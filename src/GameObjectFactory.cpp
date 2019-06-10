#include "GameObjectFactory.h"
#include "Block.h"

std::unique_ptr< Block > GameObjectFactory::create_grass( const sf::Vector2f& pos ) const {
	return std::make_unique< Block >( "dirt_grass.png", pos );
}

std::unique_ptr< Block > GameObjectFactory::create_dirt( const sf::Vector2f& pos ) const {
	return std::make_unique< Block >( "dirt.png", pos );
}

std::unique_ptr< Block > GameObjectFactory::create_stone( const sf::Vector2f& pos ) const {
	return std::make_unique< Block >( "stone.png", pos );
}

std::unique_ptr< Block > GameObjectFactory::create_sand( const sf::Vector2f& pos ) const {
	return std::make_unique< Block >( "sand.png", pos );
}
std::unique_ptr< Block > GameObjectFactory::create_mushroom( const sf::Vector2f& pos ) const {
	auto mushroom = std::make_unique< Block >( "red_mushroom.png", pos );
	mushroom->pickable( true );
	return mushroom;
}