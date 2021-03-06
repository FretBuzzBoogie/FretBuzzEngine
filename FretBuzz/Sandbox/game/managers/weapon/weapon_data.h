#pragma once
#include <string>
#include <fretbuzz.h>

namespace ns_HMGame
{
	enum WEAPON_TYPE;
	class WeaponData
	{
	public:
		enum WEAPON_ATTACK_TYPE
		{
			MELEE = 0,
			GUN = 1
		};

		WeaponData(WEAPON_TYPE a_WeaponType);
		WeaponData(const WeaponData& a_WeaponData);
		WeaponData(WEAPON_ATTACK_TYPE a_WeaponAttackType, WEAPON_TYPE a_WeaponType, std::string a_strAnimOverrideTrigger, std::string a_strSpriteName, std::string a_strBulletSpriteName, std::string a_strWeaponFireAudID);
		~WeaponData();

		WEAPON_TYPE getWeaponType() const;
		WEAPON_ATTACK_TYPE getWeaponAttackType() const;
		std::string getWeaponAnimTrigger() const;
		std::string getWeaponSpriteName() const;
		std::string getBulletSpriteName() const;
		std::string getWeaponFireAudID() const;

		void fire(glm::vec2 a_v2Position, glm::vec2 a_v3Direction,glm::quat a_quatRotation);

		void operator=(const WeaponData& a_Other);

	private:
		WEAPON_TYPE m_WeaponType;
		WEAPON_ATTACK_TYPE m_WeaponAttackType;
		std::string m_strAnimOverrideTrigger;
		std::string m_strWeaponSpriteName;
		std::string m_strBulletSpriteName;
		std::string m_strWeaponFireAudID;
	};
}