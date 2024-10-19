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
// ID Code      : UserCommonEdidInterface_User.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions of HDMI Multi Edid Switch Related
//--------------------------------------------------
#define _HDMI_EXT_EDID_MAX_CNT                          12

//--------------------------------------------------
// Enumerations Load EDID Port Selection
//--------------------------------------------------
typedef enum
{
    _A0_INPUT_PORT_EDID = _A0_INPUT_PORT,
    _D0_INPUT_PORT_EDID = _D0_INPUT_PORT,
    _D1_INPUT_PORT_EDID = _D1_INPUT_PORT,
    _D2_INPUT_PORT_EDID = _D2_INPUT_PORT,
    _D3_INPUT_PORT_EDID = _D3_INPUT_PORT,
    _D4_INPUT_PORT_EDID = _D4_INPUT_PORT,
    _D5_INPUT_PORT_EDID = _D5_INPUT_PORT,
    _D6_INPUT_PORT_EDID = _D6_INPUT_PORT,
    _D7_INPUT_PORT_EDID = _D7_INPUT_PORT,
    _D8_INPUT_PORT_EDID = _D8_INPUT_PORT,
    _D9_INPUT_PORT_EDID = _D9_INPUT_PORT,
} EnumInputPortEdid;

//--------------------------------------------------
// Enumerations of Edid Index
// For RTD User Only Use 0~11 Index
//--------------------------------------------------
typedef enum
{
    _EDID_INDEX_0 = 0,
    _EDID_INDEX_1,
    _EDID_INDEX_2,
    _EDID_INDEX_3,
    _EDID_INDEX_4,
    _EDID_INDEX_5,
    _EDID_INDEX_6,
    _EDID_INDEX_7,
    _EDID_INDEX_8,
    _EDID_INDEX_9,
    _EDID_INDEX_10,
    _EDID_INDEX_11,
    _EDID_INDEX_12,
    _EDID_INDEX_13,
    _EDID_INDEX_14,
    _EDID_INDEX_15,
}EnumEdidSelection;

//--------------------------------------------------
// Enumerations of HDMI Edid Location
//--------------------------------------------------
typedef enum
{
    _HDMI_EDID_EXTERNAL = 0,
    _HDMI_EDID_EMBEDDED,
}EnumHdmiEdidLocation;

//--------------------------------------------------
// Enumerations of HDMI Edid Switch's HPD Toggle behavior
//--------------------------------------------------
typedef enum
{
    _EDID_HPD_KEEP_ACTIVE = 0,
    _EDID_HPD_RETURN_SEARCH,
}EnumHdmiEdidHpdBehavior;

//--------------------------------------------------
// Enumerations of HDMI Edid Switch's HPD Toggle behavior
//--------------------------------------------------
typedef enum
{
    _EDID_DONOT_CHANGE = 0,
    _EDID_NEED_CHANGE,
}EnumEdidReloadCheck;

//--------------------------------------------------
// Struct of DSC HDMI EDID Modifty Parameter
//--------------------------------------------------
typedef struct
{
    BYTE b4DscMaxFrlRate : 4;
    BYTE b4DscMaxSlice : 4;
    BYTE b6DscTotalChunkKByte : 6;
    BYTE b1DscAllBpp : 1;
    BYTE b1Dsc12bpc : 1;
    BYTE b1DscNative420 : 1;
    BYTE b1Dsc10bpc : 1;
} StructDscHdmiEdidModifyParameter;

//--------------------------------------------------
// Definitions of EDID Modify Target
//--------------------------------------------------
typedef enum
{
    _EDID_MODIFY_NONE = 0,
    _EDID_MODIFY_HLG = _BIT0,
    _EDID_MODIFY_HDMI_DSC = _BIT1,
    _EDID_MODIFY_HDMI_FREESYNC_MCCS = _BIT2,
    _EDID_MODIFY_AUDIO_CAPABILITY = _BIT3,
} EnumEdidModifyTarget;

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
#if(_AUDIO_ARC_SUPPORT == _ON)
typedef enum
{
    _CTA_TAG_NONE = 0x00,
    _CTA_TAG_ADB = 0x20,
    _CTA_ADB_DES = _CTA_TAG_ADB + 1,
    _CTA_TAG_VDB = 0x40,
    _CTA_VDB_VIC = _CTA_TAG_VDB + 1,
    _CTA_TAG_VSDB = 0x60,
    _CTA_VSDB_ID = _CTA_TAG_VSDB,
    _CTA_VSDB_PA = _CTA_TAG_VSDB + 1,
    _CTA_VSDB_CLR_DE = _CTA_TAG_VSDB + 2,
    _CTA_VSDB_TMDS_CLK = _CTA_TAG_VSDB + 3,
    _CTA_VSDB_HDMI_PRE = _CTA_TAG_VSDB + 4,
    _CTA_VSDB_LATENCY = _CTA_TAG_VSDB + 5,
    _CTA_VSDB_3D = _CTA_TAG_VSDB + 6,
    _CTA_VSDB_4K2K = _CTA_TAG_VSDB + 7,
    _CTA_VSDB_STRUCT = _CTA_TAG_VSDB + 9,
    _CTA_VSDB_HFVSDB = _CTA_TAG_VSDB + 0x0A,
    _CTA_VSDB_DONE = _CTA_TAG_VSDB + 0x1F,
    _CTA_MODE_SPK = 0x80,
    _CTA_MODE_DTC = 0xA0,
    _CTA_MODE_REV = 0xC0,
    _CTA_MODE_EXT = 0xE0,
    _CTA_EXT_VCDB = _CTA_MODE_EXT + 0x00,
    _CTA_EXT_CDB = _CTA_MODE_EXT + 0x05,
    _CTA_EXT_HDRSMDB = _CTA_MODE_EXT + 0x06,
    _CTA_EXT_Y420VDB = _CTA_MODE_EXT + 0x0E,
    _CTA_EXT_Y420CMDB = _CTA_MODE_EXT + 0x0F,
    _CTA_EXT_HFSCDB = _CTA_MODE_EXT + 0x19,
} EnumEdidCtaTagType;
#endif // End of #if(_AUDIO_ARC_SUPPORT == _ON)


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if((_HLG_SUPPORT == _ON) || (_HDMI21_RX_DSC_DECODER_SUPPORT == _ON) || (_HDMI_FREESYNC_SUPPORT == _ON) || (_AUDIO_ARC_SUPPORT == _ON))
extern bit UserCommonEdidOnlineEdidModify(BYTE *pucEdidAddr, EnumEdidModifyTarget enumEdidModifyTarget);
#endif

#if(_HDMI_MULTI_EDID_SUPPORT == _ON)
#if((_TMDS_FS_ON_ONLY_TARGETPORT_HPD_SUPPORT == _ON) && (_HDMI_FREESYNC_SUPPORT == _ON))
extern void UserCommonEdidSwitchHdmiAllPortEdidToggleTargetPortHpd(void);
#endif
extern void UserCommonEdidSwitchHdmiEdid(EnumInputPort enumInputPort, EnumEdidSelection enumHDMIEDIDSelection);
extern void UserCommonEdidSwitchHdmiAllPortEdid(void);
extern EnumHdmiEdidLocation UserCommonEdidGetMultiHdmiEdidLocation(EnumInputPort enumInputPort, EnumEdidSelection enumHDMIEDIDSelection);
#endif

#if(_DP_SUPPORT == _ON)
#if(_EMBEDDED_EDID_SUPPORT == _ON)
extern void UserCommonEdidSwitchDpEdid(BYTE ucSelectedPort);
extern void UserCommonEdidSwitchDpAllPortEdid(void);
#endif
#endif

