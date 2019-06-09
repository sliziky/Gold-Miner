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
	return m_animations.position().x < Config::Window::width / 2;
}

const sf::Vector2f& Player::middle_pos() const {
	return { player_left_border(position()) + 32, player_left_border(position()) + 32 };
}

bool Player::near_right_border() const {
	return m_animations.position().x > Config::Background::width - Config::Window::width / 2;
}

bool Player::hit_left_border() const {
	return m_animations.position().x < 0 - Config::Player::from_player_border.x;
}

bool Player::hit_right_border() const {
	return m_animations.position().x > Config::Background::width - Config::Player::in_game_size + Config::Player::from_player_border.y;
}

void Player::stop_moving() {
	m_velocity = { 0.f, 0.f };
}

void Player::display_animation( const sf::Time& frame_time ) {
	// play current animation
	m_animations.play( *m_current );
	//move view 
	m_view.move( m_view_speed );
	// move player
	m_animations.move( m_velocity  /*frame_time.asSeconds()*/ );
	// update stuff
	m_animations.update( frame_time );
}
void Player::move_right() {

	// right border of the window
	if ( hit_right_border() ) {
		stop_moving();
	} 
	// move right , dont move view
	else if ( near_left_border() || near_right_border() ) {
		m_velocity.x += Config::Player::acceleration.x;
	} 
	// move right, move view
	else {
		m_velocity.x += Config::Player::acceleration.x;
		m_view_speed.x = Config::View::acceleration;
	}
}

void Player::move_left() {

	// left border of the window
	if ( hit_left_border() ) {
		stop_moving();
	}
	// moving left, dont move view
	else if ( near_left_border() || near_right_border() ) {
		m_velocity.x -= Config::Player::acceleration.x;
	}
	// move view also
	else {
		m_view_speed.x = -Config::View::acceleration;
		m_velocity.x -= Config::Player::acceleration.x;
	}
}
void Player::move_up() {

	// falling down
	if ( m_acceleration <= 0 ) {
		m_is_falling = true; 
	}

	const auto& map = m_map.map();
	auto new_pos_y = position().y + m_velocity.y;
	auto index_x_left = (int)( player_left_border(position()) ) / Config::Block::size;
	auto index_x_right = (int)( player_right_border(position()) ) / Config::Block::size;
	auto index_y = (int)( Config::Window::height - new_pos_y - 25 ) / 32;

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
			m_animations.animated_sprite().setPosition( position().x, pos.y - 64 );
		}


		m_is_jumping = false;
		m_is_falling = false;
		m_velocity.y = 0;
		m_acceleration = Config::Player::acceleration.y;
	}
	// going up
	if ( m_is_jumping ) {
		m_velocity.y -= m_acceleration;
		m_acceleration -= Config::Physics::gravity;
	}
	
}

void Player::fall_down() {
	// falling
	if ( m_is_falling_from_block ) {
		m_velocity.y += m_acceleration2;
		m_acceleration2 += Config::Physics::gravity;
	}
	const auto& map = m_map.map();
	auto new_pos_y = position().y + m_velocity.y;

	// index depends whether we go right or left
	int index_x;
	if ( m_direction == Directions::Right ) {
		index_x = (int)(player_right_border(position()) - 32) / 32;
	}
	if ( m_direction == Directions::Left ) {
		index_x = (int)(player_left_border(position()) - 32) / 32;
	}
	auto index_y = (int)(Config::Window::height - new_pos_y - 25) / 32;
	// ground or block under
	if ( m_is_falling_from_block && (index_y == 0 || map[ index_y - 1 ][ index_x ] != nullptr) ) {
		// hit the ground
		if ( index_y == 0 ) {
			m_animations.animated_sprite().setPosition( position().x, Config::Map::ground );
		}
		// hit the block
		else {
			auto pos = map[ index_y - 1 ][ index_x ]->position();
			m_animations.animated_sprite().setPosition( position().x, pos.y - 64 );
		}
		m_is_falling_from_block = false;
		m_velocity.y = 0;
		m_acceleration2 = Config::Player::acceleration.y;
	}
}

void Player::update() {
	m_velocity = { 0.f, 0.f };
	m_view_speed = { 0.f, 0.f };
	m_current = m_animations.idle_animation();

	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Up ) ) {
		m_direction = Directions::Up;
		m_is_jumping = true;
	}
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Right ) ) {
		m_direction = Directions::Right;
		m_current = m_animations.right_animation();
		move_right();
	}
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Left ) ) {
		m_direction = Directions::Left;
		m_current = m_animations.left_animation();
		move_left();
	}

	// check for COLLISION
	auto collision = m_map.check_for_collision( m_direction );
	if ( collision == Collision::BLOCK_COLLISION ) {
		stop_moving();
		stop_view();
	}
	if ( collision == Collision::NO_BLOCK_UNDER ) {
		m_is_falling_from_block = true;
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
	return pos.x + Config::Player::from_player_border.x;
}

float Player::player_right_border( const sf::Vector2f& pos ) const {
	return pos.x + Config::Player::in_game_size - Config::Player::from_player_border.y; 
}

const sf::Vector2f& Player::velocity() const {
	return m_velocity;
}