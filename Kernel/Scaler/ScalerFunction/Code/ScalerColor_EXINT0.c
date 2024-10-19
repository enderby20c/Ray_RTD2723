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
// ID Code      : ScalerColor_EXINT0.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_COLOR__

#include "ScalerFunctionInclude.h"
#include "Color/ScalerColor.h"



//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************

//****************************************************************************
// CODE TABLES
//****************************************************************************

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************

#if(_ADVANCED_HDR10_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Save Advanced HDR10 VSIF Infomation to Global Variable, and back up previous HDR10 VSIF
// Input Value  : StructAdvancedHDR10MetaData stSyncAdvancedHDR10Metadata
// Output Value : None
//--------------------------------------------------
void ScalerColorAdvancedHDR10VSIFHandler_EXINT0(StructAdvancedHDR10MetaData *pstSyncAdvancedHDR10Metadata)
{
    if(GET_ADVANCED_HDR10_INITIAL_READY() == _TRUE)
    {
        bit bMetadtaChange = _FALSE;
        bit bSendCmd = _FALSE;

#if(_ADVANCED_HDR10_DHDR_SUPPORT == _ON)
        SET_ADVANCED_HDR10_METADATA_TYPE(_ADVANDED_HDR10_VSIF_METADATA);
#endif

        // Acquire Advanced HDR10 Metadata resource lock
        if(RESOURCE_ACQUIRE(_RESOURCE_ID_COLOR_ADVANCED_HDR10_METADATA, 10) == _FALSE)
        {
            return;
        }

        __real_memcpy(&g_stSyncAdvancedHDR10BackUpMetadata, &g_stSyncAdvancedHDR10Metadata, sizeof(StructAdvancedHDR10MetaData));
        __real_memcpy(&g_stSyncAdvancedHDR10Metadata, pstSyncAdvancedHDR10Metadata, sizeof(StructAdvancedHDR10MetaData));

        bMetadtaChange = (__real_memcmp(&g_stSyncAdvancedHDR10BackUpMetadata, &g_stSyncAdvancedHDR10Metadata, sizeof(StructAdvancedHDR10MetaData)) != 0);

        // According to Delay or No-Delay Mode, then judge if back-up metadata or metadata has changed.
#if(_FRC_SUPPORT == _ON)
        if(GET_ADVANCED_HDR10_DELAY_MODE() == _TRUE) // Delay Mode
        {
            bSendCmd = GET_ADVANCED_HDR10_BACKUP_METADATA_CHANGE();
            SET_ADVANCED_HDR10_BACKUP_METADATA_CHANGE(bMetadtaChange); // record backup metadata change status
        }
        else
#endif
        {
            bSendCmd = bMetadtaChange; // No Delay Mode
            CLR_ADVANCED_HDR10_BACKUP_METADATA_CHANGE(); // clear backup metadata change status
        }

        // Release Advanced HDR10 Metadata resource lock
        RESOURCE_RELEASE(_RESOURCE_ID_COLOR_ADVANCED_HDR10_METADATA);

        if((bSendCmd == _TRUE) || (GET_ADVANCED_HDR10_METADATA_REAPPLY() == _TRUE))
        {
            CLR_ADVANCED_HDR10_YM_TABLE_READY();
            CLR_ADVANCED_HDR10_METADATA_REAPPLY();
            SET_ADVANCED_HDR10_SECOND_CPU_IRQ_FLAG();
            ScalerCpuHalSetSecondCpuSw0IRQ();
        }
    }
}

//--------------------------------------------------
// Description  : AdvancedHDR10 Interrupt process for PCM HLW DB
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerColorAdvancedHDR10PCMHLWDBIntHandler_EXINT0(void)
{
    if((ScalerGetBit_EXINT(P4F_D0_PCM_HLW_DB_A_CTRL, _BIT4) == _BIT4) || (ScalerGetBit_EXINT(P4F_D1_PCM_HLW_DB_B_CTRL, _BIT4) == _BIT4))
    {
        EnumAdvancedHDR10PCMHLWDBStatus enumAdvancedHDR10PCMHLWDBStatus = _ADVANCED_HDR10_PCM_HLW_DB_UNKNOWN;

        if(ScalerGetBit_EXINT(P4F_D0_PCM_HLW_DB_A_CTRL, _BIT4) == _BIT4)
        {
            ScalerColorPCMHLWDBReInitial(_PCM_HLW_DB_A);
            CLR_ADVANCED_HDR10_FAKE_APPLY_A();
        }

        if(ScalerGetBit_EXINT(P4F_D1_PCM_HLW_DB_B_CTRL, _BIT4) == _BIT4)
        {
            ScalerColorPCMHLWDBReInitial(_PCM_HLW_DB_B);
            CLR_ADVANCED_HDR10_FAKE_APPLY_B();
        }

        if(GET_ADVANCED_HDR10_NOTIFY_INT() == _TRUE)
        {
            CLR_ADVANCED_HDR10_COLOR_APPLY_A();
            CLR_ADVANCED_HDR10_COLOR_APPLY_B();
            ScalerSetBit_EXINT(P4F_D0_PCM_HLW_DB_A_CTRL, ~(_BIT6 | _BIT4 | _BIT1), 0x00);
            ScalerSetBit_EXINT(P4F_D1_PCM_HLW_DB_B_CTRL, ~(_BIT6 | _BIT4 | _BIT1), 0x00);

            SET_ADVANCED_HDR10_RESTORE_PCM_HLW_DB_STATUS(ScalerColorAdvancedHDR10GetPCMHLWDBStatus(_ADVANCED_HDR10_PCM_HLW_DB_PROC_NORAML));
#if(_IS_MAIN_PROCESS_CPU == _TRUE)
            SET_ADVANCED_HDR10_MAIN_CPU_IRQ_FLAG();
            ScalerCpuHalSetMainCpuSw0IRQ();
#endif
        }
        else
        {
            enumAdvancedHDR10PCMHLWDBStatus = ScalerColorAdvancedHDR10GetPCMHLWDBStatus(_ADVANCED_HDR10_PCM_HLW_DB_PROC_IRQ);
            ScalerColorAdvancedHDR10PCMHLWDBProc(enumAdvancedHDR10PCMHLWDBStatus);
        }
    }
}

#if(_ADVANCED_HDR10_DHDR_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Save Advanced HDR10 DHDR Metadata Infomation to Global Variable
// Input Value  : BYTE* stSyncAdvancedHDR10Metadata
// Output Value : None
//--------------------------------------------------
void ScalerColorAdvancedHDR10DHDRHandler_EXINT0(BYTE *pucDHDRMetaData)
{
    if(GET_ADVANCED_HDR10_INITIAL_READY() == _TRUE)
    {
        bit bMetadtaChange = _FALSE;
        BYTE ucIndex = 0;
        StructAdvancedHDR10DHDRMetaData stCurrentAdvancedHDR10DHDRMetaData = {0};

        SET_ADVANCED_HDR10_METADATA_TYPE(_ADVANDED_HDR10_DHDR_METADATA);

        stCurrentAdvancedHDR10DHDRMetaData.ucIdentifier = pucDHDRMetaData[5];
        stCurrentAdvancedHDR10DHDRMetaData.ucVersion = pucDHDRMetaData[6];
        stCurrentAdvancedHDR10DHDRMetaData.ulDistribution50 = ((((DWORD)pucDHDRMetaData[39] << 16) | ((DWORD)pucDHDRMetaData[40] << 8) | (pucDHDRMetaData[41])) >> 7);
        stCurrentAdvancedHDR10DHDRMetaData.ulDistribution99 = ((((DWORD)pucDHDRMetaData[51] << 16) | ((DWORD)pucDHDRMetaData[52] << 8) | (pucDHDRMetaData[53])) >> 7);
        stCurrentAdvancedHDR10DHDRMetaData.ulDistribution50 = MINOF(stCurrentAdvancedHDR10DHDRMetaData.ulDistribution50, 100000); // Source max lv should be less than 10000nit (unit 0.1nit)
        stCurrentAdvancedHDR10DHDRMetaData.ulDistribution99 = MINOF(stCurrentAdvancedHDR10DHDRMetaData.ulDistribution99, 100000); // Source max lv should be less than 10000nit (unit 0.1nit
        stCurrentAdvancedHDR10DHDRMetaData.usTargetDisplayLv = (WORD)MINOF(((((DWORD)pucDHDRMetaData[28] << 24) | ((DWORD)pucDHDRMetaData[29] << 16) | ((DWORD)pucDHDRMetaData[30] << 8) | (pucDHDRMetaData[31])) >> 5), 10000);

        for(ucIndex = 0; ucIndex < 9; ucIndex++)
        {
            stCurrentAdvancedHDR10DHDRMetaData.pusBezierAnchor[ucIndex] = (((WORD)(pucDHDRMetaData[91 + ucIndex] << 8) | (pucDHDRMetaData[92 + ucIndex])) >> 6);
        }

        stCurrentAdvancedHDR10DHDRMetaData.pusKneePoint[0] = (((WORD)(pucDHDRMetaData[86] << 8) | (pucDHDRMetaData[87])) >> 4);
        stCurrentAdvancedHDR10DHDRMetaData.pusKneePoint[1] = (((WORD)(pucDHDRMetaData[88] << 8) | (pucDHDRMetaData[89])) >> 4);

        bMetadtaChange = (__real_memcmp(&g_stSyncAdvancedHDR10DHDRMetaData, &stCurrentAdvancedHDR10DHDRMetaData, sizeof(StructAdvancedHDR10DHDRMetaData)) != 0);

        if(bMetadtaChange == _TRUE)
        {
            // Acquire Advanced HDR10 Metadata resource lock
            if(RESOURCE_ACQUIRE(_RESOURCE_ID_COLOR_ADVANCED_HDR10_METADATA, 10) == _FALSE)
            {
                return;
            }

            __real_memcpy(&g_stSyncAdvancedHDR10DHDRMetaData, &stCurrentAdvancedHDR10DHDRMetaData, sizeof(StructAdvancedHDR10DHDRMetaData));

            // Release Advanced HDR10 Metadata resource lock
            RESOURCE_RELEASE(_RESOURCE_ID_COLOR_ADVANCED_HDR10_METADATA);

            CLR_ADVANCED_HDR10_YM_TABLE_READY();
            CLR_ADVANCED_HDR10_METADATA_REAPPLY();
            SET_ADVANCED_HDR10_SECOND_CPU_IRQ_FLAG();
            ScalerCpuHalSetSecondCpuSw0IRQ();
        }
    }
}

//--------------------------------------------------
// Description  : check DHDR data
// Input Value  : ucContryCode, usProviderCode, usProviderOrientedCode, ucAppIdentifier, ucAppVersion
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
bit ScalerColorAdvancedHDR10CheckDHDRMetadta_EXINT0(BYTE ucContryCode, WORD usProviderCode, WORD usProviderOrientedCode, BYTE ucAppIdentifier, BYTE ucAppVersion)
{
    return ((ucContryCode == _ADVANCED_HDR10_DHDR_CONTRY_CODE) &&
            (usProviderCode == _ADVANCED_HDR10_DHDR_PROVIDER_CODE) &&
            (usProviderOrientedCode == _ADVANCED_HDR10_DHDR_PROVIDER_ORIENTTED_CODE) &&
            (ucAppIdentifier == _ADVANCED_HDR10_DHDR_APP_IDENTIFIER) &&
            (ucAppVersion == _ADVANCED_HDR10_DHDR_APP_VERSION));
}
#endif
#endif

#if(_COLOR_IP_LOCAL_CONTRAST == _ON)
#if(_COLOR_IP_LOCAL_CONTRAST_HISTOGRAM == _ON)
//--------------------------------------------------
// Description  : DRR MBR handler interrupt process (EXINT0 only)
//                Recording & calculating input & average framerate
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerColorLocalContrastIntHandler_EXINT0(void)
{
    // Step1: READ_STATUS = _FALSE & sw = 0 -> not read sram, set sw = 1 and READ_STATUS = 1
    // Step2: READ_STATUS = _TRUE  & sw = 1, not read sram finish yet, do nothing, keep origin READ_STATUS & sw mode status
    // Step3: READ_STATUS = _FALSE & sw = 1 -> read sram finished, set sw = 0
    // exception: READ_STATUS = _TRUE  & sw = 0 -> abnormal case, set READ_STATUS = 0 and sw = 0

    if(GET_LOCAL_CONTRAST_READY_TOREAD() == _FALSE)
    {
        // Step1:
        if(ScalerGetBit_EXINT(P32_99_LC_SRAM_CTRL_0_R1, _BIT1) != _BIT1)
        {
            // Enable R1 SW mode
            ScalerSetBit_EXINT(P32_99_LC_SRAM_CTRL_0_R1, ~_BIT1, _BIT1);

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
            // Judge Lcts FB Enable or not, FBPBPLREQUAL should disable FB mode
            if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_BEFORE_BLENDING) == _TRUE)
            {
                // Enable R3 SW mode
                ScalerSetBit_EXINT(PDD_99_LC_SRAM_CTRL_0_R3, ~_BIT1, _BIT1);
            }
#endif

            // Enable R2 SW mode
            if(GET_DISPLAY_MODE() != _DISPLAY_MODE_1P)
            {
                ScalerSetBit_EXINT(PC3_99_LC_SRAM_CTRL_0_R2, ~_BIT1, _BIT1);
            }

            SET_LOCAL_CONTRAST_READY_TOREAD();
        }
        else // Step3:
        {
            // Enable R1 SW mode
            ScalerSetBit_EXINT(P32_99_LC_SRAM_CTRL_0_R1, ~_BIT1, 0x00);

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
            // Judge Lcts FB Enable or not, FBPBPLREQUAL should disable FB mode
            if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_BEFORE_BLENDING) == _TRUE)
            {
                // Enable R3 SW mode
                ScalerSetBit_EXINT(PDD_99_LC_SRAM_CTRL_0_R3, ~_BIT1, 0x00);
            }
#endif

            // Disable R2 SW mode
            if(GET_DISPLAY_MODE() != _DISPLAY_MODE_1P)
            {
                ScalerSetBit_EXINT(PC3_99_LC_SRAM_CTRL_0_R2, ~_BIT1, 0x00);
            }
        }
    }
    else // exception:
    {
        if(ScalerGetBit_EXINT(P32_99_LC_SRAM_CTRL_0_R1, _BIT1) != _BIT1)
        {
            CLR_LOCAL_CONTRAST_READY_TOREAD();
        }
    }
}

#endif  // End of #if(_COLOR_IP_LOCAL_CONTRAST_HISTOGRAM == _ON)
#endif  // End of #if(_COLOR_IP_LOCAL_CONTRAST == _ON)