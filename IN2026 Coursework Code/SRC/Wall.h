#ifndef __WALL_H__
#define __WALL_H__

#include "GameObject.h"
#include "Shape.h"
#include "GameUtil.h"

class Wall : public GameObject
{
public:
	
	Wall(void);
	~Wall(void);

	bool CollisionTest(shared_ptr<GameObject> o);
	void OnCollision(const GameObjectList& objects);
};

#endif
