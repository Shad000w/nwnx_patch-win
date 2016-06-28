#ifndef _H_CNWLEVELSTATS_H
#define _H_CNWLEVELSTATS_H

struct CNWLevelStats_s
{
	CExoArrayList_uint32			ls_spells_known[10];

	unsigned long					unknown_1[30];

	CExoArrayList_uint16			ls_featlist;

	unsigned char					*ls_skilllist;
	unsigned char					ls_skillpoints;

	unsigned char					unknown_2;

	unsigned char					ls_ability;
	unsigned char					ls_hp;

	unsigned char					ls_class;

};

#endif