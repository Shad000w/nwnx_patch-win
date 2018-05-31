#include "stdio.h"
#include "stdlib.h"
#include "nwn_internals.h"
#include "types.h"
#include "../nwn_internals/CNWSStats_FeatUses.h"
#include "madCHook.h"
#include <iostream>
#pragma comment(lib, "madCHook.lib")

const int   VERSION_MAJOR = 1;
const int   VERSION_MINOR = 35;
const char *VERSION_PATCH = "a";
DWORD *heapAddress = NULL;
FILE *logFile;
char logFileName[] = "logs.0/nwnx_patch.txt";
volatile int8_t Hook_int8;
volatile uint8_t Hook_uint8;
volatile uint8_t test1;
volatile uint8_t test2;
volatile uint8_t test3;
volatile uint16_t test16;
volatile uint32_t test32;
volatile uint32_t test33;
volatile uint32_t Hook_ret;

volatile uint32_t orig_eax;
volatile uint32_t orig_ebx;
volatile uint32_t orig_ecx;
volatile uint32_t orig_edx;

CNWSCreature *self;
CNWSCreature *target;
CNWSCreatureStats *stats;
int DebugLvl = 0;
int helper,helper_backup;
CGameEffect *helper_effect,*Hook_effect;
bool NoTumbleAC = false;
bool NoCriticalImmunity = false;
bool NoMonkAbilities = false;
bool TrapImmunity = false;
bool ParalysisIgnoreMindImmunity = false;
bool PMCasterLevel = false;
bool PrestigeClassAffectSpontaneousCasters = false;
bool CurseIgnoreAbilityDecreaseImmunity = false;
bool DnDUncannyDodge = false;
//bool DisableHighlightObjects = false;
int NoServerCharacter = 0;
int DisallowAnimalCompanionPossessing = 0;
int DisableStickyCombatModes = 0;
unsigned char NumTilesExplored = 0;
int Hook_integer = 0;
CNWClass *hook_Class;
CNWSpell *hook_Spell;
CNWSModule *module;
CExoString *script;
CExoString script_dthattk = "70_s2_dthattk";
CExoString script_devast = "70_s2_devattk";
CExoString script_defarrow = "70_s2_defarrow";
CExoString script_healkit = "70_s3_healkit";
CExoString aoo_target = "AOO_TARGET";
CExoString aoo_bypass = "AOO_BYPASS";
CExoString script_aoo = "70_s2_aoo";
CExoString bypass_event = "BYPASS_EVENT";
CExoString script_equ = "70_mod_def_equ";
CExoString script_rest = "70_mod_def_rest";
CExoString script_act = "70_mod_def_act";
CExoString script_aqu = "70_mod_def_aqu";
CExoString script_unaqu = "70_mod_def_unaqu";
CExoString script_dying = "70_mod_def_dying";
CExoString script_death = "70_mod_def_death";
CExoString script_respawn = "70_mod_def_resp";
CExoString script_enter = "70_mod_def_enter";
CExoString script_lvup = "70_mod_def_lvup";
CExoString script_unequ = "70_mod_def_unequ";
CExoString script_chat = "70_mod_def_chat";
CExoString script_abort = "70_mod_def_abort";
CExoString script_leave = "70_mod_def_leave";
CExoString script_load = "70_mod_def_load";
CExoString script_user = "70_mod_def_user";
CExoString script_critical = "70_mod_crithit";
CExoString sneak_attack = "SneakAttackModifier";

bool pole[3][3];
C2DA *weaponfeats_2da,*racialtypes_2da,*spells_2da,*spells_level_2da,*classes_2da,*effects_2da;
C2DA *cls_spopt_2da[255],*cls_prog_2da[255];
unsigned int cls_cast_type[255];
unsigned int cls_cast_unlimited[255][60];

//Allocates size bytes and returns a pointer to its start location
void *(__cdecl *nwnx_malloc)(unsigned int size);
//Frees memory blocks allocated by nwnx_malloc/calloc/realloc
void (__cdecl *nwnx_free)(void *ptr);
//Allocates num*size bytes and sets all the bytes to zero
void *nwnx_calloc(unsigned int num, unsigned int size);
void Log(int nDebugLevel, const char *pcMsg, ... );

void InitializeWeaponFeats2DA()
{
	fprintf(logFile, "o Initializing weaponfeats.2da.\n");fflush(logFile);
	if(weaponfeats_2da)
	{
		weaponfeats_2da->Unload2DArray();
		fprintf(logFile, "o  weaponfeats.2da already initialized. Unloading content.\n");fflush(logFile);
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
		if(weaponfeats_2da->m_nNumColumns > 0 && weaponfeats_2da->m_nNumRows > 0)
		{
			fprintf(logFile, "o  weaponfeats.2da loaded.\n");fflush(logFile);
		}
		else
		{
			weaponfeats_2da = NULL;
			fprintf(logFile, " o  ERROR loading weaponfeats.2da!\n");fflush(logFile);
		}	
	}
	fprintf(logFile, "o  done.\n");fflush(logFile);
}

void InitializeEffects2DA()
{
	fprintf(logFile, "o Initializing effects.2da.\n");fflush(logFile);
	if(effects_2da)
	{
		effects_2da->Unload2DArray();
		fprintf(logFile, "o  effects.2da already initialized. Unloading content.\n");fflush(logFile);
	}
	else
	{
		CResRef resref;
		std::fill_n(resref.resref, 16, 0);
		sprintf_s(resref.resref,16,"%s","effects");
		effects_2da = new C2DA();
		effects_2da->C2DA(resref,0);
	}
	if(effects_2da)
	{
		effects_2da->Load2DArray();
		if(effects_2da->m_nNumColumns > 0 && effects_2da->m_nNumRows > 0)
		{
			fprintf(logFile, "o  effects.2da loaded.\n");fflush(logFile);
		}
		else
		{
			effects_2da = NULL;
			fprintf(logFile, " o  ERROR loading effects.2da!\n");fflush(logFile);
		}	
	}
	fprintf(logFile, "o  done.\n");fflush(logFile);
}

void InitializeRacialTypes2DA()
{
	fprintf(logFile, "o Initializing racial_types.2da.\n");fflush(logFile);
	if(racialtypes_2da)
	{
		racialtypes_2da->Unload2DArray();
		fprintf(logFile, "o  racial_types.2da already initialized. Unloading content.\n");fflush(logFile);
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
		CExoString FavoredEnemy = "FavoredEnemyFeat";
		int val = 0;
		for(unsigned int row = 0; row < racialtypes_2da->m_nNumRows; row++)
		{	
			CNWRace *race = &(NWN_Rules->m_lstRaces[row]);
			if(race && row != RACIAL_TYPE_INVALID)
			{
				if(racialtypes_2da->GetINTEntry_strcol(row,FavoredEnemy,&val) && val > -1)
				{
					race->FavoredEnemyFeat = val;			
				}
			}
		}
		//NWN_Rules->LoadRaceInfo();
		fprintf(logFile, "o  racial_types.2da loaded.\n");fflush(logFile);
	}
	fprintf(logFile, "o  done.\n");fflush(logFile);
}

void InitializeClasses2DA()
{
	fprintf(logFile, "o Initializing classes.2da.\n");fflush(logFile);
	if(classes_2da)
	{
		classes_2da->Unload2DArray();
		fprintf(logFile, "o  classes.2da already initialized. Unloading content.\n");fflush(logFile);
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
		//NWN_Rules->LoadClassInfo();//this caused random crashing in CNWSCreatureStats:GetSpellGainWithBonus
		fprintf(logFile, "o  classes.2da loaded.\n");fflush(logFile);
		CNWClass *cClass;
		CExoString CastType = "CastType";
		CExoString SpellsOpt = "SpellOptTable";
		CExoString SpellType = "SpellType";
		CExoString SpellsProg = "SpellProgTable";
		CExoString sVal;
		int val = 0;
		int numRows = classes_2da->m_nNumRows; if(numRows > 255) numRows = 255;
		for(unsigned char x=0;x < numRows; x++)
		{
			cClass = &(NWN_Rules->m_lstClasses[x]);
			//fprintf(logFile, "o  classes.2da loaded cls %i spellcaster %i arcane %i.\n",x,cClass->SpellCaster,g_pRules->IsArcaneClass(x));fflush(logFile);
			if(cClass->m_bIsSpellCasterClass && classes_2da->GetINTEntry_strcol(x,CastType,&val))
			{
				cls_cast_type[x] = val;
			}
			else
			{
				switch(x)//default CastType values if CastType is ****
				{
					case CLASS_TYPE_BARD: cls_cast_type[x] = 131; break;
					case CLASS_TYPE_CLERIC: cls_cast_type[x] = 8; break;
					case CLASS_TYPE_DRUID: cls_cast_type[x] = 0; break;
					case CLASS_TYPE_PALADIN: cls_cast_type[x] = 0; break;
					case CLASS_TYPE_RANGER: cls_cast_type[x] = 0; break;
					case CLASS_TYPE_SORCERER: cls_cast_type[x] = 131; break;
					case CLASS_TYPE_WIZARD: cls_cast_type[x] = 209; break;
				}
			}
			if(cClass->m_bIsSpellCasterClass && classes_2da->GetCExoStringEntry(x,SpellsOpt,&sVal) && strlen(sVal.text) <= 16)//learning nonspontaneous spellcaster
			{
				fprintf(logFile, " o Initializing %s.2da.\n",sVal.text);fflush(logFile);
				if(cls_spopt_2da[x])
				{
					cls_spopt_2da[x]->Unload2DArray();
					fprintf(logFile, " o  %s.2da already initialized. Unloading content.\n",sVal.text);fflush(logFile);
				}
				else
				{
					CResRef resref;
					std::fill_n(resref.resref, 16, 0);
					sprintf_s(resref.resref,16,"%s",sVal);
					cls_spopt_2da[x] = new C2DA();
					cls_spopt_2da[x]->C2DA(resref,0);
				}
				if(cls_spopt_2da[x])
				{
					cls_spopt_2da[x]->Load2DArray();
					if(cls_spopt_2da[x]->m_nNumColumns > 0 && cls_spopt_2da[x]->m_nNumRows > 0)
					{
						for(unsigned int row = 0; row < cls_spopt_2da[x]->m_nNumRows && row < 60; row++)
						{
							cls_cast_unlimited[x][row] = 0;
							for(unsigned int col = 4; col < 14; col++)
							{
								if(cls_spopt_2da[x]->GetINTEntry_intcol(row,col,&val) && val > 0)
								{
									val = 1<<(col-4);
									cls_cast_unlimited[x][row]|= val;
								}
							}
						}
						fprintf(logFile, " o  %s.2da loaded.\n",sVal.text);fflush(logFile);
					}
					else
					{
						cls_spopt_2da[x] = NULL;
						fprintf(logFile, " o  ERROR loading %s.2da!\n",sVal.text);fflush(logFile);
					}
				}
			}
			if(classes_2da->GetCExoStringEntry(x,SpellsProg,&sVal) && sVal != NULL && sVal.text != NULL && strlen(sVal.text) <= 16)//custom spell progression
			{
				fprintf(logFile, " o Initializing %s.2da.\n",sVal.text);fflush(logFile);
				if(cls_prog_2da[x])
				{
					cls_prog_2da[x]->Unload2DArray();
					fprintf(logFile, " o  %s.2da already initialized. Unloading content.\n",sVal.text);fflush(logFile);
				}
				else
				{
					CResRef resref;
					std::fill_n(resref.resref, 16, 0);
					sprintf_s(resref.resref,16,"%s",sVal);
					cls_prog_2da[x] = new C2DA();
					cls_prog_2da[x]->C2DA(resref,0);
				}
				if(cls_prog_2da[x])
				{
					cls_prog_2da[x]->Load2DArray();
					if(cls_prog_2da[x]->m_nNumColumns > 0 && cls_prog_2da[x]->m_nNumRows > 0)
					{
						fprintf(logFile, " o  %s.2da loaded.\n",sVal.text);fflush(logFile);
					}
					else
					{
						cls_prog_2da[x] = NULL;
						fprintf(logFile, " o  ERROR loading %s.2da!\n",sVal.text);fflush(logFile);
					}					
				}
			}
			//fprintf(logFile, "o  classes.2da loaded cls %i spellcaster %i casttype %i castopt %i.\n",x,cClass->SpellCaster,cClass->CastType,cClass->CastOption);fflush(logFile);
		}
	}
	fprintf(logFile, "o  done.\n");fflush(logFile);
}

void InitializeModuleSwitches(CNWSModule *module)
{
	NoTumbleAC = module->mod_vartable.GetInt(CExoString("72_DISABLE_TUMBLE_AC")) > 0;
	NoCriticalImmunity = module->mod_vartable.GetInt(CExoString("72_DISABLE_SNEAK_CRITICAL_IMMUNITY")) > 0;
	NoMonkAbilities = module->mod_vartable.GetInt(CExoString("72_DISABLE_MONK_IN_POLYMORPH")) > 0;
	TrapImmunity = module->mod_vartable.GetInt(CExoString("72_ENABLE_FLYING_TRAP_IMMUNITY")) > 0;
	ParalysisIgnoreMindImmunity = module->mod_vartable.GetInt(CExoString("72_DISABLE_PARALYZE_MIND_SPELL_IMMUNITY")) > 0;
	PMCasterLevel = module->mod_vartable.GetInt(CExoString("71_PALEMASTER_ADDS_CASTER_LEVEL")) > 0;
	CurseIgnoreAbilityDecreaseImmunity = module->mod_vartable.GetInt(CExoString("72_CURSE_IGNORE_ABILITY_DECREASE_IMMUNITY")) > 0;
	DnDUncannyDodge = module->mod_vartable.GetInt(CExoString("72_HARDCORE_UNCANNY_DODGE")) > 0;
	//PrestigeClassAffectSpontaneousCasters = module->mod_vartable.GetInt(CExoString("72_SpellLvlMod_AFFECT_SPONTANEOUS_CASTERS")) > 0;

	PrestigeClassAffectSpontaneousCasters = true;
}

void InitializeSpells2DA()
{
	fprintf(logFile, "o Initializing spells.2da.\n");fflush(logFile);
	if(spells_2da)
	{
		spells_2da->Unload2DArray();
		fprintf(logFile, "o  spells.2da already initialized. Unloading content.\n");fflush(logFile);
	}
	else
	{
		CResRef resref;
		std::fill_n(resref.resref, 16, 0);
		sprintf_s(resref.resref,16,"%s","spells");
		spells_2da = new C2DA();
		spells_2da->C2DA(resref,0);
	}
	if(spells_2da)
	{ 
		spells_2da->Load2DArray();
		//workaround for a fact that client reads values above 1 as 1 for column SpontaneouslyCast
		int nVal;
		CExoString SpontaneouslyCast = "SpontaneouslyCast";
		CExoString Hidden = "Hidden";
		for(unsigned int spell_id = 0; spell_id < spells_2da->m_nNumRows; spell_id++)
		{
			if(spells_2da->GetINTEntry_strcol(spell_id,SpontaneouslyCast,&nVal) && nVal > 1)
			{
				NWN_Rules->m_pSpellArray->GetSpell(spell_id)->m_bSpontaneouslyCast = (unsigned char)nVal;
			}
			if(spells_2da->GetINTEntry_strcol(spell_id,Hidden,&nVal) && nVal > 1)
			{
				NWN_Rules->m_pSpellArray->GetSpell(spell_id)->Hidden = (unsigned char)nVal;
			}
		}		
		//NWN_Rules->m_pSpellArray->Load();
		fprintf(logFile, "o  spells.2da loaded.\n");fflush(logFile);
		spells_2da->Unload2DArray();
	}
}

void InitializeSpells_Level2DA()
{
	fprintf(logFile, "o Initializing spells_level.2da.\n");fflush(logFile);
	if(spells_level_2da)
	{
		spells_level_2da->Unload2DArray();
		fprintf(logFile, "o  spells_level.2da already initialized. Unloading content.\n");fflush(logFile);
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
		if(spells_level_2da->m_nNumColumns > 0 && spells_level_2da->m_nNumRows > 0)
		{
			fprintf(logFile, "o  spells_level.2da loaded.\n");fflush(logFile);
		}
		else
		{
			spells_level_2da = NULL;
			fprintf(logFile, " o  ERROR loading spells_level.2da!\n");fflush(logFile);
		}		
	}
}

unsigned char GetSpellProgressionModifier(CNWSCreatureStats *pThis, unsigned char cls_pos)
{
	if(!classes_2da) return 0;
	unsigned char cls_id = pThis->cs_classes[cls_pos].cl_class;
	CNWClass *otherClass,*thirdClass;
	CExoString SpellType = "SpellType", cls_spell_type, third_spell_type;
	bool bArcane = false, bDivine = false;
	if(!classes_2da->GetCExoStringEntry(cls_id,SpellType,&cls_spell_type))
	{
		bArcane = (cls_cast_type[cls_id] & CAST_TYPE_ARCANE) == CAST_TYPE_ARCANE;
		bDivine = !bArcane;
		cls_spell_type = (cls_cast_type[cls_id] & CAST_TYPE_ARCANE) == CAST_TYPE_ARCANE ? "Arcane" : "Divine";
	}
	bool highest_class = true;
	unsigned char level = pThis->cs_classes[cls_pos].cl_level;
	unsigned char spellMod = 0;
	if(!(cls_cast_type[cls_id] & CAST_TYPE_SPONTANEOUS) || PrestigeClassAffectSpontaneousCasters)
	{
		unsigned char other_cls_id = 255, other_level = 255, third_id = 255, third_level = 255, third_pos = 255;
		for(unsigned char x=0;x < pThis->cs_classes_len;x++)
		{
			other_cls_id = pThis->cs_classes[x].cl_class;
			other_level = pThis->cs_classes[x].cl_level;
			if(x == cls_pos || other_cls_id == CLASS_TYPE_INVALID || other_level == 255) continue;
			otherClass = &(NWN_Rules->m_lstClasses[other_cls_id]);
			thirdClass = NULL;
			highest_class = true;
			if(pThis->cs_classes_len == 3)
			{
				third_pos = pThis->cs_classes_len-x-cls_pos;	
				third_id = pThis->cs_classes[third_pos].cl_class;
				if(third_id != CLASS_TYPE_INVALID)
				{
					third_level = pThis->cs_classes[third_pos].cl_level;
					thirdClass = &(NWN_Rules->m_lstClasses[third_id]);
					if(thirdClass->m_bIsSpellCasterClass)
					{
						if(!classes_2da->GetCExoStringEntry(third_id,SpellType,&third_spell_type))
						{
							third_spell_type = (cls_cast_type[third_id] & CAST_TYPE_ARCANE) == CAST_TYPE_ARCANE ? "Arcane" : "Divine";
						}
					}
				}				
			}
			if(cls_prog_2da[other_cls_id] && cls_spell_type != NULL)
			{			
				int nValue;
				cls_prog_2da[other_cls_id]->GetINTEntry_intcol(other_level-1,1,&nValue);
				if(nValue == 0)//class that will improve spell progression of only one class of same spell type
				{
					if(thirdClass && thirdClass->m_bIsSpellCasterClass && third_level >= level)
					{
						if(cls_spell_type == third_spell_type)
						{
							if(third_level > level || cls_pos < third_pos)
							{
								continue;
							}
						}
					}
				}
				else if(nValue == 2)//class that will improve spell progression of only one class of any spell type
				{
					if(thirdClass && thirdClass->m_bIsSpellCasterClass)
					{
						if(cls_prog_2da[other_cls_id]->GetINTEntry_strcol(other_level-1,third_spell_type,&nValue))
						{
							if(third_level > level || (third_level == level && cls_pos < third_pos))
							{
								highest_class = false;
							}										
						}
					}								
				}
				if(cls_prog_2da[other_cls_id]->GetINTEntry_strcol(other_level-1,cls_spell_type,&nValue) && highest_class)//class that will improve progression of custom type of spells
				{
					spellMod+= nValue;
				}
			}
			else
			{
				if(thirdClass && thirdClass->m_bIsSpellCasterClass && third_level >= level)
				{
					if(cls_spell_type == third_spell_type)
					{
						if(third_level > level || cls_pos < third_pos)
						{
							continue;
						}
					}
				}		
				if(otherClass->m_nArcSpellUsePerDayLevel && ((cls_cast_type[cls_id] & CAST_TYPE_ARCANE) == CAST_TYPE_ARCANE || cls_spell_type == "Arcane"))
				{
					spellMod+= (other_level+(otherClass->m_nArcSpellUsePerDayLevel != 1))/otherClass->m_nArcSpellUsePerDayLevel;
				}
				else if(otherClass->m_nDivSpellUsePerDayLevel && ((cls_cast_type[cls_id] & CAST_TYPE_ARCANE) != CAST_TYPE_ARCANE || cls_spell_type == "Divine"))
				{
					spellMod+= (pThis->cs_classes[x].cl_level+(otherClass->m_nDivSpellUsePerDayLevel != 1))/otherClass->m_nDivSpellUsePerDayLevel;
				}
			}
		}
	}
	return spellMod;
}

//system
void (__fastcall *CNWSScriptVarTable__SetString)(CNWSScriptVarTable *pThis, void*, CExoString &VarName, CExoString &Value);
int (__fastcall *CNWSMessage__HandlePlayerToServerMessage)(CNWSMessage *pMessage, void *, unsigned long nPlayerID, unsigned char *pData, unsigned long nLen);
unsigned long (__fastcall *CNWSModule__LoadModuleFinish)(CNWSModule *pThis, void*);
void (__fastcall *CServerExoAppInternal__RemovePCFromWorld)(CServerExoAppInternal *srv, void *, CNWSPlayer *player);
void (__fastcall *CNWRules__ReloadAll)(CNWRules *pThis, void *);
//scripting
int (__fastcall *CNWVirtualMachineCommands__ExecuteCommandGetAssociateType)(CVirtualMachineCommands *vm_cmds, void*, int arg1, int arg2);
int (__fastcall *CNWVirtualMachineCommands__ExecuteCommandGetAssociate)(CVirtualMachineCommands *vm_cmds, void*, int arg1, int arg2);
int (__fastcall *CNWVirtualMachineCommands__ExecuteCommandApplyEffectOnObject)(CVirtualMachineCommands *vm_cmds, void*, int cmd, int args);
int (__fastcall *CNWVirtualMachineCommands__ExecuteCommandGetRacialType)(CVirtualMachineCommands *vm_cmds, void*, int cmd, int args);
int (__fastcall *CNWVirtualMachineCommands__ExecuteCommandGetEffectSubType)(CVirtualMachineCommands *vm_cmds, void*, int cmd, int args);
int (__fastcall *CNWVirtualMachineCommands__ExecuteCommandVersusEffect)(CVirtualMachineCommands *vm_cmds, void*, int cmd, int args);
//effects
void (__fastcall *CGameEffect__SetCreator)(CGameEffect *pThis, void*, unsigned long creatorID);
int (__fastcall *CNWSEffectListHandler__OnEffectApplied)(CNWSEffectListHandler *pThis, void*, CNWSObject *obj, CGameEffect *eff, int arg1);
int (__fastcall *CNWSEffectListHandler__OnEffectRemoved)(CNWSEffectListHandler *pThis, void*, CNWSObject *obj, CGameEffect *eff);
int (__fastcall *CNWSEffectListHandler__OnApplyAbilityDecrease)(CNWSEffectListHandler *pThis, void*, CNWSObject *obj, CGameEffect *eff, int i);
int (__fastcall *CNWSEffectListHandler__OnApplyCurse)(CNWSEffectListHandler *pThis, void*, CNWSObject *obj, CGameEffect *eff, int i);
int (__fastcall *CNWSEffectListHandler__OnApplyPolymorph)(CNWSEffectListHandler *pThis, void*, CNWSObject *obj, CGameEffect *eff, int i);
int (__fastcall *CNWSEffectListHandler__OnRemovePolymorph)(CNWSEffectListHandler *pThis, void*, CNWSObject *obj, CGameEffect *eff);
int (__fastcall *CNWSEffectListHandler__OnApplyDefensiveStance) (CNWSEffectListHandler *pThis, void*, CNWSObject *obj, CGameEffect *eff, int n);
int (__fastcall *CNWSEffectListHandler__OnApplyDeath)(CNWSEffectListHandler *pThis, void*, CNWSObject *obj, CGameEffect *eff, int arg1);
int (__fastcall *CNWSCreature__GetTotalEffectBonus)(CNWSCreature *pThis, void*, char a2, CNWSObject *obj_a, int a4, int a5, unsigned __int8 a6, unsigned __int8 a7, unsigned __int8 a8, unsigned __int8 a9, int a10);
int (__fastcall *CNWSCreatureStats__GetEffectImmunity)(CNWSCreatureStats *pThis, void*, unsigned char immunity_type, CNWSCreature *cre);
//itemproperties
int (__fastcall *CNWSItemPropertyHandler__ApplyHolyAvenger)(CNWSItemPropertyHandler *pThis, void*, CNWSItem *item, CNWItemProperty *ip, CNWSCreature *cre, unsigned long l, int i);
int (__fastcall *CNWSItemPropertyHandler__RemoveHolyAvenger)(CNWSItemPropertyHandler *pThis, void*, CNWSItem *item, CNWItemProperty *ip, CNWSCreature *cre, unsigned long l);
int (__fastcall *CNWSItemPropertyHandler__ApplyBonusSpellOfLevel)(CNWSItemPropertyHandler *pThis, void*, CNWSItem *item, CNWItemProperty *ip, CNWSCreature *cre, unsigned long l, int i);
int (__fastcall *CNWSItemPropertyHandler__RemoveBonusSpellOfLevel)(CNWSItemPropertyHandler *pThis, void*, CNWSItem *item, CNWItemProperty *ip, CNWSCreature *cre, unsigned long l);
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
int (__fastcall *CNWSCreatureStats__GetCriticalHitRoll)(CNWSCreatureStats *pThis, void*, int n);
int (__fastcall *CNWSCreatureStats__GetCriticalHitMultiplier)(CNWSCreatureStats *pThis, void*, int n);
int (__fastcall *CNWSCreature__GetRelativeWeaponSize)(CNWSCreature *pThis, void*, CNWSItem *weapon);
//other
void (__fastcall *CNWSCreature__ResolveAttack)(CNWSCreature *pThis, void*, unsigned long target, int i, int i2);
int (__fastcall *CNWSCreature__CanUseItem)(CNWSCreature *pThis, void*, CNWSItem *item, int a1);
int (__fastcall *CNWSCreature__UseItem)(CNWSCreature *pThis, void*, unsigned long l1, unsigned char c1, unsigned char c2, unsigned long l2, Vector v, unsigned long l3);
void (__fastcall *CNWSCreature__SummonAnimalCompanion)(CNWSCreature *pThis, void*);
void (__fastcall *CNWSCreature__SummonFamiliar)(CNWSCreature *pThis, void*);
unsigned long (__fastcall *CNWSCreature__GetAssociateId)(CNWSCreature *pThis, void*, unsigned short type, int th);
int (__fastcall *CNWSCreature__AddEquipItemActions)(CNWSCreature *pThis, void*, CNWSItem *item, unsigned long l1, int i1, int i2, unsigned long l2);
void (__fastcall *CNWSCreature__ResolveDamageShields)(CNWSCreature *pThis, void*, CNWSCreature *attacker);
void (__fastcall *CNWSCreature__SetCombatMode)(CNWSCreature *pThis, void*, unsigned char arg1, int arg2);
int (__fastcall *CNWSCreature__ToggleMode)(CNWSCreature *pThis, void*, unsigned char arg1);
void (__fastcall *CNWSCreature__ResolveAmmunition)(CNWSCreature *pThis, void*, unsigned long num_attacks);
int (__fastcall *CNWSCreature__GetAmmunitionAvailable)(CNWSCreature *pThis, void*, int num_attacks);
void (__fastcall *CNWSCreatureStats_ClassInfo__SetNumberMemorizedSpellSlots)(CNWSCreatureStats_ClassInfo *pThis, void *,unsigned char spell_level, unsigned char spell_num);
void (__fastcall *CNWSCreature__UpdateAttributesOnEffect)(CNWSCreature *pThis, void*, CGameEffect *eff, int arg1);
void (__fastcall *CNWSCreature__ResolveMeleeSpecialAttack)(CNWSCreature *pThis, void*, int a1, int a2, CNWSObject *target, int a4);
void (__fastcall *CNWSCreature__ResolveRangedSpecialAttack)(CNWSCreature *pThis, void*, CNWSObject *target, int a1);
int (__fastcall *CNWSCreatureStats__ResolveSpecialAttackAttackBonus)(CNWSCreatureStats *pThis, void*, CNWSCreature *target);
int (__fastcall *CNWSCreatureStats__ResolveSpecialAttackDamageBonus)(CNWSCreatureStats *pThis, void*, CNWSCreature *target);
char (__fastcall *CNWSCreatureStats__GetBaseReflexSavingThrow)(CNWSCreatureStats *pThis, void *);
char (__fastcall *CNWSCreatureStats__GetBaseFortSavingThrow)(CNWSCreatureStats *pThis, void *);
char (__fastcall *CNWSCreatureStats__GetBaseWillSavingThrow)(CNWSCreatureStats *pThis, void *);
void (__fastcall *CNWSObject__ClearAllPartyInvalidActions)(CNWSObject *pThis, void *);
unsigned char (__fastcall *CNWSItem__GetMinEquipLevel)(CNWSItem *pThis, void*);
char (__fastcall *CNWSCreatureStats__GetTotalACSkillMod)(CNWSCreatureStats *pThis, void*);
int (__fastcall *CNWSCreature__GetUseMonkAbilities)(CNWSCreature *pThis, void*);
void (__fastcall *CNWSCreature__SetActivity)(CNWSCreature *pThis, void*, int nActivity, int bOn);
int (__fastcall *CNWSTrigger__GetCanFireTrapOnObject)(CNWSTrigger *pThis, void*, unsigned long targetID, int arg1);
int (__fastcall *CNWSCreatureStats__GetFavoredEnemyBonus)(CNWSCreatureStats *pThis, void*, CNWSCreature *cre);
int (__fastcall *CNWSCreatureStats__GetSpellResistance)(CNWSCreatureStats *pThis, void*);
int (__fastcall *CNWSCreature__AddPickPocketAction)(CNWSCreature *pThis, void*, unsigned long targetID);
int (__fastcall *CNWSCreature__AddTauntActions)(CNWSCreature *pThis, void*, unsigned long targetID);
int (__fastcall *CNWSCreature__AddAnimalEmpathyAction)(CNWSCreature *pThis, void*, unsigned long targetID);
int (__fastcall *CNWSCreature__StartBarter)(CNWSCreature *pThis, void*, unsigned long targetID, unsigned long itemID, int arg1);
int (__fastcall *CNWSCreature__EventHandler)(CNWSCreature *pThis, void*, int arg1, int arg2, void *arg3, int arg4, int arg5);
void (__fastcall *CNWSCreatureStats__LevelDown)(CNWSCreatureStats *pThis, void*, CNWLevelStats *CNWLevelStats);
void (__fastcall *CNWSCreatureStats__LevelUp)(CNWSCreatureStats *pThis, void*, CNWLevelStats *CNWLevelStats, unsigned char domain1, unsigned char domain2, unsigned char spellschool, int num_levels);
int (__fastcall *CNWSStore__SellItem)(CNWSStore *pThis, void *, CNWSItem *item, CNWSCreature *buyer, unsigned char a1, unsigned char a2);
unsigned long (__fastcall *CServerExoAppInternal__ValidateCreateServerCharacter)(CServerExoAppInternal *pThis, void*, CNWSPlayer *player, void *, unsigned long l1);
float (__fastcall *CNWSCreature__GetMovementRateFactor)(CNWSCreature *pThis, void*);
//spellcasting
int (__fastcall *CNWRules__IsArcaneClass)(CNWRules *pThis, void *, unsigned char cls_id);
unsigned char (__fastcall *CNWSpell__GetSpellLevel)(CNWSpell *pThis, void *, unsigned char cls_id);
unsigned char (__fastcall *CNWSCreatureStats__GetSpellGainWithBonus)(CNWSCreatureStats *pThis, void *, unsigned char cls_pos, unsigned char spell_lvl);
unsigned char (__fastcall *CNWSCreatureStats__GetSpellGainWithBonusAfterLevelUp)(CNWSCreatureStats *pThis, void *, unsigned char cls_pos, unsigned char spell_lvl, CNWLevelStats *lvlstats, unsigned char spell_school, int is_first_lvl);
int (__fastcall *CNWSCreatureStats__GetSpellMinAbilityMet)(CNWSCreatureStats *pThis, void *, unsigned char cls_pos, unsigned char spell_lvl);
void (__fastcall *CNWSCreatureStats__UpdateNumberMemorizedSpellSlots)(CNWSCreatureStats *pThis, void *);
unsigned char (__fastcall *CNWSCreatureStats__ComputeNumberKnownSpellsLeft)(CNWSCreatureStats *pThis, void *, unsigned char cls_pos, unsigned char spell_lvl);
int (__fastcall *CNWSCreatureStats_ClassInfo__ConfirmDomainSpell)(CNWSCreatureStats_ClassInfo *pThis, void *, unsigned char domain_lvl, long spell_id);
unsigned char (__fastcall *CNWSCreatureStats__GetSpellUsesLeft)(CNWSCreatureStats *pThis, void *, long spell_id, unsigned char cls_pos, unsigned char spell_lvl, unsigned char metamagic);
int (__fastcall *CNWSCreature__LearnScroll)(CNWSCreature *pThis, void*, unsigned long itemID);
void (__fastcall *CNWSCreatureStats__AdjustSpellUsesPerDay)(CNWSCreatureStats *pThis, void *);
void (__fastcall *CNWSCreatureStats__ComputeFeatBonuses)(CNWSCreatureStats *pThis, void*, int *a1, int a2, int a3);
void (__fastcall *CNWSCreature__ReadItemsFromGff)(CNWSCreature *pThis, void*, CResGFF *a1, CResStruct *a2, int a3, int a4);
void (__fastcall *CNWSCreature__PossessFamiliar)(CNWSCreature *pThis, void*);
void (__fastcall *CNWSCreature__UnpossessFamiliar)(CNWSCreature *pThis, void*);
int (__fastcall *CNWSCreature__GetIsPossessedFamiliar)(CNWSCreature *pThis, void*);
int (__fastcall *CNWSCreatureStats__CanLevelUp)(CNWSCreatureStats *pThis, void*);
void (__fastcall *CNWSCombatRound__StartCombatRound)(CNWSCombatRound *pThis, void *, unsigned long a1);
void (__fastcall *CNWSCombatRound__InitializeNumberOfAttacks)(CNWSCombatRound *pThis, void*);
int (__fastcall *CNWSCreature__UseFeat)(CNWSCreature *pThis, void*, unsigned short nFeat, unsigned short subradial, unsigned long targetID, unsigned long a4, Vector *a5);
int (__fastcall *CNWSCreatureStats__GetBaseAttackBonus)(CNWSCreatureStats *pThis, void*, int bPreEpicOnly);
int (__fastcall *CNWSCreature__GetFlanked)(CNWSCreature *pThis, void*, CNWSCreature *target);
unsigned char (__fastcall *CNWSCreatureStats__GetFeatTotalUses)(CNWSCreatureStats *pThis, void *, unsigned short feat_id);
unsigned char (__fastcall *CNWSCreatureStats__GetFeatRemainingUses)(CNWSCreatureStats *pThis, void *, unsigned short feat_id);
void (__fastcall *CNWSCreatureStats__SetFeatRemainingUses)(CNWSCreatureStats *pThis, void *, unsigned short feat_id, unsigned char feat_uses);
void (__fastcall *CNWSCreatureStats__ResetFeatRemainingUses)(CNWSCreatureStats *pThis, void *);
void (__fastcall *CNWSCreatureStats__IncrementFeatRemainingUses)(CNWSCreatureStats *pThis, void *, unsigned short feat_id);
void (__fastcall *CNWSCreatureStats__DecrementFeatRemainingUses)(CNWSCreatureStats *pThis, void *, unsigned short feat_id);
int (__fastcall *CNWSObject__GetIsPCDying)(CNWSObject *pThis, void*);
void (__fastcall *CNWSCreature__RestoreItemProperties)(CNWSCreature *pThis, void*);
void (__fastcall *CNWSItem__RemoveItemProperties)(CNWSItem *pThis, void*, CNWSCreature *cre, unsigned long l);
short (__fastcall *CNWSCreature__GetMaxHitPoints)(CNWSCreature *pThis, void*, int n);

short __fastcall CNWSCreature__GetMaxHitPoints_Hook(CNWSCreature *pThis, void *, int n)
{
	Log(3,"o CNWSCreature__GetMaxHitPoints start\n");
	short retVal = CNWSCreature__GetMaxHitPoints(pThis,NULL,n);
	retVal+= pThis->obj.obj_vartable.GetInt(CExoString("HP_BONUS"));
	int hp_percent = pThis->obj.obj_vartable.GetInt(CExoString("HP_%"));
	if(hp_percent)
	{
		hp_percent = (retVal/100)*hp_percent;
		retVal+= hp_percent;
	}
	if(retVal < 1) retVal = 1;
	if(pThis->obj.obj_hp_cur > retVal)
	{
		pThis->obj.obj_hp_cur = retVal;//fix for issue where lowering max hitpoints didn't updated current hitpoints (if they were higher than new max)
	}
	return retVal;
}

void __fastcall CNWRules__ReloadAll_Hook(CNWRules *pThis, void *)
{
	Log(2,"o CNWRules__ReloadAll start\n");
	if(classes_2da) classes_2da->Unload2DArray();
	if(racialtypes_2da) racialtypes_2da->Unload2DArray();
	CNWRules__ReloadAll(pThis,NULL);
}

int __fastcall CNWSObject__GetIsPCDying_Hook(CNWSObject *pThis, void*)
{
	Log(3,"o CNWSObject__GetIsPCDying start\n");
	int retVal = CNWSObject__GetIsPCDying(pThis,NULL);
	if(retVal && pThis->obj_vartable.GetInt(CExoString("IMMUNITY_DYING")) > 0)
	{
		return 0;
	}
	return retVal;
}

unsigned char __fastcall CNWSCreatureStats__GetFeatRemainingUses_Hook(CNWSCreatureStats *pThis, void *, unsigned short feat_id)
{
	Log(2,"o CNWSCreatureStats__GetFeatRemainingUses start\n");
	CNWFeat *feat = NWN_Rules->GetFeat(feat_id);
	if(!feat || !pThis->HasFeat(feat_id)) return 0;
	unsigned int th = 0;
	CNWSStats_FeatUses *featuses = (CNWSStats_FeatUses*)(CExoArrayList_ptr_get(&(pThis->cs_featuses), th));
	while(featuses)
	{
		if(featuses->m_nFeat == feat_id)
		{
			return featuses->m_nUsedToday;
		}
		featuses = (CNWSStats_FeatUses*)(CExoArrayList_ptr_get(&(pThis->cs_featuses), ++th));
	}
	return 100;
}

void __fastcall CNWSCreatureStats__SetFeatRemainingUses_Hook(CNWSCreatureStats *pThis, void *, unsigned short feat_id, unsigned char feat_uses)
{
	Log(2,"o CNWSCreatureStats__SetFeatRemainingUses start\n");
	CNWFeat *feat = NWN_Rules->GetFeat(feat_id);
	if(!feat || !pThis->HasFeat(feat_id)) return;
	unsigned int th = 0;
	CNWSStats_FeatUses *featuses = (CNWSStats_FeatUses*)(CExoArrayList_ptr_get(&(pThis->cs_featuses), th));
	while(featuses)
	{
		if(featuses->m_nFeat == feat_id)
		{
			featuses->m_nUsedToday = feat_uses;
			return;
		}
		featuses = (CNWSStats_FeatUses*)(CExoArrayList_ptr_get(&(pThis->cs_featuses), ++th));
	}
}

void __fastcall CNWSCreatureStats__ResetFeatRemainingUses_Hook(CNWSCreatureStats *pThis, void *)
{
	unsigned int th = 0;
	CNWSStats_FeatUses *featuses = (CNWSStats_FeatUses*)(CExoArrayList_ptr_get(&(pThis->cs_featuses), th));
	while(featuses)
	{
		featuses->m_nUsedToday = pThis->GetFeatTotalUses(featuses->m_nFeat);
		featuses = (CNWSStats_FeatUses*)(CExoArrayList_ptr_get(&(pThis->cs_featuses), ++th));
	}
}

void __fastcall CNWSCreatureStats__IncrementFeatRemainingUses_Hook(CNWSCreatureStats *pThis, void *, unsigned short feat_id)
{
	Log(2,"o CNWSCreatureStats__IncrementFeatRemainingUses start\n");
	CNWSCreatureStats__DecrementFeatRemainingUses(pThis,NULL,feat_id);
}

void __fastcall CNWSCreatureStats__DecrementFeatRemainingUses_Hook(CNWSCreatureStats *pThis, void *, unsigned short feat_id)
{
	Log(2,"o CNWSCreatureStats__DecrementFeatRemainingUses start\n");
	CNWSCreatureStats__IncrementFeatRemainingUses(pThis,NULL,feat_id);
}

unsigned char __fastcall CNWSCreatureStats__GetFeatTotalUses_Hook(CNWSCreatureStats *pThis, void *, unsigned short feat_id)
{
	Log(2,"o CNWSCreatureStats__GetFeatTotalUses start\n");
	CNWFeat *feat = NWN_Rules->GetFeat(feat_id);
	if(!feat || !pThis->HasFeat(feat_id)) return 0;
	char *var = new char[32];
	sprintf_s(var,32,"GetFeatTotalUses_%i",feat_id);
	CExoString varname = CExoString(var);
	delete var;
	if(pThis->cs_original->obj.obj_vartable.MatchIndex(varname,VARIABLE_TYPE_INT,0) != NULL)
	{
		return pThis->cs_original->obj.obj_vartable.GetInt(varname);
	}
	if(feat_id == 331 && pThis->HasFeat(feat_id))
	{
		unsigned char level_gruumsh = pThis->GetNumLevelsOfClass(CLASS_TYPE_EYE_OF_GRUUMSH);
		if(level_gruumsh > 0)
		{			
			return 1+(level_gruumsh+pThis->GetNumLevelsOfClass(CLASS_TYPE_BARBARIAN))/4;
		}
	}
	return CNWSCreatureStats__GetFeatTotalUses(pThis,NULL,feat_id);
}

int __fastcall CNWSCreature__GetFlanked_Hook(CNWSCreature *pThis, void*, CNWSCreature *target)
{
	Log(2,"o CNWSCreature__GetFlanked start\n");
	if(target->obj.obj_vartable.GetInt(CExoString("IMMUNITY_FLANKING")) > 0)
	{
		return 0;
	}
	int retVal = CNWSCreature__GetFlanked(pThis,NULL,target);
	if(DnDUncannyDodge && retVal && (target->cre_stats->HasFeat(251) || target->cre_stats->HasFeat(252) || target->cre_stats->HasFeat(253) || target->cre_stats->HasFeat(254) || target->cre_stats->HasFeat(255)))
	{
		unsigned char granted = 0, uncannypower = 0, roguelevels = 0, cls_id = 255;
		for(unsigned char cls_pos=0;cls_pos<target->cre_stats->cs_classes_len;cls_pos++)
		{
			cls_id = target->cre_stats->cs_classes[cls_pos].cl_class;
			CNWClass *cClass = &(NWN_Rules->m_lstClasses[cls_id]);
			if(cClass && cClass->IsGrantedFeat(195,granted))
			{
				uncannypower+= target->cre_stats->GetClassLevel(cls_pos,true);
			}
		}
		for(unsigned char cls_pos=0;cls_pos<pThis->cre_stats->cs_classes_len;cls_pos++)
		{
			cls_id = pThis->cre_stats->cs_classes[cls_pos].cl_class;
			CNWClass *cClass = &(NWN_Rules->m_lstClasses[cls_id]);
			if(cClass && (cClass->IsGrantedFeat(221,granted) || cClass->IsGrantedFeat(455,granted) || cClass->IsGrantedFeat(221,granted)))
			{
				roguelevels+= pThis->cre_stats->GetClassLevel(cls_pos,true);
			}
		}
		retVal = roguelevels >= uncannypower+4;
	}
	return retVal;
}

int __fastcall CNWSCreatureStats__GetBaseAttackBonus_Hook(CNWSCreatureStats *pThis, void*, int bPreEpicOnly)
{
	Log(2,"o CNWSCreatureStats__GetBaseAttackBonus start\n");
	if(bPreEpicOnly)
	{
		int orig = CNWSCreatureStats__GetBaseAttackBonus(pThis,NULL,bPreEpicOnly);
		for(unsigned int nEffect = 0; nEffect < pThis->cs_original->obj.obj_effects_len; nEffect++)
		{
			CGameEffect* e = *(pThis->cs_original->obj.obj_effects+nEffect);
			if(e->eff_type == 96)
			{
				if(e->eff_integers[0] > 0)
				{
					orig = e->eff_integers[0];
				}
			}
		}	
		return orig;
	}
	return CNWSCreatureStats__GetBaseAttackBonus(pThis,NULL,bPreEpicOnly);
}

int __fastcall CNWSCreature__GetTotalEffectBonus_Hook(CNWSCreature *pThis, void*, char a2, CNWSObject *obj_a, int a4, int a5, unsigned __int8 a6, unsigned __int8 a7, unsigned __int8 a8, unsigned __int8 a9, int a10)
{
	Log(3,"o CNWSCreature__GetTotalEffectBonus start\n");
	if(a2 == 1)
	{
		int bonus = 0;
		char wpn_type = pThis->cre_combat_round->GetAttack(pThis->cre_combat_round->CurrentAttack)->m_nWeaponAttackType;
		CNWSCreature *target = !obj_a ? NULL : NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(obj_a->obj_generic.obj_id);
		for(unsigned int nEffect = 0; nEffect < pThis->obj.obj_effects_len; nEffect++)
		{
			CGameEffect* e = *(pThis->obj.obj_effects+nEffect);
			if(e->eff_type == EFFECT_TRUETYPE_ATTACK_INCREASE && e->eff_integers[5] == 1)
			{
				e->eff_type = 99;
				if((!e->eff_integers[1] || (e->eff_integers[1] == wpn_type || (e->eff_integers[1] == 6 && (wpn_type == 1 || wpn_type == 3)) || (wpn_type == 8 && e->eff_integers[1] == 7))) &&
					(e->eff_integers[2] == RACIAL_TYPE_INVALID || (target && target->cre_stats->cs_race == e->eff_integers[2])) && 
					(!e->eff_integers[3] || (target && target->cre_stats->GetSimpleAlignmentLawChaos() == e->eff_integers[3])) &&
					(!e->eff_integers[4] || (target && target->cre_stats->GetSimpleAlignmentGoodEvil() == e->eff_integers[4])))
				{
					bonus+= e->eff_integers[0];
				}
			}
		}	
		int retVal = CNWSCreature__GetTotalEffectBonus(pThis,NULL,a2,obj_a,a4,a5,a6,a7,a8,a9,a10);
		for(unsigned int nEffect = 0; nEffect < pThis->obj.obj_effects_len; nEffect++)
		{
			CGameEffect* e = *(pThis->obj.obj_effects+nEffect);
			if(e->eff_type == 99)
			{
				e->eff_type = EFFECT_TRUETYPE_ATTACK_INCREASE;
			}
		}
		return retVal+bonus;
	}
	else if(a2 == 4)
	{
		int bonus = 0;
		for(unsigned int nEffect = 0; nEffect < pThis->obj.obj_effects_len; nEffect++)
		{
			
			CGameEffect* e = *(pThis->obj.obj_effects+nEffect);
			if(e->eff_type == EFFECT_TRUETYPE_ABILITY_INCREASE && e->eff_integers[5] == 1)
			{
				e->eff_type = 99;
				if(e->eff_integers[0] == a9)
				{
					bonus+= e->eff_integers[1];	
				}
			}
		}	
		int retVal = CNWSCreature__GetTotalEffectBonus(pThis,NULL,a2,obj_a,a4,a5,a6,a7,a8,a9,a10);
		for(unsigned int nEffect = 0; nEffect < pThis->obj.obj_effects_len; nEffect++)
		{
			CGameEffect* e = *(pThis->obj.obj_effects+nEffect);
			if(e->eff_type == 99)
			{
				e->eff_type = EFFECT_TRUETYPE_ABILITY_INCREASE;
			}
		}
		return retVal+bonus;	
	}
	return CNWSCreature__GetTotalEffectBonus(pThis,NULL,a2,obj_a,a4,a5,a6,a7,a8,a9,a10);
}

int __fastcall CNWSCreature__UseFeat_Hook(CNWSCreature *pThis, void*, unsigned short nFeat, unsigned short subradial, unsigned long targetID, unsigned long a4, Vector *a5)
{
	Log(2,"o CNWSCreature__UseFeat start\n");
	CNWFeat *feat = NWN_Rules->GetFeat(nFeat);
	if(feat && feat->m_nSpellId == -1 && targetID != OBJECT_INVALID && pThis->cre_is_pc && pThis->cre_stats->HasFeat(nFeat))
	{
		switch(nFeat)
		{
		//attack modes - npcs uses them as feat
		case 19://improved power attack
		case 28://power attack
		case 30://rapid shot
		case 204://flurry of blows
		case 389://expertise
		case 390://improved expertise
		case 425://dirty fighting
			break;
		/*
		case 5://called shot
		case 9://disarm
		case 16://improved disarm
		case 17://improved knockdown
		case 23://knockdown
		case 31://sap
		case 39://stunning fist
		case 296://quivering palm
		case 301://smite evil
		case 472://smite good
		case 882://ki damage
			*/
		default:
			pThis->obj.obj_vartable.SetInt(CExoString("SPECIAL_ATTACK_EVENT"),1,1);
			pThis->obj.obj_vartable.SetInt(CExoString("SPECIAL_ATTACK_TYPE"),nFeat == 5 ? subradial : nFeat,1);
			pThis->obj.obj_vartable.SetObject(CExoString("SPECIAL_ATTACK_TARGET"),targetID);
			if(!NWN_VirtualMachine->Runscript(&CExoString("70_s2_specattk"),pThis->obj.obj_generic.obj_id,1))
			{
				//this will happen if user doesn't have script 70_s2_stunfist which means he most likely uses plugin but not patch
				break;
			}
			//cleanup
			pThis->obj.obj_vartable.DestroyInt(CExoString("SPECIAL_ATTACK_EVENT"));
			pThis->obj.obj_vartable.DestroyInt(CExoString("SPECIAL_ATTACK_TYPE"));
			pThis->obj.obj_vartable.DestroyObject(CExoString("SPECIAL_ATTACK_TARGET"));
			return 1;
		}
	}
	return CNWSCreature__UseFeat(pThis,NULL,nFeat,subradial,targetID,a4,a5);
}

void __fastcall CNWSCombatRound__InitializeNumberOfAttacks_Hook(CNWSCombatRound *pThis, void*)
{
	Log(2,"o CNWSCombatRound__InitializeNumberOfAttacks start\n");
	CNWSCombatRound__InitializeNumberOfAttacks(pThis,NULL);
	int attk_override = pThis->Creature->obj.obj_vartable.GetInt(CExoString("NUM_ONHAND"));
	if(attk_override > 0)
		pThis->OnHandAttacks = attk_override;
	if(pThis->Creature->obj.obj_vartable.MatchIndex(CExoString("NUM_OFFHAND"),VARIABLE_TYPE_INT,0) != NULL)
		pThis->OffHandAttacks = pThis->Creature->obj.obj_vartable.GetInt(CExoString("NUM_OFFHAND"));
	if(pThis->Creature->obj.obj_vartable.MatchIndex(CExoString("NUM_EXTRA"),VARIABLE_TYPE_INT,0) != NULL)
		pThis->AdditAttacks = pThis->Creature->obj.obj_vartable.GetInt(CExoString("NUM_EXTRA"));
}

void __fastcall CNWSCombatRound__StartCombatRound_Hook(CNWSCombatRound *pThis, void *, unsigned long a1)
{
	Log(2,"o CNWSCombatRound__StartCombatRound start\n");
	if(!pThis || !pThis->Creature) return;
/*	if(pThis->Creature->cre_is_pc)
	{
		NWN_VirtualMachine->Runscript(&CExoString("70_mod_cmbround"),pThis->Creature->obj.obj_generic.obj_id,1);//probably useless
	}*/
	CNWSCombatRound__StartCombatRound(pThis,NULL,a1);
	if(pThis->Creature->obj.obj_vartable.MatchIndex(CExoString("NUM_ED"),VARIABLE_TYPE_INT,0) != NULL)
	{
		pThis->Creature->obj.obj_vartable.SetInt(CExoString("NUM_ED_Used"),pThis->Creature->obj.obj_vartable.GetInt(CExoString("NUM_ED")),1);
	}
	if(pThis->Creature->obj.obj_vartable.MatchIndex(CExoString("NUM_DEFLECT"),VARIABLE_TYPE_INT,0) != NULL)
	{
		pThis->Creature->obj.obj_vartable.SetInt(CExoString("NUM_DEFLECT_Used"),pThis->Creature->obj.obj_vartable.GetInt(CExoString("NUM_DEFLECT")),1);
	}
	if(pThis->Creature->obj.obj_vartable.MatchIndex(CExoString("NUM_AOO"),VARIABLE_TYPE_INT,0) != NULL)
	{
		int numAOOs = pThis->Creature->obj.obj_vartable.GetInt(CExoString("NUM_AOO"));
		if(numAOOs >= 0)
		{
			pThis->NumAOOs = numAOOs;
		}
	}
}

char __fastcall CNWSCreatureStats__GetBaseReflexSavingThrow_Hook(CNWSCreatureStats *pThis, void*)
{
	Log(2,"o CNWSCreatureStats__GetBaseReflexSavingThrow start\n");
	int nMod = pThis->cs_original->obj.obj_vartable.GetInt(CExoString("ReflexSaveModifier"));
	if(pThis->cs_original->obj.obj_vartable.MatchIndex(CExoString("ReflexSaveOverride"),VARIABLE_TYPE_INT,0) != NULL)
	{
		int nSave = pThis->cs_original->obj.obj_vartable.GetInt(CExoString("ReflexSaveOverride"))+nMod;
		if(nSave > 127)
			return 127;
		else if(nSave < -127)
			return -127;
		return nSave;
	}
	return CNWSCreatureStats__GetBaseReflexSavingThrow(pThis,NULL)+nMod;
}

char __fastcall CNWSCreatureStats__GetBaseFortSavingThrow_Hook(CNWSCreatureStats *pThis, void*)
{
	Log(2,"o CNWSCreatureStats__GetBaseFortSavingThrow start\n");
	int nMod = pThis->cs_original->obj.obj_vartable.GetInt(CExoString("FortitudeSaveModifier"));
	if(pThis->cs_original->obj.obj_vartable.MatchIndex(CExoString("FortitudeSaveOverride"),VARIABLE_TYPE_INT,0) != NULL)
	{
		int nSave = pThis->cs_original->obj.obj_vartable.GetInt(CExoString("FortitudeSaveOverride"))+nMod;
		if(nSave > 127)
			return 127;
		else if(nSave < -127)
			return -127;
		return nSave;
	}
	return CNWSCreatureStats__GetBaseFortSavingThrow(pThis,NULL)+nMod;
}

char __fastcall CNWSCreatureStats__GetBaseWillSavingThrow_Hook(CNWSCreatureStats *pThis, void*)
{
	Log(2,"o CNWSCreatureStats__GetBaseWillSavingThrow start\n");
	int nMod = pThis->cs_original->obj.obj_vartable.GetInt(CExoString("WillSaveModifier"));
	if(pThis->cs_original->obj.obj_vartable.MatchIndex(CExoString("WillSaveOverride"),VARIABLE_TYPE_INT,0) != NULL)
	{
		int nSave = pThis->cs_original->obj.obj_vartable.GetInt(CExoString("WillSaveOverride"))+nMod;
		if(nSave > 127)
			return 127;
		else if(nSave < -127)
			return -127;
		return nSave;
	}
	return CNWSCreatureStats__GetBaseWillSavingThrow(pThis,NULL)+nMod;
}

float __fastcall CNWSCreature__GetMovementRateFactor_Hook(CNWSCreature *pThis, void*)
{
	Log(3,"o CNWSCreature__GetMovementRateFactor start\n");
	float fSpeed = CNWSCreature__GetMovementRateFactor(pThis,NULL);
	if(pThis->obj.obj_vartable.MatchIndex(CExoString("MovementRateFactorModifier"),VARIABLE_TYPE_FLOAT,0) != NULL)
	{
		fSpeed+= pThis->obj.obj_vartable.GetFloat(CExoString("MovementRateFactorModifier"));
	}
	return fSpeed;
}

int __fastcall CNWSCreatureStats__CanLevelUp_Hook(CNWSCreatureStats *pThis, void*)
{
	Log(2,"o CNWSCreatureStats__CanLevelUp start\n");
	if(pThis->cs_original->GetIsPossessedFamiliar() || pThis->cs_original->cre_pm_IsPolymorphed) 
		return 0;
	return CNWSCreatureStats__CanLevelUp(pThis,NULL);
}

void __fastcall CNWSCreature__ReadItemsFromGff_Hook(CNWSCreature *pThis, void*, CResGFF *a1, CResStruct *a2, int a3, int a4)
{
	Log(2,"o CNWSCreature__ReadItemsFromGff start\n");
	int prev = helper;
	helper = 56;
	CNWSCreature__ReadItemsFromGff(pThis,NULL,a1,a2,a3,a4);
	helper = prev;
	pThis->cre_stats->AdjustSpellUsesPerDay();
	CResList *list = new CResList();
	CResStruct *list_element = new CResStruct();
	int test = 0;
	if(a1->GetList(list,a2,"FeatList"))
	{
		unsigned long list_len = a1->GetListCount(list);			
		for(unsigned long th=0;th < list_len;th++)
		{			
			if(a1->GetListElement(list_element,list,th))
			{
				unsigned char feat_uses = a1->ReadFieldBYTE(list_element,"Uses",test,0);
				if(test)
				{
					unsigned short feat_id = a1->ReadFieldWORD(list_element,"Feat",test,0);
					if(test)
					{
						pThis->cre_stats->SetFeatRemainingUses(feat_id,feat_uses);
					}					
				}	
			}
		}
	}
	delete list_element;
	delete list;
}

void __fastcall CNWSCreatureStats__ComputeFeatBonuses_Hook(CNWSCreatureStats *pThis, void*, int *a1, int a2, int a3)
{
	Log(2,"o CNWSCreatureStats__ComputeFeatBonuses start\n");
	int prev = helper;
	helper = 56;
	CNWSCreatureStats__ComputeFeatBonuses(pThis,NULL,a1,a2,a3);
	helper = prev;
}

void __fastcall CNWSCreatureStats__AdjustSpellUsesPerDay_Hook(CNWSCreatureStats *pThis, void*)
{
	Log(2,"o CNWSCreatureStats__AdjustSpellUsesPerDay start\n");
	if(helper == 56) return;//called from CNWSCreatureStats::ComputeFeatBonuses or CNWSCreature::ReadItemsFromGff
	else if(!pThis->cs_is_pc)
	{
		CNWSCreatureStats__AdjustSpellUsesPerDay(pThis,NULL);
		return;
	}
	for(unsigned char cls_pos=0;cls_pos<pThis->cs_classes_len;cls_pos++)
	{
		if(cls_cast_type[pThis->cs_classes[cls_pos].cl_class] & CAST_TYPE_SPONTANEOUS)
		{
			for(unsigned char spell_lvl=0;spell_lvl<10;spell_lvl++)
			{
				unsigned char spell_uses = pThis->GetSpellGainWithBonus(cls_pos, spell_lvl) + pThis->cs_classes[cls_pos].cl_spells_bonus[spell_lvl];
				if(spell_uses < pThis->cs_classes[cls_pos].cl_spells_max[spell_lvl])
				{
					if (pThis->GetSpellsPerDayLeft(cls_pos,spell_lvl) > spell_uses)
					{
						pThis->cs_classes[cls_pos].cl_spells_left[spell_lvl] = spell_uses;
					}
				}
				pThis->cs_classes[cls_pos].cl_spells_max[spell_lvl] = spell_uses;
			}
		}
	}
}

int __fastcall CNWSEffectListHandler__OnEffectApplied_Hook(CNWSEffectListHandler *pThis, void*, CNWSObject *obj, CGameEffect *eff, int n)
{
	Log(3,"o CNWSEffectListHandler__OnEffectApplied start\n");
	int nRun = 0;
	if(eff->eff_type < 96)
	{
		char *var = new char[20];
		sprintf_s(var,20,"%i_EffectRegistered",eff->eff_type);
		CExoString VarName = CExoString(var);
		delete var;
		nRun = obj->obj_vartable.GetInt(VarName);
		if(nRun != 2 && (!effects_2da || !effects_2da->GetINTEntry_intcol(eff->eff_type,1,&nRun) || nRun != 1))
		{
			return CNWSEffectListHandler__OnEffectApplied(pThis,NULL,obj,eff,n);
		}
	}
	CNWSCreature *cre = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(obj->obj_generic.obj_id);
	if(nRun == 2 || (cre && (cre->cre_is_pc || (effects_2da->GetINTEntry_intcol(eff->eff_type,2,&nRun) && nRun == 0))))
	{
		if(eff->eff_type == 96 && cre) cre->m_bUpdateCombatInformation = 1;	
		obj->obj_vartable.SetInt(CExoString("EFFECT_EVENT_EVENT_TYPE"),1,1);
		helper_effect = eff;
		NWN_VirtualMachine->Runscript(&CExoString("70_mod_effects"),obj->obj_generic.obj_id,1);
		helper_effect = NULL;
		obj->obj_vartable.DestroyInt(CExoString("EFFECT_EVENT_EVENT_TYPE"));
		if(eff->eff_type >= 96) return 0;
		else if(obj->obj_vartable.GetInt(CExoString("EFFECT_EVENT_BYPASS")) > 0)
		{
			obj->obj_vartable.DestroyInt(CExoString("EFFECT_EVENT_BYPASS"));
			return 0;
		}
	}
	return CNWSEffectListHandler__OnEffectApplied(pThis,NULL,obj,eff,n);
}

int __fastcall CNWSEffectListHandler__OnEffectRemoved_Hook(CNWSEffectListHandler *pThis, void*, CNWSObject *obj, CGameEffect *eff)
{
	Log(3,"o CNWSEffectListHandler__OnEffectRemoved start\n");
	int nRun = 0;
	if(eff->eff_type < 96)
	{
		char *var = new char[20];
		sprintf_s(var,20,"%i_EffectRegistered",eff->eff_type);
		CExoString VarName = CExoString(var);
		delete var;
		nRun = obj->obj_vartable.GetInt(VarName);
		if(nRun != 2 && (!effects_2da || !effects_2da->GetINTEntry_intcol(eff->eff_type,1,&nRun) || nRun != 1))
		{
			return CNWSEffectListHandler__OnEffectRemoved(pThis,NULL,obj,eff);
		}
	}
	CNWSCreature *cre = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(obj->obj_generic.obj_id);
	if(nRun == 2 || (cre && (cre->cre_is_pc || (effects_2da->GetINTEntry_intcol(eff->eff_type,2,&nRun) && nRun == 0))))
	{
		if(eff->eff_type == 96 && cre) cre->m_bUpdateCombatInformation = 1;	
		obj->obj_vartable.SetInt(CExoString("EFFECT_EVENT_EVENT_TYPE"),2,1);
		helper_effect = eff;
		NWN_VirtualMachine->Runscript(&CExoString("70_mod_effects"),obj->obj_generic.obj_id,1);
		helper_effect = NULL;
		obj->obj_vartable.DestroyInt(CExoString("EFFECT_EVENT_EVENT_TYPE"));
		if(eff->eff_type >= 96) return 0;
		else if(obj->obj_vartable.GetInt(CExoString("EFFECT_EVENT_BYPASS")) > 0)
		{
			obj->obj_vartable.DestroyInt(CExoString("EFFECT_EVENT_BYPASS"));
			return 0;
		}
	}
	return CNWSEffectListHandler__OnEffectRemoved(pThis,NULL,obj,eff);
}

int __fastcall CNWSEffectListHandler__OnApplyDeath_Hook(CNWSEffectListHandler *pThis, void*, CNWSObject *obj, CGameEffect *eff, int n)//required for PossessCreature custom function
{
	Log(2,"o CNWSEffectListHandler__OnApplyDeath start\n");
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
	Log(3,"o CNWSCreature__GetIsPossessedFamiliar start\n");
	return !pThis->cre_is_pc && NWN_AppManager->app_server->GetIsControlledByPlayer(pThis->obj.obj_generic.obj_id);
}

void __fastcall CNWSCreature__PossessFamiliar_Hook(CNWSCreature *pThis, void*)
{
	Log(2,"o CNWSCreature__PossessFamiliar start\n");
	int prev = helper;
	CNWSCreature *cre = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(pThis->field_B48);
	if(cre)
	{
		helper = 222;
	}
	CNWSCreature__PossessFamiliar(pThis,NULL);
	helper = prev;
}

void __fastcall CNWSCreature__UnpossessFamiliar_Hook(CNWSCreature *pThis, void*)
{
	Log(2,"o CNWSCreature__UnpossessFamiliar start\n");
	int prev = helper;
	CNWSCreature *cre = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(pThis->field_B48);
	if(cre)
	{
		helper = 222;
	}
	CNWSCreature__UnpossessFamiliar(pThis,NULL);
	pThis->field_B48 = 0;
	helper = prev;
}

void __fastcall CNWSCreatureStats__LevelUp_Hook(CNWSCreatureStats *pThis, void*, CNWLevelStats *CNWLevelStats, unsigned char domain1, unsigned char domain2, unsigned char spellschool, int num_levels)
{
	Log(2,"o CNWSCreatureStats__LevelUp start\n");
	CNWSCreatureStats__LevelUp(pThis,NULL,CNWLevelStats,domain1,domain2,spellschool,num_levels);
	unsigned char cls_id = CNWLevelStats->m_nClass;
	CNWClass *cClass = &(NWN_Rules->m_lstClasses[cls_id]);
	if(cls_id != CLASS_TYPE_INVALID && cClass && cClass->m_bIsSpellCasterClass && ((cls_cast_type[cls_id] & CAST_TYPE_SPONTANEOUS) && !(cls_cast_type[cls_id] & CAST_TYPE_RESTRICTED_SPELLBOOK)))
	{
		unsigned char cls_pos = 3;
		for(unsigned char x=0;x<pThis->cs_classes_len;x++)
		{
			if(pThis->cs_classes[x].cl_class == cls_id)
			{
				cls_pos = x;
				break;
			}
		}
		if(cls_pos == 3) return;
		unsigned char cls_lvl = pThis->cs_classes[cls_pos].cl_level;
		unsigned char spell_lvl, lvl_max = 0;
		while(lvl_max < 10 && cClass->GetSpellGain(cls_lvl,lvl_max+1) != 255)
		{
			lvl_max++;
		}
		unsigned long num_known, hidden;
		for(unsigned long spell_id=0;spell_id < NWN_Rules->m_pSpellArray->spells_len;spell_id++)
		{
			spell_lvl = NWN_Rules->m_pSpellArray->GetSpell(spell_id)->GetSpellLevel(cls_id);					
			if(spell_lvl <= lvl_max)
			{
				hidden = NWN_Rules->m_pSpellArray->GetSpell(spell_id)->Hidden;
				if(hidden > 0 && (hidden == 255 || hidden == cls_id))//hidden spell
				{
					continue;
				}
				for(num_known=0;num_known < (unsigned long)pThis->cs_classes[cls_pos].cl_spells_known->len && num_known < 255;num_known++)
				{
					if(pThis->GetKnownSpell(cls_pos,spell_lvl,(unsigned char)num_known) == spell_id)//already knows
					{
						continue;
					}
				}
				if(num_known >= (unsigned long)pThis->cs_classes[cls_pos].cl_spells_known->len)
				{
					pThis->AddKnownSpell(cls_pos,spell_id);
				}
			}
		}
	}
}

void __fastcall CNWSCreatureStats__LevelDown_Hook(CNWSCreatureStats *pThis, void *, CNWLevelStats *CNWLevelStats)
{
	Log(2,"o CNWSCreatureStats__LevelDown start\n");
	pThis->cs_mclasslevupin = pThis->GetIsClass(CLASS_TYPE_DRAGONDISCIPLE);//fix for delevelling RDD
	NWN_AppManager->app_server->srv_internal->GetModule()->mod_vartable.SetInt(CExoString("GetLastLevelDownEventType()"),1,1);
	NWN_VirtualMachine->Runscript(&CExoString("70_mod_leveldown"),pThis->cs_original->obj.obj_generic.obj_id,1);
	CNWSCreatureStats__LevelDown(pThis,NULL,CNWLevelStats);
	pThis->cs_original->m_bUpdateCombatInformation = 1;
	NWN_AppManager->app_server->srv_internal->GetModule()->mod_vartable.SetInt(CExoString("GetLastLevelDownEventType()"),2,1);
	NWN_VirtualMachine->Runscript(&CExoString("70_mod_leveldown"),pThis->cs_original->obj.obj_generic.obj_id,1);
	NWN_AppManager->app_server->srv_internal->GetModule()->mod_vartable.DestroyInt(CExoString("GetLastLevelDownEventType()"));
}

int __fastcall CNWSCreature__LearnScroll_Hook(CNWSCreature *pThis, void *, unsigned long itemID)
{
	Log(2,"o CNWSCreature__LearnScroll start\n");
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


unsigned char __fastcall CNWSCreatureStats__GetSpellUsesLeft_Hook(CNWSCreatureStats *pThis, void *, unsigned long spell_id, unsigned char cls_pos, unsigned char domain_lvl, unsigned char metamagic)
{
	Log(2,"o CNWSCreatureStats__GetSpellUsesLeft start\n");
	if(!classes_2da)
	{
		return CNWSCreatureStats__GetSpellUsesLeft(pThis,NULL,spell_id,cls_pos,domain_lvl,metamagic);
	}
	unsigned char retValOrig = CNWSCreatureStats__GetSpellUsesLeft(pThis,NULL,spell_id,cls_pos,domain_lvl,metamagic);
	if(cls_pos >= pThis->cs_classes_len || spell_id == -1) return 0;//sometimes engine passes invalid values, in this case we need to return 0
	if(pThis->cs_original->cre_pm_IsPolymorphed) return 1;
	unsigned char retVal = 0;
	unsigned char cls_id = pThis->cs_classes[cls_pos].cl_class;
	CNWClass *cClass = &(NWN_Rules->m_lstClasses[cls_id]);
	CNWSpell *cSpell = NWN_Rules->m_pSpellArray->GetSpell(spell_id);
	if(cSpell->m_nMasterSpell != spell_id)//subradial spell workaround
	{
		spell_id = cSpell->m_nMasterSpell;
		cSpell = NWN_Rules->m_pSpellArray->GetSpell(spell_id);
	}
	unsigned char nLevel = cSpell->GetSpellLevel(cls_id);
	if(cClass && cSpell && cls_id < CLASS_TYPE_INVALID && cClass->m_bIsSpellCasterClass)
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
			unsigned int cls_level = pThis->cs_classes[cls_pos].cl_level-1;		
			if(cls_cast_type[cls_id] & CAST_TYPE_SPONTANEOUS)
			{
				unsigned char left = pThis->cs_classes[cls_pos].cl_spells_left[newLevel];
				if(left > 0)
				{
					int spell = pThis->GetKnownSpell(cls_pos,nLevel,0);
					for(unsigned char x=1;spell != -1;x++)
					{
						if(spell == spell_id)
						{
							if(cls_cast_unlimited[cls_id][cls_level] > 0 && (cls_cast_unlimited[cls_id][cls_level] & (1 << newLevel))) return 1;//unlimited casting
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
						if(cls_cast_unlimited[cls_id][cls_level] > 0 && (cls_cast_unlimited[cls_id][cls_level] & (1 << newLevel))) return 1;//unlimited casting
						retVal++;
					}
				}
			}
		}
	}
	if(retValOrig != retVal && cls_id < 11)
	{
		fprintf(logFile, "o CNWSCreatureStats__GetSpellUsesLeft_Hook: new calculation doesn't match with vanilla! cls_id %i, spell_id %i, domain_lvl: %i, metamagic: %i, oldval %i, newval: %i\n",pThis->cs_classes[cls_pos].cl_class,spell_id,domain_lvl,metamagic,retValOrig,retVal);fflush(logFile);
	}
	return retVal;
}

int __fastcall CNWSCreatureStats_ClassInfo__ConfirmDomainSpell_Hook(CNWSCreatureStats_ClassInfo *pThis, void *, unsigned char domain_lvl, unsigned long spell_id)
{
	Log(2,"o CNWSCreatureStats_ClassInfo__ConfirmDomainSpell start\n");
	if(!classes_2da)
	{
		return CNWSCreatureStats_ClassInfo__ConfirmDomainSpell(pThis,NULL,domain_lvl,spell_id);
	}
	else if(spell_id == -1) return 0;
	CNWClass *cClass = &(NWN_Rules->m_lstClasses[pThis->cl_class]);
	if(pThis->cl_class != CLASS_TYPE_INVALID && cClass && (cls_cast_type[pThis->cl_class] & CAST_TYPE_SELECT_DOMAINS))
	{
		CNWDomain *cDomain = NWN_Rules->GetDomain(pThis->cl_domain_1);
		if(pThis->cl_domain_1 != 255 && cDomain)
		{
			if(cDomain->SpellLevel[domain_lvl] == spell_id)
			{
				return 1;
			}
		}
		if(pThis->cl_domain_2 != 255)
		{
			cDomain = NWN_Rules->GetDomain(pThis->cl_domain_2);
			if(cDomain && cDomain->SpellLevel[domain_lvl] == spell_id)
			{
				return 1;
			}
		}
	}
	return 0;
}

unsigned char __fastcall CNWSCreatureStats__ComputeNumberKnownSpellsLeft_Hook(CNWSCreatureStats *pThis, void *, unsigned char cls_pos, unsigned char spell_lvl)
{
	Log(2,"o CNWSCreatureStats__ComputeNumberKnownSpellsLeft start\n");
	if(!classes_2da)
	{
		return CNWSCreatureStats__ComputeNumberKnownSpellsLeft(pThis,NULL,cls_pos,spell_lvl);
	}
	unsigned char cls_id = pThis->cs_classes[cls_pos].cl_class;
	if(cls_pos >= pThis->cs_classes_len || cls_id == CLASS_TYPE_INVALID) return 0;//sometimes engine passes 254/255 into class position, in this case we need to return 0
	unsigned char retVal = 0;
	CNWClass *cClass = &(NWN_Rules->m_lstClasses[cls_id]);
	if(cClass && cClass->m_bIsSpellCasterClass && (cls_cast_type[cls_id] & CAST_TYPE_SPONTANEOUS))
	{
		unsigned char level = pThis->cs_classes[cls_pos].cl_level;
		level+= GetSpellProgressionModifier(pThis,cls_pos);
		retVal = cClass->GetSpellsKnownPerLevel(level,spell_lvl,0,0,0);
		if(retVal == 255) retVal = 0;
		else if(spell_lvl > 0 && pThis->cs_classes[cls_pos].cl_specialist)
		{
			retVal++;
		}
		retVal-= (unsigned char)pThis->cs_classes[cls_pos].cl_spells_known[spell_lvl].len;//warning ulong -> uchar
	}
	unsigned char retValOrig = CNWSCreatureStats__ComputeNumberKnownSpellsLeft(pThis,NULL,cls_pos,spell_lvl);
	if(retValOrig != retVal && cls_id < 11)
	{
		fprintf(logFile, "o CNWSCreatureStats__ComputeNumberKnownSpellsLeft: new calculation doesn't match with vanilla! cls_id %i, spell_lvl %i, oldval %i, newval: %i\n",pThis->cs_classes[cls_pos].cl_class,spell_lvl,retValOrig,retVal);fflush(logFile);
	}
	return retVal;
}

int __fastcall CNWRules__IsArcaneClass_Hook(CNWRules *, void *, unsigned char cls_id)
{//ma vliv na nektere pravidla jako hluchota, somatic spell component, prestige class spell progression
	Log(3,"o CNWRules__IsArcaneClass start\n");
	if(!classes_2da)
	{
		return cls_id == CLASS_TYPE_WIZARD || cls_id == CLASS_TYPE_SORCERER || cls_id == CLASS_TYPE_BARD;
	}
	return cls_cast_type[cls_id] & CAST_TYPE_ARCANE;
}

unsigned char __fastcall CNWSpell__GetSpellLevel_Hook(CNWSpell *pThis, void *, unsigned char cls_id)
{//tohle pomuze vyplnit zname kouzla v knize kouzel
	Log(3,"o CNWSpell__GetSpellLevel start\n");
	switch(cls_id)
	{
	case CLASS_TYPE_WIZARD:
		return pThis->m_nWizardLevel;
	case CLASS_TYPE_SORCERER:
		return pThis->m_nSorcererLevel;
	case CLASS_TYPE_BARD:
		return pThis->m_nBardLevel;
	case CLASS_TYPE_CLERIC:
		return pThis->m_nClericLevel;
	case CLASS_TYPE_DRUID:
		return pThis->m_nDruidLevel;
	case CLASS_TYPE_RANGER:
		return pThis->m_nRangerLevel;
	case CLASS_TYPE_PALADIN:
		return pThis->m_nPaladinLevel;
	case CLASS_TYPE_INVALID:
		return 255;
	}
	if(pThis->m_nInnateLevel != 255 && spells_level_2da)
	{
		if(NWN_Rules->m_pSpellArray->GetSpell(pThis->m_nMasterSpell) != pThis)//safety check whether current spell is really what it says it is
		{
			return 255;
		}
		int retVal = 0;
		char *colname = new char[4];
		sprintf_s(colname,4,"%i",cls_id);
		CExoString column = CExoString(colname);
		delete colname;
		if(spells_level_2da->GetINTEntry_strcol(pThis->m_nMasterSpell,column,&retVal))
		{
			return (unsigned char)retVal;
		}
		return 255;
		//fprintf(logFile, "o CNWSpell__GetSpellLevel: spell_id: %i, cls_id: %i, retval: %i\n",pThis->sp_ID,cls_id,retVal);fflush(logFile);
	}
	return pThis->m_nInnateLevel;
}

void __fastcall CNWSCreatureStats__UpdateNumberMemorizedSpellSlots_Hook(CNWSCreatureStats *pThis, void *)
{
	Log(2,"o CNWSCreatureStats__UpdateNumberMemorizedSpellSlots start\n");
	if(helper == 56) return;//called from CNWSCreatureStats::ComputeFeatBonuses
	CNWClass *cClass;unsigned char spell_lvl, num_slots, cls_id;
	for(unsigned char x = 0;x < pThis->cs_classes_len; x++)
	{
		cls_id = pThis->cs_classes[x].cl_class;
		cClass = &(NWN_Rules->m_lstClasses[cls_id]);
		if(cls_id != 255 && cls_id != CLASS_TYPE_BARD && cls_id != CLASS_TYPE_SORCERER && cClass && cClass->m_bIsSpellCasterClass && !(cls_cast_type[cls_id] & CAST_TYPE_SPONTANEOUS))
		{
			for(spell_lvl = 0;spell_lvl < 10;spell_lvl++)
			{
				num_slots = pThis->GetSpellGainWithBonus(x,spell_lvl)+pThis->cs_classes[x].cl_spells_bonus[spell_lvl];
				pThis->cs_classes[x].SetNumberMemorizedSpellSlots(spell_lvl,num_slots);
			}
		}
	}
}

unsigned char __fastcall CNWSCreatureStats__GetSpellGainWithBonus_Hook(CNWSCreatureStats *pThis, void *, unsigned char cls_pos, unsigned char spell_lvl)
{
	Log(2,"o CNWSCreatureStats__GetSpellGainWithBonus start\n");
	if(!classes_2da)
	{
		return CNWSCreatureStats__GetSpellGainWithBonus(pThis,NULL,cls_pos,spell_lvl);
	}
	unsigned char cls_id = pThis->cs_classes[cls_pos].cl_class;
	if(cls_pos >= pThis->cs_classes_len || cls_id == CLASS_TYPE_INVALID) return 0;//sometimes engine passes 254/255 into class position, in this case we need to return 0
	unsigned char retVal = 0;
	char bonus = 0, abil_score = 0;
	CNWClass *cClass = &(NWN_Rules->m_lstClasses[cls_id]);
	CNWRace *cRace = &(NWN_Rules->m_lstRaces[pThis->cs_race]);
	if(cClass && cRace && cClass->m_bIsSpellCasterClass)
	{
		unsigned char level = pThis->cs_classes[cls_pos].cl_level;
		level+= GetSpellProgressionModifier(pThis,cls_pos);
		switch(cClass->m_nPrimaryAbility)
		{
		case ABILITY_STRENGTH:
			abil_score = pThis->cs_str;
			abil_score+= cRace->m_nSTRAdjust;
			bonus = pThis->cs_str_mod;
			break;
		case ABILITY_DEXTERITY:
			abil_score = pThis->cs_dex;
			abil_score+= cRace->m_nDEXAdjust;
			bonus = pThis->cs_dex_mod;
			break;
		case ABILITY_CONSTITUTION:
			abil_score = pThis->cs_con;
			abil_score+= cRace->m_nCONAdjust;
			bonus = pThis->cs_con_mod;
			break;
		case ABILITY_INTELLIGENCE:
			abil_score = pThis->cs_int;
			abil_score+= cRace->m_nINTAdjust;
			bonus = pThis->cs_int_mod;
			break;
		case ABILITY_WISDOM:
			abil_score = pThis->cs_wis;
			abil_score+= cRace->m_nWISAdjust;
			bonus = pThis->cs_wis_mod;
			break;
		case ABILITY_CHARISMA:
			abil_score = pThis->cs_cha;
			abil_score+= cRace->m_nCHAAdjust;
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
	unsigned char retValOrig = CNWSCreatureStats__GetSpellGainWithBonus(pThis,NULL,cls_pos,spell_lvl);
	if(retValOrig != retVal && cls_id < 11)
	{
		fprintf(logFile, "o CNWSCreatureStats__GetSpellGainWithBonus: new calculation doesn't match with vanilla! cls_id %i, spell_lvl %i, oldval %i, newval: %i, bonus: %i, abil_score: %i\n",pThis->cs_classes[cls_pos].cl_class,spell_lvl,retValOrig,retVal,bonus,abil_score);fflush(logFile);
	}
	return retVal;
}

unsigned char __fastcall CNWSCreatureStats__GetSpellGainWithBonusAfterLevelUp_Hook(CNWSCreatureStats *pThis, void *, unsigned char cls_pos, unsigned char spell_lvl, CNWLevelStats *lvlstats, unsigned char spell_school, int is_first_lvl)
{
	Log(2,"o CNWSCreatureStats__GetSpellGainWithBonusAfterLevelUp start\n");
	if(!classes_2da)
	{
		return CNWSCreatureStats__GetSpellGainWithBonusAfterLevelUp(pThis,NULL,cls_pos,spell_lvl,lvlstats,spell_school,is_first_lvl);
	}
	unsigned char retValOrig = CNWSCreatureStats__GetSpellGainWithBonusAfterLevelUp(pThis,NULL,cls_pos,spell_lvl,lvlstats,spell_school,is_first_lvl);
	unsigned char retVal = 0;
	unsigned char cls_id = is_first_lvl ? lvlstats->m_nClass : pThis->cs_classes[cls_pos].cl_class;
	char bonus = 0, abil_score = 0;
	if(cls_id != CLASS_TYPE_INVALID)
	{
		CNWClass *cClass = &(NWN_Rules->m_lstClasses[cls_id]);
		CNWRace *cRace = &(NWN_Rules->m_lstRaces[pThis->cs_race]);
		if(cClass && cRace && cClass->m_bIsSpellCasterClass)
		{
			unsigned char level = pThis->cs_classes[cls_pos].cl_level;
			if(lvlstats->m_nClass == pThis->cs_classes[cls_pos].cl_class) level++;
			level+= GetSpellProgressionModifier(pThis,cls_pos);
			switch(cClass->m_nPrimaryAbility)
			{
			case ABILITY_STRENGTH:
				abil_score = pThis->cs_str;
				abil_score+= cRace->m_nSTRAdjust;
				bonus = pThis->cs_str_mod;
				break;
			case ABILITY_DEXTERITY:
				abil_score = pThis->cs_dex;
				abil_score+= cRace->m_nDEXAdjust;
				bonus = pThis->cs_dex_mod;
				break;
			case ABILITY_CONSTITUTION:
				abil_score = pThis->cs_con;
				abil_score+= cRace->m_nCONAdjust;
				bonus = pThis->cs_con_mod;
				break;
			case ABILITY_INTELLIGENCE:
				abil_score = pThis->cs_int;
				abil_score+= cRace->m_nINTAdjust;
				bonus = pThis->cs_int_mod;
				break;
			case ABILITY_WISDOM:
				abil_score = pThis->cs_wis;
				abil_score+= cRace->m_nWISAdjust;
				bonus = pThis->cs_wis_mod;
				break;
			case ABILITY_CHARISMA:
				abil_score = pThis->cs_cha;
				abil_score+= cRace->m_nCHAAdjust;
				bonus = pThis->cs_cha_mod;
				break;
			}
			if(lvlstats->m_nAbilityGain == cClass->m_nPrimaryAbility)//player increased casting ability on this lvl
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
		fprintf(logFile, "o CNWSCreatureStats__GetSpellGainWithBonusAfterLevelUp: new calculation doesn't match with vanilla! cls_id %i, spell_lvl %i, oldval %i, newval: %i, bonus: %i, abil_score: %i\n",cls_id,spell_lvl,retValOrig,retVal,bonus,abil_score);fflush(logFile);
	}
	return retVal;
}

int __fastcall CNWSCreatureStats__GetSpellMinAbilityMet_Hook(CNWSCreatureStats *pThis, void *, unsigned char cls_pos, unsigned char spell_lvl)
{
	Log(2,"o CNWSCreatureStats__GetSpellMinAbilityMet start\n");
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
	CNWClass *cClass = &(NWN_Rules->m_lstClasses[cls_id]);
	CNWRace *cRace = &(NWN_Rules->m_lstRaces[pThis->cs_race]);
	if(cls_id != CLASS_TYPE_INVALID && cClass && cRace && cClass->m_bIsSpellCasterClass)
	{
		unsigned char abil_score = 0;
		switch(cClass->m_nPrimaryAbility)
		{
		case ABILITY_STRENGTH:
			abil_score = pThis->cs_str;
			abil_score+= cRace->m_nSTRAdjust;
			break;
		case ABILITY_DEXTERITY:
			abil_score = pThis->cs_dex;
			abil_score+= cRace->m_nDEXAdjust;
			break;
		case ABILITY_CONSTITUTION:
			abil_score = pThis->cs_con;
			abil_score+= cRace->m_nCONAdjust;
			break;
		case ABILITY_INTELLIGENCE:
			abil_score = pThis->cs_int;
			abil_score+= cRace->m_nINTAdjust;
			break;
		case ABILITY_WISDOM:
			abil_score = pThis->cs_wis;
			abil_score+= cRace->m_nWISAdjust;
			break;
		case ABILITY_CHARISMA:
			abil_score = pThis->cs_cha;
			abil_score+= cRace->m_nCHAAdjust;
			break;
		}
		//fprintf(logFile, "o CNWSCreatureStats__GetSpellMinAbilityMet: cls_pos: %i, spell_lvl: %i, retval: %i.\n",cls_pos,spell_lvl,abil_score >= spell_lvl+10);fflush(logFile);
		return abil_score >= spell_lvl+10;
	}
	return 0;
}

unsigned long __fastcall CServerExoAppInternal__ValidateCreateServerCharacter_Hook(CServerExoAppInternal *pThis, void*, CNWSPlayer *player, void *c, unsigned long l1)
{
	Log(2,"o CServerExoAppInternal__ValidateCreateServerCharacter start\n");
	if(NoServerCharacter)
	{
		return 57922;//Server doesn't allow server vault characters.
	}
	return CServerExoAppInternal__ValidateCreateServerCharacter(pThis,NULL,player,c,l1);
}

int __fastcall CNWSStore__SellItem_Hook(CNWSStore *pThis, void *, CNWSItem *item, CNWSCreature *buyer, unsigned char a1, unsigned char a2)
{
	Log(2,"o CNWSStore__SellItem start\n");
	if(pThis && item && buyer && !item->it_infinite)
	{
		unsigned char a4 = 0, a5 = 0;
		if(buyer->cre_inventory->FindPosition(item,a4,a5,0))
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
	Log(2,"o CServerExoAppInternal__RemovePCFromWorld start\n");
	CNWSModule *mod = srv->GetModule();
	if(mod)
	{		
		mod->m_oidLastExit = player->m_oidNWSObject;
		NWN_VirtualMachine->Runscript(&script_leave,mod->obj_id);
		if(mod && mod->mod_vartable.GetInt(bypass_event) == 1)
		{
			mod->mod_vartable.DestroyInt(bypass_event);
		}
		else
		{	
			NWN_VirtualMachine->Runscript(&mod->mod_scripts[5],mod->obj_id);
		}
	}
	CServerExoAppInternal__RemovePCFromWorld(srv, NULL, player);
}

void __fastcall CGameEffect__SetCreator_Hook(CGameEffect *pThis, void*, unsigned long creatorID)
{
	Log(2,"o CGameEffect__SetCreator start\n");
	pThis->eff_creator = creatorID;
	if(creatorID != OBJECT_INVALID)
	{
		CNWSObject *creator = (CNWSObject*)NWN_AppManager->app_server->srv_internal->GetGameObject(creatorID);
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
					if(cre->cre_item_spell_item != OBJECT_INVALID)//spell from item
					{
						nLevel = cre->cre_item_spell_level;
						CNWSObject *item = (CNWSObject*)NWN_AppManager->app_server->srv_internal->GetGameObject(cre->cre_item_spell_item);
						if(pThis->eff_spellid > -1 && item && item->obj_generic.obj_type2 == OBJECT_TYPE2_ITEM)
						{
							//community patch caster level override/modifier feature
							char *sVarName = new char[64];
							sprintf_s(sVarName,64,"%i_CASTER_LEVEL_OVERRIDE",pThis->eff_spellid);
							int cl_override = item->obj_vartable.GetInt(CExoString(sVarName));
							delete sVarName;
							if(!cl_override) cl_override = item->obj_vartable.GetInt(CExoString("ITEM_CASTER_LEVEL_OVERRIDE"));
							if(cl_override) nLevel = cl_override;
							else nLevel+= item->obj_vartable.GetInt(CExoString("ITEM_CASTER_LEVEL_MODIFIER"));
						}
					}
					else if(creator->obj_last_spell_class < cre->cre_stats->cs_classes_len)//normal spell
					{
						//Log(0, "CGameEffect__SetCreator_Hook normal spell last spell class: %i, spell_id: %i, feat: %i\n",creator->obj_last_spell_class,pThis->eff_spellid,creator->obj_last_spell_feat);
						nLevel = cre->cre_stats->GetClassLevel(creator->obj_last_spell_class,true);
						//include prestige classes into calculation
						if(creator->obj_last_spell_feat == 0xFFFF && NWN_Rules->m_pSpellArray->GetSpell(pThis->eff_spellid)->m_nUserType == 1)
						{
							unsigned char cls_pos = creator->obj_last_spell_class;
							unsigned char cls_id = cre->cre_stats->cs_classes[cls_pos].cl_class;
							CNWClass *cClass = &(NWN_Rules->m_lstClasses[cls_id]);
							if(cls_pos < cre->cre_stats->cs_classes_len && cls_id != CLASS_TYPE_INVALID && cClass && cClass->m_bIsSpellCasterClass)
							{
								nLevel+= GetSpellProgressionModifier(cre->cre_stats,cls_pos);
							}
						}
					}
					else//monster special ability or invalid data input in creator->obj_last_spell_class
					{
						nLevel = (NWN_Rules->m_pSpellArray->GetSpell(pThis->eff_spellid)->m_nInnateLevel*2)-1;
						if(nLevel < 10)
						{
							nLevel = 10;
						}
					}
				}
			}
			//community patch caster level override/modifier feature
			if(pThis->eff_spellid > -1 && creator->obj_last_spell_feat == 0xFFFF && NWN_Rules->m_pSpellArray->GetSpell(pThis->eff_spellid)->m_nUserType == 1)
			{
				char *sVarName = new char[64];
				sprintf_s(sVarName,64,"%i_CASTER_LEVEL_OVERRIDE",pThis->eff_spellid);
				int cl_override = creator->obj_vartable.GetInt(CExoString(sVarName));
				delete sVarName;
				if(!cl_override) cl_override = creator->obj_vartable.GetInt(CExoString(creator->obj_last_spell_class == 255 ? "SPECIAL_ABILITY_CASTER_LEVEL_OVERRIDE" : "SPELL_CASTER_LEVEL_OVERRIDE"));
				if(cl_override) nLevel = cl_override;
				else nLevel+= creator->obj_vartable.GetInt(CExoString(creator->obj_last_spell_class == 255 ? "SPECIAL_ABILITY_CASTER_LEVEL_MODIFIER" : "SPELL_CASTER_LEVEL_MODIFIER"));
			}
			pThis->eff_casterlvl = nLevel;
			//fprintf(logFile, "o SetCreator: effect caster level set to: %i\n",nLevel);fflush(logFile);
		}
	}
}

int __fastcall CNWVirtualMachineCommands__ExecuteCommandGetEffectSubType_Hook(CVirtualMachineCommands *, void*, int, int)
{
	Log(2,"o CNWVirtualMachineCommands__ExecuteCommandGetEffectSubType start\n");
	CGameEffect *eff;
	if(!NWN_VirtualMachine->StackPopEngineStructure(0,(void **)&eff))
	{
		return -639;
	}
	int retVal = eff->eff_dursubtype & 0x18;
	CNWSModule *mod = NWN_AppManager->app_server->srv_internal->GetModule();
	if(mod && mod->mod_vartable.MatchIndex(CExoString("GetEffectTrueType"),VARIABLE_TYPE_INT,0) != NULL)
	{	
		Log(1,"NWNXPatch_Funcs DEBUG: func GetEffectTrueType\n");
		retVal = eff->eff_type;
	}
	else if(mod && mod->mod_vartable.MatchIndex(CExoString("GetEffectInteger"),VARIABLE_TYPE_INT,0) != NULL)
	{
		Log(1,"NWNXPatch_Funcs DEBUG: func GetEffectInteger\n");
		retVal = eff->eff_integers[mod->mod_vartable.GetInt(CExoString("GetEffectInteger"))];
	}
	else if(mod && mod->mod_vartable.MatchIndex(CExoString("TransferEffectValues"),VARIABLE_TYPE_INT,0) != NULL)
	{
		Log(1,"NWNXPatch_Funcs DEBUG: func TransferEffectValues\n");
		if(helper_effect)
		{
			helper_effect->eff_casterlvl = eff->eff_casterlvl;
			helper_effect->eff_creator = eff->eff_creator;
			helper_effect->eff_duration = eff->eff_duration;
			helper_effect->eff_dursubtype = eff->eff_dursubtype;
			helper_effect->eff_expire_day = eff->eff_expire_day;
			helper_effect->eff_expire_time = eff->eff_expire_time;
			helper_effect->eff_is_iconshown = eff->eff_is_iconshown;
			helper_effect->eff_is_exposed = eff->eff_is_exposed;
			helper_effect->eff_spellid = eff->eff_spellid;
			helper_effect->eff_type = eff->eff_type;
			for(unsigned char x = 0;x<eff->eff_num_integers;x++)
			{
				helper_effect->SetInteger(x,eff->GetInteger(x));
			}
		}
		else
		{
			Log(0,"ERROR: TransferEffectValues() used in incorrect event!\n");
		}
	}
	else if(mod && mod->mod_vartable.MatchIndex(CExoString("GetEffectRemainingDuration"),VARIABLE_TYPE_FLOAT,0) != NULL)
	{
		Log(1,"NWNXPatch_Funcs DEBUG: func GetEffectRemainingDuration\n");
		if(eff->eff_expire_day != 0 && eff->eff_expire_time != 0)
		{
			unsigned long time_2880s = NULL, time_msec = NULL;
			NWN_AppManager->app_server->GetWorldTimer()->GetWorldTime(&time_2880s, &time_msec);
			int64_t ret = time_2880s;
			ret = (ret * 2880000LL) + time_msec;
			int64_t current = ret, expire = eff->eff_expire_day;
			expire = (expire * 2880000LL) + eff->eff_expire_time;
			mod->mod_vartable.SetFloat(CExoString("GetEffectRemainingDuration"),(float)(expire - current) / 1000);
		}
		else if(eff->eff_duration > 0.0)
		{
			mod->mod_vartable.SetFloat(CExoString("GetEffectRemainingDuration"),eff->eff_duration);
		}
	}
	if(!NWN_VirtualMachine->StackPushInteger(retVal))
	{
		return -638;
	}
	eff->dtor();
	return 0;
}

int __fastcall CNWVirtualMachineCommands__ExecuteCommandVersusEffect_Hook(CVirtualMachineCommands *vm_cmds, void*, int cmd, int args)
{
	Log(2,"o CNWVirtualMachineCommands__ExecuteCommandVersusEffect start\n");
	CGameEffect *eff;
	int arg1,arg2;
	if(!NWN_VirtualMachine->StackPopEngineStructure(0,(void **)&eff) || (args > 1 && !NWN_VirtualMachine->StackPopInteger(&arg1)) || (args > 2 && !NWN_VirtualMachine->StackPopInteger(&arg2)))
	{
		return -638;
	}
	if((cmd == 355 && arg1 > -1 && arg1 < 6) || (cmd == 356 && arg1 > -1 && arg1 <= NWN_Rules->m_nNumRaces))
	{
		int integer_index = 0;
		switch(eff->eff_type)
		{
		case EFFECT_TRUETYPE_INVISIBILITY:
		case EFFECT_TRUETYPE_SANCTUARY:
		case EFFECT_TRUETYPE_IMMUNITY:
		case EFFECT_TRUETYPE_CONCEALMENT:
			integer_index = 1;
			break;
		case EFFECT_TRUETYPE_ATTACK_INCREASE:
		case EFFECT_TRUETYPE_ATTACK_DECREASE:
		case EFFECT_TRUETYPE_AC_INCREASE:
		case EFFECT_TRUETYPE_AC_DECREASE:
		case EFFECT_TRUETYPE_SKILL_INCREASE:
		case EFFECT_TRUETYPE_SKILL_DECREASE:
		case EFFECT_TRUETYPE_DAMAGE_INCREASE:
		case EFFECT_TRUETYPE_DAMAGE_DECREASE:
			integer_index = 2;
			break;
		case EFFECT_TRUETYPE_DAMAGE_SHIELD:
			if(cmd==356) eff->SetInteger(6,1);
		case EFFECT_TRUETYPE_SAVING_THROW_INCREASE:
		case EFFECT_TRUETYPE_SAVING_THROW_DECREASE:
			integer_index = 3;
			break;
		}
		if(integer_index)
		{
			if(cmd == 356)//vs racial type
			{
				eff->SetInteger(integer_index,arg1);
			}
			else//if(cmd == 355) - vs alignment
			{
				eff->SetInteger(integer_index+1,arg1);
				eff->SetInteger(integer_index+2,arg2);
			}
		}
	}
	else if(cmd == 357)
	{
		CNWSModule *mod = NWN_AppManager->app_server->srv_internal->GetModule();
		if(mod && mod->mod_vartable.MatchIndex(CExoString("GetEffectEventEffect"),VARIABLE_TYPE_INT,0) != NULL && helper_effect != NULL)
		{
			Log(1,"NWNXPatch_Funcs DEBUG: func GetEffectEventEffect\n");
			if(!NWN_VirtualMachine->StackPushEngineStructure(0,helper_effect))
			{
				return -638;
			}
			eff->dtor();
			return 0;
		}
		if(mod && mod->mod_vartable.MatchIndex(CExoString("SetEffectTrueType"),VARIABLE_TYPE_INT,0) != NULL)
		{
			int nTrueType = mod->mod_vartable.GetInt(CExoString("SetEffectTrueType"));
			Log(1,"NWNXPatch_Funcs DEBUG: func SetEffectTrueType, nTrueType: %i\n",nTrueType);
			eff->eff_type = (unsigned short)nTrueType;
		}
		else if(mod && mod->mod_vartable.MatchIndex(CExoString("SetEffectSpellId"),VARIABLE_TYPE_INT,0) != NULL)
		{
			int nSpellId = mod->mod_vartable.GetInt(CExoString("SetEffectSpellId"));
			Log(1,"NWNXPatch_Funcs DEBUG: func SetEffectSpellId, nSpellId: %i\n",nSpellId);
			eff->eff_spellid = nSpellId;
		}
		else if(mod && mod->mod_vartable.MatchIndex(CExoString("SetEffectCasterLevel"),VARIABLE_TYPE_INT,0) != NULL)
		{
			int nCasterLevel = mod->mod_vartable.GetInt(CExoString("SetEffectCasterLevel"));
			Log(1,"NWNXPatch_Funcs DEBUG: func SetEffectCasterLevel, nCasterLevel: %i\n",nCasterLevel);
			eff->eff_casterlvl = nCasterLevel;
		}
		else if(mod && mod->mod_vartable.MatchIndex(CExoString("SetEffectIntegerNth"),VARIABLE_TYPE_INT,0) != NULL)
		{
			int nInteger = mod->mod_vartable.GetInt(CExoString("SetEffectIntegerNth"));
			int nValue = mod->mod_vartable.GetInt(CExoString("SetEffectIntegerVal"));
			Log(1,"NWNXPatch_Funcs DEBUG: func SetEffectInteger, nInteger: %i, nValue: %i\n",nInteger,nValue);
			eff->eff_integers[nInteger] = nValue;
		}
		else if(mod && mod->mod_vartable.MatchIndex(CExoString("SetEffectCreator"),VARIABLE_TYPE_OBJECT,0) != NULL)
		{
			uint32_t oCreator = mod->mod_vartable.GetObject(CExoString("SetEffectCreator"));
			Log(1,"NWNXPatch_Funcs DEBUG: func SetEffectCreator, oCreator: %x\n",oCreator);
			eff->eff_creator = oCreator;
		}
		else if(mod && mod->mod_vartable.MatchIndex(CExoString("GetEffect"),VARIABLE_TYPE_INT,0) != NULL && mod->mod_vartable.MatchIndex(CExoString("GetEffect"),VARIABLE_TYPE_OBJECT,0) != NULL)
		{
			unsigned long id = mod->mod_vartable.GetObject(CExoString("GetEffect"));
			unsigned int th = (unsigned int)mod->mod_vartable.GetInt(CExoString("GetEffect"));
			Log(1,"NWNXPatch_Funcs DEBUG: func GetEffect, oCreature: %x, nTh: %i\n",id,th);
			CNWSObject *obj = (CNWSObject*)NWN_AppManager->app_server->srv_internal->GetGameObject(id);
			if(obj)
			{
				if(th < obj->obj_effects_len)
				{
					CGameEffect* eEffect = *(obj->obj_effects+th);
					if(!NWN_VirtualMachine->StackPushEngineStructure(0,eEffect))
					{
						return -638;
					}
					eff->dtor();
					return 0;				
				}
				eff->eff_type = 0;
			}
		}	
	}
	if(!NWN_VirtualMachine->StackPushEngineStructure(0,eff))
	{
		return -638;
	}
	eff->dtor();
	return 0;
}

int __fastcall CNWVirtualMachineCommands__ExecuteCommandApplyEffectOnObject_Hook(CVirtualMachineCommands *, void*, int, int)
{
	Log(2,"o CNWVirtualMachineCommands__ExecuteCommandApplyEffectOnObject start\n");
	int32_t dur_type;
	CGameEffect *eff;
	uint32_t obj_id;
	float duration;
	if(!NWN_VirtualMachine->StackPopInteger(&dur_type) || !NWN_VirtualMachine->StackPopEngineStructure(0,(void **)&eff) || !NWN_VirtualMachine->StackPopObject(&obj_id) || !NWN_VirtualMachine->StackPopFloat(&duration))
	{
		return -639;
	}
	CNWSObject *target = (CNWSObject*)(NWN_AppManager->app_server->srv_internal->GetGameObject(obj_id));
	if(target)
	{
		int force_apply = 1;
		if(dur_type > 9) 
		{
			dur_type-= 10;
			force_apply = 0;
		}
		if(dur_type == DURATION_TYPE_INNATE || dur_type == DURATION_TYPE_EQUIPPED)
		{
			force_apply = 0;
		}
		else if(dur_type == DURATION_TYPE_TEMPORARY)
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
		//OnDamaged event
		if(target->obj_generic.obj_type2 == OBJECT_TYPE2_CREATURE && eff->eff_type == EFFECT_TRUETYPE_DAMAGE && !target->GetDead())
		{
			CNWSCreature *cre = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(obj_id);
			if(cre && cre->cre_is_pc)
			{
				cre->obj.obj_last_damager = eff->eff_creator;
				for(unsigned char x=0;x < 13;x++)
				{
					cre->obj.obj_last_damage[x] = eff->eff_integers[x];
				}
				cre->obj.obj_vartable.SetInt(CExoString("GetDamageDealtSpellId"),eff->eff_spellid,1);
				NWN_VirtualMachine->Runscript(&CExoString("70_mod_damaged"),cre->obj.obj_generic.obj_id);
			}
		}
		// If the second param is 0 effect handlers will not apply if the target is dead or dying.
        // If the third param is 0, it will be added to the object's effect list even if not successfully applied.
		target->ApplyEffect(eff, !force_apply, force_apply);
		target->obj_pending_effect_removal = 0;
	}
	else
	{
		eff->dtor();
	}
	return 0;
}

int __fastcall CNWVirtualMachineCommands__ExecuteCommandGetRacialType_Hook(CVirtualMachineCommands *, void*, int, int)
{
	Log(2,"o CNWVirtualMachineCommands__ExecuteCommandGetRacialType start\n");
	uint32_t obj_id;
	if(!NWN_VirtualMachine->StackPopObject(&obj_id))
	{
		return -639;
	}
	CNWSCreature *cre = (NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(obj_id));
	if(cre)
	{
		unsigned short racial_type = cre->cre_stats->cs_race;
		if(cre->obj.obj_vartable.MatchIndex(CExoString("RacialTypeOverride"),VARIABLE_TYPE_INT,0) != NULL)
		{
			racial_type = cre->obj.obj_vartable.GetInt(CExoString("RacialTypeOverride"));
		}
		if(NWN_VirtualMachine->StackPushInteger(racial_type))
		{
			return 0;
		}
	}
	return -638;
}

int __fastcall CNWSCreature__EventHandler_Hook(CNWSCreature *pThis, void*, int arg1, int arg2, void *arg3, int arg4, int arg5)
{
	Log(2,"o CNWSCreature__EventHandler start\n");
	if(arg1 == 19)//19 onhitcast spell, 27 boot pc, 5 apply effect, 14 remove effect, 4 remove from area, 9 play animation, 1 timed event, 20 broadcast aoo, 21 broadcast safe projectile, 8 spell impact, 10 signal event, 11 destroy object
	{
		int32_t spell_id = pThis->obj.obj_last_spell_id;
		uint32_t spell_target = pThis->obj.obj_last_spell_target;
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
	else if(arg1 == 15)//onattacked
	{
		CNWSCombatAttackData *data = (CNWSCombatAttackData*)arg3;
		if(data)
		{		
			pThis->obj.obj_vartable.SetInt(CExoString("AttackDeflected"),data->m_bAttackDeflected,1);
			pThis->obj.obj_vartable.SetInt(CExoString("AttackResult"),data->m_nAttackResult,1);
			pThis->obj.obj_vartable.SetInt(CExoString("AttackType"),data->m_nAttackType,1);
			pThis->obj.obj_vartable.SetInt(CExoString("Concealment"),data->m_nConcealment,1);
			pThis->obj.obj_vartable.SetInt(CExoString("CoupDeGrace"),data->m_bCoupDeGrace,1);
			pThis->obj.obj_vartable.SetInt(CExoString("CriticalThreat"),data->m_bCriticalThreat,1);
			pThis->obj.obj_vartable.SetInt(CExoString("DeathAttack"),data->m_bDeathAttack,1);
			pThis->obj.obj_vartable.SetInt(CExoString("KillingBlow"),data->m_bKillingBlow,1);
			pThis->obj.obj_vartable.SetInt(CExoString("MissedBy"),data->m_nMissedBy,1);
			pThis->obj.obj_vartable.SetInt(CExoString("SneakAttack"),data->m_bSneakAttack,1);
			pThis->obj.obj_vartable.SetInt(CExoString("ThreatRoll"),data->m_nThreatRoll,1);
			pThis->obj.obj_vartable.SetInt(CExoString("ToHitMod"),data->m_nToHitMod,1);
			pThis->obj.obj_vartable.SetInt(CExoString("ToHitRoll"),data->m_nToHitRoll,1);
			//filling up OnDamaged event values so the damage dealth will be readable in OnAttacked already
			pThis->obj.obj_last_damager = arg2;
			for(unsigned char x=0;x < 13;x++)
			{
				pThis->obj.obj_last_damage[x] = (short)data->m_nDamage[x];
			}
			if(pThis->cre_is_pc)
			{
				int retVal = CNWSCreature__EventHandler(pThis,NULL,arg1,arg2,arg3,arg4,arg5);
				NWN_VirtualMachine->Runscript(&CExoString("70_mod_attacked"),pThis->obj.obj_generic.obj_id);
				return retVal;
			}
		}	
	}
	else if(arg1 == 5 && pThis->cre_is_pc)//arg2 targetid arg3 effect
	{
		CGameEffect *eff = (CGameEffect*)arg3;
		if(eff && eff->eff_type == EFFECT_TRUETYPE_DAMAGE)
		{
			pThis->obj.obj_last_damager = arg2;
			for(unsigned char x=0;x < 13;x++)
			{
				pThis->obj.obj_last_damage[x] = eff->eff_integers[x];
			}
			pThis->obj.obj_vartable.SetInt(CExoString("GetDamageDealtSpellId"),-2,1);
			NWN_VirtualMachine->Runscript(&CExoString("70_mod_damaged"),pThis->obj.obj_generic.obj_id);
		}
	}
	return CNWSCreature__EventHandler(pThis,NULL,arg1,arg2,arg3,arg4,arg5);
}

int __fastcall CNWSCreature__StartBarter_Hook(CNWSCreature *pThis, void*, unsigned long targetID, unsigned long itemID, int arg1)
{
	Log(2,"o CNWSCreature__StartBarter start\n");
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
	Log(2,"o CNWSCreature__AddPickPocketAction start\n");
	if(pThis && pThis->cre_stats->GetCanUseSkill(SKILL_PICK_POCKET))
	{
		CNWSObject* object = (CNWSObject*)(NWN_AppManager->app_server->srv_internal->GetGameObject(targetID));
		if(object && object->obj_generic.obj_type2 == OBJECT_TYPE2_CREATURE)
		{
			pThis->cre_attempted_spell = targetID;
			if(NWN_VirtualMachine->Runscript(&CExoString("70_s2_pickpocket"),pThis->obj.obj_generic.obj_id,1))
			{
				return 1;
			}
		}
	}
	return CNWSCreature__AddPickPocketAction(pThis,NULL,targetID);
}

int __fastcall CNWSCreature__AddTauntActions_Hook(CNWSCreature *pThis, void*, unsigned long targetID)
{
	Log(2,"o CNWSCreature__AddTauntActions start\n");
	if(pThis && pThis->cre_stats->GetCanUseSkill(SKILL_TAUNT))
	{
		CNWSObject* object = (CNWSObject*)(NWN_AppManager->app_server->srv_internal->GetGameObject(targetID));
		if(object && object->obj_generic.obj_type2 == OBJECT_TYPE2_CREATURE)
		{
			pThis->cre_attempted_spell = targetID;
			if(NWN_VirtualMachine->Runscript(&CExoString("70_s2_taunt"),pThis->obj.obj_generic.obj_id,1))
			{
				return 1;
			}
		}
	}
	return CNWSCreature__AddTauntActions(pThis,NULL,targetID);
}

int __fastcall CNWSCreature__AddAnimalEmpathyAction_Hook(CNWSCreature *pThis, void*, unsigned long targetID)
{
	Log(2,"o CNWSCreature__AddAnimalEmpathyAction start\n");
	if(pThis && pThis->cre_stats->GetCanUseSkill(SKILL_ANIMAL_EMPATHY))
	{
		CNWSObject* object = (CNWSObject*)(NWN_AppManager->app_server->srv_internal->GetGameObject(targetID));
		if(object && object->obj_generic.obj_type2 == OBJECT_TYPE2_CREATURE)
		{
			pThis->cre_attempted_spell = targetID;
			if(NWN_VirtualMachine->Runscript(&CExoString("70_s2_empathy"),pThis->obj.obj_generic.obj_id,1))
			{
				return 1;
			}
		}
	}
	return CNWSCreature__AddAnimalEmpathyAction(pThis,NULL,targetID);
}

int __fastcall CNWSEffectListHandler__OnApplyDefensiveStance_Hook(CNWSEffectListHandler *pThis, void*, CNWSObject *obj, CGameEffect *eff, int n)
{
	Log(2,"o CNWSEffectListHandler__OnApplyDefensiveStance start\n");
	CNWSCreature * cre = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(obj->obj_generic.obj_id);
	if(cre != NULL && cre->cre_is_pc && cre->cre_mode_combat == 11)
	{
		cre->SetEffectSpellId(641);
		if(NWN_VirtualMachine->Runscript(&CExoString("70_s2_ddstance"),obj->obj_generic.obj_id,1) == 1)
		{
			for(unsigned int nEffect = 0;nEffect < cre->obj.obj_effects_len;nEffect++)
			{
				CGameEffect* eEffect = *(cre->obj.obj_effects+nEffect);
				if(eEffect->eff_spellid == 641)
				{
					eEffect->eff_id = eff->eff_id;
				}
			}
			return 0;
		}
	}
	return CNWSEffectListHandler__OnApplyDefensiveStance(pThis,NULL,obj,eff,n);
}

int __fastcall CNWSCreatureStats__GetSpellResistance_Hook(CNWSCreatureStats *pThis, void*)
{
	Log(2,"o CNWSCreatureStats__GetSpellResistance start\n");
	if(pThis != NULL && pThis->cs_original->obj.obj_vartable.MatchIndex(CExoString("GetSpellResistance"),VARIABLE_TYPE_INT,0))
	{
		return pThis->cs_original->obj.obj_vartable.GetInt(CExoString("GetSpellResistance"));
	}
	return CNWSCreatureStats__GetSpellResistance(pThis, NULL);
}

int __fastcall CNWSCreatureStats__GetFavoredEnemyBonus_Hook(CNWSCreatureStats *pThis, void*, CNWSCreature *cre)
{
	Log(2,"o CNWSCreatureStats__GetFavoredEnemyBonus start\n");
	int modifier = ((CNWSObject*)(pThis->cs_original))->obj_vartable.GetInt(CExoString("FE_MODIFIER"));
	CNWRace *cRace = &(NWN_Rules->m_lstRaces[cre->cre_stats->cs_race]);
	if(cRace && cRace->FavoredEnemyFeat > 0)
	{
		if(pThis->HasFeat(cRace->FavoredEnemyFeat))
		{
			return 1+(pThis->GetNumLevelsOfClass(pThis->GetFeatSourceClass(cRace->FavoredEnemyFeat)))/5+modifier;
		}
		return 0;
	}
	int RetVal = CNWSCreatureStats__GetFavoredEnemyBonus(pThis,NULL,cre);
	return RetVal > 0 ? RetVal+modifier : RetVal;
}

int __fastcall CNWSTrigger__GetCanFireTrapOnObject_Hook(CNWSTrigger *pThis, void*, unsigned long targetID, int arg1)
{
	Log(2,"o CNWSTrigger__GetCanFireTrapOnObject start\n");
	int retVal = CNWSTrigger__GetCanFireTrapOnObject(pThis,NULL,targetID,arg1);
	if(TrapImmunity && retVal && !pThis->obj.obj_vartable.GetInt(CExoString("DISALLOW_FLYING")))
	{
		CNWSObject* object = (CNWSObject*)(NWN_AppManager->app_server->srv_internal->GetGameObject(targetID));
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

void NWNXPatch_Funcs(CNWSScriptVarTable *pThis, int nFunc, char *Params)
{
	Log(1, "NWNXPatch_Funcs DEBUG: func %i, params %s\n",nFunc,Params);fflush(logFile);
	CExoString VarName = CExoString("NWNXPATCH_RESULT");
	int retVal = -1;
	if(nFunc == 1)//GetPlayerLanguage
	{
		unsigned long oID = OBJECT_INVALID;
		sscanf_s(Params,"%x",&oID);
		CNWSPlayer *player = NWN_AppManager->app_server->srv_internal->GetClientObjectByObjectId(oID);
		if(oID != OBJECT_INVALID && player)
		{
			retVal = NWN_AppManager->app_server->srv_internal->GetPlayerLanguage(oID);
		}
		else
		{
			fprintf(logFile, "ERROR: GetPlayerLanguage(%08X) used on wrong object type!\n",oID);
		}
		pThis->SetInt(VarName,retVal,0);
	}
	else if(nFunc == 2)//GetObjectById
	{
		unsigned long oID = OBJECT_INVALID;
		sscanf_s(Params,"%x",&oID);
		pThis->SetObject(VarName,oID);
	}
	else if(nFunc == 3)//PlayMovie
	{
		unsigned long oID = OBJECT_INVALID;
		sscanf_s(Params,"%x|%s",&oID,Params);
		CNWSPlayer *player = NWN_AppManager->app_server->srv_internal->GetClientObjectByObjectId(oID);
		if(oID != OBJECT_INVALID && player && Params)
		{
			unsigned char *pData;
			long unsigned int nSize;

			CNWMessage *message = new CNWMessage();
			message->CreateWriteMessage(80, -1, 1);
			message->WriteCExoString(Params,strlen(Params),32);
			message->GetWriteMessage((unsigned char **) &pData, (unsigned long *) &nSize);
			NWN_AppManager->app_server->srv_internal->srv_client_messages->SendServerToPlayerMessage(player->pl_id, 201, 1, pData, nSize);
			delete message;
		}
	}
	if(nFunc == 4)//BootPCWithMessage
	{
		unsigned long oID = OBJECT_INVALID;
		unsigned long nTlkEntry = 63227;
		sscanf_s(Params,"%x|%i",&oID,&nTlkEntry);
		CNWSPlayer *player = NWN_AppManager->app_server->srv_internal->GetClientObjectByObjectId(oID);
		if(oID != OBJECT_INVALID && player)
		{
			NWN_AppManager->app_server->srv_internal->srv_network->DisconnectPlayer(player->pl_id,nTlkEntry,1);
		}
		else
		{
			fprintf(logFile, "ERROR: BootPCWithMessage(%08X,%i) used on wrong object type!\n",oID,nTlkEntry);
		}
	}
	if(nFunc == 5)//GetPCBicFileName
	{
		unsigned long oID = OBJECT_INVALID;
		sscanf_s(Params,"%x",&oID);
		CNWSPlayer *player = NWN_AppManager->app_server->srv_internal->GetClientObjectByObjectId(oID);
		if(oID != OBJECT_INVALID && player)
		{
			CNWSScriptVarTable__SetString(pThis,NULL,VarName,CExoString(player->m_resFileName.resref));
		}
		else
		{
			fprintf(logFile, "ERROR: GetPCBicFileName(%08X) used on wrong object type!\n",oID);
		}
	}
	else if(nFunc == 6)//SetCanCastInPolymorph
	{
		unsigned long oID = OBJECT_INVALID, bAllowed = OBJECT_INVALID;
		sscanf_s(Params,"%x|%i",&oID,bAllowed);
		CNWSPlayer *player = NWN_AppManager->app_server->srv_internal->GetClientObjectByObjectId(oID);
		if(oID != OBJECT_INVALID && player && (bAllowed == 1 || bAllowed == 0))
		{
			unsigned char *pData;
			long unsigned int nSize;

			CNWMessage *message = new CNWMessage();
			message->CreateWriteMessage(80, -1, 1);
			message->WriteINT(bAllowed,32);
			message->GetWriteMessage((unsigned char **) &pData, (unsigned long *) &nSize);
			NWN_AppManager->app_server->srv_internal->srv_client_messages->SendServerToPlayerMessage(player->pl_id, 203, 1, pData, nSize);
			delete message;
		}
		else
		{
			fprintf(logFile, "ERROR: SetCanCastInPolymorph(%08X,%i) used with incorrect parameters!\n",oID,bAllowed);
		}
	}
	else if(nFunc == 7)//GetIsFeatGranted
	{
		unsigned long nClass = 255;
		unsigned long nFeat = OBJECT_INVALID;
		sscanf_s(Params,"%i|%i",&nClass,&nFeat);
		if(nClass < 255 && nFeat != OBJECT_INVALID)
		{
			CNWClass *cls = &(NWN_Rules->m_lstClasses[nClass]);
			if(cls)
			{
				unsigned char granted = 0;
				cls->IsGrantedFeat((unsigned short)nFeat,granted);
				retVal = granted == 255 ? 0 : granted;
			}
		}
		else
		{
			fprintf(logFile, "ERROR: GetIsFeatGranted(%i,%i) used with incorrect parameters!\n",nClass,nFeat);
		}
		pThis->SetInt(VarName,retVal,0);
	}
	else if(nFunc == 8)//HighlightObject
	{
		unsigned long oID = OBJECT_INVALID, oObject = OBJECT_INVALID, color = OBJECT_INVALID;
		sscanf_s(Params,"%x|%x|%i",&oID,&oObject,&color);						
		CNWSPlayer *player = NWN_AppManager->app_server->srv_internal->GetClientObjectByObjectId(oID);
		CGenericObject *obj = NWN_AppManager->app_server->srv_internal->GetGameObject(oObject);
		if(oID != OBJECT_INVALID && player && oObject != OBJECT_INVALID && obj && color != OBJECT_INVALID)
		{
			unsigned char *pData;
			long unsigned int nSize;

			CNWMessage *message = new CNWMessage();
			message->CreateWriteMessage(80, -1, 1);
			message->WriteOBJECTIDServer(oObject);
			message->WriteINT(color,32);
			message->GetWriteMessage((unsigned char **) &pData, (unsigned long *) &nSize);
			NWN_AppManager->app_server->srv_internal->srv_client_messages->SendServerToPlayerMessage(player->pl_id, 207, 1, pData, nSize);
			delete message;
		}
		else
		{
			fprintf(logFile, "ERROR: HighlightObject(%08X,%08X,%i) used with incorrect parameters!\n",oID,oObject,color);
		}
	}
	else if(nFunc == 9)//VerifyClientRunningNWNCX
	{
		unsigned long oID = OBJECT_INVALID;
		sscanf_s(Params,"%x",&oID);
		CNWSPlayer *player = NWN_AppManager->app_server->srv_internal->GetClientObjectByObjectId(oID);
		if(oID != OBJECT_INVALID && player)
		{
			char *var = new char[64];
			sprintf_s(var,64,"VERIFY_NWNCX_PATCH_%i",player->pl_id);
			CExoString VarName = CExoString(var);
			delete var;
			CNWSModule *mod = NWN_AppManager->app_server->srv_internal->GetModule();
			if(mod)
			{
				retVal = mod->mod_vartable.GetInt(VarName);
			}
		}
		pThis->SetInt(VarName,retVal,0);
	}
	else if(nFunc == 10)//UnhighlightObject
	{
		unsigned long oID = OBJECT_INVALID, oObject = OBJECT_INVALID;;
		sscanf_s(Params,"%x|%x",&oID,&oObject);						
		CNWSPlayer *player = NWN_AppManager->app_server->srv_internal->GetClientObjectByObjectId(oID);
		CGenericObject *obj = NWN_AppManager->app_server->srv_internal->GetGameObject(oObject);
		if(oID != OBJECT_INVALID && player && oObject != OBJECT_INVALID && obj)
		{
			unsigned char *pData;
			long unsigned int nSize;

			CNWMessage *message = new CNWMessage();
			message->CreateWriteMessage(80, -1, 1);
			message->WriteOBJECTIDServer(oObject);
			message->GetWriteMessage((unsigned char **) &pData, (unsigned long *) &nSize);
			NWN_AppManager->app_server->srv_internal->srv_client_messages->SendServerToPlayerMessage(player->pl_id, 207, 0, pData, nSize);
			delete message;
		}
		else
		{
			fprintf(logFile, "ERROR: UnhighlightObject(%08X,%08X) used with incorrect parameters!\n",oID,oObject);
		}
	}
	else if(nFunc == 11)//SetDisableObjectHighlight
	{
		unsigned long oID = OBJECT_INVALID, val = OBJECT_INVALID;
		sscanf_s(Params,"%x|%i",&oID,&val);						
		CNWSPlayer *player = NWN_AppManager->app_server->srv_internal->GetClientObjectByObjectId(oID);
		if(oID != OBJECT_INVALID && player && (val == 1 || val == 0))
		{
			NWN_AppManager->app_server->srv_internal->srv_client_messages->SendServerToPlayerMessage(player->pl_id, 207, val != 0 ? 2 : 3, 0, 0);
		}
		else
		{
			fprintf(logFile, "ERROR: SetDisableObjectHighlight(%08X,%i) used with incorrect parameters!\n",oID,val);
		}
	}
	else if(nFunc == 12)
	{
		pThis->SetInt(VarName,VERSION_MAJOR*100+VERSION_MINOR,0);
	}
	else if(nFunc == 13)//SetSpellValue
	{
		unsigned long oID = OBJECT_INVALID, spell_id = OBJECT_INVALID, spell_const = OBJECT_INVALID, spell_value = OBJECT_INVALID;
		sscanf_s(Params,"%x|%i|%i|%s",&oID,&spell_id,&spell_const,Params);
		if(spell_id != OBJECT_INVALID && spell_const < 255 && Params)
		{
			CNWSpell *spell = NWN_Rules->m_pSpellArray->GetSpell(spell_id);
			if(spell)
			{
				if((spell_const <= 53 || spell_const == 60) && spell_const > 0 && spell_const != 41 && spell_const != 42)
				{
					CNWSPlayer *player = NWN_AppManager->app_server->srv_internal->GetClientObjectByObjectId(oID);
					if(oID != OBJECT_INVALID && player)
					{
						unsigned char *pData;
						long unsigned int nSize;

						CNWMessage *message = new CNWMessage();
						message->CreateWriteMessage(80, -1, 1);
						message->WriteINT(spell_id,32);
						message->WriteCExoString(Params,strlen(Params),32);
						message->GetWriteMessage((unsigned char **) &pData, (unsigned long *) &nSize);
						NWN_AppManager->app_server->srv_internal->srv_client_messages->SendServerToPlayerMessage(player->pl_id, 208, (unsigned char)spell_const, pData, nSize);
					}
					else
					{
						fflush(logFile);
						sscanf_s(Params,"%i",&spell_value);
						switch(spell_const)
						{
						case 1: spell->m_strrefName = spell_value; return;
						case 2: spell->m_strrefDesc = spell_value; return;		
						case 4: spell->m_nSchool = (unsigned char)spell_value; return;
						case 5: spell->m_sRange = CExoString(Params); return;
						case 6: spell->m_sComponent = CExoString(Params); return;
						case 7: spell->m_nTargetType = (unsigned short)spell_value; return;
						case 8: spell->m_sImpactScript = CExoString(Params); return;
						case 9: spell->m_nBardLevel = (unsigned char)spell_value; return;
						case 10: spell->m_nClericLevel = (unsigned char)spell_value; return;
						case 11: spell->m_nDruidLevel = (unsigned char)spell_value; return;
						case 12: spell->m_nPaladinLevel = (unsigned char)spell_value; return;
						case 13: spell->m_nRangerLevel = (unsigned char)spell_value; return;
						case 14: spell->m_nSorcererLevel = (unsigned char)spell_value; return;
						case 15: spell->m_nWizardLevel = (unsigned char)spell_value; return;
						case 16: spell->m_nInnateLevel = (unsigned char)spell_value; return;
						case 17: spell->m_nConjureTime = spell_value; return;
						case 18: spell->m_nConjureAnimation = (unsigned short)spell_value; return;						
						case 25: spell->m_nCastAnimation = (unsigned short)spell_value; return;
						case 26: spell->m_nCastTime = spell_value; return;
						case 31: spell->m_bProjectileSpawn = spell_value; return;
						case 33: spell->m_nProjectileType = spell_value; return;
						case 34: spell->m_nProjectileSpawnPoint = (unsigned char)spell_value; return;
						case 36: spell->m_nProjectileOrientationType = (unsigned char)spell_value; return;
						case 37: spell->m_nImmunityType = (unsigned char)spell_value; return;
						case 38: spell->m_bImmunityItem = spell_value; return;
						case 39: spell->m_nTalentCategory = spell_value; return;
						case 40: spell->m_nTalentMaxCR = spell_value; return;
						//case 41: spell->m_pSubRadialSpell = spell_value; break;
						//case 42: spell->m_nSubRadialSpellCount = (unsigned char)spell_value; break;
						case 43: spell->m_bUseConcentration = spell_value; return;
						case 44: spell->m_nMasterSpell = spell_value; return;
						case 45: spell->m_nCounterSpell1 = spell_value; return;
						case 46: spell->m_nCounterSpell2 = spell_value; return;
						case 47: spell->m_nUserType = (unsigned char)spell_value; return;
						case 48: spell->m_bSpontaneouslyCast = spell_value; return;
						case 49: spell->m_nAllowedMetamagic = (unsigned char)spell_value; return;
						case 50: spell->m_nAltMessage = spell_value; return;
						case 51: spell->m_bHostile = spell_value; return;
						case 52: spell->m_nFeatId = spell_value; return;
						case 53: spell->m_bHasProjectile = spell_value; return;
						case 60: spell->Hidden = (unsigned char)spell_value; return;
						}
						CResRef resref;
						std::fill_n(resref.resref, 16, 0);
						sprintf_s(resref.resref,16,"%s",Params);
						switch(spell_const)
						{
						case 3: spell->m_resrefIcon = resref; return;
						case 19: spell->m_resrefConjureHeadVisual = resref; return;
						case 20: spell->m_resrefConjureHandVisual = resref; return;
						case 21: spell->m_resrefConjureGroundVisual = resref; return;
						case 22: spell->m_resrefConjureSoundMale = resref; return;
						case 23: spell->m_resrefConjureSoundFemale = resref; return;
						case 24: spell->m_resrefConjureSoundVFX = resref; return;
						case 27: spell->m_resrefCastHeadVisual = resref; return;
						case 28: spell->m_resrefCastHandVisual = resref; return;
						case 29: spell->m_resrefCastGroundVisual = resref; return;
						case 30: spell->m_resrefCastSound = resref; return;
						case 32: spell->m_resrefProjectile = resref; return;
						case 35: spell->m_resrefProjectileSound = resref; return;					
						}
					}
				}
				else
				{
					fprintf(logFile, "ERROR: SetSpellValue(%08X,%i,%i,%s) incorrect or unsupported spell constant!\n",oID,spell_id,spell_const,Params);
				}	
			}
			else
			{
				fprintf(logFile, "ERROR: SetSpellValue(%08X,%i,%i,%s) spell not valid!\n",oID,spell_id,spell_const,Params);
			}			
		}
		else
		{
			fprintf(logFile, "ERROR: SetSpellValue(%08X,%i,%i,%s) used with incorrect parameters!\n",oID,spell_id,spell_const,Params);
		}
	}
	else if(nFunc == 14)//RegisterEffectEvent
	{
		unsigned long effect_type = OBJECT_INVALID, PCOnly = OBJECT_INVALID;
		sscanf_s(Params,"%i|%i",&effect_type,&PCOnly);						
		if(effect_type != OBJECT_INVALID && PCOnly != OBJECT_INVALID)
		{	
			if(effects_2da)
			{
				if(effects_2da->m_nNumColumns >= 2 && effect_type <= effects_2da->m_nNumRows)
				{
					if(effects_2da->m_pArrayData[effect_type][1] != NULL && effects_2da->m_pArrayData[effect_type][2] != NULL)
					{
						effects_2da->m_pArrayData[effect_type][1].text = "1";
						effects_2da->m_pArrayData[effect_type][2].text = PCOnly ? "1" : "0";
					}
					else
					{
						fprintf(logFile, "ERROR: RegisterEffectEvent(%i,%i) unknown 2da error!\n",effect_type,PCOnly);
					}
				}
				else
				{
					fprintf(logFile, "ERROR: RegisterEffectEvent(%i,%i) effects.2da has wrong number of columns or rows!\n",effect_type,PCOnly);
				}
			}
			else
			{
				fprintf(logFile, "ERROR: RegisterEffectEvent(%i,%i) effects.2da is not initialized!\n",effect_type,PCOnly);
			}

		}
		else
		{
			fprintf(logFile, "ERROR: RegisterEffectEvent(%i,%i) used with incorrect parameters!\n",effect_type,PCOnly);
		}
	}
	else if(nFunc == 15)//UnregisterEffectEvent
	{
		unsigned long effect_type = OBJECT_INVALID;
		sscanf_s(Params,"%i",&effect_type);						
		if(effect_type != OBJECT_INVALID)
		{		
			if(effects_2da)
			{
				if(effects_2da->m_nNumColumns >= 2 && effect_type <= effects_2da->m_nNumRows)
				{
					if(effects_2da->m_pArrayData[effect_type][1] != NULL)
					{
						effects_2da->m_pArrayData[effect_type][1].text = "0";
					}
					else
					{
						fprintf(logFile, "ERROR: UnregisterEffectEvent(%i) unknown 2da error!\n",effect_type);
					}
				}
				else
				{
					fprintf(logFile, "ERROR: UnregisterEffectEvent(%i) effects.2da has wrong number of columns or rows!\n",effect_type);
				}
			}
			else
			{
				fprintf(logFile, "ERROR: UnregisterEffectEvent(%i) effects.2da is not initialized!\n",effect_type);
			}

		}
		else
		{
			fprintf(logFile, "ERROR: UnregisterEffectEvent(%i) used with incorrect parameters!\n",effect_type);
		}
	}
	else if(nFunc == 101)//GetNumAreas
	{
		CNWSModule *cModule = NWN_AppManager->app_server->srv_internal->GetModule();
		if(cModule)
		{
			retVal = cModule->mod_areas_len;
		}
		else
		{
			fprintf(logFile, "ERROR: GetNumAreas() unknown error!\n");
		}
		pThis->SetInt(VarName,retVal,0);
	}
	else if(nFunc == 102)//GetNthArea
	{
		unsigned long nTh = OBJECT_INVALID;
		sscanf_s(Params,"%i",&nTh);
		CNWSModule *cModule = NWN_AppManager->app_server->srv_internal->GetModule();
		if(cModule && nTh != OBJECT_INVALID && nTh < cModule->mod_areas_len)
		{
			nTh = cModule->mod_areas[nTh];
		}
		else
		{
			fprintf(logFile, "ERROR: GetNthArea(%i) invalid parameters!\n",nTh);fflush(logFile);
			nTh = OBJECT_INVALID;
		}
		pThis->SetObject(VarName,nTh);
	}
	else if(nFunc == 103)//GetNoRestFlag
	{
		unsigned long oID = OBJECT_INVALID;
		sscanf_s(Params,"%x",&oID);
		CNWSArea *area = NWN_AppManager->app_server->srv_internal->GetAreaByGameObjectID(oID);
		if(oID != OBJECT_INVALID && area)
		{
			retVal = area->NoRest;
		}
		else
		{
			fprintf(logFile, "ERROR: GetNoRestFlag(%08X) used on wrong object type!\n",oID);
		}
		pThis->SetInt(VarName,retVal,0);
	}
	else if(nFunc == 104)//SetNoRestFlag
	{
		unsigned long oID = OBJECT_INVALID, bNoRest = 255;
		sscanf_s(Params,"%x|%i",&oID,&bNoRest);
		CNWSArea *area = NWN_AppManager->app_server->srv_internal->GetAreaByGameObjectID(oID);
		if(oID != OBJECT_INVALID && area)
		{
			if(bNoRest == 1 || bNoRest == 0)
			{
				area->NoRest = bNoRest;
				uint32_t object;
				CNWSPlayer *player;
				for(unsigned int x=0;x < area->obj_list_len;x++)
				{
					object = area->obj_list[x];
					player = NWN_AppManager->app_server->srv_internal->GetClientObjectByObjectId(object);
					if(player)
					{
						unsigned char *pData;
						long unsigned int nSize;
						CNWMessage *message = new CNWMessage();
						message->CreateWriteMessage(80, -1, 1);
						message->WriteINT(bNoRest,32);
						message->GetWriteMessage((unsigned char **) &pData, (unsigned long *) &nSize);
						NWN_AppManager->app_server->srv_internal->srv_client_messages->SendServerToPlayerMessage(player->pl_id, 204, 0, pData, nSize);
						delete message;
					}
				}
			}
			else
			{
				fprintf(logFile, "ERROR: SetNoRestFlag(%08X,%i) used with incorrect parameters!\n",oID,bNoRest);
			}
		}
		else
		{
			fprintf(logFile, "ERROR: SetNoRestFlag(%08X,%i) used on wrong object type!\n",oID,bNoRest);
		}
	}
	else if(nFunc == 105)//GetSurfaceMaterial
	{
		unsigned long oID = OBJECT_INVALID;
		float x=0.0,y=0.0,z=0.0;
		sscanf_s(Params,"%x|%f|%f|%f",&oID,&x,&y,&z);
		CNWSArea *area = NWN_AppManager->app_server->srv_internal->GetAreaByGameObjectID(oID);
		if(oID != OBJECT_INVALID && area)
		{
			CNWTile *Tile = area->GetTile(x, y, (int)z);
			if(Tile)
			{
				int Tile_x=0, Tile_y=0;
				Tile->GetLocation(&Tile_x, &Tile_y);
				//x = x - (long double)Tile_x * 10.0;
				//y = y - (long double)Tile_y * 10.0;
				x = x - (float)Tile_x * (float)10.0;
				y = y - (float)Tile_y * (float)10.0;
				retVal = ((CNWSTile*)Tile)->GetSurfaceMaterial(x, y, z);
			}
			else
			{
				fprintf(logFile, "ERROR: GetSurfaceMaterial(%08X,%f,%f,%f) invalid position!\n",oID,x,y,z);
			}
		}
		else
		{
			fprintf(logFile, "ERROR: GetSurfaceMaterial(%08X,%f,%f,%f) must be called on area!\n",oID,x,y,z);
		}
		pThis->SetInt(VarName,retVal,0);
	}
	else if(nFunc == 106)//GetPvPSettings
	{
		unsigned long oID = OBJECT_INVALID;
		sscanf_s(Params,"%x",&oID);
		CNWSArea *area = NWN_AppManager->app_server->srv_internal->GetAreaByGameObjectID(oID);
		if(oID != OBJECT_INVALID && area)
		{
			retVal = area->are_pvp_settings;
		}
		else
		{
			fprintf(logFile, "ERROR: GetPvPSettings(%08X) used on wrong object type!\n",oID);
		}
		pThis->SetInt(VarName,retVal,0);
	}
	else if(nFunc == 107)//SetPvPSettings
	{
		unsigned long oID = OBJECT_INVALID;
		unsigned long pvp_settings = 255;
		sscanf_s(Params,"%x|%i",&oID,&pvp_settings);
		CNWSArea *area = NWN_AppManager->app_server->srv_internal->GetAreaByGameObjectID(oID);
		if(oID != OBJECT_INVALID && area)
		{
			if(pvp_settings < 255)
			{
				area->are_pvp_settings = (unsigned char)pvp_settings;
			}
			else
			{
				fprintf(logFile, "ERROR: SetPvPSettings(%08X,%i) used with incorrect parameters!\n",oID,pvp_settings);
			}
		}
		else
		{
			fprintf(logFile, "ERROR: SetPvPSettings(%08X,%i) used on wrong object type!\n",oID,pvp_settings);
		}
	}
	else if(nFunc == 108)//GetTileAnimLoop
	{
		unsigned long oID = OBJECT_INVALID, animloop = OBJECT_INVALID;
		float x=0.0,y=0.0,z=0.0;
		sscanf_s(Params,"%x|%f|%f|%f|%i",&oID,&x,&y,&z,&animloop);
		CNWSArea *area = NWN_AppManager->app_server->srv_internal->GetAreaByGameObjectID(oID);
		if(oID != OBJECT_INVALID && area)
		{
			if(animloop < 4 && animloop > 0)
			{
				CNWTile *Tile = area->GetTile(x, y, (int)z);
				if(Tile)
				{
					unsigned char a1,a2,a3;
					Tile->GetAnimLoop(&a1,&a2,&a3);
					switch(animloop)
					{
						case 1: retVal = a1; break;
						case 2: retVal = a2; break;
						case 3: retVal = a3; break;
					}
				}
				else
				{
					fprintf(logFile, "ERROR: GetTileAnimLoop(%08X,%f,%f,%f,%i) invalid position!\n",oID,x,y,z,animloop);
				}
			}
			else
			{
				fprintf(logFile, "ERROR: GetTileAnimLoop(%08X,%f,%f,%f,%i) invalid animloop number!\n",oID,x,y,z,animloop);
			}
		}
		else
		{
			fprintf(logFile, "ERROR: GetTileAnimLoop(%08X,%f,%f,%f,%i) must be called on area!\n",oID,x,y,z,animloop);
		}
		pThis->SetInt(VarName,retVal,0);
	}
	else if(nFunc == 109)//SetTileAnimLoop
	{
		unsigned long oID = OBJECT_INVALID, animloop = OBJECT_INVALID, animloop_val = OBJECT_INVALID;
		float x=0.0,y=0.0,z=0.0;
		sscanf_s(Params,"%x|%f|%f|%f|%i|%i",&oID,&x,&y,&z,&animloop,&animloop_val);
		CNWSArea *area = NWN_AppManager->app_server->srv_internal->GetAreaByGameObjectID(oID);
		if(oID != OBJECT_INVALID && area)
		{
			if(animloop < 4 && animloop > 0 && animloop_val < 2)
			{
				CNWTile *Tile = area->GetTile(x, y, (int)z);
				if(Tile)
				{
					unsigned char a1,a2,a3;
					Tile->GetAnimLoop(&a1,&a2,&a3);
					switch(animloop)
					{
						case 1: a1 = (unsigned char)animloop_val; break;
						case 2: a2 = (unsigned char)animloop_val; break;
						case 3: a3 = (unsigned char)animloop_val; break;
					}
					Tile->SetAnimLoop(a1,a2,a3);
					sprintf_s(Params,strlen(Params),"%f|%f|%f|%i|%i|%i",x,y,z,a1,a2,a3);
					CNWSPlayer *player;
					for(unsigned int x=0;x < area->obj_list_len;x++)
					{
						animloop = area->obj_list[x];
						player = NWN_AppManager->app_server->srv_internal->GetClientObjectByObjectId(animloop);
						if(player)
						{
							unsigned char *pData;
							long unsigned int nSize;
							CNWMessage *message = new CNWMessage();
							message->CreateWriteMessage(80, -1, 1);
							message->WriteCExoString(Params,strlen(Params),32);
							message->GetWriteMessage((unsigned char **) &pData, (unsigned long *) &nSize);
							NWN_AppManager->app_server->srv_internal->srv_client_messages->SendServerToPlayerMessage(player->pl_id, 202, 1, pData, nSize);
							delete message;
						}
					}
				}
				else
				{
					fprintf(logFile, "ERROR: SetTileAnimLoop(%08X,%f,%f,%f,%i,%i) invalid position!\n",oID,x,y,z,animloop);
				}
			}
			else
			{
				fprintf(logFile, "ERROR: SetTileAnimLoop(%08X,%f,%f,%f,%i,%i) invalid animloop number or value!\n",oID,x,y,z,animloop);
			}
		}
		else
		{
			fprintf(logFile, "ERROR: SetTileAnimLoop(%08X,%f,%f,%f,%i,%i) must be called on area!\n",oID,x,y,z,animloop);
		}
	}
	else if(nFunc == 110)//GetAreaWind
	{
		unsigned long oID = OBJECT_INVALID;
		sscanf_s(Params,"%x",&oID);
		CNWSArea *area = NWN_AppManager->app_server->srv_internal->GetAreaByGameObjectID(oID);
		if(oID != OBJECT_INVALID && area)
		{
			retVal = area->Wind;
		}
		else
		{
			fprintf(logFile, "ERROR: GetAreaWind(%08X) used on wrong object type!\n",oID);
		}
		pThis->SetInt(VarName,retVal,0);
	}
	else if(nFunc == 111)//SetAreaWind
	{
		unsigned long oID = OBJECT_INVALID, wind = OBJECT_INVALID;
		sscanf_s(Params,"%x|%i",&oID,&wind);
		CNWSArea *area = NWN_AppManager->app_server->srv_internal->GetAreaByGameObjectID(oID);
		if(oID != OBJECT_INVALID && area)
		{
			if(wind < 3)
			{
				area->Wind = (unsigned char) wind;
				uint32_t object;
				CNWSPlayer *player;
				for(unsigned int x=0;x < area->obj_list_len;x++)
				{
					object = area->obj_list[x];
					player = NWN_AppManager->app_server->srv_internal->GetClientObjectByObjectId(object);
					if(player)
					{
						unsigned char *pData;
						long unsigned int nSize;
						CNWMessage *message = new CNWMessage();
						message->CreateWriteMessage(80, -1, 1);
						message->WriteINT(wind,32);
						message->GetWriteMessage((unsigned char **) &pData, (unsigned long *) &nSize);
						NWN_AppManager->app_server->srv_internal->srv_client_messages->SendServerToPlayerMessage(player->pl_id, 204, 1, pData, nSize);
						delete message;
					}
				}
			}
			else
			{
				fprintf(logFile, "ERROR: SetAreaWind(%08X,%i) used with incorrect parameters!\n",oID,wind);
			}
		}
		else
		{
			fprintf(logFile, "ERROR: SetAreaWind(%08X,%i) used on wrong object type!\n",oID,wind);
		}
	}
	else if(nFunc == 112)//SetAreaDayTime
	{
		unsigned long oID = OBJECT_INVALID;
		int daytime = 255;
		sscanf_s(Params,"%x|%i",&oID,&daytime);
		CNWSArea *area = NWN_AppManager->app_server->srv_internal->GetAreaByGameObjectID(oID);
		if(oID != OBJECT_INVALID && area)
		{
			if(daytime < 4)
			{
				if(daytime == -1)
				{
					if(area->are_terrain & 512)
					{
						area->UseDayNightCycle = 1;
						area->are_terrain&= ~512;
						CNWSModule *mod = NWN_AppManager->app_server->srv_internal->GetModule();
						if(mod)
						{
							area->are_terrain&= ~1024;
							area->are_terrain&= ~2048;
							unsigned long hour = NWN_AppManager->app_server->GetWorldTimer()->GetWorldTimeHour();
							if(hour >= mod->m_nDawnHour && hour <= mod->m_nDuskHour)
							{
								area->IsNight = 0;
								if(hour == mod->m_nDawnHour) daytime = 1;
								else daytime = 0;
							}
							else
							{
								area->IsNight = 1;
								if(hour == mod->m_nDuskHour) daytime = 2;
								else daytime = 3;							
							}
						}
					}
					if(area->are_terrain & 1024)
					{
						area->IsNight = 1;
						area->are_terrain&= ~1024;
						daytime = 3;
					}
					else if(area->are_terrain & 2048)
					{
						area->IsNight = 0;
						area->are_terrain&= ~2048;
						daytime = 0;
					}					
				}
				else
				{
					if(!(area->are_terrain & 1024) && !(area->are_terrain & 2048))
					{
						if(area->IsNight) area->are_terrain|= 1024;
						else area->are_terrain|= 2048;					
					}
					if(area->UseDayNightCycle) 
					{
							area->are_terrain|= 512;
							area->UseDayNightCycle = 0;
					}
					area->IsNight = daytime > 1 ? 1 : 0;
				}
				uint32_t object;
				CNWSPlayer *player;
				for(unsigned int x=0;x < area->obj_list_len;x++)
				{
					object = area->obj_list[x];
					player = NWN_AppManager->app_server->srv_internal->GetClientObjectByObjectId(object);
					if(player)
					{
						unsigned char *pData;
						long unsigned int nSize;
						CNWMessage *message = new CNWMessage();
						message->CreateWriteMessage(80, -1, 1);
						message->WriteINT(daytime,32);
						message->GetWriteMessage((unsigned char **) &pData, (unsigned long *) &nSize);
						NWN_AppManager->app_server->srv_internal->srv_client_messages->SendServerToPlayerMessage(player->pl_id, 204, 2, pData, nSize);
						delete message;
					}
				}
			}
			else
			{
				fprintf(logFile, "ERROR: SetAreaDayTime(%08X,%i) used with incorrect parameters!\n",oID,daytime);
			}
		}
		else if(oID != OBJECT_INVALID)
		{
			CNWSPlayer *player = NWN_AppManager->app_server->srv_internal->GetClientObjectByObjectId(oID);
			if(player && daytime >= 0 && daytime <= 3)
			{
				unsigned char *pData;
				long unsigned int nSize;
				CNWMessage *message = new CNWMessage();
				message->CreateWriteMessage(80, -1, 1);
				message->WriteINT(daytime,32);
				message->GetWriteMessage((unsigned char **) &pData, (unsigned long *) &nSize);
				NWN_AppManager->app_server->srv_internal->srv_client_messages->SendServerToPlayerMessage(player->pl_id, 204, 2, pData, nSize);
				delete message;
			}
			else
			{
				fprintf(logFile, "ERROR: SetAreaDayTime(%08X,%i) used with incorrect parameters!\n",oID,daytime);
			}
		}
		else
		{
			fprintf(logFile, "ERROR: SetAreaDayTime(%08X,%i) used on wrong object type!\n",oID,daytime);
		}
	}
	else if(nFunc == 113)//GetAreaAmbientColor
	{
		unsigned long oID = OBJECT_INVALID, type = OBJECT_INVALID;
		sscanf_s(Params,"%x|%i",&oID,&type);
		CNWSArea *area = NWN_AppManager->app_server->srv_internal->GetAreaByGameObjectID(oID);
		if(oID != OBJECT_INVALID && area)
		{
			if(type == 1)
			{
				retVal = (unsigned short)(area->m_nSunAmbientColor & 0xFF00) | ((unsigned char)area->m_nSunAmbientColor << 16) | (area->m_nSunAmbientColor >> 16);
			}
			else if(type == 2)
			{
				retVal = (unsigned short)(area->m_nMoonAmbientColor & 0xFF00) | ((unsigned char)area->m_nMoonAmbientColor << 16) | (area->m_nMoonAmbientColor >> 16);
			}
			else
			{
				fprintf(logFile, "ERROR: GetAreaAmbientColor(%08X,%i) used with incorrect parameters!\n",oID,type);
			}
		}
		else
		{
			fprintf(logFile, "ERROR: GetAreaAmbientColor(%08X,%i) used on wrong object type!\n",oID,type);
		}
		pThis->SetInt(VarName,retVal,0);
	}
	else if(nFunc == 114)//SetAreaAmbientColor
	{
		unsigned long oID = OBJECT_INVALID, type = OBJECT_INVALID, color = OBJECT_INVALID;
		sscanf_s(Params,"%x|%i|%i",&oID,&type,&color);
		CNWSArea *area = NWN_AppManager->app_server->srv_internal->GetAreaByGameObjectID(oID);
		if(oID != OBJECT_INVALID && area)
		{			
			if(type >= 0 && type <= 2 && color != OBJECT_INVALID)
			{
				color = (unsigned short)(color & 0xFF00) | ((unsigned char)color << 16) | (color >> 16);			
				switch(type)
				{
				case 0:
					area->m_nMoonAmbientColor = color;
				case 1:
					area->m_nSunAmbientColor = color;
					break;
				case 2:
					area->m_nMoonAmbientColor = color;
					break;
				}
				uint32_t object;
				CNWSPlayer *player;
				for(unsigned int x=0;x < area->obj_list_len;x++)
				{
					object = area->obj_list[x];
					player = NWN_AppManager->app_server->srv_internal->GetClientObjectByObjectId(object);
					if(player)
					{
						unsigned char *pData;
						long unsigned int nSize;
						CNWMessage *message = new CNWMessage();
						message->CreateWriteMessage(80, -1, 1);
						message->WriteINT(type,32);
						message->WriteINT(color,32);
						message->GetWriteMessage((unsigned char **) &pData, (unsigned long *) &nSize);
						NWN_AppManager->app_server->srv_internal->srv_client_messages->SendServerToPlayerMessage(player->pl_id, 204, 3, pData, nSize);
						delete message;
					}
				}
			}
			else
			{
				fprintf(logFile, "ERROR: SetAreaAmbientColor(%08X,%i,%i) used with incorrect parameters!\n",oID,type,color);
			}
		}
		else
		{
			fprintf(logFile, "ERROR: SetAreaAmbientColor(%08X,%i,%i) used on wrong object type!\n",oID,type,color);
		}
	}
	else if(nFunc == 115)//GetAreaDiffuseColor
	{
		unsigned long oID = OBJECT_INVALID, type = OBJECT_INVALID;
		sscanf_s(Params,"%x|%i",&oID,&type);
		CNWSArea *area = NWN_AppManager->app_server->srv_internal->GetAreaByGameObjectID(oID);
		if(oID != OBJECT_INVALID && area)
		{
			if(type == 1)
			{
				retVal = (unsigned short)(area->m_nSunDiffuseColor & 0xFF00) | ((unsigned char)area->m_nSunDiffuseColor << 16) | (area->m_nSunDiffuseColor >> 16);
			}
			else if(type == 2)
			{
				retVal = (unsigned short)(area->m_nMoonDiffuseColor & 0xFF00) | ((unsigned char)area->m_nMoonDiffuseColor << 16) | (area->m_nMoonDiffuseColor >> 16);
			}
			else
			{
				fprintf(logFile, "ERROR: GetAreaDiffuseColor(%08X,%i) used with incorrect parameters!\n",oID,type);
			}
		}
		else
		{
			fprintf(logFile, "ERROR: GetAreaDiffuseColor(%08X,%i) used on wrong object type!\n",oID,type);
		}
		pThis->SetInt(VarName,retVal,0);
	}
	else if(nFunc == 116)//SetAreaDiffuseColor
	{
		unsigned long oID = OBJECT_INVALID, type = OBJECT_INVALID, color = OBJECT_INVALID;
		sscanf_s(Params,"%x|%i|%i",&oID,&type,&color);
		CNWSArea *area = NWN_AppManager->app_server->srv_internal->GetAreaByGameObjectID(oID);
		if(oID != OBJECT_INVALID && area)
		{			
			if(type >= 0 && type <= 2 && color != OBJECT_INVALID)
			{
				color = (unsigned short)(color & 0xFF00) | ((unsigned char)color << 16) | (color >> 16);			
				switch(type)
				{
				case 0:
					area->m_nMoonDiffuseColor = color;
				case 1:
					area->m_nSunDiffuseColor = color;
					break;
				case 2:
					area->m_nMoonDiffuseColor = color;
					break;
				}
				uint32_t object;
				CNWSPlayer *player;
				for(unsigned int x=0;x < area->obj_list_len;x++)
				{
					object = area->obj_list[x];
					player = NWN_AppManager->app_server->srv_internal->GetClientObjectByObjectId(object);
					if(player)
					{
						unsigned char *pData;
						long unsigned int nSize;
						CNWMessage *message = new CNWMessage();
						message->CreateWriteMessage(80, -1, 1);
						message->WriteINT(type,32);
						message->WriteINT(color,32);
						message->GetWriteMessage((unsigned char **) &pData, (unsigned long *) &nSize);
						NWN_AppManager->app_server->srv_internal->srv_client_messages->SendServerToPlayerMessage(player->pl_id, 204, 4, pData, nSize);
						delete message;
					}
				}
			}
			else
			{
				fprintf(logFile, "ERROR: SetAreaDiffuseColor(%08X,%i,%i) used with incorrect parameters!\n",oID,type,color);
			}
		}
		else
		{
			fprintf(logFile, "ERROR: SetAreaDiffuseColor(%08X,%i,%i) used on wrong object type!\n",oID,type,color);
		}
	}
	else if(nFunc == 117)//GetAreaShadowsEnabled
	{
		unsigned long oID = OBJECT_INVALID, type = OBJECT_INVALID;
		sscanf_s(Params,"%x|%i",&oID,&type);
		CNWSArea *area = NWN_AppManager->app_server->srv_internal->GetAreaByGameObjectID(oID);
		if(oID != OBJECT_INVALID && area)
		{
			if(type == 1)
			{
				retVal = area->m_bSunShadows;
			}
			else if(type == 2)
			{
				retVal = area->m_bMoonShadows;
			}
			else
			{
				fprintf(logFile, "ERROR: GetAreaShadowsEnabled(%08X,%i) used with incorrect parameters!\n",oID,type);
			}
		}
		else
		{
			fprintf(logFile, "ERROR: GetAreaShadowsEnabled(%08X,%i) used on wrong object type!\n",oID,type);
		}
		pThis->SetInt(VarName,retVal,0);
	}
	else if(nFunc == 118)//SetAreaShadowsEnabled
	{
		unsigned long oID = OBJECT_INVALID, type = OBJECT_INVALID, value = OBJECT_INVALID;
		sscanf_s(Params,"%x|%i|%i",&oID,&type,&value);
		CNWSArea *area = NWN_AppManager->app_server->srv_internal->GetAreaByGameObjectID(oID);
		if(oID != OBJECT_INVALID && area)
		{			
			if(type >= 0 && type <= 2 && value >= 0 && value <= 1)
			{
				switch(type)
				{
				case 0:
					area->m_bMoonShadows = value;
				case 1:
					area->m_bSunShadows = value;
					break;
				case 2:
					area->m_bMoonShadows = value;
					break;
				}
				uint32_t object;
				CNWSPlayer *player;
				for(unsigned int x=0;x < area->obj_list_len;x++)
				{
					object = area->obj_list[x];
					player = NWN_AppManager->app_server->srv_internal->GetClientObjectByObjectId(object);
					if(player)
					{
						unsigned char *pData;
						long unsigned int nSize;
						CNWMessage *message = new CNWMessage();
						message->CreateWriteMessage(80, -1, 1);
						message->WriteINT(type,32);
						message->WriteINT(value,32);
						message->GetWriteMessage((unsigned char **) &pData, (unsigned long *) &nSize);
						NWN_AppManager->app_server->srv_internal->srv_client_messages->SendServerToPlayerMessage(player->pl_id, 204, 5, pData, nSize);
						delete message;
					}
				}
			}
			else
			{
				fprintf(logFile, "ERROR: SetAreaShadowsEnabled(%08X,%i,%i) used with incorrect parameters!\n",oID,type,value);
			}
		}
		else
		{
			fprintf(logFile, "ERROR: SetAreaShadowsEnabled(%08X,%i,%i) used on wrong object type!\n",oID,type,value);
		}
	}
	else if(nFunc == 119)//GetAreaLightningChance
	{
		unsigned long oID = OBJECT_INVALID, type = OBJECT_INVALID;
		sscanf_s(Params,"%x|%i",&oID,&type);
		CNWSArea *area = NWN_AppManager->app_server->srv_internal->GetAreaByGameObjectID(oID);
		if(oID != OBJECT_INVALID && area)
		{
			retVal = area->ChanceOfLightning;
		}
		else
		{
			fprintf(logFile, "ERROR: GetAreaLightningChance(%08X,%i) used on wrong object type!\n",oID,type);
		}
		pThis->SetInt(VarName,retVal,0);
	}
	else if(nFunc == 120)//SetAreaLightningChance
	{
		unsigned long oID = OBJECT_INVALID, value = OBJECT_INVALID;
		sscanf_s(Params,"%x|%i",&oID,&value);
		CNWSArea *area = NWN_AppManager->app_server->srv_internal->GetAreaByGameObjectID(oID);
		if(oID != OBJECT_INVALID && area)
		{			
			if(value >= 0 && value <= 100)
			{
				area->ChanceOfLightning = (unsigned char) value;
				uint32_t object;
				CNWSPlayer *player;
				for(unsigned int x=0;x < area->obj_list_len;x++)
				{
					object = area->obj_list[x];
					player = NWN_AppManager->app_server->srv_internal->GetClientObjectByObjectId(object);
					if(player)
					{
						unsigned char *pData;
						long unsigned int nSize;
						CNWMessage *message = new CNWMessage();
						message->CreateWriteMessage(80, -1, 1);
						message->WriteINT(value,32);
						message->GetWriteMessage((unsigned char **) &pData, (unsigned long *) &nSize);
						NWN_AppManager->app_server->srv_internal->srv_client_messages->SendServerToPlayerMessage(player->pl_id, 204, 6, pData, nSize);
						delete message;
					}
				}
			}
			else
			{
				fprintf(logFile, "ERROR: SetAreaLightningChance(%08X,%i) used with incorrect parameters!\n",oID,value);
			}
		}
		else
		{
			fprintf(logFile, "ERROR: SetAreaLightningChance(%08X,%i) used on wrong object type!\n",oID,value);
		}
	}
	else if(nFunc == 121)//GetAreaSpotModifier
	{
		unsigned long oID = OBJECT_INVALID, type = OBJECT_INVALID;
		sscanf_s(Params,"%x|%i",&oID,&type);
		CNWSArea *area = NWN_AppManager->app_server->srv_internal->GetAreaByGameObjectID(oID);
		if(oID != OBJECT_INVALID && area)
		{
			retVal = area->m_nAreaSpotModifier;
		}
		else
		{
			fprintf(logFile, "ERROR: GetAreaSpotModifier(%08X,%i) used on wrong object type!\n",oID,type);
		}
		pThis->SetInt(VarName,retVal,0);
	}
	else if(nFunc == 122)//SetAreaSpotModifier
	{
		unsigned long oID = OBJECT_INVALID, value = OBJECT_INVALID;
		sscanf_s(Params,"%x|%i",&oID,&value);
		CNWSArea *area = NWN_AppManager->app_server->srv_internal->GetAreaByGameObjectID(oID);
		if(oID != OBJECT_INVALID && area)
		{			
			if(value != OBJECT_INVALID)
			{
				area->m_nAreaSpotModifier = value;
			}
			else
			{
				fprintf(logFile, "ERROR: SetAreaSpotModifier(%08X,%i) used with incorrect parameters!\n",oID,value);
			}
		}
		else
		{
			fprintf(logFile, "ERROR: SetAreaSpotModifier(%08X,%i) used on wrong object type!\n",oID,value);
		}
	}
	else if(nFunc == 123)//GetListenSpotModifier
	{
		unsigned long oID = OBJECT_INVALID, type = OBJECT_INVALID;
		sscanf_s(Params,"%x|%i",&oID,&type);
		CNWSArea *area = NWN_AppManager->app_server->srv_internal->GetAreaByGameObjectID(oID);
		if(oID != OBJECT_INVALID && area)
		{
			retVal = area->m_nAreaListenModifier;
		}
		else
		{
			fprintf(logFile, "ERROR: GetListenSpotModifier(%08X,%i) used on wrong object type!\n",oID,type);
		}
		pThis->SetInt(VarName,retVal,0);
	}
	else if(nFunc == 124)//SetListenSpotModifier
	{
		unsigned long oID = OBJECT_INVALID, value = OBJECT_INVALID;
		sscanf_s(Params,"%x|%i",&oID,&value);
		CNWSArea *area = NWN_AppManager->app_server->srv_internal->GetAreaByGameObjectID(oID);
		if(oID != OBJECT_INVALID && area)
		{			
			if(value != OBJECT_INVALID)
			{
				area->m_nAreaListenModifier = value;
			}
			else
			{
				fprintf(logFile, "ERROR: SetListenSpotModifier(%08X,%i) used with incorrect parameters!\n",oID,value);
			}
		}
		else
		{
			fprintf(logFile, "ERROR: SetListenSpotModifier(%08X,%i) used on wrong object type!\n",oID,value);
		}
	}
	else if(nFunc == 201)//DumpEffects
	{
		unsigned long oID = OBJECT_INVALID;
		sscanf_s(Params,"%x",&oID);
		CNWSObject *object = (CNWSObject*)NWN_AppManager->app_server->srv_internal->GetGameObject(oID);
		if(oID != OBJECT_INVALID && object && object->obj_generic.obj_type2 != OBJECT_TYPE2_MODULE && object->obj_generic.obj_type2 != OBJECT_TYPE2_AREA)
		{
			CGameEffect *eff;
			uint16_t subtype = 0;
			uint16_t durtype = 0;
			for(unsigned int i = 0;i < object->obj_effects_len;i++)
			{
				eff = object->obj_effects[i];
				subtype = eff->eff_dursubtype & SUBTYPE_MASK;
				durtype = eff->eff_dursubtype & DURATION_TYPE_MASK;
				fprintf(logFile, "effect #no %i: id: %i, type: %i, subtype: %i, durtype: %i, creator: %i, spellid: %i, casterlvl: %i, value0: %i, value1: %i, value2: %i, exposed: %i, skip %i, iconshown %i\n",i,eff,eff->eff_type,subtype,durtype,eff->eff_creator,eff->eff_spellid,eff->eff_casterlvl,eff->eff_integers[0],eff->eff_integers[1],eff->eff_integers[2],eff->eff_is_exposed,eff->eff_skiponload,eff->eff_is_iconshown);
			}
		}
		else
		{
			fprintf(logFile, "ERROR: DumpEffects(%08X) used on wrong object type!\n",oID);
		}
	}
	else if(nFunc == 202)//SetCurrentHitPoints
	{
		unsigned long oID = OBJECT_INVALID;
		int nHP = -1;
		sscanf_s(Params,"%x|%i",&oID,&nHP);
		CNWSObject *object = (CNWSObject*)NWN_AppManager->app_server->srv_internal->GetGameObject(oID);
		if(oID != OBJECT_INVALID && object && (object->obj_generic.obj_type2 == OBJECT_TYPE2_CREATURE ||object->obj_generic.obj_type2 == OBJECT_TYPE2_PLACEABLE || object->obj_generic.obj_type2 == OBJECT_TYPE2_DOOR))
		{
			if((short) nHP == nHP)
			{
				object->obj_hp_cur = (short) nHP;
			}
			else
			{
				object->obj_hp_cur = object->obj_hp_max;
				fprintf(logFile, "ERROR: SetCurrentHitPoints(%08X,%i) used with incorrect parameters!\n",oID,nHP);
			}
		}
		else
		{
			fprintf(logFile, "ERROR: SetCurrentHitPoints(%08X,%i) used on wrong object type!\n",oID,nHP);
		}
	}
	else if(nFunc == 203)//SetTag
	{
		unsigned long oID = OBJECT_INVALID;
		sscanf_s(Params,"%x|%s",&oID,Params);
		CGenericObject *object = NWN_AppManager->app_server->srv_internal->GetGameObject(oID);
		if(oID != OBJECT_INVALID && object && object->obj_type2 != OBJECT_TYPE2_MODULE && object->obj_type2 != OBJECT_TYPE2_AREA)
		{
			if(Params)
			{
				CNWSModule *module = NWN_AppManager->app_server->srv_internal->GetModule();
				if(object->obj_tag.text != NULL)
				{
					module->RemoveObjectFromLookupTable(object->obj_tag, oID);
				}
				module->AddObjectToLookupTable(CExoString(Params), oID);
				CNWSObject* obj = (CNWSObject*)object;
				obj->SetTag(CExoString(Params));//object->obj_tag = CExoString(Params);
			}
			else
			{
				fprintf(logFile, "ERROR: SetTag(%08X,%s) used with incorrect parameters!\n",oID,Params);
			}
		}
		else
		{
			fprintf(logFile, "ERROR: SetTag(%08X,%s) used on wrong object type!\n",oID,Params);
		}
	}
	else if(nFunc == 204)//SetTrapFlagged
	{
		unsigned long oID = OBJECT_INVALID, bFlagged = OBJECT_INVALID;
		sscanf_s(Params,"%x|%i",&oID,&bFlagged);
		CGenericObject *object = NWN_AppManager->app_server->srv_internal->GetGameObject(oID);
		if(oID != OBJECT_INVALID && object)
		{
			if(bFlagged == 1 || bFlagged == 0)
			{
				if(object->obj_type2 == OBJECT_TYPE2_TRIGGER)
				{
					CNWSTrigger *trg = NWN_AppManager->app_server->srv_internal->GetTriggerByGameObjectID(oID);
					if(trg)
					{
						trg->TrapFlagged = bFlagged;
					}
				}
				else if(object->obj_type2 == OBJECT_TYPE2_DOOR)
				{
					CNWSDoor *door = NWN_AppManager->app_server->srv_internal->GetDoorByGameObjectID(oID);
					if(door)
					{
						door->TrapFlagged = bFlagged;
					}
				}
				else if(object->obj_type2 == OBJECT_TYPE2_PLACEABLE)
				{
					CNWSPlaceable *plc = NWN_AppManager->app_server->srv_internal->GetPlaceableByGameObjectID(oID);
					if(plc)
					{
						plc->TrapFlagged = bFlagged;
					}
				}
				else
				{
					fprintf(logFile, "ERROR: SetTrapFlagged(%08X,%i) used on wrong object type!\n",oID,bFlagged);
				}
			}
			else
			{
				fprintf(logFile, "ERROR: SetTrapFlagged(%08X,%i) used with incorrect parameters!\n",oID,bFlagged);
			}
		}
		else
		{
			fprintf(logFile, "ERROR: SetTrapFlagged(%08X,%i) used on wrong object type!\n",oID,bFlagged);
		}
	}
	else if(nFunc == 205)//SetTrapCreator
	{
		unsigned long oID = OBJECT_INVALID, oCreator = OBJECT_INVALID;
		sscanf_s(Params,"%x|%x",&oID,&oCreator);
		CGenericObject *object = NWN_AppManager->app_server->srv_internal->GetGameObject(oID);
		if(oID != OBJECT_INVALID && object)
		{
			if(oCreator != OBJECT_INVALID)
			{
				if(object->obj_type2 == OBJECT_TYPE2_TRIGGER)
				{
					CNWSTrigger *trg = NWN_AppManager->app_server->srv_internal->GetTriggerByGameObjectID(oID);
					if(trg)
					{
						trg->CreatorId = oCreator;
					}
				}
				else if(object->obj_type2 == OBJECT_TYPE2_DOOR)
				{
					CNWSDoor *door = NWN_AppManager->app_server->srv_internal->GetDoorByGameObjectID(oID);
					if(door)
					{
						door->TrapCreator = oCreator;
					}
				}
				else if(object->obj_type2 == OBJECT_TYPE2_PLACEABLE)
				{
					CNWSPlaceable *plc = NWN_AppManager->app_server->srv_internal->GetPlaceableByGameObjectID(oID);
					if(plc)
					{
						plc->TrapCreator = oCreator;
					}
				}
				else
				{
					fprintf(logFile, "ERROR: SetTrapCreator(%08X,%08X) used on wrong object type!\n",oID,oCreator);
				}
			}
			else
			{
				fprintf(logFile, "ERROR: SetTrapCreator(%08X,%08X) used with incorrect parameters!\n",oID,oCreator);
			}
		}
		else
		{
			fprintf(logFile, "ERROR: SetTrapCreator(%08X,%08X) used on wrong object type!\n",oID,oCreator);
		}
	}
	else if(nFunc == 206)//GetConversation
	{
		unsigned long oID = OBJECT_INVALID;
		sscanf_s(Params,"%x",&oID);
		CGenericObject *object = NWN_AppManager->app_server->srv_internal->GetGameObject(oID);
		if(oID != OBJECT_INVALID && object)
		{
			if(object->obj_type2 == OBJECT_TYPE2_DOOR)
			{
				CNWSDoor *door = NWN_AppManager->app_server->srv_internal->GetDoorByGameObjectID(oID);
				if(door)
				{
					CNWSScriptVarTable__SetString(pThis,NULL,VarName,CExoString(door->door_conv));
				}
			}
			else if(object->obj_type2 == OBJECT_TYPE2_PLACEABLE)
			{
				CNWSPlaceable *plc = NWN_AppManager->app_server->srv_internal->GetPlaceableByGameObjectID(oID);
				if(plc)
				{
					CNWSScriptVarTable__SetString(pThis,NULL,VarName,CExoString(plc->plc_conv));
				}
			}
			else if(object->obj_type2 == OBJECT_TYPE2_CREATURE)
			{
				CNWSCreature *cre = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(oID);
				if(cre)
				{
					CNWSScriptVarTable__SetString(pThis,NULL,VarName,CExoString(cre->cre_stats->cs_conv));
				}
			}
			else
			{
				fprintf(logFile, "ERROR: GetConversation(%08X) used on wrong object type!\n",oID);
			}
		}
		else
		{
			fprintf(logFile, "ERROR: GetConversation(%08X) used with incorrect parameters!\n",oID);
		}
		pThis->SetInt(VarName,retVal,0);
	}
	else if(nFunc == 207)//SetConversation
	{
		unsigned long oID = OBJECT_INVALID;
		sscanf_s(Params,"%x|%s",&oID,Params);
		CGenericObject *object = NWN_AppManager->app_server->srv_internal->GetGameObject(oID);
		if(oID != OBJECT_INVALID && object && Params)
		{
			size_t len = strlen(Params); if(len > 15) len = 15;
			if(object->obj_type2 == OBJECT_TYPE2_DOOR)
			{
				CNWSDoor *door = NWN_AppManager->app_server->srv_internal->GetDoorByGameObjectID(oID);
				if(door)
				{
					memcpy(door->door_conv,Params,len);
				}
			}
			else if(object->obj_type2 == OBJECT_TYPE2_PLACEABLE)
			{
				CNWSPlaceable *plc = NWN_AppManager->app_server->srv_internal->GetPlaceableByGameObjectID(oID);
				if(plc)
				{
					memcpy(plc->plc_conv,Params,len);
				}
			}
			else if(object->obj_type2 == OBJECT_TYPE2_CREATURE)
			{
				CNWSCreature *cre = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(oID);
				if(cre)
				{
					memcpy(cre->cre_stats->cs_conv,Params,len);
				}
			}
			else
			{
				fprintf(logFile, "ERROR: SetConversation(%08X,%s) used on wrong object type!\n",oID,Params);
			}
		}
		else
		{
			fprintf(logFile, "ERROR: SetConversation(%08X,%s) used with incorrect parameters!\n",oID,Params);
		}
	}
	else if(nFunc == 301)//SetBaseItemType
	{
		unsigned long oID = OBJECT_INVALID;
		unsigned long nBT = OBJECT_INVALID;
		sscanf_s(Params,"%x|%i",&oID,&nBT);
		CNWSItem *item = NWN_AppManager->app_server->srv_internal->GetItemByGameObjectID(oID);
		if(oID != OBJECT_INVALID && item)
		{
			if(nBT != OBJECT_INVALID)
			{
				item->it_baseitemtype = nBT;
			}
			else
			{
				fprintf(logFile, "ERROR: SetBaseItemType(%08X,%i) used with incorrect parameters!\n",oID,nBT);
			}
		}
		else
		{
			fprintf(logFile, "ERROR: SetBaseItemType(%08X,%i) used on wrong object type!\n",oID,nBT);
		}
	}
	else if(nFunc == 302)//GetWeaponCriticalThreat
	{
		unsigned long oID = OBJECT_INVALID, oWeapon = OBJECT_INVALID;
		sscanf_s(Params,"%x|%x",&oID,&oWeapon);
		CNWSCreature *cre = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(oID);
		CNWSItem *weapon = NWN_AppManager->app_server->srv_internal->GetItemByGameObjectID(oWeapon);
		int bonus = 0, baseitem = -1, threat = 1;
		if(oWeapon != OBJECT_INVALID && weapon)
		{
			baseitem = weapon->it_baseitemtype;
		}
		if(baseitem > -1 && weapon->obj.obj_vartable.MatchIndex(CExoString("CriticalThreatOverride"),VARIABLE_TYPE_INT,0) != NULL)
		{
			retVal = weapon->obj.obj_vartable.GetInt(CExoString("CriticalThreatOverride"));
		}
		else if(baseitem == -1 && oID != OBJECT_INVALID && cre && cre->obj.obj_vartable.MatchIndex(CExoString("CriticalThreatOverride"),VARIABLE_TYPE_INT,0) != NULL)
		{
			retVal = cre->obj.obj_vartable.GetInt(CExoString("CriticalThreatOverride"));
		}
		else
		{
			if(baseitem > -1)
			{
				threat = NWN_Rules->m_pBaseItemArray->GetBaseItem(baseitem)->CritThreat;
				if(threat < 1) threat = 1;
				if(oID != OBJECT_INVALID && cre && cre->cre_stats->HasFeat(885) && cre->cre_stats->GetIsWeaponOfChoice(baseitem))//ki critical
				{	
					bonus+= 2;
				}
				if(weapon->GetPropertyByTypeExists(43,0))
				{
					bonus+= threat;
				}
			}
			if(oID != OBJECT_INVALID && cre && cre->cre_stats->GetWeaponImprovedCritical(baseitem > -1 ? weapon : NULL))
			{
				bonus+= threat;
			}
			retVal = 21-threat-bonus;		
		}
		pThis->SetInt(VarName,retVal,0);
	}
	else if(nFunc == 303)//GetWeaponCriticalMultiplier
	{
		unsigned long oID = OBJECT_INVALID, oWeapon = OBJECT_INVALID;
		sscanf_s(Params,"%x|%x",&oID,&oWeapon);
		CNWSCreature *cre = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(oID);
		CNWSItem *weapon = NWN_AppManager->app_server->srv_internal->GetItemByGameObjectID(oWeapon);

		int multiplier = 1, baseitem = -1;
		if(oWeapon != OBJECT_INVALID && weapon)
		{
			baseitem = weapon->it_baseitemtype;
		}
		if(baseitem > -1 && weapon->obj.obj_vartable.MatchIndex(CExoString("CriticalMultiplierOverride"),VARIABLE_TYPE_INT,0) != NULL)
		{
			retVal = weapon->obj.obj_vartable.GetInt(CExoString("CriticalMultiplierOverride"));
		}
		else if(baseitem == -1 && oID != OBJECT_INVALID && cre && cre->obj.obj_vartable.MatchIndex(CExoString("CriticalMultiplierOverride"),VARIABLE_TYPE_INT,0) != NULL)
		{
			retVal = cre->obj.obj_vartable.GetInt(CExoString("CriticalMultiplierOverride"));
		}
		else
		{
			if(baseitem > -1)
			{
				multiplier = NWN_Rules->m_pBaseItemArray->GetBaseItem(baseitem)->CritHitMult;
				if(multiplier < 1) multiplier = 1;
				if(oID != OBJECT_INVALID && cre && cre->cre_stats->HasFeat(883) && cre->cre_stats->GetIsWeaponOfChoice(baseitem))//increased multiplier
				{	
					multiplier++;
				}
			}
			retVal = multiplier;	
		}
		pThis->SetInt(VarName,retVal,0);
	}
	else if(nFunc == 304)//CheckItemFitsInventory
	{
		unsigned long oID = OBJECT_INVALID;
		unsigned long oItem = OBJECT_INVALID;
		sscanf_s(Params,"%x|%x",&oID,&oItem);
		CNWSCreature *cre = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(oID);
		CNWSItem *item = NWN_AppManager->app_server->srv_internal->GetItemByGameObjectID(oItem);
		if(oID != OBJECT_INVALID && cre && oItem != OBJECT_INVALID && item)
		{
			retVal = false;
			unsigned char a1 = 0,a2 = 0;
			while(a2 < 32)
			{
				if(cre->cre_inventory->CheckFit(item,a1,a2))
				{
					retVal = true;
					break;
				}
				if(++a1 > 8)
				{
					a1 = 0; a2++;
				}
			}
		}
		else
		{
			fprintf(logFile, "ERROR: CheckItemFitsInventory(%08X,%08X) used on wrong object type!\n",oID,oItem);
		}
		pThis->SetInt(VarName,retVal,0);
	}
	else if(nFunc == 401)//SetCreatureSize
	{
		unsigned long oID = OBJECT_INVALID, newSize = OBJECT_INVALID;
		sscanf_s(Params,"%x|%i",&oID,&newSize);
		CNWSCreature *cre = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(oID);
		if(oID != OBJECT_INVALID && cre)
		{
			if(newSize < 255)
			{
				cre->cre_size = (unsigned char)newSize;
			}
			else
			{
				fprintf(logFile, "ERROR: SetCreatureSize(%08X,%i) used with incorrect parameters!\n",oID,newSize);
			}
		}
		else
		{
			fprintf(logFile, "ERROR: SetCreatureSize(%08X,%i) used on wrong object type!\n",oID,newSize);
		}
	}
	else if(nFunc == 402)//GetEquipmentWeight
	{
		unsigned long oID = OBJECT_INVALID;
		sscanf_s(Params,"%x",&oID);
		CNWSCreature *cre = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(oID);
		if(oID != OBJECT_INVALID && cre)
		{
			retVal = cre->cre_total_weight;
		}
		else
		{
			fprintf(logFile, "ERROR: GetEquipmentWeight(%08X) used on wrong object type!\n",oID);
		}
		pThis->SetInt(VarName,retVal,0);
	}
	else if(nFunc == 403)//SetGold
	{
		unsigned long oID = OBJECT_INVALID, nGold = OBJECT_INVALID;
		sscanf_s(Params,"%x|%i",&oID,&nGold);
		CNWSCreature *cre = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(oID);
		if(oID != OBJECT_INVALID && cre)
		{
			if(nGold != OBJECT_INVALID)
			{
				cre->cre_gold = nGold;
			}
			else
			{
				fprintf(logFile, "ERROR: SetGold(%08X,%i) used with incorrect parameters!\n",oID,nGold);
			}
		}
		else
		{
			fprintf(logFile, "ERROR: SetGold(%08X,%i) used on wrong object type!\n",oID,nGold);
		}
	}
	else if(nFunc == 404)//GetSoundSetId
	{
		unsigned long oID = OBJECT_INVALID;
		sscanf_s(Params,"%x",&oID);
		CNWSCreature *cre = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(oID);
		if(oID != OBJECT_INVALID && cre)
		{
			retVal = cre->cre_soundset;
		}
		else
		{
			fprintf(logFile, "ERROR: GetSoundSetId(%08X) used on wrong object type!\n",oID);
		}
		pThis->SetInt(VarName,retVal,0);
	}
	else if(nFunc == 405)//SetSoundSetId
	{
		unsigned long oID = OBJECT_INVALID, nSoundSet = OBJECT_INVALID;
		sscanf_s(Params,"%x|%i",&oID,&nSoundSet);
		CNWSCreature *cre = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(oID);
		if(oID != OBJECT_INVALID && cre)
		{
			if(nSoundSet < 65535)
			{
				cre->cre_soundset = (uint16_t) nSoundSet;
			}
			else
			{
				fprintf(logFile, "ERROR: SetSoundSetId(%08X,%i) used with incorrect parameters!\n",oID,nSoundSet);
			}
		}
		else
		{
			fprintf(logFile, "ERROR: SetSoundSetId(%08X,%i) used on wrong object type!\n",oID,nSoundSet);
		}
	}
	else if(nFunc == 406)//JumpToLimbo
	{
		unsigned long oID = OBJECT_INVALID;
		sscanf_s(Params,"%x",&oID);
		CNWSCreature *cre = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(oID);
		if(oID != OBJECT_INVALID && cre && !cre->cre_is_pc)
		{
			CNWSModule *mod = NWN_AppManager->app_server->srv_internal->GetModule();
			if(mod)
			{
				cre->RemoveFromArea(0);
				mod->AddObjectToLimbo(oID);
			}
			else
			{
				fprintf(logFile, "ERROR: JumpToLimbo(%08X) unknown error!\n",oID);
			}
		}
		else
		{
			fprintf(logFile, "ERROR: JumpToLimbo(%08X) used on wrong object type!\n",oID);
		}
	}
	else if(nFunc == 407)//GetMovementRateFactor
	{
		float fSpeed = -1.0;
		unsigned long oID = OBJECT_INVALID, nType = OBJECT_INVALID;
		sscanf_s(Params,"%x|%i",&oID,&nType);
		CNWSCreature *cre = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(oID);
		if(oID != OBJECT_INVALID && cre)
		{
			if(nType == 1)
			{
				fSpeed = cre->m_fMovementRateFactor;
			}
			else
			{
				fSpeed = cre->GetMovementRateFactor();
			}
		}
		else
		{
			fprintf(logFile, "ERROR: GetMovementRateFactor(%08X,%i) used on wrong object type!\n",oID,nType);
		}
		pThis->SetFloat(VarName,fSpeed);
	}
	else if(nFunc == 408)//GetFlanked
	{
		unsigned long oID = OBJECT_INVALID, oTarget = OBJECT_INVALID;
		sscanf_s(Params,"%x|%x",&oID,&oTarget);
		CNWSCreature *cre = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(oID);
		if(oID != OBJECT_INVALID && cre)
		{
			CNWSCreature *target = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(oTarget);
			if(oTarget != OBJECT_INVALID && target)
			{
				retVal = target->GetFlanked(cre);
			}
			else
			{
				fprintf(logFile, "ERROR: GetFlanked(%08X,%08X) used with incorrect parameters!\n",oID,oTarget);
			}
		}
		else
		{
			fprintf(logFile, "ERROR: GetFlanked(%08X,%08X) used on wrong object type!\n",oID,oTarget);
		}
		pThis->SetInt(VarName,retVal,0);
	}
	else if(nFunc == 409)//GetIsFlatFooted
	{
		unsigned long oID = OBJECT_INVALID;
		sscanf_s(Params,"%x",&oID);
		CNWSCreature *cre = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(oID);
		if(oID != OBJECT_INVALID && cre)
		{
			retVal = cre->GetFlatFooted();
		}
		else
		{
			fprintf(logFile, "ERROR: GetIsFlatFooted(%08X) used on wrong object type!\n",oID);
		}
		pThis->SetInt(VarName,retVal,0);
	}
	else if(nFunc == 410)//GetEncumbranceState
	{
		unsigned long oID = OBJECT_INVALID;
		sscanf_s(Params,"%x",&oID);
		CNWSCreature *cre = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(oID);
		if(oID != OBJECT_INVALID && cre)
		{
			retVal = cre->cre_encumbrance_state;
		}
		else
		{
			fprintf(logFile, "ERROR: GetEncumbranceState(%08X) used on wrong object type!\n",oID);
		}
		pThis->SetInt(VarName,retVal,0);
	}
	else if(nFunc == 411)//SetMovementRate
	{
		unsigned long oID = OBJECT_INVALID, mov_rate = OBJECT_INVALID;
		sscanf_s(Params,"%x|%i",&oID,&mov_rate);
		CNWSCreature *cre = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(oID);
		if(oID != OBJECT_INVALID && cre)
		{
			if(mov_rate < 255)
			{
				cre->cre_stats->SetMovementRate((unsigned char)mov_rate);	
				if(mov_rate != 1 && cre->cre_stats->cs_original->m_nAIState == 0xFFFD)
				{
					cre->cre_stats->cs_original->m_nAIState = 0xFFFF;
				}
			}
			else
			{
				fprintf(logFile, "ERROR: SetMovementRate(%08X,%i) used with incorrect parameters!\n",oID,mov_rate);
			}
		}
		else
		{
			fprintf(logFile, "ERROR: SetMovementRate(%08X,%i) used on wrong object type!\n",oID,mov_rate);
		}
	}
	else if(nFunc == 412)//BroadcastAttackOfOpportunity
	{
		unsigned long oID = OBJECT_INVALID, oTarget = OBJECT_INVALID, bAllowRanged = OBJECT_INVALID;
		sscanf_s(Params,"%x|%x|%i",&oID,&oTarget,&bAllowRanged);
		CNWSCreature *cre = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(oID);
		if(oID != OBJECT_INVALID && cre)
		{
			CNWSCreature *target = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(oTarget);
			CNWBaseItem *baseitem = NULL;
			if(oTarget != OBJECT_INVALID && target)
			{			
				CNWSItem *weapon = target->cre_equipment->GetItemInSlot(16);
				if(bAllowRanged == 1 && weapon)
				{					
					baseitem = NWN_Rules->m_pBaseItemArray->GetBaseItem(weapon->it_baseitemtype);
					if(baseitem && baseitem->RangedWeapon > 0)
					{
						bAllowRanged = baseitem->RangedWeapon;
						baseitem->RangedWeapon = 0;
					}
				}
				cre->BroadcastAttackOfOpportunity(oTarget,0);
				if(bAllowRanged != OBJECT_INVALID && bAllowRanged > 1)
				{
					baseitem->RangedWeapon = (unsigned char) bAllowRanged;
				}
			}
			else
			{
				fprintf(logFile, "ERROR: BroadcastAttackOfOpportunity(%08X,%08X,%i) used with incorrect parameters!\n",oID,oTarget,bAllowRanged);
			}
		}
		else
		{
			fprintf(logFile, "ERROR: BroadcastAttackOfOpportunity(%08X,%08X,%i) used on wrong object type!\n",oID,oTarget,bAllowRanged);
		}
	}
	else if(nFunc == 415)//SetRacialType
	{
		unsigned long oID = OBJECT_INVALID, nRace = OBJECT_INVALID;
		sscanf_s(Params,"%x|%i",&oID,&nRace);
		CNWSCreature *cre = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(oID);
		if(oID != OBJECT_INVALID && cre)
		{
			if(nRace < 65535)
			{
				cre->cre_stats->cs_race = (unsigned short)nRace;
			}
			else
			{
				fprintf(logFile, "ERROR: SetRacialType(%08X,%i) used with incorrect parameters!\n",oID,nRace);
			}
		}
		else
		{
			fprintf(logFile, "ERROR: SetRacialType(%08X,%i) used on wrong object type!\n",oID,nRace);
		}
	}
	else if(nFunc == 416)//SetXP
	{
		unsigned long oID = OBJECT_INVALID, nXP = OBJECT_INVALID;
		sscanf_s(Params,"%x|%i",&oID,&nXP);
		CNWSCreature *cre = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(oID);
		if(oID != OBJECT_INVALID && cre)
		{
			if(nXP != OBJECT_INVALID)
			{
				cre->cre_stats->cs_xp = nXP;
			}
			else
			{
				fprintf(logFile, "ERROR: SetXP(%08X,%i) used with incorrect parameters!\n",oID,nXP);
			}
		}
		else
		{
			fprintf(logFile, "ERROR: SetXP(%08X,%i) used on wrong object type!\n",oID,nXP);
		}
	}
	else if(nFunc == 417)//SetAge
	{
		unsigned long oID = OBJECT_INVALID, nAge = OBJECT_INVALID;
		sscanf_s(Params,"%x|%i",&oID,&nAge);
		CNWSCreature *cre = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(oID);
		if(oID != OBJECT_INVALID && cre)
		{
			if(nAge != OBJECT_INVALID)
			{
				cre->cre_stats->cs_age = nAge;
			}
			else
			{
				fprintf(logFile, "ERROR: SetAge(%08X,%i) used with incorrect parameters!\n",oID,nAge);
			}
		}
		else
		{
			fprintf(logFile, "ERROR: SetAge(%08X,%i) used on wrong object type!\n",oID,nAge);
		}
	}
	else if(nFunc == 418)//SetGender
	{
		unsigned long oID = OBJECT_INVALID, nGender = OBJECT_INVALID;
		sscanf_s(Params,"%x|%i",&oID,&nGender);
		CNWSCreature *cre = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(oID);
		if(oID != OBJECT_INVALID && cre)
		{
			if(nGender < 255)
			{
				cre->cre_stats->cs_gender = nGender;		
			}
			else
			{
				fprintf(logFile, "ERROR: SetGender(%08X,%i) used with incorrect parameters!\n",oID,nGender);
			}
		}
		else
		{
			fprintf(logFile, "ERROR: SetGender(%08X,%i) used on wrong object type!\n",oID,nGender);
		}
	}
	else if(nFunc == 419)//SetAbilityScore
	{
		unsigned long oID = OBJECT_INVALID, nAbility = 255, nScore = 255;
		sscanf_s(Params,"%x|%i|%i",&oID,&nAbility,&nScore);
		CNWSCreature *cre = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(oID);
		if(oID != OBJECT_INVALID && cre)
		{
			if(nAbility < 6 && nScore > 2)
			{
				switch(nAbility)
				{
				case ABILITY_STRENGTH:
					cre->cre_stats->SetSTRBase((unsigned char)nScore);
					break;
				case ABILITY_CONSTITUTION:
					cre->cre_stats->SetCONBase((unsigned char)nScore,1);
					break;
				case ABILITY_DEXTERITY:
					cre->cre_stats->SetDEXBase((unsigned char)nScore);
					break;
				case ABILITY_WISDOM:
					cre->cre_stats->SetWISBase((unsigned char)nScore);
					break;
				case ABILITY_INTELLIGENCE:
					cre->cre_stats->SetINTBase((unsigned char)nScore);
					break;
				case ABILITY_CHARISMA:
					cre->cre_stats->SetCHABase((unsigned char)nScore);
					break;
				}
			}
			else
			{
				fprintf(logFile, "ERROR: SetAbilityScore(%08X,%i,%i) used with incorrect parameters!\n",oID,nAbility,nScore);
			}
		}
		else
		{
			fprintf(logFile, "ERROR: SetAbilityScore(%08X,%i,%i) used on wrong object type!\n",oID,nAbility,nScore);
		}
	}
	else if(nFunc == 422)//GetEncounterFrom
	{
		unsigned long oID = OBJECT_INVALID;
		sscanf_s(Params,"%x",&oID);
		CNWSCreature *cre = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(oID);
		if(oID != OBJECT_INVALID && cre)
		{
			retVal = cre->EncounterObject;
		}
		else
		{
			retVal = OBJECT_INVALID;
			fprintf(logFile, "ERROR: GetEncounterFrom(%08X) used on wrong object type!\n",oID);
		}
		pThis->SetObject(VarName,retVal);
	}
	else if(nFunc == 423)//GetBodyBag
	{
		unsigned long oID = OBJECT_INVALID;
		sscanf_s(Params,"%x",&oID);
		CNWSCreature *cre = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(oID);
		if(oID != OBJECT_INVALID && cre)
		{
			retVal = cre->cre_bodybag;
		}
		else
		{
			fprintf(logFile, "ERROR: GetBodyBag(%08X) used on wrong object type!\n",oID);
		}
		pThis->SetInt(VarName,retVal,0);
	}
	else if(nFunc == 424)//SetBodyBag
	{
		unsigned long oID = OBJECT_INVALID, BodyBag = 255;
		sscanf_s(Params,"%x|%i",&oID,&BodyBag);
		CNWSCreature *cre = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(oID);
		if(oID != OBJECT_INVALID && cre)
		{
			if(BodyBag < 255)
			{
				cre->cre_bodybag = (unsigned char)BodyBag;
			}
			else
			{
				fprintf(logFile, "ERROR: SetBodyBag(%08X,%i) used with incorrect parameters!\n",oID,BodyBag);
			}
		}
		else
		{
			fprintf(logFile, "ERROR: SetBodyBag(%08X,%i) used on wrong object type!\n",oID,BodyBag);
		}
	}
	else if(nFunc == 425)//GetFactionId
	{
		unsigned long oID = OBJECT_INVALID;
		sscanf_s(Params,"%x",&oID);
		CNWSCreature *cre = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(oID);
		if(oID != OBJECT_INVALID && cre)
		{
			retVal = cre->cre_stats->cs_faction_id;
		}
		else
		{
			fprintf(logFile, "ERROR: GetFactionId(%08X) used on wrong object type!\n",oID);
		}
		pThis->SetInt(VarName,retVal,0);
	}
	else if(nFunc == 426)//SetFactionId
	{
		unsigned long oID = OBJECT_INVALID, faction_id = OBJECT_INVALID;
		sscanf_s(Params,"%x|%i",&oID,&faction_id);
		CNWSCreature *cre = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(oID);
		if(oID != OBJECT_INVALID && cre)
		{
			if(faction_id != OBJECT_INVALID)
			{
				cre->cre_stats->cs_faction_id = faction_id;
			}
			else
			{
				fprintf(logFile, "ERROR: SetFactionId(%08X,%i) used with incorrect parameters!\n",oID,faction_id);
			}
		}
		else
		{
			fprintf(logFile, "ERROR: SetFactionId(%08X,%i) used on wrong object type!\n",oID,faction_id);
		}
	}
	else if(nFunc == 427)//PossessCreature
	{
		unsigned long oID = OBJECT_INVALID, oTarget = OBJECT_INVALID;
		sscanf_s(Params,"%x|%x",&oID,&oTarget);
		CNWSCreature *cre = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(oID);
		CNWSCreature *target = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(oTarget);
		if(oID != OBJECT_INVALID && cre && oTarget != OBJECT_INVALID && target)
		{
			if(cre->cre_is_pc && !target->cre_is_pc)
			{
				cre->field_B48 = oTarget;//workaround for possess
				target->cre_MasterID = oID;//workaround for unpossessing non-associate
				target->field_B2C = oID;//workaround for automatical unpossess when dead
				cre->PossessFamiliar();
			}
			else
			{
				fprintf(logFile, "ERROR: PossessCreature(%08X,%08X) used on wrong object type!\n",oID,oTarget);
			}
		}
		else
		{
			fprintf(logFile, "ERROR: PossessCreature(%08X,%08X) used with incorrect parameters!\n",oID,oTarget);
		}
	}
	else if(nFunc == 428)//SetMovementRateFactor
	{
		unsigned long oID = OBJECT_INVALID;
		float fSpeed = 0.0;
		sscanf_s(Params,"%x|%f",&oID,&fSpeed);
		CNWSCreature *cre = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(oID);
		if(oID != OBJECT_INVALID && cre)
		{
			if(fSpeed != 0.0)
			{
				cre->SetMovementRateFactor(fSpeed);
			}
			else
			{
				fprintf(logFile, "ERROR: SetMovementRateFactor(%08X,%f) used with incorrect parameters!\n",oID,fSpeed);
			}
		}
		else
		{
			fprintf(logFile, "ERROR: SetMovementRateFactor(%08X,%f) used on wrong object type!\n",oID,fSpeed);
		}
	}
	else if(nFunc == 429)//GetTotalDamageDealtByType
	{
		unsigned long oID = OBJECT_INVALID, type = OBJECT_INVALID;
		sscanf_s(Params,"%x|%i",&oID,&type);
		CNWSCreature *cre = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(oID);
		if(oID != OBJECT_INVALID && cre && Params && type != OBJECT_INVALID)
		{
			switch(type)
			{
			case 1:
				retVal = cre->cre_combat_round->GetAttack(cre->cre_combat_round->CurrentAttack)->m_nDamage[0];
			break;
			case 2:
				retVal = cre->cre_combat_round->GetAttack(cre->cre_combat_round->CurrentAttack)->m_nDamage[1];
			break;
			case 4:
				retVal = cre->cre_combat_round->GetAttack(cre->cre_combat_round->CurrentAttack)->m_nDamage[2];
			break;
			case 8:
				retVal = cre->cre_combat_round->GetAttack(cre->cre_combat_round->CurrentAttack)->m_nDamage[3];
			break;
			case 16:
				retVal = cre->cre_combat_round->GetAttack(cre->cre_combat_round->CurrentAttack)->m_nDamage[4];
			break;
			case 32:
				retVal = cre->cre_combat_round->GetAttack(cre->cre_combat_round->CurrentAttack)->m_nDamage[5];
			break;
			case 64:
				retVal = cre->cre_combat_round->GetAttack(cre->cre_combat_round->CurrentAttack)->m_nDamage[6];
			break;
			case 128:
				retVal = cre->cre_combat_round->GetAttack(cre->cre_combat_round->CurrentAttack)->m_nDamage[7];
			break;
			case 256:
				retVal = cre->cre_combat_round->GetAttack(cre->cre_combat_round->CurrentAttack)->m_nDamage[8];
			break;
			case 512:
				retVal = cre->cre_combat_round->GetAttack(cre->cre_combat_round->CurrentAttack)->m_nDamage[9];
			break;
			case 1024:
				retVal = cre->cre_combat_round->GetAttack(cre->cre_combat_round->CurrentAttack)->m_nDamage[10];
			break;
			case 2048:
				retVal = cre->cre_combat_round->GetAttack(cre->cre_combat_round->CurrentAttack)->m_nDamage[11];
			break;
			case 4096:
				retVal = cre->cre_combat_round->GetAttack(cre->cre_combat_round->CurrentAttack)->m_nDamage[12];
			break;
			default:
				fprintf(logFile, "ERROR: SetTotalDamageDealtByType(%08X,%i) used with incorrect parameters!\n",oID,type);
			break;
			}
		}
		else
		{
			fprintf(logFile, "ERROR: SetTotalDamageDealtByType(%08X,%i) used with incorrect parameters!\n",oID,type);
		}
		pThis->SetInt(VarName,retVal,0);
	}
	else if(nFunc == 430)//SetTotalDamageDealtByType
	{
		unsigned long oID = OBJECT_INVALID, type = OBJECT_INVALID, damage = OBJECT_INVALID;
		sscanf_s(Params,"%x|%i|%i",&oID,&type,&damage);
		CNWSCreature *cre = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(oID);
		if(oID != OBJECT_INVALID && cre && type != OBJECT_INVALID && damage != OBJECT_INVALID)
		{
			switch(type)
			{
			case 1:
				cre->cre_combat_round->GetAttack(cre->cre_combat_round->CurrentAttack)->m_nDamage[0] = (unsigned short)damage;
			break;
			case 2:
				cre->cre_combat_round->GetAttack(cre->cre_combat_round->CurrentAttack)->m_nDamage[1] = (unsigned short)damage;
			break;
			case 4:
				cre->cre_combat_round->GetAttack(cre->cre_combat_round->CurrentAttack)->m_nDamage[2] = (unsigned short)damage;
			break;
			case 8:
				cre->cre_combat_round->GetAttack(cre->cre_combat_round->CurrentAttack)->m_nDamage[3] = (unsigned short)damage;
			break;
			case 16:
				cre->cre_combat_round->GetAttack(cre->cre_combat_round->CurrentAttack)->m_nDamage[4] = (unsigned short)damage;
			break;
			case 32:
				cre->cre_combat_round->GetAttack(cre->cre_combat_round->CurrentAttack)->m_nDamage[5] = (unsigned short)damage;
			break;
			case 64:
				cre->cre_combat_round->GetAttack(cre->cre_combat_round->CurrentAttack)->m_nDamage[6] = (unsigned short)damage;
			break;
			case 128:
				cre->cre_combat_round->GetAttack(cre->cre_combat_round->CurrentAttack)->m_nDamage[7] = (unsigned short)damage;
			break;
			case 256:
				cre->cre_combat_round->GetAttack(cre->cre_combat_round->CurrentAttack)->m_nDamage[8] = (unsigned short)damage;
			break;
			case 512:
				cre->cre_combat_round->GetAttack(cre->cre_combat_round->CurrentAttack)->m_nDamage[9] = (unsigned short)damage;
			break;
			case 1024:
				cre->cre_combat_round->GetAttack(cre->cre_combat_round->CurrentAttack)->m_nDamage[10] = (unsigned short)damage;
			break;
			case 2048:
				cre->cre_combat_round->GetAttack(cre->cre_combat_round->CurrentAttack)->m_nDamage[11] = (unsigned short)damage;
			break;
			case 4096:
				cre->cre_combat_round->GetAttack(cre->cre_combat_round->CurrentAttack)->m_nDamage[12] = (unsigned short) damage;
			break;
			default:
				fprintf(logFile, "ERROR: SetTotalDamageDealtByType(%08X,%i,%i) used with incorrect parameters!\n",oID,type,damage);
			break;
			}
		}
		else
		{
			fprintf(logFile, "ERROR: SetTotalDamageDealtByType(%08X,%i,%i) used with incorrect parameters!\n",oID,type,damage);
		}
	}
	else if(nFunc == 431)//ActionUseSpecialAttack
	{
		unsigned long oID = OBJECT_INVALID, oTarget = OBJECT_INVALID, feat = OBJECT_INVALID;
		sscanf_s(Params,"%x|%x|%i",&oID,&oTarget,&feat);
		CNWSCreature *cre = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(oID);
		CNWSCreature *target = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(oTarget);
		if(oID != OBJECT_INVALID && cre && oTarget != OBJECT_INVALID && target && feat != OBJECT_INVALID)
		{
			cre->AddAttackActions(oTarget,0,0,0);
			cre->cre_combat_round->AddSpecialAttack((unsigned short)feat);
		}
		else
		{
			fprintf(logFile, "ERROR: ActionUseSpecialAttack(%08X,%08X,%i) used with incorrect parameters!\n",oID,oTarget,feat);
		}
	}
	else if(nFunc == 432)//SetAttackRoll
	{
		unsigned long oID = OBJECT_INVALID, nRoll = OBJECT_INVALID;
		sscanf_s(Params,"%x|%i",&oID,&nRoll);
		CNWSCreature *cre = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(oID);
		if(oID != OBJECT_INVALID && cre && nRoll != OBJECT_INVALID && nRoll > 0 && nRoll < 256)
		{
			cre->cre_combat_round->GetAttack(cre->cre_combat_round->CurrentAttack)->m_nToHitRoll = (char) nRoll;
		}
		else
		{
			fprintf(logFile, "ERROR: SetAttackRoll(%08X,%i) used with incorrect parameters!\n",oID,nRoll);
		}
	}
	else if(nFunc == 433)//SetAttackSneak
	{
		unsigned long oID = OBJECT_INVALID, nSneak = OBJECT_INVALID;
		sscanf_s(Params,"%x|%i",&oID,&nSneak);
		CNWSCreature *cre = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(oID);
		if(oID != OBJECT_INVALID && cre && nSneak != OBJECT_INVALID && nSneak >= 0 && nSneak <= 3)
		{
			CNWSCombatAttackData *attack_data = cre->cre_combat_round->GetAttack(cre->cre_combat_round->CurrentAttack); 
			if(nSneak == 0)
			{
				attack_data->m_bSneakAttack = false;
				attack_data->m_bDeathAttack = false;
			}
			else
			{
				if(nSneak > 1)
				{
					attack_data->m_bDeathAttack = true;
				}
				if(nSneak == 1 || nSneak == 3)
					attack_data->m_bSneakAttack = true;			
			}
		}
		else
		{
			fprintf(logFile, "ERROR: SetAttackSneak(%08X,%i) used with incorrect parameters!\n",oID,nSneak);
		}
	}
	else if(nFunc == 434)//SetAttackCriticalThreatRoll
	{
		unsigned long oID = OBJECT_INVALID, nRoll = OBJECT_INVALID;
		sscanf_s(Params,"%x|%i",&oID,&nRoll);
		CNWSCreature *cre = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(oID);
		if(oID != OBJECT_INVALID && cre && nRoll > 0 && nRoll < 256)
		{
			cre->cre_combat_round->GetAttack(cre->cre_combat_round->CurrentAttack)->m_nThreatRoll = (char) nRoll;
		}
		else
		{
			fprintf(logFile, "ERROR: SetAttackCriticalThreatRoll(%08X,%i) used with incorrect parameters!\n",oID,nRoll);
		}
	}
	else if(nFunc == 435)//SetAttackKillingBlow
	{
		unsigned long oID = OBJECT_INVALID, nKill = OBJECT_INVALID;
		sscanf_s(Params,"%x|%i",&oID,&nKill);
		CNWSCreature *cre = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(oID);
		if(oID != OBJECT_INVALID && cre && nKill >= 0 && nKill <= 1)
		{
			cre->cre_combat_round->GetAttack(cre->cre_combat_round->CurrentAttack)->m_bKillingBlow = nKill;
		}
		else
		{
			fprintf(logFile, "ERROR: SetAttackKillingBlow(%08X,%i) used with incorrect parameters!\n",oID,nKill);
		}
	}
	else if(nFunc == 436)//SetAttackCoupeDeGrace
	{
		unsigned long oID = OBJECT_INVALID, nValue = OBJECT_INVALID;
		sscanf_s(Params,"%x|%i",&oID,&nValue);
		CNWSCreature *cre = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(oID);
		if(oID != OBJECT_INVALID && cre && nValue >= 0 && nValue <= 1)
		{
			cre->cre_combat_round->GetAttack(cre->cre_combat_round->CurrentAttack)->m_bCoupDeGrace = nValue;
			cre->cre_combat_round->GetAttack(cre->cre_combat_round->CurrentAttack)->m_bKillingBlow = 1;
		}
		else
		{
			fprintf(logFile, "ERROR: SetAttackCoupeDeGrace(%08X,%i) used with incorrect parameters!\n",oID,nValue);
		}
	}
	else if(nFunc == 437)//SetAttackResult todo copy to server
	{
		unsigned long oID = OBJECT_INVALID, nValue = OBJECT_INVALID;
		sscanf_s(Params,"%x|%i",&oID,&nValue);
		CNWSCreature *cre = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(oID);
		if(oID != OBJECT_INVALID && cre && nValue >= 0 && nValue <= 1)
		{
			cre->cre_combat_round->GetAttack(cre->cre_combat_round->CurrentAttack)->m_nAttackResult = (unsigned char)nValue;
		}
	}
	else if(nFunc == 438)//GetStartingPackage
	{
		unsigned long oID = OBJECT_INVALID;
		sscanf_s(Params,"%x",&oID);
		CNWSCreature *cre = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(oID);
		if(oID != OBJECT_INVALID && cre)
		{
			retVal = cre->cre_stats->cs_starting_package;
		}
		else
		{
			fprintf(logFile, "ERROR: GetStartingPackage(%08X) used on wrong object type!\n",oID);
		}
		pThis->SetInt(VarName,retVal,0);
	}
	else if(nFunc == 439)//SetStartingPackage
	{
		unsigned long oID = OBJECT_INVALID, package = OBJECT_INVALID;
		sscanf_s(Params,"%x|%i",&oID,&package);
		CNWSCreature *cre = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(oID);
		if(oID != OBJECT_INVALID && cre)
		{
			if(package <= 255)
			{
				cre->cre_stats->cs_starting_package = (unsigned char)package;
			}
			else
			{
				fprintf(logFile, "ERROR: SetStartingPackage(%08X,%i) used with incorrect parameters!\n",oID,package);
			}
		}
		else
		{
			fprintf(logFile, "ERROR: SetStartingPackage(%08X,%i) used on wrong object type!\n",oID,package);
		}
	}
	else if(nFunc == 440)//TakeItemFromCreature
	{
		unsigned long oID = OBJECT_INVALID, oItem = OBJECT_INVALID;
		sscanf_s(Params,"%x|%x",&oID,&oItem);
		CNWSCreature *cre = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(oID);
		CNWSItem *item = NWN_AppManager->app_server->srv_internal->GetItemByGameObjectID(oItem);
		if(oID != OBJECT_INVALID && cre && oItem != OBJECT_INVALID && item)
		{
			cre->RemoveItem(item,1,0,0,1);				
		}
		else
		{
			fprintf(logFile, "ERROR: TakeItemFromCreature(%08X,%08X) used with incorrect parameters!\n",oID,oItem);
		}
	}
	else if(nFunc == 441)//GetBaseAC
	{
		unsigned long oID = OBJECT_INVALID, nType = OBJECT_INVALID;
		sscanf_s(Params,"%x|%i",&oID,&nType);
		CNWSCreature *cre = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(oID);
		if(oID != OBJECT_INVALID && cre && nType > 0 && nType < 4)
		{
			switch(nType)
			{
			case AC_NATURAL_BONUS:
				retVal = cre->cre_stats->cs_ac_natural_base;
				break;
			case AC_ARMOUR_ENCHANTMENT_BONUS:
				retVal = cre->cre_stats->cs_ac_armour_base;
				break;
			case AC_SHIELD_ENCHANTMENT_BONUS:
				retVal = cre->cre_stats->cs_ac_shield_base;
				break;
			}
		}
		else
		{
			fprintf(logFile, "ERROR: GetBaseAC(%08X,%i) used with incorrect parameters!\n",oID,nType);
		}
		pThis->SetInt(VarName,retVal,0);
	}
	else if(nFunc == 442)//SetBaseAC
	{
		unsigned long oID = OBJECT_INVALID, nType = OBJECT_INVALID;
		int nAC = 255;
		sscanf_s(Params,"%x|%i|%i",&oID,&nType,&nAC);
		CNWSCreature *cre = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(oID);
		if(oID != OBJECT_INVALID && cre && nType > 0 && nType < 4 && nAC > -127 && nAC < 127)
		{
			switch(nType)
			{
			case AC_NATURAL_BONUS:
				cre->cre_stats->cs_ac_natural_base = (char)nAC;
				break;
			case AC_ARMOUR_ENCHANTMENT_BONUS:
				cre->cre_stats->cs_ac_armour_base = (char)nAC;
				break;
			case AC_SHIELD_ENCHANTMENT_BONUS:
				cre->cre_stats->cs_ac_shield_base = (char)nAC;
				break;
			}
		}
		else
		{
			fprintf(logFile, "ERROR: SetBaseAC(%08X,%i,%i) used with incorrect parameters!\n",oID,nType,nAC);
		}
	}
	else if(nFunc == 443)//AddFeat
	{
		unsigned long oID = OBJECT_INVALID, nFeat = OBJECT_INVALID, nLevel = OBJECT_INVALID;
		sscanf_s(Params,"%x|%i|%i",&oID,&nFeat,&nLevel);
		CNWSCreature *cre = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(oID);
		if(oID != OBJECT_INVALID && cre && nFeat < 65535 && (!nLevel || nLevel <= cre->cre_stats->GetLevel(0)))
		{
			if(nLevel != 0)
			{
				CNWLevelStats *lvstats = (CNWLevelStats*)(CExoArrayList_ptr_get(&(cre->cre_stats->cs_levelstat), nLevel-1));
				if(lvstats)
				{
					lvstats->AddFeat((unsigned short)nFeat);
				}				
			}
			cre->cre_stats->AddFeat((unsigned short)nFeat);
		}
		else
		{
			fprintf(logFile, "ERROR: AddFeat(%08X,%i,%i) used with incorrect parameters!\n",oID,nFeat,nLevel);
		}
	}
	else if(nFunc == 444)//RemoveFeat
	{
		unsigned long oID = OBJECT_INVALID, nFeat = OBJECT_INVALID, bRemoveFromLevel = OBJECT_INVALID;
		sscanf_s(Params,"%x|%i|%i",&oID,&nFeat,&bRemoveFromLevel);
		CNWSCreature *cre = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(oID);
		if(oID != OBJECT_INVALID && cre && nFeat < 65535)
		{
			if(bRemoveFromLevel == 1)
			{
				int nPos = CExoArrayList_uint16_contains(&cre->cre_stats->cs_feats, (unsigned short)nFeat);
				if(nPos > 0) 
				{
					CExoArrayList_uint16_delfeatindex(&cre->cre_stats->cs_feats, nPos);
				}		
			}
			cre->cre_stats->RemoveFeat((unsigned short)nFeat);
		}
		else
		{
			fprintf(logFile, "ERROR: RemoveFeat(%08X,%i,%i) used with incorrect parameters!\n",oID,nFeat,bRemoveFromLevel);
		}
	}
	else if(nFunc == 501)//GetKnowsSpell
	{
		unsigned long oID = OBJECT_INVALID, cls_id = CLASS_TYPE_INVALID, spell_id = OBJECT_INVALID;
		sscanf_s(Params,"%x|%i|%i",&oID,&cls_id,&spell_id);
		CNWSCreature *cre = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(oID);
		if(oID != OBJECT_INVALID && cre)
		{
			if(cls_id != CLASS_TYPE_INVALID && spell_id != OBJECT_INVALID)
			{
				unsigned char spell_lvl = NWN_Rules->m_pSpellArray->GetSpell(spell_id)->GetSpellLevel((unsigned char)cls_id);
				if(spell_lvl < 10)
				{
					unsigned char cls_pos = 0;
					for(;cls_pos < cre->cre_stats->cs_classes_len;cls_pos++)
					{
						if(cre->cre_stats->cs_classes[cls_pos].cl_class == cls_id)
						{
							break;
						}
					}
					if(cls_pos < cre->cre_stats->cs_classes_len)
					{
						retVal = 0;
						int spell = cre->cre_stats->GetKnownSpell(cls_pos,spell_lvl,0);
						for(unsigned char x=1;spell != -1;x++)
						{
							if(spell == spell_id)
							{
								retVal = 1;
								break;
							}
							spell = cre->cre_stats->GetKnownSpell(cls_pos,spell_lvl,x);
						}
					}
					else
					{
						fprintf(logFile, "ERROR: GetKnowsSpell(%08X,%i,%i) creature doesn't have this class!\n",oID,cls_id,spell_id);
					}
				}
				else
				{
					fprintf(logFile, "ERROR: GetKnowsSpell(%08X,%i,%i) not a spell of this class!\n",oID,cls_id,spell_id);
				}
			}
			else
			{
				fprintf(logFile, "ERROR: GetKnowsSpell(%08X,%i,%i) used with incorrect parameters!\n",oID,cls_id,spell_id);
			}
		}
		else
		{
			fprintf(logFile, "ERROR: GetKnowsSpell(%08X,%i,%i) used on wrong object type!\n",oID,cls_id,spell_id);
		}
		pThis->SetInt(VarName,retVal,0);
	}
	if(nFunc == 502)//AddKnownSpell
	{
		unsigned long oID = OBJECT_INVALID, spell_id = OBJECT_INVALID, cls_id = CLASS_TYPE_INVALID, ignore_limit = 0;
		sscanf_s(Params,"%x|%i|%i|%i",&oID,&cls_id,&spell_id,&ignore_limit);
		CNWSCreature *cre = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(oID);
		if(oID != OBJECT_INVALID && cre)
		{
			if(cls_id != CLASS_TYPE_INVALID && spell_id != OBJECT_INVALID)
			{
				unsigned char spell_lvl = NWN_Rules->m_pSpellArray->GetSpell(spell_id)->GetSpellLevel((unsigned char)cls_id);
				if(spell_lvl < 10)
				{
					unsigned char cls_pos = 0;
					for(;cls_pos < cre->cre_stats->cs_classes_len;cls_pos++)
					{
						if(cre->cre_stats->cs_classes[cls_pos].cl_class == (unsigned char)cls_id)
						{
							break;
						}
					}
					if(cls_pos < cre->cre_stats->cs_classes_len)
					{
						int spell = cre->cre_stats->GetKnownSpell(cls_pos,spell_lvl,0);
						for(unsigned char x=1;spell != -1;x++)
						{
							if(spell == spell_id)
							{
								cls_pos = 255;
								break;
							}
							spell = cre->cre_stats->GetKnownSpell(cls_pos,spell_lvl,x);
						}
						if(cls_pos != 255)
						{
							unsigned char backup = cls_cast_type[(unsigned char)cls_id];
							if(ignore_limit && (backup & CAST_TYPE_SPONTANEOUS))
							{
								cls_cast_type[(unsigned char)cls_id] = backup^CAST_TYPE_SPONTANEOUS;//small engine hack to ignore limit of number known spells left
							}
							cre->cre_stats->AddKnownSpell(cls_pos,spell_id);
							if(ignore_limit)
							{
								cls_cast_type[(unsigned char)cls_id] = backup;
							}
						}
						else
						{
							fprintf(logFile, "ERROR: AddKnownSpell(%08X,%i,%i,%i) creature already knows this spell!\n",oID,cls_id,spell_id,ignore_limit);
						}
					}
					else
					{
						fprintf(logFile, "ERROR: AddKnownSpell(%08X,%i,%i,%i) creature doesn't have this class!\n",oID,cls_id,spell_id,ignore_limit);
					}
				}
				else
				{
					fprintf(logFile, "ERROR: AddKnownSpell(%08X,%i,%i,%i) not a spell of this class!\n",oID,cls_id,spell_id,ignore_limit);
				}
			}
			else
			{
				fprintf(logFile, "ERROR: AddKnownSpell(%08X,%i,%i,%i) used with incorrect parameters!\n",oID,cls_id,spell_id,ignore_limit);
			}
		}
		else
		{
			fprintf(logFile, "ERROR: AddKnownSpell(%08X,%i,%i,%i) used on wrong object type!\n",oID,cls_id,spell_id,ignore_limit);
		}
	}
	else if(nFunc == 503)//RemoveKnownSpell
	{
		unsigned long oID = OBJECT_INVALID, cls_id = CLASS_TYPE_INVALID, spell_id = OBJECT_INVALID;
		sscanf_s(Params,"%x|%i|%i",&oID,&cls_id,&spell_id);
		CNWSCreature *cre = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(oID);
		if(oID != OBJECT_INVALID && cre)
		{
			if(cls_id != CLASS_TYPE_INVALID && spell_id != OBJECT_INVALID)
			{
				unsigned char spell_lvl = NWN_Rules->m_pSpellArray->GetSpell(spell_id)->GetSpellLevel((unsigned char)cls_id);
				if(spell_lvl < 10)
				{
					unsigned char cls_pos = 0;
					for(;cls_pos < cre->cre_stats->cs_classes_len;cls_pos++)
					{
						if(cre->cre_stats->cs_classes[cls_pos].cl_class == cls_id)
						{
							break;
						}
					}
					if(cls_pos < cre->cre_stats->cs_classes_len)
					{
						cre->cre_stats->cs_classes[cls_pos].RemoveKnownSpell(spell_lvl,spell_id);
					}
					else
					{
						fprintf(logFile, "ERROR: RemoveKnownSpell(%08X,%i,%i), creature doesn't have this class!\n",oID,cls_id,spell_id);
					}
				}
				else
				{
					fprintf(logFile, "ERROR: RemoveKnownSpell(%08X,%i,%i) not a spell of this class!\n",oID,cls_id,spell_id);
				}
			}
			else
			{
				fprintf(logFile, "ERROR: RemoveKnownSpell(%08X,%i,%i) used with incorrect parameters!\n",oID,cls_id,spell_id);
			}
		}
		else
		{
			fprintf(logFile, "ERROR: RemoveKnownSpell(%08X,%i,%i) used on wrong object type!\n",oID,cls_id,spell_id);
		}
	}
	else if(nFunc == 504)//GetKnownSpell
	{
		unsigned long oID = OBJECT_INVALID, cls_id = CLASS_TYPE_INVALID, spell_lvl = 255, index = 255;
		sscanf_s(Params,"%x|%i|%i|%i",&oID,&cls_id,&spell_lvl,&index);
		CNWSCreature *cre = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(oID);
		if(oID != OBJECT_INVALID && cre)
		{
			if(cls_id != CLASS_TYPE_INVALID && spell_lvl != 255 && index < 255)
			{
				unsigned char cls_pos = 0;
				for(;cls_pos < cre->cre_stats->cs_classes_len;cls_pos++)
				{
					if(cre->cre_stats->cs_classes[cls_pos].cl_class == cls_id)
					{
						break;
					}
				}
				if(cls_pos < cre->cre_stats->cs_classes_len)
				{
					retVal = cre->cre_stats->GetKnownSpell(cls_pos,(unsigned char)spell_lvl,(unsigned char)index);
				}
				else
				{
					fprintf(logFile, "ERROR: GetKnownSpell(%08X,%i,%i,%i) creature doesn't have this class!\n",oID,cls_id,spell_lvl,index);
				}
			}
			else
			{
				fprintf(logFile, "ERROR: GetKnownSpell(%08X,%i,%i,%i) used with incorrect parameters!\n",oID,cls_id,spell_lvl,index);
			}
		}
		else
		{
			fprintf(logFile, "ERROR: GetKnownSpell(%08X,%i,%i,%i) used on wrong object type!\n",oID,cls_id,spell_lvl,index);
		}
		pThis->SetInt(VarName,retVal,0);
	}
	else if(nFunc == 505)//GetSpellSchoolSpecialization
	{
		unsigned long oID = OBJECT_INVALID, cls_id = CLASS_TYPE_INVALID;
		sscanf_s(Params,"%x|%i",&oID,&cls_id);
		CNWSCreature *cre = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(oID);
		if(oID != OBJECT_INVALID && cre)
		{
			if(cls_id != CLASS_TYPE_INVALID)
			{
				unsigned char cls_pos = 0;
				for(;cls_pos < cre->cre_stats->cs_classes_len;cls_pos++)
				{
					if(cre->cre_stats->cs_classes[cls_pos].cl_class == cls_id)
					{
						break;
					}
				}
				if(cls_pos < cre->cre_stats->cs_classes_len)
				{
					retVal = cre->cre_stats->cs_classes[cls_pos].cl_specialist;
				}
				else
				{
					fprintf(logFile, "ERROR: GetSpellSchoolSpecialization(%08X,%i) creature doesn't have this class!\n",oID,cls_id);
				}
			}
			else
			{
				fprintf(logFile, "ERROR: GetSpellSchoolSpecialization(%08X,%i) used with incorrect parameters!\n",oID,cls_id);
			}
		}
		else
		{
			fprintf(logFile, "ERROR: GetSpellSchoolSpecialization(%08X,%i) used on wrong object type!\n",oID,cls_id);
		}
		pThis->SetInt(VarName,retVal,0);
	}
	else if(nFunc == 506)//SetSpellSchoolSpecialization
	{
		unsigned long oID = OBJECT_INVALID, cls_id = CLASS_TYPE_INVALID, school = 255;
		sscanf_s(Params,"%x|%i|%i",&oID,&cls_id,&school);
		CNWSCreature *cre = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(oID);
		if(oID != OBJECT_INVALID && cre)
		{
			if(cls_id != CLASS_TYPE_INVALID && school != OBJECT_INVALID)
			{
				unsigned char cls_pos = 0;
				for(;cls_pos < cre->cre_stats->cs_classes_len;cls_pos++)
				{
					if(cre->cre_stats->cs_classes[cls_pos].cl_class == cls_id)
					{
						break;
					}
				}
				if(cls_pos < cre->cre_stats->cs_classes_len)
				{
					cre->cre_stats->cs_classes[cls_pos].cl_specialist = (unsigned char)school;
				}
				else
				{
					fprintf(logFile, "ERROR: SetSpellSchoolSpecialization(%08X,%i,%i), creature doesn't have this class!\n",oID,cls_id,school);
				}
			}
			else
			{
				fprintf(logFile, "ERROR: SetSpellSchoolSpecialization(%08X,%i,%i) used with incorrect parameters!\n",oID,cls_id,school);
			}
		}
		else
		{
			fprintf(logFile, "ERROR: SetSpellSchoolSpecialization(%08X,%i,%i) used on wrong object type!\n",oID,cls_id,school);
		}
	}
	else if(nFunc == 507)//GetDomain
	{
		unsigned long oID = OBJECT_INVALID, cls_id = CLASS_TYPE_INVALID, th = 255;
		sscanf_s(Params,"%x|%i|%i",&oID,&cls_id,&th);
		CNWSCreature *cre = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(oID);
		if(oID != OBJECT_INVALID && cre)
		{
			if(cls_id != CLASS_TYPE_INVALID && (th == 1 || th == 2))
			{
				unsigned char cls_pos = 0;
				for(;cls_pos < cre->cre_stats->cs_classes_len;cls_pos++)
				{
					if(cre->cre_stats->cs_classes[cls_pos].cl_class == cls_id)
					{
						break;
					}
				}
				if(cls_pos < cre->cre_stats->cs_classes_len)
				{
					retVal = th == 1 ? cre->cre_stats->cs_classes[cls_pos].cl_domain_1 : cre->cre_stats->cs_classes[cls_pos].cl_domain_2;
				}
				else
				{
					fprintf(logFile, "ERROR: GetSpellSchoolSpecialization(%08X,%i,%i) creature doesn't have this class!\n",oID,cls_id,th);
				}
			}
			else
			{
				fprintf(logFile, "ERROR: GetSpellSchoolSpecialization(%08X,%i,%i) used with incorrect parameters!\n",oID,cls_id,th);
			}
		}
		else
		{
			fprintf(logFile, "ERROR: GetSpellSchoolSpecialization(%08X,%i,%i) used on wrong object type!\n",oID,cls_id,th);
		}
		pThis->SetInt(VarName,retVal,0);
	}
	else if(nFunc == 508)//SetDomain
	{
		unsigned long oID = OBJECT_INVALID, cls_id = CLASS_TYPE_INVALID, th = 255, domain = 255;
		sscanf_s(Params,"%x|%i|%i|%i",&oID,&cls_id,&th,&domain);
		CNWSCreature *cre = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(oID);
		if(oID != OBJECT_INVALID && cre)
		{
			if(cls_id != CLASS_TYPE_INVALID && domain != OBJECT_INVALID && (th == 1 || th == 2))
			{
				unsigned char cls_pos = 0;
				for(;cls_pos < cre->cre_stats->cs_classes_len;cls_pos++)
				{
					if(cre->cre_stats->cs_classes[cls_pos].cl_class == cls_id)
					{
						break;
					}
				}
				if(cls_pos < cre->cre_stats->cs_classes_len)
				{
					if(th == 1)
						cre->cre_stats->cs_classes[cls_pos].cl_domain_1 = (unsigned char)domain;
					else
						cre->cre_stats->cs_classes[cls_pos].cl_domain_2 = (unsigned char)domain;
				}
				else
				{
					fprintf(logFile, "ERROR: SetSpellSchoolSpecialization(%08X,%i,%i,%i), creature doesn't have this class!\n",oID,cls_id,th,domain);
				}
			}
			else
			{
				fprintf(logFile, "ERROR: SetSpellSchoolSpecialization(%08X,%i,%i,%i) used with incorrect parameters!\n",oID,cls_id,th,domain);
			}
		}
		else
		{
			fprintf(logFile, "ERROR: SetSpellSchoolSpecialization(%08X,%i,%i,%i) used on wrong object type!\n",oID,cls_id,th,domain);
		}
	}
	else if(nFunc == 509)//GetMemorizedSpellSlot
	{
		unsigned long oID = OBJECT_INVALID, cls_id = CLASS_TYPE_INVALID, spell_lvl = 255, index = OBJECT_INVALID;
		sscanf_s(Params,"%x|%i|%i|%i",&oID,&cls_id,&spell_lvl,&index);
		CNWSCreature *cre = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(oID);
		if(oID != OBJECT_INVALID && cre)
		{
			if(cls_id != CLASS_TYPE_INVALID && spell_lvl < 10 && index != OBJECT_INVALID)
			{
				unsigned char cls_pos = 0;
				for(;cls_pos < cre->cre_stats->cs_classes_len;cls_pos++)
				{
					if(cre->cre_stats->cs_classes[cls_pos].cl_class == cls_id)
					{
						break;
					}
				}
				if(cls_pos < cre->cre_stats->cs_classes_len)
				{
					CNWSStats_Spell *sp = (CNWSStats_Spell*)(CExoArrayList_ptr_get(&(cre->cre_stats->cs_classes[cls_pos].cl_spells_mem[spell_lvl]), index));
					if(sp)
					{
						retVal = (sp->sp_id & 0xFFFF) | ((sp->sp_meta & 0xFF) << 16) | (sp->sp_ready << 24);
					}
				}
				else
				{
					fprintf(logFile, "ERROR: GetMemorizedSpellSlot(%08X,%i,%i,%i) creature doesn't have this class!\n",oID,cls_id,spell_lvl,index);
				}
			}
			else
			{
				fprintf(logFile, "ERROR: GetMemorizedSpellSlot(%08X,%i,%i,%i) used with incorrect parameters!\n",oID,cls_id,spell_lvl,index);
			}
		}
		else
		{
			fprintf(logFile, "ERROR: GetMemorizedSpellSlot(%08X,%i,%i,%i) used on wrong object type!\n",oID,cls_id,spell_lvl,index);
		}
		pThis->SetInt(VarName,retVal,0);
	}
	else if(nFunc == 510)//SetMemorizedSpellSlot
	{
		unsigned long oID = OBJECT_INVALID, cls_id = CLASS_TYPE_INVALID, spell_lvl = 255, index = OBJECT_INVALID, spell_data = OBJECT_INVALID;
		sscanf_s(Params,"%x|%i|%i|%i|%i",&oID,&cls_id,&spell_lvl,&index,&spell_data);
		CNWSCreature *cre = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(oID);
		if(oID != OBJECT_INVALID && cre)
		{
			if(cls_id != CLASS_TYPE_INVALID && spell_lvl < 10 && index != OBJECT_INVALID && spell_data != OBJECT_INVALID)
			{
				unsigned char cls_pos = 0;
				for(;cls_pos < cre->cre_stats->cs_classes_len;cls_pos++)
				{
					if(cre->cre_stats->cs_classes[cls_pos].cl_class == cls_id)
					{
						break;
					}
				}
				if(cls_pos < cre->cre_stats->cs_classes_len)
				{
					CNWSStats_Spell *sp;
					int sp_spell = spell_data & 0xFFFF;
					int sp_meta  = (spell_data >> 16) & 0x7F;
					int sp_flags = (spell_data >> 24) & 1;
					if(sp_spell < 0)
					{
						if(cre->cre_stats->cs_classes[cls_pos].cl_spells_mem[spell_lvl].data[index] != NULL)
						{
							nwnx_free(cre->cre_stats->cs_classes[cls_pos].cl_spells_mem[spell_lvl].data[index]);
						}
						cre->cre_stats->cs_classes[cls_pos].cl_spells_mem[spell_lvl].data[index] = NULL;
					}
					else
					{
						if((sp = ((CNWSStats_Spell *)cre->cre_stats->cs_classes[cls_pos].cl_spells_mem[spell_lvl].data[index])) == NULL)
						{
							if((sp = ((CNWSStats_Spell *)nwnx_calloc(1, sizeof(*sp)))) != NULL)
							{
								cre->cre_stats->cs_classes[cls_pos].cl_spells_mem[spell_lvl].data[index] = sp;
							}
						}
						if(sp != NULL)
						{
							sp->sp_id = sp_spell;
							sp->sp_meta = sp_meta;
							sp->sp_ready = !!(sp_flags & 1);
							sp->sp_domain = !!(sp_flags & 2);
						}
					}
				}
				else
				{
					fprintf(logFile, "ERROR: SetMemorizedSpellSlot(%08X,%i,%i,%i,%i) creature doesn't have this class!\n",oID,cls_id,spell_lvl,index,spell_data);
				}
			}
			else
			{
				fprintf(logFile, "ERROR: SetMemorizedSpellSlot(%08X,%i,%i,%i,%i) used with incorrect parameters!\n",oID,cls_id,spell_lvl,index,spell_data);
			}
		}
		else
		{
			fprintf(logFile, "ERROR: SetMemorizedSpellSlot(%08X,%i,%i,%i,%i) used on wrong object type!\n",oID,cls_id,spell_lvl,index,spell_data);
		}
	}
	else if(nFunc == 511)//GetMaxSpellSlots
	{
		unsigned long oID = OBJECT_INVALID, cls_id = CLASS_TYPE_INVALID, spell_lvl = 255;
		sscanf_s(Params,"%x|%i|%i",&oID,&cls_id,&spell_lvl);
		CNWSCreature *cre = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(oID);
		if(oID != OBJECT_INVALID && cre)
		{
			if(cls_id != CLASS_TYPE_INVALID && spell_lvl < 10)
			{
				unsigned char cls_pos = 0;
				for(;cls_pos < cre->cre_stats->cs_classes_len;cls_pos++)
				{
					if(cre->cre_stats->cs_classes[cls_pos].cl_class == cls_id)
					{
						break;
					}
				}
				if(cls_pos < cre->cre_stats->cs_classes_len)
				{
					retVal = cre->cre_stats->cs_classes[cls_pos].cl_spells_mem[spell_lvl].len;
				}
				else
				{
					fprintf(logFile, "ERROR: GetMaxSpellSlots(%08X,%i,%i) creature doesn't have this class!\n",oID,cls_id,spell_lvl);
				}
			}
			else
			{
				fprintf(logFile, "ERROR: GetMaxSpellSlots(%08X,%i,%i) used with incorrect parameters!\n",oID,cls_id,spell_lvl);
			}
		}
		else
		{
			fprintf(logFile, "ERROR: GetMaxSpellSlots(%08X,%i,%i) used on wrong object type!\n",oID,cls_id,spell_lvl);
		}
		pThis->SetInt(VarName,retVal,0);
	}
	else if(nFunc == 513)//GetSpellProgression
	{
		unsigned long oID = OBJECT_INVALID, cls_id = CLASS_TYPE_INVALID;
		sscanf_s(Params,"%x|%i",&oID,&cls_id);
		CNWSCreature *cre = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(oID);
		if(oID != OBJECT_INVALID && cre)
		{
			if(cls_id != CLASS_TYPE_INVALID)
			{
				unsigned char cls_pos = 0;
				for(;cls_pos < cre->cre_stats->cs_classes_len;cls_pos++)
				{
					if(cre->cre_stats->cs_classes[cls_pos].cl_class == cls_id)
					{
						break;
					}
				}
				if(cls_pos < cre->cre_stats->cs_classes_len)
				{
					retVal = GetSpellProgressionModifier(cre->cre_stats,cls_pos);
				}
				else
				{
					fprintf(logFile, "ERROR: GetSpellProgression(%08X,%i,%i) creature doesn't have this class!\n",oID,cls_id);
				}
			}
			else
			{
				fprintf(logFile, "ERROR: GetSpellProgression(%08X,%i,%i) used with incorrect parameters!\n",oID,cls_id);
			}
		}
		else
		{
			fprintf(logFile, "ERROR: GetSpellProgression(%08X,%i,%i) used on wrong object type!\n",oID,cls_id);
		}
		pThis->SetInt(VarName,retVal,0);
	}
	fflush(logFile);
}

void __fastcall CNWSScriptVarTable__SetString_Hook(CNWSScriptVarTable *pThis, void*, CExoString &VarName, CExoString &Value)
{
	Log(2,"o CNWSScriptVarTable__SetString start\n");
	if(!strcmp(VarName.text,"NWNX!PATCH!VERIFY"))
	{
		sprintf_s(Value.text,sizeof(Value.text),"%s","1");
	}
	else if(!strcmp(VarName.text,"NWNX!PATCH!SWITCH"))
	{
		InitializeModuleSwitches(NWN_AppManager->app_server->srv_internal->GetModule());
	}
	else if(!strncmp(VarName.text,"NWNX!PATCH!FUNCS!",17))
	{
		char *delimiter = strchr(VarName.text,'!');
		while(delimiter)
		{
			if(delimiter-VarName.text == 16)
			{
				NWNXPatch_Funcs(pThis,atoi(delimiter+1),Value.text);
				return;
			}
			delimiter=strchr(delimiter+1,'!');
		}
	}
	CNWSScriptVarTable__SetString(pThis,NULL,VarName,Value);
}

unsigned long __fastcall CNWSModule__LoadModuleFinish_Hook(CNWSModule *pThis, void*)
{
	Log(2,"o CNWSModule__LoadModuleFinish start\n");
	//DisableHighlightObjects = false;
	unsigned long retVal = CNWSModule__LoadModuleFinish(pThis,NULL);
	NWN_VirtualMachine->Runscript(&script_load,pThis->obj_id);
	InitializeWeaponFeats2DA();
	InitializeEffects2DA();
	InitializeRacialTypes2DA();
	InitializeClasses2DA();
	InitializeSpells2DA();
	InitializeSpells_Level2DA();
	InitializeModuleSwitches(pThis);
	return retVal;
}

int __fastcall CNWSMessage__HandlePlayerToServerMessage_Hook(CNWSMessage *pMessage, void *, unsigned long nPlayerID, unsigned char *pData, unsigned long nLen)
{
	Log(2,"o CNWSMessage__HandlePlayerToServerMessage start\n");
	int nType = pData[1];
	int nSubtype = pData[2];

	//Log(2, "Message: PID %d, type %i, subtype %i\n", nPlayerID, nType, nSubtype);

	if(nType == 1)
	{
		unsigned char *pData;
		long unsigned int nSize;
		int32_t i;
		CExoArrayList_string *haklist;

		void *writeexo = (void *)0x00508900;

		char *txt;
		unsigned int len;
	
		// Setup some important variables
		HANDLE sharedHeap = (HANDLE) *heapAddress;
		CNWMessage *message = (CNWMessage*)(pMessage);
		CNWSModule *pModule = NWN_AppManager->app_server->srv_internal->GetModule();

		if(pModule)
		{
			// The haklist is acquired in a little counter-intuitive way.  Sorry, thats just the way of it :)
			haklist = &(pModule->mod_haks);

			fprintf(logFile, "Sending hak list...pMessage=%X, nPlayerID=%d\n", pMessage, nPlayerID);fflush(logFile);

			message->CreateWriteMessage(80, -1, 1);
			message->WriteINT(haklist->len, 32);

			for(i=haklist->len-1; i > -1;i--)
			{
				fprintf(logFile, "\t%s\n", haklist->data[i].text);fflush(logFile);

				// CExoString() class for whatever reason is giving me a ridiculously hard time.  Even CNWSModule 
				// for all of its complexity gives me an easier time.  Going to deal with this the asm way.
				txt = (char *)HeapAlloc(sharedHeap, NULL, haklist->data[i].Length);
				len = haklist->data[i].Length;
				strcpy_s(txt, len, haklist->data[i].text);
				_asm {
					push 0x20;
					push len;
					push txt;
					mov ecx, message;
					call writeexo;
				}

				// HeapFree() is called on txt by WriteCExoString, so no need to free it.
				// At least in MY debugger it does :P  I would be very interested in hearing if this plugin 
				// had memory leaks or cases in which the NWNServer internal HeapFree was *not* called.
			}
			/*
			for(i = haklist->alloc - 1; i >= 0; --i)
			{
				Log(0, "%s\n", haklist->data[i].text);
				message->WriteCExoString(haklist->data[i], 32);
			}
			*/
			txt = (char *)HeapAlloc(sharedHeap, NULL, pModule->mod_custom_tlk.Length);
			len = pModule->mod_custom_tlk.Length;
			if(len != NULL)
			{
				strcpy_s(txt, len, pModule->mod_custom_tlk.text);
				_asm {
					push 0x20;
					push len;
					push txt;
					mov ecx, message;
					call writeexo;
				}
			}

		message->GetWriteMessage((unsigned char **) &pData, (unsigned long *) &nSize);
		pMessage->SendServerToPlayerMessage(nPlayerID, 200, 1, pData, nSize);
		}
	}
	else if(nType == 119 && !DisallowAnimalCompanionPossessing)
	{
		CNWSPlayer *player = NWN_AppManager->app_server->srv_internal->GetClientObjectByPlayerId(nPlayerID,1);
		if(player)
		{
			CNWSCreature *cre = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(player->m_oidNWSObject);
			if(cre)
			{
				cre->field_B48 = cre->GetAssociateId(2,1);
				cre->PossessFamiliar();
			}
		}
	}
	else if(nType == 210)//VerifyClientRunningNWNCX
	{
		CNWSModule *mod = NWN_AppManager->app_server->srv_internal->GetModule();
		if(mod)
		{
			char *var = new char[64];
			sprintf_s(var,64,"VERIFY_NWNCX_PATCH_%i",nPlayerID);
			CExoString VarName = CExoString(var);
			delete var;
			mod->mod_vartable.SetInt(VarName,nSubtype,0);			
		}
	}
	else if(nType == 211)//OnPlayerObjectHighlighted
	{
		CNWSPlayer *player = NWN_AppManager->app_server->srv_internal->GetClientObjectByPlayerId(nPlayerID,1);
		if(player)
		{
			NWN_VirtualMachine->Runscript(&CExoString("70_mod_hlight"),player->m_oidNWSObject);	
		}
	}
	return CNWSMessage__HandlePlayerToServerMessage(pMessage,NULL,nPlayerID,pData,nLen);
}

char __fastcall CNWSCreatureStats__GetTotalACSkillMod_Hook(CNWSCreatureStats *pThis, void*)
{
	Log(2,"o CNWSCreatureStats__GetTotalACSkillMod start\n");
	if(pThis != NULL && pThis->cs_original->obj.obj_vartable.MatchIndex(CExoString("TumbleAC"),VARIABLE_TYPE_INT,0) != NULL)
	{
		int nAC = pThis->cs_original->obj.obj_vartable.GetInt(CExoString("TumbleAC"));
		if(nAC > 127)
			return 127;
		else if(nAC < -127)
			return -127;
		return nAC;
	}
	return NoTumbleAC ? 0 : CNWSCreatureStats__GetTotalACSkillMod(pThis,NULL);
}

unsigned char __fastcall CNWSItem__GetMinEquipLevel_Hook(CNWSItem *pThis, void*)
{
	Log(2,"o CNWSItem__GetMinEquipLevel start\n");
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
	Log(2,"o CNWSObject__ClearAllPartyInvalidActions start\n");
	if(pThis != NULL && pThis->obj_generic.obj_type2 == OBJECT_TYPE2_CREATURE)
	{
		return;
	}
	CNWSObject__ClearAllPartyInvalidActions(pThis, NULL);
}

void __fastcall CNWSCreature__ResolveRangedSpecialAttack_Hook(CNWSCreature *pThis, void*, CNWSObject *target, int a1)
{
	Log(2,"o CNWSCreature__ResolveRangedSpecialAttack start\n");
	CNWSCombatAttackData *attack = pThis->cre_combat_round->GetAttack(pThis->cre_combat_round->CurrentAttack);
	fprintf(logFile, "o ResolveRangedSpecialAttack: %x %i type %i ranged %i result %i\n",target->obj_generic.obj_id,a1,attack->m_nAttackType,attack->m_bRangedAttack,attack->m_nAttackResult);fflush(logFile);
	//performs default attack subroutines
	pThis->ResolveAttackRoll(target);
	pThis->ResolveDamage(target);
	pThis->ResolvePostRangedDamage(target);
	pThis->ResolveRangedAnimations(target,a1);	
	if(!pThis || !target || pThis->obj.obj_generic.obj_id == target->obj_generic.obj_id)
	{
		return CNWSCreature__ResolveRangedSpecialAttack(pThis,NULL,target,a1);
	}
	if(attack->m_nAttackType < 65000 && !pThis->cre_stats->GetFeatRemainingUses(attack->m_nAttackType))
	{
		attack->m_nAttackType = 0;
		return CNWSCreature__ResolveRangedSpecialAttack(pThis,NULL,target,a1);
	}
	if(attack->m_nAttackResult == 1 || attack->m_nAttackResult == 3 || attack->m_nAttackResult == 5 || attack->m_nAttackResult == 6 || attack->m_nAttackResult == 7 || attack->m_nAttackResult == 10)
	{
		pThis->obj.obj_vartable.SetInt(CExoString("SPECIAL_ATTACK_EVENT"),4,1);
		pThis->obj.obj_vartable.SetInt(CExoString("SPECIAL_ATTACK_TYPE"),attack->m_nAttackType,1);
		pThis->obj.obj_vartable.SetInt(CExoString("SPECIAL_ATTACK_DATA1"),attack->GetTotalDamage(1),1);
		pThis->obj.obj_vartable.SetInt(CExoString("SPECIAL_ATTACK_DATA2"),attack->m_nToHitRoll+attack->m_nToHitMod,1);
		pThis->obj.obj_vartable.SetObject(CExoString("SPECIAL_ATTACK_TARGET"),target->obj_generic.obj_id);
		if(!NWN_VirtualMachine->Runscript(&CExoString("70_s2_specattk"),pThis->obj.obj_generic.obj_id))
		{
			//this will happen if user doesn't have script 70_s2_specattk which means he most likely uses plugin but not patch
			return CNWSCreature__ResolveRangedSpecialAttack(pThis,NULL,target,a1);
		}
		//cleanup
		pThis->obj.obj_vartable.DestroyInt(CExoString("SPECIAL_ATTACK_EVENT"));
		pThis->obj.obj_vartable.DestroyInt(CExoString("SPECIAL_ATTACK_TYPE"));
		pThis->obj.obj_vartable.DestroyInt(CExoString("SPECIAL_ATTACK_DATA1"));
		pThis->obj.obj_vartable.DestroyInt(CExoString("SPECIAL_ATTACK_DATA2"));
		pThis->obj.obj_vartable.DestroyObject(CExoString("SPECIAL_ATTACK_TARGET"));
		int result = pThis->obj.obj_vartable.GetInt(CExoString("SPECIAL_ATTACK_RESULT"));
		pThis->obj.obj_vartable.DestroyInt(CExoString("SPECIAL_ATTACK_RESULT"));
		if(result == -1)
		{
			attack->m_nAttackResult = 5;
		}
		if(result == -2)
		{
			attack->m_nAttackResult = 6;
		}
		return;
	}
	CNWSCreature__ResolveRangedSpecialAttack(pThis,NULL,target,a1);
}

void __fastcall CNWSCreature__ResolveMeleeSpecialAttack_Hook(CNWSCreature *pThis, void*, int a1, int a2, CNWSObject *target, int a4)
{
	Log(2,"o CNWSCreature__ResolveMeleeSpecialAttack start\n");
	CNWSCombatAttackData *attack = pThis->cre_combat_round->GetAttack(pThis->cre_combat_round->CurrentAttack);
	fprintf(logFile, "o ResolveMeleeSpecialAttack: %i %i %x %i type %i ranged %i result %i\n",a1,a2,target->obj_generic.obj_id,a4,attack->m_nAttackType,attack->m_bRangedAttack,attack->m_nAttackResult);fflush(logFile);
	//performs default attack subroutines
	pThis->ResolveAttackRoll(target);
	pThis->ResolveDamage(target);
	pThis->ResolvePostMeleeDamage(target);
	pThis->ResolveMeleeAnimations(a1,a2,target,a4);	
	if(!pThis || !target || pThis->obj.obj_generic.obj_id == target->obj_generic.obj_id)
	{
		return CNWSCreature__ResolveMeleeSpecialAttack(pThis,NULL,a1,a2,target,a4);
	}
	if(attack->m_nAttackType < 65000 && !pThis->cre_stats->GetFeatRemainingUses(attack->m_nAttackType))
	{
		attack->m_nAttackType = 0;
		return CNWSCreature__ResolveMeleeSpecialAttack(pThis,NULL,a1,a2,target,a4);
	}
	if(attack->m_nAttackResult == 1 || attack->m_nAttackResult == 3 || attack->m_nAttackResult == 5 || attack->m_nAttackResult == 6 || attack->m_nAttackResult == 7 || attack->m_nAttackResult == 10)
	{
		pThis->obj.obj_vartable.SetInt(CExoString("SPECIAL_ATTACK_EVENT"),4,1);
		pThis->obj.obj_vartable.SetInt(CExoString("SPECIAL_ATTACK_TYPE"),attack->m_nAttackType,1);
		pThis->obj.obj_vartable.SetInt(CExoString("SPECIAL_ATTACK_DATA1"),attack->GetTotalDamage(1),1);
		pThis->obj.obj_vartable.SetInt(CExoString("SPECIAL_ATTACK_DATA2"),attack->m_nToHitRoll+attack->m_nToHitMod,1);
		pThis->obj.obj_vartable.SetObject(CExoString("SPECIAL_ATTACK_TARGET"),target->obj_generic.obj_id);
		if(!NWN_VirtualMachine->Runscript(&CExoString("70_s2_specattk"),pThis->obj.obj_generic.obj_id,1))
		{
			//this will happen if user doesn't have script 70_s2_specattk which means he most likely uses plugin but not patch
			return CNWSCreature__ResolveMeleeSpecialAttack(pThis,NULL,a1,a2,target,a4);
		}
		//cleanup
		pThis->obj.obj_vartable.DestroyInt(CExoString("SPECIAL_ATTACK_EVENT"));
		pThis->obj.obj_vartable.DestroyInt(CExoString("SPECIAL_ATTACK_TYPE"));
		pThis->obj.obj_vartable.DestroyInt(CExoString("SPECIAL_ATTACK_DATA1"));
		pThis->obj.obj_vartable.DestroyInt(CExoString("SPECIAL_ATTACK_DATA2"));
		pThis->obj.obj_vartable.DestroyObject(CExoString("SPECIAL_ATTACK_TARGET"));
		int result = pThis->obj.obj_vartable.GetInt(CExoString("SPECIAL_ATTACK_RESULT"));
		pThis->obj.obj_vartable.DestroyInt(CExoString("SPECIAL_ATTACK_RESULT"));
		if(result == -1)
		{
			attack->m_nAttackResult = 5;
		}
		if(result == -2)
		{
			attack->m_nAttackResult = 6;
		}
		return;
	}
	CNWSCreature__ResolveMeleeSpecialAttack(pThis,NULL,a1,a2,target,a4);
}

int __fastcall CNWSCreatureStats__ResolveSpecialAttackAttackBonus_Hook(CNWSCreatureStats *pThis, void*, CNWSCreature *target)
{
	Log(2,"o CNWSCreatureStats__ResolveSpecialAttackAttackBonus start\n");
	if(target == NULL)//fix for crash exploit
	{
		return 0;
	}
	CNWSCombatAttackData *attack_data = pThis->cs_original->cre_combat_round->GetAttack(pThis->cs_original->cre_combat_round->CurrentAttack);
	int attack_type = attack_data->m_nAttackType;//feat id
	if(attack_type > 0)
	{
		pThis->cs_original->obj.obj_vartable.SetInt(CExoString("SPECIAL_ATTACK_EVENT"),2,1);
		pThis->cs_original->obj.obj_vartable.SetInt(CExoString("SPECIAL_ATTACK_TYPE"),attack_data->m_nAttackType,1);
		pThis->cs_original->obj.obj_vartable.SetObject(CExoString("SPECIAL_ATTACK_TARGET"),target->obj.obj_generic.obj_id);
		if(!NWN_VirtualMachine->Runscript(&CExoString("70_s2_specattk"),pThis->cs_original->obj.obj_generic.obj_id,1))
		{
			//this will happen if user doesn't have script 70_s2_specattk which means he most likely uses plugin but not patch
			return CNWSCreatureStats__ResolveSpecialAttackAttackBonus(pThis,NULL,target);
		}
		//cleanup
		pThis->cs_original->obj.obj_vartable.DestroyInt(CExoString("SPECIAL_ATTACK_EVENT"));
		pThis->cs_original->obj.obj_vartable.DestroyInt(CExoString("SPECIAL_ATTACK_TYPE"));
		pThis->cs_original->obj.obj_vartable.DestroyObject(CExoString("SPECIAL_ATTACK_TARGET"));
		int result = pThis->cs_original->obj.obj_vartable.GetInt(CExoString("SPECIAL_ATTACK_RESULT"));
		pThis->cs_original->obj.obj_vartable.DestroyInt(CExoString("SPECIAL_ATTACK_RESULT"));
		return result;
	}
	return 0;
}

int __fastcall CNWSCreatureStats__ResolveSpecialAttackDamageBonus_Hook(CNWSCreatureStats *pThis, void*, CNWSCreature *target)
{
	Log(2,"o CNWSCreatureStats__ResolveSpecialAttackDamageBonus start\n");
	if(target == NULL)//fix for crash exploit
	{
		return 0;
	}
	CNWSCombatAttackData *attack_data = pThis->cs_original->cre_combat_round->GetAttack(pThis->cs_original->cre_combat_round->CurrentAttack);
	int attack_type = attack_data->m_nAttackType;//feat id
	if(attack_type > 0)
	{
		pThis->cs_original->obj.obj_vartable.SetInt(CExoString("SPECIAL_ATTACK_EVENT"),3,1);
		pThis->cs_original->obj.obj_vartable.SetInt(CExoString("SPECIAL_ATTACK_TYPE"),attack_data->m_nAttackType,1);
		//pThis->cs_original->obj.obj_vartable.SetInt(CExoString("SPECIAL_ATTACK_DATA1"),attack_data->AttackResult,1);
		pThis->cs_original->obj.obj_vartable.SetObject(CExoString("SPECIAL_ATTACK_TARGET"),target->obj.obj_generic.obj_id);
		if(!NWN_VirtualMachine->Runscript(&CExoString("70_s2_specattk"),pThis->cs_original->obj.obj_generic.obj_id,1))
		{
			//this will happen if user doesn't have script 70_s2_specattk which means he most likely uses plugin but not patch
			return CNWSCreatureStats__ResolveSpecialAttackAttackBonus(pThis,NULL,target);
		}
		//cleanup
		pThis->cs_original->obj.obj_vartable.DestroyInt(CExoString("SPECIAL_ATTACK_EVENT"));
		pThis->cs_original->obj.obj_vartable.DestroyInt(CExoString("SPECIAL_ATTACK_TYPE"));
		//pThis->cs_original->obj.obj_vartable.DestroyInt(CExoString("SPECIAL_ATTACK_DATA1"));
		pThis->cs_original->obj.obj_vartable.DestroyObject(CExoString("SPECIAL_ATTACK_TARGET"));
		int result = pThis->cs_original->obj.obj_vartable.GetInt(CExoString("SPECIAL_ATTACK_RESULT"));
		pThis->cs_original->obj.obj_vartable.DestroyInt(CExoString("SPECIAL_ATTACK_RESULT"));
		return result;
	}
	return 0;
}

void __fastcall CNWSCreature__UpdateAttributesOnEffect_Hook(CNWSCreature *pThis, void*, CGameEffect *eff, int arg1)
{
	Log(2,"o CNWSCreature__UpdateAttributesOnEffect start\n");
	if(helper == 40 || pThis->cre_pm_IsPolymorphed)
	{
		int prev = helper;
		helper = 39;
		CNWSCreature__UpdateAttributesOnEffect(pThis,NULL,eff,arg1);
		helper = prev;
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
			CNWClass *cClass = &(NWN_Rules->m_lstClasses[cls_id]);
			if(cClass && cClass->m_bIsSpellCasterClass && cClass->m_nPrimaryAbility == eff->eff_integers[0])
			{
				pThis->cre_stats->UpdateNumberMemorizedSpellSlots();
				pThis->cre_stats->AdjustSpellUsesPerDay();
				break;
			}
		}
	}
}

int __fastcall CNWSItemPropertyHandler__ApplyBonusSpellOfLevel_Hook(CNWSItemPropertyHandler *pThis, void*, CNWSItem *item, CNWItemProperty *ip, CNWSCreature *cre, unsigned long l, int i)
{
	Log(2,"o CNWSItemPropertyHandler__ApplyBonusSpellOfLevel start\n");
	int prev = helper;
	if(prev == 40 || cre->cre_pm_IsPolymorphed)
	{
		if(cre->cre_pm_IsPolymorphed)//polymorph skin or weapon, skip addition and mark item as merged to enforce skip also removal of this itemproperty
		{
			item->obj.obj_vartable.SetInt(CExoString("MERGED"),1,1);
			return 0;
		}
		else if(item->obj.obj_vartable.GetInt(CExoString("MERGED")) == 1)//this item was merged, skip addition
		{
			return 0;
		}
		helper = 39;//for other cases set helper value to enforce unready spell slot in SetNumberMemorizedSpellSlots
	}
	int retVal = CNWSItemPropertyHandler__ApplyBonusSpellOfLevel(pThis,NULL,item,ip,cre,l,i);
	helper = prev;
	return retVal;
}

void __fastcall CNWSCreature__RestoreItemProperties_Hook(CNWSCreature *pThis, void*)
{
	for(unsigned char slot = 0;slot < 18;slot++)
	{
		CNWSItem *item = pThis->cre_equipment->GetItemInSlot(1 << slot);
		if(item && item->GetPropertyByTypeExists(13,0))
		{
			item->obj.obj_vartable.SetInt(CExoString("BONUS_SPELL_SLOT_ACTIVE"),1,1);
		}
	}
	CNWSCreature__RestoreItemProperties(pThis,NULL);
}

void __fastcall CNWSItem__RemoveItemProperties_Hook(CNWSItem *pThis, void*, CNWSCreature *cre, unsigned long l)
{
	CNWSItem__RemoveItemProperties(pThis,NULL,cre,l);
	pThis->obj.obj_vartable.SetInt(CExoString("BONUS_SPELL_SLOT_ACTIVE"),0,1);
}

int __fastcall CNWSItemPropertyHandler__RemoveBonusSpellOfLevel_Hook(CNWSItemPropertyHandler *pThis, void*, CNWSItem *item, CNWItemProperty *ip, CNWSCreature *cre, unsigned long l)
{
	Log(2,"o CNWSItemPropertyHandler__RemoveBonusSpellOfLevel start\n");
	int prev = helper;
	if(prev == 40 || cre->cre_pm_IsPolymorphed)
	{
		if(item->obj.obj_vartable.GetInt(CExoString("MERGED")) == 1)//this item was merged, skip addition
		{
			return 0;
		}
		helper = 39;//for other cases set helper value to enforce unready spell slot in SetNumberMemorizedSpellSlots
	}
	for(unsigned char cls_pos = 0;cls_pos<cre->cre_stats->cs_classes_len;cls_pos++)
	{
		unsigned char cls_id = cre->cre_stats->cs_classes[cls_pos].cl_class;
		if(cls_id != CLASS_TYPE_INVALID && cls_id == ip->m_nSubType)
		{
			unsigned char spell_lvl = (unsigned char)ip->m_nCostTableValue;
			cre->cre_stats->SetNumberBonusSpells(cls_pos,spell_lvl,-1);
			CExoString varname = CExoString("BONUS_SPELL_SLOT_ACTIVE");
			if(cls_cast_type[cls_id] & CAST_TYPE_SPONTANEOUS && (!item->obj.obj_vartable.MatchIndex(varname,VARIABLE_TYPE_INT,0) || item->obj.obj_vartable.GetInt(varname)))
			{
				if(cre->cre_stats->GetSpellsPerDayLeft(cls_pos,spell_lvl))
				{
					cre->cre_stats->DecrementSpellsPerDayLeft(cls_pos,spell_lvl);
				}
			}
			return 0;
		}
	}
	return 0;
}

void __fastcall CNWSCreatureStats_ClassInfo__SetNumberMemorizedSpellSlots_Hook(CNWSCreatureStats_ClassInfo *pThis, void*, unsigned char spell_level, unsigned char spell_num)
{
	Log(2,"o CNWSCreatureStats_ClassInfo__SetNumberMemorizedSpellSlots start\n");
	if(helper == 39)
	{
		int numNow = pThis->GetNumberMemorizedSpellSlots(spell_level);
		if(spell_num < numNow)
		{
			int numUnready = numNow-spell_num;
			for(int i = 1;i<=numUnready;i++)
			{
				fprintf(logFile, "o Spell slots in polymorph workaround: unreadying spell at level: %i pos: %i\n",spell_level,numNow-i);fflush(logFile);
				pThis->SetMemorizedSpellInSlotReady(spell_level,numNow-i,0);
			}
		}
		return;
	}
	CNWSCreatureStats_ClassInfo__SetNumberMemorizedSpellSlots(pThis,NULL,spell_level,spell_num);
}

int __fastcall CNWSItemPropertyHandler__RemoveHolyAvenger_Hook(CNWSItemPropertyHandler *, void*, CNWSItem *item, CNWItemProperty *, CNWSCreature *cre, unsigned long)
{
	Log(2,"o CNWSItemPropertyHandler__RemoveHolyAvenger start\n");
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

int __fastcall CNWSItemPropertyHandler__ApplyHolyAvenger_Hook(CNWSItemPropertyHandler *pThis, void*, CNWSItem *item, CNWItemProperty *ip, CNWSCreature *cre, unsigned long l, int i)
{
	Log(2,"o CNWSItemPropertyHandler__ApplyHolyAvenger start\n");
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
	Log(2,"o CNWSCreature__GetRelativeWeaponSize start\n");
	if(pThis != NULL && weapon != NULL && weapon->m_oidPossessor != pThis->obj.obj_generic.obj_id)
	{
		return CNWSCreature__GetRelativeWeaponSize((CNWSCreature*)NWN_AppManager->app_server->srv_internal->GetGameObject(weapon->m_oidPossessor), NULL, weapon);
	}
	return CNWSCreature__GetRelativeWeaponSize(pThis, NULL, weapon);
}

int __fastcall CNWSCreature__GetUseMonkAbilities_Hook(CNWSCreature *pThis, void*)
{
	Log(3,"o CNWSCreature__GetUseMonkAbilities start\n");
	if(NoMonkAbilities && pThis->cre_pm_IsPolymorphed)
	{
		return 0;
	}
	return CNWSCreature__GetUseMonkAbilities(pThis,NULL);
}

void __fastcall CNWSCreature__ResolveDamageShields_Hook(CNWSCreature *pThis, void*, CNWSCreature *attacker)
{
	Log(2,"o CNWSCreature__ResolveDamageShields start\n");
	bool change = false;
	if(pThis != NULL && attacker != NULL && pThis->cre_stats->m_nDamageShieldPtr > 0)
	{
		for(unsigned int nEffect = pThis->cre_stats->m_nDamageShieldPtr; nEffect < pThis->obj.obj_effects_len; nEffect++)
		{
			CGameEffect* e = *(pThis->obj.obj_effects+nEffect);
			//0: nDamageAmount 1: nRandomAmount 2: nDamageType 3: racialtype 4: alignment_chaoslawful 5: alignment_goodevil 6: isvsracial
			if(e->eff_type == EFFECT_TRUETYPE_DAMAGE_SHIELD && ((e->eff_integers[6] == 1 && e->eff_integers[4] != RACIAL_TYPE_INVALID && attacker->cre_stats->cs_race != e->eff_integers[4]) ||
			(e->eff_integers[4] != 0 && attacker->cre_stats->GetSimpleAlignmentLawChaos() != e->eff_integers[4]) ||
			(e->eff_integers[5] != 0 && attacker->cre_stats->GetSimpleAlignmentGoodEvil() != e->eff_integers[5])))
			{
				e->eff_type = EFFECT_TRUETYPE_DEATH;
				change = true;
			}
		}
	}
	CNWSCreature__ResolveDamageShields(pThis, NULL, attacker);
	if(change)
	{
		for(unsigned int nEffect = pThis->cre_stats->m_nDamageShieldPtr; nEffect < pThis->obj.obj_effects_len; nEffect++)
		{
			CGameEffect* e = *(pThis->obj.obj_effects+nEffect);
			if(e->eff_type == EFFECT_TRUETYPE_DEATH)
			{
				e->eff_type = EFFECT_TRUETYPE_DAMAGE_SHIELD;
			}
		}
	}
}

int __fastcall CNWSCreatureStats__GetCriticalHitRoll_Hook(CNWSCreatureStats *pThis, void*, int n)
{
	Log(2,"o CNWSCreatureStats__GetCriticalHitRoll start\n");
	int bonus = 0 , baseitem = -1, threat = 1;
	CNWSItem *weapon;
	if(n == 1)//lefthand
	{
		weapon = pThis->cs_original->cre_equipment->GetItemInSlot(EQUIPMENT_SLOT_LEFTHAND);
		if(weapon != NULL)
		{
			baseitem = weapon->it_baseitemtype;
		}
	}
	else//righthand
	{
		weapon = pThis->cs_original->cre_equipment->GetItemInSlot(EQUIPMENT_SLOT_RIGHTHAND);
		if(weapon != NULL)
		{
			baseitem = weapon->it_baseitemtype;
		}
		else
		{
			weapon = pThis->cs_original->cre_equipment->GetItemInSlot(EQUIPMENT_SLOT_ARMS);
		}
	}	
	if(baseitem > -1)
	{
		if(weapon->obj.obj_vartable.MatchIndex(CExoString("CriticalThreatOverride"),VARIABLE_TYPE_INT,0) != NULL)
		{
			return weapon->obj.obj_vartable.GetInt(CExoString("CriticalThreatOverride"));
		}
		threat = NWN_Rules->m_pBaseItemArray->GetBaseItem(baseitem)->CritThreat;
		if(threat < 1) threat = 1;
		if(pThis->HasFeat(885) && pThis->GetIsWeaponOfChoice(baseitem))//ki critical
		{
			bonus+= 2;
		}
	}
	else if(pThis->cs_original->obj.obj_vartable.MatchIndex(CExoString("CriticalThreatOverride"),VARIABLE_TYPE_INT,0) != NULL)
	{
		return pThis->cs_original->obj.obj_vartable.GetInt(CExoString("CriticalThreatOverride"));
	}
	if(pThis->GetWeaponImprovedCritical(baseitem > -1 ? weapon : NULL))
	{
		bonus+= threat;
	}
	if(weapon != NULL)
	{
		if(weapon->GetPropertyByTypeExists(43,0))
		{
			bonus+= threat;
		}
		baseitem = weapon->obj.obj_vartable.GetInt(CExoString("ModCritThreat"));
		if(baseitem != 0)
		{
			if(baseitem > 21-threat-bonus)
			{
				threat = 20; bonus = 0;
			}
			else
			{
				bonus+= baseitem;
				if(21-threat-bonus > 20)
				{
					threat=1;
					bonus=0;
				}
			}
		}
	}
	return 21-threat-bonus;
}

int __fastcall CNWSCreatureStats__GetCriticalHitMultiplier_Hook(CNWSCreatureStats *pThis, void*, int n)
{
	Log(2,"o CNWSCreatureStats__GetCriticalHitMultiplier start\n");
	int baseitem = -1, multiplier = 2;
	CNWSItem *weapon;
	if(n == 1)//lefthand
	{
		weapon = pThis->cs_original->cre_equipment->GetItemInSlot(EQUIPMENT_SLOT_LEFTHAND);
		if(weapon != NULL)
		{
			baseitem = weapon->it_baseitemtype;
		}
	}
	else//righthand
	{
		weapon = pThis->cs_original->cre_equipment->GetItemInSlot(EQUIPMENT_SLOT_RIGHTHAND);
		if(weapon != NULL)
		{
			baseitem = weapon->it_baseitemtype;
		}
		else
		{
			weapon = pThis->cs_original->cre_equipment->GetItemInSlot(EQUIPMENT_SLOT_ARMS);
		}
	}	
	if(baseitem > -1)
	{
		if(weapon->obj.obj_vartable.MatchIndex(CExoString("CriticalMultiplierOverride"),VARIABLE_TYPE_INT,0) != NULL)
		{
			return weapon->obj.obj_vartable.GetInt(CExoString("CriticalMultiplierOverride"));
		}
		multiplier = NWN_Rules->m_pBaseItemArray->GetBaseItem(baseitem)->CritHitMult;
		if(multiplier < 1) multiplier = 1;
		if(pThis->HasFeat(883) && pThis->GetIsWeaponOfChoice(baseitem))//ki critical
		{
			multiplier++;
		}
	}
	else if(pThis->cs_original->obj.obj_vartable.MatchIndex(CExoString("CriticalMultiplierOverride"),VARIABLE_TYPE_INT,0) != NULL)
	{
		return pThis->cs_original->obj.obj_vartable.GetInt(CExoString("CriticalMultiplierOverride"));
	}
	return multiplier;
}

void __fastcall CNWSCreature__ResolveAttack_Hook(CNWSCreature *pThis, void*, unsigned long target, int i, int i2)
{
	Log(2,"o CNWSCreature__ResolveAttack start\n");
	uint32_t target_prev = pThis->cre_attack_target;
	CNWSCreature__ResolveAttack(pThis, NULL, target, i, i2);
	if(pThis->cre_is_pc && pThis->cre_combat_round->NumCircleKicks == 0 && target_prev != OBJECT_INVALID && target_prev != target) 
	{
		pThis->cre_combat_round->NumCircleKicks = -1;
		CNWSObject* object = (CNWSObject*)(NWN_AppManager->app_server->srv_internal->GetGameObject(target_prev));
		if(object != NULL && !object->GetDead())
		{
			CNWSAction* action = pThis->obj.obj_ai_action;
			if(action)
			{
				action->act_target = target_prev;
			}
		}
	}
	CNWSCreature *cre = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(target);
	if(cre)
	{
		int num_used = cre->obj.obj_vartable.GetInt(CExoString("NUM_ED_Used"));
		if(cre->cre_combat_round->EpicDodgeUsed == 1 && num_used > 0)
		{
			cre->cre_combat_round->EpicDodgeUsed = 0;
			cre->obj.obj_vartable.SetInt(CExoString("NUM_ED_Used"),num_used-1,1);
		}
		num_used = cre->obj.obj_vartable.GetInt(CExoString("NUM_DEFLECT_Used"));
		if(cre->cre_combat_round->DeflectArrow == 0)
		{
			cre->cre_combat_round->DeflectArrow = 1;
			cre->obj.obj_vartable.SetInt(CExoString("NUM_DEFLECT_Used"),num_used-1,1);
		}
	}
}

int __fastcall CNWSCreatureStats__GetWeaponFinesse_Hook(CNWSCreatureStats *pThis, void*, CNWSItem *item)
{
	Log(2,"o CNWSCreatureStats__GetWeaponFinesse start\n");
	if(item && item->obj.obj_vartable.MatchIndex(CExoString("finesse"),VARIABLE_TYPE_INT,0) != NULL)
	{
		return item->obj.obj_vartable.GetInt(CExoString("finesse"));
	}
	return CNWSCreatureStats__GetWeaponFinesse(pThis, NULL, item);
}

int __fastcall CNWSCreatureStats__GetWeaponFocus_Hook(CNWSCreatureStats *pThis, void*, CNWSItem *item)
{
	Log(2,"o CNWSCreatureStats__GetWeaponFocus start\n");
	if(weaponfeats_2da)
	{
		int retVal = 0;
		weaponfeats_2da->GetINTEntry_intcol(item ? item->it_baseitemtype : 36,1,&retVal);
		if(retVal > 0)
		{
			return pThis->HasFeat((unsigned short)retVal);
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
	Log(2,"o CNWSCreatureStats__GetWeaponImprovedCritical start\n");
	if(weaponfeats_2da)
	{
		int retVal = 0;
		weaponfeats_2da->GetINTEntry_intcol(item ? item->it_baseitemtype : 36,2,&retVal);
		if(retVal > 0)
		{
			return pThis->HasFeat((unsigned short)retVal);
		}
		return FALSE;
	}
	return CNWSCreatureStats__GetWeaponImprovedCritical(pThis, NULL, item);
}

int __fastcall CNWSCreatureStats__GetWeaponSpecialization_Hook(CNWSCreatureStats *pThis, void*, CNWSItem *item)
{
	Log(2,"o CNWSCreatureStats__GetWeaponSpecialization start\n");
	if(weaponfeats_2da)
	{
		int retVal = 0;
		weaponfeats_2da->GetINTEntry_intcol(item ? item->it_baseitemtype : 36,3,&retVal);
		if(retVal > 0)
		{
			return pThis->HasFeat((unsigned short)retVal);
		}
		return FALSE;
	}
	return CNWSCreatureStats__GetWeaponSpecialization(pThis, NULL, item);
}

int __fastcall CNWSCreatureStats__GetEpicWeaponFocus_Hook(CNWSCreatureStats *pThis, void*, CNWSItem *item)
{
	Log(2,"o CNWSCreatureStats__GetEpicWeaponFocus start\n");
	if(weaponfeats_2da)
	{
		int retVal = 0;
		weaponfeats_2da->GetINTEntry_intcol(item ? item->it_baseitemtype : 36,4,&retVal);
		if(retVal > 0)
		{
			return pThis->HasFeat((unsigned short)retVal);
		}
		return FALSE;
	}
	return CNWSCreatureStats__GetEpicWeaponFocus(pThis, NULL, item);
}

int __fastcall CNWSCreatureStats__GetEpicWeaponSpecialization_Hook(CNWSCreatureStats *pThis, void*, CNWSItem *item)
{
	Log(2,"o CNWSCreatureStats__GetEpicWeaponSpecialization start\n");
	if(weaponfeats_2da)
	{
		int retVal = 0;
		weaponfeats_2da->GetINTEntry_intcol(item ? item->it_baseitemtype : 36,5,&retVal);
		if(retVal > 0)
		{
			return pThis->HasFeat((unsigned short)retVal);
		}
		return FALSE;
	}
	return CNWSCreatureStats__GetEpicWeaponSpecialization(pThis, NULL, item);
}

int __fastcall CNWSCreatureStats__GetEpicWeaponOverwhelmingCritical_Hook(CNWSCreatureStats *pThis, void*, CNWSItem *item)
{
	Log(2,"o CNWSCreatureStats__GetEpicWeaponOverwhelmingCritical start\n");
	if(weaponfeats_2da)
	{
		int retVal = 0;
		weaponfeats_2da->GetINTEntry_intcol(item ? item->it_baseitemtype : 36,6,&retVal);
		if(retVal > 0)
		{
			return pThis->HasFeat((unsigned short)retVal);
		}
		return FALSE;
	}
	return CNWSCreatureStats__GetEpicWeaponOverwhelmingCritical(pThis, NULL, item);
}

int __fastcall CNWSCreatureStats__GetEpicWeaponDevastatingCritical_Hook(CNWSCreatureStats *pThis, void*, CNWSItem *item)
{
	Log(2,"o CNWSCreatureStats__GetEpicWeaponDevastatingCritical start\n");
	if(weaponfeats_2da)
	{
		int retVal = 0;
		weaponfeats_2da->GetINTEntry_intcol(item ? item->it_baseitemtype : 36,7,&retVal);
		if(retVal > 0)
		{
			return pThis->HasFeat((unsigned short)retVal);
		}
		return FALSE;
	}
	return CNWSCreatureStats__GetEpicWeaponDevastatingCritical(pThis, NULL, item);
}

int __fastcall CNWSCreatureStats__GetIsWeaponOfChoice_Hook(CNWSCreatureStats *pThis, void*, uint32_t BaseItemType)
{
	Log(2,"o CNWSCreatureStats__GetIsWeaponOfChoice start\n");
	if(weaponfeats_2da)
	{
		int retVal = 0;
		weaponfeats_2da->GetINTEntry_intcol(BaseItemType,8,&retVal);
		if(retVal > 0)
		{
			return pThis->HasFeat((unsigned short)retVal);
		}
		return FALSE;
	}
	return CNWSCreatureStats__GetIsWeaponOfChoice(pThis, NULL, BaseItemType);
}

int __fastcall CNWSCreatureStats__GetUseMonkAttackTables_Hook(CNWSCreatureStats *pThis, void*, int a2)
{
	Log(2,"o CNWSCreatureStats__GetUseMonkAttackTables start\n");
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
					CNWBaseItem *bt = NWN_Rules->m_pBaseItemArray->GetBaseItem(item->it_baseitemtype);
					return bt->WeaponType == 0 && bt->ArmorCheckPen == 0;
				}
				return 1;
			}
			return 0;
		}
	}
	return CNWSCreatureStats__GetUseMonkAttackTables(pThis, NULL, a2);
}

int __fastcall CNWSCreature__ToggleMode_Hook(CNWSCreature *pThis, void *, unsigned char arg1)
{
	Log(2,"o CNWSCreature__ToggleMode start\n");
	/*
	pThis->obj.obj_vartable.SetInt(CExoString("TOGGLE_MODE"),arg1,1);
	if(NWN_VirtualMachine->Runscript(&CExoString("70_mod_toglemode"),pThis->obj.obj_generic.obj_id,1))
	{
		RemoveClientCombatModeABCalculation = true;
	}
	pThis->obj.obj_vartable.DestroyInt(CExoString("TOGGLE_MODE"));*/
	if(arg1 == 6)//flurry of blows
	{		
		pThis->SetCombatMode(5,pThis->cre_mode_combat != 5);
		return 0;
	}
	//Defensive Stance deactivation workaround
	else if(arg1 == 12 && pThis->cre_mode_combat == 11)
	{		
		pThis->SetActivity(0x200000,0);
		return 0;
	}
	return CNWSCreature__ToggleMode(pThis, NULL, arg1);
}

void __fastcall CNWSCreature__SetCombatMode_Hook(CNWSCreature *pThis, void*, unsigned char arg1, int arg2)
{
	Log(2,"o CNWSCreature__SetCombatMode start\n");
	if(pThis == NULL || (arg1 == 0 && arg2 == 1))
	{
		if(pThis->cre_mode_combat == 5 && !DisableStickyCombatModes)//flurry of blows automatic engine cancel
		{
			if(pThis->cre_stats->GetUseMonkAttackTables(1))
			{
				return;
			}
		}
	}
	else if(arg1 == 5 && arg2 == 0)//flurry of blows manual cancel
	{
		arg1 = 0;
		arg2 = 1;
	}
	else if(arg1 == 5 && arg2 == 1)//flurry of blows manual activation
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

int __fastcall CNWSCreatureStats__GetEffectImmunity_Hook(CNWSCreatureStats *pThis, void*, unsigned char immunity_type, CNWSCreature *cre)
{
	Log(2,"o CNWSCreatureStats__GetEffectImmunity start\n");
	char *var = new char[32];
	sprintf_s(var,32,"IMMUNITY_OVERRIDE_%i",immunity_type);
	CExoString varname = CExoString(var);
	delete var;
	if(pThis->cs_original->obj.obj_vartable.MatchIndex(varname,VARIABLE_TYPE_INT,0) != NULL)
	{
		return pThis->cs_original->obj.obj_vartable.GetInt(varname);
	}
	else if(helper == 32 && immunity_type == IMMUNITY_TYPE_ABILITY_DECREASE)
	{
		return 0;
	}
	else if(immunity_type == IMMUNITY_TYPE_CRITICAL_HIT)
	{
		if(pThis->HasFeat(896)) return true;
	}
	else if(immunity_type == IMMUNITY_TYPE_POISON)
	{
		if(pThis->HasFeat(214) || pThis->HasFeat(203) || pThis->HasFeat(747)) return true;
	}
	else if(immunity_type == IMMUNITY_TYPE_DISEASE)
	{
		if(pThis->HasFeat(219) || pThis->HasFeat(209) || pThis->HasFeat(747)) return true;
	}
	else if(immunity_type == IMMUNITY_TYPE_FEAR)
	{
		if(pThis->HasFeat(300) || pThis->HasFeat(216)) return true;
	}
	else if(immunity_type == IMMUNITY_TYPE_SLEEP)
	{
		if(pThis->HasFeat(235) || pThis->HasFeat(216)) return true;
	}
	else if(immunity_type == IMMUNITY_TYPE_PARALYSIS)
	{
		if(pThis->HasFeat(963) || pThis->HasFeat(894) || pThis->HasFeat(216)) return true;
	}
	else if(immunity_type == IMMUNITY_TYPE_STUN)
	{
		if(pThis->HasFeat(894) || pThis->HasFeat(216)) return true;
	}
	else if(immunity_type == IMMUNITY_TYPE_MIND_SPELLS || immunity_type == IMMUNITY_TYPE_DOMINATE || immunity_type == IMMUNITY_TYPE_CONFUSED || immunity_type == IMMUNITY_TYPE_CHARM || immunity_type == IMMUNITY_TYPE_DAZED)
	{
		if(pThis->HasFeat(216)) return true;
	}
	return CNWSCreatureStats__GetEffectImmunity(pThis,NULL,immunity_type,cre);
}

int __fastcall CNWSEffectListHandler__OnApplyCurse_Hook(CNWSEffectListHandler *pThis, void*, CNWSObject *obj, CGameEffect *eff, int i)
{
	Log(2,"o CNWSEffectListHandler__OnApplyCurse start\n");
	if(CurseIgnoreAbilityDecreaseImmunity)
	{
		int prev = helper;
		helper = 32;
		int retVal = CNWSEffectListHandler__OnApplyCurse(pThis,NULL,obj,eff,i);
		helper = prev;
		return retVal;
	}
	return CNWSEffectListHandler__OnApplyCurse(pThis,NULL,obj,eff,i);
}

int __fastcall CNWSEffectListHandler__OnApplyAbilityDecrease_Hook(CNWSEffectListHandler *pThis, void*, CNWSObject *obj, CGameEffect *eff, int i)
{	//effect comes from an equipped item or it comes from a curse and the game difficulty is DnD rules or Very high
	Log(2,"o CNWSEffectListHandler__OnApplyAbilityDecrease start\n");
	if(eff && eff->eff_dursubtype == 3)//ability decrease effect from itemproperty
	{
		int prev = helper;
		helper = 32;
		int retVal = CNWSEffectListHandler__OnApplyAbilityDecrease(pThis,NULL,obj,eff,i);
		helper = prev;
		return retVal;
	}
	return CNWSEffectListHandler__OnApplyAbilityDecrease(pThis,NULL,obj,eff,i);
}

int __fastcall CNWSEffectListHandler__OnApplyPolymorph_Hook(CNWSEffectListHandler *pThis, void*, CNWSObject *obj, CGameEffect *eff, int i)
{
	Log(2,"o CNWSEffectListHandler__OnApplyPolymorph start\n");
	int prev = helper;
	helper = 40;
	int retVal = CNWSEffectListHandler__OnApplyPolymorph(pThis,NULL,obj,eff,i);
	helper = prev;
	return retVal;
}
int __fastcall CNWSEffectListHandler__OnRemovePolymorph_Hook(CNWSEffectListHandler *pThis, void*, CNWSObject *obj, CGameEffect *eff)
{
	Log(2,"o CNWSEffectListHandler__OnRemovePolymorph start\n");
	int prev = helper;
	helper = 40;
	int retVal = CNWSEffectListHandler__OnRemovePolymorph(pThis,NULL,obj,eff);
	helper = prev;
	return retVal;
}

int __fastcall CNWSCreature__AddEquipItemActions_Hook(CNWSCreature *pThis, void*, CNWSItem *item, unsigned long l1, int i1, int i2, unsigned long l2)
{
	Log(2,"o CNWSCreature__AddEquipItemActions start\n");
	if(pThis != NULL && item != NULL && pThis->cre_is_pc && item == pThis->cre_equipment->GetItemInSlot(l1))//double equip exploit
	{
		return 0;
	}
	return CNWSCreature__AddEquipItemActions(pThis,NULL,item,l1,i1,i2,l2);
}

int __fastcall CNWSCreature__CanUseItem_Hook(CNWSCreature *pThis, void*, CNWSItem *item, int a1)
{
	Log(2,"o CNWSCreature__CanUseItem start\n");
	if(pThis != NULL && item != NULL && pThis->cre_is_pc && pThis->cre_pm_IsPolymorphed)
	{
		int props = NWN_Rules->m_pBaseItemArray->GetBaseItem(item->it_baseitemtype)->PropColumn;
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
				NWN_Rules->m_p2DArrays->tda_polymorph->GetINTEntry_strcol(poly, CExoString("UseItems"), &poly);
				return poly > 0 || (props == 8 && poly > -1);
			}
		}
	}
	return CNWSCreature__CanUseItem(pThis,NULL,item,a1);
}

int __fastcall CNWSCreature__UseItem_Hook(CNWSCreature *pThis, void*, unsigned long l1, unsigned char c1, unsigned char c2, unsigned long l2, Vector v, unsigned long l3)
{
	Log(2,"o CNWSCreature__UseItem start\n");
	if(pThis != NULL && pThis->cre_is_pc && pThis->cre_pm_IsPolymorphed)
	{
		CNWSItem *item = NWN_AppManager->app_server->srv_internal->GetItemByGameObjectID(l1);
		if(item != NULL && NWN_Rules->m_pBaseItemArray->GetBaseItem(item->it_baseitemtype)->equipableSlots == 0 && pThis->CanUseItem(item,c1))
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
	Log(2,"o CNWSCreature__GetAssociateId start\n");
	if(helper == 222 && pThis->field_B48 != 0 && pThis->field_B48 != OBJECT_INVALID)
	{
		return pThis->field_B48;
	}
	return CNWSCreature__GetAssociateId(pThis,NULL,type,th);
}

void __fastcall CNWSCreature__SummonAnimalCompanion_Hook(CNWSCreature *pThis, void*)
{
	Log(2,"o CNWSCreature__SummonAnimalCompanion start\n");
	CNWSPlayer *player = NWN_AppManager->app_server->srv_internal->GetClientObjectByObjectId(pThis->obj.obj_generic.obj_id);
	if(player)
	{
		unsigned char expansion = NWN_Rules->GetFamiliarExpansionLevel((unsigned char)pThis->cre_stats->cs_acomp_type,1);
		if(expansion > 0 && !player->HasExpansionPack(expansion,1))
		{
			fprintf(logFile, "o Error when summoning animal companion: player doesn't have required expansion pack!\n");fflush(logFile);
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
			fprintf(logFile, "o Error when summoning animal companion: not a druid or ranger!\n");fflush(logFile);
			return;
		}
		else if(level > 40) level = 40;
		C2DA *fam2da = NWN_Rules->m_p2DArrays->tda_hen_companion;
		CExoString *base = new CExoString();
		if(!fam2da->GetCExoStringEntry(pThis->cre_stats->cs_acomp_type,CExoString("BASERESREF"),base))
		{
			fprintf(logFile, "o Error when summoning animal companion: no value found in 2DA!\n");fflush(logFile);
			delete base;
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
		delete base;
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
	Log(2,"o CNWSCreature__SummonFamiliar start\n");
	CNWSPlayer *player = NWN_AppManager->app_server->srv_internal->GetClientObjectByObjectId(pThis->obj.obj_generic.obj_id);
	if(player)
	{
		unsigned char expansion = NWN_Rules->GetFamiliarExpansionLevel((unsigned char)pThis->cre_stats->cs_famil_type,0);
		if(expansion > 0 && !player->HasExpansionPack(expansion,1))
		{
			fprintf(logFile, "o Error when summoning familiar: player doesn't have required expansion pack!\n");fflush(logFile);
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
			fprintf(logFile, "o Error when summoning familiar: not a sorcerer or wizard!\n");fflush(logFile);
			return;
		}
		else if(level > 40) level = 40;
		C2DA *fam2da = NWN_Rules->m_p2DArrays->tda_hen_familiar;
		CExoString *base = new CExoString();
		if(!fam2da->GetCExoStringEntry(pThis->cre_stats->cs_famil_type,CExoString("BASERESREF"),base))
		{
			fprintf(logFile, "o Error when summoning familiar: no value found in 2DA!\n");fflush(logFile);
			delete base;
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
		delete base;
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

void __fastcall CNWSCreature__ResolveAmmunition_Hook(CNWSCreature *pThis, void*, unsigned long num_attacks)
{
	Log(2,"o CNWSCreature__ResolveAmmunition start\n");
	CNWSItem *item = pThis->cre_equipment->GetItemInSlot(16);
	if(!item) return;
	unsigned long slot = 0, baseitem_ammo = BASE_ITEM_INVALID, baseitem_wpn = item->it_baseitemtype;
    switch(baseitem_wpn)
	{
        case 6:
		case 7:
            slot = EQUIPMENT_SLOT_BOLTS;
            baseitem_ammo = BASE_ITEM_BOLT;
        break;
        case 8:
		case 11:
            slot = EQUIPMENT_SLOT_ARROWS;
            baseitem_ammo = BASE_ITEM_ARROW;
        break;
        case 31:
            slot = EQUIPMENT_SLOT_RIGHTHAND;
            baseitem_ammo = BASE_ITEM_DART;
        break;
        case 59:
            slot = EQUIPMENT_SLOT_RIGHTHAND;
            baseitem_ammo = BASE_ITEM_SHURIKEN;
        break;
		case 61:
            slot = EQUIPMENT_SLOT_BULLETS;
            baseitem_ammo = BASE_ITEM_BULLET;
        break;
        case 63:
            slot = EQUIPMENT_SLOT_RIGHTHAND;
            baseitem_ammo = BASE_ITEM_THROWINGAXE;
        break;
		default:
			baseitem_ammo = NWN_Rules->m_pBaseItemArray->GetBaseItem(baseitem_wpn)->RangedWeapon;
			slot = NWN_Rules->m_pBaseItemArray->GetBaseItem(baseitem_ammo)->equipableSlots;
		break;
    }
	if(baseitem_ammo == BASE_ITEM_INVALID || !slot) return;
	else if(baseitem_ammo == baseitem_wpn)//throwing weapon
	{
		if(item->GetPropertyByTypeExists(14,0)) return;//boomerang
	}
	else//normal ranged weapon
	{
		if(item->GetPropertyByTypeExists(61,0)) return;//unlimited ammo
	}
	CNWSItem *ammo = pThis->cre_equipment->GetItemInSlot(slot);
    if(ammo)
	{
		NWN_AppManager->app_server->GetServerAIMaster()->AddEventDeltaTime(0,num_attacks,pThis->obj.obj_generic.obj_id,ammo->obj.obj_generic.obj_id,16,0);
    }
}

int __fastcall CNWSCreature__GetAmmunitionAvailable_Hook(CNWSCreature *pThis, void*, int num_attacks)
{
	Log(2,"o CNWSCreature__GetAmmunitionAvailable start\n");
	CNWSItem *item = pThis->cre_equipment->GetItemInSlot(EQUIPMENT_SLOT_RIGHTHAND);
	if(!item)
	{
		return num_attacks;
	}
	unsigned long slot = 0, baseitem_ammo = BASE_ITEM_INVALID, baseitem_wpn = item->it_baseitemtype;
    switch(baseitem_wpn)
	{
        case 6:
		case 7:
            slot = EQUIPMENT_SLOT_BOLTS;
            baseitem_ammo = BASE_ITEM_BOLT;
        break;
        case 8:
		case 11:
            slot = EQUIPMENT_SLOT_ARROWS;
            baseitem_ammo = BASE_ITEM_ARROW;
        break;
        case 31:
            slot = EQUIPMENT_SLOT_RIGHTHAND;
            baseitem_ammo = BASE_ITEM_DART;
        break;
        case 59:
            slot = EQUIPMENT_SLOT_RIGHTHAND;
            baseitem_ammo = BASE_ITEM_SHURIKEN;
        break;
		case 61:
            slot = EQUIPMENT_SLOT_BULLETS;
            baseitem_ammo = BASE_ITEM_BULLET;
        break;
        case 63:
            slot = EQUIPMENT_SLOT_RIGHTHAND;
            baseitem_ammo = BASE_ITEM_THROWINGAXE;
        break;
		default:
			baseitem_ammo = NWN_Rules->m_pBaseItemArray->GetBaseItem(baseitem_wpn)->RangedWeapon;
			slot = NWN_Rules->m_pBaseItemArray->GetBaseItem(baseitem_ammo)->equipableSlots;
		break;
    }
	if(baseitem_ammo == BASE_ITEM_INVALID || !slot) return 0;
	else if(baseitem_ammo == baseitem_wpn)//throwing weapon
	{
		if(item->GetPropertyByTypeExists(14,0)) return num_attacks;//boomerang
	}
	else//normal ranged weapon
	{
		if(item->GetPropertyByTypeExists(61,0)) return num_attacks;//unlimited ammo
	}
	CNWSItem *ammo = pThis->cre_equipment->GetItemInSlot(slot);
	unsigned long stacksize = 0;
    if(ammo)
	{
		stacksize = ammo->it_stacksize;
    }
    if(stacksize <= 0) 
	{
        int i = 0;
        unsigned long id;
        do
		{
			id = pThis->cre_inventory->FindItemWithBaseItemId(baseitem_ammo,i++);
			item = NWN_AppManager->app_server->srv_internal->GetItemByGameObjectID(id);
			if(item && pThis->CanEquipItem(item,&slot,1,0,0,0) == 1)
			{
				pThis->RemoveItemFromRepository(item,1);
				if(item->m_oidPossessor != pThis->obj.obj_generic.obj_id) 
				{
					item->SetPossessor(pThis->obj.obj_generic.obj_id, 0, 0, 0);
                }
				pThis->EquipItem(slot,item,1,0);
                stacksize = item->it_stacksize;
				pThis->cre_last_ammo_warning = stacksize;
				if(baseitem_wpn == 30) return 0;
                break;
            }
        }while(id != OBJECT_INVALID);
    }
    if(stacksize > 0 && stacksize < 20 && pThis->cre_last_ammo_warning >= stacksize + 5)
    {
        pThis->cre_last_ammo_warning = stacksize;
		CNWSPlayer *player = NWN_AppManager->app_server->GetClientObjectByObjectId(pThis->obj.obj_generic.obj_id);
		if(player)
		{
			CNWCCMessageData *msg = new CNWCCMessageData();
			msg->SetInteger(0,stacksize);
			msg->SetInteger(9,0x18);
			NWN_AppManager->app_server->GetNWSMessage()->SendServerToPlayerCCMessage(player->pl_id,11,msg,0);
			delete msg;		
		}
    }
    if(stacksize < (uint32_t) num_attacks) 
	{
		if(pThis->cre_is_pc || pThis->GetIsPossessedFamiliar())
		{
			pThis->SendFeedbackMessage(0x19,0,0);
        }
		else if(pThis->cre_MasterID != OBJECT_INVALID)
		{
			CNWSCreature *master = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(pThis->cre_MasterID);
            if(master)
			{
				CNWSPlayer *player = NWN_AppManager->app_server->GetClientObjectByObjectId(master->obj.obj_generic.obj_id);
				if(player)
				{
					CNWCCMessageData *msg = new CNWCCMessageData();
					msg->SetInteger(9,0xF1);
					NWN_AppManager->app_server->GetNWSMessage()->SendServerToPlayerCCMessage(player->pl_id,11,msg,0);
					delete msg;		
				}
            }
        }
		num_attacks = stacksize;
    }
    return num_attacks;
}

void __fastcall CNWSCreature__SetActivity_Hook(CNWSCreature *pThis, void*, int nActivity, int bOn)
{
	Log(2,"o CNWSCreature__SetActivity start\n");
	//Vanilla Defensive Stance deactivation call
	if(nActivity & 0x100000 && !bOn && pThis->cre_is_pc)
	{
		return;
	}
	//Custom Defensive Stance deativation call
	else if(nActivity == 0x200000 && !bOn)
	{
		nActivity = 0x100000;
		pThis->cre_mode_combat = 0;
	}
	CNWSCreature__SetActivity(pThis, NULL, nActivity, bOn);
}

int CreateHook(DWORD pCode, PVOID pCallbackFunc, PVOID *pNextHook, const char * czName, const char * czFunc)
{
	if(pCode && !GetPrivateProfileInt("Community Patch",czName,false,"./nwnplayer.ini"))
	{
		if(HookCode((PVOID)pCode, pCallbackFunc, pNextHook))
		{
			fprintf(logFile, "o %s patched succesfully.\n", czFunc);
			return 1;
		}
		else
		{
			fprintf(logFile, "o %s patch failed.\n", czFunc);
		}
	}
	else
	{
		fprintf(logFile, "o %s patch disabled.\n", czFunc);
	}
	return 0;
}

void HookFunctions()
{
	//system
	CreateHook(0x5A1440,CNWSScriptVarTable__SetString_Hook, (PVOID*)&CNWSScriptVarTable__SetString, "DisableSetLocalStringHook","SetLocalString function");
	CreateHook(0x5426A0,CNWSMessage__HandlePlayerToServerMessage_Hook, (PVOID*)&CNWSMessage__HandlePlayerToServerMessage, "DisableConnect","Sending hak-list to client");
	CreateHook(0x4D5230,CNWSModule__LoadModuleFinish_Hook, (PVOID*)&CNWSModule__LoadModuleFinish, "DisableLoadModuleFinishHook","LoadModuleFinish function");
	CreateHook(0x4B48E0,CNWRules__ReloadAll_Hook,(PVOID*)&CNWRules__ReloadAll, "DisableReloadAll", "ReloadAll function.");
	
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
	CreateHook(0x4778B0,CNWSCreatureStats__GetCriticalHitRoll_Hook, (PVOID*)&CNWSCreatureStats__GetCriticalHitRoll, "DisableWeaponHooks","Ki critical offhand bug");
	CreateHook(0x477A20,CNWSCreatureStats__GetCriticalHitMultiplier_Hook, (PVOID*)&CNWSCreatureStats__GetCriticalHitMultiplier, "DisableWeaponHooks","Enabling critical hit multiplier modification");

	//other
	CreateHook(0x551250,CNWSCreature__GetFlanked_Hook, (PVOID*)&CNWSCreature__GetFlanked, "DisableUncannyDodge", "Enabling hardcore DnD uncanny dodge 2 rule.");
	CreateHook(0x48E050,CNWSCreatureStats__GetTotalACSkillMod_Hook, (PVOID*)&CNWSCreatureStats__GetTotalACSkillMod, "DisableGetTotalACSkillModHook","Tumble AC");
	CreateHook(0x49E370,CNWSCreature__GetUseMonkAbilities_Hook, (PVOID*)&CNWSCreature__GetUseMonkAbilities, "DisableGetUseMonkAbilitiesHook","Monk abilities in polymorph");

	CreateHook(0x547580,CNWSCreature__ResolveAttack_Hook, (PVOID*)&CNWSCreature__ResolveAttack, "DisableResolveAttackHook","Circle kick");
	CreateHook(0x491F10,CNWSCreature__AddEquipItemActions_Hook, (PVOID*)&CNWSCreature__AddEquipItemActions, "DisableAddEquipItemActionsHook","Double equip exploit");
	CreateHook(0x4CC070,CNWSCreature__SummonAnimalCompanion_Hook, (PVOID*)&CNWSCreature__SummonAnimalCompanion, "DisableSummonAnimalCompanionHook","Animal companion summoning");
	CreateHook(0x4CC390,CNWSCreature__SummonFamiliar_Hook, (PVOID*)&CNWSCreature__SummonFamiliar, "DisableSummonFamiliarHook","Familiar summoning");

	CreateHook(0x4CDD80,CNWSCreature__GetAssociateId_Hook, (PVOID*)&CNWSCreature__GetAssociateId, "DisablePossessing","Possessing function #1");
	CreateHook(0x4CCAC0,CNWSCreature__PossessFamiliar_Hook, (PVOID*)&CNWSCreature__PossessFamiliar, "DisablePossessing","Possessing function #2");
	CreateHook(0x4CCD60,CNWSCreature__UnpossessFamiliar_Hook, (PVOID*)&CNWSCreature__UnpossessFamiliar, "DisablePossessing","Possessing function #3");
	CreateHook(0x4CE920,CNWSCreature__GetIsPossessedFamiliar_Hook, (PVOID*)&CNWSCreature__GetIsPossessedFamiliar, "DisablePossessing","Possessing function #4");
	CreateHook(0x4ECA70,CNWSEffectListHandler__OnApplyDeath_Hook, (PVOID*)&CNWSEffectListHandler__OnApplyDeath, "DisablePossessing","Possessing function #6");
	CreateHook(0x483B00,CNWSCreatureStats__CanLevelUp_Hook,(PVOID*)&CNWSCreatureStats__CanLevelUp, "DisablePossessing", "Possessing function #7");
	
	CreateHook(0x4CE950,CNWSCreature__CanUseItem_Hook, (PVOID*)&CNWSCreature__CanUseItem, "DisableUseItemHook","CanUseItem function");
	CreateHook(0x4A4CB0,CNWSCreature__UseItem_Hook, (PVOID*)&CNWSCreature__UseItem, "DisableUseItemHook","Use items in polymorph");
	
	CreateHook(0x48B770,CNWSCreatureStats__GetEffectImmunity_Hook, (PVOID*)&CNWSCreatureStats__GetEffectImmunity, "DisableEffectImmunityHook","GetEffectImmunity function");
	CreateHook(0x4EDA30,CNWSEffectListHandler__OnApplyAbilityDecrease_Hook, (PVOID*)&CNWSEffectListHandler__OnApplyAbilityDecrease, "DisableEffectImmunityHook","Itemproperty ability decrease");
	CreateHook(0x4F57D0,CNWSEffectListHandler__OnApplyCurse_Hook, (PVOID*)&CNWSEffectListHandler__OnApplyCurse, "DisableEffectImmunityHook","Curse ability decrease");

	CreateHook(0x4EB560,CNWSEffectListHandler__OnEffectApplied_Hook, (PVOID*)&CNWSEffectListHandler__OnEffectApplied, "DisableCustomEffects","Enabling custom applied effect event handler");
	CreateHook(0x4EB5A0,CNWSEffectListHandler__OnEffectRemoved_Hook, (PVOID*)&CNWSEffectListHandler__OnEffectRemoved, "DisableCustomEffects","Enabling custom remove effect event handler");

	CreateHook(0x54FB70,CNWSCreature__ResolveDamageShields_Hook, (PVOID*)&CNWSCreature__ResolveDamageShields, "DisableResolveDamageShieldsHook","Effect damage shield versus alignment");
	CreateHook(0x4A6D00,CNWSCreature__GetRelativeWeaponSize_Hook, (PVOID*)&CNWSCreature__GetRelativeWeaponSize, "DisableGetRelativeWeaponSizeHook","Deflect arrow weapon size bug");
	CreateHook(0x59F2E0,CNWSItemPropertyHandler__ApplyHolyAvenger_Hook, (PVOID*)&CNWSItemPropertyHandler__ApplyHolyAvenger, "DisableHolyAvengerHook","ApplyHolyAvenger function");
	CreateHook(0x59FC80,CNWSItemPropertyHandler__RemoveHolyAvenger_Hook, (PVOID*)&CNWSItemPropertyHandler__RemoveHolyAvenger, "DisableHolyAvengerHook","Holy avenger weapon enhancement bug");
	CreateHook(0x4A4F20,CNWSCreature__RestoreItemProperties_Hook,(PVOID*)&CNWSCreature__RestoreItemProperties, "DisableItemProperties", "Correcting losing spelluses when unequipping item with bonus spell slots #1");
	CreateHook(0x4FE800,CNWSItem__RemoveItemProperties_Hook,(PVOID*)&CNWSItem__RemoveItemProperties, "DisableItemProperties", "Correcting losing spelluses when unequipping item with bonus spell slots #2");
	
	CreateHook(0x4A5080,CNWSCreature__ToggleMode_Hook, (PVOID*)&CNWSCreature__ToggleMode, "DisableToggleModeHook","ToggleMode function");
	CreateHook(0x4BB4D0,CNWSCreature__SetCombatMode_Hook, (PVOID*)&CNWSCreature__SetCombatMode, "DisableToggleModeHook","Flurry of blows modification");

	CreateHook(0x489890,CNWSCreatureStats__GetSpellResistance_Hook,(PVOID*)&CNWSCreatureStats__GetSpellResistance, "DisableSRHook", "Spell Resistance override");

	CreateHook(0x577DF0,CNWVirtualMachineCommands__ExecuteCommandApplyEffectOnObject_Hook,(PVOID*)&CNWVirtualMachineCommands__ExecuteCommandApplyEffectOnObject, "DisableApplyEffectOnObject", "ApplyEffectToObject extension");
	CreateHook(0x570D20,CNWVirtualMachineCommands__ExecuteCommandGetRacialType_Hook,(PVOID*)&CNWVirtualMachineCommands__ExecuteCommandGetRacialType, "DisableRacialType", "GetRacialType extension");
	CreateHook(0x5700A0,CNWVirtualMachineCommands__ExecuteCommandGetEffectSubType_Hook,(PVOID*)&CNWVirtualMachineCommands__ExecuteCommandGetEffectSubType, "DisableEffects", "Enabling effect modifications and additional effect information functions");
	CreateHook(0x57F5E0,CNWVirtualMachineCommands__ExecuteCommandVersusEffect_Hook,(PVOID*)&CNWVirtualMachineCommands__ExecuteCommandVersusEffect, "DisableEffects", "Enabling VersusEffect to work with EffectDamageShield");
	CreateHook(0x4AB140,CNWSCreature__GetTotalEffectBonus_Hook,(PVOID*)&CNWSCreature__GetTotalEffectBonus, "DisableGetTotalEffectBonus", "Enabling uncapped EffectAttackIncrease");
	CreateHook(0x46ED40,CNWSCreatureStats__GetBaseAttackBonus_Hook,(PVOID*)&CNWSCreatureStats__GetBaseAttackBonus, "DisableGetBaseAttackBonus", "Enabling EffectModifyBAB");
	CreateHook(0x45B990,CServerExoAppInternal__RemovePCFromWorld_Hook,(PVOID*)&CServerExoAppInternal__RemovePCFromWorld, "DisablePlayerLeave", "OnClientLeave extension");
	CreateHook(0x454610,CServerExoAppInternal__ValidateCreateServerCharacter_Hook,(PVOID*)&CServerExoAppInternal__ValidateCreateServerCharacter, "DisableValidateServerCharacter", "Disallow New Characters server option");
	
	CreateHook(0x4E8C00,CGameEffect__SetCreator_Hook,(PVOID*)&CGameEffect__SetCreator, "DisableEffectCasterLevel" , "Effect caster level bug");
	CreateHook(0x48B920,CNWSCreatureStats__AdjustSpellUsesPerDay_Hook,(PVOID*)&CNWSCreatureStats__AdjustSpellUsesPerDay, "DisableAdjustSpellUses", "Spontaneous casters spell uses correction.");
	CreateHook(0x48E850,CNWSCreatureStats__ComputeFeatBonuses_Hook, (PVOID*)&CNWSCreatureStats__ComputeFeatBonuses, "DisableComputeFeatBonuses","Fixed losing spellslots/spelluses upon login from Great Ability feats.");
	CreateHook(0x499500,CNWSCreature__ReadItemsFromGff_Hook, (PVOID*)&CNWSCreature__ReadItemsFromGff, "DisableReadItemsFromGff","Fixed losing spelluses upon login from multiple items with charisma bonus.");
	CreateHook(0x496CE0,CNWSCreature__EventHandler_Hook,(PVOID*)&CNWSCreature__EventHandler, "DisableEventHandler" , "OnHitSpellCast bugfix and OnAttacked/OnDamaged events for player");
	CreateHook(0x465B30,CNWSStore__SellItem_Hook,(PVOID*) &CNWSStore__SellItem, "DisableSellItem", "Buying with full inventory bug");
	CreateHook(0x484F50,CNWSCreatureStats__LevelDown_Hook,(PVOID*) &CNWSCreatureStats__LevelDown, "DisableLevelDownHook", "Fixed combat info update after level down");
	CreateHook(0x4847F0,CNWSCreatureStats__LevelUp_Hook,(PVOID*) &CNWSCreatureStats__LevelUp, "DisableLevelUpHook", "Support for spontaneous non-learner custom spellcaster class.");
	CreateHook(0x4E5A60,CNWSObject__GetIsPCDying_Hook,(PVOID*)&CNWSObject__GetIsPCDying, "DisablePCDying", "Enabling immunity to dying");
	CreateHook(0x4A6ED0, CNWSCreature__GetMaxHitPoints_Hook,(PVOID*) &CNWSCreature__GetMaxHitPoints, "DisableHitPoints", "Enabling to modify hitpoints");
	CreateHook(0x548220,CNWSCreature__GetAmmunitionAvailable_Hook, (PVOID*)&CNWSCreature__GetAmmunitionAvailable, "DisableRangedWeapons","Enabling custom ranged weapons");
	CreateHook(0x548100,CNWSCreature__ResolveAmmunition_Hook, (PVOID*)&CNWSCreature__ResolveAmmunition, "DisableRangedWeapons","Enabling Boomerang item property");
	CreateHook(0x490690,CNWSCreature__SetActivity_Hook, (PVOID*)&CNWSCreature__SetActivity, "DisableSetActivityHook","Defensive stance not canceling properly");
	CreateHook(0x4FA850,CNWSEffectListHandler__OnApplyDefensiveStance_Hook,(PVOID*)&CNWSEffectListHandler__OnApplyDefensiveStance, "DisableDefensiveStance", "Defensive Stance feat softcoding");
	CreateHook(0x474710,CNWSCreatureStats__ResolveSpecialAttackDamageBonus_Hook, (PVOID*)&CNWSCreatureStats__ResolveSpecialAttackDamageBonus, "DisableSpecialAttacks","Crash exploit no#1");
	CreateHook(0x4A8800,CNWSCreature__StartBarter_Hook, (PVOID*)&CNWSCreature__StartBarter, "DisableStartBarterHook","Crash exploit no#2");
	CreateHook(0x5017A0,CNWSItem__GetMinEquipLevel_Hook, (PVOID*)&CNWSItem__GetMinEquipLevel, "DisableGetMinEquipLevelHook", "Item level restriction");//run only at ILR=1 when acquire/move curson onto item/examine
	CreateHook(0x4DFA60,CNWSObject__ClearAllPartyInvalidActions_Hook, (PVOID*)&CNWSObject__ClearAllPartyInvalidActions, "DisableClearAllPartyInvalidActionsHook", "Party actions canceling");
	CreateHook(0x5A96F0,CNWSTrigger__GetCanFireTrapOnObject_Hook, (PVOID*)&CNWSTrigger__GetCanFireTrapOnObject, "DisableFireTrapHook", "Flying creatures immunity to traps feature");
	CreateHook(0x489E50,CNWSCreatureStats__GetFavoredEnemyBonus_Hook,(PVOID*)&CNWSCreatureStats__GetFavoredEnemyBonus, "DisableFavoredEnemyHook", "Favored Enemy calculation");
	CreateHook(0x493120,CNWSCreature__AddPickPocketAction_Hook,(PVOID*)&CNWSCreature__AddPickPocketAction, "DisableAddPickPocketAction", "Pickpocket skill softcoding");
	CreateHook(0x4A5D90,CNWSCreature__AddTauntActions_Hook,(PVOID*)&CNWSCreature__AddTauntActions, "DisableAddTauntActions", "Taunt skill softcoding");
	CreateHook(0x4A5CA0,CNWSCreature__AddAnimalEmpathyAction_Hook,(PVOID*)&CNWSCreature__AddAnimalEmpathyAction, "DisableAddAnimalEmpathyActions", "Animal empathy skill softcoding");
	CreateHook(0x4B1F70,CNWSCreature__LearnScroll_Hook,(PVOID*)&CNWSCreature__LearnScroll, "DisableLearnScroll", "Learn scroll sofcoding");
	CreateHook(0x49E180,CNWSCreature__GetMovementRateFactor_Hook,(PVOID*)&CNWSCreature__GetMovementRateFactor, "DisableSpeed", "Enabling modifications into speed");

	CreateHook(0x47E020,CNWSCreatureStats__GetBaseReflexSavingThrow_Hook,(PVOID*)&CNWSCreatureStats__GetBaseReflexSavingThrow, "DisableSavingThrows", "Enabling modifications into reflex saving throw");
	CreateHook(0x47DD90,CNWSCreatureStats__GetBaseFortSavingThrow_Hook,(PVOID*)&CNWSCreatureStats__GetBaseFortSavingThrow, "DisableSavingThrows", "Enabling modifications into fortitude saving throw");
	CreateHook(0x47DED0,CNWSCreatureStats__GetBaseWillSavingThrow_Hook,(PVOID*)&CNWSCreatureStats__GetBaseWillSavingThrow, "DisableSavingThrows", "Enabling modifications into will saving throw");

	CreateHook(0x52FA00,CNWSCombatRound__StartCombatRound_Hook,(PVOID*)&CNWSCombatRound__StartCombatRound, "DisableStartCombatRound", "Enabling combat round modifications.");
	CreateHook(0x530E40,CNWSCombatRound__InitializeNumberOfAttacks_Hook,(PVOID*)&CNWSCombatRound__InitializeNumberOfAttacks,"DisableInitializeNumberOfAttacks","Enabling number of attacks modifications.");

	//special attacks
	CreateHook(0x549FC0,CNWSCreature__ResolveMeleeSpecialAttack_Hook,(PVOID*)&CNWSCreature__ResolveMeleeSpecialAttack,"DisableSpecialAttacks","Enabling custom special attacks #1");
	CreateHook(0x547A50,CNWSCreature__ResolveRangedSpecialAttack_Hook,(PVOID*)&CNWSCreature__ResolveRangedSpecialAttack,"DisableSpecialAttacks","Enabling custom special attacks #2");
	CreateHook(0x4744F0,CNWSCreatureStats__ResolveSpecialAttackAttackBonus_Hook, (PVOID*)&CNWSCreatureStats__ResolveSpecialAttackAttackBonus, "DisableSpecialAttacks","Enabling custom special attacks #3");
	CreateHook(0x4A3700,CNWSCreature__UseFeat_Hook,(PVOID*)&CNWSCreature__UseFeat,"DisableSpecialAttacks","Enabling custom special attacks #4");
	
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
	fprintf_s(logFile, "o Hooking neccessary functions to fix spell slots in polymorph:\n");
	int ok = 0;
	ok+= CreateHook(0x4F76D0,CNWSEffectListHandler__OnApplyPolymorph_Hook, (PVOID*)&CNWSEffectListHandler__OnApplyPolymorph, "DisableSpellSlotsInPolymorphHook","OnApplyPolymorph function");
	ok+= CreateHook(0x4F78E0,CNWSEffectListHandler__OnRemovePolymorph_Hook, (PVOID*)&CNWSEffectListHandler__OnRemovePolymorph, "DisableSpellSlotsInPolymorphHook","OnRemovePolymorph function");
	ok+= CreateHook(0x59D590,CNWSItemPropertyHandler__ApplyBonusSpellOfLevel_Hook, (PVOID*)&CNWSItemPropertyHandler__ApplyBonusSpellOfLevel, "DisableSpellSlotsInPolymorphHook","ApplyBonusSpellOfLevel function");
	ok+= CreateHook(0x59D610,CNWSItemPropertyHandler__RemoveBonusSpellOfLevel_Hook, (PVOID*)&CNWSItemPropertyHandler__RemoveBonusSpellOfLevel, "DisableSpellSlotsInPolymorphHook","RemoveBonusSpellOfLevel function");
	ok+= CreateHook(0x498AB0,CNWSCreature__UpdateAttributesOnEffect_Hook, (PVOID*)&CNWSCreature__UpdateAttributesOnEffect, "DisableSpellSlotsInPolymorphHook","UpdateAttributtesOnEffect function");
	ok+= CreateHook(0x46C630,CNWSCreatureStats_ClassInfo__SetNumberMemorizedSpellSlots_Hook, (PVOID*)&CNWSCreatureStats_ClassInfo__SetNumberMemorizedSpellSlots, "DisableSpellSlotsInPolymorphHook","SetNumberMemorizedSpellSlots function");
	fprintf_s(logFile, ok == 6 ? "SUCCESS.\n" : "ERROR, %i Hooks failed, this feature might not work properly!\n");

	//feat uses
	fprintf_s(logFile, "o Hooking neccessary functions to fix feat uses after relogging/reloading: ");
	ok = 0;
	ok+= CreateHook(0x47F8C0,CNWSCreatureStats__GetFeatTotalUses_Hook,(PVOID*)&CNWSCreatureStats__GetFeatTotalUses, "DisableFeatUses", "Enabling Gruumsh rage stacking");
	ok+= CreateHook(0x47EF10,CNWSCreatureStats__GetFeatRemainingUses_Hook,(PVOID*)&CNWSCreatureStats__GetFeatRemainingUses, "DisableFeatUses", "Enabling modify number of feat uses");
	ok+= CreateHook(0x47EE20,CNWSCreatureStats__SetFeatRemainingUses_Hook,(PVOID*)&CNWSCreatureStats__SetFeatRemainingUses, "DisableFeatUses", "Enabling modify number of feat uses");
	ok+= CreateHook(0x4801D0,CNWSCreatureStats__ResetFeatRemainingUses_Hook,(PVOID*)&CNWSCreatureStats__ResetFeatRemainingUses, "DisableFeatUses", "Enabling modify number of feat uses");	
	ok+= CreateHook(0x480240,CNWSCreatureStats__IncrementFeatRemainingUses_Hook,(PVOID*)&CNWSCreatureStats__IncrementFeatRemainingUses, "DisableFeatUses", "Enabling modify number of feat uses");
	ok+= CreateHook(0x480200,CNWSCreatureStats__DecrementFeatRemainingUses_Hook,(PVOID*)&CNWSCreatureStats__DecrementFeatRemainingUses, "DisableFeatUses", "Enabling modify number of feat uses");
	fprintf_s(logFile, ok == 6 ? "SUCCESS.\n" : "ERROR, %i Hooks failed, this feature might not work properly!\n");

	//development

	fprintf(logFile,"\n");
	fflush(logFile);
}

void Hook_SpontaneousSpell()//note, while in singleplayer, the SpontaneouslyCast field is only 0 or 1, in server version this field match with 2da, thus the whole code is much simpler
{
	__asm leave
	__asm mov test1, al//class
	__asm mov eax, [esp+84h]//spell id
	__asm mov test32, eax

	test33 = NWN_Rules->m_pSpellArray->GetSpell(test32)->m_bSpontaneouslyCast;

	if(test33 > 0 && ((test1 == 2 && test33 == 1) || test33 == test1))
	{
		Hook_ret = 0x53F570;
	}
	else
	{
		Hook_ret = 0x53F635;
	}

	__asm jmp Hook_ret
}

void Hook_DevastatingCriticalRanged()
{
	__asm leave
	__asm mov orig_ebx, ebx
	__asm mov orig_ecx, ecx
	__asm mov orig_edx, edx
	__asm mov orig_eax, eax
	__asm mov DWORD PTR target, edi
	__asm mov DWORD PTR self, ebp

	if(self != NULL && target != NULL && NWN_VirtualMachine->Runscript(&script_devast,self->obj.obj_generic.obj_id,1))
	{
		if(target->obj.GetDead())
		{
			Hook_ret = 0x54E01E;
		}
		else
		{
			Hook_ret = 0x54E0DA;
		}
	}
	else
	{
		Hook_ret = 0x54E0A4;
	}

	__asm mov eax, orig_eax
	__asm mov ebx, orig_ebx
	__asm mov ecx, orig_ecx
	__asm mov edx, orig_edx
	__asm jmp Hook_ret
}

void Hook_DevastatingCriticalMelee()
{
	__asm leave
	__asm mov orig_ebx, ebx
	__asm mov orig_ecx, ecx
	__asm mov orig_edx, edx
	__asm mov orig_eax, eax
	__asm mov DWORD PTR target, ebx
	__asm mov DWORD PTR self, edi
	
	if(self != NULL && target != NULL && NWN_VirtualMachine->Runscript(&script_devast,self->obj.obj_generic.obj_id,1))
	{
		if(target->obj.GetDead())
		{
			__asm mov [esi+40h], 1
			Hook_ret = 0x54D610;
		}
		else
		{
			Hook_ret = 0x54D6BC;
		}
	}
	else
	{
		Hook_ret = 0x54D692;
	}

	__asm mov eax, orig_eax
	__asm mov ebx, orig_ebx
	__asm mov ecx, orig_ecx
	__asm mov edx, orig_edx
	__asm jmp Hook_ret
}

void Hook_AssassinDeathAttack()
{
	__asm leave
	__asm mov DWORD PTR self, esi
	__asm mov DWORD PTR target, edi

	if(self != NULL && target != NULL && !target->cre_combat_state && self->cre_stats->HasFeat(455))
	{
		target->cre_combat_state = 1;//disables multiple death attack onhits in first flurry
		if(!NWN_VirtualMachine->Runscript(&script_dthattk,self->obj.obj_generic.obj_id,1))
		{
			//Hook_ret = 0x745840;//doesnt work anyway
		}
	}
	__asm mov eax, 0x54CD29
	__asm jmp eax
}

void Hook_SpecAttacks1()//CNWSCreature::ResolveMeleeSpecialAttack
{
	__asm leave
	__asm mov eax, 0x54A078
	__asm jmp eax
}

void Hook_SpecAttacks2()//CNWSCreature::ResolveRangedSpecialAttack
{
	__asm leave
	__asm mov eax, 0x547AD3
	__asm jmp eax
}

void Hook_SpecAttacks3()//CNWSCreature::ResolveAttackRoll
{
	__asm leave
	__asm mov test1, bl//tohitroll
	__asm mov al, [esp+14h]
	__asm mov Hook_int8, al//tohitmod
	__asm mov [esi+10h], al
	__asm mov al, [esp+18h]//ac
	__asm mov test3, al
	__asm mov al, [esi+0Eh]//roll override
	__asm mov Hook_uint8, al

	if(Hook_uint8 > 0) 
	{	
		test1 = Hook_uint8;
		__asm mov bl, test1
	}
	else __asm mov [esi+0Eh], bl

	if(test1+Hook_int8 >= test3)
	{
		__asm mov ecx, 1
	}

	__asm mov eax, 0x54B9B1
	__asm jmp eax
}

void Hook_SpecAttacks4()//CNWSCreature::ResolveAttackRoll
{
	__asm leave
	__asm mov test1, al//new threat roll
	__asm mov al, [esp+14h]
	__asm mov Hook_int8, al//tohitmod
	__asm mov al, [esp+18h]//ac
	__asm mov test3, al
	__asm mov al, [esi+0Fh]//threat roll override
	__asm mov Hook_uint8, al
	__asm mov [esi+48h], 1

	if(Hook_uint8 > 0) 
	{	
		test1 = Hook_uint8;
		__asm mov bl, test1
	}
	else
	{
		__asm mov al, test1
		__asm mov [esi+0Fh], al
	}

	if(test1+Hook_int8 >= test3)
	{
		__asm mov eax, 0x54BB2B//crit
		__asm jmp eax
	}
	else
	{
		__asm mov eax, 0x54BC75//not a crit
		__asm jmp eax
	}
}

void Hook_SneakAttackCalculation()
{
	__asm leave
	__asm mov ebx, 0Ah
	__asm mov DWORD PTR stats, esi

	if(stats != NULL && (stats->cs_original->cre_combat_round->GetAttack(stats->cs_original->cre_combat_round->CurrentAttack)->m_bSneakAttack || (stats->HasFeat(834) && stats->cs_original->cre_combat_round->GetAttack(stats->cs_original->cre_combat_round->CurrentAttack)->m_bDeathAttack)))
	{
		__asm mov eax, 0x476CE3
	}
	else
	{
		__asm mov eax, 0x4771B6
	}
	__asm jmp eax
}

void Hook_SneakAttackImmunity()
{
	__asm leave
	__asm mov DWORD PTR self, edi
	__asm mov DWORD PTR target, esi

	if(self != NULL && target != NULL)
	{
		if(!target->cre_stats->GetEffectImmunity(IMMUNITY_TYPE_SNEAK_ATTACK,self))//sneak immunity
		{
			if(NoCriticalImmunity || !target->cre_stats->GetEffectImmunity(IMMUNITY_TYPE_CRITICAL_HIT,self))//critical immunity
			{
				//if(!target->cre_stats->HasFeat(896))//PM Deathless Mastery
				{
					__asm mov eax, 0x54C20D
					__asm jmp eax
					return;
				}
			}
		}
	}
	__asm mov eax, 0x54C221
	__asm jmp eax
}

void Hook_DeathAttackImmunity()
{
	__asm leave
	__asm mov DWORD PTR self, edi
	__asm mov DWORD PTR target, esi

	if(self != NULL && target != NULL)
	{
		if(!target->cre_stats->GetEffectImmunity(IMMUNITY_TYPE_SNEAK_ATTACK,self))//sneak immunity
		{
			if(NoCriticalImmunity || !target->cre_stats->GetEffectImmunity(IMMUNITY_TYPE_CRITICAL_HIT,self))//critical immunity
			{
				//if(!target->cre_stats->HasFeat(896))//PM Deathless Mastery
				{
					__asm mov eax, 0x54C750
					__asm jmp eax
					return;
				}
			}
		}
	}
	__asm mov eax, 0x54C768
	__asm jmp eax
}

void Hook_HealersKit()
{
	__asm leave
	__asm mov DWORD PTR self, esi
	__asm mov DWORD PTR target, edi
	
	if(self != NULL && target != NULL)
	{
		self->obj.obj_last_spell_target = target->obj.obj_conv_object_1;
		self->cre_item_spell_item = target->obj.obj_portrait_id;
		NWN_VirtualMachine->Runscript(&script_healkit,self->obj.obj_generic.obj_id,1);
	}
	__asm mov eax, 0x4CAB98
	__asm jmp eax
}

void Hook_CombatMode1()
{
	__asm leave
	__asm mov eax, 0x53D728
	__asm jmp eax
}

void Hook_CombatMode2()
{
	__asm leave
	__asm mov eax, 0x53D134
	__asm jmp eax
}

void Hook_CombatMode3()
{
	__asm leave
	__asm mov eax, 0x547478
	__asm jmp eax
}

void Hook_MindImmunity()
{
	__asm leave
	__asm mov test1, al
	if(test1)
	{
		__asm mov eax, 0x4F0F3D
	}
	else if(ParalysisIgnoreMindImmunity)
	{
		__asm mov eax, 0x4F1756
	}
	else
	{
		_asm mov eax, 0x4F15FD
	}
	__asm jmp eax
}

float myFloat;
void Hook_Speed()
{
	__asm leave
	__asm mov Hook_integer, eax
	__asm mov target, ebx

	myFloat = target->m_fMovementRateFactor*((float)Hook_integer/100);
	target->SetMovementRateFactor(myFloat);

	__asm mov eax, 0x4F267B
	__asm jmp eax
}

void Hook_SpellSlotsCrash()
{
	__asm leave
	__asm inc edi
	__asm mov test32, edi
	__asm mov eax, [esi+24h]
	__asm mov test33, eax
	
	if(test32 < test33)
	{
		__asm mov eax, 0x442121
	}
	else
	{
		__asm mov eax, 0x4421C5
	}

	__asm jmp eax
}

void Hook_SpellSlotsCrash2()//0x4420EE
{
	__asm leave
	__asm inc edi
	__asm mov test32, edi
	__asm mov eax, [esi]
	__asm mov test33, eax

	if(test32 < test33)
	{
		__asm mov eax, 0x4420C5
	}
	else
	{
		__asm mov eax, 0x442102
	}

	__asm jmp eax
}	         

void Hook_CustomToken()
{
	__asm leave
	Hook_ret = 0x576EC9;
	__asm jmp Hook_ret
}

void Hook_Unpossess()//0x740270 - CNWSCreature::ResolveAttack
{
	__asm leave
	Hook_ret = 0x5476A8;
	__asm jmp Hook_ret
}

void Hook_GetUnarmedDamageDice()//0x47090F - CNWSCreatureStats::GetUnarmedDamageDice
{
	__asm leave
	__asm mov test32, ebp//monk lvl
	__asm mov test33, edi//shou lvl
	if(test33 >= 5 && test32 < 11)
	{
		__asm mov eax, 2
	}
	Hook_ret = 0x470937;
	__asm jmp Hook_ret
}

void Hook_OnClientExit()//0x45BB7B - CServerExoAppInternal::RemovePCFromWorld
{
	__asm leave
	Hook_ret = 0x45BB9A;
	__asm jmp Hook_ret
}

void Hook_ModuleEvents()//0x4D224E - CNWSModule::EventHandler
{
	__asm leave
	__asm pop eax
	__asm pop ebx
	__asm mov test32, eax
	__asm mov DWORD PTR script, esi
	__asm mov ax, [edi]
	__asm mov orig_eax, eax

	//fprintf_s(logFile, "o Hook_ModuleEvents, test1: %i, %i, %s, %i\n",test32,test33,script->text,orig_eax);fflush(logFile);
	
	if(orig_eax == 35)//OnRest
	{
		NWN_VirtualMachine->Runscript(&script_rest,test32);
	}
	else if(orig_eax == 39)//equip
	{
		NWN_VirtualMachine->Runscript(&script_equ,test32);
	}
	else if(orig_eax == 19)
	{
		NWN_VirtualMachine->Runscript(&script_aqu,test32);
	}
	else if(orig_eax == 20)
	{
		NWN_VirtualMachine->Runscript(&script_unaqu,test32);
	}
	else if(orig_eax == 32)
	{
		NWN_VirtualMachine->Runscript(&script_dying,test32);
	}
	else if(orig_eax == 10)
	{
		NWN_VirtualMachine->Runscript(&script_death,test32);
	}
	else if(orig_eax == 33)
	{
		NWN_VirtualMachine->Runscript(&script_respawn,test32);
	}
	else if(orig_eax == 14)
	{
		NWN_VirtualMachine->Runscript(&script_enter,test32);
	}
	else if(orig_eax == 18)
	{
		NWN_VirtualMachine->Runscript(&script_act,test32);
	}
	else if(orig_eax == 37)
	{
		NWN_VirtualMachine->Runscript(&script_lvup,test32);
	}
	else if(orig_eax == 38)
	{
		NWN_VirtualMachine->Runscript(&script_abort,test32);
	}
	else if(orig_eax == 11)
	{
		NWN_VirtualMachine->Runscript(&script_user,test32);
	}
	else if(orig_eax == 15)
	{
		NWN_VirtualMachine->Runscript(&script_leave,test32);
	}

	module = NWN_AppManager->app_server->srv_internal->GetModule();
	
	if(module && module->mod_vartable.GetInt(bypass_event) == 1)
	{
		module->mod_vartable.DestroyInt(bypass_event);
	}
	else
	{
		NWN_VirtualMachine->Runscript(script,test32);
	}

	Hook_ret = 0x4D225A;
	__asm jmp Hook_ret
}

void Hook_OnPlayerUnEquip()//0x49637D - CNWSCreature::UnequipItem
{
	__asm leave
	__asm mov DWORD PTR module, eax

	//fprintf_s(logFile, "o Hook_Unequip, test1: %i, %s\n",module->obj_id,module->mod_scripts[16].text);fflush(logFile);

	NWN_VirtualMachine->Runscript(&script_unequ,module->obj_id);
	if(module && module->mod_vartable.GetInt(bypass_event) == 1)
	{
		module->mod_vartable.DestroyInt(bypass_event);
	}
	else
	{
		NWN_VirtualMachine->Runscript(&module->mod_scripts[16],module->obj_id);
	}

	Hook_ret = 0x496394;
	__asm jmp Hook_ret
}

void Hook_OnPlayerChat()//0x534F70 - CNWSMessage::HandlePlayerToServerChatMessage
{
	__asm leave
	__asm mov DWORD PTR module, esi

	//fprintf_s(logFile, "o Hook_Chat, test1: %i, %s\n",module->obj_id,module->mod_scripts[17].text);fflush(logFile);

	NWN_VirtualMachine->Runscript(&script_chat,module->obj_id);
	if(module && module->mod_vartable.GetInt(bypass_event) == 1)
	{
		module->mod_vartable.DestroyInt(bypass_event);
	}
	else
	{
		NWN_VirtualMachine->Runscript(&module->mod_scripts[17],module->obj_id);
	}

	Hook_ret = 0x534F88;
	__asm jmp Hook_ret
}

void Hook_AOO1()//0x4A2CBE - CNWSCreature::BroadcastAttackOfOpportunity
{
	__asm leave
	__asm mov orig_ebx, ebx
	__asm mov DWORD PTR self, esi
	__asm mov edx, [ebx+4h]
	__asm mov test32, edx

	//fprintf_s(logFile, "o Hook_AOO1, target: %x, self: %x\n",test32,self->obj.obj_generic.obj_id);fflush(logFile);
	
	self->obj.obj_vartable.SetObject(aoo_target,test32);
	NWN_VirtualMachine->Runscript(&script_aoo,self->obj.obj_generic.obj_id);
	if(self->obj.obj_vartable.GetInt(aoo_bypass) == 1)
	{
		self->obj.obj_vartable.DestroyInt(aoo_bypass);
		Hook_ret = 0x4A2D10;
	}
	else if(self->cre_attempted_target == OBJECT_INVALID)
	{
		Hook_ret = 0x4A2CCA;
	}
	else
	{
		Hook_ret = 0x4A2CDB;
	}

	__asm mov ebx, orig_ebx
	__asm jmp Hook_ret
}

void Hook_AOO2()//0x4A3025 - CNWSCreature::BroadcastAttackOfOpportunity
{
	__asm leave
	__asm mov orig_ebx, ebx
	__asm mov DWORD PTR self, esi
	__asm mov edx, [ebx+4h]
	__asm mov test32, edx

	//fprintf_s(logFile, "o Hook_AOO2, target: %x, self: %x\n",test32,self->obj.obj_generic.obj_id);fflush(logFile);
	
	self->obj.obj_vartable.SetObject(aoo_target,test32);
	NWN_VirtualMachine->Runscript(&script_aoo,self->obj.obj_generic.obj_id);
	if(self->obj.obj_vartable.GetInt(aoo_bypass) == 1)
	{
		self->obj.obj_vartable.DestroyInt(aoo_bypass);
		Hook_ret = 0x4A3071;
	}
	else if(self->cre_attempted_target == OBJECT_INVALID)
	{
		Hook_ret = 0x4A3031;
	}
	else
	{
		Hook_ret = 0x4A3042;
	}

	__asm mov ebx, orig_ebx
	__asm jmp Hook_ret
}

void Hook_DamageReduction()//0x4EB93E - CNWSEffectListHandler::OnApplyDamage
{
	__asm leave
	__asm mov orig_eax, eax
	__asm mov eax, [esp+0ACh]
	__asm mov DWORD PTR Hook_effect, eax

	test32 = Hook_effect->GetInteger(16);

	__asm mov edx, [esi]
	__asm push 0
	__asm push 0
	__asm push test32
	__asm push orig_eax
	__asm push ebp
	__asm mov ecx, esi

	__asm mov Hook_ret, 0x4EB949
	__asm jmp Hook_ret
}

void Hook_FeatUses()//0x479CF6 - CNWSCreatureStats::ReadStatsFromGFF
{
	__asm leave
	Hook_ret = 0x479D27;
	__asm jmp Hook_ret
}

void Hook_ImmunityMind1()//CNWSEffectListHandler::OnApplySetState
{
	__asm leave
	Hook_ret = 0x4F15FD;
	__asm jmp Hook_ret
}

void Hook_ImmunityMind2()//CNWSEffectListHandler::OnApplySetState
{
	__asm leave
	Hook_ret = 0x4F1756;
	__asm jmp Hook_ret
}

void Hook_ImmunityPoison()//CNWSEffectListHandler::OnApplyPoison
{
	__asm leave
	__asm mov ebp, eax
	Hook_ret = 0x4F36D1;
	__asm jmp Hook_ret
}

void Hook_ImmunityDisease()//CNWSEffectListHandler::OnApplyDisease
{
	__asm leave
	Hook_ret = 0x4F3FB2;
	__asm jmp Hook_ret
}

void Hook_ImmunityCritical()//CNWSCreature::ResolveAttackRoll
{
	__asm leave
	__asm mov DWORD PTR self, ebp
	NWN_VirtualMachine->Runscript(&script_critical,self->obj.obj_generic.obj_id);
	Hook_ret = 0x54BC7B;
	__asm jmp Hook_ret
}

void Hook_ELC1()//0x434243 - CNWSPlayer::ValidateCharacter - number of spells learned
{//todo change max spells learned value
	__asm leave
	__asm mov orig_ebx, ebx
	__asm mov orig_ecx, ecx
	__asm mov orig_edx, edx
	__asm mov test1, al
	__asm mov DWORD PTR stats, edi

	fprintf_s(logFile, "o Hook_ELC1, cls_id: %i\n",test1);fflush(logFile);

	if(cls_cast_type[test1] & CAST_TYPE_RESTRICTED_SPELLBOOK)
	{
		hook_Class = &(NWN_Rules->m_lstClasses[test1]);
		for(test2=0;test2<stats->cs_classes_len;test2++)
		{
			if(stats->cs_classes[test2].cl_class == test1) break;
		}
		test2 = stats->cs_classes[test2].cl_level-1;

		test32 = !test2 ? 3 : 2;
		test33 = !test2;
		if(cls_spopt_2da[test1] && cls_spopt_2da[test1]->GetINTEntry_intcol(test2,1,&Hook_integer) && Hook_integer > -1 && (unsigned int)Hook_integer < test32)
		{
			test32 = Hook_integer;
		}
		if(cls_spopt_2da[test1] && cls_spopt_2da[test1]->GetINTEntry_intcol(test2,3,&Hook_integer) && Hook_integer > -1 && (unsigned int)Hook_integer < test33)
		{
			test33 = Hook_integer;
		}
		test3 = hook_Class->m_nPrimaryAbility;
		if(test3 == ABILITY_STRENGTH)
		{
			test1 = stats->cs_str_mod;
		}
		else if(test3 == ABILITY_DEXTERITY)
		{
			test1 = stats->cs_dex_mod;
		}
		else if(test3 == ABILITY_CONSTITUTION)
		{
			test1 = stats->cs_con_mod;
		}
		else if(test3 == ABILITY_WISDOM)
		{
			test1 = stats->cs_wis_mod;
		}
		else if(test3 == ABILITY_CHARISMA)
		{
			test1 = stats->cs_cha_mod;
		}
		else
		{
			test1 = stats->cs_int_mod;
		}

		if(test33 && test1 > 0)
		{
			test32+= test1;
		}
		
		__asm mov eax, test32
		__asm mov [esp+5Ch], eax//push max number of spells learned
	}

	Hook_ret = 0x4342AD;

	__asm mov ebx, orig_ebx
	__asm mov ecx, orig_ecx
	__asm mov edx, orig_edx
	__asm jmp Hook_ret
}

void Hook_ELC2()//0x434440 - CNWSPlayer::ValidateCharacter - number of spells learned2
{
	__asm leave
	__asm mov orig_ebx, ebx
	__asm mov orig_ecx, ecx
	__asm mov orig_edx, edx
	__asm mov test1, cl

	fprintf_s(logFile, "o Hook_ELC2, cls_id: %i\n",test1);fflush(logFile);

	if(cls_cast_type[test1] & CAST_TYPE_RESTRICTED_SPELLBOOK)
	{
		Hook_ret = 0x434444;
	}
	else
	{
		Hook_ret = 0x43445D;
	}

	__asm mov ebx, orig_ebx
	__asm mov ecx, orig_ecx
	__asm mov edx, orig_edx
	__asm jmp Hook_ret
}

void Hook_SpellcasterType7()//480408 - CNWSCreatureStats::AddKnownSpell
{
	__asm leave
	__asm mov test1, al
	__asm mov orig_eax, eax
	__asm mov orig_ebx, ebx
	__asm mov orig_ecx, ecx
	__asm mov orig_edx, edx

	//fprintf(logFile, "o Hook_SpellcasterType7: cls_id: %i\n",test1);fflush(logFile);
	if(cls_cast_type[test1] & CAST_TYPE_SPONTANEOUS)
	{
		Hook_ret = 0x480410;
	}
	else
	{
		Hook_ret = 0x480421;
	}

	__asm mov eax, orig_eax
	__asm mov ebx, orig_ebx
	__asm mov ecx, orig_ecx
	__asm mov edx, orig_edx
	__asm jmp Hook_ret
}

void Hook_SpellcasterType13a()//0x482AA5 - CNWSCreatureStats::ReadySpellLevel
{
	__asm leave
	__asm mov test1, al
	__asm mov orig_eax, eax
	__asm mov orig_ebx, ebx
	__asm mov orig_ecx, ecx
	__asm mov orig_edx, edx

	//fprintf(logFile, "o Hook_SpellcasterType13a: cls_id: %i\n",test1);fflush(logFile);
	if(cls_cast_type[test1] & CAST_TYPE_SPONTANEOUS)
	{
		Hook_ret = 0x482B4E;
	}
	else
	{
		Hook_ret = 0x482ADD;
	}

	__asm mov eax, orig_eax
	__asm mov ebx, orig_ebx
	__asm mov ecx, orig_ecx
	__asm mov edx, orig_edx
	__asm jmp Hook_ret
}

void Hook_SpellcasterType13b()//0x482D02 - CNWSCreatureStats::UnReadySpell - without this casting a spontaneous spell fails
{
	__asm leave
	__asm mov test1, al
	__asm mov [esp+24h], dl
	__asm mov DWORD PTR stats, ebp
	__asm mov orig_eax, eax
	__asm mov orig_ebx, ebx
	__asm mov orig_ecx, ecx
	__asm mov orig_edx, edx

	Hook_ret = 0x482DD4;

	if(orig_ebx < stats->cs_classes_len)
	{
		test2 = stats->cs_classes[orig_ebx].cl_level-1;
		hook_Class = &(NWN_Rules->m_lstClasses[test1]);
	
		//fprintf(logFile, "o Hook_SpellcasterType13b: cls_id: %i, cls_pos: %i, cls_lvl: %i, sp_lvl: %i, spell_levels: %i\n",test1,orig_ebx,test2,orig_edx,hook_Class->NumSpellLevels[test2-1]);fflush(logFile);
		if((cls_cast_type[test1] & CAST_TYPE_SPONTANEOUS) == CAST_TYPE_SPONTANEOUS || (cls_cast_unlimited[test1][test2] > 0 && (cls_cast_unlimited[test1][test2] & (1 << orig_edx))))//unlimited casting
		{
			Hook_ret = 0x482EB7;
		}	
		else
		{
			Hook_ret = 0x482D1A;
		}
	}

	__asm mov eax, orig_eax
	__asm mov ebx, orig_ebx
	__asm mov ecx, orig_ecx
	__asm mov edx, orig_edx
	__asm jmp Hook_ret
}

void Hook_SpellcasterType14()//0x4A1D2D - CNWSCreature::BroadcastSpellCast - ???
{
	__asm leave
	__asm mov test1, al
	__asm mov orig_eax, eax
	__asm mov orig_ebx, ebx
	__asm mov orig_ecx, ecx
	__asm mov orig_edx, edx

	//fprintf(logFile, "o Hook_SpellcasterType14: cls_id: %i\n",test1);fflush(logFile);
	if(cls_cast_type[test1] & CAST_TYPE_SPONTANEOUS)
	{
		Hook_ret = 0x4A1D4D;
	}
	else
	{
		Hook_ret = 0x4A1F31;
	}

	__asm mov eax, orig_eax
	__asm mov ebx, orig_ebx
	__asm mov ecx, orig_ecx
	__asm mov edx, orig_edx
	__asm jmp Hook_ret
}

void Hook_SpellcasterType18a()//0x479EC2 - CNWSCreatureStats::ReadStatsFromGFF - read familiar/animal companion info from GFF - without this familiar/animal info is lost after reload/relog
{
	__asm leave
	__asm mov orig_eax, eax
	__asm mov orig_ebx, ebx
	__asm mov orig_ecx, ecx
	__asm mov orig_edx, edx

	//fprintf(logFile, "o Hook_SpellcasterType18a\n");fflush(logFile);

	__asm mov [esp+78h], 1//force to load familiar info
	__asm mov [esp+7Ch], 1//force to load animal info

	__asm mov ebx, orig_ebx
	__asm mov ecx, orig_ecx
	__asm mov edx, orig_edx
	__asm mov eax, 0x479F02
	__asm jmp eax
}

void Hook_SpellcasterType18b()//0x47BED7 - CNWSCreatureStats::SaveClassInfo - save familiar/animal companion info into GFF - without this familiar/animal info is lost after relog
{
	__asm leave
	__asm mov orig_ebx, ebx
	__asm mov orig_ecx, ecx
	__asm mov orig_edx, edx

	//fprintf(logFile, "o Hook_SpellcasterType18b\n");fflush(logFile);

	__asm mov [esp+5Ch], 1//force to load familiar info
	__asm mov [esp+60h], 1//force to load animal info

	__asm mov ebx, orig_ebx
	__asm mov ecx, orig_ecx
	__asm mov edx, orig_edx
	__asm mov eax, 0x47BF08
	__asm jmp eax
}

void Hook_SpellcasterType18c()//0x47BA42 - CNWSCreatureStats::SaveClassInfo - save spontaneous spell uses
{
	__asm leave
	__asm mov test1, al
	__asm mov orig_eax, eax
	__asm mov orig_ebx, ebx
	__asm mov orig_ecx, ecx
	__asm mov orig_edx, edx

	//fprintf(logFile, "o Hook_SpellcasterType18c: cls_id %i\n",test1);fflush(logFile);
	if(cls_cast_type[test1] & CAST_TYPE_SPONTANEOUS)
	{
		Hook_ret = 0x47BA7A;
	}
	else
	{
		Hook_ret = 0x47BB22;
	}

	__asm mov eax, orig_eax
	__asm mov ebx, orig_ebx
	__asm mov ecx, orig_ecx
	__asm mov edx, orig_edx
	__asm jmp Hook_ret
}

void Hook_SpellcasterType18d()//0x478E3A - CNWSCreatureStats::ReadStatsFromGFF - read spontaneous spell uses
{
	__asm leave
	__asm mov test1, dl
	__asm mov orig_eax, eax
	__asm mov orig_ebx, ebx
	__asm mov orig_ecx, ecx
	__asm mov orig_edx, edx

	//fprintf(logFile, "o Hook_SpellcasterType18d: cls_id %i\n",test1);fflush(logFile);
	if(cls_cast_type[test1] & CAST_TYPE_SPONTANEOUS)
	{
		Hook_ret = 0x478E5C;
	}
	else
	{
		Hook_ret = 0x478F01;
	}

	__asm mov eax, orig_eax
	__asm mov ebx, orig_ebx
	__asm mov ecx, orig_ecx
	__asm mov edx, orig_edx
	__asm jmp Hook_ret
}

void Hook_SpellcasterType21()//0x43902A - CNWSMessage::ComputeLastUpdate_GuiKnownSpellUses - determines whether to send spontaneous spell uses update to the client
{
	__asm leave
	__asm mov Hook_integer, edi
	__asm mov DWORD PTR stats, ecx
	__asm mov orig_eax, eax
	__asm mov orig_ebx, ebx
	__asm mov orig_ecx, ecx
	__asm mov orig_edx, edx

	test1 = stats->cs_classes[Hook_integer].cl_class;

	//fprintf(logFile, "o Hook_SpellcasterType21: cls_id: %i\n",test1);fflush(logFile);
	if(cls_cast_type[test1] & CAST_TYPE_SPONTANEOUS)
	{
		Hook_ret = 0x43904C;
	}
	else
	{
		Hook_ret = 0x439072;
	}

	__asm mov eax, orig_eax
	__asm mov ebx, orig_ebx
	__asm mov ecx, orig_ecx
	__asm mov edx, orig_edx
	__asm jmp Hook_ret
}

void Hook_SpellcasterType22a()//0x442089 - CNWSMessage::WriteGameObjUpdate_PlayerUpdate - handles spontaneous spell uses update from server
{
	__asm leave
	__asm mov test1, al
	__asm mov orig_eax, eax
	__asm mov orig_ebx, ebx
	__asm mov orig_ecx, ecx
	__asm mov orig_edx, edx

	//fprintf(logFile, "o Hook_SpellcasterType22a: cls_id: %i\n",test1);fflush(logFile);
	if(cls_cast_type[test1] & CAST_TYPE_SPONTANEOUS)
	{
		Hook_ret = 0x4421AF;
	}
	else
	{
		Hook_ret = 0x4420AD;
	}

	__asm mov eax, orig_eax
	__asm mov ebx, orig_ebx
	__asm mov ecx, orig_ecx
	__asm mov edx, orig_edx
	__asm jmp Hook_ret
}

void Hook_SpellcasterType22b()//0x442223 - CNWSMessage::WriteGameObjUpdate_PlayerUpdate - handles spontaneous spell uses update from server, fires very often
{
	__asm leave
	__asm mov test1, al
	__asm mov orig_eax, eax
	__asm mov orig_ebx, ebx
	__asm mov orig_ecx, ecx
	__asm mov orig_edx, edx

	//fprintf(logFile, "o Hook_SpellcasterType22b: cls_id: %i\n",test1);fflush(logFile);
	if(cls_cast_type[test1] & CAST_TYPE_SPONTANEOUS)
	{
		Hook_ret = 0x44223F;
	}
	else
	{
		Hook_ret = 0x442292;
	}

	__asm mov eax, orig_eax
	__asm mov ebx, orig_ebx
	__asm mov ecx, orig_ecx
	__asm mov edx, orig_edx
	__asm jmp Hook_ret
}

void Hook_SpellcasterType22c()//0x442398 - CNWSMessage::WriteGameObjUpdate_PlayerUpdate - handles spontaneous spell uses update from server
{
	__asm leave
	__asm mov test1, al
	__asm mov orig_eax, eax
	__asm mov orig_ebx, ebx
	__asm mov orig_ecx, ecx
	__asm mov orig_edx, edx

	//fprintf(logFile, "o Hook_SpellcasterType22c: cls_id: %i\n",test1);fflush(logFile);
	if(cls_cast_type[test1] & CAST_TYPE_SPONTANEOUS)
	{
		Hook_ret = 0x4423B4;
	}
	else
	{
		Hook_ret = 0x4423DD;
	}

	__asm mov eax, orig_eax
	__asm mov ebx, orig_ebx
	__asm mov ecx, orig_ecx
	__asm mov edx, orig_edx
	__asm jmp Hook_ret
}

void Hook_SpellcasterType23()//0x4BDA2B - CNWSCreature::AIActionCastSpell - somatic spell failure
{
	__asm leave
	__asm mov test1, al
	__asm mov orig_eax, eax
	__asm mov orig_ebx, ebx
	__asm mov orig_ecx, ecx
	__asm mov orig_edx, edx

	//fprintf(logFile, "o Hook_SpellcasterType23: cls_id: %i\n",test1);fflush(logFile);
	if(cls_cast_type[test1] & CAST_TYPE_ARCANE)
	{
		Hook_ret = 0x4BDA4B;
	}
	else
	{
		Hook_ret = 0x4BDB5B;
	}

	__asm mov eax, orig_eax
	__asm mov ebx, orig_ebx
	__asm mov ecx, orig_ecx
	__asm mov edx, orig_edx
	__asm jmp Hook_ret
}

void Hook_SpellcasterType26()//0x48CF1F - CNWSCreatureStats::FeatRequirementsMetAfterLevelUp
{
	__asm leave
	__asm mov test1, cl
	__asm mov orig_eax, eax
	__asm mov orig_ebx, ebx
	__asm mov orig_ecx, ecx
	__asm mov orig_edx, edx

	//fprintf(logFile, "o Hook_SpellcasterType26: cls_id: %i\n",test1);fflush(logFile);

	if(cls_cast_type[test1] & CAST_TYPE_SPONTANEOUS)
	{
		Hook_ret = 0x48CF62;
	}
	else
	{
		Hook_ret = 0x48CF2F;
	}

	__asm mov eax, orig_eax
	__asm mov ebx, orig_ebx
	__asm mov ecx, orig_ecx
	__asm mov edx, orig_edx
	__asm jmp Hook_ret
}

void Hook_Domains6()//0x691255 - CNWSCreatureStats_ClassInfo::GetMemorizedSpellReadyCount
{
	__asm leave
	__asm mov test1, cl
	__asm mov orig_eax, eax
	__asm mov orig_ebx, ebx
	__asm mov orig_ecx, ecx
	__asm mov orig_edx, edx
	
	//fprintf(logFile, "o Hook_Domains6: cls_id: %i\n",test1);fflush(logFile);

	if(cls_cast_type[test1] & CAST_TYPE_SELECT_DOMAINS)
	{
		Hook_ret = 0x46C883;
	}
	else
	{
		Hook_ret = 0x46CA05;
	}

	__asm mov eax, orig_eax
	__asm mov ebx, orig_ebx
	__asm mov ecx, orig_ecx
	__asm mov edx, orig_edx
	__asm push esi//?
	__asm push edi//?
	__asm jmp Hook_ret
}

void Hook_Domains7()//0x478DA2 - CNWSCreatureStats::ReadStatsFromGFF
{
	__asm leave
	__asm mov test1, al
	__asm mov orig_eax, eax
	__asm mov orig_ebx, ebx
	__asm mov orig_ecx, ecx
	__asm mov orig_edx, edx
	
	//fprintf(logFile, "o Hook_Domains7: cls_id: %i\n",test1);fflush(logFile);

	if(cls_cast_type[test1] & CAST_TYPE_SELECT_DOMAINS)
	{
		Hook_ret = 0x478DAA;
	}
	else
	{
		Hook_ret = 0x478E1E;
	}

	__asm mov eax, orig_eax
	__asm mov ebx, orig_ebx
	__asm mov ecx, orig_ecx
	__asm mov edx, orig_edx
	__asm jmp Hook_ret
}

void Hook_Domains8()//0x47B988 - CNWSCreatureStats::SaveClassInfo
{
	__asm leave
	__asm mov test1, dl
	__asm mov orig_eax, eax
	__asm mov orig_ebx, ebx
	__asm mov orig_ecx, ecx
	__asm mov orig_edx, edx

	//fprintf(logFile, "o Hook_Domains8: cls_id: %i\n",test1);fflush(logFile);

	if(cls_cast_type[test1] & CAST_TYPE_SELECT_DOMAINS)
	{
		Hook_ret = 0x47B994;
	}
	else
	{
		Hook_ret = 0x47BA18;
	}

	__asm mov eax, orig_eax
	__asm mov ebx, orig_ebx
	__asm mov ecx, orig_ecx
	__asm mov edx, orig_edx
	__asm jmp Hook_ret
}

void Hook_Domains9()//0x480550 - CNWSCreatureStats::SetMemorizedSpellSlot
{
	__asm leave
	__asm mov test1, al
	__asm mov orig_eax, eax
	__asm mov orig_ebx, ebx
	__asm mov orig_ecx, ecx
	__asm mov orig_edx, edx
	
	//fprintf(logFile, "o Hook_Domains9: cls_id: %i\n",test1);fflush(logFile);

	if(cls_cast_type[test1] & CAST_TYPE_SELECT_DOMAINS)
	{
		Hook_ret = 0x48055C;
	}
	else
	{
		Hook_ret = 0x48061A;
	}

	__asm mov eax, orig_eax
	__asm mov ebx, orig_ebx
	__asm mov ecx, orig_ecx
	__asm mov edx, orig_edx
	__asm jmp Hook_ret
}

void Hook_Domains10()//0x483831 - CNWSCreatureStats::ValidateLevelUp
{
	__asm leave
	__asm mov test1, dl
	__asm mov orig_eax, eax
	__asm mov orig_ebx, ebx
	__asm mov orig_ecx, ecx
	__asm mov orig_edx, edx
	
	//fprintf(logFile, "o Hook_Domains10: cls_id: %i\n",test1);fflush(logFile);

	if(cls_cast_type[test1] & CAST_TYPE_SELECT_DOMAINS)
	{
		Hook_ret = 0x483839;
	}
	else
	{
		Hook_ret = 0x483892;
	}

	__asm mov eax, orig_eax
	__asm mov ebx, orig_ebx
	__asm mov ecx, orig_ecx
	__asm mov edx, orig_edx
	__asm jmp Hook_ret
}

void Hook_Domains11()//0x544600 - CNWSMessage::HandlePlayerToServerLevelUpMessage
{
	__asm leave
	__asm mov test1, al
	__asm mov orig_eax, eax
	__asm mov orig_ebx, ebx
	__asm mov orig_ecx, ecx
	__asm mov orig_edx, edx
	__asm mov [esp+10h], 0
	__asm mov [esp+14h], 0

	//fprintf(logFile, "o Hook_Domains11: cls_id: %i\n",test1);fflush(logFile);

	if(cls_cast_type[test1] & CAST_TYPE_SELECT_DOMAINS)
	{
		Hook_ret = 0x544612;
	}
	else
	{
		Hook_ret = 0x54462C;
	}

	__asm mov eax, orig_eax
	__asm mov ebx, orig_ebx
	__asm mov ecx, orig_ecx
	__asm mov edx, orig_edx
	__asm jmp Hook_ret
}

void Hook_Domains12()//0x4849A1 - CNWSCreatureStats::LevelUp
{
	__asm leave
	__asm mov test1, dl
	__asm mov orig_eax, eax
	__asm mov orig_ebx, ebx
	__asm mov orig_ecx, ecx
	__asm mov orig_edx, edx

	//fprintf(logFile, "o Hook_Domains12: cls_id: %i\n",test1);fflush(logFile);

	if(cls_cast_type[test1] & CAST_TYPE_SELECT_DOMAINS)
	{
		Hook_ret = 0x4849A9;
	}
	else
	{
		Hook_ret = 0x4849D8;
	}

	__asm mov eax, orig_eax
	__asm mov ebx, orig_ebx
	__asm mov ecx, orig_ecx
	__asm mov edx, orig_edx
	__asm jmp Hook_ret
}

void Hook_Domains15()//0x4378FD - CNWSMessage::ComputeUpdateRequired
{
	__asm leave
	__asm mov test1, al
	__asm mov orig_eax, eax
	__asm mov orig_ebx, ebx
	__asm mov orig_ecx, ecx
	__asm mov orig_edx, edx

	//fprintf(logFile, "o Hook_Domains15: cls_id: %i\n",test1);fflush(logFile);

	if(cls_cast_type[test1] & CAST_TYPE_SELECT_DOMAINS)
	{
		Hook_ret = 0x437905;
	}
	else
	{
		Hook_ret = 0x437935;
	}

	__asm mov eax, orig_eax
	__asm mov ebx, orig_ebx
	__asm mov ecx, orig_ecx
	__asm mov edx, orig_edx
	__asm jmp Hook_ret
}

void Hook_Domains16()//0x4469F5 - CNWSMessage::WriteGameObjUpdate_UpdateObject
{
	__asm leave
	__asm mov test1, al
	__asm mov orig_eax, eax
	__asm mov orig_ebx, ebx
	__asm mov orig_ecx, ecx
	__asm mov orig_edx, edx

	//fprintf(logFile, "o Hook_Domains16: cls_id: %i\n",test1);fflush(logFile);

	if(cls_cast_type[test1] & CAST_TYPE_SELECT_DOMAINS)
	{
		Hook_ret = 0x4469FD;
	}
	else
	{
		Hook_ret = 0x446A29;
	}

	__asm mov eax, orig_eax
	__asm mov ebx, orig_ebx
	__asm mov ecx, orig_ecx
	__asm mov edx, orig_edx
	__asm jmp Hook_ret
}

void Hook_Domains17()//0x44B4C6 - CNWSMessage::UpdateLastUpdateObject
{
	__asm leave
	__asm mov test1, al
	__asm mov orig_eax, eax
	__asm mov orig_ebx, ebx
	__asm mov orig_ecx, ecx
	__asm mov orig_edx, edx

	//fprintf(logFile, "o Hook_Domains17: cls_id: %i\n",test1);fflush(logFile);

	if(cls_cast_type[test1] & CAST_TYPE_SELECT_DOMAINS)
	{
		Hook_ret = 0x44B4CE;
	}
	else
	{
		Hook_ret = 0x44B4F2;
	}

	__asm mov eax, orig_eax
	__asm mov ebx, orig_ebx
	__asm mov ecx, orig_ecx
	__asm mov edx, orig_edx
	__asm jmp Hook_ret
}

void PatchImage()
{
	DWORD DefaultPrivs;
	unsigned char *pPatch = (unsigned char *) 0x58A872;
	VirtualProtect(pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	pPatch[0]=0xFF;
	VirtualProtect(pPatch, 1, DefaultPrivs, NULL);
	fprintf(logFile, "o Disabling limitation in CopyItemAndModify function.\n");
	
	pPatch = (unsigned char *) 0x58E36B;
	VirtualProtect(pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	pPatch[0]=0x64;
	VirtualProtect(pPatch, 1, DefaultPrivs, NULL);
	pPatch = (unsigned char *) 0x58E36F;
	VirtualProtect(pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	pPatch[0]=0x64;
	VirtualProtect(pPatch, 1, DefaultPrivs, NULL);
	fprintf(logFile, "o Increasing limit in SetItemCharges function to 100.\n");

	pPatch = (unsigned char *) 0x54CC4A;
	VirtualProtect(pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_AssassinDeathAttack - (uint32_t)(pPatch + 5);
	VirtualProtect(pPatch, 1, DefaultPrivs, NULL);
	fprintf(logFile, "o Sofcoding Assassin's Death Attack OnHit ability.\n");

	pPatch = (unsigned char *) 0x54D5D0;
	VirtualProtect(pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_DevastatingCriticalMelee - (uint32_t)(pPatch + 5);
	VirtualProtect((DWORD*)pPatch, 1, DefaultPrivs, NULL);
	pPatch = (unsigned char *) 0x54DFDD;
	VirtualProtect(pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_DevastatingCriticalRanged - (uint32_t)(pPatch + 5);
	VirtualProtect(pPatch, 1, DefaultPrivs, NULL);
	fprintf(logFile, "o Sofcoding Devastating Critical ability.\n");

	pPatch = (unsigned char *) 0x54A049;
	VirtualProtect(pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_SpecAttacks1 - (uint32_t)(pPatch + 5);
	VirtualProtect(pPatch, 1, DefaultPrivs, NULL);
	pPatch = (unsigned char *) 0x547AAE;
	VirtualProtect(pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_SpecAttacks2 - (uint32_t)(pPatch + 5);
	VirtualProtect(pPatch, 1, DefaultPrivs, NULL);
	pPatch = (unsigned char *) 0x54B996;
	VirtualProtect(pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_SpecAttacks3 - (uint32_t)(pPatch + 5);
	VirtualProtect(pPatch, 1, DefaultPrivs, NULL);
	pPatch = (unsigned char *) 0x54BB0C;
	VirtualProtect(pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_SpecAttacks4 - (uint32_t)(pPatch + 5);
	VirtualProtect(pPatch, 1, DefaultPrivs, NULL);
	fprintf(logFile, "o Softcoding special attacks.\n");

	pPatch = (unsigned char *) 0x476CD2;
	VirtualProtect(pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_SneakAttackCalculation - (uint32_t)(pPatch + 5);
	VirtualProtect(pPatch, 1, DefaultPrivs, NULL);
	fprintf(logFile, "o Fixing Improved sneak attack issue.\n");

	pPatch = (unsigned char *) 0x54C1CA;
	VirtualProtect(pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_SneakAttackImmunity - (uint32_t)(pPatch + 5);
	VirtualProtect(pPatch, 1, DefaultPrivs, NULL);
	pPatch = (unsigned char *) 0x54C70C;
	DefaultPrivs = NULL;
	VirtualProtect(pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_DeathAttackImmunity - (uint32_t)(pPatch + 5);
	VirtualProtect(pPatch, 1, DefaultPrivs, NULL);
	fprintf(logFile, "o Detaching sneak attack immunity from critical hit immunity.\n");

	pPatch = (unsigned char *) 0x4CA74F;
	VirtualProtect((DWORD*)pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_HealersKit - (uint32_t)(pPatch + 5);
	VirtualProtect((DWORD*)pPatch, 1, DefaultPrivs, NULL);
	fprintf(logFile, "o Softcoding healer's kit.\n");

	if(!DisableStickyCombatModes)
	{
		pPatch = (unsigned char *) 0x53D716;//CNWSMessage::HandlePlayerToServerInputWalkToWaypoint
		VirtualProtect((DWORD*)pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
		memset((PVOID)pPatch, '\x90', 8);
		pPatch[0] = 0xE9;
		*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_CombatMode1 - (uint32_t)(pPatch + 5);
		VirtualProtect((DWORD*)pPatch, 1, DefaultPrivs, NULL);
		pPatch = (unsigned char *) 0x53D129;//CNWSMessage::HandlePlayerToServerInputDriveControl
		VirtualProtect((DWORD*)pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
		memset((PVOID)pPatch, '\x90', 8);
		pPatch[0] = 0xE9;
		*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_CombatMode2 - (uint32_t)(pPatch + 5);
		VirtualProtect((DWORD*)pPatch, 1, DefaultPrivs, NULL);
		pPatch = (unsigned char *) 0x54746D;//CNWSCreature::AIActionAttackObject
		VirtualProtect((DWORD*)pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
		memset((PVOID)pPatch, '\x90', 8);
		pPatch[0] = 0xE9;
		*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_CombatMode3 - (uint32_t)(pPatch + 5);
		VirtualProtect((DWORD*)pPatch, 1, DefaultPrivs, NULL);	
		fprintf(logFile, "o Patching automatic combat mode canceling.\n");
	}
	else
	{
		fprintf(logFile, "o Patching automatic combat mode canceling disabled.\n");
	}

	pPatch = (unsigned char *) 0x4F0F34;
	VirtualProtect((DWORD*)pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_MindImmunity - (uint32_t)(pPatch + 5);
	VirtualProtect((DWORD*)pPatch, 1, DefaultPrivs, NULL);
	fprintf(logFile, "o Patching mind immunity.\n");

	pPatch = (unsigned char *) 0x4F2653;
	VirtualProtect((DWORD*)pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_Speed - (uint32_t)(pPatch + 5);
	VirtualProtect((DWORD*)pPatch, 1, DefaultPrivs, NULL);
	fprintf(logFile, "o Patching speed calculation.\n");

	pPatch = (unsigned char *) 0x442194;
	VirtualProtect((DWORD*)pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_SpellSlotsCrash - (uint32_t)(pPatch + 5);
	VirtualProtect((DWORD*)pPatch, 1, DefaultPrivs, NULL);
	pPatch = (unsigned char *) 0x4420EE;
	VirtualProtect((DWORD*)pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_SpellSlotsCrash2 - (uint32_t)(pPatch + 5);
	VirtualProtect((DWORD*)pPatch, 1, DefaultPrivs, NULL);
	fprintf(logFile, "o Patching 255 spellslots crash.\n");
	fflush(logFile);

	if(NumTilesExplored > 0 && NumTilesExplored <= 10 && NumTilesExplored != 8)
	{
		pPatch = (unsigned char *) 0x494DBD;
		VirtualProtect(pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
		pPatch[0]= NumTilesExplored;
		VirtualProtect(pPatch, 1, DefaultPrivs, NULL);
		fprintf(logFile, "o Changing number of tiles explored to %i.\n",NumTilesExplored);
	}
	
	/*
	pPatch = (unsigned char *) 0x576EBF;
	VirtualProtect((DWORD*)pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_Unpossess - (uint32_t)(pPatch + 5);
	VirtualProtect((DWORD*)pPatch, 1, DefaultPrivs, NULL);
	fprintf(logFile, "o Removing automatic unpossess.\n");*/

	/*
	//TODO - crashing
	pPatch = (unsigned char *) 0x434243;//ValidateCharacter
	VirtualProtect((DWORD*)pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_ELC1 - (uint32_t)(pPatch + 5);
	VirtualProtect((DWORD*)pPatch, 1, DefaultPrivs, NULL);
	pPatch = (unsigned char *) 0x434440;//ValidateCharacter
	VirtualProtect((DWORD*)pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_ELC2 - (uint32_t)(pPatch + 5);
	VirtualProtect((DWORD*)pPatch, 1, DefaultPrivs, NULL);
	fprintf(logFile, "o Fix for ELC number of spells learned.\n");
	*/

	pPatch = (unsigned char *) 0x576EBF;//SetCustomToken
	VirtualProtect((DWORD*)pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_CustomToken - (uint32_t)(pPatch + 5);
	VirtualProtect((DWORD*)pPatch, 1, DefaultPrivs, NULL);
	fprintf(logFile, "o Enabling to set <CUSTOM0> to <CUSTOM9>.\n");

	pPatch = (unsigned char *) 0x47090F;//CNWSCreatureStats::GetUnarmedDamageDice
	VirtualProtect((DWORD*)pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_GetUnarmedDamageDice - (uint32_t)(pPatch + 5);
	VirtualProtect((DWORD*)pPatch, 1, DefaultPrivs, NULL);
	fprintf(logFile, "o Patching Shou Disciple+Monk unarmed damage calculation.\n");

	if(!GetPrivateProfileInt("Community Patch","DisablePlayerLeave",0,"./nwnplayer.ini"))
	{
		pPatch = (unsigned char *) 0x45BB7B;//CServerExoAppInternal::RemovePCFromWorld
		VirtualProtect((DWORD*)pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
		memset((PVOID)pPatch, '\x90', 8);
		pPatch[0] = 0xE9;
		*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_OnClientExit - (uint32_t)(pPatch + 5);
		VirtualProtect((DWORD*)pPatch, 1, DefaultPrivs, NULL);
		fprintf(logFile, "o Removing vanilla OnClientExit call.\n");
	}

	if(!GetPrivateProfileInt("Community Patch","DisableModuleEvents",0,"./nwnplayer.ini"))
	{
		pPatch = (unsigned char *) 0x4D224E;//CNWSModule::EventHandler
		VirtualProtect((DWORD*)pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
		memset((PVOID)pPatch, '\x90', 8);
		pPatch[0] = 0xE9;
		*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_ModuleEvents - (uint32_t)(pPatch + 5);
		VirtualProtect((DWORD*)pPatch, 1, DefaultPrivs, NULL);
		pPatch = (unsigned char *) 0x534F70;//CNWSMessage::HandlePlayerToServerChatMessage
		VirtualProtect((DWORD*)pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
		memset((PVOID)pPatch, '\x90', 8);
		pPatch[0] = 0xE9;
		*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_OnPlayerChat - (uint32_t)(pPatch + 5);
		VirtualProtect((DWORD*)pPatch, 1, DefaultPrivs, NULL);
		pPatch = (unsigned char *) 0x49637D;//CNWSCreature::UnequipItem
		VirtualProtect((DWORD*)pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
		memset((PVOID)pPatch, '\x90', 8);
		pPatch[0] = 0xE9;
		*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_OnPlayerUnEquip - (uint32_t)(pPatch + 5);
		VirtualProtect((DWORD*)pPatch, 1, DefaultPrivs, NULL);
		fprintf(logFile, "o Enabling module event duplicates.\n");
	}
	else
	{
		fprintf(logFile, "o Module event duplicates disabled.\n");
	}

	if(!GetPrivateProfileInt("Community Patch","DisableAttackOfOpportunity",0,"./nwnplayer.ini"))
	{	
		pPatch = (unsigned char *) 0x4A2CBE;//CNWSCreature::BroadcastAttackOfOpportunity
		VirtualProtect((DWORD*)pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
		memset((PVOID)pPatch, '\x90', 8);
		pPatch[0] = 0xE9;
		*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_AOO1 - (uint32_t)(pPatch + 5);
		VirtualProtect((DWORD*)pPatch, 1, DefaultPrivs, NULL);
		pPatch = (unsigned char *) 0x4A3025;//CNWSCreature::BroadcastAttackOfOpportunity
		VirtualProtect((DWORD*)pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
		memset((PVOID)pPatch, '\x90', 8);
		pPatch[0] = 0xE9;
		*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_AOO2 - (uint32_t)(pPatch + 5);
		VirtualProtect((DWORD*)pPatch, 1, DefaultPrivs, NULL);
		fprintf(logFile, "o Softcoding Attacks of Opportunity.\n");
	}
	else
	{
		fprintf(logFile, "o Softcoding Attack of Opportunity disabled.\n");
	}

	pPatch = (unsigned char *) 0x4EB93E;//CNWSEffectListHandler::OnApplyDamage
	VirtualProtect((DWORD*)pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_DamageReduction - (uint32_t)(pPatch + 5);
	VirtualProtect((DWORD*)pPatch, 1, DefaultPrivs, NULL);
	fprintf(logFile, "o Fixing nDamagePower parameter in EffectDamage.\n");

	/*
	pPatch = (unsigned char *) 0x479CF6;//CNWSCreatureStats::ReadStatsFromGFF
	VirtualProtect((DWORD*)pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_FeatUses - (uint32_t)(pPatch + 5);
	VirtualProtect((DWORD*)pPatch, 1, DefaultPrivs, NULL);
	fprintf(logFile, "o Correcting feat uses when relogging.\n");
	*/

	pPatch = (unsigned char *) 0x4F0E50;//CNWSEffectListHandler::OnApplySetState - sleep
	VirtualProtect((DWORD*)pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_ImmunityMind1 - (uint32_t)(pPatch + 5);
	VirtualProtect((DWORD*)pPatch, 1, DefaultPrivs, NULL);
	pPatch = (unsigned char *) 0x4F0F17;//CNWSEffectListHandler::OnApplySetState - paralysis
	VirtualProtect((DWORD*)pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_ImmunityMind1 - (uint32_t)(pPatch + 5);
	VirtualProtect((DWORD*)pPatch, 1, DefaultPrivs, NULL);
	pPatch = (unsigned char *) 0x4F100B;//CNWSEffectListHandler::OnApplySetState - stun
	VirtualProtect((DWORD*)pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_ImmunityMind1 - (uint32_t)(pPatch + 5);
	VirtualProtect((DWORD*)pPatch, 1, DefaultPrivs, NULL);
	pPatch = (unsigned char *) 0x4F1531;//CNWSEffectListHandler::OnApplySetState - fear
	VirtualProtect((DWORD*)pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_ImmunityMind1 - (uint32_t)(pPatch + 5);
	VirtualProtect((DWORD*)pPatch, 1, DefaultPrivs, NULL);
	pPatch = (unsigned char *) 0x4F160C;//CNWSEffectListHandler::OnApplySetState - mind spells
	VirtualProtect((DWORD*)pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_ImmunityMind2 - (uint32_t)(pPatch + 5);
	VirtualProtect((DWORD*)pPatch, 1, DefaultPrivs, NULL);
	pPatch = (unsigned char *) 0x4F3687;//CNWSEffectListHandler::OnApplyPoison
	VirtualProtect((DWORD*)pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_ImmunityPoison - (uint32_t)(pPatch + 5);
	VirtualProtect((DWORD*)pPatch, 1, DefaultPrivs, NULL);
	pPatch = (unsigned char *) 0x4F3F5C;//CNWSEffectListHandler::OnApplyDisease
	VirtualProtect((DWORD*)pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_ImmunityDisease - (uint32_t)(pPatch + 5);
	pPatch = (unsigned char *) 0x54BB93;//CNWSCreature::ResolveAttackRoll
	VirtualProtect((DWORD*)pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_ImmunityCritical - (uint32_t)(pPatch + 5);
	VirtualProtect((DWORD*)pPatch, 1, DefaultPrivs, NULL);VirtualProtect((DWORD*)pPatch, 1, DefaultPrivs, NULL);
	fprintf(logFile, "o Removing hardcoded feat immunity.\n");

	pPatch = (unsigned char *) 0x53F564;
	VirtualProtect((DWORD*)pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_SpontaneousSpell - (uint32_t)(pPatch + 5);
	VirtualProtect((DWORD*)pPatch, 1, DefaultPrivs, NULL);
	fprintf(logFile, "o Enabling spontaneous casting for other classes.\n");

	fflush(logFile);
}

void PatchSpellCasting()
{
	DWORD DefaultPrivs;
	unsigned char *pPatch = (unsigned char *) 0x480408;////CNWSCreatureStats::AddKnownSpell
	VirtualProtect((DWORD*)pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_SpellcasterType7 - (uint32_t)(pPatch + 5);
	VirtualProtect((DWORD*)pPatch, 1, DefaultPrivs, NULL);
	fprintf(logFile, "o Enabling custom spellcasting #7.\n");

	pPatch = (unsigned char *) 0x482AA5;//CNWSCreatureStats::ReadySpellLevel
	VirtualProtect((DWORD*)pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_SpellcasterType13a - (uint32_t)(pPatch + 5);
	VirtualProtect((DWORD*)pPatch, 1, DefaultPrivs, NULL);
	fprintf(logFile, "o Enabling custom spellcasting #13a.\n");

	pPatch = (unsigned char *) 0x482D02;//CNWSCreatureStats::UnReadySpell
	VirtualProtect((DWORD*)pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_SpellcasterType13b - (uint32_t)(pPatch + 5);
	VirtualProtect((DWORD*)pPatch, 1, DefaultPrivs, NULL);
	fprintf(logFile, "o Enabling custom spellcasting #13b.\n");

	pPatch = (unsigned char *) 0x4A1D2D;//CNWSCreature::BroadcastSpellCast
	VirtualProtect((DWORD*)pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_SpellcasterType14 - (uint32_t)(pPatch + 5);
	VirtualProtect((DWORD*)pPatch, 1, DefaultPrivs, NULL);
	fprintf(logFile, "o Enabling custom spellcasting #14.\n");

	pPatch = (unsigned char *) 0x479EC2;//CNWSCreatureStats::ReadStatsFromGFF
	VirtualProtect((DWORD*)pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_SpellcasterType18a - (uint32_t)(pPatch + 5);
	VirtualProtect((DWORD*)pPatch, 1, DefaultPrivs, NULL);
	fprintf(logFile, "o Enabling custom spellcasting #18a.\n");

	pPatch = (unsigned char *) 0x47BED7;//CNWSCreatureStats::SaveClassInfo
	VirtualProtect((DWORD*)pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_SpellcasterType18b - (uint32_t)(pPatch + 5);
	VirtualProtect((DWORD*)pPatch, 1, DefaultPrivs, NULL);
	fprintf(logFile, "o Enabling custom spellcasting #18b.\n");

	pPatch = (unsigned char *) 0x47BA42;//CNWSCreatureStats::SaveClassInfo
	VirtualProtect((DWORD*)pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_SpellcasterType18c - (uint32_t)(pPatch + 5);
	VirtualProtect((DWORD*)pPatch, 1, DefaultPrivs, NULL);
	fprintf(logFile, "o Enabling custom spellcasting #18c.\n");

	pPatch = (unsigned char *) 0x478E3A;//CNWSCreatureStats::ReadStatsFromGFF
	VirtualProtect((DWORD*)pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_SpellcasterType18d - (uint32_t)(pPatch + 5);
	VirtualProtect((DWORD*)pPatch, 1, DefaultPrivs, NULL);
	fprintf(logFile, "o Enabling custom spellcasting #18d.\n");

	pPatch = (unsigned char *) 0x43902A;//CNWSMessage::ComputeLastUpdate_GuiKnownSpellUses
	VirtualProtect((DWORD*)pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_SpellcasterType21 - (uint32_t)(pPatch + 5);
	VirtualProtect((DWORD*)pPatch, 1, DefaultPrivs, NULL);
	fprintf(logFile, "o Enabling custom spellcasting #21.\n");

	pPatch = (unsigned char *) 0x442089;//CNWSMessage::WriteGameObjUpdate_PlayerUpdate
	VirtualProtect((DWORD*)pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_SpellcasterType22a - (uint32_t)(pPatch + 5);
	VirtualProtect((DWORD*)pPatch, 1, DefaultPrivs, NULL);
	fprintf(logFile, "o Enabling custom spellcasting #22a.\n");

	pPatch = (unsigned char *) 0x442223;//CNWSMessage::WriteGameObjUpdate_PlayerUpdate
	VirtualProtect((DWORD*)pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_SpellcasterType22b - (uint32_t)(pPatch + 5);
	VirtualProtect((DWORD*)pPatch, 1, DefaultPrivs, NULL);
	fprintf(logFile, "o Enabling custom spellcasting #22b.\n");

	pPatch = (unsigned char *) 0x442398;//CNWSMessage::WriteGameObjUpdate_PlayerUpdate
	VirtualProtect((DWORD*)pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_SpellcasterType22c - (uint32_t)(pPatch + 5);
	VirtualProtect((DWORD*)pPatch, 1, DefaultPrivs, NULL);
	fprintf(logFile, "o Enabling custom spellcasting #22c.\n");

	pPatch = (unsigned char *) 0x4BDA2B;//CNWSCreature::AIActionCastSpell
	VirtualProtect((DWORD*)pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_SpellcasterType23 - (uint32_t)(pPatch + 5);
	VirtualProtect((DWORD*)pPatch, 1, DefaultPrivs, NULL);
	fprintf(logFile, "o Enabling custom spellcasting #23.\n");

	pPatch = (unsigned char *) 0x48CF1F;//CNWSCreatureStats::FeatRequirementsMetAfterLevelUp
	VirtualProtect((DWORD*)pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_SpellcasterType26 - (uint32_t)(pPatch + 5);
	VirtualProtect((DWORD*)pPatch, 1, DefaultPrivs, NULL);
	fprintf(logFile, "o Enabling custom spellcasting #26.\n");

	pPatch = (unsigned char *) 0x46C875;//CNWSCreatureStats_ClassInfo::GetMemorizedSpellReadyCount
	VirtualProtect((DWORD*)pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_Domains6 - (uint32_t)(pPatch + 5);
	VirtualProtect((DWORD*)pPatch, 1, DefaultPrivs, NULL);
	fprintf(logFile, "o Enabling custom spellcasting #domains6.\n");

	pPatch = (unsigned char *) 0x478DA2;//CNWSCreatureStats::ReadStatsFromGFF
	VirtualProtect((DWORD*)pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_Domains7 - (uint32_t)(pPatch + 5);
	VirtualProtect((DWORD*)pPatch, 1, DefaultPrivs, NULL);
	fprintf(logFile, "o Enabling custom spellcasting #domains7.\n");

	pPatch = (unsigned char *) 0x47B988;//CNWSCreatureStats::SaveClassInfo
	VirtualProtect((DWORD*)pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_Domains8 - (uint32_t)(pPatch + 5);
	VirtualProtect((DWORD*)pPatch, 1, DefaultPrivs, NULL);
	fprintf(logFile, "o Enabling custom spellcasting #domains8.\n");

	pPatch = (unsigned char *) 0x480550;//CNWSCreatureStats::SetMemorizedSpellSlot
	VirtualProtect((DWORD*)pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	//memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_Domains9 - (uint32_t)(pPatch + 5);
	VirtualProtect((DWORD*)pPatch, 1, DefaultPrivs, NULL);
	fprintf(logFile, "o Enabling custom spellcasting #domains9.\n");

	pPatch = (unsigned char *) 0x483831;//CNWSCreatureStats::ValidateLevelUp
	VirtualProtect((DWORD*)pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_Domains10 - (uint32_t)(pPatch + 5);
	VirtualProtect((DWORD*)pPatch, 1, DefaultPrivs, NULL);
	fprintf(logFile, "o Enabling custom spellcasting #domains10.\n");

	pPatch = (unsigned char *) 0x544600;//CNWSMessage::HandlePlayerToServerLevelUpMessage
	VirtualProtect((DWORD*)pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_Domains11 - (uint32_t)(pPatch + 5);
	VirtualProtect((DWORD*)pPatch, 1, DefaultPrivs, NULL);
	fprintf(logFile, "o Enabling custom spellcasting #domains11.\n");

	pPatch = (unsigned char *) 0x4849A1;//CNWSCreatureStats::LevelUp
	VirtualProtect((DWORD*)pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_Domains12 - (uint32_t)(pPatch + 5);
	VirtualProtect((DWORD*)pPatch, 1, DefaultPrivs, NULL);
	fprintf(logFile, "o Enabling custom spellcasting #domains12.\n");

	pPatch = (unsigned char *) 0x4378FD;//CNWSMessage::ComputeUpdateRequired
	VirtualProtect((DWORD*)pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_Domains15 - (uint32_t)(pPatch + 5);
	VirtualProtect((DWORD*)pPatch, 1, DefaultPrivs, NULL);
	fprintf(logFile, "o Enabling custom spellcasting #domains15.\n");

	pPatch = (unsigned char *) 0x4469F5;//CNWSMessage::WriteGameObjUpdate_UpdateObject
	VirtualProtect((DWORD*)pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_Domains16 - (uint32_t)(pPatch + 5);
	VirtualProtect((DWORD*)pPatch, 1, DefaultPrivs, NULL);
	fprintf(logFile, "o Enabling custom spellcasting #domains16.\n");

	pPatch = (unsigned char *) 0x44B4C6;//CNWSMessage::UpdateLastUpdateObject
	VirtualProtect((DWORD*)pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_Domains17 - (uint32_t)(pPatch + 5);
	VirtualProtect((DWORD*)pPatch, 1, DefaultPrivs, NULL);
	fprintf(logFile, "o Enabling custom spellcasting #domains17.\n");

	fflush(logFile);
}

void InitPlugin()
{
	logFile = _fsopen(logFileName, "w",_SH_DENYNO);
	fprintf(logFile, "Community Patch Patch plugin by Shadooow v %i.%i%s (Server Edition)\n\n",VERSION_MAJOR,VERSION_MINOR,VERSION_PATCH);
	fflush(logFile);
	DebugLvl = GetPrivateProfileInt("Community Patch","DebugLevel",0,"./nwnplayer.ini");
	NoServerCharacter = GetPrivateProfileInt("Server Options","Disallow New Characters",0,"./nwnplayer.ini");
	NumTilesExplored = (unsigned char)GetPrivateProfileInt("Server Options","Num Tiles Explored",0,"./nwnplayer.ini");
	DisallowAnimalCompanionPossessing = GetPrivateProfileInt("Server Options","Disallow Animal Companion Possessing",0,"./nwnplayer.ini");
	DisableStickyCombatModes = GetPrivateProfileInt("Community Patch","Disable Sticky Combat Modes",0,"./nwnplayer.ini");

	nwnx_malloc = (void *(__cdecl *)(unsigned int))0x40D550;
	nwnx_free = (void (__cdecl *)(void *))0x40D560;
	heapAddress = (DWORD *)0x5EEFF00;	
	helper_backup = 0;
	helper = 0;
	helper_effect = NULL;
	PatchImage();

	if(!GetPrivateProfileInt("Community Patch","DisableCustomSpellCasters",false,"./nwnplayer.ini"))
	{
		PatchSpellCasting();
	}
	HookFunctions();
}

void Log(int nDebugLevel, const char *pcMsg, ... )
{
	if(nDebugLevel <= DebugLvl && logFile)
	{  
		if (ftell(logFile) > 5242880)
		{	
			fclose(logFile);
			logFile = _fsopen(logFileName, "w",_SH_DENYNO);
			fprintf(logFile, "Community Patch Patch plugin by Shadooow v %i.%i%s (Server Edition)\n\n",VERSION_MAJOR,VERSION_MINOR,VERSION_PATCH);
			fprintf(logFile, "o Logfile hit maximum size limit, starting again.\n");
		}

        va_list argptr;
        va_start(argptr, pcMsg);

		vfprintf(logFile,pcMsg,argptr);
        va_end(argptr);
		fflush(logFile);
	}
}

void *nwnx_calloc(unsigned int num, unsigned int size)
{
	void *pArray = nwnx_malloc(num*size);

	if(pArray == NULL)
		return NULL;

	memset(pArray, NULL, num*size);

	return pArray;
}

BOOL APIENTRY DllMain(HMODULE, DWORD ul_reason_for_call, LPVOID)
{
 	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
	{
		InitPlugin();
	}
	else if (ul_reason_for_call == DLL_PROCESS_DETACH)
	{
		//delete plugin;
	}
	return TRUE;
}