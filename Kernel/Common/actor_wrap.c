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
// ID Code      : actor_wrap.c No.0000
// Update Note  :
//--------------------------------------------------------------------------------

#include "SysInclude.h"

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if((_SCPU_SUPPORT == _ON) && (_CPU32_SCPU_FW_MODE == _SCPU_FW_MODE_ACTOR))

#if(_HW_CPU32_IS_BOOT_CPU == _TRUE)
#define _WRAPPER_FUNCTION(wrapper_idx, fn)\
    extern void __real_ ## fn(void);\
    void __wrap_ ## fn(void)\
    {\
        if(ScalerCpuCtrlCheckScpuActive() == _TRUE)\
        {\
            g_pulInterLock[(wrapper_idx)] = 1;\
            polling_inter_lock(wrapper_idx);\
            g_pulInterLock[(wrapper_idx)] = 0;\
        }\
        else\
        {\
            __real_ ## fn();\
        }\
    }
#endif

#if(_HW_CPU32_IS_BOOT_CPU == _FALSE)
#define _WRAPPER_FUNCTION(wrapper_idx, fn)\
    extern void __real_ ## fn(void);\
    void __wrap_ ## fn(void)\
    {\
        if(g_pulInterLock[(wrapper_idx)] == 1)\
        {\
            __real_ ## fn();\
            g_pulInterLock[(wrapper_idx)] = 0;\
        }\
    }
#endif

#endif // End of #if((_SCPU_SUPPORT == _ON) && (_CPU32_SCPU_FW_MODE == _SCPU_FW_MODE_ACTOR))

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
#if((_SCPU_SUPPORT == _ON) && (_CPU32_SCPU_FW_MODE == _SCPU_FW_MODE_ACTOR))
typedef enum
{
    _WRAPER_FLAG_KEY_HANDLER,
    _WRAPER_FLAG_JUDGE_HANDLER,

#if(_AUDIO_SUPPORT == _ON)
    _WRAPER_FLAG_AUDIO_HANDLER,
#endif

    _WRAPER_FLAG_TIMER_HANDLER,
    _WRAPER_FLAG_SOURCE_HANDLER,
    _WRAPER_FLAG_MODE_HANDLER,

#if(_USB_SUPPORT == _ON)
    _WRAPER_FLAG_USB_HANDLER,
#endif

#if(_DP_SUPPORT == _ON)
    _WRAPER_FLAG_DP_RX_HANDLER,
#endif

#if(_HDMI_SUPPORT == _ON)
    _WRAPER_FLAG_TMDS_RX_HANDLER,
#endif

#if(_HDMI_CEC_SUPPORT == _ON)
    _WRAPER_FLAG_CEC_HANDLER,
#endif

#if(_DP_TX_SUPPORT == _ON)
    _WRAPER_FLAG_DP_TX_HANDLER,
#endif

#if(_DP_MST_SUPPORT == _ON)
    _WRAPER_FLAG_DPMST_HANDLER,
#endif

#if(_HDCP_2_2_SUPPORT == _ON)
    _WRAPER_FLAG_HDCP2_HANDLER,
#endif

    _WRAPER_FLAG_COLOR_HANDLER,

#if(_AUTO_TEST_SUPPORT == _ON)
    _WRAPER_FLAG_AT_HANDLER,
#endif

    _WRAPER_FLAG_OSD_HANDLER,

#if(_DDCCI_CODE_REDUCTION == _OFF)
    _WRAPER_FLAG_DDCCI_HANDLER,
#endif

    _WRAPER_FLAG_DEBUG_HANDLER,

#if(_DUAL_BANK_DEBUG_SUPPORT == _ON)
    _WRAPER_FLAG_DUAL_BANK_USER_HANDLER,
#endif

    _WRAPER_FLAG_MAX,
} EnumWrapperFlag;
#endif


//****************************************************************************
// CODE TABLES
//****************************************************************************

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
#if((_SCPU_SUPPORT == _ON) && (_CPU32_SCPU_FW_MODE == _SCPU_FW_MODE_ACTOR))
volatile DWORD g_pulInterLock[_WRAPER_FLAG_MAX];
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if((_SCPU_SUPPORT == _ON) && (_CPU32_SCPU_FW_MODE == _SCPU_FW_MODE_ACTOR))
//--------------------------------------------------
// Description  : main process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void polling_inter_lock(EnumWrapperFlag enumFlag)
{
    WORD us1msTickCnt = g_usTimerCounter;

    while(g_pulInterLock[enumFlag] != 0)
    {
        if(us1msTickCnt != g_usTimerCounter)
        {
            ScalerWdtClearWDT();
            us1msTickCnt = g_usTimerCounter;
        }

#if(_HW_CPU32_IS_BOOT_CPU == _TRUE)
#if((_SCPU_SUPPORT == _ON) && (_HW_CPU32_NOTIFY_INT_SUPPORT == _ON))
        ScalerCpuCtrlHandler();
#endif
#endif

        ScalerMcuDelayXus(10);
    }
}


_WRAPPER_FUNCTION(_WRAPER_FLAG_KEY_HANDLER, UserCommonKeyHandler)
_WRAPPER_FUNCTION(_WRAPER_FLAG_JUDGE_HANDLER, SysJudgeHandler)

#if(_AUDIO_SUPPORT == _ON)
_WRAPPER_FUNCTION(_WRAPER_FLAG_AUDIO_HANDLER, SysAudioHandler)
#endif

_WRAPPER_FUNCTION(_WRAPER_FLAG_TIMER_HANDLER, SysTimerHandler)
_WRAPPER_FUNCTION(_WRAPER_FLAG_SOURCE_HANDLER, SysSourceHandler)

_WRAPPER_FUNCTION(_WRAPER_FLAG_MODE_HANDLER, SysModeHandler)

#if(_USB_SUPPORT == _ON)
_WRAPPER_FUNCTION(_WRAPER_FLAG_USB_HANDLER, SysUsbHandler)
#endif

#if(_DP_SUPPORT == _ON)
_WRAPPER_FUNCTION(_WRAPER_FLAG_DP_RX_HANDLER, SysDpRxHandler)
#endif

#if(_HDMI_SUPPORT == _ON)
_WRAPPER_FUNCTION(_WRAPER_FLAG_TMDS_RX_HANDLER, SysTmdsRxHandler)
#endif

#if(_HDMI_CEC_SUPPORT == _ON)
_WRAPPER_FUNCTION(_WRAPER_FLAG_CEC_HANDLER, SysCecHandler)
#endif

#if(_DP_TX_SUPPORT == _ON)
_WRAPPER_FUNCTION(_WRAPER_FLAG_DP_TX_HANDLER, SysDpTxHandler)
#endif

#if(_DP_MST_SUPPORT == _ON)
_WRAPPER_FUNCTION(_WRAPER_FLAG_DPMST_HANDLER, SysDpMstHandler)
#endif

#if(_HDCP_2_2_SUPPORT == _ON)
_WRAPPER_FUNCTION(_WRAPER_FLAG_HDCP2_HANDLER, ScalerHdcp2Handler)
#endif

_WRAPPER_FUNCTION(_WRAPER_FLAG_COLOR_HANDLER, SysColorHandler)

#if(_AUTO_TEST_SUPPORT == _ON)
_WRAPPER_FUNCTION(_WRAPER_FLAG_AT_HANDLER, SysATHandler)
#endif

_WRAPPER_FUNCTION(_WRAPER_FLAG_OSD_HANDLER, UserCommonOsdHandler)

#if(_DDCCI_CODE_REDUCTION == _OFF)
_WRAPPER_FUNCTION(_WRAPER_FLAG_DDCCI_HANDLER, UserCommonDdcciHandler)
#endif

_WRAPPER_FUNCTION(_WRAPER_FLAG_DEBUG_HANDLER, SysDebugHandler)

#if(_DUAL_BANK_DEBUG_SUPPORT == _ON)
_WRAPPER_FUNCTION(_WRAPER_FLAG_DUAL_BANK_USER_HANDLER, UserCommonDualBankUserHandler)
#endif

#endif

