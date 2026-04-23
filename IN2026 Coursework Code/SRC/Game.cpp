#include "Enemy.h"
#include "Game.h"
#include "Animation.h"
#include "AnimationManager.h"
#include "GameUtil.h"
#include "GameWindow.h"
#include "GameWorld.h"
#include "GameDisplay.h"
#include "Character.h"
#include "BoundingShape.h"
#include "BoundingSphere.h"
#include "BoundingBox.h"
#include "GUILabel.h"
#include "Explosion.h"
#include "Wall.h"
#include "CollectibleAmmo.h"

// PUBLIC INSTANCE CONSTRUCTORS ///////////////////////////////////////////////

/** Constructor. Takes arguments from command line, just in case. */
Game::Game(int argc, char* argv[]) : GameSession(argc, argv)
{
	mLevel = 0;
	mEnemyCount = 0;
}

/** Destructor. */
Game::~Game(void)
{
}

// PUBLIC INSTANCE METHODS ////////////////////////////////////////////////////

/** Start an asteroids game. */
void Game::Start()
{
	// Create a shared pointer for the Asteroids game object - DO NOT REMOVE
	shared_ptr<Game> thisPtr = shared_ptr<Game>(this);

	// Add this class as a listener of the game world
	mGameWorld->AddListener(thisPtr.get());

	// Add this as a listener to the world and the keyboard
	mGameWindow->AddKeyboardListener(thisPtr);

	// Add a score keeper to the game world
	mGameWorld->AddListener(&mScoreKeeper);

	// Add this class as a listener of the score keeper
	mScoreKeeper.AddListener(thisPtr);

	// Create an ambient light to show sprite textures
	GLfloat ambient_light[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat diffuse_light[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
	glEnable(GL_LIGHT0);


	//change these for new assets
	Animation* explosion_anim = AnimationManager::GetInstance().CreateAnimationFromFile("explosion", 64, 1024, 64, 64, "explosion_fs.png");
	Animation* asteroid1_anim = AnimationManager::GetInstance().CreateAnimationFromFile("asteroid1", 128, 8192, 128, 128, "asteroid1_fs.png");
	
	//player anim stuff

	//idle sprites
	Animation* player_anim_idleDown = AnimationManager::GetInstance().CreateAnimationFromFile("char_idleDown", 768, 128, 128, 128, "char_idle_down.png"); 
	Animation* player_anim_idleUp = AnimationManager::GetInstance().CreateAnimationFromFile("char_idleUp", 768, 128, 128, 128, "char_idle_up.png");
	Animation* player_anim_idleRight = AnimationManager::GetInstance().CreateAnimationFromFile("char_idleRight", 768, 128, 128, 128, "char_idle_right.png");
	Animation* player_anim_idleLeft = AnimationManager::GetInstance().CreateAnimationFromFile("char_idleLeft", 768, 128, 128, 128, "char_idle_left.png");

	//movement sprites
	Animation* player_anim_rightMove = AnimationManager::GetInstance().CreateAnimationFromFile("char_moveRight", 768, 128, 128, 128, "char_move_right.png");
	Animation* player_anim_leftMove = AnimationManager::GetInstance().CreateAnimationFromFile("char_moveLeft", 768, 128, 128, 128, "char_move_left.png");
	Animation* player_anim_downMove = AnimationManager::GetInstance().CreateAnimationFromFile("char_moveDown", 768, 128, 128, 128, "char_move_down.png");
	Animation* player_anim_upMove = AnimationManager::GetInstance().CreateAnimationFromFile("char_moveUp", 768, 128, 128, 128, "char_move_up.png");

	//other player sprites
	Animation* player_anim_death = AnimationManager::GetInstance().CreateAnimationFromFile("char_death", 1536, 128, 128, 128, "char_death.png");
	Animation* player_anim_damage = AnimationManager::GetInstance().CreateAnimationFromFile("char_damage", 768, 128, 128, 128, "char_damage.png");

	//wall sprites
	Animation* wall_anim = AnimationManager::GetInstance().CreateAnimationFromFile("wall", 768, 128, 128, 128, "wall.png");

	//bullet sprite
	//Animation* bullet1_anim = AnimationManager::GetInstance().CreateAnimationFromFile("bullet1", 768, 128, 128, 128, "bullet1.png");
	
	// Create a character and add it to the world
	mGameWorld->AddObject(CreateCharacter());

	// Create some asteroids and add them to the world
	CreateEnemies(5);

	CreateWalls();

	//test for instantiating bullets

	SpawnBullet(2);

	//Create the GUI
	CreateGUI();

	// Add a player (watcher) to the game world
	mGameWorld->AddListener(&mPlayer);

	// Add this class as a listener of the player
	mPlayer.AddListener(thisPtr);

	// Start the game
	GameSession::Start();
}

/** Stop the current game. */
void Game::Stop()
{
	// Stop the game
	GameSession::Stop();
}

// PUBLIC INSTANCE METHODS IMPLEMENTING IKeyboardListener /////////////////////

void Game::OnKeyPressed(uchar key, int x, int y)
{
	switch (key)
	{
	case ' ':
		mCharacter->Shoot();
		break;
	default:
		break;
	}
}

void Game::OnKeyReleased(uchar key, int x, int y) {}

void Game::OnSpecialKeyPressed(int key, int x, int y)
{
	shared_ptr<Sprite> Character_sprite1;
	//Character_sprite1->SetLoopAnimation(true);
	Animation* anim_ptr2;

	Direction dir;

	switch (key)
	{
		// If up arrow key is pressed start applying forward thrust
	case GLUT_KEY_UP: 
		mCharacter->MoveVertical(10);
		dir = UP;

		anim_ptr2 = AnimationManager::GetInstance().GetAnimationByName("char_moveUp");
		Character_sprite1 = make_shared<Sprite>(anim_ptr2->GetWidth(), anim_ptr2->GetHeight(), anim_ptr2);
		mCharacter->SetSprite(Character_sprite1);

		mCharacter->SetScale(0.8f);
		mCharacter->SetDirection(dir);

		
		break;

		// 
		// If left arrow key is pressed start rotating anti-clockwise
	case GLUT_KEY_LEFT: 
		mCharacter->MoveHorizontal(-10);
		dir = LEFT;

		anim_ptr2 = AnimationManager::GetInstance().GetAnimationByName("char_moveLeft");
		Character_sprite1 = make_shared<Sprite>(anim_ptr2->GetWidth(), anim_ptr2->GetHeight(), anim_ptr2);
		mCharacter->SetSprite(Character_sprite1);
		mCharacter->SetScale(0.8f);
		mCharacter->SetDirection(dir);
			
			
		break;
		// 
		// If right arrow key is pressed start rotating clockwise
	case GLUT_KEY_RIGHT: 
		mCharacter->MoveHorizontal(10);
		dir = RIGHT;

		anim_ptr2 = AnimationManager::GetInstance().GetAnimationByName("char_moveRight");
		Character_sprite1 = make_shared<Sprite>(anim_ptr2->GetWidth(), anim_ptr2->GetHeight(), anim_ptr2);
		mCharacter->SetSprite(Character_sprite1);
		mCharacter->SetScale(0.8f);
		mCharacter->SetDirection(dir);
		
		break;

	case GLUT_KEY_DOWN:
		mCharacter->MoveVertical(-10);
		dir = DOWN;

		anim_ptr2 = AnimationManager::GetInstance().GetAnimationByName("char_moveDown");
		Character_sprite1 = make_shared<Sprite>(anim_ptr2->GetWidth(), anim_ptr2->GetHeight(), anim_ptr2);
		mCharacter->SetSprite(Character_sprite1);
		mCharacter->SetScale(0.8f);
		mCharacter->SetDirection(dir);

		break;


	default: 

		//if other doesn't work remove this
		anim_ptr2 = AnimationManager::GetInstance().GetAnimationByName("char_idleDown");
		Character_sprite1 = make_shared<Sprite>(anim_ptr2->GetWidth(), anim_ptr2->GetHeight(), anim_ptr2);
		mCharacter->SetSprite(Character_sprite1);
		mCharacter->SetScale(0.8f);
		mCharacter->SetDirection(dir);
		break;
	}
}

void Game::OnSpecialKeyReleased(int key, int x, int y)
{
	shared_ptr<Sprite> Character_sprite2;
	//Character_sprite2->SetLoopAnimation(true);

	Animation* anim_ptr3;

	switch (key)
	{
		// If up arrow key is released stop applying forward thrust
	case GLUT_KEY_UP: 
		mCharacter->MoveVertical(0);

		anim_ptr3 = AnimationManager::GetInstance().GetAnimationByName("char_idleUp");
		Character_sprite2 = make_shared<Sprite>(anim_ptr3->GetWidth(), anim_ptr3->GetHeight(), anim_ptr3);
		mCharacter->SetSprite(Character_sprite2);
		mCharacter->SetScale(0.8f);

	break;
		// 
		// If left arrow key is released stop rotating
	case GLUT_KEY_LEFT: 
		mCharacter->MoveHorizontal(0);

		anim_ptr3 = AnimationManager::GetInstance().GetAnimationByName("char_idleLeft");
		Character_sprite2 = make_shared<Sprite>(anim_ptr3->GetWidth(), anim_ptr3->GetHeight(), anim_ptr3);
		mCharacter->SetSprite(Character_sprite2);
		mCharacter->SetScale(0.8f);
		
		break;
		// 
		// If right arrow key is released stop rotating
	case GLUT_KEY_RIGHT:  
		mCharacter->MoveHorizontal(0);
		
		anim_ptr3 = AnimationManager::GetInstance().GetAnimationByName("char_idleRight");
		Character_sprite2 = make_shared<Sprite>(anim_ptr3->GetWidth(), anim_ptr3->GetHeight(), anim_ptr3);
		mCharacter->SetSprite(Character_sprite2);
		mCharacter->SetScale(0.8f); 
		break;
		// 
		// 

	case GLUT_KEY_DOWN:
		mCharacter->MoveVertical(0);

		anim_ptr3 = AnimationManager::GetInstance().GetAnimationByName("char_idleDown");
		Character_sprite2 = make_shared<Sprite>(anim_ptr3->GetWidth(), anim_ptr3->GetHeight(), anim_ptr3);
		mCharacter->SetSprite(Character_sprite2);
		mCharacter->SetScale(0.8f);

		break;
		// Default case - do nothing
	default:

		anim_ptr3 = AnimationManager::GetInstance().GetAnimationByName("char_idleDown");
		Character_sprite2 = make_shared<Sprite>(anim_ptr3->GetWidth(), anim_ptr3->GetHeight(), anim_ptr3);
		mCharacter->SetSprite(Character_sprite2);
		mCharacter->SetScale(0.8f);

		break;

	}
}


// PUBLIC INSTANCE METHODS IMPLEMENTING IGameWorldListener ////////////////////

void Game::OnObjectRemoved(GameWorld* world, shared_ptr<GameObject> object)
{
	if (object->GetType() == GameObjectType("Enemy"))
	{
		shared_ptr<GameObject> explosion = CreateExplosion();
		explosion->SetPosition(object->GetPosition());
		explosion->SetRotation(object->GetRotation());
		mGameWorld->AddObject(explosion);
		mEnemyCount--;
		if (mEnemyCount <= 0)
		{
			SetTimer(500, START_NEXT_LEVEL);
		}
	}
	if (object->GetType() == GameObjectType("Character"))
	{
		mGameWorld->SetPlayer(NULL);
	}
}

// PUBLIC INSTANCE METHODS IMPLEMENTING ITimerListener ////////////////////////

void Game::OnTimer(int value)
{
	if (value == CREATE_NEW_PLAYER)
	{
		mCharacter->Reset();
		mGameWorld->AddObject(mCharacter);
	}

	if (value == START_NEXT_LEVEL)
	{
		mLevel++;
		int num_Enemies = 5 + 2 * mLevel;
		CreateEnemies(num_Enemies);
	}

	if (value == SHOW_GAME_OVER)
	{
		mGameOverLabel->SetVisible(true);
	}
	if (value == SPAWN_NEW_BULLET) {

		SpawnBullet(2);
	}

}

// PROTECTED INSTANCE METHODS /////////////////////////////////////////////////
shared_ptr<GameObject> Game::CreateCharacter()
{
	// Create a raw pointer to a spaceship that can be converted to
	// shared_ptrs of different types because GameWorld implements IRefCount
	mCharacter = make_shared<Character>();
	mCharacter->SetBoundingShape(make_shared<BoundingSphere>(mCharacter->GetThisPtr(), 5.0f));
	shared_ptr<Shape> Ammo_shape = make_shared<Shape>("Bullet.shape");
	mCharacter->SetAmmoShape(Ammo_shape);

	mCharacter->SetBullets();

	//character stuff
	Animation* anim_ptr = AnimationManager::GetInstance().GetAnimationByName("char_idleDown");
	shared_ptr<Sprite> Character_sprite = make_shared<Sprite>(anim_ptr->GetWidth(), anim_ptr->GetHeight(), anim_ptr);
	mCharacter->SetSprite(Character_sprite);
	mCharacter->SetScale(0.8f);
	// Reset spaceship back to centre of the world
	mCharacter->Reset();

	mGameWorld->SetPlayer(mCharacter);
	mCharacter->RestoreHealth();
	// Return the spaceship so it can be added to the world
	return mCharacter;

}

void Game::CreateEnemies(const uint num_enemies)
{
	mEnemyCount = num_enemies;
	for (uint i = 0; i < num_enemies; i++)
	{
		int num = rand() % 3;

		Animation* anim_ptr = AnimationManager::GetInstance().GetAnimationByName("asteroid1");
		shared_ptr<Sprite> enemy_sprite = make_shared<Sprite>(anim_ptr->GetWidth(), anim_ptr->GetHeight(), anim_ptr);
		enemy_sprite->SetLoopAnimation(true);

		shared_ptr<Enemy> enemy = make_shared<Enemy>();
		enemy->SetBoundingShape(make_shared<BoundingSphere>(enemy->GetThisPtr(), 5.0f));
		enemy->SetSprite(enemy_sprite);
		enemy->SetEnemyType(num);
		enemy->SetFollowRadius(25.0f);
		mGameWorld->AddObject(enemy);
	}
}

void Game::SpawnBullet(int bullets){

	for (int i = 0; i < bullets; i++) {
		shared_ptr<GameObject> bullet = make_shared<CollectibleAmmo>();
		bullet->SetBoundingShape(make_shared<BoundingSphere>(bullet->GetThisPtr(), 4.0f));
		shared_ptr<Shape> Ammo_shape = make_shared<Shape>("Bullet.shape");
		bullet->SetShape(Ammo_shape);
		bullet->SetScale(3.5f);
		mGameWorld->AddObject(bullet);
	}

	SetTimer(10000, SPAWN_NEW_BULLET);
}

void Game::CreateWalls() {

	float roomW = 6000.0f;
	float roomH = 6000.0f;
	float thickness = 5.0f;

	Animation* WallAnim_ptr = AnimationManager::GetInstance().GetAnimationByName("wall");
	shared_ptr<Sprite> wall_spriteH = make_shared<Sprite>(roomW, thickness, WallAnim_ptr);
	shared_ptr<Sprite> wall_spriteV = make_shared<Sprite>(thickness, roomH, WallAnim_ptr);

	//top
	shared_ptr<GameObject> wallT = make_shared<Wall>();
	wallT->SetSprite(wall_spriteH);
	wallT->SetPosition(GLVector3f(0, roomH / 2, 0));
	wallT->SetBoundingShape(make_shared<BoundingBox>(wallT->GetThisPtr(), roomW, thickness));
	mGameWorld->AddObject(wallT);

	//bottom
	shared_ptr<GameObject> wallB = make_shared<Wall>();
	wallB->SetSprite(wall_spriteH);
	wallB->SetPosition(GLVector3f(0, ( - roomH / 2), 0));
	wallB->SetBoundingShape(make_shared<BoundingBox>(wallB->GetThisPtr(), roomW, thickness));
	mGameWorld->AddObject(wallB);

	//left
	shared_ptr<GameObject> wallL = make_shared<Wall>();
	wallL->SetSprite(wall_spriteV);
	wallL->SetPosition(GLVector3f(-(roomW / 2), 0, 0));
	wallL->SetBoundingShape(make_shared<BoundingBox>(wallL->GetThisPtr(), thickness, roomH));
	mGameWorld->AddObject(wallL);

	//right
	shared_ptr<GameObject> wallR = make_shared<Wall>();
	wallR->SetSprite(wall_spriteV);
	wallR->SetPosition(GLVector3f(roomW / 2, 0, 0));
	wallR->SetBoundingShape(make_shared<BoundingBox>(wallR->GetThisPtr(), thickness, roomH));
	mGameWorld->AddObject(wallR);
}

void Game::CreateGUI()
{
	// Add a (transparent) border around the edge of the game display
	mGameDisplay->GetContainer()->SetBorder(GLVector2i(10, 10));


	// Create a new GUILabel and wrap it up in a shared_ptr
	mScoreLabel = make_shared<GUILabel>("Score: 0");
	// Set the vertical alignment of the label to GUI_VALIGN_TOP
	mScoreLabel->SetVerticalAlignment(GUIComponent::GUI_VALIGN_TOP);
	// Add the GUILabel to the GUIComponent  
	shared_ptr<GUIComponent> score_component
		= static_pointer_cast<GUIComponent>(mScoreLabel);
	mGameDisplay->GetContainer()->AddComponent(score_component, GLVector2f(0.0f, 1.0f));

	// Create a new GUILabel and wrap it up in a shared_ptr
	mLivesLabel = make_shared<GUILabel>("Lives: 3");
	// Set the vertical alignment of the label to GUI_VALIGN_BOTTOM
	mLivesLabel->SetVerticalAlignment(GUIComponent::GUI_VALIGN_BOTTOM);
	// Add the GUILabel to the GUIComponent  
	shared_ptr<GUIComponent> lives_component = static_pointer_cast<GUIComponent>(mLivesLabel);
	mGameDisplay->GetContainer()->AddComponent(lives_component, GLVector2f(0.0f, 0.0f));

	// Create a new GUILabel and wrap it up in a shared_ptr
	mGameOverLabel = shared_ptr<GUILabel>(new GUILabel("GAME OVER"));
	// Set the horizontal alignment of the label to GUI_HALIGN_CENTER
	mGameOverLabel->SetHorizontalAlignment(GUIComponent::GUI_HALIGN_CENTER);
	// Set the vertical alignment of the label to GUI_VALIGN_MIDDLE
	mGameOverLabel->SetVerticalAlignment(GUIComponent::GUI_VALIGN_MIDDLE);
	// Set the visibility of the label to false (hidden)
	mGameOverLabel->SetVisible(false);
	// Add the GUILabel to the GUIContainer  
	shared_ptr<GUIComponent> game_over_component
		= static_pointer_cast<GUIComponent>(mGameOverLabel);
	mGameDisplay->GetContainer()->AddComponent(game_over_component, GLVector2f(0.5f, 0.5f));

	//bullets label
	mBulletsLabel = make_shared<GUILabel>("Bullets: 6");
	mBulletsLabel->SetVerticalAlignment(GUIComponent::GUI_VALIGN_TOP);
	shared_ptr<GUIComponent> bullets_component
		= static_pointer_cast<GUIComponent>(mBulletsLabel);
	mGameDisplay->GetContainer()->AddComponent(bullets_component, GLVector2f(0.0f, 0.9f));

	//health label
	mHealthLabel = make_shared<GUILabel>("Health: 20");
	mHealthLabel->SetVerticalAlignment(GUIComponent::GUI_VALIGN_BOTTOM);
	shared_ptr<GUIComponent> health_component
		= static_pointer_cast<GUIComponent>(mHealthLabel);
	mGameDisplay->GetContainer()->AddComponent(health_component, GLVector2f(0.0f, 0.1f));

}

void Game::OnScoreChanged(int score)
{
	// Format the score message using an string-based stream
	std::ostringstream msg_stream;
	msg_stream << "Score: " << score;
	// Get the score message as a string
	std::string score_msg = msg_stream.str();
	mScoreLabel->SetText(score_msg);
}

void Game::OnBulletFired(int bullets_left) {

	// Format the bullet message using an string-based stream
	std::ostringstream msg_stream;
	msg_stream << "bullets: " << bullets_left;
	// Get the score message as a string
	std::string bullet_msg = msg_stream.str();
	mBulletsLabel->SetText(bullet_msg);
}
void Game::OnBulletCollected(int bullets_left) {

	// Format the bullet message using an string-based stream
	std::ostringstream msg_stream;
	msg_stream << "bullets: " << bullets_left;
	// Get the score message as a string
	std::string bullet_msg = msg_stream.str();
	mBulletsLabel->SetText(bullet_msg);
}

void Game::OnPlayerKilled(int lives_left)
{
	shared_ptr<GameObject> explosion = CreateExplosion();
	explosion->SetPosition(mCharacter->GetPosition());
	explosion->SetRotation(mCharacter->GetRotation());
	mGameWorld->AddObject(explosion);

	// Format the lives left message using an string-based stream
	std::ostringstream msg_stream;
	msg_stream << "Lives: " << lives_left;
	// Get the lives left message as a string
	std::string lives_msg = msg_stream.str();
	mLivesLabel->SetText(lives_msg);

	if (lives_left > 0)
	{
		SetTimer(1000, CREATE_NEW_PLAYER);
	}
	else
	{
		SetTimer(500, SHOW_GAME_OVER);
	}
}
void Game::OnPlayerTakeDamage(int health_left) {
	// Format the bullet message using an string-based stream
	std::ostringstream msg_stream;
	msg_stream << "Health: " << health_left;
	// Get the score message as a string
	std::string health_msg = msg_stream.str();
	mHealthLabel->SetText(health_msg);
}

shared_ptr<GameObject> Game::CreateExplosion()
{
	Animation* anim_ptr = AnimationManager::GetInstance().GetAnimationByName("explosion");
	shared_ptr<Sprite> explosion_sprite =
		make_shared<Sprite>(anim_ptr->GetWidth(), anim_ptr->GetHeight(), anim_ptr);
	explosion_sprite->SetLoopAnimation(false);
	shared_ptr<GameObject> explosion = make_shared<Explosion>();
	explosion->SetSprite(explosion_sprite);
	explosion->Reset();
	return explosion;
}
