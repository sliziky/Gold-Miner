#include "Block.h"
#include "Config.h"

#include "TextureHolder.h"

Block::Block( const sf::Texture& texture, const sf::Vector2f& pos )
	: m_position( pos ) 
{

	// default texture is 64x64 but we want 32x32
	m_sprite.setScale( Config::Tiles::scale );
	m_sprite.setTexture( texture );
	m_sprite.setPosition( m_position );
}

Block::Block( const sf::Texture& texture, const sf::Vector2i& pos )
	: Block( texture, static_cast<sf::Vector2f>(pos) ) 
{
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