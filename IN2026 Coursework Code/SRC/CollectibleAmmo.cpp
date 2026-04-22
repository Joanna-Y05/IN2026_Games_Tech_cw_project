#include <stdlib.h>
#include "GameUtil.h"
#include "CollectibleAmmo.h"
#include "BoundingShape.h"
#include "Character.h"

CollectibleAmmo::CollectibleAmmo(void) : GameObject("CollectibleAmmo")
{
	mPosition.x = rand() / 2;
	mPosition.y = rand() / 2;
	mPosition.z = 0.0;
	mVelocity = 0.0f;
	mRotation = 0.0f;
	mAcceleration = 0.0f;
}

CollectibleAmmo::~CollectibleAmmo(void)
{
}

bool CollectibleAmmo::CollisionTest(shared_ptr<GameObject> o)
{
	if (GetType() == o->GetType()) return false;
	if (mBoundingShape.get() == NULL) return false;
	if (o->GetBoundingShape().get() == NULL) return false;
	return mBoundingShape->CollisionTest(o->GetBoundingShape());
}

void CollectibleAmmo::OnCollision(const GameObjectList& objects)
{

	for (auto obj : objects) {

		if (obj->GetType().GetTypeName() == "Character") {

				Character* temp = (Character*)obj.get();
				temp->IncreaseBullets();
				mWorld->FlagForRemoval(GetThisPtr());
		}
	}
}