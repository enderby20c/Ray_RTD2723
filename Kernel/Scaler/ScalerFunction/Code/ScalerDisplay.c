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
// ID Code      : ScalerDisplay.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_DISPLAY__

#include "ScalerFunctionInclude.h"
#include "Display/ScalerDisplay.h"


//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
StructDisplayCustomizedData g_stDisplayCustomizedData;


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Set display DVF mode by V freq.
// Input Value  : stDVCustomizedFreq --> custim V freq. range
// Output Value : None
//--------------------------------------------------
EnumDVFSelect ScalerDisplaySelectDVFMode(void)
{
#if(_FRC_SUPPORT == _ON)
    if(GET_FORCE_DISPLAY_1P_MODE() == _TRUE)
    {
#if(_DRR_FREE_RUN_DISPLAY_SUPPORT == _OFF)
#if(_DRR_SUPPORT == _ON)
        if(ScalerDrrGetType(GET_MDOMAIN_INPUT_PORT()) != _DRR_NONE_TYPE)
        {
            return _1_IVF;
        }
        else
#endif
#endif
        {
            if(g_stDisplayCustomizedData.structDVCustomizedFreq.b1FORCETOFREERUN == _ENABLE)
            {
                return _PANEL_TYP_FRAME_RATE_FREE_RUN;
            }
            else
            {
                WORD usMaxFreqMargin = g_stDisplayCustomizedData.structDVCustomizedFreq.usMaxFreq + _PANEL_FRAME_SYNC_MARGIN;
                WORD usMinFreqMargin = g_stDisplayCustomizedData.structDVCustomizedFreq.usMinFreq - _PANEL_FRAME_SYNC_MARGIN;

#if(_MOTION_BLUR_REDUCTION_LCD_SUPPORT == _ON)
#if(_RTK_ADVANCED_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
                ScalerMbrAdvanceUpdateRtkAdvMbrStatus(GET_MDOMAIN_INPUT_VFREQ());
#endif
#elif(_MOTION_BLUR_REDUCTION_OLED_SUPPORT == _ON)
#if(_MN_FRAMESYNC_FORCE_TO_FREERUN == _OFF)
                if(GET_MBR_BFI_AVAILABLE_MODE() == _BFI_KERNEL_2X)
                {
                    // Judge 2IVF First
                    if((GET_MDOMAIN_INPUT_VFREQ() <= (usMaxFreqMargin / 2)) &&
                       (GET_MDOMAIN_INPUT_VFREQ() >= (usMinFreqMargin / 2))) // DVF = 2 * IVF
                    {
                        return _2_IVF;
                    }
                }
#endif
#endif

                if((GET_MDOMAIN_INPUT_VFREQ() <= usMaxFreqMargin) &&
                   (GET_MDOMAIN_INPUT_VFREQ() >= usMinFreqMargin))
                {
                    return _1_IVF;
                }
                else
                {
#if(_MN_FRAMESYNC_FORCE_TO_FREERUN == _OFF)
                    if((GET_MDOMAIN_INPUT_VFREQ() <= (usMaxFreqMargin / 2)) &&
                       (GET_MDOMAIN_INPUT_VFREQ() >= (usMinFreqMargin / 2))) // DVF = 2 * IVF
                    {
                        // For 1080p_30
                        return _2_IVF;
                    }
                    else if((GET_MDOMAIN_INPUT_VFREQ() <= (usMaxFreqMargin * 2 / 5)) &&
                            (GET_MDOMAIN_INPUT_VFREQ() >= (usMinFreqMargin * 2 / 5))) // DVF = 2.5 * IVF
                    {
                        // For 1080p_25, 1080p_24
                        return _2_5_IVF;
                    }
                    else if((GET_MDOMAIN_INPUT_VFREQ() <= (usMaxFreqMargin / 3)) &&
                            (GET_MDOMAIN_INPUT_VFREQ() >= (usMinFreqMargin / 3))) // DVF = 3 * IVF
                    {
                        return _3_IVF;
                    }
                    else
#endif
                    {
                        return _PANEL_TYP_FRAME_RATE_FREE_RUN;
                    }
                }
            }
        }
    }
    else
    {
        return _PANEL_TYP_FRAME_RATE_FREE_RUN;
    }
#else // else of #if(_FRC_SUPPORT == _ON)

    return _1_IVF;

#endif // End of #if(_FRC_SUPPORT == _ON)
}

//--------------------------------------------------
// Description  : Set DVfreq.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplaySetDVFreq(void)
{
    switch(GET_MEMORY_DVF_SELECT())
    {
        case _1_IVF:
            g_usMDomainDVFreq = GET_MDOMAIN_INPUT_VFREQ();
            break;

#if(_FRC_SUPPORT == _ON)
        case _2_IVF:
            g_usMDomainDVFreq = 2 * GET_MDOMAIN_INPUT_VFREQ();
            break;

        case _3_IVF:
            g_usMDomainDVFreq = 3 * GET_MDOMAIN_INPUT_VFREQ();
            break;

        case _5_4_IVF:
            g_usMDomainDVFreq = 4 * GET_MDOMAIN_INPUT_VFREQ() / 5;
            break;

        case _6_5_IVF:
            g_usMDomainDVFreq = 5 * GET_MDOMAIN_INPUT_VFREQ() / 6;
            break;

        case _2_5_IVF:
            g_usMDomainDVFreq = 5 * GET_MDOMAIN_INPUT_VFREQ() / 2;
            break;

        case _PANEL_TYP_FRAME_RATE_FREE_RUN:
            g_usMDomainDVFreq = g_stDisplayCustomizedData.structDVCustomizedFreq.usTypFreq;
            break;
#endif

        default:
            g_usMDomainDVFreq = GET_MDOMAIN_INPUT_VFREQ();
            break;
    }
}

#if(_PANEL_STYLE == _PANEL_LVDS)
//--------------------------------------------------
// Description  : LVDS TX Port output Data Selection
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplayLvdsTxDataSel(void)
{
#if(_LVDS_PORT_SEL == _LVDS_1_PORT_A)

    ScalerSetByte(P39_02_LVDS_DISPLAY_CONV_CTRL1, 0x00);

#elif(_LVDS_PORT_SEL == _LVDS_1_PORT_B)

    ScalerSetByte(P39_02_LVDS_DISPLAY_CONV_CTRL1, 0x00);

#elif(_LVDS_PORT_SEL == _LVDS_1_PORT_C)

    ScalerSetByte(P39_03_LVDS_DISPLAY_CONV_CTRL2, 0x00);

#elif(_LVDS_PORT_SEL == _LVDS_1_PORT_D)

    ScalerSetByte(P39_03_LVDS_DISPLAY_CONV_CTRL2, 0x00);

#elif(_LVDS_PORT_SEL == _LVDS_2_PORT_AB)

    ScalerSetByte(P39_02_LVDS_DISPLAY_CONV_CTRL1, ((_LVDS_PORT_MIRROR == _DISABLE) ? 0x01 : 0x10));

#elif(_LVDS_PORT_SEL == _LVDS_2_PORT_CD)

    ScalerSetByte(P39_03_LVDS_DISPLAY_CONV_CTRL2, ((_LVDS_PORT_MIRROR == _DISABLE) ? 0x01 : 0x10));

#elif(_LVDS_PORT_SEL == _LVDS_4_PORT_ABCD)

#endif // #if(_LVDS_PORT_SEL == _LVDS_1_PORT_A)
}

//--------------------------------------------------
// Description  : LVDS TX Port output Data Swap Selection
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplayLvdsTxPortSwap(void)
{
    BYTE ucLvdsPortSwapIndex = 0;

    // Port AB Swap
    ucLvdsPortSwapIndex = ((_LVDS_PORT_AB_SWAP == _DISABLE) ? 0 : 4);

    ScalerSetByte(P39_02_LVDS_DISPLAY_CONV_CTRL1, (((ScalerGetBit(P39_02_LVDS_DISPLAY_CONV_CTRL1, (_BIT7 | _BIT6 | _BIT5 | _BIT4))) >> ucLvdsPortSwapIndex) | ((ScalerGetBit(P39_02_LVDS_DISPLAY_CONV_CTRL1, (_BIT3 | _BIT2 | _BIT1 | _BIT0))) << ucLvdsPortSwapIndex)));

    // Port CD Swap
    ucLvdsPortSwapIndex = ((_LVDS_PORT_CD_SWAP == _DISABLE) ? 0 : 4);

    ScalerSetByte(P39_03_LVDS_DISPLAY_CONV_CTRL2, (((ScalerGetBit(P39_03_LVDS_DISPLAY_CONV_CTRL2, (_BIT7 | _BIT6 | _BIT5 | _BIT4))) >> ucLvdsPortSwapIndex) | ((ScalerGetBit(P39_03_LVDS_DISPLAY_CONV_CTRL2, (_BIT3 | _BIT2 | _BIT1 | _BIT0))) << ucLvdsPortSwapIndex)));
}
#endif

//--------------------------------------------------
// Description  : Get Lvds Pll Power Status
// Input Value  : None
// Output Value : _TRUE: Power On   _FALSE: Power Down
//--------------------------------------------------
bit ScalerDisplayGetPllPowerStatus(void)
{
#if(_PANEL_STYLE == _PANEL_LVDS)

    return ScalerDisplayGetLvdsPllPowerStatus();

#elif(_PANEL_STYLE == _PANEL_DPTX)

    return ScalerDisplayDpTxGetPllPowerStatus();

#elif(_PANEL_STYLE == _PANEL_VBO)

    return ScalerDisplayVboTxGetPllPowerStatus();

#endif

    return _FALSE;
}

#if(_PANEL_EXIST_MULTIPANEL == _ON)
//--------------------------------------------------
// Description  : Set Display Interface Lane Power
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplayInterfacePowerSwitch(void)
{
#if(_PANEL_STYLE == _PANEL_DPTX)
    ScalerDisplayDpTxPowerSwitch();
#elif(_PANEL_STYLE == _PANEL_VBO)
    ScalerDisplayVboTxPowerSwitch();
#endif
}
#endif

//--------------------------------------------------
// Description  : Set Display Conversion
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplaySetDspc(void)
{
#if(_PANEL_STYLE == _PANEL_LVDS)
    ScalerDisplayLvdsSetDspcControl();
#elif(_PANEL_STYLE == _PANEL_DPTX)
    ScalerDisplayDpTxSetDspcControl();
#elif(_PANEL_STYLE == _PANEL_VBO)
    ScalerDisplayVboTxSetDspcControl();
#endif
}
