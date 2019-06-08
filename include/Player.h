#pragma once
#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>

#include "Config.h"
#include "IGameObject.h"
#include "Animations.h"
class Player {

public:
	Player( sf::View& view );
	const Animation* current() const { return m_current; }
	const Animations& animations() const { return m_animations; }

	void move_right();
	void move_left();
	void move_up();
	void move();
	void display_animation( sf::Time frame_time );

private:
	sf::Vector2f m_velocity;
	bool m_is_moving;
	bool m_is_falling = false;
	bool m_is_jumping = false;
	sf::Vector2f m_position;
	Animations m_animations;
	Animation* m_current;
	sf::View& m_view;
	int m_acceleration = Config::Player::acceleration.y;
};