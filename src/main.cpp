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