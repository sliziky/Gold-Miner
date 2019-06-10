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

struct BlockCollision Map::check_for_collision( const Directions& direction ) const {
	if ( direction == Directions::Right ) {
		return check_for_collision_right();
	}
	if ( direction == Directions::Left ) {
		return check_for_collision_left();
	}
	if ( direction == Directions::Up ) {
		return check_for_collision_up();
	}
	if ( direction == Directions::Idle ) {
		return check_for_collision_idle();
	}
	return { Collision::NO_COLLISION, 0, 0 };
}

struct BlockCollision Map::check_for_collision_left() const {
	const auto& player_position = m_player.position();
	const auto& player_velocity = m_player.velocity();
	auto new_pos = player_position + player_velocity;

	// index_x, index_y represent coordinations in our map

	auto index_y = static_cast< int >(Config::Window::height - player_position.y - Config::Player::size.y) / 32;
//	std::cout << Config::Window::height - player_position.y - Config::Player::size.y << std::endl;
	bool above_ground = index_y > 0 ? true : false;
	// fall from block, consider right border of the player


	auto index_x = static_cast<int>(m_player.player_left_border( new_pos )) / Config::Block::size;
	if ( block_exists_at( index_y, index_x ) ) {
		if ( !m_blocks[ index_y ][ index_x ]->pickable() ) {
			return { Collision::BLOCK_COLLISION, index_x, index_y };
		} else {
			return { Collision::BLOCK_PICKABLE, index_x, index_y };
		}
	}

	if ( block_exists_at( index_y + 1, index_x ) ) {
		if ( !m_blocks[ index_y + 1 ][ index_x ]->pickable() ) {
			return { Collision::BLOCK_COLLISION, index_x, index_y + 1};
		} else {
			return { Collision::BLOCK_PICKABLE, index_x, index_y + 1};
		}
	}


	index_x = static_cast< int >( m_player.player_right_border( new_pos )) / Config::Block::size;
	auto index_x_2 = static_cast<int>(m_player.player_left_border( new_pos )) / Config::Block::size;

	if ( !m_player.is_jumping() && above_ground ) {
		if ( !block_exists_at( index_y - 1, index_x ) && !block_exists_at( index_y - 1, index_x_2 ) ) {
			return { Collision::NO_BLOCK_UNDER, index_x, index_y - 1 };
		}
		if ( block_exists_at( index_y - 1, index_x ) && m_blocks[ index_y - 1 ][ index_x ]->pickable() ) {
			return { Collision::BLOCK_UNDER_PICKABLE, index_x, index_y - 1 };
		}
	}
	// block in the way, consider left border of the player
	//index_x = (int)(new_pos.x + Config::Player::from_player_border.x) / Config::Block::size;
	return { Collision::NO_COLLISION, 0, 0 };
}


struct BlockCollision Map::check_for_collision_idle() const {
	const auto& player_position = m_player.position();
	const auto& player_velocity = m_player.velocity();
	auto new_pos = player_position + player_velocity;
	auto index_x = static_cast<int>(m_player.player_left_border( new_pos )) / Config::Block::size;
	auto index_y = static_cast<int>(Config::Window::height - new_pos.y + Config::Player::size.y) / Config::Block::size;
	if ( !block_exists_at( index_y, index_x ) ) {
		return { Collision::NO_BLOCK_UNDER, index_x, index_y };
	}

}

struct BlockCollision Map::check_for_collision_up() const {
	const auto& player_position = m_player.position();
	const auto& player_velocity = m_player.velocity();
	auto new_pos = player_position + player_velocity;
	auto index_x = static_cast<int>(m_player.player_left_border( new_pos ) + 1) / Config::Block::size;
	auto index_y = static_cast<int>(Config::Window::height - new_pos.y) / Config::Block::size;
	if ( block_exists_at( index_y, index_x ) ) {
	std::cout << "Index of blocking block " << index_x << std::endl;
		return { Collision::BLOCK_ABOVE, index_x, index_y };
	}
	//index_x = static_cast<int>(m_player.player_right_border( new_pos )) / Config::Block::size;
	//if ( block_exists_at( index_y, index_x ) ) {
	//	return { Collision::BLOCK_ABOVE, index_x, index_y };
	//}
	return {Collision::NO_COLLISION, 0, 0};
}

struct BlockCollision Map::check_for_collision_right() const {
	const auto& player_position = m_player.position();
	const auto& player_velocity = m_player.velocity();
	auto new_pos = player_position + player_velocity;

	// index_x, index_y represent coordinations in our map
	auto index_x = static_cast< int >( m_player.player_left_border(player_position) ) / Config::Block::size;
	auto index_y = static_cast<int>(Config::Window::height - player_position.y - Config::Player::size.y) / 32;
	std::cout << index_x << " " << index_y << std::endl;
	bool above_ground = index_y > 0 ? true : false;


	index_x = static_cast<int>(m_player.player_right_border( new_pos )) / Config::Block::size;
	if ( block_exists_at( index_y, index_x ) ) {
		if ( !m_blocks[ index_y ][ index_x ]->pickable() ) {
			return { Collision::BLOCK_COLLISION, index_x, index_y };
		}
		else {
			return { Collision::BLOCK_PICKABLE, index_x, index_y };
		}
	}


	// fall from block, consider left border of the player
	index_x = static_cast<int>(m_player.player_left_border( new_pos )) / Config::Block::size;
	auto index_x_2 = static_cast<int>(m_player.player_right_border( new_pos )) / Config::Block::size;
	if ( !m_player.is_jumping() && above_ground ) {
		//index_x = static_cast<int>(m_player.player_right_border( new_pos ));
		if ( !block_exists_at( index_y - 1, index_x ) && !block_exists_at( index_y - 1, index_x_2 ) ) {
			return { Collision::NO_BLOCK_UNDER, index_x, index_y - 1 };
		}

		if ( block_exists_at( index_y - 1, index_x ) && m_blocks[ index_y - 1 ][ index_x ]->pickable() ) {
			return { Collision::BLOCK_UNDER_PICKABLE, index_x, index_y - 1 };
		}
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
}

void Map::check_for_destroying( const sf::Vector2i& pos ) {
	auto index_x = static_cast< int >(pos.x) / Config::Block::size;
	auto index_y = static_cast< int >(Config::Window::height - pos.y) / Config::Block::size;
	if ( block_exists_at( index_y, index_x ) ) {
		destroy_block( index_y, index_x );
	}
}

void Map::destroy_block( int row, int col ) {
	m_blocks[ row ][ col ].reset();
}