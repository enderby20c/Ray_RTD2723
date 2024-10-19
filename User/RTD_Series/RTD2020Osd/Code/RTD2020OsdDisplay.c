/********************************************************************************/
/*   Copyright (c) 2021 Realtek Semiconductor Corp. All rights reserved.        */
/*                                                                              */
/*   SPDX-License-Identifier: LicenseRef-Realtek-Proprietary                    */
/*                                                                              */
/*   This software component is confidential and proprietary to Realtek         */
/*   Semiconductor Corp. Disclosure, reproduction, redistribution, in whole     */
/*   or in part, of this work and its derivatives without express permission    */
/*   is prohibited.                                                             */
/********************************************************************************/

//----------------------------------------------------------------------------------------------------
// ID Code      : RTD2020OsdDisplay.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RTD_OSDDISPLAY__

#include "RTD2020UserInclude.h"

#if(_OSD_TYPE == _REALTEK_2020_OSD)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************
#if(_DM_FUNCTION == _ON)
BYTE code tOSD_DM[] =
{
    0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, _NEXT_,
    0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, _NEXT_,
    0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, _END_,
};
BYTE code tOSD_DM_2[] =
{
    0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, _NEXT_,
    0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6, 0xB7, 0xB8, _NEXT_,
    0xB9, 0xBA, 0xBB, 0xBC, 0xBD, 0xBE, 0xBF, 0xC0, 0xC1, 0xC2, 0xC3, 0xC4, _END_,
};
BYTE code tOSD_DM_CLEAR[] =
{
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, _NEXT_,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, _NEXT_,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, _END_,
};

#endif
//--------------------------------------------------
// Definitions of Picture OSD ITEM
//--------------------------------------------------
//following order could modify by User
BYTE code tOSD_MAIN_ITEM_PRI[] =
{
    _OSD_MENU_QUICKLINK,
#if(_MULTI_DISPLAY_MAX > 1)
    _OSD_MENU_MUTIP,
#endif
    _OSD_MENU_PICTURE,
    _OSD_MENU_DISPLAY,
    _OSD_MENU_COLOR,
    _OSD_MENU_ADVANCE,
    _OSD_MENU_OTHER,
#if(_HDR10_SUPPORT == _ON)
    _OSD_MENU_HDR,
#endif
#if(_AUDIO_SUPPORT == _ON)
    _OSD_MENU_AUDIO,
#endif
    _OSD_MENU_INPUT,
#if(_DM_FUNCTION == _ON)
    _OSD_MENU_DVISION,
#endif
#if(_AUDIO_ARC_SUPPORT == _ON)
    _OSD_MENU_AUDIO_ARC_EARC,
#endif
    _OSD_MENU_FACTORY,

};
#define _OSD_MAIN_ITEM_AMOUNT      (sizeof(tOSD_MAIN_ITEM_PRI))
//--------------------------------------------------
// Definitions of QUICK
//--------------------------------------------------
//following order could modify by User
BYTE code tOSD_QUICK_ITEM_PRI[] =
{
#if(_MULTI_DISPLAY_MAX > 1)
    _OSD_MUTIP_MODE,
#endif
    _OSD_ADVANCE_DDCCI,
#if(_DP_SUPPORT == _ON)
    _OSD_ADVANCE_DPOPTION,
#endif
    _OSD_OTHER_MENU_TIME,
#if(_USB2_HOST_EHCI_MASS_STORGE_PROGRAM_SUPPORT == _ON)
    _OSD_ADVANCE_FW_UPDATE,
#endif
    _OSD_OTHER_CROSSHAIR,
};
#define _OSD_QUICK_ITEM_AMOUNT     (sizeof(tOSD_QUICK_ITEM_PRI))
//--------------------------------------------------
// Definitions of Picture OSD ITEM
//--------------------------------------------------

//following order could modify by User
BYTE code tOSD_PICTURE_ITEM_PRI[] =
{
    _OSD_PICTURE_BACKLIGHT,

#if(_BRIGHTNESS_FUNCTION == _ON)
    _OSD_PICTURE_BRIGHTNESS,
#endif

#if(_CONTRAST_FUNCTION == _ON)
    _OSD_PICTURE_CONTRAST,
#endif

#if(_SHARPNESS_FUNCTION == _ON)
    _OSD_PICTURE_SHARNESS,
#endif


};
#define _OSD_PICTURE_ITEM_AMOUNT   (sizeof(tOSD_PICTURE_ITEM_PRI))

//--------------------------------------------------
// Definitions of Dispaly OSD ITEM
//-------------------------------------------------
//following order could modify by User
BYTE code tOSD_DISPLAY_ITEM_PRI[] =
{
    _OSD_DISPLAY_AUTO,
    _OSD_AUTO_COLOR,
    _OSD_DISPLAY_HPOS,
    _OSD_DISPLAY_VPOS,
    _OSD_DISPLAY_CLOCK,
    _OSD_DISPLAY_PHASE,

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
    _OSD_DISPLAY_DISP_ROTATE,
#endif
#if(_DISP_LATENCY_ADJUST_SUPPORT == _ON)
    _OSD_DISPLAY_LATENCY,
#endif
#if(_FREEZE_SUPPORT == _ON)
    _OSD_DISPLAY_FREEZE,
#endif

};
#define _OSD_DISPLAY_ITEM_AMOUNT   (sizeof(tOSD_DISPLAY_ITEM_PRI))

//--------------------------------------------------
// Definitions of Color OSD ITEM
//--------------------------------------------------
//following order could modify by User
BYTE code tOSD_COLOR_ITEM_PRI[] =
{
#if(_UNIFORMITY_FUNCTION == _ON)
    _OSD_COLOR_PANEL_UNIFORMITY,
#endif
#if(_GAMMA_FUNCTION == _ON)
    _OSD_COLOR_GAMMA,
#endif
    _OSD_COLOR_TEMPERATURE,
    _OSD_COLOR_TEMP_USER,
#if((_ICM_FUNCTION == _ON) || (_DCC_FUNCTION == _ON))
    _OSD_COLOR_EFFECT,
    _OSD_COLOR_EFFECT_USER,
#if(_ICM_CHAMELEON_FUNCTION == _ON)
    _OSD_COLOR_CHAMELEON_USER,
#endif
#endif
#if(_COLOR_DEMO_FUNCTION == _ON)
    _OSD_COLOR_DEMO,
    _OSD_COLOR_DEMO_SIDE,
#endif
#if(_COLOR_FORMAT_CONVERT_FUNCTION == _ON)
    _OSD_COLOR_FORMAT,
#endif
#if(_PCM_FUNCTION == _ON)
    _OSD_COLOR_PCM,
#endif
#if(_GLOBAL_HUE_SATURATION_FUNCTION == _ON)
    _OSD_COLOR_HUE,
    _OSD_COLOR_SATURATION,
#endif
#if(_DYNAMIC_LOWBLUE_FUNCTION == _ON)
    _OSD_COLOR_EYE_PROTECT,
#endif

};
#define _OSD_COLOR_ITEM_AMOUNT     (sizeof(tOSD_COLOR_ITEM_PRI))

//--------------------------------------------------
// Definitions of Advance Item
//--------------------------------------------------
//following order could modify by User
BYTE code tOSD_ADVANCE_ITEM_PRI[] =
{
#if(_ASPECT_RATIO_SUPPORT == _ON)
    _OSD_ADVANCE_ASPECT,
#endif

#if(_OVERSCAN_SUPPORT == _ON)
    _OSD_ADVANCE_OVERSCAN,
#endif

#if(_OD_FUNCTION == _ON)
    _OSD_ADVANCE_OVERDRIVE,
#endif

    _OSD_ADVANCE_DDCCI,

#if(_ULTRA_VIVID_FUNCTION == _ON)
    _OSD_ADVANCE_ULTRAVIVID,
#endif

#if(_DCR_FUNCTION == _ON)
    _OSD_ADVANCE_DCR,
#endif

#if(_DP_SUPPORT == _ON)
    _OSD_ADVANCE_DPOPTION,
#if(_DP_MST_SUPPORT == _ON)
    _OSD_ADVANCE_DPMST,
#endif
    _OSD_ADVANCE_DP_RESOLUTION,
    _OSD_ADVANCE_DUAL_DP_EDID,
    _OSD_ADVANCE_CLONE,
#endif
#if(_DSC_DECODER_SUPPORT == _ON)
    _OSD_ADVANCE_DSC,
#endif
#if(_USB_HUB_SUPPORT == _ON)
    _OSD_ADVANCE_TYPEC_MODE,
#endif

#if(_HDMI_MULTI_EDID_SUPPORT == _ON)
    _OSD_ADVANCE_HDMI_VERSIONS,
#endif

#if((_FREESYNC_SUPPORT == _ON) || (_FREESYNC_II_SUPPORT == _ON))
    _OSD_ADVANCE_FREESYNC,
#endif


#if(_LOCAL_DIMMING_FUNCTION == _ON)
    _OSD_ADVANCE_LOCALDIMMING,
    _OSD_ADVANCE_LOCALDIMMING_USER,
#endif

#if (_GLOBAL_DIMMING_FUNCTION == _ON)
    _OSD_ADVANCE_GLOBAL_DIMMING,
#endif
#if(_SDR_TO_HDR_FUNCTION == _ON)
    _OSD_ADVANCE_SDR_TO_HDR,
#endif

#if(_PIXEL_SHIFT_SUPPORT == _ON)
    _OSD_ADVANCE_PIXELSHIFT,
#endif

#if(_LOCAL_CONTRAST_FUNCTION == _ON)
    _OSD_ADVANCE_LOCAL_CONTRAST,
#endif

#if(_ADVANCED_LOCAL_CONTRAST_SUPPORT == _ON)
    _OSD_ADVANCE_LOCAL_CONTRAST_USER,
#endif

#if(_USB_HUB_SUPPORT == _ON)
    _OSD_ADVANCE_HUB_SWITCH,
#endif
#if(_EAGLE_SIGHT_SUPPORT == _ON)
    _OSD_ADVANCE_EAGLE_SIGHT,
#endif

#if(_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
    _OSD_ADVANCE_MBR,
#endif

#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
    _OSD_ADVANCE_DP_AUXLESS_ALPM,
#endif

#if(_ADAPTIVESYNC_SUPPORT == _ON)
    _OSD_ADVANCE_DP_ADAPTIVESYNC,
#endif

#if(_PR_MODE_SUPPORT == _ON)
    _OSD_ADVANCE_PANEL_REPLAY,
#endif

#if(_SDR_PLUS_FUNCTION == _ON)
    _OSD_ADVANCE_SDR_PLUS,
    _OSD_ADVANCE_SDR_PLUS_ADJ,
#endif

#if(_IMMERSIVE_NIGHT_SNIPER_FUNCTION == _ON)
    _OSD_ADVANCE_NIGHT_SNIPER,
#endif

#if(_ANTI_ALIASING_FUNCTION == _ON)
    _OSD_ADVANCE_ANTI_ALIASING,
#endif

    _OSD_ADVANCE_ENERGY_SAVE,
};

#define _OSD_ADVANCE_ITEM_AMOUNT   (sizeof(tOSD_ADVANCE_ITEM_PRI))
//--------------------------------------------------
// Definitions of Audio OSD ITEM
//--------------------------------------------------

//following order could modify by User
BYTE code tOSD_AUDIO_ITEM_PRI[] =
{
    _OSD_AUDIO_VOLUME,
    _OSD_AUDIO_MUTE,
#if(_SLEEP_AUDIO_SUPPORT == _ON)
    _OSD_AUDIO_STAND_ALONG,
#endif
    _OSD_AUDIO_AUDIO_SOURCE,
#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
    _OSD_AUDIO_AUDIO_SELF_TEST,
#endif
#if(_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE)
    _OSD_TTS_FUNCTION,
    _OSD_TTS_TEXT_VOLUME,
    _OSD_TTS_AUDIO_VOLUME,
#endif // End of #if(_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE)
};
#define _OSD_AUDIO_ITEM_AMOUNT     (sizeof(tOSD_AUDIO_ITEM_PRI))

//--------------------------------------------------
// Definitions of Other OSD ITEM
//--------------------------------------------------
//following order could modify by User
BYTE code tOSD_OTHER_ITEM_PRI[] =
{
    _OSD_OTHER_RESET,
    _OSD_OTHER_MENU_TIME,
    _OSD_OTHER_OSD_HPOS,
    _OSD_OTHER_OSD_VPOS,
    _OSD_OTHER_LANGUAGE,
    _OSD_OTHER_TRNASPARENCY,
#if((_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE) || (_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE))
    _OSD_OTHER_ROTATE,
#endif
    _OSD_OTHER_BORDER_WIDTH,
    _OSD_OTHER_BORDER_COLOR,
    _OSD_EXIT_HOTKEY,
};
#define _OSD_OTHER_ITEM_AMOUNT     (sizeof(tOSD_OTHER_ITEM_PRI))
//--------------------------------------------------
// Definitions of Muti Display ITEM
//--------------------------------------------------
//following order could modify by User
BYTE code tOSD_MUTIP_ITEM_PRI[] =
{
    _OSD_MUTIP_MODE,
    _OSD_MUTIP_SELECTREGION,
    _OSD_MUTIP_INPUT_SWAP,
    _OSD_MUTIP_LR_RATIO,
    _OSD_MUTIP_PIP_POSITION,
    _OSD_MUTIP_PIP_POSITION_USER,
#if(_PIP_TRANSPARENCY_SUPPORT == _ON)
    _OSD_MUTIP_PIP_TRANSPARENCY,
#endif
    _OSD_MUTIP_PIP_SIZE,
#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
    _OSD_MUTIP_PXP_MST,
#endif

};
#define _OSD_MUTIP_ITEM_AMOUNT     (sizeof(tOSD_MUTIP_ITEM_PRI))

//--------------------------------------------------
// Definitions of HDR OSD ITEM
//--------------------------------------------------

//following order could modify by User
BYTE code tOSD_HDR_ITEM_PRI[] =
{
    _OSD_HDR_MODE,
    _OSD_HDR_DARK_ENHANCE,
    _OSD_HDR_SHARP_ENHANCE,
    _OSD_HDR_CONTRAST,
#if(_HDR10_COLOR_ENHANCE_FUNCTION == _ON)
    _OSD_HDR_COLOR_ENHANCE,
#endif
#if(_HDR10_LIGHT_ENHANCE_FUNCTION == _ON)
    _OSD_HDR_LIGHT_ENHANCE,
#endif
#if(_HLG_SUPPORT == _ON)
    _OSD_HDR_HLG_OOTF,
#endif
};
#define _OSD_HDR_ITEM_AMOUNT       (sizeof(tOSD_HDR_ITEM_PRI))

//--------------------------------------------------
// Definitions of Input OSD ITEM
//--------------------------------------------------
//following order could modify by User
BYTE code tOSD_INPUT_ITEM_PRI[] =
{
    _OSD_SOURCE_1P,
    _OSD_SOURCE_2P,
    _OSD_SOURCE_3P,
    _OSD_SOURCE_4P,
};
#define _OSD_INPUT_ITEM_AMOUNT     (sizeof(tOSD_INPUT_ITEM_PRI))
#if(_DM_FUNCTION == _ON)
//--------------------------------------------------
// Definitions of DOBLY ITEM
//--------------------------------------------------

//following order could modify by User
BYTE code tOSD_DVISION_ITEM_PRI[] =
{
    _OSD_DVISION,
    _OSD_DVISION_PICTURE,
    _OSD_DVISION_BACKLIGHT,
    _OSD_DVISION_BRIGHTNESS,
    _OSD_DVISION_CONTRAST,
    // _OSD_DVISION_SATURATION,
    _OSD_DVISION_RESET,
    _OSD_DVISION_NOTIFICATION,
};
#define _OSD_DVISION_ITEM_AMOUNT   (sizeof(tOSD_DVISION_ITEM_PRI))
#define _DM_ROW_OFFSET             8
#endif

#if(_AUDIO_ARC_SUPPORT == _ON)
//--------------------------------------------------
// Definitions of Audio OSD ITEM
//--------------------------------------------------
//following order could modify by User
BYTE code tOSD_AUDIO_ARC_ITEM_PRI[] =
{
    _OSD_AUDIO_ARC_OUTPUT,
    _OSD_AUDIO_ARC_INPUTPORT,
    _OSD_AUDIO_ARC_MODE,
    _OSD_AUDIO_ARC_MUTE,
    _OSD_AUDIO_ARC_CHANEL,
};
#define _OSD_AUDIO_ARC_ITEM_AMOUNT (sizeof(tOSD_AUDIO_ARC_ITEM_PRI))
#endif

//STEP 5 //add New Item to any category above
//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
#if(_PIXEL_SHIFT_SUPPORT == _ON)
bit g_bflagMinuteON = _FALSE;
#endif

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
WORD OsdDisplayGetSourcePortString(EnumInputPort enumInputPort);
#if(_VGA_SUPPORT == _ON)
EnumStringIndex OsdDisplayGetVGAModeString(bit bUserMode);
#endif
#if(_DIGITAL_PORT_SUPPORT == _ON)
EnumStringIndex OsdDisplayGetShowHDCPEnable(EnumHDCPType enumHDCPType);
#endif

void OsdDispDisableOsd(void);
void OsdDispSetPosition(BYTE ucType, EnumOsdPositionType enumOsdPositionType, WORD usHPos, WORD usVPos);
void OsdDispMainMenuKeyInfo(BYTE ucItem, BYTE ucState);
void OsdDispMainMenu(void);
void OsdDispSliderAndNumber(WORD usOsdState, WORD usValue);
WORD OsdDisplayDetOverRange(WORD usValue, WORD usMax, WORD usMin, bit bCycle);
void OsdDisplaySixColorGetOneColor(EnumSelRegion enumSelRegion, BYTE ucColor);
void OsdDisplaySixColorSetOneColor(EnumSelRegion enumSelRegion, BYTE ucColor);
#if(_SIX_COLOR_SUPPORT == _ON)
void OsdDisplaySixColorGetOneColorData(EnumSelRegion enumSelRegion, BYTE ucColor, StructICMSetting *pstICMData);
#endif
void OsdDispHotKeyOptionMenu(void);
void OsdDispHotKeySourceMenuIcon(BYTE ucPort);
void OsdDispHotKeySourceMenuSwitch(BYTE ucPort);
void OsdDispHotKeySourceMenu(void);
void OsdDispPanelUniformityMsgSwitch(void);
void OsdDispOsdMessage(EnumOSDDispMsg enumMessage);
#if(_DM_FUNCTION == _ON)
void OsdDispOsdDMMessage(EnumOSDDispMsg enumMessage);
#endif

#if(_VGA_SUPPORT == _ON)
void OsdDispAutoConfigProc(void);
void OsdDisplayAutoBalanceProc(void);
#endif
void OsdDispOsdReset(void);
#if(_DP_SUPPORT == _ON)
void OsdDispResetDpCapabilitySwitch(void);
#endif
void OsdDispShowLogo(void);
#if(_GOSD_SUPPORT == _ON)
void OsdDispGosdShowLogo(void);
#endif
void OsdDispMpDisplayStateNotice(WORD usRow, WORD usCol, BYTE ucNoticeInfo, EnumDisplayRegion enumDisplayRegion, BYTE ucFontIndex);
#if((_4P_DISPLAY_SUPPORT == _ON) || (_2P_DISPLAY_SUPPORT == _ON) || (_3P_DISPLAY_SUPPORT == _ON))
void OsdDispMpDisplayStateNoticeFontB(WORD usRow, WORD usCol, BYTE ucNoticeInfo, EnumDisplayRegion enumDisplayRegion, BYTE ucFontIndex);
#endif
void OsdDispMpUpdateDisplayStateNotice(bit bOn, EnumDisplayRegion enumDisplayRegion);
#if((_2P_DISPLAY_SUPPORT == _ON) || (_4P_DISPLAY_SUPPORT == _ON) || (_3P_DISPLAY_SUPPORT == _ON))
BYTE OsdDispMpDisplayStateGetNoticeType(EnumDisplayRegion enumDisplayRegion, bit bOn);
#endif
#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
void OsdDispMpDisplayStateNotice_2P_LR(BYTE ucNoticeL, BYTE ucNoticeR);
#endif
#if(_2P_PBP_TB_DISPLAY_SUPPORT == _ON)
void OsdDispMpDisplayStateNotice_2P_TB(BYTE ucNoticeT, BYTE ucNoticeB);
#endif
#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
void OsdDispMpDisplayStateNotice_2P_PIP(BYTE ucNoticeMain, BYTE ucNoticeSub);
#endif
#if(_3P_FLAG_DISPLAY_SUPPORT == _ON)
void OsdDispMpDisplayStateNotice_3P_FLAG(BYTE ucNotice1P, BYTE ucNotice2P, BYTE ucNotice3P);
#endif
#if(_3P_SKEW_LR_DISPLAY_SUPPORT == _ON)
void OsdDispMpDisplayStateNotice_3P_SKEWL(BYTE ucNotice1P, BYTE ucNotice2P, BYTE ucNotice3P);
void OsdDispMpDisplayStateNotice_3P_SKEWR(BYTE ucNotice1P, BYTE ucNotice2P, BYTE ucNotice3P);
#endif
#if(_3P_SKEW_TB_DISPLAY_SUPPORT == _ON)
void OsdDispMpDisplayStateNotice_3P_SKEWT(BYTE ucNotice1P, BYTE ucNotice2P, BYTE ucNotice3P);
void OsdDispMpDisplayStateNotice_3P_SKEWB(BYTE ucNotice1P, BYTE ucNotice2P, BYTE ucNotice3P);
#endif
#if(_4P_DISPLAY_SUPPORT == _ON)
void OsdDispMpDisplayStateNotice_4P(BYTE ucNotice1P, BYTE ucNotice2P, BYTE ucNotice3P, BYTE ucNotice4P);
#endif
WORD OsdDisp2ndMenuStringGet(BYTE ucIndex, EnumOsdItem enumOsdItem);
bit OsdDisp2ndMenuCheck(WORD usOsdState);
void OsdDisp2ndMenuEnter(BYTE ucIndex, WORD usOsdState);
bit OsdDisp2ndMutiPSelectbyKey(void);
bit OsdDisp2ndPictureSelectbyKey(void);
bit OsdDisp2ndDisplaySelectbyKey(void);
bit OsdDisp2ndAdvanceSelectbyKey(void);
bit OsdDisp2ndAudioSelectbyKey(void);
bit OsdDisp2ndOtherSelectbyKey(void);
bit OsdDisp2ndHdrSelectbyKey(void);
bit OsdDisp2ndQuicklinkSelectbyKey(void);
bit OsdDisp2ndInputSelectbyKey(void);
#if(_DM_FUNCTION == _ON)
bit OsdDisp2ndDVisionSelectbyKey(void);
#endif
void OsdDisp1stMenuIconString(BYTE ucIconPos, WORD usIcon, BYTE ucColor);
void OsdDisp1stMenu(void);
void OsdDisp1stMenuIcon(void);
void OsdDisp2ndMenuString(BYTE ucIconPos, WORD usString, BYTE ucColor);
void OsdDisp2ndMenuStringSwitch(EnumOsdItem enumOsdItem);
void OsdDisp1stMenuCursor(BYTE ucIdx);
void OsdDisp2ndMenuCursor(BYTE ucIdex);
void OsdDisp1stMenuSelectbyKey(void);
void OsdDisp1stMenuEnterCheck(void);
void OsdDispItemValueUpdate(EnumOsdItem enumOsdItem);
void OsdDisp4thItemValueUpdate(WORD usOsdState);
void OsdMenu3rdFrame(void);
void OsdDisp3rdItemAdj(EnumOsdItem enumOsdItem, bit bitbAdjShow);
void OsdDisp4thItemAdj(bit bitbAdjShow);
void OsdDisp3rdListItemAdj(EnumOsdItem enumOsdItem, bit bitbAdjShow);
void OsdDispHotKeyMenuListItemAdj(bit bitbAdjShow);
void OsdDisp4thListItemAdj(bit bitbAdjShow);
void OsdDisp3rdBartemAdj(bit bitbAdjShow);
void OsdDispSubMenuListCursor(BYTE ucIdex);
void OsdDispSubMenu4thListCursor(BYTE ucIdex);
void OsdDisp3rdMenuAdjorShow(WORD usOsdState, WORD usValue, bit bitbAdjShow);
void OsdDisp3rdMenuReDraw(WORD usOsdState);
void OsdDisp4thMenuEnter(WORD usOsdState);
void OsdDisp4thMenuListCursor(BYTE ucIdex, BYTE ucOffse);
void OsdDisp4thMenuInFoBlock(EnumStringIndex enumString);
void OsdDisp4thMenuTitle(void);
bit OsdDisp3rdItemCheck(EnumOsdItem enumOsdItem, BYTE ucIdx);
EnumOsdMenuStatus OsdDispGetUpLayer(EnumOsdItem enumOsdItem);
BYTE OsdDispGetOsdItemIdx(EnumOsdItem enumOsdItem);
void OsdDispDirectMenu(EnumOsdItem enumOsdItem);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description : Get Select Region is Full or not
// Input Value : None
// Output Value :
//--------------------------------------------------
bit OsdDisplayGetSelectRegFullStatus(void)
{
    switch(GET_OSD_DISPLAY_MODE())
    {
        case _OSD_DM_2P_LR:
            if(GET_OSD_SELECT_REGION() == _OSD_SR_2P_LR_FULL)
            {
                return _TRUE;
            }
            break;
        case _OSD_DM_2P_TB:
            if(GET_OSD_SELECT_REGION() == _OSD_SR_2P_TB_FULL)
            {
                return _TRUE;
            }
            break;
        case _OSD_DM_2P_PIP:
            if(GET_OSD_SELECT_REGION() == _OSD_SR_2P_PIP_FULL)
            {
                return _TRUE;
            }
            break;
        case _OSD_DM_4P:
            if(GET_OSD_SELECT_REGION() == _OSD_SR_4P_FULL)
            {
                return _TRUE;
            }
            break;
        case _OSD_DM_3P_FLAG:
            if(GET_OSD_SELECT_REGION() == _OSD_SR_3P_FLAG_FULL)
            {
                return _TRUE;
            }
            break;
        case _OSD_DM_3P_SKEW_L:
            if(GET_OSD_SELECT_REGION() == _OSD_SR_3P_SKEW_L_FULL)
            {
                return _TRUE;
            }
            break;
        case _OSD_DM_3P_SKEW_R:
            if(GET_OSD_SELECT_REGION() == _OSD_SR_3P_SKEW_R_FULL)
            {
                return _TRUE;
            }
            break;
        case _OSD_DM_3P_SKEW_T:
            if(GET_OSD_SELECT_REGION() == _OSD_SR_3P_SKEW_T_FULL)
            {
                return _TRUE;
            }
            break;
        case _OSD_DM_3P_SKEW_B:
            if(GET_OSD_SELECT_REGION() == _OSD_SR_3P_SKEW_B_FULL)
            {
                return _TRUE;
            }
            break;
        default:
            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description :
// Input Value : None
// Output Value : None
//--------------------------------------------------
WORD OsdDisplayGetSourcePortString(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
#if(_A0_INPUT_PORT_TYPE != _A0_NO_PORT)
        case _A0_INPUT_PORT:
            return _STRING_A0_PORT;
#endif
#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
        case _D0_INPUT_PORT:
            return _STRING_D0_PORT;
#endif
#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
        case _D1_INPUT_PORT:
            return _STRING_D1_PORT;
#endif
#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
        case _D2_INPUT_PORT:
            return _STRING_D2_PORT;
#endif
#if(_D9_INPUT_PORT_TYPE != _D9_NO_PORT)
        case _D9_INPUT_PORT:
            return _STRING_D9_PORT;
#endif
#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
        case _D3_INPUT_PORT:
            return _STRING_D3_PORT;
#endif
#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
        case _D4_INPUT_PORT:
            return _STRING_D4_PORT;
#endif
#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
        case _D5_INPUT_PORT:
            return _STRING_D5_PORT;
#endif
#if(_D6_INPUT_PORT_TYPE != _D6_NO_PORT)
        case _D6_INPUT_PORT:
            return _STRING_D6_PORT;
#endif
#if(_D7_INPUT_PORT_TYPE != _D7_NO_PORT)
        case _D7_INPUT_PORT:
            return _STRING_D7_PORT;
#endif
#if(_D8_INPUT_PORT_TYPE != _D8_NO_PORT)
        case _D8_INPUT_PORT:
            return _STRING_D8_PORT;
#endif

        default:
            return _STRING_D0_PORT;
    }
}

#if(_VGA_SUPPORT == _ON)
//--------------------------------------------------
// Description :
// Input Value :
// Output Value :
//--------------------------------------------------
EnumStringIndex OsdDisplayGetVGAModeString(bit bUserMode)
{
    if(bUserMode == _USER_MODE_TYPE)
    {
        return _STRING_VGA_USER_MODE;
    }
    else
    {
        return _STRING_VGA_PRESET_MODE;
    }
}
#endif

#if(_DIGITAL_PORT_SUPPORT == _ON)
//--------------------------------------------------
// Description  : return HDCP version string (ex: HDCP enabled)
// Input Value  : ucVersion: HDCP version
// Output Value : formatted string pointer
//--------------------------------------------------
EnumStringIndex OsdDisplayGetShowHDCPEnable(EnumHDCPType enumHDCPType)
{
    switch(enumHDCPType)
    {
        case _HDCP_14:
            // print "HDCP 1.4 Sink"
            return _STRING_HDCP_14;

        case _HDCP_22:
            // print "HDCP 2.2 Sink"
            return _STRING_HDCP_22;

        case _HDCP_14_REPEATER:
            // print "HDCP 1.4 Repeater"
            return _STRING_HDCP_14_REPEATER;

        case _HDCP_22_REPEATER:
            // print "HDCP 2.2 Repeater"
            return _STRING_HDCP_22_REPEATER;

        case _HDCP_NONE:
        default:
            // print "HDCP disable"
            return _STRING_HDCP_NONE;
    }
}
#endif

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdDispPopMenuCheck(void)
{
    if((SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK) &&
       (SysRegionCheckAllDisplayState(_DISPLAY_STATE_NO_SIGNAL) == _FALSE))
    {
        if(GET_OSD_STATE() == _MENU_NONE)
        {
            if(GET_OSD_CROSSHAIR() != _CROSSHAIR_OFF)
            {
                OsdFontCrosshair();
            }
        }
    }
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdDispDisableOsd(void)
{
    SET_OSD_IN_FACTORY_MENU_STATUS(_FALSE);
    UserCommonTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_DISABLE);
    SET_OSD_STATE(_MENU_NONE);
    UserCommonTimerWaitForDDomainEvent(_EVENT_DEN_STOP);
    OsdFuncDisableOsd();
    g_ucOsdWidth = 0;
    g_ucOsdHeight = 0;
    g_ucOsdWidthB = 0;
    g_ucOsdHeightB = 0;
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdDispSetPosition(BYTE ucType, EnumOsdPositionType enumOsdPositionType, WORD usHPos, WORD usVPos)
{
    DWORD ulX = 0;
    DWORD ulY = 0;
    BYTE ucFonWidth = 12;
    BYTE ucFonHeight = 18;
    BYTE ucHorizontalDelayStep = 1;
    BYTE ucTempWidth = g_ucOsdWidth;
    BYTE ucTempHeight = g_ucOsdHeight;

    if((enumOsdPositionType == _OSD_POSITION_GLOBAL_B) ||
       (enumOsdPositionType == _OSD_POSITION_FONT_B))
    {
        ucTempWidth = g_ucOsdWidthB;
        ucTempHeight = g_ucOsdHeightB;
    }

    if(GET_OSD_DOUBLE_SIZE() == _ON)
    {
        ucFonWidth *= 2;
        ucFonHeight *= 2;
    }

    if(ucType == _POS_PERCENT)
    {
#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
        if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) ||
           (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
        {
            ulX = ((((DWORD)(_PANEL_DH_WIDTH) - (DWORD)ucTempWidth * ucFonHeight) / ucHorizontalDelayStep) * usHPos) / _OSD_H_POS_MAX;
            ulY = (((DWORD)_PANEL_DV_HEIGHT - (DWORD)ucTempHeight * ucFonWidth) * usVPos) / _OSD_V_POS_MAX;
        }
        else
        {
            ulX = ((((DWORD)(_PANEL_DH_WIDTH) - (DWORD)ucTempWidth * ucFonWidth) / ucHorizontalDelayStep) * usHPos) / _OSD_H_POS_MAX;
            ulY = (((DWORD)_PANEL_DV_HEIGHT - (DWORD)ucTempHeight * ucFonHeight) * usVPos) / _OSD_V_POS_MAX;
        }
#elif(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
        if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) || (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
        {
            ulX = ((((DWORD)(_PANEL_DH_WIDTH) - (DWORD)ucTempHeight * ucFonHeight) / ucHorizontalDelayStep) * usHPos) / _OSD_H_POS_MAX;
            ulY = (((DWORD)_PANEL_DV_HEIGHT - (DWORD)ucTempWidth * ucFonWidth) * usVPos) / _OSD_V_POS_MAX;
        }
        else
        {
            ulX = ((((DWORD)(_PANEL_DH_WIDTH) - (DWORD)ucTempWidth * ucFonWidth) / ucHorizontalDelayStep) * usHPos) / _OSD_H_POS_MAX;
            ulY = (((DWORD)_PANEL_DV_HEIGHT - (DWORD)ucTempHeight * ucFonHeight) * usVPos) / _OSD_V_POS_MAX;
        }
#else
        ulX = ((((DWORD)(_PANEL_DH_WIDTH) - (DWORD)ucTempWidth * ucFonWidth) / ucHorizontalDelayStep) * usHPos) / _OSD_H_POS_MAX;
        ulY = (((DWORD)_PANEL_DV_HEIGHT - (DWORD)ucTempHeight * ucFonHeight) * usVPos) / _OSD_V_POS_MAX;
#endif
#if((_GOSD_SUPPORT == _ON) && ((_IS_MAIN_PROCESS_CPU == _TRUE) || (_CPU32_SCPU_FW_MODE == _SCPU_FW_MODE_ACTOR)))
        if((GET_OSD_STATE() > _MENU_NONE) &&
           (GET_OSD_STATE() < _MENU_HOTKEY_SOURCE))
        {
            WORD usGosdDispWidth = (WORD)ucTempWidth * ucFonWidth;
            WORD usGosdDispHeight = (WORD)ucTempHeight * ucFonHeight;
            WORD usGosdWinWidth = usGosdDispWidth / ((GET_OSD_DOUBLE_SIZE() == _ON) ? (2) : (1));
            WORD usGosdWinHeight = usGosdDispHeight / ((GET_OSD_DOUBLE_SIZE() == _ON) ? (2) : (1));
            WORD usRotationSize = MAXOF(usGosdWinWidth, usGosdWinHeight);
            DWORD ulRotationSurfaceOffset = 0;
            StructGosdDisplayOsdParam stDisplayParam;
            stDisplayParam.ulSurfaceId = _GOSD_SURFACE_MAINMENUBG_ID;

            switch(GET_OSD_ROTATE_STATUS())
            {
                case _OSD_ROTATE_DEGREE_90:
                    ulRotationSurfaceOffset = 1;
                    stDisplayParam.stWinRect.stSize.usW = usGosdWinHeight;
                    stDisplayParam.stWinRect.stSize.usH = usGosdWinWidth;
                    stDisplayParam.stWinRect.stPosition.usX = usRotationSize - stDisplayParam.stWinRect.stSize.usW;
                    stDisplayParam.stWinRect.stPosition.usY = 0;
                    stDisplayParam.stDispRect.stSize.usW = usGosdDispHeight;
                    stDisplayParam.stDispRect.stSize.usH = usGosdDispWidth;
                    stDisplayParam.stDispRect.stPosition.usX = ((((DWORD)(_PANEL_DH_WIDTH) - usGosdDispHeight) / ucHorizontalDelayStep) * (_OSD_H_POS_MAX - usHPos)) / _OSD_H_POS_MAX;
                    stDisplayParam.stDispRect.stPosition.usY = (((DWORD)_PANEL_DV_HEIGHT - usGosdDispWidth) * usVPos) / _OSD_V_POS_MAX;
                    break;
                case _OSD_ROTATE_DEGREE_270:
                    ulRotationSurfaceOffset = 1;
                    stDisplayParam.stWinRect.stSize.usW = usGosdWinHeight;
                    stDisplayParam.stWinRect.stSize.usH = usGosdWinWidth;
                    stDisplayParam.stWinRect.stPosition.usX = 0;
                    stDisplayParam.stWinRect.stPosition.usY = usRotationSize - stDisplayParam.stWinRect.stSize.usH;
                    stDisplayParam.stDispRect.stSize.usW = usGosdDispHeight;
                    stDisplayParam.stDispRect.stSize.usH = usGosdDispWidth;
                    stDisplayParam.stDispRect.stPosition.usX = ((((DWORD)(_PANEL_DH_WIDTH) - usGosdDispHeight) / ucHorizontalDelayStep) * usHPos) / _OSD_H_POS_MAX;
                    stDisplayParam.stDispRect.stPosition.usY = (((DWORD)_PANEL_DV_HEIGHT - usGosdDispWidth) * (_OSD_V_POS_MAX - usVPos)) / _OSD_V_POS_MAX;
                    break;
                case _OSD_ROTATE_DEGREE_180:
                    ulRotationSurfaceOffset = 1;
                    stDisplayParam.stWinRect.stSize.usW = usGosdWinWidth;
                    stDisplayParam.stWinRect.stSize.usH = usGosdWinHeight;
                    stDisplayParam.stWinRect.stPosition.usX = 0;
                    stDisplayParam.stWinRect.stPosition.usY = usRotationSize - stDisplayParam.stWinRect.stSize.usH;
                    stDisplayParam.stDispRect.stSize.usW = usGosdDispWidth;
                    stDisplayParam.stDispRect.stSize.usH = usGosdDispHeight;
                    stDisplayParam.stDispRect.stPosition.usX = ((((DWORD)(_PANEL_DH_WIDTH) - usGosdDispWidth) / ucHorizontalDelayStep) * (_OSD_H_POS_MAX - usHPos)) / _OSD_H_POS_MAX;
                    stDisplayParam.stDispRect.stPosition.usY = (((DWORD)_PANEL_DV_HEIGHT - usGosdDispHeight) * (_OSD_V_POS_MAX - usVPos)) / _OSD_V_POS_MAX;
                    break;
                default:
                case _OSD_ROTATE_DEGREE_0:
                    stDisplayParam.stWinRect.stSize.usW = usGosdWinWidth;
                    stDisplayParam.stWinRect.stSize.usH = usGosdWinHeight;
                    stDisplayParam.stWinRect.stPosition.usX = 0;
                    stDisplayParam.stWinRect.stPosition.usY = 0;
                    stDisplayParam.stDispRect.stSize.usW = usGosdDispWidth;
                    stDisplayParam.stDispRect.stSize.usH = usGosdDispHeight;
                    stDisplayParam.stDispRect.stPosition.usX = ((((DWORD)(_PANEL_DH_WIDTH) - usGosdDispWidth) / ucHorizontalDelayStep) * usHPos) / _OSD_H_POS_MAX;
                    stDisplayParam.stDispRect.stPosition.usY = (((DWORD)_PANEL_DV_HEIGHT - usGosdDispHeight) * usVPos) / _OSD_V_POS_MAX;
                    break;
            }
            stDisplayParam.stDispRect.stPosition.usX = MINOF(stDisplayParam.stDispRect.stPosition.usX, UserCommonOsdGetMaxHPos(enumOsdPositionType));

            UserCommonGosdDisplaySurfaceSync(_GOSD_PLANE_OSD1, stDisplayParam.ulSurfaceId + ulRotationSurfaceOffset, &stDisplayParam.stWinRect, &stDisplayParam.stDispRect, _DB_APPLY_POLLING, _GOSD_DEFAULT_POLLING_MS);
        }
#endif // end of #if(_GOSD_SUPPORT == _ON && _IS_MAIN_PROCESS_CPU == _TRUE)

    }
    else
    {
        // Notice!!! if osd set double size need to check real position
        switch(GET_OSD_ROTATE_STATUS())
        {
            case _OSD_ROTATE_DEGREE_270:
                ulX = usHPos;
                ulY = _PANEL_DV_HEIGHT - usVPos - (DWORD)ucTempWidth * ucFonWidth;
                break;
            case _OSD_ROTATE_DEGREE_90:
                ulX = _PANEL_DH_WIDTH - usHPos - (DWORD)ucTempHeight * ucFonHeight;
                ulY = usVPos;
                break;
            default:
                ulX = usHPos;
                ulY = usVPos;
                break;
        }
    }

    if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) ||
       (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
    {
        DWORD ulTempWidth = 0;

        ulTempWidth = ulX;
        ulX = ulY;
        ulY = ulTempWidth;
    }

    OsdFuncSetPosition(enumOsdPositionType, ulX, ulY);
}


//--------------------------------------------------
// Description :
// Input Value :
// Output Value :
//--------------------------------------------------
void OsdDispMainMenuKeyInfo(BYTE ucItem, BYTE ucState)
{
    // _KEY_INFO_ALL
    BYTE ucColor = COLOR(_CP_BLUE_200, _CP_BG);
    BYTE ucRow = 20;
    BYTE ucCol = 22;
    BYTE ucInterval = 5;
    BYTE ucIsMainMenu = _FALSE;

#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
    if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) ||
       (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
    {
        if((g_ucOsdWidth == _OSD_MAIN_MENU_HEIGHT) &&
           (g_ucOsdHeight == _OSD_MAIN_MENU_WIDTH))
        {
            ucIsMainMenu = _TRUE;
        }
    }
    else
#endif
    {
        if((g_ucOsdWidth == _OSD_MAIN_MENU_WIDTH) &&
           (g_ucOsdHeight == _OSD_MAIN_MENU_HEIGHT))
        {
            ucIsMainMenu = _TRUE;
        }
    }

    if(ucIsMainMenu == _FALSE)
    {
        return;
    }

    if((ucState == _OSD_SELECT) || (ucState == _OSD_HIGHLIGHT))
    {
        ucColor = COLOR(_CP_PINK, _CP_BG);
        UserCommonTimerReactiveTimerEvent(SEC(0.05), _USER_TIMER_EVENT_OSD_KEYINFO_UNHIGHLIGHT);
    }

    switch(ucItem)
    {
        case _KEY_INFO_ENTER:
            if((ucState == _OSD_SELECT) || (ucState == _OSD_UNSELECT))
            {
                OsdFontPut1BitTable(ucRow, (ucCol + (ucInterval * 0)), tOSD_iKEY_ENTER, ucColor);
            }
            else if((ucState == _OSD_HIGHLIGHT) || (ucState == _OSD_UNHIGHLIGHT))
            {
                OsdFuncChangeColor1Bit(ucRow, (ucCol + (ucInterval * 0)), WIDTH(2), HEIGHT(2), ucColor, _FONTFROM_0_255);
            }
            else
            {
                OsdFuncClearOsd(ucRow, (ucCol + (ucInterval * 0)), WIDTH(2), HEIGHT(2));
            }

            break;

        case _KEY_INFO_EXIT:
            if((ucState == _OSD_SELECT) || (ucState == _OSD_UNSELECT))
            {
                OsdFontPut1BitTable(ucRow, (ucCol + (ucInterval * 1)), tOSD_iKEY_EXIT, ucColor);
            }
            else if((ucState == _OSD_HIGHLIGHT) || (ucState == _OSD_UNHIGHLIGHT))
            {
                OsdFuncChangeColor1Bit(ucRow, (ucCol + (ucInterval * 1)), WIDTH(2), HEIGHT(2), ucColor, _FONTFROM_0_255);
            }
            else
            {
                OsdFuncClearOsd(ucRow, (ucCol + (ucInterval * 1)), WIDTH(2), HEIGHT(2));
            }
            break;

        case _KEY_INFO_LEFT:
            if((ucState == _OSD_SELECT) || (ucState == _OSD_UNSELECT))
            {
                OsdFontPut1BitTable(ucRow, (ucCol + (ucInterval * 2)), tOSD_iKEY_LEFT, ucColor);
            }
            else if((ucState == _OSD_HIGHLIGHT) || (ucState == _OSD_UNHIGHLIGHT))
            {
                OsdFuncChangeColor1Bit(ucRow, (ucCol + (ucInterval * 2)), WIDTH(2), HEIGHT(2), ucColor, _FONTFROM_0_255);
            }
            else
            {
                OsdFuncClearOsd(ucRow, (ucCol + (ucInterval * 2)), WIDTH(2), HEIGHT(2));
            }
            break;

        case _KEY_INFO_RIGHT:
            if((ucState == _OSD_SELECT) || (ucState == _OSD_UNSELECT))
            {
                OsdFontPut1BitTable(ucRow, (ucCol + (ucInterval * 3)), tOSD_iKEY_RIGHT, ucColor);
            }
            else if((ucState == _OSD_HIGHLIGHT) || (ucState == _OSD_UNHIGHLIGHT))
            {
                OsdFuncChangeColor1Bit(ucRow, (ucCol + (ucInterval * 3)), WIDTH(2), HEIGHT(2), ucColor, _FONTFROM_0_255);
            }
            else
            {
                OsdFuncClearOsd(ucRow, (ucCol + (ucInterval * 3)), WIDTH(2), HEIGHT(2));
            }
            break;

        case _KEY_INFO_BACK:
            if((ucState == _OSD_SELECT) || (ucState == _OSD_UNSELECT))
            {
                OsdFontPut1BitTable(ucRow, (ucCol + (ucInterval * 1)), tOSD_iKEY_BACK, ucColor);
            }
            else if((ucState == _OSD_HIGHLIGHT) || (ucState == _OSD_UNHIGHLIGHT))
            {
                OsdFuncChangeColor1Bit(ucRow, (ucCol + (ucInterval * 1)), WIDTH(2), HEIGHT(2), ucColor, _FONTFROM_0_255);
            }
            else
            {
                OsdFuncClearOsd(ucRow, (ucCol + (ucInterval * 1)), WIDTH(2), HEIGHT(2));
            }
            break;

        case _KEY_INFO_ALL:
            if((ucState == _OSD_SELECT) || (ucState == _OSD_UNSELECT))
            {
                OsdFontPut1BitTable(ucRow, (ucCol + (ucInterval * 0)), tOSD_iKEY_ENTER, ucColor);
                OsdFontPut1BitTable(ucRow, (ucCol + (ucInterval * 1)), tOSD_iKEY_EXIT, ucColor);
                OsdFontPut1BitTable(ucRow, (ucCol + (ucInterval * 2)), tOSD_iKEY_LEFT, ucColor);
                OsdFontPut1BitTable(ucRow, (ucCol + (ucInterval * 3)), tOSD_iKEY_RIGHT, ucColor);
            }
            else if((ucState == _OSD_HIGHLIGHT) || (ucState == _OSD_UNHIGHLIGHT))
            {
                OsdFuncChangeColor1Bit(ucRow, (ucCol + (ucInterval * 0)), WIDTH(2), HEIGHT(2), ucColor, _FONTFROM_0_255);
                OsdFuncChangeColor1Bit(ucRow, (ucCol + (ucInterval * 1)), WIDTH(2), HEIGHT(2), ucColor, _FONTFROM_0_255);
                OsdFuncChangeColor1Bit(ucRow, (ucCol + (ucInterval * 2)), WIDTH(2), HEIGHT(2), ucColor, _FONTFROM_0_255);
                OsdFuncChangeColor1Bit(ucRow, (ucCol + (ucInterval * 3)), WIDTH(2), HEIGHT(2), ucColor, _FONTFROM_0_255);
            }
            else
            {
                OsdFuncClearOsd(ucRow, (ucCol + (ucInterval * 0)), WIDTH(2), HEIGHT(2));
                OsdFuncClearOsd(ucRow, (ucCol + (ucInterval * 1)), WIDTH(2), HEIGHT(2));
                OsdFuncClearOsd(ucRow, (ucCol + (ucInterval * 2)), WIDTH(2), HEIGHT(2));
                OsdFuncClearOsd(ucRow, (ucCol + (ucInterval * 3)), WIDTH(2), HEIGHT(2));
            }
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdDispMainMenu(void)
{
    OsdDisp1stMenu();
}

//--------------------------------------------------
// Description    :
// Input Value    : None
// Output Value : None
//--------------------------------------------------
void OsdDispSliderAndNumber(WORD usOsdState, WORD usValue)
{
    if((GET_OSD_STATE() >= _MENU_DISPLAYMODE) && (GET_OSD_STATE() < _MENU_HOTKEY_SOURCE))
    {
        OsdDisp3rdMenuAdjorShow(usOsdState, usValue, _ON);
    }
    else
    {
        // support direct jump to sub item
        OsdDisp3rdMenuAdjorShow(usOsdState, usValue, _OFF);
    }
}
//--------------------------------------------------
// Description    :
// Input Value    : None
// Output Value : None
//--------------------------------------------------
WORD OsdDisplayDetOverRange(WORD usValue, WORD usMax, WORD usMin, bit bCycle)
{
    switch(GET_KEYMESSAGE())
    {
        case _RIGHT_KEY_MESSAGE:
            if(usValue >= usMax)
            {
                if(bCycle == _ON)
                {
                    return usMin;
                }
                else
                {
                    return usMax;
                }
            }
            else
            {
                usValue++;
            }

            break;

        case _LEFT_KEY_MESSAGE:
            if (usValue <= usMin)
            {
                if(bCycle == _ON)
                {
                    return usMax;
                }
                else
                {
                    return usMin;
                }
            }
            else
            {
                usValue--;
            }
            break;

        default:
            break;
    }

    return usValue;
}

//--------------------------------------------------
// Description  : Six Color Get One Color
// Input Value  : SixColor
// Output Value : None
//--------------------------------------------------
void OsdDisplaySixColorGetOneColor(EnumSelRegion enumSelRegion, BYTE ucColor)
{
    EnumHLWType enumHLWType = UserCommonColorGetSelectRegionHLWArea(enumSelRegion);
    BYTE ucType = (enumHLWType == _HLW_OUTSIDE_WINDOW) ? _OUTSIDE : _INSIDE;
    StructOsdRegionDataSixColorType *pstData = &g_pstOsdRegionData[ucType].stSixColorData;

    switch(ucColor)
    {
        // DOUBLE CHECK HERE
        case _SIXCOLOR_R:
            SET_OSD_SIX_COLOR_HUE(pstData->ucSixColorHueR);
            SET_OSD_SIX_COLOR_SATURATION(pstData->ucSixColorSaturationR);
            break;

        case _SIXCOLOR_Y:
            SET_OSD_SIX_COLOR_HUE(pstData->ucSixColorHueY);
            SET_OSD_SIX_COLOR_SATURATION(pstData->ucSixColorSaturationY);
            break;

        case _SIXCOLOR_G:
            SET_OSD_SIX_COLOR_HUE(pstData->ucSixColorHueG);
            SET_OSD_SIX_COLOR_SATURATION(pstData->ucSixColorSaturationG);
            break;

        case _SIXCOLOR_C:
            SET_OSD_SIX_COLOR_HUE(pstData->ucSixColorHueC);
            SET_OSD_SIX_COLOR_SATURATION(pstData->ucSixColorSaturationC);
            break;

        case _SIXCOLOR_B:
            SET_OSD_SIX_COLOR_HUE(pstData->ucSixColorHueB);
            SET_OSD_SIX_COLOR_SATURATION(pstData->ucSixColorSaturationB);
            break;

        case _SIXCOLOR_M:
            SET_OSD_SIX_COLOR_HUE(pstData->ucSixColorHueM);
            SET_OSD_SIX_COLOR_SATURATION(pstData->ucSixColorSaturationM);
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Six Color Set One Color
// Input Value  : SixColor
// Output Value : None
//--------------------------------------------------
void OsdDisplaySixColorSetOneColor(EnumSelRegion enumSelRegion, BYTE ucColor)
{
    EnumHLWType enumHLWType = UserCommonColorGetSelectRegionHLWArea(enumSelRegion);
    BYTE ucType = (enumHLWType == _HLW_OUTSIDE_WINDOW) ? _OUTSIDE : _INSIDE;
    StructOsdRegionDataSixColorType *pstData = &g_pstOsdRegionData[ucType].stSixColorData;

    switch(ucColor)
    {
        case _SIXCOLOR_R:
            pstData->ucSixColorHueR = GET_OSD_SIX_COLOR_HUE();
            pstData->ucSixColorSaturationR = GET_OSD_SIX_COLOR_SATURATION();
            break;

        case _SIXCOLOR_Y:
            pstData->ucSixColorHueY = GET_OSD_SIX_COLOR_HUE();
            pstData->ucSixColorSaturationY = GET_OSD_SIX_COLOR_SATURATION();
            break;

        case _SIXCOLOR_G:
            pstData->ucSixColorHueG = GET_OSD_SIX_COLOR_HUE();
            pstData->ucSixColorSaturationG = GET_OSD_SIX_COLOR_SATURATION();
            break;

        case _SIXCOLOR_C:
            pstData->ucSixColorHueC = GET_OSD_SIX_COLOR_HUE();
            pstData->ucSixColorSaturationC = GET_OSD_SIX_COLOR_SATURATION();
            break;

        case _SIXCOLOR_B:
            pstData->ucSixColorHueB = GET_OSD_SIX_COLOR_HUE();
            pstData->ucSixColorSaturationB = GET_OSD_SIX_COLOR_SATURATION();
            break;

        case _SIXCOLOR_M:
            pstData->ucSixColorHueM = GET_OSD_SIX_COLOR_HUE();
            pstData->ucSixColorSaturationM = GET_OSD_SIX_COLOR_SATURATION();
            break;

        default:
            break;
    }
}

#if(_SIX_COLOR_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Six Color Get One Color for ICM data
// Input Value  : SixColor
// Output Value : None
//--------------------------------------------------
void OsdDisplaySixColorGetOneColorData(EnumSelRegion enumSelRegion, BYTE ucColor, StructICMSetting *pstICMData)
{
    EnumHLWType enumHLWType = UserCommonColorGetSelectRegionHLWArea(enumSelRegion);
    BYTE ucType = (enumHLWType == _HLW_OUTSIDE_WINDOW) ? _OUTSIDE : _INSIDE;
    StructOsdRegionDataSixColorType *pstData = &g_pstOsdRegionData[ucType].stSixColorData;

    switch(ucColor)
    {
        // DOUBLE CHECK HERE
        case _SIXCOLOR_R:
            pstICMData->unICMData.stICMSixColorData.ucSixColorHueR = pstData->ucSixColorHueR;
            pstICMData->unICMData.stICMSixColorData.ucSixColorSaturationR = pstData->ucSixColorSaturationR;
            break;

        case _SIXCOLOR_Y:
            pstICMData->unICMData.stICMSixColorData.ucSixColorHueY = pstData->ucSixColorHueY;
            pstICMData->unICMData.stICMSixColorData.ucSixColorSaturationY = pstData->ucSixColorSaturationY;
            break;

        case _SIXCOLOR_G:
            pstICMData->unICMData.stICMSixColorData.ucSixColorHueG = pstData->ucSixColorHueG;
            pstICMData->unICMData.stICMSixColorData.ucSixColorSaturationG = pstData->ucSixColorSaturationG;
            break;

        case _SIXCOLOR_C:
            pstICMData->unICMData.stICMSixColorData.ucSixColorHueC = pstData->ucSixColorHueC;
            pstICMData->unICMData.stICMSixColorData.ucSixColorSaturationC = pstData->ucSixColorSaturationC;
            break;

        case _SIXCOLOR_B:
            pstICMData->unICMData.stICMSixColorData.ucSixColorHueB = pstData->ucSixColorHueB;
            pstICMData->unICMData.stICMSixColorData.ucSixColorSaturationB = pstData->ucSixColorSaturationB;
            break;

        case _SIXCOLOR_M:
            pstICMData->unICMData.stICMSixColorData.ucSixColorHueM = pstData->ucSixColorHueM;
            pstICMData->unICMData.stICMSixColorData.ucSixColorSaturationM = pstData->ucSixColorSaturationM;
            break;

        default:
            break;
    }
}
#endif

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdDispHotKeyOptionMenu(void)
{
    OsdDispMainMenu();
    SET_OSD_ITEM_INDEX(0);
    OsdDisp2ndMenuReDraw(_MENU_QUICKLINK_ITEM, _HIGH);
}

//--------------------------------------------------
// Description :
// Input Value :
// Output Value :
//--------------------------------------------------
void OsdDispHotKeySourceMenuIcon(BYTE ucPort)
{
    BYTE ucCol = 5;

    if(GET_OSD_STATE() == _MENU_HOTKEY_SOURCE)
    {
        OsdFuncClearOsd(ROW(6), COL(13), WIDTH(47), HEIGHT(1));
        OsdPropPutStringCenter(ROW(6), COL(0), WIDTH(12), _PFONT_PAGE_1, _STRING_INPUT, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());

        // Left & Right Arrow
        OsdFontPut1Bit(ROW(3), COL(13), _iLEFT_00, COLOR(_CP_BLUE, _CP_BG));
        OsdFontPut1Bit(ROW(3) + 1, COL(13), _iLEFT_00 + 1, COLOR(_CP_BLUE, _CP_BG));

        OsdFontPut1Bit(ROW(3), COL(62), _iRIGHT_00, COLOR(_CP_BLUE, _CP_BG));
        OsdFontPut1Bit(ROW(3) + 1, COL(62), _iRIGHT_00 + 1, COLOR(_CP_BLUE, _CP_BG));

        if(ucPort <= _OSD_INPUT_D2)
        {
            // A0
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_1, _A0_INPUT_TYPE);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(ucCol + (12 * 1)), (_1DYNAMIC_ICON_START + (1 * 24)), _CP_BLUE, _CP_BG);
            OsdPropPutString(ROW(6), COL(ucCol + (12 * 1)), _PFONT_PAGE_1, _STRING_A0_PORT, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);

            // D0
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_2, _D0_INPUT_TYPE);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(ucCol + (12 * 2)), (_1DYNAMIC_ICON_START + (2 * 24)), _CP_BLUE, _CP_BG);
            OsdPropPutString(ROW(6), COL(ucCol + (12 * 2)), _PFONT_PAGE_1, _STRING_D0_PORT, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);

            // D1
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_3, _D1_INPUT_TYPE);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(ucCol + (12 * 3)), (_1DYNAMIC_ICON_START + (3 * 24)), _CP_BLUE, _CP_BG);
            OsdPropPutString(ROW(6), COL(ucCol + (12 * 3)), _PFONT_PAGE_1, _STRING_D1_PORT, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);

            // D2
            OsdFontVLCDynamicLoadIcon(_ICON_POS_DOWN_0, _D2_INPUT_TYPE);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(ucCol + (12 * 4)), (_1DYNAMIC_ICON_START + (4 * 24)), _CP_BLUE, _CP_BG);
            OsdPropPutString(ROW(6), COL(ucCol + (12 * 4)), _PFONT_PAGE_1, _STRING_D2_PORT, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
        }
        else if((ucPort > _OSD_INPUT_D2) && (ucPort <= _OSD_INPUT_D6))
        {
            // D3
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_1, _D3_INPUT_TYPE);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(ucCol + (12 * 1)), (_1DYNAMIC_ICON_START + (1 * 24)), _CP_BLUE, _CP_BG);
            OsdPropPutString(ROW(6), COL(ucCol + (12 * 1)), _PFONT_PAGE_1, _STRING_D3_PORT, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);

            // D4
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_2, _D4_INPUT_TYPE);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(ucCol + (12 * 2)), (_1DYNAMIC_ICON_START + (2 * 24)), _CP_BLUE, _CP_BG);
            OsdPropPutString(ROW(6), COL(ucCol + (12 * 2)), _PFONT_PAGE_1, _STRING_D4_PORT, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);

            // D5
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_3, _D5_INPUT_TYPE);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(ucCol + (12 * 3)), (_1DYNAMIC_ICON_START + (3 * 24)), _CP_BLUE, _CP_BG);
            OsdPropPutString(ROW(6), COL(ucCol + (12 * 3)), _PFONT_PAGE_1, _STRING_D5_PORT, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);

            // D6
            OsdFontVLCDynamicLoadIcon(_ICON_POS_DOWN_0, _D6_INPUT_TYPE);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(ucCol + (12 * 4)), (_1DYNAMIC_ICON_START + (4 * 24)), _CP_BLUE, _CP_BG);
            OsdPropPutString(ROW(6), COL(ucCol + (12 * 4)), _PFONT_PAGE_1, _STRING_D6_PORT, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
        }
#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
        else if((ucPort > _OSD_INPUT_D6) && (ucPort <= _OSD_INPUT_D9_D0)) // D7/D8/D9/D9_D0
        {
            // D7
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_1, _D7_INPUT_TYPE);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(ucCol + (12 * 1)), (_1DYNAMIC_ICON_START + (1 * 24)), _CP_BLUE, _CP_BG);
            OsdPropPutString(ROW(6), COL(ucCol + (12 * 1)), _PFONT_PAGE_1, _STRING_D7_PORT, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);

            // D8
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_2, _D8_INPUT_TYPE);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(ucCol + (12 * 2)), (_1DYNAMIC_ICON_START + (2 * 24)), _CP_BLUE, _CP_BG);
            OsdPropPutString(ROW(6), COL(ucCol + (12 * 2)), _PFONT_PAGE_1, _STRING_D8_PORT, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);

            // D9
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_3, _D9_INPUT_TYPE);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(ucCol + (12 * 3)), (_1DYNAMIC_ICON_START + (3 * 24)), _CP_BLUE, _CP_BG);
            OsdPropPutString(ROW(6), COL(ucCol + (12 * 3)), _PFONT_PAGE_1, _STRING_D9_PORT, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);

            // D9_D0
            OsdFontVLCDynamicLoadIcon(_ICON_POS_DOWN_0, _D9_INPUT_TYPE);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(ucCol + (12 * 4)), (_1DYNAMIC_ICON_START + (4 * 24)), _CP_BLUE, _CP_BG);
            OsdPropPutString(ROW(6), COL(ucCol + (12 * 4)), _PFONT_PAGE_1, _STRING_D9_D0_PORT, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
        }
        else // D9_d1/D9_D2/AUTO
        {
            // D9_D1
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_1, _D9_INPUT_TYPE);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(ucCol + (12 * 1)), (_1DYNAMIC_ICON_START + (1 * 24)), _CP_BLUE, _CP_BG);
            OsdPropPutString(ROW(6), COL(ucCol + (12 * 1)), _PFONT_PAGE_1, _STRING_D9_D1_PORT, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);

            // D9_D2
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_2, _D9_INPUT_TYPE);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(ucCol + (12 * 2)), (_1DYNAMIC_ICON_START + (2 * 24)), _CP_BLUE, _CP_BG);
            OsdPropPutString(ROW(6), COL(ucCol + (12 * 2)), _PFONT_PAGE_1, _STRING_D9_D2_PORT, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);

            // auto
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_3, _ICON_INPUT_AUTO);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(ucCol + (12 * 3)), (_1DYNAMIC_ICON_START + (3 * 24)), _CP_BLUE, _CP_BG);
            OsdPropPutStringCenter(ROW(6), COL(ucCol + (12 * 3)), WIDTH(7), _PFONT_PAGE_1, _STRING_AUTOSELECT_PORT, COLOR(_CP_BLUE, _CP_BG), GET_OSD_LANGUAGE());

            // None
            OsdFuncClearOsd(ROW(2), COL(ucCol + (12 * 4)), WIDTH(12), HEIGHT(5));

            // None
            // OsdFuncClearOsd(ROW(2), COL(ucCol + (12 *4)), WIDTH(12), HEIGHT(5));
        }
#else
        else
        {
            // D7
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_1, _D7_INPUT_TYPE);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(ucCol + (12 * 1)), (_1DYNAMIC_ICON_START + (1 * 24)), _CP_BLUE, _CP_BG);
            OsdPropPutString(ROW(6), COL(ucCol + (12 * 1)), _PFONT_PAGE_1, _STRING_D7_PORT, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);

            // D8
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_2, _D8_INPUT_TYPE);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(ucCol + (12 * 2)), (_1DYNAMIC_ICON_START + (2 * 24)), _CP_BLUE, _CP_BG);
            OsdPropPutString(ROW(6), COL(ucCol + (12 * 2)), _PFONT_PAGE_1, _STRING_D8_PORT, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);

            // auto
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_3, _ICON_INPUT_AUTO);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(ucCol + (12 * 3)), (_1DYNAMIC_ICON_START + (3 * 24)), _CP_BLUE, _CP_BG);
            OsdPropPutStringCenter(ROW(6), COL(ucCol + (12 * 3)), WIDTH(7), _PFONT_PAGE_1, _STRING_AUTOSELECT_PORT, COLOR(_CP_BLUE, _CP_BG), GET_OSD_LANGUAGE());

            // None
            OsdFuncClearOsd(ROW(2), COL(ucCol + (12 * 4)), WIDTH(12), HEIGHT(5));
        }
#endif
    }
}

//--------------------------------------------------
// Description :
// Input Value :
// Output Value :
//--------------------------------------------------
void OsdDispHotKeySourceMenuSwitch(BYTE ucPort)
{
    OsdWindowDrawingByFontHighlight(_OSD_WIN_HIGHLIGHT_1, ROW(0), COL(3 + (12 * ((ucPort % 4) + 1))), WIDTH(10), HEIGHT(8), _CP_LIGHTBLUE, _CP_ORANGE, _CP_BG);
}

//--------------------------------------------------
// Description :
// Input Value :
// Output Value :
//--------------------------------------------------
void OsdDispHotKeySourceMenu(void)
{
    if(GET_OSD_DISPLAY_MODE() == _OSD_DM_1P)
    {
        if(SysSourceGetScanType() == _SOURCE_SWITCH_AUTO_IN_GROUP)
        {
            SET_OSD_1P_INPUT_SOURCE(_OSD_INPUT_AUTO);
        }
        else if(GET_OSD_1P_INPUT_SOURCE() != _OSD_INPUT_AUTO)
        {
            SET_OSD_1P_INPUT_SOURCE(SysRegionGetInputPort(_DISPLAY_RGN_1P));
        }
        g_usBackupValue = GET_OSD_1P_INPUT_SOURCE();
        SET_OSD_STATE(_MENU_HOTKEY_SOURCE);
        OsdFuncDisableOsd();
        OsdFuncApplyMap(WIDTH(_OSD_HOTKEY_SOURCE_MENU_WIDTH), HEIGHT(_OSD_HOTKEY_SOURCE_MENU_HEIGHT), COLOR(_CP_BLACK, _CP_BG));

#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
        OsdFuncMapRotation(GET_OSD_ROTATE_STATUS(), _OSD_MAP_A_REMAPPING_ENABLE, HEIGHT(8), _OSD_MAP_B_REMAPPING_DISABLE, 0, _OSD_FONT_LIB_ROTATION_ENABLE);
#endif

        OsdFuncBlending(_OSD_TRANSPARENCY_ONLY_WINDOW);
        OsdFuncTransparency(GET_OSD_TRANSPARENCY_STATUS());

        // Adjust Color Palette
        OsdPaletteSelectPalette(_PALETTE_MAIN_MENU);

        // Load Font & Icon
        OsdFuncSet2BitIconOffset(_2BIT_ICON_OFFSET);

        OsdFontVLCLoadFont(_FONT1_GLOBAL);

        // Background window
#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
        if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) || (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
        {
            OsdWindowDrawingByFont(_OSD_WINDOW_1, ROW(0), COL(0), WIDTH(12), g_ucOsdWidth, _CP_BLUE);
            OsdWindowDrawingByFont(_OSD_WINDOW_0, ROW(0), COL(12), WIDTH(52), g_ucOsdWidth, _CP_LIGHTBLUE);
        }
        else
#endif
        {
            OsdWindowDrawingByFont(_OSD_WINDOW_1, ROW(0), COL(0), WIDTH(12), g_ucOsdHeight, _CP_BLUE);
            OsdWindowDrawingByFont(_OSD_WINDOW_0, ROW(0), COL(12), WIDTH(52), g_ucOsdHeight, _CP_LIGHTBLUE);
        }

        // title
        // icon
        // _MENU_INPUT
        OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_0, _ICON_INPUT);

        OsdFontPut1BitMainMenuIcon(ROW(2), COL(3), (_1DYNAMIC_ICON_START + (0 * 24)), _CP_WHITE, _CP_BG);

        // highligh window
        OsdDispHotKeySourceMenuSwitch(g_usBackupValue);
        OsdDispHotKeySourceMenuIcon(GET_OSD_1P_INPUT_SOURCE());

        OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, 50, 50);

        OsdFuncEnableOsd();
    }
    else // Multi Frame
    {
        OsdDispMainMenu();
        SET_OSD_ITEM_INDEX(0);
        OsdDisp2ndMenuReDraw(_MENU_INPUT_ITEM, _HIGH);
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdDispPanelUniformityMsgSwitch(void)
{
    BYTE uctemp = 0;
    SET_OSD_PANEL_UNIFORMITY(GET_OSD_SELECT_REGION(), !(GET_OSD_PANEL_UNIFORMITY(GET_OSD_SELECT_REGION())));
    SET_OSD_PANEL_UNIFORMITY(GET_OSD_INVERSE_REGION(), (GET_OSD_PANEL_UNIFORMITY(GET_OSD_SELECT_REGION())));

    if(GET_OSD_PANEL_UNIFORMITY(GET_OSD_SELECT_REGION()) == _ON)
    {
        uctemp = 1;
    }

    OsdWindowDrawingByFontHighlight(_OSD_WIN_HIGHLIGHT_1, ROW(2), COL(18 + (9 * uctemp)), WIDTH(6), HEIGHT(4), _CP_LIGHTBLUE, _CP_ORANGE, _CP_BG);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdDispOsdMessage(EnumOSDDispMsg enumMessage)
{
    OsdDispDisableOsd();

    g_usFontPointer0 = _OSD_PAGE_0_START;
    g_usFontPointer1 = _OSD_PAGE_1_START;
    g_usFontPointer2 = _OSD_PAGE_2_START;

    OsdFuncApplyMap(WIDTH(_OSD_HOTKEY_MENU_WIDTH), HEIGHT(_OSD_HOTKEY_MENU_HEIGHT), COLOR(_CP_WHITE, _CP_BG));

#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
    OsdFuncMapRotation(GET_OSD_ROTATE_STATUS(), _OSD_MAP_A_REMAPPING_ENABLE, HEIGHT(_OSD_HOTKEY_MENU_HEIGHT), _OSD_MAP_B_REMAPPING_DISABLE, 0, _OSD_FONT_LIB_ROTATION_ENABLE);
#endif

    OsdFuncBlending(_OSD_TRANSPARENCY_WINDOW_AND_CHARACTER_BACKGROUND);
    OsdFuncTransparency(GET_OSD_TRANSPARENCY_STATUS());

    // Adjust Color Palette
    OsdPaletteSelectPalette(_PALETTE_MAIN_MENU);

    // Load Font & Icon
    OsdFuncSet2BitIconOffset(_2BIT_ICON_OFFSET);

    OsdFontVLCLoadFont(_FONT1_GLOBAL);

    // Background window Modify
#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
    if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) ||
       (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
    {
        OsdWindowDrawingByFont(_OSD_WINDOW_1, ROW(0), COL(0), WIDTH(12), HEIGHT(g_ucOsdWidth), _CP_BLUE);
        OsdWindowDrawingByFont(_OSD_WINDOW_0, ROW(0), COL(12), WIDTH(g_ucOsdHeight - 12), HEIGHT(g_ucOsdWidth), _CP_LIGHTBLUE);
    }
    else
#endif
    {
        if(enumMessage == _OSD_DISP_PANEL_UNIFORMITY_ONOFF_MSG)
        {
            OsdWindowDrawingByFont(_OSD_WINDOW_1, ROW(0), COL(0), WIDTH(g_ucOsdWidth), HEIGHT(g_ucOsdHeight), _CP_LIGHTBLUE);
        }
        else
        {
            OsdWindowDrawingByFont(_OSD_WINDOW_1, ROW(0), COL(0), WIDTH(12), HEIGHT(g_ucOsdHeight), _CP_BLUE);
            OsdWindowDrawingByFont(_OSD_WINDOW_0, ROW(0), COL(12), WIDTH(g_ucOsdWidth - 12), HEIGHT(g_ucOsdHeight), _CP_LIGHTBLUE);
        }
    }

    //==== Show page item =======
    switch(enumMessage)
    {
        case _OSD_DISP_NOSIGNAL_MSG:
            // title
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_0, _ICON_NO_SIGNAL);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(3), (_1DYNAMIC_ICON_START + (0 * 24)), _CP_WHITE, _CP_BG);
            // icon
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_1, _ICON_NO_SIGNAL_TEXT_0);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(18), (_1DYNAMIC_ICON_START + (1 * 24)), _CP_BLUE, _CP_BG);
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_2, _ICON_NO_SIGNAL_TEXT_1);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(18 + 6), (_1DYNAMIC_ICON_START + (2 * 24)), _CP_BLUE, _CP_BG);
            break;

        case _OSD_DISP_NOCABLE_MSG:
            // title
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_0, _ICON_NO_CABLE);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(3), (_1DYNAMIC_ICON_START + (0 * 24)), _CP_WHITE, _CP_BG);
            // icon
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_1, _ICON_NO_CABLE_TEXT_0);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(18), (_1DYNAMIC_ICON_START + (1 * 24)), _CP_BLUE, _CP_BG);
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_2, _ICON_NO_CABLE_TEXT_1);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(18 + 6), (_1DYNAMIC_ICON_START + (2 * 24)), _CP_BLUE, _CP_BG);
            break;

        case _OSD_DISP_NOSUPPORT_MSG:
            // title
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_0, _ICON_NO_SUPPORT);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(3), (_1DYNAMIC_ICON_START + (0 * 24)), _CP_WHITE, _CP_BG);
            // icon
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_1, _ICON_NO_SUPPORT_TEXT_0);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(18), (_1DYNAMIC_ICON_START + (1 * 24)), _CP_BLUE, _CP_BG);
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_2, _ICON_NO_SUPPORT_TEXT_1);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(18 + 6), (_1DYNAMIC_ICON_START + (2 * 24)), _CP_BLUE, _CP_BG);
            break;

        case _OSD_DISP_FAIL_SAFE_MODE_MSG:
            OsdPropPutStringCenter(ROW(_OSD_MESSAGE_ROW_START), COL(_OSD_MESSAGE_COL_START), WIDTH(_OSD_MESSAGE_STRING_LENGHT), _PFONT_PAGE_0, _STRING_NO_SUPPORT, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
            break;

        case _OSD_DISP_AUTO_CONFIG_MSG:
            // title
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_0, _ICON_AUTO_ADJUST);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(3), (_1DYNAMIC_ICON_START + (0 * 24)), _CP_WHITE, _CP_BG);

            // icon
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_1, _ICON_AUTO_ADJUST_TEXT_0);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(14), (_1DYNAMIC_ICON_START + (1 * 24)), _CP_BLUE, _CP_BG);
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_2, _ICON_AUTO_ADJUST_TEXT_1);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(14 + 6), (_1DYNAMIC_ICON_START + (2 * 24)), _CP_BLUE, _CP_BG);
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_3, _ICON_AUTO_ADJUST_TEXT_2);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(14 + 6 + 6), (_1DYNAMIC_ICON_START + (3 * 24)), _CP_BLUE, _CP_BG);

            break;

        case _OSD_DISP_INPUT_SIGNAL_MSG:
            OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, 50, 50);
            UserCommonTimerWaitForDDomainEvent(_EVENT_DEN_STOP);
            return;

            break;

        case _OSD_DISP_AUTO_COLOR_MSG:
            // title
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_0, _ICON_COLOR);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(3), (_1DYNAMIC_ICON_START + (0 * 24)), _CP_WHITE, _CP_BG);
            // icon
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_1, _ICON_AUTO_COLOR_TEXT_0);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(14), (_1DYNAMIC_ICON_START + (1 * 24)), _CP_BLUE, _CP_BG);
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_2, _ICON_AUTO_COLOR_TEXT_1);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(14 + 6), (_1DYNAMIC_ICON_START + (2 * 24)), _CP_BLUE, _CP_BG);
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_3, _ICON_AUTO_COLOR_TEXT_2);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(14 + 6 + 6), (_1DYNAMIC_ICON_START + (3 * 24)), _CP_BLUE, _CP_BG);

            break;

        case _OSD_DISP_POWER_SAVING_MSG:
            // SET_OSD_STATE(_MENU_MESSAGE_DISPLAY);
            // title
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_0, _ICON_POWER_SAVING);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(3), (_1DYNAMIC_ICON_START + (0 * 24)), _CP_WHITE, _CP_BG);
            // icon
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_1, _ICON_POWER_SAVING_TEXT_0);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(14), (_1DYNAMIC_ICON_START + (1 * 24)), _CP_BLUE, _CP_BG);
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_2, _ICON_POWER_SAVING_TEXT_1);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(14 + 6), (_1DYNAMIC_ICON_START + (2 * 24)), _CP_BLUE, _CP_BG);
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_3, _ICON_POWER_SAVING_TEXT_2);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(14 + 6 + 6), (_1DYNAMIC_ICON_START + (3 * 24)), _CP_BLUE, _CP_BG);
            break;

        case _OSD_DISP_PANEL_UNIFORMITY_ONOFF_MSG:
            // title
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_0, _ICON_TRUN_OFF_PANEL_UNI_TEXT0);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(3), (_1DYNAMIC_ICON_START + (0 * 24)), _CP_BLUE, _CP_BG);
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_1, _ICON_TRUN_OFF_PANEL_UNI_TEXT1);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(3 + 6), (_1DYNAMIC_ICON_START + (1 * 24)), _CP_BLUE, _CP_BG);
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_2, _ICON_YES);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(18), (_1DYNAMIC_ICON_START + (2 * 24)), _CP_BLUE, _CP_BG);
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_3, _ICON_NO);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(27), (_1DYNAMIC_ICON_START + (3 * 24)), _CP_BLUE, _CP_BG);

            break;
#if(_FREEZE_SUPPORT == _ON)
        case _OSD_DISP_DISABLE_FREEZE_MSG:
            // title
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_0, _ICON_FREEZE);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(3), (_1DYNAMIC_ICON_START + (0 * 24)), _CP_WHITE, _CP_BG);
            // icon
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_1, _ICON_FREEZE_DISABLE_TEXT_0);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(14), (_1DYNAMIC_ICON_START + (1 * 24)), _CP_BLUE, _CP_BG);
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_2, _ICON_FREEZE_DISABLE_TEXT_1);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(14 + 6), (_1DYNAMIC_ICON_START + (2 * 24)), _CP_BLUE, _CP_BG);
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_3, _ICON_FREEZE_DISABLE_TEXT_2);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(14 + 6 + 6), (_1DYNAMIC_ICON_START + (3 * 24)), _CP_BLUE, _CP_BG);
            break;
#endif
#if(_DP_MST_SUPPORT == _ON)
        case _OSD_DISP_MST_WARNING_MSG:
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_0, _ICON_DP_MST);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(3), (_1DYNAMIC_ICON_START + (0 * 24)), _CP_WHITE, _CP_BG);
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_1, _ICON_MST_WARNING_MSG_0);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(14), (_1DYNAMIC_ICON_START + (1 * 24)), _CP_BLUE, _CP_BG);
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_2, _ICON_MST_WARNING_MSG_1);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(14 + 6), (_1DYNAMIC_ICON_START + (2 * 24)), _CP_BLUE, _CP_BG);
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_3, _ICON_MST_WARNING_MSG_2);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(14 + 6 + 6), (_1DYNAMIC_ICON_START + (3 * 24)), _CP_BLUE, _CP_BG);
            break;
#endif

#if(_USB2_HOST_EHCI_MASS_STORGE_PROGRAM_SUPPORT == _ON)
        case _OSD_DISP_FW_UPDATE_MSG:
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_0, _ICON_FW_UPDATE);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(3), (_1DYNAMIC_ICON_START + (0 * 24)), _CP_WHITE, _CP_BG);

            OsdPropPutString(ROW(1), COL(14), _PFONT_PAGE_0, _STRING_FW_UPDATE_MSG1, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
            OsdPropPutString(ROW(5), COL(14), _PFONT_PAGE_0, _STRING_FW_UPDATE_MSG3, COLOR(_CP_RED, _CP_BG), _ENGLISH);
            OsdPropShowFileName(ROW(6), COL(14));
            break;

        case _OSD_DISP_FW_UPDATE_BAR_MSG:
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_0, _ICON_FW_UPDATE);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(3), (_1DYNAMIC_ICON_START + (0 * 24)), _CP_WHITE, _CP_BG);
            OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, 50, 0);
            SET_OSD_STATE(_MENU_FW_UPDATE_PROCESS_BAR);
            SET_OSD_WINDOW_BUTTON_TYPE(_OSD_WINDOW_BUTTON_TYPE_BORDER);
            SET_OSD_WINDOW_BORDER_PIXEL_WIDTH(_BAR_BORDER);
            SET_OSD_WINDOW_BORDER_PIXEL_HEIGHT(_BAR_BORDER);
            SET_OSD_WINDOW_EFF_COLOR_1(_CP_BLUE);
            OsdWindowDrawing(_SLIDER_1_BORDER_WINDOW, ((14 * 12)), (27), ((14 + 20) * 12), (27 + 36), _CP_LIGHTBLUE);
            OsdWindowDrawing(_SLIDER_1_BAR_WINDOW, ((14 * 12) + _BAR_BORDER), ((27) + _BAR_BORDER), (((14 * 12) + _BAR_BORDER) + 1), ((27 + 36) - _BAR_BORDER), _CP_WHITE);
            UserCommonTimerActiveTimerEvent(1, _USER_TIMER_EVENT_UPDATE_PROCESSING);
            OsdFuncEnableOsd();
            return;
            break;
#endif

        default:
            break;
    }

    OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, 50, 50);

    OsdFuncEnableOsd();
}
#if(_DM_FUNCTION == _ON)
#if(_IS_MAIN_PROCESS_CPU == _TRUE)
//--------------------------------------------------
// Description  : show DM logo
// Input Value  : enumMessage
// Output Value : None
//--------------------------------------------------
void OsdDispOsdDMMessage(EnumOSDDispMsg enumMessage)
{
    StructTimingFormat stTimingFormat;
    WORD usHPos = 0;
    WORD usVPos = 0;
    BYTE ucFonWidth = 12;
    BYTE ucFonHeight = 18;
    memset(&stTimingFormat, 0x00, sizeof(StructTimingFormat));

    if(GET_OSD_DOUBLE_SIZE() == _ON)
    {
        ucFonWidth *= 2;
        ucFonHeight *= 2;
    }

    if(GET_OSD_STATE() != _MENU_HOTKEY_INFORMATION)
    {
        OsdFuncDisableOsd();
        SET_OSD_STATE(_MENU_HOTKEY_INFORMATION);
        g_usFontPointer0 = _OSD_PAGE_0_START;
        g_usFontPointer1 = _OSD_PAGE_1_START;
        g_usFontPointer2 = _OSD_PAGE_2_START;

        OsdFuncBlending(_OSD_TRANSPARENCY_WINDOW_AND_CHARACTER_BACKGROUND);
        OsdFuncTransparency(GET_OSD_TRANSPARENCY_STATUS());
        // Adjust Color Palette
        OsdPaletteSelectPalette(_PALETTE_MAIN_MENU);
        // Load Font & Icon
        OsdFuncSet2BitIconOffset(_2BIT_ICON_OFFSET);
        OsdFuncApplyMapOsdAB(WIDTH(_OSD_HOTKEY_MENU_WIDTH), HEIGHT(_OSD_HOTKEY_MENU_HEIGHT + _DM_ROW_OFFSET), COLOR(_CP_WHITE, _CP_BG), WIDTH(_OSD_HOTKEY_MENU_WIDTH), HEIGHT(_OSD_HOTKEY_MENU_HEIGHT + _DM_ROW_OFFSET), COLOR(_CP_WHITE, _CP_BG));
#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
        OsdFuncMapRotation(GET_OSD_ROTATE_STATUS(), _OSD_MAP_A_REMAPPING_ENABLE, HEIGHT(_OSD_HOTKEY_MENU_HEIGHT + _DM_ROW_OFFSET), _OSD_MAP_B_REMAPPING_ENABLE, HEIGHT(_OSD_HOTKEY_MENU_HEIGHT + _DM_ROW_OFFSET), _OSD_FONT_LIB_ROTATION_ENABLE);
#endif
        UserCommonOsdMapABFunctionEnable(_OSD_A, _DISABLE);
        UserCommonOsdMapABFunctionEnable(_OSD_B, _DISABLE);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_CABLE_ICON, _ICON_NO_CABLE);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_CABLE_TEXT_0, _ICON_NO_CABLE_TEXT_0);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_CABLE_TEXT_1, _ICON_NO_CABLE_TEXT_1);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_SIGNAL_ICON, _ICON_NO_SIGNAL);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_SIGNAL_TEXT_0, _ICON_NO_SIGNAL_TEXT_0);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_SIGNAL_TEXT_1, _ICON_NO_SIGNAL_TEXT_1);
    }
    OsdFontVLCLoadFont(_FONT_DVISION);
    OsdFontVLCLoadFont(_FONT_DVISION_2P);

    //==== Show page item =======
    switch(enumMessage)
    {
        case _OSD_DISP_INPUT_SIGNAL_MSG:
            // OsdFontPut1BitTable(ROW(2), COL(21), tOSD_DM, COLOR(_CP_WHITE, _CP_BG));
            // OsdWindowDrawingByFont(_OSD_WINDOW_2, ROW(0), COL(18), WIDTH(18), HEIGHT(7), _CP_BLACK);

            OsdWindowDrawingByFont(_OSD_WINDOW_1, ROW(0 + _DM_ROW_OFFSET), COL(0), WIDTH(12), HEIGHT(g_ucOsdHeight - _DM_ROW_OFFSET), _CP_BLUE);
            OsdWindowDrawingByFont(_OSD_WINDOW_0, ROW(0 + _DM_ROW_OFFSET), COL(12), WIDTH(g_ucOsdWidth - 12), HEIGHT(g_ucOsdHeight - _DM_ROW_OFFSET), _CP_LIGHTBLUE);
            OsdDispMpDisplayStateNotice(ROW(0 + _DM_ROW_OFFSET), COL(0), _OSD_NOTICE_INFO, _DISPLAY_RGN_1P, _PFONT_PAGE_0);
            if(UserCommonColorDMGetDMStatus(_DISPLAY_RGN_1P) == _TRUE)
            {
                OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, 100, 0);
            }
            else
            {
                OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, 50, 50);
            }
            UserCommonOsdMapABFunctionEnable(_OSD_A, _ENABLE);
            break;

        case _OSD_DISP_DM_MAIN_MSG: // show Dolby logo only
            if(GET_OSD_DISPLAY_MODE() == _OSD_DM_1P)
            {
                OsdFontPut1BitTableMapAB(ROW(2), COL(21), _OSD_MODE_BYTE0_256_511, tOSD_DM_2, COLOR(_CP_WHITE, _CP_BG));
                OsdWindowDrawingByFont(_OSD_WINDOW_2, ROW(0), COL(18), WIDTH(18), HEIGHT(7), _CP_BLACK);
                OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, 100, 0);
                UserCommonOsdMapABFunctionEnable(_OSD_A, _ENABLE);
            }
            else if(GET_OSD_DISPLAY_MODE() == _OSD_DM_2P_LR)
            {
                if(GET_OSD_PBP_LR_RATIO() == _OSD_PBP_LR_RATIO_CENTER)
                {
                    OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_A, ((_PANEL_DH_WIDTH / 2) - _OSD_HOTKEY_MENU_WIDTH * ucFonWidth), 0);
                }
                else
                {
#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
                    UserCommonDisplayGetPbplrRightBackground(&stTimingFormat);
#endif
                    OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_A, ((_PANEL_DH_WIDTH - stTimingFormat.usHWidth) - (_OSD_HOTKEY_MENU_WIDTH * ucFonWidth)), 0);
                }
                OsdFontPut1BitTableMapAB(ROW(2), COL(21), _OSD_MODE_BYTE0_256_511, tOSD_DM_2, COLOR(_CP_WHITE, _CP_BG));
                OsdWindowDrawingByFont(_OSD_WINDOW_2, ROW(0), COL(18), WIDTH(18), HEIGHT(7), _CP_BLACK);
                UserCommonTimerWaitForDDomainEvent(_EVENT_DEN_STOP);
                UserCommonOsdMapABFunctionEnable(_OSD_A, _ENABLE);
            }
            else if(GET_OSD_DISPLAY_MODE() == _OSD_DM_2P_TB)
            {
                OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_A, (_PANEL_DH_WIDTH - _OSD_HOTKEY_MENU_WIDTH * ucFonWidth), 0);
                OsdFontPut1BitTableMapAB(ROW(2), COL(21), _OSD_MODE_BYTE0_256_511, tOSD_DM_2, COLOR(_CP_WHITE, _CP_BG));
                OsdWindowDrawingByFont(_OSD_WINDOW_2, ROW(0), COL(18), WIDTH(18), HEIGHT(7), _CP_BLACK);
                UserCommonTimerWaitForDDomainEvent(_EVENT_DEN_STOP);
                UserCommonOsdMapABFunctionEnable(_OSD_A, _ENABLE);
            }
            else if(GET_OSD_DISPLAY_MODE() == _OSD_DM_2P_PIP)
            {
                OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_A, (_PANEL_DH_WIDTH - _OSD_HOTKEY_MENU_WIDTH * ucFonWidth), 0);
                OsdFontPut1BitTableMapAB(ROW(2), COL(21), _OSD_MODE_BYTE0_256_511, tOSD_DM_2, COLOR(_CP_WHITE, _CP_BG));
                OsdWindowDrawingByFont(_OSD_WINDOW_2, ROW(0), COL(18), WIDTH(18), HEIGHT(7), _CP_BLACK);
                UserCommonTimerWaitForDDomainEvent(_EVENT_DEN_STOP);
                UserCommonOsdMapABFunctionEnable(_OSD_A, _ENABLE);
            }
            OsdFuncEnableOsd();
            break;
        case _OSD_DISP_DM_SUB_MSG: // show Dolby logo only
            if(GET_OSD_DISPLAY_MODE() == _OSD_DM_2P_LR)
            {
                OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_B, (_PANEL_DH_WIDTH - _OSD_HOTKEY_MENU_WIDTH * ucFonWidth), 0);
                OsdFontPut1BitTableMapAB(ROW(2 + _OSD_MAP_B_ROW_OFFSET), COL(21), _OSD_MODE_BYTE0_256_511, tOSD_DM_2, COLOR(_CP_WHITE, _CP_BG));
                SET_OSD_WINDOW_REFERENCE_DELAY(1);
                OsdWindowDrawingByFont(_OSD_WINDOW_3, ROW(0), COL(18), WIDTH(18), HEIGHT(7), _CP_BLACK);
                UserCommonTimerWaitForDDomainEvent(_EVENT_DEN_STOP);
                UserCommonOsdMapABFunctionEnable(_OSD_B, _ENABLE);
            }
            else if(GET_OSD_DISPLAY_MODE() == _OSD_DM_2P_TB)
            {
                OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_B, (_PANEL_DH_WIDTH - _OSD_HOTKEY_MENU_WIDTH * ucFonWidth), (_PANEL_DV_HEIGHT / 2));
                OsdFontPut1BitTableMapAB(ROW(2 + _OSD_MAP_B_ROW_OFFSET), COL(21), _OSD_MODE_BYTE0_256_511, tOSD_DM_2, COLOR(_CP_WHITE, _CP_BG));
                SET_OSD_WINDOW_REFERENCE_DELAY(1);
                OsdWindowDrawingByFont(_OSD_WINDOW_3, ROW(0), COL(18), WIDTH(18), HEIGHT(7), _CP_BLACK);
                UserCommonTimerWaitForDDomainEvent(_EVENT_DEN_STOP);
                UserCommonOsdMapABFunctionEnable(_OSD_B, _ENABLE);
            }
#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
            else if(GET_OSD_DISPLAY_MODE() == _OSD_DM_2P_PIP)
            {
                UserCommonDisplayGetPipSubBackground(&stTimingFormat);

                usHPos = (stTimingFormat.usHStart - _PANEL_DH_START) + stTimingFormat.usHWidth - (_OSD_HOTKEY_MENU_WIDTH * ucFonWidth);
                usVPos = (stTimingFormat.usVStart - _PANEL_DV_START);
                OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_B, usHPos, usVPos);

                OsdFontPut1BitTableMapAB(ROW(2 + _OSD_MAP_B_ROW_OFFSET), COL(21), _OSD_MODE_BYTE0_256_511, tOSD_DM_2, COLOR(_CP_WHITE, _CP_BG));
                SET_OSD_WINDOW_REFERENCE_DELAY(1);
                OsdWindowDrawingByFont(_OSD_WINDOW_3, ROW(0), COL(18), WIDTH(18), HEIGHT(7), _CP_BLACK);
                UserCommonTimerWaitForDDomainEvent(_EVENT_DEN_STOP);
                UserCommonOsdMapABFunctionEnable(_OSD_B, _ENABLE);
            }
#endif
            OsdFuncEnableOsd();
            break;
        default:
            break;
    }
}
#endif
#endif
#if(_VGA_SUPPORT == _ON)
//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdDispAutoConfigProc(void)
{
    OsdDispOsdMessage(_OSD_DISP_AUTO_CONFIG_MSG);
    UserCommonVgaAutoConfig();
    OsdDispDisableOsd();
}
//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdDisplayAutoBalanceProc(void)
{
    OsdDispDisableOsd();
    OsdDispOsdMessage(_OSD_DISP_AUTO_COLOR_MSG);

    if((SysVgaGetRegion() != _DISPLAY_RGN_NONE) &&
       (SysRegionGetDisplayState(SysVgaGetRegion()) == _DISPLAY_STATE_ACTIVE))
    {
        if(GET_OSD_COLOR_FORMAT(_A0_INPUT_PORT) == _COLOR_SPACE_RGB)
        {
            // Perform auto-color for RGB
            if(UserCommonVgaAutoDoWhiteBalance(_AUTO_TUNE_RGB) == _AUTO_SUCCESS)
            {
                UserCommonVgaAutoGetAutoColorResult(&g_stVgaAdcData);
                UserCommonNVRamSaveADCSetting(_COLOR_SPACE_RGB);

#if((_YPBPR_SUPPORT == _ON) && (_YPBPR_AUTO_METHOD == _YPBPR_AUTO_BY_FORMULA))
                // Calculate YPbPr gain/offset using formula
                g_stVgaAdcData = UserCommonVgaAutoBalanceYPbPrFromFormula(&g_stVgaAdcData);
                UserCommonNVRamSaveADCSetting(_COLOR_SPACE_YPBPR);

                // Restore RGB gain/offset
                UserCommonVgaAutoGetAutoColorResult(&g_stVgaAdcData);
#endif
            }
            else
            {
                UserCommonNVRamRestoreADCSetting();
            }
        }
#if((_YPBPR_SUPPORT == _ON) && (_YPBPR_AUTO_METHOD == _YPBPR_AUTO_BY_SOURCE))
        else
        {
            // Perform auto-color for YPbPr
            if(UserCommonVgaAutoDoWhiteBalance(_AUTO_TUNE_YPBPR) == _AUTO_SUCCESS)
            {
                UserCommonVgaAutoGetAutoColorResult(&g_stVgaAdcData);
                UserCommonNVRamSaveADCSetting(_COLOR_SPACE_YPBPR);
            }
            else
            {
                UserCommonNVRamRestoreADCSetting();
            }
        }
#endif
    }

    OsdDispDisableOsd();
}
#endif // End of #if(_VGA_SUPPORT == _ON)

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdDispOsdReset(void)
{
    BYTE ucIndex = GET_OSD_LANGUAGE();
    UserCommonDDomainBackgroundEnable(_DDOMAIN_RGN_ALL, _ENABLE);

    OsdDispDisableOsd();

    UserCommonNVRamRestoreSystemData();

    RTDNVRamRestoreOsdUserData();
    RTDNVRamRestoreOsdRegionData();
    RTDNVRamLoadOsdRegionData(GET_OSD_DISPLAY_MODE(), GET_OSD_SELECT_REGION());
    RTDNVRamRestoreOsdDisplayModeData();
    RTDNVRamLoadOsdDisplayModeData(GET_OSD_DISPLAY_MODE());
    RTDNVRamRestoreUserColorSetting();
    RTDNVRamRestoreOsdInputSourceData();
    RTDNVRamRestoreOsdInputPortData();
    RTDNVRamRestoreBacklight();

#if(_VGA_SUPPORT == _ON)
    UserCommonNVRamRestoreModeUserData();

    if((SysVgaGetRegion() != _DISPLAY_RGN_NONE) &&
       (SysRegionGetDisplayState(SysVgaGetRegion()) == _DISPLAY_STATE_ACTIVE))
    {
        SET_VGA_MODE_DO_FIRST_AUTO(_TRUE);
        UserCommonModeSearchInitalUserAndCenterData(g_stVgaModeUserData.ucModeNumber);
        UserCommonNVRamSaveModeUserData();
    }
#endif

#if(_DP_SUPPORT == _ON)
    // Switch DP Cpability
    OsdDispResetDpCapabilitySwitch();
#endif

#if(_DSC_DECODER_SUPPORT == _ON)
    // Switch DSC Capability
    UserCommonDscSwitchDisplayModeCapability();
#endif

#if(_FREESYNC_SUPPORT == _ON)
    // Switch Free Sync Capability
    UserCommonFreeSyncSupportSwitch();
#endif

#if((_DP_SUPPORT == _ON) && (_DP_ADAPTIVESYNC_SUPPORT == _ON))
    // Switch Adaptive Sync Capability
    UserCommonDpAdaptiveSyncSupportSwitch();
#endif

    if(ucIndex != GET_OSD_LANGUAGE())
    {
        SET_OSD_LANGUAGE(ucIndex);
        RTDNVRamSaveOsdUserData();
    }

#if(_COLOR_DEMO_FUNCTION == _ON)
    // Disable HLW
    SET_OSD_HLWIN_TYPE(_HL_WIN_OFF);
    UserAdjustHLWinType();
#endif

    UserAdjustDisplayMode();

    SET_OSD_STATE(_MENU_NONE);

#if(_HDMI_MULTI_EDID_SUPPORT == _ON)
    // Switch All HDMI Port Edid
    UserCommonEdidSwitchHdmiAllPortEdid();
#endif
}

#if(_DP_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Osd Display Reset Dp Capability Switch
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdDispResetDpCapabilitySwitch(void)
{
    // Set Aux Diff mode or Single-eneded mode & Resistance Setting
    SET_DP_AUX_DIFF_MODE();

    SET_DP_AUX_ADJR_SETTING(UserCommonNVRamGetSystemData(_DP_AUX_ADJR_SETTING));

    UserCommonDpAuxSet();

    // Switch All DP Port Dp Version
    UserCommonDpVersionSwitchDpAllPortVersion();

#if(_TYPE_C_PORT_CTRL_SUPPORT == _ON)
    // Switch All DP Port Dp Count Capability
    UserCommonUsbTypeCRxSetLaneCountCapabilitySwitch();
#endif

#if(_EMBEDDED_EDID_SUPPORT == _ON)
    // Switch All DP Port Edid
    UserCommonEdidSwitchDpAllPortEdid();
#endif

#if(_DP_MST_SUPPORT == _ON)
    // Switch Mst Capability
    UserCommonDpMstRxCapablePortSwitch(UserCommonDpGetMSTCapablePort());
#endif
}
#endif

//--------------------------------------------------
// Description  : Logo showing function
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdDispShowLogo(void)
{
    g_ucLogoTimerCounter = _OSD_TRANSPARENCY_MIN;
    g_bOsdLogoTransparencyDec = (g_ucLogoTimerCounter == _OSD_TRANSPARENCY_MAX) ? (_TRUE) : (_FALSE);

    UserCommonDDomainPatternGenAdjustColor(0, 0, 0);
    UserCommonDDomainPatternGenEnable(_ENABLE);
    UserCommonDDomainBackgroundEnable(_DDOMAIN_RGN_ALL, _DISABLE);

    OsdDispDisableOsd();

#if(_GOSD_SUPPORT == _OFF)
    OsdPaletteSelectPalette(_PALETTE_RTD_LOGO);
    OsdFuncApplyMap(WIDTH(_OSD_LOGOA_WIDTH / 12), HEIGHT(_OSD_LOGOA_HEIGHT / 18), COLOR(_LOGO_CP_WHITE, _LOGO_CP_BG));

#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
    OsdFuncMapRotation(GET_OSD_ROTATE_STATUS(), _OSD_MAP_A_REMAPPING_ENABLE, g_ucOsdHeight, _OSD_MAP_B_REMAPPING_DISABLE, 0, _OSD_FONT_LIB_ROTATION_ENABLE);
#endif

    OsdFuncBlending(_OSD_TRANSPARENCY_ALL);
    OsdFuncTransparency(_OSD_TRANSPARENCY_MAX); // default = _OSD_TRANSPARENCY_MAX for _INSTANT_TIMER_EVENT_0 == _OFF
    OsdFontVLCLoadFont(_REALTEK_LOGO_FONT_CMD);

    OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, 50, 50);

    UserCommonOsdMapABFunctionEnable(_OSD_A, _ENABLE);

#if(_INSTANT_TIMER_EVENT_0 == _ON)
    UserCommonTimer0SetTimerCount(16);
#endif

#else // #if(_GOSD_SUPPORT == _OFF)
    OsdDispGosdShowLogo();
#endif // #if(_GOSD_SUPPORT == _OFF)
    OsdFuncEnableOsd();

    SET_OSD_LOGO_ON(_ON);
}

//--------------------------------------------------
// Description  : OSD information function
// Input Value  : None
// Output Value : None
//--------------------------------------------------
//void OsdDispShowInformation(void)

#if(_GOSD_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Gosd Draw logo
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdDispGosdShowLogo(void)
{
#if((_IS_MAIN_PROCESS_CPU == _TRUE) || (_CPU32_SCPU_FW_MODE == _SCPU_FW_MODE_ACTOR))
    UserCommonGosdReleaseMultiSurfaceSync(_GOSD_SURFACE_RTK_LOGO_01_ID, _GOSD_DEFAULT_POLLING_MS);
    // create logo surface
    UserCommonGosdCreateSurfaceSync(_GOSD_SURFACE_RTK_LOGO_01_ID, _GOSD_SURFACE_RTK_LOGO_01_FORMAT, _GOSD_SURFACE_RTK_LOGO_01_WIDTH, _GOSD_SURFACE_RTK_LOGO_01_HEIGHT, _GOSD_SURFACE_RTK_LOGO_01_ADDRESS, _GOSD_DEFAULT_POLLING_MS);
    UserCommonGosdCreateSurfaceSync(_GOSD_SURFACE_RTK_LOGO_02_ID, _GOSD_SURFACE_RTK_LOGO_02_FORMAT, _GOSD_SURFACE_RTK_LOGO_02_WIDTH, _GOSD_SURFACE_RTK_LOGO_02_HEIGHT, _GOSD_SURFACE_RTK_LOGO_02_ADDRESS, _GOSD_DEFAULT_POLLING_MS);
    UserCommonGosdCreateSurfaceSync(_GOSD_SURFACE_RTK_LOGO_03_ID, _GOSD_SURFACE_RTK_LOGO_03_FORMAT, _GOSD_SURFACE_RTK_LOGO_03_WIDTH, _GOSD_SURFACE_RTK_LOGO_03_HEIGHT, _GOSD_SURFACE_RTK_LOGO_03_ADDRESS, _GOSD_DEFAULT_POLLING_MS);
    UserCommonGosdCreateSurfaceSync(_GOSD_SURFACE_RTK_LOGO_04_ID, _GOSD_SURFACE_RTK_LOGO_04_FORMAT, _GOSD_SURFACE_RTK_LOGO_04_WIDTH, _GOSD_SURFACE_RTK_LOGO_04_HEIGHT, _GOSD_SURFACE_RTK_LOGO_04_ADDRESS, _GOSD_DEFAULT_POLLING_MS);
    UserCommonGosdCreateSurfaceSync(_GOSD_SURFACE_RTK_LOGO_05_ID, _GOSD_SURFACE_RTK_LOGO_05_FORMAT, _GOSD_SURFACE_RTK_LOGO_05_WIDTH, _GOSD_SURFACE_RTK_LOGO_05_HEIGHT, _GOSD_SURFACE_RTK_LOGO_05_ADDRESS, _GOSD_DEFAULT_POLLING_MS);
    UserCommonGosdCreateSurfaceSync(_GOSD_SURFACE_RTK_LOGO_06_ID, _GOSD_SURFACE_RTK_LOGO_06_FORMAT, _GOSD_SURFACE_RTK_LOGO_06_WIDTH, _GOSD_SURFACE_RTK_LOGO_06_HEIGHT, _GOSD_SURFACE_RTK_LOGO_06_ADDRESS, _GOSD_DEFAULT_POLLING_MS);
    UserCommonGosdCreateSurfaceSync(_GOSD_SURFACE_RTK_LOGO_07_ID, _GOSD_SURFACE_RTK_LOGO_07_FORMAT, _GOSD_SURFACE_RTK_LOGO_07_WIDTH, _GOSD_SURFACE_RTK_LOGO_07_HEIGHT, _GOSD_SURFACE_RTK_LOGO_07_ADDRESS, _GOSD_DEFAULT_POLLING_MS);
    UserCommonGosdCreateSurfaceSync(_GOSD_SURFACE_RTK_LOGO_08_ID, _GOSD_SURFACE_RTK_LOGO_08_FORMAT, _GOSD_SURFACE_RTK_LOGO_08_WIDTH, _GOSD_SURFACE_RTK_LOGO_08_HEIGHT, _GOSD_SURFACE_RTK_LOGO_08_ADDRESS, _GOSD_DEFAULT_POLLING_MS);
    UserCommonGosdCreateSurfaceSync(_GOSD_SURFACE_RTK_LOGO_09_ID, _GOSD_SURFACE_RTK_LOGO_09_FORMAT, _GOSD_SURFACE_RTK_LOGO_09_WIDTH, _GOSD_SURFACE_RTK_LOGO_09_HEIGHT, _GOSD_SURFACE_RTK_LOGO_09_ADDRESS, _GOSD_DEFAULT_POLLING_MS);
    UserCommonGosdCreateSurfaceSync(_GOSD_SURFACE_RTK_LOGO_10_ID, _GOSD_SURFACE_RTK_LOGO_10_FORMAT, _GOSD_SURFACE_RTK_LOGO_10_WIDTH, _GOSD_SURFACE_RTK_LOGO_10_HEIGHT, _GOSD_SURFACE_RTK_LOGO_10_ADDRESS, _GOSD_DEFAULT_POLLING_MS);
    UserCommonGosdCreateSurfaceSync(_GOSD_SURFACE_RTK_LOGO_11_ID, _GOSD_SURFACE_RTK_LOGO_11_FORMAT, _GOSD_SURFACE_RTK_LOGO_11_WIDTH, _GOSD_SURFACE_RTK_LOGO_11_HEIGHT, _GOSD_SURFACE_RTK_LOGO_11_ADDRESS, _GOSD_DEFAULT_POLLING_MS);
    UserCommonGosdCreateSurfaceSync(_GOSD_SURFACE_RTK_LOGO_12_ID, _GOSD_SURFACE_RTK_LOGO_12_FORMAT, _GOSD_SURFACE_RTK_LOGO_12_WIDTH, _GOSD_SURFACE_RTK_LOGO_12_HEIGHT, _GOSD_SURFACE_RTK_LOGO_12_ADDRESS, _GOSD_DEFAULT_POLLING_MS);
    UserCommonGosdCreateSurfaceSync(_GOSD_SURFACE_RTK_LOGO_13_ID, _GOSD_SURFACE_RTK_LOGO_13_FORMAT, _GOSD_SURFACE_RTK_LOGO_13_WIDTH, _GOSD_SURFACE_RTK_LOGO_13_HEIGHT, _GOSD_SURFACE_RTK_LOGO_13_ADDRESS, _GOSD_DEFAULT_POLLING_MS);
    UserCommonGosdCreateSurfaceSync(_GOSD_SURFACE_RTK_LOGO_14_ID, _GOSD_SURFACE_RTK_LOGO_14_FORMAT, _GOSD_SURFACE_RTK_LOGO_14_WIDTH, _GOSD_SURFACE_RTK_LOGO_14_HEIGHT, _GOSD_SURFACE_RTK_LOGO_14_ADDRESS, _GOSD_DEFAULT_POLLING_MS);
    UserCommonGosdCreateSurfaceSync(_GOSD_SURFACE_RTK_LOGO_15_ID, _GOSD_SURFACE_RTK_LOGO_15_FORMAT, _GOSD_SURFACE_RTK_LOGO_15_WIDTH, _GOSD_SURFACE_RTK_LOGO_15_HEIGHT, _GOSD_SURFACE_RTK_LOGO_15_ADDRESS, _GOSD_DEFAULT_POLLING_MS);
    UserCommonGosdCreateSurfaceSync(_GOSD_SURFACE_RTK_LOGO_16_ID, _GOSD_SURFACE_RTK_LOGO_16_FORMAT, _GOSD_SURFACE_RTK_LOGO_16_WIDTH, _GOSD_SURFACE_RTK_LOGO_16_HEIGHT, _GOSD_SURFACE_RTK_LOGO_16_ADDRESS, _GOSD_DEFAULT_POLLING_MS);
    UserCommonGosdCreateSurfaceSync(_GOSD_SURFACE_RTK_LOGO_17_ID, _GOSD_SURFACE_RTK_LOGO_17_FORMAT, _GOSD_SURFACE_RTK_LOGO_17_WIDTH, _GOSD_SURFACE_RTK_LOGO_17_HEIGHT, _GOSD_SURFACE_RTK_LOGO_17_ADDRESS, _GOSD_DEFAULT_POLLING_MS);
    UserCommonGosdCreateSurfaceSync(_GOSD_SURFACE_RTK_LOGO_18_ID, _GOSD_SURFACE_RTK_LOGO_18_FORMAT, _GOSD_SURFACE_RTK_LOGO_18_WIDTH, _GOSD_SURFACE_RTK_LOGO_18_HEIGHT, _GOSD_SURFACE_RTK_LOGO_18_ADDRESS, _GOSD_DEFAULT_POLLING_MS);
    UserCommonGosdCreateSurfaceSync(_GOSD_SURFACE_RTK_LOGO_19_ID, _GOSD_SURFACE_RTK_LOGO_19_FORMAT, _GOSD_SURFACE_RTK_LOGO_19_WIDTH, _GOSD_SURFACE_RTK_LOGO_19_HEIGHT, _GOSD_SURFACE_RTK_LOGO_19_ADDRESS, _GOSD_DEFAULT_POLLING_MS);
    UserCommonGosdCreateSurfaceSync(_GOSD_SURFACE_RTK_LOGO_20_ID, _GOSD_SURFACE_RTK_LOGO_20_FORMAT, _GOSD_SURFACE_RTK_LOGO_20_WIDTH, _GOSD_SURFACE_RTK_LOGO_20_HEIGHT, _GOSD_SURFACE_RTK_LOGO_20_ADDRESS, _GOSD_DEFAULT_POLLING_MS);
    UserCommonGosdCreateSurfaceSync(_GOSD_SURFACE_RTK_LOGO_21_ID, _GOSD_SURFACE_RTK_LOGO_21_FORMAT, _GOSD_SURFACE_RTK_LOGO_21_WIDTH, _GOSD_SURFACE_RTK_LOGO_21_HEIGHT, _GOSD_SURFACE_RTK_LOGO_21_ADDRESS, _GOSD_DEFAULT_POLLING_MS);
    UserCommonGosdCreateSurfaceSync(_GOSD_SURFACE_RTK_LOGO_22_ID, _GOSD_SURFACE_RTK_LOGO_22_FORMAT, _GOSD_SURFACE_RTK_LOGO_22_WIDTH, _GOSD_SURFACE_RTK_LOGO_22_HEIGHT, _GOSD_SURFACE_RTK_LOGO_22_ADDRESS, _GOSD_DEFAULT_POLLING_MS);
    UserCommonGosdCreateSurfaceSync(_GOSD_SURFACE_RTK_LOGO_23_ID, _GOSD_SURFACE_RTK_LOGO_23_FORMAT, _GOSD_SURFACE_RTK_LOGO_23_WIDTH, _GOSD_SURFACE_RTK_LOGO_23_HEIGHT, _GOSD_SURFACE_RTK_LOGO_23_ADDRESS, _GOSD_DEFAULT_POLLING_MS);
    UserCommonGosdCreateSurfaceSync(_GOSD_SURFACE_RTK_LOGO_24_ID, _GOSD_SURFACE_RTK_LOGO_24_FORMAT, _GOSD_SURFACE_RTK_LOGO_24_WIDTH, _GOSD_SURFACE_RTK_LOGO_24_HEIGHT, _GOSD_SURFACE_RTK_LOGO_24_ADDRESS, _GOSD_DEFAULT_POLLING_MS);
    UserCommonGosdCreateSurfaceSync(_GOSD_SURFACE_RTK_LOGO_25_ID, _GOSD_SURFACE_RTK_LOGO_25_FORMAT, _GOSD_SURFACE_RTK_LOGO_25_WIDTH, _GOSD_SURFACE_RTK_LOGO_25_HEIGHT, _GOSD_SURFACE_RTK_LOGO_25_ADDRESS, _GOSD_DEFAULT_POLLING_MS);
    UserCommonGosdCreateSurfaceSync(_GOSD_SURFACE_RTK_LOGO_26_ID, _GOSD_SURFACE_RTK_LOGO_26_FORMAT, _GOSD_SURFACE_RTK_LOGO_26_WIDTH, _GOSD_SURFACE_RTK_LOGO_26_HEIGHT, _GOSD_SURFACE_RTK_LOGO_26_ADDRESS, _GOSD_DEFAULT_POLLING_MS);
    UserCommonGosdCreateSurfaceSync(_GOSD_SURFACE_RTK_LOGO_27_ID, _GOSD_SURFACE_RTK_LOGO_27_FORMAT, _GOSD_SURFACE_RTK_LOGO_27_WIDTH, _GOSD_SURFACE_RTK_LOGO_27_HEIGHT, _GOSD_SURFACE_RTK_LOGO_27_ADDRESS, _GOSD_DEFAULT_POLLING_MS);
    UserCommonGosdCreateSurfaceSync(_GOSD_SURFACE_RTK_LOGO_28_ID, _GOSD_SURFACE_RTK_LOGO_28_FORMAT, _GOSD_SURFACE_RTK_LOGO_28_WIDTH, _GOSD_SURFACE_RTK_LOGO_28_HEIGHT, _GOSD_SURFACE_RTK_LOGO_28_ADDRESS, _GOSD_DEFAULT_POLLING_MS);
    UserCommonGosdCreateSurfaceSync(_GOSD_SURFACE_RTK_LOGO_29_ID, _GOSD_SURFACE_RTK_LOGO_29_FORMAT, _GOSD_SURFACE_RTK_LOGO_29_WIDTH, _GOSD_SURFACE_RTK_LOGO_29_HEIGHT, _GOSD_SURFACE_RTK_LOGO_29_ADDRESS, _GOSD_DEFAULT_POLLING_MS);
    UserCommonGosdCreateSurfaceSync(_GOSD_SURFACE_RTK_LOGO_30_ID, _GOSD_SURFACE_RTK_LOGO_30_FORMAT, _GOSD_SURFACE_RTK_LOGO_30_WIDTH, _GOSD_SURFACE_RTK_LOGO_30_HEIGHT, _GOSD_SURFACE_RTK_LOGO_30_ADDRESS, _GOSD_DEFAULT_POLLING_MS);
    UserCommonGosdCreateSurfaceSync(_GOSD_SURFACE_RTK_LOGO_31_ID, _GOSD_SURFACE_RTK_LOGO_31_FORMAT, _GOSD_SURFACE_RTK_LOGO_31_WIDTH, _GOSD_SURFACE_RTK_LOGO_31_HEIGHT, _GOSD_SURFACE_RTK_LOGO_31_ADDRESS, _GOSD_DEFAULT_POLLING_MS);
    UserCommonGosdCreateSurfaceSync(_GOSD_SURFACE_RTK_LOGO_32_ID, _GOSD_SURFACE_RTK_LOGO_32_FORMAT, _GOSD_SURFACE_RTK_LOGO_32_WIDTH, _GOSD_SURFACE_RTK_LOGO_32_HEIGHT, _GOSD_SURFACE_RTK_LOGO_32_ADDRESS, _GOSD_DEFAULT_POLLING_MS);

    // load logo image
    StructGosdLoadImageInfo stSrc;
    stSrc.usImageSourceStartFlashBank = _GOSD_IMAGE_SOURCE_FLASH_START_BANK;

    stSrc.usImageIndex = _GOSD_IMAGE_SOURCE_RTK_LOGO_01;
    UserCommonGosdSetLoadImageInfoSync(_GOSD_SURFACE_RTK_LOGO_01_ID, &stSrc, _GOSD_LOAD_POLLING, _GOSD_DEFAULT_POLLING_MS);
    stSrc.usImageIndex = _GOSD_IMAGE_SOURCE_RTK_LOGO_02;
    UserCommonGosdSetLoadImageInfoSync(_GOSD_SURFACE_RTK_LOGO_02_ID, &stSrc, _GOSD_LOAD_POLLING, _GOSD_DEFAULT_POLLING_MS);
    stSrc.usImageIndex = _GOSD_IMAGE_SOURCE_RTK_LOGO_03;
    UserCommonGosdSetLoadImageInfoSync(_GOSD_SURFACE_RTK_LOGO_03_ID, &stSrc, _GOSD_LOAD_POLLING, _GOSD_DEFAULT_POLLING_MS);
    stSrc.usImageIndex = _GOSD_IMAGE_SOURCE_RTK_LOGO_04;
    UserCommonGosdSetLoadImageInfoSync(_GOSD_SURFACE_RTK_LOGO_04_ID, &stSrc, _GOSD_LOAD_POLLING, _GOSD_DEFAULT_POLLING_MS);
    stSrc.usImageIndex = _GOSD_IMAGE_SOURCE_RTK_LOGO_05;
    UserCommonGosdSetLoadImageInfoSync(_GOSD_SURFACE_RTK_LOGO_05_ID, &stSrc, _GOSD_LOAD_POLLING, _GOSD_DEFAULT_POLLING_MS);
    stSrc.usImageIndex = _GOSD_IMAGE_SOURCE_RTK_LOGO_06;
    UserCommonGosdSetLoadImageInfoSync(_GOSD_SURFACE_RTK_LOGO_06_ID, &stSrc, _GOSD_LOAD_POLLING, _GOSD_DEFAULT_POLLING_MS);
    stSrc.usImageIndex = _GOSD_IMAGE_SOURCE_RTK_LOGO_07;
    UserCommonGosdSetLoadImageInfoSync(_GOSD_SURFACE_RTK_LOGO_07_ID, &stSrc, _GOSD_LOAD_POLLING, _GOSD_DEFAULT_POLLING_MS);
    stSrc.usImageIndex = _GOSD_IMAGE_SOURCE_RTK_LOGO_08;
    UserCommonGosdSetLoadImageInfoSync(_GOSD_SURFACE_RTK_LOGO_08_ID, &stSrc, _GOSD_LOAD_POLLING, _GOSD_DEFAULT_POLLING_MS);
    stSrc.usImageIndex = _GOSD_IMAGE_SOURCE_RTK_LOGO_09;
    UserCommonGosdSetLoadImageInfoSync(_GOSD_SURFACE_RTK_LOGO_09_ID, &stSrc, _GOSD_LOAD_POLLING, _GOSD_DEFAULT_POLLING_MS);
    stSrc.usImageIndex = _GOSD_IMAGE_SOURCE_RTK_LOGO_10;
    UserCommonGosdSetLoadImageInfoSync(_GOSD_SURFACE_RTK_LOGO_10_ID, &stSrc, _GOSD_LOAD_POLLING, _GOSD_DEFAULT_POLLING_MS);
    stSrc.usImageIndex = _GOSD_IMAGE_SOURCE_RTK_LOGO_11;
    UserCommonGosdSetLoadImageInfoSync(_GOSD_SURFACE_RTK_LOGO_11_ID, &stSrc, _GOSD_LOAD_POLLING, _GOSD_DEFAULT_POLLING_MS);
    stSrc.usImageIndex = _GOSD_IMAGE_SOURCE_RTK_LOGO_12;
    UserCommonGosdSetLoadImageInfoSync(_GOSD_SURFACE_RTK_LOGO_12_ID, &stSrc, _GOSD_LOAD_POLLING, _GOSD_DEFAULT_POLLING_MS);
    stSrc.usImageIndex = _GOSD_IMAGE_SOURCE_RTK_LOGO_13;
    UserCommonGosdSetLoadImageInfoSync(_GOSD_SURFACE_RTK_LOGO_13_ID, &stSrc, _GOSD_LOAD_POLLING, _GOSD_DEFAULT_POLLING_MS);
    stSrc.usImageIndex = _GOSD_IMAGE_SOURCE_RTK_LOGO_14;
    UserCommonGosdSetLoadImageInfoSync(_GOSD_SURFACE_RTK_LOGO_14_ID, &stSrc, _GOSD_LOAD_POLLING, _GOSD_DEFAULT_POLLING_MS);
    stSrc.usImageIndex = _GOSD_IMAGE_SOURCE_RTK_LOGO_15;
    UserCommonGosdSetLoadImageInfoSync(_GOSD_SURFACE_RTK_LOGO_15_ID, &stSrc, _GOSD_LOAD_POLLING, _GOSD_DEFAULT_POLLING_MS);
    stSrc.usImageIndex = _GOSD_IMAGE_SOURCE_RTK_LOGO_16;
    UserCommonGosdSetLoadImageInfoSync(_GOSD_SURFACE_RTK_LOGO_16_ID, &stSrc, _GOSD_LOAD_POLLING, _GOSD_DEFAULT_POLLING_MS);
    stSrc.usImageIndex = _GOSD_IMAGE_SOURCE_RTK_LOGO_17;
    UserCommonGosdSetLoadImageInfoSync(_GOSD_SURFACE_RTK_LOGO_17_ID, &stSrc, _GOSD_LOAD_POLLING, _GOSD_DEFAULT_POLLING_MS);
    stSrc.usImageIndex = _GOSD_IMAGE_SOURCE_RTK_LOGO_18;
    UserCommonGosdSetLoadImageInfoSync(_GOSD_SURFACE_RTK_LOGO_18_ID, &stSrc, _GOSD_LOAD_POLLING, _GOSD_DEFAULT_POLLING_MS);
    stSrc.usImageIndex = _GOSD_IMAGE_SOURCE_RTK_LOGO_19;
    UserCommonGosdSetLoadImageInfoSync(_GOSD_SURFACE_RTK_LOGO_19_ID, &stSrc, _GOSD_LOAD_POLLING, _GOSD_DEFAULT_POLLING_MS);
    stSrc.usImageIndex = _GOSD_IMAGE_SOURCE_RTK_LOGO_20;
    UserCommonGosdSetLoadImageInfoSync(_GOSD_SURFACE_RTK_LOGO_20_ID, &stSrc, _GOSD_LOAD_POLLING, _GOSD_DEFAULT_POLLING_MS);
    stSrc.usImageIndex = _GOSD_IMAGE_SOURCE_RTK_LOGO_21;
    UserCommonGosdSetLoadImageInfoSync(_GOSD_SURFACE_RTK_LOGO_21_ID, &stSrc, _GOSD_LOAD_POLLING, _GOSD_DEFAULT_POLLING_MS);
    stSrc.usImageIndex = _GOSD_IMAGE_SOURCE_RTK_LOGO_22;
    UserCommonGosdSetLoadImageInfoSync(_GOSD_SURFACE_RTK_LOGO_22_ID, &stSrc, _GOSD_LOAD_POLLING, _GOSD_DEFAULT_POLLING_MS);
    stSrc.usImageIndex = _GOSD_IMAGE_SOURCE_RTK_LOGO_23;
    UserCommonGosdSetLoadImageInfoSync(_GOSD_SURFACE_RTK_LOGO_23_ID, &stSrc, _GOSD_LOAD_POLLING, _GOSD_DEFAULT_POLLING_MS);
    stSrc.usImageIndex = _GOSD_IMAGE_SOURCE_RTK_LOGO_24;
    UserCommonGosdSetLoadImageInfoSync(_GOSD_SURFACE_RTK_LOGO_24_ID, &stSrc, _GOSD_LOAD_POLLING, _GOSD_DEFAULT_POLLING_MS);
    stSrc.usImageIndex = _GOSD_IMAGE_SOURCE_RTK_LOGO_25;
    UserCommonGosdSetLoadImageInfoSync(_GOSD_SURFACE_RTK_LOGO_25_ID, &stSrc, _GOSD_LOAD_POLLING, _GOSD_DEFAULT_POLLING_MS);
    stSrc.usImageIndex = _GOSD_IMAGE_SOURCE_RTK_LOGO_26;
    UserCommonGosdSetLoadImageInfoSync(_GOSD_SURFACE_RTK_LOGO_26_ID, &stSrc, _GOSD_LOAD_POLLING, _GOSD_DEFAULT_POLLING_MS);
    stSrc.usImageIndex = _GOSD_IMAGE_SOURCE_RTK_LOGO_27;
    UserCommonGosdSetLoadImageInfoSync(_GOSD_SURFACE_RTK_LOGO_27_ID, &stSrc, _GOSD_LOAD_POLLING, _GOSD_DEFAULT_POLLING_MS);
    stSrc.usImageIndex = _GOSD_IMAGE_SOURCE_RTK_LOGO_28;
    UserCommonGosdSetLoadImageInfoSync(_GOSD_SURFACE_RTK_LOGO_28_ID, &stSrc, _GOSD_LOAD_POLLING, _GOSD_DEFAULT_POLLING_MS);
    stSrc.usImageIndex = _GOSD_IMAGE_SOURCE_RTK_LOGO_29;
    UserCommonGosdSetLoadImageInfoSync(_GOSD_SURFACE_RTK_LOGO_29_ID, &stSrc, _GOSD_LOAD_POLLING, _GOSD_DEFAULT_POLLING_MS);
    stSrc.usImageIndex = _GOSD_IMAGE_SOURCE_RTK_LOGO_30;
    UserCommonGosdSetLoadImageInfoSync(_GOSD_SURFACE_RTK_LOGO_30_ID, &stSrc, _GOSD_LOAD_POLLING, _GOSD_DEFAULT_POLLING_MS);
    stSrc.usImageIndex = _GOSD_IMAGE_SOURCE_RTK_LOGO_31;
    UserCommonGosdSetLoadImageInfoSync(_GOSD_SURFACE_RTK_LOGO_31_ID, &stSrc, _GOSD_LOAD_POLLING, _GOSD_DEFAULT_POLLING_MS);
    stSrc.usImageIndex = _GOSD_IMAGE_SOURCE_RTK_LOGO_32;
    UserCommonGosdSetLoadImageInfoSync(_GOSD_SURFACE_RTK_LOGO_32_ID, &stSrc, _GOSD_LOAD_POLLING, _GOSD_DEFAULT_POLLING_MS);

    // check surface ready to be used
    if(UserCommonGosdPollingSurfaceStatusSync(_GOSD_SURFACE_IDLE, _GOSD_SURFACE_RTK_LOGO_32_ID, 1000) == _FALSE)
    {
        return;
    }

    DWORD ulRotationSurfaceOffset = 0;
    // rotate surface
    if(GET_OSD_ROTATE_STATUS() > _OSD_ROTATE_DEGREE_0)
    {
        // rotation_surface_id = original_surface_id + 32
        ulRotationSurfaceOffset = 32;

        DWORD ulTempSurfaceId = _GOSD_SURFACE_RTK_LOGO_32_ID + ulRotationSurfaceOffset + 1;
        DWORD ulRotationTempSurfaceId = ulTempSurfaceId + 1;
        StructGosdRectangle stSrcRect;
        StructGosdPosition stOutPosition;
        WORD usRotationSize = MAXOF(_GOSD_SURFACE_RTK_LOGO_01_WIDTH, _GOSD_SURFACE_RTK_LOGO_01_HEIGHT);
        WORD usFinalW = (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_180) ? (_GOSD_SURFACE_RTK_LOGO_01_WIDTH) : (_GOSD_SURFACE_RTK_LOGO_01_HEIGHT);
        WORD usFinalH = (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_180) ? (_GOSD_SURFACE_RTK_LOGO_01_HEIGHT) : (_GOSD_SURFACE_RTK_LOGO_01_WIDTH);
        // create temp surface
        UserCommonGosdCreateSurfaceSync(ulTempSurfaceId, _GOSD_PIXEL_FORMAT_ARGB8888, usRotationSize, usRotationSize, _GOSD_AUTO_ADDRESS, _GOSD_DEFAULT_POLLING_MS);
        // creat rotation temp surface
        UserCommonGosdCreateSurfaceSync(ulRotationTempSurfaceId, _GOSD_PIXEL_FORMAT_ARGB8888, usRotationSize, usRotationSize, _GOSD_AUTO_ADDRESS, _GOSD_DEFAULT_POLLING_MS);

        // rotation each display surface
        for(DWORD ulSurfaceId = _GOSD_SURFACE_RTK_LOGO_01_ID; ulSurfaceId <= _GOSD_SURFACE_RTK_LOGO_32_ID; ulSurfaceId++)
        {
            stSrcRect.stSize.usW = _GOSD_SURFACE_RTK_LOGO_01_WIDTH;
            stSrcRect.stSize.usH = _GOSD_SURFACE_RTK_LOGO_01_HEIGHT;
            stSrcRect.stPosition.usX = 0;
            stSrcRect.stPosition.usY = 0;
            stOutPosition.usX = 0;
            stOutPosition.usY = 0;
            // copy to temp surface
            UserCommonGosdCopyPasteSync(ulSurfaceId, ulTempSurfaceId, stSrcRect, stOutPosition, _GOSD_DEFAULT_POLLING_MS);
            // rotation
            stSrcRect.stSize.usW = usRotationSize;
            stSrcRect.stSize.usH = usRotationSize;
            stSrcRect.stPosition.usX = 0;
            stSrcRect.stPosition.usY = 0;
            stOutPosition.usX = 0;
            stOutPosition.usY = 0;
            UserCommonGosdRotateSync(ulTempSurfaceId, ulRotationTempSurfaceId, stSrcRect, stOutPosition, GET_OSD_ROTATE_STATUS(), _GOSD_DEFAULT_POLLING_MS);
            // create rotation surface
            UserCommonGosdCreateSurfaceSync(ulSurfaceId + ulRotationSurfaceOffset, _GOSD_PIXEL_FORMAT_ARGB8888, usFinalW, usFinalH, _GOSD_AUTO_ADDRESS, _GOSD_DEFAULT_POLLING_MS);
            // copy
            switch(GET_OSD_ROTATE_STATUS())
            {
                default:
                case _OSD_ROTATE_DEGREE_0:
                    stSrcRect.stSize.usW = 512;
                    stSrcRect.stSize.usH = 128;
                    stSrcRect.stPosition.usX = 0;
                    stSrcRect.stPosition.usY = 0;
                    break;
                case _OSD_ROTATE_DEGREE_90:
                    stSrcRect.stSize.usW = 128;
                    stSrcRect.stSize.usH = 512;
                    stSrcRect.stPosition.usX = 512 - 128;
                    stSrcRect.stPosition.usY = 0;
                    break;
                case _OSD_ROTATE_DEGREE_270:
                    stSrcRect.stSize.usW = 128;
                    stSrcRect.stSize.usH = 512;
                    stSrcRect.stPosition.usX = 0;
                    stSrcRect.stPosition.usY = 0;
                    break;
                case _OSD_ROTATE_DEGREE_180:
                    stSrcRect.stSize.usW = 512;
                    stSrcRect.stSize.usH = 128;
                    stSrcRect.stPosition.usX = 0;
                    stSrcRect.stPosition.usY = 512 - 128;
                    break;
            }
            stOutPosition.usX = 0;
            stOutPosition.usY = 0;
            UserCommonGosdCopyPasteSync(ulRotationTempSurfaceId, ulSurfaceId + ulRotationSurfaceOffset, stSrcRect, stOutPosition, _GOSD_DEFAULT_POLLING_MS);
        }
    }

    {
        StructGosdRectangle stWinRect;
        StructGosdRectangle stDispRect;

        // set DisplaySurface param
        switch(GET_OSD_ROTATE_STATUS())
        {
            default:
            case _OSD_ROTATE_DEGREE_0:
                stWinRect.stSize.usW = 512;
                stWinRect.stSize.usH = 128;
                stWinRect.stPosition.usX = 0;
                stWinRect.stPosition.usY = 0;
                break;
            case _OSD_ROTATE_DEGREE_90:
                stWinRect.stSize.usW = 128;
                stWinRect.stSize.usH = 512;
                stWinRect.stPosition.usX = 0; // 512 - 128;
                stWinRect.stPosition.usY = 0;
                break;
            case _OSD_ROTATE_DEGREE_270:
                stWinRect.stSize.usW = 128;
                stWinRect.stSize.usH = 512;
                stWinRect.stPosition.usX = 0;
                stWinRect.stPosition.usY = 0;
                break;
            case _OSD_ROTATE_DEGREE_180:
                stWinRect.stSize.usW = 512;
                stWinRect.stSize.usH = 128;
                stWinRect.stPosition.usX = 0;
                stWinRect.stPosition.usY = 0; // 512 - 128;
                break;
        }
        stDispRect.stSize.usW = stWinRect.stSize.usW * 2;
        stDispRect.stSize.usH = stWinRect.stSize.usH * 2;
        stDispRect.stPosition.usX = (_PANEL_DH_WIDTH - stDispRect.stSize.usW) / 2;
        stDispRect.stPosition.usY = (_PANEL_DV_HEIGHT - stDispRect.stSize.usH) / 2;

        // set Continuous Step
        UserCommonGosdContinuousStepDisplay(0, _GOSD_PLANE_OSD1, _GOSD_SURFACE_RTK_LOGO_01_ID + ulRotationSurfaceOffset, &stWinRect, &stDispRect);
        UserCommonGosdContinuousStepDisplay(1, _GOSD_PLANE_OSD1, _GOSD_SURFACE_RTK_LOGO_02_ID + ulRotationSurfaceOffset, &stWinRect, &stDispRect);
        UserCommonGosdContinuousStepDisplay(2, _GOSD_PLANE_OSD1, _GOSD_SURFACE_RTK_LOGO_03_ID + ulRotationSurfaceOffset, &stWinRect, &stDispRect);
        UserCommonGosdContinuousStepDisplay(3, _GOSD_PLANE_OSD1, _GOSD_SURFACE_RTK_LOGO_04_ID + ulRotationSurfaceOffset, &stWinRect, &stDispRect);
        UserCommonGosdContinuousStepDisplay(4, _GOSD_PLANE_OSD1, _GOSD_SURFACE_RTK_LOGO_05_ID + ulRotationSurfaceOffset, &stWinRect, &stDispRect);
        UserCommonGosdContinuousStepDisplay(5, _GOSD_PLANE_OSD1, _GOSD_SURFACE_RTK_LOGO_06_ID + ulRotationSurfaceOffset, &stWinRect, &stDispRect);
        UserCommonGosdContinuousStepDisplay(6, _GOSD_PLANE_OSD1, _GOSD_SURFACE_RTK_LOGO_07_ID + ulRotationSurfaceOffset, &stWinRect, &stDispRect);
        UserCommonGosdContinuousStepDisplay(7, _GOSD_PLANE_OSD1, _GOSD_SURFACE_RTK_LOGO_08_ID + ulRotationSurfaceOffset, &stWinRect, &stDispRect);
        UserCommonGosdContinuousStepDisplay(8, _GOSD_PLANE_OSD1, _GOSD_SURFACE_RTK_LOGO_09_ID + ulRotationSurfaceOffset, &stWinRect, &stDispRect);
        UserCommonGosdContinuousStepDisplay(9, _GOSD_PLANE_OSD1, _GOSD_SURFACE_RTK_LOGO_10_ID + ulRotationSurfaceOffset, &stWinRect, &stDispRect);
        UserCommonGosdContinuousStepDisplay(10, _GOSD_PLANE_OSD1, _GOSD_SURFACE_RTK_LOGO_11_ID + ulRotationSurfaceOffset, &stWinRect, &stDispRect);
        UserCommonGosdContinuousStepDisplay(11, _GOSD_PLANE_OSD1, _GOSD_SURFACE_RTK_LOGO_12_ID + ulRotationSurfaceOffset, &stWinRect, &stDispRect);
        UserCommonGosdContinuousStepDisplay(12, _GOSD_PLANE_OSD1, _GOSD_SURFACE_RTK_LOGO_13_ID + ulRotationSurfaceOffset, &stWinRect, &stDispRect);
        UserCommonGosdContinuousStepDisplay(13, _GOSD_PLANE_OSD1, _GOSD_SURFACE_RTK_LOGO_14_ID + ulRotationSurfaceOffset, &stWinRect, &stDispRect);
        UserCommonGosdContinuousStepDisplay(14, _GOSD_PLANE_OSD1, _GOSD_SURFACE_RTK_LOGO_15_ID + ulRotationSurfaceOffset, &stWinRect, &stDispRect);
        UserCommonGosdContinuousStepDisplay(15, _GOSD_PLANE_OSD1, _GOSD_SURFACE_RTK_LOGO_16_ID + ulRotationSurfaceOffset, &stWinRect, &stDispRect);
        UserCommonGosdContinuousStepDisplay(16, _GOSD_PLANE_OSD1, _GOSD_SURFACE_RTK_LOGO_17_ID + ulRotationSurfaceOffset, &stWinRect, &stDispRect);
        UserCommonGosdContinuousStepDisplay(17, _GOSD_PLANE_OSD1, _GOSD_SURFACE_RTK_LOGO_18_ID + ulRotationSurfaceOffset, &stWinRect, &stDispRect);
        UserCommonGosdContinuousStepDisplay(18, _GOSD_PLANE_OSD1, _GOSD_SURFACE_RTK_LOGO_19_ID + ulRotationSurfaceOffset, &stWinRect, &stDispRect);
        UserCommonGosdContinuousStepDisplay(19, _GOSD_PLANE_OSD1, _GOSD_SURFACE_RTK_LOGO_20_ID + ulRotationSurfaceOffset, &stWinRect, &stDispRect);
        UserCommonGosdContinuousStepDisplay(20, _GOSD_PLANE_OSD1, _GOSD_SURFACE_RTK_LOGO_21_ID + ulRotationSurfaceOffset, &stWinRect, &stDispRect);
        UserCommonGosdContinuousStepDisplay(21, _GOSD_PLANE_OSD1, _GOSD_SURFACE_RTK_LOGO_22_ID + ulRotationSurfaceOffset, &stWinRect, &stDispRect);
        UserCommonGosdContinuousStepDisplay(22, _GOSD_PLANE_OSD1, _GOSD_SURFACE_RTK_LOGO_23_ID + ulRotationSurfaceOffset, &stWinRect, &stDispRect);
        UserCommonGosdContinuousStepDisplay(23, _GOSD_PLANE_OSD1, _GOSD_SURFACE_RTK_LOGO_24_ID + ulRotationSurfaceOffset, &stWinRect, &stDispRect);
        UserCommonGosdContinuousStepDisplay(24, _GOSD_PLANE_OSD1, _GOSD_SURFACE_RTK_LOGO_25_ID + ulRotationSurfaceOffset, &stWinRect, &stDispRect);
        UserCommonGosdContinuousStepDisplay(25, _GOSD_PLANE_OSD1, _GOSD_SURFACE_RTK_LOGO_26_ID + ulRotationSurfaceOffset, &stWinRect, &stDispRect);
        UserCommonGosdContinuousStepDisplay(26, _GOSD_PLANE_OSD1, _GOSD_SURFACE_RTK_LOGO_27_ID + ulRotationSurfaceOffset, &stWinRect, &stDispRect);
        UserCommonGosdContinuousStepDisplay(27, _GOSD_PLANE_OSD1, _GOSD_SURFACE_RTK_LOGO_28_ID + ulRotationSurfaceOffset, &stWinRect, &stDispRect);
        UserCommonGosdContinuousStepDisplay(28, _GOSD_PLANE_OSD1, _GOSD_SURFACE_RTK_LOGO_29_ID + ulRotationSurfaceOffset, &stWinRect, &stDispRect);
        UserCommonGosdContinuousStepDisplay(29, _GOSD_PLANE_OSD1, _GOSD_SURFACE_RTK_LOGO_30_ID + ulRotationSurfaceOffset, &stWinRect, &stDispRect);
        UserCommonGosdContinuousStepDisplay(30, _GOSD_PLANE_OSD1, _GOSD_SURFACE_RTK_LOGO_31_ID + ulRotationSurfaceOffset, &stWinRect, &stDispRect);
        UserCommonGosdContinuousStepDisplay(31, _GOSD_PLANE_OSD1, _GOSD_SURFACE_RTK_LOGO_32_ID + ulRotationSurfaceOffset, &stWinRect, &stDispRect);
    }
    // Enable Continuous
    UserCommonGosdContinuousEnable(80, _GOSD_PLANE_OSD1, _GOSD_CONTINUOUS_ONCE, 32);

    // set SubBlending mix Gosd only
    UserCommonOsdSubBlendingSetFosdMixerEnable(_DISABLE);
    UserCommonOsdSubBlendingSetGosdMixerEnable(_ENABLE);
#endif // End of #if((_IS_MAIN_PROCESS_CPU == _TRUE) || (_CPU32_SCPU_FW_MODE == _SCPU_FW_MODE_ACTOR))
}
#endif // #if(_GOSD_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Draw OSD notice window
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdDispMpDisplayStateNotice(WORD usRow, WORD usCol, BYTE ucNoticeInfo, EnumDisplayRegion enumDisplayRegion, BYTE ucFontIndex)
{
    EnumRegionIndex enumRegionIndex = UserCommonRegionGetIndex(enumDisplayRegion);
    EnumInputPort enumInputPort = _NO_INPUT_PORT;

    switch(ucNoticeInfo)
    {
        case _OSD_NOTICE_KEEP:

            return;

        case _OSD_NOTICE_INFO:
            enumInputPort = SysRegionGetInputPort(enumDisplayRegion);

            UserCommonOsdChange1BitColor(ROW(usRow), COL(usCol), LENGTH(_OSD_MESSAGE_COL_START), HEIGHT(_OSD_HOTKEY_MENU_HEIGHT), FG_COLOR(_CP_BLUE), BG_COLOR(_CP_BLUE));
            UserCommonOsdChange1BitColor(ROW(usRow), COL(usCol + _OSD_MESSAGE_COL_START), LENGTH(_OSD_HOTKEY_MENU_WIDTH - 12), HEIGHT(_OSD_HOTKEY_MENU_HEIGHT), FG_COLOR(_CP_LIGHTBLUE), BG_COLOR(_CP_LIGHTBLUE));

            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_0, _ICON_INFORMATION_HINT);
            OsdFontPut1BitMainMenuIcon(ROW(usRow + 2), COL(usCol + 3), _1BIT_NOTICE_INFORMATION, _CP_WHITE, _CP_BLUE);
            OsdPropPutStringCenter(ROW(usRow + 1), COL(usCol + _OSD_MESSAGE_COL_START), WIDTH(_OSD_MESSAGE_STRING_LENGHT), ucFontIndex, OsdDisplayGetSourcePortString(enumInputPort), COLOR(_CP_BLUE, _CP_LIGHTBLUE), _ENGLISH);
            OsdPropPutStringCenter(ROW(usRow + 2), COL(usCol + _OSD_MESSAGE_COL_START), WIDTH(_OSD_MESSAGE_STRING_LENGHT), ucFontIndex, _STRING_NOW_RESOLUTION_0 + enumRegionIndex, COLOR(_CP_BLUE, _CP_LIGHTBLUE), _ENGLISH);
            OsdPropPutStringCenter(ROW(usRow + 3), COL(usCol + _OSD_MESSAGE_COL_START), WIDTH(_OSD_MESSAGE_STRING_LENGHT), ucFontIndex, _STRING_HFREQPCLK_0 + enumRegionIndex, COLOR(_CP_BLUE, _CP_LIGHTBLUE), _ENGLISH);

            switch(SysRegionGetSourceType(enumDisplayRegion))
            {
#if(_VGA_SUPPORT == _ON)
                case _SOURCE_VGA:
                    OsdPropPutStringCenter(ROW(usRow + 4), COL(usCol + _OSD_MESSAGE_COL_START), WIDTH(_OSD_MESSAGE_STRING_LENGHT), ucFontIndex, OsdDisplayGetVGAModeString(g_stVgaModeUserData.b1IsPresetMode), COLOR(_CP_BLUE, _CP_LIGHTBLUE), _ENGLISH);
                    OsdPropShowNumber(ROW(usRow + 4), COL(usCol + 26), g_stVgaModeUserData.ucModeNumber, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), ucFontIndex, COLOR(_CP_BLUE, _CP_LIGHTBLUE));
                    break;
#endif

#if(_DIGITAL_PORT_SUPPORT == _ON)
                default:
                    OsdPropPutStringCenter(ROW(usRow + 4), COL(usCol + _OSD_MESSAGE_COL_START), WIDTH(_OSD_MESSAGE_STRING_LENGHT), ucFontIndex, OsdDisplayGetShowHDCPEnable(UserCommonSourceHdcpCheckEnabled(enumInputPort)), COLOR(_CP_BLUE, _CP_LIGHTBLUE), _ENGLISH);
                    break;
#endif
            }
#if(_FREESYNC_SUPPORT == _ON)
            if((UserCommonDrrGetType() == _DRR_FREESYNC_TYPE) && (GET_OSD_DISPLAY_MODE() == _OSD_DM_1P))
            {
                OsdPropShowFreeSyncVFreqRange(ROW(usRow + 5), COL(usCol + _OSD_MESSAGE_COL_START), WIDTH(_OSD_MESSAGE_STRING_LENGHT), ucFontIndex, COLOR(_CP_BLUE, _CP_LIGHTBLUE));
                UserCommonTimerActiveTimerEvent(SEC(1), _USER_TIMER_EVENT_OSD_SHOW_FREESYNC_VFREQ);
            }
#endif

#if(_OD_FUNCTION == _ON)
            if(UserCommonColorODGetStatus(_OD_REALTIME_ENABLE_STATUS) == _OFF)
            {
                OsdPropPutString(ROW(usRow + 7), COL(usCol + _OSD_MESSAGE_COL_START + 1), ucFontIndex, _STRING_OD, COLOR(_CP_BLUE, _CP_LIGHTBLUE), _ENGLISH);
                OsdPropPutString(ROW(usRow + 7), COL(usCol + _OSD_MESSAGE_COL_START + 4), ucFontIndex, _STRING_OFF, COLOR(_CP_BLUE, _CP_LIGHTBLUE), _ENGLISH);
            }
            else
            {
                OsdPropPutString(ROW(usRow + 7), COL(usCol + _OSD_MESSAGE_COL_START + 1), ucFontIndex, _STRING_OD, COLOR(_CP_BLUE, _CP_LIGHTBLUE), _ENGLISH);
                OsdPropPutString(ROW(usRow + 7), COL(usCol + _OSD_MESSAGE_COL_START + 4), ucFontIndex, _STRING_ON, COLOR(_CP_BLUE, _CP_LIGHTBLUE), _ENGLISH);
            }
#endif

#if(_DSC_DECODER_SUPPORT == _ON)
            if(UserCommonDscGetEnable(enumInputPort) == _ENABLE)
            {
                OsdPropPutString(ROW(usRow + 6), COL(usCol + _OSD_MESSAGE_COL_START + 1), ucFontIndex, _STRING_DSC, COLOR(_CP_BLUE, _CP_LIGHTBLUE), _ENGLISH);
                OsdPropPutString(ROW(usRow + 6), COL(usCol + _OSD_MESSAGE_COL_START + 4), ucFontIndex, _STRING_ON, COLOR(_CP_BLUE, _CP_LIGHTBLUE), _ENGLISH);
            }
            else
            {
                OsdPropPutString(ROW(usRow + 6), COL(usCol + _OSD_MESSAGE_COL_START + 1), ucFontIndex, _STRING_DSC, COLOR(_CP_BLUE, _CP_LIGHTBLUE), _ENGLISH);
                OsdPropPutString(ROW(usRow + 6), COL(usCol + _OSD_MESSAGE_COL_START + 4), ucFontIndex, _STRING_OFF, COLOR(_CP_BLUE, _CP_LIGHTBLUE), _ENGLISH);
            }

#endif
#if(_ULTRA_HDR_SUPPORT == _ON)
#if(_DM_FUNCTION == _ON)
#if(_IS_MAIN_PROCESS_CPU == _TRUE)
            if(UserCommonColorDMGetDMStatus(enumDisplayRegion) == _TRUE)
            {
                if(UserCommonColorDMGetDMGameMode(enumDisplayRegion) == _TRUE)
                {
                    OsdPropPutString(ROW(usRow + 6), COL(usCol + _OSD_MESSAGE_COL_START + 15), ucFontIndex, _STRING_DVISION, COLOR(_CP_RED, _CP_LIGHTBLUE), _ENGLISH);
                }
                else
                {
                    OsdPropPutString(ROW(usRow + 6), COL(usCol + _OSD_MESSAGE_COL_START + 15), ucFontIndex, _STRING_DVISION, COLOR(_CP_BLUE, _CP_LIGHTBLUE), _ENGLISH);
                }
                break;
            }
#endif
#endif

#if(_HDMI_SBTM_SUPPORT == _ON)
            if(UserCommonColorHDRGetSBTMStatus(enumDisplayRegion) == _HDR10_SBTM_ON)
            {
                OsdPropPutString(ROW(usRow + 6), COL(usCol + _OSD_MESSAGE_COL_START + 15), ucFontIndex, _STRING_SBTM, COLOR(_CP_BLUE, _CP_LIGHTBLUE), _ENGLISH);
                break;
            }
#endif

#if(_HDR10_SUPPORT == _ON)
            if(UserCommonColorHDRGetHDR10Status(enumDisplayRegion) == _HDR10_ON)
            {
                OsdPropPutString(ROW(usRow + 6), COL(usCol + _OSD_MESSAGE_COL_START + 15), ucFontIndex, _STRING_HDR_MODE, COLOR(_CP_BLUE, _CP_LIGHTBLUE), _ENGLISH);
                break;
            }
#endif

#if(_HLG_SUPPORT == _ON)
            if(UserCommonColorHDRGetHDR10Status(enumDisplayRegion) == _HLG_ON)
            {
                OsdPropPutString(ROW(usRow + 6), COL(usCol + _OSD_MESSAGE_COL_START + 15), ucFontIndex, _STRING_HLG, COLOR(_CP_BLUE, _CP_LIGHTBLUE), _ENGLISH);
                break;
            }
#endif
#if(_FREESYNC_II_SUPPORT == _ON)
            if(UserCommonColorHDRGetFreesynIIStatus(enumDisplayRegion) == _ON)
            {
                OsdPropPutString(ROW(usRow + 6), COL(usCol + _OSD_MESSAGE_COL_START + 15), ucFontIndex, _STRING_FREESYNC, COLOR(_CP_BLUE, _CP_LIGHTBLUE), _ENGLISH);
                break;
            }
#endif
#endif
#if(_DRR_SUPPORT == _ON)
            OsdPropShowDrrStatus(ROW(usRow + 7), COL(usCol + _OSD_MESSAGE_COL_START + 15), ucFontIndex, COLOR(_CP_BLUE, _CP_LIGHTBLUE));
#endif

            OsdPropPutString(ROW(usRow + 6), COL(usCol + _OSD_MESSAGE_COL_START + 15), ucFontIndex, _STRING_SDR, COLOR(_CP_BLUE, _CP_LIGHTBLUE), _ENGLISH);


            break;

        case _OSD_NOTICE_NO_SUPPORT:
        case _OSD_NOTICE_NO_CABLE:
        case _OSD_NOTICE_NO_SIGNAL:

#if(_DM_FUNCTION == _ON)
            if(GET_OSD_DISPLAY_MODE() < _OSD_DM_3P_FLAG)
            {
                OsdFuncCloseWindow(_OSD_WINDOW_2);
                OsdFontPut1BitTableMapAB(ROW(2), COL(21), _OSD_1_BIT_BYTE0, tOSD_DM_CLEAR, COLOR(_CP_WHITE, _CP_BG));
            }
#endif
            UserCommonOsdChange1BitColor(ROW(usRow), COL(usCol), LENGTH(12), HEIGHT(8), FG_COLOR(_CP_BLUE), BG_COLOR(_CP_BLUE));
            UserCommonOsdChange1BitColor(ROW(usRow), COL(usCol + 12), LENGTH(36 - 12), HEIGHT(8), FG_COLOR(_CP_LIGHTBLUE), BG_COLOR(_CP_LIGHTBLUE));

            OsdFontPut1BitMainMenuIcon(ROW(usRow + 2), COL(usCol + 3), ((ucNoticeInfo == _OSD_NOTICE_NO_SUPPORT) ? (_1BIT_NOTICE_NO_SUPPORT_ICON) : ((ucNoticeInfo == _OSD_NOTICE_NO_CABLE) ? (_1BIT_NOTICE_NO_CABLE_ICON) : (_1BIT_NOTICE_NO_SIGNAL_ICON))), _CP_WHITE, _CP_BLUE);
            OsdFontPut1BitMainMenuIcon(ROW(usRow + 2), COL(usCol + 18), ((ucNoticeInfo == _OSD_NOTICE_NO_SUPPORT) ? (_1BIT_NOTICE_NO_SUPPORT_TEXT_0) : ((ucNoticeInfo == _OSD_NOTICE_NO_CABLE) ? (_1BIT_NOTICE_NO_CABLE_TEXT_0) : (_1BIT_NOTICE_NO_SIGNAL_TEXT_0))), _CP_BLUE, _CP_LIGHTBLUE);
            OsdFontPut1BitMainMenuIcon(ROW(usRow + 2), COL(usCol + 18 + 6), ((ucNoticeInfo == _OSD_NOTICE_NO_SUPPORT) ? (_1BIT_NOTICE_NO_SUPPORT_TEXT_1) : ((ucNoticeInfo == _OSD_NOTICE_NO_CABLE) ? (_1BIT_NOTICE_NO_CABLE_TEXT_1) : (_1BIT_NOTICE_NO_SIGNAL_TEXT_1))), _CP_BLUE, _CP_LIGHTBLUE);
            break;

        default:
        case _OSD_NOTICE_NONE:

            // Clear message here
#if(_DM_FUNCTION == _ON)
            if(GET_OSD_DISPLAY_MODE() < _OSD_DM_3P_FLAG)
            {
                OsdFuncCloseWindow(_OSD_WINDOW_2);
                OsdFontPut1BitTableMapAB(ROW(2), COL(21), _OSD_1_BIT_BYTE0, tOSD_DM_CLEAR, COLOR(_CP_WHITE, _CP_BG));
            }
#endif
            OsdFuncClearOsd(ROW(usRow), COL(usCol), LENGTH(12), HEIGHT(8));
            OsdFuncClearOsd(ROW(usRow), COL(usCol + 12), LENGTH(36 - 12), HEIGHT(8));
            break;
    }
}

#if((_4P_DISPLAY_SUPPORT == _ON) || (_2P_DISPLAY_SUPPORT == _ON) || (_3P_DISPLAY_SUPPORT == _ON))
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdDispMpDisplayStateNoticeFontB(WORD usRow, WORD usCol, BYTE ucNoticeInfo, EnumDisplayRegion enumDisplayRegion, BYTE ucFontIndex)
{
    EnumRegionIndex enumRegionIndex = UserCommonRegionGetIndex(enumDisplayRegion);
    EnumInputPort enumInputPort = _NO_INPUT_PORT;

    switch(ucNoticeInfo)
    {
        case _OSD_NOTICE_KEEP:
            break;

        case _OSD_NOTICE_INFO:
            enumInputPort = SysRegionGetInputPort(enumDisplayRegion);

            UserCommonOsdChange1BitColor(ROW(_OSD_MAP_B_ROW_OFFSET + usRow), COL(usCol), LENGTH(12), HEIGHT(8), FG_COLOR(_CP_BLUE), BG_COLOR(_CP_BLUE));
            UserCommonOsdChange1BitColor(ROW(_OSD_MAP_B_ROW_OFFSET + usRow), COL(usCol + 12), LENGTH(36 - 12), HEIGHT(8), FG_COLOR(_CP_LIGHTBLUE), BG_COLOR(_CP_LIGHTBLUE));

            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_0, _ICON_INFORMATION_HINT);
            OsdFontPut1BitMainMenuIconOsdB(ROW(usRow + 2), COL(usCol + 3), _1BIT_NOTICE_INFORMATION, _CP_WHITE, _CP_BLUE);

            OsdPropPutStringCenter(ROW(_OSD_MAP_B_ROW_OFFSET + usRow + 2), COL(usCol + _OSD_MESSAGE_COL_START), WIDTH(_OSD_MESSAGE_STRING_LENGHT), ucFontIndex, OsdDisplayGetSourcePortString(enumInputPort), COLOR(_CP_BLUE, _CP_LIGHTBLUE), _ENGLISH);

            OsdPropPutStringCenter(ROW(_OSD_MAP_B_ROW_OFFSET + usRow + 3), COL(usCol + _OSD_MESSAGE_COL_START), WIDTH(_OSD_MESSAGE_STRING_LENGHT), ucFontIndex, _STRING_NOW_RESOLUTION_0 + enumRegionIndex, COLOR(_CP_BLUE, _CP_LIGHTBLUE), _ENGLISH);
            OsdPropPutStringCenter(ROW(_OSD_MAP_B_ROW_OFFSET + usRow + 4), COL(usCol + _OSD_MESSAGE_COL_START), WIDTH(_OSD_MESSAGE_STRING_LENGHT), ucFontIndex, _STRING_HFREQPCLK_0 + enumRegionIndex, COLOR(_CP_BLUE, _CP_LIGHTBLUE), _ENGLISH);

            switch(SysRegionGetSourceType(enumDisplayRegion))
            {
#if(_VGA_SUPPORT == _ON)
                case _SOURCE_VGA:
                    OsdPropPutStringCenter(ROW(_OSD_MAP_B_ROW_OFFSET + usRow + 5), COL(usCol + _OSD_MESSAGE_COL_START), WIDTH(_OSD_MESSAGE_STRING_LENGHT), ucFontIndex, OsdDisplayGetVGAModeString(g_stVgaModeUserData.b1IsPresetMode), COLOR(_CP_BLUE, _CP_LIGHTBLUE), _ENGLISH);
                    OsdPropShowNumber(ROW(_OSD_MAP_B_ROW_OFFSET + usRow + 5), COL(usCol + 26), g_stVgaModeUserData.ucModeNumber, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), ucFontIndex, COLOR(_CP_BLUE, _CP_LIGHTBLUE));
                    break;
#endif

#if(_DIGITAL_PORT_SUPPORT == _ON)

                default:
                    OsdPropPutStringCenter(ROW(_OSD_MAP_B_ROW_OFFSET + usRow + 5), COL(usCol + _OSD_MESSAGE_COL_START), WIDTH(_OSD_MESSAGE_STRING_LENGHT), ucFontIndex, OsdDisplayGetShowHDCPEnable(UserCommonSourceHdcpCheckEnabled(enumInputPort)), COLOR(_CP_BLUE, _CP_LIGHTBLUE), _ENGLISH);
                    break;
#endif
            }

#if(_DSC_DECODER_SUPPORT == _ON)
            if(UserCommonDscGetEnable(enumInputPort) == _ENABLE)
            {
                OsdPropPutString(ROW(_OSD_MAP_B_ROW_OFFSET + usRow + 7), COL(usCol + _OSD_MESSAGE_COL_START + 1), ucFontIndex, _STRING_DSC, COLOR(_CP_BLUE, _CP_LIGHTBLUE), _ENGLISH);
                OsdPropPutString(ROW(_OSD_MAP_B_ROW_OFFSET + usRow + 7), COL(usCol + _OSD_MESSAGE_COL_START + 4), ucFontIndex, _STRING_ON, COLOR(_CP_BLUE, _CP_LIGHTBLUE), _ENGLISH);
            }
            else
            {
                OsdPropPutString(ROW(_OSD_MAP_B_ROW_OFFSET + usRow + 7), COL(usCol + _OSD_MESSAGE_COL_START + 1), ucFontIndex, _STRING_DSC, COLOR(_CP_BLUE, _CP_LIGHTBLUE), _ENGLISH);
                OsdPropPutString(ROW(_OSD_MAP_B_ROW_OFFSET + usRow + 7), COL(usCol + _OSD_MESSAGE_COL_START + 4), ucFontIndex, _STRING_OFF, COLOR(_CP_BLUE, _CP_LIGHTBLUE), _ENGLISH);
            }
#endif
#if(_ULTRA_HDR_SUPPORT == _ON)
#if(_DM_FUNCTION == _ON)
#if(_IS_MAIN_PROCESS_CPU == _TRUE)
            if(UserCommonColorDMGetDMStatus(enumDisplayRegion) == _TRUE)
            {
                if(UserCommonColorDMGetDMGameMode(enumDisplayRegion) == _TRUE)
                {
                    OsdPropPutString(ROW(_OSD_MAP_B_ROW_OFFSET + usRow + 7), COL(usCol + _OSD_MESSAGE_COL_START + 15), ucFontIndex, _STRING_DVISION, COLOR(_CP_RED, _CP_LIGHTBLUE), _ENGLISH);
                }
                else
                {
                    OsdPropPutString(ROW(_OSD_MAP_B_ROW_OFFSET + usRow + 7), COL(usCol + _OSD_MESSAGE_COL_START + 15), ucFontIndex, _STRING_DVISION, COLOR(_CP_BLUE, _CP_LIGHTBLUE), _ENGLISH);
                }
                break;
            }
#endif
#endif
#if(_HDMI_SBTM_SUPPORT == _ON)
            if(UserCommonColorHDRGetSBTMStatus(enumDisplayRegion) == _HDR10_SBTM_ON)
            {
                OsdPropPutString(ROW(_OSD_MAP_B_ROW_OFFSET + usRow + 7), COL(usCol + _OSD_MESSAGE_COL_START + 15), ucFontIndex, _STRING_SBTM, COLOR(_CP_BLUE, _CP_LIGHTBLUE), _ENGLISH);
                break;
            }
#endif
#if(_HDR10_SUPPORT == _ON)
            if(UserCommonColorHDRGetHDR10Status(enumDisplayRegion) == _HDR10_ON)
            {
                OsdPropPutString(ROW(_OSD_MAP_B_ROW_OFFSET + usRow + 7), COL(usCol + _OSD_MESSAGE_COL_START + 15), ucFontIndex, _STRING_HDR_MODE, COLOR(_CP_BLUE, _CP_LIGHTBLUE), _ENGLISH);
                break;
            }
#endif
#if(_HLG_SUPPORT == _ON)
            if(UserCommonColorHDRGetHDR10Status(enumDisplayRegion) == _HLG_ON)
            {
                OsdPropPutString(ROW(_OSD_MAP_B_ROW_OFFSET + usRow + 7), COL(usCol + _OSD_MESSAGE_COL_START + 15), ucFontIndex, _STRING_HLG, COLOR(_CP_BLUE, _CP_LIGHTBLUE), _ENGLISH);
                break;
            }
#endif
#if(_FREESYNC_II_SUPPORT == _ON)
            if(UserCommonColorHDRGetFreesynIIStatus(enumDisplayRegion) == _ON)
            {
                OsdPropPutString(ROW(_OSD_MAP_B_ROW_OFFSET + usRow + 7), COL(usCol + _OSD_MESSAGE_COL_START + 15), ucFontIndex, _STRING_FREESYNC, COLOR(_CP_BLUE, _CP_LIGHTBLUE), _ENGLISH);
                break;
            }
#endif
#endif
#if(_DRR_SUPPORT == _ON)
            OsdPropShowDrrStatus(ROW(_OSD_MAP_B_ROW_OFFSET + usRow + 7), COL(usCol + _OSD_MESSAGE_COL_START + 15), ucFontIndex, COLOR(_CP_BLUE, _CP_LIGHTBLUE));
#endif

            OsdPropPutString(ROW(_OSD_MAP_B_ROW_OFFSET + usRow + 7), COL(usCol + _OSD_MESSAGE_COL_START + 15), ucFontIndex, _STRING_SDR, COLOR(_CP_BLUE, _CP_LIGHTBLUE), _ENGLISH);

            break;

        case _OSD_NOTICE_NO_SUPPORT:
        case _OSD_NOTICE_NO_CABLE:
        case _OSD_NOTICE_NO_SIGNAL:
#if(_DM_FUNCTION == _ON)
            if(GET_OSD_DISPLAY_MODE() < _OSD_DM_3P_FLAG)
            {
                OsdFuncCloseWindow(_OSD_WINDOW_3);
                OsdFontPut1BitTableMapAB(ROW(2 + _OSD_MAP_B_ROW_OFFSET), COL(21), _OSD_1_BIT_BYTE0, tOSD_DM_CLEAR, COLOR(_CP_WHITE, _CP_BG));
            }
#endif
            UserCommonOsdChange1BitColor(ROW(_OSD_MAP_B_ROW_OFFSET + usRow), COL(usCol), LENGTH(12), HEIGHT(8), FG_COLOR(_CP_BLUE), BG_COLOR(_CP_BLUE));
            UserCommonOsdChange1BitColor(ROW(_OSD_MAP_B_ROW_OFFSET + usRow), COL(usCol + 12), LENGTH(36 - 12), HEIGHT(8), FG_COLOR(_CP_LIGHTBLUE), BG_COLOR(_CP_LIGHTBLUE));

            OsdFontPut1BitMainMenuIconOsdB(ROW(usRow + 2), COL(usCol + 3), ((ucNoticeInfo == _OSD_NOTICE_NO_SUPPORT) ? (_1BIT_NOTICE_NO_SUPPORT_ICON) : ((ucNoticeInfo == _OSD_NOTICE_NO_CABLE) ? (_1BIT_NOTICE_NO_CABLE_ICON) : (_1BIT_NOTICE_NO_SIGNAL_ICON))), _CP_WHITE, _CP_BLUE);
            OsdFontPut1BitMainMenuIconOsdB(ROW(usRow + 2), COL(usCol + 18), ((ucNoticeInfo == _OSD_NOTICE_NO_SUPPORT) ? (_1BIT_NOTICE_NO_SUPPORT_TEXT_0) : ((ucNoticeInfo == _OSD_NOTICE_NO_CABLE) ? (_1BIT_NOTICE_NO_CABLE_TEXT_0) : (_1BIT_NOTICE_NO_SIGNAL_TEXT_0))), _CP_BLUE, _CP_LIGHTBLUE);
            OsdFontPut1BitMainMenuIconOsdB(ROW(usRow + 2), COL(usCol + 18 + 6), ((ucNoticeInfo == _OSD_NOTICE_NO_SUPPORT) ? (_1BIT_NOTICE_NO_SUPPORT_TEXT_1) : ((ucNoticeInfo == _OSD_NOTICE_NO_CABLE) ? (_1BIT_NOTICE_NO_CABLE_TEXT_1) : (_1BIT_NOTICE_NO_SIGNAL_TEXT_1))), _CP_BLUE, _CP_LIGHTBLUE);
            break;

        default:
        case _OSD_NOTICE_NONE:
            // Clear message here
#if(_DM_FUNCTION == _ON)
            if(GET_OSD_DISPLAY_MODE() < _OSD_DM_3P_FLAG)
            {
                OsdFuncCloseWindow(_OSD_WINDOW_3);
                OsdFontPut1BitTableMapAB(ROW(2 + _OSD_MAP_B_ROW_OFFSET), COL(21), _OSD_1_BIT_BYTE0, tOSD_DM_CLEAR, COLOR(_CP_WHITE, _CP_BG));
            }
#endif

            OsdFuncClearOsd(ROW(_OSD_MAP_B_ROW_OFFSET + usRow), COL(usCol), LENGTH(12), HEIGHT(8));
            OsdFuncClearOsd(ROW(_OSD_MAP_B_ROW_OFFSET + usRow), COL(usCol + 12), LENGTH(36 - 12), HEIGHT(8));
            break;
    }
}
#endif

//--------------------------------------------------
// Description  : Update OSD notice window for current display mode
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdDispMpUpdateDisplayStateNotice(bit bOn, EnumDisplayRegion enumDisplayRegion)
{
    bOn = bOn;
    enumDisplayRegion = enumDisplayRegion;

#if(_MULTI_DISPLAY_MAX > 1)
    if(GET_OSD_DISPLAY_MODE() != _OSD_DM_1P)
    {
        BYTE ucRegionIndex = 0;
        BYTE ucRegionCount = SysRegionGetDisplayStateCount(_DISPLAY_STATE_MAX);
        BYTE pucState[_MULTI_DISPLAY_MAX] = {0};

        for(ucRegionIndex = 0; ucRegionIndex < ucRegionCount; ++ucRegionIndex)
        {
            EnumDisplayRegion enumCurrentDisplayRegion = SysRegionGetDisplayRegion(ucRegionIndex);

            if((bOn == _ON) ||
               (enumDisplayRegion == _DISPLAY_RGN_NONE) ||
               (enumDisplayRegion == enumCurrentDisplayRegion))
            {
                // Update OSD notice
                pucState[ucRegionIndex] = OsdDispMpDisplayStateGetNoticeType(enumCurrentDisplayRegion, bOn);
            }
            else
            {
                pucState[ucRegionIndex] = _OSD_NOTICE_KEEP;
            }
        }

        switch(GET_OSD_DISPLAY_MODE())
        {
#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
            case _OSD_DM_2P_LR:
                OsdDispMpDisplayStateNotice_2P_LR(pucState[0], pucState[1]);
                break;
#endif
#if(_2P_PBP_TB_DISPLAY_SUPPORT == _ON)
            case _OSD_DM_2P_TB:
                OsdDispMpDisplayStateNotice_2P_TB(pucState[0], pucState[1]);
                break;
#endif
#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
            case _OSD_DM_2P_PIP:
                OsdDispMpDisplayStateNotice_2P_PIP(pucState[0], pucState[1]);
                break;
#endif
#if(_3P_FLAG_DISPLAY_SUPPORT == _ON)
            case _OSD_DM_3P_FLAG:
                OsdDispMpDisplayStateNotice_3P_FLAG(pucState[0], pucState[1], pucState[2]);
                break;
#endif
#if(_3P_SKEW_LR_DISPLAY_SUPPORT == _ON)
            case _OSD_DM_3P_SKEW_L:
                OsdDispMpDisplayStateNotice_3P_SKEWL(pucState[0], pucState[1], pucState[2]);
                break;
            case _OSD_DM_3P_SKEW_R:
                OsdDispMpDisplayStateNotice_3P_SKEWR(pucState[0], pucState[1], pucState[2]);
                break;
#endif
#if(_3P_SKEW_TB_DISPLAY_SUPPORT == _ON)
            case _OSD_DM_3P_SKEW_T:
                OsdDispMpDisplayStateNotice_3P_SKEWT(pucState[0], pucState[1], pucState[2]);
                break;
            case _OSD_DM_3P_SKEW_B:
                OsdDispMpDisplayStateNotice_3P_SKEWB(pucState[0], pucState[1], pucState[2]);
                break;
#endif
#if(_4P_DISPLAY_SUPPORT == _ON)
            case _OSD_DM_4P:
                OsdDispMpDisplayStateNotice_4P(pucState[0], pucState[1], pucState[2], pucState[3]);
                break;
#endif
            default:
                break;
        }
    }
    else
#endif
    {
        // SET_OSD_STATE(_MENU_INFORMATION);
        switch(SysRegionGetDisplayState(_DISPLAY_RGN_1P))
        {
            case _DISPLAY_STATE_NO_SIGNAL:
                OsdDispOsdMessage(_OSD_DISP_NOSIGNAL_MSG);
                break;
            case _DISPLAY_STATE_OOR:
                OsdDispOsdMessage(_OSD_DISP_NOSUPPORT_MSG);
                break;

            default:
#if(_DM_FUNCTION == _ON)
                OsdDispOsdDMMessage(_OSD_DISP_INPUT_SIGNAL_MSG);
#else
                OsdDispOsdMessage(_OSD_DISP_INPUT_SIGNAL_MSG);
                OsdDispMpDisplayStateNotice(ROW(0), COL(0), _OSD_NOTICE_INFO, _DISPLAY_RGN_1P, _PFONT_PAGE_0);
#endif
                break;
        }

        OsdFuncEnableOsd();
    }
}

#if((_2P_DISPLAY_SUPPORT == _ON) || (_4P_DISPLAY_SUPPORT == _ON) || (_3P_DISPLAY_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Get current OSD notice type for specific display region
// Input Value  : select region
// Output Value : OSD notice type
//--------------------------------------------------
BYTE OsdDispMpDisplayStateGetNoticeType(EnumDisplayRegion enumDisplayRegion, bit bOn)
{
    if((bOn == _ON) ||
       ((SysRegionCheckDisplayEvent(enumDisplayRegion, _DISPLAY_EVENT_STATE_CHANGE_USR) == _TRUE) &&
        ((GET_OSD_STATE() == _MENU_HOTKEY_INFORMATION) ||
         (GET_OSD_STATE() == _MENU_NONE))))
    {
        switch(SysRegionGetDisplayState(enumDisplayRegion))
        {
            case _DISPLAY_STATE_OOR:
                DebugMessageOsd("4._OSD_NOTICE_NO_SUPPORT", enumDisplayRegion);
                return _OSD_NOTICE_NO_SUPPORT;

            case _DISPLAY_STATE_NO_SIGNAL:
                if(SysSourceGetCableDetect(UserCommonNVRamGetSystemRegionPortData(enumDisplayRegion)) == _TRUE)
                {
                    DebugMessageOsd("4._OSD_NOTICE_NO_SIGNAL", enumDisplayRegion);
                    return _OSD_NOTICE_NO_SIGNAL;
                }
                else
                {
                    DebugMessageOsd("4._OSD_NOTICE_NO_CABLE", enumDisplayRegion);
                    return _OSD_NOTICE_NO_CABLE;
                }

            case _DISPLAY_STATE_ACTIVE:

                if(GET_FAIL_SAFE_MODE(UserCommonRegionGetIndex(enumDisplayRegion)) == _TRUE)
                {
                    // Show OOR in fail safe mode
                    DebugMessageOsd("4._OSD_NOTICE_NONE", enumDisplayRegion);
                    return _OSD_NOTICE_NONE;
                }
                else
                {
                    DebugMessageOsd("4._OSD_NOTICE_INFO", enumDisplayRegion);
                    return _OSD_NOTICE_INFO;
                }

            default:
            case _DISPLAY_STATE_NONE:
                DebugMessageOsd("4._OSD_NOTICE_NONE", enumDisplayRegion);
                return _OSD_NOTICE_NONE;
        }
    }
    else
    {
        DebugMessageOsd("4._OSD_NOTICE_KEEP", enumDisplayRegion);
        return _OSD_NOTICE_KEEP;
    }
}
#endif // End of #if((_2P_DISPLAY_SUPPORT == _ON) || (_4P_DISPLAY_SUPPORT == _ON) || (_3P_DISPLAY_SUPPORT == _ON))

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
//--------------------------------------------------
// Description  : No signal & No cable & No support for Multi 2P LR
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdDispMpDisplayStateNotice_2P_LR(BYTE ucNoticeL, BYTE ucNoticeR)
{
    BYTE ucFonWidth = _FONT_WIDTH;
    BYTE ucFonHeight = _FONT_HEIGHT;
    WORD usHPos_a = 0;
    WORD usHPos_b = 0;
    WORD usVPos_a = 0;
    WORD usVPos_b = 0;
    WORD usFontNumWidth = _FONT_WIDTH;
    WORD usFontNumHeight = _FONT_HEIGHT;
    StructTimingFormat stTimingFormat;
#if(_DM_FUNCTION == _ON)
    BYTE ucRowOffset = 8;
#else
    BYTE ucRowOffset = 0;
#endif
    memset(&stTimingFormat, 0, sizeof(StructTimingFormat));

    if(GET_OSD_DOUBLE_SIZE() == _ON)
    {
        ucFonWidth = _FONT_WIDTH * 2;
        ucFonHeight = _FONT_HEIGHT * 2;
    }

    if(GET_OSD_STATE() != _MENU_HOTKEY_INFORMATION)
    {
        OsdFuncDisableOsd();

        SET_OSD_STATE(_MENU_HOTKEY_INFORMATION);
        g_usFontPointer0 = _OSD_PAGE_0_START;
        g_usFontPointer1 = _OSD_PAGE_1_START;
        g_usFontPointer2 = _OSD_PAGE_2_START;

        UserCommonOsdMapABFunctionEnable(_OSD_A, _DISABLE);
        UserCommonOsdMapABFunctionEnable(_OSD_B, _DISABLE);

        OsdFuncApplyMapOsdAB(WIDTH(_OSD_HOTKEY_MENU_WIDTH), HEIGHT(_OSD_HOTKEY_MENU_HEIGHT + ucRowOffset), COLOR(_CP_WHITE, _CP_BG), WIDTH(_OSD_HOTKEY_MENU_WIDTH), HEIGHT(_OSD_HOTKEY_MENU_HEIGHT + ucRowOffset), COLOR(_CP_WHITE, _CP_BG));

#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
        OsdFuncMapRotation(GET_OSD_ROTATE_STATUS(), _OSD_MAP_A_REMAPPING_ENABLE, HEIGHT(_OSD_HOTKEY_MENU_HEIGHT + ucRowOffset), _OSD_MAP_B_REMAPPING_ENABLE, HEIGHT(_OSD_HOTKEY_MENU_HEIGHT + ucRowOffset), _OSD_FONT_LIB_ROTATION_ENABLE);
#endif

        OsdFuncBlending(_OSD_TRANSPARENCY_WINDOW_AND_CHARACTER_BACKGROUND);
        OsdFuncTransparency(GET_OSD_TRANSPARENCY_STATUS());

        // Adjust Color Palette
        OsdPaletteSelectPalette(_PALETTE_MAIN_MENU);

        // Load Font & Icon
        OsdFuncSet2BitIconOffset(_2BIT_ICON_OFFSET);

        OsdFontVLCLoadFont(_FONT1_GLOBAL);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_SUPPORT_ICON, _ICON_NO_SUPPORT);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_SUPPORT_TEXT_0, _ICON_NO_SUPPORT_TEXT_0);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_SUPPORT_TEXT_1, _ICON_NO_SUPPORT_TEXT_1);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_CABLE_ICON, _ICON_NO_CABLE);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_CABLE_TEXT_0, _ICON_NO_CABLE_TEXT_0);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_CABLE_TEXT_1, _ICON_NO_CABLE_TEXT_1);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_SIGNAL_ICON, _ICON_NO_SIGNAL);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_SIGNAL_TEXT_0, _ICON_NO_SIGNAL_TEXT_0);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_SIGNAL_TEXT_1, _ICON_NO_SIGNAL_TEXT_1);
    }

    // L/R swap check
    OsdDispMpDisplayStateNotice(ROW(0 + ucRowOffset), COL(0), ucNoticeL, _DISPLAY_RGN_PBP_LR_EQUAL_LEFT, _PFONT_PAGE_0);
    OsdDispMpDisplayStateNoticeFontB(ROW(0 + ucRowOffset), COL(0), ucNoticeR, _DISPLAY_RGN_PBP_LR_EQUAL_RIGHT, _PFONT_PAGE_1);

    switch(GET_OSD_ROTATE_STATUS())
    {
        case _OSD_ROTATE_DEGREE_0:
        case _OSD_ROTATE_DEGREE_180:
            usFontNumWidth = (_MESSAGE_WIDTH_MID_FONT_NUM * ucFonWidth);
            usFontNumHeight = (_MESSAGE_HEIGHT_MID_FONT_NUM * ucFonHeight);
            break;
        case _OSD_ROTATE_DEGREE_90:
        case _OSD_ROTATE_DEGREE_270:
            usFontNumWidth = (_MESSAGE_HEIGHT_MID_FONT_NUM * ucFonHeight);
            usFontNumHeight = (_MESSAGE_WIDTH_MID_FONT_NUM * ucFonWidth);
            break;
        default:
            break;
    }

    if(GET_OSD_PBP_LR_RATIO() == _OSD_PBP_LR_RATIO_CENTER)
    {
        // _PBP_LR_L_EQUAL_R
        if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_180)
        {
            usHPos_a = _PANEL_DH_WIDTH / 4 * 3;
            usHPos_b = _PANEL_DH_WIDTH / 4;
        }
        else
        {
            usHPos_a = _PANEL_DH_WIDTH / 4;
            usHPos_b = _PANEL_DH_WIDTH / 4 * 3;
        }
    }
    else
    {
        UserCommonDisplayGetPbplrRightBackground(&stTimingFormat);

        if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_180)
        {
            // _PBP_LR_L_LARGER_THAN_R
            usHPos_a = (_PANEL_DH_WIDTH - stTimingFormat.usHWidth) / 2 + stTimingFormat.usHWidth;
            usHPos_b = (stTimingFormat.usHWidth > (usFontNumWidth * 2)) ? (stTimingFormat.usHWidth / 2) : (0);
        }
        else
        {
            // _PBP_LR_L_LARGER_THAN_R
            usHPos_a = (_PANEL_DH_WIDTH - stTimingFormat.usHWidth) / 2;
            usHPos_b = _PANEL_DH_WIDTH - stTimingFormat.usHWidth / 2;
        }
    }

    usVPos_a = _PANEL_DV_HEIGHT / 2;
    usVPos_b = _PANEL_DV_HEIGHT / 2;

    usHPos_a = (usHPos_a > usFontNumWidth) ? (usHPos_a - usFontNumWidth) : (0);
    usVPos_a = (usVPos_a > usFontNumHeight) ? (usVPos_a - usFontNumHeight) : (0);
    usHPos_b = (usHPos_b > usFontNumWidth) ? (usHPos_b - usFontNumWidth) : (0);
    usVPos_b = (usVPos_b > usFontNumHeight) ? (usVPos_b - usFontNumHeight) : (0);
#if(_DM_FUNCTION == _ON)
#if(_IS_MAIN_PROCESS_CPU == _TRUE)
    if(ucNoticeL != _OSD_NOTICE_KEEP)
    {
        if((UserCommonColorDMGetDMStatus(_DISPLAY_RGN_PBP_LR_EQUAL_LEFT) == _TRUE) && (GET_OSD_DVISION_NOTICE(SysRegionGetInputPort(_DISPLAY_RGN_PBP_LR_EQUAL_LEFT)) == _ON))
        {
            if(GET_OSD_PBP_LR_RATIO() == _OSD_PBP_LR_RATIO_CENTER)
            {
                OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_A, ((_PANEL_DH_WIDTH / 2) - _OSD_HOTKEY_MENU_WIDTH * ucFonWidth), 0);
            }
            else
            {
                OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_A, ((_PANEL_DH_WIDTH - stTimingFormat.usHWidth) - (_OSD_HOTKEY_MENU_WIDTH * ucFonWidth)), 0);
            }
        }
        else
        {
            OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_A, usHPos_a, usVPos_a);
        }
        UserCommonTimerWaitForDDomainEvent(_EVENT_DEN_STOP);
        UserCommonOsdMapABFunctionEnable(_OSD_A, _ENABLE);
    }
    if(ucNoticeR != _OSD_NOTICE_KEEP)
    {
        if((UserCommonColorDMGetDMStatus(_DISPLAY_RGN_PBP_LR_EQUAL_RIGHT) == _TRUE) && (GET_OSD_DVISION_NOTICE(SysRegionGetInputPort(_DISPLAY_RGN_PBP_LR_EQUAL_RIGHT)) == _ON))
        {
            OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_B, (_PANEL_DH_WIDTH - _OSD_HOTKEY_MENU_WIDTH * ucFonWidth), 0);
        }
        else
        {
            OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_B, usHPos_b, usVPos_b);
        }
        UserCommonTimerWaitForDDomainEvent(_EVENT_DEN_STOP);
        UserCommonOsdMapABFunctionEnable(_OSD_B, _ENABLE);
    }
#endif
#else
    OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_A, usHPos_a, usVPos_a);
    OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_B, usHPos_b, usVPos_b);
    UserCommonOsdMapABFunctionEnable(_OSD_A, _ENABLE);
    UserCommonOsdMapABFunctionEnable(_OSD_B, _ENABLE);
#endif
    OsdFuncEnableOsd();
}
#endif // End of #if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)

#if(_2P_PBP_TB_DISPLAY_SUPPORT == _ON)
//--------------------------------------------------
// Description  : No signal & No cable & No support for Multi 2P TB
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdDispMpDisplayStateNotice_2P_TB(BYTE ucNoticeT, BYTE ucNoticeB)
{
    BYTE ucFonWidth = _FONT_WIDTH;
    BYTE ucFonHeight = _FONT_HEIGHT;
#if(_DM_FUNCTION == _ON)
    BYTE ucRowOffset = 8;
#else
    BYTE ucRowOffset = 0;
#endif

    if(GET_OSD_DOUBLE_SIZE() == _ON)
    {
        ucFonWidth = _FONT_WIDTH * 2;
        ucFonHeight = _FONT_HEIGHT * 2;
    }

    if(GET_OSD_STATE() != _MENU_HOTKEY_INFORMATION)
    {
        OsdFuncDisableOsd();

        SET_OSD_STATE(_MENU_HOTKEY_INFORMATION);
        g_usFontPointer0 = _OSD_PAGE_0_START;
        g_usFontPointer1 = _OSD_PAGE_1_START;
        g_usFontPointer2 = _OSD_PAGE_2_START;

        UserCommonOsdMapABFunctionEnable(_OSD_A, _DISABLE);
        UserCommonOsdMapABFunctionEnable(_OSD_B, _DISABLE);

        OsdFuncApplyMapOsdAB(WIDTH(_OSD_HOTKEY_MENU_WIDTH), HEIGHT(_OSD_HOTKEY_MENU_HEIGHT + ucRowOffset), COLOR(_CP_WHITE, _CP_BG), WIDTH(_OSD_HOTKEY_MENU_WIDTH), HEIGHT(_OSD_HOTKEY_MENU_HEIGHT + ucRowOffset), COLOR(_CP_WHITE, _CP_BG));

#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
        OsdFuncMapRotation(GET_OSD_ROTATE_STATUS(), _OSD_MAP_A_REMAPPING_ENABLE, HEIGHT(_OSD_HOTKEY_MENU_HEIGHT + ucRowOffset), _OSD_MAP_B_REMAPPING_ENABLE, HEIGHT(_OSD_HOTKEY_MENU_HEIGHT + ucRowOffset), _OSD_FONT_LIB_ROTATION_ENABLE);
#endif

        OsdFuncBlending(_OSD_TRANSPARENCY_WINDOW_AND_CHARACTER_BACKGROUND);
        OsdFuncTransparency(GET_OSD_TRANSPARENCY_STATUS());

        // Adjust Color Palette
        OsdPaletteSelectPalette(_PALETTE_MAIN_MENU);

        // Load Font & Icon
        OsdFuncSet2BitIconOffset(_2BIT_ICON_OFFSET);

        OsdFontVLCLoadFont(_FONT1_GLOBAL);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_SUPPORT_ICON, _ICON_NO_SUPPORT);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_SUPPORT_TEXT_0, _ICON_NO_SUPPORT_TEXT_0);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_SUPPORT_TEXT_1, _ICON_NO_SUPPORT_TEXT_1);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_CABLE_ICON, _ICON_NO_CABLE);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_CABLE_TEXT_0, _ICON_NO_CABLE_TEXT_0);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_CABLE_TEXT_1, _ICON_NO_CABLE_TEXT_1);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_SIGNAL_ICON, _ICON_NO_SIGNAL);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_SIGNAL_TEXT_0, _ICON_NO_SIGNAL_TEXT_0);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_SIGNAL_TEXT_1, _ICON_NO_SIGNAL_TEXT_1);
    }

    OsdDispMpDisplayStateNotice(ROW(0 + ucRowOffset), COL(0), ucNoticeT, _DISPLAY_RGN_TOP, _PFONT_PAGE_0);
    OsdDispMpDisplayStateNoticeFontB(ROW(0 + ucRowOffset), COL(0), ucNoticeB, _DISPLAY_RGN_BOTTOM, _PFONT_PAGE_1);

    switch(GET_OSD_ROTATE_STATUS())
    {
        case _OSD_ROTATE_DEGREE_0:
#if(_DM_FUNCTION == _ON)
#if(_IS_MAIN_PROCESS_CPU == _TRUE)
            if(ucNoticeT != _OSD_NOTICE_KEEP)
            {
                if((UserCommonColorDMGetDMStatus(_DISPLAY_RGN_TOP) == _TRUE) && (GET_OSD_DVISION_NOTICE(SysRegionGetInputPort(_DISPLAY_RGN_TOP)) == _ON))
                {
                    OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_A, (_PANEL_DH_WIDTH - _OSD_HOTKEY_MENU_WIDTH * ucFonWidth), 0);
                }
                else
                {
                    OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_A, ((_PANEL_DH_WIDTH / 2) - (_MESSAGE_WIDTH_MID_FONT_NUM * ucFonWidth)), ((_PANEL_DV_HEIGHT / 4) - (_MESSAGE_HEIGHT_MID_FONT_NUM * ucFonHeight)));
                }
                UserCommonTimerWaitForDDomainEvent(_EVENT_DEN_STOP);
                UserCommonOsdMapABFunctionEnable(_OSD_A, _ENABLE);
            }
            if(ucNoticeB != _OSD_NOTICE_KEEP)
            {
                if((UserCommonColorDMGetDMStatus(_DISPLAY_RGN_BOTTOM) == _TRUE) && (GET_OSD_DVISION_NOTICE(SysRegionGetInputPort(_DISPLAY_RGN_BOTTOM)) == _ON))
                {
                    OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_B, (_PANEL_DH_WIDTH - _OSD_HOTKEY_MENU_WIDTH * ucFonWidth), (_PANEL_DV_HEIGHT / 2));
                }
                else
                {
                    OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_B, ((_PANEL_DH_WIDTH / 2) - (_MESSAGE_WIDTH_MID_FONT_NUM * ucFonWidth)), ((_PANEL_DV_HEIGHT / 4 * 3) - (_MESSAGE_HEIGHT_MID_FONT_NUM * ucFonHeight)));
                }
                UserCommonTimerWaitForDDomainEvent(_EVENT_DEN_STOP);
                UserCommonOsdMapABFunctionEnable(_OSD_B, _ENABLE);
            }
#endif
#else
            OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_A, ((_PANEL_DH_WIDTH / 2) - (_MESSAGE_WIDTH_MID_FONT_NUM * ucFonWidth)), ((_PANEL_DV_HEIGHT / 4) - (_MESSAGE_HEIGHT_MID_FONT_NUM * ucFonHeight)));
            UserCommonOsdMapABFunctionEnable(_OSD_A, _ENABLE);
            OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_B, ((_PANEL_DH_WIDTH / 2) - (_MESSAGE_WIDTH_MID_FONT_NUM * ucFonWidth)), ((_PANEL_DV_HEIGHT / 4 * 3) - (_MESSAGE_HEIGHT_MID_FONT_NUM * ucFonHeight)));
            UserCommonOsdMapABFunctionEnable(_OSD_B, _ENABLE);
#endif
            break;
        case _OSD_ROTATE_DEGREE_180:
            OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_A, ((_PANEL_DH_WIDTH / 2) - (_MESSAGE_WIDTH_MID_FONT_NUM * ucFonWidth)), ((_PANEL_DV_HEIGHT / 4 * 3) - (_MESSAGE_HEIGHT_MID_FONT_NUM * ucFonHeight)));
            OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_B, ((_PANEL_DH_WIDTH / 2) - (_MESSAGE_WIDTH_MID_FONT_NUM * ucFonWidth)), ((_PANEL_DV_HEIGHT / 4) - (_MESSAGE_HEIGHT_MID_FONT_NUM * ucFonHeight)));
            break;
        case _OSD_ROTATE_DEGREE_90:
        case _OSD_ROTATE_DEGREE_270:
            OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_A, ((_PANEL_DH_WIDTH / 2) - (_MESSAGE_HEIGHT_MID_FONT_NUM * ucFonHeight)), ((_PANEL_DV_HEIGHT / 4) - (_MESSAGE_WIDTH_MID_FONT_NUM * ucFonWidth)));
            OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_B, ((_PANEL_DH_WIDTH / 2) - (_MESSAGE_HEIGHT_MID_FONT_NUM * ucFonHeight)), ((_PANEL_DV_HEIGHT / 4 * 3) - (_MESSAGE_WIDTH_MID_FONT_NUM * ucFonWidth)));
            break;
        default:
            break;
    }

    OsdFuncEnableOsd();
}
#endif // End of #if(_2P_PBP_TB_DISPLAY_SUPPORT == _ON)

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
//--------------------------------------------------
// Description  : No signal & No cable & No support for Multi 2P PIP
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdDispMpDisplayStateNotice_2P_PIP(BYTE ucNoticeMain, BYTE ucNoticeSub)
{
    WORD usHPos = 0;
    WORD usHWidth = 0;
    WORD usVPos = 0;
    WORD usVHeight = 0;
    WORD usPostionH = 0xFFFF;
    WORD usPostionV = 0xFFFF;
    StructTimingFormat stTimingFormat;
    BYTE ucFonWidth = _FONT_WIDTH;
    BYTE ucFonHeight = _FONT_HEIGHT;
#if(_DM_FUNCTION == _ON)
    BYTE ucRowOffset = 8;
#else
    BYTE ucRowOffset = 0;
#endif

    if(GET_OSD_DOUBLE_SIZE() == _ON)
    {
        ucFonWidth = _FONT_WIDTH * 2;
        ucFonHeight = _FONT_HEIGHT * 2;
    }

    memset(&stTimingFormat, 0x00, sizeof(StructTimingFormat));

    if(GET_OSD_STATE() != _MENU_HOTKEY_INFORMATION)
    {
        OsdFuncDisableOsd();

        UserCommonOsdMapABFunctionEnable(_OSD_A, _DISABLE);
        UserCommonOsdMapABFunctionEnable(_OSD_B, _DISABLE);

        SET_OSD_STATE(_MENU_HOTKEY_INFORMATION);

        g_usFontPointer0 = _OSD_PAGE_0_START;
        g_usFontPointer1 = _OSD_PAGE_1_START;
        g_usFontPointer2 = _OSD_PAGE_2_START;

        OsdFuncApplyMapOsdAB(WIDTH(_OSD_HOTKEY_MENU_WIDTH), HEIGHT(_OSD_HOTKEY_MENU_HEIGHT + ucRowOffset), COLOR(_CP_WHITE, _CP_BG), WIDTH(_OSD_HOTKEY_MENU_WIDTH), HEIGHT(_OSD_HOTKEY_MENU_HEIGHT + ucRowOffset), COLOR(_CP_WHITE, _CP_BG));

#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
        OsdFuncMapRotation(GET_OSD_ROTATE_STATUS(), _OSD_MAP_A_REMAPPING_ENABLE, HEIGHT(_OSD_HOTKEY_MENU_HEIGHT + ucRowOffset), _OSD_MAP_B_REMAPPING_ENABLE, HEIGHT(_OSD_HOTKEY_MENU_HEIGHT + ucRowOffset), _OSD_FONT_LIB_ROTATION_ENABLE);
#endif

        OsdFuncBlending(_OSD_TRANSPARENCY_WINDOW_AND_CHARACTER_BACKGROUND);
        OsdFuncTransparency(GET_OSD_TRANSPARENCY_STATUS());

        // Adjust Color Palette
        OsdPaletteSelectPalette(_PALETTE_MAIN_MENU);

        // Load Font & Icon
        OsdFuncSet2BitIconOffset(_2BIT_ICON_OFFSET);

        OsdFontVLCLoadFont(_FONT1_GLOBAL);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_SUPPORT_ICON, _ICON_NO_SUPPORT);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_SUPPORT_TEXT_0, _ICON_NO_SUPPORT_TEXT_0);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_SUPPORT_TEXT_1, _ICON_NO_SUPPORT_TEXT_1);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_CABLE_ICON, _ICON_NO_CABLE);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_CABLE_TEXT_0, _ICON_NO_CABLE_TEXT_0);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_CABLE_TEXT_1, _ICON_NO_CABLE_TEXT_1);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_SIGNAL_ICON, _ICON_NO_SIGNAL);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_SIGNAL_TEXT_0, _ICON_NO_SIGNAL_TEXT_0);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_SIGNAL_TEXT_1, _ICON_NO_SIGNAL_TEXT_1);
    }

    OsdDispMpDisplayStateNotice(ROW(0 + ucRowOffset), COL(0), ucNoticeMain, _DISPLAY_RGN_PIP_MAIN, _PFONT_PAGE_0);
    OsdDispMpDisplayStateNoticeFontB(ROW(0 + ucRowOffset), COL(0), ucNoticeSub, _DISPLAY_RGN_PIP_SUB, _PFONT_PAGE_1);

    UserCommonDisplayGetPipSubBackground(&stTimingFormat);

    usHWidth = _PANEL_DH_WIDTH / 2;
    usVHeight = _PANEL_DV_HEIGHT / 2;

    usPostionH = 0xFFFF;
    usPostionV = 0xFFFF;
    if(_TRUE)
    {
        switch(GET_OSD_PIP_POSITION_TYPE())
        {
            case _PIP_POSITON_LT:
                usHPos = 0;
                usVPos = 0;
                usPostionH = (usHPos + usHWidth + ((_PANEL_DH_WIDTH - usHPos - usHWidth - _OSD_HOTKEY_MENU_WIDTH * ucFonWidth) / 2));
                usPostionV = usVPos + usVHeight + ((_PANEL_DV_HEIGHT - usVPos - usVHeight - _OSD_HOTKEY_MENU_HEIGHT * ucFonHeight) / 2);
                break;

            case _PIP_POSITON_LB:
                usHPos = 0;
                usVPos = _PANEL_DV_START + usVHeight;
                usPostionH = (usHPos + usHWidth + ((_PANEL_DH_WIDTH - usHPos - usHWidth - _OSD_HOTKEY_MENU_WIDTH * ucFonWidth) / 2));
                usPostionV = (usVPos - _OSD_HOTKEY_MENU_HEIGHT * ucFonHeight) / 2;
                break;

            case _PIP_POSITON_RT:
                usHPos = _PANEL_DH_START + usHWidth;
                usVPos = 0;
                usPostionH = (usHPos - _OSD_HOTKEY_MENU_WIDTH * ucFonWidth) / 2;
                usPostionV = usVPos + usVHeight + ((_PANEL_DV_HEIGHT - usVPos - usVHeight - _OSD_HOTKEY_MENU_HEIGHT * ucFonHeight) / 2);
                break;

            case _PIP_POSITON_RB:
                usHPos = _PANEL_DH_START + usHWidth;
                usVPos = _PANEL_DV_START + usVHeight;
                usPostionH = (usHPos - _OSD_HOTKEY_MENU_WIDTH * ucFonWidth) / 2;
                usPostionV = (usVPos - _OSD_HOTKEY_MENU_HEIGHT * ucFonHeight) / 2;
                break;

            case _PIP_POSITON_MIDDLE:
                // usHPos = (_PANEL_DH_WIDTH - usHWidth) / 2;
                usVPos = (_PANEL_DV_HEIGHT - usVHeight) / 2;
                usPostionH = (_PANEL_DH_WIDTH - _OSD_HOTKEY_MENU_WIDTH * ucFonWidth) / 2;
                usPostionV = (usVPos - _OSD_HOTKEY_MENU_HEIGHT * ucFonHeight) / 2;
                break;

            case _PIP_POSITON_USER:
                usHPos = (stTimingFormat.usHStart - _PANEL_DH_START);
                usHWidth = (stTimingFormat.usHWidth - GET_OSD_SELECT_REGION_WIDTH());
                usVPos = (stTimingFormat.usVStart - _PANEL_DV_START);
                usVHeight = (stTimingFormat.usVHeight - GET_OSD_SELECT_REGION_WIDTH());

                if(GET_OSD_PIP_USER_POSITION_H() >= _OSD_PIP_USER_POSITION_H_CENTER)
                {
                    usPostionH = (usHPos - _OSD_HOTKEY_MENU_WIDTH * ucFonWidth) / 2;
                }
                else
                {
                    usPostionH = (usHPos + usHWidth + ((_PANEL_DH_WIDTH - usHPos - usHWidth - _OSD_HOTKEY_MENU_WIDTH * ucFonWidth) / 2));
                }

                if(GET_OSD_PIP_USER_POSITION_V() >= _OSD_PIP_USER_POSITION_V_CENTER)
                {
                    usPostionV = (usVPos - _OSD_HOTKEY_MENU_HEIGHT * ucFonHeight) / 2;
                }
                else
                {
                    usPostionV = usVPos + usVHeight + ((_PANEL_DV_HEIGHT - usVPos - usVHeight - _OSD_HOTKEY_MENU_HEIGHT * ucFonHeight) / 2);
                }
                break;

            default:
                break;
        }

        switch(GET_OSD_ROTATE_STATUS())
        {
            case _OSD_ROTATE_DEGREE_0:
                break;
            case _OSD_ROTATE_DEGREE_180:
                usPostionH = _PANEL_DH_WIDTH - usPostionH - _OSD_HOTKEY_MENU_WIDTH * ucFonWidth;
                usPostionV = _PANEL_DV_HEIGHT - usPostionV - _OSD_HOTKEY_MENU_HEIGHT * ucFonHeight;
                break;
            case _OSD_ROTATE_DEGREE_90:
            case _OSD_ROTATE_DEGREE_270:
                if(GET_OSD_PIP_POSITION_TYPE() == _PIP_POSITON_MIDDLE)
                {
                    usPostionH += (_PANEL_DH_WIDTH / 3);
                }
                usPostionH += (_OSD_HOTKEY_MENU_WIDTH * ucFonWidth / 2);
                usPostionH = (usPostionH > (_OSD_HOTKEY_MENU_HEIGHT * ucFonHeight / 2)) ? (usPostionH - (_OSD_HOTKEY_MENU_HEIGHT * ucFonHeight / 2)) : (usPostionH - (_OSD_HOTKEY_MENU_WIDTH * ucFonWidth / 2));
                usPostionV += (_OSD_HOTKEY_MENU_HEIGHT * ucFonHeight / 2);
                usPostionV = (usPostionV > (_OSD_HOTKEY_MENU_WIDTH * ucFonWidth / 2)) ? (usPostionV - (_OSD_HOTKEY_MENU_WIDTH * ucFonWidth / 2)) : (usPostionV - (_OSD_HOTKEY_MENU_HEIGHT * ucFonHeight / 2));
                break;
            default:
                break;
        }
    }
#if(_DM_FUNCTION == _ON)
#if(_IS_MAIN_PROCESS_CPU == _TRUE)
    if(ucNoticeMain != _OSD_NOTICE_KEEP)
    {
        if((UserCommonColorDMGetDMStatus(_DISPLAY_RGN_PIP_MAIN) == _TRUE) || (GET_OSD_DVISION_NOTICE(SysRegionGetInputPort(_DISPLAY_RGN_PIP_MAIN)) == _ON))
        {
            // change OSD position to up right
            OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_A, (_PANEL_DH_WIDTH - _OSD_HOTKEY_MENU_WIDTH * ucFonWidth), 0);
        }
        else
        {
            // change OSD position to center
            OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_A, usPostionH, usPostionV);
        }
        UserCommonTimerWaitForDDomainEvent(_EVENT_DEN_STOP);
        UserCommonOsdMapABFunctionEnable(_OSD_A, _ENABLE);
    }
#endif
#else
    OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_A, usPostionH, usPostionV);
    UserCommonOsdMapABFunctionEnable(_OSD_A, _ENABLE);
#endif

    ////////// Sub
    usHPos = (stTimingFormat.usHStart - _PANEL_DH_START);
    usHWidth = (stTimingFormat.usHWidth - GET_OSD_SELECT_REGION_WIDTH());
    usVPos = (stTimingFormat.usVStart - _PANEL_DV_START);
    usVHeight = (stTimingFormat.usVHeight - GET_OSD_SELECT_REGION_WIDTH());

    usPostionH = 0xFFFF;
    usPostionV = 0xFFFF;
    if(_TRUE)
    {
        if((_OSD_HOTKEY_MENU_WIDTH * ucFonWidth) > usHWidth)
        {
            usPostionH = (usHPos);
        }
        else
        {
            usPostionH = (usHPos + ((usHWidth - _OSD_HOTKEY_MENU_WIDTH * ucFonWidth) / 2));
        }

        if((_OSD_HOTKEY_MENU_HEIGHT * ucFonHeight) > usVHeight)
        {
            usPostionV = usVPos;
        }
        else
        {
            usPostionV = usVPos + ((usVHeight - _OSD_HOTKEY_MENU_HEIGHT * ucFonHeight) / 2);
        }

        switch(GET_OSD_ROTATE_STATUS())
        {
            case _OSD_ROTATE_DEGREE_0:
                break;
            case _OSD_ROTATE_DEGREE_180:
                usPostionH = _PANEL_DH_WIDTH - usPostionH - _OSD_HOTKEY_MENU_WIDTH * ucFonWidth;
                usPostionV = _PANEL_DV_HEIGHT - usPostionV - _OSD_HOTKEY_MENU_HEIGHT * ucFonHeight;
                break;
            case _OSD_ROTATE_DEGREE_90:
            case _OSD_ROTATE_DEGREE_270:
                usPostionH += (_OSD_HOTKEY_MENU_WIDTH * ucFonWidth / 2);
                usPostionH = (usPostionH > (_OSD_HOTKEY_MENU_HEIGHT * ucFonHeight / 2)) ? (usPostionH - (_OSD_HOTKEY_MENU_HEIGHT * ucFonHeight / 2)) : (usPostionH - (_OSD_HOTKEY_MENU_WIDTH * ucFonWidth / 2));
                usPostionV += (_OSD_HOTKEY_MENU_HEIGHT * ucFonHeight / 2);
                usPostionV = (usPostionV > (_OSD_HOTKEY_MENU_WIDTH * ucFonWidth / 2)) ? (usPostionV - (_OSD_HOTKEY_MENU_WIDTH * ucFonWidth / 2)) : (usPostionV - (_OSD_HOTKEY_MENU_HEIGHT * ucFonHeight / 2));
                usPostionV = ((usPostionV + _OSD_HOTKEY_MENU_WIDTH * ucFonWidth) > _PANEL_DV_END) ? (_PANEL_DV_END - _OSD_HOTKEY_MENU_WIDTH * ucFonWidth) : (usPostionV);
                break;
            default:
                break;
        }
    }

#if(_DM_FUNCTION == _ON)
#if(_IS_MAIN_PROCESS_CPU == _TRUE)
    if(ucNoticeSub != _OSD_NOTICE_KEEP)
    {
        if((UserCommonColorDMGetDMStatus(_DISPLAY_RGN_PIP_SUB) == _TRUE) && (GET_OSD_DVISION_NOTICE(SysRegionGetInputPort(_DISPLAY_RGN_PIP_SUB)) == _ON))
        {
            usPostionH = (stTimingFormat.usHStart - _PANEL_DH_START) + stTimingFormat.usHWidth - (_OSD_HOTKEY_MENU_WIDTH * ucFonWidth);
            usPostionV = (stTimingFormat.usVStart - _PANEL_DV_START);
            OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_B, usPostionH, usPostionV);
        }
        else
        {
            // change OSD position to center
            OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_B, usPostionH, usPostionV);
        }
        UserCommonTimerWaitForDDomainEvent(_EVENT_DEN_STOP);
        UserCommonOsdMapABFunctionEnable(_OSD_B, _ENABLE);
    }
#endif
#else
    OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_B, usPostionH, usPostionV);
    UserCommonOsdMapABFunctionEnable(_OSD_B, _ENABLE);
#endif

    OsdFuncEnableOsd();
}
#endif // End of #if(_2P_PIP_DISPLAY_SUPPORT == _ON)
#if(_3P_SKEW_LR_DISPLAY_SUPPORT == _ON)
//--------------------------------------------------
// Description  : No signal & No cable & No support for Multi 3P
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdDispMpDisplayStateNotice_3P_SKEWL(BYTE ucNotice1P, BYTE ucNotice2P, BYTE ucNotice3P)
{
    BYTE ucFonWidth = _FONT_WIDTH;
    BYTE ucFonHeight = _FONT_HEIGHT;

    if(GET_OSD_DOUBLE_SIZE() == _ON)
    {
        ucFonWidth = _FONT_WIDTH * 2;
        ucFonHeight = _FONT_HEIGHT * 2;
    }

    DebugMessageOsd("4.ucNotice1P", ucNotice1P);
    DebugMessageOsd("4.ucNotice2P", ucNotice2P);
    DebugMessageOsd("4.ucNotice3P", ucNotice3P);

    if(GET_OSD_STATE() != _MENU_HOTKEY_INFORMATION)
    {
        OsdFuncDisableOsd();

        UserCommonOsdMapABFunctionEnable(_OSD_B, _ENABLE);

        SET_OSD_STATE(_MENU_HOTKEY_INFORMATION);

        g_usFontPointer0 = _OSD_PAGE_0_START;
        g_usFontPointer1 = _OSD_PAGE_1_START;
        g_usFontPointer2 = _OSD_PAGE_2_START;

        if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_0) ||
           (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_180))
        {
            OsdFuncApplyMapOsdAB(WIDTH(_MESSAGE_WIDTH_FONT_NUM), HEIGHT(_MESSAGE_HEIGHT_FONT_NUM), COLOR(_CP_WHITE, _CP_BG), WIDTH(_MESSAGE_WIDTH_FONT_NUM), HEIGHT(_MESSAGE_HEIGHT_FONT_NUM + (_PANEL_DV_HEIGHT / 2 / ucFonHeight)), COLOR(_CP_WHITE, _CP_BG));
#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
            OsdFuncMapRotation(GET_OSD_ROTATE_STATUS(), _OSD_MAP_A_REMAPPING_ENABLE, HEIGHT(_MESSAGE_HEIGHT_FONT_NUM), _OSD_MAP_B_REMAPPING_ENABLE, HEIGHT((_MESSAGE_HEIGHT_FONT_NUM + (_PANEL_DV_HEIGHT / 2 / ucFonHeight))), _OSD_FONT_LIB_ROTATION_ENABLE);
#endif
        }
        else
        {
            OsdFuncApplyMapOsdAB(WIDTH(_MESSAGE_WIDTH_FONT_NUM), HEIGHT(_MESSAGE_HEIGHT_FONT_NUM), COLOR(_CP_WHITE, _CP_BG), WIDTH(_MESSAGE_WIDTH_FONT_NUM + (_PANEL_DV_HEIGHT / 2 / ucFonWidth)), HEIGHT(_MESSAGE_HEIGHT_FONT_NUM), COLOR(_CP_WHITE, _CP_BG));
#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
            OsdFuncMapRotation(GET_OSD_ROTATE_STATUS(), _OSD_MAP_A_REMAPPING_ENABLE, HEIGHT(_MESSAGE_HEIGHT_FONT_NUM), _OSD_MAP_B_REMAPPING_ENABLE, HEIGHT(_MESSAGE_HEIGHT_FONT_NUM), _OSD_FONT_LIB_ROTATION_ENABLE);
#endif
        }

        OsdFuncBlending(_OSD_TRANSPARENCY_WINDOW_AND_CHARACTER_BACKGROUND);
        OsdFuncTransparency(GET_OSD_TRANSPARENCY_STATUS());

        // Adjust Color Palette
        OsdPaletteSelectPalette(_PALETTE_MAIN_MENU);

        // Load Font & Icon
        OsdFuncSet2BitIconOffset(_2BIT_ICON_OFFSET);

        OsdFontVLCLoadFont(_FONT1_GLOBAL);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_SUPPORT_ICON, _ICON_NO_SUPPORT);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_SUPPORT_TEXT_0, _ICON_NO_SUPPORT_TEXT_0);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_SUPPORT_TEXT_1, _ICON_NO_SUPPORT_TEXT_1);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_CABLE_ICON, _ICON_NO_CABLE);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_CABLE_TEXT_0, _ICON_NO_CABLE_TEXT_0);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_CABLE_TEXT_1, _ICON_NO_CABLE_TEXT_1);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_SIGNAL_ICON, _ICON_NO_SIGNAL);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_SIGNAL_TEXT_0, _ICON_NO_SIGNAL_TEXT_0);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_SIGNAL_TEXT_1, _ICON_NO_SIGNAL_TEXT_1);
    }
    if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_0)
    {
        OsdDispMpDisplayStateNotice(ROW(0), COL(0), ucNotice1P, _DISPLAY_RGN_SKEW_L_MAIN, _PFONT_PAGE_0);

        OsdDispMpDisplayStateNoticeFontB(ROW(0), COL(0), ucNotice2P, _DISPLAY_RGN_SKEW_L_TOP, _PFONT_PAGE_1);
        OsdDispMpDisplayStateNoticeFontB(ROW(_PANEL_DV_HEIGHT / 2 / ucFonHeight), COL(0), ucNotice3P, _DISPLAY_RGN_SKEW_L_BOTTOM, _PFONT_PAGE_2);
    }
    else if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_180)
    {
        ////////// OSD A
        OsdDispMpDisplayStateNotice(ROW(0), COL(0), ucNotice1P, _DISPLAY_RGN_SKEW_L_MAIN, _PFONT_PAGE_0);

        ////////// OSD B
        OsdDispMpDisplayStateNoticeFontB(ROW(0), COL(0), ucNotice3P, _DISPLAY_RGN_SKEW_L_BOTTOM, _PFONT_PAGE_1);
        OsdDispMpDisplayStateNoticeFontB(ROW(_PANEL_DV_HEIGHT / 2 / ucFonHeight), COL(0), ucNotice2P, _DISPLAY_RGN_SKEW_L_TOP, _PFONT_PAGE_2);
    }
    else if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90)
    {
        ////////// OSD A
        OsdDispMpDisplayStateNotice(ROW(0), COL(0), ucNotice1P, _DISPLAY_RGN_SKEW_L_MAIN, _PFONT_PAGE_0);

        ////////// OSD B
        OsdDispMpDisplayStateNoticeFontB(ROW(0), COL(0), ucNotice2P, _DISPLAY_RGN_SKEW_L_TOP, _PFONT_PAGE_1);
        OsdDispMpDisplayStateNoticeFontB(ROW(0), COL(_PANEL_DV_HEIGHT / 2 / ucFonWidth), ucNotice3P, _DISPLAY_RGN_SKEW_L_BOTTOM, _PFONT_PAGE_2);
    }
    else if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270)
    {
        ////////// OSD A
        OsdDispMpDisplayStateNotice(ROW(0), COL(0), ucNotice1P, _DISPLAY_RGN_SKEW_L_MAIN, _PFONT_PAGE_0);

        ////////// OSD B
        OsdDispMpDisplayStateNoticeFontB(ROW(0), COL(0), ucNotice3P, _DISPLAY_RGN_SKEW_L_BOTTOM, _PFONT_PAGE_1);
        OsdDispMpDisplayStateNoticeFontB(ROW(0), COL(_PANEL_DV_HEIGHT / 2 / ucFonWidth), ucNotice2P, _DISPLAY_RGN_SKEW_L_TOP, _PFONT_PAGE_2);
    }

    if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_0)
    {
        OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_A, ((_PANEL_DH_WIDTH / 4) - (_MESSAGE_WIDTH_MID_FONT_NUM * ucFonWidth)), ((_PANEL_DV_HEIGHT / 2) - (_MESSAGE_HEIGHT_MID_FONT_NUM * ucFonHeight)));
        OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_B, ((_PANEL_DH_WIDTH / 4 * 3) - (_MESSAGE_WIDTH_MID_FONT_NUM * ucFonWidth)), ((_PANEL_DV_HEIGHT / 4) - (_MESSAGE_HEIGHT_MID_FONT_NUM * ucFonHeight)));
    }
    else if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_180)
    {
        OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_A, ((_PANEL_DH_WIDTH / 4 * 3) - (_MESSAGE_WIDTH_MID_FONT_NUM * ucFonWidth)), ((_PANEL_DV_HEIGHT / 2) - (_MESSAGE_HEIGHT_MID_FONT_NUM * ucFonHeight)));
        OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_B, ((_PANEL_DH_WIDTH / 4) - (_MESSAGE_WIDTH_MID_FONT_NUM * ucFonWidth)), ((_PANEL_DV_HEIGHT / 4) - (_MESSAGE_HEIGHT_MID_FONT_NUM * ucFonHeight)));
    }
    else if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) || (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
    {
        OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_A, ((_PANEL_DH_WIDTH / 4) - (_MESSAGE_HEIGHT_MID_FONT_NUM * ucFonHeight)), ((_PANEL_DV_HEIGHT / 2) - (_MESSAGE_WIDTH_MID_FONT_NUM * ucFonWidth)));
        OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_B, ((_PANEL_DH_WIDTH / 4 * 3) - (_MESSAGE_HEIGHT_MID_FONT_NUM * ucFonHeight)), ((_PANEL_DV_HEIGHT / 4) - (_MESSAGE_WIDTH_MID_FONT_NUM * ucFonWidth)));
    }

    OsdFuncEnableOsd();
}
//--------------------------------------------------
// Description  : No signal & No cable & No support for Multi 3P
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdDispMpDisplayStateNotice_3P_SKEWR(BYTE ucNotice1P, BYTE ucNotice2P, BYTE ucNotice3P)
{
    BYTE ucFonWidth = _FONT_WIDTH;
    BYTE ucFonHeight = _FONT_HEIGHT;

    if(GET_OSD_DOUBLE_SIZE() == _ON)
    {
        ucFonWidth = _FONT_WIDTH * 2;
        ucFonHeight = _FONT_HEIGHT * 2;
    }

    DebugMessageOsd("4.ucNotice1P", ucNotice1P);
    DebugMessageOsd("4.ucNotice2P", ucNotice2P);
    DebugMessageOsd("4.ucNotice3P", ucNotice3P);

    if(GET_OSD_STATE() != _MENU_HOTKEY_INFORMATION)
    {
        OsdFuncDisableOsd();

        UserCommonOsdMapABFunctionEnable(_OSD_B, _ENABLE);

        SET_OSD_STATE(_MENU_HOTKEY_INFORMATION);

        g_usFontPointer0 = _OSD_PAGE_0_START;
        g_usFontPointer1 = _OSD_PAGE_1_START;
        g_usFontPointer2 = _OSD_PAGE_2_START;

        if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_0) ||
           (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_180))
        {
            OsdFuncApplyMapOsdAB(WIDTH(_MESSAGE_WIDTH_FONT_NUM), HEIGHT(_MESSAGE_HEIGHT_FONT_NUM), COLOR(_CP_WHITE, _CP_BG), WIDTH(_MESSAGE_WIDTH_FONT_NUM), HEIGHT(_MESSAGE_HEIGHT_FONT_NUM + (_PANEL_DV_HEIGHT / 2 / ucFonHeight)), COLOR(_CP_WHITE, _CP_BG));
#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
            OsdFuncMapRotation(GET_OSD_ROTATE_STATUS(), _OSD_MAP_A_REMAPPING_ENABLE, HEIGHT(_MESSAGE_HEIGHT_FONT_NUM), _OSD_MAP_B_REMAPPING_ENABLE, HEIGHT((_MESSAGE_HEIGHT_FONT_NUM + (_PANEL_DV_HEIGHT / 2 / ucFonHeight))), _OSD_FONT_LIB_ROTATION_ENABLE);
#endif
        }
        else
        {
            OsdFuncApplyMapOsdAB(WIDTH(_MESSAGE_WIDTH_FONT_NUM), HEIGHT(_MESSAGE_HEIGHT_FONT_NUM), COLOR(_CP_WHITE, _CP_BG), WIDTH(_MESSAGE_WIDTH_FONT_NUM + (_PANEL_DV_HEIGHT / 2 / ucFonWidth)), HEIGHT(_MESSAGE_HEIGHT_FONT_NUM), COLOR(_CP_WHITE, _CP_BG));
#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
            OsdFuncMapRotation(GET_OSD_ROTATE_STATUS(), _OSD_MAP_A_REMAPPING_ENABLE, HEIGHT(_MESSAGE_HEIGHT_FONT_NUM), _OSD_MAP_B_REMAPPING_ENABLE, HEIGHT(_MESSAGE_HEIGHT_FONT_NUM), _OSD_FONT_LIB_ROTATION_ENABLE);
#endif
        }

        OsdFuncBlending(_OSD_TRANSPARENCY_WINDOW_AND_CHARACTER_BACKGROUND);
        OsdFuncTransparency(GET_OSD_TRANSPARENCY_STATUS());

        // Adjust Color Palette
        OsdPaletteSelectPalette(_PALETTE_MAIN_MENU);

        // Load Font & Icon
        OsdFuncSet2BitIconOffset(_2BIT_ICON_OFFSET);

        OsdFontVLCLoadFont(_FONT1_GLOBAL);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_SUPPORT_ICON, _ICON_NO_SUPPORT);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_SUPPORT_TEXT_0, _ICON_NO_SUPPORT_TEXT_0);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_SUPPORT_TEXT_1, _ICON_NO_SUPPORT_TEXT_1);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_CABLE_ICON, _ICON_NO_CABLE);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_CABLE_TEXT_0, _ICON_NO_CABLE_TEXT_0);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_CABLE_TEXT_1, _ICON_NO_CABLE_TEXT_1);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_SIGNAL_ICON, _ICON_NO_SIGNAL);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_SIGNAL_TEXT_0, _ICON_NO_SIGNAL_TEXT_0);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_SIGNAL_TEXT_1, _ICON_NO_SIGNAL_TEXT_1);
    }
    if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_0)
    {
        OsdDispMpDisplayStateNotice(ROW(0), COL(0), ucNotice1P, _DISPLAY_RGN_SKEW_R_MAIN, _PFONT_PAGE_0);

        OsdDispMpDisplayStateNoticeFontB(ROW(0), COL(0), ucNotice2P, _DISPLAY_RGN_SKEW_R_TOP, _PFONT_PAGE_1);
        OsdDispMpDisplayStateNoticeFontB(ROW(_PANEL_DV_HEIGHT / 2 / ucFonHeight), COL(0), ucNotice3P, _DISPLAY_RGN_SKEW_R_BOTTOM, _PFONT_PAGE_2);
    }
    else if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_180)
    {
        ////////// OSD A
        OsdDispMpDisplayStateNotice(ROW(0), COL(0), ucNotice1P, _DISPLAY_RGN_SKEW_R_MAIN, _PFONT_PAGE_0);

        ////////// OSD B
        OsdDispMpDisplayStateNoticeFontB(ROW(0), COL(0), ucNotice3P, _DISPLAY_RGN_SKEW_R_BOTTOM, _PFONT_PAGE_1);
        OsdDispMpDisplayStateNoticeFontB(ROW(_PANEL_DV_HEIGHT / 2 / ucFonHeight), COL(0), ucNotice2P, _DISPLAY_RGN_SKEW_R_TOP, _PFONT_PAGE_2);
    }
    else if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90)
    {
        ////////// OSD A
        OsdDispMpDisplayStateNotice(ROW(0), COL(0), ucNotice1P, _DISPLAY_RGN_SKEW_R_MAIN, _PFONT_PAGE_0);

        ////////// OSD B
        OsdDispMpDisplayStateNoticeFontB(ROW(0), COL(0), ucNotice2P, _DISPLAY_RGN_SKEW_R_TOP, _PFONT_PAGE_1);
        OsdDispMpDisplayStateNoticeFontB(ROW(0), COL(_PANEL_DV_HEIGHT / 2 / ucFonWidth), ucNotice3P, _DISPLAY_RGN_SKEW_R_BOTTOM, _PFONT_PAGE_2);
    }
    else if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270)
    {
        ////////// OSD A
        OsdDispMpDisplayStateNotice(ROW(0), COL(0), ucNotice1P, _DISPLAY_RGN_SKEW_R_MAIN, _PFONT_PAGE_0);

        ////////// OSD B
        OsdDispMpDisplayStateNoticeFontB(ROW(0), COL(0), ucNotice3P, _DISPLAY_RGN_SKEW_R_BOTTOM, _PFONT_PAGE_1);
        OsdDispMpDisplayStateNoticeFontB(ROW(0), COL(_PANEL_DV_HEIGHT / 2 / ucFonWidth), ucNotice2P, _DISPLAY_RGN_SKEW_R_TOP, _PFONT_PAGE_2);
    }

    if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_0)
    {
        OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_A, ((_PANEL_DH_WIDTH / 4 * 3) - (_MESSAGE_WIDTH_MID_FONT_NUM * ucFonWidth)), ((_PANEL_DV_HEIGHT / 2) - (_MESSAGE_HEIGHT_MID_FONT_NUM * ucFonHeight)));
        OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_B, ((_PANEL_DH_WIDTH / 4) - (_MESSAGE_WIDTH_MID_FONT_NUM * ucFonWidth)), ((_PANEL_DV_HEIGHT / 4) - (_MESSAGE_HEIGHT_MID_FONT_NUM * ucFonHeight)));
    }
    else if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_180)
    {
        OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_A, ((_PANEL_DH_WIDTH / 4) - (_MESSAGE_WIDTH_MID_FONT_NUM * ucFonWidth)), ((_PANEL_DV_HEIGHT / 2) - (_MESSAGE_HEIGHT_MID_FONT_NUM * ucFonHeight)));
        OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_B, ((_PANEL_DH_WIDTH / 4 * 3) - (_MESSAGE_WIDTH_MID_FONT_NUM * ucFonWidth)), ((_PANEL_DV_HEIGHT / 4) - (_MESSAGE_HEIGHT_MID_FONT_NUM * ucFonHeight)));
    }
    else if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) || (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
    {
        OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_A, ((_PANEL_DH_WIDTH / 4 * 3) - (_MESSAGE_HEIGHT_MID_FONT_NUM * ucFonHeight)), ((_PANEL_DV_HEIGHT / 2) - (_MESSAGE_WIDTH_MID_FONT_NUM * ucFonWidth)));
        OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_B, ((_PANEL_DH_WIDTH / 4) - (_MESSAGE_HEIGHT_MID_FONT_NUM * ucFonHeight)), ((_PANEL_DV_HEIGHT / 4) - (_MESSAGE_WIDTH_MID_FONT_NUM * ucFonWidth)));
    }

    OsdFuncEnableOsd();
}
#endif // End of #if(_3P_DISPLAY_SUPPORT == _ON)
#if(_3P_FLAG_DISPLAY_SUPPORT == _ON)
//--------------------------------------------------
// Description  : No signal & No cable & No support for Multi 4P
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdDispMpDisplayStateNotice_3P_FLAG(BYTE ucNotice1P, BYTE ucNotice2P, BYTE ucNotice3P)
{
    BYTE ucFonWidth = _FONT_WIDTH;
    BYTE ucFonHeight = _FONT_HEIGHT;

    if(GET_OSD_DOUBLE_SIZE() == _ON)
    {
        ucFonWidth = _FONT_WIDTH * 2;
        ucFonHeight = _FONT_HEIGHT * 2;
    }

    DebugMessageOsd("4.ucNotice1P", ucNotice1P);
    DebugMessageOsd("4.ucNotice2P", ucNotice2P);
    DebugMessageOsd("4.ucNotice3P", ucNotice3P);

    if(GET_OSD_STATE() != _MENU_HOTKEY_INFORMATION)
    {
        OsdFuncDisableOsd();

        UserCommonOsdMapABFunctionEnable(_OSD_B, _ENABLE);

        SET_OSD_STATE(_MENU_HOTKEY_INFORMATION);

        g_usFontPointer0 = _OSD_PAGE_0_START;
        g_usFontPointer1 = _OSD_PAGE_1_START;
        g_usFontPointer2 = _OSD_PAGE_2_START;

        if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_0) ||
           (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_180))
        {
            OsdFuncApplyMapOsdAB(WIDTH(_MESSAGE_WIDTH_FONT_NUM), HEIGHT(_MESSAGE_HEIGHT_FONT_NUM), COLOR(_CP_WHITE, _CP_BG), WIDTH(_MESSAGE_WIDTH_FONT_NUM + (_PANEL_DH_WIDTH / 8 * 3 / ucFonWidth)), HEIGHT(_MESSAGE_HEIGHT_FONT_NUM), COLOR(_CP_WHITE, _CP_BG));
#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
            OsdFuncMapRotation(GET_OSD_ROTATE_STATUS(), _OSD_MAP_A_REMAPPING_ENABLE, HEIGHT(_MESSAGE_HEIGHT_FONT_NUM), _OSD_MAP_B_REMAPPING_ENABLE, HEIGHT(_MESSAGE_HEIGHT_FONT_NUM), _OSD_FONT_LIB_ROTATION_ENABLE);
#endif
        }
        else
        {
            OsdFuncApplyMapOsdAB(WIDTH(_MESSAGE_WIDTH_FONT_NUM), HEIGHT(_MESSAGE_HEIGHT_FONT_NUM), COLOR(_CP_WHITE, _CP_BG), WIDTH(_MESSAGE_WIDTH_FONT_NUM), HEIGHT(_MESSAGE_HEIGHT_FONT_NUM + (_PANEL_DH_WIDTH / 8 * 3 / ucFonHeight)), COLOR(_CP_WHITE, _CP_BG));
#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
            OsdFuncMapRotation(GET_OSD_ROTATE_STATUS(), _OSD_MAP_A_REMAPPING_ENABLE, HEIGHT(_MESSAGE_HEIGHT_FONT_NUM), _OSD_MAP_B_REMAPPING_ENABLE, HEIGHT(_MESSAGE_HEIGHT_FONT_NUM), _OSD_FONT_LIB_ROTATION_ENABLE);
#endif
        }

        OsdFuncBlending(_OSD_TRANSPARENCY_WINDOW_AND_CHARACTER_BACKGROUND);
        OsdFuncTransparency(GET_OSD_TRANSPARENCY_STATUS());

        // Adjust Color Palette
        OsdPaletteSelectPalette(_PALETTE_MAIN_MENU);

        // Load Font & Icon
        OsdFuncSet2BitIconOffset(_2BIT_ICON_OFFSET);

        OsdFontVLCLoadFont(_FONT1_GLOBAL);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_SUPPORT_ICON, _ICON_NO_SUPPORT);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_SUPPORT_TEXT_0, _ICON_NO_SUPPORT_TEXT_0);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_SUPPORT_TEXT_1, _ICON_NO_SUPPORT_TEXT_1);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_CABLE_ICON, _ICON_NO_CABLE);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_CABLE_TEXT_0, _ICON_NO_CABLE_TEXT_0);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_CABLE_TEXT_1, _ICON_NO_CABLE_TEXT_1);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_SIGNAL_ICON, _ICON_NO_SIGNAL);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_SIGNAL_TEXT_0, _ICON_NO_SIGNAL_TEXT_0);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_SIGNAL_TEXT_1, _ICON_NO_SIGNAL_TEXT_1);
    }
    if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_0)
    {
        OsdDispMpDisplayStateNotice(ROW(0), COL(0), ucNotice2P, _DISPLAY_RGN_FLAG_LEFT, _PFONT_PAGE_0);

        OsdDispMpDisplayStateNoticeFontB(ROW(0), COL(0), ucNotice1P, _DISPLAY_RGN_FLAG_MAIN, _PFONT_PAGE_1);
        OsdDispMpDisplayStateNoticeFontB(ROW(0), COL(_PANEL_DH_WIDTH / 8 * 3 / ucFonWidth), ucNotice3P, _DISPLAY_RGN_FLAG_RIGHT, _PFONT_PAGE_2);
    }
    else if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_180)
    {
        ////////// OSD A
        OsdDispMpDisplayStateNotice(ROW(0), COL(0), ucNotice3P, _DISPLAY_RGN_FLAG_RIGHT, _PFONT_PAGE_0);

        ////////// OSD B
        OsdDispMpDisplayStateNoticeFontB(ROW(0), COL(0), ucNotice1P, _DISPLAY_RGN_FLAG_MAIN, _PFONT_PAGE_1);
        OsdDispMpDisplayStateNoticeFontB(ROW(0), COL(_PANEL_DH_WIDTH / 8 * 3 / ucFonWidth), ucNotice2P, _DISPLAY_RGN_FLAG_LEFT, _PFONT_PAGE_2);
    }
    else if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90)
    {
        ////////// OSD A
        OsdDispMpDisplayStateNotice(ROW(0), COL(0), ucNotice3P, _DISPLAY_RGN_FLAG_RIGHT, _PFONT_PAGE_0);

        ////////// OSD B
        OsdDispMpDisplayStateNoticeFontB(ROW(0), COL(0), ucNotice1P, _DISPLAY_RGN_FLAG_MAIN, _PFONT_PAGE_1);
        OsdDispMpDisplayStateNoticeFontB(ROW(_PANEL_DH_WIDTH / 8 * 3 / ucFonHeight), COL(0), ucNotice2P, _DISPLAY_RGN_FLAG_LEFT, _PFONT_PAGE_2);
    }
    else if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270)
    {
        ////////// OSD A
        OsdDispMpDisplayStateNotice(ROW(0), COL(0), ucNotice2P, _DISPLAY_RGN_FLAG_LEFT, _PFONT_PAGE_0);

        ////////// OSD B
        OsdDispMpDisplayStateNoticeFontB(ROW(0), COL(0), ucNotice1P, _DISPLAY_RGN_FLAG_MAIN, _PFONT_PAGE_1);
        OsdDispMpDisplayStateNoticeFontB(ROW(_PANEL_DH_WIDTH / 8 * 3 / ucFonHeight), COL(0), ucNotice3P, _DISPLAY_RGN_FLAG_RIGHT, _PFONT_PAGE_2);
    }

    switch(GET_OSD_ROTATE_STATUS())
    {
        case _OSD_ROTATE_DEGREE_0:
        case _OSD_ROTATE_DEGREE_180:
            OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_A, ((_PANEL_DH_WIDTH / 8) - (_MESSAGE_WIDTH_MID_FONT_NUM * ucFonWidth)), ((_PANEL_DV_HEIGHT / 2) - (_MESSAGE_HEIGHT_MID_FONT_NUM * ucFonHeight)));
            OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_B, ((_PANEL_DH_WIDTH / 2) - (_MESSAGE_WIDTH_MID_FONT_NUM * ucFonWidth)), ((_PANEL_DV_HEIGHT / 2) - (_MESSAGE_HEIGHT_MID_FONT_NUM * ucFonHeight)));
            break;
        case _OSD_ROTATE_DEGREE_90:
            OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_A, ((_PANEL_DH_WIDTH / 8 * 7) - (_MESSAGE_HEIGHT_MID_FONT_NUM * ucFonHeight)), ((_PANEL_DV_HEIGHT / 2) - (_MESSAGE_WIDTH_MID_FONT_NUM * ucFonWidth)));
            OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_B, ((_PANEL_DH_WIDTH / 8) - (_MESSAGE_HEIGHT_MID_FONT_NUM * ucFonHeight)), ((_PANEL_DV_HEIGHT / 2) - (_MESSAGE_WIDTH_MID_FONT_NUM * ucFonWidth)));
            break;
        case _OSD_ROTATE_DEGREE_270:
            OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_A, ((_PANEL_DH_WIDTH / 8) - (_MESSAGE_HEIGHT_MID_FONT_NUM * ucFonHeight)), ((_PANEL_DV_HEIGHT / 2) - (_MESSAGE_WIDTH_MID_FONT_NUM * ucFonWidth)));
            OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_B, ((_PANEL_DH_WIDTH / 8 * 4) - (_MESSAGE_HEIGHT_MID_FONT_NUM * ucFonHeight)), ((_PANEL_DV_HEIGHT / 2) - (_MESSAGE_WIDTH_MID_FONT_NUM * ucFonWidth)));
            break;
        default:
            break;
    }

    OsdFuncEnableOsd();
}
#endif // End of #if(_3P_DISPLAY_SUPPORT == _ON)
#if(_3P_SKEW_TB_DISPLAY_SUPPORT == _ON)
//--------------------------------------------------
// Description  : No signal & No cable & No support for Multi 3P
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdDispMpDisplayStateNotice_3P_SKEWT(BYTE ucNotice1P, BYTE ucNotice2P, BYTE ucNotice3P)
{
    BYTE ucFonWidth = _FONT_WIDTH;
    BYTE ucFonHeight = _FONT_HEIGHT;

    if(GET_OSD_DOUBLE_SIZE() == _ON)
    {
        ucFonWidth = _FONT_WIDTH * 2;
        ucFonHeight = _FONT_HEIGHT * 2;
    }

    DebugMessageOsd("4.ucNotice1P", ucNotice1P);
    DebugMessageOsd("4.ucNotice2P", ucNotice2P);
    DebugMessageOsd("4.ucNotice3P", ucNotice3P);

    if(GET_OSD_STATE() != _MENU_HOTKEY_INFORMATION)
    {
        OsdFuncDisableOsd();

        UserCommonOsdMapABFunctionEnable(_OSD_B, _ENABLE);

        SET_OSD_STATE(_MENU_HOTKEY_INFORMATION);

        g_usFontPointer0 = _OSD_PAGE_0_START;
        g_usFontPointer1 = _OSD_PAGE_1_START;
        g_usFontPointer2 = _OSD_PAGE_2_START;

        if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_0) ||
           (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_180))
        {
            OsdFuncApplyMapOsdAB(WIDTH(_MESSAGE_WIDTH_FONT_NUM), HEIGHT(_MESSAGE_HEIGHT_FONT_NUM), COLOR(_CP_WHITE, _CP_BG), WIDTH(_MESSAGE_WIDTH_FONT_NUM + (_PANEL_DH_WIDTH / 2 / ucFonWidth)), HEIGHT(_MESSAGE_HEIGHT_FONT_NUM), COLOR(_CP_WHITE, _CP_BG));
#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
            OsdFuncMapRotation(GET_OSD_ROTATE_STATUS(), _OSD_MAP_A_REMAPPING_ENABLE, HEIGHT(_MESSAGE_HEIGHT_FONT_NUM), _OSD_MAP_B_REMAPPING_ENABLE, HEIGHT(_MESSAGE_HEIGHT_FONT_NUM), _OSD_FONT_LIB_ROTATION_ENABLE);
#endif
        }
        else
        {
            OsdFuncApplyMapOsdAB(WIDTH(_MESSAGE_WIDTH_FONT_NUM), HEIGHT(_MESSAGE_HEIGHT_FONT_NUM), COLOR(_CP_WHITE, _CP_BG), WIDTH(_MESSAGE_WIDTH_FONT_NUM), HEIGHT(_MESSAGE_HEIGHT_FONT_NUM + (_PANEL_DH_WIDTH / 2 / ucFonHeight)), COLOR(_CP_WHITE, _CP_BG));
#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
            OsdFuncMapRotation(GET_OSD_ROTATE_STATUS(), _OSD_MAP_A_REMAPPING_ENABLE, HEIGHT(_MESSAGE_HEIGHT_FONT_NUM), _OSD_MAP_B_REMAPPING_ENABLE, HEIGHT(_MESSAGE_HEIGHT_FONT_NUM + (_PANEL_DH_WIDTH / 2 / ucFonHeight)), _OSD_FONT_LIB_ROTATION_ENABLE);
#endif
        }

        OsdFuncBlending(_OSD_TRANSPARENCY_WINDOW_AND_CHARACTER_BACKGROUND);
        OsdFuncTransparency(GET_OSD_TRANSPARENCY_STATUS());

        // Adjust Color Palette
        OsdPaletteSelectPalette(_PALETTE_MAIN_MENU);

        // Load Font & Icon
        OsdFuncSet2BitIconOffset(_2BIT_ICON_OFFSET);

        OsdFontVLCLoadFont(_FONT1_GLOBAL);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_SUPPORT_ICON, _ICON_NO_SUPPORT);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_SUPPORT_TEXT_0, _ICON_NO_SUPPORT_TEXT_0);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_SUPPORT_TEXT_1, _ICON_NO_SUPPORT_TEXT_1);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_CABLE_ICON, _ICON_NO_CABLE);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_CABLE_TEXT_0, _ICON_NO_CABLE_TEXT_0);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_CABLE_TEXT_1, _ICON_NO_CABLE_TEXT_1);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_SIGNAL_ICON, _ICON_NO_SIGNAL);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_SIGNAL_TEXT_0, _ICON_NO_SIGNAL_TEXT_0);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_SIGNAL_TEXT_1, _ICON_NO_SIGNAL_TEXT_1);
    }
    if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_0)
    {
        OsdDispMpDisplayStateNotice(ROW(0), COL(0), ucNotice1P, _DISPLAY_RGN_SKEW_T_MAIN, _PFONT_PAGE_0);

        OsdDispMpDisplayStateNoticeFontB(ROW(0), COL(0), ucNotice2P, _DISPLAY_RGN_SKEW_T_LEFT, _PFONT_PAGE_1);
        OsdDispMpDisplayStateNoticeFontB(ROW(0), COL(_PANEL_DH_WIDTH / 2 / ucFonWidth), ucNotice3P, _DISPLAY_RGN_SKEW_T_RIGHT, _PFONT_PAGE_2);
    }
    else if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_180)
    {
        ////////// OSD A
        OsdDispMpDisplayStateNotice(ROW(0), COL(0), ucNotice1P, _DISPLAY_RGN_SKEW_T_MAIN, _PFONT_PAGE_0);

        ////////// OSD B
        OsdDispMpDisplayStateNoticeFontB(ROW(0), COL(0), ucNotice3P, _DISPLAY_RGN_SKEW_T_RIGHT, _PFONT_PAGE_1);
        OsdDispMpDisplayStateNoticeFontB(ROW(0), COL(_PANEL_DH_WIDTH / 2 / ucFonWidth), ucNotice2P, _DISPLAY_RGN_SKEW_T_LEFT, _PFONT_PAGE_2);
    }
    else if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90)
    {
        ////////// OSD A
        OsdDispMpDisplayStateNotice(ROW(0), COL(0), ucNotice1P, _DISPLAY_RGN_SKEW_T_MAIN, _PFONT_PAGE_0);

        ////////// OSD B
        OsdDispMpDisplayStateNoticeFontB(ROW(0), COL(0), ucNotice3P, _DISPLAY_RGN_SKEW_T_RIGHT, _PFONT_PAGE_1);
        OsdDispMpDisplayStateNoticeFontB(ROW(_PANEL_DH_WIDTH / 2 / ucFonHeight), COL(0), ucNotice2P, _DISPLAY_RGN_SKEW_T_LEFT, _PFONT_PAGE_2);
    }
    else if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270)
    {
        ////////// OSD A
        OsdDispMpDisplayStateNotice(ROW(0), COL(0), ucNotice1P, _DISPLAY_RGN_SKEW_T_MAIN, _PFONT_PAGE_0);

        ////////// OSD B
        OsdDispMpDisplayStateNoticeFontB(ROW(0), COL(0), ucNotice2P, _DISPLAY_RGN_SKEW_T_LEFT, _PFONT_PAGE_1);
        OsdDispMpDisplayStateNoticeFontB(ROW(_PANEL_DH_WIDTH / 2 / ucFonHeight), COL(0), ucNotice3P, _DISPLAY_RGN_SKEW_T_RIGHT, _PFONT_PAGE_2);
    }

    if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_0)
    {
        OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_A, ((_PANEL_DH_WIDTH / 2) - (_MESSAGE_WIDTH_MID_FONT_NUM * ucFonWidth)), ((_PANEL_DV_HEIGHT / 4) - (_MESSAGE_HEIGHT_MID_FONT_NUM * ucFonHeight)));
        OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_B, ((_PANEL_DH_WIDTH / 4 * 1) - (_MESSAGE_WIDTH_MID_FONT_NUM * ucFonWidth)), ((_PANEL_DV_HEIGHT / 4 * 3) - (_MESSAGE_HEIGHT_MID_FONT_NUM * ucFonHeight)));
    }
    else if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_180)
    {
        OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_A, ((_PANEL_DH_WIDTH / 2) - (_MESSAGE_WIDTH_MID_FONT_NUM * ucFonWidth)), ((_PANEL_DV_HEIGHT / 4 * 3) - (_MESSAGE_HEIGHT_MID_FONT_NUM * ucFonHeight)));
        OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_B, ((_PANEL_DH_WIDTH / 4 * 1) - (_MESSAGE_WIDTH_MID_FONT_NUM * ucFonWidth)), ((_PANEL_DV_HEIGHT / 4 * 1) - (_MESSAGE_HEIGHT_MID_FONT_NUM * ucFonHeight)));
    }
    else if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) || (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
    {
        OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_A, ((_PANEL_DH_WIDTH / 2) - (_MESSAGE_HEIGHT_MID_FONT_NUM * ucFonHeight)), ((_PANEL_DV_HEIGHT / 4) - (_MESSAGE_WIDTH_MID_FONT_NUM * ucFonWidth)));
        OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_B, ((_PANEL_DH_WIDTH / 4 * 1) - (_MESSAGE_HEIGHT_MID_FONT_NUM * ucFonHeight)), ((_PANEL_DV_HEIGHT / 4 * 3) - (_MESSAGE_WIDTH_MID_FONT_NUM * ucFonWidth)));
    }

    OsdFuncEnableOsd();
}
//--------------------------------------------------
// Description  : No signal & No cable & No support for Multi 3P
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdDispMpDisplayStateNotice_3P_SKEWB(BYTE ucNotice1P, BYTE ucNotice2P, BYTE ucNotice3P)
{
    BYTE ucFonWidth = _FONT_WIDTH;
    BYTE ucFonHeight = _FONT_HEIGHT;

    if(GET_OSD_DOUBLE_SIZE() == _ON)
    {
        ucFonWidth = _FONT_WIDTH * 2;
        ucFonHeight = _FONT_HEIGHT * 2;
    }

    DebugMessageOsd("4.ucNotice1P", ucNotice1P);
    DebugMessageOsd("4.ucNotice2P", ucNotice2P);
    DebugMessageOsd("4.ucNotice3P", ucNotice3P);

    if(GET_OSD_STATE() != _MENU_HOTKEY_INFORMATION)
    {
        OsdFuncDisableOsd();

        UserCommonOsdMapABFunctionEnable(_OSD_B, _ENABLE);

        SET_OSD_STATE(_MENU_HOTKEY_INFORMATION);

        g_usFontPointer0 = _OSD_PAGE_0_START;
        g_usFontPointer1 = _OSD_PAGE_1_START;
        g_usFontPointer2 = _OSD_PAGE_2_START;

        if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_0) ||
           (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_180))
        {
            OsdFuncApplyMapOsdAB(WIDTH(_MESSAGE_WIDTH_FONT_NUM), HEIGHT(_MESSAGE_HEIGHT_FONT_NUM), COLOR(_CP_WHITE, _CP_BG), WIDTH(_MESSAGE_WIDTH_FONT_NUM + (_PANEL_DH_WIDTH / 2 / ucFonWidth)), HEIGHT(_MESSAGE_HEIGHT_FONT_NUM), COLOR(_CP_WHITE, _CP_BG));
#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
            OsdFuncMapRotation(GET_OSD_ROTATE_STATUS(), _OSD_MAP_A_REMAPPING_ENABLE, HEIGHT(_MESSAGE_HEIGHT_FONT_NUM), _OSD_MAP_B_REMAPPING_ENABLE, HEIGHT((_MESSAGE_HEIGHT_FONT_NUM)), _OSD_FONT_LIB_ROTATION_ENABLE);
#endif
        }
        else
        {
            OsdFuncApplyMapOsdAB(WIDTH(_MESSAGE_WIDTH_FONT_NUM), HEIGHT(_MESSAGE_HEIGHT_FONT_NUM), COLOR(_CP_WHITE, _CP_BG), WIDTH(_MESSAGE_WIDTH_FONT_NUM), HEIGHT(_MESSAGE_HEIGHT_FONT_NUM + (_PANEL_DH_WIDTH / 2 / ucFonHeight)), COLOR(_CP_WHITE, _CP_BG));
#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
            OsdFuncMapRotation(GET_OSD_ROTATE_STATUS(), _OSD_MAP_A_REMAPPING_ENABLE, HEIGHT(_MESSAGE_HEIGHT_FONT_NUM), _OSD_MAP_B_REMAPPING_ENABLE, HEIGHT(_MESSAGE_HEIGHT_FONT_NUM + (_PANEL_DH_WIDTH / 2 / ucFonHeight)), _OSD_FONT_LIB_ROTATION_ENABLE);
#endif
        }

        OsdFuncBlending(_OSD_TRANSPARENCY_WINDOW_AND_CHARACTER_BACKGROUND);
        OsdFuncTransparency(GET_OSD_TRANSPARENCY_STATUS());

        // Adjust Color Palette
        OsdPaletteSelectPalette(_PALETTE_MAIN_MENU);

        // Load Font & Icon
        OsdFuncSet2BitIconOffset(_2BIT_ICON_OFFSET);

        OsdFontVLCLoadFont(_FONT1_GLOBAL);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_SUPPORT_ICON, _ICON_NO_SUPPORT);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_SUPPORT_TEXT_0, _ICON_NO_SUPPORT_TEXT_0);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_SUPPORT_TEXT_1, _ICON_NO_SUPPORT_TEXT_1);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_CABLE_ICON, _ICON_NO_CABLE);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_CABLE_TEXT_0, _ICON_NO_CABLE_TEXT_0);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_CABLE_TEXT_1, _ICON_NO_CABLE_TEXT_1);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_SIGNAL_ICON, _ICON_NO_SIGNAL);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_SIGNAL_TEXT_0, _ICON_NO_SIGNAL_TEXT_0);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_SIGNAL_TEXT_1, _ICON_NO_SIGNAL_TEXT_1);
    }
    if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_0)
    {
        OsdDispMpDisplayStateNotice(ROW(0), COL(0), ucNotice1P, _DISPLAY_RGN_SKEW_B_MAIN, _PFONT_PAGE_0);

        OsdDispMpDisplayStateNoticeFontB(ROW(0), COL(0), ucNotice2P, _DISPLAY_RGN_SKEW_B_LEFT, _PFONT_PAGE_1);
        OsdDispMpDisplayStateNoticeFontB(ROW(0), COL(_PANEL_DH_WIDTH / 2 / ucFonWidth), ucNotice3P, _DISPLAY_RGN_SKEW_B_RIGHT, _PFONT_PAGE_2);
    }
    else if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_180)
    {
        ////////// OSD A
        OsdDispMpDisplayStateNotice(ROW(0), COL(0), ucNotice1P, _DISPLAY_RGN_SKEW_B_MAIN, _PFONT_PAGE_0);

        ////////// OSD B
        OsdDispMpDisplayStateNoticeFontB(ROW(0), COL(0), ucNotice3P, _DISPLAY_RGN_SKEW_B_RIGHT, _PFONT_PAGE_1);
        OsdDispMpDisplayStateNoticeFontB(ROW(0), COL(_PANEL_DH_WIDTH / 2 / ucFonWidth), ucNotice2P, _DISPLAY_RGN_SKEW_B_LEFT, _PFONT_PAGE_2);
    }
    else if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90)
    {
        ////////// OSD A
        OsdDispMpDisplayStateNotice(ROW(0), COL(0), ucNotice1P, _DISPLAY_RGN_SKEW_B_MAIN, _PFONT_PAGE_0);

        ////////// OSD B
        OsdDispMpDisplayStateNoticeFontB(ROW(0), COL(0), ucNotice3P, _DISPLAY_RGN_SKEW_B_RIGHT, _PFONT_PAGE_1);
        OsdDispMpDisplayStateNoticeFontB(ROW(_PANEL_DH_WIDTH / 2 / ucFonHeight), COL(0), ucNotice2P, _DISPLAY_RGN_SKEW_B_LEFT, _PFONT_PAGE_2);
    }
    else if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270)
    {
        ////////// OSD A
        OsdDispMpDisplayStateNotice(ROW(0), COL(0), ucNotice1P, _DISPLAY_RGN_SKEW_B_MAIN, _PFONT_PAGE_0);

        ////////// OSD B
        OsdDispMpDisplayStateNoticeFontB(ROW(0), COL(0), ucNotice2P, _DISPLAY_RGN_SKEW_B_LEFT, _PFONT_PAGE_1);
        OsdDispMpDisplayStateNoticeFontB(ROW((_PANEL_DH_WIDTH / 2 / ucFonHeight)), COL(0), ucNotice3P, _DISPLAY_RGN_SKEW_B_RIGHT, _PFONT_PAGE_2);
    }

    if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_0)
    {
        OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_A, ((_PANEL_DH_WIDTH / 2) - (_MESSAGE_WIDTH_MID_FONT_NUM * ucFonWidth)), ((_PANEL_DV_HEIGHT / 4 * 3) - (_MESSAGE_HEIGHT_MID_FONT_NUM * ucFonHeight)));
        OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_B, ((_PANEL_DH_WIDTH / 4) - (_MESSAGE_WIDTH_MID_FONT_NUM * ucFonWidth)), ((_PANEL_DV_HEIGHT / 4) - (_MESSAGE_HEIGHT_MID_FONT_NUM * ucFonHeight)));
    }
    else if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_180)
    {
        OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_A, ((_PANEL_DH_WIDTH / 2) - (_MESSAGE_WIDTH_MID_FONT_NUM * ucFonWidth)), ((_PANEL_DV_HEIGHT / 4) - (_MESSAGE_HEIGHT_MID_FONT_NUM * ucFonHeight)));
        OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_B, ((_PANEL_DH_WIDTH / 4 * 1) - (_MESSAGE_WIDTH_MID_FONT_NUM * ucFonWidth)), ((_PANEL_DV_HEIGHT / 4 * 3) - (_MESSAGE_HEIGHT_MID_FONT_NUM * ucFonHeight)));
    }
    else if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) || (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
    {
        OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_A, ((_PANEL_DH_WIDTH / 2) - (_MESSAGE_HEIGHT_MID_FONT_NUM * ucFonHeight)), ((_PANEL_DV_HEIGHT / 4 * 3) - (_MESSAGE_WIDTH_MID_FONT_NUM * ucFonWidth)));
        OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_B, ((_PANEL_DH_WIDTH / 4) - (_MESSAGE_HEIGHT_MID_FONT_NUM * ucFonHeight)), ((_PANEL_DV_HEIGHT / 4) - (_MESSAGE_WIDTH_MID_FONT_NUM * ucFonWidth)));
    }

    OsdFuncEnableOsd();
}
#endif // End of #if(_3P_DISPLAY_SUPPORT == _ON)

#if(_4P_DISPLAY_SUPPORT == _ON)
//--------------------------------------------------
// Description  : No signal & No cable & No support for Multi 4P
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdDispMpDisplayStateNotice_4P(BYTE ucNotice1P, BYTE ucNotice2P, BYTE ucNotice3P, BYTE ucNotice4P)
{
    BYTE ucFonWidth = _FONT_WIDTH;
    BYTE ucFonHeight = _FONT_HEIGHT;

    if(GET_OSD_DOUBLE_SIZE() == _ON)
    {
        ucFonWidth = _FONT_WIDTH * 2;
        ucFonHeight = _FONT_HEIGHT * 2;
    }

    DebugMessageOsd("4.ucNotice1P", ucNotice1P);
    DebugMessageOsd("4.ucNotice2P", ucNotice2P);
    DebugMessageOsd("4.ucNotice3P", ucNotice3P);
    DebugMessageOsd("4.ucNotice4P", ucNotice4P);

    if(GET_OSD_STATE() != _MENU_HOTKEY_INFORMATION)
    {
        OsdFuncDisableOsd();

        UserCommonOsdMapABFunctionEnable(_OSD_B, _ENABLE);

        SET_OSD_STATE(_MENU_HOTKEY_INFORMATION);

        g_usFontPointer0 = _OSD_PAGE_0_START;
        g_usFontPointer1 = _OSD_PAGE_1_START;
        g_usFontPointer2 = _OSD_PAGE_2_START;

        if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_0) ||
           (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_180))
        {
            OsdFuncApplyMapOsdAB(WIDTH(_MESSAGE_WIDTH_FONT_NUM), HEIGHT(_MESSAGE_HEIGHT_FONT_NUM + (_PANEL_DV_HEIGHT / 2 / ucFonHeight)), COLOR(_CP_WHITE, _CP_BG), WIDTH(_MESSAGE_WIDTH_FONT_NUM), HEIGHT(_MESSAGE_HEIGHT_FONT_NUM + (_PANEL_DV_HEIGHT / 2 / ucFonHeight)), COLOR(_CP_WHITE, _CP_BG));
#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
            OsdFuncMapRotation(GET_OSD_ROTATE_STATUS(), _OSD_MAP_A_REMAPPING_ENABLE, HEIGHT((_MESSAGE_HEIGHT_FONT_NUM + (_PANEL_DV_HEIGHT / 2 / ucFonHeight))), _OSD_MAP_B_REMAPPING_ENABLE, HEIGHT((_MESSAGE_HEIGHT_FONT_NUM + (_PANEL_DV_HEIGHT / 2 / ucFonHeight))), _OSD_FONT_LIB_ROTATION_ENABLE);
#endif
        }
        else
        {
            OsdFuncApplyMapOsdAB(WIDTH(_MESSAGE_WIDTH_FONT_NUM + (_PANEL_DV_HEIGHT / 2 / ucFonWidth)), HEIGHT(_MESSAGE_HEIGHT_FONT_NUM), COLOR(_CP_WHITE, _CP_BG), WIDTH(_MESSAGE_WIDTH_FONT_NUM + (_PANEL_DV_HEIGHT / 2 / ucFonWidth)), HEIGHT(_MESSAGE_HEIGHT_FONT_NUM), COLOR(_CP_WHITE, _CP_BG));
#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
            OsdFuncMapRotation(GET_OSD_ROTATE_STATUS(), _OSD_MAP_A_REMAPPING_ENABLE, HEIGHT(_MESSAGE_HEIGHT_FONT_NUM), _OSD_MAP_B_REMAPPING_ENABLE, HEIGHT(_MESSAGE_HEIGHT_FONT_NUM), _OSD_FONT_LIB_ROTATION_ENABLE);
#endif
        }

        OsdFuncBlending(_OSD_TRANSPARENCY_WINDOW_AND_CHARACTER_BACKGROUND);
        OsdFuncTransparency(GET_OSD_TRANSPARENCY_STATUS());

        // Adjust Color Palette
        OsdPaletteSelectPalette(_PALETTE_MAIN_MENU);

        // Load Font & Icon
        OsdFuncSet2BitIconOffset(_2BIT_ICON_OFFSET);

        OsdFontVLCLoadFont(_FONT1_GLOBAL);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_SUPPORT_ICON, _ICON_NO_SUPPORT);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_SUPPORT_TEXT_0, _ICON_NO_SUPPORT_TEXT_0);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_SUPPORT_TEXT_1, _ICON_NO_SUPPORT_TEXT_1);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_CABLE_ICON, _ICON_NO_CABLE);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_CABLE_TEXT_0, _ICON_NO_CABLE_TEXT_0);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_CABLE_TEXT_1, _ICON_NO_CABLE_TEXT_1);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_SIGNAL_ICON, _ICON_NO_SIGNAL);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_SIGNAL_TEXT_0, _ICON_NO_SIGNAL_TEXT_0);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_SIGNAL_TEXT_1, _ICON_NO_SIGNAL_TEXT_1);
    }
    if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_0)
    {
        OsdDispMpDisplayStateNotice(ROW(0), COL(0), ucNotice1P, _DISPLAY_RGN_LT, _PFONT_PAGE_0);
        OsdDispMpDisplayStateNotice(ROW(_PANEL_DV_HEIGHT / 2 / ucFonHeight), COL(0), ucNotice2P, _DISPLAY_RGN_LB, _PFONT_PAGE_2);

        OsdDispMpDisplayStateNoticeFontB(ROW(0), COL(0), ucNotice3P, _DISPLAY_RGN_RT, _PFONT_PAGE_1);
        OsdDispMpDisplayStateNoticeFontB(ROW(_PANEL_DV_HEIGHT / 2 / ucFonHeight), COL(0), ucNotice4P, _DISPLAY_RGN_RB, _PFONT_PAGE_3);
    }
    else if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_180)
    {
        ////////// OSD A
        OsdDispMpDisplayStateNotice(ROW(0), COL(0), ucNotice2P, _DISPLAY_RGN_LB, _PFONT_PAGE_0);
        OsdDispMpDisplayStateNotice(ROW(_PANEL_DV_HEIGHT / 2 / ucFonHeight), COL(0), ucNotice1P, _DISPLAY_RGN_LT, _PFONT_PAGE_2);

        ////////// OSD B
        OsdDispMpDisplayStateNoticeFontB(ROW(0), COL(0), ucNotice4P, _DISPLAY_RGN_RB, _PFONT_PAGE_1);
        OsdDispMpDisplayStateNoticeFontB(ROW(_PANEL_DV_HEIGHT / 2 / ucFonHeight), COL(0), ucNotice3P, _DISPLAY_RGN_RT, _PFONT_PAGE_3);
    }
    else if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90)
    {
        ////////// OSD A
        OsdDispMpDisplayStateNotice(ROW(0), COL(0), ucNotice3P, _DISPLAY_RGN_RT, _PFONT_PAGE_0);
        OsdDispMpDisplayStateNotice(ROW(0), COL(_PANEL_DV_HEIGHT / 2 / ucFonWidth), ucNotice4P, _DISPLAY_RGN_RB, _PFONT_PAGE_2);

        ////////// OSD B
        OsdDispMpDisplayStateNoticeFontB(ROW(0), COL(0), ucNotice1P, _DISPLAY_RGN_LT, _PFONT_PAGE_1);
        OsdDispMpDisplayStateNoticeFontB(ROW(0), COL(_PANEL_DV_HEIGHT / 2 / ucFonWidth), ucNotice2P, _DISPLAY_RGN_LB, _PFONT_PAGE_3);
    }
    else if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270)
    {
        ////////// OSD A
        OsdDispMpDisplayStateNotice(ROW(0), COL(0), ucNotice2P, _DISPLAY_RGN_LB, _PFONT_PAGE_0);
        OsdDispMpDisplayStateNotice(ROW(0), COL(_PANEL_DV_HEIGHT / 2 / ucFonWidth), ucNotice1P, _DISPLAY_RGN_LT, _PFONT_PAGE_2);

        ////////// OSD B
        OsdDispMpDisplayStateNoticeFontB(ROW(0), COL(0), ucNotice4P, _DISPLAY_RGN_RB, _PFONT_PAGE_1);
        OsdDispMpDisplayStateNoticeFontB(ROW(0), COL(_PANEL_DV_HEIGHT / 2 / ucFonWidth), ucNotice3P, _DISPLAY_RGN_RT, _PFONT_PAGE_3);
    }

    switch(GET_OSD_ROTATE_STATUS())
    {
        case _OSD_ROTATE_DEGREE_0:
            OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_A, ((_PANEL_DH_WIDTH / 4) - (_MESSAGE_WIDTH_MID_FONT_NUM * ucFonWidth)), ((_PANEL_DV_HEIGHT / 4) - (_MESSAGE_HEIGHT_MID_FONT_NUM * ucFonHeight)));
            OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_B, ((_PANEL_DH_WIDTH / 4 * 3) - (_MESSAGE_WIDTH_MID_FONT_NUM * ucFonWidth)), ((_PANEL_DV_HEIGHT / 4) - (_MESSAGE_HEIGHT_MID_FONT_NUM * ucFonHeight)));
            break;
        case _OSD_ROTATE_DEGREE_180:
            OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_A, ((_PANEL_DH_WIDTH / 4 * 3) - (_MESSAGE_WIDTH_MID_FONT_NUM * ucFonWidth)), ((_PANEL_DV_HEIGHT / 4) - (_MESSAGE_HEIGHT_MID_FONT_NUM * ucFonHeight)));
            OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_B, ((_PANEL_DH_WIDTH / 4) - (_MESSAGE_WIDTH_MID_FONT_NUM * ucFonWidth)), ((_PANEL_DV_HEIGHT / 4) - (_MESSAGE_HEIGHT_MID_FONT_NUM * ucFonHeight)));
            break;
        case _OSD_ROTATE_DEGREE_90:
            OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_A, ((_PANEL_DH_WIDTH / 4 * 3) - (_MESSAGE_HEIGHT_MID_FONT_NUM * ucFonHeight)), ((_PANEL_DV_HEIGHT / 4) - (_MESSAGE_WIDTH_MID_FONT_NUM * ucFonWidth)));
            OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_B, ((_PANEL_DH_WIDTH / 4) - (_MESSAGE_HEIGHT_MID_FONT_NUM * ucFonHeight)), ((_PANEL_DV_HEIGHT / 4) - (_MESSAGE_WIDTH_MID_FONT_NUM * ucFonWidth)));
            break;
        case _OSD_ROTATE_DEGREE_270:
            OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_A, ((_PANEL_DH_WIDTH / 4) - (_MESSAGE_HEIGHT_MID_FONT_NUM * ucFonHeight)), ((_PANEL_DV_HEIGHT / 4) - (_MESSAGE_WIDTH_MID_FONT_NUM * ucFonWidth)));
            OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_B, ((_PANEL_DH_WIDTH / 4 * 3) - (_MESSAGE_HEIGHT_MID_FONT_NUM * ucFonHeight)), ((_PANEL_DV_HEIGHT / 4) - (_MESSAGE_WIDTH_MID_FONT_NUM * ucFonWidth)));
            break;
        default:
            break;
    }

    OsdFuncEnableOsd();
}
#endif // End of #if(_4P_DISPLAY_SUPPORT == _ON)


//=====================================================================================================
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdDisp1stMenuIconString(BYTE ucIconPos, WORD usIcon, BYTE ucColor)
{
    BYTE ucFontPage = _PFONT_PAGE_0;
    WORD usIconLoad = 0;

    BYTE ucRow = ((ucIconPos / 4) ? ROW(14) : ROW(4));
    BYTE ucCol = COL(4) + ((ucIconPos % 4) * 10);

    if(usIcon == _ICON_NONE)
    {
        OsdFuncClearOsd(ucRow, (ucCol - 2), WIDTH(10), HEIGHT(5));
        return;
    }

    // icon
    if((usIcon >= _ICON_A0_PORT) && (usIcon <= _ICON_D6_PORT))
    {
        switch(usIcon)
        {
            case _ICON_A0_PORT:
                usIconLoad = _A0_INPUT_TYPE;
                break;
            case _ICON_D0_PORT:
                usIconLoad = _D0_INPUT_TYPE;
                break;
            case _ICON_D1_PORT:
                usIconLoad = _D1_INPUT_TYPE;
                break;
            case _ICON_D2_PORT:
                usIconLoad = _D2_INPUT_TYPE;
                break;
            case _ICON_D3_PORT:
                usIconLoad = _D3_INPUT_TYPE;
                break;
            case _ICON_D4_PORT:
                usIconLoad = _D4_INPUT_TYPE;
                break;
            case _ICON_D5_PORT:
                usIconLoad = _D5_INPUT_TYPE;
                break;
            case _ICON_D6_PORT:
                usIconLoad = _D6_INPUT_TYPE;
                break;
            default:
                break;
        }

        OsdFontVLCDynamicLoadIcon(ucIconPos, usIconLoad);
    }
    else
    {
        OsdFontVLCDynamicLoadIcon(ucIconPos, usIcon);
    }
    OsdFontPut1BitMainMenuIcon(ucRow, ucCol, (_1DYNAMIC_ICON_START + (ucIconPos * 24)), ucColor, _CP_BG);

    // string
    ucRow += 4;
    ucCol -= 2;
    OsdFuncClearOsd(ucRow, ucCol, WIDTH(10), HEIGHT(1));

    if((usIcon >= _ICON_A0_PORT) && (usIcon <= _ICON_D6_PORT))
    {
        OsdPropPutStringCenter(ucRow, ucCol, WIDTH(10), ucFontPage, (usIcon - _ICON_INPUT_END + _STRIN_END), COLOR(ucColor, _CP_BG), GET_OSD_LANGUAGE());
    }
    else if(usIcon < _OPTION_ICON_END)
    {
        OsdPropPutStringCenter(ucRow, ucCol, WIDTH(10), ucFontPage, usIcon - 1, COLOR(ucColor, _CP_BG), GET_OSD_LANGUAGE());
    }
}


//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdDisp1stMenu(void)
{
    // BYTE ucTest = 0;

    g_usFontPointer0 = _OSD_PAGE_0_START;
    g_usFontPointer1 = _OSD_PAGE_1_START;
    g_usFontPointer2 = _OSD_PAGE_2_START;

    OsdFuncDisableOsd();
    UserCommonOsdWindowDisable(_OSD_WINDOW_ALL);
    OsdFuncApplyMap(WIDTH(_OSD_MAIN_MENU_WIDTH), HEIGHT(_OSD_MAIN_MENU_HEIGHT), COLOR(_CP_WHITE, _CP_BG));
    UserCommonOsdMapABFunctionEnable(_OSD_A, _ENABLE);

#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
    OsdFuncMapRotation(GET_OSD_ROTATE_STATUS(), _OSD_MAP_A_REMAPPING_ENABLE, HEIGHT(_OSD_MAIN_MENU_HEIGHT), _OSD_MAP_B_REMAPPING_DISABLE, 0, _OSD_FONT_LIB_ROTATION_ENABLE);
#endif

    OsdFuncBlending(_OSD_TRANSPARENCY_ONLY_WINDOW);
    OsdFuncTransparency(GET_OSD_TRANSPARENCY_STATUS());

    // Adjust Color Palette
    OsdPaletteSelectPalette(_PALETTE_MAIN_MENU);

    // set 2bit Font offest
    OsdFuncSet2BitIconOffset(_2BIT_ICON_OFFSET);

    OsdFontVLCLoadFont(_FONT1_GLOBAL);

#if((_GOSD_SUPPORT == _ON) && ((_IS_MAIN_PROCESS_CPU == _TRUE) || (_CPU32_SCPU_FW_MODE == _SCPU_FW_MODE_ACTOR)))
    StructGosdLoadImageInfo stImageSourceInfo;
    StructGosdRectangle stWinRect = (StructGosdRectangle){{0, 0}, {_GOSD_IMAGE_SOURCE_MAINMENUBG_WIDTH, _GOSD_IMAGE_SOURCE_MAINMENUBG_HEIGHT}};
    StructGosdRectangle stDispRect = (StructGosdRectangle){{0, 0}, {_GOSD_IMAGE_SOURCE_MAINMENUBG_WIDTH, _GOSD_IMAGE_SOURCE_MAINMENUBG_HEIGHT}};

    UserCommonGosdReleaseMultiSurfaceSync(0, _GOSD_DEFAULT_POLLING_MS);

    UserCommonGosdCreateSurfaceSync(_GOSD_SURFACE_MAINMENUBG_ID, _GOSD_SURFACE_MAINMENUBG_FORMAT, _GOSD_SURFACE_MAINMENUBG_WIDTH, _GOSD_SURFACE_MAINMENUBG_HEIGHT, _GOSD_SURFACE_MAINMENUBG_ADDRESS, _GOSD_DEFAULT_POLLING_MS);
    stImageSourceInfo.usImageIndex = _GOSD_IMAGE_SOURCE_MAINMENUBG;
    stImageSourceInfo.usImageSourceStartFlashBank = _GOSD_IMAGE_SOURCE_FLASH_START_BANK;
    UserCommonGosdSetLoadImageInfoSync(_GOSD_SURFACE_MAINMENUBG_ID, &stImageSourceInfo, _GOSD_LOAD_POLLING, _GOSD_DEFAULT_POLLING_MS);

    // Calculate size of main_menu
    if(GET_OSD_DOUBLE_SIZE() == _ON)
    {
        stDispRect.stSize.usW *= 2;
        stDispRect.stSize.usH *= 2;
    }

    stDispRect.stPosition.usX = (_PANEL_DH_WIDTH - stDispRect.stSize.usW) / 2;
    stDispRect.stPosition.usY = (_PANEL_DV_HEIGHT - stDispRect.stSize.usH) / 2;

    DWORD ulRotationSurfaceOffset = 0;
    if(GET_OSD_ROTATE_STATUS() > _OSD_ROTATE_DEGREE_0)
    {
        ulRotationSurfaceOffset = 1;
        DWORD ulTempSurfaceId = _GOSD_SURFACE_MAINMENUBG_ID + ulRotationSurfaceOffset + 1;
        WORD usRotationSize = CEILING(MAXOF(stWinRect.stSize.usW, stWinRect.stSize.usH), 16);
        WORD usTemp = 0;
        StructGosdRectangle stSrcRect;
        StructGosdRectangle stFullRect;
        StructGosdPosition stOutPosition;

        stSrcRect.stPosition.usX = 0;
        stSrcRect.stPosition.usY = 0;
        stSrcRect.stSize.usW = stWinRect.stSize.usW;
        stSrcRect.stSize.usH = stWinRect.stSize.usH;
        stFullRect.stSize.usW = stWinRect.stSize.usW;
        stFullRect.stSize.usH = stWinRect.stSize.usH;

        switch(GET_OSD_ROTATE_STATUS())
        {
            default:
            case _OSD_ROTATE_DEGREE_0:
                break;
            case _OSD_ROTATE_DEGREE_90:
                usTemp = stWinRect.stSize.usW;
                stWinRect.stSize.usW = stWinRect.stSize.usH;
                stWinRect.stSize.usH = usTemp;
                stWinRect.stPosition.usX = usRotationSize - stWinRect.stSize.usW;
                stWinRect.stPosition.usY = 0;
                usTemp = stDispRect.stSize.usW;
                stDispRect.stSize.usW = stDispRect.stSize.usH;
                stDispRect.stSize.usH = usTemp;
                stDispRect.stPosition.usX = 0;
                stDispRect.stPosition.usY = 0;
                break;
            case _OSD_ROTATE_DEGREE_270:
                usTemp = stWinRect.stSize.usW;
                stWinRect.stSize.usW = stWinRect.stSize.usH;
                stWinRect.stSize.usH = usTemp;
                stWinRect.stPosition.usX = 0;
                stWinRect.stPosition.usY = usRotationSize - stWinRect.stSize.usH;
                usTemp = stDispRect.stSize.usW;
                stDispRect.stSize.usW = stDispRect.stSize.usH;
                stDispRect.stSize.usH = usTemp;
                stDispRect.stPosition.usX = 0;
                stDispRect.stPosition.usY = 0;
                break;
            case _OSD_ROTATE_DEGREE_180:
                stWinRect.stPosition.usX = usRotationSize - stWinRect.stSize.usW;
                stWinRect.stPosition.usY = usRotationSize - stWinRect.stSize.usH;
                break;
        }

        UserCommonGosdCreateSurfaceSync(ulTempSurfaceId, _GOSD_PIXEL_FORMAT_ARGB8888, usRotationSize, usRotationSize, _GOSD_AUTO_ADDRESS, _GOSD_DEFAULT_POLLING_MS);
        stSrcRect.stSize.usW = stFullRect.stSize.usW;
        stSrcRect.stSize.usH = stFullRect.stSize.usH;
        stSrcRect.stPosition.usX = 0;
        stSrcRect.stPosition.usY = 0;
        stOutPosition.usX = 0;
        stOutPosition.usY = 0;
        // copy to temp surface
        UserCommonGosdCopyPasteSync(_GOSD_SURFACE_MAINMENUBG_ID, ulTempSurfaceId, stSrcRect, stOutPosition, _GOSD_DEFAULT_POLLING_MS);
        // created rotation surface
        UserCommonGosdCreateSurfaceSync(_GOSD_SURFACE_MAINMENUBG_ID + ulRotationSurfaceOffset, _GOSD_PIXEL_FORMAT_ARGB8888, usRotationSize, usRotationSize, _GOSD_AUTO_ADDRESS, _GOSD_DEFAULT_POLLING_MS);
        // rotation
        stSrcRect.stSize.usW = usRotationSize;
        stSrcRect.stSize.usH = usRotationSize;
        stSrcRect.stPosition.usX = 0;
        stSrcRect.stPosition.usY = 0;
        stOutPosition.usX = 0;
        stOutPosition.usY = 0;
        UserCommonGosdRotateSync(ulTempSurfaceId, _GOSD_SURFACE_MAINMENUBG_ID + ulRotationSurfaceOffset, stSrcRect, stOutPosition, GET_OSD_ROTATE_STATUS(), _GOSD_DEFAULT_POLLING_MS);
        UserCommonGosdReleaseSurfaceSync(ulTempSurfaceId, _GOSD_DEFAULT_POLLING_MS);
    }

    UserCommonGosdDisplaySurfaceSync(_GOSD_PLANE_OSD1, _GOSD_SURFACE_MAINMENUBG_ID + ulRotationSurfaceOffset, &stWinRect, &stDispRect, _DB_APPLY_POLLING, _GOSD_DEFAULT_POLLING_MS);

    // set SubBlending mix as Fosd Over Gosd
    UserCommonOsdSubBlendingSetMixerFactor(0x3F, 0x04, 0x3F, 0x04);
    // set SubBlending mix Fosd and Gosd both
    UserCommonOsdSubBlendingSetFosdMixerEnable(_ENABLE);
    UserCommonOsdSubBlendingSetGosdMixerEnable(_ENABLE);
#else
    OsdFontVLCLoadFont(_REALTEK_4BIT_LOGO);
    // Realtek Mark
    OsdFontPut1BitTable(ROW(0), COL(32), tOSD_iREALTEK, COLOR(_CP_WHITE, _CP_BG));
#if 1 // Add 4bit logo
    OsdFontPut4Bit(ROW(0), COL(31), _4BIT_REALTEK_LOGO_ST, 0x00);
    OsdFontPut4Bit(ROW(0), COL(32), _4BIT_REALTEK_LOGO_ST + 1, 0x00);
    OsdFontPut4Bit(ROW(0), COL(33), _4BIT_REALTEK_LOGO_ST + 2, 0x00);
    OsdFontPut4Bit(ROW(0), COL(34), _4BIT_REALTEK_LOGO_ST + 3, 0x00);
    OsdFontPut4Bit(ROW(1), COL(31), _4BIT_REALTEK_LOGO_ST + 4, 0x00);
    OsdFontPut4Bit(ROW(1), COL(32), _4BIT_REALTEK_LOGO_ST + 5, 0x00);
    OsdFontPut4Bit(ROW(1), COL(33), _4BIT_REALTEK_LOGO_ST + 6, 0x00);
    OsdFontPut4Bit(ROW(1), COL(34), _4BIT_REALTEK_LOGO_ST + 7, 0x00);
#endif

    // Set Gradient Window
    SET_OSD_WINDOW_GRANIENT_INDEX(_OSD_WIN_GRADIENT_0);
    SET_OSD_WINDOW_GRANIENT_WIN(_OSD_WINDOW_0);
    SET_OSD_WINDOW_GRADIENT_ENABLE_B(_ENABLE);
    SET_OSD_WINDOW_GRADIENT_DIRECTION(_OSD_WINDOW_GRADIENT_DIRECTION_VERTICAL);
    SET_OSD_WINDOW_GRADIENT_POLARITY_B(_OSD_WINDOW_GRADIENT_POLARITY_DECREASE);
    SET_OSD_WINDOW_GRADIENT_LEVEL_COLOR_R(_OSD_WINDOW_GRADIENT_LEVEL_PER_1);
    SET_OSD_WINDOW_GRADIENT_LEVEL_COLOR_G(_OSD_WINDOW_GRADIENT_LEVEL_PER_1);
    SET_OSD_WINDOW_GRADIENT_LEVEL_COLOR_B(_OSD_WINDOW_GRADIENT_LEVEL_PER_1);
    SET_OSD_WINDOW_GRADIENT_LEVEL_SETP(_OSD_WINDOW_GRADIENT_LEVEL_STEP_3);
    SET_OSD_WINDOW_GRADIENT_COLOR(_CP_BLUE_200);
    UserCommonOsdDrawWindowGradient(ROW(0) + 1, COL(0) + 1, WIDTH(g_ucOsdWidth) * 12 - 1, HEIGHT(g_ucOsdHeight) * 18 - 1); // -1 : border size = 1

    SET_OSD_WINDOW_BUTTON_TYPE(_OSD_WINDOW_BUTTON_TYPE_BORDER);
    SET_OSD_WINDOW_COLOR_BORDER(_CP_WHITE);
    SET_OSD_WINDOW_BORDER_PIXEL_WIDTH(1);
    SET_OSD_WINDOW_BORDER_PIXEL_HEIGHT(1);
    OsdWindowDrawingByFont(_OSD_WINDOW_0, ROW(0), COL(0), WIDTH(g_ucOsdWidth), HEIGHT(g_ucOsdHeight), _CP_BLUE_200);
#endif
    // Main Menu Icon & String
    SET_OSD_ITEM_INDEX(0);
    OsdDisp1stMenuIcon();
    SET_OSD_STATE(_MENU_MAIN);
    OsdDisp1stMenuCursor(GET_OSD_ITEM_INDEX());
    // key info
    OsdDispMainMenuKeyInfo(_KEY_INFO_ALL, _OSD_UNSELECT);

    OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, GET_OSD_HPOS(), GET_OSD_VPOS());

    // Osd Enable
    OsdFuncEnableOsd();
}
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
BYTE OsdDisp1stMenuGetIdx(EnumOsdItem enumOsdItem)
{
    BYTE ucI = 0;

    for(ucI = 0; ucI < _OSD_MAIN_ITEM_AMOUNT; ucI++)
    {
        if(enumOsdItem == tOSD_MAIN_ITEM_PRI[ucI])
        {
            return ucI;
        }
    }

    return 0;
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdDisp1stMenuRedraw(void)
{
    UserCommonOsdWindowDisable(_OSD_WIN_HIGHLIGHT_2);
    UserCommonOsdWindowDisable(_OSD_WINDOW_1);

    // clear all
    OsdFuncClearOsd(4, 4, WIDTH((g_ucOsdWidth - 6)), HEIGHT(g_ucOsdHeight - 7));
    OsdWindowGridLine(_OFF);////By Jerry -2017-12-11//replace GridLine function

    SET_OSD_WINDOW_GRADIENT_DIRECTION(_OSD_WINDOW_GRADIENT_DIRECTION_VERTICAL);
    SET_OSD_WINDOW_GRADIENT_POLARITY_B(_OSD_WINDOW_GRADIENT_POLARITY_DECREASE);
    SET_OSD_WINDOW_GRADIENT_LEVEL_SETP(_OSD_WINDOW_GRADIENT_LEVEL_STEP_3);

#if(_GOSD_SUPPORT == _OFF)
    // Set Gradient Window
    SET_OSD_WINDOW_GRADIENT_ENABLE_B(_ENABLE);
    SET_OSD_WINDOW_GRANIENT_INDEX(_OSD_WIN_GRADIENT_0);
    SET_OSD_WINDOW_GRANIENT_WIN(_OSD_WINDOW_0);
    SET_OSD_WINDOW_GRADIENT_LEVEL_COLOR_R(_OSD_WINDOW_GRADIENT_LEVEL_PER_1);
    SET_OSD_WINDOW_GRADIENT_LEVEL_COLOR_G(_OSD_WINDOW_GRADIENT_LEVEL_PER_1);
    SET_OSD_WINDOW_GRADIENT_LEVEL_COLOR_B(_OSD_WINDOW_GRADIENT_LEVEL_PER_1);
    SET_OSD_WINDOW_GRADIENT_COLOR(_CP_BLUE_200);
    UserCommonOsdDrawWindowGradient(ROW(0), COL(0), WIDTH(g_ucOsdWidth) * 12, HEIGHT(g_ucOsdHeight) * 18);

    // Background window
    SET_OSD_WINDOW_BUTTON_TYPE(_OSD_WINDOW_BUTTON_TYPE_BORDER);
    SET_OSD_WINDOW_COLOR_BORDER(_CP_WHITE);
    OsdWindowDrawingByFont(_OSD_WINDOW_0, ROW(0), COL(0), WIDTH(g_ucOsdWidth), HEIGHT(g_ucOsdHeight), _CP_BLUE_200);
#endif
    // Main Menu Icon & String
    OsdDisp1stMenuIcon();
    OsdDisp1stMenuCursor(GET_OSD_ITEM_INDEX());
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdDisp1stMenuIcon(void)
{
    BYTE ucI = 0;
    BYTE ucMaxItem = _OSD_MAIN_ITEM_AMOUNT;

    if(GET_OSD_ITEM_INDEX() >= _OSD_MAIN_ITEM_AMOUNT)
    {
        SET_OSD_ITEM_INDEX(0);
    }

    if(_OSD_MAIN_ITEM_AMOUNT > _MENU_1ST_ITEM_MAX)
    {
        if(GET_OSD_ITEM_INDEX() >= _MENU_1ST_ITEM_MAX)
        {
            if((WORD)_OSD_MAIN_ITEM_AMOUNT >= ((WORD)((GET_OSD_ITEM_INDEX() / _MENU_1ST_ITEM_MAX) + 1) * _MENU_1ST_ITEM_MAX))
            {
                ucMaxItem = (((GET_OSD_ITEM_INDEX() / _MENU_1ST_ITEM_MAX) + 1) * _MENU_1ST_ITEM_MAX);
            }
        }
        else
        {
            ucMaxItem = _MENU_1ST_ITEM_MAX;
        }
    }

    for(ucI = ((GET_OSD_ITEM_INDEX() / _MENU_1ST_ITEM_MAX) * _MENU_1ST_ITEM_MAX); ucI < ucMaxItem; ucI++)
    {
        switch(tOSD_MAIN_ITEM_PRI[ucI])
        {
            default:
            case _OSD_MENU_PICTURE:
                OsdDisp1stMenuIconString((ucI % _MENU_1ST_ITEM_MAX), _ICON_PICTURE, _CP_LIGHTBLUE);
                break;

            case _OSD_MENU_DISPLAY:
                OsdDisp1stMenuIconString((ucI % _MENU_1ST_ITEM_MAX), _ICON_DISPLAYFUNCTION, _CP_LIGHTBLUE);
                break;

            case _OSD_MENU_COLOR:
                OsdDisp1stMenuIconString((ucI % _MENU_1ST_ITEM_MAX), _ICON_COLOR, _CP_LIGHTBLUE);
                break;

            case _OSD_MENU_ADVANCE:
                OsdDisp1stMenuIconString((ucI % _MENU_1ST_ITEM_MAX), _ICON_ADVANCE, _CP_LIGHTBLUE);
                break;

            case _OSD_MENU_AUDIO:
                OsdDisp1stMenuIconString((ucI % _MENU_1ST_ITEM_MAX), _ICON_AUDIO, _CP_LIGHTBLUE);
                break;

            case _OSD_MENU_OTHER:
                OsdDisp1stMenuIconString((ucI % _MENU_1ST_ITEM_MAX), _ICON_OTHER, _CP_LIGHTBLUE);
                break;

            case _OSD_MENU_MUTIP:
                OsdDisp1stMenuIconString((ucI % _MENU_1ST_ITEM_MAX), _ICON_MUTIP, _CP_LIGHTBLUE);
                break;

            case _OSD_MENU_HDR:
                OsdDisp1stMenuIconString((ucI % _MENU_1ST_ITEM_MAX), _ICON_HDR, _CP_LIGHTBLUE);
                break;

            case _OSD_MENU_QUICKLINK:
                OsdDisp1stMenuIconString((ucI % _MENU_1ST_ITEM_MAX), _ICON_QUICKLINK, _CP_LIGHTBLUE);
                break;

            case _OSD_MENU_INPUT:
                OsdDisp1stMenuIconString((ucI % _MENU_1ST_ITEM_MAX), _ICON_INPUT, _CP_LIGHTBLUE);
                break;

            case _OSD_MENU_FACTORY:
                OsdDisp1stMenuIconString((ucI % _MENU_1ST_ITEM_MAX), _ICON_FACTORY, _CP_LIGHTBLUE);
                break;
#if(_DM_FUNCTION == _ON)
            case _OSD_MENU_DVISION:
                OsdDisp1stMenuIconString((ucI % _MENU_1ST_ITEM_MAX), _ICON_DVISION, _CP_LIGHTBLUE);
                break;
#endif
#if(_AUDIO_ARC_SUPPORT == _ON)
            case _OSD_MENU_AUDIO_ARC_EARC:
                OsdDisp1stMenuIconString((ucI % _MENU_1ST_ITEM_MAX), _ICON_EARC, _CP_LIGHTBLUE);
                break;
#endif
        }
    }

    // Clear Icon
    if((ucMaxItem % _MENU_1ST_ITEM_MAX) != 0)
    {
        for(ucI = (ucMaxItem % _MENU_1ST_ITEM_MAX); ucI < _MENU_1ST_ITEM_MAX; ucI++)
        {
            OsdDisp1stMenuIconString((ucI), _ICON_NONE, _CP_LIGHTBLUE);
        }
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdDisp1stMenuSelectbyKey(void)
{
    BYTE ucBackup = GET_OSD_ITEM_INDEX();

    if(GET_OSD_ITEM_INDEX() >= _OSD_MAIN_ITEM_AMOUNT)
    {
        SET_OSD_ITEM_INDEX(0);
        return;
    }

    if(GET_KEYMESSAGE() == _RIGHT_KEY_MESSAGE)
    {
        SET_OSD_ITEM_INDEX((GET_OSD_ITEM_INDEX() + 1) % _OSD_MAIN_ITEM_AMOUNT);
        if((GET_OSD_ITEM_INDEX() % _MENU_1ST_ITEM_MAX) == 0)
        {
            UserCommonOsdWindowDisable(_OSD_WIN_HIGHLIGHT_1);
            OsdDisp1stMenuIcon();
        }
    }
    else if(GET_KEYMESSAGE() == _LEFT_KEY_MESSAGE)
    {
        SET_OSD_ITEM_INDEX((GET_OSD_ITEM_INDEX() + _OSD_MAIN_ITEM_AMOUNT - 1) % _OSD_MAIN_ITEM_AMOUNT);

        if((ucBackup == 0) || (ucBackup == _MENU_1ST_ITEM_MAX))
        {
            UserCommonOsdWindowDisable(_OSD_WIN_HIGHLIGHT_1);
            OsdDisp1stMenuIcon();
        }
    }
}

//--------------------------------------------------
// Description  : Check initial Picture Item
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdDisp1stMenuEnterCheck(void)
{
    BYTE ucBackupIdx = GET_OSD_ITEM_INDEX();
    WORD usOsdStateSwitch = tOSD_MAIN_ITEM_PRI[GET_OSD_ITEM_INDEX()];

    SET_OSD_ITEM_INDEX(0); // from 0 to check

    switch(usOsdStateSwitch)
    {
        case _OSD_MENU_PICTURE:
#if(_DM_FUNCTION == _ON)
#if(_IS_MAIN_PROCESS_CPU == _TRUE)
            if(UserCommonColorDMGetDMStatus(GET_OSD_SYSTEM_DISPLAY_REGION()) == _ON)
            {
                SET_OSD_ITEM_INDEX(ucBackupIdx);
                break;
            }
#endif
#endif
            do
            {
                if(OsdDisp2ndMenuCheck(tOSD_PICTURE_ITEM_PRI[GET_OSD_ITEM_INDEX()]) == _TRUE)
                {
                    break;
                }
                SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() + 1);
            }
            while(GET_OSD_ITEM_INDEX() < _OSD_PICTURE_ITEM_AMOUNT);

            if((GET_OSD_ITEM_INDEX() < _OSD_PICTURE_ITEM_AMOUNT))
            {
                OsdDisp2ndMenuReDraw(_MENU_PICTURE_ITEM, _HIGH);
            }
            else
            {
                // No Item can be selected
                SET_OSD_ITEM_INDEX(ucBackupIdx);
            }

            break;

        case _OSD_MENU_DISPLAY:
            do
            {
                if(OsdDisp2ndMenuCheck(tOSD_DISPLAY_ITEM_PRI[GET_OSD_ITEM_INDEX()]) == _TRUE)
                {
                    break;
                }
                SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() + 1);
            }
            while(GET_OSD_ITEM_INDEX() < _OSD_DISPLAY_ITEM_AMOUNT);

            if(GET_OSD_ITEM_INDEX() < _OSD_DISPLAY_ITEM_AMOUNT)
            {
                OsdDisp2ndMenuReDraw(_MENU_DISPLAY_ITEM, _HIGH);
            }
            else
            {
                // No Item can be selected
                SET_OSD_ITEM_INDEX(ucBackupIdx);
            }

            break;

        case _OSD_MENU_COLOR:
#if(_DM_FUNCTION == _ON)
#if(_IS_MAIN_PROCESS_CPU == _TRUE)
            if(UserCommonColorDMGetDMStatus(GET_OSD_SYSTEM_DISPLAY_REGION()) == _ON)
            {
                SET_OSD_ITEM_INDEX(ucBackupIdx);
                break;
            }
#endif
#endif
            do
            {
                if(OsdDisp2ndMenuCheck(tOSD_COLOR_ITEM_PRI[GET_OSD_ITEM_INDEX()]) == _TRUE)
                {
                    break;
                }
                SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() + 1);
            }
            while(GET_OSD_ITEM_INDEX() < _OSD_COLOR_ITEM_AMOUNT);

            if((GET_OSD_ITEM_INDEX() < _OSD_COLOR_ITEM_AMOUNT))
            {
                OsdDisp2ndMenuReDraw(_MENU_COLOR_ITEM, _HIGH);
            }
            else
            {
                // No Item can be selected
                SET_OSD_ITEM_INDEX(ucBackupIdx);
            }

            break;

        case _OSD_MENU_ADVANCE:
            do
            {
                if(OsdDisp2ndMenuCheck(tOSD_ADVANCE_ITEM_PRI[GET_OSD_ITEM_INDEX()]) == _TRUE)
                {
                    break;
                }
                SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() + 1);
            }
            while(GET_OSD_ITEM_INDEX() < _OSD_ADVANCE_ITEM_AMOUNT);

            if(GET_OSD_ITEM_INDEX() < _OSD_ADVANCE_ITEM_AMOUNT)
            {
                OsdDisp2ndMenuReDraw(_MENU_ADVANCE_ITEM, _HIGH);
            }
            else
            {
                // No Item can be selected
                SET_OSD_ITEM_INDEX(ucBackupIdx);
            }

            break;

        case _OSD_MENU_AUDIO:
            do
            {
                if(OsdDisp2ndMenuCheck(tOSD_AUDIO_ITEM_PRI[GET_OSD_ITEM_INDEX()]) == _TRUE)
                {
                    break;
                }
                SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() + 1);
            }
            while(GET_OSD_ITEM_INDEX() < _OSD_AUDIO_ITEM_AMOUNT);

            if(GET_OSD_ITEM_INDEX() < _OSD_AUDIO_ITEM_AMOUNT)
            {
                OsdDisp2ndMenuReDraw(_MENU_AUDIO_ITEM, _HIGH);
            }
            else
            {
                // No Item can be selected
                SET_OSD_ITEM_INDEX(ucBackupIdx);
            }

            break;

        case _OSD_MENU_OTHER:
            do
            {
                if(OsdDisp2ndMenuCheck(tOSD_OTHER_ITEM_PRI[GET_OSD_ITEM_INDEX()]) == _TRUE)
                {
                    break;
                }
                SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() + 1);
            }
            while(GET_OSD_ITEM_INDEX() < _OSD_OTHER_ITEM_AMOUNT);

            if(GET_OSD_ITEM_INDEX() < _OSD_OTHER_ITEM_AMOUNT)
            {
                OsdDisp2ndMenuReDraw(_MENU_OTHER_ITEM, _HIGH);
            }
            else
            {
                // No Item can be selected
                SET_OSD_ITEM_INDEX(ucBackupIdx);
            }

            break;

        case _OSD_MENU_MUTIP:
            do
            {
                if(OsdDisp2ndMenuCheck(tOSD_MUTIP_ITEM_PRI[GET_OSD_ITEM_INDEX()]) == _TRUE)
                {
                    break;
                }
                SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() + 1);
            }
            while(GET_OSD_ITEM_INDEX() < _OSD_MUTIP_ITEM_AMOUNT);

            if(GET_OSD_ITEM_INDEX() < _OSD_MUTIP_ITEM_AMOUNT)
            {
                OsdDisp2ndMenuReDraw(_MENU_MUTIP_ITEM, _HIGH);
            }
            else
            {
                // No Item can be selected
                SET_OSD_ITEM_INDEX(ucBackupIdx);
            }

            break;
        case _OSD_MENU_HDR:
#if(_DM_FUNCTION == _ON)
#if(_IS_MAIN_PROCESS_CPU == _TRUE)
            if(UserCommonColorDMGetDMStatus(GET_OSD_SYSTEM_DISPLAY_REGION()) == _ON)
            {
                SET_OSD_ITEM_INDEX(ucBackupIdx);
                break;
            }
#endif
#endif
            do
            {
                if(OsdDisp2ndMenuCheck(tOSD_HDR_ITEM_PRI[GET_OSD_ITEM_INDEX()]) == _TRUE)
                {
                    break;
                }
                SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() + 1);
            }
            while(GET_OSD_ITEM_INDEX() < _OSD_HDR_ITEM_AMOUNT);

            if(GET_OSD_ITEM_INDEX() < _OSD_HDR_ITEM_AMOUNT)
            {
                OsdDisp2ndMenuReDraw(_MENU_HDR_ITEM, _HIGH);
            }
            else
            {
                // No Item can be selected
                SET_OSD_ITEM_INDEX(ucBackupIdx);
            }
            break;
        case _OSD_MENU_QUICKLINK:
            do
            {
                if(OsdDisp2ndMenuCheck(tOSD_QUICK_ITEM_PRI[GET_OSD_ITEM_INDEX()]) == _TRUE)
                {
                    break;
                }
                SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() + 1);
            }
            while(GET_OSD_ITEM_INDEX() < _OSD_QUICK_ITEM_AMOUNT);

            if(GET_OSD_ITEM_INDEX() < _OSD_QUICK_ITEM_AMOUNT)
            {
                OsdDisp2ndMenuReDraw(_MENU_QUICKLINK_ITEM, _HIGH);
            }
            else
            {
                // No Item can be selected
                SET_OSD_ITEM_INDEX(ucBackupIdx);
            }

            break;
        case _OSD_MENU_INPUT:
            do
            {
                if(OsdDisp2ndMenuCheck(tOSD_INPUT_ITEM_PRI[GET_OSD_ITEM_INDEX()]) == _TRUE)
                {
                    break;
                }
                SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() + 1);
            }
            while(GET_OSD_ITEM_INDEX() < _OSD_INPUT_ITEM_AMOUNT);

            if(GET_OSD_ITEM_INDEX() < _OSD_INPUT_ITEM_AMOUNT)
            {
                OsdDisp2ndMenuReDraw(_MENU_INPUT_ITEM, _HIGH);
            }
            else
            {
                // No Item can be selected
                SET_OSD_ITEM_INDEX(ucBackupIdx);
            }

            break;

        case _OSD_MENU_FACTORY:
            RTDFactoryMainMenu();
            break;

#if(_DM_FUNCTION == _ON)
        case _OSD_MENU_DVISION:
            if(GET_OSD_HDR_MODE(SysRegionGetInputPort(GET_OSD_SYSTEM_DISPLAY_REGION())) == _HDR10_MODE_OFF)
            {
                SET_OSD_ITEM_INDEX(ucBackupIdx);
                break;
            }
            do
            {
                if(OsdDisp2ndMenuCheck(tOSD_DVISION_ITEM_PRI[GET_OSD_ITEM_INDEX()]) == _TRUE)
                {
                    break;
                }
                SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() + 1);
            }
            while(GET_OSD_ITEM_INDEX() < _OSD_DVISION_ITEM_AMOUNT);

            if(GET_OSD_ITEM_INDEX() < _OSD_DVISION_ITEM_AMOUNT)
            {
                OsdDisp2ndMenuReDraw(_MENU_DVISION_ITEM, _HIGH);
            }
            else
            {
                // No Item can be selected
                SET_OSD_ITEM_INDEX(ucBackupIdx);
            }

            break;
#endif

#if(_AUDIO_ARC_SUPPORT == _ON)
        case _OSD_MENU_AUDIO_ARC_EARC:
            do
            {
                if(OsdDisp2ndMenuCheck(tOSD_AUDIO_ARC_ITEM_PRI[GET_OSD_ITEM_INDEX()]) == _TRUE)
                {
                    break;
                }
                SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() + 1);
            }
            while(GET_OSD_ITEM_INDEX() < _OSD_AUDIO_ARC_ITEM_AMOUNT);

            if(GET_OSD_ITEM_INDEX() < _OSD_AUDIO_ARC_ITEM_AMOUNT)
            {
                OsdDisp2ndMenuReDraw(_MENU_AUDIO_ARC_EARC_ITEM, _HIGH);
            }
            else
            {
                // No Item can be selected
                SET_OSD_ITEM_INDEX(ucBackupIdx);
            }

            break;
#endif
        default:
            break;
    }
}
//--------------------------------------------------
// Description  :Picture sub Item switcht
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdDispItemValueUpdate(EnumOsdItem enumOsdItem)
{
    switch(enumOsdItem)
    {
        default:
            break;

        case _OSD_MUTIP_MODE:
            g_stOsdItemData.usStringIdx = _STRING_DISPLAYMODE;
            g_stOsdItemData.usAdjValue = GET_OSD_DISPLAY_MODE();
            g_stOsdItemData.usAdjValueMin = _OSD_DM_1P;
            g_stOsdItemData.usAdjValueMax = _OSD_DM_4P;
            g_stOsdItemData.usSubStringIdx = _STRING_1P;
            g_stOsdItemData.usSubOsdState = _MENU_DISPLAYMODE;
            g_stOsdItemData.b3ShowType = _ADJ_LIST;
            break;

        case _OSD_MUTIP_SELECTREGION:
            g_stOsdItemData.usStringIdx = _STRING_SELECTREGION;
            if(GET_OSD_DISPLAY_MODE() == _OSD_DM_2P_LR)
            {
                g_stOsdItemData.usAdjValue = GET_OSD_SELECT_REGION();
                g_stOsdItemData.usAdjValueMin = _OSD_SR_2P_LR_L;
                g_stOsdItemData.usAdjValueMax = _OSD_SR_2P_LR_FULL;
                g_stOsdItemData.usSubStringIdx = _STRING_2P_LR_L;
                g_stOsdItemData.usSubOsdState = _MENU_SELECTREGIOM;
                g_stOsdItemData.b3ShowType = _ADJ_LIST;
            }
            else if(GET_OSD_DISPLAY_MODE() == _OSD_DM_2P_TB)
            {
                g_stOsdItemData.usAdjValue = GET_OSD_SELECT_REGION();
                g_stOsdItemData.usAdjValueMin = _OSD_SR_2P_TB_T;
                g_stOsdItemData.usAdjValueMax = _OSD_SR_2P_TB_FULL;
                g_stOsdItemData.usSubStringIdx = _STRING_2P_TB_T;
                g_stOsdItemData.usSubOsdState = _MENU_SELECTREGIOM;
                g_stOsdItemData.b3ShowType = _ADJ_LIST;
            }
            else if(GET_OSD_DISPLAY_MODE() == _OSD_DM_2P_PIP)
            {
                g_stOsdItemData.usAdjValue = GET_OSD_SELECT_REGION();
                g_stOsdItemData.usAdjValueMin = _OSD_SR_2P_PIP_MAIN;
                g_stOsdItemData.usAdjValueMax = _OSD_SR_2P_PIP_FULL;
                g_stOsdItemData.usSubStringIdx = _STRING_2P_PIP_MAIN;
                g_stOsdItemData.usSubOsdState = _MENU_SELECTREGIOM;
                g_stOsdItemData.b3ShowType = _ADJ_LIST;
            }
            else if(GET_OSD_DISPLAY_MODE() == _OSD_DM_3P_FLAG)
            {
                g_stOsdItemData.usAdjValue = GET_OSD_SELECT_REGION();
                g_stOsdItemData.usAdjValueMin = _OSD_SR_3P_FLAG_MAIN;
                g_stOsdItemData.usAdjValueMax = _OSD_SR_3P_FLAG_FULL;
                g_stOsdItemData.usSubStringIdx = _STRING_3P_FLAG_MAIN;
                g_stOsdItemData.usSubOsdState = _MENU_SELECTREGIOM;
                g_stOsdItemData.b3ShowType = _ADJ_LIST;
            }
            else if(GET_OSD_DISPLAY_MODE() == _OSD_DM_3P_SKEW_L)
            {
                g_stOsdItemData.usAdjValue = GET_OSD_SELECT_REGION();
                g_stOsdItemData.usAdjValueMin = _OSD_SR_3P_SKEW_L_MAIN;
                g_stOsdItemData.usAdjValueMax = _OSD_SR_3P_SKEW_L_FULL;
                g_stOsdItemData.usSubStringIdx = _STRING_3P_SKEW_MAIN;
                g_stOsdItemData.usSubOsdState = _MENU_SELECTREGIOM;
                g_stOsdItemData.b3ShowType = _ADJ_LIST;
            }
            else if(GET_OSD_DISPLAY_MODE() == _OSD_DM_3P_SKEW_R)
            {
                g_stOsdItemData.usAdjValue = GET_OSD_SELECT_REGION();
                g_stOsdItemData.usAdjValueMin = _OSD_SR_3P_SKEW_R_MAIN;
                g_stOsdItemData.usAdjValueMax = _OSD_SR_3P_SKEW_R_FULL;
                g_stOsdItemData.usSubStringIdx = _STRING_3P_SKEW_MAIN;
                g_stOsdItemData.usSubOsdState = _MENU_SELECTREGIOM;
                g_stOsdItemData.b3ShowType = _ADJ_LIST;
            }
            else if(GET_OSD_DISPLAY_MODE() == _OSD_DM_3P_SKEW_T)
            {
                g_stOsdItemData.usAdjValue = GET_OSD_SELECT_REGION();
                g_stOsdItemData.usAdjValueMin = _OSD_SR_3P_SKEW_T_MAIN;
                g_stOsdItemData.usAdjValueMax = _OSD_SR_3P_SKEW_T_FULL;
                g_stOsdItemData.usSubStringIdx = _STRING_3P_SKEW_MAIN;
                g_stOsdItemData.usSubOsdState = _MENU_SELECTREGIOM;
                g_stOsdItemData.b3ShowType = _ADJ_LIST;
            }
            else if(GET_OSD_DISPLAY_MODE() == _OSD_DM_3P_SKEW_B)
            {
                g_stOsdItemData.usAdjValue = GET_OSD_SELECT_REGION();
                g_stOsdItemData.usAdjValueMin = _OSD_SR_3P_SKEW_B_MAIN;
                g_stOsdItemData.usAdjValueMax = _OSD_SR_3P_SKEW_B_FULL;
                g_stOsdItemData.usSubStringIdx = _STRING_3P_SKEW_MAIN;
                g_stOsdItemData.usSubOsdState = _MENU_SELECTREGIOM;
                g_stOsdItemData.b3ShowType = _ADJ_LIST;
            }
            else if(GET_OSD_DISPLAY_MODE() == _OSD_DM_4P)
            {
                g_stOsdItemData.usAdjValue = GET_OSD_SELECT_REGION();
                g_stOsdItemData.usAdjValueMin = _OSD_SR_4P_LT_INSIDE;
                g_stOsdItemData.usAdjValueMax = _OSD_SR_4P_FULL;
                g_stOsdItemData.usSubStringIdx = _STRING_4P_LT_IN;
                g_stOsdItemData.usSubOsdState = _MENU_SELECTREGIOM;
                g_stOsdItemData.b3ShowType = _ADJ_LIST;
            }
            else
            {
                // only 1 region
                g_stOsdItemData.usAdjValue = _OSD_SR_1P_FULL;
                g_stOsdItemData.usAdjValueMin = _OSD_SR_1P_FULL;
                g_stOsdItemData.usAdjValueMax = _OSD_SR_1P_FULL;
                g_stOsdItemData.usSubStringIdx = _STRING_1P;
                g_stOsdItemData.usSubOsdState = _MENU_SELECTREGIOM;
                g_stOsdItemData.b3ShowType = _ADJ_LIST;
            }
            break;

        case _OSD_MUTIP_LR_RATIO:
            g_stOsdItemData.usStringIdx = _STRING_DISP_LR_RATIO;
            g_stOsdItemData.usSubStringIdx = _STRIN_END;
            g_stOsdItemData.usSubOsdState = _MENU_DISPLAYFUN_LR_RATIO_ADJUST;
            g_stOsdItemData.b3ShowType = _ADJ_BAR_REAL;
            if(GET_OSD_DISPLAY_MODE() == _OSD_DM_2P_LR)
            {
                g_stOsdItemData.usAdjValue = GET_OSD_PBP_LR_RATIO();
                g_stOsdItemData.usAdjValueMin = _OSD_PBP_LR_RATIO_MIN;
                g_stOsdItemData.usAdjValueMax = _OSD_PBP_LR_RATIO_MAX;
                g_stOsdItemData.usAdjValueCenter = _OSD_PBP_LR_RATIO_CENTER;
            }
            else if(GET_OSD_DISPLAY_MODE() == _OSD_DM_3P_FLAG)
            {
                // (GET_OSD_DISPLAY_MODE() == _OSD_DM_3P_FLAG)
                g_stOsdItemData.usAdjValue = GET_OSD_3P_FLAG_RATIO();
                g_stOsdItemData.usAdjValueMin = _OSD_3P_FLAG_RATIO_MIN;
                g_stOsdItemData.usAdjValueMax = _OSD_3P_FLAG_RATIO_MAX;
                g_stOsdItemData.usAdjValueCenter = _OSD_3P_FLAG_RATIO_CENTER;
            }
            else
            {
                // (GET_OSD_DISPLAY_MODE() == _OSD_DM_3P_SKEWLR)
                g_stOsdItemData.usAdjValue = GET_OSD_3P_SKEW_LR_RATIO();
                g_stOsdItemData.usAdjValueMin = _OSD_3P_SKEW_LR_RATIO_MIN;
                g_stOsdItemData.usAdjValueMax = _OSD_3P_SKEW_LR_RATIO_MAX;
                g_stOsdItemData.usAdjValueCenter = _OSD_3P_SKEW_LR_RATIO_CENTER;
            }
            break;

        case _OSD_MUTIP_PIP_POSITION:
            g_stOsdItemData.usStringIdx = _STRING_PIP_POSITION;
            g_stOsdItemData.usAdjValue = GET_OSD_PIP_POSITION_TYPE();
            g_stOsdItemData.usAdjValueMin = _PIP_POSITON_LT;
            g_stOsdItemData.usAdjValueMax = _PIP_POSITON_USER;
            g_stOsdItemData.usSubStringIdx = _STRING_POSITION_LT;
            g_stOsdItemData.usSubOsdState = _MENU_DISPLAYFUN_PIP_POSITION_ADJUST;
            g_stOsdItemData.b3ShowType = _ADJ_LIST;
            break;

        case _OSD_MUTIP_PIP_POSITION_USER:
            g_stOsdItemData.usStringIdx = _STRING_PIP_POSITION_USER;
            g_stOsdItemData.usAdjValue = 0;
            g_stOsdItemData.usAdjValueMin = 0;
            g_stOsdItemData.usAdjValueMax = 1;
            g_stOsdItemData.usSubStringIdx = _STRING_PIP_USER_POSITION_H;
            g_stOsdItemData.usSubOsdState = _MENU_DISPLAYFUN_PIP_POSITION_USER;
            g_stOsdItemData.b3ShowType = _ADJ_LIST;
            break;

        case _OSD_MUTIP_PIP_TRANSPARENCY:
            g_stOsdItemData.usStringIdx = _STRING_PIP_TRANSPARENCY;
            g_stOsdItemData.usAdjValue = GET_OSD_PIP_TRANSPARENCY();
            g_stOsdItemData.usAdjValueMin = _OSD_PIP_TRANSPARENCY_MIN;
            g_stOsdItemData.usAdjValueMax = _OSD_PIP_TRANSPARENCY_MAX;
            g_stOsdItemData.usAdjValueCenter = _OSD_PIP_TRANSPARENCY_CENTER;
            g_stOsdItemData.usSubStringIdx = _STRING_PIP_TRANSPARENCY;
            g_stOsdItemData.usSubOsdState = _MENU_DISPLAYFUN_PIP_TRANSPARENCY_ADJUST;
            g_stOsdItemData.b3ShowType = _ADJ_BAR_REAL;
            break;

        case _OSD_MUTIP_PIP_SIZE:
            g_stOsdItemData.usStringIdx = _STRING_PIP_SIZE;
            g_stOsdItemData.usAdjValue = GET_OSD_PIP_SIZE();
            g_stOsdItemData.usAdjValueMin = _OSD_PIP_SIZE_MIN;
            g_stOsdItemData.usAdjValueMax = _OSD_PIP_SIZE_MAX;
            g_stOsdItemData.usAdjValueCenter = _OSD_PIP_SIZE_CENTER;
            g_stOsdItemData.usSubStringIdx = _STRING_PIP_SIZE;
            g_stOsdItemData.usSubOsdState = _MENU_DISPLAYFUN_PIP_SIZE_ADJUST;
            g_stOsdItemData.b3ShowType = _ADJ_BAR_REAL;
            break;

        case _OSD_MUTIP_INPUT_SWAP:
            g_stOsdItemData.usStringIdx = _STRING_INPUT_SWAP;
            g_stOsdItemData.usSubStringIdx = _STRING_OFF;
            g_stOsdItemData.b3ShowType = _ADJ_DIRECT;
            g_stOsdItemData.usSubOsdState = _MENU_HOTKEY_NONE;
            break;

#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
        case _OSD_MUTIP_PXP_MST:
            g_stOsdItemData.usStringIdx = _STRING_PXP_MST;
            g_stOsdItemData.usAdjValue = GET_OSD_PXP_MST();
            g_stOsdItemData.usAdjValueMin = _OFF_PXP_MST;
            g_stOsdItemData.usAdjValueMax = _ON_SELECT_MODE;
            g_stOsdItemData.usSubStringIdx = _STRING_OFF_PXP_MST;
            g_stOsdItemData.usSubOsdState = _MENU_PXP_MST_ADJUST;
            g_stOsdItemData.b3ShowType = _ADJ_LIST;
            break;
#endif
        case _OSD_PICTURE_BACKLIGHT:
            g_stOsdItemData.usStringIdx = _STRING_BACKLIGHT;
            g_stOsdItemData.usAdjValue = GET_OSD_BACKLIGHT();
            g_stOsdItemData.usAdjValueMin = _BACKLIGHT_MIN;
            g_stOsdItemData.usAdjValueMax = _BACKLIGHT_MAX;
            g_stOsdItemData.usAdjValueCenter = _BACKLIGHT_CENTER;
            g_stOsdItemData.usSubStringIdx = _STRING_BACKLIGHT;
            g_stOsdItemData.usSubOsdState = _MENU_PICTURE_BACKLIGHT_ADJUST;
            g_stOsdItemData.b3ShowType = _ADJ_BAR_PERCENT;
            break;

        case _OSD_PICTURE_BRIGHTNESS:
            g_stOsdItemData.usStringIdx = _STRING_BRIGHTNESS;
            g_stOsdItemData.usAdjValue = GET_OSD_BRIGHTNESS(GET_OSD_SELECT_REGION());
            g_stOsdItemData.usAdjValueMin = _BRIGHTNESS_MIN;
            g_stOsdItemData.usAdjValueMax = _BRIGHTNESS_MAX;
            g_stOsdItemData.usAdjValueCenter = _BRIGHTNESS_CENTER;
            g_stOsdItemData.usSubStringIdx = _STRING_BRIGHTNESS;
            g_stOsdItemData.usSubOsdState = _MENU_PICTURE_BRIGHTNESS_ADJUST;
            g_stOsdItemData.b3ShowType = _ADJ_BAR_PERCENT;
            break;

        case _OSD_PICTURE_CONTRAST:
            g_stOsdItemData.usStringIdx = _STRING_CONTRAST;
            g_stOsdItemData.usAdjValue = GET_OSD_CONTRAST(GET_OSD_SELECT_REGION());
            g_stOsdItemData.usAdjValueMin = _CONTRAST_MIN;
            g_stOsdItemData.usAdjValueMax = _CONTRAST_MAX;
            g_stOsdItemData.usAdjValueCenter = _CONTRAST_CENTER;
            g_stOsdItemData.usSubStringIdx = _STRING_CONTRAST;
            g_stOsdItemData.usSubOsdState = _MENU_PICTURE_CONTRAST_ADJUST;
            g_stOsdItemData.b3ShowType = _ADJ_BAR_PERCENT;
            break;

        case _OSD_PICTURE_SHARNESS:
            g_stOsdItemData.usStringIdx = _STRING_SHARPNESS;
            g_stOsdItemData.usAdjValue = GET_OSD_SHARPNESS(UserAdjustGetSelectRegionPort());
            g_stOsdItemData.usAdjValueMin = _SHARPNESS_MIN;
            g_stOsdItemData.usAdjValueMax = _SHARPNESS_MAX;
            g_stOsdItemData.usAdjValueCenter = _SHARPNESS_CENTER;
            g_stOsdItemData.usSubStringIdx = _STRING_SHARPNESS;
            g_stOsdItemData.usSubOsdState = _MENU_PICTURE_SHARPNESS_ADJUST;
            g_stOsdItemData.b3ShowType = _ADJ_BAR_REAL;
            break;

        case _OSD_DISPLAY_AUTO:
            g_stOsdItemData.usStringIdx = _STRING_AUTO_ADJUST;
            g_stOsdItemData.usSubStringIdx = _STRING_OFF;
            g_stOsdItemData.b3ShowType = _ADJ_DIRECT;
            g_stOsdItemData.usSubOsdState = _MENU_HOTKEY_NONE;
            break;

        case _OSD_AUTO_COLOR:
            g_stOsdItemData.usStringIdx = _STRING_AUTO_COLOR;
            g_stOsdItemData.usSubStringIdx = _STRING_OFF;
            g_stOsdItemData.b3ShowType = _ADJ_DIRECT;
            g_stOsdItemData.usSubOsdState = _MENU_HOTKEY_NONE;
            break;

        case _OSD_DISPLAY_HPOS:
            g_stOsdItemData.usStringIdx = _STRING_HPOS;
#if(_VGA_SUPPORT == _ON)
            if((SysVgaGetRegion() != _DISPLAY_RGN_NONE) &&
               (SysRegionGetDisplayState(SysVgaGetRegion()) == _DISPLAY_STATE_ACTIVE))// if(SysSourceGetSourceType() == _SOURCE_VGA)
            {
                g_stOsdItemData.usAdjValue = GET_VGA_MODE_ADJUST_H_POSITION();
            }
            else
#endif
            {
                g_stOsdItemData.usAdjValue = 0;
            }

            g_stOsdItemData.usAdjValueMin = _0_PERCENT;
            g_stOsdItemData.usAdjValueMax = _100_PERCENT;
            g_stOsdItemData.usAdjValueCenter = _50_PERCENT;
            g_stOsdItemData.usSubStringIdx = _STRIN_END;
            g_stOsdItemData.usSubOsdState = _MENU_ANALOG_HPOS_ADJUST;
            g_stOsdItemData.b3ShowType = _ADJ_BAR_REAL;
            break;

        case _OSD_DISPLAY_VPOS:
            g_stOsdItemData.usStringIdx = _STRING_VPOS;
#if(_VGA_SUPPORT == _ON)
            if((SysVgaGetRegion() != _DISPLAY_RGN_NONE) &&
               (SysRegionGetDisplayState(SysVgaGetRegion()) == _DISPLAY_STATE_ACTIVE))// if(SysSourceGetSourceType() == _SOURCE_VGA)
            {
                g_stOsdItemData.usAdjValue = GET_VGA_MODE_ADJUST_V_POSITION();
            }
            else
#endif
            {
                g_stOsdItemData.usAdjValue = 0;
            }

            g_stOsdItemData.usAdjValueMin = _0_PERCENT;
            g_stOsdItemData.usAdjValueMax = _100_PERCENT;
            g_stOsdItemData.usAdjValueCenter = _50_PERCENT;
            g_stOsdItemData.usSubStringIdx = _STRIN_END;
            g_stOsdItemData.usSubOsdState = _MENU_ANALOG_VPOS_ADJUST;
            g_stOsdItemData.b3ShowType = _ADJ_BAR_REAL;
            break;

        case _OSD_DISPLAY_CLOCK:
            g_stOsdItemData.usStringIdx = _STRING_CLOCK;
#if(_VGA_SUPPORT == _ON)
            if((SysVgaGetRegion() != _DISPLAY_RGN_NONE) &&
               (SysRegionGetDisplayState(SysVgaGetRegion()) == _DISPLAY_STATE_ACTIVE)) // if(SysSourceGetSourceType() == _SOURCE_VGA)
            {
#if(_AUTO_CLOCK_SAVE_VALUE_OPTION == _CLOCK_SAVE_PERCENT_VALUE)
                g_stOsdItemData.usAdjValue = GET_VGA_MODE_ADJUST_CLOCK();
                g_stOsdItemData.usAdjValueMin = _0_PERCENT;
                g_stOsdItemData.usAdjValueMax = _100_PERCENT;
                g_stOsdItemData.usAdjValueCenter = _50_PERCENT;
#else
                g_stOsdItemData.usAdjValue = GET_VGA_MODE_ADJUST_CLOCK();
                g_stOsdItemData.usAdjValueMin = UserCommonVgaGetAdcClockRange(_GET_CLOCKRANGE_MIN);
                g_stOsdItemData.usAdjValueMax = UserCommonVgaGetAdcClockRange(_GET_CLOCKRANGE_MAX);
                g_stOsdItemData.usAdjValueCenter = (((g_stOsdItemData.usAdjValueMax - g_stOsdItemData.usAdjValueMin) / 2) + g_stOsdItemData.usAdjValueMin);
#endif
            }
            else
#endif
            {
                g_stOsdItemData.usAdjValue = 0;
                g_stOsdItemData.usAdjValueMin = _0_PERCENT;
                g_stOsdItemData.usAdjValueMax = _100_PERCENT;
                g_stOsdItemData.usAdjValueCenter = _50_PERCENT;
            }

            g_stOsdItemData.usSubStringIdx = _STRING_CLOCK;
            g_stOsdItemData.usSubOsdState = _MENU_ANALOG_CLOCK_ADJUST;
            g_stOsdItemData.b3ShowType = _ADJ_BAR_REAL;
            break;

        case _OSD_DISPLAY_PHASE:
            g_stOsdItemData.usStringIdx = _STRING_PHASE;
#if(_VGA_SUPPORT == _ON)
            if((SysVgaGetRegion() != _DISPLAY_RGN_NONE) &&
               (SysRegionGetDisplayState(SysVgaGetRegion()) == _DISPLAY_STATE_ACTIVE))// if(SysSourceGetSourceType() == _SOURCE_VGA)
            {
                g_stOsdItemData.usAdjValue = GET_VGA_MODE_ADJUST_PHASE();
                g_stOsdItemData.usAdjValueMin = _OSD_PHASE_MIN;
                g_stOsdItemData.usAdjValueMax = _OSD_PHASE_MAX;
                g_stOsdItemData.usAdjValueCenter = (((_OSD_PHASE_MAX - _OSD_PHASE_MIN) / 2) + _OSD_PHASE_MIN);
            }
            else
#endif
            {
                g_stOsdItemData.usAdjValue = 0;
                g_stOsdItemData.usAdjValueMin = _0_PERCENT;
                g_stOsdItemData.usAdjValueMax = _100_PERCENT;
                g_stOsdItemData.usAdjValueCenter = _50_PERCENT;
            }

            g_stOsdItemData.usSubStringIdx = _STRING_PHASE;
            g_stOsdItemData.usSubOsdState = _MENU_ANALOG_PHASE_ADJUST;
            g_stOsdItemData.b3ShowType = _ADJ_BAR_REAL;
            break;

        case _OSD_DISPLAY_DISP_ROTATE:
            g_stOsdItemData.usStringIdx = _STRING_DISP_ROTATE;
            g_stOsdItemData.usAdjValue = GET_OSD_DISP_ROTATE();
            g_stOsdItemData.usAdjValueMin = _DISP_ROTATE_0;
            g_stOsdItemData.usAdjValueMax = (_DISP_ROTATE_AMOUNT - 1);
            g_stOsdItemData.usSubStringIdx = _STRING_0_DEGREE;
            g_stOsdItemData.usSubOsdState = _MENU_DISPLAYFUN_DISP_ROTATE_ADJUST;
            g_stOsdItemData.b3ShowType = _ADJ_LIST;
            break;

        case _OSD_DISPLAY_LATENCY:
            g_stOsdItemData.usStringIdx = _STRING_DISP_LATENCY;
            g_stOsdItemData.usAdjValue = GET_OSD_LATENCY();
            g_stOsdItemData.usAdjValueMin = _LATENCY_L;
            g_stOsdItemData.usAdjValueMax = _LATENCY_H;
            g_stOsdItemData.usSubStringIdx = _STRING_ULTRA_VIVID_L;
            g_stOsdItemData.usSubOsdState = _MENU_DISPLAYFUN_LATENCY_ADJUST;
            g_stOsdItemData.b3ShowType = _ADJ_LIST;
            break;

        case _OSD_DISPLAY_FREEZE:
            g_stOsdItemData.usStringIdx = _STRING_FREEZE;
            g_stOsdItemData.usAdjValue = GET_OSD_FREEZE_STATUS();
            g_stOsdItemData.usAdjValueMin = _OFF;
            g_stOsdItemData.usAdjValueMax = _ON;
            g_stOsdItemData.usSubStringIdx = _STRING_OFF;
            g_stOsdItemData.usSubOsdState = _MENU_DISPLAYFUN_FREEZE_ADJUST;
            g_stOsdItemData.b3ShowType = _ADJ_LIST;
            break;

        case _OSD_COLOR_PANEL_UNIFORMITY:
            g_stOsdItemData.usStringIdx = _STRING_PANEL_UNIFORMITY;
#if(_UNIFORMITY_FUNCTION == _ON)
            if(UserCommonColorPanelUniformityCheckStatus(GET_OSD_SYSTEM_SELECT_REGION()))
            {
                g_stOsdItemData.usAdjValue = GET_OSD_PANEL_UNIFORMITY(GET_OSD_SELECT_REGION());
            }
            else
#endif
            {
                SET_OSD_PANEL_UNIFORMITY(GET_OSD_SELECT_REGION(), _OFF);
                SET_OSD_PANEL_UNIFORMITY(GET_OSD_INVERSE_REGION(), _OFF);
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
                g_stOsdItemData.usAdjValue = _OFF;
            }
            g_stOsdItemData.usAdjValueMin = _OFF;
            g_stOsdItemData.usAdjValueMax = _ON;
            g_stOsdItemData.usSubStringIdx = _STRING_OFF;
            g_stOsdItemData.usSubOsdState = _MENU_COLOR_PANEL_UNIFORMITY_ADJUST;
            g_stOsdItemData.b3ShowType = _ADJ_LIST;
            break;

        case _OSD_COLOR_GAMMA:
            g_stOsdItemData.usStringIdx = _STRING_GAMMA;
            g_stOsdItemData.usAdjValue = GET_OSD_GAMMA(GET_OSD_SELECT_REGION());
            g_stOsdItemData.usAdjValueMin = _GAMMA_OFF;
            g_stOsdItemData.usAdjValueMax = _GAMMA_AMOUNT;
            g_stOsdItemData.usSubStringIdx = _STRING_GAMMA_OFF;
            g_stOsdItemData.usSubOsdState = _MENU_COLOR_GAMMA_ADJUST;
            g_stOsdItemData.b3ShowType = _ADJ_LIST;
            break;

        case _OSD_COLOR_TEMPERATURE:
            g_stOsdItemData.usStringIdx = _STRING_COLOR_TEMP;
            g_stOsdItemData.usAdjValue = GET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION());
            g_stOsdItemData.usAdjValueMin = _CT_9300;
            g_stOsdItemData.usAdjValueMax = _CT_COLORTEMP_AMOUNT;
            g_stOsdItemData.usSubStringIdx = _STRING_TEMP_9300;
            g_stOsdItemData.usSubOsdState = _MENU_COLOR_TEMPERATURE_ADJUST;
            g_stOsdItemData.b3ShowType = _ADJ_LIST;
            break;

        case _OSD_COLOR_TEMP_USER:
            g_stOsdItemData.usStringIdx = _STRING_COLOR_TEMP_USER;
            g_stOsdItemData.usAdjValue = 0;
            g_stOsdItemData.usAdjValueMin = 0;
            g_stOsdItemData.usAdjValueMax = 2;
            g_stOsdItemData.usSubStringIdx = _STRING_TEMP_USER_R;
            g_stOsdItemData.usSubOsdState = _MENU_COLOR_TEMP_USER_R;
            g_stOsdItemData.b3ShowType = _ADJ_LIST;
            break;

        case _OSD_COLOR_EFFECT:
            g_stOsdItemData.usStringIdx = _STRING_COLOR_EFFECT;
            g_stOsdItemData.usAdjValue = GET_OSD_COLOR_EFFECT(GET_OSD_SELECT_REGION());
            g_stOsdItemData.usAdjValueMin = _COLOREFFECT_STANDARD;
            g_stOsdItemData.usAdjValueMax = _COLOREFFECT_AMOUNT;
            g_stOsdItemData.usSubStringIdx = _STRING_COLOR_EFF_STD;
            g_stOsdItemData.usSubOsdState = _MENU_COLOR_EFFECT_ADJUST;
            g_stOsdItemData.b3ShowType = _ADJ_LIST;
            break;

        case _OSD_COLOR_EFFECT_USER:
            g_stOsdItemData.usStringIdx = _STRING_SIX_COLOR;
            g_stOsdItemData.usAdjValue = (_MENU_COLOR_EFF_USER_R_HUE - _MENU_COLOR_EFF_USER_R_HUE);
            g_stOsdItemData.usAdjValueMin = (_MENU_COLOR_EFF_USER_R_HUE - _MENU_COLOR_EFF_USER_R_HUE);
            g_stOsdItemData.usAdjValueMax = (_MENU_COLOR_EFF_USER_M_SAT - _MENU_COLOR_EFF_USER_R_HUE);
            g_stOsdItemData.usSubStringIdx = _STRING_COLOR_EFF_USER_R_HUE;
            g_stOsdItemData.usSubOsdState = _MENU_COLOR_EFF_USER_R_HUE;
            g_stOsdItemData.b3ShowType = _ADJ_LIST;
            break;

#if(_ICM_CHAMELEON_FUNCTION == _ON)
        case _OSD_COLOR_CHAMELEON_USER:
            g_stOsdItemData.usStringIdx = _STRING_CHAMELEON;
            g_stOsdItemData.usAdjValue = 0;
            g_stOsdItemData.usAdjValueMin = 0;
            g_stOsdItemData.usAdjValueMax = 2;
            g_stOsdItemData.usSubStringIdx = _STRING_HUE;
            g_stOsdItemData.usSubOsdState = _MENU_COLOR_CHAMELEON_HUE;
            g_stOsdItemData.b3ShowType = _ADJ_LIST;
            break;
#endif

        case _OSD_COLOR_DEMO:
            g_stOsdItemData.usStringIdx = _STRING_DEMO;
            g_stOsdItemData.usAdjValue = GET_OSD_HLWIN_TYPE();
            g_stOsdItemData.usAdjValueMin = _HL_WIN_OFF;
            g_stOsdItemData.usAdjValueMax = _HL_WIN_AMOUNT;
            g_stOsdItemData.usSubStringIdx = _STRING_COLOR_DEMO_OFF;
            g_stOsdItemData.usSubOsdState = _MENU_COLOR_DEMO_ADJUST;
            g_stOsdItemData.b3ShowType = _ADJ_LIST;
            break;
        case _OSD_COLOR_DEMO_SIDE:
            g_stOsdItemData.usStringIdx = _STRING_DEMO_SIDE;
            g_stOsdItemData.usAdjValue = GET_OSD_HLWIN_SIDE();
            g_stOsdItemData.usAdjValueMin = _OSD_HLW_INSIDE;
            g_stOsdItemData.usAdjValueMax = _OSD_HLW_OUTSIDE;
            g_stOsdItemData.usSubStringIdx = _STRING_INSIDE;
            g_stOsdItemData.usSubOsdState = _MENU_COLOR_DEMO_SIDE_ADJUST;
            g_stOsdItemData.b3ShowType = _ADJ_LIST;
            break;
        case _OSD_COLOR_FORMAT:
            g_stOsdItemData.usStringIdx = _STRING_COLOR_FORMAT;
            g_stOsdItemData.usAdjValue = GET_OSD_COLOR_FORMAT(SysRegionGetInputPort(GET_OSD_SYSTEM_DISPLAY_REGION()));
            g_stOsdItemData.usAdjValueMin = _COLOR_SPACE_RGB;
            g_stOsdItemData.usAdjValueMax = _COLOR_SPACE_YPBPR;
            g_stOsdItemData.usSubStringIdx = _STRING_COLOR_FORMAT_RGB;
            g_stOsdItemData.usSubOsdState = _MENU_COLOR_FORMAT_ADJUST;
            g_stOsdItemData.b3ShowType = _ADJ_LIST;
            break;

        case _OSD_COLOR_PCM:
            g_stOsdItemData.usStringIdx = _STRING_PCM;
            g_stOsdItemData.usAdjValue = GET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION());
            g_stOsdItemData.usAdjValueMin = _PCM_OSD_NATIVE;
            g_stOsdItemData.usAdjValueMax = _PCM_OSD_AMOUNT;
            g_stOsdItemData.usSubStringIdx = _STRING_COLOR_PCM_NACTIVE;
            g_stOsdItemData.usSubOsdState = _MENU_COLOR_PCM_ADJUST;
            g_stOsdItemData.b3ShowType = _ADJ_LIST;
            break;

        case _OSD_COLOR_HUE:
            g_stOsdItemData.usStringIdx = _STRING_HUE;
            g_stOsdItemData.usAdjValue = GET_OSD_HUE(GET_OSD_SELECT_REGION());
            g_stOsdItemData.usAdjValueMin = _HUE_MIN;
            g_stOsdItemData.usAdjValueMax = _HUE_MAX;
            g_stOsdItemData.usAdjValueCenter = _HUE_CENTER;
            g_stOsdItemData.usSubStringIdx = _STRIN_END;
            g_stOsdItemData.usSubOsdState = _MENU_COLOR_HUE_ADJUST;
            g_stOsdItemData.b3ShowType = _ADJ_BAR_PERCENT;
            break;

        case _OSD_COLOR_SATURATION:
            g_stOsdItemData.usStringIdx = _STRING_SATURATION;
            g_stOsdItemData.usAdjValue = GET_OSD_SATURATION(GET_OSD_SELECT_REGION());
            g_stOsdItemData.usAdjValueMin = _SATURATION_MIN;
            g_stOsdItemData.usAdjValueMax = _SATURATION_MAX;
            g_stOsdItemData.usAdjValueCenter = _SATURATION_CENTER;
            g_stOsdItemData.usSubStringIdx = _STRIN_END;
            g_stOsdItemData.usSubOsdState = _MENU_COLOR_SATURATION_ADJUST;
            g_stOsdItemData.b3ShowType = _ADJ_BAR_PERCENT;
            break;
#if(_DYNAMIC_LOWBLUE_FUNCTION == _ON)
        case _OSD_COLOR_EYE_PROTECT:
            g_stOsdItemData.usStringIdx = _STRING_EYE_PROTECT;
            g_stOsdItemData.usAdjValue = 0;
            g_stOsdItemData.usAdjValueMin = 0;
            g_stOsdItemData.usAdjValueMax = 2; // 1. Low Blue 2.Level 3.Night Mode 4.Ambient
            g_stOsdItemData.usSubStringIdx = _STRING_LOWBLUE;
            g_stOsdItemData.usSubOsdState = _MENU_COLOR_EYE_PROTECT_ADJUST;
            g_stOsdItemData.b3ShowType = _ADJ_LIST;
            break;
#endif
        case _OSD_ADVANCE_ASPECT:
            g_stOsdItemData.usStringIdx = _STRING_ASPECT_RATIO;
            g_stOsdItemData.usAdjValue = GET_OSD_ASPECT_RATIO_TYPE(UserAdjustGetSelectRegionPort());
            g_stOsdItemData.usAdjValueMin = _OSD_ASPECT_RATIO_FULL;
            g_stOsdItemData.usAdjValueMax = _OSD_ASPECT_RATIO_AMOUNT;
            g_stOsdItemData.usSubStringIdx = _STRING_AS_RATIO_FULL;
            g_stOsdItemData.usSubOsdState = _MENU_ADVANCE_ASPECT_ADJUST;
            g_stOsdItemData.b3ShowType = _ADJ_LIST;
            break;

        case _OSD_ADVANCE_OVERSCAN:
            g_stOsdItemData.usStringIdx = _STRING_OVER_SCAN;
            g_stOsdItemData.usAdjValue = GET_OSD_OVERSCAN_STATUS(UserAdjustGetSelectRegionPort());
            g_stOsdItemData.usAdjValueMin = _OFF;
            g_stOsdItemData.usAdjValueMax = _ON;
            g_stOsdItemData.usSubStringIdx = _STRING_OFF;
            g_stOsdItemData.usSubOsdState = _MENU_ADVANCE_OVER_SCAN_ADJUST;
            g_stOsdItemData.b3ShowType = _ADJ_LIST;
            break;

        case _OSD_ADVANCE_OVERDRIVE:
            g_stOsdItemData.usStringIdx = _STRING_OVER_DRIVE;
            g_stOsdItemData.usAdjValue = GET_OSD_OD_GAIN();
            g_stOsdItemData.usAdjValueMin = _OD_GAIN_MIN;
            g_stOsdItemData.usAdjValueMax = _OD_GAIN_MAX;
            g_stOsdItemData.usAdjValueCenter = _OD_GAIN_CENTER;
            g_stOsdItemData.usSubStringIdx = _STRING_OFF;
            g_stOsdItemData.usSubOsdState = _MENU_ADVANCE_OD_GAIN_ADJUST;
            g_stOsdItemData.b3ShowType = _ADJ_BAR_REAL;
            break;

        case _OSD_ADVANCE_DDCCI:
            g_stOsdItemData.usStringIdx = _STRING_DDCCI;
            g_stOsdItemData.usAdjValue = GET_OSD_DDCCI_STATUS();
            g_stOsdItemData.usAdjValueMin = _OFF;
            g_stOsdItemData.usAdjValueMax = _ON;
            g_stOsdItemData.usSubStringIdx = _STRING_OFF;
            g_stOsdItemData.usSubOsdState = _MENU_ADVANCE_DDCCI_ADJUST;
            g_stOsdItemData.b3ShowType = _ADJ_LIST;
            break;

        case _OSD_ADVANCE_ULTRAVIVID:
            g_stOsdItemData.usStringIdx = _STRING_ULTRA_VIVID;
            g_stOsdItemData.usAdjValue = GET_OSD_ULTRA_VIVID_STATUS(GET_OSD_SELECT_REGION());
            g_stOsdItemData.usAdjValueMin = _ULTRA_VIVID_OFF;
            g_stOsdItemData.usAdjValueMax = _ULTRA_VIVID_AMOUNT;
            g_stOsdItemData.usSubStringIdx = _STRING_ULTRA_VIVID_OFF;
            g_stOsdItemData.usSubOsdState = _MENU_ADVANCE_ULTRA_VIVID_ADJUST;
            g_stOsdItemData.b3ShowType = _ADJ_LIST;
            break;

        case _OSD_ADVANCE_DCR:
            g_stOsdItemData.usStringIdx = _STRING_DCR;
            g_stOsdItemData.usAdjValue = GET_OSD_DCR_STATUS();
            g_stOsdItemData.usAdjValueMin = _OFF;
            g_stOsdItemData.usAdjValueMax = _ON;
            g_stOsdItemData.usSubStringIdx = _STRING_OFF;
            g_stOsdItemData.usSubOsdState = _MENU_ADVANCE_DCR_ADJUST;
            g_stOsdItemData.b3ShowType = _ADJ_LIST;
            break;

        case _OSD_ADVANCE_DPOPTION:
            g_stOsdItemData.usStringIdx = _STRING_DP_OPTION;
            g_stOsdItemData.usAdjValue = 0;// D0 Port
            g_stOsdItemData.usAdjValueMin = 0; // D0/D1/D2
            g_stOsdItemData.usAdjValueMax = 2;
            g_stOsdItemData.usSubStringIdx = _STRING_D0;
            g_stOsdItemData.usSubOsdState = _MENU_ADVANCE_DP_OPTION_D0;
            g_stOsdItemData.b3ShowType = _ADJ_LIST;
            break;

        case _OSD_ADVANCE_DPMST:
            g_stOsdItemData.usStringIdx = _STRING_DP_MST;
            g_stOsdItemData.usAdjValue = GET_OSD_DP_MST();
            g_stOsdItemData.usAdjValueMin = _MST_OFF;
            g_stOsdItemData.usAdjValueMax = _MST_AMOUNT;
            g_stOsdItemData.usSubStringIdx = _STRING_MST_OFF;
            g_stOsdItemData.usSubOsdState = _MENU_ADVANCE_DP_MST_ADJUST;
            g_stOsdItemData.b3ShowType = _ADJ_LIST;
            break;

        case _OSD_ADVANCE_DUAL_DP_EDID:
            g_stOsdItemData.usStringIdx = _STRING_DUAL_DP_EDID;
            g_stOsdItemData.usAdjValue = UserCommonNVRamGetSystemData(_DUAL_DP_EDID_SELECT);
            g_stOsdItemData.usAdjValueMin = _DUAL_DP_EDID_5K3K_60HZ;
            g_stOsdItemData.usAdjValueMax = _DUAL_DP_EDID_AMOUNT;
            g_stOsdItemData.usSubStringIdx = _STRING_DUAL_DP_5K3K_60HZ; // need to confirm
            g_stOsdItemData.usSubOsdState = _MENU_ADVANCE_DUAL_DP_EDID_ADJUST;
            g_stOsdItemData.b3ShowType = _ADJ_LIST;
            break;

        case _OSD_ADVANCE_DP_RESOLUTION:
            g_stOsdItemData.usStringIdx = _STRING_DP_RESOLUTION;
            if(GET_OSD_DSC_PORT() == _DSC_FROM_D0_PORT)
            {
                g_stOsdItemData.usAdjValue = 1;// D1 Port
            }
            else
            {
                g_stOsdItemData.usAdjValue = 0;// D0 Port
            }
            g_stOsdItemData.usAdjValueMin = 0; // D0/D1/D2
            g_stOsdItemData.usAdjValueMax = 2; // D2
            g_stOsdItemData.usSubStringIdx = _STRING_D0;
            g_stOsdItemData.usSubOsdState = _MENU_ADVANCE_EDID_ADJUST;
            g_stOsdItemData.b3ShowType = _ADJ_LIST;
            break;

        case _OSD_ADVANCE_CLONE:
            if(GET_OSD_DISPLAY_MODE() == _OSD_DM_1P)
            {
#if(_DP_TX_SOURCE_SWITCH_MODE_1P == _DP_TX_SOURCE_AUTO)
                g_stOsdItemData.usStringIdx = _STRING_CLONE;
                g_stOsdItemData.usAdjValue = GET_OSD_CLONE_MODE_1P();
                g_stOsdItemData.usAdjValueMin = _OFF;
                g_stOsdItemData.usAdjValueMax = _ON;
                g_stOsdItemData.usSubStringIdx = _STRING_OFF;
                g_stOsdItemData.usSubOsdState = _MENU_ADVANCE_CLONE_ADJUST;
                g_stOsdItemData.b3ShowType = _ADJ_LIST;

#elif(_DP_TX_SOURCE_SWITCH_MODE_1P == _DP_TX_SOURCE_FIXED_PORT)
                g_stOsdItemData.usStringIdx = _STRING_MST_TX;
                g_stOsdItemData.usAdjValue = GET_OSD_CLONE_MODE_1P();
                g_stOsdItemData.usAdjValueMin = _OSD_CLONE_FIX_OFF;
                g_stOsdItemData.usAdjValueMax = _OSD_CLONE_FIX_D6;
                g_stOsdItemData.usSubStringIdx = _STRING_CLONE_FIX_OFF;
                g_stOsdItemData.usSubOsdState = _MENU_ADVANCE_CLONE_ADJUST;
                g_stOsdItemData.b3ShowType = _ADJ_LIST;
#endif
            }
            else
            {
#if(_DP_TX_SOURCE_SWITCH_MODE_MTP == _DP_TX_SOURCE_AUTO)
                g_stOsdItemData.usStringIdx = _STRING_CLONE;
                g_stOsdItemData.usAdjValue = GET_OSD_CLONE_MODE_MTP();
                g_stOsdItemData.usAdjValueMin = _OFF;
                g_stOsdItemData.usAdjValueMax = _ON;
                g_stOsdItemData.usSubStringIdx = _STRING_OFF;
                g_stOsdItemData.usSubOsdState = _MENU_ADVANCE_CLONE_ADJUST;
                g_stOsdItemData.b3ShowType = _ADJ_LIST;

#elif(_DP_TX_SOURCE_SWITCH_MODE_MTP == _DP_TX_SOURCE_FIXED_PORT)
                g_stOsdItemData.usStringIdx = _STRING_MST_TX;
                g_stOsdItemData.usAdjValue = GET_OSD_CLONE_MODE_MTP();
                g_stOsdItemData.usAdjValueMin = _OSD_CLONE_FIX_OFF;
                g_stOsdItemData.usAdjValueMax = _OSD_CLONE_FIX_D6;
                g_stOsdItemData.usSubStringIdx = _STRING_CLONE_FIX_OFF;
                g_stOsdItemData.usSubOsdState = _MENU_ADVANCE_CLONE_ADJUST;
                g_stOsdItemData.b3ShowType = _ADJ_LIST;
#endif
            }

            break;

        case _OSD_ADVANCE_FREESYNC:
            g_stOsdItemData.usStringIdx = _STRING_FREESYNC;
            g_stOsdItemData.usAdjValue = GET_OSD_FREE_SYNC_STATUS();
            g_stOsdItemData.usAdjValueMin = _OFF;
            g_stOsdItemData.usAdjValueMax = _ON;
            g_stOsdItemData.usSubStringIdx = _STRING_OFF;
            g_stOsdItemData.usSubOsdState = _MENU_ADVANCE_FREESYNC_ADJUST;
            g_stOsdItemData.b3ShowType = _ADJ_LIST;
            break;

        case _OSD_ADVANCE_TYPEC_MODE:
            g_stOsdItemData.usStringIdx = _STRING_TYPEC_MODE;
            g_stOsdItemData.usAdjValue = 0;
            g_stOsdItemData.usAdjValueMin = 0;
            g_stOsdItemData.usAdjValueMax = 3;
            g_stOsdItemData.usSubStringIdx = _STRING_D0;
            g_stOsdItemData.usSubOsdState = _MENU_ADVANCE_TYPEC_MODE_D0;
            g_stOsdItemData.b3ShowType = _ADJ_LIST;
            break;

        case _OSD_ADVANCE_DSC:
            g_stOsdItemData.usStringIdx = _STRING_DSC;

#if(_EAGLE_SIGHT_SUPPORT == _ON)
            if(SysRegionEagleSightTransDisplayMode(SysModeGetDisplayMode()) == _DISPLAY_MODE_1P)
#else
            if(SysModeGetDisplayMode() == _DISPLAY_MODE_1P)
#endif
            {
                g_stOsdItemData.usAdjValue = GET_OSD_1P_DSC_PORT();
                g_stOsdItemData.usAdjValueMin = _DSC_OFF;
                g_stOsdItemData.usAdjValueMax = _DSC_AUTO;
                g_stOsdItemData.usSubStringIdx = _STRING_DSC_OFF;
                g_stOsdItemData.usSubOsdState = _MENU_ADVANCE_DSC_ADJUST;
                g_stOsdItemData.b3ShowType = _ADJ_LIST;
            }
            else
            {
#if(_DSC_MULTI_DISPLAY_AUTO_SELECT_SUPPORT == _ON)
                g_stOsdItemData.usAdjValue = GET_OSD_DSC_PORT();
                g_stOsdItemData.usAdjValueMin = _DSC_FROM_NO_PORT;
                g_stOsdItemData.usAdjValueMax = _DSC_PORT_AUTO_SELECT;
                g_stOsdItemData.usSubStringIdx = _STRING_DSC_OFF;
                g_stOsdItemData.usSubOsdState = _MENU_ADVANCE_DSC_ADJUST;
                g_stOsdItemData.b3ShowType = _ADJ_LIST;
#else
                g_stOsdItemData.usAdjValue = GET_OSD_DSC_PORT();
                g_stOsdItemData.usAdjValueMin = _DSC_FROM_NO_PORT;
                g_stOsdItemData.usAdjValueMax = _DSC_FROM_D5_PORT;
                g_stOsdItemData.usSubStringIdx = _STRING_DSC_NONE;
                g_stOsdItemData.usSubOsdState = _MENU_ADVANCE_DSC_ADJUST;
                g_stOsdItemData.b3ShowType = _ADJ_LIST;
#endif
            }
            break;

        case _OSD_ADVANCE_LOCALDIMMING:
            g_stOsdItemData.usStringIdx = _STRING_LOCAL_DIMMING;
            g_stOsdItemData.usAdjValue = GET_OSD_LOCAL_DIMMING();
            g_stOsdItemData.usAdjValueMin = _OFF;
            g_stOsdItemData.usAdjValueMax = _ON;
            g_stOsdItemData.usSubStringIdx = _STRING_OFF;
            g_stOsdItemData.usSubOsdState = _MENU_ADVANCE_HDR_LD_ONOFF_ADJUST;
            g_stOsdItemData.b3ShowType = _ADJ_LIST;
            break;

        case _OSD_ADVANCE_LOCALDIMMING_USER:
            g_stOsdItemData.usStringIdx = _STRING_LD_SMOOTHADJ;
            g_stOsdItemData.usAdjValue = GET_OSD_LD_ADJ();
            g_stOsdItemData.usAdjValueMin = _0_PERCENT;
            g_stOsdItemData.usAdjValueMax = _100_PERCENT;
            g_stOsdItemData.usAdjValueCenter = _50_PERCENT;
            g_stOsdItemData.usSubStringIdx = _STRING_OFF;
            g_stOsdItemData.usSubOsdState = _MENU_ADVANCE_HDR_LD_SMOOTH_ADJ_ADJUST;
            g_stOsdItemData.b3ShowType = _ADJ_BAR_REAL;
            break;

        case _OSD_ADVANCE_GLOBAL_DIMMING:
            g_stOsdItemData.usStringIdx = _STRING_GLOBAL_DIMMING;
            g_stOsdItemData.usAdjValue = GET_OSD_GLOBAL_DIMMING();
            g_stOsdItemData.usAdjValueMin = _OFF;
            g_stOsdItemData.usAdjValueMax = _ON;
            g_stOsdItemData.usSubStringIdx = _STRING_OFF;
            g_stOsdItemData.usSubOsdState = _MENU_ADVANCE_GLOBAL_DIMMING_ADJUST;
            g_stOsdItemData.b3ShowType = _ADJ_LIST;
            break;
        case _OSD_ADVANCE_LOCAL_CONTRAST:
            g_stOsdItemData.usStringIdx = _STRING_OWL_SIGHT;
            g_stOsdItemData.usAdjValue = GET_OSD_LOCAL_CONTRAST(GET_OSD_SELECT_REGION());
            g_stOsdItemData.usAdjValueMin = _LOCAL_CONTRAST_OFF;
            g_stOsdItemData.usAdjValueMax = _LOCAL_CONTRAST_AMOUNT;
            g_stOsdItemData.usSubStringIdx = _STRING_OWLSIGHT_OFF;
            g_stOsdItemData.usSubOsdState = _MENU_ADVANCE_LOCAL_CONTRAST_ADJUST;
            g_stOsdItemData.b3ShowType = _ADJ_LIST;
            break;
        case _OSD_ADVANCE_LOCAL_CONTRAST_USER:
            g_stOsdItemData.usStringIdx = _STRING_OWLSIGHT_USER;
            g_stOsdItemData.usAdjValue = 0;
            g_stOsdItemData.usAdjValueMin = 0;
            g_stOsdItemData.usAdjValueMax = 1;
            g_stOsdItemData.usSubStringIdx = _STRING_OWLSIGHT_BLENDING;
            g_stOsdItemData.usSubOsdState = _MENU_ADVANCE_LOCAL_CONTRAST_USER;
            g_stOsdItemData.b3ShowType = _ADJ_LIST;
            break;

        case _OSD_ADVANCE_PIXELSHIFT:
            g_stOsdItemData.usStringIdx = _STRING_PIXEL_SHIFT;
            g_stOsdItemData.usAdjValue = GET_OSD_PIXELSHIFT_STATUS();
            g_stOsdItemData.usAdjValueMin = _OFF;
            g_stOsdItemData.usAdjValueMax = _ON;
            g_stOsdItemData.usSubStringIdx = _STRING_OFF;
            g_stOsdItemData.usSubOsdState = _MENU_ADVANCE_PIXEL_SHIFT_ADJUST;
            g_stOsdItemData.b3ShowType = _ADJ_LIST;
            break;

        case _OSD_ADVANCE_HDMI_VERSIONS:
            g_stOsdItemData.usStringIdx = _STRING_HDMI_VERSION;
            // check which port is HDMI
            for(g_stOsdItemData.usAdjValue = 0; g_stOsdItemData.usAdjValue <= 5; g_stOsdItemData.usAdjValue++)
            {
                if(OsdDisp3rdItemCheck(_OSD_ADVANCE_HDMI_VERSIONS, g_stOsdItemData.usAdjValue) == _TRUE)
                {
                    break;
                }
            }
            // Prevent over D5 port
            if(g_stOsdItemData.usAdjValue > 5)
            {
                g_stOsdItemData.usAdjValueMin = 0;// _D0_INPUT_PORT;
            }
            g_stOsdItemData.usAdjValueMin = 0;// _D0_INPUT_PORT;
            g_stOsdItemData.usAdjValueMax = 5;// _D5_INPUT_PORT;
            g_stOsdItemData.usSubStringIdx = _STRING_HDMI_D0;
            g_stOsdItemData.usSubOsdState = _MENU_ADVANCE_HDMI_VERSION_ADJUST;
            g_stOsdItemData.b3ShowType = _ADJ_LIST;
            break;

        case _OSD_ADVANCE_SDR_TO_HDR:
            g_stOsdItemData.usStringIdx = _STRING_SDR_TO_HDR;
            g_stOsdItemData.usAdjValue = GET_OSD_SDR_TO_HDR(GET_OSD_SELECT_REGION());
            g_stOsdItemData.usAdjValueMin = _OFF;
            g_stOsdItemData.usAdjValueMax = _ON;
            g_stOsdItemData.usSubStringIdx = _STRING_OFF;
            g_stOsdItemData.usSubOsdState = _MENU_ADVANCE_SDR_TO_HDR_ADJUST;
            g_stOsdItemData.b3ShowType = _ADJ_LIST;
            break;
        case _OSD_ADVANCE_HUB_SWITCH:
            g_stOsdItemData.usStringIdx = _STRING_HUB_SWITCH;
            g_stOsdItemData.usAdjValue = GET_USER_USB_HUB_SWITCH_MODE();
            g_stOsdItemData.usAdjValueMin = _OSD_HUB_AUTO;
            g_stOsdItemData.usAdjValueMax = _OSD_HUB_D1;
            g_stOsdItemData.usSubStringIdx = _STRING_USB_AUTO;
            g_stOsdItemData.usSubOsdState = _MENU_ADVANCE_HUB_SWITCH_ADJUST;
            g_stOsdItemData.b3ShowType = _ADJ_LIST;
            break;
        case _OSD_ADVANCE_EAGLE_SIGHT:
            g_stOsdItemData.usStringIdx = _STRING_EAGLE_SIGHT;
            g_stOsdItemData.usAdjValue = 0;
            g_stOsdItemData.usAdjValueMin = 0;
#if(_EAGLE_SIGHT_CIRCLE_WIN_SUPPORT == _ON)
            g_stOsdItemData.usAdjValueMax = 7; // 1. on/off 2.region select 3.Transparent 4.Zoom 5.Capture Position 6. Display Position 7.Border 8.Circle Window
#else
            g_stOsdItemData.usAdjValueMax = 6; // 1. on/off 2.region select 3.Transparent 4.Zoom 5.Capture Position 6. Display Position 7.Border
#endif
            g_stOsdItemData.usSubStringIdx = _STRING_EAGLE_SIGHT_ONOFF;
            g_stOsdItemData.usSubOsdState = _MENU_ADVANCE_EAGLE_SIGHT_ADJUST;
            g_stOsdItemData.b3ShowType = _ADJ_LIST;
            break;
        case _OSD_ADVANCE_MBR:
            g_stOsdItemData.usStringIdx = _STRING_MBR;
            g_stOsdItemData.usAdjValue = _MBR_MODE;
            g_stOsdItemData.usAdjValueMin = _MBR_MODE;
            g_stOsdItemData.usAdjValueMax = _MBR_POSITION;
            g_stOsdItemData.usSubStringIdx = _STRING_MBR_MODE;
            g_stOsdItemData.usSubOsdState = _MENU_ADVANCE_MBR_ADJUST;
            g_stOsdItemData.b3ShowType = _ADJ_LIST;
            break;
        case _OSD_ADVANCE_DP_AUXLESS_ALPM:
            g_stOsdItemData.usStringIdx = _STRING_DP_ALPM;
            g_stOsdItemData.usAdjValue = GET_OSD_DP_AUXLESS_ALPM();
            g_stOsdItemData.usAdjValueMin = _OFF;
            g_stOsdItemData.usAdjValueMax = _ON;
            g_stOsdItemData.usSubStringIdx = _STRING_OFF;
            g_stOsdItemData.usSubOsdState = _MENU_ADVANCE_DP_AUXLESS_ALPM_ADJUST;
            g_stOsdItemData.b3ShowType = _ADJ_LIST;
            break;
        case _OSD_ADVANCE_DP_ADAPTIVESYNC:
            g_stOsdItemData.usStringIdx = _STRING_DP_ADAPTIVESYNC;
            g_stOsdItemData.usAdjValue = GET_OSD_DP_ADAPTIVE_SYNC();
            g_stOsdItemData.usAdjValueMin = _OFF;
            g_stOsdItemData.usAdjValueMax = _ON;
            g_stOsdItemData.usSubStringIdx = _STRING_OFF;
            g_stOsdItemData.usSubOsdState = _MENU_ADVANCE_DP_ADAPTIVESYNC;
            g_stOsdItemData.b3ShowType = _ADJ_LIST;
            break;
        case _OSD_ADVANCE_PANEL_REPLAY:
            g_stOsdItemData.usStringIdx = _STRING_PANEL_REPLAY;
            g_stOsdItemData.usAdjValue = GET_OSD_PANEL_REPLAY();
            g_stOsdItemData.usAdjValueMin = _OFF;
            g_stOsdItemData.usAdjValueMax = _ON;
            g_stOsdItemData.usSubStringIdx = _STRING_OFF;
            g_stOsdItemData.usSubOsdState = _MENU_ADVANCE_PANEL_REPLAYM_ADJUST;
            g_stOsdItemData.b3ShowType = _ADJ_LIST;
            break;

        case _OSD_ADVANCE_SDR_PLUS:
            g_stOsdItemData.usStringIdx = _STRING_SDR_PLUS;
            g_stOsdItemData.usAdjValue = GET_OSD_SDR_PLUS(GET_OSD_SELECT_REGION());
            g_stOsdItemData.usAdjValueMin = _OFF;
            g_stOsdItemData.usAdjValueMax = _ON;
            g_stOsdItemData.usSubStringIdx = _STRING_OFF;
            g_stOsdItemData.usSubOsdState = _MENU_ADVANCE_SDR_PLUS;
            g_stOsdItemData.b3ShowType = _ADJ_LIST;
            break;
        case _OSD_ADVANCE_SDR_PLUS_ADJ:
            g_stOsdItemData.usStringIdx = _STRING_SDR_PLUS_ADJ;
            g_stOsdItemData.usAdjValue = 0;
            g_stOsdItemData.usAdjValueMin = 0;
            g_stOsdItemData.usAdjValueMax = 1;// 1.Sharpness 2.Darkness
            g_stOsdItemData.usSubStringIdx = _STRING_SDR_PLUS_SHARP;
            g_stOsdItemData.usSubOsdState = _MENU_ADVANCE_SDR_PLUS_SELECT;
            g_stOsdItemData.b3ShowType = _ADJ_LIST;
            break;

#if(_IMMERSIVE_NIGHT_SNIPER_FUNCTION == _ON)
        case _OSD_ADVANCE_NIGHT_SNIPER:
            g_stOsdItemData.usStringIdx = _STRING_NIGHT_SNIPER;
            g_stOsdItemData.usAdjValue = 0;
            g_stOsdItemData.usAdjValueMin = 0;
            g_stOsdItemData.usAdjValueMax = 2;
            g_stOsdItemData.usSubStringIdx = _STRING_NIGHT_SNIPER_SELECT;
            g_stOsdItemData.usSubOsdState = _MENU_ADVANCE_NIGHT_SNIPER;
            g_stOsdItemData.b3ShowType = _ADJ_LIST;
            break;
#endif

        case _OSD_ADVANCE_ANTI_ALIASING:
            g_stOsdItemData.usStringIdx = _STRING_ANTI_ALIASING;
            g_stOsdItemData.usAdjValue = 0; // Mode
            g_stOsdItemData.usAdjValueMin = 0; // Mode/Level
            g_stOsdItemData.usAdjValueMax = 1;
            g_stOsdItemData.usSubStringIdx = _STRING_MODE;
            g_stOsdItemData.usSubOsdState = _MENU_ADVANCE_ANTI_ALIASING;
            g_stOsdItemData.b3ShowType = _ADJ_LIST;
            break;

        case _OSD_ADVANCE_ENERGY_SAVE:
            g_stOsdItemData.usStringIdx = _STRING_ENERGYSAVE;
            g_stOsdItemData.usAdjValue = GET_OSD_ENERGY_SAVER();
            g_stOsdItemData.usAdjValueMin = _OFF;
            g_stOsdItemData.usAdjValueMax = _ON;
            g_stOsdItemData.usSubStringIdx = _STRING_OFF;
            g_stOsdItemData.usSubOsdState = _MENU_ADVANCE_ENERGY_SAVER;
            g_stOsdItemData.b3ShowType = _ADJ_LIST;
            break;

        case _OSD_AUDIO_VOLUME:
            g_stOsdItemData.usStringIdx = _STRING_VOLUME;
            g_stOsdItemData.usAdjValue = GET_OSD_VOLUME();
            g_stOsdItemData.usAdjValueMin = _0_PERCENT;
            g_stOsdItemData.usAdjValueMax = _100_PERCENT;
            g_stOsdItemData.usAdjValueCenter = _50_PERCENT;
            g_stOsdItemData.usSubStringIdx = _STRING_OFF;
            g_stOsdItemData.usSubOsdState = _MENU_AUDIO_VOLUME_ADJUST;
            g_stOsdItemData.b3ShowType = _ADJ_BAR_REAL;
            break;

        case _OSD_AUDIO_MUTE:
            g_stOsdItemData.usStringIdx = _STRING_MUTE;
            g_stOsdItemData.usAdjValue = GET_OSD_VOLUME_MUTE();
            g_stOsdItemData.usAdjValueMin = _DISABLE;
            g_stOsdItemData.usAdjValueMax = _ENABLE;
            g_stOsdItemData.usSubStringIdx = _STRING_DISABLE;
            g_stOsdItemData.usSubOsdState = _MENU_AUDIO_MUTE_ON_OFF;
            g_stOsdItemData.b3ShowType = _ADJ_LIST;
            break;

        case _OSD_AUDIO_STAND_ALONG:
            g_stOsdItemData.usStringIdx = _STRING_STAND_ALONG;
            g_stOsdItemData.usAdjValue = GET_OSD_AUDIO_STAND_ALONE();
            g_stOsdItemData.usAdjValueMin = _OFF;
            g_stOsdItemData.usAdjValueMax = _ON;
            g_stOsdItemData.usSubStringIdx = _STRING_OFF;
            g_stOsdItemData.usSubOsdState = _MENU_AUDIO_STAND_ALONG_SELECT;
            g_stOsdItemData.b3ShowType = _ADJ_LIST;
            break;

        case _OSD_AUDIO_AUDIO_SOURCE:
            g_stOsdItemData.usStringIdx = _STRING_AUDIO_SOURCE;
            g_stOsdItemData.usAdjValue = GET_OSD_AUDIO_SOURCE();
            g_stOsdItemData.usAdjValueMin = _OSD_AUDIO_SOURCE_LINEIN;
            g_stOsdItemData.usSubStringIdx = _STRING_AUDIO_LINE_IN;
            g_stOsdItemData.usAdjValueMax = _OSD_AUDIO_SOURCE_DIGITAL_REGION_4;
            g_stOsdItemData.usSubOsdState = _MENU_AUDIO_AUDIO_SOURCE_SELECT;
            g_stOsdItemData.b3ShowType = _ADJ_LIST;
            break;

        case _OSD_AUDIO_AUDIO_SELF_TEST:
            g_stOsdItemData.usStringIdx = _STRING_AUDIO_SELF_TEST;
            g_stOsdItemData.usAdjValue = _OFF;
            g_stOsdItemData.usAdjValueMin = _OFF;
            g_stOsdItemData.usAdjValueMax = _ON;
            g_stOsdItemData.usSubStringIdx = _STRING_OFF;
            g_stOsdItemData.usSubOsdState = _MENU_AUDIO_AUDIO_SELF_TEST_SELECT;
            g_stOsdItemData.b3ShowType = _ADJ_LIST;
            break;

#if(_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE)
        case _OSD_TTS_FUNCTION:
            g_stOsdItemData.usStringIdx = _STRING_TTS_SUPPORT;
            g_stOsdItemData.usAdjValue = GET_OSD_AUDIO_TTS_SUPPORT();
            g_stOsdItemData.usAdjValueMin = _OFF;
            g_stOsdItemData.usAdjValueMax = _ON;
            g_stOsdItemData.usSubStringIdx = _STRING_OFF;
            g_stOsdItemData.usSubOsdState = _MENU_TTS_FUNCTION;
            g_stOsdItemData.b3ShowType = _ADJ_LIST;
            break;

        case _OSD_TTS_TEXT_VOLUME:
            g_stOsdItemData.usStringIdx = _STRING_TTS_TEXT_VOLUME;
            g_stOsdItemData.usAdjValue = GET_OSD_AUDIO_TTS_TEXT_VOLUME();
            g_stOsdItemData.usAdjValueMin = _0_PERCENT;
            g_stOsdItemData.usAdjValueMax = _100_PERCENT;
            g_stOsdItemData.usAdjValueCenter = _50_PERCENT;
            g_stOsdItemData.usSubStringIdx = _STRING_OFF;
            g_stOsdItemData.usSubOsdState = _MENU_TTS_TEXT_VOLUME;
            g_stOsdItemData.b3ShowType = _ADJ_BAR_REAL;
            break;

        case _OSD_TTS_AUDIO_VOLUME:
            g_stOsdItemData.usStringIdx = _STRING_TTS_AUDIO_VOLUME;
            g_stOsdItemData.usAdjValue = GET_OSD_AUDIO_TTS_AUDIO_VOLUME();
            g_stOsdItemData.usAdjValueMin = _0_PERCENT;
            g_stOsdItemData.usAdjValueMax = _100_PERCENT;
            g_stOsdItemData.usAdjValueCenter = _50_PERCENT;
            g_stOsdItemData.usSubStringIdx = _STRING_OFF;
            g_stOsdItemData.usSubOsdState = _MENU_TTS_AUDIO_VOLUME;
            g_stOsdItemData.b3ShowType = _ADJ_BAR_REAL;
            break;
#endif // End of #if(_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE)

        case _OSD_OTHER_RESET:
            g_stOsdItemData.usStringIdx = _STRING_RESET;
            g_stOsdItemData.usSubStringIdx = _STRING_OFF;
            g_stOsdItemData.b3ShowType = _ADJ_DIRECT;
            g_stOsdItemData.usSubOsdState = _MENU_HOTKEY_NONE;
            break;

        case _OSD_OTHER_MENU_TIME:
            g_stOsdItemData.usStringIdx = _STRING_MENU_TIME;
            g_stOsdItemData.usAdjValue = GET_OSD_TIME_OUT();
            g_stOsdItemData.usAdjValueMin = _OSD_TIMEOUT_MIN;
            g_stOsdItemData.usAdjValueMax = _OSD_TIMEOUT_MAX;
            g_stOsdItemData.usAdjValueCenter = _OSD_TIMEOUT_CENTER;
            g_stOsdItemData.usSubStringIdx = _STRING_OFF;
            g_stOsdItemData.usSubOsdState = _MENU_OTHER_MENU_TIME_ADJUST;
            g_stOsdItemData.b3ShowType = _ADJ_BAR_REAL;
            break;

        case _OSD_OTHER_OSD_HPOS:
            g_stOsdItemData.usStringIdx = _STRING_OSD_HPOS;
            g_stOsdItemData.usAdjValue = GET_OSD_HPOS();
            g_stOsdItemData.usAdjValueMin = _OSD_H_POS_MIN;
            g_stOsdItemData.usAdjValueMax = _OSD_H_POS_MAX;
            g_stOsdItemData.usAdjValueCenter = _OSD_H_POS_CENTER;
            g_stOsdItemData.usSubStringIdx = _STRING_OFF;
            g_stOsdItemData.usSubOsdState = _MENU_OTHER_OSD_HPOS_ADJUST;
            g_stOsdItemData.b3ShowType = _ADJ_BAR_REAL;
            break;

        case _OSD_OTHER_OSD_VPOS:
            g_stOsdItemData.usStringIdx = _STRING_OSD_VPOS;
            g_stOsdItemData.usAdjValue = GET_OSD_VPOS();
            g_stOsdItemData.usAdjValueMin = _OSD_V_POS_MIN;
            g_stOsdItemData.usAdjValueMax = _OSD_V_POS_MAX;
            g_stOsdItemData.usAdjValueCenter = _OSD_V_POS_CENTER;
            g_stOsdItemData.usSubStringIdx = _STRING_OFF;
            g_stOsdItemData.usSubOsdState = _MENU_OTHER_OSD_VPOS_ADJUST;
            g_stOsdItemData.b3ShowType = _ADJ_BAR_REAL;
            break;

        case _OSD_OTHER_LANGUAGE:
            g_stOsdItemData.usStringIdx = _STRING_LANGUAGE;
            g_stOsdItemData.usAdjValue = GET_OSD_LANGUAGE();
            g_stOsdItemData.usAdjValueMin = _ENGLISH;
            g_stOsdItemData.usAdjValueMax = _CHINESE_T;
            g_stOsdItemData.usSubStringIdx = _STRING_ENGLISH;
            g_stOsdItemData.usSubOsdState = _MENU_OTHER_LANGUAGE_ADJUST;
            g_stOsdItemData.b3ShowType = _ADJ_LIST;
            break;

        case _OSD_OTHER_TRNASPARENCY:
            g_stOsdItemData.usStringIdx = _STRING_TRANSPARENCY;
            g_stOsdItemData.usAdjValue = GET_OSD_TRANSPARENCY_STATUS();
            g_stOsdItemData.usAdjValueMin = _OSD_TRANSPARENCY_MIN;
            g_stOsdItemData.usAdjValueMax = _OSD_TRANSPARENCY_MAX;
            g_stOsdItemData.usAdjValueCenter = _OSD_TRANSPARENCY_CENTER;
            g_stOsdItemData.usSubStringIdx = _STRING_OFF;
            g_stOsdItemData.usSubOsdState = _MENU_OTHER_TRNASPARENCY_ADJUST;
            g_stOsdItemData.b3ShowType = _ADJ_BAR_PERCENT;
            break;

        case _OSD_OTHER_ROTATE:
            g_stOsdItemData.usStringIdx = _STRING_ROTATE;
            g_stOsdItemData.usAdjValue = GET_OSD_ROTATE_STATUS();
            g_stOsdItemData.usAdjValueMin = _OSD_ROTATE_DEGREE_0;
            g_stOsdItemData.usAdjValueMax = _OSD_ROTATE_DEGREE_180;
            g_stOsdItemData.usSubStringIdx = _STRING_OSD_0_DEGREE;
            g_stOsdItemData.usSubOsdState = _MENU_OTHER_ROTATE_ADJUST;
            g_stOsdItemData.b3ShowType = _ADJ_LIST;
            break;

        case _OSD_OTHER_BORDER_WIDTH:
            g_stOsdItemData.usStringIdx = _STRING_BORDER_WIDTH;
            g_stOsdItemData.usAdjValue = GET_OSD_SELECT_REGION_WIDTH();
            g_stOsdItemData.usAdjValueMin = _OSD_SR_WIDTH_MIN;
            g_stOsdItemData.usAdjValueMax = _OSD_SR_WIDTH_MAX;
            g_stOsdItemData.usAdjValueCenter = _OSD_SR_WIDTH_CENTER;
            g_stOsdItemData.usSubStringIdx = _STRING_BORDER_WIDTH;
            g_stOsdItemData.usSubOsdState = _MENU_OTHER_BORDER_WIDTH_ADJUST;
            g_stOsdItemData.b3ShowType = _ADJ_BAR_REAL;
            break;

        case _OSD_OTHER_BORDER_COLOR:
            g_stOsdItemData.usStringIdx = _STRING_BORDER_COLOR;
            g_stOsdItemData.usAdjValue = GET_OSD_SELECT_REGION_COLOR();
            g_stOsdItemData.usAdjValueMin = _SELECT_REGION_COLOR_R;
            g_stOsdItemData.usAdjValueMax = _SELECT_REGION_COLOR_W;
            g_stOsdItemData.usSubStringIdx = _STRING_COLOR_DEMO_TYPE1;
            g_stOsdItemData.usSubOsdState = _MENU_OTHER_BORDER_COLOR_ADJUST;
            g_stOsdItemData.b3ShowType = _ADJ_LIST;
            break;

        case _OSD_OTHER_CROSSHAIR:
            g_stOsdItemData.usStringIdx = _STRING_CROSSHAIR;
            g_stOsdItemData.usAdjValue = g_stOsdUserData.ucCrosshair;
            g_stOsdItemData.usAdjValueMin = _CROSSHAIR_OFF;
            g_stOsdItemData.usAdjValueMax = _CROSSHAIR_POSITION;
            g_stOsdItemData.usSubStringIdx = _STRING_OFF;
            g_stOsdItemData.usSubOsdState = _MENU_OTHER_CROSSHAIR_ADJUST;
            g_stOsdItemData.b3ShowType = _ADJ_LIST;
            break;

        case _OSD_HDR_MODE:
            g_stOsdItemData.usStringIdx = _STRING_HDR_MODE;
            g_stOsdItemData.usAdjValue = GET_OSD_HDR_MODE(SysRegionGetInputPort(GET_OSD_SYSTEM_DISPLAY_REGION())); // GET_OSD_HDR_MODE(GET_OSD_SELECT_REGION());
            g_stOsdItemData.usAdjValueMin = _HDR10_MODE_OFF;
#if(_HLG_SUPPORT == _ON)
            g_stOsdItemData.usAdjValueMax = _HDR10_HLG_MODE_FORCE_HLG;
#else
            g_stOsdItemData.usAdjValueMax = _HDR10_MODE_FORCE_2084;
#endif
            g_stOsdItemData.usSubStringIdx = _STRING_HDR10_MODE_OFF;
            g_stOsdItemData.usSubOsdState = _MENU_ADVANCE_HDR_MODE_ADJUST;
            g_stOsdItemData.b3ShowType = _ADJ_LIST;
            break;

        case _OSD_HDR_DARK_ENHANCE:
            g_stOsdItemData.usStringIdx = _STRING_DARK_ENHANCE;
            g_stOsdItemData.usAdjValue = GET_OSD_REGION_DARK_ENHANCE(GET_OSD_SELECT_REGION());
            g_stOsdItemData.usAdjValueMin = _OFF;
            g_stOsdItemData.usAdjValueMax = _ON;
            g_stOsdItemData.usSubStringIdx = _STRING_OFF;
            g_stOsdItemData.usSubOsdState = _MENU_ADVANCE_HDR_DARK_ENHANCE_ONOFF_ADJUST;
            g_stOsdItemData.b3ShowType = _ADJ_LIST;
            break;

        case _OSD_HDR_SHARP_ENHANCE:
            g_stOsdItemData.usStringIdx = _STRING_SHARPNESS_ENHANCE;
            g_stOsdItemData.usAdjValue = GET_OSD_REGION_HDR_SHARPNESS(GET_OSD_SELECT_REGION());
            g_stOsdItemData.usAdjValueMin = _OFF;
            g_stOsdItemData.usAdjValueMax = _ON;
            g_stOsdItemData.usSubStringIdx = _STRING_OFF;
            g_stOsdItemData.usSubOsdState = _MENU_ADVANCE_HDR_SHARPNESS_ONOFF_ADJUST;
            g_stOsdItemData.b3ShowType = _ADJ_LIST;
            break;

        case _OSD_HDR_CONTRAST:
            g_stOsdItemData.usStringIdx = _STRING_HDR_CONTRAST;
            g_stOsdItemData.usAdjValue = GET_OSD_REGION_HDR_CONTRAST(GET_OSD_SELECT_REGION());
            g_stOsdItemData.usAdjValueMin = _0_PERCENT;
            g_stOsdItemData.usAdjValueMax = _100_PERCENT;
            g_stOsdItemData.usAdjValueCenter = _50_PERCENT;
            g_stOsdItemData.usSubStringIdx = _STRING_OFF;
            g_stOsdItemData.usSubOsdState = _MENU_ADVANCE_HDR_CONTRAST_ADJUST;
            g_stOsdItemData.b3ShowType = _ADJ_BAR_REAL;
            break;

        case _OSD_HDR_COLOR_ENHANCE:
            g_stOsdItemData.usStringIdx = _STRING_COLOR_ENHANCE;
            g_stOsdItemData.usAdjValue = GET_OSD_HDR_COLOR_ENHANCE(GET_OSD_SELECT_REGION());
            g_stOsdItemData.usAdjValueMin = _HDR10_COLORENHANCE_OFF;
            g_stOsdItemData.usAdjValueMax = _HDR10_COLORENHANCE_TYPE_3;
            g_stOsdItemData.usSubStringIdx = _STRING_ULTRA_VIVID_OFF;
            g_stOsdItemData.usSubOsdState = _MENU_ADVANCE_HDR_COLOR_ENHANCE_ADJUST;
            g_stOsdItemData.b3ShowType = _ADJ_LIST;
            break;

        case _OSD_HDR_LIGHT_ENHANCE:
            g_stOsdItemData.usStringIdx = _STRING_LIGHT_ENHANCE;
            g_stOsdItemData.usAdjValue = GET_OSD_HDR_LIGHT_ENHANCE(GET_OSD_SELECT_REGION());
            g_stOsdItemData.usAdjValueMin = _HDR10_LIGHTENHANCE_OFF;
            g_stOsdItemData.usAdjValueMax = _HDR10_LIGHTENHANCE_TYPE_160;
            g_stOsdItemData.usSubStringIdx = _STRING_ULTRA_VIVID_OFF;
            g_stOsdItemData.usSubOsdState = _MENU_ADVANCE_HDR_LIGHT_ENHANCE_ADJUST;
            g_stOsdItemData.b3ShowType = _ADJ_LIST;
            break;

        case _OSD_HDR_HLG_OOTF:
            g_stOsdItemData.usStringIdx = _STRING_HLG_OOTF;
            g_stOsdItemData.usAdjValue = GET_OSD_HDR_HLG_OOTF(GET_OSD_SELECT_REGION());
            g_stOsdItemData.usAdjValueMin = _HLG_OOTF_STANDARD_MODE;
            g_stOsdItemData.usAdjValueMax = _HLG_OOTF_USER_MODE_3;
            g_stOsdItemData.usSubStringIdx = _STRING_HLG_STANDARD;
            g_stOsdItemData.usSubOsdState = _MENU_ADVANCE_HDR_HLG_OOTF_ADJUST;
            g_stOsdItemData.b3ShowType = _ADJ_LIST;
            break;
        case _OSD_SOURCE_1P:
            g_stOsdItemData.usStringIdx = _STRING_1P;
            g_stOsdItemData.usAdjValue = GET_OSD_1P_INPUT_SOURCE();
            g_stOsdItemData.usAdjValueMin = _OSD_INPUT_A0;
            g_stOsdItemData.usAdjValueMax = _OSD_INPUT_AUTO;
            g_stOsdItemData.usSubStringIdx = _STRING_A0_PORT;
            g_stOsdItemData.usSubOsdState = _MENU_INPUT_SOURCE_1P_ADJ;
            g_stOsdItemData.b3ShowType = _ADJ_LIST;
            break;

        case _OSD_SOURCE_2P:
            g_stOsdItemData.usStringIdx = _STRING_2P;
            g_stOsdItemData.usAdjValue = GET_OSD_2P_INPUT_SOURCE();
            g_stOsdItemData.usAdjValueMin = _OSD_INPUT_A0;
            g_stOsdItemData.usAdjValueMax = _OSD_INPUT_AUTO;
            g_stOsdItemData.usSubStringIdx = _STRING_A0_PORT;
            g_stOsdItemData.usSubOsdState = _MENU_INPUT_SOURCE_2P_ADJ;
            g_stOsdItemData.b3ShowType = _ADJ_LIST;
            break;

        case _OSD_SOURCE_3P:
            g_stOsdItemData.usStringIdx = _STRING_3P;
            g_stOsdItemData.usAdjValue = GET_OSD_3P_INPUT_SOURCE();
            g_stOsdItemData.usAdjValueMin = _OSD_INPUT_A0;
            g_stOsdItemData.usAdjValueMax = _OSD_INPUT_AUTO;
            g_stOsdItemData.usSubStringIdx = _STRING_A0_PORT;
            g_stOsdItemData.usSubOsdState = _MENU_INPUT_SOURCE_3P_ADJ;
            g_stOsdItemData.b3ShowType = _ADJ_LIST;
            break;

        case _OSD_SOURCE_4P:
            g_stOsdItemData.usStringIdx = _STRING_4P;
            g_stOsdItemData.usAdjValue = GET_OSD_4P_INPUT_SOURCE();
            g_stOsdItemData.usAdjValueMin = _OSD_INPUT_A0;
            g_stOsdItemData.usAdjValueMax = _OSD_INPUT_AUTO;
            g_stOsdItemData.usSubStringIdx = _STRING_A0_PORT;
            g_stOsdItemData.usSubOsdState = _MENU_INPUT_SOURCE_4P_ADJ;
            g_stOsdItemData.b3ShowType = _ADJ_LIST;
            break;

        case _OSD_EXIT_HOTKEY:
            g_stOsdItemData.usStringIdx = _STRING_EXIT_HOTKEY;
            g_stOsdItemData.usAdjValue = GET_OSD_HOTKEY_EXIT();
            g_stOsdItemData.usAdjValueMin = _OSD_PICTURE_BACKLIGHT;
            g_stOsdItemData.usAdjValueMax = _OSD_SOURCE_4P;
            g_stOsdItemData.usSubStringIdx = _STRING_BACKLIGHT;
            g_stOsdItemData.usSubOsdState = _MENU_EXIT_HOTKEY_ADJ;
            g_stOsdItemData.b3ShowType = _ADJ_LIST;
            break;
#if(_DM_FUNCTION == _ON)
        case _OSD_DVISION:
            g_stOsdItemData.usStringIdx = _STRING_DVISION;
            g_stOsdItemData.usAdjValue = GET_OSD_DVISION(SysRegionGetInputPort(GET_OSD_SYSTEM_DISPLAY_REGION()));
            g_stOsdItemData.usAdjValueMin = _OFF;
            g_stOsdItemData.usAdjValueMax = _ON;
            g_stOsdItemData.usSubStringIdx = _STRING_OFF;
            g_stOsdItemData.usSubOsdState = _MENU_OSD_DVISION;
            g_stOsdItemData.b3ShowType = _ADJ_LIST;
            break;
        case _OSD_DVISION_PICTURE:
            g_stOsdItemData.usStringIdx = _STRING_DVISION_PICTURE;
            g_stOsdItemData.usAdjValue = GET_DVISION_PICTURE(GET_OSD_SELECT_REGION());
            g_stOsdItemData.usAdjValueMin = _OSD_DVISION_PICTURE_DARK;
            g_stOsdItemData.usAdjValueMax = _OSD_DVISION_PICTURE_AMOUNT - 1;
            g_stOsdItemData.usSubStringIdx = _STRING_DVISION_DARK;
            g_stOsdItemData.usSubOsdState = _MENU_OSD_DVISION_PICTURE;
            g_stOsdItemData.b3ShowType = _ADJ_LIST;
            break;
        case _OSD_DVISION_BACKLIGHT:
            g_stOsdItemData.usStringIdx = _STRING_DVISION_BACKLIGHT;
            g_stOsdItemData.usAdjValue = GET_DVISION_BACKLIGHT(GET_OSD_SELECT_REGION());
            g_stOsdItemData.usAdjValueMin = _0_PERCENT;
            g_stOsdItemData.usAdjValueMax = _100_PERCENT;
            g_stOsdItemData.usAdjValueCenter = _50_PERCENT;
            g_stOsdItemData.usSubStringIdx = _STRING_OFF;
            g_stOsdItemData.usSubOsdState = _MENU_OSD_DVISION_BACKLIGHT;
            g_stOsdItemData.b3ShowType = _ADJ_BAR_PERCENT;
            break;
        case _OSD_DVISION_BRIGHTNESS:
            g_stOsdItemData.usStringIdx = _STRING_DVISION_BRIGHTNESS;
            g_stOsdItemData.usAdjValue = GET_DVISION_BRIGHTNESS(GET_OSD_SELECT_REGION());
            g_stOsdItemData.usAdjValueMin = _0_PERCENT;
            g_stOsdItemData.usAdjValueMax = _100_PERCENT;
            g_stOsdItemData.usAdjValueCenter = _50_PERCENT;
            g_stOsdItemData.usSubStringIdx = _STRING_OFF;
            g_stOsdItemData.usSubOsdState = _MENU_OSD_DVISION_BRIGHTNESS;
            g_stOsdItemData.b3ShowType = _ADJ_BAR_PERCENT;
            break;
        case _OSD_DVISION_CONTRAST:
            g_stOsdItemData.usStringIdx = _STRING_DVISION_CONTRAST;
            g_stOsdItemData.usAdjValue = GET_DVISION_CONTRAST(GET_OSD_SELECT_REGION());
            g_stOsdItemData.usAdjValueMin = _0_PERCENT;
            g_stOsdItemData.usAdjValueMax = _100_PERCENT;
            g_stOsdItemData.usAdjValueCenter = _50_PERCENT;
            g_stOsdItemData.usSubStringIdx = _STRING_OFF;
            g_stOsdItemData.usSubOsdState = _MENU_OSD_DVISION_CONTRAST;
            g_stOsdItemData.b3ShowType = _ADJ_BAR_PERCENT;
            break;
        case _OSD_DVISION_SATURATION:
            g_stOsdItemData.usStringIdx = _STRING_DVISION_SATURATION;
            g_stOsdItemData.usAdjValue = GET_DVISION_SATURATION(GET_OSD_SELECT_REGION());
            g_stOsdItemData.usAdjValueMin = _0_PERCENT;
            g_stOsdItemData.usAdjValueMax = _100_PERCENT;
            g_stOsdItemData.usAdjValueCenter = _50_PERCENT;
            g_stOsdItemData.usSubStringIdx = _STRING_OFF;
            g_stOsdItemData.usSubOsdState = _MENU_OSD_DVISION_SATURATION;
            g_stOsdItemData.b3ShowType = _ADJ_BAR_PERCENT;
            break;
        case _OSD_DVISION_RESET:
            g_stOsdItemData.usStringIdx = _STRING_DVISION_RESET;
            g_stOsdItemData.usSubStringIdx = _STRING_OFF;
            g_stOsdItemData.b3ShowType = _ADJ_DIRECT;
            break;
        case _OSD_DVISION_NOTIFICATION:
            g_stOsdItemData.usStringIdx = _STRING_DVISION_NOTIFICATION;
            g_stOsdItemData.usAdjValue = GET_OSD_DVISION_NOTICE(SysRegionGetInputPort(GET_OSD_SYSTEM_DISPLAY_REGION()));
            g_stOsdItemData.usAdjValueMin = _OFF;
            g_stOsdItemData.usAdjValueMax = _ON;
            g_stOsdItemData.usSubStringIdx = _STRING_OFF;
            g_stOsdItemData.usSubOsdState = _MENU_OSD_DVISION_NOTIFICATION;
            g_stOsdItemData.b3ShowType = _ADJ_LIST;
            break;
#endif

#if(_AUDIO_ARC_SUPPORT == _ON)
        case _OSD_AUDIO_ARC_OUTPUT:
            g_stOsdItemData.usStringIdx = _STRING_AUDIO_ARC_OUT;
            g_stOsdItemData.usAdjValue = GET_OSD_ARC_OUT();
            g_stOsdItemData.usAdjValueMin = _ARC_DAC;
            g_stOsdItemData.usAdjValueMax = _ARC_ARC;
            g_stOsdItemData.usSubStringIdx = _STRING_AUDIO_DAC;
            g_stOsdItemData.usSubOsdState = _MENU_AUDIO_ARC_OUTPUT;
            g_stOsdItemData.b3ShowType = _ADJ_LIST;
            break;
        case _OSD_AUDIO_ARC_INPUTPORT:
            g_stOsdItemData.usStringIdx = _STRING_AUDIO_ARC_PORT;
            g_stOsdItemData.usAdjValue = GET_OSD_ARC_PORT();
            g_stOsdItemData.usAdjValueMin = _ARC_PORT_LINE_IN;
            g_stOsdItemData.usAdjValueMax = _ARC_PORT_D4;
            g_stOsdItemData.usSubStringIdx = _STRING_AUDIO_ARC_PORT_LINE_IN;
            g_stOsdItemData.usSubOsdState = _MENU_AUDIO_ARC_INPUTPORT;
            g_stOsdItemData.b3ShowType = _ADJ_LIST;
            break;
        case _OSD_AUDIO_ARC_MODE:
            g_stOsdItemData.usStringIdx = _STRING_AUDIO_ARC_MODE;
            g_stOsdItemData.usAdjValue = GET_OSD_ARC_MODE();
            g_stOsdItemData.usAdjValueMin = _AUDIO_ARC_EARC_OFF;
            g_stOsdItemData.usAdjValueMax = _AUDIO_EARC_ON;
            g_stOsdItemData.usSubStringIdx = _STRING_ARC_EARC_OFF;
            g_stOsdItemData.usSubOsdState = _MENU_AUDIO_ARC_MODE;
            g_stOsdItemData.b3ShowType = _ADJ_LIST;
            break;
        case _OSD_AUDIO_ARC_MUTE:
            g_stOsdItemData.usStringIdx = _STRING_AUDIO_ARC_MUTE;
            g_stOsdItemData.usAdjValue = GET_OSD_ARC_MUTE_STATUS();
            g_stOsdItemData.usAdjValueMin = _OFF;
            g_stOsdItemData.usAdjValueMax = _ON;
            g_stOsdItemData.usSubStringIdx = _STRING_DISABLE;
            g_stOsdItemData.usSubOsdState = _MENU_AUDIO_ARC_MUTE;
            g_stOsdItemData.b3ShowType = _ADJ_LIST;
            break;
        case _OSD_AUDIO_ARC_CHANEL:
            g_stOsdItemData.usStringIdx = _STRING_AUDIO_ARC_CHANEL;
            g_stOsdItemData.usAdjValue = GET_OSD_ARC_CHANEL();
            g_stOsdItemData.usAdjValueMin = _ARC_2_CH;
            g_stOsdItemData.usAdjValueMax = _ARC_8_CH;
            g_stOsdItemData.usSubStringIdx = _STRING_AUDIO_ARC_2_CH;
            g_stOsdItemData.usSubOsdState = _MENU_AUDIO_ARC_CHANEL;
            g_stOsdItemData.b3ShowType = _ADJ_LIST;
            break;
#endif

#if(_USB2_HOST_EHCI_MASS_STORGE_PROGRAM_SUPPORT == _ON)
        case _OSD_ADVANCE_FW_UPDATE:
            g_stOsdItemData.usStringIdx = _STRING_FW_UPDATE;
            g_stOsdItemData.usAdjValue = _DISABLE;
            g_stOsdItemData.usAdjValueMin = _DISABLE;
            g_stOsdItemData.usAdjValueMax = _ENABLE;
            g_stOsdItemData.usSubStringIdx = _STRING_DISABLE;
            g_stOsdItemData.usSubOsdState = _MENU_ADVANCE_FW_UPDATE;
            g_stOsdItemData.b3ShowType = _ADJ_LIST;
            break;
#endif

            // ==>STEP 2 //update Item parameters
    }

    DebugMessageOsd("enumOsdItem", enumOsdItem);
    DebugMessageOsd("g_stOsdItemData.usAdjValue", g_stOsdItemData.usAdjValue);
}

//--------------------------------------------------
// Description  :Picture sub Item switcht
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdDisp2ndMenuValue(BYTE ucIndex, WORD usState, BYTE ucColor)
{
    WORD usTemp = 0;
    StructOsdItemDataType stBackValue;

    stBackValue = g_stOsdItemData;

    switch(usState)
    {
        case _OSD_DISPLAY_AUTO:
        case _OSD_AUTO_COLOR:
        case _OSD_MUTIP_INPUT_SWAP:
        case _OSD_OTHER_RESET:
#if(_DM_FUNCTION == _ON)
        case _OSD_DVISION_RESET:
#endif
            break;
        case _OSD_MUTIP_PIP_POSITION_USER:
        case _OSD_COLOR_TEMP_USER:
        case _OSD_COLOR_EFFECT_USER:
        case _OSD_COLOR_CHAMELEON_USER:
        case _OSD_ADVANCE_DPOPTION:
        case _OSD_ADVANCE_DP_RESOLUTION:
        case _OSD_ADVANCE_TYPEC_MODE:
        case _OSD_ADVANCE_HDMI_VERSIONS:
        case _OSD_ADVANCE_EAGLE_SIGHT:
        case _OSD_ADVANCE_MBR:
        case _OSD_ADVANCE_LOCAL_CONTRAST_USER:
        case _OSD_ADVANCE_SDR_PLUS_ADJ:
#if(_IMMERSIVE_NIGHT_SNIPER_FUNCTION == _ON)
        case _OSD_ADVANCE_NIGHT_SNIPER:
#endif
        case _OSD_ADVANCE_ANTI_ALIASING:

#if(_DYNAMIC_LOWBLUE_FUNCTION == _ON)
        case _OSD_COLOR_EYE_PROTECT:
#endif
            if(ucColor != _CP_GRAY)
            {
                // Enter 4th sub Menu
                ucColor = _CP_YELLOW;
            }
            OsdPropPutString(ROW(_MENU_2ND_ITEM_ROW_ST + ucIndex * 2), COL(_MENU_2ND_ITEM_VAL_COL_ST), _PFONT_PAGE_1, _STRING_ENTER, COLOR(ucColor, _CP_BG), GET_OSD_LANGUAGE());

            break;

        case _OSD_SOURCE_1P:
        case _OSD_SOURCE_2P:
        case _OSD_SOURCE_3P:
        case _OSD_SOURCE_4P:
            // Source name only English!!!
            if(g_stOsdItemData.b3ShowType == _ADJ_LIST)
            {
                usTemp = g_stOsdItemData.usSubStringIdx + g_stOsdItemData.usAdjValue - g_stOsdItemData.usAdjValueMin;
                OsdPropPutString(ROW(_MENU_2ND_ITEM_ROW_ST + ucIndex * 2), COL(_MENU_2ND_ITEM_VAL_COL_ST), _PFONT_PAGE_1, usTemp, COLOR(ucColor, _CP_BG), _ENGLISH);
            }
            break;
        case _OSD_EXIT_HOTKEY:
            OsdDispItemValueUpdate(stBackValue.usAdjValue);
            OsdPropPutString(ROW(_MENU_2ND_ITEM_ROW_ST + ucIndex * 2), COL(_MENU_2ND_ITEM_VAL_COL_ST), _PFONT_PAGE_1, g_stOsdItemData.usStringIdx, COLOR(ucColor, _CP_BG), GET_OSD_LANGUAGE());
            g_stOsdItemData = stBackValue;
            break;
//==>STEP 7 //If the case is not follow below condition, Please made by yourself here.

        default:
#if(_DM_FUNCTION == _ON)
            if(usState == _OSD_DVISION_PICTURE)
            {
                if(GET_DVISION_PICTURE_MODIFY(GET_OSD_SELECT_REGION()) == _ON)
                {
                    SET_OSD_INFO_STRING_MODE(_PUT_STRING_RIGHT);
                    SET_OSD_INFO_STRING_MODE_LENGTH(_MENU_3RD_ITEM_WIDTH - 2);
                    OsdPropPutString(ROW(_MENU_2ND_ITEM_ROW_ST + ucIndex * 2), COL(_MENU_2ND_ITEM_VAL_COL_ST), _PFONT_PAGE_1, _STRING_COLOR_EFF_USER, COLOR(ucColor, _CP_BG), GET_OSD_LANGUAGE());
                }
            }
#endif
            if(g_stOsdItemData.b3ShowType == _ADJ_LIST)
            {
                usTemp = g_stOsdItemData.usSubStringIdx + g_stOsdItemData.usAdjValue - g_stOsdItemData.usAdjValueMin;
                OsdPropPutString(ROW(_MENU_2ND_ITEM_ROW_ST + ucIndex * 2), COL(_MENU_2ND_ITEM_VAL_COL_ST), _PFONT_PAGE_1, usTemp, COLOR(ucColor, _CP_BG), GET_OSD_LANGUAGE());
            }
            else if(g_stOsdItemData.b3ShowType == _ADJ_BAR_PERCENT)
            {
                usTemp = UserCommonDisplayRealValueToPercentAdjust(g_stOsdItemData.usAdjValue, g_stOsdItemData.usAdjValueMax, g_stOsdItemData.usAdjValueMin, g_stOsdItemData.usAdjValueCenter);
                OsdPropShowNumber(ROW(_MENU_2ND_ITEM_ROW_ST + ucIndex * 2), COL(_MENU_2ND_ITEM_VAL_COL_ST), usTemp, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_1, COLOR(ucColor, _CP_BG));
            }
            else if(g_stOsdItemData.b3ShowType == _ADJ_BAR_REAL)
            {
                usTemp = g_stOsdItemData.usAdjValue;
                OsdPropShowNumber(ROW(_MENU_2ND_ITEM_ROW_ST + ucIndex * 2), COL(_MENU_2ND_ITEM_VAL_COL_ST), usTemp, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_1, COLOR(ucColor, _CP_BG));
            }
            else// if(g_stOsdItemData.b3ShowType == _ADJ_DIRECT)
            {
                usTemp = g_stOsdItemData.usSubStringIdx;
                OsdPropPutString(ROW(_MENU_2ND_ITEM_ROW_ST + ucIndex * 2), COL(_MENU_2ND_ITEM_VAL_COL_ST), _PFONT_PAGE_1, usTemp, COLOR(ucColor, _CP_BG), GET_OSD_LANGUAGE());
            }
            break;
    }
}

//--------------------------------------------------
// Description  : Get  Sub item Icon
// Input Value  :
// Output Value :
//--------------------------------------------------
WORD OsdDisp2ndMenuStringGet(BYTE ucIndex, EnumOsdItem enumOsdItem)
{
    ucIndex = ucIndex;
    enumOsdItem = enumOsdItem;
    /*
    WORD usTempState = 0;

    switch(enumOsdItem)
    {
        case _OSD_MENU_PICTURE:
            if(ucIndex < _OSD_PICTURE_ITEM_AMOUNT)
            {
                usTempState = tOSD_PICTURE_ITEM_PRI[ucIndex];
            }
            break;

        case _OSD_MENU_DISPLAY:
            if(ucIndex < _OSD_DISPLAY_ITEM_AMOUNT)
            {
                usTempState = tOSD_DISPLAY_ITEM_PRI[ucIndex];
            }
            break;

        case _OSD_MENU_COLOR:
            if(ucIndex < _OSD_COLOR_ITEM_AMOUNT)
            {
                usTempState = tOSD_COLOR_ITEM_PRI[ucIndex];
            }
            break;

        case _OSD_MENU_ADVANCE:
            if(ucIndex < _OSD_ADVANCE_ITEM_AMOUNT)
            {
                usTempState = tOSD_ADVANCE_ITEM_PRI[ucIndex];
            }
            break;

        case _OSD_MENU_AUDIO:
            if(ucIndex < _OSD_AUDIO_ITEM_AMOUNT)
            {
                usTempState = tOSD_AUDIO_ITEM_PRI[ucIndex];
            }
            break;

        case _OSD_MENU_OTHER:
            if(ucIndex < _OSD_OTHER_ITEM_AMOUNT)
            {
                usTempState = tOSD_OTHER_ITEM_PRI[ucIndex];
            }
            break;

        case _OSD_MENU_FACTORY:
            break;

        case _OSD_MENU_HDR:
            if(ucIndex < _OSD_HDR_ITEM_AMOUNT)
            {
                usTempState = tOSD_HDR_ITEM_PRI[ucIndex];
            }
            break;

        case _OSD_MENU_MUTIP:
            if(ucIndex < _OSD_MUTIP_ITEM_AMOUNT)
            {
                usTempState = tOSD_MUTIP_ITEM_PRI[ucIndex];
            }
            break;

        case _OSD_MENU_QUICKLINK:
            if(ucIndex < _OSD_QUICK_ITEM_AMOUNT)
            {
                usTempState = tOSD_QUICK_ITEM_PRI[ucIndex];
            }
            break;

        case _OSD_MENU_INPUT:
            if(ucIndex < _OSD_INPUT_ITEM_AMOUNT)
            {
                usTempState = tOSD_INPUT_ITEM_PRI[ucIndex];
            }
            break;

#if(_DM_FUNCTION == _ON)
        case _OSD_MENU_DVISION:
            if(ucIndex < _OSD_DVISION_ITEM_AMOUNT)
            {
                usTempState = tOSD_DVISION_ITEM_PRI[ucIndex];
            }
            break;
#endif
        default:
            break;
    }
    */

    return g_stOsdItemData.usStringIdx;
}

//--------------------------------------------------
// Description : re-draw Picture Menu
// Input Value  : High: clean all & redraw ;  Low: Change selected color only
// Output Value :
//--------------------------------------------------
void OsdDisp2ndMenuReDraw(WORD usOsdState, bit bRedrawLevel)
{
    if(usOsdState == _MENU_NONE)
    {
        OsdDispDisableOsd();
        return;
    }

    UserCommonOsdWindowDisable(_OSD_WIN_HIGHLIGHT_1);
    OsdWindowSliderDisable();
    UserCommonOsdWindowDisable(_OSD_WIN_HIGHLIGHT_3);
    UserCommonOsdWindowDisable(_OSD_WIN_HIGHLIGHT_4);
    UserCommonOsdWindowDisable(_OSD_WIN_HIGHLIGHT_5);
    UserCommonOsdWindowDisable(_OSD_WIN_HIGHLIGHT_3_BORDER);

    if(bRedrawLevel == _HIGH)
    {
        // clear all
        OsdFuncClearOsd(4, 0, WIDTH(g_ucOsdWidth), HEIGHT(g_ucOsdHeight - 7));

        SET_OSD_WINDOW_BORDER_PIXEL_WIDTH(1);
        SET_OSD_WINDOW_BORDER_PIXEL_HEIGHT(1);

        SET_OSD_WINDOW_BUTTON_TYPE(_OSD_WINDOW_BUTTON_TYPE_BORDER);
        SET_OSD_WINDOW_COLOR_BORDER(_CP_WHITE);
        OsdWindowDrawingByFont(_OSD_WINDOW_1, ROW(3), COL(13), WIDTH(g_ucOsdWidth - 13), HEIGHT(g_ucOsdHeight - 5), _CP_LIGHTBLUE);
    }
    else
    {
        // clear all
        OsdFuncClearOsd(ROW(_MENU_2ND_ITEM_ROW_ST), COL(_MENU_2ND_ITEM_VAL_COL_ST), LENGTH(_MENU_3RD_ITEM_WIDTH), HEIGHT((_MENU_2ND_ITEM_MAX * 2)));
    }

    OsdWindowGridLine(1);////By Jerry -2017-12-11//replace GridLine function
    switch(usOsdState)
    {
        default:
        case _MENU_NONE:
            OsdDispDisableOsd();
            break;

        case _MENU_MUTIP_ITEM:
            SET_OSD_STATE(_MENU_MUTIP_ITEM);

            if(bRedrawLevel == _HIGH)
            {
                OsdDisp1stMenuIconString((0), _ICON_MUTIP, _CP_LIGHTBLUE);
            }
            OsdDisp2ndMenuStringSwitch(_OSD_MENU_MUTIP);
            OsdDisp2ndMenuCursor(GET_OSD_ITEM_INDEX());
            break;

        case _MENU_PICTURE_ITEM:
            SET_OSD_STATE(_MENU_PICTURE_ITEM);

            if(bRedrawLevel == _HIGH)
            {
                OsdDisp1stMenuIconString((0), _ICON_PICTURE, _CP_LIGHTBLUE);
            }
            OsdDisp2ndMenuStringSwitch(_OSD_MENU_PICTURE);
            OsdDisp2ndMenuCursor(GET_OSD_ITEM_INDEX());
            break;

        case _MENU_DISPLAY_ITEM:
            SET_OSD_STATE(_MENU_DISPLAY_ITEM);

            if(bRedrawLevel == _HIGH)
            {
                OsdDisp1stMenuIconString((0), _ICON_DISPLAYFUNCTION, _CP_LIGHTBLUE);
            }
            OsdDisp2ndMenuStringSwitch(_OSD_MENU_DISPLAY);
            OsdDisp2ndMenuCursor(GET_OSD_ITEM_INDEX());
            break;

        case _MENU_COLOR_ITEM:
            SET_OSD_STATE(_MENU_COLOR_ITEM);

            if(bRedrawLevel == _HIGH)
            {
                OsdDisp1stMenuIconString((0), _ICON_COLOR, _CP_LIGHTBLUE);
            }
            OsdDisp2ndMenuStringSwitch(_OSD_MENU_COLOR);
            OsdDisp2ndMenuCursor(GET_OSD_ITEM_INDEX());
            break;

        case _MENU_ADVANCE_ITEM:
            SET_OSD_STATE(_MENU_ADVANCE_ITEM);

            if(bRedrawLevel == _HIGH)
            {
                OsdDisp1stMenuIconString((0), _ICON_ADVANCE, _CP_LIGHTBLUE);
            }
            OsdDisp2ndMenuStringSwitch(_OSD_MENU_ADVANCE);
            OsdDisp2ndMenuCursor(GET_OSD_ITEM_INDEX());
            break;

        case _MENU_AUDIO_ITEM:
            SET_OSD_STATE(_MENU_AUDIO_ITEM);

            if(bRedrawLevel == _HIGH)
            {
                OsdDisp1stMenuIconString((0), _ICON_AUDIO, _CP_LIGHTBLUE);
            }
            OsdDisp2ndMenuStringSwitch(_OSD_MENU_AUDIO);
            OsdDisp2ndMenuCursor(GET_OSD_ITEM_INDEX());
            break;

        case _MENU_OTHER_ITEM:
            SET_OSD_STATE(_MENU_OTHER_ITEM);
            if(bRedrawLevel == _HIGH)
            {
                OsdDisp1stMenuIconString((0), _ICON_OTHER, _CP_LIGHTBLUE);
            }
            OsdDisp2ndMenuStringSwitch(_OSD_MENU_OTHER);
            OsdDisp2ndMenuCursor(GET_OSD_ITEM_INDEX());
            break;

        case _MENU_HDR_ITEM:
            SET_OSD_STATE(_MENU_HDR_ITEM);
            if(bRedrawLevel == _HIGH)
            {
                OsdDisp1stMenuIconString((0), _ICON_HDR, _CP_LIGHTBLUE);
            }
            OsdDisp2ndMenuStringSwitch(_OSD_MENU_HDR);
            OsdDisp2ndMenuCursor(GET_OSD_ITEM_INDEX());
            break;

        case _MENU_QUICKLINK_ITEM:
            SET_OSD_STATE(_MENU_QUICKLINK_ITEM);
            if(bRedrawLevel == _HIGH)
            {
                OsdDisp1stMenuIconString((0), _ICON_QUICKLINK, _CP_LIGHTBLUE);
            }
            OsdDisp2ndMenuStringSwitch(_OSD_MENU_QUICKLINK);
            OsdDisp2ndMenuCursor(GET_OSD_ITEM_INDEX());
            break;

        case _MENU_INPUT_ITEM:
            SET_OSD_STATE(_MENU_INPUT_ITEM);
            if(bRedrawLevel == _HIGH)
            {
                OsdDisp1stMenuIconString((0), _ICON_INPUT, _CP_LIGHTBLUE);
            }
            OsdDisp2ndMenuStringSwitch(_OSD_MENU_INPUT);
            OsdDisp2ndMenuCursor(GET_OSD_ITEM_INDEX());
            break;
#if(_DM_FUNCTION == _ON)
        case _MENU_DVISION_ITEM:
            SET_OSD_STATE(_MENU_DVISION_ITEM);
            if(bRedrawLevel == _HIGH)
            {
                OsdDisp1stMenuIconString((0), _ICON_DVISION, _CP_LIGHTBLUE);
            }
            OsdDisp2ndMenuStringSwitch(_OSD_MENU_DVISION);
            OsdDisp2ndMenuCursor(GET_OSD_ITEM_INDEX());
            break;
#endif

#if(_AUDIO_ARC_SUPPORT == _ON)
        case _MENU_AUDIO_ARC_EARC_ITEM:
            SET_OSD_STATE(_MENU_AUDIO_ARC_EARC_ITEM);
            if(bRedrawLevel == _HIGH)
            {
                OsdDisp1stMenuIconString((0), _ICON_EARC, _CP_LIGHTBLUE);
            }
            OsdDisp2ndMenuStringSwitch(_OSD_MENU_AUDIO_ARC_EARC);
            OsdDisp2ndMenuCursor(GET_OSD_ITEM_INDEX());
            break;
#endif
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
bit OsdDisp2ndMenuCheck(WORD usOsdState)
{
    switch(usOsdState)// OSD_PICTURE_ITEM_PRI[ucIndex])
    {
//-----------------------------------------------
        case _OSD_MUTIP_MODE:
            break;

        case _OSD_MUTIP_SELECTREGION:
            if(GET_OSD_DISPLAY_MODE() == _OSD_DM_1P)
            {
                return _FALSE;
            }
#if(_COLOR_DEMO_FUNCTION == _ON)
            if(GET_OSD_HLWIN_TYPE() != _HL_WIN_OFF)
            {
                return _FALSE;
            }
#endif
            break;

        case _OSD_MUTIP_LR_RATIO:
            switch(GET_OSD_DISPLAY_MODE())
            {
                case _OSD_DM_2P_LR:
                case _OSD_DM_3P_FLAG:
                    return _TRUE;

                case _OSD_DM_3P_SKEW_L:
                case _OSD_DM_3P_SKEW_R:
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
                    if(GET_D_DOMAIN_PATH() == _D_DOMAIN_4_PATH)
                    {
                        return _FALSE;
                    }
#endif
                    return _TRUE;

                default:
                    return _FALSE;
            }
            break;

        case _OSD_MUTIP_PIP_POSITION:
        case _OSD_MUTIP_PIP_TRANSPARENCY:
        case _OSD_MUTIP_PIP_SIZE:
            if(GET_OSD_DISPLAY_MODE() != _OSD_DM_2P_PIP)
            {
                return _FALSE;
            }
            break;

        case _OSD_MUTIP_PIP_POSITION_USER:
            if(GET_OSD_DISPLAY_MODE() != _OSD_DM_2P_PIP)
            {
                return _FALSE;
            }

            if(GET_OSD_PIP_POSITION_TYPE() != _PIP_POSITON_USER)
            {
                return _FALSE;
            }
            break;

        case _OSD_MUTIP_INPUT_SWAP:
            if((GET_OSD_DISPLAY_MODE() == _OSD_DM_1P) ||
               (GET_OSD_DISPLAY_MODE() == _OSD_DM_3P_FLAG) ||
               (GET_OSD_DISPLAY_MODE() == _OSD_DM_3P_SKEW_L) ||
               (GET_OSD_DISPLAY_MODE() == _OSD_DM_3P_SKEW_R) ||
               (GET_OSD_DISPLAY_MODE() == _OSD_DM_3P_SKEW_T) ||
               (GET_OSD_DISPLAY_MODE() == _OSD_DM_3P_SKEW_B) ||
               (GET_OSD_DISPLAY_MODE() == _OSD_DM_4P))
            {
                return _FALSE;
            }
            break;

//-----------------------------------------------
        case _OSD_PICTURE_BACKLIGHT:
#if(_HDR10_BACKLIGHT_ADAPTIVE_TM_SUPPORT == _ON)
            if(UserCommonColorHDRGetBackLightAdaptiveTMBackLightStatus() != _HDR10_BACKLIGHT_ADAPTIVE_TM_BACKLIGHT_OSD)
            {
                return _FALSE;
            }
#elif(_HDR10_SUPPORT == _ON)
#if(_HLG_SUPPORT == _ON)
            if((UserCommonColorHDRGetHDR10Status(GET_OSD_SYSTEM_DISPLAY_REGION()) == _HDR10_ON) ||
               (UserCommonColorHDRGetHDR10Status(GET_OSD_SYSTEM_DISPLAY_REGION()) == _HLG_ON))
#else
            if(UserCommonColorHDRGetHDR10Status(GET_OSD_SYSTEM_DISPLAY_REGION()) == _HDR10_ON)
#endif
            {
                return _FALSE;
            }
#endif
#if(_FREESYNC_II_SUPPORT == _ON)
            if(UserCommonColorHDRGetFreesynIIStatus(GET_OSD_SYSTEM_DISPLAY_REGION()) == _ON)
            {
                return _FALSE;
            }
#endif
            break;

        case _OSD_PICTURE_BRIGHTNESS:
#if(_HDR10_SUPPORT == _ON)
#if(_HLG_SUPPORT == _ON)
            if((UserCommonColorHDRGetHDR10Status(GET_OSD_SYSTEM_DISPLAY_REGION()) == _HDR10_ON) ||
               (UserCommonColorHDRGetHDR10Status(GET_OSD_SYSTEM_DISPLAY_REGION()) == _HLG_ON))
#else
            if(UserCommonColorHDRGetHDR10Status(GET_OSD_SYSTEM_DISPLAY_REGION()) == _HDR10_ON)
#endif
            {
                return _FALSE;
            }
#endif
#if(_FREESYNC_II_SUPPORT == _ON)
            if(UserCommonColorHDRGetFreesynIIStatus(GET_OSD_SYSTEM_DISPLAY_REGION()) == _ON)
            {
                return _FALSE;
            }
#endif
            break;

        case _OSD_PICTURE_CONTRAST:
#if(_HDR10_SUPPORT == _ON)
#if(_HLG_SUPPORT == _ON)
            if((UserCommonColorHDRGetHDR10Status(GET_OSD_SYSTEM_DISPLAY_REGION()) == _HDR10_ON) ||
               (UserCommonColorHDRGetHDR10Status(GET_OSD_SYSTEM_DISPLAY_REGION()) == _HLG_ON))
#else
            if(UserCommonColorHDRGetHDR10Status(GET_OSD_SYSTEM_DISPLAY_REGION()) == _HDR10_ON)
#endif
            {
                return _FALSE;
            }
#endif
#if(_FREESYNC_II_SUPPORT == _ON)
            if(UserCommonColorHDRGetFreesynIIStatus(GET_OSD_SYSTEM_DISPLAY_REGION()) == _ON)
            {
                return _FALSE;
            }
#endif
            break;

        case _OSD_PICTURE_SHARNESS:
            break;
//-----------------------------------------------
        case _OSD_AUTO_COLOR:
        case _OSD_DISPLAY_HPOS:
        case _OSD_DISPLAY_VPOS:
        case _OSD_DISPLAY_AUTO:
        case _OSD_DISPLAY_CLOCK:
        case _OSD_DISPLAY_PHASE:
#if(_VGA_SUPPORT == _ON)
            if((SysVgaGetRegion() != _DISPLAY_RGN_NONE) &&
               (SysRegionGetDisplayState(SysVgaGetRegion()) == _DISPLAY_STATE_ACTIVE))
            {
                return _TRUE;
            }
            else
#endif
            {
                return _FALSE;
            }
            break;

        case _OSD_DISPLAY_DISP_ROTATE:
            if(GET_OSD_DISPLAY_MODE() != _OSD_DM_1P)
            {
                return _FALSE;
            }
            break;

        case _OSD_DISPLAY_LATENCY:
#if(_DISPLAY_ROTATION_SUPPORT == _ON)
            if(GET_OSD_DISP_ROTATE() != _DISP_ROTATE_0)
            {
                return _FALSE;
            }
#endif
            if(GET_OSD_DISPLAY_MODE() != _OSD_DM_1P)
            {
                return _FALSE;
            }
            break;

        case _OSD_DISPLAY_FREEZE:
            if(GET_OSD_DISPLAY_MODE() != _OSD_DM_1P)
            {
                return _FALSE;
            }
            break;

//-----------------------------------------------
        case _OSD_COLOR_PANEL_UNIFORMITY:
            if(GET_OSD_LOCAL_DIMMING() == _ON)
            {
                return _FALSE;
            }
#if(_FREESYNC_II_SUPPORT == _ON)
            if(UserCommonColorHDRGetFreesynIIStatus(GET_OSD_SYSTEM_DISPLAY_REGION()) == _ON)
            {
                return _FALSE;
            }
#endif
#if(_SDR_TO_HDR_FUNCTION == _ON)
            if(GET_OSD_SDR_TO_HDR(GET_OSD_SELECT_REGION()) == _ON)
            {
                return _FALSE;
            }
#endif
#if(_HDR10_SUPPORT == _ON)
#if(_HLG_SUPPORT == _ON)
            if((UserCommonColorHDRGetHDR10Status(GET_OSD_SYSTEM_DISPLAY_REGION()) == _HDR10_ON) ||
               (UserCommonColorHDRGetHDR10Status(GET_OSD_SYSTEM_DISPLAY_REGION()) == _HLG_ON))
#else
            if(UserCommonColorHDRGetHDR10Status(GET_OSD_SYSTEM_DISPLAY_REGION()) == _HDR10_ON)
#endif
            {
                return _FALSE;
            }
#endif
#if(_UNIFORMITY_FUNCTION == _ON)
            if(UserCommonColorPanelUniformityCheckStatus(GET_OSD_SYSTEM_SELECT_REGION()) == _FALSE)
            {
                return _FALSE;
            }
#endif

            break;

        case _OSD_COLOR_GAMMA:
#if(_FREESYNC_II_SUPPORT == _ON)
            if(UserCommonColorHDRGetFreesynIIStatus(GET_OSD_SYSTEM_DISPLAY_REGION()) == _ON)
            {
                return _FALSE;
            }
#endif
#if(_SDR_TO_HDR_FUNCTION == _ON)
            if(GET_OSD_SDR_TO_HDR(GET_OSD_SELECT_REGION()) == _ON)
            {
                return _FALSE;
            }
#endif
#if(_HDR10_SUPPORT == _ON)
#if(_HLG_SUPPORT == _ON)
            if((UserCommonColorHDRGetHDR10Status(GET_OSD_SYSTEM_DISPLAY_REGION()) == _HDR10_ON) ||
               (UserCommonColorHDRGetHDR10Status(GET_OSD_SYSTEM_DISPLAY_REGION()) == _HLG_ON))
#else
            if(UserCommonColorHDRGetHDR10Status(GET_OSD_SYSTEM_DISPLAY_REGION()) == _HDR10_ON)
#endif
            {
                return _FALSE;
            }
#endif

            break;

        case _OSD_COLOR_TEMPERATURE:
#if(_HDR10_SUPPORT == _ON)
#if(_HLG_SUPPORT == _ON)
            if((UserCommonColorHDRGetHDR10Status(GET_OSD_SYSTEM_DISPLAY_REGION()) == _HDR10_ON) ||
               (UserCommonColorHDRGetHDR10Status(GET_OSD_SYSTEM_DISPLAY_REGION()) == _HLG_ON))
#else
            if(UserCommonColorHDRGetHDR10Status(GET_OSD_SYSTEM_DISPLAY_REGION()) == _HDR10_ON)
#endif
            {
                return _FALSE;
            }
#endif
#if(_FREESYNC_II_SUPPORT == _ON)
            if(UserCommonColorHDRGetFreesynIIStatus(GET_OSD_SYSTEM_DISPLAY_REGION()) == _ON)
            {
                return _FALSE;
            }
#endif
#if(_SDR_TO_HDR_FUNCTION == _ON)
            if(GET_OSD_SDR_TO_HDR(GET_OSD_SELECT_REGION()) == _ON)
            {
                return _FALSE;
            }
#endif
            break;

        case _OSD_COLOR_TEMP_USER:
#if(_HDR10_SUPPORT == _ON)
#if(_HLG_SUPPORT == _ON)
            if((UserCommonColorHDRGetHDR10Status(GET_OSD_SYSTEM_DISPLAY_REGION()) == _HDR10_ON) ||
               (UserCommonColorHDRGetHDR10Status(GET_OSD_SYSTEM_DISPLAY_REGION()) == _HLG_ON))
#else
            if(UserCommonColorHDRGetHDR10Status(GET_OSD_SYSTEM_DISPLAY_REGION()) == _HDR10_ON)
#endif
            {
                return _FALSE;
            }
#endif
#if(_FREESYNC_II_SUPPORT == _ON)
            if(UserCommonColorHDRGetFreesynIIStatus(GET_OSD_SYSTEM_DISPLAY_REGION()) == _ON)
            {
                return _FALSE;
            }
#endif
#if(_SDR_TO_HDR_FUNCTION == _ON)
            if(GET_OSD_SDR_TO_HDR(GET_OSD_SELECT_REGION()) == _ON)
            {
                return _FALSE;
            }
#endif
            if(GET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION()) != _CT_USER)
            {
                return _FALSE;
            }
            break;

        case _OSD_COLOR_EFFECT:
#if(_SDR_TO_HDR_FUNCTION == _ON)
            if(GET_OSD_SDR_TO_HDR(GET_OSD_SELECT_REGION()) == _ON)
            {
                return _FALSE;
            }
#endif
#if(_HDR10_SUPPORT == _ON)
#if(_HDR10_LIGHT_ENHANCE_FUNCTION == _ON)
            if(GET_OSD_HDR_LIGHT_ENHANCE(GET_OSD_SELECT_REGION()) != _LEVEL_OFF)
            {
                return _FALSE;
            }
#endif
#if(_HDR10_COLOR_ENHANCE_FUNCTION == _ON)
            if(GET_OSD_HDR_COLOR_ENHANCE(GET_OSD_SELECT_REGION()) != _LEVEL_OFF)
            {
                return _FALSE;
            }
#endif
#endif
            break;

        case _OSD_COLOR_EFFECT_USER:
#if(_SDR_TO_HDR_FUNCTION == _ON)
            if(GET_OSD_SDR_TO_HDR(GET_OSD_SELECT_REGION()) == _ON)
            {
                return _FALSE;
            }
#endif
#if(_HDR10_SUPPORT == _ON)
#if(_HLG_SUPPORT == _ON)
            if((UserCommonColorHDRGetHDR10Status(GET_OSD_SYSTEM_DISPLAY_REGION()) == _HDR10_ON) ||
               (UserCommonColorHDRGetHDR10Status(GET_OSD_SYSTEM_DISPLAY_REGION()) == _HLG_ON))
#else
            if(UserCommonColorHDRGetHDR10Status(GET_OSD_SYSTEM_DISPLAY_REGION()) == _HDR10_ON)
#endif
            {
                return _FALSE;
            }
#endif
            if(GET_OSD_COLOR_EFFECT(GET_OSD_SELECT_REGION()) != _COLOREFFECT_USER)
            {
                return _FALSE;
            }

            break;
#if(_ICM_CHAMELEON_FUNCTION == _ON)
        case _OSD_COLOR_CHAMELEON_USER:
#if(_SDR_TO_HDR_FUNCTION == _ON)
            if(GET_OSD_SDR_TO_HDR(GET_OSD_SELECT_REGION()) == _ON)
            {
                return _FALSE;
            }
#endif
#if(_HDR10_SUPPORT == _ON)
#if(_HLG_SUPPORT == _ON)
            if((UserCommonColorHDRGetHDR10Status(GET_OSD_SYSTEM_DISPLAY_REGION()) == _HDR10_ON) ||
               (UserCommonColorHDRGetHDR10Status(GET_OSD_SYSTEM_DISPLAY_REGION()) == _HLG_ON))
#else
            if(UserCommonColorHDRGetHDR10Status(GET_OSD_SYSTEM_DISPLAY_REGION()) == _HDR10_ON)
#endif
            {
                return _FALSE;
            }
#endif
            if(GET_OSD_COLOR_EFFECT(GET_OSD_SELECT_REGION()) != _COLOREFFECT_CHAMELEON)
            {
                return _FALSE;
            }

            break;
#endif
        case _OSD_COLOR_DEMO:
            if(UserCommonColorDemoModeSupportCheck() == _FALSE)
            {
                return _FALSE;
            }

            break;
        case _OSD_COLOR_DEMO_SIDE:
            if(GET_OSD_HLWIN_TYPE() == _HL_WIN_OFF)
            {
                return _FALSE;
            }
#if(_HW_D_DOMAIN_PATH_COUNT <= 1)
            return _FALSE;
#endif
            break;
        case _OSD_COLOR_FORMAT:
#if(_HDR10_SUPPORT == _ON)
#if(_HLG_SUPPORT == _ON)
            if((UserCommonColorHDRGetHDR10Status(GET_OSD_SYSTEM_DISPLAY_REGION()) == _HDR10_ON) ||
               (UserCommonColorHDRGetHDR10Status(GET_OSD_SYSTEM_DISPLAY_REGION()) == _HLG_ON))
#else
            if(UserCommonColorHDRGetHDR10Status(GET_OSD_SYSTEM_DISPLAY_REGION()) == _HDR10_ON)
#endif
            {
                return _FALSE;
            }
#endif

#if(_DM_FUNCTION == _ON)
#if(_IS_MAIN_PROCESS_CPU == _TRUE)
            if(GET_OSD_DVISION(SysRegionGetInputPort(GET_OSD_SYSTEM_DISPLAY_REGION())) == _ON)
            {
                if(UserCommonColorDMGetDMStatus(GET_OSD_SYSTEM_DISPLAY_REGION()) == _ON)
                {
                    return _FALSE;
                }
            }
#endif
#endif

            if(OsdDisplayGetSelectRegFullStatus() == _TRUE)
            {
                return _FALSE;
            }

            switch(SysRegionGetSourceType(GET_OSD_SYSTEM_DISPLAY_REGION()))
            {
                case _SOURCE_VGA:
                case _SOURCE_DVI:
                    break;

                default:
                    return _FALSE;
            }

            break;

        case _OSD_COLOR_PCM:
#if(_HDR10_SUPPORT == _ON)
#if(_HLG_SUPPORT == _ON)
            if((UserCommonColorHDRGetHDR10Status(GET_OSD_SYSTEM_DISPLAY_REGION()) == _HDR10_ON) ||
               (UserCommonColorHDRGetHDR10Status(GET_OSD_SYSTEM_DISPLAY_REGION()) == _HLG_ON))
#else
            if(UserCommonColorHDRGetHDR10Status(GET_OSD_SYSTEM_DISPLAY_REGION()) == _HDR10_ON)
#endif
            {
                return _FALSE;
            }
#endif

            break;

        case _OSD_COLOR_HUE:
        case _OSD_COLOR_SATURATION:
#if(_HDR10_SUPPORT == _ON)
#if(_HLG_SUPPORT == _ON)
            if((UserCommonColorHDRGetHDR10Status(GET_OSD_SYSTEM_DISPLAY_REGION()) == _HDR10_ON) ||
               (UserCommonColorHDRGetHDR10Status(GET_OSD_SYSTEM_DISPLAY_REGION()) == _HLG_ON))
#else
            if(UserCommonColorHDRGetHDR10Status(GET_OSD_SYSTEM_DISPLAY_REGION()) == _HDR10_ON)
#endif
            {
                return _FALSE;
            }
#endif
            if(GET_OSD_GLOBAL_DIMMING() == _ON)
            {
                return _FALSE;
            }

            break;

//-----------------------------------------------
        case _OSD_ADVANCE_ASPECT:
            if(OsdDisplayGetSelectRegFullStatus() == _TRUE)
            {
                return _FALSE;
            }
#if(_HW_DISPLAY_ROTATION_90_SUPPORT == _ON)
            if(GET_OSD_DISP_ROTATE() == _DISP_ROTATE_90)
            {
                return _FALSE;
            }
#endif
#if(_HW_DISPLAY_ROTATION_270_SUPPORT == _ON)
            if(GET_OSD_DISP_ROTATE() == _DISP_ROTATE_270)
            {
                return _FALSE;
            }
#endif
            break;

        case _OSD_ADVANCE_OVERSCAN:
            if(OsdDisplayGetSelectRegFullStatus() == _TRUE)
            {
                return _FALSE;
            }
            break;

        case _OSD_ADVANCE_OVERDRIVE:
            break;

        case _OSD_ADVANCE_DDCCI:
            break;

        case _OSD_ADVANCE_ULTRAVIVID:
#if(_HDR10_SUPPORT == _ON)
#if(_HLG_SUPPORT == _ON)
            if(((UserCommonColorHDRGetHDR10Status(GET_OSD_SYSTEM_DISPLAY_REGION()) == _HDR10_ON) ||
                (UserCommonColorHDRGetHDR10Status(GET_OSD_SYSTEM_DISPLAY_REGION()) == _HLG_ON)) &&
               (GET_OSD_REGION_HDR_SHARPNESS(GET_OSD_SELECT_REGION()) == _HDR10_SHARPNESSENHANCE_ON))
#else
            if((UserCommonColorHDRGetHDR10Status(GET_OSD_SYSTEM_DISPLAY_REGION()) == _HDR10_ON) &&
               (GET_OSD_REGION_HDR_SHARPNESS(GET_OSD_SELECT_REGION()) == _HDR10_SHARPNESSENHANCE_ON))
#endif
            {
                return _FALSE;
            }
#endif
#if(_DM_FUNCTION == _ON)
            if(GET_DVISION_PICTURE(GET_OSD_SYSTEM_DISPLAY_REGION()) == _OSD_DVISION_PICTURE_USER)
            {
                return _FALSE;
            }
#endif
            break;

        case _OSD_ADVANCE_DCR:
            if(GET_OSD_LOCAL_DIMMING() == _ON)
            {
                return _FALSE;
            }
#if(_HDR10_SUPPORT == _ON)
#if(_HLG_SUPPORT == _ON)
            if((UserCommonColorHDRGetHDR10Status(GET_OSD_SYSTEM_DISPLAY_REGION()) == _HDR10_ON) ||
               (UserCommonColorHDRGetHDR10Status(GET_OSD_SYSTEM_DISPLAY_REGION()) == _HLG_ON))
#else
            if(UserCommonColorHDRGetHDR10Status(GET_OSD_SYSTEM_DISPLAY_REGION()) == _HDR10_ON)
#endif
            {
                return _FALSE;
            }
#endif
            break;

        case _OSD_ADVANCE_DPOPTION:
            break;

        case _OSD_ADVANCE_DPMST:
            break;

        case _OSD_ADVANCE_DP_RESOLUTION:
            break;

        case _OSD_ADVANCE_CLONE:
            break;

        case _OSD_ADVANCE_FREESYNC:
            if(UserCommonDisplayGetFrameSyncSupport() == _FRAME_SYNC_SUPPORT_OFF)
            {
                return _FALSE;
            }
            break;

        case _OSD_ADVANCE_DP_ADAPTIVESYNC:
#if(_EAGLE_SIGHT_SUPPORT == _ON)
            if(SysRegionEagleSightTransDisplayMode(SysModeGetDisplayMode()) != _DISPLAY_MODE_1P)
#else
            if(SysModeGetDisplayMode() != _DISPLAY_MODE_1P)
#endif
            {
                return _FALSE;
            }
            break;

        case _OSD_ADVANCE_TYPEC_MODE:
            break;

        case _OSD_ADVANCE_DSC:
            break;

        case _OSD_ADVANCE_LOCALDIMMING:
#if(_ASPECT_RATIO_SUPPORT == _ON)
            if(GET_OSD_ASPECT_RATIO_TYPE(UserAdjustGetSelectRegionPort()) != _OSD_ASPECT_RATIO_FULL)
            {
                return _FALSE;
            }
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
            if(SysRegionEagleSightTransDisplayMode(SysModeGetDisplayMode()) != _DISPLAY_MODE_1P)
#else
            if(SysModeGetDisplayMode() != _DISPLAY_MODE_1P)
#endif
            {
                return _FALSE;
            }
            break;

        case _OSD_ADVANCE_LOCALDIMMING_USER:
            if(GET_OSD_LOCAL_DIMMING() != _ON)
            {
                return _FALSE;
            }
            break;
        case _OSD_ADVANCE_GLOBAL_DIMMING:
            break;

#if(_PIXEL_SHIFT_SUPPORT == _ON)
        case _OSD_ADVANCE_PIXELSHIFT:
            break;
#endif

        case _OSD_ADVANCE_HDMI_VERSIONS:
            break;

        case _OSD_ADVANCE_DUAL_DP_EDID:
            break;

#if(_SDR_TO_HDR_FUNCTION == _ON)
        case _OSD_ADVANCE_SDR_TO_HDR:
#if(_HDR10_SUPPORT == _ON)
#if(_HLG_SUPPORT == _ON)
            if((UserCommonColorHDRGetHDR10Status(GET_OSD_SYSTEM_DISPLAY_REGION()) == _HDR10_ON) ||
               (UserCommonColorHDRGetHDR10Status(GET_OSD_SYSTEM_DISPLAY_REGION()) == _HLG_ON))
#else
            if(UserCommonColorHDRGetHDR10Status(GET_OSD_SYSTEM_DISPLAY_REGION()) == _HDR10_ON)
#endif
            {
                return _FALSE;
            }
#endif
#if(_FREESYNC_II_SUPPORT == _ON)
            if(UserCommonColorHDRGetFreesynIIStatus(GET_OSD_SYSTEM_DISPLAY_REGION()) == _ON)
            {
                return _FALSE;
            }
#endif

            break;
#endif
#if(_DYNAMIC_LOWBLUE_FUNCTION == _ON)
        case _OSD_COLOR_EYE_PROTECT:
#if(_UNIFORMITY_FUNCTION == _ON)
            if(GET_OSD_PANEL_UNIFORMITY(GET_OSD_SYSTEM_DISPLAY_REGION()) == _ON)

            {
                return _FALSE;
            }
#endif
#if(_LOCAL_DIMMING_FUNCTION == _ON)
            if(UserCommonColorLocalDimmingGetEnableStatus() == _LOCAL_DIMMING_ENABLE)
            {
                return _FALSE;
            }
#endif
            break;
#endif
        case _OSD_ADVANCE_HUB_SWITCH:
            break;
        case _OSD_ADVANCE_EAGLE_SIGHT:
            if(SysModeGetDisplayMode() != _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT)
            {
                return _FALSE;
            }
#if(_EAGLE_SIGHT_SUPPORT == _ON)
            if(UserCommonDisplayGetEagleSightMainSubSync() != _EAGLE_SIGHT_MAIN_SUB_SYNC)
            {
                return _FALSE;
            }
#endif
            break;
        case _OSD_ADVANCE_MBR:
#if(_MOTION_BLUR_REDUCTION_OLED_SUPPORT == _ON)
            if(UserCommonDisplayMbrGetBlackFrameInsertAvailable() == _BFI_MODE_OFF)
            {
                return _FALSE;
            }
#endif
            break;
        case _OSD_ADVANCE_PANEL_REPLAY:
            // one of DP port set DP version 1.4
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
            if(GET_OSD_DP_D0_VERSION() >= _DP_VER_1_DOT_4)
            {
                return _TRUE;
            }
#endif
#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
            if(GET_OSD_DP_D1_VERSION() >= _DP_VER_1_DOT_4)
            {
                return _TRUE;
            }
#endif
#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
            if(GET_OSD_DP_D2_VERSION() >= _DP_VER_1_DOT_4)
            {
                return _TRUE;
            }
#endif
            return _FALSE;
            break;
#if(_SDR_PLUS_FUNCTION == _ON)
        case _OSD_ADVANCE_SDR_PLUS:
#if((_HDR10_SUPPORT == _ON) || (_HLG_SUPPORT == _ON))
            if(UserCommonColorHDRGetHDR10Status(GET_OSD_SYSTEM_DISPLAY_REGION()) != _HDR10_OFF)
            {
                return _FALSE;
            }
#endif

            if(UserCommonColorLocalContrastCheckStatus(GET_OSD_SYSTEM_SELECT_REGION()) == _OFF)
            {
                return _FALSE;
            }
            break;
        case _OSD_ADVANCE_SDR_PLUS_ADJ:
            if(GET_OSD_SDR_PLUS(GET_OSD_SELECT_REGION()) == _OFF)
            {
                return _FALSE;
            }
#if((_HDR10_SUPPORT == _ON) || (_HLG_SUPPORT == _ON))
            if(UserCommonColorHDRGetHDR10Status(GET_OSD_SYSTEM_DISPLAY_REGION()) != _HDR10_OFF)
            {
                return _FALSE;
            }
#endif
            break;
#endif

#if(_IMMERSIVE_NIGHT_SNIPER_FUNCTION == _ON)
        case _OSD_ADVANCE_NIGHT_SNIPER:
            if(UserCommonColorNightSniperCheckStatus(GET_OSD_SYSTEM_SELECT_REGION()) == _OFF)
            {
                return _FALSE;
            }

#if((_HDR10_SUPPORT == _ON) || (_HLG_SUPPORT == _ON))
            if(UserCommonColorHDRGetHDR10Status(GET_OSD_SYSTEM_DISPLAY_REGION()) != _HDR10_OFF)
            {
                return _FALSE;
            }
#endif
            break;
#endif
//-----------------------------------------------

        case _OSD_AUDIO_VOLUME:
            break;

        case _OSD_AUDIO_MUTE:
            break;

        case _OSD_AUDIO_STAND_ALONG:
            break;

        case _OSD_AUDIO_AUDIO_SOURCE:
#if(_AUDIO_SUPPORT == _OFF)
            return _FALSE;
#endif
            break;

#if(_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE)
        case _OSD_TTS_FUNCTION:
        case _OSD_TTS_TEXT_VOLUME:
        case _OSD_TTS_AUDIO_VOLUME:
            break;
#endif // End of #if(_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE)

        case _OSD_AUDIO_SOUND_MODE:
            break;

#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
        case _OSD_AUDIO_AUDIO_SELF_TEST:
            break;
#endif
//-----------------------------------------------
        case _OSD_OTHER_RESET:
            break;

        case _OSD_OTHER_MENU_TIME:
            break;

        case _OSD_OTHER_OSD_HPOS:
            break;

        case _OSD_OTHER_OSD_VPOS:
            break;

        case _OSD_OTHER_LANGUAGE:
            break;

        case _OSD_OTHER_TRNASPARENCY:
            break;

        case _OSD_OTHER_ROTATE:
            break;

        case _OSD_OTHER_CROSSHAIR:
            break;

        case _OSD_OTHER_BORDER_WIDTH:
        case _OSD_OTHER_BORDER_COLOR:
            if(GET_OSD_DISPLAY_MODE() == _OSD_DM_1P)
            {
                return _FALSE;
            }
            break;
//-----------------------------------------------
#if(_HDR10_SUPPORT == _ON)
        case _OSD_HDR_MODE:
            // HDR Not support 2P_Full region
            if(OsdFuncHdrRegionCheck() == _FALSE)
            {
                return _FALSE;
            }
            break;
#endif

#if(_HDR10_SUPPORT == _ON)
        case _OSD_HDR_DARK_ENHANCE:
            if(UserCommonColorHDRGetHDR10Status(GET_OSD_SYSTEM_DISPLAY_REGION()) != _HDR10_ON)
            {
                return _FALSE;
            }
            break;
#endif

#if(_HDR10_SUPPORT == _ON)
        case _OSD_HDR_SHARP_ENHANCE:
        case _OSD_HDR_CONTRAST:
#if(_HLG_SUPPORT == _ON)
            if((UserCommonColorHDRGetHDR10Status(GET_OSD_SYSTEM_DISPLAY_REGION()) != _HDR10_ON) &&
               (UserCommonColorHDRGetHDR10Status(GET_OSD_SYSTEM_DISPLAY_REGION()) != _HLG_ON))
#else
            if(UserCommonColorHDRGetHDR10Status(GET_OSD_SYSTEM_DISPLAY_REGION()) != _HDR10_ON)
#endif
            {
                return _FALSE;
            }
            break;
#endif

#if(_HDR10_SUPPORT == _ON)
        case _OSD_HDR_COLOR_ENHANCE:
            if(UserCommonColorHDRGetHDR10Status(GET_OSD_SYSTEM_DISPLAY_REGION()) != _HDR10_ON)
            {
                return _FALSE;
            }
            break;
#endif

#if(_HDR10_SUPPORT == _ON)
        case _OSD_HDR_LIGHT_ENHANCE:
            if(UserCommonColorHDRGetHDR10Status(GET_OSD_SYSTEM_DISPLAY_REGION()) != _HDR10_ON)
            {
                return _FALSE;
            }
            break;
#endif

        case _OSD_HDR_HLG_OOTF:
#if(_HLG_SUPPORT == _ON)
            if(UserCommonColorHDRGetHDR10Status(GET_OSD_SYSTEM_DISPLAY_REGION()) != _HLG_ON)
            {
                return _FALSE;
            }
#endif
            break;
//-----------------------------------------------
        case _OSD_SOURCE_1P:
            break;

        case _OSD_SOURCE_2P:
#if(_2P_DISPLAY_SUPPORT == _ON)
            if(GET_OSD_DISPLAY_MODE() == _OSD_DM_1P)
            {
                return _FALSE;
            }

#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
            if(GET_OSD_PXP_MST() == _ON_FIXED_MODE)
            {
                return _FALSE;
            }
#endif
#else
            return _FALSE;
#endif
            break;

        case _OSD_SOURCE_3P:
#if((_4P_DISPLAY_SUPPORT == _ON) || (_3P_FLAG_DISPLAY_SUPPORT == _ON) || (_3P_SKEW_LR_DISPLAY_SUPPORT == _ON) || (_3P_SKEW_TB_DISPLAY_SUPPORT == _ON))
            if(GET_OSD_DISPLAY_MODE() < _OSD_DM_3P_FLAG)
            {
                return _FALSE;
            }
#else
            return _FALSE;
#endif
            break;

        case _OSD_SOURCE_4P:
#if(_4P_DISPLAY_SUPPORT == _ON)
            if(GET_OSD_DISPLAY_MODE() != _OSD_DM_4P)
            {
                return _FALSE;
            }
#else
            return _FALSE;
#endif
            break;

        case _OSD_EXIT_HOTKEY:
            break;
#if(_LOCAL_CONTRAST_FUNCTION == _ON)
        case _OSD_ADVANCE_LOCAL_CONTRAST:
            if(UserCommonColorLocalContrastCheckStatus(GET_OSD_SYSTEM_SELECT_REGION()) == _OFF)
            {
                return _FALSE;
            }
            break;
        case _OSD_ADVANCE_LOCAL_CONTRAST_USER:

            if(GET_OSD_LOCAL_CONTRAST(GET_OSD_SELECT_REGION()) <= _LOCAL_CONTRAST_H)
            {
                return _FALSE;
            }
            break;
#endif
#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
        case _OSD_MUTIP_PXP_MST:
            if((GET_OSD_DISPLAY_MODE() == _OSD_DM_2P_LR) ||
               (GET_OSD_DISPLAY_MODE() == _OSD_DM_2P_PIP) ||
               (GET_OSD_DISPLAY_MODE() == _OSD_DM_2P_TB))
            {
                return _TRUE;
            }
            return _FALSE;
#endif
//-----------------------------------------------
#if(_DM_FUNCTION == _ON)
        case _OSD_DVISION:
            // DVision Not support 2P_Full region
            if(OsdFuncHdrRegionCheck() == _FALSE)
            {
                return _FALSE;
            }
            break;
        case _OSD_DVISION_PICTURE:
        case _OSD_DVISION_BACKLIGHT:
        case _OSD_DVISION_BRIGHTNESS:
        case _OSD_DVISION_CONTRAST:
        case _OSD_DVISION_SATURATION:
        case _OSD_DVISION_RESET:
        case _OSD_DVISION_NOTIFICATION:
            // DVision Not support 2P_Full region
            if(OsdFuncHdrRegionCheck() == _FALSE)
            {
                return _FALSE;
            }
            if(GET_OSD_DVISION(SysRegionGetInputPort(GET_OSD_SYSTEM_DISPLAY_REGION())) == _OFF)
            {
                return _FALSE;
            }
            break;
#endif

#if(_AUDIO_ARC_SUPPORT == _ON)
        case _OSD_AUDIO_ARC_OUTPUT:
        case _OSD_AUDIO_ARC_INPUTPORT:
        case _OSD_AUDIO_ARC_MODE:
        case _OSD_AUDIO_ARC_MUTE:
        case _OSD_AUDIO_ARC_CHANEL:
            break;
#endif

#if(_USB2_HOST_EHCI_MASS_STORGE_PROGRAM_SUPPORT == _ON)
        case _OSD_ADVANCE_FW_UPDATE:
            // update FW anytime
            break;
#endif

#if(_ANTI_ALIASING_FUNCTION == _ON)
        case _OSD_ADVANCE_ANTI_ALIASING:
            if(UserCommonColorGetAntiAliasingSupport(GET_OSD_SYSTEM_SELECT_REGION()) == _FALSE)
            {
                return _FALSE;
            }
            break;
#endif
        case _OSD_ADVANCE_ENERGY_SAVE:
#if(_LOCAL_DIMMING_ENERGY_SAVE_MODE_SUPPORT == _OFF)
            return _FALSE;
#endif
            break;
//-----------------------------------------------
//==>STEP 3 // Update Item selected Conditions

        default:
            return _FALSE;
            break;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : 1st Menu Enter 2nd Menu
// Input Value  : OSD Select index & current OSD State
// Output Value :
//--------------------------------------------------
void OsdDisp2ndMenuEnter(BYTE ucIndex, WORD usOsdState)
{
    WORD usTempState = usOsdState;
    SET_OSD_STATE_PREVIOUS(usOsdState);

    switch(usOsdState)
    {
        case _MENU_PICTURE_ITEM:
            if(ucIndex < _OSD_PICTURE_ITEM_AMOUNT)
            {
                usTempState = tOSD_PICTURE_ITEM_PRI[ucIndex];
            }
            break;

        case _MENU_DISPLAY_ITEM:
            if(ucIndex < _OSD_DISPLAY_ITEM_AMOUNT)
            {
                usTempState = tOSD_DISPLAY_ITEM_PRI[ucIndex];
            }
            break;

        case _MENU_COLOR_ITEM:
            if(ucIndex < _OSD_COLOR_ITEM_AMOUNT)
            {
                usTempState = tOSD_COLOR_ITEM_PRI[ucIndex];
            }
            break;

        case _MENU_ADVANCE_ITEM:
            if(ucIndex < _OSD_ADVANCE_ITEM_AMOUNT)
            {
                switch(tOSD_ADVANCE_ITEM_PRI[ucIndex])
                {
                    case _OSD_ADVANCE_ASPECT:
                    case _OSD_ADVANCE_OVERSCAN:
                        switch(GET_OSD_DISPLAY_MODE())
                        {
                            case _OSD_DM_2P_LR:
                                if(GET_OSD_SELECT_REGION() == _OSD_SR_2P_LR_FULL)
                                {
                                    return;
                                }
                                break;
                            case _OSD_DM_2P_TB:
                                if(GET_OSD_SELECT_REGION() == _OSD_SR_2P_TB_FULL)
                                {
                                    return;
                                }
                                break;
                            case _OSD_DM_2P_PIP:
                                if(GET_OSD_SELECT_REGION() == _OSD_SR_2P_PIP_FULL)
                                {
                                    return;
                                }
                                break;
                            case _OSD_DM_4P:
                                switch(GET_OSD_SELECT_REGION())
                                {
                                    case _OSD_SR_4P_LT_INSIDE:
                                    case _OSD_SR_4P_LB_INSIDE:
                                    case _OSD_SR_4P_RT_INSIDE:
                                    case _OSD_SR_4P_RB_INSIDE:
                                        break;
                                    default:
                                        return;
                                }
                                break;
                            case _OSD_DM_3P_FLAG:
                                switch(GET_OSD_SELECT_REGION())
                                {
                                    case _OSD_SR_3P_FLAG_MAIN:
                                    case _OSD_SR_3P_FLAG_L:
                                    case _OSD_SR_3P_FLAG_R:
                                        break;
                                    default:
                                        return;
                                }
                                break;
                            case _OSD_DM_3P_SKEW_L:
                                switch(GET_OSD_SELECT_REGION())
                                {
                                    case _OSD_SR_3P_SKEW_L_MAIN:
                                    case _OSD_SR_3P_SKEW_L_UP:
                                    case _OSD_SR_3P_SKEW_L_DOWN:
                                        break;
                                    default:
                                        return;
                                }
                                break;
                            case _OSD_DM_3P_SKEW_R:
                                switch(GET_OSD_SELECT_REGION())
                                {
                                    case _OSD_SR_3P_SKEW_R_MAIN:
                                    case _OSD_SR_3P_SKEW_R_UP:
                                    case _OSD_SR_3P_SKEW_R_DOWN:
                                        break;
                                    default:
                                        return;
                                }
                                break;
                            case _OSD_DM_3P_SKEW_T:
                                switch(GET_OSD_SELECT_REGION())
                                {
                                    case _OSD_SR_3P_SKEW_T_MAIN:
                                    case _OSD_SR_3P_SKEW_T_LEFT:
                                    case _OSD_SR_3P_SKEW_T_RIGHT:
                                        break;
                                    default:
                                        return;
                                }
                                break;
                            case _OSD_DM_3P_SKEW_B:
                                switch(GET_OSD_SELECT_REGION())
                                {
                                    case _OSD_SR_3P_SKEW_B_MAIN:
                                    case _OSD_SR_3P_SKEW_B_LEFT:
                                    case _OSD_SR_3P_SKEW_B_RIGHT:
                                        break;
                                    default:
                                        return;
                                }
                                break;
                            default:
                                break;
                        }
                        break;
                    default:
                        break;
                }

                usTempState = tOSD_ADVANCE_ITEM_PRI[ucIndex];
            }
            break;

        case _MENU_AUDIO_ITEM:
            if(ucIndex < _OSD_AUDIO_ITEM_AMOUNT)
            {
                usTempState = tOSD_AUDIO_ITEM_PRI[ucIndex];
            }
            break;

        case _MENU_OTHER_ITEM:
            if(ucIndex < _OSD_OTHER_ITEM_AMOUNT)
            {
                usTempState = tOSD_OTHER_ITEM_PRI[ucIndex];
            }
            break;

        case _MENU_MUTIP_ITEM:
            if(ucIndex < _OSD_MUTIP_ITEM_AMOUNT)
            {
                usTempState = tOSD_MUTIP_ITEM_PRI[ucIndex];
            }
            break;

        case _MENU_HDR_ITEM:
            if(ucIndex < _OSD_HDR_ITEM_AMOUNT)
            {
                usTempState = tOSD_HDR_ITEM_PRI[ucIndex];
            }
            break;
        case _MENU_QUICKLINK_ITEM:
            if(ucIndex < _OSD_QUICK_ITEM_AMOUNT)
            {
                usTempState = tOSD_QUICK_ITEM_PRI[ucIndex];
            }
            break;
        case _MENU_INPUT_ITEM:
            if(ucIndex < _OSD_INPUT_ITEM_AMOUNT)
            {
                usTempState = tOSD_INPUT_ITEM_PRI[ucIndex];
            }
            break;
#if(_DM_FUNCTION == _ON)
        case _MENU_DVISION_ITEM:
            if(ucIndex < _OSD_DVISION_ITEM_AMOUNT)
            {
                usTempState = tOSD_DVISION_ITEM_PRI[ucIndex];
            }
            break;
#endif

#if(_AUDIO_ARC_SUPPORT == _ON)
        case _MENU_AUDIO_ARC_EARC_ITEM:
            if(ucIndex < _OSD_AUDIO_ARC_ITEM_AMOUNT)
            {
                usTempState = tOSD_AUDIO_ARC_ITEM_PRI[ucIndex];
            }
            break;
#endif
        default:
            break;
    }

    switch(usTempState)
    {
        case _OSD_MUTIP_INPUT_SWAP:
#if(_DM_FUNCTION == _OFF)
            OsdDisp4thMenuInFoBlock(_STRING_PLEASE_WAIT);
#endif
            if((GET_OSD_DISPLAY_MODE() == _OSD_DM_2P_LR) ||
               (GET_OSD_DISPLAY_MODE() == _OSD_DM_2P_TB) ||
               (GET_OSD_DISPLAY_MODE() == _OSD_DM_2P_PIP))
            {
                g_usBackupValue = GET_OSD_1P_INPUT_SOURCE();
                SET_OSD_1P_INPUT_SOURCE(GET_OSD_2P_INPUT_SOURCE());
                SET_OSD_2P_INPUT_SOURCE(g_usBackupValue);
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_DISPLAYMODEDATA_MSG);

#if(_2P_DISPLAY_SUPPORT == _ON)
                UserAdjustSwapInputPort();
#endif
            }
#if(_DM_FUNCTION == _OFF)
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_MUTIP_INPUT_SWAP), _LOW);
#endif
            break;

        case _OSD_COLOR_GAMMA:
        case _OSD_COLOR_PCM:
        case _OSD_ADVANCE_LOCALDIMMING:
        case _OSD_HDR_MODE:
        case _OSD_ADVANCE_SDR_TO_HDR:
#if(_UNIFORMITY_FUNCTION == _ON)
            if(GET_OSD_PANEL_UNIFORMITY(GET_OSD_SELECT_REGION()) == _ON)
            {
                if(usTempState == _OSD_COLOR_GAMMA)
                {
                    g_usBackupValue = _FROM_STATE_GAMMA;
                }
                else if(usTempState == _OSD_COLOR_PCM)
                {
                    g_usBackupValue = _FROM_STATE_PCM;
                }
                else if(usTempState == _OSD_ADVANCE_LOCALDIMMING)
                {
                    g_usBackupValue = _FROM_STATE_LD;
                }
                else if(usTempState == _OSD_HDR_MODE)
                {
                    g_usBackupValue = _FROM_STATE_HDR;
                }
                else if(usTempState == _OSD_ADVANCE_SDR_TO_HDR)
                {
                    g_usBackupValue = _FROM_STATE_SDRTOHDR;
                }
                g_usAdjustValue = GET_OSD_PANEL_UNIFORMITY(GET_OSD_SELECT_REGION());
                OsdDispOsdMessage(_OSD_DISP_PANEL_UNIFORMITY_ONOFF_MSG);
                OsdWindowDrawingByFontHighlight(_OSD_WIN_HIGHLIGHT_1, ROW(2), COL(27), WIDTH(6), HEIGHT(4), _CP_LIGHTBLUE, _CP_ORANGE, _CP_BG);
                SET_OSD_STATE(_MENU_PANEL_UNIFORMITY_MSG_ADJUST);
            }
            else
#endif
            {
                OsdMenu3rdFrame();
                OsdDispItemValueUpdate(usTempState);
                g_usBackupValue = g_stOsdItemData.usAdjValue;
                SET_OSD_STATE(g_stOsdItemData.usSubOsdState);
                OsdDisp3rdItemAdj(usTempState, _OFF);
            }
            break;

        case _OSD_OTHER_RESET:
            // show wait
            OsdPropPutString(ROW(_MENU_3RD_ITEM_ROW_ST + 2), COL(_MENU_3RD_ITEM_LIST_ST), _PFONT_PAGE_2, _STRING_PLEASE_WAIT, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
            OsdDispOsdReset();
            OsdPropPutString(ROW(_MENU_3RD_ITEM_ROW_ST + 2), COL(_MENU_3RD_ITEM_LIST_ST), _PFONT_PAGE_2, _STRING_PASS, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
            break;

        case _OSD_DISPLAY_AUTO:
#if(_VGA_SUPPORT == _ON)
            if((SysVgaGetRegion() != _DISPLAY_RGN_NONE) &&
               (SysRegionGetDisplayState(SysVgaGetRegion()) == _DISPLAY_STATE_ACTIVE))
            {
                OsdMenu3rdFrame();
                OsdDisp4thMenuInFoBlock(_STRING_PLEASE_WAIT);
                g_usAdjustValue = 0;
                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _SELECT);
                UserCommonVgaAutoConfig();
                OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_DISPLAY_AUTO), _LOW);
            }
            if(g_usAdjustValue != 100)
            {
                OsdPropPutString(ROW(_MENU_2ND_ITEM_ROW_ST + ucIndex * 2), COL(_MENU_2ND_ITEM_VAL_COL_ST), _PFONT_PAGE_2, _STRING_FAIL, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
            }
            else
            {
                OsdPropPutString(ROW(_MENU_2ND_ITEM_ROW_ST + ucIndex * 2), COL(_MENU_2ND_ITEM_VAL_COL_ST), _PFONT_PAGE_2, _STRING_PASS, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
            }
#endif
            break;

#if(_VGA_SUPPORT == _ON)
        case _OSD_AUTO_COLOR:

            if((SysVgaGetRegion() != _DISPLAY_RGN_NONE) &&
               (SysRegionGetDisplayState(SysVgaGetRegion()) == _DISPLAY_STATE_ACTIVE))
            {
                OsdPropPutString(ROW(_MENU_2ND_ITEM_ROW_ST + ucIndex * 2), COL(_MENU_2ND_ITEM_VAL_COL_ST), _PFONT_PAGE_2, _STRING_PLEASE_WAIT, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
                if(GET_OSD_FACTORY_AUTO_COLOR_TYPE() == _AUTO_COLOR_TYPE_INTERNAL)
                {
                    g_usAdjustValue = _AUTO_CALIBRATE_RGB;
                }
                else
                {
                    g_usAdjustValue = _AUTO_TUNE_RGB;
                }

                if(UserCommonVgaAutoDoWhiteBalance(g_usAdjustValue) == _AUTO_SUCCESS)
                {
                    OsdFuncClearOsd(ROW(_MENU_2ND_ITEM_ROW_ST + ucIndex * 2), COL(_MENU_2ND_ITEM_VAL_COL_ST), WIDTH(10), HEIGHT(1));
                    OsdPropPutString(ROW(_MENU_2ND_ITEM_ROW_ST + ucIndex * 2), COL(_MENU_2ND_ITEM_VAL_COL_ST), _PFONT_PAGE_2, _STRING_PASS, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
                    UserCommonVgaAutoGetAutoColorResult(&g_stVgaAdcData);
                    UserCommonNVRamSaveADCSetting(_COLOR_SPACE_RGB);
                }
                else
                {
                    OsdFuncClearOsd(ROW(_MENU_2ND_ITEM_ROW_ST + ucIndex * 2), COL(_MENU_2ND_ITEM_VAL_COL_ST), WIDTH(10), HEIGHT(1));
                    OsdPropPutString(ROW(_MENU_2ND_ITEM_ROW_ST + ucIndex * 2), COL(_MENU_2ND_ITEM_VAL_COL_ST), _PFONT_PAGE_2, _STRING_FAIL, COLOR(_CP_WHITE, _CP_BG), GET_OSD_LANGUAGE());
                    UserCommonNVRamRestoreADCSetting();
                }
            }

            break;
#endif
#if(_DM_FUNCTION == _ON)
        case _OSD_DVISION_RESET:
            RTDNVRamRestoreOsdDVisionModeData();
            OsdDisp2ndMenuReDraw(_MENU_DVISION_ITEM, _HIGH);
#if(_IS_MAIN_PROCESS_CPU == _TRUE)
            UserCommonColorDMOSDAdjust(GET_OSD_SYSTEM_SELECT_REGION(), _DM_ADJUST_DM_AND_COLOR);
#endif
            break;
#endif
        case _OSD_COLOR_TEMP_USER:
            RTDNVRamLoadColorSetting(GET_OSD_SELECT_REGION());
            OsdMenu3rdFrame();
            OsdDispItemValueUpdate(usTempState);
            g_usBackupValue = g_stOsdItemData.usAdjValue;
            SET_OSD_STATE(g_stOsdItemData.usSubOsdState);
            OsdDisp3rdItemAdj(usTempState, _OFF);
            break;
        //==>STEP 8 //Check Item if it need special process

        default:
            OsdMenu3rdFrame();
            OsdDispItemValueUpdate(usTempState);
            g_usBackupValue = g_stOsdItemData.usAdjValue;
            SET_OSD_STATE(g_stOsdItemData.usSubOsdState);
            OsdDisp3rdItemAdj(usTempState, _OFF);
            break;
    }
}

//--------------------------------------------------
// Description    :
// Input Value    :
// Output Value :
//--------------------------------------------------
bit OsdDisp2ndMutiPSelectbyKey(void)
{
    BYTE ucBackup = GET_OSD_ITEM_INDEX();
    do
    {
        if(GET_KEYMESSAGE() == _RIGHT_KEY_MESSAGE)
        {
            if(GET_OSD_ITEM_INDEX() >= (_OSD_MUTIP_ITEM_AMOUNT - 1))
            {
                SET_OSD_ITEM_INDEX(ucBackup);
                return _FALSE;
            }

            SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() + 1);
        }
        if(GET_KEYMESSAGE() == _LEFT_KEY_MESSAGE)
        {
            if(GET_OSD_ITEM_INDEX() == 0)
            {
                SET_OSD_ITEM_INDEX(ucBackup);
                return _FALSE;
            }

            SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() - 1);
        }

        if(GET_OSD_ITEM_INDEX() >= _OSD_MUTIP_ITEM_AMOUNT)
        {
            SET_OSD_ITEM_INDEX(ucBackup);
            return _FALSE;
        }
    }
    while (OsdDisp2ndMenuCheck(tOSD_MUTIP_ITEM_PRI[GET_OSD_ITEM_INDEX()]) == _FALSE);

    if(ucBackup == GET_OSD_ITEM_INDEX())
    {
        return _FALSE;
    }

    if(GET_KEYMESSAGE() == _RIGHT_KEY_MESSAGE)
    {
        if(((ucBackup % _MENU_2ND_ITEM_MAX) + (GET_OSD_ITEM_INDEX() - ucBackup)) >= _MENU_2ND_ITEM_MAX)
        {
            OsdDisp2ndMenuStringSwitch(_OSD_MENU_MUTIP);
        }
    }
    if(GET_KEYMESSAGE() == _LEFT_KEY_MESSAGE)
    {
        if((ucBackup >= _MENU_2ND_ITEM_MAX) &&
           ((ucBackup % _MENU_2ND_ITEM_MAX) < (ucBackup - GET_OSD_ITEM_INDEX())))
        {
            OsdDisp2ndMenuStringSwitch(_OSD_MENU_MUTIP);
        }
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
bit OsdDisp2ndPictureSelectbyKey(void)
{
    BYTE ucBackup = GET_OSD_ITEM_INDEX();
    do
    {
        if(GET_KEYMESSAGE() == _RIGHT_KEY_MESSAGE)
        {
            if(GET_OSD_ITEM_INDEX() >= (_OSD_PICTURE_ITEM_AMOUNT - 1))
            {
                SET_OSD_ITEM_INDEX(ucBackup);
                return _FALSE;
            }

            SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() + 1);
        }
        if(GET_KEYMESSAGE() == _LEFT_KEY_MESSAGE)
        {
            if(GET_OSD_ITEM_INDEX() == 0)
            {
                SET_OSD_ITEM_INDEX(ucBackup);
                return _FALSE;
            }

            SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() - 1);
        }

        if(GET_OSD_ITEM_INDEX() >= _OSD_PICTURE_ITEM_AMOUNT)
        {
            SET_OSD_ITEM_INDEX(ucBackup);
            return _FALSE;
        }
    }
    while ((OsdDisp2ndMenuCheck(tOSD_PICTURE_ITEM_PRI[GET_OSD_ITEM_INDEX()])) == _FALSE);

    if(ucBackup == GET_OSD_ITEM_INDEX())
    {
        return _FALSE;
    }

    if(GET_KEYMESSAGE() == _RIGHT_KEY_MESSAGE)
    {
        if(((ucBackup % _MENU_2ND_ITEM_MAX) + (GET_OSD_ITEM_INDEX() - ucBackup)) >= _MENU_2ND_ITEM_MAX)
        {
            OsdDisp2ndMenuStringSwitch(_OSD_MENU_PICTURE);
        }
    }

    if(GET_KEYMESSAGE() == _LEFT_KEY_MESSAGE)
    {
        if((ucBackup >= _MENU_2ND_ITEM_MAX) &&
           ((ucBackup % _MENU_2ND_ITEM_MAX) < (ucBackup - GET_OSD_ITEM_INDEX())))
        {
            OsdDisp2ndMenuStringSwitch(_OSD_MENU_PICTURE);
        }
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
bit OsdDisp2ndDisplaySelectbyKey(void)
{
    BYTE ucBackup = GET_OSD_ITEM_INDEX();
    do
    {
        if(GET_KEYMESSAGE() == _RIGHT_KEY_MESSAGE)
        {
            if(GET_OSD_ITEM_INDEX() >= (_OSD_DISPLAY_ITEM_AMOUNT - 1))
            {
                SET_OSD_ITEM_INDEX(ucBackup);
                return _FALSE;
            }

            SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() + 1);
        }
        if(GET_KEYMESSAGE() == _LEFT_KEY_MESSAGE)
        {
            if(GET_OSD_ITEM_INDEX() == 0)
            {
                SET_OSD_ITEM_INDEX(ucBackup);
                return _FALSE;
            }

            SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() - 1);
        }

        if(GET_OSD_ITEM_INDEX() >= _OSD_DISPLAY_ITEM_AMOUNT)
        {
            SET_OSD_ITEM_INDEX(ucBackup);
            return _FALSE;
        }
    }
    while ((OsdDisp2ndMenuCheck(tOSD_DISPLAY_ITEM_PRI[GET_OSD_ITEM_INDEX()])) == _FALSE);

    if(ucBackup == GET_OSD_ITEM_INDEX())
    {
        return _FALSE;
    }

    if(GET_KEYMESSAGE() == _RIGHT_KEY_MESSAGE)
    {
        if(((ucBackup % _MENU_2ND_ITEM_MAX) + (GET_OSD_ITEM_INDEX() - ucBackup)) >= _MENU_2ND_ITEM_MAX)
        {
            OsdDisp2ndMenuStringSwitch(_OSD_MENU_DISPLAY);
        }
    }

    if(GET_KEYMESSAGE() == _LEFT_KEY_MESSAGE)
    {
        if((ucBackup >= _MENU_2ND_ITEM_MAX) &&
           ((ucBackup % _MENU_2ND_ITEM_MAX) < (ucBackup - GET_OSD_ITEM_INDEX())))
        {
            OsdDisp2ndMenuStringSwitch(_OSD_MENU_DISPLAY);
        }
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
bit OsdDisp2ndColorSelectbyKey(void)
{
    BYTE ucBackup = GET_OSD_ITEM_INDEX();
    do
    {
        if(GET_KEYMESSAGE() == _RIGHT_KEY_MESSAGE)
        {
            if(GET_OSD_ITEM_INDEX() >= (_OSD_COLOR_ITEM_AMOUNT - 1))
            {
                SET_OSD_ITEM_INDEX(ucBackup);
                return _FALSE;
            }

            SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() + 1);
        }

        if(GET_KEYMESSAGE() == _LEFT_KEY_MESSAGE)
        {
            if(GET_OSD_ITEM_INDEX() == 0)
            {
                SET_OSD_ITEM_INDEX(ucBackup);
                return _FALSE;
            }

            SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() - 1);
        }

        if(GET_OSD_ITEM_INDEX() >= _OSD_COLOR_ITEM_AMOUNT)
        {
            SET_OSD_ITEM_INDEX(ucBackup);
            return _FALSE;
        }
    }
    while (OsdDisp2ndMenuCheck(tOSD_COLOR_ITEM_PRI[GET_OSD_ITEM_INDEX()]) == _FALSE);

    if(ucBackup == GET_OSD_ITEM_INDEX())
    {
        return _FALSE;
    }

    if(GET_KEYMESSAGE() == _RIGHT_KEY_MESSAGE)
    {
        if(((ucBackup % _MENU_2ND_ITEM_MAX) + (GET_OSD_ITEM_INDEX() - ucBackup)) >= _MENU_2ND_ITEM_MAX)
        {
            OsdDisp2ndMenuStringSwitch(_OSD_MENU_COLOR);
        }
    }
    if(GET_KEYMESSAGE() == _LEFT_KEY_MESSAGE)
    {
        if((ucBackup >= _MENU_2ND_ITEM_MAX) &&
           ((ucBackup % _MENU_2ND_ITEM_MAX) < (ucBackup - GET_OSD_ITEM_INDEX())))
        {
            OsdDisp2ndMenuStringSwitch(_OSD_MENU_COLOR);
        }
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
bit OsdDisp2ndAdvanceSelectbyKey(void)
{
    BYTE ucBackup = GET_OSD_ITEM_INDEX();
    do
    {
        if(GET_KEYMESSAGE() == _RIGHT_KEY_MESSAGE)
        {
            if(GET_OSD_ITEM_INDEX() >= (_OSD_ADVANCE_ITEM_AMOUNT - 1))
            {
                SET_OSD_ITEM_INDEX(ucBackup);
                return _FALSE;
            }

            SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() + 1);
        }
        if(GET_KEYMESSAGE() == _LEFT_KEY_MESSAGE)
        {
            if(GET_OSD_ITEM_INDEX() == 0)
            {
                SET_OSD_ITEM_INDEX(ucBackup);
                return _FALSE;
            }

            SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() - 1);
        }

        if(GET_OSD_ITEM_INDEX() >= _OSD_ADVANCE_ITEM_AMOUNT)
        {
            SET_OSD_ITEM_INDEX(ucBackup);
            return _FALSE;
        }
    }
    while (OsdDisp2ndMenuCheck(tOSD_ADVANCE_ITEM_PRI[GET_OSD_ITEM_INDEX()]) == _FALSE);

    if(ucBackup == GET_OSD_ITEM_INDEX())
    {
        return _FALSE;
    }

    if(GET_KEYMESSAGE() == _RIGHT_KEY_MESSAGE)
    {
        if(((ucBackup % _MENU_2ND_ITEM_MAX) + (GET_OSD_ITEM_INDEX() - ucBackup)) >= _MENU_2ND_ITEM_MAX)
        {
            OsdDisp2ndMenuStringSwitch(_OSD_MENU_ADVANCE);
        }
    }
    if(GET_KEYMESSAGE() == _LEFT_KEY_MESSAGE)
    {
        if((ucBackup >= _MENU_2ND_ITEM_MAX) &&
           ((ucBackup % _MENU_2ND_ITEM_MAX) < (ucBackup - GET_OSD_ITEM_INDEX())))
        {
            OsdDisp2ndMenuStringSwitch(_OSD_MENU_ADVANCE);
        }
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
bit OsdDisp2ndAudioSelectbyKey(void)
{
    BYTE ucBackup = GET_OSD_ITEM_INDEX();
    do
    {
        if(GET_KEYMESSAGE() == _RIGHT_KEY_MESSAGE)
        {
            if(GET_OSD_ITEM_INDEX() >= (_OSD_AUDIO_ITEM_AMOUNT - 1))
            {
                SET_OSD_ITEM_INDEX(ucBackup);
                return _FALSE;
            }

            SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() + 1);
        }
        if(GET_KEYMESSAGE() == _LEFT_KEY_MESSAGE)
        {
            if(GET_OSD_ITEM_INDEX() == 0)
            {
                SET_OSD_ITEM_INDEX(ucBackup);
                return _FALSE;
            }

            SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() - 1);
        }

        if(GET_OSD_ITEM_INDEX() >= _OSD_AUDIO_ITEM_AMOUNT)
        {
            SET_OSD_ITEM_INDEX(ucBackup);
            return _FALSE;
        }
    }
    while (OsdDisp2ndMenuCheck(tOSD_AUDIO_ITEM_PRI[GET_OSD_ITEM_INDEX()]) == _FALSE);

    if(ucBackup == GET_OSD_ITEM_INDEX())
    {
        return _FALSE;
    }

    if(GET_KEYMESSAGE() == _RIGHT_KEY_MESSAGE)
    {
        if(((ucBackup % _MENU_2ND_ITEM_MAX) + (GET_OSD_ITEM_INDEX() - ucBackup)) >= _MENU_2ND_ITEM_MAX)
        {
            OsdDisp2ndMenuStringSwitch(_OSD_MENU_AUDIO);
        }
    }

    if(GET_KEYMESSAGE() == _LEFT_KEY_MESSAGE)
    {
        if((ucBackup >= _MENU_2ND_ITEM_MAX) &&
           ((ucBackup % _MENU_2ND_ITEM_MAX) < (ucBackup - GET_OSD_ITEM_INDEX())))
        {
            OsdDisp2ndMenuStringSwitch(_OSD_MENU_AUDIO);
        }
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
bit OsdDisp2ndOtherSelectbyKey(void)
{
    BYTE ucBackup = GET_OSD_ITEM_INDEX();
    do
    {
        if(GET_KEYMESSAGE() == _RIGHT_KEY_MESSAGE)
        {
            if(GET_OSD_ITEM_INDEX() >= (_OSD_OTHER_ITEM_AMOUNT - 1))
            {
                SET_OSD_ITEM_INDEX(ucBackup);
                return _FALSE;
            }

            SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() + 1);
        }

        if(GET_KEYMESSAGE() == _LEFT_KEY_MESSAGE)
        {
            if(GET_OSD_ITEM_INDEX() == 0)
            {
                SET_OSD_ITEM_INDEX(ucBackup);
                return _FALSE;
            }

            SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() - 1);
        }

        if(GET_OSD_ITEM_INDEX() >= _OSD_OTHER_ITEM_AMOUNT)
        {
            SET_OSD_ITEM_INDEX(ucBackup);
            return _FALSE;
        }
    }
    while (OsdDisp2ndMenuCheck(tOSD_OTHER_ITEM_PRI[GET_OSD_ITEM_INDEX()]) == _FALSE);

    if(ucBackup == GET_OSD_ITEM_INDEX())
    {
        return _FALSE;
    }

    if(GET_KEYMESSAGE() == _RIGHT_KEY_MESSAGE)
    {
        if(((ucBackup % _MENU_2ND_ITEM_MAX) + (GET_OSD_ITEM_INDEX() - ucBackup)) >= _MENU_2ND_ITEM_MAX)
        {
            OsdDisp2ndMenuStringSwitch(_OSD_MENU_OTHER);
        }
    }

    if(GET_KEYMESSAGE() == _LEFT_KEY_MESSAGE)
    {
        if((ucBackup >= _MENU_2ND_ITEM_MAX) &&
           ((ucBackup % _MENU_2ND_ITEM_MAX) < (ucBackup - GET_OSD_ITEM_INDEX())))
        {
            OsdDisp2ndMenuStringSwitch(_OSD_MENU_OTHER);
        }
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
bit OsdDisp2ndHdrSelectbyKey(void)
{
    BYTE ucBackup = GET_OSD_ITEM_INDEX();
    do
    {
        if(GET_KEYMESSAGE() == _RIGHT_KEY_MESSAGE)
        {
            if(GET_OSD_ITEM_INDEX() >= (_OSD_HDR_ITEM_AMOUNT - 1))
            {
                SET_OSD_ITEM_INDEX(ucBackup);
                return _FALSE;
            }

            SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() + 1);
        }

        if(GET_KEYMESSAGE() == _LEFT_KEY_MESSAGE)
        {
            if(GET_OSD_ITEM_INDEX() == 0)
            {
                SET_OSD_ITEM_INDEX(ucBackup);
                return _FALSE;
            }

            SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() - 1);
        }

        if(GET_OSD_ITEM_INDEX() >= _OSD_HDR_ITEM_AMOUNT)
        {
            SET_OSD_ITEM_INDEX(ucBackup);
            return _FALSE;
        }
    }
    while (OsdDisp2ndMenuCheck(tOSD_HDR_ITEM_PRI[GET_OSD_ITEM_INDEX()]) == _FALSE);

    if(ucBackup == GET_OSD_ITEM_INDEX())
    {
        return _FALSE;
    }

    if(GET_KEYMESSAGE() == _RIGHT_KEY_MESSAGE)
    {
        if(((ucBackup % _MENU_2ND_ITEM_MAX) + (GET_OSD_ITEM_INDEX() - ucBackup)) >= _MENU_2ND_ITEM_MAX)
        {
            OsdDisp2ndMenuStringSwitch(_OSD_MENU_HDR);
        }
    }

    if(GET_KEYMESSAGE() == _LEFT_KEY_MESSAGE)
    {
        if((ucBackup >= _MENU_2ND_ITEM_MAX) &&
           ((ucBackup % _MENU_2ND_ITEM_MAX) < (ucBackup - GET_OSD_ITEM_INDEX())))
        {
            OsdDisp2ndMenuStringSwitch(_OSD_MENU_HDR);
        }
    }

    return _TRUE;
}

//--------------------------------------------------
// Description    :
// Input Value    :
// Output Value :
//--------------------------------------------------
bit OsdDisp2ndQuicklinkSelectbyKey(void)
{
    BYTE ucBackup = GET_OSD_ITEM_INDEX();
    do
    {
        if(GET_KEYMESSAGE() == _RIGHT_KEY_MESSAGE)
        {
            if(GET_OSD_ITEM_INDEX() >= (_OSD_QUICK_ITEM_AMOUNT - 1))
            {
                SET_OSD_ITEM_INDEX(ucBackup);
                return _FALSE;
            }

            SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() + 1);
        }

        if(GET_KEYMESSAGE() == _LEFT_KEY_MESSAGE)
        {
            if(GET_OSD_ITEM_INDEX() == 0)
            {
                SET_OSD_ITEM_INDEX(ucBackup);
                return _FALSE;
            }

            SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() - 1);
        }

        if(GET_OSD_ITEM_INDEX() >= _OSD_QUICK_ITEM_AMOUNT)
        {
            SET_OSD_ITEM_INDEX(ucBackup);
            return _FALSE;
        }
    }
    while (OsdDisp2ndMenuCheck(tOSD_QUICK_ITEM_PRI[GET_OSD_ITEM_INDEX()]) == _FALSE);

    if(ucBackup == GET_OSD_ITEM_INDEX())
    {
        return _FALSE;
    }

    if(GET_KEYMESSAGE() == _RIGHT_KEY_MESSAGE)
    {
        if(((ucBackup % _MENU_2ND_ITEM_MAX) + (GET_OSD_ITEM_INDEX() - ucBackup)) >= _MENU_2ND_ITEM_MAX)
        {
            OsdDisp2ndMenuStringSwitch(_OSD_MENU_QUICKLINK);
        }
    }

    if(GET_KEYMESSAGE() == _LEFT_KEY_MESSAGE)
    {
        if((ucBackup >= _MENU_2ND_ITEM_MAX) &&
           ((ucBackup % _MENU_2ND_ITEM_MAX) < (ucBackup - GET_OSD_ITEM_INDEX())))
        {
            OsdDisp2ndMenuStringSwitch(_OSD_MENU_QUICKLINK);
        }
    }

    return _TRUE;
}

//--------------------------------------------------
// Description    :
// Input Value    :
// Output Value :
//--------------------------------------------------
bit OsdDisp2ndInputSelectbyKey(void)
{
    BYTE ucBackup = GET_OSD_ITEM_INDEX();
    do
    {
        if(GET_KEYMESSAGE() == _RIGHT_KEY_MESSAGE)
        {
            if(GET_OSD_ITEM_INDEX() >= (_OSD_INPUT_ITEM_AMOUNT - 1))
            {
                SET_OSD_ITEM_INDEX(ucBackup);
                return _FALSE;
            }

            SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() + 1);
        }

        if(GET_KEYMESSAGE() == _LEFT_KEY_MESSAGE)
        {
            if(GET_OSD_ITEM_INDEX() == 0)
            {
                SET_OSD_ITEM_INDEX(ucBackup);
                return _FALSE;
            }

            SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() - 1);
        }

        if(GET_OSD_ITEM_INDEX() >= _OSD_INPUT_ITEM_AMOUNT)
        {
            SET_OSD_ITEM_INDEX(ucBackup);
            return _FALSE;
        }
    }
    while (OsdDisp2ndMenuCheck(tOSD_INPUT_ITEM_PRI[GET_OSD_ITEM_INDEX()]) == _FALSE);

    if(ucBackup == GET_OSD_ITEM_INDEX())
    {
        return _FALSE;
    }

    if(GET_KEYMESSAGE() == _RIGHT_KEY_MESSAGE)
    {
        if(((ucBackup % _MENU_2ND_ITEM_MAX) + (GET_OSD_ITEM_INDEX() - ucBackup)) >= _MENU_2ND_ITEM_MAX)
        {
            OsdDisp2ndMenuStringSwitch(_OSD_MENU_INPUT);
        }
    }
    if(GET_KEYMESSAGE() == _LEFT_KEY_MESSAGE)
    {
        if((ucBackup >= _MENU_2ND_ITEM_MAX) &&
           ((ucBackup % _MENU_2ND_ITEM_MAX) < (ucBackup - GET_OSD_ITEM_INDEX())))
        {
            OsdDisp2ndMenuStringSwitch(_OSD_MENU_INPUT);
        }
    }

    return _TRUE;
}
#if(_DM_FUNCTION == _ON)
//--------------------------------------------------
// Description    :
// Input Value    :
// Output Value :
//--------------------------------------------------
bit OsdDisp2ndDVisionSelectbyKey(void)
{
    BYTE ucBackup = GET_OSD_ITEM_INDEX();

    do
    {
        if(GET_KEYMESSAGE() == _RIGHT_KEY_MESSAGE)
        {
            if(GET_OSD_ITEM_INDEX() >= (_OSD_DVISION_ITEM_AMOUNT - 1))
            {
                SET_OSD_ITEM_INDEX(ucBackup);
                return _FALSE;
            }

            SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() + 1);
        }

        if(GET_KEYMESSAGE() == _LEFT_KEY_MESSAGE)
        {
            if(GET_OSD_ITEM_INDEX() == 0)
            {
                SET_OSD_ITEM_INDEX(ucBackup);
                return _FALSE;
            }

            SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() - 1);
        }

        if(GET_OSD_ITEM_INDEX() >= _OSD_DVISION_ITEM_AMOUNT)
        {
            SET_OSD_ITEM_INDEX(ucBackup);
            return _FALSE;
        }
    }
    while (OsdDisp2ndMenuCheck(tOSD_DVISION_ITEM_PRI[GET_OSD_ITEM_INDEX()]) == _FALSE);

    if(ucBackup == GET_OSD_ITEM_INDEX())
    {
        return _FALSE;
    }

    if(GET_KEYMESSAGE() == _RIGHT_KEY_MESSAGE)
    {
        if(((ucBackup % _MENU_2ND_ITEM_MAX) + (GET_OSD_ITEM_INDEX() - ucBackup)) >= _MENU_2ND_ITEM_MAX)
        {
            OsdDisp2ndMenuStringSwitch(_OSD_MENU_DVISION);
        }
    }
    if(GET_KEYMESSAGE() == _LEFT_KEY_MESSAGE)
    {
        if((ucBackup >= _MENU_2ND_ITEM_MAX) &&
           ((ucBackup % _MENU_2ND_ITEM_MAX) < (ucBackup - GET_OSD_ITEM_INDEX())))
        {
            OsdDisp2ndMenuStringSwitch(_OSD_MENU_DVISION);
        }
    }

    return _TRUE;
}
#endif

#if(_AUDIO_ARC_SUPPORT == _ON)
//--------------------------------------------------
// Description    :
// Input Value    :
// Output Value :
//--------------------------------------------------
bit OsdDisp2ndeArcSelectbyKey(void)
{
    BYTE ucBackup = GET_OSD_ITEM_INDEX();

    do
    {
        if(GET_KEYMESSAGE() == _RIGHT_KEY_MESSAGE)
        {
            if(GET_OSD_ITEM_INDEX() >= (_OSD_AUDIO_ARC_ITEM_AMOUNT - 1))
            {
                SET_OSD_ITEM_INDEX(ucBackup);
                return _FALSE;
            }

            SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() + 1);
        }

        if(GET_KEYMESSAGE() == _LEFT_KEY_MESSAGE)
        {
            if(GET_OSD_ITEM_INDEX() == 0)
            {
                SET_OSD_ITEM_INDEX(ucBackup);
                return _FALSE;
            }

            SET_OSD_ITEM_INDEX(GET_OSD_ITEM_INDEX() - 1);
        }

        if(GET_OSD_ITEM_INDEX() >= _OSD_AUDIO_ARC_ITEM_AMOUNT)
        {
            SET_OSD_ITEM_INDEX(ucBackup);
            return _FALSE;
        }
    }
    while (OsdDisp2ndMenuCheck(tOSD_AUDIO_ARC_ITEM_PRI[GET_OSD_ITEM_INDEX()]) == _FALSE);

    if(ucBackup == GET_OSD_ITEM_INDEX())
    {
        return _FALSE;
    }

    if(GET_KEYMESSAGE() == _RIGHT_KEY_MESSAGE)
    {
        if(((ucBackup % _MENU_2ND_ITEM_MAX) + (GET_OSD_ITEM_INDEX() - ucBackup)) >= _MENU_2ND_ITEM_MAX)
        {
            OsdDisp2ndMenuStringSwitch(_OSD_MENU_AUDIO_ARC_EARC);
        }
    }
    if(GET_KEYMESSAGE() == _LEFT_KEY_MESSAGE)
    {
        if((ucBackup >= _MENU_2ND_ITEM_MAX) &&
           ((ucBackup % _MENU_2ND_ITEM_MAX) < (ucBackup - GET_OSD_ITEM_INDEX())))
        {
            OsdDisp2ndMenuStringSwitch(_OSD_MENU_AUDIO_ARC_EARC);
        }
    }

    return _TRUE;
}
#endif
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdDisp2ndMenuString(BYTE ucIconPos, WORD usString, BYTE ucColor)
{
    BYTE ucRow = ROW(_MENU_2ND_ITEM_ROW_ST + ucIconPos * 2);
    BYTE ucCol = COL(_MENU_2ND_ITEM_COL_ST);

    OsdFuncClearOsd(ucRow, ucCol, WIDTH(10), HEIGHT(1));

    SET_OSD_INFO_STRING_MODE(_PUT_STRING_LEFT);
    SET_OSD_INFO_STRING_MODE_LENGTH(_MENU_2ND_ITEM_WIDTH);
    OsdPropPutString(ucRow, ucCol, _PFONT_PAGE_1, usString, COLOR(ucColor, _CP_BG), GET_OSD_LANGUAGE());
}
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdDisp2ndMenuStringSwitch(EnumOsdItem enumOsdItem)
{
    BYTE ucTest = 0;
    BYTE ucItemMax = _MENU_2ND_ITEM_MAX;

    UserCommonOsdWindowDisable(_OSD_WIN_HIGHLIGHT_2);
    OsdFuncClearOsd(_MENU_2ND_ITEM_ROW_ST, _MENU_2ND_ITEM_COL_ST, WIDTH(g_ucOsdWidth - _MENU_2ND_ITEM_COL_ST), HEIGHT(_MENU_2ND_ITEM_MAX * 2));

    switch(enumOsdItem)
    {
        case _OSD_MENU_MUTIP:

            if((_OSD_MUTIP_ITEM_AMOUNT - ((GET_OSD_ITEM_INDEX() / _MENU_2ND_ITEM_MAX) * _MENU_2ND_ITEM_MAX)) < _MENU_2ND_ITEM_MAX)
            {
                ucItemMax = (_OSD_MUTIP_ITEM_AMOUNT % _MENU_2ND_ITEM_MAX);
            }
            else
            {
                ucItemMax = _MENU_2ND_ITEM_MAX;
            }

            for (ucTest = 0; ucTest < ucItemMax; ucTest++)
            {
                OsdDispItemValueUpdate(tOSD_MUTIP_ITEM_PRI[(((GET_OSD_ITEM_INDEX() / _MENU_2ND_ITEM_MAX) * _MENU_2ND_ITEM_MAX) + ucTest)]);
                OsdDisp2ndMenuString(ucTest, OsdDisp2ndMenuStringGet(((GET_OSD_ITEM_INDEX() / _MENU_2ND_ITEM_MAX) * _MENU_2ND_ITEM_MAX) + ucTest, _OSD_MENU_MUTIP), (OsdDisp2ndMenuCheck(tOSD_MUTIP_ITEM_PRI[((((GET_OSD_ITEM_INDEX() / _MENU_2ND_ITEM_MAX)*_MENU_2ND_ITEM_MAX) + ucTest))])) ? _CP_BLUE : _CP_GRAY);
                OsdDisp2ndMenuValue(ucTest, tOSD_MUTIP_ITEM_PRI[(((GET_OSD_ITEM_INDEX() / _MENU_2ND_ITEM_MAX) * _MENU_2ND_ITEM_MAX) + ucTest)], ((OsdDisp2ndMenuCheck(tOSD_MUTIP_ITEM_PRI[(((GET_OSD_ITEM_INDEX() / _MENU_2ND_ITEM_MAX) * _MENU_2ND_ITEM_MAX) + ucTest)])) ? _CP_BLUE : _CP_GRAY));
            }

            break;

        case _OSD_MENU_PICTURE:

            if((_OSD_PICTURE_ITEM_AMOUNT - ((GET_OSD_ITEM_INDEX() / _MENU_2ND_ITEM_MAX) * _MENU_2ND_ITEM_MAX)) < _MENU_2ND_ITEM_MAX)
            {
                ucItemMax = (_OSD_PICTURE_ITEM_AMOUNT % _MENU_2ND_ITEM_MAX);
            }
            else
            {
                ucItemMax = _MENU_2ND_ITEM_MAX;
            }

            for(ucTest = 0; ucTest < ucItemMax; ucTest++)
            {
                OsdDispItemValueUpdate(tOSD_PICTURE_ITEM_PRI[(((GET_OSD_ITEM_INDEX() / _MENU_2ND_ITEM_MAX) * _MENU_2ND_ITEM_MAX) + ucTest)]);
                OsdDisp2ndMenuString(ucTest, OsdDisp2ndMenuStringGet(((GET_OSD_ITEM_INDEX() / _MENU_2ND_ITEM_MAX) * _MENU_2ND_ITEM_MAX) + ucTest, _OSD_MENU_PICTURE), (OsdDisp2ndMenuCheck(tOSD_PICTURE_ITEM_PRI[((((GET_OSD_ITEM_INDEX() / _MENU_2ND_ITEM_MAX) * _MENU_2ND_ITEM_MAX) + ucTest))])) ? _CP_BLUE : _CP_GRAY);
                OsdDisp2ndMenuValue(ucTest, tOSD_PICTURE_ITEM_PRI[(((GET_OSD_ITEM_INDEX() / _MENU_2ND_ITEM_MAX) * _MENU_2ND_ITEM_MAX) + ucTest)], ((OsdDisp2ndMenuCheck(tOSD_PICTURE_ITEM_PRI[(((GET_OSD_ITEM_INDEX() / _MENU_2ND_ITEM_MAX) * _MENU_2ND_ITEM_MAX) + ucTest)])) ? _CP_BLUE : _CP_GRAY));
            }

            break;

        case _OSD_MENU_DISPLAY:
            if((_OSD_DISPLAY_ITEM_AMOUNT - ((GET_OSD_ITEM_INDEX() / _MENU_2ND_ITEM_MAX) * _MENU_2ND_ITEM_MAX)) < _MENU_2ND_ITEM_MAX)
            {
                ucItemMax = (_OSD_DISPLAY_ITEM_AMOUNT % _MENU_2ND_ITEM_MAX);
            }
            else
            {
                ucItemMax = _MENU_2ND_ITEM_MAX;
            }

            for(ucTest = 0; ucTest < ucItemMax; ucTest++)
            {
                OsdDispItemValueUpdate(tOSD_DISPLAY_ITEM_PRI[(((GET_OSD_ITEM_INDEX() / _MENU_2ND_ITEM_MAX) * _MENU_2ND_ITEM_MAX) + ucTest)]);
                OsdDisp2ndMenuString(ucTest, OsdDisp2ndMenuStringGet(((GET_OSD_ITEM_INDEX() / _MENU_2ND_ITEM_MAX) * _MENU_2ND_ITEM_MAX) + ucTest, _OSD_MENU_DISPLAY), (OsdDisp2ndMenuCheck(tOSD_DISPLAY_ITEM_PRI[(((GET_OSD_ITEM_INDEX() / _MENU_2ND_ITEM_MAX) * _MENU_2ND_ITEM_MAX) + ucTest)])) ? _CP_BLUE : _CP_GRAY);
                OsdDisp2ndMenuValue(ucTest, tOSD_DISPLAY_ITEM_PRI[(((GET_OSD_ITEM_INDEX() / _MENU_2ND_ITEM_MAX) * _MENU_2ND_ITEM_MAX) + ucTest)], ((OsdDisp2ndMenuCheck(tOSD_DISPLAY_ITEM_PRI[(((GET_OSD_ITEM_INDEX() / _MENU_2ND_ITEM_MAX) * _MENU_2ND_ITEM_MAX) + ucTest)])) ? _CP_BLUE : _CP_GRAY)); //
            }

            break;

        case _OSD_MENU_COLOR:

            if((_OSD_COLOR_ITEM_AMOUNT - ((GET_OSD_ITEM_INDEX() / _MENU_2ND_ITEM_MAX) * _MENU_2ND_ITEM_MAX)) < _MENU_2ND_ITEM_MAX)
            {
                ucItemMax = (_OSD_COLOR_ITEM_AMOUNT % _MENU_2ND_ITEM_MAX);
            }
            else
            {
                ucItemMax = _MENU_2ND_ITEM_MAX;
            }

            for (ucTest = 0; ucTest < ucItemMax; ucTest++)
            {
                OsdDispItemValueUpdate(tOSD_COLOR_ITEM_PRI[(((GET_OSD_ITEM_INDEX() / _MENU_2ND_ITEM_MAX) * _MENU_2ND_ITEM_MAX) + ucTest)]);
                OsdDisp2ndMenuString(ucTest, OsdDisp2ndMenuStringGet(((GET_OSD_ITEM_INDEX() / _MENU_2ND_ITEM_MAX) * _MENU_2ND_ITEM_MAX) + ucTest, _OSD_MENU_COLOR), (OsdDisp2ndMenuCheck(tOSD_COLOR_ITEM_PRI[(((GET_OSD_ITEM_INDEX() / _MENU_2ND_ITEM_MAX) * _MENU_2ND_ITEM_MAX) + ucTest)])) ? _CP_BLUE : _CP_GRAY);
                OsdDisp2ndMenuValue(ucTest, tOSD_COLOR_ITEM_PRI[(((GET_OSD_ITEM_INDEX() / _MENU_2ND_ITEM_MAX) * _MENU_2ND_ITEM_MAX) + ucTest)], ((OsdDisp2ndMenuCheck(tOSD_COLOR_ITEM_PRI[(((GET_OSD_ITEM_INDEX() / _MENU_2ND_ITEM_MAX) * _MENU_2ND_ITEM_MAX) + ucTest)])) ? _CP_BLUE : _CP_GRAY)); //
            }

            break;

        case _OSD_MENU_ADVANCE:
            if((_OSD_ADVANCE_ITEM_AMOUNT - ((GET_OSD_ITEM_INDEX() / _MENU_2ND_ITEM_MAX) * _MENU_2ND_ITEM_MAX)) < _MENU_2ND_ITEM_MAX)
            {
                ucItemMax = (_OSD_ADVANCE_ITEM_AMOUNT % _MENU_2ND_ITEM_MAX);
            }
            else
            {
                ucItemMax = _MENU_2ND_ITEM_MAX;
            }

            for (ucTest = 0; ucTest < ucItemMax; ucTest++)
            {
                OsdDispItemValueUpdate(tOSD_ADVANCE_ITEM_PRI[(((GET_OSD_ITEM_INDEX() / _MENU_2ND_ITEM_MAX) * _MENU_2ND_ITEM_MAX) + ucTest)]);
                OsdDisp2ndMenuString(ucTest, OsdDisp2ndMenuStringGet(((GET_OSD_ITEM_INDEX() / _MENU_2ND_ITEM_MAX) * _MENU_2ND_ITEM_MAX) + ucTest, _OSD_MENU_ADVANCE), (OsdDisp2ndMenuCheck(tOSD_ADVANCE_ITEM_PRI[(((GET_OSD_ITEM_INDEX() / _MENU_2ND_ITEM_MAX) * _MENU_2ND_ITEM_MAX) + ucTest)])) ? _CP_BLUE : _CP_GRAY);
                OsdDisp2ndMenuValue(ucTest, tOSD_ADVANCE_ITEM_PRI[(((GET_OSD_ITEM_INDEX() / _MENU_2ND_ITEM_MAX) * _MENU_2ND_ITEM_MAX) + ucTest)], ((OsdDisp2ndMenuCheck(tOSD_ADVANCE_ITEM_PRI[(((GET_OSD_ITEM_INDEX() / _MENU_2ND_ITEM_MAX) * _MENU_2ND_ITEM_MAX) + ucTest)])) ? _CP_BLUE : _CP_GRAY));
            }

            break;

        case _OSD_MENU_AUDIO:
            if((_OSD_AUDIO_ITEM_AMOUNT - ((GET_OSD_ITEM_INDEX() / _MENU_2ND_ITEM_MAX) * _MENU_2ND_ITEM_MAX)) < _MENU_2ND_ITEM_MAX)
            {
                ucItemMax = (_OSD_AUDIO_ITEM_AMOUNT % _MENU_2ND_ITEM_MAX);
            }
            else
            {
                ucItemMax = _MENU_2ND_ITEM_MAX;
            }

            for (ucTest = 0; ucTest < ucItemMax; ucTest++)
            {
                OsdDispItemValueUpdate(tOSD_AUDIO_ITEM_PRI[(((GET_OSD_ITEM_INDEX() / _MENU_2ND_ITEM_MAX) * _MENU_2ND_ITEM_MAX) + ucTest)]);
                OsdDisp2ndMenuString(ucTest, OsdDisp2ndMenuStringGet(((GET_OSD_ITEM_INDEX() / _MENU_2ND_ITEM_MAX) * _MENU_2ND_ITEM_MAX) + ucTest, _OSD_MENU_AUDIO), (OsdDisp2ndMenuCheck(tOSD_AUDIO_ITEM_PRI[(((GET_OSD_ITEM_INDEX() / _MENU_2ND_ITEM_MAX) * _MENU_2ND_ITEM_MAX) + ucTest)])) ? _CP_BLUE : _CP_GRAY);
                OsdDisp2ndMenuValue(ucTest, tOSD_AUDIO_ITEM_PRI[(((GET_OSD_ITEM_INDEX() / _MENU_2ND_ITEM_MAX) * _MENU_2ND_ITEM_MAX) + ucTest)], ((OsdDisp2ndMenuCheck(tOSD_AUDIO_ITEM_PRI[(((GET_OSD_ITEM_INDEX() / _MENU_2ND_ITEM_MAX) * _MENU_2ND_ITEM_MAX) + ucTest)])) ? _CP_BLUE : _CP_GRAY)); //
            }

            break;

        case _OSD_MENU_OTHER:
            DebugMessageOsd("_MENU_OTHER ", GET_OSD_ITEM_INDEX());

            if((_OSD_OTHER_ITEM_AMOUNT - ((GET_OSD_ITEM_INDEX() / _MENU_2ND_ITEM_MAX) * _MENU_2ND_ITEM_MAX)) < _MENU_2ND_ITEM_MAX)
            {
                ucItemMax = (_OSD_OTHER_ITEM_AMOUNT % _MENU_2ND_ITEM_MAX);
            }
            else
            {
                ucItemMax = _MENU_2ND_ITEM_MAX;
            }

            for (ucTest = 0; ucTest < ucItemMax; ucTest++)
            {
                OsdDispItemValueUpdate(tOSD_OTHER_ITEM_PRI[(((GET_OSD_ITEM_INDEX() / _MENU_2ND_ITEM_MAX) * _MENU_2ND_ITEM_MAX) + ucTest)]);
                OsdDisp2ndMenuString(ucTest, OsdDisp2ndMenuStringGet(((GET_OSD_ITEM_INDEX() / _MENU_2ND_ITEM_MAX)*_MENU_2ND_ITEM_MAX) + ucTest, _OSD_MENU_OTHER), (OsdDisp2ndMenuCheck(tOSD_OTHER_ITEM_PRI[(((GET_OSD_ITEM_INDEX() / _MENU_2ND_ITEM_MAX) * _MENU_2ND_ITEM_MAX) + ucTest)])) ? _CP_BLUE : _CP_GRAY);
                OsdDisp2ndMenuValue(ucTest, tOSD_OTHER_ITEM_PRI[(((GET_OSD_ITEM_INDEX() / _MENU_2ND_ITEM_MAX) * _MENU_2ND_ITEM_MAX) + ucTest)], ((OsdDisp2ndMenuCheck(tOSD_OTHER_ITEM_PRI[(((GET_OSD_ITEM_INDEX() / _MENU_2ND_ITEM_MAX) * _MENU_2ND_ITEM_MAX) + ucTest)])) ? _CP_BLUE : _CP_GRAY)); //
            }

            break;

#if(_HDR10_SUPPORT == _ON)
        case _OSD_MENU_HDR:
            if((_OSD_HDR_ITEM_AMOUNT - ((GET_OSD_ITEM_INDEX() / _MENU_2ND_ITEM_MAX) * _MENU_2ND_ITEM_MAX)) < _MENU_2ND_ITEM_MAX)
            {
                ucItemMax = (_OSD_HDR_ITEM_AMOUNT % _MENU_2ND_ITEM_MAX);
            }
            else
            {
                ucItemMax = _MENU_2ND_ITEM_MAX;
            }

            for (ucTest = 0; ucTest < ucItemMax; ucTest++)
            {
                OsdDispItemValueUpdate(tOSD_HDR_ITEM_PRI[(((GET_OSD_ITEM_INDEX() / _MENU_2ND_ITEM_MAX) * _MENU_2ND_ITEM_MAX) + ucTest)]);
                OsdDisp2ndMenuString(ucTest, OsdDisp2ndMenuStringGet(((GET_OSD_ITEM_INDEX() / _MENU_2ND_ITEM_MAX) * _MENU_2ND_ITEM_MAX) + ucTest, _OSD_MENU_HDR), (OsdDisp2ndMenuCheck(tOSD_HDR_ITEM_PRI[(((GET_OSD_ITEM_INDEX() / _MENU_2ND_ITEM_MAX) * _MENU_2ND_ITEM_MAX) + ucTest)])) ? _CP_BLUE : _CP_GRAY);
                OsdDisp2ndMenuValue(ucTest, tOSD_HDR_ITEM_PRI[(((GET_OSD_ITEM_INDEX() / _MENU_2ND_ITEM_MAX) * _MENU_2ND_ITEM_MAX) + ucTest)], ((OsdDisp2ndMenuCheck(tOSD_HDR_ITEM_PRI[(((GET_OSD_ITEM_INDEX() / _MENU_2ND_ITEM_MAX) * _MENU_2ND_ITEM_MAX) + ucTest)])) ? _CP_BLUE : _CP_GRAY)); //
            }
            break;
#endif
        case _OSD_MENU_QUICKLINK:
            if((_OSD_QUICK_ITEM_AMOUNT - ((GET_OSD_ITEM_INDEX() / _MENU_2ND_ITEM_MAX) * _MENU_2ND_ITEM_MAX)) < _MENU_2ND_ITEM_MAX)
            {
                ucItemMax = (_OSD_QUICK_ITEM_AMOUNT % _MENU_2ND_ITEM_MAX);
            }
            else
            {
                ucItemMax = _MENU_2ND_ITEM_MAX;
            }

            for (ucTest = 0; ucTest < ucItemMax; ucTest++)
            {
                OsdDispItemValueUpdate(tOSD_QUICK_ITEM_PRI[(((GET_OSD_ITEM_INDEX() / _MENU_2ND_ITEM_MAX) * _MENU_2ND_ITEM_MAX) + ucTest)]);
                OsdDisp2ndMenuString(ucTest, OsdDisp2ndMenuStringGet(((GET_OSD_ITEM_INDEX() / _MENU_2ND_ITEM_MAX) * _MENU_2ND_ITEM_MAX) + ucTest, _OSD_MENU_QUICKLINK), (OsdDisp2ndMenuCheck(tOSD_QUICK_ITEM_PRI[(((GET_OSD_ITEM_INDEX() / _MENU_2ND_ITEM_MAX) * _MENU_2ND_ITEM_MAX) + ucTest)])) ? _CP_BLUE : _CP_GRAY);
                OsdDisp2ndMenuValue(ucTest, tOSD_QUICK_ITEM_PRI[(((GET_OSD_ITEM_INDEX() / _MENU_2ND_ITEM_MAX) * _MENU_2ND_ITEM_MAX) + ucTest)], ((OsdDisp2ndMenuCheck(tOSD_QUICK_ITEM_PRI[(((GET_OSD_ITEM_INDEX() / _MENU_2ND_ITEM_MAX) * _MENU_2ND_ITEM_MAX) + ucTest)])) ? _CP_BLUE : _CP_GRAY)); //
            }

            break;

        case _OSD_MENU_INPUT:

            if((_OSD_INPUT_ITEM_AMOUNT - ((GET_OSD_ITEM_INDEX() / _MENU_2ND_ITEM_MAX) * _MENU_2ND_ITEM_MAX)) < _MENU_2ND_ITEM_MAX)
            {
                ucItemMax = (_OSD_INPUT_ITEM_AMOUNT % _MENU_2ND_ITEM_MAX);
            }
            else
            {
                ucItemMax = _MENU_2ND_ITEM_MAX;
            }

            for(ucTest = 0; ucTest < ucItemMax; ucTest++)
            {
                OsdDispItemValueUpdate(tOSD_INPUT_ITEM_PRI[(((GET_OSD_ITEM_INDEX() / _MENU_2ND_ITEM_MAX) * _MENU_2ND_ITEM_MAX) + ucTest)]);
                OsdDisp2ndMenuString(ucTest, OsdDisp2ndMenuStringGet(((GET_OSD_ITEM_INDEX() / _MENU_2ND_ITEM_MAX) * _MENU_2ND_ITEM_MAX) + ucTest, _OSD_MENU_INPUT), (OsdDisp2ndMenuCheck(tOSD_INPUT_ITEM_PRI[(((GET_OSD_ITEM_INDEX() / _MENU_2ND_ITEM_MAX) * _MENU_2ND_ITEM_MAX) + ucTest)])) ? _CP_BLUE : _CP_LIGHTBLUE);
                OsdDisp2ndMenuValue(ucTest, tOSD_INPUT_ITEM_PRI[(((GET_OSD_ITEM_INDEX() / _MENU_2ND_ITEM_MAX) * _MENU_2ND_ITEM_MAX) + ucTest)], ((OsdDisp2ndMenuCheck(tOSD_INPUT_ITEM_PRI[(((GET_OSD_ITEM_INDEX() / _MENU_2ND_ITEM_MAX) * _MENU_2ND_ITEM_MAX) + ucTest)])) ? _CP_BLUE : _CP_LIGHTBLUE)); //
            }

            break;
#if(_DM_FUNCTION == _ON)
        case _OSD_MENU_DVISION:
            if((_OSD_DVISION_ITEM_AMOUNT - ((GET_OSD_ITEM_INDEX() / _MENU_2ND_ITEM_MAX) * _MENU_2ND_ITEM_MAX)) < _MENU_2ND_ITEM_MAX)
            {
                ucItemMax = (_OSD_DVISION_ITEM_AMOUNT % _MENU_2ND_ITEM_MAX);
            }
            else
            {
                ucItemMax = _MENU_2ND_ITEM_MAX;
            }

            for (ucTest = 0; ucTest < ucItemMax; ucTest++)
            {
                OsdDispItemValueUpdate(tOSD_DVISION_ITEM_PRI[(((GET_OSD_ITEM_INDEX() / _MENU_2ND_ITEM_MAX) * _MENU_2ND_ITEM_MAX) + ucTest)]);
                OsdDisp2ndMenuString(ucTest, OsdDisp2ndMenuStringGet(((GET_OSD_ITEM_INDEX() / _MENU_2ND_ITEM_MAX) * _MENU_2ND_ITEM_MAX) + ucTest, _OSD_MENU_HDR), (OsdDisp2ndMenuCheck(tOSD_DVISION_ITEM_PRI[(((GET_OSD_ITEM_INDEX() / _MENU_2ND_ITEM_MAX) * _MENU_2ND_ITEM_MAX) + ucTest)])) ? _CP_BLUE : _CP_GRAY);
                OsdDisp2ndMenuValue(ucTest, tOSD_DVISION_ITEM_PRI[(((GET_OSD_ITEM_INDEX() / _MENU_2ND_ITEM_MAX) * _MENU_2ND_ITEM_MAX) + ucTest)], ((OsdDisp2ndMenuCheck(tOSD_DVISION_ITEM_PRI[(((GET_OSD_ITEM_INDEX() / _MENU_2ND_ITEM_MAX) * _MENU_2ND_ITEM_MAX) + ucTest)])) ? _CP_BLUE : _CP_GRAY)); //
            }
            break;
#endif
#if(_AUDIO_ARC_SUPPORT == _ON)
        case _OSD_MENU_AUDIO_ARC_EARC:
            if((_OSD_AUDIO_ARC_ITEM_AMOUNT - ((GET_OSD_ITEM_INDEX() / _MENU_2ND_ITEM_MAX) * _MENU_2ND_ITEM_MAX)) < _MENU_2ND_ITEM_MAX)
            {
                ucItemMax = (_OSD_AUDIO_ARC_ITEM_AMOUNT % _MENU_2ND_ITEM_MAX);
            }
            else
            {
                ucItemMax = _MENU_2ND_ITEM_MAX;
            }

            for (ucTest = 0; ucTest < ucItemMax; ucTest++)
            {
                OsdDispItemValueUpdate(tOSD_AUDIO_ARC_ITEM_PRI[(((GET_OSD_ITEM_INDEX() / _MENU_2ND_ITEM_MAX) * _MENU_2ND_ITEM_MAX) + ucTest)]);
                OsdDisp2ndMenuString(ucTest, OsdDisp2ndMenuStringGet(((GET_OSD_ITEM_INDEX() / _MENU_2ND_ITEM_MAX) * _MENU_2ND_ITEM_MAX) + ucTest, _OSD_MENU_AUDIO_ARC_EARC), (OsdDisp2ndMenuCheck(tOSD_AUDIO_ARC_ITEM_PRI[(((GET_OSD_ITEM_INDEX() / _MENU_2ND_ITEM_MAX) * _MENU_2ND_ITEM_MAX) + ucTest)])) ? _CP_BLUE : _CP_GRAY);
                OsdDisp2ndMenuValue(ucTest, tOSD_AUDIO_ARC_ITEM_PRI[(((GET_OSD_ITEM_INDEX() / _MENU_2ND_ITEM_MAX) * _MENU_2ND_ITEM_MAX) + ucTest)], ((OsdDisp2ndMenuCheck(tOSD_AUDIO_ARC_ITEM_PRI[(((GET_OSD_ITEM_INDEX() / _MENU_2ND_ITEM_MAX) * _MENU_2ND_ITEM_MAX) + ucTest)])) ? _CP_BLUE : _CP_GRAY)); //
            }
            break;
#endif
        case _OSD_MENU_FACTORY:
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdDisp1stMenuCursor(BYTE ucIdx)
{
    BYTE ucRow = 0;
    BYTE ucCol = 0;

    ucRow = (((ucIdx % 8) / 4) ? ROW(14) : ROW(4));
    ucCol = COL(4) + ((ucIdx % 4) * 10) - 2;

    SET_OSD_WINDOW_BUTTON_TYPE(_OSD_WINDOW_BUTTON_TYPE_ROUNDED);

    // OsdWindowDrawingByFontHighlight(_OSD_WIN_HIGHLIGHT_1, ucRow, ucCol, WIDTH(10), HEIGHT(5), _CP_BLUE, _CP_ORANGE, _CP_BLUE);
    OsdWindowDrawingByFontHighlight(_OSD_WIN_HIGHLIGHT_1, ucRow - 1, ucCol - 1, WIDTH(10 + 2), HEIGHT(5 + 2), _CP_BLUE, _CP_ORANGE, _CP_BLUE);

    UserCommonOsdRoundedWindowOnOff(_OSD_WIN_HIGHLIGHT_1, _ON, _ON, _ON, _ON, _ON);
#if 0// for 8x8 rounded
    UserCommonOsdRoundedWindowSize(_OSD_WIN_HIGHLIGHT_1, _OSD_ROUNDED_WIN_SIZE_8X8);
    UserCommonOsdRoundedWindowPattern8x8(0, 1);
    UserCommonOsdRoundedWindowPattern8x8(1, 3);
    UserCommonOsdRoundedWindowPattern8x8(2, 4);
    UserCommonOsdRoundedWindowPattern8x8(3, 5);
    UserCommonOsdRoundedWindowPattern8x8(4, 6);
    UserCommonOsdRoundedWindowPattern8x8(5, 6);
    UserCommonOsdRoundedWindowPattern8x8(6, 7);
    UserCommonOsdRoundedWindowPattern8x8(7, 7);
#else
    UserCommonOsdRoundedWindowSize(_OSD_WIN_HIGHLIGHT_1, _OSD_ROUNDED_WIN_SIZE_16X16);
    UserCommonOsdRoundedWindowPattern16x16(0, 3);
    UserCommonOsdRoundedWindowPattern16x16(1, 6);
    UserCommonOsdRoundedWindowPattern16x16(2, 8);
    UserCommonOsdRoundedWindowPattern16x16(3, 9);
    UserCommonOsdRoundedWindowPattern16x16(4, 10);
    UserCommonOsdRoundedWindowPattern16x16(5, 11);
    UserCommonOsdRoundedWindowPattern16x16(6, 12);
    UserCommonOsdRoundedWindowPattern16x16(7, 13);
    UserCommonOsdRoundedWindowPattern16x16(8, 13);
    UserCommonOsdRoundedWindowPattern16x16(9, 14);
    UserCommonOsdRoundedWindowPattern16x16(10, 14);
    UserCommonOsdRoundedWindowPattern16x16(11, 14);
    UserCommonOsdRoundedWindowPattern16x16(12, 15);
    UserCommonOsdRoundedWindowPattern16x16(13, 15);
    UserCommonOsdRoundedWindowPattern16x16(14, 15);
    UserCommonOsdRoundedWindowPattern16x16(15, 15);
#endif
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdDisp2ndMenuCursor(BYTE ucIdex)
{
    OsdWindowDrawing(
        _OSD_WIN_HIGHLIGHT_2,
        (_MENU_2ND_ITEM_COL_ST * 12 - 6),
        ((_MENU_2ND_ITEM_ROW_ST + (ucIdex % _MENU_2ND_ITEM_MAX) * 2) * 18 - 9),
        ((_MENU_2ND_ITEM_COL_ST + _MENU_2ND_ITEM_WIDTH + 1) * 12),
        ((_MENU_2ND_ITEM_ROW_ST + (ucIdex % _MENU_2ND_ITEM_MAX) * 2 + 1) * 18 + 10),
        _CP_BLUE);

    UserCommonOsdWindowHighlightFunction(_ENABLE, _OSD_WIN_HIGHLIGHT_2, _CP_WHITE, _CP_BLUE, _CP_BG);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdMenu3rdFrame(void)
{
    // Clear data
    OsdWindowGridLine(2);////By Jerry -2017-12-11//replace GridLine function
    UserCommonOsdWindowDisable(_OSD_WIN_HIGHLIGHT_4);
    OsdFuncClearOsd(
        ROW(_MENU_2ND_ITEM_ROW_ST),
        COL(_MENU_2ND_ITEM_VAL_COL_ST),
        LENGTH(_MENU_3RD_ITEM_WIDTH),
        HEIGHT((_MENU_2ND_ITEM_MAX) * 2));

    OsdWindowDrawing(_OSD_WIN_HIGHLIGHT_3_BORDER, COL(_MENU_2ND_ITEM_VAL_COL_ST) * 12 - 1, ROW(_MENU_2ND_ITEM_ROW_ST) * 18 - 1, ((COL(_MENU_2ND_ITEM_VAL_COL_ST) + WIDTH(_MENU_3RD_ITEM_WIDTH)) * 12 + 1), ((ROW(_MENU_2ND_ITEM_ROW_ST) + HEIGHT((_MENU_2ND_ITEM_MAX - 1) * 2 + 1)) * 18 + 1), _CP_WHITE);

    SET_OSD_WINDOW_BORDER_PIXEL_WIDTH(1);
    SET_OSD_WINDOW_BORDER_PIXEL_HEIGHT(1);
    SET_OSD_WINDOW_BUTTON_TYPE(_OSD_WINDOW_BUTTON_TYPE_CHESSBOARD);
    OsdWindowDrawingByFont(_OSD_WIN_HIGHLIGHT_3, ROW(_MENU_2ND_ITEM_ROW_ST), COL(_MENU_2ND_ITEM_VAL_COL_ST), WIDTH(_MENU_3RD_ITEM_WIDTH), HEIGHT((_MENU_2ND_ITEM_MAX - 1) * 2 + 1), _CP_BLUE);

    // draw Window
    UserCommonOsdWindowChessboard(_ON, _OSD_WIN_HIGHLIGHT_3, _CP_BLUE, _CP_GRAY);
}
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdDisp4thItemAdj(bit bitbAdjShow)
{
    if((g_stOsdItemData.b3ShowType == _ADJ_BAR_REAL) ||
       (g_stOsdItemData.b3ShowType == _ADJ_BAR_PERCENT))
    {
        OsdDisp3rdBartemAdj(bitbAdjShow);
    }
    else if(g_stOsdItemData.b3ShowType == _ADJ_LIST)
    {
        OsdDisp4thListItemAdj(bitbAdjShow);
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdDisp3rdItemAdj(EnumOsdItem enumOsdItem, bit bitbAdjShow)
{
    if((g_stOsdItemData.b3ShowType == _ADJ_BAR_REAL) ||
       (g_stOsdItemData.b3ShowType == _ADJ_BAR_PERCENT))
    {
        OsdDisp3rdBartemAdj(bitbAdjShow);
    }
    else if(g_stOsdItemData.b3ShowType == _ADJ_LIST)
    {
        if(enumOsdItem == _OSD_EXIT_HOTKEY)
        {
            OsdDispHotKeyMenuListItemAdj(bitbAdjShow);
        }
        else
        {
            OsdDisp3rdListItemAdj(enumOsdItem, bitbAdjShow);
        }
    }
}

//--------------------------------------------------
// Description  :  you must call "OsdDispItemValueUpdate(enumOsdItem); " function before
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdDisp3rdBartemAdj(bit bitbAdjShow)
{
    WORD usAdjValue = g_stOsdItemData.usAdjValue;
    WORD usBackupValue = g_stOsdItemData.usAdjValue;

    if((g_stOsdItemData.b3ShowType != _ADJ_BAR_REAL) &&
       (g_stOsdItemData.b3ShowType != _ADJ_BAR_PERCENT))
    {
        return;
    }

    if((g_stOsdItemData.usAdjValueCenter == 0) ||
       (g_stOsdItemData.usAdjValueCenter >= g_stOsdItemData.usAdjValueMax) ||
       (g_stOsdItemData.usAdjValueCenter <= g_stOsdItemData.usAdjValueMin))
    {
        g_stOsdItemData.usAdjValueCenter = ((g_stOsdItemData.usAdjValueMax - g_stOsdItemData.usAdjValueMin) / 2) + g_stOsdItemData.usAdjValueMin;
    }

    if(g_stOsdItemData.b3ShowType == _ADJ_BAR_PERCENT)
    {
        usAdjValue = UserCommonDisplayRealValueToPercentAdjust(g_stOsdItemData.usAdjValue, g_stOsdItemData.usAdjValueMax, g_stOsdItemData.usAdjValueMin, g_stOsdItemData.usAdjValueCenter);
        usBackupValue = usAdjValue;
        if(bitbAdjShow == _ON)
        {
            usAdjValue = OsdDisplayDetOverRange(usAdjValue, _100_PERCENT, _0_PERCENT, _OFF);
            if(usBackupValue != usAdjValue) // redraw
            {
                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), usAdjValue, _SLIDER_0, _SELECT);
                OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), usAdjValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_3, _OSD_NUMBER_UNSTLECT_COLOR);
            }
        }
        else
        {
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), usAdjValue, _SLIDER_0, _SELECT);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), usAdjValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_3, _OSD_NUMBER_UNSTLECT_COLOR);
        }
        if(bitbAdjShow == _ON)
        {
            g_stOsdItemData.usAdjValue = UserCommonDisplayPercentToRealValueAdjust(usAdjValue, g_stOsdItemData.usAdjValueMax, g_stOsdItemData.usAdjValueMin, g_stOsdItemData.usAdjValueCenter);
        }
    }
    else if(g_stOsdItemData.b3ShowType == _ADJ_BAR_REAL)
    {
        usBackupValue = usAdjValue;
        if(bitbAdjShow == _ON)
        {
            usAdjValue = OsdDisplayDetOverRange(usAdjValue, g_stOsdItemData.usAdjValueMax, g_stOsdItemData.usAdjValueMin, _OFF);
            if(usBackupValue != usAdjValue)// redraw
            {
                OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), usAdjValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_4), _PFONT_PAGE_3, _OSD_NUMBER_UNSTLECT_COLOR);
                g_stOsdItemData.usAdjValue = usAdjValue;
                usAdjValue = UserCommonDisplayRealValueToPercentAdjust(usAdjValue, g_stOsdItemData.usAdjValueMax, g_stOsdItemData.usAdjValueMin, g_stOsdItemData.usAdjValueCenter);
                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), usAdjValue, _SLIDER_0, _SELECT);
            }
        }
        else
        {
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), usAdjValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_4), _PFONT_PAGE_3, _OSD_NUMBER_UNSTLECT_COLOR);
            usAdjValue = UserCommonDisplayRealValueToPercentAdjust(usAdjValue, g_stOsdItemData.usAdjValueMax, g_stOsdItemData.usAdjValueMin, g_stOsdItemData.usAdjValueCenter);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), usAdjValue, _SLIDER_0, _SELECT);
        }
    }

    g_usAdjustValue = g_stOsdItemData.usAdjValue;
}

//--------------------------------------------------
// Description  :  you must call "OsdDispItemValueUpdate(enumOsdItem); " function before
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdDisp3rdListItemAdj(EnumOsdItem enumOsdItem, bit bitbAdjShow)
{
    BYTE ucLoop = 0;
    WORD usItemMax = 0;
    BYTE ucCPColor = _CP_WHITE;
    WORD usBackValue = g_stOsdItemData.usAdjValue;

    if(g_stOsdItemData.b3ShowType != _ADJ_LIST)
    {
        return;
    }

    if(bitbAdjShow == _ON)
    {
        ucLoop = 0;
        do
        {
            g_stOsdItemData.usAdjValue = (OsdDisplayDetOverRange(g_stOsdItemData.usAdjValue, g_stOsdItemData.usAdjValueMax, g_stOsdItemData.usAdjValueMin, _ON));
            ucLoop++;
        }
        while((OsdDisp3rdItemCheck(enumOsdItem, (g_stOsdItemData.usAdjValue - g_stOsdItemData.usAdjValueMin)) != _TRUE) &&
              (ucLoop < (g_stOsdItemData.usAdjValueMax - g_stOsdItemData.usAdjValueMin + 1)));

        if(((usBackValue / _MENU_3RD_ITEM_MAX) * _MENU_3RD_ITEM_MAX) != ((g_stOsdItemData.usAdjValue / _MENU_3RD_ITEM_MAX) * _MENU_3RD_ITEM_MAX))
        {
            OsdMenu3rdFrame();
            if(((g_stOsdItemData.usAdjValueMax - g_stOsdItemData.usAdjValueMin + 1) - (((g_stOsdItemData.usAdjValue - g_stOsdItemData.usAdjValueMin) / _MENU_3RD_ITEM_MAX) * _MENU_3RD_ITEM_MAX)) < _MENU_3RD_ITEM_MAX)
            {
                usItemMax = ((g_stOsdItemData.usAdjValueMax - g_stOsdItemData.usAdjValueMin + 1) % _MENU_3RD_ITEM_MAX);
            }
            else
            {
                usItemMax = _MENU_3RD_ITEM_MAX;
            }

            for (ucLoop = 0; ucLoop < usItemMax; ucLoop++)
            {
                ucCPColor = (OsdDisp3rdItemCheck(enumOsdItem, (ucLoop + (((g_stOsdItemData.usAdjValue - g_stOsdItemData.usAdjValueMin) / _MENU_3RD_ITEM_MAX) * _MENU_3RD_ITEM_MAX)))) ? _CP_WHITE : _CP_GRAY;
                SET_OSD_INFO_STRING_MODE(_PUT_STRING_CENTER);
                SET_OSD_INFO_STRING_MODE_LENGTH(_MENU_3RD_ITEM_LIST_WIDTH);

                if(g_stOsdItemData.usSubStringIdx == _STRING_A0_PORT)
                {
                    OsdPropPutString(ROW(_MENU_3RD_ITEM_ROW_ST + ucLoop * 2), COL(_MENU_3RD_ITEM_LIST_ST), _PFONT_PAGE_2, g_stOsdItemData.usSubStringIdx + (((g_stOsdItemData.usAdjValue - g_stOsdItemData.usAdjValueMin) / _MENU_3RD_ITEM_MAX) * _MENU_3RD_ITEM_MAX) + ucLoop, COLOR(ucCPColor, _CP_BG), _ENGLISH);
                }
                else
                {
                    OsdPropPutString(ROW(_MENU_3RD_ITEM_ROW_ST + ucLoop * 2), COL(_MENU_3RD_ITEM_LIST_ST), _PFONT_PAGE_2, g_stOsdItemData.usSubStringIdx + (((g_stOsdItemData.usAdjValue - g_stOsdItemData.usAdjValueMin) / _MENU_3RD_ITEM_MAX) * _MENU_3RD_ITEM_MAX) + ucLoop, COLOR(ucCPColor, _CP_BG), GET_OSD_LANGUAGE());
                }
            }
        }

        OsdDispSubMenuListCursor((g_stOsdItemData.usAdjValue - g_stOsdItemData.usAdjValueMin));
    }
    else
    {
        if(((g_stOsdItemData.usAdjValueMax - g_stOsdItemData.usAdjValueMin + 1) - (((g_stOsdItemData.usAdjValue - g_stOsdItemData.usAdjValueMin) / _MENU_3RD_ITEM_MAX) * _MENU_3RD_ITEM_MAX)) < _MENU_3RD_ITEM_MAX)
        {
            usItemMax = ((g_stOsdItemData.usAdjValueMax - g_stOsdItemData.usAdjValueMin + 1) % _MENU_3RD_ITEM_MAX);
        }
        else
        {
            usItemMax = _MENU_3RD_ITEM_MAX;
        }

        for(ucLoop = 0; ucLoop < usItemMax; ucLoop++)
        {
            ucCPColor = (OsdDisp3rdItemCheck(enumOsdItem, (ucLoop + (((g_stOsdItemData.usAdjValue - g_stOsdItemData.usAdjValueMin) / _MENU_3RD_ITEM_MAX) * _MENU_3RD_ITEM_MAX)))) ? _CP_WHITE : _CP_GRAY;
            SET_OSD_INFO_STRING_MODE(_PUT_STRING_CENTER);
            SET_OSD_INFO_STRING_MODE_LENGTH(_MENU_3RD_ITEM_LIST_WIDTH);
            if(g_stOsdItemData.usSubStringIdx == _STRING_A0_PORT)
            {
                OsdPropPutString(ROW(_MENU_3RD_ITEM_ROW_ST + ucLoop * 2), COL(_MENU_3RD_ITEM_LIST_ST), _PFONT_PAGE_2, g_stOsdItemData.usSubStringIdx + (((g_stOsdItemData.usAdjValue - g_stOsdItemData.usAdjValueMin) / _MENU_3RD_ITEM_MAX) * _MENU_3RD_ITEM_MAX) + ucLoop, COLOR(ucCPColor, _CP_BG), _ENGLISH);
            }
            else
            {
                OsdPropPutString(ROW(_MENU_3RD_ITEM_ROW_ST + ucLoop * 2), COL(_MENU_3RD_ITEM_LIST_ST), _PFONT_PAGE_2, g_stOsdItemData.usSubStringIdx + (((g_stOsdItemData.usAdjValue - g_stOsdItemData.usAdjValueMin) / _MENU_3RD_ITEM_MAX) * _MENU_3RD_ITEM_MAX) + ucLoop, COLOR(ucCPColor, _CP_BG), GET_OSD_LANGUAGE());
            }
        }

        OsdDispSubMenuListCursor((g_stOsdItemData.usAdjValue - g_stOsdItemData.usAdjValueMin));
    }

    g_usAdjustValue = g_stOsdItemData.usAdjValue;
}

//--------------------------------------------------
// Description  :  you must call "OsdDispItemValueUpdate(enumOsdItem); " function before
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdDispHotKeyMenuListItemAdj(bit bitbAdjShow)
{
    BYTE ucLoop = 0;
    WORD usItemMax = 0;
    BYTE ucCPColor = _CP_WHITE;
    StructOsdItemDataType stBackValue;

    stBackValue = g_stOsdItemData;
    if(bitbAdjShow == _ON)
    {
        stBackValue.usAdjValue = (OsdDisplayDetOverRange(stBackValue.usAdjValue, stBackValue.usAdjValueMax, stBackValue.usAdjValueMin, _ON));

        ucLoop = 0;
        while((OsdDisp2ndMenuCheck(stBackValue.usAdjValue) != _TRUE) && (ucLoop < (stBackValue.usAdjValueMax - stBackValue.usAdjValueMin + 1)))
        {
            stBackValue.usAdjValue = (OsdDisplayDetOverRange(stBackValue.usAdjValue, stBackValue.usAdjValueMax, stBackValue.usAdjValueMin, _ON));
            ucLoop++;
        }

        if(((g_stOsdItemData.usAdjValue / _MENU_3RD_ITEM_MAX) * _MENU_3RD_ITEM_MAX) != ((stBackValue.usAdjValue / _MENU_3RD_ITEM_MAX) * _MENU_3RD_ITEM_MAX))
        {
            OsdMenu3rdFrame();
            if(((stBackValue.usAdjValueMax - stBackValue.usAdjValueMin + 1) - (((stBackValue.usAdjValue - stBackValue.usAdjValueMin) / _MENU_3RD_ITEM_MAX) * _MENU_3RD_ITEM_MAX)) < _MENU_3RD_ITEM_MAX)
            {
                usItemMax = ((stBackValue.usAdjValueMax - stBackValue.usAdjValueMin + 1) % _MENU_3RD_ITEM_MAX);
            }
            else
            {
                usItemMax = _MENU_3RD_ITEM_MAX;
            }

            for (ucLoop = 0; ucLoop < usItemMax; ucLoop++)
            {
                ucCPColor = (OsdDisp2ndMenuCheck((ucLoop + (((stBackValue.usAdjValue - stBackValue.usAdjValueMin) / _MENU_3RD_ITEM_MAX) * _MENU_3RD_ITEM_MAX) + stBackValue.usAdjValueMin))) ? _CP_WHITE : _CP_GRAY;
                SET_OSD_INFO_STRING_MODE(_PUT_STRING_CENTER);
                SET_OSD_INFO_STRING_MODE_LENGTH(_MENU_3RD_ITEM_LIST_WIDTH);
                OsdDispItemValueUpdate(((ucLoop + (((stBackValue.usAdjValue - stBackValue.usAdjValueMin) / _MENU_3RD_ITEM_MAX) * _MENU_3RD_ITEM_MAX)) + stBackValue.usAdjValueMin));
                OsdPropPutString(ROW(_MENU_3RD_ITEM_ROW_ST + ucLoop * 2), COL(_MENU_3RD_ITEM_LIST_ST), _PFONT_PAGE_2, g_stOsdItemData.usStringIdx, COLOR(ucCPColor, _CP_BG), GET_OSD_LANGUAGE());
            }
        }

        OsdDispSubMenuListCursor((stBackValue.usAdjValue - stBackValue.usAdjValueMin));
    }
    else
    {
        if(((stBackValue.usAdjValueMax - stBackValue.usAdjValueMin + 1) - (((stBackValue.usAdjValue - stBackValue.usAdjValueMin) / _MENU_3RD_ITEM_MAX) * _MENU_3RD_ITEM_MAX)) < _MENU_3RD_ITEM_MAX)
        {
            usItemMax = ((stBackValue.usAdjValueMax - stBackValue.usAdjValueMin + 1) % _MENU_3RD_ITEM_MAX);
        }
        else
        {
            usItemMax = _MENU_3RD_ITEM_MAX;
        }

        for(ucLoop = 0; ucLoop < usItemMax; ucLoop++)
        {
            ucCPColor = (OsdDisp2ndMenuCheck((ucLoop + (((stBackValue.usAdjValue - stBackValue.usAdjValueMin) / _MENU_3RD_ITEM_MAX) * _MENU_3RD_ITEM_MAX) + stBackValue.usAdjValueMin))) ? _CP_WHITE : _CP_GRAY;
            SET_OSD_INFO_STRING_MODE(_PUT_STRING_CENTER);
            SET_OSD_INFO_STRING_MODE_LENGTH(_MENU_3RD_ITEM_LIST_WIDTH);
            OsdDispItemValueUpdate(((ucLoop + (((stBackValue.usAdjValue - stBackValue.usAdjValueMin) / _MENU_3RD_ITEM_MAX) * _MENU_3RD_ITEM_MAX)) + stBackValue.usAdjValueMin));
            OsdPropPutString(ROW(_MENU_3RD_ITEM_ROW_ST + ucLoop * 2), COL(_MENU_3RD_ITEM_LIST_ST), _PFONT_PAGE_2, g_stOsdItemData.usStringIdx, COLOR(ucCPColor, _CP_BG), GET_OSD_LANGUAGE());
        }

        OsdDispSubMenuListCursor((stBackValue.usAdjValue - stBackValue.usAdjValueMin));
    }

    g_usAdjustValue = stBackValue.usAdjValue;
    g_stOsdItemData = stBackValue;
}

//--------------------------------------------------
// Description  :  you must call "OsdDispItemValueUpdate(enumOsdItem); " function before
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdDisp4thListItemAdj(bit bitbAdjShow)
{
    BYTE ucLoop = 0;
    WORD usItemMax = 0;
    BYTE ucCPColor = _CP_WHITE;
    WORD usBackValue = g_stOsdItemData.usAdjValue;

    if(g_stOsdItemData.b3ShowType != _ADJ_LIST)
    {
        return;
    }

    if(bitbAdjShow == _ON)
    {
        g_stOsdItemData.usAdjValue = (OsdDisplayDetOverRange(g_stOsdItemData.usAdjValue, g_stOsdItemData.usAdjValueMax, g_stOsdItemData.usAdjValueMin, _ON));

        if(((usBackValue / _MENU_4TH_ITEM_MAX) * _MENU_4TH_ITEM_MAX) != ((g_stOsdItemData.usAdjValue / _MENU_4TH_ITEM_MAX) * _MENU_4TH_ITEM_MAX))
        {
            OsdMenu3rdFrame();
            OsdDisp4thMenuTitle();
            if(((g_stOsdItemData.usAdjValueMax - g_stOsdItemData.usAdjValueMin + 1) - (((g_stOsdItemData.usAdjValue - g_stOsdItemData.usAdjValueMin) / _MENU_4TH_ITEM_MAX) * _MENU_4TH_ITEM_MAX)) < _MENU_4TH_ITEM_MAX)
            {
                usItemMax = ((g_stOsdItemData.usAdjValueMax - g_stOsdItemData.usAdjValueMin + 1) % _MENU_4TH_ITEM_MAX);
            }
            else
            {
                usItemMax = _MENU_4TH_ITEM_MAX;
            }

            for (ucLoop = 0; ucLoop < usItemMax; ucLoop++)
            {
                ucCPColor = _CP_WHITE;
                SET_OSD_INFO_STRING_MODE(_PUT_STRING_CENTER);
                SET_OSD_INFO_STRING_MODE_LENGTH(_MENU_4TH_ITEM_LIST_WIDTH);
                OsdPropPutString(ROW(_MENU_4TH_ITEM_ROW_ST + ucLoop * 2), COL(_MENU_4TH_ITEM_LIST_ST), _PFONT_PAGE_2, g_stOsdItemData.usSubStringIdx + (((g_stOsdItemData.usAdjValue - g_stOsdItemData.usAdjValueMin) / _MENU_4TH_ITEM_MAX) * _MENU_4TH_ITEM_MAX) + ucLoop, COLOR(ucCPColor, _CP_BG), GET_OSD_LANGUAGE());
            }
        }

        OsdDispSubMenu4thListCursor((g_stOsdItemData.usAdjValue - g_stOsdItemData.usAdjValueMin));
    }
    else
    {
        if(((g_stOsdItemData.usAdjValueMax - g_stOsdItemData.usAdjValueMin + 1) - (((g_stOsdItemData.usAdjValue - g_stOsdItemData.usAdjValueMin) / _MENU_4TH_ITEM_MAX) * _MENU_4TH_ITEM_MAX)) < _MENU_4TH_ITEM_MAX)
        {
            usItemMax = ((g_stOsdItemData.usAdjValueMax - g_stOsdItemData.usAdjValueMin + 1) % _MENU_4TH_ITEM_MAX);
        }
        else
        {
            usItemMax = _MENU_4TH_ITEM_MAX;
        }

        for(ucLoop = 0; ucLoop < usItemMax; ucLoop++)
        {
            ucCPColor = _CP_WHITE;
            SET_OSD_INFO_STRING_MODE(_PUT_STRING_CENTER);
            SET_OSD_INFO_STRING_MODE_LENGTH(_MENU_4TH_ITEM_LIST_WIDTH);
            OsdPropPutString(ROW(_MENU_4TH_ITEM_ROW_ST + ucLoop * 2), COL(_MENU_4TH_ITEM_LIST_ST), _PFONT_PAGE_2, g_stOsdItemData.usSubStringIdx + (((g_stOsdItemData.usAdjValue - g_stOsdItemData.usAdjValueMin) / _MENU_4TH_ITEM_MAX) * _MENU_4TH_ITEM_MAX) + ucLoop, COLOR(ucCPColor, _CP_BG), GET_OSD_LANGUAGE());
        }

        OsdDispSubMenu4thListCursor((g_stOsdItemData.usAdjValue - g_stOsdItemData.usAdjValueMin));
    }

    g_usAdjustValue = g_stOsdItemData.usAdjValue;
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdDispSubMenuListCursor(BYTE ucIdex)
{
    ucIdex = (ucIdex % _MENU_3RD_ITEM_MAX);

    OsdWindowDrawing(_OSD_WIN_HIGHLIGHT_4, ((_MENU_3RD_ITEM_LIST_ST) * 12), ((_MENU_3RD_ITEM_ROW_ST + ucIdex * 2) * 18 - 9), (((_MENU_3RD_ITEM_LIST_ST) + _MENU_3RD_ITEM_LIST_WIDTH) * 12), ((_MENU_3RD_ITEM_ROW_ST + ucIdex * 2 + 1) * 18 + 9), _CP_ORANGE);

    UserCommonOsdWindowHighlightFunction(_ENABLE, _OSD_WIN_HIGHLIGHT_4, _CP_BLUE, _CP_ORANGE, _CP_BLUE);
}
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdDispSubMenu4thListCursor(BYTE ucIdex)
{
    ucIdex = (ucIdex % _MENU_4TH_ITEM_MAX);

    OsdWindowDrawing(_OSD_WIN_HIGHLIGHT_4, ((_MENU_4TH_ITEM_LIST_ST) * 12), ((_MENU_4TH_ITEM_ROW_ST + ucIdex * 2) * 18 - 9), (((_MENU_4TH_ITEM_LIST_ST) + _MENU_4TH_ITEM_LIST_WIDTH) * 12), ((_MENU_4TH_ITEM_ROW_ST + ucIdex * 2 + 1) * 18 + 9), _CP_ORANGE);

    UserCommonOsdWindowHighlightFunction(_ENABLE, _OSD_WIN_HIGHLIGHT_4, _CP_BLUE, _CP_ORANGE, _CP_BLUE);
}

//--------------------------------------------------
// Description    :
// Input Value    : _ON: adj & show , OFF: only show
// Output Value : None
//--------------------------------------------------
void OsdDisp3rdMenuAdjorShow(WORD usOsdState, WORD usValue, bit bitbAdjShow)
{
    g_usAdjustValue = usValue;

    switch(usOsdState)
    {
        //==> Picture Item
        case _MENU_DISPLAYMODE:
            OsdDisp3rdItemAdj(_OSD_MUTIP_MODE, bitbAdjShow);
            break;
        case _MENU_SELECTREGIOM:
            OsdDisp3rdItemAdj(_OSD_MUTIP_SELECTREGION, bitbAdjShow);
            break;
        case _MENU_DISPLAYFUN_LR_RATIO_ADJUST:
            OsdDisp3rdItemAdj(_OSD_MUTIP_LR_RATIO, bitbAdjShow);
            break;
        case _MENU_DISPLAYFUN_PIP_POSITION_ADJUST:
            OsdDisp3rdItemAdj(_OSD_MUTIP_PIP_POSITION, bitbAdjShow);
            break;
        case _MENU_DISPLAYFUN_PIP_POSITION_USER:
            OsdDisp3rdItemAdj(_OSD_MUTIP_PIP_POSITION_USER, bitbAdjShow);
            break;
        case _MENU_DISPLAYFUN_PIP_POSITION_H_ADJUST:
            OsdDisp3rdBartemAdj(bitbAdjShow);
            break;
        case _MENU_DISPLAYFUN_PIP_POSITION_V_ADJUST:
            OsdDisp3rdBartemAdj(bitbAdjShow);
            break;
        case _MENU_DISPLAYFUN_PIP_TRANSPARENCY_ADJUST:
            OsdDisp3rdItemAdj(_OSD_MUTIP_PIP_TRANSPARENCY, bitbAdjShow);
            break;
        case _MENU_DISPLAYFUN_PIP_SIZE_ADJUST:
            OsdDisp3rdItemAdj(_OSD_MUTIP_PIP_SIZE, bitbAdjShow);
            break;

        //==> Picture Item
        case _MENU_PICTURE_BACKLIGHT_ADJUST:
            OsdDisp3rdItemAdj(_OSD_PICTURE_BACKLIGHT, bitbAdjShow);
            break;

        case _MENU_PICTURE_BRIGHTNESS_ADJUST:
            OsdDisp3rdItemAdj(_OSD_PICTURE_BRIGHTNESS, bitbAdjShow);
            break;

        case _MENU_PICTURE_CONTRAST_ADJUST:
            OsdDisp3rdItemAdj(_OSD_PICTURE_CONTRAST, bitbAdjShow);
            break;

        case _MENU_PICTURE_SHARPNESS_ADJUST:
            OsdDisp3rdItemAdj(_OSD_PICTURE_SHARNESS, bitbAdjShow);
            break;
// Display Item
#if(_VGA_SUPPORT == _ON)

        case _MENU_ANALOG_HPOS_ADJUST:
            OsdDisp3rdItemAdj(_OSD_DISPLAY_HPOS, bitbAdjShow);
            break;
        case _MENU_ANALOG_VPOS_ADJUST:
            OsdDisp3rdItemAdj(_OSD_DISPLAY_VPOS, bitbAdjShow);
            break;
        case _MENU_ANALOG_CLOCK_ADJUST:
            OsdDisp3rdItemAdj(_OSD_DISPLAY_CLOCK, bitbAdjShow);
            break;
        case _MENU_ANALOG_PHASE_ADJUST:
            OsdDisp3rdItemAdj(_OSD_DISPLAY_PHASE, bitbAdjShow);
            break;
#endif

        case _MENU_DISPLAYFUN_DISP_ROTATE_ADJUST:
            OsdDisp3rdItemAdj(_OSD_DISPLAY_DISP_ROTATE, bitbAdjShow);
            break;
        case _MENU_DISPLAYFUN_LATENCY_ADJUST:
            OsdDisp3rdItemAdj(_OSD_DISPLAY_LATENCY, bitbAdjShow);
            break;
        case _MENU_DISPLAYFUN_FREEZE_ADJUST:
            OsdDisp3rdItemAdj(_OSD_DISPLAY_FREEZE, bitbAdjShow);
            break;
        case _MENU_COLOR_PANEL_UNIFORMITY_ADJUST:
            OsdDisp3rdItemAdj(_OSD_COLOR_PANEL_UNIFORMITY, bitbAdjShow);
            break;
        case _MENU_COLOR_GAMMA_ADJUST:
            OsdDisp3rdItemAdj(_OSD_COLOR_GAMMA, bitbAdjShow);
            break;
        case _MENU_COLOR_TEMPERATURE_ADJUST:
            OsdDisp3rdItemAdj(_OSD_COLOR_TEMPERATURE, bitbAdjShow);
            break;
        case _MENU_COLOR_TEMP_USER_R:
        case _MENU_COLOR_TEMP_USER_G:
        case _MENU_COLOR_TEMP_USER_B:
            OsdDisp3rdItemAdj(_OSD_COLOR_TEMP_USER, bitbAdjShow);
            break;
        case _MENU_COLOR_EFFECT_ADJUST:
            OsdDisp3rdItemAdj(_OSD_COLOR_EFFECT, bitbAdjShow);
            break;
        case _MENU_COLOR_EFF_USER_R_HUE:
        case _MENU_COLOR_EFF_USER_R_SAT:
        case _MENU_COLOR_EFF_USER_Y_HUE:
        case _MENU_COLOR_EFF_USER_Y_SAT:
        case _MENU_COLOR_EFF_USER_G_HUE:
        case _MENU_COLOR_EFF_USER_G_SAT:
        case _MENU_COLOR_EFF_USER_C_HUE:
        case _MENU_COLOR_EFF_USER_C_SAT:
        case _MENU_COLOR_EFF_USER_B_HUE:
        case _MENU_COLOR_EFF_USER_B_SAT:
        case _MENU_COLOR_EFF_USER_M_HUE:
        case _MENU_COLOR_EFF_USER_M_SAT:
            OsdDisp3rdItemAdj(_OSD_COLOR_EFFECT_USER, bitbAdjShow);
            break;
#if(_ICM_CHAMELEON_FUNCTION == _ON)
        case _MENU_COLOR_CHAMELEON_HUE:
        case _MENU_COLOR_CHAMELEON_SAT:
        case _MENU_COLOR_CHAMELEON_LIGHTNESS:
            OsdDisp3rdItemAdj(_OSD_COLOR_CHAMELEON_USER, bitbAdjShow);
            break;
#endif
        case _MENU_COLOR_DEMO_ADJUST:
            OsdDisp3rdItemAdj(_OSD_COLOR_DEMO, bitbAdjShow);
            break;
        case _MENU_COLOR_DEMO_SIDE_ADJUST:
            OsdDisp3rdItemAdj(_OSD_COLOR_DEMO_SIDE, bitbAdjShow);
            break;
        case _MENU_COLOR_FORMAT_ADJUST:
            OsdDisp3rdItemAdj(_OSD_COLOR_FORMAT, bitbAdjShow);
            break;
        case _MENU_COLOR_PCM_ADJUST:
            OsdDisp3rdItemAdj(_OSD_COLOR_PCM, bitbAdjShow);
            break;
        case _MENU_COLOR_HUE_ADJUST:
            OsdDisp3rdItemAdj(_OSD_COLOR_HUE, bitbAdjShow);
            break;
        case _MENU_COLOR_SATURATION_ADJUST:
            OsdDisp3rdItemAdj(_OSD_COLOR_SATURATION, bitbAdjShow);
            break;
#if(_DYNAMIC_LOWBLUE_FUNCTION == _ON)
        case _MENU_COLOR_EYE_PROTECT_ADJUST:
        case _MENU_COLOR_EYE_PROTECT_MODE_ADJUST:
        case _MENU_COLOR_EYE_PROTECT_LEVEL_ADJUST:
        case _MENU_COLOR_EYE_PROTECT_TIME_ADJUST:
            OsdDisp3rdItemAdj(_OSD_COLOR_EYE_PROTECT, bitbAdjShow);
            break;
#endif
        //==> Advance
        case _MENU_ADVANCE_ASPECT_ADJUST:
            OsdDisp3rdItemAdj(_OSD_ADVANCE_ASPECT, bitbAdjShow);
            break;
        case _MENU_ADVANCE_OVER_SCAN_ADJUST:
            OsdDisp3rdItemAdj(_OSD_ADVANCE_OVERSCAN, bitbAdjShow);
            break;
        case _MENU_ADVANCE_DDCCI_ADJUST:
            OsdDisp3rdItemAdj(_OSD_ADVANCE_DDCCI, bitbAdjShow);
            break;
        case _MENU_ADVANCE_DCR_ADJUST:
            OsdDisp3rdItemAdj(_OSD_ADVANCE_DCR, bitbAdjShow);
            break;
        case _MENU_ADVANCE_ULTRA_VIVID_ADJUST:
            OsdDisp3rdItemAdj(_OSD_ADVANCE_ULTRAVIVID, bitbAdjShow);
            break;

        case _MENU_ADVANCE_DP_MST_ADJUST:
            OsdDisp3rdItemAdj(_OSD_ADVANCE_DPMST, bitbAdjShow);
            break;
        case _MENU_ADVANCE_DP_OPTION_D0:
        case _MENU_ADVANCE_DP_OPTION_D1:
        case _MENU_ADVANCE_DP_OPTION_D2:
        case _MENU_ADVANCE_DP_OPTION_D6:
            OsdDisp3rdItemAdj(_OSD_ADVANCE_DPOPTION, bitbAdjShow);
            break;

        case _MENU_ADVANCE_EDID_ADJUST:
            OsdDisp3rdItemAdj(_OSD_ADVANCE_DP_RESOLUTION, bitbAdjShow);
            break;
        case _MENU_ADVANCE_TYPEC_MODE_D0:
        case _MENU_ADVANCE_TYPEC_MODE_D1:
        case _MENU_ADVANCE_TYPEC_MODE_D2:
        case _MENU_ADVANCE_TYPEC_MODE_D6:
            OsdDisp3rdItemAdj(_OSD_ADVANCE_TYPEC_MODE, bitbAdjShow);
            break;

        case _MENU_ADVANCE_HDMI_VERSION_ADJUST:
            OsdDisp3rdItemAdj(_OSD_ADVANCE_HDMI_VERSIONS, bitbAdjShow);
            break;

        case _MENU_ADVANCE_FREESYNC_ADJUST:
            OsdDisp3rdItemAdj(_OSD_ADVANCE_FREESYNC, bitbAdjShow);
            break;

        case _MENU_ADVANCE_CLONE_ADJUST:
            OsdDisp3rdItemAdj(_OSD_ADVANCE_CLONE, bitbAdjShow);
            break;
        case _MENU_ADVANCE_PIXEL_SHIFT_ADJUST:
            OsdDisp3rdItemAdj(_OSD_ADVANCE_PIXELSHIFT, bitbAdjShow);
            break;
        case _MENU_ADVANCE_SDR_TO_HDR_ADJUST:
            OsdDisp3rdItemAdj(_OSD_ADVANCE_SDR_TO_HDR, bitbAdjShow);
            break;
        case _MENU_ADVANCE_OD_GAIN_ADJUST:
            OsdDisp3rdItemAdj(_OSD_ADVANCE_OVERDRIVE, bitbAdjShow);
            break;
        case _MENU_ADVANCE_LOCAL_CONTRAST_ADJUST:
            OsdDisp3rdItemAdj(_OSD_ADVANCE_LOCAL_CONTRAST, bitbAdjShow);
            break;
        case _MENU_ADVANCE_LOCAL_CONTRAST_USER:
            OsdDisp3rdItemAdj(_OSD_ADVANCE_LOCAL_CONTRAST_USER, bitbAdjShow);
            break;
        case _MENU_ADVANCE_LOCAL_CONTRAST_BLENDING:
            OsdDisp3rdBartemAdj(bitbAdjShow);
            break;
        case _MENU_ADVANCE_LOCAL_CONTRAST_DIFFGAIN:
            OsdDisp3rdBartemAdj(bitbAdjShow);
            break;
        case _MENU_ADVANCE_DUAL_DP_EDID_ADJUST:
            OsdDisp3rdItemAdj(_OSD_ADVANCE_DUAL_DP_EDID, bitbAdjShow);
            break;
        case _MENU_ADVANCE_DSC_ADJUST:
            OsdDisp3rdItemAdj(_OSD_ADVANCE_DSC, bitbAdjShow);
            break;
        case _MENU_ADVANCE_EAGLE_SIGHT_ADJUST:
            OsdDisp3rdItemAdj(_OSD_ADVANCE_EAGLE_SIGHT, bitbAdjShow);
            break;
        case _MENU_ADVANCE_MBR_ADJUST:
            OsdDisp3rdItemAdj(_OSD_ADVANCE_MBR, bitbAdjShow);
            break;
        case _MENU_ADVANCE_DP_AUXLESS_ALPM_ADJUST:
            OsdDisp3rdItemAdj(_OSD_ADVANCE_DP_AUXLESS_ALPM, bitbAdjShow);
            break;
        case _MENU_ADVANCE_DP_ADAPTIVESYNC:
            OsdDisp3rdItemAdj(_OSD_ADVANCE_DP_ADAPTIVESYNC, bitbAdjShow);
            break;
        case _MENU_ADVANCE_PANEL_REPLAYM_ADJUST:
            OsdDisp3rdItemAdj(_OSD_ADVANCE_PANEL_REPLAY, bitbAdjShow);
            break;
        case _MENU_ADVANCE_SDR_PLUS:
            OsdDisp3rdItemAdj(_OSD_ADVANCE_SDR_PLUS, bitbAdjShow);
            break;
        case _MENU_ADVANCE_SDR_PLUS_SELECT:
            OsdDisp3rdItemAdj(_OSD_ADVANCE_SDR_PLUS_ADJ, bitbAdjShow);
            break;
        case _MENU_ADVANCE_SDR_PLUS_SHARP:
            OsdDisp3rdItemAdj(_OSD_ADVANCE_SDR_PLUS_SHARP, bitbAdjShow);
            break;
        case _MENU_ADVANCE_SDR_PLUS_DARK:
            OsdDisp3rdItemAdj(_OSD_ADVANCE_SDR_PLUS_DARK, bitbAdjShow);
            break;
        case _MENU_ADVANCE_ANTI_ALIASING:
        case _MENU_ADVANCE_ANTI_ALIASING_MODE_ADJ:
        case _MENU_ADVANCE_ANTI_ALIASING_LEVEL_ADJ:
            OsdDisp3rdItemAdj(_OSD_ADVANCE_ANTI_ALIASING, bitbAdjShow);
            break;
        case _MENU_ADVANCE_ENERGY_SAVER:
            OsdDisp3rdItemAdj(_OSD_ADVANCE_ENERGY_SAVE, bitbAdjShow);
            break;
#if(_IMMERSIVE_NIGHT_SNIPER_FUNCTION == _ON)
        case _MENU_ADVANCE_NIGHT_SNIPER:
            OsdDisp3rdItemAdj(_OSD_ADVANCE_NIGHT_SNIPER, bitbAdjShow);
            break;
        case _MENU_ADVANCE_NIGHT_SNIPER_ADJUST:
            OsdDisp3rdItemAdj(_OSD_ADVANCE_NIGHT_SNIPER_ADJUST, bitbAdjShow);
            break;
        case _MENU_ADVANCE_NIGHT_SNIPER_SATURATION:
            OsdDisp3rdItemAdj(_OSD_ADVANCE_NIGHT_SNIPER_SATURATION, bitbAdjShow);
            break;
        case _MENU_ADVANCE_NIGHT_SNIPER_LIGHTNESS:
            OsdDisp3rdItemAdj(_OSD_ADVANCE_NIGHT_SNIPER_LIGHTNESS, bitbAdjShow);
            break;
#endif

        //==> Audio
        case _MENU_AUDIO_VOLUME_ADJUST:
            OsdDisp3rdItemAdj(_OSD_AUDIO_VOLUME, bitbAdjShow);
            break;
        case _MENU_AUDIO_MUTE_ON_OFF:
            OsdDisp3rdItemAdj(_OSD_AUDIO_MUTE, bitbAdjShow);
            break;
        case _MENU_AUDIO_STAND_ALONG_SELECT:
            OsdDisp3rdItemAdj(_OSD_AUDIO_STAND_ALONG, bitbAdjShow);
            break;

        case _MENU_AUDIO_AUDIO_SOURCE_SELECT:
            OsdDisp3rdItemAdj(_OSD_AUDIO_AUDIO_SOURCE, bitbAdjShow);
            break;
        case _MENU_AUDIO_AUDIO_SELF_TEST_SELECT:
            OsdDisp3rdItemAdj(_OSD_AUDIO_AUDIO_SELF_TEST, bitbAdjShow);
            break;
        case _MENU_AUDIO_SOUND_MODE_SELECT:
            break;

#if(_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE)
        case _MENU_TTS_FUNCTION:
            OsdDisp3rdItemAdj(_OSD_TTS_FUNCTION, bitbAdjShow);
            break;
        case _MENU_TTS_TEXT_VOLUME:
            OsdDisp3rdItemAdj(_OSD_TTS_TEXT_VOLUME, bitbAdjShow);
            break;
        case _MENU_TTS_AUDIO_VOLUME:
            OsdDisp3rdItemAdj(_OSD_TTS_AUDIO_VOLUME, bitbAdjShow);
            break;
#endif // End of #if(_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE)

        case _MENU_OTHER_MENU_TIME_ADJUST:
            OsdDisp3rdItemAdj(_OSD_OTHER_MENU_TIME, bitbAdjShow);
            break;

        case _MENU_OTHER_OSD_HPOS_ADJUST:
            OsdDisp3rdItemAdj(_OSD_OTHER_OSD_HPOS, bitbAdjShow);
            break;

        case _MENU_OTHER_OSD_VPOS_ADJUST:
            OsdDisp3rdItemAdj(_OSD_OTHER_OSD_VPOS, bitbAdjShow);
            break;

        case _MENU_OTHER_LANGUAGE_ADJUST:
            OsdDisp3rdItemAdj(_OSD_OTHER_LANGUAGE, bitbAdjShow);
            break;


        case _MENU_OTHER_TRNASPARENCY_ADJUST:
            OsdDisp3rdItemAdj(_OSD_OTHER_TRNASPARENCY, bitbAdjShow);
            break;

        case _MENU_OTHER_ROTATE_ADJUST:
            OsdDisp3rdItemAdj(_OSD_OTHER_ROTATE, bitbAdjShow);
            break;

        case _MENU_OTHER_CROSSHAIR_ADJUST:
            OsdDisp3rdItemAdj(_OSD_OTHER_CROSSHAIR, bitbAdjShow);
            break;

//==Color Temp User
        case _MENU_COLOR_TEMP_USER_ADJUST_R:
        case _MENU_COLOR_TEMP_USER_ADJUST_G:
        case _MENU_COLOR_TEMP_USER_ADJUST_B:
            OsdDisp3rdItemAdj(_OSD_COLOR_TEMP_USER, bitbAdjShow);
            break;

        case _MENU_COLOR_EFF_USER_R_HUE_ADJUST:
        case _MENU_COLOR_EFF_USER_Y_HUE_ADJUST:
        case _MENU_COLOR_EFF_USER_G_HUE_ADJUST:
        case _MENU_COLOR_EFF_USER_C_HUE_ADJUST:
        case _MENU_COLOR_EFF_USER_B_HUE_ADJUST:
        case _MENU_COLOR_EFF_USER_M_HUE_ADJUST:
            OsdDisp3rdItemAdj(_OSD_COLOR_EFFECT_USER, bitbAdjShow);
            break;
        case _MENU_COLOR_EFF_USER_R_SAT_ADJUST:
        case _MENU_COLOR_EFF_USER_Y_SAT_ADJUST:
        case _MENU_COLOR_EFF_USER_G_SAT_ADJUST:
        case _MENU_COLOR_EFF_USER_C_SAT_ADJUST:
        case _MENU_COLOR_EFF_USER_B_SAT_ADJUST:
        case _MENU_COLOR_EFF_USER_M_SAT_ADJUST:
            OsdDisp3rdItemAdj(_OSD_COLOR_EFFECT_USER, bitbAdjShow);
            break;
#if(_ICM_CHAMELEON_FUNCTION == _ON)
        case _MENU_COLOR_CHAMELEON_HUE_ADJUST:
        case _MENU_COLOR_CHAMELEON_SAT_ADJUST:
        case _MENU_COLOR_CHAMELEON_LIGHTNESS_ADJUST:
            OsdDisp3rdItemAdj(_OSD_COLOR_CHAMELEON_USER, bitbAdjShow);
            break;
#endif

        case _MENU_ADVANCE_HDR_MODE_ADJUST:
            OsdDisp3rdItemAdj(_OSD_HDR_MODE, bitbAdjShow);
            break;

        case _MENU_ADVANCE_HDR_DARK_ENHANCE_ONOFF_ADJUST:
            OsdDisp3rdItemAdj(_OSD_HDR_DARK_ENHANCE, bitbAdjShow);
            break;
        case _MENU_ADVANCE_HDR_SHARPNESS_ONOFF_ADJUST:
            OsdDisp3rdItemAdj(_OSD_HDR_SHARP_ENHANCE, bitbAdjShow);
            break;

        case _MENU_ADVANCE_HDR_CONTRAST_ADJUST:
            OsdDisp3rdItemAdj(_OSD_HDR_CONTRAST, bitbAdjShow);
            break;
        case _MENU_ADVANCE_HDR_COLOR_ENHANCE_ADJUST:
            OsdDisp3rdItemAdj(_OSD_HDR_COLOR_ENHANCE, bitbAdjShow);
            break;
        case _MENU_ADVANCE_HDR_LIGHT_ENHANCE_ADJUST:
            OsdDisp3rdItemAdj(_OSD_HDR_LIGHT_ENHANCE, bitbAdjShow);
            break;
        case _MENU_ADVANCE_HDR_HLG_OOTF_ADJUST:
            OsdDisp3rdItemAdj(_OSD_HDR_HLG_OOTF, bitbAdjShow);
            break;
        case _MENU_ADVANCE_HDR_LD_ONOFF_ADJUST:
            OsdDisp3rdItemAdj(_OSD_ADVANCE_LOCALDIMMING, bitbAdjShow);
            break;
        case _MENU_ADVANCE_HDR_LD_SMOOTH_ADJ_ADJUST:
            OsdDisp3rdItemAdj(_OSD_ADVANCE_LOCALDIMMING_USER, bitbAdjShow);
            break;

        case _MENU_ADVANCE_GLOBAL_DIMMING_ADJUST:
            OsdDisp3rdItemAdj(_OSD_ADVANCE_GLOBAL_DIMMING, bitbAdjShow);
            break;

        case _MENU_ADVANCE_EAGLE_SIGHT_FUNCTION_ADJUST:
            OsdDisp4thItemAdj(bitbAdjShow);
            break;
        case _MENU_ADVANCE_EAGLE_SIGHT_REGION_ADJUST:
            OsdDisp4thItemAdj(bitbAdjShow);
            break;
        case _MENU_ADVANCE_EAGLE_SIGHT_TRANSPARENT_ADJUST:
            OsdDisp4thItemAdj(bitbAdjShow);
            break;
        case _MENU_ADVANCE_EAGLE_SIGHT_ZOOM_ADJUST:
            OsdDisp4thItemAdj(bitbAdjShow);
            break;
        case _MENU_ADVANCE_EAGLE_SIGHT_CAP_POSITION_ADJUST:
            OsdDisp4thItemAdj(bitbAdjShow);
            break;
        case _MENU_ADVANCE_EAGLE_SIGHT_DISP_POSITION_ADJUST:
            OsdDisp4thItemAdj(bitbAdjShow);
            break;
        case _MENU_ADVANCE_EAGLE_SIGHT_BORDER_ADJUST:
            OsdDisp4thItemAdj(bitbAdjShow);
            break;
#if(_EAGLE_SIGHT_CIRCLE_WIN_SUPPORT == _ON)
        case _MENU_ADVANCE_EAGLE_SIGHT_CIRCLEWIN_ADJUST:
            OsdDisp4thItemAdj(bitbAdjShow);
            break;
#endif
        case _MENU_ADVANCE_MBR_MODE_ADJUST:
            OsdDisp4thItemAdj(bitbAdjShow);
            break;
        case _MENU_ADVANCE_MBR_DUTY_ADJUST:
            OsdDisp4thItemAdj(bitbAdjShow);
            break;
        case _MENU_ADVANCE_MBR_POSITION_ADJUST:
            OsdDisp4thItemAdj(bitbAdjShow);
            break;

        case _MENU_INPUT_SOURCE_1P_ADJ:
            OsdDisp3rdItemAdj(_OSD_SOURCE_1P, bitbAdjShow);
            break;
        case _MENU_INPUT_SOURCE_2P_ADJ:
            OsdDisp3rdItemAdj(_OSD_SOURCE_2P, bitbAdjShow);
            break;
        case _MENU_INPUT_SOURCE_3P_ADJ:
            OsdDisp3rdItemAdj(_OSD_SOURCE_3P, bitbAdjShow);
            break;
        case _MENU_INPUT_SOURCE_4P_ADJ:
            OsdDisp3rdItemAdj(_OSD_SOURCE_4P, bitbAdjShow);
            break;

#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
        case _MENU_PXP_MST_ADJUST:
            OsdDisp3rdItemAdj(_OSD_MUTIP_PXP_MST, bitbAdjShow);
            break;
#endif

        case _MENU_EXIT_HOTKEY_ADJ:
            OsdDisp3rdItemAdj(_OSD_EXIT_HOTKEY, bitbAdjShow);
            break;

        case _MENU_ADVANCE_HUB_SWITCH_ADJUST:
            OsdDisp3rdItemAdj(_OSD_ADVANCE_HUB_SWITCH, bitbAdjShow);
            break;
#if(_DM_FUNCTION == _ON)
        case _MENU_OSD_DVISION:
            OsdDisp3rdItemAdj(_OSD_DVISION, bitbAdjShow);
            break;
        case _MENU_OSD_DVISION_PICTURE:
            OsdDisp3rdItemAdj(_OSD_DVISION_PICTURE, bitbAdjShow);
            break;
        case _MENU_OSD_DVISION_BACKLIGHT:
            OsdDisp3rdItemAdj(_OSD_DVISION_BACKLIGHT, bitbAdjShow);
            break;
        case _MENU_OSD_DVISION_BRIGHTNESS:
            OsdDisp3rdItemAdj(_OSD_DVISION_BRIGHTNESS, bitbAdjShow);
            break;
        case _MENU_OSD_DVISION_CONTRAST:
            OsdDisp3rdItemAdj(_OSD_DVISION_CONTRAST, bitbAdjShow);
            break;
        case _MENU_OSD_DVISION_SATURATION:
            OsdDisp3rdItemAdj(_OSD_DVISION_SATURATION, bitbAdjShow);
            break;
        case _MENU_OSD_DVISION_NOTIFICATION:
            OsdDisp3rdItemAdj(_OSD_DVISION_NOTIFICATION, bitbAdjShow);
            break;
#endif
#if(_AUDIO_ARC_SUPPORT == _ON)
        case _MENU_AUDIO_ARC_OUTPUT:
            OsdDisp3rdItemAdj(_OSD_AUDIO_ARC_OUTPUT, bitbAdjShow);
            break;
        case _MENU_AUDIO_ARC_INPUTPORT:
            OsdDisp3rdItemAdj(_OSD_AUDIO_ARC_INPUTPORT, bitbAdjShow);
            break;
        case _MENU_AUDIO_ARC_MODE:
            OsdDisp3rdItemAdj(_OSD_AUDIO_ARC_MODE, bitbAdjShow);
            break;
        case _MENU_AUDIO_ARC_MUTE:
            OsdDisp3rdItemAdj(_OSD_AUDIO_ARC_MUTE, bitbAdjShow);
            break;
        case _MENU_AUDIO_ARC_CHANEL:
            OsdDisp3rdItemAdj(_OSD_AUDIO_ARC_CHANEL, bitbAdjShow);
            break;
#endif
#if(_USB2_HOST_EHCI_MASS_STORGE_PROGRAM_SUPPORT == _ON)
        case _MENU_ADVANCE_FW_UPDATE:
            OsdDisp3rdItemAdj(_OSD_ADVANCE_FW_UPDATE, bitbAdjShow);
            break;
#endif
        //==>STEP 6//Add New Item adjust range Here!!!!!

        default:
            break;
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdDisp3rdMenuReDraw(WORD usOsdState)
{
    OsdWindowSliderDisable();
    UserCommonOsdWindowDisable(_OSD_WIN_HIGHLIGHT_5);
    OsdMenu3rdFrame();

    switch(usOsdState)
    {
        case _MENU_DISPLAYFUN_PIP_POSITION_USER:
            OsdDispItemValueUpdate(_OSD_MUTIP_PIP_POSITION_USER);
            SET_OSD_STATE(g_stOsdItemData.usSubOsdState);
            OsdDisp3rdItemAdj(_OSD_MUTIP_PIP_POSITION_USER, _OFF);
            break;
        case _MENU_COLOR_TEMP_USER_R:
            OsdDispItemValueUpdate(_OSD_COLOR_TEMP_USER);
            SET_OSD_STATE(_MENU_COLOR_TEMP_USER_R);
            g_stOsdItemData.usAdjValue = 0;
            OsdDisp3rdItemAdj(_OSD_COLOR_TEMP_USER, _OFF);
            break;
        case _MENU_COLOR_TEMP_USER_G:
            OsdDispItemValueUpdate(_OSD_COLOR_TEMP_USER);
            SET_OSD_STATE(_MENU_COLOR_TEMP_USER_G);
            g_stOsdItemData.usAdjValue = 1;
            OsdDisp3rdItemAdj(_OSD_COLOR_TEMP_USER, _OFF);
            break;
        case _MENU_COLOR_TEMP_USER_B:
            OsdDispItemValueUpdate(_OSD_COLOR_TEMP_USER);
            g_stOsdItemData.usAdjValue = 2;
            SET_OSD_STATE(_MENU_COLOR_TEMP_USER_B);
            OsdDisp3rdItemAdj(_OSD_COLOR_TEMP_USER, _OFF);
            break;

        case _MENU_COLOR_EFF_USER_R_HUE:
            OsdDispItemValueUpdate(_OSD_COLOR_EFFECT_USER);
            g_stOsdItemData.usAdjValue = 0;
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_R_HUE);
            OsdDisp3rdItemAdj(_OSD_COLOR_EFFECT_USER, _OFF);
            break;
        case _MENU_COLOR_EFF_USER_R_SAT:
            OsdDispItemValueUpdate(_OSD_COLOR_EFFECT_USER);
            g_stOsdItemData.usAdjValue = 1;
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_R_SAT);
            OsdDisp3rdItemAdj(_OSD_COLOR_EFFECT_USER, _OFF);
            break;
        case _MENU_COLOR_EFF_USER_Y_HUE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_Y_HUE);
            OsdDispItemValueUpdate(_OSD_COLOR_EFFECT_USER);
            g_stOsdItemData.usAdjValue = 2;
            OsdDisp3rdItemAdj(_OSD_COLOR_EFFECT_USER, _OFF);
            break;
        case _MENU_COLOR_EFF_USER_Y_SAT:
            OsdDispItemValueUpdate(_OSD_COLOR_EFFECT_USER);
            g_stOsdItemData.usAdjValue = 3;
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_Y_SAT);
            OsdDisp3rdItemAdj(_OSD_COLOR_EFFECT_USER, _OFF);
            break;
        case _MENU_COLOR_EFF_USER_G_HUE:
            OsdDispItemValueUpdate(_OSD_COLOR_EFFECT_USER);
            g_stOsdItemData.usAdjValue = 4;
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_G_HUE);
            OsdDisp3rdItemAdj(_OSD_COLOR_EFFECT_USER, _OFF);
            break;
        case _MENU_COLOR_EFF_USER_G_SAT:
            OsdDispItemValueUpdate(_OSD_COLOR_EFFECT_USER);
            g_stOsdItemData.usAdjValue = 5;
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_G_SAT);
            OsdDisp3rdItemAdj(_OSD_COLOR_EFFECT_USER, _OFF);
            break;
        case _MENU_COLOR_EFF_USER_C_HUE:
            OsdDispItemValueUpdate(_OSD_COLOR_EFFECT_USER);
            g_stOsdItemData.usAdjValue = 6;
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_C_HUE);
            OsdDisp3rdItemAdj(_OSD_COLOR_EFFECT_USER, _OFF);
            break;
        case _MENU_COLOR_EFF_USER_C_SAT:
            OsdDispItemValueUpdate(_OSD_COLOR_EFFECT_USER);
            g_stOsdItemData.usAdjValue = 7;
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_C_SAT);
            OsdDisp3rdItemAdj(_OSD_COLOR_EFFECT_USER, _OFF);
            break;
        case _MENU_COLOR_EFF_USER_B_HUE:
            OsdDispItemValueUpdate(_OSD_COLOR_EFFECT_USER);
            g_stOsdItemData.usAdjValue = 8;
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_B_HUE);
            OsdDisp3rdItemAdj(_OSD_COLOR_EFFECT_USER, _OFF);
            break;
        case _MENU_COLOR_EFF_USER_B_SAT:
            OsdDispItemValueUpdate(_OSD_COLOR_EFFECT_USER);
            g_stOsdItemData.usAdjValue = 9;
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_B_SAT);
            OsdDisp3rdItemAdj(_OSD_COLOR_EFFECT_USER, _OFF);
            break;
        case _MENU_COLOR_EFF_USER_M_HUE:
            OsdDispItemValueUpdate(_OSD_COLOR_EFFECT_USER);
            g_stOsdItemData.usAdjValue = 10;
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_M_HUE);
            OsdDisp3rdItemAdj(_OSD_COLOR_EFFECT_USER, _OFF);
            break;
        case _MENU_COLOR_EFF_USER_M_SAT:
            OsdDispItemValueUpdate(_OSD_COLOR_EFFECT_USER);
            g_stOsdItemData.usAdjValue = 11;
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_M_SAT);
            OsdDisp3rdItemAdj(_OSD_COLOR_EFFECT_USER, _OFF);
            break;

#if(_ICM_CHAMELEON_FUNCTION == _ON)
        case _MENU_COLOR_CHAMELEON_HUE:
            OsdDispItemValueUpdate(_OSD_COLOR_CHAMELEON_USER);
            g_stOsdItemData.usAdjValue = 0;
            SET_OSD_STATE(_MENU_COLOR_CHAMELEON_HUE);
            OsdDisp3rdItemAdj(_OSD_COLOR_CHAMELEON_USER, _OFF);
            break;
        case _MENU_COLOR_CHAMELEON_SAT:
            OsdDispItemValueUpdate(_OSD_COLOR_CHAMELEON_USER);
            g_stOsdItemData.usAdjValue = 1;
            SET_OSD_STATE(_MENU_COLOR_CHAMELEON_SAT);
            OsdDisp3rdItemAdj(_OSD_COLOR_CHAMELEON_USER, _OFF);
            break;
        case _MENU_COLOR_CHAMELEON_LIGHTNESS:
            OsdDispItemValueUpdate(_OSD_COLOR_CHAMELEON_USER);
            g_stOsdItemData.usAdjValue = 2;
            SET_OSD_STATE(_MENU_COLOR_CHAMELEON_LIGHTNESS);
            OsdDisp3rdItemAdj(_OSD_COLOR_CHAMELEON_USER, _OFF);
            break;
#endif
#if(_DYNAMIC_LOWBLUE_FUNCTION == _ON)
        case _MENU_COLOR_EYE_PROTECT_ADJUST:
            OsdDispItemValueUpdate(_OSD_COLOR_EYE_PROTECT);
            g_stOsdItemData.usAdjValue = (g_us4thItemNum);
            SET_OSD_STATE(g_stOsdItemData.usSubOsdState);
            OsdDisp3rdItemAdj(_OSD_COLOR_EYE_PROTECT, _OFF);
            break;
#endif
        case _MENU_ADVANCE_DP_OPTION_D0:
            OsdDispItemValueUpdate(_OSD_ADVANCE_DPOPTION);
            g_stOsdItemData.usAdjValue = 0;
            SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D0);
            OsdDisp3rdItemAdj(_OSD_ADVANCE_DPOPTION, _OFF);
            break;
        case _MENU_ADVANCE_DP_OPTION_D1:
            OsdDispItemValueUpdate(_OSD_ADVANCE_DPOPTION);
            g_stOsdItemData.usAdjValue = 1;
            SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D1);
            OsdDisp3rdItemAdj(_OSD_ADVANCE_DPOPTION, _OFF);
            break;
        case _MENU_ADVANCE_DP_OPTION_D2:
            OsdDispItemValueUpdate(_OSD_ADVANCE_DPOPTION);
            g_stOsdItemData.usAdjValue = 2;
            SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D2);
            OsdDisp3rdItemAdj(_OSD_ADVANCE_DPOPTION, _OFF);
            break;
        case _MENU_ADVANCE_DP_OPTION_D6:
            OsdDispItemValueUpdate(_OSD_ADVANCE_DPOPTION);
            g_stOsdItemData.usAdjValue = 3;
            SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D6);
            OsdDisp3rdItemAdj(_OSD_ADVANCE_DPOPTION, _OFF);
            break;
        case _MENU_ADVANCE_TYPEC_MODE_D0:
            OsdDispItemValueUpdate(_OSD_ADVANCE_TYPEC_MODE);
            g_stOsdItemData.usAdjValue = 0;
            SET_OSD_STATE(_MENU_ADVANCE_TYPEC_MODE_D0);
            OsdDisp3rdItemAdj(_OSD_ADVANCE_TYPEC_MODE, _OFF);
            break;
        case _MENU_ADVANCE_TYPEC_MODE_D1:
            OsdDispItemValueUpdate(_OSD_ADVANCE_TYPEC_MODE);
            g_stOsdItemData.usAdjValue = 1;
            SET_OSD_STATE(_MENU_ADVANCE_TYPEC_MODE_D1);
            OsdDisp3rdItemAdj(_OSD_ADVANCE_TYPEC_MODE, _OFF);
            break;
        case _MENU_ADVANCE_TYPEC_MODE_D2:
            OsdDispItemValueUpdate(_OSD_ADVANCE_TYPEC_MODE);
            g_stOsdItemData.usAdjValue = 2;
            SET_OSD_STATE(_MENU_ADVANCE_TYPEC_MODE_D2);
            OsdDisp3rdItemAdj(_OSD_ADVANCE_TYPEC_MODE, _OFF);
            break;
        case _MENU_ADVANCE_TYPEC_MODE_D6:
            OsdDispItemValueUpdate(_OSD_ADVANCE_TYPEC_MODE);
            g_stOsdItemData.usAdjValue = 3;
            SET_OSD_STATE(_MENU_ADVANCE_TYPEC_MODE_D6);
            OsdDisp3rdItemAdj(_OSD_ADVANCE_TYPEC_MODE, _OFF);
            break;
        case _MENU_ADVANCE_HDMI_VERSION_ADJUST:
            OsdDispItemValueUpdate(_OSD_ADVANCE_HDMI_VERSIONS);
            g_stOsdItemData.usAdjValue = (g_us4thItemNum);
            SET_OSD_STATE(g_stOsdItemData.usSubOsdState);
            OsdDisp3rdItemAdj(_OSD_ADVANCE_HDMI_VERSIONS, _OFF);
            break;
        case _MENU_ADVANCE_EDID_ADJUST:
            OsdDispItemValueUpdate(_OSD_ADVANCE_DP_RESOLUTION);
            g_stOsdItemData.usAdjValue = (g_us4thItemNum);
            SET_OSD_STATE(g_stOsdItemData.usSubOsdState);
            OsdDisp3rdItemAdj(_OSD_ADVANCE_DP_RESOLUTION, _OFF);
            break;
        case _MENU_ADVANCE_EAGLE_SIGHT_ADJUST:
            OsdDispItemValueUpdate(_OSD_ADVANCE_EAGLE_SIGHT);
            g_stOsdItemData.usAdjValue = (g_us4thItemNum);
            SET_OSD_STATE(g_stOsdItemData.usSubOsdState);
            OsdDisp3rdItemAdj(_OSD_ADVANCE_EAGLE_SIGHT, _OFF);
            break;
        case _MENU_ADVANCE_MBR_ADJUST:
            OsdDispItemValueUpdate(_OSD_ADVANCE_MBR);
            g_stOsdItemData.usAdjValue = (g_us4thItemNum);
            SET_OSD_STATE(g_stOsdItemData.usSubOsdState);
            OsdDisp3rdItemAdj(_OSD_ADVANCE_MBR, _OFF);
            break;
        case _MENU_ADVANCE_LOCAL_CONTRAST_BLENDING:
            OsdDispItemValueUpdate(_OSD_ADVANCE_LOCAL_CONTRAST_USER);
            g_stOsdItemData.usAdjValue = 0;
            SET_OSD_STATE(g_stOsdItemData.usSubOsdState);
            OsdDisp3rdItemAdj(_OSD_ADVANCE_LOCAL_CONTRAST_USER, _OFF);
            break;
        case _MENU_ADVANCE_LOCAL_CONTRAST_DIFFGAIN:
            OsdDispItemValueUpdate(_OSD_ADVANCE_LOCAL_CONTRAST_USER);
            g_stOsdItemData.usAdjValue = 1;
            SET_OSD_STATE(g_stOsdItemData.usSubOsdState);
            OsdDisp3rdItemAdj(_OSD_ADVANCE_LOCAL_CONTRAST_USER, _OFF);
            break;
        case _MENU_ADVANCE_SDR_PLUS_SHARP:
            OsdDispItemValueUpdate(_OSD_ADVANCE_SDR_PLUS_ADJ);
            g_stOsdItemData.usAdjValue = 0;
            SET_OSD_STATE(g_stOsdItemData.usSubOsdState);
            OsdDisp3rdItemAdj(_OSD_ADVANCE_SDR_PLUS_ADJ, _OFF);
            break;
        case _MENU_ADVANCE_SDR_PLUS_DARK:
            OsdDispItemValueUpdate(_OSD_ADVANCE_SDR_PLUS_ADJ);
            g_stOsdItemData.usAdjValue = 1;
            SET_OSD_STATE(g_stOsdItemData.usSubOsdState);
            OsdDisp3rdItemAdj(_OSD_ADVANCE_SDR_PLUS_ADJ, _OFF);
            break;
#if(_IMMERSIVE_NIGHT_SNIPER_FUNCTION == _ON)
        case _MENU_ADVANCE_NIGHT_SNIPER_ADJUST:
            OsdDispItemValueUpdate(_OSD_ADVANCE_NIGHT_SNIPER);
            g_stOsdItemData.usAdjValue = 0;
            SET_OSD_STATE(g_stOsdItemData.usSubOsdState);
            OsdDisp3rdItemAdj(_OSD_ADVANCE_NIGHT_SNIPER, _OFF);
            break;
        case _MENU_ADVANCE_NIGHT_SNIPER_SATURATION:
            OsdDispItemValueUpdate(_OSD_ADVANCE_NIGHT_SNIPER);
            g_stOsdItemData.usAdjValue = 1;
            SET_OSD_STATE(g_stOsdItemData.usSubOsdState);
            OsdDisp3rdItemAdj(_OSD_ADVANCE_NIGHT_SNIPER, _OFF);
            break;
        case _MENU_ADVANCE_NIGHT_SNIPER_LIGHTNESS:
            OsdDispItemValueUpdate(_OSD_ADVANCE_NIGHT_SNIPER);
            g_stOsdItemData.usAdjValue = 2;
            SET_OSD_STATE(g_stOsdItemData.usSubOsdState);
            OsdDisp3rdItemAdj(_OSD_ADVANCE_NIGHT_SNIPER, _OFF);
            break;
#endif
        case _MENU_ADVANCE_ANTI_ALIASING:
            OsdDispItemValueUpdate(_OSD_ADVANCE_ANTI_ALIASING);
            g_stOsdItemData.usAdjValue = (g_us4thItemNum);
            SET_OSD_STATE(g_stOsdItemData.usSubOsdState);
            OsdDisp3rdItemAdj(_OSD_ADVANCE_ANTI_ALIASING, _OFF);
            break;

        default:
            break;
    }
}
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdDisp4thItemValueUpdate(WORD usOsdState)
{
    memset(&g_stOsdItemData, 0, sizeof(StructOsdItemDataType));

    switch(usOsdState)
    {
        case _MENU_DISPLAYFUN_PIP_POSITION_USER:
            if(g_usAdjustValue == 0)
            {
                g_stOsdItemData.usStringIdx = _STRING_PIP_USER_POSITION_H;
                g_stOsdItemData.usAdjValue = GET_OSD_PIP_USER_POSITION_H();
                g_stOsdItemData.usAdjValueMin = _OSD_PIP_USER_POSITION_H_MIN;
                g_stOsdItemData.usAdjValueMax = _OSD_PIP_USER_POSITION_H_MAX;
                g_stOsdItemData.usAdjValueCenter = _OSD_PIP_USER_POSITION_H_CENTER;
                g_stOsdItemData.usSubStringIdx = _STRING_PIP_USER_POSITION_H;
                g_stOsdItemData.usSubOsdState = _MENU_DISPLAYFUN_PIP_POSITION_H_ADJUST;
                g_stOsdItemData.b3ShowType = _ADJ_BAR_PERCENT;
            }
            else if(g_usAdjustValue == 1)
            {
                g_stOsdItemData.usStringIdx = _STRING_PIP_USER_POSITION_V;
                g_stOsdItemData.usAdjValue = GET_OSD_PIP_USER_POSITION_V();
                g_stOsdItemData.usAdjValueMin = _OSD_PIP_USER_POSITION_V_MIN;
                g_stOsdItemData.usAdjValueMax = _OSD_PIP_USER_POSITION_V_MAX;
                g_stOsdItemData.usAdjValueCenter = _OSD_PIP_USER_POSITION_V_CENTER;
                g_stOsdItemData.usSubStringIdx = _STRING_PIP_USER_POSITION_V;
                g_stOsdItemData.usSubOsdState = _MENU_DISPLAYFUN_PIP_POSITION_V_ADJUST;
                g_stOsdItemData.b3ShowType = _ADJ_BAR_PERCENT;
            }
            break;
//==User Color Temp R/G/B
        case _MENU_COLOR_TEMP_USER_R:
            g_stOsdItemData.usStringIdx = _STRING_TEMP_USER_R;
            g_stOsdItemData.usAdjValue = GET_COLOR_TEMP_TYPE_USER_R();
            g_stOsdItemData.usAdjValueMin = _USER_RGB_MIN;
            g_stOsdItemData.usAdjValueMax = _USER_RGB_MAX;
            g_stOsdItemData.usAdjValueCenter = _USER_RGB_CENTER;
            g_stOsdItemData.usSubStringIdx = _STRING_TEMP_USER_R;
            g_stOsdItemData.usSubOsdState = _MENU_COLOR_TEMP_USER_ADJUST_R;
            g_stOsdItemData.b3ShowType = _ADJ_BAR_REAL;
            break;
        case _MENU_COLOR_TEMP_USER_G:
            g_stOsdItemData.usStringIdx = _STRING_TEMP_USER_G;
            g_stOsdItemData.usAdjValue = GET_COLOR_TEMP_TYPE_USER_G();
            g_stOsdItemData.usAdjValueMin = _USER_RGB_MIN;
            g_stOsdItemData.usAdjValueMax = _USER_RGB_MAX;
            g_stOsdItemData.usAdjValueCenter = _USER_RGB_CENTER;
            g_stOsdItemData.usSubStringIdx = _STRING_TEMP_USER_G;
            g_stOsdItemData.usSubOsdState = _MENU_COLOR_TEMP_USER_ADJUST_G;
            g_stOsdItemData.b3ShowType = _ADJ_BAR_REAL;
            break;
        case _MENU_COLOR_TEMP_USER_B:
            g_stOsdItemData.usStringIdx = _STRING_TEMP_USER_B;
            g_stOsdItemData.usAdjValue = GET_COLOR_TEMP_TYPE_USER_B();
            g_stOsdItemData.usAdjValueMin = _USER_RGB_MIN;
            g_stOsdItemData.usAdjValueMax = _USER_RGB_MAX;
            g_stOsdItemData.usAdjValueCenter = _USER_RGB_CENTER;
            g_stOsdItemData.usSubStringIdx = _STRING_TEMP_USER_B;
            g_stOsdItemData.usSubOsdState = _MENU_COLOR_TEMP_USER_ADJUST_B;
            g_stOsdItemData.b3ShowType = _ADJ_BAR_REAL;
            break;
//==User Color Effect R/G/B/Y/C/M
        case _MENU_COLOR_EFF_USER_R_HUE:
            g_stOsdItemData.usStringIdx = _STRING_COLOR_EFF_USER_R_HUE;
            SET_OSD_SIX_COLOR(_SIXCOLOR_R);
            OsdDisplaySixColorGetOneColor(GET_OSD_SYSTEM_SELECT_REGION(), GET_OSD_SIX_COLOR());

            g_stOsdItemData.usAdjValue = GET_OSD_SIX_COLOR_HUE();
            g_stOsdItemData.usAdjValueMin = _SIX_COLOR_HUE_MIN;
            g_stOsdItemData.usAdjValueMax = _SIX_COLOR_HUE_MAX;
            g_stOsdItemData.usAdjValueCenter = _SIX_COLOR_HUE_CENTER;
            g_stOsdItemData.usSubStringIdx = _STRING_COLOR_EFF_USER_R_HUE;
            g_stOsdItemData.usSubOsdState = _MENU_COLOR_EFF_USER_R_HUE_ADJUST;
            g_stOsdItemData.b3ShowType = _ADJ_BAR_PERCENT;
            break;
        case _MENU_COLOR_EFF_USER_R_SAT:
            g_stOsdItemData.usStringIdx = _STRING_COLOR_EFF_USER_R_SAT;
            SET_OSD_SIX_COLOR(_SIXCOLOR_R);
            OsdDisplaySixColorGetOneColor(GET_OSD_SYSTEM_SELECT_REGION(), GET_OSD_SIX_COLOR());

            g_stOsdItemData.usAdjValue = GET_OSD_SIX_COLOR_SATURATION();
            g_stOsdItemData.usAdjValueMin = _SIX_COLOR_SATURATION_MIN;
            g_stOsdItemData.usAdjValueMax = _SIX_COLOR_SATURATION_MAX;
            g_stOsdItemData.usAdjValueCenter = _SIX_COLOR_SATURATION_CENTER;
            g_stOsdItemData.usSubStringIdx = _STRING_COLOR_EFF_USER_R_SAT;
            g_stOsdItemData.usSubOsdState = _MENU_COLOR_EFF_USER_R_SAT_ADJUST;
            g_stOsdItemData.b3ShowType = _ADJ_BAR_PERCENT;
            break;
        case _MENU_COLOR_EFF_USER_Y_HUE:
            g_stOsdItemData.usStringIdx = _STRING_COLOR_EFF_USER_Y_HUE;
            SET_OSD_SIX_COLOR(_SIXCOLOR_Y);
            OsdDisplaySixColorGetOneColor(GET_OSD_SYSTEM_SELECT_REGION(), GET_OSD_SIX_COLOR());

            g_stOsdItemData.usAdjValue = GET_OSD_SIX_COLOR_HUE();
            g_stOsdItemData.usAdjValueMin = _SIX_COLOR_HUE_MIN;
            g_stOsdItemData.usAdjValueMax = _SIX_COLOR_HUE_MAX;
            g_stOsdItemData.usAdjValueCenter = _SIX_COLOR_HUE_CENTER;
            g_stOsdItemData.usSubStringIdx = _STRING_COLOR_EFF_USER_Y_HUE;
            g_stOsdItemData.usSubOsdState = _MENU_COLOR_EFF_USER_Y_HUE_ADJUST;
            g_stOsdItemData.b3ShowType = _ADJ_BAR_PERCENT;
            break;
        case _MENU_COLOR_EFF_USER_Y_SAT:
            g_stOsdItemData.usStringIdx = _STRING_COLOR_EFF_USER_Y_SAT;
            SET_OSD_SIX_COLOR(_SIXCOLOR_Y);
            OsdDisplaySixColorGetOneColor(GET_OSD_SYSTEM_SELECT_REGION(), GET_OSD_SIX_COLOR());

            g_stOsdItemData.usAdjValue = GET_OSD_SIX_COLOR_SATURATION();
            g_stOsdItemData.usAdjValueMin = _SIX_COLOR_SATURATION_MIN;
            g_stOsdItemData.usAdjValueMax = _SIX_COLOR_SATURATION_MAX;
            g_stOsdItemData.usAdjValueCenter = _SIX_COLOR_SATURATION_CENTER;
            g_stOsdItemData.usSubStringIdx = _STRING_COLOR_EFF_USER_Y_SAT;
            g_stOsdItemData.usSubOsdState = _MENU_COLOR_EFF_USER_Y_SAT_ADJUST;
            g_stOsdItemData.b3ShowType = _ADJ_BAR_PERCENT;
            break;
        case _MENU_COLOR_EFF_USER_G_HUE:
            g_stOsdItemData.usStringIdx = _STRING_COLOR_EFF_USER_G_HUE;
            SET_OSD_SIX_COLOR(_SIXCOLOR_G);
            OsdDisplaySixColorGetOneColor(GET_OSD_SYSTEM_SELECT_REGION(), GET_OSD_SIX_COLOR());

            g_stOsdItemData.usAdjValue = GET_OSD_SIX_COLOR_HUE();
            g_stOsdItemData.usAdjValueMin = _SIX_COLOR_HUE_MIN;
            g_stOsdItemData.usAdjValueMax = _SIX_COLOR_HUE_MAX;
            g_stOsdItemData.usAdjValueCenter = _SIX_COLOR_HUE_CENTER;
            g_stOsdItemData.usSubStringIdx = _STRING_COLOR_EFF_USER_G_HUE;
            g_stOsdItemData.usSubOsdState = _MENU_COLOR_EFF_USER_G_HUE_ADJUST;
            g_stOsdItemData.b3ShowType = _ADJ_BAR_PERCENT;
            break;
        case _MENU_COLOR_EFF_USER_G_SAT:
            g_stOsdItemData.usStringIdx = _STRING_COLOR_EFF_USER_G_SAT;
            SET_OSD_SIX_COLOR(_SIXCOLOR_G);
            OsdDisplaySixColorGetOneColor(GET_OSD_SYSTEM_SELECT_REGION(), GET_OSD_SIX_COLOR());

            g_stOsdItemData.usAdjValue = GET_OSD_SIX_COLOR_SATURATION();
            g_stOsdItemData.usAdjValueMin = _SIX_COLOR_SATURATION_MIN;
            g_stOsdItemData.usAdjValueMax = _SIX_COLOR_SATURATION_MAX;
            g_stOsdItemData.usAdjValueCenter = _SIX_COLOR_SATURATION_CENTER;
            g_stOsdItemData.usSubStringIdx = _STRING_COLOR_EFF_USER_G_SAT;
            g_stOsdItemData.usSubOsdState = _MENU_COLOR_EFF_USER_G_SAT_ADJUST;
            g_stOsdItemData.b3ShowType = _ADJ_BAR_PERCENT;
            break;
        case _MENU_COLOR_EFF_USER_C_HUE:
            g_stOsdItemData.usStringIdx = _STRING_COLOR_EFF_USER_C_HUE;
            SET_OSD_SIX_COLOR(_SIXCOLOR_C);
            OsdDisplaySixColorGetOneColor(GET_OSD_SYSTEM_SELECT_REGION(), GET_OSD_SIX_COLOR());

            g_stOsdItemData.usAdjValue = GET_OSD_SIX_COLOR_HUE();
            g_stOsdItemData.usAdjValueMin = _SIX_COLOR_HUE_MIN;
            g_stOsdItemData.usAdjValueMax = _SIX_COLOR_HUE_MAX;
            g_stOsdItemData.usAdjValueCenter = _SIX_COLOR_HUE_CENTER;
            g_stOsdItemData.usSubStringIdx = _STRING_COLOR_EFF_USER_C_HUE;
            g_stOsdItemData.usSubOsdState = _MENU_COLOR_EFF_USER_C_HUE_ADJUST;
            g_stOsdItemData.b3ShowType = _ADJ_BAR_PERCENT;
            break;
        case _MENU_COLOR_EFF_USER_C_SAT:
            g_stOsdItemData.usStringIdx = _STRING_COLOR_EFF_USER_C_SAT;
            SET_OSD_SIX_COLOR(_SIXCOLOR_C);
            OsdDisplaySixColorGetOneColor(GET_OSD_SYSTEM_SELECT_REGION(), GET_OSD_SIX_COLOR());

            g_stOsdItemData.usAdjValue = GET_OSD_SIX_COLOR_SATURATION();
            g_stOsdItemData.usAdjValueMin = _SIX_COLOR_SATURATION_MIN;
            g_stOsdItemData.usAdjValueMax = _SIX_COLOR_SATURATION_MAX;
            g_stOsdItemData.usAdjValueCenter = _SIX_COLOR_SATURATION_CENTER;
            g_stOsdItemData.usSubStringIdx = _STRING_COLOR_EFF_USER_C_SAT;
            g_stOsdItemData.usSubOsdState = _MENU_COLOR_EFF_USER_C_SAT_ADJUST;
            g_stOsdItemData.b3ShowType = _ADJ_BAR_PERCENT;
            break;
        case _MENU_COLOR_EFF_USER_B_HUE:
            g_stOsdItemData.usStringIdx = _STRING_COLOR_EFF_USER_B_HUE;
            SET_OSD_SIX_COLOR(_SIXCOLOR_B);
            OsdDisplaySixColorGetOneColor(GET_OSD_SYSTEM_SELECT_REGION(), GET_OSD_SIX_COLOR());

            g_stOsdItemData.usAdjValue = GET_OSD_SIX_COLOR_HUE();
            g_stOsdItemData.usAdjValueMin = _SIX_COLOR_HUE_MIN;
            g_stOsdItemData.usAdjValueMax = _SIX_COLOR_HUE_MAX;
            g_stOsdItemData.usAdjValueCenter = _SIX_COLOR_HUE_CENTER;
            g_stOsdItemData.usSubStringIdx = _STRING_COLOR_EFF_USER_B_HUE;
            g_stOsdItemData.usSubOsdState = _MENU_COLOR_EFF_USER_B_HUE_ADJUST;
            g_stOsdItemData.b3ShowType = _ADJ_BAR_PERCENT;
            break;
        case _MENU_COLOR_EFF_USER_B_SAT:
            g_stOsdItemData.usStringIdx = _STRING_COLOR_EFF_USER_B_SAT;
            SET_OSD_SIX_COLOR(_SIXCOLOR_B);
            OsdDisplaySixColorGetOneColor(GET_OSD_SYSTEM_SELECT_REGION(), GET_OSD_SIX_COLOR());

            g_stOsdItemData.usAdjValue = GET_OSD_SIX_COLOR_SATURATION();
            g_stOsdItemData.usAdjValueMin = _SIX_COLOR_SATURATION_MIN;
            g_stOsdItemData.usAdjValueMax = _SIX_COLOR_SATURATION_MAX;
            g_stOsdItemData.usAdjValueCenter = _SIX_COLOR_SATURATION_CENTER;
            g_stOsdItemData.usSubStringIdx = _STRING_COLOR_EFF_USER_B_SAT;
            g_stOsdItemData.usSubOsdState = _MENU_COLOR_EFF_USER_B_SAT_ADJUST;
            g_stOsdItemData.b3ShowType = _ADJ_BAR_PERCENT;
            break;
        case _MENU_COLOR_EFF_USER_M_HUE:
            g_stOsdItemData.usStringIdx = _STRING_COLOR_EFF_USER_M_HUE;
            SET_OSD_SIX_COLOR(_SIXCOLOR_M);
            OsdDisplaySixColorGetOneColor(GET_OSD_SYSTEM_SELECT_REGION(), GET_OSD_SIX_COLOR());

            g_stOsdItemData.usAdjValue = GET_OSD_SIX_COLOR_HUE();
            g_stOsdItemData.usAdjValueMin = _SIX_COLOR_HUE_MIN;
            g_stOsdItemData.usAdjValueMax = _SIX_COLOR_HUE_MAX;
            g_stOsdItemData.usAdjValueCenter = _SIX_COLOR_HUE_CENTER;
            g_stOsdItemData.usSubStringIdx = _STRING_COLOR_EFF_USER_M_HUE;
            g_stOsdItemData.usSubOsdState = _MENU_COLOR_EFF_USER_M_HUE_ADJUST;
            g_stOsdItemData.b3ShowType = _ADJ_BAR_PERCENT;
            break;
        case _MENU_COLOR_EFF_USER_M_SAT:
            g_stOsdItemData.usStringIdx = _STRING_COLOR_EFF_USER_M_SAT;
            SET_OSD_SIX_COLOR(_SIXCOLOR_M);
            OsdDisplaySixColorGetOneColor(GET_OSD_SYSTEM_SELECT_REGION(), GET_OSD_SIX_COLOR());

            g_stOsdItemData.usAdjValue = GET_OSD_SIX_COLOR_SATURATION();
            g_stOsdItemData.usAdjValueMin = _SIX_COLOR_SATURATION_MIN;
            g_stOsdItemData.usAdjValueMax = _SIX_COLOR_SATURATION_MAX;
            g_stOsdItemData.usAdjValueCenter = _SIX_COLOR_SATURATION_CENTER;
            g_stOsdItemData.usSubStringIdx = _STRING_COLOR_EFF_USER_M_SAT;
            g_stOsdItemData.usSubOsdState = _MENU_COLOR_EFF_USER_M_SAT_ADJUST;
            g_stOsdItemData.b3ShowType = _ADJ_BAR_PERCENT;
            break;
#if(_ICM_CHAMELEON_FUNCTION == _ON)
        case _MENU_COLOR_CHAMELEON_HUE:
            g_stOsdItemData.usStringIdx = _STRING_HUE;
            g_stOsdItemData.usAdjValue = GET_OSD_CHAMELEON_HUE(GET_OSD_SELECT_REGION());
            g_stOsdItemData.usAdjValueMin = _CHAMELEON_HUE_MIN;
            g_stOsdItemData.usAdjValueMax = _CHAMELEON_HUE_MAX;
            g_stOsdItemData.usAdjValueCenter = _CHAMELEON_HUE_CENTER;
            g_stOsdItemData.usSubStringIdx = _STRING_HUE;
            g_stOsdItemData.usSubOsdState = _MENU_COLOR_CHAMELEON_HUE_ADJUST;
            g_stOsdItemData.b3ShowType = _ADJ_BAR_REAL;
            break;
        case _MENU_COLOR_CHAMELEON_SAT:
            g_stOsdItemData.usStringIdx = _STRING_SATURATION;
            g_stOsdItemData.usAdjValue = GET_OSD_CHAMELEON_SAT(GET_OSD_SELECT_REGION());
            g_stOsdItemData.usAdjValueMin = _CHAMELEON_SAT_MIN;
            g_stOsdItemData.usAdjValueMax = _CHAMELEON_SAT_MAX;
            g_stOsdItemData.usAdjValueCenter = _CHAMELEON_SAT_CENTER;
            g_stOsdItemData.usSubStringIdx = _STRING_SATURATION;
            g_stOsdItemData.usSubOsdState = _MENU_COLOR_CHAMELEON_SAT_ADJUST;
            g_stOsdItemData.b3ShowType = _ADJ_BAR_PERCENT;
            break;
        case _MENU_COLOR_CHAMELEON_LIGHTNESS:
            g_stOsdItemData.usStringIdx = _STRING_LIGHTNESS;
            g_stOsdItemData.usAdjValue = GET_OSD_CHAMELEON_LIGHTNESS(GET_OSD_SELECT_REGION());
            g_stOsdItemData.usAdjValueMin = _CHAMELEON_LIGHT_MIN;
            g_stOsdItemData.usAdjValueMax = _CHAMELEON_LIGHT_MAX;
            g_stOsdItemData.usAdjValueCenter = _CHAMELEON_LIGHT_CENTER;
            g_stOsdItemData.usSubStringIdx = _STRING_LIGHTNESS;
            g_stOsdItemData.usSubOsdState = _MENU_COLOR_CHAMELEON_LIGHTNESS_ADJUST;
            g_stOsdItemData.b3ShowType = _ADJ_BAR_PERCENT;
            break;
#endif
#if(_DYNAMIC_LOWBLUE_FUNCTION == _ON)
        case _MENU_COLOR_EYE_PROTECT_ADJUST:
            if(g_usAdjustValue == _LOWBLUE_MODE)
            {
                g_stOsdItemData.usStringIdx = _STRING_LOWBLUE;
                g_stOsdItemData.usAdjValue = GET_OSD_EYEPROTECT_LOWBLUE();
                g_stOsdItemData.usAdjValueMin = _LOWBLUE_OFF;
                g_stOsdItemData.usAdjValueMax = _LOWBLUE_STATIC_GLOBAL;
                g_stOsdItemData.usSubStringIdx = _STRING_LOWBLUE_OFF;
                g_stOsdItemData.usSubOsdState = _MENU_COLOR_EYE_PROTECT_MODE_ADJUST;
                g_stOsdItemData.b3ShowType = _ADJ_LIST;
                g_us4thItemNum = 0;
            }
            else if(g_usAdjustValue == _PROTECT_LEVEL)
            {
                g_stOsdItemData.usStringIdx = _STRING_PROTECT_LEVEL;
                g_stOsdItemData.usAdjValue = GET_OSD_EYEPROTECT_LOWBLUE_LEVEL();
                g_stOsdItemData.usAdjValueMin = _EYEPROTECT_LEVEL_0;
                g_stOsdItemData.usAdjValueMax = _EYEPROTECT_LEVEL_3;
                g_stOsdItemData.usSubStringIdx = _STRING_LEVEL0;
                g_stOsdItemData.usSubOsdState = _MENU_COLOR_EYE_PROTECT_LEVEL_ADJUST;
                g_stOsdItemData.b3ShowType = _ADJ_LIST;
                g_us4thItemNum = 1;
            }
            else if(g_usAdjustValue == _NIGHT_MODE)
            {
                g_stOsdItemData.usStringIdx = _STRING_NIGHT_MODE;
                SET_OSD_EYEPROTECT_NIGHTMODE_TIME(_EYEPROTECT_TIME_OFF);// always set ot off , just for demo used
                g_stOsdItemData.usAdjValue = GET_OSD_EYEPROTECT_NIGHTMODE_TIME();
                g_stOsdItemData.usAdjValueMin = _EYEPROTECT_TIME_OFF;
                g_stOsdItemData.usAdjValueMax = _EYEPROTECT_TIME_10MIN;
                g_stOsdItemData.usSubStringIdx = _STRING_NIGHT_OFF;
                g_stOsdItemData.usSubOsdState = _MENU_COLOR_EYE_PROTECT_TIME_ADJUST;
                g_stOsdItemData.b3ShowType = _ADJ_LIST;
                g_us4thItemNum = 2;
            }
            else if(g_usAdjustValue == _AMBIENT_SENSE_MODE)
            {
                g_stOsdItemData.usStringIdx = _STRING_AMBIENT_SENCE;
                g_stOsdItemData.usAdjValue = GET_OSD_EYEPROTECT_AMBIENTSENSE_MODE();
                g_stOsdItemData.usAdjValueMin = _OFF;
                g_stOsdItemData.usAdjValueMax = _ON;
                g_stOsdItemData.usSubStringIdx = _STRING_OFF;
                g_stOsdItemData.usSubOsdState = _MENU_COLOR_EYE_PROTECT_AMBIENTSENSE_ADJUST;
                g_stOsdItemData.b3ShowType = _ADJ_LIST;
                g_us4thItemNum = 3;
            }
            break;
#endif
//=======ADJ list for DP version
        case _MENU_ADVANCE_DP_OPTION_D0:
            g_stOsdItemData.usStringIdx = _STRING_D0;
            g_stOsdItemData.usAdjValue = GET_OSD_DP_D0_VERSION();
            g_stOsdItemData.usAdjValueMin = _DP_VER_1_DOT_1;
            g_stOsdItemData.usAdjValueMax = _DP_VER_AMOUNT;
            g_stOsdItemData.usSubStringIdx = _STRING_1_DOT_1;
            g_stOsdItemData.usSubOsdState = _MENU_ADVANCE_DP_D0_VERSION_ADJUST;
            g_stOsdItemData.b3ShowType = _ADJ_LIST;
            break;
        case _MENU_ADVANCE_DP_OPTION_D1:
            g_stOsdItemData.usStringIdx = _STRING_D1;
            g_stOsdItemData.usAdjValue = GET_OSD_DP_D1_VERSION();
            g_stOsdItemData.usAdjValueMin = _DP_VER_1_DOT_1;
            g_stOsdItemData.usAdjValueMax = _DP_VER_AMOUNT;
            g_stOsdItemData.usSubStringIdx = _STRING_1_DOT_1;
            g_stOsdItemData.usSubOsdState = _MENU_ADVANCE_DP_D1_VERSION_ADJUST;
            g_stOsdItemData.b3ShowType = _ADJ_LIST;
            break;
        case _MENU_ADVANCE_DP_OPTION_D2:
            g_stOsdItemData.usStringIdx = _STRING_D2;
            g_stOsdItemData.usAdjValue = GET_OSD_DP_D2_VERSION();
            g_stOsdItemData.usAdjValueMin = _DP_VER_1_DOT_1;
            g_stOsdItemData.usAdjValueMax = _DP_VER_AMOUNT;
            g_stOsdItemData.usSubStringIdx = _STRING_1_DOT_1;
            g_stOsdItemData.usSubOsdState = _MENU_ADVANCE_DP_D2_VERSION_ADJUST;
            g_stOsdItemData.b3ShowType = _ADJ_LIST;
            break;
        case _MENU_ADVANCE_DP_OPTION_D6:
            g_stOsdItemData.usStringIdx = _STRING_D6;
            g_stOsdItemData.usAdjValue = GET_OSD_DP_D6_VERSION();
            g_stOsdItemData.usAdjValueMin = _DP_VER_1_DOT_1;
            g_stOsdItemData.usAdjValueMax = _DP_VER_AMOUNT;
            g_stOsdItemData.usSubStringIdx = _STRING_1_DOT_1;
            g_stOsdItemData.usSubOsdState = _MENU_ADVANCE_DP_D6_VERSION_ADJUST;
            g_stOsdItemData.b3ShowType = _ADJ_LIST;
            break;
//=======ADJ list for typeC USB U3
        case _MENU_ADVANCE_TYPEC_MODE_D0:
            g_stOsdItemData.usStringIdx = _STRING_D0;
#if(_D0_USB_HUB_SUPPORT == _ON)
            g_stOsdItemData.usAdjValue = GET_OSD_D0_TYPE_C_U3_MODE();
#endif
            g_stOsdItemData.usAdjValueMin = _TYPE_C_U3_ON;
            g_stOsdItemData.usAdjValueMax = _TYPE_C_U3_OFF;
            g_stOsdItemData.usSubStringIdx = _STRING_U3_ON;
            g_stOsdItemData.usSubOsdState = _MENU_ADVANCE_D0_TYPEC_MODE_ADJUST;
            g_stOsdItemData.b3ShowType = _ADJ_LIST;
            break;
        case _MENU_ADVANCE_TYPEC_MODE_D1:
            g_stOsdItemData.usStringIdx = _STRING_D1;
#if(_D1_USB_HUB_SUPPORT == _ON)
            g_stOsdItemData.usAdjValue = GET_OSD_D1_TYPE_C_U3_MODE();
#endif
            g_stOsdItemData.usAdjValueMin = _TYPE_C_U3_ON;
            g_stOsdItemData.usAdjValueMax = _TYPE_C_U3_OFF;
            g_stOsdItemData.usSubStringIdx = _STRING_U3_ON;
            g_stOsdItemData.usSubOsdState = _MENU_ADVANCE_D1_TYPEC_MODE_ADJUST;
            g_stOsdItemData.b3ShowType = _ADJ_LIST;
            break;
        case _MENU_ADVANCE_TYPEC_MODE_D2:
            g_stOsdItemData.usStringIdx = _STRING_D2;
#if(_D2_USB_HUB_SUPPORT == _ON)
            g_stOsdItemData.usAdjValue = GET_OSD_D2_TYPE_C_U3_MODE();
#endif
            g_stOsdItemData.usAdjValueMin = _TYPE_C_U3_ON;
            g_stOsdItemData.usAdjValueMax = _TYPE_C_U3_OFF;
            g_stOsdItemData.usSubStringIdx = _STRING_U3_ON;
            g_stOsdItemData.usSubOsdState = _MENU_ADVANCE_D2_TYPEC_MODE_ADJUST;
            g_stOsdItemData.b3ShowType = _ADJ_LIST;
            break;
        case _MENU_ADVANCE_TYPEC_MODE_D6:
            g_stOsdItemData.usStringIdx = _STRING_D6;
#if(0)
            g_stOsdItemData.usAdjValue = GET_OSD_D6_TYPE_C_U3_MODE();
#endif
            g_stOsdItemData.usAdjValueMin = _TYPE_C_U3_ON;
            g_stOsdItemData.usAdjValueMax = _TYPE_C_U3_OFF;
            g_stOsdItemData.usSubStringIdx = _STRING_U3_ON;
            g_stOsdItemData.usSubOsdState = _MENU_ADVANCE_D6_TYPEC_MODE_ADJUST;
            g_stOsdItemData.b3ShowType = _ADJ_LIST;
            break;
//=======ADJ list for HDMI Version
        case _MENU_ADVANCE_HDMI_VERSION_ADJUST:
            g_stOsdItemData.usAdjValueMin = _HDMI_1P4;
            g_stOsdItemData.usAdjValueMax = _HDMI_2P0;
            if(g_usAdjustValue == 0)// D0 Inputport
            {
                g_stOsdItemData.usStringIdx = _STRING_HDMI_D0;
                g_stOsdItemData.usAdjValue = GET_OSD_D0_HDMI_VER();
                g_us4thItemNum = 0;
            }
            else if(g_usAdjustValue == 1)// D1 Inputport
            {
                g_stOsdItemData.usStringIdx = _STRING_HDMI_D1;
                g_stOsdItemData.usAdjValue = GET_OSD_D1_HDMI_VER();
                g_us4thItemNum = 1;
#if(_D1_HDMI_FRL_SUPPORT == _ON)
                g_stOsdItemData.usAdjValueMin = _HDMI_1P4;
                g_stOsdItemData.usAdjValueMax = _HDMI_2P1;
#endif
            }
            else if(g_usAdjustValue == 2)// D2 Inputport
            {
                g_stOsdItemData.usStringIdx = _STRING_HDMI_D2;
                g_stOsdItemData.usAdjValue = GET_OSD_D2_HDMI_VER();
                g_us4thItemNum = 2;
#if(_D2_HDMI_FRL_SUPPORT == _ON)
                g_stOsdItemData.usAdjValueMin = _HDMI_1P4;
                g_stOsdItemData.usAdjValueMax = _HDMI_2P1;
#endif
            }
            else if(g_usAdjustValue == 3)// D3 Inputport
            {
                g_stOsdItemData.usStringIdx = _STRING_HDMI_D3;
                g_stOsdItemData.usAdjValue = GET_OSD_D3_HDMI_VER();
                g_us4thItemNum = 3;
#if (_D3_HDMI_FRL_SUPPORT == _ON)
                g_stOsdItemData.usAdjValueMin = _HDMI_1P4;
                g_stOsdItemData.usAdjValueMax = _HDMI_2P1;
#endif
            }
            else if(g_usAdjustValue == 4)// D4 Inputport
            {
                g_stOsdItemData.usStringIdx = _STRING_HDMI_D4;
                g_stOsdItemData.usAdjValue = GET_OSD_D4_HDMI_VER();
                g_us4thItemNum = 4;
#if(_D4_HDMI_FRL_SUPPORT == _ON)
                g_stOsdItemData.usAdjValueMin = _HDMI_1P4;
                g_stOsdItemData.usAdjValueMax = _HDMI_2P1;
#endif
            }
            else if(g_usAdjustValue == 5)// D5 Inputport
            {
                g_stOsdItemData.usStringIdx = _STRING_HDMI_D5;
                g_stOsdItemData.usAdjValue = GET_OSD_D5_HDMI_VER();
                g_us4thItemNum = 5;
            }

            g_stOsdItemData.usSubStringIdx = _STRING_1_DOT_4;
            g_stOsdItemData.usSubOsdState = _MENU_ADVANCE_DX_HDMI_VERSION_ADJUST;
            g_stOsdItemData.b3ShowType = _ADJ_LIST;
            break;
        case _MENU_ADVANCE_EDID_DX_ADJUST:

            if(g_usAdjustValue == 0)// D0 Inputport
            {
                g_stOsdItemData.usStringIdx = _STRING_D0;
                g_stOsdItemData.usAdjValue = UserCommonNVRamGetSystemData(_EDID_D0_SELECT);
                g_us4thItemNum = 0;
            }
            else if(g_usAdjustValue == 1)// D1 Inputport
            {
                g_stOsdItemData.usStringIdx = _STRING_D1;
                g_stOsdItemData.usAdjValue = UserCommonNVRamGetSystemData(_EDID_D1_SELECT);
                g_us4thItemNum = 1;
            }
            else if(g_usAdjustValue == 2)// D2 Inputport
            {
                g_stOsdItemData.usStringIdx = _STRING_D2;
                g_stOsdItemData.usAdjValue = UserCommonNVRamGetSystemData(_EDID_D2_SELECT);
                g_us4thItemNum = 2;
            }
            else if(g_usAdjustValue == 3)// D6 Inputport
            {
                g_stOsdItemData.usStringIdx = _STRING_D6;
                g_stOsdItemData.usAdjValue = UserCommonNVRamGetSystemData(_EDID_D6_SELECT);
                g_us4thItemNum = 3;
            }

            g_stOsdItemData.usAdjValueMin = _DP_EDID_1080P;
#if(_HW_DP_HIGH_RESOL_SUPPORT == _ON)
            g_stOsdItemData.usAdjValueMax = _DP_EDID_AMOUNT;
#else
            g_stOsdItemData.usAdjValueMax = _DP_EDID_4K2K_60HZ;
#endif
            g_stOsdItemData.usSubStringIdx = _STRING_DP_1080P;
            g_stOsdItemData.usSubOsdState = _MENU_ADVANCE_EDID_DX_ADJUST;
            g_stOsdItemData.b3ShowType = _ADJ_LIST;
            break;
        case _MENU_ADVANCE_EAGLE_SIGHT_ADJUST:
            if(g_usAdjustValue == _EAGLE_SIGHT_FUNCTION)
            {
                g_stOsdItemData.usStringIdx = _STRING_EAGLE_SIGHT_ONOFF;
                g_stOsdItemData.usAdjValue = GET_EAGLE_SIGHT_STATUS();
                g_stOsdItemData.usAdjValueMin = _OFF;
                g_stOsdItemData.usAdjValueMax = _ON;
                g_stOsdItemData.usSubStringIdx = _STRING_OFF;
                g_stOsdItemData.usSubOsdState = _MENU_ADVANCE_EAGLE_SIGHT_FUNCTION_ADJUST;
                g_stOsdItemData.b3ShowType = _ADJ_LIST;
                g_us4thItemNum = 0;
            }
            else if(g_usAdjustValue == _EAGLE_SIGHT_COLOR_REGION)
            {
                g_stOsdItemData.usStringIdx = _STRING_EAGLE_SIGHT_SELECTREGION;
                g_stOsdItemData.usAdjValue = GET_OSD_SELECT_REGION();
                g_stOsdItemData.usAdjValueMin = _OSD_SR_EAGLESIGHT_MAIN;
                g_stOsdItemData.usAdjValueMax = _OSD_SR_EAGLESIGHT_FULL;
                g_stOsdItemData.usSubStringIdx = _STRING_2P_PIP_MAIN;
                g_stOsdItemData.usSubOsdState = _MENU_ADVANCE_EAGLE_SIGHT_REGION_ADJUST;
                g_stOsdItemData.b3ShowType = _ADJ_LIST;
                g_us4thItemNum = 1;
            }
            else if(g_usAdjustValue == _EAGLE_SIGHT_TRANSPARENT)
            {
                g_stOsdItemData.usStringIdx = _STRING_EAGLE_SIGHT_TRANSPARENT;
                g_stOsdItemData.usAdjValue = GET_EAGLE_SIGHT_TRANSPARENCY();
                g_stOsdItemData.usAdjValueMin = _OSD_EAGLE_SIGHT_TRANSPARENCY_MIN;
                g_stOsdItemData.usAdjValueMax = _OSD_EAGLE_SIGHT_TRANSPARENCY_MAX;
                g_stOsdItemData.usAdjValueCenter = _OSD_EAGLE_SIGHT_TRANSPARENCY_CENTER;
                g_stOsdItemData.usSubStringIdx = _STRING_EAGLE_SIGHT_TRANSPARENT;
                g_stOsdItemData.usSubOsdState = _MENU_ADVANCE_EAGLE_SIGHT_TRANSPARENT_ADJUST;
                g_stOsdItemData.b3ShowType = _ADJ_BAR_REAL;
                g_us4thItemNum = 2;
            }
            else if(g_usAdjustValue == _EAGLE_SIGHT_ZOOM)
            {
                g_stOsdItemData.usStringIdx = _STRING_EAGLE_SIGHT_ZOOM;
                g_stOsdItemData.usAdjValue = GET_EAGLE_SIGHT_ZOOM();
                g_stOsdItemData.usAdjValueMin = _ES_1p5x;
                g_stOsdItemData.usAdjValueMax = _ES_ZOOM_AMOUNT;
                g_stOsdItemData.usSubStringIdx = _STRING_1_5_X;
                g_stOsdItemData.usSubOsdState = _MENU_ADVANCE_EAGLE_SIGHT_ZOOM_ADJUST;
                g_stOsdItemData.b3ShowType = _ADJ_LIST;
                g_us4thItemNum = 3;
            }
            else if(g_usAdjustValue == _EAGLE_SIGHT_CAPTURE_POSITION)
            {
                g_stOsdItemData.usStringIdx = _STRING_EAGLE_SIGHT_CAP_POSITION;
                g_stOsdItemData.usAdjValue = GET_EAGLE_SIGHT_CAP_POSITION();
                g_stOsdItemData.usAdjValueMin = _POSITON_LT;
                g_stOsdItemData.usAdjValueMax = _POSITON_AMOUNT;
                g_stOsdItemData.usSubStringIdx = _STRING_POSITION_LT;
                g_stOsdItemData.usSubOsdState = _MENU_ADVANCE_EAGLE_SIGHT_CAP_POSITION_ADJUST;
                g_stOsdItemData.b3ShowType = _ADJ_LIST;
                g_us4thItemNum = 4;
            }
            else if(g_usAdjustValue == _EAGLE_SIGHT_DISPLAY_POSITION)
            {
                g_stOsdItemData.usStringIdx = _STRING_EAGLE_SIGHT_DISP_POSITION;
                g_stOsdItemData.usAdjValue = GET_EAGLE_SIGHT_DISP_POSITION();
                g_stOsdItemData.usAdjValueMin = _POSITON_LT;
                g_stOsdItemData.usAdjValueMax = _POSITON_AMOUNT;
                g_stOsdItemData.usSubStringIdx = _STRING_POSITION_LT;
                g_stOsdItemData.usSubOsdState = _MENU_ADVANCE_EAGLE_SIGHT_DISP_POSITION_ADJUST;
                g_stOsdItemData.b3ShowType = _ADJ_LIST;
                g_us4thItemNum = 5;
            }
            else if(g_usAdjustValue == _EAGLE_SIGHT_BORDER_WIDTH)
            {
                g_stOsdItemData.usStringIdx = _STRING_EAGLE_SIGHT_BORDER;
                g_stOsdItemData.usAdjValue = GET_EAGLE_SIGHT_BORDER();
                g_stOsdItemData.usAdjValueMin = _EAGLE_SIGHT_BORDER_WIDTH_MIN;
                g_stOsdItemData.usAdjValueMax = _EAGLE_SIGHT_BORDER_WIDTH_MAX;
                g_stOsdItemData.usAdjValueCenter = _EAGLE_SIGHT_BORDER_WIDTH_CENTER;
                g_stOsdItemData.usSubStringIdx = _STRING_EAGLE_SIGHT_BORDER;
                g_stOsdItemData.usSubOsdState = _MENU_ADVANCE_EAGLE_SIGHT_BORDER_ADJUST;
                g_stOsdItemData.b3ShowType = _ADJ_BAR_REAL;
                g_us4thItemNum = 6;
            }

#if(_EAGLE_SIGHT_CIRCLE_WIN_SUPPORT == _ON)
            else if(g_usAdjustValue == _EAGLE_SIGHT_CIRCLE_WINDOW)
            {
                g_stOsdItemData.usStringIdx = _STRING_EAGLE_SIGHT_CIRCLEWIN;
                g_stOsdItemData.usAdjValue = GET_EAGLE_SIGHT_CIRCLE_WIN_STATUS();
                g_stOsdItemData.usAdjValueMin = _OFF;
                g_stOsdItemData.usAdjValueMax = _ON;
                g_stOsdItemData.usSubStringIdx = _STRING_OFF;
                g_stOsdItemData.usSubOsdState = _MENU_ADVANCE_EAGLE_SIGHT_CIRCLEWIN_ADJUST;
                g_stOsdItemData.b3ShowType = _ADJ_LIST;
                g_us4thItemNum = 7;
            }
#endif
            break;
        case _MENU_ADVANCE_MBR_ADJUST:
            if(g_usAdjustValue == _MBR_MODE)
            {
                g_stOsdItemData.usStringIdx = _STRING_MBR_MODE;
                g_stOsdItemData.usAdjValue = GET_OSD_MBR_MODE();
                g_stOsdItemData.usAdjValueMin = _OSD_MBR_OFF;
#if((_DRR_MOTION_BLUR_REDUCTION_SUPPORT == _ON) || (_RTK_ADVANCED_MOTION_BLUR_REDUCTION_SUPPORT == _ON))
                g_stOsdItemData.usAdjValueMax = _OSD_MBR_RTK_ADV;
#else
                g_stOsdItemData.usAdjValueMax = _OSD_MBR_USERMODE;
#endif
                g_stOsdItemData.usSubStringIdx = _STRING_MBR_OFF;
                g_stOsdItemData.usSubOsdState = _MENU_ADVANCE_MBR_MODE_ADJUST;
                g_stOsdItemData.b3ShowType = _ADJ_LIST;
                g_us4thItemNum = 0;
            }
            else if(g_usAdjustValue == _MBR_DUTY)
            {
                g_stOsdItemData.usStringIdx = _STRING_MBR_DUTY;
                g_stOsdItemData.usAdjValue = GET_OSD_MBR_DUTY();
                g_stOsdItemData.usAdjValueMin = _MBR_DUTY_MIN;
                g_stOsdItemData.usAdjValueMax = _MBR_DUTY_MAX;
                g_stOsdItemData.usAdjValueCenter = _MBR_DUTY_CENTER;
                g_stOsdItemData.usSubStringIdx = _STRING_MBR_DUTY;
                g_stOsdItemData.usSubOsdState = _MENU_ADVANCE_MBR_DUTY_ADJUST;
                g_stOsdItemData.b3ShowType = _ADJ_BAR_REAL;
                g_us4thItemNum = 1;
            }
            else if(g_usAdjustValue == _MBR_POSITION)
            {
                g_stOsdItemData.usStringIdx = _STRING_MBR_POSITION;
                g_stOsdItemData.usAdjValue = GET_OSD_MBR_POSITION();
                g_stOsdItemData.usAdjValueMin = _MBR_POS_MIN;
                g_stOsdItemData.usAdjValueMax = _MBR_POS_MAX;
                g_stOsdItemData.usAdjValueCenter = _MBR_POS_CENTER;
                g_stOsdItemData.usSubStringIdx = _STRING_MBR_POSITION;
                g_stOsdItemData.usSubOsdState = _MENU_ADVANCE_MBR_POSITION_ADJUST;
                g_stOsdItemData.b3ShowType = _ADJ_BAR_REAL;
                g_us4thItemNum = 2;
            }
            break;
        case _MENU_ADVANCE_LOCAL_CONTRAST_USER:
            if(g_usAdjustValue == 0)
            {
                g_stOsdItemData.usStringIdx = _STRING_OWLSIGHT_BLENDING;
                g_stOsdItemData.usAdjValue = GET_OSD_LOCAL_CONTRAST_BLENDING(GET_OSD_SELECT_REGION());
                g_stOsdItemData.usAdjValueMin = _OSD_LC_BLENDING_MIN;
                g_stOsdItemData.usAdjValueMax = _OSD_LC_BLENDING_MAX;
                g_stOsdItemData.usAdjValueCenter = (_OSD_LC_BLENDING_MAX - _OSD_LC_BLENDING_MIN) / 2;
                g_stOsdItemData.usSubStringIdx = _STRING_OWLSIGHT_BLENDING;
                g_stOsdItemData.usSubOsdState = _MENU_ADVANCE_LOCAL_CONTRAST_BLENDING;
                g_stOsdItemData.b3ShowType = _ADJ_BAR_PERCENT;
            }
            else if(g_usAdjustValue == 1)
            {
                g_stOsdItemData.usStringIdx = _STRING_OWLSIGHT_DIFFGAIN;
                g_stOsdItemData.usAdjValue = GET_OSD_LOCAL_CONTRAST_DIFFGAIN(GET_OSD_SELECT_REGION());
                g_stOsdItemData.usAdjValueMin = _OSD_LC_DIFFGAIN_MIN;
                g_stOsdItemData.usAdjValueMax = _OSD_LC_DIFFGAIN_MAX;
                g_stOsdItemData.usAdjValueCenter = (_OSD_LC_DIFFGAIN_MAX - _OSD_LC_DIFFGAIN_MIN) / 2;
                g_stOsdItemData.usSubStringIdx = _STRING_OWLSIGHT_DIFFGAIN;
                g_stOsdItemData.usSubOsdState = _MENU_ADVANCE_LOCAL_CONTRAST_DIFFGAIN;
                g_stOsdItemData.b3ShowType = _ADJ_BAR_PERCENT;
            }
            break;

        case _MENU_ADVANCE_SDR_PLUS_SELECT:
            if(g_usAdjustValue == 0)
            {
                g_stOsdItemData.usStringIdx = _STRING_SDR_PLUS_SHARP;
                g_stOsdItemData.usAdjValue = GET_OSD_SDR_PLUS_SHARP(GET_OSD_SELECT_REGION());
                g_stOsdItemData.usAdjValueMin = 0;
                g_stOsdItemData.usAdjValueMax = 100;
                g_stOsdItemData.usAdjValueCenter = 50;
                g_stOsdItemData.usSubStringIdx = _STRING_SDR_PLUS_SHARP;
                g_stOsdItemData.usSubOsdState = _MENU_ADVANCE_SDR_PLUS_SHARP;
                g_stOsdItemData.b3ShowType = _ADJ_BAR_PERCENT;
            }
            else if(g_usAdjustValue == 1)
            {
                g_stOsdItemData.usStringIdx = _STRING_SDR_PLUS_DARK;
                g_stOsdItemData.usAdjValue = GET_OSD_SDR_PLUS_DARK(GET_OSD_SELECT_REGION());
                g_stOsdItemData.usAdjValueMin = 0;
                g_stOsdItemData.usAdjValueMax = 100;
                g_stOsdItemData.usAdjValueCenter = 50;
                g_stOsdItemData.usSubStringIdx = _STRING_SDR_PLUS_DARK;
                g_stOsdItemData.usSubOsdState = _MENU_ADVANCE_SDR_PLUS_DARK;
                g_stOsdItemData.b3ShowType = _ADJ_BAR_PERCENT;
            }
            break;
#if(_IMMERSIVE_NIGHT_SNIPER_FUNCTION == _ON)
        case _MENU_ADVANCE_NIGHT_SNIPER:
            if(g_usAdjustValue == 0)
            {
                g_stOsdItemData.usStringIdx = _STRING_NIGHT_SNIPER_SELECT;
                g_stOsdItemData.usAdjValue = GET_OSD_NIGHT_SNIPER(GET_OSD_SELECT_REGION());
                g_stOsdItemData.usAdjValueMin = _OFF;
                g_stOsdItemData.usAdjValueMax = _ON;
                g_stOsdItemData.usSubStringIdx = _STRING_OFF;
                g_stOsdItemData.usSubOsdState = _MENU_ADVANCE_NIGHT_SNIPER_ADJUST;
                g_stOsdItemData.b3ShowType = _ADJ_LIST;
            }
            if(g_usAdjustValue == 1)
            {
                g_stOsdItemData.usStringIdx = _STRING_NIGHT_SNIPER_SATURATION;
                g_stOsdItemData.usAdjValue = GET_OSD_NIGHT_SNIPER_SAT(GET_OSD_SELECT_REGION());
                g_stOsdItemData.usAdjValueMin = 0;
                g_stOsdItemData.usAdjValueMax = 100;
                g_stOsdItemData.usAdjValueCenter = 50;
                g_stOsdItemData.usSubStringIdx = _STRING_NIGHT_SNIPER_SATURATION;
                g_stOsdItemData.usSubOsdState = _MENU_ADVANCE_NIGHT_SNIPER_SATURATION;
                g_stOsdItemData.b3ShowType = _ADJ_BAR_PERCENT;
            }
            else if(g_usAdjustValue == 2)
            {
                g_stOsdItemData.usStringIdx = _STRING_NIGHT_SNIPER_LIGHTNESS;
                g_stOsdItemData.usAdjValue = GET_OSD_NIGHT_SNIPER_LIGHT(GET_OSD_SELECT_REGION());
                g_stOsdItemData.usAdjValueMin = 0;
                g_stOsdItemData.usAdjValueMax = 100;
                g_stOsdItemData.usAdjValueCenter = 50;
                g_stOsdItemData.usSubStringIdx = _STRING_NIGHT_SNIPER_LIGHTNESS;
                g_stOsdItemData.usSubOsdState = _MENU_ADVANCE_NIGHT_SNIPER_LIGHTNESS;
                g_stOsdItemData.b3ShowType = _ADJ_BAR_PERCENT;
            }
            break;
#endif
        case _MENU_ADVANCE_ANTI_ALIASING:
            if(g_usAdjustValue == 0)
            {
                g_stOsdItemData.usStringIdx = _STRING_MODE;
                g_stOsdItemData.usAdjValue = GET_ANTI_ALIASING_MODE();
                g_stOsdItemData.usAdjValueMin = 0;
                g_stOsdItemData.usAdjValueMax = 1;
                g_stOsdItemData.usSubStringIdx = _STRING_EDGE_ENHANCE;
                g_stOsdItemData.usSubOsdState = _MENU_ADVANCE_ANTI_ALIASING_MODE_ADJ;
                g_stOsdItemData.b3ShowType = _ADJ_LIST;
                g_us4thItemNum = 0;
            }
            else if(g_usAdjustValue == 1)
            {
                g_stOsdItemData.usStringIdx = _STRING_LEVEL;
                g_stOsdItemData.usAdjValue = GET_ANTI_ALIASING_LEVEL();
                g_stOsdItemData.usAdjValueMin = 0;
                g_stOsdItemData.usAdjValueMax = 5;
                g_stOsdItemData.usSubStringIdx = _STRING_LEVEL;
                g_stOsdItemData.usSubOsdState = _MENU_ADVANCE_ANTI_ALIASING_LEVEL_ADJ;
                g_stOsdItemData.b3ShowType = _ADJ_BAR_REAL;
                g_us4thItemNum = 1;
            }
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdDisp4thMenuInFoBlock(EnumStringIndex enumString)
{
    SET_OSD_INFO_STRING_MODE(_PUT_STRING_CENTER);
    SET_OSD_INFO_STRING_MODE_LENGTH(_MENU_3RD_ITEM_LIST_WIDTH);
    OsdPropPutString(ROW(_MENU_3RD_ITEM_ROW_ST + 10), COL(_MENU_3RD_ITEM_LIST_ST), _PFONT_PAGE_2, enumString, COLOR(_CP_RED, _CP_BG), GET_OSD_LANGUAGE());

    // draw Window
    SET_OSD_WINDOW_BORDER_PIXEL_WIDTH(1);
    SET_OSD_WINDOW_BORDER_PIXEL_HEIGHT(1);

    SET_OSD_WINDOW_BUTTON_TYPE(_OSD_WINDOW_BUTTON_TYPE_BORDER);
    SET_OSD_WINDOW_COLOR_BORDER(_CP_WHITE);
    OsdWindowDrawingByFont(_OSD_WIN_HIGHLIGHT_5, ROW(_MENU_3RD_ITEM_ROW_ST + 9), COL(_MENU_2ND_ITEM_VAL_COL_ST), WIDTH(_MENU_3RD_ITEM_WIDTH), HEIGHT(3), _CP_BLUE);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdDisp4thMenuTitle(void)
{
    OsdDisp4thMenuInFoBlock(g_stOsdItemData.usStringIdx);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdDisp4thMenuEnter(WORD usOsdState)
{
    OsdDisp4thItemValueUpdate(usOsdState);

    UserCommonOsdWindowDisable(_OSD_WIN_HIGHLIGHT_4);
    OsdMenu3rdFrame();
    OsdDisp4thMenuTitle();

    g_usBackupValue = g_stOsdItemData.usAdjValue;
    SET_OSD_STATE(g_stOsdItemData.usSubOsdState);
    OsdDisp4thItemAdj(_OFF);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
bit OsdDisp3rdItemCheck(EnumOsdItem enumOsdItem, BYTE ucIdx)
{
    switch(enumOsdItem)
    {
        case _OSD_ADVANCE_DPOPTION:
        case _OSD_ADVANCE_DP_RESOLUTION:

#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
            if(ucIdx == 0)
            {
                return _TRUE;
            }
#endif
#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
            if(ucIdx == 1)
            {
                return _TRUE;
            }
#endif
#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
            if(ucIdx == 2)
            {
                return _TRUE;
            }
#endif
#if(_D6_INPUT_PORT_TYPE == _D6_DP_PORT)
            if(ucIdx == 3)
            {
                return _TRUE;
            }
#endif
            break;

        case _OSD_ADVANCE_TYPEC_MODE:

#if(_D0_USB_HUB_SUPPORT == _ON)
            if(ucIdx == 0)
            {
                return _TRUE;
            }
#endif
#if(_D1_USB_HUB_SUPPORT == _ON)
            if(ucIdx == 1)
            {
                return _TRUE;
            }
#endif
#if(_D2_USB_HUB_SUPPORT == _ON)
            if(ucIdx == 2)
            {
                return _TRUE;
            }
#endif
#if(0)
            if(ucIdx == 3)
            {
                return _TRUE;
            }
#endif
            break;

        case _OSD_ADVANCE_HDMI_VERSIONS:


#if(_D0_INPUT_PORT_TYPE == _D0_HDMI_PORT)
            if(ucIdx == 0)
            {
                return _TRUE;
            }
#endif
#if(_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT)
            if(ucIdx == 1)
            {
                return _TRUE;
            }
#endif
#if(_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT)
            if(ucIdx == 2)
            {
                return _TRUE;
            }
#endif
#if(_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT)
            if(ucIdx == 3)
            {
                return _TRUE;
            }
#endif
#if(_D4_INPUT_PORT_TYPE == _D4_HDMI_PORT)
            if(ucIdx == 4)
            {
                return _TRUE;
            }
#endif
#if(_D5_INPUT_PORT_TYPE == _D5_HDMI_PORT)
            if(ucIdx == 5)
            {
                return _TRUE;
            }
#endif
            break;

        case _OSD_SOURCE_1P:
        case _OSD_SOURCE_2P:
        case _OSD_SOURCE_3P:
        case _OSD_SOURCE_4P:
            if(ucIdx == _OSD_INPUT_AUTO)
            {
                return _TRUE;
            }

#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
            if(GET_OSD_PXP_MST() == _ON_SELECT_MODE)
            {
                if((ucIdx == _OSD_INPUT_D9_D0) || (ucIdx == _OSD_INPUT_D9_D1) || (ucIdx == _OSD_INPUT_D9_D2))
                {
                    return _TRUE;
                }
            }
#endif

#if(_A0_INPUT_PORT_TYPE != _A0_NO_PORT)
            if(ucIdx == _OSD_INPUT_A0)
            {
                return _TRUE;
            }
#endif
#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
            if(ucIdx == _OSD_INPUT_D0)
            {
                return _TRUE;
            }
#endif
#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
            if(ucIdx == _OSD_INPUT_D1)
            {
                return _TRUE;
            }
#endif
#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
            if(ucIdx == _OSD_INPUT_D2)
            {
                return _TRUE;
            }
#endif
#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
            if(ucIdx == _OSD_INPUT_D3)
            {
                return _TRUE;
            }
#endif
#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
            if(ucIdx == _OSD_INPUT_D4)
            {
                return _TRUE;
            }
#endif
#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
            if(ucIdx == _OSD_INPUT_D5)
            {
                return _TRUE;
            }
#endif
#if(_D6_INPUT_PORT_TYPE != _D6_NO_PORT)
            if(ucIdx == _OSD_INPUT_D6)
            {
                return _TRUE;
            }
#endif
#if(_D7_INPUT_PORT_TYPE != _D7_NO_PORT)
            if(ucIdx == _OSD_INPUT_D7)
            {
                return _TRUE;
            }
#endif
#if(_D8_INPUT_PORT_TYPE != _D8_NO_PORT)
            if(ucIdx == _OSD_INPUT_D8)
            {
                return _TRUE;
            }
#endif
            break;

        case _OSD_MUTIP_MODE:

            if(ucIdx == _OSD_DM_1P)
            {
                return _TRUE;
            }

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
            if(ucIdx == _OSD_DM_2P_LR)
            {
                return _TRUE;
            }
#endif
#if(_2P_PBP_TB_DISPLAY_SUPPORT == _ON)
            if(ucIdx == _OSD_DM_2P_TB)
            {
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
                if(UserCommonRegionGetFrontBackModeSupport() == _TRUE)
                {
                    // return _FALSE;
                }
#endif
                return _TRUE;
            }
#endif
#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
            if(ucIdx == _OSD_DM_2P_PIP)
            {
                return _TRUE;
            }
#endif
#if(_3P_FLAG_DISPLAY_SUPPORT == _ON)
            if(ucIdx == _OSD_DM_3P_FLAG)
            {
                return _TRUE;
            }
#endif
#if(_3P_SKEW_LR_DISPLAY_SUPPORT == _ON)
            if((ucIdx == _OSD_DM_3P_SKEW_L) ||
               (ucIdx == _OSD_DM_3P_SKEW_R))
            {
                return _TRUE;
            }
#endif
#if(_3P_SKEW_TB_DISPLAY_SUPPORT == _ON)
            if((ucIdx == _OSD_DM_3P_SKEW_T) ||
               (ucIdx == _OSD_DM_3P_SKEW_B))
            {
                return _TRUE;
            }
#endif

#if(_4P_DISPLAY_SUPPORT == _ON)
            if(ucIdx == _OSD_DM_4P)
            {
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
                if(UserCommonRegionGetFrontBackModeSupport() == _TRUE)
                {
                    // return _FALSE;
                }
#endif
                return _TRUE;
            }
#endif

            return _FALSE;
            break;

        case _OSD_ADVANCE_DPMST:

            if(ucIdx == _MST_OFF)
            {
                return _TRUE;
            }

            if(ucIdx == _MST_AUTO)
            {
                if(
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
                    (GET_OSD_DP_D0_VERSION() >= _DP_VER_1_DOT_2) ||
#endif
#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
                    (GET_OSD_DP_D1_VERSION() >= _DP_VER_1_DOT_2) ||
#endif
#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
                    (GET_OSD_DP_D2_VERSION() >= _DP_VER_1_DOT_2) ||
#endif
#if(_D6_INPUT_PORT_TYPE == _D6_DP_PORT)
                    (GET_OSD_DP_D6_VERSION() >= _DP_VER_1_DOT_2) ||
#endif
                    0
                    )
                {
                    return _TRUE;
                }
            }

#if((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) && (_D0_DP_MST_PORT_SUPPORT == _ON))
            if(ucIdx == _MST_D0)
            {
                if(GET_OSD_DP_D0_VERSION() >= _DP_VER_1_DOT_2)
                {
                    return _TRUE;
                }
            }
#endif
#if((_D1_INPUT_PORT_TYPE == _D1_DP_PORT) && (_D1_DP_MST_PORT_SUPPORT == _ON))
            if(ucIdx == _MST_D1)
            {
                if(GET_OSD_DP_D1_VERSION() >= _DP_VER_1_DOT_2)
                {
                    return _TRUE;
                }
            }
#endif
#if((_D2_INPUT_PORT_TYPE == _D2_DP_PORT) && (_D2_DP_MST_PORT_SUPPORT == _ON))
            if(ucIdx == _MST_D2)
            {
                if(GET_OSD_DP_D2_VERSION() >= _DP_VER_1_DOT_2)
                {
                    return _TRUE;
                }
            }
#endif

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) &&\
    ((_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0) && (_D0_DP_MST_PORT_SUPPORT == _ON)))
            if(ucIdx == _MST_D6)
            {
                if(GET_OSD_DP_D6_VERSION() >= _DP_VER_1_DOT_2)
                {
                    return _TRUE;
                }
            }
#endif

            return _FALSE;
            break;
#if(_DYNAMIC_LOWBLUE_FUNCTION == _ON)
        case _OSD_COLOR_EYE_PROTECT:
            return _TRUE;
            break;
#endif
        case _OSD_COLOR_FORMAT:
            if((ucIdx == _COLOR_SPACE_RGB) ||
               (ucIdx == _COLOR_SPACE_YPBPR))
            {
                return _TRUE;
            }
            return _FALSE;
            break;

        case _OSD_EXIT_HOTKEY:
            switch(ucIdx + g_stOsdItemData.usAdjValueMin)
            {
#if(_USB_HUB_SUPPORT == _OFF)
                case (_OSD_ADVANCE_TYPEC_MODE):
                    return _FALSE;
#endif
#if(_USB_HUB_SUPPORT == _OFF)
                case (_OSD_ADVANCE_HUB_SWITCH):
                    return _FALSE;
#endif
#if(_HDR10_SUPPORT == _OFF)
                case (_OSD_HDR_MODE):
                case (_OSD_HDR_DARK_ENHANCE):
                case (_OSD_HDR_SHARP_ENHANCE):
                case (_OSD_HDR_COLOR_ENHANCE):
                case (_OSD_HDR_LIGHT_ENHANCE):
                case (_OSD_HDR_HLG_OOTF):
                    return _FALSE;
#endif
                case (_OSD_ADVANCE_LOCALDIMMING):
                case (_OSD_ADVANCE_LOCALDIMMING_USER):
                    return _FALSE;

#if(_PIXEL_SHIFT_SUPPORT == _ON)
                case (_OSD_ADVANCE_PIXELSHIFT):
                    return _FALSE;
#endif
#if(_DP_SUPPORT == _OFF)
                case (_OSD_ADVANCE_DPMST):
                case (_OSD_ADVANCE_DPOPTION):
                case (_OSD_ADVANCE_DP_RESOLUTION):
                    return _FALSE;
#endif
#if(_HDMI_MULTI_EDID_SUPPORT == _OFF)
                case (_OSD_ADVANCE_HDMI_VERSIONS):
                    return _FALSE;
#endif
#if(_SDR_TO_HDR_FUNCTION == _OFF)
                case (_OSD_ADVANCE_SDR_TO_HDR):
                    return _FALSE;
#endif
#if(_AUDIO_SUPPORT == _OFF)
                case (_OSD_AUDIO_AUDIO_SOURCE):
                case (_OSD_AUDIO_MUTE):
                case (_OSD_AUDIO_VOLUME):
                    return _FALSE;
#endif
#if(_INTERNAL_AUDIO_TEST_SUPPORT == _OFF)
                case (_OSD_AUDIO_AUDIO_SELF_TEST):
                    return _FALSE;
#endif
                default:
                    break;
            }
            return _TRUE;

            break;

        case _OSD_ADVANCE_DSC:

#if(_EAGLE_SIGHT_SUPPORT == _ON)
            if(SysRegionEagleSightTransDisplayMode(SysModeGetDisplayMode()) == _DISPLAY_MODE_1P)
#else
            if(SysModeGetDisplayMode() == _DISPLAY_MODE_1P)
#endif
            {
                if(((GET_OSD_DP_D0_VERSION() >= _DP_VER_1_DOT_4) || (GET_OSD_DP_D1_VERSION() >= _DP_VER_1_DOT_4) || (GET_OSD_DP_D2_VERSION() >= _DP_VER_1_DOT_4)) ||
                   ((GET_OSD_D1_HDMI_VER() >= _HDMI_2P1) || (GET_OSD_D2_HDMI_VER() >= _HDMI_2P1) || (GET_OSD_D3_HDMI_VER() >= _HDMI_2P1) || (GET_OSD_D4_HDMI_VER() >= _HDMI_2P1) || (GET_OSD_D5_HDMI_VER() >= _HDMI_2P1)))
                {
                    return _TRUE;
                }
                return _FALSE;
            }
            else
            {
#if(_DSC_MULTI_DISPLAY_AUTO_SELECT_SUPPORT == _ON)
                if((GET_OSD_DP_D0_VERSION() >= _DP_VER_1_DOT_4) || (GET_OSD_DP_D1_VERSION() >= _DP_VER_1_DOT_4) || (GET_OSD_DP_D2_VERSION() >= _DP_VER_1_DOT_4))
                {
                    return _TRUE;
                }
                return _FALSE;
#else
                if(ucIdx == _DSC_FROM_NO_PORT)
                {
                    return _TRUE;
                }
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
                if((GET_OSD_DP_D0_VERSION() >= _DP_VER_1_DOT_4) && (ucIdx == _DSC_FROM_D0_PORT))
                {
                    return _TRUE;
                }
#endif
#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
                if((GET_OSD_DP_D1_VERSION() >= _DP_VER_1_DOT_4) && (ucIdx == _DSC_FROM_D1_PORT))
                {
                    return _TRUE;
                }
#endif
#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
                if((GET_OSD_DP_D2_VERSION() >= _DP_VER_1_DOT_4) && (ucIdx == _DSC_FROM_D2_PORT))
                {
                    return _TRUE;
                }
#endif
#if(_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT)
                if((GET_OSD_D1_HDMI_VER() >= _HDMI_2P1) && (ucIdx == _DSC_FROM_D1_PORT))
                {
                    return _TRUE;
                }
#endif
#if(_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT)
                if((GET_OSD_D2_HDMI_VER() >= _HDMI_2P1) && (ucIdx == _DSC_FROM_D2_PORT))
                {
                    return _TRUE;
                }
#endif
#if(_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT)
                if((GET_OSD_D3_HDMI_VER() >= _HDMI_2P1) && (ucIdx == _DSC_FROM_D3_PORT))
                {
                    return _TRUE;
                }
#endif
#if(_D4_INPUT_PORT_TYPE == _D4_HDMI_PORT)
                if((GET_OSD_D4_HDMI_VER() >= _HDMI_2P1) && (ucIdx == _DSC_FROM_D4_PORT))
                {
                    return _TRUE;
                }
#endif
#if(_D5_INPUT_PORT_TYPE == _D5_HDMI_PORT)
                if((GET_OSD_D5_HDMI_VER() >= _HDMI_2P1) && (ucIdx == _DSC_FROM_D5_PORT))
                {
                    return _TRUE;
                }
#endif
                return _FALSE;
#endif
            }
            break;
        case _OSD_AUDIO_AUDIO_SOURCE:
            if(ucIdx == _OSD_AUDIO_SOURCE_LINEIN)
            {
#if(_LINE_IN_SUPPORT == _ON)
                return _TRUE;
#else
                return _FALSE;
#endif
            }
            if(ucIdx == _OSD_AUDIO_SOURCE_DIGITAL_REGION_4)
            {
                if(GET_OSD_DISPLAY_MODE() == _OSD_DM_4P)
                {
                    return _TRUE;
                }
                else
                {
                    return _FALSE;
                }
            }
            else if(ucIdx == _OSD_AUDIO_SOURCE_DIGITAL_REGION_3)
            {
                if(GET_OSD_DISPLAY_MODE() >= _OSD_DM_3P_FLAG)
                {
                    return _TRUE;
                }
                else
                {
                    return _FALSE;
                }
            }
            else if(ucIdx == _OSD_AUDIO_SOURCE_DIGITAL_REGION_2)
            {
                if(GET_OSD_DISPLAY_MODE() >= _OSD_DM_2P_LR)
                {
                    return _TRUE;
                }
                else
                {
                    return _FALSE;
                }
            }
            return _TRUE;

            break;

        case _OSD_ADVANCE_HUB_SWITCH:
#if(_D0_USB_HUB_SUPPORT == _OFF)
            if(ucIdx == _OSD_HUB_D0)
            {
                return _FALSE;
            }
#endif
#if(_D1_USB_HUB_SUPPORT == _OFF)
            if(ucIdx == _OSD_HUB_D1)
            {
                return _FALSE;
            }
#endif
            return _TRUE;
            break;

#if(_IMMERSIVE_NIGHT_SNIPER_FUNCTION == _ON)
        case _OSD_ADVANCE_NIGHT_SNIPER:
            if(GET_OSD_NIGHT_SNIPER(GET_OSD_SELECT_REGION()) == _OFF)
            {
                if(ucIdx != 0)
                {
                    return _FALSE;
                }
            }
            return _TRUE;
            break;
#endif

        default:
            return _TRUE;
            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
EnumOsdMenuStatus OsdDispGetUpLayer(EnumOsdItem enumOsdItem)
{
    WORD usOsdState = GET_OSD_STATE_PREVIOUS();
    WORD usLoop = 0;

    // Find last saved State
    switch(usOsdState)
    {
        case _MENU_PICTURE_ITEM:
            do
            {
                if((tOSD_PICTURE_ITEM_PRI[usLoop]) == enumOsdItem)
                {
                    return usOsdState;
                }
                usLoop++;
            }
            while(usLoop < _OSD_PICTURE_ITEM_AMOUNT);
            break;

        case _MENU_DISPLAY_ITEM:
            do
            {
                if((tOSD_DISPLAY_ITEM_PRI[usLoop]) == enumOsdItem)
                {
                    return usOsdState;
                }
                usLoop++;
            }
            while(usLoop < _OSD_DISPLAY_ITEM_AMOUNT);
            break;

        case _MENU_COLOR_ITEM:
            do
            {
                if((tOSD_COLOR_ITEM_PRI[usLoop]) == enumOsdItem)
                {
                    return usOsdState;
                }
                usLoop++;
            }
            while(usLoop < _OSD_COLOR_ITEM_AMOUNT);
            break;

        case _MENU_ADVANCE_ITEM:
            do
            {
                if((tOSD_ADVANCE_ITEM_PRI[usLoop]) == enumOsdItem)
                {
                    return usOsdState;
                }
                usLoop++;
            }
            while(usLoop < _OSD_ADVANCE_ITEM_AMOUNT);
            break;

        case _MENU_AUDIO_ITEM:
            do
            {
                if((tOSD_AUDIO_ITEM_PRI[usLoop]) == enumOsdItem)
                {
                    return usOsdState;
                }
                usLoop++;
            }
            while(usLoop < _OSD_AUDIO_ITEM_AMOUNT);
            break;

        case _MENU_OTHER_ITEM:
            do
            {
                if((tOSD_OTHER_ITEM_PRI[usLoop]) == enumOsdItem)
                {
                    return usOsdState;
                }
                usLoop++;
            }
            while(usLoop < _OSD_OTHER_ITEM_AMOUNT);
            break;

        case _MENU_MUTIP_ITEM:
            do
            {
                if((tOSD_MUTIP_ITEM_PRI[usLoop]) == enumOsdItem)
                {
                    return usOsdState;
                }
                usLoop++;
            }
            while(usLoop < _OSD_MUTIP_ITEM_AMOUNT);
            break;

        case _MENU_HDR_ITEM:
            do
            {
                if((tOSD_HDR_ITEM_PRI[usLoop]) == enumOsdItem)
                {
                    return usOsdState;
                }
                usLoop++;
            }
            while(usLoop < _OSD_HDR_ITEM_AMOUNT);
            break;

        case _MENU_QUICKLINK_ITEM:
            do
            {
                if((tOSD_QUICK_ITEM_PRI[usLoop]) == enumOsdItem)
                {
                    return usOsdState;
                }
                usLoop++;
            }
            while(usLoop < _OSD_QUICK_ITEM_AMOUNT);
            break;
#if(_DM_FUNCTION == _ON)
        case _MENU_DVISION_ITEM:
            do
            {
                if((tOSD_DVISION_ITEM_PRI[usLoop]) == enumOsdItem)
                {
                    return usOsdState;
                }
                usLoop++;
            }
            while(usLoop < _OSD_DVISION_ITEM_AMOUNT);
            break;

#endif
#if(_AUDIO_ARC_SUPPORT == _ON)
        case _MENU_AUDIO_ARC_EARC_ITEM:
            do
            {
                if((tOSD_AUDIO_ARC_ITEM_PRI[usLoop]) == enumOsdItem)
                {
                    return usOsdState;
                }
                usLoop++;
            }
            while(usLoop < _OSD_AUDIO_ARC_ITEM_AMOUNT);
            break;
#endif

        case _MENU_NONE:
        default:
            return usOsdState;
    }

    // find again for all
    for(usOsdState = _MENU_PICTURE_ITEM; usOsdState <= _MENU_QUICKLINK_ITEM; usOsdState++)
    {
        usLoop = 0;
        switch(usOsdState)
        {
            case _MENU_PICTURE_ITEM:
                do
                {
                    if((tOSD_PICTURE_ITEM_PRI[usLoop]) == enumOsdItem)
                    {
                        return usOsdState;
                    }
                    usLoop++;
                }
                while(usLoop < _OSD_PICTURE_ITEM_AMOUNT);
                break;

            case _MENU_DISPLAY_ITEM:
                do
                {
                    if((tOSD_DISPLAY_ITEM_PRI[usLoop]) == enumOsdItem)
                    {
                        return usOsdState;
                    }
                    usLoop++;
                }
                while(usLoop < _OSD_DISPLAY_ITEM_AMOUNT);
                break;

            case _MENU_COLOR_ITEM:
                do
                {
                    if((tOSD_COLOR_ITEM_PRI[usLoop]) == enumOsdItem)
                    {
                        return usOsdState;
                    }
                    usLoop++;
                }
                while(usLoop < _OSD_COLOR_ITEM_AMOUNT);
                break;

            case _MENU_ADVANCE_ITEM:
                do
                {
                    if((tOSD_ADVANCE_ITEM_PRI[usLoop]) == enumOsdItem)
                    {
                        return usOsdState;
                    }
                    usLoop++;
                }
                while(usLoop < _OSD_ADVANCE_ITEM_AMOUNT);
                break;

            case _MENU_AUDIO_ITEM:
                do
                {
                    if((tOSD_AUDIO_ITEM_PRI[usLoop]) == enumOsdItem)
                    {
                        return usOsdState;
                    }
                    usLoop++;
                }
                while(usLoop < _OSD_AUDIO_ITEM_AMOUNT);
                break;

            case _MENU_OTHER_ITEM:
                do
                {
                    if((tOSD_OTHER_ITEM_PRI[usLoop]) == enumOsdItem)
                    {
                        return usOsdState;
                    }
                    usLoop++;
                }
                while(usLoop < _OSD_OTHER_ITEM_AMOUNT);
                break;

            case _MENU_MUTIP_ITEM:
                do
                {
                    if((tOSD_MUTIP_ITEM_PRI[usLoop]) == enumOsdItem)
                    {
                        return usOsdState;
                    }
                    usLoop++;
                }
                while(usLoop < _OSD_MUTIP_ITEM_AMOUNT);
                break;

            case _MENU_HDR_ITEM:
                do
                {
                    if((tOSD_HDR_ITEM_PRI[usLoop]) == enumOsdItem)
                    {
                        return usOsdState;
                    }
                    usLoop++;
                }
                while(usLoop < _OSD_HDR_ITEM_AMOUNT);
                break;

            case _MENU_QUICKLINK_ITEM:
                do
                {
                    if((tOSD_QUICK_ITEM_PRI[usLoop]) == enumOsdItem)
                    {
                        return usOsdState;
                    }
                    usLoop++;
                }
                while(usLoop < _OSD_QUICK_ITEM_AMOUNT);
                break;
#if(_DM_FUNCTION == _ON)
            case _MENU_DVISION_ITEM:
                do
                {
                    if((tOSD_DVISION_ITEM_PRI[usLoop]) == enumOsdItem)
                    {
                        return usOsdState;
                    }
                    usLoop++;
                }
                while(usLoop < _OSD_DVISION_ITEM_AMOUNT);
                break;

#endif

            default:
                return usOsdState;
        }
    }

    return usOsdState;
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
BYTE OsdDispGetOsdItemIdx(EnumOsdItem enumOsdItem)
{
    WORD usLoop = 0;

    // Find last saved State
    switch(GET_OSD_STATE())
    {
        case _MENU_PICTURE_ITEM:
            do
            {
                if((tOSD_PICTURE_ITEM_PRI[usLoop]) == enumOsdItem)
                {
                    return usLoop;
                }
                usLoop++;
            }
            while(usLoop < _OSD_PICTURE_ITEM_AMOUNT);
            break;

        case _MENU_DISPLAY_ITEM:
            do
            {
                if((tOSD_DISPLAY_ITEM_PRI[usLoop]) == enumOsdItem)
                {
                    return usLoop;
                }
                usLoop++;
            }
            while(usLoop < _OSD_DISPLAY_ITEM_AMOUNT);
            break;

        case _MENU_COLOR_ITEM:
            do
            {
                if((tOSD_COLOR_ITEM_PRI[usLoop]) == enumOsdItem)
                {
                    return usLoop;
                }
                usLoop++;
            }
            while(usLoop < _OSD_COLOR_ITEM_AMOUNT);
            break;

        case _MENU_ADVANCE_ITEM:
            do
            {
                if((tOSD_ADVANCE_ITEM_PRI[usLoop]) == enumOsdItem)
                {
                    return usLoop;
                }
                usLoop++;
            }
            while(usLoop < _OSD_ADVANCE_ITEM_AMOUNT);
            break;

        case _MENU_AUDIO_ITEM:
            do
            {
                if((tOSD_AUDIO_ITEM_PRI[usLoop]) == enumOsdItem)
                {
                    return usLoop;
                }
                usLoop++;
            }
            while(usLoop < _OSD_AUDIO_ITEM_AMOUNT);
            break;

        case _MENU_OTHER_ITEM:
            do
            {
                if((tOSD_OTHER_ITEM_PRI[usLoop]) == enumOsdItem)
                {
                    return usLoop;
                }
                usLoop++;
            }
            while(usLoop < _OSD_OTHER_ITEM_AMOUNT);
            break;

        case _MENU_MUTIP_ITEM:
            do
            {
                if((tOSD_MUTIP_ITEM_PRI[usLoop]) == enumOsdItem)
                {
                    return usLoop;
                }
                usLoop++;
            }
            while(usLoop < _OSD_MUTIP_ITEM_AMOUNT);
            break;

        case _MENU_HDR_ITEM:
            do
            {
                if((tOSD_HDR_ITEM_PRI[usLoop]) == enumOsdItem)
                {
                    return usLoop;
                }
                usLoop++;
            }
            while(usLoop < _OSD_HDR_ITEM_AMOUNT);
            break;

        case _MENU_QUICKLINK_ITEM:
            do
            {
                if((tOSD_QUICK_ITEM_PRI[usLoop]) == enumOsdItem)
                {
                    return usLoop;
                }
                usLoop++;
            }
            while(usLoop < _OSD_QUICK_ITEM_AMOUNT);
            break;

        case _MENU_NONE:
        default:
            return usLoop;
    }

    return usLoop;
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdDispDirectMenu(EnumOsdItem enumOsdItem)
{
    g_usFontPointer1 = _OSD_PAGE_1_START;
    g_usFontPointer2 = _OSD_PAGE_2_START;

    OsdFuncDisableOsd();
    if(OsdDisp2ndMenuCheck(enumOsdItem) == _FALSE)
    {
        return;
    }
    UserCommonOsdWindowDisable(_OSD_WINDOW_ALL);
    OsdFuncApplyMap(WIDTH(_OSD_MAIN_MENU_WIDTH), HEIGHT(_OSD_MAIN_MENU_HEIGHT), COLOR(_CP_WHITE, _CP_BG));

#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
    OsdFuncMapRotation(GET_OSD_ROTATE_STATUS(), _OSD_MAP_A_REMAPPING_ENABLE, HEIGHT(_OSD_MAIN_MENU_HEIGHT), _OSD_MAP_B_REMAPPING_DISABLE, 0, _OSD_FONT_LIB_ROTATION_ENABLE);
#endif

    OsdFuncBlending(_OSD_TRANSPARENCY_WINDOW_AND_CHARACTER_BACKGROUND);
    OsdFuncTransparency(GET_OSD_TRANSPARENCY_STATUS());

    // Adjust Color Palette
    OsdPaletteSelectPalette(_PALETTE_MAIN_MENU);

    // set 2bit Font offest
    OsdFuncSet2BitIconOffset(_2BIT_ICON_OFFSET);

    OsdFontVLCLoadFont(_FONT1_GLOBAL);

    // Realtek Mark
    OsdFontPut1BitTable(ROW(0), COL(32), tOSD_iREALTEK, COLOR(_CP_WHITE, _CP_BG));

    // Set Gradient Window
    SET_OSD_WINDOW_GRANIENT_INDEX(_OSD_WIN_GRADIENT_0);
    SET_OSD_WINDOW_GRANIENT_WIN(_OSD_WINDOW_0);
    SET_OSD_WINDOW_GRADIENT_ENABLE_B(_ENABLE);
    SET_OSD_WINDOW_GRADIENT_DIRECTION(_OSD_WINDOW_GRADIENT_DIRECTION_VERTICAL);
    SET_OSD_WINDOW_GRADIENT_POLARITY_B(_OSD_WINDOW_GRADIENT_POLARITY_DECREASE);
    SET_OSD_WINDOW_GRADIENT_LEVEL_COLOR_R(_OSD_WINDOW_GRADIENT_LEVEL_PER_1);
    SET_OSD_WINDOW_GRADIENT_LEVEL_COLOR_G(_OSD_WINDOW_GRADIENT_LEVEL_PER_1);
    SET_OSD_WINDOW_GRADIENT_LEVEL_COLOR_B(_OSD_WINDOW_GRADIENT_LEVEL_PER_1);
    SET_OSD_WINDOW_GRADIENT_LEVEL_SETP(_OSD_WINDOW_GRADIENT_LEVEL_STEP_3);
    SET_OSD_WINDOW_GRADIENT_COLOR(_CP_BLUE_200);
    UserCommonOsdDrawWindowGradient(ROW(0), COL(0), WIDTH(g_ucOsdWidth) * 12, HEIGHT(g_ucOsdHeight) * 18);

    SET_OSD_WINDOW_BUTTON_TYPE(_OSD_WINDOW_BUTTON_TYPE_BORDER);
    SET_OSD_WINDOW_COLOR_BORDER(_CP_WHITE);
    SET_OSD_WINDOW_BORDER_PIXEL_WIDTH(1);
    SET_OSD_WINDOW_BORDER_PIXEL_HEIGHT(1);

    OsdWindowDrawingByFont(_OSD_WINDOW_0, ROW(0), COL(0), WIDTH(g_ucOsdWidth), HEIGHT(g_ucOsdHeight), _CP_BLUE_200);

    // key info
    OsdDispMainMenuKeyInfo(_KEY_INFO_ALL, _OSD_UNSELECT);
    OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, GET_OSD_HPOS(), GET_OSD_VPOS());

    SET_OSD_WINDOW_BORDER_PIXEL_WIDTH(1);
    SET_OSD_WINDOW_BORDER_PIXEL_HEIGHT(1);

    OsdWindowDrawingByFont(_OSD_WINDOW_1, ROW(3), COL(13), WIDTH(g_ucOsdWidth - 13), HEIGHT(g_ucOsdHeight - 5), _CP_LIGHTBLUE);
    OsdMenu3rdFrame();
    OsdDispItemValueUpdate(enumOsdItem);
    OsdDisp2ndMenuString(0, g_stOsdItemData.usStringIdx, _CP_BLUE);
    g_usBackupValue = g_stOsdItemData.usAdjValue;
    SET_OSD_STATE(g_stOsdItemData.usSubOsdState);
    OsdDisp3rdItemAdj(enumOsdItem, _OFF);

    OsdFuncEnableOsd();
    SET_OSD_STATE_PREVIOUS(_MENU_NONE);
}

#if(_PIXEL_SHIFT_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set Pixel Orbiting Status
// Input Value  :
// Output Value : _TRUE means support Pixel Orbiting
//--------------------------------------------------
void OsdDisplaySetPixelOrbitingCapability(void)
{
    g_enumPixelShiftState = _PIXEL_SHIFT_DEFAULT;

    if((GET_OSD_DISPLAY_MODE() != _OSD_DM_1P) ||
       (SysRegionGetDisplayState(_DISPLAY_RGN_1P) != _DISPLAY_STATE_ACTIVE) ||
#if(_EAGLE_SIGHT_SUPPORT == _ON)
       (UserCommonDisplayGetShowEagleSightWindow() == _ENABLE) ||
#endif
#if((_DRR_SUPPORT == _ON) && (_FW_PIXEL_SHIFT_MODE == _PIXEL_SHIFT_IN_IDOMAIN))
       ((GET_OSD_FREE_SYNC_STATUS() == _ON) || (UserCommonDrrGetType() != _DRR_NONE_TYPE)) ||
#endif
#if((_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON) && (_FW_PIXEL_SHIFT_MODE == _PIXEL_SHIFT_IN_IDOMAIN))
       (UserCommonRegionGetFrontBackModeSupport() == _TRUE) ||
#endif
       ((UserCommonColorGetColorSpace(SysRegionGetInputPort(_DISPLAY_RGN_1P))) == _COLOR_SPACE_YCBCR422) ||
       ((UserCommonColorGetColorSpace(SysRegionGetInputPort(_DISPLAY_RGN_1P))) == _COLOR_SPACE_YCBCR420))
    {
        SET_PIXEL_ORBITING_CAPABILITY(_OFF);
    }
    else
    {
        SET_PIXEL_ORBITING_CAPABILITY(_ON);
    }
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdDisplayPixelOrbitingAction(void)
{
    if((GET_PIXEL_ORBITING_CAPABILITY() == _ON) && (GET_OSD_PIXELSHIFT_STATUS() == _TRUE))
    {
        if(g_bflagMinuteON == _TRUE)
        {
            if(GET_PIXEL_ORBITING_TIME() > 0)
            {
                GET_PIXEL_ORBITING_TIME()--;
            }
            if(GET_PIXEL_ORBITING_TIME() == 0)
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_PIXEL_ORBITING_ACTION_MSG);
            }
            g_bflagMinuteON = _FALSE;
        }
    }
}
#endif

#endif // End of #if(_OSD_TYPE == _REALTEK_2020_OSD)
