#ifndef _H_CNWSPELLARRAY_H_
#define _H_CNWSPELLARRAY_H_

struct CNWSpellArray_s {
	unsigned long spells_len;
	
	CNWSpell *GetSpell(int SpellID);

	void Load();

	CNWSpellArray *CNWSpellArray();
};


#endif