#include "types.h"
#include "nwn_internals.h"

#include "CNWSPlayerCharSheetGUI.h"

uint32_t (__thiscall *CNWSPlayerCharSheetGUI__ComputeCharacterSheetUpdateRequired)(CNWSPlayerCharSheetGUI_s *pThis, CNWSPlayer *Player) = (uint32_t (__thiscall*)(CNWSPlayerCharSheetGUI_s *, CNWSPlayer *))0x42E120;

uint32_t CNWSPlayerCharSheetGUI_s::ComputeCharacterSheetUpdateRequired(CNWSPlayer *Player) {
	char *pl = (char*)Player;
	return CNWSPlayerCharSheetGUI__ComputeCharacterSheetUpdateRequired((CNWSPlayerCharSheetGUI_s*)(pl + 0x60), Player);
}