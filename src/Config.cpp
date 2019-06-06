
#include <chrono>
#include <SFML/System/Vector2.hpp>
#include <iostream>

#include "Config.h"

using namespace std::chrono_literals;

const sf::Vector2f Config::Player::scale = { .15f, .15f };

const uint16_t Config::Window::width = 640;
const uint16_t Config::Window::height   = 480;
const std::string Config::Window::title = "Gold Miner";
