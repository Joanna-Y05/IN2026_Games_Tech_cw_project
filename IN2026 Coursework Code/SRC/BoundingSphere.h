#ifndef __BOUNDINGSPHERE_H__
#define __BOUNDINGSPHERE_H__

#include "GameUtil.h"
#include "GameObjectType.h"
#include "BoundingShape.h"
#include "BoundingBox.h"

class BoundingSphere : public BoundingShape
{
public:
	BoundingSphere() : BoundingShape("BoundingSphere"), mRadius(0) {}
	BoundingSphere(shared_ptr<GameObject> o, float r)
		: BoundingShape("BoundingSphere", o), mRadius(r) {}

	bool CollisionTest(shared_ptr<BoundingShape> bs) {

		GLVector3f posA = GetGameObject()->GetPosition();

		if (GetType() == bs->GetType()) {
			BoundingSphere* bsphere = (BoundingSphere*)bs.get();
			GLVector3f pos1 = GetGameObject()->GetPosition();
			GLVector3f pos2 = bsphere->GetGameObject()->GetPosition();
			float distanceSqr = (pos2 - pos1).lengthSqr();
			float collision_distance = GetRadius() + bsphere->GetRadius();
			return (distanceSqr <= pow(collision_distance, 2));
		}
		//section i added for bounding box
		else if (bs->GetType().GetTypeName() == "BoundingBox") {
			BoundingBox* box = (BoundingBox*)bs.get();
			GLVector3f posB = box->GetGameObject()->GetPosition();

			float halfW = box->GetHeight() / 2.0f;
			float halfH = box->GetWidth() / 2.0f;

			//clamp sphere center to box
			float closestX = std::max(posB.x - halfW, std::min(posA.x, posB.x + halfW));
			float closestY = std::max(posB.x - halfH, std::min(posA.y, posB.y + halfH));

			float dx = posA.x - closestX;
			float dy = posA.y - closestY;

			return (dx * dx + dy * dy) <= (mRadius * mRadius);
		}

		return false;
	}

	void SetRadius(float r) { mRadius = r; }
	float GetRadius() { return mRadius; }

protected:
	float mRadius;
};

#endif
