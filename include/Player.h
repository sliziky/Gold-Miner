#pragma once
#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>

#include "Config.h"
#include "IGameObject.h"
#include "Animations.h"
#include "Map.h"
class Map;
class Player {

public:
	Player( sf::View& view, Map& map );
	const Animation* current() const { return m_current; }
	const Animations& animations() const { return m_animations; }

	void move_right();
	void move_left();
	void move_up();
	void move();
	void display_animation( sf::Time frame_time );
	void is_jumping( bool v ) { m_is_jumping = v; }
private:
	sf::Vector2f m_velocity;
	bool m_is_moving;
	bool m_is_falling = false;
	bool m_is_jumping = false;
	sf::Vector2f m_position;
	Animations m_animations;
	Animation* m_current;
	sf::View& m_view;
	Map& m_map;
	int m_acceleration = Config::Player::acceleration.y;
};