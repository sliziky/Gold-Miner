#include "Map.h"
#include "Config.h"
#include "Collision.h"
Map::Map( Player& player )
	: m_player( player )
{
	sf::Texture text;
	text.loadFromFile( "background.png" );
	m_background.setTexture( text );
	m_background.setPosition( { 0, 0 } );
	m_blocks.resize( Config::Map::depth );
	for ( int i = 0; i < Config::Map::depth; ++i ) {
		m_blocks[ i ].resize( Config::Map::width );
	}
}

bool Map::block_exists_at( int row, int col ) const {
	if ( row < 0 || col < 0 ) return false;
	if ( row >= Config::Map::depth || col >= Config::Map::width ) return false;
	return m_blocks[ row ][ col ] != nullptr;
}

Collision Map::check_for_collision( const Directions& direction ) const {
	if ( direction == Directions::Right ) {
		return check_for_collision_right();
	}
	if ( direction == Directions::Left ) {
		return check_for_collision_left();
	}
}

Collision Map::check_for_collision_left() const {
	const auto& player_position = m_player.position();
	const auto& player_velocity = m_player.velocity();
	auto new_pos = player_position + player_velocity;

	// index_x, index_y represent coordinations in our map
	auto index_x = static_cast< int >( m_player.player_right_border( new_pos )) / Config::Block::size;
	auto index_y = static_cast< int >(Config::Window::height - Config::Player::in_game_size - player_position.y + 2) / 32;
	
	bool above_ground = index_y > 0 ? true : false;
	// fall from block, consider right border of the player
	if ( !m_player.is_jumping() && above_ground && !block_exists_at(index_y - 1, index_x ) ) {
		return Collision::NO_BLOCK_UNDER;
	}
	// block in the way, consider left border of the player
	index_x = (int)(new_pos.x + Config::Player::from_player_border.x) / Config::Block::size;
	if ( block_exists_at( index_y, index_x ) ) {
		return Collision::BLOCK_COLLISION;
	}
	return Collision::NO_COLLISION;
}

Collision Map::check_for_collision_right() const {
	const auto& player_position = m_player.position();
	const auto& player_velocity = m_player.velocity();
	auto new_pos = player_position + player_velocity;

	// index_x, index_y represent coordinations in our map
	auto index_x = static_cast< int >( m_player.player_right_border(new_pos) ) / Config::Block::size;
	auto index_y = static_cast< int >(Config::Window::height - Config::Player::in_game_size - player_position.y + 2) / 32;
	
	bool above_ground = index_y > 0 ? true : false;
	// fall from block, consider left border of the player
	if ( !m_player.is_jumping() && above_ground && !block_exists_at( index_y - 1, index_x ) ) {
		return Collision::NO_BLOCK_UNDER;
	}
	
	if ( block_exists_at( index_y, index_x ) ) {
		return Collision::BLOCK_COLLISION;
	}
	return Collision::NO_COLLISION;
}

void Map::generate_row() {
	// generate row of blocks
	// testing version so far
	for ( int i = 0; i < 8; ++i ) {
		m_blocks[ 0 ][ i ] = m_factory.create_grass( { (float)i * 32, (float)Config::Window::height - 32 } );
	}
	for ( int i = 20; i < 25; ++i ) {
		m_blocks[ 0 ][ i ] = m_factory.create_grass( { (float)i * 32, (float)Config::Window::height - 32 } );
	}

}

void Map::generate_map() {
	for ( int i = 0; i < 1; ++i ) {
		generate_row();
	}
}
