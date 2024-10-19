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
// ID Code      : ScalerDM_EXINT0.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_DM_EXINT0__

#include "ScalerFunctionInclude.h"
#include "DM/ScalerDM.h"

//****************************************************************************
// CODE TABLES
//****************************************************************************

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
#if(_DM_FUNCTION == _ON)
#if(_IS_MAIN_PROCESS_CPU == _TRUE)
BYTE g_pucDM_VSIF_CompareMask[_DM_VSIF_METADATA_PB_LEN] =
{
    0x00, 0x00, 0x00, 0xFF, 0xB0, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

BYTE g_pucDM_SDP_CompareMask[_DM_SDP_METADATA_PB_LEN] =
{
    0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xB0, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00,
};

BYTE g_pucDM_ExtSDP_CompareMask[_DM_SDP_METADATA_PB_LEN] =
{
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xB0, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00,
};

BYTE g_pucDM_EMP_CompareMask[_DM_EMP_METADATA_PB_LEN] =
{
    0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0xB0, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

BYTE g_pucDM_HdmiDRAM_CompareMask[_DM_DRAM_METADATA_LEN] =
{
    0x00, 0x00, 0x00, 0x00, 0x07, 0x07, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x00, 0x00,
};

BYTE g_pucDM_DpDRAM_CompareMask[_DM_DRAM_METADATA_LEN] =
{
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x07, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF,
};

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : DM I-DEN Start Handler
// Input Value  : Input Path (M1 or S1)
// Output Value : None
//--------------------------------------------------
void ScalerDMIDenStartHandler_EXINT0(EnumInputDataPath enumInputPath)
{
    EnumRegionIndex enumRegionIndex = ScalerDMGetIndexFromInputDataPath_EXINT0(enumInputPath);

    if(enumRegionIndex > 1)
    {
        return;
    }

    if((GET_DM_DRAM_SUPPORT_INDEX(enumRegionIndex) == _DM_SUPPORT_ON) && (GET_DM_METADATA_RECEIVED_INDEX(enumRegionIndex) == _FALSE))
    {
        EnumInputPort enumInputPort = GET_DM_PORT_INDEX(enumRegionIndex);

        ScalerDMPacketReCheck_EXINT0(enumInputPort);

        if(GET_DM_METADATA_RECEIVED_INDEX(enumRegionIndex) == _FALSE)
        {
            // Update DRAM Data
            ScalerDMDRAMHandler_EXINT0(enumInputPort, enumRegionIndex);
        }
    }

    // Detect DM metadata received or not
    ScalerDMCheckMetadata_EXINT0(enumRegionIndex);

    // DM unmute counter
    if(GET_DM_MUTE_STATUS_INDEX(enumRegionIndex) != _DM_NO_MUTE)
    {
        if(GET_DM_UNMUTE_FRAME_CNT_INDEX(enumRegionIndex) < _DM_UNMUTE_WAIT_FRAME_CNT)
        {
            // add 1 count
            SET_DM_UNMUTE_FRAME_CNT_INDEX(enumRegionIndex, GET_DM_UNMUTE_FRAME_CNT_INDEX(enumRegionIndex) + 0x01);
        }
    }
    else
    {
        CLR_DM_UNMUTE_FRAME_CNT_INDEX(enumRegionIndex);
    }

    if(GET_DM_BEC_STATUS_INDEX(enumRegionIndex) == _DM_BEC_PREPARATIVE)
    {
        SET_DM_BEC_STATUS_INDEX(enumRegionIndex, _DM_BEC_BUSY);
    }
}

//--------------------------------------------------
// Description  : Get Current DM data
// Input Value  : EnumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDMGetDRAMData_EXINT0(EnumInputPort enumInputPort, EnumRegionIndex enumRegionIndex)
{
    BYTE pucSdpInfoData[_HW_DP_SDP_PAYLOAD_LENGTH] = {0};
    bit bDMInfoReceive = _FALSE;
    bit bDMInfoChange = _FALSE;
    BYTE pucDMDRAM[_DM_DRAM_METADATA_PB_LEN];

    ScalerSyncGetDRAMDataByPort(enumInputPort, _DRAM_DM, pucSdpInfoData, &bDMInfoReceive, &bDMInfoChange);

    __real_memcpy(pucDMDRAM, pucSdpInfoData, _DM_DRAM_METADATA_PB_LEN);

    // Check Version/ Length
    if(ScalerDMJudgeDRAMMetadata(pucDMDRAM) == _TRUE)
    {
        BYTE pucDMInfoData[_DM_DRAM_METADATA_LEN] = {0};

        EnumDMReceivedType enumDMReceivedType = ScalerDMConvertInfoData(enumInputPort, pucDMDRAM, pucDMInfoData);

        ScalerDMMetadataHandler_EXINT0(pucDMInfoData, enumDMReceivedType, enumRegionIndex, enumInputPort);
    }
}

//--------------------------------------------------
// Description  : Check & Map Dolby Metadata to all region using same port
// Input Value  : pucDMMetaData, enumDMReceivedType, enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDMMetadataSourceMapping_EXINT0(BYTE *pucDMMetaData, EnumDMReceivedType enumDMReceivedType, EnumInputPort enumInputPort)
{
    if((GET_DM_METADATA_SUPPORT_INDEX(_REGION_INDEX_0) == _DM_SUPPORT_ON) && (GET_DM_PORT_INDEX(_REGION_INDEX_0) == enumInputPort))
    {
        ScalerDMMetadataHandler_EXINT0(pucDMMetaData, enumDMReceivedType, _REGION_INDEX_0, enumInputPort);
    }
#if(_2P_DISPLAY_SUPPORT == _ON)
    if(GET_RGN_MAX_DISPLAY_REGION() == 2)
    {
        if((GET_DM_METADATA_SUPPORT_INDEX(_REGION_INDEX_1) == _DM_SUPPORT_ON) && (GET_DM_PORT_INDEX(_REGION_INDEX_1) == enumInputPort))
        {
            ScalerDMMetadataHandler_EXINT0(pucDMMetaData, enumDMReceivedType, _REGION_INDEX_1, enumInputPort);
        }
    }
#endif
}

//--------------------------------------------------
// Description  : Main DM Metadata Proc
// Input Value  : pucDMMetaData, enumDMReceivedType, ucRegionIndex
// Output Value : None
//--------------------------------------------------
void ScalerDMMetadataHandler_EXINT0(BYTE *pucDMMetaData, EnumDMReceivedType enumDMReceivedType, EnumRegionIndex enumRegionIndex, EnumInputPort enumInputPort)
{
    if(GET_DM_INITIAL_READY_INDEX(enumRegionIndex) == _TRUE)
    {
        // If DM is active, check if current Metadata have lower priority
        // VSIF > SDP > EMP > DRAM
        if((GET_DM_METADATA_TYPE(enumRegionIndex) != _DM_METADATA_NONE) && (enumDMReceivedType < GET_DM_METADATA_TYPE(enumRegionIndex)))
        {
            return;
        }

        // use max metadata length
        BYTE pucDMMetaDatatemp[_DM_EMP_METADATA_LEN] = {0};
        BYTE ucCnt = 0;

        SET_DM_METADATA_RECEIVED_INDEX(enumRegionIndex);

        switch(enumDMReceivedType)
        {
            // HDMI DRAM
            case _HDMI_DM_DRAM_ENTRY:

                // Update DRAM change
                if(g_pstDMSettingInfo[enumRegionIndex].b1MetadtaChangeHdmiDRAM == _FALSE)
                {
                    for(ucCnt = 0; ucCnt < _DM_DRAM_METADATA_LEN; ucCnt++)
                    {
                        if((g_ppucDMDRAMMetadata[enumRegionIndex][ucCnt] & g_pucDM_HdmiDRAM_CompareMask[ucCnt]) != (pucDMMetaData[ucCnt] & g_pucDM_HdmiDRAM_CompareMask[ucCnt]))
                        {
                            g_pstDMSettingInfo[enumRegionIndex].b1MetadtaChangeHdmiDRAM = _TRUE;
                            break;
                        }
                    }

                    if(g_pstDMSettingInfo[enumRegionIndex].b1MetadtaChangeHdmiDRAM == _TRUE)
                    {
                        SET_DM_INPUT_STATUS_INDEX(enumRegionIndex, _DM_ON_NORMAL);
                        __real_memcpy(&g_ppucDMDRAMMetadata[enumRegionIndex], pucDMMetaData, _DM_DRAM_METADATA_LEN);
                    }
                }
                break;

            // DP DRAM
            case _DP_DM_DRAM_ENTRY:

                // Update DRAM change
                if(g_pstDMSettingInfo[enumRegionIndex].b1MetadtaChangeDpDRAM == _FALSE)
                {
                    for(ucCnt = 0; ucCnt < _DM_DRAM_METADATA_LEN; ucCnt++)
                    {
                        if((g_ppucDMDRAMMetadata[enumRegionIndex][ucCnt] & g_pucDM_DpDRAM_CompareMask[ucCnt]) != (pucDMMetaData[ucCnt] & g_pucDM_DpDRAM_CompareMask[ucCnt]))
                        {
                            g_pstDMSettingInfo[enumRegionIndex].b1MetadtaChangeDpDRAM = _TRUE;
                            break;
                        }
                    }

                    if(g_pstDMSettingInfo[enumRegionIndex].b1MetadtaChangeDpDRAM == _TRUE)
                    {
                        SET_DM_INPUT_STATUS_INDEX(enumRegionIndex, _DM_ON_NORMAL);
                        __real_memcpy(&g_ppucDMDRAMMetadata[enumRegionIndex], pucDMMetaData, _DM_DRAM_METADATA_LEN);
                    }
                }
                break;

            // HDMI VSIF
            case _HDMI_DM_PKT_ENTRY: // pucDmMetaData Size: 27 Byte

                // Update VSIF change
                if(g_pstDMSettingInfo[enumRegionIndex].b1MetadtaChangeVSIF == _FALSE)
                {
                    for(ucCnt = 0; ucCnt < _DM_VSIF_METADATA_PB_LEN; ucCnt++)
                    {
                        if((g_ppucDMVSIFMetadata[enumRegionIndex][ucCnt + 4] & g_pucDM_VSIF_CompareMask[ucCnt]) != (pucDMMetaData[ucCnt] & g_pucDM_VSIF_CompareMask[ucCnt]))
                        {
                            g_pstDMSettingInfo[enumRegionIndex].b1MetadtaChangeVSIF = _TRUE;
                            break;
                        }
                    }

                    if(g_pstDMSettingInfo[enumRegionIndex].b1MetadtaChangeVSIF == _TRUE)
                    {
#if(_DM_CONFIG_GAME_MODE_INDEX != _DM_PICTURE_MODE_NONE)
                        if((pucDMMetaData[9] & (_BIT3 | _BIT2 | _BIT1 | _BIT0)) == _BIT1) // LSB4bit Content_Type 0x02 = Game mode
                        {
                            SET_DM_INPUT_STATUS_INDEX(enumRegionIndex, _DM_ON_GAME);
                        }
                        else
#endif
                        {
                            SET_DM_INPUT_STATUS_INDEX(enumRegionIndex, _DM_ON_NORMAL);
                        }

                        // copy Metadata
                        pucDMMetaDatatemp[0] = 0x81;
                        pucDMMetaDatatemp[1] = 0x01;
                        pucDMMetaDatatemp[2] = 0x1B;
                        pucDMMetaDatatemp[3] = 0xFF; // Checksum meaningless
                        for(ucCnt = 0; ucCnt < _DM_VSIF_METADATA_PB_LEN; ucCnt++)
                        {
                            pucDMMetaDatatemp[ucCnt + 4] = pucDMMetaData[ucCnt];
                        }

                        __real_memcpy(&g_ppucDMVSIFMetadata[enumRegionIndex], pucDMMetaDatatemp, _DM_VSIF_METADATA_LEN);
                    }
                }
                break;

            // HDMI EMP
            case _HDMI_DM_EMP_ENTRY:
                // Update EMP change
                if(g_pstDMSettingInfo[enumRegionIndex].b1MetadtaChangeEMP == _FALSE)
                {
                    for(ucCnt = 0; ucCnt < _DM_EMP_METADATA_PB_LEN; ucCnt++)
                    {
                        if((g_ppucDMEMPMetadata[enumRegionIndex][ucCnt + 7] & g_pucDM_EMP_CompareMask[ucCnt]) != (pucDMMetaData[ucCnt] & g_pucDM_EMP_CompareMask[ucCnt]))
                        {
                            g_pstDMSettingInfo[enumRegionIndex].b1MetadtaChangeEMP = _TRUE;
                            break;
                        }
                    }

                    if(g_pstDMSettingInfo[enumRegionIndex].b1MetadtaChangeEMP == _TRUE)
                    {
#if(_DM_CONFIG_GAME_MODE_INDEX != _DM_PICTURE_MODE_NONE)
                        if((pucDMMetaData[12] & (_BIT3 | _BIT2 | _BIT1 | _BIT0)) == _BIT1) // LSB4bit Content_Type 0x02 = Game mode
                        {
                            SET_DM_INPUT_STATUS_INDEX(enumRegionIndex, _DM_ON_GAME);
                        }
                        else
#endif
                        {
                            SET_DM_INPUT_STATUS_INDEX(enumRegionIndex, _DM_ON_NORMAL);
                        }

                        // copy Metadata
                        pucDMMetaDatatemp[0] = 0xE6;
                        pucDMMetaDatatemp[1] = 0x00;
                        pucDMMetaDatatemp[2] = 0x00;
                        pucDMMetaDatatemp[3] = 0x00;
                        pucDMMetaDatatemp[4] = 0x00;
                        pucDMMetaDatatemp[5] = 0x00;
                        pucDMMetaDatatemp[6] = 0x22;

                        for(ucCnt = 0; ucCnt < _DM_EMP_METADATA_PB_LEN; ucCnt++)
                        {
                            pucDMMetaDatatemp[ucCnt + 7] = pucDMMetaData[ucCnt];
                        }

                        __real_memcpy(&g_ppucDMEMPMetadata[enumRegionIndex], pucDMMetaDatatemp, _DM_EMP_METADATA_LEN);
                    }
                }
                break;

            // DP Infoframe SDP
            case _DP_DM_SDP_ENTRY:
                // Update SDP change
                if(g_pstDMSettingInfo[enumRegionIndex].b1MetadtaChangeSDP == _FALSE)
                {
                    for(ucCnt = 0; ucCnt < _DM_SDP_METADATA_PB_LEN; ucCnt++)
                    {
                        if((g_ppucDMSDPMetadata[enumRegionIndex][ucCnt + 4] & g_pucDM_SDP_CompareMask[ucCnt]) != (pucDMMetaData[ucCnt] & g_pucDM_SDP_CompareMask[ucCnt]))
                        {
                            g_pstDMSettingInfo[enumRegionIndex].b1MetadtaChangeSDP = _TRUE;
                            break;
                        }
                    }

                    if(g_pstDMSettingInfo[enumRegionIndex].b1MetadtaChangeSDP == _TRUE)
                    {
                        SET_DM_INPUT_STATUS_INDEX(enumRegionIndex, _DM_ON_NORMAL);

                        // copy Metadata
                        pucDMMetaDatatemp[0] = 0x00;
                        pucDMMetaDatatemp[1] = 0x81;
                        pucDMMetaDatatemp[2] = 0x1D;
                        pucDMMetaDatatemp[3] = 0x4C;

                        for(ucCnt = 0; ucCnt < _DM_SDP_METADATA_PB_LEN; ucCnt++)
                        {
                            pucDMMetaDatatemp[ucCnt + 4] = pucDMMetaData[ucCnt];
                        }

                        __real_memcpy(&g_ppucDMSDPMetadata[enumRegionIndex], pucDMMetaDatatemp, _DM_SDP_METADATA_LEN);
                    }
                }
                break;

            // DP VSC_EXT_VESA SDP
            case _DP_DM_EXT_SDP_ENTRY:
                // Update SDP change
                if(g_pstDMSettingInfo[enumRegionIndex].b1MetadtaChangeSDP == _FALSE)
                {
                    for(ucCnt = 0; ucCnt < _DM_SDP_METADATA_PB_LEN; ucCnt++)
                    {
                        if((g_ppucDMSDPMetadata[enumRegionIndex][ucCnt + 4] & g_pucDM_ExtSDP_CompareMask[ucCnt]) != (pucDMMetaData[ucCnt] & g_pucDM_ExtSDP_CompareMask[ucCnt]))
                        {
                            g_pstDMSettingInfo[enumRegionIndex].b1MetadtaChangeSDP = _TRUE;
                            break;
                        }
                    }

                    if(g_pstDMSettingInfo[enumRegionIndex].b1MetadtaChangeSDP == _TRUE)
                    {
                        SET_DM_INPUT_STATUS_INDEX(enumRegionIndex, _DM_ON_NORMAL);

                        // copy Metadata
                        pucDMMetaDatatemp[0] = 0x00;
                        pucDMMetaDatatemp[1] = 0x20;
                        pucDMMetaDatatemp[2] = 0x01; // New Spec demand 0x01, Interface remain 0x00 for better compatibility
                        pucDMMetaDatatemp[3] = 0x00;

                        for(ucCnt = 0; ucCnt < _DM_SDP_METADATA_PB_LEN; ucCnt++)
                        {
                            pucDMMetaDatatemp[ucCnt + 4] = pucDMMetaData[ucCnt];
                        }

                        __real_memcpy(&g_ppucDMSDPMetadata[enumRegionIndex], pucDMMetaDatatemp, _DM_SDP_METADATA_LEN);
                    }
                }
                break;

            default:
                break;
        }

        if((ScalerColorGetColorSpace(enumInputPort) != g_pstDMSettingInfo[enumRegionIndex].enumDMColorSpace) ||
           (ScalerColorGetColorDepth(enumInputPort) != g_pstDMSettingInfo[enumRegionIndex].ucDMColorDepth))
        {
            switch(GET_DM_METADATA_TYPE(enumRegionIndex))
            {
                case _HDMI_DM_DRAM_ENTRY:
                    g_pstDMSettingInfo[enumRegionIndex].b1MetadtaChangeHdmiDRAM = _TRUE;
                    break;
                case _HDMI_DM_EMP_ENTRY:
                    g_pstDMSettingInfo[enumRegionIndex].b1MetadtaChangeEMP = _TRUE;
                    break;
                case _DP_DM_SDP_ENTRY:
                    g_pstDMSettingInfo[enumRegionIndex].b1MetadtaChangeSDP = _TRUE;
                    break;
                case _DP_DM_EXT_SDP_ENTRY:
                    g_pstDMSettingInfo[enumRegionIndex].b1MetadtaChangeSDP = _TRUE;
                    break;
                case _DP_DM_DRAM_ENTRY:
                    g_pstDMSettingInfo[enumRegionIndex].b1MetadtaChangeDpDRAM = _TRUE;
                    break;
                case _HDMI_DM_PKT_ENTRY:
                    g_pstDMSettingInfo[enumRegionIndex].b1MetadtaChangeVSIF = _TRUE;
                    break;
                case _DM_METADATA_NONE:
                default:
                    break;
            }
        }

        if(((g_pstDMSettingInfo[enumRegionIndex].b1MetadtaChangeHdmiDRAM == _TRUE) ||
            (g_pstDMSettingInfo[enumRegionIndex].b1MetadtaChangeDpDRAM == _TRUE) ||
            (g_pstDMSettingInfo[enumRegionIndex].b1MetadtaChangeVSIF == _TRUE) ||
            (g_pstDMSettingInfo[enumRegionIndex].b1MetadtaChangeEMP == _TRUE) ||
            (g_pstDMSettingInfo[enumRegionIndex].b1MetadtaChangeSDP == _TRUE)) &&
           (GET_DM_BEC_STATUS_INDEX(enumRegionIndex) == _DM_BEC_INIT) &&
           (GET_DM_MUTE_STATUS_INDEX(enumRegionIndex) == _DM_NO_MUTE))
        {
#if(_EAGLE_SIGHT_SUPPORT == _ON)
            if((GET_RGN_DISPLAY_REGION(enumRegionIndex) == _DISPLAY_RGN_EAGLE_SIGHT_MAIN) && (ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _FALSE))
            {
                SET_DM_MAIN_SUB_SYNC();
            }
#endif

#if(_DM_MUTE_MODE == _DM_MUTE_D_DEN_STOP)
            SET_DM_MUTE_FLAG_INDEX(enumRegionIndex);
#else
            ScalerDMBackgroundEnable(GET_RGN_DISPLAY_REGION(enumRegionIndex), _ENABLE);
#endif

#if(_DM_COLORFORMAT_CHANGE_WO_RESET_SUPPORT == _ON)
            ScalerGlobalDoubleBufferEnable(ScalerRegionGetInputDataPath(GET_RGN_DISPLAY_REGION(enumRegionIndex)), _DISABLE);
            CLR_DIGITAL_DM_COLOR_INFO_CHANGE_RESET();
            CLR_DIGITAL_COLOR_INFO_CHANGE_RESET();
#endif

            SET_DM_MUTE_STATUS_INDEX(enumRegionIndex, _DM_IN_MUTE);

            SET_DM_BEC_STATUS_INDEX(enumRegionIndex, _DM_BEC_PREPARATIVE);
        }
    }
}

#if(_DP_SUPPORT == _ON)
//--------------------------------------------------
// Description  : check if receive DM DRMI(DRAM) from DP
// Input Value  : enumInputPath
// Output Value : None
//--------------------------------------------------
bit ScalerDMDRAMCheckDp_EXINT0(EnumInputPort enumInputPort)
{
    if(ScalerDpMacStreamRxGetDMDRAMReceived_EXINT0(enumInputPort) == _TRUE)
    {
        // for HDR
        SET_DRAM_RECEIVED_FROM_DM_DETECT(enumInputPort);

        return _TRUE;
    }
    else
    {
        return _FALSE;
    }
}
#endif

#if(_HDMI_SUPPORT == _ON)
//--------------------------------------------------
// Description  : check if receive DM DRMI(DRAM) from HDMI
// Input Value  : enumInputPath
// Output Value : None
//--------------------------------------------------
bit ScalerDMDRAMCheckHdmi_EXINT0(EnumInputPort enumInputPort)
{
    if(ScalerTmdsMacRxGetDMDramReceived_EXINT0(enumInputPort) == _TRUE)
    {
        // for HDR
        SET_DRAM_RECEIVED_FROM_DM_DETECT(enumInputPort);

        return _TRUE;
    }
    else
    {
        return _FALSE;
    }
}
#endif

//--------------------------------------------------
// Description  : check DM DRMI(DRAM)
// Input Value  : enumInputPath
// Output Value : None
//--------------------------------------------------
void ScalerDMDRAMHandler_EXINT0(EnumInputPort enumInputPort, EnumRegionIndex enumRegionIndex)
{
    bit bReceive = _FALSE;
    switch(ScalerSyncGetPortType(enumInputPort))
    {
#if(_DP_SUPPORT == _ON)
        case _PORT_DP:
            bReceive = ScalerDMDRAMCheckDp_EXINT0(enumInputPort);
            break;
#endif
#if(_HDMI_SUPPORT == _ON)
        case _PORT_HDMI:
            bReceive = ScalerDMDRAMCheckHdmi_EXINT0(enumInputPort);
            break;
#endif
        default:
            break;
    }

    if(bReceive == _TRUE)
    {
        // DRM Data
        ScalerDMGetDRAMData_EXINT0(enumInputPort, enumRegionIndex);

        if((enumRegionIndex == _REGION_INDEX_0) && (GET_DM_PORT_INDEX(_REGION_INDEX_1) == enumInputPort)) // One port to 2 region check
        {
            // DRM Data
            ScalerDMGetDRAMData_EXINT0(enumInputPort, _REGION_INDEX_1);
        }
    }
}

//--------------------------------------------------
// Description  : Check DM Metadata Received or not (during display)
// Input Value  : enumRegionIndex
// Output Value : None
//--------------------------------------------------
void ScalerDMCheckMetadata_EXINT0(EnumRegionIndex enumRegionIndex)
{
    EnumDisplayRegion enumDisplayRegion = GET_RGN_DISPLAY_REGION(enumRegionIndex);

    if(GET_DM_METADATA_RECEIVED_INDEX(enumRegionIndex) == _TRUE)
    {
        CLR_DM_METADATA_RECEIVED_INDEX(enumRegionIndex);
        CLR_DM_METADATA_MISS_CNT_INDEX(enumRegionIndex);

#if(_HDMI21_ALLM_SUPPORT == _ON)
        // Check HDMI ALLM Flag
        {
            EnumInputPort enumInputPort = GET_DM_PORT_INDEX(enumRegionIndex);

            if(ScalerSyncGetPortType(enumInputPort) == _PORT_HDMI)
            {
                if(ScalerTmdsMacRxGetDmAllmStatus_EXINT0(enumInputPort) == _TRUE)
                {
                    // clear dm_allm_en flag every i_de start
                    ScalerTmdsMacRxClrDmAllmStatus_EXINT0(enumInputPort);

                    SET_DM_INPUT_STATUS_INDEX(enumRegionIndex, _DM_ON_GAME);
                }
            }
        }
#endif

        // if DM has errors, wait 6 frame before exit DM
        if((GET_DM_METADATA_ERROR_INDEX(enumRegionIndex) == _TRUE) && (GET_DM_MUTE_STATUS_INDEX(enumRegionIndex) == _DM_IN_MUTE))
        {
            WORD usErrorFrameCnt = 0;
            WORD usCurrentFrameCnt = (WORD)ScalerDMGetFrameCnt(enumDisplayRegion);

            if(usCurrentFrameCnt < g_pstDMSettingInfo[enumRegionIndex].ucFrameCnt)
            {
                usCurrentFrameCnt += 256;
            }

            usErrorFrameCnt = usCurrentFrameCnt - g_pstDMSettingInfo[enumRegionIndex].ucFrameCnt + 1;

            if(usErrorFrameCnt >= _DM_FAULT_TOLERANCE_CNT)
            {
                SET_DM_MUTE_STATUS_INDEX(enumRegionIndex, _DM_OUT_MUTE);
#if(_EAGLE_SIGHT_SUPPORT == _ON)
                if((enumDisplayRegion == _DISPLAY_RGN_EAGLE_SIGHT_MAIN) && (ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _FALSE))
                {
                    SET_DM_MAIN_SUB_SYNC();
                }
#endif
            }
        }
    }
    else // in Dolby, check if out Dolby
    {
        if(((GET_HDR_TARGET_STATUS(enumDisplayRegion) == _HDR_TARGET_STATUS_DM) || (GET_HDR_TARGET_STATUS(enumDisplayRegion) == _HDR_TARGET_STATUS_DM_GAME)) &&
           (GET_DM_MUTE_STATUS_INDEX(enumRegionIndex) == _DM_NO_MUTE))
        {
            BYTE ucMissToleranceCnt = 0x00;

#if(_EAGLE_SIGHT_SUPPORT == _ON)
            if(ScalerRegionEagleSightTransDisplayMode(GET_DISPLAY_MODE()) == _DISPLAY_MODE_1P)
#else
            if(GET_DISPLAY_MODE() == _DISPLAY_MODE_1P)
#endif
            {
                ucMissToleranceCnt = _DM_METADATA_MISS_TOLERANCE_CNT_1P;
            }
            else
            {
                ucMissToleranceCnt = _DM_METADATA_MISS_TOLERANCE_CNT_MTP;
            }

            SET_DM_METADATA_MISS_CNT_INDEX(enumRegionIndex);

            // When no Dolby metadata received frame reach tolerance --> out Dolby
            if(GET_DM_METADATA_MISS_CNT_INDEX(enumRegionIndex) == ucMissToleranceCnt)
            {
                // Close DM
#if(_DM_MUTE_MODE == _DM_MUTE_D_DEN_STOP)
                SET_DM_MUTE_FLAG_INDEX(enumRegionIndex);
#else
                ScalerDMBackgroundEnable(enumDisplayRegion, _ENABLE);
#endif

#if(_DM_COLORFORMAT_CHANGE_WO_RESET_SUPPORT == _ON)
                ScalerGlobalDoubleBufferEnable(ScalerRegionGetInputDataPath(enumDisplayRegion), _DISABLE);
                CLR_DIGITAL_DM_COLOR_INFO_CHANGE_RESET();
                CLR_DIGITAL_COLOR_INFO_CHANGE_RESET();
#endif

                SET_DM_MUTE_STATUS_INDEX(enumRegionIndex, _DM_OUT_MUTE);
                SET_DM_INPUT_STATUS_INDEX(enumRegionIndex, _DM_OFF);

                CLR_DM_METADATA_MISS_CNT_INDEX(enumRegionIndex);

#if(_EAGLE_SIGHT_SUPPORT == _ON)
                if((enumDisplayRegion == _DISPLAY_RGN_EAGLE_SIGHT_MAIN) && (ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _FALSE))
                {
                    SET_DM_MAIN_SUB_SYNC();
                }
#endif
            }
        }
    }
}

//--------------------------------------------------
// Description  : DM Get input data path for select region
// Input Value  : enumInputDataPath
// Output Value : enumRegionIndex
//--------------------------------------------------
EnumRegionIndex ScalerDMGetIndexFromInputDataPath_EXINT0(EnumInputDataPath enumInputDataPath)
{
    switch(enumInputDataPath)
    {
        case _INPUT_PATH_M1:
            return _REGION_INDEX_0;

        case _INPUT_PATH_S1:
            return _REGION_INDEX_1;

        case _INPUT_PATH_NONE:
        case _INPUT_PATH_M2:
        case _INPUT_PATH_S2:
        case _INPUT_PATH_S3:
        case _INPUT_PATH_S4:
        case _INPUT_PATH_M1_M2:
        case _INPUT_PATH_S1_S2:
        case _INPUT_PATH_S3_S4:
        case _INPUT_PATH_M1_M2_S1_S2:
        case _INPUT_PATH_ALL:
        default:
            return _REGION_INDEX_NONE;
    }
}


//--------------------------------------------------
// Description  : Re check InterFace DM Packet Info
// Input Value  : enumInputPath
// Output Value : None
//--------------------------------------------------
void ScalerDMPacketReCheck_EXINT0(EnumInputPort enumInputPort)
{
    switch(ScalerSyncGetPortType(enumInputPort))
    {
#if(_DP_SUPPORT == _ON)
        case _PORT_DP:
            if(GET_DP_RX_GLOBAL_INT_FLAG() == _TRUE)
            {
                ScalerDpMacStreamRxDMPacketReCheck_EXINT0(enumInputPort);
            }
            break;
#endif
#if(_HDMI_SUPPORT == _ON)
        case _PORT_HDMI:
            if((CPU32_GET_INT_PENDING_STATUS() & (_IRQ_MASK_HDMI_HIGH | _IRQ_MASK_HDMI_LOW)) != 0)
            {
                ScalerTmdsMacRxDMPacketReCheck_EXINT0(enumInputPort);
            }
            break;
#endif
        default:
            break;
    }
}
#endif
#endif
