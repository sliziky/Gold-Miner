#pragma once

#include <SFML/Graphics.hpp>

class InventoryWindow {
public:
    InventoryWindow();
    InventoryWindow( const std::string& texture );
    void set_size( const sf::Vector2f& size );

    //SETTERS
    void set_fill_color( const sf::Color& );
    void set_outline_color( const sf::Color& );
    void set_outline_thickness( float );
    void set_position( const sf::Vector2f& pos );

    //GETTERS
    const sf::Texture* texture() const { return m_window.getTexture(); }
    void texture( const sf::Texture& texture ) { m_window.setTexture( &texture ); }
    const sf::RectangleShape& window() const { return m_window; }

private:
    sf::RectangleShape m_window;
};