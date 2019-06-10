#include "Map.h"
#include "Config.h"
#include "Collision.h"
Map::Map( Player& player , Inventory& inv )
	: m_player( player )
	, m_inventory( inv )
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

struct BlockCollision Map::check_for_collision( const Directions& direction ) const {
	if ( direction == Directions::Right ) {
		return check_for_collision_right();
	}
	if ( direction == Directions::Left ) {
		return check_for_collision_left();		
	}

	//if ( direction == Directions::Up ) {
	//	return check_for_collision_up();
	//}
	//if ( direction == Directions::Idle ) {
	//	return check_for_collision_idle();
	//}
	return { Collision::NO_COLLISION, 0, 0 };
}

struct BlockCollision Map::check_for_collision_left() const {
	const auto& player_position = m_player.position();
	const auto& player_velocity = m_player.velocity();
	auto new_pos = player_position + player_velocity;

	// index_x, index_y represent coordinations in our map

	auto block_near_feet = Config::Window::height - new_pos.y - Config::Player::size.y/4;
	auto block_near_face = block_near_feet - Config::Block::size;
	
	auto index_x_right_b = static_cast<int>(m_player.player_right_border( new_pos )) / Config::Block::size;
	auto index_x_left_b = static_cast<int>(m_player.player_left_border( new_pos )) / Config::Block::size;
	auto index_y_face = static_cast< int> ( block_near_face ) / Config::Block::size;
	auto index_y_feet = static_cast< int >( block_near_feet ) / Config::Block::size;
	auto index_x = static_cast< int >(m_player.player_left_border( new_pos )) / Config::Block::size;
	if ( block_exists_at( index_y_feet, index_x ) || block_exists_at( index_y_face, index_x ) ) {
		return { Collision::BLOCK_COLLISION, index_x, index_y_feet };
	}

	return { Collision::NO_COLLISION, 0, 0 };
}
//
//
//struct BlockCollision Map::check_for_collision_idle() const {
//	const auto& player_position = m_player.position();
//	const auto& player_velocity = m_player.velocity();
//	auto new_pos = player_position + player_velocity;
//	auto index_x = static_cast<int>(m_player.player_left_border( new_pos )) / Config::Block::size;
//	auto index_y = static_cast<int>(Config::Window::height - new_pos.y + Config::Player::size.y) / Config::Block::size;
//	if ( !block_exists_at( index_y, index_x ) ) {
//		return { Collision::NO_BLOCK_UNDER, index_x, index_y };
//	}
//
//}
//
//struct BlockCollision Map::check_for_collision_up() const {
//	const auto& player_position = m_player.position();
//	const auto& player_velocity = m_player.velocity();
//	auto new_pos = player_position + player_velocity;
//	auto index_x = static_cast<int>(m_player.player_left_border( new_pos ) + 1) / Config::Block::size;
//	auto index_y = static_cast<int>(Config::Window::height - new_pos.y) / Config::Block::size;
//	if ( block_exists_at( index_y, index_x ) ) {
//	std::cout << "Index of blocking block " << index_x << std::endl;
//		return { Collision::BLOCK_ABOVE, index_x, index_y };
//	}
//	//index_x = static_cast<int>(m_player.player_right_border( new_pos )) / Config::Block::size;
//	//if ( block_exists_at( index_y, index_x ) ) {
//	//	return { Collision::BLOCK_ABOVE, index_x, index_y };
//	//}
//	return {Collision::NO_COLLISION, 0, 0};
//}
//
struct BlockCollision Map::check_for_collision_right() const {
	const auto& player_position = m_player.position();
	const auto& player_velocity = m_player.velocity();
	auto new_pos = player_position + player_velocity;

	// index_x, index_y represent coordinations in our map

	auto block_near_face = Config::Window::height - new_pos.y - Config::Player::size.y / 4;
	auto block_near_feet = block_near_face - Config::Player::size.y / 2;

	auto index_y_feet = static_cast< int > (block_near_feet) / Config::Block::size;
	auto index_y_face = static_cast< int > (block_near_face) / Config::Block::size;
	auto index_x_right_b = static_cast< int >(m_player.player_right_border( new_pos )) / Config::Block::size;
	auto index_x_left_b  = static_cast<int>(m_player.player_left_border( new_pos )) / Config::Block::size;
	auto index_x_mid = (m_player.player_left_border( new_pos ) + Config::Player::size.x / 2) / Config::Block::size;
	std::cout << index_y_feet << std::endl;
	if ( block_exists_at( index_y_feet, index_x_right_b ) || block_exists_at( index_y_face, index_x_right_b ) ) {
		return { Collision::BLOCK_COLLISION, index_x_right_b, index_y_feet };
	}

	if ( !m_player.is_jumping() && index_y_feet > 0 && !block_exists_at( index_y_feet - 1, index_x_mid)) {
		return { Collision::NO_BLOCK_UNDER, index_x_left_b, index_y_feet - 1 };
	}

	return { Collision::NO_COLLISION, 0, 0 };
}

void Map::generate_row() {
	// generate row of blocks
}

void Map::generate_col_up( int x, int height ) {
	for ( int i = 0; i < height; ++i ) {
		m_blocks[ i ][ x ] = m_factory.create_grass( {(float)x * 32, Config::Window::height - (float)i * Config::Block::size - Config::Block::size}  );
	}
}

void Map::generate_map() {
	for ( int i = 5; i >= 0; --i ) {
		generate_col_up( 5 - i ,  i );
	}
	for ( int i = 0; i <= 5; ++i ) {
		generate_col_up( 15 + i , i );
	}
}

void Map::destroy_block( const sf::Vector2i& pos ) {
	//auto index_x = static_cast<int>(pos.x) / Config::Block::size * Config::Block::size;
	//auto index_y = static_cast<int>(Config::Window::height - pos.y) / Config::Block::size * Config::Block::size;
	auto index_x = static_cast< int >(pos.x) / Config::Block::size;
	auto index_y = static_cast< int >(Config::Window::height - pos.y - 1) / Config::Block::size;
	if ( block_exists_at( index_y, index_x ) ) {
		m_blocks[ index_y ][ index_x ].reset();
	}
}

void Map::create_block( const sf::Vector2i& pos ) {
	//auto index_x = static_cast<int>(pos.x) / Config::Block::size * Config::Block::size;
	//auto index_y = static_cast<int>(Config::Window::height - pos.y) / Config::Block::size * Config::Block::size;
	auto index_x = static_cast<int>(pos.x) / Config::Block::size;
	auto index_y = static_cast<int>(Config::Window::height - pos.y - 1) / Config::Block::size;
	std::cout << index_y << std::endl;
	sf::Vector2f p = { (float)pos.x, (float)pos.y };
	if ( !block_exists_at( index_y, index_x ) && m_inventory.current()->getTexture() != nullptr ) {
		m_blocks[ index_y ][ index_x ] = m_factory.create_dirt( p );
	}
}
