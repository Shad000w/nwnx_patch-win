#include "types.h"
#include "nwn_internals.h"

void 	(__thiscall *CNWSStore__AddToArea)(CNWSStore *pThis, CNWSArea *Area, Vector Position, int a3) = (void(__thiscall*)(CNWSStore *, CNWSArea *, Vector, int))0x465640;
void	(__thiscall *CNWSStore__CNWSStore)(CNWSStore *pThis, nwn_objid_t oID) = (void(__thiscall*)(CNWSStore *, nwn_objid_t))0x464490;
int 	(__thiscall *CNWSStore__LoadStore)(CNWSStore *pThis, CResGFF *pResGFF, CResStruct *pResStruct, CExoString *Tag) = (int(__thiscall*)(CNWSStore *pThis, CResGFF *, CResStruct *, CExoString *))0x464940;
void	(__thiscall *CNWSStore__SetScriptName)(CNWSStore *pThis, int iScript, CExoString ScriptName) = (void (__thiscall*)(CNWSStore *, int, CExoString))0x466460;
int		(__thiscall *CNWSStore__SaveStore)(CNWSStore *pThis, CResGFF *, void *ResStruct) = (int (__thiscall*)(CNWSStore *, CResGFF *, void *))0x4652B0;

int		(__thiscall *CNWSStore__CalculateItemBuyPrice)(CNWSStore *pThis, CNWSItem *item, unsigned long unknown) = (int (__thiscall*)(CNWSStore *, CNWSItem *, unsigned long))0x4657E0;
int		(__thiscall *CNWSStore__CalculateItemSellPrice)(CNWSStore *pThis, CNWSItem *item, unsigned long unknown) = (int (__thiscall*)(CNWSStore *, CNWSItem *, unsigned long))0x4658C0;
void	(__thiscall *CNWSStore__RemoveItem)(CNWSStore *pThis, CNWSItem *item) = (void (__thiscall*)(CNWSStore *, CNWSItem *))0x465960;
int		(__thiscall *CNWSStore__AcquireItem)(CNWSStore *pThis, CNWSItem *item, int a1, unsigned char a2, unsigned char a3) = (int (__thiscall*)(CNWSStore *, CNWSItem *, int, unsigned char, unsigned char))0x4659B0;
int		(__thiscall *CNWSStore__SellItem)(CNWSStore *pThis, CNWSItem *item, CNWSCreature *buyer, unsigned char a1, unsigned char a2) = (int (__thiscall*)(CNWSStore *, CNWSItem *, CNWSCreature *, unsigned char, unsigned char))0x465B30;
int		(__thiscall *CNWSStore__AddItemToInventory)(CNWSStore *pThis, CNWSItem * *item, unsigned char a1, unsigned char a2, unsigned char a3) = (int (__thiscall*)(CNWSStore *, CNWSItem * *, unsigned char, unsigned char, unsigned char))0x465C90;
int		(__thiscall *CNWSStore__RemoveItemFromInventory)(CNWSStore *pThis, CNWSItem *item, unsigned char a1) = (int (__thiscall*)(CNWSStore *, CNWSItem *, unsigned char))0x465F10;
int		(__thiscall *CNWSStore__GetIsRestrictedBuyItem)(CNWSStore *pThis, int a1) = (int (__thiscall*)(CNWSStore *, int))0x465FA0;
void	(__thiscall *CNWSStore__AddCustomer)(CNWSStore *pThis, CNWSPlayer *player, char a1, char a2) = (void (__thiscall*)(CNWSStore *, CNWSPlayer *, char, char))0x466010;
void	(__thiscall *CNWSStore__RemoveCustomer)(CNWSStore *pThis, CNWSPlayer *player) = (void (__thiscall*)(CNWSStore *, CNWSPlayer *))0x4660F0;
short	(__thiscall *CNWSStore__GetCustomerSellRate)(CNWSStore *pThis, unsigned long customer_id) = (short (__thiscall*)(CNWSStore *, unsigned long))0x466180;
unsigned char(__thiscall *CNWSStore__GetCustomerBuyRate)(CNWSStore *pThis, unsigned long customer_id, int a1) = (unsigned char (__thiscall*)(CNWSStore *, unsigned long, int))0x4661E0;
int		(__thiscall *CNWSStore__GetItemInInventory)(CNWSStore *pThis, unsigned long item_id) = (int (__thiscall*)(CNWSStore *, unsigned long))0x466250;
int		(__thiscall *CNWSStore__GetItemInInventoryResRef)(CNWSStore *pThis, CExoString *resref) = (int (__thiscall*)(CNWSStore *, CExoString *))0x4662A0;

CNWSStore_s::CNWSStore_s(nwn_objid_t oID) {
	CNWSStore__CNWSStore(this, oID);	
}

void CNWSStore::SetScriptName(int iScript, CExoString ScriptName) {
	CNWSStore__SetScriptName(this, iScript, ScriptName);
}

int CNWSStore::SaveStore(CResGFF *ResGFF, void *ResStruct) {
	return CNWSStore__SaveStore(this, ResGFF, ResStruct);
}

int CNWSStore_s::LoadStore(CResGFF *pResGFF, CResStruct *pResStruct, CExoString *Tag) {
	return CNWSStore__LoadStore(this, pResGFF, pResStruct, Tag);
}

void CNWSStore_s::AddToArea(CNWSArea *Area, Vector Position, int a3) {
	CNWSStore__AddToArea(this, Area, Position, a3);
}

int CNWSStore_s::CalculateItemBuyPrice(CNWSItem *item, unsigned long unknown) {
	return CNWSStore__CalculateItemBuyPrice(this,item,unknown);
}

int CNWSStore_s::CalculateItemSellPrice(CNWSItem *item, unsigned long unknown) {
	return CNWSStore__CalculateItemSellPrice(this,item,unknown);
}

void CNWSStore_s::RemoveItem(CNWSItem *item) {
	CNWSStore__RemoveItem(this, item);
}

int CNWSStore_s::AcquireItem(CNWSItem *item, int a1, unsigned char a2, unsigned char a3) {
	return CNWSStore__AcquireItem(this,item,a1,a2,a3);
}

int CNWSStore_s::SellItem(CNWSItem *item, CNWSCreature *buyer, unsigned char a1, unsigned char a2) {
	return CNWSStore__SellItem(this,item,buyer,a1,a2);
}

int CNWSStore_s::AddItemToInventory(CNWSItem * *item, unsigned char a1, unsigned char a2, unsigned char a3) {
	return CNWSStore__AddItemToInventory(this,item,a1,a2,a3);
}

int CNWSStore_s::RemoveItemFromInventory(CNWSItem *item, unsigned char a1) {
	return CNWSStore__RemoveItemFromInventory(this,item,a1);
}

int CNWSStore_s::GetIsRestrictedBuyItem(int a1) {
	return CNWSStore__GetIsRestrictedBuyItem(this,a1);
}

void CNWSStore_s::AddCustomer(CNWSPlayer *player, char a1, char a2) {
	CNWSStore__AddCustomer(this, player, a1, a2);
}

void CNWSStore_s::RemoveCustomer(CNWSPlayer *player) {
	CNWSStore__RemoveCustomer(this, player);
}

short CNWSStore_s::GetCustomerSellRate(unsigned long customer_id) {
	return CNWSStore__GetCustomerSellRate(this,customer_id);
}

unsigned char CNWSStore_s::GetCustomerBuyRate(unsigned long customer_id, int a1) {
	return CNWSStore__GetCustomerBuyRate(this,customer_id,a1);
}

int CNWSStore_s::GetItemInInventory(unsigned long item_id) {
	return CNWSStore__GetItemInInventory(this,item_id);
}

int CNWSStore_s::GetItemInInventory(CExoString *resref) {
	return CNWSStore__GetItemInInventoryResRef(this,resref);
}