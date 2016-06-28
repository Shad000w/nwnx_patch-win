#ifndef __CNWRACE_H__
#define __CNWRACE_H__

#include "CExoString.h"

struct CNWRace_s {

public:

	unsigned __int32 Name;//0
	unsigned __int32 ConverName;//4
	unsigned __int32 ConverNameLower;//8
	unsigned __int32 NamePlural;//C
	unsigned __int32 Description;//10
	unsigned __int32 Biography;//14
	__int8 StrAdjust;//18
	__int8 DexAdjust;//19
	__int8 IntAdjust;//1A
	__int8 ChaAdjust;//1B
	__int8 WisAdjust;//1C
	__int8 ConAdjust;//1D
	__int8 Endurance;//1E
	__int8 Favored;//1F
	unsigned __int32 Player_Race;
	unsigned __int32 field_24;
	unsigned __int32 field_28;
	unsigned __int32 Age;
	unsigned __int32 Appearance;
};
#endif