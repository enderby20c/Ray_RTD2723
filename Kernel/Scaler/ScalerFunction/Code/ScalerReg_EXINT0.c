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
// ID Code      : ScalerReg_EXINT0.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_REG_EXINT0__

#include "ScalerFunctionInclude.h"
#include "Reg/ScalerReg.h"




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
// Description  : Enable Access Port
// Input Value  : usAddr    --> Start address of register
//                ucValue   --> Data Port Value we want to set
// Output Value : Return Access Port Value
//--------------------------------------------------
BYTE ScalerEnableAccessPort_EXINT0(WORD usAddr, BYTE ucValue)
{
    usAddr = usAddr;
    return ucValue;
}

//--------------------------------------------------
// Description  : Disable Access Port
// Input Value  : usAddr   --> Start address of register
// Output Value : None
//--------------------------------------------------
void ScalerDisableAccessPort_EXINT0(WORD usAddr)
{
    usAddr = usAddr;
}

//--------------------------------------------------
// Description  : Set the value into selected register in data port
// Input Value  : usAddr    --> Access Port Address of register
//                ucValue1  --> Data Port Value we want to set
//                ucValue2  --> Data Value we want to set
// Output Value : None
//--------------------------------------------------
void ScalerSetDataPortByte_EXINT0(WORD usAddr, BYTE ucValue1, BYTE ucValue2)
{
    // backup port addr
    BYTE ucBackupPortAddr = ScalerGetByte_EXINT(usAddr);

    ScalerSetByte_EXINT(usAddr, ScalerEnableAccessPort_EXINT0(usAddr, ucValue1));
    ScalerSetByte_EXINT(usAddr + 1, ucValue2);

    ScalerDisableAccessPort_EXINT0(usAddr);

    // return backup port addr
    ScalerSetByte_EXINT(usAddr, ucBackupPortAddr);
}

//--------------------------------------------------
// Description  : Get bytes from selected register in data port
// Input Value  : usAddr    --> Access Port Address of register
//                ucValue   --> Data Port Address we want to Get
//                ucLength  --> Numbers of data we want to read
//                pArray    --> Pointer of the reading data array
//                bAutoInc  --> Address auto increasing select
// Output Value : None
//--------------------------------------------------
void ScalerGetDataPortByte_EXINT0(WORD usAddr, BYTE ucValue, WORD usLength, BYTE *pucArray, bit bAutoInc)
{
    BYTE ucAccessValue = 0;
    WORD usIndex = 0;

    // backup port addr
    BYTE ucBackupPortAddr = ScalerGetByte_EXINT(usAddr);

    if(usLength > 0)
    {
        ucAccessValue = ScalerEnableAccessPort_EXINT0(usAddr, ucValue);

        for(usIndex = 0; usIndex < usLength; usIndex++)
        {
            if(bAutoInc == _AUTOINC)
            {
                ScalerSetByte_EXINT(usAddr, ucAccessValue + usIndex);
            }
            else
            {
                ScalerSetByte_EXINT(usAddr, ucAccessValue);
            }

            pucArray[usIndex] = ScalerGetByte_EXINT(usAddr + 1);
        }

        ScalerDisableAccessPort_EXINT0(usAddr);
    }

    // return backup port addr
    ScalerSetByte_EXINT(usAddr, ucBackupPortAddr);
}

//--------------------------------------------------
// Description  : Set some bits of selected register in data port
// Input Value  : usAddr    --> Access Port Address of register
//                ucValue   --> Data Port Value we want to set
//                ulAnd     --> & operation
//                ucOr      --> | operation
// Output Value : None
//--------------------------------------------------
void ScalerSetDataPortBit_EXINT0(WORD usAddr, BYTE ucValue, DWORD ulAnd, BYTE ucOr)
{
    BYTE ucValueTemp = 0;

    // backup port addr
    BYTE ucBackupPortAddr = ScalerGetByte_EXINT(usAddr);

    ScalerSetByte_EXINT(usAddr, ScalerEnableAccessPort_EXINT0(usAddr, ucValue));
    ucValueTemp = ScalerGetByte_EXINT(usAddr + 1);

    ucValueTemp = (ucValueTemp & (BYTE)ulAnd) | ucOr;

    ScalerSetByte_EXINT(usAddr, ScalerEnableAccessPort_EXINT0(usAddr, ucValue));
    ScalerSetByte_EXINT(usAddr + 1, ucValueTemp);

    ScalerDisableAccessPort_EXINT0(usAddr);

    // return backup port addr
    ScalerSetByte_EXINT(usAddr, ucBackupPortAddr);
}

//--------------------------------------------------
// Description  : Set some bits of selected register in data port
// Input Value  : usAddr    --> Access Port Address of register
//                ucValue   --> Data Port Value we want to set
//                ucAnd     --> & operation
// Output Value : Value after & operation
//--------------------------------------------------
BYTE ScalerGetDataPortBit_EXINT0(WORD usAddr, BYTE ucValue, BYTE ucAnd)
{
    BYTE ucValueTemp = 0;

    // backup port addr
    BYTE ucBackupPortAddr = ScalerGetByte_EXINT(usAddr);

    ScalerSetByte_EXINT(usAddr, ScalerEnableAccessPort_EXINT0(usAddr, ucValue));
    ucValueTemp = (ScalerGetByte_EXINT(usAddr + 1) & ucAnd);
    ScalerDisableAccessPort_EXINT0(usAddr);

    // return backup port addr
    ScalerSetByte_EXINT(usAddr, ucBackupPortAddr);

    return ucValueTemp;
}

//--------------------------------------------------
// Description  : Get bytes from selected register in data port
// Input Value  : usAddr    --> Access Port Address of register
//                ucValue   --> Data Port Address we want to Get
// Output Value : None
//--------------------------------------------------
BYTE ScalerGetDataPortSingleByte_EXINT0(WORD usAddr, BYTE ucValue)
{
    BYTE ucLength = 1;
    BYTE pucArray[1] = {0};

    ScalerGetDataPortByte_EXINT0(usAddr, ucValue, ucLength, pucArray, _NON_AUTOINC);

    return pucArray[0];
}

//--------------------------------------------------
// Description  : Get bytes from selected register in data port
// Input Value  : usAddr    --> Access Port Address of register
//                ucValue   --> Data Port Address we want to Get
//                bAutoInc  --> Address auto increasing select
// Output Value : None
//--------------------------------------------------
WORD ScalerGetDataPortWord_EXINT0(WORD usAddr, BYTE ucValue, bit bAutoInc)
{
    BYTE pucArray[2] = {0};

    // backup port addr
    BYTE ucBackupPortAddr = ScalerGetByte_EXINT(usAddr);

    ScalerGetDataPortByte_EXINT0(usAddr, ucValue, 2, pucArray, bAutoInc);

    // return backup port addr
    ScalerSetByte_EXINT(usAddr, ucBackupPortAddr);

    return (WORD)pucArray[0] * 256 + pucArray[1];
}

