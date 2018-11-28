#pragma once
#include "Vector.h"
#include <Windows.h>
#include "Misc.h"
#include "Point.h"

template <class data1>
data1 GetDataFromArray(byte* Array, uint32_t dwOffset)
{
	return *reinterpret_cast<data1*>(reinterpret_cast<uint32_t>(Array) + dwOffset);
}

class Entity;
inline Entity GetEntityFromDWORD(DWORD dw);

class EngineBuffer
{
public:
	uint8_t pEngineData[0x4D18];
};

class EntityBuffer
{
public:
	uint8_t pEntityData[0xB000];
};

class Engine
{
public:
	EngineBuffer eb;

	int GetLocalIndex()
	{
		return GetDataFromArray<int>(eb.pEngineData, oh.m_dwLocalPlayerIndex) + 1;
	}

	Vector GetViewAngles()
	{
		return GetDataFromArray<Vector>(eb.pEngineData, oh.m_dwViewAngles);
	}

	string getMapName()
	{
		for (int i = 0; i < 64; i++)
			mapName[i] = GetDataFromArray<char>(eb.pEngineData, oh.m_dwMapname + i);

		return mapName;
	}

	int GetSignOnState()
	{
		return GetDataFromArray<DWORD>(eb.pEngineData, oh.gameStateOffset);
	}

}; Engine engine;

class Entity
{
public:
	DWORD dwBase;
	Vector currentangle;
	Vector aimangle;

	EntityBuffer eb;

	DWORD GetPlayerBase()
	{
		return GetDataFromArray<DWORD>(eb.pEntityData, 0x00);
	}

	bool GetDormant()
	{
		return GetDataFromArray<bool>(eb.pEntityData, oh.m_bDormant);
	}

	bool GetSpottedByMe()
	{
		INT64 dwMask = GetDataFromArray<INT64>(eb.pEntityData, oh.m_bSpottedByMask);
		return bool(dwMask & 1 << engine.GetLocalIndex() - 1);
	}

	float GetFlashDuration()
	{
		return GetDataFromArray<float>(eb.pEntityData, oh.m_flFlashDuration);
	}

	int GetClassID()
	{
		int vt = GetDataFromArray<int>(eb.pEntityData, 0x8);
		int fn = oh.mem.Read<int>(vt + 0x8);
		int clazz = oh.mem.Read<int>(fn + 0x1);
		return oh.mem.Read<int>(clazz + 20);
	}

	int GetFlags()
	{
		return GetDataFromArray<int>(eb.pEntityData, oh.m_fFlags);
	}

	int GetHealth()
	{
		return GetDataFromArray<int>(eb.pEntityData, oh.m_iHealth);
	}

	int GetIndex()
	{
		return GetDataFromArray<int>(eb.pEntityData, oh.m_dwIndex);
	}

	int GetShotsFired()
	{
		return GetDataFromArray<int>(eb.pEntityData, oh.m_iShotsFired);
	}

	int GetTeam()
	{
		return GetDataFromArray<int>(eb.pEntityData, oh.m_iTeamNum);
	}

	int GetTicks()
	{
		return GetDataFromArray<int>(eb.pEntityData, oh.m_nTickBase);
	}

	Vector GetBonePosition(int TargetBone)
	{
		DWORD BoneMatrix = GetDataFromArray<DWORD>(eb.pEntityData, oh.m_dwBoneMatrix);
		Misc::Bone temp = oh.mem.Read<Misc::Bone>(BoneMatrix + 0x30 * TargetBone + 0x0C);
		//Misc::Bone temp = GetDataFromArray<Misc::Bone>(eb.pEntityData, BoneMatrix + 0x30 * TargetBone + 0x0C);
		return Vector(temp.bone_x, temp.bone_y, temp.bone_z);
	}

	Misc::BoneMatrix GetBoneMatrix() /////////
	{
		DWORD BoneMatrix = GetDataFromArray<DWORD>(eb.pEntityData, oh.m_dwBoneMatrix);
		return oh.mem.Read<Misc::BoneMatrix>(BoneMatrix);
	}

	Vector GetPunch()
	{
		return GetDataFromArray<Vector>(eb.pEntityData, oh.m_vecPunch);
	}

	Vector GetVecOrigin()
	{
		Vector temp = GetDataFromArray<Vector>(eb.pEntityData, oh.m_vecOrigin);
		return Vector(temp.x, temp.y, temp.z + GetDataFromArray<float>(eb.pEntityData, 0x10C));
	}

	string GetName()
	{
		tPlayerName temp = oh.mem.Read<tPlayerName>(oh.RadarPointer + (0x1E0 * GetIndex()) + 0x24);
		wstring ws(temp.Text);
		string str(ws.begin(), ws.end());
		return str;
	}

	WeaponIndex GetCurrentWeapon()
	{
		DWORD WeaponsIndex = GetDataFromArray<DWORD>(eb.pEntityData, + oh.m_hActiveWeapon);
		int WeaponsIndex2 = WeaponsIndex & 0xFFF;
		DWORD okey = oh.mem.Read<DWORD>(oh.ClientDLL + oh.m_dwEntityList + (WeaponsIndex2 - 1) * 0x10);
		int weapon_id = oh.mem.Read<int>(okey + oh.m_iWeaponID);

		return WeaponIndex(weapon_id);
	}

	DWORD GetCrosshairEntity()
	{
		int CrossHairID = GetDataFromArray<int>(eb.pEntityData, oh.m_iCrossHairID);
		return oh.mem.Read<DWORD>(oh.ClientDLL + oh.m_dwEntityList + (CrossHairID - 1) * oh.EntLoopDist); // CH = Crosshair.
	}

	Entity * GetCrosshairEntityPtr()
	{
		int CrossHairID = GetDataFromArray<int>(eb.pEntityData, oh.m_iCrossHairID);
		return oh.mem.Read<Entity*>(oh.ClientDLL + oh.m_dwEntityList + (CrossHairID - 1) * oh.EntLoopDist);
	}

	int GetCrosshairEntityTeam()
	{
		DWORD entity = this->GetCrosshairEntity();
		return GetDataFromArray<int>(GetEntityFromDWORD(entity).eb.pEntityData, oh.m_iTeamNum);
		//return oh.mem.Read<int>(entity + oh.m_iTeamNum); // Enemy in crosshair's team, we need this to compare it to our own player's team)
	}

	int GetRank()
	{
		//DWORD dwTemp = oh.mem.Read<DWORD>(oh.ClientDLL + oh.CSPlayerResource);
		return oh.mem.Read<int>(oh.PlayerResource + oh.m_iCompetitiveRanking + GetIndex() * 4);
	}

	int GetLifeState()
	{
		return GetDataFromArray<int>(eb.pEntityData, oh.m_lifeState);
	}

	bool GetGunGameImmunity()
	{
		return GetDataFromArray<bool>(eb.pEntityData, oh.m_bGunGameImmunity);
	}

	#pragma region weaponstuff
	WeaponType GetWeaponType()
	{
		WeaponIndex weapon = GetCurrentWeapon();

		if (weapon == WEAPON_DEAGLE || weapon == WEAPON_DUAL || weapon == WEAPON_FIVE7 || weapon == WEAPON_GLOCK || weapon == WEAPON_P250_CZ75 || weapon == WEAPON_HKP2000 || weapon == WEAPON_TEC9 || weapon == WEAPON_TASER)
			return WEAPONTYPE_PISTOL;
		if (weapon == WEAPON_MAC10 || weapon == WEAPON_P90 || weapon == WEAPON_UMP || weapon == WEAPON_BIZON || weapon == WEAPON_MP7 || weapon == WEAPON_MP9)
			return WEAPONTYPE_SMG;
		if (weapon == WEAPON_XM1014 || weapon == WEAPON_MAG7 || weapon == WEAPON_SAWEDOFF || weapon == WEAPON_NOVA)
			return WEAPONTYPE_SHOTGUN;
		if (weapon == WEAPON_AK47 || weapon == WEAPON_AUG || weapon == WEAPON_FAMAS || weapon == WEAPON_GALIL || weapon == WEAPON_M4A1 || weapon == WEAPON_SG553)
			return WEAPONTYPE_RIFLE;
		if (weapon == WEAPON_M249 || weapon == WEAPON_NEGEV)
			return WEAPONTYPE_HEAVY;
		if (weapon == WEAPON_AWP || weapon == WEAPON_SSG08 || weapon == WEAPON_SCAR20 || weapon == WEAPON_G3SG1)
			return WEAPONTYPE_SNIPER;
		if (weapon == WEAPON_KNIFEGG || weapon == WEAPON_KNIFE || weapon == WEAPON_FLASHBANG || weapon == WEAPON_HEGRENADE || weapon == WEAPON_SMOKE || weapon == WEAPON_T_MOLOTOV || weapon == WEAPON_CT_MOLOTOV || weapon == WEAPON_DECOY || weapon == WEAPON_C4)
			return WEAPONTYPE_OTHER;

		cout << "WEAPONTYPE NOT FOUND FROM ID:\t" << weapon << endl;
		return WEAPONTYPE_OTHER;
	}
	#pragma endregion 

};Entity me, player[playerCount]; //Entity * meee, * players[playerCount];

inline Entity GetEntityFromDWORD(DWORD dw)
{
	for (int p = 0; p <= playerCount; p++)
	{
		if (player[p].dwBase == dw)
			return player[p];
	}
	//cout << "COULD NOT FIND ENTITY FROM DWORD. (NULL)" << endl;
	return {};
}

inline Entity GetEntityFromIndex(int i)
{
	for (int p = 0; p <= playerCount; p++)
	{
		if (player[p].GetIndex() == i)
			return player[p];
	}
	//cout << "COULD NOT FIND ENTITY FROM INDEX. (NULL)" << endl;
	return{};
}

inline void SetAngle(Vector angle) {
	Point point;
	while (angle.y > 180 || angle.y < -180 || angle.x > 89.0f || angle.x < -89.0f)
	{
		angle = angle.NormalizeAngle();
	}

	/*if (angle.y > 180 || angle.y < -180 || angle.x > 89.0f || angle.x < -89.0f)
		cout << "CANNOT WRITE INVALID ANGLES:\n" << angle;*/

	/*point.x = angle.x;
	point.y = angle.y;
	*/

	//if (angle.y > 180)
	//	angle.y -= 360;

	//if (angle.y < -180)
	//	angle.y += 360;

	//if (angle.x > 89.0f)
	//	angle.x = 89.0f;

	//if (angle.x < -89.0f)
	//	angle.x = -89.0f;

	oh.mem.Write<Vector>(oh.dwEngine + oh.m_dwViewAngles, angle);

}

/*ItemDefinitionIndex GetItemDefinitionIndex(Entity* p)
{
ItemDefinitionIndex nWeaponIndex = oh.mem.Read<ItemDefinitionIndex>(dwWeaponEntity + m_AttributeManager + m_Item + m_iItemDefinitionIndex);
return nWeaponIndex;
}*/