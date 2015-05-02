#ifndef WEAPON_H
#define WEAPON_H

#include "Application.h"
#include "GameObject.h"
#include "Bullet.h"
#include "FPcamera.h"

enum WEAPON_TYPE
{
	WEAP_DEFAULT = 0,
	WEAP_KNIFE,
	WEAP_PISTOL,
	WEAP_RIFLE,
	WEAP_SNIPER,
	WEAP_HEAVY,
	WEAP_MAX
};

class Weapon : GameObject
{
private:
	WEAPON_TYPE m_WeaponType;
	string m_sName;
	float m_fFireRate;
	float m_fDmg;
	float m_fReloadSpeed;
	float m_fRecoil;
	int m_iMagazineSize;
	int m_iMaxAmmo;
	int m_iCurrentAmmo;
	vector<Bullet *> m_Ammo;

	bool m_bCanFire;
	bool m_bIsReload;
	bool m_bIsEmpty;
public:
	Weapon(void);
	~Weapon(void);
	
	void setWeaponType(WEAPON_TYPE weaponType);
	void setName(string name);
	void setFireRate(float fireRate);
	void setDmg(float dmg);
	void setReloadSpeed(float reloadSpeed);
	void setRecoil(float recoil);
	void setAmmo(int ammo);
	void setMagazineSize(int magazineSize);
	void setMaxAmmo(int maxAmmo);
	void setFire(bool canFire);
	void setReload(bool reloading);
	void setEmpty(bool empty);

	WEAPON_TYPE getWeaponType(void) const;
	string getName(void) const;
	float getFireRate(void) const;
	float getDmg(void) const;
	float getReloadSpeed(void) const;
	float getRecoil(void) const;
	int getAmmo(void) const;
	int getMagazineSize(void) const;
	int getMaxAmmo(void) const;
	bool getCanFire(void) const;
	bool getReload(void) const;
	bool getEmpty(void) const;

	void Fire(FPcamera &user);
	void updateFire(void);
	void Reload(void);
	void SpecialFunc(void);
};

#endif