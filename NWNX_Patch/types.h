#ifndef _NX_NWN_TYPES_H_
#define _NX_NWN_TYPES_H_

#include "../nwn_internals/nwn_const.h"
#include ".\nwnx_funcs_const.h"
#include ".\CExoString.h"

struct CNWSAction_s;						typedef struct CNWSAction_s						CNWSAction;
struct CResStruct_s;						typedef struct CResStruct_s						CResStruct;
struct CVirtualMachineCommands_s;			typedef struct CVirtualMachineCommands_s		CVirtualMachineCommands;
struct CNWSObjectActionNode_s;				typedef struct CNWSObjectActionNode_s			CNWSObjectActionNode;
struct CCodeBase_s;							typedef struct CCodeBase_s						CCodeBase;
struct CResource_s;							typedef struct CResource_s						CResource; 
struct CTwoDimArrays_s;						typedef struct CTwoDimArrays_s					CTwoDimArrays;
struct C2DA_s;								typedef struct C2DA_s							C2DA; 
struct CExoArrayList_float_s;             	typedef struct CExoArrayList_float_s            CExoArrayList_float;
struct CExoArrayList_int32_s;             	typedef struct CExoArrayList_int32_s            CExoArrayList_int32;
struct CExoArrayList_int8_s;              	typedef struct CExoArrayList_int8_s             CExoArrayList_int8;
struct CExoArrayList_ptr_s;               	typedef struct CExoArrayList_ptr_s              CExoArrayList_ptr;
struct CExoArrayList_uint16_s;            	typedef struct CExoArrayList_uint16_s           CExoArrayList_uint16;
struct CExoArrayList_uint32_s;            	typedef struct CExoArrayList_uint32_s           CExoArrayList_uint32;
struct CExoArrayList_uint64_s;            	typedef struct CExoArrayList_uint64_s           CExoArrayList_uint64;
struct CExoArrayList_uint8_s;             	typedef struct CExoArrayList_uint8_s            CExoArrayList_uint8; 
struct CExoArrayList_string_s;             	typedef struct CExoArrayList_string_s           CExoArrayList_string;
struct CResRef_s;							typedef struct CResRef_s						CResRef;
struct CResGFF_s;							typedef struct CResGFF_s						CResGFF;
struct Vector_s;							typedef struct Vector_s                         Vector;
struct CNWClass_s;							typedef struct CNWClass_s						CNWClass;
struct CScriptEvent_s;						typedef struct CScriptEvent_s					CScriptEvent;
struct CNWCCMessageData_s;					typedef struct CNWCCMessageData_s				CNWCCMessageData;
struct CNWSFaction_s;						typedef struct CNWSFaction_s                    CNWSFaction;
struct CFactionManager_s;					typedef struct CFactionManager_s                CFactionManager;
//struct CExoString_s; typedef CExoString_s CExoString;
//struct CExoLinkedListHeader_s;				typedef struct CExoLinkedListHeader_s           CExoLinkedListHeader;
//struct CExoLinkedListNode_s;				typedef struct CExoLinkedListNode_s             CExoLinkedListNode;
class CExoLinkedList_s;					typedef CExoLinkedList_s                 CExoLinkedList;
//struct CExoLocStringElement_s;				typedef struct CExoLocStringElement_s           CExoLocStringElement;
class  CExoLocString_s;						typedef CExoLocString_s                  		CExoLocString; 
struct CNWSpell_s;							typedef CNWSpell_s								CNWSpell;
struct CNWSpellArray_s;						typedef CNWSpellArray_s							CNWSpellArray;
struct CNWSAreaOfEffectObject_s;          typedef struct CNWSAreaOfEffectObject_s          CNWSAreaOfEffectObject; 
struct CNWSSoundObject_s;                 typedef struct CNWSSoundObject_s                 CNWSSoundObject; 
struct CNWSWaypoint_s;                    typedef struct CNWSWaypoint_s                    CNWSWaypoint; 
struct CNWSEncounter_s;                   typedef struct CNWSEncounter_s                   CNWSEncounter; 
struct CNWSSoundObject_s;                 typedef struct CNWSSoundObject_s                 CNWSSoundObject; 
struct CNWSStore_s;                       typedef struct CNWSStore_s                       CNWSStore; 
struct CNWSPlayerCharSheetGUI_s;			typedef struct CNWSPlayerCharSheetGUI_s			CNWSPlayerCharSheetGUI;
struct CNWSAction_s;						typedef struct CNWSAction_s						CNWSAction;
struct CNWSClient_s;						typedef struct CNWSClient_s						CNWSClient;
struct CNWSPlayer_s;                      typedef struct CNWSPlayer_s                      CNWSPlayer;
struct CNWSPlayerTURD_s;					typedef struct CNWSPlayerTURD_s					CNWSPlayerTURD;
struct CServerAIMaster_s;                 typedef struct CServerAIMaster_s                 CServerAIMaster; 
struct CWorldTimer_s;                     typedef struct CWorldTimer_s                     CWorldTimer; 
struct CServerExoAppConfig_s;				typedef CServerExoAppConfig_s					CServerExoAppConfig;
struct CServerExoApp_s;                   typedef struct CServerExoApp_s                   CServerExoApp;
struct CServerExoAppInternal_s;           typedef struct CServerExoAppInternal_s           CServerExoAppInternal;
struct CNWBaseItem_s;						typedef CNWBaseItem_s							CNWBaseItem;
struct CNWBaseItemArray_s;					typedef CNWBaseItemArray_s						CNWBaseItemArray;
struct CExoResMan_s;						typedef CExoResMan_s							CExoResMan;
struct CTlkTable_s;							typedef CTlkTable_s								CTlkTable;
struct CNWTlkTable_s;						typedef CNWTlkTable_s							CNWTlkTable;
struct CNWRules_s;							typedef struct CNWRules_s						CNWRules;
struct CNWSEffectListHandler_s;				typedef struct CNWSEffectListHandler_s			CNWSEffectListHandler;
struct CNetLayer_s;                       typedef struct CNetLayer_s                       CNetLayer;
struct CAppManager_s;                     typedef struct CAppManager_s                     CAppManager;
struct CScriptLocation_s;                 typedef struct CScriptLocation_s                 CScriptLocation; 
struct CScriptVariable_s;					typedef struct CScriptVariable_s				CScriptVariable;
struct CNWSCombatAttackData_s;            typedef struct CNWSCombatAttackData_s            CNWSCombatAttackData;
struct CNWSCombatRound_s;                 typedef struct CNWSCombatRound_s                 CNWSCombatRound; 
struct CNWSScriptVarTable_s;				typedef struct CNWSScriptVarTable_s				CNWSScriptVarTable;
struct CNWSQuickbarButton_s;				typedef CNWSQuickbarButton_s				CNWSQuickbarButton;
struct CNWSStats_Spell_s;					typedef struct CNWSStats_Spell_s				CNWSStats_Spell;
struct CNWSStats_Level_s;					typedef struct CNWSStats_Level_s				CNWSStats_Level;
struct CCombatinformation_s;				typedef struct CCombatinformation_s				CCombatinformation;
struct CNWSCreatureEventHandler_s;			typedef struct CNWSCreatureEventHandler_s		CNWSCreatureEventHandler;
struct CGameEffect_s;						typedef struct CGameEffect_s                    CGameEffect; 
struct CGameObject_VTable_s;              	typedef struct CGameObject_VTable_s             CGameObject_VTable;
struct CItemRepository_s;                 typedef struct CItemRepository_s                 CItemRepository;
struct CLastUpdateObject_s;               typedef struct CLastUpdateObject_s               CLastUpdateObject;
struct CNWSObject_s;						typedef struct CNWSObject_s                     CNWSObject; 
struct CNWSItemProperty_s;                 	typedef struct CNWSItemProperty_s               CNWSItemProperty; 
struct CNWSInventory_s;                     typedef struct CNWSInventory_s                   CNWSInventory; 
struct CNWSItemPropertyHandler_s;			typedef struct CNWSItemPropertyHandler_s		CNWSItemPropertyHandler;
struct CNWSItem_s;                          typedef struct CNWSItem_s                       CNWSItem; 
struct CNWTile_s;							typedef struct CNWTile_s						CNWTile;
struct CNWSTile_s;							typedef struct CNWSTile_s						CNWSTile;
struct CNWSArea_s;							typedef struct CNWSArea_s						CNWSArea;
struct CNWMessage_s;                     	typedef struct CNWMessage_s                     CNWMessage;
struct CNWSMessage_s;                     	typedef struct CNWSMessage_s                     CNWSMessage;
struct CGameObjectArrayElement_s;			typedef struct CGameObjectArrayElement_s		CGameObjectArrayElement;
struct CGameObjectArray_s;					typedef struct CGameObjectArray_s				CGameObjectArray;
struct CLookupTableObject_s;				typedef struct CLookupTableObject_s				CLookupTableObject;
struct CNWSModule_s;						typedef struct CNWSModule_s						CNWSModule;
struct CNWSDoor_s;                        	typedef struct CNWSDoor_s                       CNWSDoor; 
struct CNWSTrigger_s;                     	typedef struct CNWSTrigger_s                    CNWSTrigger; 
struct CNWSPlaceable_s;                   	typedef struct CNWSPlaceable_s                  CNWSPlaceable; 
struct CGenericObject_s;					typedef struct CGenericObject_s					CGenericObject;
struct CNWSCreatureAppearanceInfo_s;      	typedef struct CNWSCreatureAppearanceInfo_s     CNWSCreatureAppearanceInfo;
struct CNWSCreatureClass_s;               	typedef struct CNWSCreatureClass_s              CNWSCreatureClass;
struct CNWSCreatureStats_s;               	typedef struct CNWSCreatureStats_s              CNWSCreatureStats;
struct CNWSCreature_s;                    	typedef struct CNWSCreature_s                   CNWSCreature; 
class CQuickbarExtension;
struct CVirtualMachine_s;                 typedef struct CVirtualMachine_s                 CVirtualMachine;
struct CNWVisibilityNode_s;					typedef struct CNWVisibilityNode_s				CNWVisibilityNode;
struct CNWLevelStats_s;                     typedef struct CNWLevelStats_s                  CNWLevelStats;

struct CEffectsStore_s {
	nwn_objid_t objid;
	uint16_t len;
	uint32_t *pEffect; //this really is just a list of pointers.
};

struct CEffectsStore_s; typedef struct CEffectsStore_s CEffectsStore;

#include "..\nwn_internals\CNWSAction.h"
#include "..\nwn_internals\CExoArrayList.h"
#include "..\nwn_internals\Vector.h"
#include "..\nwn_internals\CExoLinkedList.h"
//#include ".\CExoString.h"
//#include ".\CExoLinkedListHeader.h"
//#include ".\CExoLinkedListNode.h" 
//#include ".\CExoLocStringElement.h" 
#include "..\nwn_internals\CExoLocString.h"
#include "..\nwn_internals\CScriptLocation.h"
#include "..\nwn_internals\CScriptVariable.h"
#include "..\nwn_internals\CNWSMessage.h"
#include "..\nwn_internals\CNWMessage.h"
#include "..\nwn_internals\CNWBaseItem.h"
#include "..\nwn_internals\CNWSQuickbarButton.h"
#include "..\nwn_internals\CNWSCreatureEventHandler.h"
#include "..\nwn_internals\CNWSScriptVarTable.h"
#include "..\nwn_internals\CGameObject_VTable.h"
#include "..\nwn_internals\CGenericObject.h"
#include "..\nwn_internals\CNWSObject.h"
#include "..\nwn_internals\CNWSDoor.h"
#include "..\nwn_internals\CNWSTrigger.h"
#include "..\nwn_internals\CNWSPlaceable.h"
#include "..\nwn_internals\CNWSPlayer.h"
#include "..\nwn_internals\CServerAIMaster.h" 
#include "..\nwn_internals\CServerExoAppConfig.h"
#include "..\nwn_internals\CServerExoApp.h"
#include "..\nwn_internals\CServerExoAppInternal.h"
#include "..\nwn_internals\CNetLayer.h"
#include "..\nwn_internals\CNWBaseItemArray.h"
#include "..\nwn_internals\CNWRules.h"
#include "..\nwn_internals\CAppManager.h"
#include "..\nwn_internals\CNWSAreaOfEffectObject.h"
#include "..\nwn_internals\CNWSWaypoint.h"
#include "..\nwn_internals\CNWSEncounter.h"
#include "..\nwn_internals\CNWSStore.h"
#include "..\nwn_internals\CNWSSoundObject.h"
#include "..\nwn_internals\CNWSItemProperty.h"
#include "..\nwn_internals\CNWSItemPropertyHandler.h"
#include "..\nwn_internals\CNWSInventory.h"
#include "..\nwn_internals\CNWSItem.h"
#include "..\nwn_internals\CNWSCreatureAppearanceInfo.h"
#include "..\nwn_internals\CNWSCreature.h"
#include "..\nwn_internals\CNWSStats_Spell.h"
#include "..\nwn_internals\CNWSStats_Level.h"
#include "..\nwn_internals\CNWSCreatureClass.h" 
#include "..\nwn_internals\CNWSCreatureStats.h"
#include "..\nwn_internals\CGameEffect.h"
#include "..\nwn_internals\CItemRepository.h" 
#include "..\nwn_internals\CLastUpdateObject.h"
#include "..\nwn_internals\CNWSArea.h"
#include "..\nwn_internals\CNWSModule.h"
#include "..\nwn_internals\CWorldTimer.h"
#include "..\nwn_internals\CQuickbarExtension.h"
#include "..\nwn_internals\CVirtualMachine.h"
#include "..\nwn_internals\CNWVisibilityNode.h"
#include "..\nwn_internals\CNWSCombatAttackData.h"
#include "..\nwn_internals\CNWSCombatRound.h" 
#include "..\nwn_internals\CGameObjectArrayElement.h"
#include "..\nwn_internals\CGameObjectArray.h"
#include "..\nwn_internals\CNWTlkTable.h"
#include "..\nwn_internals\CTlkTable.h"
#include "..\nwn_internals\CResRef.h"
#include "..\nwn_internals\CExoResMan.h"
#include "..\nwn_internals\CLookupTableObject.h"
#include "..\nwn_internals\CNWSClient.h"
#include "..\nwn_internals\CNWCCMessageData.h"
#include "..\nwn_internals\CNWSTile.h"
#include "..\nwn_internals\CNWTile.h"
#include "..\nwn_internals\CFactionManager.h"
#include "..\nwn_internals\CNWSFaction.h"
#include "..\nwn_internals\CCombatinformation.h"
#include "..\nwn_internals\CNWSPlayerTURD.h"
#include "..\nwn_internals\CResource.h"
#include "..\nwn_internals\C2DA.h"
#include "..\nwn_internals\CNWSPlayerCharSheetGUI.h"
#include "..\nwn_internals\CTwoDimArrays.h"
#include "..\nwn_internals\CScriptEvent.h"
#include "..\nwn_internals\CNWSpell.h"
#include "..\nwn_internals\CNWClass.h"
#include "..\nwn_internals\CNWSpellArray.h"
#include "..\nwn_internals\CResGFF.h"
#include "..\nwn_internals\CCodeBase.h"
#include "..\nwn_internals\CNWSObjectActionNode.h"
#include "..\nwn_internals\CVirtualMachineCommands.h"
#include "..\nwn_internals\CResStruct.h"
#include "..\nwn_internals\CNWLevelStats.h"

#include "..\nwn_internals\nwn_internals.h"

#endif /* _NX_NWN_TYPES_H_ */