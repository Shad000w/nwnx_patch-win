#include "stdafx.h"
#include "types.h"
#include "nwn_internals.h"

unsigned char	(__thiscall *CNWSCreatureStats_ClassInfo__GetNumberMemorizedSpellSlots)(CNWSCreatureClass *pThis, unsigned char spell_level) = (unsigned char(__thiscall*)(CNWSCreatureClass *pThis, unsigned char spell_level))0x46CC60;
int				(__thiscall *CNWSCreatureStats_ClassInfo__GetMemorizedSpellInSlotReady)(CNWSCreatureClass *pThis, unsigned char spell_level, unsigned char spell_pos) = (int(__thiscall*)(CNWSCreatureClass *pThis, unsigned char spell_level, unsigned char spell_pos))0x46C740;
void			(__thiscall *CNWSCreatureStats_ClassInfo__SetMemorizedSpellInSlotReady)(CNWSCreatureClass *pThis, unsigned char spell_level, unsigned char spell_pos, int spell_ready) = (void(__thiscall*)(CNWSCreatureClass *pThis, unsigned char spell_level, unsigned char spell_pos, int spell_ready))0x46C780;
void			(__thiscall *CNWSCreatureStats_ClassInfo__SetNumberMemorizedSpellSlots)(CNWSCreatureClass *pThis, unsigned char spell_level, unsigned char num_slots) = (void(__thiscall*)(CNWSCreatureClass*, unsigned char, unsigned char))0x46C630;
int				(__thiscall *CNWSCreatureStats_ClassInfo__ConfirmDomainSpell)(CNWSCreatureClass *pThis, unsigned char arg1, unsigned long spell_id) = (int(__thiscall*)(CNWSCreatureClass*, unsigned char, unsigned long))0x46CBD0;
void			(__thiscall *CNWSCreatureStats_ClassInfo__RemoveKnownSpell)(CNWSCreatureClass *pThis, unsigned char spell_level, unsigned long spell_id) = (void(__thiscall*)(CNWSCreatureClass*, unsigned char, unsigned long))0x46C4B0;
/*
.text:0046C220 ; public: void __thiscall CNWSCreatureStats_ClassInfo::SetMemorizedSpellSlot(unsigned char, unsigned char, unsigned long, int, unsigned char)
46C2C0 ; public: void __thiscall CNWSCreatureStats_ClassInfo::ClearMemorizedSpellSlot(unsigned char, unsigned char)
46C310 ; public: void __thiscall CNWSCreatureStats_ClassInfo::ClearMemorizedKnownSpells(unsigned long)
.text:0046C4B0 ; public: void __thiscall CNWSCreatureStats_ClassInfo::RemoveKnownSpell(unsigned char, unsigned long)
.text:0046C4B0 ; public: void __thiscall CNWSCreatureStats_ClassInfo::RemoveKnownSpell(unsigned char, unsigned long)
.text:0046C510 ; public: unsigned long __thiscall CNWSCreatureStats_ClassInfo::GetKnownSpell(unsigned char, unsigned char)
.text:0046C550 ; public: unsigned long __thiscall CNWSCreatureStats_ClassInfo::GetMemorizedSpellInSlot(unsigned char, unsigned char)
.text:0046C5A0 ; public: int __thiscall CNWSCreatureStats_ClassInfo::GetIsDomainSpell(unsigned char, unsigned char)
.text:0046C5F0 ; public: class CNWSStats_Spell * __thiscall CNWSCreatureStats_ClassInfo::GetMemorizedSpellInSlotDetails(unsigned char, unsigned char)
.text:0046C630 ; public: void __thiscall CNWSCreatureStats_ClassInfo::SetNumberMemorizedSpellSlots(unsigned char, unsigned char)
.text:0046C740 ; public: int __thiscall CNWSCreatureStats_ClassInfo::GetMemorizedSpellInSlotReady(unsigned char, unsigned char)
.text:0046C780 ; public: void __thiscall CNWSCreatureStats_ClassInfo::SetMemorizedSpellInSlotReady(unsigned char, unsigned char, int)
.text:0046C7C0 ; public: unsigned char __thiscall CNWSCreatureStats_ClassInfo::GetMemorizedSpellReadyCount(unsigned long, unsigned char *, unsigned char *, unsigned char)
.text:0046CB90 ; public: unsigned char __thiscall CNWSCreatureStats_ClassInfo::GetMemorizedSpellInSlotMetaType(unsigned char, unsigned char)
46CBD0 ; public: int __thiscall CNWSCreatureStats_ClassInfo::ConfirmDomainSpell(unsigned char, unsigned long)

*/

CNWSCreatureStats *CNWSCreatureClass::AsNWSCreatureStats()
{
	return ((CNWSCreatureStats*)((char*)this-0x10));
}

unsigned char CNWSCreatureClass::GetNumberMemorizedSpellSlots(unsigned char spell_level)
{
	return CNWSCreatureStats_ClassInfo__GetNumberMemorizedSpellSlots(this,spell_level);
}

int CNWSCreatureClass::GetMemorizedSpellInSlotReady(unsigned char spell_level, unsigned char spell_pos)
{
	return CNWSCreatureStats_ClassInfo__GetMemorizedSpellInSlotReady(this,spell_level,spell_pos);
}

void CNWSCreatureClass::SetMemorizedSpellInSlotReady(unsigned char spell_level, unsigned char spell_pos, int spell_ready)
{
	CNWSCreatureStats_ClassInfo__SetMemorizedSpellInSlotReady(this,spell_level,spell_pos,spell_ready);
}

void CNWSCreatureClass::SetNumberMemorizedSpellSlots(unsigned char spell_level, unsigned char num_slots)
{
	CNWSCreatureStats_ClassInfo__SetNumberMemorizedSpellSlots(this,spell_level,num_slots);
}

int CNWSCreatureClass::ConfirmDomainSpell(unsigned char arg1, unsigned long spell_id)
{
	return CNWSCreatureStats_ClassInfo__ConfirmDomainSpell(this,arg1,spell_id);
}

void CNWSCreatureClass::RemoveKnownSpell(unsigned char spell_level, unsigned long spell_id)
{
	CNWSCreatureStats_ClassInfo__RemoveKnownSpell(this,spell_level,spell_id);
}