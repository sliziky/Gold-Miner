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

	//GETTERS
	std::vector< std::vector< std::unique_ptr< Block >> >& map() { return m_blocks; }
	//const std::vector< std::vector< std::unique_ptr< Block >> >& map() const { return m_blocks; }
	const sf::Sprite& background() const { return m_background; }
	
	void generate_col_up( int x, int height );
	void generate_row();
	void generate_map();
	void check_for_destroying( const sf::Vector2i& pos );
	void destroy_block( int row, int col );
	struct BlockCollision check_for_collision_left() const;
	struct BlockCollision check_for_collision_up() const;
	struct BlockCollision check_for_collision_idle() const;

	struct BlockCollision check_for_collision_right() const;
	struct BlockCollision check_for_collision( const Directions& ) const;
	bool block_exists_at( int row, int col ) const;

private:
	Player& m_player;
	std::vector < Row > m_blocks;
	GameObjectFactory m_factory;
	sf::Sprite m_background;
};