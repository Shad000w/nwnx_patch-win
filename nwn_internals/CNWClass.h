#ifndef _H_CNWCLASS_H_
#define _H_CNWCLASS_H_

/*

CastType
[01] 0 0 0 0 0 0 0 1 - Restrict Spellbook [Show Only Known/ALL (1/0)]
[02] 0 0 0 0 0 0 1 0 - Prepared/Spontaneous (1/0)
[04] 0 0 0 0 0 1 0 0 - Enable spell select at lvl up
[08] 0 0 0 0 1 0 0 0 - Enable spell select at feat/lvl gain
[10] 0 0 0 1 0 0 0 0 - Disable retrain spells
[20] 0 0 1 0 0 0 0 0 - Can learn scrolls
[40] 0 1 0 0 0 0 0 0 - 
[80] 1 0 0 0 0 0 0 0 - Arcane/Divine (1/0)
*/
#define CAST_TYPE_RESTRICTED_SPELLBOOK	0x1
#define CAST_TYPE_SPONTANEOUS			0x2
#define CAST_TYPE_4						0x4
#define CAST_TYPE_SELECT_DOMAINS		0x8
#define CAST_TYPE_SELECT_SPELL_SCHOOL	0x10
#define CAST_TYPE_CUSTOM_SPELL_TYPE     0x20
#define CAST_TYPE_LEARN_FROM_SCROLL		0x40
#define CAST_TYPE_ARCANE				0x80
/*
CastOpt
[01] 0 0 0 0 0 0 0 1 - Can have Companion
[02] 0 0 0 0 0 0 1 0 - Can have Familiar
[04] 0 0 0 0 0 1 0 0 - Select Domains at Creation
[08] 0 0 0 0 1 0 0 0 - Select Schools at Creation
[10] 0 0 0 1 0 0 0 0 - Select Spells at creation
[20] 0 0 1 0 0 0 0 0 - Select Companion at Creation
[40] 0 1 0 0 0 0 0 0 - Select Familiar at Creation
[80] 1 0 0 0 0 0 0 0 -

AlignRestrict
[01] 0 0 0 0 0 0 0 1 - no neutral
[02] 0 0 0 0 0 0 1 0 - no lawful
[04] 0 0 0 0 0 1 0 0 - no chaotic
[08] 0 0 0 0 1 0 0 0 - no good
[10] 0 0 0 1 0 0 0 0 - no evil

AlignRstrctType

0x0 = None
0x1 = Law/Chaos
0x2 = Good/Evil
0x3 = Both
*/

struct CNWClass_Feat
{
    uint16_t nFeat;
    uint8_t nLevelGranted;
    uint8_t nListType;
    int32_t nTalentCategory;
    int32_t nMaxCR;
    int32_t nOnClassRadial;
};

struct CNWClass_Skill
{
    uint16_t nSkill;
    int32_t bClassSkill;
};

struct CNWClass_s {
	uint32_t m_nName;
    uint32_t m_nNameLower;
    uint32_t m_nNamePlural;
    uint32_t m_nDescription;
    CExoString m_sIcon;
    CExoString m_sPreReqTable;
    uint8_t m_lstBaseAttackBonus[60];
    uint8_t m_nHitDie;
    uint8_t m_nSkillPointBase;
    uint8_t m_lstFortificationSaveThrowBonus[60];
    uint8_t m_lstWillSaveThrowBonus[60];
    uint8_t m_lstReflexSaveThrowBonus[60];
    uint8_t** m_lstSpellKnownTable;
    uint8_t m_lstSpellLevelsPerLevel[40];
    uint8_t* m_lstSpellGainTable[40];
    CNWClass_Skill* m_lstSkillTable;
    uint16_t m_nNumSkills;
    CNWClass_Feat* m_lstFeatTable;
    uint16_t m_nNumFeats;
    uint8_t m_lstBonusFeatsTable[40];
    uint8_t m_nPrimaryAbility;
    uint8_t m_pnRecommendedAbilities[6];
    uint8_t m_nClassRestrictions;
    uint8_t m_nClassRestrictionType;
    int32_t m_nClassRestrictionsInversed;
    uint8_t m_pnEffectiveCRForLevel[41];
    int32_t m_bIsPlayerClass;
    int32_t m_bIsSpellCasterClass;
    uint8_t m_nMaxLevel;
    int32_t m_bXPPenalty;
    uint32_t m_nDefaultPackage;
    uint8_t m_nArcSpellUsePerDayLevel;
    uint8_t m_nDivSpellUsePerDayLevel;
    uint8_t m_nEpicLevel;

	CNWClass_s();
	~CNWClass_s();
	unsigned char GetFortSaveBonus(uint8_t Level);
	unsigned char GetWillSaveBonus(uint8_t Level);
	unsigned char GetRefSaveBonus(uint8_t Level);
	unsigned char GetSpellGain(unsigned char cls_lvl, unsigned char spell_lvl);
	//cls_id, race and charisma is ignored
	unsigned char GetSpellsKnownPerLevel(unsigned char cls_lvl, unsigned char spell_lvl, unsigned char cls_id, unsigned short race, unsigned char charisma);

	int IsBonusFeat(unsigned short feat_id);
	int IsNormalFeat(unsigned short feat_id);
	int IsGrantedFeat(unsigned short feat_id, unsigned char &var);
};

#endif