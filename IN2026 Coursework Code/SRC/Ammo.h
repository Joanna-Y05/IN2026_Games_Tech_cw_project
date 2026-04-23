#ifndef __AMMO_H__
#define __AMMO_H__

#include "GameUtil.h"
#include "GameObject.h"

class Ammo : public GameObject
{
public:
	Ammo();
	Ammo(GLVector3f p, GLVector3f v, GLVector3f a, GLfloat h, GLfloat r);
	Ammo(const Ammo& b);
	virtual ~Ammo(void);

	virtual void Update(int t);

	//void SetTimeToLive(int ttl) { mTimeToLive = ttl; }
	//int GetTimeToLive(void) { return mTimeToLive; }

	bool CollisionTest(shared_ptr<GameObject> o);
	void OnCollision(const GameObjectList& objects);


protected:
	//int mTimeToLive;
	float mSpeed;
};


#endif
