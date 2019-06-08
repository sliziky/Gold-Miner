#include "Map.h"
#include "Config.h"

Map::Map( )
{
	sf::Texture text;
	text.loadFromFile( "background.png" );
	m_background.setTexture( text );
}
void Map::generate_row() {
	// generate row of blocks
	std::vector< std::unique_ptr<Block>> row;
	for ( int i = 0; i < 8; ++i ) {
		row.push_back( m_factory.create_grass( { (float)i * 32, (float)Config::Window::height - 32 } ));
	}
	m_blocks.emplace_back( std::move( row ) );

	for ( int i = 0; i < 5; ++i ) {
		row.push_back( m_factory.create_grass( { (float)i * 32, (float)Config::Window::height - 64 } ) );
	}
	m_blocks.emplace_back( std::move( row ) );
}

//bool Map::check_for_collision() const {
//	for ( const auto& row : m_blocks ) {
//		for ( const auto& block : row ) {
//			if ( block->sprite().getGlobalBounds().intersects( m_player.animations().animated_sprite().getGlobalBounds() ) ) {
//				return true;
//			}
//		}
//	}
//	return false;
//}