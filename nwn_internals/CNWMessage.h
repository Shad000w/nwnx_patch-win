#ifndef _NX_NWN_STRUCT_CNWMESSAGE_
#define _NX_NWN_STRUCT_CNWMESSAGE_

struct CNWMessage_s {
	void *vftable;
	void *field_04;
	unsigned __int32 field_08;
	unsigned __int32 field_0C;
	void *field_10;
	unsigned __int32 field_14;
	unsigned __int32 field_18;
	unsigned __int32 field_1C;
	unsigned __int8 field_20;
	unsigned __int8 field_21;
	unsigned __int8 field_22;
	unsigned __int8 field_23;
	unsigned __int32 field_24;
	unsigned __int32 field_28;
	unsigned __int32 field_2C;
	unsigned __int32 field_30;
	unsigned __int32 field_34;
	unsigned __int32 field_38;
	unsigned __int32 field_3C;
	unsigned __int32 field_40;
	unsigned __int8 field_44;
	char field_45;


	CNWMessage_s();
	~CNWMessage_s();

	int 		ReadBOOL();
	int			ReadCResRef(CResRef *ResRef, int a3);
	int 		MessageReadOverflow(int a2);

	void CreateWriteMessage(unsigned long l, unsigned long l2, int i);
	//void WriteCExoString(CExoString s, int i);
	void WriteCExoString(char*name, unsigned long len, int i);
	void WriteINT(int i, int i2);
	int GetWriteMessage(unsigned char **c, unsigned long *l);
	void WriteOBJECTIDServer(unsigned long oID);
};

#endif