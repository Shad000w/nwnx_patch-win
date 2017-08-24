#ifndef _NX_NWN_STRUCT_CWORLDTIMER_
#define _NX_NWN_STRUCT_CWORLDTIMER_

struct CWorldTimer_s {
    void               *unknown;
    
	void		GetWorldTime(unsigned long *a2, unsigned long *a3);
	void		SetWorldTime(unsigned long a2, unsigned long a3, int a4);
	uint32_t	SubtractWorldTimes(unsigned long a2, unsigned long a3, unsigned long a4, unsigned long a5, unsigned long *a6, unsigned long *a7);
	int			GetCalendarDayFromSeconds(float seconds);
	unsigned long	GetWorldTimeSecond();
	unsigned long	GetWorldTimeHour();
};

#endif