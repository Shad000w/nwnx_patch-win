#include "types.h"
#include "nwn_internals.h"

unsigned char (__thiscall *CNWSpell__GetSpellLevel)(CNWSpell*,unsigned char) = (unsigned char(__thiscall*)(CNWSpell*,unsigned char))0x502AC0;


unsigned char CNWSpell::GetSpellLevel(unsigned char cls_id)
{
return CNWSpell__GetSpellLevel(this,cls_id);
}