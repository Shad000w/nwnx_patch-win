#ifndef _NX_NWN_STRUCT_CNWSDOOR_
#define _NX_NWN_STRUCT_CNWSDOOR_

struct CNWSDoor_s {
  CNWSObject obj;
  CExoString OnOpen;
  CExoString OnClosed;
  CExoString OnDamaged;
  CExoString OnDeath;
  CExoString OnDisarm;
  CExoString OnHeartbeat;
  CExoString OnLock;
  CExoString OnMeleeAttacked;
  CExoString OnSpellCastAt;
  CExoString OnTrapTriggered;
  CExoString OnUnlock;
  CExoString OnUserDefined;
  CExoString OnClick;
  CExoString OnDialog;
  CExoString OnFailToOpen;
  unsigned __int32 Appearance;
  unsigned __int32 GenericType;
  char door_conv[16];
  unsigned __int32 Bearing;
  unsigned __int32 Faction;
  unsigned __int8 Fort;
  unsigned __int8 byte259;
  unsigned __int8 Will;
  unsigned __int8 OpenLockDC;
  unsigned __int8 CloseLockDC;
  unsigned __int8 SecretDoorDC;
  unsigned __int8 Hardness;
  unsigned __int8 f25F[1];
  unsigned __int32 Locked;
  unsigned __int32 Lockable;
  unsigned __int8 anim_state;
  unsigned __int8 f269;
  unsigned __int8 f26A;
  unsigned __int8 f26B;
  CExoString KeyTag;
  CExoString KeyRequiredFeedbackMessage;
  unsigned __int32 KeyRequired;
  unsigned __int32 dword280;
  unsigned __int32 dword284;
  unsigned __int32 dword288;
  unsigned __int32 TrapCreator;//28C
  unsigned __int32 TrapIsTrapped;//290
  unsigned __int8 TrapDisarmDC;//294
  unsigned __int8 TrapDetectDC;//295
  unsigned __int8 f296;
  unsigned __int8 f297;
  unsigned __int8 AutoRemoveKey;//298
  unsigned __int8 f299;
  unsigned __int8 f29A;
  unsigned __int8 f29B;
  unsigned __int32 TrapFlagged;//29C
  unsigned __int8 TrapType;//2A0
  unsigned __int8 f2A1[3];
  unsigned __int32 TrapDisarmable;//2A4
  unsigned __int32 TrapDetectable;//2A8
  unsigned __int32 TrapOneShot;//2AC
  unsigned __int32 TrapRecoverable;//2b0
  unsigned __int32 TrapActive;//2b4
  unsigned __int32 TrapFaction;//2b8
  unsigned __int32 dword2BC;
  unsigned __int32 dword2C0;
  unsigned __int32 dword2C4;
  unsigned __int32 dword2C8;
  unsigned __int32 dword2CC;
  unsigned __int32 dword2D0;
  unsigned __int32 dword2D4;
  unsigned __int32 dword2D8;
  unsigned __int32 dword2DC;
  unsigned __int32 SurfaceMesh;
  unsigned __int32 dword2E4;
  unsigned __int32 dword2E8;
  unsigned __int32 dword2EC;
  unsigned __int32 dword2F0;
  unsigned __int32 dword2F4;
  unsigned __int32 dword2F8;
  unsigned __int8 LinkedToFlags;
  unsigned __int8 f2FD[3];
  CExoString LinkedToTag;
  unsigned __int32 LinkedToObject;
  unsigned __int8 f30C;
  unsigned __int8 f30D;
  unsigned __int8 f30E;
  unsigned __int8 f30F;
  unsigned __int8 f310;
  unsigned __int8 f311;
  unsigned __int8 f312;
  unsigned __int8 f313;
  unsigned __int8 f314;
  unsigned __int8 f315;
  unsigned __int8 f316;
  unsigned __int8 f317;
  unsigned __int8 f318;
  unsigned __int8 f319;
  unsigned __int8 f31A;
  unsigned __int8 f31B;
  unsigned __int8 f31C;
  unsigned __int8 f31D;
  unsigned __int8 f31E;
  unsigned __int8 f31F;
  unsigned __int8 f320;
  unsigned __int8 f321;
  unsigned __int8 f322;
  unsigned __int8 f323;
  unsigned __int8 f324;
  unsigned __int8 f325;
  unsigned __int8 f326;
  unsigned __int8 f327;
  unsigned __int8 f328[4];
  unsigned __int32 dword32C;
  unsigned __int16 LoadScreenID;
  	
	void SetScriptName(int iScript, CExoString ScriptName);

};

#endif