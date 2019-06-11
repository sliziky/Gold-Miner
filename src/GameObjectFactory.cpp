#include "GameObjectFactory.h"
#include "Block.h"
#include "Utils.h"

std::unique_ptr< Block > GameObjectFactory::create_grass( const sf::Vector2f& pos ) const {
	return std::make_unique< Block >( "dirt_grass.png", Utils::round_position(pos) );
}

std::unique_ptr< Block > GameObjectFactory::create_dirt( const sf::Vector2f& pos ) const {
	return std::make_unique< Block >( "dirt.png", Utils::round_position(pos) );
}

std::unique_ptr< Block > GameObjectFactory::create_stone( const sf::Vector2f& pos ) const {
	return std::make_unique< Block >( "stone.png", Utils::round_position(pos) );
}

std::unique_ptr< Block > GameObjectFactory::create_sand( const sf::Vector2f& pos ) const {
	return std::make_unique< Block >( "sand.png", Utils::round_position(pos) );
}
std::unique_ptr< Block > GameObjectFactory::create_mushroom( const sf::Vector2f& pos ) const {
	auto mushroom = std::make_unique< Block >( "red_mushroom.png", Utils::round_position(pos) );
	mushroom->pickable( true );
	return mushroom;
}