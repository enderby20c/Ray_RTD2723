{
#if(_PANEL_STYLE == _PANEL_DPTX)
    _PANEL_DPTX_LINK_HBR2, // _PANEL_DPTX_LINK_RATE
    _PANEL_DPTX_LANE_NUMBER_4, // _PANEL_DPTX_LANE_NUMBER
    _PANEL_DPTX_VENDOR_SPECIFIC_NONE, // _PANEL_DPTX_VENDOR_SPECIFIC_TYPE
    _DPTX_PANEL_1_SECTION, // _PANEL_DPTX_PANEL_SECTION
#endif

    _PANEL_PIXEL_LCD, // _PANEL_PIXEL_TYPE

    2000,        // _LAST_LINE_MAX
    1900,        // _LAST_LINE_MIN
    _PANEL_AUO, // _PANEL_MANUFACTURER
    _PANEL_DISP_24_BIT, // _PANEL_DISP_COLOR_BIT

    600,        // _PANEL_TYP_FRAME_RATE
    860,        // _PANEL_MAX_FRAME_RATE
    560,        // _PANEL_MIN_FRAME_RATE

#if(_DRR_SUPPORT == _ON)
    750,        // _PANEL_DP_FREESYNC_MAX_FRAME_RATE
    480,        // _PANEL_DP_FREESYNC_MIN_FRAME_RATE
    750,        // _PANEL_HDMI_FREESYNC_MAX_FRAME_RATE
    480,        // _PANEL_HDMI_FREESYNC_MIN_FRAME_RATE
    750,        // _PANEL_HDMI21_VRR_MAX_FRAME_RATE
    480,        // _PANEL_HDMI21_VRR_MIN_FRAME_RATE
#endif

    48,         // _PANEL_DH_START
    1920,       // _PANEL_DH_WIDTH

    2100,       // _PANEL_DH_TOTAL
    2200,       // _PANEL_DH_TOTAL_MAX
    2048,       // _PANEL_DH_TOTAL_MIN

    6,          // _PANEL_DV_START
    1080,       // _PANEL_DV_HEIGHT

    1150,       // _PANEL_DV_TOTAL
#if(_DRR_SUPPORT == _ON)
    8000,       // _PANEL_DV_TOTAL_MAX
#else
    1600,       // _PANEL_DV_TOTAL_MAX
#endif
    1100,       // _PANEL_DV_TOTAL_MIN

    8,          // _PANEL_DH_SYNC_WIDTH
    2,          // _PANEL_DV_SYNC_HEIGHT

    144,        // _PANEL_PIXEL_CLOCK
    180,        // _PANEL_PIXEL_CLOCK_MAX
    110,        // _PANEL_PIXEL_CLOCK_MIN

    100,        // _PANEL_POWER_ON_T1
    40,         // _PANEL_POWER_ON_T2
    300,        // _PANEL_POWER_ON_T3

    20,         // _PANEL_POWER_OFF_T4
    40,         // _PANEL_POWER_OFF_T5
    600,        // _PANEL_POWER_OFF_T6
},

