#pragma once

#include <SFML/Graphics.hpp>
#include "IGameObject.h"
#include "Collision.h"
class Block : public IGameObject {
public:
	Block( const sf::Texture& tex, const sf::Vector2f& pos );
	Block( const sf::Texture& tex, const sf::Vector2i& pos );


	

	//GETTERS
	const sf::Sprite& sprite() const override;
	sf::Sprite& sprite() { return m_sprite; }
	const sf::Vector2f& position() const;
	
	//SETTERS
	void position( const sf::Vector2f& pos );
	void pickable( bool v );
	bool pickable() const;
	void gameTick() override;
private:
	sf::Vector2f m_position;
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	bool m_pickable = false;
};

struct BlockCollision {
	BlockCollision( Collision collision, int x, int y )
		: collision( collision )
		, index_x( x )
		, index_y( y ) {}
	Collision collision;
	int index_x;
	int index_y;
};