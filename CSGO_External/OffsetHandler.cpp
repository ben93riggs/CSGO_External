#pragma once
#include "OffsetHandler.h"
#include <sstream>

std::string OffsetHandler::toHex(DWORD offset)
{
	std::stringstream ss;
	ss << std::hex << offset;
	std::string x = ss.str();
	for (auto &c : x) c = toupper(c);
	return x;
	return nullptr;
}

void OffsetHandler::getOffsets() {
	modClient = mem.GetModule(L"client.dll");
	modEngine = mem.GetModule(L"engine.dll");

	updateLocalPlayer();
	updateEntityList();
	updateAttack();
	updateJump();
	updateEnginePointer();
	updateViewMatrix();
	updateCrosshairIndex();
	updateGlowObject();
	updateRadarBase();
	updateCSPlayerResource();

	Radar = mem.Read<DWORD>(ClientDLL + m_dwRadarBase);
	RadarPointer = mem.Read<DWORD>(Radar + 0x50);
	dwEngine = mem.Read<DWORD>(EngineDLL + m_dwClientState);
	PlayerResource = mem.Read<DWORD>(ClientDLL + CSPlayerResource);

}

void OffsetHandler::updateLocalPlayer() {
	DWORD lpStart = mem.FindPatternArr(modClient.dwBase, modClient.dwSize, "xxx????xx????xxxxx?", 19, 0x8D, 0x34, 0x85, 0x0, 0x0, 0x0, 0x0, 0x89, 0x15, 0x0, 0x0, 0x0, 0x0, 0x8B, 0x41, 0x8, 0x8B, 0x48, 0x0);
	DWORD lpP1 = mem.Read<DWORD>(lpStart + 3);
	BYTE lpP2 = mem.Read<BYTE>(lpStart + 18);
	m_dwLocalPlayer = (lpP1 + lpP2) - modClient.dwBase;
}

void OffsetHandler::updateEntityList() {
	DWORD elStart = mem.FindPatternArr(modClient.dwBase, modClient.dwSize, "x????xx?xxx", 11, 0x5, 0x0, 0x0, 0x0, 0x0, 0xC1, 0xE9, 0x0, 0x39, 0x48, 0x4);
	DWORD elP1 = mem.Read<DWORD>(elStart + 1);
	BYTE elP2 = mem.Read<BYTE>(elStart + 7);
	m_dwEntityList = (elP1 + elP2) - modClient.dwBase;
}

void OffsetHandler::updateAttack() {
	DWORD aStart = mem.FindPatternArr(modClient.dwBase, modClient.dwSize, "xx????xx????xxxxxxxxxxx", 23, 0x89, 0x15, 0x0, 0x0, 0x0, 0x0, 0x8B, 0x15, 0x0, 0x0, 0x0, 0x0, 0xF6, 0xC2, 0x3, 0x74, 0x3, 0x83, 0xCE, 0x4, 0xA8, 0x4, 0xBF);
	DWORD aOff = mem.Read<DWORD>(aStart + 2);
	m_dwForceAttack = aOff - modClient.dwBase;
}

void OffsetHandler::updateJump() {
	DWORD aStart = mem.FindPatternArr(modClient.dwBase, modClient.dwSize, "xx????xx????xxxxxxxxxxx", 23, 0x89, 0x15, 0x0, 0x0, 0x0, 0x0, 0x8B, 0x15, 0x0, 0x0, 0x0, 0x0, 0xF6, 0xC2, 0x3, 0x74, 0x3, 0x83, 0xCE, 0x8, 0xA8, 0x8, 0xBF);
	DWORD jOff = mem.Read<DWORD>(aStart + 2);
	m_dwForceJump = jOff - modClient.dwBase;
}

void OffsetHandler::updateViewMatrix() {
	DWORD vmStart = mem.FindPatternArr(modClient.dwBase, modClient.dwSize, "xxxxxxxxxxxxxxxxxxxxxxx????xxxxxx", 33, 0x53, 0x8B, 0xDC, 0x83, 0xEC, 0x08, 0x83, 0xE4, 0xF0, 0x83, 0xC4, 0x04, 0x55, 0x8B, 0x6B, 0x04, 0x89, 0x6C, 0x24, 0x04, 0x8B, 0xEC, 0xA1, 0x00, 0x00, 0x00, 0x00, 0x81, 0xEC, 0x98, 0x03, 0x00, 0x00);
	vmStart = mem.Read<DWORD>(vmStart + 0x4EE);
	vmStart -= modClient.dwBase;
	vmStart += 0x80;
	m_dwViewMatrix = 0x4AB9BB4;//vmStart;
}

void OffsetHandler::updateCrosshairIndex()
{
	/*DWORD chStart = mem.FindPatternArr(modClient.dwBase, modClient.dwSize, "xxxxxx????????xx????xx????xxx????xx", 35, 0x56, 0x57, 0x8B, 0xF9, 0xC7, 0x87, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8B, 0x0D, 0x0, 0x0, 0x0, 0x0, 0x81, 0xF9, 0x0, 0x0, 0x0, 0x0, 0x75, 0x07, 0xA1, 0x0, 0x0, 0x0, 0x0, 0xEB, 0x07);
	DWORD chOff = mem.Read<DWORD>(chStart + 6);
	std::cout << chOff - modClient.dwBase << std::endl;*/
	m_iCrossHairID = 0xAA70;//chOff;
}

void OffsetHandler::updateGlowObject()
{
	DWORD goStart = mem.FindPatternArr(modClient.dwBase, modClient.dwSize, "x????xxx?xxxxx", 14, 0xA1, 0x0, 0x0, 0x0, 0x0, 0xA8, 0x01, 0x75, 0x0, 0x0F, 0x57, 0xC0, 0xC7, 0x05);
	DWORD goOff = mem.Read<DWORD>(goStart + 1);
	goOff -= modClient.dwBase;
	goOff += 0x4;
	m_dwGlowObject = goOff;
}

void OffsetHandler::updateEnginePointer() {
	DWORD epStart = mem.FindPatternArr(modEngine.dwBase, modEngine.dwSize, "xxxxxxxx????xxxxxxxxxx????xxxx????xxx", 37, 0xF3, 0x0F, 0x5C, 0xC1, 0xF3, 0x0F, 0x10, 0x15, 0x0, 0x0, 0x0, 0x0, 0x0F, 0x2F, 0xD0, 0x76, 0x04, 0xF3, 0x0F, 0x58, 0xC1, 0xA1, 0x0, 0x0, 0x0, 0x0, 0xF3, 0x0F, 0x11, 0x80, 0x0, 0x0, 0x0, 0x0, 0xD9, 0x46, 0x04);
	m_dwClientState = mem.Read<DWORD>(epStart + 22) - modEngine.dwBase;
}

void OffsetHandler::updateServerRevealRank()
{
	DWORD srrStart = mem.FindPatternArr(modClient.dwBase, modClient.dwSize, "xxxx????x", 9, 0x8B, 0xEC, 0x8B, 0x0D, 0x00, 0x00, 0x00, 0x00, 0x68);
	DWORD srrOff = mem.Read<DWORD>(srrStart + 4);
	m_dwServerRevealRank = srrOff;
}

void OffsetHandler::updateRadarBase()
{
	DWORD rbStart = mem.FindPatternArr(modClient.dwBase, modClient.dwSize, "x????xxxxxxx?xxx????xxxx", 24, 0xA1, 0x00, 0x00, 0x00, 0x00, 0x8B, 0x0C, 0xB0, 0x8B, 0x01, 0xFF, 0x50, 0x00, 0x46, 0x3B, 0x35, 0x00, 0x00, 0x00, 0x00, 0x7C, 0xEA, 0x8B, 0x0D);
	DWORD rbOff = mem.Read<DWORD>(rbStart + 1);
	m_dwRadarBase = rbOff - modClient.dwBase;
}

void OffsetHandler::updateCSPlayerResource()
{
	DWORD csprStart = mem.FindPatternArr(modClient.dwBase, modClient.dwSize, "xx????xxxx????xx", 16, 0x8B, 0x3D, 0x00, 0x00, 0x00, 0x00, 0x85, 0xFF, 0x0F, 0x84, 0x00, 0x00, 0x00, 0x00, 0x81, 0xC7);
	DWORD csprOff = mem.Read<DWORD>(csprStart + 2);
	CSPlayerResource = csprOff - modClient.dwBase;
}


void OffsetHandler::printDebug()
{
	//system("cls");
	std::cout << std::endl;
	std::cout << "\tPRINTDEBUG()" << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "Client.DLL Position: \t" << toHex(modClient.dwBase) << std::endl;
	std::cout << "Engine.DLL Position: \t" << toHex(modEngine.dwBase) << std::endl;
	std::cout << std::endl;
	std::cout << "m_dwLocalPlayer: \t" << toHex(m_dwLocalPlayer) << std::endl;
	std::cout << "m_dwEntityList: \t" << toHex(m_dwEntityList) << std::endl;
	std::cout << "m_dwForceAttack: \t" << toHex(m_dwForceAttack) << std::endl;
	std::cout << "m_dwForceJump: \t\t" << toHex(m_dwForceJump) << std::endl;
	std::cout << "m_dwViewMatrix: \t" << toHex(m_dwViewMatrix) << std::endl;
	std::cout << "m_iCrossHairID: \t" << toHex(m_iCrossHairID) << std::endl;
	std::cout << "m_dwClientState: \t" << toHex(m_dwClientState) << std::endl;
	std::cout << "m_dwGlowObject: \t" << toHex(m_dwGlowObject) << std::endl;
	std::cout << "m_dwRadarBase: \t\t" << toHex(m_dwRadarBase) << std::endl;
	std::cout << "CSPlayerResource: \t" << toHex(CSPlayerResource) << std::endl;

	std::cout << std::endl;

}