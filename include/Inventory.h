#pragma once

#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
class Inventory {

public:
	Inventory();

	//GETTERS
	const std::vector< sf::RectangleShape >& inventory() const;
	
	//SETTERS
	void set_position( const sf::Vector2f& pos );
	
	void move( int moved_by );
private:
	std::vector< sf::RectangleShape > m_windows;
	sf::RectangleShape* current = nullptr;
	int current_pos = 0;
};