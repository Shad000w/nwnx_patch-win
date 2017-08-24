#ifndef _H_CNWLEVELSTATS_H
#define _H_CNWLEVELSTATS_H

struct CNWLevelStats_s
{
	CExoArrayList_uint32			m_pAddedKnownSpellList[10];
	CExoArrayList_uint32			m_pRemovedKnownSpellList[10];
	CExoArrayList_uint16			m_lstFeats;//F0
	char* m_lstSkillRanks;
    uint16_t m_nSkillPointsRemaining;//100
    uint8_t m_nAbilityGain;//102
    uint8_t m_nHitDie;//103
    uint8_t m_nClass;//104
    int32_t m_bEpic;//105
};

#endif