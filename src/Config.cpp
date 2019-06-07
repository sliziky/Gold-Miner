
#include <chrono>
#include <SFML/System/Vector2.hpp>
#include <iostream>

#include "Config.h"

using namespace std::chrono_literals;

const sf::Vector2f Config::Player::scale = { 2.f, 2.f };
const sf::Vector2f Config::Player::speed = { 200.f, 100.f };
const uint8_t Config::Player::sheet_size = 32;


const uint16_t Config::Window::width = 640;
const uint16_t Config::Window::height   = 480;
const std::string Config::Window::title = "Gold Miner";

const float Config::View::speed = 3.3f;

const std::string Config::Path::background = "background.png";
const std::string Config::Path::player_sprite = "sheet.png";

const uint16_t Config::Background::width = 1280;
const uint16_t Config::Background::height = 480;

const uint16_t Config::Borders::left = -10;
const uint16_t Config::Borders::right = Config::Background::width - 64;


