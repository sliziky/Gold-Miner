#pragma once

#include <SFML/Graphics.hpp>
#include "Config.h"

struct Utils {
    static sf::Vector2f round_position( const sf::Vector2f& position );
};

struct Mouse {
    static sf::Vector2i position;
};
