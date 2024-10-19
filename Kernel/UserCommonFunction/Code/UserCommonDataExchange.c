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
// ID Code      : UserCommonDataExchange.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_COMMON_DATA_EXCHANGE__

#include "UserCommonInclude.h"
#include "DataExchange/UserCommonDataExchange.h"

//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_TWO_CHIP_DATA_EXCHANGE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Data Exchange Send Data Byte
// Input Value  : Data Exchange  Group, Cmd, Byte
// Output Value : ture or false
//--------------------------------------------------
bit UserCommonDataExchangeSendEvent(EnumDataExchangeTypeGroup enumDataExchangeTypeGroup, BYTE ucCmdType)
{
    DebugMessageSystem("Data Exchange Send Data CMD Group", enumDataExchangeTypeGroup);
    DebugMessageSystem("Data Exchange Send Data CMD Type", ucCmdType);

    if(ScalerMcuDataExchangeSendData((BYTE)enumDataExchangeTypeGroup, ucCmdType, 0, pData) == _TRUE)
    {
        return _TRUE;
    }
    else
    {
        return _FALSE;
    }
}

//--------------------------------------------------
// Description  : Data Exchange Send Data Byte
// Input Value  : Data Exchange  Group, Cmd, Byte
// Output Value : ture or false
//--------------------------------------------------
bit UserCommonDataExchangeSendByte(EnumDataExchangeTypeGroup enumDataExchangeTypeGroup, BYTE ucCmdType, BYTE ucWriteByte)
{
    DebugMessageSystem("Data Exchange Send Data CMD Group", enumDataExchangeTypeGroup);
    DebugMessageSystem("Data Exchange Send Data CMD Type", ucCmdType);

    if(ScalerMcuDataExchangeSendData((BYTE)enumDataExchangeTypeGroup, ucCmdType, 1, &ucWriteByte) == _TRUE)
    {
        return _TRUE;
    }
    else
    {
        return _FALSE;
    }
}

//--------------------------------------------------
// Description  : Data Exchange Send Data Array
// Input Value  : Data Exchange  Group, Cmd, Length, Array
// Output Value : ture or false
//--------------------------------------------------
bit UserCommonDataExchangeSendData(EnumDataExchangeTypeGroup enumDataExchangeTypeGroup, BYTE ucCmdType, BYTE ucDataLength, BYTE *pucWriteArray)
{
    DebugMessageSystem("Data Exchange Send Data CMD Group", enumDataExchangeTypeGroup);
    DebugMessageSystem("Data Exchange Send Data CMD Type", ucCmdType);

    if(ScalerMcuDataExchangeSendData((BYTE)enumDataExchangeTypeGroup, ucCmdType, ucDataLength, pucWriteArray) == _TRUE)
    {
        return _TRUE;
    }
    else
    {
        return _FALSE;
    }
}

//--------------------------------------------------
// Description  : Data Exchange Check Send Data Byte done
// Input Value  : Data Exchange  Group, Cmd, Byte, Polling Interval
// Output Value : ture or false
//--------------------------------------------------
bit UserCommonDataExchangeCheckSendEventDone(EnumDataExchangeTypeGroup enumDataExchangeTypeGroup, BYTE ucCmdType, BYTE ucPollingInterval)
{
    DebugMessageSystem("Data Exchange Send Data CMD Group", enumDataExchangeTypeGroup);
    DebugMessageSystem("Data Exchange Send Data CMD Type", ucCmdType);

    if(ScalerMcuDataCheckSendDataDone((BYTE)enumDataExchangeTypeGroup, ucCmdType, 0, pData, ucPollingInterval) == _TRUE)
    {
        return _TRUE;
    }
    else
    {
        return _FALSE;
    }
}

//--------------------------------------------------
// Description  : Data Exchange Check Send Data Byte done
// Input Value  : Data Exchange  Group, Cmd, Byte, Polling Interval
// Output Value : ture or false
//--------------------------------------------------
bit UserCommonDataExchangeCheckSendByteDone(EnumDataExchangeTypeGroup enumDataExchangeTypeGroup, BYTE ucCmdType, BYTE ucWriteByte, BYTE ucPollingInterval)
{
    DebugMessageSystem("Data Exchange Send Data CMD Group", enumDataExchangeTypeGroup);
    DebugMessageSystem("Data Exchange Send Data CMD Type", ucCmdType);

    if(ScalerMcuDataCheckSendDataDone((BYTE)enumDataExchangeTypeGroup, ucCmdType, 1, &ucWriteByte, ucPollingInterval) == _TRUE)
    {
        return _TRUE;
    }
    else
    {
        return _FALSE;
    }
}

//--------------------------------------------------
// Description  : Data Exchange Check Send Data Array done
// Input Value  : Data Exchange  Group, Cmd, Length, Array, Polling Interval
// Output Value : ture or false
//--------------------------------------------------
bit UserCommonDataExchangeCheckSendDataDone(EnumDataExchangeTypeGroup enumDataExchangeTypeGroup, BYTE ucCmdType, BYTE ucDataLength, BYTE *pucWriteArray, BYTE ucPollingInterval)
{
    DebugMessageSystem("Data Exchange Check Send Data CMD Group", enumDataExchangeTypeGroup);
    DebugMessageSystem("Data Exchange Check Send Data CMD Type", ucCmdType);

    if(ScalerMcuDataCheckSendDataDone((BYTE)enumDataExchangeTypeGroup, ucCmdType, ucDataLength, pucWriteArray, ucPollingInterval) == _TRUE)
    {
        return _TRUE;
    }
    else
    {
        return _FALSE;
    }
}
#endif

