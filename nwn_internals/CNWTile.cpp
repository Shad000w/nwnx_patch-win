#include "types.h"
#include "nwn_internals.h"

void (__thiscall *CNWTile__GetLocation)(CNWTile* pThis, int *, int *) = (void (__thiscall*)(CNWTile *, int *, int *))0x523150;
void (__thiscall *CNWTile__SetAnimLoop)(CNWTile* pThis, unsigned char, unsigned char, unsigned char) = (void (__thiscall*)(CNWTile *, unsigned char, unsigned char, unsigned char))0x5234F0;
void (__thiscall *CNWTile__GetAnimLoop)(CNWTile* pThis, unsigned char *, unsigned char *, unsigned char *) = (void (__thiscall*)(CNWTile *, unsigned char *, unsigned char *, unsigned char *))0x523480;
void (__thiscall *CNWTile__SetReplaceTexture)(CNWTile* pThis, unsigned char) = (void (__thiscall*)(CNWTile *, unsigned char))0x5234E0;

void CNWTile::GetLocation(int *a2, int *a3) {
	CNWTile__GetLocation(this, a2, a3);
}

void CNWTile::SetAnimLoop(unsigned char a1, unsigned char a2, unsigned char a3)
{
CNWTile__SetAnimLoop(this,a1,a2,a3);
}

void CNWTile::GetAnimLoop(unsigned char *a1, unsigned char *a2, unsigned char *a3)
{
CNWTile__GetAnimLoop(this,a1,a2,a3);
}

void CNWTile::SetReplaceTexture(unsigned char a1)
{
CNWTile__SetReplaceTexture(this,a1);
}
