#include "GameObjectFactory.h"
#include "Block.h"

std::unique_ptr< Block > GameObjectFactory::create_grass( const sf::Vector2f& pos ) const {
	sf::Vector2f tmp = pos;
	tmp.x = (int)tmp.x / 32 * 32;
	tmp.y = (int)tmp.y / 32 * 32;
	return std::make_unique< Block >( "dirt_grass.png", tmp );
}

std::unique_ptr< Block > GameObjectFactory::create_dirt( const sf::Vector2f& pos ) const {
	sf::Vector2f tmp = pos;
	tmp.x = (int)tmp.x / 32 * 32;
	tmp.y = (int)tmp.y / 32 * 32;
	return std::make_unique< Block >( "dirt.png", tmp );
}

std::unique_ptr< Block > GameObjectFactory::create_stone( const sf::Vector2f& pos ) const {
	sf::Vector2f tmp = pos;
	tmp.x = (int)tmp.x / 32 * 32;
	tmp.y = (int)tmp.y / 32 * 32;
	return std::make_unique< Block >( "stone.png", tmp );
}

std::unique_ptr< Block > GameObjectFactory::create_sand( const sf::Vector2f& pos ) const {
	sf::Vector2f tmp = pos;
	tmp.x = (int)tmp.x / 32 * 32;
	tmp.y = (int)tmp.y / 32 * 32;
	return std::make_unique< Block >( "sand.png", tmp );
}
std::unique_ptr< Block > GameObjectFactory::create_mushroom( const sf::Vector2f& pos ) const {
	sf::Vector2f tmp = pos;
	tmp.x = (int)tmp.x / 32 * 32;
	tmp.y = (int)tmp.y / 32 * 32;
	auto mushroom = std::make_unique< Block >( "red_mushroom.png", tmp );
	mushroom->pickable( true );
	return mushroom;
}