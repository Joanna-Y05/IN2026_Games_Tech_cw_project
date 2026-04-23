#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "GameObject.h"
#include <array>
#include "BoundingSphere.h"

class Enemy : public GameObject
{
public:
	Enemy(void);
	~Enemy(void);

	bool CollisionTest(shared_ptr<GameObject> o);
	void OnCollision(const GameObjectList& objects);

	void DowngradeEnemy();
	void SetFollowRadius(float followRadius);
	void SetEnemyType(int type);
	int GetEnemyType() { return currentType; }
	void Update(int t);
	int GetPower() { return currentPower; }
	bool GetWhoKilled() { return KilledByPlayer; }




protected:
	int enemyPowers[3] = { 1, 5, 12 };
	float enemySpeeds[3] = { 10.0f, 20.0f, 30.0f };
	int currentType;
	int currentPower;
	shared_ptr<BoundingSphere> mFollowSphere;
	float mSpeed;
	bool KilledByPlayer = false;


};

#endif
