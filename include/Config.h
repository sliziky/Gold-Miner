#pragma once

#include <chrono>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>

struct Config {
	struct Player {
		static const sf::Vector2f acceleration;
		static const sf::Vector2f scale;
		static const uint8_t sheet_size;
		static const int in_game_size;
		static const sf::Vector3f from_player_border;
		static const sf::Vector2f size;
	};

	struct Window {
		static const uint16_t width;
		static const int height;
		static const std::string title;
	};

	struct View {
		static const float acceleration;
	};

	struct Path {
		static const std::string background;
		static const std::string player_sprite;
	};

	struct Background {
		static const uint16_t width;
		static const uint16_t height;
	};

	struct Borders {
		static const uint16_t left;
		static const uint16_t right;
	};
	struct Physics {
		static const uint8_t gravity;
	};
	struct Animations {
		static const float speed;
	};
	struct Tiles {
		static const sf::Vector2f scale;
	};

	struct Map {
		static const uint16_t ground;
		static const uint16_t width;
		static const uint16_t depth;
	};
	struct Block {
		static const uint8_t size;
	};
	struct Inventory {
		static const uint8_t number_of_windows;
		static const sf::Vector2f window_size;
		static const sf::Color fill_color;
		static const sf::Color outline_color;
		static const int thickness;
	};
};