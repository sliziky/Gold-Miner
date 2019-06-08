
#include <chrono>
#include <SFML/System/Vector2.hpp>
#include <iostream>

#include "Config.h"

using namespace std::chrono_literals;

const sf::Vector2f Config::Player::scale = { 2.f, 2.f };
const sf::Vector2f Config::Player::acceleration = { 3.f, 9.f };
const uint8_t Config::Player::sheet_size = 32;
const uint8_t Config::Player::in_game_size = Config::Player::sheet_size * Config::Player::scale.x;

const uint16_t Config::Window::width = 640;
const uint16_t Config::Window::height   = 480;
const std::string Config::Window::title = "Gold Miner";

const float Config::View::acceleration = 3.f;

const std::string Config::Path::background = "background.png";
const std::string Config::Path::player_sprite = "sheet.png";

const uint16_t Config::Background::width = 1280;
const uint16_t Config::Background::height = 480;

const uint16_t Config::Borders::left = -10;
const uint16_t Config::Borders::right = Config::Background::width - Config::Player::in_game_size;

const uint8_t Config::Physics::gravity = 1;

const float Config::Animations::speed = 0.1f;

const sf::Vector2f Config::Tiles::scale = { 0.25f, 0.25f };

const uint16_t Config::Map::width = 40;
const uint16_t Config::Map::depth = 64;
