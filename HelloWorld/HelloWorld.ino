#include <MicroView.h>

void setup() {
	uView.begin();				// start MicroView
	uView.clear(PAGE);			// clear page
	uView.print("Hello\nWorld\nMike");	// display HelloWorld
	uView.display();
}

void loop () {}
