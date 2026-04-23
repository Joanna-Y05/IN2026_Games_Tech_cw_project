#include "GameWorld.h"
#include "Ammo.h"
#include "BoundingSphere.h"

// PUBLIC INSTANCE CONSTRUCTORS ///////////////////////////////////////////////

/** Constructor. Bullets live for 2s by default. */
Ammo::Ammo()
	: GameObject("Ammo")
{
}

/** Construct a new bullet with given position, velocity, acceleration, angle, rotation and lifespan. */
Ammo::Ammo(GLVector3f p, GLVector3f v, GLVector3f a, GLfloat h, GLfloat r)
	: GameObject("Ammo", p, v, a, h, r)
{
}

/** Copy constructor. */
Ammo::Ammo(const Ammo& b)
	: GameObject(b)
{
}

/** Destructor. */
Ammo::~Ammo(void)
{
}

// PUBLIC INSTANCE METHODS ////////////////////////////////////////////////////

/** Update bullet, removing it from game world if necessary. */
void Ammo::Update(int t)
{
	// Update position/velocity
	GameObject::Update(t);

/* change this section to be if it collides with a wall
	// If time to live is zero then remove bullet from world
	if (mTimeToLive == 0) {
		if (mWorld) mWorld->FlagForRemoval(GetThisPtr());
	}
	*/

}

bool Ammo::CollisionTest(shared_ptr<GameObject> o)
{
	if (o->GetType() != GameObjectType("Enemy") || (o->GetType() != GameObjectType("Wall"))) return false;
	if (mBoundingShape.get() == NULL) return false;
	if (o->GetBoundingShape().get() == NULL) return false;
	return mBoundingShape->CollisionTest(o->GetBoundingShape());
}

void Ammo::OnCollision(const GameObjectList& objects)
{
	mWorld->FlagForRemoval(GetThisPtr());
}
