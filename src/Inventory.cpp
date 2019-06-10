#include "Inventory.h"
#include "Config.h"
Inventory::Inventory() {
	m_windows.resize( Config::Inventory::number_of_windows );
	for ( int i = 0; i < Config::Inventory::number_of_windows; ++i ) {
		m_windows[ i ].setSize( Config::Inventory::window_size );
		m_windows[ i ].setFillColor( Config::Inventory::fill_color );
		m_windows[ i ].setOutlineColor( Config::Inventory::outline_color );
		m_windows[ i ].setOutlineThickness( Config::Inventory::thickness );
	}
	current = &m_windows[ current_pos ];
	current->setOutlineColor( sf::Color::Red );
}
const std::vector< sf::RectangleShape >& Inventory::inventory() const {
	return m_windows;
}

void Inventory::set_position( const sf::Vector2f& pos ) {
	for ( int i = 0; i < Config::Inventory::number_of_windows; ++i ) {
		m_windows[ i ].setPosition( { pos.x + i * 42 - Config::Window::width / 4 , 10.f } );
	}
}

void Inventory::move( int moved_by ) {
	current_pos += moved_by;
	if ( current_pos == Config::Inventory::number_of_windows ) { current_pos = 0; }
	if ( current_pos == -1 ) { current_pos = 7; }

	current->setOutlineThickness( Config::Inventory::thickness );
	current->setOutlineColor( Config::Inventory::outline_color );
	current = &m_windows[ current_pos ];
	current->setOutlineThickness( 5 );
	current->setOutlineColor( sf::Color::Red );

}