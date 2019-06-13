#pragma once

#include <SFML/Graphics.hpp>

#include <map>

struct TextureHolder {
    //GETTERS
    static const sf::Texture& texture( const std::string& name );
    
    static std::map < std::string, sf::Texture > textures;
};