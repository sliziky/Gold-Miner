#include "Inventory.h"
#include "Config.h"
#include "Textures.h"


Inventory::Inventory() {
	m_windows.resize( Config::Inventory::number_of_windows );
	for ( int i = 0; i < Config::Inventory::number_of_windows; ++i ) {
		m_windows[ i ].setSize( Config::Inventory::window_size );
		m_windows[ i ].setFillColor( Config::Inventory::fill_color );
		m_windows[ i ].setOutlineColor( Config::Inventory::outline_color );
		m_windows[ i ].setOutlineThickness( Config::Inventory::thickness );
	}

	// current chosen window
	m_current = &m_windows[ current_pos ];
	m_current->setOutlineColor( sf::Color::Red );
	
	// currently working only "dirt" texture
	tex = std::make_unique<sf::Texture>();
	tex->loadFromFile( "dirt.png" );

}
const std::vector< sf::RectangleShape >& Inventory::inventory() const {
	return m_windows;
}

void Inventory::set_position( const sf::Vector2f& pos ) {
	for ( int i = 0; i < Config::Inventory::number_of_windows; ++i ) {
		m_windows[ i ].setPosition( { pos.x + i * 42 - Config::Window::width / 4 , 10.f } );
	}
}

void Inventory::add_to_inventory() {
	m_current->setTexture( tex.get() );
}

void Inventory::move( int moved_by ) {
	// move through inventory by moved_by "blocks"
	if ( moved_by == 0 ) return;
	current_pos += moved_by;

	// if we are on last window, go to first
	if ( current_pos == Config::Inventory::number_of_windows ) { current_pos = 0; }
	// if we are on first, go to last
	if ( current_pos == -1 ) { current_pos = 7; }

	// set old window to "normal"
	m_current->setOutlineThickness( Config::Inventory::thickness );
	m_current->setOutlineColor( Config::Inventory::outline_color );
	m_current = &m_windows[ current_pos ];
	// update new window
	m_current->setOutlineThickness( 5 );
	m_current->setOutlineColor( sf::Color::Red );

}

