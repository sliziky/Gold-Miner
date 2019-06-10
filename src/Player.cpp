#include "Player.h"
#include "Directions.h"
#include "Collision.h"
Player::Player( sf::View& view, Map& map )
	: m_is_moving( false ) 
	, m_current( nullptr )
	, m_view( view )
	, m_map( map )
{
	m_current = m_animations.idle_animation();
}


bool Player::near_left_border() const {
	return position().x + 16  <= 320;
}

const sf::Vector2f& Player::middle_pos() const {
	return {};
}

bool Player::near_right_border() const {
	return position().x > Config::Background::width - Config::Window::width / 2;
}

bool Player::hit_left_border() const {
	return position().x + m_velocity.x < 0;
}

bool Player::hit_right_border() const {
	return position().x + m_velocity.x + Config::Player::size.x >= Config::Background::width;
}

void Player::stop_moving() {
	m_velocity.x = 0.f;
	//m_velocity = { 0.f, 0.f };
}

void Player::display_animation( const sf::Time& frame_time ) {
	// play current animation
	m_animations.play( *m_current );
	//move view 
	//m_view.move( m_view_speed );
	// move player
	m_animations.move( m_velocity  /*frame_time.asSeconds()*/ );
	// update stuff
	m_animations.update( frame_time );
}
void Player::move_right() {

	m_velocity.x += Config::Player::acceleration.x;
	auto new_pos = position() + m_velocity;
	if ( hit_right_border() ) { stop_moving(); };

	auto border_distance = Config::Window::width / 2 + Config::Player::acceleration.x;
	
	if ( new_pos.x >= border_distance && position().x < 1280 - border_distance   ) {
		m_view_speed.x = Config::View::acceleration;
	}
}

void Player::move_left() {

	m_velocity.x -= Config::Player::acceleration.x;
	auto new_pos = position() + m_velocity;
	if ( hit_left_border() ) { stop_moving(); };

	auto border_distance = Config::Window::width / 2 + Config::Player::acceleration.x;


	if ( position().x >= border_distance && new_pos.x < 1280- border_distance ) {
		m_view_speed.x = -Config::View::acceleration;
	}

}
void Player::move_up() {

	// falling down
	if ( m_acceleration <= 0 ) {
		m_is_falling = true;
	}
	if ( m_is_jumping ) {
		m_velocity.y -= m_acceleration;
		m_acceleration -= Config::Physics::gravity;
	}

	const auto& map = m_map.map();
	auto new_pos = position() + m_velocity;
	auto index_x_left = (int)( player_left_border( new_pos ) ) / Config::Block::size;
	auto index_x_right = (int)( player_right_border( new_pos ) ) / Config::Block::size;
	index_y = (int)( Config::Window::height - new_pos.y - Config::Player::size.y/2 ) / Config::Block::size;

	// ground or block under
	if ( m_is_falling 
		 && ( index_y == 0 
		 ||  map[ index_y - 1 ][ index_x_left ] != nullptr 
		 ||  map[ index_y - 1 ][ index_x_right ] != nullptr )) {
		// hit the ground
		if ( index_y == 0 ) {
			m_animations.animated_sprite().setPosition( position().x, 416 );
		}
		// hit the block
		else {
			sf::Vector2f pos;
			//get the position of the block
			if ( m_map.block_exists_at( index_y - 1, index_x_left )) {
				pos = map[ index_y - 1 ][ index_x_left ]->position();
			}
			if ( m_map.block_exists_at( index_y - 1, index_x_right ) ) {
				pos = map[ index_y - 1 ][ index_x_right ]->position();
			}
			// place player above the block
			m_animations.animated_sprite().setPosition( position().x, pos.y - 2 * Config::Block::size );
		}

		m_is_jumping = false;
		m_is_falling = false;
		m_velocity.y = 0;
		m_acceleration = Config::Player::acceleration.y;
	}

	
}

void Player::fall_down() {
	// falling
	if ( m_is_falling_from_block ) {
		m_velocity.y += m_acceleration2;
		m_acceleration2 += Config::Physics::gravity;
	}

	const auto& map = m_map.map();
	auto new_pos = position() + m_velocity;

	// index depends whether we go right or left
	int index_x;

	if ( m_direction == Directions::Right ) {
		index_x = static_cast< int >( player_left_border(position()) - Config::Block::size ) / Config::Block::size;
	}
	if ( m_direction == Directions::Left ) {
		index_x = static_cast< int >( player_right_border(position()) - Config::Block::size ) / Config::Block::size;
	}
	index_y = (int)(Config::Window::height - new_pos.y - Config::Player::size.y) / Config::Block::size;

	if ( m_block_up || m_is_falling_from_block && (index_y == 0 || map[ index_y - 1 ][ index_x ] != nullptr) ) {
		// hit the ground
		if ( index_y == 0 ) {
			m_animations.animated_sprite().setPosition( position().x, 416 );
		}
		// hit the block
		else {
			auto pos = map[ index_y - 1 ][ index_x ]->position();
			m_animations.animated_sprite().setPosition( position().x, pos.y - 64);
		}
		m_block_up = false;
		m_is_falling_from_block = false;
		m_velocity.y = 0;
		m_acceleration2 = Config::Player::acceleration.y;
	}
}

void Player::update() {
	m_velocity = { 0.f, 0.f };
	m_view_speed = { 0.f, 0.f };
	m_current = m_animations.idle_animation();
	m_direction = Directions::Idle;

	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Up ) ) {
		m_direction = Directions::Up;
		m_is_jumping = true;
	}
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Right ) ) {
		m_direction = Directions::Right;
		move_right();
	}
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Left ) ) {
		m_direction = Directions::Left;
		move_left();
	}


	// check for COLLISION
	BlockCollision collision_detection = m_map.check_for_collision( m_direction );
	if ( collision_detection.collision == Collision::BLOCK_COLLISION ) {
		stop_moving();
		stop_view();
	}
	if ( collision_detection.collision == Collision::NO_BLOCK_UNDER ) {
		m_is_falling_from_block = true;
	}
	//if ( collision_detection.collision == Collision::BLOCK_PICKABLE ) {
	//	m_map.map()[ collision_detection.index_y ][ collision_detection.index_x ].reset();
	//}
	//if ( collision_detection.collision == Collision::BLOCK_UNDER_PICKABLE ) {
	//	m_is_falling_from_block = true;
	//	m_map.map()[ collision_detection.index_y ][ collision_detection.index_x ].reset();
	//}
	if ( m_direction == Directions::Up &&  collision_detection.collision == Collision::BLOCK_ABOVE ) {
		m_is_jumping = false;
		m_is_falling = false;
		m_velocity.y = 0.f;
		//m_velocity = { 0, 0 };
		//m_acceleration = Config::Player::acceleration.y;
	}
	move_up(); // jumping
	fall_down(); // falling from the block
}


void Player::stop_view() {
	m_view_speed = { 0.f, 0.f };
}

const sf::Vector2f& Player::position() const { 
	return m_animations.animated_sprite().getPosition(); 
}

float Player::player_left_border( const sf::Vector2f& pos ) const {
	return pos.x;
}

float Player::player_right_border( const sf::Vector2f& pos ) const {
	return pos.x + Config::Player::size.x; 
}

const sf::Vector2f& Player::velocity() const {
	return m_velocity;
}