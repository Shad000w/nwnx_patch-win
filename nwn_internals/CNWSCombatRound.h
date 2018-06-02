#ifndef _NX_NWN_STRUCT_CNWSCOMBATROUND_
#define _NX_NWN_STRUCT_CNWSCOMBATROUND_
 
struct CNWSCombatRound_s
{
	CNWSCombatAttackData AttackData[50];				/* 0x0/0 */ 
	CExoArrayList_2<uint16_t> *SpecialAttackList;		/* 0x20D0/8400 *///crashes
	unsigned long SpecialAttackCount;					/* 0x20D4/8404 */
	unsigned long field_20D8;							/* 0x20D8/8408 */
	CExoArrayList_2<uint16_t> *SpecAttackIdList;		/* 0x20DC/8412 *///crashes
	unsigned long SpecialAttackIdCount;					/* 0x20E0/8416 */
	unsigned long field_20E4;							/* 0x20E4/8420 */
/* 0x20E8/8424 */    uint16_t m_nAttackID;
/* 0x20EC/8428 */    int32_t m_bRoundStarted;
/* 0x20F0/8432 */    int32_t m_bSpellCastRound;
/* 0x20F4/8436 */    int32_t m_nTimer;
/* 0x20F8/8440 */    int32_t m_nRoundLength;
/* 0x20FC/8444 */    int32_t m_nOverlapAmount;
/* 0x2100/8448 */    int32_t m_nBleedAmount;
/* 0x2104/8452 */    int32_t m_bRoundPaused;
/* 0x2108/8456 */    uint32_t m_oidRoundPausedBy;
/* 0x210C/8460 */    int32_t m_nPauseTimer;
/* 0x2110/8464 */    int32_t m_bInfinitePause;
/* 0x2114/8468 */    uint8_t m_nCurrentAttack;
/* 0x2115/8469 */    uint8_t m_nAttackGroup;
/* 0x2118/8472 */    int32_t m_bDeflectArrow;
/* 0x211C/8476 */    int32_t m_bWeaponSucks;
/* 0x2120/8480 */    int32_t m_bEpicDodgeUsed;
/* 0x2124/8484 */    int32_t m_nParryIndex;
/* 0x2128/8488 */    int32_t m_nAttacksOfOpportunity;
/* 0x212C/8492 */    int32_t m_nCleaveAttacks;
/* 0x2130/8496 */    int32_t m_nCircleKickAttacks;
/* 0x2134/8500 */    uint32_t m_oidNewAttackTarget;
/* 0x2138/8504 */    int32_t m_nOnHandAttacks;
/* 0x213C/8508 */    int32_t m_nOffHandAttacks;
/* 0x2140/8512 */    int32_t m_nOffHandAttacksTaken;
/* 0x2144/8516 */    int32_t m_nExtraAttacksTaken;
/* 0x2148/8520 */    int32_t m_nAdditionalAttacks;
/* 0x214C/8524 */    int32_t m_nBonusEffectAttacks;
/* 0x2150/8528 */    uint8_t m_nParryActions;
/* 0x2154/8532 */    uint32_t m_oidDodgeTarget;
/* 0x2158/8536 */    uint32_t *m_pScheduledActions;
/* 0x215C/8540 */	 CNWSCreature *m_pBaseCreature;

	void		ClearAllAttacks();
	CNWSItem *	GetCurrentAttackWeapon(int a2);
	void		StartCombatRound(nwn_objid_t oidDefender);
	CNWSCombatAttackData *GetAttack(int a2);
	int GetWeaponAttackType();
	void UpdateAttackTargetForAllActions(unsigned long target);
	void AddSpecialAttack(unsigned short nFeat);

};

#endif