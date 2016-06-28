#include "stdafx.h"
#include "types.h"
#include "nwn_internals.h"

void			(__thiscall *CNWSArea__CNWSArea)(void* pThis, CResRef, int, unsigned long)=(void (__thiscall*)(void *, CResRef, int, unsigned long))0x50A2E0;
void			(__thiscall *CNWSArea__Destructor)(CNWSArea *pThis)=(void (__thiscall*)(CNWSArea *))0x50A780;
int 			(__thiscall *CNWSArea__LoadArea)(void*, int)=(int (__thiscall*)(void*, int))0x50C380;
void			(__thiscall *CNWSArea__scalar_Destructor)(CNWSArea *pThis, char)=(void (__thiscall*)(CNWSArea *, char))0x50A760;
signed int 		(__thiscall *CNWSArea__ExploreArea)(CNWSArea *pThis, CNWSCreature *a2, int a3, int a4, int a5)=(signed int (__thiscall*)(CNWSArea *, CNWSCreature *, int, int, int))0x529C50;
long double 	(__thiscall *CNWSArea__ComputeHeight)(CNWSArea *pThis, Vector v)=(long double (__thiscall*)(CNWSArea *, Vector))0x5276D0;
CNWTile*		(__thiscall *CNWSArea__GetTile)(CNWSArea* pThis, float x, float y, int z)=(CNWTile* (__thiscall*)(CNWSArea* pThis, float, float, int))0x50C0E0;
void *			(__thiscall *CNWSArea__SetScriptName)(CNWSArea *pThis, int iScript, CExoString ScriptName)=(void* (__thiscall*)(CNWSArea *, int, CExoString))0x510C00;
int 			(__thiscall *CNWSArea__ClearLineOfSight)(CNWSArea *pThis, Vector v1, Vector v2, Vector *v3, uint32_t *, nwn_objid_t, nwn_objid_t, uint8_t)=(int (__thiscall*)(CNWSArea *, Vector, Vector, Vector *, uint32_t *, nwn_objid_t, nwn_objid_t, uint8_t))0x5114E0;
signed int 		(__thiscall *CNWSArea__GetFirstObjectInArea)(CNWSArea *pThis, nwn_objid_t *oID)=(signed int (__thiscall*)(CNWSArea *, nwn_objid_t *))0x50C070;
signed int 		(__thiscall *CNWSArea__GetNextObjectInArea)(CNWSArea *pThis, nwn_objid_t *oID)=(signed int (__thiscall*)(CNWSArea *, nwn_objid_t *))0x50C0A0;
signed int		(__thiscall *CNWSArea__AddObjectToArea)(CNWSArea *pThis, unsigned int Object_ID, int bRunEnterScript)=(signed int (__thiscall*)(CNWSArea *, unsigned int, int))0x50BAA0;
signed int 		(__thiscall *CNWSArea__RemoveObjectFromArea)(CNWSArea *pThis, unsigned int oID)=(signed int (__thiscall*)(CNWSArea *, unsigned int))0x50BEE0;
void			(__thiscall *CNWSArea__UpdatePlayerAutomaps)(CNWSArea *pThis )=(void(__thiscall*)(CNWSArea*))0x529D90;

void CNWSArea_s::UpdatePlayerAutomaps() {
	CNWSArea__UpdatePlayerAutomaps(this);
}

void CNWSArea_s::Destructor() {
	CNWSArea__Destructor(this);
}

void CNWSArea_s::CNWSArea(CResRef a1, int a2, unsigned long a3) {
	CNWSArea__CNWSArea(this, a1, a2, a3);
}

signed int CNWSArea_s::AddObjectToArea(unsigned int Object_ID, int bRunEnterScript) {
	return CNWSArea__AddObjectToArea(this, Object_ID, bRunEnterScript);
}

int CNWSArea_s::ClearLineOfSight(Vector v1, Vector v2, Vector *v3, uint32_t *a5, nwn_objid_t a6, nwn_objid_t a7, uint8_t a8) {
	return CNWSArea__ClearLineOfSight(this, v1, v2, v3, a5, a6, a7, a8);
}

long double CNWSArea_s::ComputeHeight( Vector v ) {
	return CNWSArea__ComputeHeight(this, v);
}

signed int CNWSArea_s::ExploreArea(CNWSCreature *a2, int a3, int a4, int a5) {
	return CNWSArea__ExploreArea(this, a2, a3, a4, a5);
}

signed int CNWSArea_s::GetFirstObjectInArea(nwn_objid_t *oID) {
	return CNWSArea__GetFirstObjectInArea(this, oID);
}

signed int CNWSArea_s::GetNextObjectInArea(nwn_objid_t *oID) {
	return CNWSArea__GetNextObjectInArea(this, oID);
}

CNWTile *CNWSArea_s::GetTile(float x, float y, int z) {
	return CNWSArea__GetTile(this, x, y, z);
}

int CNWSArea_s::LoadArea(int a2) {
	return CNWSArea__LoadArea(this, a2);
}

signed int CNWSArea_s::RemoveObjectFromArea(unsigned int oID) {
	return CNWSArea__RemoveObjectFromArea(this, oID);
}

void *CNWSArea_s::SetScriptName(int iScript, CExoString ScriptName) {
	return CNWSArea__SetScriptName(this, iScript, ScriptName);
}

void CNWSArea_s::scalar_Destructor(char Flag) {
	CNWSArea__scalar_Destructor(this, Flag);
}
