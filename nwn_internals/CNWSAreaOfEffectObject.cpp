#include "types.h"
#include "nwn_internals.h"

void 			(__thiscall *CNWSAreaOfEffectObject__SetScriptName)(CNWSAreaOfEffectObject *pThis, int iScript, CExoString ScriptName) = (void (__thiscall*)(CNWSAreaOfEffectObject *, int, CExoString))0x4F2F20;

void CNWSAreaOfEffectObject_s::SetScriptName(int iScript, CExoString ScriptName) {
	CNWSAreaOfEffectObject__SetScriptName(this, iScript, ScriptName);
}
