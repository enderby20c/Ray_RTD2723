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
// ID Code      : ScalerDM.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_DM__

#include "ScalerFunctionInclude.h"
#include "DM/ScalerDM.h"

#if(_DM_FUNCTION == _ON)
#if(_DM_FUNCTION_BYPASS_HW_APPLY == _ON)
#warning "_DM_FUNCTION_BYPASS_HW_APPLY is only for testing, should be _OFF in MP FW!!!"
#endif
#endif

#if(_DM_FUNCTION == _ON)
//****************************************************************************
// CODE TABLES
//****************************************************************************
BYTE code tDMConfigTable[] =
{
#include _DM_CONFIG_TABLE
};

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
volatile StructDMSettingInfo g_pstDMSettingInfo[_DM_MAX_REGION_COUNT];
volatile Struct3rdPartyDMDRM g_stDMDRMFormat;

volatile BYTE g_ppucDMVSIFMetadata[_DM_MAX_REGION_COUNT][_DM_VSIF_METADATA_LEN];
volatile BYTE g_ppucDMSDPMetadata[_DM_MAX_REGION_COUNT][_DM_SDP_METADATA_LEN];
volatile BYTE g_ppucDMEMPMetadata[_DM_MAX_REGION_COUNT][_DM_EMP_METADATA_LEN];
volatile BYTE g_ppucDMDRAMMetadata[_DM_MAX_REGION_COUNT][_DM_DRAM_METADATA_LEN];

volatile bit g_bDMMainSubSync;

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : DM Register page select
// Input Value  : EnumDisplayRegion
// Output Value : None
//--------------------------------------------------
void ScalerDMHWApplyPathSelect(EnumInputDataPath enumInputDataPath)
{
    DWORD ulPageSelect = 0;

    if((enumInputDataPath & _INPUT_PATH_M1) != 0x00)
    {
        ulPageSelect |= _BIT0;
    }

    if((enumInputDataPath & _INPUT_PATH_M2) != 0x00)
    {
        ulPageSelect |= _BIT1;
    }

    if((enumInputDataPath & _INPUT_PATH_S1) != 0x00)
    {
        ulPageSelect |= _BIT2;
    }

    if((enumInputDataPath & _INPUT_PATH_S2) != 0x00)
    {
        ulPageSelect |= _BIT3;
    }

    Scaler32SetDWord(PB00308_00_DM_REG_PAGE_SET, ulPageSelect);
}

//--------------------------------------------------
// Description  : DM Frame Count
// Input Value  : EnumDisplayRegion
// Output Value : frame cnt
//--------------------------------------------------
BYTE ScalerDMGetFrameCnt(EnumDisplayRegion enumDisplayRegion)
{
    ScalerDMHWApplyPathSelect(ScalerRegionGetInputDataPath(enumDisplayRegion));

    return Scaler32GetByte(PB00304_00_DM_SUBMODULE_ENABLE_00, 0x03);
}

//--------------------------------------------------
// Description  : Turn on Background to do DM mute
// Input Value  : enumDisplayRegion
// Output Value : T/F
//--------------------------------------------------
void ScalerDMBackgroundEnable(EnumDisplayRegion enumDisplayRegion, bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        ScalerDDomainBackgroundEnable(ScalerRegionGetDDomainRegion(enumDisplayRegion), _ENABLE);

        // if local dimming is enable, use IPG to force data to black
#if(_LOCAL_DIMMING_FUNCTION == _ON)
        if(ScalerColorLDBLModelGetEnableStatus() == _TRUE)
        {
            ScalerIDomainPatternGenEnable(ScalerRegionGetInputDataPath(enumDisplayRegion), _ENABLE);
        }
#endif
    }
    else
    {
#if(_LOCAL_DIMMING_FUNCTION == _ON)
        ScalerIDomainPatternGenEnable(ScalerRegionGetInputDataPath(enumDisplayRegion), _DISABLE);
#endif
        ScalerDDomainBackgroundEnable(ScalerRegionGetDDomainRegion(enumDisplayRegion), _DISABLE);
    }
}

//--------------------------------------------------
// Description  : Get DDomainRegion DM mute status
// Input Value  : None
// Output Value : EnumDDomainRegion : which DDomainRegions are DM mute
//--------------------------------------------------
EnumDDomainRegion ScalerDMGetDDomainRegionMuteStatus(void)
{
    // check max DM support region
    if(ScalerRegionGetMaxRegionCount() > _DM_MAX_REGION_COUNT)
    {
        return _DDOMAIN_RGN_NONE;
    }

    EnumDDomainRegion enumDMMuteDDomainRegion = _DDOMAIN_RGN_NONE;
    switch(GET_DISPLAY_MODE())
    {
        case _DISPLAY_MODE_1P:
            if(GET_DM_MUTE_STATUS_INDEX(0) != _DM_NO_MUTE)
            {
                enumDMMuteDDomainRegion |= _DDOMAIN_RGN_R1_A1;
            }
            break;
#if(_2P_DISPLAY_SUPPORT == _ON)
#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PIP:
#endif
#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PBP_LR_EQUAL:
        case _DISPLAY_MODE_2P_PBP_LR_L_LARGE:
        case _DISPLAY_MODE_2P_PBP_LR_R_LARGE:
#endif
#if(_2P_PBP_TB_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PBP_TB:
#endif
            if(GET_DM_MUTE_STATUS_INDEX(0) != _DM_NO_MUTE)
            {
                enumDMMuteDDomainRegion |= _DDOMAIN_RGN_R1_A1;
            }
            if(GET_DM_MUTE_STATUS_INDEX(1) != _DM_NO_MUTE)
            {
                enumDMMuteDDomainRegion |= _DDOMAIN_RGN_R1_A2;
            }
            break;
#if(_EAGLE_SIGHT_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT:
            if(GET_DM_MUTE_STATUS_INDEX(0) != _DM_NO_MUTE)
            {
                enumDMMuteDDomainRegion |= _DDOMAIN_RGN_R1_A1;
                enumDMMuteDDomainRegion |= _DDOMAIN_RGN_R1_A2;
            }
            break;
#endif
#endif // End of #if(_2P_DISPLAY_SUPPORT == _ON)
        default:
            break;
    }

    return enumDMMuteDDomainRegion;
}

#if(_IS_MAIN_PROCESS_CPU == _FALSE)
//--------------------------------------------------
// Description  : Setting Metadata source priority
// Input Value  : display mode, metadata from interface
// Output Value : successfully get metadata addr or not
//--------------------------------------------------
bit ScalerDMSwitchRSV(EnumRegionIndex enumRegionIndex, DWORD *pulRSVAddr, bit bOsdChange)
{
    if(bOsdChange == _TRUE)
    {
        switch(GET_DM_METADATA_TYPE(enumRegionIndex))
        {
            case _HDMI_DM_PKT_ENTRY:
                *pulRSVAddr = (DWORD)(&g_ppucDMVSIFMetadata[enumRegionIndex][0]);
                DebugMessageDM("DM_TR9_SwitchRSV_OSD_VSIF", _HDMI_DM_PKT_ENTRY);
                return _TRUE;
                break;
            case _DP_DM_SDP_ENTRY:
            case _DP_DM_EXT_SDP_ENTRY:
                *pulRSVAddr = (DWORD)(&g_ppucDMSDPMetadata[enumRegionIndex][0]);
                DebugMessageDM("DM_TR9_SwitchRSV_OSD_SDP", GET_DM_METADATA_TYPE(enumRegionIndex));
                return _TRUE;
                break;
            case _HDMI_DM_EMP_ENTRY:
                *pulRSVAddr = (DWORD)(&g_ppucDMEMPMetadata[enumRegionIndex][0]);
                DebugMessageDM("DM_TR9_SwitchRSV_OSD_EMP", _HDMI_DM_EMP_ENTRY);
                return _TRUE;
                break;
            case _HDMI_DM_DRAM_ENTRY:
                *pulRSVAddr = (DWORD)(&g_ppucDMDRAMMetadata[enumRegionIndex][0]);
                DebugMessageDM("DM_TR9_SwitchRSV_OSD_HDMI_DRAM", _HDMI_DM_DRAM_ENTRY);
                return _TRUE;
                break;
            case _DP_DM_DRAM_ENTRY:
                *pulRSVAddr = (DWORD)(&g_ppucDMDRAMMetadata[enumRegionIndex][0]);
                DebugMessageDM("DM_TR9_SwitchRSV_OSD_DP_DRAM", _DP_DM_DRAM_ENTRY);
                return _TRUE;
                break;
            default:
                return _FALSE;
                break;
        }
    }
    else
    {
        bit bFlag = _FALSE;

        if(g_pstDMSettingInfo[enumRegionIndex].b1MetadtaChangeVSIF == _TRUE) // VSIF
        {
            *pulRSVAddr = (DWORD)(&g_ppucDMVSIFMetadata[enumRegionIndex][0]);
            SET_DM_METADATA_TYPE(enumRegionIndex, _HDMI_DM_PKT_ENTRY);
            g_pstDMSettingInfo[enumRegionIndex].b1MetadtaChangeVSIF = _FALSE;
            DebugMessageDM("DM_TR9_SwitchRSV_VSIF", _HDMI_DM_PKT_ENTRY);
            bFlag = _TRUE;
        }
        else if(g_pstDMSettingInfo[enumRegionIndex].b1MetadtaChangeSDP == _TRUE) // SDP, EXT SDP
        {
            *pulRSVAddr = (DWORD)(&g_ppucDMSDPMetadata[enumRegionIndex][0]);
            SET_DM_METADATA_TYPE(enumRegionIndex, _DP_DM_SDP_ENTRY);
            g_pstDMSettingInfo[enumRegionIndex].b1MetadtaChangeSDP = _FALSE;
            DebugMessageDM("DM_TR9_SwitchRSV_SDP", GET_DM_METADATA_TYPE(enumRegionIndex));
            bFlag = _TRUE;
        }
        else if(g_pstDMSettingInfo[enumRegionIndex].b1MetadtaChangeEMP == _TRUE) // EMP
        {
            *pulRSVAddr = (DWORD)(&g_ppucDMEMPMetadata[enumRegionIndex][0]);
            SET_DM_METADATA_TYPE(enumRegionIndex, _HDMI_DM_EMP_ENTRY);
            g_pstDMSettingInfo[enumRegionIndex].b1MetadtaChangeEMP = _FALSE;
            DebugMessageDM("DM_TR9_SwitchRSV_EMP", _HDMI_DM_EMP_ENTRY);
            bFlag = _TRUE;
        }
        else if(g_pstDMSettingInfo[enumRegionIndex].b1MetadtaChangeHdmiDRAM == _TRUE) // HDMI DRAM
        {
            *pulRSVAddr = (DWORD)(&g_ppucDMDRAMMetadata[enumRegionIndex][0]);
            SET_DM_METADATA_TYPE(enumRegionIndex, _HDMI_DM_DRAM_ENTRY);
            g_pstDMSettingInfo[enumRegionIndex].b1MetadtaChangeHdmiDRAM = _FALSE;
            DebugMessageDM("DM_TR9_SwitchRSV_HDMI_DRAM", _HDMI_DM_DRAM_ENTRY);
            bFlag = _TRUE;
        }
        else if(g_pstDMSettingInfo[enumRegionIndex].b1MetadtaChangeDpDRAM == _TRUE) // DP DRAM
        {
            *pulRSVAddr = (DWORD)(&g_ppucDMDRAMMetadata[enumRegionIndex][0]);
            SET_DM_METADATA_TYPE(enumRegionIndex, _DP_DM_DRAM_ENTRY);
            g_pstDMSettingInfo[enumRegionIndex].b1MetadtaChangeDpDRAM = _FALSE;
            DebugMessageDM("DM_TR9_SwitchRSV_DP_DRAM", _DP_DM_DRAM_ENTRY);
            bFlag = _TRUE;
        }
        else
        {
            bFlag = _FALSE;
        }

        g_pstDMSettingInfo[enumRegionIndex].b1MetadtaChangeVSIF = _FALSE;
        g_pstDMSettingInfo[enumRegionIndex].b1MetadtaChangeSDP = _FALSE;
        g_pstDMSettingInfo[enumRegionIndex].b1MetadtaChangeEMP = _FALSE;
        g_pstDMSettingInfo[enumRegionIndex].b1MetadtaChangeHdmiDRAM = _FALSE;
        g_pstDMSettingInfo[enumRegionIndex].b1MetadtaChangeDpDRAM = _FALSE;

        return bFlag;
    }
}

//--------------------------------------------------
// Description  : Setting DM inforframe
// Input Value  : inbit, color space, hight, width
// Output Value : successfully set from infoframe data or not
//--------------------------------------------------
bit ScalerDMSwitchIDK(BYTE ucInbit, EnumColorSpace enumColorSpace, WORD usHWidth, WORD usVHeight, char *pDMArgv[])
{
    BYTE ucCnt = 0;

    for(ucCnt = 0; ucCnt < _SIZE_OF_INFOFRAME; ucCnt++)
    {
        memset(&pDMArgv[ucCnt], 0, sizeof(pDMArgv[ucCnt]));
    }

    switch (ucInbit)
    {
        case 8:
        case 10:
        case 12:
            pDMArgv[5] = "12";
            break;

        default:
            return _FALSE;
    }

    switch (enumColorSpace)
    {
        case _COLOR_SPACE_RGB:
            pDMArgv[7] = "rgb";
            pDMArgv[9] = "444";
            break;

        case _COLOR_SPACE_YCBCR422:
        case _COLOR_SPACE_YCBCR420:
            pDMArgv[7] = "yuv";
            pDMArgv[9] = "422";
            break;

        case _COLOR_SPACE_YCBCR444:
            pDMArgv[7] = "rgb"; // Dolby's patch , BEC do not has YUV444 input case, need to force to RGB444
            pDMArgv[9] = "444";
            break;

        case _COLOR_SPACE_YPBPR:
        case _COLOR_SPACE_Y_ONLY:
        case _COLOR_SPACE_RAW:
        default:
            return _FALSE;
    }

    if((usHWidth == 1920) && (usVHeight == 1080))
    {
        pDMArgv[13] = "1920x1080";
    }
    else if((usHWidth == 2560) && (usVHeight == 1440))
    {
        pDMArgv[13] = "2560x1440";
    }
    else if((usHWidth == 3840) && (usVHeight == 2160))
    {
        pDMArgv[13] = "3840x2160";
    }
    else
    {
        pDMArgv[13] = "1920x1080";
    }

    pDMArgv[0] = "control_path_test";
    pDMArgv[1] = "-hdmi";
    pDMArgv[2] = "-if";
    pDMArgv[3] = "dovi";
    pDMArgv[4] = "-sbd";
    // pDMArgv[5] = "12";
    pDMArgv[6] = "-sclr";
    // pDMArgv[7] = "rgb";
    pDMArgv[8] = "-schrm";
    // pDMArgv[9] = "444";
    pDMArgv[10] = "-tid";
    pDMArgv[11] = "2";
    pDMArgv[12] = "-r";
    // pDMArgv[13] = "1920x1080";

    return _TRUE;
}

//--------------------------------------------------
// Description  : prepare metadata/OSD data for BEC source code
// Input Value  : EnumDisplayRegion, ucinbit, ucColorSpace
// Output Value : None
//--------------------------------------------------
bit ScalerDMRunBEC(EnumDisplayRegion enumDisplayRegion, BYTE ucInbit, EnumColorSpace enumColorSpace)
{
    EnumRegionIndex enumRegionIndex = ScalerRegionGetIndex(enumDisplayRegion);

    if(enumRegionIndex > 1)
    {
        return _FALSE;
    }

    char *pucInfoFrame[_SIZE_OF_INFOFRAME];
    bit bMetadataStatus = _FALSE;
    bit bInfoFrameStatus = _FALSE;

    bMetadataStatus = ScalerDMSwitchRSV(enumRegionIndex, &(g_pstDMSettingInfo[enumRegionIndex].ulMetadtaAddr), GET_DM_OSD_CHANGE_INDEX(enumRegionIndex));

    bInfoFrameStatus = ScalerDMSwitchIDK(ucInbit, enumColorSpace, g_pstMeasureRegionTimingInfo[enumRegionIndex].stTimingInfo.usHWidth, g_pstMeasureRegionTimingInfo[enumRegionIndex].stTimingInfo.usVHeight, pucInfoFrame);

    if((bMetadataStatus == _TRUE) && (bInfoFrameStatus == _TRUE))
    {
#if(_DM_FUNCTION_BYPASS_HW_APPLY == _OFF)
        __attribute__((aligned(_BURST_WRITE32_DATA_ALIGNMENT)))
        StructBW32CmdUnitFormat pstDMB0501[_SIZE_OF_DM_B0501];
        DWORD pulDMRegister[_SIZE_OF_DM_REG] = {0};
        DWORD pulDMB0103[_SIZE_OF_DM_B0103] = {0};
        DWORD pulDMB02[_SIZE_OF_DM_B02] = {0};
        Enum3rdPartyDMControlPathStatus enumDMControlPathResult = _DM_CONTROL_PATH_FAIL;

#if(_DM_CONFIG_GAME_MODE_INDEX != _DM_PICTURE_MODE_NONE)
        if(GET_DM_OSD_CHANGE_INDEX(enumRegionIndex) == _FALSE)
        {
            if(GET_DM_INPUT_STATUS_INDEX(enumRegionIndex) == _DM_ON_GAME)
            {
                SET_DM_PICTURE_MODE_INDEX(enumRegionIndex, _DM_CONFIG_GAME_MODE_INDEX);
            }
            else
            {
                SET_DM_PICTURE_MODE_INDEX(enumRegionIndex, GET_DM_BACKUP_NORMAL_MODE_INDEX(enumRegionIndex));
            }
        }
#endif

        DebugMessageDM("DM_TR9_PictureMode", (g_pstDMSettingInfo[enumRegionIndex].stDMOSDColorSetting.stDMOsdSetting.lDMPictureMode));

        enumDMControlPathResult = DMControlPathTest(pulDMRegister, pulDMB0103, pulDMB02, pstDMB0501, (BYTE *)(g_pstDMSettingInfo[enumRegionIndex].ulMetadtaAddr),
                                                    tDMConfigTable, pucInfoFrame, _SIZE_OF_INFOFRAME, &(g_pstDMSettingInfo[enumRegionIndex].stDMOSDColorSetting.stDMOsdSetting));

        DebugMessageDM("DM_TR9_DMControlPathTest", enumDMControlPathResult);

        if(enumDMControlPathResult == _DM_CONTROL_PATH_SUCCESS)
        {
            ScalerDMHWApply(enumDisplayRegion, enumColorSpace, pulDMRegister, pulDMB02, pstDMB0501);
            CLR_DM_METADATA_ERROR_INDEX(enumRegionIndex);
            DebugMessageDM("DM_TR9_HW_Apply_Done", 0);

            return _TRUE;
        }
        else
        {
            DebugMessageDM("DM_TR9_HW_Apply_False", 0);
            return _FALSE;
        }
#else
        DebugMessageDM("DM_TR9_Bypass_HW_Apply", 1);
        return _TRUE;
#endif
    }
    else
    {
        return _FALSE;
    }
}

//--------------------------------------------------
// Description  : DM HW apply
// Input Value  : EnumDisplayRegion, ucColorSpace
// Output Value : None
//--------------------------------------------------
void ScalerDMHWApply(EnumDisplayRegion enumDisplayRegion, EnumColorSpace enumColorSpace, DWORD *pulDMRegister, DWORD *pulDMB02, StructBW32CmdUnitFormat *pstDMB0501)
{
    WORD usCnt = 0;
    bit bB02Sel = _FALSE;
    EnumInputDataPath enumInputDataPath = ScalerRegionGetInputDataPath(enumDisplayRegion);

#if(_EAGLE_SIGHT_SUPPORT == _ON)
    if((enumDisplayRegion == _DISPLAY_RGN_EAGLE_SIGHT_MAIN) && (GET_DM_MAIN_SUB_SYNC() == _TRUE))
    {
        enumInputDataPath |= ScalerRegionGetInputDataPath(GET_RGN_DISPLAY_REGION(_REGION_INDEX_1));
        DebugMessageDM("DM_TR9_Main/Sub_Sync", enumInputDataPath);
    }
#endif

    ScalerDMHWApplyPathSelect(enumInputDataPath);
    // sel B02 1:FW access table 1, HW access table 0
    // sel B02 0:FW access table 0, HW access table 1
    if(Scaler32GetBit(PB00305_C0_DM_B02_LUT_CTRL0, _BIT2) == 0)
    {
        bB02Sel = _TRUE;
    }
    else
    {
        bB02Sel = _FALSE;
    }

    // Maintain B05 DB Status
    if((Scaler32GetDWord(PB00304_00_DM_SUBMODULE_ENABLE_00) & _BIT17) == _BIT17)
    {
        pulDMRegister[1] |= _BIT17;
        DebugMessageDM("DM_TR9_B05_DB_On_Already", Scaler32GetDWord(PB00304_00_DM_SUBMODULE_ENABLE_00));
    }

    for(usCnt = 0; usCnt < _SIZE_OF_DM_REG; usCnt += 2)
    {
        Scaler32SetDWord(pulDMRegister[usCnt], pulDMRegister[usCnt + 1]);
    }

    // Dolby's patch , BEC do not has YUV444 input case, need to force to RGB444
    if(enumColorSpace == _COLOR_SPACE_YCBCR444)
    {
        Scaler32SetDWord(PB00304_08_INPUT_FORMAT, 0x0000000C);
        Scaler32SetDWord(PB00304_30_YCCTORGB_COEF0, 0x00002565);
        Scaler32SetDWord(PB00304_34_YCCTORGB_COEF1, 0x000035EA);
        Scaler32SetDWord(PB00304_38_YCCTORGB_COEF2, 0xF9FC2565);
        Scaler32SetDWord(PB00304_3C_YCCTORGB_COEF3, 0x0000EB1D);
        Scaler32SetDWord(PB00304_40_YCCTORGB_COEF4, 0x44C92565);
        Scaler32SetDWord(PB00304_44_YCCTORGB_COEF5, 0x00000000);
        Scaler32SetDWord(PB00304_48_YCCTORGB_OFFSET0, 0x01D4B7B7);
        Scaler32SetDWord(PB00304_4C_YCCTORGB_OFFSET1, 0xFF4E2487);
        Scaler32SetDWord(PB00304_50_YCCTORGB_OFFSET2, 0x024BB4AC);
        Scaler32SetDWord(PB00304_58_SIGNAL_RANGE, 0x0FFF0000);
        Scaler32SetDWord(PB00304_5C_SRANGEINV, 0x00010040);
    }

    // B02 table W
    Scaler32SetBit(PB00305_C0_DM_B02_LUT_CTRL0, ~(_BIT1 | _BIT0), 0x01); // FW W en

    for(usCnt = 0; usCnt < _SIZE_OF_DM_B02; usCnt += 2)
    {
        Scaler32SetDWord(pulDMB02[usCnt], pulDMB02[usCnt + 1]);
    }

    BYTE ucDelay_B02 = 30; // fine-tune to 250ns delay
    while(--ucDelay_B02)
    {
        NOP();
    }

    // disable FW RW
    Scaler32SetBit(PB00305_C0_DM_B02_LUT_CTRL0, ~(_BIT1 | _BIT0), 0x00);

    // B05
    Scaler32SetDWord(PB00306_38_DM_B05_LUT_CTRL0, 0x20000000); // FW W B05 en 0010 0000

    pstDMB0501[_SIZE_OF_DM_B0501 - 1].ulBW32_ADDRESS = PB00304_10_DM_DUMMY;
    pstDMB0501[_SIZE_OF_DM_B0501 - 1].ulBW32_DATA = 0x00;

#if((_HW_CPU32_BW32_SUPPORT == _ON) && (_DM_BW32_FW_MODE == _OFF))
    StructBW32CmdInfo stTmpBW32CmdInfo;
    stTmpBW32CmdInfo.stBW32BaseInfo.enumBW32CmdFormat = _BW32_CMD_FORMAT;
    stTmpBW32CmdInfo.stBW32BaseInfo.ulDdrSrcAddr = (DWORD)pstDMB0501;
    stTmpBW32CmdInfo.stBW32BaseInfo.ulTotalCmdNum = _SIZE_OF_DM_B0501;
    stTmpBW32CmdInfo.enumBW32TriggerSource = _BW32_TRIGGER_MANUAL;

    if(ScalerBW32LaunchCmdX(1, &stTmpBW32CmdInfo, 20, _TRUE, 6, _BW32_CALLBACK_NULL) == _FALSE)
    {
        DebugMessageDM("DM_TR9_Data Apply HW BW32 error", 0);
    }
#else
    BYTE ucDelay_B0501 = 30;
    for(WORD usCmdNumIdx = 0; usCmdNumIdx < _SIZE_OF_DM_B0501; usCmdNumIdx++) // fine-tune to 250ns interval
    {
        ucDelay_B0501 = 30;
        Scaler32SetDWord(pstDMB0501[usCmdNumIdx].ulBW32_ADDRESS, pstDMB0501[usCmdNumIdx].ulBW32_DATA);
        while(--ucDelay_B0501)
        {
            NOP();
        }
    }
#endif
    Scaler32SetDWord(PB00306_38_DM_B05_LUT_CTRL0, 0x00000000); // FW W/R B05 disable

    // sel B02 FW/HW access table
    if(bB02Sel == _TRUE)
    {
        Scaler32SetDWord(PB00305_C0_DM_B02_LUT_CTRL0, 0x00000004); // sel B02 FW access table 1, HW access table 0  //dis FW RW
        DebugMessageDM("DM_TR9_PB00305_C0", Scaler32GetDWord(PB00305_C0_DM_B02_LUT_CTRL0));
    }
    else
    {
        Scaler32SetDWord(PB00305_C0_DM_B02_LUT_CTRL0, 0x00000000); // sel B02 FW access table 0, HW access table 1  //dis FW RW
        DebugMessageDM("DM_TR9_PB00305_C0", Scaler32GetDWord(PB00305_C0_DM_B02_LUT_CTRL0));
    }
}

//--------------------------------------------------
// Description  : DM Init
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDMSCPUInit(void)
{
#if(_DM_FUNCTION_BYPASS_HW_APPLY == _OFF)
    if(DMInit(_DM_CUSTOMER_FW_ID, &g_stDMDRMFormat) == _TRUE)
    {
        DebugMessageDM("DM Customer ID Verify Pass", 1);
    }
    else
    {
        DebugMessageDM("DM Customer ID Verify Fail", 0);
    }
#else
    DebugMessageDM("DM Bypass HW Apply", 0);
#endif
}
#endif

#if(_IS_MAIN_PROCESS_CPU == _TRUE)
//--------------------------------------------------
// Description  : Judje input status change or not
// Input Value  : enumDisplayRegion
// Output Value : T/F
//--------------------------------------------------
bit ScalerDMStatusChange(EnumDisplayRegion enumDisplayRegion)
{
    EnumRegionIndex enumRegionIndex = ScalerRegionGetIndex(enumDisplayRegion);

    if(enumRegionIndex >= _DM_MAX_REGION_COUNT)
    {
        return _FALSE;
    }

    switch(GET_HDR_TARGET_STATUS(enumDisplayRegion))
    {
        case _HDR_TARGET_STATUS_TRADITIONAL_GAMMA_SDR:
        case _HDR_TARGET_STATUS_SMPTE_ST_2084:
        case _HDR_TARGET_STATUS_FORCE_2084:
        case _HDR_TARGET_STATUS_AUTO_HLG:
        case _HDR_TARGET_STATUS_FORCE_HLG:
        case _HDR_TARGET_STATUS_FREESYNC_II_NATIVE_COLOR:
        case _HDR_TARGET_STATUS_ADVANCED_HDR10:
            return _TRUE; // DM_NonDolby_to_Dolby

        case _HDR_TARGET_STATUS_DM:
            switch(GET_DM_INPUT_STATUS_INDEX(enumRegionIndex))
            {
                case _DM_ON_GAME:
                    return _TRUE; // DM_Dolby_to_DolbyGame

                case _DM_ON_NORMAL:
                case _DM_OFF:
                    return _FALSE;
                default:
                    return _FALSE;
            }

        case _HDR_TARGET_STATUS_DM_GAME:
            switch(GET_DM_INPUT_STATUS_INDEX(enumRegionIndex))
            {
                case _DM_ON_NORMAL:
                    return _TRUE; // DM_DolbyGame_to_Dolby

                case _DM_ON_GAME:
                case _DM_OFF:
                    return _FALSE;
                default:
                    return _FALSE;
            }

        default:
            return _FALSE;
    }
}

//--------------------------------------------------
// Description  : B05 DB SRAM en
// Input Value  : enumDisplayRegion
// Output Value : None
//--------------------------------------------------
void ScalerDMB05DoubleBufferEnable(EnumDisplayRegion enumDisplayRegion, bit bEn)
{
    ScalerDMHWApplyPathSelect(ScalerRegionGetInputDataPath(enumDisplayRegion));
    Scaler32SetBit(PB00304_00_DM_SUBMODULE_ENABLE_00, ~(_BIT17), (bEn == _ENABLE) ? _BIT17 : 0x00);
}
//--------------------------------------------------
// Description  : B05 DB SRAM apply
// Input Value  : enumDisplayRegion
// Output Value : None
//--------------------------------------------------
void ScalerDMB05DoubleBufferApply(EnumInputDataPath enumSelectedDataPath)
{
    // Check if B05 DB enable
    ScalerDMHWApplyPathSelect(enumSelectedDataPath);
    if((Scaler32GetDWord(PB00304_00_DM_SUBMODULE_ENABLE_00) & _BIT17) == _BIT17)
    {
        Scaler32SetBit(PB00304_00_DM_SUBMODULE_ENABLE_00, ~(_BIT16), _BIT16);
    }
}

//--------------------------------------------------
// Description  : DM Disable
// Input Value  : enumDisplayRegion
// Output Value : None
//--------------------------------------------------
void ScalerDMDisable(EnumInputDataPath enumInputDataPath)
{
    ScalerDMHWApplyPathSelect(enumInputDataPath);
    Scaler32SetDWord(PB00304_00_DM_SUBMODULE_ENABLE_00, 0x00000000); // sub-module disable
    Scaler32SetDWord(PB00304_08_INPUT_FORMAT, 0x0000000C); // reset input format & bit-depth
    Scaler32SetDWord(PB00305_C0_DM_B02_LUT_CTRL0, 0x00000000); // reset B02 LUT select to default

    ScalerGlobalIDomainDBApply(enumInputDataPath, _DB_APPLY_POLLING);
}

//--------------------------------------------------
// Description  : Get if DM is ready to receive metadata
// Input Value  : target port
// Output Value : ready or not
//--------------------------------------------------
bit ScalerDMGetMetadataSupport(EnumInputPort enumInputPort)
{
    BYTE ucIndex = 0;

    for(ucIndex = 0; ucIndex < _DM_MAX_REGION_COUNT; ucIndex++)
    {
        // check DM support status by region_index
        if((GET_DM_METADATA_SUPPORT_INDEX(ucIndex) == _DM_SUPPORT_ON) && (GET_DM_INITIAL_READY_INDEX(ucIndex) == _TRUE) && (GET_DM_PORT_INDEX(ucIndex) == enumInputPort))
        {
            return _TRUE;
        }
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Get if DRAM metadata is DM data or not
// Input Value  : DRAM metadata 32BYTE
// Output Value : DM data or not
//--------------------------------------------------
bit ScalerDMJudgeDRAMMetadata(BYTE *pucSdpInfoData)
{
    if((pucSdpInfoData[0] == 0x01) && (pucSdpInfoData[1] == 0x1A))
    {
        WORD usMaxDisplayMasteringLv = ((WORD)(pucSdpInfoData[21] << 8) | (pucSdpInfoData[20]));

        if(usMaxDisplayMasteringLv == 0x0000)
        {
            return _FALSE;
        }
        else if(pucSdpInfoData[24] != g_stDMDRMFormat.ucMaxCLL)
        {
            return _FALSE;
        }
        else if(pucSdpInfoData[26] != g_stDMDRMFormat.ucMaxFALL)
        {
            return _FALSE;
        }
        else if(pucSdpInfoData[16] != g_stDMDRMFormat.ucWx_LSB)
        {
            return _FALSE;
        }
        else if(pucSdpInfoData[18] != g_stDMDRMFormat.ucWy_LSB)
        {
            return _FALSE;
        }
        else
        {
            WORD pusPrimaryX[3] = {0};
            WORD pusPrimaryY[3] = {0};
            WORD usTmp = 0x0000;
            BYTE pucRGBIndex[3] = {0};

            pusPrimaryX[0] = ((WORD)(pucSdpInfoData[5] << 8) | (pucSdpInfoData[4]));
            pusPrimaryY[0] = ((WORD)(pucSdpInfoData[7] << 8) | (pucSdpInfoData[6]));
            pusPrimaryX[1] = ((WORD)(pucSdpInfoData[9] << 8) | (pucSdpInfoData[8]));
            pusPrimaryY[1] = ((WORD)(pucSdpInfoData[11] << 8) | (pucSdpInfoData[10]));
            pusPrimaryX[2] = ((WORD)(pucSdpInfoData[13] << 8) | (pucSdpInfoData[12]));
            pusPrimaryY[2] = ((WORD)(pucSdpInfoData[15] << 8) | (pucSdpInfoData[14]));

            usTmp = MAXOF3(pusPrimaryX[0], pusPrimaryX[1], pusPrimaryX[2]);
            if(usTmp == pusPrimaryX[0])
            {
                pucRGBIndex[0] = 0;
            }
            else if(usTmp == pusPrimaryX[1])
            {
                pucRGBIndex[0] = 1;
            }
            else
            {
                pucRGBIndex[0] = 2;
            }

            usTmp = MAXOF3(pusPrimaryY[0], pusPrimaryY[1], pusPrimaryY[2]);
            if(usTmp == pusPrimaryY[0])
            {
                pucRGBIndex[1] = 0;
            }
            else if(usTmp == pusPrimaryY[1])
            {
                pucRGBIndex[1] = 1;
            }
            else
            {
                pucRGBIndex[1] = 2;
            }

            if((pucRGBIndex[0] + pucRGBIndex[1]) == 1)
            {
                pucRGBIndex[2] = 2;
            }
            else if((pucRGBIndex[0] + pucRGBIndex[1]) == 2)
            {
                pucRGBIndex[2] = 1;
            }
            else if((pucRGBIndex[0] + pucRGBIndex[1]) == 3)
            {
                pucRGBIndex[2] = 0;
            }
            else
            {
                return _FALSE;
            }

            if(pusPrimaryX[pucRGBIndex[0]] != g_stDMDRMFormat.usRx)
            {
                return _FALSE;
            }
            else if(pusPrimaryY[pucRGBIndex[0]] != g_stDMDRMFormat.usRy)
            {
                return _FALSE;
            }
            else if(pusPrimaryX[pucRGBIndex[1]] != g_stDMDRMFormat.usGx)
            {
                return _FALSE;
            }
            else if(pusPrimaryY[pucRGBIndex[1]] != g_stDMDRMFormat.usGy)
            {
                return _FALSE;
            }
            else if(pusPrimaryX[pucRGBIndex[2]] != g_stDMDRMFormat.usBx)
            {
                return _FALSE;
            }
            else if(pusPrimaryY[pucRGBIndex[2]] != g_stDMDRMFormat.usBy)
            {
                return _FALSE;
            }
            else
            {
                return _TRUE;
            }
        }
    }
    else
    {
        return _FALSE;
    }
}

//--------------------------------------------------
// Description  : DRAM metadata convert to DP/HDMI DM formate
// Input Value  : DRAM metadata 32BYTE
// Output Value : EnumDMReceivedType
//--------------------------------------------------
EnumDMReceivedType ScalerDMConvertInfoData(EnumInputPort enumInputPort, BYTE *pucSdpInfoData, BYTE *pucDMInfoData)
{
    BYTE ucCnt = 0;

    switch(ScalerSyncGetPortType(enumInputPort))
    {
        case _PORT_DP:
            // Remap to DP DM format
            pucDMInfoData[0] = 0x00;
            pucDMInfoData[1] = 0x87;
            pucDMInfoData[2] = 0x1D;
            pucDMInfoData[3] = 0x4C;

            for(ucCnt = 4; ucCnt < _DM_DRAM_METADATA_LEN; ucCnt++)
            {
                pucDMInfoData[ucCnt] = pucSdpInfoData[ucCnt - 4];
            }

            return _DP_DM_DRAM_ENTRY;

        case _PORT_HDMI:
            // Remap to HDMI DM format
            pucDMInfoData[0] = 0x87;
            pucDMInfoData[1] = pucSdpInfoData[0];
            pucDMInfoData[2] = pucSdpInfoData[1];
            pucDMInfoData[3] = 0xFF; // Checksum meaningless

            for(ucCnt = 4; ucCnt < _DM_DRAM_METADATA_LEN; ucCnt++)
            {
                pucDMInfoData[ucCnt] = pucSdpInfoData[ucCnt - 2];
            }

            pucDMInfoData[30] = 0x00; // HDMI DRAM METADATA LEN only 30, but share the same g_ppucDMDRAMMetadata with DP
            pucDMInfoData[31] = 0x00; // HDMI DRAM METADATA LEN only 30, but share the same g_ppucDMDRAMMetadata with DP

            return _HDMI_DM_DRAM_ENTRY;

        default:
            return _DM_METADATA_NONE;
    }
}

//--------------------------------------------------
// Description  : Sync DM Main/Sub Data
// Input Value  : void
// Output Value : void
//--------------------------------------------------
void ScalerDMSyncMainSubData(void)
{
    SET_DM_BEC_STATUS_INDEX(_REGION_INDEX_1, GET_DM_BEC_STATUS_INDEX(_REGION_INDEX_0));
    SET_DM_MUTE_STATUS_INDEX(_REGION_INDEX_1, GET_DM_MUTE_STATUS_INDEX(_REGION_INDEX_0));
    SET_DM_INPUT_STATUS_INDEX(_REGION_INDEX_1, GET_DM_INPUT_STATUS_INDEX(_REGION_INDEX_0));
    SET_DM_PORT_INDEX(_REGION_INDEX_1, GET_DM_PORT_INDEX(_REGION_INDEX_0));
    SET_DM_METADATA_TYPE(_REGION_INDEX_1, GET_DM_METADATA_TYPE(_REGION_INDEX_0));

    switch(GET_DM_METADATA_TYPE(_REGION_INDEX_0))
    {
        case _HDMI_DM_PKT_ENTRY:
            memcpy(&g_ppucDMVSIFMetadata[1], &g_ppucDMVSIFMetadata[0], _DM_VSIF_METADATA_LEN);
            break;
        case _HDMI_DM_EMP_ENTRY:
            memcpy(&g_ppucDMEMPMetadata[1], &g_ppucDMEMPMetadata[0], _DM_EMP_METADATA_LEN);
            break;
        case _DP_DM_SDP_ENTRY:
        case _DP_DM_EXT_SDP_ENTRY:
            memcpy(&g_ppucDMSDPMetadata[1], &g_ppucDMSDPMetadata[0], _DM_SDP_METADATA_LEN);
            break;
        case _HDMI_DM_DRAM_ENTRY:
        case _DP_DM_DRAM_ENTRY:
            memcpy(&g_ppucDMDRAMMetadata[1], &g_ppucDMDRAMMetadata[0], _DM_DRAM_METADATA_LEN);
            break;
        case _DM_METADATA_NONE:
        default:
            break;
    }
}
#endif
#endif

