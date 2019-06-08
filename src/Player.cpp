#include "Player.h"

Player::Player( sf::View& view, Map& map )
	: m_is_moving( false ) 
	, m_current( nullptr )
	, m_view( view )
	, m_map( map )
{
	m_current = m_animations.idle_animation();
}


void Player::display_animation( sf::Time frame_time ) {
	m_animations.play( *m_current );
	m_animations.move( m_velocity  /*frame_time.asSeconds()*/ );
	m_animations.update( frame_time );
}
void Player::move_right() {

	// hit right border
	if ( m_animations.position().x > Config::Background::width - Config::Player::in_game_size ) {
		m_velocity.x = 0;
	} 
	// move right , dont move view
	else if ( m_animations.position().x < Config::Window::width / 2
				|| m_animations.position().x > Config::Background::width - Config::Window::width / 2 ) {
		m_velocity.x += Config::Player::acceleration.x;
	} 
	// move right, move view
	else {
		m_velocity.x += Config::Player::acceleration.x;
		m_view.move( { +Config::View::acceleration, 0 } );
	}
	// change current animation
	m_current = m_animations.right_animation();
}

void Player::move_left() {
	// hit left border
	if ( m_animations.position().x < -10 ) {
		m_velocity.x = 0;
	}
	// moving left, dont move view
	else if ( m_animations.position().x > Config::Background::width - Config::Window::width / 2
			  || m_animations.position().x < Config::Window::width / 2 ) {
		m_velocity.x -= Config::Player::acceleration.x;
	} 
	// move view also
	else {
		m_view.move( { -Config::View::acceleration, 0 } );
		m_velocity.x -= Config::Player::acceleration.x;
	}
	// change animation
	m_current = m_animations.left_animation();
}

void Player::move_up() {
	// falling down
	if ( m_acceleration <= 0 ) { 
		m_is_falling = true; 
		std::cout << m_animations.position().y << std::endl;
	}
	// hit ground
	if ( m_animations.position().y == 416 && m_is_falling ) {
		m_is_jumping = false;
		m_is_falling = false;
		m_acceleration = Config::Player::acceleration.y;
	}
	// going up
	if ( m_is_jumping ) {
		m_velocity.y -= m_acceleration;
		m_acceleration -= Config::Physics::gravity;
	}
}

void Player::move() {
	m_velocity = { 0.f, 0.f };
	m_current = m_animations.idle_animation();
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Right ) ) {
		move_right();
	}
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Left ) ) {
		move_left();
	}
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Up ) ) {
		m_is_jumping = true;
	}
	move_up();
	auto new_pos = m_animations.animated_sprite().getPosition() + m_velocity;
	for ( const auto& object : m_map.map() ) {
		for ( const auto& obj : object ) {
			if ( obj->sprite().getGlobalBounds().contains( new_pos ) ) {
				m_velocity = { 0,0 };
				return;
			}
		}
	}

}
