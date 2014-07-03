#include "stdafx.h"
#include "types.h"
#include "nwn_internals.h"

void (__thiscall *CNWTile__GetLocation)(CNWTile* pTHIS, int *, int *) = (void (__thiscall*)(CNWTile* pTHIS, int *, int *))0x00523150;

void CNWTile::GetLocation(int *a2, int *a3) {
	CNWTile__GetLocation(this, a2, a3);
}

void (__thiscall *CNWTile__SetAnimLoop)(CNWTile* pTHIS, unsigned char *, unsigned char *, unsigned char *) = (void (__thiscall*)(CNWTile* pTHIS, unsigned char *, unsigned char *, unsigned char *))0x005234F0;

void CNWTile::SetAnimLoop(unsigned char *a1, unsigned char *a2, unsigned char *a3)
{
CNWTile__SetAnimLoop(this,a1,a2,a3);
}

void (__thiscall *CNWTile__GetAnimLoop)(CNWTile* pTHIS, unsigned char *, unsigned char *, unsigned char *) = (void (__thiscall*)(CNWTile* pTHIS, unsigned char *, unsigned char *, unsigned char *))0x00523480;

void CNWTile::GetAnimLoop(unsigned char *a1, unsigned char *a2, unsigned char *a3)
{
CNWTile__GetAnimLoop(this,a1,a2,a3);
}

void (__thiscall *CNWTile__SetReplaceTexture)(CNWTile* pTHIS, unsigned char) = (void (__thiscall*)(CNWTile* pTHIS, unsigned char))0x005234E0;

void CNWTile::SetReplaceTexture(unsigned char a1)
{
CNWTile__SetReplaceTexture(this,a1);
}
