#include "types.h"
#include "nwn_internals.h"

int (__thiscall *CNWSTile__GetSurfaceMaterial)(CNWSTile *pThis, float, float, float) = (int (__thiscall*)(CNWSTile *, float, float, float))0x5B4CB0;


int CNWSTile::GetSurfaceMaterial(float x, float y, float z) {
	return CNWSTile__GetSurfaceMaterial(this, x, y, z);
}