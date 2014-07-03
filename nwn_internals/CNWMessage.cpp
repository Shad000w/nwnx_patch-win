#include "stdafx.h"
#include "types.h"
#include "nwn_internals.h"

int (__thiscall *CNWMessage__ReadBOOL)(CNWMessage *pTHIS) = (int(__thiscall*)(CNWMessage *pTHIS))0x005078C0;
int (__thiscall *CNWMessage__ReadCResRef)(CNWMessage *pTHIS, CResRef *a2, signed int a3) = (int (__thiscall*)(CNWMessage *pTHIS, CResRef *a2, signed int a3))0x00507BC0;
int (__thiscall *CNWMessage__MessageReadOverflow)(CNWMessage *pTHIS, int a2) = (int (__thiscall*)(CNWMessage *pTHIS, int a2))0x00507DD0;

void (__thiscall *CNWMessage__CreateWriteMessage)(CNWMessage *pTHIS, unsigned long l, unsigned long l2, int i) = (void (__thiscall*)(CNWMessage *pTHIS, unsigned long l, unsigned long l2, int i))0x507E30;
int  (__thiscall *CNWMessage__GetWriteMessage)(CNWMessage *pTHIS, unsigned char **c, unsigned long *l) = (int (__thiscall*)(CNWMessage *pTHIS, unsigned char **c, unsigned long *l))0x508B80;
void (__thiscall *CNWMessage__WriteCExoString)(CNWMessage *pTHIS, CExoString s, int i) = (void(__thiscall*)(CNWMessage *pTHIS, CExoString s, int i))0x508900;
void (__thiscall *CNWMessage__WriteINT)(CNWMessage *pTHIS, int i, int i2) = (void(__thiscall*)(CNWMessage *pTHIS, int i, int i2))0x5084F0;


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


void CNWMessage::WriteCExoString(CExoString s, int i)
{	
	return CNWMessage__WriteCExoString(this,s,i);
}

void CNWMessage::WriteINT(int i, int i2)
{
	return CNWMessage__WriteINT(this,i,i2);
}