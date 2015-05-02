#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include "Weapon.h"

using std::vector;

class Inventory
{
public:
	Inventory(void);
	~Inventory(void);

	vector<Weapon *> weaponList;
	int m_iSlots;

	void removeWeapon(Weapon &oldWeapon);
	void addWeapon(Weapon &newWeapon);

	Weapon* currentWeapon(void);
};

#endif