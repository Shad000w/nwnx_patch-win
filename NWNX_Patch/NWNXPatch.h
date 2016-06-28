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

#if !defined(NWNXPatch_H_)
#define NWNXPatch_H_
#pragma once
//#include "../NWNXdll/IniFile.h"
#include "../NWNXdll/NWNXBase.h"
#include "nwn_internals.h"
#include "types.h"

#define OBJECT_INVALID 0x7F000000

class CNWNXPatch : public CNWNXBase
{
public:
	CNWNXPatch();
	~CNWNXPatch();

	BOOL OnCreate(const char* LogDir);
	char* OnRequest(char *gameObject, char* Request, char* Parameters);
	unsigned long OnRequestObject (char *gameObject, char* Request);
	BOOL OnRelease();
	void RemoveCopyItemAndModifyColorCap();
	void QuiveringPalm();
	void AssassinDeathAttack();
	void SneakAttackCalculation();
	void DevastatingCritical();
	void HealKit();
	void RemoveItemChargesCap();
	void RemoveChatListenRestrictions();
	void DeathSneakAttackImmunity();
	void InitializeModuleSwitches(CNWSModule *module);
	void CombatMode();
	void SpontaneousSpell();
	void ExamineCRNPCOnly();
	void MindImmunity();
	void Speed();
	void SpellSlotsCrash();
	void AutoMap();
	void PatchSpellCasting();
	void NewCharacterValidation();

	//CIniFile iniFile = new CIniFile();
	CExoString module_script_leave;
	bool NoTumbleAC;
	bool NoCriticalImmunity;
	bool NoMonkAbilities;
	bool TrapImmunity;
	bool PMCasterLevel;
	bool CurseIgnoreAbilityDecreaseImmunity;
	bool PrestigeClassAffectSpontaneousCasters;
	unsigned char NumTilesExplored;
	unsigned int helper;
	unsigned int hand;
	int examineCRonPlayers;
	char *temp;
	int NoServerCharacter;
	//C2DA *spells_2da;
	unsigned int cls_cast_type[255];

	void SendHakList(CNWSMessage *pMessage, int nPlayerID);

	//nwns malloc routine
	void * (__cdecl *nwnx_malloc)(size_t cb);
	//nwns free routine
	void (__cdecl *nwnx_free)(void * cb);


protected:

private:
	DWORD *heapAddress;
};

#endif