/******************************************************************************/
/*!
\file	twoDcollision.h
\author Jun Xiang
\brief
Checks for collision in 2D spcae
*/
/******************************************************************************/
#ifndef TWO_D_COLLISION_H
#define TWO_D_COLLISION_H

#include "twoDhitbox.h"
#include <vector>

using std::vector;

void check2DCollision(twoDhitbox &user, vector<twoDhitbox> &target, bool &collide, string &boxName);
void check2DCollision(twoDhitbox &user, twoDhitbox &target, bool &collide, string &boxName);
void check2DCollision(Vector2 &user, vector<twoDhitbox> &target, bool &collide, string &boxName);
void check2DCollision(Vector2 &user, twoDhitbox &target, bool &collide, string &boxName);

#endif