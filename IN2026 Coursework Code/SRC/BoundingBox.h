#ifndef __BOUNDINGBOX_H__
#define __BOUNDINGBOX_H__

#include "GameUtil.h"
#include "GameObjectType.h"
#include "BoundingShape.h"
using namespace std;

class BoundingBox : public BoundingShape
{
public:

	BoundingBox() : BoundingShape("BoundingShape"), mWidth(0), mHeight(0){}
	BoundingBox(shared_ptr<GameObject> o, float w, float h) : BoundingShape("BoundingBox", o), mWidth(w), mHeight(h){}

	bool CollisionTest(shared_ptr<BoundingShape> bs);

	void SetSize(float w, float h) { mWidth = w; mHeight = h; }
	float GetWidth() { return mWidth; }
	float GetHeight() { return mHeight; }

protected:
	float mWidth;
	float mHeight;
};


#endif
