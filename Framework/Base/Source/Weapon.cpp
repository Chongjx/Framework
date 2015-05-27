#include "Weapon.h"

Weapon::Weapon(void)
{
	m_WeaponType = WEAP_DEFAULT;
	m_sName = "DEFAULT";
	m_fFireRate = 1.f;
	m_fDmg = 10.f;
	m_fReloadSpeed = 3.f;
	m_iMagazineSize = 30;
	m_iMaxAmmo = 300;
	m_iCurrentAmmo = 30;

	for (int i = 0; i < m_iMagazineSize * 2; ++i)
	{
		m_Ammo.push_back(new Bullet);
	}

	for(std::vector<Bullet *>::iterator it = m_Ammo.begin(); it != m_Ammo.end(); ++it)
	{
		Bullet *bullet = (Bullet*) *it;
		bullet->setRender(false);
		bullet->setStatus(false);
	}

	m_bCanFire = true;
	m_bIsReload = false;
	m_bIsEmpty = false;
}

Weapon::~Weapon(void)
{
	while(m_Ammo.size() > 0)
	{
		Bullet *bullet = m_Ammo.back();
		delete bullet;
		m_Ammo.pop_back();
	}
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

	for (int i = 0; i < m_iMagazineSize; ++i)
	{
		m_Ammo.push_back(new Bullet);
	}
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

void Weapon::Fire(FPcamera &user)
{
	for(std::vector<Bullet *>::iterator it = m_Ammo.begin(); it != m_Ammo.end(); ++it)
	{
		Bullet *bullet = (Bullet*) *it;
			
		if(bullet->getStatus() == false)
		{
			bullet->setStatus(true);
			Vector3 view = (user.getTarget() - user.getPosition()).Normalized();
			bullet->Shot(user.getTarget(), Vector3(view.x, view.y, view.z), 200.f, 5.f);
			break;
		}
	}
	--m_iCurrentAmmo;
}

void Weapon::Reload(void)
{
}

void Weapon::SpecialFunc(void)
{
}