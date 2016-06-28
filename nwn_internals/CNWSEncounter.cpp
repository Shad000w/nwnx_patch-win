#include "types.h"
#include "nwn_internals.h"

void (__thiscall *CNWSEncounter__SetScriptName)(CNWSEncounter *pThis, int iScript, CExoString ScriptName) = (void (__thiscall*)(CNWSEncounter *, int, CExoString))0x5ADA00;

void CNWSEncounter::SetScriptName(int iScript, CExoString ScriptName) {
	CNWSEncounter__SetScriptName(this, iScript, ScriptName);
}