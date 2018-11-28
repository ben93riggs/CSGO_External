#ifndef PROCMEM_H
#define PROCMEM_H
#define WIN32_LEAN_AND_MEAN
#pragma once
#include <windows.h>
#include <iostream>

struct PModule {
	DWORD dwBase;
	DWORD dwSize;
};

class ProcMem{
protected:
	
	DWORD dwPID, dwProtection, dwCaveAddress;
	BOOL bPOn, bIOn, bProt;

public:
	HANDLE hProcess;
	ProcMem();
	virtual ~ProcMem();
public:
	int chSizeOfArray(char *chArray);
	int iSizeOfArray(int *iArray);
	bool iFind(int *iAry, int iVal);
	PModule GetModule(wchar_t const * moduleName);

#pragma region TEMPLATE MEMORY FUNCTIONS

	template <class cData>
	cData Read(DWORD dwAddress)
	{
		cData cRead;
		ReadProcessMemory(hProcess, LPVOID(dwAddress), &cRead, sizeof(cData), nullptr);
		return cRead;
	}


	template <class cData>
	cData Read(DWORD dwAddress, char *Offset, BOOL Type)
	{
		int iSize = iSizeOfArray(Offset) - 1;
		dwAddress = Read<DWORD>(dwAddress);
		for (int i = 0; i < iSize; i++)
			dwAddress = Read<DWORD>(dwAddress + Offset[i]);

		if (!Type)
			return dwAddress + Offset[iSize];
		else
			return Read<cData>(dwAddress + Offset[iSize]);
	}


	template <class cData>
	void Read(DWORD dwAddress, cData Value)
	{
		ReadProcessMemory(hProcess, LPVOID(dwAddress), &Value, sizeof(cData), nullptr);
	}


	template <class cData>
	void Read(DWORD dwAddress, char *Offset, cData Value)
	{
		Read<cData>(Read<cData>(dwAddress, Offset, false), Value);
	}

	    //WRITE MEMORY 
    template <class cData> 
    void Write(DWORD dwAddress, cData Value) 
    { 
        WriteProcessMemory(hProcess, LPVOID(dwAddress), &Value, sizeof(cData), nullptr); 
    } 

    //WRITE MEMORY - Pointer 
    template <class cData> 
    void Write(DWORD dwAddress, char *Offset, cData Value) 
    { 
        Write<cData>(Read<cData>(dwAddress, Offset, false), Value); 
    }  


	virtual bool Process(wchar_t const* ProcessName);
	virtual void Patch(DWORD dwAddress, char *chPatch_Bts, char *chDefault_Bts);
	virtual DWORD AOB_Scan(DWORD dwAddress, DWORD dwEnd, char *chPattern);
	virtual DWORD Module(wchar_t const * Modulename);
	bool DataCompare(const BYTE* pData, const BYTE* pMask, const char* pszMask);
	DWORD FindPattern(DWORD start, DWORD size, const char* sig, const char* mask);
	//DWORD FindPatternArr(DWORD start, DWORD size, const char* mask, ...);
	DWORD FindPatternArr(DWORD start, DWORD size, const char* mask, int count, ...);
#pragma endregion

};
#endif

