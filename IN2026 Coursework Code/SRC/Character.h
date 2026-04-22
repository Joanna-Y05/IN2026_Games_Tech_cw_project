#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "GameUtil.h"
#include "GameObject.h"
#include "Shape.h"

enum Direction {
	LEFT,
	RIGHT,
	UP,
	DOWN
};

class Character : public GameObject
{
public:
	Character();
	Character(GLVector3f p, GLVector3f v, GLVector3f a, GLfloat h, GLfloat r);
	Character(const Character& s);
	virtual ~Character(void);

	virtual void Update(int t);
	virtual void Render(void);

	virtual void MoveVertical(float t);
	virtual void MoveHorizontal(float t);

	virtual void Rotate(float r);
	virtual void Shoot(void);

	void SetCharacterShape(shared_ptr<Shape> character_shape) { mCharacterShape = character_shape; }
	void SetAmmoShape(shared_ptr<Shape> ammo_shape) { mAmmoShape = ammo_shape; }

	bool CollisionTest(shared_ptr<GameObject> o);
	void OnCollision(const GameObjectList& objects);
	void SetDirection(Direction dir) { mDirection = dir; }

	void IncreaseBullets() { mBullets++; };
	void DecreaseBullets() { mBullets--; };
	void SetBullets() { mBullets = mMaxBullets; }
	int GetBullets() { return mBullets; }

	void TakeDamage(int damage) { mHealth -= damage; }

private:
	float mSpeed;

	shared_ptr<Shape> mCharacterShape;
	shared_ptr<Shape> mAmmoShape;
	shared_ptr<Animation> mAnim;

	Direction mDirection;
	GLVector3f mPrevPosition;

	//stuff for ammo system
	int mBullets;
	int mMaxBullets = 6;

	//stuff for health system
	int mHealth = 30;

};
#endif
