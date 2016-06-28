#include "stdafx.h"
#include "types.h"
#include "nwn_internals.h"

CNWSFaction*	(__thiscall *CFactionManager__GetFaction)(CFactionManager *pThis, uint32_t FactionID) = (CNWSFaction * (__thiscall*)(CFactionManager *pThis, uint32_t FactionID))0x00533EE0;


CNWSFaction *CFactionManager::GetFaction(uint32_t FactionID) {
	return CFactionManager__GetFaction(this, FactionID);
}