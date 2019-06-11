#pragma once

#include <vector>
#include <memory>
#include "Block.h"
#include "Player.h"
#include "GameObjectFactory.h"
#include "Player.h"
#include "Collision.h"
#include "Directions.h"
#include "Inventory.h"
class Player;
class Map {
	using Row = std::vector< std::unique_ptr< Block >>;
public:
	Map( Player& player, Inventory& inv, sf::RenderWindow& rw );

	//GETTERS
	std::vector< std::vector< std::unique_ptr< Block >> >& map() { return m_blocks; }
	const std::vector< std::vector< std::unique_ptr< Block >> >& map() const { return m_blocks; }
	const sf::Sprite& background() const { return m_background; }
	
	void generate_col_up( int x, int height );
	void generate_row();
	void generate_map();
	void destroy_block( const sf::Vector2i& pos );
	void create_block( const sf::Vector2i& pos );

	//COLLISION CHECKERS
	struct BlockCollision check_for_collision_left() const;
	struct BlockCollision check_for_collision_up() const;
	struct BlockCollision check_for_collision_idle() const;
	struct BlockCollision check_for_collision_right() const;
	struct BlockCollision check_for_collision( const Directions& ) const;

	bool block_exists_at( int row, int col ) const;
	void update();
private:
	sf::RenderWindow& m_window;
	Player& m_player;
	std::vector < Row > m_blocks;
	GameObjectFactory m_factory;
	Inventory& m_inventory;
	sf::Sprite m_background;
};