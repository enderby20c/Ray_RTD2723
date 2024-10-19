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
// ID Code      : QC_Option.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _FACTORY_RTD_QC_SUPPORT                                 _OFF

#if(_FACTORY_RTD_QC_SUPPORT == _ON)

#if(_SCALER_TYPE == _RL6829_SERIES)
#include <QC/RL6829_QC_Option.h>
#elif(_SCALER_TYPE == _RL6952_SERIES)
#include <QC/RL6952_QC_Option.h>
#elif(_SCALER_TYPE == _RL6978_SERIES)
#include <QC/RL6978_QC_Option.h>
#endif

#ifndef PCB_QC_NOTIFY
#define PCB_QC_NOTIFY(id)                                       {\
                                                                }
#endif

#ifndef EXT_DEBUG_BOARD_GPIO_INITIAL
#define EXT_DEBUG_BOARD_GPIO_INITIAL()                          {\
                                                                }
#endif

#ifndef EXT_PATTERNGEN_BOARD_INITIAL
#define EXT_PATTERNGEN_BOARD_INITIAL()                          {\
                                                                }
#endif

#endif // End of #if(_FACTORY_RTD_QC_SUPPORT == _ON)


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
#if(_FACTORY_RTD_QC_SUPPORT == _ON)
typedef enum
{
    _QC_EXT_LED_DISP_0 = 0x00,
    // Display "0"

    _QC_EXT_LED_DISP_1 = 0x01,
    // Display "1"

    _QC_EXT_LED_DISP_2 = 0x02,
    // Display "2"

    _QC_EXT_LED_DISP_3 = 0x03,
    // Display "3"

    _QC_EXT_LED_DISP_4 = 0x04,
    // Display "4"

    _QC_EXT_LED_DISP_5 = 0x05,
    // Display "5"

    _QC_EXT_LED_DISP_6 = 0x06,
    // Display "6"

    _QC_EXT_LED_DISP_7 = 0x07,
    // Display "7"

    _QC_EXT_LED_DISP_8 = 0x08,
    // Display "8"

    _QC_EXT_LED_DISP_9 = 0x09,
    // Display "9"

    _QC_EXT_LED_DISP_A = 0x0A,
    // Display "A"

    _QC_EXT_LED_DISP_B = 0x0B,
    // Display "B"

    _QC_EXT_LED_DISP_C = 0x0C,
    // Display "C"

    _QC_EXT_LED_DISP_D = 0x0D,
    // Display "D"

    _QC_EXT_LED_DISP_E = 0x0E,
    // Display "E"

    _QC_EXT_LED_DISP_F = 0x0F,
    // Display "F"

    _QC_EXT_LED_DISP_DOT = 0x100,
    // Display dot point

    _QC_EXT_LED_DISP_NONE = 0x200,
    // Display None

    _QC_EXT_LED_DISP_DUMMY = 0xF00,
    // DUMMY
} EnumQCExt7SegmentDigit;

typedef enum
{
    _QC_EXT_LED_MODE_DEC = 0x00,
    // Dec display mode

    _QC_EXT_LED_MODE_HEX,
    // Hec display mode
} EnumQCExt7SegmentDispMode;

typedef enum
{
    _QC_EXT_LED_MODE_NONE = 0x00,
    // Display nothing

    _QC_EXT_LED_MODE_ALL,
    // Display all LED
} EnumQCExt7SegmentResetType;

typedef enum
{
    _QC_EXT_LED_DEVICE_0 = 0x00,
    // LED Device U4 position (High)

    _QC_EXT_LED_DEVICE_1,
    // LED Device U3 position (Low)
} EnumQCExt7SegmentIndex;
#endif


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_FACTORY_RTD_QC_SUPPORT == _ON)
extern BYTE ScalerQCGetDisplayMode(void);
extern BYTE ScalerQCGetInputPort(void);
extern BYTE ScalerQCGetMultiPanelIndex(void);
extern bit ScalerQCUpdateConfig(void);
extern WORD ScalerQCHandler(void);
extern bit ScalerQCErrorHandler(void);
extern void ScalerQCExtBoardInitialProc(void);
extern void ScalerQCExtBoard7SegmentDisplay(BYTE ucNum, EnumQCExt7SegmentDispMode enumLEDDispMode);
#endif
