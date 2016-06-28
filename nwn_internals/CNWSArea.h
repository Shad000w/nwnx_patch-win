#ifndef _NX_NWN_STRUCT_CNWSAREA_
#define _NX_NWN_STRUCT_CNWSAREA_

struct CNWSArea_s {
	void						*are_vftable;
	uint32_t					are_terrain;//04    - bitflag 4 natural, 2 undeground, 1 interior 
	uint32_t					are_width;//08
	uint32_t					are_height;//0c
	uint32_t					field_10;//hodnota 16?
	uint32_t					field_14;// microset 5 krypta 1?
	uint32_t					field_18;
	uint32_t					field_1C;
	uint32_t					field_20;
	uint32_t					field_24;
	uint32_t					field_28;
	uint32_t					field_2C;// hodnota 48
	uint32_t					field_30;//microset 14 krypta 2

	CExoLocString				area_name;				/* 0x0034 */
	CExoString					not_area_tag;				/* 0x003C */
	char						area_tileset_ref[16];	/* 0x0044 */	//no terminator

	uint32_t					field_54;
	uint32_t					field_58;
	uint32_t					field_5C;
	CExoString					are_script_hb;//60
	CExoString					are_script_userdefined;//68
	CExoString					are_script_onenter;//70
	CExoString					are_script_onexit;//78
	uint32_t					field_80;
	uint32_t					field_84;
	uint32_t					field_88;//1 microset 0krypta
	uint32_t					field_8C;//1 oba tilesety
	uint32_t					field_90;
	uint32_t					field_94;
	uint32_t					field_98;
	uint32_t					NoRest;
	uint32_t					field_A0;//50microset 60krypta
	uint32_t					field_A4;
	uint32_t					field_A8;
	uint32_t					field_AC;
	uint32_t					field_B0;
	uint32_t					*area_git;//CResRef
	uint32_t					field_B8;
	uint32_t					field_BC;
	uint32_t					field_C0;
	uint32_t					obj_type;//c4
	nwn_objid_t					obj_id;//c8
	uint32_t					obj_type2;//cc
	uint32_t					are_numplayers;//d0
	uint32_t					field_D4;
	uint32_t					field_D8;
	uint32_t					field_DC;
	uint32_t					field_E0;
	uint32_t					field_E4;
	uint32_t					field_E8;
	uint32_t					field_EC;
	uint32_t					field_F0;
	uint32_t					field_F4;
	uint32_t					field_F8;
	uint32_t					field_FC;
	CExoString					are_tag;//100
	uint32_t					field_108;
	uint32_t					field_10C;
	CNWSScriptVarTable			area_vartable;	/* 0x0110 */
	uint32_t					field_118;
	uint32_t					field_11C;//some pointer to pathfinding
	uint32_t					field_120;
	uint32_t					field_124;
	uint32_t					field_128;
	uint32_t					field_12C;
	uint32_t					field_130;
	uint32_t					field_134;
	uint32_t					field_138;
	uint32_t					field_13C;
	uint32_t					field_140;
	uint32_t					field_144;
	uint32_t					field_148;
	uint32_t					field_14C;
	nwn_objid_t					*obj_list; //150
	uint32_t					obj_list_len; //154
	uint32_t					obj_list_alloc; //158
	uint32_t					first_next_obj_index; //15C
	uint32_t					*transition_list; //160
	uint32_t					transition_list_len; //164
	uint32_t					transition_list_alloc; //168
	uint32_t					field_16C;
	uint32_t					field_170;
	uint32_t					field_174;
	uint32_t					field_178;
	uint32_t					field_17C;
	uint32_t					field_180;
	uint32_t					field_184;
	uint32_t					field_188;
	uint32_t					field_18C;
	uint32_t					field_190;
	uint32_t					field_194;//some pointer to pathfinding
	uint32_t					field_198;
	uint32_t					field_19C;
	uint32_t					field_1A0;
	uint32_t					field_1A4;
	uint32_t					field_1A8;
	uint32_t					field_1AC;
	uint32_t					field_1B0;
	uint32_t					field_1B4;
	uint32_t					field_1B8;
	uint32_t					field_1BC;
	uint32_t					field_1C0;
	uint32_t					field_1C4;
	uint32_t					field_1C8;
	uint32_t					field_1CC;
	uint32_t					field_1D0;
	uint32_t					field_1D4;
	uint32_t					field_1D8;
	uint32_t					field_1DC;
	uint32_t					field_1E0;
	uint32_t					field_1E4;
	uint32_t					field_1E8;
	uint32_t					field_1EC;
	uint32_t					field_1F0;
	uint32_t					field_1F4;
	uint32_t					field_1F8;
	uint8_t						field_1FC;
	uint8_t						are_weather;//1FD
	uint8_t						field_1FE;
	uint8_t						are_pvp_settings;
	uint32_t					field_200;
	uint32_t					field_204;
	uint32_t					are_loadscreen_id;

void Destructor();
void CNWSArea(CResRef, int, unsigned long);
    
signed int 	AddObjectToArea(unsigned int Object_ID, int bRunEnterScript);
int 		ClearLineOfSight(Vector v1, Vector v2, Vector *v3, uint32_t *, nwn_objid_t, nwn_objid_t, uint8_t);
long double ComputeHeight( Vector v );
signed int 	ExploreArea(CNWSCreature *a2, int a3, int a4, int a5);
signed int 	GetFirstObjectInArea(nwn_objid_t *oID);
signed int 	GetNextObjectInArea(nwn_objid_t *oID);
CNWTile*	GetTile(float x, float y, int z);
int 		LoadArea(int);
signed int 	RemoveObjectFromArea(unsigned int oID);
void *		SetScriptName(int iScript, CExoString ScriptName);
void		scalar_Destructor(char Flag);
void		UpdatePlayerAutomaps();

};

#endif /* _NX_NWN_STRUCT_CNWSAREA_ */

/* vim: set sw=4: */
