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
// ID Code      : RTD2020UserInterfaceHdcp.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_INTERFACE_HDCP__

#include "RTD2020UserInclude.h"
#include "RTD2020UserInterfaceHdcp.h"

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
#if(_DIGITAL_PORT_SUPPORT == _ON)

#if(_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_USER)
//--------------------------------------------------
// Description  : Get HDCP Bksv By User Defined Method
// Input Value  : ucSubaddr: Address of HDCP
//                ucLength: Length of HDCP
//                pucReadArray: HDCP data
// Output Value : None
//--------------------------------------------------
void UserInterfaceHdcpGetKeyBksvByUser(BYTE ucSubAddr, BYTE ucLength, BYTE *pucReadArray)
{
    ucSubAddr = ucSubAddr;
    ucLength = ucLength;
    pucReadArray = pucReadArray;
}

//--------------------------------------------------
// Description  : Get HDCP By User Defined Method
// Input Value  : ucSubaddr: Address of HDCP
//                ucLength: Length of HDCP
//                pucReadArray: HDCP data
// Output Value : None
//--------------------------------------------------
void UserInterfaceHdcpGetKeyByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    usSubAddr = usSubAddr;
    usLength = usLength;
    pucReadArray = pucReadArray;
}

#if(_DP_TX_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get Tx HDCP Aksv By User Defined Method
// Input Value  : ucSubaddr: Address of HDCP
//                ucLength: Length of HDCP
//                pucReadArray: HDCP data
// Output Value : None
//--------------------------------------------------
void UserInterfaceHdcpGetTxKeyAksvByUser(BYTE ucSubAddr, BYTE ucLength, BYTE *pucReadArray)
{
    ucSubAddr = ucSubAddr;
    ucLength = ucLength;
    pucReadArray = pucReadArray;
}

//--------------------------------------------------
// Description  : Get HDCP By User Defined Method
// Input Value  : usSubaddr: Address of HDCP
//                usLength: Length of HDCP
//                pucReadArray: HDCP data
// Output Value : None
//--------------------------------------------------
void UserInterfaceHdcpGetTxKeyByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    usSubAddr = usSubAddr;
    usLength = usLength;
    pucReadArray = pucReadArray;
}
#endif // End of #if(_DP_TX_SUPPORT == _ON)
#endif // End of #if(_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_USER)

#if((_HDCP_2_2_SUPPORT == _ON) && ((_RX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_USER) || (_TX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_USER)))
//--------------------------------------------------
// Description  : Get HDCP By User Defined Method
// Input Value  : usSubaddr: Address of HDCP
//                usLength: Length of HDCP
//                pucReadArray: HDCP data
// Output Value : None
//--------------------------------------------------
void UserInterfaceHdcp2GetCertrxByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    usSubAddr = usSubAddr;
    usLength = usLength;
    pucReadArray = pucReadArray;
}

//--------------------------------------------------
// Description  : Get HDCP By User Defined Method
// Input Value  : usSubaddr: Address of HDCP
//                usLength: Length of HDCP
//                pucReadArray: HDCP data
// Output Value : None
//--------------------------------------------------
void UserInterfaceHdcp2GetRSADkeyByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    usSubAddr = usSubAddr;
    usLength = usLength;
    pucReadArray = pucReadArray;
}

//--------------------------------------------------
// Description  : Get HDCP By User Defined Method
// Input Value  : usSubaddr: Address of HDCP
//                usLength: Length of HDCP
//                pucReadArray: HDCP data
// Output Value : None
//--------------------------------------------------
void UserInterfaceHdcp2GetRSARRModNByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    usSubAddr = usSubAddr;
    usLength = usLength;
    pucReadArray = pucReadArray;
}

//--------------------------------------------------
// Description  : Get HDCP By User Defined Method
// Input Value  : usSubaddr: Address of HDCP
//                usLength: Length of HDCP
//                pucReadArray: HDCP data
// Output Value : None
//--------------------------------------------------
void UserInterfaceHdcp2GetRSAKPrivByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    usSubAddr = usSubAddr;
    usLength = usLength;
    pucReadArray = pucReadArray;
}

//--------------------------------------------------
// Description  : Get HDCP By User Defined Method
// Input Value  : usSubaddr: Address of HDCP
//                usLength: Length of HDCP
//                pucReadArray: HDCP data
// Output Value : None
//--------------------------------------------------
void UserInterfaceHdcp2GetRSANpinvByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    usSubAddr = usSubAddr;
    usLength = usLength;
    pucReadArray = pucReadArray;
}

//--------------------------------------------------
// Description  : Get HDCP By User Defined Method
// Input Value  : usSubaddr: Address of HDCP
//                usLength: Length of HDCP
//                pucReadArray: HDCP data
// Output Value : None
//--------------------------------------------------
void UserInterfaceHdcp2GetLCKeyByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    usSubAddr = usSubAddr;
    usLength = usLength;
    pucReadArray = pucReadArray;
}

#if((_DP_HDCP_2_2_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Get HDCP2.2 TX KEY -- RRMODN
// Input Value  : usSubaddr: Address of HDCP
//                usLength: Length of HDCP
//                pucReadArray: HDCP data
// Output Value : None
//--------------------------------------------------
void UserInterfaceHdcp2GetDpTxRRMODNByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    usSubAddr = usSubAddr;
    usLength = usLength;
    pucReadArray = pucReadArray;
}

//--------------------------------------------------
// Description  : Get HDCP2.2 TX KEY -- RRMODN
// Input Value  : usSubaddr: Address of HDCP
//                usLength: Length of HDCP
//                pucReadArray: HDCP data
// Output Value : None
//--------------------------------------------------
void UserInterfaceHdcp2GetDpTxDcpLlcNByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    usSubAddr = usSubAddr;
    usLength = usLength;
    pucReadArray = pucReadArray;
}

//--------------------------------------------------
// Description  : Get HDCP2.2 TX KEY -- RRMODN
// Input Value  : usSubaddr: Address of HDCP
//                usLength: Length of HDCP
//                pucReadArray: HDCP data
// Output Value : None
//--------------------------------------------------
void UserInterfaceHdcp2GetDpTxEKeyByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    usSubAddr = usSubAddr;
    usLength = usLength;
    pucReadArray = pucReadArray;
}

//--------------------------------------------------
// Description  : Get HDCP2.2 TX KEY -- RRMODN
// Input Value  : usSubaddr: Address of HDCP
//                usLength: Length of HDCP
//                pucReadArray: HDCP data
// Output Value : None
//--------------------------------------------------
void UserInterfaceHdcp2GetDpTxNPinvByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    usSubAddr = usSubAddr;
    usLength = usLength;
    pucReadArray = pucReadArray;
}
#endif // End of #if((_DP_HDCP_2_2_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
#endif // End of #if((_HDCP_2_2_SUPPORT == _ON) && ((_RX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_USER) || (_TX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_USER)))

#endif // End of #if(_DIGITAL_PORT_SUPPORT == _ON)

#endif // End of #if(_OSD_TYPE == _REALTEK_2020_OSD)
