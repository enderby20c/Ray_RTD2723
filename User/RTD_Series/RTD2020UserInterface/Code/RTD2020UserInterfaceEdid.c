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
// ID Code      : RTD2020UserInterfaceEdid.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_INTERFACE_EDID__

#include "RTD2020UserInclude.h"
#include "RTD2020UserInterfaceEdid.h"
#include "RTD2020UserHDMIEdid.h"
#include "RTD2020UserDPEdid.h"

#if(_OSD_TYPE == _REALTEK_2020_OSD)

//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_WRITE_EDID_LOCATION_BY_USER_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set Embedded EDID Data
// Input Value  : Input Port EDID Select
// Output Value : None
//--------------------------------------------------
void UserInterfaceEdidGetEmbeddedEdidData(EnumInputPortEdid enumInputPort)
{
    EnumEdidSelection enumIndex = _EDID_INDEX_0;

    switch(enumInputPort)
    {
        case _A0_INPUT_PORT_EDID:
            break;

#if(_D0_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
        case _D0_INPUT_PORT_EDID:

#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)

            memset(MCU_DDCRAM_D0, 0, _D0_EMBEDDED_DDCRAM_MAX_SIZE);
            enumIndex = UserAdjustGetDpEdidIndex(_D0_INPUT_PORT);

#if(_HW_DP_HIGH_RESOL_SUPPORT == _ON)
            if(UserCommonNVRamGetSystemData(_EDID_D0_SELECT) >= _DP_EDID_4K2K_240HZ)
            {
                BYTE pucEdidContent[_D0_EMBEDDED_DDCRAM_MAX_SIZE] = {0};

                memcpy(pucEdidContent, tDP_EDID_TABLE_BY_RESOL_1[enumIndex], tDP_EDID_TABLE_SIZE_BY_RESOL_1[enumIndex]);

#if((_DP_HLG_SUPPORT == _ON) || (_AUDIO_ARC_SUPPORT == _ON))
                if(UserCommonEdidOnlineEdidModify(pucEdidContent, UserAdjustGetEdidModifyTarget(_D0_INPUT_PORT)) == _TRUE)
                {
                    // Set Modified Edid to DDCRAM
                    memcpy(MCU_DDCRAM_D0, pucEdidContent, _D0_EMBEDDED_DDCRAM_MAX_SIZE);
                }
                else
#endif
                {
                    // Set Raw Edid to DDCRAM
                    memcpy(MCU_DDCRAM_D0, tDP_EDID_TABLE_BY_RESOL_1[enumIndex], tDP_EDID_TABLE_SIZE_BY_RESOL_1[enumIndex]);
                }
            }
            else
#endif
            {
                BYTE pucEdidContent[_D0_EMBEDDED_DDCRAM_MAX_SIZE] = {0};

                memcpy(pucEdidContent, tDP_EDID_TABLE_BY_RESOL_0[enumIndex], tDP_EDID_TABLE_SIZE_BY_RESOL_0[enumIndex]);

#if((_DP_HLG_SUPPORT == _ON) || (_AUDIO_ARC_SUPPORT == _ON))
                if(UserCommonEdidOnlineEdidModify(pucEdidContent, UserAdjustGetEdidModifyTarget(_D0_INPUT_PORT)) == _TRUE)
                {
                    // Set Modified Edid to DDCRAM
                    memcpy(MCU_DDCRAM_D0, pucEdidContent, _D0_EMBEDDED_DDCRAM_MAX_SIZE);
                }
                else
#endif
                {
                    // Set Raw Edid to DDCRAM
                    memcpy(MCU_DDCRAM_D0, tDP_EDID_TABLE_BY_RESOL_0[enumIndex], tDP_EDID_TABLE_SIZE_BY_RESOL_0[enumIndex]);
                }
            }
#endif // End of #if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
            break;
#endif // #if(_D0_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)

#if(_D1_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
        case _D1_INPUT_PORT_EDID:

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)

            memset(MCU_DDCRAM_D1, 0, _D1_EMBEDDED_DDCRAM_MAX_SIZE);
            enumIndex = UserAdjustGetDpEdidIndex(_D1_INPUT_PORT);

#if(_HW_DP_HIGH_RESOL_SUPPORT == _ON)
            if(UserCommonNVRamGetSystemData(_EDID_D1_SELECT) >= _DP_EDID_4K2K_240HZ)
            {
                BYTE pucEdidContent[_D1_EMBEDDED_DDCRAM_MAX_SIZE] = {0};

                memcpy(pucEdidContent, tDP_EDID_TABLE_BY_RESOL_1[enumIndex], tDP_EDID_TABLE_SIZE_BY_RESOL_1[enumIndex]);

#if((_DP_HLG_SUPPORT == _ON) || (_AUDIO_ARC_SUPPORT == _ON))
                if(UserCommonEdidOnlineEdidModify(pucEdidContent, UserAdjustGetEdidModifyTarget(_D1_INPUT_PORT)) == _TRUE)
                {
                    // Set Modified Edid to DDCRAM
                    memcpy(MCU_DDCRAM_D1, pucEdidContent, _D1_EMBEDDED_DDCRAM_MAX_SIZE);
                }
                else
#endif
                {
                    // Set Raw Edid to DDCRAM
                    memcpy(MCU_DDCRAM_D1, tDP_EDID_TABLE_BY_RESOL_1[enumIndex], tDP_EDID_TABLE_SIZE_BY_RESOL_1[enumIndex]);
                }
            }
            else
#endif
            {
                BYTE pucEdidContent[_D1_EMBEDDED_DDCRAM_MAX_SIZE] = {0};

                memcpy(pucEdidContent, tDP_EDID_TABLE_BY_RESOL_0[enumIndex], tDP_EDID_TABLE_SIZE_BY_RESOL_0[enumIndex]);

#if((_DP_HLG_SUPPORT == _ON) || (_AUDIO_ARC_SUPPORT == _ON))
                if(UserCommonEdidOnlineEdidModify(pucEdidContent, UserAdjustGetEdidModifyTarget(_D1_INPUT_PORT)) == _TRUE)
                {
                    // Set Modified Edid to DDCRAM
                    memcpy(MCU_DDCRAM_D1, pucEdidContent, _D1_EMBEDDED_DDCRAM_MAX_SIZE);
                }
                else
#endif
                {
                    // Set Raw Edid to DDCRAM
                    memcpy(MCU_DDCRAM_D1, tDP_EDID_TABLE_BY_RESOL_0[enumIndex], tDP_EDID_TABLE_SIZE_BY_RESOL_0[enumIndex]);
                }
            }
#elif(_D1_HDMI_SUPPORT == _ON)

#if(_D1_HDMI_MULTI_EDID_SUPPORT == _ON)
            enumIndex = UserInterfaceEdidGetMultiHdmiEdidIndex(_D1_INPUT_PORT);

            if(UserCommonEdidGetMultiHdmiEdidLocation(_D1_INPUT_PORT, enumIndex) != _HDMI_EDID_EXTERNAL)
            {
                BYTE pucEdidContent[_D1_EMBEDDED_DDCRAM_MAX_SIZE] = {0};

                memset(pucEdidContent, 0, _D1_EMBEDDED_DDCRAM_MAX_SIZE);
                memcpy(pucEdidContent, tHDMI_EDID_TABLE[enumIndex], tHDMI_EDID_TABLE_SIZE[enumIndex]);

#if((_HDMI_HLG_SUPPORT == _ON) || (_HDMI21_RX_DSC_DECODER_SUPPORT == _ON) || (_HDMI_FREESYNC_SUPPORT == _ON) || (_AUDIO_ARC_SUPPORT == _ON))
                if(UserCommonEdidOnlineEdidModify(pucEdidContent, UserAdjustGetEdidModifyTarget(_D1_INPUT_PORT)) == _TRUE)
                {
                    // Set Modified Edid to DDCRAM
                    memcpy(MCU_DDCRAM_D1, pucEdidContent, _D1_EMBEDDED_DDCRAM_MAX_SIZE);
                }
                else
#endif
                {
                    // Set Raw Edid to DDCRAM
                    memcpy(MCU_DDCRAM_D1, tHDMI_EDID_TABLE[enumIndex], tHDMI_EDID_TABLE_SIZE[enumIndex]);
                }
            }
#else
            memset(MCU_DDCRAM_D1, 0, _D1_EMBEDDED_DDCRAM_MAX_SIZE);
            memcpy(MCU_DDCRAM_D1, tHDMI_EDID_FHD_TABLE, sizeof(tHDMI_EDID_FHD_TABLE));
#endif

#endif
            break;
#endif // #if(_D1_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)

#if(_D2_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
        case _D2_INPUT_PORT_EDID:

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)

            memset(MCU_DDCRAM_D2, 0, _D2_EMBEDDED_DDCRAM_MAX_SIZE);
            enumIndex = UserAdjustGetDpEdidIndex(_D2_INPUT_PORT);

#if(_HW_DP_HIGH_RESOL_SUPPORT == _ON)
            if(UserCommonNVRamGetSystemData(_EDID_D2_SELECT) >= _DP_EDID_4K2K_240HZ)
            {
                BYTE pucEdidContent[_D2_EMBEDDED_DDCRAM_MAX_SIZE] = {0};

                memcpy(pucEdidContent, tDP_EDID_TABLE_BY_RESOL_1[enumIndex], tDP_EDID_TABLE_SIZE_BY_RESOL_1[enumIndex]);

#if((_DP_HLG_SUPPORT == _ON) || (_AUDIO_ARC_SUPPORT == _ON))
                if(UserCommonEdidOnlineEdidModify(pucEdidContent, UserAdjustGetEdidModifyTarget(_D2_INPUT_PORT)) == _TRUE)
                {
                    // Set Modified Edid to DDCRAM
                    memcpy(MCU_DDCRAM_D2, pucEdidContent, _D2_EMBEDDED_DDCRAM_MAX_SIZE);
                }
                else
#endif
                {
                    // Set Raw Edid to DDCRAM
                    memcpy(MCU_DDCRAM_D2, tDP_EDID_TABLE_BY_RESOL_1[enumIndex], tDP_EDID_TABLE_SIZE_BY_RESOL_1[enumIndex]);
                }
            }
            else
#endif
            {
                BYTE pucEdidContent[_D2_EMBEDDED_DDCRAM_MAX_SIZE] = {0};

                memcpy(pucEdidContent, tDP_EDID_TABLE_BY_RESOL_0[enumIndex], tDP_EDID_TABLE_SIZE_BY_RESOL_0[enumIndex]);

#if((_DP_HLG_SUPPORT == _ON) || (_AUDIO_ARC_SUPPORT == _ON))
                if(UserCommonEdidOnlineEdidModify(pucEdidContent, UserAdjustGetEdidModifyTarget(_D2_INPUT_PORT)) == _TRUE)
                {
                    // Set Modified Edid to DDCRAM
                    memcpy(MCU_DDCRAM_D2, pucEdidContent, _D2_EMBEDDED_DDCRAM_MAX_SIZE);
                }
                else
#endif
                {
                    // Set Raw Edid to DDCRAM
                    memcpy(MCU_DDCRAM_D2, tDP_EDID_TABLE_BY_RESOL_0[enumIndex], tDP_EDID_TABLE_SIZE_BY_RESOL_0[enumIndex]);
                }
            }

#elif(_D2_HDMI_SUPPORT == _ON)

#if(_D2_HDMI_MULTI_EDID_SUPPORT == _ON)
            enumIndex = UserInterfaceEdidGetMultiHdmiEdidIndex(_D2_INPUT_PORT);

            if(UserCommonEdidGetMultiHdmiEdidLocation(_D2_INPUT_PORT, enumIndex) != _HDMI_EDID_EXTERNAL)
            {
                BYTE pucEdidContent[_D2_EMBEDDED_DDCRAM_MAX_SIZE] = {0};

                memset(pucEdidContent, 0, _D2_EMBEDDED_DDCRAM_MAX_SIZE);
                memcpy(pucEdidContent, tHDMI_EDID_TABLE[enumIndex], tHDMI_EDID_TABLE_SIZE[enumIndex]);

#if((_HDMI_HLG_SUPPORT == _ON) || (_HDMI21_RX_DSC_DECODER_SUPPORT == _ON) || (_HDMI_FREESYNC_SUPPORT == _ON) || (_AUDIO_ARC_SUPPORT == _ON))
                if(UserCommonEdidOnlineEdidModify(pucEdidContent, UserAdjustGetEdidModifyTarget(_D2_INPUT_PORT)) == _TRUE)
                {
                    // Set Modified Edid to DDCRAM
                    memcpy(MCU_DDCRAM_D2, pucEdidContent, _D2_EMBEDDED_DDCRAM_MAX_SIZE);
                }
                else
#endif
                {
                    // Set Raw Edid to DDCRAM
                    memcpy(MCU_DDCRAM_D2, tHDMI_EDID_TABLE[enumIndex], tHDMI_EDID_TABLE_SIZE[enumIndex]);
                }
            }
#else
            memset(MCU_DDCRAM_D2, 0, _D2_EMBEDDED_DDCRAM_MAX_SIZE);
            memcpy(MCU_DDCRAM_D2, tHDMI_EDID_FHD_TABLE, sizeof(tHDMI_EDID_FHD_TABLE));
#endif

#endif
            break;
#endif // #if(_D2_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)


#if(_D3_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
        case _D3_INPUT_PORT_EDID:

#if(_D3_HDMI_SUPPORT == _ON)

#if(_D3_HDMI_MULTI_EDID_SUPPORT == _ON)
            enumIndex = UserInterfaceEdidGetMultiHdmiEdidIndex(_D3_INPUT_PORT);

            if(UserCommonEdidGetMultiHdmiEdidLocation(_D3_INPUT_PORT, enumIndex) != _HDMI_EDID_EXTERNAL)
            {
                BYTE pucEdidContent[_D3_EMBEDDED_DDCRAM_MAX_SIZE] = {0};

                memset(pucEdidContent, 0, _D3_EMBEDDED_DDCRAM_MAX_SIZE);
                memcpy(pucEdidContent, tHDMI_EDID_TABLE[enumIndex], tHDMI_EDID_TABLE_SIZE[enumIndex]);

#if((_HDMI_HLG_SUPPORT == _ON) || (_HDMI21_RX_DSC_DECODER_SUPPORT == _ON) || (_HDMI_FREESYNC_SUPPORT == _ON) || (_AUDIO_ARC_SUPPORT == _ON))
                if(UserCommonEdidOnlineEdidModify(pucEdidContent, UserAdjustGetEdidModifyTarget(_D3_INPUT_PORT)) == _TRUE)
                {
                    // Set Modified Edid to DDCRAM
                    memcpy(MCU_DDCRAM_D3, pucEdidContent, _D3_EMBEDDED_DDCRAM_MAX_SIZE);
                }
                else
#endif

                {
                    // Set Raw Edid to DDCRAM
                    memcpy(MCU_DDCRAM_D3, tHDMI_EDID_TABLE[enumIndex], tHDMI_EDID_TABLE_SIZE[enumIndex]);
                }
            }
#else
            memset(MCU_DDCRAM_D3, 0, _D3_EMBEDDED_DDCRAM_MAX_SIZE);
            memcpy(MCU_DDCRAM_D3, tHDMI_EDID_FHD_TABLE, sizeof(tHDMI_EDID_FHD_TABLE));
#endif

#endif
            break;
#endif // #if(_D3_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)

#if(_D4_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
        case _D4_INPUT_PORT_EDID:

#if(_D4_HDMI_SUPPORT == _ON)

#if(_D4_HDMI_MULTI_EDID_SUPPORT == _ON)
            enumIndex = UserInterfaceEdidGetMultiHdmiEdidIndex(_D4_INPUT_PORT);

            if(UserCommonEdidGetMultiHdmiEdidLocation(_D4_INPUT_PORT, enumIndex) != _HDMI_EDID_EXTERNAL)
            {
                BYTE pucEdidContent[_D4_EMBEDDED_DDCRAM_MAX_SIZE] = {0};

                memset(pucEdidContent, 0, _D4_EMBEDDED_DDCRAM_MAX_SIZE);
                memcpy(pucEdidContent, tHDMI_EDID_TABLE[enumIndex], tHDMI_EDID_TABLE_SIZE[enumIndex]);

#if((_HDMI_HLG_SUPPORT == _ON) || (_HDMI21_RX_DSC_DECODER_SUPPORT == _ON) || (_HDMI_FREESYNC_SUPPORT == _ON) || (_AUDIO_ARC_SUPPORT == _ON))
                if(UserCommonEdidOnlineEdidModify(pucEdidContent, UserAdjustGetEdidModifyTarget(_D4_INPUT_PORT)) == _TRUE)
                {
                    // Set Modified Edid to DDCRAM
                    memcpy(MCU_DDCRAM_D4, pucEdidContent, _D4_EMBEDDED_DDCRAM_MAX_SIZE);
                }
                else
#endif
                {
                    // Set Raw Edid to DDCRAM
                    memcpy(MCU_DDCRAM_D4, tHDMI_EDID_TABLE[enumIndex], tHDMI_EDID_TABLE_SIZE[enumIndex]);
                }
            }
#else
            memset(MCU_DDCRAM_D4, 0, _D4_EMBEDDED_DDCRAM_MAX_SIZE);
            memcpy(MCU_DDCRAM_D4, tHDMI_EDID_FHD_TABLE, sizeof(tHDMI_EDID_FHD_TABLE));

#endif

#endif
            break;
#endif // #if(_D4_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)

#if(_D5_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
        case _D5_INPUT_PORT_EDID:

#if(_D5_HDMI_SUPPORT == _ON)

#if(_D5_HDMI_MULTI_EDID_SUPPORT == _ON)
            enumIndex = UserInterfaceEdidGetMultiHdmiEdidIndex(_D5_INPUT_PORT);

            if(UserCommonEdidGetMultiHdmiEdidLocation(_D5_INPUT_PORT, enumIndex) != _HDMI_EDID_EXTERNAL)
            {
                BYTE pucEdidContent[_D5_EMBEDDED_DDCRAM_MAX_SIZE] = {0};

                memset(pucEdidContent, 0, _D5_EMBEDDED_DDCRAM_MAX_SIZE);
                memcpy(pucEdidContent, tHDMI_EDID_TABLE[enumIndex], tHDMI_EDID_TABLE_SIZE[enumIndex]);

#if((_HDMI_HLG_SUPPORT == _ON) || (_HDMI21_RX_DSC_DECODER_SUPPORT == _ON) || (_HDMI_FREESYNC_SUPPORT == _ON) || (_AUDIO_ARC_SUPPORT == _ON))
                if(UserCommonEdidOnlineEdidModify(pucEdidContent, UserAdjustGetEdidModifyTarget(_D5_INPUT_PORT)) == _TRUE)
                {
                    // Set Modified Edid to DDCRAM
                    memcpy(MCU_DDCRAM_D5, pucEdidContent, _D5_EMBEDDED_DDCRAM_MAX_SIZE);
                }
                else
#endif
                {
                    // Set Raw Edid to DDCRAM
                    memcpy(MCU_DDCRAM_D5, tHDMI_EDID_TABLE[enumIndex], tHDMI_EDID_TABLE_SIZE[enumIndex]);
                }
            }
#else
            memset(MCU_DDCRAM_D5, 0, _D5_EMBEDDED_DDCRAM_MAX_SIZE);
            memcpy(MCU_DDCRAM_D5, tHDMI_EDID_FHD_TABLE, sizeof(tHDMI_EDID_FHD_TABLE));
#endif

#endif
            break;
#endif // #if(_D5_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)

#if(_D6_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
        case _D6_INPUT_PORT_EDID:

#if(_D6_INPUT_PORT_TYPE == _D6_DP_PORT)

            memset(MCU_DDCRAM_D6, 0, _D6_EMBEDDED_DDCRAM_MAX_SIZE);
            enumIndex = UserAdjustGetDpEdidIndex(_D6_INPUT_PORT);

#if(_HW_DP_HIGH_RESOL_SUPPORT == _ON)
            if(UserCommonNVRamGetSystemData(_EDID_D6_SELECT) >= _DP_EDID_4K2K_240HZ)
            {
                BYTE pucEdidContent[_D6_EMBEDDED_DDCRAM_MAX_SIZE] = {0};

                memcpy(pucEdidContent, tDP_EDID_TABLE_BY_RESOL_1[enumIndex], tDP_EDID_TABLE_SIZE_BY_RESOL_1[enumIndex]);

#if((_DP_HLG_SUPPORT == _ON) || (_AUDIO_ARC_SUPPORT == _ON))
                if(UserCommonEdidOnlineEdidModify(pucEdidContent, UserAdjustGetEdidModifyTarget(_D6_INPUT_PORT)) == _TRUE)
                {
                    // Set Modified Edid to DDCRAM
                    memcpy(MCU_DDCRAM_D6, pucEdidContent, _D6_EMBEDDED_DDCRAM_MAX_SIZE);
                }
                else
#endif
                {
                    // Set Raw Edid to DDCRAM
                    memcpy(MCU_DDCRAM_D6, tDP_EDID_TABLE_BY_RESOL_1[enumIndex], tDP_EDID_TABLE_SIZE_BY_RESOL_1[enumIndex]);
                }
            }
            else
#endif
            {
                BYTE pucEdidContent[_D6_EMBEDDED_DDCRAM_MAX_SIZE] = {0};

                memcpy(pucEdidContent, tDP_EDID_TABLE_BY_RESOL_0[enumIndex], tDP_EDID_TABLE_SIZE_BY_RESOL_0[enumIndex]);

#if((_DP_HLG_SUPPORT == _ON) || (_AUDIO_ARC_SUPPORT == _ON))
                if(UserCommonEdidOnlineEdidModify(pucEdidContent, UserAdjustGetEdidModifyTarget(_D6_INPUT_PORT)) == _TRUE)
                {
                    // Set Modified Edid to DDCRAM
                    memcpy(MCU_DDCRAM_D6, pucEdidContent, _D6_EMBEDDED_DDCRAM_MAX_SIZE);
                }
                else
#endif
                {
                    // Set Raw Edid to DDCRAM
                    memcpy(MCU_DDCRAM_D6, tDP_EDID_TABLE_BY_RESOL_0[enumIndex], tDP_EDID_TABLE_SIZE_BY_RESOL_0[enumIndex]);
                }
            }

#endif
            break;
#endif // #if(_D6_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)

        case _D7_INPUT_PORT_EDID:

#if(_D7_INPUT_PORT_TYPE == _D7_DP_PORT)

#if((_D0_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) &&\
    (_D1_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE))
            switch(UserCommonNVRamGetSystemData(_DUAL_DP_EDID_SELECT))
            {
                case _DUAL_DP_EDID_5K3K_60HZ:
                    if(_D0_EMBEDDED_DDCRAM_MAX_SIZE > sizeof(tEDID_TABLE_DP_5K3K_60_D0))
                    {
                        memset(MCU_DDCRAM_D0, 0, _D0_EMBEDDED_DDCRAM_MAX_SIZE);
                    }
                    memcpy(MCU_DDCRAM_D0, tEDID_TABLE_DP_5K3K_60_D0, sizeof(tEDID_TABLE_DP_5K3K_60_D0));

                    if(_D1_EMBEDDED_DDCRAM_MAX_SIZE > sizeof(tEDID_TABLE_DP_5K3K_60_D1))
                    {
                        memcpy(MCU_DDCRAM_D1, 0, _D1_EMBEDDED_DDCRAM_MAX_SIZE);
                    }
                    memcpy(MCU_DDCRAM_D1, tEDID_TABLE_DP_5K3K_60_D1, sizeof(tEDID_TABLE_DP_5K3K_60_D1));
                    break;

                case _DUAL_DP_EDID_4K2K_144HZ:
                    if(_D0_EMBEDDED_DDCRAM_MAX_SIZE > sizeof(tEDID_TABLE_DP_4K2K_144_D0))
                    {
                        memset(MCU_DDCRAM_D0, 0, _D0_EMBEDDED_DDCRAM_MAX_SIZE);
                    }
                    memcpy(MCU_DDCRAM_D0, tEDID_TABLE_DP_4K2K_144_D0, sizeof(tEDID_TABLE_DP_4K2K_144_D0));

                    if(_D1_EMBEDDED_DDCRAM_MAX_SIZE > sizeof(tEDID_TABLE_DP_4K2K_144_D1))
                    {
                        memcpy(MCU_DDCRAM_D1, 0, _D1_EMBEDDED_DDCRAM_MAX_SIZE);
                    }
                    memcpy(MCU_DDCRAM_D1, tEDID_TABLE_DP_4K2K_144_D1, sizeof(tEDID_TABLE_DP_4K2K_144_D1));
                    break;

                case _DUAL_DP_EDID_8K4K_60HZ:
                    if(_D0_EMBEDDED_DDCRAM_MAX_SIZE > sizeof(tEDID_TABLE_DP_8K4K_60_D0))
                    {
                        memset(MCU_DDCRAM_D0, 0, _D0_EMBEDDED_DDCRAM_MAX_SIZE);
                    }
                    memcpy(MCU_DDCRAM_D0, tEDID_TABLE_DP_8K4K_60_D0, sizeof(tEDID_TABLE_DP_8K4K_60_D0));

                    if(_D1_EMBEDDED_DDCRAM_MAX_SIZE > sizeof(tEDID_TABLE_DP_8K4K_60_D1))
                    {
                        memset(MCU_DDCRAM_D1, 0, _D1_EMBEDDED_DDCRAM_MAX_SIZE);
                    }
                    memcpy(MCU_DDCRAM_D1, tEDID_TABLE_DP_8K4K_60_D1, sizeof(tEDID_TABLE_DP_8K4K_60_D1));
                    break;

                default:
                    break;
            }
#endif

#endif
            break;

        case _D8_INPUT_PORT_EDID:

#if(_D8_INPUT_PORT_TYPE == _D8_DP_PORT)

#if((_D1_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) &&\
    (_D2_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE))
            if(UserCommonNVRamGetSystemData(_DUAL_DP_EDID_SELECT) == _DUAL_DP_EDID_5K3K_60HZ)
            {
                memcpy(MCU_DDCRAM_D1, tEDID_TABLE_DP_5K3K_60_D1, _D8_D1_EMBEDDED_DDCRAM_SIZE);
                memcpy(MCU_DDCRAM_D2, tEDID_TABLE_DP_5K3K_60_D2, _D8_D2_EMBEDDED_DDCRAM_SIZE);
            }
            else if(UserCommonNVRamGetSystemData(_DUAL_DP_EDID_SELECT) == _DUAL_DP_EDID_4K2K_144HZ)
            {
                memcpy(MCU_DDCRAM_D1, tEDID_TABLE_DP_4K2K_144_D1, _D8_D1_EMBEDDED_DDCRAM_SIZE);
                memcpy(MCU_DDCRAM_D2, tEDID_TABLE_DP_4K2K_144_D2, _D8_D2_EMBEDDED_DDCRAM_SIZE);
            }
            else if(UserCommonNVRamGetSystemData(_DUAL_DP_EDID_SELECT) == _DUAL_DP_EDID_8K4K_60HZ)
            {
                memcpy(MCU_DDCRAM_D1, tEDID_TABLE_DP_8K4K_60_D1, _D8_D1_EMBEDDED_DDCRAM_SIZE);
                memcpy(MCU_DDCRAM_D2, tEDID_TABLE_DP_8K4K_60_D2, _D8_D2_EMBEDDED_DDCRAM_SIZE);
            }
#endif

#endif
            break;

        case _D9_INPUT_PORT_EDID:

#if((_DP_SUPPORT == _ON) && (_D9_INPUT_PORT_TYPE == _D9_DP_PORT))
#if(_D9_EMBEDDED_XRAM_MAX_SIZE != _EDID_SIZE_NONE)

#if(_DP_MST_PXP_LOAD_D9_EDID_BY_INPUT_PORT == _ON)
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
            memset(g_pucDpRx0PxpEdid, 0, _D9_EMBEDDED_XRAM_MAX_SIZE);

            // Set Raw Edid to XRAM
            memcpy(g_pucDpRx0PxpEdid, tDP_EDID_TABLE_BY_RESOL_0[enumIndex], tDP_EDID_TABLE_SIZE_BY_RESOL_0[enumIndex]);
#endif
#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
            memset(g_pucDpRx1PxpEdid, 0, _D9_EMBEDDED_XRAM_MAX_SIZE);

            // Set Raw Edid to XRAM
            memcpy(g_pucDpRx1PxpEdid, tDP_EDID_TABLE_BY_RESOL_0[enumIndex], tDP_EDID_TABLE_SIZE_BY_RESOL_0[enumIndex]);
#endif
#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
            memset(g_pucDpRx2PxpEdid, 0, _D9_EMBEDDED_XRAM_MAX_SIZE);

            // Set Raw Edid to XRAM
            memcpy(g_pucDpRx2PxpEdid, tDP_EDID_TABLE_BY_RESOL_0[enumIndex], tDP_EDID_TABLE_SIZE_BY_RESOL_0[enumIndex]);
#endif
#else
            memset(g_pucDpRxPxpEdid, 0, _D9_EMBEDDED_XRAM_MAX_SIZE);

            // Set Raw Edid to XRAM
            memcpy(g_pucDpRxPxpEdid, tDP_EDID_TABLE_BY_RESOL_0[enumIndex], tDP_EDID_TABLE_SIZE_BY_RESOL_0[enumIndex]);
#endif

#endif
#endif
            break;

        default:
            break;
    }
}

#if((_HDMI_EXTERNAL_SWITCH_SUPPORT == _ON) && ((_D3_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) || (_D4_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)))
//--------------------------------------------------
// Description  : Reload HDMI EDID
// Input Value  : enumInputPort --> switch target
// Output Value : None
//--------------------------------------------------
void UserInterfaceEdidReloadHdmiExternalSwitchEmbeddedEdid(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
        case _D3_INPUT_PORT:
            memset(MCU_DDCRAM_D3, 0, _D3_EMBEDDED_DDCRAM_MAX_SIZE);
            memcpy(MCU_DDCRAM_D3, tHDMI_D3_EDID_TABLE, _D3_EMBEDDED_DDCRAM_MAX_SIZE);
            break;

        case _D4_INPUT_PORT:
            memset(MCU_DDCRAM_D4, 0, _D4_EMBEDDED_DDCRAM_MAX_SIZE);
            memcpy(MCU_DDCRAM_D4, tHDMI_D4_EDID_TABLE, _D4_EMBEDDED_DDCRAM_MAX_SIZE);
            break;

        case _D12_INPUT_PORT:
            memset(MCU_DDCRAM_D3, 0, _D3_EMBEDDED_DDCRAM_MAX_SIZE);
            memcpy(MCU_DDCRAM_D3, tHDMI_D12_EDID_TABLE, _D3_EMBEDDED_DDCRAM_MAX_SIZE);
            break;

        case _D13_INPUT_PORT:
            memset(MCU_DDCRAM_D3, 0, _D3_EMBEDDED_DDCRAM_MAX_SIZE);
            memcpy(MCU_DDCRAM_D3, tHDMI_D13_EDID_TABLE, _D3_EMBEDDED_DDCRAM_MAX_SIZE);
            break;

        case _D14_INPUT_PORT:
            memset(MCU_DDCRAM_D4, 0, _D4_EMBEDDED_DDCRAM_MAX_SIZE);
            memcpy(MCU_DDCRAM_D4, tHDMI_D14_EDID_TABLE, _D4_EMBEDDED_DDCRAM_MAX_SIZE);
            break;

        case _D15_INPUT_PORT:
            memset(MCU_DDCRAM_D4, 0, _D4_EMBEDDED_DDCRAM_MAX_SIZE);
            memcpy(MCU_DDCRAM_D4, tHDMI_D15_EDID_TABLE, _D4_EMBEDDED_DDCRAM_MAX_SIZE);
            break;

        default:
            break;
    }
}
#endif
#endif // End of #if(_WRITE_EDID_LOCATION_BY_USER_SUPPORT == _ON)

#if(_HDMI_MULTI_EDID_SUPPORT == _ON)
#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Check EDID DSC Cap need to reload
// Input Value  : enumInputPort
// Output Value : bit
//--------------------------------------------------
EnumEdidReloadCheck UserInterfaceEdidCheckHdmiDscEdidIndexChange(EnumInputPort enumInputPort)
{
    enumInputPort = enumInputPort;
    return _EDID_NEED_CHANGE;
}
#endif

//--------------------------------------------------
// Description  : Get HPD Toggle w/ Mode state back to search or not
// Input Value  : BYTE InputPort
// Output Value : _TRUE (HPD Toggle & return to Search State)
//--------------------------------------------------
EnumHdmiEdidHpdBehavior UserInterfaceEdidGetHpdToggleResetToSearch(void)
{
    return _EDID_HPD_RETURN_SEARCH;
}

//--------------------------------------------------
// Description  : Get the HDMI Port Edid location
// Input Value  : EDID Index
// Output Value : External/ Embedded Edid
//--------------------------------------------------
EnumHdmiEdidLocation UserInterfaceEdidGetMultiHdmiEdidLocation(BYTE ucPortIndex, EnumEdidSelection enumEdidIndex)
{
    return tEdidMultiLocatedTable[ucPortIndex][enumEdidIndex];
}

//--------------------------------------------------
// Description  : Get the Mapping of Edid index of Function Application
// Input Value  : enumInputPort
// Output Value : Edid Index Enum
//--------------------------------------------------
EnumEdidSelection UserInterfaceEdidGetMultiHdmiEdidIndex(EnumInputPort enumInputPort)
{
    EnumEdidSelection enumIndex = _EDID_INDEX_0;
    BYTE ucHdmiVer = OsdFuncGetHdmiPortVersion(enumInputPort);
/*
#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
    if(UserInterfaceDscDecoderGetEnable(enumInputPort) == _DSC_DECODER_SUPPORT_ON)
    {
        enumIndex += ((_HDMI_FREESYNC_SUPPORT == _ON) ? ((_HDMI_HDR10_SUPPORT == _ON) ? 12 : 6) : ((_HDMI_HDR10_SUPPORT == _ON) ? 6 : 3));
    }
#endif
*/
#if(_HDMI_FREESYNC_SUPPORT == _ON)
    if(GET_OSD_FREE_SYNC_STATUS() == _ON)
    {
        enumIndex += ((_HDMI_HDR10_SUPPORT == _ON) ? 0x06 : 0x03);
    }
#endif

#if(_HDMI_HDR10_SUPPORT == _ON)
    if(UserInterfaceColorHDRGetHDR10ModeStatus(enumInputPort) != _HDR10_MODE_OFF)
    {
        enumIndex += 0x03;
    }
#endif

    switch(ucHdmiVer)
    {
        case _HDMI_1P4:
            break;

        case _HDMI_2P0:
            enumIndex += 0x01;
            break;

#if(_HDMI_FRL_SUPPORT == _ON)
        case _HDMI_2P1:
            enumIndex += 0x02;
            break;
#endif

        default:
            break;
    }
    return enumIndex;
}
#endif

#if((_EDID_EXTERNAL_EEPROM_MAX_SIZE != _EDID_SIZE_NONE) && ((_HDMI_FREESYNC_SUPPORT == _ON) || (_HDMI21_VRR_SUPPORT == _ON) || (_HDMI21_FVA_SUPPORT == _ON)))
//--------------------------------------------------
// Description  : Get the Mapping of Edid index of Function Application
// Input Value  : pucEdidContent
// Output Value : Edid Index Enum
//--------------------------------------------------
void UserInterfaceEdidGetExternalEdid(EnumInputPort enumInputPort, BYTE *pucEdidContent)
{
    switch(enumInputPort)
    {
        case _D1_INPUT_PORT:
#if(_D1_HDMI_MULTI_EDID_SUPPORT == _ON)
            memcpy(pucEdidContent, tHDMI_EXT_EEPROM_EDID_TABLE[UserAdjustGetHdmiExternalEdidIndex(enumInputPort)], _EDID_EXTERNAL_EEPROM_MAX_SIZE);
#else
            memcpy(pucEdidContent, tHDMI_EXT_EEPROM_EDID_TABLE[0], _EDID_EXTERNAL_EEPROM_MAX_SIZE);
#endif
            break;

        case _D2_INPUT_PORT:
#if(_D2_HDMI_MULTI_EDID_SUPPORT == _ON)
            memcpy(pucEdidContent, tHDMI_EXT_EEPROM_EDID_TABLE[UserAdjustGetHdmiExternalEdidIndex(enumInputPort)], _EDID_EXTERNAL_EEPROM_MAX_SIZE);
#else
            memcpy(pucEdidContent, tHDMI_EXT_EEPROM_EDID_TABLE[0], _EDID_EXTERNAL_EEPROM_MAX_SIZE);
#endif
            break;

        case _D3_INPUT_PORT:
#if(_D3_HDMI_MULTI_EDID_SUPPORT == _ON)
            memcpy(pucEdidContent, tHDMI_EXT_EEPROM_EDID_TABLE[UserAdjustGetHdmiExternalEdidIndex(enumInputPort)], _EDID_EXTERNAL_EEPROM_MAX_SIZE);
#else
            memcpy(pucEdidContent, tHDMI_EXT_EEPROM_EDID_TABLE[0], _EDID_EXTERNAL_EEPROM_MAX_SIZE);
#endif
            break;

        case _D4_INPUT_PORT:
#if(_D4_HDMI_MULTI_EDID_SUPPORT == _ON)
            memcpy(pucEdidContent, tHDMI_EXT_EEPROM_EDID_TABLE[UserAdjustGetHdmiExternalEdidIndex(enumInputPort)], _EDID_EXTERNAL_EEPROM_MAX_SIZE);
#else
            memcpy(pucEdidContent, tHDMI_EXT_EEPROM_EDID_TABLE[0], _EDID_EXTERNAL_EEPROM_MAX_SIZE);
#endif
            break;

        case _D5_INPUT_PORT:
#if(_D5_HDMI_MULTI_EDID_SUPPORT == _ON)
            memcpy(pucEdidContent, tHDMI_EXT_EEPROM_EDID_TABLE[UserAdjustGetHdmiExternalEdidIndex(enumInputPort)], _EDID_EXTERNAL_EEPROM_MAX_SIZE);
#else
            memcpy(pucEdidContent, tHDMI_EXT_EEPROM_EDID_TABLE[0], _EDID_EXTERNAL_EEPROM_MAX_SIZE);
#endif
            break;

        default:
            break;
    }
}
#endif
#endif // End of #if(_OSD_TYPE == _REALTEK_2020_OSD)
