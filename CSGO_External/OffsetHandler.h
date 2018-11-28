#pragma once
#include <Windows.h>
#include "ProcMem.h"
//#include <string>

class OffsetHandler
{
public:
	//OffsetHandler();
	//~OffsetHandler();
	ProcMem mem;
	std::string toHex(DWORD offset);
	void getOffsets();
	void printDebug();
	DWORD m_dwEntityList;
	DWORD m_dwLocalPlayer;
	DWORD m_dwClientState;
	DWORD m_dwViewMatrix;
	DWORD m_dwForceAttack;
	DWORD m_dwForceJump;
	DWORD m_iCrossHairID;
	DWORD m_dwGlowObject;
	DWORD m_dwServerRevealRank;
	DWORD m_dwRadarBase;// = 0x04ED462C;
	DWORD CSPlayerResource;// = 0x2EDD8F4;
	DWORD dwEngine;
	DWORD Radar;
	DWORD RadarPointer;
	DWORD ClientDLL;
	DWORD EngineDLL;
	DWORD PlayerResource;

#pragma region static offsets
	DWORD m_szName = 0x9D8;
	DWORD gameStateOffset = 0x100;//dwClientState_State
	DWORD m_dwLocalPlayerIndex = 0x178;//
	DWORD m_dwMapname = 0x284;//
	DWORD EntLoopDist = 0x10;
	DWORD playerCountOffset = 0x308;//same as dwMaxPlayer
	DWORD m_dwMaxPlayer = 0x308;//
	DWORD m_iTeamNum = 0xF0;//
	DWORD m_iHealth = 0xFC;//
	DWORD m_lifeState = 0x25B;
	DWORD m_dwIndex = 0x64; //entityClass
	DWORD m_iWeaponID = 0x32EC; //if offset isnt working try adding 0x8 to it 0x4->0xC
	DWORD m_hActiveWeapon = 0x2EE8;
	DWORD m_vecViewOffset = 0x104;
	DWORD m_fFlags = 0x100;
	DWORD m_angEyeAngles = 0xA9EC;
	DWORD m_vecPunch = 0x3018;
	DWORD m_flFlashMaxAlpha = 0xA2F4;
	DWORD m_flFlashDuration = 0xA2F8;
	DWORD m_vecOrigin = 0x134;
	DWORD m_bSpotted = 0x939;
	DWORD m_bSpottedByMask = 0x97C;
	DWORD m_bDormant = 0xE9;
	DWORD m_dwViewAngles = 0x4D0C;//
	DWORD m_dwBoneMatrix = 0x2698;
	DWORD m_iShotsFired = 0xA2B0;
	DWORD m_bGunGameImmunity = 0x38A0;
	DWORD m_nTickBase = 0x3414;
	DWORD m_iCompetitiveRanking = 0x1A44;
	DWORD m_bSendPackets = 0xDFC97;// 0xDFF97;
	//DWORD m_AttributeManager = ;
	//DWORD m_Item = ;
	//DWORD m_iItemDefinitionIndex = 2F80;
#pragma endregion

private:
	
	PModule modClient, modEngine;

	void updateLocalPlayer();
	void updateEntityList();
	void updateAttack();
	void updateJump();
	void updateEnginePointer();
	void updateServerRevealRank();
	void updateRadarBase();
	void updateCSPlayerResource();
	void updateViewMatrix();
	void updateCrosshairIndex();
	void updateGlowObject();
};