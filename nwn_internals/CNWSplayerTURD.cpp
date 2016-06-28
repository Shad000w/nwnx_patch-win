#include "types.h"
#include "nwn_internals.h"

void * (__thiscall *CNWSPlayerTURD__scalar_deleting_destructor)(CNWSPlayerTURD_s *pThis, uint32_t Flags) = (void* (__thiscall*)(CNWSPlayerTURD_s *, uint32_t))0x4DBFF0;
	
void *CNWSPlayerTURD_s::ScalarDestructor(uint32_t Flags) {
	return CNWSPlayerTURD__scalar_deleting_destructor(this, Flags);
}