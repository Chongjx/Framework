#include "twoDcollision.h"

void check2DCollision(twoDhitbox &user, vector<twoDhitbox> &target, bool &collide, string &boxName)
{
	for (int i = 0; i < target.size(); ++i)
	{
		if (user.getMiniPoint().x <= target[i].getMaxiPoint().x &&
			user.getMaxiPoint().x >= target[i].getMiniPoint().x &&
			user.getMiniPoint().y <= target[i].getMaxiPoint().y &&
			user.getMaxiPoint().y >= target[i].getMiniPoint().y)

		{
			collide = true;
			boxName = target[i].getName();
			break;
		}
	}
}

void check2DCollision(twoDhitbox &user, twoDhitbox &target, bool &collide, string &boxName)
{
	if (user.getMiniPoint().x <= target.getMaxiPoint().x &&
		user.getMaxiPoint().x >= target.getMiniPoint().x &&
		user.getMiniPoint().y <= target.getMaxiPoint().y &&
		user.getMaxiPoint().y >= target.getMiniPoint().y)

	{
		collide = true;
		boxName = target.getName();
	}
}

void check2DCollision(Vector2 &user, vector<twoDhitbox> &target, bool &collide, string &boxName)
{
	for (int i = 0; i < target.size(); ++i)
	{
		if (user.x <= target[i].getMaxiPoint().x &&
			user.x >= target[i].getMiniPoint().x &&
			user.y <= target[i].getMaxiPoint().y &&
			user.y >= target[i].getMiniPoint().y)

		{
			collide = true;
			boxName = target[i].getName();
		}
	}
}

void check2DCollision(Vector2 &user, twoDhitbox &target, bool &collide, string &boxName)
{
	if (user.x <= target.getMaxiPoint().x &&
		user.x >= target.getMiniPoint().x &&
		user.y <= target.getMaxiPoint().y &&
		user.y >= target.getMiniPoint().y)

	{
		collide = true;
		boxName = target.getName();
	}
}