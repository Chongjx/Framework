#include "threeDcollision.h"

void check3DCollision(threeDhitbox &user, vector<threeDhitbox> &target, bool &collide, string &boxName)
{
	for (int i = 0; i < target.size(); ++i)
	{
		if (user.getMaxiPoint().x > target[i].getMiniPoint().x &&
			user.getMiniPoint().x < target[i].getMaxiPoint().x &&
			user.getMaxiPoint().y > target[i].getMiniPoint().y &&
			user.getMiniPoint().y < target[i].getMaxiPoint().y &&
			user.getMaxiPoint().z > target[i].getMiniPoint().z &&
			user.getMiniPoint().z < target[i].getMaxiPoint().z)

		{
			collide = true;
			boxName = target[i].getName();
			break;
		}
	}
}

void check3DCollision(threeDhitbox &user, threeDhitbox &target, bool &collide, string &boxName)
{
	if (user.getMaxiPoint().x > target.getMiniPoint().x &&
		user.getMiniPoint().x < target.getMaxiPoint().x &&
		user.getMaxiPoint().y > target.getMiniPoint().y &&
		user.getMiniPoint().y < target.getMaxiPoint().y &&
		user.getMaxiPoint().z > target.getMiniPoint().z &&
		user.getMiniPoint().z < target.getMaxiPoint().z)

	{
		collide = true;
		boxName = target.getName();
	}
}