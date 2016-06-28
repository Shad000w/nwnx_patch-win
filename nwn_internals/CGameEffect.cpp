#include "types.h"
#include "nwn_internals.h"

CGameEffect*	(__thiscall *CGameEffect__CGameEffect)(CGameEffect *pThis, int a2) = (CGameEffect *(__thiscall*)(CGameEffect *, int))0x4E7D30;
void			(__thiscall *CGameEffect__dtor)(CGameEffect *pThis) = (void (__thiscall*)(CGameEffect *))0x4E7FD0;
void 			(__thiscall *CGameEffect__CopyEffect)(CGameEffect *pThis, CGameEffect *Source, int bCopyVars) = (void(__thiscall*)(CGameEffect *, CGameEffect *, int))0x4E8270;
int				(__thiscall *CGameEffect__GetScriptEffectType)(CGameEffect *pThis) = (int (__thiscall *)(CGameEffect *))0x4E8CD0;
//int			(__thiscall *CGameEffect__GetInteger)(CGameEffect *pThis, int nInt) = (int (__thiscall*)(CGameEffect *, int))0x4E8130;
int				(__thiscall *CGameEffect__SetCreator)(CGameEffect *pThis, nwn_objid_t oidCreator) = (int (__thiscall*)(CGameEffect *, nwn_objid_t))0x4E8C00;
CGameEffect*	(__thiscall *CGameEffect__CGameEffect_c)(CGameEffect *pThis, CGameEffect *Effect, int bCopy) = (CGameEffect* (__thiscall*)(CGameEffect *, CGameEffect *, int))0x4E7E70;
CGameEffect*	(__thiscall *CGameEffect__SetLinked)(CGameEffect *pThis, CGameEffect *a2, CGameEffect *a3) = (CGameEffect*(__thiscall*)(CGameEffect *, CGameEffect *, CGameEffect *))0x4E8450;
int				(__thiscall *CGameEffect__UpdateLinked)(CGameEffect *pThis) = (int(__thiscall*)(CGameEffect *))0x4E8470;
int				(__thiscall *CGameEffect__SetInteger)( CGameEffect *pThis, int a2, int a3) = (int(__thiscall *)( CGameEffect *, int, int))0x4E8140;

int CGameEffect_s::UpdateLinked(){

	return CGameEffect__UpdateLinked( this );
}

CGameEffect_s::CGameEffect_s(int a1) {
	CGameEffect__CGameEffect(this, a1);
}
CGameEffect_s::CGameEffect_s(CGameEffect *Effect, int bCopy) {
	CGameEffect__CGameEffect_c(this, Effect, bCopy);
}

CGameEffect *CGameEffect_s::ctor(int a2) {
	return CGameEffect__CGameEffect(this, a2);
}

CGameEffect *CGameEffect_s::ctor(CGameEffect *Effect, int bCopy) {
	return CGameEffect__CGameEffect_c(this, Effect, bCopy);
}

int	CGameEffect_s::GetScriptEffectType() {
	return CGameEffect__GetScriptEffectType(this);
}

int CGameEffect_s::SetInteger(int nIndex, int nData){
	return CGameEffect__SetInteger( this, nIndex, nData );
}

int CGameEffect_s::GetInteger(int nInt) {

	if( this->eff_num_integers >= (uint32_t)nInt || nInt < 0 )
		return -1;

	return this->eff_integers[nInt];
}

void CGameEffect_s::dtor() {
	CGameEffect__dtor(this);
}

int CGameEffect_s::SetNumIntegers(int nInts) {
	eff_num_integers = nInts;
	if (eff_integers) {
		delete[] eff_integers;
		eff_integers = NULL;
	}
	eff_integers = new int[nInts];
	for (int i=0; i<nInts; i++) {
		eff_integers[i] = 0;
	}
	return 0;
}

int CGameEffect_s::SetCreator(nwn_objid_t oidCreator) {
	return CGameEffect__SetCreator(this, oidCreator);
}

int CGameEffect_s::SetNumIntegersInitializeToNegativeOne(int nInts) {
	if (eff_num_integers) {
		delete eff_integers;
		eff_integers = NULL;
	}
	eff_integers = new int[nInts];
	memset(eff_integers, -1, nInts * sizeof(int));
	eff_num_integers = nInts;
	
	return -1;
}

void CGameEffect_s::CopyEffect(CGameEffect *Source, int bCopyVars) {
	CGameEffect__CopyEffect(this, Source, bCopyVars);
}

CGameEffect* CGameEffect_s::SetLinked(CGameEffect *a2, CGameEffect *a3) {
	return CGameEffect__SetLinked(this, a2, a3);
}
