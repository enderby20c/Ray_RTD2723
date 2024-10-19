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
// ID Code      : ScalerSync.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_SYNC_H__
#define __SCALER_SYNC_H__

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_DP_SUPPORT == _ON)
//--------------------------------------------------
// Definitions of DP DC OFF HPD Related
//--------------------------------------------------
#if(_D0_DP_SUPPORT == _ON)
#define GET_DP_RX0_HDCP_CHECK_ENABLE()                      (g_bSyncDpRx0HdcpCheckEnable)
#define SET_DP_RX0_HDCP_CHECK_ENABLE()                      (g_bSyncDpRx0HdcpCheckEnable = _TRUE)
#define CLR_DP_RX0_HDCP_CHECK_ENABLE()                      (g_bSyncDpRx0HdcpCheckEnable = _FALSE)
#endif

#if(_D1_DP_SUPPORT == _ON)
#define GET_DP_RX1_HDCP_CHECK_ENABLE()                      (g_bSyncDpRx1HdcpCheckEnable)
#define SET_DP_RX1_HDCP_CHECK_ENABLE()                      (g_bSyncDpRx1HdcpCheckEnable = _TRUE)
#define CLR_DP_RX1_HDCP_CHECK_ENABLE()                      (g_bSyncDpRx1HdcpCheckEnable = _FALSE)
#endif

#if(_D2_DP_SUPPORT == _ON)
#define GET_DP_RX2_HDCP_CHECK_ENABLE()                      (g_bSyncDpRx2HdcpCheckEnable)
#define SET_DP_RX2_HDCP_CHECK_ENABLE()                      (g_bSyncDpRx2HdcpCheckEnable = _TRUE)
#define CLR_DP_RX2_HDCP_CHECK_ENABLE()                      (g_bSyncDpRx2HdcpCheckEnable = _FALSE)
#endif
#endif

#if(_HDR10_SUPPORT == _ON)
#define SET_HDR10_RX_INFO_DATA(inputport, x)                (g_pstSyncHDR10SaticMetadata[ScalerSyncDxHDRMetadataIndexMapping(inputport)] = (x))
#define CLR_HDR10_RX_INFO_DATA(inputport)                   (memset(&g_pstSyncHDR10SaticMetadata[ScalerSyncDxHDRMetadataIndexMapping(inputport)], 0, sizeof(StructHDR10StaticMetaData)))
#endif

#if(_HDMI_SBTM_SUPPORT == _ON)
#define SET_HDR10_SBTM_RX_INFO_DATA(inputport, x)           (g_pstSyncHDR10SBTMMetadata[ScalerSyncDxHDRMetadataIndexMapping(inputport)] = (x))
#define CLR_HDR10_SBTM_RX_INFO_DATA(inputport)              (memset(&g_pstSyncHDR10SBTMMetadata[ScalerSyncDxHDRMetadataIndexMapping(inputport)], 0, sizeof(StructHDR10SBTMInfo)))
#endif


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef enum
{
    _HDR_METADATA_INDEX_DEFAULT = 0x00,
    _HDR_METADATA_INDEX_0 = (_D0_INPUT_PORT_TYPE != _D0_NO_PORT) + _HDR_METADATA_INDEX_DEFAULT,
    _HDR_METADATA_INDEX_1 = (_D1_INPUT_PORT_TYPE != _D1_NO_PORT) + _HDR_METADATA_INDEX_0,
    _HDR_METADATA_INDEX_2 = (_D2_INPUT_PORT_TYPE != _D2_NO_PORT) + _HDR_METADATA_INDEX_1,
    _HDR_METADATA_INDEX_3 = (_D3_INPUT_PORT_TYPE != _D3_NO_PORT) + _HDR_METADATA_INDEX_2,
    _HDR_METADATA_INDEX_4 = (_D4_INPUT_PORT_TYPE != _D4_NO_PORT) + _HDR_METADATA_INDEX_3,
    _HDR_METADATA_INDEX_5 = (_D5_INPUT_PORT_TYPE != _D5_NO_PORT) + _HDR_METADATA_INDEX_4,
    _HDR_METADATA_INDEX_VALID = _HDR_METADATA_PORT_VALID,
} EnumHDRMetadataIndex;


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_ULTRA_HDR_SUPPORT == _ON)
#if(_HDR10_SUPPORT == _ON)
extern bit ScalerSyncHDR10CheckPortStatus(EnumInputPort enumInputPort);
#endif
#if(_HDMI_SBTM_SUPPORT == _ON)
extern bit ScalerSyncHDR10SBTMCheckPortStatus(EnumInputPort enumInputPort);
#endif
#endif

#if(_DP_SUPPORT == _ON)

#if(_DP_MARGIN_LINK_SUPPORT == _ON)
extern void ScalerSyncDpMarginLinkCapabilitySwitchProc(void);
#endif

extern bit ScalerSyncDpPowerSwitchHpdToggleCheck(EnumInputPort enumInputPort, EnumPowerAction enumPowerAction);
extern bit ScalerSyncDpCheckUrgentHotPlugEventExist(void);
extern void ScalerSyncDpCheckHdcpEnable(void);
extern bit ScalerSyncDpGetHdcpEnable(EnumInputPort enumInputPort);
#endif

#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
extern void ScalerSyncInterfaceD0Proc(bit bEnable);
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
extern void ScalerSyncInterfaceD1Proc(bit bEnable);
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
extern void ScalerSyncInterfaceD2Proc(bit bEnable);
#endif

#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
extern void ScalerSyncInterfaceD3Proc(bit bEnable);
#endif

#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
extern void ScalerSyncInterfaceD4Proc(bit bEnable);
#endif

#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
extern void ScalerSyncInterfaceD5Proc(bit bEnable);
#endif

#if(_D9_INPUT_PORT_TYPE != _D9_NO_PORT)
extern void ScalerSyncInterfaceD9Proc(bit bEnable);
#endif

#if(_DIGITAL_PORT_SUPPORT == _ON)
extern void ScalerSyncDigitalClrColorimetryChanged(EnumInputPort enumInputPort);
extern void ScalerSyncDigitalClrColorimetryExtChanged(EnumInputPort enumInputPort);
extern void ScalerSyncDigitalClrQuantizationChanged(EnumInputPort enumInputPort);
#endif


#endif // End of #ifndef __SCALER_SYNC_H__
