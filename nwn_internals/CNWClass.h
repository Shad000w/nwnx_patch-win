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

struct CNWClass_s {
	uint32_t			name_tlk;
	uint32_t			name_lower_tlk;
	uint32_t			name_plural;
	uint32_t			description_tlk;
	CExoString			Icon;
	CExoString			PreReqTable;
	uint8_t				AttackBonusTable[60];
	uint8_t				HitDie;
	uint8_t				SkillPointBase;
	uint8_t				FortSaveTable[60];
	uint8_t				ReflSaveTable[60];
	uint8_t				WillSaveTable[60];
	uint8_t				byte112;
	uint8_t				byte113;
	void				*SpellsKnown;
	unsigned __int8		NumSpellLevels[40];
	uint32_t			SpellGain[40];
	uint32_t			*SkillsTable;
	uint32_t			SkillsTable_Len;
	uint32_t			*feats;
	uint32_t			feats_len;
	uint8_t				f1f0[38];
	uint8_t				PrimaryAbility;//216
	uint8_t				Str;//217
	uint8_t				Dex;//218
	uint8_t				Con;//219
	uint8_t				Int;//21A
	uint8_t				Wis;//21B
	uint8_t				Cha;//21C
	uint8_t				AlignRestrict;//21D
	uint8_t				AlignRestrictType;//21E
	uint8_t				f21F[1];
	uint32_t			InvertRestrict;//220
	uint32_t			fix;//hm?
	uint8_t				EffCRLvl[40];//224
	uint8_t				PlayerClass;//250
	uint8_t				field251;
	uint8_t				field252;//252
	uint8_t				field253;//253
	uint8_t				SpellCaster;//254
	uint8_t				field255;//255
	uint16_t			field256;
	uint32_t			MaxLevel;
	uint32_t			XPPenalty;//25C
	uint32_t			Package;//260
	uint8_t				ArcSpellLvlMod;
	uint8_t				DivSpellLvlMod;
	uint8_t				EpicLevel;

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