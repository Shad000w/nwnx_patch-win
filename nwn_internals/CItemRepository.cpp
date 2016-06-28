#include "stdafx.h"
#include "types.h"
#include "nwn_internals.h"

uint32_t (__thiscall *CItemRepository__FindItemWithTag)(CItemRepository *, CExoString *) = (uint32_t (__thiscall*)(CItemRepository *, CExoString *))0x4FFA40;
int (__thiscall *CItemRepository__FindPosition)(CItemRepository *, CNWSItem *, unsigned char &, unsigned char &, int) = (int (__thiscall*)(CItemRepository *, CNWSItem *, unsigned char &, unsigned char &, int))0x4FFB50;

uint32_t CItemRepository_s::FindItemWithTag(CExoString *sTag) {
	return CItemRepository__FindItemWithTag(this, sTag);
}

int CItemRepository::FindPosition(CNWSItem *item, unsigned char &a1, unsigned char &a2, int a3) {
	return CItemRepository__FindPosition(this, item,a1,a2,a3);
}