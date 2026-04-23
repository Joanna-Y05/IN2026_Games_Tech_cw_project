#include <stdlib.h>
#include "GameUtil.h"
#include "Enemy.h"
#include "BoundingShape.h"
#include "Character.h"
#include "BoundingSphere.h"

Enemy::Enemy(void) : GameObject("Enemy")
{
	//mAngle = rand() % 360;
	mRotation = 0; // rand() % 90;
	mPosition.x = rand() / 4;
	mPosition.y = rand() / 4;
	mPosition.z = 0.0;
	mVelocity.x = 10.0 * cos(DEG2RAD * mAngle);
	mVelocity.y = 10.0 * sin(DEG2RAD * mAngle);
	mVelocity.z = 0.0;
}

Enemy::~Enemy(void)
{
}

bool Enemy::CollisionTest(shared_ptr<GameObject> o)
{
	if (GetType() == o->GetType()) return false;
	if (mBoundingShape.get() == NULL) return false;
	if (o->GetBoundingShape().get() == NULL) return false;
	return mBoundingShape->CollisionTest(o->GetBoundingShape());
}

void Enemy::OnCollision(const GameObjectList& objects)
{
	for (auto obj : objects) {

		//for collisions with ammo
		if (obj->GetType().GetTypeName() == "Ammo") {
			
			
			if (GetEnemyType() == 1) {
				mWorld->FlagForRemoval(GetThisPtr());
			}
			else {
				DowngradeEnemy();
			}
			
		}

		//for collisions with player
		if (obj->GetType().GetTypeName() == "Character") {
			mWorld->FlagForRemoval(GetThisPtr());
		}

		//for collisions with wall


	}
}

void Enemy::SetFollowRadius(float followRadius) {

	mFollowSphere = make_shared<BoundingSphere>(GetThisPtr(), followRadius);
}

void Enemy::Update(int t) {
	GameObject::Update(t);

	shared_ptr<GameObject> player = mWorld->GetPlayer();

	if (mFollowSphere->CollisionTest(player->GetBoundingShape())) {
		GLVector3f dir = player->GetPosition() - mPosition;

		float len = sqrt(dir.x * dir.x + dir.y * dir.y);
		if (len > 0) {
			dir.x /= len;
			dir.y /= len;
		}

		mVelocity.x = dir.x * mSpeed;
		mVelocity.y = dir.y * mSpeed;
	}
	else {
		mVelocity.x = 10.0 * cos(DEG2RAD * mAngle);
		mVelocity.y = 10.0 * sin(DEG2RAD * mAngle);
		mVelocity.z = 0.0;
	}
}

void Enemy::SetEnemyType(int type) {
	if (type == 1) {
		this->SetScale(enemyScales[0]);
		currentPower = enemyPowers[0];
		mSpeed = enemySpeeds[0];
	}
	if (type == 2) {
		this->SetScale(enemyScales[1]);
		currentPower = enemyPowers[1];
		mSpeed = enemySpeeds[1];
	}
	if (type == 3) {
		this->SetScale(enemyScales[2]);
		currentPower = enemyPowers[2];
		mSpeed = enemySpeeds[2];
	}
}

