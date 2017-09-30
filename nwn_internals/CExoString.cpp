#include <windows.h>
#include "CExoString.h"

DWORD CExoString__operator_as_c = 0x40BAA0;
DWORD CExoString__operator_as_CExoString = 0x40B9D0;
DWORD CExoString__operator_pl = 0x40BF10;
DWORD CExoString__CExoString = 0x512AA0;//TODO
DWORD CExoString__CExoString_c = 0x40B7E0;
DWORD CExoString___CExoString = 0x40B9A0;
DWORD CExoString__Format = 0x40C340;
DWORD CExoString__operator_equal_CExoString = 0x40BB60;
DWORD CExoString__operator_equal_c = 0x40BBF0;
DWORD CExoString__operator_not_CExoString = 0x40BC70;
DWORD CExoString__operator_not_c = 0x40BCF0;

__declspec( naked ) CExoString::CExoString(){ __asm{ jmp dword ptr [CExoString__CExoString] }}
__declspec( naked ) CExoString::CExoString(char const *str){ __asm{ jmp dword ptr [CExoString__CExoString_c] }}
__declspec( naked ) CExoString::~CExoString(){__asm{ jmp dword ptr [CExoString___CExoString] }}


 __declspec( naked ) CExoString & CExoString::operator=(char const *){ __asm{ jmp dword ptr [CExoString__operator_as_c] }}
 __declspec( naked ) CExoString & CExoString::operator=(CExoString const &){ __asm{ jmp dword ptr [CExoString__operator_as_CExoString] }}
 __declspec( naked ) CExoString CExoString::operator+(CExoString const &) const{ __asm{ jmp dword ptr [CExoString__operator_pl] }}

  __declspec( naked ) int CExoString::Format(int, char *, char) { __asm{ jmp dword ptr [CExoString__Format] }}

  __declspec( naked ) bool CExoString::operator==(CExoString const &Comp){ __asm{ jmp dword ptr [CExoString__operator_equal_CExoString] }}
  __declspec( naked ) bool CExoString::operator==(char const *){ __asm{ jmp dword ptr [CExoString__operator_equal_c] }}
  __declspec( naked ) bool CExoString::operator!=(CExoString const &Comp){ __asm{ jmp dword ptr [CExoString__operator_not_CExoString] }}
  __declspec( naked ) bool CExoString::operator!=(char const *){ __asm{ jmp dword ptr [CExoString__operator_not_c] }}