// Computer Science and Games Technology: Lab Exercise 01

// First we need to include some header files...
#include <windows.h>	// The standard header for Windows applications
#include <time.h>		// The standard header to access time fuctions

#include "GlutSession.h"
#include "StartScreen.h"

// Now we need to perform some Windows magic to stop an extra console
// window from appearing, don't worry about the specifics of this.
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

// Main Function For Bringing It All Together.
int main(int argc, char* argv[])
{
	// Initialise random number generator
	srand((unsigned)time(NULL));
	// Initialise a unique GLUT session
	GlutSession::GetInstance().Init(argc, argv);

	// Create a new asteroids game
	StartScreen screen(argc, argv);
	// Start the asteroids game
	screen.OpenScreen();

	return 0;
}
