#include "stdafx.h"
#include "NWNXPatch.h"

CNWNXPatch Patch;
extern "C" __declspec(dllexport) CNWNXBase* GetClassObject()
{
	return &Patch;
}

BOOL APIENTRY DllMain (HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    return TRUE;
}