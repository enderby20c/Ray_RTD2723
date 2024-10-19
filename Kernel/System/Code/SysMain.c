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
// ID Code      : SysMain.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __MAIN__

#include "SysInclude.h"
#include "Main/SysMain.h"

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
// Description  : The main function
// Input Value  : None
// Output Value : None
//--------------------------------------------------
SWORD main(void)
{
#if(_IS_MAIN_PROCESS_CPU == _TRUE)

    do
    {
        SysMainSystemInitial();

        while(SysMainSytemPowerDetect() == _TRUE)
        {
            SysMainProcess();
        }
    }
    while(_TRUE);

#else

    SysMainSecondarySystemInitial();

    do
    {
#if(_CPU32_SCPU_FW_MODE == _SCPU_FW_MODE_ACTOR)
        SysMainProcess();
#endif

        SysMainSecondaryProcess();
    }
    while(_TRUE);

#endif

    return 0;
}

#if((_IS_MAIN_PROCESS_CPU == _TRUE) || (_CPU32_SCPU_FW_MODE == _SCPU_FW_MODE_ACTOR))
//--------------------------------------------------
// Description  : main process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysMainProcess(void)
{
    UserCommonKeyHandler();

#if(_HW_CPU32_IS_BOOT_CPU == _TRUE)
    SysPowerHandler();
#endif

    SysJudgeHandler();

#if(_AUDIO_SUPPORT == _ON)
    SysAudioHandler();
#endif
    SysTimerHandler();
    SysSourceHandler();
    SysModeHandler();

#if(_USB_SUPPORT == _ON)
    SysUsbHandler();
#endif

#if(_DP_SUPPORT == _ON)
    SysDpRxHandler();
#endif

#if(_HDMI_SUPPORT == _ON)
    SysTmdsRxHandler();
#endif

#if(_HDMI_CEC_SUPPORT == _ON)
    SysCecHandler();
#endif

#if(_DP_TX_SUPPORT == _ON)
    SysDpTxHandler();
#endif

#if(_DP_MST_SUPPORT == _ON)
    SysDpMstHandler();
#endif

#if(_HDCP_2_2_SUPPORT == _ON)
    ScalerHdcp2Handler();
#endif

#if(_HW_CPU32_IS_BOOT_CPU == _TRUE)
#if((_SCPU_SUPPORT == _ON) && (_HW_CPU32_NOTIFY_INT_SUPPORT == _ON))
    ScalerCpuCtrlHandler();
#endif
#endif

    SysColorHandler();

#if(_AUTO_TEST_SUPPORT == _ON)
    SysATHandler();
#endif

    UserCommonOsdHandler();

#if(_DDCCI_CODE_REDUCTION == _OFF)
    UserCommonDdcciHandler();
#endif

    SysDebugHandler();

#if(_DUAL_BANK_DEBUG_SUPPORT == _ON)
    UserCommonDualBankUserHandler();
#endif
}
#endif

#if(_IS_MAIN_PROCESS_CPU == _TRUE)
//--------------------------------------------------
// Description  : System AC on initial flow
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysMainSystemInitial(void)
{
    ScalerMcuInitial();

    ScalerPinshareInitial();
#if((_DUAL_BANK_FLASH_PARTITION_SUPPORT == _ON) &&\
    ((_DUAL_BANK_FLASH_PARTITION_BOOT_USER_SEL == _DUAL_BANK_FLASH_PARTITION_BOOT) ||\
    (_DUAL_BANK_FLASH_PARTITION_BOOT_USER_SEL == _DUAL_BANK_FLASH_PARTITION_BOTH)))
#if(_DUAL_BANK_FLASH_PARTITION_BOOT_USER_SEL == _DUAL_BANK_FLASH_PARTITION_BOTH)
    if(ScalerDualBankUserGetKCPUBankOffset() == 0x00)
#endif
    {
        UserCommonDualBankProcess();
    }
#endif

    ScalerTimerInitialTimerEvent();

    UserCommonPowerAcOnInitial();

    ScalerMcuDdcRamEnable();

    SysRegionInitial();

    SysSourceInitial();

    SysPowerInitial();

#if(_IR_SUPPORT == _IR_HW_SUPPORT)
    ScalerIRHWModeInitial();
#endif

    SET_POWER_STATUS(_POWER_STATUS_AC_ON);

    if(UserCommonNVRamGetSystemData(_MONITOR_POWER_STATUS) == _ON)
    {
        SET_TARGET_POWER_STATUS(_POWER_STATUS_NORMAL);
    }
    else
    {
        SET_TARGET_POWER_STATUS(_POWER_STATUS_OFF);
    }

    SET_MODE_STATE(_MODE_STATUS_POWER_OFF);
}
#endif

#if(_IS_MAIN_PROCESS_CPU == _FALSE)
//--------------------------------------------------
// Description  : secondary main process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysMainSecondaryProcess(void)
{
#if(_SCPU_SUPPORT == _ON)
#if((_AUDIO_PARALLEL_MODE_SUPPORT == _ON) && (_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EXTERNAL_DEVICE))
    ScalerCpuSyncDelayForHbrAudioSetting();
#endif
#endif

    SysColorSecondaryHandler();

#if((_HW_CPU32_NOTIFY_INT_SUPPORT == _ON) && (_SCPU_SUPPORT == _ON))
    ScalerScpuSyncHandler();
#endif

#if(_GOSD_SUPPORT == _ON)
    UserCommonGosdHandler();
#endif

#if(_DM_FUNCTION == _ON)
    UserCommonColorDMMuteHandler();
    UserCommonColorDMBECHandler();
#endif
}

//--------------------------------------------------
// Description  : System AC on initial flow
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysMainSecondarySystemInitial(void)
{
#if(_GOSD_SUPPORT == _ON)
    ScalerGosdPowerOnInitial();
#endif

#if(_DM_FUNCTION == _ON)
    ScalerDMSCPUInit();
#endif
}
#endif

//--------------------------------------------------
// Description  : System power detect
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit SysMainSytemPowerDetect(void)
{
    return PCB_POWER_5V_DETECT();
}
