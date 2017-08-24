#include <windows.h>
#ifndef CExoString_h_
#define CExoString_h_

struct CExoString
{
public:
	char *text;
	ULONG Length;

	CExoString();
	CExoString(char const *);
	~CExoString();
	bool operator!=(CExoString const &Comp);
	bool operator!=(char const *Comp);
	bool operator==(CExoString const &Comp);
	bool operator==(char const *c);
	CExoString & operator=(char const *);
	CExoString & operator=(CExoString const &);
	CExoString operator+(CExoString const &) const;

	int Format(int a1, char *a2, char a3);

};

#endif