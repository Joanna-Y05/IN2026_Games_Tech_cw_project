#include "GameUtil.h"
#include "GameWorld.h"
#include "Ammo.h"
#include "Character.h"
#include "BoundingSphere.h"

using namespace std;

// PUBLIC INSTANCE CONSTRUCTORS ///////////////////////////////////////////////

/**  Default constructor. */
Character::Character()
	: GameObject("Character"), mSpeed(0)
{
}

/** Construct a spaceship with given position, velocity, acceleration, angle, and rotation. */
Character::Character(GLVector3f p, GLVector3f v, GLVector3f a, GLfloat h, GLfloat r)
	: GameObject("Character", p, v, a, h, r), mSpeed(0)
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
	// Call parent update function
	GameObject::Update(t);
}


/** Render this spaceship. */
void Character::Render(void)
{
	if (mCharacterShape.get() != NULL) mCharacterShape->Render();
	GameObject::Render();
}

/** Fire the rockets. */
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
	// Construct a unit length vector in the direction the spaceship is headed
	GLVector3f character_heading(cos(DEG2RAD * mAngle), sin(DEG2RAD * mAngle), 0);
	character_heading.normalize();
	// Calculate the point at the node of the spaceship from position and heading
	GLVector3f ammo_position = mPosition + (character_heading * 4);
	// Calculate how fast the bullet should travel
	float ammo_speed = 30;
	// Construct a vector for the bullet's velocity
	GLVector3f ammo_velocity = mVelocity + character_heading * ammo_speed;
	// Construct a new bullet
	shared_ptr<GameObject> ammo
	(new Ammo(ammo_position, ammo_velocity, mAcceleration, mAngle, 0, 2000));
	ammo->SetBoundingShape(make_shared<BoundingSphere>(ammo->GetThisPtr(), 2.0f));
	ammo->SetShape(mAmmoShape);
	// Add the new bullet to the game world
	mWorld->AddObject(ammo);

}

bool Character::CollisionTest(shared_ptr<GameObject> o)
{
	if (o->GetType() != GameObjectType("Enemy")) return false;
	if (mBoundingShape.get() == NULL) return false;
	if (o->GetBoundingShape().get() == NULL) return false;
	return mBoundingShape->CollisionTest(o->GetBoundingShape());
}

void Character::OnCollision(const GameObjectList& objects)
{
	mWorld->FlagForRemoval(GetThisPtr());
}