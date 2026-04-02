#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "GameObject.h"

class Enemy : public GameObject
{
public:
	Enemy(void);
	~Enemy(void);

	bool CollisionTest(shared_ptr<GameObject> o);
	void OnCollision(const GameObjectList& objects);
};

#endif
