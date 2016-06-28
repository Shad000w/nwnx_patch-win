#include "types.h"
#include "nwn_internals.h"

CExoString const & (__thiscall *CTlkTable__GetCustomTokenValue)(CTlkTable *pThis, uint32_t a2) = (CExoString const & (__thiscall*)(CTlkTable *, uint32_t))0x43C370;


CExoString const &CTlkTable_s::GetCustomTokenValue(uint32_t a2) {
	return CTlkTable__GetCustomTokenValue(this, a2);
}