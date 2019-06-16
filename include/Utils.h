#pragma once

#include <SFML/Graphics.hpp>
#include "Config.h"

struct Utils {
	/**
	  *   \brief Function returns rounded position.
	  *
	  *   Given some (mouse) position we want to round
	  *   the position to get the block we are pointing at
	  *
	  *   \param  A position.
	  *   \return Rounded position
	  *
	  **/
    static sf::Vector2f round_position( const sf::Vector2f& position );
	static sf::Vector2f round_position( const sf::Vector2i& position );


	/**
	  *   \brief Function returns distance between mouse and player.
	  *
	  *   \param  A player position, a mouse position.
	  *   \return Distance between player and mouse
	  *
	  **/
	static int distance( const sf::Vector2f& player_pos, const sf::Vector2i& mouse_pos );

	static bool block_within_range( const sf::Vector2f& player_pos, const sf::Vector2i& mouse_pos,int range );
};

struct Mouse {
    static sf::Vector2i position;
};
