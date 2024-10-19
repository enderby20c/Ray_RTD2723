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
// ID Code      : ScalerColorMRCM.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_COLOR_MRCM__

#include "ScalerFunctionInclude.h"
#include "Color/ScalerColor.h"

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_COLOR_IP_MRCM == _ON)
//--------------------------------------------------
// Description  : MRCM enable
// Input Value  : Enable
// Output Value : None
//--------------------------------------------------
void ScalerColorMRCMEnable(EnumFunctionOnOFF enumOn)
{
    if(enumOn == _FUNCTION_ON)
    {
        Scaler32SetBit(PB00800_00_MRCM_CTRL_M1, ~(_BIT4 | _BIT0), _BIT0);
    }
    else
    {
        Scaler32SetBit(PB00800_00_MRCM_CTRL_M1, ~(_BIT4 | _BIT0), 0x00);
        ScalerTimerWaitForDDomainEvent(_EVENT_DVS);
    }
}

//--------------------------------------------------
// Description  : MRCM Setting
// Input Value  : MRCM statistic region struct
// Output Value : None
//--------------------------------------------------
void ScalerColorMRCMSetting(StructMRCMData *pstMRCMData)
{
    DWORD ulTemp = 0;
    // Set v_num ,h_num and protect ready to read bit(_BIT4)
    ulTemp = TO_WORD((pstMRCMData->uch_num - 1), (pstMRCMData->ucv_num - 1));
    Scaler32SetBit(PB00800_00_MRCM_CTRL_M1, ~(_BIT(29, 16) | _BIT4), ulTemp << 16);

    // Set start_pixel_h and start_pixel_v
    ulTemp = WORD_TO_DWORD(pstMRCMData->usstart_pixel_h, pstMRCMData->usstart_pixel_v);
    Scaler32SetDWord(PB00800_04_MRCM_CTRL_M1, ulTemp);

    // Set end_pixel_h and end_pixel_v
    ulTemp = WORD_TO_DWORD(pstMRCMData->usend_pixel_h, pstMRCMData->usend_pixel_v);
    Scaler32SetDWord(PB00800_08_MRCM_CTRL_M1, ulTemp);

    // Set h_step and v_step
    ulTemp = WORD_TO_DWORD(pstMRCMData->ush_step, pstMRCMData->usv_step);
    Scaler32SetDWord(PB00800_0C_MRCM_CTRL_M1, ulTemp);

    // Set h_offset_r and h_offset_l
    ulTemp = WORD_TO_DWORD(pstMRCMData->ush_offset_r, pstMRCMData->ush_offset_l);
    Scaler32SetDWord(PB00800_10_MRCM_CTRL_M1, ulTemp);

    // Set v_offset_t and v_offset_b
    ulTemp = WORD_TO_DWORD(pstMRCMData->usv_offset_t, pstMRCMData->usv_offset_b);
    Scaler32SetDWord(PB00800_14_MRCM_CTRL_M1, ulTemp);

    // Set r_thd1 and g_thd1
    ulTemp = WORD_TO_DWORD(pstMRCMData->usr_thd1, pstMRCMData->usg_thd1);
    Scaler32SetDWord(PB00800_18_MRCM_CTRL_M1, ulTemp);

    // Set b_thd1 and rgb_thd1
    ulTemp = WORD_TO_DWORD(pstMRCMData->usb_thd1, pstMRCMData->usrgb_thd1);
    Scaler32SetDWord(PB00800_1C_MRCM_CTRL_M1, ulTemp);

    // Set r_thd2 and g_thd2
    ulTemp = WORD_TO_DWORD(pstMRCMData->usr_thd2, pstMRCMData->usg_thd2);
    Scaler32SetDWord(PB00800_20_MRCM_CTRL_M1, ulTemp);

    // Set b_thd2 and rgb_thd2
    ulTemp = WORD_TO_DWORD(pstMRCMData->usb_thd2, pstMRCMData->usrgb_thd2);
    Scaler32SetDWord(PB00800_24_MRCM_CTRL_M1, ulTemp);

    // Set bg_r_value and bg_g_value
    ulTemp = WORD_TO_DWORD(((WORD)pstMRCMData->ucbg_r_value) << 6, ((WORD)pstMRCMData->ucbg_g_value) << 6);
    Scaler32SetDWord(PB00800_28_MRCM_CTRL_M1, ulTemp);

    // Set bg_b_value
    ulTemp = ((((DWORD)pstMRCMData->ucbg_b_value) << 6) << 16);
    Scaler32SetDWord(PB00800_2C_MRCM_CTRL_M1, ulTemp);
}

//--------------------------------------------------
// Description  : change MRCM sram
// Input Value  : toggle sram
// Output Value : None
//--------------------------------------------------
void ScalerColorMRCMSramSel(bit bSramSelect)
{
    Scaler32SetBit(PB00800_00_MRCM_CTRL_M1, ~(_BIT4 | _BIT3), (bSramSelect << 3));
}

//--------------------------------------------------
// Description  : Get MRCM sram Number
// Input Value  : None
// Output Value : Sram Number
//--------------------------------------------------
bit ScalerColorMRCMGetSramNumber(void)
{
    return (bit)(Scaler32GetBit(PB00800_00_MRCM_CTRL_M1, _BIT3) != 0);
}

//--------------------------------------------------
// Description  : check Ready to read flag
// Input Value  : None
// Output Value : ready to read flag status
//--------------------------------------------------
bit ScalerColorMRCMReadyToRead(void)
{
    return (bit)(Scaler32GetBit(PB00800_00_MRCM_CTRL_M1, _BIT4) != 0);
}

//--------------------------------------------------
// Description  : write one clear ready to read flag
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerColorMRCMApply(void)
{
    Scaler32SetBit(PB00800_00_MRCM_CTRL_M1, ~_BIT4, _BIT4);
}

//--------------------------------------------------
// Description  : read MRCM result
// Input Value  : data type
// Output Value : Get specific data
//--------------------------------------------------
QWORD ScalerColorMRCMReadResult(EnumMRCMReadResultOption enumMRCMReadResultOption)
{
    QWORD uqTemp = 0;

    switch(enumMRCMReadResultOption)
    {
        // thd1
        case _MRCM_ABOVE_TH1_NUM_R:
            uqTemp = Scaler32GetDWord(PB00801_00_MRCM_STATISTICS) >> 8;
            break;

        case _MRCM_ABOVE_TH1_VAL_R:
            uqTemp = TO_QWORD(Scaler32GetByte(PB00801_00_MRCM_STATISTICS, 0), Scaler32GetDWord(PB00801_04_MRCM_STATISTICS));
            break;

        case _MRCM_ABOVE_TH1_NUM_G:
            uqTemp = Scaler32GetDWord(PB00801_08_MRCM_STATISTICS) >> 8;
            break;

        case _MRCM_ABOVE_TH1_VAL_G:
            uqTemp = TO_QWORD(Scaler32GetByte(PB00801_08_MRCM_STATISTICS, 0), Scaler32GetDWord(PB00801_0C_MRCM_STATISTICS));
            break;

        case _MRCM_ABOVE_TH1_NUM_B:
            uqTemp = Scaler32GetDWord(PB00801_10_MRCM_STATISTICS) >> 8;
            break;

        case _MRCM_ABOVE_TH1_VAL_B:
            uqTemp = TO_QWORD(Scaler32GetByte(PB00801_10_MRCM_STATISTICS, 0), Scaler32GetDWord(PB00801_14_MRCM_STATISTICS));
            break;

        case _MRCM_ABOVE_TH1_NUM_RGB:
            uqTemp = Scaler32GetDWord(PB00801_18_MRCM_STATISTICS) >> 8;
            break;

        case _MRCM_ABOVE_TH1_VAL_RGB:
            uqTemp = TO_QWORD(Scaler32GetByte(PB00801_18_MRCM_STATISTICS, 0), Scaler32GetDWord(PB00801_1C_MRCM_STATISTICS));
            break;

        // thd2
        case _MRCM_ABOVE_TH2_NUM_R:
            uqTemp = Scaler32GetDWord(PB00801_28_MRCM_STATISTICS) >> 8;
            break;

        case _MRCM_ABOVE_TH2_VAL_R:
            uqTemp = TO_QWORD(Scaler32GetByte(PB00801_28_MRCM_STATISTICS, 0), Scaler32GetDWord(PB00801_2C_MRCM_STATISTICS));
            break;

        case _MRCM_ABOVE_TH2_NUM_G:
            uqTemp = Scaler32GetDWord(PB00801_30_MRCM_STATISTICS) >> 8;
            break;

        case _MRCM_ABOVE_TH2_VAL_G:
            uqTemp = TO_QWORD(Scaler32GetByte(PB00801_30_MRCM_STATISTICS, 0), Scaler32GetDWord(PB00801_34_MRCM_STATISTICS));
            break;

        case _MRCM_ABOVE_TH2_NUM_B:
            uqTemp = Scaler32GetDWord(PB00801_38_MRCM_STATISTICS) >> 8;
            break;

        case _MRCM_ABOVE_TH2_VAL_B:
            uqTemp = TO_QWORD(Scaler32GetByte(PB00801_38_MRCM_STATISTICS, 0), Scaler32GetDWord(PB00801_3C_MRCM_STATISTICS));
            break;

        case _MRCM_ABOVE_TH2_NUM_RGB:
            uqTemp = Scaler32GetDWord(PB00801_40_MRCM_STATISTICS) >> 8;
            break;

        case _MRCM_ABOVE_TH2_VAL_RGB:
            uqTemp = TO_QWORD(Scaler32GetByte(PB00801_40_MRCM_STATISTICS, 0), Scaler32GetDWord(PB00801_44_MRCM_STATISTICS));
            break;

        // Max, Min R/G/B/RGB
        case _MRCM_ABOVE_MAX_CODE_R:
            uqTemp = Scaler32GetWord(PB00801_20_MRCM_STATISTICS, 1);
            break;

        case _MRCM_ABOVE_MIN_CODE_R:
            uqTemp = Scaler32GetWord(PB00801_48_MRCM_STATISTICS, 1);
            break;

        case _MRCM_ABOVE_MAX_CODE_G:
            uqTemp = Scaler32GetWord(PB00801_20_MRCM_STATISTICS, 0);
            break;

        case _MRCM_ABOVE_MIN_CODE_G:
            uqTemp = Scaler32GetWord(PB00801_48_MRCM_STATISTICS, 0);
            break;

        case _MRCM_ABOVE_MAX_CODE_B:
            uqTemp = Scaler32GetWord(PB00801_24_MRCM_STATISTICS, 1);
            break;

        case _MRCM_ABOVE_MIN_CODE_B:
            uqTemp = Scaler32GetWord(PB00801_4C_MRCM_STATISTICS, 1);
            break;

        case _MRCM_ABOVE_MAX_CODE_RGB:
            uqTemp = Scaler32GetWord(PB00801_24_MRCM_STATISTICS, 0);
            break;

        case _MRCM_ABOVE_MIN_CODE_RGB:
            uqTemp = Scaler32GetWord(PB00801_4C_MRCM_STATISTICS, 0);
            break;

        default:
            uqTemp = 0;
            break;
    }
    return uqTemp;
}

//--------------------------------------------------
// Description  : read out MRCM stastic result (fast)
// Input Value  : Region, THD Statistics
// Output Value : None
//--------------------------------------------------
void ScalerColorMRCMReadRGBResult(BYTE ucMRCMRegion, EnumMRCMThdType enumMrcmThdType, StructMRCMRGBResult *pstMRCMRGBResult)
{
    DWORD ulTemp_0 = 0;
    ScalerColorMRCMRegionSelect(ucMRCMRegion);

    if(enumMrcmThdType == _MRCM_THD1)
    {
        ulTemp_0 = Scaler32GetDWord(PB00801_00_MRCM_STATISTICS);
        pstMRCMRGBResult->ulRedNum = ulTemp_0 >> 8;
        pstMRCMRGBResult->uqRedVal = TO_QWORD(ulTemp_0 & 0x000000FF, Scaler32GetDWord(PB00801_04_MRCM_STATISTICS));

        ulTemp_0 = Scaler32GetDWord(PB00801_08_MRCM_STATISTICS);
        pstMRCMRGBResult->ulGreenNum = ulTemp_0 >> 8;
        pstMRCMRGBResult->uqGreenVal = TO_QWORD(ulTemp_0 & 0x000000FF, Scaler32GetDWord(PB00801_0C_MRCM_STATISTICS));

        ulTemp_0 = Scaler32GetDWord(PB00801_10_MRCM_STATISTICS);
        pstMRCMRGBResult->ulBlueNum = ulTemp_0 >> 8;
        pstMRCMRGBResult->uqBlueVal = TO_QWORD(ulTemp_0 & 0x000000FF, Scaler32GetDWord(PB00801_14_MRCM_STATISTICS));
    }
    else if(enumMrcmThdType == _MRCM_THD2)
    {
        ulTemp_0 = Scaler32GetDWord(PB00801_28_MRCM_STATISTICS);
        pstMRCMRGBResult->ulRedNum = ulTemp_0 >> 8;
        pstMRCMRGBResult->uqRedVal = TO_QWORD(ulTemp_0 & 0x000000FF, Scaler32GetDWord(PB00801_2C_MRCM_STATISTICS));

        ulTemp_0 = Scaler32GetDWord(PB00801_30_MRCM_STATISTICS);
        pstMRCMRGBResult->ulGreenNum = ulTemp_0 >> 8;
        pstMRCMRGBResult->uqGreenVal = TO_QWORD(ulTemp_0 & 0x000000FF, Scaler32GetDWord(PB00801_34_MRCM_STATISTICS));

        ulTemp_0 = Scaler32GetDWord(PB00801_38_MRCM_STATISTICS);
        pstMRCMRGBResult->ulBlueNum = ulTemp_0 >> 8;
        pstMRCMRGBResult->uqBlueVal = TO_QWORD(ulTemp_0 & 0x000000FF, Scaler32GetDWord(PB00801_3C_MRCM_STATISTICS));
    }
}

//--------------------------------------------------
// Description  : select MRCM PCM mode
// Input Value  : PCM mode
// Output Value : None
//--------------------------------------------------
void ScalerColorMRCMPcmMode(EnumPCMModeSelect enumPCMModeSelect)
{
    if(enumPCMModeSelect == _PCM_MODE)
    {
        Scaler32SetBit(PB00800_00_MRCM_CTRL_M1, ~(_BIT4 | _BIT2), _BIT2);
    }
    else
    {
        Scaler32SetBit(PB00800_00_MRCM_CTRL_M1, ~(_BIT4 | _BIT2), 0x00);
    }
}

//--------------------------------------------------
// Description  : select MRCM Region to read region statistics
// Input Value  : MRCM Region
// Output Value : None
//--------------------------------------------------
void ScalerColorMRCMRegionSelect(BYTE ucMRCMRegion)
{
    Scaler32SetBit(PB00800_00_MRCM_CTRL_M1, ~(_BIT(13, 8) | _BIT4), (ucMRCMRegion & 0x3F) << 8);
#if(_HW_MRCM_DUMMY_READ_SUPPORT == _ON)
    Scaler32GetDWord(PB00801_00_MRCM_STATISTICS); // dummy read
    Scaler32GetDWord(PB00801_28_MRCM_STATISTICS); // dummy read
#endif
}
#endif

