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
// ID Code      : ScalerDpMacDphyRx.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_DP_MAC_DPHY_RX__

#include "ScalerFunctionInclude.h"
#include "DpMacDphyRx/ScalerDpMacDphyRx.h"

#if(_DP_SUPPORT == _ON)
//****************************************************************************
// CODE TABLES
//****************************************************************************
#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
WORD code tDpMacRxPbnMappingUhbr20G4Lane[64] =
{
    179, 358, 537, 716, 895, 1074, 1253, 1432, 1611, 1790, 1970, 2149, 2328, 2507, 2686, 2865, 3044, 3223, 3402, 3581, 3760, 3940, 4119, 4298, 4477, 4656, 4835, 5014, 5193, 5372, 5551, 5731, 5910, 6089, 6268, 6447, 6626, 6805, 6984, 7163, 7342, 7521, 7701, 7880, 8059, 8238, 8417, 8596, 8775, 8954, 9133, 9312, 9492, 9671, 9850, 10029, 10208, 10387, 10566, 10745, 10924, 11103, 11282, 11462,
};

WORD code tDpMacRxPbnMappingUhbr20G2Lane[64] =
{
    89, 179, 268, 358, 447, 537, 626, 716, 805, 895, 985, 1074, 1164, 1253, 1343, 1432, 1522, 1611, 1701, 1790, 1880, 1970, 2059, 2149, 2238, 2328, 2417, 2507, 2596, 2686, 2775, 2865, 2955, 3044, 3134, 3223, 3313, 3402, 3492, 3581, 3671, 3760, 3850, 3940, 4029, 4119, 4208, 4298, 4387, 4477, 4566, 4656, 4745, 4835, 4925, 5014, 5104, 5193, 5283, 5372, 5462, 5551, 5641, 5730,
};

WORD code tDpMacRxPbnMappingUhbr20G1Lane[64] =
{
    44, 89, 134, 179, 223, 268, 313, 358, 402, 447, 492, 537, 582, 626, 671, 716, 761, 805, 850, 895, 940, 985, 1029, 1074, 1119, 1164, 1208, 1253, 1298, 1343, 1387, 1432, 1477, 1522, 1567, 1611, 1656, 1701, 1746, 1790, 1835, 1880, 1925, 1970, 2014, 2059, 2104, 2149, 2193, 2238, 2283, 2328, 2373, 2417, 2462, 2507, 2552, 2596, 2641, 2686, 2731, 2775, 2820, 2865,
};

WORD code tDpMacRxPbnMappingUhbr13p5G4Lane[64] =
{
    120, 241, 362, 483, 604, 725, 846, 967, 1087, 1208, 1329, 1450, 1571, 1692, 1813, 1934, 2055, 2175, 2296, 2417, 2538, 2659, 2780, 2901, 3022, 3143, 3263, 3384, 3505, 3626, 3747, 3868, 3989, 4110, 4231, 4351, 4472, 4593, 4714, 4835, 4956, 5077, 5198, 5319, 5439, 5560, 5681, 5802, 5923, 6044, 6165, 6286, 6407, 6527, 6648, 6769, 6890, 7011, 7132, 7253, 7374, 7494, 7615, 7736,
};

WORD code tDpMacRxPbnMappingUhbr13p5G2Lane[64] =
{
    60, 120, 181, 241, 302, 362, 423, 483, 544, 604, 664, 725, 785, 846, 906, 967, 1027, 1088, 1148, 1208, 1269, 1329, 1390, 1450, 1511, 1571, 1632, 1692, 1752, 1813, 1873, 1934, 1994, 2055, 2115, 2176, 2236, 2296, 2357, 2417, 2478, 2538, 2599, 2659, 2720, 2780, 2840, 2901, 2961, 3022, 3082, 3143, 3203, 3264, 3324, 3384, 3445, 3505, 3566, 3626, 3687, 3747, 3808, 3868,
};

WORD code tDpMacRxPbnMappingUhbr13p5G1Lane[64] =
{
    30, 60, 90, 120, 151, 181, 211, 241, 272, 302, 332, 362, 392, 423, 453, 483, 513, 544, 574, 604, 634, 664, 695, 725, 755, 785, 816, 846, 876, 906, 936, 967, 997, 1027, 1057, 1088, 1118, 1148, 1178, 1208, 1239, 1269, 1299, 1329, 1360, 1390, 1420, 1450, 1480, 1511, 1541, 1571, 1601, 1632, 1662, 1692, 1722, 1752, 1783, 1813, 1843, 1873, 1904, 1934,
};

WORD code tDpMacRxPbnMappingUhbr10G4Lane[64] =
{
    89, 179, 268, 358, 447, 537, 626, 716, 805, 895, 985, 1074, 1164, 1253, 1343, 1432, 1522, 1611, 1701, 1790, 1880, 1970, 2059, 2149, 2238, 2328, 2417, 2507, 2596, 2686, 2775, 2865, 2955, 3044, 3134, 3223, 3313, 3402, 3492, 3581, 3671, 3760, 3850, 3940, 4029, 4119, 4208, 4298, 4387, 4477, 4566, 4656, 4745, 4835, 4925, 5014, 5104, 5193, 5283, 5372, 5462, 5551, 5641, 5730,
};

WORD code tDpMacRxPbnMappingUhbr10G2Lane[64] =
{
    44, 89, 134, 179, 223, 268, 313, 358, 402, 447, 492, 537, 582, 626, 671, 716, 761, 805, 850, 895, 940, 985, 1029, 1074, 1119, 1164, 1208, 1253, 1298, 1343, 1387, 1432, 1477, 1522, 1567, 1611, 1656, 1701, 1746, 1790, 1835, 1880, 1925, 1970, 2014, 2059, 2104, 2149, 2193, 2238, 2283, 2328, 2373, 2417, 2462, 2507, 2552, 2596, 2641, 2686, 2731, 2775, 2820, 2865,
};

WORD code tDpMacRxPbnMappingUhbr10G1Lane[64] =
{
    22, 44, 67, 89, 111, 134, 156, 179, 201, 223, 246, 268, 291, 313, 335, 358, 380, 402, 425, 447, 470, 492, 514, 537, 559, 582, 604, 626, 649, 671, 693, 716, 738, 761, 783, 805, 828, 850, 873, 895, 917, 940, 962, 985, 1007, 1029, 1052, 1074, 1096, 1119, 1141, 1164, 1186, 1208, 1231, 1253, 1276, 1298, 1320, 1343, 1365, 1387, 1410, 1432,
};
#endif


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
#if((_DP_MST_SUPPORT == _ON) || (_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON))
// MST Rx stream
volatile BYTE g_ppucDpMacDphyRxStreamToIdMapping[_DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS][_HW_DP_MST_ST_SOURCE_COUNT];
volatile StructRxStreamInfoBackup g_pstDpMacDphyRxStreamInfoBackup[_DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS];
volatile bit g_pbDpMacDphyRxManualForceSetAct[_DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS];
volatile EnumDpStreamNum g_ppenumDpMacDphyRxStreamAllocateInfo[_DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS][_DP_TOTAL_MAC_NEEDED_PORT];
#endif

#if(_HW_DP_MAC_POWER_CUT_GEN == _DP_MAC_POWER_CUT_SEPARATE)
StructDpMacDphyRxPowerStatus g_stDpMacDphyRxPowerStatus;
#endif


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_DP_MST_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP MST Set St_source Mux Register
// Input Value  : enumSourceNum, ucValue
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxSetSourceMuxReg_8b10b(EnumInputPort enumInputPort, EnumDpStreamSourceNum enumSourceNum, EnumDpStreamNum enumDpStreamNum)
{
    BYTE ucValue = (enumDpStreamNum == _DP_ST_NONE) ? 0 : enumDpStreamNum + 1;

    switch(enumSourceNum)
    {
        case _DP_ST_SOURCE1:

            ScalerSetBit(ScalerDpMacDphyRxGetPagedAddress(enumInputPort, PB5_12_SOURCE_SEL_0), ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), ucValue << 4);
            break;

        case _DP_ST_SOURCE2:

            ScalerSetBit(ScalerDpMacDphyRxGetPagedAddress(enumInputPort, PB5_12_SOURCE_SEL_0), ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ucValue << 0);
            break;

        case _DP_ST_SOURCE3:

            ScalerSetBit(ScalerDpMacDphyRxGetPagedAddress(enumInputPort, PB5_13_SOURCE_SEL_1), ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), ucValue << 4);
            break;

        case _DP_ST_SOURCE4:

            ScalerSetBit(ScalerDpMacDphyRxGetPagedAddress(enumInputPort, PB5_13_SOURCE_SEL_1), ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ucValue << 0);
            break;

        case _DP_ST_SOURCE5:

            ScalerSetBit(ScalerDpMacDphyRxGetPagedAddress(enumInputPort, PB5_14_SOURCE_SEL_2), ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), ucValue << 4);
            break;

        case _DP_ST_SOURCE6:

            ScalerSetBit(ScalerDpMacDphyRxGetPagedAddress(enumInputPort, PB5_14_SOURCE_SEL_2), ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ucValue << 0);
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Reset ST1_Source ~ ST5_Source Mux
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxResetSourceMuxReg_8b10b(EnumInputPort enumInputPort)
{
    ScalerSetBit(ScalerDpMacDphyRxGetPagedAddress(enumInputPort, PB5_12_SOURCE_SEL_0), ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);
    ScalerSetBit(ScalerDpMacDphyRxGetPagedAddress(enumInputPort, PB5_12_SOURCE_SEL_0), ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(ScalerDpMacDphyRxGetPagedAddress(enumInputPort, PB5_13_SOURCE_SEL_1), ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);
    ScalerSetBit(ScalerDpMacDphyRxGetPagedAddress(enumInputPort, PB5_13_SOURCE_SEL_1), ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(ScalerDpMacDphyRxGetPagedAddress(enumInputPort, PB5_14_SOURCE_SEL_2), ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);
    ScalerSetBit(ScalerDpMacDphyRxGetPagedAddress(enumInputPort, PB5_14_SOURCE_SEL_2), ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
}

//--------------------------------------------------
// Description  : DP Mst Rx Load New Stream PayLoad
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxLoadNewStreamPayload_8b10b(EnumInputPort enumInputPort)
{
    // Load by MTPH_CNT = 63, Delay 5us, Then Load by Receiving ACT
    ScalerSetBit(ScalerDpMacDphyRxGetPagedAddress(enumInputPort, PB5_01_STHD_CTRL_1), ~_BIT7, 0x00);
    DELAY_5US();
    ScalerSetBit(ScalerDpMacDphyRxGetPagedAddress(enumInputPort, PB5_01_STHD_CTRL_1), ~_BIT7, _BIT7);
}
#endif // End of #if(_DP_MST_SUPPORT == _ON)

//--------------------------------------------------
// Description  : Dp Mac Dphy Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxInitial(EnumInputPort enumInputPort)
{
    enumInputPort = enumInputPort;

#if((_DP_MST_SUPPORT == _ON) || (_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON))
    ScalerDpMacDphyRxResetStreamAllocateInfo(enumInputPort);
#endif
}

#if(_HW_DP_MAC_POWER_CUT_GEN == _DP_MAC_POWER_CUT_SEPARATE)
//--------------------------------------------------
// Description  : DP MAC power process
// Input Value  : EnumInputPort, EnumPowerAction
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxPowerProc(EnumInputPort enumInputPort, EnumPowerAction enumPowerAction)
{
    EnumDpMacDphySel enumDpMacDphySel = ScalerDpRxGetMacDphySwitch(enumInputPort);

#if((_AUDIO_SUPPORT == _ON) && (_INTERNAL_AUDIO_TEST_SUPPORT == _ON) && (_INTERNAL_AUDIO_TEST_FIX_AUDIO_OUTPUT == _ON))
    // Ignore Power Control when in Audio Pattern Gen
    if(ScalerAudioGetInternalAudioGenEnable(enumInputPort) == _ENABLE)
    {
        return;
    }
#endif

    switch(enumDpMacDphySel)
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

            ScalerDpMacDphyRx0PowerProc(enumPowerAction);

            break;
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            ScalerDpMacDphyRx1PowerProc(enumPowerAction);

            break;
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            ScalerDpMacDphyRx2PowerProc(enumPowerAction);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Get DP Mac RX Power Cut Status
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpMacDphyRxGetPowerCutFlagStatus(EnumInputPort enumInputPort)
{
    switch(ScalerDpRxGetMacDphySwitch(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

            return GET_DP_MAC_DPHY_RX0_POWER_CUT_STATUS();
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            return GET_DP_MAC_DPHY_RX1_POWER_CUT_STATUS();
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            return GET_DP_MAC_DPHY_RX2_POWER_CUT_STATUS();
#endif

        default:
            break;
    }

    return _FALSE;
}
#endif

//--------------------------------------------------
// Description  : Dp Digital Phy Initial Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxDigitalPhyInitial(EnumInputPort enumInputPort)
{
#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
    if(enumInputPort == _D9_INPUT_PORT)
    {
        enumInputPort = GET_DP_MST_RX_PXP_INPUT_PORT();
    }
#endif

    switch(ScalerDpRxGetMacDphySwitch(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

            ScalerDpMacDphyRx0DigitalPhyInitial();

            break;
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            ScalerDpMacDphyRx1DigitalPhyInitial();

            break;
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            ScalerDpMacDphyRx2DigitalPhyInitial();

            break;
#endif

#if(_DUAL_DP_SUPPORT == _ON)
        case _DP_MAC_DPHY_DUAL:

#if(_DUAL_DP_MAC_DPHY_USE == _DUAL_DP_MAC_DPHY_RX0RX1)
            ScalerDpMacDphyRx0DigitalPhyInitial();
            ScalerDpMacDphyRx1DigitalPhyInitial();
#elif(_DUAL_DP_MAC_DPHY_USE == _DUAL_DP_MAC_DPHY_RX1RX2)
            ScalerDpMacDphyRx1DigitalPhyInitial();
            ScalerDpMacDphyRx2DigitalPhyInitial();
#endif

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Check Dp Training Pattern 1 for PHY CTS
// Input Value  : None
// Output Value : TRUE --> TP1 Pass
//--------------------------------------------------
bit ScalerDpMacDphyRxPhyCtsTp1Check(EnumInputPort enumInputPort)
{
#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
    if(enumInputPort == _D9_INPUT_PORT)
    {
        enumInputPort = GET_DP_MST_RX_PXP_INPUT_PORT();
    }
#endif

    switch(ScalerDpRxGetMacDphySwitch(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)

        case _DP_MAC_DPHY_RX0:

            return ScalerDpMacDphyRx0PhyCtsTp1Check();
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)

        case _DP_MAC_DPHY_RX1:

            return ScalerDpMacDphyRx1PhyCtsTp1Check();
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)

        case _DP_MAC_DPHY_RX2:

            return ScalerDpMacDphyRx2PhyCtsTp1Check();
#endif

        default:

            return _FALSE;
    }
}

//--------------------------------------------------
// Description  : Check Dp Training Pattern 2 for PHY CTS
// Input Value  : None
// Output Value : TRUE --> TP2 Pass
//--------------------------------------------------
bit ScalerDpMacDphyRxPhyCtsTp2Check(EnumInputPort enumInputPort)
{
#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
    if(enumInputPort == _D9_INPUT_PORT)
    {
        enumInputPort = GET_DP_MST_RX_PXP_INPUT_PORT();
    }
#endif

    switch(ScalerDpRxGetMacDphySwitch(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)

        case _DP_MAC_DPHY_RX0:

            return ScalerDpMacDphyRx0PhyCtsTp2Check();
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)

        case _DP_MAC_DPHY_RX1:

            return ScalerDpMacDphyRx1PhyCtsTp2Check();
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)

        case _DP_MAC_DPHY_RX2:

            return ScalerDpMacDphyRx2PhyCtsTp2Check();
#endif

        default:

            return _FALSE;
    }
}

//--------------------------------------------------
// Description  : DP Scramble Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxScrambleSetting(EnumInputPort enumInputPort)
{
#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
    if(enumInputPort == _D9_INPUT_PORT)
    {
        enumInputPort = GET_DP_MST_RX_PXP_INPUT_PORT();
    }
#endif

    switch(ScalerDpRxGetMacDphySwitch(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

            ScalerDpMacDphyRx0ScrambleSetting();

            break;
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            ScalerDpMacDphyRx1ScrambleSetting();

            break;
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            ScalerDpMacDphyRx2ScrambleSetting();

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Set DP MAC Error Count Reset
// Input Value  : Rx Error Count Decode Method
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxDecodeErrorCountReset(EnumInputPort enumInputPort, EnumDpMacDecodeMethod enumDpMacDecodeMethod)
{
#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
    if(enumInputPort == _D9_INPUT_PORT)
    {
        enumInputPort = GET_DP_MST_RX_PXP_INPUT_PORT();
    }
#endif

    switch(ScalerDpRxGetMacDphySwitch(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

            ScalerDpMacDphyRx0DecodeErrorCountReset(enumDpMacDecodeMethod);

            break;
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            ScalerDpMacDphyRx1DecodeErrorCountReset(enumDpMacDecodeMethod);

            break;
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            ScalerDpMacDphyRx2DecodeErrorCountReset(enumDpMacDecodeMethod);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description : Measure 8b10b Error Count Per Lane
// Input Value  : DP Lane
// Output Value : True --> locked; False --> unlocked
//--------------------------------------------------
bit ScalerDpMacDphyRxDecodeErrorCountLaneMeasure(EnumInputPort enumInputPort, WORD usErrorCriteria, BYTE ucDpMacLaneNumber)
{
#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
    if(enumInputPort == _D9_INPUT_PORT)
    {
        enumInputPort = GET_DP_MST_RX_PXP_INPUT_PORT();
    }
#endif

    switch(ScalerDpRxGetMacDphySwitch(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)

        case _DP_MAC_DPHY_RX0:

            return ScalerDpMacDphyRx0DecodeErrorCountLaneMeasure(usErrorCriteria, ucDpMacLaneNumber);
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)

        case _DP_MAC_DPHY_RX1:

            return ScalerDpMacDphyRx1DecodeErrorCountLaneMeasure(usErrorCriteria, ucDpMacLaneNumber);
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)

        case _DP_MAC_DPHY_RX2:

            return ScalerDpMacDphyRx2DecodeErrorCountLaneMeasure(usErrorCriteria, ucDpMacLaneNumber);
#endif

        default:

            return _FALSE;
    }
}

//--------------------------------------------------
// Description : Get 8b10b Error Count Per Lane
// Input Value  : DP Lane
// Output Value : Error Count
//--------------------------------------------------
WORD ScalerDpMacDphyRxGetDecodeErrorCount(EnumInputPort enumInputPort, BYTE ucDpMacLaneNumber)
{
#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
    if(enumInputPort == _D9_INPUT_PORT)
    {
        enumInputPort = GET_DP_MST_RX_PXP_INPUT_PORT();
    }
#endif

    switch(ScalerDpRxGetMacDphySwitch(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)

        case _DP_MAC_DPHY_RX0:

            return ScalerDpMacDphyRx0GetDecodeErrorCount(ucDpMacLaneNumber);
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)

        case _DP_MAC_DPHY_RX1:

            return ScalerDpMacDphyRx1GetDecodeErrorCount(ucDpMacLaneNumber);
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)

        case _DP_MAC_DPHY_RX2:

            return ScalerDpMacDphyRx2GetDecodeErrorCount(ucDpMacLaneNumber);
#endif

        default:

            return _FALSE;
    }
}

//-----------------------------------------------------------------------
// Description  : Set DP PHY to MAC Lane Swap / PN Swap / Clock Selection
// Input Value  : None
// Output Value : None
//-----------------------------------------------------------------------
void ScalerDpMacDphyRxLaneSwapSelect(EnumInputPort enumInputPort, BYTE ucClockLaneSelect)
{
#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
    if(enumInputPort == _D9_INPUT_PORT)
    {
        enumInputPort = GET_DP_MST_RX_PXP_INPUT_PORT();
    }
#endif

    switch(ScalerDpRxGetMacDphySwitch(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

            ScalerDpMacDphyRx0LaneSwapSelect(enumInputPort, ucClockLaneSelect);

            break;
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            ScalerDpMacDphyRx1LaneSwapSelect(enumInputPort, ucClockLaneSelect);

            break;
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            ScalerDpMacDphyRx2LaneSwapSelect(enumInputPort, ucClockLaneSelect);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Digital Phy Reset
// Input Value  : EnumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxDigitalPhyReset(EnumInputPort enumInputPort)
{
#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
    if(enumInputPort == _D9_INPUT_PORT)
    {
        enumInputPort = GET_DP_MST_RX_PXP_INPUT_PORT();
    }
#endif

    switch(ScalerDpRxGetMacDphySwitch(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

#if(_DP_MAC_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
            {
                SET_DP_MAC_DPHY_RX0_DIGITAL_PHY_RESET_128B132B();
            }
            else
#endif
            {
                SET_DP_MAC_DPHY_RX0_DIGITAL_PHY_RESET_8B10B();
            }

            break;
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
            {
                SET_DP_MAC_DPHY_RX1_DIGITAL_PHY_RESET_128B132B();
            }
            else
#endif
            {
                SET_DP_MAC_DPHY_RX1_DIGITAL_PHY_RESET_8B10B();
            }

            break;
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

#if(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
            {
                SET_DP_MAC_DPHY_RX2_DIGITAL_PHY_RESET_128B132B();
            }
            else
#endif
            {
                SET_DP_MAC_DPHY_RX2_DIGITAL_PHY_RESET_8B10B();
            }

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Set DP MAC Lane Count
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxLaneCountSet(EnumInputPort enumInputPort, BYTE ucDpLaneCount)
{
#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
    if(enumInputPort == _D9_INPUT_PORT)
    {
        enumInputPort = GET_DP_MST_RX_PXP_INPUT_PORT();
    }
#endif

    switch(ScalerDpRxGetMacDphySwitch(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

            ScalerDpMacDphyRx0LaneCountSet(ucDpLaneCount);

            break;
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            ScalerDpMacDphyRx1LaneCountSet(ucDpLaneCount);

            break;
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            ScalerDpMacDphyRx2LaneCountSet(ucDpLaneCount);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Set DP MAC Set Comma Detect
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxSetCommaDetect(EnumInputPort enumInputPort, bit bEn)
{
#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
    if(enumInputPort == _D9_INPUT_PORT)
    {
        enumInputPort = GET_DP_MST_RX_PXP_INPUT_PORT();
    }
#endif

    switch(ScalerDpRxGetMacDphySwitch(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

            ScalerDpMacDphyRx0SetCommaDetect(bEn);

            break;
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            ScalerDpMacDphyRx1SetCommaDetect(bEn);

            break;
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            ScalerDpMacDphyRx2SetCommaDetect(bEn);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Set DP MAC Lane Count
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE ScalerDpMacDphyRxGetLaneMuxMapping(EnumInputPort enumInputPort, EnumDpLane enumDpLane)
{
#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
    if(enumInputPort == _D9_INPUT_PORT)
    {
        enumInputPort = GET_DP_MST_RX_PXP_INPUT_PORT();
    }
#endif

    switch(ScalerDpRxGetMacDphySwitch(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

            return ScalerDpMacDphyRx0GetLaneMuxMapping(enumDpLane);
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            return ScalerDpMacDphyRx1GetLaneMuxMapping(enumDpLane);
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            return ScalerDpMacDphyRx2GetLaneMuxMapping(enumDpLane);
#endif

        default:

            return 0x00;
    }
}

//--------------------------------------------------
// Description  : Set DP MAC Clock Selection
// Input Value  : Link Clock or XTAL Clock
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxClkSelect(EnumInputPort enumInputPort, EnumDpMacClkSelect enumClkSelect)
{
#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
    if(enumInputPort == _D9_INPUT_PORT)
    {
        enumInputPort = GET_DP_MST_RX_PXP_INPUT_PORT();
    }
#endif

    switch(ScalerDpRxGetMacDphySwitch(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

            ScalerDpMacDphyRx0ClkSelect(enumClkSelect);

            break;
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            ScalerDpMacDphyRx1ClkSelect(enumClkSelect);

            break;
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            ScalerDpMacDphyRx2ClkSelect(enumClkSelect);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Reset DP MAC FIFIO
// Input Value  : Inputport
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxChannelFifoReset(EnumInputPort enumInputPort)
{
#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
    if(enumInputPort == _D9_INPUT_PORT)
    {
        enumInputPort = GET_DP_MST_RX_PXP_INPUT_PORT();
    }
#endif

    switch(ScalerDpRxGetMacDphySwitch(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

            ScalerDpMacDphyRx0ChannelFifoReset();

            break;
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            ScalerDpMacDphyRx1ChannelFifoReset();

            break;
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            ScalerDpMacDphyRx2ChannelFifoReset();

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Get Dp Mac Rx Paged Address
// Input Value  : enumInputPort, usMac0Addr
// Output Value : Paged Address
//--------------------------------------------------
WORD ScalerDpMacDphyRxGetPagedAddress(EnumInputPort enumInputPort, WORD usMac0Addr)
{
    WORD usBasePage = usMac0Addr >> 8;

#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
    if(enumInputPort == _D9_INPUT_PORT)
    {
        enumInputPort = GET_DP_MST_RX_PXP_INPUT_PORT();
    }
#endif

    EnumDpMacDphySel enumDpMacDphy = ScalerDpRxGetMacDphySwitch(enumInputPort);

    switch(usBasePage)
    {
        case _PAGEB:

            switch(enumDpMacDphy)
            {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
                case _DP_MAC_DPHY_RX0:

                    return GET_PAGED_ADDR(_PAGEB, usMac0Addr);
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
                case _DP_MAC_DPHY_RX1:

                    return GET_PAGED_ADDR(_PAGEB0, usMac0Addr);
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
                case _DP_MAC_DPHY_RX2:

                    return GET_PAGED_ADDR(_PAGEC5, usMac0Addr);
#endif
                default:

                    return usMac0Addr;
            }

        case _PAGEB5:

            switch(enumDpMacDphy)
            {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
                case _DP_MAC_DPHY_RX0:

                    return GET_PAGED_ADDR(_PAGEB5, usMac0Addr);
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
                case _DP_MAC_DPHY_RX1:

                    return GET_PAGED_ADDR(_PAGEB8, usMac0Addr);
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
                case _DP_MAC_DPHY_RX2:

                    return GET_PAGED_ADDR(_PAGEC6, usMac0Addr);
#endif
                default:

                    return usMac0Addr;
            }

        case _PAGE9D:

            switch(enumDpMacDphy)
            {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
                case _DP_MAC_DPHY_RX0:

                    return GET_PAGED_ADDR(_PAGE9D, usMac0Addr);
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
                case _DP_MAC_DPHY_RX1:

                    return GET_PAGED_ADDR(_PAGE9F, usMac0Addr);
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
                case _DP_MAC_DPHY_RX2:

                    return GET_PAGED_ADDR(_PAGEE4, usMac0Addr);
#endif
                default:

                    return usMac0Addr;
            }

        default:

            return usMac0Addr;
    }
}

//--------------------------------------------------
// Description  : HDCP 1.4 Reset Proc for MAC RX
// Input Value  : PORT
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxHdcp14ResetProc(EnumInputPort enumInputPort)
{
#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
    if(enumInputPort == _D9_INPUT_PORT)
    {
        enumInputPort = GET_DP_MST_RX_PXP_INPUT_PORT();
    }
#endif

    switch(ScalerDpRxGetMacDphySwitch(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

            ScalerDpMacDphyRx0Hdcp14ResetProc();

            break;
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            ScalerDpMacDphyRx1Hdcp14ResetProc();

            break;
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            ScalerDpMacDphyRx2Hdcp14ResetProc();

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Check DP Hdcp ReAuth Process
// Input Value  : None
// Output Value : TRUE or FALSE
//--------------------------------------------------
bit ScalerDpMacDphyRxHdcpReAuthStatusCheck(EnumInputPort enumInputPort)
{
#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
    if(enumInputPort == _D9_INPUT_PORT)
    {
        enumInputPort = GET_DP_MST_RX_PXP_INPUT_PORT();
    }
#endif

    switch(ScalerDpRxGetMacDphySwitch(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

            return ScalerDpMacDphyRx0HdcpReAuthStatusCheck();
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            return ScalerDpMacDphyRx1HdcpReAuthStatusCheck();
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            return ScalerDpMacDphyRx2HdcpReAuthStatusCheck();
#endif

        default:

            return _FALSE;
    }
}

//--------------------------------------------------
// Description  : DP Hdcp Enable Link Integrity
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxLinkIntegrityEnable(void)
{
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
    // Enable DP Link Integrity Enable
    SET_DP_MAC_DPHY_RX0_LINK_INTEGRITY_8B10B();
#if(_DP_MAC_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
    SET_DP_MAC_DPHY_RX0_LINK_INTEGRITY_128B132B();
#endif
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
    // Enable DP Link Integrity Enable
    SET_DP_MAC_DPHY_RX1_LINK_INTEGRITY_8B10B();
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    SET_DP_MAC_DPHY_RX1_LINK_INTEGRITY_128B132B();
#endif
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
    // Enable DP Link Integrity Enable
    SET_DP_MAC_DPHY_RX2_LINK_INTEGRITY_8B10B();
#if(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
    SET_DP_MAC_DPHY_RX2_LINK_INTEGRITY_128B132B();
#endif
#endif
}

//--------------------------------------------------
// Description  : Enable/Disable DownLoad HDCP Key
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxHdcpDownLoadKey(bit bEnable)
{
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
    ScalerDpMacDphyRx0HdcpDownLoadKey(bEnable);
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
    ScalerDpMacDphyRx1HdcpDownLoadKey(bEnable);
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
    ScalerDpMacDphyRx2HdcpDownLoadKey(bEnable);
#endif
}

//--------------------------------------------------
// Description  : DownLoad HDCP Key to SRAM
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxHdcpDownLoadKeyToSram(WORD usLength, BYTE *pucReadArray)
{
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
    // Download HDCP Key to SRAM
    ScalerDpMacDphyRx0HdcpDownLoadKeyToSram(usLength, pucReadArray);
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
    // Download HDCP Key to SRAM
    ScalerDpMacDphyRx1HdcpDownLoadKeyToSram(usLength, pucReadArray);
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
    // Download HDCP Key to SRAM
    ScalerDpMacDphyRx2HdcpDownLoadKeyToSram(usLength, pucReadArray);
#endif
}

//--------------------------------------------------
// Description  : Clear CPIRQ Flag
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxCheckHdcpCpirqStatus(EnumInputPort enumInputPort)
{
#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
    if(enumInputPort == _D9_INPUT_PORT)
    {
        enumInputPort = GET_DP_MST_RX_PXP_INPUT_PORT();
    }
#endif

    switch(ScalerDpRxGetMacDphySwitch(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

            ScalerDpMacDphyRx0CheckHdcpCpirqStatus();

            break;
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            ScalerDpMacDphyRx1CheckHdcpCpirqStatus();

            break;
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            ScalerDpMacDphyRx2CheckHdcpCpirqStatus();

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : DP Content Protection Interrupt Request
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxCpIRQ(EnumInputPort enumInputPort, EnumDpRxBStatusType enumBStatusType)
{
#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
    if(enumInputPort == _D9_INPUT_PORT)
    {
        enumInputPort = GET_DP_MST_RX_PXP_INPUT_PORT();
    }
#endif

    switch(ScalerDpRxGetMacDphySwitch(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

            ScalerDpMacDphyRx0CpIRQ(enumBStatusType);

            break;
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            ScalerDpMacDphyRx1CpIRQ(enumBStatusType);

            break;
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            ScalerDpMacDphyRx2CpIRQ(enumBStatusType);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Check whether HDCP is valid
// Input Value  : None
// Output Value : TRUE => HDCP valid
//--------------------------------------------------
bit ScalerDpMacDphyRxHdcpCheckValid(EnumInputPort enumInputPort)
{
#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
    if(enumInputPort == _D9_INPUT_PORT)
    {
        enumInputPort = GET_DP_MST_RX_PXP_INPUT_PORT();
    }
#endif

    switch(ScalerDpRxGetMacDphySwitch(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

            return ScalerDpMacDphyRx0HdcpCheckValid();
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            return ScalerDpMacDphyRx1HdcpCheckValid();
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            return ScalerDpMacDphyRx2HdcpCheckValid();
#endif

#if(_DUAL_DP_SUPPORT == _ON)
        case _DP_MAC_DPHY_DUAL:

#if(_DUAL_DP_MAC_DPHY_USE == _DUAL_DP_MAC_DPHY_RX0RX1)
            return (ScalerDpMacDphyRx0HdcpCheckValid() && ScalerDpMacDphyRx1HdcpCheckValid());
#elif(_DUAL_DP_MAC_DPHY_USE == _DUAL_DP_MAC_DPHY_RX1RX2)
            return (ScalerDpMacDphyRx1HdcpCheckValid() && ScalerDpMacDphyRx2HdcpCheckValid());
#endif
#endif
        default:

            return _FALSE;
    }
}

//--------------------------------------------------
// Description  : Check whether HDCP is enabled
// Input Value  : None
// Output Value : TRUE => HDCP Enabled
//--------------------------------------------------
bit ScalerDpMacDphyRxHdcpCheckEnabled(EnumInputPort enumInputPort)
{
#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
    if(enumInputPort == _D9_INPUT_PORT)
    {
        enumInputPort = GET_DP_MST_RX_PXP_INPUT_PORT();
    }
#endif

    switch(ScalerDpRxGetMacDphySwitch(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

            return ScalerDpMacDphyRx0HdcpCheckEnabled();
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            return ScalerDpMacDphyRx1HdcpCheckEnabled();
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            return ScalerDpMacDphyRx2HdcpCheckEnabled();
#endif

        default:

            return _FALSE;
    }
}

//--------------------------------------------------
// Description  : DP Mst Mode Config
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxSetHdcpMode(EnumInputPort enumInputPort, EnumHDCPType enumHDCPType)
{
#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
    if(enumInputPort == _D9_INPUT_PORT)
    {
        enumInputPort = GET_DP_MST_RX_PXP_INPUT_PORT();
    }
#endif

    switch(ScalerDpRxGetMacDphySwitch(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

            // Enable HDCP MAC0
            ScalerDpMacDphyRx0SetHdcpMode(enumHDCPType);

            break;
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            // Enable HDCP MAC1
            ScalerDpMacDphyRx1SetHdcpMode(enumHDCPType);

            break;
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            // Enable HDCP MAC2
            ScalerDpMacDphyRx2SetHdcpMode(enumHDCPType);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Check DP Link Integrity
// Input Value  : enumInputPort
// Output Value : FALSE => DP Link Integrity Fail
//--------------------------------------------------
bit ScalerDpMacDphyRxHdcpCheck(EnumInputPort enumInputPort)
{
#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
    if(enumInputPort == _D9_INPUT_PORT)
    {
        enumInputPort = GET_DP_MST_RX_PXP_INPUT_PORT();
    }
#endif

    switch(ScalerDpRxGetMacDphySwitch(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

#if(_DP_MAC_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
            {
                return ScalerDpMacDphyRx0HdcpCheck_128b132b();
            }
            else
#endif
            {
                return ScalerDpMacDphyRx0HdcpCheck_8b10b();
            }
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
            {
                return ScalerDpMacDphyRx1HdcpCheck_128b132b();
            }
            else
#endif
            {
                return ScalerDpMacDphyRx1HdcpCheck_8b10b();
            }
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

#if(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
            {
                return ScalerDpMacDphyRx2HdcpCheck_128b132b();
            }
            else
#endif
            {
                return ScalerDpMacDphyRx2HdcpCheck_8b10b();
            }
#endif
        default:

            break;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Set DPRX SRAM CLK Gate
// Input Value  : PORT
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxHdcpSramClkGate(EnumInputPort enumInputPort, bit bEnable)
{
#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
    if(enumInputPort == _D9_INPUT_PORT)
    {
        enumInputPort = GET_DP_MST_RX_PXP_INPUT_PORT();
    }
#endif

    switch(ScalerDpRxGetMacDphySwitch(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

            ScalerDpMacDphyRx0HdcpSramClkGate(bEnable);

            break;
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            ScalerDpMacDphyRx1HdcpSramClkGate(bEnable);

            break;
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            ScalerDpMacDphyRx2HdcpSramClkGate(bEnable);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : DP Mst Mode Config
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxConfigMstOrSstMode(EnumInputPort enumInputPort)
{
#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
    if(enumInputPort == _D9_INPUT_PORT)
    {
        enumInputPort = GET_DP_MST_RX_PXP_INPUT_PORT();
    }
#endif

    switch(ScalerDpRxGetMacDphySwitch(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

            ScalerDpMacDphyRx0ConfigMstOrSstMode();

            break;
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            ScalerDpMacDphyRx1ConfigMstOrSstMode();

            break;
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            ScalerDpMacDphyRx2ConfigMstOrSstMode();

            break;
#endif

#if(_DUAL_DP_SUPPORT == _ON)
        case _DP_MAC_DPHY_DUAL:

#if(_DUAL_DP_MAC_DPHY_USE == _DUAL_DP_MAC_DPHY_RX0RX1)
            ScalerDpMacDphyRx0ConfigMstOrSstMode();
            ScalerDpMacDphyRx1ConfigMstOrSstMode();
#elif(_DUAL_DP_MAC_DPHY_USE == _DUAL_DP_MAC_DPHY_RX1RX2)
            ScalerDpMacDphyRx1ConfigMstOrSstMode();
            ScalerDpMacDphyRx2ConfigMstOrSstMode();
#endif

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Get Mst protocol(MTP or SST format) Status of inputport
// Input Value  : enumInputport
// Output Value : _ENABLE or _DISABLE
//--------------------------------------------------
bit ScalerDpMacDphyRxGetMstProtocolEnable(EnumInputPort enumInputPort)
{
    if(enumInputPort == _NO_INPUT_PORT)
    {
        return _DISABLE;
    }

#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
    {
        return _ENABLE;
    }
    else
#endif
    {
        if(ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x00, 0x01, 0x11, _BIT0) == _BIT0)
        {
            return _ENABLE;
        }
        else
        {
            return _DISABLE;
        }
    }
}

//--------------------------------------------------
// Description  : Recover Data from Power Cut State
// Input Value  : None
// Output Value : None
//-------------------------------------------------
void ScalerDpMacDphyRxPowerDataRecover(EnumInputPort enumInputPort)
{
    switch(ScalerDpRxGetMacDphySwitch(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

            ScalerDpMacDphyRx0PowerDataRecover();

            break;
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            ScalerDpMacDphyRx1PowerDataRecover();

            break;
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            ScalerDpMacDphyRx2PowerDataRecover();

            break;
#endif

        default:

            break;
    }
}

#if(_DP_RX_FEC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : FEC Support
// Input Value  : Enable or Disable
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxFecDecode(EnumInputPort enumInputPort, BYTE ucFECDecode)
{
#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
    if(enumInputPort == _D9_INPUT_PORT)
    {
        enumInputPort = GET_DP_MST_RX_PXP_INPUT_PORT();
    }
#endif

    switch(ScalerDpRxGetMacDphySwitch(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

            ScalerDpMacDphyRx0FecDecode(ucFECDecode);

            break;
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            ScalerDpMacDphyRx1FecDecode(ucFECDecode);

            break;
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            ScalerDpMacDphyRx2FecDecode(ucFECDecode);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Get FEC Decode Status
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE ScalerDpMacDphyRxGetFecDecodeStatus(EnumInputPort enumInputPort)
{
#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
    if(enumInputPort == _D9_INPUT_PORT)
    {
        enumInputPort = GET_DP_MST_RX_PXP_INPUT_PORT();
    }
#endif

    switch(ScalerDpRxGetMacDphySwitch(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

            return GET_DP_MAC_DPHY_RX0_FEC_DECODE_STATUS();
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            return GET_DP_MAC_DPHY_RX1_FEC_DECODE_STATUS();
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            return GET_DP_MAC_DPHY_RX2_FEC_DECODE_STATUS();
#endif

        default:

            return _FALSE;
    }
}

//--------------------------------------------------
// Description  : FEC Decode Check
// Input Value  : Enable or Disable
// Output Value : None
//--------------------------------------------------
bit ScalerDpMacDphyRxFecDecodeCheck(EnumInputPort enumInputPort)
{
#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
    if(enumInputPort == _D9_INPUT_PORT)
    {
        enumInputPort = GET_DP_MST_RX_PXP_INPUT_PORT();
    }
#endif

    switch(ScalerDpRxGetMacDphySwitch(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

            if(ScalerDpMacDphyRx0FecDecodeCheck() == _TRUE)
            {
                return _TRUE;
            }

            break;
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            if(ScalerDpMacDphyRx1FecDecodeCheck() == _TRUE)
            {
                return _TRUE;
            }

            break;
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            if(ScalerDpMacDphyRx2FecDecodeCheck() == _TRUE)
            {
                return _TRUE;
            }

            break;
#endif

        default:

            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : FEC Mac Reset
// Input Value  : EnumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxFecInitial(EnumInputPort enumInputPort)
{
    BYTE ucDpFecSettingMainMacInfo = 0;
    EnumDpAuxRxModeStatus enumBackUpAuxModeMainStatus = ScalerDpAuxRxGetAuxModeStatus(enumInputPort);

#if(_DUAL_DP_SUPPORT == _ON)
    BYTE ucDpFecSettingSubMacInfo = 0;
    EnumDpAuxRxModeStatus enumBackUpAuxModeSubStatus = ScalerDpAuxRxGetAuxModeStatus(enumInputPort);
#endif

#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
    if(enumInputPort == _D9_INPUT_PORT)
    {
        enumInputPort = GET_DP_MST_RX_PXP_INPUT_PORT();
    }
#endif

    switch(ScalerDpRxGetMacDphySwitch(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

            if(enumBackUpAuxModeMainStatus == _DP_RX_AUX_AUTO_MODE)
            {
                ScalerDpAuxRxSetManualMode(enumInputPort);
            }

            ucDpFecSettingMainMacInfo = ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x00, 0x01, 0x20);

            ScalerDpMacDphyRxFecErrorCountSelect(enumInputPort, ((ucDpFecSettingMainMacInfo & (_BIT3 | _BIT2 | _BIT1)) << 3));
            ScalerDpMacDphyRxFecLaneSelect(enumInputPort, ((ucDpFecSettingMainMacInfo & (_BIT5 | _BIT4)) >> 2));

            if(enumBackUpAuxModeMainStatus == _DP_RX_AUX_AUTO_MODE)
            {
                ScalerDpAuxRxSetAutoMode(enumInputPort);
            }

            break;
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            if(enumBackUpAuxModeMainStatus == _DP_RX_AUX_AUTO_MODE)
            {
                ScalerDpAuxRxSetManualMode(enumInputPort);
            }

            ucDpFecSettingMainMacInfo = ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x00, 0x01, 0x20);

            ScalerDpMacDphyRxFecErrorCountSelect(enumInputPort, ((ucDpFecSettingMainMacInfo & (_BIT3 | _BIT2 | _BIT1)) << 3));
            ScalerDpMacDphyRxFecLaneSelect(enumInputPort, ((ucDpFecSettingMainMacInfo & (_BIT5 | _BIT4)) >> 2));

            if(enumBackUpAuxModeMainStatus == _DP_RX_AUX_AUTO_MODE)
            {
                ScalerDpAuxRxSetAutoMode(enumInputPort);
            }

            break;
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            if(enumBackUpAuxModeMainStatus == _DP_RX_AUX_AUTO_MODE)
            {
                ScalerDpAuxRxSetManualMode(enumInputPort);
            }

            ucDpFecSettingMainMacInfo = ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x00, 0x01, 0x20);

            ScalerDpMacDphyRxFecErrorCountSelect(enumInputPort, ((ucDpFecSettingMainMacInfo & (_BIT3 | _BIT2 | _BIT1)) << 3));
            ScalerDpMacDphyRxFecLaneSelect(enumInputPort, ((ucDpFecSettingMainMacInfo & (_BIT5 | _BIT4)) >> 2));

            if(enumBackUpAuxModeMainStatus == _DP_RX_AUX_AUTO_MODE)
            {
                ScalerDpAuxRxSetAutoMode(enumInputPort);
            }

            break;
#endif

#if(_DUAL_DP_SUPPORT == _ON)
        case _DP_MAC_DPHY_DUAL:

#if(_DUAL_DP_MAC_DPHY_USE == _DUAL_DP_MAC_DPHY_RX0RX1)
            if(enumBackUpAuxModeMainStatus == _DP_RX_AUX_AUTO_MODE)
            {
                ScalerDpAuxRxSetManualMode(_D0_INPUT_PORT);
            }
            if(enumBackUpAuxModeSubStatus == _DP_RX_AUX_AUTO_MODE)
            {
                ScalerDpAuxRxSetManualMode(_D1_INPUT_PORT);
            }

            // Mac0 to D0 port, Mac1 to D1 port
            ucDpFecSettingMainMacInfo = ScalerDpAuxRxGetDpcdInfo(_D0_INPUT_PORT, 0x00, 0x01, 0x20);
            ucDpFecSettingSubMacInfo = ScalerDpAuxRxGetDpcdInfo(_D1_INPUT_PORT, 0x00, 0x01, 0x20);

            // Sync FEC Mac and DPCD value
            ScalerDpMacDphyRxFecErrorCountSelect(_D0_INPUT_PORT, ((ucDpFecSettingMainMacInfo & (_BIT3 | _BIT2 | _BIT1)) << 3));
            ScalerDpMacDphyRxFecLaneSelect(_D0_INPUT_PORT, ((ucDpFecSettingMainMacInfo & (_BIT5 | _BIT4)) >> 2));

            ScalerDpMacDphyRxFecErrorCountSelect(_D1_INPUT_PORT, ((ucDpFecSettingSubMacInfo & (_BIT3 | _BIT2 | _BIT1)) << 3));
            ScalerDpMacDphyRxFecLaneSelect(_D1_INPUT_PORT, ((ucDpFecSettingSubMacInfo & (_BIT5 | _BIT4)) >> 2));

            if(enumBackUpAuxModeMainStatus == _DP_RX_AUX_AUTO_MODE)
            {
                ScalerDpAuxRxSetAutoMode(_D0_INPUT_PORT);
            }
            if(enumBackUpAuxModeSubStatus == _DP_RX_AUX_AUTO_MODE)
            {
                ScalerDpAuxRxSetAutoMode(_D1_INPUT_PORT);
            }

#elif(_DUAL_DP_MAC_DPHY_USE == _DUAL_DP_MAC_DPHY_RX1RX2)
            if(enumBackUpAuxModeMainStatus == _DP_RX_AUX_AUTO_MODE)
            {
                ScalerDpAuxRxSetManualMode(_D1_INPUT_PORT);
            }
            if(enumBackUpAuxModeSubStatus == _DP_RX_AUX_AUTO_MODE)
            {
                ScalerDpAuxRxSetManualMode(_D2_INPUT_PORT);
            }

            // Mac1 to D1 port, Mac2 to D2 port
            ucDpFecSettingMainMacInfo = ScalerDpAuxRxGetDpcdInfo(_D1_INPUT_PORT, 0x00, 0x01, 0x20);
            ucDpFecSettingSubMacInfo = ScalerDpAuxRxGetDpcdInfo(_D2_INPUT_PORT, 0x00, 0x01, 0x20);

            // Sync FEC Mac and DPCD value
            ScalerDpMacDphyRxFecErrorCountSelect(_D1_INPUT_PORT, ((ucDpFecSettingMainMacInfo & (_BIT3 | _BIT2 | _BIT1)) << 3));
            ScalerDpMacDphyRxFecLaneSelect(_D1_INPUT_PORT, ((ucDpFecSettingMainMacInfo & (_BIT5 | _BIT4)) >> 2));

            ScalerDpMacDphyRxFecErrorCountSelect(_D2_INPUT_PORT, ((ucDpFecSettingSubMacInfo & (_BIT3 | _BIT2 | _BIT1)) << 3));
            ScalerDpMacDphyRxFecLaneSelect(_D2_INPUT_PORT, ((ucDpFecSettingSubMacInfo & (_BIT5 | _BIT4)) >> 2));

            if(enumBackUpAuxModeMainStatus == _DP_RX_AUX_AUTO_MODE)
            {
                ScalerDpAuxRxSetAutoMode(_D1_INPUT_PORT);
            }
            if(enumBackUpAuxModeSubStatus == _DP_RX_AUX_AUTO_MODE)
            {
                ScalerDpAuxRxSetAutoMode(_D2_INPUT_PORT);
            }
#endif
            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Clear FEC Error Count
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxResetFecErrorCount(EnumInputPort enumInputPort)
{
    switch(ScalerDpRxGetMacDphySwitch(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:
            ScalerSetBit(PB_D3_FEC_ERROR_DETECT, ~_BIT1, _BIT1);
            ScalerSetBit(PB_D3_FEC_ERROR_DETECT, ~_BIT1, 0x00);
#if(_DP_MAC_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
            ScalerSetBit(PC_82_FEC_ERROR_DETECT, ~_BIT1, _BIT1);
            ScalerSetBit(PC_82_FEC_ERROR_DETECT, ~_BIT1, 0x00);
#endif
            break;
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            ScalerSetBit(PB0_D3_FEC_ERROR_DETECT, ~_BIT1, _BIT1);
            ScalerSetBit(PB0_D3_FEC_ERROR_DETECT, ~_BIT1, 0x00);
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
            ScalerSetBit(P1F_82_FEC_ERROR_DETECT, ~_BIT1, _BIT1);
            ScalerSetBit(P1F_82_FEC_ERROR_DETECT, ~_BIT1, 0x00);
#endif
            break;
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            ScalerSetBit(PC5_D3_FEC_ERROR_DETECT, ~_BIT1, _BIT1);
            ScalerSetBit(PC5_D3_FEC_ERROR_DETECT, ~_BIT1, 0x00);
#if(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
            ScalerSetBit(PD2_82_FEC_ERROR_DETECT, ~_BIT1, _BIT1);
            ScalerSetBit(PD2_82_FEC_ERROR_DETECT, ~_BIT1, 0x00);
#endif
            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : FEC Error Count Select
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxFecErrorCountSelect(EnumInputPort enumInputPort, BYTE ucFECSelect)
{
    switch(ScalerDpRxGetMacDphySwitch(enumInputPort))
#if(_HW_DP_RX_FEC_ERROR_COUNT_SEL_DB_SUPPORT == _ON)
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:
            ScalerSetBit(PB_D3_FEC_ERROR_DETECT, ~(_BIT6 | _BIT5 | _BIT4), ucFECSelect);
            // Enable err_cnt_sel Double Buffer
            ScalerSetBit(PB_D7_FEC_ERROR_CNT_H, ~_BIT7, _BIT7);
#if(_DP_MAC_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
            ScalerSetBit(PC_82_FEC_ERROR_DETECT, ~(_BIT6 | _BIT5 | _BIT4), ucFECSelect);
            ScalerSetBit(PC_8B_FEC_MERGE_PARITY_ERROR_CNT_CTRL, ~(_BIT6 | _BIT0), _BIT6);
            // Enable err_cnt_sel Double Buffer
            ScalerSetBit(PC_86_FEC_ERROR_CNT_H, ~_BIT7, _BIT7);
#endif
            break;
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            ScalerSetBit(PB0_D3_FEC_ERROR_DETECT, ~(_BIT6 | _BIT5 | _BIT4), ucFECSelect);
            // Enable err_cnt_sel Double Buffer
            ScalerSetBit(PB0_D7_FEC_ERROR_CNT_H, ~_BIT7, _BIT7);
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
            ScalerSetBit(P1F_82_FEC_ERROR_DETECT, ~(_BIT6 | _BIT5 | _BIT4), ucFECSelect);
            ScalerSetBit(P1F_8B_FEC_MERGE_PARITY_ERROR_CNT_CTRL, ~(_BIT6 | _BIT0), _BIT6);
            // Enable err_cnt_sel Double Buffer
            ScalerSetBit(P1F_86_FEC_ERROR_CNT_H, ~_BIT7, _BIT7);
#endif
            break;
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            ScalerSetBit(PC5_D3_FEC_ERROR_DETECT, ~(_BIT6 | _BIT5 | _BIT4), ucFECSelect);
            // Enable err_cnt_sel Double Buffer
            ScalerSetBit(PC5_D7_FEC_ERROR_CNT_H, ~_BIT7, _BIT7);
#if(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
            ScalerSetBit(PD2_82_FEC_ERROR_DETECT, ~(_BIT6 | _BIT5 | _BIT4), ucFECSelect);
            ScalerSetBit(PD2_8B_FEC_MERGE_PARITY_ERROR_CNT_CTRL, ~(_BIT6 | _BIT0), _BIT6);
            // Enable err_cnt_sel Double Buffer
            ScalerSetBit(PD2_86_FEC_ERROR_CNT_H, ~_BIT7, _BIT7);
#endif
            break;
#endif

        default:

            break;
    }
#else
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:
            // Set err_cnt_sel = 3'b111 to avoid transient 0s
            ScalerSetBit(PB_D3_FEC_ERROR_DETECT, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5 | _BIT4));
            ScalerSetBit(PB_D3_FEC_ERROR_DETECT, ~(_BIT6 | _BIT5 | _BIT4), ucFECSelect);
#if(_DP_MAC_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
            // Set err_cnt_sel = 3'b111 to avoid transient 0s
            ScalerSetBit(PC_82_FEC_ERROR_DETECT, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5 | _BIT4));
            ScalerSetBit(PC_82_FEC_ERROR_DETECT, ~(_BIT6 | _BIT5 | _BIT4), ucFECSelect);
            ScalerSetBit(PC_8B_FEC_MERGE_PARITY_ERROR_CNT_CTRL, ~(_BIT6 | _BIT0), _BIT6);
#endif
            break;
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:
            // Set err_cnt_sel = 3'b111 to avoid transient 0s
            ScalerSetBit(PB0_D3_FEC_ERROR_DETECT, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5 | _BIT4));
            ScalerSetBit(PB0_D3_FEC_ERROR_DETECT, ~(_BIT6 | _BIT5 | _BIT4), ucFECSelect);
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
            // Set err_cnt_sel = 3'b111 to avoid transient 0s
            ScalerSetBit(P1F_82_FEC_ERROR_DETECT, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5 | _BIT4));
            ScalerSetBit(P1F_82_FEC_ERROR_DETECT, ~(_BIT6 | _BIT5 | _BIT4), ucFECSelect);
            ScalerSetBit(P1F_8B_FEC_MERGE_PARITY_ERROR_CNT_CTRL, ~(_BIT6 | _BIT0), _BIT6);
#endif
            break;
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:
            // Set err_cnt_sel = 3'b111 to avoid transient 0s
            ScalerSetBit(PC5_D3_FEC_ERROR_DETECT, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5 | _BIT4));
            ScalerSetBit(PC5_D3_FEC_ERROR_DETECT, ~(_BIT6 | _BIT5 | _BIT4), ucFECSelect);
#if(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
            // Set err_cnt_sel = 3'b111 to avoid transient 0s
            ScalerSetBit(PD2_82_FEC_ERROR_DETECT, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5 | _BIT4));
            ScalerSetBit(PD2_82_FEC_ERROR_DETECT, ~(_BIT6 | _BIT5 | _BIT4), ucFECSelect);
            ScalerSetBit(PD2_8B_FEC_MERGE_PARITY_ERROR_CNT_CTRL, ~(_BIT6 | _BIT0), _BIT6);
#endif
            break;
#endif

        default:

            break;
    }
#endif
}

//--------------------------------------------------
// Description  : FEC Error Lane Select
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxFecLaneSelect(EnumInputPort enumInputPort, BYTE ucFECLane)
{
#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
    if(enumInputPort == _D9_INPUT_PORT)
    {
        enumInputPort = GET_DP_MST_RX_PXP_INPUT_PORT();
    }
#endif

    switch(ScalerDpRxGetMacDphySwitch(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

            ScalerSetBit(PB_D3_FEC_ERROR_DETECT, ~(_BIT3 | _BIT2), ucFECLane);
#if(_DP_MAC_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
            ScalerSetBit(PC_82_FEC_ERROR_DETECT, ~(_BIT3 | _BIT2), ucFECLane);
#endif
            break;
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            ScalerSetBit(PB0_D3_FEC_ERROR_DETECT, ~(_BIT3 | _BIT2), ucFECLane);
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
            ScalerSetBit(P1F_82_FEC_ERROR_DETECT, ~(_BIT3 | _BIT2), ucFECLane);
#endif
            break;
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            ScalerSetBit(PC5_D3_FEC_ERROR_DETECT, ~(_BIT3 | _BIT2), ucFECLane);
#if(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
            ScalerSetBit(PD2_82_FEC_ERROR_DETECT, ~(_BIT3 | _BIT2), ucFECLane);
#endif
            break;
#endif

        default:

            break;
    }
}
#endif

#if(_DP_MST_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Backup MST Info Clear
// Input Value  : Input port
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxClearMstInfoBackup(EnumInputPort enumInputPort)
{
#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
    if(enumInputPort == _D9_INPUT_PORT)
    {
        enumInputPort = GET_DP_MST_RX_PXP_INPUT_PORT();
    }
#endif

    switch(ScalerDpRxGetMacDphySwitch(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

            g_stDpMacDphyRx0MiscInfo.b1DpMstEnableBackup = _FALSE;

            break;
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            g_stDpMacDphyRx1MiscInfo.b1DpMstEnableBackup = _FALSE;

            break;
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            g_stDpMacDphyRx2MiscInfo.b1DpMstEnableBackup = _FALSE;

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Backup MST Info Enable
// Input Value  : Input port
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerDpMacDphyRxGetMstInfoBackup(EnumInputPort enumInputPort)
{
#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
    if(enumInputPort == _D9_INPUT_PORT)
    {
        enumInputPort = GET_DP_MST_RX_PXP_INPUT_PORT();
    }
#endif

    switch(ScalerDpRxGetMacDphySwitch(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

            return g_stDpMacDphyRx0MiscInfo.b1DpMstEnableBackup;
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            return g_stDpMacDphyRx1MiscInfo.b1DpMstEnableBackup;
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            return g_stDpMacDphyRx2MiscInfo.b1DpMstEnableBackup;
#endif

        default:

            break;
    }

    return _FALSE;
}

#if(_DP_TX_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get DP Mst Rx Stream Status
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpMacDphyRxHdcpStreamStatus(EnumDpHdcpUpstreamPort enumDpHdcpUpstreamPort, BYTE ucDaisyStreamCnt)
{
    EnumInputPort enumInputPort = _NO_INPUT_PORT;

#if(_D0_DP_SUPPORT == _ON)
    if(enumDpHdcpUpstreamPort == _HDCP_D0_PORT)
    {
        enumInputPort = _D0_INPUT_PORT;
    }
#endif

#if(_D1_DP_SUPPORT == _ON)
    if(enumDpHdcpUpstreamPort == _HDCP_D1_PORT)
    {
        enumInputPort = _D1_INPUT_PORT;
    }
#endif

#if(_D2_DP_SUPPORT == _ON)
    if(enumDpHdcpUpstreamPort == _HDCP_D2_PORT)
    {
        enumInputPort = _D2_INPUT_PORT;
    }
#endif

    return ((bit)GET_DP_MAC_DPHY_RX_REG_ST_STATUS(enumInputPort, ucDaisyStreamCnt));
}

//--------------------------------------------------
// Description  : DP Rx Hdcp TimeSlot Encryption Status
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpMacDphyRxHdcpTimeSlotEncStatus(EnumDpHdcpUpstreamPort enumDpHdcpUpstreamPort, BYTE ucTimeSlot)
{
    EnumInputPort enumInputPort = _NO_INPUT_PORT;

#if(_D0_DP_SUPPORT == _ON)
    if(enumDpHdcpUpstreamPort == _HDCP_D0_PORT)
    {
        enumInputPort = _D0_INPUT_PORT;
    }
#endif

#if(_D1_DP_SUPPORT == _ON)
    if(enumDpHdcpUpstreamPort == _HDCP_D1_PORT)
    {
        enumInputPort = _D1_INPUT_PORT;
    }
#endif

#if(_D2_DP_SUPPORT == _ON)
    if(enumDpHdcpUpstreamPort == _HDCP_D2_PORT)
    {
        enumInputPort = _D2_INPUT_PORT;
    }
#endif

    switch(ScalerDpRxGetMacDphySwitch(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:
#if(_DP_MAC_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
            {
                return ((bit)GET_DP_MAC_DPHY_RX0_TIMESLOT_HDCP_ENC_VALUE_128B132B(ucTimeSlot) != 0);
            }
            else
#endif
            {
                return ((bit)GET_DP_MAC_DPHY_RX0_TIMESLOT_HDCP_ENC_VALUE_8B10B(ucTimeSlot) != 0);
            }
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
            {
                return ((bit)GET_DP_MAC_DPHY_RX1_TIMESLOT_HDCP_ENC_VALUE_128B132B(ucTimeSlot) != 0);
            }
            else
#endif
            {
                return ((bit)GET_DP_MAC_DPHY_RX1_TIMESLOT_HDCP_ENC_VALUE_8B10B(ucTimeSlot) != 0);
            }
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:
#if(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
            {
                return ((bit)GET_DP_MAC_DPHY_RX2_TIMESLOT_HDCP_ENC_VALUE_128B132B(ucTimeSlot) != 0);
            }
            else
#endif
            {
                return ((bit)GET_DP_MAC_DPHY_RX2_TIMESLOT_HDCP_ENC_VALUE_8B10B(ucTimeSlot) != 0);
            }
#endif
        default:

            return _FALSE;
    }
}

//--------------------------------------------------
// Description  : DP Rx Hdcp TimeSlot Encryption Value
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE ScalerDpMacDphyRxHdcpTimeSlotEncValue(EnumInputPort enumInputPort, BYTE ucTimeSlot)
{
#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
    if(enumInputPort == _D9_INPUT_PORT)
    {
        enumInputPort = GET_DP_MST_RX_PXP_INPUT_PORT();
    }
#endif

    switch(ScalerDpRxGetMacDphySwitch(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:
#if(_DP_MAC_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
            {
                return GET_DP_MAC_DPHY_RX0_TIMESLOT_HDCP_ENC_VALUE_128B132B(ucTimeSlot);
            }
            else
#endif
            {
                return GET_DP_MAC_DPHY_RX0_TIMESLOT_HDCP_ENC_VALUE_8B10B(ucTimeSlot);
            }
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
            {
                return GET_DP_MAC_DPHY_RX1_TIMESLOT_HDCP_ENC_VALUE_128B132B(ucTimeSlot);
            }
            else
#endif
            {
                return GET_DP_MAC_DPHY_RX1_TIMESLOT_HDCP_ENC_VALUE_8B10B(ucTimeSlot);
            }
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:
#if(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
            {
                return GET_DP_MAC_DPHY_RX2_TIMESLOT_HDCP_ENC_VALUE_128B132B(ucTimeSlot);
            }
            else
#endif
            {
                return GET_DP_MAC_DPHY_RX2_TIMESLOT_HDCP_ENC_VALUE_8B10B(ucTimeSlot);
            }
#endif
        default:

            return _FALSE;
    }
}

//--------------------------------------------------
// Description  : DP Rx Hdcp TimeSlot Encryption Value
// Input Value  : None
// Output Value : None
//--------------------------------------------------
WORD ScalerDpMacDphyRxStreamStartAddress(EnumDpHdcpUpstreamPort enumDpHdcpUpstreamPort, BYTE ucDaisyStreamCnt)
{
    EnumInputPort enumInputPort = _NO_INPUT_PORT;

#if(_D0_DP_SUPPORT == _ON)
    if(enumDpHdcpUpstreamPort == _HDCP_D0_PORT)
    {
        enumInputPort = _D0_INPUT_PORT;
    }
#endif

#if(_D1_DP_SUPPORT == _ON)
    if(enumDpHdcpUpstreamPort == _HDCP_D1_PORT)
    {
        enumInputPort = _D1_INPUT_PORT;
    }
#endif

#if(_D2_DP_SUPPORT == _ON)
    if(enumDpHdcpUpstreamPort == _HDCP_D2_PORT)
    {
        enumInputPort = _D2_INPUT_PORT;
    }
#endif

    switch(ScalerDpRxGetMacDphySwitch(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:
#if(_DP_MAC_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
            {
                return GET_DP_MAC_DPHY_RX0_STX_START_ADDRESS_128B132B(ucDaisyStreamCnt);
            }
            else
#endif
            {
                return GET_DP_MAC_DPHY_RX0_STX_START_ADDRESS_8B10B(ucDaisyStreamCnt);
            }
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
            {
                return GET_DP_MAC_DPHY_RX1_STX_START_ADDRESS_128B132B(ucDaisyStreamCnt);
            }
            else
#endif
            {
                return GET_DP_MAC_DPHY_RX1_STX_START_ADDRESS_8B10B(ucDaisyStreamCnt);
            }
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:
#if(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
            {
                return GET_DP_MAC_DPHY_RX2_STX_START_ADDRESS_128B132B(ucDaisyStreamCnt);
            }
            else
#endif
            {
                return GET_DP_MAC_DPHY_RX2_STX_START_ADDRESS_8B10B(ucDaisyStreamCnt);
            }
#endif
        default:

            return _FALSE;
    }
}
#endif
#endif

//--------------------------------------------------
// Description : DP Signal Detection Measure
// Input Value  : DP Lane Select, Measure target, Measure Period
// Output Value : Measure Counter
//--------------------------------------------------
DWORD ScalerDpMacDphyRxSignalDetectMeasureCount(EnumInputPort enumInputPort, BYTE ucDpLaneSel, EnumDpMeasureTarget enumDpMeasureTarget, EnumDpMeasurePeriod enumDpMeasurePeriod)
{
#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
    if(enumInputPort == _D9_INPUT_PORT)
    {
        enumInputPort = GET_DP_MST_RX_PXP_INPUT_PORT();
    }
#endif

    switch(ScalerDpRxGetMacDphySwitch(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

            return ScalerDpMacDphyRx0SignalDetectMeasureCount(ucDpLaneSel, enumDpMeasureTarget, enumDpMeasurePeriod);
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            return ScalerDpMacDphyRx1SignalDetectMeasureCount(ucDpLaneSel, enumDpMeasureTarget, enumDpMeasurePeriod);
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            return ScalerDpMacDphyRx2SignalDetectMeasureCount(ucDpLaneSel, enumDpMeasureTarget, enumDpMeasurePeriod);
#endif

        default:

            return 0x00000000;
    }
}

//--------------------------------------------------
// Description : Check Valid Signal
// Input Value  : DP Link Rate and Lane Count
// Output Value : True --> valid, False --> invalid
//--------------------------------------------------
bit ScalerDpMacDphyRxSignalCheck(EnumInputPort enumInputPort)
{
    bit bReturn = _FALSE;

#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
    if(enumInputPort == _D9_INPUT_PORT)
    {
        enumInputPort = GET_DP_MST_RX_PXP_INPUT_PORT();
    }
#endif

#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
    ScalerDpMacDphyRxAuxlessAlpmClrOccurred(enumInputPort);
#endif

    switch(ScalerDpRxGetMacDphySwitch(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

            bReturn = ScalerDpMacDphyRx0SignalCheck(ScalerDpAuxRxGetDpcdLinkRate(enumInputPort), (ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x00, 0x01, 0x01) & 0x1F));

            break;
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            bReturn = ScalerDpMacDphyRx1SignalCheck(ScalerDpAuxRxGetDpcdLinkRate(enumInputPort), (ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x00, 0x01, 0x01) & 0x1F));

            break;
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            bReturn = ScalerDpMacDphyRx2SignalCheck(ScalerDpAuxRxGetDpcdLinkRate(enumInputPort), (ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x00, 0x01, 0x01) & 0x1F));

            break;
#endif

        default:
            break;
    }

#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
    if(ScalerDpMacDphyRxAuxlessAlpmGetOccurred(enumInputPort) == _TRUE)
    {
        return _TRUE;
    }
    else
#endif
    {
        return bReturn;
    }
}

//--------------------------------------------------
// Description  : Check Valid Lane CDR
// Input Value  : None
// Output Value : True --> CDR Lock
//--------------------------------------------------
bit ScalerDpMacDphyRxCDRCheck(EnumInputPort enumInputPort)
{
    bit bReturn = _FALSE;

#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
    if(enumInputPort == _D9_INPUT_PORT)
    {
        enumInputPort = GET_DP_MST_RX_PXP_INPUT_PORT();
    }
#endif

#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
    ScalerDpMacDphyRxAuxlessAlpmClrOccurred(enumInputPort);
#endif

    switch(ScalerDpRxGetMacDphySwitch(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

            bReturn = ScalerDpMacDphyRx0CDRCheck(ScalerDpAuxRxGetDpcdLinkRate(enumInputPort), (ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x00, 0x01, 0x01) & 0x1F));

            break;
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            bReturn = ScalerDpMacDphyRx1CDRCheck(ScalerDpAuxRxGetDpcdLinkRate(enumInputPort), (ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x00, 0x01, 0x01) & 0x1F));

            break;
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            bReturn = ScalerDpMacDphyRx2CDRCheck(ScalerDpAuxRxGetDpcdLinkRate(enumInputPort), (ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x00, 0x01, 0x01) & 0x1F));

            break;
#endif

        default:
            break;
    }

#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
    if(ScalerDpMacDphyRxAuxlessAlpmGetOccurred(enumInputPort) == _TRUE)
    {
        return _TRUE;
    }
    else
#endif
    {
        return bReturn;
    }
}

//--------------------------------------------------
// Description  : Check Valid Lane Alignment
// Input Value  : None
// Output Value : True --> Align
//--------------------------------------------------
bit ScalerDpMacDphyRxAlignCheck(EnumInputPort enumInputPort)
{
    bit bReturn = _FALSE;

#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
    if(enumInputPort == _D9_INPUT_PORT)
    {
        enumInputPort = GET_DP_MST_RX_PXP_INPUT_PORT();
    }
#endif

#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
    ScalerDpMacDphyRxAuxlessAlpmClrOccurred(enumInputPort);
#endif

    switch(ScalerDpRxGetMacDphySwitch(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

            bReturn = ScalerDpMacDphyRx0AlignCheck();

            break;
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            bReturn = ScalerDpMacDphyRx1AlignCheck();

            break;
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            bReturn = ScalerDpMacDphyRx2AlignCheck();

            break;
#endif

        default:
            break;
    }

#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
    if(ScalerDpMacDphyRxAuxlessAlpmGetOccurred(enumInputPort) == _TRUE)
    {
        return _TRUE;
    }
    else
#endif
    {
        return bReturn;
    }
}

//--------------------------------------------------
// Description : check DP 8b/10b Decode Error
// Input Value  : None
// Output Value : True --> ok, False --> 8b/10b Decode Error
//--------------------------------------------------
bit ScalerDpMacDphyRxDecodeCheck(EnumInputPort enumInputPort)
{
    bit bReturn = _FALSE;

#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
    if(enumInputPort == _D9_INPUT_PORT)
    {
        enumInputPort = GET_DP_MST_RX_PXP_INPUT_PORT();
    }
#endif

#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
    ScalerDpMacDphyRxAuxlessAlpmClrOccurred(enumInputPort);
#endif

    switch(ScalerDpRxGetMacDphySwitch(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

            bReturn = ScalerDpMacDphyRx0DecodeCheck();

            break;
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            bReturn = ScalerDpMacDphyRx1DecodeCheck();

            break;
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            bReturn = ScalerDpMacDphyRx2DecodeCheck();

            break;
#endif

        default:
            break;
    }

#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
    if(ScalerDpMacDphyRxAuxlessAlpmGetOccurred(enumInputPort) == _TRUE)
    {
        return _TRUE;
    }
    else
#endif
    {
        return bReturn;
    }
}

//--------------------------------------------------
// Description  : DP Port Cable Status
// Input Value  : enumInputPort
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
void ScalerDpMacDphyRxLinkStatusIRQAssertCheck(EnumInputPort enumInputPort)
{
    EnumDpAuxRxModeStatus enumBackUpAuxModeStatus = ScalerDpAuxRxGetAuxModeStatus(enumInputPort);

    // Double Check Link Status
    if((ScalerDpMacDphyRxCDRCheck(enumInputPort) == _FALSE) ||
       (ScalerDpMacDphyRxAlignCheck(enumInputPort) == _FALSE) ||
       (ScalerDpMacDphyRxDecodeCheck(enumInputPort) == _FALSE) ||
       ((ScalerDpPhyRxDFECheck(enumInputPort) == _FALSE) && (ScalerDpMacDphyRxSignalCheck(enumInputPort) == _FALSE)))
    {
        // Check if Auto mode
        if(enumBackUpAuxModeStatus == _DP_RX_AUX_AUTO_MODE)
        {
            ScalerDpAuxRxSetManualMode(enumInputPort);
        }

        // Active WD Timer Event for HPD_IRQ in 100ms
        if(ScalerDpAuxRxGetLTStatus(enumInputPort) == _DP_NORMAL_LINK_TRAINING_PASS)
        {
            ScalerDpAuxRxActiveWDLinkStatusIRQ(enumInputPort);
        }

        if(enumBackUpAuxModeStatus == _DP_RX_AUX_AUTO_MODE)
        {
            ScalerDpAuxRxSetAutoMode(enumInputPort);
        }
    }
}

#if(_DP_HDCP2_RX_SUPPORT == _ON)
//--------------------------------------------------
// Description  : HDCP 2.2 Reset Proc for MAC RX
// Input Value  : PORT
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxHdcp2ResetProc(EnumInputPort enumInputPort)
{
#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
    if(enumInputPort == _D9_INPUT_PORT)
    {
        enumInputPort = GET_DP_MST_RX_PXP_INPUT_PORT();
    }
#endif

    switch(ScalerDpRxGetMacDphySwitch(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

            ScalerDpMacDphyRx0Hdcp2ResetProc();

            break;
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            ScalerDpMacDphyRx1Hdcp2ResetProc();

            break;
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            ScalerDpMacDphyRx2Hdcp2ResetProc();

            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : HDCP 2.2 Clear Restored Cipher Data
// Input Value  : Input Port
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxClrHdcp2CipherBackupInfo(EnumInputPort enumInputPort)
{
#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
    if(enumInputPort == _D9_INPUT_PORT)
    {
        enumInputPort = GET_DP_MST_RX_PXP_INPUT_PORT();
    }
#endif

    switch(ScalerDpRxGetMacDphySwitch(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

            ScalerDpMacDphyRx0ClrHdcp2CipherBackupInfo();

            break;
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            ScalerDpMacDphyRx1ClrHdcp2CipherBackupInfo();

            break;
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            ScalerDpMacDphyRx2ClrHdcp2CipherBackupInfo();

            break;
#endif
        default:

            break;
    }
}

#if(_DP_TX_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Check Dp Rx HDCP Link Veriffication Pattern (0x531F) for MST Mode
// Input Value  : PORT
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpMacDphyRxHdcpDetectLvp(EnumInputPort enumInputPort)
{
#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
    if(enumInputPort == _D9_INPUT_PORT)
    {
        enumInputPort = GET_DP_MST_RX_PXP_INPUT_PORT();
    }
#endif

    switch(ScalerDpRxGetMacDphySwitch(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

            return ScalerDpMacDphyRx0HdcpDetectLvp();
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            return ScalerDpMacDphyRx1HdcpDetectLvp();
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            return ScalerDpMacDphyRx2HdcpDetectLvp();
#endif
        default:

            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Check Dp Rx HDCP Link Veriffication Pattern (0x531F) for MST Mode
// Input Value  : PORT
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
EnumDpHdcp2AESType ScalerDpMacDphyRxHdcp2GetStxType(EnumInputPort enumInputPort, BYTE ucStreamId)
{
#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
    if(enumInputPort == _D9_INPUT_PORT)
    {
        enumInputPort = GET_DP_MST_RX_PXP_INPUT_PORT();
    }
#endif

    switch(ScalerDpRxGetMacDphySwitch(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

            return ScalerDpMacDphyRx0Hdcp2GetStxType(ucStreamId);
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            return ScalerDpMacDphyRx1Hdcp2GetStxType(ucStreamId);
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            return ScalerDpMacDphyRx2Hdcp2GetStxType(ucStreamId);
#endif
        default:

            break;
    }

    return _HDCP2_TYPE_0;
}

//--------------------------------------------------
// Description  : Set Dp Rx HDCP2 AES Type
// Input Value  : PORT
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
EnumDpHdcp2AESType ScalerDpMacDphyRxHdcp2GetAESCipherType(EnumDpHdcp2AESCipherSet enumDpHdcp2AESCipherSet)
{
    switch(enumDpHdcp2AESCipherSet)
    {
        case _HDCP2_CIPHER_AES0:

            return _HDCP2_TYPE_0;

        case _HDCP2_CIPHER_AES1:

            return _HDCP2_TYPE_1;

        case _HDCP2_CIPHER_AES2:

            return _HDCP2_TYPE_2;

        case _HDCP2_CIPHER_NONE:
        default:

            break;
    }

    return _HDCP2_TYPE_0;
}
#endif
#endif


#if(_DP_HDCP14_RX_REPEATER_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Check DP Hdcp ReAuth Process
// Input Value  : PORT
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpMacDphyRxHdcp14Auth1Check(EnumInputPort enumInputPort)
{
#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
    if(enumInputPort == _D9_INPUT_PORT)
    {
        enumInputPort = GET_DP_MST_RX_PXP_INPUT_PORT();
    }
#endif

    switch(ScalerDpRxGetMacDphySwitch(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

            return ScalerDpMacDphyRx0Hdcp14Auth1Check();
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            return ScalerDpMacDphyRx1Hdcp14Auth1Check();
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            return ScalerDpMacDphyRx2Hdcp14Auth1Check();
#endif
        default:

            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Load KSV FIFO to SHA-1 Input
// Input Value  : PORT
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxHdcp14WriteShaInput(EnumInputPort enumInputPort)
{
#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
    if(enumInputPort == _D9_INPUT_PORT)
    {
        enumInputPort = GET_DP_MST_RX_PXP_INPUT_PORT();
    }
#endif

    switch(ScalerDpRxGetMacDphySwitch(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

            ScalerDpMacDphyRx0Hdcp14WriteShaInput();

            break;
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            ScalerDpMacDphyRx1Hdcp14WriteShaInput();

            break;
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            ScalerDpMacDphyRx2Hdcp14WriteShaInput();

            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Dp Rx HDCP - Load SHA Result to DPCD table
// Input Value  : PORT
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxHdcp14LoadShaToDpcd(EnumInputPort enumInputPort)
{
#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
    if(enumInputPort == _D9_INPUT_PORT)
    {
        enumInputPort = GET_DP_MST_RX_PXP_INPUT_PORT();
    }
#endif

    switch(ScalerDpRxGetMacDphySwitch(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

            ScalerDpMacDphyRx0Hdcp14LoadShaToDpcd();

            break;
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            ScalerDpMacDphyRx1Hdcp14LoadShaToDpcd();

            break;
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            ScalerDpMacDphyRx2Hdcp14LoadShaToDpcd();

            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Fake HDCP Authentication
// Input Value  : PORT
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxHdcp14FakeAuthenProc(EnumInputPort enumInputPort)
{
#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
    if(enumInputPort == _D9_INPUT_PORT)
    {
        enumInputPort = GET_DP_MST_RX_PXP_INPUT_PORT();
    }
#endif

    switch(ScalerDpRxGetMacDphySwitch(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

            ScalerDpMacDphyRx0Hdcp14FakeAuthenProc();

            break;
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            ScalerDpMacDphyRx1Hdcp14FakeAuthenProc();

            break;
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            ScalerDpMacDphyRx2Hdcp14FakeAuthenProc();

            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Check Dp Rx HDCP Link Veriffication Pattern (0x531F) for MST Mode
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpMacDphyRxHdcpCheckLvp(EnumInputPort enumInputPort)
{
#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
    if(enumInputPort == _D9_INPUT_PORT)
    {
        enumInputPort = GET_DP_MST_RX_PXP_INPUT_PORT();
    }
#endif

    switch(ScalerDpRxGetMacDphySwitch(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

            return ScalerDpMacDphyRx0HdcpCheckLvp();
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            return ScalerDpMacDphyRx1HdcpCheckLvp();
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            return ScalerDpMacDphyRx2HdcpCheckLvp();
#endif
        default:

            return _FALSE;
    }
}

//--------------------------------------------------
// Description  : Dp Rx HDCP - SHA circuit Run
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxHDCPAuthShaRun(EnumInputPort enumInputPort, bit bIsFirst)
{
#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
    if(enumInputPort == _D9_INPUT_PORT)
    {
        enumInputPort = GET_DP_MST_RX_PXP_INPUT_PORT();
    }
#endif

    switch(ScalerDpRxGetMacDphySwitch(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

            ScalerDpMacDphyRx0HDCPAuthShaRun(bIsFirst);

            break;
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            ScalerDpMacDphyRx1HDCPAuthShaRun(bIsFirst);

            break;
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            ScalerDpMacDphyRx2HDCPAuthShaRun(bIsFirst);

            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Dp Rx HDCP - Get M0
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE ScalerDpMacDphyRxHdcp14GetM0(EnumInputPort enumInputPort, BYTE ucIndex)
{
#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
    if(enumInputPort == _D9_INPUT_PORT)
    {
        enumInputPort = GET_DP_MST_RX_PXP_INPUT_PORT();
    }
#endif

    switch(ScalerDpRxGetMacDphySwitch(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

            switch(ucIndex)
            {
                case 0:
                    return GET_DP_MAC_DPHY_RX0_HDCP14_M0_0();
                case 1:
                    return GET_DP_MAC_DPHY_RX0_HDCP14_M0_1();
                case 2:
                    return GET_DP_MAC_DPHY_RX0_HDCP14_M0_2();
                case 3:
                    return GET_DP_MAC_DPHY_RX0_HDCP14_M0_3();
                case 4:
                    return GET_DP_MAC_DPHY_RX0_HDCP14_M0_4();
                case 5:
                    return GET_DP_MAC_DPHY_RX0_HDCP14_M0_5();
                case 6:
                    return GET_DP_MAC_DPHY_RX0_HDCP14_M0_6();
                case 7:
                    return GET_DP_MAC_DPHY_RX0_HDCP14_M0_7();
                default:
                    break;
            }

            break;
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            switch(ucIndex)
            {
                case 0:
                    return GET_DP_MAC_DPHY_RX1_HDCP14_M0_0();
                case 1:
                    return GET_DP_MAC_DPHY_RX1_HDCP14_M0_1();
                case 2:
                    return GET_DP_MAC_DPHY_RX1_HDCP14_M0_2();
                case 3:
                    return GET_DP_MAC_DPHY_RX1_HDCP14_M0_3();
                case 4:
                    return GET_DP_MAC_DPHY_RX1_HDCP14_M0_4();
                case 5:
                    return GET_DP_MAC_DPHY_RX1_HDCP14_M0_5();
                case 6:
                    return GET_DP_MAC_DPHY_RX1_HDCP14_M0_6();
                case 7:
                    return GET_DP_MAC_DPHY_RX1_HDCP14_M0_7();
                default:
                    break;
            }

            break;
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            switch(ucIndex)
            {
                case 0:
                    return GET_DP_MAC_DPHY_RX2_HDCP14_M0_0();
                case 1:
                    return GET_DP_MAC_DPHY_RX2_HDCP14_M0_1();
                case 2:
                    return GET_DP_MAC_DPHY_RX2_HDCP14_M0_2();
                case 3:
                    return GET_DP_MAC_DPHY_RX2_HDCP14_M0_3();
                case 4:
                    return GET_DP_MAC_DPHY_RX2_HDCP14_M0_4();
                case 5:
                    return GET_DP_MAC_DPHY_RX2_HDCP14_M0_5();
                case 6:
                    return GET_DP_MAC_DPHY_RX2_HDCP14_M0_6();
                case 7:
                    return GET_DP_MAC_DPHY_RX2_HDCP14_M0_7();
                default:
                    break;
            }

            break;

#endif
        default:

            break;
    }

    return 0;
}
#endif

#if((_DP_MST_SUPPORT == _ON) || (_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON))
//--------------------------------------------------
// Description  : DP Mst Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxMstReset(EnumInputPort enumInputPort)
{
#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
    if(enumInputPort == _D9_INPUT_PORT)
    {
        enumInputPort = GET_DP_MST_RX_PXP_INPUT_PORT();
    }
#endif

    switch(ScalerDpRxGetMacDphySwitch(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:
#if((_DP_MST_SUPPORT == _ON) || (_DP_MAC_RX0_128B132B_CODING_TYPE_SUPPORT == _ON))
            ScalerDpMacDphyRx0MstReset();
#endif
            break;
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:
#if((_DP_MST_SUPPORT == _ON) || (_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON))
            ScalerDpMacDphyRx1MstReset();
#endif
            break;
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:
#if((_DP_MST_SUPPORT == _ON) || (_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON))
            ScalerDpMacDphyRx2MstReset();
#endif
            break;
#endif
        default:

            break;
    }
}
//--------------------------------------------------
// Description  : Calculate Current PBN of Time Slot
// Input Value  : enumDpLaneCount, enumDpLinkRate, ucAvailableTimeSlot
// Output Value : PBN
//--------------------------------------------------
WORD ScalerDpMacDphyRxGetPBN(EnumDpLinkRate enumDpLinkRate, EnumDpLaneCount enumDpLaneCount, BYTE ucAvailableTimeSlot)
{
    if(ucAvailableTimeSlot == 0)
    {
        return 0;
    }

    switch(enumDpLinkRate)
    {
        case _DP_LOW_SPEED_162MHZ:
        case _DP_HIGH_SPEED_270MHZ:
        case _DP_HIGH_SPEED2_540MHZ:
        case _DP_HIGH_SPEED3_810MHZ:

            return (WORD) ((GET_DP_MAC_DPHY_RX_PBN_PER_TIME_SLOT(enumDpLinkRate, enumDpLaneCount)) * ucAvailableTimeSlot);

#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)

        case _DP_ULTRA_SPEED_2000MHZ:
            switch(enumDpLaneCount)
            {
                case _DP_LINK_4_LANE:
                    return tDpMacRxPbnMappingUhbr20G4Lane[ucAvailableTimeSlot - 1];

                case _DP_LINK_2_LANE:
                    return tDpMacRxPbnMappingUhbr20G2Lane[ucAvailableTimeSlot - 1];

                case _DP_LINK_1_LANE:
                    return tDpMacRxPbnMappingUhbr20G1Lane[ucAvailableTimeSlot - 1];

                default:
                    break;
            }
            break;

        case _DP_ULTRA_SPEED_1350MHZ:
            switch(enumDpLaneCount)
            {
                case _DP_LINK_4_LANE:
                    return tDpMacRxPbnMappingUhbr13p5G4Lane[ucAvailableTimeSlot - 1];

                case _DP_LINK_2_LANE:
                    return tDpMacRxPbnMappingUhbr13p5G2Lane[ucAvailableTimeSlot - 1];

                case _DP_LINK_1_LANE:
                    return tDpMacRxPbnMappingUhbr13p5G1Lane[ucAvailableTimeSlot - 1];

                default:
                    break;
            }
            break;

        case _DP_ULTRA_SPEED_1000MHZ:
            switch(enumDpLaneCount)
            {
                case _DP_LINK_4_LANE:
                    return tDpMacRxPbnMappingUhbr10G4Lane[ucAvailableTimeSlot - 1];

                case _DP_LINK_2_LANE:
                    return tDpMacRxPbnMappingUhbr10G2Lane[ucAvailableTimeSlot - 1];

                case _DP_LINK_1_LANE:
                    return tDpMacRxPbnMappingUhbr10G1Lane[ucAvailableTimeSlot - 1];

                default:
                    break;
            }
            break;
#endif

        default:
            break;
    }

    return 0;
}

//--------------------------------------------------
// Description  : Calculate PBN of One Time Slot
// Input Value  : enumDpLaneCount, enumDpLinkRate
// Output Value : PBN(unit: 0.01PBN)
//--------------------------------------------------
WORD ScalerDpMacDphyRxGetPBNPerTimeSlot(EnumDpLinkRate enumDpLinkRate, EnumDpLaneCount enumDpLaneCount)
{
#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
    WORD code tDpMacRxPbnMapping_128b132b[9] =
    {
        17909, 8955, 4477, 12089, 6044, 3022, 8955, 4477, 2239,
    };
#endif

    switch(enumDpLinkRate)
    {
        case _DP_LOW_SPEED_162MHZ:
        case _DP_HIGH_SPEED_270MHZ:
        case _DP_HIGH_SPEED2_540MHZ:
        case _DP_HIGH_SPEED3_810MHZ:

            return (WORD) ((GET_DP_MAC_DPHY_RX_PBN_PER_TIME_SLOT(enumDpLinkRate, enumDpLaneCount)) * 100);

#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)

        case _DP_ULTRA_SPEED_2000MHZ:
            switch(enumDpLaneCount)
            {
                case _DP_LINK_4_LANE:
                    return tDpMacRxPbnMapping_128b132b[0];

                case _DP_LINK_2_LANE:
                    return tDpMacRxPbnMapping_128b132b[1];

                case _DP_LINK_1_LANE:
                    return tDpMacRxPbnMapping_128b132b[2];

                default:
                    break;
            }
            break;

        case _DP_ULTRA_SPEED_1350MHZ:
            switch(enumDpLaneCount)
            {
                case _DP_LINK_4_LANE:
                    return tDpMacRxPbnMapping_128b132b[3];

                case _DP_LINK_2_LANE:
                    return tDpMacRxPbnMapping_128b132b[4];

                case _DP_LINK_1_LANE:
                    return tDpMacRxPbnMapping_128b132b[5];

                default:
                    break;
            }
            break;

        case _DP_ULTRA_SPEED_1000MHZ:
            switch(enumDpLaneCount)
            {
                case _DP_LINK_4_LANE:
                    return tDpMacRxPbnMapping_128b132b[6];

                case _DP_LINK_2_LANE:
                    return tDpMacRxPbnMapping_128b132b[7];

                case _DP_LINK_1_LANE:
                    return tDpMacRxPbnMapping_128b132b[8];

                default:
                    break;
            }
            break;
#endif

        default:
            break;
    }

    return 0;
}

//--------------------------------------------------
// Description  : Restore Stream Postion Infomation From Backup to Reg
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxRestoreSourceMuxBackupToReg(EnumInputPort enumInputPort)
{
    EnumDpStreamSourceNum enumSourceNum = _DP_ST_SOURCE1;

    ScalerDpRxSetBaseInputPort(enumInputPort);

    for(enumSourceNum = _DP_ST_SOURCE1; enumSourceNum <= _DP_ST_SOURCE_END; enumSourceNum++)
    {
        ScalerDpMacDphyRxSetSourceMuxReg(enumInputPort, enumSourceNum, GET_DP_MAC_DPHY_RX_ST_SOURCE_BACKUP(enumSourceNum));
    }
}

//--------------------------------------------------
// Description  : Restore Stream Postion Infomation From Backup to Reg
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxRestorePositionBackupToRegAndLoad(EnumInputPort enumInputPort)
{
    EnumDpStreamNum enumDpStreamNum = _DP_ST_1;

    ScalerDpRxSetBaseInputPort(enumInputPort);

    for(enumDpStreamNum = _DP_ST_1; enumDpStreamNum <= _DP_ST_END; enumDpStreamNum++)
    {
        SET_DP_MAC_DPHY_RX_REG_ST_START_POSITION(enumDpStreamNum, GET_DP_MAC_DPHY_RX_ST_START_POSITION_BACKUP(enumDpStreamNum));
        SET_DP_MAC_DPHY_RX_REG_ST_END_POSITION(enumDpStreamNum, GET_DP_MAC_DPHY_RX_ST_END_POSITION_BACKUP(enumDpStreamNum));
        SET_DP_MAC_DPHY_RX_REG_ST_STATUS(enumDpStreamNum, GET_DP_MAC_DPHY_RX_ST_STATUS_BACKUP(enumDpStreamNum));
    }

    SET_DP_MAC_DPHY_RX_LOAD_NEW_STREAM_PAYLOAD();
}

//--------------------------------------------------
// Description  : DP MST Set St_source Mux Register
// Input Value  : enumSourceNum, ucValue
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxSetSourceMuxReg(EnumInputPort enumInputPort, EnumDpStreamSourceNum enumSourceNum, EnumDpStreamNum enumDpStreamNum)
{
#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
    if(enumInputPort == _D9_INPUT_PORT)
    {
        enumInputPort = GET_DP_MST_RX_PXP_INPUT_PORT();
    }
#endif

#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
    {
        ScalerDpMacDphyRxSetSourceMuxReg_128b132b(enumInputPort, enumSourceNum, enumDpStreamNum);
    }
    else
#endif
    {
#if(_DP_MST_SUPPORT == _ON)
        ScalerDpMacDphyRxSetSourceMuxReg_8b10b(enumInputPort, enumSourceNum, enumDpStreamNum);
#endif
    }
}

//--------------------------------------------------
// Description  : Reset ST1_Source ~ ST5_Source Mux
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxResetSourceMuxReg(EnumInputPort enumInputPort)
{
#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
    ScalerDpMacDphyRxResetSourceMuxReg_128b132b(enumInputPort);
#endif

#if(_DP_MST_SUPPORT == _ON)
    ScalerDpMacDphyRxResetSourceMuxReg_8b10b(enumInputPort);
#endif
}

//--------------------------------------------------
// Description  : Get DP Mst Rx Stream Reg Address
// Input Value  : None
// Output Value : Word Mst Rx Stream Reg Address
//--------------------------------------------------
WORD ScalerDpMacDphyRxGetStreamRegAddress(EnumInputPort enumInputPort)
{
#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
    if(enumInputPort == _D9_INPUT_PORT)
    {
        enumInputPort = GET_DP_MST_RX_PXP_INPUT_PORT();
    }
#endif

#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
    {
        return ScalerDpMacDphyRxGetPagedAddress(enumInputPort, P9D_02_STHD_CTRL_2);
    }
    else
#endif
    {
        return ScalerDpMacDphyRxGetPagedAddress(enumInputPort, PB5_02_STHD_CTRL_2);
    }
}

//--------------------------------------------------
// Description  : Get DP Mst Rx Source Reg Address
// Input Value  : None
// Output Value : Word Mst Rx Source Reg Address
//--------------------------------------------------
WORD ScalerDpMacDphyRxGetSourceRegAddress(EnumInputPort enumInputPort)
{
#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
    if(enumInputPort == _D9_INPUT_PORT)
    {
        enumInputPort = GET_DP_MST_RX_PXP_INPUT_PORT();
    }
#endif

#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
    {
        return ScalerDpMacDphyRxGetPagedAddress(enumInputPort, P9D_12_SOURCE_SEL_0);
    }
    else
#endif
    {
        return ScalerDpMacDphyRxGetPagedAddress(enumInputPort, PB5_12_SOURCE_SEL_0);
    }
}

//--------------------------------------------------
// Description  : Get DP Mst Rx Stream Status
// Input Value  : BYTE Stream x
// Output Value : bit Enable or Disable
//--------------------------------------------------
bit ScalerDpMacDphyRxGetStreamStatusReg(EnumInputPort enumInputPort, EnumDpStreamNum enumDpStreamNum)
{
    enumInputPort = enumInputPort;
    enumDpStreamNum = enumDpStreamNum;

    // 8b10b: start position = 0 -> disable, != 0 -> enable, 128b132b: bit7 indicate status
#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
    ScalerDpRxSetBaseInputPort(enumInputPort);

    if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
    {
        return ScalerGetBit((GET_DP_MAC_DPHY_RX_REG_ST_START_ADDR() + (enumDpStreamNum << 1)), _BIT7);
    }
    else
#endif
    {
        return (GET_DP_MAC_DPHY_RX_REG_ST_START_POSITION(enumDpStreamNum) != 0 ? 1 : 0);
    }
}


//--------------------------------------------------
// Description  : Set DP Mst Rx Stream Status
// Input Value  : BYTE Stream x
// Output Value : bit Enable or Disable
//--------------------------------------------------
void ScalerDpMacDphyRxSetStreamStatusReg(EnumInputPort enumInputPort, EnumDpStreamNum enumDpStreamNum, bit bEn)
{
    enumInputPort = enumInputPort;
    enumDpStreamNum = enumDpStreamNum;
    bEn = bEn;

    // 8b10b: start position = 0 -> disable, != 0 -> enable, 128b132b: bit7 indicate status
#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
    ScalerDpRxSetBaseInputPort(enumInputPort);

    if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
    {
        ScalerSetBit((GET_DP_MAC_DPHY_RX_REG_ST_START_ADDR() + (enumDpStreamNum << 1)), ~_BIT7, bEn << 7);
    }
#endif
}

//--------------------------------------------------
// Description  : DP Mst Rx Load New Stream PayLoad
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxLoadNewStreamPayload(EnumInputPort enumInputPort)
{
#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
    if(enumInputPort == _D9_INPUT_PORT)
    {
        enumInputPort = GET_DP_MST_RX_PXP_INPUT_PORT();
    }
#endif

#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
    {
        ScalerDpMacDphyRxLoadNewStreamPayload_128b132b(enumInputPort);
    }
    else
#endif
    {
#if(_DP_MST_SUPPORT == _ON)
        ScalerDpMacDphyRxLoadNewStreamPayload_8b10b(enumInputPort);
#endif
    }
}

//--------------------------------------------------
// Description  : Check DP Link Integrity
// Input Value  : enumInputPort
// Output Value : FALSE => DP Link Integrity Fail
//--------------------------------------------------
bit ScalerDpMacDphyRxGetMstStreamExist(EnumDpMacStreamSourceType enumDpMacStreamSourceType)
{
    ScalerDpRxSetBaseInputPort(ScalerDpMacStreamRxGetSourcePort(enumDpMacStreamSourceType));

    switch(enumDpMacStreamSourceType)
    {
        case _STREAM_SOURCE_D0_DP:
        case _STREAM_SOURCE_D1_DP:
        case _STREAM_SOURCE_D2_DP:
#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
        case _STREAM_SOURCE_PXP:
#endif

            {
                EnumDpStreamSourceNum enumSourceNum = ScalerDpMacStreamRxGetStreamSourceTypeToSourceMux(enumDpMacStreamSourceType);

                if((enumSourceNum < _HW_DP_MST_ST_SOURCE_COUNT) &&
                   (GET_DP_MAC_DPHY_RX_ST_SOURCE_BACKUP(enumSourceNum) != _DP_ST_NONE))
                {
                    return _TRUE;
                }
            }

            break;

#if(_DP_MST2SST_SUPPORT == _ON)
        case _STREAM_SOURCE_MST2SST:

            if(GET_DP_MAC_TX_ST_SOURCE_BACKUP(_DP_ST_SOURCE1) != _DP_ST_NONE)
            {
                return _TRUE;
            }

            break;
#endif

        default:
            break;
    }

    return _FALSE;
}
#endif

#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Mac Rx Auxless ALPM CLR Occurred
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxAuxlessAlpmClrOccurred(EnumInputPort enumInputPort)
{
#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
    if(enumInputPort == _D9_INPUT_PORT)
    {
        enumInputPort = GET_DP_MST_RX_PXP_INPUT_PORT();
    }
#endif

    switch(ScalerDpRxGetMacDphySwitch(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

            CLR_DP_MAC_DPHY_RX0_AUXLESS_ALPM_OCCURRED();

            break;
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            CLR_DP_MAC_DPHY_RX1_AUXLESS_ALPM_OCCURRED();

            break;
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            CLR_DP_MAC_DPHY_RX2_AUXLESS_ALPM_OCCURRED();

            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Mac Rx Auxless ALPM Get Occurred
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
bit ScalerDpMacDphyRxAuxlessAlpmGetOccurred(EnumInputPort enumInputPort)
{
#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
    if(enumInputPort == _D9_INPUT_PORT)
    {
        enumInputPort = GET_DP_MST_RX_PXP_INPUT_PORT();
    }
#endif

    if(ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x00, 0x01, 0x16, (_BIT2 | _BIT0)) != (_BIT2 | _BIT0))
    {
        return _FALSE;
    }

    switch(ScalerDpRxGetMacDphySwitch(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

            return GET_DP_MAC_DPHY_RX0_AUXLESS_ALPM_OCCURRED();
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            return GET_DP_MAC_DPHY_RX1_AUXLESS_ALPM_OCCURRED();
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            return GET_DP_MAC_DPHY_RX2_AUXLESS_ALPM_OCCURRED();
#endif

        default:
            return _FALSE;
    }
}

//--------------------------------------------------
// Description  : Mac Rx Auxless ALPM tDRL Calculate
// Input Value  : enumInputPort
// Output Value : tDRL time
//--------------------------------------------------
WORD ScalerDpMacDphyRxAuxlessAlpmTdrlTime(EnumInputPort enumInputPort)
{
#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
    if(enumInputPort == _D9_INPUT_PORT)
    {
        enumInputPort = GET_DP_MST_RX_PXP_INPUT_PORT();
    }
#endif

    switch(ScalerDpAuxRxGetDpcdLinkRate(enumInputPort))
    {
        case _DP_LINK_RBR:
            return _DP_AUXLESS_ALPM_TDRL_TIME_RBR;

        case _DP_LINK_HBR:
            return _DP_AUXLESS_ALPM_TDRL_TIME_HBR;

        case _DP_LINK_HBR2:
            return _DP_AUXLESS_ALPM_TDRL_TIME_HBR2;

        case _DP_LINK_HBR3:
            return _DP_AUXLESS_ALPM_TDRL_TIME_HBR3;

#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
        case _DP_LINK_UHBR10:
            return _DP_AUXLESS_ALPM_TDRL_TIME_UHBR10;

        case _DP_LINK_UHBR13_5:
            return _DP_AUXLESS_ALPM_TDRL_TIME_UHBR13_5;

        case _DP_LINK_UHBR20:
            return _DP_AUXLESS_ALPM_TDRL_TIME_UHBR20;
#endif

        default:
            return _DP_AUXLESS_ALPM_TDRL_TIME_RBR;
    }
}

//--------------------------------------------------
// Description  : Mac Rx Auxless ALPM Initial
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxAuxlessAlpmEnable(EnumInputPort enumInputPort, bit bEn)
{
#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
    if(enumInputPort == _D9_INPUT_PORT)
    {
        enumInputPort = GET_DP_MST_RX_PXP_INPUT_PORT();
    }
#endif

    switch(ScalerDpRxGetMacDphySwitch(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

            ScalerDpMacDphyRx0AuxlessAlpmEnable(enumInputPort, bEn);

            break;
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            ScalerDpMacDphyRx1AuxlessAlpmEnable(enumInputPort, bEn);

            break;
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            ScalerDpMacDphyRx2AuxlessAlpmEnable(enumInputPort, bEn);

            break;
#endif
        default:

            break;
    }
}
#endif

#if(_DP_8B10B_DEC_ERROR_WD_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Enable Dp 8b10b Decoder Error WD
// Input Value  : _ENABLE/ DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxSet8b10bDecErrorWD(EnumInputPort enumInputPort, bit bEn)
{
#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
    if(enumInputPort == _D9_INPUT_PORT)
    {
        enumInputPort = GET_DP_MST_RX_PXP_INPUT_PORT();
    }
#endif

    switch(ScalerDpRxGetMacDphySwitch(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

            ScalerDpMacDphyRx0Set8b10bDecErrorWD(bEn);

            break;
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            ScalerDpMacDphyRx1Set8b10bDecErrorWD(bEn);

            break;
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            ScalerDpMacDphyRx2Set8b10bDecErrorWD(bEn);

            break;
#endif

#if(_DUAL_DP_SUPPORT == _ON)
        case _DP_MAC_DPHY_DUAL:

#if(_DUAL_DP_MAC_USE == _DUAL_DP_MAC_RX0RX1)
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
            ScalerDpMacDphyRx0Set8b10bDecErrorWD(bEn);
#endif
#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
            ScalerDpMacDphyRx1Set8b10bDecErrorWD(bEn);
#endif
#elif(_DUAL_DP_MAC_USE == _DUAL_DP_MAC_RX1RX2)
#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
            ScalerDpMacDphyRx1Set8b10bDecErrorWD(bEn);
#endif
#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
            ScalerDpMacDphyRx2Set8b10bDecErrorWD(bEn);
#endif
#endif
            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Check Dp 8b10b Dec Err Status
// Input Value  : None
// Output Value : _SUCCESS --> No Dec Err
//                _FAIL    --> Dec Err Occur
//--------------------------------------------------
bit ScalerDpMacDphyRxCheck8b10bDecErrorStatus(EnumInputPort enumInputPort)
{
    bit bReturn = _FAIL;

#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
    if(enumInputPort == _D9_INPUT_PORT)
    {
        enumInputPort = GET_DP_MST_RX_PXP_INPUT_PORT();
    }
#endif

#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
    ScalerDpMacDphyRxAuxlessAlpmClrOccurred(enumInputPort);
#endif

    switch(ScalerDpRxGetMacDphySwitch(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

            bReturn = ScalerDpMacDphyRx0Check8b10bDecErrorStatus();

            break;
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            bReturn = ScalerDpMacDphyRx1Check8b10bDecErrorStatus();

            break;
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            bReturn = ScalerDpMacDphyRx2Check8b10bDecErrorStatus();

            break;
#endif

        default:
            break;
    }


#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
    if(ScalerDpMacDphyRxAuxlessAlpmGetOccurred(enumInputPort) == _TRUE)
    {
        return _SUCCESS;
    }
    else
#endif
    {
        return bReturn;
    }
}
#endif

//--------------------------------------------------
// Description  : Signal PreDetection for DP(Power Normal)
// Input Value  : _D0_INPUT_PORT or _D1_INPUT_PORT
// Output Value : True : DP Signal Detected
//              : False : No Signal
//--------------------------------------------------
bit ScalerDpMacDphyRxNormalPreDetect(EnumInputPort enumInputPort)
{
#if(_DUAL_DP_SUPPORT == _ON)
    EnumDpMacDphySel enumDpMacDphySelMain = _DP_MAC_DPHY_NONE;
    EnumDpMacDphySel enumDpMacDphySelSub = _DP_MAC_DPHY_NONE;
#endif

#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
    if(enumInputPort == _D9_INPUT_PORT)
    {
        enumInputPort = GET_DP_MST_RX_PXP_INPUT_PORT();
    }
#endif

    switch(ScalerDpRxGetMacDphySwitch(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)

        case _DP_MAC_DPHY_RX0:

            if(ScalerDpMacDphyRx0NormalPreDetect() == _TRUE)
            {
                return _TRUE;
            }

            break;
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)

        case _DP_MAC_DPHY_RX1:

            if(ScalerDpMacDphyRx1NormalPreDetect() == _TRUE)
            {
                return _TRUE;
            }

            break;
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)

        case _DP_MAC_DPHY_RX2:

            if(ScalerDpMacDphyRx2NormalPreDetect() == _TRUE)
            {
                return _TRUE;
            }

            break;
#endif

#if(_DUAL_DP_SUPPORT == _ON)
        case _DP_MAC_DPHY_DUAL:

            enumDpMacDphySelMain = ScalerDpRxGetMacDphySwitch(_DUAL_DP_MAIN_PORT);
            enumDpMacDphySelSub = ScalerDpRxGetMacDphySwitch(_DUAL_DP_SUB_PORT);

#if(_DUAL_DP_MAC_DPHY_USE == _DUAL_DP_MAC_DPHY_RX0RX1)
            if(((enumDpMacDphySelMain == _DP_MAC_DPHY_RX0) && (ScalerDpMacDphyRx0NormalPreDetect() == _TRUE)) ||
               ((enumDpMacDphySelMain == _DP_MAC_DPHY_RX1) && (ScalerDpMacDphyRx1NormalPreDetect() == _TRUE)))
            {
                if(((enumDpMacDphySelSub == _DP_MAC_DPHY_RX0) && (ScalerDpMacDphyRx0NormalPreDetect() == _TRUE)) ||
                   ((enumDpMacDphySelSub == _DP_MAC_DPHY_RX1) && (ScalerDpMacDphyRx1NormalPreDetect() == _TRUE)))
                {
                    SET_DUAL_DP_PORT_SWITCH_SELECT(_DUAL_DP_INPUT_PORT);
                }
                else
                {
                    SET_DUAL_DP_PORT_SWITCH_SELECT(_DUAL_DP_MAIN_PORT);
                }
                return _TRUE;
            }

#if(_DUAL_DP_SEARCH_MAIN_PORT_ONLY == _OFF)
            if(((enumDpMacDphySelSub == _DP_MAC_DPHY_RX0) && (ScalerDpMacDphyRx0NormalPreDetect() == _TRUE)) ||
               ((enumDpMacDphySelSub == _DP_MAC_DPHY_RX1) && (ScalerDpMacDphyRx1NormalPreDetect() == _TRUE)))
            {
                SET_DUAL_DP_PORT_SWITCH_SELECT(_DUAL_DP_SUB_PORT);
                return _TRUE;
            }
#endif

#elif(_DUAL_DP_MAC_DPHY_USE == _DUAL_DP_MAC_DPHY_RX1RX2)
            if(((enumDpMacDphySelMain == _DP_MAC_DPHY_RX1) && (ScalerDpMacDphyRx1NormalPreDetect() == _TRUE)) ||
               ((enumDpMacDphySelMain == _DP_MAC_DPHY_RX2) && (ScalerDpMacDphyRx2NormalPreDetect() == _TRUE)))
            {
                if(((enumDpMacDphySelSub == _DP_MAC_DPHY_RX1) && (ScalerDpMacDphyRx1NormalPreDetect() == _TRUE)) ||
                   ((enumDpMacDphySelSub == _DP_MAC_DPHY_RX2) && (ScalerDpMacDphyRx2NormalPreDetect() == _TRUE)))
                {
                    SET_DUAL_DP_PORT_SWITCH_SELECT(_DUAL_DP_INPUT_PORT);
                }
                else
                {
                    SET_DUAL_DP_PORT_SWITCH_SELECT(_DUAL_DP_MAIN_PORT);
                }
                return _TRUE;
            }

#if(_DUAL_DP_SEARCH_MAIN_PORT_ONLY == _OFF)
            if(((enumDpMacDphySelSub == _DP_MAC_DPHY_RX1) && (ScalerDpMacDphyRx1NormalPreDetect() == _TRUE)) ||
               ((enumDpMacDphySelSub == _DP_MAC_DPHY_RX2) && (ScalerDpMacDphyRx2NormalPreDetect() == _TRUE)))
            {
                SET_DUAL_DP_PORT_SWITCH_SELECT(_DUAL_DP_SUB_PORT);
                return _TRUE;
            }
#endif
#endif
            break;
#endif

        default:

            break;
    }

#if((_DP_MST_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
    if(ScalerDpMstRxReactiveSearchTimeCheck(enumInputPort) == _TRUE)
    {
        return _TRUE;
    }
#endif

    return _FALSE;
}

//--------------------------------------------------
// Description  : Signal Detection for DP(Power Saving)
// Input Value  : _D0_INPUT_PORT or _D1_INPUT_PORT
// Output Value : True : DP Signal Detected
//              : False : No Signal
//--------------------------------------------------
bit ScalerDpMacDphyRxPSPreDetect(EnumInputPort enumInputPort)
{
#if(_DUAL_DP_SUPPORT == _ON)
    EnumDpMacDphySel enumDpMacDphySelMain = _DP_MAC_DPHY_NONE;
    EnumDpMacDphySel enumDpMacDphySelSub = _DP_MAC_DPHY_NONE;
#endif

#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
    if(enumInputPort == _D9_INPUT_PORT)
    {
        enumInputPort = GET_DP_MST_RX_PXP_INPUT_PORT();
    }
#endif

    switch(ScalerDpRxGetMacDphySwitch(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)

        case _DP_MAC_DPHY_RX0:

            if(ScalerDpMacDphyRx0PSPreDetect() == _TRUE)
            {
                return _TRUE;
            }

            break;
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            if(ScalerDpMacDphyRx1PSPreDetect() == _TRUE)
            {
                return _TRUE;
            }

            break;
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            if(ScalerDpMacDphyRx2PSPreDetect() == _TRUE)
            {
                return _TRUE;
            }

            break;
#endif

#if(_DUAL_DP_SUPPORT == _ON)
        case _DP_MAC_DPHY_DUAL:

            enumDpMacDphySelMain = ScalerDpRxGetMacDphySwitch(_DUAL_DP_MAIN_PORT);
            enumDpMacDphySelSub = ScalerDpRxGetMacDphySwitch(_DUAL_DP_SUB_PORT);

#if(_DUAL_DP_MAC_DPHY_USE == _DUAL_DP_MAC_DPHY_RX0RX1)
            if(((enumDpMacDphySelMain == _DP_MAC_DPHY_RX0) && (ScalerDpMacDphyRx0PSPreDetect() == _TRUE)) ||
               ((enumDpMacDphySelMain == _DP_MAC_DPHY_RX1) && (ScalerDpMacDphyRx1PSPreDetect() == _TRUE)))
            {
                if(((enumDpMacDphySelSub == _DP_MAC_DPHY_RX0) && (ScalerDpMacDphyRx0PSPreDetect() == _TRUE)) ||
                   ((enumDpMacDphySelSub == _DP_MAC_DPHY_RX1) && (ScalerDpMacDphyRx1PSPreDetect() == _TRUE)))
                {
                    SET_DUAL_DP_PORT_SWITCH_SELECT(_DUAL_DP_INPUT_PORT);
                }
                else
                {
                    SET_DUAL_DP_PORT_SWITCH_SELECT(_DUAL_DP_MAIN_PORT);
                }
                return _TRUE;
            }

#if(_DUAL_DP_SEARCH_MAIN_PORT_ONLY == _OFF)
            if(((enumDpMacDphySelSub == _DP_MAC_DPHY_RX0) && (ScalerDpMacDphyRx0PSPreDetect() == _TRUE)) ||
               ((enumDpMacDphySelSub == _DP_MAC_DPHY_RX1) && (ScalerDpMacDphyRx1PSPreDetect() == _TRUE)))
            {
                SET_DUAL_DP_PORT_SWITCH_SELECT(_DUAL_DP_SUB_PORT);
                return _TRUE;
            }
#endif

#elif(_DUAL_DP_MAC_DPHY_USE == _DUAL_DP_MAC_DPHY_RX1RX2)
            if(((enumDpMacDphySelMain == _DP_MAC_DPHY_RX1) && (ScalerDpMacDphyRx1PSPreDetect() == _TRUE)) ||
               ((enumDpMacDphySelMain == _DP_MAC_DPHY_RX2) && (ScalerDpMacDphyRx2PSPreDetect() == _TRUE)))
            {
                if(((enumDpMacDphySelSub == _DP_MAC_DPHY_RX1) && (ScalerDpMacDphyRx1PSPreDetect() == _TRUE)) ||
                   ((enumDpMacDphySelSub == _DP_MAC_DPHY_RX2) && (ScalerDpMacDphyRx2PSPreDetect() == _TRUE)))
                {
                    SET_DUAL_DP_PORT_SWITCH_SELECT(_DUAL_DP_INPUT_PORT);
                }
                else
                {
                    SET_DUAL_DP_PORT_SWITCH_SELECT(_DUAL_DP_MAIN_PORT);
                }
                return _TRUE;
            }

#if(_DUAL_DP_SEARCH_MAIN_PORT_ONLY == _OFF)
            if(((enumDpMacDphySelSub == _DP_MAC_DPHY_RX1) && (ScalerDpMacDphyRx1PSPreDetect() == _TRUE)) ||
               ((enumDpMacDphySelSub == _DP_MAC_DPHY_RX2) && (ScalerDpMacDphyRx2PSPreDetect() == _TRUE)))
            {
                SET_DUAL_DP_PORT_SWITCH_SELECT(_DUAL_DP_SUB_PORT);
                return _TRUE;
            }
#endif
#endif
            break;
#endif

        default:

            break;
    }

#if(_DP_MST_SUPPORT == _ON)
#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
    if((GET_DP_MST_RX_PXP_MODE_SUPPORT() == _ON) && (GET_DP_MST_RX_PXP_INPUT_PORT() == enumInputPort))
    {
        if(ScalerDpMacDphyRxGetStreamAllocateInfo(enumInputPort, ScalerDpMstRxDxPortNumMapping(_D9_INPUT_PORT)) != _DP_ST_NONE)
        {
            DebugMessageDpRx("DP MAC RX: Pxp Stream Allocate", 0);

            return _TRUE;
        }
    }
#endif

#if(_DP_TX_SUPPORT == _ON)
    if(ScalerDpMstRxReactiveSearchTimeCheck(enumInputPort) == _TRUE)
    {
        return _TRUE;
    }
#endif
#endif

    return _FALSE;
}

//--------------------------------------------------
// Description  : HDCP Unplug Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxHDCPUnplugReset(EnumInputPort enumInputPort)
{
#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
    if(enumInputPort == _D9_INPUT_PORT)
    {
        enumInputPort = GET_DP_MST_RX_PXP_INPUT_PORT();
    }
#endif

    switch(ScalerDpRxGetMacDphySwitch(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

            ScalerDpMacDphyRx0HDCPUnplugReset();

            break;
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            ScalerDpMacDphyRx1HDCPUnplugReset();

            break;
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            ScalerDpMacDphyRx2HDCPUnplugReset();

            break;
#endif

        default:

            break;
    }
}

#if(_DP_MST_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Backup MST Info
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxMstInfoBackup(EnumInputPort enumInputPort, EnumDpMstBackup enumDpMstBackup)
{
#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
    if(enumInputPort == _D9_INPUT_PORT)
    {
        enumInputPort = GET_DP_MST_RX_PXP_INPUT_PORT();
    }
#endif

    switch(ScalerDpRxGetMacDphySwitch(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

            ScalerDpMacDphyRx0MstInfoBackup(enumDpMstBackup);

            break;
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            ScalerDpMacDphyRx1MstInfoBackup(enumDpMstBackup);

            break;
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            ScalerDpMacDphyRx2MstInfoBackup(enumDpMstBackup);

            break;
#endif

        default:

            break;
    }
}
#endif

#if((_DP_MST_SUPPORT == _ON) || (_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Check ST1_Source ~ ST6_Source Mux Change
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxStreamChangeHandler(void)
{
    EnumInputPort enumInputPort = _D0_INPUT_PORT;

    for(enumInputPort = _D0_INPUT_PORT; enumInputPort <= _D2_INPUT_PORT; enumInputPort++)
    {
        if(ScalerSyncGetPortType(enumInputPort) != _PORT_DP)
        {
            continue;
        }

        // MAC is power off when Fake LT is true -> can not access register
        if(ScalerDpMacRxGetPowerCutFlagStatus(enumInputPort) == _TRUE)
        {
            continue;
        }

        ScalerDpRxSetBaseInputPort(enumInputPort);

        if(GET_DP_MAC_DPHY_RX_ST_SOURCE_CHANGE() == _TRUE)
        {
            ScalerDpMacDphyRxRestoreSourceMuxBackupToReg(enumInputPort);

            CLR_DP_MAC_DPHY_RX_ST_SOURCE_CHANGE();
        }

        if(GET_DP_MAC_DPHY_RX_ST_POSITION_CHANGE() == _TRUE)
        {
            ScalerDpMacDphyRxRestorePositionBackupToRegAndLoad(enumInputPort);

            CLR_DP_MAC_DPHY_RX_ST_POSITION_CHANGE();
        }
    }
}

//--------------------------------------------------
// Description  : Mapping EnumDpMstPort to EnumDpMacNeededPort
// Input Value  : EnumDpMstPort
// Output Value : EnumDpMacNeededPort
//--------------------------------------------------
EnumDpMacNeededPort ScalerDpMacDphyRxGetMstPortToMacNeededPort(EnumDpMstPort enumDpMstPort)
{
    switch(enumDpMstPort)
    {
        case _DP_PORT8:
        default:

            return _DP_RX_PORT8;

#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
        case _DP_PORT9:

            return _DP_RX_PORT9;
#endif

#if(_DP_MST2SST_SUPPORT == _ON)
        case _DP_PORT1:

            return _DP_TX_PORT1;
#endif
    }
}

//--------------------------------------------------
// Description  : Set Stream Allocate Info
// Input Value  : enumInputPort, EnumDpMstPort, enumDpStreamNum
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxSetStreamAllocateInfo(EnumInputPort enumInputPort, EnumDpMstPort enumDpMstPort, EnumDpStreamNum enumDpStreamNum)
{
#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
    if(enumInputPort == _D9_INPUT_PORT)
    {
        enumInputPort = GET_DP_MST_RX_PXP_INPUT_PORT();
    }
#endif

    BYTE ucIndex = enumInputPort - _D0_INPUT_PORT;

    if(ucIndex < _DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS)
    {
        EnumDpMacNeededPort enumDpMacNeededPort = ScalerDpMacDphyRxGetMstPortToMacNeededPort(enumDpMstPort);
        g_ppenumDpMacDphyRxStreamAllocateInfo[ucIndex][enumDpMacNeededPort] = enumDpStreamNum;
    }
}

//--------------------------------------------------
// Description  : Get Stream Allocate Info
// Input Value  : enumInputPort, EnumDpMstPort
// Output Value : enumDpStreamNum
//--------------------------------------------------
EnumDpStreamNum ScalerDpMacDphyRxGetStreamAllocateInfo(EnumInputPort enumInputPort, EnumDpMstPort enumDpMstPort)
{
#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
    if(enumInputPort == _D9_INPUT_PORT)
    {
        enumInputPort = GET_DP_MST_RX_PXP_INPUT_PORT();
    }
#endif

    BYTE ucIndex = enumInputPort - _D0_INPUT_PORT;

    if(ucIndex < _DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS)
    {
        EnumDpMacNeededPort enumDpMacNeededPort = ScalerDpMacDphyRxGetMstPortToMacNeededPort(enumDpMstPort);
        return g_ppenumDpMacDphyRxStreamAllocateInfo[ucIndex][enumDpMacNeededPort];
    }

    return _DP_ST_NONE;
}

//--------------------------------------------------
// Description  : Reset Stream Allocate Info
// Input Value  : enumInputPort
// Output Value : EnumStxSource
//--------------------------------------------------
void ScalerDpMacDphyRxResetStreamAllocateInfo(EnumInputPort enumInputPort)
{
#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
    if(enumInputPort == _D9_INPUT_PORT)
    {
        enumInputPort = GET_DP_MST_RX_PXP_INPUT_PORT();
    }
#endif

    BYTE ucIndex = enumInputPort - _D0_INPUT_PORT;

    if(ucIndex < _DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS)
    {
        EnumDpMacNeededPort enumDpMacNeededPort = _DP_RX_PORT8;

        for(enumDpMacNeededPort = _DP_RX_PORT8; enumDpMacNeededPort < _DP_TOTAL_MAC_NEEDED_PORT; enumDpMacNeededPort++)
        {
            g_ppenumDpMacDphyRxStreamAllocateInfo[ucIndex][enumDpMacNeededPort] = _DP_ST_NONE;
        }
    }
}

#if(_HW_DP_MAC_STREAM_SWITCH_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Snyc Source Mux According Mac and InputPort
// Input Value  : EnumDpMacSel, EnumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxSyncSourceMux(EnumDpMacSel enumDpMacSel, EnumInputPort enumInputPort)
{
    EnumInputPort enumPortTemp = _D0_INPUT_PORT;
    EnumDpMstPort enumDpMstPort = _DP_PORT8;

#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
    if(enumInputPort == _D9_INPUT_PORT)
    {
        enumInputPort = GET_DP_MST_RX_PXP_INPUT_PORT();
    }
#endif

    // Decide Which Mst Port Needed to Sync
    switch(ScalerDpRxGetMacStreamSourceType(enumDpMacSel))
    {
        case _STREAM_SOURCE_D0_DP:
        case _STREAM_SOURCE_D1_DP:
        case _STREAM_SOURCE_D2_DP:

            enumDpMstPort = ScalerDpMstRxDxPortNumMapping(enumInputPort);
            break;

#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
        case _STREAM_SOURCE_PXP:

            enumDpMstPort = ScalerDpMstRxDxPortNumMapping(_D9_INPUT_PORT);
            break;
#endif

#if(_DP_MST2SST_SUPPORT == _ON)
        case _STREAM_SOURCE_MST2SST:

            enumDpMstPort = ScalerDpMstTxPxPortNumMapping(_P0_OUTPUT_PORT);
            break;
#endif

        default:
            break;
    }

    // Enable Mux For Current InputPort, disable Other InputPorts
    for(enumPortTemp = _D0_INPUT_PORT; enumPortTemp <= _D2_INPUT_PORT; enumPortTemp++)
    {
        if(enumInputPort == enumPortTemp)
        {
            ScalerDpMacDphyRxSetSourceMuxBackup(enumPortTemp,
                                                ScalerDpMacStreamRxGetMacToSourceMux(enumDpMacSel),
                                                ScalerDpMacDphyRxGetStreamAllocateInfo(enumPortTemp, enumDpMstPort));
        }
        else
        {
            ScalerDpMacDphyRxSetSourceMuxBackup(enumPortTemp,
                                                ScalerDpMacStreamRxGetMacToSourceMux(enumDpMacSel),
                                                _DP_ST_NONE);
        }
    }
}
#endif

//--------------------------------------------------
// Description  : Set ST1_Source ~ ST6_Source Mux Backup
// Input Value  : EnumDpStreamSourceNum, EnumDpMstRxStreamNum
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxSetSourceMuxBackup(EnumInputPort enumInputPort, EnumDpStreamSourceNum enumSourceNum, EnumDpStreamNum enumStreamNum)
{
    if(enumSourceNum >= _HW_DP_MST_ST_SOURCE_COUNT)
    {
        return;
    }

    ScalerDpRxSetBaseInputPort(enumInputPort);

    if(GET_DP_MAC_DPHY_RX_ST_SOURCE_BACKUP(enumSourceNum) != enumStreamNum)
    {
        SET_DP_MAC_DPHY_RX_ST_SOURCE_BACKUP(enumSourceNum, enumStreamNum);

        SET_DP_MAC_DPHY_RX_ST_SOURCE_CHANGE();
    }
}

#endif

#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP MST Set St_source Mux Register
// Input Value  : enumSourceNum, ucValue
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxSetSourceMuxReg_128b132b(EnumInputPort enumInputPort, EnumDpStreamSourceNum enumSourceNum, EnumDpStreamNum enumDpStreamNum)
{
    BYTE ucValue = (enumDpStreamNum == _DP_ST_NONE) ? 0 : enumDpStreamNum + 1;

    switch(enumSourceNum)
    {
        case _DP_ST_SOURCE1:

            ScalerSetBit(ScalerDpMacDphyRxGetPagedAddress(enumInputPort, P9D_12_SOURCE_SEL_0), ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), ucValue << 4);
            break;

        case _DP_ST_SOURCE2:

            ScalerSetBit(ScalerDpMacDphyRxGetPagedAddress(enumInputPort, P9D_12_SOURCE_SEL_0), ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ucValue << 0);
            break;

        case _DP_ST_SOURCE3:

            ScalerSetBit(ScalerDpMacDphyRxGetPagedAddress(enumInputPort, P9D_13_SOURCE_SEL_1), ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), ucValue << 4);
            break;

        case _DP_ST_SOURCE4:

            ScalerSetBit(ScalerDpMacDphyRxGetPagedAddress(enumInputPort, P9D_13_SOURCE_SEL_1), ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ucValue << 0);
            break;

        case _DP_ST_SOURCE5:

            ScalerSetBit(ScalerDpMacDphyRxGetPagedAddress(enumInputPort, P9D_14_SOURCE_SEL_2), ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), ucValue << 4);
            break;

        case _DP_ST_SOURCE6:

            ScalerSetBit(ScalerDpMacDphyRxGetPagedAddress(enumInputPort, P9D_14_SOURCE_SEL_2), ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ucValue << 0);
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Reset ST1_Source ~ ST5_Source Mux
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxResetSourceMuxReg_128b132b(EnumInputPort enumInputPort)
{
    ScalerSetBit(ScalerDpMacDphyRxGetPagedAddress(enumInputPort, P9D_12_SOURCE_SEL_0), ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);
    ScalerSetBit(ScalerDpMacDphyRxGetPagedAddress(enumInputPort, P9D_12_SOURCE_SEL_0), ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(ScalerDpMacDphyRxGetPagedAddress(enumInputPort, P9D_13_SOURCE_SEL_1), ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);
    ScalerSetBit(ScalerDpMacDphyRxGetPagedAddress(enumInputPort, P9D_13_SOURCE_SEL_1), ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(ScalerDpMacDphyRxGetPagedAddress(enumInputPort, P9D_14_SOURCE_SEL_2), ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);
    ScalerSetBit(ScalerDpMacDphyRxGetPagedAddress(enumInputPort, P9D_14_SOURCE_SEL_2), ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
}

//--------------------------------------------------
// Description  : DP Mst Rx Load New Stream PayLoad
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxLoadNewStreamPayload_128b132b(EnumInputPort enumInputPort)
{
    // Load by MTPH_CNT = 63, Delay 5us, Then Load by Receiving ACT
    ScalerSetBit(ScalerDpMacDphyRxGetPagedAddress(enumInputPort, P9D_01_STHD_CTRL_1), ~_BIT7, 0x00);

    // Delay Up to 65537 Timeslots
    // 3.2ns per Timeslot for UHBR10
    // Delay Time  >=  65537 * 3.2ns = 210ns, as 500ns for Insurance Purposes
    DELAY_XUS(500);
    ScalerSetBit(ScalerDpMacDphyRxGetPagedAddress(enumInputPort, P9D_01_STHD_CTRL_1), ~_BIT7, _BIT7);
}
#endif // End of #if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
#endif // End of #if(_DP_SUPPORT == _ON)
