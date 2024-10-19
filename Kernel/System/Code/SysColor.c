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
// ID Code      : SysColor.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SYSTEM_COLOR__

#include "SysInclude.h"
#include "Color/SysColor.h"

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
// Description  : Color Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysColorHandler(void)
{
    BYTE ucRegionIndex = 0;
    BYTE ucRegionCount = GET_RGN_MAX_DISPLAY_REGION();
    BYTE ucActiveRegionCount = 0;
    EnumDisplayRegion enumDisplayRegion = 0;

    for(ucRegionIndex = 0; ucRegionIndex < ucRegionCount; ++ucRegionIndex)
    {
#if(_COLOR_IP_DCC_HISTOGRAM == _ON)
        if((GET_RGN_DISPLAY_STATE(ucRegionIndex) == _DISPLAY_STATE_ACTIVE) && (GET_DCC_READY_STATUS() == _FALSE))
        {
            if(ScalerColorDCCGetDataReadyStatus() == _TRUE)
            {
                // Clear DCC data ready status.
                ScalerColorDCCClrDataReadyStatus();
                SET_DCC_READY_STATUS();
            }
        }
#endif

#if(_COLOR_IP_DCR == _ON)
        if((GET_RGN_DISPLAY_STATE(ucRegionIndex) == _DISPLAY_STATE_ACTIVE) && (GET_DCR_READY_STATUS() == _FALSE))
        {
            if(ScalerColorDCRGetDataReadyStatus() == _TRUE)
            {
                // Clear DCR data ready status.
                ScalerColorDCRClrDataReadyStatus();

                SET_DCR_READY_STATUS();

                // freeze DCR data
                ScalerColorDCRDataRefreshControl(_DISABLE);
            }
        }
#endif
    }

#if(_COLOR_IP_LOCAL_CONTRAST == _ON)
#if(_COLOR_IP_LOCAL_CONTRAST_HISTOGRAM == _ON)
#if((_LOCAL_CONTRAST_READYAVG_TOTAL_BLKNUM <= _LOCAL_CONTRAST_READYAVG_KCPU_BLKNUM_LIMIT) && (_HW_CPU32_IS_BOOT_CPU == _TRUE))
#if(_FW_CPU32_IS_HIGH_SPEED_CPU == _TRUE)
    if((GET_LOCAL_CONTRAST_READY_TOREAD() == _ENABLE) && (ScalerColorLocalContrastGetYavgSWmodeStatus() == _TRUE))
    {
        ScalerColorLocalContrastReadYavg();
        CLR_LOCAL_CONTRAST_READY_TOREAD();
    }
#endif
#endif
#endif
#endif


    for(ucRegionIndex = 0; ucRegionIndex < ucRegionCount; ++ucRegionIndex)
    {
        enumDisplayRegion = GET_RGN_DISPLAY_REGION(ucRegionIndex);

        switch(GET_RGN_DISPLAY_STATE(ucRegionIndex))
        {
            case _DISPLAY_STATE_ACTIVE:
                ucActiveRegionCount = ucActiveRegionCount + 1;

#if(_DM_COLORFORMAT_CHANGE_WO_RESET_SUPPORT == _ON)
                UserCommonColorDMFormatChgWoResetHandler(enumDisplayRegion);
#endif

#if(_COLOR_IP_DCC_HISTOGRAM == _ON)
                SysColorDCCHistogramHandler(enumDisplayRegion);
#endif

#if(_COLOR_IP_DCR == _ON)
                SysColorDCRHandler(enumDisplayRegion);
#endif

#if(_LOCAL_DIMMING_FUNCTION == _ON)
#if((_HW_CPU32_IS_BOOT_CPU == _TRUE) || (_CPU32_SCPU_FW_MODE == _SCPU_FW_MODE_ACTOR))
                UserCommonColorLocalDimmingGetKCPUStage();
#endif
#if(_FW_CPU32_IS_HIGH_SPEED_CPU == _TRUE)
                UserCommonColorLocalDimmingHandler();
#endif
#endif

#if(_COLORIMETRY_SEAMLESS_CHANGE_SUPPORT == _ON)
                UserCommonColorSeamlessChgHandler(enumDisplayRegion);
#endif
                break;

            default:
                break;
        }
    }

    if(ucActiveRegionCount == ucRegionCount)
    {
#if((_MOTION_BLUR_REDUCTION_LCD_SUPPORT == _ON) && (_DRR_MOTION_BLUR_REDUCTION_SUPPORT == _ON))
        UserCommonDisplayMbrDrrHandler();
#endif
    }

#if(_COLOR_IP_DCC_HISTOGRAM == _ON)
    CLR_DCC_READY_STATUS();
#endif

#if(_COLOR_IP_DCR == _ON)
    if(GET_DCR_READY_STATUS() == _TRUE)
    {
        // release DCR data
        ScalerColorDCRDataRefreshControl(_ENABLE);
    }
    CLR_DCR_READY_STATUS();
#endif
#if(_COLOR_IP_MRCM == _ON)
    UserCommonColorMRCMHandler();
#endif
}

#if(_COLOR_IP_DCC_HISTOGRAM == _ON)
//--------------------------------------------------
// Description  : Color DCC Histogram Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysColorDCCHistogramHandler(EnumDisplayRegion enumDisplayRegion)
{
    enumDisplayRegion = enumDisplayRegion;
    if(GET_DCC_READY_STATUS() == _TRUE)
    {
#if(_DCC_HISTOGRM_INFO_FUNCTION == _ON)
        UserInterfaceColorDCCHistogramHandler(enumDisplayRegion);
#endif

#if(_DM_FUNCTION == _ON)
#if(_IS_MAIN_PROCESS_CPU == _TRUE)
        UserCommonColorDMHandler(enumDisplayRegion);
#endif
#endif

#if(_ULTRA_HDR_SUPPORT == _ON)
        UserCommonColorHDRHandler(enumDisplayRegion);
#endif
    }
}
#endif

#if(_COLOR_IP_DCR == _ON)
//--------------------------------------------------
// Description  : Color DCR Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysColorDCRHandler(EnumDisplayRegion enumDisplayRegion)
{
    if(GET_DCR_READY_STATUS() == _TRUE)
    {
#if(_DCR_FUNCTION == _ON)
        UserInterfaceColorDCRHandler(enumDisplayRegion);
#endif

#if(_GLOBAL_DIMMING_FUNCTION == _ON)
        UserCommonColorGlobalDimmingHandler(enumDisplayRegion);
#endif

#if(_LOCAL_DIMMING_FUNCTION == _ON)
        UserCommonColorLocalDimmingDCRHandler(enumDisplayRegion);
#endif
    }
}
#endif

#if(_IS_MAIN_PROCESS_CPU == _FALSE)
//--------------------------------------------------
// Description  : Color Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysColorSecondaryHandler(void)
{
    BYTE ucRegionIndex = 0;
    BYTE ucRegionCount = GET_RGN_MAX_DISPLAY_REGION();

    for(ucRegionIndex = 0; ucRegionIndex < ucRegionCount; ++ucRegionIndex)
    {
        switch(GET_RGN_DISPLAY_STATE(ucRegionIndex))
        {
            case _DISPLAY_STATE_ACTIVE:
#if(_LOCAL_DIMMING_FUNCTION == _ON)
#if(_FW_CPU32_IS_HIGH_SPEED_CPU == _TRUE)
                UserCommonColorLocalDimmingHandler();
#endif
#endif
                break;

            default:
                break;
        }
    }

#if(_COLOR_IP_LOCAL_CONTRAST == _ON)
#if(_COLOR_IP_LOCAL_CONTRAST_HISTOGRAM == _ON)
#if((_LOCAL_CONTRAST_READYAVG_TOTAL_BLKNUM > _LOCAL_CONTRAST_READYAVG_KCPU_BLKNUM_LIMIT) && ((_SCPU_SUPPORT == _ON) && (_HW_CPU32_IS_BOOT_CPU != _TRUE)))
#if(_FW_CPU32_IS_HIGH_SPEED_CPU == _TRUE)
    if((GET_LOCAL_CONTRAST_READY_TOREAD() == _ENABLE) && (ScalerColorLocalContrastGetYavgSWmodeStatus() == _TRUE))
    {
        ScalerColorLocalContrastReadYavg();
        CLR_LOCAL_CONTRAST_READY_TOREAD();
    }
#endif
#endif
#endif
#endif
}
#endif
