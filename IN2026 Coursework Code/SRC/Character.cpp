#include "GameUtil.h"
#include "GameWorld.h"
#include "Ammo.h"
#include "Character.h"
#include "BoundingSphere.h"
#include <iostream>

using namespace std;

// PUBLIC INSTANCE CONSTRUCTORS ///////////////////////////////////////////////

/**  Default constructor. */
Character::Character()
	: GameObject("Character"), mSpeed(0)
{
}

/** Construct a spaceship with given position, velocity, acceleration, angle, and rotation. */
Character::Character(GLVector3f p, GLVector3f v, GLVector3f a, GLfloat h, GLfloat r)
	: GameObject("Character", p, v, a, h, r), mSpeed(0), mMaxBullets(0)
{
}

/** Copy constructor. */
Character::Character(const Character& s)
	: GameObject(s), mSpeed(0)
{
}

/** Destructor. */
Character::~Character(void)
{
}

// PUBLIC INSTANCE METHODS ////////////////////////////////////////////////////

/** Update this spaceship. */
void Character::Update(int t)
{
	mPrevPosition = mPosition;
	// Call parent update function
	GameObject::Update(t);
}


/** Render this spaceship. */
void Character::Render(void)
{
	if (mCharacterShape.get() != NULL) mCharacterShape->Render();
	GameObject::Render();
}

/** move. */
void Character::MoveVertical(float t)
{
	mSpeed = t;
	mVelocity.y = mSpeed * cos(DEG2RAD);
}

void Character::MoveHorizontal(float t)
{
	mSpeed = t;
	mVelocity.x = mSpeed * cos(DEG2RAD);

}

/** Set the rotation. */
void Character::Rotate(float r)
{
	mRotation = r;
}

/** Shoot a bullet. */
void Character::Shoot(void)
{
	// Check the world exists
	if (!mWorld) return;

	//first checks if ammo is available
	if (mBullets > 0) {

		// Construct a unit length vector in the direction the spaceship is headed
		GLVector3f dirVec;
		GLfloat aAngle;

		switch (mDirection) {
		case LEFT:
			dirVec = GLVector3f(-1.0f, 0.0f, 0.0f);
			aAngle = 0;
			break;

		case RIGHT:
			dirVec = GLVector3f(1.0f, 0.0f, 0.0f);
			aAngle = 180;
			break;

		case UP:
			dirVec = GLVector3f(0.0f, 1.0f, 0.0f);
			aAngle = 90;
			break;

		case DOWN:
			dirVec = GLVector3f(0.0f, -1.0f, 0.0f);
			aAngle = 270;
			break;
		}


		// Calculate the point at the node of the spaceship from position and heading
		GLVector3f ammo_position = mPosition;


		// Calculate how fast the bullet should travel
		float ammo_speed = 30;

		// Construct a vector for the bullet's velocity
		GLVector3f ammo_velocity = GLVector3f(
			dirVec.x * ammo_speed,
			dirVec.y * ammo_speed,
			dirVec.z * ammo_speed
		);


		// Construct a new bullet
		shared_ptr<GameObject> ammo
		(new Ammo(ammo_position, ammo_velocity, mAcceleration, aAngle, 0));
		ammo->SetBoundingShape(make_shared<BoundingSphere>(ammo->GetThisPtr(), 2.0f));
		ammo->SetShape(mAmmoShape);
		// Add the new bullet to the game world
		mWorld->AddObject(ammo);

		Character::DecreaseBullets();
	}

}

bool Character::CollisionTest(shared_ptr<GameObject> o)
{
	if (o->GetType() != GameObjectType("Enemy") || o->GetType() != GameObjectType("Wall")) return false;
	if (mBoundingShape.get() == NULL) return false;
	if (o->GetBoundingShape().get() == NULL) return false;
	return mBoundingShape->CollisionTest(o->GetBoundingShape());
}

void Character::OnCollision(const GameObjectList& objects)
{
	//mWorld->FlagForRemoval(GetThisPtr()); //this would delete the player which i do not want anymore but kept for reference in case i need this functionality

	
	for (auto obj : objects) {
		//collisions with walls
		if (obj->GetType().GetTypeName() == "Wall") {

			//for x axis
			if (mPosition.x != mPrevPosition.x) {
				mPosition.x = mPrevPosition.x;
				mVelocity.x = 0;
			}

			//for y axis
			if (mPosition.y != mPrevPosition.y) {
				mPosition.y = mPrevPosition.y;
				mVelocity.y = 0;
			}

			break;
		}
		

		//collisions with enemies

		//colliions with bullet items
	}
	

}