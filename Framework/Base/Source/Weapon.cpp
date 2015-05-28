#include "Weapon.h"

Weapon::Weapon(void)
{
	m_WeaponType = WEAP_DEFAULT;
	m_sName = "DEFAULT";
	m_fFireRate = 1.f;
	m_fDmg = 10.f;
	m_fReloadSpeed = 3.f;
	m_iMagazineSize = 30;
	m_iMagazineAmmo = 30;
	m_iMaxAmmo = 300;
	m_iCurrentAmmo = 30;

	m_bCanFire = true;
	m_bIsReload = false;
	m_bIsEmpty = false;

	m_fFireTimer = 0.f;
	m_fReloadTimer = 0.f;

	this->m_bReflectLight = false;
}

Weapon::~Weapon(void)
{
}

void Weapon::setWeaponType(WEAPON_TYPE weaponType)
{
	this->m_WeaponType = weaponType;
}

void Weapon::setName(string name)
{
	this->m_sName = name;
}

void Weapon::setFireRate(float fireRate)
{
	this->m_fFireRate = fireRate;
}

void Weapon::setDmg(float dmg)
{
	this->m_fDmg = dmg;
}

void Weapon::setReloadSpeed(float reloadSpeed)
{
	this->m_fReloadSpeed = reloadSpeed;
}

void Weapon::setRecoil(float recoil)
{
	this->m_fRecoil = recoil;
}

void Weapon::setAmmo(int ammo)
{
	this->m_iCurrentAmmo = ammo;
}

void Weapon::setMagazineSize(int magazineSize)
{
	this->m_iMagazineSize = magazineSize;
}

void Weapon::setMagazineAmmo(int magazineAmmo)
{
	this->m_iMagazineAmmo = magazineAmmo;
}

void Weapon::setMaxAmmo(int maxAmmo)
{
	this->m_iMaxAmmo = maxAmmo;
}

void Weapon::setFire(bool canFire)
{
	this->m_bCanFire = canFire;
}

void Weapon::setReload(bool reloading)
{
	this->m_bIsReload = reloading;
}

void Weapon::setEmpty(bool empty)
{
	this->m_bIsEmpty = empty;
}

WEAPON_TYPE Weapon::getWeaponType(void) const
{
	return this->m_WeaponType;
}

string Weapon::getName(void) const
{
	return this->m_sName;
}

float Weapon::getFireRate(void) const
{
	return this->m_fFireRate;
}

float Weapon::getDmg(void) const
{
	return this->m_fDmg;
}

float Weapon::getReloadSpeed(void) const
{
	return this->m_fReloadSpeed;
}

float Weapon::getRecoil(void) const
{
	return this->m_fRecoil;
}

int Weapon::getAmmo(void) const
{
	return this->m_iCurrentAmmo;
}

int Weapon::getMagazineSize(void) const
{
	return this->m_iMagazineSize;
}

int Weapon::getMagazineAmmo(void) const
{
	return this->m_iMagazineAmmo;
}

int Weapon::getMaxAmmo(void) const
{
	return this->m_iMaxAmmo;
}

bool Weapon::getCanFire(void) const
{
	return this->m_bCanFire;
}

bool Weapon::getReload(void) const
{
	return this->m_bIsReload;
}

bool Weapon::getEmpty(void) const
{
	return this->m_bIsEmpty;
}

void Weapon::Update(double dt)
{
	m_fFireTimer += dt;

	if (m_iCurrentAmmo <= 0)
	{
		m_bIsEmpty = true;
		m_bCanFire = false;
	}

	else if (m_iMagazineAmmo > 0)
	{ 
		m_bIsEmpty = false;
		m_bCanFire = true;
	}

	if (m_bIsReload)
	{
		m_bCanFire = false;
		m_fReloadTimer += dt;

		if (m_fReloadTimer > m_fReloadSpeed)
		{
			m_bCanFire = true;
			m_fReloadTimer = 0.f;
			m_bIsReload = false;
		}
	}
}

bool Weapon::Fire(void)
{
	if(m_bCanFire)
	{
		switch(m_WeaponType)
		{
			case WEAP_PISTOL:
			{
				if (m_fFireTimer > m_fFireRate)
				{
					--m_iMagazineAmmo;
					m_fFireTimer = 0.f;
					m_bCanFire = true;
					break;
				}

				else
				{
					m_bCanFire = false;
				}
				
			}
			case WEAP_RIFLE:
			{
				if (m_fFireTimer > m_fFireRate)
				{
					--m_iMagazineAmmo;
					m_fFireTimer = 0.f;
					m_bCanFire = true;
					break;
				}
				else
				{
					m_bCanFire = false;
				}
			}
			case WEAP_SNIPER:
			{
				if (m_fFireTimer > m_fFireRate)
				{
					--m_iMagazineAmmo;
					m_fFireTimer = 0.f;
					m_bCanFire = true;
					break;
				}
				else
				{
					m_bCanFire = false;
				}
			}
		}

		return m_bCanFire;
	}

	else
	{
		return false;
	}
}

bool Weapon::Reload(void)
{
	if (m_iCurrentAmmo <= 0)
	{
		return false;
	}

	// if there are enough ammo to reload
	else if (m_iMagazineAmmo < m_iMagazineSize)
	{
		int ammoReloaded = m_iMagazineSize - m_iMagazineAmmo;

		m_iCurrentAmmo -= ammoReloaded;
		m_iMagazineAmmo = m_iMagazineSize;

		m_bIsReload = true;

		return true;
	}

	else
	{
		return false;
	}
}

void Weapon::SpecialFunc(void)
{
}