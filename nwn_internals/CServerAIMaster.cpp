#include "types.h"
#include "nwn_internals.h"

int (__thiscall *CServerAIMaster__AddEventAbsoluteTime)(CServerAIMaster *pThis, unsigned int a2, unsigned int a3, int a4, int a5, int Event, void *a7) = (int(__thiscall*)(CServerAIMaster *, unsigned int, unsigned int, int, int, int, void *))0x4675A0;
int (__thiscall *CServerAIMaster__AddEventDeltaTime)(CServerAIMaster *pThis, int Seconds, unsigned int Day, int Caller_ID, int Object_ID, int Event, void *a7) = (int(__thiscall*)(CServerAIMaster *, int, unsigned int, int, int, int, void *))0x4674A0;

int CServerAIMaster_s::AddEventDeltaTime(int Seconds, unsigned int Day, int Caller_ID, int Object_ID, int Event, void *a7) {
	return CServerAIMaster__AddEventDeltaTime(this, Seconds, Day, Caller_ID, Object_ID, Event, a7);
}

int CServerAIMaster_s::AddEventAbsoluteTime(unsigned int a2, unsigned int a3, int a4, int a5, int Event, void *a7) {
	return CServerAIMaster__AddEventAbsoluteTime(this, a2, a3, a4, a5, Event, a7);
}