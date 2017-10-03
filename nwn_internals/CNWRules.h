#ifndef _NX_NWN_STRUCT_CNWRULES_
#define _NX_NWN_STRUCT_CNWRULES_

#include "CNWSkill.h"

struct CNWRules_s {
	void** m_vtable;//00
    float m_fRangeTypes[5];//0 - personal 04, 1 - touch 08, 2 - short 0C, 3 - medium 10, 4 - long 14
    CNWBaseItemArray* m_pBaseItemArray;//18
    unsigned int m_nExperienceTable[41];//1C
    CNWSpellArray* m_pSpellArray;//C0
    CNWFeat* m_lstFeats;//C4
    unsigned int* m_lstMasterFeats;//C8
    unsigned int* m_lstMasterFeatDescriptions;//CC
    CResRef* m_lstMasterFeatIcons;//D0
    unsigned short* m_lstSortedFeatIDs;//D4
    unsigned short m_nNumFeats;//D8
    unsigned short m_nNumSortedFeats;//DA
    char m_nNumMasterFeats;//DC
    unsigned char m_nNumClasses;//DD
    unsigned char m_nNumRaces;//DE
    unsigned char m_nNumSkills;//DF
    unsigned char m_nNumDomains;//E0
    CNWClass* m_lstClasses;//E4
    CNWRace* m_lstRaces;//E8
    CNWSkill* m_lstSkills;//EC
    CNWDomain* m_lstDomains;//F0
    CTwoDimArrays_s* m_p2DArrays;//F4
    unsigned char m_nDifficultyOptions[5][7];//F8

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