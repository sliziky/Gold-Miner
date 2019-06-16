#include "Inventory.h"
#include "Config.h"
#include "TextureHolder.h"

#include <iostream>
Inventory::Inventory() {
	m_windows.resize( Config::Inventory::number_of_windows );

	// current chosen window
	m_current_window = &m_windows[ current_pos ];
	m_current_window->set_outline_color( sf::Color::Red );
	m_current_window->set_outline_thickness( 5 );


}
const std::vector< InventoryWindow >& Inventory::inventory() const {
	return m_windows;
}

const InventoryWindow* Inventory::current_window() const {
	return m_current_window;
}

const sf::Texture* Inventory::current_window_texture() const {
	return m_current_window->texture();
}

bool Inventory::current_window_empty() const {
	return current_window_texture() == nullptr;
}


void Inventory::set_position( const sf::Vector2f& pos ) {
	for ( int i = 0; i < Config::Inventory::number_of_windows; ++i ) {
		m_windows[ i ].set_position( { pos.x + i * 42 - Config::Window::width / 4 , 10.f } );
	}
}

void Inventory::add_to_inventory( const std::string& name ) {
	if ( current_window_empty() ) {
		m_current_window->texture( TextureHolder::texture( name ) );
	}
}

void Inventory::move( int moved_by ) {
	// move through inventory by moved_by "blocks"
	if ( moved_by == 0 ) return;
	current_pos += moved_by;

	// if we are behind last window, go to first
	if ( current_pos >= Config::Inventory::number_of_windows ) { current_pos = 0; }
	// if we are before first, go to last
	if ( current_pos < 0 ) { current_pos = Config::Inventory::number_of_windows - 1; }

	// set old window to "normal"
	m_current_window->set_outline_thickness( Config::Inventory::thickness );
	m_current_window->set_outline_color( Config::Inventory::outline_color );
	m_current_window = &m_windows[ current_pos ];
	// update curren to new window
	m_current_window->set_outline_thickness( 5 );
	m_current_window->set_outline_color( sf::Color::Red );

}

