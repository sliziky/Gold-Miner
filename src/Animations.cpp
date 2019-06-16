#include "Animations.h"
#include "Config.h"
Animations::Animations()
	: m_animated_sprite( sf::seconds( Config::Animations::speed ), false, true )
	, sheet_size( Config::Player::sheet_size )
{
	//TODO error while loading

	m_player_texture.loadFromFile( "new.png" );

	m_animated_sprite.setPosition({ static_cast< float > (276), 
									static_cast< float > (Config::Window::height - 60)
								   });

	m_animated_sprite.setScale( Config::Player::scale );
	
	m_idle_animation.setSpriteSheet( m_player_texture );
	m_right_animation.setSpriteSheet( m_player_texture );
	m_left_animation.setSpriteSheet( m_player_texture );

	// load idle animation from spritesheet
	for ( int i = 0; i < m_player_texture.getSize().x / sheet_size; ++i ) {
		m_idle_animation.addFrame( sf::IntRect( i * Config::Player::size.x, 0, Config::Player::size.x, Config::Player::size.y ) );
	}
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
