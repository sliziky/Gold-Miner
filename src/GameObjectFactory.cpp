#include "GameObjectFactory.h"
#include "Block.h"
#include "Utils.h"
#include "TextureHolder.h"

//ANY
std::unique_ptr< Block > GameObjectFactory::create_block( const sf::Texture& name, const sf::Vector2f& pos ) const {
	return std::make_unique< Block >( name, pos );
}

//GRASS
std::unique_ptr< Block > GameObjectFactory::create_grass( const sf::Vector2f& pos ) const {
	return std::make_unique< Block >( TextureHolder::texture("grass"), Utils::round_position(pos) );
}

//DIRT
std::unique_ptr< Block > GameObjectFactory::create_dirt( const sf::Vector2f& pos ) const {
	return std::make_unique< Block >( TextureHolder::texture("dirt"), Utils::round_position(pos) );
}

//STONE
std::unique_ptr< Block > GameObjectFactory::create_stone( const sf::Vector2f& pos ) const {
	return std::make_unique< Block >( TextureHolder::texture("stone"), Utils::round_position(pos) );
}

//SAND
std::unique_ptr< Block > GameObjectFactory::create_sand( const sf::Vector2f& pos ) const {
	return std::make_unique< Block >( TextureHolder::texture("sand"), Utils::round_position(pos) );
}
// std::unique_ptr< Block > GameObjectFactory::create_mushroom( const sf::Vector2f& pos ) const {
// 	auto mushroom = std::make_unique< Block >( "red_mushroom.png", Utils::round_position(pos) );
// 	mushroom->pickable( true );
// 	return mushroom;
// }