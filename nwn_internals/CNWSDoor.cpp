#include "types.h"
#include "nwn_internals.h"

void (__thiscall *CNWSDoor__SetScriptName)(CNWSDoor *pThis, int iScript, CExoString ScriptName) = (void (__thiscall*)(CNWSDoor *, int, CExoString))0x4CC670;


void CNWSDoor::SetScriptName(int iScript, CExoString ScriptName) {
	CNWSDoor__SetScriptName(this, iScript, ScriptName);
}