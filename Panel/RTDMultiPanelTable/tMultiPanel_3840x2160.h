// 3840x2160
{
#if(_PANEL_STYLE == _PANEL_DPTX)
    _PANEL_DPTX_LINK_HBR2, // _PANEL_DPTX_LINK_RATE
    _PANEL_DPTX_LANE_NUMBER_4, // _PANEL_DPTX_LANE_NUMBER
    _PANEL_DPTX_VENDOR_SPECIFIC_NONE, // _PANEL_DPTX_VENDOR_SPECIFIC_TYPE
    _DPTX_PANEL_1_SECTION, // _PANEL_DPTX_PANEL_SECTION
#endif

    _PANEL_PIXEL_LCD, // _PANEL_PIXEL_TYPE

    3800,        // _LAST_LINE_MAX
    3600,        // _LAST_LINE_MIN
    _PANEL_SAMSUNG, // _PANEL_MANUFACTURER
    _PANEL_DISP_24_BIT,

    600,        // _PANEL_TYP_FRAME_RATE
    860,        // _PANEL_MAX_FRAME_RATE
    560,        // _PANEL_MIN_FRAME_RATE

#if(_DRR_SUPPORT == _ON)
    600,        // _PANEL_DP_FREESYNC_MAX_FRAME_RATE
    400,        // _PANEL_DP_FREESYNC_MIN_FRAME_RATE
    600,        // _PANEL_HDMI_FREESYNC_MAX_FRAME_RATE
    400,        // _PANEL_HDMI_FREESYNC_MIN_FRAME_RATE
    600,        // _PANEL_HDMI21_VRR_MAX_FRAME_RATE
    400,        // _PANEL_HDMI21_VRR_MIN_FRAME_RATE
#endif

    48,         // _PANEL_DH_START
    3840,       // _PANEL_DH_WIDTH

    3956,       // _PANEL_DH_TOTAL
    4020,       // _PANEL_DH_TOTAL_MAX
    3892,       // _PANEL_DH_TOTAL_MIN

    6,          // _PANEL_DV_START
    2160,       // _PANEL_DV_HEIGHT

    2190,       // _PANEL_DV_TOTAL
#if(_DRR_SUPPORT == _ON)
    8000,       // _PANEL_DV_TOTAL_MAX
#else
    2210,       // _PANEL_DV_TOTAL_MAX
#endif
    2170,       // _PANEL_DV_TOTAL_MIN

    8,          // _PANEL_DH_SYNC_WIDTH
    2,          // _PANEL_DV_SYNC_HEIGHT

    520,        // _PANEL_PIXEL_CLOCK
    700,        // _PANEL_PIXEL_CLOCK_MAX
    250,        // _PANEL_PIXEL_CLOCK_MIN

    10,        // _PANEL_POWER_ON_T1
    100,         // _PANEL_POWER_ON_T2
    50,        // _PANEL_POWER_ON_T3

    50,         // _PANEL_POWER_OFF_T4
    10,         // _PANEL_POWER_OFF_T5
    300,        // _PANEL_POWER_OFF_T6
},

