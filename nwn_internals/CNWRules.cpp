#include "types.h"
#include "nwn_internals.h"

CNWFeat* (__thiscall *CNWRules__GetFeat)(CNWRules*, unsigned short) = (CNWFeat* (__thiscall*)(CNWRules*, unsigned short))0x4B7E70;//warning: crash when loading game
CNWDomain* (__thiscall *CNWRules__GetDomain)(CNWRules*, unsigned short) = (CNWDomain* (__thiscall*)(CNWRules*, unsigned short))0x4B7EB0;//warning: crash when loading game

uint8_t 		(__thiscall *CNWRules__GetFeatExpansionLevel)(CNWRules *pThis, uint16_t FeatID) = (uint8_t (__thiscall*)(CNWRules *, uint16_t))0x004B80F0;
int			(__thiscall *CNWRules__GetDifficultyOption)(CNWRules *pThis, int i1, int i2) = (int (__thiscall*)(CNWRules *pThis, int, int))0x4B7EF0;
int				(__thiscall *CNWRules__IsArcaneClass)(CNWRules *pThis, unsigned char) = (int (__thiscall*)(CNWRules *, unsigned char))0x4B8270;
unsigned char (__thiscall *CNWRules__GetFamiliarExpansionLevel)(CNWRules*, unsigned char, int) = (unsigned char (__thiscall*)(CNWRules*, unsigned char, int))0x4B8230;
unsigned char (__thiscall *CNWRules__GetMetaMagicLevelCost)(CNWRules*, unsigned char) = (unsigned char (__thiscall*)(CNWRules*, unsigned char))0x4B7DE0;

void (__thiscall *CNWRules__LoadClassInfo)(CNWRules*) = (void (__thiscall*)(CNWRules*))0x4B5F10;
void (__thiscall *CNWRules__LoadRaceInfo)(CNWRules*) = (void (__thiscall*)(CNWRules*))0x4B6DB0;
void (__thiscall *CNWRules__LoadSkillInfo)(CNWRules*) = (void (__thiscall*)(CNWRules*))0x4B7510;
void (__thiscall *CNWRules__LoadDomainInfo)(CNWRules*) = (void (__thiscall*)(CNWRules*))0x4B7A00;
void (__thiscall *CNWRules__LoadFeatInfo)(CNWRules*) = (void (__thiscall*)(CNWRules*))0x4B4B90;

CNWFeat* CNWRules::GetFeat(unsigned short feat) {
	return CNWRules__GetFeat(this, feat);
}

CNWDomain* CNWRules::GetDomain(unsigned short id) {
	return CNWRules__GetDomain(this, id);
}

uint8_t CNWRules::GetFeatExpansionLevel(uint16_t FeatID) {
	return CNWRules__GetFeatExpansionLevel(this, FeatID);
}

int CNWRules::GetDifficultyOption(int i1, int i2) {
	return CNWRules__GetDifficultyOption(this, i1,i2);
}

unsigned short CNWRules::RollDice(unsigned char NumDice, unsigned char DieType) {
	int v4, v3=0;
	if (DieType && (v4 = NumDice, (signed int)NumDice > 0)) {
		do {
			--v4;
			v3 += rand() % DieType + 1;
		} while (v4);
		return v3;
	}
	return 0;		
}

int CNWRules::IsArcaneClass(unsigned char cls) {
	return CNWRules__IsArcaneClass(this, cls);
}

unsigned char CNWRules::GetFamiliarExpansionLevel(unsigned char type, int famil_or_acomp) {
	return CNWRules__GetFamiliarExpansionLevel(this, type, famil_or_acomp);
}

unsigned char CNWRules::GetMetaMagicLevelCost(unsigned char meta_type) {
	return CNWRules__GetMetaMagicLevelCost(this, meta_type);
}

void CNWRules::LoadClassInfo() {
	CNWRules__LoadClassInfo(this);
}

void CNWRules::LoadRaceInfo() {
	CNWRules__LoadRaceInfo(this);
}

void CNWRules::LoadDomainInfo() {
	CNWRules__LoadDomainInfo(this);
}

void CNWRules::LoadFeatInfo() {
	CNWRules__LoadFeatInfo(this);
}

void CNWRules::LoadSkillInfo() {
	CNWRules__LoadSkillInfo(this);
}