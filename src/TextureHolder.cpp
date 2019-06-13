#include "TextureHolder.h"
#include <vector>

// initializes a static std::map of textures 
std::map< std::string, sf::Texture > create_texture_map() {
    std::vector< std::string > textures = {
        "dirt", "grass", "sand", "stone"
    };


    std::map< std::string, sf::Texture > map;

    for ( const auto& t : textures ) {
        map[ t ] = sf::Texture();
        map[ t ].loadFromFile( t + ".png" ); 
    }
    return map;
}

// 'textures' is static so we have to initialize it via function 
std::map< std::string, sf::Texture > TextureHolder::textures = create_texture_map();


const sf::Texture& TextureHolder::texture( const std::string& name ) {
    auto texture = textures.find(name);
    return texture->second;
}