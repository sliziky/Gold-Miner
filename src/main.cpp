#include <SFML/Graphics.hpp>

#include "Player.h"
#include "Config.cpp"

int main() {
	sf::RenderWindow window( sf::VideoMode( Config::Window::width, Config::Window::height ), Config::Window::title, sf::Style::Titlebar | sf::Style::Default );


	while ( window.isOpen() ) {
		sf::Event event;
		while ( window.pollEvent( event ) ) {
			if ( event.type == sf::Event::Closed )
				window.close();
		}
		window.clear();
		window.display();
	}

	return 0;
}