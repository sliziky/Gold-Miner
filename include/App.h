#pragma once

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Config.h"
#include "..//thirdparty/animation/src/AnimatedSprite.h"
#include <vector>
#include "GameObjectFactory.h"
#include "Map.h"
#include "Inventory.h"
#include <SFML/Audio.hpp>
class App {
public:
	App()
		: m_window( sf::VideoMode( Config::Window::width, Config::Window::height ), Config::Window::title, sf::Style::Default )
		, m_view( sf::FloatRect( 0.f, 0.f, 640.f, 480.f ) ) 
		, m_player( m_view, m_map )
		, m_map( m_player )
	{
		m_window.setFramerateLimit( 60 );
		m_window.setView( m_view );
		m_background.loadFromFile( Config::Path::background );
		m_player_texture.loadFromFile( Config::Path::player_sprite );
		m_sprite_background.setTexture( m_background );
		m_sprite_background.setPosition( 0, 0 );
		//m_music.openFromFile( "music.ogg" );
	}

	void run() {
		// testing row
		m_music.play();
		m_map.generate_map();
		sf::RectangleShape rect;
		while ( m_window.isOpen() ) {
			const auto& map = m_map.map();
			auto mouse_moved = 0;
			sf::Event event;
			while ( m_window.pollEvent( event ) ) {
				if ( event.type == sf::Event::Closed ) {
					m_window.close();
				}
				else if ( event.type == sf::Event::MouseWheelMoved ) {
					mouse_moved = event.mouseWheel.delta;
				}
			}
			
			sf::Time frameTime = m_frame_clock.restart();
			// get input and move player
			m_player.update();


			// draw stuff
			rect.setPosition( m_player.position() );
			rect.setOutlineColor( sf::Color::Blue );
			rect.setOutlineThickness( 3 );
			rect.setFillColor( sf::Color::Transparent );
			rect.setSize( { (float)Config::Player::in_game_size, 
						  (float)Config::Player::in_game_size } );



			m_window.clear();
			m_window.draw( m_sprite_background );
			m_player.display_animation( frameTime );
			m_window.setView( m_view );
			m_window.draw( rect );
			for ( const auto& row : map ) {
				for ( const auto& block : row ) {
					if ( block ) {
						m_window.draw( block->sprite() );
					}
				}
			}
			m_inventory.set_position( {m_view.getCenter()} );
			m_inventory.move( mouse_moved );
			for ( const auto& inventory_window : m_inventory.inventory() ) {
				m_window.draw( inventory_window );
			}
			m_window.draw( m_player.animations().animated_sprite() );
			m_window.display();
			sf::sleep( sf::milliseconds( 5 ) );
		}
	}
private:
	sf::RenderWindow m_window;
	Player m_player;
	sf::View m_view;
	sf::Texture m_background;
	sf::Texture m_player_texture;
	sf::Sprite m_sprite_background;
	std::vector< std::unique_ptr< IGameObject> > m_objects;
	Map m_map;
	Inventory m_inventory;
	GameObjectFactory m_factory;
	sf::Clock m_frame_clock;
	sf::Music m_music;

};