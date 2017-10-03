#ifndef __CNWSKILL_H__
#define __CNWSKILL_H__

#include "CExoString.h"

struct CNWSkill {
    int m_nNameStrref;//0x0
    int m_nDescriptionStrref;//0x4
    int m_nTalentCategory;//0x8
    int m_nTalentMaxCR;//0xC
    CExoString m_sIconName;//0x10
    int m_nKeyAbility;//0x18
    int m_bHostileSkill;//0x1C
    int m_bUntrained;//0x20
    int m_bArmorCheckPenalty;//0x24
    int m_bAllClassesCanUse;//0x28
};
#endif