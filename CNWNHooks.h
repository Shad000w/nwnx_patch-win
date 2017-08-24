#include <windows.h>
#include <string.h>
#include <stdio.h>
#include "nwn_internals.h"
#include "types.h"
#pragma comment(lib, "madCHook.lib")

typedef unsigned long dword;
typedef unsigned short int word;
typedef unsigned char byte;

int CreateHook(DWORD pCode, PVOID pCallbackFunc, PVOID *pNextHook, const char * czName, const char * czFunc);
void Hook();