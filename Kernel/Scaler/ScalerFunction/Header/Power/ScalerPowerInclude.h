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
// ID Code      : ScalerPowerInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define POLLING_VCCK_OFF_STATUS(timeout)                {\
                                                            BYTE ucLocalTimeOut = (timeout);\
                                                            ScalerSetByte(_POLLING_VCCK_ADDR, _POLLING_VCCK_VALUE);\
                                                            while((ScalerGetByte(_POLLING_VCCK_ADDR) != _POLLING_VCCK_VALUE) && ((ucLocalTimeOut)-- != 0))\
                                                            {\
                                                                ScalerSetByte(_POLLING_VCCK_ADDR, _POLLING_VCCK_VALUE);\
                                                                ScalerTimerDelayXms(1);\
                                                            }\
                                                            ScalerTimerDelayXms(10);\
                                                        }

//--------------------------------------------------
// Power Domain Macro
//--------------------------------------------------
#define GET_POWER_ISO_TOP_FLG()                         ((bit)(g_stPowerIsolationStatus.b1IsolationTop))
#define SET_POWER_ISO_TOP_FLG()                         (g_stPowerIsolationStatus.b1IsolationTop = 1)
#define CLR_POWER_ISO_TOP_FLG()                         (g_stPowerIsolationStatus.b1IsolationTop = 0)

#define GET_POWER_ISO_AUDIO_FLG()                       ((bit)(g_stPowerIsolationStatus.b1IsolationAudio))
#define SET_POWER_ISO_AUDIO_FLG()                       (g_stPowerIsolationStatus.b1IsolationAudio = 1)
#define CLR_POWER_ISO_AUDIO_FLG()                       (g_stPowerIsolationStatus.b1IsolationAudio = 0)

#define GET_POWER_ISO_GDITX_FLG()                       ((bit)(g_stPowerIsolationStatus.b1IsolationGdiTx))
#define SET_POWER_ISO_GDITX_FLG()                       (g_stPowerIsolationStatus.b1IsolationGdiTx = 1)
#define CLR_POWER_ISO_GDITX_FLG()                       (g_stPowerIsolationStatus.b1IsolationGdiTx = 0)

#define GET_POWER_ISO_GDIRX_FLG()                       ((bit)(g_stPowerIsolationStatus.b1IsolationGdiRx))
#define SET_POWER_ISO_GDIRX_FLG()                       (g_stPowerIsolationStatus.b1IsolationGdiRx = 1)
#define CLR_POWER_ISO_GDIRX_FLG()                       (g_stPowerIsolationStatus.b1IsolationGdiRx = 0)

#define GET_POWER_ISO_DPMAC_FLG()                       ((bit)(g_stPowerIsolationStatus.b1IsolationDpMac))
#define SET_POWER_ISO_DPMAC_FLG()                       (g_stPowerIsolationStatus.b1IsolationDpMac = 1)
#define CLR_POWER_ISO_DPMAC_FLG()                       (g_stPowerIsolationStatus.b1IsolationDpMac = 0)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef struct
{
    BYTE b1IsolationTop : 1;
    BYTE b1IsolationAudio : 1;
    BYTE b1IsolationGdiTx : 1;
    BYTE b1IsolationGdiRx : 1;
    BYTE b1IsolationDpMac : 1;
} StructPowerIsolation;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern StructPowerIsolation g_stPowerIsolationStatus;

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern EnumPowerCut ScalerPowerGroupGetPowerCutStatus(EnumPowerGroup enumPowerGroup);
extern void ScalerPowerGroupPowerCut(EnumPowerGroup enumPowerGroup, EnumPowerCut enumPowerCut, EnumPowerReset enumPowerReset);
#if(_HW_IMD_POWER_CUT_INDEPENDENT_SUPPORT == _ON)
extern void ScalerPowerDisplayInitialSetting(EnumDisplayMode enumDisplayMode);
#endif
extern bit ScalerPowerDomainClockGatingControl(EnumPowerClockGatingGroup enumPowerClockGatingGroup, EnumPowerClockGating enumPowerClockGating);
