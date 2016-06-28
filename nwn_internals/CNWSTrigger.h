#ifndef _CNWSTRIGGER_H_
#define _CNWSTRIGGER_H_

struct CNWSTrigger_s
{
  CNWSObject obj;
  CExoLocString LocalizedName;
  CExoString LinkedTo;
  unsigned __int8 LinkedToFlags;
  unsigned __int8 field_1D1;
  unsigned __int8 field_1D2;
  unsigned __int8 field_1D3;
  unsigned __int8 DescriptionOverride;
  unsigned __int8 field_1D5;
  unsigned __int8 field_1D6;
  unsigned __int8 field_1D7;
  unsigned __int8 field_1D8;
  unsigned __int8 field_1D9;
  unsigned __int8 field_1DA;
  unsigned __int8 field_1DB;
  CExoString OnHeartbeat;
  CExoString OnEnter;
  CExoString OnExit;
  CExoString OnUserDefined;
  CExoString OnTrapTriggered;
  CExoString OnDisarm;
  CExoString OnClick;
  CExoString KeyName;
  __int32 Geometry_len;
  Vector *geometry_vectors;
  unsigned __int32 field_224;
  unsigned __int32 field_228;
  unsigned __int32 VerticesCount;
  unsigned __int32 *Vertices;
  unsigned __int32 obj_id_01;
  unsigned __int32 obj_id_02;
  unsigned __int32 obj_id_03;
  unsigned __int32 *DetectedBy_;
  unsigned __int8 field_244;
  unsigned __int8 field_245;
  unsigned __int8 field_246;
  unsigned __int8 field_247;
  unsigned __int8 field_248;
  unsigned __int8 field_249;
  unsigned __int8 field_24A;
  unsigned __int8 field_24B;
  unsigned __int32 Type1_;
  unsigned __int32 Faction;
  unsigned __int32 TrapIsTrapped;//254
  unsigned __int32 TrapDetectable;//258
  unsigned __int32 TrapDisarmable;//25C
  unsigned __int32 TrapFlagged;//260
  unsigned __int32 AutoRemoveKey;//264
  unsigned __int32 TrapOneShot;//268
  unsigned __int8 TrapType;//26C
  unsigned __int8 field_26D;
  unsigned __int8 field_26E;
  unsigned __int8 field_26F;
  unsigned __int32 TrapDetectDC;//270
  unsigned __int32 TrapDisarmDC;//274
  unsigned __int32 TrapRecoverable;//278
  unsigned __int32 TrapActive;//27C
  unsigned __int8 field_280;
  unsigned __int8 field_281;
  unsigned __int8 field_282;
  unsigned __int8 field_283;
  float HighlightHeight;//284
  unsigned __int32 CreatorId;//288   -trap creator
  unsigned __int8 field_28C;
  unsigned __int8 field_28D;
  unsigned __int8 field_28E;
  unsigned __int8 field_28F;
  unsigned __int8 field_290;
  unsigned __int8 field_291;
  unsigned __int8 field_292;
  unsigned __int8 field_293;
  unsigned __int8 field_294;
  unsigned __int8 field_295;
  unsigned __int8 field_296;
  unsigned __int8 field_297;
  unsigned __int8 field_298;
  unsigned __int8 field_299;
  unsigned __int8 field_29A;
  unsigned __int8 field_29B;
  unsigned __int32 field_29C;
  unsigned __int8 Cursor;
  unsigned __int8 field_2A1;
  unsigned __int8 field_2A2;
  unsigned __int8 field_2A3;
  unsigned __int8 field_2A4;
  unsigned __int8 field_2A5;
  unsigned __int8 field_2A6;
  unsigned __int8 field_2A7;
  unsigned __int8 field_2A8;
  unsigned __int8 field_2A9;
  unsigned __int8 field_2AA;
  unsigned __int8 field_2AB;
  unsigned __int16 LoadScreenID;
  unsigned __int8 field_2AE;
  unsigned __int8 field_2AF;

	void SetScriptName(int iScript, CExoString ScriptName);
};

#endif