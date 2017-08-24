#include "types.h"
#include "nwn_internals.h"

void		(__thiscall *CWorldTimer__GetWorldTime)(CWorldTimer *pThis, unsigned long *a2, unsigned long *a3) = (void (__thiscall *)(CWorldTimer *pThis, unsigned long *a2, unsigned long *a3))0x005BA630;
void		(__thiscall *CWorldTimer__SetWorldTime)(CWorldTimer *pThis, unsigned long a2, unsigned long a3, int a4) = (void (__thiscall *)(CWorldTimer *pThis, unsigned long a2, unsigned long a3, int a4))0x005BA590;
unsigned long 	(__thiscall *CWorldTimer__SubtractWorldTimes)(CWorldTimer *pThis, unsigned long a2, unsigned long a3, unsigned long a4, unsigned long a5, unsigned long *a6, unsigned long *a7) = (unsigned long (__thiscall *)(CWorldTimer *pThis, unsigned long a2, unsigned long a3, unsigned long a4, unsigned long a5, unsigned long *a6, unsigned long *a7))0x005BA7B0;
int			(__thiscall *CWorldTimer__GetCalendarDayFromSeconds)(CWorldTimer*pThis, float a2) = (int(__thiscall *)(CWorldTimer*, float))0x005BAAA0;
unsigned long(__thiscall *CWorldTimer__GetWorldTimeSecond)(CWorldTimer*pThis) = (unsigned long(__thiscall *)(CWorldTimer*))0x005BAA40;
unsigned long(__thiscall *CWorldTimer__GetWorldTimeHour)(CWorldTimer*pThis) = (unsigned long(__thiscall *)(CWorldTimer*))0x5BA9C0;

unsigned long CWorldTimer::GetWorldTimeHour(){
	return CWorldTimer__GetWorldTimeHour(this);
}

unsigned long CWorldTimer_s::GetWorldTimeSecond(){
	return CWorldTimer__GetWorldTimeSecond(this);
}

int	CWorldTimer_s::GetCalendarDayFromSeconds(float seconds){
	return CWorldTimer__GetCalendarDayFromSeconds(this, seconds);
}

void CWorldTimer_s::GetWorldTime(unsigned long *a2, unsigned long *a3) {
	 CWorldTimer__GetWorldTime(this, a2, a3);
}

void CWorldTimer_s::SetWorldTime(unsigned long a2, unsigned long a3, int a4) {
	CWorldTimer__SetWorldTime(this, a2, a3, a4);
}

uint32_t CWorldTimer_s::SubtractWorldTimes(unsigned long a2, unsigned long a3, unsigned long a4, unsigned long a5, unsigned long *a6, unsigned long *a7) {
	return CWorldTimer__SubtractWorldTimes(this, a2, a3, a4, a5, a6, a7);
}

