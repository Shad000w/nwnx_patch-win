#include "stdafx.h"
#include "types.h"
#include "nwn_internals.h"
#include "CNWSCombatAttackData.h"

int (__thiscall *CNWSCombatAttackData__GetDamage)(CNWSCombatAttackData *pTHIS, unsigned short i) = (int(__thiscall*)(CNWSCombatAttackData *pTHIS, unsigned short i))0x52EFD0;
int (__thiscall *CNWSCombatAttackData__GetTotalDamage)(CNWSCombatAttackData *pTHIS, int i) = (int(__thiscall*)(CNWSCombatAttackData *pTHIS, int i))0x52F0F0;

CNWSCombatAttackData* (__thiscall *CNWSCombatAttackData__CNWSCombatAttackData)(CNWSCombatAttackData *pTHIS) = (CNWSCombatAttackData*(__thiscall*)(CNWSCombatAttackData *pTHIS))0x52ECC0;
void (__thiscall *CNWSCombatAttackData___CNWSCombatAttackData)(CNWSCombatAttackData *pTHIS) = (void(__thiscall*)(CNWSCombatAttackData *pTHIS))0x52ED60;


CNWSCombatAttackData_s::CNWSCombatAttackData_s()
{
	CNWSCombatAttackData__CNWSCombatAttackData(this);
}

CNWSCombatAttackData_s::~CNWSCombatAttackData_s() 
{
	CNWSCombatAttackData___CNWSCombatAttackData(this);
}


int CNWSCombatAttackData_s::GetDamage(unsigned short i) 
{
	return CNWSCombatAttackData__GetDamage(this,i);
}

int CNWSCombatAttackData_s::GetTotalDamage(int i) 
{
	return CNWSCombatAttackData__GetTotalDamage(this,i);
}