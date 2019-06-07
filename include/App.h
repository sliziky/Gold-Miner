#pragma once

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Config.h"
#include "..//thirdparty/animation/src/AnimatedSprite.h"

class App {
public:
	App()
		: m_window( sf::VideoMode( Config::Window::width, Config::Window::height ), Config::Window::title, sf::Style::Default )
		, m_view( sf::FloatRect( 0.f, 0.f, 640.f, 480.f ) ) 
	{
		m_window.setFramerateLimit( 60 );
		m_window.setView( m_view );
		m_background.loadFromFile( Config::Path::background );
		m_player.loadFromFile( Config::Path::player_sprite );
		m_sprite_background.setTexture( m_background );
		m_sprite_background.setPosition( 0, 0 );
	}
	void run() {
		sf::Clock frameClock;
		Player player;


		while ( m_window.isOpen() ) {
			sf::Event event;
			while ( m_window.pollEvent( event ) ) {
				if ( event.type == sf::Event::Closed ) {
					m_window.close();
				}
			}
			
			sf::Time frameTime = frameClock.restart();
			
			player.move( m_view );
			player.display_animation( frameTime );
			m_window.clear();
			m_window.setView( m_view );
			m_window.draw( m_sprite_background );
			m_window.draw( player.animations().animated_sprite() );
			m_window.display();
		}
	}
private:
	sf::RenderWindow m_window;
	//Player m_player;
	sf::View m_view;
	sf::Texture m_background;
	sf::Texture m_player;
	sf::Sprite m_sprite_background;
};