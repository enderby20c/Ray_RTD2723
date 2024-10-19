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
// ID Code      : RL6952_Series_DpRx.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"
#include "DpRx/ScalerDpRx.h"

#if(_DP_SUPPORT == _ON)
//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
BYTE g_pucDpRxEN[4] =
{
    0x30, 0x90, 0xC0, 0x60
};

WORD g_pusDpRxST[64] =
{
    0x8000, 0xC000, 0xE000, 0xF000, 0xF800, 0xFC00, 0xFe00, 0xFF00,
    0xFF80, 0xFFC0, 0xFFE0, 0xFFF0, 0xFFF8, 0xFFFC, 0xFFFE, 0xFFFF,
    0x7FFF, 0x3FFF, 0x1FFF, 0x0FFF, 0x07FF, 0x03FF, 0x01FF, 0x00FF,
    0x007F, 0x003F, 0x001F, 0x000F, 0x0007, 0x0003, 0x0001, 0x0000,
    0x8000, 0xC000, 0xE000, 0xF000, 0xF800, 0xFC00, 0xFE00, 0xFF00,
    0xFF80, 0xFFC0, 0xFFE0, 0xFFF0, 0xFFF8, 0xFFFC, 0xFFFE, 0xFFFF,
    0x7FFF, 0x3FFF, 0x1FFF, 0x0FFF, 0x07FF, 0x03FF, 0x01FF, 0x00FF,
    0x007F, 0x003F, 0x001F, 0x000F, 0x0007, 0x0003, 0x0001, 0x0000
};


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Dp Mac Dphy Rxx Mapping to InputPort
// Input Value  : EnumDpMacDphySel
// Output Value : EnumInputPort
//--------------------------------------------------
EnumInputPort ScalerDpRxMacDphyGetInputPortSwitch(EnumDpMacDphySel enumDpMacDphySel)
{
    EnumInputPort enumInputPort = _NO_INPUT_PORT;

    switch(enumDpMacDphySel)
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

#if(_HW_D0_DP_MAC_DPHY_RX_MAPPING == _MAPPING_RX0)
            enumInputPort = _D0_INPUT_PORT;
#elif(_HW_D1_DP_MAC_DPHY_RX_MAPPING == _MAPPING_RX0)
            enumInputPort = _D1_INPUT_PORT;
#elif(_HW_D2_DP_MAC_DPHY_RX_MAPPING == _MAPPING_RX0)
            enumInputPort = _D2_INPUT_PORT;
#endif

            break;
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

#if(_HW_D0_DP_MAC_DPHY_RX_MAPPING == _MAPPING_RX1)
            enumInputPort = _D0_INPUT_PORT;
#elif(_HW_D1_DP_MAC_DPHY_RX_MAPPING == _MAPPING_RX1)
            enumInputPort = _D1_INPUT_PORT;
#elif(_HW_D2_DP_MAC_DPHY_RX_MAPPING == _MAPPING_RX1)
            enumInputPort = _D2_INPUT_PORT;
#endif

            break;
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

#if(_HW_D0_DP_MAC_DPHY_RX_MAPPING == _MAPPING_RX2)
            enumInputPort = _D0_INPUT_PORT;
#elif(_HW_D1_DP_MAC_DPHY_RX_MAPPING == _MAPPING_RX2)
            enumInputPort = _D1_INPUT_PORT;
#elif(_HW_D2_DP_MAC_DPHY_RX_MAPPING == _MAPPING_RX2)
            enumInputPort = _D2_INPUT_PORT;
#endif

            break;
#endif

#if(_DUAL_DP_SUPPORT == _ON)
        case _DP_MAC_DPHY_DUAL:

#if(_DUAL_DP_MAC_DPHY_USE == _DUAL_DP_MAC_RX0RX1)
            enumInputPort = _D7_INPUT_PORT;
#elif(_DUAL_DP_MAC_DPHY_USE == _DUAL_DP_MAC_RX1RX2)
            enumInputPort = _D8_INPUT_PORT;
#endif

            break;
#endif

        default:
            break;
    }

    return enumInputPort;
}

//--------------------------------------------------
// Description  : Get Mac Dphy Switch According to enumInputPort
// Input Value  : EnumInputPort
// Output Value : EnumDpMacDphySel
//--------------------------------------------------
EnumDpMacDphySel ScalerDpRxGetMacDphySwitch(EnumInputPort enumInputPort)
{
    EnumDpMacDphySel enumDpMacDphySel = _DP_MAC_DPHY_NONE;

    switch(enumInputPort)
    {
#if(_D0_DP_SUPPORT == _ON)
        case _D0_INPUT_PORT:

#if(_HW_D0_DP_MAC_DPHY_RX_MAPPING == _MAPPING_RX0)
            enumDpMacDphySel = _DP_MAC_DPHY_RX0;
#elif(_HW_D0_DP_MAC_DPHY_RX_MAPPING == _MAPPING_RX1)
            enumDpMacDphySel = _DP_MAC_DPHY_RX1;
#elif(_HW_D0_DP_MAC_DPHY_RX_MAPPING == _MAPPING_RX2)
            enumDpMacDphySel = _DP_MAC_DPHY_RX2;
#endif

            break;
#endif

#if(_D1_DP_SUPPORT == _ON)
        case _D1_INPUT_PORT:

#if(_HW_D1_DP_MAC_DPHY_RX_MAPPING == _MAPPING_RX0)
            enumDpMacDphySel = _DP_MAC_DPHY_RX0;
#elif(_HW_D1_DP_MAC_DPHY_RX_MAPPING == _MAPPING_RX1)
            enumDpMacDphySel = _DP_MAC_DPHY_RX1;
#elif(_HW_D1_DP_MAC_DPHY_RX_MAPPING == _MAPPING_RX2)
            enumDpMacDphySel = _DP_MAC_DPHY_RX2;
#endif

            break;
#endif

#if(_D2_DP_SUPPORT == _ON)
        case _D2_INPUT_PORT:

#if(_HW_D2_DP_MAC_DPHY_RX_MAPPING == _MAPPING_RX0)
            enumDpMacDphySel = _DP_MAC_DPHY_RX0;
#elif(_HW_D2_DP_MAC_DPHY_RX_MAPPING == _MAPPING_RX1)
            enumDpMacDphySel = _DP_MAC_DPHY_RX1;
#elif(_HW_D2_DP_MAC_DPHY_RX_MAPPING == _MAPPING_RX2)
            enumDpMacDphySel = _DP_MAC_DPHY_RX2;
#endif

            break;
#endif

#if(_D7_DP_SUPPORT == _ON)
        case _D7_INPUT_PORT:

            enumDpMacDphySel = _DP_MAC_DPHY_DUAL;

            break;
#endif

#if(_D8_DP_SUPPORT == _ON)
        case _D8_INPUT_PORT:

            enumDpMacDphySel = _DP_MAC_DPHY_DUAL;

            break;
#endif

        default:
            break;
    }

    return enumDpMacDphySel;
}

#if(_DP_RX_MSA_MISC_CHANGE_IRQ_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get MSA Color Space And Depth Change Flag Valid Or Not
// Input Value  : void
// Output Value : None
//--------------------------------------------------
bit ScalerDpRxColorSpaceAndDepthChangeFlagValidCheck(void)
{
    return _TRUE;
}
#endif

#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Get PXP MAC from D0 = 00, D1 = 01, D2 = 10 or 11
// Input Value  : None
// Output Value : enumInputPort
//--------------------------------------------------
EnumInputPort ScalerDpRxGetPxpInputPortMux(void)
{
    EnumInputPort enumInputPort = _NO_INPUT_PORT;
#if(_DP_MAC_RX0_SUPPORT == _ON)
    EnumDpMacSel enumDpMacSelStart = _DP_MAC_0;
#elif(_DP_MAC_RX1_SUPPORT == _ON)
    EnumDpMacSel enumDpMacSelStart = _DP_MAC_1;
#elif(_DP_MAC_RX2_SUPPORT == _ON)
    EnumDpMacSel enumDpMacSelStart = _DP_MAC_2;
#endif

    for(EnumDpMacSel enumDpMacSel = enumDpMacSelStart; enumDpMacSel < _DP_MAC_ENTITY_MAX; enumDpMacSel++)
    {
        if(ScalerDpRxMacGetInputPortSwitch(enumDpMacSel) == _D9_INPUT_PORT)
        {
            switch(enumDpMacSel)
            {
#if(_DP_MAC_RX0_SUPPORT == _ON)
                case _DP_MAC_0:

                    switch(ScalerGetBit(P6F_09_MUX_DPRX_MAC, (_BIT7 | _BIT6)))
                    {
                        default:
                        case 0x00:
                            enumInputPort = _D0_INPUT_PORT;
                            break;

                        case (_BIT6):
                            enumInputPort = _D1_INPUT_PORT;
                            break;

                        case (_BIT7):
                        case (_BIT7 | _BIT6):
                            enumInputPort = _D2_INPUT_PORT;
                            break;
                    }
                    break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
                case _DP_MAC_1:

                    switch(ScalerGetBit(P6F_09_MUX_DPRX_MAC, (_BIT5 | _BIT4)))
                    {
                        default:
                        case 0x00:
                            enumInputPort = _D0_INPUT_PORT;
                            break;

                        case (_BIT4):
                            enumInputPort = _D1_INPUT_PORT;
                            break;

                        case (_BIT5):
                        case (_BIT5 | _BIT4):
                            enumInputPort = _D2_INPUT_PORT;
                            break;
                    }
                    break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
                case _DP_MAC_2:

                    switch(ScalerGetBit(P6F_09_MUX_DPRX_MAC, (_BIT3 | _BIT2)))
                    {
                        default:
                        case 0x00:
                            enumInputPort = _D0_INPUT_PORT;
                            break;

                        case (_BIT2):
                            enumInputPort = _D1_INPUT_PORT;
                            break;

                        case (_BIT3):
                        case (_BIT3 | _BIT2):
                            enumInputPort = _D2_INPUT_PORT;
                            break;
                    }
                    break;
#endif
                default:
                    break;
            }
        }
    }
    return enumInputPort;
}

//--------------------------------------------------
// Description  : Set PXP MAC from D0 = 00, D1 = 01, D2 = 10 or 11
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpRxSetPxpInputPortMux(EnumInputPort enumInputPort)
{
#if(_DP_MAC_RX0_SUPPORT == _ON)
    EnumDpMacSel enumDpMacSelStart = _DP_MAC_0;
#elif(_DP_MAC_RX1_SUPPORT == _ON)
    EnumDpMacSel enumDpMacSelStart = _DP_MAC_1;
#elif(_DP_MAC_RX2_SUPPORT == _ON)
    EnumDpMacSel enumDpMacSelStart = _DP_MAC_2;
#endif

    for(EnumDpMacSel enumDpMacSel = enumDpMacSelStart; enumDpMacSel < _DP_MAC_ENTITY_MAX; enumDpMacSel++)
    {
        if(ScalerDpRxMacGetInputPortSwitch(enumDpMacSel) == _D9_INPUT_PORT)
        {
#if(_HW_DP_MAC_STREAM_SWITCH_SUPPORT == _ON)
            ScalerDpRxSetMacDphyToStreamMux(enumDpMacSel, enumInputPort);

            // Sync MST Mux
            ScalerDpMacDphyRxSyncSourceMux(enumDpMacSel, enumInputPort);
#endif
        }
    }
}

//--------------------------------------------------
// Description  : Reset PXP Inputport Mux
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpRxResetPxpInputPortMux(EnumInputPort enumInputPort)
{
#if(_DP_MAC_RX0_SUPPORT == _ON)
    EnumDpMacSel enumDpMacSelStart = _DP_MAC_0;
#elif(_DP_MAC_RX1_SUPPORT == _ON)
    EnumDpMacSel enumDpMacSelStart = _DP_MAC_1;
#elif(_DP_MAC_RX2_SUPPORT == _ON)
    EnumDpMacSel enumDpMacSelStart = _DP_MAC_2;
#endif

    if(ScalerDpRxGetPxpInputPortMux() == enumInputPort)
    {
        for(EnumDpMacSel enumDpMacSel = enumDpMacSelStart; enumDpMacSel < _DP_MAC_ENTITY_MAX; enumDpMacSel++)
        {
            if(ScalerDpRxMacGetInputPortSwitch(enumDpMacSel) == _D9_INPUT_PORT)
            {
#if(_HW_DP_MAC_STREAM_SWITCH_SUPPORT == _ON)
                ScalerDpRxMacDphyToStreamMuxReset(enumDpMacSel);
#endif
            }
        }
    }
}
#endif

//--------------------------------------------------
// Description  : DP NF PLL Rs And Icp Register Value Calculate
// Input Value  : ucNcode --> PLL N Code
// Output Value : None
//--------------------------------------------------
BYTE ScalerDpRxPllRsIcpCalculate(BYTE ucNcode)
{
    // Cal Rs, Cs, Icp
    // Icp = loopdivider / 4
    PDATA_DWORD(0) = ((DWORD)ucNcode * 20) / 4;
    pData[1] = (PDATA_DWORD(0) + 25) / 50;
    pData[1] -= (pData[1] == 0) ? 0 : 1;

    // Set Icp , RS:RL6952 default 12.5K, RS:reserved, Icp = 2.5uA + 2.5uA*bit[0] + 5uA*bit[1] + 10uA*bit[2]
    pData[2] = (_BIT7 | _BIT4 | _BIT3 | (pData[1] & 0x07));

    return pData[2];
}

#endif // #if(_DP_SUPPORT == _ON)

