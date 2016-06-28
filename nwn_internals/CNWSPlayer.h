#ifndef _NX_NWN_STRUCT_CNWSPLAYER_
#define _NX_NWN_STRUCT_CNWSPLAYER_

struct CNWSPlayer_s {
	/* CNWSClient */
	uint32_t			vftable;			/* 0x00 */
	uint32_t			pl_id;				/* 0x04 */
	uint32_t			field_08;			/* 0x08 */
	/* end CNWSClient */

	unsigned __int32			field_0C;			/* 0x000C */
	unsigned __int32			field_10;			/* 0x0010 */
	unsigned __int32			field_14;			/* 0x0014 */
	unsigned __int32			field_18;			/* 0x0018 */
	unsigned __int32			field_1C;			/* 0x001C */
	unsigned __int32			field_20;			/* 0x0020 */
	unsigned __int32			field_24;			/* 0x0024 */
	unsigned __int32			field_28;			/* 0x0028 */
	unsigned __int32			field_2C;			/* 0x002C */
	unsigned __int32			obj_id;				/* 0x0030 */

	unsigned __int8				spacer1[65];		/* 0x0034 */

	char				pl_bicfile[19];		/* 0x0075 */

	//void					*m_pActiveObjectsLastUpdate;		/* 0x0C */
//	unsigned long			m_pActivePartyObjectsLastUpdate;	/* 0x10 */
//	unsigned long			AreaTransitionLoadScreenId;			/* 0x14 */
//	unsigned long			AreaTransitionBMP;					/* 0x18 */
//	unsigned long			field_1C;							/* 0x1C */
//	unsigned long			FloatyEffects;						/* 0x20 */
//	unsigned long			AreaListSize;						/* 0x24 */
//	unsigned long			*AreaList;							/* 0x28 */
//	unsigned long			LoginState;							/* 0x2C */
//	unsigned long			obj_id		;						/* 0x30 */
//	double					m_nLastUpdatedTime;					/* 0x34 */
//	unsigned long			m_oidLastObjectControlled;			/* 0x3C */
//	unsigned long			m_oidPCObject;						/* 0x40 */
//	unsigned long			m_bIsPrimaryPlayer;					/* 0x44 */
//	unsigned long			FromSaveGame;						/* 0x48 */
//	unsigned long			FromTURD;							/* 0x4C */
//	unsigned long			PlayerListIndex;					/* 0x50 */
//	unsigned long			PlayModuleListingCharacters;		/* 0x54 */
//	unsigned long			JournalQuestInfo;					/* 0x58 */
//	unsigned long			StoreGUIInfo;						/* 0x5C */
//	CNWSPlayerCharSheetGUI *PlayerCharSheetGUI;					/* 0x60 */
//	void					*m_pInventoryGUI;					/* 0x64 */
//	void					*m_pOtherInventoryGUI;				/* 0x68 */
//	unsigned long			PlayerLastUpdateObject;				/* 0x6C */
//	unsigned long			AlwaysRun;							/* 0x70 */
//	unsigned char			CharacterType;						/* 0x74 */
//	char					BicFile[16];						/* 0x75 */
//	unsigned long			CommunityNameAuthorized;			/* 0x88 */
//	unsigned long			ModuleInfoSucceeded;				/* 0x8C */
//	unsigned long			field_90;							/* 0x90 */
//	unsigned long			CutsceneState;						/* 0x94 */

	int						SetGameObject( CNWSObject * obj );
	int 					AddArea(uint32_t areaid);
	CGenericObject* 		GetGameObject();
	int 					HasExpansionPack(unsigned char a2, int a3);
	void					vec_dtor(char Flag);
	CLastUpdateObject*		GetLastUpdateObject( );
	CExoString*				GetPlayerName(CExoString *str);
};

#endif