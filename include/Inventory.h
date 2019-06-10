#pragma once

#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
#include <map>
class Inventory {

public:
	Inventory();

	//GETTERS
	const std::vector< sf::RectangleShape >& inventory() const;
	const sf::RectangleShape* current() const { return m_current; }
	
	//SETTERS
	void set_position( const sf::Vector2f& pos );

	void add_to_inventory();
	void move( int moved_by );
private:
	std::vector< sf::RectangleShape > m_windows;
	sf::RectangleShape* m_current = nullptr;
	int current_pos = 0;
	std::unique_ptr < sf::Texture > tex;
};