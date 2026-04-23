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
	case 'N':
		StartGame();
		break;

	case 'I':
		if (instructionsOpened == false) { instructionsOpened = true; }
		else { instructionsOpened = false; }
		

		if (instructionsOpened == true) {

			mTitleLabel->SetVisible(true);
			mInstructions->SetVisible(true);
			mHintLabel->SetVisible(true);

			mWelcomeLabel->SetVisible(false);
			mNewGameLabel->SetVisible(false);
			mNameLabel->SetVisible(false);
			mQuitLabel->SetVisible(false);
			mInstructionsLabel->SetVisible(false);

		}
		else {

			mWelcomeLabel->SetVisible(true);
			mNewGameLabel->SetVisible(true);
			mNameLabel->SetVisible(true);
			mQuitLabel->SetVisible(true);
			mInstructionsLabel->SetVisible(true);

			mTitleLabel->SetVisible(false);
			mInstructions->SetVisible(false);
			mHintLabel->SetVisible(false);
		}
		break;

	case 'Q':
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



	// WELCOME SCREEN SECTION
	// welcome label
	// Create a new GUILabel and wrap it up in a shared_ptr
	mWelcomeLabel = shared_ptr<GUILabel>(new GUILabel("WELCOME TO MY GAME"));
	// Set the horizontal alignment of the label to GUI_HALIGN_CENTER
	mWelcomeLabel->SetHorizontalAlignment(GUIComponent::GUI_HALIGN_CENTER);
	// Set the vertical alignment of the label to GUI_VALIGN_MIDDLE
	mWelcomeLabel->SetVerticalAlignment(GUIComponent::GUI_VALIGN_MIDDLE);
	// Set the visibility of the label to false (hidden)
	//mWelcomeLabel->SetVisible(true);
	// Add the GUILabel to the GUIContainer  
	shared_ptr<GUIComponent> welcome_component
		= static_pointer_cast<GUIComponent>(mWelcomeLabel);
	mGameDisplay->GetContainer()->AddComponent(welcome_component, GLVector2f(0.5f, 0.8f));

	// new game label
	// Create a new GUILabel and wrap it up in a shared_ptr
	mNewGameLabel = shared_ptr<GUILabel>(new GUILabel("(N) NEW GAME"));
	// Set the horizontal alignment of the label to GUI_HALIGN_CENTER
	mNewGameLabel->SetHorizontalAlignment(GUIComponent::GUI_HALIGN_CENTER);
	// Set the vertical alignment of the label to GUI_VALIGN_MIDDLE
	mNewGameLabel->SetVerticalAlignment(GUIComponent::GUI_VALIGN_MIDDLE);
	//mNewGameLabel->SetVisible(true);
	// Add the GUILabel to the GUIContainer  
	shared_ptr<GUIComponent> newGame_component
		= static_pointer_cast<GUIComponent>(mNewGameLabel);
	mGameDisplay->GetContainer()->AddComponent(newGame_component, GLVector2f(0.5f, 0.5f));

	// instruction label
	// Create a new GUILabel and wrap it up in a shared_ptr
	mInstructionsLabel = shared_ptr<GUILabel>(new GUILabel("(I) INSTRUCTIONS"));
	// Set the horizontal alignment of the label to GUI_HALIGN_CENTER
	mInstructionsLabel->SetHorizontalAlignment(GUIComponent::GUI_HALIGN_CENTER);
	// Set the vertical alignment of the label to GUI_VALIGN_MIDDLE
	mInstructionsLabel->SetVerticalAlignment(GUIComponent::GUI_VALIGN_MIDDLE);
	//mInstructionsLabel->SetVisible(true);
	// Add the GUILabel to the GUIContainer  
	shared_ptr<GUIComponent> instructions_component
		= static_pointer_cast<GUIComponent>(mInstructionsLabel);
	mGameDisplay->GetContainer()->AddComponent(instructions_component, GLVector2f(0.5f, 0.3f));

	// quit label
	// Create a new GUILabel and wrap it up in a shared_ptr
	mQuitLabel = shared_ptr<GUILabel>(new GUILabel("(Q) Quit"));
	// Set the horizontal alignment of the label to GUI_HALIGN_CENTER
	mQuitLabel->SetHorizontalAlignment(GUIComponent::GUI_HALIGN_CENTER);
	// Set the vertical alignment of the label to GUI_VALIGN_MIDDLE
	mQuitLabel->SetVerticalAlignment(GUIComponent::GUI_VALIGN_MIDDLE);
	//mQuitLabel->SetVisible(true);
	// Add the GUILabel to the GUIContainer  
	shared_ptr<GUIComponent> quit_component
		= static_pointer_cast<GUIComponent>(mQuitLabel);
	mGameDisplay->GetContainer()->AddComponent(quit_component, GLVector2f(0.5f, 0.1f));

	// name label
	// Create a new GUILabel and wrap it up in a shared_ptr
	mNameLabel = shared_ptr<GUILabel>(new GUILabel("BY: Joanna Ayeni"));
	// Set the horizontal alignment of the label to GUI_HALIGN_CENTER
	mNameLabel->SetHorizontalAlignment(GUIComponent::GUI_HALIGN_RIGHT);
	// Set the vertical alignment of the label to GUI_VALIGN_MIDDLE
	mNameLabel->SetVerticalAlignment(GUIComponent::GUI_VALIGN_MIDDLE);
	//mNameLabel->SetVisible(true);
	// Add the GUILabel to the GUIContainer  
	shared_ptr<GUIComponent> name_component
		= static_pointer_cast<GUIComponent>(mNameLabel);
	mGameDisplay->GetContainer()->AddComponent(name_component, GLVector2f(1.0f, 1.0f));

	//  INSTRUCTION SECTION

	// title label
	// Create a new GUILabel and wrap it up in a shared_ptr
	mTitleLabel = shared_ptr<GUILabel>(new GUILabel("INSTRUCTIONS"));
	// Set the horizontal alignment of the label to GUI_HALIGN_CENTER
	mTitleLabel->SetHorizontalAlignment(GUIComponent::GUI_HALIGN_CENTER);
	// Set the vertical alignment of the label to GUI_VALIGN_MIDDLE
	mTitleLabel->SetVerticalAlignment(GUIComponent::GUI_VALIGN_TOP);
	mTitleLabel->SetVisible(false);
	// Add the GUILabel to the GUIContainer  
	shared_ptr<GUIComponent> title_component
		= static_pointer_cast<GUIComponent>(mTitleLabel);
	mGameDisplay->GetContainer()->AddComponent(title_component, GLVector2f(0.5f, 0.9f));

	// instuctions
	// Create a new GUILabel and wrap it up in a shared_ptr
	mInstructions = shared_ptr<GUILabel>(new GUILabel("move = arrow keys, shoot = space bar"));
	// Set the horizontal alignment of the label to GUI_HALIGN_CENTER
	mInstructions->SetHorizontalAlignment(GUIComponent::GUI_HALIGN_CENTER);
	// Set the vertical alignment of the label to GUI_VALIGN_MIDDLE
	mInstructions->SetVerticalAlignment(GUIComponent::GUI_VALIGN_MIDDLE);
	mInstructions->SetVisible(false);
	// Add the GUILabel to the GUIContainer  
	shared_ptr<GUIComponent> instr_component
		= static_pointer_cast<GUIComponent>(mInstructions);
	mGameDisplay->GetContainer()->AddComponent(instr_component, GLVector2f(0.5f, 0.5f));

	// hint label
	// Create a new GUILabel and wrap it up in a shared_ptr
	mHintLabel = shared_ptr<GUILabel>(new GUILabel("press (I) to return to the main menu"));
	// Set the horizontal alignment of the label to GUI_HALIGN_CENTER
	mHintLabel->SetHorizontalAlignment(GUIComponent::GUI_HALIGN_CENTER);
	// Set the vertical alignment of the label to GUI_VALIGN_MIDDLE
	mHintLabel->SetVerticalAlignment(GUIComponent::GUI_VALIGN_TOP);
	mHintLabel->SetVisible(false);
	// Add the GUILabel to the GUIContainer  
	shared_ptr<GUIComponent> hint_component
		= static_pointer_cast<GUIComponent>(mHintLabel);
	mGameDisplay->GetContainer()->AddComponent(hint_component, GLVector2f(0.5f, 0.1f));

}
