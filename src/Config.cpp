
#include <chrono>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Config.h"

using namespace std::chrono_literals;

//PLAYER
const sf::Vector2f Config::Player::scale = { 1.f, 1.f };
const sf::Vector2f Config::Player::acceleration = { 3.f, 8.f };
const uint8_t Config::Player::sheet_size = 64;
const int Config::Player::in_game_size = 64;
const sf::Vector2f Config::Player::size = {32, 64};

const sf::Vector3f Config::Player::from_player_border = { 12, 21, 22 };

//WINDOW
const uint16_t Config::Window::width = 640;
const int Config::Window::height   = 480;
const std::string Config::Window::title = "Gold Miner";

//VIEW
const float Config::View::acceleration = 3.f;

//PATH
const std::string Config::Path::background = "background.png";
const std::string Config::Path::player_sprite = "sheet.png";

//BACKGROUND
const uint16_t Config::Background::width = 640;
const uint16_t Config::Background::height = 480;

//BORDERS
const uint16_t Config::Borders::left = -10;
const uint16_t Config::Borders::right = Config::Background::width - Config::Player::in_game_size;

//PHYSICS
const uint8_t Config::Physics::gravity = 1;

//ANIMATIONS
const float Config::Animations::speed = 1.f;

//TILES
const sf::Vector2f Config::Tiles::scale = { 0.25f, 0.25f };

//MAP
const uint16_t Config::Map::width = 40;
const uint16_t Config::Map::depth = 64;
const uint16_t Config::Map::ground = Config::Window::height - 2 * Config::Player::sheet_size;

//BLOCK
const uint8_t Config::Block::size = 32;

//INVENTORY
const uint8_t Config::Inventory::number_of_windows = 8;
const sf::Vector2f Config::Inventory::window_size = { 32, 32 };
const sf::Color Config::Inventory::fill_color = { 169,169,169 };
const sf::Color Config::Inventory::outline_color = { 105, 105, 105 };
const int Config::Inventory::thickness = 2;