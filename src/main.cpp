#include <SFML/Graphics.hpp>

#include "Player.h"
#include "Config.h"

int main() {
	sf::RenderWindow window( sf::VideoMode( Config::Window::width, Config::Window::height ), Config::Window::title, sf::Style::Default );
	window.setFramerateLimit( 25 );
	Player player;
	sf::Vector2f movement { 0.f, 0.f };
	//TODO basic player movement and draw
	while ( window.isOpen() ) {
		sf::Event event;
		while ( window.pollEvent( event ) ) {
			if ( event.type == sf::Event::Closed ) {
				window.close();
			}
		}
		
		window.clear();
		if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Right ) ) {
			movement.x += 5.f;
			player.move( movement );
			window.draw( player._sprites[i] );
		}
		else {
			window.draw( player._sprites[ 0 ] );
		}
		
		
		window.display();
		// Display window contents on screen
		++i;
		if ( i == 9 ) i = 0;
		
	}

	return 0;
}