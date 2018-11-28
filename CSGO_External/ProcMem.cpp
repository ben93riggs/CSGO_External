#pragma once
#include "ProcMem.h"
#include <TlHelp32.h>

using namespace std;

#pragma region Misc Functions

ProcMem::ProcMem(){
}

ProcMem::~ProcMem(){
	CloseHandle(hProcess);
}

int ProcMem::chSizeOfArray(char *chArray)
{
	for (int iLength = 1; iLength < MAX_PATH; iLength++)
		if (chArray[iLength] == '*')
			return iLength;

	cout << "\nLENGTH: Failed To Read Length Of Array\n";
	return 0;
}


int ProcMem::iSizeOfArray(int *iArray){


	for (int iLength = 1; iLength < MAX_PATH; iLength++)
		if (iArray[iLength] == '*')
			return iLength;

	cout << "\nLENGTH: Failed To Read Length Of Array\n";
	return 0;
}


bool ProcMem::iFind(int *iAry, int iVal){

	for (int i = 0; i < 64; i++)
		if (iVal == iAry[i] && iVal != 0)
			return true;

	return false;
}

#pragma endregion

#pragma region Memory Functions


bool ProcMem::Process(wchar_t const* ProcessName)
{
	HANDLE hPID = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	PROCESSENTRY32 ProcEntry;
	ProcEntry.dwSize = sizeof(ProcEntry);

	do
		if (!wcscmp(ProcEntry.szExeFile, ProcessName))
		{
			dwPID = ProcEntry.th32ProcessID;
			CloseHandle(hPID);
			hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPID);
			return true;
		}
	while (Process32Next(hPID, &ProcEntry));

	return false;
}

PModule ProcMem::GetModule(wchar_t const* moduleName)
{
	HANDLE module = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwPID);
	MODULEENTRY32 mEntry;
	mEntry.dwSize = sizeof(mEntry);

	do {
		if (!wcscmp(mEntry.szModule, moduleName)) {
			CloseHandle(module);

			PModule mod = { DWORD(mEntry.hModule), mEntry.modBaseSize };
			return mod;
		}
	} while (Module32Next(module, &mEntry));

	PModule mod = { DWORD(false), DWORD(false) };
	return mod;
}


void ProcMem::Patch(DWORD dwAddress, char *Patch_Bts, char *Default_Bts)
{
	int iSize = chSizeOfArray(Default_Bts);
	if (!bPOn)
		for (int i = 0; i < iSize; i++)
			Read<BYTE>(dwAddress + i, Patch_Bts[i]);
	else
		for (int i = 0; i < iSize; i++)
			Read<BYTE>(dwAddress + i, Default_Bts[i]);

	bPOn = !bPOn;
}

DWORD ProcMem::AOB_Scan(DWORD dwAddress, DWORD dwEnd, char *Bytes){


	int iBytesToRead = 0, iTmp = 0;
	int length = chSizeOfArray(Bytes);
	bool bTmp = false;


	if (Bytes[0] == '?')
	{
		for (; iBytesToRead < MAX_PATH; iBytesToRead++)
			if (Bytes[iBytesToRead] != '?')
			{
			iTmp = (iBytesToRead + 1);
			break;
			}
	}


	for (; dwAddress < dwEnd; dwAddress++)
	{
		if (iBytesToRead == length)
			return dwAddress - iBytesToRead;

		if (Read<BYTE>(dwAddress) == Bytes[iBytesToRead] || (bTmp && Bytes[iBytesToRead] == '?'))
		{
			iBytesToRead++;
			bTmp = true;
		}
		else
		{
			iBytesToRead = iTmp;
			bTmp = false;
		}
	}

	cout << "\nAOB_SCAN: Failed To Find Byte Pattern\n";
	return 0;
}


DWORD ProcMem::Module(wchar_t const * ModuleName){


	HANDLE hModule = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwPID);
	MODULEENTRY32 mEntry;
	mEntry.dwSize = sizeof(mEntry);


	do
		if (!wcscmp(mEntry.szModule, ModuleName))
		{
		CloseHandle(hModule);
		return DWORD(mEntry.modBaseAddr);
		}
	while (Module32Next(hModule, &mEntry));

	//cout << "\nMODULE: Process Platform Invalid.\nPlease have CS:GO running while this program is open!\n";
	return 0;
}

bool ProcMem::DataCompare(const BYTE* pData, const BYTE* pMask, const char* pszMask) {
	for (; *pszMask; ++pszMask, ++pData, ++pMask) {
		if (*pszMask == 'x' && *pData != *pMask) {
			return false;
		}
	}

	return (*pszMask == NULL);
}

DWORD ProcMem::FindPattern(DWORD start, DWORD size, const char* sig, const char* mask) {
	BYTE* data = new BYTE[size];

	unsigned long bytesRead;
	//SIZE_T bytesRead;

	if (!ReadProcessMemory(hProcess, LPVOID(start), data, size, &bytesRead)) {
		return NULL;
	}

	for (DWORD i = 0; i < size; i++) {
		if (DataCompare(static_cast<const BYTE*>(data + i), reinterpret_cast<const BYTE*>(sig), mask)) {
			return start + i;
		}
	}

	return NULL;
}

DWORD ProcMem::FindPatternArr(DWORD start, DWORD size, const char* mask, int count, ...) {
	//int count = strlen(mask);
	//cout << count << endl << endl;;
	char* sig = new char[count + 1];
	va_list ap;
	va_start(ap, count);
	for (int i = 0; i < count; i++) {
		char read = va_arg(ap, char);
		sig[i] = read;
	}
	va_end(ap);
	sig[count] = '\0';

	return FindPattern(start, size, sig, mask);
}

#pragma endregion