#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Config.h"

class Player : public sf::Sprite {

public:
	Player() {
		for ( int i = 0; i < _file_names.size(); ++i ) {
			sf::Texture text;
			text.loadFromFile( _file_names[ i ] );
			text.setSmooth( true );
			_textures.push_back( text );
		}
		for ( int i = 0; i < _file_names.size(); ++i ) {
			sf::Sprite text;
			text.setTexture( _textures[ i ] );
			text.scale( Config::Player::scale );
			_sprites.push_back( text );
		}
	}
	void make_sound() const {
		std::cout << "Good\n";
	}
	std::vector< sf::Sprite > _sprites;
	std::vector< sf::Texture > _textures;
	std::vector< std::string > _file_names = { "Run__001.png","Run__002.png" ,"Run__003.png" ,"Run__004.png" ,"Run__005.png" ,"Run__006.png" ,"Run__007.png" ,"Run__008.png" ,"Run__009.png" };

};