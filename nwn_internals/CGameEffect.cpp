#include "types.h"
#include "nwn_internals.h"

CGameEffect*	(__thiscall *CGameEffect__CGameEffect)(CGameEffect *, int ) = (CGameEffect *(__thiscall*)(CGameEffect *, int))0x4E7D30;
void			(__thiscall *CGameEffect__dtor)(CGameEffect *) = (void (__thiscall*)(CGameEffect *))0x4E7FD0;
void 			(__thiscall *CGameEffect__CopyEffect)(CGameEffect *, CGameEffect *, int) = (void(__thiscall*)(CGameEffect *, CGameEffect *, int))0x4E8270;
void			(__thiscall *CGameEffect__SetNumIntegers)(CGameEffect *, int) = (void (__thiscall*)(CGameEffect *, int))0x4E8070;
void			(__thiscall *CGameEffect__SetNumIntegersInitializeToNegativeOne)(CGameEffect *, int) = (void (__thiscall*)(CGameEffect *, int))0x4E80D0;
int				(__thiscall *CGameEffect__GetScriptEffectType)(CGameEffect *) = (int (__thiscall *)(CGameEffect *))0x4E8CD0;
int				(__thiscall *CGameEffect__GetInteger)(CGameEffect *, int) = (int (__thiscall*)(CGameEffect *, int))0x4E8130;
int				(__thiscall *CGameEffect__SetCreator)(CGameEffect *, nwn_objid_t) = (int (__thiscall*)(CGameEffect *, nwn_objid_t))0x4E8C00;
CGameEffect*	(__thiscall *CGameEffect__CGameEffect_c)(CGameEffect *, CGameEffect *, int) = (CGameEffect* (__thiscall*)(CGameEffect *, CGameEffect *, int))0x4E7E70;
CGameEffect*	(__thiscall *CGameEffect__SetLinked)(CGameEffect *, CGameEffect *, CGameEffect *) = (CGameEffect*(__thiscall*)(CGameEffect *, CGameEffect *, CGameEffect *))0x4E8450;
int				(__thiscall *CGameEffect__UpdateLinked)(CGameEffect *) = (int(__thiscall*)(CGameEffect *))0x4E8470;
int				(__thiscall *CGameEffect__SetInteger)(CGameEffect *, int, int) = (int(__thiscall *)(CGameEffect *, int, int))0x4E8140;

int CGameEffect_s::UpdateLinked()
{
	return CGameEffect__UpdateLinked( this );
}

CGameEffect_s::CGameEffect_s(int a1)
{
	CGameEffect__CGameEffect(this, a1);
}

CGameEffect_s::CGameEffect_s(CGameEffect *Effect, int bCopy) 
{
	CGameEffect__CGameEffect_c(this, Effect, bCopy);
}

CGameEffect *CGameEffect_s::ctor(int a2)
{
	return CGameEffect__CGameEffect(this, a2);
}

CGameEffect *CGameEffect_s::ctor(CGameEffect *Effect, int bCopy)
{
	return CGameEffect__CGameEffect_c(this, Effect, bCopy);
}

int	CGameEffect_s::GetScriptEffectType() 
{
	return CGameEffect__GetScriptEffectType(this);
}

int CGameEffect_s::SetInteger(int nIndex, int nData)
{
	return CGameEffect__SetInteger(this, nIndex, nData);
}

int CGameEffect_s::GetInteger(int nInt)
{
	return CGameEffect__GetInteger(this, nInt);
}

void CGameEffect_s::dtor()
{
	CGameEffect__dtor(this);
}

void CGameEffect_s::SetNumIntegers(int nInts)
{
	CGameEffect__SetNumIntegers(this, nInts);
}

int CGameEffect_s::SetCreator(nwn_objid_t oidCreator)
{
	return CGameEffect__SetCreator(this, oidCreator);
}

void CGameEffect_s::SetNumIntegersInitializeToNegativeOne(int nInts)
{
CGameEffect__SetNumIntegersInitializeToNegativeOne(this, nInts);
}

void CGameEffect_s::CopyEffect(CGameEffect *Source, int bCopyVars) 
{
	CGameEffect__CopyEffect(this, Source, bCopyVars);
}

CGameEffect* CGameEffect_s::SetLinked(CGameEffect *a2, CGameEffect *a3) 
{
	return CGameEffect__SetLinked(this, a2, a3);
}
