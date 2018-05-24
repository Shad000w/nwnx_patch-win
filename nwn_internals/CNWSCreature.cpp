#include "types.h"
#include "nwn_internals.h"

DWORD CNWSCreature__SummonAssociate = 0x4CC6D0;
DWORD CNWSCreature__GetFamiliarName = 0x4CC640;
DWORD CNWSCreature__GetAnimalCompanionName = 0x4CC360;


__declspec( naked ) void CNWSCreature_s::SummonAssociate(CResRef resref, char*name, unsigned long len, unsigned short type){__asm{ jmp dword ptr [CNWSCreature__SummonAssociate] }}
__declspec( naked ) CExoString CNWSCreature_s::GetFamiliarName(){__asm{ jmp dword ptr [CNWSCreature__GetFamiliarName] }}
__declspec( naked ) CExoString CNWSCreature_s::GetAnimalCompanionName(){__asm{ jmp dword ptr [CNWSCreature__GetAnimalCompanionName] }}

int					(__thiscall *CNWSCreature__AddAttackActions)(CNWSCreature*, unsigned long, int, int, int) = (int(__thiscall*)(CNWSCreature*, unsigned long, int, int, int))0x493810;
void				(__thiscall *CNWSCreature__ActivityManager)(CNWSCreature *pThis, unsigned long Activity) = (void(__thiscall*)(CNWSCreature *pThis, unsigned long Activity))0x00490630;
unsigned char		(__thiscall *CNWSCreature__CanEquipItem)(CNWSCreature *, CNWSItem *, unsigned long *, int, int, int, CNWSPlayer *) = (unsigned char(__thiscall*)(CNWSCreature *, CNWSItem *, unsigned long *, int, int, int, CNWSPlayer *))0x4C0110;
signed int 			(__thiscall *CNWSCreature__AcquireItem)(CNWSCreature *pThis, CNWSItem **Item, nwn_objid_t From_oID, nwn_objid_t a4, char a5, char a6, int a7, int a8) = (signed int (__thiscall*)(CNWSCreature *pThis, CNWSItem **Item, nwn_objid_t From_oID, nwn_objid_t a4, char a5, char a6, int a7, int a8))0x004C0580;
int					(__thiscall *CNWSCreature__EquipItem)(CNWSCreature *, unsigned long, CNWSItem *, int, int) = (int (__thiscall*)(CNWSCreature *, unsigned long, CNWSItem *, int, int))0x4961E0;
int					(__thiscall *CNWSCreature__UnequipItem)(CNWSCreature *, CNWSItem *, int) = (int (__thiscall*)(CNWSCreature *, CNWSItem *, int))0x496330;
int 				(__thiscall *CNWSCreature__ApplyDiseasePayload)(CNWSCreature *pThis, CGameEffect *eff, unsigned long a3, unsigned long a4) = (int(__thiscall*)(CNWSCreature *pThis, CGameEffect *eff, unsigned long a3, unsigned long a4))0x004B0170;
int 				(__thiscall *CNWSCreature__ApplyPoisonPayload)(CNWSCreature *pThis, CGameEffect *eff, unsigned long t1, unsigned long t2) = (int(__thiscall*)(CNWSCreature *pThis, CGameEffect *eff, unsigned long t1, unsigned long t2))0x004B0770;
void				(__thiscall *CNWSCreature__CancelRest)(CNWSCreature *pThis, unsigned short a1) = (void(__thiscall*)(CNWSCreature *pThis, unsigned short a1))0x004A6840;
__int16 			(__thiscall *CNWSCreature__GetArmorClass)(CNWSCreature *pThis) = (__int16 (__thiscall*)(CNWSCreature *pThis))0x004A6E00;
int 				(__thiscall *CNWSCreature__GetRelativeWeaponSize)(CNWSCreature *pThis, CNWSItem *weapon) = (int (__thiscall*)(CNWSCreature *pThis, CNWSItem *weapon))0x004A6D00;
int 				(__thiscall *CNWSCreature__GetWeaponPower)(CNWSCreature *pThis, CNWSItem *weapon, int n) = (int (__thiscall*)(CNWSCreature *pThis, CNWSItem *weapon, int n))0x004AA8A0;
int 				(__thiscall *CNWSCreature__GetTotalEffectBonus)(CNWSCreature *pThis, char a2, CNWSObject *obj_a, int a4, int a5, unsigned __int8 a6, unsigned __int8 a7, unsigned __int8 a8, unsigned __int8 a9, int a10) = (int (__thiscall*)(CNWSCreature *pThis, char a2, CNWSObject *obj_a, int a4, int a5, unsigned __int8 a6, unsigned __int8 a7, unsigned __int8 a8, unsigned __int8 a9, int a10))0x004AB140;
int 				(__thiscall *CNWSCreature__GetBlind)(CNWSCreature *Cre) = (int (__thiscall*)(CNWSCreature *Cre))0x004AEB40;
CNWSFaction * 		(__thiscall *CNWSCreature__GetFaction)(CNWSCreature *pThis) = (CNWSFaction*(__thiscall*)(CNWSCreature *pThis))0x004C7770;
bool 				(__thiscall *CNWSCreature__GetFlanked)(CNWSCreature *pThis, CNWSCreature *Target) = (bool (__thiscall*)(CNWSCreature *pThis, CNWSCreature *Target))0x00551250;
int 				(__thiscall *CNWSCreature__GetFlatFooted)(CNWSCreature *pThis) = (int (__thiscall*)(CNWSCreature *pThis))0x00551170;
int 				(__thiscall *CNWSCreature__GetInvisible)(CNWSCreature *pThis, CNWSObject* obj, int i) = (int (__thiscall*)(CNWSCreature *pThis, CNWSObject* obj, int i))0x004AEB60;
int16_t				(__thiscall *CNWSCreature__GetMaxHitPoints)(CNWSCreature *pThis, int a1) = (int16_t(__thiscall*)(CNWSCreature *pThis, int a1))0x004A6ED0;
nwn_objid_t			(__thiscall *CNWSCreature__GetNearestEnemy)(CNWSCreature *pThis, float fDistance, unsigned long a2, int a3, int a4) = (nwn_objid_t(__thiscall*)(CNWSCreature *pThis, float fDistance, unsigned long a2, int a3, int a4))0x004A5570;
int 				(__thiscall *CNWSCreature__GetRangeWeaponEquipped)(CNWSCreature *pThis) = (int (__thiscall*)(CNWSCreature *pThis))0x00496460;
int 				(__thiscall *CNWSCreature__GetUseMonkAbilities)(CNWSCreature *pThis) = (int (__thiscall*)(CNWSCreature *pThis))0x0049E370;
CNWVisibilityNode * (__thiscall *CNWSCreature__GetVisibleListElement)(CNWSCreature *pThis, unsigned long ul) = (CNWVisibilityNode * (__thiscall*)(CNWSCreature *pThis, unsigned long ul))0x004C7FF0;
float 				(__thiscall *CNWSCreature__MaxAttackRange)(CNWSCreature *pThis, nwn_objid_t, int, int) = (float (__thiscall*)(CNWSCreature *pThis, nwn_objid_t, int, int))0x00498090;
void 				(__thiscall *CNWSCreature__NotifyAssociateActionToggle)(CNWSCreature *pThis, int Action) = (void(__thiscall*)(CNWSCreature *pThis, int Action))0x004B2A70;
void 				(__thiscall *CNWSCreature__PossessCreature)(CNWSCreature *pThis, nwn_objid_t oidPossessee) = (void (__thiscall*)(CNWSCreature *pThis, nwn_objid_t oidPossessee))0x004CD1B0;
void 				(__thiscall *CNWSCreature__PossessFamiliar)(CNWSCreature *) = (void (__thiscall*)(CNWSCreature *))0x4CCAC0;
void 				(__thiscall *CNWSCreature__PostProcess)(CNWSCreature *pThis) = (void (__thiscall*)(CNWSCreature *pThis))0x0049E450;
void 				(__thiscall *CNWSCreature__ReceiveAssociateCommand)(CNWSCreature *pThis, int a1) = (void(__thiscall*)(CNWSCreature *pThis, int a1))0x004CBC60;
void				(__thiscall *CNWSCreature__RemoveBadEffects)(CNWSCreature *pThis) = (void(__thiscall*)(CNWSCreature *pThis))0x004A6C20;
void				(__thiscall *CNWSCreature__RemoveFromArea)(CNWSCreature*, int AreaID) = (void (__thiscall *)(CNWSCreature*, int AreaID))0x004964C0;
signed int 			(__thiscall *CNWSCreature__RemoveItem)(CNWSCreature *pThis, CNWSItem *a2, int a3, int bSendFeedBack, int a5, int a6) = (signed int (__thiscall*)(CNWSCreature *pThis, CNWSItem *a2, int a3, int bSendFeedBack, int a5, int a6))0x004C0830;
int		 			(__thiscall *CNWSCreature__RemoveItemFromRepository)(CNWSCreature *, CNWSItem *, int) = (int (__thiscall*)(CNWSCreature *, CNWSItem *, int))0x4B2870;
void				(__thiscall *CNWSCreature__ResolveAttack)(CNWSCreature *pThis, int a2_target_oid, signed int a3, int a4) = (void (__thiscall*)(CNWSCreature *pThis, int a2_target_oid, signed int a3, int a4))0x00547580;
int					(__thiscall *CNWSCreature__ResolveRangedAttack)(CNWSCreature *Attacker_this, CNWSObject *Defender_a2, int nAttacks_a3, int a4) = (int (__thiscall*)(CNWSCreature *Attacker_this, CNWSObject *Defender_a2, int nAttacks_a3, int a4))0x00547880;
int					(__thiscall *CNWSCreature__ResolveInitiative)(CNWSCreature *pThis) = (int (__thiscall*)(CNWSCreature *pThis))0x4A2440;
void*				(__thiscall *CNWSCreature__Rest)(CNWSCreature *pThis, int a2, int bCreatureToEnemyLineOfSightCheck) = (void*(__thiscall*)(CNWSCreature *pThis, int a2, int bCreatureToEnemyLineOfSightCheck))0x004A65C0;
void				(__thiscall *CNWSCreature__RestoreItemProperties)(CNWSCreature *pThis) = (void(__thiscall*)(CNWSCreature *pThis))0x004A4F20;
void 				(__thiscall *CNWSCreature__SendFeedbackMessage)(CNWSCreature *pThis, unsigned short, CNWCCMessageData*, CNWSPlayer *) = (void (__thiscall*)(CNWSCreature *pThis, unsigned short, CNWCCMessageData*, CNWSPlayer *))0x004AD4D0;
void 				(__thiscall *CNWSCreature__SetActivity)(CNWSCreature *pThis, int Activity, int bOn) = (void(__thiscall*)(CNWSCreature *pThis, int Activity, int bOn))0x00490690;
void				(__thiscall *CNWSCreature__SetAnimation)(CNWSCreature *pThis, int nAnim) = (void(__thiscall*)(CNWSCreature *pThis, int nAnim))0x004960C0;
void 				(__thiscall *CNWSCreature__SetCombatMode)(CNWSCreature *pThis, unsigned char Mode, int bOn) = (void(__thiscall*)(CNWSCreature *pThis, unsigned char Mode, int bOn))0x004BB4D0;
void				(__thiscall *CNWSCreature__SetQuickbarButton_Item)(CNWSCreature*, uint8_t, uint32_t, int, uint32_t) = (void (__thiscall *)(CNWSCreature*, uint8_t, uint32_t, int, uint32_t))0x004A8D20;
void				(__thiscall *CNWSCreature__SetQuickbarButton_Spell)(CNWSCreature*, uint8_t, uint8_t, uint32_t, uint8_t, uint8_t) = (void (__thiscall *)(CNWSCreature*, uint8_t, uint8_t, uint32_t, uint8_t, uint8_t))0x004A8D70;
void				(__thiscall *CNWSCreature__SetQuickbarButton_SpellLikeAbility)(CNWSCreature*, uint8_t, uint32_t, uint8_t) = (void (__thiscall *)(CNWSCreature*, uint8_t, uint32_t, uint8_t))0x004A8DD0;
void *				(__thiscall *CNWSCreature__SetScriptName)(CNWSCreature *pThis, signed int iScript, CExoString ScriptName) = (void* (__thiscall*)(CNWSCreature *pThis, signed int iScript, CExoString ScriptName))0x0049F8D0;
void				(__thiscall *CNWSCreature__StartGuiTimingBar)(CNWSCreature*, unsigned long, unsigned char) = (void (__thiscall *)(CNWSCreature*, unsigned long, unsigned char))0x004B1A90;
void				(__thiscall *CNWSCreature__StopGuiTimingBar)(CNWSCreature*) = (void (__thiscall *)(CNWSCreature*))0x004B1AF0;
int 				(__thiscall *CNWSCreature__ToggleMode)(CNWSCreature* pThis, unsigned char Mode) = (int (__thiscall*)(CNWSCreature* pThis, unsigned char Mode))0x004A5080;
void 				(__thiscall *CNWSCreature__UnpossessCreature)(CNWSCreature *pThis) = (void(__thiscall*)(CNWSCreature *pThis))0x004CD450;
void 				(__thiscall *CNWSCreature__UnpossessFamiliar)(CNWSCreature *) = (void(__thiscall*)(CNWSCreature *))0x4CCD60;
void 				(__thiscall *CNWSCreature__UpdateAutoMap)(CNWSCreature* pThis, uint32_t areaid) = (void (__thiscall*)(CNWSCreature* pThis, uint32_t areaid))0x00494C50;
void 				(__thiscall *CNWSCreature__UpdateEncumbranceState)(CNWSCreature *pThis, int bFeedback) = (void (__thiscall*)(CNWSCreature *pThis, int bFeedback))0x004CFC70;
void 				(__thiscall *CNWSCreature__UpdateEffectPointers)(CNWSCreature *pThis) = (void (__thiscall*)(CNWSCreature *pThis))0x4986C0;
void				(__thiscall *CNWSCreature__SetAutoMapData)(CNWSCreature *pThis, int a2, int a3, int a4) = (void(__thiscall*)(CNWSCreature *pThis, int a2, int a3, int a4))0x004B1DD0;
void 				(__thiscall *CNWSCreature__SetPVPPlayerLikesMe)(CNWSCreature *pThis, unsigned long oid_Player2, int a3, int a4) = (void(__thiscall*)(CNWSCreature *pThis, unsigned long oid_Player2, int a3, int a4))0x004D0450;
CNWSCreature*		(__thiscall *CNWSCreature__CNWSCreature)(CNWSCreature *pThis, int a2, unsigned int a3, unsigned int a4) = (CNWSCreature*(__thiscall*)(CNWSCreature *pThis, int a2, unsigned int a3, unsigned int a4))0x0048F5B0;
void				(__thiscall *CNWSCreature___CNWSCreature)(CNWSCreature *pThis) = (void(__thiscall*)(CNWSCreature *pThis))0x00490000;
int				    (__thiscall *CNWSCreature__HasFeat)(CNWSCreature*, unsigned short nFeat) = (int (__thiscall *)(CNWSCreature*, unsigned short))0x0047ECF0;
bool				(__thiscall *CNWSCreature__GetMode)(CNWSCreature*, unsigned char nFeat) = (bool (__thiscall *)(CNWSCreature*, unsigned char))0x004A53C0;
void 				(__thiscall *CNWSCreature__UpdateAppearanceDependantInfo)(CNWSCreature *pThis) = (void (__thiscall *)(CNWSCreature* pThis))0x004A83F0;
void 				(__thiscall *CNWSCreature__UpdateAppearanceForEquippedItems)(CNWSCreature *pThis) = (void (__thiscall *)(CNWSCreature* pThis))0x004A7A90;
void				(__thiscall *CNWSCreature__AddAssociate)(CNWSCreature * pThis, nwn_objid_t oID, unsigned short nType) = (void (__thiscall *)(CNWSCreature * pThis, nwn_objid_t oID, unsigned short nType))0x004CB430;
void				(__thiscall *CNWSCreature__AddToAssociateList)(CNWSCreature * pThis, nwn_objid_t oID) = (void (__thiscall *)(CNWSCreature * pThis, nwn_objid_t oID))0x004CB2A0;
void				(__thiscall *CNWSCreature__RemoveToAssociateList)(CNWSCreature * pThis, nwn_objid_t oID) = (void (__thiscall *)(CNWSCreature * pThis, nwn_objid_t oID))0x004CB7F0;
int					(__thiscall *CNWSCreature__ReprocessAssociateList)(CNWSCreature * pThis) = (int (__thiscall *)(CNWSCreature * pThis))0x004CB390;
void				(__thiscall *CNWSCreature__UpdatePersonalSpace)(CNWSCreature * pThis) = (void (__thiscall *)(CNWSCreature * pThis))0x004A81D0;
CNWSCreatureStats*	(__thiscall *CNWSCreature__GetStats)(CNWSCreature *pThis) = (CNWSCreatureStats*(__thiscall*)(CNWSCreature *pThis))0x00436A70;
void				(__thiscall *CNWSCreature__BroadcastAttackOfOpportunity) (CNWSCreature* pThis, unsigned long l, int nUnknown) = (void (__thiscall*)(CNWSCreature* pThis, unsigned long l, int nUnknown))0x004A27C0;
CNWSQuickbarButton*	(__thiscall *CNWSCreature__GetQuickbarButton)(CNWSCreature* pThis, unsigned char nTh) = (CNWSQuickbarButton*(__thiscall*)(CNWSCreature* pThis, unsigned char nTh))0x004B2A20;
int					(__thiscall *CNWSCreature__Polymorph)(CNWSCreature* pThis, int nPoly, CGameEffect *eff, int nLock) = (int(__thiscall*)(CNWSCreature* pThis, int nPoly, CGameEffect *eff, int nLock))0x004AD960;
int					(__thiscall *CNWSCreature__UnPolymorph)(CNWSCreature* pThis, CGameEffect *eff) = (int(__thiscall*)(CNWSCreature* pThis, CGameEffect *eff))0x4AE6C0;
int					(__thiscall *CNWSCreature__GetIsPossessedFamiliar)(CNWSCreature* pThis) = (int(__thiscall*)(CNWSCreature* pThis))0x4CE920;
int					(__thiscall *CNWSCreature__GetIsInUseRange)(CNWSCreature* pThis, int n1, float f, int n2) = (int(__thiscall*)(CNWSCreature* pThis, int n1, float f, int n2))0x4AF2B0;
int					(__thiscall *CNWSCreature__CanUseItem)(CNWSCreature *pThis, CNWSItem *item, int a1) = (int(__thiscall*)(CNWSCreature *pThis, CNWSItem *item, int a1))0x4CE950;

unsigned long (__thiscall *CNWSCreature__GetAssociateId)(CNWSCreature *pThis, unsigned short type, int nTh)=(unsigned long(__thiscall*)(CNWSCreature* pThis, unsigned short type, int nTh))0x4CDD80;
void				(__thiscall *CNWSCreature__SetEffectSpellId)(CNWSCreature * pThis, unsigned long ID) = (void (__thiscall *)(CNWSCreature * pThis, unsigned long ID))0x4A11F0;
float				(__thiscall *CNWSCreature__GetMovementRateFactor)(CNWSCreature *pThis)=(float(__thiscall*)(CNWSCreature*))0x49E180;
int					(__thiscall *CNWSCreature__SetMovementRateFactor)(CNWSCreature * pThis, float fSpeed) = (int (__thiscall *)(CNWSCreature *, float))0x49E2B0;

void				(__thiscall *CNWSCreature__ResolveAttackRoll)(CNWSCreature*, CNWSObject *) = (void (__thiscall*)(CNWSCreature*, CNWSObject *))0x54B790;
void				(__thiscall *CNWSCreature__ResolveDamage)(CNWSCreature*, CNWSObject *) = (void (__thiscall*)(CNWSCreature*, CNWSObject *))0x54CA70;
void				(__thiscall *CNWSCreature__ResolvePostMeleeDamage)(CNWSCreature*, CNWSObject *) = (void (__thiscall*)(CNWSCreature*, CNWSObject *))0x54D470;
void				(__thiscall *CNWSCreature__ResolvePostRangedDamage)(CNWSCreature*, CNWSObject *) = (void (__thiscall*)(CNWSCreature*, CNWSObject *))0x54DD80;
void				(__thiscall *CNWSCreature__ResolveMeleeAnimations)(CNWSCreature*, int, int, CNWSObject *, int) = (void (__thiscall*)(CNWSCreature*, int, int, CNWSObject *, int))0x54B0D0;
void				(__thiscall *CNWSCreature__ResolveRangedAnimations)(CNWSCreature*, CNWSObject *, int) = (void (__thiscall*)(CNWSCreature*, CNWSObject *, int))0x548860;

void CNWSCreature::ResolveAttackRoll(CNWSObject *obj)
{
	CNWSCreature__ResolveAttackRoll(this, obj);
}
void CNWSCreature::ResolveDamage(CNWSObject *obj)
{
	CNWSCreature__ResolveDamage(this, obj);
}
void CNWSCreature::ResolvePostMeleeDamage(CNWSObject *obj)
{
	CNWSCreature__ResolvePostMeleeDamage(this, obj);
}
void CNWSCreature::ResolvePostRangedDamage(CNWSObject *obj)
{
	CNWSCreature__ResolvePostRangedDamage(this, obj);
}
void CNWSCreature::ResolveMeleeAnimations(int a1, int a2, CNWSObject *obj, int a4)
{
	CNWSCreature__ResolveMeleeAnimations(this, a1,a2,obj,a4);
}
void CNWSCreature::ResolveRangedAnimations(CNWSObject *obj, int a1)
{
	CNWSCreature__ResolveRangedAnimations(this,obj,a1);
}

//void Destructor(char c) {
	//CNWSCreature__dtor_CNWSCreature(this, c);
//}
CNWSCreatureStats *CNWSCreature_s::GetStats(){
	return CNWSCreature__GetStats(this);
}

void CNWSCreature_s::UpdatePersonalSpace( ){
	CNWSCreature__UpdatePersonalSpace( this );
}

void CNWSCreature_s::RemoveToAssociateList( nwn_objid_t oID ){
	CNWSCreature__RemoveToAssociateList( this, oID );
}

int CNWSCreature_s::ReprocessAssociateList(  ){
	return CNWSCreature__ReprocessAssociateList( this );
}

void CNWSCreature_s::AddToAssociateList( nwn_objid_t oID ){
	CNWSCreature__AddToAssociateList( this, oID );
}

void CNWSCreature_s::AddAssociate( nwn_objid_t oID, unsigned short nType ){
	CNWSCreature__AddAssociate( this, oID, nType );
}

void CNWSCreature_s::UpdateAppearanceDependantInfo( ) {
	CNWSCreature__UpdateAppearanceDependantInfo(this);
}

void CNWSCreature_s::UpdateAppearanceForEquippedItems( ) {
	CNWSCreature__UpdateAppearanceForEquippedItems(this);
}

void CNWSCreature_s::UpdateEffectPointers( ) {
	CNWSCreature__UpdateEffectPointers(this);
}

bool CNWSCreature_s::GetMode( unsigned char mode ) {
	return CNWSCreature__GetMode( this, mode );
}

int CNWSCreature_s::HasFeat(unsigned short nFeat) {
	return this->GetStats()->HasFeat(nFeat);//crashed otherwise
}

CNWSCreature_s::CNWSCreature_s(int a2, unsigned int a3, unsigned int a4) {
	CNWSCreature__CNWSCreature(this, a2, a3, a4);
}

CNWSCreature_s::~CNWSCreature_s() {
	CNWSCreature___CNWSCreature(this);
}

signed int CNWSCreature_s::AcquireItem(CNWSItem **Item, nwn_objid_t From_oID, nwn_objid_t a4, char a5, char a6, int a7, int bUpdateEncumbrance) {
	return CNWSCreature__AcquireItem(this, Item, From_oID, a4, a5, a6, a7, bUpdateEncumbrance);
}

int CNWSCreature::EquipItem(unsigned long slot, CNWSItem *item, int a1, int a2)
{
	return CNWSCreature__EquipItem(this,slot,item,a1,a2);
}

int CNWSCreature::UnequipItem(CNWSItem *item, int a1)
{
	return CNWSCreature__UnequipItem(this,item,a1);
}

int CNWSCreature_s::GetBlind() {
	return CNWSCreature__GetBlind(this);
}

bool CNWSCreature_s::GetFlanked(CNWSCreature *Target) {
	return CNWSCreature__GetFlanked(this, Target);
}

int CNWSCreature_s::GetFlatFooted() {
	return CNWSCreature__GetFlatFooted(this);
}

int CNWSCreature_s::GetInvisible(CNWSObject* obj, int i) {
	return CNWSCreature__GetInvisible(this, obj, i);
}

int CNWSCreature_s::GetRangeWeaponEquipped() {
	return CNWSCreature__GetRangeWeaponEquipped(this);
}

int CNWSCreature_s::GetRelativeWeaponSize(CNWSItem *weapon) {
	return CNWSCreature__GetRelativeWeaponSize(this, weapon);
}

int CNWSCreature_s::GetWeaponPower(CNWSItem *weapon, int n) {
	return CNWSCreature__GetWeaponPower(this, weapon, n);
}

int CNWSCreature_s::GetTotalEffectBonus(char a2, CNWSObject *obj_a, int a4, int a5, unsigned __int8 a6, unsigned __int8 a7, unsigned __int8 a8, unsigned __int8 a9, int a10) {
	return CNWSCreature__GetTotalEffectBonus(this, a2, obj_a, a4, a5,  a6, a7, a8, a9, a10);
}

CNWVisibilityNode *CNWSCreature_s::GetVisibleListElement(unsigned long ul) {
	return CNWSCreature__GetVisibleListElement(this, ul);
}

float CNWSCreature_s::MaxAttackRange(nwn_objid_t ID, int a, int b) {
	return CNWSCreature__MaxAttackRange(this, ID, a, b);
}

void CNWSCreature_s::PostProcess() {
	CNWSCreature__PostProcess(this);
}

void CNWSCreature_s::RemoveFromArea(int AreaID) {
	CNWSCreature__RemoveFromArea(this, AreaID);
}

signed int CNWSCreature_s::RemoveItem(CNWSItem *a2, int a3, int bSendFeedBack, int a5, int a6) {
	return CNWSCreature__RemoveItem(this, a2, a3, bSendFeedBack, a5, a6);
}

int CNWSCreature::RemoveItemFromRepository(CNWSItem *item, int a1) {
	return CNWSCreature__RemoveItemFromRepository(this, item,a1);
}

void CNWSCreature_s::ResolveAttack(int a2_target_oid, signed int a3, int a4) {
	CNWSCreature__ResolveAttack(this, a2_target_oid, a3, a4);
}

int CNWSCreature_s::ResolveRangedAttack(CNWSObject *Defender_a2, int nAttacks_a3, int a4) {
	return CNWSCreature__ResolveRangedAttack(this, Defender_a2, nAttacks_a3, a4);
}

void CNWSCreature_s::ResolveInitiative() {
	CNWSCreature__ResolveInitiative(this);
}

void CNWSCreature_s::SendFeedbackMessage(unsigned short a1, CNWCCMessageData* a2, CNWSPlayer *a3) {
	CNWSCreature__SendFeedbackMessage(this, a1, a2, a3);
}

void *CNWSCreature_s::SetScriptName(signed int iScript, CExoString ScriptName) {
	return CNWSCreature__SetScriptName(this, iScript, ScriptName);
}

void CNWSCreature_s::StartGuiTimingBar(unsigned long a, unsigned char b) {
	CNWSCreature__StartGuiTimingBar(this, a, b);
}

void CNWSCreature_s::StopGuiTimingBar() {
	CNWSCreature__StopGuiTimingBar(this);
}

void CNWSCreature_s::UpdateAutoMap(uint32_t areaid) {
	CNWSCreature__UpdateAutoMap(this, areaid);
}

void CNWSCreature_s::PossessCreature(nwn_objid_t oID) {
	CNWSCreature__PossessCreature(this, oID);
}

void CNWSCreature::PossessFamiliar(){
	CNWSCreature__PossessFamiliar(this);
}

int CNWSCreature_s::GetUseMonkAbilities() {
	return CNWSCreature__GetUseMonkAbilities(this);
}

void CNWSCreature_s::UpdateEncumbranceState(int bFeedback) {
	return CNWSCreature__UpdateEncumbranceState(this, bFeedback);
}

void CNWSCreature_s::SetAutoMapData(int a2, int a3, int a4) {
	CNWSCreature__SetAutoMapData(this, a2, a3, a4);
}

int CNWSCreature_s::GetIsInUseRange(int n1, float f, int n2) {
	return CNWSCreature__GetIsInUseRange(this, n1, f, n2);
}

void CNWSCreature_s::SetPVPPlayerLikesMe(unsigned long oid_Player2, int a3, int a4) {
	CNWSCreature__SetPVPPlayerLikesMe(this, oid_Player2, a3, a4);
}

int CNWSCreature_s::GetDamageFlags() {
	CNWSCombatRound *CRound = cre_combat_round;
	CNWSCombatAttackData *AttackData = CRound->GetAttack(CRound->CurrentAttack);
	CNWSItem *Weapon = CRound->GetCurrentAttackWeapon(AttackData->m_nWeaponAttackType);

	if (Weapon) {
		return Weapon->GetDamageFlags();
	}

	return 1;
}

void CNWSCreature_s::SetActivity(int Activity, int bOn) {
	CNWSCreature__SetActivity(this, Activity, bOn);
}

void CNWSCreature_s::SetCombatMode(int Mode, int bOn) {
	CNWSCreature__SetCombatMode(this, Mode, bOn);
}

int CNWSCreature_s::ToggleMode(unsigned char Mode) {
	return CNWSCreature__ToggleMode(this, Mode);
}

void CNWSCreature_s::BroadcastAttackOfOpportunity(unsigned long l, int nUnknown){
	return CNWSCreature__BroadcastAttackOfOpportunity(this,l,nUnknown);
}

void CNWSCreature_s::NotifyAssociateActionToggle(int Action) {
	CNWSCreature__NotifyAssociateActionToggle(this, Action);
}

int CNWSCreature_s::GetArmorClass() {
	return CNWSCreature__GetArmorClass(this);
}

int CNWSCreature_s::ApplyPoisonPayload(CGameEffect *eff, unsigned long t1, unsigned long t2) {
	return CNWSCreature__ApplyPoisonPayload(this, eff, t1, t2);
}

void *CNWSCreature_s::Rest(int a2, int bCreatureToEnemyLineOfSightCheck) {
	return CNWSCreature__Rest(this, a2, bCreatureToEnemyLineOfSightCheck);
}

void CNWSCreature_s::ReceiveAssociateCommand(int a1) {
	CNWSCreature__ReceiveAssociateCommand(this, a1);
}

void CNWSCreature_s::ActivityManager(unsigned long Activity) {
	CNWSCreature__ActivityManager(this, Activity);
}

void CNWSCreature_s::CancelRest(unsigned short a1) {
	CNWSCreature__CancelRest(this, a1);
}

void CNWSCreature_s::SetAnimation(int nAnim) {
	CNWSCreature__SetAnimation(this, nAnim);
}

nwn_objid_t CNWSCreature_s::GetNearestEnemy(float fDistance, unsigned long a2, int a3, int a4) {
	return CNWSCreature__GetNearestEnemy(this, fDistance, a2, a3, a4);
}

void CNWSCreature_s::RemoveBadEffects() {
	CNWSCreature__RemoveBadEffects(this);
}

int CNWSCreature_s::ApplyDiseasePayload(CGameEffect *eff, unsigned long a3, unsigned long a4) {
	return CNWSCreature__ApplyDiseasePayload(this, eff, a3, a4);
}

void CNWSCreature_s::RestoreItemProperties() {
	CNWSCreature__RestoreItemProperties(this);
}

int16_t CNWSCreature_s::GetMaxHitPoints(int a2) {
	return CNWSCreature__GetMaxHitPoints(this, a2);
}

void CNWSCreature_s::UnpossessCreature() {
	CNWSCreature__UnpossessCreature(this);
}

void CNWSCreature::UnpossessFamiliar() {
	CNWSCreature__UnpossessFamiliar(this);
}

CNWSFaction * CNWSCreature_s::GetFaction() {
	return CNWSCreature__GetFaction(this);
}

CNWSQuickbarButton * CNWSCreature_s::GetQuickbarButton(unsigned char nTh)
{
	return CNWSCreature__GetQuickbarButton(this,nTh);
}

int CNWSCreature_s::Polymorph(int nPoly, CGameEffect *eff, int nLock) 
{
	return CNWSCreature__Polymorph(this,nPoly,eff,nLock);
}

int CNWSCreature_s::UnPolymorph(CGameEffect *eff) 
{
	return CNWSCreature__UnPolymorph(this,eff);
}

int CNWSCreature_s::GetIsPossessedFamiliar()
{
	return CNWSCreature__GetIsPossessedFamiliar(this);
}

int CNWSCreature_s::CanUseItem(CNWSItem *item, int a1)
{
	return CNWSCreature__CanUseItem(this,item,a1);
}

unsigned char CNWSCreature::CanEquipItem(CNWSItem *item, unsigned long *a1, int a2, int a3, int a4, CNWSPlayer *player)
{
	return CNWSCreature__CanEquipItem(this,item,a1,2,3,4,player);
}

unsigned long CNWSCreature_s::GetAssociateId(unsigned short type, int nTh)
{
	return CNWSCreature__GetAssociateId(this,type,nTh);
}

void CNWSCreature_s::SetEffectSpellId(unsigned long ID)
{
	CNWSCreature__SetEffectSpellId(this, ID);
}

float CNWSCreature_s::GetMovementRateFactor()
{
	return CNWSCreature__GetMovementRateFactor(this);
}

int CNWSCreature_s::SetMovementRateFactor(float fSpeed)
{
	return CNWSCreature__SetMovementRateFactor(this, fSpeed);
}

int CNWSCreature::AddAttackActions(unsigned long feat, int a1, int a2, int a3)
{
	return CNWSCreature__AddAttackActions(this, feat,a1,a2,a3);
}