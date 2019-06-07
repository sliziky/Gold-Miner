#include <SFML/Graphics.hpp>

#include "Player.h"
#include "Config.h"
#include "..//thirdparty/animation/src/AnimatedSprite.h"
#include "Animations.h"
#include "App.h"

int main() {
	App app;
	try {
		app.run();
	}
	catch ( const std::exception& exc ) {
		std::cerr << "Error " << exc.what() << '\n';
	}
	return 0;
}