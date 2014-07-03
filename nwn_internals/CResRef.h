#ifndef _H_CRESREF_H_
#define _H_CRESREF_H_

struct CResRef_s {
public:
	char resref[16];
	
	CResRef *CResRef(char *Ref);
	//CResRef *CResRef(char *Ref);
}; 

#endif;