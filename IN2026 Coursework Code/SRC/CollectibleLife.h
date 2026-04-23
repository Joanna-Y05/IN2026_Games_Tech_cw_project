#ifndef __COLLECTIBLELIFE_H__
#define __COLLECTIBLELIFE_H__

#include "GameObject.h"

class CollectibleLife : public GameObject
{
public:
	CollectibleLife(void);
	~CollectibleLife(void);

	bool CollisionTest(shared_ptr<GameObject> o);
	void OnCollision(const GameObjectList& objects);
};

#endif