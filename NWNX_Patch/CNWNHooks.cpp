#include "CNWNHooks.h"
#include "../NWNXdll/madCHook.h"
#include "../NWNXdll/IniFile.h"
#include "NWNXPatch.h"
#include "CVirtualMachine.h"
#include "nwn_internals.h"
#include "types.h"
#include <iostream>
#include <stdio.h>

extern CNWNXPatch Patch;

C2DA *weaponfeats_2da,*racialtypes_2da, *classes_2da, *spells_level_2da;

void InitializeWeaponFeats2DA()
{
	fprintf(Patch.m_fFile, "o Initializing weaponfeats.2da.\n");fflush(Patch.m_fFile);
	if(weaponfeats_2da)
	{
		weaponfeats_2da->Unload2DArray();
		fprintf(Patch.m_fFile, "o  weaponfeats.2da already initialized. Unloading content.\n");fflush(Patch.m_fFile);
	}
	else
	{
		CResRef resref;
		std::fill_n(resref.resref, 16, 0);
		sprintf_s(resref.resref,16,"%s","weaponfeats");
		weaponfeats_2da = new C2DA();
		weaponfeats_2da->C2DA(resref,0);
	}
	if(weaponfeats_2da)
	{
		weaponfeats_2da->Load2DArray();
		fprintf(Patch.m_fFile, "o  weaponfeats.2da loaded.\n");fflush(Patch.m_fFile);
	}
	fprintf(Patch.m_fFile, "o  done.\n");fflush(Patch.m_fFile);
}

void InitializeRacialTypes2DA()
{
	fprintf(Patch.m_fFile, "o Initializing racial_types.2da.\n");fflush(Patch.m_fFile);
	if(racialtypes_2da)
	{
		racialtypes_2da->Unload2DArray();
		fprintf(Patch.m_fFile, "o  racial_types.2da already initialized. Unloading content.\n");fflush(Patch.m_fFile);
	}
	else
	{
		CResRef resref;
		std::fill_n(resref.resref, 16, 0);
		sprintf_s(resref.resref,16,"%s","racialtypes");
		racialtypes_2da = new C2DA();
		racialtypes_2da->C2DA(resref,0);
	}
	if(racialtypes_2da)
	{
		racialtypes_2da->Load2DArray();
		NWN_Rules->LoadRaceInfo();
		fprintf(Patch.m_fFile, "o  racial_types.2da loaded.\n");fflush(Patch.m_fFile);
	}
	fprintf(Patch.m_fFile, "o  done.\n");fflush(Patch.m_fFile);
}

void InitializeClasses2DA()
{
	fprintf(Patch.m_fFile, "o Initializing classes.2da.\n");fflush(Patch.m_fFile);
	if(classes_2da)
	{
		classes_2da->Unload2DArray();
		fprintf(Patch.m_fFile, "o  classes.2da already initialized. Unloading content.\n");fflush(Patch.m_fFile);
	}
	else
	{
		CResRef resref;
		std::fill_n(resref.resref, 16, 0);
		sprintf_s(resref.resref,16,"%s","classes");
		classes_2da = new C2DA();
		classes_2da->C2DA(resref,0);
	}
	if(classes_2da)
	{
		classes_2da->Load2DArray();
		NWN_Rules->LoadClassInfo();
		fprintf(Patch.m_fFile, "o  classes.2da loaded.\n");fflush(Patch.m_fFile);
		CNWClass *cClass;
		CExoString CastType = CExoString("CastType");
		CExoString sVal;
		int val = 0;
		int numRows = classes_2da->tda_rows_len; if(numRows > 255) numRows = 255;
		for(unsigned char x=0;x < numRows; x++)
		{
			cClass = &(NWN_Rules->ru_classes[x]);
			//fprintf(logFile, "o  classes.2da loaded cls %i spellcaster %i arcane %i.\n",x,cClass->SpellCaster,g_pRules->IsArcaneClass(x));fflush(logFile);
			if(cClass->SpellCaster && classes_2da->GetINTEntry_strcol(x,CastType,&val))
			{
				Patch.cls_cast_type[x] = val;
			}
			else
			{
				switch(x)//default CastType values if CastType is ****
				{
					case CLASS_TYPE_BARD: Patch.cls_cast_type[x] = 131; break;
					case CLASS_TYPE_CLERIC: Patch.cls_cast_type[x] = 8; break;
					case CLASS_TYPE_DRUID: Patch.cls_cast_type[x] = 0; break;
					case CLASS_TYPE_PALADIN: Patch.cls_cast_type[x] = 0; break;
					case CLASS_TYPE_RANGER: Patch.cls_cast_type[x] = 0; break;
					case CLASS_TYPE_SORCERER: Patch.cls_cast_type[x] = 131; break;
					case CLASS_TYPE_WIZARD: Patch.cls_cast_type[x] = 209; break;
				}
			}
			//fprintf(Patch.m_fFile, "o  classes.2da loaded cls %i spellcaster %i arcane %i playerclass %i.\n",x,cClass->SpellCaster,NWN_Rules->IsArcaneClass(x),cClass->PlayerClass);fflush(Patch.m_fFile);
		}
	}
	fprintf(Patch.m_fFile, "o  done.\n");fflush(Patch.m_fFile);
}

/*
void InitializeSpells2DA()
{
	fprintf(Patch.m_fFile, "o Initializing spells.2da.\n");fflush(Patch.m_fFile);
	if(Patch.spells_2da)
	{
		Patch.spells_2da->Unload2DArray();
		fprintf(Patch.m_fFile, "o  spells.2da already initialized. Unloading content.\n");fflush(Patch.m_fFile);
	}
	else
	{
		CResRef resref;
		std::fill_n(resref.resref, 16, 0);
		sprintf(resref.resref,"%s","spells");
		Patch.spells_2da = new C2DA();
		Patch.spells_2da->C2DA(resref,0);
	}
	if(Patch.spells_2da)
	{
		Patch.spells_2da->Load2DArray();
		fprintf(Patch.m_fFile, "o  spells.2da loaded.\n");fflush(Patch.m_fFile);
	}
}*/

void InitializeSpells_Level2DA()
{
	fprintf(Patch.m_fFile, "o Initializing spells_level.2da.\n");fflush(Patch.m_fFile);
	if(spells_level_2da)
	{
		spells_level_2da->Unload2DArray();
		fprintf(Patch.m_fFile, "o  spells_level.2da already initialized. Unloading content.\n");fflush(Patch.m_fFile);
	}
	else
	{
		CResRef resref;
		std::fill_n(resref.resref, 16, 0);
		sprintf_s(resref.resref,16,"%s","spells_level");
		spells_level_2da = new C2DA();
		spells_level_2da->C2DA(resref,0);
	}
	if(spells_level_2da)
	{
		spells_level_2da->Load2DArray();
		fprintf(Patch.m_fFile, "o  spells_level.2da loaded.\n");fflush(Patch.m_fFile);
	}
}

//system
int (__fastcall *CNWSMessage__HandlePlayerToServerMessage)(CNWSMessage *pMessage, void *, unsigned long nPlayerID, unsigned char *pData, unsigned long nLen);

unsigned long (__fastcall *CNWSModule__LoadModuleFinish)(CNWSModule *pThis, void*);
void (__fastcall *CServerExoAppInternal__RemovePCFromWorld)(CServerExoAppInternal *srv, void *, CNWSPlayer *player);
//scripting
int (__fastcall *CNWVirtualMachineCommands__ExecuteCommandGetAssociateType)(CVirtualMachineCommands *vm_cmds, void*, int arg1, int arg2);
int (__fastcall *CNWVirtualMachineCommands__ExecuteCommandGetAssociate)(CVirtualMachineCommands *vm_cmds, void*, int arg1, int arg2);
int (__fastcall *CNWVirtualMachineCommands__ExecuteCommandApplyEffectOnObject)(CVirtualMachineCommands *vm_cmds, void*, int cmd, int args);
//effects
void (__fastcall *CGameEffect__SetCreator)(CGameEffect *pThis, void*, unsigned long creatorID);
int (__fastcall *CNWSCreatureStats__GetEffectImmunity)(CNWSCreatureStats *pThis, void*, unsigned char c, CNWSCreature *cre);
int (__fastcall *CNWSEffectListHandler__OnApplyAbilityDecrease)(CNWSEffectListHandler *pThis, void*, CNWSObject *obj, CGameEffect *eff, int i);
int (__fastcall *CNWSEffectListHandler__OnApplyCurse)(CNWSEffectListHandler *pThis, void*, CNWSObject *obj, CGameEffect *eff, int i);
int (__fastcall *CNWSEffectListHandler__OnApplyPolymorph)(CNWSEffectListHandler *pThis, void*, CNWSObject *obj, CGameEffect *eff, int i);
int (__fastcall *CNWSEffectListHandler__OnRemovePolymorph)(CNWSEffectListHandler *pThis, void*, CNWSObject *obj, CGameEffect *eff);
int (__fastcall *CNWSEffectListHandler__OnApplyDisarm)(CNWSEffectListHandler *pThis, void*, CNWSObject *obj, CGameEffect *eff, int arg1);
int (__fastcall *CNWSEffectListHandler__OnApplyKnockdown)(CNWSEffectListHandler *pThis, void*, CNWSObject *obj, CGameEffect *eff, int arg1);
int (__fastcall *CNWSEffectListHandler__OnApplyDefensiveStance) (CNWSEffectListHandler *pThis, void*, CNWSObject *obj, CGameEffect *eff, int n);
int (__fastcall *CNWSEffectListHandler__OnApplyDeath)(CNWSEffectListHandler *pThis, void*, CNWSObject *obj, CGameEffect *eff, int arg1);
//weapons
int (__fastcall *CNWSCreatureStats__GetWeaponFinesse)(CNWSCreatureStats *pThis, void*, CNWSItem *item);
int (__fastcall *CNWSCreatureStats__GetWeaponFocus)(CNWSCreatureStats *pThis, void*, CNWSItem *item);
int (__fastcall *CNWSCreatureStats__GetWeaponImprovedCritical)(CNWSCreatureStats *pThis, void*, CNWSItem *item);
int (__fastcall *CNWSCreatureStats__GetWeaponSpecialization)(CNWSCreatureStats *pThis, void*, CNWSItem *item);
int (__fastcall *CNWSCreatureStats__GetEpicWeaponFocus)(CNWSCreatureStats *pThis, void*, CNWSItem *item);
int (__fastcall *CNWSCreatureStats__GetEpicWeaponSpecialization)(CNWSCreatureStats *pThis, void*, CNWSItem *item);
int (__fastcall *CNWSCreatureStats__GetEpicWeaponOverwhelmingCritical)(CNWSCreatureStats *pThis, void*, CNWSItem *item);
int (__fastcall *CNWSCreatureStats__GetEpicWeaponDevastatingCritical)(CNWSCreatureStats *pThis, void*, CNWSItem *item);
int (__fastcall *CNWSCreatureStats__GetIsWeaponOfChoice)(CNWSCreatureStats *pThis, void*, uint32_t BaseItemType);
int (__fastcall *CNWSCreatureStats__GetUseMonkAttackTables)(CNWSCreatureStats *pThis, void*, int a2);
unsigned char (__fastcall *CNWSCreatureStats__GetUnarmedDamageDice)(CNWSCreatureStats *pThis, void*);
//other
void (__fastcall *CNWSCreature__ResolveAttack)(CNWSCreature *pThis, void*, unsigned long target, int i, int i2);
int (__fastcall *CNWSCreature__CanUseItem)(CNWSCreature *pThis, void*, CNWSItem *item, int a1);
int (__fastcall *CNWSCreature__UseItem)(CNWSCreature *pThis, void*, unsigned long l1, unsigned char c1, unsigned char c2, unsigned long l2, Vector v, unsigned long l3);
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
int (__fastcall *CNWSCreature__ToggleMode)(CNWSCreature *pThis, void*, unsigned char arg1);
void (__fastcall *CNWSCreature__ResolveAmmunition)(CNWSCreature *pThis, void*, unsigned long l);
void (__fastcall *CNWSCreature__BroadcastAttackOfOpportunity)(CNWSCreature *pThis, void*, unsigned long targetID, int arg1);
void (__fastcall *CNWSCombatRound__AddAttackOfOpportunity)(CNWSCombatRound *pThis, void*, unsigned long lTarget);
void (__fastcall *CNWSCreatureStats_ClassInfo__SetNumberMemorizedSpellSlots)(CNWSCreatureClass *pThis, void *,unsigned char spell_level, unsigned char spell_num);
int (__fastcall *CNWSItemPropertyHandler__ApplyBonusSpellOfLevel)(CNWSItemPropertyHandler *pThis, void*, CNWSItem *item, int *ip, CNWSCreature *cre, unsigned long l, int i);
int (__fastcall *CNWSItemPropertyHandler__RemoveBonusSpellOfLevel)(CNWSItemPropertyHandler *pThis, void*, CNWSItem *item, int *ip, CNWSCreature *cre, unsigned long l);
void (__fastcall *CNWSCreature__UpdateAttributesOnEffect)(CNWSCreature *pThis, void*, CGameEffect *eff, int arg1);
int (__fastcall *CNWSCreatureStats__ResolveSpecialAttackDamageBonus)(CNWSCreatureStats *pThis, void*, CNWSCreature *target);
void (__fastcall *CNWSObject__ClearAllPartyInvalidActions)(CNWSObject *pThis, void *);
unsigned char (__fastcall *CNWSItem__GetMinEquipLevel)(CNWSItem *pThis, void*);
char (__fastcall *CNWSCreatureStats__GetTotalACSkillMod)(CNWSCreatureStats *pThis, void*);
int (__fastcall *CNWSCreature__GetUseMonkAbilities)(CNWSCreature *pThis, void*);
void (__fastcall *CNWSCreature__SetActivity)(CNWSCreature *pThis, void*, int nActivity, int bOn);
int (__fastcall *CNWSTrigger__GetCanFireTrapOnObject)(CNWSTrigger *pThis, void*, unsigned long targetID, int arg1);
int (__fastcall *CNWSCreatureStats__GetFavoredEnemyBonus)(CNWSCreatureStats *pThis, void*, CNWSCreature *cre);
int (__fastcall *CNWSCreatureStats__GetSpellResistance)(CNWSCreatureStats *pThis, void*);
float (__fastcall *CNWSCreature__MaxAttackRange)(CNWSCreature *pThis, void*, unsigned long targetID, int arg1, int arg2);
void (__fastcall *CNWSCreature__RemoveBadEffects)(CNWSCreature *pThis, void*);
int (__fastcall *CNWSCreature__AddPickPocketAction)(CNWSCreature *pThis, void*, unsigned long targetID);
int (__fastcall *CNWSCreature__StartBarter)(CNWSCreature *pThis, void*, unsigned long targetID, unsigned long itemID, int arg1);
int (__fastcall *CNWSCreature__EventHandler)(CNWSCreature *pThis, void*, int arg1, int arg2, float arg3, int arg4, int arg5);
void (__fastcall *CNWSCreatureStats__LevelDown)(CNWSCreatureStats *pThis, void*, int *CNWLevelStats);
void (__fastcall *CNWSCreatureStats__LevelUp)(CNWSCreatureStats *pThis, void*, int *CNWLevelStats, unsigned char domain1, unsigned char domain2, unsigned char spellschool, int num_levels);
int (__fastcall *CNWSStore__SellItem)(CNWSStore *pThis, void *, CNWSItem *item, CNWSCreature *buyer, unsigned char a1, unsigned char a2);
unsigned long (__fastcall *CServerExoAppInternal__ValidateCreateServerCharacter)(CServerExoAppInternal *pThis, void*, CNWSPlayer *player, void *, unsigned long l1);
//spellcasting
int (__fastcall *CNWRules__IsArcaneClass)(CNWRules *pThis, void *, unsigned char cls_id);
unsigned char (__fastcall *CNWSpell__GetSpellLevel)(CNWSpell *pThis, void *, unsigned char cls_id);
unsigned char (__fastcall *CNWSCreatureStats__GetSpellGainWithBonus)(CNWSCreatureStats *pThis, void *, unsigned char cls_pos, unsigned char spell_lvl);
unsigned char (__fastcall *CNWSCreatureStats__GetSpellGainWithBonusAfterLevelUp)(CNWSCreatureStats *pThis, void *, unsigned char cls_pos, unsigned char spell_lvl, CNWLevelStats *lvlstats, unsigned char spell_school, int is_first_lvl);
int (__fastcall *CNWSCreatureStats__GetSpellMinAbilityMet)(CNWSCreatureStats *pThis, void *, unsigned char cls_pos, unsigned char spell_lvl);
void (__fastcall *CNWSCreatureStats__UpdateNumberMemorizedSpellSlots)(CNWSCreatureStats *pThis, void *);
unsigned char (__fastcall *CNWSCreatureStats__ComputeNumberKnownSpellsLeft)(CNWSCreatureStats *pThis, void *, unsigned char cls_pos, unsigned char spell_lvl);
int (__fastcall *CNWSCreatureStats_ClassInfo__ConfirmDomainSpell)(CNWSCreatureClass *pThis, void *, unsigned char domain_lvl, long spell_id);
unsigned char (__fastcall *CNWSCreatureStats__GetSpellUsesLeft)(CNWSCreatureStats *pThis, void *, long spell_id, unsigned char cls_pos, unsigned char spell_lvl, unsigned char metamagic);
int (__fastcall *CNWSCreature__LearnScroll)(CNWSCreature *pThis, void*, unsigned long itemID);
void (__fastcall *CNWSCreatureStats__AdjustSpellUsesPerDay)(CNWSCreatureStats *pThis, void *);
void (__fastcall *CNWSCreatureStats__ComputeFeatBonuses)(CNWSCreatureStats *pThis, void*, int *a1, int a2, int a3);
void (__fastcall *CNWSCreature__ReadItemsFromGff)(CNWSCreature *pThis, void*, int *a1, int *a2, int a3, int a4);
void (__fastcall *CNWSCreature__PossessFamiliar)(CNWSCreature *pThis, void*);
void (__fastcall *CNWSCreature__UnpossessFamiliar)(CNWSCreature *pThis, void*);
int (__fastcall *CNWSCreature__GetIsPossessedFamiliar)(CNWSCreature *pThis, void*);
void (__fastcall *CGuiCreatureMenu__RadialMenuPossessFamiliar)(int *pThis, void*, int a1);

void __fastcall CNWSCreature__ReadItemsFromGff_Hook(CNWSCreature *pThis, void*, int *a1, int *a2, int a3, int a4)
{
	int prev = Patch.helper;
	Patch.helper = 56;
	CNWSCreature__ReadItemsFromGff(pThis,NULL,a1,a2,a3,a4);
	Patch.helper = prev;
	pThis->cre_stats->AdjustSpellUsesPerDay();
}

void __fastcall CNWSCreatureStats__ComputeFeatBonuses_Hook(CNWSCreatureStats *pThis, void*, int *a1, int a2, int a3)
{
	int prev = Patch.helper;
	Patch.helper = 56;
	CNWSCreatureStats__ComputeFeatBonuses(pThis,NULL,a1,a2,a3);
	Patch.helper = prev;
}

void __fastcall CNWSCreatureStats__AdjustSpellUsesPerDay_Hook(CNWSCreatureStats *pThis, void*)
{
	if(Patch.helper == 56) return;//called from CNWSCreatureStats::ComputeFeatBonuses or CNWSCreature::ReadItemsFromGff
	else if(!pThis->cs_is_pc)
	{
		CNWSCreatureStats__AdjustSpellUsesPerDay(pThis,NULL);
		return;
	}
	for(unsigned char cls_pos=0;cls_pos<pThis->cs_classes_len;cls_pos++)
	{
		if(Patch.cls_cast_type[pThis->cs_classes[cls_pos].cl_class] & CAST_TYPE_SPONTANEOUS)
		{
			for(unsigned char spell_lvl=0;spell_lvl<10;spell_lvl++)
			{
				unsigned char spell_gain = pThis->GetSpellGainWithBonus(cls_pos,spell_lvl);
				unsigned char spell_max = pThis->cs_classes[cls_pos].cl_spells_max[spell_lvl];
				//unsigned char spell_uses = pThis->cs_classes[cls_pos].cl_spells_left[spell_lvl];
				//fprintf(logFile, "o CNWSCreatureStats__AdjustSpellUsesPerDay max spells of %i lvl: %i, gain %i, curr %i\n",spell_lvl,spell_max,spell_gain,spell_uses);fflush(logFile);
				/*if(spell_gain > spell_max)//this is a reason why its bugged
				{
					//pThis->cs_classes[cls_pos].cl_spells_max[spell_lvl] = spell_gain;
				}*/
				if(spell_gain < spell_max)
				{
					pThis->cs_classes[cls_pos].cl_spells_max[spell_lvl] = spell_gain;
					pThis->cs_classes[cls_pos].cl_spells_left[spell_lvl]-= spell_max-spell_gain;
				}
			}
		}
	}
}

int __fastcall CNWSEffectListHandler__OnApplyDeath_Hook(CNWSEffectListHandler *pThis, void*, CNWSObject *obj, CGameEffect *eff, int n)//required for PossessCreature custom function
{
	int retVal = CNWSEffectListHandler__OnApplyDeath(pThis,NULL,obj,eff,n);
	CNWSCreature *cre = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(obj->obj_generic.obj_id);
	if(cre && cre->GetIsPossessedFamiliar() && NWN_AppManager->app_server->GetIsControlledByPlayer(obj->obj_generic.obj_id))
	{
		CNWSCreature *cre_orig = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(cre->field_B2C);
		if(cre_orig)
		{
			cre_orig->UnpossessFamiliar();
		}
	}
	return retVal;
}

int __fastcall CNWSCreature__GetIsPossessedFamiliar_Hook(CNWSCreature *pThis, void*)//required to prevent creature default AI and making unsafe actions
{
	return !pThis->cre_is_pc && NWN_AppManager->app_server->GetIsControlledByPlayer(pThis->obj.obj_generic.obj_id);
}

void __fastcall CNWSCreature__PossessFamiliar_Hook(CNWSCreature *pThis, void*)
{
	int prev = Patch.helper;
	CNWSCreature *cre = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(pThis->field_B48);
	if(cre)
	{
		Patch.helper = 222;
	}
	CNWSCreature__PossessFamiliar(pThis,NULL);
	Patch.helper = prev;
}

void __fastcall CNWSCreature__UnpossessFamiliar_Hook(CNWSCreature *pThis, void*)
{
	int prev = Patch.helper;
	CNWSCreature *cre = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(pThis->field_B48);
	if(cre)
	{
		Patch.helper = 222;
	}
	CNWSCreature__UnpossessFamiliar(pThis,NULL);
	pThis->field_B48 = 0;
	Patch.helper = prev;
}

void __fastcall CNWSCreatureStats__LevelUp_Hook(CNWSCreatureStats *pThis, void*, int *CNWLevelStats, unsigned char domain1, unsigned char domain2, unsigned char spellschool, int num_levels)
{
	unsigned char lvl_array[2];
	for(unsigned char x=0;x < 3;x++)
	{
		lvl_array[x] = pThis->cs_classes[x].cl_level;
	}
	CNWSCreatureStats__LevelUp(pThis,NULL,CNWLevelStats,domain1,domain2,spellschool,num_levels);
	for(unsigned char x=0;x<pThis->cs_classes_len;x++)//support for custom spontaneous non learner spellcaster
	{
		if(pThis->cs_classes[x].cl_level != lvl_array[x])
		{
			unsigned char cls_id = pThis->cs_classes[x].cl_class;
			CNWClass *cClass = &(NWN_Rules->ru_classes[cls_id]);
			if(cls_id != CLASS_TYPE_INVALID && cClass && cClass->SpellCaster && ((Patch.cls_cast_type[cls_id] & CAST_TYPE_SPONTANEOUS) && !(Patch.cls_cast_type[cls_id] & CAST_TYPE_RESTRICTED_SPELLBOOK)))
			{
				unsigned char cls_id = pThis->cs_classes[x].cl_class;
				unsigned char cls_lvl = pThis->cs_classes[x].cl_level;
				unsigned char spell_lvl, lvl_max = 0;
				while(lvl_max < 10 && cClass->GetSpellGain(cls_lvl,lvl_max+1) != 255)
				{
					lvl_max++;
				}
				unsigned long num_known;
				for(unsigned long spell_id=0;spell_id < NWN_Rules->ru_spells->spells_len;spell_id++)
				{
					spell_lvl = NWN_Rules->ru_spells->GetSpell(spell_id)->GetSpellLevel(cls_id);
					if(spell_lvl <= lvl_max)
					{
						for(num_known=0;num_known < (unsigned long)pThis->cs_classes[x].cl_spells_known->len && num_known < 255;num_known++)
						{
							if(pThis->GetKnownSpell(x,spell_lvl,(unsigned char)num_known) == spell_id)//already knows
							{
								break;
							}
						}
						if(num_known >= (unsigned long)pThis->cs_classes[x].cl_spells_known->len)
						{
							pThis->AddKnownSpell(x,spell_id);
						}
					}
				}
			}
			return;
		}
	}
}

void __fastcall CNWSCreatureStats__LevelDown_Hook(CNWSCreatureStats *pThis, void *, int *CNWLevelStats)
{
	CNWSCreatureStats__LevelDown(pThis,NULL,CNWLevelStats);
	pThis->UpdateCombatInformation();
	//todo update spellslots?
}

int __fastcall CNWSCreature__LearnScroll_Hook(CNWSCreature *pThis, void *, unsigned long itemID)
{
	CNWSItem *item = NWN_AppManager->app_server->srv_internal->GetItemByGameObjectID(itemID);
	if(pThis != NULL && item != NULL)
	{
		pThis->obj.obj_vartable.SetObject(CExoString("LEARNSCROLL_ITEMID"),itemID);
		if(NWN_VirtualMachine->Runscript(&CExoString("70_s2_learnscrol"),pThis->obj.obj_generic.obj_id,1) == 1)
		{
			return 0;
		}
	}
	return CNWSCreature__LearnScroll(pThis,NULL,itemID);
}


unsigned char __fastcall CNWSCreatureStats__GetSpellUsesLeft_Hook(CNWSCreatureStats *pThis, void *, long spell_id, unsigned char cls_pos, unsigned char domain_lvl, unsigned char metamagic)
{
	if(!classes_2da)
	{
		return CNWSCreatureStats__GetSpellUsesLeft(pThis,NULL,spell_id,cls_pos,domain_lvl,metamagic);
	}
	unsigned char retValOrig = CNWSCreatureStats__GetSpellUsesLeft(pThis,NULL,spell_id,cls_pos,domain_lvl,metamagic);
	if(cls_pos >= pThis->cs_classes_len || spell_id == -1) return 0;//sometimes engine invalid values, in this case we need to return 0
	if(pThis->cs_original->cre_pm_IsPolymorphed) return 1;
	unsigned char retVal = 0;
	unsigned char cls_id = pThis->cs_classes[cls_pos].cl_class;
	CNWClass *cClass = &(NWN_Rules->ru_classes[cls_id]);
	CNWSpell *cSpell = NWN_Rules->ru_spells->GetSpell(spell_id);
	if(cSpell->sp_ID != spell_id)//subradial spell workaround
	{
		spell_id = cSpell->sp_ID;
		cSpell = NWN_Rules->ru_spells->GetSpell(spell_id);
	}
	unsigned char nLevel = cSpell->GetSpellLevel(cls_id);
	if(cClass && cSpell && cls_id < CLASS_TYPE_INVALID && cClass->SpellCaster)
	{
		if(domain_lvl && domain_lvl < 10)
		{
			if(!pThis->cs_classes[cls_pos].ConfirmDomainSpell(domain_lvl,spell_id))
			{
				return 0;
			}
			nLevel = domain_lvl;
		}
		unsigned char newLevel = nLevel+NWN_Rules->GetMetaMagicLevelCost(metamagic);
		if(nLevel < 10 && newLevel < 10 && pThis->GetSpellMinAbilityMet(cls_pos,newLevel))
		{
			if(Patch.cls_cast_type[cls_id] & CAST_TYPE_SPONTANEOUS)
			{
				unsigned char left = pThis->cs_classes[cls_pos].cl_spells_left[newLevel];
				if(left > 0)
				{
					int spell = pThis->GetKnownSpell(cls_pos,nLevel,0);
					for(unsigned char x=1;spell != -1;x++)
					{
						if(spell == spell_id)
						{
							retVal = left;
							break;
						}
						spell = pThis->GetKnownSpell(cls_pos,nLevel,x);
					}
				}
			}
			else//memorized
			{
				CNWSStats_Spell *sp;
				for(unsigned long index=0;index < (unsigned long)pThis->cs_classes[cls_pos].cl_spells_mem[newLevel].len;index++)
				{
					sp = (CNWSStats_Spell*)(CExoArrayList_ptr_get(&(pThis->cs_classes[cls_pos].cl_spells_mem[newLevel]), index));
					if(sp && sp->sp_ready && sp->sp_id == spell_id && (sp->sp_meta&0xFF) == metamagic)
					{
						retVal++;
					}
				}
			}
		}
	}
	if(retValOrig != retVal && cls_id < 11)
	{
		fprintf(Patch.m_fFile, "o CNWSCreatureStats__GetSpellUsesLeft_Hook: new calculation doesn't match with vanilla! cls_id %i, spell_id %i, domain_lvl: %i, metamagic: %i, oldval %i, newval: %i\n",pThis->cs_classes[cls_pos].cl_class,spell_id,domain_lvl,metamagic,retValOrig,retVal);fflush(Patch.m_fFile);
	}
	return retVal;
}

int __fastcall CNWSCreatureStats_ClassInfo__ConfirmDomainSpell_Hook(CNWSCreatureClass *pThis, void *, unsigned char domain_lvl, long spell_id)
{
	if(!classes_2da)
	{
		return CNWSCreatureStats_ClassInfo__ConfirmDomainSpell(pThis,NULL,domain_lvl,spell_id);
	}
	else if(spell_id == -1) return 0;
	CNWClass *cClass = &(NWN_Rules->ru_classes[pThis->cl_class]);
	if(pThis->cl_class != CLASS_TYPE_INVALID && cClass && (Patch.cls_cast_type[pThis->cl_class] & CAST_TYPE_SELECT_DOMAINS))
	{
		CNWDomain *cDomain = NWN_Rules->GetDomain(pThis->cl_domain_1);
		if(pThis->cl_domain_1 != 255 && cDomain)
		{
			if(cDomain->SpellLevel[domain_lvl] == spell_id)
			{
				return 1;
			}
		}
		if(pThis->cl_domain_2 != 255 && (cDomain = NWN_Rules->GetDomain(pThis->cl_domain_2)))
		{
			if(cDomain->SpellLevel[domain_lvl] == spell_id)
			{
				return 1;
			}
		}
	}
	return 0;
}

unsigned char __fastcall CNWSCreatureStats__ComputeNumberKnownSpellsLeft_Hook(CNWSCreatureStats *pThis, void *, unsigned char cls_pos, unsigned char spell_lvl)
{
	if(!classes_2da)
	{
		return CNWSCreatureStats__ComputeNumberKnownSpellsLeft(pThis,NULL,cls_pos,spell_lvl);
	}
	if(cls_pos >= pThis->cs_classes_len) return 0;//sometimes engine passes 254/255 into class position, in this case we need  to return 0
	unsigned char retVal;
	unsigned char cls_id = pThis->cs_classes[cls_pos].cl_class;
	if(cls_id != CLASS_TYPE_INVALID)
	{
		CNWClass *cClass = &(NWN_Rules->ru_classes[cls_id]);
		if(cClass && cClass->SpellCaster && (Patch.cls_cast_type[cls_id] & CAST_TYPE_SPONTANEOUS))
		{
			CNWClass *otherClass;
			int bArcane = Patch.cls_cast_type[cls_id] & CAST_TYPE_ARCANE;
			bool can_enhance_with_prc = true;
			int level = pThis->cs_classes[cls_pos].cl_level;
			int spellMod = 0;
			if((Patch.cls_cast_type[cls_id] & CAST_TYPE_SPONTANEOUS) && Patch.PrestigeClassAffectSpontaneousCasters)
			{
				for(unsigned char x=0;x < pThis->cs_classes_len;x++)
				{
					if(x == cls_pos || pThis->cs_classes[x].cl_class == CLASS_TYPE_INVALID) continue;
					otherClass = &(NWN_Rules->ru_classes[pThis->cs_classes[x].cl_class]);
					if(otherClass->SpellCaster && bArcane == (Patch.cls_cast_type[pThis->cs_classes[x].cl_class] & CAST_TYPE_ARCANE) && pThis->cs_classes[x].cl_level >= level)
					{
						if(pThis->cs_classes[x].cl_level > level || cls_pos < x)
						{
							can_enhance_with_prc = false;
							break;
						}
					}
					if(otherClass->ArcSpellLvlMod && bArcane)
					{
						spellMod+= (pThis->cs_classes[x].cl_level+(otherClass->ArcSpellLvlMod != 1))/otherClass->ArcSpellLvlMod;
					}
					else if(otherClass->DivSpellLvlMod && !bArcane)
					{
						spellMod+= (pThis->cs_classes[x].cl_level+(otherClass->DivSpellLvlMod != 1))/otherClass->DivSpellLvlMod;
					}
				}
			}
			if(can_enhance_with_prc) level+= spellMod;
			retVal = cClass->GetSpellsKnownPerLevel(level,spell_lvl,0,0,0);
			if(retVal == 255) retVal = 0;
			else if(spell_lvl > 0 && pThis->cs_classes[cls_pos].cl_specialist)
			{
				retVal++;
			}
			retVal-= (unsigned char)pThis->cs_classes[cls_pos].cl_spells_known[spell_lvl].len;//warning ulong -> uchar
		}
	}
	unsigned char retValOrig = CNWSCreatureStats__ComputeNumberKnownSpellsLeft(pThis,NULL,cls_pos,spell_lvl);
	if(retValOrig != retVal && cls_id < 11)
	{
		fprintf(Patch.m_fFile, "o CNWSCreatureStats__ComputeNumberKnownSpellsLeft: new calculation doesnt match with vanilla! cls_id %i, spell_lvl %i, oldval %i, newval: %i\n",pThis->cs_classes[cls_pos].cl_class,spell_lvl,retValOrig,retVal);fflush(Patch.m_fFile);
	}
	return retVal;
}

int __fastcall CNWRules__IsArcaneClass_Hook(CNWRules *pThis, void *, unsigned char cls_id)
{//ma vliv na nektere pravidla jako hluchota, somatic spell component, prestige class spell progression
	if(!classes_2da)
	{
		return cls_id == CLASS_TYPE_WIZARD || cls_id == CLASS_TYPE_SORCERER || cls_id == CLASS_TYPE_BARD;
	}
	return Patch.cls_cast_type[cls_id] & CAST_TYPE_ARCANE;
}

unsigned char __fastcall CNWSpell__GetSpellLevel_Hook(CNWSpell *pThis, void *, unsigned char cls_id)
{//tohle pomuze vyplnit zname kouzla v knize kouzel
	switch(cls_id)
	{
	case CLASS_TYPE_WIZARD:
	case CLASS_TYPE_SORCERER:
		return pThis->sp_level_wiz;
	case CLASS_TYPE_BARD:
		return pThis->sp_level_bard;
	case CLASS_TYPE_CLERIC:
		return pThis->sp_level_cleric;
	case CLASS_TYPE_DRUID:
		return pThis->sp_level_druid;
	case CLASS_TYPE_RANGER:
		return pThis->sp_level_ranger;
	case CLASS_TYPE_PALADIN:
		return pThis->sp_level_paladin;
	case CLASS_TYPE_INVALID:
		return 255;
	}
	if(spells_level_2da && spells_level_2da->tda_rows_len > 0 && spells_level_2da->tda_cols_len > 1)
	{
		int retVal = 0;
		char *colname = new char[4];
		sprintf_s(colname,4,"%i",cls_id);
		CExoString column = CExoString(colname);
		if(spells_level_2da->GetINTEntry_strcol(pThis->sp_ID,column,&retVal))
		{
			return retVal;
		}
		return 255;
		//fprintf(Patch.m_fFile, "o CNWSpell__GetSpellLevel: spell_id: %i, cls_id: %i, retval: %i\n",pThis->sp_ID,cls_id,retVal);fflush(Patch.m_fFile);
	}
	return pThis->sp_level_innate;
}

void __fastcall CNWSCreatureStats__UpdateNumberMemorizedSpellSlots_Hook(CNWSCreatureStats *pThis, void *)
{
	if(Patch.helper == 56) return;//called from CNWSCreatureStats::ComputeFeatBonuses
	CNWClass *cClass;int spell_lvl, num_slots;uint8_t cls_id;
	for(unsigned char x = 0;x < pThis->cs_classes_len; x++)
	{
		cls_id = pThis->cs_classes[x].cl_class;
		cClass = &(NWN_Rules->ru_classes[cls_id]);
		if(cls_id != 255 && cls_id != CLASS_TYPE_BARD && cls_id != CLASS_TYPE_SORCERER && cClass && cClass->SpellCaster && !(Patch.cls_cast_type[cls_id] & CAST_TYPE_SPONTANEOUS))
		{
			for(spell_lvl = 0;spell_lvl < 10;spell_lvl++)
			{
				num_slots = pThis->GetSpellGainWithBonus(x,spell_lvl);
				pThis->GetInfo(x)->SetNumberMemorizedSpellSlots(spell_lvl,num_slots);
			}
		}
	}
}

unsigned char __fastcall CNWSCreatureStats__GetSpellGainWithBonus_Hook(CNWSCreatureStats *pThis, void *, unsigned char cls_pos, unsigned char spell_lvl)
{
	if(!classes_2da)
	{
		return CNWSCreatureStats__GetSpellGainWithBonus(pThis,NULL,cls_pos,spell_lvl);
	}
	if(cls_pos >= pThis->cs_classes_len) return 0;//sometimes engine passes 254/255 into class position, in this case we need to return 0
	unsigned char retVal = 0;
	unsigned char cls_id = pThis->cs_classes[cls_pos].cl_class;
	char bonus = 0, abil_score = 0;
	if(cls_id != CLASS_TYPE_INVALID)
	{
		CNWClass *cClass = &(NWN_Rules->ru_classes[cls_id]);
		CNWRace *cRace = &(NWN_Rules->ru_races[pThis->cs_race]);
		if(cClass && cClass->SpellCaster)
		{
			CNWClass *otherClass;
			int bArcane = Patch.cls_cast_type[cls_id] & CAST_TYPE_ARCANE;
			int can_enhance_with_prc = 1;
			int level = pThis->cs_classes[cls_pos].cl_level;
			int spellMod = 0;
			if(!(Patch.cls_cast_type[cls_id] & CAST_TYPE_SPONTANEOUS) || Patch.PrestigeClassAffectSpontaneousCasters)
			{
				for(unsigned char x=0;x < pThis->cs_classes_len;x++)
				{
					if(x == cls_pos || pThis->cs_classes[x].cl_class == CLASS_TYPE_INVALID) continue;
					otherClass = &(NWN_Rules->ru_classes[pThis->cs_classes[x].cl_class]);
					if(otherClass->SpellCaster && bArcane == (Patch.cls_cast_type[pThis->cs_classes[x].cl_class] & CAST_TYPE_ARCANE) && pThis->cs_classes[x].cl_level >= level)
					{
						if(pThis->cs_classes[x].cl_level > level || cls_pos < x)
						{
							can_enhance_with_prc = 0;
						}
					}
					if(otherClass->ArcSpellLvlMod && bArcane)
					{
						spellMod+= (pThis->cs_classes[x].cl_level+(otherClass->ArcSpellLvlMod != 1))/otherClass->ArcSpellLvlMod;
					}
					else if(otherClass->DivSpellLvlMod && !bArcane)
					{
						spellMod+= (pThis->cs_classes[x].cl_level+(otherClass->DivSpellLvlMod != 1))/otherClass->DivSpellLvlMod;
					}
				}
			}
			if(can_enhance_with_prc) level+= spellMod;
//			char bonus = 0;char abil_score = 0;
			switch(cClass->PrimaryAbility)
			{
			case ABILITY_STRENGTH:
				abil_score = pThis->cs_str;
				abil_score+= cRace->StrAdjust;
				bonus = pThis->cs_str_mod;
				break;
			case ABILITY_DEXTERITY:
				abil_score = pThis->cs_dex;
				abil_score+= cRace->DexAdjust;
				bonus = pThis->cs_dex_mod;
				break;
			case ABILITY_CONSTITUTION:
				abil_score = pThis->cs_con;
				abil_score+= cRace->ConAdjust;
				bonus = pThis->cs_con_mod;
				break;
			case ABILITY_INTELLIGENCE:
				abil_score = pThis->cs_int;
				abil_score+= cRace->IntAdjust;
				bonus = pThis->cs_int_mod;
				break;
			case ABILITY_WISDOM:
				abil_score = pThis->cs_wis;
				abil_score+= cRace->WisAdjust;
				bonus = pThis->cs_wis_mod;
				break;
			case ABILITY_CHARISMA:
				abil_score = pThis->cs_cha;
				abil_score+= cRace->ChaAdjust;
				bonus = pThis->cs_cha_mod;
				break;
			}
			retVal = cClass->GetSpellGain(level,spell_lvl);
			if(retVal == 255 || abil_score < 10+spell_lvl) retVal = 0;
			else if(spell_lvl > 0)
			{
				if(pThis->cs_classes[cls_pos].cl_specialist) retVal++;
				if(bonus >= spell_lvl) retVal+= ((bonus-spell_lvl)/4)+1;
			}
		}
	}
	unsigned char retValOrig = CNWSCreatureStats__GetSpellGainWithBonus(pThis,NULL,cls_pos,spell_lvl);
	if(retValOrig != retVal && cls_id < 11)
	{
		fprintf(Patch.m_fFile, "o CNWSCreatureStats__GetSpellGainWithBonus: new calculation doesnt match with vanilla! cls_id %i, spell_lvl %i, oldval %i, newval: %i, bonus: %i, abil_score: %i\n",pThis->cs_classes[cls_pos].cl_class,spell_lvl,retValOrig,retVal,bonus,abil_score);fflush(Patch.m_fFile);
	}
	return retVal;
}

unsigned char __fastcall CNWSCreatureStats__GetSpellGainWithBonusAfterLevelUp_Hook(CNWSCreatureStats *pThis, void *, unsigned char cls_pos, unsigned char spell_lvl, CNWLevelStats *lvlstats, unsigned char spell_school, int is_first_lvl)
{
	if(!classes_2da)
	{
		return CNWSCreatureStats__GetSpellGainWithBonusAfterLevelUp(pThis,NULL,cls_pos,spell_lvl,lvlstats,spell_school,is_first_lvl);
	}
	if(cls_pos >= pThis->cs_classes_len) return 0;//sometimes engine passes 254/255 into class position, in this case we need  to return 0
	unsigned char retValOrig = CNWSCreatureStats__GetSpellGainWithBonusAfterLevelUp(pThis,NULL,cls_pos,spell_lvl,lvlstats,spell_school,is_first_lvl);
	unsigned char retVal = 0;
	unsigned char cls_id = is_first_lvl ? lvlstats->ls_class : pThis->cs_classes[cls_pos].cl_class;
	char bonus = 0, abil_score = 0;
	if(cls_id != CLASS_TYPE_INVALID)
	{
		CNWClass *cClass = &(NWN_Rules->ru_classes[cls_id]);
		CNWRace *cRace = &(NWN_Rules->ru_races[pThis->cs_race]);
		if(cClass && cClass->SpellCaster)
		{
			CNWClass *otherClass;
			int bArcane = Patch.cls_cast_type[cls_id] & CAST_TYPE_ARCANE;
			int can_enhance_with_prc = 1;
			int level = is_first_lvl ? 1 : pThis->cs_classes[cls_pos].cl_level+1;
			int spellMod = 0;
			if(!(Patch.cls_cast_type[cls_id] & CAST_TYPE_SPONTANEOUS) || Patch.PrestigeClassAffectSpontaneousCasters)
			{
				for(unsigned char x=0;x < pThis->cs_classes_len;x++)
				{
					if(x == cls_pos || pThis->cs_classes[x].cl_class == CLASS_TYPE_INVALID) continue;
					otherClass = &(NWN_Rules->ru_classes[pThis->cs_classes[x].cl_class]);
					if(otherClass->SpellCaster && bArcane == (Patch.cls_cast_type[pThis->cs_classes[x].cl_class] & CAST_TYPE_ARCANE) && pThis->cs_classes[x].cl_level >= level)
					{
						if(pThis->cs_classes[x].cl_level > level || cls_pos < x)
						{
							can_enhance_with_prc = 0;
						}
					}
					if(otherClass->ArcSpellLvlMod && bArcane)
					{
						spellMod+= (pThis->cs_classes[x].cl_level+(otherClass->ArcSpellLvlMod != 1))/otherClass->ArcSpellLvlMod;
					}
					else if(otherClass->DivSpellLvlMod && !bArcane)
					{
						spellMod+= (pThis->cs_classes[x].cl_level+(otherClass->DivSpellLvlMod != 1))/otherClass->DivSpellLvlMod;
					}
				}
			}
			if(can_enhance_with_prc) level+= spellMod;
//			char bonus = 0;char abil_score = 0;
			switch(cClass->PrimaryAbility)
			{
			case ABILITY_STRENGTH:
				abil_score = pThis->cs_str;
				abil_score+= cRace->StrAdjust;
				bonus = pThis->cs_str_mod;
				break;
			case ABILITY_DEXTERITY:
				abil_score = pThis->cs_dex;
				abil_score+= cRace->DexAdjust;
				bonus = pThis->cs_dex_mod;
				break;
			case ABILITY_CONSTITUTION:
				abil_score = pThis->cs_con;
				abil_score+= cRace->ConAdjust;
				bonus = pThis->cs_con_mod;
				break;
			case ABILITY_INTELLIGENCE:
				abil_score = pThis->cs_int;
				abil_score+= cRace->IntAdjust;
				bonus = pThis->cs_int_mod;
				break;
			case ABILITY_WISDOM:
				abil_score = pThis->cs_wis;
				abil_score+= cRace->WisAdjust;
				bonus = pThis->cs_wis_mod;
				break;
			case ABILITY_CHARISMA:
				abil_score = pThis->cs_cha;
				abil_score+= cRace->ChaAdjust;
				bonus = pThis->cs_cha_mod;
				break;
			}
			if(lvlstats->ls_ability == cClass->PrimaryAbility)//player increased casting ability on this lvl
			{
				abil_score++;
				if((abil_score/2)*2 == abil_score)//new level increased ability modifier too
				{
					bonus++;
				}
			}
			retVal = cClass->GetSpellGain(level,spell_lvl);
			if(retVal == 255 || abil_score < 10+spell_lvl) retVal = 0;
			else if(spell_lvl > 0)
			{
				if(spell_school > 0) retVal++;
				if(bonus >= spell_lvl) retVal+= ((bonus-spell_lvl)/4)+1;
			}
		}
	}
	if(retValOrig != retVal && cls_id < 11)
	{
		fprintf(Patch.m_fFile, "o CNWSCreatureStats__GetSpellGainWithBonusAfterLevelUp: new calculation doesn't match with vanilla! cls_id %i, spell_lvl %i, oldval %i, newval: %i, bonus: %i, abil_score: %i\n",cls_id,spell_lvl,retValOrig,retVal,bonus,abil_score);fflush(Patch.m_fFile);
	}
	return retVal;
}

int __fastcall CNWSCreatureStats__GetSpellMinAbilityMet_Hook(CNWSCreatureStats *pThis, void *, unsigned char cls_pos, unsigned char spell_lvl)
{
	if(cls_pos >= pThis->cs_classes_len) return 0;//sometimes engine passes 254/255 into class position, in this case we need to return 0
	unsigned char cls_id = pThis->cs_classes[cls_pos].cl_class;
	switch(cls_id)
	{
	case CLASS_TYPE_ABERRATION:
	case CLASS_TYPE_ANIMAL:
	case CLASS_TYPE_BEAST:
	case CLASS_TYPE_COMMONER:
	case CLASS_TYPE_CONSTRUCT:
	case CLASS_TYPE_DRAGON:
	case CLASS_TYPE_ELEMENTAL:
	case CLASS_TYPE_FEY:
	case CLASS_TYPE_GIANT:
	case CLASS_TYPE_HUMANOID:
	case CLASS_TYPE_MAGICAL_BEAST:
	case CLASS_TYPE_MONSTROUS:
	case CLASS_TYPE_OUTSIDER:
	case CLASS_TYPE_SHAPECHANGER:
	case CLASS_TYPE_UNDEAD:
	case CLASS_TYPE_VERMIN:
		return 1;
	}
	CNWClass *cClass = &(NWN_Rules->ru_classes[cls_id]);
	CNWRace *cRace = &(NWN_Rules->ru_races[pThis->cs_race]);
	if(cls_id != CLASS_TYPE_INVALID && cClass && cRace && cClass->SpellCaster)
	{
		unsigned char abil_score = 0;
		switch(cClass->PrimaryAbility)
		{
		case ABILITY_STRENGTH:
			abil_score = pThis->cs_str;
			abil_score+= cRace->StrAdjust;
			break;
		case ABILITY_DEXTERITY:
			abil_score = pThis->cs_dex;
			abil_score+= cRace->DexAdjust;
			break;
		case ABILITY_CONSTITUTION:
			abil_score = pThis->cs_con;
			abil_score+= cRace->ConAdjust;
			break;
		case ABILITY_INTELLIGENCE:
			abil_score = pThis->cs_int;
			abil_score+= cRace->IntAdjust;
			break;
		case ABILITY_WISDOM:
			abil_score = pThis->cs_wis;
			abil_score+= cRace->WisAdjust;
			break;
		case ABILITY_CHARISMA:
			abil_score = pThis->cs_cha;
			abil_score+= cRace->ChaAdjust;
			break;
		}
		//fprintf(Patch.m_fFile, "o CNWSCreatureStats__GetSpellMinAbilityMet: cls_pos: %i, spell_lvl: %i, retval: %i.\n",cls_pos,spell_lvl,abil_score >= spell_lvl+10);fflush(Patch.m_fFile);
		return abil_score >= spell_lvl+10;
	}
	return 0;
}

unsigned long __fastcall CServerExoAppInternal__ValidateCreateServerCharacter_Hook(CServerExoAppInternal *pThis, void*, CNWSPlayer *player, void *c, unsigned long l1)
{
	if(Patch.NoServerCharacter)
	{
		return 57922;//Server doesn't allow server vault characters.
	}
	return CServerExoAppInternal__ValidateCreateServerCharacter(pThis,NULL,player,c,l1);
}

int __fastcall CNWSStore__SellItem_Hook(CNWSStore *pThis, void *, CNWSItem *item, CNWSCreature *buyer, unsigned char a1, unsigned char a2)
{
	if(pThis && item && buyer && item->it_infinite == 0)
	{
		unsigned char a1 = 0 ,a2 = 0;
		if(buyer->cre_inventory->FindPosition(item,a1,a2,0))
		{
			pThis->RemoveItem(item);
			buyer->AcquireItem(&item,pThis->obj.obj_generic.obj_id,OBJECT_INVALID,a1,a2,0,1);
			return 1;
		}
		return 0;
	}
	return CNWSStore__SellItem(pThis,NULL,item,buyer,a1,a2);
}

void __fastcall CServerExoAppInternal__RemovePCFromWorld_Hook(CServerExoAppInternal *srv, void *, CNWSPlayer *player)
{
	if(Patch.module_script_leave.text != "")
	{
		srv->GetModule()->mod_last_exit = player->obj_id;
		NWN_VirtualMachine->Runscript(&Patch.module_script_leave,srv->srv_obj_module);
	}
	CServerExoAppInternal__RemovePCFromWorld(srv, NULL, player);
}

void __fastcall CGameEffect__SetCreator_Hook(CGameEffect *pThis, void*, unsigned long creatorID)
{
	pThis->eff_creator = creatorID;
	if(creatorID != OBJECT_INVALID)
	{
		CNWSObject *creator = (CNWSObject*)NWN_AppManager->app_server->GetGameObject(creatorID);
		if(creator)
		{
			int nLevel = -1;
			if(creator->obj_generic.obj_type2 == OBJECT_TYPE2_AREA_OF_EFFECT)
			{
				CNWSAreaOfEffectObject *aoe = (CNWSAreaOfEffectObject*)creator;
				if(aoe)
				{
					pThis->eff_spellid = aoe->SpellID;
					pThis->eff_creator = aoe->CreatorID;
					nLevel = creator->obj_vartable.GetInt(CExoString("AOE_LEVEL"));
					if(nLevel > -1)
					{
						pThis->eff_casterlvl = nLevel;
					}
				}
				return;
			}
			else if(creator->obj_generic.obj_type2 == OBJECT_TYPE2_PLACEABLE)
			{
				CNWSPlaceable *plc = (CNWSPlaceable*)creator;
				if(plc)
				{
					pThis->eff_spellid = plc->effect_spell_id;
				}
				return;
			}
			else if(creator->obj_generic.obj_type2 == OBJECT_TYPE2_CREATURE)
			{
				CNWSCreature *cre = (CNWSCreature*)creator;
				if(cre && cre->effect_spell_id > -1)
				{
					pThis->eff_spellid = cre->effect_spell_id;
					if(cre->cre_item_spell_item != OBJECT_INVALID)
					{
						nLevel = cre->cre_item_spell_level;
						CNWSObject *item = (CNWSObject*)NWN_AppManager->app_server->GetGameObject(cre->cre_item_spell_item);
						if(pThis->eff_spellid > -1 && item && item->obj_generic.obj_type2 == OBJECT_TYPE2_ITEM)
						{
							//community patch caster level override/modifier feature
							char *sVarName = new char[64];
							sprintf_s(sVarName,64,"%i_CASTER_LEVEL_OVERRIDE",pThis->eff_spellid);
							int cl_override = item->obj_vartable.GetInt(CExoString(sVarName));
							if(!cl_override) cl_override = item->obj_vartable.GetInt(CExoString("ITEM_CASTER_LEVEL_OVERRIDE"));
							if(cl_override) nLevel = cl_override;
							else nLevel+= item->obj_vartable.GetInt(CExoString("ITEM_CASTER_LEVEL_MODIFIER"));
						}
					}
					else if(creator->obj_last_spell_class != 255)
					{
						nLevel = cre->cre_stats->GetClassLevel(creator->obj_last_spell_class,true);
						//include prestige classes into calculation
						if(creator->obj_last_spell_feat == 0xFFFF && NWN_Rules->ru_spells->GetSpell(pThis->eff_spellid)->UserType == 1)
						{
							int cls_id = cre->cre_stats->cs_classes[creator->obj_last_spell_class].cl_class;
							CNWClass *cClass = &(NWN_Rules->ru_classes[cls_id]);
							bool bArcane = NWN_Rules->IsArcaneClass(cls_id) != 0;
							bool bDivine = cClass->SpellCaster == 1;
							for(unsigned char i = 0; i < cre->cre_stats->cs_classes_len; i++)//todo vyresit double castery
							{
								cClass = &(NWN_Rules->ru_classes[cre->cre_stats->cs_classes[i].cl_class]);
								if(bArcane && cClass->ArcSpellLvlMod && (cre->cre_stats->cs_classes[i].cl_class != 34 || Patch.PMCasterLevel))
								{
									nLevel+= (cre->cre_stats->GetClassLevel(i,true)+(cClass->ArcSpellLvlMod != 1))/cClass->ArcSpellLvlMod;
								}
								else if(bDivine && cClass->DivSpellLvlMod)
								{
									nLevel+= (cre->cre_stats->GetClassLevel(i,true)+(cClass->DivSpellLvlMod != 1))/cClass->DivSpellLvlMod;
								}
							}
						}
					}
					else//monster special ability
					{
						nLevel = (NWN_Rules->ru_spells->GetSpell(pThis->eff_spellid)->sp_level_innate*2)-1;
						if(nLevel < 10)
						{
							nLevel = 10;
						}
					}
				}
			}
			//community patch caster level override/modifier feature
			if(pThis->eff_spellid > -1 && creator->obj_last_spell_feat == 0xFFFF && NWN_Rules->ru_spells->GetSpell(pThis->eff_spellid)->UserType == 1)
			{
				char *sVarName = new char[64];
				sprintf_s(sVarName,64,"%i_CASTER_LEVEL_OVERRIDE",pThis->eff_spellid);
				int cl_override = creator->obj_vartable.GetInt(CExoString(sVarName));
				if(!cl_override) cl_override = creator->obj_vartable.GetInt(CExoString(creator->obj_last_spell_class == 255 ? "SPECIAL_ABILITY_CASTER_LEVEL_OVERRIDE" : "SPELL_CASTER_LEVEL_OVERRIDE"));
				if(cl_override) nLevel = cl_override;
				else nLevel+= creator->obj_vartable.GetInt(CExoString(creator->obj_last_spell_class == 255 ? "SPECIAL_ABILITY_CASTER_LEVEL_MODIFIER" : "SPELL_CASTER_LEVEL_MODIFIER"));
			}
			pThis->eff_casterlvl = nLevel;
			//fprintf(Patch.m_fFile, "o SetCreator: effect caster level set to: %i\n",nLevel);fflush(Patch.m_fFile);
		}
	}
}

int __fastcall CNWVirtualMachineCommands__ExecuteCommandApplyEffectOnObject_Hook(CVirtualMachineCommands *vm_cmds, void*, int cmd, int args)
{
	int32_t dur_type;
	CGameEffect *eff;
	nwn_objid_t obj_id;
	float duration;
	if(!NWN_VirtualMachine->StackPopInteger(&dur_type) || !NWN_VirtualMachine->StackPopEngineStructure(0,(void **)&eff) || !NWN_VirtualMachine->StackPopObject(&obj_id) || !NWN_VirtualMachine->StackPopFloat(&duration))
	{
		return -639;
	}
	CNWSObject *target = (CNWSObject*)(NWN_AppManager->app_server->GetGameObject(obj_id));
	if(target)
	{
		if(dur_type == DURATION_TYPE_TEMPORARY)
		{
			eff->eff_duration = duration;
		}
		else if(dur_type < DURATION_TYPE_PERMANENT || dur_type > DURATION_TYPE_INNATE)
		{
			dur_type = DURATION_TYPE_INSTANT;
		}
		eff->eff_dursubtype = dur_type|(eff->eff_dursubtype & 0x18);
		if(eff->eff_type == EFFECT_TRUETYPE_LINK)
		{
			target->obj_pending_effect_removal = 1;
		}
		target->ApplyEffect(eff, 0, 1);
		target->obj_pending_effect_removal = 0;
	}
	else
	{
		eff->dtor();
	}
	return 0;
}

int __fastcall CNWSCreature__EventHandler_Hook(CNWSCreature *pThis, void*, int arg1, int arg2, float arg3, int arg4, int arg5)
{
	if(arg1 == 19)//19 onhitcast spell, 27 boot pc, 5 apply effect, 14 remove effect, 4 remove from area, 9 play animation, 1 timed event, 20 broadcast aoo, 21 broadcast safe projectile, 8 spell impact, 10 signal event, 11 destroy object
	{
		int32_t spell_id = pThis->obj.obj_last_spell_id;
		nwn_objid_t spell_target = pThis->obj.obj_last_spell_target;
		uint32_t spell_item_item = pThis->cre_item_spell_item;
		Vector spell_loc = pThis->obj.obj_last_spell_location;
		int retVal = CNWSCreature__EventHandler(pThis,NULL,arg1,arg2,arg3,arg4,arg5);
		//push back old values
		pThis->obj.obj_last_spell_id = spell_id;
		pThis->obj.obj_last_spell_target = spell_target;
		pThis->cre_item_spell_item = spell_item_item;
		pThis->obj.obj_last_spell_location = spell_loc;
		return retVal;
	}
	else
	{
		return CNWSCreature__EventHandler(pThis,NULL,arg1,arg2,arg3,arg4,arg5);
	}
}

int __fastcall CNWSCreature__StartBarter_Hook(CNWSCreature *pThis, void*, unsigned long targetID, unsigned long itemID, int arg1)
{
	if(pThis && targetID && itemID && !arg1)
	{
		CNWSItem *item = NWN_AppManager->app_server->srv_internal->GetItemByGameObjectID(itemID);
		if(item && item->it_cursed)
		{
			return 0;
		}
	}
	return CNWSCreature__StartBarter(pThis,NULL,targetID,itemID,arg1);
}

int __fastcall CNWSCreature__AddPickPocketAction_Hook(CNWSCreature *pThis, void*, unsigned long targetID)
{
	if(pThis && pThis->cre_stats->GetCanUseSkill(13))
	{
		CNWSObject* object = (CNWSObject*)(NWN_AppManager->app_server->GetGameObject(targetID));
		if(object && object->obj_generic.obj_type2 == OBJECT_TYPE2_CREATURE)
		{
			pThis->cre_attempted_spell = targetID;
			if(NWN_VirtualMachine->Runscript(&CExoString("70_s2_pickpocket"),pThis->obj.obj_generic.obj_id,1))
			{
				return 4;
			}
		}
	}
	return CNWSCreature__AddPickPocketAction(pThis,NULL,targetID);
}

void __fastcall CNWSCreature__RemoveBadEffects_Hook(CNWSCreature *pThis, void*)//code by jd28
{
	CGameEffect *eff;
	uint16_t subtype = 0;
	uint16_t durtype = 0;
	unsigned int i = 0;

	while(i < pThis->obj.obj_effects_len)
	{
		eff = pThis->obj.obj_effects[i];
		subtype = eff->eff_dursubtype & SUBTYPE_MASK;
		durtype = eff->eff_dursubtype & DURATION_TYPE_MASK;
		//fprintf(Patch.m_fFile, "o CNWSCreature__RemoveBadEffects: nth: %i type: %i %i %i %i\n",i,eff->eff_type,eff->eff_dursubtype,subtype,durtype);fflush(Patch.m_fFile);

		// When resting if an effect duration type is temporary or permenant and
		// is of the subtype magical or extraordinary, the effect is remove.
		if((durtype == DURATION_TYPE_TEMPORARY || durtype == DURATION_TYPE_PERMANENT ) && (subtype == SUBTYPE_MAGICAL || subtype == SUBTYPE_EXTRAORDINARY))
		{
			//fprintf(Patch.m_fFile, "o found removing\n");fflush(Patch.m_fFile);
			pThis->obj.RemoveEffectById(eff->eff_id);
		}
		else
		{
			++i;
		}
	}
}

int __fastcall CNWSEffectListHandler__OnApplyDefensiveStance_Hook(CNWSEffectListHandler *pThis, void*, CNWSObject *obj, CGameEffect *eff, int n)
{
	CNWSCreature * cre = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(obj->obj_generic.obj_id);
	if(cre != NULL && cre->cre_is_pc && cre->cre_mode_combat == 11)
	{
		cre->SetEffectSpellId(641);
		if(NWN_VirtualMachine->Runscript(&CExoString("70_s2_ddstance"),obj->obj_generic.obj_id,1) == 1)
		{
			for(unsigned int nEffect = 0;nEffect < cre->obj.obj_effects_len;nEffect++)
			{
				CGameEffect* eEffect = *(cre->obj.obj_effects+nEffect);
				if(eEffect->eff_spellid == 641 && eEffect->eff_type == 94)
				{
					eEffect->eff_type = 95;
					break;
				}
			}
			return 0;
		}
	}
	return CNWSEffectListHandler__OnApplyDefensiveStance(pThis,NULL,obj,eff,n);
}

float __fastcall CNWSCreature__MaxAttackRange_Hook(CNWSCreature *pThis, void*, unsigned long targetID, int arg1, int arg2)
{
//fprintf(Patch.m_fFile, "o CNWSCreature__MaxAttackRange: %i %i %i\n",targetID,arg1,arg2);fflush(Patch.m_fFile);
float fReturn = CNWSCreature__MaxAttackRange(pThis,NULL,targetID,arg1,arg2);
//fprintf(Patch.m_fFile, "o CNWSCreature__MaxAttackRange: %f\n",fReturn);fflush(Patch.m_fFile);
CNWSItem *item = pThis->cre_equipment->GetItemInSlot(16);
 if(item == NULL)
 {//fprintf(Patch.m_fFile, "o CNWSCreature__MaxAttackRange: unarmed, pushing 2.5 instead\n");fflush(Patch.m_fFile);
 fReturn = 2.5;
 }
return fReturn;
}

int __fastcall CNWSCreatureStats__GetSpellResistance_Hook( CNWSCreatureStats *pThis, void*)
{
	if(pThis != NULL)
	{
		int nOverride = pThis->cs_original->obj.obj_vartable.GetInt(CExoString("SPELL_RESISTANCE_OVERRIDE"));
		if(nOverride != 0)
		{
			return nOverride > 0 ? nOverride : 0;
		}
	}
	return CNWSCreatureStats__GetSpellResistance(pThis, NULL);
}

int __fastcall CNWSEffectListHandler__OnApplyKnockdown_Hook(CNWSEffectListHandler *pThis, void*, CNWSObject *obj, CGameEffect *eff, int arg1)
{
	CNWSObject *attacker = (CNWSObject*)NWN_AppManager->app_server->GetGameObject(eff->eff_creator);
	if(obj != NULL && obj->obj_generic.obj_type2 == OBJECT_TYPE2_CREATURE && attacker != NULL && attacker->obj_generic.obj_type2 == OBJECT_TYPE2_CREATURE)
	{
		CNWSCreature *cre = (CNWSCreature*)attacker;
		CNWSCreature *pc = (CNWSCreature*)obj;
		if(pc != NULL && pc->cre_is_pc && cre != NULL)
		{
			obj->obj_vartable.SetInt(CExoString("KNOCKDOWN_TYPE"),eff->eff_integers[0],1);
			obj->obj_vartable.SetInt(CExoString("KNOCKDOWN_AB"),cre->cre_combat_round->AttackData->ToHitMod+cre->cre_combat_round->AttackData->ToHitRoll,1);
			obj->obj_vartable.SetObject(CExoString("KNOCKDOWN_WPN"),cre->cre_combat_round->GetCurrentAttackWeapon(1)->obj.obj_generic.obj_id);
			if(NWN_VirtualMachine->Runscript(&CExoString("70_s2_knockdown"),obj->obj_generic.obj_id,1) == 1)
			{
				return 0xC;
			}
		}
	}
	return CNWSEffectListHandler__OnApplyKnockdown(pThis,NULL,obj,eff,arg1);
}

int __fastcall CNWSEffectListHandler__OnApplyDisarm_Hook(CNWSEffectListHandler *pThis, void*, CNWSObject *obj, CGameEffect *eff, int arg1)
{
	CNWSObject *attacker = (CNWSObject*)NWN_AppManager->app_server->GetGameObject(eff->eff_creator);
	if(obj != NULL && obj->obj_generic.obj_type2 == OBJECT_TYPE2_CREATURE && attacker != NULL && attacker->obj_generic.obj_type2 == OBJECT_TYPE2_CREATURE)
	{
		CNWSCreature *cre = (CNWSCreature*)attacker;
		CNWSCreature *pc = (CNWSCreature*)obj;
		if(pc != NULL && pc->cre_is_pc && cre != NULL)
		{
			obj->obj_vartable.SetInt(CExoString("DISARM_TYPE"),eff->eff_integers[0],1);
			obj->obj_vartable.SetInt(CExoString("DISARM_AB"),cre->cre_combat_round->AttackData->ToHitMod+cre->cre_combat_round->AttackData->ToHitRoll,1);
			obj->obj_vartable.SetObject(CExoString("DISARM_WPN"),cre->cre_combat_round->GetCurrentAttackWeapon(1)->obj.obj_generic.obj_id);
			if(NWN_VirtualMachine->Runscript(&CExoString("70_s2_disarm"),obj->obj_generic.obj_id,1) == 1)
			{
				return 0xC;
			}
		}
	}
	return CNWSEffectListHandler__OnApplyDisarm(pThis,NULL,obj,eff,arg1);
}

int __fastcall CNWSCreatureStats__GetFavoredEnemyBonus_Hook(CNWSCreatureStats *pThis, void*, CNWSCreature *cre)
{
	int modifier = ((CNWSObject*)(pThis->cs_original))->obj_vartable.GetInt(CExoString("FE_MODIFIER"));
	if(racialtypes_2da)
	{
		int feat = 0;
		if(racialtypes_2da->GetINTEntry_strcol(cre->cre_stats->cs_race,CExoString("FavoredEnemyFeat"),&feat) && feat > 0)
		{
			if(pThis->HasFeat(feat))
			{
				return 1+(pThis->GetNumLevelsOfClass(pThis->GetFeatSourceClass(feat)))/5+modifier;
			}
			return 0;
		}
	}
	int RetVal = CNWSCreatureStats__GetFavoredEnemyBonus(pThis,NULL,cre);
	return RetVal > 0 ? RetVal+modifier : RetVal;
}

int __fastcall CNWSTrigger__GetCanFireTrapOnObject_Hook(CNWSTrigger *pThis, void*, unsigned long targetID, int arg1)
{
	int retVal = CNWSTrigger__GetCanFireTrapOnObject(pThis,NULL,targetID,arg1);
	if(Patch.TrapImmunity && retVal && !pThis->obj.obj_vartable.GetInt(CExoString("DISALLOW_FLYING")))
	{
		CNWSObject* object = (CNWSObject*)(NWN_AppManager->app_server->GetGameObject(targetID));
		if(object != NULL && object->obj_generic.obj_type2 == OBJECT_TYPE2_CREATURE && !object->GetDead())
		{
			if(CNWSCreature *cre = (CNWSCreature*)object)
			{
				switch(cre->cre_appearance_info.cai_appearance)
				{
				case 186:
				case 10:
				case 11:
				case 52:
				case 53:
				case 374:
				case 144:
				case 55:
				case 100:
				case 105:
				case 103:
				case 106:
				case 107:
				case 108:
				case 109:
				case 110:
				case 111:
				case 112:
				case 113:
				case 114:
				case 115:
				case 104:
				case 145:
				case 146:
				case 147:
				case 156:
				case 116:
				case 187:
				case 378:
				case 377:
				case 381:
				case 383:
				case 382:
				case 385:
				case 379:
				case 376:
				case 384:
				case 380:
				case 69:
				case 68:
				case 401:
				case 402:
				case 403:
				case 419:
				case 430:
				case 472:
				case 73:
				case 299://Beholder G'Zhorb
				case 460://Halaster
				case 465://Masterius full power
				case 7:
				case 291:
				case 375:
					return 0;
				}
				return !object->obj_vartable.GetInt(CExoString("FLYING"));
			}
		}
	}
	return retVal;
}


unsigned long __fastcall CNWSModule__LoadModuleFinish_Hook(CNWSModule *pThis, void*)
{
	unsigned long retVal = CNWSModule__LoadModuleFinish(pThis,NULL);
	InitializeWeaponFeats2DA();
	InitializeRacialTypes2DA();
	InitializeClasses2DA();
	//InitializeSpells2DA();
	InitializeSpells_Level2DA();
	Patch.InitializeModuleSwitches(pThis);
	//OnClientLeave improvement initialization
	Patch.module_script_leave = pThis->mod_scripts[5];
	pThis->mod_scripts[5] = CExoString("");
	return retVal;
}

int __fastcall CNWSMessage__HandlePlayerToServerMessage_Hook(CNWSMessage *pMessage, void *, unsigned long nPlayerID, unsigned char *pData, unsigned long nLen)
{
	int nType = pData[1];
	int nSubtype = pData[2];

	Patch.Log(0, "Message: PID %d, type %i, subtype %i\n", nPlayerID, nType, nSubtype);

	if(nType == 1)
	{
		Patch.SendHakList(pMessage,nPlayerID);
	}
	else if(nType == 6 && nSubtype == 119)
	{
		CNWSPlayer *player = NWN_AppManager->app_server->srv_internal->GetClientObjectByPlayerId(nPlayerID,1);
		if(player)
		{
			CGenericObject *obj = player->GetGameObject();
			CNWSCreature *cre = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(obj->obj_id);
			if(cre)
			{
				cre->field_B48 = cre->GetAssociateId(2,1);
				cre->PossessFamiliar();
			}
		}
	}
	return CNWSMessage__HandlePlayerToServerMessage(pMessage,NULL,nPlayerID,pData,nLen);
}

char __fastcall CNWSCreatureStats__GetTotalACSkillMod_Hook(CNWSCreatureStats *pThis, void*)
{
	if(Patch.NoTumbleAC)
	{
		return 0;
	}
	if(pThis->cs_original->obj.obj_vartable.MatchIndex(CExoString("TumbleAC"),VARIABLE_TYPE_INT,0) != NULL)
	{
		int nAC = pThis->cs_original->obj.obj_vartable.GetInt(CExoString("TumbleAC"));
		if(nAC > 127)
			return 127;
		else if(nAC < -127)
			return -127;
		return nAC;
	}
	return CNWSCreatureStats__GetTotalACSkillMod(pThis,NULL);
}


unsigned char __fastcall CNWSItem__GetMinEquipLevel_Hook(CNWSItem *pThis, void*)
{
	if(pThis != NULL && pThis->obj.obj_vartable.MatchIndex(CExoString("CILR"),VARIABLE_TYPE_INT,0) != NULL)
	{
		int cILR = pThis->obj.obj_vartable.GetInt(CExoString("CILR"));
		if(cILR > 255)
			return 255;
		else if(cILR < 0)
			return 0;
		return cILR;
	}
	return CNWSItem__GetMinEquipLevel(pThis,NULL);
}

void __fastcall CNWSObject__ClearAllPartyInvalidActions_Hook(CNWSObject *pThis, void *)
{
	if(pThis != NULL && pThis->obj_generic.obj_type2 == OBJECT_TYPE2_CREATURE)
	{
		return;
	}
	CNWSObject__ClearAllPartyInvalidActions(pThis, NULL);
}

int __fastcall CNWSCreatureStats__ResolveSpecialAttackDamageBonus_Hook(CNWSCreatureStats *pThis, void*, CNWSCreature *target)
{
	if(target == NULL)//fix for crash exploit
	{
		return 0;
	}
	CNWSCombatAttackData *attack_data = pThis->cs_original->cre_combat_round->GetAttack(pThis->cs_original->cre_combat_round->CurrentAttack);
	int attack_type = attack_data->AttackType;//301 smite evil   472 smite good   39 stun fist = feat id
	if(attack_type == 39)//stunning fist
	{
		for(unsigned char x=0;x < pThis->cs_classes_len;x++)
		{
			if(pThis->cs_classes[x].cl_class == CLASS_TYPE_MONK)
			{
				return 0;//no damage penalty for monks
			}
		}
		return -4;
	}
	if(attack_type == 301)//smite evil
	{
		if(target->cre_stats->cs_al_goodevil > 30)
		{
			return 0;
		}
	}
	else if(attack_type == 472)//smite good
	{
		if(target->cre_stats->cs_al_goodevil < 70)
		{
			return 0;
		}
	}
	else
	{
		return 0;
	}
	int nDamage = 0;
	unsigned char granted;
	CNWClass *cClass;
	for(unsigned char x=0;x < pThis->cs_classes_len;x++)
	{
		cClass = &(NWN_Rules->ru_classes[pThis->cs_classes[x].cl_class]);
		if(cClass->IsGrantedFeat(attack_type,granted))
		{
			nDamage+= pThis->cs_classes[x].cl_level;
		}
	}
	if(nDamage > 0)
	{
		int multiplier = 0;
		if(pThis->HasFeat(833))
		{
			multiplier = 10;
		}
		else if(pThis->HasFeat(832))
		{
			multiplier = 9;
		}
		else if(pThis->HasFeat(831))
		{
			multiplier = 8;
		}
		else if(pThis->HasFeat(830))
		{
			multiplier = 7;
		}
		else if(pThis->HasFeat(829))
		{
			multiplier = 6;
		}
		else if(pThis->HasFeat(828))
		{
			multiplier = 5;
		}
		else if(pThis->HasFeat(827))
		{
			multiplier = 4;
		}
		else if(pThis->HasFeat(826))
		{
			multiplier = 3;
		}
		else if(pThis->HasFeat(825))
		{
			multiplier = 2;
		}
		else if(pThis->HasFeat(824))
		{
			multiplier = 1;
		}
		return nDamage+multiplier*nDamage;
	}
	return 0;
}

void __fastcall CNWSCreature__UpdateAttributesOnEffect_Hook(CNWSCreature *pThis, void*, CGameEffect *eff, int arg1)
{
	if(Patch.helper == 40 || pThis->cre_pm_IsPolymorphed)
	{
		int prev = Patch.helper;
		Patch.helper = 39;
		CNWSCreature__UpdateAttributesOnEffect(pThis,NULL,eff,arg1);
		Patch.helper = prev;
	}
	else
	{
		CNWSCreature__UpdateAttributesOnEffect(pThis,NULL,eff,arg1);
	}
	//support for custom spellcasters based on str/dex/con cast ability
	if(eff->eff_type == EFFECT_TRUETYPE_ABILITY_INCREASE && (eff->eff_integers[0] == ABILITY_STRENGTH || eff->eff_integers[0] == ABILITY_DEXTERITY || eff->eff_integers[0] == ABILITY_CONSTITUTION))
	{
		for(unsigned char cls_pos = 0;cls_pos<pThis->cre_stats->cs_classes_len;cls_pos++)
		{
			unsigned char cls_id = pThis->cre_stats->cs_classes[cls_pos].cl_class;
			CNWClass *cClass = &(NWN_Rules->ru_classes[cls_id]);
			if(cClass && cClass->SpellCaster && cClass->PrimaryAbility == eff->eff_integers[0])
			{
				pThis->cre_stats->UpdateNumberMemorizedSpellSlots();
				pThis->cre_stats->AdjustSpellUsesPerDay();
				break;
			}
		}
	}
}

int __fastcall CNWSItemPropertyHandler__ApplyBonusSpellOfLevel_Hook(CNWSItemPropertyHandler *pThis, void*, CNWSItem *item, int *ip, CNWSCreature *cre, unsigned long l, int i)
{
	int prev = Patch.helper;
	if(prev == 40 || cre->cre_pm_IsPolymorphed)
	{
		if(cre->cre_pm_IsPolymorphed)//polymorph skin or weapon, skip addition and mark item as merged to enforce skip also removal of this itemproperty
		{
			item->obj.obj_vartable.SetInt(CExoString("MERGED"),1,1);
			return 20;
		}
		else if(item->obj.obj_vartable.GetInt(CExoString("MERGED")) == 1)//this item was merged, skip addition
		{
			return 20;
		}
		Patch.helper = 39;//for other cases set helper value to enforce unready spell slot in SetNumberMemorizedSpellSlots
	}
	int retVal = CNWSItemPropertyHandler__ApplyBonusSpellOfLevel(pThis,NULL,item,ip,cre,l,i);
	Patch.helper = prev;
	return retVal;
}

int __fastcall CNWSItemPropertyHandler__RemoveBonusSpellOfLevel_Hook(CNWSItemPropertyHandler *pThis, void*, CNWSItem *item, int *ip, CNWSCreature *cre, unsigned long l)
{
	int prev = Patch.helper;
	if(prev == 40 || cre->cre_pm_IsPolymorphed)
	{
		if(item->obj.obj_vartable.GetInt(CExoString("MERGED")) == 1)//this item was merged, skip addition
		{
			return 16;
		}
		Patch.helper = 39;//for other cases set helper value to enforce unready spell slot in SetNumberMemorizedSpellSlots
	}
	int retVal = CNWSItemPropertyHandler__RemoveBonusSpellOfLevel(pThis,NULL,item,ip,cre,l);
	Patch.helper = prev;
	return retVal;
}


void __fastcall CNWSCreatureStats_ClassInfo__SetNumberMemorizedSpellSlots_Hook(CNWSCreatureClass *pThis, void*, unsigned char spell_level, unsigned char spell_num)
{
	if(Patch.helper == 39)
	{
		int numNow = pThis->GetNumberMemorizedSpellSlots(spell_level);
		if(spell_num < numNow)
		{
			int numUnready = numNow-spell_num;
			for(int i = 1;i<=numUnready;i++)
			{
				fprintf(Patch.m_fFile, "o Spell slots in polymorph workaround: unreadying spell at level: %i pos: %i\n",spell_level,numNow-i);fflush(Patch.m_fFile);
				pThis->SetMemorizedSpellInSlotReady(spell_level,numNow-i,0);
			}
		}
		return;
	}
	CNWSCreatureStats_ClassInfo__SetNumberMemorizedSpellSlots(pThis,NULL,spell_level,spell_num);
}

int __fastcall CNWSItemPropertyHandler__RemoveHolyAvenger_Hook(CNWSItemPropertyHandler *pThis, void*, CNWSItem *item, int *ip, CNWSCreature *cre, unsigned long l)
{
	for(unsigned int nEffect = 0;nEffect < cre->obj.obj_effects_len;nEffect++)
	{
		CGameEffect *e = *(cre->obj.obj_effects+nEffect);
		if(/*e->eff_dursubtype == 3 && */e->eff_spellid == 538 && e->eff_creator == item->obj.obj_generic.obj_id)
		{
			cre->obj.RemoveEffect(e);
			continue;
		}
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
		return CNWSCreature__GetRelativeWeaponSize((CNWSCreature*)NWN_AppManager->app_server->GetGameObject(weapon->it_container_obj), NULL, weapon);
	}
	return CNWSCreature__GetRelativeWeaponSize(pThis, NULL, weapon);
}

int __fastcall CNWSCreature__GetUseMonkAbilities_Hook(CNWSCreature *pThis, void*)
{
	if(Patch.NoMonkAbilities && pThis->cre_pm_IsPolymorphed)
	{
		return 0;
	}
	return CNWSCreature__GetUseMonkAbilities(pThis,NULL);
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
		return pThis->Creature->cre_equipment->GetItemInSlot(slot);//fix for Ki critical for offhand weapons
	}
	return CNWSCombatRound__GetCurrentAttackWeapon(pThis, NULL, n);
}

int __fastcall CNWSCreatureStats__GetCriticalHitRoll_Hook(CNWSCreatureStats *pThis, void*, int n)
{
	if(pThis != NULL && pThis->cs_original->obj.obj_generic.obj_type2 == OBJECT_TYPE2_CREATURE)
	{
		Patch.hand = (n+1)*16;
	}
	return CNWSCreatureStats__GetCriticalHitRoll(pThis, NULL, n);
}

void __fastcall CNWSCreature__ResolveAttack_Hook(CNWSCreature *pThis, void*, unsigned long target, int i, int i2)
{
	nwn_objid_t target_prev = pThis->cre_attack_target;
	CNWSCreature__ResolveAttack(pThis, NULL, target, i, i2);
	if(pThis->cre_is_pc && pThis->cre_combat_round->NumCircleKicks == 0 && target_prev != OBJECT_INVALID && target_prev != target) 
	{
		pThis->cre_combat_round->NumCircleKicks = -1;
		CNWSObject* object = (CNWSObject*)(NWN_AppManager->app_server->GetGameObject(target_prev));
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

int __fastcall CNWSCreatureStats__GetWeaponFinesse_Hook(CNWSCreatureStats *pThis, void*, CNWSItem *item)
{
	if(item && item->obj.obj_vartable.MatchIndex(CExoString("finesse"),VARIABLE_TYPE_INT,0) != NULL)
	{
		return item->obj.obj_vartable.GetInt(CExoString("finesse"));
	}
	return CNWSCreatureStats__GetWeaponFinesse(pThis, NULL, item);
}

int __fastcall CNWSCreatureStats__GetWeaponFocus_Hook(CNWSCreatureStats *pThis, void*, CNWSItem *item)
{
	if(weaponfeats_2da && weaponfeats_2da->tda_rows_len > 0)
	{
		int retVal = 0;
		weaponfeats_2da->GetINTEntry_intcol(item ? item->it_baseitemtype : 36,1,&retVal);
		if(retVal > 0)
		{
			return pThis->HasFeat(retVal);
		}
		return FALSE;
	}
	else if(item && item->it_baseitemtype == 95)
	{
		return pThis->HasFeat(1072);
	}
	return CNWSCreatureStats__GetWeaponFocus(pThis, NULL, item);
}

int __fastcall CNWSCreatureStats__GetWeaponImprovedCritical_Hook(CNWSCreatureStats *pThis, void*, CNWSItem *item)
{
	if(weaponfeats_2da && weaponfeats_2da->tda_rows_len > 0)
	{
		int retVal = 0;
		weaponfeats_2da->GetINTEntry_intcol(item ? item->it_baseitemtype : 36,2,&retVal);
		if(retVal > 0)
		{
			return pThis->HasFeat(retVal);
		}
		return FALSE;
	}
	return CNWSCreatureStats__GetWeaponImprovedCritical(pThis, NULL, item);
}

int __fastcall CNWSCreatureStats__GetWeaponSpecialization_Hook(CNWSCreatureStats *pThis, void*, CNWSItem *item)
{
	if(weaponfeats_2da && weaponfeats_2da->tda_rows_len > 0)
	{
		int retVal = 0;
		weaponfeats_2da->GetINTEntry_intcol(item ? item->it_baseitemtype : 36,3,&retVal);
		if(retVal > 0)
		{
			return pThis->HasFeat(retVal);
		}
		return FALSE;
	}
	return CNWSCreatureStats__GetWeaponSpecialization(pThis, NULL, item);
}

int __fastcall CNWSCreatureStats__GetEpicWeaponFocus_Hook(CNWSCreatureStats *pThis, void*, CNWSItem *item)
{
	if(weaponfeats_2da && weaponfeats_2da->tda_rows_len > 0)
	{
		int retVal = 0;
		weaponfeats_2da->GetINTEntry_intcol(item ? item->it_baseitemtype : 36,4,&retVal);
		if(retVal > 0)
		{
			return pThis->HasFeat(retVal);
		}
		return FALSE;
	}
	return CNWSCreatureStats__GetEpicWeaponFocus(pThis, NULL, item);
}

int __fastcall CNWSCreatureStats__GetEpicWeaponSpecialization_Hook(CNWSCreatureStats *pThis, void*, CNWSItem *item)
{
	if(weaponfeats_2da && weaponfeats_2da->tda_rows_len > 0)
	{
		int retVal = 0;
		weaponfeats_2da->GetINTEntry_intcol(item ? item->it_baseitemtype : 36,5,&retVal);
		if(retVal > 0)
		{
			return pThis->HasFeat(retVal);
		}
		return FALSE;
	}
	return CNWSCreatureStats__GetEpicWeaponSpecialization(pThis, NULL, item);
}

int __fastcall CNWSCreatureStats__GetEpicWeaponOverwhelmingCritical_Hook(CNWSCreatureStats *pThis, void*, CNWSItem *item)
{
	if(weaponfeats_2da && weaponfeats_2da->tda_rows_len > 0)
	{
		int retVal = 0;
		weaponfeats_2da->GetINTEntry_intcol(item ? item->it_baseitemtype : 36,6,&retVal);
		if(retVal > 0)
		{
			return pThis->HasFeat(retVal);
		}
		return FALSE;
	}
	return CNWSCreatureStats__GetEpicWeaponOverwhelmingCritical(pThis, NULL, item);
}

int __fastcall CNWSCreatureStats__GetEpicWeaponDevastatingCritical_Hook(CNWSCreatureStats *pThis, void*, CNWSItem *item)
{
	if(weaponfeats_2da && weaponfeats_2da->tda_rows_len > 0)
	{
		int retVal = 0;
		weaponfeats_2da->GetINTEntry_intcol(item ? item->it_baseitemtype : 36,7,&retVal);
		if(retVal > 0)
		{
			return pThis->HasFeat(retVal);
		}
		return FALSE;
	}
	return CNWSCreatureStats__GetEpicWeaponDevastatingCritical(pThis, NULL, item);
}

int __fastcall CNWSCreatureStats__GetIsWeaponOfChoice_Hook(CNWSCreatureStats *pThis, void*, uint32_t BaseItemType)
{
	if(weaponfeats_2da && weaponfeats_2da->tda_rows_len > 0)
	{
		int retVal = 0;
		weaponfeats_2da->GetINTEntry_intcol(BaseItemType,8,&retVal);
		if(retVal > 0)
		{
			return pThis->HasFeat(retVal);
		}
		return FALSE;
	}
	return CNWSCreatureStats__GetIsWeaponOfChoice(pThis, NULL, BaseItemType);
}

int __fastcall CNWSCreatureStats__GetUseMonkAttackTables_Hook(CNWSCreatureStats *pThis, void*, int a2)
{
	if(pThis->cs_original->GetUseMonkAbilities())
	{
		CNWSItem *item = pThis->cs_original->cre_equipment->GetItemInSlot(16);//main hand
		if(item != NULL)
		{
			if((item->it_baseitemtype == 40 && item->obj.obj_vartable.GetInt(CExoString("ubab")) > -1) || item->obj.obj_vartable.GetInt(CExoString("ubab")) > 0)
			{
				item = pThis->cs_original->cre_equipment->GetItemInSlot(32);//off hand
				if(item != NULL)
				{
					if((item->it_baseitemtype == 40 && item->obj.obj_vartable.GetInt(CExoString("ubab")) > -1) || item->obj.obj_vartable.GetInt(CExoString("ubab")) > 0)
					{
						return 1;
					}
					CNWBaseItem *bt = NWN_Rules->ru_baseitems->GetBaseItem(item->it_baseitemtype);
					return bt->WeaponType == 0 && bt->ArmorCheckPen == 0;
				}
				return 1;
			}
			return 0;
		}
	}
	return CNWSCreatureStats__GetUseMonkAttackTables(pThis, NULL, a2);
}

unsigned char __fastcall CNWSCreatureStats__GetUnarmedDamageDice_Hook(CNWSCreatureStats *pThis, void*)
{
	if(pThis->GetUnarmedDamageDie() == 20)
	{
		return 1;
	}
	return CNWSCreatureStats__GetUnarmedDamageDice(pThis,NULL);
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
		if(pThis->cre_mode_combat == 5)//attempt to cancel flurry of blows
		{
			if(pThis->cre_stats->GetUseMonkAttackTables(1))
			{
				return;
			}
		}
	}
	else if(arg2 == 0)
	{
		arg1 = 0;
		arg2 = 1;
	}
	else if(arg1 == 5 && arg2 == 1)//flurry
	{
		if(pThis->cre_stats->GetUseMonkAttackTables(1))
		{
			pThis->cre_mode_combat = 5;
			pThis->SetActivity(0x4000,1);
			return;
		}
	}
	CNWSCreature__SetCombatMode(pThis, NULL, arg1, arg2);
}

void __fastcall CNWSCreature__BroadcastAttackOfOpportunity_Hook(CNWSCreature *pThis, void*, unsigned long targetID, int arg1)
{
	pThis->obj.obj_vartable.SetObject(CExoString("AOO_TARGET"),targetID);
	if(NWN_VirtualMachine->Runscript(&CExoString("70_s2_aoo"),pThis->obj.obj_generic.obj_id,1))
	{
		if(pThis->obj.obj_vartable.GetInt(CExoString("AOO_BYPASS")) > 0)
		{
			pThis->obj.obj_vartable.DestroyInt(CExoString("AOO_BYPASS"));
			return;
		}
	}
	CNWSCreature__BroadcastAttackOfOpportunity(pThis,NULL,targetID,arg1);
}

void __fastcall CNWSCombatRound__AddAttackOfOpportunity_Hook(CNWSCombatRound *pThis, void*, unsigned long lTarget)
{//bad place to do this, runs too late, attacking is already started, its only possible to block aoo but not attacking and current action = attack
	if(pThis->Creature != NULL && lTarget != OBJECT_INVALID)
	{
		pThis->Creature->obj.obj_vartable.SetObject(CExoString("AOO_TARGET"),lTarget);
		if(NWN_VirtualMachine->Runscript(&CExoString("70_s2_aoo"),pThis->Creature->obj.obj_generic.obj_id,1))
		{
			if(pThis->Creature->obj.obj_vartable.GetInt(CExoString("AOO_BYPASS")) > 0)
			{
				pThis->Creature->obj.obj_vartable.DestroyInt(CExoString("AOO_BYPASS"));
				return;
			}
		}
	}
	CNWSCombatRound__AddAttackOfOpportunity(pThis,NULL,lTarget);
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
	if(Patch.CurseIgnoreAbilityDecreaseImmunity)
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
	/*if(NWN_AppManager->app_server->srv_internal->ServerInfo->game_diff > 2)//DnD rules or Very high difficulty
	{
		if(eff->eff_creator != NULL)
		{
			CGenericObject *creator = NWN_AppManager->app_server->GetGameObject(eff->eff_creator);
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

int __fastcall CNWSEffectListHandler__OnApplyPolymorph_Hook(CNWSEffectListHandler *pThis, void*, CNWSObject *obj, CGameEffect *eff, int i)
{
	int prev = Patch.helper;
	Patch.helper = 40;
	int retVal = CNWSEffectListHandler__OnApplyPolymorph(pThis,NULL,obj,eff,i);
	Patch.helper = prev;
	return retVal;
}
int __fastcall CNWSEffectListHandler__OnRemovePolymorph_Hook(CNWSEffectListHandler *pThis, void*, CNWSObject *obj, CGameEffect *eff)
{
	int prev = Patch.helper;
	Patch.helper = 40;
	int retVal = CNWSEffectListHandler__OnRemovePolymorph(pThis,NULL,obj,eff);
	Patch.helper = prev;
	return retVal;
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
		int props = NWN_Rules->ru_baseitems->GetBaseItem(item->it_baseitemtype)->PropColumn;
		//bool potion = item->it_baseitemtype == 49 || item->it_baseitemtype == 104;
		//bool wand = item->it_baseitemtype == 44 || item->it_baseitemtype == 46;
		//bool healkit = item->it_baseitemtype == 39;
		//bool trap = item->it_baseitemtype == 64;
		//bool thieftool = item->it_baseitemtype == 62;
		//bool container = NWN_Rules->ru_baseitems->GetBaseItem(item->it_baseitemtype)->Container;
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
				NWN_Rules->ru_2das->tda_polymorph->GetINTEntry_strcol(poly, CExoString("UseItems"), &poly);
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
		CNWSItem *item = NWN_AppManager->app_server->srv_internal->GetItemByGameObjectID(l1);
		if(item != NULL && NWN_Rules->ru_baseitems->GetBaseItem(item->it_baseitemtype)->equipableSlots == 0 && pThis->CanUseItem(item,c1))
		{
			pThis->cre_pm_IsPolymorphed = 0;
			int retVal = CNWSCreature__UseItem(pThis,NULL,l1,c1,c2,l2,v,l3);
			pThis->cre_pm_IsPolymorphed = 1;
			return retVal;
		}
	}
	return CNWSCreature__UseItem(pThis,NULL,l1,c1,c2,l2,v,l3);
}

unsigned long __fastcall CNWSCreature__GetAssociateId_Hook(CNWSCreature *pThis, void*, unsigned short type, int th)
{
	if(Patch.helper == 222 && pThis->field_B48 != 0 && pThis->field_B48 != OBJECT_INVALID)
	{
		return pThis->field_B48;
	}
	return CNWSCreature__GetAssociateId(pThis,NULL,type,th);
}

void __fastcall CNWSCreature__SummonAnimalCompanion_Hook(CNWSCreature *pThis, void*)
{
	CNWSPlayer *player = NWN_AppManager->app_server->srv_internal->GetClientObjectByObjectId(pThis->obj.obj_generic.obj_id);
	if(player)
	{
		unsigned char expansion = NWN_Rules->GetFamiliarExpansionLevel(pThis->cre_stats->cs_acomp_type,1);
		if(expansion > 0 && !player->HasExpansionPack(expansion,1))
		{
			fprintf(Patch.m_fFile, "o Error when summoning animal companion: player doesn't have required expansion pack!\n");fflush(Patch.m_fFile);
			return;
		}
	}

	uint32_t assoc_id = pThis->GetAssociateId(2,1);
	CNWSCreature *assoc = NULL;
	if(assoc_id != OBJECT_INVALID && (assoc = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(assoc_id)) != NULL)
	{
		assoc->ReceiveAssociateCommand(-8);
	}

	CResRef resref;
	std::fill_n(resref.resref, 16, 0);

	if(pThis->obj.obj_vartable.GetString(CExoString("NWNX!PATCH!SETSUMMONEDRESREF")) != NULL)//called from community patch script
	{
		char *var = pThis->obj.obj_vartable.GetString(CExoString("NWNX!PATCH!SETSUMMONEDRESREF"))->text;
		pThis->obj.obj_vartable.DestroyString(CExoString("NWNX!PATCH!SETSUMMONEDRESREF"));
		sprintf_s(resref.resref,16,"%s",var);
	}
	else//vanilla call
	{
		int level = pThis->cre_stats->GetNumLevelsOfClass(CLASS_TYPE_DRUID)+pThis->cre_stats->GetNumLevelsOfClass(CLASS_TYPE_RANGER);
		if(level <= 0)
		{
			fprintf(Patch.m_fFile, "o Error when summoning animal companion: not a druid or ranger!\n");fflush(Patch.m_fFile);
			return;
		}
		else if(level > 40) level = 40;
		C2DA *fam2da = NWN_Rules->ru_2das->tda_hen_companion;
		CExoString *base = new CExoString();
		if(!fam2da->GetCExoStringEntry(pThis->cre_stats->cs_acomp_type,CExoString("BASERESREF"),base))
		{
			fprintf(Patch.m_fFile, "o Error when summoning animal companion: no value found in 2DA!\n");fflush(Patch.m_fFile);
			return;
		}
		if (level > 9)
		{
			sprintf_s(resref.resref,16,"%s%d",base->text,level);
		}
		else
		{
			sprintf_s(resref.resref,16,"%s0%d",base->text,level);
		}
	}

	for(size_t i = 0; i < 16; ++i)
	{
		resref.resref[i] = tolower(resref.resref[i]);
	}

	pThis->SummonAssociate(resref,NULL,NULL,2);
	unsigned int th = 1;
	unsigned long animalID = pThis->GetAssociateId(2,th);
	while(animalID != NULL && animalID != OBJECT_INVALID)//loop because old animal can still be valid in this point
	{
		CNWSCreature *animal = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(animalID);
		if(animal)
		{
			animal->cre_DisplayName = pThis->cre_stats->cs_acomp_name;
			pThis->cre_summoned_acomp = 1;
		}
		animalID = pThis->GetAssociateId(2,++th);
	}
}

void __fastcall CNWSCreature__SummonFamiliar_Hook(CNWSCreature *pThis, void*)
{
	CNWSPlayer *player = NWN_AppManager->app_server->srv_internal->GetClientObjectByObjectId(pThis->obj.obj_generic.obj_id);
	if(player)
	{
		unsigned char expansion = NWN_Rules->GetFamiliarExpansionLevel(pThis->cre_stats->cs_famil_type,0);
		if(expansion > 0 && !player->HasExpansionPack(expansion,1))
		{
			fprintf(Patch.m_fFile, "o Error when summoning familiar: player doesn't have required expansion pack!\n");fflush(Patch.m_fFile);
			return;
		}
	}

	uint32_t assoc_id = pThis->GetAssociateId(3,1);
	CNWSCreature *assoc = NULL;
	if(assoc_id != OBJECT_INVALID && (assoc = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(assoc_id)) != NULL)
	{
		assoc->ReceiveAssociateCommand(-8);
	}

	CResRef resref;
	std::fill_n(resref.resref, 16, 0);

	if(pThis->obj.obj_vartable.GetString(CExoString("NWNX!PATCH!SETSUMMONEDRESREF")) != NULL)//called from community patch script
	{
		char *var = pThis->obj.obj_vartable.GetString(CExoString("NWNX!PATCH!SETSUMMONEDRESREF"))->text;
		pThis->obj.obj_vartable.DestroyString(CExoString("NWNX!PATCH!SETSUMMONEDRESREF"));
		sprintf_s(resref.resref,16,"%s",var);
	}
	else//vanilla call
	{
		int level = pThis->cre_stats->GetNumLevelsOfClass(CLASS_TYPE_SORCERER)+pThis->cre_stats->GetNumLevelsOfClass(CLASS_TYPE_WIZARD);
		if(level <= 0)
		{
			fprintf(Patch.m_fFile, "o Error when summoning familiar: not a sorcerer or wizard!\n");fflush(Patch.m_fFile);
			return;
		}
		else if(level > 40) level = 40;
		C2DA *fam2da = NWN_Rules->ru_2das->tda_hen_familiar;
		int familiar_type = pThis->cre_stats->cs_famil_type;
		CExoString *base = new CExoString();
		if(!fam2da->GetCExoStringEntry(pThis->cre_stats->cs_famil_type,CExoString("BASERESREF"),base))
		{
			fprintf(Patch.m_fFile, "o Error when summoning familiar: no value found in 2DA!\n");fflush(Patch.m_fFile);
			return;
		}
		if (level > 9)
		{
			sprintf_s(resref.resref,16,"%s%d",base->text,level);
		}
		else
		{
			sprintf_s(resref.resref,16,"%s0%d",base->text,level);
		}
	}

	for(size_t i = 0; i < 16; ++i)
	{
		resref.resref[i] = tolower(resref.resref[i]);
	}

	pThis->SummonAssociate(resref,NULL,NULL,3);
	unsigned long familiarID = pThis->GetAssociateId(3,1);
	if(familiarID != NULL && familiarID != OBJECT_INVALID)
	{
		CNWSCreature *familiar = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(familiarID);
		if(familiar)
		{
			familiar->cre_DisplayName = pThis->cre_stats->cs_famil_name;
			pThis->cre_summoned_famil = 1;
		}
	}
}

void __fastcall CNWSCreature__ResolveAmmunition_Hook(CNWSCreature *pThis, void*, unsigned long l)
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
	CNWSCreature__ResolveAmmunition(pThis, NULL,l);
}

void __fastcall CNWSCreature__SetActivity_Hook(CNWSCreature *pThis, void*, int nActivity, int bOn)
{
	//fix for Defensive Stance mode not properly canceled
	if(nActivity == 0x100000 && !bOn && pThis->cre_is_pc)
	{
		pThis->cre_mode_combat = 0;
	}
	CNWSCreature__SetActivity(pThis, NULL, nActivity, bOn);
}

int CreateHook(DWORD pCode, PVOID pCallbackFunc, PVOID *pNextHook, const char * czName, const char * czFunc)
{
	CIniFile iniFile ("nwnplayer.ini");

	if(pCode && !iniFile.ReadBool("Community Patch", czName, false))
	{
		if(HookCode((PVOID)pCode, pCallbackFunc, pNextHook))
		{
			fprintf(Patch.m_fFile, "o %s patched succesfully.\n", czFunc);
			return 1;
		}
		else
		{
			fprintf(Patch.m_fFile, "o %s patch failed.\n", czFunc);
		}
	}
	else
	{
		fprintf(Patch.m_fFile, "o %s patch disabled.\n", czFunc);
	}
	return 0;
}

void Hook()
{
	//system
	CreateHook(0x5426A0,CNWSMessage__HandlePlayerToServerMessage_Hook, (PVOID*)&CNWSMessage__HandlePlayerToServerMessage, "DisableConnect","Sending hak-list to client");
	CreateHook(0x4D5230,CNWSModule__LoadModuleFinish_Hook, (PVOID*)&CNWSModule__LoadModuleFinish, "DisableLoadModuleFinishHook","LoadModuleFinish function");

	//weapons
	CreateHook(0x481210,CNWSCreatureStats__GetWeaponFinesse_Hook, (PVOID*)&CNWSCreatureStats__GetWeaponFinesse, "DisableWeaponHooks","GetWeaponFinesse function");
	CreateHook(0x4812E0,CNWSCreatureStats__GetWeaponFocus_Hook, (PVOID*)&CNWSCreatureStats__GetWeaponFocus, "DisableWeaponHooks","GetWeaponFocus function");
	CreateHook(0x481D70,CNWSCreatureStats__GetWeaponImprovedCritical_Hook, (PVOID*)&CNWSCreatureStats__GetWeaponImprovedCritical, "DisableWeaponHooks","GetWeaponImprovedCritical function");
	CreateHook(0x4817E0,CNWSCreatureStats__GetWeaponSpecialization_Hook, (PVOID*)&CNWSCreatureStats__GetWeaponSpecialization, "DisableWeaponHooks","GetWeaponsSpec");
	CreateHook(0x481510,CNWSCreatureStats__GetEpicWeaponFocus_Hook, (PVOID*)&CNWSCreatureStats__GetEpicWeaponFocus, "DisableWeaponHooks","GetEpicWeaponFocus function");
	CreateHook(0x481AA0,CNWSCreatureStats__GetEpicWeaponSpecialization_Hook, (PVOID*)&CNWSCreatureStats__GetEpicWeaponSpecialization,"DisableWeaponHooks","GetEpicWeaponSpecialization function");
	CreateHook(0x481FB0,CNWSCreatureStats__GetEpicWeaponOverwhelmingCritical_Hook, (PVOID*)&CNWSCreatureStats__GetEpicWeaponOverwhelmingCritical, "DisableWeaponHooks","GetEpicWeaponOverwhelmingCritical function");
	CreateHook(0x482280,CNWSCreatureStats__GetEpicWeaponDevastatingCritical_Hook, (PVOID*)&CNWSCreatureStats__GetEpicWeaponDevastatingCritical, "DisableWeaponHooks","GetEpicWeaponDevastatingCritical function");
	CreateHook(0x48CB10,CNWSCreatureStats__GetIsWeaponOfChoice_Hook, (PVOID*)&CNWSCreatureStats__GetIsWeaponOfChoice, "DisableWeaponHooks","GetIsWeaponOfChoice function");
	CreateHook(0x470730,CNWSCreatureStats__GetUseMonkAttackTables_Hook, (PVOID*)&CNWSCreatureStats__GetUseMonkAttackTables, "DisableWeaponHooks","GetUseMonkAttackTables function");
	CreateHook(0x4707B0,CNWSCreatureStats__GetUnarmedDamageDice_Hook, (PVOID*)&CNWSCreatureStats__GetUnarmedDamageDice, "DisableWeaponHooks", "UnarmedDamageDice calculation");

	//other
	CreateHook(0x48E050,CNWSCreatureStats__GetTotalACSkillMod_Hook, (PVOID*)&CNWSCreatureStats__GetTotalACSkillMod, "DisableGetTotalACSkillModHook","Tumble AC");
	CreateHook(0x49E370,CNWSCreature__GetUseMonkAbilities_Hook, (PVOID*)&CNWSCreature__GetUseMonkAbilities, "DisableGetUseMonkAbilitiesHook","Monk abilities in polymorph");

	CreateHook(0x4778B0,CNWSCreatureStats__GetCriticalHitRoll_Hook, (PVOID*)&CNWSCreatureStats__GetCriticalHitRoll, "DisableGetCriticalHitRollHook","Ki critical offhand bug");
	CreateHook(0x532C90,CNWSCombatRound__GetCurrentAttackWeapon_Hook, (PVOID*)&CNWSCombatRound__GetCurrentAttackWeapon, "DisableGetCriticalHitRollHook","GetCurrentAttackWeapon function");
	CreateHook(0x4A27C0,CNWSCreature__BroadcastAttackOfOpportunity_Hook,(PVOID*)&CNWSCreature__BroadcastAttackOfOpportunity, "DisableAttackOfOpportunity","Attack of opportunity");

	CreateHook(0x547580,CNWSCreature__ResolveAttack_Hook, (PVOID*)&CNWSCreature__ResolveAttack, "DisableResolveAttackHook","Circle kick");
	CreateHook(0x491F10,CNWSCreature__AddEquipItemActions_Hook, (PVOID*)&CNWSCreature__AddEquipItemActions, "DisableAddEquipItemActionsHook","Double equip exploit");
	CreateHook(0x4CC070,CNWSCreature__SummonAnimalCompanion_Hook, (PVOID*)&CNWSCreature__SummonAnimalCompanion, "DisableSummonAnimalCompanionHook","Animal companion summoning");
	CreateHook(0x4CC390,CNWSCreature__SummonFamiliar_Hook, (PVOID*)&CNWSCreature__SummonFamiliar, "DisableSummonFamiliarHook","Familiar summoning");

	CreateHook(0x4CDD80,CNWSCreature__GetAssociateId_Hook, (PVOID*)&CNWSCreature__GetAssociateId, "DisablePossessing","Possessing function #1");
	CreateHook(0x4CCAC0,CNWSCreature__PossessFamiliar_Hook, (PVOID*)&CNWSCreature__PossessFamiliar, "DisablePossessing","Possessing function #2");
	CreateHook(0x4CCD60,CNWSCreature__UnpossessFamiliar_Hook, (PVOID*)&CNWSCreature__UnpossessFamiliar, "DisablePossessing","Possessing function #3");
	CreateHook(0x4CE920,CNWSCreature__GetIsPossessedFamiliar_Hook, (PVOID*)&CNWSCreature__GetIsPossessedFamiliar, "DisablePossessing","Possessing function #4");
	CreateHook(0x4ECA70,CNWSEffectListHandler__OnApplyDeath_Hook, (PVOID*)&CNWSEffectListHandler__OnApplyDeath, "DisablePossessing","Possessing function #6");

	CreateHook(0x4CE950,CNWSCreature__CanUseItem_Hook, (PVOID*)&CNWSCreature__CanUseItem, "DisableUseItemHook","CanUseItem function");
	CreateHook(0x4A4CB0,CNWSCreature__UseItem_Hook, (PVOID*)&CNWSCreature__UseItem, "DisableUseItemHook","Use items in polymorph");
	
	CreateHook(0x48B770,CNWSCreatureStats__GetEffectImmunity_Hook, (PVOID*)&CNWSCreatureStats__GetEffectImmunity, "DisableEffectImmunityHook","GetEffectImmunity function");
	CreateHook(0x4EDA30,CNWSEffectListHandler__OnApplyAbilityDecrease_Hook, (PVOID*)&CNWSEffectListHandler__OnApplyAbilityDecrease, "DisableEffectImmunityHook","Itemproperty ability decrease");
	CreateHook(0x4F57D0,CNWSEffectListHandler__OnApplyCurse_Hook, (PVOID*)&CNWSEffectListHandler__OnApplyCurse, "DisableEffectImmunityHook","Curse ability decrease");

	CreateHook(0x54FB70,CNWSCreature__ResolveDamageShields_Hook, (PVOID*)&CNWSCreature__ResolveDamageShields, "DisableResolveDamageShieldsHook","Effect damage shield versus alignment");
	CreateHook(0x4A6D00,CNWSCreature__GetRelativeWeaponSize_Hook, (PVOID*)&CNWSCreature__GetRelativeWeaponSize, "DisableGetRelativeWeaponSizeHook","Deflect arrow weapon size bug");
	CreateHook(0x59F2E0,CNWSItemPropertyHandler__ApplyHolyAvenger_Hook, (PVOID*)&CNWSItemPropertyHandler__ApplyHolyAvenger, "DisableHolyAvengerHook","ApplyHolyAvenger function");
	CreateHook(0x59FC80,CNWSItemPropertyHandler__RemoveHolyAvenger_Hook, (PVOID*)&CNWSItemPropertyHandler__RemoveHolyAvenger, "DisableHolyAvengerHook","Holy avenger weapon enhancement bug");
	
	CreateHook(0x4A5080,CNWSCreature__ToggleMode_Hook, (PVOID*)&CNWSCreature__ToggleMode, "DisableToggleModeHook","ToggleMode function");
	CreateHook(0x4BB4D0,CNWSCreature__SetCombatMode_Hook, (PVOID*)&CNWSCreature__SetCombatMode, "DisableToggleModeHook","Flurry of blows modification");

	CreateHook(0x4F0300,CNWSEffectListHandler__OnApplyDisarm_Hook, (PVOID*)&CNWSEffectListHandler__OnApplyDisarm, "DisableDisarmHook","Disarm feat softcoding");
	CreateHook(0x489890,CNWSCreatureStats__GetSpellResistance_Hook,(PVOID*)&CNWSCreatureStats__GetSpellResistance, "DisableSRHook" , "Spell Resistance override");

	CreateHook(0x577DF0,CNWVirtualMachineCommands__ExecuteCommandApplyEffectOnObject_Hook,(PVOID*)&CNWVirtualMachineCommands__ExecuteCommandApplyEffectOnObject, "DisableApplyEffectOnObject" , "ApplyEffectToObject extension");
	CreateHook(0x45B990,CServerExoAppInternal__RemovePCFromWorld_Hook,(PVOID*)&CServerExoAppInternal__RemovePCFromWorld, "DisablePlayerLeave" , "OnClientLeave extension");
	CreateHook(0x454610,CServerExoAppInternal__ValidateCreateServerCharacter_Hook,(PVOID*)&CServerExoAppInternal__ValidateCreateServerCharacter, "DisableValidateServerCharacter", "Disallow New Characters server option");

	CreateHook(0x4E8C00,CGameEffect__SetCreator_Hook,(PVOID*)&CGameEffect__SetCreator, "DisableEffectCasterLevel" , "Effect caster level bug");
	CreateHook(0x48B920,CNWSCreatureStats__AdjustSpellUsesPerDay_Hook,(PVOID*)&CNWSCreatureStats__AdjustSpellUsesPerDay, "DisableAdjustSpellUses", "Spontaneous casters spell uses correction.");
	CreateHook(0x48E850,CNWSCreatureStats__ComputeFeatBonuses_Hook, (PVOID*)&CNWSCreatureStats__ComputeFeatBonuses, "DisableComputeFeatBonuses","Fixed losing spellslots/spelluses upon login from Great Ability feats.");
	CreateHook(0x499500,CNWSCreature__ReadItemsFromGff_Hook, (PVOID*)&CNWSCreature__ReadItemsFromGff, "DisableReadItemsFromGff","Fixed losing spelluses upon login from multiple items with charisma bonus.");
	CreateHook(0x496CE0,CNWSCreature__EventHandler_Hook,(PVOID*)&CNWSCreature__EventHandler, "DisableOnHitCastSpellHook" , "OnHitSpellCast bug");
	CreateHook(0x465B30,CNWSStore__SellItem_Hook,(PVOID*) &CNWSStore__SellItem, "DisableSellItem", "Buying with full inventory bug");
	CreateHook(0x484F50,CNWSCreatureStats__LevelDown_Hook,(PVOID*) &CNWSCreatureStats__LevelDown, "DisableLevelDownHook", "Fixed combat info update after level down");
	CreateHook(0x4847F0,CNWSCreatureStats__LevelUp_Hook,(PVOID*) &CNWSCreatureStats__LevelUp, "DisableLevelUpHook", "Support for spontaneous non-learner custom spellcaster class.");

	CreateHook(0x548100,CNWSCreature__ResolveAmmunition_Hook, (PVOID*)&CNWSCreature__ResolveAmmunition, "DisableResolveAmmunitionHook","Boomerang item property");
	CreateHook(0x490690,CNWSCreature__SetActivity_Hook, (PVOID*)&CNWSCreature__SetActivity, "DisableSetActivityHook","Defensive stance not canceling properly");
	CreateHook(0x4FA850,CNWSEffectListHandler__OnApplyDefensiveStance_Hook,(PVOID*)&CNWSEffectListHandler__OnApplyDefensiveStance, "DisableDefensiveStance", "Defensive Stance feat softcoding");
	CreateHook(0x474710,CNWSCreatureStats__ResolveSpecialAttackDamageBonus_Hook, (PVOID*)&CNWSCreatureStats__ResolveSpecialAttackDamageBonus, "DisableResolveSpecialAttackDamageBonusHook","Crash exploit no#1");
	CreateHook(0x4A8800,CNWSCreature__StartBarter_Hook, (PVOID*)&CNWSCreature__StartBarter, "DisableStartBarterHook","Crash exploit no#2");
	CreateHook(0x5017A0,CNWSItem__GetMinEquipLevel_Hook, (PVOID*)&CNWSItem__GetMinEquipLevel, "DisableGetMinEquipLevelHook", "Item level restriction");//run only at ILR=1 when acquire/move curson onto item/examine
	CreateHook(0x4DFA60,CNWSObject__ClearAllPartyInvalidActions_Hook, (PVOID*)&CNWSObject__ClearAllPartyInvalidActions, "DisableClearAllPartyInvalidActionsHook", "Party actions canceling");
	CreateHook(0x5A96F0,CNWSTrigger__GetCanFireTrapOnObject_Hook, (PVOID*)&CNWSTrigger__GetCanFireTrapOnObject, "DisableFireTrapHook", "Flying creatures immunity to traps feature");
	CreateHook(0x489E50,CNWSCreatureStats__GetFavoredEnemyBonus_Hook,(PVOID*)&CNWSCreatureStats__GetFavoredEnemyBonus, "DisableFavoredEnemyHook", "Favored Enemy calculation");
	CreateHook(0x493120,CNWSCreature__AddPickPocketAction_Hook,(PVOID*)&CNWSCreature__AddPickPocketAction, "DisableAddPickPocketAction", "Pickpocket skill softcoding");
	CreateHook(0x4B1F70,CNWSCreature__LearnScroll_Hook,(PVOID*)&CNWSCreature__LearnScroll, "DisableLearnScroll", "Learn scroll sofcoding");

	//spellcasting
	CreateHook(0x4828A0,CNWSCreatureStats__GetSpellMinAbilityMet_Hook,(PVOID*)&CNWSCreatureStats__GetSpellMinAbilityMet, "DisableCustomSpellCasters", "Enabling custom spellcasters #1");
	CreateHook(0x47D1C0,CNWSCreatureStats__UpdateNumberMemorizedSpellSlots_Hook,(PVOID*)&CNWSCreatureStats__UpdateNumberMemorizedSpellSlots, "DisableCustomSpellCasters", "Enabling custom spellcasters #2");
	CreateHook(0x46D550,CNWSCreatureStats__GetSpellGainWithBonus_Hook,(PVOID*)&CNWSCreatureStats__GetSpellGainWithBonus, "DisableCustomSpellCasters", "Enabling custom spellcasters #3b");
	CreateHook(0x48D6F0,CNWSCreatureStats__GetSpellGainWithBonusAfterLevelUp_Hook,(PVOID*)&CNWSCreatureStats__GetSpellGainWithBonusAfterLevelUp, "DisableCustomSpellCasters", "Enabling custom spellcasters #3c");
	CreateHook(0x502AC0,CNWSpell__GetSpellLevel_Hook,(PVOID*)&CNWSpell__GetSpellLevel, "DisableCustomSpellCasters", "Enabling custom spellcasters #4");
	CreateHook(0x4B8270,CNWRules__IsArcaneClass_Hook,(PVOID*)&CNWRules__IsArcaneClass, "DisableCustomSpellCasters", "Enabling custom spellcasters #5");
	CreateHook(0x489690,CNWSCreatureStats__ComputeNumberKnownSpellsLeft_Hook,(PVOID*)&CNWSCreatureStats__ComputeNumberKnownSpellsLeft, "DisableCustomSpellCasters", "Enabling custom spellcasters #6");
	CreateHook(0x46CBD0,CNWSCreatureStats_ClassInfo__ConfirmDomainSpell_Hook,(PVOID*)&CNWSCreatureStats_ClassInfo__ConfirmDomainSpell, "DisableCustomSpellCasters", "Enabling custom spellcasters #7");
	CreateHook(0x482550,CNWSCreatureStats__GetSpellUsesLeft_Hook,(PVOID*)&CNWSCreatureStats__GetSpellUsesLeft, "DisableCustomSpellCasters", "Enabling custom spellcasters #8");

	//spell slots
	fprintf_s(Patch.m_fFile, "o Hooking neccessary functions to fix spell slots in polymorph:\n");
	int ok = 0;
	ok+= CreateHook(0x4F76D0,CNWSEffectListHandler__OnApplyPolymorph_Hook, (PVOID*)&CNWSEffectListHandler__OnApplyPolymorph, "DisableSpellSlotsInPolymorphHook","OnApplyPolymorph function");
	ok+= CreateHook(0x4F78E0,CNWSEffectListHandler__OnRemovePolymorph_Hook, (PVOID*)&CNWSEffectListHandler__OnRemovePolymorph, "DisableSpellSlotsInPolymorphHook","OnRemovePolymorph function");
	ok+= CreateHook(0x59D590,CNWSItemPropertyHandler__ApplyBonusSpellOfLevel_Hook, (PVOID*)&CNWSItemPropertyHandler__ApplyBonusSpellOfLevel, "DisableSpellSlotsInPolymorphHook","ApplyBonusSpellOfLevel function");
	ok+= CreateHook(0x59D610,CNWSItemPropertyHandler__RemoveBonusSpellOfLevel_Hook, (PVOID*)&CNWSItemPropertyHandler__RemoveBonusSpellOfLevel, "DisableSpellSlotsInPolymorphHook","RemoveBonusSpellOfLevel function");
	ok+= CreateHook(0x498AB0,CNWSCreature__UpdateAttributesOnEffect_Hook, (PVOID*)&CNWSCreature__UpdateAttributesOnEffect, "DisableSpellSlotsInPolymorphHook","UpdateAttributtesOnEffect function");
	ok+= CreateHook(0x46C630,CNWSCreatureStats_ClassInfo__SetNumberMemorizedSpellSlots_Hook, (PVOID*)&CNWSCreatureStats_ClassInfo__SetNumberMemorizedSpellSlots, "DisableSpellSlotsInPolymorphHook","SetNumberMemorizedSpellSlots function");

	if(ok < 6)
	{
		fprintf_s(Patch.m_fFile, "o Hooking neccessary functions to fix spell slots in polymorph: ERROR, %i Hooks failed, this feature might not work properly!\n");
	}
	else
	{
		fprintf_s(Patch.m_fFile, "o Hooking neccessary functions to fix spell slots in polymorph: SUCCESS.\n");
	}

	fprintf(Patch.m_fFile,"\n");
	fflush(Patch.m_fFile);

	//scrap
	//CreateHook(0x5325D0,CNWSCombatRound__AddAttackOfOpportunity_Hook,(PVOID*)&CNWSCombatRound__AddAttackOfOpportunity,"DisableAttackOfOpportunity","Attack of opportunity");
	//CreateHook(0x4EFEE0,CNWSEffectListHandler__OnApplyKnockdown_Hook, (PVOID*)&CNWSEffectListHandler__OnApplyKnockdown, "DisableKnockdownHook","Knockdown feat softcoding");
	//CreateHook(0x498090,CNWSCreature__MaxAttackRange_Hook, (PVOID*)&CNWSCreature__MaxAttackRange, "Test","Unarmed attack range fix attempt.");//had unwanted issues with creature weapons
	//CreateHook(0x4A6C20,CNWSCreature__RemoveBadEffects_Hook, (PVOID*)&CNWSCreature__RemoveBadEffects, "DisableBadEffectsHook","Fix for bad effects removal at rest");//i dont see a problem in there, requires confirmation
}