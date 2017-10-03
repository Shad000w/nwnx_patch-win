#ifndef __CNWRACE_H__
#define __CNWRACE_H__

#include "CExoString.h"

struct CNWRace_s {
	int m_nNameStrref;
    int m_nConverNameStrref;
    int m_nConverNameLowerStrref;
    int m_nNamePluralStrref;
    int m_nDescriptionStrref;
    int m_nDefaultBiographyStrref;
    char m_nSTRAdjust;
    char m_nDEXAdjust;
    char m_nINTAdjust;
    char m_nCHAAdjust;
    char m_nWISAdjust;
    char m_nCONAdjust;
    unsigned char m_nEndurance;
    unsigned char m_nFavoredClass;
    int m_bIsPlayerRace;
    unsigned short m_nNumFeats;
	unsigned short FavoredEnemyFeat;//custom value
    unsigned short* m_lstFeatTable;
    int m_nAge;
    unsigned short m_nDefaultAppearance;
};
#endif