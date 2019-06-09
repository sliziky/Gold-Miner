#pragma once
#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>

#include "Config.h"
#include "IGameObject.h"
#include "Animations.h"
#include "Map.h"
#include "Directions.h"
#include "Collision.h"
class Map;

class Player {

public:
	Player( sf::View& view, Map& map );

	const Animation* current() const { return m_current; }
	const Animations& animations() const { return m_animations; }
	
	void update();
	void move_right();
	void move_left();
	void move_up();
	void fall_down();
	void display_animation( const sf::Time& frame_time );

	//GETTERS
	const sf::Vector2f& position() const;
	const sf::Vector2f& velocity() const;
	float player_right_border( const sf::Vector2f& pos ) const;
	float player_left_border( const sf::Vector2f& pos ) const;
	const sf::Vector2f& middle_pos() const;
	bool  is_jumping() const { return m_is_jumping; }

	bool near_right_border() const;
	bool near_left_border() const;
	bool hit_left_border() const;
	bool hit_right_border() const;
	void stop_moving();
	void stop_view();

private:
	bool m_is_falling_from_block = false;
	bool m_is_moving;
	bool m_is_falling = false;
	bool m_is_jumping = false;
	sf::Vector2f m_velocity; // player velocity
	sf::Vector2f m_position; // player position
	sf::Vector2f m_view_speed; 
	Animations m_animations; // stores all animations ( right, left, idle )
	Animation* m_current; // current animation to be drawn
	sf::View& m_view; // view from Window
	Map& m_map;	
	int m_acceleration = Config::Player::acceleration.y;
	int m_acceleration2 = Config::Player::acceleration.y;
	Directions m_direction;
};