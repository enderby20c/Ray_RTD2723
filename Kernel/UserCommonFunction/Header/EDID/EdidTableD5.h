//--------------------------------------------------
// EDID Type Selection
//--------------------------------------------------
#if(_D5_INPUT_PORT_TYPE == _D5_HDMI_PORT)
#define _EDID_D5_TYPE_SEL                               _EDID_HDMI_1920_1080_60HZ
#endif


//--------------------------------------------------
// EDID Table
//--------------------------------------------------
#if((_WRITE_EDID_TO_SYSTEM_EEPROM == _ON) || ((_D5_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) && (_D5_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_CODE)))

BYTE code tEDID_TABLE_D5[] =
{
#if(_EDID_D5_TYPE_SEL == _EDID_HDMI_1920_1080_60HZ)
#include <EDID/EdidHdmi/EDID_HDMI_BC_1920x1080@60.h>
#elif(_EDID_D5_TYPE_SEL == _EDID_HDMI_1920_1080_60HZ_HDR)
#include <EDID/EdidHdmi/EDID_HDMI_BC_1920x1080@60_HDR0.h>
#elif(_EDID_D5_TYPE_SEL == _EDID_HDMI_1920_1080_40HZ_75HZ_FREESYNC)
#include <EDID/EdidHdmi/EDID_HDMI_BC_1920x1080@40-75_DRR0.h>
#elif(_EDID_D5_TYPE_SEL == _EDID_HDMI_1920_1080_40HZ_120HZ_FREESYNC)
#include <EDID/EdidHdmi/EDID_HDMI_BC_1920x1080@40-120_DRR0.h>
#elif(_EDID_D5_TYPE_SEL == _EDID_HDMI_2560_1440_60HZ)
#include <EDID/EdidHdmi/EDID_HDMI_BC_2560x1440@60.h>
#elif(_EDID_D5_TYPE_SEL == _EDID_HDMI_2560_1440_60HZ_HDR)
#include <EDID/EdidHdmi/EDID_HDMI_BC_2560x1440@60_HDR0.h>
#elif(_EDID_D5_TYPE_SEL == _EDID_HDMI_2560_1440_40HZ_70HZ_FREESYNC)
#include <EDID/EdidHdmi/EDID_HDMI_BC_2560x1440@40-70_DRR0.h>
#elif(_EDID_D5_TYPE_SEL == _EDID_HDMI2_3840_2160_60HZ_WITH_420)
#include <EDID/EdidHdmi/EDID_HDMI_BC_3840x2160@60_M0.h>
#elif(_EDID_D5_TYPE_SEL == _EDID_HDMI2_3840_2160_60HZ)
#include <EDID/EdidHdmi/EDID_HDMI_BC_3840x2160@60.h>
#elif(_EDID_D5_TYPE_SEL == _EDID_HDMI2_3840_2160_60HZ_WITH_420_HDR)
#include <EDID/EdidHdmi/EDID_HDMI_BC_3840x2160@60_M0_HDR0.h>
#endif
};

#endif
