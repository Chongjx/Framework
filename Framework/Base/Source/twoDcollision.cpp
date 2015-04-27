#include "twoDcollision.h"

void check2DCollision(twoDhitbox &user, vector<twoDhitbox> &target, bool &collide, string &boxName)
{
	bool side1, side2, side3, side4 = true;

	for (int i = 0; i < target.size(); ++i)
	{
		if (user.getOrigin().x < target[i].getOrigin().x + target[i].getHalfLength() &&
			user.getOrigin().x + user.getHalfLength() > target[i].getOrigin().x &&
			user.getOrigin().y < target[i].getOrigin().y + target[i].getHalfWidth() &&
			user.getOrigin().y + user.getHalfWidth() > target[i].getOrigin().y)

		{
			collide = true;
			boxName = target[i].getName();
			break;
		}
	}
}

void check2DCollision(twoDhitbox &user, twoDhitbox &target, bool &collide, string &boxName)
{
	if (user.getOrigin().x < target.getOrigin().x + target.getLength() &&
		user.getOrigin().x + user.getLength() > target.getOrigin().x &&
		user.getOrigin().y < target.getOrigin().y + target.getWidth() &&
		user.getWidth() + user.getOrigin().y > target.getOrigin().y)

	{
		collide = true;
		boxName = target.getName();
	}
}

void check2DCollision(Vector2 &user, vector<twoDhitbox> &target, bool &collide, string &boxName)
{
	for (int i = 0; i < target.size(); ++i)
	{
		if (user.x < target[i].getOrigin().x + target[i].getLength() &&
			user.x > target[i].getOrigin().x &&
			user.y < target[i].getOrigin().y + target[i].getWidth() &&
			user.y > target[i].getOrigin().y)

		{
			collide = true;
			boxName = target[i].getName();
		}
	}
}

void check2DCollision(Vector2 &user, twoDhitbox &target, bool &collide, string &boxName)
{
	if (user.x < target.getOrigin().x + target.getLength() &&
		user.x > target.getOrigin().x &&
		user.y < target.getOrigin().y + target.getWidth() &&
		user.y > target.getOrigin().y)

	{
		collide = true;
		boxName = target.getName();
	}
}