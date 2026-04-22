#include "GameUtil.h"
#include "GameObjectType.h"
#include "BoundingBox.h"
#include "BoundingSphere.h"
#include "BoundingShape.h"

using namespace std;

bool BoundingBox::CollisionTest(shared_ptr<BoundingShape> bs) {

	GLVector3f posA = GetGameObject()->GetPosition();

	//specifically for boundingspheres can add another for boxes if i add any more box objects
	if (bs->GetType().GetTypeName() == "BoundingSphere") {


		BoundingSphere* bsphere = (BoundingSphere*)bs.get();
		GLVector3f posB = bsphere->GetGameObject()->GetPosition();

		float halfW = mWidth / 2.0f;
		float halfH = mHeight / 2.0f;

		//clamp sphere center to box
		float closestX = std::max(posA.x - halfW, std::min(posB.x, posA.x + halfW));
		float closestY = std::max(posA.y - halfH, std::min(posB.y, posA.y + halfH));

		float dx = posB.x - closestX;
		float dy = posB.y - closestY;

		return (dx * dx + dy * dy) <= (bsphere->GetRadius() * bsphere->GetRadius());
	}

	return false;
}