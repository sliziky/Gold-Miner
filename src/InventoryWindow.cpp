#include "InventoryWindow.h"
#include "TextureHolder.h"

#include "Config.h"

InventoryWindow::InventoryWindow() {
    set_size( Config::Inventory::window_size );
    set_fill_color( Config::Inventory::fill_color );
    set_outline_color( Config::Inventory::outline_color );
    set_outline_thickness( Config::Inventory::thickness );
}

void InventoryWindow::set_size( const sf::Vector2f& size ) {
    m_window.setSize( size );
}

void InventoryWindow::set_fill_color( const sf::Color& color ) {
    m_window.setFillColor( color );
}

void InventoryWindow::set_outline_color( const sf::Color& color ) {
    m_window.setOutlineColor( color );
}

void InventoryWindow::set_outline_thickness( float thickness ) {
    m_window.setOutlineThickness( thickness );
}

void InventoryWindow::set_position( const sf::Vector2f& pos ) {
    m_window.setPosition( pos );
}