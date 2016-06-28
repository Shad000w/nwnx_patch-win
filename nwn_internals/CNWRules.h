#ifndef _NX_NWN_STRUCT_CNWRULES_
#define _NX_NWN_STRUCT_CNWRULES_

struct CNWRules_s {
	unsigned __int32 field_00;//*v_table ??
	float ru_spell_range_personal;//04
	float ru_spell_range_touch;//08
	float ru_spell_range_short;//0C
	float ru_spell_range_medium;//10
	float ru_spell_range_long;//14
	CNWBaseItemArray *ru_baseitems;//18
	unsigned __int32 ru_xp_level[41];//1C
	CNWSpellArray *ru_spells;//C0
	void *ru_feats;//C4
	unsigned __int32 field_C8;
	unsigned __int32 field_CC;
	unsigned __int32 field_D0;
	unsigned __int16 *ru_sorted_feats;//D4
	unsigned __int16 ru_feats_len;//D8
	unsigned __int16 ru_sorted_feats_len;//DA
	unsigned __int8 ru_unknown_len; //DC
	unsigned __int8 ru_classes_len;//DD
	unsigned __int8 ru_races_len;//DE
	unsigned __int8 ru_skills_len;//DF
	unsigned __int8 ru_domains_len; //E0
	unsigned __int8 field_E1;
	unsigned __int16 field_E2;
	CNWClass *ru_classes;//E4
	CNWRace *ru_races;//E8
	void *ru_skills;//EC
	CNWDomain *ru_domains;//F0
	CTwoDimArrays_s *ru_2das;//F4

	uint8_t GetFeatExpansionLevel(uint16_t FeatID);
	unsigned short RollDice(unsigned char NumDice, unsigned char DieType);
	int IsArcaneClass(unsigned char);
	int GetDifficultyOption(int, int);
	
	CNWSpell* GetSpell(unsigned long spell_id);
	CNWFeat* GetFeat(unsigned short feat);
	CNWDomain* GetDomain(unsigned short domain_id);

	unsigned char GetMetaMagicLevelCost(unsigned char meta_type);

	unsigned char GetFamiliarExpansionLevel(unsigned char type, int famil_or_acomp);

	void LoadClassInfo();
//	int LoadDifficultyInfo();
	void LoadDomainInfo();
	void LoadFeatInfo();
	void LoadRaceInfo();
	void LoadSkillInfo();
};

#endif