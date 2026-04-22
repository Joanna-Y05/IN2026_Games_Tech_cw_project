#include <stdlib.h>
#include "GameUtil.h"
#include "Wall.h"
#include "BoundingBox.h"
#include "GameWorld.h"

using namespace std;

Wall::Wall(void) : GameObject("Wall") {
	mVelocity = GLVector3f(0,0,0);
	mRotation = 0.0f;
	mAcceleration = GLVector3f(0, 0, 0);
}

Wall::~Wall(void){}

bool Wall::CollisionTest(shared_ptr<GameObject> o) {
	if (GetType() == o->GetType()) return false;
	if (mBoundingShape.get() == NULL) return false;
	if (o->GetBoundingShape().get() == NULL) return false;
	return mBoundingShape->CollisionTest(o->GetBoundingShape());
}

void Wall::OnCollision(const GameObjectList& objects) {

}