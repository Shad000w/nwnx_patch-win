#include "types.h"
#include "nwn_internals.h"

void (__thiscall *CNWSTrigger__SetScriptName)(CNWSTrigger *pThis, int iScript, CExoString ScriptName) = (void (__thiscall*)(CNWSTrigger *, int, CExoString))0x4CB790;

void CNWSTrigger::SetScriptName(int iScript, CExoString ScriptName) {
	CNWSTrigger__SetScriptName(this, iScript, ScriptName);
}