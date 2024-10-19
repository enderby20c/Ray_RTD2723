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
// ID Code      : UserCommonEdid.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __USER_COMMON_EDID_H__
#define __USER_COMMON_EDID_H__


//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_EMBEDDED_EDID_SUPPORT == _ON)
#define CHECK_EDID_MODIFY_TARGET(x, flag)               (((x) & (flag)) != 0)

#if(_DUAL_DP_SUPPORT == _ON)
//--------------------------------------------------
// MACRO for DP Dual Port EDID Select
//--------------------------------------------------
#define GET_DP_DUAL_PORT_EDID_STATUS_SELECT()           (g_bEdidDpDualPortSwitchSelect)
#define SET_DP_DUAL_PORT_EDID_STATUS_SELECT()           (g_bEdidDpDualPortSwitchSelect = _TRUE)
#define CLR_DP_DUAL_PORT_EDID_STATUS_SELECT()           (g_bEdidDpDualPortSwitchSelect = _FALSE)
#endif

// --------------------------------------------------
// Define Edid Block Size Information
// --------------------------------------------------
#define _EDID_BLOCK_SIZE_BITWIDTH                       (0x07)  // 128 Byte = 2^7

// --------------------------------------------------
// CTA Extension General Version Offset Definition
// --------------------------------------------------
#define _CTA_OFT_TAG                                    0x00
#define _CTA_OFT_DTD_OFFSET                             0x02
#define _CTA_OFT_DB_START                               0x04
#define _CTA_OFT_CHECKSUM                               0x7F
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
#if(_EMBEDDED_EDID_SUPPORT == _ON)
typedef enum
{
    _DB_SHIFT_ADD = 0x00,
    _DB_SHIFT_REMOVE,
} EnumEdidDataBlockShiftDirect;
#endif


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_EMBEDDED_EDID_SUPPORT == _ON)
extern void UserCommonEdidEmbeddedInfoParser(EnumInputPort enumInputPort);
#endif

#if((_HLG_SUPPORT == _ON) || (_HDMI21_RX_DSC_DECODER_SUPPORT == _ON) || (_HDMI_FREESYNC_SUPPORT == _ON) || (_AUDIO_ARC_SUPPORT == _ON))
extern void UserCommonEdidShiftCtaDataBlockAddrProc(EnumEdidDataBlockShiftDirect enumShiftDir, BYTE ucLengthExt, WORD *pusCtaDataBlockAddr, EnumEdidCtaDataBlock enumCtaBaseDataBlock);
extern BYTE UserCommonEdidCntDtdNum(BYTE *pucDtd, BYTE ucDtdLength);
extern bit UserCommonEdidCheckSumCal(BYTE *pucDdcRamAddr, WORD usStartAddr);
#if(_HLG_SUPPORT == _ON)
extern bit UserCommonEdidHlgEdidModify(BYTE *pucEdidAddr, WORD *pusCtaDataBlockAddr);
#endif
#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
extern bit UserCommonEdidDscHdmiEdidModify(BYTE *pucEdidAddr, WORD *pusCtaDataBlockAddr);
#endif
#if(_HDMI_FREESYNC_SUPPORT == _ON)
extern bit UserCommonEdidHdmiFreesyncModify(BYTE *pucEdidAddr, WORD *pusCtaDataBlockAddr);
#endif
#endif
#if(_HDMI_MULTI_EDID_SUPPORT == _ON)
extern BYTE UserCommonEdidGetHdmiEdidCount(EnumInputPort enumInputPort);
extern bit UserCommonEdidCheckMultiEdidSupport(EnumInputPort enumInputPort);
#if((_EMBEDDED_EDID_SUPPORT == _ON) && (_WRITE_EDID_LOCATION_BY_USER_SUPPORT == _ON))
extern void UserCommonEdidReloadHdmiEdid(EnumInputPort enumInputPort);
#endif
extern void UserCommonEdidBeforeReloadHdmiEdidProc(EnumInputPort enumInputPort, EnumEdidSelection enumHDMIEDIDSelection);
extern void UserCommonEdidAfterReloadHdmiEdidProc(EnumInputPort enumInputPort, EnumEdidSelection enumHDMIEDIDSelection);
extern void UserCommonEdidSwitchMultiHdmiEeprom(EnumInputPort enumInputPort, EnumEdidSelection enumHDMIEDIDSelection);
#endif

#if((_HDMI_SUPPORT == _ON) && (_EDID_EXTERNAL_EEPROM_MAX_SIZE != _EDID_SIZE_NONE))
extern void UserCommonEdidHdmiExternalInfoParser(EnumInputPort enumInputPort);
#endif


#endif // End of #ifndef __USER_COMMON_EDID_H__
