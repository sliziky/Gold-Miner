#pragma once

#include <chrono>
#include <SFML/System/Vector2.hpp>

struct Config {
	struct Player {
		//static const sf::Vector2f max_player_speed;
		static const sf::Vector2f scale;
	};

	struct Window {
		static const uint16_t width;
		static const uint16_t height;
		static const std::string title;
	};

};
//
//#include <chrono>
//#include <SFML/System/Vector2.hpp>
//#include <iostream>
//
//using namespace std::chrono_literals;
//
//namespace Config::Window
//{
//	const uint16_t width = 640;
//	const uint16_t height = 480;
//	const std::string title = "Gold Miner";
//}
//
//namespace Config::Player
//{
//	const sf::Vector2f max_player_speed = { 5.f, 5.f };
//	const sf::Vector2f scale = { 15.f, 15.f };
//}
//
//namespace Config::Inventory
//{
//	const uint8_t inventory_on_screen = 8;
//	const uint8_t inventory_total = 128;
//	const uint8_t stack = 32;
//}
//
//namespace Config::Map
//{
//	const uint16_t width = 256;
//	const uint8_t depth = 64;
//}
//
//namespace Config::Tick
//{
//	const uint16_t day_ticks = 24000;
//	const std::chrono::milliseconds tick_time = 5ms;
//}
//
