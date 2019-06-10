#include "Block.h"
#include "Config.h"
Block::Block( const std::string& file, const sf::Vector2f& pos )
	: m_position( pos ) 
{
	m_texture.loadFromFile( file );
	m_sprite.setScale( Config::Tiles::scale );
	m_sprite.setTexture( m_texture );
	m_sprite.setPosition( pos );
}

const sf::Sprite& Block::sprite() const { return m_sprite; }

void Block::pickable( bool v ) {
	m_pickable = v;
}

bool Block::pickable() const {
	return m_pickable;
}

void Block::gameTick() {}
void Block::position( const sf::Vector2f& pos ) { m_position = pos; }
const sf::Vector2f& Block::position() const { return m_position; }