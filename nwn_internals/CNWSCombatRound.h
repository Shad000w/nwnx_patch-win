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
	unsigned long AttackID;								/* 0x20E8/8424 */
	unsigned long RoundStarted;							/* 0x20EC/8428 */
	unsigned long SpellCastRound;						/* 0x20F0/8432 */
	unsigned long Timer;								/* 0x20F4/8436 */
	unsigned long RoundLength;							/* 0x20F8/8440 */
	unsigned long OverlapAmount;						/* 0x20FC/8444 */
	unsigned long BleedTimer;							/* 0x2100/8448 */
	unsigned long RoundPaused;							/* 0x2104/8452 */
	unsigned long RoundPausedBy;						/* 0x2108/8456 */
	unsigned long PauseTimer;							/* 0x210C/8460 */
	unsigned long InfinitePause;						/* 0x2110/8464 */
	char CurrentAttack;									/* 0x2114/8468 */
	char AttackGroup;									/* 0x2115/8469 */
	char rsvd1[2];										/* 0x2118/8472 */
	unsigned long DeflectArrow;							/* 0x2118/8472 */
	unsigned long WeaponSucks;							/* 0x211C/8476 */
	unsigned long EpicDodgeUsed;						/* 0x2120/8480 */
	unsigned long ParryIndex;							/* 0x2124/8484 */
	unsigned long NumAOOs;								/* 0x2128/8488 */
	unsigned long NumCleaves;							/* 0x212C/8492 */
	unsigned long NumCircleKicks;						/* 0x2130/8496 */
	unsigned long NewAttack;							/* 0x2134/8500 */
	unsigned long OnHandAttacks;						/* 0x2138/8504 */
	unsigned long OffHandAttacks;						/* 0x213C/8508 */
	unsigned long OffHandTaken;							/* 0x2140/8512 */
	unsigned long ExtraTaken;							/* 0x2144/8516 */
	unsigned long AdditAttacks;							/* 0x2148/8520 */
	unsigned long EffectAttacks;						/* 0x214C/8524 */
	unsigned long ParryActions;							/* 0x2150/8528 */
	unsigned long DodgeTarget;							/* 0x2154/8532 */
	CExoLinkedList *SchedActionList;					/* 0x2158/8536 */
	CNWSCreature *Creature;								/* 0x215C/8540 */

	void		ClearAllAttacks();
	CNWSItem *	GetCurrentAttackWeapon(int a2);
	void		StartCombatRound(nwn_objid_t oidDefender);
	CNWSCombatAttackData *GetAttack(int a2);
	int GetWeaponAttackType();
	void UpdateAttackTargetForAllActions(unsigned long target);

};

#endif