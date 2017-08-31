#ifndef _NX_NWN_STRUCT_CNWSMODULE_
#define _NX_NWN_STRUCT_CNWSMODULE_

struct CNWSModule_s{
	uint32_t obj_type;
	uint32_t					obj_id			/* 0x004 */;
	uint32_t					field_08;
	uint32_t					field_0C;
	uint32_t					field_10;
	uint32_t					field_14;
	uint32_t					field_18;
	uint32_t					field_1C;
	uint32_t					field_20;
	uint32_t					field_24;
	uint32_t					field_28;
	uint32_t					field_2C;
	uint32_t					field_30;
	uint32_t					*mod_areas;
	uint32_t					mod_areas_len;
	uint32_t					mod_areas_alloc;
	uint32_t					field_40;
	uint32_t					field_44;
	uint32_t					field_48;
	uint32_t					field_4C;
	uint32_t					mod_PlayerTURDList;//50  //should be CExoLinkedList
	//CExoLocString				*mod_description;//54
	CExoString					mod_custom_tlk;//58-5C
	CExoLocString				*mod_description;//54
	//CExoString					mod_custom_tlk2;//58-5C
	uint32_t					field_60;
	CExoString					mod_current_game;//64-68
	uint32_t					field_6C;
	uint32_t					field_70;
	uint32_t					field_74;
	uint32_t					mod_is_demo;//78
	uint32_t					mod_1;//7C
	CExoLocString				mod_name;/* 0x0080 */
	CExoArrayList_string		mod_haks; /* 0x88, 0x8C, 0x90 */
	//uint32_t					field_88;//CExoStringList				mod_haks;/* 0x0084 */
	//uint32_t					field_8C;
	//uint32_t					field_90;
	uint32_t					field_94;//CResRef						mod_dunno;
	uint32_t					field_98;
	uint32_t					field_9C;
	uint32_t					field_A0;
	CNWSScriptVarTable			mod_vartable;//A4
	uint32_t					field_AC;
	uint32_t					field_B0;
	CExoString					mod_scripts[18];//B4-13C
/*
	CExoString					Mod_OnHeartbeat;
	CExoString					Mod_OnUsrDefined;
	CExoString					Mod_OnModLoad;
	CExoString					Mod_OnModStart;
	CExoString					Mod_OnClientEntr;
	CExoString					Mod_OnClientLeav;
	CExoString					Mod_OnActvtItem;
	CExoString					Mod_OnAcquirItem;
	CExoString					Mod_OnUnAqreItem;
	CExoString					Mod_OnPlrDeath;
	CExoString					Mod_OnPlrDying;
	CExoString					Mod_OnSpawnBtnDn;
	CExoString					Mod_OnPlrRest;
	CExoString					Mod_OnPlrLvlUp;
	CExoString					Mod_OnCutsnAbort;
	CExoString					Mod_OnPlrEqItm;
	CExoString					Mod_OnPlrUnEqItm;
	CExoString					Mod_OnPlrChat;  
*/
    uint32_t m_nLastHeartbeatScriptCalendarDay;
    uint32_t m_nLastHeartbeatScriptTimeOfDay;
	uint32_t					field_148;
	uint32_t					field_14C;
	uint32_t					field_150;//CExoArrayList_ptr			mod_lookuptable;/* 0x0150 */
	uint32_t					field_154;
	uint32_t					field_158;
	uint32_t					field_15C;
	int32_t m_nCustomScriptEventId;
	uint32_t m_oidLastEnter;
    uint32_t m_oidLastExit;
    uint32_t m_oidLastItemAcquired;
    uint32_t m_oidLastItemAcquiredFrom;
    uint32_t m_oidLastItemAcquiredBy;
    uint32_t m_oidLastItemLost;
    uint32_t m_oidLastItemLoser;
	int32_t m_nLastItemAcquiredSize;//0x180
	int32_t m_nLastItemLostSize;
	uint32_t m_oidLastItemEquipped;
    uint32_t m_oidLastItemEquippedBy;
    uint32_t m_oidLastItemUnequipped;
    uint32_t m_oidLastItemUnequippedBy;
    uint32_t m_oidLastRested;
	uint8_t m_nLastRestEventType;
    uint32_t m_oidLastPlayerDied;
    uint32_t m_oidLastPlayerDying;
    uint32_t m_oidLastRespawnButtonPresser;
    uint32_t m_oidLastItemActivated;
    uint32_t m_oidLastItemActivator;
    uint32_t m_oidLastItemActivatedArea;
	uint32_t m_oidLastItemActivatedTarget;
	Vector m_vLastItemActivatedPosition;
	uint32_t m_oidLastPCLevellingUp;
    uint32_t m_oidLastPCCancelCutscene;
	uint8_t m_nMinutesPerHour;
    uint8_t m_nDawnHour;
    uint8_t m_nDuskHour;
    uint8_t m_nStartMonth;
    uint8_t m_nStartDay;
    uint8_t m_nStartHour;
    uint8_t m_nXPScale;
    uint32_t m_nCurrentYear;
    uint32_t m_nCurrentMonth;
    uint32_t m_nCurrentDay;
    uint32_t m_nCurrentHour;
	uint32_t m_nTimeIntoTransition;
    uint8_t m_nTimeOfDayState;
    uint32_t m_nLastUpdateCalendarDay;
    uint32_t m_nLastUpdateTimeOfDay;
    int32_t m_bIsSaveGame;
	
	uint32_t					field_1FC;
	uint32_t					field_200;
	uint32_t					field_204;
    int32_t m_bModuleLoadFinished;
    int32_t m_nMaxHenchmen;
	uint32_t					*mod_limbo_list;//todo verify
	uint32_t					mod_limbo_list_len;//todo verify
	uint32_t					mod_limbo_list_alloc;//todo verify
	uint32_t					field_21C;
	uint32_t					field_220;
	uint32_t					field_224;
	uint32_t					field_228;

	CExoString m_sTag;
    int32_t m_bIsNWMFile;
    CExoString m_sNWMResName;
    int32_t m_nResourceCount;
    uint8_t m_nPlayerPathfindRule;
    uint8_t m_nEnableScriptDebugger;
    uint32_t m_oidLastPlayerChatObjectId;
    CExoString m_sLastPlayerChatMessage;
    uint8_t m_nLastPlayerChatType;

	nwn_objid_t			FindObjectByTagTypeOrdinal(CExoString *tag, int type, unsigned long nth);
	void				AddObjectToLimbo(nwn_objid_t oID);
	int 				AddObjectToLookupTable(CExoString Tag, nwn_objid_t oID);
	CNWSArea * 			GetArea(nwn_objid_t oID);
	CNWSPlayerTURD* 	GetPlayerTURDFromList(CNWSPlayer *Player);
	void 				SetScriptName(int iScript, CExoString ScriptName);
	int 				RemoveObjectFromLookupTable(CExoString Tag, nwn_objid_t oID);
	nwn_objid_t			FindObjectByTagOrdinal(CExoString *sTag, int nNth);
};

#endif

