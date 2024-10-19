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
// ID Code      : UserCommonEdidInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if((_HLG_SUPPORT == _ON) || (_HDMI21_RX_DSC_DECODER_SUPPORT == _ON) || (_HDMI_FREESYNC_SUPPORT == _ON) || (_AUDIO_ARC_SUPPORT == _ON))
extern void UserCommonEdidRemoveCtaDataBlockProc(BYTE *pucDdcRamAddr, WORD *pusCtaDataBlockAddr, EnumEdidCtaDataBlock enumCtaDataBlock);
extern bit UserCommonEdidAddCtaDataBlockProc(BYTE *pucDdcRamAddr, WORD *pusCtaDataBlockAddr, EnumEdidCtaDataBlock enumCtaDataBlock, BYTE *pucAddCtaDataBlock);
#endif

#if(_EMBEDDED_EDID_SUPPORT == _ON)
extern void UserCommonEdidLoadEmbeddedEdidData(void);
extern void UserCommonEdidLoadEmbeddedEdidDataByPort(EnumInputPortEdid enumInputPort);
extern BYTE *UserCommonEdidGetDDCRamAddress(EnumInputPort enumInputPort);

#if((_HDMI_EXTERNAL_SWITCH_SUPPORT == _ON) && ((_D3_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) || (_D4_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)))
extern void UserCommonEdidReloadHdmiExternalSwitchEmbeddedEdid(EnumInputPort enumInputPort);
#endif
#endif

extern EnumHdmiEdidLocation UserCommonEdidCheckHdmiCurrentEdidLocation(EnumInputPort enumInputPort);

#if(_HDMI_MULTI_EDID_SUPPORT == _ON)
extern void UserCommonEdidMultiHdmiEdidInitial(void);
#endif

#if((_HDMI_SUPPORT == _ON) && (_EDID_EXTERNAL_EEPROM_MAX_SIZE != _EDID_SIZE_NONE))
extern void UserCommonEdidHdmiAllPortExternalEdidParser(void);
#endif

#if(_DP_SUPPORT == _ON)
#if(_EMBEDDED_EDID_SUPPORT == _ON)
#if(_DUAL_DP_SUPPORT == _ON)
extern void UserCommonEdidDpDualPortEdidTableSwitch(EnumInputPort enumInputPort);
extern bit UserCommonEdidDpGetDualPortEdidSelectStatus(void);
#endif
#endif
#endif

