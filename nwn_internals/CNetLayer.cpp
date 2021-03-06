#include "stdafx.h"
#include "types.h"
#include "nwn_internals.h"


void	(__thiscall *CNetLayer__SetConnectionsDisallowed)(CNetLayer *pThis, int bDisAllowConnections) = (void (__thiscall*)(CNetLayer *pThis, int bDisAllowConnections))0x0041F890;
int 	(__thiscall *CNetLayer__SetGameMasterPassword)(CNetLayer *pThis, CExoString dm_pwd) = (int (__thiscall*)(CNetLayer *pThis, CExoString dm_pwd))0x0041F380;
int		(__thiscall *CNetLayer__DisconnectPlayer)(CNetLayer *pThis, unsigned long PlayerID, unsigned long tlkEntry, int a3) = (int (__thiscall*)(CNetLayer *pThis, unsigned long PlayerID, unsigned long tlkEntry, int a3))0x0041F490;

void  CNetLayer_s::SetConnectionsDisallowed(int bDisAllowConnections) {
	CNetLayer__SetConnectionsDisallowed(this, bDisAllowConnections);
}

int  CNetLayer_s::SetGameMasterPassword(CExoString dm_pwd) {
	return CNetLayer__SetGameMasterPassword(this, dm_pwd);
}

int CNetLayer_s::DisconnectPlayer(unsigned long PlayerID, unsigned long tlkEntry, int a3) {
	return CNetLayer__DisconnectPlayer(this, PlayerID, tlkEntry, a3);
}