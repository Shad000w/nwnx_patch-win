#ifndef _NX_NWN_STRUCT_CNWSCREATURESTATS_
#define _NX_NWN_STRUCT_CNWSCREATURESTATS_

#include "CExoLocString2.h"

struct CNWSStats_SpellLikeAbility_s{

	unsigned long nSpell;
	unsigned long nReady;
	unsigned char bLevel;
};

struct CNWSStats_SpellLikeAbility_s;		typedef struct CNWSStats_SpellLikeAbility_s     CNWSStats_SpellLikeAbility;


struct CNWSCreatureStats_s {
  CExoArrayList_uint16 cs_feats;
  CExoArrayList_ptr cs_featuses;
  CExoArrayList_uint16 cs_skin_feats;
  CNWSCreature *cs_original;
  CExoArrayList_ptr cs_levelstat;
  CExoLocString2 cs_firstname;
  CExoLocString2 cs_lastname;
  char cs_conv[16];
  unsigned int cs_conv_interruptable;
  CExoLocString cs_desc_base;
  CExoLocString cs_desc_override;
  int cs_age;
  unsigned int cs_gender;
  unsigned int cs_xp;
  unsigned int cs_is_pc;
  unsigned int cs_is_dm;
  unsigned int field_7C;
  unsigned int field_80;
  unsigned int cs_ai_disabled;
  unsigned int field_88;
  unsigned int cs_mclasslevupin;
  unsigned int cs_faction_id;
  unsigned int cs_faction_orig;
  unsigned int cs_faction_predom;
  float cs_cr;
  unsigned __int8 cs_starting_package;
  unsigned __int8 cs_classes_len;
  unsigned __int8 field_9A;
  unsigned __int8 field_9B;
  CNWSCreatureStats_ClassInfo cs_classes[3];
  unsigned __int16 cs_race;//3EC
  unsigned __int16 field_3EE;
  CExoString cs_subrace;
  unsigned __int8 cs_str;
  char cs_str_mod;
  unsigned __int8 cs_dex;
  char cs_dex_mod;
  unsigned __int8 cs_con;
  char cs_con_mod;
  unsigned __int8 cs_int;
  char cs_int_mod;
  unsigned __int8 cs_wis;
  char cs_wis_mod;
  unsigned __int8 cs_cha;
  char cs_cha_mod;
  char cs_ac_natural_base;
  char cs_ac_armour_base;
  char cs_ac_shield_base;
  char cs_ac_armour_bonus;
  char cs_ac_armour_penalty;
  char cs_ac_deflection_bonus;
  char cs_ac_deflection_penalty;
  char cs_ac_shield_bonus;
  char cs_ac_shield_penalty;
  char cs_ac_natural_bonus;
  char cs_ac_natural_penalty;
  char cs_ac_dodge_bonus;
  char cs_ac_dodge_penalty;
  unsigned __int8 cs_override_bab;
  unsigned __int8 field_412;
  unsigned __int8 field_413;
  unsigned int field_414;
  unsigned int field_418;
  unsigned int field_41C;
  unsigned int field_420;
  unsigned int field_424;
  CCombatinformation *cs_combat_info;
  char m_nArcaneSpellFailure;//42C
  uint8_t m_nBaseArmorArcaneSpellFailure;//42D
  uint8_t m_nBaseShieldArcaneSpellFailure;//42E
  uint8_t m_pSpellFailure[9];//42F
  char m_nSpellResistance;//438
  char m_nSpellResistancePenalty;//439
  CExoArrayList_2<CNWSStats_SpellLikeAbility> *cs_specabil;
 	uint16_t m_nTempHitpointsPtr;
	uint16_t m_nACVersusPtr;
	uint16_t m_nAttackBonusPtr;
	uint16_t m_nDamageReductionPtr;
	uint16_t m_nDamageResistancePtr;
	uint16_t m_nDamageBonusPtr;
	uint16_t m_nAIStatePtr;
	uint16_t m_nEffectIconPtr;
	uint16_t m_nSanctuaryPtr;
	uint16_t m_nInvisibilityPtr;
	uint16_t m_nSpellResistancePtr;
	uint16_t m_nAbilityPtr;
	uint16_t m_nSeeInvisiblePtr;
	uint16_t m_nUltraVisionPtr;
	uint16_t m_nMissChancePtr;
	uint16_t m_nConcealmentPtr;
	uint16_t m_nBlindnessPtr;
	uint16_t m_nWalkAnimationPtr;
	uint16_t m_nSpellLevelAbsorptionPtr;
	uint16_t m_nSpellImmunityPtr;
	uint16_t m_nDamageShieldPtr;
	uint16_t m_nSkillBonusPtr;
	uint16_t m_nSavingThrowBonusPtr;
	uint16_t m_nHastePtr;
	uint16_t m_nEffectImmunityPtr;
	uint16_t m_nLimitMovementSpeedPtr;
	uint16_t m_nMovementSpeedDecreasePtr;
	uint16_t m_nSkillPointsRemaining;
	char* m_lstSkillRanks;
	char m_nArmorCheckPenalty;
	char m_nShieldCheckPenalty;
	CResRef m_cPortrait;
  unsigned __int8 cs_al_goodevil;
  unsigned __int8 field_48F;
  unsigned __int8 cs_al_lawchaos;
  unsigned __int8 field_491;
  unsigned __int8 cs_color_skin;
  unsigned __int8 cs_color_hair;
  unsigned __int8 cs_color_tattoo_1;
  unsigned __int8 cs_color_tattoo_2;
  unsigned __int16 cs_appearance;
  unsigned __int8 cs_phenotype;
  unsigned __int8 cs_appearance_head;
  unsigned __int8 cs_bodypart_rfoot;
  unsigned __int8 cs_bodypart_lfoot;
  unsigned __int8 cs_bodypart_rshin;
  unsigned __int8 cs_bodypart_lshin;
  unsigned __int8 cs_bodypart_lthigh;
  unsigned __int8 cs_bodypart_rthigh;
  unsigned __int8 cs_bodypart_pelvis;
  unsigned __int8 cs_bodypart_torso;
  unsigned __int8 cs_bodypart_belt;
  unsigned __int8 cs_bodypart_neck;
  unsigned __int8 cs_bodypart_rfarm;
  unsigned __int8 cs_bodypart_lfarm;
  unsigned __int8 cs_bodypart_rbicep;
  unsigned __int8 cs_bodypart_lbicep;
  unsigned __int8 cs_bodypart_rshoul;
  unsigned __int8 cs_bodypart_lshoul;
  unsigned __int8 cs_bodypart_rhand;
  unsigned __int8 cs_bodypart_lhand;
  unsigned __int8 field_4AC;
  unsigned __int8 cs_tail_old;
  unsigned __int8 cs_wings_old;
  unsigned __int8 field_4AF;
  unsigned int cs_tail;
  unsigned int cs_wings;
  unsigned int cs_movement_rate;
  unsigned int cs_runrate;
  unsigned int cs_walkrate;
  char cs_save_fort;
  char cs_save_will;
  char cs_save_reflex;
  unsigned __int8 field_4C7;
  unsigned int cs_acomp_type;
  unsigned int cs_famil_type;
  CExoString cs_acomp_name;
  CExoString cs_famil_name;
  char *cs_deity;

void 				AddExperience(uint32_t XP);
void				AddKnownSpell(unsigned char cls_pos, unsigned long spell_id);
char 				AddFeat(uint16_t Feat);
void				RemoveFeat(uint16_t Feat);
char				GetACNaturalBase(int bTouchAttack);
int 				GetAttackModifierVersus(CNWSCreature *Vs);
//unsigned char 	GetAttacksPerRound();
int 				GetBaseAttackBonus(int bPreEpicOnly);
int					GetCriticalHitMultiplier(int bOffhand);
int 				GetCanUseSkill(unsigned char Skill);
unsigned char		GetCONStat();
char 				GetDEXMod(int bMaxArmorDex);
signed int 			GetEpicWeaponFocus(CNWSItem *weapon);
int 				GetEffectImmunity(unsigned __int8 Type, CNWSCreature *a3_Versus);
int 				GetFavoredEnemyBonus(CNWSCreature *cre_enemy);
char 				GetFortSavingThrow(int bBaseOnly);
char 				GetWillSavingThrow(int bBaseOnly);
char 				GetReflexSavingThrow(int bBaseOnly);
unsigned long 		GetHighestLevelKnown();
unsigned short		GetNumberKnownSpells(unsigned char cls_pos, unsigned char spell_level);
unsigned long		GetKnownSpell(unsigned char cls_pos, unsigned char spell_id, unsigned char spell_level);
unsigned long		GetMemorizedSpellInSlot(unsigned char c1, unsigned char c2, unsigned char c3);
unsigned char		GetMemorizedSpellInSlotReady(unsigned char c1, unsigned char c2, unsigned char c3); 
unsigned char		GetMemorizedSpellInSlotMetaType(unsigned char c1, unsigned char c2, unsigned char c3);
unsigned char		GetNumberMemorizedSpellSlots(unsigned char cls_pos, unsigned char spell_level);
unsigned char		GetSpellsOfLevelReady(unsigned char cls_pos, unsigned char spell_level);
unsigned char		GetSpellGainWithBonus(unsigned char cls_pos, unsigned char spell_level);
int 				GetIsWeaponOfChoice(uint32_t BaseItemType);
unsigned char		GetLevel(int bCountNegativeLevels);
int					GetMeleeAttackBonus(int a1, int a2, int a3);
char				GetSkillRank(unsigned char Skill, CNWSObject *vsObj, int bBaseRanksOnly);
unsigned char		GetUnarmedDamageDice();
unsigned char		GetUnarmedDamageDie();
int 				GetUseMonkAttackTables(int a1);
signed int 			GetWeaponFinesse(CNWSItem *weapon);
signed int 			GetWeaponFocus(CNWSItem *weapon);
signed int 			GetWeaponImprovedCritical(CNWSItem *weapon);
int 				HasFeat(uint16_t feat);
bool 				LevelUp(CNWLevelStats *a2, int a3, char a4, char a5, int a6);
void				ReadySpellLevel(unsigned char SpellLevel);
void 				ResetFeatRemainingUses();
void 				ResetSpellLikeAbilities();
int 				ResolveSpecialAttackAttackBonus(CNWSCreature *Defender);
unsigned char		GetSimpleAlignmentGoodEvil();
unsigned char		GetSimpleAlignmentLawChaos();
unsigned char		GetFeatSourceClass(unsigned short nFeat);

void				SetCHABase(uint8_t CHABase);
void				SetCONBase(uint8_t CONBase, int a3);
void				SetDEXBase(uint8_t DEXBase);
void				SetINTBase(uint8_t INTBase);
void				SetSTRBase(uint8_t STRBase);
void				SetWISBase(uint8_t WISBase);

void				SetMovementRate(uint8_t MOVrate);
int					SetMemorizedSpellSlot(unsigned char a1, unsigned char a2, unsigned long spell_id, unsigned char a3, unsigned char a4, int unknown);

unsigned char 		GetCHAStat();
unsigned char 		GetDEXStat();
unsigned char 		GetINTStat();
unsigned char 		GetSTRStat();
unsigned char 		GetWISStat();
char				GetTotalSTRBonus();
char				GetTotalDEXBonus();
char				GetTotalCONBonus();
char				GetTotalINTBonus();
char				GetTotalWISBonus();
char				GetTotalCHABonus();

int16_t				GetDamageRoll(CNWSObject *Defender, int bOffHand, int AttackResult, int SneakAttack, int DeathAttack, int a7);
CNWSCreatureStats_ClassInfo*	GetInfo(unsigned char cls);
unsigned char		GetClassLevel(unsigned char cls_pos, int bCountNegativeLevels);
unsigned char		GetClass(unsigned char cls_pos);
int GetNumLevelsOfClass(unsigned char nClassType);
int GetNumLevelsOfClass(unsigned char nClassType, int bPreEpicOnly); 
unsigned char GetFeatTotalUses(unsigned short feat_id);
uint8_t GetFeatRemainingUses(uint16_t FeatID);
void DecrementFeatRemainingUses(uint16_t FeatID);
void SetFeatRemainingUses(unsigned short feat_id, unsigned char feat_uses);
unsigned char GetIsClass(unsigned char ClassType);
int GetArmorClassVersus(CNWSCreature *Attacker, int bTouchAttack);
int GetRangedAttackBonus( int arg1, int arg2);
CExoString GetAnimalCompanionName();
CExoString GetFamiliarName();
int					GetSpellMinAbilityMet(unsigned char cls_pos, unsigned char spell_lvl);
void				UpdateCombatInformation();
	void UpdateNumberMemorizedSpellSlots();
	void AdjustSpellUsesPerDay();
	void SetNumberBonusSpells(unsigned char cls_pos, unsigned char spell_lvl, unsigned char mod);
	void DecrementSpellsPerDayLeft(unsigned char cls_pos, unsigned char spell_lvl);
	unsigned char GetSpellsPerDayLeft(unsigned char cls_pos, unsigned char spell_lvl);
	void ComputeFeatBonuses(CExoArrayList_uint16 *list, int arg1, int arg2);
};


#endif
