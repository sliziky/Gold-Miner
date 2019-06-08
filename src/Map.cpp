#include "Map.h"
#include "Config.h"
void Map::generate_row() {
	// generate row of blocks
	std::vector< std::unique_ptr<Block>> row;
	for ( int i = 0; i < Config::Map::width; ++i ) {
		row.push_back( m_factory.create_grass( { (float)i * 32, (float)Config::Window::height - 32 } ));
	}
	m_blocks.emplace_back( std::move( row ) );
}