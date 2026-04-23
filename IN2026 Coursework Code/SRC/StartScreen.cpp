#include "StartScreen.h"

#include "GameUtil.h"
#include "GameSession.h"
#include "IKeyboardListener.h"
#include "GameDisplay.h"

#include "GameWindow.h"
#include "GUILabel.h"
#include "Game.h"

StartScreen::StartScreen(int margc, char* margv[]) : GameSession(argc, argv) {}

StartScreen::~StartScreen(void){}

void StartScreen::OpenScreen() {

	shared_ptr<StartScreen> thisPtr = shared_ptr<StartScreen>(this);

	// Add this as a listener to the world and the keyboard
	mGameWindow->AddKeyboardListener(thisPtr);

	// Create an ambient light to show sprite textures
	GLfloat ambient_light[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat diffuse_light[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
	glEnable(GL_LIGHT0);

	CreateGUI();

	GameSession::Start();
}

void StartScreen::ShowInstructions() {

	// Create an ambient light to show sprite textures
	GLfloat ambient_light[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat diffuse_light[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
	glEnable(GL_LIGHT0);

	CreateGUI();
}

void StartScreen::Stop() {
	GameSession::Stop();
}


void StartScreen::StartGame() {

	Game game(argc, argv);
	// Start the asteroids game
	game.Start();

}

void StartScreen::OnKeyPressed(uchar key, int x, int y)
{
	switch (key)
	{
	case 'n':
		StartGame();
		break;

	case 'i':
		ShowInstructions();
		break;

	case 'q':
		Stop();
		break;
	default:
		break;
	}
}

void StartScreen::OnKeyReleased(uchar key, int x, int y) {}
void StartScreen::OnSpecialKeyPressed(int key, int x, int y){}
void StartScreen::OnSpecialKeyReleased(int key, int x, int y){}

void StartScreen::CreateGUI() {

	// Add a (transparent) border around the edge of the game display
	mGameDisplay->GetContainer()->SetBorder(GLVector2i(10, 10));

	// Create a new GUILabel and wrap it up in a shared_ptr
	mWelcomeLabel = shared_ptr<GUILabel>(new GUILabel("WELCOME TO MY GAME"));
	// Set the horizontal alignment of the label to GUI_HALIGN_CENTER
	mWelcomeLabel->SetHorizontalAlignment(GUIComponent::GUI_HALIGN_CENTER);
	// Set the vertical alignment of the label to GUI_VALIGN_MIDDLE
	mWelcomeLabel->SetVerticalAlignment(GUIComponent::GUI_VALIGN_MIDDLE);
	// Set the visibility of the label to false (hidden)
	mWelcomeLabel->SetVisible(false);
	// Add the GUILabel to the GUIContainer  
	shared_ptr<GUIComponent> welcome_component
		= static_pointer_cast<GUIComponent>(mWelcomeLabel);
	mGameDisplay->GetContainer()->AddComponent(welcome_component, GLVector2f(0.5f, 0.8f));

}
