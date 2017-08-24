#ifndef _NX_NWN_STRUCT_CNWSAREA_
#define _NX_NWN_STRUCT_CNWSAREA_

#include "CResRef.h"

struct CNWSArea_s {
    void** are_vftable;
    uint32_t are_terrain;
    int32_t are_width;
    int32_t are_height;
    int32_t m_nStaticObjects;
    int32_t m_nStaticObjectsFilled;
    uint32_t* m_poidStaticObjectsObjectIds;
    int32_t* m_pnStaticObjectsTriangleStart;
    int32_t* m_pnStaticObjectsTriangleCount;
    int32_t* m_pnStaticObjectsVertexStart;
    int32_t* m_pnStaticObjectsVertexCount;
    int32_t m_nStaticObjectTriangleArraySize;
    int32_t m_nStaticObjectTriangles;
    int32_t* m_pnStaticObjectTriangles;
    int32_t m_nStaticObjectVertexArraySize;
    int32_t m_nStaticObjectVertices;
    Vector* m_pvStaticObjectVertices;
    int32_t m_nStaticBoundingBoxes;
    int32_t m_nStaticBoundingBoxesFilled;
    Vector* m_pvStaticBoundingBoxes;
    uint32_t* m_poidStaticBBObjectIds;
    Vector m_vFogColor;
    uint8_t m_nFogValue;
    uint32_t m_nMoonAmbientColor;
    uint32_t m_nMoonDiffuseColor;
    uint32_t m_nMoonFogColor;
    uint8_t m_nMoonFogAmount;
    int32_t m_bMoonShadows;
    uint32_t m_nSunAmbientColor;
    uint32_t m_nSunDiffuseColor;
    uint32_t m_nSunFogColor;
    uint8_t m_nSunFogAmount;
	int32_t						m_bSunShadows;
    int32_t						UseDayNightCycle;
	uint32_t					IsNight;
	uint8_t						SkyBox;
    uint8_t						ChanceOfRain;
    uint8_t						ChanceOfSnow;
    uint8_t						ChanceOfLightning;
    uint8_t						Wind;
    int32_t						NoRest;
    uint8_t						ShadowOpacity;
	float						FogClipDistance;//A4
	uint32_t					field_A8;
	uint32_t					field_AC;
	uint32_t					field_B0;
	uint32_t					*area_git;//CResRef
	uint32_t					field_B8;
	uint32_t					field_BC;
	uint32_t					field_C0;
	uint32_t					obj_type;//c4
	uint32_t					obj_id;//c8
	uint32_t					obj_type2;//cc
	uint32_t					are_numplayers;//d0
	uint32_t					*trap_list;//D4
	uint32_t					trap_list_len;//D8
	uint32_t					trap_list_alloc;//DC
	uint32_t					m_nObjectByNameIndex;//E0
	uint32_t					m_nLastHeartbeatScriptCalendarDay;//E4
	uint32_t					m_nLastHeartbeatScriptTimeOfDay;//E8
	uint32_t					*m_lstExpansions;//EC
	CExoString					m_sComments;//F0
	CExoString/*CExoLocString*/ area_name;//F8
	CExoString					are_tag;//100
	CResRef					area_tileset_ref;//108
	int/*CNWTileSet*/			*m_pTileSet;//118
    CNWSTile					*m_pTile;//11C
	int/*NWAreaHeader_st*/		*m_pHeader;//120
	CExoString					are_script_hb;//124
	CExoString					are_script_userdefined;//12C
	CExoString					are_script_onenter;//134
	CExoString					are_script_onexit;//13C
    int32_t						m_nChanceOfFog;//144
    int32_t						m_nAreaSpotModifier;//148
    int32_t						m_nAreaListenModifier;//14C
	uint32_t					*obj_list; //150
	uint32_t					obj_list_len; //154
	uint32_t					obj_list_alloc; //158
	uint32_t					m_nPosGameObjects;/*first_next_obj_index;*/ //15C
	uint32_t					*transition_list; //160
	uint32_t					transition_list_len; //164
	uint32_t					transition_list_alloc; //168
    int32_t						*m_pnInterTileTravel;//16C
    float						*m_pfInterTileExit;//170
    int32_t						*m_pnInterTileRegionVisited;//174
    uint8_t						*m_pnInterTileRegionDepths;//178
    int32_t 					m_nInterTileTravelLength;//17C
    int32_t 					m_nInterTileGoalX;//180
    int32_t 					m_nInterTileGoalY;//184
    int32_t 					m_nInterTileGoalRegion;//188
    float						m_fGoalTargetX;//18C
    float						m_fGoalTargetY;//190
    int/*CPathfindInformation*/	*m_pSearchInfo;//194
    int/*CPathfindInformation*/	*m_pSoundPathInfo;//198
    int/*CNWSAreaGridTransTableEntry*/ *m_pcGridTransTableEntry;//19C
    int32_t 					g_nUnsmoothedWPList;//1A0
    float* 						g_pfUnsmoothedWPList;//1A4
    int32_t 					g_nSmoothedWPList;//1A8
    float* 						g_pfSmoothedWPList;//1AC
    float 						g_fPersonalSpace;//1B0
    int32_t						m_bGridPathfindingTerminated;//1B4
    int32_t						m_nGridNodesSearched;//1B8
    uint32_t 					m_oidLastEntered;//1BC
    uint32_t 					m_oidLastLeft;//1C0
    int32_t 					m_nCustomScriptEventId;//1C4
    int/*CNWSAreaInterTileSuccessors*/	*m_pcInterTileSuccessors;//1C8
    int32_t* 					m_pbInterTileDeniedExitCheck;//1CC
    int32_t						m_bInterAreaDFSVisited;//1D0
	CNWSScriptVarTable			area_vartable;//1D4
	uint32_t					field_1DC;
	uint32_t					field_1E0;
	int/*CNWSAmbientSound*/		*m_pAmbientSound;//1E4
	uint32_t					m_nWeatherType;//1E8
	int32_t						m_bWeatherStarted;//1EC
    uint32_t					m_nWeatherMinDurationTimer;//1F0
    uint32_t					m_nLastUpdateCalendarDay;//1F4
    uint32_t					m_nLastUpdateTimeOfDay;//1F8
    uint8_t						m_nOverrideWeatherType;//1FC
    uint8_t						m_nCurrentWeatherType;//1FD
	uint8_t						are_lightning_scheme;//1FE
	uint8_t						are_pvp_settings;//1FF
	uint32_t					are_map_size;//200
    int32_t						are_environmental_audio;//204
	uint16_t					are_loadscreen_id;//208

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
