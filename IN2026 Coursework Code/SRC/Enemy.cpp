#include <stdlib.h>
#include "GameUtil.h"
#include "Enemy.h"
#include "BoundingShape.h"
#include "Character.h"

Enemy::Enemy(void) : GameObject("Enemy")
{
	//mAngle = rand() % 360;
	mRotation = 0; // rand() % 90;
	mPosition.x = rand() / 2;
	mPosition.y = rand() / 2;
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
				DestroyEnemy();
			}
			else {
				DowngradeEnemy();
			}
		}

		//for collisions with player
		if (obj->GetType().GetTypeName() == "Character") {
			Character* temp = (Character*)obj.get();

			temp->TakeDamage(currentPower);
		}
		//for collisions with wall


	}
}

void Enemy::DestroyEnemy() {
	mWorld->FlagForRemoval(GetThisPtr());
}

void Enemy::SetFollowRadius() {}

void Enemy::SetEnemyType(int type) {
	if (type == 1) {
		this->SetScale(enemyScales[0]);
		currentPower = enemyPowers[0];
	}
	if (type == 2) {
		this->SetScale(enemyScales[1]);
		currentPower = enemyPowers[1];
	}
	if (type == 3) {
		this->SetScale(enemyScales[2]);
		currentPower = enemyPowers[2];
	}
}

