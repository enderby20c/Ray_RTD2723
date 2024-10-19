//--------------------------------------------------
// EDID Type Selection
//--------------------------------------------------
#define _EDID_SEGMENT_SIZE_384                           _EDID_DP_5120_2880_60HZ_384
#define _EDID_SEGMENT_SIZE_256                           _EDID_DP_5120_2880_60HZ_256

#define _EDID_D8_D1_TYPE_SEL                             ((_D8_D1_EMBEDDED_DDCRAM_SIZE == _EDID_SIZE_384) ? _EDID_SEGMENT_SIZE_384 : _EDID_SEGMENT_SIZE_256)
#define _EDID_D8_D2_TYPE_SEL                             ((_D8_D2_EMBEDDED_DDCRAM_SIZE == _EDID_SIZE_384) ? _EDID_SEGMENT_SIZE_384 : _EDID_SEGMENT_SIZE_256)

//--------------------------------------------------
// EDID Table
//--------------------------------------------------
#if((_WRITE_EDID_TO_SYSTEM_EEPROM == _ON) ||\
    ((_D8_D1_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) &&\
     (_D8_D2_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) &&\
     (_D8_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_CODE)))

BYTE code tEDID_TABLE_D8_D1[] =
{
#if(_EDID_D8_D1_TYPE_SEL == _EDID_DP_5120_2880_60HZ_256)
#include <EDID/EdidDp/EDID_DP_BD2_5120x2880@60_M5.h>
#elif(_EDID_D8_D1_TYPE_SEL == _EDID_DP_5120_2880_60HZ_384)
#include <EDID/EdidDp/EDID_DP_BCD2_5120x2880@60_M5.h>
#elif(_EDID_D8_D1_TYPE_SEL == _EDID_DP_3840_2160_144HZ_256)
#include <EDID/EdidDp/EDID_DP_BD2_3840x2160@144_M5.h>
#elif(_EDID_D8_D1_TYPE_SEL == _EDID_DP_3840_2160_144HZ_384)
#include <EDID/EdidDp/EDID_DP_BCD2_3840x2160@144_M5.h>
#endif
};

BYTE code tEDID_TABLE_D8_D2[] =
{
#if(_EDID_D8_D2_TYPE_SEL == _EDID_DP_5120_2880_60HZ_256)
#include <EDID/EdidDp/EDID_DP_BD2_5120x2880@60_M5.h>
#elif(_EDID_D8_D2_TYPE_SEL == _EDID_DP_5120_2880_60HZ_384)
#include <EDID/EdidDp/EDID_DP_BCD2_5120x2880@60_M5.h>
#elif(_EDID_D8_D2_TYPE_SEL == _EDID_DP_3840_2160_144HZ_256)
#include <EDID/EdidDp/EDID_DP_BD2_3840x2160@144_M5.h>
#elif(_EDID_D8_D2_TYPE_SEL == _EDID_DP_3840_2160_144HZ_384)
#include <EDID/EdidDp/EDID_DP_BCD2_3840x2160@144_M5.h>
#endif
};

#endif
