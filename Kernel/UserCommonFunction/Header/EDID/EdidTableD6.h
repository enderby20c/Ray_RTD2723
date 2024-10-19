//--------------------------------------------------
// EDID Type Selection
//--------------------------------------------------
#define _EDID_D6_TYPE_SEL                               _EDID_DP_1920_1080_60HZ


//--------------------------------------------------
// EDID Table
//--------------------------------------------------
#if((_WRITE_EDID_TO_SYSTEM_EEPROM == _ON) || ((_D6_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) && (_D6_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_CODE)))

BYTE code tEDID_TABLE_D6[] =
{
#if(_EDID_D6_TYPE_SEL == _EDID_DP_1920_1080_60HZ)
#include <EDID/EdidDp/EDID_DP_BC_1920x1080@60.h>
#elif(_EDID_D6_TYPE_SEL == _EDID_DP_1920_1080_60HZ_HDR)
#include <EDID/EdidDp/EDID_DP_BC_1920x1080@60_HDR0.h>
#elif(_EDID_D6_TYPE_SEL == _EDID_DP_1920_1080_30HZ_144HZ_FREESYNC)
#include <EDID/EdidDp/EDID_DP_BC_1920x1080@30-144_DRR0.h>
#elif(_EDID_D6_TYPE_SEL == _EDID_DP_1920_1080_50HZ_75HZ_FREESYNC)
#include <EDID/EdidDp/EDID_DP_BC_1920x1080@50-75_DRR0.h>
#elif(_EDID_D6_TYPE_SEL == _EDID_DP_2560_1440_60HZ)
#include <EDID/EdidDp/EDID_DP_BC_2560x1440@60.h>
#elif(_EDID_D6_TYPE_SEL == _EDID_DP_2560_1440_60HZ_HDR)
#include <EDID/EdidDp/EDID_DP_BC_2560x1440@60_HDR0.h>
#elif(_EDID_D6_TYPE_SEL == _EDID_DP_3840_2160_30HZ)
#include <EDID/EdidDp/EDID_DP_BC_3840x2160@30.h>
#elif(_EDID_D6_TYPE_SEL == _EDID_DP_3840_2160_60HZ)
#include <EDID/EdidDp/EDID_DP_BC_3840x2160@60.h>
#elif(_EDID_D6_TYPE_SEL == _EDID_DP_3840_2160_60HZ_HDR)
#include <EDID/EdidDp/EDID_DP_BC_3840x2160@60_HDR0.h>
#endif
};

#endif
