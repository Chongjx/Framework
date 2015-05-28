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

	pistol.setWeaponType(WEAP_PISTOL);
	pistol.setName("Desert Eagle");
	pistol.setFireRate(0.25f);
	pistol.setDmg(10.f);
	pistol.setReloadSpeed(1.f);
	pistol.setRecoil(5.f);
	pistol.setMagazineSize(7);
	pistol.setMagazineAmmo(7);
	pistol.setMaxAmmo(49);
	pistol.setAmmo(49);
	pistol.setFire(true);
	pistol.setReload(false);
	pistol.setEmpty(false);
	pistol.setRender(false);

	rifle.setWeaponType(WEAP_RIFLE);
	rifle.setName("P90");
	rifle.setFireRate(0.1f);
	rifle.setDmg(20.f);
	rifle.setReloadSpeed(2.f);
	rifle.setRecoil(5.f);
	rifle.setMagazineSize(30);
	rifle.setMagazineAmmo(30);
	rifle.setMaxAmmo(120);
	rifle.setAmmo(120);
	rifle.setFire(true);
	rifle.setReload(false);
	rifle.setEmpty(false);
	rifle.setRender(false);

	sniper.setWeaponType(WEAP_SNIPER);
	sniper.setName("SCAR-20");
	sniper.setFireRate(0.5f);
	sniper.setDmg(50.f);
	sniper.setReloadSpeed(5.f);
	sniper.setRecoil(10.f);
	sniper.setMagazineSize(5);
	sniper.setMagazineAmmo(5);
	sniper.setMaxAmmo(25);
	sniper.setAmmo(25);
	sniper.setFire(true);
	sniper.setReload(false);
	sniper.setEmpty(false);
	sniper.setRender(false);

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

	pistol.setWeaponType(WEAP_PISTOL);
	pistol.setName("Desert Eagle");
	pistol.setFireRate(0.25f);
	pistol.setDmg(10.f);
	pistol.setReloadSpeed(1.f);
	pistol.setRecoil(5.f);
	pistol.setMagazineSize(7);
	pistol.setMagazineAmmo(7);
	pistol.setMaxAmmo(49);
	pistol.setAmmo(49);
	pistol.setFire(true);
	pistol.setReload(false);
	pistol.setEmpty(false);
	pistol.setRender(false);

	rifle.setWeaponType(WEAP_RIFLE);
	rifle.setName("P90");
	rifle.setFireRate(0.1f);
	rifle.setDmg(20.f);
	rifle.setReloadSpeed(2.f);
	rifle.setRecoil(5.f);
	rifle.setMagazineSize(30);
	rifle.setMagazineAmmo(30);
	rifle.setMaxAmmo(120);
	rifle.setAmmo(120);
	rifle.setFire(true);
	rifle.setReload(false);
	rifle.setEmpty(false);
	rifle.setRender(false);

	sniper.setWeaponType(WEAP_SNIPER);
	sniper.setName("SCAR-20");
	sniper.setFireRate(1.5f);
	sniper.setDmg(50.f);
	sniper.setReloadSpeed(5.f);
	sniper.setRecoil(10.f);
	sniper.setMagazineSize(5);
	sniper.setMagazineAmmo(5);
	sniper.setMaxAmmo(25);
	sniper.setAmmo(25);
	sniper.setFire(true);
	sniper.setReload(false);
	sniper.setEmpty(false);
	sniper.setRender(false);

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
}*/

void Inventory::switchWeapon(bool increment)
{
	switch(currentWeapon->getWeaponType())
	{
	case WEAP_PISTOL:
		{
			if (increment)
			{
				nextWeapon = &rifle;
				break;
			}

			else
			{
				nextWeapon = &sniper;
				break;
			}
		}
	case WEAP_RIFLE:
		{
			if (increment)
			{
				nextWeapon = &sniper;
				break;
			}

			else
			{
				nextWeapon = &pistol;
				break;
			}
		}
	case WEAP_SNIPER:
		{
			if (increment)
			{
				nextWeapon = &pistol;
				break;
			}

			else
			{
				nextWeapon = &rifle;
				break;
			}
		}
	}

	switch(nextWeapon->getWeaponType())
	{
	case WEAP_PISTOL:
		{
			currentWeapon = &pistol;
			break;
		}
	case WEAP_RIFLE:
		{
			currentWeapon = &rifle;
			break;
		}
	case WEAP_SNIPER:
		{
			currentWeapon = &sniper;
			break;
		}
	}
}

/*
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