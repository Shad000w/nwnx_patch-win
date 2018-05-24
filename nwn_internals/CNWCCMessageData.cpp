#include "stdafx.h"
#include "types.h"
#include "nwn_internals.h"
#include "CNWCCMessageData.h"

void		(__thiscall *CNWCCMessageData__ctor)(CNWCCMessageData *pThis) = (void(__thiscall*)(CNWCCMessageData *pThis))0x00506630;
void		(__thiscall *CNWCCMessageData__dtor)(CNWCCMessageData *pThis) = (void(__thiscall*)(CNWCCMessageData *pThis))0x00506680;
void 		(__thiscall *CNWCCMessageData__CopyTo)(CNWCCMessageData *pThis, CNWCCMessageData *Dest) = (void(__thiscall*)(CNWCCMessageData *pThis, CNWCCMessageData *Dest))0x00506EC0;
int			(__thiscall *CNWCCMessageData__SetInteger)(CNWCCMessageData *pThis, int nNthInt, int Value) = (int(__thiscall*)(CNWCCMessageData *pThis, int nNthInt, int Value))0x00506720;
void		(__thiscall *CNWCCMessageData__SetObjectID)(CNWCCMessageData *pThis, int Nth, nwn_objid_t oID) = (void(__thiscall*)(CNWCCMessageData *pThis, int Nth, nwn_objid_t oID))0x005067D0;
uint32_t 	(__thiscall *CNWCCMessageData__SetString)(CNWCCMessageData *pThis, uint32_t a2, CExoString ExoString) = (uint32_t (__thiscall*)(CNWCCMessageData *pThis, uint32_t a2, CExoString ExoString))0x00506880;


CNWCCMessageData_s::CNWCCMessageData_s() {
	CNWCCMessageData__ctor(this);
}

CNWCCMessageData_s::~CNWCCMessageData_s() {
	CNWCCMessageData__dtor(this);
}

uint32_t CNWCCMessageData_s::SetString(uint32_t a2, CExoString ExoString) {
	return CNWCCMessageData__SetString(this, a2, ExoString);
}

void CNWCCMessageData_s::SetObjectID(int Nth, nwn_objid_t oID) {
	CNWCCMessageData__SetObjectID(this, Nth, oID);
}

int CNWCCMessageData_s::SetInteger(int Nth, int Value) {
	return CNWCCMessageData__SetInteger(this, Nth, Value);
}

void CNWCCMessageData_s::CopyTo(CNWCCMessageData *Dest) {
	CNWCCMessageData__CopyTo(this, Dest);
}
/*
void CNWCCMessageData_s::AddAttackerCombatMessage(CNWSCreature *Attacker) {
	CNWSCombatAttackData *aData = Attacker->cre_combat_round->GetAttack(Attacker->cre_combat_round->CurrentAttack);
	if (aData->Messages_count == aData->Messages_alloc) {
		int newsize = aData->Messages_alloc ? 2*aData->Messages_alloc : 16;

		//create new message list and copy the old one
		CNWCCMessageData **msgList = new CNWCCMessageData*[newsize];
		int i=0;
		while (i<aData->Messages_count)
			msgList[i] = aData->Messages[i++];

		delete[] aData->Messages;
		aData->Messages = msgList;
	}
	aData->Messages[aData->Messages_count++] = this;
}*/