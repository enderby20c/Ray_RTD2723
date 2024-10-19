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
// ID Code      : ScalerDMInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_DM_FUNCTION == _ON)
//--------------------------------------------------
// Definitions of max region index for DM
//--------------------------------------------------
#define _DM_MAX_REGION_COUNT                                2 // DM not support over 2P

//--------------------------------------------------
// Definitions of DM OUI
//--------------------------------------------------
#define _DM_OUI_0                                           0x46 // First sent byte
#define _DM_OUI_1                                           0xD0
#define _DM_OUI_2                                           0x00 // last sent byte

//--------------------------------------------------
// Definitions of DM Metadata Length
//--------------------------------------------------
#define _DM_VSIF_METADATA_LEN                               31
#define _DM_VSIF_METADATA_PB_LEN                            27
#define _DM_SDP_METADATA_LEN                                36
#define _DM_SDP_METADATA_PB_LEN                             32
#define _DM_EMP_METADATA_LEN                                44
#define _DM_EMP_METADATA_PB_LEN                             37
#define _DM_DRAM_METADATA_LEN                               32
#define _DM_DRAM_METADATA_PB_LEN                            28

//--------------------------------------------------
// Definitions of DM Judge Frame Count
//--------------------------------------------------
#define _DM_METADATA_MISS_TOLERANCE_CNT_1P                  1
#define _DM_METADATA_MISS_TOLERANCE_CNT_MTP                 2
#define _DM_FAULT_TOLERANCE_CNT                             6
#define _DM_UNMUTE_WAIT_FRAME_CNT                           2
#define _DM_UNMUTE_WAIT_MAINLOOP_CNT                        2

//--------------------------------------------------
// Macros of DM
//--------------------------------------------------
#define CLR_DM_VSIF_INFO_DATA_INDEX(index)                  (memset(&g_ppucDMVSIFMetadata[index], 0, _DM_VSIF_METADATA_LEN))
#define CLR_DM_SDP_INFO_DATA_INDEX(index)                   (memset(&g_ppucDMSDPMetadata[index], 0, _DM_SDP_METADATA_LEN))
#define CLR_DM_EMP_INFO_DATA_INDEX(index)                   (memset(&g_ppucDMEMPMetadata[index], 0, _DM_EMP_METADATA_LEN))
#define CLR_DM_DRAM_INFO_DATA_INDEX(index)                  (memset(&g_ppucDMDRAMMetadata[index], 0, _DM_DRAM_METADATA_LEN))

#define CLR_DM_METADATA_CHANGE_VSIF_INDEX(index)            (g_pstDMSettingInfo[index].b1MetadtaChangeVSIF = _FALSE)
#define CLR_DM_METADATA_CHANGE_EMP_INDEX(index)             (g_pstDMSettingInfo[index].b1MetadtaChangeEMP = _FALSE)
#define CLR_DM_METADATA_CHANGE_SDP_INDEX(index)             (g_pstDMSettingInfo[index].b1MetadtaChangeSDP = _FALSE)
#define CLR_DM_METADATA_CHANGE_HDMI_DRAM_INDEX(index)       (g_pstDMSettingInfo[index].b1MetadtaChangeHdmiDRAM = _FALSE)
#define CLR_DM_METADATA_CHANGE_DP_DRAM_INDEX(index)         (g_pstDMSettingInfo[index].b1MetadtaChangeDpDRAM = _FALSE)

#define CLR_DM_METADATA_ADDR_INDEX(index)                   (g_pstDMSettingInfo[index].ulMetadtaAddr = 0x00000000)

#define GET_DM_METADATA_MISS_CNT_INDEX(index)               (g_pstDMSettingInfo[index].b2MetadataMissCnt)
#define SET_DM_METADATA_MISS_CNT_INDEX(index)               (g_pstDMSettingInfo[index].b2MetadataMissCnt += 0x01)
#define CLR_DM_METADATA_MISS_CNT_INDEX(index)               (g_pstDMSettingInfo[index].b2MetadataMissCnt = 0x00)

#define GET_DM_METADATA_TYPE(index)                         (g_pstDMSettingInfo[index].enumDMMetadataType)
#define SET_DM_METADATA_TYPE(index, x)                      (g_pstDMSettingInfo[index].enumDMMetadataType = (x))
#define CLR_DM_METADATA_TYPE(index)                         (g_pstDMSettingInfo[index].enumDMMetadataType = _DM_METADATA_NONE)

#define GET_DM_INITIAL_READY_INDEX(index)                   (g_pstDMSettingInfo[index].b1InitialReady)
#define SET_DM_INITIAL_READY_INDEX(index)                   (g_pstDMSettingInfo[index].b1InitialReady = _TRUE)
#define CLR_DM_INITIAL_READY_INDEX(index)                   (g_pstDMSettingInfo[index].b1InitialReady = _FALSE)

#define GET_DM_METADATA_RECEIVED_INDEX(index)               (g_pstDMSettingInfo[index].b1DMReceived)
#define SET_DM_METADATA_RECEIVED_INDEX(index)               (g_pstDMSettingInfo[index].b1DMReceived = _TRUE)
#define CLR_DM_METADATA_RECEIVED_INDEX(index)               (g_pstDMSettingInfo[index].b1DMReceived = _FALSE)

#define GET_DM_INPUT_STATUS_INDEX(index)                    (g_pstDMSettingInfo[index].enumDMInputStatus)
#define SET_DM_INPUT_STATUS_INDEX(index, x)                 (g_pstDMSettingInfo[index].enumDMInputStatus = (x))

#define GET_DM_METADATA_SUPPORT_INDEX(index)                (g_pstDMSettingInfo[index].enumDMMetadataSupport)
#define SET_DM_METADATA_SUPPORT_INDEX(index, x)             (g_pstDMSettingInfo[index].enumDMMetadataSupport = (x))
#define CLR_DM_METADATA_SUPPORT_INDEX(index)                (g_pstDMSettingInfo[index].enumDMMetadataSupport = _DM_SUPPORT_OFF)

#define GET_DM_DRAM_SUPPORT_INDEX(index)                    (g_pstDMSettingInfo[index].enumDMDRAMSupport)
#define SET_DM_DRAM_SUPPORT_INDEX(index, x)                 (g_pstDMSettingInfo[index].enumDMDRAMSupport = (x))
#define CLR_DM_DRAM_SUPPORT_INDEX(index)                    (g_pstDMSettingInfo[index].enumDMDRAMSupport = _DM_SUPPORT_OFF)

#define SET_DM_OSD_CHANGE_INDEX(index)                      (g_pstDMSettingInfo[index].b1OSDChange = _TRUE)
#define GET_DM_OSD_CHANGE_INDEX(index)                      (g_pstDMSettingInfo[index].b1OSDChange)
#define CLR_DM_OSD_CHANGE_INDEX(index)                      (g_pstDMSettingInfo[index].b1OSDChange = _FALSE)

#define GET_DM_METADATA_ERROR_INDEX(index)                  (g_pstDMSettingInfo[index].b1MetadataError)
#define SET_DM_METADATA_ERROR_INDEX(index)                  (g_pstDMSettingInfo[index].b1MetadataError = _TRUE)
#define CLR_DM_METADATA_ERROR_INDEX(index)                  (g_pstDMSettingInfo[index].b1MetadataError = _FALSE)

#define GET_DM_BEC_STATUS_INDEX(index)                      (g_pstDMSettingInfo[index].enumDMBECStatus)
#define SET_DM_BEC_STATUS_INDEX(index, x)                   (g_pstDMSettingInfo[index].enumDMBECStatus = (x))

#define GET_DM_MUTE_STATUS_INDEX(index)                     (g_pstDMSettingInfo[index].enumDMMuteStatus)
#define SET_DM_MUTE_STATUS_INDEX(index, x)                  (g_pstDMSettingInfo[index].enumDMMuteStatus = (x))

#define GET_DM_PORT_INDEX(index)                            (g_pstDMSettingInfo[index].enumInputPort)
#define SET_DM_PORT_INDEX(index, x)                         (g_pstDMSettingInfo[index].enumInputPort = (x))
#define CLR_DM_PORT_INDEX(index)                            (g_pstDMSettingInfo[index].enumInputPort = _NO_INPUT_PORT)

#define GET_DM_UNMUTE_FRAME_CNT_INDEX(index)                (g_pstDMSettingInfo[index].b4UnmuteFrameCnt)
#define SET_DM_UNMUTE_FRAME_CNT_INDEX(index, x)             (g_pstDMSettingInfo[index].b4UnmuteFrameCnt = (x))
#define CLR_DM_UNMUTE_FRAME_CNT_INDEX(index)                (g_pstDMSettingInfo[index].b4UnmuteFrameCnt = 0x00)

#define GET_DM_UNMUTE_MAINLOOP_CNT_INDEX(index)             (g_pstDMSettingInfo[index].b4UnmuteMainloopCnt)
#define SET_DM_UNMUTE_MAINLOOP_CNT_INDEX(index, x)          (g_pstDMSettingInfo[index].b4UnmuteMainloopCnt = (x))
#define CLR_DM_UNMUTE_MAINLOOP_CNT_INDEX(index)             (g_pstDMSettingInfo[index].b4UnmuteMainloopCnt = 0x00)

#define GET_DM_MUTE_FLAG_INDEX(index)                       (g_pstDMSettingInfo[index].b1MuteFlag)
#define SET_DM_MUTE_FLAG_INDEX(index)                       (g_pstDMSettingInfo[index].b1MuteFlag = 0x01)
#define CLR_DM_MUTE_FLAG_INDEX(index)                       (g_pstDMSettingInfo[index].b1MuteFlag = 0x00)

#define GET_DM_UNMUTE_FLAG_INDEX(index)                     (g_pstDMSettingInfo[index].b1UnmuteFlag)
#define SET_DM_UNMUTE_FLAG_INDEX(index)                     (g_pstDMSettingInfo[index].b1UnmuteFlag = 0x01)
#define CLR_DM_UNMUTE_FLAG_INDEX(index)                     (g_pstDMSettingInfo[index].b1UnmuteFlag = 0x00)

#define GET_DM_HW_DISABLE_FLAG_INDEX(index)                 (g_pstDMSettingInfo[index].b1HWDisableFlag)
#define SET_DM_HW_DISABLE_FLAG_INDEX(index)                 (g_pstDMSettingInfo[index].b1HWDisableFlag = 0x01)
#define CLR_DM_HW_DISABLE_FLAG_INDEX(index)                 (g_pstDMSettingInfo[index].b1HWDisableFlag = 0x00)

#define GET_DM_MAIN_SUB_SYNC()                              (g_bDMMainSubSync)
#define SET_DM_MAIN_SUB_SYNC()                              (g_bDMMainSubSync = _TRUE)
#define CLR_DM_MAIN_SUB_SYNC()                              (g_bDMMainSubSync = _FALSE)

#define GET_DM_PICTURE_MODE_INDEX(index)                    ((BYTE)(g_pstDMSettingInfo[index].stDMOSDColorSetting.stDMOsdSetting.lDMPictureMode))
#define SET_DM_PICTURE_MODE_INDEX(index, x)                 (g_pstDMSettingInfo[index].stDMOSDColorSetting.stDMOsdSetting.lDMPictureMode = ((SDWORD)(x)))

#if(_DM_CONFIG_GAME_MODE_INDEX != _DM_PICTURE_MODE_NONE)
#define GET_DM_BACKUP_NORMAL_MODE_INDEX(index)              (g_pstDMSettingInfo[index].ucNormalModeIndex)
#define SET_DM_BACKUP_NORMAL_MODE_INDEX(index, x)           (g_pstDMSettingInfo[index].ucNormalModeIndex = (x))
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Enumerations of DM mute/unmute Type
//--------------------------------------------------
typedef enum
{
    _DM_NO_MUTE,  // No mute Status
    _DM_OUT_UNMUTE_READY, // Ready to unmute
    _DM_IN_UNMUTE_READY, // Ready to unmute
    _DM_OUT_MUTE, // DM/DM_GAME to Non-DM
    _DM_IN_MUTE,  // Non-DM to DM/DM_GAME
    _DM_OSD_MUTE, // OSD DM/DM_GAME to DM/DM_GAME
} EnumDMMuteStatus;

typedef struct
{
    Struct3rdPartyDMOsdSetting stDMOsdSetting;
} StructColorDMOsdSetting;

//--------------------------------------------------
// Enumerations of BEC Status
//--------------------------------------------------
typedef enum
{
    _DM_BEC_INIT,
    _DM_BEC_PREPARATIVE,
    _DM_BEC_BUSY,
    _DM_BEC_DONE,
} EnumDMBECStatus;

//--------------------------------------------------
// Enumerations of DM Info Received Entry
//--------------------------------------------------
typedef enum
{
    _DM_METADATA_NONE = 0x00,
    _HDMI_DM_DRAM_ENTRY = 0x01,
    _HDMI_DM_EMP_ENTRY = 0x02,
    _DP_DM_SDP_ENTRY = 0x03,
    _DP_DM_EXT_SDP_ENTRY = 0x04,
    _DP_DM_DRAM_ENTRY = 0x05,
    _HDMI_DM_PKT_ENTRY = 0x06,
} EnumDMReceivedType;

//--------------------------------------------------
// Enumerations of DM Checkpoint
//--------------------------------------------------
typedef enum
{
    _DM_CHK_INIT,
    _DM_CHK_FIRST_ACTIVE,
    _DM_CHK_DSP,
} EnumDMCheckPoint;

//--------------------------------------------------
// Structure of DM Setting Info
//--------------------------------------------------
typedef struct
{
    BYTE b1MetadtaChangeVSIF : 1;
    BYTE b1MetadtaChangeEMP : 1;
    BYTE b1MetadtaChangeSDP : 1;
    BYTE b1MetadtaChangeHdmiDRAM : 1;
    BYTE b1MetadtaChangeDpDRAM : 1;

    BYTE b1InitialReady : 1;
    BYTE b1OSDChange : 1;
    BYTE b1DMReceived : 1;
    BYTE b1MetadataError : 1;
    BYTE b1MuteFlag : 1;
    BYTE b1UnmuteFlag : 1;
    BYTE b1HWDisableFlag : 1;
    BYTE b2MetadataMissCnt : 2;

    BYTE b4UnmuteFrameCnt : 4;
    BYTE b4UnmuteMainloopCnt : 4;

    BYTE ucFrameCnt;

#if(_DM_CONFIG_GAME_MODE_INDEX != _DM_PICTURE_MODE_NONE)
    BYTE ucNormalModeIndex;
#endif

    DWORD ulMetadtaAddr;

    EnumDMBECStatus enumDMBECStatus;
    EnumDMMuteStatus enumDMMuteStatus;
    EnumDMSupport enumDMMetadataSupport;
    EnumDMSupport enumDMDRAMSupport;
    EnumDMStatus enumDMInputStatus;
    EnumInputPort enumInputPort;
    EnumDMReceivedType enumDMMetadataType;

    EnumColorSpace enumDMColorSpace;
    BYTE ucDMColorDepth;

    StructColorDMOsdSetting stDMOSDColorSetting;
} StructDMSettingInfo;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern volatile StructDMSettingInfo g_pstDMSettingInfo[_DM_MAX_REGION_COUNT];

extern volatile BYTE g_ppucDMVSIFMetadata[_DM_MAX_REGION_COUNT][_DM_VSIF_METADATA_LEN];
extern volatile BYTE g_ppucDMSDPMetadata[_DM_MAX_REGION_COUNT][_DM_SDP_METADATA_LEN];
extern volatile BYTE g_ppucDMEMPMetadata[_DM_MAX_REGION_COUNT][_DM_EMP_METADATA_LEN];
extern volatile BYTE g_ppucDMDRAMMetadata[_DM_MAX_REGION_COUNT][_DM_DRAM_METADATA_LEN];

extern volatile bit g_bDMMainSubSync;

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern BYTE ScalerDMGetFrameCnt(EnumDisplayRegion enumDisplayRegion);
extern void ScalerDMBackgroundEnable(EnumDisplayRegion enumDisplayRegion, bit bEnable);

#if(_IS_MAIN_PROCESS_CPU == _FALSE)
extern bit ScalerDMRunBEC(EnumDisplayRegion enumDisplayRegion, BYTE ucInbit, EnumColorSpace enumColorSpace);
extern void ScalerDMSCPUInit(void);
#endif

#if(_IS_MAIN_PROCESS_CPU == _TRUE)
extern void ScalerDMInitial(void);
extern bit ScalerDMStatusChange(EnumDisplayRegion enumDisplayRegion);
extern void ScalerDMB05DoubleBufferEnable(EnumDisplayRegion enumDisplayRegion, bit bEn);
extern void ScalerDMDisable(EnumInputDataPath enumInputDataPath);
extern void ScalerDMSyncMainSubData(void);
#endif
#endif
