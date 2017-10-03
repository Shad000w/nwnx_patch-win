#ifndef __CNWFEAT_H__
#define __CNWFEAT_H__

#include "CExoString.h"
#include "CResRef.h"

struct CNWFeat_s {
	int m_nNameStrref;//0x0
    int m_nDescriptionStrref;//0x4
    int m_nTalentCategory;//0x8
    int m_nTalentMaxCR;//0xC
    CResRef m_cIcon;//0x10
    int m_bGainMultiple;//0x20
    int m_bAllClassesCanUse;//0x24
    int m_bTargetSelf;//0x28
    int m_bHostileFeat;//0x2C
    unsigned char m_nMinAttackBonus;//0x30
    unsigned char m_nMinSTR;//0x31
    unsigned char m_nMinDEX;//0x32
    unsigned char m_nMinINT;//0x33
    unsigned char m_nMinWIS;//0x34
    unsigned char m_nMinCON;//0x35
    unsigned char m_nMinCHA;//0x36
    unsigned char m_nMinSpellLevel;//0x37
    unsigned short m_lstPrereqFeats[2];
    unsigned short m_lstOrPrereqFeats[5];
    unsigned short m_nRequiredSkill;//0x48
    unsigned short m_nMinRequiredSkillRank;//4A
    unsigned short m_nRequiredSkill2;//0x4C
    unsigned short m_nMinRequiredSkillRank2;//0x4E
    int m_nSuccessor;//0x50
    char m_nMasterFeat;//0x54
    unsigned char m_nMinLevel;//0x55
    unsigned char m_nMaxLevel;//0x56
    unsigned char m_nMinLevelClass;//0x57
    unsigned char m_nMinFortSave;//0x458
    int m_nSpellId;//0x5C
    unsigned char m_nUsesPerDay;//0x60
    int m_bValidFeat;//0x64
    int m_bRequiresEpic;//0x68
    int m_bRequiresAction;//0x6C
};
#endif