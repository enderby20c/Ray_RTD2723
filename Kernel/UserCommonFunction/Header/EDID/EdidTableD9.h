//--------------------------------------------------
// EDID Type Selection
//--------------------------------------------------


//--------------------------------------------------
// EDID Table
//--------------------------------------------------
#if((_WRITE_EDID_TO_SYSTEM_EEPROM == _ON) || ((_D9_EMBEDDED_XRAM_MAX_SIZE != _EDID_SIZE_NONE) && (_D9_EMBEDDED_XRAM_LOCATION == _EDID_TABLE_LOCATION_CODE)))

BYTE code tEDID_TABLE_D9[] =
{
#include <EDID/EdidDp/EDID_DP_BC_1920x1080@60.h>
};

#endif
