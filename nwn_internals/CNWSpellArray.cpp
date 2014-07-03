#include "stdafx.h"
#include "types.h"
#include "nwn_internals.h"

CNWSpell *(__thiscall *CNWSpellArray__GetSpell)(CNWSpellArray *pTHIS, int SpellID) = (CNWSpell*(__thiscall*)(CNWSpellArray *pTHIS, int SpellID))0x00502C90;
	
CNWSpell *CNWSpellArray_s::GetSpell(int SpellID) {
	return CNWSpellArray__GetSpell(this, SpellID);
}

void (__thiscall *CNWSpellArray__Load)(CNWSpellArray *pTHIS) = (void(__thiscall*)(CNWSpellArray *pTHIS))0x00502CC0;

void CNWSpellArray_s::Load()
{
CNWSpellArray__Load(this);
}

CNWSpellArray *(__thiscall *CNWSpellArray__CNWSpellArray)(CNWSpellArray *pTHIS) = (CNWSpellArray*(__thiscall*)(CNWSpellArray *pTHIS))0x00512AA0;

CNWSpellArray *CNWSpellArray_s::CNWSpellArray()
{
return CNWSpellArray__CNWSpellArray(this);
}
