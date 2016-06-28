#include "CNWSInventory.h"
#include "types.h"
#include "nwn_internals.h"

CNWSItem* (__thiscall *CNWSInventory__GetItemInSlot)(CNWSInventory* pThis, unsigned long nSlot) = (CNWSItem* (__thiscall*)(CNWSInventory*, unsigned long))0x502240;
int (__thiscall *CNWSInventory__GetItemInInventory)(CNWSInventory* pThis, CNWSItem *item) = (int (__thiscall*)(CNWSInventory* inventory, CNWSItem *item))0x5021E0;
unsigned long (__thiscall *CNWSInventory__GetSlotFromItem)(CNWSInventory* pThis, CNWSItem *item) = (unsigned long (__thiscall*)(CNWSInventory* inventory, CNWSItem *item))0x502210;
int (__thiscall *CNWSInventory__RemoveItem)(CNWSInventory* pThis, CNWSItem *item) = (int (__thiscall*)(CNWSInventory* inventory, CNWSItem *item))0x502490;
void (__thiscall *CNWSInventory__PutItemInSlot)(CNWSInventory* pThis, unsigned long nSlot, CNWSItem *item) = (void (__thiscall*)(CNWSInventory* inventory, unsigned long nSlot, CNWSItem *item))0x5024D0;


CNWSInventory_s::CNWSInventory_s() {
	*(uint32_t*)&vftable = 0x006342E0;
	memset(Slot, 0x7F000000, sizeof(Slot));
}

CNWSItem *CNWSInventory::GetItemInSlot(unsigned long nSlot) {
	return CNWSInventory__GetItemInSlot(this, nSlot);
}

int CNWSInventory::GetItemInInventory(CNWSItem *item)
{
	return CNWSInventory__GetItemInInventory(this, item);
}

unsigned long CNWSInventory::GetSlotFromItem(CNWSItem *item)
{
	return CNWSInventory__GetSlotFromItem(this, item);
}

int CNWSInventory::RemoveItem(CNWSItem *item)
{
	return CNWSInventory__RemoveItem(this, item);
}

void CNWSInventory::PutItemInSlot(unsigned long nSlot, CNWSItem *item)
{
	CNWSInventory__PutItemInSlot(this, nSlot, item);
}