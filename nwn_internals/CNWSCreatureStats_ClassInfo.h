#ifndef _NX_NWN_STRUCT__CNWSCREATURESTATS_CLASSINFO_
#define _NX_NWN_STRUCT__CNWSCREATURESTATS_CLASSINFO_

struct CNWSCreatureStats_ClassInfo_s
{
	CExoArrayList_uint32		cl_spells_known[10];	/* 0x000 - 0x00A4 */ // 120 bytes
	CExoArrayList_ptr			cl_spells_mem[10];		/* 0x078 - 0x011C */ // 120 bytes
	uint8_t						cl_spells_bonus[10];	/* 0x0F0 - 0x0194 */
	uint8_t						cl_spells_left[10];		/* 0x0FA - 0x019E */
	uint8_t						cl_spells_max[10];		/* 0x104 - 0x01A8 */

	uint8_t						cl_class;				/* 0x10E - 0x01B2 */
	uint8_t						cl_level;				/* 0x10F - 0x01B3 */

	uint8_t						cl_negative_level;		/* 0x110 - 0x01B4 */

	uint8_t						cl_specialist;			/* 0x111 - 0x01B5 */
	uint8_t						cl_domain_1;			/* 0x112 - 0x01B6 */
	uint8_t						cl_domain_2;			/* 0x113 - 0x01B7 */

	uint32_t					cl_fallen;			/* 0x114 - 0x01B8 */

CNWSCreatureStats_ClassInfo_s();
~CNWSCreatureStats_ClassInfo_s();
void SetMemorizedSpellSlot(unsigned char, unsigned char, unsigned long spell_id, int, unsigned char);
void ClearMemorizedSpellSlot(unsigned char, unsigned char);
void ClearMemorizedKnownSpells(unsigned long spell_id);
void RemoveKnownSpell(unsigned char spell_level, unsigned long spell_id);
unsigned long GetKnownSpell(unsigned char, unsigned char);
unsigned long GetMemorizedSpellInSlot(unsigned char, unsigned char);
int GetIsDomainSpell(unsigned char, unsigned char);
CNWSStats_Spell * GetMemorizedSpellInSlotDetails(unsigned char, unsigned char);
void SetNumberMemorizedSpellSlots(unsigned char, unsigned char);
int GetMemorizedSpellInSlotReady(unsigned char spell_level, unsigned char spell_pos);
void SetMemorizedSpellInSlotReady(unsigned char spell_level, unsigned char spell_pos, int spell_ready);
unsigned char GetMemorizedSpellReadyCount(unsigned long spell_id, unsigned char *, unsigned char *, unsigned char);
unsigned char GetMemorizedSpellInSlotMetaType(unsigned char, unsigned char);
int ConfirmDomainSpell(unsigned char arg1, unsigned long spell_id);
unsigned char GetNumberMemorizedSpellSlots(unsigned char spell_level);

//int AddKnownSpell(unsigned char, unsigned long);
//int DecrementSpellsPerDayLeft(unsigned char);
//int GetMaxSpellsPerDayLeft(unsigned char);
//int GetMemorizedSpellReadyCount(unsigned long, unsigned char);
//int GetNumberBonusSpells(unsigned char);
//int GetNumberKnownSpells(unsigned char);
//int GetSpellsPerDayLeft(unsigned char);
//int IncrementSpellsPerDayLeft(unsigned char);
//int ResetSpellsPerDayLeft(unsigned char, unsigned char);
//int SetMaxSpellsPerDayLeft(unsigned char, unsigned char);
//int SetNumberBonusSpells(unsigned char, unsigned char);
//int SetSpellsPerDayLeft(unsigned char, unsigned char);


};
#endif