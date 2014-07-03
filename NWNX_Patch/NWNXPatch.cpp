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
volatile uint32_t Hook_ret;

void Hook_DevastatingCriticalRanged()
{
	__asm leave
	__asm mov DWORD PTR target, edi
	__asm mov DWORD PTR self, ebp
	if(self != NULL && target != NULL && (*NWN_VirtualMachine)->Runscript(&script_devast,self->obj.obj_generic.obj_id,1))
	{
		if(target->obj.GetDead())
		{
			__asm lea ebp, [esi+78h]
			__asm mov edi, NULL
			__asm mov eax, 0x54E0B9
			__asm jmp eax
		}
		else
		{
			__asm mov eax, 0x54E0DA
			__asm jmp eax
		}
	}
	else
	{
		__asm mov eax, 0x54E0E8
		__asm jmp eax
	}
}

void Hook_DevastatingCriticalMelee()
{
	__asm leave
	__asm mov DWORD PTR target, ebx
	__asm mov DWORD PTR self, edi

	if(self != NULL && target != NULL && (*NWN_VirtualMachine)->Runscript(&script_devast,self->obj.obj_generic.obj_id,1))
	{
		if(target->obj.GetDead())
		{
			__asm mov eax, 0x54D6A7
			__asm jmp eax
		}
		else
		{
			__asm mov eax, 0x54D6BC
			__asm jmp eax
		}
	}
	else
	{
		__asm mov eax, 0x54D740
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
		__asm jmp eax
	}
	else
	{
		__asm mov eax, 0x4771B6
		__asm jmp eax
	}
}

void Hook_AssassinDeathAttack()
{
	__asm leave
	__asm mov DWORD PTR self, esi
	__asm mov DWORD PTR target, edi
	Hook_ret = 0x54CD29;
	if(self != NULL && target != NULL && !target->cre_combat_state && self->cre_stats->HasFeat(455))
	{
		target->cre_combat_state = 1;//disables multiple death attack onhits in first flurry
		self->SetEffectSpellId(788);//will set a spell ID for any effect created in the executed script
		Patch.helper = 33;
		if(!(*NWN_VirtualMachine)->Runscript(&script_dthattk,self->obj.obj_generic.obj_id,1))
		{
			//Hook_ret = 0x745840;//doesnt work anyway
		}
		Patch.helper = 0;
	}
	__asm mov eax, Hook_ret
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
		self->cre_last_spell_item = target->obj.obj_portrait_id;
		(*NWN_VirtualMachine)->Runscript(&script_healkit,self->obj.obj_generic.obj_id,1);
	}
	__asm mov eax, 0x4CAB98
	__asm jmp eax
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

void CNWNXPatch::DevastatingCritical()
{
	unsigned char *pPatch = (unsigned char*)0x54D5D0;
	DWORD DefaultPrivs;
	VirtualProtect(pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);

	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_DevastatingCriticalMelee - (uint32_t)(pPatch + 5);

	VirtualProtect((DWORD*)pPatch, 1, DefaultPrivs, NULL);

	pPatch = (unsigned char*) 0x54DFDD;
	VirtualProtect(pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);

	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_DevastatingCriticalRanged - (uint32_t)(pPatch + 5);

	VirtualProtect(pPatch, 1, DefaultPrivs, NULL);
	 
	fprintf(m_fFile, "o Sofcoding the Devastating Critical ability.\n");
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

	fprintf(m_fFile, "o Sofcoding the Assassin's Death Attack OnHit ability.\n");
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

void CNWNXPatch::HealKit()
{
	char *pPatch = (char *) 0x4CA74F;
	DWORD DefaultPrivs;
	VirtualProtect((DWORD*)pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);

	memset((PVOID)pPatch, '\x90', 8);
	pPatch[0] = 0xE9;
	*((uint32_t *)(pPatch + 1)) = (uint32_t)Hook_HealersKit - (uint32_t)(pPatch + 5);

	VirtualProtect((DWORD*)pPatch, 1, DefaultPrivs, NULL);

	fprintf(m_fFile, "o Softcoding healer's kit.\n");
	fflush(m_fFile);
}

void CNWNXPatch::RemoveItemChargesCap()
{
	DWORD DefaultPrivs;
	unsigned char *pPatch = (unsigned char*)0x58E36B;

	VirtualProtect(pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	
	pPatch[0]=0x99;//trying to set FF resulted in weird behavior

	VirtualProtect(pPatch, 1, DefaultPrivs, NULL);

	pPatch = (unsigned char*)0x58E36F;

	VirtualProtect(pPatch, 1, PAGE_EXECUTE_READWRITE, &DefaultPrivs);
	
	pPatch[0]=0x99;

	VirtualProtect(pPatch, 1, DefaultPrivs, NULL);

	fprintf(m_fFile, "o Disabling limitation in SetItemCharges function.\n");
	fflush(m_fFile);
}

BOOL CNWNXPatch::OnRelease( )
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

	fprintf(m_fFile, "Community Patch Patch plugin by Shadooow v 1.6 (Server Edition)\n\n");
	fflush(m_fFile);

	helper = 0;
	hand = 0;

	//Set our nwnx memory funcs
	nwnx_malloc = (void *(__cdecl *)(size_t))0x0040D550;
	//nwns free routine
	nwnx_free = (void (__cdecl *)(void *))0x0040D560;

	RemoveCopyItemAndModifyColorCap();
	RemoveItemChargesCap();
	AssassinDeathAttack();
	SneakAttackCalculation();
	DevastatingCritical();
	HealKit();
	Hook();

	return true;
}
unsigned long CNWNXPatch::OnRequestObject (char *gameObject, char* Request){

	return OBJECT_INVALID;
}

char* CNWNXPatch::OnRequest(char *gameObject, char* Request, char* Parameters)
{
	return NULL;
}