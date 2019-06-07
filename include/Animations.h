#pragma once
#include "../thirdparty/animation/src/AnimatedSprite.h"
#include "Config.h"
class Animations {
public:
	Animations();
	Animation* left_animation();
	const Animation* left_animation() const;
	Animation* right_animation();
	const Animation* right_animation() const;
	Animation* idle_animation();
	const Animation* idle_animation() const;
	void play( const Animation& animation );
	void move( const sf::Vector2f& offset );
	void move( float offsetX, float offsetY);
	void update( sf::Time delta_time );
	const AnimatedSprite& animated_sprite() const;
	AnimatedSprite& animated_sprite();
	const sf::Vector2f& position() const { return m_animated_sprite.getPosition(); }

	const uint8_t sheet_size = Config::Player::sheet_size;
	

private:
	Animation m_idle_animation;
	Animation m_right_animation;
	Animation m_left_animation;
	AnimatedSprite m_animated_sprite;
	sf::Texture m_player_texture;
};