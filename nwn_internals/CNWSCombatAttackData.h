#ifndef _NX_NWN_STRUCT_CNWSCOMBATATTACKDATA_
#define _NX_NWN_STRUCT_CNWSCOMBATATTACKDATA_
 
 struct CNWSCombatAttackData_s {
  	unsigned __int8 m_nAttackGroup;//0x0
    unsigned __int16 m_nAnimationLength;
    unsigned __int32 m_oidReactObject;//0x4
    unsigned __int16 m_nReactionDelay;//0x8
    unsigned __int16 m_nReactionAnimation;//0xA
    unsigned __int16 m_nReactionAnimationLength;//0xC
    unsigned __int8 m_nToHitRoll;//0xE
    unsigned __int8 m_nThreatRoll;//0xF
    int m_nToHitMod;//0x10
    char m_nMissedBy;
    __int16 m_nDamage[13];
  /*unsigned __int16 Damage_Bludgeoning;
  unsigned __int16 Damage_Piercing;
  unsigned __int16 Damage_Slashing;
  unsigned __int16 Damage_Magical;
  unsigned __int16 Damage_Acid;
  unsigned __int16 Damage_cold;
  unsigned __int16 Damage_Divine;
  unsigned __int16 Damage_Electrical;
  unsigned __int16 Damage_Fire;
  unsigned __int16 Damage_Negative;
  unsigned __int16 Damage_Positive;
  unsigned __int16 Damage_Sonic;
  unsigned __int16 BaseDamage;*/
    unsigned __int8 m_nWeaponAttackType;//0x30 1=onhand,2=offhand,3,4,5=creaturewpn,6=extraattack,7=unarmed
    unsigned __int8 m_nAttackMode;//0x31
    unsigned __int8 m_nConcealment;//0x32
    int m_bRangedAttack;//0x34
    int m_bSneakAttack;//0x38
    int m_bDeathAttack;//0x3C
    int m_bKillingBlow;//0x40
    int m_bCoupDeGrace;//0x44
    int m_bCriticalThreat;//0x48
    int m_bAttackDeflected;//0x4C
    unsigned __int8 m_nAttackResult;//0x50 - 0=nothing 2=parried 4=miss 1=hit,3=critical hit,5=resisted,6=failed,7=automatic hit,8=target concealed %, 9=attacker miss chance %,10=devastating critical hit
    unsigned __int16 m_nAttackType;//0x52 match feat id; 39stun fist 23knockdown 9disarm 16impdisarm
    unsigned __int16 m_nSpecialAttackID;
    Vector m_vRangedTarget;
    unsigned __int32 m_oidAmmunition;
    CExoString m_sAttackDebugText;//70
    CExoString m_sDamageDebugText;//78
    CExoArrayList_ptr m_alstOnHitGameEffects;//CGameEffect
    CExoArrayList_ptr m_alstOnHitSpellScripts;//CNWSSpellScriptData
    CExoArrayList_ptr m_alstOnHitEnemySpellScripts;//CNWSSpellScriptData
    CExoArrayList_ptr m_alstPendingFeedback;//CNWCCMessageData

  CNWSCombatAttackData_s();
  ~CNWSCombatAttackData_s();
 

  int GetDamage(unsigned short i);
  int GetTotalDamage(int i);
};

#endif