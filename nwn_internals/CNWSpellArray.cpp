#include "types.h"
#include "nwn_internals.h"

void (__thiscall *CNWSpellArray__Load)(CNWSpellArray *pThis) = (void(__thiscall*)(CNWSpellArray *))0x502CC0;
CNWSpellArray *(__thiscall *CNWSpellArray__CNWSpellArray)(CNWSpellArray *pThis) = (CNWSpellArray*(__thiscall*)(CNWSpellArray *))0x512AA0;
CNWSpell *(__thiscall *CNWSpellArray__GetSpell)(CNWSpellArray *pThis, int SpellID) = (CNWSpell*(__thiscall*)(CNWSpellArray *, int))0x502C90;
	
CNWSpell *CNWSpellArray_s::GetSpell(int SpellID) {
	return CNWSpellArray__GetSpell(this, SpellID);
}

void CNWSpellArray_s::Load()
{
CNWSpellArray__Load(this);
}

CNWSpellArray *CNWSpellArray_s::CNWSpellArray()
{
return CNWSpellArray__CNWSpellArray(this);
}
