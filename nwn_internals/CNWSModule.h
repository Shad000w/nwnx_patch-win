#ifndef _NX_NWN_STRUCT_CNWSMODULE_
#define _NX_NWN_STRUCT_CNWSMODULE_

struct CNWSModule_s{
	uint32_t obj_type;
	nwn_objid_t					obj_id			/* 0x004 */;
	uint32_t					field_08;
	uint32_t					field_0C;
	uint32_t					field_10;
	uint32_t					field_14;
	nwn_objid_t					*xmod_areas;//18
	uint32_t					xmod_areas_len;//1c
	uint32_t					xmod_areas_alloc;//20
	uint32_t					field_24;
	uint32_t					field_28;
	uint32_t					field_2C;
	uint32_t					field_30;
	nwn_objid_t					*mod_areas;//34
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
	uint32_t					field_140;
	uint32_t					field_144;
	uint32_t					field_148;
	uint32_t					field_14C;
	uint32_t					field_150;//CExoArrayList_ptr			mod_lookuptable;/* 0x0150 */
	uint32_t					field_154;
	uint32_t					field_158;
	uint32_t					field_15C;
	uint32_t					field_160;
	nwn_objid_t					mod_last_enter;/* 0x0164 */
	nwn_objid_t					mod_last_exit;/* 0x0168 */
	nwn_objid_t					mod_last_item_aquired;/* 0x016C */
	nwn_objid_t					mod_last_item_aquired_from;/* 0x0170 */
	nwn_objid_t					mod_last_item_aquired_by;/* 0x0174 */
	uint32_t					field_178;
	uint32_t					field_17C;
	uint32_t					mod_last_item_aquired_stack_size;/* 0x0180 */
	uint32_t					field_184;
	uint32_t					field_188;
	uint32_t					field_18C;
	uint32_t					field_190;
	uint32_t					field_194;
	nwn_objid_t					mod_last_rested;//198
	uint32_t					field_19C;
	nwn_objid_t					mod_last_player_died;//1A0
	nwn_objid_t					mod_last_player_dying;//1A4
	uint32_t					field_1A8;
	uint32_t					field_1AC;
	uint32_t					field_1B0;
	uint32_t					field_1B4;
	uint32_t					field_1B8;
	uint32_t					field_1BC;//hodnota 127?
	uint32_t					field_1C0;
	uint32_t					field_1C4;
	uint32_t					field_1C8;
	uint32_t					field_1CC;
	uint8_t						mod_min_per_hour;//1D0
	uint8_t						mod_dawnhour;//1D1
	uint8_t						mod_duskhour;//1D2
	uint8_t						mod_start_month;//1D3
	uint8_t						mod_start_day;//1D4
	uint8_t						mod_start_hour;//1D5
	uint8_t						mod_xp_scale;//1D6
	uint8_t						field_1D7;//1D7
	uint32_t					mod_date_year;//1D8
	uint32_t					mod_date_month;//1DC
	uint32_t					mod_date_day;//1E0
	uint32_t					mod_time_hour;//1E4
	uint32_t					field_1E8;
	uint32_t					field_1EC;//1?
	uint32_t					field_1F0;//461132?
	uint32_t					field_1F4;//1584496?
	uint32_t					field_1F8;
	uint32_t					field_1FC;
	uint32_t					field_200;
	uint32_t					field_204;
	uint32_t					field_208;//1?
	uint32_t					mod_max_henchmen;
	nwn_objid_t					*mod_limbo_list;//todo verify
	uint32_t					mod_limbo_list_len;//todo verify
	uint32_t					mod_limbo_list_alloc;//todo verify
	uint32_t					field_21C;
	uint32_t					field_220;
	uint32_t					field_224;
	uint32_t					field_228;
	CExoString					mod_tag;//230-234
	uint32_t					mod_is_official_campaign;//238
	CExoString					mod_nwm_res_name;//23C-240
	uint32_t					mod_table_count; //244
	uint8_t						mod_pc_pathfind_rule;//248
	uint8_t						mod_enable_script_debugger;//249
	uint8_t						field_24A;
	uint8_t						field_24B;
	nwn_objid_t					mod_last_pc_chat_obj;//24C
	CExoString					mod_last_pc_chat;//250-254
	uint32_t					mod_last_pc_chat_type;//258
	uint32_t					field_258;

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

