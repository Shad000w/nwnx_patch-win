#include "types.h"
#include "nwn_internals.h"

//CResRef* (__thiscall *CResRef__CResRef)(CResRef *pThis, CExoString const &) = (CResRef* (__thiscall*)(CResRef *pThis, CExoString const &))0x00415AD0;
CResRef* (__thiscall *CResRef__CResRef)(CResRef *pThis, char *) = (CResRef* (__thiscall*)(CResRef *pThis, char *))0x415B50;

CResRef *CResRef::CResRef(char *Ref) {
	return CResRef__CResRef(this, Ref);
}
/*
CResRef *CResRef::CResRef(char *Ref) {
	return CResRef__CResRef(this, Ref);
}*/