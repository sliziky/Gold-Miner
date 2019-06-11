#include "Block.h"
#include "Config.h"
Block::Block( const std::string& file, const sf::Vector2f& pos )
	: m_position( pos ) 
{
	m_texture.loadFromFile( file );
	
	// default texture is 64x64 but we want 32x32
	m_sprite.setScale( Config::Tiles::scale );
	m_sprite.setTexture( m_texture );
	m_sprite.setPosition( m_position );
}

//GETTERS
const sf::Sprite& Block::sprite() const { return m_sprite; }
const sf::Vector2f& Block::position() const { return m_position; }

bool Block::pickable() const {
	return m_pickable;
}

//SETTERS
void Block::pickable( bool pickable ) {
	m_pickable = pickable;
}

void Block::position( const sf::Vector2f& new_pos ) { 
	m_position = new_pos; 
}


void Block::gameTick() {}