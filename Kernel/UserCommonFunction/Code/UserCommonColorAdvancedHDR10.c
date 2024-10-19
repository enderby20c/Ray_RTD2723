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
// ID Code      : UserCommonColorAdvancedHDR10.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include <UserCommonInclude.h>
#include <ColorAdvancedHDR10/UserCommonColorAdvancedHDR10.h>

#if((_HW_CPU32_NOTIFY_INT_SUPPORT == _ON) && (_HW_CPU32_IS_BOOT_CPU != _TRUE) && (_SCPU_SUPPORT == _ON))
#if(_ADVANCED_HDR10_SUPPORT == _ON)
//****************************************************************************
// CODE TABLES
//****************************************************************************

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Calculate Advanced HDR10 LUT based on received Metadata, then notify main CPU to update color setting.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonColorAdvancedHDR10SyncProcess(void)
{
    // Preparing for ADVANCED HDR10 TonaMapping Curve in Ymapping LUT 710 Bytes
    WORD usYMCompensate = 0;
    WORD usPanelMaxLv = GET_ADVANCED_HDR10_PANEL_MAX_LV();

#if(_ADVANCED_HDR10_DHDR_SUPPORT == _ON)
    if(GET_ADVANCED_HDR10_METADATA_TYPE() == _ADVANDED_HDR10_DHDR_METADATA)
    {
        StructColorAdvancedHDR10DHDRCoeff stColorAdvancedHDR10DHRCoeff = {0};

        // Acquire Advanced HDR10 Metadata resource lock
        if(RESOURCE_ACQUIRE(_RESOURCE_ID_COLOR_ADVANCED_HDR10_METADATA, 10) == _FALSE)
        {
            SET_ADVANCED_HDR10_METADATA_REAPPLY();
            return;
        }

        usYMCompensate = ScalerColorAdvancedHDR10SyncGetYMCompensate(_ADVANDED_HDR10_DHDR_METADATA, g_stSyncAdvancedHDR10DHDRMetaData.ulDistribution99, usPanelMaxLv);

        if(g_stSyncAdvancedHDR10DHDRMetaData.usTargetDisplayLv == 0) // profileA
        {
            ScalerColorAdvancedHDR10DHDRSyncBasisOOTF(&g_stSyncAdvancedHDR10DHDRMetaData, usPanelMaxLv, &stColorAdvancedHDR10DHRCoeff);
        }
        else  // profileB
        {
            ScalerColorAdvancedHDR10DHDRSyncGuidedOOTF(&g_stSyncAdvancedHDR10DHDRMetaData, usPanelMaxLv, &stColorAdvancedHDR10DHRCoeff);
        }

        // Release Advanced HDR10 Metadata resource lock
        RESOURCE_RELEASE(_RESOURCE_ID_COLOR_ADVANCED_HDR10_METADATA);

        ScalerColorAdvancedHDR10DHDRSyncGetLUT(g_pucSyncAdvancedHDR10YmTable, &stColorAdvancedHDR10DHRCoeff, usYMCompensate);
    }
    else
#endif
    {
        StructAdvancedHDR10MetaData stAdvancedHDR10Metadata;
        StructColorAdvancedHDR10Coeff stColorAdvancedHDR10Coeff = {0};

        // Acquire Advanced HDR10 Metadata resource lock
        if(RESOURCE_ACQUIRE(_RESOURCE_ID_COLOR_ADVANCED_HDR10_METADATA, 10) == _FALSE)
        {
            SET_ADVANCED_HDR10_METADATA_REAPPLY();
            return;
        }

        if(GET_ADVANCED_HDR10_DELAY_MODE() == _TRUE)
        {
            memcpy(&stAdvancedHDR10Metadata, &g_stSyncAdvancedHDR10BackUpMetadata, sizeof(StructAdvancedHDR10MetaData));
        }
        else
        {
            memcpy(&stAdvancedHDR10Metadata, &g_stSyncAdvancedHDR10Metadata, sizeof(StructAdvancedHDR10MetaData));
        }

        usYMCompensate = ScalerColorAdvancedHDR10SyncGetYMCompensate(_ADVANDED_HDR10_VSIF_METADATA, (WORD)stAdvancedHDR10Metadata.ucDistribution99, usPanelMaxLv);

        if(stAdvancedHDR10Metadata.ucTargetDisplayLv == 0) // profileA
        {
            ScalerColorAdvancedHDR10SyncBasisOOTF(&stAdvancedHDR10Metadata, usPanelMaxLv, &stColorAdvancedHDR10Coeff);
        }
        else  // profileB
        {
            ScalerColorAdvancedHDR10SyncGuidedOOTF(&stAdvancedHDR10Metadata, usPanelMaxLv, &stColorAdvancedHDR10Coeff);
        }

        // Release Advanced HDR10 Metadata resource lock
        RESOURCE_RELEASE(_RESOURCE_ID_COLOR_ADVANCED_HDR10_METADATA);

        ScalerColorAdvancedHDR10SyncGetLUT(g_pucSyncAdvancedHDR10YmTable, &stColorAdvancedHDR10Coeff, usYMCompensate);
    }

    SET_ADVANCED_HDR10_YM_TABLE_READY();

    // Send Cmd to 3081 to apply IG & Ymapping
    if(GET_ADVANCED_HDR10_COLOR_INITIAL_SETTING() == _TRUE)
    {
        ScalerColorCpuSyncIntNotifyAdvancedHDR10(_ADVANCED_HDR10_APPLY, _SCALER_CPU_SYNC_TIMEOUT_COLOR_ADVANCED_HDR10_APPLY);
    }
}

//--------------------------------------------------
// Description  : Advanced HDR10 Second CPU PendSV callback
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonColorAdvancedHDR10SecondCpuPendSVCallback(void)
{
    if(GET_ADVANCED_HDR10_SECOND_CPU_IRQ_FLAG() == _TRUE)
    {
        UserCommonColorAdvancedHDR10SyncProcess();
        CLR_ADVANCED_HDR10_SECOND_CPU_IRQ_FLAG();
    }
}
#endif
#endif
