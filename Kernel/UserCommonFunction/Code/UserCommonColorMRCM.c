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
// ID Code      : UserCommonColorMRCM.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_COMMON_COLOR_MRCM__

#include "UserCommonInclude.h"
#include "ColorMRCM/UserCommonColorMRCM.h"

#if(_COLOR_IP_MRCM == _ON)

//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
bit g_bColorMRCMSramNotEmpty = _FALSE;
BYTE g_ucColorMRCMLoopCounter = 0;
EnumMRCMSet g_enumColorMRCMDataReadySet = _MRCM_SET_NONE;
EnumMRCMKernelSet g_enumColorMRCMKernelDataReadySet = _MRCM_KERNEL_SET_NONE;
bit g_bColorMRCMReadResultDone = _FALSE;
BYTE g_ucColorMRCMCurrentLoopNum = 0;
StructMRCMLoopData g_stColorMRCMLoopUserData;
StructMRCMLoopData g_stColorMRCMLoopKernelData;
EnumMRCMCase g_enumColorMRCMCase = _MRCM_OFF;
#if(_DYNAMIC_LOWBLUE_FUNCTION == _ON)
WORD g_ppusColorMrcmHazardRegion[_LOWBLUE_MRCM_HOR_DIVISION * _LOWBLUE_MRCM_VER_DIVISION][_AVE_FILTER_FRAME_NUM] = {0};
WORD g_pusColorCurrentGainB[_LOWBLUE_MRCM_HOR_DIVISION * _LOWBLUE_MRCM_VER_DIVISION] = {0};
BYTE g_ucColorFrameIndex = 0;
WORD g_pusColorHazardFrameBuffer[_LOWBLUE_MRCM_HOR_DIVISION * _LOWBLUE_MRCM_VER_DIVISION] = {0};
#endif
//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : MRCM main flow
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonColorMRCMHandler(void)
{
    if(ScalerColorMRCMReadyToRead() == _TRUE)
    {
        if(GET_MRCM_SRAM_NOT_EMPTY() == _TRUE)
        {
            if(g_ucColorMRCMLoopCounter >= GET_MRCM_USER_DATA_LOOP_NUM())
            {
                EnumMRCMKernelSet enumMRCMKernelSet = (EnumMRCMKernelSet)(g_ucColorMRCMLoopCounter - GET_MRCM_USER_DATA_LOOP_NUM());
                SET_MRCM_READY_SET(_MRCM_SET_NONE);
                SET_MRCM_READY_KERNEL_SET(enumMRCMKernelSet);
            }
            else
            {
                SET_MRCM_READY_KERNEL_SET(_MRCM_KERNEL_SET_NONE);
                SET_MRCM_READY_SET(g_ucColorMRCMLoopCounter);
            }
            UserCommonColorMRCMCaseReadResult();
            if(GET_MRCM_READ_RESULT_DONE() == _TRUE)
            {
                UserCommonColorMRCMApplication();
                CLR_MRCM_READ_RESULT_DONE();
            }
            else
            {
                return;
            }
        }
        else
        {
            SET_MRCM_SRAM_NOT_EMPTY();
        }
        UserCommonColorMRCMLoopSetting();
        ScalerColorMRCMSramSel(!(ScalerColorMRCMGetSramNumber()));
        ScalerColorMRCMApply();
    }
}

//--------------------------------------------------
// Description  : According to loopcounter and MRCMsetting, next setting will be decided
// Input Value  : MRCM statistic region struct
// Output Value : None
//--------------------------------------------------
void UserCommonColorMRCMLoopSetting(void)
{
    BYTE ucMRCMLoopNum = GET_MRCM_CURRENT_LOOP_NUM();

    if(GET_MRCM_USER_DATA_LOOP_NUM() != 0)
    {
        BYTE ucSettingIndex = (g_ucColorMRCMLoopCounter + 2) % ucMRCMLoopNum;
        if(ucSettingIndex >= GET_MRCM_USER_DATA_LOOP_NUM())
        {
            ucSettingIndex -= GET_MRCM_USER_DATA_LOOP_NUM();
            UserCommonColorMRCMSetting(&(g_stColorMRCMLoopKernelData.pstMRCMData[ucSettingIndex]));
        }
        else
        {
            UserCommonColorMRCMSetting(&(g_stColorMRCMLoopUserData.pstMRCMData[ucSettingIndex]));
        }
    }

    g_ucColorMRCMLoopCounter = (g_ucColorMRCMLoopCounter + 1) % ucMRCMLoopNum;
}

//--------------------------------------------------
// Description  : Reset MRCM global variable to default value
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonColorMRCMDefaultSetting(void)
{
    CLR_MRCM_SRAM_NOT_EMPTY();
    g_ucColorMRCMLoopCounter = 0;
    SET_MRCM_READY_SET(_MRCM_SET_NONE);
    CLR_MRCM_READ_RESULT_DONE();
    SET_MRCM_CURRENT_LOOP_NUM(0);
    ScalerColorMRCMSramSel(0);
}

//--------------------------------------------------
// Description  : Set MRCM data
// Input Value  : MRCM statistic region struct
// Output Value : None
//--------------------------------------------------
void UserCommonColorMRCMSetting(StructMRCMData *pstMRCMData)
{
    ScalerColorMRCMSetting(pstMRCMData);
}

//--------------------------------------------------
// Description  : Read MRCM result
// Input Value  : data type
// Output Value : Get specific data
//--------------------------------------------------
QWORD UserCommonColorMRCMReadResult(EnumMRCMReadResultOption enumMRCMReadResultOption)
{
    return ScalerColorMRCMReadResult(enumMRCMReadResultOption);
}

//--------------------------------------------------
// Description  : MRCM Ajust and set first MRCM setting
// Input Value  : Reset MRCM. If user application changes, set as bMRCMSettingReset _TRUE.
// ex: application1 => application2 or application1 => using application1 and application2 at the same time
// Output Value : None
//--------------------------------------------------
void UserCommonColorMRCMAdjust(void)
{
    StructMRCMSetting stMRCMSetting;
    memset(&stMRCMSetting, 0, sizeof(stMRCMSetting));
    memset(&g_stColorMRCMLoopUserData, 0, sizeof(StructMRCMLoopData));
    memset(&g_stColorMRCMLoopKernelData, 0, sizeof(StructMRCMLoopData));

    UserCommonColorMRCMGetData(&stMRCMSetting);

    memcpy(&g_stColorMRCMLoopUserData, &(stMRCMSetting.stMRCMSettingData.stMRCMLoopUserData), sizeof(StructMRCMLoopData));
    memcpy(&g_stColorMRCMLoopKernelData, &(stMRCMSetting.stMRCMSettingData.stMRCMLoopKernelData), sizeof(StructMRCMLoopData));

    if(((GET_MRCM_USER_DATA_LOOP_NUM() + GET_MRCM_KERNEL_DATA_LOOP_NUM()) < 1) ||
       (GET_MRCM_USER_DATA_LOOP_NUM() > _MRCM_SETTING_NUM) ||
       (GET_MRCM_KERNEL_DATA_LOOP_NUM() > _MRCM_SETTING_NUM))
    {
        stMRCMSetting.enumMRCMCase = _MRCM_OFF; // _MRCM_SETTING is out of range
    }
    else
    {
        stMRCMSetting.enumMRCMCase = _MRCM_ON;
    }

    switch(stMRCMSetting.enumMRCMCase)
    {
        case _MRCM_ON:
            SET_MRCM_CASE(_MRCM_ON);
            break;

        case _MRCM_OFF:
            SET_MRCM_CASE(_MRCM_OFF);
            break;

        default:
            stMRCMSetting.enumMRCMCase = _MRCM_OFF;
            SET_MRCM_CASE(_MRCM_OFF);
            break;
    }

    if(GET_MRCM_CASE() != _MRCM_OFF)
    {
        UserCommonColorMRCMEnable(_FUNCTION_OFF);
        if(GET_MRCM_USER_DATA_LOOP_NUM() > 0)
        {
            if(GET_MRCM_USER_DATA_LOOP_NUM() > 0)
            {
                UserCommonColorMRCMSetting(&(g_stColorMRCMLoopUserData.pstMRCMData[0]));
            }
            else
            {
                UserCommonColorMRCMSetting(&(g_stColorMRCMLoopKernelData.pstMRCMData[0]));
            }
        }
        else
        {
            UserCommonColorMRCMSetting(&(g_stColorMRCMLoopKernelData.pstMRCMData[0]));
        }
        UserCommonColorMRCMEnable(_FUNCTION_ON);
        SET_MRCM_CURRENT_LOOP_NUM((GET_MRCM_USER_DATA_LOOP_NUM() + GET_MRCM_KERNEL_DATA_LOOP_NUM()));
    }
    else
    {
        UserCommonColorMRCMEnable(_FUNCTION_OFF);
        UserCommonColorMRCMDefaultSetting();
    }
}

//--------------------------------------------------
// Description  : MRCM enable
// Input Value  : Enable
// Output Value : None
//--------------------------------------------------
void UserCommonColorMRCMEnable(EnumFunctionOnOFF enumOn)
{
    ScalerColorMRCMEnable(enumOn);
    if(enumOn == _FUNCTION_OFF)
    {
        UserCommonColorMRCMDefaultSetting();
    }
    else
    {
        ScalerColorMRCMPcmMode(_PCM_MODE);
        ScalerGlobalDDomainDBApply(_D_DOMAIN_DB_APPLY_REGION_EITHER, _DB_APPLY_POLLING);
    }
}

//--------------------------------------------------
// Description  : Get MRCM Setting
// Input Value  : MRCM statistic region struct
// Output Value : None
//--------------------------------------------------
void UserCommonColorMRCMGetData(StructMRCMSetting *pstMRCMSetting)
{
    BYTE ucMRCMKernelLoopNum = 0;
    BYTE ucMRCMCount = 0;
#if(_MRCM_SUPPORT == _ON)
    UserInterfaceColorMRCMGetData(&pstMRCMSetting->stMRCMSettingData.stMRCMLoopUserData);
#endif
    /*
    if(KERNEL_APPLICATION != _OFF)
    {
         Set pstMRCMSetting->stMRCMSettingData.stMRCMLoopKernelData.pstMRCMData[ucMRCMKernelLoopNum]
         ucLoopNumCount = ucLoopNumCount + 1;
    }
    */
#if(_DYNAMIC_LOWBLUE_FUNCTION == _ON)
    // force to low blue light application
    if(UserCommonColorGetLowBlueStatus() != _LOWBLUE_MODE_OFF)
    {
        // MRCM Setting0
        // DB parameter
        pstMRCMSetting->enumMRCMCase = _MRCM_ON;
        pstMRCMSetting->stMRCMSettingData.stMRCMLoopKernelData.pstMRCMData[ucMRCMKernelLoopNum].usstart_pixel_h = 0;
        pstMRCMSetting->stMRCMSettingData.stMRCMLoopKernelData.pstMRCMData[ucMRCMKernelLoopNum].usend_pixel_h = _PANEL_DH_WIDTH;
        pstMRCMSetting->stMRCMSettingData.stMRCMLoopKernelData.pstMRCMData[ucMRCMKernelLoopNum].usstart_pixel_v = 0;
        pstMRCMSetting->stMRCMSettingData.stMRCMLoopKernelData.pstMRCMData[ucMRCMKernelLoopNum].usend_pixel_v = _PANEL_DV_HEIGHT;
        pstMRCMSetting->stMRCMSettingData.stMRCMLoopKernelData.pstMRCMData[ucMRCMKernelLoopNum].uch_num = _LOWBLUE_MRCM_HOR_DIVISION; /// add define for low blue
        pstMRCMSetting->stMRCMSettingData.stMRCMLoopKernelData.pstMRCMData[ucMRCMKernelLoopNum].ucv_num = _LOWBLUE_MRCM_VER_DIVISION;
        pstMRCMSetting->stMRCMSettingData.stMRCMLoopKernelData.pstMRCMData[ucMRCMKernelLoopNum].ush_offset_l = (_PANEL_DH_WIDTH) / _LOWBLUE_MRCM_HOR_DIVISION;
        pstMRCMSetting->stMRCMSettingData.stMRCMLoopKernelData.pstMRCMData[ucMRCMKernelLoopNum].ush_offset_r = (_PANEL_DH_WIDTH) / _LOWBLUE_MRCM_HOR_DIVISION;
        pstMRCMSetting->stMRCMSettingData.stMRCMLoopKernelData.pstMRCMData[ucMRCMKernelLoopNum].ush_step = (_PANEL_DH_WIDTH) / _LOWBLUE_MRCM_HOR_DIVISION;
        pstMRCMSetting->stMRCMSettingData.stMRCMLoopKernelData.pstMRCMData[ucMRCMKernelLoopNum].usv_offset_t = (_PANEL_DV_HEIGHT) / _LOWBLUE_MRCM_VER_DIVISION;
        pstMRCMSetting->stMRCMSettingData.stMRCMLoopKernelData.pstMRCMData[ucMRCMKernelLoopNum].usv_offset_b = (_PANEL_DV_HEIGHT) / _LOWBLUE_MRCM_VER_DIVISION;
        pstMRCMSetting->stMRCMSettingData.stMRCMLoopKernelData.pstMRCMData[ucMRCMKernelLoopNum].usv_step = (_PANEL_DV_HEIGHT) / _LOWBLUE_MRCM_VER_DIVISION;
        pstMRCMSetting->stMRCMSettingData.stMRCMLoopKernelData.pstMRCMData[ucMRCMKernelLoopNum].usr_thd1 = 0;
        pstMRCMSetting->stMRCMSettingData.stMRCMLoopKernelData.pstMRCMData[ucMRCMKernelLoopNum].usg_thd1 = 0;
        pstMRCMSetting->stMRCMSettingData.stMRCMLoopKernelData.pstMRCMData[ucMRCMKernelLoopNum].usb_thd1 = 0;
        pstMRCMSetting->stMRCMSettingData.stMRCMLoopKernelData.pstMRCMData[ucMRCMKernelLoopNum].usrgb_thd1 = 0;
        pstMRCMSetting->stMRCMSettingData.stMRCMLoopKernelData.pstMRCMData[ucMRCMKernelLoopNum].usr_thd2 = 10000;
        pstMRCMSetting->stMRCMSettingData.stMRCMLoopKernelData.pstMRCMData[ucMRCMKernelLoopNum].usg_thd2 = 10000;
        pstMRCMSetting->stMRCMSettingData.stMRCMLoopKernelData.pstMRCMData[ucMRCMKernelLoopNum].usb_thd2 = 10000;
        pstMRCMSetting->stMRCMSettingData.stMRCMLoopKernelData.pstMRCMData[ucMRCMKernelLoopNum].usrgb_thd2 = 0;
        ucMRCMKernelLoopNum++;
    }
#endif
    pstMRCMSetting->stMRCMSettingData.stMRCMLoopKernelData.ucMRCMLoopNum = ucMRCMKernelLoopNum;
    for(ucMRCMCount = 0; ucMRCMCount < _MRCM_SETTING_NUM; ucMRCMCount++)
    {
        StructMRCMData *pstMRCMUserData = &pstMRCMSetting->stMRCMSettingData.stMRCMLoopUserData.pstMRCMData[ucMRCMCount];
        StructMRCMData *pstMRCMKernelData = &pstMRCMSetting->stMRCMSettingData.stMRCMLoopKernelData.pstMRCMData[ucMRCMCount];
        pstMRCMUserData->uch_num = MAXOF(pstMRCMUserData->uch_num, 1);
        pstMRCMUserData->ucv_num = MAXOF(pstMRCMUserData->ucv_num, 1);
        pstMRCMKernelData->uch_num = MAXOF(pstMRCMKernelData->uch_num, 1);
        pstMRCMKernelData->ucv_num = MAXOF(pstMRCMKernelData->ucv_num, 1);
    }
}

//--------------------------------------------------
// Description  : MRCM Application
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonColorMRCMApplication(void)
{
    if(GET_MRCM_CASE() == _MRCM_ON)
    {
#if(_MRCM_SUPPORT == _ON)
        UserInterfaceColorMRCMApplication();
#endif
        /*
        if(KERNEL_APPLICATION != _OFF)
        {
            if(GET_MRCM_READY_KERNEL_SET() == enumLoopNumCount)
            {
                Calculation MRCM Data for Corresponding Application
            }
            enumLoopNumCount = enumLoopNumCount + 1;
        }
        */
#if(_DYNAMIC_LOWBLUE_FUNCTION == _ON)
        if(GET_MRCM_READY_KERNEL_SET() == _MRCM_KERNEL_SET_0)
        {
            UserCommonColorLowBlueHandler();
        }
#endif
    }
}

//--------------------------------------------------
// Description  : MRCM Read Result of kernal and user cases
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonColorMRCMCaseReadResult(void)
{
    if(GET_MRCM_CASE() == _MRCM_ON)
    {
#if(_MRCM_SUPPORT == _ON)
        if(GET_MRCM_READY_SET() != _MRCM_SET_NONE)
        {
            UserInterfaceColorMRCMReadResult();
        }
#endif
        /*
        if(KERNEL_APPLICATION != _OFF)
        {
            if(GET_MRCM_READY_KERNEL_SET() == enumLoopNumCount)
            {
                Read MRCM Data for Corresponding Application
            }
            enumLoopNumCount = enumLoopNumCount + 1;
        }
        */
#if(_DYNAMIC_LOWBLUE_FUNCTION == _ON)
        if(GET_MRCM_READY_KERNEL_SET() == _MRCM_KERNEL_SET_0)
        {
            UserCommonColorMRCMLowBlueReadResult();
        }
#endif
        SET_MRCM_READ_RESULT_DONE();
    }
}

//--------------------------------------------------
// Description  : select MRCM Region to read region statistics
// Input Value  : MRCM Region
// Output Value : None
//--------------------------------------------------
void UserCommonColorMRCMRegionSelect(BYTE ucMRCMRegion)
{
    ScalerColorMRCMRegionSelect(ucMRCMRegion);
}

#if(_DYNAMIC_LOWBLUE_FUNCTION == _ON)
//--------------------------------------------------
// Description  : Dynamic Low Blue Get Blue Light Hazard
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonColorMRCMLowBlueReadResult(void)
{
    BYTE ucTemp = 0;
    WORD usTargetBgain = 0;
    WORD usRHazardmax = g_stColorDynamicLowBlueSetting.usHazardRmax; // represent 16bit
    WORD usGHazardmax = g_stColorDynamicLowBlueSetting.usHazardGmax;
    WORD usBHazardmax = g_stColorDynamicLowBlueSetting.usHazardBmax;
    WORD usLbTarget = g_stColorDynamicLowBlueSetting.usHazardTarget;
    WORD usGainStepB = g_stColorDynamicLowBlueSetting.usGainStepB;
    StructMRCMRGBResult stMRCMRGBThd1Result;
    StructMRCMRGBResult stMRCMRGBThd2Result;
    WORD usValue = 0;
    WORD usTempValue = 0;
    EnumDynamicLowBlueType enumDynamicLowBlueType = UserCommonColorGetLowBlueStatus();
    if((enumDynamicLowBlueType == _LOWBLUE_MODE_OFF) || (enumDynamicLowBlueType == _LOWBLUE_MODE_STATIC_GLOBAL))
    {
        return;
    }
    for(ucTemp = 0; ucTemp < (_LOWBLUE_MRCM_HOR_DIVISION * _LOWBLUE_MRCM_VER_DIVISION); ucTemp++)
    {
        // transfer mrcm value to Blue Hazard Value (Lb)
        ScalerColorMRCMReadRGBResult(ucTemp, _MRCM_THD1, &stMRCMRGBThd1Result);
        ScalerColorMRCMReadRGBResult(ucTemp, _MRCM_THD2, &stMRCMRGBThd2Result);
        usValue = 0;
        if(stMRCMRGBThd2Result.ulRedNum > g_stColorDynamicLowBlueSetting.usRegionPixelThd)
        {
            usValue = (QWORD)((stMRCMRGBThd2Result.uqRedVal / stMRCMRGBThd2Result.ulRedNum) * usRHazardmax) >> 14;
        }
        else
        {
            usValue = (QWORD)((stMRCMRGBThd1Result.uqRedVal / stMRCMRGBThd1Result.ulRedNum) * usRHazardmax) >> 14;
        }
        if(stMRCMRGBThd2Result.ulGreenNum > g_stColorDynamicLowBlueSetting.usRegionPixelThd)
        {
            usValue += (QWORD)((stMRCMRGBThd2Result.uqGreenVal / stMRCMRGBThd2Result.ulGreenNum) * usGHazardmax) >> 14;
        }
        else
        {
            usValue += (QWORD)((stMRCMRGBThd1Result.uqGreenVal / stMRCMRGBThd1Result.ulGreenNum) * usGHazardmax) >> 14;
        }
        if(stMRCMRGBThd2Result.ulBlueNum > g_stColorDynamicLowBlueSetting.usRegionPixelThd)
        {
            usValue += (QWORD)((stMRCMRGBThd2Result.uqBlueVal / stMRCMRGBThd2Result.ulBlueNum) * usBHazardmax) >> 14;
        }
        else
        {
            usValue += (QWORD)((stMRCMRGBThd1Result.uqBlueVal / stMRCMRGBThd1Result.ulBlueNum) * usBHazardmax) >> 14;
        }

        // 4 frames Average filter. Get this region average hazard
        // safely add and safely subtract
        // g_pusColorHazardFrameBuffer[ucTemp] = g_pusColorHazardFrameBuffer[ucTemp] + (usValue >> 2) - (g_ppusColorMrcmHazardRegion[ucTemp][g_ucColorFrameIndex] >> 2);
        if(usValue > g_ppusColorMrcmHazardRegion[ucTemp][g_ucColorFrameIndex])
        {
            usTempValue = (usValue - g_ppusColorMrcmHazardRegion[ucTemp][g_ucColorFrameIndex]) >> 2;

            if(usTempValue > (65535 - g_pusColorHazardFrameBuffer[ucTemp]))
            {
                g_pusColorHazardFrameBuffer[ucTemp] = 65535;
            }
            else
            {
                g_pusColorHazardFrameBuffer[ucTemp] = g_pusColorHazardFrameBuffer[ucTemp] + usTempValue;
            }
        }
        else
        {
            usTempValue = (g_ppusColorMrcmHazardRegion[ucTemp][g_ucColorFrameIndex] - usValue) >> 2;

            if(g_pusColorHazardFrameBuffer[ucTemp] < usTempValue)
            {
                g_pusColorHazardFrameBuffer[ucTemp] = 0;
            }
            else
            {
                g_pusColorHazardFrameBuffer[ucTemp] = g_pusColorHazardFrameBuffer[ucTemp] - usTempValue;
            }
        }
        g_ppusColorMrcmHazardRegion[ucTemp][g_ucColorFrameIndex] = usValue;

        // determine target gain of each region
        if(g_stColorDynamicLowBlueSetting.enumDynamicLowBlueType == _LOWBLUE_MODE_ADAPTIVE)
        {
            if(g_pusColorHazardFrameBuffer[ucTemp] >= usLbTarget)
            {
                usTargetBgain = ((DWORD)g_stColorDynamicLowBlueSetting.usGainB * g_pusColorHazardFrameBuffer[ucTemp]) / (usRHazardmax + usGHazardmax + usBHazardmax);
            }
            else
            {
                usTargetBgain = 0;
            }
            usTargetBgain = ((usTargetBgain + g_stColorDynamicLowBlueSetting.usGainOffset) > g_stColorDynamicLowBlueSetting.usGainB) ? g_stColorDynamicLowBlueSetting.usGainB : (usTargetBgain + g_stColorDynamicLowBlueSetting.usGainOffset);

            if(g_pusColorCurrentGainB[ucTemp] > usTargetBgain)
            {
                g_pusColorCurrentGainB[ucTemp] = ((g_pusColorCurrentGainB[ucTemp]) <= (usTargetBgain + usGainStepB)) ? usTargetBgain : (g_pusColorCurrentGainB[ucTemp] - usGainStepB);
            }
            else if(g_pusColorCurrentGainB[ucTemp] < usTargetBgain)
            {
                g_pusColorCurrentGainB[ucTemp] = ((g_pusColorCurrentGainB[ucTemp] + usGainStepB) >= usTargetBgain) ? usTargetBgain : (g_pusColorCurrentGainB[ucTemp] + usGainStepB);
            }
        }
        else if(g_stColorDynamicLowBlueSetting.enumDynamicLowBlueType == _LOWBLUE_MODE_GLOBAL)
        {
            // get the max hazard value of all regions
            if(g_pusColorHazardFrameBuffer[ucTemp] >= usLbTarget)
            {
                usLbTarget = g_pusColorHazardFrameBuffer[ucTemp];
                usTargetBgain = ((DWORD)g_stColorDynamicLowBlueSetting.usGainB * g_pusColorHazardFrameBuffer[ucTemp]) / (usRHazardmax + usGHazardmax + usBHazardmax);
            }
        }
    }

    if(g_stColorDynamicLowBlueSetting.enumDynamicLowBlueType == _LOWBLUE_MODE_GLOBAL)
    {
        usTargetBgain = ((usTargetBgain + g_stColorDynamicLowBlueSetting.usGainOffset) > g_stColorDynamicLowBlueSetting.usGainB) ? g_stColorDynamicLowBlueSetting.usGainB : (usTargetBgain + g_stColorDynamicLowBlueSetting.usGainOffset);
        for(ucTemp = 0; ucTemp < (_LOWBLUE_MRCM_HOR_DIVISION * _LOWBLUE_MRCM_VER_DIVISION); ucTemp++)
        {
            if(g_pusColorCurrentGainB[ucTemp] > usTargetBgain)
            {
                g_pusColorCurrentGainB[ucTemp] = ((g_pusColorCurrentGainB[ucTemp] - usGainStepB) <= usTargetBgain) ? usTargetBgain : (g_pusColorCurrentGainB[ucTemp] - usGainStepB);
            }

            if(g_pusColorCurrentGainB[ucTemp] < usTargetBgain)
            {
                g_pusColorCurrentGainB[ucTemp] = ((g_pusColorCurrentGainB[ucTemp] + usGainStepB) >= usTargetBgain) ? usTargetBgain : (g_pusColorCurrentGainB[ucTemp] + usGainStepB);
            }
        }
    }
    g_ucColorFrameIndex = (g_ucColorFrameIndex + 1) % _AVE_FILTER_FRAME_NUM;
    SET_MRCM_READ_RESULT_DONE();
}

//--------------------------------------------------
// Description  : MRCM Application : Low Blue Application Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonColorLowBlueHandler(void)
{
    EnumDynamicLowBlueType enumDynamicLowBlueType = UserCommonColorGetLowBlueStatus();
    if((enumDynamicLowBlueType != _LOWBLUE_MODE_OFF) && (enumDynamicLowBlueType != _LOWBLUE_MODE_STATIC_GLOBAL))
    {
        if((g_stColorDynamicLowBlueSetting.enumDynamicLowBlueType == _LOWBLUE_MODE_ADAPTIVE) || (g_stColorDynamicLowBlueSetting.enumDynamicLowBlueType == _LOWBLUE_MODE_GLOBAL))
        {
            UserCommonColorLowBlueLocalAdjust(g_pusColorCurrentGainB);
        }
    }
}

//--------------------------------------------------
// Description  : MRCM Application : Low Blue Application Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonColorMRCMLowBlueReset(void)
{
    memset(g_pusColorCurrentGainB, 0, sizeof(g_pusColorCurrentGainB));
    memset(g_ppusColorMrcmHazardRegion, 0, sizeof(g_ppusColorMrcmHazardRegion));
    memset(g_pusColorHazardFrameBuffer, 0, sizeof(g_pusColorHazardFrameBuffer));
}
#endif
#endif // End of #if(_MRCM_SUPPORT == _ON)