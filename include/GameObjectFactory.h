#pragma once

#include <memory> 
#include <SFML/Graphics.hpp>
#include "Block.h"

class GameObjectFactory {
public:
	std::unique_ptr< Block > create_dirt( const sf::Vector2f& pos ) const;
	std::unique_ptr< Block > create_grass( const sf::Vector2f& pos ) const;
	std::unique_ptr< Block > create_stone( const sf::Vector2f& pos ) const;
	std::unique_ptr< Block > create_sand( const sf::Vector2f& pos ) const;

private:

};