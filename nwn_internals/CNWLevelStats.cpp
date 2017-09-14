#include "types.h"
#include "nwn_internals.h"

void 	(__thiscall *CNWLevelStats__AddFeat)(CNWLevelStats *pThis, uint16_t Feat) = (void (__thiscall *)(CNWLevelStats *, uint16_t))0x506570;
void	(__thiscall *CNWLevelStats__CNWLevelStats)(CNWLevelStats *pThis) = (void (__thiscall*)(CNWLevelStats *))0x506330;


void  CNWLevelStats_s::AddFeat(uint16_t Feat) {
	CNWLevelStats__AddFeat(this, Feat);
}

CNWLevelStats_s::CNWLevelStats_s() {
	CNWLevelStats__CNWLevelStats(this);
}

