#ifndef THREE_D_COLLISION_H
#define THREE_D_COLLISION_H

#include "threeDhitbox.h"
#include <vector>

using std::vector;

void check3DCollision(threeDhitbox &user, vector<threeDhitbox> &target, bool &collide, string &boxName);
void check3DCollision(threeDhitbox &user, threeDhitbox &target, bool &collide, string &boxName);

#endif