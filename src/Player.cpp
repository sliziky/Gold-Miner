#include "Player.h"

Player::Player()
	: m_is_moving( false ) 
	, m_current( nullptr )
{
	m_current = m_animations.idle_animation();
	position(m_animations.position());
}
void Player::gameTick()  {

}

const sf::Vector2f& Player::position() const  {
	return m_position;
}

void Player::position( const sf::Vector2f& new_pos ) {
	m_position = new_pos;
}

void Player::display_animation( sf::Time frame_time ) {
	m_animations.play( *m_current );
	m_animations.move( m_movement * frame_time.asSeconds() );
	m_animations.update( frame_time );
}
void Player::move_right( sf::View& view ) {
	if ( m_animations.position().x > Config::Background::width - 64 ) {
		m_movement.x = 0;
	} else if ( m_animations.position().x < Config::Window::width / 2
				|| m_animations.position().x > Config::Background::width - Config::Window::width / 2 ) {
		m_movement.x += Config::Player::speed.x;
	} else {
		m_movement.x += Config::Player::speed.x;
		view.move( { +Config::View::speed, 0 } );
	}
	m_current = m_animations.right_animation();
}

void Player::move_left( sf::View& view ) {
	if ( m_animations.position().x < -10 ) {
		m_movement.x = 0;
	} else if ( m_animations.position().x > Config::Background::width - Config::Window::width / 2 ) {
		m_movement.x -= Config::Player::speed.x;
	} else if ( m_animations.position().x < Config::Window::width / 2 ) {
		m_movement.x -= Config::Player::speed.x;
	} else {
		view.move( { -Config::View::speed, 0 } );
		m_movement.x -= Config::Player::speed.x;
	}
	m_current = m_animations.left_animation();
}

void Player::move( sf::View& view ) {
	m_movement = { 0.f, 0.f };
	m_current = m_animations.idle_animation();
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Right ) ) {
		move_right( view );
	}
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Left ) ) {
		move_left( view );
	}
}
