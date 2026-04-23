#ifndef __STARTSCREEN_H__
#define __STARTSCREEN_H__

#include "GameUtil.h"
#include "GameSession.h"
#include "IKeyboardListener.h"

#include "GameWindow.h"
#include "GUILabel.h"

class GUILabel;

class StartScreen : public GameSession, public IKeyboardListener
{
public: 

	StartScreen(int argc, char* argv[]);
	virtual ~StartScreen(void);

	virtual void StartGame(void);
	virtual void OpenScreen(void);
	virtual void Stop(void);
	

	// Declaration of IKeyboardListener interface ////////////////////////////////

	void OnKeyPressed(uchar key, int x, int y);
	void OnKeyReleased(uchar key, int x, int y);
	void OnSpecialKeyPressed(int key, int x, int y);
	void OnSpecialKeyReleased(int key, int x, int y);

private:

	//open screen GUI
	shared_ptr<GUILabel> mWelcomeLabel;
	shared_ptr<GUILabel> mNewGameLabel;
	shared_ptr<GUILabel> mInstructionsLabel;
	shared_ptr<GUILabel> mQuitLabel;
	shared_ptr<GUILabel> mNameLabel;

	//instructions screen GUI
	shared_ptr<GUILabel> mTitleLabel;
	shared_ptr<GUILabel> mInstructions;
	shared_ptr<GUILabel> mHintLabel;

	void CreateGUI();
	bool instructionsOpened = false;

	int argc;
	char* argv[];

};


#endif
