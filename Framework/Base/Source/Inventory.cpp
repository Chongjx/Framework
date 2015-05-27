#include "Inventory.h"

Inventory::Inventory(void)
{
	m_iSlots = 3;
	currentWeapon = NULL;
	for (int i = 0; i < m_iSlots; ++i)
	{
		Weapon* newWeapon = new Weapon;
		weaponList.push_back(newWeapon);
		++m_iNumWeap;
	}

	currentWeapon = &pistol;
	nextWeapon = &rifle;
}

Inventory::Inventory(int bagSize)
{
	m_iSlots = bagSize;
	currentWeapon = NULL;
	nextWeapon = NULL;
	for (int i = 0; i < m_iSlots; ++i)
	{
		Weapon* newWeapon = new Weapon;
		weaponList.push_back(newWeapon);
		++m_iNumWeap;
	}

	currentWeapon = &pistol;
	nextWeapon = &rifle;
}

Inventory::~Inventory(void)
{
	while(weaponList.size() > 0)
	{
		Weapon *go = weaponList.back();
		delete go;
		weaponList.pop_back();
	}
}

/*
bool Inventory::addWeapon(Weapon &newWeapon)
{
	// there is no space for new weapon
	if (weaponList.size() == m_iSlots)
	{
		return false;
	}

	else
	{
		weaponList.push_back(&newWeapon);
		++m_iNumWeap;
		return true;
	}
}

void Inventory::switchWeapon(bool increment)
{
	if (weaponList.size() > 0)
	{
		// if current weapon is the first weap
		if (currentWeapon == weaponList[0])
		{
			// check to switch next or previous
			if(increment)
			{
				// if weaponList has 2 or more weapon to loop
				if (m_iNumWeap > 1)
				{
					
				}
			}
		}
	}
}

bool Inventory::removeWeapon(void)
{
	for(std::vector<Weapon *>::iterator it = weaponList.begin(); it != weaponList.end(); ++it)
	{
		Weapon* weap = (Weapon *)*it;

		if (weap == currentWeapon)
		{
			delete weap;
			weaponList.pop_back();
			--m_iNumWeap;
			return true;
		}
	}

	return false;
}*/