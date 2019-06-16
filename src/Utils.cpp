#include "Utils.h"
#include <iostream>
#include <initializer_list>
sf::Vector2f Utils::round_position( const sf::Vector2f& position ) {
	return Utils::round_position( static_cast<sf::Vector2i> (position) );
}

sf::Vector2f Utils::round_position( const sf::Vector2i& position ) {
	sf::Vector2f rounded;
	rounded.x = (int)position.x / Config::Block::size * Config::Block::size;
	rounded.y = (int)position.y / Config::Block::size * Config::Block::size;
	return rounded;
}

int Utils::distance( const sf::Vector2f& player_pos, const sf::Vector2i& mouse_pos ) {
	sf::Vector2f left_upper = { player_pos.x, player_pos.y };
	sf::Vector2f right_upper = { player_pos.x + Config::Player::size.x, player_pos.y };
	sf::Vector2f left_down = { player_pos.x, player_pos.y + Config::Player::size.y };
	sf::Vector2f right_down = { player_pos.x + Config::Player::size.x, player_pos.y + Config::Player::size.y };
	sf::Vector2f right_mid = { player_pos.x + Config::Player::size.x, player_pos.y + Config::Player::size.x };
	sf::Vector2f left_mid = { player_pos.x, player_pos.y + Config::Player::size.x };


	sf::Vector2f mouse = Utils::round_position(static_cast<sf::Vector2f>(mouse_pos));
	mouse.x += 16;
	mouse.y += 16;

	auto d1 = std::sqrt( (left_upper.x - mouse.x) * (left_upper.x - mouse.x) + (left_upper.y - mouse.y) * (left_upper.y - mouse.y) );
	auto d2 = std::sqrt( (left_down.x - mouse.x) * (left_down.x - mouse.x) + (left_down.y - mouse.y) * (left_down.y - mouse.y) );
	auto d3 = std::sqrt( (right_upper.x - mouse.x) * (right_upper.x - mouse.x) + (right_upper.y - mouse.y) * (right_upper.y - mouse.y) );
	auto d4 = std::sqrt( (right_down.x - mouse.x) * (right_down.x - mouse.x) + (right_down.y - mouse.y) * (right_down.y - mouse.y) );
	auto d5 = std::sqrt( (right_mid.x - mouse.x) * (right_mid.x - mouse.x) + (right_mid.y - mouse.y) * (right_mid.y - mouse.y) );
	auto d6 = std::sqrt( (left_mid.x - mouse.x) * (left_mid.x - mouse.x) + (left_mid.y - mouse.y) * (left_mid.y - mouse.y) );


	
	float min = std::min( { d1,d2,d3,d4,d5,d6 } );
	//std::cout << min << std::endl;
	//std::cout << (int) min / 32 << std::endl;
	return min / 32;
	//auto x1 = Utils::round_position( player_pos );
	//x1.x /= 32;
	//x1.y /= 32;
	//auto x2 = Utils::round_position( static_cast<sf::Vector2f>(mouse_pos) );
	//x2.x /= 32;
	//x2.y /= 32;

	//sf::Vector2f l;
	//l.x = x1.x - x2.x;
	//l.y = x1.y - x2.y;
	//std::cout << l.x << " " << l.y << std::endl;
	//return static_cast< int > ( std::sqrt( l.x * l.x + l.y * l.y ) );
}

bool Utils::block_within_range( const sf::Vector2f& player_pos, const sf::Vector2i& block_pos, int range ) {
//	std::cout << Utils::distance( player_pos, block_pos ) << std::endl;
	return Utils::distance( player_pos, block_pos ) <= range;
}

sf::Vector2i Mouse::position = {0, 0};