#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include "Weapon.h"

using std::vector;

class Inventory
{
public:
	Inventory(void);
	Inventory(int bagSize);
	~Inventory(void);

	vector<Weapon *> weaponList;
	int m_iSlots;
	int m_iNumWeap;

	Weapon* currentWeapon;
	Weapon* nextWeapon;

	Weapon pistol;
	Weapon rifle;
	Weapon sniper;

	//bool addWeapon(Weapon &newWeapon);
	//void switchWeapon(bool increment);
	//bool removeWeapon(void);
};

#endif