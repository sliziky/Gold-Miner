#include "../include/Animations.h"
#include "Config.h"
Animations::Animations()
	: m_animated_sprite( sf::seconds( Config::Animations::speed ), false, true )
	, sheet_size( Config::Player::sheet_size )
{
	//TODO error while loading

	m_player_texture.loadFromFile( "new.png" );

	m_animated_sprite.setPosition({ static_cast< float > (Config::Window::width / 2), 
									static_cast< float > (Config::Window::height - Config::Player::in_game_size)
								   });
	m_animated_sprite.setScale( Config::Player::scale );
	
	m_idle_animation.setSpriteSheet( m_player_texture );
	m_right_animation.setSpriteSheet( m_player_texture );
	m_left_animation.setSpriteSheet( m_player_texture );
	// load idle animation from spritesheet
	for ( int i = 0; i < m_player_texture.getSize().x / sheet_size; ++i ) {
		m_idle_animation.addFrame( sf::IntRect( i * 32, 0, 32, 64 ) );
	}

	// load right animation from spritesheet
	//for ( int i = 0; i < 8; ++i ) {
	//	m_right_animation.addFrame( sf::IntRect( i * sheet_size, 0, sheet_size, sheet_size ) );

	//	//m_right_animation.addFrame( sf::IntRect( i * sheet_size, 32, sheet_size, sheet_size ) );
	//}

	//// load left animation from spritesheet
	//for ( int i = 0; i < 8; ++i ) {
	//	m_left_animation.addFrame( sf::IntRect( i* sheet_size, 0, sheet_size, sheet_size ) );

	//	//m_left_animation.addFrame( sf::IntRect( i * sheet_size, 288, sheet_size, sheet_size ) );
	//}
}

Animation* Animations::left_animation() {
	return &m_left_animation;
}

const Animation* Animations::left_animation() const {
	return &m_left_animation;
}

Animation* Animations::right_animation() {
	return &m_right_animation;
}

const Animation* Animations::right_animation() const {
	return &m_right_animation;
}

Animation* Animations::idle_animation() {
	return &m_idle_animation;
}

const Animation* Animations::idle_animation() const {
	return &m_idle_animation;
}

void Animations::play( const Animation& animation ) {
	m_animated_sprite.play( animation );
}

void Animations::move( const sf::Vector2f& offset ) {
	m_animated_sprite.move( offset );
}

void Animations::move( float offsetX, float offsetY ) {
	m_animated_sprite.move( offsetX, offsetY );
}

void Animations::update( sf::Time delta_time )  {
	m_animated_sprite.update( delta_time );
}

const AnimatedSprite& Animations::animated_sprite() const {
	return m_animated_sprite;
}

AnimatedSprite& Animations::animated_sprite() {
	return m_animated_sprite;
}
