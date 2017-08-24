#include "types.h"
#include "nwn_internals.h"

DWORD CNWMessage__WriteCExoString = 0x508900;


__declspec( naked ) void CNWMessage_s::WriteCExoString(char*name, unsigned long len, int i){__asm{ jmp dword ptr [CNWMessage__WriteCExoString] }}


CNWMessage* (__thiscall *CNWMessage__CNWMessage)(CNWMessage *pThis) = (CNWMessage*(__thiscall*)(CNWMessage *pThis))0x507030;
int (__thiscall *CNWMessage__ReadBOOL)(CNWMessage *pThis) = (int(__thiscall*)(CNWMessage *pThis))0x005078C0;
int (__thiscall *CNWMessage__ReadCResRef)(CNWMessage *pThis, CResRef *a2, signed int a3) = (int (__thiscall*)(CNWMessage *pThis, CResRef *a2, signed int a3))0x00507BC0;
int (__thiscall *CNWMessage__MessageReadOverflow)(CNWMessage *pThis, int a2) = (int (__thiscall*)(CNWMessage *pThis, int a2))0x00507DD0;
void (__thiscall *CNWMessage_dtor)(CNWMessage *pThis) = (void(__thiscall*)(CNWMessage *pThis))0x534C30;
void (__thiscall *CNWMessage__CreateWriteMessage)(CNWMessage *pThis, unsigned long l, unsigned long l2, int i) = (void (__thiscall*)(CNWMessage *pThis, unsigned long l, unsigned long l2, int i))0x507E30;
int  (__thiscall *CNWMessage__GetWriteMessage)(CNWMessage *pThis, unsigned char **c, unsigned long *l) = (int (__thiscall*)(CNWMessage *pThis, unsigned char **c, unsigned long *l))0x508B80;
//void (__thiscall *CNWMessage__WriteCExoString)(CNWMessage *pThis, CExoString s, int i) = (void(__thiscall*)(CNWMessage *pThis, CExoString s, int i))0x508900;
void (__thiscall *CNWMessage__WriteINT)(CNWMessage *pThis, int i, int i2) = (void(__thiscall*)(CNWMessage *pThis, int i, int i2))0x5084F0;
void (__thiscall *CNWMessage__WriteOBJECTIDServer)(CNWMessage *pThis, unsigned long) = (void(__thiscall*)(CNWMessage *pThis, unsigned long))0x508CB0;

CNWMessage_s::CNWMessage_s() {
	CNWMessage__CNWMessage(this);
}

CNWMessage_s::~CNWMessage_s() {
	CNWMessage_dtor(this);
}

int CNWMessage_s::ReadCResRef(CResRef *ResRef, int a3) {
	return CNWMessage__ReadCResRef(this, ResRef, a3);
}

int CNWMessage_s::MessageReadOverflow(int a2) {
	if (this->field_30 <= this->field_2C)
		return this->field_38 < this->field_3C;
	return 1;
	//return CNWMessage__MessageReadOverflow(this, a2);
}
	
int CNWMessage_s::ReadBOOL() {
	return CNWMessage__ReadBOOL(this);
}

void CNWMessage::CreateWriteMessage(unsigned long l, unsigned long l2, int i)
{
	return CNWMessage__CreateWriteMessage(this,l,l2,i);
}

int CNWMessage::GetWriteMessage(unsigned char **c, unsigned long *l)
{
	return CNWMessage__GetWriteMessage(this,c,l);
}

/*
void CNWMessage::WriteCExoString(CExoString s, int i)
{	
	return CNWMessage__WriteCExoString(this,s,i);
}*/

void CNWMessage::WriteINT(int i, int i2)
{
	return CNWMessage__WriteINT(this,i,i2);
}

void CNWMessage::WriteOBJECTIDServer(unsigned long oID)
{
	CNWMessage__WriteOBJECTIDServer(this,oID);
}