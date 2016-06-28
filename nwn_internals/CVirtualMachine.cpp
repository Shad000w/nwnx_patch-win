#include "types.h"
#include "nwn_internals.h"

int (__thiscall *CVirtualMachine__RunScript)(CVirtualMachine *pThis, CExoString *a2, nwn_objid_t, int a4) = (int (__thiscall*)(CVirtualMachine *pThis, CExoString *a2, nwn_objid_t, int a4))0x005BF9D0;
int (__thiscall *CVirtualMachine__StackPushEngineStructure)(CVirtualMachine *pThis, int, void *) = (int (__thiscall*)(CVirtualMachine *pThis, int, void *))0x005C0970;
int (__thiscall *CVirtualMachine__StackPushFloat)(CVirtualMachine *pThis, float f) = (int(__thiscall*)(CVirtualMachine *pThis, float f))0x005C0660;
int (__thiscall *CVirtualMachine__StackPushInteger)(CVirtualMachine *pThis, int i) = (int(__thiscall*)(CVirtualMachine *pThis, int i))0x005C05E0;
int (__thiscall *CVirtualMachine__StackPushObject)(CVirtualMachine *pThis, nwn_objid_t Object) = (int(__thiscall*)(CVirtualMachine *pThis, nwn_objid_t Object))0x005C0A10;
int (__thiscall *CVirtualMachine__StackPopInteger)(CVirtualMachine *pThis, int *) = (int (__thiscall*)(CVirtualMachine *pThis, int *))0x005C0590;
int (__thiscall *CVirtualMachine__StackPopFloat)(CVirtualMachine *pThis, float *) = (int (__thiscall*)(CVirtualMachine *pThis, float *))0x5C0610;
int (__thiscall *CVirtualMachine__StackPopEngineStructure)(CVirtualMachine *pThis, int a2, void **a3) = (int(__thiscall*)(CVirtualMachine *pThis, int a2, void **a3))0x005C08F0;
int (__thiscall *CVirtualMachine__StackPopObject)(CVirtualMachine *pThis, nwn_objid_t *oID) = (int(__thiscall*)(CVirtualMachine *pThis, nwn_objid_t *oID))0x005C09C0;
int (__thiscall *CVirtualMachine__StackPopString)(CVirtualMachine *pThis, CExoString *s) = (int(__thiscall*)(CVirtualMachine *pThis, CExoString *s))0x005C0800;
		
int CVirtualMachine_s::Runscript(CExoString *ScriptName, nwn_objid_t OBJECT_SELF, int a4) {
	return CVirtualMachine__RunScript(this, ScriptName, OBJECT_SELF, a4);
}

int CVirtualMachine_s::StackPushEngineStructure(int a2, void *a3) {
	return CVirtualMachine__StackPushEngineStructure(this, a2, a3);
}

int CVirtualMachine_s::StackPopEngineStructure(int a2, void **a3) {
	return CVirtualMachine__StackPopEngineStructure(this, a2, a3);
}

int CVirtualMachine_s::StackPopInteger(int *iINT) {
	return CVirtualMachine__StackPopInteger(this, iINT);
}

int CVirtualMachine_s::StackPopFloat(float *fFloat) {
	return CVirtualMachine__StackPopFloat(this, fFloat);
}

int CVirtualMachine_s::StackPushInteger(int i) {
	return CVirtualMachine__StackPushInteger(this, i);
}

int CVirtualMachine_s::StackPushFloat(float f) {
	return CVirtualMachine__StackPushFloat(this, f);
}

int CVirtualMachine_s::StackPopString(CExoString *str) {
	return CVirtualMachine__StackPopString(this, str);	
}

int CVirtualMachine_s::StackPushObject(nwn_objid_t Object) {
	return CVirtualMachine__StackPushObject(this, Object);
}

int CVirtualMachine_s::StackPopObject(nwn_objid_t *oID) {
	return CVirtualMachine__StackPopObject(this, oID);
}