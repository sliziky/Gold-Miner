#pragma once
#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>

#include "Config.h"
#include "IGameObject.h"
#include "Animations.h"
class Player : public sf::Sprite, public IGameObject {

public:
	Player();
	void gameTick() override;
	void position( const sf::Vector2f& pos ) override;
	const sf::Vector2f& position() const override;
	std::vector< sf::Sprite > _sprites;
	std::vector< sf::Texture > _textures;
	const Animation* current() const { return m_current; }
	const Animations& animations() const { return m_animations; }

	void move_right( sf::View& view );
	void move_left( sf::View& view );
	void move( sf::View& view );
	void display_animation( sf::Time frame_time );

private:
	sf::Vector2f m_movement;
	bool m_is_moving;
	sf::Vector2f m_position;
	Animations m_animations;
	Animation* m_current;
	sf::View m_view;
};