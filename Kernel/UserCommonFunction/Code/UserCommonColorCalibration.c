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
// ID Code      : UserCommonColorCalibration.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_COMMON_COLOR_CALIBRATION__

#include "UserCommonInclude.h"
#include "ColorCalibration/UserCommonColorCalibration.h"

#if((_OGC_FUNCTION == _ON) || (_OCC_FUNCTION == _ON) || (_OGC_DICOM_FUNCTION == _ON) || (_UNIFORMITY_FUNCTION == _ON))

//****************************************************************************
// CODE TABLES
//****************************************************************************
//--------------------------------------------------
// Table of OGC/OCC/DICOM
//--------------------------------------------------
WORD code tOGC_GRAY_TABLE[] =
{
    252 * 4, 244 * 4, 232 * 4,
    216 * 4, 196 * 4, 172 * 4,
    148 * 4, 124 * 4, 96 * 4,
    68 * 4,  44 * 4,  24 * 4,
    12 * 4,  6 * 4,   2 * 4,
    0
};

#if(_OCC_FUNCTION == _ON)
BYTE code tSRGBByPass[] =
{
    0,0,0,0,0,0,
    0,0,0,0,0,0,
    0,0,0,0,0,0
};

BYTE code tSRGBHalf[] =
{
    0x01, 0x80, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x01, 0x80, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x01, 0x80,
};
//--------------------------------------------------
// sRGB Table for OCC
//--------------------------------------------------
#if(_OCC_LUT_MODE == _OFF)
WORD code tOCC_SRGB_TABLE[] =
{
    192 * 4,  80 * 4,  80 * 4,
    192 * 4, 192 * 4,  80 * 4,
    96 * 4, 192 * 4,  96 * 4,
    96 * 4, 192 * 4, 192 * 4,
    128 * 4, 128 * 4, 192 * 4,
    192 * 4, 128 * 4, 192 * 4,
    1023, 1023, 1023,
};
#else
WORD code tOCC_SRGB_TABLE[] =
{
    1023,0,0,
    0,1023,0,
    0,0,248 * 4,
    1023,1023,0,
    1023,0,248 * 4,
    0,1023,248 * 4,
    1023,1023,1023,

    128 * 4,0,0,
    0,128 * 4,0,
    0,0,128 * 4,
    128 * 4,128 * 4,0,
    128 * 4,0,128 * 4,
    0,128 * 4,128 * 4,
    96 * 4,96 * 4,96 * 4,

    192 * 4,0,0,
    0,192 * 4,0,
    0,0,192 * 4,
    192 * 4,192 * 4,0,
    192 * 4,0,192 * 4,
    0,192 * 4,192 * 4,
    192 * 4,192 * 4,192 * 4
};
#endif
#endif

WORD code tGAMMA_INDEX[] =
{
#if(_OGC_FUNCTION == _ON)
    _OGC_NONE_ADDRESS,
#if(_OGC_TOTAL_GAMMA > 1)
    _OGC_NONE_ADDRESS,
#if(_OGC_TOTAL_GAMMA > 2)
    _OGC_NONE_ADDRESS,
#if(_OGC_TOTAL_GAMMA > 3)
    _OGC_NONE_ADDRESS,
#if(_OGC_TOTAL_GAMMA > 4)
    _OGC_NONE_ADDRESS,
#if(_OGC_TOTAL_GAMMA > 5)
    _OGC_NONE_ADDRESS,
#endif
#endif
#endif
#endif
#endif
#endif

#if(_OCC_FUNCTION == _ON)
    _OCC_GAMMA10_ADDRESS,
#endif

#if(_OGC_DICOM_FUNCTION == _ON)
    _OGC_NONE_ADDRESS,
#if(_OGC_TOTAL_DICOM > 1)
    _OGC_NONE_ADDRESS,
#if(_OGC_TOTAL_DICOM > 2)
    _OGC_NONE_ADDRESS,
#if(_OGC_TOTAL_DICOM > 3)
    _OGC_NONE_ADDRESS,
#endif
#endif
#endif
#endif

#if(_BACKLIGHT_DIMMING_SUPPORT == _ON)
    _DIMMING_OCC_GAMMA10_ADDRESS,
#endif

#if(_FREESYNC_II_SUPPORT == _ON)
    _FREESYNC_II_OCC_GAMMA10_ADDRESS,
#endif
#if((_HDR10_SUPPORT == _ON) || (_TWO_BRI_CALIBRATION_TYPE >= _TWO_BRI_CALIBRATION_OGC_OCC_DICOM_HDR))
    _OCC_HDR10_GAMMA10_ADDRESS,
#if(_MULTI_BRI_CALIBRATION_TYPE >= _MULTI_BRI_THREE_CALIBRATION)
    _OCC_GAMMA10_MULTI_BRI_3_ADDRESS,
#if(_MULTI_BRI_CALIBRATION_TYPE >= _MULTI_BRI_FOUR_CALIBRATION)
    _OCC_GAMMA10_MULTI_BRI_4_ADDRESS,
#endif
#endif
#endif
};

WORD code tHDR10IGAMMA_INDEX[] =
{
    _OGC_HDR10_IG_1200_NOR_ADDRESS,
    _OGC_HDR10_IG_1200_DARK_ADDRESS,
    _OGC_HDR10_IG_4000_NOR_ADDRESS,
    _OGC_HDR10_IG_4000_DARK_ADDRESS,
    _OGC_HDR10_IG_10000_NOR_ADDRESS,
    _OGC_HDR10_IG_10000_DARK_ADDRESS,
    _OGC_HDR10_IG_540_NOR_ADDRESS,
    _OGC_HDR10_IG_540_DARK_ADDRESS,
    _OGC_HDR10_IG_NOTM_NOR_ADDRESS,
    _OGC_HDR10_IG_NOTM_DARK_ADDRESS,
    _OGC_HDR10_IG_NOTM_PEAK_NOR_ADDRESS,
    _OGC_HDR10_IG_NOTM_PEAK_DARK_ADDRESS,
    _OGC_HDR10_IG_540_FIXED_POINT_NOR_ADDRESS,
    _OGC_HDR10_IG_540_FIXED_POINT_DARK_ADDRESS,
    _OGC_HDR10_IG_1200_FIXED_POINT_NOR_ADDRESS,
    _OGC_HDR10_IG_1200_FIXED_POINT_DARK_ADDRESS,
    _OGC_HDR10_IG_4000_FIXED_POINT_NOR_ADDRESS,
    _OGC_HDR10_IG_4000_FIXED_POINT_DARK_ADDRESS,
    _OGC_HDR10_IG_10000_FIXED_POINT_NOR_ADDRESS,
    _OGC_HDR10_IG_10000_FIXED_POINT_DARK_ADDRESS,
    _OGC_HDR10_IG_NOTM_USER_DEF_PEAK_NOR_ADDRESS,
    _OGC_HDR10_IG_NOTM_USER_DEF_PEAK_DARK_ADDRESS,
    _OGC_HDR10_IG_NOTM_DISPLAY_HDR_1_1_ADDRESS,
    _OGC_HDR10_IG_ADAPTIVE_TM_LV1_NOR_ADDRESS,
    _OGC_HDR10_IG_ADAPTIVE_TM_LV1_DARK_ADDRESS,
    _OGC_HDR10_IG_ADAPTIVE_TM_LV2_NOR_ADDRESS,
    _OGC_HDR10_IG_ADAPTIVE_TM_LV2_DARK_ADDRESS,
    _OGC_HDR10_IG_ADAPTIVE_TM_LV3_NOR_ADDRESS,
    _OGC_HDR10_IG_ADAPTIVE_TM_LV3_DARK_ADDRESS,
    _OGC_HDR10_IG_ADAPTIVE_TM_LV4_NOR_ADDRESS,
    _OGC_HDR10_IG_ADAPTIVE_TM_LV4_DARK_ADDRESS,
    _OGC_HDR10_IG_540_USER_FIXED_NOR_ADDRESS,
    _OGC_HDR10_IG_540_USER_FIXED_DARK_ADDRESS,
    _OGC_HDR10_IG_1200_USER_FIXED_NOR_ADDRESS,
    _OGC_HDR10_IG_1200_USER_FIXED_DARK_ADDRESS,
    _OGC_HDR10_IG_4000_USER_FIXED_NOR_ADDRESS,
    _OGC_HDR10_IG_4000_USER_FIXED_DARK_ADDRESS,
    _OGC_HDR10_IG_10000_USER_FIXED_NOR_ADDRESS,
    _OGC_HDR10_IG_10000_USER_FIXED_DARK_ADDRESS,
};

#if(_BACKLIGHT_DIMMING_SUPPORT == _ON)
#if(_OGC_FUNCTION == _ON)
WORD code tDIMMINGIGAMMA_INDEX[] =
{
    _DIMMING_OGC_GAMMA1_ADDRESS,
#if(_OGC_TOTAL_GAMMA > 1)
    _DIMMING_OGC_GAMMA2_ADDRESS,
#if(_OGC_TOTAL_GAMMA > 2)
    _DIMMING_OGC_GAMMA3_ADDRESS,
#if(_OGC_TOTAL_GAMMA > 3)
    _DIMMING_OGC_GAMMA4_ADDRESS,
#if(_OGC_TOTAL_GAMMA > 4)
    _DIMMING_OGC_GAMMA5_ADDRESS,
#if(_OGC_TOTAL_GAMMA > 5)
    _DIMMING_OGC_GAMMA6_ADDRESS,
#endif
#endif
#endif
#endif
#endif
};
#endif
#endif

#if(_FREESYNC_II_SUPPORT == _ON)
WORD code tFREESYNC2IGAMMA_INDEX[] =
{
    _FREESYNC_II_IG_SRGB_ADDRESS,
    _FREESYNC_II_IG_BT709_ADDRESS,
    _FREESYNC_II_IG_GAMMA22_ADDRESS,
    _FREESYNC_II_IG_GAMMA26_ADDRESS,
    _FREESYNC_II_IG_PQINTERIM_ADDRESS,
    _FREESYNC_II_IG_PQ_ADDRESS,
};
#endif

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
WORD g_ppusColorGammaCount[][3] =
{
#if(_OGC_FUNCTION == _ON)
    {_OGC_GAMMA_TABLE_LENGTH, _OGC_GAMMA_TABLE_LENGTH, _OGC_GAMMA_TABLE_LENGTH},
#if(_OGC_TOTAL_GAMMA > 1)
    {_OGC_GAMMA_TABLE_LENGTH, _OGC_GAMMA_TABLE_LENGTH, _OGC_GAMMA_TABLE_LENGTH},
#if(_OGC_TOTAL_GAMMA > 2)
    {_OGC_GAMMA_TABLE_LENGTH, _OGC_GAMMA_TABLE_LENGTH, _OGC_GAMMA_TABLE_LENGTH},
#if(_OGC_TOTAL_GAMMA > 3)
    {_OGC_GAMMA_TABLE_LENGTH, _OGC_GAMMA_TABLE_LENGTH, _OGC_GAMMA_TABLE_LENGTH},
#if(_OGC_TOTAL_GAMMA > 4)
    {_OGC_GAMMA_TABLE_LENGTH, _OGC_GAMMA_TABLE_LENGTH, _OGC_GAMMA_TABLE_LENGTH},
#if(_OGC_TOTAL_GAMMA > 5)
    {_OGC_GAMMA_TABLE_LENGTH, _OGC_GAMMA_TABLE_LENGTH, _OGC_GAMMA_TABLE_LENGTH},
#endif
#endif
#endif
#endif
#endif
#endif  // End of #if(_OGC_SUPPORT == _ON)

#if(_OCC_FUNCTION == _ON)
    {2200, 2200, 2200},  // To be Edit
#endif

#if(_OGC_DICOM_FUNCTION == _ON)
    {_OGC_GAMMA_TABLE_LENGTH, _OGC_GAMMA_TABLE_LENGTH, _OGC_GAMMA_TABLE_LENGTH},
#if(_OGC_TOTAL_DICOM > 1)
    {_OGC_GAMMA_TABLE_LENGTH, _OGC_GAMMA_TABLE_LENGTH, _OGC_GAMMA_TABLE_LENGTH},
#if(_OGC_TOTAL_DICOM > 2)
    {_OGC_GAMMA_TABLE_LENGTH, _OGC_GAMMA_TABLE_LENGTH, _OGC_GAMMA_TABLE_LENGTH},
#if(_OGC_TOTAL_DICOM > 3)
    {_OGC_GAMMA_TABLE_LENGTH, _OGC_GAMMA_TABLE_LENGTH, _OGC_GAMMA_TABLE_LENGTH},
#endif
#endif
#endif
#endif

#if(_BACKLIGHT_DIMMING_SUPPORT == _ON)
    {2200, 2200, 2200},
#endif

#if(_FREESYNC_II_SUPPORT == _ON)
    {2200, 2200, 2200},
#endif
};

#if(_OCC_RGB_3D_GAMMA_SUPPORT == _ON)
WORD g_ppusColor3DGammaCount[][3] =
{
    {_OGC_GAMMA_TABLE_LENGTH, _OGC_GAMMA_TABLE_LENGTH, _OGC_GAMMA_TABLE_LENGTH},
#if(_OCC_RGB_3D_GAMMA_TOTAL_SET > 1)
    {_OGC_GAMMA_TABLE_LENGTH, _OGC_GAMMA_TABLE_LENGTH, _OGC_GAMMA_TABLE_LENGTH},
#if(_OCC_RGB_3D_GAMMA_TOTAL_SET > 2)
    {_OGC_GAMMA_TABLE_LENGTH, _OGC_GAMMA_TABLE_LENGTH, _OGC_GAMMA_TABLE_LENGTH},
#if(_OCC_RGB_3D_GAMMA_TOTAL_SET > 3)
    {_OGC_GAMMA_TABLE_LENGTH, _OGC_GAMMA_TABLE_LENGTH, _OGC_GAMMA_TABLE_LENGTH},
#if(_OCC_RGB_3D_GAMMA_TOTAL_SET > 4)
    {_OGC_GAMMA_TABLE_LENGTH, _OGC_GAMMA_TABLE_LENGTH, _OGC_GAMMA_TABLE_LENGTH},
#if(_OCC_RGB_3D_GAMMA_TOTAL_SET > 5)
    {_OGC_GAMMA_TABLE_LENGTH, _OGC_GAMMA_TABLE_LENGTH, _OGC_GAMMA_TABLE_LENGTH},
#endif
#endif
#endif
#endif
#endif
};
#endif

WORD g_usColorCTGainSavePos;
#if(_UNIFORMITY_FUNCTION == _ON)
BYTE g_ucColorUniformityLUTSaveBank = _UNIFORMITY_FLASH_BANK0;
BYTE g_ucColorUniformityLUTStartPosIndex;
WORD g_usColorUniformityLUTSavePos;
#endif
WORD g_usColorMatrixSavePos;
WORD g_usColorHLGLUTSavePos;
#if(_GLOBAL_DIMMING_OCC_TOOL_SUPPORT == _ON)
WORD g_usColorGDSavePos;
#endif
BYTE g_ucColorCalibrationType;
BYTE g_ucColorCalibrationTypeII;
BYTE g_ucColor3DLUTChecksumType;
BYTE g_ucColorUniformityChecksumType;
BYTE g_ucColorPatternType = _BG_PATTERN;

BYTE g_ucColorBacklightFlag;
#if(_DCIP3_NO_COMPRESSION_SUPPORT == _ON)
BYTE g_ucColorDCIP3MatrixType;
#endif
#if(_OCC_USER_DEFINE_SHIFT_1_BIT_SUPPORT == _ON)
BYTE g_ucColorUserDefineMatrixType;
#endif
#if(_OCC_GAMUT_NO_COMPRESSION_SUPPORT == _ON)
BYTE g_ucColorOCCMatrixType;
#endif
#if(_MULTI_BRI_CALIBRATION_TYPE != _MULTI_BRI_CALIBRATION_NONE)
BYTE g_ucColorMultiOCCType;
#endif
#if((_HDR10_SUPPORT == _ON) || (_BACKLIGHT_DIMMING_SUPPORT == _ON) || (_FREESYNC_II_SUPPORT == _ON))
BYTE g_ucColorIGLUTSavePos;
WORD g_usColor1025IGLUTSavePos;
#endif
#if(_SAVE_OGC_OCC_VERIFY_REPORT_SUPPORT == _ON)
WORD g_usColorVerifySavePos;
#endif
BYTE g_ucColorPatternIndex;
#if(_OCC_RGB_3D_GAMMA_SUPPORT == _ON)
BYTE g_ucColor3DLUTSaveBank = _OCC_RGB_3D_GAMMA_FLASH_BANK0;
BYTE g_ucColor3DLUTStartPosIndex;
WORD g_usColor3DLUTSavePos;
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Show Calibration Pattern
// Input Value  : WORD usRed, WORD usGreen, WORD usBlue
// Output Value : None
//--------------------------------------------------
void UserCommonColorCalibrationShowPattern(WORD usRed, WORD usGreen, WORD usBlue)
{
    if(g_ucColorPatternType == _BG_PATTERN)
    {
        ScalerDDomainBackgroundSetColor10bit(usRed, usGreen, usBlue, _DB_APPLY_POLLING);
    }
    else
    {
        UserCommonColorCalibrationShowDDomainPattern(usRed, usGreen, usBlue, g_ucColorPatternType);
    }
}
//--------------------------------------------------
// Description  : Calibration Pattern Enable
// Input Value  : bEnable
// Output Value : None
//--------------------------------------------------
void UserCommonColorCalibrationPatternEnable(bit bEnable)
{
    if(g_ucColorPatternType == _BG_PATTERN)
    {
        ScalerDDomainBackgroundEnable(_DDOMAIN_RGN_ALL, bEnable);
    }
    else
    {
        ScalerDDomainPatternGenEnable(bEnable);
    }
}
//--------------------------------------------------
// Description  : Do OGC/OCC/DICOM Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonColorCalibrationProcess(void)
{
    BYTE ucCalibrationStep = 0;
    BYTE ucFlag = 1;
#if((_OGC_FUNCTION == _ON) || (_FREESYNC_II_SUPPORT == _ON))
    BYTE ucGammaIndex = 0;
#endif

#if(_OGC_FUNCTION == _ON)
    BYTE ucColorTempIndex = 0;
    WORD pusBriTemp[3] = {0x200, 0x200, 0x200};
    WORD pusContrastData[3] = {0};
#endif

    WORD usR = 0;
    WORD usG = 0;
    WORD usB = 0;
    WORD usGray = 0;
    BYTE ucCountBank = 0;
    BYTE ucCountPage = 0;
    BYTE ucMaxPage = 0;
    BYTE ucColorGammaBankNum = 0;
    BYTE *pucColorGammaBankAddr = _NULL_POINTER;
#if(_OCC_RGB_3D_GAMMA_SUPPORT == _ON)
    BYTE uc3DLUTTypeIndex = 0;
    BYTE uc3DLUTBankNum = 0;
    BYTE *puc3DLUTTableAddr = _NULL_POINTER;
#endif
#if(_UNIFORMITY_FUNCTION == _ON)
    BYTE ucUniformityTypeIndex = 0;
    BYTE ucUniformityModeIndex = 0;
    BYTE ucGainTableBank = 0;
    WORD usGainTableAddr = 0;
#if(_UNIFORMITY_LEVEL0_SUPPORT == _ON)
    BYTE ucUniformityLevel0Enable = 0;
    BYTE ucOffsetTableBank = 0;
    BYTE ucOffsetTableStartBank = 0;
    WORD usOffsetTableAddr = 0;
    WORD usDecayTableAddr = 0;
#endif
#endif

#if(_OGC_DICOM_FUNCTION == _ON)
    BYTE ucDICOMIndex = 0;
#endif
    ScalerGlobalDoubleBufferEnable(_INPUT_PATH_ALL, _ENABLE);

    SET_INTERRUPT_ENABLE_STATUS(_INT_EXINT_1, _DISABLE);

    ucCalibrationStep = g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_STEP];

    SET_ON_LINE_CALIBRATION_STATUS(_CALIBRATION_ON);

    if(UserCommonColorCalibrationInitialCheck() == _SUCCESS)
    {
//****************************************************************************************//
//                               MEASURE PROCESS                                          //
//****************************************************************************************//
        /////////////////////////////////////////////////////////////////
        /////////////////////TOOL GET FW AUTHORIZATION///////////////////
        /////////////////////////////////////////////////////////////////
        if(ucCalibrationStep == _DDCCI_DISP_CALIB_GET_AUTHORIZE)
        {
            g_pucMcuDdcciTxBuf[_DDCCI_SOURCE] = _DDCCI_DEST_ADDRESS;
            g_pucMcuDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | 0x0D;
            ScalerColorGetAuthorize(g_pucMcuDdcciRxBuf + 5, &g_pucMcuDdcciTxBuf[_DDCCI_LENGTH + 1], 13);
            g_pucMcuDdcciTxBuf[15] = UserCommonDdcciCalCheckSum();

            ScalerMcuDdcciSendData(GET_RUN_DDCCI_HANDLE_CHANNEL(), g_pucMcuDdcciTxBuf);
            SET_INTERRUPT_ENABLE_STATUS(_INT_EXINT_1, _ENABLE);
            ScalerMcuDdcciReleaseScl();
            return;
        }
        /////////////////////////////////////////////////////////////////
        /////////////////////TOOL GET FW DEFINE//////////////////////////
        /////////////////////////////////////////////////////////////////
        if(ucCalibrationStep == _DDCCI_DISP_CALIB_GET_DEFINE)
        {
            UserCommonColorCalibrationReplyResult(_DISP_CALIB_START);
#if(_GLOBAL_DIMMING_OCC_TOOL_SUPPORT == _ON)
            SET_ON_LINE_GD_HDR_CALIBRATION_STATUS(_CALIBRATION_OFF);
#if(_GLOBAL_DIMMING_FUNCTION == _ON)
            UserCommonColorGlobalDimmingAdjust();
#endif
#endif
            UserInterfaceColorCalibrationBeforeProc(_OGC_CAL);
            ScalerMcuDdcciReleaseScl();

            return;
        }
        /////////////////////////////////////////////////////////////////
        /////////////////////TOOL GET FW INFO////////////////////////////
        /////////////////////////////////////////////////////////////////
        if(ucCalibrationStep == _DDCCI_DISP_CALIB_GET_FW_INFO)
        {
            if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_FW_INFO] == _DDCCI_DISP_CALIB_GET_FW_DEFINE)
            {
                UserCommonColorCalibrationReplyResult(_DISP_CALIB_START);
            }
            else if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_FW_INFO] == _DDCCI_DISP_CALIB_GET_FW_VERSION)
            {
                UserCommonColorCalibrationReplyResult(_DISP_CALIB_GET_VERSION);
            }
            else if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_FW_INFO] == _DDCCI_DISP_CALIB_GET_PANEL_LV_INFO)
            {
                UserCommonColorCalibrationReplyResult(_DISP_CALIB_GET_NOTM_INFO);
            }
            else if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_FW_INFO] == _DDCCI_DISP_CALIB_GET_UNIFORMITY_FW_VERSION)
            {
                UserCommonColorCalibrationReplyResult(_DISP_CALIB_GET_UNI_VERSION);
            }
            else if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_FW_INFO] == _DDCCI_DISP_CALIB_GET_FW_SUPPORT)
            {
                UserCommonColorCalibrationReplyResult(_DISP_CALIB_GET_FW_SUPPORT);
            }
            else if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_FW_INFO] == _DDCCI_DISP_CALIB_GET_PANEL_INFO)
            {
                UserCommonColorCalibrationReplyResult(_DISP_CALIB_GET_PANEL_INFO);
            }
            else if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_FW_INFO] == _DDCCI_DISP_CALIB_GET_FW_ADVANCE_DEFINE)
            {
                UserCommonColorCalibrationReplyResult(_DISP_CALIB_GET_FW_ADVANCE);
            }
            else if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_FW_INFO] == _DDCCI_DISP_CALIB_GET_GD_DEFINE)
            {
                UserCommonColorCalibrationReplyResult(_DISP_CALIB_GET_GD_SET);
            }
            else if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_FW_INFO] == _DDCCI_DISP_CALIB_GET_AUTHORIZE_VERSION)
            {
                UserCommonColorCalibrationReplyResult(_DISP_CALIB_GET_AUTH_VER);
            }
            ScalerMcuDdcciReleaseScl();
            return;
        }
        /////////////////////////////////////////////////////////////////
        /////////////////////END            /////////////////////////////
        /////////////////////////////////////////////////////////////////
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_END)
        {
            BYTE ucData = 1;
            UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _OCC_OGC_CALIBRATION_FINISH_ADDRESS, 1, &ucData);
#if(_FREESYNC_II_SUPPORT == _ON)
            UserCommonFlashWrite(_FREESYNC_II_FLASH_BANK, (((WORD)_FREESYNC_II_FLASH_PAGE) << 12) + _FREESYNC_II_FINISH_ADDRESS, 1, &ucData);
#endif
            SET_ON_LINE_CALIBRATION_STATUS(_CALIBRATION_OFF);
            UserInterfaceColorCalibrationAfterProc(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_END_TYPE]);
        }

        /////////////////////////////////////////////////////////////////
        //////////////DISPLAY CALIBRATION: MEASURE START/////////////////
        //////////////DISPLAY CALIBRATION: MEASURE RED///////////////////
        /////////////////////////////////////////////////////////////////
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_OGC_MEASURE_RED)
        {
            ucFlag &= UserCommonColorCalibrationOGCStart();

            UserCommonColorCalibrationPatternEnable(_ENABLE);
            UserCommonColorCalibrationShowPattern(_PATTERN_TOP, 0, 0);

            g_usColorCTGainSavePos = 0;
            g_usColorMatrixSavePos = 0;
            g_ucColorPatternIndex = 0;

            if(g_ucColorBacklightFlag == _NORMAL_BACKLIGHT_CAL)
            {
#if(_OGC_DICOM_FUNCTION == _ON)
                ucColorGammaBankNum = UserCommonColorGetDICOMBank(_OGC_TOTAL_DICOM);
                pucColorGammaBankAddr = UserCommonColorGetDICOMAddr(_OGC_TOTAL_DICOM);
#else
                ucColorGammaBankNum = UserCommonColorGetOGCBank(_OGC_GAMMA_MAX, _OGC_MAX_BACKLIGHT_TYPE);
                pucColorGammaBankAddr = UserCommonColorGetOGCAddr(_OGC_GAMMA_MAX, _OGC_MAX_BACKLIGHT_TYPE);
#endif
                for(ucCountBank = _OGC_FLASH_BANK; ucCountBank <= ucColorGammaBankNum; ucCountBank++)
                {
                    if(ucCountBank < ucColorGammaBankNum)
                    {
                        ucMaxPage = 15;
                    }
                    else
                    {
                        ucMaxPage = ((DWORD)pucColorGammaBankAddr + _OGC_GAMMA_TABLE_SIZE) / _FLASH_PAGE_SIZE;
                    }

                    for(ucCountPage = 0; ucCountPage <= ucMaxPage; ucCountPage++)
                    {
                        ucFlag &= UserCommonFlashErasePage(ucCountBank, ucCountPage);
                    }
                }
#if(_MULTI_BRI_CALIBRATION_TYPE != _MULTI_BRI_CALIBRATION_NONE)
                ucMaxPage = ((WORD)_DIMMING_OCC_GAMMA10_ADDRESS + _OCC_GAMMA_TABLE_SIZE) / _FLASH_PAGE_SIZE;
                for(ucCountPage = 0; ucCountPage <= ucMaxPage; ucCountPage++)
                {
                    ucFlag &= UserCommonFlashErasePage(_FREESYNC_II_FLASH_BANK, _FREESYNC_II_FLASH_PAGE + ucCountPage);
                }
#else
#if(_FREESYNC_II_SUPPORT == _ON)
                ucFlag &= UserCommonFlashErasePage(_FREESYNC_II_FLASH_BANK, _FREESYNC_II_FLASH_PAGE);
                ucFlag &= UserCommonFlashErasePage(_FREESYNC_II_FLASH_BANK, _FREESYNC_II_FLASH_PAGE + 1);
#if(_OCC_IG_NODE_1025_SUPPORT == _ON)
                ucFlag &= UserCommonFlashErasePage(_FREESYNC_II_FLASH_BANK, _FREESYNC_II_FLASH_PAGE + 2);
                ucFlag &= UserCommonFlashErasePage(_FREESYNC_II_FLASH_BANK, _FREESYNC_II_FLASH_PAGE + 3);
#endif
#endif
#endif
#if(_SAVE_OGC_OCC_VERIFY_REPORT_SUPPORT == _ON)
                for(ucCountPage = 0; ucCountPage <= 15; ucCountPage++)
                {
                    ucFlag &= UserCommonFlashErasePage(_OGC_OCC_VERIFY_REPORT_BANK, ucCountPage);
                }
                g_usColorVerifySavePos = 0;
#endif
#if(_OCC_RGB_3D_GAMMA_SUPPORT == _ON)
                uc3DLUTBankNum = UserCommonColorGetOCC3DGammaTableBank(_OCC_RGB_3D_GAMMA_TOTAL_SET - 1);
                for(ucCountBank = _OCC_RGB_3D_GAMMA_FLASH_BANK0; ucCountBank <= uc3DLUTBankNum; ucCountBank++)
                {
                    for(ucCountPage = 0; ucCountPage <= 15; ucCountPage++)
                    {
                        ucFlag &= UserCommonFlashErasePage(ucCountBank, ucCountPage);
                    }
                }

                uc3DLUTBankNum = UserCommonColorGet3DGammaOGCTableBank();
                for(ucCountPage = 0; ucCountPage <= 15; ucCountPage++)
                {
                    ucFlag &= UserCommonFlashErasePage(uc3DLUTBankNum, ucCountPage);
                }
#endif
            }
        }
        /////////////////////////////////////////////////////////////////
        //////////////DISPLAY CALIBRATION: MEASURE BLACK/////////////////
        /////////////////////////////////////////////////////////////////
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_OGC_MEASURE_BLACK)
        {
            UserCommonColorCalibrationShowPattern(0, 0, 0);
        }
        /////////////////////////////////////////////////////////////////
        //////////////DISPLAY CALIBRATION: MEASURE BLUE//////////////////
        /////////////////////////////////////////////////////////////////
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_OGC_MEASURE_BLUE)
        {
            UserCommonColorCalibrationShowPattern(0, 0, _PATTERN_TOP);
        }

        /////////////////////////////////////////////////////////////////
        //////////////DISPLAY CALIBRATION: MEASURE GREEN/////////////////
        /////////////////////////////////////////////////////////////////
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_OGC_MEASURE_GREEN)
        {
            UserCommonColorCalibrationShowPattern(0, _PATTERN_TOP, 0);
        }

        /////////////////////////////////////////////////////////////////
        //////////////DISPLAY CALIBRATION: MEASURE WHITE/////////////////
        /////////////////////////////////////////////////////////////////
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_OGC_MEASURE_WHITE)
        {
            UserCommonColorCalibrationShowPattern(_PATTERN_TOP, _PATTERN_TOP, _PATTERN_TOP);
        }

        /////////////////////////////////////////////////////////////////
        //////////////DISPLAY CALIBRATION: MEASURE GRAY1~7///////////////
        /////////////////////////////////////////////////////////////////
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_OGC_MEASURE_GRAY1TO7)
        {
            usGray = (g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_GRAY_HIGH] << 8) | (g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_GRAY_LOW]);

            UserCommonColorCalibrationShowPattern(usGray, usGray, usGray);
        }

        /////////////////////////////////////////////////////////////////
        ////////////DISPLAY CALIBRATION: MEASURE GRAY1 / GRAY2///////////
        /////////////////////Save RGB CT gains///////////////////////////
        /////////////////////////////////////////////////////////////////
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_OGC_MEASURE_GRAY1)
        {
            if(g_usColorCTGainSavePos == 0)
            {
                UserCommonColorCalibrationShowPattern(
                    tOGC_GRAY_TABLE[ucCalibrationStep - _DDCCI_DISP_CALIB_OGC_MEASURE_GRAY1],
                    tOGC_GRAY_TABLE[ucCalibrationStep - _DDCCI_DISP_CALIB_OGC_MEASURE_GRAY1],
                    tOGC_GRAY_TABLE[ucCalibrationStep - _DDCCI_DISP_CALIB_OGC_MEASURE_GRAY1]);
            }

            /****************** Save RGB Gain to Flash******************/
            /* CT/Gamma   Gamma1     Gamma2    Gamma3   Gamma4   Gamma5*/
            /*    CT1     R/G/B      R/G/B     R/G/B    R/G/B    R/G/B */
            /*    CT2     R/G/B      R/G/B     R/G/B    R/G/B    R/G/B */
            /*    CT3     R/G/B      R/G/B     R/G/B    R/G/B    R/G/B */
            /*    CT4     R/G/B      R/G/B     R/G/B    R/G/B    R/G/B */
            /*    CT5     R/G/B      R/G/B     R/G/B    R/G/B    R/G/B */
            /*    User    R/G/B      R/G/B     R/G/B    R/G/B    R/G/B */
            /************************************************************/

#if(_OGC_FUNCTION == _ON)
            if(g_ucColorBacklightFlag == _NORMAL_BACKLIGHT_CAL)
            {
                UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _OGC_RGB_GAIN_ADDRESS + g_usColorCTGainSavePos, (g_pucMcuDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 4, &g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_RGB_GAIN]);
                g_usColorCTGainSavePos += (g_pucMcuDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 4;
            }
#if(_TWO_BRI_CALIBRATION_TYPE >= _TWO_BRI_CALIBRATION_OGC_OCC_DICOM_HDR)
            else if(g_ucColorBacklightFlag == _MAX_BACKLIGHT_CAL)
            {
                UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _OGC_RGB_GAIN_MAX_BRI_ADDRESS + g_usColorCTGainSavePos, (g_pucMcuDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 4, &g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_RGB_GAIN]);
                g_usColorCTGainSavePos += (g_pucMcuDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 4;
            }
#if(_TWO_BRI_CALIBRATION_TYPE >= _MULTI_BRI_CALIBRATION_OGC_OCC)
            else if(g_ucColorBacklightFlag == _MULTI_BACKLIGHT_3_CAL)
            {
                UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _OGC_RGB_GAIN_MULTI_BRI_3_CAL_ADDRESS + g_usColorCTGainSavePos, (g_pucMcuDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 4, &g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_RGB_GAIN]);
                g_usColorCTGainSavePos += (g_pucMcuDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 4;
            }
#if(_MULTI_BRI_CALIBRATION_TYPE >= _MULTI_BRI_FOUR_CALIBRATION)
            else if(g_ucColorBacklightFlag == _MULTI_BACKLIGHT_4_CAL)
            {
                UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _OGC_RGB_GAIN_MULTI_BRI_4_CAL_ADDRESS + g_usColorCTGainSavePos, (g_pucMcuDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 4, &g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_RGB_GAIN]);
                g_usColorCTGainSavePos += (g_pucMcuDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 4;
            }
#endif
#endif
#endif
#endif
        }
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_OGC_MEASURE_GRAY2)
        {
            UserCommonColorCalibrationShowPattern(
                tOGC_GRAY_TABLE[ucCalibrationStep - _DDCCI_DISP_CALIB_OGC_MEASURE_GRAY1],
                tOGC_GRAY_TABLE[ucCalibrationStep - _DDCCI_DISP_CALIB_OGC_MEASURE_GRAY1],
                tOGC_GRAY_TABLE[ucCalibrationStep - _DDCCI_DISP_CALIB_OGC_MEASURE_GRAY1]);

            if(g_ucColorBacklightFlag == _NORMAL_BACKLIGHT_CAL)
            {
                UserCommonColorCalibrationSaveHeader();
            }
        }

        /////////////////////////////////////////////////////////////////
        ////////////DISPLAY CALIBRATION: MEASURE GRAY3 ~ GRAY20//////////
        //////////////////////////SAVE LUT///////////////////////////////
        /////////////////////////////////////////////////////////////////
        else if((ucCalibrationStep >= _DDCCI_DISP_CALIB_OGC_MEASURE_GRAY3) && (ucCalibrationStep <= _DDCCI_DISP_CALIB_OGC_MEASURE_LAST_GRAY))
        {
            if((g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_LUT_LENGTH] == 2) && (g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_LUT_ID] == 0xFF))
            {
                UserCommonColorCalibrationShowPattern(
                    tOGC_GRAY_TABLE[ucCalibrationStep - _DDCCI_DISP_CALIB_OGC_MEASURE_GRAY1],
                    tOGC_GRAY_TABLE[ucCalibrationStep - _DDCCI_DISP_CALIB_OGC_MEASURE_GRAY1],
                    tOGC_GRAY_TABLE[ucCalibrationStep - _DDCCI_DISP_CALIB_OGC_MEASURE_GRAY1]);
            }
#if(_OCC_RGB_3D_GAMMA_SUPPORT == _ON)
            else if((g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_LUT_LENGTH] == 0x03) && (g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_LUT_ID] == 0xFF))
            {
                UserCommonColorCalibrationSave3DGammaOGCLUT((g_pucMcuDdcciRxBuf[_DDCCI_LENGTH] & 0x7F));
            }
#endif
            else
            {
                UserCommonColorCalibrationSaveLUT((g_pucMcuDdcciRxBuf[_DDCCI_LENGTH] & 0x7F));
            }
        }

        /////////////////////////////////////////////////////////////////
        //////////////DISPLAY CALIBRATION: MEASURE GRAY0 ~ GRAY255///////
        /////////////////////////////////////////////////////////////////
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_CHANGE_PATTERN)
        {
            if((g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_LUT_LENGTH] == 2) && (g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_LUT_ID] == 0xFF))
            {
                usR = (g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_RCODE] << 8) | (g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_RCODE + 1]);
                usG = (g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_GCODE] << 8) | (g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_GCODE + 1]);
                usB = (g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_BCODE] << 8) | (g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_BCODE + 1]);
                UserCommonColorCalibrationShowPattern(usR, usG, usB);
                g_ucColorPatternIndex += 1;
            }
            else
            {
                if(g_ucColorPatternIndex == 1)
                {
                    /****************** Save RGB Gain to Flash******************/
                    /* CT/Gamma   Gamma1     Gamma2    Gamma3   Gamma4   Gamma5*/
                    /*    CT1     R/G/B      R/G/B     R/G/B    R/G/B    R/G/B */
                    /*    CT2     R/G/B      R/G/B     R/G/B    R/G/B    R/G/B */
                    /*    CT3     R/G/B      R/G/B     R/G/B    R/G/B    R/G/B */
                    /*    CT4     R/G/B      R/G/B     R/G/B    R/G/B    R/G/B */
                    /*    CT5     R/G/B      R/G/B     R/G/B    R/G/B    R/G/B */
                    /*    User    R/G/B      R/G/B     R/G/B    R/G/B    R/G/B */
                    /************************************************************/

#if(_OGC_FUNCTION == _ON)
                    if(g_ucColorBacklightFlag == _NORMAL_BACKLIGHT_CAL)
                    {
                        UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _OGC_RGB_GAIN_ADDRESS + g_usColorCTGainSavePos, (g_pucMcuDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 4, &g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_RGB_GAIN]);
                        g_usColorCTGainSavePos += (g_pucMcuDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 4;
                    }
#if(_TWO_BRI_CALIBRATION_TYPE >= _TWO_BRI_CALIBRATION_OGC_OCC_DICOM_HDR)
                    else if(g_ucColorBacklightFlag == _MAX_BACKLIGHT_CAL)
                    {
                        UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _OGC_RGB_GAIN_MAX_BRI_ADDRESS + g_usColorCTGainSavePos, (g_pucMcuDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 4, &g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_RGB_GAIN]);
                        g_usColorCTGainSavePos += (g_pucMcuDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 4;
                    }
#if(_TWO_BRI_CALIBRATION_TYPE >= _MULTI_BRI_CALIBRATION_OGC_OCC)
                    else if(g_ucColorBacklightFlag == _MULTI_BACKLIGHT_3_CAL)
                    {
                        UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _OGC_RGB_GAIN_MULTI_BRI_3_CAL_ADDRESS + g_usColorCTGainSavePos, (g_pucMcuDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 4, &g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_RGB_GAIN]);
                        g_usColorCTGainSavePos += (g_pucMcuDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 4;
                    }
#if(_MULTI_BRI_CALIBRATION_TYPE >= _MULTI_BRI_FOUR_CALIBRATION)
                    else if(g_ucColorBacklightFlag == _MULTI_BACKLIGHT_4_CAL)
                    {
                        UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _OGC_RGB_GAIN_MULTI_BRI_4_CAL_ADDRESS + g_usColorCTGainSavePos, (g_pucMcuDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 4, &g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_RGB_GAIN]);
                        g_usColorCTGainSavePos += (g_pucMcuDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 4;
                    }
#endif
#endif
#endif
#endif
                }
                else if(g_ucColorPatternIndex == 2)
                {
                    if(g_ucColorBacklightFlag == _NORMAL_BACKLIGHT_CAL)
                    {
                        UserCommonColorCalibrationSaveHeader();
                    }
                }
                else
                {
                    UserCommonColorCalibrationSaveLUT((g_pucMcuDdcciRxBuf[_DDCCI_LENGTH] & 0x7F));
                }
            }
        }

        /////////////////////////////////////////////////////////////////
        //////////////DISPLAY CALIBRATION: MEASURE END///////////////////
        /////////////////////////////////////////////////////////////////
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_OGC_MEASURE_END)
        {
            ucFlag = UserCommonColorCalibrationCheckSum();

            UserCommonColorCalibrationShowGamma();
        }
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_CHK_COLORMATRIX)
        {
            ucFlag = UserCommonColorCalibrationMatrixCheckSum(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_COLORMATRIX_TYPE]);

#if(_BACKLIGHT_DIMMING_SUPPORT == _ON)
            g_ucColorIGLUTSavePos = 0;
            g_usColor1025IGLUTSavePos = 0;
            g_usColorCTGainSavePos = 0;
#endif
        }
#if(_HDR10_SUPPORT == _ON)
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_SAVE_IGLUT)
        {
            if(g_ucColorIGLUTSavePos > 195)
            {
                g_ucColorIGLUTSavePos = 0;
            }

            UserCommonFlashWrite(_OGC_FLASH_BANK, tHDR10IGAMMA_INDEX[g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_IGLUT_INDEX]] + g_ucColorIGLUTSavePos, (g_pucMcuDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 5, &g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_IGLUT_START]);
            g_ucColorIGLUTSavePos += (g_pucMcuDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 5;
        }
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_SAVE_1025NODE_IGLUT)
        {
            if(g_usColor1025IGLUTSavePos > 1539)
            {
                g_usColor1025IGLUTSavePos = 0;
            }

            UserCommonFlashWrite(_OGC_FLASH_BANK, tHDR10IGAMMA_INDEX[g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_IGLUT_INDEX]] + g_usColor1025IGLUTSavePos, (g_pucMcuDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 5, &g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_IGLUT_START]);
            g_usColor1025IGLUTSavePos += (g_pucMcuDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 5;
        }
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_SET_HDR_MODE)
        {
            UserCommonColorCalibrationIPBypass();

            // Set Input Gamma
            ScalerColorPCMSetPCMMode(_1P_NORMAL_REGION, _PCM_MODE);
            ScalerColorPCMInputGammaAdjust(_1P_NORMAL_REGION, g_pucColorDISP_CALIBRATION_FLASH + _OGC_HDR10_IG_1200_NOR_ADDRESS + (g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_SET_HDR_IG_INDEX] * _OGC_HDR10_IG_TABLE_SIZE), _OGC_FLASH_BANK, _IG_DB_DISABLE);

#if(_OCC_RGB_3D_GAMMA_HDR10_REMAP_SUPPORT == _ON)
            ScalerColorPCMOutputGammaAdjust(_1P_NORMAL_REGION, g_pucColorDISP_CALIBRATION_FLASH + _OCC_GAMMA10_ADDRESS, _OCC_GAMMA_FLASH_BANK);
#else
            ScalerColorPCMOutputGammaAdjust(_1P_NORMAL_REGION, g_pucColorDISP_CALIBRATION_FLASH + _OCC_HDR10_GAMMA10_ADDRESS, _OCC_GAMMA_FLASH_BANK);
#endif

            // Set Color Matrix
            ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _SRGB_1_BIT_SHIFT_LEFT, g_pucColorDISP_CALIBRATION_FLASH + _OCC_HDR10_SRGB_MATRIX_ADDRESS + (g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_SET_HDR_COLOR_MATRIX] * _OCC_COLORMATRIX_TABLE_SIZE), _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);

            ScalerColorOutputGammaEnable(_FUNCTION_ON);
#if(_COLOR_IP_SRGB == _ON)
            ScalerColorSRGBEnable(_FUNCTION_ON);
#endif
            ScalerColorPCMInputGammaEnable(_FUNCTION_ON);
#if(_HW_D_DOMAIN_RGN_COUNT_MAX > 1)
            ScalerColorPCMSetEffectiveRegion(_HLW_INSIDEB_OUTSIDEA, _DB_APPLY_NO_POLLING);
#endif
#if(_COLOR_IP_I_GAMMA == _ON)
            ScalerColorPCMRegionEnable(_1P_NORMAL_REGION, _DB_APPLY_POLLING, _ON);
#endif
        }
#endif
#if(_ADVANCED_HDR10_SUPPORT == _ON)
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_SAVE_ADVANCED_HDR10_IGLUT)
        {
            if(g_ucColorIGLUTSavePos > 195)
            {
                g_ucColorIGLUTSavePos = 0;
            }

            if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_IGLUT_INDEX] < 40)
            {
                UserCommonFlashWrite(_OGC_FLASH_BANK, _OGC_ADVANCED_HDR10_IG_NOTM_DARK_ADDRESS + _OGC_HDR10_IG_129_NODE_TABLE_SIZE * g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_IGLUT_INDEX] + g_ucColorIGLUTSavePos, (g_pucMcuDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 5, &g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_IGLUT_START]);
            }
            g_ucColorIGLUTSavePos += (g_pucMcuDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 5;
        }
#endif
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_SET_BACKLIGHT)
        {
#if(_MULTI_BRI_CALIBRATION_TYPE != _MULTI_BRI_CALIBRATION_NONE)
            if((g_ucColorBacklightFlag == _MULTI_BACKLIGHT_3_CAL) || (g_ucColorBacklightFlag == _MULTI_BACKLIGHT_4_CAL))
            {
                UserInterfaceColorCalibrationAdjustMultiBacklight(g_ucColorBacklightFlag);
            }
            else
#endif
            {
                UserInterfaceColorCalibrationAdjustBacklight(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_BACKLIGHT_INDEX]);
            }
        }
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_SAVE_EDID_INFO)
        {
            UserCommonColorCalibrationSaveEDIDInfo();
        }
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_SAVE_NOTM_DCR_THD)
        {
            UserCommonColorCalibrationSaveNoToneMappingDCRTHD();
        }
#if(_HDR10_SUPPORT == _ON)
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_SAVE_HDR10_NOTM_BOUNG)
        {
            UserCommonColorCalibrationSaveHDR10BoundInfo();
        }
#endif
#if(_FREESYNC_II_SUPPORT == _ON)
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_FREESYNC_II_MEASURE_WHITE)
        {
            UserCommonColorCalibrationShowWhite(_FREESYNC_II_WHITE);
        }
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_SAVE_FREESYNC_II_IGLUT)
        {
#if(_OCC_IG_NODE_1025_SUPPORT == _ON)
            if(g_usColor1025IGLUTSavePos > 1539)
            {
                g_usColor1025IGLUTSavePos = 0;
            }

            UserCommonFlashWrite(_FREESYNC_II_FLASH_BANK, tFREESYNC2IGAMMA_INDEX[g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_FREESYNC_II_IGLUT_INDEX] & 0x0F] + g_usColor1025IGLUTSavePos, (g_pucMcuDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 5, &g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_FREESYNC_II_IGLUT_START]);
            g_usColor1025IGLUTSavePos += (g_pucMcuDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 5;
#else
            if(g_ucColorIGLUTSavePos > 195)
            {
                g_ucColorIGLUTSavePos = 0;
            }

            UserCommonFlashWrite(_FREESYNC_II_FLASH_BANK, tFREESYNC2IGAMMA_INDEX[g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_FREESYNC_II_IGLUT_INDEX] & 0x0F] + g_ucColorIGLUTSavePos, (g_pucMcuDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 5, &g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_FREESYNC_II_IGLUT_START]);
            g_ucColorIGLUTSavePos += (g_pucMcuDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 5;
#endif
        }
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_SAVE_PANEL_NATIVE_MATRIX)
        {
            UserCommonFlashWrite(_FREESYNC_II_FLASH_BANK, _FREESYNC_II_PANEL_NATIVE_MATRIX_ADDRESS, (g_pucMcuDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 4, &g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_FREESYNC_II_MATRIX_START]);
        }
#endif
#if(_BACKLIGHT_DIMMING_SUPPORT == _ON)
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_LD_COMMAND)
        {
            if((g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_IGLUT_INDEX] >> 4) == _DIMMING_COMMAND_SAVE_IG)
            {
#if(_OGC_FUNCTION == _ON)
#if(_OCC_IG_NODE_1025_SUPPORT == _ON)
                if(g_usColor1025IGLUTSavePos > 1539)
                {
                    g_usColor1025IGLUTSavePos = 0;
                }
                UserCommonFlashWrite(_OGC_FLASH_BANK, tDIMMINGIGAMMA_INDEX[g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_IGLUT_INDEX] & 0x0F] + g_usColor1025IGLUTSavePos, (g_pucMcuDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 5, &g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_IGLUT_START]);
                g_usColor1025IGLUTSavePos += (g_pucMcuDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 5;
#else
                if(g_ucColorIGLUTSavePos > 195)
                {
                    g_ucColorIGLUTSavePos = 0;
                }

                UserCommonFlashWrite(_OGC_FLASH_BANK, tDIMMINGIGAMMA_INDEX[g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_IGLUT_INDEX] & 0x0F] + g_ucColorIGLUTSavePos, (g_pucMcuDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 5, &g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_IGLUT_START]);
                g_ucColorIGLUTSavePos += (g_pucMcuDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 5;
#endif
#endif
            }
            else if((g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_IGLUT_INDEX] >> 4) == _DIMMING_COMMAND_SAVE_GAIN)
            {
                UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _DIMMING_OGC_RGB_GAIN_ADDRESS + g_usColorCTGainSavePos, (g_pucMcuDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 5, &g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_IGLUT_START]);
                g_usColorCTGainSavePos += (g_pucMcuDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 5;
            }
#if(_OGC_FUNCTION == _ON)
            else if((g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_IGLUT_INDEX] >> 4) == _DIMMING_COMMAND_SET_GAMMMA)
            {
                ucGammaIndex = (g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_IGLUT_START] >> 4) & 0x0F;
                ucColorTempIndex = g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_IGLUT_START] & 0x0F;

                UserCommonColorCalibrationIPBypass();

                ScalerColorPCMInputGammaAdjust(_1P_NORMAL_REGION, g_pucColorDISP_CALIBRATION_FLASH + _DIMMING_OGC_GAMMA1_ADDRESS + (ucGammaIndex * _OGC_HDR10_IG_TABLE_SIZE), _OGC_FLASH_BANK, _IG_DB_DISABLE);

                // Set PCM Color Matrix
                ScalerColorPCMSetPCMMode(_1P_NORMAL_REGION, _PCM_MODE);

                ScalerColorPCMOutputGammaAdjust(_1P_NORMAL_REGION, g_pucColorDISP_CALIBRATION_FLASH + _DIMMING_OCC_GAMMA10_ADDRESS, _OCC_GAMMA_FLASH_BANK);

                // Set PCM Color Matrix
#if(_PCM_FUNCTION == _ON)
                ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _SRGB_1_BIT_SHIFT_LEFT, ScalerColorsRGBBypassGetTableAddress(_SRGB_HALF), ScalerColorsRGBBypassGetTableBank(), 18);
#endif
                ScalerColorOutputGammaEnable(_FUNCTION_ON);
#if(_COLOR_IP_SRGB == _ON)
                ScalerColorSRGBEnable(_FUNCTION_ON);
#endif
                ScalerColorPCMInputGammaEnable(_FUNCTION_ON);

#if(_HW_D_DOMAIN_RGN_COUNT_MAX > 1)
                ScalerColorPCMSetEffectiveRegion(_HLW_INSIDEB_OUTSIDEA, _DB_APPLY_NO_POLLING);
#endif

#if(_COLOR_IP_I_GAMMA == _ON)
                ScalerColorPCMRegionEnable(_1P_NORMAL_REGION, _DB_APPLY_POLLING, _ON);
#endif

#if(_COLOR_IP_BRIGHTNESS == _ON)
                ScalerColorBrightnessAdjust(_1P_NORMAL_REGION, pusBriTemp);
#endif

                if(ucColorTempIndex != 0x0F)
                {
                    UserCommonFlashRead(_OGC_FLASH_BANK, ((WORD)_OGC_FLASH_PAGE << 12) | (ucColorTempIndex * _OGC_TOTAL_GAMMA * 6 + ucGammaIndex * 6 + _DIMMING_OGC_RGB_GAIN_ADDRESS), 6, pData);
                }
                else // Native
                {
                    pData[0] = 0x08;
                    pData[1] = 0x00;
                    pData[2] = 0x08;
                    pData[3] = 0x00;
                    pData[4] = 0x08;
                    pData[5] = 0x00;
                }

                // Construct contrast data format
                pusContrastData[0] = TO_WORD(pData[0], pData[1]);
                pusContrastData[1] = TO_WORD(pData[2], pData[3]);
                pusContrastData[2] = TO_WORD(pData[4], pData[5]);
#if(_COLOR_IP_CONTRAST == _ON)
                ScalerColorContrastAdjust(_1P_NORMAL_REGION, pusContrastData);
                ScalerColorContrastEnable(_FUNCTION_ON);
#endif
            }
#endif
        }
#endif
#if(_LOCAL_DIMMING_GLOBAL_BOOST_SUPPORT == _ON)
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_LD_BOOST_COMMAND)
        {
            if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_BOOST_INDEX] == _DDCCI_DISP_CALIB_BOOST_ON)
            {
                UserCommonColorCalibrationShowWhite(_LD_BOOST_WHITE);
                UserInterfaceColorCalibrationLDBoostAdjust(_ON);
#if(_SPI_BACKLIGHT_DIMMING_SUPPORT == _ON)
                UserCommonSpiDimmingManualApplyUpdateSync();
#endif
            }
            else if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_BOOST_INDEX] == _DDCCI_DISP_CALIB_BOOST_OFF)
            {
                UserInterfaceColorCalibrationLDBoostAdjust(_OFF);
#if(_SPI_BACKLIGHT_DIMMING_SUPPORT == _ON)
                UserCommonSpiDimmingManualApplyUpdateSync();
#endif
            }
            else if (g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_BOOST_INDEX] == _DDCCI_DISP_CALIB_DIMMING_SAVE_GAIN)
            {
                UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _LOCAL_DIMMING_GAIN_ADDRESS, (g_pucMcuDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 5, &g_pucMcuDdcciRxBuf[_DDCCI_DISP_DIMMING_BOOST_GAIN_INDEX]);
            }
        }
#endif

        /////////////////////////////////////////////////////////////////
        ////////////////////////OCC PROCESS//////////////////////////////
        /////////////////////////////////////////////////////////////////
#if(_OCC_FUNCTION == _ON)
        if(((g_ucColorCalibrationType >> _OCC_CAL_TYPE) & 0x01) == _TRUE)
        {
            UserCommonColorCalibrationOCCProcess(ucCalibrationStep);
        }
#endif


//****************************************************************************************//
//                               VERIFICATION PROCESS                                     //
//****************************************************************************************//
        /////////////////////////////////////////////////////////////////
        //////////////////////////VERIFICATION///////////////////////////
        /////////////////////////////////////////////////////////////////
        if(ucCalibrationStep == _DDCCI_DISP_CALIB_VERIFICATION)
        {
            usR = (g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_VERIFY_RED] << 8) | (g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_VERIFY_RED + 1]);
            usG = (g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_VERIFY_GREEN] << 8) | (g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_VERIFY_GREEN + 1]);
            usB = (g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_VERIFY_BLUE] << 8) | (g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_VERIFY_BLUE + 1]);

            UserCommonColorCalibrationShowDDomainPattern(usR, usG, usB, g_ucColorPatternType);
            ScalerDDomainPatternGenEnable(_ENABLE);
            ScalerDDomainBackgroundEnable(_DDOMAIN_RGN_ALL, _DISABLE);
        }

        /////////////////////////////////////////////////////////////////
        ///////////////////////SET GAMMA PROCESS/////////////////////////
        /////////////////////////////////////////////////////////////////
#if(_OGC_FUNCTION == _ON)
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_SET_GAMMA)
        {
            ucGammaIndex = (g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_INDEX] >> 4) & 0x0F;
            ucColorTempIndex = g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_INDEX] & 0x0F;

            UserCommonColorCalibrationIPBypass();

#if(_HW_D_DOMAIN_RGN_COUNT_MAX > 1)
            ScalerColorGammaSetEffectiveRegion(_HLW_INSIDEB_OUTSIDEA, _DB_APPLY_NO_POLLING);
#endif

#if(_TWO_BRI_CALIBRATION_TYPE >= _TWO_BRI_CALIBRATION_OGC_OCC_DICOM_HDR)
            if(g_ucColorBacklightFlag == _MAX_BACKLIGHT_CAL)
            {
                ucColorGammaBankNum = UserCommonColorGetOGCBank(ucGammaIndex, _OGC_MAX_BACKLIGHT_TYPE);
                pucColorGammaBankAddr = UserCommonColorGetOGCAddr(ucGammaIndex, _OGC_MAX_BACKLIGHT_TYPE);
            }
#if(_TWO_BRI_CALIBRATION_TYPE >= _MULTI_BRI_CALIBRATION_OGC_OCC)
            // Multi Bri 3 & Multi Bri 4 use Max Backlight Gamma Table
            else if((g_ucColorBacklightFlag == _MULTI_BACKLIGHT_3_CAL) || (g_ucColorBacklightFlag == _MULTI_BACKLIGHT_4_CAL))
            {
                ucColorGammaBankNum = UserCommonColorGetOGCBank(ucGammaIndex, _OGC_MAX_BACKLIGHT_TYPE);
                pucColorGammaBankAddr = UserCommonColorGetOGCAddr(ucGammaIndex, _OGC_MAX_BACKLIGHT_TYPE);
            }
#endif
            else
#endif
            {
                ucColorGammaBankNum = UserCommonColorGetOGCBank(ucGammaIndex, _OGC_NORMAL_TYPE);
                pucColorGammaBankAddr = UserCommonColorGetOGCAddr(ucGammaIndex, _OGC_NORMAL_TYPE);
            }
            // Set Output Gamma
            UserCommonColorCalibrationSetGammaTable(ucColorGammaBankNum, pucColorGammaBankAddr, _DB_APPLY_NO_POLLING);

            ScalerColorBrightnessContrastHLWRegionEnable(_1P_NORMAL_REGION, _DB_APPLY_POLLING, _ON);
#if(_COLOR_IP_BRIGHTNESS == _ON)
            ScalerColorBrightnessAdjust(_1P_NORMAL_REGION, pusBriTemp);
#endif
            if(ucColorTempIndex != 0x0F)
            {
#if(_TWO_BRI_CALIBRATION_TYPE >= _TWO_BRI_CALIBRATION_OGC_OCC_DICOM_HDR)
                if(g_ucColorBacklightFlag == _MAX_BACKLIGHT_CAL)
                {
                    UserCommonFlashRead(_OGC_FLASH_BANK, ((WORD)_OGC_FLASH_PAGE << 12) | (ucColorTempIndex * _OGC_TOTAL_GAMMA * 6 + ucGammaIndex * 6 + _OGC_RGB_GAIN_MAX_BRI_ADDRESS), 6, pData);
                }
#if(_TWO_BRI_CALIBRATION_TYPE >= _MULTI_BRI_CALIBRATION_OGC_OCC)
                else if(g_ucColorBacklightFlag == _MULTI_BACKLIGHT_3_CAL)
                {
                    UserCommonFlashRead(_OGC_FLASH_BANK, ((WORD)_OGC_FLASH_PAGE << 12) | (ucColorTempIndex * _OGC_TOTAL_GAMMA * 6 + ucGammaIndex * 6 + _OGC_RGB_GAIN_MULTI_BRI_3_CAL_ADDRESS), 6, pData);
                }
#if(_MULTI_BRI_CALIBRATION_TYPE >= _MULTI_BRI_FOUR_CALIBRATION)
                else if(g_ucColorBacklightFlag == _MULTI_BACKLIGHT_4_CAL)
                {
                    UserCommonFlashRead(_OGC_FLASH_BANK, ((WORD)_OGC_FLASH_PAGE << 12) | (ucColorTempIndex * _OGC_TOTAL_GAMMA * 6 + ucGammaIndex * 6 + _OGC_RGB_GAIN_MULTI_BRI_4_CAL_ADDRESS), 6, pData);
                }
#endif
#endif
                else
#endif
                {
                    UserCommonFlashRead(_OGC_FLASH_BANK, ((WORD)_OGC_FLASH_PAGE << 12) | (ucColorTempIndex * _OGC_TOTAL_GAMMA * 6 + ucGammaIndex * 6 + _OGC_RGB_GAIN_ADDRESS), 6, pData);
                }
            }
            else // Native
            {
                pData[0] = 0x08;
                pData[1] = 0x00;
                pData[2] = 0x08;
                pData[3] = 0x00;
                pData[4] = 0x08;
                pData[5] = 0x00;
            }

            // Construct contrast data format
            pusContrastData[0] = TO_WORD(pData[0], pData[1]);
            pusContrastData[1] = TO_WORD(pData[2], pData[3]);
            pusContrastData[2] = TO_WORD(pData[4], pData[5]);

#if(_COLOR_IP_CONTRAST == _ON)
            ScalerColorContrastAdjust(_1P_NORMAL_REGION, pusContrastData);
            ScalerColorContrastEnable(_FUNCTION_ON);
#endif
        }
#endif  // End of #if(_OGC_SUPPORT == _ON)

        /////////////////////////////////////////////////////////////////
        ////////////////////////SET PCM PROCESS//////////////////////////
        /////////////////////////////////////////////////////////////////
#if(_OCC_FUNCTION == _ON)
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_SET_PCM)
        {
            UserCommonColorCalibrationIPBypass();

            // Set PCM Input Gamma
            ScalerColorPCMInputGammaLoadTable(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN]);

            // Set PCM Color Matrix
            ScalerColorPCMSetPCMMode(_1P_NORMAL_REGION, _PCM_MODE);

#if(_TWO_BRI_CALIBRATION_TYPE < _TWO_BRI_CALIBRATION_OGC_OCC_DICOM_HDR)
            ScalerColorPCMOutputGammaAdjust(_1P_NORMAL_REGION, g_pucColorDISP_CALIBRATION_FLASH + _OCC_GAMMA10_ADDRESS, _OCC_GAMMA_FLASH_BANK);

            // Set PCM Color Matrix

            if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_SRGB)
            {
                ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _SRGB_0_BIT_SHIFT_LEFT, g_pucColorDISP_CALIBRATION_FLASH + _OCC_SRGBMATRIX_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_ADOBE_RGB)
            {
                ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _ADOBE_SRGB_PRECISION, g_pucColorDISP_CALIBRATION_FLASH + _OCC_ADOBEMATRIX_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_USER_DEFINE)
            {
                ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _USER_DEFINE_PRECISION, g_pucColorDISP_CALIBRATION_FLASH + _OCC_USERDEFINE_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_EBU_MODE)
            {
                ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _SRGB_0_BIT_SHIFT_LEFT, g_pucColorDISP_CALIBRATION_FLASH + _OCC_EBU_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_SOFT_PROFT)
            {
                ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _SRGB_0_BIT_SHIFT_LEFT, g_pucColorDISP_CALIBRATION_FLASH + _OCC_SOFTPROOF_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_REC_709)
            {
                ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _SRGB_0_BIT_SHIFT_LEFT, g_pucColorDISP_CALIBRATION_FLASH + _OCC_REC709_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_DCI_P3)
            {
                ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _DCIP3_SRGB_PRECISION, g_pucColorDISP_CALIBRATION_FLASH + _OCC_DCIP3_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_SMPTE_C)
            {
                ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _SRGB_0_BIT_SHIFT_LEFT, g_pucColorDISP_CALIBRATION_FLASH + _OCC_SMPTEC_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_USER_DEFINE_2)
            {
                ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _USER_DEFINE_PRECISION, g_pucColorDISP_CALIBRATION_FLASH + _OCC_USERDEFINE2_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_USER_DEFINE_3)
            {
                ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _USER_DEFINE_PRECISION, g_pucColorDISP_CALIBRATION_FLASH + _OCC_USERDEFINE3_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_USER_DEFINE_4)
            {
                ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _USER_DEFINE_PRECISION, g_pucColorDISP_CALIBRATION_FLASH + _OCC_USERDEFINE4_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_USER_DEFINE_5)
            {
                ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _USER_DEFINE_PRECISION, g_pucColorDISP_CALIBRATION_FLASH + _OCC_USERDEFINE5_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_USER_DEFINE_6)
            {
                ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _USER_DEFINE_PRECISION, g_pucColorDISP_CALIBRATION_FLASH + _OCC_USERDEFINE6_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_DISPLAY_P3)
            {
                ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _DCIP3_SRGB_PRECISION, g_pucColorDISP_CALIBRATION_FLASH + _OCC_DISPLAYP3_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else
            {
                ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _SRGB_0_BIT_SHIFT_LEFT, g_pucColorDISP_CALIBRATION_FLASH + _OCC_SRGBMATRIX_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
#else

            ScalerColorPCMOutputGammaAdjust(_1P_NORMAL_REGION, g_pucColorDISP_CALIBRATION_FLASH + _OCC_GAMMA10_ADDRESS + (g_ucColorBacklightFlag * _OCC_GAMMA_TABLE_SIZE), _OCC_GAMMA_FLASH_BANK);

            // Set PCM Color Matrix

            if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_SRGB)
            {
                ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _SRGB_0_BIT_SHIFT_LEFT, g_pucColorDISP_CALIBRATION_FLASH + _OCC_SRGBMATRIX_ADDRESS + (g_ucColorBacklightFlag * _OCC_COLOR_MATRIX_TOTAL_SPACE), _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_ADOBE_RGB)
            {
                ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _ADOBE_SRGB_PRECISION, g_pucColorDISP_CALIBRATION_FLASH + _OCC_ADOBEMATRIX_ADDRESS + (g_ucColorBacklightFlag * _OCC_COLOR_MATRIX_TOTAL_SPACE), _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_USER_DEFINE)
            {
                ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _USER_DEFINE_PRECISION, g_pucColorDISP_CALIBRATION_FLASH + _OCC_USERDEFINE_ADDRESS + (g_ucColorBacklightFlag * _OCC_COLOR_MATRIX_TOTAL_SPACE), _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_EBU_MODE)
            {
                ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _SRGB_0_BIT_SHIFT_LEFT, g_pucColorDISP_CALIBRATION_FLASH + _OCC_EBU_ADDRESS + (g_ucColorBacklightFlag * _OCC_COLOR_MATRIX_TOTAL_SPACE), _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_SOFT_PROFT)
            {
                ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _SRGB_0_BIT_SHIFT_LEFT, g_pucColorDISP_CALIBRATION_FLASH + _OCC_SOFTPROOF_ADDRESS + (g_ucColorBacklightFlag * _OCC_COLOR_MATRIX_TOTAL_SPACE), _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_REC_709)
            {
                ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _SRGB_0_BIT_SHIFT_LEFT, g_pucColorDISP_CALIBRATION_FLASH + _OCC_REC709_ADDRESS + (g_ucColorBacklightFlag * _OCC_COLOR_MATRIX_TOTAL_SPACE), _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_DCI_P3)
            {
                ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _DCIP3_SRGB_PRECISION, g_pucColorDISP_CALIBRATION_FLASH + _OCC_DCIP3_ADDRESS + (g_ucColorBacklightFlag * _OCC_COLOR_MATRIX_TOTAL_SPACE), _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_SMPTE_C)
            {
                ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _SRGB_0_BIT_SHIFT_LEFT, g_pucColorDISP_CALIBRATION_FLASH + _OCC_SMPTEC_ADDRESS + (g_ucColorBacklightFlag * _OCC_COLOR_MATRIX_TOTAL_SPACE), _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_USER_DEFINE_2)
            {
                ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _USER_DEFINE_PRECISION, g_pucColorDISP_CALIBRATION_FLASH + _OCC_USERDEFINE2_ADDRESS + (g_ucColorBacklightFlag * _OCC_COLOR_MATRIX_TOTAL_SPACE), _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_USER_DEFINE_3)
            {
                ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _USER_DEFINE_PRECISION, g_pucColorDISP_CALIBRATION_FLASH + _OCC_USERDEFINE3_ADDRESS + (g_ucColorBacklightFlag * _OCC_COLOR_MATRIX_TOTAL_SPACE), _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_USER_DEFINE_4)
            {
                ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _USER_DEFINE_PRECISION, g_pucColorDISP_CALIBRATION_FLASH + _OCC_USERDEFINE4_ADDRESS + (g_ucColorBacklightFlag * _OCC_COLOR_MATRIX_TOTAL_SPACE), _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_USER_DEFINE_5)
            {
                ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _USER_DEFINE_PRECISION, g_pucColorDISP_CALIBRATION_FLASH + _OCC_USERDEFINE5_ADDRESS + (g_ucColorBacklightFlag * _OCC_COLOR_MATRIX_TOTAL_SPACE), _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_USER_DEFINE_6)
            {
                ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _USER_DEFINE_PRECISION, g_pucColorDISP_CALIBRATION_FLASH + _OCC_USERDEFINE6_ADDRESS + (g_ucColorBacklightFlag * _OCC_COLOR_MATRIX_TOTAL_SPACE), _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_DISPLAY_P3)
            {
                ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _DCIP3_SRGB_PRECISION, g_pucColorDISP_CALIBRATION_FLASH + _OCC_DISPLAYP3_ADDRESS + (g_ucColorBacklightFlag * _OCC_COLOR_MATRIX_TOTAL_SPACE), _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else
            {
                ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _SRGB_0_BIT_SHIFT_LEFT, g_pucColorDISP_CALIBRATION_FLASH + _OCC_SRGBMATRIX_ADDRESS + (g_ucColorBacklightFlag * _OCC_COLOR_MATRIX_TOTAL_SPACE), _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
#endif

            ScalerColorOutputGammaEnable(_FUNCTION_ON);
#if(_COLOR_IP_SRGB == _ON)
            ScalerColorSRGBEnable(_FUNCTION_ON);
#endif
            ScalerColorPCMInputGammaEnable(_FUNCTION_ON);
#if(_HW_D_DOMAIN_RGN_COUNT_MAX > 1)
            ScalerColorPCMSetEffectiveRegion(_HLW_INSIDEB_OUTSIDEA, _DB_APPLY_NO_POLLING);
#endif
#if(_COLOR_IP_I_GAMMA == _ON)
            ScalerColorPCMRegionEnable(_1P_NORMAL_REGION, _DB_APPLY_POLLING, _ON);
#endif
        }
#endif  // End of #if(_OCC_SUPPORT == _ON)

        /////////////////////////////////////////////////////////////////
        ///////////////////////SET DICOM PROCESS/////////////////////////
        /////////////////////////////////////////////////////////////////
#if(_OGC_DICOM_FUNCTION == _ON)
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_SET_DICOM)
        {
#if(_OGC_TOTAL_DICOM > 1)
            ucDICOMIndex = g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_INDEX];
#else
            ucDICOMIndex = _DICOM1_TYPE;
#endif
            UserCommonColorCalibrationIPBypass();

#if(_HW_D_DOMAIN_RGN_COUNT_MAX > 1)
            ScalerColorGammaSetEffectiveRegion(_HLW_INSIDEB_OUTSIDEA, _DB_APPLY_NO_POLLING);
#endif

            ucColorGammaBankNum = UserCommonColorGetDICOMBank(ucDICOMIndex);
            pucColorGammaBankAddr = UserCommonColorGetDICOMAddr(ucDICOMIndex);
            // Set Output Gamma
            UserCommonColorCalibrationSetGammaTable(ucColorGammaBankNum, pucColorGammaBankAddr, _DB_APPLY_POLLING);
        }
#endif  // End of #if(_OGC_DICOM_SUPPORT == _ON)

        /////////////////////////////////////////////////////////////////
        ///////////////////////SET FREESYNC II PROCESS///////////////////
        /////////////////////////////////////////////////////////////////
#if(_FREESYNC_II_SUPPORT == _ON)
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_SET_FREESYNC_II)
        {
            ucGammaIndex = g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_INDEX] & 0x0F;

            UserCommonColorCalibrationIPBypass();

            // Set Freesync II Input Gamma
            ScalerColorPCMSetPCMMode(_1P_NORMAL_REGION, _PCM_MODE);
            ScalerColorPCMInputGammaAdjust(_1P_NORMAL_REGION, g_pucColorDISP_FREESYNC_II_CALIBRATION_FLASH + tFREESYNC2IGAMMA_INDEX[ucGammaIndex], _FREESYNC_II_FLASH_BANK, _IG_DB_DISABLE);

            ScalerColorPCMOutputGammaAdjust(_1P_NORMAL_REGION, g_pucColorDISP_FREESYNC_II_CALIBRATION_FLASH + _FREESYNC_II_OCC_GAMMA10_ADDRESS, _FREESYNC_II_FLASH_BANK);

            // Set Color Matrix
            ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _SRGB_1_BIT_SHIFT_LEFT, g_pucColorDISP_FREESYNC_II_CALIBRATION_FLASH + _FREESYNC_II_PANEL_NATIVE_MATRIX_ADDRESS, _FREESYNC_II_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);

            ScalerColorOutputGammaEnable(_FUNCTION_ON);
#if(_COLOR_IP_SRGB == _ON)
            ScalerColorSRGBEnable(_FUNCTION_ON);
#endif
            ScalerColorPCMInputGammaEnable(_FUNCTION_ON);
#if(_HW_D_DOMAIN_RGN_COUNT_MAX > 1)
            ScalerColorPCMSetEffectiveRegion(_HLW_INSIDEB_OUTSIDEA, _DB_APPLY_NO_POLLING);
#endif
#if(_COLOR_IP_I_GAMMA == _ON)
            ScalerColorPCMRegionEnable(_1P_NORMAL_REGION, _DB_APPLY_POLLING, _ON);
#endif
        }
#endif  // End of #if(_OGC_SUPPORT == _ON)

/////////////////////////////////////////////////////////////////
        ///////////////////////SET PCM GAMMA PROCESS/////////////////////
        /////////////////////////////////////////////////////////////////
#if(_OCC_PCM_GAMMA_SUPPORT == _ON)
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_SET_PCM_GAMMA)
        {
            UserCommonColorCalibrationIPBypass();

            // Set PCM Input Gamma
            UserCommonColorCalibrationSetOCCPCMGamma();
#if(_HW_D_DOMAIN_RGN_COUNT_MAX > 1)
            ScalerColorPCMSetEffectiveRegion(_HLW_INSIDEB_OUTSIDEA, _DB_APPLY_NO_POLLING);
#endif
#if(_COLOR_IP_I_GAMMA == _ON)
            ScalerColorPCMRegionEnable(_1P_NORMAL_REGION, _DB_APPLY_POLLING, _ON);
#endif
        }
#endif
#if(_OCC_RGB_3D_GAMMA_SUPPORT == _ON)
        else if (ucCalibrationStep == _DDCCI_DISP_CALIB_3DLUT_MEASURE_RED)
        {
            BYTE ucColor3DGammaBankNum = 0;
            BYTE uc3DLUTStartTypeIndex = 0;

            UserCommonColorCalibrationPatternEnable(_DISABLE);

            g_ucColorPatternType = g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_TYPE];
            uc3DLUTStartTypeIndex = g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_OCC_COLORSPACE];

            ucColor3DGammaBankNum = UserCommonColorGetOCC3DGammaTableBank(0);
            UserCommonFlashWrite(ucColor3DGammaBankNum, _RGB_3D_GAMMA_OCC_START_ADDRESS, 1, &uc3DLUTStartTypeIndex);

#if(_OCC_BOX_PATTERN_GENERATOR_SUPPORT == _ON)
            if(g_ucColorPatternType == _PG_PATTERN)
            {
                g_ucColorPatternType = _PG_BOX_PATTERN;
            }
#endif
            // Show Pattern
            UserCommonColorCalibrationPatternEnable(_ENABLE);
            UserCommonColorCalibrationShowPattern(_PATTERN_TOP, 0, 0);
        }
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_3DLUT_ERASE_FLASH)
        {
            BYTE ucMinPage = _PAGE0;
            uc3DLUTTypeIndex = g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_3DLUT_INDEX];
            uc3DLUTBankNum = UserCommonColorGetOCC3DGammaTableBank(uc3DLUTTypeIndex);
            puc3DLUTTableAddr = UserCommonColorGetOCC3DGammaTableAddress(uc3DLUTTypeIndex);
            ucMaxPage = (DWORD)(((DWORD)puc3DLUTTableAddr + _RGB_3D_GAMMA_1TABLE_SIZE + 1) / _FLASH_PAGE_SIZE); // ex: Total size = 29479bytes(29478 LUT + 1 checksum)
            ucMinPage = (uc3DLUTTypeIndex % 2 == 0) ? _PAGE0 : _PAGE8;
            for(ucCountPage = ucMinPage; ucCountPage <= ucMaxPage; ucCountPage++)
            {
                ucFlag &= UserCommonFlashErasePage(uc3DLUTBankNum, ucCountPage);
            }
        }
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_3DLUT_WRITE_START)
        {
            g_usColor3DLUTSavePos = 0;
            g_ucColor3DLUTStartPosIndex = g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_3DLUT_INDEX];
            g_ucColor3DLUTSaveBank = UserCommonColorGetOCC3DGammaTableBank(g_ucColor3DLUTStartPosIndex);
        }
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_3DLUT_WRITE)
        {
            puc3DLUTTableAddr = UserCommonColorGetOCC3DGammaTableAddress(g_ucColor3DLUTStartPosIndex);
            UserCommonFlashWrite(g_ucColor3DLUTSaveBank, (DWORD)puc3DLUTTableAddr + g_usColor3DLUTSavePos, (g_pucMcuDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 4, &g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_3DLUT_INDEX]);
            g_usColor3DLUTSavePos += (g_pucMcuDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 4;
        }
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_3DLUT_WRITE_END)
        {
            g_ucColor3DLUTChecksumType = g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_TYPE];
            g_ucColorCalibrationType = 0;
            g_ucColorCalibrationTypeII = 0;
            ucFlag = UserCommonColorCalibrationCheckSum();
            g_ucColor3DLUTChecksumType = 0;
        }
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_3DLUT_SET_MODE)
        {
            UserCommonColorCalibrationIPBypass();
            // Set Input Gamma
            ScalerColorPCMSetPCMMode(_1P_NORMAL_REGION, _PCM_MODE);
            ScalerColorPCMInputGammaAdjust(_1P_NORMAL_REGION, g_pucColorDISP_CALIBRATION_FLASH + _OGC_HDR10_IG_1200_NOR_ADDRESS + (g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_SET_HDR_IG_INDEX] * _OGC_HDR10_IG_TABLE_SIZE), _OGC_FLASH_BANK, _IG_DB_DISABLE);
            ScalerColorPCMOutputGammaAdjust(_1P_NORMAL_REGION, g_pucColorDISP_CALIBRATION_FLASH + _OCC_GAMMA10_ADDRESS, _OCC_GAMMA_FLASH_BANK);

            // Set Color Matrix
            ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _SRGB_1_BIT_SHIFT_LEFT, g_pucColorDISP_CALIBRATION_FLASH + _OCC_HDR10_SRGB_MATRIX_ADDRESS + (g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_SET_HDR_COLOR_MATRIX] * _OCC_COLORMATRIX_TABLE_SIZE), _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);

            // Set 3D Gamma
            ScalerColor3DGammaRegionEnable(_1P_NORMAL_REGION, _DB_APPLY_POLLING, _OFF);
            uc3DLUTTypeIndex = g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_SET_HDR_TABLE_INDEX];
            uc3DLUTBankNum = UserCommonColorGetOCC3DGammaTableBank(uc3DLUTTypeIndex);
            puc3DLUTTableAddr = UserCommonColorGetOCC3DGammaTableAddress(uc3DLUTTypeIndex);
            ScalerColorRGB3DGammaAdjust(puc3DLUTTableAddr, uc3DLUTBankNum);
            ScalerColorRGBGamma3DGammaSwapEnable(_FUNCTION_ON);
            ScalerColorRGB3DGammaEnable(_ENABLE);
            ScalerColor3DGammaRegionEnable(_1P_NORMAL_REGION, _DB_APPLY_POLLING, _ON);

            ScalerColorOutputGammaEnable(_FUNCTION_ON);
#if(_COLOR_IP_SRGB == _ON)
            ScalerColorSRGBEnable(_FUNCTION_ON);
#endif
            ScalerColorPCMInputGammaEnable(_FUNCTION_ON);
#if(_HW_D_DOMAIN_RGN_COUNT_MAX > 1)
            ScalerColorPCMSetEffectiveRegion(_HLW_INSIDEB_OUTSIDEA, _DB_APPLY_NO_POLLING);
#endif
#if(_COLOR_IP_I_GAMMA == _ON)
            ScalerColorPCMRegionEnable(_1P_NORMAL_REGION, _DB_APPLY_POLLING, _ON);
#endif
        }
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_3DLUT_SET_NORMAL_MODE)
        {
            BYTE ucShowMode = 0;
            ucShowMode = g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_TYPE];    // 1 : Show OG, 2 : Show 3D, 3 : Show OG+3D

#if(_HW_D_DOMAIN_RGN_COUNT_MAX > 1)
            ScalerColorGammaSetEffectiveRegion(_HLW_INSIDEB_OUTSIDEA, _DB_APPLY_NO_POLLING);
#endif
            UserCommonColorCalibrationIPBypass();
            if(ucShowMode & 0x01)           // Set OG
            {
                ucGammaIndex = (g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_OCC_COLORSPACE] >> 4) & 0x0F;
                uc3DLUTBankNum = UserCommonColorGet3DGammaOGCTableBank();
                puc3DLUTTableAddr = UserCommonColorGet3DGammaOGCTableAddress(ucGammaIndex);

                ScalerColorOutputGammaEnable(_FUNCTION_OFF);
#if(_PCM_FULL_TIME_FUNCTION == _ON)
                ScalerColorPCMInputGammaEnable(_FUNCTION_ON);
                ScalerColorPCMSetPCMMode(_1P_NORMAL_REGION, _PCM_MODE);
                ScalerColorPCMOutputGammaAdjust(_1P_NORMAL_REGION, puc3DLUTTableAddr, uc3DLUTBankNum);
                ScalerColorPCMInputGammaRegionEnable(_1P_NORMAL_REGION, _DB_APPLY_NONE, _OFF, _PCM_HLW_DB_A_OR_B);
                ScalerColorPCMOutputGammaRegionEnable(_1P_NORMAL_REGION, _DB_APPLY_NO_POLLING, _ON);
#else
#if(_PCM_FUNCTION == _ON)
                ScalerColorPCMSetPCMMode(_1P_NORMAL_REGION, _OGC_MODE);
#endif
                ScalerColorOutputGammaAdjust(_1P_NORMAL_REGION, puc3DLUTTableAddr, uc3DLUTBankNum);
                ScalerColorGammaRegionEnable(_1P_NORMAL_REGION, _DB_APPLY_NO_POLLING, _ON);
#endif
                ScalerColorOutputGammaEnable(_FUNCTION_ON);
            }
            if((ucShowMode >> 1) & 0x01)    // Set 3D Gamma
            {
                uc3DLUTTypeIndex = g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_OCC_COLORSPACE] & 0x0F;
                uc3DLUTBankNum = UserCommonColorGetOCC3DGammaTableBank(uc3DLUTTypeIndex);
                puc3DLUTTableAddr = UserCommonColorGetOCC3DGammaTableAddress(uc3DLUTTypeIndex);

                ScalerColor3DGammaRegionEnable(_1P_NORMAL_REGION, _DB_APPLY_POLLING, _OFF);
                ScalerColorRGB3DGammaAdjust(puc3DLUTTableAddr, uc3DLUTBankNum);
                ScalerColorRGBGamma3DGammaSwapEnable(_FUNCTION_OFF);
                ScalerColorRGB3DGammaEnable(_FUNCTION_ON);
                ScalerColor3DGammaRegionEnable(_1P_NORMAL_REGION, _DB_APPLY_POLLING, _ON);
            }
        }
#endif
#if((_MULTI_BRI_CALIBRATION_TYPE != _MULTI_BRI_CALIBRATION_NONE) || (_OCC_RGB_3D_GAMMA_SUPPORT == _ON))
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_USER_SET_BACKLIGHT)
        {
            UserInterfaceColorCalibrationAdjustMultiBacklight(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_TYPE]);
        }
#endif

        /////////////////////////////////////////////////////////////////
        ///////////////////////VERIFICATION END//////////////////////////
        /////////////////////////////////////////////////////////////////
        else if((ucCalibrationStep == _DDCCI_DISP_CALIB_OGC_VERIFY_END) || (ucCalibrationStep == _DDCCI_DISP_CALIB_OCC_VERIFY_END))
        {
            ScalerDDomainPatternGenEnable(_DISABLE);
            UserCommonColorCalibrationShowDDomainPattern(0, 0, 0, g_ucColorPatternType);
        }
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_MEASURE_BG)
        {
            ScalerDDomainBackgroundEnable(_DDOMAIN_RGN_ALL, _ENABLE);

            usR = (g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_VERIFY_RED] << 8) | (g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_VERIFY_RED + 1]);
            usG = (g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_VERIFY_GREEN] << 8) | (g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_VERIFY_GREEN + 1]);
            usB = (g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_VERIFY_BLUE] << 8) | (g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_VERIFY_BLUE + 1]);

            ScalerDDomainBackgroundSetColor10bit(usR, usG, usB, _DB_APPLY_POLLING);
        }
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_BG_OFF)
        {
            ScalerDDomainBackgroundEnable(_DDOMAIN_RGN_ALL, _DISABLE);
        }
#if(_UNIFORMITY_FUNCTION == _ON)
        /////////////////////////////////////////////////////////////////
        ///////////////////////SET UNIFORMITY LUT////////////////////////
        /////////////////////////////////////////////////////////////////
        if(ucCalibrationStep == _DDCCI_DISP_CALIB_UNIFORMITY_GET_OGC_HEADER)
        {
            UserCommonColorCalibrationReplyOGCHeader();
            // ScalerMcuDdcciReleaseScl();
            ScalerMcuDdcciReleaseScl();

            return;
        }
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_UNIFORMITY_GET_LVRATIO)
        {
            UserCommonColorCalibReplyOGCOCCLvRatio();
            ScalerMcuDdcciReleaseScl();

            return;
        }
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_UNIFORMITY_GET_NEWLVRATIO)
        {
            UserCommonColorCalibReplyOGCNEWLvRatio();
            ScalerMcuDdcciReleaseScl();

            return;
        }
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_UNIFORMITY_ERASE_FLASH)
        {
            ucUniformityTypeIndex = (g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_UNIFORMITY_INDEX] & 0x0F);
            ucGainTableBank = UserCommonColorGetPanelUniformityGainBank(ucUniformityTypeIndex);
            usGainTableAddr = UserCommonColorGetPanelUniformityGainAddr(ucUniformityTypeIndex);
            for(ucCountBank = _UNIFORMITY_FLASH_BANK0; ucCountBank <= ucGainTableBank; ucCountBank++)
            {
                if(ucCountBank < ucGainTableBank)
                {
                    ucMaxPage = 15;
                }
                else
                {
                    if(_PANEL_UNIFORMITY_1LEVEL_SIZE * UserCommonColorGetUniformityType(ucUniformityTypeIndex) > 65536)
                    {
                        ucMaxPage = 15;
                        for(ucCountPage = 0; ucCountPage <= ucMaxPage; ucCountPage++)
                        {
                            ucFlag &= UserCommonFlashErasePage(ucCountBank, ucCountPage);
                        }

                        ucMaxPage = (DWORD)((_PANEL_UNIFORMITY_1LEVEL_SIZE * UserCommonColorGetUniformityType(ucUniformityTypeIndex) - 65536) / _FLASH_PAGE_SIZE);
                        ucCountBank++;
                    }
                    else
                    {
                        ucMaxPage = (DWORD)((usGainTableAddr + _PANEL_UNIFORMITY_1LEVEL_SIZE * UserCommonColorGetUniformityType(ucUniformityTypeIndex)) / _FLASH_PAGE_SIZE); // ex: Total size = 4096bytes(4095 LUT + 1 checksum), only need Page0
                    }
                }

                for(ucCountPage = 0; ucCountPage <= ucMaxPage; ucCountPage++)
                {
                    ucFlag &= UserCommonFlashErasePage(ucCountBank, ucCountPage);
                }
            }
#if(_UNIFORMITY_LEVEL0_SUPPORT == _ON)
            ucOffsetTableBank = UserCommonColorGetPanelUniformityOffsetBank(ucUniformityTypeIndex);
            usOffsetTableAddr = UserCommonColorGetPanelUniformityOffsetAddr(ucUniformityTypeIndex);
            ucOffsetTableStartBank = UserCommonColorGetPanelUniformityOffsetBank(0);
            for(ucCountBank = ucOffsetTableStartBank; ucCountBank <= ucOffsetTableBank; ucCountBank++)
            {
                if(ucCountBank < ucOffsetTableBank)
                {
                    ucMaxPage = 15;
                }
                else
                {
                    ucMaxPage = (DWORD)((usOffsetTableAddr + _PANEL_UNIFORMITY_OFFSET_LUT_SIZE + _PANEL_UNIFORMITY_DECAY_LUT_SIZE) / _FLASH_PAGE_SIZE); // ex: Total size = 4096bytes(4095 LUT + 1 checksum), only need Page0
                }

                for(ucCountPage = 0; ucCountPage <= ucMaxPage; ucCountPage++)
                {
                    ucFlag &= UserCommonFlashErasePage(ucCountBank, ucCountPage);
                }
            }
#endif
        }
#if(_UNIFORMITY_PLUS_FUNCTION == _ON)
#if(_OGC_FUNCTION == _ON)
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_UNIFORMITY_SET_POST_GAMMA)
        {
            ucGammaIndex = (g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_INDEX] >> 4) & 0x0F;
            ucColorTempIndex = g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_INDEX] & 0x0F;

            UserCommonColorCalibrationIPBypass();

#if(_HW_D_DOMAIN_RGN_COUNT_MAX > 1)
            ScalerColorGammaSetEffectiveRegion(_HLW_INSIDEB_OUTSIDEA, _DB_APPLY_NO_POLLING);
#endif

#if(_TWO_BRI_CALIBRATION_TYPE >= _TWO_BRI_CALIBRATION_OGC_OCC_DICOM_HDR)
            if(g_ucColorBacklightFlag == _MAX_BACKLIGHT_CAL)
            {
                ucColorGammaBankNum = UserCommonColorGetOGCBank(ucGammaIndex, _OGC_MAX_BACKLIGHT_TYPE);
                pucColorGammaBankAddr = UserCommonColorGetOGCAddr(ucGammaIndex, _OGC_MAX_BACKLIGHT_TYPE);
            }
#if(_TWO_BRI_CALIBRATION_TYPE >= _MULTI_BRI_CALIBRATION_OGC_OCC)
            // Multi Bri 3 & Multi Bri 4 use Max Backlight Gamma Table
            else if((g_ucColorBacklightFlag == _MULTI_BACKLIGHT_3_CAL) || (g_ucColorBacklightFlag == _MULTI_BACKLIGHT_4_CAL))
            {
                ucColorGammaBankNum = UserCommonColorGetOGCBank(ucGammaIndex, _OGC_MAX_BACKLIGHT_TYPE);
                pucColorGammaBankAddr = UserCommonColorGetOGCAddr(ucGammaIndex, _OGC_MAX_BACKLIGHT_TYPE);
            }
#endif
            else
#endif
            {
                ucColorGammaBankNum = UserCommonColorGetOGCBank(ucGammaIndex, _OGC_NORMAL_TYPE);
                pucColorGammaBankAddr = UserCommonColorGetOGCAddr(ucGammaIndex, _OGC_NORMAL_TYPE);
            }
            // Set Post Gamma
            UserCommonColorCalibrationSetPostGammaTable(ucColorGammaBankNum, pucColorGammaBankAddr, _DB_APPLY_NO_POLLING);
#if((_COLOR_IP_CONTRAST == _ON) || (_COLOR_IP_BRIGHTNESS == _ON))
            ScalerColorBrightnessContrastHLWRegionEnable(_1P_NORMAL_REGION, _DB_APPLY_POLLING, _ON);
#endif
#if(_COLOR_IP_BRIGHTNESS == _ON)
            ScalerColorBrightnessAdjust(_1P_NORMAL_REGION, pusBriTemp);
#endif
            if(ucColorTempIndex != 0x0F)
            {
#if(_TWO_BRI_CALIBRATION_TYPE >= _TWO_BRI_CALIBRATION_OGC_OCC_DICOM_HDR)
                if(g_ucColorBacklightFlag == _MAX_BACKLIGHT_CAL)
                {
                    UserCommonFlashRead(_OGC_FLASH_BANK, ((WORD)_OGC_FLASH_PAGE << 12) | (ucColorTempIndex * _OGC_TOTAL_GAMMA * 6 + ucGammaIndex * 6 + _OGC_RGB_GAIN_MAX_BRI_ADDRESS), 6, pData);
                }
#if(_TWO_BRI_CALIBRATION_TYPE >= _MULTI_BRI_CALIBRATION_OGC_OCC)
                else if(g_ucColorBacklightFlag == _MULTI_BACKLIGHT_3_CAL)
                {
                    UserCommonFlashRead(_OGC_FLASH_BANK, ((WORD)_OGC_FLASH_PAGE << 12) | (ucColorTempIndex * _OGC_TOTAL_GAMMA * 6 + ucGammaIndex * 6 + _OGC_RGB_GAIN_MULTI_BRI_3_CAL_ADDRESS), 6, pData);
                }
#if(_MULTI_BRI_CALIBRATION_TYPE >= _MULTI_BRI_FOUR_CALIBRATION)
                else if(g_ucColorBacklightFlag == _MULTI_BACKLIGHT_4_CAL)
                {
                    UserCommonFlashRead(_OGC_FLASH_BANK, ((WORD)_OGC_FLASH_PAGE << 12) | (ucColorTempIndex * _OGC_TOTAL_GAMMA * 6 + ucGammaIndex * 6 + _OGC_RGB_GAIN_MULTI_BRI_4_CAL_ADDRESS), 6, pData);
                }
#endif
#endif
                else
#endif
                {
                    UserCommonFlashRead(_OGC_FLASH_BANK, ((WORD)_OGC_FLASH_PAGE << 12) | (ucColorTempIndex * _OGC_TOTAL_GAMMA * 6 + ucGammaIndex * 6 + _OGC_RGB_GAIN_ADDRESS), 6, pData);
                }
            }
            else // Native
            {
                pData[0] = 0x08;
                pData[1] = 0x00;
                pData[2] = 0x08;
                pData[3] = 0x00;
                pData[4] = 0x08;
                pData[5] = 0x00;
            }

            // Construct contrast data format
            pusContrastData[0] = TO_WORD(pData[0], pData[1]);
            pusContrastData[1] = TO_WORD(pData[2], pData[3]);
            pusContrastData[2] = TO_WORD(pData[4], pData[5]);

#if(_COLOR_IP_CONTRAST == _ON)
            ScalerColorContrastAdjust(_1P_NORMAL_REGION, pusContrastData);
            ScalerColorContrastEnable(_FUNCTION_ON);
#endif
        }
#endif
#endif
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_UNIFORMITY_GET_PCM_MATRIX)
        {
            switch((g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_UNIFORMITY_INDEX] & 0x07) | ((g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_UNIFORMITY_INDEX] & 0xE0) >> 2))
            {
                case 0:

                    UserCommonColorCalibrationReplyOCCMatrix(_PCM_SRGB);

                    break;

                case 1:

                    UserCommonColorCalibrationReplyOCCMatrix(_PCM_ADOBE_RGB);

                    break;

                case 2:

                    UserCommonColorCalibrationReplyOCCMatrix(_PCM_DCI_P3);

                    break;

                case 3:

                    UserCommonColorCalibrationReplyOCCMatrix(_PCM_USER_DEFINE);

                    break;

                case 4:

                    UserCommonColorCalibrationReplyOCCMatrix(_PCM_USER_DEFINE_2);

                    break;

                case 5:

                    UserCommonColorCalibrationReplyOCCMatrix(_PCM_DISPLAY_P3);

                    break;

                case 6:

                    UserCommonColorCalibrationReplyOCCMatrix(_PCM_REC_709);

                    break;

                case 7:

                    UserCommonColorCalibrationReplyOCCMatrix(_PCM_SMPTE_C);

                    break;

                case 8:

                    UserCommonColorCalibrationReplyOCCMatrix(_PCM_EBU_MODE);

                    break;

                case 9:

                    UserCommonColorCalibrationReplyOCCMatrix(_PCM_USER_DEFINE_3);

                    break;

                case 10:

                    UserCommonColorCalibrationReplyOCCMatrix(_PCM_USER_DEFINE_4);

                    break;

                case 11:

                    UserCommonColorCalibrationReplyOCCMatrix(_PCM_USER_DEFINE_5);

                    break;

                case 12:

                    UserCommonColorCalibrationReplyOCCMatrix(_PCM_USER_DEFINE_6);

                    break;

                default:
                    break;
            }
            ScalerMcuDdcciReleaseScl();

            return;
        }
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_UNIFORMITY_WRITE_START)
        {
            g_usColorUniformityLUTSavePos = 0;
            g_ucColorUniformityLUTStartPosIndex = g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_UNIFORMITY_INDEX] & 0x0F;
            g_ucColorUniformityLUTSaveBank = UserCommonColorGetPanelUniformityGainBank(g_ucColorUniformityLUTStartPosIndex);
        }
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_UNIFORMITY_WRITE)
        {
            usGainTableAddr = UserCommonColorGetPanelUniformityGainAddr(g_ucColorUniformityLUTStartPosIndex);
            DWORD  ulTableAddrEnd = usGainTableAddr + g_usColorUniformityLUTSavePos + (g_pucMcuDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 4;

            if(ulTableAddrEnd > 65536)
            {
                UserCommonFlashWrite(g_ucColorUniformityLUTSaveBank, usGainTableAddr + g_usColorUniformityLUTSavePos, 65536 - (usGainTableAddr + g_usColorUniformityLUTSavePos), &g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_UNIFORMITY_INDEX]);
                g_ucColorUniformityLUTSaveBank = g_ucColorUniformityLUTSaveBank + 1;
                usGainTableAddr = 0;
                UserCommonFlashWrite(g_ucColorUniformityLUTSaveBank, usGainTableAddr, ulTableAddrEnd - 65536, &g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_UNIFORMITY_INDEX + (65536 - (usGainTableAddr + g_usColorUniformityLUTSavePos))]);
                g_usColorUniformityLUTSavePos = ulTableAddrEnd - 65536;
            }
            else
            {
                UserCommonFlashWrite(g_ucColorUniformityLUTSaveBank, usGainTableAddr + g_usColorUniformityLUTSavePos, (g_pucMcuDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 4, &g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_UNIFORMITY_INDEX]);
                g_usColorUniformityLUTSavePos += (g_pucMcuDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 4;
            }
        }
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_UNIFORMITY_WRITE_END)
        {
            g_ucColorUniformityChecksumType = g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_TYPE];

            g_ucColorCalibrationType = 0;
            g_ucColorCalibrationTypeII = 0;
            ucFlag = UserCommonColorCalibrationCheckSum();
            g_usColorUniformityLUTSavePos = 0;// level0, CYShih
        }
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_UNIFORMITY_VERIFY_START)
        {
            if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_UNIFORMITY_INDEX] == _ON)
            {
                ScalerColorPanelUniformityRegionEnable(_1P_NORMAL_REGION, _DB_APPLY_POLLING, _OFF);
                ucUniformityTypeIndex = (g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_UNIFORMITY_INDEX + 1] & 0xF0) >> 4;
                ucUniformityModeIndex = g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_UNIFORMITY_INDEX + 1] & 0x0F;
                ucGainTableBank = UserCommonColorGetPanelUniformityGainBank(ucUniformityTypeIndex);
                usGainTableAddr = UserCommonColorGetPanelUniformityGainAddr(ucUniformityTypeIndex);

#if(_UNIFORMITY_LEVEL0_SUPPORT == _ON)
                ucUniformityLevel0Enable = g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_UNIFORMITY_INDEX + 2] & _BIT0;
                ucOffsetTableBank = UserCommonColorGetPanelUniformityOffsetBank(ucUniformityTypeIndex);
                usOffsetTableAddr = UserCommonColorGetPanelUniformityOffsetAddr(ucUniformityTypeIndex);
                usDecayTableAddr = UserCommonColorGetPanelUniformityDecayAddr(ucUniformityTypeIndex);
                if(ucUniformityLevel0Enable == _ON)
                {
                    ScalerColorPanelUniformityOffsetAdjust(g_pucColorDISP_CALIBRATION_FLASH + usOffsetTableAddr, _PANEL_UNIFORMITY_OFFSET_LUT_SIZE, ucOffsetTableBank);
                    ScalerColorPanelUniformityDecayAdjust(g_pucColorDISP_CALIBRATION_FLASH + usDecayTableAddr, _PANEL_UNIFORMITY_DECAY_LUT_SIZE, ucOffsetTableBank, ucUniformityModeIndex, UserCommonColorGetUniformityType(ucUniformityTypeIndex));
                }
                ScalerColorPanelUniformityOffsetEnable(ucUniformityLevel0Enable);
#endif
                ScalerColorPanelUniformityAdjust(g_pucColorDISP_CALIBRATION_FLASH + usGainTableAddr, _PANEL_UNIFORMITY_1LEVEL_SIZE * UserCommonColorGetUniformityType(ucUniformityTypeIndex), ucGainTableBank, ucUniformityModeIndex, UserCommonColorGetUniformityType(ucUniformityTypeIndex));
                ScalerColorPanelUniformityEnable(_ENABLE);
                ScalerColorPanelUniformityRegionEnable(_1P_NORMAL_REGION, _DB_APPLY_POLLING, _ON);
            }
            else
            {
                ScalerColorPanelUniformityRegionEnable(_1P_NORMAL_REGION, _DB_APPLY_POLLING, _OFF);
#if(_UNIFORMITY_LEVEL0_SUPPORT == _ON)
                ScalerColorPanelUniformityOffsetEnable(_FUNCTION_OFF);
#endif
            }
        }
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_UNIFORMITY_VERIFY_END)
        {
            UserCommonColorCalibrationIPBypass();
        }
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_UNIFORMITY_GET_DEFINE)
        {
            // UserCommonColorCalibrationReplyResult(_DISP_CALIB_UNIFORMITY);
            UserInterfaceColorCalibrationBeforeProc(_UNIFORMITY_CAL);
            UserCommonColorCalibrationReplyUniformityDefine();
            // ScalerMcuDdcciReleaseScl();
            ScalerColorPanelUniformityInitial();
#if(_TWO_BRI_CALIBRATION_TYPE >= _TWO_BRI_CALIBRATION_OGC_OCC_DICOM_HDR)
            g_ucColorBacklightFlag = _MAX_BACKLIGHT_CAL;
#endif
            ScalerMcuDdcciReleaseScl();
            return;
        }
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_UNIFORMITY_GET_CCT_GAIN)
        {
            UserCommonColorCalibrationReplyCCTGain();
            // ScalerMcuDdcciReleaseScl();
            ScalerMcuDdcciReleaseScl();
            return;
        }
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_UNIFORMITY_GET_FM_DATA)
        {
            UserCommonColorCalibrationReplyFastModeData();
            ScalerMcuDdcciReleaseScl();

            return;
        }
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_UNIFORMITY_GET_LEVEL_MODE)
        {
            UserCommonColorCalibrationReplyUniformityLevelMode();
            ScalerMcuDdcciReleaseScl();
            return;
        }
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_UNIFORMITY_GET_NEW_LEVEL)
        {
            UserCommonColorCalibrationReplyUniformityNewLevelMode();
            ScalerMcuDdcciReleaseScl();
            return;
        }
#if(_UNIFORMITY_PLUS_FUNCTION == _ON)
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_UNIFORMITY_SET_PLUS_MODE)
        {
            UserCommonColorCalibrationIPBypass();
#if(_PCM_FUNCTION == _ON)
            // Set PCM Input Gamma
            ScalerColorPCMInputGammaLoadTable(_PCM_HDR_2084);// IG bypass table
            ScalerColorPCMSetPCMMode(_1P_NORMAL_REGION, _PCM_MODE);
#if(_TWO_BRI_CALIBRATION_TYPE < _TWO_BRI_CALIBRATION_OGC_OCC_DICOM_HDR)
            ScalerColorPCMOutputGammaAdjust(_1P_NORMAL_REGION, g_pucColorDISP_CALIBRATION_FLASH + _OCC_GAMMA10_ADDRESS, _OCC_GAMMA_FLASH_BANK);
#else
            ScalerColorPCMOutputGammaAdjust(_1P_NORMAL_REGION, g_pucColorDISP_CALIBRATION_FLASH + _OCC_GAMMA10_MAX_BRI_ADDRESS, _OCC_GAMMA_FLASH_BANK);
#endif

            ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _SRGB_0_BIT_SHIFT_LEFT, ScalerColorsRGBBypassGetTableAddress(_SRGB_BYPASS), ScalerColorsRGBBypassGetTableBank(), _OCC_COLORMATRIX_TABLE_SIZE);
            ScalerColorOutputGammaEnable(_FUNCTION_ON);
            ScalerColorSRGBEnable(_FUNCTION_ON);
            ScalerColorPCMInputGammaEnable(_FUNCTION_ON);
#if(_HW_D_DOMAIN_RGN_COUNT_MAX > 1)
            ScalerColorPCMSetEffectiveRegion(_HLW_INSIDEB_OUTSIDEA, _DB_APPLY_NO_POLLING);
#endif
            ScalerColorPCMRegionEnable(_1P_NORMAL_REGION, _DB_APPLY_POLLING, _ON);
#endif
        }
#endif
#if(_OCC_FUNCTION == _ON)
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_UNIFORMITY_SET_PCM)
        {
            UserCommonColorCalibrationIPBypass();
            // Set PCM Input Gamma
            if ((g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_USER_DEFINE) || (g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_USER_DEFINE_2))
            {
                ScalerColorPCMInputGammaLoadTable(_PCM_ADOBE_RGB);
            }
            else
            {
                ScalerColorPCMInputGammaLoadTable(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN]);
            }
            // Set PCM Color Matrix
            ScalerColorPCMSetPCMMode(_1P_NORMAL_REGION, _PCM_MODE);

#if(_TWO_BRI_CALIBRATION_TYPE < _TWO_BRI_CALIBRATION_OGC_OCC_DICOM_HDR)
            ScalerColorPCMOutputGammaAdjust(_1P_NORMAL_REGION, g_pucColorDISP_CALIBRATION_FLASH + _OCC_GAMMA10_ADDRESS, _OCC_GAMMA_FLASH_BANK);
            // Set PCM Color Matrix

            if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_SRGB)
            {
                ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _SRGB_0_BIT_SHIFT_LEFT, g_pucColorDISP_CALIBRATION_FLASH + _OCC_SRGBMATRIX_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_ADOBE_RGB)
            {
                ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _ADOBE_SRGB_PRECISION, g_pucColorDISP_CALIBRATION_FLASH + _OCC_ADOBEMATRIX_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_USER_DEFINE)
            {
                ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _USER_DEFINE_PRECISION, g_pucColorDISP_CALIBRATION_FLASH + _OCC_USERDEFINE_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_EBU_MODE)
            {
                ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _SRGB_0_BIT_SHIFT_LEFT, g_pucColorDISP_CALIBRATION_FLASH + _OCC_EBU_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_REC_709)
            {
                ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _SRGB_0_BIT_SHIFT_LEFT, g_pucColorDISP_CALIBRATION_FLASH + _OCC_REC709_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_DCI_P3)
            {
                ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _DCIP3_SRGB_PRECISION, g_pucColorDISP_CALIBRATION_FLASH + _OCC_DCIP3_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_SMPTE_C)
            {
                ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _SRGB_0_BIT_SHIFT_LEFT, g_pucColorDISP_CALIBRATION_FLASH + _OCC_SMPTEC_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_USER_DEFINE_2)
            {
                ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _USER_DEFINE_PRECISION, g_pucColorDISP_CALIBRATION_FLASH + _OCC_USERDEFINE2_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_USER_DEFINE_3)
            {
                ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _USER_DEFINE_PRECISION, g_pucColorDISP_CALIBRATION_FLASH + _OCC_USERDEFINE3_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_USER_DEFINE_4)
            {
                ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _USER_DEFINE_PRECISION, g_pucColorDISP_CALIBRATION_FLASH + _OCC_USERDEFINE4_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_USER_DEFINE_5)
            {
                ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _USER_DEFINE_PRECISION, g_pucColorDISP_CALIBRATION_FLASH + _OCC_USERDEFINE5_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_USER_DEFINE_6)
            {
                ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _USER_DEFINE_PRECISION, g_pucColorDISP_CALIBRATION_FLASH + _OCC_USERDEFINE6_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else // if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_DISPLAY_P3)
            {
                ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _DCIP3_SRGB_PRECISION, g_pucColorDISP_CALIBRATION_FLASH + _OCC_DISPLAYP3_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
#else
            ScalerColorPCMOutputGammaAdjust(_1P_NORMAL_REGION, g_pucColorDISP_CALIBRATION_FLASH + _OCC_GAMMA10_MAX_BRI_ADDRESS, _OCC_GAMMA_FLASH_BANK);

            // Set PCM Color Matrix

            if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_SRGB)
            {
                ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _SRGB_0_BIT_SHIFT_LEFT, g_pucColorDISP_CALIBRATION_FLASH + _OCC_SRGBMATRIX_MAX_BRI_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_ADOBE_RGB)
            {
                ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _ADOBE_SRGB_PRECISION, g_pucColorDISP_CALIBRATION_FLASH + _OCC_ADOBEMATRIX_MAX_BRI_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_USER_DEFINE)
            {
                ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _USER_DEFINE_PRECISION, g_pucColorDISP_CALIBRATION_FLASH + _OCC_USERDEFINE_MAX_BRI_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_EBU_MODE)
            {
                ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _SRGB_0_BIT_SHIFT_LEFT, g_pucColorDISP_CALIBRATION_FLASH + _OCC_EBU_MAX_BRI_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_REC_709)
            {
                ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _SRGB_0_BIT_SHIFT_LEFT, g_pucColorDISP_CALIBRATION_FLASH + _OCC_REC709_MAX_BRI_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_DCI_P3)
            {
                ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _DCIP3_SRGB_PRECISION, g_pucColorDISP_CALIBRATION_FLASH + _OCC_DCIP3_MAX_BRI_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_SMPTE_C)
            {
                ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _SRGB_0_BIT_SHIFT_LEFT, g_pucColorDISP_CALIBRATION_FLASH + _OCC_SMPTEC_MAX_BRI_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_USER_DEFINE_2)
            {
                ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _USER_DEFINE_PRECISION, g_pucColorDISP_CALIBRATION_FLASH + _OCC_USERDEFINE2_MAX_BRI_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_USER_DEFINE_3)
            {
                ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _USER_DEFINE_PRECISION, g_pucColorDISP_CALIBRATION_FLASH + _OCC_USERDEFINE3_MAX_BRI_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_USER_DEFINE_4)
            {
                ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _USER_DEFINE_PRECISION, g_pucColorDISP_CALIBRATION_FLASH + _OCC_USERDEFINE4_MAX_BRI_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_USER_DEFINE_5)
            {
                ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _USER_DEFINE_PRECISION, g_pucColorDISP_CALIBRATION_FLASH + _OCC_USERDEFINE5_MAX_BRI_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_USER_DEFINE_6)
            {
                ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _USER_DEFINE_PRECISION, g_pucColorDISP_CALIBRATION_FLASH + _OCC_USERDEFINE6_MAX_BRI_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else // if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_DISPLAY_P3)
            {
                ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _DCIP3_SRGB_PRECISION, g_pucColorDISP_CALIBRATION_FLASH + _OCC_DISPLAYP3_MAX_BRI_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
#endif
            ScalerColorOutputGammaEnable(_FUNCTION_ON);
#if(_COLOR_IP_SRGB == _ON)
            ScalerColorSRGBEnable(_FUNCTION_ON);
#endif
            ScalerColorPCMInputGammaEnable(_FUNCTION_ON);
#if(_HW_D_DOMAIN_RGN_COUNT_MAX > 1)
            ScalerColorPCMSetEffectiveRegion(_HLW_INSIDEB_OUTSIDEA, _DB_APPLY_NO_POLLING);
#endif
#if(_COLOR_IP_I_GAMMA == _ON)
            ScalerColorPCMRegionEnable(_1P_NORMAL_REGION, _DB_APPLY_POLLING, _ON);
#endif
        }
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_UNIFORMITY_SET_IG_GAMMA)
        {
            ScalerTimerWaitForDDomainEvent(_EVENT_DEN_STOP);
            ScalerColorPCMInputGammaEnable(_FUNCTION_OFF);
            ScalerColorPCMInputGammaLoadTable(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_INDEX]);

            ScalerColorPCMInputGammaEnable(_FUNCTION_ON);
        }



#endif

#if(_UNIFORMITY_LEVEL0_SUPPORT == _ON)
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_UNIFORMITY_W_OFFSET)
        {
            ucOffsetTableBank = UserCommonColorGetPanelUniformityOffsetBank(g_ucColorUniformityLUTStartPosIndex);
            usOffsetTableAddr = UserCommonColorGetPanelUniformityOffsetAddr(g_ucColorUniformityLUTStartPosIndex);
            UserCommonFlashWrite(ucOffsetTableBank, usOffsetTableAddr + g_usColorUniformityLUTSavePos, (g_pucMcuDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 4, &g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_UNIFORMITY_INDEX]);
            g_usColorUniformityLUTSavePos += (g_pucMcuDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 4;
        }
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_UNIFORMITY_W_OFFSET_END)
        {
            g_ucColorUniformityChecksumType = g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_TYPE];

            g_ucColorCalibrationType = 0;
            g_ucColorCalibrationTypeII = 0;
            ucFlag = UserCommonColorCalibrationCheckSum();
            g_usColorUniformityLUTSavePos = 0;// level0, CYShih
        }
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_UNIFORMITY_W_DECAY)
        {
            ucOffsetTableBank = UserCommonColorGetPanelUniformityOffsetBank(g_ucColorUniformityLUTStartPosIndex);
            usDecayTableAddr = UserCommonColorGetPanelUniformityDecayAddr(g_ucColorUniformityLUTStartPosIndex);
            UserCommonFlashWrite(ucOffsetTableBank, usDecayTableAddr + g_usColorUniformityLUTSavePos, (g_pucMcuDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 4, &g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_UNIFORMITY_INDEX]);
            g_usColorUniformityLUTSavePos += (g_pucMcuDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 4;
        }
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_UNIFORMITY_W_DECAY_END)
        {
            g_ucColorUniformityChecksumType = g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_TYPE];

            g_ucColorCalibrationType = 0;
            g_ucColorCalibrationTypeII = 0;
            ucFlag = UserCommonColorCalibrationCheckSum();
        }
#endif  // End of #if(_UNIFORMITY_LEVEL0_SUPPORT == _ON)
#endif  // End of #if(_UNIFORMITY_SUPPORT== _ON)

#if(_BACKLIGHT_DIMMING_SUPPORT == _ON)
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_DIMMING_START)
        {
#if(_COLOR_IP_COLOR_CONVERT == _ON)
            ScalerColorSpaceConvertIDomainEnable(_DISPLAY_RGN_1P, _OFF);
            ScalerColorSpaceConvertDDomainEnable(_DISPLAY_RGN_1P, _OFF);
#endif
            UserInterfaceColorCalibrationBeforeDimmingProc();
        }
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_DIMMING_END)
        {
            UserInterfaceColorCalibrationAfterDimmingProc();
        }
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_DIMMING_CHECKFW)
        {
            UserCommonColorCalibrationReplyDimmingDefine();
            UserCommonColorCalibrationReplyResult(_DISP_CALIB_PASS);
            ScalerMcuDdcciReleaseScl();
            return;
        }
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_DIMMING_SETPWM)
        {
            UserCommonColorCalibrationSetPWMValue();
        }
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_DIMMING_SHOW_WHITE)
        {
            BYTE ucTempPatternType = g_ucColorPatternType;
            g_ucColorPatternType = _PG_PATTERN;
            UserCommonColorCalibrationPatternEnable(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_DIMMING_DATA_START]);
            UserCommonColorCalibrationShowPattern(_PATTERN_TOP, _PATTERN_TOP, _PATTERN_TOP);
            g_ucColorPatternType = ucTempPatternType;
        }
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_DIMMING_SHOW_BLACK)
        {
            BYTE ucTempPatternType = g_ucColorPatternType;
            g_ucColorPatternType = _PG_PATTERN;
            UserCommonColorCalibrationPatternEnable(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_DIMMING_DATA_START]);
            UserCommonColorCalibrationShowPattern(0, 0, 0);
            g_ucColorPatternType = ucTempPatternType;
        }
#if(_GLOBAL_DIMMING_OCC_TOOL_SUPPORT == _ON)
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_DIMMING_SET_GD_HDR)
        {
            UserCommonColorCalibrationIPBypass();
            ScalerColorPCMSetPCMMode(_1P_NORMAL_REGION, _PCM_MODE);
            // Set Input Gamma
            ScalerColorPCMInputGammaAdjust(_1P_NORMAL_REGION, g_pucColorDISP_CALIBRATION_FLASH + _OGC_HDR10_IG_1200_NOR_ADDRESS + (g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_SET_HDR_IG_INDEX] * _OGC_HDR10_IG_TABLE_SIZE), _OGC_FLASH_BANK, _IG_DB_DISABLE);

            ScalerColorPCMOutputGammaAdjust(_1P_NORMAL_REGION, g_pucColorDISP_CALIBRATION_FLASH + _DIMMING_OCC_GAMMA10_ADDRESS, _OCC_GAMMA_FLASH_BANK);

            // Set Color Matrix
            ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _SRGB_3_BIT_SHIFT_LEFT, g_pucColorDISP_CALIBRATION_FLASH + _OCC_HDR10_SRGB_MATRIX_ADDRESS + (g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_SET_HDR_COLOR_MATRIX] * _OCC_COLORMATRIX_TABLE_SIZE), _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);



            ScalerColorOutputGammaEnable(_FUNCTION_ON);
#if(_COLOR_IP_SRGB == _ON)
            ScalerColorSRGBEnable(_FUNCTION_ON);
#endif
            ScalerColorPCMInputGammaEnable(_FUNCTION_ON);

#if(_HW_D_DOMAIN_RGN_COUNT_MAX > 1)
            ScalerColorPCMSetEffectiveRegion(_HLW_INSIDEB_OUTSIDEA, _DB_APPLY_NO_POLLING);
#endif
#if(_COLOR_IP_I_GAMMA == _ON)
            ScalerColorPCMRegionEnable(_1P_NORMAL_REGION, _DB_APPLY_POLLING, _ON);
#endif
        }
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_DIMMING_WRITE_FLASH)
        {
            WORD usFlashAddr = 0;
            WORD usTableAddress = 0;

            if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_DIMMING_FLASH_FIRST] != 0)
            {
                g_usColorGDSavePos = 0;
            }

            switch(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_DIMMING_FLASH_INDEX])
            {
                case _DDCCI_DISP_CALIB_DIMMING_WRITE_PWMLUT:
                    usTableAddress = _OCC_GLOBAL_DIMMING_PWMLUT_ADDRESS;
                    break;

                default:
                    return;
            }
            usFlashAddr = (((WORD)_OGC_FLASH_PAGE) << 12) + usTableAddress + g_usColorGDSavePos;
            ucFlag &= UserCommonFlashWrite(_OGC_FLASH_BANK, usFlashAddr, g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_DIMMING_FLASH_LEN], &g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_DIMMING_FLASH_DATA]);
            g_usColorGDSavePos += g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_DIMMING_FLASH_LEN];
        }
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_DIMMING_SWITCH)
        {
            SET_ON_LINE_GD_HDR_CALIBRATION_STATUS(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_DIMMING_SWITCH_INDEX]);
            if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_DIMMING_SWITCH_INDEX] == _CALIBRATION_ON)
            {
#if(_GLOBAL_DIMMING_FUNCTION == _ON)
                UserCommonColorGlobalDimmingAdjust();
#endif
            }
        }
#endif
#endif
        if(ucCalibrationStep == _DDCCI_DISP_CALIB_PANEL_COLOR_MATCHING_DATA)
        {
            if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_COLOR_MATCHING_INDEX] == _DDCCI_DISP_CALIB_COLOR_MATCHING_READ)
            {
                UserCommonColorCalibrationAccessPanelColorMatchingData(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_COLOR_MATCHING_INDEX]);
                ScalerMcuDdcciReleaseScl();
                return;
            }
            else if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_COLOR_MATCHING_INDEX] == _DDCCI_DISP_CALIB_COLOR_MATCHING_WRITE)
            {
                UserCommonColorCalibrationAccessPanelColorMatchingData(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_COLOR_MATCHING_INDEX]);
            }
            else if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_COLOR_MATCHING_INDEX] == _DDCCI_DISP_CALIB_COLOR_MATCHING_ERASE)
            {
                for(ucCountPage = 0; ucCountPage <= 15; ucCountPage++)
                {
                    ucFlag &= UserCommonFlashErasePage(_OGC_FLASH_BANK, ucCountPage);
                }
            }
        }
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_PANEL_OGCOCC_LVRATIO)
        {
            UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _OGCOCC_LV_RARIO_ADDRESS, (g_pucMcuDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 4, &g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_LVRATIO_INDEX]);
        }
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_GENERAL_DPG)
        {
            usR = ((WORD)g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_GENERAL_DPG_R_CODE_H] << 8) | ((WORD)g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_GENERAL_DPG_R_CODE_L]);
            usG = ((WORD)g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_GENERAL_DPG_G_CODE_H] << 8) | ((WORD)g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_GENERAL_DPG_G_CODE_L]);
            usB = ((WORD)g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_GENERAL_DPG_B_CODE_H] << 8) | ((WORD)g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_GENERAL_DPG_B_CODE_L]);

            if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_GENERAL_DPG_TYPE] == _DPG_FULL)
            {
                ScalerDDomainPatternGenAdjustColor10bit(usR, usG, usB);
                UserCommonColorCalibrationSetBoxPatternGen(g_pucMcuDdcciRxBuf + _DDCCI_DISP_CALIB_GENERAL_DPG_BOX_THD, _DISABLE);
            }
            else
            {
                ScalerDDomainBoxPatternGenAdjustColor10bit(usR, usG, usB);
                UserCommonColorCalibrationSetBoxPatternGen(g_pucMcuDdcciRxBuf + _DDCCI_DISP_CALIB_GENERAL_DPG_BOX_THD, _ENABLE);
            }
            ScalerDDomainPatternGenEnable(_ENABLE);
            ScalerDDomainBackgroundEnable(_DDOMAIN_RGN_ALL, _DISABLE);
        }
#if(_HLG_SUPPORT == _ON)
        if(ucCalibrationStep == _DDCCI_DISP_CALIB_SAVE_HLG_YMAPPING_LUT)
        {
            if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_HLGLUT_TYPE_INDEX] == _DDCCI_DISP_CALIB_YM_STANDARD_LUT_WRITE)
            {
                UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _OGC_HLG_YM_STANDARD_MODE_ADDRESS + g_usColorHLGLUTSavePos, (g_pucMcuDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 5, &g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_HLGLUT_START]);
                g_usColorHLGLUTSavePos += (g_pucMcuDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 5;
            }
        }
#endif
#if(_OCC_BOX_PATTERN_GENERATOR_SUPPORT == _ON)
        if(ucCalibrationStep == _DDCCI_DISP_CALIB_OCC_SET_BOX_PATTERNGEN)
        {
            UserCommonColorCalibrationSetBoxPatternGen(g_pucMcuDdcciRxBuf + _DDCCI_DISP_CALIB_SET_FRONT_PG_INDEX, _ENABLE);
            g_ucColorPatternType = _PG_BOX_PATTERN;
        }
#endif
#if((_HDR10_BACKLIGHT_ADAPTIVE_TM_SUPPORT == _ON) || (_HDR10_MASTERING_LV_STEPLESS_TM_SUPPORT == _ON))
        if(ucCalibrationStep == _DDCCI_DISP_CALIB_SAVE_HDR_COMMAND)
        {
            if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_HDR_COMMAND_TYPE] == _DDCCI_DISP_CALIB_HDR_BACKLIGHT_ADAPTIVE)
            {
                UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _OGC_HDR10_BACKLIGHT_ADAPTIVE_BOUND_ADDRESS, _OGC_HDR10_BACKLIGHT_ADAPTIVE_BOUND_LENGTH, &g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_HDR_DATA_INDEX]);
            }
            else if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_HDR_COMMAND_TYPE] == _DDCCI_DISP_CALIB_HDR_MASTERING_STEPLESS)
            {
                UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _OGC_HDR10_MASTERING_LV_STEPLESS_BOUND_ADDRESS, _OGC_HDR10_MASTERING_LV_STEPLESS_BOUND_LENGTH, &g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_HDR_DATA_INDEX]);
            }
        }
#endif
#if(_SAVE_OGC_OCC_VERIFY_REPORT_SUPPORT == _ON)
        if(ucCalibrationStep == _DDCCI_DISP_CALIB_SAVE_OCC_VERIFY_REPORT)
        {
            UserCommonFlashWrite(_OGC_OCC_VERIFY_REPORT_BANK, g_usColorVerifySavePos, (g_pucMcuDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 4, &g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_OCC_VERIFY_INDEX]);
            g_usColorVerifySavePos += (g_pucMcuDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 4;
        }
#endif
//****************************************************************************************//
//                               FINAL PROCESS                                            //
//****************************************************************************************//
        /////////////////////////////////////////////////////////////////
        ///////////////////////REPLY RESULTS/////////////////////////////
        /////////////////////////////////////////////////////////////////
        if(ucCalibrationStep == _DDCCI_DISP_CALIB_VERIFICATION)
        {
            UserCommonColorCalibrationReplyResult(_DISP_CALIB_PASS);
        }
        else
        {
            if(ucFlag == 1)
            {
                UserCommonColorCalibrationReplyResult(_DISP_CALIB_PASS);
            }
            else
            {
                if((ucCalibrationStep == _DDCCI_DISP_CALIB_OGC_MEASURE_BLACK) || (ucCalibrationStep == _DDCCI_DISP_CALIB_OGC_MEASURE_GREEN))
                {
                    UserCommonColorCalibrationReplyResult(_DISP_CALIB_ERASE_ERROR);
                }
                else if(ucCalibrationStep == _DDCCI_DISP_CALIB_OGC_MEASURE_RED)
                {
                    UserCommonColorCalibrationReplyResult(_DISP_CALIB_FW_ERROR);
                }
                else
                {
                    UserCommonColorCalibrationReplyResult(_DISP_CALIB_CRC_ERROR);
                }
            }
        }
    }
    else    // else of if(UserCommonColorCalibrationInitialCheck() == _SUCCESS)
    {
        UserCommonColorCalibrationReplyResult(_DISP_CALIB_FAIL);
    }

    ScalerMcuDdcciReleaseScl();
}

//--------------------------------------------------
// Description  : OGC Measure Start Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit UserCommonColorCalibrationOGCStart(void)
{
    BYTE ucCnt = 0;
    BYTE ucFlag = 1;
#if(_OCC_RGB_3D_GAMMA_SUPPORT == _ON)
    BYTE ucCnt2 = 0;
#endif
#if(_HDR10_SUPPORT == _ON)
    g_ucColorIGLUTSavePos = 0;
    g_usColorHLGLUTSavePos = 0;
    g_usColor1025IGLUTSavePos = 0;

#endif

    // Get Counter Start
#if(_OGC_FUNCTION == _ON)
    for(ucCnt = 0; ucCnt < _OGC_TOTAL_GAMMA; ucCnt++)
    {
        g_ppusColorGammaCount[ucCnt][0] = _OGC_GAMMA_TABLE_LENGTH;
        g_ppusColorGammaCount[ucCnt][1] = _OGC_GAMMA_TABLE_LENGTH;
        g_ppusColorGammaCount[ucCnt][2] = _OGC_GAMMA_TABLE_LENGTH;
    }
#endif  // End of #if(_OGC_SUPPORT == _ON)

#if(_OCC_FUNCTION == _ON)
    g_ppusColorGammaCount[ucCnt][0] = 2200;
    g_ppusColorGammaCount[ucCnt][1] = 2200;
    g_ppusColorGammaCount[ucCnt][2] = 2200;
    ucCnt++;
#endif  // End of #if(_OCC_SUPPORT == _ON)

#if(_OGC_DICOM_FUNCTION == _ON)

    g_ppusColorGammaCount[ucCnt][0] = _OGC_GAMMA_TABLE_LENGTH;
    g_ppusColorGammaCount[ucCnt][1] = _OGC_GAMMA_TABLE_LENGTH;
    g_ppusColorGammaCount[ucCnt][2] = _OGC_GAMMA_TABLE_LENGTH;
    ucCnt++;
#if(_OGC_TOTAL_DICOM > 1)
    g_ppusColorGammaCount[ucCnt][0] = _OGC_GAMMA_TABLE_LENGTH;
    g_ppusColorGammaCount[ucCnt][1] = _OGC_GAMMA_TABLE_LENGTH;
    g_ppusColorGammaCount[ucCnt][2] = _OGC_GAMMA_TABLE_LENGTH;
    ucCnt++;
#if(_OGC_TOTAL_DICOM > 2)
    g_ppusColorGammaCount[ucCnt][0] = _OGC_GAMMA_TABLE_LENGTH;
    g_ppusColorGammaCount[ucCnt][1] = _OGC_GAMMA_TABLE_LENGTH;
    g_ppusColorGammaCount[ucCnt][2] = _OGC_GAMMA_TABLE_LENGTH;
    ucCnt++;
#if(_OGC_TOTAL_DICOM > 3)
    g_ppusColorGammaCount[ucCnt][0] = _OGC_GAMMA_TABLE_LENGTH;
    g_ppusColorGammaCount[ucCnt][1] = _OGC_GAMMA_TABLE_LENGTH;
    g_ppusColorGammaCount[ucCnt][2] = _OGC_GAMMA_TABLE_LENGTH;
    ucCnt++;
#endif
#endif
#endif
#endif  // End of #if(_OGC_DICOM_SUPPORT == _ON)

#if(_BACKLIGHT_DIMMING_SUPPORT == _ON)
    g_ppusColorGammaCount[ucCnt][0] = 2200;
    g_ppusColorGammaCount[ucCnt][1] = 2200;
    g_ppusColorGammaCount[ucCnt][2] = 2200;
    ucCnt++;
#endif  // End of #if(_OGC_DICOM_SUPPORT == _ON)

#if(_FREESYNC_II_SUPPORT == _ON)
    g_ppusColorGammaCount[ucCnt][0] = 2200;
    g_ppusColorGammaCount[ucCnt][1] = 2200;
    g_ppusColorGammaCount[ucCnt][2] = 2200;
    ucCnt++;
#endif  // End of #if(_FREESYNC_II_SUPPORT == _ON)

#if(_OCC_RGB_3D_GAMMA_SUPPORT == _ON)
    for(ucCnt2 = 0; ucCnt2 < _OCC_RGB_3D_GAMMA_TOTAL_SET; ucCnt2++)
    {
        g_ppusColor3DGammaCount[ucCnt2][0] = _OGC_GAMMA_TABLE_LENGTH;
        g_ppusColor3DGammaCount[ucCnt2][1] = _OGC_GAMMA_TABLE_LENGTH;
        g_ppusColor3DGammaCount[ucCnt2][2] = _OGC_GAMMA_TABLE_LENGTH;
    }
#endif  // End of #if(_OCC_RGB_3D_GAMMA_SUPPORT == _ON)

    // Get Counter End
    g_ucColorCalibrationType = g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_TYPE];

#if((_TWO_BRI_CALIBRATION_TYPE != _TWO_BRI_CALIBRATION_NONE) || (_OCC_RGB_3D_GAMMA_SUPPORT == _ON))
    g_ucColorBacklightFlag = g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_HDR_FLAG];
#endif

#if(_OGC_FUNCTION == _OFF)
    if(((g_ucColorCalibrationType >> _OGC_CAL_TYPE) & _BIT0) == _TRUE)
    {
        ucFlag = 0;
    }
#endif  // End of #if(_OGC_SUPPORT == _OFF)

#if(_OCC_FUNCTION == _OFF)
    if(((g_ucColorCalibrationType >> _OCC_CAL_TYPE) & _BIT0) == _TRUE)
    {
        ucFlag = 0;
    }
#endif  // End of #if(_OCC_SUPPORT == _OFF)

#if(_OGC_DICOM_FUNCTION == _OFF)
    if(((g_ucColorCalibrationType >> _DICOM_CAL_TYPE) & _BIT0) == _TRUE)
    {
        ucFlag = 0;
    }
#endif  // End of #if(_OGC_DICOM_SUPPORT == _OFF)

    if(((g_ucColorCalibrationType >> (_DICOM_CAL_TYPE + 1)) & 0x07) != _OGC_TOTAL_GAMMA)
    {
        ucFlag = 0;
    }

    g_ucColorPatternType = (g_ucColorCalibrationType & _BIT6) >> 6;
#if(_OCC_BOX_PATTERN_GENERATOR_SUPPORT == _ON)
    if(g_ucColorPatternType == _PG_PATTERN)
    {
        g_ucColorPatternType = _PG_BOX_PATTERN;
    }
#endif
    g_ucColorCalibrationTypeII = (g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_TYPE_II] & _BIT0) >> 0;

#if(_DCIP3_NO_COMPRESSION_SUPPORT == _ON)
    g_ucColorDCIP3MatrixType = (g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_TYPE_II] & _BIT2) >> 2;
    if(!g_ucColorDCIP3MatrixType)
    {
        ucFlag = 0;
    }
#endif

#if(_OCC_USER_DEFINE_SHIFT_1_BIT_SUPPORT == _ON)
    g_ucColorUserDefineMatrixType = (g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_TYPE_II] & _BIT3) >> 3;
    if(!g_ucColorUserDefineMatrixType)
    {
        ucFlag = 0;
    }
#endif

#if(_MULTI_BRI_CALIBRATION_TYPE > _MULTI_BRI_CALIBRATION_NONE)
    g_ucColorMultiOCCType = (g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_TYPE_II] & _BIT4) >> 4;
    if(!g_ucColorMultiOCCType)
    {
        ucFlag = 0;
    }
#endif

#if(_OCC_GAMUT_NO_COMPRESSION_SUPPORT == _ON)
    g_ucColorOCCMatrixType = (g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_TYPE_II] & _BIT5) >> 5;
    if(!g_ucColorOCCMatrixType)
    {
        ucFlag = 0;
    }
#endif

    UserCommonColorCalibrationIPBypass();

#if(_OCC_FUNCTION == _ON)
    if(((g_ucColorCalibrationType >> _OCC_CAL_TYPE) & _BIT0) == _TRUE)
    {
#if(_HW_D_DOMAIN_RGN_COUNT_MAX > 1)
        ScalerColorPCMSetEffectiveRegion(_HLW_INSIDEB_OUTSIDEA, _DB_APPLY_NO_POLLING);
#endif
        ScalerColorPCMSetPCMMode(_1P_NORMAL_REGION, _PCM_MODE);
        ScalerColorPCMInputGammaEnable(_FUNCTION_OFF);
#if(_HW_D_DOMAIN_RGN_COUNT_MAX > 1)
        ScalerColorSRGBSetEffectiveRegion(_HLW_INSIDEB_OUTSIDEA, _DB_APPLY_POLLING);
#endif
#if(_HDR10_SUPPORT == _ON)
        ScalerColorPCMInputGammaLoadTable(_PCM_HDR_2084);
#else
        ScalerColorPCMInputGammaLoadTable(_PCM_SRGB);
#endif
        UserCommonColorCalibrationShowDDomainPattern(tOCC_SRGB_TABLE[0], tOCC_SRGB_TABLE[1], tOCC_SRGB_TABLE[2], g_ucColorPatternType);
        ScalerDDomainPatternGenEnable(_ENABLE);
    }
    else
#endif  // End of #if(_OCC_SUPPORT == _ON)
    {

#if(_PCM_FUNCTION == _ON)
        ScalerColorPCMInputGammaEnable(_FUNCTION_OFF);
#endif
    }

    return ucFlag;
}

#if(_OCC_FUNCTION == _ON)
//--------------------------------------------------
// Description  : Display Calibration OCC Process
// Input Value  : Calibration Step
// Output Value : ucFlag
//--------------------------------------------------
BYTE UserCommonColorCalibrationOCCProcess(BYTE ucStep)
{
    BYTE ucFlag = 1;
    BYTE ucPatternEnd = (_OCC_LUT_MODE == _ON) ? _DDCCI_DISP_CALIB_OCC_MEASURE_SRGB21 : _DDCCI_DISP_CALIB_OCC_MEASURE_SRGB7;


    if((ucStep >= _DDCCI_DISP_CALIB_OCC_MEASURE_SRGB1) && (ucStep < ucPatternEnd))
    {
        UserCommonColorCalibrationShowDDomainPattern(tOCC_SRGB_TABLE[(ucStep - _DDCCI_DISP_CALIB_OCC_MEASURE_SRGB1 + 1) * 3],
                                                     tOCC_SRGB_TABLE[(ucStep - _DDCCI_DISP_CALIB_OCC_MEASURE_SRGB1 + 1) * 3 + 1],
                                                     tOCC_SRGB_TABLE[(ucStep - _DDCCI_DISP_CALIB_OCC_MEASURE_SRGB1 + 1) * 3 + 2], g_ucColorPatternType);
    }
    else if(ucStep == ucPatternEnd)
    {
        if(g_ucColorBacklightFlag == _NORMAL_BACKLIGHT_CAL)
        {
            UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _OCC_SRGBMATRIX_ADDRESS + g_usColorMatrixSavePos, (g_pucMcuDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 5, &g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_OCC_MATRIX]);
            g_usColorMatrixSavePos += (g_pucMcuDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 5;
        }
#if(_TWO_BRI_CALIBRATION_TYPE >= _TWO_BRI_CALIBRATION_OGC_OCC_DICOM_HDR)
#if(_MULTI_BRI_CALIBRATION_TYPE >= _MULTI_BRI_THREE_CALIBRATION)
        else if(g_ucColorBacklightFlag == _MULTI_BACKLIGHT_3_CAL)
        {
            UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _OCC_SRGBMATRIX_MULTI_BRI_3_ADDRESS + g_usColorMatrixSavePos, (g_pucMcuDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 5, &g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_OCC_MATRIX]);
            g_usColorMatrixSavePos += (g_pucMcuDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 5;
        }
#if(_MULTI_BRI_CALIBRATION_TYPE >= _MULTI_BRI_FOUR_CALIBRATION)
        else if(g_ucColorBacklightFlag == _MULTI_BACKLIGHT_4_CAL)
        {
            UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _OCC_SRGBMATRIX_MULTI_BRI_4_ADDRESS + g_usColorMatrixSavePos, (g_pucMcuDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 5, &g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_OCC_MATRIX]);
            g_usColorMatrixSavePos += (g_pucMcuDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 5;
        }
#endif
#endif
        else
        {
            UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _OCC_SRGBMATRIX_MAX_BRI_ADDRESS + g_usColorMatrixSavePos, (g_pucMcuDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 5, &g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_OCC_MATRIX]);
            g_usColorMatrixSavePos += (g_pucMcuDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 5;
        }
#endif
#if(_COLOR_IP_I_GAMMA == _ON)
        ScalerColorPCMRegionEnable(_1P_NORMAL_REGION, _DB_APPLY_POLLING, _OFF);
#endif

#if(_TWO_BRI_CALIBRATION_TYPE >= _TWO_BRI_CALIBRATION_OGC_OCC_DICOM_HDR)
        if(g_ucColorBacklightFlag == _MAX_BACKLIGHT_CAL)
        {
            // Set PCM Color Matrix
            if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_SRGB)
            {
                ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _SRGB_0_BIT_SHIFT_LEFT, g_pucColorDISP_CALIBRATION_FLASH + _OCC_SRGBMATRIX_MAX_BRI_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_ADOBE_RGB)
            {
                ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _ADOBE_SRGB_PRECISION, g_pucColorDISP_CALIBRATION_FLASH + _OCC_ADOBEMATRIX_MAX_BRI_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_USER_DEFINE)
            {
                ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _USER_DEFINE_PRECISION, g_pucColorDISP_CALIBRATION_FLASH + _OCC_USERDEFINE_MAX_BRI_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_EBU_MODE)
            {
                ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _SRGB_0_BIT_SHIFT_LEFT, g_pucColorDISP_CALIBRATION_FLASH + _OCC_EBU_MAX_BRI_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_SOFT_PROFT)
            {
                ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _SRGB_0_BIT_SHIFT_LEFT, g_pucColorDISP_CALIBRATION_FLASH + _OCC_SOFTPROOF_MAX_BRI_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_REC_709)
            {
                ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _SRGB_0_BIT_SHIFT_LEFT, g_pucColorDISP_CALIBRATION_FLASH + _OCC_REC709_MAX_BRI_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_DCI_P3)
            {
                ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _DCIP3_SRGB_PRECISION, g_pucColorDISP_CALIBRATION_FLASH + _OCC_DCIP3_MAX_BRI_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_SMPTE_C)
            {
                ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _SRGB_0_BIT_SHIFT_LEFT, g_pucColorDISP_CALIBRATION_FLASH + _OCC_SMPTEC_MAX_BRI_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_USER_DEFINE_2)
            {
                ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _USER_DEFINE_PRECISION, g_pucColorDISP_CALIBRATION_FLASH + _OCC_USERDEFINE2_MAX_BRI_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_USER_DEFINE_3)
            {
                ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _USER_DEFINE_PRECISION, g_pucColorDISP_CALIBRATION_FLASH + _OCC_USERDEFINE3_MAX_BRI_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_USER_DEFINE_4)
            {
                ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _USER_DEFINE_PRECISION, g_pucColorDISP_CALIBRATION_FLASH + _OCC_USERDEFINE4_MAX_BRI_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_USER_DEFINE_5)
            {
                ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _USER_DEFINE_PRECISION, g_pucColorDISP_CALIBRATION_FLASH + _OCC_USERDEFINE5_MAX_BRI_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_USER_DEFINE_6)
            {
                ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _USER_DEFINE_PRECISION, g_pucColorDISP_CALIBRATION_FLASH + _OCC_USERDEFINE6_MAX_BRI_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else // if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_DISPLAY_P3)
            {
                ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _DCIP3_SRGB_PRECISION, g_pucColorDISP_CALIBRATION_FLASH + _OCC_DISPLAYP3_MAX_BRI_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
        }
        else
#endif
        {
            // Set PCM Color Matrix
            if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_SRGB)
            {
                ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _SRGB_0_BIT_SHIFT_LEFT, g_pucColorDISP_CALIBRATION_FLASH + _OCC_SRGBMATRIX_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_ADOBE_RGB)
            {
                ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _ADOBE_SRGB_PRECISION, g_pucColorDISP_CALIBRATION_FLASH + _OCC_ADOBEMATRIX_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_USER_DEFINE)
            {
                ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _USER_DEFINE_PRECISION, g_pucColorDISP_CALIBRATION_FLASH + _OCC_USERDEFINE_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_EBU_MODE)
            {
                ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _SRGB_0_BIT_SHIFT_LEFT, g_pucColorDISP_CALIBRATION_FLASH + _OCC_EBU_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_SOFT_PROFT)
            {
                ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _SRGB_0_BIT_SHIFT_LEFT, g_pucColorDISP_CALIBRATION_FLASH + _OCC_SOFTPROOF_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_REC_709)
            {
                ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _SRGB_0_BIT_SHIFT_LEFT, g_pucColorDISP_CALIBRATION_FLASH + _OCC_REC709_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_DCI_P3)
            {
                ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _DCIP3_SRGB_PRECISION, g_pucColorDISP_CALIBRATION_FLASH + _OCC_DCIP3_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_SMPTE_C)
            {
                ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _SRGB_0_BIT_SHIFT_LEFT, g_pucColorDISP_CALIBRATION_FLASH + _OCC_SMPTEC_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_USER_DEFINE_2)
            {
                ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _USER_DEFINE_PRECISION, g_pucColorDISP_CALIBRATION_FLASH + _OCC_USERDEFINE2_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_USER_DEFINE_3)
            {
                ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _USER_DEFINE_PRECISION, g_pucColorDISP_CALIBRATION_FLASH + _OCC_USERDEFINE3_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_USER_DEFINE_4)
            {
                ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _USER_DEFINE_PRECISION, g_pucColorDISP_CALIBRATION_FLASH + _OCC_USERDEFINE4_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_USER_DEFINE_5)
            {
                ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _USER_DEFINE_PRECISION, g_pucColorDISP_CALIBRATION_FLASH + _OCC_USERDEFINE5_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_USER_DEFINE_6)
            {
                ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _USER_DEFINE_PRECISION, g_pucColorDISP_CALIBRATION_FLASH + _OCC_USERDEFINE6_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else // if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_DISPLAY_P3)
            {
                ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _DCIP3_SRGB_PRECISION, g_pucColorDISP_CALIBRATION_FLASH + _OCC_DISPLAYP3_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
        }

#if(_COLOR_IP_SRGB == _ON)
        ScalerColorSRGBEnable(_FUNCTION_ON);
#endif
#if(_COLOR_IP_I_GAMMA == _ON)
        ScalerColorPCMRegionEnable(_1P_NORMAL_REGION, _DB_APPLY_POLLING, _ON);
#endif
        // Disable Display Pattern Gen. & set (0,0,0)
        ScalerDDomainPatternGenEnable(_DISABLE);
        UserCommonColorCalibrationShowDDomainPattern(0, 0, 0, g_ucColorPatternType);
    }
#if(_HDR10_SUPPORT == _ON)
    else if(ucStep == _DDCCI_DISP_CALIB_SAVE_HDR_MATRIX)
    {
        UserCommonFlashWrite(_OGC_FLASH_BANK, _OCC_HDR10_SRGB_MATRIX_ADDRESS, (g_pucMcuDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 4, &g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_HDRMATRIX_START]);
    }
#endif
    return ucFlag;
}
#endif // End of #if(_OCC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Access Multi panel color matching data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonColorCalibrationAccessPanelColorMatchingData(BYTE ucCommand)
{
    BYTE pucTemp[12] = {0};
    if(ucCommand == _DDCCI_DISP_CALIB_COLOR_MATCHING_READ)
    {
        UserCommonFlashRead(_OGC_FLASH_BANK, ((WORD)_OGC_FLASH_PAGE << 12) | _OCC_PANEL_COLOR_MAPPING_DATA_ADDRESS, 12, pucTemp);
        g_pucMcuDdcciTxBuf[_DDCCI_SOURCE] = _DDCCI_DEST_ADDRESS;
        g_pucMcuDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | 0x0C;
        g_pucMcuDdcciTxBuf[2] = pucTemp[0];// xp
        g_pucMcuDdcciTxBuf[3] = pucTemp[1];
        g_pucMcuDdcciTxBuf[4] = pucTemp[2];// yp
        g_pucMcuDdcciTxBuf[5] = pucTemp[3];
        g_pucMcuDdcciTxBuf[6] = pucTemp[4];// xc
        g_pucMcuDdcciTxBuf[7] = pucTemp[5];
        g_pucMcuDdcciTxBuf[8] = pucTemp[6];// yc
        g_pucMcuDdcciTxBuf[9] = pucTemp[7];
        g_pucMcuDdcciTxBuf[10] = pucTemp[8];// xp_target
        g_pucMcuDdcciTxBuf[11] = pucTemp[9];
        g_pucMcuDdcciTxBuf[12] = pucTemp[10];// yp_target
        g_pucMcuDdcciTxBuf[13] = pucTemp[11];
        g_pucMcuDdcciTxBuf[14] = UserCommonDdcciCalCheckSum();// CYShih, 8
        ScalerMcuDdcciSendData(GET_RUN_DDCCI_HANDLE_CHANNEL(), g_pucMcuDdcciTxBuf);
        SET_INTERRUPT_ENABLE_STATUS(_INT_EXINT_1, _ENABLE);
    }
    else if(ucCommand == _DDCCI_DISP_CALIB_COLOR_MATCHING_WRITE)
    {
        memcpy(pucTemp, (g_pucMcuDdcciRxBuf + 6), 12);
        UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) | _OCC_PANEL_COLOR_MAPPING_DATA_ADDRESS, 12, pucTemp);
    }
}

//--------------------------------------------------
// Description  : Check if the checksum from Tool is equal to DDCCI data
// Input Value  : None
// Output Value : _SUCCESS/_FAIL
//--------------------------------------------------
bit UserCommonColorCalibrationInitialCheck(void)
{
    BYTE ucSum = 0;
    BYTE ucChecksum = 0;
    BYTE ucLength = 0;
    BYTE ucI = 0;

    ucLength = g_pucMcuDdcciRxBuf[_DDCCI_LENGTH] & 0x7F;

    for(ucI = 2; ucI < (ucLength + 1); ucI++)
    {
        ucSum += g_pucMcuDdcciRxBuf[ucI];
    }

    ucChecksum = g_pucMcuDdcciRxBuf[ucLength + 1];

    if(ucSum == ucChecksum)
    {
        return _SUCCESS;
    }
    else
    {
        return _FAIL;
    }
}


//--------------------------------------------------
// Description  : Read or Write LUT Data from Flash
// Input Value  : bReadWrite: Read or Write
//                ucBank: Bank index
//                ucIndex: Gamma index
//                usAddr: address in ucBank
//                ucLength: the data length to load
//                pucData: data buffer to save the load data
// Output Value : None
//--------------------------------------------------
void UserCommonColorCalibrationFlashData(bit bReadWrite, BYTE ucBank, BYTE ucIndex, WORD usAddr, WORD usLength, BYTE *pucData)
{
#if(_FREESYNC_II_SUPPORT == _ON)
    if(ucIndex == _OCC_FREESYNC_II_POSITION)
    {
        ucBank = _FREESYNC_II_FLASH_BANK;
        usAddr += ((WORD)_FREESYNC_II_FLASH_PAGE << 12);
    }
    else
#endif
    {
#if(_OCC_FUNCTION == _ON)
#if(_OGC_FUNCTION == _ON)
        if(ucIndex >= _OCC_POSITION)
#endif
        {
#if(_OGC_DICOM_FUNCTION == _ON)
            if(ucIndex == _DICOM_POSITION)
            {
                ucBank = ucBank;
            }
#if(_OGC_TOTAL_DICOM > 1)
            else if(ucIndex == _DICOM2_POSITION)
            {
                ucBank = ucBank;
            }
#if(_OGC_TOTAL_DICOM > 2)
            else if(ucIndex == _DICOM3_POSITION)
            {
                ucBank = ucBank;
            }
#if(_OGC_TOTAL_DICOM > 3)
            else if(ucIndex == _DICOM4_POSITION)
            {
                ucBank = ucBank;
            }
#endif
#endif
#endif
            else
#endif
            {
                ucBank = _OCC_GAMMA_FLASH_BANK;
            }
        }
#endif

        usAddr += ((WORD)_OGC_FLASH_PAGE << 12);
        ucIndex = ucIndex;
    }

    if(bReadWrite == _READ)
    {
        UserCommonFlashRead(ucBank, usAddr, usLength, pucData);
    }
    else
    {
        UserCommonFlashWrite(ucBank, usAddr, usLength, pucData);
    }
}

//--------------------------------------------------
// Description  : Save LUT Data from DDCCI Rx
// Input Value  : nAddress: address in DISP_CALIBRATION_FLASH;
//                nLength: Data Length
//                ucBuffer: pointer of databuffer
// Output Value : None
//--------------------------------------------------
void UserCommonColorCalibrationSaveLUT(BYTE ucTotalLength)
{
    BYTE ucLUTLength = 0;
    BYTE ucPointer = 5;
    BYTE ucGammaIndex = 0;
    BYTE ucRGB = 0;
    WORD usStartAddr = 0;
    WORD usCurrLUT = 0;
    BYTE pucIntoLUT[128] = {0};
    SWORD shRemain = 0;
    SWORD shCnt = 0;
    // int nNum = 0;
    BYTE ucCurPointer = 0;
    SWORD shWriteCnt = 0;
#if((_OCC_FUNCTION == _ON) || (_PCM_FULL_TIME_FUNCTION == _ON))
    bit bOCCMode = _FALSE;
#endif
#if(_OGC_NO_INTERPOLATION_SUPPORT == _OFF)
    WORD usLastLUT = 0;
    BYTE ucJ = 0;
    WORD usInto = 0;
    bit bIsLastLUT = _FALSE;
#if((_OCC_FUNCTION == _ON) || (_PCM_FULL_TIME_FUNCTION == _ON))
    bit bWriteDirectly = _FALSE;
#endif
#endif
    BYTE ucColorGammaBankNum = 0;
    BYTE *pucColorGammaBankAddr = _NULL_POINTER;
    WORD usFlashSaveAddr = 0;
    WORD usFlashSaveLength = 0;

    // ucTotalLength - 1: exclude checksum
    while(ucPointer < (ucTotalLength - 1))
    {
        // LUT Length (exclude ID and Length Bytes)
        ucLUTLength = g_pucMcuDdcciRxBuf[ucPointer] - 2;

        ucGammaIndex = (g_pucMcuDdcciRxBuf[ucPointer + 1] >> 4) & 0x0F;
        ucRGB = g_pucMcuDdcciRxBuf[ucPointer + 1] & 0x0F;
        ucPointer += 2;

        if(ucGammaIndex >= (sizeof(g_ppusColorGammaCount) / sizeof(g_ppusColorGammaCount[0])))
        {
            return;
        }

#if(_TWO_BRI_CALIBRATION_TYPE >= _TWO_BRI_CALIBRATION_OGC_OCC_DICOM_HDR)
        if(g_ucColorBacklightFlag == _MAX_BACKLIGHT_CAL)
        {
            ucColorGammaBankNum = UserCommonColorGetOGCBank(ucGammaIndex, _OGC_MAX_BACKLIGHT_TYPE);
            pucColorGammaBankAddr = UserCommonColorGetOGCAddr(ucGammaIndex, _OGC_MAX_BACKLIGHT_TYPE);
        }
        else
#endif
        {
            ucColorGammaBankNum = UserCommonColorGetOGCBank(ucGammaIndex, _OGC_NORMAL_TYPE);
            pucColorGammaBankAddr = UserCommonColorGetOGCAddr(ucGammaIndex, _OGC_NORMAL_TYPE);
        }

#if(_OCC_FUNCTION == _ON)

        if(ucGammaIndex == _OCC_POSITION)
        {
            bOCCMode = _TRUE;
        }
        else
        {
#if(_PCM_FULL_TIME_FUNCTION == _ON)
            bOCCMode = _TRUE;
#else
            bOCCMode = _FALSE;
#endif
        }

#if(_BACKLIGHT_DIMMING_SUPPORT == _ON)
        if(ucGammaIndex == _DIMMING_POSITION)
        {
            bOCCMode = _TRUE;
        }
#endif

#if(_FREESYNC_II_SUPPORT == _ON)
        if(ucGammaIndex == _OCC_FREESYNC_II_POSITION)
        {
            bOCCMode = _TRUE;
        }
#endif
#else
#if(_PCM_FULL_TIME_FUNCTION == _ON)
        bOCCMode = _TRUE;
#endif
#endif


        if(ucGammaIndex == _NONE_VALUE)
        {
            return;
        }
#if(_OCC_FUNCTION == _ON)
        else if(ucGammaIndex == _OCC_POSITION)
        {
#if(((_TWO_BRI_CALIBRATION_TYPE == _TWO_BRI_CALIBRATION_DICOM_HDR) && (_HDR10_SUPPORT == _ON)) || (_TWO_BRI_CALIBRATION_TYPE >= _TWO_BRI_CALIBRATION_OGC_OCC_DICOM_HDR))
            if(g_ucColorBacklightFlag == _MAX_BACKLIGHT_CAL)
            {
                usStartAddr = tGAMMA_INDEX[_OCC_HDR_POSITION] + (ucRGB) * 2200;
            }
#if(_MULTI_BRI_CALIBRATION_TYPE >= _MULTI_BRI_THREE_CALIBRATION)
            else if(g_ucColorBacklightFlag == _MULTI_BACKLIGHT_3_CAL)
            {
                usStartAddr = tGAMMA_INDEX[_OCC_MULTI_BRI_3_POSITION] + (ucRGB) * 2200;
            }
#if(_MULTI_BRI_CALIBRATION_TYPE >= _MULTI_BRI_FOUR_CALIBRATION)
            else if(g_ucColorBacklightFlag == _MULTI_BACKLIGHT_4_CAL)
            {
                usStartAddr = tGAMMA_INDEX[_OCC_MULTI_BRI_4_POSITION] + (ucRGB) * 2200;
            }
#endif
#endif
            else
#endif
            {
                usStartAddr = tGAMMA_INDEX[_OCC_POSITION] + (ucRGB) * 2200;
            }
        }
#if(_BACKLIGHT_DIMMING_SUPPORT == _ON)
        else if(ucGammaIndex == _DIMMING_POSITION)
        {
            usStartAddr = tGAMMA_INDEX[_DIMMING_POSITION] + (ucRGB) * 2200;
        }
#endif
#if(_FREESYNC_II_SUPPORT == _ON)
        else if(ucGammaIndex == _OCC_FREESYNC_II_POSITION)
        {
            usStartAddr = tGAMMA_INDEX[_OCC_FREESYNC_II_POSITION] + (ucRGB) * 2200;
        }
#endif
#endif
#if(_OGC_DICOM_FUNCTION == _ON)
        else if(ucGammaIndex == _DICOM_POSITION)
        {
            ucColorGammaBankNum = UserCommonColorGetDICOMBank(_DICOM1_TYPE);
            pucColorGammaBankAddr = UserCommonColorGetDICOMAddr(_DICOM1_TYPE);
            usStartAddr = (DWORD)pucColorGammaBankAddr + (ucRGB) * _OGC_GAMMA_TABLE_LENGTH;
        }
#if(_OGC_TOTAL_DICOM > 1)
        else if(ucGammaIndex == _DICOM2_POSITION) // DICOM2
        {
            ucColorGammaBankNum = UserCommonColorGetDICOMBank(_DICOM2_TYPE);
            pucColorGammaBankAddr = UserCommonColorGetDICOMAddr(_DICOM2_TYPE);
            usStartAddr = (DWORD)pucColorGammaBankAddr + (ucRGB) * _OGC_GAMMA_TABLE_LENGTH;
        }
#if(_OGC_TOTAL_DICOM > 2)
        else if(ucGammaIndex == _DICOM3_POSITION) // DICOM3
        {
            ucColorGammaBankNum = UserCommonColorGetDICOMBank(_DICOM3_TYPE);
            pucColorGammaBankAddr = UserCommonColorGetDICOMAddr(_DICOM3_TYPE);
            usStartAddr = (DWORD)pucColorGammaBankAddr + (ucRGB) * _OGC_GAMMA_TABLE_LENGTH;
        }
#if(_OGC_TOTAL_DICOM > 3)
        else if(ucGammaIndex == _DICOM4_POSITION) // DICOM4
        {
            ucColorGammaBankNum = UserCommonColorGetDICOMBank(_DICOM4_TYPE);
            pucColorGammaBankAddr = UserCommonColorGetDICOMAddr(_DICOM4_TYPE);
            usStartAddr = (DWORD)pucColorGammaBankAddr + (ucRGB) * _OGC_GAMMA_TABLE_LENGTH;
        }
#endif
#endif
#endif
#endif
        else
        {
            usStartAddr = (DWORD)pucColorGammaBankAddr + (ucRGB) * _OGC_GAMMA_TABLE_LENGTH;
        }

#if(_OGC_NO_INTERPOLATION_SUPPORT == _OFF)
        bIsLastLUT = _FALSE;

#if((_OCC_FUNCTION == _ON) || (_PCM_FULL_TIME_FUNCTION == _ON))
        if((bOCCMode == _TRUE) && (g_ppusColorGammaCount[ucGammaIndex][ucRGB] == 2200))
        {
            bIsLastLUT = _TRUE;
        }
        else if((bOCCMode == _FALSE) && (g_ppusColorGammaCount[ucGammaIndex][ucRGB] == 2052))
        {
            bIsLastLUT = _TRUE;
        }
#else
        if(g_ppusColorGammaCount[ucGammaIndex][ucRGB] == 2052)
        {
            bIsLastLUT = _TRUE;
        }
#endif
        if(bIsLastLUT == _TRUE)
        {
            shRemain = (ucLUTLength - 2) * 4 + 4;
        }
        else
        {
#if((_OCC_FUNCTION == _ON) || (_PCM_FULL_TIME_FUNCTION == _ON))
            if((bOCCMode == _TRUE) && (g_ppusColorGammaCount[ucGammaIndex][ucRGB] <= 164))
            {
                shRemain = ucLUTLength;
            }
            else
#endif
            {
                shRemain = ucLUTLength * 4;
            }
        }
        ucCurPointer = ucPointer + ucLUTLength - 1;

        while(shRemain > 0)
        {
            if(shRemain > 128)
            {
                shCnt = (bIsLastLUT == _TRUE) ? 124 : 128;
                shRemain -= shCnt;
            }
            else
            {
                shCnt = shRemain;
                shRemain = 0;
            }
            shWriteCnt = shCnt;
            shCnt--;
            while(shCnt > 0)
            {
                usCurrLUT = (g_pucMcuDdcciRxBuf[ucCurPointer - 1] << 8) | g_pucMcuDdcciRxBuf[ucCurPointer];

                if(ucCurPointer == ucPointer + ucLUTLength - 1)
                {
                    if(bIsLastLUT == _TRUE)
                    {
                        pucIntoLUT[shCnt--] = 0;
                        pucIntoLUT[shCnt--] = 0;

                        // Save 1024
                        pucIntoLUT[shCnt--] = usCurrLUT & 0xFF;
                        pucIntoLUT[shCnt--] = usCurrLUT >> 8;
                        ucCurPointer -= 2;
                        continue;
                    }
                    else
                    {
                        usFlashSaveLength = 2;
                        usFlashSaveAddr = (usStartAddr + g_ppusColorGammaCount[ucGammaIndex][ucRGB]);
                        UserCommonColorCalibrationFlashData(_READ, ucColorGammaBankNum, ucGammaIndex, usFlashSaveAddr, usFlashSaveLength, pData);
                        usLastLUT = (pData[0] << 8) | pData[1];
                    }
                }
                else
                {
                    usLastLUT = (g_pucMcuDdcciRxBuf[ucCurPointer + 1] << 8) | g_pucMcuDdcciRxBuf[ucCurPointer + 2];
                }

                if(bIsLastLUT == _TRUE)
                {
                    // Last interpolation: 1020, 1021, 1022; 1023 = 1024
                    pucIntoLUT[shCnt--] = usLastLUT & 0xFF;
                    pucIntoLUT[shCnt--] = (usLastLUT >> 8) & 0x3F;

                    for(ucJ = 1; ucJ < 4; ucJ++)
                    {
                        usInto = usLastLUT - (2 * (DWORD)(usLastLUT - usCurrLUT) * ucJ + 3) / 6;
                        pucIntoLUT[shCnt--] = usInto & 0xFF;
                        pucIntoLUT[shCnt--] = (usInto >> 8);
                    }

                    bIsLastLUT = _FALSE;
                }
                else
                {
#if((_OCC_FUNCTION == _ON) || (_PCM_FULL_TIME_FUNCTION == _ON))
                    if(bOCCMode == _TRUE)
                    {
                        if(g_ppusColorGammaCount[ucGammaIndex][ucRGB] - (shWriteCnt - shCnt - 1) <= 164) // Latch: No Intopolation
                        {
                            bWriteDirectly = _TRUE;

                            if(shWriteCnt > (shCnt + 1))
                            {
                                usFlashSaveLength = (shWriteCnt - (shCnt + 1));
                                usFlashSaveAddr = (usStartAddr + g_ppusColorGammaCount[ucGammaIndex][ucRGB] - usFlashSaveLength);
                                UserCommonColorCalibrationFlashData(_WRITE, ucColorGammaBankNum, ucGammaIndex, usFlashSaveAddr, usFlashSaveLength, &pucIntoLUT[shCnt + 1]);
                                g_ppusColorGammaCount[ucGammaIndex][ucRGB] -= usFlashSaveLength;
                            }
                            break;
                        }
                        else
                        {
                            for(ucJ = 1; ucJ <= 4; ucJ++)
                            {
                                usInto = usLastLUT - ((usLastLUT - usCurrLUT) * ucJ + 2) / 4;
                                pucIntoLUT[shCnt--] = usInto & 0xFF;
                                pucIntoLUT[shCnt--] = (usInto >> 8) & 0x3F;
                            }
                        }
                    }
                    else
#endif
                    {
                        for(ucJ = 1; ucJ <= 4; ucJ++)
                        {
                            usInto = usLastLUT - ((usLastLUT - usCurrLUT) * ucJ + 2) / 4;
                            pucIntoLUT[shCnt--] = usInto & 0xFF;
                            pucIntoLUT[shCnt--] = usInto >> 8;
                        }
                    }
                }
                ucCurPointer -= 2;
            }

#if((_OCC_FUNCTION == _ON) || (_PCM_FULL_TIME_FUNCTION == _ON))
            if(bWriteDirectly == _TRUE)
            {
                if(g_ppusColorGammaCount[ucGammaIndex][ucRGB] <= 148) // Latch: No Intopolation
                {
                    usFlashSaveLength = ucCurPointer - ucPointer + 1;
                    usFlashSaveAddr = (usStartAddr + g_ppusColorGammaCount[ucGammaIndex][ucRGB] - usFlashSaveLength);
                    UserCommonColorCalibrationFlashData(_WRITE, ucColorGammaBankNum, ucGammaIndex, usFlashSaveAddr, usFlashSaveLength, &g_pucMcuDdcciRxBuf[ucPointer]);
                    g_ppusColorGammaCount[ucGammaIndex][ucRGB] = g_ppusColorGammaCount[ucGammaIndex][ucRGB] - usFlashSaveLength;
                    bWriteDirectly = _FALSE;
                    break;
                }
                else if(g_ppusColorGammaCount[ucGammaIndex][ucRGB] <= 164) // add 16 0s
                {
                    memset(pData, 0, 16);
                    usFlashSaveLength = 16;
                    usFlashSaveAddr = (usStartAddr + g_ppusColorGammaCount[ucGammaIndex][ucRGB] - usFlashSaveLength);
                    UserCommonColorCalibrationFlashData(_WRITE, ucColorGammaBankNum, ucGammaIndex, usFlashSaveAddr, usFlashSaveLength, pData);
                    g_ppusColorGammaCount[ucGammaIndex][ucRGB] = 148;

                    usFlashSaveLength = ucCurPointer - ucPointer + 1;
                    usFlashSaveAddr = (usStartAddr + g_ppusColorGammaCount[ucGammaIndex][ucRGB] - usFlashSaveLength);
                    UserCommonColorCalibrationFlashData(_WRITE, ucColorGammaBankNum, ucGammaIndex, usFlashSaveAddr, usFlashSaveLength, &g_pucMcuDdcciRxBuf[ucPointer]);
                    g_ppusColorGammaCount[ucGammaIndex][ucRGB] = g_ppusColorGammaCount[ucGammaIndex][ucRGB] - usFlashSaveLength;
                    bWriteDirectly = _FALSE;
                    break;
                }
                bWriteDirectly = _FALSE;
            }
            else
#endif
            {
                usFlashSaveLength = shWriteCnt;
                usFlashSaveAddr = (usStartAddr + g_ppusColorGammaCount[ucGammaIndex][ucRGB] - usFlashSaveLength);
                UserCommonColorCalibrationFlashData(_WRITE, ucColorGammaBankNum, ucGammaIndex, usFlashSaveAddr, usFlashSaveLength, pucIntoLUT);
                g_ppusColorGammaCount[ucGammaIndex][ucRGB] -= shWriteCnt;
            }
        }
        ucPointer += ucLUTLength;
#else
        shRemain = ucLUTLength;
        ucCurPointer = ucPointer + ucLUTLength - 1;

        while(shRemain > 0)
        {
            if(shRemain > 128)
            {
                shCnt = 128;
                shRemain -= shCnt;
            }
            else
            {
                shCnt = shRemain;
                shRemain = 0;
            }
            shWriteCnt = shCnt;
            shCnt--;
            while(shCnt > 0)
            {
                usCurrLUT = (g_pucMcuDdcciRxBuf[ucCurPointer - 1] << 8) | g_pucMcuDdcciRxBuf[ucCurPointer];

                pucIntoLUT[shCnt--] = usCurrLUT & 0xFF;
                pucIntoLUT[shCnt--] = usCurrLUT >> 8;
                ucCurPointer -= 2;

#if((_OCC_FUNCTION == _ON) || (_PCM_FULL_TIME_FUNCTION == _ON))
                if(bOCCMode == _TRUE)
                {
                    if(g_ppusColorGammaCount[ucGammaIndex][ucRGB] - (shWriteCnt - shCnt - 1) == 164) // Latch: No Intopolation
                    {

                        if((shWriteCnt - shCnt - 1) != 0)
                        {
                            usFlashSaveLength = (shWriteCnt - shCnt - 1);
                            usFlashSaveAddr = (usStartAddr + g_ppusColorGammaCount[ucGammaIndex][ucRGB] - usFlashSaveLength);
                            UserCommonColorCalibrationFlashData(_WRITE, ucColorGammaBankNum, ucGammaIndex, usFlashSaveAddr, usFlashSaveLength, (pucIntoLUT + shCnt + 1));
                            g_ppusColorGammaCount[ucGammaIndex][ucRGB] -= shWriteCnt - shCnt - 1;
                        }

                        memset(pData, 0, 16);
                        usFlashSaveLength = 16;
                        usFlashSaveAddr = (usStartAddr + g_ppusColorGammaCount[ucGammaIndex][ucRGB] - usFlashSaveLength);
                        UserCommonColorCalibrationFlashData(_WRITE, ucColorGammaBankNum, ucGammaIndex, usFlashSaveAddr, usFlashSaveLength, pData);
                        g_ppusColorGammaCount[ucGammaIndex][ucRGB] = 148;

                        shCnt++;
                        shWriteCnt = shCnt;
                        shCnt--;

                        continue;
                    }
                }
#endif
            }
            usFlashSaveLength = shWriteCnt;
            usFlashSaveAddr = (usStartAddr + g_ppusColorGammaCount[ucGammaIndex][ucRGB] - usFlashSaveLength);
            UserCommonColorCalibrationFlashData(_WRITE, ucColorGammaBankNum, ucGammaIndex, usFlashSaveAddr, usFlashSaveLength, pucIntoLUT);
            g_ppusColorGammaCount[ucGammaIndex][ucRGB] -= shWriteCnt;
        }
        ucPointer += ucLUTLength;
#endif
    }
}

#if(_OCC_RGB_3D_GAMMA_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Save LUT Data from DDCCI Rx for 3D Gamma OG Calibration
// Input Value  : nAddress: address in DISP_CALIBRATION_FLASH;
//                nLength: Data Length
//                ucBuffer: pointer of databuffer
// Output Value : None
//--------------------------------------------------
void UserCommonColorCalibrationSave3DGammaOGCLUT(BYTE ucTotalLength)
{
    BYTE ucLUTLength = 0;
    BYTE ucPointer = 7;
    BYTE ucGammaIndex = 0;
    BYTE ucRGB = 0;
    WORD usStartAddr = 0;
    WORD usCurrLUT = 0;
    BYTE pucIntoLUT[128] = {0};
    SWORD shRemain = 0;
    SWORD shCnt = 0;
    BYTE ucCurPointer = 0;
    SWORD shWriteCnt = 0;
#if(_OGC_NO_INTERPOLATION_SUPPORT == _OFF)
    WORD usLastLUT = 0;
    BYTE ucJ = 0;
    WORD usInto = 0;
    bit bIsLastLUT = _FALSE;
#if(_PCM_FULL_TIME_FUNCTION == _ON)
    bit bWriteDirectly = _FALSE;
#endif
#endif
    BYTE ucColorGammaBankNum = 0;
    BYTE *pucColorGammaBankAddr = _NULL_POINTER;
    WORD usFlashSaveAddr = 0;
    WORD usFlashSaveLength = 0;
#if(_PCM_FULL_TIME_FUNCTION == _ON)
    bit bOCCMode = _FALSE;
#endif

    // ucTotalLength - 1: exclude checksum
    while(ucPointer < (ucTotalLength - 1))
    {
        // LUT Length (exclude ID and Length Bytes)
        ucLUTLength = g_pucMcuDdcciRxBuf[ucPointer] - 2;

        ucGammaIndex = (g_pucMcuDdcciRxBuf[ucPointer + 1] >> 4) & 0x0F;
        ucRGB = g_pucMcuDdcciRxBuf[ucPointer + 1] & 0x0F;
        ucPointer += 2;

        if(ucGammaIndex >= (sizeof(g_ppusColor3DGammaCount) / sizeof(g_ppusColor3DGammaCount[0])))
        {
            return;
        }

        ucColorGammaBankNum = UserCommonColorGet3DGammaOGCTableBank();
        pucColorGammaBankAddr = UserCommonColorGet3DGammaOGCTableAddress(ucGammaIndex);

#if(_PCM_FULL_TIME_FUNCTION == _ON)
        bOCCMode = _TRUE;
#endif

        if(ucGammaIndex == _3DGAMMA_END_POSITION)
        {
            return;
        }

        usStartAddr = (DWORD)pucColorGammaBankAddr + (ucRGB) * _OGC_GAMMA_TABLE_LENGTH;

#if(_OGC_NO_INTERPOLATION_SUPPORT == _OFF)
        bIsLastLUT = _FALSE;
        if(g_ppusColor3DGammaCount[ucGammaIndex][ucRGB] == _OGC_GAMMA_TABLE_LENGTH)
        {
            bIsLastLUT = _TRUE;
        }
        if(bIsLastLUT == _TRUE)
        {
            shRemain = (ucLUTLength - 2) * 4 + 4;
        }
        else
        {
#if(_PCM_FULL_TIME_FUNCTION == _ON)
            if((bOCCMode == _TRUE) && (g_ppusColor3DGammaCount[ucGammaIndex][ucRGB] <= 164))
            {
                shRemain = ucLUTLength;
            }
            else
#endif
            {
                shRemain = ucLUTLength * 4;
            }
        }
        ucCurPointer = ucPointer + ucLUTLength - 1;

        while(shRemain > 0)
        {
            if(shRemain > 128)
            {
                shCnt = (bIsLastLUT == _TRUE) ? 124 : 128;
                shRemain -= shCnt;
            }
            else
            {
                shCnt = shRemain;
                shRemain = 0;
            }
            shWriteCnt = shCnt;
            shCnt--;
            while(shCnt > 0)
            {
                usCurrLUT = (g_pucMcuDdcciRxBuf[ucCurPointer - 1] << 8) | g_pucMcuDdcciRxBuf[ucCurPointer];

                if(ucCurPointer == ucPointer + ucLUTLength - 1)
                {
                    if(bIsLastLUT == _TRUE)
                    {
                        if(shCnt < 3)
                        {
                            break;
                        }
                        pucIntoLUT[shCnt--] = 0;
                        pucIntoLUT[shCnt--] = 0;

                        // Save 1024
                        pucIntoLUT[shCnt--] = usCurrLUT & 0xFF;
                        pucIntoLUT[shCnt--] = usCurrLUT >> 8;
                        ucCurPointer -= 2;
                        continue;
                    }
                    else
                    {
                        usFlashSaveLength = 2;
                        usFlashSaveAddr = (usStartAddr + g_ppusColor3DGammaCount[ucGammaIndex][ucRGB]);
                        UserCommonFlashRead(ucColorGammaBankNum, usFlashSaveAddr, usFlashSaveLength, pData);
                        usLastLUT = (pData[0] << 8) | pData[1];
                    }
                }
                else
                {
                    usLastLUT = (g_pucMcuDdcciRxBuf[ucCurPointer + 1] << 8) | g_pucMcuDdcciRxBuf[ucCurPointer + 2];
                }

                if(bIsLastLUT == _TRUE)
                {
                    if(shCnt < 7)
                    {
                        break;
                    }
                    // Last interpolation: 1020, 1021, 1022; 1023 = 1024
                    pucIntoLUT[shCnt--] = usLastLUT & 0xFF;
                    pucIntoLUT[shCnt--] = (usLastLUT >> 8) & 0x3F;

                    for(ucJ = 1; ucJ < 4; ucJ++)
                    {
                        usInto = usLastLUT - (2 * (DWORD)(usLastLUT - usCurrLUT) * ucJ + 3) / 6;
                        pucIntoLUT[shCnt--] = usInto & 0xFF;
                        pucIntoLUT[shCnt--] = (usInto >> 8);
                    }

                    bIsLastLUT = _FALSE;
                }
                else
                {
#if(_PCM_FULL_TIME_FUNCTION == _ON)
                    if(bOCCMode == _TRUE)
                    {
                        if(g_ppusColor3DGammaCount[ucGammaIndex][ucRGB] - (shWriteCnt - shCnt - 1) <= 164) // Latch: No interpolation
                        {
                            bWriteDirectly = _TRUE;

                            if(shWriteCnt > (shCnt + 1))
                            {
                                usFlashSaveLength = (shWriteCnt - (shCnt + 1));
                                usFlashSaveAddr = (usStartAddr + g_ppusColor3DGammaCount[ucGammaIndex][ucRGB] - usFlashSaveLength);
                                UserCommonColorCalibrationFlashData(_WRITE, ucColorGammaBankNum, ucGammaIndex, usFlashSaveAddr, usFlashSaveLength, &pucIntoLUT[shCnt + 1]);
                                g_ppusColor3DGammaCount[ucGammaIndex][ucRGB] -= usFlashSaveLength;
                            }
                            break;
                        }
                        else
                        {
                            if(shCnt < 7)
                            {
                                break;
                            }
                            for(ucJ = 1; ucJ <= 4; ucJ++)
                            {
                                usInto = usLastLUT - ((usLastLUT - usCurrLUT) * ucJ + 2) / 4;
                                pucIntoLUT[shCnt--] = usInto & 0xFF;
                                pucIntoLUT[shCnt--] = (usInto >> 8) & 0x3F;
                            }
                        }
                    }
                    else
#endif
                    {
                        if(shCnt < 7)
                        {
                            break;
                        }
                        for(ucJ = 1; ucJ <= 4; ucJ++)
                        {
                            usInto = usLastLUT - ((usLastLUT - usCurrLUT) * ucJ + 2) / 4;
                            pucIntoLUT[shCnt--] = usInto & 0xFF;
                            pucIntoLUT[shCnt--] = usInto >> 8;
                        }
                    }
                }
                ucCurPointer -= 2;
            }

#if(_PCM_FULL_TIME_FUNCTION == _ON)
            if(bWriteDirectly == _TRUE)
            {
                if(g_ppusColor3DGammaCount[ucGammaIndex][ucRGB] <= 148) // Latch: No interpolation
                {
                    usFlashSaveLength = ucCurPointer - ucPointer + 1;
                    usFlashSaveAddr = (usStartAddr + g_ppusColor3DGammaCount[ucGammaIndex][ucRGB] - usFlashSaveLength);
                    UserCommonColorCalibrationFlashData(_WRITE, ucColorGammaBankNum, ucGammaIndex, usFlashSaveAddr, usFlashSaveLength, &g_pucMcuDdcciRxBuf[ucPointer]);
                    g_ppusColor3DGammaCount[ucGammaIndex][ucRGB] = g_ppusColor3DGammaCount[ucGammaIndex][ucRGB] - usFlashSaveLength;
                    bWriteDirectly = _FALSE;
                    break;
                }
                else if(g_ppusColor3DGammaCount[ucGammaIndex][ucRGB] <= 164) // add 16 0s
                {
                    memset(pData, 0, 16);
                    usFlashSaveLength = 16;
                    usFlashSaveAddr = (usStartAddr + g_ppusColor3DGammaCount[ucGammaIndex][ucRGB] - usFlashSaveLength);
                    UserCommonColorCalibrationFlashData(_WRITE, ucColorGammaBankNum, ucGammaIndex, usFlashSaveAddr, usFlashSaveLength, pData);
                    g_ppusColor3DGammaCount[ucGammaIndex][ucRGB] = 148;

                    usFlashSaveLength = ucCurPointer - ucPointer + 1;
                    usFlashSaveAddr = (usStartAddr + g_ppusColor3DGammaCount[ucGammaIndex][ucRGB] - usFlashSaveLength);
                    UserCommonColorCalibrationFlashData(_WRITE, ucColorGammaBankNum, ucGammaIndex, usFlashSaveAddr, usFlashSaveLength, &g_pucMcuDdcciRxBuf[ucPointer]);
                    g_ppusColor3DGammaCount[ucGammaIndex][ucRGB] = g_ppusColor3DGammaCount[ucGammaIndex][ucRGB] - usFlashSaveLength;
                    bWriteDirectly = _FALSE;
                    break;
                }
                bWriteDirectly = _FALSE;
            }
            else
#endif
            {
                usFlashSaveLength = (shWriteCnt < 0) ? 0 : shWriteCnt;
                usFlashSaveAddr = (usStartAddr + g_ppusColor3DGammaCount[ucGammaIndex][ucRGB] - usFlashSaveLength);
                UserCommonFlashWrite(ucColorGammaBankNum, usFlashSaveAddr, usFlashSaveLength, pucIntoLUT);
                g_ppusColor3DGammaCount[ucGammaIndex][ucRGB] -= shWriteCnt;
            }
        }
        ucPointer += ucLUTLength;
#else
        shRemain = ucLUTLength;
        ucCurPointer = ucPointer + ucLUTLength - 1;

        while(shRemain > 0)
        {
            if(shRemain > 128)
            {
                shCnt = 128;
                shRemain -= shCnt;
            }
            else
            {
                shCnt = shRemain;
                shRemain = 0;
            }
            shWriteCnt = shCnt;
            shCnt--;
            while(shCnt > 0)
            {
                if(shCnt < 1)
                {
                    break;
                }
                usCurrLUT = (g_pucMcuDdcciRxBuf[ucCurPointer - 1] << 8) | g_pucMcuDdcciRxBuf[ucCurPointer];
                pucIntoLUT[shCnt--] = usCurrLUT & 0xFF;
                pucIntoLUT[shCnt--] = usCurrLUT >> 8;
                ucCurPointer -= 2;
#if(_PCM_FULL_TIME_FUNCTION == _ON)
                if(bOCCMode == _TRUE)
                {
                    if(g_ppusColor3DGammaCount[ucGammaIndex][ucRGB] - (shWriteCnt - shCnt - 1) == 164) // Latch: No interpolation
                    {
                        if((shWriteCnt - shCnt - 1) != 0)
                        {
                            usFlashSaveLength = (shWriteCnt - shCnt - 1);
                            usFlashSaveAddr = (usStartAddr + g_ppusColor3DGammaCount[ucGammaIndex][ucRGB] - usFlashSaveLength);
                            UserCommonColorCalibrationFlashData(_WRITE, ucColorGammaBankNum, ucGammaIndex, usFlashSaveAddr, usFlashSaveLength, (pucIntoLUT + shCnt + 1));
                            g_ppusColor3DGammaCount[ucGammaIndex][ucRGB] -= shWriteCnt - shCnt - 1;
                        }

                        memset(pData, 0, 16);
                        usFlashSaveLength = 16;
                        usFlashSaveAddr = (usStartAddr + g_ppusColor3DGammaCount[ucGammaIndex][ucRGB] - usFlashSaveLength);
                        UserCommonColorCalibrationFlashData(_WRITE, ucColorGammaBankNum, ucGammaIndex, usFlashSaveAddr, usFlashSaveLength, pData);
                        g_ppusColor3DGammaCount[ucGammaIndex][ucRGB] = 148;

                        shCnt++;
                        shWriteCnt = shCnt;
                        shCnt--;
                        continue;
                    }
                }
#endif
            }
            usFlashSaveLength = (shWriteCnt < 0) ? 0 : shWriteCnt;
            usFlashSaveAddr = (usStartAddr + g_ppusColor3DGammaCount[ucGammaIndex][ucRGB] - usFlashSaveLength);
            UserCommonFlashWrite(ucColorGammaBankNum, usFlashSaveAddr, usFlashSaveLength, pucIntoLUT);
            g_ppusColor3DGammaCount[ucGammaIndex][ucRGB] -= shWriteCnt;
        }
        ucPointer += ucLUTLength;
#endif
    }
}
#endif

//--------------------------------------------------
// Description  : Calculate the checksum of data in Flash
// Input Value  : ucCheckType: 0- OGC, 1-OCC, 2-DICOM, 3-RGB gain, other- color Matrix,
// Output Value : Checksum
//--------------------------------------------------
BYTE UserCommonColorCalibrationCalCheckSum(BYTE ucCheckType)
{
    WORD usI = 0;
    WORD usJ = 0;
    BYTE ucColorGammaBankNum = 0;
    BYTE *pucColorGammaBankAddr = _NULL_POINTER;
    BYTE ucCheckSum = 0;
    bit bOGCTable = _FALSE;
#if(_PCM_FULL_TIME_FUNCTION == _ON)
    bOGCTable = _TRUE;
#endif

    pData[0] = 0;
    usJ = usJ; // uncall

    switch(ucCheckType)
    {
        case _OGC_TYPE:

            for(DWORD ulGammaIndex = 0; ulGammaIndex < _OGC_TOTAL_GAMMA; ++ulGammaIndex)
            {
                ucColorGammaBankNum = UserCommonColorGetOGCBank((EnumOGCTypeSelect)(_OGC_GAMMA1_TYPE + ulGammaIndex), _OGC_NORMAL_TYPE);
                pucColorGammaBankAddr = UserCommonColorGetOGCAddr((EnumOGCTypeSelect)(_OGC_GAMMA1_TYPE + ulGammaIndex), _OGC_NORMAL_TYPE);

                ucCheckSum += UserCommonColorCalibrationCalGammaCheckSum(ucColorGammaBankNum, (DWORD)pucColorGammaBankAddr, bOGCTable);
            }

            return ucCheckSum;

        case _OGC_MAX_BRI_TYPE:

            for(DWORD ulGammaIndex = 0; ulGammaIndex < _OGC_TOTAL_GAMMA; ++ulGammaIndex)
            {
                ucColorGammaBankNum = UserCommonColorGetOGCBank((EnumOGCTypeSelect)(_OGC_GAMMA1_TYPE + ulGammaIndex), _OGC_MAX_BACKLIGHT_TYPE);
                pucColorGammaBankAddr = UserCommonColorGetOGCAddr((EnumOGCTypeSelect)(_OGC_GAMMA1_TYPE + ulGammaIndex), _OGC_MAX_BACKLIGHT_TYPE);

                ucCheckSum += UserCommonColorCalibrationCalGammaCheckSum(ucColorGammaBankNum, (DWORD)pucColorGammaBankAddr, bOGCTable);
            }

            return ucCheckSum;

        case _OCC_TYPE:

            pData[0] = UserCommonColorCalibrationCalGammaCheckSum(_OCC_GAMMA_FLASH_BANK, ((((WORD)_OGC_FLASH_PAGE) << 12) + _OCC_GAMMA10_ADDRESS), _TRUE);

            break;

        case _OCC_HDR_TYPE:

            pData[0] = UserCommonColorCalibrationCalGammaCheckSum(_OCC_GAMMA_FLASH_BANK, ((((WORD)_OGC_FLASH_PAGE) << 12) + _OCC_HDR10_GAMMA10_ADDRESS), _TRUE);

            break;

#if(_OGC_DICOM_FUNCTION == _ON)
        case _DICOM_TYPE:

            for(DWORD ulDicomIndex = 0; ulDicomIndex < _OGC_TOTAL_DICOM; ++ulDicomIndex)
            {
                ucColorGammaBankNum = UserCommonColorGetDICOMBank((EnumDICOMTypeSelect)(_DICOM1_TYPE + ulDicomIndex));
                pucColorGammaBankAddr = UserCommonColorGetDICOMAddr((EnumDICOMTypeSelect)(_DICOM1_TYPE + ulDicomIndex));

                ucCheckSum += UserCommonColorCalibrationCalGammaCheckSum(ucColorGammaBankNum, (DWORD)pucColorGammaBankAddr, bOGCTable);
            }

            return ucCheckSum;
#endif

        case _RGB_GAIN_TYPE:

            for(usI = _OGC_RGB_GAIN_ADDRESS; usI < (_OGC_RGB_GAIN_ADDRESS + _OGC_RGB_GAIN_ACTUAL_SIZE); usI++)
            {
                UserCommonFlashRead(_OGC_FLASH_BANK, ((((WORD)_OGC_FLASH_PAGE) << 12) + usI), 1, pData + 2);

                pData[0] += pData[2];
            }

            break;

        case _RGB_GAIN_MAX_BRI_TYPE:

            for(usI = _OGC_RGB_GAIN_MAX_BRI_ADDRESS; usI < (_OGC_RGB_GAIN_MAX_BRI_ADDRESS + _OGC_RGB_GAIN_ACTUAL_SIZE); usI++)
            {
                UserCommonFlashRead(_OGC_FLASH_BANK, ((((WORD)_OGC_FLASH_PAGE) << 12) + usI), 1, pData + 2);

                pData[0] += pData[2];
            }

            break;

#if(_TWO_BRI_CALIBRATION_TYPE >= _MULTI_BRI_CALIBRATION_OGC_OCC)
#if(_MULTI_BRI_CALIBRATION_TYPE >= _MULTI_BRI_THREE_CALIBRATION)
        case _RGB_GAIN_MULTI_BRI_3_TYPE:

            for(usI = _OGC_RGB_GAIN_MULTI_BRI_3_CAL_ADDRESS; usI < (_OGC_RGB_GAIN_MULTI_BRI_3_CAL_ADDRESS + _OGC_RGB_GAIN_ACTUAL_SIZE); usI++)
            {
                UserCommonFlashRead(_OGC_FLASH_BANK, ((((WORD)_OGC_FLASH_PAGE) << 12) + usI), 1, pData + 2);

                pData[0] += pData[2];
            }

            break;

#if(_MULTI_BRI_CALIBRATION_TYPE >= _MULTI_BRI_FOUR_CALIBRATION)
        case _RGB_GAIN_MULTI_BRI_4_TYPE:

            for(usI = _OGC_RGB_GAIN_MULTI_BRI_4_CAL_ADDRESS; usI < (_OGC_RGB_GAIN_MULTI_BRI_4_CAL_ADDRESS + _OGC_RGB_GAIN_ACTUAL_SIZE); usI++)
            {
                UserCommonFlashRead(_OGC_FLASH_BANK, ((((WORD)_OGC_FLASH_PAGE) << 12) + usI), 1, pData + 2);

                pData[0] += pData[2];
            }

            break;
#endif
#endif
#endif

        case _HEADER_TYPE:

            //==========Calculate OGC Header============
            for(usI = _OGC_HEADER_ADDRESS + 3; usI < _OCC_HEADER_ADDRESS; usI++)
            {
                UserCommonFlashRead(_OGC_FLASH_BANK, ((((WORD)_OGC_FLASH_PAGE) << 12) + usI), 1, pData + 2);

                pData[0] += pData[2];
            }
            //==========Calculate OCC Header============
            for(usI = _OCC_HEADER_ADDRESS + 3; usI < _DICOM_HEADER_ADDRESS; usI++)
            {
                UserCommonFlashRead(_OGC_FLASH_BANK, ((((WORD)_OGC_FLASH_PAGE) << 12) + usI), 1, pData + 2);

                pData[0] += pData[2];
            }
            //==========Calculate DICOM Header============
            for(usI = _DICOM_HEADER_ADDRESS + 3; usI < _WHITE_LV_HEADER_ADDRESS; usI++)
            {
                UserCommonFlashRead(_OGC_FLASH_BANK, ((((WORD)_OGC_FLASH_PAGE) << 12) + usI), 1, pData + 2);

                pData[0] += pData[2];
            }
            //==========Calculate White Lv Header============
            for(usI = _WHITE_LV_HEADER_ADDRESS + 3; usI < (_WHITE_LV_HEADER_ADDRESS + _WHITE_LV_HEADER_LENGTH); usI++)
            {
                UserCommonFlashRead(_OGC_FLASH_BANK, ((((WORD)_OGC_FLASH_PAGE) << 12) + usI), 1, pData + 2);

                pData[0] += pData[2];
            }

            break;

        case _COLOR_MATRIX_TYPE:

            for(usI = _OCC_SRGBMATRIX_ADDRESS; usI < (_OCC_SRGBMATRIX_ADDRESS + _OCC_COLORMATRIX_TABLE_SIZE * (_PCM_USER_DEFINE_2)); usI++)
            {
                UserCommonFlashRead(_OGC_FLASH_BANK, ((((WORD)_OGC_FLASH_PAGE) << 12) + usI), 1, pData + 2);
                pData[0] += pData[2];
            }

            break;

        case _COLOR_MATRIX_TYPE2:

            for(usI = (_OCC_SRGBMATRIX_ADDRESS + _OCC_COLORMATRIX_TABLE_SIZE * (_PCM_USER_DEFINE_2)); usI < (_OCC_SRGBMATRIX_ADDRESS + _OCC_COLORMATRIX_TABLE_SIZE * (_PCM_USER_DEFINE_2 + g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_COLORMATRIX2_NUM])); usI++)
            {
                UserCommonFlashRead(_OGC_FLASH_BANK, ((((WORD)_OGC_FLASH_PAGE) << 12) + usI), 1, pData + 2);
                pData[0] += pData[2];
            }

            break;

        case _COLOR_MATRIX_MAX_BRI_TYPE:

            for(usI = _OCC_SRGBMATRIX_MAX_BRI_ADDRESS; usI < (_OCC_SRGBMATRIX_MAX_BRI_ADDRESS + _OCC_COLORMATRIX_TABLE_SIZE * (_PCM_USER_DEFINE_2)); usI++)
            {
                UserCommonFlashRead(_OGC_FLASH_BANK, ((((WORD)_OGC_FLASH_PAGE) << 12) + usI), 1, pData + 2);
                pData[0] += pData[2];
            }

            break;

        case _COLOR_MATRIX_MAX_BRI_TYPE2:

            for(usI = (_OCC_SRGBMATRIX_MAX_BRI_ADDRESS + _OCC_COLORMATRIX_TABLE_SIZE * (_PCM_USER_DEFINE_2)); usI < (_OCC_SRGBMATRIX_MAX_BRI_ADDRESS + _OCC_COLORMATRIX_TABLE_SIZE * (_PCM_USER_DEFINE_2 + g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_COLORMATRIX2_NUM])); usI++)
            {
                UserCommonFlashRead(_OGC_FLASH_BANK, ((((WORD)_OGC_FLASH_PAGE) << 12) + usI), 1, pData + 2);
                pData[0] += pData[2];
            }

            break;

#if(_MULTI_BRI_CALIBRATION_TYPE >= _MULTI_BRI_THREE_CALIBRATION)
        case _COLOR_MATRIX_MULTI_BRI_3_TYPE:

            for(usI = _OCC_SRGBMATRIX_MULTI_BRI_3_ADDRESS; usI < (_OCC_SRGBMATRIX_MULTI_BRI_3_ADDRESS + _OCC_COLORMATRIX_TABLE_SIZE * (_PCM_USER_DEFINE_2)); usI++)
            {
                UserCommonFlashRead(_OGC_FLASH_BANK, ((((WORD)_OGC_FLASH_PAGE) << 12) + usI), 1, pData + 2);
                pData[0] += pData[2];
            }

            break;

        case _COLOR_MATRIX_MULTI_BRI_3_TYPE2:

            for(usI = (_OCC_SRGBMATRIX_MULTI_BRI_3_ADDRESS + _OCC_COLORMATRIX_TABLE_SIZE * (_PCM_USER_DEFINE_2)); usI < (_OCC_SRGBMATRIX_MULTI_BRI_3_ADDRESS + _OCC_COLORMATRIX_TABLE_SIZE * (_PCM_USER_DEFINE_2 + g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_COLORMATRIX2_NUM])); usI++)
            {
                UserCommonFlashRead(_OGC_FLASH_BANK, ((((WORD)_OGC_FLASH_PAGE) << 12) + usI), 1, pData + 2);
                pData[0] += pData[2];
            }

            break;

#if(_MULTI_BRI_CALIBRATION_TYPE >= _MULTI_BRI_FOUR_CALIBRATION)
        case _COLOR_MATRIX_MULTI_BRI_4_TYPE:

            for(usI = _OCC_SRGBMATRIX_MULTI_BRI_4_ADDRESS; usI < (_OCC_SRGBMATRIX_MULTI_BRI_4_ADDRESS + _OCC_COLORMATRIX_TABLE_SIZE * (_PCM_USER_DEFINE_2)); usI++)
            {
                UserCommonFlashRead(_OGC_FLASH_BANK, ((((WORD)_OGC_FLASH_PAGE) << 12) + usI), 1, pData + 2);
                pData[0] += pData[2];
            }

            break;

        case _COLOR_MATRIX_MULTI_BRI_4_TYPE2:

            for(usI = (_OCC_SRGBMATRIX_MULTI_BRI_4_ADDRESS + _OCC_COLORMATRIX_TABLE_SIZE * (_PCM_USER_DEFINE_2)); usI < (_OCC_SRGBMATRIX_MULTI_BRI_4_ADDRESS + _OCC_COLORMATRIX_TABLE_SIZE * (_PCM_USER_DEFINE_2 + g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_COLORMATRIX2_NUM])); usI++)
            {
                UserCommonFlashRead(_OGC_FLASH_BANK, ((((WORD)_OGC_FLASH_PAGE) << 12) + usI), 1, pData + 2);
                pData[0] += pData[2];
            }

            break;
#endif
#endif

#if(_ADVANCED_HDR10_SUPPORT == _ON)
        case _ADVANCED_HDR10_TYPE:

            for(usJ = 0; usJ < 40; usJ++)
            {
                for(usI = 0; usI < _OGC_HDR10_IG_129_NODE_TABLE_SIZE; usI++)
                {
                    UserCommonFlashRead(_OGC_FLASH_BANK, ((((WORD)_OGC_FLASH_PAGE) << 12) + _OGC_ADVANCED_HDR10_IG_NOTM_DARK_ADDRESS + _OGC_HDR10_IG_129_NODE_TABLE_SIZE * usJ + usI), 1, pData + 2);
                    pData[0] += pData[2];
                }
            }

            break;

#endif

#if(_HDR10_SUPPORT == _ON)
        case _HDR_TYPE:

            for(usI = _OCC_HDR10_SRGB_MATRIX_ADDRESS; usI < (_OCC_HDR10_SRGB_MATRIX_ADDRESS + _OCC_COLORMATRIX_TABLE_SIZE * 4); usI++)
            {
                UserCommonFlashRead(_OGC_FLASH_BANK, ((((WORD)_OGC_FLASH_PAGE) << 12) + usI), 1, pData + 2);
                pData[0] += pData[2];
            }

            for(usJ = 0; usJ < _HDR_TOTAL_IG; usJ++)
            {
#if(_HDR10_FIXED_POINT_TONEMAPPING_SUPPORT == _ON)
                if((tHDR10IGAMMA_INDEX[usJ] >= _OGC_HDR10_IG_540_FIXED_POINT_NOR_ADDRESS) && (tHDR10IGAMMA_INDEX[usJ] < _OGC_HDR10_IG_NOTM_USER_DEF_PEAK_NOR_ADDRESS))
                {
                    for(usI = 0; usI < _OGC_HDR10_IG_129_NODE_TABLE_SIZE; usI++)
                    {
                        UserCommonFlashRead(_OGC_FLASH_BANK, ((((WORD)_OGC_FLASH_PAGE) << 12) + _OGC_HDR10_IG_540_FIXED_POINT_NOR_ADDRESS + _OGC_HDR10_IG_129_NODE_TABLE_SIZE * (usJ - 12) + usI), 1, pData + 2);
                        pData[0] += pData[2];
                    }
                }
                else if(tHDR10IGAMMA_INDEX[usJ] >= _OGC_HDR10_IG_NOTM_USER_DEF_PEAK_NOR_ADDRESS)
                {
                    for(usI = 0; usI < _OGC_HDR10_IG_TABLE_SIZE; usI++)
                    {
                        UserCommonFlashRead(_OGC_FLASH_BANK, ((((WORD)_OGC_FLASH_PAGE) << 12) + _OGC_HDR10_IG_NOTM_USER_DEF_PEAK_NOR_ADDRESS + _OGC_HDR10_IG_TABLE_SIZE * (usJ - 20) + usI), 1, pData + 2);
                        pData[0] += pData[2];
                    }
                }
                else
#endif
                {
                    for(usI = 0; usI < _OGC_HDR10_IG_TABLE_SIZE; usI++)
                    {
                        UserCommonFlashRead(_OGC_FLASH_BANK, ((((WORD)_OGC_FLASH_PAGE) << 12) + _OGC_HDR10_IG_1200_NOR_ADDRESS + _OGC_HDR10_IG_TABLE_SIZE * usJ + usI), 1, pData + 2);
                        pData[0] += pData[2];
                    }
                }
            }
            break;

        case _HDR10_NOTM_BOUND_TYPE:

            for(usI = 0; usI < _NOTM_BOUND_SAVE_LENGTH; usI++)
            {
                UserCommonFlashRead(_OGC_FLASH_BANK, ((((WORD)_OGC_FLASH_PAGE) << 12) + _OGC_HDR10_NOTM_BOUND_ADDRESS + usI), 1, pData + 2);
                pData[0] += pData[2];
            }

            break;

#endif

#if(_BACKLIGHT_DIMMING_SUPPORT == _ON)
        case _DIMMING_OG_TYPE:

            pData[0] = UserCommonColorCalibrationCalGammaCheckSum(_OCC_GAMMA_FLASH_BANK, ((((WORD)_OGC_FLASH_PAGE) << 12) + _DIMMING_OCC_GAMMA10_ADDRESS), _TRUE);

            break;

#if(_OGC_FUNCTION == _ON)
        case _DIMMING_IG_TYPE:

            for(usJ = 0; usJ < _OGC_TOTAL_GAMMA; usJ++)
            {
                for(usI = 0; usI < _OGC_HDR10_IG_TABLE_SIZE; usI++)
                {
                    UserCommonFlashRead(_OGC_FLASH_BANK, ((((WORD)_OGC_FLASH_PAGE) << 12) + _DIMMING_OGC_GAMMA1_ADDRESS + _OGC_HDR10_IG_TABLE_SIZE * usJ + usI), 1, pData + 2);
                    pData[0] += pData[2];
                }
            }

            for(usI = _DIMMING_OGC_RGB_GAIN_ADDRESS; usI < (_DIMMING_OGC_RGB_GAIN_ADDRESS + _OGC_RGB_GAIN_ACTUAL_SIZE); usI++)
            {
                UserCommonFlashRead(_OGC_FLASH_BANK, ((((WORD)_OGC_FLASH_PAGE) << 12) + usI), 1, pData + 2);

                pData[0] += pData[2];
            }

            break;
#endif

#endif

        case _EDID_INFO_TYPE:
            for(usI = 0; usI < 14; usI++)
            {
                UserCommonFlashRead(_OGC_FLASH_BANK, ((((WORD)_OGC_FLASH_PAGE) << 12) + _EDID_INFO_ADDRESS + usI), 1, pData + 2);
                pData[0] += pData[2];
            }
            break;

        case _NOTM_DCR_THD_TYPE:
            for(usI = 0; usI < _NOTM_DCR_THD_LENGTH; usI++)
            {
                UserCommonFlashRead(_OGC_FLASH_BANK, ((((WORD)_OGC_FLASH_PAGE) << 12) + _DIMMING_NOTM_DCR_THD_ADDRESS + usI), 1, pData + 2);
                pData[0] += pData[2];
            }
            break;

#if(_FREESYNC_II_SUPPORT == _ON)
        case _FREESYNC_II_OG_TYPE:

            pData[0] = UserCommonColorCalibrationCalGammaCheckSum(_FREESYNC_II_FLASH_BANK, ((((WORD)_FREESYNC_II_FLASH_PAGE) << 12) + _FREESYNC_II_OCC_GAMMA10_ADDRESS), _TRUE);

            break;

        case _FREESYNC_II_IG_TYPE:
            for(usJ = 0; usJ < 5; usJ++)
            {
                for(usI = 0; usI < _OGC_HDR10_IG_TABLE_SIZE; usI++)
                {
                    UserCommonFlashRead(_FREESYNC_II_FLASH_BANK, ((((WORD)_FREESYNC_II_FLASH_PAGE) << 12) + _FREESYNC_II_IG_SRGB_ADDRESS + _OGC_HDR10_IG_TABLE_SIZE * usJ + usI), 1, pData + 2);
                    pData[0] += pData[2];
                }
            }
            break;

        case _FREESYNC_II_PQ_TYPE:
            for(usI = 0; usI < _OGC_HDR10_IG_TABLE_SIZE; usI++)
            {
                UserCommonFlashRead(_FREESYNC_II_FLASH_BANK, ((((WORD)_FREESYNC_II_FLASH_PAGE) << 12) + _FREESYNC_II_IG_PQ_ADDRESS + usI), 1, pData + 2);
                pData[0] += pData[2];
            }
            break;
#endif

#if(_HLG_SUPPORT == _ON)
        case _HLG_YMAPPING_TYPE:

            for(usI = 0; usI < _YMAPPING_GAIN_TABLE_SIZE; usI++)
            {
                UserCommonFlashRead(_OGC_FLASH_BANK, ((((WORD)_OGC_FLASH_PAGE) << 12) + _OGC_HLG_YM_STANDARD_MODE_ADDRESS + usI), 1, pData + 2);
                pData[0] += pData[2];
            }
            break;
#endif

#if(_HDR10_BACKLIGHT_ADAPTIVE_TM_SUPPORT == _ON)
        case _HDR_BACKLIGHT_ADAPTIVE_TYPE:
            for(usJ = 0; usJ < 8; usJ++)
            {
                for(usI = 0; usI < _OGC_HDR10_IG_129_NODE_TABLE_SIZE; usI++)
                {
                    UserCommonFlashRead(_OGC_FLASH_BANK, ((((WORD)_OGC_FLASH_PAGE) << 12) + _OGC_HDR10_IG_ADAPTIVE_TM_LV1_NOR_ADDRESS + _OGC_HDR10_IG_129_NODE_TABLE_SIZE * usJ + usI), 1, pData + 2);
                    pData[0] += pData[2];
                }
            }

            for(usI = 0; usI < _OGC_HDR10_BACKLIGHT_ADAPTIVE_BOUND_LENGTH; usI++)
            {
                UserCommonFlashRead(_OGC_FLASH_BANK, ((((WORD)_OGC_FLASH_PAGE) << 12) + _OGC_HDR10_BACKLIGHT_ADAPTIVE_BOUND_ADDRESS + usI), 1, pData + 2);
                pData[0] += pData[2];
            }
            break;
#endif

#if(_HDR10_MASTERING_LV_STEPLESS_TM_SUPPORT == _ON)
        case _HDR_MASTERING_LV_STEPLESS_TYPE:
            for(usI = 0; usI < _OGC_HDR10_MASTERING_LV_STEPLESS_BOUND_LENGTH; usI++)
            {
                UserCommonFlashRead(_OGC_FLASH_BANK, ((((WORD)_OGC_FLASH_PAGE) << 12) + _OGC_HDR10_MASTERING_LV_STEPLESS_BOUND_ADDRESS + usI), 1, pData + 2);
                pData[0] += pData[2];
            }
            break;
#endif

#if(_HDR10_USER_DEFINE_FIXED_POINT_TONEMAPPING_SUPPORT == _ON)
        case _HDR_USER_DEFINE_FIXED_POINT_TYPE:
            for(usJ = 0; usJ < 8; usJ++)
            {
                for(usI = 0; usI < _OGC_HDR10_IG_129_NODE_TABLE_SIZE; usI++)
                {
                    UserCommonFlashRead(_OGC_FLASH_BANK, ((((WORD)_OGC_FLASH_PAGE) << 12) + _OGC_HDR10_IG_540_USER_FIXED_NOR_ADDRESS + _OGC_HDR10_IG_129_NODE_TABLE_SIZE * usJ + usI), 1, pData + 2);
                    pData[0] += pData[2];
                }
            }
            break;
#endif

#if(_MULTI_BRI_CALIBRATION_TYPE >= _MULTI_BRI_THREE_CALIBRATION)
        case _OCC_MULTI_BRI_3_TYPE:

            pData[0] = UserCommonColorCalibrationCalGammaCheckSum(_OCC_GAMMA_FLASH_BANK, ((((WORD)_OGC_FLASH_PAGE) << 12) + _OCC_GAMMA10_MULTI_BRI_3_ADDRESS), _TRUE);

            break;

#if(_MULTI_BRI_CALIBRATION_TYPE >= _MULTI_BRI_FOUR_CALIBRATION)
        case _OCC_MULTI_BRI_4_TYPE:

            pData[0] = UserCommonColorCalibrationCalGammaCheckSum(_OCC_GAMMA_FLASH_BANK, ((((WORD)_OGC_FLASH_PAGE) << 12) + _OCC_GAMMA10_MULTI_BRI_4_ADDRESS), _TRUE);

            break;
#endif
#endif
#if(_GLOBAL_DIMMING_ONLINE_CALIBRATION_SUPPORT == _ON)
        case _GD_PWMLUT_TYPE:
            for(usI = 0; usI < _OCC_GLOBAL_DIMMING_PWMLUT_TABLE_SIZE; usI++)
            {
                UserCommonFlashRead(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _OCC_GLOBAL_DIMMING_PWMLUT_ADDRESS + usI, 1, pData + 2);
                pData[0] += pData[2];
            }
            break;
#endif

#if(_SAVE_OGC_OCC_VERIFY_REPORT_SUPPORT == _ON)
        case _OCC_VERIFY_REPORT_TYPE:
            for(usJ = 0; usJ < g_usColorVerifySavePos; usJ++)
            {
                UserCommonFlashRead(_OGC_OCC_VERIFY_REPORT_BANK, usJ, 1, pData + 2);
                pData[0] += pData[2];
            }
            break;
#endif

#if(_OCC_RGB_3D_GAMMA_SUPPORT == _ON)
        case _3D_GAMMA_TYPE:
            ucCheckSum = 0;
            ucColorGammaBankNum = UserCommonColorGet3DGammaOGCTableBank();
            for(usI = 0; usI < g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_3DLUT_CHKSUM + 1]; usI++)
            {
                pucColorGammaBankAddr = UserCommonColorGet3DGammaOGCTableAddress(usI);
                ucCheckSum += UserCommonColorCalibrationCalGammaCheckSum(ucColorGammaBankNum, (DWORD)pucColorGammaBankAddr, bOGCTable);
            }
            return ucCheckSum;
            break;
#endif
        default:
            break;
    }

    return pData[0];
}

//--------------------------------------------------
// Description  : Measure End --> Show Gamma
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonColorCalibrationShowGamma(void)
{
#if((_OGC_FUNCTION == _ON) || (_OGC_DICOM_FUNCTION == _ON))
    BYTE ucColorGammaBankNum = 0;
    BYTE *pucColorGammaBankAddr = _NULL_POINTER;
#endif
#if(_OGC_FUNCTION == _ON)
    BYTE ucGammaIndex = 0;
    BYTE ucColorTempIndex = 0;
    WORD pusBriTemp[3] = {0x200, 0x200, 0x200};
    WORD pusContrastData[3] = {0};
#endif

    ScalerColorOutputGammaEnable(_FUNCTION_OFF);

#if(_OGC_FUNCTION == _ON)
    if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_FINAL_TYPE] == _OGC_CAL_TYPE)
    {
        ucGammaIndex = (g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_OGC_GAMMA_CT_INFO] >> 4) & 0x0F;
        ucColorTempIndex = g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_OGC_GAMMA_CT_INFO] & 0x0F;

#if(_TWO_BRI_CALIBRATION_TYPE >= _TWO_BRI_CALIBRATION_OGC_OCC_DICOM_HDR)
        if(g_ucColorBacklightFlag == _MAX_BACKLIGHT_CAL)
        {
            ucColorGammaBankNum = UserCommonColorGetOGCBank(ucGammaIndex, _OGC_MAX_BACKLIGHT_TYPE);
            pucColorGammaBankAddr = UserCommonColorGetOGCAddr(ucGammaIndex, _OGC_MAX_BACKLIGHT_TYPE);
        }
        else
#endif
        {
            ucColorGammaBankNum = UserCommonColorGetOGCBank(ucGammaIndex, _OGC_NORMAL_TYPE);
            pucColorGammaBankAddr = UserCommonColorGetOGCAddr(ucGammaIndex, _OGC_NORMAL_TYPE);
        }
        UserCommonColorCalibrationSetGammaTable(ucColorGammaBankNum, pucColorGammaBankAddr, _DB_APPLY_POLLING);

#if(_COLOR_IP_BRIGHTNESS == _ON)
        ScalerColorBrightnessAdjust(_1P_NORMAL_REGION, pusBriTemp);
#endif

        if(ucColorTempIndex != 0x0F)
        {
            UserCommonFlashRead(_OGC_FLASH_BANK, ((WORD)_OGC_FLASH_PAGE << 12) | (ucColorTempIndex * _OGC_TOTAL_GAMMA * 6 + ucGammaIndex * 6 + _OGC_RGB_GAIN_ADDRESS), 6, pData);
        }
        else // Native
        {
            pData[0] = 0x08;
            pData[1] = 0x00;
            pData[2] = 0x08;
            pData[3] = 0x00;
            pData[4] = 0x08;
            pData[5] = 0x00;
        }

        // Construct contrast data format
        pusContrastData[0] = TO_WORD(pData[0], pData[1]);
        pusContrastData[1] = TO_WORD(pData[2], pData[3]);
        pusContrastData[2] = TO_WORD(pData[4], pData[5]);

#if(_COLOR_IP_CONTRAST == _ON)
        ScalerColorContrastAdjust(_1P_NORMAL_REGION, pusContrastData);
        ScalerColorContrastEnable(_FUNCTION_ON);
#endif

#if(_COLOR_IP_SRGB == _ON)
        ScalerColorSRGBEnable(_FUNCTION_OFF);
#endif

        UserCommonColorCalibrationPatternEnable(_DISABLE);
    }
#endif  // End of #if(_OGC_SUPPORT == _ON)

#if(_OCC_FUNCTION == _ON)
    if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_FINAL_TYPE] == _OCC_CAL_TYPE)
    {
        ScalerTimerWaitForDDomainEvent(_EVENT_DEN_STOP);
        ScalerColorPCMInputGammaEnable(_FUNCTION_OFF);
        ScalerColorOutputGammaEnable(_FUNCTION_OFF);
#if(_COLOR_IP_SRGB == _ON)
        ScalerColorSRGBEnable(_FUNCTION_OFF);
#endif
        ScalerColorPCMSetPCMMode(_1P_NORMAL_REGION, _PCM_MODE);

#if((_TWO_BRI_CALIBRATION_TYPE == _TWO_BRI_CALIBRATION_DICOM_HDR) && (_HDR10_SUPPORT == _OFF))
        ScalerColorPCMOutputGammaAdjust(_1P_NORMAL_REGION, g_pucColorDISP_CALIBRATION_FLASH + _OCC_GAMMA10_ADDRESS, _OCC_GAMMA_FLASH_BANK);
#else
        if(g_ucColorBacklightFlag == _NORMAL_BACKLIGHT_CAL)
        {
            ScalerColorPCMOutputGammaAdjust(_1P_NORMAL_REGION, g_pucColorDISP_CALIBRATION_FLASH + _OCC_GAMMA10_ADDRESS, _OCC_GAMMA_FLASH_BANK);
        }
#if(_MULTI_BRI_CALIBRATION_TYPE >= _MULTI_BRI_THREE_CALIBRATION)
        else if(g_ucColorBacklightFlag == _MULTI_BACKLIGHT_3_CAL)
        {
            ScalerColorPCMOutputGammaAdjust(_1P_NORMAL_REGION, g_pucColorDISP_CALIBRATION_FLASH + _OCC_GAMMA10_MULTI_BRI_3_ADDRESS, _OCC_GAMMA_FLASH_BANK);
        }
#if(_MULTI_BRI_CALIBRATION_TYPE >= _MULTI_BRI_FOUR_CALIBRATION)
        else if(g_ucColorBacklightFlag == _MULTI_BACKLIGHT_4_CAL)
        {
            ScalerColorPCMOutputGammaAdjust(_1P_NORMAL_REGION, g_pucColorDISP_CALIBRATION_FLASH + _OCC_GAMMA10_MULTI_BRI_4_ADDRESS, _OCC_GAMMA_FLASH_BANK);
        }
#endif
#endif
        else
        {
            ScalerColorPCMOutputGammaAdjust(_1P_NORMAL_REGION, g_pucColorDISP_CALIBRATION_FLASH + _OCC_HDR10_GAMMA10_ADDRESS, _OCC_GAMMA_FLASH_BANK);
        }
#endif
#if(_PCM_FUNCTION == _ON)
        ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _SRGB_0_BIT_SHIFT_LEFT, ScalerColorsRGBBypassGetTableAddress(_SRGB_BYPASS), ScalerColorsRGBBypassGetTableBank(), 18);
#endif

        ScalerTimerWaitForDDomainEvent(_EVENT_DEN_STOP);

        ScalerColorOutputGammaEnable(_FUNCTION_ON);
#if(_COLOR_IP_SRGB == _ON)
        ScalerColorSRGBEnable(_FUNCTION_ON);
#endif
        ScalerColorPCMInputGammaEnable(_FUNCTION_ON);
#if(_COLOR_IP_I_GAMMA == _ON)
        ScalerColorPCMRegionEnable(_1P_NORMAL_REGION, _DB_APPLY_POLLING, _ON);
#endif
#if(_COLOR_IP_BRIGHTNESS == _ON)
        ScalerColorBrightnessEnable(_FUNCTION_OFF);
#endif
#if(_COLOR_IP_CONTRAST == _ON)
        ScalerColorContrastEnable(_FUNCTION_OFF);
#endif

        if(g_ucColorPatternType == _BG_PATTERN)
        {
            ScalerDDomainBackgroundEnable(_DDOMAIN_RGN_ALL, _FALSE);
        }
        UserCommonColorCalibrationShowDDomainPattern(tOCC_SRGB_TABLE[0], tOCC_SRGB_TABLE[1], tOCC_SRGB_TABLE[2], g_ucColorPatternType);
    }
    else
    {
        UserCommonColorCalibrationPatternEnable(_DISABLE);
    }
#endif  // End of #if(_OCC_SUPPORT == _ON)

#if(_OGC_DICOM_FUNCTION == _ON)
    if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_FINAL_TYPE] == _DICOM_CAL_TYPE)
    {
        ucColorGammaBankNum = UserCommonColorGetDICOMBank(_DICOM1_TYPE);
        pucColorGammaBankAddr = UserCommonColorGetDICOMAddr(_DICOM1_TYPE);

        UserCommonColorCalibrationSetGammaTable(ucColorGammaBankNum, pucColorGammaBankAddr, _DB_APPLY_POLLING);

#if(_COLOR_IP_BRIGHTNESS == _ON)
        ScalerColorBrightnessEnable(_FUNCTION_OFF);
#endif
#if(_COLOR_IP_CONTRAST == _ON)
        ScalerColorContrastEnable(_FUNCTION_OFF);
#endif
#if(_COLOR_IP_SRGB == _ON)
        ScalerColorSRGBEnable(_FUNCTION_OFF);
#endif
        UserCommonColorCalibrationPatternEnable(_DISABLE);
    }
#endif  // End of #if(_OGC_DICOM_SUPPORT == _ON)
}

//--------------------------------------------------
// Description  : Display Calibration Measure End CheckSum
// Input Value  : None
// Output Value : _SUCCESS/_FAIL
//--------------------------------------------------
BYTE UserCommonColorCalibrationCheckSum(void)
{
    BYTE ucFlag = 1;
#if(_OCC_RGB_3D_GAMMA_SUPPORT == _ON)
    DWORD ulI_3DLUT = 0;
    BYTE pucTemp_3DLUT[2] = {0, 0};
    BYTE uc3DLUTTableBank = 0;
    WORD us3DLUTTableAddr = 0;
    DWORD ul3DLUTCheckSumAddr = 0;
#endif
#if(_UNIFORMITY_FUNCTION == _ON)
    DWORD ulI = 0;
    BYTE pucTemp[2] = {0, 0};
    BYTE ucGainTableBank = 0;
    WORD usGainTableAddr = 0;
    DWORD ulGainCheckSumAddr = 0;
#if(_UNIFORMITY_LEVEL0_SUPPORT == _ON)
    BYTE ucOffsetTableBank = 0;
    BYTE ucOffsetTableStartBank = 0;
    WORD usOffsetTableAddr = 0;
    WORD usDecayTableAddr = 0;
    WORD usOffsetCheckSumAddr = 0;
    WORD usDecayCheckSumAddr = 0;
#endif
#endif

    if(g_ucColorBacklightFlag == _NORMAL_BACKLIGHT_CAL)
    {
#if(_OGC_FUNCTION == _ON)
        if(((g_ucColorCalibrationType >> _OGC_CAL_TYPE) & 0x01) == _TRUE)
        {
            pData[1] = UserCommonColorCalibrationCalCheckSum(_OGC_TYPE);

            if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_OGC_CHKSUM] == pData[1])
            {
                UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _OGC_CHKSUM_ADDRESS, 1, &pData[1]);
                pData[4] = _OGC_FUNCTION;
                UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _OGC_FINISH_ADDRESS, 1, &pData[4]);
            }
            else
            {
                ucFlag = _BIT1;
            }
        }
#endif  // End of #if(_OGC_SUPPORT == _ON)

#if(_OCC_FUNCTION == _ON)
        if(((g_ucColorCalibrationType >> _OCC_CAL_TYPE) & 0x01) == _TRUE)
        {
            pData[2] = UserCommonColorCalibrationCalCheckSum(_OCC_TYPE);

            if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_OCC_CHKSUM] == pData[2])
            {
                UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _OCC_CHKSUM_ADDRESS, 1, &pData[2]);
                pData[4] = _OCC_FUNCTION;
                UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _OCC_FINISH_ADDRESS, 1, &pData[4]);
            }
            else
            {
                ucFlag |= _BIT2;
            }
        }

#if(_BACKLIGHT_DIMMING_SUPPORT == _ON)
        if(((g_ucColorCalibrationType >> _DIMMING_CAL_TYPE) & 0x01) == _TRUE)
        {
            pData[2] = UserCommonColorCalibrationCalCheckSum(_DIMMING_OG_TYPE);

            if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_LD_OCC_CHKSUM] == pData[2])
            {
                UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _DIMMING_OCC_CHKSUM_ADDRESS, 1, &pData[2]);
            }
            else
            {
                ucFlag |= _BIT2;
            }
        }
#endif
#endif  // End of #if(_OCC_SUPPORT == _ON)

    }

#if(_TWO_BRI_CALIBRATION_TYPE >= _TWO_BRI_CALIBRATION_OGC_OCC_DICOM_HDR)
    if(g_ucColorBacklightFlag == _MAX_BACKLIGHT_CAL)
    {
#if(_OGC_FUNCTION == _ON)
        if(((g_ucColorCalibrationType >> _OGC_CAL_TYPE) & 0x01) == _TRUE)
        {
            pData[1] = UserCommonColorCalibrationCalCheckSum(_OGC_MAX_BRI_TYPE);

            if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_OGC_CHKSUM] == pData[1])
            {
                UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _OGC_MAX_BRI_CHKSUM_ADDRESS, 1, &pData[1]);
            }
            else
            {
                ucFlag |= _BIT1;
            }
        }
#endif  // End of #if(_OGC_SUPPORT == _ON)
    }
#endif

#if(_OGC_DICOM_FUNCTION == _ON)
#if(_TWO_BRI_CALIBRATION_TYPE != _TWO_BRI_CALIBRATION_NONE)
    if(g_ucColorBacklightFlag == _MAX_BACKLIGHT_CAL)
#else
    if(g_ucColorBacklightFlag == _NORMAL_BACKLIGHT_CAL)
#endif
    {
        if(((g_ucColorCalibrationType >> _DICOM_CAL_TYPE) & 0x01) == _TRUE)
        {
            pData[3] = UserCommonColorCalibrationCalCheckSum(_DICOM_TYPE);

            if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_DICOM_CHKSUM] == pData[3])
            {
                UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _OGC_DICOM_CHKSUM_ADDRESS, 1, &pData[3]);
                pData[4] = _OGC_DICOM_FUNCTION;
                UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _OGC_DICOM_FINISH_ADDRESS, 1, &pData[4]);
            }
            else
            {
                ucFlag |= _BIT3;
            }
        }
    }
#endif  // End of #if(_OGC_DICOM_SUPPORT == _ON)


#if(_TWO_BRI_CALIBRATION_TYPE != _TWO_BRI_CALIBRATION_NONE)
#if(_HDR10_SUPPORT == _ON)
    if(g_ucColorBacklightFlag == _MAX_BACKLIGHT_CAL)
    {
        if(((g_ucColorCalibrationType >> _OCC_CAL_TYPE) & 0x01) == _TRUE)
        {
            pData[2] = UserCommonColorCalibrationCalCheckSum(_OCC_HDR_TYPE);

            if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_OCC_CHKSUM] == pData[2])
            {
                UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _OCC_HDR_CHKSUM_ADDRESS, 1, &pData[2]);
            }
            else
            {
                ucFlag |= _BIT2;
            }
        }
    }
#endif  // End of #if(_HDR10_SUPPORT == _ON)
#endif

#if(_FREESYNC_II_SUPPORT == _ON)
#if(_TWO_BRI_CALIBRATION_TYPE != _TWO_BRI_CALIBRATION_NONE)
    if(g_ucColorBacklightFlag == _MAX_BACKLIGHT_CAL)
#else
    if(g_ucColorBacklightFlag == _NORMAL_BACKLIGHT_CAL)
#endif
    {
        if(((g_ucColorCalibrationTypeII >> _FREESYNC_II_CAL_TYPE) & 0x01) == _TRUE)
        {
            pData[2] = UserCommonColorCalibrationCalCheckSum(_FREESYNC_II_OG_TYPE);

            if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_FREESYNC_II_CHKSUM] == pData[2])
            {
                UserCommonFlashWrite(_FREESYNC_II_FLASH_BANK, (((WORD)_FREESYNC_II_FLASH_PAGE) << 12) + _FREESYNC_II_CHKSUM_ADDRESS, 1, &pData[2]);
            }
            else
            {
                ucFlag |= _BIT2;
            }
        }
    }
#endif

#if(_OCC_RGB_3D_GAMMA_SUPPORT == _ON)
    if(((g_ucColor3DLUTChecksumType >> _3D_GAMMA_3D_TYPE)  & 0x01) == _TRUE)
    {
        pucTemp_3DLUT[1] = 0;
        uc3DLUTTableBank = UserCommonColorGetOCC3DGammaTableBank(g_ucColor3DLUTStartPosIndex);
        us3DLUTTableAddr = (DWORD)(UserCommonColorGetOCC3DGammaTableAddress(g_ucColor3DLUTStartPosIndex));
        ul3DLUTCheckSumAddr = us3DLUTTableAddr + _RGB_3D_GAMMA_1TABLE_SIZE;

        for(ulI_3DLUT = us3DLUTTableAddr; ulI_3DLUT < ul3DLUTCheckSumAddr; ulI_3DLUT++)
        {
            UserCommonFlashRead(uc3DLUTTableBank, ulI_3DLUT, 1, &pucTemp_3DLUT[0]);
            pucTemp_3DLUT[1] += pucTemp_3DLUT[0];
        }

        UserCommonFlashWrite(uc3DLUTTableBank, ul3DLUTCheckSumAddr, 1, &pucTemp_3DLUT[1]);
        UserCommonFlashRead(uc3DLUTTableBank, ul3DLUTCheckSumAddr, 1, &pData[5]);

        if((g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_3DLUT_CHKSUM] == pData[5]) &&
           (pucTemp_3DLUT[1] == pData[5]))
        {
            pData[4] = _OCC_RGB_3D_GAMMA_SUPPORT;
            UserCommonFlashWrite(_OCC_RGB_3D_GAMMA_FLASH_BANK0, (_RGB_3D_GAMMA_FINISH_ADDRESS + g_ucColor3DLUTStartPosIndex), 1, &pData[4]);
        }
        else
        {
            ucFlag |= _BIT4;
        }
    }

    if(((g_ucColor3DLUTChecksumType >> _3D_GAMMA_OG_TYPE)  & 0x01) == _TRUE)
    {
        uc3DLUTTableBank = UserCommonColorGet3DGammaOGCTableBank();
        pucTemp_3DLUT[1] = UserCommonColorCalibrationCalCheckSum(_3D_GAMMA_TYPE);
        UserCommonFlashWrite(uc3DLUTTableBank, _OGC_CHKSUM_ADDRESS, 1, &pucTemp_3DLUT[1]);
        if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_3DLUT_CHKSUM] == pucTemp_3DLUT[1])
        {
            pData[4] = _OCC_RGB_3D_GAMMA_SUPPORT;
            UserCommonFlashWrite(uc3DLUTTableBank, _OGC_FINISH_ADDRESS, 1, &pData[4]);
        }
        else
        {
            ucFlag |= _BIT4;
        }
    }
#endif

#if(_UNIFORMITY_FUNCTION == _ON)
    if(((g_ucColorUniformityChecksumType >> _UNIFORMITY_GAIN_TYPE) & 0x01) == _TRUE)
    {
        // level0
        pucTemp[1] = 0;
        ucGainTableBank = UserCommonColorGetPanelUniformityGainBank(g_ucColorUniformityLUTStartPosIndex);
        usGainTableAddr = UserCommonColorGetPanelUniformityGainAddr(g_ucColorUniformityLUTStartPosIndex);

        ulGainCheckSumAddr = usGainTableAddr + _PANEL_UNIFORMITY_1LEVEL_SIZE * UserCommonColorGetUniformityType(g_ucColorUniformityLUTStartPosIndex);

        for(ulI = usGainTableAddr; ulI < ulGainCheckSumAddr; ulI++)
        {
            if(ulI > 65535)
            {
                UserCommonFlashRead(g_ucColorUniformityLUTSaveBank, ulI - 65536, 1, &pucTemp[0]);
            }
            else
            {
                UserCommonFlashRead(ucGainTableBank, ulI, 1, &pucTemp[0]);
            }
            pucTemp[1] += pucTemp[0];
        }

        if(ulGainCheckSumAddr > 65535)
        {
            UserCommonFlashWrite(g_ucColorUniformityLUTSaveBank, ulGainCheckSumAddr - 65536, 1, &pucTemp[1]);
            UserCommonFlashRead(g_ucColorUniformityLUTSaveBank, ulGainCheckSumAddr - 65536, 1, &pData[5]);
        }
        else
        {
            UserCommonFlashWrite(g_ucColorUniformityLUTSaveBank, ulGainCheckSumAddr, 1, &pucTemp[1]);
            UserCommonFlashRead(g_ucColorUniformityLUTSaveBank, ulGainCheckSumAddr, 1, &pData[5]);
        }

        if((g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_UNIFORMITY_CHKSUM] == pData[5]) &&
           (pucTemp[1] == pData[5]))
        {
            if((g_ucColorUniformityLUTStartPosIndex + 1) == _UNIFORMITY_TOTAL_SET)
            {
                pData[4] = _UNIFORMITY_FUNCTION;
                UserCommonFlashWrite(_UNIFORMITY_FLASH_BANK0, _UNIFORMITY_FINISH_ADDRESS, 1, &pData[4]);
            }
        }
        else
        {
            ucFlag |= _BIT4;
        }
    }
    // level0
#if(_UNIFORMITY_LEVEL0_SUPPORT == _ON)
    if(((g_ucColorUniformityChecksumType >> _UNIFORMITY_OFFSET_TYPE) & 0x01) == _TRUE)
    {
        // level0
        pucTemp[1] = 0;
        ucOffsetTableBank = UserCommonColorGetPanelUniformityOffsetBank(g_ucColorUniformityLUTStartPosIndex);
        usOffsetTableAddr = UserCommonColorGetPanelUniformityOffsetAddr(g_ucColorUniformityLUTStartPosIndex);
        usOffsetCheckSumAddr = usOffsetTableAddr + _PANEL_UNIFORMITY_OFFSET_LUT_SIZE;
        for(ulI = usOffsetTableAddr; ulI < (DWORD)(usOffsetTableAddr + _PANEL_UNIFORMITY_OFFSET_LUT_SIZE); ulI++)
        {
            UserCommonFlashRead(ucOffsetTableBank, ulI, 1, &pucTemp[0]);
            pucTemp[1] += pucTemp[0];
        }
        //
        UserCommonFlashWrite(ucOffsetTableBank, usOffsetCheckSumAddr, 1, &pucTemp[1]);
        UserCommonFlashRead(ucOffsetTableBank, usOffsetCheckSumAddr, 1, &pData[5]);

        if((g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_UNIFORMITY_CHKSUM] == pData[5]) &&
           (pucTemp[1] == pData[5]))
        {
            if((g_ucColorUniformityLUTStartPosIndex + 1) == _UNIFORMITY_TOTAL_SET)
            {
                BYTE ucData = _UNIFORMITY_LEVEL0_SUPPORT;
                ucOffsetTableStartBank = UserCommonColorGetPanelUniformityOffsetBank(0);
                UserCommonFlashWrite(ucOffsetTableStartBank, _UNIFORMITY_OFFSET_FINISH_ADDRESS, 1, &ucData);
            }
        }
        else
        {
            ucFlag |= _BIT4;
        }
    }
    if(((g_ucColorUniformityChecksumType >> _UNIFORMITY_DECAY_TYPE) & 0x01) == _TRUE)
    {
        // level0
        pucTemp[1] = 0;
        ucOffsetTableBank = UserCommonColorGetPanelUniformityOffsetBank(g_ucColorUniformityLUTStartPosIndex);
        usDecayTableAddr = UserCommonColorGetPanelUniformityDecayAddr(g_ucColorUniformityLUTStartPosIndex);
        usDecayCheckSumAddr = usDecayTableAddr + _PANEL_UNIFORMITY_DECAY_LUT_SIZE;
        for(ulI = usDecayTableAddr; ulI < (DWORD)(usDecayTableAddr + _PANEL_UNIFORMITY_DECAY_LUT_SIZE); ulI++)
        {
            UserCommonFlashRead(ucOffsetTableBank, ulI, 1, &pucTemp[0]);
            pucTemp[1] += pucTemp[0];
        }
        //
        UserCommonFlashWrite(ucOffsetTableBank, usDecayCheckSumAddr, 1, &pucTemp[1]);
        UserCommonFlashRead(ucOffsetTableBank, usDecayCheckSumAddr, 1, &pData[5]);

        if((g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_UNIFORMITY_CHKSUM] != pData[5]) ||
           (pucTemp[1] != pData[5])) // do not set bit0 in flash
        {
            ucFlag |= _BIT4;
        }
    }
#endif
#endif  // End of #if(_UNIFORMITY_SUPPORT == _ON)

#if(_MULTI_BRI_CALIBRATION_TYPE >= _MULTI_BRI_THREE_CALIBRATION)
    if(g_ucColorBacklightFlag == _MULTI_BACKLIGHT_3_CAL)
    {
        if(((g_ucColorCalibrationType >> _OCC_CAL_TYPE) & 0x01) == _TRUE)
        {
            pData[2] = UserCommonColorCalibrationCalCheckSum(_OCC_MULTI_BRI_3_TYPE);

            if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_OCC_CHKSUM] == pData[2])
            {
                UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _OCC_MULTI_BRI_3_CHKSUM_ADDRESS, 1, &pData[2]);
            }
            else
            {
                ucFlag |= _BIT2;
            }
        }
    }
#if(_MULTI_BRI_CALIBRATION_TYPE >= _MULTI_BRI_FOUR_CALIBRATION)
    if(g_ucColorBacklightFlag == _MULTI_BACKLIGHT_4_CAL)
    {
        if(((g_ucColorCalibrationType >> _OCC_CAL_TYPE) & 0x01) == _TRUE)
        {
            pData[2] = UserCommonColorCalibrationCalCheckSum(_OCC_MULTI_BRI_4_TYPE);

            if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_OCC_CHKSUM] == pData[2])
            {
                UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _OCC_MULTI_BRI_4_CHKSUM_ADDRESS, 1, &pData[2]);
            }
            else
            {
                ucFlag |= _BIT2;
            }
        }
    }
#endif
#endif

    return ucFlag;
}

//--------------------------------------------------
// Description  : Display Calibration OCC Measure End Matrix CheckSum
// Input Value  : ucCheckType: 5- color matrix
// Output Value : _SUCCESS/_FAIL
//--------------------------------------------------
BYTE UserCommonColorCalibrationMatrixCheckSum(BYTE ucCheckType)
{
    BYTE ucFlag = 1;
    BYTE pucTemp[2] = {0, 0};

    switch(ucCheckType)
    {
        case _COLOR_MATRIX_TYPE:

            pucTemp[0] = UserCommonColorCalibrationCalCheckSum(_COLOR_MATRIX_TYPE);

            if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_COLORMATRIX_CHECKSUM] == pucTemp[0])
            {
                UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _OCC_COLOR_MATRIX_CHKSUM_ADDRESS, 1, &pucTemp[0]);
            }
            else
            {
                ucFlag |= _BIT2;
            }

            break;

        case _COLOR_MATRIX_TYPE2:

            pucTemp[0] = UserCommonColorCalibrationCalCheckSum(_COLOR_MATRIX_TYPE2);

            if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_COLORMATRIX2_CHECKSUM] == pucTemp[0])
            {
                UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _OCC_COLOR_MATRIX2_CHKSUM_ADDRESS, 1, &pucTemp[0]);
            }
            else
            {
                ucFlag |= _BIT2;
            }

            break;

        case _COLOR_MATRIX_MAX_BRI_TYPE:

            pucTemp[0] = UserCommonColorCalibrationCalCheckSum(_COLOR_MATRIX_MAX_BRI_TYPE);

            if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_COLORMATRIX_CHECKSUM] == pucTemp[0])
            {
                UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _OCC_COLOR_MATRIX_MAX_BRI_CHKSUM_ADDRESS, 1, &pucTemp[0]);
            }
            else
            {
                ucFlag |= _BIT2;
            }

            break;

        case _COLOR_MATRIX_MAX_BRI_TYPE2:

            pucTemp[0] = UserCommonColorCalibrationCalCheckSum(_COLOR_MATRIX_MAX_BRI_TYPE2);

            if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_COLORMATRIX2_CHECKSUM] == pucTemp[0])
            {
                UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _OCC_COLOR_MATRIX2_MAX_BRI_CHKSUM_ADDRESS, 1, &pucTemp[0]);
            }
            else
            {
                ucFlag |= _BIT2;
            }

            break;

#if(_MULTI_BRI_CALIBRATION_TYPE >= _MULTI_BRI_THREE_CALIBRATION)
        case _COLOR_MATRIX_MULTI_BRI_3_TYPE:

            pucTemp[0] = UserCommonColorCalibrationCalCheckSum(_COLOR_MATRIX_MULTI_BRI_3_TYPE);

            if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_COLORMATRIX_CHECKSUM] == pucTemp[0])
            {
                UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _OCC_COLOR_MATRIX_MULTI_BRI_3_CHKSUM_ADDRESS, 1, &pucTemp[0]);
            }
            else
            {
                ucFlag |= _BIT2;
            }

            break;

        case _COLOR_MATRIX_MULTI_BRI_3_TYPE2:

            pucTemp[0] = UserCommonColorCalibrationCalCheckSum(_COLOR_MATRIX_MULTI_BRI_3_TYPE2);

            if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_COLORMATRIX2_CHECKSUM] == pucTemp[0])
            {
                UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _OCC_COLOR_MATRIX2_MULTI_BRI_3_CHKSUM_ADDRESS, 1, &pucTemp[0]);
            }
            else
            {
                ucFlag |= _BIT2;
            }

            break;

#if(_MULTI_BRI_CALIBRATION_TYPE >= _MULTI_BRI_FOUR_CALIBRATION)
        case _COLOR_MATRIX_MULTI_BRI_4_TYPE:

            pucTemp[0] = UserCommonColorCalibrationCalCheckSum(_COLOR_MATRIX_MULTI_BRI_4_TYPE);

            if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_COLORMATRIX_CHECKSUM] == pucTemp[0])
            {
                UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _OCC_COLOR_MATRIX_MULTI_BRI_4_CHKSUM_ADDRESS, 1, &pucTemp[0]);
            }
            else
            {
                ucFlag |= _BIT2;
            }

            break;

        case _COLOR_MATRIX_MULTI_BRI_4_TYPE2:

            pucTemp[0] = UserCommonColorCalibrationCalCheckSum(_COLOR_MATRIX_MULTI_BRI_4_TYPE2);

            if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_COLORMATRIX2_CHECKSUM] == pucTemp[0])
            {
                UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _OCC_COLOR_MATRIX2_MULTI_BRI_4_CHKSUM_ADDRESS, 1, &pucTemp[0]);
            }
            else
            {
                ucFlag |= _BIT2;
            }

            break;
#endif
#endif

#if(_HDR10_SUPPORT == _ON)
        case _HDR_TYPE:

            pucTemp[0] = UserCommonColorCalibrationCalCheckSum(_HDR_TYPE);

            if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_COLORMATRIX_CHECKSUM] == pucTemp[0])
            {
                UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _HDR_CHKSUM_ADDRESS, 1, &pucTemp[0]);
                pucTemp[1] = _HDR10_SUPPORT;
                UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _HDR_FINISH_ADDRESS, 1, &pucTemp[1]);
            }
            else
            {
                ucFlag |= _BIT2;
            }

            break;

        case _HDR10_NOTM_BOUND_TYPE:

            pucTemp[0] = UserCommonColorCalibrationCalCheckSum(_HDR10_NOTM_BOUND_TYPE);

            if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_COLORMATRIX_CHECKSUM] == pucTemp[0])
            {
                UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _HDR_NOTM_BOUND_CHKSUM_ADDRESS, 1, &pucTemp[0]);
            }
            else
            {
                ucFlag |= _BIT2;
            }

            break;
#endif

#if(_ADVANCED_HDR10_SUPPORT == _ON)
        case _ADVANCED_HDR10_TYPE:

            pucTemp[0] = UserCommonColorCalibrationCalCheckSum(_ADVANCED_HDR10_TYPE);

            if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_COLORMATRIX_CHECKSUM] == pucTemp[0])
            {
                UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _ADVANCED_HDR10_CHKSUM_ADDRESS, 1, &pucTemp[0]);
            }
            else
            {
                ucFlag |= _BIT2;
            }

            break;
#endif

#if(_BACKLIGHT_DIMMING_SUPPORT == _ON)
#if(_OGC_FUNCTION == _ON)
        case _DIMMING_IG_TYPE:

            pucTemp[0] = UserCommonColorCalibrationCalCheckSum(_DIMMING_IG_TYPE);

            if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_COLORMATRIX_CHECKSUM] == pucTemp[0])
            {
                UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _DIMMING_IG_CHKSUM_ADDRESS, 1, &pucTemp[0]);
            }
            else
            {
                ucFlag |= _BIT2;
            }

            break;
#endif
#endif

        case _RGB_GAIN_TYPE:

#if(_OGC_FUNCTION == _ON)
            pucTemp[0] = UserCommonColorCalibrationCalCheckSum(_RGB_GAIN_TYPE);

            if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_RGB_GAIN_CHKSUM] == pucTemp[0])
            {
                UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _OGC_RGB_GAIN_CHKSUM_ADDRESS, 1, &pucTemp[0]);
            }
            else
            {
                ucFlag |= _BIT2;
            }
#endif
            pucTemp[1] = UserCommonColorCalibrationCalCheckSum(_HEADER_TYPE);

            if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_HEADER_CHKSUM] == pucTemp[1])
            {
                UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _OGC_HEADER_CHKSUM_ADDRESS, 1, &pucTemp[1]);
            }
            else
            {
                ucFlag |= _BIT2;
            }
            break;

        case _RGB_GAIN_MAX_BRI_TYPE:

#if(_OGC_FUNCTION == _ON)
            pucTemp[0] = UserCommonColorCalibrationCalCheckSum(_RGB_GAIN_MAX_BRI_TYPE);

            if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_RGB_GAIN_CHKSUM] == pucTemp[0])
            {
                UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _OGC_RGB_GAIN_MAX_BRI_CHKSUM_ADDRESS, 1, &pucTemp[0]);
            }
            else
            {
                ucFlag |= _BIT2;
            }
#endif
            break;

#if(_TWO_BRI_CALIBRATION_TYPE >= _MULTI_BRI_CALIBRATION_OGC_OCC)
#if(_MULTI_BRI_CALIBRATION_TYPE >= _MULTI_BRI_THREE_CALIBRATION)
        case _RGB_GAIN_MULTI_BRI_3_TYPE:

#if(_OGC_FUNCTION == _ON)
            pucTemp[0] = UserCommonColorCalibrationCalCheckSum(_RGB_GAIN_MULTI_BRI_3_TYPE);

            if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_RGB_GAIN_CHKSUM] == pucTemp[0])
            {
                UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _OGC_RGB_GAIN_MULTI_BRI_3_CHKSUM_ADDRESS, 1, &pucTemp[0]);
            }
            else
            {
                ucFlag |= _BIT2;
            }
#endif
            break;

#if(_MULTI_BRI_CALIBRATION_TYPE >= _MULTI_BRI_FOUR_CALIBRATION)
        case _RGB_GAIN_MULTI_BRI_4_TYPE:

#if(_OGC_FUNCTION == _ON)
            pucTemp[0] = UserCommonColorCalibrationCalCheckSum(_RGB_GAIN_MULTI_BRI_4_TYPE);

            if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_RGB_GAIN_CHKSUM] == pucTemp[0])
            {
                UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _OGC_RGB_GAIN_MULTI_BRI_4_CHKSUM_ADDRESS, 1, &pucTemp[0]);
            }
            else
            {
                ucFlag |= _BIT2;
            }
#endif
            break;
#endif
#endif
#endif

        case _EDID_INFO_TYPE:

            pucTemp[0] = UserCommonColorCalibrationCalCheckSum(_EDID_INFO_TYPE);

            if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_COLORMATRIX_CHECKSUM] == pucTemp[0])
            {
                UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _EDID_INFO_CHKSUM_ADDRESS, 1, &pucTemp[0]);
            }
            else
            {
                ucFlag |= _BIT2;
            }
            break;

        case _NOTM_DCR_THD_TYPE:

            pucTemp[0] = UserCommonColorCalibrationCalCheckSum(_NOTM_DCR_THD_TYPE);

            if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_COLORMATRIX_CHECKSUM] == pucTemp[0])
            {
                UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _DIMMING_NOTM_DCR_THD_CHKSUM_ADDRESS, 1, &pucTemp[0]);
            }
            else
            {
                ucFlag |= _BIT2;
            }
            break;

#if(_FREESYNC_II_SUPPORT == _ON)
        case _FREESYNC_II_IG_TYPE:

            pucTemp[0] = UserCommonColorCalibrationCalCheckSum(_FREESYNC_II_IG_TYPE);

            if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_COLORMATRIX_CHECKSUM] == pucTemp[0])
            {
                UserCommonFlashWrite(_FREESYNC_II_FLASH_BANK, (((WORD)_FREESYNC_II_FLASH_PAGE) << 12) + _FREESYNC_II_IG_CHKSUM_ADDRESS, 1, &pucTemp[0]);
            }
            else
            {
                ucFlag |= _BIT2;
            }
            break;

        case _FREESYNC_II_PQ_TYPE:

            pucTemp[0] = UserCommonColorCalibrationCalCheckSum(_FREESYNC_II_PQ_TYPE);

            if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_COLORMATRIX_CHECKSUM] == pucTemp[0])
            {
                UserCommonFlashWrite(_FREESYNC_II_FLASH_BANK, (((WORD)_FREESYNC_II_FLASH_PAGE) << 12) + _FREESYNC_II_IG_PQ_CHKSUM_ADDRESS, 1, &pucTemp[0]);
            }
            else
            {
                ucFlag |= _BIT2;
            }
            break;
#endif

#if(_HLG_SUPPORT == _ON)
        case _HLG_YMAPPING_TYPE:

            pucTemp[0] = UserCommonColorCalibrationCalCheckSum(_HLG_YMAPPING_TYPE);

            if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_COLORMATRIX_CHECKSUM] == pucTemp[0])
            {
                UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _HDR_HLG_YMAPPING_CHKSUM_ADDRESS, 1, &pucTemp[0]);
            }
            else
            {
                ucFlag |= _BIT2;
            }
            break;
#endif

#if(_HDR10_BACKLIGHT_ADAPTIVE_TM_SUPPORT == _ON)
        case _HDR_BACKLIGHT_ADAPTIVE_TYPE:

            pucTemp[0] = UserCommonColorCalibrationCalCheckSum(_HDR_BACKLIGHT_ADAPTIVE_TYPE);

            if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_COLORMATRIX_CHECKSUM] == pucTemp[0])
            {
                UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _HDR_BACKLIGHT_ADAPTIVE_CHKSUM_ADDRESS, 1, &pucTemp[0]);
            }
            else
            {
                ucFlag |= _BIT2;
            }
            break;
#endif

#if(_HDR10_MASTERING_LV_STEPLESS_TM_SUPPORT == _ON)
        case _HDR_MASTERING_LV_STEPLESS_TYPE:
            pucTemp[0] = UserCommonColorCalibrationCalCheckSum(_HDR_MASTERING_LV_STEPLESS_TYPE);

            if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_COLORMATRIX_CHECKSUM] == pucTemp[0])
            {
                UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _HDR_MASTERING_LV_STEPLESS_CHKSUM_ADDRESS, 1, &pucTemp[0]);
            }
            else
            {
                ucFlag |= _BIT2;
            }
            break;
#endif

#if(_HDR10_USER_DEFINE_FIXED_POINT_TONEMAPPING_SUPPORT == _ON)
        case _HDR_USER_DEFINE_FIXED_POINT_TYPE:
            pucTemp[0] = UserCommonColorCalibrationCalCheckSum(_HDR_USER_DEFINE_FIXED_POINT_TYPE);

            if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_COLORMATRIX_CHECKSUM] == pucTemp[0])
            {
                UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _HDR_USER_DEFINE_FIXED_POINT_CHKSUM_ADDRESS, 1, &pucTemp[0]);
            }
            else
            {
                ucFlag |= _BIT2;
            }
            break;
#endif
#if(_GLOBAL_DIMMING_ONLINE_CALIBRATION_SUPPORT == _ON)
        case _GD_PWMLUT_TYPE:
            pucTemp[0] = UserCommonColorCalibrationCalCheckSum(_GD_PWMLUT_TYPE);
            if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_COLORMATRIX_CHECKSUM] == pucTemp[0])
            {
                BYTE ucData = 1;
                UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _GD_PWMLUT_CHKSUM_ADDRESS, 1, &pucTemp[0]);
                UserCommonFlashWrite(_OGC_FLASH_BANK, _GD_FINISH_ADDRESS, 1, &ucData);
            }
            else
            {
                ucFlag |= _BIT2;
            }

            break;
#endif
#if(_SAVE_OGC_OCC_VERIFY_REPORT_SUPPORT == _ON)
        case _OCC_VERIFY_REPORT_TYPE:
            pucTemp[0] = UserCommonColorCalibrationCalCheckSum(_OCC_VERIFY_REPORT_TYPE);

            if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_OCC_VERIFY_CHECKSUM] == pucTemp[0])
            {
                UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _OCC_VERIFY_CHECKSUM_ADDRESS, 1, &pucTemp[0]);
            }
            else
            {
                ucFlag |= _BIT2;
            }
            break;
#endif
        default:

            break;
    }

    return ucFlag;
}

//--------------------------------------------------
// Description  : Display Calibration Reply Results
// Input Value  : ucType --> Pass or other Fail Errors
// Output Value : None
//--------------------------------------------------
void UserCommonColorCalibrationReplyResult(BYTE ucType)
{
    g_pucMcuDdcciTxBuf[_DDCCI_SOURCE] = _DDCCI_DEST_ADDRESS;
    g_pucMcuDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | 0x04;

    switch(ucType)
    {
        case _DISP_CALIB_START:

            g_pucMcuDdcciTxBuf[_DDCCI_SOURCE] = _DDCCI_DEST_ADDRESS;
            g_pucMcuDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | 0x04;
            g_pucMcuDdcciTxBuf[_DDCCI_DISP_CALIB_OGCOCCDICOM_SUPPORT] = (_FREESYNC_II_SUPPORT << 7) | (_BACKLIGHT_DIMMING_SUPPORT << 6) | ((_TWO_BRI_CALIBRATION_TYPE == _TWO_BRI_CALIBRATION_DICOM_HDR) << 5) | (_HDR10_SUPPORT << 4) | (_OGC_DICOM_FUNCTION << 2) | (_OCC_FUNCTION << 1) | (_OGC_FUNCTION);
            g_pucMcuDdcciTxBuf[_DDCCI_DISP_CALIB_OGC_TOTAL_GAMMA] = ((_DISP_CALIB_VERSION << 3) | _OGC_TOTAL_GAMMA);
            g_pucMcuDdcciTxBuf[_DDCCI_DISP_CALIB_OGC_TOTAL_CT] = _OGC_TOTAL_CT;
            g_pucMcuDdcciTxBuf[_DDCCI_DISP_CALIB_PANEL_BITNUM] = ((_OCC_BOX_PATTERN_GENERATOR_SUPPORT << 7) | (_PANEL_DISP_BIT_MODE << 4) | (_HLG_SUPPORT << 3) | ((_TWO_BRI_CALIBRATION_TYPE == _TWO_BRI_CALIBRATION_OGC_OCC_DICOM_HDR) << 2) | (_ADVANCED_HDR10_SUPPORT << 1) | _OCC_LUT_MODE);
//            g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_PANEL_BITNUM] = (_PANEL_DISP_BIT_MODE );
            g_pucMcuDdcciTxBuf[_DDCCI_DISP_CALIB_PANEL_BITNUM + 1] = UserCommonDdcciCalCheckSum();

            break;

        case _DISP_CALIB_GET_VERSION:

            g_pucMcuDdcciTxBuf[_DDCCI_SOURCE] = _DDCCI_DEST_ADDRESS;
            g_pucMcuDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | 0x02;
            g_pucMcuDdcciTxBuf[_DDCCI_DISP_CALIB_FW_VERSION_H] = ((_DISP_CALIB_FW_VERSION & 0xFF00) >> 8);
            g_pucMcuDdcciTxBuf[_DDCCI_DISP_CALIB_FW_VERSION_L] = (_DISP_CALIB_FW_VERSION & 0xFF);
            g_pucMcuDdcciTxBuf[_DDCCI_DISP_CALIB_FW_VERSION_L + 1] = UserCommonDdcciCalCheckSum();

            break;

        case _DISP_CALIB_GET_NOTM_INFO:

            g_pucMcuDdcciTxBuf[_DDCCI_SOURCE] = _DDCCI_DEST_ADDRESS;
            g_pucMcuDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | 0x03;
            g_pucMcuDdcciTxBuf[_DDCCI_DISP_CALIB_MAX_LV] = _PANEL_MAX_LUMINANCE;
            g_pucMcuDdcciTxBuf[_DDCCI_DISP_CALIB_MAX_FRAME_AVE_LV] = _PANEL_MAX_FRAME_AVERAGE_LUMINANCE;
            g_pucMcuDdcciTxBuf[_DDCCI_DISP_CALIB_MIN_LV] = _PANEL_MIN_LUMINANCE;
            g_pucMcuDdcciTxBuf[_DDCCI_DISP_CALIB_MIN_LV + 1] = UserCommonDdcciCalCheckSum();

            break;

        case _DISP_CALIB_GET_UNI_VERSION:

            g_pucMcuDdcciTxBuf[_DDCCI_SOURCE] = _DDCCI_DEST_ADDRESS;
            g_pucMcuDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | 0x02;
            g_pucMcuDdcciTxBuf[_DDCCI_DISP_CALIB_FW_VERSION_H] = ((_DISP_CALIB_UNI_VERSION & 0xFF00) >> 8);
            g_pucMcuDdcciTxBuf[_DDCCI_DISP_CALIB_FW_VERSION_L] = (_DISP_CALIB_UNI_VERSION & 0xFF);
            g_pucMcuDdcciTxBuf[_DDCCI_DISP_CALIB_FW_VERSION_L + 1] = UserCommonDdcciCalCheckSum();
            break;

        case _DISP_CALIB_GET_FW_SUPPORT:

            g_pucMcuDdcciTxBuf[_DDCCI_SOURCE] = _DDCCI_DEST_ADDRESS;
            g_pucMcuDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | 0x02;
            g_pucMcuDdcciTxBuf[_DDCCI_DISP_CALIB_FW_SUPPORT] = ((_OCC_USER_DEFINE_SHIFT_1_BIT_SUPPORT << 7) | ((_OGC_TOTAL_DICOM - 1) & 0x03) << 5) | (_DCIP3_NO_COMPRESSION_SUPPORT << 4) | (_OCC_IG_NODE_1025_SUPPORT << 3) | ((_DISPLAY_HDR_VERSION == _DISPLAY_HDR_VERSION_1_1) << 2) | (_HDR10_USER_DEFINE_PANEL_MAX_LV_SUPPORT << 1) | (_LOCAL_DIMMING_GLOBAL_BOOST_SUPPORT);
#if(_HDR10_USER_DEFINE_PANEL_MAX_LV_SUPPORT == _ON)
            g_pucMcuDdcciTxBuf[_DDCCI_DISP_CALIB_FW_SUPPORT + 1] = _PANEL_MAX_USER_DEFINE_LUMINANCE;
#else
            g_pucMcuDdcciTxBuf[_DDCCI_DISP_CALIB_FW_SUPPORT + 1] = 0x00;
#endif
            g_pucMcuDdcciTxBuf[_DDCCI_DISP_CALIB_FW_SUPPORT + 2] = UserCommonDdcciCalCheckSum();

            break;

        case _DISP_CALIB_GET_PANEL_INFO:
            g_pucMcuDdcciTxBuf[_DDCCI_SOURCE] = _DDCCI_DEST_ADDRESS;
            g_pucMcuDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | 0x05;
            g_pucMcuDdcciTxBuf[_DDCCI_DISP_CALIB_PANEL_DH_WIDTH_H] = ((_PANEL_DH_WIDTH & 0xFF00) >> 8);
            g_pucMcuDdcciTxBuf[_DDCCI_DISP_CALIB_PANEL_DH_WIDTH_L] = (_PANEL_DH_WIDTH & 0xFF);
            g_pucMcuDdcciTxBuf[_DDCCI_DISP_CALIB_PANEL_DV_HEIGHTTH_H] = ((_PANEL_DV_HEIGHT & 0xFF00) >> 8);
            g_pucMcuDdcciTxBuf[_DDCCI_DISP_CALIB_PANEL_DV_HEIGHTTH_L] = (_PANEL_DV_HEIGHT & 0xFF);
            g_pucMcuDdcciTxBuf[_DDCCI_DISP_CALIB_PANEL_FRONTBACK_SUPPORT] = ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH);
            g_pucMcuDdcciTxBuf[_DDCCI_DISP_CALIB_PANEL_FRONTBACK_SUPPORT + 1] = UserCommonDdcciCalCheckSum();

            break;

        case _DISP_CALIB_GET_FW_ADVANCE:
            g_pucMcuDdcciTxBuf[_DDCCI_SOURCE] = _DDCCI_DEST_ADDRESS;
            g_pucMcuDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | 0x05;
            g_pucMcuDdcciTxBuf[_DDCCI_DISP_CALIB_ADVANCE_1] = (((_TWO_BRI_CALIBRATION_TYPE == _MULTI_BRI_CALIBRATION_OGC_OCC) << 6) | (_OCC_PCM_GAMMA_SUPPORT << 5) | (_OCC_DISPLAY_P3_GAMMA_22_SUPPORT << 4) | (_HDR10_USER_DEFINE_FIXED_POINT_TONEMAPPING_SUPPORT << 3) | (_HDR10_EETF_TONEMAPPING_SUPPORT << 2) | (_HDR10_MASTERING_LV_STEPLESS_TM_SUPPORT << 1) | _HDR10_BACKLIGHT_ADAPTIVE_TM_SUPPORT);
            g_pucMcuDdcciTxBuf[_DDCCI_DISP_CALIB_ADVANCE_2] = ((_SAVE_OGC_OCC_VERIFY_REPORT_SUPPORT << 5) | (_PCM_FULL_TIME_FUNCTION << 4) | (_OCC_GAMUT_NO_COMPRESSION_SUPPORT << 3) | (_OGC_NO_INTERPOLATION_SUPPORT << 2) | (_MULTI_BRI_CALIBRATION_TYPE & 0x03));
            g_pucMcuDdcciTxBuf[_DDCCI_DISP_CALIB_ADVANCE_3] = (((_DISPLAY_HDR_VERSION == _DISPLAY_HDR_VERSION_1_2) << 2) | (_GLOBAL_DIMMING_DARK_MODE_SUPPORT << 1) | (_GLOBAL_DIMMING_ONLINE_CALIBRATION_SUPPORT));
            g_pucMcuDdcciTxBuf[_DDCCI_DISP_CALIB_ADVANCE_4] = ((_OCC_RGB_3D_GAMMA_SUPPORT << 7) | (_OCC_RGB_3D_GAMMA_HDR10_REMAP_SUPPORT << 6) | ((_OCC_RGB_3D_GAMMA_TOTAL_SET - 1) & 0x3F));
            g_pucMcuDdcciTxBuf[_DDCCI_DISP_CALIB_ADVANCE_5] = 0x00;
            g_pucMcuDdcciTxBuf[_DDCCI_DISP_CALIB_ADVANCE_5 + 1] = UserCommonDdcciCalCheckSum();

            break;

        case _DISP_CALIB_GET_GD_SET:
            g_pucMcuDdcciTxBuf[_DDCCI_SOURCE] = _DDCCI_DEST_ADDRESS;
            g_pucMcuDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | 0x06;
            g_pucMcuDdcciTxBuf[_DDCCI_DISP_CALIB_GD_1] = _GLOBAL_DIMMING_DARK_MODE_MAX_GAIN;
            g_pucMcuDdcciTxBuf[_DDCCI_DISP_CALIB_GD_2] = (_GD_PANEL_LV_MAX & 0xFF00) >> 8;
            g_pucMcuDdcciTxBuf[_DDCCI_DISP_CALIB_GD_3] = _GD_PANEL_LV_MAX & 0xFF;
            g_pucMcuDdcciTxBuf[_DDCCI_DISP_CALIB_GD_4] = (_GD_PANEL_LV_MIN & 0xFF00) >> 8;
            g_pucMcuDdcciTxBuf[_DDCCI_DISP_CALIB_GD_5] = _GD_PANEL_LV_MIN & 0xFF;
            g_pucMcuDdcciTxBuf[_DDCCI_DISP_CALIB_GD_6] = 0x00;

            g_pucMcuDdcciTxBuf[_DDCCI_DISP_CALIB_GD_6 + 1] = UserCommonDdcciCalCheckSum();

            break;
        case _DISP_CALIB_GET_AUTH_VER:
            g_pucMcuDdcciTxBuf[_DDCCI_SOURCE] = _DDCCI_DEST_ADDRESS;
            g_pucMcuDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | 0x02;
            g_pucMcuDdcciTxBuf[_DDCCI_LENGTH + 1] = HIBYTE(ScalerColorGetAuthorizeVersion());
            g_pucMcuDdcciTxBuf[_DDCCI_LENGTH + 2] = LOBYTE(ScalerColorGetAuthorizeVersion());
            g_pucMcuDdcciTxBuf[_DDCCI_LENGTH + 3] = UserCommonDdcciCalCheckSum();
            break;

        case _DISP_CALIB_PASS:

            g_pucMcuDdcciTxBuf[_DDCCI_DISP_CALIB_STRING_1] = 'P';
            g_pucMcuDdcciTxBuf[_DDCCI_DISP_CALIB_STRING_2] = 'A';
            g_pucMcuDdcciTxBuf[_DDCCI_DISP_CALIB_STRING_3] = 'S';
            g_pucMcuDdcciTxBuf[_DDCCI_DISP_CALIB_STRING_4] = 'S';
            g_pucMcuDdcciTxBuf[_DDCCI_DISP_CALIB_STRING_4 + 1] = UserCommonDdcciCalCheckSum();

            break;

        case _DISP_CALIB_ERASE_ERROR:

            g_pucMcuDdcciTxBuf[_DDCCI_DISP_CALIB_STRING_1] = 'E';
            g_pucMcuDdcciTxBuf[_DDCCI_DISP_CALIB_STRING_2] = 'R';
            g_pucMcuDdcciTxBuf[_DDCCI_DISP_CALIB_STRING_3] = 'A';
            g_pucMcuDdcciTxBuf[_DDCCI_DISP_CALIB_STRING_4] = 'S';
            g_pucMcuDdcciTxBuf[_DDCCI_DISP_CALIB_STRING_4 + 1] = UserCommonDdcciCalCheckSum();

            break;

        case _DISP_CALIB_FW_ERROR:

            g_pucMcuDdcciTxBuf[_DDCCI_DISP_CALIB_STRING_1] = 'F';
            g_pucMcuDdcciTxBuf[_DDCCI_DISP_CALIB_STRING_2] = 'W';
            g_pucMcuDdcciTxBuf[_DDCCI_DISP_CALIB_STRING_3] = 'E';
            g_pucMcuDdcciTxBuf[_DDCCI_DISP_CALIB_STRING_4] = g_ucColorCalibrationType;
            g_pucMcuDdcciTxBuf[_DDCCI_DISP_CALIB_STRING_4 + 1] = UserCommonDdcciCalCheckSum();

            break;

        case _DISP_CALIB_CRC_ERROR:

            g_pucMcuDdcciTxBuf[_DDCCI_DISP_CALIB_STRING_1] = 'C';
            g_pucMcuDdcciTxBuf[_DDCCI_DISP_CALIB_STRING_2] = 'R';
            g_pucMcuDdcciTxBuf[_DDCCI_DISP_CALIB_STRING_3] = 'C';
            g_pucMcuDdcciTxBuf[_DDCCI_DISP_CALIB_STRING_4] = 'E';
            g_pucMcuDdcciTxBuf[_DDCCI_DISP_CALIB_STRING_4 + 1] = UserCommonDdcciCalCheckSum();

            break;

        case _DISP_CALIB_FAIL:

        default:

            g_pucMcuDdcciTxBuf[_DDCCI_DISP_CALIB_STRING_1] = 'F';
            g_pucMcuDdcciTxBuf[_DDCCI_DISP_CALIB_STRING_2] = 'A';
            g_pucMcuDdcciTxBuf[_DDCCI_DISP_CALIB_STRING_3] = 'I';
            g_pucMcuDdcciTxBuf[_DDCCI_DISP_CALIB_STRING_4] = 'L';
            g_pucMcuDdcciTxBuf[_DDCCI_DISP_CALIB_STRING_4 + 1] = UserCommonDdcciCalCheckSum();

            break;
    }

    ScalerMcuDdcciSendData(GET_RUN_DDCCI_HANDLE_CHANNEL(), g_pucMcuDdcciTxBuf);

    SET_INTERRUPT_ENABLE_STATUS(_INT_EXINT_1, _ENABLE);
}
//--------------------------------------------------
// Description  : Save OGC/OCC Header
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonColorCalibrationSaveHeader(void)
{
    //==========Write OGC Header============
    pData[0] = 0x11;
    pData[1] = 0x11;
    pData[2] = _OGC_HEADER_LENGTH;
    pData[3] = g_pucMcuDdcciRxBuf[_OGC_HEADER_IF_DO_OGC]; // 1: Do OGC; 0: not do OGC, even if OGC SUPPORT is on
    UserCommonFlashWrite(_OGC_FLASH_BANK, _OGC_HEADER_ADDRESS, 4, pData);
    UserCommonFlashWrite(_OGC_FLASH_BANK, _OGC_HEADER_ADDRESS + 4, 2 + _OGC_TOTAL_GAMMA + _OGC_TOTAL_CT, g_pucMcuDdcciRxBuf + _OGC_HEADER_GAMMA_CT_INDEX);
    // Gamma Number, Gamma Index1, GammaIndex2,..., Gamma Index n;
    // CT Numer, CT Index1, CT Index 2, ..., CT Index n.

    //==========Write OCC Header============
    pData[0] = 0x22;
    pData[1] = 0x22;
    pData[2] = _OCC_HEADER_LENGTH;
    pData[3] = g_pucMcuDdcciRxBuf[_OCC_HEADER_IF_DO_OCC]; // 1: do OCC; 0: not do OCC, even if OCC support is on
    pData[4] = g_pucMcuDdcciRxBuf[_OCC_HEADER_MATRIX_NUMBER]; // Matrix Number:3/2/1. 1st is sRGB, 2nd is Adobe, 3rd is SoftProof
    UserCommonFlashWrite(_OGC_FLASH_BANK, _OCC_HEADER_ADDRESS, 5, pData);
    //==========Write DICOM Header============
    pData[0] = 0x33;
    pData[1] = 0x33;
    pData[2] = _DICOM_HEADER_LENGTH;
    pData[3] = g_pucMcuDdcciRxBuf[_DICOM_HEADER_IF_DO_DICOM];
    pData[4] = g_pucMcuDdcciRxBuf[_DICOM_HEADER_MODE]; // 0 - By RGB Mode; 1- By Gray Mod
    UserCommonFlashWrite(_OGC_FLASH_BANK, _DICOM_HEADER_ADDRESS, 5, pData);

    //==========Write White Lv Header============
    pData[0] = 0x44;
    pData[1] = 0x44;
    pData[2] = _WHITE_LV_HEADER_LENGTH;
    pData[3] = g_pucMcuDdcciRxBuf[_WHITE_LV_HEADER];
    pData[4] = g_pucMcuDdcciRxBuf[_WHITE_LV_HEADER + 1];
    UserCommonFlashWrite(_OGC_FLASH_BANK, _WHITE_LV_HEADER_ADDRESS, 5, pData);
}

//--------------------------------------------------
// Description  : Save EDID info
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonColorCalibrationSaveEDIDInfo(void)
{
    UserCommonFlashWrite(_OGC_FLASH_BANK, _EDID_INFO_ADDRESS, 14, g_pucMcuDdcciRxBuf + _DDCCI_DISP_CALIB_EDID_INDEX);
}

//--------------------------------------------------
// Description  : Save No ToneMapping DCR THD
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonColorCalibrationSaveNoToneMappingDCRTHD(void)
{
    UserCommonFlashWrite(_OGC_FLASH_BANK, _DIMMING_NOTM_DCR_THD_ADDRESS, _NOTM_DCR_THD_LENGTH, g_pucMcuDdcciRxBuf + _DDCCI_DISP_CALIB_NOTM_DCR_THD_INDEX);
}

//--------------------------------------------------
// Description  : Show Calibration D-Domain Pattern
// Input Value  : WORD usRed, WORD usGreen, WORD usBlue, bit PatternType
// Output Value : None
//--------------------------------------------------
void UserCommonColorCalibrationShowDDomainPattern(WORD usRed, WORD usGreen, WORD usBlue, BYTE ucPatternType)
{
    ucPatternType = ucPatternType;

#if(_OCC_BOX_PATTERN_GENERATOR_SUPPORT == _ON)
    if(ucPatternType == _PG_BOX_PATTERN)
    {
        ScalerDDomainBoxPatternGenAdjustColor10bit(usRed, usGreen, usBlue);
    }
    else
#endif
    {
        ScalerDDomainPatternGenAdjustColor10bit(usRed, usGreen, usBlue);
    }
}

//--------------------------------------------------
// Description  : Set Registers of Box Pattern Generator
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonColorCalibrationSetBoxPatternGen(BYTE *pucCommand, bit bEnable)
{
    ScalerDDomainPatternGenFrontSetBox(pucCommand, bEnable);

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
    {
        ScalerDDomainPatternGenBackSetBox(pucCommand + _DDCCI_DISP_CALIB_PATTERN_INDEX_OFFSET, bEnable);
    }
#endif
}


#if(_HDR10_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Save HDR10 No Tone Mapping Bound info
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonColorCalibrationSaveHDR10BoundInfo(void)
{
    UserCommonFlashWrite(_OGC_FLASH_BANK, _OGC_HDR10_NOTM_BOUND_ADDRESS, _NOTM_BOUND_SAVE_LENGTH, g_pucMcuDdcciRxBuf + _DDCCI_DISP_CALIB_HDR10_NOTM_BOUND_INDEX);
}
#endif

#if((_FREESYNC_II_SUPPORT == _ON) || (_LOCAL_DIMMING_GLOBAL_BOOST_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Show White Pattern
// Input Value  : BYTE ucPatternType
// Output Value : None
//--------------------------------------------------
void UserCommonColorCalibrationShowWhite(BYTE ucPatternType)
{
    ScalerTimerWaitForDDomainEvent(_EVENT_DEN_STOP);
    ScalerColorPCMInputGammaEnable(_FUNCTION_OFF);
    ScalerColorOutputGammaEnable(_FUNCTION_OFF);
#if(_COLOR_IP_SRGB == _ON)
    ScalerColorSRGBEnable(_FUNCTION_OFF);
#endif
    if(ucPatternType == _FREESYNC_II_WHITE)
    {
        ScalerColorPCMOutputGammaAdjust(_1P_NORMAL_REGION, g_pucColorDISP_FREESYNC_II_CALIBRATION_FLASH + _FREESYNC_II_OCC_GAMMA10_ADDRESS, _FREESYNC_II_FLASH_BANK);
    }
    else if(ucPatternType == _LD_BOOST_WHITE)
    {
        ScalerColorPCMOutputGammaAdjust(_1P_NORMAL_REGION, g_pucColorDISP_CALIBRATION_FLASH + _OCC_HDR10_GAMMA10_ADDRESS, _OCC_GAMMA_FLASH_BANK);
    }

#if(_PCM_FUNCTION == _ON)
    ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _SRGB_1_BIT_SHIFT_LEFT, ScalerColorsRGBBypassGetTableAddress(_SRGB_BYPASS), ScalerColorsRGBBypassGetTableBank(), 18);
#endif
    ScalerColorPCMSetPCMMode(_1P_NORMAL_REGION, _PCM_MODE);

    ScalerColorOutputGammaEnable(_FUNCTION_ON);
#if(_COLOR_IP_SRGB == _ON)
    ScalerColorSRGBEnable(_FUNCTION_ON);
#endif
    ScalerColorPCMInputGammaEnable(_FUNCTION_ON);
#if(_COLOR_IP_I_GAMMA == _ON)
    ScalerColorPCMRegionEnable(_1P_NORMAL_REGION, _DB_APPLY_POLLING, _ON);
#endif
#if(_COLOR_IP_BRIGHTNESS == _ON)
    ScalerColorBrightnessEnable(_FUNCTION_OFF);
#endif
#if(_COLOR_IP_CONTRAST == _ON)
    ScalerColorContrastEnable(_FUNCTION_OFF);
#endif

    if(g_ucColorPatternType == _BG_PATTERN)
    {
        ScalerDDomainBackgroundEnable(_DDOMAIN_RGN_ALL, _DISABLE);
    }

    UserCommonColorCalibrationShowDDomainPattern(tOCC_SRGB_TABLE[18], tOCC_SRGB_TABLE[19], tOCC_SRGB_TABLE[20], g_ucColorPatternType);
}
#endif
#if(_UNIFORMITY_FUNCTION == _ON)
//--------------------------------------------------
// Description  : Display Calibration Reply PCM Matrix
// Input Value  : ucPCMType --> _PCM_OSD_SRGB or ADOBE_RGB
// Output Value : None
//--------------------------------------------------
void UserCommonColorCalibrationReplyOCCMatrix(BYTE ucPCMType)
{
    WORD usReadStartPos = 0;
    WORD usTotalLength = 18;
    BYTE ucSendLength = 13;

#if(_OCC_LUT_MODE == _ON)
    usTotalLength = 306;
#endif

    g_pucMcuDdcciTxBuf[_DDCCI_SOURCE] = _DDCCI_DEST_ADDRESS;

    usReadStartPos = (WORD)ucSendLength * ((g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_UNIFORMITY_INDEX] >> 3) & 0x03);

    ucSendLength = ((usTotalLength - usReadStartPos) < 13) ? (usTotalLength - usReadStartPos) : 13;
#if(_TWO_BRI_CALIBRATION_TYPE >= _TWO_BRI_CALIBRATION_OGC_OCC_DICOM_HDR)
    switch(ucPCMType)
    {
        case _PCM_SRGB:

            g_pucMcuDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | ucSendLength;
            UserCommonFlashRead(_OGC_FLASH_BANK, ((WORD)_OGC_FLASH_PAGE << 12) + _OCC_SRGBMATRIX_MAX_BRI_ADDRESS + (WORD)usReadStartPos, ucSendLength, g_pucMcuDdcciTxBuf + _DDCCI_COMMAND);
            g_pucMcuDdcciTxBuf[_DDCCI_COMMAND + ucSendLength] = UserCommonDdcciCalCheckSum();

            break;

        case _PCM_ADOBE_RGB:

            g_pucMcuDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | ucSendLength;
            UserCommonFlashRead(_OGC_FLASH_BANK, ((WORD)_OGC_FLASH_PAGE << 12) + _OCC_ADOBEMATRIX_MAX_BRI_ADDRESS + (WORD)usReadStartPos, ucSendLength, g_pucMcuDdcciTxBuf + _DDCCI_COMMAND);
            g_pucMcuDdcciTxBuf[_DDCCI_COMMAND + ucSendLength] = UserCommonDdcciCalCheckSum();

            break;

        case _PCM_DCI_P3:

            g_pucMcuDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | ucSendLength;
            UserCommonFlashRead(_OGC_FLASH_BANK, ((WORD)_OGC_FLASH_PAGE << 12) + _OCC_DCIP3_MAX_BRI_ADDRESS + (WORD)usReadStartPos, ucSendLength, g_pucMcuDdcciTxBuf + _DDCCI_COMMAND);
            g_pucMcuDdcciTxBuf[_DDCCI_COMMAND + ucSendLength] = UserCommonDdcciCalCheckSum();

            break;

        case _PCM_USER_DEFINE:

            g_pucMcuDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | ucSendLength;
            UserCommonFlashRead(_OGC_FLASH_BANK, ((WORD)_OGC_FLASH_PAGE << 12) + _OCC_USERDEFINE_MAX_BRI_ADDRESS + (WORD)usReadStartPos, ucSendLength, g_pucMcuDdcciTxBuf + _DDCCI_COMMAND);
            g_pucMcuDdcciTxBuf[_DDCCI_COMMAND + ucSendLength] = UserCommonDdcciCalCheckSum();

            break;

        case _PCM_USER_DEFINE_2:

            g_pucMcuDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | ucSendLength;
            UserCommonFlashRead(_OGC_FLASH_BANK, ((WORD)_OGC_FLASH_PAGE << 12) + _OCC_USERDEFINE2_MAX_BRI_ADDRESS + (WORD)usReadStartPos, ucSendLength, g_pucMcuDdcciTxBuf + _DDCCI_COMMAND);
            g_pucMcuDdcciTxBuf[_DDCCI_COMMAND + ucSendLength] = UserCommonDdcciCalCheckSum();

            break;

        case _PCM_DISPLAY_P3:

            g_pucMcuDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | ucSendLength;
            UserCommonFlashRead(_OGC_FLASH_BANK, ((WORD)_OGC_FLASH_PAGE << 12) + _OCC_DISPLAYP3_MAX_BRI_ADDRESS + (WORD)usReadStartPos, ucSendLength, g_pucMcuDdcciTxBuf + _DDCCI_COMMAND);
            g_pucMcuDdcciTxBuf[_DDCCI_COMMAND + ucSendLength] = UserCommonDdcciCalCheckSum();

            break;

        case _PCM_REC_709:

            g_pucMcuDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | ucSendLength;
            UserCommonFlashRead(_OGC_FLASH_BANK, ((WORD)_OGC_FLASH_PAGE << 12) + _OCC_REC709_MAX_BRI_ADDRESS + (WORD)usReadStartPos, ucSendLength, g_pucMcuDdcciTxBuf + _DDCCI_COMMAND);
            g_pucMcuDdcciTxBuf[_DDCCI_COMMAND + ucSendLength] = UserCommonDdcciCalCheckSum();

            break;

        case _PCM_SMPTE_C:

            g_pucMcuDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | ucSendLength;
            UserCommonFlashRead(_OGC_FLASH_BANK, ((WORD)_OGC_FLASH_PAGE << 12) + _OCC_SMPTEC_MAX_BRI_ADDRESS + (WORD)usReadStartPos, ucSendLength, g_pucMcuDdcciTxBuf + _DDCCI_COMMAND);
            g_pucMcuDdcciTxBuf[_DDCCI_COMMAND + ucSendLength] = UserCommonDdcciCalCheckSum();

            break;

        case _PCM_EBU_MODE:

            g_pucMcuDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | ucSendLength;
            UserCommonFlashRead(_OGC_FLASH_BANK, ((WORD)_OGC_FLASH_PAGE << 12) + _OCC_EBU_MAX_BRI_ADDRESS + (WORD)usReadStartPos, ucSendLength, g_pucMcuDdcciTxBuf + _DDCCI_COMMAND);
            g_pucMcuDdcciTxBuf[_DDCCI_COMMAND + ucSendLength] = UserCommonDdcciCalCheckSum();

            break;

        case _PCM_USER_DEFINE_3:

            g_pucMcuDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | ucSendLength;
            UserCommonFlashRead(_OGC_FLASH_BANK, ((WORD)_OGC_FLASH_PAGE << 12) + _OCC_USERDEFINE3_MAX_BRI_ADDRESS + (WORD)usReadStartPos, ucSendLength, g_pucMcuDdcciTxBuf + _DDCCI_COMMAND);
            g_pucMcuDdcciTxBuf[_DDCCI_COMMAND + ucSendLength] = UserCommonDdcciCalCheckSum();

            break;

        case _PCM_USER_DEFINE_4:

            g_pucMcuDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | ucSendLength;
            UserCommonFlashRead(_OGC_FLASH_BANK, ((WORD)_OGC_FLASH_PAGE << 12) + _OCC_USERDEFINE4_MAX_BRI_ADDRESS + (WORD)usReadStartPos, ucSendLength, g_pucMcuDdcciTxBuf + _DDCCI_COMMAND);
            g_pucMcuDdcciTxBuf[_DDCCI_COMMAND + ucSendLength] = UserCommonDdcciCalCheckSum();

            break;

        case _PCM_USER_DEFINE_5:

            g_pucMcuDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | ucSendLength;
            UserCommonFlashRead(_OGC_FLASH_BANK, ((WORD)_OGC_FLASH_PAGE << 12) + _OCC_USERDEFINE5_MAX_BRI_ADDRESS + (WORD)usReadStartPos, ucSendLength, g_pucMcuDdcciTxBuf + _DDCCI_COMMAND);
            g_pucMcuDdcciTxBuf[_DDCCI_COMMAND + ucSendLength] = UserCommonDdcciCalCheckSum();

            break;

        case _PCM_USER_DEFINE_6:

            g_pucMcuDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | ucSendLength;
            UserCommonFlashRead(_OGC_FLASH_BANK, ((WORD)_OGC_FLASH_PAGE << 12) + _OCC_USERDEFINE6_MAX_BRI_ADDRESS + (WORD)usReadStartPos, ucSendLength, g_pucMcuDdcciTxBuf + _DDCCI_COMMAND);
            g_pucMcuDdcciTxBuf[_DDCCI_COMMAND + ucSendLength] = UserCommonDdcciCalCheckSum();

            break;

        default:
            break;
    }
#else
    switch(ucPCMType)
    {
        case _PCM_SRGB:

            g_pucMcuDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | ucSendLength;
            UserCommonFlashRead(_OGC_FLASH_BANK, ((WORD)_OGC_FLASH_PAGE << 12) + _OCC_SRGBMATRIX_ADDRESS + (WORD)usReadStartPos, ucSendLength, g_pucMcuDdcciTxBuf + _DDCCI_COMMAND);
            g_pucMcuDdcciTxBuf[_DDCCI_COMMAND + ucSendLength] = UserCommonDdcciCalCheckSum();

            break;

        case _PCM_ADOBE_RGB:

            g_pucMcuDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | ucSendLength;
            UserCommonFlashRead(_OGC_FLASH_BANK, ((WORD)_OGC_FLASH_PAGE << 12) + _OCC_ADOBEMATRIX_ADDRESS + (WORD)usReadStartPos, ucSendLength, g_pucMcuDdcciTxBuf + _DDCCI_COMMAND);
            g_pucMcuDdcciTxBuf[_DDCCI_COMMAND + ucSendLength] = UserCommonDdcciCalCheckSum();

            break;

        case _PCM_DCI_P3:

            g_pucMcuDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | ucSendLength;
            UserCommonFlashRead(_OGC_FLASH_BANK, ((WORD)_OGC_FLASH_PAGE << 12) + _OCC_DCIP3_ADDRESS + (WORD)usReadStartPos, ucSendLength, g_pucMcuDdcciTxBuf + _DDCCI_COMMAND);
            g_pucMcuDdcciTxBuf[_DDCCI_COMMAND + ucSendLength] = UserCommonDdcciCalCheckSum();

            break;

        case _PCM_USER_DEFINE:

            g_pucMcuDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | ucSendLength;
            UserCommonFlashRead(_OGC_FLASH_BANK, ((WORD)_OGC_FLASH_PAGE << 12) + _OCC_USERDEFINE_ADDRESS + (WORD)usReadStartPos, ucSendLength, g_pucMcuDdcciTxBuf + _DDCCI_COMMAND);
            g_pucMcuDdcciTxBuf[_DDCCI_COMMAND + ucSendLength] = UserCommonDdcciCalCheckSum();

            break;

        case _PCM_USER_DEFINE_2:

            g_pucMcuDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | ucSendLength;
            UserCommonFlashRead(_OGC_FLASH_BANK, ((WORD)_OGC_FLASH_PAGE << 12) + _OCC_USERDEFINE2_ADDRESS + (WORD)usReadStartPos, ucSendLength, g_pucMcuDdcciTxBuf + _DDCCI_COMMAND);
            g_pucMcuDdcciTxBuf[_DDCCI_COMMAND + ucSendLength] = UserCommonDdcciCalCheckSum();

            break;

        case _PCM_DISPLAY_P3:

            g_pucMcuDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | ucSendLength;
            UserCommonFlashRead(_OGC_FLASH_BANK, ((WORD)_OGC_FLASH_PAGE << 12) + _OCC_DISPLAYP3_ADDRESS + (WORD)usReadStartPos, ucSendLength, g_pucMcuDdcciTxBuf + _DDCCI_COMMAND);
            g_pucMcuDdcciTxBuf[_DDCCI_COMMAND + ucSendLength] = UserCommonDdcciCalCheckSum();

            break;

        case _PCM_REC_709:

            g_pucMcuDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | ucSendLength;
            UserCommonFlashRead(_OGC_FLASH_BANK, ((WORD)_OGC_FLASH_PAGE << 12) + _OCC_REC709_ADDRESS + (WORD)usReadStartPos, ucSendLength, g_pucMcuDdcciTxBuf + _DDCCI_COMMAND);
            g_pucMcuDdcciTxBuf[_DDCCI_COMMAND + ucSendLength] = UserCommonDdcciCalCheckSum();

            break;

        case _PCM_SMPTE_C:

            g_pucMcuDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | ucSendLength;
            UserCommonFlashRead(_OGC_FLASH_BANK, ((WORD)_OGC_FLASH_PAGE << 12) + _OCC_SMPTEC_ADDRESS + (WORD)usReadStartPos, ucSendLength, g_pucMcuDdcciTxBuf + _DDCCI_COMMAND);
            g_pucMcuDdcciTxBuf[_DDCCI_COMMAND + ucSendLength] = UserCommonDdcciCalCheckSum();

            break;

        case _PCM_EBU_MODE:

            g_pucMcuDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | ucSendLength;
            UserCommonFlashRead(_OGC_FLASH_BANK, ((WORD)_OGC_FLASH_PAGE << 12) + _OCC_EBU_ADDRESS + (WORD)usReadStartPos, ucSendLength, g_pucMcuDdcciTxBuf + _DDCCI_COMMAND);
            g_pucMcuDdcciTxBuf[_DDCCI_COMMAND + ucSendLength] = UserCommonDdcciCalCheckSum();

            break;

        case _PCM_USER_DEFINE_3:

            g_pucMcuDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | ucSendLength;
            UserCommonFlashRead(_OGC_FLASH_BANK, ((WORD)_OGC_FLASH_PAGE << 12) + _OCC_USERDEFINE3_ADDRESS + (WORD)usReadStartPos, ucSendLength, g_pucMcuDdcciTxBuf + _DDCCI_COMMAND);
            g_pucMcuDdcciTxBuf[_DDCCI_COMMAND + ucSendLength] = UserCommonDdcciCalCheckSum();

            break;

        case _PCM_USER_DEFINE_4:

            g_pucMcuDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | ucSendLength;
            UserCommonFlashRead(_OGC_FLASH_BANK, ((WORD)_OGC_FLASH_PAGE << 12) + _OCC_USERDEFINE4_ADDRESS + (WORD)usReadStartPos, ucSendLength, g_pucMcuDdcciTxBuf + _DDCCI_COMMAND);
            g_pucMcuDdcciTxBuf[_DDCCI_COMMAND + ucSendLength] = UserCommonDdcciCalCheckSum();

            break;

        case _PCM_USER_DEFINE_5:

            g_pucMcuDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | ucSendLength;
            UserCommonFlashRead(_OGC_FLASH_BANK, ((WORD)_OGC_FLASH_PAGE << 12) + _OCC_USERDEFINE5_ADDRESS + (WORD)usReadStartPos, ucSendLength, g_pucMcuDdcciTxBuf + _DDCCI_COMMAND);
            g_pucMcuDdcciTxBuf[_DDCCI_COMMAND + ucSendLength] = UserCommonDdcciCalCheckSum();

            break;

        case _PCM_USER_DEFINE_6:

            g_pucMcuDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | ucSendLength;
            UserCommonFlashRead(_OGC_FLASH_BANK, ((WORD)_OGC_FLASH_PAGE << 12) + _OCC_USERDEFINE6_ADDRESS + (WORD)usReadStartPos, ucSendLength, g_pucMcuDdcciTxBuf + _DDCCI_COMMAND);
            g_pucMcuDdcciTxBuf[_DDCCI_COMMAND + ucSendLength] = UserCommonDdcciCalCheckSum();

            break;

        default:
            break;
    }
#endif
    // ScalerMcuDdcciSendData(g_pucDdcciTxBuf);
    ScalerMcuDdcciSendData(GET_RUN_DDCCI_HANDLE_CHANNEL(), g_pucMcuDdcciTxBuf);

    SET_INTERRUPT_ENABLE_STATUS(_INT_EXINT_1, _ENABLE);
}

//--------------------------------------------------
// Description  : Display Calibration Reply OGC Header
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonColorCalibrationReplyOGCHeader(void)
{
    WORD usReadStartPos = 0;
    BYTE ucSendLength = 13;

    g_pucMcuDdcciTxBuf[_DDCCI_SOURCE] = _DDCCI_DEST_ADDRESS;

    usReadStartPos = (WORD)ucSendLength * (g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_UNIFORMITY_INDEX] & 0x01);

    ucSendLength = ((_OGC_HEADER_LENGTH - usReadStartPos) < 13) ? (_OGC_HEADER_LENGTH - usReadStartPos) : 13;

    g_pucMcuDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | ucSendLength;
    UserCommonFlashRead(_OGC_FLASH_BANK, ((WORD)_OGC_FLASH_PAGE << 12) + _OGC_HEADER_ADDRESS + usReadStartPos, ucSendLength, g_pucMcuDdcciTxBuf + _DDCCI_COMMAND);
    g_pucMcuDdcciTxBuf[_DDCCI_COMMAND + ucSendLength] = UserCommonDdcciCalCheckSum();

    // ScalerMcuDdcciSendData(g_pucDdcciTxBuf);
    ScalerMcuDdcciSendData(GET_RUN_DDCCI_HANDLE_CHANNEL(), g_pucMcuDdcciTxBuf);

    SET_INTERRUPT_ENABLE_STATUS(_INT_EXINT_1, _ENABLE);
}
//--------------------------------------------------
// Description  : Reply the OGCOCC LV ratio to uniformity tool
// Input Value  : ucCTGammaIndex, the set of CT and gamma
// Output Value : CT_ratio,SRGB,AdobeRGB,DCIP3,DisplayP3,Userdefine--ratio
//--------------------------------------------------
void UserCommonColorCalibReplyOGCOCCLvRatio(void)
{
    WORD usReadStartPos = 0;
    BYTE ucSendLength = 13;
    BYTE ucLvRatioLength = (_OGC_TOTAL_CT + 5) * 2;

    g_pucMcuDdcciTxBuf[_DDCCI_SOURCE] = _DDCCI_DEST_ADDRESS;
    usReadStartPos = (WORD)ucSendLength * (g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_UNIFORMITY_INDEX] & 0x0F);
    ucSendLength = ((ucLvRatioLength - usReadStartPos) < 13) ? (ucLvRatioLength - usReadStartPos) : 13;
    g_pucMcuDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | ucSendLength;
    UserCommonFlashRead(_OGC_FLASH_BANK, ((WORD)_OGC_FLASH_PAGE << 12) + _OGCOCC_LV_RARIO_ADDRESS + usReadStartPos, ucSendLength, g_pucMcuDdcciTxBuf + _DDCCI_COMMAND);
    g_pucMcuDdcciTxBuf[_DDCCI_COMMAND + ucSendLength] = UserCommonDdcciCalCheckSum();

    ScalerMcuDdcciSendData(GET_RUN_DDCCI_HANDLE_CHANNEL(), g_pucMcuDdcciTxBuf);

    SET_INTERRUPT_ENABLE_STATUS(_INT_EXINT_1, _ENABLE);
}

//--------------------------------------------------
// Description  : Reply the OGCOCC LV ratio to uniformity tool
// Input Value  : ucCTGammaIndex, the set of CT and gamma
// Output Value : CT_ratio,SRGB,AdobeRGB,DCIP3,displayP3,Userdefine1~6,EBU,SMPTEC,REC709--ratio
//--------------------------------------------------
void UserCommonColorCalibReplyOGCNEWLvRatio(void)
{
    WORD usReadStartPos = 0;
    BYTE ucSendLength = 13;
    BYTE ucLvRatioLength = 0;

    ucLvRatioLength = g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_UNIFORMITY_INDEX + 1];

    g_pucMcuDdcciTxBuf[_DDCCI_SOURCE] = _DDCCI_DEST_ADDRESS;
    usReadStartPos = (WORD)ucSendLength * (g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_UNIFORMITY_INDEX] & 0x0F);
    ucSendLength = ((ucLvRatioLength - usReadStartPos) < 13) ? (ucLvRatioLength - usReadStartPos) : 13;
    g_pucMcuDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | ucSendLength;
    UserCommonFlashRead(_OGC_FLASH_BANK, ((WORD)_OGC_FLASH_PAGE << 12) + _OGCOCC_LV_RARIO_ADDRESS + usReadStartPos, ucSendLength, g_pucMcuDdcciTxBuf + _DDCCI_COMMAND);
    g_pucMcuDdcciTxBuf[_DDCCI_COMMAND + ucSendLength] = UserCommonDdcciCalCheckSum();

    ScalerMcuDdcciSendData(GET_RUN_DDCCI_HANDLE_CHANNEL(), g_pucMcuDdcciTxBuf);

    SET_INTERRUPT_ENABLE_STATUS(_INT_EXINT_1, _ENABLE);
}

//--------------------------------------------------
// Description  : Display Calibration Reply Define, which Uniformity Tool Needs
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonColorCalibrationReplyUniformityDefine(void)
{
    g_pucMcuDdcciTxBuf[_DDCCI_SOURCE] = _DDCCI_DEST_ADDRESS;
    g_pucMcuDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | 0x08;

    g_pucMcuDdcciTxBuf[2] = (_UNIFORMITY_PLUS_FUNCTION << 7) |
                            ((_UNIFORMITY_1ST_TABLE_LEVEL & 0x07) << 4) |
                            (_UNIFORMITY_TOTAL_SET & 0x0F);

    g_pucMcuDdcciTxBuf[3] = _PANEL_UNIFORMITY_HOR_INTERVAL;
    g_pucMcuDdcciTxBuf[4] = (BYTE)_PANEL_DH_WIDTH;
    g_pucMcuDdcciTxBuf[5] = (BYTE)(_PANEL_DH_WIDTH / 256);
    g_pucMcuDdcciTxBuf[6] = (BYTE)_PANEL_DV_HEIGHT;
    g_pucMcuDdcciTxBuf[7] = (BYTE)(_PANEL_DV_HEIGHT / 256);
    g_pucMcuDdcciTxBuf[8] = (BYTE)_OGC_TOTAL_CT;

    // Level0
    // Offset
    g_pucMcuDdcciTxBuf[9] = (_UNIFORMITY_OFFSET_TYPE6 << 6) |
                            (_UNIFORMITY_OFFSET_TYPE5 << 5) |
                            (_UNIFORMITY_OFFSET_TYPE4 << 4) |
                            (_UNIFORMITY_OFFSET_TYPE3 << 3) |
                            (_UNIFORMITY_OFFSET_TYPE2 << 2) |
                            (_UNIFORMITY_OFFSET_TYPE1 << 1) |
                            _UNIFORMITY_OFFSET_TYPE0;

    g_pucMcuDdcciTxBuf[10] = UserCommonDdcciCalCheckSum();// 8

    // ScalerMcuDdcciSendData(g_pucDdcciTxBuf);
    ScalerMcuDdcciSendData(GET_RUN_DDCCI_HANDLE_CHANNEL(), g_pucMcuDdcciTxBuf);

    SET_INTERRUPT_ENABLE_STATUS(_INT_EXINT_1, _ENABLE);
}
//--------------------------------------------------
// Description  : Reply the CCT gain to uniformity tool
// Input Value  : ucCTGammaIndex, the set of CT and gamma
// Output Value : None
//--------------------------------------------------
void UserCommonColorCalibrationReplyCCTGain(void)
{
    BYTE ucGammaIndex = 0;
    BYTE ucColorTempIndex = 0;
    BYTE pucTemp[6] = {0, 0, 0, 0, 0, 0};
    ucGammaIndex = (g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_INDEX] >> 4) & 0x0F;
    ucColorTempIndex = g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_INDEX] & 0x0F;
    if(ucColorTempIndex != 0x0F)
    {
#if(_TWO_BRI_CALIBRATION_TYPE >= _TWO_BRI_CALIBRATION_OGC_OCC_DICOM_HDR)
        UserCommonFlashRead(_OGC_FLASH_BANK, ((WORD)_OGC_FLASH_PAGE << 12) | (ucColorTempIndex * _OGC_TOTAL_GAMMA * 6 + ucGammaIndex * 6 + _OGC_RGB_GAIN_MAX_BRI_ADDRESS), 6, pucTemp);
#else
        UserCommonFlashRead(_OGC_FLASH_BANK, ((WORD)_OGC_FLASH_PAGE << 12) | (ucColorTempIndex * _OGC_TOTAL_GAMMA * 6 + ucGammaIndex * 6 + _OGC_RGB_GAIN_ADDRESS), 6, pucTemp);
#endif
    }
    else
    {
        pucTemp[0] = 0x08;
        pucTemp[1] = 0x00;
        pucTemp[2] = 0x08;
        pucTemp[3] = 0x00;
        pucTemp[4] = 0x08;
        pucTemp[5] = 0x00;
    }
    g_pucMcuDdcciTxBuf[_DDCCI_SOURCE] = _DDCCI_DEST_ADDRESS;
    g_pucMcuDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | 0x06;
    g_pucMcuDdcciTxBuf[2] = pucTemp[0];// R
    g_pucMcuDdcciTxBuf[3] = pucTemp[1];
    g_pucMcuDdcciTxBuf[4] = pucTemp[2];// G
    g_pucMcuDdcciTxBuf[5] = pucTemp[3];
    g_pucMcuDdcciTxBuf[6] = pucTemp[4];// B
    g_pucMcuDdcciTxBuf[7] = pucTemp[5];
    g_pucMcuDdcciTxBuf[8] = UserCommonDdcciCalCheckSum();// CYShih, 8

    // ScalerMcuDdcciSendData(g_pucDdcciTxBuf);
    ScalerMcuDdcciSendData(GET_RUN_DDCCI_HANDLE_CHANNEL(), g_pucMcuDdcciTxBuf);

    SET_INTERRUPT_ENABLE_STATUS(_INT_EXINT_1, _ENABLE);
}
//--------------------------------------------------
// Description  : Reply the RGB x, y to uniformity tool
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonColorCalibrationReplyFastModeData(void)
{
    BYTE pucTemp[14] = {0};

    UserCommonFlashRead(_OGC_FLASH_BANK, ((WORD)_OGC_FLASH_PAGE << 12 | _EDID_INFO_ADDRESS), 14, pucTemp);

    g_pucMcuDdcciTxBuf[_DDCCI_SOURCE] = _DDCCI_DEST_ADDRESS;
    g_pucMcuDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | 0x0A;
    g_pucMcuDdcciTxBuf[2] = pucTemp[4];// rx, ry, gx, gy, 2 lsb
    g_pucMcuDdcciTxBuf[3] = pucTemp[5];// bx, by, wx, wy, 2 lsb
    g_pucMcuDdcciTxBuf[4] = pucTemp[6];// rx, 8msb
    g_pucMcuDdcciTxBuf[5] = pucTemp[7];// ry, 8msb
    g_pucMcuDdcciTxBuf[6] = pucTemp[8];// gx, 8msb
    g_pucMcuDdcciTxBuf[7] = pucTemp[9];// gy, 8msb
    g_pucMcuDdcciTxBuf[8] = pucTemp[10];// bx, 8msb
    g_pucMcuDdcciTxBuf[9] = pucTemp[11];// by, 8msb
    g_pucMcuDdcciTxBuf[10] = pucTemp[12];// wx, 8msb
    g_pucMcuDdcciTxBuf[11] = pucTemp[13];// wy, 8msb
    g_pucMcuDdcciTxBuf[12] = UserCommonDdcciCalCheckSum();

    ScalerMcuDdcciSendData(GET_RUN_DDCCI_HANDLE_CHANNEL(), g_pucMcuDdcciTxBuf);
    // ScalerMcuDdcciSendData(GET_RUN_DDCCI_HANDLE_CHANNEL(), g_pucDdcciTxBuf);

    SET_INTERRUPT_ENABLE_STATUS(_INT_EXINT_1, _ENABLE);
}
//--------------------------------------------------
// Description  : Reply uniformity level mode to uniformity tool
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonColorCalibrationReplyUniformityLevelMode(void)
{
    g_pucMcuDdcciTxBuf[_DDCCI_SOURCE] = _DDCCI_DEST_ADDRESS;
    g_pucMcuDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | 0x03;
    g_pucMcuDdcciTxBuf[2] = (_UNIFORMITY_1ST_TABLE_LEVEL << 4) | _UNIFORMITY_2ND_TABLE_LEVEL;
    g_pucMcuDdcciTxBuf[3] = (_UNIFORMITY_3RD_TABLE_LEVEL << 4) | _UNIFORMITY_4TH_TABLE_LEVEL;
    g_pucMcuDdcciTxBuf[4] = (_UNIFORMITY_5TH_TABLE_LEVEL << 4) | _UNIFORMITY_6TH_TABLE_LEVEL;

    g_pucMcuDdcciTxBuf[5] = UserCommonDdcciCalCheckSum();

    ScalerMcuDdcciSendData(GET_RUN_DDCCI_HANDLE_CHANNEL(), g_pucMcuDdcciTxBuf);

    SET_INTERRUPT_ENABLE_STATUS(_INT_EXINT_1, _ENABLE);
}

//--------------------------------------------------
// Description  : Reply uniformity level mode to  new uniformity tool
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonColorCalibrationReplyUniformityNewLevelMode(void)
{
    g_pucMcuDdcciTxBuf[_DDCCI_SOURCE] = _DDCCI_DEST_ADDRESS;
    g_pucMcuDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | 0x0A;
    g_pucMcuDdcciTxBuf[2] = (_UNIFORMITY_1ST_TABLE_LEVEL << 4) | _UNIFORMITY_2ND_TABLE_LEVEL;
    g_pucMcuDdcciTxBuf[3] = (_UNIFORMITY_3RD_TABLE_LEVEL << 4) | _UNIFORMITY_4TH_TABLE_LEVEL;
    g_pucMcuDdcciTxBuf[4] = (_UNIFORMITY_5TH_TABLE_LEVEL << 4) | _UNIFORMITY_6TH_TABLE_LEVEL;
    g_pucMcuDdcciTxBuf[5] = (_UNIFORMITY_7TH_TABLE_LEVEL << 4) | _UNIFORMITY_8TH_TABLE_LEVEL;
    g_pucMcuDdcciTxBuf[6] = (_UNIFORMITY_9TH_TABLE_LEVEL << 4);
    g_pucMcuDdcciTxBuf[7] = 0;
    g_pucMcuDdcciTxBuf[8] = 0;
    g_pucMcuDdcciTxBuf[9] = 0;
    g_pucMcuDdcciTxBuf[10] = 0;
    g_pucMcuDdcciTxBuf[11] = 0;

    g_pucMcuDdcciTxBuf[12] = UserCommonDdcciCalCheckSum();

    ScalerMcuDdcciSendData(GET_RUN_DDCCI_HANDLE_CHANNEL(), g_pucMcuDdcciTxBuf);

    SET_INTERRUPT_ENABLE_STATUS(_INT_EXINT_1, _ENABLE);
}

#if(_UNIFORMITY_PLUS_FUNCTION == _ON)
//--------------------------------------------------
// Description  : Calibration set Gamma Table in Post Gamma
// Input Value  : ucColorGammaBankNum, usColorGammaAddr
// Output Value : None
//--------------------------------------------------
void UserCommonColorCalibrationSetPostGammaTable(BYTE ucColorGammaBankNum, BYTE *pucColorGammaAddr, EnumDBApply enumDBApply)
{
    ScalerColorPostGammaEnable(_1P_NORMAL_REGION, _FUNCTION_OFF);
#if(_PCM_FULL_TIME_FUNCTION == _ON)
    ScalerColorPCMInputGammaEnable(_FUNCTION_ON);
    ScalerColorPCMSetPCMMode(_1P_NORMAL_REGION, _PCM_MODE);
    ScalerColorPCMInputGammaRegionEnable(_1P_NORMAL_REGION, _DB_APPLY_NONE, _OFF, _PCM_HLW_DB_A_OR_B);
    ScalerColorPCMPostGammaAdjust(_1P_NORMAL_REGION, pucColorGammaAddr, ucColorGammaBankNum);
    ScalerColorPCMPostGammaRegionEnable(_1P_NORMAL_REGION, enumDBApply, _ON);
#else
#if(_PCM_FUNCTION == _ON)
    ScalerColorPCMInputGammaEnable(_FUNCTION_OFF);
    ScalerColorPCMSetPCMMode(_1P_NORMAL_REGION, _OGC_MODE);
#endif
    ScalerColorPostGammaAdjust(_1P_NORMAL_REGION, pucColorGammaAddr, ucColorGammaBankNum);
    ScalerColorPostGammaRegionEnable(_1P_NORMAL_REGION, enumDBApply, _ON);
#endif
    ScalerColorPostGammaEnable(_1P_NORMAL_REGION, _FUNCTION_ON);
}
#endif // End of #if(_UNIFORMITY_PLUS_FUNCTION == _ON)
#endif // End of #if(_UNIFORMITY_SUPPORT == _ON)

#if(_BACKLIGHT_DIMMING_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Reply panel define
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonColorCalibrationReplyDimmingDefine(void)
{
#if(_GLOBAL_DIMMING_FUNCTION == _ON)
    if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_DIMMING_INDEX] == _DDCCI_DISP_DIMMING_TYPE_GLOBAL)
    {
#if(_DEVICE_LED_DRIVER_TYPE != _DEVICE_LED_DRIVER_NONE)
        g_pucMcuDdcciTxBuf[_DDCCI_SOURCE] = _DDCCI_DEST_ADDRESS;
        g_pucMcuDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | 0x06;
        g_pucMcuDdcciTxBuf[2] = (BYTE)(_DEVICE_LED_DRIVER_PWM_MAX / 256);
        g_pucMcuDdcciTxBuf[3] = (BYTE)(_DEVICE_LED_DRIVER_PWM_MAX);
        g_pucMcuDdcciTxBuf[4] = (BYTE)(_DEVICE_LED_DRIVER_PWM_MIN / 256);
        g_pucMcuDdcciTxBuf[5] = (BYTE)(_DEVICE_LED_DRIVER_PWM_MIN);
        g_pucMcuDdcciTxBuf[6] = _HDR10_SUPPORT;
        g_pucMcuDdcciTxBuf[7] = _FREESYNC_II_SUPPORT;
        g_pucMcuDdcciTxBuf[8] = UserCommonDdcciCalCheckSum();
#elif(_DEVICE_LED_DRIVER_TYPE == _DEVICE_LED_DRIVER_NONE)
        WORD usPWMMax = UserInterfaceColorGlobalDimmingGetMaxPWM();
        WORD usPWMMin = UserInterfaceColorGlobalDimmingGetMinPWM();
        g_pucMcuDdcciTxBuf[_DDCCI_SOURCE] = _DDCCI_DEST_ADDRESS;
        g_pucMcuDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | 0x06;
        g_pucMcuDdcciTxBuf[2] = (BYTE)(usPWMMax / 256);
        g_pucMcuDdcciTxBuf[3] = (BYTE)(usPWMMax);
        g_pucMcuDdcciTxBuf[4] = (BYTE)(usPWMMin / 256);
        g_pucMcuDdcciTxBuf[5] = (BYTE)(usPWMMin);
        g_pucMcuDdcciTxBuf[6] = _HDR10_SUPPORT;
        g_pucMcuDdcciTxBuf[7] = _FREESYNC_II_SUPPORT;
        g_pucMcuDdcciTxBuf[8] = UserCommonDdcciCalCheckSum();
#endif
    }
#endif // endif(_GLOBAL_DIMMING_SUPPORT == _ON)
    ScalerMcuDdcciSendData(GET_RUN_DDCCI_HANDLE_CHANNEL(), g_pucMcuDdcciTxBuf);
    SET_INTERRUPT_ENABLE_STATUS(_INT_EXINT_1, _ENABLE);
}


//--------------------------------------------------
// Description  : Set scaler PWM value
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonColorCalibrationSetPWMValue(void)
{
#if(_GLOBAL_DIMMING_FUNCTION == _ON)
    if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_DIMMING_INDEX] == _DDCCI_DISP_DIMMING_TYPE_GLOBAL)
    {
        WORD usPWM = 0;
        usPWM = (g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_DIMMING_DATA_START] << 8) +
                (g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_DIMMING_DATA_START + 1]);
        UserCommonColorGlobalDimmingSetPWMValue(usPWM);
    }
#endif // endif(_LOCAL_DIMMING_SUPPORT == _ON)
}

#endif
#if(_OCC_PCM_GAMMA_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set OCC PCM Gamm
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonColorCalibrationSetOCCPCMGamma(void)
{
    ScalerColorPCMInputGamma129NodeAdjust(_1P_NORMAL_REGION, ScalerColorOCCPCMGammaGetTableAddress(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_GAMMA_INDEX]), ScalerColorPCMGetTableBank(), _IG_DB_DISABLE);

    // Set PCM MODE
    ScalerColorPCMSetPCMMode(_1P_NORMAL_REGION, _PCM_MODE);

#if(_TWO_BRI_CALIBRATION_TYPE < _TWO_BRI_CALIBRATION_OGC_OCC_DICOM_HDR)
    ScalerColorPCMOutputGammaAdjust(_1P_NORMAL_REGION, g_pucColorDISP_CALIBRATION_FLASH + _OCC_GAMMA10_ADDRESS, _OCC_GAMMA_FLASH_BANK);
    // Set PCM Color Matrix
    if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_CT_INDEX] == _OCC_PCM_GAMMA_CT_MODE1)
    {
        ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _SRGB_1_BIT_SHIFT_LEFT, g_pucColorDISP_CALIBRATION_FLASH + _OCC_USERDEFINE_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
    }
    else if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_CT_INDEX] == _OCC_PCM_GAMMA_CT_MODE2)
    {
        ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _SRGB_1_BIT_SHIFT_LEFT, g_pucColorDISP_CALIBRATION_FLASH + _OCC_USERDEFINE2_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
    }
    else if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_CT_INDEX] == _OCC_PCM_GAMMA_CT_MODE3)
    {
        ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _SRGB_1_BIT_SHIFT_LEFT, g_pucColorDISP_CALIBRATION_FLASH + _OCC_USERDEFINE3_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
    }
    else if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_CT_INDEX] == _OCC_PCM_GAMMA_CT_MODE4)
    {
        ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _SRGB_1_BIT_SHIFT_LEFT, g_pucColorDISP_CALIBRATION_FLASH + _OCC_USERDEFINE4_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
    }
    else if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_CT_INDEX] == _OCC_PCM_GAMMA_CT_MODE5)
    {
        ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _SRGB_1_BIT_SHIFT_LEFT, g_pucColorDISP_CALIBRATION_FLASH + _OCC_USERDEFINE5_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
    }
    else // _PCM_GAMMA_CT_MODE6
    {
        ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _SRGB_1_BIT_SHIFT_LEFT, g_pucColorDISP_CALIBRATION_FLASH + _OCC_USERDEFINE6_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
    }

#else
    ScalerColorPCMOutputGammaAdjust(_1P_NORMAL_REGION, g_pucColorDISP_CALIBRATION_FLASH + _OCC_GAMMA10_ADDRESS + (g_ucColorBacklightFlag * _OCC_GAMMA_TABLE_SIZE), _OCC_GAMMA_FLASH_BANK);

    // Set PCM Color Matrix
    if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_CT_INDEX] == _OCC_PCM_GAMMA_CT_MODE1)
    {
        ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _SRGB_1_BIT_SHIFT_LEFT, g_pucColorDISP_CALIBRATION_FLASH + _OCC_USERDEFINE_ADDRESS + (g_ucColorBacklightFlag * _OCC_COLOR_MATRIX_TOTAL_SPACE), _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
    }
    else if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_CT_INDEX] == _OCC_PCM_GAMMA_CT_MODE2)
    {
        ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _SRGB_1_BIT_SHIFT_LEFT, g_pucColorDISP_CALIBRATION_FLASH + _OCC_USERDEFINE2_ADDRESS + (g_ucColorBacklightFlag * _OCC_COLOR_MATRIX_TOTAL_SPACE), _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
    }
    else if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_CT_INDEX] == _OCC_PCM_GAMMA_CT_MODE3)
    {
        ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _SRGB_1_BIT_SHIFT_LEFT, g_pucColorDISP_CALIBRATION_FLASH + _OCC_USERDEFINE3_ADDRESS + (g_ucColorBacklightFlag * _OCC_COLOR_MATRIX_TOTAL_SPACE), _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
    }
    else if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_CT_INDEX] == _OCC_PCM_GAMMA_CT_MODE4)
    {
        ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _SRGB_1_BIT_SHIFT_LEFT, g_pucColorDISP_CALIBRATION_FLASH + _OCC_USERDEFINE4_ADDRESS + (g_ucColorBacklightFlag * _OCC_COLOR_MATRIX_TOTAL_SPACE), _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
    }
    else if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_CT_INDEX] == _OCC_PCM_GAMMA_CT_MODE5)
    {
        ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _SRGB_1_BIT_SHIFT_LEFT, g_pucColorDISP_CALIBRATION_FLASH + _OCC_USERDEFINE5_ADDRESS + (g_ucColorBacklightFlag * _OCC_COLOR_MATRIX_TOTAL_SPACE), _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
    }
    else // _PCM_GAMMA_CT_MODE6
    {
        ScalerColorPCMSRGBAdjust(_1P_NORMAL_REGION, _SRGB_1_BIT_SHIFT_LEFT, g_pucColorDISP_CALIBRATION_FLASH + _OCC_USERDEFINE6_ADDRESS + (g_ucColorBacklightFlag * _OCC_COLOR_MATRIX_TOTAL_SPACE), _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
    }
#endif

    ScalerColorOutputGammaEnable(_FUNCTION_ON);
    if(g_pucMcuDdcciRxBuf[_DDCCI_DISP_CALIB_CT_INDEX] != 0x0F)
    {
        ScalerColorSRGBEnable(_FUNCTION_ON);
    }
    ScalerColorPCMInputGammaEnable(_FUNCTION_ON);
}
#endif // End of #if(_OCC_PCM_GAMMA_SUPPORT== _ON)
//--------------------------------------------------
// Description  : Calculate the checksum of Gamma in Flash
// Input Value  : ucColorGammaBankNum, usColorGammaAddr, bOCCMode
// Output Value : Checksum
//--------------------------------------------------
BYTE UserCommonColorCalibrationCalGammaCheckSum(BYTE ucColorGammaBankNum, WORD usColorGammaAddr, bit bOCCMode)
{
    pData[5] = 0;
    WORD usI = 0;
    WORD usJ = 0;
    WORD usStep = 8;

#if(_OGC_NO_INTERPOLATION_SUPPORT == _ON)
    usStep = 2;
#endif
    if(bOCCMode == _TRUE)
    {
        for(usJ = 0; usJ < 3; usJ++)
        {
            for(usI = 0; usI < 148; usI++)
            {
                UserCommonFlashRead(ucColorGammaBankNum, ((DWORD)usColorGammaAddr + usJ * 2200 + usI), 1, pData + 2);
                pData[5] += pData[2];
            }

            for(usI = 164; usI < 2200; usI = usI + usStep)
            {
                UserCommonFlashRead(ucColorGammaBankNum, ((DWORD)usColorGammaAddr + usJ * 2200 + usI), 2, pData + 2);
                pData[5] += pData[2];
                pData[5] += pData[3];
            }
        }
    }
    else
    {
        for(usJ = 0; usJ < 3; usJ++)
        {
            for(usI = 0; usI < _OGC_GAMMA_TABLE_LENGTH; usI = usI + usStep)
            {
                UserCommonFlashRead(ucColorGammaBankNum, ((DWORD)usColorGammaAddr + usJ * _OGC_GAMMA_TABLE_LENGTH + usI), 2, pData + 2);
                pData[5] += pData[2];
                pData[5] += pData[3];
            }
        }
    }
    return pData[5];
}

//--------------------------------------------------
// Description  : Calibration set Gamma Table
// Input Value  : ucColorGammaBankNum, usColorGammaAddr
// Output Value : None
//--------------------------------------------------
void UserCommonColorCalibrationSetGammaTable(BYTE ucColorGammaBankNum, BYTE *pucColorGammaAddr, EnumDBApply enumDBApply)
{
    ScalerColorOutputGammaEnable(_FUNCTION_OFF);
#if(_PCM_FULL_TIME_FUNCTION == _ON)
    ScalerColorPCMInputGammaEnable(_FUNCTION_ON);
    ScalerColorPCMSetPCMMode(_1P_NORMAL_REGION, _PCM_MODE);
    ScalerColorPCMOutputGammaAdjust(_1P_NORMAL_REGION, pucColorGammaAddr, ucColorGammaBankNum);
    ScalerColorPCMInputGammaRegionEnable(_1P_NORMAL_REGION, _DB_APPLY_NONE, _OFF, _PCM_HLW_DB_A_OR_B);
    ScalerColorPCMOutputGammaRegionEnable(_1P_NORMAL_REGION, enumDBApply, _ON);
#else
#if(_PCM_FUNCTION == _ON)
    ScalerColorPCMInputGammaEnable(_FUNCTION_OFF);
    ScalerColorPCMSetPCMMode(_1P_NORMAL_REGION, _OGC_MODE);
#endif
    ScalerColorOutputGammaAdjust(_1P_NORMAL_REGION, pucColorGammaAddr, ucColorGammaBankNum);
    ScalerColorGammaRegionEnable(_1P_NORMAL_REGION, enumDBApply, _ON);
#endif
    ScalerColorOutputGammaEnable(_FUNCTION_ON);
}

//--------------------------------------------------
// Description  : Bypass Color IP
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonColorCalibrationIPBypass(void)
{
    ScalerTimerWaitForDDomainEvent(_EVENT_DEN_STOP);
#if(_COLOR_IP_LOCAL_CONTRAST == _ON)
    ScalerColorLocalContrastEnable(_1P_NORMAL_REGION, _LOCAL_CONTRAST_ALL_FUNCTION_OFF);
#endif
#if(_COLOR_IP_DCC == _ON)
    ScalerColorDCCEnable(_FUNCTION_OFF);
#endif
#if(_COLOR_IP_ICM == _ON)
    ScalerColorICMEnable(_FUNCTION_OFF);
#endif
#if(_COLOR_IP_CONTRAST == _ON)
    ScalerColorContrastEnable(_FUNCTION_OFF);
#endif
#if(_COLOR_IP_BRIGHTNESS == _ON)
    ScalerColorBrightnessEnable(_FUNCTION_OFF);
#endif
#if(_COLOR_IP_IAPS == _ON)
    ScalerColorIAPSGainEnable(_FUNCTION_OFF);
#endif
#if(_COLOR_IP_RGB_3D_GAMMA == _ON)
    ScalerColorRGB3DGammaEnable(_FUNCTION_OFF);
#endif
#if(_COLOR_IP_I_GAMMA == _ON)
    ScalerColorPCMRegionEnable(_1P_NORMAL_REGION, _DB_APPLY_NONE, _OFF);
    ScalerColorPCMInputGammaEnable(_FUNCTION_OFF);
#if(_PCM_FULL_TIME_FUNCTION == _ON)
    ScalerColorPCMSetPCMMode(_1P_NORMAL_REGION, _PCM_MODE);
#else
    ScalerColorPCMSetPCMMode(_1P_NORMAL_REGION, _OGC_MODE);
#endif
#endif
#if(_COLOR_IP_YMAPPING == _ON)
    ScalerColorYMappingEnable(_1P_NORMAL_REGION, _FUNCTION_OFF);
#endif
#if(_COLOR_IP_SRGB == _ON)
    ScalerColorSRGBEnable(_FUNCTION_OFF);
#endif
#if(_COLOR_IP_P_GAMMA == _ON)
    ScalerColorPostGammaEnable(_1P_NORMAL_REGION, _FUNCTION_OFF);
#endif
#if(_COLOR_IP_LOCAL_DIMMING == _ON)
    ScalerColorLDBLModelEnable(_FUNCTION_OFF);
#endif
#if(_COLOR_IP_UNIFORMITY == _ON)
    ScalerColorPanelUniformityRegionEnable(_1P_NORMAL_REGION, _DB_APPLY_NONE, _OFF);
#endif
#if(_COLOR_IP_O_GAMMA == _ON)
    ScalerColorGammaRegionEnable(_1P_NORMAL_REGION, _DB_APPLY_NONE, _OFF);
    ScalerColorOutputGammaEnable(_FUNCTION_OFF);
#endif
#if(_COLOR_IP_COLOR_CONVERT == _ON)
    ScalerColorSpaceConvertDDomainEnable(_DISPLAY_RGN_1P, _OFF);
#else
    ScalerGlobalDDomainDBApply(_D_DOMAIN_DB_APPLY_REGION_EITHER, _DB_APPLY_POLLING);
#endif
}
#endif // End of #if((_OGC_SUPPORT == _ON) || (_OCC_SUPPORT == _ON) || (_OGC_DICOM_SUPPORT == _ON) || (_UNIFORMITY_SUPPORT == _ON))
