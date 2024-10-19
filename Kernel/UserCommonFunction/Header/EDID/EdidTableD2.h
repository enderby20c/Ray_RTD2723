//--------------------------------------------------
// EDID Type Selection
//--------------------------------------------------
#if(_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT)

#if(_D2_HDMI20_SUPPORT == _ON)

#if(_HDMI20_YCBCR420_SUPPORT == _ON)
#define _EDID_D2_TYPE_SEL                               _EDID_HDMI2_3840_2160_60HZ_WITH_420
#else
#define _EDID_D2_TYPE_SEL                               _EDID_HDMI2_3840_2160_60HZ
#endif

#else
#define _EDID_D2_TYPE_SEL                               _EDID_HDMI_1920_1080_60HZ
#endif

#elif(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)

#if(_D8_INPUT_PORT_TYPE == _D8_DP_PORT)
#define _EDID_D2_TYPE_SEL                               _EDID_DP_5120_2880_60HZ_384
#else
#define _EDID_D2_TYPE_SEL                               _EDID_DP_1920_1080_60HZ
#endif

#endif


//--------------------------------------------------
// EDID Table
//--------------------------------------------------
#if((_WRITE_EDID_TO_SYSTEM_EEPROM == _ON) || ((_D2_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) && (_D2_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_CODE)))

BYTE code tEDID_TABLE_D2[] =
{
#if(_EDID_D2_TYPE_SEL == _EDID_HDMI_1920_1080_60HZ)
#include <EDID/EdidHdmi/EDID_HDMI_BC_1920x1080@60.h>
#elif(_EDID_D2_TYPE_SEL == _EDID_HDMI_1920_1080_60HZ_HDR)
#include <EDID/EdidHdmi/EDID_HDMI_BC_1920x1080@60_HDR0.h>
#elif(_EDID_D2_TYPE_SEL == _EDID_HDMI_1920_1080_40HZ_75HZ_FREESYNC)
#include <EDID/EdidHdmi/EDID_HDMI_BC_1920x1080@40-75_DRR0.h>
#elif(_EDID_D2_TYPE_SEL == _EDID_HDMI_1920_1080_40HZ_120HZ_FREESYNC)
#include <EDID/EdidHdmi/EDID_HDMI_BC_1920x1080@40-120_DRR0.h>
#elif(_EDID_D2_TYPE_SEL == _EDID_HDMI_2560_1440_60HZ)
#include <EDID/EdidHdmi/EDID_HDMI_BC_2560x1440@60.h>
#elif(_EDID_D2_TYPE_SEL == _EDID_HDMI_2560_1440_60HZ_HDR)
#include <EDID/EdidHdmi/EDID_HDMI_BC_2560x1440@60_HDR0.h>
#elif(_EDID_D2_TYPE_SEL == _EDID_HDMI_2560_1440_40HZ_70HZ_FREESYNC)
#include <EDID/EdidHdmi/EDID_HDMI_BC_2560x1440@40-70_DRR0.h>
#elif(_EDID_D2_TYPE_SEL == _EDID_HDMI2_3840_2160_60HZ_WITH_420)
#include <EDID/EdidHdmi/EDID_HDMI_BC_3840x2160@60_M0.h>
#elif(_EDID_D2_TYPE_SEL == _EDID_HDMI2_3840_2160_60HZ)
#include <EDID/EdidHdmi/EDID_HDMI_BC_3840x2160@60.h>
#elif(_EDID_D2_TYPE_SEL == _EDID_HDMI2_3840_2160_60HZ_WITH_420_HDR)
#include <EDID/EdidHdmi/EDID_HDMI_BC_3840x2160@60_M0_HDR0.h>
#elif(_EDID_D2_TYPE_SEL == _EDID_DP_1920_1080_60HZ)
#include <EDID/EdidDp/EDID_DP_BC_1920x1080@60.h>
#endif
};

#endif
