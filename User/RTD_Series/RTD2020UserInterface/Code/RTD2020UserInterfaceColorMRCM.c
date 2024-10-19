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
// ID Code      : RTD2020UserInterfaceColorMRCM.c
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_INTERFACE_COLOR_MRCM__

#include "RTD2020UserInclude.h"
#include "RTD2020UserInterfaceColorMRCM.h"

#if(_OSD_TYPE == _REALTEK_2020_OSD)

//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
#if(_MRCM_SUPPORT == _ON)
QWORD g_puqColorMRCMAccR[4] = {0};
QWORD g_puqColorMRCMAccG[4] = {0};
QWORD g_puqColorMRCMAccB[4] = {0};

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : MRCM User Setting
// Input Value  : MRCM statistic region struct
// Output Value : NONE
//--------------------------------------------------
void UserInterfaceColorMRCMGetData(StructMRCMLoopData *pstMRCMLoopUserData)
{
    if(GET_OSD_CROSSHAIR() != _CROSSHAIR_OFF)
    {
        // |H_STEP |
        // -------------------------_
        // |       |   |   |       |
        // |   0   |   1   |   2   | V_STEP
        // |       |   |   |       |_
        // -------------------------
        // |       |       |       |
        // | --3-- |   4   | --5-- |
        // |       |       |       |
        // -------------------------
        // |       |   |   |       |
        // |   6   |   7   |   8   |
        // |       |   |   |       |
        // -------------------------
        //
        // index 4 = usH/Vposition (center point)
        WORD usHposition = (50 * _PANEL_DH_WIDTH) / 100 - 1; // defalt nine-square division center position, ex: FHD => 0~1919
        WORD usVposition = (50 * _PANEL_DV_HEIGHT) / 100 - 1;
        if(GET_OSD_CROSSHAIR() == _CROSSHAIR_POSITION)
        {
            usHposition = (GET_OSD_HPOS() * (_PANEL_DH_WIDTH - (_OSD_CROSSHAIR_WIDTH * _FONT_WIDTH))) / 100 - 1 + (_OSD_CROSSHAIR_WIDTH * _FONT_WIDTH / 2); // nine-square division center position, ex: FHD => 0~1919
            usVposition = (GET_OSD_VPOS() * (_PANEL_DV_HEIGHT - (_OSD_CROSSHAIR_HEIGHT * _FONT_HEIGHT))) / 100 - 1 + (_OSD_CROSSHAIR_HEIGHT * _FONT_HEIGHT / 2);
        }
        // (_MRCM_H_STEP + _MRCM_H_STEP / 2) - 1 <= usHposition <= _PANEL_DH_WIDTH - (_MRCM_H_STEP + _MRCM_H_STEP / 2) - 1
        usHposition = MINOF(_PANEL_DH_WIDTH - (_MRCM_CROSSHAIR_H_STEP + _MRCM_CROSSHAIR_H_STEP / 2) - 1, MAXOF(usHposition, (_MRCM_CROSSHAIR_H_STEP + _MRCM_CROSSHAIR_H_STEP / 2) - 1));
        usVposition = MINOF(_PANEL_DV_HEIGHT - (_MRCM_CROSSHAIR_V_STEP + _MRCM_CROSSHAIR_V_STEP / 2) - 1, MAXOF(usVposition, (_MRCM_CROSSHAIR_V_STEP + _MRCM_CROSSHAIR_V_STEP / 2) - 1));
        pstMRCMLoopUserData->ucMRCMLoopNum = 1;
        pstMRCMLoopUserData->pstMRCMData[0].uch_num = 3; // nine-square division
        pstMRCMLoopUserData->pstMRCMData[0].ucv_num = 3;
        pstMRCMLoopUserData->pstMRCMData[0].usb_thd1 = 0;
        pstMRCMLoopUserData->pstMRCMData[0].usstart_pixel_h = (usHposition + 1) - (_MRCM_CROSSHAIR_H_STEP + _MRCM_CROSSHAIR_H_STEP / 2); // End - Start + 1 = step
        pstMRCMLoopUserData->pstMRCMData[0].usstart_pixel_v = (usVposition + 1) - (_MRCM_CROSSHAIR_V_STEP + _MRCM_CROSSHAIR_V_STEP / 2);
        pstMRCMLoopUserData->pstMRCMData[0].usend_pixel_h = (usHposition + 1) + (_MRCM_CROSSHAIR_H_STEP + _MRCM_CROSSHAIR_H_STEP / 2); // End - Start + 1 = step
        pstMRCMLoopUserData->pstMRCMData[0].usend_pixel_v = (usVposition + 1) + (_MRCM_CROSSHAIR_V_STEP + _MRCM_CROSSHAIR_V_STEP / 2);
        pstMRCMLoopUserData->pstMRCMData[0].ush_offset_l = _MRCM_CROSSHAIR_H_STEP;
        pstMRCMLoopUserData->pstMRCMData[0].ush_offset_r = _MRCM_CROSSHAIR_H_STEP;
        pstMRCMLoopUserData->pstMRCMData[0].usv_offset_t = _MRCM_CROSSHAIR_V_STEP;
        pstMRCMLoopUserData->pstMRCMData[0].usv_offset_b = _MRCM_CROSSHAIR_V_STEP;
        pstMRCMLoopUserData->pstMRCMData[0].ush_step = _MRCM_CROSSHAIR_H_STEP;
        pstMRCMLoopUserData->pstMRCMData[0].usv_step = _MRCM_CROSSHAIR_V_STEP;
    }
}

//--------------------------------------------------
// Description  : MRCM User read result
// Input Value  : NONE
// Output Value : NONE
//--------------------------------------------------
void UserInterfaceColorMRCMReadResult(void)
{
    BYTE ucTemp = 0;
    for(ucTemp = 0; ucTemp < 4; ucTemp++) // read region 1, 3, 5, 7 => coresponding to up, left, right, down
    {
        UserCommonColorMRCMRegionSelect(ucTemp * 2 + 1);
        g_puqColorMRCMAccR[ucTemp] = UserCommonColorMRCMReadResult(_MRCM_ABOVE_TH1_VAL_R);
        g_puqColorMRCMAccG[ucTemp] = UserCommonColorMRCMReadResult(_MRCM_ABOVE_TH1_VAL_G);
        g_puqColorMRCMAccB[ucTemp] = UserCommonColorMRCMReadResult(_MRCM_ABOVE_TH1_VAL_B);
    }
}
//--------------------------------------------------
// Description  : MRCM User Application
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceColorMRCMApplication(void)
{
    if((GET_OSD_CROSSHAIR() != _CROSSHAIR_OFF) && (GET_OSD_CROSSHAIR_SHOW() == _TRUE))
    {
        for(BYTE ucTemp = 0; ucTemp < 4; ucTemp++)
        {
            BYTE ucCrosshairR = (g_puqColorMRCMAccR[ucTemp] / _MRCM_CROSSHAIR_REGION_PIXEL_NUM) >> 6; // 14 bits >> 6, for OSD 8 bits Color
            BYTE ucCrosshairG = (g_puqColorMRCMAccG[ucTemp] / _MRCM_CROSSHAIR_REGION_PIXEL_NUM) >> 6;
            BYTE ucCrosshairB = (g_puqColorMRCMAccB[ucTemp] / _MRCM_CROSSHAIR_REGION_PIXEL_NUM) >> 6;
            UserCommonOsdSetColorPalette(ucTemp, ~ucCrosshairR, ~ucCrosshairG, ~ucCrosshairB); // draw up, left, right, down
        }
    }
}
#endif // End of #if(_MRCM_SUPPORT == _ON)
#endif // End of #if(_OSD_TYPE == _REALTEK_2020_OSD)

