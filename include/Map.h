#pragma once

#include <vector>
#include <memory>
#include "Block.h"
#include "GameObjectFactory.h"
class Map {
	using Row = std::vector< std::unique_ptr< Block >>;
public:
	void generate_row();
	const std::vector< std::vector< std::unique_ptr< Block >> >& map() const { return m_blocks; }
private:
	std::vector < Row > m_blocks;
	GameObjectFactory m_factory;
};