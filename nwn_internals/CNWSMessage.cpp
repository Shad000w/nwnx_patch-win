#include "types.h"
#include "nwn_internals.h"

int 		(__thiscall *CNWSMessage__SendServerToPlayerGuiQuickbar_SetButton)(CNWSMessage*, CNWSPlayer*, uint8_t, int32_t) = (int (__thiscall *)(CNWSMessage*, CNWSPlayer *, uint8_t, int32_t))0x044E950; 
int			(__thiscall *CNWSMessage__SendServerToPlayerGameObjUpdate)(CNWSMessage*, CNWSPlayer *) = (int (__thiscall *)(CNWSMessage*, CNWSPlayer *))0x00440110;
void		(__thiscall *CNWSMessage__WriteGameObjUpdate_UpdateObject)(CNWSMessage*, CNWSPlayer*, CNWSObject*, CLastUpdateObject*, uint32_t, uint32_t) = (void (__thiscall *)(CNWSMessage*, CNWSPlayer*, CNWSObject*, CLastUpdateObject*, uint32_t, uint32_t))0x00445160;
void		(__thiscall *CNWSMessage__WriteGameObjUpdate_UpdateAppearance)(CNWSMessage*, CNWSObject*, CLastUpdateObject*, uint32_t) = (void (__thiscall *)(CNWSMessage*, CNWSObject*, CLastUpdateObject*, uint32_t))0x0043E9C0;
nwn_objid_t	(__thiscall *CNWSMessage__ReadOBJECTIDServer)(CNWSMessage *pThis) = (nwn_objid_t (__thiscall*)(CNWSMessage *pThis))0x00508C80;
int			(__thiscall *CNWSMessage__SendServerToPlayerMessage)(CNWSMessage*, nwn_objid_t Receiver, uint8_t a2, uint8_t Channel, void *pMessagedata, nwn_objid_t Sender) = (int (__thiscall *)(CNWSMessage*, nwn_objid_t Receiver, uint8_t a2, uint8_t Channel, void *pMessagedata, nwn_objid_t Sender))0x00449F40;
int 		(__thiscall *CNWSMessage__SendServerToPlayerArea_VisualEffect)(CNWSMessage *pThis, CNWSPlayer* plyer, int VFX_number, float Px, float Py, float Pz) = (int (__thiscall*)(CNWSMessage *pThis, CNWSPlayer* plyer, int VFX_number, float Px, float Py, float Pz))0x0043A2B0;
int 		(__thiscall *CNWSMessage__SendServerToPlayerDungeonMasterAreaList)(CNWSMessage *pThis, CNWSPlayer *Player) = (int (__thiscall*)(CNWSMessage *pThis, CNWSPlayer *Player))0x00448700;

int 		(__thiscall *CNWSMessage__SendServerToPlayerChat_DM_Talk)(CNWSMessage *pThis, uint32_t Receiver, nwn_objid_t Sender, CExoString Msg) = (int (__thiscall*)(CNWSMessage *pThis, uint32_t Receiver, nwn_objid_t Sender, CExoString Msg))0x0043DA80;
int 		(__thiscall *CNWSMessage__SendServerToPlayerChat_DM_Whisper)(CNWSMessage *pThis, uint32_t Receiver, nwn_objid_t Sender, CExoString Msg) = (int (__thiscall*)(CNWSMessage *pThis, uint32_t Receiver, nwn_objid_t Sender, CExoString Msg))0x0043E7D0;
int 		(__thiscall *CNWSMessage__SendServerToPlayerChat_ServerTell)(CNWSMessage *pThis, uint32_t Receiver, CExoString Msg) = (int (__thiscall*)(CNWSMessage *pThis, uint32_t Receiver, CExoString Msg))0x0043DEA0;
int 		(__thiscall *CNWSMessage__SendServerToPlayerChat_Party)(CNWSMessage *pThis, uint32_t Receiver, nwn_objid_t Sender, CExoString Msg) = (int (__thiscall*)(CNWSMessage *pThis, uint32_t Receiver, nwn_objid_t Sender, CExoString Msg))0x0043D790;
int 		(__thiscall *CNWSMessage__SendServerToPlayerChat_Shout)(CNWSMessage *pThis, uint32_t Receiver, nwn_objid_t Sender, CExoString Msg) = (int (__thiscall*)(CNWSMessage *pThis, uint32_t Receiver, nwn_objid_t Sender, CExoString Msg))0x0043DF80;
int 		(__thiscall *CNWSMessage__SendServerToPlayerChat_Silent_Shout)(CNWSMessage *pThis, uint32_t Receiver, nwn_objid_t Sender, CExoString Msg) = (int (__thiscall*)(CNWSMessage *pThis, uint32_t Receiver, nwn_objid_t Sender, CExoString Msg))0x0043E230;
int 		(__thiscall *CNWSMessage__SendServerToPlayerChat_Talk)(CNWSMessage *pThis, uint32_t Receiver, nwn_objid_t Sender, CExoString Msg) = (int(__thiscall*)(CNWSMessage *pThis, uint32_t Receiver, nwn_objid_t Sender, CExoString Msg))0x0043D9A0;
int 		(__thiscall *CNWSMessage__SendServerToPlayerChat_Tell)(CNWSMessage *pThis, uint32_t Receiver, nwn_objid_t Sender, CExoString Msg) = (int (__thiscall*)(CNWSMessage *pThis, uint32_t Receiver, nwn_objid_t Sender, CExoString Msg))0x0043DC90;
int 		(__thiscall *CNWSMessage__SendServerToPlayerChat_Whisper)(CNWSMessage *pThis, uint32_t Receiver, uint32_t Sender, CExoString Msg) = (int(__thiscall*)(CNWSMessage *pThis, uint32_t Receiver, uint32_t Sender, CExoString Msg))0x0043E4E0;

int 		(__thiscall *CNWSMessage__SendServerToPlayerChatMessage)(CNWSMessage *pThis, uint8_t Channel, nwn_objid_t Sender, CExoString Msg, uint32_t player_id) = (int (__thiscall*)(CNWSMessage *pThis, uint8_t Channel, nwn_objid_t Sender, CExoString Msg, uint32_t player_id))0x0043CA00;
void		(__thiscall *CNWSMessage__WriteGameObjUpdate_CharacterSheet)(CNWSMessage *pThis, CNWSPlayer *player, uint32_t a3) = (void (__thiscall*)(CNWSMessage *pThis, CNWSPlayer *player, uint32_t a3))0x00447B10;
int			(__thiscall *CNWSMessage__SendServerToPlayerPVP_Attitude_Change)(CNWSMessage *pThis, int oidPlayer1, int oidPlayer2, int a4) = (int(__thiscall*)(CNWSMessage *pThis, int oidPlayer1, int oidPlayer2, int a4))0x00450630;
int 		(__thiscall *CNWSMessage__SendServerToPlayerCCMessage)(CNWSMessage *pThis, unsigned long a1, unsigned char a2, CNWCCMessageData *mData, CNWSCombatAttackData *CombatAttackData) = (int(__thiscall*)(CNWSMessage *pThis, unsigned long a1, unsigned char a2, CNWCCMessageData *mData, CNWSCombatAttackData *CombatAttackData))0x0044B630;

int 		(__thiscall *CNWSMessage__SendServerToPlayerArea_ClientArea)(CNWSMessage *pThis, CNWSPlayer_s *Player, CNWSArea *Area, Vector Pos, Vector *Rot, int a8) = (int(__thiscall*)(CNWSMessage *pThis, CNWSPlayer_s *Player, CNWSArea *Area, Vector Pos, Vector *Rot, int a8))0x00439EB0;
int 		(__thiscall *CNWSMessage__SendServerToPlayerModule_Info)(CNWSMessage *pThis, uint32_t PlayerID) = (int(__thiscall*)(CNWSMessage *pThis, uint32_t PlayerID))0x00449FF0;
int			(__thiscall *CNWSMessage__SendServerToPlayerPolymorph)(CNWSMessage *pThis, CNWSPlayer *Player, unsigned long l, int i, int i2) = (int(__thiscall*)(CNWSMessage *pThis, CNWSPlayer *Player, unsigned long l, int i, int i2))0x004515B0;
int			(__thiscall *CNWSMessage__SendServerToPlayerInventory_UnequipCancel)(CNWSMessage *pThis, unsigned long l, unsigned long l2, int i) = (int(__thiscall*)(CNWSMessage *pThis, unsigned long l, unsigned long l2, int i))0x449E30;
int			(__thiscall *CNWSMessage__SendServerToPlayerPlayerList_All)(CNWSMessage *pTHIS, CNWSPlayer *player) = (int (__thiscall*)(CNWSMessage *pTHIS, CNWSPlayer *player))0x0044A4C0;

int CNWSMessage_s::SendServerToPlayerPlayerList_All(CNWSPlayer *player){
	return CNWSMessage__SendServerToPlayerPlayerList_All(this, player);
}

nwn_objid_t CNWSMessage_s::ReadOBJECTIDServer() {
	return CNWSMessage__ReadOBJECTIDServer(this);
}

void CNWSMessage_s::WriteGameObjUpdate_CharacterSheet(CNWSPlayer* player, uint32_t a3) {
	CNWSMessage__WriteGameObjUpdate_CharacterSheet(this, player, a3);
}

int CNWSMessage_s::SendServerToPlayerArea_VisualEffect(CNWSPlayer* player, int VFX_number, float Px, float Py, float Pz) {
	return CNWSMessage__SendServerToPlayerArea_VisualEffect(this, player, VFX_number, Px, Py, Pz);
}

int CNWSMessage_s::SendServerToPlayerChat_Party(uint32_t Receiver, nwn_objid_t Sender, CExoString Msg) {
	return CNWSMessage__SendServerToPlayerChat_Party(this, Receiver, Sender, Msg);
}

int CNWSMessage_s::SendServerToPlayerChat_ServerTell(uint32_t Receiver_id, CExoString Msg) {
	return CNWSMessage__SendServerToPlayerChat_ServerTell(this, Receiver_id, Msg);
}

int CNWSMessage_s::SendServerToPlayerChat_Shout(uint32_t Receiver, nwn_objid_t Sender, CExoString Msg) {
	return CNWSMessage__SendServerToPlayerChat_Shout(this, Receiver, Sender, Msg);
}

int CNWSMessage_s::SendServerToPlayerChat_Silent_Shout(uint32_t Receiver, nwn_objid_t Sender, CExoString Msg) {
	return CNWSMessage__SendServerToPlayerChat_Silent_Shout(this, Receiver, Sender, Msg);
}

int CNWSMessage_s::SendServerToPlayerChat_Tell(uint32_t Receiver, nwn_objid_t Sender, CExoString Msg) {
	return CNWSMessage__SendServerToPlayerChat_Tell(this, Receiver, Sender, Msg);
}

int CNWSMessage_s::SendServerToPlayerChatMessage(uint8_t Channel, nwn_objid_t Sender, CExoString Msg, uint32_t player_id) {
	return CNWSMessage__SendServerToPlayerChatMessage(this, Channel, Sender, Msg, player_id);
}
 
int CNWSMessage_s::SendServerToPlayerDungeonMasterAreaList(CNWSPlayer *Player) {
	return CNWSMessage__SendServerToPlayerDungeonMasterAreaList(this, Player);
}

int CNWSMessage_s::SendServerToPlayerGameObjUpdate(CNWSPlayer *Player) {
	return CNWSMessage__SendServerToPlayerGameObjUpdate(this, Player);
}

int CNWSMessage_s::SendServerToPlayerGuiQuickbar_SetButton(CNWSPlayer* Player, uint8_t a2, int32_t a3) {
	return CNWSMessage__SendServerToPlayerGuiQuickbar_SetButton(this, Player, a2, a3);
}

int CNWSMessage_s::SendServerToPlayerMessage(nwn_objid_t Receiver, uint8_t a2, uint8_t Channel, void *pMessagedata, uint32_t MessageLength) {
return CNWSMessage__SendServerToPlayerMessage(this, Receiver, a2, Channel, pMessagedata, MessageLength);
}

void CNWSMessage_s::WriteGameObjUpdate_UpdateAppearance(CNWSObject* a1, CLastUpdateObject* a2, uint32_t a3) {
	CNWSMessage__WriteGameObjUpdate_UpdateAppearance(this, a1, a2, a3);
}

void CNWSMessage_s::WriteGameObjUpdate_UpdateObject(CNWSPlayer* a1, CNWSObject* a2, CLastUpdateObject* a3, uint32_t a4, uint32_t a5) {
	CNWSMessage__WriteGameObjUpdate_UpdateObject(this, a1, a2, a3, a4, a5);
}

int CNWSMessage_s::SendServerToPlayerPVP_Attitude_Change(int oidPlayer1, int oidPlayer2, int a4) {
	return CNWSMessage__SendServerToPlayerPVP_Attitude_Change(this, oidPlayer1, oidPlayer2, a4);
}

int CNWSMessage_s::SendServerToPlayerCCMessage(unsigned long a1, unsigned char a2, CNWCCMessageData *mData, CNWSCombatAttackData *CombatAttackData) {
	return CNWSMessage__SendServerToPlayerCCMessage(this, a1, a2, mData, CombatAttackData);
}

int CNWSMessage_s::SendServerToPlayerChat_Talk(uint32_t Receiver, nwn_objid_t Sender, CExoString Msg) {
	return CNWSMessage__SendServerToPlayerChat_Talk(this, Receiver, Sender, Msg);
}


int CNWSMessage_s::SendServerToPlayerChat_DM_Talk(uint32_t Receiver, nwn_objid_t Sender, CExoString Msg) {
	return CNWSMessage__SendServerToPlayerChat_DM_Talk(this, Receiver, Sender, Msg);
}

int CNWSMessage_s::SendServerToPlayerChat_DM_Whisper(uint32_t Receiver, nwn_objid_t Sender, CExoString Msg) {
	return CNWSMessage__SendServerToPlayerChat_DM_Whisper(this, Receiver, Sender, Msg);
}

int CNWSMessage_s::SendServerToPlayerChat_Whisper(uint32_t Receiver, nwn_objid_t Sender, CExoString Msg) {
	return CNWSMessage__SendServerToPlayerChat_Whisper(this, Receiver, Sender, Msg);
}

int CNWSMessage_s::SendServerToPlayerArea_ClientArea(CNWSPlayer_s *Player, CNWSArea *Area, Vector Pos, Vector *Rot, int a8) {
	return CNWSMessage__SendServerToPlayerArea_ClientArea(this, Player, Area, Pos, Rot, a8);
}

int CNWSMessage_s::SendServerToPlayerModule_Info(uint32_t PlayerID) {
	return CNWSMessage__SendServerToPlayerModule_Info(this, PlayerID);
}

int CNWSMessage_s::SendServerToPlayerPolymorph(CNWSPlayer_s *pThis, unsigned long l, int i, int i2)
{
	return CNWSMessage__SendServerToPlayerPolymorph(this,pThis,l,i,i2);
}

int CNWSMessage_s::SendServerToPlayerInventory_UnequipCancel(unsigned long l, unsigned long l2, int i)
{
	return CNWSMessage__SendServerToPlayerInventory_UnequipCancel(this,l,l2,i);
}