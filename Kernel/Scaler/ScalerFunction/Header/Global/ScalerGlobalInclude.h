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
// ID Code      : ScalerGlobalInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _I_DOMAIN_DB_MASK                           (((_HW_I_DOMAIN_M1_PATH_SUPPORT == _ON) ? _BIT3 : 0x00) |\
                                                    ((_HW_I_DOMAIN_M2_PATH_SUPPORT == _ON) ? _BIT2 : 0x00) |\
                                                    ((_HW_I_DOMAIN_S1_PATH_SUPPORT == _ON) ? _BIT1 : 0x00) |\
                                                    ((_HW_I_DOMAIN_S2_PATH_SUPPORT == _ON) ? _BIT0 : 0x00) |\
                                                    ((_HW_I_DOMAIN_S3_PATH_SUPPORT == _ON) ? _BIT4 : 0x00) |\
                                                    ((_HW_I_DOMAIN_S4_PATH_SUPPORT == _ON) ? _BIT5 : 0x00))

//--------------------------------------------------
// Definitions of System Clock Frequency
//--------------------------------------------------
#define _GDI_CLK_DIV                                (ScalerGetBit(P80_06_GDI_CLK_DIVIDER, (_BIT3 | _BIT2 | _BIT1 | _BIT0))) // GDI Clock Divider
#define _SYS_CLK_DIV                                (ScalerGetBit(P0_22_M1_FIFO_CLOCK_SELECT, (_BIT6 | _BIT5 | _BIT4 | _BIT3)) >> 3) // System Clock Divider
#define _SYS_USE_ISO_CLK                            ((bit)ScalerGetBit(P0_09_GA_POWER_CTRL, _BIT3) ? _TRUE : _FALSE)
#define _SYS_CLK_KHZ                                (DWORD)((bit)ScalerGetBit(P0_22_M1_FIFO_CLOCK_SELECT, _BIT2) ? (((DWORD)1000 * _M2PLL_CLK_MHZ) / _SYS_CLK_DIV) : (_SYS_USE_ISO_CLK ? _HW_INTERNAL_OSC_XTAL : _EXT_XTAL))

#define _M2PLL_SYS_DIV                              13
#define _M2PLL_MEASURE_DIV                          4

//--------------------------------------------------
// Definitation of IMD double buffer
//--------------------------------------------------
// Input slow: ivs + iblock_00 --> worse case, I_frame need 3 frame to apply, add 1 I_frame for D_frame apply
// 24Hz 4 frame time
#define _DOUBLE_BUFFER_WAIT_TIME                    (168)

//--------------------------------------------------
// Definition of Interrupt Event
//--------------------------------------------------
#if(_GLOBAL_INTERRUPT_FUNCTION_FOR_IDOMAIN == _ON)
#define SET_EVENT_IVS_INT(x, y)                     (g_pstGlobalIntFuncForIDomain[x].b1IVSFlag = (y))
#define GET_EVENT_IVS_INT(x)                        (g_pstGlobalIntFuncForIDomain[x].b1IVSFlag)

#define SET_EVENT_IEN_START_INT(x, y)               (g_pstGlobalIntFuncForIDomain[x].b1IenStartFlag = (y))
#define GET_EVENT_IEN_START_INT(x)                  (g_pstGlobalIntFuncForIDomain[x].b1IenStartFlag)

#define SET_EVENT_IEN_STOP_INT(x, y)                (g_pstGlobalIntFuncForIDomain[x].b1IenStopFlag = (y))
#define GET_EVENT_IEN_STOP_INT(x)                   (g_pstGlobalIntFuncForIDomain[x].b1IenStopFlag)
#endif

#if(_GLOBAL_INTERRUPT_FUNCTION_FOR_DDOMAIN == _ON)
#define SET_EVENT_DEN_START_INT(x)                  (g_stGlobalIntFuncForDDomain.b1DenStartFlag = (x))
#define GET_EVENT_DEN_START_INT()                   (g_stGlobalIntFuncForDDomain.b1DenStartFlag)

#define SET_EVENT_DEN_STOP_INT(x)                   (g_stGlobalIntFuncForDDomain.b1DenStopFlag = (x))
#define GET_EVENT_DEN_STOP_INT()                    (g_stGlobalIntFuncForDDomain.b1DenStopFlag)
#endif

#if(_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_IV)
#define SET_I_DB_APPLY_POINT(x)                     (g_enumGlobalIDBApplyPoint = (x))
#define GET_I_DB_APPLY_POINT()                      (g_enumGlobalIDBApplyPoint)
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef struct
{
    BYTE pucFtearPrevent[4];
    BYTE ucGroupNum;
    EnumInputDataPath penumGroup[4];
} StructDBDataPathGroup;

#if(_GLOBAL_INTERRUPT_FUNCTION_FOR_IDOMAIN == _ON)
//--------------------------------------------------
// Enumerations of Functions using Global Interrupt
//--------------------------------------------------
typedef struct
{
#if(_DM_FUNCTION == _ON)
    BYTE b1DM : 1;
#endif

    BYTE b1IVSFlag : 1;
    BYTE b1IenStartFlag : 1;
    BYTE b1IenStopFlag : 1;
} StructGlobalIntFuncForIDomain;
#endif

#if(_GLOBAL_INTERRUPT_FUNCTION_FOR_DDOMAIN == _ON)
//--------------------------------------------------
// Enumerations of Functions using Global Interrupt
//--------------------------------------------------
typedef struct
{
#if((_OD_FUNCTION == _ON) && (_FRC_SUPPORT == _ON))
    BYTE b1DynamicOD : 1;
#endif

#if(_COLOR_IP_LOCAL_CONTRAST_HISTOGRAM == _ON)
    BYTE b1LocalContrast : 1;
#endif

#if((_MOTION_BLUR_REDUCTION_LCD_SUPPORT == _ON) && (_DRR_MOTION_BLUR_REDUCTION_SUPPORT == _ON))
    BYTE b1DrrMbrDVS : 1;
#endif

    BYTE b1DenStartFlag : 1;
    BYTE b1DenStopFlag : 1;
} StructGlobalIntFuncForDDomain;
#endif

#if(_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_IV)
//--------------------------------------------------
// Enumerations of I DB Apply Point
//--------------------------------------------------
typedef enum
{
    _GLOBAL_APPLY_I,
    _GLOBAL_APPLY_I_MI,
} EnumGlobalIDBApplyPoint;
#endif

//--------------------------------------------------
// Enumerations of Frame Sync Line buffer Fifo WD status
//--------------------------------------------------
typedef enum
{
    _FRAME_BUFFER_NO_NEED_TO_CHK = 0x00,
    _LINE_BUFFER_FIFO_WD_EBABLE = _BIT0,
    _LINE_BUFFER_FIFO_IRQ_EBABLE = _BIT1,
    _LINE_BUFFER_FIFO_WD_IRQ_EBABLE = (_LINE_BUFFER_FIFO_WD_EBABLE | _LINE_BUFFER_FIFO_IRQ_EBABLE),
} EnumGlobalLineBufferFifoWDIrqStatus;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if(_GLOBAL_INTERRUPT_FUNCTION_FOR_IDOMAIN == _ON)
extern volatile StructGlobalIntFuncForIDomain g_pstGlobalIntFuncForIDomain[_HW_I_DOMAIN_PATH_COUNT];
#endif

#if(_GLOBAL_INTERRUPT_FUNCTION_FOR_DDOMAIN == _ON)
extern volatile StructGlobalIntFuncForDDomain g_stGlobalIntFuncForDDomain;
#endif

#if(_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_IV)
extern EnumGlobalIDBApplyPoint g_enumGlobalIDBApplyPoint;
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************

extern BYTE ScalerGlobalGetIDCode(void);

#if((_FRC_SUPPORT == _ON) && (_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_I))
extern BYTE ScalerGlobalIDDomainDBApplyFRCModeCheck(EnumInputDataPath enumSelectedDataPath);
extern void ScalerGlobalIDDomainDBApplyFRCModeSetDB(EnumInputDataPath enumSelectedDataPath);
extern void ScalerGlobalIDDomainDBSetBufferAddress(StructDBDataPathGroup *pstDataPathGroupInfo);
extern void ScalerGlobalIDDomainDBGetDataPathGroup(EnumInputDataPath enumSelectedDataPath, StructDBDataPathGroup *pstDataPathGroupInfo);
extern void ScalerGlobalIDDomainDBClearReadyBit(EnumInputDataPath enumSelectedDataPath);
#endif

#if((_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_I) || (_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_IV))
extern void ScalerGlobalIDomainDoubleBufferEnable(EnumInputDataPath enumSelectedDataPath, bit bEn);
extern EnumIDomainDBEnableStatus ScalerGlobalGetIDomainDBStatus(EnumInputDataPath enumSelectedDataPath);
extern void ScalerGlobalDDomainDoubleBufferEnable(bit bEn);
#endif

#if(_DISPLAY_PREVENT_GARBAGE_METHOD == _GARBAGE_PREVENT_BY_WATCH_DOG)
extern bit ScalerGlobalGetDvsTimeoutWatchDogEnable(void);
extern void ScalerGlobalSetDvsTimeoutWatchDog(bit bEnable);
#endif

extern void ScalerGlobalIDDomainDBSetTriggerEvent(EnumInputDataPath enumSelectedDataPath, EnumDBIDomainTriggerEvent enumTriggerEvent);

#if(_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_IV)
extern void ScalerGlobalClrIDoubleBufferHappenFlag(void);
extern void ScalerGlobalClrDDoubleBufferHappenFlag(void);

extern void ScalerGlobalDoubleBufferMdomainForceApplyEnable(bit bEnable);
extern void ScalerGlobalDoubleBufferSetMIForceApplyFrameEnd(BYTE ucFrameend, EnumInputDataPath enumInputPath);
extern void ScalerGlobalDoubleBufferSetMDForceApplyFrameEnd(WORD usFrameend);
#endif

extern BYTE ScalerGlobalGetIDomainDBApplyBit(EnumInputDataPath enumInputDataPath);
extern EnumInputDataPath ScalerGlobalGetIDomainInputDataPath(EnumWaitIDomainEventType enumEvent, EnumInputDataPath enumInputDataPath);

extern EnumGlobalLineBufferFifoWDIrqStatus ScalerGlobalGetFrameSyncLinebufferFifoWatchDogStatus(void);
extern void ScalerGlobalSetFrameSyncLinebufferFifoWDIrq(EnumGlobalLineBufferFifoWDIrqStatus enumWDIrqStatus, bit bEnable);
