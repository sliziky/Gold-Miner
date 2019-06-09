#pragma once

#include <vector>
#include <memory>
#include "Block.h"
#include "Player.h"
#include "GameObjectFactory.h"
#include "Player.h"
#include "Collision.h"
#include "Directions.h"

class Player;
class Map {
	using Row = std::vector< std::unique_ptr< Block >>;
public:
	Map( Player& player );
	void generate_row();
	void generate_map();
	const std::vector< std::vector< std::unique_ptr< Block >> >& map() const { return m_blocks; }
	const sf::Sprite& background() const { return m_background; }
	Collision check_for_collision_left() const;
	Collision check_for_collision_right() const;
	Collision check_for_collision( const Directions& ) const;
	bool block_exists_at( int row, int col ) const;

private:
	Player& m_player;
	std::vector < Row > m_blocks;
	GameObjectFactory m_factory;
	sf::Sprite m_background;
};