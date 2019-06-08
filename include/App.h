#pragma once

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Config.h"
#include "..//thirdparty/animation/src/AnimatedSprite.h"
#include <vector>
#include "GameObjectFactory.h"
#include "Map.h"
class App {
public:
	App()
		: m_window( sf::VideoMode( Config::Window::width, Config::Window::height ), Config::Window::title, sf::Style::Default )
		, m_view( sf::FloatRect( 0.f, 0.f, 640.f, 480.f ) ) 
		, m_player( m_view )
	{
		m_window.setFramerateLimit( 60 );
		m_window.setView( m_view );
		m_background.loadFromFile( Config::Path::background );
		m_player_texture.loadFromFile( Config::Path::player_sprite );
		m_sprite_background.setTexture( m_background );
		m_sprite_background.setPosition( 0, 0 );
	}

	void run() {
		sf::Clock frameClock;

		m_map.generate_row();
		while ( m_window.isOpen() ) {
			const auto& map = m_map.map();
			sf::Event event;
			while ( m_window.pollEvent( event ) ) {
				if ( event.type == sf::Event::Closed ) {
					m_window.close();
				}
			}
			
			sf::Time frameTime = frameClock.restart();
			
			m_player.move();
			auto& player_sprite = m_player.animations().animated_sprite();

			m_window.clear();

			m_player.display_animation( frameTime );
			m_window.setView( m_view );
			m_window.draw( m_sprite_background );
			for ( const auto& row : map ) {
				for ( const auto& block : row ) {
					m_window.draw( block->sprite() );
				}
			}
			m_window.draw( m_player.animations().animated_sprite() );
			m_window.display();
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
	GameObjectFactory m_factory;
};