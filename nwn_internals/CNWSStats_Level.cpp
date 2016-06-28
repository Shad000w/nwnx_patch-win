#include "types.h"
#include "nwn_internals.h"

void 			(__thiscall *CNWLevelStats__AddFeat)(CNWSStats_Level *pThis, uint16_t Feat) = (void (__thiscall *)(CNWSStats_Level *, uint16_t))0x506570;
CNWSStats_Level*(__thiscall *CNWLevelStats__CNWLevelStats)(CNWSStats_Level *pThis) = (CNWSStats_Level* (__thiscall*)(CNWSStats_Level *))0x506330;


void  CNWSStats_Level_s::AddFeat(uint16_t Feat) {
	CNWLevelStats__AddFeat(this, Feat);
}

CNWSStats_Level* CNWSStats_Level_s::CNWLevelStats() {
	return CNWLevelStats__CNWLevelStats(this);
}

