#include "stdafx.h"
#include "types.h"
#include "nwn_internals.h"

uint32_t (__thiscall *CItemRepository__FindItemWithTag)(CItemRepository *, CExoString *) = (uint32_t (__thiscall*)(CItemRepository *, CExoString *))0x4FFA40;
unsigned long (__thiscall *CItemRepository__FindItemWithBaseItemId)(CItemRepository *, unsigned long, int) = (unsigned long (__thiscall*)(CItemRepository *, unsigned long, int))0x4FF980;
int (__thiscall *CItemRepository__FindPosition)(CItemRepository *, CNWSItem *, unsigned char &, unsigned char &, int) = (int (__thiscall*)(CItemRepository *, CNWSItem *, unsigned char &, unsigned char &, int))0x4FFB50;

int (__thiscall *CItemRepository__CheckFit)(CItemRepository *, CNWSItem *, unsigned char, unsigned char) = (int (__thiscall*)(CItemRepository *, CNWSItem *, unsigned char, unsigned char))0x4FF650;

uint32_t CItemRepository_s::FindItemWithTag(CExoString *sTag) {
	return CItemRepository__FindItemWithTag(this, sTag);
}

unsigned long CItemRepository::FindItemWithBaseItemId(unsigned long a1, int a2){
	return CItemRepository__FindItemWithBaseItemId(this, a1, a2);
}

int CItemRepository::FindPosition(CNWSItem *item, unsigned char &a1, unsigned char &a2, int a3) {
	return CItemRepository__FindPosition(this, item,a1,a2,a3);
}

int CItemRepository::CheckFit(CNWSItem *item, unsigned char a1, unsigned char a2) {
	return CItemRepository__CheckFit(this, item,a1,a2);
}