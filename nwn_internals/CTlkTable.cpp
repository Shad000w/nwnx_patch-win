#include "types.h"
#include "nwn_internals.h"

CExoString const & (__thiscall *CTlkTable__GetCustomTokenValue)(CTlkTable *, unsigned long) = (CExoString const & (__thiscall*)(CTlkTable *, unsigned long))0x43C370;


CExoString const &CTlkTable_s::GetCustomTokenValue(unsigned long a2) {
	return CTlkTable__GetCustomTokenValue(this, a2);
}