#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "GameObject.h"
#include <array>

class Enemy : public GameObject
{
public:
	Enemy(void);
	~Enemy(void);

	bool CollisionTest(shared_ptr<GameObject> o);
	void OnCollision(const GameObjectList& objects);

	void DestroyEnemy();
	void DowngradeEnemy() { currentType -= 1; SetEnemyType(currentType); };
	void SetFollowRadius();
	void SetEnemyType(int type);
	int GetEnemyType() { return currentType; }




protected:
	float enemyScales[3] = {0.1f, 0.2f, 0.5f};
	int enemyPowers[3] = { 1, 3, 7 };
	int currentType;
	int currentPower;


};

#endif
