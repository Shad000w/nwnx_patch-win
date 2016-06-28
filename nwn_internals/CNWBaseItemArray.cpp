#include "types.h"
#include "nwn_internals.h"

CNWBaseItem *	(__thiscall *CNWBaseItemArray__GetBaseItem)(CNWBaseItemArray *pThis, int baseItem) = (CNWBaseItem* (__thiscall*)(CNWBaseItemArray *, int))0x512AF0;


CNWBaseItem *CNWBaseItemArray_s::GetBaseItem(int BaseItem) {
	return CNWBaseItemArray__GetBaseItem(this, BaseItem);
}