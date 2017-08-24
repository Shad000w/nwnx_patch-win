#ifndef _NX_NWN_STRUCT_CNWSPLAYER_
#define _NX_NWN_STRUCT_CNWSPLAYER_

#include "CResRef.h"

struct CNWSPlayer_s {
	/* CNWSClient */
	unsigned __int32			vftable;			/* 0x0000 */
    unsigned __int32			pl_id;				/* 0x0004 */
    unsigned __int32			cl_lang;			/* 0x0008 */
    /* end CNWSClient */

	/*CExoLinkedListTemplatedCLastUpdateObject*/int *m_pActiveObjectsLastUpdate;
    /*CExoLinkedListTemplatedCLastUpdatePartyObject*/int *m_pActivePartyObjectsLastUpdate;
    int32_t m_nAreaTransitionBMP;
    CExoString m_sAreaTransitionName;
    int32_t m_bFloatyEffects;
    int32_t m_nAreas;
    uint32_t* m_pAreas;
    uint8_t m_nLoginState;
    uint32_t m_oidNWSObject;
    uint64_t m_nLastUpdatedTime;
    uint32_t m_oidLastObjectControlled;
    uint32_t m_oidPCObject;
    int32_t m_bIsPrimaryPlayer;
    int32_t m_bFromSaveGame;
    int32_t m_bFromTURD;
    uint32_t m_nPlayerListIndex;
    int32_t m_bPlayModuleListingCharacters;
    /*CNWSPlayerJournalQuest*/int *m_pJournalQuest;
    /*CNWSPlayerStoreGUI*/int *m_pStoreGUI;
    /*CNWSPlayerCharSheetGUI*/int *m_pCharSheetGUI;
    /*CNWSPlayerInventoryGUI*/int *m_pInventoryGUI;
    /*CNWSPlayerInventoryGUI*/int *m_pOtherInventoryGUI;
    /*CNWSPlayerLastUpdateObject*/int *m_pPlayerLUO;
    int32_t m_bAlwaysRun;
    uint8_t m_nCharacterType;
    CResRef m_resFileName;
    int32_t m_bCommunityNameAuthorized;
    int32_t m_bModuleInfoSucceeded;
    uint32_t m_nIFOCharacterIndex;
    int32_t m_bCutsceneState;

	int						SetGameObject( CNWSObject * obj );
	int 					AddArea(uint32_t areaid);
	CGenericObject* 		GetGameObject();
	int 					HasExpansionPack(unsigned char a2, int a3);
	void					vec_dtor(char Flag);
	CLastUpdateObject*		GetLastUpdateObject( );
	CExoString*				GetPlayerName(CExoString *str);
};

#endif