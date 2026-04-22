#ifndef __COLLECTIBLEAMMO_H__
#define __COLLECTIBLEAMMO_H__

#include "Character.h"
#include "GameObject.h"

class CollectibleAmmo : public GameObject
{
public:
	CollectibleAmmo(void);
	~CollectibleAmmo(void);

	bool CollisionTest(shared_ptr<GameObject> o);
	void OnCollision(const GameObjectList& objects);
};

#endif
