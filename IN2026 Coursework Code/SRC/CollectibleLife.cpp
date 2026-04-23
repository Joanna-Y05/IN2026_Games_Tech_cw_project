#include <stdlib.h>
#include "GameUtil.h"
#include "CollectibleLife.h"
#include "BoundingShape.h"
#include "Character.h"

CollectibleLife::CollectibleLife(void) : GameObject("CollectibleLife")
{
	mPosition.x = rand() / 2;
	mPosition.y = rand() / 2;
	mPosition.z = 0.0;
	mVelocity = 0.0f;
	mRotation = 0.0f;
	mAcceleration = 0.0f;
}

CollectibleLife::~CollectibleLife(void)
{
}

bool CollectibleLife::CollisionTest(shared_ptr<GameObject> o)
{
	if (GetType() == o->GetType()) return false;
	if (mBoundingShape.get() == NULL) return false;
	if (o->GetBoundingShape().get() == NULL) return false;
	return mBoundingShape->CollisionTest(o->GetBoundingShape());
}

void CollectibleLife::OnCollision(const GameObjectList& objects)
{

	for (auto obj : objects) {

		if (obj->GetType().GetTypeName() == "Character") {
			mWorld->FlagForRemoval(GetThisPtr());
		}
	}
}