#ifndef _H_CNWSPLAYERCHARSHEETGUI_H_
#define _H_CNWSPLAYERCHARSHEETGUI_H_

struct CNWSPlayerCharSheetGUI_s {
	unsigned long ObjectID;
	char UpdatedList;//1: skills, 2: feats
	char field_5;
	char field_6;
	char field_7;
	void *CreatureStatsUpdate;
	
	uint32_t ComputeCharacterSheetUpdateRequired(CNWSPlayer *Player);
};

#endif