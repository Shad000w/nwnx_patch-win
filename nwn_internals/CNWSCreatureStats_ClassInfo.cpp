#include "types.h"
#include "nwn_internals.h"

CNWSCreatureStats_ClassInfo*(__thiscall *CNWSCreatureStats_ClassInfo__CNWSCreatureStats_ClassInfo)(CNWSCreatureStats_ClassInfo *) = (CNWSCreatureStats_ClassInfo*(__thiscall*)(CNWSCreatureStats_ClassInfo*))0x46C080;
void			(__thiscall *CNWSCreatureStats_ClassInfo_dtor)(CNWSCreatureStats_ClassInfo *pThis) = (void(__thiscall*)(CNWSCreatureStats_ClassInfo *pThis))0x46C140;
void			(__thiscall *CNWSCreatureStats_ClassInfo__SetMemorizedSpellSlot)(CNWSCreatureStats_ClassInfo *, unsigned char, unsigned char, unsigned long, int, unsigned char) = (void(__thiscall*)(CNWSCreatureStats_ClassInfo*, unsigned char, unsigned char, unsigned long, int, unsigned char))0x46C220;
void			(__thiscall *CNWSCreatureStats_ClassInfo__ClearMemorizedSpellSlot)(CNWSCreatureStats_ClassInfo *, unsigned char, unsigned long) = (void(__thiscall*)(CNWSCreatureStats_ClassInfo*, unsigned char, unsigned long))0x46C2C0;
void			(__thiscall *CNWSCreatureStats_ClassInfo__ClearMemorizedKnownSpells)(CNWSCreatureStats_ClassInfo *, unsigned long) = (void(__thiscall*)(CNWSCreatureStats_ClassInfo*, unsigned long))0x46C310;
void			(__thiscall *CNWSCreatureStats_ClassInfo__RemoveKnownSpell)(CNWSCreatureStats_ClassInfo *, unsigned char, unsigned long) = (void(__thiscall*)(CNWSCreatureStats_ClassInfo*, unsigned char, unsigned long))0x46C4B0;
unsigned long	(__thiscall *CNWSCreatureStats_ClassInfo__GetKnownSpell)(CNWSCreatureStats_ClassInfo *, unsigned char, unsigned char) = (unsigned long(__thiscall*)(CNWSCreatureStats_ClassInfo*, unsigned char, unsigned char))0x46C510;
unsigned long	(__thiscall *CNWSCreatureStats_ClassInfo__GetMemorizedSpellInSlot)(CNWSCreatureStats_ClassInfo *, unsigned char, unsigned char) = (unsigned long(__thiscall*)(CNWSCreatureStats_ClassInfo*, unsigned char, unsigned char))0x46C550;
int				(__thiscall *CNWSCreatureStats_ClassInfo__GetIsDomainSpell)(CNWSCreatureStats_ClassInfo *, unsigned char, unsigned char) = (int(__thiscall*)(CNWSCreatureStats_ClassInfo*, unsigned char, unsigned char))0x46C5A0;
CNWSStats_Spell*(__thiscall *CNWSCreatureStats_ClassInfo__GetMemorizedSpellInSlotDetails)(CNWSCreatureStats_ClassInfo *, unsigned char, unsigned char) = (CNWSStats_Spell*(__thiscall*)(CNWSCreatureStats_ClassInfo*, unsigned char, unsigned char))0x46C5F0;
void			(__thiscall *CNWSCreatureStats_ClassInfo__SetNumberMemorizedSpellSlots)(CNWSCreatureStats_ClassInfo *, unsigned char, unsigned char) = (void(__thiscall*)(CNWSCreatureStats_ClassInfo*, unsigned char, unsigned char))0x46C630;
int				(__thiscall *CNWSCreatureStats_ClassInfo__GetMemorizedSpellInSlotReady)(CNWSCreatureStats_ClassInfo *, unsigned char, unsigned char) = (int(__thiscall*)(CNWSCreatureStats_ClassInfo*, unsigned char, unsigned char))0x46C740;
void			(__thiscall *CNWSCreatureStats_ClassInfo__SetMemorizedSpellInSlotReady)(CNWSCreatureStats_ClassInfo *, unsigned char, unsigned char, int) = (void(__thiscall*)(CNWSCreatureStats_ClassInfo*, unsigned char, unsigned char, int))0x46C780;
unsigned char	(__thiscall *CNWSCreatureStats_ClassInfo__GetMemorizedSpellReadyCount)(CNWSCreatureStats_ClassInfo *, unsigned long, unsigned char *, unsigned char *, unsigned char) = (unsigned char(__thiscall*)(CNWSCreatureStats_ClassInfo*, unsigned long, unsigned char *, unsigned char *, unsigned char))0x46C7C0;
unsigned char	(__thiscall *CNWSCreatureStats_ClassInfo__GetMemorizedSpellInSlotMetaType)(CNWSCreatureStats_ClassInfo *, unsigned char, unsigned char) = (unsigned char(__thiscall*)(CNWSCreatureStats_ClassInfo*, unsigned char, unsigned char))0x46CB90;
int				(__thiscall *CNWSCreatureStats_ClassInfo__ConfirmDomainSpell)(CNWSCreatureStats_ClassInfo *, unsigned char, unsigned long) = (int(__thiscall*)(CNWSCreatureStats_ClassInfo*, unsigned char, unsigned long))0x46CBD0;
unsigned char	(__thiscall *CNWSCreatureStats_ClassInfo__GetNumberMemorizedSpellSlots)(CNWSCreatureStats_ClassInfo *, unsigned char) = (unsigned char(__thiscall*)(CNWSCreatureStats_ClassInfo*, unsigned char))0x46CC60;

CNWSCreatureStats_ClassInfo_s::CNWSCreatureStats_ClassInfo_s()
{
	CNWSCreatureStats_ClassInfo__CNWSCreatureStats_ClassInfo(this);
}

CNWSCreatureStats_ClassInfo_s::~CNWSCreatureStats_ClassInfo_s()
{
	CNWSCreatureStats_ClassInfo_dtor(this);
}

void CNWSCreatureStats_ClassInfo_s::SetMemorizedSpellSlot(unsigned char arg1, unsigned char arg2, unsigned long spell_id, int arg3, unsigned char arg4)
{
	CNWSCreatureStats_ClassInfo__SetMemorizedSpellSlot(this,arg1,arg2,spell_id,arg3,arg4);
}

void CNWSCreatureStats_ClassInfo_s::ClearMemorizedSpellSlot(unsigned char spell_level, unsigned char slot_pos)
{
	CNWSCreatureStats_ClassInfo__ClearMemorizedSpellSlot(this,spell_level,slot_pos);
}

void CNWSCreatureStats_ClassInfo_s::ClearMemorizedKnownSpells(unsigned long spell_id)
{
	CNWSCreatureStats_ClassInfo__ClearMemorizedKnownSpells(this,spell_id);
}

void CNWSCreatureStats_ClassInfo_s::RemoveKnownSpell(unsigned char spell_level, unsigned long spell_id)
{
	CNWSCreatureStats_ClassInfo__RemoveKnownSpell(this,spell_level,spell_id);
}

unsigned long CNWSCreatureStats_ClassInfo_s::GetKnownSpell(unsigned char arg1, unsigned char arg2)
{
	return CNWSCreatureStats_ClassInfo__GetKnownSpell(this,arg1,arg2);
}

unsigned long CNWSCreatureStats_ClassInfo_s::GetMemorizedSpellInSlot(unsigned char arg1, unsigned char arg2)
{
	return CNWSCreatureStats_ClassInfo__GetMemorizedSpellInSlot(this,arg1,arg2);
}

int CNWSCreatureStats_ClassInfo_s::GetIsDomainSpell(unsigned char arg1, unsigned char arg2)
{
	return CNWSCreatureStats_ClassInfo__GetIsDomainSpell(this,arg1,arg2);
}

CNWSStats_Spell * CNWSCreatureStats_ClassInfo_s::GetMemorizedSpellInSlotDetails(unsigned char arg1, unsigned char arg2)
{
	return CNWSCreatureStats_ClassInfo__GetMemorizedSpellInSlotDetails(this,arg1,arg2);
}

void CNWSCreatureStats_ClassInfo_s::SetNumberMemorizedSpellSlots(unsigned char arg1, unsigned char arg2)
{
	CNWSCreatureStats_ClassInfo__SetNumberMemorizedSpellSlots(this,arg1,arg2);
}

int CNWSCreatureStats_ClassInfo_s::GetMemorizedSpellInSlotReady(unsigned char spell_level, unsigned char spell_pos)
{
	return CNWSCreatureStats_ClassInfo__GetMemorizedSpellInSlotReady(this,spell_level,spell_pos);
}

void CNWSCreatureStats_ClassInfo_s::SetMemorizedSpellInSlotReady(unsigned char spell_level, unsigned char spell_pos, int spell_ready)
{
	CNWSCreatureStats_ClassInfo__SetMemorizedSpellInSlotReady(this,spell_level,spell_pos,spell_ready);
}

unsigned char CNWSCreatureStats_ClassInfo_s::GetMemorizedSpellReadyCount(unsigned long spell_id, unsigned char *arg1, unsigned char *arg2, unsigned char arg3)
{
	return CNWSCreatureStats_ClassInfo__GetMemorizedSpellReadyCount(this,spell_id,arg1,arg2,arg3);
}

unsigned char CNWSCreatureStats_ClassInfo_s::GetMemorizedSpellInSlotMetaType(unsigned char arg1, unsigned char arg2)
{
	return CNWSCreatureStats_ClassInfo__GetMemorizedSpellInSlotMetaType(this,arg1,arg2);
}

int CNWSCreatureStats_ClassInfo_s::ConfirmDomainSpell(unsigned char arg1, unsigned long spell_id)
{
	return CNWSCreatureStats_ClassInfo__ConfirmDomainSpell(this,arg1,spell_id);
}

unsigned char CNWSCreatureStats_ClassInfo_s::GetNumberMemorizedSpellSlots(unsigned char spell_level)
{
	return CNWSCreatureStats_ClassInfo__GetNumberMemorizedSpellSlots(this,spell_level);
}










/*
int CNWSCreatureStats_ClassInfo::AddKnownSpell(unsigned char, unsigned long)
int CNWSCreatureStats_ClassInfo::DecrementSpellsPerDayLeft(unsigned char)
int CNWSCreatureStats_ClassInfo::GetMaxSpellsPerDayLeft(unsigned char)

int CNWSCreatureStats_ClassInfo::GetMemorizedSpellReadyCount(unsigned long, unsigned char)
int CNWSCreatureStats_ClassInfo::GetNumberBonusSpells(unsigned char)
int CNWSCreatureStats_ClassInfo::GetNumberKnownSpells(unsigned char)
int CNWSCreatureStats_ClassInfo::GetSpellsPerDayLeft(unsigned char)
int CNWSCreatureStats_ClassInfo::IncrementSpellsPerDayLeft(unsigned char)
int CNWSCreatureStats_ClassInfo::ResetSpellsPerDayLeft(unsigned char, unsigned char)
int CNWSCreatureStats_ClassInfo::SetMaxSpellsPerDayLeft(unsigned char, unsigned char)
int CNWSCreatureStats_ClassInfo::SetNumberBonusSpells(unsigned char, unsigned char)
int CNWSCreatureStats_ClassInfo::SetSpellsPerDayLeft(unsigned char, unsigned char)
*/