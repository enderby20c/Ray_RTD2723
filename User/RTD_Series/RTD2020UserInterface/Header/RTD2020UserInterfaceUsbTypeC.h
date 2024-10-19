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
// ID Code      : RTD2020UserInterfaceUsbTypeC.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_OSD_TYPE == _REALTEK_2020_OSD)

#if(_TYPE_C_PORT_CTRL_SUPPORT == _ON)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// MACRO for Type-C Port Controller
//--------------------------------------------------
#if((_PORT_CTRL_RTS_SUPPORT == _ON) || (_PORT_CTRL_RTD_SUPPORT == _ON) || (_PORT_CTRL_USER_SERIES_SUPPORT == _ON))
#define GET_D0_TYPE_C_POWER_OFF_FLG()               (g_stUsbTypeCPowerOffInfo.b1D0TypeCPowerOffFlag)
#define SET_D0_TYPE_C_POWER_OFF_FLG()               (g_stUsbTypeCPowerOffInfo.b1D0TypeCPowerOffFlag = _TRUE)
#define CLR_D0_TYPE_C_POWER_OFF_FLG()               (g_stUsbTypeCPowerOffInfo.b1D0TypeCPowerOffFlag = _FALSE)

#define GET_D1_TYPE_C_POWER_OFF_FLG()               (g_stUsbTypeCPowerOffInfo.b1D1TypeCPowerOffFlag)
#define SET_D1_TYPE_C_POWER_OFF_FLG()               (g_stUsbTypeCPowerOffInfo.b1D1TypeCPowerOffFlag = _TRUE)
#define CLR_D1_TYPE_C_POWER_OFF_FLG()               (g_stUsbTypeCPowerOffInfo.b1D1TypeCPowerOffFlag = _FALSE)

#define GET_D2_TYPE_C_POWER_OFF_FLG()               (g_stUsbTypeCPowerOffInfo.b1D2TypeCPowerOffFlag)
#define SET_D2_TYPE_C_POWER_OFF_FLG()               (g_stUsbTypeCPowerOffInfo.b1D2TypeCPowerOffFlag = _TRUE)
#define CLR_D2_TYPE_C_POWER_OFF_FLG()               (g_stUsbTypeCPowerOffInfo.b1D2TypeCPowerOffFlag = _FALSE)

#define GET_P0_TYPE_C_POWER_OFF_FLG()               (g_stUsbTypeCPowerOffInfo.b1P0TypeCPowerOffFlag)
#define SET_P0_TYPE_C_POWER_OFF_FLG()               (g_stUsbTypeCPowerOffInfo.b1P0TypeCPowerOffFlag = _TRUE)
#define CLR_P0_TYPE_C_POWER_OFF_FLG()               (g_stUsbTypeCPowerOffInfo.b1P0TypeCPowerOffFlag = _FALSE)

#define GET_P1_TYPE_C_POWER_OFF_FLG()               (g_stUsbTypeCPowerOffInfo.b1P1TypeCPowerOffFlag)
#define SET_P1_TYPE_C_POWER_OFF_FLG()               (g_stUsbTypeCPowerOffInfo.b1P1TypeCPowerOffFlag = _TRUE)
#define CLR_P1_TYPE_C_POWER_OFF_FLG()               (g_stUsbTypeCPowerOffInfo.b1P1TypeCPowerOffFlag = _FALSE)

#define GET_P2_TYPE_C_POWER_OFF_FLG()               (g_stUsbTypeCPowerOffInfo.b1P2TypeCPowerOffFlag)
#define SET_P2_TYPE_C_POWER_OFF_FLG()               (g_stUsbTypeCPowerOffInfo.b1P2TypeCPowerOffFlag = _TRUE)
#define CLR_P2_TYPE_C_POWER_OFF_FLG()               (g_stUsbTypeCPowerOffInfo.b1P2TypeCPowerOffFlag = _FALSE)

#define GET_P3_TYPE_C_POWER_OFF_FLG()               (g_stUsbTypeCPowerOffInfo.b1P3TypeCPowerOffFlag)
#define SET_P3_TYPE_C_POWER_OFF_FLG()               (g_stUsbTypeCPowerOffInfo.b1P3TypeCPowerOffFlag = _TRUE)
#define CLR_P3_TYPE_C_POWER_OFF_FLG()               (g_stUsbTypeCPowerOffInfo.b1P3TypeCPowerOffFlag = _FALSE)

#define GET_P4_TYPE_C_POWER_OFF_FLG()               (g_stUsbTypeCPowerOffInfo.b1P4TypeCPowerOffFlag)
#define SET_P4_TYPE_C_POWER_OFF_FLG()               (g_stUsbTypeCPowerOffInfo.b1P4TypeCPowerOffFlag = _TRUE)
#define CLR_P4_TYPE_C_POWER_OFF_FLG()               (g_stUsbTypeCPowerOffInfo.b1P4TypeCPowerOffFlag = _FALSE)
#endif

#if(_TYPE_C_MODAL_OPERATION_SUPPORT == _ON)
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE)
//--------------------------------------------------
// Macro for Lenovo Alt Mode Docking Event Queue Control
//--------------------------------------------------
#define GET_D0_TYPE_C_DOCK_EVENT_QUEUE(x)           (g_stUsbTypeCLenovoDockEventQueue.pstDockEvent[x])
#define SET_D0_TYPE_C_DOCK_EVENT_QUEUE(x)           (g_stUsbTypeCLenovoDockEventQueue.pstDockEvent[g_stUsbTypeCLenovoDockEventQueue.b2DockEventTail] = (x))
#define CLR_D0_TYPE_C_DOCK_EVENT_QUEUE()            (memset(&g_stUsbTypeCLenovoDockEventQueue.pstDockEvent[g_stUsbTypeCLenovoDockEventQueue.b2DockEventHead], 0, sizeof(StructTypeCLenovoDockEvent)))

#define GET_D0_TYPE_C_DOCK_EVENT_CNT()              (g_stUsbTypeCLenovoDockEventQueue.b2DockEventCnt)
#define ADD_D0_TYPE_C_DOCK_EVENT_CNT()              (g_stUsbTypeCLenovoDockEventQueue.b2DockEventCnt += 1)
#define SUB_D0_TYPE_C_DOCK_EVENT_CNT()              (g_stUsbTypeCLenovoDockEventQueue.b2DockEventCnt -= 1)
#define CLR_D0_TYPE_C_DOCK_EVENT_CNT()              (g_stUsbTypeCLenovoDockEventQueue.b2DockEventCnt = 0)

#define GET_D0_TYPE_C_DOCK_EVENT_HEAD()             (g_stUsbTypeCLenovoDockEventQueue.b2DockEventHead)
#define ADD_D0_TYPE_C_DOCK_EVENT_HEAD()             (g_stUsbTypeCLenovoDockEventQueue.b2DockEventHead = (g_stUsbTypeCLenovoDockEventQueue.b2DockEventHead + 1) % 3)
#define CLR_D0_TYPE_C_DOCK_EVENT_HEAD()             (g_stUsbTypeCLenovoDockEventQueue.b2DockEventHead = 0)

#define GET_D0_TYPE_C_DOCK_EVENT_TAIL()             (g_stUsbTypeCLenovoDockEventQueue.b2DockEventTail)
#define ADD_D0_TYPE_C_DOCK_EVENT_TAIL()             (g_stUsbTypeCLenovoDockEventQueue.b2DockEventTail = (g_stUsbTypeCLenovoDockEventQueue.b2DockEventTail + 1) % 3)
#define CLR_D0_TYPE_C_DOCK_EVENT_TAIL()             (g_stUsbTypeCLenovoDockEventQueue.b2DockEventTail = 0)
#endif

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_ACER_ALT_MODE)
#define GET_D0_TYPE_C_ACER_USER_EVENT()             (g_stUsbTypeCAcerUserEvent.enumEvent)
#define SET_D0_TYPE_C_ACER_USER_EVENT(x)            (g_stUsbTypeCAcerUserEvent.enumEvent = (g_stUsbTypeCAcerUserEvent.enumEvent | (x)))
#define CLR_D0_TYPE_C_ACER_USER_EVENT(x)            (g_stUsbTypeCAcerUserEvent.enumEvent = (g_stUsbTypeCAcerUserEvent.enumEvent & (EnumTypeCAcerUserEvent)(~(x))))

#define GET_D0_TYPE_C_ACER_USER_VDM_CNT()           (g_stUsbTypeCAcerUserEvent.b3VdmCnt)
#define SET_D0_TYPE_C_ACER_USER_VDM_CNT(x)          (g_stUsbTypeCAcerUserEvent.b3VdmCnt = (x))

#define GET_D0_TYPE_C_ACER_USER_VDM_DATA(x)         (g_stUsbTypeCAcerUserEvent.pucVdmData[x])
#define SET_D0_TYPE_C_ACER_USER_VDM_DATA(x, y)      (g_stUsbTypeCAcerUserEvent.pucVdmData[x] = (y))
#endif

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)
#define GET_D0_TYPE_C_HP_USER_EVENT()               (g_stUsbTypeCHpUserEvent.enumEvent)
#define SET_D0_TYPE_C_HP_USER_EVENT(x)              (g_stUsbTypeCHpUserEvent.enumEvent = (g_stUsbTypeCHpUserEvent.enumEvent | (x)))
#define CLR_D0_TYPE_C_HP_USER_EVENT(x)              (g_stUsbTypeCHpUserEvent.enumEvent = (g_stUsbTypeCHpUserEvent.enumEvent & (EnumTypeCHpUserEvent)(~(x))))

#define GET_D0_TYPE_C_HP_USER_VDM_CNT()             (g_stUsbTypeCHpUserEvent.b3VdmCnt)
#define SET_D0_TYPE_C_HP_USER_VDM_CNT(x)            (g_stUsbTypeCHpUserEvent.b3VdmCnt = (x))

#define GET_D0_TYPE_C_HP_USER_VDM_DATA(x)           (g_stUsbTypeCHpUserEvent.pucVdmData[x])
#define SET_D0_TYPE_C_HP_USER_VDM_DATA(x, y)        (g_stUsbTypeCHpUserEvent.pucVdmData[x] = (y))
#endif

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)
#define GET_D0_TYPE_C_DELL_USER_EVENT()             (g_stUsbTypeCDellUserEvent.enumEvent)
#define SET_D0_TYPE_C_DELL_USER_EVENT(x)            (g_stUsbTypeCDellUserEvent.enumEvent = (g_stUsbTypeCDellUserEvent.enumEvent | (x)))
#define CLR_D0_TYPE_C_DELL_USER_EVENT(x)            (g_stUsbTypeCDellUserEvent.enumEvent = (g_stUsbTypeCDellUserEvent.enumEvent & (EnumTypeCDellUserEvent)(~(x))))

#define GET_D0_TYPE_C_DELL_USER_VDM_CNT()           (g_stUsbTypeCDellUserEvent.b3VdmCnt)
#define SET_D0_TYPE_C_DELL_USER_VDM_CNT(x)          (g_stUsbTypeCDellUserEvent.b3VdmCnt = (x))

#define GET_D0_TYPE_C_DELL_USER_VDM_DATA(x)         (g_stUsbTypeCDellUserEvent.pucVdmData[x])
#define SET_D0_TYPE_C_DELL_USER_VDM_DATA(x, y)      (g_stUsbTypeCDellUserEvent.pucVdmData[x] = (y))
#endif
#endif  // End of #if(_TYPE_C_MODAL_OPERATION_SUPPORT == _ON)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef struct
{
    BYTE b1D0TypeCPowerOffFlag : 1;
    BYTE b1D1TypeCPowerOffFlag : 1;
    BYTE b1D2TypeCPowerOffFlag : 1;
    BYTE b1P0TypeCPowerOffFlag : 1;
    BYTE b1P1TypeCPowerOffFlag : 1;
    BYTE b1P2TypeCPowerOffFlag : 1;
    BYTE b1P3TypeCPowerOffFlag : 1;
    BYTE b1P4TypeCPowerOffFlag : 1;
} StructUsbTypeCPowerOffInfo;

//--------------------------------------------------
// Struct for Lenovo Alt Mode Docking Event Queue
//--------------------------------------------------
typedef struct
{
    BYTE b2DockEventCnt : 2;
    BYTE b2DockEventHead : 2;
    BYTE b2DockEventTail : 2;
    StructTypeCLenovoDockEvent pstDockEvent[3];
}StructUsbTypeCLenovoDockEventQueue;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************


#endif // End of #if(_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#endif // End of #if(_OSD_TYPE == _REALTEK_2020_OSD)
