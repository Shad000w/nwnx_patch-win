#ifndef _H_CNWSAREAOFEFFECTOBJECT_H_
#define _H_CNWSAREAOFEFFECTOBJECT_H_

struct CNWSAreaOfEffectObject_s {
	CNWSObject obj;
  unsigned __int8 unknown_449;//1c0
  unsigned __int8 unknown_450;//1c1
  unsigned __int8 unknown_451;//1c2
  unsigned __int8 unknown_452;//1c3
  unsigned __int32 AreaEffectId;//1c4
  unsigned __int8 Shape;//1c8
  unsigned __int8 unknown_458;//1c9
  unsigned __int8 unknown_459;//1cA
  unsigned __int8 unknown_460;//1cB
  __int32 SpellID;//1CC
  float Radius;
  float Width;
  unsigned __int32 Length;
  unsigned __int8 unknown_477;
  unsigned __int8 unknown_478;
  unsigned __int8 unknown_479;
  unsigned __int8 unknown_480;
  unsigned __int32 CreatorID;
  unsigned __int32 LinkedToObject;
  unsigned __int32 LastEntered;
  unsigned __int32 LastLeft;
  unsigned __int8 SpellSaveDC;
  unsigned __int8 unknown_498;
  unsigned __int8 unknown_499;
  unsigned __int8 unknown_500;
  unsigned __int8 SpellLevel;
  unsigned __int8 unknown_502;
  unsigned __int8 unknown_503;
  unsigned __int8 unknown_504;
  CExoString OnHeartbeat;
  CExoString OnUserDefined;
  CExoString OnObjEnter;
  CExoString OnObjExit;
  unsigned __int32 LastHrtbtDay;
  unsigned __int32 LastHrtbtTime;
  unsigned __int32 Duration;
  unsigned __int8 DurationType;
  unsigned __int8 unknown_550;
  unsigned __int8 unknown_551;
  unsigned __int8 unknown_552;

	void SetScriptName(int iScript, CExoString ScriptName);
};

#endif