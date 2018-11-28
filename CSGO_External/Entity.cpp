#include "Entity.h"

#pragma region Engine
int Engine::GetLocalIndex()
{
	return GetDataFromArray<int>(eb.pEngineData, oh.m_dwLocalPlayerIndex) + 1;
}

Vector Engine::GetViewAngles()
{
	return GetDataFromArray<Vector>(eb.pEngineData, oh.m_dwViewAngles);
}

string Engine::getMapName()
{
	for (int i = 0; i < 64; i++)
		mapName[i] = GetDataFromArray<char>(eb.pEngineData, oh.m_dwMapname + i);

	return mapName;
}

int Engine::GetSignOnState()
{
	return GetDataFromArray<DWORD>(eb.pEngineData, oh.gameStateOffset);
}
#pragma endregion

Engine engine;

#pragma region Entity
DWORD Entity::GetPlayerBase()
{
	return GetDataFromArray<DWORD>(eb.pEntityData, 0x00);
}

bool Entity::GetDormant()
{
	return GetDataFromArray<bool>(eb.pEntityData, oh.m_bDormant);
}

bool Entity::GetSpottedByMe()
{
	INT64 dwMask = GetDataFromArray<INT64>(eb.pEntityData, oh.m_bSpottedByMask);
	return bool(dwMask & 1 << engine.GetLocalIndex() - 1);
}

float Entity::GetFlashDuration()
{
	return GetDataFromArray<float>(eb.pEntityData, oh.m_flFlashDuration);
}

int Entity::GetClassID()
{
	int vt = GetDataFromArray<int>(eb.pEntityData, 0x8);
	int fn = oh.mem.Read<int>(vt + 0x8);
	int clazz = oh.mem.Read<int>(fn + 0x1);
	return oh.mem.Read<int>(clazz + 20);
}

int Entity::GetFlags()
{
	return GetDataFromArray<int>(eb.pEntityData, oh.m_fFlags);
}

int Entity::GetHealth()
{
	return GetDataFromArray<int>(eb.pEntityData, oh.m_iHealth);
}

int Entity::GetIndex()
{
	return GetDataFromArray<int>(eb.pEntityData, oh.m_dwIndex);
}

int Entity::GetShotsFired()
{
	return GetDataFromArray<int>(eb.pEntityData, oh.m_iShotsFired);
}

int Entity::GetTeam()
{
	return GetDataFromArray<int>(eb.pEntityData, oh.m_iTeamNum);
}

int Entity::GetTicks()
{
	return GetDataFromArray<int>(eb.pEntityData, oh.m_nTickBase);
}

Vector Entity::GetBonePosition(int TargetBone)
{
	DWORD BoneMatrix = GetDataFromArray<DWORD>(eb.pEntityData, oh.m_dwBoneMatrix);
	Misc::Bone temp = oh.mem.Read<Misc::Bone>(BoneMatrix + 0x30 * TargetBone + 0x0C);
	
	return Vector(temp.bone_x, temp.bone_y, temp.bone_z);
}

Misc::BoneMatrix Entity::GetBoneMatrix()
{
	DWORD BoneMatrix = GetDataFromArray<DWORD>(eb.pEntityData, oh.m_dwBoneMatrix);
	return oh.mem.Read<Misc::BoneMatrix>(BoneMatrix);
}

Vector Entity::GetPunch()
{
	return GetDataFromArray<Vector>(eb.pEntityData, oh.m_vecPunch);
}

Vector Entity::GetVecOrigin()
{
	Vector temp = GetDataFromArray<Vector>(eb.pEntityData, oh.m_vecOrigin);
	return Vector(temp.x, temp.y, temp.z + GetDataFromArray<float>(eb.pEntityData, 0x10C));
}

string Entity::GetName()
{
	tPlayerName temp = oh.mem.Read<tPlayerName>(oh.RadarPointer + (0x1E0 * GetIndex()) + 0x24);
	wstring ws(temp.Text);
	string str(ws.begin(), ws.end());
	return str;
}

WeaponIndex Entity::GetCurrentWeapon()
{
	DWORD ActiveWeapon = GetDataFromArray<DWORD>(eb.pEntityData, +oh.m_hActiveWeapon);
	ActiveWeapon = ActiveWeapon & 0xFFF;

	DWORD CurrentWeapon = oh.mem.Read<DWORD>(oh.ClientDLL + oh.m_dwEntityList + ((ActiveWeapon)-1) * 0x10);
	int weapon_id = oh.mem.Read<int>(CurrentWeapon + oh.m_iItemDefinitionIndex);

	return WeaponIndex(weapon_id);
}

DWORD Entity::GetCrosshairEntity()
{
	int CrossHairID = GetDataFromArray<int>(eb.pEntityData, oh.m_iCrossHairID);
	return oh.mem.Read<DWORD>(oh.ClientDLL + oh.m_dwEntityList + (CrossHairID - 1) * oh.EntLoopDist); // CH = Crosshair.
}

Entity* Entity::GetCrosshairEntityPtr()
{
	int CrossHairID = GetDataFromArray<int>(eb.pEntityData, oh.m_iCrossHairID);
	return oh.mem.Read<Entity*>(oh.ClientDLL + oh.m_dwEntityList + (CrossHairID - 1) * oh.EntLoopDist);
}

int Entity::GetCrosshairEntityTeam()
{
	DWORD entity = this->GetCrosshairEntity();
	return GetDataFromArray<int>(GetEntityFromDWORD(entity).eb.pEntityData, oh.m_iTeamNum);
}

int Entity::GetRank()
{
	return oh.mem.Read<int>(oh.PlayerResource + oh.m_iCompetitiveRanking + GetIndex() * 4);
}

int Entity::GetLifeState()
{
	return GetDataFromArray<int>(eb.pEntityData, oh.m_lifeState);
}

bool Entity::GetGunGameImmunity()
{
	return GetDataFromArray<bool>(eb.pEntityData, oh.m_bGunGameImmunity);
}

#pragma region weaponstuff
WeaponType Entity::GetWeaponType()
{
	WeaponIndex weapon = GetCurrentWeapon();

	if (weapon == WEAPON_DEAGLE || weapon == WEAPON_REVOLVER || weapon == WEAPON_DUAL || weapon == WEAPON_FIVE7 || weapon == WEAPON_GLOCK || weapon == WEAPON_P250 || weapon == WEAPON_CZ75_AUTO || weapon == WEAPON_HKP2000 || weapon == WEAPON_TEC9 || weapon == WEAPON_TASER || weapon == WEAPON_USPS)
		return WEAPONTYPE_PISTOL;
	if (weapon == WEAPON_MAC10 || weapon == WEAPON_P90 || weapon == WEAPON_UMP || weapon == WEAPON_BIZON || weapon == WEAPON_MP7 || weapon == WEAPON_MP9)
		return WEAPONTYPE_SMG;
	if (weapon == WEAPON_XM1014 || weapon == WEAPON_MAG7 || weapon == WEAPON_SAWEDOFF || weapon == WEAPON_NOVA)
		return WEAPONTYPE_SHOTGUN;
	if (weapon == WEAPON_AK47 || weapon == WEAPON_AUG || weapon == WEAPON_FAMAS || weapon == WEAPON_GALIL || weapon == WEAPON_M4A1 || weapon == WEAPON_M4A1_S || weapon == WEAPON_SG553)
		return WEAPONTYPE_RIFLE;
	if (weapon == WEAPON_M249 || weapon == WEAPON_NEGEV)
		return WEAPONTYPE_HEAVY;
	if (weapon == WEAPON_AWP || weapon == WEAPON_SSG08 || weapon == WEAPON_SCAR20 || weapon == WEAPON_G3SG1)
		return WEAPONTYPE_SNIPER;
	if (weapon == WEAPON_KNIFEGG || weapon == WEAPON_KNIFE || weapon == WEAPON_KNIFE_T || weapon == WEAPON_FLASHBANG || weapon == WEAPON_HEGRENADE || weapon == WEAPON_SMOKE || weapon == WEAPON_T_MOLOTOV || weapon == WEAPON_CT_MOLOTOV || weapon == WEAPON_DECOY || weapon == WEAPON_C4 || weapon == WEAPON_KNIFE_BAYONET || weapon == WEAPON_KNIFE_FLIP || weapon == WEAPON_KNIFE_GUT || weapon == WEAPON_KNIFE_KARAMBIT || weapon == WEAPON_KNIFE_M9_BAYONET || weapon == WEAPON_KNIFE_HUNTSMAN || weapon == WEAPON_KNIFE_FALCHION || weapon == WEAPON_KNIFE_BOWIE || weapon == WEAPON_KNIFE_BUTTERFLY || weapon == WEAPON_KNIFE_SHADOW_DAGGERS)
		return WEAPONTYPE_OTHER;

	cout << "WEAPONTYPE NOT FOUND FROM ID:\t" << weapon << endl;
	return WEAPONTYPE_OTHER;
}

#pragma endregion 
#pragma endregion

Entity me, player[playerCount];