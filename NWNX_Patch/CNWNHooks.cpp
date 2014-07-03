#include "CNWNHooks.h"
#include "../NWNXdll/madCHook.h"
#include "../NWNXdll/IniFile.h"
#include "NWNXPatch.h"
#include "CExoString.h"
#include "CVirtualMachine.h"
#include "nwn_internals.h"
#include "types.h"
#include <iostream>
#include <stdio.h>

extern CNWNXPatch Patch;

int (__fastcall *CNWSEffectListHandler__OnApplyCurse)(CNWSEffectListHandler *pThis, void*, CNWSObject *obj, CGameEffect *eff, int i);
int (__fastcall *CNWSEffectListHandler__OnApplyAbilityDecrease)(CNWSEffectListHandler *pThis, void*, CNWSObject *obj, CGameEffect *eff, int i);
int (__fastcall *CNWSCreatureStats__GetEffectImmunity)(CNWSCreatureStats *pThis, void*, unsigned char c, CNWSCreature *cre);
int (__fastcall *CNWSCreatureStats__GetWeaponFocus)(CNWSCreatureStats *pThis, int edx, CNWSItem *item);
void (__fastcall *CNWSCreature__ResolveAttack)(CNWSCreature *pThis, void*, unsigned long target, int i, int i2);
int (__fastcall *CNWSCreature__UseItem)(CNWSCreature *pThis, void*, unsigned long l1, unsigned char c1, unsigned char c2, unsigned long l2, Vector v, unsigned long l3);
int (__fastcall *CNWSCreature__CanUseItem)(CNWSCreature *pThis, void*, CNWSItem *item, int a1);
void (__fastcall *CNWSCreature__SummonAssociate)(CNWSCreature *pThis, void*, CResRef resref, char *name, uint32_t len, uint16_t type);
void (__fastcall *CNWSCreature__SummonAnimalCompanion)(CNWSCreature *pThis, void*);
void (__fastcall *CNWSCreature__SummonFamiliar)(CNWSCreature *pThis, void*);
unsigned long (__fastcall *CNWSCreature__GetAssociateId)(CNWSCreature *pThis, void*, unsigned short type, int th);
int (__fastcall *CNWSCreature__AddEquipItemActions)(CNWSCreature *pThis, void*, CNWSItem *item, unsigned long l1, int i1, int i2, unsigned long l2);
int (__fastcall *CNWSCreatureStats__GetCriticalHitRoll)(CNWSCreatureStats *pThis, void*, int n);
CNWSItem* (__fastcall *CNWSCombatRound__GetCurrentAttackWeapon)(CNWSCombatRound *pThis, void*, int n);
void (__fastcall *CNWSCreature__ResolveDamageShields)(CNWSCreature *pThis, void*, CNWSCreature *attacker);
int (__fastcall *CNWSCreature__GetRelativeWeaponSize)(CNWSCreature *pThis, void*, CNWSItem *weapon);
int (__fastcall *CNWSItemPropertyHandler__ApplyHolyAvenger)(CNWSItemPropertyHandler *pThis, void*, CNWSItem *item, int *ip, CNWSCreature *cre, unsigned long l, int i);
int (__fastcall *CNWSItemPropertyHandler__RemoveHolyAvenger)(CNWSItemPropertyHandler *pThis, void*, CNWSItem *item, int *ip, CNWSCreature *cre, unsigned long l);
void (__fastcall *CNWSCreature__SetCombatMode)(CNWSCreature *pThis, void*, unsigned char arg1, int arg2);
int (__fastcall *CNWSCreature__ToggleMode)(CNWSCreature *pThis, void *, unsigned char arg1);
void (__fastcall *CNWSCreature__ResolveAmmunition)(CNWSCreature *pThis, int edx, unsigned long l);

int __fastcall CNWSItemPropertyHandler__RemoveHolyAvenger_Hook(CNWSItemPropertyHandler *pThis, void*, CNWSItem *item, int *ip, CNWSCreature *cre, unsigned long l)
{
	unsigned int nEffect = 0;
	while(nEffect < cre->obj.obj_effects_len)
	{
		CGameEffect* e = *(cre->obj.obj_effects+nEffect);
		if(/*e->eff_dursubtype == 3 && */e->eff_spellid == 538 && e->eff_creator == item->obj.obj_generic.obj_id)
		{
			cre->obj.RemoveEffect(e);
			continue;
		}
		nEffect++;
	}
	return 1;
}

int __fastcall CNWSItemPropertyHandler__ApplyHolyAvenger_Hook(CNWSItemPropertyHandler *pThis, void*, CNWSItem *item, int *ip, CNWSCreature *cre, unsigned long l, int i)
{
	for(unsigned int nEffect=0; nEffect < cre->obj.obj_effects_len; nEffect++)
	{
		CGameEffect* e = *(cre->obj.obj_effects+nEffect);
		e->eff_id_02 = 538;
	}
	int retVal = CNWSItemPropertyHandler__ApplyHolyAvenger(pThis,NULL,item,ip,cre,l,i);
	for(unsigned int nEffect=0; nEffect < cre->obj.obj_effects_len; nEffect++)
	{
		CGameEffect* e = *(cre->obj.obj_effects+nEffect);
		if(e->eff_id_02 == 538)
		{
			e->eff_id_02 = 0;
		}
		else
		{
			e->eff_spellid = 538;
		}
	}
	return retVal;
}

int __fastcall CNWSCreature__GetRelativeWeaponSize_Hook(CNWSCreature *pThis, void*, CNWSItem *weapon)
{//NOTE: good place for Oversized two weapon fighting feat
	if(pThis != NULL && weapon != NULL && weapon->it_container_obj != pThis->obj.obj_generic.obj_id)
	{
		return CNWSCreature__GetRelativeWeaponSize((CNWSCreature*)(*NWN_AppManager)->app_server->GetGameObject(weapon->it_container_obj), NULL, weapon);
	}
	return CNWSCreature__GetRelativeWeaponSize(pThis, NULL, weapon);
}

void __fastcall CNWSCreature__ResolveDamageShields_Hook(CNWSCreature *pThis, void*, CNWSCreature *attacker)
{
	bool change = false;
	if(pThis != NULL && attacker != NULL)
	{
		for(unsigned int nEffect = 0; nEffect < pThis->obj.obj_effects_len; nEffect++)
		{
			CGameEffect* e = *(pThis->obj.obj_effects+nEffect);
			if(e->eff_type == EFFECT_TRUETYPE_DAMAGE_SHIELD)
			{
				if(e->eff_spellid == 84)//holy aura
				{
					if(attacker->cre_stats->GetSimpleAlignmentGoodEvil() != ALIGNMENT_EVIL)
					{
						e->eff_integers[3] = e->eff_integers[0];
						e->eff_integers[4] = e->eff_integers[1];
						e->eff_integers[5] = e->eff_integers[2];
						e->eff_integers[0] = 0;
						e->eff_integers[1] = 0;
						e->eff_integers[2] = 0;
						change = true;
					}
				}
				else if(e->eff_spellid == 187)//unholy aura
				{
					if(attacker->cre_stats->GetSimpleAlignmentGoodEvil() != ALIGNMENT_GOOD)
					{
						e->eff_integers[3] = e->eff_integers[0];
						e->eff_integers[4] = e->eff_integers[1];
						e->eff_integers[5] = e->eff_integers[2];
						e->eff_integers[0] = 0;
						e->eff_integers[1] = 0;
						e->eff_integers[2] = 0;
						change = true;
					}
				}
			}
		}
	}
	CNWSCreature__ResolveDamageShields(pThis, NULL, attacker);
	if(change)
	{
		for(unsigned int nEffect = 0; nEffect < pThis->obj.obj_effects_len; nEffect++)
		{
			CGameEffect* e = *(pThis->obj.obj_effects+nEffect);
			if(e->eff_type == 61 && e->eff_integers[0] == 0)
			{
					e->eff_integers[0] = e->eff_integers[3];
					e->eff_integers[1] = e->eff_integers[4];
					e->eff_integers[2] = e->eff_integers[5];
			}
		}
	}
}

CNWSItem* __fastcall CNWSCombatRound__GetCurrentAttackWeapon_Hook(CNWSCombatRound *pThis, void*, int n)
{
	if(Patch.hand)
	{
		unsigned long slot = Patch.hand;
		Patch.hand = 0;
		return pThis->org_nwcreature->cre_equipment->GetItemInSlot(slot);//fix for Ki critical for offhand weapons
	}
	return CNWSCombatRound__GetCurrentAttackWeapon(pThis, NULL, n);
}

int __fastcall CNWSCreatureStats__GetCriticalHitRoll_Hook(CNWSCreatureStats *pThis, void*, int n)
{
	if(pThis != NULL && pThis->cs_original->obj.obj_generic.obj_type == 5)
	{
		Patch.hand = (n+1)*16;
	}
	return CNWSCreatureStats__GetCriticalHitRoll(pThis, NULL, n);
}

void __fastcall CNWSCreature__ResolveAttack_Hook(CNWSCreature *pThis, void*, unsigned long target, int i, int i2)
{
	nwn_objid_t target_prev = pThis->cre_attack_target;
	CNWSCreature__ResolveAttack(pThis, NULL, target, i, i2);
	if(pThis->cre_combat_round->NumCircleKicks == 0 && target_prev != OBJECT_INVALID && target_prev != target) 
	{
		pThis->cre_combat_round->NumCircleKicks = -1;
		CNWSObject* object = (CNWSObject*)((*NWN_AppManager)->app_server->GetGameObject(target_prev));
		if(object != NULL && !object->GetDead())
		{
			CNWSAction* action = pThis->obj.obj_ai_action;
			if(action)
			{
				action->act_target = target_prev;
			}
		}
	}
}

int __fastcall CNWSCreatureStats__GetWeaponFocus_Hook(CNWSCreatureStats *pThis, int edx, CNWSItem *item)
{
	if(item && ((CNWSItem*)item)->it_baseitemtype == 95)
	{
		return pThis->HasFeat(1072);
	}
	return CNWSCreatureStats__GetWeaponFocus(pThis, edx, item);
}

int __fastcall CNWSCreatureStats__GetEffectImmunity_Hook(CNWSCreatureStats *pThis, void*, unsigned char c, CNWSCreature *cre)
{
	if((Patch.helper == 32 && c == IMMUNITY_TYPE_ABILITY_DECREASE) || (Patch.helper == 33 && c == IMMUNITY_TYPE_MIND_SPELLS))
	{
		return 0;
	}
	return CNWSCreatureStats__GetEffectImmunity(pThis,NULL,c,cre);
}

int __fastcall CNWSEffectListHandler__OnApplyCurse_Hook(CNWSEffectListHandler *pThis, void*, CNWSObject *obj, CGameEffect *eff, int i)
{
	if((*NWN_AppManager)->app_server->srv_internal->ServerInfo->game_diff > 2)//DnD rules or Very high difficulty
	{
		eff->eff_id_02 = 333;
	}
	return CNWSEffectListHandler__OnApplyCurse(pThis,NULL,obj,eff,i);
}

int __fastcall CNWSEffectListHandler__OnApplyAbilityDecrease_Hook(CNWSEffectListHandler *pThis, void*, CNWSObject *obj, CGameEffect *eff, int i)
{	//effect comes from an equipped item or it comes from a curse and the game difficulty is DnD rules or Very high
	if(eff && eff->eff_dursubtype == 3 || eff->eff_id_02 == 333)
	{
		int prev = Patch.helper;
		Patch.helper = 32;
		int retVal = CNWSEffectListHandler__OnApplyAbilityDecrease(pThis,NULL,obj,eff,i);
		Patch.helper = prev;
		return retVal;
	}
	/*if((*NWN_AppManager)->app_server->srv_internal->ServerInfo->game_diff > 2)//DnD rules or Very high difficulty
	{
		if(eff->eff_creator != NULL)
		{
			CGenericObject *creator = (*NWN_AppManager)->app_server->GetGameObject(eff->eff_creator);
			Patch.Log(1,"o ability decrease creator tag %s\n",creator->obj_tag);//todo || eff->eff_spellid == 129 || eff->eff_spellid == 27 || eff->eff_spellid == 613)
			if(creator->obj_tag == "70_EC_POISON" || creator->obj_tag == "70_EC_DISEASE")//creator is Community Pa POISON or DISEASE engine
			{
				int prev = Patch.helper;
				Patch.helper = 32;
				int retVal = CNWSEffectListHandler__OnApplyAbilityDecreaseNext(pThis,NULL,obj,eff,nDecrease);
				Patch.helper = prev;
				return retVal;
			}
		}
	}*/
	return CNWSEffectListHandler__OnApplyAbilityDecrease(pThis,NULL,obj,eff,i);
}

int __fastcall CNWSCreature__AddEquipItemActions_Hook(CNWSCreature *pThis, void*, CNWSItem *item, unsigned long l1, int i1, int i2, unsigned long l2)
{
	if(pThis != NULL && item != NULL && pThis->cre_is_pc && item == pThis->cre_equipment->GetItemInSlot(l1))//double equip exploit
	{
		return 0;
	}
	return CNWSCreature__AddEquipItemActions(pThis,NULL,item,l1,i1,i2,l2);
}

int __fastcall CNWSCreature__CanUseItem_Hook(CNWSCreature *pThis, void*, CNWSItem *item, int a1)
{
	if(pThis != NULL && item != NULL && pThis->cre_is_pc && pThis->cre_pm_IsPolymorphed)
	{
		int props = (*NWN_Rules)->ru_baseitems->GetBaseItem(item->it_baseitemtype)->PropColumn;
		//bool potion = item->it_baseitemtype == 49 || item->it_baseitemtype == 104;
		//bool wand = item->it_baseitemtype == 44 || item->it_baseitemtype == 46;
		//bool healkit = item->it_baseitemtype == 39;
		//bool trap = item->it_baseitemtype == 64;
		//bool thieftool = item->it_baseitemtype == 62;
		//bool container = (*NWN_Rules)->ru_baseitems->GetBaseItem(item->it_baseitemtype)->Container;
		//bool misc = container || props == 15;//any miscs, book
		if(props >= 8 && props <= 12 || props == 4 || props == 15 || props == 18 || props == 19)
		{
			pThis->cre_pm_IsPolymorphed = 0;
			int orig = CNWSCreature__CanUseItem(pThis,NULL,item,a1);
			pThis->cre_pm_IsPolymorphed = 1;
			if(!orig) return 0;
			int poly = -1;
			for(unsigned int nEffect = 0; nEffect < pThis->obj.obj_effects_len; nEffect++)
			{
				CGameEffect* e = *(pThis->obj.obj_effects+nEffect);
				if(e->eff_type == EFFECT_TRUETYPE_POLYMORPH)
				{
					poly = e->eff_integers[0];
					break;
				}
			}
			if(poly > -1)
			{
				CExoString ExoString = "UseItems";
				(*NWN_Rules)->ru_2das->tda_polymorph->GetINTEntry_strcol(poly, ExoString, &poly);
				return poly > 0 || (props == 8 && poly > -1);
			}
		}
	}
	return CNWSCreature__CanUseItem(pThis,NULL,item,a1);
}

int __fastcall CNWSCreature__UseItem_Hook(CNWSCreature *pThis, void*, unsigned long l1, unsigned char c1, unsigned char c2, unsigned long l2, Vector v, unsigned long l3)
{
	if(pThis != NULL && pThis->cre_is_pc && pThis->cre_pm_IsPolymorphed)
	{
		CNWSItem* item = ((CNWSObject*)((*NWN_AppManager)->app_server->GetGameObject(l1)))->AsNWSItem();
		if(item != NULL && (*NWN_Rules)->ru_baseitems->GetBaseItem(item->it_baseitemtype)->equipableSlots == 0 && pThis->CanUseItem(item,c1))
		{
			pThis->cre_pm_IsPolymorphed = 0;
			int retVal = CNWSCreature__UseItem(pThis,NULL,l1,c1,c2,l2,v,l3);
			pThis->cre_pm_IsPolymorphed = 1;
			return retVal;
		}
	}
	return CNWSCreature__UseItem(pThis,NULL,l1,c1,c2,l2,v,l3);
}

void __fastcall CNWSCreature__SummonAssociate_Hook(CNWSCreature *pThis, void*, CResRef resref, char *name, uint32_t len, uint16_t type)
{
	if(pThis->obj.obj_vartable.GetString(CExoString("NWNX!PATCH!SETSUMMONEDRESREF")) != NULL)
	{
		char *var = pThis->obj.obj_vartable.GetString(CExoString("NWNX!PATCH!SETSUMMONEDRESREF"))->text;
		pThis->obj.obj_vartable.DestroyString(CExoString("NWNX!PATCH!SETSUMMONEDRESREF"));
		if(strlen(var) < 16)
		{
			for ( size_t i = 0; i < 16; ++i ) 
			{
			var[i] = tolower(var[i]);
			}
			std::fill_n(resref.resref, 16, 0);
			sprintf(resref.resref,"%s",var);
		}
	}
	CNWSCreature__SummonAssociate(pThis,NULL,resref,name,len, type);
}

unsigned long __fastcall CNWSCreature__GetAssociateId_Hook(CNWSCreature *pThis, void*, unsigned short type, int th)
{
	if(type == 2 && pThis->cre_summoned_acomp > 1)
	{
		return pThis->cre_summoned_acomp;
	}
	else if(type == 3 && pThis->cre_summoned_acomp > 1 && Patch.helper == 31)
	{
		unsigned long retVal = CNWSCreature__GetAssociateId(pThis,NULL,type,th);
		if(retVal == pThis->cre_summoned_acomp)
			return CNWSCreature__GetAssociateId(pThis,NULL,type,2);
		else
			return retVal;
	}
	return CNWSCreature__GetAssociateId(pThis,NULL,type,th);
}

void __fastcall CNWSCreature__SummonAnimalCompanion_Hook(CNWSCreature *pThis, void*)
{
	CNWSCreature__SummonAnimalCompanion(pThis,NULL);
	unsigned long animalID = CNWSCreature__GetAssociateId(pThis,NULL,2,1);
	if(animalID != NULL && animalID != 0x7F000000)
	{
		CNWSCreature *animal = (CNWSCreature*)(*NWN_AppManager)->app_server->srv_internal->GetGameObject(animalID);
		if(animal != NULL)
		{
			animal->cre_associate_type = 3;
			pThis->cre_summoned_acomp = animalID;
		}
	}
/*
	CResRef resref;
	std::fill_n(resref.resref, 16, 0);

	fprintf(Patch.m_fFile, "o summona 1\n");fflush(Patch.m_fFile);

	int32_t level = pThis->cre_stats->GetNumLevelsOfClass(CLASS_TYPE_RANGER)-3;
	if(level < 0) level = 0;
	fprintf(Patch.m_fFile, "o summon 1a: %i\n",level);fflush(Patch.m_fFile);
	level += pThis->cre_stats->GetNumLevelsOfClass(CLASS_TYPE_DRUID);
	fprintf(Patch.m_fFile, "o summon 1b: %i\n",level);fflush(Patch.m_fFile);
	if ( level <= 0 )
	{
		fprintf(Patch.m_fFile, "o summon 1c\n");fflush(Patch.m_fFile);
		return;
	}
	else if ( level > 40 )
	{
		level = 40;
	}
	fprintf(Patch.m_fFile, "o summon 2\n");fflush(Patch.m_fFile);
	uint32_t assoc_id = pThis->GetAssociateId(2, 1);
	CNWSCreature *assoc = NULL;
	if ( assoc_id != OBJECT_INVALID && (assoc = (CNWSCreature*)(*NWN_AppManager)->app_server->GetGameObject(assoc_id)) != NULL ) {
		assoc->ReceiveAssociateCommand(-8);
	}
	fprintf(Patch.m_fFile, "o summon 3\n");fflush(Patch.m_fFile);
	int acomp_type = pThis->cre_stats->cs_acomp_type;
	fprintf(Patch.m_fFile, "o summon 4\n");fflush(Patch.m_fFile);
	char *source = new char[250];
	CExoString base = "................";
	fprintf(Patch.m_fFile, "o summon 5 type: %i\n",acomp_type);fflush(Patch.m_fFile);
	(*NWN_Rules)->ru_2das->tda_hen_companion->GetCExoStringEntry(acomp_type,"BASERESREF",&base);
	fprintf(Patch.m_fFile, "o summon 5apul %s\n",base.text);fflush(Patch.m_fFile);
	if ( level > 9 ) 
	{
		_snprintf(resref.resref, 16, "%s%d", base.text, level);
	}
	else 
	{
		_snprintf(resref.resref, 16, "%s0%d", base.text, level);
	}
	fprintf(Patch.m_fFile, "o summon 6 %s\n",resref.resref);fflush(Patch.m_fFile);
	for ( size_t i = 0; i < 16; ++i ) {
		resref.resref[i] = tolower(resref.resref[i]);
	}
	fprintf(Patch.m_fFile, "o summon 7 %s\n",resref.resref);fflush(Patch.m_fFile);

	CExoString name = pThis->cre_stats->cs_acomp_name;
	//_snprintf(name, 250, "%s", pThis->cre_stats->cs_acomp_name.text);
	fprintf(Patch.m_fFile, "o summon 9: %s %s\n",resref.resref,name.text);fflush(Patch.m_fFile);
	pThis->SummonAssociate(resref, name.CStr(), name.len, 2);
	//CNWSCreature__SummonAssociateOrig(pThis,NULL,resref,pThis->cre_stats->cs_acomp_name.CStr(),2);
	fprintf(Patch.m_fFile, "o summon 10\n");fflush(Patch.m_fFile);
	pThis->cre_summoned_acomp = 1;
	base.~CExoString();
	fprintf(Patch.m_fFile, "o summon 11\n");fflush(Patch.m_fFile);*/
}

void __fastcall CNWSCreature__SummonFamiliar_Hook(CNWSCreature *pThis, void*)
{
	int prev = Patch.helper;
	Patch.helper = 31;
	CNWSCreature__SummonFamiliar(pThis,NULL);
	Patch.helper = prev;
/*
	CResRef *resref = new CResRef();
	std::fill_n(resref->resref, 16, 0);
	fprintf(Patch.m_fFile, "o summonf 1\n");fflush(Patch.m_fFile);

	int32_t level = pThis->cre_stats->GetNumLevelsOfClass(CLASS_TYPE_SORCERER);
	level += pThis->cre_stats->GetNumLevelsOfClass(CLASS_TYPE_WIZARD);
	if ( level <= 0 ) 
	{
		fprintf(Patch.m_fFile, "o summon 1c\n");fflush(Patch.m_fFile);
		return;
	}
	else if ( level > 40 ) 
	{
		level = 40;
	}
	fprintf(Patch.m_fFile, "o summon 2\n");fflush(Patch.m_fFile);
	uint32_t assoc_id = pThis->GetAssociateId(3, 1);
	CNWSCreature *assoc = NULL;
	if ( assoc_id != OBJECT_INVALID && (assoc = (CNWSCreature*)(*NWN_AppManager)->app_server->GetGameObject(assoc_id)) != NULL ) {
		assoc->ReceiveAssociateCommand(-8);
	}
	//char *ref = new char[16];
	fprintf(Patch.m_fFile, "o summon 3\n");fflush(Patch.m_fFile);
	int familiar_type = pThis->cre_stats->cs_famil_type;
	fprintf(Patch.m_fFile, "o summon 4\n");fflush(Patch.m_fFile);
	CExoString base = "................";
	fprintf(Patch.m_fFile, "o summon 5 type: %i\n",familiar_type);fflush(Patch.m_fFile);
	(*NWN_Rules)->ru_2das->tda_hen_familiar->GetCExoStringEntry(familiar_type,"BASERESREF",&base);
	fprintf(Patch.m_fFile, "o summon 5apul %s\n",base.text);fflush(Patch.m_fFile);
	if ( level > 9 ) {
		_snprintf(resref->resref, 16, "%s%d", base.text, level);
	}
	else {
		_snprintf(resref->resref, 16, "%s0%d", base.text, level);
	}
	fprintf(Patch.m_fFile, "o summon 6 %s\n",resref->resref);fflush(Patch.m_fFile);
	for ( size_t i = 0; i < 16; ++i ) {
		resref->resref[i] = tolower(resref->resref[i]);
	}
	fprintf(Patch.m_fFile, "o summon 7 %s\n",resref->resref);fflush(Patch.m_fFile);

	CExoString name = pThis->cre_stats->cs_famil_name;
	//_snprintf(name, 250, "%s", pThis->cre_stats->cs_acomp_name.text);
	fprintf(Patch.m_fFile, "o summon 9: %s %s\n",resref->resref,name.text);fflush(Patch.m_fFile);
	pThis->SummonAssociate(*resref, name.CStr(), name.len, 2);
	fprintf(Patch.m_fFile, "o summon 10\n");fflush(Patch.m_fFile);
	pThis->cre_summoned_famil = 1;
	base.~CExoString();
	fprintf(Patch.m_fFile, "o summon 11\n");fflush(Patch.m_fFile);
	name.~CExoString();
	fprintf(Patch.m_fFile, "o summon 13\n");fflush(Patch.m_fFile);*/
}

int __fastcall CNWSCreature__ToggleMode_Hook(CNWSCreature *pThis, void *, unsigned char arg1)
{
	if(arg1 > 1)
	{//TODO: game checks for appropriate feats here, so there is a potentional exploit...
		arg1--;
		pThis->SetCombatMode(arg1,pThis->cre_mode_combat != arg1);
		return 0;
	}
	return CNWSCreature__ToggleMode(pThis, NULL, arg1);
}

void __fastcall CNWSCreature__SetCombatMode_Hook(CNWSCreature *pThis, void*, unsigned char arg1, int arg2)
{
	if(pThis == NULL || (arg1 == 0 && arg2 == 1))
	{
		return;
	}
	else if(arg2 == 0)
	{
		arg1 = 0;
		arg2 = 1;
	}
	CNWSCreature__SetCombatMode(pThis, NULL, arg1, arg2);
}

void __fastcall CNWSCreature__ResolveAmmunition_Hook(CNWSCreature *pThis, int edx, unsigned long l)
{
	CNWSItem *item = pThis->cre_equipment->GetItemInSlot(16);
	if(item != NULL)
	{
		int bt = item->it_baseitemtype;
		if(bt == 31 || bt == 59 || bt == 63)//throwing weapon
		{
			if(item->GetPropertyByTypeExists(14,0))//boomerang
			{
				return;//do nothing
			}
		}
	}
	CNWSCreature__ResolveAmmunition(pThis, edx,l);
}

void Hook()
{
	if(HookCode((PVOID)0x4812E0, CNWSCreatureStats__GetWeaponFocus_Hook, (PVOID*)&CNWSCreatureStats__GetWeaponFocus))
	{
		fprintf(Patch.m_fFile, "o Trident weapon focus patched succesfully!\n");
	}
	else
	{
		fprintf(Patch.m_fFile, "o Trident weapon focus patch failed.\n");
	}

	bool fail = false;
	if(!HookCode((PVOID)0x532C90, CNWSCombatRound__GetCurrentAttackWeapon_Hook, (PVOID*)&CNWSCombatRound__GetCurrentAttackWeapon))
	{
		fail = true;
	}
	if(!fail && HookCode((PVOID)0x4778B0, CNWSCreatureStats__GetCriticalHitRoll_Hook, (PVOID*)&CNWSCreatureStats__GetCriticalHitRoll))
	{
		fprintf(Patch.m_fFile, "o Ki critical offhand bug patched succesfully!\n");
	}
	else
	{
		fprintf(Patch.m_fFile, "o Ki critical offhand bug failed ERROR #%i.\n",fail);
	}

	if(HookCode((PVOID)0x547580, CNWSCreature__ResolveAttack_Hook, (PVOID*)&CNWSCreature__ResolveAttack))
	{
		fprintf(Patch.m_fFile, "o Circle kick patched succesfully!\n");
	}
	else
	{
		fprintf(Patch.m_fFile, "o Circle kick patch failed.\n");
	}

	if(HookCode((PVOID)0x491F10, CNWSCreature__AddEquipItemActions_Hook, (PVOID*)&CNWSCreature__AddEquipItemActions))
	{
		fprintf(Patch.m_fFile, "o Double equip exploit patched successfully!\n");
	}
	else
	{
		fprintf(Patch.m_fFile, "o Double equip exploit patch failed.\n");
	}

	if(HookCode((PVOID)0x4CC070, CNWSCreature__SummonAnimalCompanion_Hook, (PVOID*)&CNWSCreature__SummonAnimalCompanion))
	{
		fprintf(Patch.m_fFile, "o Animal companion summoning patched succesfully!\n");
	}
	else
	{
		fprintf(Patch.m_fFile, "o Animal companion summoning patch failed.\n");
	}

	if(HookCode((PVOID)0x4CC390, CNWSCreature__SummonFamiliar_Hook, (PVOID*)&CNWSCreature__SummonFamiliar))
	{
		fprintf(Patch.m_fFile, "o Familiar summoning patched succesfully!\n");
	}
	else
	{
		fprintf(Patch.m_fFile, "o Familiar summoning  patch failed.\n");
	}

	if(HookCode((PVOID)0x4CC6D0, CNWSCreature__SummonAssociate_Hook, (PVOID*)&CNWSCreature__SummonAssociate))
	{
		fprintf(Patch.m_fFile, "o Associate summoning patched succesfully!\n");
	}
	else
	{
		fprintf(Patch.m_fFile, "o Associate summoning patch failed.\n");
	}

	if(HookCode((PVOID)0x4CDD80, CNWSCreature__GetAssociateId_Hook, (PVOID*)&CNWSCreature__GetAssociateId))
	{
		fprintf(Patch.m_fFile, "o Associate ID patched succesfully!\n");
	}
	else
	{
		fprintf(Patch.m_fFile, "o Associate ID patch failed.\n");
	}
	
	fail = false;
	if(!HookCode((PVOID)0x4CE950, CNWSCreature__CanUseItem_Hook, (PVOID*)&CNWSCreature__CanUseItem))
	{
		fail = true;
	}
	if(!fail && HookCode((PVOID)0x4A4CB0, CNWSCreature__UseItem_Hook, (PVOID*)&CNWSCreature__UseItem))
	{
		fprintf(Patch.m_fFile, "o Use items in polymorph patched successfully!\n");
	}
	else
	{
		fprintf(Patch.m_fFile, "o Use items in polymorph patch failed. ERROR #%i.\n",fail);
	}
	
	fail = false;
	if(!HookCode((PVOID)0x48B770, CNWSCreatureStats__GetEffectImmunity_Hook, (PVOID*)&CNWSCreatureStats__GetEffectImmunity))
	{
		fail = true;
	}
	if(!fail && HookCode((PVOID)0x4EDA30, CNWSEffectListHandler__OnApplyAbilityDecrease_Hook, (PVOID*)&CNWSEffectListHandler__OnApplyAbilityDecrease))
	{
		fprintf(Patch.m_fFile, "o Itemproperty ability decrease patched succesfully!\n");
	}
	else
	{
		fprintf(Patch.m_fFile, "o Itemproperty ability decrease patch failed. ERROR #%i.\n",fail);
	}
	if(!fail && HookCode((PVOID)0x4F57D0, CNWSEffectListHandler__OnApplyCurse_Hook, (PVOID*)&CNWSEffectListHandler__OnApplyCurse))
	{
		fprintf(Patch.m_fFile, "o Curse ability decrease patched succesfully!\n");
	}
	else
	{
		fprintf_s(Patch.m_fFile, "o Curse ability decrease patch failed. ERROR #%i.\n",fail);
	}

	if(HookCode((PVOID)0x54FB70, CNWSCreature__ResolveDamageShields_Hook, (PVOID*)&CNWSCreature__ResolveDamageShields))
	{
		fprintf(Patch.m_fFile, "o Effect damage shield versus alignment patched succesfully!\n");
	}
	else
	{
		fprintf(Patch.m_fFile, "o Effect damage shield versus alignment patch failed.\n");
	}

	if(HookCode((PVOID)0x4A6D00, CNWSCreature__GetRelativeWeaponSize_Hook, (PVOID*)&CNWSCreature__GetRelativeWeaponSize))
	{
		fprintf(Patch.m_fFile, "o Deflect arrow weapon size bug patched succesfully!\n");
	}
	else
	{
		fprintf(Patch.m_fFile, "o Deflect arrow weapon size bug patch failed.\n");
	}

	fail = false;
	if(!HookCode((PVOID)0x59F2E0, CNWSItemPropertyHandler__ApplyHolyAvenger_Hook, (PVOID*)&CNWSItemPropertyHandler__ApplyHolyAvenger))
	{
		fail = true;
	}
	if(!fail && HookCode((PVOID)0x59FC80, CNWSItemPropertyHandler__RemoveHolyAvenger_Hook, (PVOID*)&CNWSItemPropertyHandler__RemoveHolyAvenger))
	{
		fprintf(Patch.m_fFile, "o Holy avenger weapon enhancement bug patched succesfully!\n");
	}
	else
	{
		fprintf(Patch.m_fFile, "o Holy avenger weapon enhancement bug patch failed. ERROR #%i.\n",fail);
	}

	fail = false;
	if(!HookCode((PVOID)0x4A5080, CNWSCreature__ToggleMode_Hook, (PVOID*)&CNWSCreature__ToggleMode))
	{
		fail = true;
	}
	if(!fail && HookCode((PVOID)0x4BB4D0, CNWSCreature__SetCombatMode_Hook, (PVOID*)&CNWSCreature__SetCombatMode))
	{
		fprintf(Patch.m_fFile, "o Combat mode cancelling patched succesfully!\n");
	}
	else
	{
		fprintf(Patch.m_fFile, "o Combat mode cancelling patch failed.\n");
	}

	if(HookCode((PVOID)0x548100, CNWSCreature__ResolveAmmunition_Hook, (PVOID*)&CNWSCreature__ResolveAmmunition))
	{
		fprintf(Patch.m_fFile, "o Boomerang item property enabled succesfully!\n");
	}
	else
	{
		fprintf_s(Patch.m_fFile, "o Failed in enabling the boomerang item property. ERROR #%i.\n",fail);
	}

	fprintf(Patch.m_fFile, "\n" );
	fflush(Patch.m_fFile);
}