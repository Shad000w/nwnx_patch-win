#ifndef __CNWDOMAIN_H__
#define __CNWDOMAIN_H__

#include "CExoString.h"

struct CNWDomain_s {

public:

	unsigned __int32 Name;
	unsigned __int32 Description;
	unsigned __int32 field_08;
	unsigned __int32 field_0C;
	unsigned __int32 field_10;
	unsigned __int32 field_14;
	unsigned __int32 SpellLevel[9];
	unsigned __int32 field_3C;//???
	unsigned __int32 field_40;
	unsigned __int32 field_44;//1
	unsigned __int32 field_48;//1
};
#endif