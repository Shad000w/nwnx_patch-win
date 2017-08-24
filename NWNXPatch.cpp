/***************************************************************************
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 ***************************************************************************/
#define _CRT_SECURE_NO_WARNINGS

#include "stdafx.h"
#include "NWNXPatch.h"
#include "stdio.h"
#include "stdlib.h"
#include "CNWNHooks.h"
#include "../NWNXdll/IniFile.h"
#include "nwn_internals.h"
#include "types.h"

extern CNWNXPatch Patch;

CNWSCreature *self;
CNWSCreatureStats *stats;
CNWSCreature *target;
CExoString script_dthattk = "70_s2_dthattk";
CExoString script_devast = "70_s2_devattk";
CExoString script_healkit = "70_s3_healkit";
CExoString SpontaneouslyCast = "SpontaneouslyCast";
bool ParalysisIgnoreMindImmunity = 0;
volatile uint32_t Hook_ret;
volatile uint32_t test32;
volatile uint32_t test33;
volatile uint8_t test1;
volatile uint8_t test2;
volatile uint8_t test3;
volatile uint8_t Hook_uint8;
volatile int *pointer;
volatile uint32_t orig_eax;
volatile uint32_t orig_ebx;
volatile uint32_t orig_ecx;
volatile uint32_t orig_edx;
int Hook_integer = 0;

void Hook_SpontaneousSpell()//note, while in singleplayer, the SpontaneouslyCast field is only 0 or 1, in server version this field match with 2da, thus the whole code is much simpler
{
	__asm leave
	__asm mov test1, al//class
	__asm mov eax, [esp+84h]//spell id
	__asm mov test32, eax

	unsigned int spontaneous = NWN_Rules->ru_spells->GetSpell(test32)->SpontaneouslyCast;

	Hook_ret = 0x53F635;

	if(spontaneous > 0 && ((test1 == 2 && spontaneous == 1) || spontaneous == test1))
	{
		Hook_ret = 0x53F570;
	}

	__asm mov eax, Hook_ret
	__asm jmp eax
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
			__asm mov eax, 0x54E01E
		}
		else
		{
			__asm mov eax, 0x54E0DA
		}
	}
	else
	{
		__asm mov eax, 0x54E0A4
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
			__asm mov Hook_ret, 0x54D610
		}
		else
		{
			__asm mov Hook_ret, 0x54D6BC
		}
	}
	else
	{
		__asm mov Hook_ret, 0x54D692
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
	__asm mov test2, al//tohitmod
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

	if(test1+test2 >= test3)
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
	__asm mov test2, al//tohitmod
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

	if(test1+test2 >= test3)
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
	__asm mov ebx, 0Ah//not sure what is this and it works without it but for safety
	__asm mov DWORD PTR stats, esi

	if(stats != NULL && (stats->cs_original->cre_combat_round->GetAttack(stats->cs_original->cre_combat_round->CurrentAttack)->SneakAttack || (stats->HasFeat(834) && stats->cs_original->cre_combat_round->GetAttack(stats->cs_original->cre_combat_round->CurrentAttack)->DeathAttack)))
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
		if(!target->cre_stats->GetEffectImmunity(30,self))//sneak immunity
		{
			if(Patch.NoCriticalImmunity || !target->cre_stats->GetEffectImmunity(31,self))//critical immunity
			{
				if(!target->cre_stats->HasFeat(896))//PM Deathless Mastery
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
		if(!target->cre_stats->GetEffectImmunity(30,self))//sneak immunity
		{
			if(Patch.NoCriticalImmunity || !target->cre_stats->GetEffectImmunity(31,self))//critical immunity
			{
				if(!target->cre_stats->HasFeat(896))//PM Deathless Mastery
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

void Hook_ExamineCR()
{
	__asm leave
	__asm mov DWORD PTR target, edi//target of examine

	Hook_ret = 0x446E49;

	if(target != NULL && NWN_AppManager->app_server->srv_internal->ServerInfo->examine_cr == 1 && (Patch.examineCRonPlayers != -1 || target->cre_is_pc == 0))
	{
		fprintf(Patch.m_fFile, "o examine cr test  5\n");fflush(Patch.m_fFile);
		Hook_ret = 0x446DFB;//tohle je problem tady to pada jinak je to OK
	}

	__asm mov eax, Hook_ret
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
	__asm mov orig_ebx, ebx
	__asm mov orig_ecx, ecx
	__asm mov orig_edx, edx
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

	__asm mov ebx, orig_ebx
	__asm mov ecx, orig_ecx
	__asm mov edx, orig_edx
	__asm jmp eax
}

void Hook_CustomToken()
{
	__asm leave
	__asm push ebx
	__asm push edi
	Hook_ret = 0x576ED1;
	__asm jmp Hook_ret;
}

void Hook_Unpossess()//0x740270 - CNWSCreature::ResolveAttack
{
	__asm leave
	Hook_ret = 0x5476A8;
	__asm jmp Hook_ret;
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

void Hook_NewCharacter()//crash crash crash
{
	__asm leave
	//__asm mov eax, [esi+9Ch]//esi nejaka struktura asi CExoFile, 9C -> is loaded
	//__asm mov Hook_integer, eax
	

	//fprintf(Patch.m_fFile, "o new char test %i\n",Hook_integer);fflush(Patch.m_fFile);
	/*__asm mov pointer, edi
	fprintf(Patch.m_fFile, "o new char test1\n");fflush(Patch.m_fFile);
	fprintf(Patch.m_fFile, "o new char test %s\n",pointer);fflush(Patch.m_fFile);
	fprintf(Patch.m_fFile, "o new char test2\n");fflush(Patch.m_fFile);*/

	__asm mov eax, 0x4548AA;//note: smazani charu se provede spadne to potom
	__asm jmp eax
}

void Hook_SpellcasterType7()//480408 - CNWSCreatureStats::AddKnownSpell
{
	__asm leave
	__asm mov test1, al
	__asm mov orig_eax, eax
	__asm mov orig_ebx, ebx
	__asm mov orig_ecx, ecx
	__asm mov orig_edx, edx

	//fprintf(Patch.m_fFile, "o Hook_SpellcasterType7: cls_id: %i\n",test1);fflush(Patch.m_fFile);
	if(Patch.cls_cast_type[test1] & CAST_TYPE_SPONTANEOUS)
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

	//fprintf(Patch.m_fFile, "o Hook_SpellcasterType13a: cls_id: %i\n",test1);fflush(Patch.m_fFile);
	if(Patch.cls_cast_type[test1] & CAST_TYPE_SPONTANEOUS)
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
	__asm mov orig_eax, eax
	__asm mov orig_ebx, ebx
	__asm mov orig_ecx, ecx
	__asm mov orig_edx, edx

	//fprintf(Patch.m_fFile, "o Hook_SpellcasterType13b: cls_id: %i\n",test1);fflush(Patch.m_fFile);
	if(Patch.cls_cast_type[test1] & CAST_TYPE_SPONTANEOUS)
	{
		Hook_ret = 0x482EB7;
	}
	else
	{
		Hook_ret = 0x482D1A;
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

	//fprintf(Patch.m_fFile, "o Hook_SpellcasterType14: cls_id: %i\n",test1);fflush(Patch.m_fFile);
	if(Patch.cls_cast_type[test1] & CAST_TYPE_SPONTANEOUS)
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

	//fprintf(Patch.m_fFile, "o Hook_SpellcasterType18a\n");fflush(Patch.m_fFile);

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
	__asm mov orig_eax, eax
	__asm mov orig_ebx, ebx
	__asm mov orig_ecx, ecx
	__asm mov orig_edx, edx

	//fprintf(Patch.m_fFile, "o Hook_SpellcasterType18b\n");fflush(Patch.m_fFile);

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

	//fprintf(Patch.m_fFile, "o Hook_SpellcasterType18c: cls_id %i\n",test1);fflush(Patch.m_fFile);
	if(Patch.cls_cast_type[test1] & CAST_TYPE_SPONTANEOUS)
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

	//fprintf(Patch.m_fFile, "o Hook_SpellcasterType18d: cls_id %i\n",test1);fflush(Patch.m_fFile);
	if(Patch.cls_cast_type[test1] & CAST_TYPE_SPONTANEOUS)
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

	//fprintf(Patch.m_fFile, "o Hook_SpellcasterType21: cls_id: %i\n",test1);fflush(Patch.m_fFile);
	if(Patch.cls_cast_type[test1] & CAST_TYPE_SPONTANEOUS)
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

	//fprintf(Patch.m_fFile, "o Hook_SpellcasterType22a: cls_id: %i\n",test1);fflush(Patch.m_fFile);
	if(Patch.cls_cast_type[test1] & CAST_TYPE_SPONTANEOUS)
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

	//fprintf(Patch.m_fFile, "o Hook_SpellcasterType22b: cls_id: %i\n",test1);fflush(Patch.m_fFile);
	if(Patch.cls_cast_type[test1] & CAST_TYPE_SPONTANEOUS)
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

	//fprintf(Patch.m_fFile, "o Hook_SpellcasterType22c: cls_id: %i\n",test1);fflush(Patch.m_fFile);
	if(Patch.cls_cast_type[test1] & CAST_TYPE_SPONTANEOUS)
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

	//fprintf(Patch.m_fFile, "o Hook_SpellcasterType23: cls_id: %i\n",test1);fflush(Patch.m_fFile);
	if(Patch.cls_cast_type[test1] & CAST_TYPE_ARCANE)
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

void Hook_Domains6()//0x691255 - CNWSCreatureStats_ClassInfo::GetMemorizedSpellReadyCount
{
	__asm leave
	__asm mov test1, cl
	__asm mov orig_eax, eax
	__asm mov orig_ebx, ebx
	__asm mov orig_ecx, ecx
	__asm mov orig_edx, edx
	
	//fprintf(Patch.m_fFile, "o Hook_Domains6: cls_id: %i\n",test1);fflush(Patch.m_fFile);

	if(Patch.cls_cast_type[test1] & CAST_TYPE_SELECT_DOMAINS)
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
	
	//fprintf(Patch.m_fFile, "o Hook_Domains7: cls_id: %i\n",test1);fflush(Patch.m_fFile);

	if(Patch.cls_cast_type[test1] & CAST_TYPE_SELECT_DOMAINS)
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

	//fprintf(Patch.m_fFile, "o Hook_Domains8: cls_id: %i\n",test1);fflush(Patch.m_fFile);

	if(Patch.cls_cast_type[test1] & CAST_TYPE_SELECT_DOMAINS)
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
	
	//fprintf(Patch.m_fFile, "o Hook_Domains9: cls_id: %i\n",test1);fflush(Patch.m_fFile);

	if(Patch.cls_cast_type[test1] & CAST_TYPE_SELECT_DOMAINS)
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
	
	//fprintf(Patch.m_fFile, "o Hook_Domains10: cls_id: %i\n",test1);fflush(Patch.m_fFile);

	if(Patch.cls_cast_type[test1] & CAST_TYPE_SELECT_DOMAINS)
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

	//fprintf(Patch.m_fFile, "o Hook_Domains11: cls_id: %i\n",test1);fflush(Patch.m_fFile);

	if(Patch.cls_cast_type[test1] & CAST_TYPE_SELECT_DOMAINS)
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

	//fprintf(Patch.m_fFile, "o Hook_Domains12: cls_id: %i\n",test1);fflush(Patch.m_fFile);

	if(Patch.cls_cast_type[test1] & CAST_TYPE_SELECT_DOMAINS)
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

	//fprintf(Patch.m_fFile, "o Hook_Domains15: cls_id: %i\n",test1);fflush(Patch.m_fFile);

	if(Patch.cls_cast_type[test1] & CAST_TYPE_SELECT_DOMAINS)
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

	//fprintf(Patch.m_fFile, "o Hook_Domains16: cls_id: %i\n",test1);fflush(Patch.m_fFile);

	if(Patch.cls_cast_type[test1] & CAST_TYPE_SELECT_DOMAINS)
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

	//fprintf(Patch.m_fFile, "o Hook_Domains17: cls_id: %i\n",test1);fflush(Patch.m_fFile);

	if(Patch.cls_cast_type[test1] & CAST_TYPE_SELECT_DOMAINS)
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

void CNWNXPatch::RemoveCopyItemAndModifyColorCap()
{
	DWORD DefaultPrivs;
	unsigned char *pPatch = (unsigned char*)0x58A872;
	//Make the memoryspace writeable
	VirtualProtect(pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	//0x0058A871: BA [04] 00 00 00: mov edx 0x04
	pPatch[0]=0xFF; //<- set cap to 255
	//Restore the privs back to default
	VirtualProtect(pPatch, 1, DefaultPrivs, NULL);

	fprintf(m_fFile, "o Disabling limitation in CopyItemAndModify function.\n");
	fflush(m_fFile);
}

void CNWNXPatch::SpecialAttacks()
{
	DWORD DefaultPrivs;

	unsigned char *pPatch = (unsigned char *)0x54A049;
	VirtualProtect(pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_SpecAttacks1 - (uint32_t)(pPatch + 5);
	VirtualProtect(pPatch, 1, DefaultPrivs, NULL);

	pPatch = (unsigned char*)0x547AAE;
	VirtualProtect(pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_SpecAttacks2 - (uint32_t)(pPatch + 5);
	VirtualProtect(pPatch, 1, DefaultPrivs, NULL);

	pPatch = (unsigned char*)0x54B996;
	VirtualProtect(pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_SpecAttacks3 - (uint32_t)(pPatch + 5);
	VirtualProtect(pPatch, 1, DefaultPrivs, NULL);

	pPatch = (unsigned char*)0x54BB0C;
	VirtualProtect(pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_SpecAttacks4 - (uint32_t)(pPatch + 5);
	VirtualProtect(pPatch, 1, DefaultPrivs, NULL);
	 
	fprintf(m_fFile, "o Softcoding special attacks.\n");
	fflush(m_fFile);
}

void CNWNXPatch::DevastatingCritical()
{
	unsigned char *pPatch = (unsigned char*)0x54D5D0;
	DWORD DefaultPrivs;
	VirtualProtect(pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);

	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_DevastatingCriticalMelee - (uint32_t)(pPatch + 5);
	VirtualProtect((DWORD*)pPatch, 1, DefaultPrivs, NULL);

	pPatch = (unsigned char*)0x54DFDD;
	VirtualProtect(pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_DevastatingCriticalRanged - (uint32_t)(pPatch + 5);
	VirtualProtect(pPatch, 1, DefaultPrivs, NULL);
	 
	fprintf(m_fFile, "o Sofcoding Devastating Critical ability.\n");
	fflush(m_fFile);
}

void CNWNXPatch::AssassinDeathAttack()
{
	unsigned char *pPatch = (unsigned char*)0x54CC4A;
	DWORD DefaultPrivs;
	VirtualProtect(pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_AssassinDeathAttack - (uint32_t)(pPatch + 5);
	VirtualProtect(pPatch, 1, DefaultPrivs, NULL);

	fprintf(m_fFile, "o Sofcoding Assassin's Death Attack OnHit ability.\n");
	fflush(m_fFile);
}

void CNWNXPatch::SneakAttackCalculation()
{
	unsigned char *pPatch = (unsigned char*)0x476CD2;
	DWORD DefaultPrivs;
	VirtualProtect(pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_SneakAttackCalculation - (uint32_t)(pPatch + 5);
	VirtualProtect(pPatch, 1, DefaultPrivs, NULL);

	fprintf(m_fFile, "o Fixing Improved sneak attack issue.\n");
	fflush(m_fFile);
}

void CNWNXPatch::DeathSneakAttackImmunity()
{
	unsigned char *pPatch = (unsigned char*)0x54C1CA;
	DWORD DefaultPrivs;
	VirtualProtect(pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);

	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_SneakAttackImmunity - (uint32_t)(pPatch + 5);
	VirtualProtect(pPatch, 1, DefaultPrivs, NULL);
	pPatch = (unsigned char*)0x54C70C;
	DefaultPrivs = NULL;
	VirtualProtect(pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_DeathAttackImmunity - (uint32_t)(pPatch + 5);
	VirtualProtect(pPatch, 1, DefaultPrivs, NULL);

	fprintf(m_fFile, "o Detaching sneak attack immunity from critical hit immunity.\n");
	fflush(m_fFile);
}

void CNWNXPatch::HealKit()
{
	unsigned char *pPatch = (unsigned char *)0x4CA74F;
	DWORD DefaultPrivs;
	VirtualProtect((DWORD*)pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_HealersKit - (uint32_t)(pPatch + 5);
	VirtualProtect((DWORD*)pPatch, 1, DefaultPrivs, NULL);

	fprintf(m_fFile, "o Softcoding healer's kit.\n");
	fflush(m_fFile);
}

void CNWNXPatch::CombatMode()
{
	unsigned char *pPatch = (unsigned char *)0x53D716;//CNWSMessage::HandlePlayerToServerInputWalkToWaypoint
	DWORD DefaultPrivs;
	VirtualProtect((DWORD*)pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_CombatMode1 - (uint32_t)(pPatch + 5);
	VirtualProtect((DWORD*)pPatch, 1, DefaultPrivs, NULL);

	pPatch = (unsigned char *)0x53D129;//CNWSMessage::HandlePlayerToServerInputDriveControl
	VirtualProtect((DWORD*)pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_CombatMode2 - (uint32_t)(pPatch + 5);
	VirtualProtect((DWORD*)pPatch, 1, DefaultPrivs, NULL);

	pPatch = (unsigned char *)0x54746D;//CNWSCreature::AIActionAttackObject
	VirtualProtect((DWORD*)pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_CombatMode3 - (uint32_t)(pPatch + 5);
	VirtualProtect((DWORD*)pPatch, 1, DefaultPrivs, NULL);	

	fprintf(m_fFile, "o Patching automatic combat mode canceling.\n");
	fflush(m_fFile);
}

void CNWNXPatch::SpontaneousSpell()
{
	unsigned char *pPatch = (unsigned char *)0x53F564;
	DWORD DefaultPrivs;
	VirtualProtect((DWORD*)pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_SpontaneousSpell - (uint32_t)(pPatch + 5);
	VirtualProtect((DWORD*)pPatch, 1, DefaultPrivs, NULL);

	fprintf(m_fFile, "o Enabling spontaneous casting for other classes.\n");
	fflush(m_fFile);
}

void CNWNXPatch::ExamineCRNPCOnly()
{
	unsigned char *pPatch = (unsigned char *) 0x446DF9;
	DWORD DefaultPrivs;
	VirtualProtect((DWORD*)pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_ExamineCR - (uint32_t)(pPatch + 5);
	VirtualProtect((DWORD*)pPatch, 1, DefaultPrivs, NULL);

	fprintf(m_fFile, "o Examine CR only for NPCs.\n");
	fflush(m_fFile);
}

void CNWNXPatch::MindImmunity()
{
	unsigned char *pPatch = (unsigned char *)0x4F0F34;
	DWORD DefaultPrivs;
	VirtualProtect((DWORD*)pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_MindImmunity - (uint32_t)(pPatch + 5);
	VirtualProtect((DWORD*)pPatch, 1, DefaultPrivs, NULL);

	fprintf(m_fFile, "o Patching mind immunity.\n");
	fflush(m_fFile);
}

void CNWNXPatch::RemoveItemChargesCap()
{
	DWORD DefaultPrivs;
	unsigned char *pPatch = (unsigned char*)0x58E36B;
	VirtualProtect(pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	pPatch[0]=0x64;//trying to set higher values resulted in weird behavior
	VirtualProtect(pPatch, 1, DefaultPrivs, NULL);
	pPatch = (unsigned char*)0x58E36F;
	VirtualProtect(pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	pPatch[0]=0x64;
	VirtualProtect(pPatch, 1, DefaultPrivs, NULL);

	fprintf(m_fFile, "o Increasing limit in SetItemCharges function to 100.\n");
	fflush(m_fFile);
}

void CNWNXPatch::Speed()
{
	unsigned char *pPatch = (unsigned char *)0x4F2653;
	DWORD DefaultPrivs;
	VirtualProtect((DWORD*)pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_Speed - (uint32_t)(pPatch + 5);
	VirtualProtect((DWORD*)pPatch, 1, DefaultPrivs, NULL);

	fprintf(m_fFile, "o Patching speed calculation.\n");
	fflush(m_fFile);
}

void CNWNXPatch::SpellSlotsCrash()
{
	unsigned char *pPatch = (unsigned char *)0x442194;
	DWORD DefaultPrivs;
	VirtualProtect((DWORD*)pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_SpellSlotsCrash - (uint32_t)(pPatch + 5);
	VirtualProtect((DWORD*)pPatch, 1, DefaultPrivs, NULL);

	fprintf(m_fFile, "o Patching 255 spellslots crash.\n");
	fflush(m_fFile);
}

void CNWNXPatch::NewCharacterValidation()
{
	unsigned char *pPatch = (unsigned char *)0x4548A2;
	DWORD DefaultPrivs;
	VirtualProtect((DWORD*)pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_NewCharacter - (uint32_t)(pPatch + 5);
	VirtualProtect((DWORD*)pPatch, 1, DefaultPrivs, NULL);

	fprintf(m_fFile, "o New character validation.\n");
	fflush(m_fFile);
}

void CNWNXPatch::AutoMap()
{
	DWORD DefaultPrivs;
	unsigned char *pPatch = (unsigned char*)0x494DBD;
	VirtualProtect(pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	pPatch[0]= NumTilesExplored;
	VirtualProtect(pPatch, 1, DefaultPrivs, NULL);
	fprintf(m_fFile, "o Changing number of tiles explored to %i.\n",NumTilesExplored);
	fflush(m_fFile);
}

void CNWNXPatch::CustomToken()
{
	unsigned char *pPatch = (unsigned char *)0x576EBF;
	DWORD DefaultPrivs;
	VirtualProtect((DWORD*)pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_CustomToken - (uint32_t)(pPatch + 5);
	VirtualProtect((DWORD*)pPatch, 1, DefaultPrivs, NULL);

	fprintf(m_fFile, "o Enabling to set <CUSTOM0> to <CUSTOM9>.\n");
	fflush(m_fFile);
}

void CNWNXPatch::GetUnarmedDamage()
{
	unsigned char *pPatch = (unsigned char *)0x47090F;
	DWORD DefaultPrivs;
	VirtualProtect((DWORD*)pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_GetUnarmedDamageDice - (uint32_t)(pPatch + 5);
	VirtualProtect((DWORD*)pPatch, 1, DefaultPrivs, NULL);

	fprintf(m_fFile, "o Patching Shou Disciple+Monk unarmed damage calculation.\n");
	fflush(m_fFile);
}

void CNWNXPatch::Unpossess()
{
	unsigned char *pPatch = (unsigned char *)0x576EBF;
	DWORD DefaultPrivs;
	VirtualProtect((DWORD*)pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_Unpossess - (uint32_t)(pPatch + 5);
	VirtualProtect((DWORD*)pPatch, 1, DefaultPrivs, NULL);

	fprintf(m_fFile, "o Removing automatic unpossess.\n");
	fflush(m_fFile);
}

void CNWNXPatch::PatchSpellCasting()
{
	DWORD DefaultPrivs;
	unsigned char *pPatch = (unsigned char*)0x480408;////CNWSCreatureStats::AddKnownSpell
	VirtualProtect((DWORD*)pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_SpellcasterType7 - (uint32_t)(pPatch + 5);
	VirtualProtect((DWORD*)pPatch, 1, DefaultPrivs, NULL);
	fprintf(m_fFile, "o Enabling custom spellcasting #7.\n");

	pPatch = (unsigned char*)0x482AA5;//CNWSCreatureStats::ReadySpellLevel
	VirtualProtect((DWORD*)pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_SpellcasterType13a - (uint32_t)(pPatch + 5);
	VirtualProtect((DWORD*)pPatch, 1, DefaultPrivs, NULL);
	fprintf(m_fFile, "o Enabling custom spellcasting #13a.\n");

	pPatch = (unsigned char*)0x482D02;//CNWSCreatureStats::UnReadySpell
	VirtualProtect((DWORD*)pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_SpellcasterType13b - (uint32_t)(pPatch + 5);
	VirtualProtect((DWORD*)pPatch, 1, DefaultPrivs, NULL);
	fprintf(m_fFile, "o Enabling custom spellcasting #13b.\n");

	pPatch = (unsigned char*)0x4A1D2D;//CNWSCreature::BroadcastSpellCast
	VirtualProtect((DWORD*)pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_SpellcasterType14 - (uint32_t)(pPatch + 5);
	VirtualProtect((DWORD*)pPatch, 1, DefaultPrivs, NULL);
	fprintf(m_fFile, "o Enabling custom spellcasting #14.\n");

	pPatch = (unsigned char*)0x479EC2;//CNWSCreatureStats::ReadStatsFromGFF
	VirtualProtect((DWORD*)pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_SpellcasterType18a - (uint32_t)(pPatch + 5);
	VirtualProtect((DWORD*)pPatch, 1, DefaultPrivs, NULL);
	fprintf(m_fFile, "o Enabling custom spellcasting #18a.\n");

	pPatch = (unsigned char*)0x47BED7;//CNWSCreatureStats::SaveClassInfo
	VirtualProtect((DWORD*)pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_SpellcasterType18b - (uint32_t)(pPatch + 5);
	VirtualProtect((DWORD*)pPatch, 1, DefaultPrivs, NULL);
	fprintf(m_fFile, "o Enabling custom spellcasting #18b.\n");

	pPatch = (unsigned char*)0x47BA42;//CNWSCreatureStats::SaveClassInfo
	VirtualProtect((DWORD*)pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_SpellcasterType18c - (uint32_t)(pPatch + 5);
	VirtualProtect((DWORD*)pPatch, 1, DefaultPrivs, NULL);
	fprintf(m_fFile, "o Enabling custom spellcasting #18c.\n");

	pPatch = (unsigned char*)0x478E3A;//CNWSCreatureStats::ReadStatsFromGFF
	VirtualProtect((DWORD*)pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_SpellcasterType18d - (uint32_t)(pPatch + 5);
	VirtualProtect((DWORD*)pPatch, 1, DefaultPrivs, NULL);
	fprintf(m_fFile, "o Enabling custom spellcasting #18d.\n");

	pPatch = (unsigned char*)0x43902A;//CNWSMessage::ComputeLastUpdate_GuiKnownSpellUses
	VirtualProtect((DWORD*)pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_SpellcasterType21 - (uint32_t)(pPatch + 5);
	VirtualProtect((DWORD*)pPatch, 1, DefaultPrivs, NULL);
	fprintf(m_fFile, "o Enabling custom spellcasting #21.\n");

	pPatch = (unsigned char*)0x442089;//CNWSMessage::WriteGameObjUpdate_PlayerUpdate
	VirtualProtect((DWORD*)pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_SpellcasterType22a - (uint32_t)(pPatch + 5);
	VirtualProtect((DWORD*)pPatch, 1, DefaultPrivs, NULL);
	fprintf(m_fFile, "o Enabling custom spellcasting #22a.\n");

	pPatch = (unsigned char*)0x442223;//CNWSMessage::WriteGameObjUpdate_PlayerUpdate
	VirtualProtect((DWORD*)pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_SpellcasterType22b - (uint32_t)(pPatch + 5);
	VirtualProtect((DWORD*)pPatch, 1, DefaultPrivs, NULL);
	fprintf(m_fFile, "o Enabling custom spellcasting #22b.\n");

	pPatch = (unsigned char*)0x442398;//CNWSMessage::WriteGameObjUpdate_PlayerUpdate
	VirtualProtect((DWORD*)pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_SpellcasterType22c - (uint32_t)(pPatch + 5);
	VirtualProtect((DWORD*)pPatch, 1, DefaultPrivs, NULL);
	fprintf(m_fFile, "o Enabling custom spellcasting #22c.\n");

	pPatch = (unsigned char*)0x4BDA2B;//CNWSCreature::AIActionCastSpell
	VirtualProtect((DWORD*)pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_SpellcasterType23 - (uint32_t)(pPatch + 5);
	VirtualProtect((DWORD*)pPatch, 1, DefaultPrivs, NULL);
	fprintf(m_fFile, "o Enabling custom spellcasting #23.\n");

	pPatch = (unsigned char *) 0x46C875;//CNWSCreatureStats_ClassInfo::GetMemorizedSpellReadyCount
	VirtualProtect((DWORD*)pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_Domains6 - (uint32_t)(pPatch + 5);
	VirtualProtect((DWORD*)pPatch, 1, DefaultPrivs, NULL);
	fprintf(m_fFile, "o Enabling custom spellcasting #domains6.\n");

	pPatch = (unsigned char *) 0x478DA2;//CNWSCreatureStats::ReadStatsFromGFF
	VirtualProtect((DWORD*)pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_Domains7 - (uint32_t)(pPatch + 5);
	VirtualProtect((DWORD*)pPatch, 1, DefaultPrivs, NULL);
	fprintf(m_fFile, "o Enabling custom spellcasting #domains7.\n");

	pPatch = (unsigned char *) 0x47B988;//CNWSCreatureStats::SaveClassInfo
	VirtualProtect((DWORD*)pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_Domains8 - (uint32_t)(pPatch + 5);
	VirtualProtect((DWORD*)pPatch, 1, DefaultPrivs, NULL);
	fprintf(m_fFile, "o Enabling custom spellcasting #domains8.\n");

	pPatch = (unsigned char *) 0x480550;//CNWSCreatureStats::SetMemorizedSpellSlot
	VirtualProtect((DWORD*)pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	//memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_Domains9 - (uint32_t)(pPatch + 5);
	VirtualProtect((DWORD*)pPatch, 1, DefaultPrivs, NULL);
	fprintf(m_fFile, "o Enabling custom spellcasting #domains9.\n");

	pPatch = (unsigned char *) 0x483831;//CNWSCreatureStats::ValidateLevelUp
	VirtualProtect((DWORD*)pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_Domains10 - (uint32_t)(pPatch + 5);
	VirtualProtect((DWORD*)pPatch, 1, DefaultPrivs, NULL);
	fprintf(m_fFile, "o Enabling custom spellcasting #domains10.\n");

	pPatch = (unsigned char *) 0x544600;//CNWSMessage::HandlePlayerToServerLevelUpMessage
	VirtualProtect((DWORD*)pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_Domains11 - (uint32_t)(pPatch + 5);
	VirtualProtect((DWORD*)pPatch, 1, DefaultPrivs, NULL);
	fprintf(m_fFile, "o Enabling custom spellcasting #domains11.\n");

	pPatch = (unsigned char *) 0x4849A1;//CNWSCreatureStats::LevelUp
	VirtualProtect((DWORD*)pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_Domains12 - (uint32_t)(pPatch + 5);
	VirtualProtect((DWORD*)pPatch, 1, DefaultPrivs, NULL);
	fprintf(m_fFile, "o Enabling custom spellcasting #domains12.\n");

	pPatch = (unsigned char *) 0x4378FD;//CNWSMessage::ComputeUpdateRequired
	VirtualProtect((DWORD*)pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_Domains15 - (uint32_t)(pPatch + 5);
	VirtualProtect((DWORD*)pPatch, 1, DefaultPrivs, NULL);
	fprintf(m_fFile, "o Enabling custom spellcasting #domains15.\n");

	pPatch = (unsigned char *) 0x4469F5;//CNWSMessage::WriteGameObjUpdate_UpdateObject
	VirtualProtect((DWORD*)pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_Domains16 - (uint32_t)(pPatch + 5);
	VirtualProtect((DWORD*)pPatch, 1, DefaultPrivs, NULL);
	fprintf(m_fFile, "o Enabling custom spellcasting #domains16.\n");

	pPatch = (unsigned char *) 0x44B4C6;//CNWSMessage::UpdateLastUpdateObject
	VirtualProtect((DWORD*)pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_Domains17 - (uint32_t)(pPatch + 5);
	VirtualProtect((DWORD*)pPatch, 1, DefaultPrivs, NULL);
	fprintf(m_fFile, "o Enabling custom spellcasting #domains17.\n");

	fflush(m_fFile);
}

void CNWNXPatch::InitializeModuleSwitches(CNWSModule *module)
{
	Patch.NoTumbleAC = module->mod_vartable.GetInt(CExoString("72_DISABLE_TUMBLE_AC")) > 0;
	Patch.NoCriticalImmunity = module->mod_vartable.GetInt(CExoString("72_DISABLE_SNEAK_CRITICAL_IMMUNITY")) > 0;
	Patch.NoMonkAbilities = module->mod_vartable.GetInt(CExoString("72_DISABLE_MONK_IN_POLYMORPH")) > 0;
	Patch.TrapImmunity = module->mod_vartable.GetInt(CExoString("72_ENABLE_FLYING_TRAP_IMMUNITY")) > 0;
	ParalysisIgnoreMindImmunity = module->mod_vartable.GetInt(CExoString("72_DISABLE_PARALYZE_MIND_SPELL_IMMUNITY")) > 0;
	Patch.PMCasterLevel = module->mod_vartable.GetInt(CExoString("71_PALEMASTER_ADDS_CASTER_LEVEL")) > 0;
	Patch.CurseIgnoreAbilityDecreaseImmunity = module->mod_vartable.GetInt(CExoString("72_CURSE_IGNORE_ABILITY_DECREASE_IMMUNITY")) > 0;
	Patch.DnDUncannyDodge = module->mod_vartable.GetInt(CExoString("72_HARDCORE_UNCANNY_DODGE")) > 0;
	Patch.PrestigeClassAffectSpontaneousCasters = true;
}

void CNWNXPatch::SendHakList(CNWSMessage *pMessage, int nPlayerID)
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

		Log(0, "Sending hak list...pMessage=%X, nPlayerID=%d, sharedHeap=%X\n", pMessage, nPlayerID, sharedHeap);

		message->CreateWriteMessage(80, -1, 1);
		message->WriteINT(haklist->len, 32);

		for(i=haklist->len-1; i > -1;i--) {
			Log(0, "\t%s\n", haklist->data[i].text);

			// CExoString() class for whatever reason is giving me a ridiculously hard time.  Even CNWSModule 
			// for all of its complexity gives me an easier time.  Going to deal with this the asm way.
			txt = (char *)HeapAlloc(sharedHeap, NULL, haklist->data[i].len);
			len = haklist->data[i].len;
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

		Log(0, "%s\n", pModule->mod_custom_tlk.text);
		// message->WriteCExoString(pModule->m_sCustomTLK, 32);
		txt = (char *)HeapAlloc(sharedHeap, NULL, pModule->mod_custom_tlk.len);
		len = pModule->mod_custom_tlk.len;
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

CNWNXPatch::CNWNXPatch() {
	heapAddress = (DWORD *)0x5EEFF00;  // nwserver keeps their heap's address at this address.
}

CNWNXPatch::~CNWNXPatch() {

}

BOOL CNWNXPatch::OnRelease()
{
	Log( 0,"o Shutting down\n" );
	return CNWNXBase::OnRelease();
}

BOOL CNWNXPatch::OnCreate(const char* LogDir)
{
	char log[MAX_PATH];
	
	sprintf(log, "%s\\nwnx_patch.txt", LogDir);

	// call the base class function
	if (!CNWNXBase::OnCreate(log))
		return false;

	fprintf(m_fFile, "Community Patch Patch plugin by Shadooow v 1.29d (Server Edition)\n\n");
	fflush(m_fFile);

	CIniFile iniFile = ("nwnplayer.ini");

	examineCRonPlayers = iniFile.ReadInteger("Server Options","Examine CR On Players",0);
	NoServerCharacter = iniFile.ReadInteger("Server Options","Disallow New Characters",0);
	DisallowAnimalCompanionPossessing = iniFile.ReadInteger("Server Options","Disallow Animal Companion Possessing",0);
	DisableStickyCombatModes = iniFile.ReadInteger("Community Patch","Disable Sticky Modes",0);

	helper = 0;
	helper_effect = NULL;
	NoTumbleAC = false;
	NoCriticalImmunity = false;
	NoMonkAbilities = false;
	TrapImmunity = false;
	ParalysisIgnoreMindImmunity = false;
	PMCasterLevel = false;
	CurseIgnoreAbilityDecreaseImmunity = false;
	DnDUncannyDodge = false;
	PrestigeClassAffectSpontaneousCasters = false;
	module_script_leave = NULL;

	for(unsigned int x=0;x<CLASS_TYPE_INVALID;x++)
	{
		cls_cast_type[x] = 0;
	}

	//Set our nwnx memory funcs
	nwnx_malloc = (void *(__cdecl *)(size_t))0x0040D550;
	//nwns free routine
	nwnx_free = (void (__cdecl *)(void *))0x0040D560;

	RemoveCopyItemAndModifyColorCap();
	RemoveItemChargesCap();
	SpecialAttacks();
	AssassinDeathAttack();
	SneakAttackCalculation();
	DevastatingCritical();
	DeathSneakAttackImmunity();
	HealKit();
	if(!DisableStickyCombatModes)
	{
		CombatMode();
	}
	else
	{
		fprintf(m_fFile, "o Patching automatic combat mode canceling disabled.\n");
		fflush(m_fFile);
	}
	SpontaneousSpell();
	MindImmunity();
	Speed();
	SpellSlotsCrash();
	NumTilesExplored = iniFile.ReadInteger("Server Options","Num Tiles Explored",0);
	if(NumTilesExplored > 0 && NumTilesExplored <= 10 && NumTilesExplored != 8)
	{
		AutoMap();
	}
	CustomToken();
	GetUnarmedDamage();
	//Unpossess();
	if(!iniFile.ReadInteger("Community Patch","DisableCustomSpellCasters",0))
	{
		PatchSpellCasting();
	}
	//Spellbook();
	//ExamineCRNPCOnly();
	//NewCharacterValidation();
	Hook();

	return true;
}

unsigned long CNWNXPatch::OnRequestObject (char *gameObject, char* Request){

	return OBJECT_INVALID;
}

void NWNXPatch_Funcs(CNWSModule *mod, int nFunc, char *Params)
{
	fprintf(Patch.m_fFile, "NWNXPatch_Funcs DEBUG: func %i, params %s\n",nFunc,Params);fflush(Patch.m_fFile);//TODO remove
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
			fprintf(Patch.m_fFile, "ERROR: GetPlayerLanguage(%08X) used on wrong object type!\n",oID);
		}
		mod->mod_vartable.SetInt(VarName,retVal,0);
	}
	else if(nFunc == 2)//GetObjectById
	{
		unsigned long oID = OBJECT_INVALID;
		sscanf_s(Params,"%x",&oID);
		mod->mod_vartable.SetObject(VarName,oID);
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
			NWN_AppManager->app_server->srv_internal->srv_network->DisconnectPlayer(player->pl_id,nTlkEntry,0);
		}
		else
		{
			fprintf(Patch.m_fFile, "ERROR: BootPCWithMessage(%08X,%i) used on wrong object type!\n",oID,nTlkEntry);
		}
	}
	if(nFunc == 5)//GetPCBicFileName
	{
		unsigned long oID = OBJECT_INVALID;
		sscanf_s(Params,"%x",&oID);
		CNWSPlayer *player = NWN_AppManager->app_server->srv_internal->GetClientObjectByObjectId(oID);
		if(oID != OBJECT_INVALID && player)
		{
			mod->mod_vartable.SetString(VarName,CExoString(player->m_resFileName.resref));
		}
		else
		{
			fprintf(Patch.m_fFile, "ERROR: GetPCBicFileName(%08X) used on wrong object type!\n",oID);
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
			fprintf(Patch.m_fFile, "ERROR: SetCanCastInPolymorph(%08X,%i) used with incorrect parameters!\n",oID,bAllowed);
		}
	}
	else if(nFunc == 7)//GetIsFeatGranted
	{
		unsigned long nClass = 255;
		unsigned long nFeat = OBJECT_INVALID;
		sscanf_s(Params,"%i|%i",&nClass,&nFeat);
		if(nClass < 255 && nFeat != OBJECT_INVALID)
		{
			CNWClass *cls = &(NWN_Rules->ru_classes[(unsigned char)nClass]);
			if(cls)
			{
				unsigned char granted = 0;
				cls->IsGrantedFeat((unsigned short)nFeat,granted);
				retVal = granted == 255 ? 0 : granted;
			}
		}
		else
		{
			fprintf(Patch.m_fFile, "ERROR: GetIsFeatGranted(%i,%i) used with incorrect parameters!\n",nClass,nFeat);
		}
		mod->mod_vartable.SetInt(VarName,retVal,0);
	}
	else if(nFunc == 8)//HighlightObject
	{
		unsigned long oID = OBJECT_INVALID, oObject = OBJECT_INVALID, color = OBJECT_INVALID;
		sscanf_s(Params,"%x|%x|%i",&oID,&oObject,&color);						
		CNWSPlayer *player = NWN_AppManager->app_server->srv_internal->GetClientObjectByObjectId(oID);
		if(oID != OBJECT_INVALID && player && oObject != OBJECT_INVALID && color != OBJECT_INVALID)
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
			fprintf(Patch.m_fFile, "ERROR: HighlightObject(%08X,%08X,%i) used with incorrect parameters!\n",oID,oObject,color);
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
			sprintf(var,"VERIFY_NWNCX_PATCH_%i",player->pl_id);
			CExoString VarName = CExoString(var);
			delete var;
			CNWSModule *mod = NWN_AppManager->app_server->srv_internal->GetModule();
			if(mod)
			{
				retVal = mod->mod_vartable.GetInt(VarName);
			}
		}
		mod->mod_vartable.SetInt(VarName,retVal,0);
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
			fprintf(Patch.m_fFile, "ERROR: UnhighlightObject(%08X,%08X) used with incorrect parameters!\n",oID,oObject);
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
			fprintf(Patch.m_fFile, "ERROR: SetDisableObjectHighlight(%08X) used with incorrect parameters!\n",oID);
		}
	}
	if(nFunc == 101)//GetNumAreas
	{
		CNWSModule *cModule = NWN_AppManager->app_server->srv_internal->GetModule();
		if(cModule)
		{
			retVal = cModule->mod_areas_len;
		}
		else
		{
			fprintf(Patch.m_fFile, "ERROR: GetNumAreas() unknown error!\n");
		}
		mod->mod_vartable.SetInt(VarName,retVal,0);
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
			fprintf(Patch.m_fFile, "ERROR: GetNthArea(%i) invalid parameters!\n",nTh);fflush(Patch.m_fFile);
			nTh = OBJECT_INVALID;
		}
		mod->mod_vartable.SetObject(VarName,nTh);
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
			fprintf(Patch.m_fFile, "ERROR: GetNoRestFlag(%08X) used on wrong object type!\n",oID);
		}
		mod->mod_vartable.SetInt(VarName,retVal,0);
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
				fprintf(Patch.m_fFile, "ERROR: SetNoRestFlag(%08X,%i) used with incorrect parameters!\n",oID,bNoRest);
			}
		}
		else
		{
			fprintf(Patch.m_fFile, "ERROR: SetNoRestFlag(%08X,%i) used on wrong object type!\n",oID,bNoRest);
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
				fprintf(Patch.m_fFile, "ERROR: GetSurfaceMaterial(%08X,%f,%f,%f) invalid position!\n",oID,x,y,z);
			}
		}
		else
		{
			fprintf(Patch.m_fFile, "ERROR: GetSurfaceMaterial(%08X,%f,%f,%f) must be called on area!\n",oID,x,y,z);
		}
		mod->mod_vartable.SetInt(VarName,retVal,0);
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
			fprintf(Patch.m_fFile, "ERROR: GetPvPSettings(%08X) used on wrong object type!\n",oID);
		}
		mod->mod_vartable.SetInt(VarName,retVal,0);
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
				fprintf(Patch.m_fFile, "ERROR: SetPvPSettings(%08X,%i) used with incorrect parameters!\n",oID,pvp_settings);
			}
		}
		else
		{
			fprintf(Patch.m_fFile, "ERROR: SetPvPSettings(%08X,%i) used on wrong object type!\n",oID,pvp_settings);
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
					fprintf(Patch.m_fFile, "ERROR: GetTileAnimLoop(%08X,%f,%f,%f,%i) invalid position!\n",oID,x,y,z,animloop);
				}
			}
			else
			{
				fprintf(Patch.m_fFile, "ERROR: GetTileAnimLoop(%08X,%f,%f,%f,%i) invalid animloop number!\n",oID,x,y,z,animloop);
			}
		}
		else
		{
			fprintf(Patch.m_fFile, "ERROR: GetTileAnimLoop(%08X,%f,%f,%f,%i) must be called on area!\n",oID,x,y,z,animloop);
		}
		mod->mod_vartable.SetInt(VarName,retVal,0);
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
					sprintf(Params,"%f|%f|%f|%i|%i|%i",x,y,z,a1,a2,a3);
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
					fprintf(Patch.m_fFile, "ERROR: SetTileAnimLoop(%08X,%f,%f,%f,%i,%i) invalid position!\n",oID,x,y,z,animloop);
				}
			}
			else
			{
				fprintf(Patch.m_fFile, "ERROR: SetTileAnimLoop(%08X,%f,%f,%f,%i,%i) invalid animloop number or value!\n",oID,x,y,z,animloop);
			}
		}
		else
		{
			fprintf(Patch.m_fFile, "ERROR: SetTileAnimLoop(%08X,%f,%f,%f,%i,%i) must be called on area!\n",oID,x,y,z,animloop);
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
			fprintf(Patch.m_fFile, "ERROR: GetAreaWind(%08X) used on wrong object type!\n",oID);
		}
		mod->mod_vartable.SetInt(VarName,retVal,0);
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
				fprintf(Patch.m_fFile, "ERROR: SetAreaWind(%08X,%i) used with incorrect parameters!\n",oID,wind);
			}
		}
		else
		{
			fprintf(Patch.m_fFile, "ERROR: SetAreaWind(%08X,%i) used on wrong object type!\n",oID,wind);
		}
	}
	else if(nFunc == 112)//SetAreaDayTime
	{//todo remove debugs
		fprintf(Patch.m_fFile, "SetAreaDayTime call\n");fflush(Patch.m_fFile);
		unsigned long oID = OBJECT_INVALID;
		int daytime = 255;
		sscanf_s(Params,"%x|%i",&oID,&daytime);
		CNWSArea *area = NWN_AppManager->app_server->srv_internal->GetAreaByGameObjectID(oID);
		fprintf(Patch.m_fFile, "SetAreaDayTime 1\n");fflush(Patch.m_fFile);
		if(oID != OBJECT_INVALID && area)
		{
			if(daytime < 4)
			{
				if(daytime == -1)
				{
					fprintf(Patch.m_fFile, "SetAreaDayTime 2\n");fflush(Patch.m_fFile);
					if(area->are_terrain & 512)
					{
						fprintf(Patch.m_fFile, "SetAreaDayTime 3\n");fflush(Patch.m_fFile);
						area->UseDayNightCycle = 1;
						area->are_terrain&= ~512;
						CNWSModule *mod = NWN_AppManager->app_server->srv_internal->GetModule();
						if(mod)
						{
							area->are_terrain&= ~1024;
							area->are_terrain&= ~2048;
							unsigned long hour = NWN_AppManager->app_server->GetWorldTimer()->GetWorldTimeHour();
							if(hour >= mod->mod_dawnhour && hour <= mod->mod_duskhour)
							{
								area->IsNight = 0;
								if(hour == mod->mod_dawnhour) daytime = 1;
								else daytime = 0;
							}
							else
							{
								area->IsNight = 1;
								if(hour == mod->mod_duskhour) daytime = 2;
								else daytime = 3;							
							}
						}
						fprintf(Patch.m_fFile, "SetAreaDayTime 4\n");fflush(Patch.m_fFile);
					}
					if(area->are_terrain & 1024)
					{
						fprintf(Patch.m_fFile, "SetAreaDayTime 5\n");fflush(Patch.m_fFile);
						area->IsNight = 1;
						area->are_terrain&= ~1024;
						daytime = 3;
					}
					else if(area->are_terrain & 2048)
					{
						fprintf(Patch.m_fFile, "SetAreaDayTime 6\n");fflush(Patch.m_fFile);
						area->IsNight = 0;
						area->are_terrain&= ~2048;
						daytime = 0;
					}			
					fprintf(Patch.m_fFile, "SetAreaDayTime 7\n");fflush(Patch.m_fFile);
				}
				else
				{
					fprintf(Patch.m_fFile, "SetAreaDayTime 11\n");fflush(Patch.m_fFile);
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
					fprintf(Patch.m_fFile, "SetAreaDayTime 12\n");fflush(Patch.m_fFile);
				}
				uint32_t object;
				CNWSPlayer *player;
				fprintf(Patch.m_fFile, "SetAreaDayTime 20\n");fflush(Patch.m_fFile);
				for(unsigned int x=0;x < area->obj_list_len;x++)
				{
					object = area->obj_list[x];
					player = NWN_AppManager->app_server->srv_internal->GetClientObjectByObjectId(object);
					if(player)
					{
						fprintf(Patch.m_fFile, "SetAreaDayTime 90\n");fflush(Patch.m_fFile);
						unsigned char *pData;
						long unsigned int nSize;
						CNWMessage *message = new CNWMessage();
						fprintf(Patch.m_fFile, "SetAreaDayTime 91\n");fflush(Patch.m_fFile);
						message->CreateWriteMessage(80, -1, 1);
						fprintf(Patch.m_fFile, "SetAreaDayTime 92\n");fflush(Patch.m_fFile);
						message->WriteINT(daytime,32);
						fprintf(Patch.m_fFile, "SetAreaDayTime 93\n");fflush(Patch.m_fFile);
						message->GetWriteMessage((unsigned char **) &pData, (unsigned long *) &nSize);
						fprintf(Patch.m_fFile, "SetAreaDayTime 94\n");fflush(Patch.m_fFile);
						NWN_AppManager->app_server->srv_internal->srv_client_messages->SendServerToPlayerMessage(player->pl_id, 204, 2, pData, nSize);
						delete message;
						fprintf(Patch.m_fFile, "SetAreaDayTime 95\n");fflush(Patch.m_fFile);
					}
				}
			}
			else
			{
				fprintf(Patch.m_fFile, "ERROR: SetAreaDayTime(%08X,%i) used with incorrect parameters!\n",oID,daytime);
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
				fprintf(Patch.m_fFile, "ERROR: SetAreaDayTime(%08X,%i) used with incorrect parameters!\n",oID,daytime);
			}
		}
		else
		{
			fprintf(Patch.m_fFile, "ERROR: SetAreaDayTime(%08X,%i) used on wrong object type!\n",oID,daytime);
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
				fprintf(Patch.m_fFile, "ERROR: GetAreaAmbientColor(%08X,%i) used with incorrect parameters!\n",oID,type);
			}
		}
		else
		{
			fprintf(Patch.m_fFile, "ERROR: GetAreaAmbientColor(%08X,%i) used on wrong object type!\n",oID,type);
		}
		mod->mod_vartable.SetInt(VarName,retVal,0);
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
				fprintf(Patch.m_fFile, "ERROR: SetAreaAmbientColor(%08X,%i,%i) used with incorrect parameters!\n",oID,type,color);
			}
		}
		else
		{
			fprintf(Patch.m_fFile, "ERROR: SetAreaAmbientColor(%08X,%i,%i) used on wrong object type!\n",oID,type,color);
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
				fprintf(Patch.m_fFile, "ERROR: GetAreaDiffuseColor(%08X,%i) used with incorrect parameters!\n",oID,type);
			}
		}
		else
		{
			fprintf(Patch.m_fFile, "ERROR: GetAreaDiffuseColor(%08X,%i) used on wrong object type!\n",oID,type);
		}
		mod->mod_vartable.SetInt(VarName,retVal,0);
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
				fprintf(Patch.m_fFile, "ERROR: SetAreaDiffuseColor(%08X,%i,%i) used with incorrect parameters!\n",oID,type,color);
			}
		}
		else
		{
			fprintf(Patch.m_fFile, "ERROR: SetAreaDiffuseColor(%08X,%i,%i) used on wrong object type!\n",oID,type,color);
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
				fprintf(Patch.m_fFile, "ERROR: GetAreaShadowsEnabled(%08X,%i) used with incorrect parameters!\n",oID,type);
			}
		}
		else
		{
			fprintf(Patch.m_fFile, "ERROR: GetAreaShadowsEnabled(%08X,%i) used on wrong object type!\n",oID,type);
		}
		mod->mod_vartable.SetInt(VarName,retVal,0);
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
				fprintf(Patch.m_fFile, "ERROR: SetAreaShadowsEnabled(%08X,%i,%i) used with incorrect parameters!\n",oID,type,value);
			}
		}
		else
		{
			fprintf(Patch.m_fFile, "ERROR: SetAreaShadowsEnabled(%08X,%i,%i) used on wrong object type!\n",oID,type,value);
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
			fprintf(Patch.m_fFile, "ERROR: GetAreaLightningChance(%08X,%i) used on wrong object type!\n",oID,type);
		}
		mod->mod_vartable.SetInt(VarName,retVal,0);
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
				fprintf(Patch.m_fFile, "ERROR: SetAreaLightningChance(%08X,%i) used with incorrect parameters!\n",oID,value);
			}
		}
		else
		{
			fprintf(Patch.m_fFile, "ERROR: SetAreaLightningChance(%08X,%i) used on wrong object type!\n",oID,value);
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
			fprintf(Patch.m_fFile, "ERROR: GetAreaSpotModifier(%08X,%i) used on wrong object type!\n",oID,type);
		}
		mod->mod_vartable.SetInt(VarName,retVal,0);
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
				fprintf(Patch.m_fFile, "ERROR: SetAreaSpotModifier(%08X,%i) used with incorrect parameters!\n",oID,value);
			}
		}
		else
		{
			fprintf(Patch.m_fFile, "ERROR: SetAreaSpotModifier(%08X,%i) used on wrong object type!\n",oID,value);
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
			fprintf(Patch.m_fFile, "ERROR: GetListenSpotModifier(%08X,%i) used on wrong object type!\n",oID,type);
		}
		mod->mod_vartable.SetInt(VarName,retVal,0);
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
				fprintf(Patch.m_fFile, "ERROR: SetListenSpotModifier(%08X,%i) used with incorrect parameters!\n",oID,value);
			}
		}
		else
		{
			fprintf(Patch.m_fFile, "ERROR: SetListenSpotModifier(%08X,%i) used on wrong object type!\n",oID,value);
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
				fprintf(Patch.m_fFile, "effect #no %i: id: %i, type: %i, subtype: %i, durtype: %i, creator: %i, spellid: %i, casterlvl: %i, value0: %i, value1: %i, value2: %i, exposed: %i, skip %i, iconshown %i\n",i,eff,eff->eff_type,subtype,durtype,eff->eff_creator,eff->eff_spellid,eff->eff_casterlvl,eff->eff_integers[0],eff->eff_integers[1],eff->eff_integers[2],eff->eff_is_exposed,eff->eff_skiponload,eff->eff_is_iconshown);
			}
		}
		else
		{
			fprintf(Patch.m_fFile, "ERROR: DumpEffects(%08X) used on wrong object type!\n",oID);
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
				fprintf(Patch.m_fFile, "ERROR: SetCurrentHitPoints(%08X,%i) used with incorrect parameters!\n",oID,nHP);
			}
		}
		else
		{
			fprintf(Patch.m_fFile, "ERROR: SetCurrentHitPoints(%08X,%i) used on wrong object type!\n",oID,nHP);
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
				CNWSModule *module = (NWN_AppManager->app_server->srv_internal)->GetModule();
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
				fprintf(Patch.m_fFile, "ERROR: SetTag(%08X,%s) used with incorrect parameters!\n",oID,Params);
			}
		}
		else
		{
			fprintf(Patch.m_fFile, "ERROR: SetTag(%08X,%s) used on wrong object type!\n",oID,Params);
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
					fprintf(Patch.m_fFile, "ERROR: SetTrapFlagged(%08X,%i) used on wrong object type!\n",oID,bFlagged);
				}
			}
			else
			{
				fprintf(Patch.m_fFile, "ERROR: SetTrapFlagged(%08X,%i) used with incorrect parameters!\n",oID,bFlagged);
			}
		}
		else
		{
			fprintf(Patch.m_fFile, "ERROR: SetTrapFlagged(%08X,%i) used on wrong object type!\n",oID,bFlagged);
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
					fprintf(Patch.m_fFile, "ERROR: SetTrapCreator(%08X,%08X) used on wrong object type!\n",oID,oCreator);
				}
			}
			else
			{
				fprintf(Patch.m_fFile, "ERROR: SetTrapCreator(%08X,%08X) used with incorrect parameters!\n",oID,oCreator);
			}
		}
		else
		{
			fprintf(Patch.m_fFile, "ERROR: SetTrapCreator(%08X,%08X) used on wrong object type!\n",oID,oCreator);
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
					mod->mod_vartable.SetString(VarName,CExoString(door->door_conv));
				}
			}
			else if(object->obj_type2 == OBJECT_TYPE2_PLACEABLE)
			{
				CNWSPlaceable *plc = NWN_AppManager->app_server->srv_internal->GetPlaceableByGameObjectID(oID);
				if(plc)
				{
					mod->mod_vartable.SetString(VarName,CExoString(plc->plc_conv));
				}
			}
			else if(object->obj_type2 == OBJECT_TYPE2_CREATURE)
			{
				CNWSCreature *cre = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(oID);
				if(cre)
				{
					mod->mod_vartable.SetString(VarName,CExoString(cre->cre_stats->cs_conv));
				}
			}
			else
			{
				fprintf(Patch.m_fFile, "ERROR: GetConversation(%08X) used on wrong object type!\n",oID);
			}
		}
		else
		{
			fprintf(Patch.m_fFile, "ERROR: GetConversation(%08X) used with incorrect parameters!\n",oID);
		}
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
				fprintf(Patch.m_fFile, "ERROR: SetConversation(%08X,%s) used on wrong object type!\n",oID,Params);
			}
		}
		else
		{
			fprintf(Patch.m_fFile, "ERROR: SetConversation(%08X,%s) used with incorrect parameters!\n",oID,Params);
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
				fprintf(Patch.m_fFile, "ERROR: SetBaseItemType(%08X,%i) used with incorrect parameters!\n",oID,nBT);
			}
		}
		else
		{
			fprintf(Patch.m_fFile, "ERROR: SetBaseItemType(%08X,%i) used on wrong object type!\n",oID,nBT);
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
				threat = NWN_Rules->ru_baseitems->GetBaseItem(baseitem)->CritThreat;
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
		mod->mod_vartable.SetInt(VarName,retVal,0);
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
				multiplier = NWN_Rules->ru_baseitems->GetBaseItem(baseitem)->CritHitMult;
				if(multiplier < 1) multiplier = 1;
				if(oID != OBJECT_INVALID && cre && cre->cre_stats->HasFeat(883) && cre->cre_stats->GetIsWeaponOfChoice(baseitem))//increased multiplier
				{	
					multiplier++;
				}
			}
			retVal = multiplier;	
		}
		mod->mod_vartable.SetInt(VarName,retVal,0);
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
			fprintf(Patch.m_fFile, "ERROR: CheckItemFitsInventory(%08X,%08X) used on wrong object type!\n",oID,oItem);
		}
		mod->mod_vartable.SetInt(VarName,retVal,0);
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
				fprintf(Patch.m_fFile, "ERROR: SetCreatureSize(%08X,%i) used with incorrect parameters!\n",oID,newSize);
			}
		}
		else
		{
			fprintf(Patch.m_fFile, "ERROR: SetCreatureSize(%08X,%i) used on wrong object type!\n",oID,newSize);
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
			fprintf(Patch.m_fFile, "ERROR: GetEquipmentWeight(%08X) used on wrong object type!\n",oID);
		}
		mod->mod_vartable.SetInt(VarName,retVal,0);
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
				fprintf(Patch.m_fFile, "ERROR: SetGold(%08X,%i) used with incorrect parameters!\n",oID,nGold);
			}
		}
		else
		{
			fprintf(Patch.m_fFile, "ERROR: SetGold(%08X,%i) used on wrong object type!\n",oID,nGold);
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
			fprintf(Patch.m_fFile, "ERROR: GetSoundSetId(%08X) used on wrong object type!\n",oID);
		}
		mod->mod_vartable.SetInt(VarName,retVal,0);
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
				fprintf(Patch.m_fFile, "ERROR: SetSoundSetId(%08X,%i) used with incorrect parameters!\n",oID,nSoundSet);
			}
		}
		else
		{
			fprintf(Patch.m_fFile, "ERROR: SetSoundSetId(%08X,%i) used on wrong object type!\n",oID,nSoundSet);
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
				fprintf(Patch.m_fFile, "ERROR: JumpToLimbo(%08X) unknown error!\n",oID);
			}
		}
		else
		{
			fprintf(Patch.m_fFile, "ERROR: JumpToLimbo(%08X) used on wrong object type!\n",oID);
		}
	}
	else if(nFunc == 407)//GetMovementRateFactor
	{
		float fSpeed = -1.0;
		unsigned long oID = OBJECT_INVALID;
		sscanf_s(Params,"%x",&oID);
		CNWSCreature *cre = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(oID);
		if(oID != OBJECT_INVALID && cre)
		{
			fSpeed = cre->GetMovementRateFactor();
		}
		else
		{
			fprintf(Patch.m_fFile, "ERROR: GetMovementRateFactor(%08X) used on wrong object type!\n",oID);
		}
		mod->mod_vartable.SetFloat(VarName,fSpeed);
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
				fprintf(Patch.m_fFile, "ERROR: GetFlanked(%08X,%08X) used with incorrect parameters!\n",oID,oTarget);
			}
		}
		else
		{
			fprintf(Patch.m_fFile, "ERROR: GetFlanked(%08X,%08X) used on wrong object type!\n",oID,oTarget);
		}
		mod->mod_vartable.SetInt(VarName,retVal,0);
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
			fprintf(Patch.m_fFile, "ERROR: GetIsFlatFooted(%08X) used on wrong object type!\n",oID);
		}
		mod->mod_vartable.SetInt(VarName,retVal,0);
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
			fprintf(Patch.m_fFile, "ERROR: GetEncumbranceState(%08X) used on wrong object type!\n",oID);
		}
		mod->mod_vartable.SetInt(VarName,retVal,0);
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
				fprintf(Patch.m_fFile, "ERROR: SetMovementRate(%08X,%i) used with incorrect parameters!\n",oID,mov_rate);
			}
		}
		else
		{
			fprintf(Patch.m_fFile, "ERROR: SetMovementRate(%08X,%i) used on wrong object type!\n",oID,mov_rate);
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
					baseitem = NWN_Rules->ru_baseitems->GetBaseItem(weapon->it_baseitemtype);
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
				fprintf(Patch.m_fFile, "ERROR: BroadcastAttackOfOpportunity(%08X,%08X,%i) used with incorrect parameters!\n",oID,oTarget,bAllowRanged);
			}
		}
		else
		{
			fprintf(Patch.m_fFile, "ERROR: BroadcastAttackOfOpportunity(%08X,%08X,%i) used on wrong object type!\n",oID,oTarget,bAllowRanged);
		}
	}
	else if(nFunc == 413)//GetUsedDeflectArrows
	{
		unsigned long oID = OBJECT_INVALID;
		sscanf_s(Params,"%x",&oID);
		CNWSCreature *cre = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(oID);
		if(oID != OBJECT_INVALID && cre)
		{
			retVal = cre->cre_combat_round->DeflectArrow;
		}
		else
		{
			fprintf(Patch.m_fFile, "ERROR: GetUsedDeflectArrows(%08X) used on wrong object type!\n",oID);
		}
		mod->mod_vartable.SetInt(VarName,retVal,0);
	}
	else if(nFunc == 414)//SetUsedDeflectArrows
	{
		unsigned long oID = OBJECT_INVALID, DeflectArrow = OBJECT_INVALID;
		sscanf_s(Params,"%x|%i",&oID,&DeflectArrow);
		CNWSCreature *cre = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(oID);
		if(oID != OBJECT_INVALID && cre)
		{
			if(DeflectArrow < 255)
			{
				cre->cre_combat_round->DeflectArrow = DeflectArrow;
			}
			else
			{
				fprintf(Patch.m_fFile, "ERROR: SetUsedDeflectArrows(%08X,%i) used with incorrect parameters!\n",oID,DeflectArrow);
			}
		}
		else
		{
			fprintf(Patch.m_fFile, "ERROR: SetUsedDeflectArrows(%08X,%i) used on wrong object type!\n",oID,DeflectArrow);
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
				fprintf(Patch.m_fFile, "ERROR: SetRacialType(%08X,%i) used with incorrect parameters!\n",oID,nRace);
			}
		}
		else
		{
			fprintf(Patch.m_fFile, "ERROR: SetRacialType(%08X,%i) used on wrong object type!\n",oID,nRace);
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
				fprintf(Patch.m_fFile, "ERROR: SetXP(%08X,%i) used with incorrect parameters!\n",oID,nXP);
			}
		}
		else
		{
			fprintf(Patch.m_fFile, "ERROR: SetXP(%08X,%i) used on wrong object type!\n",oID,nXP);
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
				fprintf(Patch.m_fFile, "ERROR: SetAge(%08X,%i) used with incorrect parameters!\n",oID,nAge);
			}
		}
		else
		{
			fprintf(Patch.m_fFile, "ERROR: SetAge(%08X,%i) used on wrong object type!\n",oID,nAge);
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
				fprintf(Patch.m_fFile, "ERROR: SetGender(%08X,%i) used with incorrect parameters!\n",oID,nGender);
			}
		}
		else
		{
			fprintf(Patch.m_fFile, "ERROR: SetGender(%08X,%i) used on wrong object type!\n",oID,nGender);
		}
	}
	else if(nFunc == 419)//SetAbilityScore
	{
		unsigned long oID = OBJECT_INVALID;
		unsigned long nAbility = 255, nScore = 255;
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
				fprintf(Patch.m_fFile, "ERROR: SetAbilityScore(%08X,%i,%i) used with incorrect parameters!\n",oID,nAbility,nScore);
			}
		}
		else
		{
			fprintf(Patch.m_fFile, "ERROR: SetAbilityScore(%08X,%i,%i) used on wrong object type!\n",oID,nAbility,nScore);
		}
	}
	else if(nFunc == 420)//GetUsedEpicDodge
	{
		unsigned long oID = OBJECT_INVALID;
		sscanf_s(Params,"%x",&oID);
		CNWSCreature *cre = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(oID);
		if(oID != OBJECT_INVALID && cre)
		{
			retVal = cre->cre_combat_round->EpicDodgeUsed;
		}
		else
		{
			fprintf(Patch.m_fFile, "ERROR: GetUsedEpicDodge(%08X) used on wrong object type!\n",oID);
		}
		mod->mod_vartable.SetInt(VarName,retVal,0);
	}
	else if(nFunc == 421)//SetUsedEpicDodge
	{
		unsigned long oID = OBJECT_INVALID;
		unsigned long EpicDodge = 255;
		sscanf_s(Params,"%x|%i",&oID,&EpicDodge);
		CNWSCreature *cre = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(oID);
		if(oID != OBJECT_INVALID && cre)
		{
			if(EpicDodge < 255)
			{
				cre->cre_combat_round->EpicDodgeUsed = EpicDodge;
			}
			else
			{
				fprintf(Patch.m_fFile, "ERROR: SetUsedEpicDodge(%08X,%i) used with incorrect parameters!\n",oID,EpicDodge);
			}
		}
		else
		{
			fprintf(Patch.m_fFile, "ERROR: SetUsedEpicDodge(%08X,%i) used on wrong object type!\n",oID,EpicDodge);
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
			fprintf(Patch.m_fFile, "ERROR: GetEncounterFrom(%08X) used on wrong object type!\n",oID);
		}
		mod->mod_vartable.SetObject(VarName,retVal);
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
			fprintf(Patch.m_fFile, "ERROR: GetBodyBag(%08X) used on wrong object type!\n",oID);
		}
		mod->mod_vartable.SetInt(VarName,retVal,0);
	}
	else if(nFunc == 424)//SetBodyBag
	{
		unsigned long oID = OBJECT_INVALID;
		unsigned long BodyBag = 255;
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
				fprintf(Patch.m_fFile, "ERROR: SetBodyBag(%08X,%i) used with incorrect parameters!\n",oID,BodyBag);
			}
		}
		else
		{
			fprintf(Patch.m_fFile, "ERROR: SetUsedEpicDodge(%08X,%i) used on wrong object type!\n",oID,BodyBag);
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
			fprintf(Patch.m_fFile, "ERROR: GetFactionId(%08X) used on wrong object type!\n",oID);
		}
		mod->mod_vartable.SetInt(VarName,retVal,0);
	}
	else if(nFunc == 426)//SetFactionId
	{
		unsigned long oID = OBJECT_INVALID;
		unsigned long faction_id = OBJECT_INVALID;
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
				fprintf(Patch.m_fFile, "ERROR: SetFactionId(%08X,%i) used with incorrect parameters!\n",oID,faction_id);
			}
		}
		else
		{
			fprintf(Patch.m_fFile, "ERROR: SetFactionId(%08X,%i) used on wrong object type!\n",oID,faction_id);
		}
	}
	else if(nFunc == 427)//PossessCreature
	{
		unsigned long oID = OBJECT_INVALID;
		unsigned long oTarget = OBJECT_INVALID;
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
				fprintf(Patch.m_fFile, "ERROR: PossessCreature(%08X,%08X) used on wrong object type!\n",oID,oTarget);
			}
		}
		else
		{
			fprintf(Patch.m_fFile, "ERROR: PossessCreature(%08X,%08X) used with incorrect parameters!\n",oID,oTarget);
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
				fprintf(Patch.m_fFile, "ERROR: SetMovementRateFactor(%08X,%f) used with incorrect parameters!\n",oID,fSpeed);
			}
		}
		else
		{
			fprintf(Patch.m_fFile, "ERROR: SetMovementRateFactor(%08X,%f) used on wrong object type!\n",oID,fSpeed);
		}
	}
	else if(nFunc == 429)//GetTotalDamageDealtByType
	{
		unsigned long oID = OBJECT_INVALID;
		unsigned long type = OBJECT_INVALID;
		sscanf_s(Params,"%x|%i",&oID,&type);
		CNWSCreature *cre = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(oID);
		if(oID != OBJECT_INVALID && cre && Params && type != OBJECT_INVALID)
		{
			switch(type)
			{
			case 1:
				retVal = cre->cre_combat_round->GetAttack(cre->cre_combat_round->CurrentAttack)->Damage_Bludgeoning;
			break;
			case 2:
				retVal = cre->cre_combat_round->GetAttack(cre->cre_combat_round->CurrentAttack)->Damage_Piercing;
			break;
			case 4:
				retVal = cre->cre_combat_round->GetAttack(cre->cre_combat_round->CurrentAttack)->Damage_Slashing;
			break;
			case 8:
				retVal = cre->cre_combat_round->GetAttack(cre->cre_combat_round->CurrentAttack)->Damage_Magical;
			break;
			case 16:
				retVal = cre->cre_combat_round->GetAttack(cre->cre_combat_round->CurrentAttack)->Damage_Acid;
			break;
			case 32:
				retVal = cre->cre_combat_round->GetAttack(cre->cre_combat_round->CurrentAttack)->Damage_cold;
			break;
			case 64:
				retVal = cre->cre_combat_round->GetAttack(cre->cre_combat_round->CurrentAttack)->Damage_Divine;
			break;
			case 128:
				retVal = cre->cre_combat_round->GetAttack(cre->cre_combat_round->CurrentAttack)->Damage_Electrical;
			break;
			case 256:
				retVal = cre->cre_combat_round->GetAttack(cre->cre_combat_round->CurrentAttack)->Damage_Fire;
			break;
			case 512:
				retVal = cre->cre_combat_round->GetAttack(cre->cre_combat_round->CurrentAttack)->Damage_Negative;
			break;
			case 1024:
				retVal = cre->cre_combat_round->GetAttack(cre->cre_combat_round->CurrentAttack)->Damage_Positive;
			break;
			case 2048:
				retVal = cre->cre_combat_round->GetAttack(cre->cre_combat_round->CurrentAttack)->Damage_Sonic;
			break;
			case 4096:
				retVal = cre->cre_combat_round->GetAttack(cre->cre_combat_round->CurrentAttack)->BaseDamage;
			break;
			}
		}
		mod->mod_vartable.SetInt(VarName,retVal,0);
	}
	else if(nFunc == 430)//SetTotalDamageDealtByType
	{
		unsigned long oID = OBJECT_INVALID;
		unsigned long type = OBJECT_INVALID;
		unsigned long damage = OBJECT_INVALID;
		sscanf_s(Params,"%x|%i|%i",&oID,&type,&damage);
		CNWSCreature *cre = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(oID);
		if(oID != OBJECT_INVALID && cre && type != OBJECT_INVALID && damage != OBJECT_INVALID)
		{
			switch(type)
			{
			case 1:
				cre->cre_combat_round->GetAttack(cre->cre_combat_round->CurrentAttack)->Damage_Bludgeoning = (unsigned short)damage;
			break;
			case 2:
				cre->cre_combat_round->GetAttack(cre->cre_combat_round->CurrentAttack)->Damage_Piercing = (unsigned short)damage;
			break;
			case 4:
				cre->cre_combat_round->GetAttack(cre->cre_combat_round->CurrentAttack)->Damage_Slashing = (unsigned short)damage;
			break;
			case 8:
				cre->cre_combat_round->GetAttack(cre->cre_combat_round->CurrentAttack)->Damage_Magical = (unsigned short)damage;
			break;
			case 16:
				cre->cre_combat_round->GetAttack(cre->cre_combat_round->CurrentAttack)->Damage_Acid = (unsigned short)damage;
			break;
			case 32:
				cre->cre_combat_round->GetAttack(cre->cre_combat_round->CurrentAttack)->Damage_cold = (unsigned short)damage;
			break;
			case 64:
				cre->cre_combat_round->GetAttack(cre->cre_combat_round->CurrentAttack)->Damage_Divine = (unsigned short)damage;
			break;
			case 128:
				cre->cre_combat_round->GetAttack(cre->cre_combat_round->CurrentAttack)->Damage_Electrical = (unsigned short)damage;
			break;
			case 256:
				cre->cre_combat_round->GetAttack(cre->cre_combat_round->CurrentAttack)->Damage_Fire = (unsigned short)damage;
			break;
			case 512:
				cre->cre_combat_round->GetAttack(cre->cre_combat_round->CurrentAttack)->Damage_Negative = (unsigned short)damage;
			break;
			case 1024:
				cre->cre_combat_round->GetAttack(cre->cre_combat_round->CurrentAttack)->Damage_Positive = (unsigned short)damage;
			break;
			case 2048:
				cre->cre_combat_round->GetAttack(cre->cre_combat_round->CurrentAttack)->Damage_Sonic = (unsigned short)damage;
			break;
			case 4096:
				cre->cre_combat_round->GetAttack(cre->cre_combat_round->CurrentAttack)->BaseDamage = (unsigned short) damage;
			break;
			}
		}
	}
	else if(nFunc == 431)//ActionUseSpecialAttack
	{
		unsigned long oID = OBJECT_INVALID;
		unsigned long oTarget = OBJECT_INVALID;
		unsigned long feat = OBJECT_INVALID;
		sscanf_s(Params,"%x|%x|%i",&oID,&oTarget,&feat);
		CNWSCreature *cre = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(oID);
		CNWSCreature *target = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(oTarget);
		if(oID != OBJECT_INVALID && cre && oTarget != OBJECT_INVALID && target && feat != OBJECT_INVALID)
		{
			cre->AddAttackActions(oTarget,0,0,0);
			cre->cre_combat_round->AddSpecialAttack((unsigned short)feat);
		}
	}
	else if(nFunc == 432)//SetAttackRoll
	{
		unsigned long oID = OBJECT_INVALID;
		unsigned long nRoll = OBJECT_INVALID;
		sscanf_s(Params,"%x|%i",&oID,&nRoll);
		CNWSCreature *cre = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(oID);
		if(oID != OBJECT_INVALID && cre && nRoll != OBJECT_INVALID && nRoll > 0 && nRoll < 256)
		{
			cre->cre_combat_round->GetAttack(cre->cre_combat_round->CurrentAttack)->ToHitRoll = (char) nRoll;
		}
	}
	else if(nFunc == 433)//SetAttackSneak
	{
		unsigned long oID = OBJECT_INVALID;
		unsigned long nSneak = OBJECT_INVALID;
		sscanf_s(Params,"%x|%i",&oID,&nSneak);
		CNWSCreature *cre = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(oID);
		if(oID != OBJECT_INVALID && cre && nSneak != OBJECT_INVALID && nSneak >= 0 && nSneak <= 3)
		{
			CNWSCombatAttackData *attack_data = cre->cre_combat_round->GetAttack(cre->cre_combat_round->CurrentAttack); 
			if(nSneak == 0)
			{
				attack_data->SneakAttack = false;
				attack_data->DeathAttack = false;
			}
			else
			{
				if(nSneak > 1)
				{
					attack_data->DeathAttack = true;
				}
				if(nSneak == 1 || nSneak == 3)
					attack_data->SneakAttack = true;			
			}
		}
	}
	else if(nFunc == 434)//SetAttackCriticalThreatRoll
	{
		unsigned long oID = OBJECT_INVALID;
		unsigned long nRoll = OBJECT_INVALID;
		sscanf_s(Params,"%x|%i",&oID,&nRoll);
		CNWSCreature *cre = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(oID);
		if(oID != OBJECT_INVALID && cre && nRoll > 0 && nRoll < 256)
		{
			cre->cre_combat_round->GetAttack(cre->cre_combat_round->CurrentAttack)->ThreatRoll = (char) nRoll;
		}
	}
	else if(nFunc == 435)//SetAttackKillingBlow
	{
		unsigned long oID = OBJECT_INVALID;
		unsigned long nKill = OBJECT_INVALID;
		sscanf_s(Params,"%x|%i",&oID,&nKill);
		CNWSCreature *cre = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(oID);
		if(oID != OBJECT_INVALID && cre && nKill >= 0 && nKill <= 1)
		{
			cre->cre_combat_round->GetAttack(cre->cre_combat_round->CurrentAttack)->KillingBlow = nKill;
		}
	}
	else if(nFunc == 436)//SetAttackCoupeDeGrace
	{
		unsigned long oID = OBJECT_INVALID;
		unsigned long nValue = OBJECT_INVALID;
		sscanf_s(Params,"%x|%i",&oID,&nValue);
		CNWSCreature *cre = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(oID);
		if(oID != OBJECT_INVALID && cre && nValue >= 0 && nValue <= 1)
		{
			cre->cre_combat_round->GetAttack(cre->cre_combat_round->CurrentAttack)->CoupDeGrace = nValue;
			cre->cre_combat_round->GetAttack(cre->cre_combat_round->CurrentAttack)->KillingBlow = 1;
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
			fprintf(Patch.m_fFile, "ERROR: GetStartingPackage(%08X) used on wrong object type!\n",oID);
		}
		mod->mod_vartable.SetInt(VarName,retVal,0);
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
				fprintf(Patch.m_fFile, "ERROR: SetStartingPackage(%08X,%i) used with incorrect parameters!\n",oID,package);
			}
		}
		else
		{
			fprintf(Patch.m_fFile, "ERROR: SetStartingPackage(%08X,%i) used on wrong object type!\n",oID,package);
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
			fprintf(Patch.m_fFile, "ERROR: TakeItemFromCreature(%08X,%08X) used with incorrect parameters!\n",oID,oItem);
		}
	}
	else if(nFunc == 501)//GetKnowsSpell
	{
		unsigned long oID = OBJECT_INVALID;
		unsigned long cls_id = CLASS_TYPE_INVALID;
		unsigned long spell_id = OBJECT_INVALID;
		sscanf_s(Params,"%x|%i|%i",&oID,&cls_id,&spell_id);
		CNWSCreature *cre = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(oID);
		if(oID != OBJECT_INVALID && cre)
		{
			if(cls_id != CLASS_TYPE_INVALID && spell_id != OBJECT_INVALID)
			{
				unsigned char spell_lvl = NWN_Rules->ru_spells->GetSpell(spell_id)->GetSpellLevel((unsigned char)cls_id);
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
						fprintf(Patch.m_fFile, "ERROR: GetKnowsSpell(%08X,%i,%i) creature doesn't have this class!\n",oID,cls_id,spell_id);
					}
				}
				else
				{
					fprintf(Patch.m_fFile, "ERROR: GetKnowsSpell(%08X,%i,%i) not a spell of this class!\n",oID,cls_id,spell_id);
				}
			}
			else
			{
				fprintf(Patch.m_fFile, "ERROR: GetKnowsSpell(%08X,%i,%i) used with incorrect parameters!\n",oID,cls_id,spell_id);
			}
		}
		else
		{
			fprintf(Patch.m_fFile, "ERROR: GetKnowsSpell(%08X,%i,%i) used on wrong object type!\n",oID,cls_id,spell_id);
		}
		mod->mod_vartable.SetInt(VarName,retVal,0);
	}
	if(nFunc == 502)//AddKnownSpell
	{
		unsigned long oID = OBJECT_INVALID, spell_id = OBJECT_INVALID;
		unsigned long cls_id = CLASS_TYPE_INVALID;
		unsigned long ignore_limit = 0;
		sscanf_s(Params,"%x|%i|%i|%i",&oID,&cls_id,&spell_id,&ignore_limit);
		CNWSCreature *cre = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(oID);
		if(oID != OBJECT_INVALID && cre)
		{
			if(cls_id != CLASS_TYPE_INVALID && spell_id != OBJECT_INVALID)
			{
				unsigned char spell_lvl = NWN_Rules->ru_spells->GetSpell(spell_id)->GetSpellLevel((unsigned char)cls_id);
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
							unsigned char backup = Patch.cls_cast_type[cls_id];
							if(ignore_limit)
							{
								Patch.cls_cast_type[cls_id] = Patch.cls_cast_type[cls_id]^CAST_TYPE_SPONTANEOUS;//small engine hack to ignore limit of number known spells left
							}
							cre->cre_stats->AddKnownSpell(cls_pos,spell_id);
							if(ignore_limit)
							{
								Patch.cls_cast_type[cls_id] = backup;
							}
						}
						else
						{
							fprintf(Patch.m_fFile, "ERROR: AddKnownSpell(%08X,%i,%i,%i) creature already knows this spell!\n",oID,cls_id,spell_id,ignore_limit);
						}
					}
					else
					{
						fprintf(Patch.m_fFile, "ERROR: AddKnownSpell(%08X,%i,%i,%i) creature doesn't have this class!\n",oID,cls_id,spell_id,ignore_limit);
					}
				}
				else
				{
					fprintf(Patch.m_fFile, "ERROR: AddKnownSpell(%08X,%i,%i,%i) not a spell of this class!\n",oID,cls_id,spell_id,ignore_limit);
				}
			}
			else
			{
				fprintf(Patch.m_fFile, "ERROR: AddKnownSpell(%08X,%i,%i,%i) used with incorrect parameters!\n",oID,cls_id,spell_id,ignore_limit);
			}
		}
		else
		{
			fprintf(Patch.m_fFile, "ERROR: AddKnownSpell(%08X,%i,%i,%i) used on wrong object type!\n",oID,cls_id,spell_id,ignore_limit);
		}
	}
	else if(nFunc == 503)//RemoveKnownSpell
	{
		unsigned long oID = OBJECT_INVALID;
		unsigned long cls_id = CLASS_TYPE_INVALID;
		unsigned long spell_id = OBJECT_INVALID;
		sscanf_s(Params,"%x|%i|%i",&oID,&cls_id,&spell_id);
		CNWSCreature *cre = NWN_AppManager->app_server->srv_internal->GetCreatureByGameObjectID(oID);
		if(oID != OBJECT_INVALID && cre)
		{
			if(cls_id != CLASS_TYPE_INVALID && spell_id != OBJECT_INVALID)
			{
				unsigned char spell_lvl = NWN_Rules->ru_spells->GetSpell(spell_id)->GetSpellLevel((unsigned char)cls_id);
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
						fprintf(Patch.m_fFile, "ERROR: RemoveKnownSpell(%08X,%i,%i), creature doesn't have this class!\n",oID,cls_id,spell_id);
					}
				}
				else
				{
					fprintf(Patch.m_fFile, "ERROR: RemoveKnownSpell(%08X,%i,%i) not a spell of this class!\n",oID,cls_id,spell_id);
				}
			}
			else
			{
				fprintf(Patch.m_fFile, "ERROR: RemoveKnownSpell(%08X,%i,%i) used with incorrect parameters!\n",oID,cls_id,spell_id);
			}
		}
		else
		{
			fprintf(Patch.m_fFile, "ERROR: RemoveKnownSpell(%08X,%i,%i) used on wrong object type!\n",oID,cls_id,spell_id);
		}
	}
	else if(nFunc == 504)//GetKnownSpell
	{
		unsigned long oID = OBJECT_INVALID;
		unsigned long cls_id = CLASS_TYPE_INVALID;
		unsigned long spell_lvl = 255;
		unsigned long index = 255;
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
					fprintf(Patch.m_fFile, "ERROR: GetKnownSpell(%08X,%i,%i,%i) creature doesn't have this class!\n",oID,cls_id,spell_lvl,index);
				}
			}
			else
			{
				fprintf(Patch.m_fFile, "ERROR: GetKnownSpell(%08X,%i,%i,%i) used with incorrect parameters!\n",oID,cls_id,spell_lvl,index);
			}
		}
		else
		{
			fprintf(Patch.m_fFile, "ERROR: GetKnownSpell(%08X,%i,%i,%i) used on wrong object type!\n",oID,cls_id,spell_lvl,index);
		}
		mod->mod_vartable.SetInt(VarName,retVal,0);
	}
	else if(nFunc == 505)//GetSpellSchoolSpecialization
	{
		unsigned long oID = OBJECT_INVALID;
		unsigned long cls_id = CLASS_TYPE_INVALID;
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
					fprintf(Patch.m_fFile, "ERROR: GetSpellSchoolSpecialization(%08X,%i) creature doesn't have this class!\n",oID,cls_id);
				}
			}
			else
			{
				fprintf(Patch.m_fFile, "ERROR: GetSpellSchoolSpecialization(%08X,%i) used with incorrect parameters!\n",oID,cls_id);
			}
		}
		else
		{
			fprintf(Patch.m_fFile, "ERROR: GetSpellSchoolSpecialization(%08X,%i) used on wrong object type!\n",oID,cls_id);
		}
		mod->mod_vartable.SetInt(VarName,retVal,0);
	}
	else if(nFunc == 506)//SetSpellSchoolSpecialization
	{
		unsigned long oID = OBJECT_INVALID;
		unsigned long cls_id = CLASS_TYPE_INVALID;
		unsigned long school = 255;
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
					fprintf(Patch.m_fFile, "ERROR: SetSpellSchoolSpecialization(%08X,%i,%i), creature doesn't have this class!\n",oID,cls_id,school);
				}
			}
			else
			{
				fprintf(Patch.m_fFile, "ERROR: SetSpellSchoolSpecialization(%08X,%i,%i) used with incorrect parameters!\n",oID,cls_id,school);
			}
		}
		else
		{
			fprintf(Patch.m_fFile, "ERROR: SetSpellSchoolSpecialization(%08X,%i,%i) used on wrong object type!\n",oID,cls_id,school);
		}
	}
	else if(nFunc == 507)//GetDomain
	{
		unsigned long oID = OBJECT_INVALID;
		unsigned long cls_id = CLASS_TYPE_INVALID;
		unsigned long th = 255;
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
					fprintf(Patch.m_fFile, "ERROR: GetSpellSchoolSpecialization(%08X,%i,%i) creature doesn't have this class!\n",oID,cls_id,th);
				}
			}
			else
			{
				fprintf(Patch.m_fFile, "ERROR: GetSpellSchoolSpecialization(%08X,%i,%i) used with incorrect parameters!\n",oID,cls_id,th);
			}
		}
		else
		{
			fprintf(Patch.m_fFile, "ERROR: GetSpellSchoolSpecialization(%08X,%i,%i) used on wrong object type!\n",oID,cls_id,th);
		}
		mod->mod_vartable.SetInt(VarName,retVal,0);
	}
	else if(nFunc == 508)//SetDomain
	{
		unsigned long oID = OBJECT_INVALID;
		unsigned long cls_id = CLASS_TYPE_INVALID;
		unsigned long th = 255;
		unsigned long domain = 255;
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
					fprintf(Patch.m_fFile, "ERROR: SetSpellSchoolSpecialization(%08X,%i,%i,%i), creature doesn't have this class!\n",oID,cls_id,th,domain);
				}
			}
			else
			{
				fprintf(Patch.m_fFile, "ERROR: SetSpellSchoolSpecialization(%08X,%i,%i,%i) used with incorrect parameters!\n",oID,cls_id,th,domain);
			}
		}
		else
		{
			fprintf(Patch.m_fFile, "ERROR: SetSpellSchoolSpecialization(%08X,%i,%i,%i) used on wrong object type!\n",oID,cls_id,th,domain);
		}
	}
	else if(nFunc == 509)//GetMemorizedSpellSlot
	{
		unsigned long oID = OBJECT_INVALID;
		unsigned long cls_id = CLASS_TYPE_INVALID;
		unsigned long spell_lvl = 255;
		unsigned long index = OBJECT_INVALID;
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
					fprintf(Patch.m_fFile, "ERROR: GetMemorizedSpellSlot(%08X,%i,%i,%i) creature doesn't have this class!\n",oID,cls_id,spell_lvl,index);
				}
			}
			else
			{
				fprintf(Patch.m_fFile, "ERROR: GetMemorizedSpellSlot(%08X,%i,%i,%i) used with incorrect parameters!\n",oID,cls_id,spell_lvl,index);
			}
		}
		else
		{
			fprintf(Patch.m_fFile, "ERROR: GetMemorizedSpellSlot(%08X,%i,%i,%i) used on wrong object type!\n",oID,cls_id,spell_lvl,index);
		}
		mod->mod_vartable.SetInt(VarName,retVal,0);
	}
	else if(nFunc == 510)//SetMemorizedSpellSlot
	{
		unsigned long oID = OBJECT_INVALID;
		unsigned long cls_id = CLASS_TYPE_INVALID;
		unsigned long spell_lvl = 255;
		unsigned long index = OBJECT_INVALID;
		unsigned long spell_data = OBJECT_INVALID;
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
							free(cre->cre_stats->cs_classes[cls_pos].cl_spells_mem[spell_lvl].data[index]);
						}
						cre->cre_stats->cs_classes[cls_pos].cl_spells_mem[spell_lvl].data[index] = NULL;
					}
					else
					{
						if((sp = ((CNWSStats_Spell *)cre->cre_stats->cs_classes[cls_pos].cl_spells_mem[spell_lvl].data[index])) == NULL)
						{
							if((sp = ((CNWSStats_Spell *)calloc(1, sizeof(*sp)))) != NULL)
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
					fprintf(Patch.m_fFile, "ERROR: SetMemorizedSpellSlot(%08X,%i,%i,%i,%i) creature doesn't have this class!\n",oID,cls_id,spell_lvl,index,spell_data);
				}
			}
			else
			{
				fprintf(Patch.m_fFile, "ERROR: SetMemorizedSpellSlot(%08X,%i,%i,%i,%i) used with incorrect parameters!\n",oID,cls_id,spell_lvl,index,spell_data);
			}
		}
		else
		{
			fprintf(Patch.m_fFile, "ERROR: SetMemorizedSpellSlot(%08X,%i,%i,%i,%i) used on wrong object type!\n",oID,cls_id,spell_lvl,index,spell_data);
		}
	}
	else if(nFunc == 511)//GetMaxSpellSlots
	{
		unsigned long oID = OBJECT_INVALID;
		unsigned long cls_id = CLASS_TYPE_INVALID;
		unsigned long spell_lvl = 255;
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
					fprintf(Patch.m_fFile, "ERROR: GetMaxSpellSlots(%08X,%i,%i) creature doesn't have this class!\n",oID,cls_id,spell_lvl);
				}
			}
			else
			{
				fprintf(Patch.m_fFile, "ERROR: GetMaxSpellSlots(%08X,%i,%i) used with incorrect parameters!\n",oID,cls_id,spell_lvl);
			}
		}
		else
		{
			fprintf(Patch.m_fFile, "ERROR: GetMaxSpellSlots(%08X,%i,%i) used on wrong object type!\n",oID,cls_id,spell_lvl);
		}
		mod->mod_vartable.SetInt(VarName,retVal,0);
	}
	fflush(Patch.m_fFile);
}

char* CNWNXPatch::OnRequest(char *gameObject, char* Request, char* Parameters)
{
	if(!strcmp(Request,"VERIFY"))
	{
		sprintf(Parameters,"%s","1");
	}
	else if(!strcmp(Request,"SWITCH"))
	{
		InitializeModuleSwitches(NWN_AppManager->app_server->srv_internal->GetModule());
	}
	else if(!strncmp(Request,"FUNCS!",6))
	{
		char *delimiter = strchr(Request,'!');
		while(delimiter)
		{
			if(delimiter-Request == 5)
			{
				CGenericObject *obj = (CGenericObject*)gameObject;
				if(obj && obj->obj_type == OBJECT_TYPE_MODULE)
				{
					CNWSModule *mod = NWN_AppManager->app_server->srv_internal->GetModule();
					NWNXPatch_Funcs(mod,atoi(delimiter+1),Parameters);
				}
				break;
			}
			delimiter=strchr(delimiter+1,'!');
		}
	}
	return NULL;
}