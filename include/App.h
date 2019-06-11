#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <vector>


#include "Player.h"
#include "Config.h"
#include "..//thirdparty/animation/src/AnimatedSprite.h"
#include "GameObjectFactory.h"
#include "Map.h"
#include "Utils.h"
#include "Inventory.h"
#include "Utils.h"
#include "Input.h"


//debug settings
constexpr int DEBUG = 1;

class App {
public:
	App()
		: m_window( sf::VideoMode( Config::Window::width, Config::Window::height ), Config::Window::title, sf::Style::Default )
		, m_view( sf::FloatRect( 0.f, 0.f, 640.f, 480.f ) ) 
		, m_player( m_view, m_map )
		, m_map( m_player, m_inventory, m_window )
	{

		m_window.setFramerateLimit( 60 );
		m_window.setView( m_view );
		m_player_texture.loadFromFile( Config::Path::player_sprite );

		// adding background
		m_background.loadFromFile( Config::Path::background );
		m_sprite_background.setTexture( m_background );
		m_sprite_background.setPosition( 0, 0 );

		// world creating
		m_map.generate_map();

	}

	void run() {

		sf::RectangleShape rect;
		if constexpr ( DEBUG ) {
			// draw rect around the player
			rect.setOutlineColor( sf::Color::Blue );
			rect.setOutlineThickness( 3 );
			rect.setFillColor( sf::Color::Transparent );
			rect.setSize( { (float)Config::Player::size.x,
						  (float)Config::Player::size.y } );
		}
		m_inventory.add_to_inventory();

		//rectangle around mouse pointer
		sf::RectangleShape mouse_rect;
		mouse_rect.setSize( {32, 32} );
		mouse_rect.setFillColor( sf::Color::Transparent );
		mouse_rect.setOutlineColor( sf::Color::Black );
		mouse_rect.setOutlineThickness( 1 );


		while ( m_window.isOpen() ) {

			// for mouse wheel detection
			auto mouse_moved = 0;


			sf::Event event;
			while ( m_window.pollEvent( event ) ) {
				if ( event.type == sf::Event::Closed ) {
					m_window.close();
				} 

				// moving current inventory window by 1
				else if ( event.type == sf::Event::MouseWheelMoved ) {
					mouse_moved = event.mouseWheel.delta;
				}
			}

			sf::Time frameTime = m_frame_clock.restart();

			check_input();

			m_map.update();
			m_player.update();
			
			//VIEW
			m_window.setView( m_view );

			//CLEAR 
			m_window.clear();

			//DRAWING
			// draw background
			m_window.draw( m_sprite_background );

			// update player animation
			m_player.display_animation( frameTime );

			if constexpr ( DEBUG ) {
				// draw line above the player
				sf::Vertex line[] = { {{m_player.player_left_border( m_player.position() ), m_player.position().y}, sf::Color::Red},
				{{m_player.player_right_border( m_player.position() ), m_player.position().y}, sf::Color::Red} };
				rect.setPosition( m_player.position() );
				m_window.draw( line, 2, sf::Lines );
				m_window.draw( rect );
			}

			// draw player
			m_window.draw( m_player.animations().animated_sprite() );

			sf::Vector2f mouse_pos = { (float)sf::Mouse::getPosition( m_window ).x, (float)sf::Mouse::getPosition( m_window ).y };
			// mouse_pos.x = (int)mouse_pos.x / 32 * 32;
			// mouse_pos.y = (int)mouse_pos.y / 32 * 32;
			// mouse_rect.setPosition( mouse_pos.x, mouse_pos.y );
			mouse_rect.setPosition( Utils::round_position( mouse_pos ) );

			// draw blocks
			draw_blocks();
		
			m_window.draw( mouse_rect );
			// center inventory to the center of the view
			m_inventory.set_position( {m_view.getCenter()} );
			
			// set current inventory window
			m_inventory.move( mouse_moved );

			// draw inventory windows
			draw_inventory();

			//display rendered items
			m_window.display();

			reset_states();
			sf::sleep( sf::milliseconds( 5 ) );
		}
	}

	void draw_blocks() {
		const auto& map = m_map.map();
		for ( const auto& row : map ) {
			for ( const auto& block : row ) {
				if ( block ) {
					m_window.draw( block->sprite() );
				}
			}
		}
	}

	void draw_inventory() {
		for ( const auto& inventory_window : m_inventory.inventory() ) {
			m_window.draw( inventory_window );
		}
	}

	void check_input() {

		// mouse left button
		if ( sf::Mouse::isButtonPressed( sf::Mouse::Left ) ) {
			Mouse::position = sf::Mouse::getPosition( m_window );
			Input::Mouse_Left = true;
		}
		
		// mouse right button
		if ( sf::Mouse::isButtonPressed( sf::Mouse::Right ) ) {
			Mouse::position = sf::Mouse::getPosition( m_window );
			Input::Mouse_Right = true;
		}

		// left key
		if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Left ) ) {
			Input::Left_Key = true;
		}

		// right key
		if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Right ) ) {
			Input::Right_Key = true;
		}

		// up key
		if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Up) ) {
			Input::Up_Key = true;
		}	
	}

	void reset_states() {
		Input::Left_Key = false;
		Input::Right_Key = false;
		Input::Up_Key = false;
		Input::Mouse_Left = false;
		Input::Mouse_Right = false;
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