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
// ID Code      : UserCommonDp.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_COMMON_DP__

#include "UserCommonInclude.h"
#include "Dp/UserCommonDp.h"

#if(_DP_RX_COLOR_FORMAT_420_SUPPORT == _ON)
#warning "NOTE: Native 420 Information Should be Included In EDID"
#endif

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
//--------------------------------------------------
// Description  : Set Dp Aux Diff Mode or single-ended mode
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonDpAuxSet(void)
{
    ScalerDpAuxRxSet();
}

//--------------------------------------------------
// Description  : All Dp Port Dp Version Switch
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonDpVersionSwitchDpAllPortVersion(void)
{
#if(_D0_DP_SUPPORT == _ON)
    UserCommonDpRxVersionSwitch(_D0_INPUT_PORT, UserInterfaceDpGetVersion(_D0_INPUT_PORT), UserCommonDpGetMSTCapablePort());
#endif
#if(_D1_DP_SUPPORT == _ON)
    UserCommonDpRxVersionSwitch(_D1_INPUT_PORT, UserInterfaceDpGetVersion(_D1_INPUT_PORT), UserCommonDpGetMSTCapablePort());
#endif
#if(_D2_DP_SUPPORT == _ON)
    UserCommonDpRxVersionSwitch(_D2_INPUT_PORT, UserInterfaceDpGetVersion(_D2_INPUT_PORT), UserCommonDpGetMSTCapablePort());
#endif
}

//--------------------------------------------------
// Description  : Get DP Version
// Input Value  : Input Port
// Output Value : DP_VERSION_1_1 or DP_VERSION_1_2 or DP_VERSION_1_4
//--------------------------------------------------
EnumDpVersionType UserCommonDpGetVersion(EnumInputPort enumInputPort)
{
#if(_FACTORY_RTD_QC_SUPPORT == _ON)
    return UserCommonQCDpGetVersion(enumInputPort);
#else
    return UserInterfaceDpGetVersion(enumInputPort);
#endif
}

//--------------------------------------------------
// Description  : Get DP Link Rate For PCB Limit
// Input Value  : Input Port
// Output Value : EnumDpLinkRate
//--------------------------------------------------
EnumDpLinkRate UserCommonDpGetPcbMaxLinkRate(EnumInputPort enumInputPort)
{
    return ScalerDpRxRGetPcbMaxLinkRate(enumInputPort);
}

//--------------------------------------------------
// Description  : Get DP Link Rate For User Setting
// Input Value  : Input Port
// Output Value : EnumDpLinkRate
//--------------------------------------------------
EnumDpLinkRate UserCommonDpGetMaxLinkRate(EnumInputPort enumInputPort)
{
    EnumDpLinkRate enumDpLinkRateLimit = UserCommonDpGetPcbMaxLinkRate(enumInputPort);
    EnumDpLinkRate enumDpLinkRate = UserInterfaceDpGetMaxLinkRate(enumInputPort);
    EnumDpVersionType enumDpVersion = UserCommonDpGetVersion(enumInputPort);

    // Avoid Switch Target Out Of Limit
    if(enumDpLinkRate > enumDpLinkRateLimit)
    {
        enumDpLinkRate = enumDpLinkRateLimit;
    }

    // Avoid Switch Target Out Of Spec
    if(enumDpVersion >= _DP_VERSION_2_0)
    {
        if(enumDpLinkRate > _DP_LINK_UHBR20)
        {
            enumDpLinkRate = _DP_LINK_UHBR20;
        }
    }
    else if(enumDpVersion == _DP_VERSION_1_4)
    {
        if(enumDpLinkRate > _DP_LINK_HBR3)
        {
            enumDpLinkRate = _DP_LINK_HBR3;
        }
    }
    else if(enumDpVersion == _DP_VERSION_1_2)
    {
        if(enumDpLinkRate > _DP_LINK_HBR2)
        {
            enumDpLinkRate = _DP_LINK_HBR2;
        }
    }
    else
    {
        if(enumDpLinkRate > _DP_LINK_HBR)
        {
            enumDpLinkRate = _DP_LINK_HBR;
        }
    }

    return enumDpLinkRate;
}

//--------------------------------------------------
// Description  : Get Dp MST Capable Port
// Input Value  : None
// Output Value : _DP_MST_RX0 or _DP_MST_RX1
//--------------------------------------------------
EnumDPMSTPort UserCommonDpGetMSTCapablePort(void)
{
#if(_DP_MST_SUPPORT == _OFF)
    return _DP_MST_NO_PORT;
#else
    return UserInterfaceDpGetMSTCapablePort();
#endif
}

//--------------------------------------------------
// Description  : Get DP Lane Count (DPCD 00101h)
// Input Value  : DP Input Port
// Output Value : DP Lane Count
//--------------------------------------------------
EnumDpLaneCount UserCommonDpAuxRxGetLaneCount(EnumInputPort enumInputPort)
{
    return ScalerDpAuxRxGetDpcdLaneCount(enumInputPort);
}

//--------------------------------------------------
// Description  : Get DP Link Rate (DPCD 00100h)
// Input Value  : DP Input Port
// Output Value : DP Link Rate
//--------------------------------------------------
EnumDpLinkRate UserCommonDpAuxRxGetDpcdLinkRate(EnumInputPort enumInputPort)
{
    return ScalerDpAuxRxGetDpcdLinkRate(enumInputPort);
}

//--------------------------------------------------
// Description  : Switch Max Link Rate Capability
// Input Value  : DP Input Port, Link Rate
// Output Value : None
//--------------------------------------------------
void UserCommonDpAuxRxMaxLinkRateCapabilitySwitch(EnumInputPort enumInputPort)
{
    ScalerDpAuxRxMaxLinkRateCapabilitySwitch(enumInputPort, UserCommonDpGetMaxLinkRate(enumInputPort));
}

//--------------------------------------------------
// Description  : Get DP Voltage Swing Level(DPCD 00103h-00106h [1:0])
// Input Value  : DP Input Port, Lane #
// Output Value : DP Voltage Swing Level of the lane
//--------------------------------------------------
EnumDpVoltageSwingLevel UserCommonDpAuxRxGetLaneVoltageSwingLv(EnumInputPort enumInputPort, EnumDpLane enumDpLane)
{
    return ScalerDpAuxRxGetLaneVoltageSwingLv(enumInputPort, enumDpLane);
}

//--------------------------------------------------
// Description  : Get DP Pre-emphasis Level(DPCD 00103h-00106h [4:3])
// Input Value  : DP Input Port, Lane #
// Output Value : DP Pre-emphasis Level of the lane
//--------------------------------------------------
EnumDpPreEmphasisLevel UserCommonDpAuxRxGetLanePreEmpLv(EnumInputPort enumInputPort, EnumDpLane enumDpLane)
{
    return ScalerDpAuxRxGetLanePreEmpLv(enumInputPort, enumDpLane);
}

//--------------------------------------------------
// Description  : Dp Rx Lane Count Switch
// Input Value  : DP input port, Lane Count
// Output Value : None
//--------------------------------------------------
void UserCommonDpRxLaneCountSwitch(EnumInputPort enumInputPort, EnumDpLaneCount enumDpLaneCount)
{
    ScalerDpRxLaneCountSwitch(enumInputPort, enumDpLaneCount);
}

//--------------------------------------------------
// Description  : Dp Version Switch
// Input Value  : DP input port, _DP_VERSION_1_1 or _DP_VERSION_1_2
// Output Value : None
//--------------------------------------------------
void UserCommonDpRxVersionSwitch(EnumInputPort enumInputPort, EnumDpVersionType enumDpVersion, EnumDPMSTPort enumDpRxMstPort)
{
#if(_AUDIO_SUPPORT == _ON)
    // Mute Audio Output
    UserCommonAudioMuteCurrentDigitalPortProc(enumInputPort);
#endif

    ScalerDpRxVersionSwitch(enumInputPort, enumDpVersion, enumDpRxMstPort);
    UserCommonDpAuxRxMaxLinkRateCapabilitySwitch(enumInputPort);

#if(_DP_PR_MODE_SUPPORT == _ON)
    // Check DP Version Prior than 1.4 with PR
    ScalerDpRxPRModeSupportSwitch(enumInputPort, ((enumDpVersion >= _DP_VERSION_1_4) ? UserInterfaceDpPRModeGetEnable(enumInputPort) : _DP_PR_MODE_SUPPORT_OFF));
#endif

#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
    // Check DP Version Prior than 2.0 with Auxless ALPM
    ScalerDpRxAuxlessAlpmSupportSwitch(enumInputPort, ((enumDpVersion >= _DP_VERSION_2_0) ? UserInterfaceDpAuxlessAlpmGetEnable(enumInputPort) : _DP_AUXLESS_ALPM_SUPPORT_OFF));
#endif

#if(_DP_RX_DSC_DECODER_SUPPORT == _ON)
    // Check DP Version Prior than 1.4 with DSC
    ScalerDscDecoderSyncDpSupportSwitch(enumInputPort, ((enumDpVersion >= _DP_VERSION_1_4) ? UserInterfaceDscDecoderGetEnable(enumInputPort) : _DSC_DECODER_SUPPORT_OFF));
#endif
}

//--------------------------------------------------
// Description  : Get Dp Video Msa Info
// Input Value  : EnumInputPort, EnumDpRxMsaType
// Output Value : UnionDpRxMsaValue
//--------------------------------------------------
UnionDpRxMsaValue UserCommonDpRxGetMsaInfo(EnumInputPort enumInputPort, EnumDpRxMsaType enumDpRxMsaType)
{
    return ScalerDpMacStreamRxGetMsaInfo(enumInputPort, enumDpRxMsaType);
}

//--------------------------------------------------
// Description  : Check Dp Video Straam VBID
// Input Value  : _D0_INPUT_PORT or _D1_INPUT_PORT
// Output Value : True --> Get Video Stream
//--------------------------------------------------
bit UserCommonDpRxGetVideoStream(EnumInputPort enumInputPort)
{
    return ScalerDpRxGetVideoStream(enumInputPort);
}

//--------------------------------------------------
// Description  : Check Dp DSC Straam VBID
// Input Value  : _D0_INPUT_PORT or _D1_INPUT_PORT
// Output Value : True --> Get DSC Stream
//--------------------------------------------------
bit UserCommonDpRxGetDscStream(EnumInputPort enumInputPort)
{
    return ScalerDpRxGetDscStream(enumInputPort);
}

//--------------------------------------------------
// Description  : Check Dp Audio Straam VBID
// Input Value  : _D0_INPUT_PORT or _D1_INPUT_PORT
// Output Value : True --> Get Audio Stream
//--------------------------------------------------
bit UserCommonDpRxGetAudioStream(EnumInputPort enumInputPort)
{
    return ScalerDpRxGetAudioStream(enumInputPort);
}

//--------------------------------------------------
// Description  : Read DP Rx Error Count
// Input Value  : DP Input Port
// Output Value : DP 4 Lane Error Count & Valid Flag
//--------------------------------------------------
StructDpRxErrorCount UserCommonDpRxGetErrorCount(EnumInputPort enumInputPort)
{
    return ScalerDpRxGetErrorCount(enumInputPort);
}

//--------------------------------------------------
// Description  : Get DPCD Table Information
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
// Output Value : DPCD Information
//--------------------------------------------------
BYTE UserCommonDpAuxRxGetDpcdBitInfo(EnumInputPort enumInputPort, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdBit)
{
    return ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdBit);
}

//--------------------------------------------------
// Description  : Get DPCD Table Information
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
// Output Value : DPCD Information
//--------------------------------------------------
BYTE UserCommonDpAuxRxGetDpcdInfo(EnumInputPort enumInputPort, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL)
{
    return ScalerDpAuxRxGetDpcdInfo(enumInputPort, ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL);
}

//--------------------------------------------------
// Description  : Set DPCD Table Information
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
//                ucDpcdValue --> DPCD Value
// Output Value : None
//--------------------------------------------------
void UserCommonDpAuxRxSetDpcdBitValue(EnumInputPort enumInputPort, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit, EnumDpcdAttribute enumDpcdAttribute)
{
    if(enumDpcdAttribute == _DPCD_READ_ONLY)
    {
        ScalerDpAuxRxSetDpcdBitValue(enumInputPort, ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);
    }
    else if(enumDpcdAttribute == _DPCD_WRITE)
    {
        ScalerDpAuxRxSetDpcdBitWriteValue(enumInputPort, ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);
    }
    else if(enumDpcdAttribute == _DPCD_WRITE_1_CLEAR)
    {
        ScalerDpAuxRxSetDpcdBitWrite1ClearValue(enumInputPort, ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);
    }
}

//--------------------------------------------------
// Description  : Set DPCD Table Information
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
//                ucDpcdValue --> DPCD Value
// Output Value : None
//--------------------------------------------------
void UserCommonDpAuxRxSetDpcdValue(EnumInputPort enumInputPort, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue, EnumDpcdAttribute enumDpcdAttribute)
{
    if(enumDpcdAttribute == _DPCD_READ_ONLY)
    {
        ScalerDpAuxRxSetDpcdValue(enumInputPort, ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);
    }
    else if(enumDpcdAttribute == _DPCD_WRITE)
    {
        ScalerDpAuxRxSetDpcdWriteValue(enumInputPort, ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);
    }
    else if(enumDpcdAttribute == _DPCD_WRITE_1_CLEAR)
    {
        ScalerDpAuxRxSetDpcdWrite1ClearValue(enumInputPort, ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);
    }
}

//--------------------------------------------------
// Description  : Get DP Source MST enable (DPCD 00111h[0])
// Input Value  : DP Input Port
// Output Value : _TRUE --> MST enable, _FALSE --> SST
//--------------------------------------------------
bit UserCommonDpRxGetSrcMstEnable(EnumInputPort enumInputPort)
{
    return ScalerDpRxGetSrcMstEnable(enumInputPort);
}

//--------------------------------------------------
// Description  : Set Dp HotPlug Event
// Input Value  : Hot Plug Type
// Output Value : None
//--------------------------------------------------
void UserCommonDpRxSetHotPlugEvent(EnumInputPort enumInputPort, EnumDpHotPlugType_User enumHpdType)
{
    switch(enumHpdType)
    {
        case _DP_HPD_USER_LOW:

            ScalerDpRxSetHotPlugEvent(enumInputPort, _DP_HPD_LOW_RESET_AUX);

            break;

        case _DP_HPD_USER_HIGH:

            ScalerDpRxSetHotPlugEvent(enumInputPort, _DP_HPD_ASSERTED);

            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Dp Hot Plug Event Get Done
// Input Value  : enumInputPort
// Output Value : _TRUE: Done, _FALSE: Proccessing
//--------------------------------------------------
EnumDpHotPlugType_User UserCommonDpRxGetHotPlugStatus(EnumInputPort enumInputPort)
{
    bit bHpdStatus = _LOW;

#if((_TYPE_C_DX_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON))
    if(ScalerTypeCPcbxTypeCxMapping(ScalerTypeCDxConvertToPcbPort(enumInputPort)) != _EMB_TYPE_C_NOT_EXIST)
    {
        bHpdStatus = ScalerTypeCRxGetHPDStatus(enumInputPort);
    }
    else
#endif
    {
        bHpdStatus = ScalerDpRxGetHotPlugStatus(enumInputPort);
    }

    if(bHpdStatus == _HIGH)
    {
        return _DP_HPD_USER_HIGH;
    }
    else
    {
        return _DP_HPD_USER_LOW;
    }
}

//--------------------------------------------------
// Description  : DP Tx I2CoverAux Write
// Input Value  : ucSlaveAddress --> SlaveAddress of I2CoverAux Write
//                ucLength --> Length of I2CoverAux Write
//                pWriteArray --> Data of I2CoverAux Write
// Output Value : EnumDpAuxStatus --> Native Aux Write Sucessful
//--------------------------------------------------
EnumDpAuxStatus UserCommonDpTxAuxI2COverWrite(BYTE ucSlaveAddress, BYTE ucLength, BYTE *pucDataArray)
{
    ucSlaveAddress = ucSlaveAddress;
    ucLength = ucLength;
    pucDataArray = pucDataArray;

#if(_DP_PHY_TX_SUPPORT == _ON)
    while(ucLength > 16)
    {
        ucLength = ucLength - 16;

        if(ScalerDpAuxTxI2CoverWrite(ucSlaveAddress, 16, pucDataArray, 1) == _FALSE)
        {
            return _DP_AUX_FAIL;
        }
        else
        {
            pucDataArray = pucDataArray + 16;
        }
    }

    if(ScalerDpAuxTxI2CoverWrite(ucSlaveAddress, ucLength, pucDataArray, 0) == _FALSE)
    {
        return _DP_AUX_FAIL;
    }

    return _DP_AUX_PASS;
#else
    return _DP_AUX_FAIL;
#endif
}

//--------------------------------------------------
// Description  : DP Tx I2CoverAux Read
// Input Value  : ucSlaveAddress --> SlaveAddress of I2CoverAux Read
//                ucLength --> Length of I2CoverAux Read
//                pWriteArray --> Data of I2CoverAux Read
// Output Value : EnumDpAuxStatus --> Native Aux Write Sucessful
//--------------------------------------------------
EnumDpAuxStatus UserCommonDpTxAuxI2COverRead(BYTE ucSlaveAddress, BYTE ucLength, BYTE *pucDataArray)
{
    ucSlaveAddress = ucSlaveAddress;
    ucLength = ucLength;
    pucDataArray = pucDataArray;

#if(_DP_PHY_TX_SUPPORT == _ON)
    while(ucLength > 16)
    {
        ucLength = ucLength - 16;

        if(ScalerDpAuxTxI2CoverRead(ucSlaveAddress, 16, pucDataArray, 1) == _FALSE)
        {
            return _DP_AUX_FAIL;
        }
        else
        {
            pucDataArray = pucDataArray + 16;
        }
    }

    if(ScalerDpAuxTxI2CoverRead(ucSlaveAddress, ucLength, pucDataArray, 0) == _FALSE)
    {
        return _DP_AUX_FAIL;
    }

    return _DP_AUX_PASS;
#else
    return _DP_AUX_FAIL;
#endif
}

//--------------------------------------------------
// Description  : Dp IRQ Assert Proc
// Input Value  : ucInputPort
// Output Value : None
//--------------------------------------------------
void UserCommonDpRxHpdIrqAssert(BYTE ucInputPort)
{
    ScalerDpAuxRxHpdIrqAssert(ucInputPort);
}

//--------------------------------------------------
// Description  : DPCD Link Status Field Reset
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void UserCommonDpAuxRxDpcdLinkStatusInitial(EnumInputPort enumInputPort)
{
    ScalerDpAuxRxDpcdLinkStatusReset(enumInputPort, _DP_DPCD_LINK_STATUS_INITIAL);
}

//--------------------------------------------------
// Description  : Get Link Training Pass
// Input Value  : EnumInputPort
// Output Value : EnumUserDpLTStatus
//--------------------------------------------------
EnumUserDpLTStatus UserCommonDpGetLinkTrainingStatus(EnumInputPort enumInputPort)
{
    return (EnumUserDpLTStatus)ScalerDpAuxRxGetLinkTrainingPass(enumInputPort);
}

#if(_DP_ADAPTIVESYNC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : AdaptiveSync Support Switch
// Input Value  : Check Status
// Output Value : None
//--------------------------------------------------
void UserCommonDpAdaptiveSyncSupportSwitch(void)
{
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
    ScalerDrrDpAdaptiveSyncSupportSwitch(_D0_INPUT_PORT, UserInterfaceDpAdaptiveSyncGetEnable(_D0_INPUT_PORT));
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
    ScalerDrrDpAdaptiveSyncSupportSwitch(_D1_INPUT_PORT, UserInterfaceDpAdaptiveSyncGetEnable(_D1_INPUT_PORT));
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
    ScalerDrrDpAdaptiveSyncSupportSwitch(_D2_INPUT_PORT, UserInterfaceDpAdaptiveSyncGetEnable(_D2_INPUT_PORT));
#endif
}

//--------------------------------------------------
// Description  : Get AdaptiveSync Support
// Input Value  : enumInputPort
// Output Value : enumAdaptiveSyncSupport
//--------------------------------------------------
EnumDpAdaptiveSyncSupport UserCommonDpAdaptiveSyncGetSupport(EnumInputPort enumInputPort)
{
    return ScalerDrrDpAdaptiveSyncGetSupport(enumInputPort);
}

//--------------------------------------------------
// Description  : Set AdaptiveSync Support By Port
// Input Value  : enumInputPort, enumSupport
// Output Value : None
//--------------------------------------------------
void UserCommonDpAdaptiveSyncSetInputPortSupport(EnumInputPort enumInputPort, EnumDpAdaptiveSyncSupport enumSupport)
{
    ScalerDrrDpAdaptiveSyncSupportSwitch(enumInputPort, enumSupport);
}
#endif

#if(_DP_HDR10_SUPPORT == _ON)
#if(_DP_HDR_VENDOR_SUPPORT != _DP_HDR_VENDOR_SUPPORT_NONE)
//--------------------------------------------------
// Description  : DP HDR Support Switch
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonDpHdrSupportSwitch(void)
{
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
    if(UserInterfaceColorHDRGetHDR10ModeStatus(_D0_INPUT_PORT) != _HDR10_MODE_OFF)
    {
        ScalerDpRxHdrSupportSwitch(_D0_INPUT_PORT, _DP_HDR_SUPPORT_ON);
    }
    else
    {
        ScalerDpRxHdrSupportSwitch(_D0_INPUT_PORT, _DP_HDR_SUPPORT_OFF);
    }
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
    if(UserInterfaceColorHDRGetHDR10ModeStatus(_D1_INPUT_PORT) != _HDR10_MODE_OFF)
    {
        ScalerDpRxHdrSupportSwitch(_D1_INPUT_PORT, _DP_HDR_SUPPORT_ON);
    }
    else
    {
        ScalerDpRxHdrSupportSwitch(_D1_INPUT_PORT, _DP_HDR_SUPPORT_OFF);
    }
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
    if(UserInterfaceColorHDRGetHDR10ModeStatus(_D2_INPUT_PORT) != _HDR10_MODE_OFF)
    {
        ScalerDpRxHdrSupportSwitch(_D2_INPUT_PORT, _DP_HDR_SUPPORT_ON);
    }
    else
    {
        ScalerDpRxHdrSupportSwitch(_D2_INPUT_PORT, _DP_HDR_SUPPORT_OFF);
    }
#endif
}
#endif
#endif

#if(_DP_MST_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Mst Capable Port Switch
// Input Value  : EnumDpRxMstPort
// Output Value : None
//--------------------------------------------------
void UserCommonDpMstRxCapablePortSwitch(EnumDPMSTPort enumMstCapablePort)
{
#if(_AUDIO_SUPPORT == _ON)
    if(SysAudioCheckDpPortExist() == _TRUE)
    {
        UserCommonAudioResetProc();
    }
#endif
    ScalerDpMstRxCapablePortSwitch(enumMstCapablePort);
}

#if((_DP_TX_SUPPORT == _ON) && (_DP_MST_TX_INTERCEPT_DDCCI_MSG_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Mst Tx Intercept Ddcci Msg Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonDpMstTxInterceptDdcciMsgSetting(bit bStatus)
{
    bStatus = bStatus;

    ScalerDpMstTxInterceptDdcciMsgSetting(bStatus);
}
#endif
#endif

#if((_DP_MST_SUPPORT == _ON) || (_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Get DP Rx Mst Stream Exist
// Input Value  : EnumInputPort
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit UserCommonDpMstRxGetMstStreamExist(EnumInputPort enumInputPort)
{
    return ScalerDpMacDphyRxGetMstStreamExist(ScalerDpRxDxMacSourceMapping(enumInputPort));
}
#endif

#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
//--------------------------------------------------
// Description  : DP Rx Pxp Mode Support Switch
// Input Value  : enumDpMstPxpMode
// Output Value : None
//--------------------------------------------------
void UserCommonDpMstRxPxpModeSwitch(EnumDpMstPxpMode enumDpMstPxpMode)
{
#if(_AUDIO_SUPPORT == _ON)
    if(ScalerAudioDigitalAudioSourceType(_AUDIO_DAC_OUT) == _SOURCE_DP)
    {
        UserCommonAudioResetProc();
    }
#endif
    ScalerDpMstRxPxpModeSwitch(enumDpMstPxpMode);

    SysDpRxPxpInputPortSwitch(UserInterfaceDpGetPxpInputTarget());

    SysDpRxPxpPortNumSwapJudge();
}

//--------------------------------------------------
// Description  : Get DP Rx Pxp Mode Support Status
// Input Value  : None
// Output Value : EnumDpMstPxpMode enumDpMstPxpMode
//--------------------------------------------------
EnumDpMstPxpMode UserCommonDpMstRxGetPxpMode(void)
{
    return ScalerDpMstRxGetPxpMode();
}
#endif

#if(_DP_LONG_HPD_ALLOWED_BY_USER_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set Dp Long HPD Allowed or Not
// Input Value  : ucInputPort, bAllowed = _TRUE/_FALSE
// Output Value : None
//--------------------------------------------------
void UserCommonDpLongHpdSetAllowed(EnumInputPort enumInputPort, bit bAllowed)
{
    ScalerDpRxLongHpdSetAllowed(enumInputPort, bAllowed);
}
#endif

//--------------------------------------------------
// Description  : Get Dp Port Edid Native Timing BW
// Input Value  : enumDpEdidPort --> Dp Edid Port
// Output Value : Bw, Unit: 0.01M
//--------------------------------------------------
WORD UserCommonDpMacGetEdidNativeTimingBw(EnumDpEdidPort enumDpEdidPort)
{
    switch(enumDpEdidPort)
    {
        case _D0_DP_EDID:
        case _D1_DP_EDID:
        case _D2_DP_EDID:

            return ScalerSyncGetDpRxPortEdidBw(enumDpEdidPort);

        case _DP_TX_EDID:

#if(_DP_TX_SUPPORT == _ON)
            return ScalerDpMacTxGetDownStreamEdidBw();
#endif

        default:

            break;
    }

    return 0;
}

//--------------------------------------------------
// Description  : DP Get Quantization Prevalue
// Input Value  : enumInputPort
// Output Value : Quantization Prevalue
//--------------------------------------------------
BYTE UserCommonDpMacGetQuantizationPreValue(EnumInputPort enumInputPort)
{
    return ScalerDpMacStreamRxGetQuantizationPreValue(enumInputPort);
}

#if(_DP_PR_MODE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP PR Mode Support Switch
// Input Value  : Check Status
// Output Value : None
//--------------------------------------------------
void UserCommonDpPRModeSupportSwitch(void)
{
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
    ScalerDpRxPRModeSupportSwitch(_D0_INPUT_PORT, UserInterfaceDpPRModeGetEnable(_D0_INPUT_PORT));
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
    ScalerDpRxPRModeSupportSwitch(_D1_INPUT_PORT, UserInterfaceDpPRModeGetEnable(_D1_INPUT_PORT));
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
    ScalerDpRxPRModeSupportSwitch(_D2_INPUT_PORT, UserInterfaceDpPRModeGetEnable(_D2_INPUT_PORT));
#endif
}
#endif

#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP Auxless ALPM Support Switch
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonDpAuxlessAlpmSupportSwitch(void)
{
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
    ScalerDpRxAuxlessAlpmSupportSwitch(_D0_INPUT_PORT, UserInterfaceDpAuxlessAlpmGetEnable(_D0_INPUT_PORT));
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
    ScalerDpRxAuxlessAlpmSupportSwitch(_D1_INPUT_PORT, UserInterfaceDpAuxlessAlpmGetEnable(_D1_INPUT_PORT));
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
    ScalerDpRxAuxlessAlpmSupportSwitch(_D2_INPUT_PORT, UserInterfaceDpAuxlessAlpmGetEnable(_D2_INPUT_PORT));
#endif
}
#endif

#if(_DP_FREESYNC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get AMD Aupi Panel Info
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonDpGetAmdAupiPanelInfo(void)
{
    StructDrrAmdAupiInfo stDrrDpAmdAupiInfo = {0};
    StructDrrAmdAupiInfo stCheck = {0};

    UserInterfaceFreeSyncGetDpAupiPanelInfo(&stDrrDpAmdAupiInfo);
    CLR_FREESYNC_DP_AUPI_INFO();

    // check if stDrrDpAmdAupiInfo is all zero
    if(memcmp(&stDrrDpAmdAupiInfo, &stCheck, sizeof(stDrrDpAmdAupiInfo)) != 0)
    {
        g_stDrrDpAmdAupiInfo = stDrrDpAmdAupiInfo;
        SET_FREESYNC_DP_AUPI_INFO();
    }
}
#endif

#if(_DP_USER_INT0_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP User Int Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonDpIntHandler_EXINT0(void)
{
    EnumInputPort enumInputPort = _D0_INPUT_PORT;

    for(enumInputPort = _D0_INPUT_PORT; enumInputPort <= _D2_INPUT_PORT; enumInputPort ++)
    {
        if(SysSourceGetPortTypeFromInputPort(enumInputPort) == _PORT_DP)
        {
#if(_DP_USER_INT_FOR_SOURCE_WRITE_OUI_SUPPORT == _ON)
            if(GET_DP_RX_USER_INT_EVENT(enumInputPort, _DP_USER_INT_EVENT_SOURCE_WRITE_OUI) == _TRUE)
            {
                CLR_DP_RX_USER_INT_EVENT(enumInputPort, _DP_USER_INT_EVENT_SOURCE_WRITE_OUI);

                UserInterfaceDpSourceWriteOuiHandler_EXINT0(enumInputPort);
            }
#endif
        }
    }
}
#endif
#endif

#if(_DP_MAC_TX_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Dp Tx Get Stream Source
// Input Value  : None
// Output Value : GET_DP_TX_STREAM_SOURCE
//--------------------------------------------------
EnumDPTxInputSource UserCommonDpTxGetStreamSource(void)
{
    return ScalerDpMacTxGetStreamSource();
}

//--------------------------------------------------
// Description  : Dp Tx Get Downstream DP Plug Status
// Input Value  : None
// Output Value : _DP_UNPLUG / _DP_PLUG
//--------------------------------------------------
bit UserCommonDpTxGetDownstreamHPDStatus(void)
{
    return ScalerDpMacTxUserGetDownstreamHPDStatus();
}

#if(_DP_TX_BLOCK_CONTROL_BEFORE_STREAM_OUTPUT == _ON)
//--------------------------------------------------
// Description  : DP Tx Clone Mode Switch
// Input Value  : Clone Mode on/off
// Output Value : None
//--------------------------------------------------
void UserCommonDpMacTxCloneModeSwitch(EnumDPCloneOutputStatus enumClone)
{
    ScalerDpMacTxCloneModeSwitch(enumClone);
}
#endif
#endif
