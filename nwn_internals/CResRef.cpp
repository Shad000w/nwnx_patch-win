#include "stdafx.h"
#include "types.h"
#include "nwn_internals.h"

//CResRef* (__thiscall *CResRef__CResRef)(CResRef *pTHIS, CExoString const &) = (CResRef* (__thiscall*)(CResRef *pTHIS, CExoString const &))0x00415AD0;
CResRef* (__thiscall *CResRef__CResRef)(CResRef *pTHIS, char *) = (CResRef* (__thiscall*)(CResRef *pTHIS, char *))0x415B50;

CResRef *CResRef::CResRef(char *Ref) {
	return CResRef__CResRef(this, Ref);
}
/*
CResRef *CResRef::CResRef(char *Ref) {
	return CResRef__CResRef(this, Ref);
}*/