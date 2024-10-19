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
// ID Code      : 3rdPartyDM.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef enum
{
    _DM_CONTROL_PATH_VERIFY_FAIL,
    _DM_CONTROL_PATH_FAIL,
    _DM_CONTROL_PATH_SUCCESS,
} Enum3rdPartyDMControlPathStatus;

typedef struct
{
    DWORD ulBW32_ADDRESS; /*!< Offset: 0x00 BurstWrite Reg Address#0 */
    DWORD ulBW32_DATA; /*!< Offset: 0x04 BurstWrite Reg Data#0 */
} StructBW32CmdUnitFormat;

typedef struct
{
    WORD usBacklightData;
    WORD usBrightnessData;
    WORD usContrastData;
    WORD usSaturationData;
} Struct3rdPartyDMColorData;

typedef struct
{
    SDWORD lDMPictureMode;
    Struct3rdPartyDMColorData stDMColorData;
} Struct3rdPartyDMOsdSetting;

typedef struct
{
    BYTE ucWx_LSB;
    BYTE ucWy_LSB;
    BYTE ucMaxCLL;
    BYTE ucMaxFALL;
    WORD usRx;
    WORD usRy;
    WORD usGx;
    WORD usGy;
    WORD usBx;
    WORD usBy;
} Struct3rdPartyDMDRM;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern bit DMInit(DWORD ulCustomerFwId, Struct3rdPartyDMDRM *pstDMDRM);
extern Enum3rdPartyDMControlPathStatus DMControlPathTest(DWORD *pulDMRegister, DWORD *pulDMB0103, DWORD *pulDMB02, StructBW32CmdUnitFormat *pstDMB0501, BYTE *pucMetadata, BYTE *pucConfigFile, char *pucInfoFrame[], BYTE ucBECArgc, Struct3rdPartyDMOsdSetting *pstDMOSDColorSetting);
