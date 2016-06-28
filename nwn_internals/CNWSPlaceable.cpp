#include "types.h"
#include "nwn_internals.h"

void 	(__thiscall *CNWSPlaceable__CNWSPlaceable)(CNWSPlaceable *pThis, nwn_objid_t oID) = (void(__thiscall*)(CNWSPlaceable *pThis, nwn_objid_t oID))0x0051DEC0;
void 	(__thiscall *CNWSPlaceable__AddToArea)(CNWSPlaceable *pThis, CNWSArea *Area, Vector v, int a2) = (void(__thiscall*)(CNWSPlaceable *pThis, CNWSArea *Area, Vector v, int a2))0x005206F0;
int32_t	(__thiscall *CNWSPlaceable__AcquireItem)(CNWSPlaceable *pThis, CNWSItem **a2, nwn_objid_t From, int a4, int a5, int bSendFeedBack) = (signed int (__thiscall*)(CNWSPlaceable *pThis, CNWSItem **a2, nwn_objid_t From, int a4, int a5, int bSendFeedBack))0x00521AD0;
int		(__thiscall *CNWSPlaceable__LoadPlaceable)(CNWSPlaceable *pThis, CResGFF *ResGFF, CResStruct *ResStruct, CExoString *Tag) = (int(__thiscall*)(CNWSPlaceable *pThis, CResGFF *ResGFF, CResStruct *ResStruct, CExoString *Tag))0x0051E4D0;
int		(__thiscall *CNWSPlaceable__SavePlaceable)(CNWSPlaceable *pThis, CResGFF *, void *CResStruct) = (int (__thiscall*)(CNWSPlaceable *pThis, CResGFF *, void *CResStruct))0x0051FBD0;
void 	(__thiscall *CNWSPlaceable__SetScriptName)(CNWSPlaceable *pThis, int iScript, CExoString ScriptName) = (void (__thiscall*)(CNWSPlaceable *pThis, int iScript, CExoString ScriptName))0x004CD150;

CNWSPlaceable_s::CNWSPlaceable_s(nwn_objid_t oID) {
	CNWSPlaceable__CNWSPlaceable(this, oID);
}

int32_t CNWSPlaceable_s::AcquireItem(CNWSItem **a2, nwn_objid_t From, int a4, int a5, int bSendFeedBack) {
	return CNWSPlaceable__AcquireItem(this, a2, From, a4, a5, bSendFeedBack);
}

void  CNWSPlaceable_s::SetScriptName(int iScript, CExoString ScriptName) {
	CNWSPlaceable__SetScriptName(this, iScript, ScriptName);
}

int CNWSPlaceable::SavePlaceable(CResGFF *ResGFF, void *ResStruct) {
	return CNWSPlaceable__SavePlaceable(this, ResGFF, ResStruct);
}

int CNWSPlaceable_s::LoadPlaceable(CResGFF *ResGFF, CResStruct *ResStruct, CExoString *Tag) {
	return CNWSPlaceable__LoadPlaceable(this, ResGFF, ResStruct, Tag);
}

void CNWSPlaceable_s::AddToArea(CNWSArea *Area, Vector v, int a2) {
	CNWSPlaceable__AddToArea(this, Area, v, a2);
}