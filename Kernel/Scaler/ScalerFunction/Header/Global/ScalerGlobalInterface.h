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
// ID Code      : ScalerGlobalInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Macro for global lock
//--------------------------------------------------
#define CHK_GLOBAL_D_DB_LOCK()                              (g_stGlobalLock.b1DDomainDBLock)
#define GET_GLOBAL_D_DB_LOCK()                              (g_stGlobalLock.b1DDomainDBLock = _TRUE)
#define CLR_GLOBAL_D_DB_LOCK()                              (g_stGlobalLock.b1DDomainDBLock = _FALSE)

#define CHK_BURST_WRITE_LOCK()                              (g_stGlobalLock.b1BurstWriteLock)
#define GET_BURST_WRITE_LOCK()                              (g_stGlobalLock.b1BurstWriteLock = _TRUE)
#define CLR_BURST_WRITE_LOCK()                              (g_stGlobalLock.b1BurstWriteLock = _FALSE)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Enumerations IRQ Type
//--------------------------------------------------
typedef enum
{
    _IRQ_NONE = 0x00,
    _IRQ_IVS,
    _IRQ_IEN_START,
    _IRQ_IEN_STOP,
    _IRQ_DVS,
    _IRQ_DEN_START,
    _IRQ_DEN_STOP,
#if(_HW_DVS_TIMEOUT_IRQ_SUPPORT == _ON)
    _IRQ_DVS_TIMEOUT,
#endif
    _IRQ_IHS_TIMEOUT
} EnumIRQ;

//--------------------------------------------------
// Enumerations Functions which use Global IRQ
//--------------------------------------------------
typedef enum
{
    _GLOBAL_INT_IDOMAIN_DM,
    _GLOBAL_INT_IDOMAIN_ALL_FUNCTION
} EnumGlobalIntFuncForIDomain;

//--------------------------------------------------
// Enumerations Functions which use Global IRQ
//--------------------------------------------------
typedef enum
{
    _GLOBAL_INT_DDOMAIN_DYNAMIC_OD,
    _GLOBAL_INT_DDOMAIN_ADVANCED_HDR10,
    _GLOBAL_INT_DDOMAIN_DRR_MBR_DVS,
    _GLOBAL_INT_DDOMAIN_LOCAL_CONTRAST,
    _GLOBAL_INT_DDOMAIN_ALL_FUNCTION
} EnumGlobalIntFuncForDDomain;

//--------------------------------------------------
// Enumerations of System Clock
//--------------------------------------------------
typedef enum
{
    _EXT_XTAL_CLK,
    _IOSC_CLK,
    _M2PLL_CLK,
    _ECBUS_CLK
} EnumClkSel;

//--------------------------------------------------
// Enumerations of DB trigger event
//--------------------------------------------------
typedef enum
{
    _DB_TRIGGER_EVENT_IVS,
    _DB_TRIGGER_EVENT_IEN_STOP,
} EnumDBIDomainTriggerEvent;

//--------------------------------------------------
// Enumerations of DB Enable Status
//--------------------------------------------------
typedef enum
{
    _DB_DISABLE = 0x00,

    _I_DB_ENABLE = _BIT0,
    _D_DB_ENABLE = _BIT1,
    _ID_DB_SYNC = _BIT2,
    _VGIP_DB_ENABLE = _BIT3,
    _DTG_DB_ENABLE = _BIT4,

    _I_D_DB_ENABLE = (_I_DB_ENABLE | _D_DB_ENABLE),
    _VGIP_DTG_DB_ENABLE = (_VGIP_DB_ENABLE | _DTG_DB_ENABLE),
    _IMD_DB_ENABLE = (_ID_DB_SYNC | _I_D_DB_ENABLE),
} EnumDBEnableStatus;

//--------------------------------------------------
// Enumerations of I Domain DB Enable Status
//--------------------------------------------------
typedef enum
{
    _I_DOMAIN_DB_DISABLE = 0x00,

    _I_M1_DB_ENABLE = _BIT0,
    _I_M2_DB_ENABLE = _BIT1,
    _I_S1_DB_ENABLE = _BIT2,
    _I_S2_DB_ENABLE = _BIT3,
    _I_S3_DB_ENABLE = _BIT4,
    _I_S4_DB_ENABLE = _BIT5,
} EnumIDomainDBEnableStatus;

//--------------------------------------------------
// Enumerations of VGIP DB Enable Status
//--------------------------------------------------
typedef enum
{
    _VGIP_DB_DISABLE = 0x00,

    _VGIP_M1_DB_ENABLE = _BIT0,
    _VGIP_M2_DB_ENABLE = _BIT1,
    _VGIP_S1_DB_ENABLE = _BIT2,
    _VGIP_S2_DB_ENABLE = _BIT3,
    _VGIP_S3_DB_ENABLE = _BIT4,
    _VGIP_S4_DB_ENABLE = _BIT5,
} EnumVGIPDBEnableStatus;

//--------------------------------------------------
// Enumerations FrontBack Status Position
//--------------------------------------------------
typedef enum
{
    _FRONT_BACK_IN_I_DOMAIN,
    _FRONT_BACK_IN_D_DOMAIN_ALL_PATH,
    _FRONT_BACK_IN_D_DOMAIN_BEFORE_BLENDING,
} EnumFrontBackStatusPosition;

//--------------------------------------------------
// Enumerations of DP Cable ID Detect
//--------------------------------------------------
typedef enum
{
    _DP_CABLE_ID_RESULT_LOW = 0x00,
    _DP_CABLE_ID_RESULT_MID,
    _DP_CABLE_ID_RESULT_HIGH,
} EnumDpCableIDResult;

//--------------------------------------------------
// Struct for global resource locks
//--------------------------------------------------
typedef struct
{
    BYTE b1DDomainDBLock : 1;
    BYTE b1BurstWriteLock : 1;
} StructEnumGlobalLock;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern volatile StructEnumGlobalLock g_stGlobalLock;

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerGlobalDisplayInitial(EnumDisplayMode enumDisplayMode);
extern void ScalerGlobalSetInt31EnableStatus(bit bEn);
extern bit ScalerGlobalGetInt31EnableStatus(void);
extern void ScalerGlobalRemovePortMapping(EnumInputPort enumInputPort, EnumDDomainRegion enumDDomainRegion);
extern void ScalerGlobalWholeChipReset(void);
extern void ScalerGlobalCrystalClkSel(EnumClkSel enumSel);
extern void ScalerGlobalOsdInitial(void);
extern void ScalerGlobalResetProc(BYTE ucResetTarget);
extern void ScalerGlobalFirstActiveProc(EnumSourceType enumSourceType, BYTE ucGetInputPort, EnumDisplayRegion enumDisplayRegion);
extern void ScalerGlobalSystemClkSel(EnumClkSel enumClockSel);

extern void ScalerGlobalDoubleBufferEnable(EnumInputDataPath enumSelectedDataPath, bit bEn);
extern void ScalerGlobalIDDomainDBSetTriggerEventInitial(EnumInputDataPath enumSelectedDataPath, EnumDBIDomainTriggerEvent enumTriggerEvent);
extern void ScalerGlobalDDomainDBApply(EnumDDomainDBApplyRegion enumDDomainDBApplyRegion, EnumDBApply enumDBApply);
extern void ScalerGlobalIDomainDBApply(EnumInputDataPath enumInputDataPath, EnumDBApply enumDBApply);
extern EnumDBEnableStatus ScalerGlobalGetDBStatus(EnumInputDataPath enumInputDataPath);
extern void ScalerGlobalIDDomainDBApply(EnumInputDataPath enumSelectedDataPath, EnumDBApply enumDBApply);
extern void ScalerGlobalWaitDDomainDBApplyFinish(void);
extern void ScalerGlobalResetDoubleBuffer(EnumInputDataPath enumInputDataPath, EnumDBEnableStatus enumDBEnableStatus, bit bEn);
extern void ScalerGlobalDisableAllWatchDog(void);

#if((_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_I) || (_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_IV))
extern bit ScalerGlobalGetDDomainDBStatus(void);
#endif

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
extern void ScalerGlobalResetExtension(void);
#endif

#if((_DISPLAY_PREVENT_GARBAGE_METHOD == _GARBAGE_PREVENT_BY_BACKLIGHT) || (_DISPLAY_PREVENT_GARBAGE_METHOD == _GARBAGE_PREVENT_BY_IRQ_BACKGROUND))
extern void ScalerGlobalPreventGarbageByBacklight_EXINT0(void);
#endif

#if(_GLOBAL_INTERRUPT_FUNCTION_FOR_IDOMAIN == _ON)
extern void ScalerGlobalIDomainIntHandler_EXINT0(void);
extern void ScalerGlobalInterruptProcForIDomain(EnumGlobalIntFuncForIDomain enumGlobalIntFunction, EnumInputDataPath enumInputDataPath, bit bEn);
#endif

#if(_GLOBAL_INTERRUPT_FUNCTION_FOR_DDOMAIN == _ON)
extern void ScalerGlobalDDomainIntHandler_EXINT0(void);
extern void ScalerGlobalInterruptProcForDDomain(EnumGlobalIntFuncForDDomain enumGlobalIntFunction, BYTE ucEn);
#endif

extern void ScalerGlobalPathWatchDog(EnumInputDataPath enumInputDataPath, bit bEnable);
extern void ScalerGlobalClrDvsTimeoutFlag(void);

#if(_M_DOMAIN_IMG_CMP_SUPPORT == _ON)
#if(_HW_M_DOMAIN_IMG_CMP_TYPE == _M_DOMAIN_IMG_CMP_GEN_1)
extern void ScalerGlobalEnableUnderflowMonitor(bit bEnable, EnumDDomainRegion enumDDomainRegion);
#endif
#endif


//****************************************************************************
// IN-LINE FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Get if F/B mode should be supported for currently used panel parameter
// Input Value  : None
// Output Value : _TRUE if Front/Back mode should be supported
//--------------------------------------------------
inline bit ScalerGlobalGetFrontBackStatus(EnumFrontBackStatusPosition enumFrontBackStatusPosition)
{
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    if(GET_D_DOMAIN_PATH() == _D_DOMAIN_4_PATH)
    {
        switch(enumFrontBackStatusPosition)
        {
            case _FRONT_BACK_IN_D_DOMAIN_ALL_PATH:
                return _TRUE;

            case _FRONT_BACK_IN_I_DOMAIN:
                switch(GET_DISPLAY_MODE())
                {
                    case _DISPLAY_MODE_1P:
                        return _TRUE;

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
                    case _DISPLAY_MODE_2P_PIP:
                        return _TRUE;
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
                    case _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT:
                        return _TRUE;
#endif

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
                    case _DISPLAY_MODE_2P_PBP_LR_L_LARGE:
                    case _DISPLAY_MODE_2P_PBP_LR_R_LARGE:
                        return _TRUE;
#endif
                    default:
                        return _FALSE;
                }

            case _FRONT_BACK_IN_D_DOMAIN_BEFORE_BLENDING:
                switch(GET_DISPLAY_MODE())
                {
                    case _DISPLAY_MODE_1P:

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
                    case _DISPLAY_MODE_2P_PIP:
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
                    case _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT:
#endif

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
                    case _DISPLAY_MODE_2P_PBP_LR_L_LARGE:
                    case _DISPLAY_MODE_2P_PBP_LR_R_LARGE:
#endif

#if(_2P_PBP_TB_DISPLAY_SUPPORT == _ON)
                    case _DISPLAY_MODE_2P_PBP_TB:
#endif

#if(_3P_SKEW_TB_DISPLAY_SUPPORT == _ON)
                    case _DISPLAY_MODE_3P_SKEW_T:
                    case _DISPLAY_MODE_3P_SKEW_B:
#endif
                        return _TRUE;

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
                    case _DISPLAY_MODE_2P_PBP_LR_EQUAL:
#endif

#if(_3P_FLAG_DISPLAY_SUPPORT == _ON)
                    case _DISPLAY_MODE_3P_FLAG:
#endif

#if(_3P_SKEW_LR_DISPLAY_SUPPORT == _ON)
                    case _DISPLAY_MODE_3P_SKEW_L:
                    case _DISPLAY_MODE_3P_SKEW_R:
#endif

#if(_4P_DISPLAY_SUPPORT == _ON)
                    case _DISPLAY_MODE_4P:
#endif
                    default:
                        return _FALSE;
                }
            default:
                return _FALSE;
        }
    }
    else
#endif
    {
        enumFrontBackStatusPosition = enumFrontBackStatusPosition;
        return _FALSE;
    }
}
