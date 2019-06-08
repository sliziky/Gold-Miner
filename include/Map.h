#pragma once

#include <vector>
#include <memory>
#include "Block.h"
#include "Player.h"
#include "GameObjectFactory.h"
class Map {
	using Row = std::vector< std::unique_ptr< Block >>;
public:
	Map();
	void generate_row();
	const std::vector< std::vector< std::unique_ptr< Block >> >& map() const { return m_blocks; }
	const sf::Sprite& background() const { return m_background; }
private:
	std::vector < Row > m_blocks;
	GameObjectFactory m_factory;
	sf::Sprite m_background;
};