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
// ID Code      : UserCommonDpInterface_User.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef enum
{
    _DPCD_READ_ONLY = 0x00,
    _DPCD_WRITE,
    _DPCD_WRITE_1_CLEAR,
} EnumDpcdAttribute;

typedef enum
{
    _DP_AUX_FAIL = 0x00,
    _DP_AUX_PASS,
} EnumDpAuxStatus;

typedef enum
{
    _DP_LT_NOT_PASS = 0x00,
    _DP_LT_PASS,
} EnumUserDpLTStatus;


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_DP_SUPPORT == _ON)
extern void UserCommonDpAuxSet(void);
extern void UserCommonDpVersionSwitchDpAllPortVersion(void);
extern EnumDpVersionType UserCommonDpGetVersion(EnumInputPort enumInputPort);
extern EnumDPMSTPort UserCommonDpGetMSTCapablePort(void);
extern EnumDpLaneCount UserCommonDpAuxRxGetLaneCount(EnumInputPort enumInputPort);
extern EnumDpLinkRate UserCommonDpAuxRxGetDpcdLinkRate(EnumInputPort enumInputPort);
extern void UserCommonDpAuxRxMaxLinkRateCapabilitySwitch(EnumInputPort enumInputPort);
extern EnumDpVoltageSwingLevel UserCommonDpAuxRxGetLaneVoltageSwingLv(EnumInputPort enumInputPort, EnumDpLane enumDpLane);
extern EnumDpPreEmphasisLevel UserCommonDpAuxRxGetLanePreEmpLv(EnumInputPort enumInputPort, EnumDpLane enumDpLane);
extern void UserCommonDpRxLaneCountSwitch(EnumInputPort enumInputPort, EnumDpLaneCount enumDpLaneCount);
extern void UserCommonDpRxVersionSwitch(EnumInputPort enumInputPort, EnumDpVersionType enumDpVersion, EnumDPMSTPort enumDpRxMstPort);
extern UnionDpRxMsaValue UserCommonDpRxGetMsaInfo(EnumInputPort enumInputPort, EnumDpRxMsaType enumDpRxMsaType);
extern bit UserCommonDpRxGetVideoStream(EnumInputPort enumInputPort);
extern bit UserCommonDpRxGetDscStream(EnumInputPort enumInputPort);
extern bit UserCommonDpRxGetAudioStream(EnumInputPort enumInputPort);
extern StructDpRxErrorCount UserCommonDpRxGetErrorCount(EnumInputPort enumInputPort);
extern BYTE UserCommonDpAuxRxGetDpcdBitInfo(EnumInputPort enumInputPort, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdBit);
extern BYTE UserCommonDpAuxRxGetDpcdInfo(EnumInputPort enumInputPort, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL);
extern void UserCommonDpAuxRxSetDpcdBitValue(EnumInputPort enumInputPort, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit, EnumDpcdAttribute enumDpcdAttribute);
extern void UserCommonDpAuxRxSetDpcdValue(EnumInputPort enumInputPort, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue, EnumDpcdAttribute enumDpcdAttribute);
extern bit UserCommonDpRxGetSrcMstEnable(EnumInputPort enumInputPort);
extern void UserCommonDpRxSetHotPlugEvent(EnumInputPort enumInputPort, EnumDpHotPlugType_User enumHpdType);
extern EnumDpHotPlugType_User UserCommonDpRxGetHotPlugStatus(EnumInputPort enumInputPort);
extern EnumDpAuxStatus UserCommonDpTxAuxI2COverWrite(BYTE ucSlaveAddress, BYTE ucLength, BYTE *pucDataArray);
extern EnumDpAuxStatus UserCommonDpTxAuxI2COverRead(BYTE ucSlaveAddress, BYTE ucLength, BYTE *pucDataArray);
extern void UserCommonDpRxHpdIrqAssert(BYTE ucInputPort);
extern void UserCommonDpAuxRxDpcdLinkStatusInitial(EnumInputPort enumInputPort);
extern EnumUserDpLTStatus UserCommonDpGetLinkTrainingStatus(EnumInputPort enumInputPort);

#if(_DP_MST_SUPPORT == _ON)
extern void UserCommonDpMstRxCapablePortSwitch(EnumDPMSTPort enumMstCapablePort);
#if((_DP_TX_SUPPORT == _ON) && (_DP_MST_TX_INTERCEPT_DDCCI_MSG_SUPPORT == _ON))
extern void UserCommonDpMstTxInterceptDdcciMsgSetting(bit bStatus);
#endif
#endif

#if((_DP_MST_SUPPORT == _ON) || (_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON))
extern bit UserCommonDpMstRxGetMstStreamExist(EnumInputPort enumInputPort);
#endif

#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
extern void UserCommonDpMstRxPxpModeSwitch(EnumDpMstPxpMode enumDpMstPxpMode);
extern EnumDpMstPxpMode UserCommonDpMstRxGetPxpMode(void);
#endif

#if(_DP_LONG_HPD_ALLOWED_BY_USER_SUPPORT == _ON)
extern void UserCommonDpLongHpdSetAllowed(EnumInputPort enumInputPort, bit bAllowed);
#endif

#if(_DP_PR_MODE_SUPPORT == _ON)
extern void UserCommonDpPRModeSupportSwitch(void);
#endif

#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
extern void UserCommonDpAuxlessAlpmSupportSwitch(void);
#endif

#if(_DP_ADAPTIVESYNC_SUPPORT == _ON)
extern void UserCommonDpAdaptiveSyncSupportSwitch(void);
extern EnumDpAdaptiveSyncSupport UserCommonDpAdaptiveSyncGetSupport(EnumInputPort enumInputPort);
extern void UserCommonDpAdaptiveSyncSetInputPortSupport(EnumInputPort enumInputPort, EnumDpAdaptiveSyncSupport enumSupport);
#endif

#if(_DP_HDR10_SUPPORT == _ON)
#if(_DP_HDR_VENDOR_SUPPORT != _DP_HDR_VENDOR_SUPPORT_NONE)
extern void UserCommonDpHdrSupportSwitch(void);
#endif
#endif

extern WORD UserCommonDpMacGetEdidNativeTimingBw(EnumDpEdidPort enumDpEdidPort);
extern BYTE UserCommonDpMacGetQuantizationPreValue(EnumInputPort enumInputPort);
#endif

#if(_DP_MAC_TX_SUPPORT == _ON)
extern EnumDPTxInputSource UserCommonDpTxGetStreamSource(void);
extern bit UserCommonDpTxGetDownstreamHPDStatus(void);

#if(_DP_TX_BLOCK_CONTROL_BEFORE_STREAM_OUTPUT == _ON)
extern void UserCommonDpMacTxCloneModeSwitch(EnumDPCloneOutputStatus enumClone);
#endif
#endif
