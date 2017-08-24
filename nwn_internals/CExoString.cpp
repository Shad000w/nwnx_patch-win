#include <windows.h>
#include "CExoString.h"

DWORD CExoString__operator_as_c = 0x40BAA0;
DWORD CExoString__operator_as_CExoString = 0x40B9D0;
DWORD CExoString__operator_pl = 0x40BF10;
DWORD CExoString__CExoString = 0x512AA0;//TODO
DWORD CExoString__CExoString_c = 0x40B7E0;
DWORD CExoString___CExoString = 0x40B9A0;
DWORD CExoString__Format = 0x40C340;

__declspec( naked ) CExoString::CExoString(){ __asm{ jmp dword ptr [CExoString__CExoString] }}
__declspec( naked ) CExoString::CExoString(char const *str){ __asm{ jmp dword ptr [CExoString__CExoString_c] }}
__declspec( naked ) CExoString::~CExoString(){__asm{ jmp dword ptr [CExoString___CExoString] }}


 __declspec( naked ) CExoString & CExoString::operator=(char const *){ __asm{ jmp dword ptr [CExoString__operator_as_c] }}
 __declspec( naked ) CExoString & CExoString::operator=(CExoString const &){ __asm{ jmp dword ptr [CExoString__operator_as_CExoString] }}
 __declspec( naked ) CExoString CExoString::operator+(CExoString const &) const{ __asm{ jmp dword ptr [CExoString__operator_pl] }}

  __declspec( naked ) int CExoString::Format(int, char *, char) { __asm{ jmp dword ptr [CExoString__Format] }}

 bool CExoString::operator!=(const CExoString &Comp) {
	bool result=false;
	char *c = this->text;
	char *c2 = Comp.text;
	if (text && Comp.text) {
		if (strcmp(c, c2))
			result = true;
	}
	else {
		result = c && *c || c2 && *c2;
	}
	return result;
}

bool CExoString::operator!=(char const *Comp) {
	bool result=false;
	char *c = this->text;
	if (text && Comp) {
		if (strcmp(text, Comp) != 0)
			result = true;
	}
	else {
		result = c && *c || Comp && *Comp;
	}
	return result;
}

bool CExoString::operator==(CExoString const &Comp) {
	if (!text && !Comp.text) return true;
	else if (!text && Comp.text || text && !Comp.text)
		return false;
	
	//both have to be valid pointers at this point
	if (strcmp(text, Comp.text))
		return false;
		
	return true;
}

bool CExoString::operator==(char const *c) {
	if (!text && !c) return true;
	else if (!text && c || text && !c)
		return false;
	
	//both have to be valid pointers at this point
	if (strcmp(text, c))
		return false;
		
	return true;
}