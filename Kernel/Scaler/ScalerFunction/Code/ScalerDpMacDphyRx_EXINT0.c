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
// ID Code      : ScalerDpMacDphyRx_EXINT0.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_DP_MAC_DPHY_RX_EXINT0__

#include "ScalerFunctionInclude.h"
#include "DpMacDphyRx/ScalerDpMacDphyRx.h"

#if(_DP_SUPPORT == _ON)
//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_DP_MST_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP MST Set St_source Mux Register
// Input Value  : enumSourceNum, ucValue
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxSetSourceMuxReg_8b10b_EXINT0(EnumInputPort enumInputPort, EnumDpStreamSourceNum enumSourceNum, EnumDpStreamNum enumDpStreamNum)
{
    BYTE ucValue = (enumDpStreamNum == _DP_ST_NONE) ? 0 : enumDpStreamNum + 1;

    switch(enumSourceNum)
    {
        case _DP_ST_SOURCE1:

            ScalerSetBit_EXINT(ScalerDpMacDphyRxGetPagedAddress_EXINT0(enumInputPort, PB5_12_SOURCE_SEL_0), ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), ucValue << 4);
            break;

        case _DP_ST_SOURCE2:

            ScalerSetBit_EXINT(ScalerDpMacDphyRxGetPagedAddress_EXINT0(enumInputPort, PB5_12_SOURCE_SEL_0), ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ucValue << 0);
            break;

        case _DP_ST_SOURCE3:

            ScalerSetBit_EXINT(ScalerDpMacDphyRxGetPagedAddress_EXINT0(enumInputPort, PB5_13_SOURCE_SEL_1), ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), ucValue << 4);
            break;

        case _DP_ST_SOURCE4:

            ScalerSetBit_EXINT(ScalerDpMacDphyRxGetPagedAddress_EXINT0(enumInputPort, PB5_13_SOURCE_SEL_1), ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ucValue << 0);
            break;

        case _DP_ST_SOURCE5:

            ScalerSetBit_EXINT(ScalerDpMacDphyRxGetPagedAddress_EXINT0(enumInputPort, PB5_14_SOURCE_SEL_2), ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), ucValue << 4);
            break;

        case _DP_ST_SOURCE6:

            ScalerSetBit_EXINT(ScalerDpMacDphyRxGetPagedAddress_EXINT0(enumInputPort, PB5_14_SOURCE_SEL_2), ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ucValue << 0);
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Backup ST1_Source ~ ST6_Source Clear
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxResetSourceMuxReg_8b10b_EXINT0(EnumInputPort enumInputPort)
{
    ScalerSetBit_EXINT(ScalerDpMacDphyRxGetPagedAddress(enumInputPort, PB5_12_SOURCE_SEL_0), ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);
    ScalerSetBit_EXINT(ScalerDpMacDphyRxGetPagedAddress(enumInputPort, PB5_12_SOURCE_SEL_0), ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(ScalerDpMacDphyRxGetPagedAddress(enumInputPort, PB5_13_SOURCE_SEL_1), ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);
    ScalerSetBit_EXINT(ScalerDpMacDphyRxGetPagedAddress(enumInputPort, PB5_13_SOURCE_SEL_1), ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(ScalerDpMacDphyRxGetPagedAddress(enumInputPort, PB5_14_SOURCE_SEL_2), ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);
    ScalerSetBit_EXINT(ScalerDpMacDphyRxGetPagedAddress(enumInputPort, PB5_14_SOURCE_SEL_2), ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
}

//--------------------------------------------------
// Description  : DP Mst Rx Load New Stream PayLoad EXINT0
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxLoadNewStreamPayload_8b10b_EXINT0(EnumInputPort enumInputPort)
{
    // Load by MTPH_CNT = 63, Delay 5us, Then Load by Receiving ACT
    ScalerSetBit_EXINT(ScalerDpMacDphyRxGetPagedAddress_EXINT0(enumInputPort, PB5_01_STHD_CTRL_1), ~_BIT7, 0x00);
    DELAY_5US_EXINT();
    ScalerSetBit_EXINT(ScalerDpMacDphyRxGetPagedAddress_EXINT0(enumInputPort, PB5_01_STHD_CTRL_1), ~_BIT7, _BIT7);
}
#endif

#if((_DP_MST_SUPPORT == _ON) || (_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Reset ST1 ~ ST6
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxResetStreamPositionReg_EXINT0(EnumInputPort enumInputPort)
{
    EnumDpStreamNum enumDpStreamNum = _DP_ST_1;

    ScalerDpRxSetBaseInputPort_EXINT0(enumInputPort);

    for(enumDpStreamNum = _DP_ST_1; enumDpStreamNum <= _DP_ST_END; enumDpStreamNum++)
    {
        // Reset Start Position
        ScalerSetBit_EXINT((GET_DP_MAC_DPHY_RX_REG_ST_START_ADDR_8B10B_EXINT() + ((enumDpStreamNum) << 1)), ~0x3F, (0x00));

        // Reset End Position
        ScalerSetBit_EXINT((GET_DP_MAC_DPHY_RX_REG_ST_START_ADDR_8B10B_EXINT() + ((enumDpStreamNum) << 1) + 1), ~0x3F, (0x00));

#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
        // Reset Stream Enable
        ScalerSetBit_EXINT((GET_DP_MAC_DPHY_RX_REG_ST_START_ADDR_128B132B_EXINT() + ((enumDpStreamNum) << 1)), ~_BIT7, (0x00));

        // Reset Start Position
        ScalerSetBit_EXINT((GET_DP_MAC_DPHY_RX_REG_ST_START_ADDR_128B132B_EXINT() + ((enumDpStreamNum) << 1)), ~0x3F, (0x00));

        // Reset End Position
        ScalerSetBit_EXINT((GET_DP_MAC_DPHY_RX_REG_ST_START_ADDR_128B132B_EXINT() + ((enumDpStreamNum) << 1) + 1), ~0x3F, (0x00));
#endif
    }
}

//--------------------------------------------------
// Description  : Check Add Payload ID Whether Existed Or Not
// Input Value  : PayloadID
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
BYTE ScalerDpMacDphyRxCheckIDExisted_EXINT0(EnumInputPort enumInputPort, BYTE ucPayloadID)
{
    EnumDpStreamNum enumDpStreamNum = _DP_ST_1;

    for(enumDpStreamNum = _DP_ST_1; enumDpStreamNum <= _DP_ST_END; enumDpStreamNum++)
    {
        // ID Exist in STx to ID Table
        if(ucPayloadID == GET_DP_MAC_DPHY_RX_STREAM_TO_ID_MAPPING(enumInputPort, enumDpStreamNum))
        {
            return _TRUE;
        }
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Search ST1 ~ ST6 to Match Input Paramater
// Input Value  : Target ID
// Output Value : Match ST Number Index
//--------------------------------------------------
EnumDpStreamNum ScalerDpMacDphyRxSearchMatchStream_EXINT0(EnumInputPort enumInputPort, BYTE ucTargetID)
{
    EnumDpStreamNum enumDpStreamNum = _DP_ST_1;

    for(enumDpStreamNum = _DP_ST_1; enumDpStreamNum <= _DP_ST_END; enumDpStreamNum++)
    {
        // Setting STx to ID Table
        if(GET_DP_MAC_DPHY_RX_STREAM_TO_ID_MAPPING(enumInputPort, enumDpStreamNum) == ucTargetID)
        {
            return enumDpStreamNum;
        }
    }

    return _DP_ST_NONE;
}

//--------------------------------------------------
// Description  : Clear Stream Payload ID Mapping Table
// Input Value  : void
// Output Value : void
//--------------------------------------------------
void ScalerDpMacDphyRxResetStreamToIDMapping_EXINT0(EnumInputPort enumInputPort)
{
    EnumDpStreamNum enumDpStreamNum = _DP_ST_1;

    for(enumDpStreamNum = _DP_ST_1; enumDpStreamNum <= _DP_ST_END; enumDpStreamNum++)
    {
        SET_DP_MAC_DPHY_RX_STREAM_TO_ID_MAPPING(enumInputPort, enumDpStreamNum, 0);
    }
}

//--------------------------------------------------
// Description  : Mapping EnumDpMstPort to EnumDpMacNeededPort
// Input Value  : EnumDpMstPort
// Output Value : EnumDpMacNeededPort
//--------------------------------------------------
EnumDpMacNeededPort ScalerDpMacDphyRxGetMstPortToMacNeededPort_EXINT0(EnumDpMstPort enumDpMstPort)
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
// Input Value  : enumInputPort, enumDpMstPort, enumDpStreamNum
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxSetStreamAllocateInfo_EXINT0(EnumInputPort enumInputPort, EnumDpMstPort enumDpMstPort, EnumDpStreamNum enumDpStreamNum)
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
        EnumDpMacNeededPort enumDpMacNeededPort = ScalerDpMacDphyRxGetMstPortToMacNeededPort_EXINT0(enumDpMstPort);
        g_ppenumDpMacDphyRxStreamAllocateInfo[ucIndex][enumDpMacNeededPort] = enumDpStreamNum;
    }
}

//--------------------------------------------------
// Description  : Get Stream Allocate Info
// Input Value  : enumInputPort, EnumDpMstPort
// Output Value : EnumDpStreamNum
//--------------------------------------------------
EnumDpStreamNum ScalerDpMacDphyRxGetStreamAllocateInfo_EXINT0(EnumInputPort enumInputPort, EnumDpMstPort enumDpMstPort)
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
        EnumDpMacNeededPort enumDpMacNeededPort = ScalerDpMacDphyRxGetMstPortToMacNeededPort_EXINT0(enumDpMstPort);
        return g_ppenumDpMacDphyRxStreamAllocateInfo[ucIndex][enumDpMacNeededPort];
    }

    return _DP_ST_NONE;
}

//--------------------------------------------------
// Description  : Reset Stream Allocate Info
// Input Value  : enumInputPort
// Output Value : EnumStxSource
//--------------------------------------------------
void ScalerDpMacDphyRxResetStreamAllocateInfo_EXINT0(EnumInputPort enumInputPort)
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

//--------------------------------------------------
// Description  : Get Stream Source Status
// Input Value  : Source Number
// Output Value : Stream Number
//--------------------------------------------------
EnumDpStreamNum ScalerDpMacDphyRxGetSourceMuxBackup_EXINT0(EnumInputPort enumInputPort, EnumDpStreamSourceNum enumDpStreamSourceNum)
{
    ScalerDpRxSetBaseInputPort_EXINT0(enumInputPort);

    return GET_DP_MAC_DPHY_RX_ST_SOURCE_BACKUP(enumDpStreamSourceNum);
}

//--------------------------------------------------
// Description  : Set ST1_Source ~ ST6_Source Mux Backup
// Input Value  : EnumDpStreamSourceNum, EnumDpMstRxStreamNum
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxSetSourceMuxBackup_EXINT0(EnumInputPort enumInputPort, EnumDpStreamSourceNum enumSourceNum, EnumDpStreamNum enumStreamNum)
{
    if(enumSourceNum >= _HW_DP_MST_ST_SOURCE_COUNT)
    {
        return;
    }

    ScalerDpRxSetBaseInputPort_EXINT0(enumInputPort);

    if(GET_DP_MAC_DPHY_RX_ST_SOURCE_BACKUP(enumSourceNum) != enumStreamNum)
    {
        SET_DP_MAC_DPHY_RX_ST_SOURCE_BACKUP(enumSourceNum, enumStreamNum);

        SET_DP_MAC_DPHY_RX_ST_SOURCE_CHANGE();
    }
}

//--------------------------------------------------
// Description  : Set ST1 ~ ST6 Start Backup
// Input Value  : EnumDpStreamNum, BYTE ucValue
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxSetStreamStartBackup_EXINT0(EnumInputPort enumInputPort, EnumDpStreamNum enumDpStreamNum, BYTE ucValue)
{
    ScalerDpRxSetBaseInputPort_EXINT0(enumInputPort);

    if(GET_DP_MAC_DPHY_RX_ST_START_POSITION_BACKUP(enumDpStreamNum) != ucValue)
    {
        SET_DP_MAC_DPHY_RX_ST_START_POSITION_BACKUP(enumDpStreamNum, ucValue);

        if(ScalerDpMacRxGetPowerCutFlagStatus_EXINT0(enumInputPort) == _FALSE)
        {
            SET_DP_MAC_DPHY_RX_REG_ST_START_POSITION_EXINT(enumDpStreamNum, ucValue);
        }
        else
        {
            SET_DP_MAC_DPHY_RX_ST_POSITION_CHANGE();
        }
    }
}

//--------------------------------------------------
// Description  : Set ST1 ~ ST6 End Backup
// Input Value  : EnumDpStreamNum, BYTE ucValue
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxSetStreamEndBackup_EXINT0(EnumInputPort enumInputPort, EnumDpStreamNum enumDpStreamNum, BYTE ucValue)
{
    ScalerDpRxSetBaseInputPort_EXINT0(enumInputPort);

    if(GET_DP_MAC_DPHY_RX_ST_END_POSITION_BACKUP(enumDpStreamNum) != ucValue)
    {
        SET_DP_MAC_DPHY_RX_ST_END_POSITION_BACKUP(enumDpStreamNum, ucValue);

        if(ScalerDpMacRxGetPowerCutFlagStatus_EXINT0(enumInputPort) == _FALSE)
        {
            SET_DP_MAC_DPHY_RX_REG_ST_END_POSITION_EXINT(enumDpStreamNum, ucValue);
        }
        else
        {
            SET_DP_MAC_DPHY_RX_ST_POSITION_CHANGE();
        }
    }
}

//--------------------------------------------------
// Description  : Set ST1 ~ ST6 Status Backup
// Input Value  : EnumDpStreamNum, bit bEnable
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxSetStreamStatusBackup_EXINT0(EnumInputPort enumInputPort, EnumDpStreamNum enumDpStreamNum, bit bEnable)
{
    ScalerDpRxSetBaseInputPort_EXINT0(enumInputPort);

    if(GET_DP_MAC_DPHY_RX_ST_STATUS_BACKUP(enumDpStreamNum) != bEnable)
    {
        SET_DP_MAC_DPHY_RX_ST_STATUS_BACKUP(enumDpStreamNum, bEnable);

        if(ScalerDpMacRxGetPowerCutFlagStatus_EXINT0(enumInputPort) == _FALSE)
        {
            SET_DP_MAC_DPHY_RX_REG_ST_STATUS_EXINT(enumDpStreamNum, bEnable);
        }
        else
        {
            SET_DP_MAC_DPHY_RX_ST_POSITION_CHANGE();
        }
    }
}

//--------------------------------------------------
// Description  : Reset ST1 ~ ST6 Source Mux Backup
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxResetSourceMuxBackup_EXINT0(EnumInputPort enumInputPort)
{
    EnumDpStreamSourceNum enumSourceNum = _DP_ST_SOURCE1;

    for(enumSourceNum = _DP_ST_SOURCE1; enumSourceNum <= _DP_ST_SOURCE_END; enumSourceNum++)
    {
        ScalerDpMacDphyRxSetSourceMuxBackup_EXINT0(enumInputPort, enumSourceNum, _DP_ST_NONE);
    }
}

//--------------------------------------------------
// Description  : Reset ST1 ~ ST6 Start Backup
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxResetStreamStartBackup_EXINT0(EnumInputPort enumInputPort)
{
    EnumDpStreamNum enumDpStreamNum = _DP_ST_1;

    for(enumDpStreamNum = _DP_ST_1; enumDpStreamNum <= _DP_ST_END; enumDpStreamNum++)
    {
        ScalerDpMacDphyRxSetStreamStartBackup_EXINT0(enumInputPort, enumDpStreamNum, 0x00);
    }
}

//--------------------------------------------------
// Description  : Reset ST1 ~ ST6 End Backup
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxResetStreamEndBackup_EXINT0(EnumInputPort enumInputPort)
{
    EnumDpStreamNum enumDpStreamNum = _DP_ST_1;

    for(enumDpStreamNum = _DP_ST_1; enumDpStreamNum <= _DP_ST_END; enumDpStreamNum++)
    {
        ScalerDpMacDphyRxSetStreamEndBackup_EXINT0(enumInputPort, enumDpStreamNum, 0x00);
    }
}

//--------------------------------------------------
// Description  : Reset ST1 ~ ST6 Status Backup
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxResetStreamStatusBackup_EXINT0(EnumInputPort enumInputPort)
{
    EnumDpStreamNum enumDpStreamNum = _DP_ST_1;

    for(enumDpStreamNum = _DP_ST_1; enumDpStreamNum <= _DP_ST_END; enumDpStreamNum++)
    {
        ScalerDpMacDphyRxSetStreamStatusBackup_EXINT0(enumInputPort, enumDpStreamNum, _DISABLE);
    }
}

//--------------------------------------------------
// Description  : Get DP Mst Rx Stream Reg Address
// Input Value  : None
// Output Value : Word Mst Rx Stream Reg Address
//--------------------------------------------------
WORD ScalerDpMacDphyRxGetStreamRegAddress_EXINT0(EnumInputPort enumInputPort)
{
#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpAuxRxGetCodingType_EXINT0(enumInputPort) == _CODING_TYPE_128B132B)
    {
        return ScalerDpMacDphyRxGetPagedAddress_EXINT0(enumInputPort, P9D_02_STHD_CTRL_2);
    }
    else
#endif
    {
        return ScalerDpMacDphyRxGetPagedAddress_EXINT0(enumInputPort, PB5_02_STHD_CTRL_2);
    }
}

//--------------------------------------------------
// Description  : Get DP Mst Rx Source Reg Address
// Input Value  : None
// Output Value : Word Reg Address
//--------------------------------------------------
WORD ScalerDpMacDphyRxGetSourceRegAddress_EXINT0(EnumInputPort enumInputPort)
{
#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpAuxRxGetCodingType_EXINT0(enumInputPort) == _CODING_TYPE_128B132B)
    {
        return ScalerDpMacDphyRxGetPagedAddress_EXINT0(enumInputPort, P9D_12_SOURCE_SEL_0);
    }
    else
#endif
    {
        return ScalerDpMacDphyRxGetPagedAddress_EXINT0(enumInputPort, PB5_12_SOURCE_SEL_0);
    }
}

//--------------------------------------------------
// Description  : Get DP Mst Rx Load Stream Payload Reg Address
// Input Value  : None
// Output Value : Word Reg Address
//--------------------------------------------------
WORD ScalerDpMacDphyRxGetLoadStreamPayloadRegAddress_EXINT0(EnumInputPort enumInputPort)
{
#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpAuxRxGetCodingType_EXINT0(enumInputPort) == _CODING_TYPE_128B132B)
    {
        return ScalerDpMacDphyRxGetPagedAddress_EXINT0(enumInputPort, P9D_01_STHD_CTRL_1);
    }
    else
#endif
    {
        return ScalerDpMacDphyRxGetPagedAddress_EXINT0(enumInputPort, PB5_01_STHD_CTRL_1);
    }
}

//--------------------------------------------------
// Description  : Set DP Mst Rx Stream Status
// Input Value  : BYTE Stream x
// Output Value : bit Enable or Disable
//--------------------------------------------------
void ScalerDpMacDphyRxSetStreamStatusReg_EXINT0(EnumInputPort enumInputPort, EnumDpStreamNum enumDpStreamNum, bit bEn)
{
    enumInputPort = enumInputPort;
    enumDpStreamNum = enumDpStreamNum;
    bEn = bEn;

    // 8b10b: start position = 0 -> disable, != 0 -> enable, 128b132b: bit7 indicate status
#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
    ScalerDpRxSetBaseInputPort_EXINT0(enumInputPort);

    if(ScalerDpAuxRxGetCodingType_EXINT0(enumInputPort) == _CODING_TYPE_128B132B)
    {
        ScalerSetBit_EXINT((GET_DP_MAC_DPHY_RX_REG_ST_START_ADDR_EXINT() + (enumDpStreamNum << 1)), ~_BIT7, bEn << 7);
    }
#endif
}

//--------------------------------------------------
// Description  : DP MST Set St_source Mux Register
// Input Value  : enumSourceNum, ucValue
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxSetSourceMuxReg_EXINT0(EnumInputPort enumInputPort, EnumDpStreamSourceNum enumSourceNum, EnumDpStreamNum enumDpStreamNum)
{
#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpAuxRxGetCodingType_EXINT0(enumInputPort) == _CODING_TYPE_128B132B)
    {
        ScalerDpMacDphyRxSetSourceMuxReg_128b132b_EXINT0(enumInputPort, enumSourceNum, enumDpStreamNum);
    }
    else
#endif
    {
#if(_DP_MST_SUPPORT == _ON)
        ScalerDpMacDphyRxSetSourceMuxReg_8b10b_EXINT0(enumInputPort, enumSourceNum, enumDpStreamNum);
#endif
    }
}

//--------------------------------------------------
// Description  : Backup ST1_Source ~ ST6_Source Clear
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxResetSourceMuxReg_EXINT0(EnumInputPort enumInputPort)
{
#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
    ScalerDpMacDphyRxResetSourceMuxReg_128b132b_EXINT0(enumInputPort);
#endif

#if(_DP_MST_SUPPORT == _ON)
    ScalerDpMacDphyRxResetSourceMuxReg_8b10b_EXINT0(enumInputPort);
#endif
}

//--------------------------------------------------
// Description  : DP Mst Rx Load New Stream PayLoad EXINT0
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxLoadNewStreamPayload_EXINT0(EnumInputPort enumInputPort)
{
#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpAuxRxGetCodingType_EXINT0(enumInputPort) == _CODING_TYPE_128B132B)
    {
        ScalerDpMacDphyRxLoadNewStreamPayload_128b132b_EXINT0(enumInputPort);
    }
    else
#endif
    {
#if(_DP_MST_SUPPORT == _ON)
        ScalerDpMacDphyRxLoadNewStreamPayload_8b10b_EXINT0(enumInputPort);
#endif
    }
}
#endif

//--------------------------------------------------
// Description  : DP Mst Mode Config
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxConfigMstOrSstMode_EXINT0(EnumInputPort enumInputPort)
{
    switch(ScalerDpRxGetMacDphySwitch_EXINT0(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

            ScalerDpMacDphyRx0ConfigMstOrSstMode_EXINT0();

            break;
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            ScalerDpMacDphyRx1ConfigMstOrSstMode_EXINT0();

            break;
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            ScalerDpMacDphyRx2ConfigMstOrSstMode_EXINT0();

            break;
#endif

#if(_DUAL_DP_SUPPORT == _ON)
        case _DP_MAC_DPHY_DUAL:

#if(_DUAL_DP_MAC_DPHY_USE == _DUAL_DP_MAC_DPHY_RX0RX1)
            ScalerDpMacDphyRx0ConfigMstOrSstMode_EXINT0();
            ScalerDpMacDphyRx1ConfigMstOrSstMode_EXINT0();
#elif(_DUAL_DP_MAC_DPHY_USE == _DUAL_DP_MAC_DPHY_RX1RX2)
            ScalerDpMacDphyRx1ConfigMstOrSstMode_EXINT0();
            ScalerDpMacDphyRx2ConfigMstOrSstMode_EXINT0();
#endif

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Get Mst protocol(MTP or SST format) Status of inputport
// Input Value  : void
// Output Value : _ENABLE or _DISABLE
//--------------------------------------------------
bit ScalerDpMacDphyRxGetMstProtocolEnable_EXINT0(EnumInputPort enumInputPort)
{
    if(enumInputPort == _NO_INPUT_PORT)
    {
        return _DISABLE;
    }


#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpAuxRxGetCodingType_EXINT0(enumInputPort) == _CODING_TYPE_128B132B)
    {
        return _ENABLE;
    }
    else
#endif
    {
        if(ScalerDpAuxRxGetDpcdBitInfo_EXINT0(enumInputPort, 0x00, 0x01, 0x11, _BIT0) == _BIT0)
        {
            return _ENABLE;
        }
        else
        {
            return _DISABLE;
        }
    }
}

//-----------------------------------------------------------------------
// Description  : Set DP PHY to MAC Lane Swap / PN Swap / Clock Selection
// Input Value  : None
// Output Value : None
//-----------------------------------------------------------------------
void ScalerDpMacDphyRxLaneSwapSelect_EXINT0(EnumInputPort enumInputPort, BYTE ucClockLaneSelect)
{
    switch(ScalerDpRxGetMacDphySwitch_EXINT0(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

            ScalerDpMacDphyRx0LaneSwapSelect_EXINT0(enumInputPort, ucClockLaneSelect);

            break;
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            ScalerDpMacDphyRx1LaneSwapSelect_EXINT0(enumInputPort, ucClockLaneSelect);

            break;
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            ScalerDpMacDphyRx2LaneSwapSelect_EXINT0(enumInputPort, ucClockLaneSelect);

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
void ScalerDpMacDphyRxLaneCountSet_EXINT0(EnumInputPort enumInputPort, BYTE ucDpLaneCount)
{
    switch(ScalerDpRxGetMacDphySwitch_EXINT0(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

            ScalerDpMacDphyRx0LaneCountSet_EXINT0(ucDpLaneCount);

            break;
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            ScalerDpMacDphyRx1LaneCountSet_EXINT0(ucDpLaneCount);

            break;
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            ScalerDpMacDphyRx2LaneCountSet_EXINT0(ucDpLaneCount);

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
void ScalerDpMacDphyRxSetCommaDetect_EXINT0(EnumInputPort enumInputPort, bit bEn)
{
    switch(ScalerDpRxGetMacDphySwitch_EXINT0(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

            ScalerDpMacDphyRx0SetCommaDetect_EXINT0(bEn);

            break;
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            ScalerDpMacDphyRx1SetCommaDetect_EXINT0(bEn);

            break;
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            ScalerDpMacDphyRx2SetCommaDetect_EXINT0(bEn);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Set DP MAC Clock Selection
// Input Value  : Link Clock or XTAL Clock
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxClkSelect_EXINT0(EnumInputPort enumInputPort, EnumDpMacClkSelect enumClkSelect)
{
    switch(ScalerDpRxGetMacDphySwitch_EXINT0(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

            ScalerDpMacDphyRx0ClkSelect_EXINT0(enumClkSelect);

            break;
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            ScalerDpMacDphyRx1ClkSelect_EXINT0(enumClkSelect);

            break;
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            ScalerDpMacDphyRx2ClkSelect_EXINT0(enumClkSelect);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description : DP Signal Detection Measure
// Input Value  : DP Lane Select, Measure target, Measure Period
// Output Value : Measure Counter
//--------------------------------------------------
DWORD ScalerDpMacDphyRxSignalDetectMeasureCount_EXINT0(EnumInputPort enumInputPort, BYTE ucDpLaneSel, EnumDpMeasureTarget enumDpMeasureTarget, EnumDpMeasurePeriod enumDpMeasurePeriod)
{
    switch(ScalerDpRxGetMacDphySwitch_EXINT0(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

            return ScalerDpMacDphyRx0SignalDetectMeasureCount_EXINT0(ucDpLaneSel, enumDpMeasureTarget, enumDpMeasurePeriod);
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            return ScalerDpMacDphyRx1SignalDetectMeasureCount_EXINT0(ucDpLaneSel, enumDpMeasureTarget, enumDpMeasurePeriod);
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            return ScalerDpMacDphyRx2SignalDetectMeasureCount_EXINT0(ucDpLaneSel, enumDpMeasureTarget, enumDpMeasurePeriod);
#endif

        default:

            return 0x00000000;
    }
}

//--------------------------------------------------
// Description  : DP TP1 Decode Check
// Input Value  : DP Lane
// Output Value : TRUE/FALSE
//--------------------------------------------------
BYTE ScalerDpMacDphyRxTp1Detect_EXINT0(EnumInputPort enumInputPort, EnumDpLane enumDpLane)
{
    switch(ScalerDpRxGetMacDphySwitch_EXINT0(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

            return ScalerDpMacDphyRx0Tp1Detect_EXINT0(enumDpLane);
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            return ScalerDpMacDphyRx1Tp1Detect_EXINT0(enumDpLane);
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            return ScalerDpMacDphyRx2Tp1Detect_EXINT0(enumDpLane);
#endif

        default:

            return 0x00;
    }
}

//--------------------------------------------------
// Description  : Check Dp Training Pattern 2 Decode
// Input Value  : DP Lane
// Output Value : TRUE --> TP2 Decode Check Pass
//--------------------------------------------------
BYTE ScalerDpMacDphyRxTp1DecodeCheck_EXINT0(EnumInputPort enumInputPort, BYTE ucDpLane)
{
    switch(ScalerDpRxGetMacDphySwitch_EXINT0(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

            return ScalerDpMacDphyRx0Tp1DecodeCheck_EXINT0(ucDpLane);
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            return ScalerDpMacDphyRx1Tp1DecodeCheck_EXINT0(ucDpLane);
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            return ScalerDpMacDphyRx2Tp1DecodeCheck_EXINT0(ucDpLane);
#endif

        default:

            return _FALSE;
    }
}

//--------------------------------------------------
// Description  : DP TP2 Decode Check
// Input Value  : Link Rate, DP Lane
// Output Value : TRUE/FALSE
//--------------------------------------------------
BYTE ScalerDpMacDphyRxTp2DecodeCheck_EXINT0(EnumInputPort enumInputPort, EnumDpLane enumDpLane)
{
    switch(ScalerDpRxGetMacDphySwitch_EXINT0(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

            return ScalerDpMacDphyRx0Tp2DecodeCheck_EXINT0(enumDpLane);
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            return ScalerDpMacDphyRx1Tp2DecodeCheck_EXINT0(enumDpLane);
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            return ScalerDpMacDphyRx2Tp2DecodeCheck_EXINT0(enumDpLane);
#endif

        default:

            return 0x00;
    }
}

//--------------------------------------------------
// Description  : Check Dp Training Pattern 2 Decode
// Input Value  : DP Lane
// Output Value : TRUE --> TP3 Decode Check Pass
//--------------------------------------------------
BYTE ScalerDpMacDphyRxTp3DecodeCheck_EXINT0(EnumInputPort enumInputPort, EnumDpLane enumDpLane)
{
    enumDpLane = enumDpLane;

    switch(ScalerDpRxGetMacDphySwitch_EXINT0(enumInputPort))
    {
#if((_DP_MAC_DPHY_RX0_SUPPORT == _ON) && (_DP_MAC_RX0_128B132B_CODING_TYPE_SUPPORT == _ON))
        case _DP_MAC_DPHY_RX0:

            return ScalerDpMacDphyRx0Tp3DecodeCheck_EXINT0(enumDpLane);
#endif

#if((_DP_MAC_DPHY_RX1_SUPPORT == _ON) && (_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON))
        case _DP_MAC_DPHY_RX1:

            return ScalerDpMacDphyRx1Tp3DecodeCheck_EXINT0(enumDpLane);
#endif

#if((_DP_MAC_DPHY_RX2_SUPPORT == _ON) && (_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON))
        case _DP_MAC_DPHY_RX2:

            return ScalerDpMacDphyRx2Tp3DecodeCheck_EXINT0(enumDpLane);
#endif

        default:

            return 0x00;
    }
}

//--------------------------------------------------
// Description  : DP MAC Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxReset_EXINT0(EnumInputPort enumInputPort)
{
    switch(ScalerDpRxGetMacDphySwitch_EXINT0(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

            ScalerDpMacDphyRx0Reset_EXINT0();

            break;
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            ScalerDpMacDphyRx1Reset_EXINT0();

            break;
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            ScalerDpMacDphyRx2Reset_EXINT0();

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : DP Channel Fifo Reset
// Input Value  : Input Port
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxChannelFifoReset_EXINT0(EnumInputPort enumInputPort)
{
    switch(ScalerDpRxGetMacDphySwitch_EXINT0(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

            ScalerDpMacDphyRx0ChannelFifoReset_EXINT0();

            break;
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            ScalerDpMacDphyRx1ChannelFifoReset_EXINT0();

            break;
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            ScalerDpMacDphyRx2ChannelFifoReset_EXINT0();

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : DP De-Skew Circuit Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxDeSkewReset_EXINT0(EnumInputPort enumInputPort)
{
    switch(ScalerDpRxGetMacDphySwitch_EXINT0(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

            ScalerDpMacDphyRx0DeSkewReset_EXINT0();

            break;
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            ScalerDpMacDphyRx1DeSkewReset_EXINT0();

            break;
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            ScalerDpMacDphyRx2DeSkewReset_EXINT0();

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : DP De-Skew Circuit Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxEnhancementControlMode_EXINT0(EnumInputPort enumInputPort, bit bEn)
{
    switch(ScalerDpRxGetMacDphySwitch_EXINT0(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

            ScalerDpMacDphyRx0EnhancementControlMode_EXINT0(bEn);

            break;
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            ScalerDpMacDphyRx1EnhancementControlMode_EXINT0(bEn);

            break;
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            ScalerDpMacDphyRx2EnhancementControlMode_EXINT0(bEn);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : DP De-Skew Circuit Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxScramble_EXINT0(EnumInputPort enumInputPort, bit bEn)
{
    switch(ScalerDpRxGetMacDphySwitch_EXINT0(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

            ScalerDpMacDphyRx0Scramble_EXINT0(bEn);

            break;
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            ScalerDpMacDphyRx1Scramble_EXINT0(bEn);

            break;
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            ScalerDpMacDphyRx2Scramble_EXINT0(bEn);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : DP Mac Reset Proc
// Input Value  : Dx Port
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxMacResetProc_EXINT0(EnumInputPort enumInputPort)
{
    switch(ScalerDpRxGetMacDphySwitch_EXINT0(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

            ScalerDpMacDphyRx0MacResetProc_EXINT0();

            break;
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            ScalerDpMacDphyRx1MacResetProc_EXINT0();

            break;
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            ScalerDpMacDphyRx2MacResetProc_EXINT0();

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
void ScalerDpMacDphyRxSetHdcpMode_EXINT0(EnumInputPort enumInputPort, EnumHDCPType enumHdcpType)
{
    switch(ScalerDpRxGetMacDphySwitch_EXINT0(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

            // Enable HDCP MAC0
            ScalerDpMacDphyRx0SetHdcpMode_EXINT0(enumHdcpType);

            break;
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            // Enable HDCP MAC1
            ScalerDpMacDphyRx1SetHdcpMode_EXINT0(enumHdcpType);

            break;
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            // Enable HDCP MAC2
            ScalerDpMacDphyRx2SetHdcpMode_EXINT0(enumHdcpType);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Clear Integrity Failure Flag
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxClearIntegrityFailureFlag_EXINT0(EnumInputPort enumInputPort)
{
    switch(ScalerDpRxGetMacDphySwitch_EXINT0(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:
#if(_DP_MAC_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
            {
                ScalerSetBit_EXINT(PC_02_HDCP_INTGT_VRF, ~_BIT7, 0x00);
                ScalerSetBit_EXINT(PC_02_HDCP_INTGT_VRF, ~_BIT7, _BIT7);
            }
            else
#endif
            {
                ScalerSetBit_EXINT(PB_1B_HDCP_INTGT_VRF, ~_BIT7, 0x00);
                ScalerSetBit_EXINT(PB_1B_HDCP_INTGT_VRF, ~_BIT7, _BIT7);
            }

            break;
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
            {
                ScalerSetBit_EXINT(P1F_02_HDCP_INTGT_VRF, ~_BIT7, 0x00);
                ScalerSetBit_EXINT(P1F_02_HDCP_INTGT_VRF, ~_BIT7, _BIT7);
            }
            else
#endif
            {
                ScalerSetBit_EXINT(PB0_1B_HDCP_INTGT_VRF, ~_BIT7, 0x00);
                ScalerSetBit_EXINT(PB0_1B_HDCP_INTGT_VRF, ~_BIT7, _BIT7);
            }

            break;
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:
#if(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
            {
                ScalerSetBit_EXINT(PD2_02_HDCP_INTGT_VRF, ~_BIT7, 0x00);
                ScalerSetBit_EXINT(PD2_02_HDCP_INTGT_VRF, ~_BIT7, _BIT7);
            }
            else
#endif
            {
                ScalerSetBit_EXINT(PC5_1B_HDCP_INTGT_VRF, ~_BIT7, 0x00);
                ScalerSetBit_EXINT(PC5_1B_HDCP_INTGT_VRF, ~_BIT7, _BIT7);
            }

            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Calculate R0' by manual toggle HDCP 1.4 Module
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxSetHdcp14CalR0_EXINT0(EnumInputPort enumInputPort)
{
    switch(ScalerDpRxGetMacDphySwitch_EXINT0(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

            ScalerSetBit_EXINT(PB_63_HDCP_OTHER, ~_BIT7, _BIT7);
            ScalerSetBit_EXINT(PB_63_HDCP_OTHER, ~_BIT7, 0x00);

            // Delay Time us [200,x] Waiting for R0 Calculate Finish
            DELAY_XUS_EXINT(200);

            break;
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            ScalerSetBit_EXINT(PB0_63_HDCP_OTHER, ~_BIT7, _BIT7);
            ScalerSetBit_EXINT(PB0_63_HDCP_OTHER, ~_BIT7, 0x00);

            // Delay Time us [200,x] Waiting for R0 Calculate Finish
            DELAY_XUS_EXINT(200);

            break;
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            ScalerSetBit_EXINT(PC5_63_HDCP_OTHER, ~_BIT7, _BIT7);
            ScalerSetBit_EXINT(PC5_63_HDCP_OTHER, ~_BIT7, 0x00);

            // Delay Time us [200,x] Waiting for R0 Calculate Finish
            DELAY_XUS_EXINT(200);

            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Set HDCP An, Aksv, Repeater by FW
// Input Value  : Dx Port
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxSetHdcp14Info_EXINT0(EnumInputPort enumInputPort)
{
    switch(ScalerDpRxGetMacDphySwitch_EXINT0(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

            ScalerDpMacDphyRx0SetHdcp14Info_EXINT0();

            break;
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            ScalerDpMacDphyRx1SetHdcp14Info_EXINT0();

            break;
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            ScalerDpMacDphyRx2SetHdcp14Info_EXINT0();

            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Get Hdcp14 R0 to DPCD Table
// Input Value  : Dx Port, Hdcp14 R0 Type
// Output Value : None
//--------------------------------------------------
BYTE ScalerDpMacDphyRxGetHdcp14R0_EXINT0(EnumInputPort enumInputPort, EnumDpHdcp14R0Type enumDpHdcp14R0Type)
{
    switch(ScalerDpRxGetMacDphySwitch_EXINT0(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

            return ScalerDpMacDphyRx0GetHdcp14R0_EXINT0(enumDpHdcp14R0Type);
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            return ScalerDpMacDphyRx1GetHdcp14R0_EXINT0(enumDpHdcp14R0Type);
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            return ScalerDpMacDphyRx2GetHdcp14R0_EXINT0(enumDpHdcp14R0Type);
#endif
        default:

            break;
    }
    return 0x00;
}

//--------------------------------------------------
// Description  : Recover Data from Power Cut State
// Input Value  : None
// Output Value : None
//-------------------------------------------------
void ScalerDpMacDphyRxPowerDataRecover_EXINT0(EnumInputPort enumInputPort)
{
    switch(ScalerDpRxGetMacDphySwitch_EXINT0(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

            ScalerDpMacDphyRx0PowerDataRecover_EXINT0();

            break;
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            ScalerDpMacDphyRx1PowerDataRecover_EXINT0();

            break;
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            ScalerDpMacDphyRx2PowerDataRecover_EXINT0();

            break;
#endif
        default:

            break;
    }
}

#if(_HW_DP_MAC_POWER_CUT_GEN == _DP_MAC_POWER_CUT_SEPARATE)
//--------------------------------------------------
// Description  : Get DP Mac RX Power Cut Status
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpMacDphyRxGetPowerCutCurrentStatus_EXINT0(EnumInputPort enumInputPort)
{
    EnumDpMacDphySel enumDpMacDphySel = ScalerDpRxGetMacDphySwitch_EXINT0(enumInputPort);

    switch(enumDpMacDphySel)
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

            return ScalerPowerGroupGetPowerCutStatus(_POWER_CUT_GROUP_RX0_DP14_DPHY);
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            return ScalerPowerGroupGetPowerCutStatus(_POWER_CUT_GROUP_RX1_DP14_DPHY);
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            return ScalerPowerGroupGetPowerCutStatus(_POWER_CUT_GROUP_RX2_DP14_DPHY);
#endif

        default:
            break;
    }

    return _POWER_CUT_ON;
}

//--------------------------------------------------
// Description  : DP MAC power process
// Input Value  : EnumInputPort, EnumPowerAction
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxPowerProc_EXINT0(EnumInputPort enumInputPort, EnumPowerAction enumPowerAction)
{
    EnumDpMacDphySel enumDpMacDphySel = ScalerDpRxGetMacDphySwitch_EXINT0(enumInputPort);

    switch(enumDpMacDphySel)
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

            ScalerDpMacDphyRx0PowerProc_EXINT0(enumPowerAction);

            break;
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            ScalerDpMacDphyRx1PowerProc_EXINT0(enumPowerAction);

            break;
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            ScalerDpMacDphyRx2PowerProc_EXINT0(enumPowerAction);

            break;
#endif

        default:

            break;
    }
}
#endif

//--------------------------------------------------
// Description  : Reset 8b10b Error Count value
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxDecodeErrorCountReset_EXINT0(EnumInputPort enumInputPort, EnumDpMacDecodeMethod enumDpMacDecodeMethod)
{
    switch(ScalerDpRxGetMacDphySwitch_EXINT0(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

            ScalerDpMacDphyRx0DecodeErrorCountReset_EXINT0(enumDpMacDecodeMethod);

            break;
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            ScalerDpMacDphyRx1DecodeErrorCountReset_EXINT0(enumDpMacDecodeMethod);

            break;
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            ScalerDpMacDphyRx2DecodeErrorCountReset_EXINT0(enumDpMacDecodeMethod);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Disable 8b10b Error Count value
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxDecodeErrorCountOff_EXINT0(EnumInputPort enumInputPort)
{
    switch(ScalerDpRxGetMacDphySwitch_EXINT0(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

            ScalerDpMacDphyRx0DecodeErrorCountOff_EXINT0();

            break;
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            ScalerDpMacDphyRx1DecodeErrorCountOff_EXINT0();

            break;
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            ScalerDpMacDphyRx2DecodeErrorCountOff_EXINT0();

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Disable 8b10b Error Count value
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxErrorCounterUpdate_EXINT0(EnumInputPort enumInputPort)
{
    switch(ScalerDpRxGetMacDphySwitch_EXINT0(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

            ScalerDpMacDphyRx0ErrorCounterUpdate_EXINT0();

            break;
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            ScalerDpMacDphyRx1ErrorCounterUpdate_EXINT0();

            break;
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            ScalerDpMacDphyRx2ErrorCounterUpdate_EXINT0();

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Update 8b10b Error Count value
// Input Value  : InputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxPhyCtsErrorCounterUpdate_EXINT0(EnumInputPort enumInputPort)
{
    switch(ScalerDpRxGetMacDphySwitch_EXINT0(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

            ScalerDpMacDphyRx0PhyCtsErrorCounterUpdate_EXINT0();

            break;
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            ScalerDpMacDphyRx1PhyCtsErrorCounterUpdate_EXINT0();

            break;
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            ScalerDpMacDphyRx2PhyCtsErrorCounterUpdate_EXINT0();

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
WORD ScalerDpMacDphyRxGetPagedAddress_EXINT0(EnumInputPort enumInputPort, WORD usMac0Addr)
{
    EnumDpMacDphySel enumDpMacDphy = ScalerDpRxGetMacDphySwitch_EXINT0(enumInputPort);
    WORD usBasePage = usMac0Addr >> 8;

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

#if(_DP_HDCP2_RX_SUPPORT == _ON)
//--------------------------------------------------
// Description  : HDCP 2.2 Reset Proc for MAC RX
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxHdcp2ResetProc_EXINT0(EnumInputPort enumInputPort)
{
    switch(ScalerDpRxGetMacDphySwitch_EXINT0(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

            ScalerDpMacDphyRx0Hdcp2ResetProc_EXINT0();

            break;
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            ScalerDpMacDphyRx1Hdcp2ResetProc_EXINT0();

            break;
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            ScalerDpMacDphyRx2Hdcp2ResetProc_EXINT0();

            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Enable HDCP 2.2 Link Integrity Check
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxHdcp2EnableLinkIntegrityCheck_EXINT0(bit bEnable, EnumInputPort enumInputPort)
{
    switch(ScalerDpRxGetMacDphySwitch_EXINT0(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

            ScalerDpMacDphyRx0Hdcp2EnableLinkIntegrityCheck_EXINT0(bEnable);

            break;
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            ScalerDpMacDphyRx1Hdcp2EnableLinkIntegrityCheck_EXINT0(bEnable);

            break;
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            ScalerDpMacDphyRx2Hdcp2EnableLinkIntegrityCheck_EXINT0(bEnable);

            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Enable HDCP 2.2 Auth Done
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxHdcp2EnableDecryption_EXINT0(EnumInputPort enumInputPort)
{
    switch(ScalerDpRxGetMacDphySwitch_EXINT0(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

            ScalerDpMacDphyRx0Hdcp2EnableDecryption_EXINT0();

            break;
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            ScalerDpMacDphyRx1Hdcp2EnableDecryption_EXINT0();

            break;
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            ScalerDpMacDphyRx2Hdcp2EnableDecryption_EXINT0();

            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Enable HDCP 2.2 Auth Done
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxHdcp2EnableAuthDone_EXINT0(bit bEnable, EnumInputPort enumInputPort)
{
    switch(ScalerDpRxGetMacDphySwitch_EXINT0(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

            ScalerDpMacDphyRx0Hdcp2EnableAuthDone_EXINT0(bEnable);

            break;
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            ScalerDpMacDphyRx1Hdcp2EnableAuthDone_EXINT0(bEnable);

            break;
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            ScalerDpMacDphyRx2Hdcp2EnableAuthDone_EXINT0(bEnable);

            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : HDCP 2.2 Set AES Type
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxHdcp2SetAESType_EXINT0(EnumInputPort enumInputPort)
{
    switch(ScalerDpRxGetMacDphySwitch_EXINT0(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

            ScalerDpMacDphyRx0Hdcp2SetAESType_EXINT0();

            break;
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            ScalerDpMacDphyRx1Hdcp2SetAESType_EXINT0();

            break;
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            ScalerDpMacDphyRx2Hdcp2SetAESType_EXINT0();

            break;
#endif
        default:

            break;
    }
}
#endif

#if(_DP_RX_FEC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : FEC Support
// Input Value  : Enable or Disable
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxFecDecode_EXINT0(EnumInputPort enumInputPort, BYTE ucFECDecode)
{
    switch(ScalerDpRxGetMacDphySwitch_EXINT0(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

            ScalerDpMacDphyRx0FecDecode_EXINT0(ucFECDecode);

            break;
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            ScalerDpMacDphyRx1FecDecode_EXINT0(ucFECDecode);

            break;
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            ScalerDpMacDphyRx2FecDecode_EXINT0(ucFECDecode);

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
BYTE ScalerDpMacDphyRxGetFecDecodeStatus_EXINT0(EnumInputPort enumInputPort)
{
    switch(ScalerDpRxGetMacDphySwitch_EXINT0(enumInputPort))
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
// Description  : FEC Error Count Select
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxFecErrorCountSelect_EXINT0(EnumInputPort enumInputPort, BYTE ucFECSelect)
{
    switch(ScalerDpRxGetMacDphySwitch_EXINT0(enumInputPort))
#if(_HW_DP_RX_FEC_ERROR_COUNT_SEL_DB_SUPPORT == _ON)
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:
            ScalerSetBit_EXINT(PB_D3_FEC_ERROR_DETECT, ~(_BIT6 | _BIT5 | _BIT4), ucFECSelect);
            // Enable err_cnt_sel Double Buffer
            ScalerSetBit_EXINT(PB_D7_FEC_ERROR_CNT_H, ~_BIT7, _BIT7);
#if(_DP_MAC_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
            ScalerSetBit_EXINT(PC_82_FEC_ERROR_DETECT, ~(_BIT6 | _BIT5 | _BIT4), ucFECSelect);
            ScalerSetBit_EXINT(PC_8B_FEC_MERGE_PARITY_ERROR_CNT_CTRL, ~(_BIT6 | _BIT0), _BIT6);
            // Enable err_cnt_sel Double Buffer
            ScalerSetBit_EXINT(PC_86_FEC_ERROR_CNT_H, ~_BIT7, _BIT7);
#endif
            break;
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            ScalerSetBit_EXINT(PB0_D3_FEC_ERROR_DETECT, ~(_BIT6 | _BIT5 | _BIT4), ucFECSelect);
            ScalerSetBit_EXINT(PB0_D7_FEC_ERROR_CNT_H, ~_BIT7, _BIT7);
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
            ScalerSetBit_EXINT(P1F_82_FEC_ERROR_DETECT, ~(_BIT6 | _BIT5 | _BIT4), ucFECSelect);
            ScalerSetBit_EXINT(P1F_8B_FEC_MERGE_PARITY_ERROR_CNT_CTRL, ~(_BIT6 | _BIT0), _BIT6);
            // Enable err_cnt_sel Double Buffer
            ScalerSetBit_EXINT(P1F_86_FEC_ERROR_CNT_H, ~_BIT7, _BIT7);
#endif
            break;
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            ScalerSetBit_EXINT(PC5_D3_FEC_ERROR_DETECT, ~(_BIT6 | _BIT5 | _BIT4), ucFECSelect);
            // Enable err_cnt_sel Double Buffer
            ScalerSetBit_EXINT(PC5_D7_FEC_ERROR_CNT_H, ~_BIT7, _BIT7);
#if(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
            ScalerSetBit_EXINT(PD2_82_FEC_ERROR_DETECT, ~(_BIT6 | _BIT5 | _BIT4), ucFECSelect);
            ScalerSetBit_EXINT(PD2_8B_FEC_MERGE_PARITY_ERROR_CNT_CTRL, ~(_BIT6 | _BIT0), _BIT6);
            // Enable err_cnt_sel Double Buffer
            ScalerSetBit_EXINT(PD2_86_FEC_ERROR_CNT_H, ~_BIT7, _BIT7);
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
            ScalerSetBit_EXINT(PB_D3_FEC_ERROR_DETECT, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5 | _BIT4));
            ScalerSetBit_EXINT(PB_D3_FEC_ERROR_DETECT, ~(_BIT6 | _BIT5 | _BIT4), ucFECSelect);
#if(_DP_MAC_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
            // Set err_cnt_sel = 3'b111 to avoid transient 0s
            ScalerSetBit_EXINT(PC_82_FEC_ERROR_DETECT, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5 | _BIT4));
            ScalerSetBit_EXINT(PC_82_FEC_ERROR_DETECT, ~(_BIT6 | _BIT5 | _BIT4), ucFECSelect);
            ScalerSetBit_EXINT(PC_8B_FEC_MERGE_PARITY_ERROR_CNT_CTRL, ~(_BIT6 | _BIT0), _BIT6);
#endif
            break;
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:
            // Set err_cnt_sel = 3'b111 to avoid transient 0s
            ScalerSetBit_EXINT(PB0_D3_FEC_ERROR_DETECT, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5 | _BIT4));
            ScalerSetBit_EXINT(PB0_D3_FEC_ERROR_DETECT, ~(_BIT6 | _BIT5 | _BIT4), ucFECSelect);
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
            // Set err_cnt_sel = 3'b111 to avoid transient 0s
            ScalerSetBit_EXINT(P1F_82_FEC_ERROR_DETECT, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5 | _BIT4));
            ScalerSetBit_EXINT(P1F_82_FEC_ERROR_DETECT, ~(_BIT6 | _BIT5 | _BIT4), ucFECSelect);
            ScalerSetBit_EXINT(P1F_8B_FEC_MERGE_PARITY_ERROR_CNT_CTRL, ~(_BIT6 | _BIT0), _BIT6);
#endif
            break;
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:
            // Set err_cnt_sel = 3'b111 to avoid transient 0s
            ScalerSetBit_EXINT(PC5_D3_FEC_ERROR_DETECT, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5 | _BIT4));
            ScalerSetBit_EXINT(PC5_D3_FEC_ERROR_DETECT, ~(_BIT6 | _BIT5 | _BIT4), ucFECSelect);
#if(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
            // Set err_cnt_sel = 3'b111 to avoid transient 0s
            ScalerSetBit_EXINT(PD2_82_FEC_ERROR_DETECT, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5 | _BIT4));
            ScalerSetBit_EXINT(PD2_82_FEC_ERROR_DETECT, ~(_BIT6 | _BIT5 | _BIT4), ucFECSelect);
            ScalerSetBit_EXINT(PD2_8B_FEC_MERGE_PARITY_ERROR_CNT_CTRL, ~(_BIT6 | _BIT0), _BIT6);
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
void ScalerDpMacDphyRxFecLaneSelect_EXINT0(EnumInputPort enumInputPort, BYTE ucFECLane)
{
    switch(ScalerDpRxGetMacDphySwitch_EXINT0(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

            ScalerSetBit_EXINT(PB_D3_FEC_ERROR_DETECT, ~(_BIT3 | _BIT2), ucFECLane);
#if(_DP_MAC_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
            ScalerSetBit_EXINT(PC_82_FEC_ERROR_DETECT, ~(_BIT3 | _BIT2), ucFECLane);
#endif
            break;
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            ScalerSetBit_EXINT(PB0_D3_FEC_ERROR_DETECT, ~(_BIT3 | _BIT2), ucFECLane);
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
            ScalerSetBit_EXINT(P1F_82_FEC_ERROR_DETECT, ~(_BIT3 | _BIT2), ucFECLane);
#endif
            break;
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            ScalerSetBit_EXINT(PC5_D3_FEC_ERROR_DETECT, ~(_BIT3 | _BIT2), ucFECLane);
#if(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
            ScalerSetBit_EXINT(PD2_82_FEC_ERROR_DETECT, ~(_BIT3 | _BIT2), ucFECLane);
#endif
            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Get FEC Error Count
// Input Value  : None
// Output Value : Error Count Low Byte
//--------------------------------------------------
BYTE ScalerDpMacDphyRxFecErrorCountUpdateLowByte_EXINT0(EnumInputPort enumInputPort)
{
    switch(ScalerDpRxGetMacDphySwitch_EXINT0(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

#if(_DP_MAC_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(ScalerDpAuxRxGetCodingType_EXINT0(enumInputPort) == _CODING_TYPE_128B132B)
            {
                return ScalerGetByte_EXINT(PC_87_FEC_ERROR_CNT_L);
            }
            else
#endif
            {
                return ScalerGetByte_EXINT(PB_D8_FEC_ERROR_CNT_L);
            }
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(ScalerDpAuxRxGetCodingType_EXINT0(enumInputPort) == _CODING_TYPE_128B132B)
            {
                return ScalerGetByte_EXINT(P1F_87_FEC_ERROR_CNT_L);
            }
            else
#endif
            {
                return ScalerGetByte_EXINT(PB0_D8_FEC_ERROR_CNT_L);
            }
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

#if(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(ScalerDpAuxRxGetCodingType_EXINT0(enumInputPort) == _CODING_TYPE_128B132B)
            {
                return ScalerGetByte_EXINT(PD2_87_FEC_ERROR_CNT_L);
            }
            else
#endif
            {
                return ScalerGetByte_EXINT(PC5_D8_FEC_ERROR_CNT_L);
            }
#endif
        default:

            return 0x00;
    }
}

//--------------------------------------------------
// Description  : Get FEC Error Count
// Input Value  : None
// Output Value : Error Count Low Byte
//--------------------------------------------------
BYTE ScalerDpMacDphyRxFecErrorCountUpdateHighByte_EXINT0(EnumInputPort enumInputPort)
{
    switch(ScalerDpRxGetMacDphySwitch_EXINT0(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

#if(_DP_MAC_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(ScalerDpAuxRxGetCodingType_EXINT0(enumInputPort) == _CODING_TYPE_128B132B)
            {
                return ScalerGetByte_EXINT(PC_86_FEC_ERROR_CNT_H);
            }
            else
#endif
            {
                return ScalerGetByte_EXINT(PB_D7_FEC_ERROR_CNT_H);
            }
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(ScalerDpAuxRxGetCodingType_EXINT0(enumInputPort) == _CODING_TYPE_128B132B)
            {
                return ScalerGetByte_EXINT(P1F_86_FEC_ERROR_CNT_H);
            }
            else
#endif
            {
                return ScalerGetByte_EXINT(PB0_D7_FEC_ERROR_CNT_H);
            }
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

#if(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(ScalerDpAuxRxGetCodingType_EXINT0(enumInputPort) == _CODING_TYPE_128B132B)
            {
                return ScalerGetByte_EXINT(PD2_86_FEC_ERROR_CNT_H);
            }
            else
#endif
            {
                return ScalerGetByte_EXINT(PC5_D7_FEC_ERROR_CNT_H);
            }
#endif

        default:

            return 0x00;
    }
}

//--------------------------------------------------
// Description  : Reset FEC Error Count
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxResetFecErrorCount_EXINT0(EnumInputPort enumInputPort)
{
    switch(ScalerDpRxGetMacDphySwitch_EXINT0(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:
            ScalerSetBit_EXINT(PB_D3_FEC_ERROR_DETECT, ~_BIT1, _BIT1);
            ScalerSetBit_EXINT(PB_D3_FEC_ERROR_DETECT, ~_BIT1, 0x00);
#if(_DP_MAC_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
            ScalerSetBit_EXINT(PC_82_FEC_ERROR_DETECT, ~_BIT1, _BIT1);
            ScalerSetBit_EXINT(PC_82_FEC_ERROR_DETECT, ~_BIT1, 0x00);
#endif
            break;
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            ScalerSetBit_EXINT(PB0_D3_FEC_ERROR_DETECT, ~_BIT1, _BIT1);
            ScalerSetBit_EXINT(PB0_D3_FEC_ERROR_DETECT, ~_BIT1, 0x00);
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
            ScalerSetBit_EXINT(P1F_82_FEC_ERROR_DETECT, ~_BIT1, _BIT1);
            ScalerSetBit_EXINT(P1F_82_FEC_ERROR_DETECT, ~_BIT1, 0x00);
#endif
            break;
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            ScalerSetBit_EXINT(PC5_D3_FEC_ERROR_DETECT, ~_BIT1, _BIT1);
            ScalerSetBit_EXINT(PC5_D3_FEC_ERROR_DETECT, ~_BIT1, 0x00);
#if(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
            ScalerSetBit_EXINT(PD2_82_FEC_ERROR_DETECT, ~_BIT1, _BIT1);
            ScalerSetBit_EXINT(PD2_82_FEC_ERROR_DETECT, ~_BIT1, 0x00);
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
void ScalerDpMacDphyRxClearFecErrorCount_EXINT0(EnumInputPort enumInputPort)
{
#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
    if(enumInputPort == _D9_INPUT_PORT)
    {
        enumInputPort = GET_DP_MST_RX_PXP_INPUT_PORT();
    }
#endif

    switch(ScalerDpRxGetMacDphySwitch_EXINT0(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:
#if(_DP_MAC_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(ScalerDpAuxRxGetCodingType_EXINT0(enumInputPort) == _CODING_TYPE_128B132B)
            {
                ScalerSetBit_EXINT(PC_82_FEC_ERROR_DETECT, ~_BIT1, _BIT1);
                ScalerSetBit_EXINT(PC_82_FEC_ERROR_DETECT, ~_BIT1, 0x00);
            }
            else
#endif
            {
                ScalerSetBit_EXINT(PB_D3_FEC_ERROR_DETECT, ~_BIT1, _BIT1);
                ScalerSetBit_EXINT(PB_D3_FEC_ERROR_DETECT, ~_BIT1, 0x00);
            }

            break;
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(ScalerDpAuxRxGetCodingType_EXINT0(enumInputPort) == _CODING_TYPE_128B132B)
            {
                ScalerSetBit_EXINT(P1F_82_FEC_ERROR_DETECT, ~_BIT1, _BIT1);
                ScalerSetBit_EXINT(P1F_82_FEC_ERROR_DETECT, ~_BIT1, 0x00);
            }
            else
#endif
            {
                ScalerSetBit_EXINT(PB0_D3_FEC_ERROR_DETECT, ~_BIT1, _BIT1);
                ScalerSetBit_EXINT(PB0_D3_FEC_ERROR_DETECT, ~_BIT1, 0x00);
            }

            break;
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:
#if(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(ScalerDpAuxRxGetCodingType_EXINT0(enumInputPort) == _CODING_TYPE_128B132B)
            {
                ScalerSetBit_EXINT(PD2_82_FEC_ERROR_DETECT, ~_BIT1, _BIT1);
                ScalerSetBit_EXINT(PD2_82_FEC_ERROR_DETECT, ~_BIT1, 0x00);
            }
            else
#endif
            {
                ScalerSetBit_EXINT(PC5_D3_FEC_ERROR_DETECT, ~_BIT1, _BIT1);
                ScalerSetBit_EXINT(PC5_D3_FEC_ERROR_DETECT, ~_BIT1, 0x00);
            }

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
void ScalerDpMacDphyRxFecEnableAggregatedErrorCount_EXINT0(EnumInputPort enumInputPort, bit bEnable)
{
    EnumDpMacDphySel enumDpMacDphySel = _DP_MAC_DPHY_NONE;

#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
    if(enumInputPort == _D9_INPUT_PORT)
    {
        enumInputPort = GET_DP_MST_RX_PXP_INPUT_PORT();
    }
#endif

    enumDpMacDphySel = ScalerDpRxGetMacDphySwitch_EXINT0(enumInputPort);

    if(bEnable == _ENABLE)
    {
        switch(enumDpMacDphySel)
        {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
            case _DP_MAC_DPHY_RX0:
#if(_DP_MAC_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
                ScalerSetBit_EXINT(PC_8B_FEC_MERGE_PARITY_ERROR_CNT_CTRL, ~(_BIT5 | _BIT0), _BIT5);
#endif
                ScalerSetBit_EXINT(PB_D3_FEC_ERROR_DETECT, ~_BIT0, _BIT0);
                break;
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
            case _DP_MAC_DPHY_RX1:
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
                ScalerSetBit_EXINT(P1F_8B_FEC_MERGE_PARITY_ERROR_CNT_CTRL, ~(_BIT5 | _BIT0), _BIT5);
#endif
                ScalerSetBit_EXINT(PB0_D3_FEC_ERROR_DETECT, ~_BIT0, _BIT0);
                break;
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
            case _DP_MAC_DPHY_RX2:
#if(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
                ScalerSetBit_EXINT(PD2_8B_FEC_MERGE_PARITY_ERROR_CNT_CTRL, ~(_BIT5 | _BIT0), _BIT5);
#endif
                ScalerSetBit_EXINT(PC5_D3_FEC_ERROR_DETECT, ~_BIT0, _BIT0);
                break;
#endif

            default:
                break;
        }
    }
    else
    {
        switch(enumDpMacDphySel)
        {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
            case _DP_MAC_DPHY_RX0:
#if(_DP_MAC_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
                ScalerSetBit_EXINT(PC_8B_FEC_MERGE_PARITY_ERROR_CNT_CTRL, ~(_BIT5 | _BIT0), 0x00);
#endif
                ScalerSetBit_EXINT(PB_D3_FEC_ERROR_DETECT, ~_BIT0, 0x00);
                break;
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
            case _DP_MAC_DPHY_RX1:
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
                ScalerSetBit_EXINT(P1F_8B_FEC_MERGE_PARITY_ERROR_CNT_CTRL, ~(_BIT5 | _BIT0), 0x00);
#endif
                ScalerSetBit_EXINT(PB0_D3_FEC_ERROR_DETECT, ~_BIT0, 0x00);
                break;
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
            case _DP_MAC_DPHY_RX2:
#if(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
                ScalerSetBit_EXINT(PD2_8B_FEC_MERGE_PARITY_ERROR_CNT_CTRL, ~(_BIT5 | _BIT0), 0x00);
#endif
                ScalerSetBit_EXINT(PC5_D3_FEC_ERROR_DETECT, ~_BIT0, 0x00);
                break;
#endif

            default:
                break;
        }
    }
}

//--------------------------------------------------
// Description  : FEC Decode Check
// Input Value  : Enable or Disable
// Output Value : None
//--------------------------------------------------
bit ScalerDpMacDphyRxFecDecodeCheck_EXINT0(EnumInputPort enumInputPort)
{
#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
    if(enumInputPort == _D9_INPUT_PORT)
    {
        enumInputPort = GET_DP_MST_RX_PXP_INPUT_PORT();
    }
#endif

    switch(ScalerDpRxGetMacDphySwitch_EXINT0(enumInputPort))
    {
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX0:

            if(ScalerDpMacDphyRx0FecDecodeCheck_EXINT0() == _TRUE)
            {
                return _TRUE;
            }

            break;
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX1:

            if(ScalerDpMacDphyRx1FecDecodeCheck_EXINT0() == _TRUE)
            {
                return _TRUE;
            }

            break;
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
        case _DP_MAC_DPHY_RX2:

            if(ScalerDpMacDphyRx2FecDecodeCheck_EXINT0() == _TRUE)
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

#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP MST Set St_source Mux Register
// Input Value  : enumSourceNum, ucValue
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxSetSourceMuxReg_128b132b_EXINT0(EnumInputPort enumInputPort, EnumDpStreamSourceNum enumSourceNum, EnumDpStreamNum enumDpStreamNum)
{
    BYTE ucValue = (enumDpStreamNum == _DP_ST_NONE) ? 0 : enumDpStreamNum + 1;

    switch(enumSourceNum)
    {
        case _DP_ST_SOURCE1:

            ScalerSetBit_EXINT(ScalerDpMacDphyRxGetPagedAddress_EXINT0(enumInputPort, P9D_12_SOURCE_SEL_0), ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), ucValue << 4);
            break;

        case _DP_ST_SOURCE2:

            ScalerSetBit_EXINT(ScalerDpMacDphyRxGetPagedAddress_EXINT0(enumInputPort, P9D_12_SOURCE_SEL_0), ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ucValue << 0);
            break;

        case _DP_ST_SOURCE3:

            ScalerSetBit_EXINT(ScalerDpMacDphyRxGetPagedAddress_EXINT0(enumInputPort, P9D_13_SOURCE_SEL_1), ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), ucValue << 4);
            break;

        case _DP_ST_SOURCE4:

            ScalerSetBit_EXINT(ScalerDpMacDphyRxGetPagedAddress_EXINT0(enumInputPort, P9D_13_SOURCE_SEL_1), ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ucValue << 0);
            break;

        case _DP_ST_SOURCE5:

            ScalerSetBit_EXINT(ScalerDpMacDphyRxGetPagedAddress_EXINT0(enumInputPort, P9D_14_SOURCE_SEL_2), ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), ucValue << 4);
            break;

        case _DP_ST_SOURCE6:

            ScalerSetBit_EXINT(ScalerDpMacDphyRxGetPagedAddress_EXINT0(enumInputPort, P9D_14_SOURCE_SEL_2), ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ucValue << 0);
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Backup ST1_Source ~ ST6_Source Clear
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxResetSourceMuxReg_128b132b_EXINT0(EnumInputPort enumInputPort)
{
    ScalerSetBit_EXINT(ScalerDpMacDphyRxGetPagedAddress(enumInputPort, P9D_12_SOURCE_SEL_0), ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);
    ScalerSetBit_EXINT(ScalerDpMacDphyRxGetPagedAddress(enumInputPort, P9D_12_SOURCE_SEL_0), ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(ScalerDpMacDphyRxGetPagedAddress(enumInputPort, P9D_13_SOURCE_SEL_1), ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);
    ScalerSetBit_EXINT(ScalerDpMacDphyRxGetPagedAddress(enumInputPort, P9D_13_SOURCE_SEL_1), ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(ScalerDpMacDphyRxGetPagedAddress(enumInputPort, P9D_14_SOURCE_SEL_2), ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);
    ScalerSetBit_EXINT(ScalerDpMacDphyRxGetPagedAddress(enumInputPort, P9D_14_SOURCE_SEL_2), ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
}

//--------------------------------------------------
// Description  : DP Mst Rx Load New Stream PayLoad EXINT0
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRxLoadNewStreamPayload_128b132b_EXINT0(EnumInputPort enumInputPort)
{
    // Load by MTPH_CNT = 63, Delay 5us, Then Load by Receiving ACT
    ScalerSetBit_EXINT(ScalerDpMacDphyRxGetPagedAddress_EXINT0(enumInputPort, P9D_01_STHD_CTRL_1), ~_BIT7, 0x00);

    // Delay Up to 65537 Timeslots
    // 3.2ns per Timeslot for UHBR10
    // Delay Time  >=  65537 * 3.2ns = 210ns, as 500ns for Insurance Purposes
    DELAY_XUS_EXINT(500);
    ScalerSetBit_EXINT(ScalerDpMacDphyRxGetPagedAddress_EXINT0(enumInputPort, P9D_01_STHD_CTRL_1), ~_BIT7, _BIT7);
}
#endif
#endif
