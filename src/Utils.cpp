#include "Utils.h"

sf::Vector2f Utils::round_position( const sf::Vector2f& position ) {
    sf::Vector2f rounded;
	rounded.x = (int)position.x / Config::Block::size * Config::Block::size;
	rounded.y = (int)position.y / Config::Block::size * Config::Block::size;
    return rounded;
}

sf::Vector2i Mouse::position = {0, 0};