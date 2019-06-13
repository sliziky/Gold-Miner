#pragma once

#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
#include <map>
#include "InventoryWindow.h"
class Inventory {

public:
	Inventory();

	//GETTERS
	const std::vector< InventoryWindow >& inventory() const;
	const InventoryWindow* current_window() const;
	const sf::Texture* current_window_texture() const;
	bool current_window_empty() const;

	//SETTERS
	void set_position( const sf::Vector2f& pos );

	void add_to_inventory( const std::string& name );
	void move( int moved_by );

private:
	std::vector< InventoryWindow > m_windows;
	InventoryWindow* m_current_window = nullptr;
	int current_pos = 0;
};