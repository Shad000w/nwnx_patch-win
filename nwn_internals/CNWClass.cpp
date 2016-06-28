#include "types.h"
#include "nwn_internals.h"

unsigned char (__thiscall *CNWClass__GetFortSaveBonus)(CNWClass*, unsigned char) = (unsigned char(__thiscall*)(CNWClass *, unsigned char))0x504B90;
unsigned char (__thiscall *CNWClass__GetWillSaveBonus)(CNWClass*, unsigned char) = (unsigned char(__thiscall*)(CNWClass *, unsigned char))0x504BD0;
unsigned char (__thiscall *CNWClass__GetRefSaveBonus)(CNWClass*, unsigned char) = (unsigned char(__thiscall*)(CNWClass *, unsigned char))0x504BB0;
unsigned char (__thiscall *CNWClass__GetSpellGain)(CNWClass*, unsigned char, unsigned char) = (unsigned char(__thiscall*)(CNWClass*, unsigned char, unsigned char))0x504BF0;
unsigned char (__thiscall *CNWClass__GetSpellsKnownPerLevel)(CNWClass*, unsigned char, unsigned char, unsigned char, unsigned short, unsigned char) = (unsigned char(__thiscall*)(CNWClass*, unsigned char, unsigned char, unsigned char, unsigned short, unsigned char))0x504C30;

int (__thiscall *CNWClass__IsBonusFeat)(CNWClass*, unsigned short) = (int(__thiscall*)(CNWClass*, unsigned short))0x505E80;
int (__thiscall *CNWClass__IsNormalFeat)(CNWClass*, unsigned short) = (int(__thiscall*)(CNWClass*, unsigned short))0x505ED0;
int (__thiscall *CNWClass__IsGrantedFeat)(CNWClass*, unsigned short, unsigned char&) = (int(__thiscall*)(CNWClass*, unsigned short, unsigned char&))0x505F40;

unsigned char CNWClass_s::GetFortSaveBonus(uint8_t Level) {
	return CNWClass__GetFortSaveBonus(this, Level);
}

unsigned char CNWClass_s::GetWillSaveBonus(uint8_t Level) {
	return CNWClass__GetWillSaveBonus(this, Level);
}

unsigned char CNWClass_s::GetRefSaveBonus(uint8_t Level) {
	return CNWClass__GetRefSaveBonus(this, Level);
}

unsigned char CNWClass::GetSpellGain(unsigned char cls_lvl, unsigned char spell_lvl) {
	return CNWClass__GetSpellGain(this,cls_lvl,spell_lvl);
}

unsigned char CNWClass::GetSpellsKnownPerLevel(unsigned char cls_lvl, unsigned char spell_lvl, unsigned char cls_id, unsigned short race, unsigned char charisma) {
	return CNWClass__GetSpellsKnownPerLevel(this,cls_lvl,spell_lvl,cls_id,race,charisma);
}

int CNWClass_s::IsBonusFeat(unsigned short feat_id) {
	return CNWClass__IsBonusFeat(this,feat_id);
}

int CNWClass_s::IsNormalFeat(unsigned short feat_id) {
	return CNWClass__IsNormalFeat(this,feat_id);
}

int CNWClass_s::IsGrantedFeat(unsigned short feat_id, unsigned char &val) {
	return CNWClass__IsGrantedFeat(this,feat_id,val);
}