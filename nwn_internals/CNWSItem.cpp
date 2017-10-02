#include "types.h"
#include "nwn_internals.h"

CNWSItem*		(__thiscall *CNWSItem__CNWSItem)(CNWSItem *pThis, unsigned long) = (CNWSItem*(__thiscall*)(CNWSItem *pThis, unsigned long))0x004FAA90;

void 			(__thiscall *CNWSItem__AddToArea)(CNWSItem *pThis, CNWSArea *area, float x, float y, float z, int a5) = (void(__thiscall*)(CNWSItem *pThis, CNWSArea *area, float x, float y, float z, int a5))0x004FB6F0;
int 			(__thiscall *CNWSItem__ComputeArmorClass)(CNWSItem *pThis) = (int (__thiscall*)(CNWSItem *pThis))0x004FE870;
unsigned short	(__thiscall *CNWSItem__GetDamageFlags)(CNWSItem *pThis) = (unsigned short(__thiscall*)(CNWSItem *pThis))0x00501660;
unsigned char 	(__thiscall *CNWSItem__GetMinEquipLevel)(CNWSItem *pThis) = (unsigned char(__thiscall*)(CNWSItem *pThis))0x005017A0;
int 			(__thiscall *CNWSItem__GetPropertyByType)(CNWSItem *pThis, CNWItemProperty **iprp, uint16_t ipType, uint16_t ipSubType) = (int(__thiscall*)(CNWSItem *pThis, CNWItemProperty **iprp, uint16_t ipType, uint16_t ipSubType))0x004FE670;
int 			(__thiscall *CNWSItem__GetPropertyByTypeExists)(CNWSItem* pThis, unsigned short, unsigned short) = (int(__thiscall*)(CNWSItem* pThis, unsigned short, unsigned short))0x004FE370;
int 			(__thiscall *CNWSItem__LoadFromTemplate)(CNWSItem *pThis, CResRef CRes, CExoString *Tag) = (int(__thiscall*)(CNWSItem *pThis, CResRef CRes, CExoString *Tag))0x004FBAE0;
int				(__thiscall *CNWSItem__LoadItem)(CNWSItem *pThis, CResGFF *ResGFF, void *CResStruct, int a3) = (int(__thiscall*)(CNWSItem *pThis, CResGFF *ResGFF, void *CResStruct, int a3))0x004FD0D0;
int 			(__thiscall *CNWSItem__SaveItem)(CNWSItem *pThis, CResGFF *, void *ResStruct, int) = (int(__thiscall*)(CNWSItem *pThis, CResGFF *, void *ResStruct, int))0x004FD300;
void 			(__thiscall *CNWSItem__SetDisplayName)(CNWSItem *pThis, CExoString Name) = (void(__thiscall*)(CNWSItem *pThis, CExoString Name))0x00596AB0;
int 			(__thiscall *CNWSItem__SetPossessor)(CNWSItem *pThis, unsigned int a2_Possessor_id, int a3_Signalevent, int a4_bFeedback, int i) = (int (__thiscall*)(CNWSItem *pThis, unsigned int a2_Possessor_id, int a3_Signalevent, int a4_bFeedback, int i))0x004FAF10;
int 			(__thiscall *CNWSItem__CompareItem)(CNWSItem *pTHIS, CNWSItem * itm) = (int(__thiscall*)(CNWSItem *, CNWSItem *))0x004FE9B0;
void			(__thiscall *CNWSItem__UpdateUsedActiveProperties)(CNWSItem *pThis, int unknown) = (void (__thiscall*)(CNWSItem *pThis, int unknown))0x4FDEE0;
void			(__thiscall *CNWSItem__RestoreUsedActiveProperties)(CNWSItem *pThis, int unknown) = (void (__thiscall*)(CNWSItem *pThis, int unknown))0x4FE220;
void			(__thiscall *CNWSItem__AIUpdate)(CNWSItem *pThis) = (void (__thiscall*)(CNWSItem *pThis))0x4FB7C0;

void CNWSItem_s::AIUpdate() 
{
	CNWSItem__AIUpdate(this);
}

void CNWSItem_s::UpdateUsedActiveProperties(int unknown) 
{
	CNWSItem__UpdateUsedActiveProperties(this, unknown);
}

void CNWSItem_s::RestoreUsedActiveProperties(int unknown) 
{
	CNWSItem__RestoreUsedActiveProperties(this, unknown);
}

CNWSItem_s::CNWSItem_s(nwn_objid_t oID) {
	CNWSItem__CNWSItem(this, oID);
}
	
int CNWSItem_s::CompareItem( CNWSItem * itm ){

	return CNWSItem__CompareItem( this, itm );
}

int CNWSItem_s::ComputeArmorClass() {
	return CNWSItem__ComputeArmorClass(this);
}

int CNWSItem_s::SetPossessor(unsigned int a2_Possessor_id, int a3_Signalevent, int a4_bFeedback, int i) {
	return CNWSItem__SetPossessor(this, a2_Possessor_id, a3_Signalevent, a4_bFeedback, i);
}

unsigned short CNWSItem_s::GetDamageFlags() {
	return CNWSItem__GetDamageFlags(this);
}

int CNWSItem_s::GetPropertyByType(CNWItemProperty **iprp, uint16_t ipType, uint16_t ipSubType) {
	return CNWSItem__GetPropertyByType(this, iprp, ipType, ipSubType);
}

int CNWSItem_s::SaveItem(CResGFF *ResGFF, void *ResStruct, int a3) {
	return CNWSItem__SaveItem(this, ResGFF, ResStruct, a3);
}

CNWSItem *CNWSItem_s::ctor(unsigned int a1) {
	return CNWSItem__CNWSItem(this, a1);
}

int CNWSItem_s::LoadItem(CResGFF *ResGFF, void *CResStruct, int a3) {
	return CNWSItem__LoadItem(this, ResGFF, CResStruct, a3);
}

void CNWSItem_s::AddToArea(CNWSArea *Area, float x, float y, float z, int a5) {
	CNWSItem__AddToArea(this, Area, x,y,z, a5);
}

int CNWSItem_s::GetPropertyByTypeExists(unsigned short a1, unsigned short a2) {
	return CNWSItem__GetPropertyByTypeExists(this, a1, a2);
}

int CNWSItem_s::LoadFromTemplate(CResRef CRes, CExoString *Tag) {
	return CNWSItem__LoadFromTemplate(this, CRes, Tag);
}

void CNWSItem_s::SetDisplayName(CExoString Name) {
	CNWSItem__SetDisplayName(this, Name);
}

CExoString CNWSItem_s::GetName() {
	CExoString sRet = "";
	CExoLinkedList *NameList = it_LocNames;
	if (NameList) {
		CExoLocStringNode *NameNode = (CExoLocStringNode*)NameList->ListHeader->FirstElement->Data;
		sRet = NameNode->Text;
	}
	return sRet;
}

CExoString *CNWSItem_s::GetDescription() {
	CExoString *sRet = NULL;
	CExoLinkedList *DescList = this->it_DescIdentified;
	if (DescList) {
		if (DescList->ListHeader) {
			if (DescList->Count > 0) {
				CExoLocStringNode *DescNode = (CExoLocStringNode*)DescList->ListHeader->FirstElement->Data;
				sRet = &DescNode->Text;
			}
		}
	}
	return sRet;
}

unsigned char CNWSItem_s::GetMinEquipLevel() {
	return CNWSItem__GetMinEquipLevel(this);
}