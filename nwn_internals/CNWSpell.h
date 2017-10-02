#ifndef __H_CNWSPELL_H__
#define __H_CNWSPELL_H__

struct CNWSpell_s {
  	CExoString m_sLabel;
    int m_strrefName;
    unsigned int m_strrefDesc;
    CResRef m_resrefIcon;
    unsigned char m_nSchool;
    CExoString m_sRange;
    CExoString m_sComponent;
    unsigned short m_nTargetType;
    CExoString m_sImpactScript;
    unsigned char m_nBardLevel;
    unsigned char m_nClericLevel;
    unsigned char m_nDruidLevel;
    unsigned char m_nPaladinLevel;
    unsigned char m_nRangerLevel;
    unsigned char m_nSorcererLevel;
    unsigned char m_nWizardLevel;
    unsigned char m_nInnateLevel;
    unsigned int m_nConjureTime;
    unsigned short m_nConjureAnimation;
    CResRef m_resrefConjureHeadVisual;
    CResRef m_resrefConjureHandVisual;
    CResRef m_resrefConjureGroundVisual;
    CResRef m_resrefConjureSoundMale;
    CResRef m_resrefConjureSoundFemale;
    CResRef m_resrefConjureSoundVFX;
    unsigned short m_nCastAnimation;
    unsigned int m_nCastTime;
    CResRef m_resrefCastHeadVisual;
    CResRef m_resrefCastHandVisual;
    CResRef m_resrefCastGroundVisual;
    CResRef m_resrefCastSound;
    int m_bProjectileSpawn;
    CResRef m_resrefProjectile;
    unsigned int m_nProjectileType;
    unsigned char m_nProjectileSpawnPoint;
    CResRef m_resrefProjectileSound;
    unsigned char m_nProjectileOrientationType;
    unsigned char m_nImmunityType;
    int m_bImmunityItem;
    int m_nTalentCategory;
    int m_nTalentMaxCR;
    unsigned int* m_pSubRadialSpell;
    unsigned char m_nSubRadialSpellCount;
    int m_bUseConcentration;
    unsigned int m_nMasterSpell;
    unsigned int m_nCounterSpell1;
    unsigned int m_nCounterSpell2;
    unsigned char m_nUserType;
    unsigned char field_145;//custom value
    unsigned char field_146;//custom value
    unsigned char Hidden;//0x147 - custom value
	int m_bSpontaneouslyCast;
    unsigned char m_nAllowedMetamagic;
    unsigned int m_nAltMessage;
    int m_bHostile;
    int m_nFeatId;
    int m_bHasProjectile;

  unsigned char GetSpellLevel(unsigned char cls_id);
};
#endif


