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
// ID Code      : Debug.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __DEBUG_H__
#define __DEBUG_H__

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// DDC Channel Select
//--------------------------------------------------
#define _DEBUG_DDC_CHANNEL_SEL                      _PCB_DEBUG_DDC

//--------------------------------------------------
// JTAG Channel Select
//--------------------------------------------------
#define _DEBUG_JTAG_CHANNEL_SEL                     _PCB_DEBUG_JTAG

//--------------------------------------------------
// system bus debug
//--------------------------------------------------
#define _SYSTEM_BUS_ERROR_DEBUG_SUPPORT             _OFF

//--------------------------------------------------
// allow call debug message below HW4 INT Level
//--------------------------------------------------
#define _PROMOTE_DDC_INT_TO_HW4_INT_LVL             _OFF

//--------------------------------------------------
// RTD Tool IIC Debug by UserInterface Function
//--------------------------------------------------
#define _DEBUG_IIC_BY_USERINTERFACE                 _OFF

//--------------------------------------------------
// Enable Power Domain Function
//--------------------------------------------------
#define _DEBUG_POWER_DOMAIN_ENABLE                  _OFF

//--------------------------------------------------
// Assert macro
//--------------------------------------------------
#define _ASSERT_SUPPORT                             _OFF
#define _DEBUG_MESSAGE_ASSERT                       _OFF
#define _CPU_NOTIFY_INT_DEBUG_SUPPORT               _OFF

//--------------------------------------------------
// Compiler Option
//--------------------------------------------------
#define _UNITY_BUILD_SUPPORT                        _OFF

//--------------------------------------------------
// Debug Message Supported
//--------------------------------------------------
#define _DEBUG_MESSAGE_SYSTEM                       _OFF
#define _DEBUG_MESSAGE_SCALER                       _OFF
#define _DEBUG_MESSAGE_ANALOG                       _OFF
#define _DEBUG_MESSAGE_DIGITAL                      _OFF
#define _DEBUG_MESSAGE_RX0                          _OFF
#define _DEBUG_MESSAGE_RX1                          _OFF
#define _DEBUG_MESSAGE_RX2                          _OFF
#define _DEBUG_MESSAGE_RX3                          _OFF
#define _DEBUG_MESSAGE_RX4                          _OFF
#define _DEBUG_MESSAGE_RX5                          _OFF
#define _DEBUG_MESSAGE_MST                          _OFF
#define _DEBUG_MESSAGE_DPRX                         _OFF
#define _DEBUG_MESSAGE_DPTX                         _OFF
#define _DEBUG_MESSAGE_HDCP2                        _OFF
#define _DEBUG_MESSAGE_AUDIO                        _OFF
#define _DEBUG_MESSAGE_MEASURE                      _OFF
#define _DEBUG_MESSAGE_MEMORY                       _OFF
#define _DEBUG_MESSAGE_MEMORY_PHASE_CAL             _OFF
#define _DEBUG_MESSAGE_FRAME_SYNC                   _OFF
#define _DEBUG_MESSAGE_FRC                          _OFF
#define _DEBUG_MESSAGE_OSD                          _OFF
#define _DEBUG_MESSAGE_IR                           _OFF
#define _DEBUG_MESSAGE_HDR                          _OFF
#define _DEBUG_MESSAGE_CEC                          _OFF
#define _DEBUG_MESSAGE_CPU32                        _OFF
#define _DEBUG_MESSAGE_CHECK_DISP_SETTING           _OFF
#define _DEBUG_MESSAGE_QC                           _OFF
#define _DEBUG_MESSAGE_TYPE_C                       _OFF
#define _DEBUG_MESSAGE_DSC                          _OFF
#define _DEBUG_MESSAGE_U3_CTS                       _OFF
#define _DEBUG_MESSAGE_BILLBOARD                    _OFF
#define _DEBUG_MESSAGE_U2HOST_EHCI                  _OFF
#define _DEBUG_MESSAGE_U2HOST_OHCI                  _OFF
#define _DEBUG_MESSAGE_U2HOST                       _OFF
#define _DEBUG_MESSAGE_DATA_COMMUNICATION           _OFF
#define _DEBUG_MESSAGE_CHECK_MDOMAIN                _OFF
#define _DEBUG_MESSAGE_GOSD                         _OFF
#define _DEBUG_MESSAGE_SIGNATURE                    _OFF
#define _DEBUG_MESSAGE_DUALBANK                     _OFF
#define _DEBUG_MESSAGE_DM                           _OFF
#define _DEBUG_MESSAGE_ARC_TX                       _OFF

#ifndef _DEBUG_MESSAGE_AUTOTEST
#define _DEBUG_MESSAGE_AUTOTEST                     _OFF
#endif

#if(_DEBUG_MESSAGE_SYSTEM == _ON)
#define DebugMessageSystem(x, y)                    DEBUG_MESSAGE_FUNCTION((x), (y))
#else
#define DebugMessageSystem(x, y)                    ;
#endif

#if(_DEBUG_MESSAGE_SCALER == _ON)
#define DebugMessageScaler(x, y)                    DEBUG_MESSAGE_FUNCTION((x), (y))
#else
#define DebugMessageScaler(x, y)                    ;
#endif

#if(_DEBUG_MESSAGE_ANALOG == _ON)
#define DebugMessageAnalog(x, y)                    DEBUG_MESSAGE_FUNCTION((x), (y))
#else
#define DebugMessageAnalog(x, y)                    ;
#endif

#if(_DEBUG_MESSAGE_DIGITAL == _ON)
#define DebugMessageDigital(x, y)                   DEBUG_MESSAGE_FUNCTION((x), (y))
#else
#define DebugMessageDigital(x, y)                   ;
#endif

#if(_DEBUG_MESSAGE_RX0 == _ON)
#define DebugMessageRx0(x, y)                       DEBUG_MESSAGE_FUNCTION((x), (y))
#else
#define DebugMessageRx0(x, y)                       ;
#endif

#if(_DEBUG_MESSAGE_RX1 == _ON)
#define DebugMessageRx1(x, y)                       DEBUG_MESSAGE_FUNCTION((x), (y))
#else
#define DebugMessageRx1(x, y)                       ;
#endif

#if(_DEBUG_MESSAGE_RX2 == _ON)
#define DebugMessageRx2(x, y)                       DEBUG_MESSAGE_FUNCTION((x), (y))
#else
#define DebugMessageRx2(x, y)                       ;
#endif

#if(_DEBUG_MESSAGE_RX3 == _ON)
#define DebugMessageRx3(x, y)                       DEBUG_MESSAGE_FUNCTION((x), (y))
#else
#define DebugMessageRx3(x, y)                       ;
#endif

#if(_DEBUG_MESSAGE_RX4 == _ON)
#define DebugMessageRx4(x, y)                       DEBUG_MESSAGE_FUNCTION((x), (y))
#else
#define DebugMessageRx4(x, y)                       ;
#endif

#if(_DEBUG_MESSAGE_RX5 == _ON)
#define DebugMessageRx5(x, y)                       DEBUG_MESSAGE_FUNCTION((x), (y))
#else
#define DebugMessageRx5(x, y)                       ;
#endif

#if(_DEBUG_MESSAGE_MST == _ON)
#define DebugMessageMst(x, y)                       DEBUG_MESSAGE_FUNCTION((x), (y))
#else
#define DebugMessageMst(x, y)                       ;
#endif

#if(_DEBUG_MESSAGE_DPRX == _ON)
#define DebugMessageDpRx(x, y)                      DEBUG_MESSAGE_FUNCTION((x), (y))
#else
#define DebugMessageDpRx(x, y)                      ;
#endif

#if(_DEBUG_MESSAGE_DPTX == _ON)
#define DebugMessageDpTx(x, y)                      DEBUG_MESSAGE_FUNCTION((x), (y))
#else
#define DebugMessageDpTx(x, y)                      ;
#endif

#if(_DEBUG_MESSAGE_HDCP2 == _ON)
#define DebugMessageHDCP2(x, y)                     DEBUG_MESSAGE_FUNCTION((x), (y))
#else
#define DebugMessageHDCP2(x, y)                     ;
#endif

#if(_DEBUG_MESSAGE_AUDIO == _ON)
#define DebugMessageAudio(x, y)                     DEBUG_MESSAGE_FUNCTION((x), (y))
#else
#define DebugMessageAudio(x, y)                     ;
#endif

#if(_DEBUG_MESSAGE_MEASURE == _ON)
#define DebugMessageMeasure(x, y)                   DEBUG_MESSAGE_FUNCTION((x), (y))
#else
#define DebugMessageMeasure(x, y)                   ;
#endif

#if(_DEBUG_MESSAGE_MEMORY == _ON)
#define DebugMessageMemory(x, y)                    DEBUG_MESSAGE_FUNCTION((x), (y))
#else
#define DebugMessageMemory(x, y)                    ;
#endif

#if(_DEBUG_MESSAGE_MEMORY_PHASE_CAL == _ON)
#define DebugMessageMemoryPhaseCal(x, y)            DEBUG_MESSAGE_FUNCTION((x), (y))
#else
#define DebugMessageMemoryPhaseCal(x, y)            ;
#endif

#if(_DEBUG_MESSAGE_FRAME_SYNC == _ON)
#define DebugMessageFS(x, y)                        DEBUG_MESSAGE_FUNCTION((x), (y))
#else
#define DebugMessageFS(x, y)                        ;
#endif

#if(_DEBUG_MESSAGE_FRC == _ON)
#define DebugMessageFRC(x, y)                       DEBUG_MESSAGE_FUNCTION((x), (y))
#else
#define DebugMessageFRC(x, y)                       ;
#endif

#if(_DEBUG_MESSAGE_OSD == _ON)
#define DebugMessageOsd(x, y)                       DEBUG_MESSAGE_FUNCTION((x), (y))
#else
#define DebugMessageOsd(x, y)                       ;
#endif

#if(_DEBUG_MESSAGE_IR == _ON)
#define DebugMessageIR(x, y)                        DEBUG_MESSAGE_FUNCTION((x), (y))
#else
#define DebugMessageIR(x, y)                        ;
#endif

#if(_DEBUG_MESSAGE_HDR == _ON)
#define DebugMessageHDR(x, y)                       DEBUG_MESSAGE_FUNCTION((x), (y))
#else
#define DebugMessageHDR(x, y)                       ;
#endif

#if(_DEBUG_MESSAGE_CEC == _ON)
#define DebugMessageCEC(x, y)                       DEBUG_MESSAGE_FUNCTION((x), (y))
#else
#define DebugMessageCEC(x, y)                       ;
#endif

#if(_DEBUG_MESSAGE_CPU32 == _ON)
#define DebugMessageCpu32(x, y)                     DEBUG_MESSAGE_FUNCTION((x), (y))
#else
#define DebugMessageCpu32(x, y)                     ;
#endif

#if(_DEBUG_MESSAGE_QC == _ON)
#define DebugMessageQC(x, y)                        DEBUG_MESSAGE_FUNCTION((x), (y))
#else
#define DebugMessageQC(x, y)                        ;
#endif

#if(_DEBUG_MESSAGE_AUTOTEST == _ON)
#define DebugMessageAutoTest(x, y)                  DEBUG_MESSAGE_FUNCTION((x), (y))
#else
#define DebugMessageAutoTest(x, y)                  ;
#endif

#if(_DEBUG_MESSAGE_ASSERT == _ON)
#define DebugMessageAssert(x, y)                    DEBUG_MESSAGE_FUNCTION((x), (y))
#else
#define DebugMessageAssert(x, y)                    ;
#endif

#if(_DEBUG_MESSAGE_CHECK_DISP_SETTING == _ON)
#define DebugMessageCheck(x, y)                     DEBUG_MESSAGE_FUNCTION((x), (y))
#else
#define DebugMessageCheck(x, y)                     ;
#endif

#if(_DEBUG_MESSAGE_TYPE_C == _ON)
#define DebugMessageTypeC(x, y)                     DEBUG_MESSAGE_FUNCTION((x), (y))
#else
#define DebugMessageTypeC(x, y)                     ;
#endif

#if(_DEBUG_MESSAGE_DSC == _ON)
#define DebugMessageDSC(x, y)                       DEBUG_MESSAGE_FUNCTION((x), (y))
#else
#define DebugMessageDSC(x, y)                       ;
#endif

#if(_DEBUG_MESSAGE_U3_CTS == _ON)
#define DebugMessageU3Cts(x, y)                     DEBUG_MESSAGE_FUNCTION((x), (y))
#else
#define DebugMessageU3Cts(x, y)                     ;
#endif

#if(_DEBUG_MESSAGE_BILLBOARD == _ON)
#define DebugMessageBB(x, y)                        DEBUG_MESSAGE_FUNCTION((x), (y))
#else
#define DebugMessageBB(x, y)                        ;
#endif

#if(_DEBUG_MESSAGE_U2HOST_EHCI == _ON)
#define DebugMessageU2HostEHCI(x, y)                DEBUG_MESSAGE_FUNCTION((x), (y))
#else
#define DebugMessageU2HostEHCI(x, y)                ;
#endif

#if(_DEBUG_MESSAGE_U2HOST_OHCI == _ON)
#define DebugMessageU2HostOHCI(x, y)                DEBUG_MESSAGE_FUNCTION((x), (y))
#else
#define DebugMessageU2HostOHCI(x, y)                ;
#endif

#if(_DEBUG_MESSAGE_U2HOST == _ON)
#define DebugMessageU2Host(x, y)                    DEBUG_MESSAGE_FUNCTION((x), (y))
#else
#define DebugMessageU2Host(x, y)                    ;
#endif

#if(_DEBUG_MESSAGE_DATA_COMMUNICATION == _ON)
#define DebugMessageDataComminucation(x, y)         DEBUG_MESSAGE_FUNCTION((x), (y))
#else
#define DebugMessageDataComminucation(x, y)         ;
#endif

#if(_DEBUG_MESSAGE_CHECK_MDOMAIN == _ON)
#define DebugMessageCheckMDomain(x, y)              DEBUG_MESSAGE_FUNCTION((x), (y))
#else
#define DebugMessageCheckMDomain(x, y)              ;
#endif

#if(_DEBUG_MESSAGE_GOSD == _ON)
#define DebugMessageGOSD(x, y)                      DEBUG_MESSAGE_FUNCTION((x), (y))
#else
#define DebugMessageGOSD(x, y)                      ;
#endif

#if(_DEBUG_MESSAGE_SIGNATURE == _ON)
#define DebugMessageSignature(x, y)                 DEBUG_MESSAGE_FUNCTION((x), (y))
#else
#define DebugMessageSignature(x, y)                 ;
#endif

#if(_DEBUG_MESSAGE_DUALBANK == _ON)
#define DebugMessageDualBank(x, y)                  DEBUG_MESSAGE_FUNCTION((x), (y))
#else
#define DebugMessageDualBank(x, y)                  ;
#endif

#if(_DEBUG_MESSAGE_DM == _ON)
#define DebugMessageDM(x, y)                        DEBUG_MESSAGE_FUNCTION((x), (y))
#else
#define DebugMessageDM(x, y)                        ;
#endif

#if(_DEBUG_MESSAGE_ARC_TX == _ON)
#define DebugMessageArcTx(x, y)                     DEBUG_MESSAGE_FUNCTION((x), (y))
#else
#define DebugMessageArcTx(x, y)                     ;
#endif

#if((_DEBUG_MESSAGE_SYSTEM == _ON) ||\
    (_DEBUG_MESSAGE_SCALER == _ON) ||\
    (_DEBUG_MESSAGE_ANALOG == _ON) ||\
    (_DEBUG_MESSAGE_DIGITAL == _ON) ||\
    (_DEBUG_MESSAGE_RX0 == _ON) ||\
    (_DEBUG_MESSAGE_RX1 == _ON) ||\
    (_DEBUG_MESSAGE_RX2 == _ON) ||\
    (_DEBUG_MESSAGE_RX3 == _ON) ||\
    (_DEBUG_MESSAGE_RX4 == _ON) ||\
    (_DEBUG_MESSAGE_RX5 == _ON) ||\
    (_DEBUG_MESSAGE_MST == _ON) ||\
    (_DEBUG_MESSAGE_DPRX == _ON) ||\
    (_DEBUG_MESSAGE_DPTX == _ON) ||\
    (_DEBUG_MESSAGE_HDCP2 == _ON) ||\
    (_DEBUG_MESSAGE_AUDIO == _ON) ||\
    (_DEBUG_MESSAGE_MEASURE == _ON) ||\
    (_DEBUG_MESSAGE_MEMORY == _ON) ||\
    (_DEBUG_MESSAGE_MEMORY_PHASE_CAL == _ON) ||\
    (_DEBUG_MESSAGE_FRAME_SYNC == _ON) ||\
    (_DEBUG_MESSAGE_FRC == _ON) ||\
    (_DEBUG_MESSAGE_OSD == _ON) ||\
    (_DEBUG_MESSAGE_IR == _ON) ||\
    (_DEBUG_MESSAGE_HDR == _ON) ||\
    (_DEBUG_MESSAGE_CEC == _ON) ||\
    (_DEBUG_MESSAGE_CPU32 == _ON) ||\
    (_DEBUG_MESSAGE_QC == _ON) ||\
    (_DEBUG_MESSAGE_AUTOTEST == _ON) ||\
    (_DEBUG_MESSAGE_ASSERT == _ON) ||\
    (_DEBUG_MESSAGE_CHECK_DISP_SETTING == _ON) ||\
    (_DEBUG_MESSAGE_TYPE_C == _ON) ||\
    (_DEBUG_MESSAGE_DSC == _ON) ||\
    (_DEBUG_MESSAGE_U3_CTS == _ON) ||\
    (_DEBUG_MESSAGE_U2HOST == _ON) ||\
    (_DEBUG_MESSAGE_U2HOST_EHCI == _ON) ||\
    (_DEBUG_MESSAGE_U2HOST_OHCI == _ON) ||\
    (_DEBUG_MESSAGE_BILLBOARD == _ON) ||\
    (_DEBUG_MESSAGE_DATA_COMMUNICATION == _ON) ||\
    (_DEBUG_MESSAGE_CHECK_MDOMAIN == _ON) ||\
    (_DEBUG_MESSAGE_GOSD == _ON) ||\
    (_DEBUG_MESSAGE_SIGNATURE == _ON) ||\
    (_DEBUG_MESSAGE_DUALBANK == _ON) ||\
    (_DEBUG_MESSAGE_DM == _ON) ||\
    (_DEBUG_MESSAGE_ARC_TX == _ON))

#define _DEBUG_MESSAGE_SUPPORT                      _ON
#else
#define _DEBUG_MESSAGE_SUPPORT                      _OFF
#endif

#if(_DEBUG_MESSAGE_SUPPORT == _ON)
#define DebugMessageCritical(x, y)                  DEBUG_MESSAGE_FUNCTION((x), (y))
#else
#define DebugMessageCritical(x, y)                  ;
#endif

#if(_DEBUG_MESSAGE_SUPPORT == _ON)
#define _TIME_CURSOR_SUPPORT                        _ON
#else
#define _TIME_CURSOR_SUPPORT                        _OFF
#endif

//--------------------------------------------------
// Debug clipping Support
//--------------------------------------------------
#define __CLIPPING__                                __attribute__((used)) static void RTK_DEBUG_CLIP(void) {}

//--------------------------------------------------
// Debug time cursor Support
//--------------------------------------------------
#if(_TIME_CURSOR_SUPPORT == _ON)
#define DEBUG_TIMER_SAMPLE_START_MS(EnumDebugTimeCursor)\
                                                    {\
                                                        g_ucDebugTimerCursorUsedMS &= ~(1U << ((EnumDebugTimeCursor) % _DEBUG_TIME_CURSOR_END));\
                                                        g_pstDebugTimerCursorMS[(EnumDebugTimeCursor) % _DEBUG_TIME_CURSOR_END].usCounter_StartMS = g_usTimerMeasureCounter;\
                                                    }

#define DEBUG_TIMER_SAMPLE_END_MS(EnumDebugTimeCursor)\
                                                    {\
                                                        g_pstDebugTimerCursorMS[(EnumDebugTimeCursor) % _DEBUG_TIME_CURSOR_END].usCounter_EndMS = g_usTimerMeasureCounter;\
                                                        g_ucDebugTimerCursorUsedMS |= (1U << ((EnumDebugTimeCursor) % _DEBUG_TIME_CURSOR_END));\
                                                    }

#define DEBUG_TIMER_SAMPLE_START_US(EnumDebugTimeCursor)\
                                                    {\
                                                        g_ucDebugTimerCursorUsedUS &= ~(1U << ((EnumDebugTimeCursor) % _DEBUG_TIME_CURSOR_END));\
                                                        g_ucDebugTimerCursorUsedMS &= ~(1U << ((EnumDebugTimeCursor) % _DEBUG_TIME_CURSOR_END));\
                                                        g_pstDebugTimerCursorMS[(EnumDebugTimeCursor) % _DEBUG_TIME_CURSOR_END].usCounter_StartMS = g_usTimerMeasureCounter;\
                                                        g_pstDebugTimerCursorUS[(EnumDebugTimeCursor) % _DEBUG_TIME_CURSOR_END].ulCounter_StartUS = ScalerTimerGetCurrentValue(_CPU_TIMER_3);\
                                                    }

#define DEBUG_TIMER_SAMPLE_END_US(EnumDebugTimeCursor)\
                                                    {\
                                                        g_pstDebugTimerCursorMS[(EnumDebugTimeCursor) % _DEBUG_TIME_CURSOR_END].usCounter_EndMS = g_usTimerMeasureCounter;\
                                                        g_pstDebugTimerCursorUS[(EnumDebugTimeCursor) % _DEBUG_TIME_CURSOR_END].ulCounter_EndUS = ScalerTimerGetCurrentValue(_CPU_TIMER_3);\
                                                        g_ucDebugTimerCursorUsedUS |= (1U << ((EnumDebugTimeCursor) % _DEBUG_TIME_CURSOR_END));\
                                                        g_ucDebugTimerCursorUsedMS |= (1U << ((EnumDebugTimeCursor) % _DEBUG_TIME_CURSOR_END));\
                                                    }

#else

#define DEBUG_TIMER_SAMPLE_START_MS(EnumDebugTimeCursor)\
                                                    {\
                                                    }
#define DEBUG_TIMER_SAMPLE_END_MS(EnumDebugTimeCursor)\
                                                    {\
                                                    }
#define DEBUG_TIMER_SAMPLE_START_US(EnumDebugTimeCursor)\
                                                    {\
                                                    }
#define DEBUG_TIMER_SAMPLE_END_US(EnumDebugTimeCursor)\
                                                    {\
                                                    }

#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
#ifndef __ASSEMBLER__

typedef enum
{
    _DBG_OFF = _OFF,
    _DBG_ON = _ON,
} EnumDebugMode;

typedef enum
{
    _DEBUG_TIME_CURSOR_1 = 0,
    _DEBUG_TIME_CURSOR_2 = 1,
    _DEBUG_TIME_CURSOR_3 = 2,
    _DEBUG_TIME_CURSOR_4 = 3,
    _DEBUG_TIME_CURSOR_5 = 4,
    _DEBUG_TIME_CURSOR_END,
} EnumDebugTimeCursor;

typedef struct
{
    WORD usCounter_StartMS;
    WORD usCounter_EndMS;
} StructTimerSampleMS;

typedef struct
{
    DWORD ulCounter_StartUS;
    DWORD ulCounter_EndUS;
} StructTimerSampleUS;

#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#ifndef __ASSEMBLER__
//--------------------------------------------------
// Debug IIC UserInterface Extern
//--------------------------------------------------
#if(_DEBUG_IIC_BY_USERINTERFACE == _ON)
extern EnumDebugMode UserInterfaceDebugIIC(BYTE ucType, BYTE *pucDdcciArray, BYTE *pucReturnValue);
#endif

#endif

#endif // End of #ifndef __DEBUG_H__
