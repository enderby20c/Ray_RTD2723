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
// ID Code      : RTD2020UserInterfaceNVRam.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_INTERFACE_NVRAM__

#include "RTD2020UserInclude.h"
#include "RTD2020UserInterfaceNVRam.h"

#if(_OSD_TYPE == _REALTEK_2020_OSD)

//****************************************************************************
// CODE TABLES
//****************************************************************************

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Move data to another page of flash
// Input Value  : ucPageID: previous page ID
//                pucData: data to be saved
// Output Value : _MOVE_FAIL/_MOVE_SUCCESS
//--------------------------------------------------
EnumFlashMoveDataResult UserInterfaceFlashMoveData(BYTE ucPageID, BYTE *pucData)
{
    if(RTDFlashMoveData(ucPageID, pucData) == _TRUE)
    {
        return _MOVE_SUCCESS;
    }
    else
    {
        return _MOVE_FAIL;
    }
}
#endif // End of #if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _ON)

//--------------------------------------------------
// Description  : Check Whther ADC Data is Reasonable
// Input Value  : LOAD or SAVE
// Output Value : _TRUE => Reasonable
//--------------------------------------------------
EnumNvramCheckResult UserInterfaceNVRamGetDataStatus(EnumNvramCheckType enumNvramCheckType)
{
    switch(enumNvramCheckType)
    {
#if(_VGA_SUPPORT == _ON)
        case _CHECK_ADC_LOAD:

            if(g_stVgaAdcData.ucAdcPGA >= 0xF0)
            {
                // Assign Prefered Value
                g_stVgaAdcData.ucAdcPGA = 8;
            }

            break;

        case _CHECK_ADC_SAVE:

            if(g_stVgaAdcData.ucAdcPGA >= 0xF0)
            {
                return _CHECK_FAIL;
            }
            break;
#endif

        case _CHECK_SYSTEM_DATA_LOAD:
        case _CHECK_SYSTEM_DATA_SAVE:
        case _CHECK_MODE_USER_DATA_LOAD:
        case _CHECK_MODE_USER_DATA_SAVE:

            break;

        default:
            break;
    }

    return _CHECK_SUCCESS;
}

#if(_USER_SYSTEM_EEPROM_CUSTOMIZATION == _ON)
//--------------------------------------------------
// Description  : User Custom Check Proc when System Eeprom Read
// Input Value  : usSubAddr    --> Start address of selected device
//                usLength     --> Numbers of data we want to read
//                pReadArray   --> Result array
// Output Value : Reading result (Fail/Success)
//--------------------------------------------------
EnumNvramCheckResult UserInterfaceNVRamSystemEepromReadCustomProc(DWORD ulSubAddr, WORD usLength, BYTE *pucReadArray)
{
    ulSubAddr = ulSubAddr;
    usLength = usLength;
    pucReadArray = pucReadArray;
    return _CHECK_SUCCESS;
}

//--------------------------------------------------
// Description  : User Custom Check Proc when System Eeprom Write
// Input Value  : usSubAddr    --> Start address of selected device
//                usLength     --> Numbers of data we want to write
//                pReadArray   --> Result array
// Output Value : Reading result (Fail/Success)
//--------------------------------------------------
EnumNvramCheckResult UserInterfaceNVRamSystemEepromWriteCustomProc(DWORD ulSubAddr, WORD usLength, BYTE *pucWriteArray)
{
    ulSubAddr = ulSubAddr;
    usLength = usLength;
    pucWriteArray = pucWriteArray;
    return _CHECK_SUCCESS;
}
#endif

#endif // End of #if(_OSD_TYPE == _REALTEK_2020_OSD)
