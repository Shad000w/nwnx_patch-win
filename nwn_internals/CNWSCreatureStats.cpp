#include "stdafx.h"
#include "types.h"
#include "nwn_internals.h"

void 			(__thiscall *CNWSCreatureStats__AddExperience)(CNWSCreatureStats *pThis, uint32_t XP) = (void (__thiscall*)(CNWSCreatureStats *pThis, uint32_t XP))0x0047D6F0;
char 			(__thiscall *CNWSCreatureStats__AddFeat)(CNWSCreatureStats *pThis, uint16_t Feat) = (char (__thiscall *)(CNWSCreatureStats *pThis, uint16_t Feat))0x0047EBC0;
void			(__thiscall *CNWSCreatureStats__AddKnownSpell)(CNWSCreatureStats *pThis, unsigned char a1, unsigned long spell_id) = (void(__thiscall*)(CNWSCreatureStats*, unsigned char, unsigned long))0x480320;
void			(__thiscall *CNWSCreatureStats__DecrementFeatRemainingUses)(CNWSCreatureStats *pThis, unsigned short FeatID) = (void(__thiscall*)(CNWSCreatureStats *pThis, unsigned short FeatID))0x00480200;
void			(__thiscall *CNWSCreatureStats__SetFeatRemainingUses)(CNWSCreatureStats *, unsigned short, unsigned char) = (void(__thiscall*)(CNWSCreatureStats *, unsigned short, unsigned char))0x47EE20;
char			(__thiscall *CNWSCreatureStats__GetACNaturalBase)(CNWSCreatureStats *pThis, int bTouchAttack) = (char (__thiscall*)(CNWSCreatureStats *pThis, int bTouchAttack))0x00489B00;
int 			(__thiscall *CNWSCreatureStats__GetArmorClassVersus)(CNWSCreatureStats *pThis, CNWSCreature *Attacker, int bTouchAttack) = (int (__thiscall*)(CNWSCreatureStats *pThis, CNWSCreature *Attacker, int bTouchAttack))0x0046DC00;
int 			(__thiscall *CNWSCreatureStats__GetAttackModifierVersus)(CNWSCreatureStats *, CNWSCreature *) = (int (__thiscall *)(CNWSCreatureStats *, CNWSCreature *))0x00470F00;
int 			(__thiscall *CNWSCreatureStats__GetBaseAttackBonus)(CNWSCreatureStats *Stats, int bPreEpicOnly) = (int (__thiscall*)(CNWSCreatureStats *Stats, int bPreEpicOnly))0x0046ED40;
int 			(__thiscall *CNWSCreatureStats__GetCanUseSkill)(CNWSCreatureStats *pThis, unsigned char Skill) = (int (__thiscall*)(CNWSCreatureStats *pThis, unsigned char Skill))0x0047E160;
unsigned char 	(__thiscall *CNWSCreatureStats__GetCHAStat)(CNWSCreatureStats *pThis) = (unsigned char(__thiscall*)(CNWSCreatureStats *pThis))0x0047C970;
unsigned char 	(__thiscall *CNWSCreatureStats__GetCONStat)(CNWSCreatureStats *pThis) = (unsigned char(__thiscall*)(CNWSCreatureStats *pThis))0x0047C760;
int				(__thiscall *CNWSCreatureStats__GetCriticalHitMultiplier)(CNWSCreatureStats *pThis, int bOffhandWeapon) = (int(__thiscall*)(CNWSCreatureStats *pThis, int bOffhandWeapon))0x00477A20;
char 			(__thiscall *CNWSCreatureStats__GetDEXMod)(CNWSCreatureStats *pThis, int bMaxArmorDex) = (char (__thiscall*)(CNWSCreatureStats *pThis, int bMaxArmorDex))0x0047CAF0;
unsigned char 	(__thiscall *CNWSCreatureStats__GetDEXStat)(CNWSCreatureStats *pThis) = (unsigned char(__thiscall*)(CNWSCreatureStats *pThis))0x0047CA20;
int 			(__thiscall *CNWSCreatureStats__GetEffectImmunity)(CNWSCreatureStats *pThis, unsigned __int8 Type, CNWSCreature *a3_Versus) = (int (__thiscall*)(CNWSCreatureStats *pThis, unsigned __int8 Type, CNWSCreature *a3_Versus))0x0048B770;
signed int 		(__thiscall *CNWSCreatureStats__GetEpicWeaponFocus)(CNWSCreatureStats *pThis, CNWSItem *weapon) = (signed int (__thiscall*)(CNWSCreatureStats *pThis, CNWSItem *weapon))0x00481510;
int 			(__thiscall *CNWSCreatureStats__GetFavoredEnemyBonus)(CNWSCreatureStats *pThis, CNWSCreature *cre_enemy) = (int (__thiscall*)(CNWSCreatureStats *pThis, CNWSCreature *cre_enemy))0x00489E50;
uint8_t			(__thiscall *CNWSCreatureStats__GetFeatRemainingUses)(CNWSCreatureStats *pThis, uint16_t FeatID) = (uint8_t(__thiscall*)(CNWSCreatureStats *pThis, uint16_t FeatID))0x0047EF10;

char 			(__thiscall *CNWSCreatureStats__GetFortSavingThrow)(CNWSCreatureStats *pThis, int bBaseOnly) = (char(__thiscall*)(CNWSCreatureStats *pThis, int bBaseOnly))0x00488BD0;
char			(__thiscall *CNWSCreatureStats__GetWillSavingThrow)(CNWSCreatureStats *pThis, int bBaseOnly) = (char(__thiscall*)(CNWSCreatureStats *pThis, int bBaseOnly))0x00488C70;
char			(__thiscall *CNWSCreatureStats__GetReflexSavingThrow)(CNWSCreatureStats *pThis, int bBaseOnly) = (char(__thiscall*)(CNWSCreatureStats *pThis, int bBaseOnly))0x00488D10;

unsigned short 	(__thiscall *CNWSCreatureStats__GetNumberKnownSpells)(CNWSCreatureStats *pThis, unsigned char a1, unsigned char a2) = (unsigned short(__thiscall*)(CNWSCreatureStats*, unsigned char, unsigned char))0x4809F0;
unsigned long 	(__thiscall *CNWSCreatureStats__GetKnownSpell)(CNWSCreatureStats *pThis, unsigned char a1, unsigned char a2, unsigned char a3) = (unsigned long(__thiscall*)(CNWSCreatureStats*, unsigned char, unsigned char, unsigned char))0x480820;

unsigned long 	(__thiscall *CNWSCreatureStats__GetHighestLevelKnown)(CNWSCreatureStats *pThis) = (unsigned long(__thiscall*)(CNWSCreatureStats *pThis))0x00480A30;
unsigned long 	(__thiscall *CNWSCreatureStats__GetMemorizedSpellInSlot)(CNWSCreatureStats *pThis, unsigned char c1, unsigned char c2, unsigned char c3) = (unsigned long(__thiscall*)(CNWSCreatureStats *pThis, unsigned char c1, unsigned char c2, unsigned char c3))0x480890;
unsigned char 	(__thiscall *CNWSCreatureStats__GetMemorizedSpellInSlotReady)(CNWSCreatureStats *pThis, unsigned char c1, unsigned char c2, unsigned char c3) = (unsigned char(__thiscall*)(CNWSCreatureStats *pThis, unsigned char c1, unsigned char c2, unsigned char c3))0x480910;
unsigned char 	(__thiscall *CNWSCreatureStats__GetMemorizedSpellInSlotMetaType)(CNWSCreatureStats *pThis, unsigned char c1, unsigned char c2, unsigned char c3) = (unsigned char(__thiscall*)(CNWSCreatureStats *pThis, unsigned char c1, unsigned char c2, unsigned char c3))0x480980;
unsigned char 	(__thiscall *CNWSCreatureStats__GetNumberMemorizedSpellSlots)(CNWSCreatureStats *pThis, unsigned char c1, unsigned char c2) = (unsigned char(__thiscall*)(CNWSCreatureStats *pThis, unsigned char c1, unsigned char c2))0x480A80;
unsigned char 	(__thiscall *CNWSCreatureStats__GetSpellsOfLevelReady)(CNWSCreatureStats *pThis, unsigned char c1, unsigned char c2) = (unsigned char(__thiscall*)(CNWSCreatureStats*s, unsigned char, unsigned char))0x48E080;
unsigned char 	(__thiscall *CNWSCreatureStats__GetSpellGainWithBonus)(CNWSCreatureStats *pThis, unsigned char c1, unsigned char c2) = (unsigned char(__thiscall*)(CNWSCreatureStats*, unsigned char, unsigned char))0x46D550;

unsigned char 	(__thiscall *CNWSCreatureStats__GetINTStat)(CNWSCreatureStats *pThis) = (unsigned char(__thiscall*)(CNWSCreatureStats *pThis))0x0047C810;
unsigned char 	(__thiscall *CNWSCreatureStats__GetIsClass)(CNWSCreatureStats *pThis, unsigned char) = (unsigned char(__thiscall*)(CNWSCreatureStats *pThis, unsigned char))0x004732D0;
int 			(__thiscall *CNWSCreatureStats__GetIsWeaponOfChoice)(CNWSCreatureStats *pThis, uint32_t BaseItemType) = (int (__thiscall*)(CNWSCreatureStats *pThis, uint32_t BaseItemType))0x0048CB10;
unsigned char	(__thiscall *CNWSCreatureStats__GetLevel)(CNWSCreatureStats *pThis, int bCountNegativeLevels) = (unsigned char (__thiscall*)(CNWSCreatureStats *pThis, int bCountNegativeLevels))0x0046DB40;
int				(__thiscall *CNWSCreatureStats__GetMeleeAttackBonus)(CNWSCreatureStats *, int, int, int) = (int (__thiscall *)(CNWSCreatureStats *, int, int, int))0x0046FB40;
unsigned char 	(__thiscall *CNWSCreatureStats__GetFeatSourceClass)(CNWSCreatureStats *pThis, unsigned short nFeat) = (unsigned char(__thiscall*)(CNWSCreatureStats *pThis, unsigned short))0x48DF60;
CNWSCreatureStats_ClassInfo* (__thiscall *CNWSCreatureStats__GetClassInfo)(CNWSCreatureStats *pTHIS, unsigned char cls) = (CNWSCreatureStats_ClassInfo* (__thiscall*)(CNWSCreatureStats*, unsigned char))0x4732A0;
unsigned char	(__thiscall *CNWSCreatureStats__GetClassLevel)(CNWSCreatureStats *pThis, unsigned char, int) = (unsigned char (__thiscall*)(CNWSCreatureStats *pThis, unsigned char, int))0x474B80;
int 			(__thiscall *CNWSCreatureStats__GetNumLevelsOfClass)(CNWSCreatureStats *pThis, unsigned char) = (int (__thiscall*)(CNWSCreatureStats *pThis, unsigned char))0x0048F400;
int 			(__thiscall *CNWSCreatureStats__GetNumLevelsOfClass2)(CNWSCreatureStats *pThis, unsigned char, int) = (int (__thiscall*)(CNWSCreatureStats *pThis, unsigned char, int))0x0048F240;
void 			(__thiscall *CNWSCreatureStats__ReadySpellLevel)(CNWSCreatureStats *pThis, unsigned char SpellLevel) = (void(__thiscall*)(CNWSCreatureStats *pThis, unsigned char SpellLevel))0x00482A50;
char 			(__thiscall *CNWSCreatureStats__GetSkillRank)(CNWSCreatureStats *pThis, unsigned __int8 nSkill, CNWSObject *vsObj, int bBaseRanksOnly) = (char (__thiscall*)(CNWSCreatureStats *pThis, unsigned __int8 nSkill, CNWSObject *vsObj, int bBaseRanksOnly))0x0047E2C0;
unsigned char 	(__thiscall *CNWSCreatureStats__GetSTRStat)(CNWSCreatureStats *pThis) = (unsigned char(__thiscall*)(CNWSCreatureStats *pThis))0x0047C6B0;
signed int 		(__thiscall *CNWSCreatureStats__GetWeaponFinesse)(CNWSCreatureStats *pThis, CNWSItem *weapon) = (signed int (__thiscall*)(CNWSCreatureStats *pThis, CNWSItem *weapon))0x00481210;
signed int 		(__thiscall *CNWSCreatureStats__GetWeaponFocus)(CNWSCreatureStats *pThis, CNWSItem *weapon) = (signed int (__thiscall*)(CNWSCreatureStats *pThis, CNWSItem *weapon))0x004812E0;
signed int 		(__thiscall *CNWSCreatureStats__GetWeaponImprovedCritical)(CNWSCreatureStats *pThis, CNWSItem *weapon) = (signed int (__thiscall*)(CNWSCreatureStats *pThis, CNWSItem *weapon))0x00481D70;
unsigned char 	(__thiscall *CNWSCreatureStats__GetWISStat)(CNWSCreatureStats *pThis) = (unsigned char(__thiscall*)(CNWSCreatureStats *pThis))0x0047C8C0;
unsigned char	(__thiscall *CNWSCreatureStats__GetUnarmedDamageDice)(CNWSCreatureStats *pThis) = (unsigned char(__thiscall*)(CNWSCreatureStats *pThis))0x004707B0;
unsigned char	(__thiscall *CNWSCreatureStats__GetUnarmedDamageDie)(CNWSCreatureStats *pThis) = (unsigned char(__thiscall*)(CNWSCreatureStats *pThis))0x00470940;
int 			(__thiscall *CNWSCreatureStats__GetUseMonkAttackTables)(CNWSCreatureStats *pThis, int) = (int (__thiscall*)(CNWSCreatureStats *pThis, int))0x00470730;
int 			(__thiscall *CNWSCreatureStats__HasFeat)(CNWSCreatureStats *Stats, uint16_t feat) = (int (__thiscall*)(CNWSCreatureStats *Stats, uint16_t feat))0x0047ECF0;
bool 			(__thiscall *CNWSCreatureStats__LevelUp)(CNWSCreatureStats *pThis, CNWLevelStats *a2, int a3, char a4, char a5, int a6) = (bool (__thiscall*)(CNWSCreatureStats *pThis, CNWLevelStats *a2, int a3, char a4, char a5, int a6))0x004847F0;
unsigned char	(__thiscall *CNWSCreatureStats__GetFeatTotalUses)(CNWSCreatureStats*, unsigned short) = (unsigned char(__thiscall*)(CNWSCreatureStats *,unsigned short))0x47F8C0;
void			(__thiscall *CNWSCreatureStats__ResetFeatRemainingUses)(CNWSCreatureStats *pThis) = (void(__thiscall*)(CNWSCreatureStats *pThis))0x004801D0;
void			(__thiscall *CNWSCreatureStats__ResetSpellLikeAbilities)(CNWSCreatureStats *pThis) = (void(__thiscall*)(CNWSCreatureStats *pThis))0x00488E40;
int 			(__thiscall *CNWSCreatureStats__ResolveSpecialAttackAttackBonus)(CNWSCreatureStats *pAttackerStats, CNWSCreature *Defender) = (int (__thiscall*)(CNWSCreatureStats *pAttackerStats, CNWSCreature *Defender))0x004744F0;
//unsigned char 	(__thiscall *CNWSCreatureStats__GetAttacksPerRound)(CNWSCreatureStats *, = (unsigned char

char			(__thiscall *CNWSCreatureStats__GetTotalSTRBonus)(CNWSCreatureStats *pThis) = (char (__thiscall*)(CNWSCreatureStats*))0x4895D0;
char			(__thiscall *CNWSCreatureStats__GetTotalDEXBonus)(CNWSCreatureStats *pThis) = (char (__thiscall*)(CNWSCreatureStats*))0x4895F0;
char			(__thiscall *CNWSCreatureStats__GetTotalCONBonus)(CNWSCreatureStats *pThis) = (char (__thiscall*)(CNWSCreatureStats*))0x489610;
char			(__thiscall *CNWSCreatureStats__GetTotalINTBonus)(CNWSCreatureStats *pThis) = (char (__thiscall*)(CNWSCreatureStats*))0x489630;
char			(__thiscall *CNWSCreatureStats__GetTotalWISBonus)(CNWSCreatureStats *pThis) = (char (__thiscall*)(CNWSCreatureStats*))0x489650;
char			(__thiscall *CNWSCreatureStats__GetTotalCHABonus)(CNWSCreatureStats *pThis) = (char (__thiscall*)(CNWSCreatureStats*))0x489670;

void			(__thiscall *CNWSCreatureStats__SetCHABase)(CNWSCreatureStats *pThis, uint8_t AbilityBase) = (void (__thiscall*)(CNWSCreatureStats *pThis, uint8_t AbilityBase))0x0047D0D0;
void			(__thiscall *CNWSCreatureStats__SetCONBase)(CNWSCreatureStats *pThis, uint8_t AbilityBase, int a3) = (void (__thiscall*)(CNWSCreatureStats *pThis, uint8_t AbilityBase, int a3))0x0047CDE0;
void			(__thiscall *CNWSCreatureStats__SetDEXBase)(CNWSCreatureStats *pThis, uint8_t AbilityBase) = (void (__thiscall*)(CNWSCreatureStats *pThis, uint8_t AbilityBase))0x0047CCC0;
void			(__thiscall *CNWSCreatureStats__SetINTBase)(CNWSCreatureStats *pThis, uint8_t AbilityBase) = (void (__thiscall*)(CNWSCreatureStats *pThis, uint8_t AbilityBase))0x0047CEF0;
void			(__thiscall *CNWSCreatureStats__SetSTRBase)(CNWSCreatureStats *pThis, uint8_t AbilityBase) = (void (__thiscall*)(CNWSCreatureStats *pThis, uint8_t AbilityBase))0x0047CBD0;
void			(__thiscall *CNWSCreatureStats__SetWISBase)(CNWSCreatureStats *pThis, uint8_t AbilityBase) = (void (__thiscall*)(CNWSCreatureStats *pThis, uint8_t AbilityBase))0x0047CFE0;

void			(__thiscall *CNWSCreatureStats__SetMovementRate)(CNWSCreatureStats *pThis, uint8_t MovementRate) = (void (__thiscall*)(CNWSCreatureStats *pThis, uint8_t MovementRate))0x00488990;
int				(__thiscall *CNWSCreatureStats__SetMemorizedSpellSlot)(CNWSCreatureStats *pThis, unsigned char a1, unsigned char a2, unsigned long spell_id, unsigned char a3, unsigned char a4, int unknown) = (int (__thiscall*)(CNWSCreatureStats*, unsigned char, unsigned char, unsigned long, unsigned char, unsigned char, int))0x4804B0;
int (__thiscall *CNWSCreatureStats__GetRangedAttackBonus)( CNWSCreatureStats *pThis, int arg1, int arg2 ) = (int (__thiscall*)(CNWSCreatureStats *pThis, int arg1, int arg2))0x00470120;

int16_t (__thiscall *CNWSCreatureStats__GetDamageRoll)(CNWSCreatureStats *pThis, CNWSObject *Defender, int bOffHand, int AttackResult, int SneakAttack, int DeathAttack, int a7) = (int16_t (__thiscall*)(CNWSCreatureStats *pThis, CNWSObject *Defender, int bOffHand, int AttackResult, int SneakAttack, int DeathAttack, int a7))0x004764D0;
CExoString (__thiscall *CNWSCreatureStats__GetAnimalCompanionName)(CNWSCreatureStats*) = (CExoString(__thiscall*)(CNWSCreatureStats*))0x446AA0;
CExoString (__thiscall *CNWSCreatureStats__GetFamiliarName)(CNWSCreatureStats*) = (CExoString(__thiscall*)(CNWSCreatureStats*))0x446AD0;
int (__thiscall *CNWSCreatureStats__GetSpellMinAbilityMet)(CNWSCreatureStats*, unsigned char, unsigned char) = (int (__thiscall*)(CNWSCreatureStats*, unsigned char, unsigned char))0x4828A0;
void(__thiscall *CNWSCreatureStats__RemoveFeat)(CNWSCreatureStats*, uint16_t) = (void(__thiscall *)(CNWSCreatureStats*, uint16_t))0x00480280;
void (__thiscall *CNWSCreatureStats__UpdateCombatInformation)(CNWSCreatureStats*) = (void (__thiscall*)(CNWSCreatureStats*))0x46EEB0;

void (__thiscall *CNWSCreatureStats__UpdateNumberMemorizedSpellSlots)(CNWSCreatureStats*) = (void (__thiscall*)(CNWSCreatureStats*))0x47D1C0;
void (__thiscall *CNWSCreatureStats__AdjustSpellUsesPerDay)(CNWSCreatureStats*) = (void (__thiscall*)(CNWSCreatureStats*))0x48B920;
void (__thiscall *CNWSCreatureStats__SetNumberBonusSpells)(CNWSCreatureStats*,unsigned char, unsigned char, unsigned char) = (void (__thiscall*)(CNWSCreatureStats*,unsigned char, unsigned char, unsigned char))0x48B660;
void (__thiscall *CNWSCreatureStats__DecrementSpellsPerDayLeft)(CNWSCreatureStats*,unsigned char, unsigned char) = (void (__thiscall*)(CNWSCreatureStats*,unsigned char, unsigned char))0x482F60;
unsigned char	(__thiscall *CNWSCreatureStats__GetSpellsPerDayLeft)(CNWSCreatureStats*, unsigned char, unsigned char) = (unsigned char(__thiscall*)(CNWSCreatureStats *,unsigned char, unsigned char))0x482F10;
void (__thiscall *CNWSCreatureStats__ComputeFeatBonuses)(CNWSCreatureStats*, CExoArrayList_uint16*, int, int) = (void (__thiscall*)(CNWSCreatureStats*, CExoArrayList_uint16*, int, int))0x48E850;

CNWSCreatureStats_ClassInfo* CNWSCreatureStats::GetInfo(unsigned char cls)
{	
	return CNWSCreatureStats__GetClassInfo(this, cls);
}

void CNWSCreatureStats_s::RemoveFeat(uint16_t Feat)
{
	CNWSCreatureStats__RemoveFeat(this, Feat);
}

void CNWSCreatureStats_s::AddKnownSpell(unsigned char cls_pos, unsigned long spell_id)
{
	CNWSCreatureStats__AddKnownSpell(this,cls_pos,spell_id);
}

int CNWSCreatureStats_s::GetRangedAttackBonus( int arg1, int arg2 )
{
	return CNWSCreatureStats__GetRangedAttackBonus( this, arg1, arg2 );
}

int CNWSCreatureStats_s::SetMemorizedSpellSlot(unsigned char a1, unsigned char a2, unsigned long spell_id, unsigned char a3, unsigned char a4, int unknown)
{
	return CNWSCreatureStats__SetMemorizedSpellSlot(this, a1,a2,spell_id,a3,a4,unknown);
}

void CNWSCreatureStats_s::SetCHABase(uint8_t CHABase) {
	CNWSCreatureStats__SetCHABase(this, CHABase);
}

void CNWSCreatureStats_s::SetMovementRate(uint8_t MOVrate) {
	CNWSCreatureStats__SetMovementRate(this, MOVrate);
}

void CNWSCreatureStats_s::SetCONBase(uint8_t CONBase, int a3) {
	CNWSCreatureStats__SetCONBase(this, CONBase, a3);
}

void CNWSCreatureStats_s::SetDEXBase(uint8_t DEXBase) {
	CNWSCreatureStats__SetDEXBase(this, DEXBase);
}

void CNWSCreatureStats_s::SetINTBase(uint8_t INTBase) {
	CNWSCreatureStats__SetINTBase(this, INTBase);
}

void CNWSCreatureStats_s::SetSTRBase(uint8_t STRBase) {
	CNWSCreatureStats__SetSTRBase(this, STRBase);
}

void CNWSCreatureStats_s::SetWISBase(uint8_t WISBase) {
	CNWSCreatureStats__SetWISBase(this, WISBase);
}

void CNWSCreatureStats_s::AddExperience(uint32_t XP) {
	return CNWSCreatureStats__AddExperience(this, XP);
}

char CNWSCreatureStats_s::AddFeat(uint16_t Feat) {
	return CNWSCreatureStats__AddFeat(this, Feat);
}

char CNWSCreatureStats_s::GetACNaturalBase(int bTouchAttack) {
	return CNWSCreatureStats__GetACNaturalBase(this, bTouchAttack);
}

int CNWSCreatureStats_s::GetAttackModifierVersus(CNWSCreature *Vs) {
	return CNWSCreatureStats__GetAttackModifierVersus(this, Vs);
}

//unsigned char CNWSCreatureStats_s::GetAttacksPerRound() {
//	return CNWSCreatureStats__GetAttacksPerRound(this);
//}

int CNWSCreatureStats_s::GetBaseAttackBonus(int bPreEpicOnly) {
	return CNWSCreatureStats__GetBaseAttackBonus(this, bPreEpicOnly);
}

char CNWSCreatureStats_s::GetDEXMod(int bMaxArmorDex) {
	return CNWSCreatureStats__GetDEXMod(this, bMaxArmorDex);
}

char CNWSCreatureStats_s::GetTotalSTRBonus() {
	return CNWSCreatureStats__GetTotalSTRBonus(this);
}

char CNWSCreatureStats_s::GetTotalDEXBonus() {
	return CNWSCreatureStats__GetTotalDEXBonus(this);
}

char CNWSCreatureStats_s::GetTotalCONBonus() {
	return CNWSCreatureStats__GetTotalCONBonus(this);
}

char CNWSCreatureStats_s::GetTotalINTBonus() {
	return CNWSCreatureStats__GetTotalINTBonus(this);
}

char CNWSCreatureStats_s::GetTotalWISBonus() {
	return CNWSCreatureStats__GetTotalWISBonus(this);
}

char CNWSCreatureStats_s::GetTotalCHABonus() {
	return CNWSCreatureStats__GetTotalCHABonus(this);
}


signed int CNWSCreatureStats_s::GetEpicWeaponFocus(CNWSItem *weapon) {
	return CNWSCreatureStats__GetEpicWeaponFocus(this, weapon);
}

int CNWSCreatureStats_s::GetFavoredEnemyBonus(CNWSCreature *cre_enemy) {
	return CNWSCreatureStats__GetFavoredEnemyBonus(this, cre_enemy);
}

int CNWSCreatureStats_s::GetIsWeaponOfChoice(uint32_t BaseItemType) {
	return CNWSCreatureStats__GetIsWeaponOfChoice(this, BaseItemType);
}

unsigned char CNWSCreatureStats_s::GetLevel(int bCountNegativeLevels) {
	return CNWSCreatureStats__GetLevel(this, bCountNegativeLevels);
}

int CNWSCreatureStats_s::GetMeleeAttackBonus(int a1, int a2, int a3) {
	return CNWSCreatureStats__GetMeleeAttackBonus(this, a1, a2, a3);
}

int CNWSCreatureStats_s::GetUseMonkAttackTables(int a1) {
	return CNWSCreatureStats__GetUseMonkAttackTables(this, a1);
}

signed int CNWSCreatureStats_s::GetWeaponFinesse(CNWSItem *weapon) {
	return CNWSCreatureStats__GetWeaponFinesse(this, weapon);
}

signed int CNWSCreatureStats_s::GetWeaponFocus(CNWSItem *weapon) {
	return CNWSCreatureStats__GetWeaponFocus(this, weapon);
}

signed int CNWSCreatureStats_s::GetWeaponImprovedCritical(CNWSItem *weapon) {
	return CNWSCreatureStats__GetWeaponImprovedCritical(this, weapon);
}

int CNWSCreatureStats_s::HasFeat(uint16_t feat) {
	return CNWSCreatureStats__HasFeat(this, feat);
}

bool CNWSCreatureStats_s::LevelUp(CNWLevelStats *a2, int a3, char a4, char a5, int a6) {
	return CNWSCreatureStats__LevelUp(this, a2, a3, a4, a5, a6);
}

int CNWSCreatureStats_s::ResolveSpecialAttackAttackBonus(CNWSCreature *Defender) {
	return CNWSCreatureStats__ResolveSpecialAttackAttackBonus(this, Defender);
}

int16_t CNWSCreatureStats_s::GetDamageRoll(CNWSObject *Defender, int bOffHand, int AttackResult, int SneakAttack, int DeathAttack, int a7) {
	return CNWSCreatureStats__GetDamageRoll(this, Defender, bOffHand, AttackResult, SneakAttack, DeathAttack, a7);
}

unsigned char CNWSCreatureStats_s::GetFeatSourceClass(unsigned short nFeat) {
	return CNWSCreatureStats__GetFeatSourceClass(this, nFeat);
}

unsigned char CNWSCreatureStats_s::GetClassLevel(unsigned char cls_pos, int bCountNegativeLevels) {
	return CNWSCreatureStats__GetClassLevel(this, cls_pos, bCountNegativeLevels);
}

unsigned short CNWSCreatureStats_s::GetNumberKnownSpells(unsigned char a1, unsigned char a2) {
	return CNWSCreatureStats__GetNumberKnownSpells(this,a1,a2);
}

unsigned long CNWSCreatureStats_s::GetKnownSpell(unsigned char a1, unsigned char a2, unsigned char a3) {
	return CNWSCreatureStats__GetKnownSpell(this,a1,a2,a3);
}

int CNWSCreatureStats_s::GetNumLevelsOfClass(unsigned char nClassType) {
	return CNWSCreatureStats__GetNumLevelsOfClass(this, nClassType);
}

int CNWSCreatureStats_s::GetNumLevelsOfClass(unsigned char nClassType, int bPreEpicOnly) {
	return CNWSCreatureStats__GetNumLevelsOfClass2(this, nClassType, bPreEpicOnly);
}

unsigned char CNWSCreatureStats_s::GetSimpleAlignmentGoodEvil() {
	int ge = this->cs_al_goodevil;
	if (ge > 30)
		if (ge > 70) 
			return  4;
		else
		return 1;
	return 5;
}

unsigned char CNWSCreatureStats_s::GetSimpleAlignmentLawChaos() {
	int lc = this->cs_al_lawchaos;
	if (lc > 30)
		if (lc > 70) 
			return  2;
		else
		return 1;
	return 3;
}

int CNWSCreatureStats_s::GetCanUseSkill(unsigned char Skill) {
	return CNWSCreatureStats__GetCanUseSkill(this, Skill);
}

char CNWSCreatureStats_s::GetSkillRank(unsigned char Skill, CNWSObject *vsObj, int bBaseRanksOnly) {
	return CNWSCreatureStats__GetSkillRank(this, Skill, vsObj, bBaseRanksOnly);
}

int CNWSCreatureStats_s::GetEffectImmunity(unsigned __int8 Type, CNWSCreature *a3_Versus) {
	return CNWSCreatureStats__GetEffectImmunity(this, Type, a3_Versus);
}

unsigned char CNWSCreatureStats::GetFeatTotalUses(unsigned short feat_id) 
{
	return CNWSCreatureStats__GetFeatTotalUses(this,feat_id);
}

uint8_t CNWSCreatureStats_s::GetFeatRemainingUses(uint16_t FeatID) {
	return CNWSCreatureStats__GetFeatRemainingUses(this, FeatID);
}

void CNWSCreatureStats_s::DecrementFeatRemainingUses(uint16_t FeatID) {
	return CNWSCreatureStats__DecrementFeatRemainingUses(this, FeatID);
}

void CNWSCreatureStats_s::SetFeatRemainingUses(unsigned short feat_id, unsigned char feat_uses)
{
	return CNWSCreatureStats__SetFeatRemainingUses(this, feat_id, feat_uses);
}

unsigned char CNWSCreatureStats_s::GetIsClass(unsigned char ClassType) {
	return CNWSCreatureStats__GetIsClass(this, ClassType);
}

int CNWSCreatureStats_s::GetArmorClassVersus(CNWSCreature *Attacker, int bTouchAttack) {
	return CNWSCreatureStats__GetArmorClassVersus(this, Attacker, bTouchAttack);	
}

unsigned char CNWSCreatureStats_s::GetUnarmedDamageDice() {
	return CNWSCreatureStats__GetUnarmedDamageDice(this);
}

unsigned char CNWSCreatureStats_s::GetUnarmedDamageDie() {
	return CNWSCreatureStats__GetUnarmedDamageDie(this);
}

int CNWSCreatureStats_s::GetCriticalHitMultiplier(int bOffhand) {
	return CNWSCreatureStats__GetCriticalHitMultiplier(this, bOffhand);
}

unsigned long CNWSCreatureStats_s::GetHighestLevelKnown() {
	return CNWSCreatureStats__GetHighestLevelKnown(this);
}

void CNWSCreatureStats_s::ReadySpellLevel(unsigned char SpellLevel) {
	CNWSCreatureStats__ReadySpellLevel(this, SpellLevel);
}

void CNWSCreatureStats_s::ResetFeatRemainingUses() {
	CNWSCreatureStats__ResetFeatRemainingUses(this);
}

void CNWSCreatureStats_s::ResetSpellLikeAbilities() {
	CNWSCreatureStats__ResetSpellLikeAbilities(this);
}

unsigned char CNWSCreatureStats_s::GetCONStat() {
	return CNWSCreatureStats__GetCONStat(this);
}

char CNWSCreatureStats_s::GetFortSavingThrow(int bBaseOnly) {
	return CNWSCreatureStats__GetFortSavingThrow(this, bBaseOnly);
}

char CNWSCreatureStats_s::GetWillSavingThrow(int bBaseOnly) {
	return CNWSCreatureStats__GetWillSavingThrow(this, bBaseOnly);
}

char CNWSCreatureStats_s::GetReflexSavingThrow(int bBaseOnly) {
	return CNWSCreatureStats__GetReflexSavingThrow(this, bBaseOnly);
}

unsigned long CNWSCreatureStats_s::GetMemorizedSpellInSlot(unsigned char c1, unsigned char c2, unsigned char c3) 
{
	return CNWSCreatureStats__GetMemorizedSpellInSlot(this,c1,c2,c3);
}

unsigned char CNWSCreatureStats_s::GetMemorizedSpellInSlotReady(unsigned char c1, unsigned char c2, unsigned char c3) 
{
	return CNWSCreatureStats__GetMemorizedSpellInSlotReady(this,c1,c2,c3);
}

unsigned char CNWSCreatureStats_s::GetMemorizedSpellInSlotMetaType(unsigned char c1, unsigned char c2, unsigned char c3) 
{
	return CNWSCreatureStats__GetMemorizedSpellInSlotMetaType(this,c1,c2,c3);
}

unsigned char CNWSCreatureStats_s::GetNumberMemorizedSpellSlots(unsigned char cls_pos, unsigned char spell_level) 
{
	return CNWSCreatureStats__GetNumberMemorizedSpellSlots(this,cls_pos,spell_level);
}

unsigned char CNWSCreatureStats_s::GetSpellsOfLevelReady(unsigned char cls_pos, unsigned char spell_level) 
{
	return CNWSCreatureStats__GetSpellsOfLevelReady(this,cls_pos,spell_level);
}

unsigned char CNWSCreatureStats_s::GetSpellGainWithBonus(unsigned char cls_pos, unsigned char spell_level) 
{
	return CNWSCreatureStats__GetSpellGainWithBonus(this,cls_pos,spell_level);
}

unsigned char CNWSCreatureStats_s::GetSTRStat() {
	return CNWSCreatureStats__GetSTRStat(this);
}

unsigned char CNWSCreatureStats_s::GetDEXStat() {
	return CNWSCreatureStats__GetDEXStat(this);
}

unsigned char CNWSCreatureStats_s::GetINTStat() {
	return CNWSCreatureStats__GetINTStat(this);
}

unsigned char CNWSCreatureStats_s::GetWISStat() {
	return CNWSCreatureStats__GetWISStat(this);
}

unsigned char CNWSCreatureStats_s::GetCHAStat() {
	return CNWSCreatureStats__GetCHAStat(this);
}

CExoString CNWSCreatureStats_s::GetAnimalCompanionName() {
	return CNWSCreatureStats__GetAnimalCompanionName(this);
}

CExoString CNWSCreatureStats_s::GetFamiliarName() {
	return CNWSCreatureStats__GetFamiliarName(this);
}

int CNWSCreatureStats::GetSpellMinAbilityMet(unsigned char cls_pos, unsigned char spell_lvl)
{
	return CNWSCreatureStats__GetSpellMinAbilityMet(this,cls_pos,spell_lvl);
}

void CNWSCreatureStats::UpdateCombatInformation()
{
	CNWSCreatureStats__UpdateCombatInformation(this);
}

void CNWSCreatureStats::UpdateNumberMemorizedSpellSlots()
{
	CNWSCreatureStats__UpdateNumberMemorizedSpellSlots(this);
}

void CNWSCreatureStats::AdjustSpellUsesPerDay()
{
	CNWSCreatureStats__AdjustSpellUsesPerDay(this);
}

void CNWSCreatureStats::SetNumberBonusSpells(unsigned char cls_pos, unsigned char spell_lvl, unsigned char mod)
{
	CNWSCreatureStats__SetNumberBonusSpells(this,cls_pos,spell_lvl,mod);
}

void CNWSCreatureStats::DecrementSpellsPerDayLeft(unsigned char cls_pos, unsigned char spell_lvl)
{
	CNWSCreatureStats__DecrementSpellsPerDayLeft(this,cls_pos,spell_lvl);
}

unsigned char CNWSCreatureStats::GetSpellsPerDayLeft(unsigned char cls_pos, unsigned char spell_lvl)
{
	return CNWSCreatureStats__GetSpellsPerDayLeft(this,cls_pos,spell_lvl);
}