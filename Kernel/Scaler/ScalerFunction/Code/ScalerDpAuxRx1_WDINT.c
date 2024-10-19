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
// ID Code      : ScalerDpAuxRx1_WDINT.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"
#include "DpAuxRx1/ScalerDpAuxRx1.h"




//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_DP_AUX_RX1_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Input Dpcd Access Addr
// Input Value  : ulDpcdAddr
// Output Value : none
//--------------------------------------------------
void ScalerDpAuxRx1SetDpcdAccessAddr_WDINT(DWORD ulDpcdAddr)
{
#if(_HW_DP_AUX_RX_MAC_DPCD_ACCESS_TYPE == _DP_AUX_RX_MAC_DPCD_ACCESS_WAIT_BUSY)
    WORD usTimeout = 1000;

    // Set Dpcd Addr
    Scaler32SetDWord_WDINT(_REG_DP_AUX_RX1_DPCD_ADDR_INPUT_PORT, ulDpcdAddr);

    // Set Aux Rx Mac Access Busy to toggle Hw
    Scaler32SetBit_WDINT(_REG_DP_AUX_RX1_DPCD_ACCESS_CONTROL, ~(_BIT(2, 0)), _BIT2);

    while((Scaler32GetBit_WDINT(_REG_DP_AUX_RX1_DPCD_ACCESS_CONTROL, _BIT2) == _BIT2) && (--usTimeout))
    {
        ScalerMcuDelayDot2usPN();
    }
#else
    ScalerMcuDelayDot2usPN();

    // Set Dpcd Addr
    Scaler32SetDWord_WDINT(_REG_DP_AUX_RX1_DPCD_ADDR_INPUT_PORT, ulDpcdAddr);
#endif
}

//--------------------------------------------------
// Description  : Input Dpcd Access Data
// Input Value  : usDpcdData
// Output Value : none
//--------------------------------------------------
void ScalerDpAuxRx1SetDpcdAccessByteData_WDINT(BYTE ucDpcdData)
{
#if(_HW_DP_AUX_RX_MAC_DPCD_ACCESS_TYPE == _DP_AUX_RX_MAC_DPCD_ACCESS_WAIT_BUSY)
    // Backup For Avoid Interrupt Conflict
    g_stDpAuxRx1DpcdUpdateProtect_WDINT.usDpAuxRxNotDpcdBit = 0xFF00;
    g_stDpAuxRx1DpcdUpdateProtect_WDINT.usDpAuxRxDpcdBit = ucDpcdData;

    // Set Flag Avoid Interrupt
    SET_DP_AUX_RX1_DPCD_UPDATE_PROTECT_WDINT();
#endif

#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    // Set Dpcd Data Value = Original Data and Set _BITX
    g_stDpAuxRx1DpcdUpdateProtect_WDINT.usDpAuxRxDpcdData = ((ScalerDpAuxRx1GetDpcdAccessData_WDINT() & 0xFF00) | ucDpcdData);
#else
    // Set Dpcd Data Value
    g_stDpAuxRx1DpcdUpdateProtect_WDINT.usDpAuxRxDpcdData = ucDpcdData;
#endif

#if(_HW_DP_AUX_RX_MAC_DPCD_ACCESS_TYPE == _DP_AUX_RX_MAC_DPCD_ACCESS_WAIT_BUSY)
    WORD usTimeout = 1000;

#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    EnumDpAuxRxDpcdAccess enumDpAuxRxDpcdAccess = Scaler32GetBit_WDINT(_REG_DP_AUX_RX1_DPCD_ACCESS_CONTROL, _DP_AUX_RX_DPCD_ACCESS_ALL);

    // Avoid Hw Bug
    ScalerDpAuxRx1AccessSelect_WDINT(_DP_AUX_RX_DPCD_ACCESS_ALL);
#endif

    // Set Dpcd Data
    Scaler32SetDWord_WDINT(_REG_DP_AUX_RX1_DPCD_DATA_INPUT_PORT, g_stDpAuxRx1DpcdUpdateProtect_WDINT.usDpAuxRxDpcdData);

    // Set Aux Rx Mac Access Busy to toggle Hw
    Scaler32SetBit_WDINT(_REG_DP_AUX_RX1_DPCD_ACCESS_CONTROL, ~(_BIT(2, 0)), _BIT0);

    // Reset Backup
    CLR_DP_AUX_RX1_DPCD_UPDATE_PROTECT_WDINT();

    while((Scaler32GetBit_WDINT(_REG_DP_AUX_RX1_DPCD_ACCESS_CONTROL, _BIT0) == _BIT0) && (--usTimeout))
    {
        ScalerMcuDelayDot2usPN();
    }

#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    // Restore Original Setting
    ScalerDpAuxRx1AccessSelect_WDINT(enumDpAuxRxDpcdAccess);
#endif
#else
    ScalerMcuDelayDot2usPN();

    // Set Dpcd Data
    Scaler32SetDWord_WDINT(_REG_DP_AUX_RX1_DPCD_DATA_INPUT_PORT, g_stDpAuxRx1DpcdUpdateProtect_WDINT.usDpAuxRxDpcdData);
#endif
}

//--------------------------------------------------
// Description  : Input Dpcd Access Data
// Input Value  : usDpcdData
// Output Value : none
//--------------------------------------------------
void ScalerDpAuxRx1SetDpcdAccessBitData_WDINT(WORD usNotDpcdBit, WORD usDpcdBit)
{
#if(_HW_DP_AUX_RX_MAC_DPCD_ACCESS_TYPE == _DP_AUX_RX_MAC_DPCD_ACCESS_WAIT_BUSY)
    bit bAutoIncBackUp = (Scaler32GetBit_WDINT(_REG_DP_AUX_RX1_DPCD_ACCESS_CONTROL, _BIT3) == _BIT3);
#else
    bit bAutoIncBackUp = (Scaler32GetBit_WDINT(_REG_DP_AUX_RX1_DPCD_ADDR_INPUT_PORT, _BIT20) == _BIT20);
#endif

    if(bAutoIncBackUp == _TRUE)
    {
        // Disable Dpcd Auto Inc
        ScalerDpAuxRx1DpcdAutoIncEnable_WDINT(_DISABLE);
    }

    // Backup For Avoid Interrupt Conflict
    g_stDpAuxRx1DpcdUpdateProtect_WDINT.usDpAuxRxNotDpcdBit = usNotDpcdBit;
    g_stDpAuxRx1DpcdUpdateProtect_WDINT.usDpAuxRxDpcdBit = usDpcdBit;

    // Set Flag Avoid Interrupt
    SET_DP_AUX_RX1_DPCD_UPDATE_PROTECT_WDINT();

    // Set Dpcd Data Value = Original Data and Set _BITX
    g_stDpAuxRx1DpcdUpdateProtect_WDINT.usDpAuxRxDpcdData = ((ScalerDpAuxRx1GetDpcdAccessData_WDINT() & g_stDpAuxRx1DpcdUpdateProtect_WDINT.usDpAuxRxNotDpcdBit) | g_stDpAuxRx1DpcdUpdateProtect_WDINT.usDpAuxRxDpcdBit);

#if(_HW_DP_AUX_RX_MAC_DPCD_ACCESS_TYPE == _DP_AUX_RX_MAC_DPCD_ACCESS_WAIT_BUSY)
    WORD usTimeout = 1000;

#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    EnumDpAuxRxDpcdAccess enumDpAuxRxDpcdAccess = Scaler32GetBit_WDINT(_REG_DP_AUX_RX1_DPCD_ACCESS_CONTROL, _DP_AUX_RX_DPCD_ACCESS_ALL);

    // Avoid Hw Bug
    ScalerDpAuxRx1AccessSelect_WDINT(_DP_AUX_RX_DPCD_ACCESS_ALL);
#endif

    // Set Dpcd Data
    Scaler32SetDWord_WDINT(_REG_DP_AUX_RX1_DPCD_DATA_INPUT_PORT, g_stDpAuxRx1DpcdUpdateProtect_WDINT.usDpAuxRxDpcdData);

    // Set Aux Rx Mac Access Busy to toggle Hw
    Scaler32SetBit_WDINT(_REG_DP_AUX_RX1_DPCD_ACCESS_CONTROL, ~(_BIT(2, 0)), _BIT0);

    // Reset Backup
    CLR_DP_AUX_RX1_DPCD_UPDATE_PROTECT_WDINT();

    while((Scaler32GetBit_WDINT(_REG_DP_AUX_RX1_DPCD_ACCESS_CONTROL, _BIT0) == _BIT0) && (--usTimeout))
    {
        ScalerMcuDelayDot2usPN();
    }

#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    // Restore Original Setting
    ScalerDpAuxRx1AccessSelect_WDINT(enumDpAuxRxDpcdAccess);
#endif
#else
    ScalerMcuDelayDot2usPN();

    // Set Dpcd Data
    Scaler32SetDWord_WDINT(_REG_DP_AUX_RX1_DPCD_DATA_INPUT_PORT, g_stDpAuxRx1DpcdUpdateProtect_WDINT.usDpAuxRxDpcdData);

    // Reset Backup
    CLR_DP_AUX_RX1_DPCD_UPDATE_PROTECT_WDINT();
#endif

    if(bAutoIncBackUp == _TRUE)
    {
        // Enable Dpcd Auto Inc
        ScalerDpAuxRx1DpcdAutoIncEnable_WDINT(_ENABLE);
    }
}

//--------------------------------------------------
// Description  : Get Dpcd Access Data
// Input Value  : none
// Output Value : usDpcdData
//--------------------------------------------------
WORD ScalerDpAuxRx1GetDpcdAccessData_WDINT(void)
{
    ScalerMcuDelayDot2usPN();

    // Get Dpcd Data
    return Scaler32GetWord_WDINT(_REG_DP_AUX_RX1_DPCD_DATA_OUTPUT_PORT, 0x00);
}

//--------------------------------------------------
// Description  : DP Aux Auto Inc Enable
// Input Value  : bEnable
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx1DpcdAutoIncEnable_WDINT(bit bEnable)
{
#if(_HW_DP_AUX_RX_MAC_DPCD_ACCESS_TYPE == _DP_AUX_RX_MAC_DPCD_ACCESS_WAIT_BUSY)
    Scaler32SetBit_WDINT(_REG_DP_AUX_RX1_DPCD_ACCESS_CONTROL, ~_BIT3, (bEnable << 3));
#else
    Scaler32SetBit_WDINT(_REG_DP_AUX_RX1_DPCD_ADDR_INPUT_PORT, ~_BIT20, (bEnable << 20));
#endif
}

//--------------------------------------------------
// Description  : Get DPCD Table Information in WDINT
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
// Output Value : DPCD Information
//--------------------------------------------------
BYTE ScalerDpAuxRx1GetDpcdInfo_WDINT(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL)
{
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    EnumDpAuxRxModeStatus enumDpAuxRxModeStatus = GET_DP_AUX_RX1_MODE_EXINT();

    // Avoid Tx & FW conflict
    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        SET_DP_AUX_RX1_MANUAL_MODE_EXINT();
    }
#endif

    // Set Dpcd Addr
    ScalerDpAuxRx1SetDpcdAccessAddr_WDINT(TO_DWORD(0x00, ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL));

#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    // Restore to Original Mode
    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        SET_DP_AUX_RX1_AUTO_MODE_EXINT();
    }
#endif

    return (BYTE)(ScalerDpAuxRx1GetDpcdAccessData_WDINT() & _BIT(7, 0));
}

//--------------------------------------------------
// Description  : Get DPCD Table Information in WDINT
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
// Output Value : DPCD Information
//--------------------------------------------------
BYTE ScalerDpAuxRx1GetDpcdBitInfo_WDINT(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdBit)
{
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    EnumDpAuxRxModeStatus enumDpAuxRxModeStatus = GET_DP_AUX_RX1_MODE_EXINT();

    // Avoid Tx & FW conflict
    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        SET_DP_AUX_RX1_MANUAL_MODE_EXINT();
    }
#endif

    // Set Dpcd Addr
    ScalerDpAuxRx1SetDpcdAccessAddr_WDINT(TO_DWORD(0x00, ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL));

#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    // Restore to Original Mode
    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        SET_DP_AUX_RX1_AUTO_MODE_EXINT();
    }
#endif

    return (BYTE)(ScalerDpAuxRx1GetDpcdAccessData_WDINT() & ucDpcdBit);
}

//--------------------------------------------------
// Description  : Set DPCD Table Information in WDINT
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
//                ucDpcdValue --> DPCD Value
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx1SetDpcdValue_WDINT(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue)
{
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    EnumDpAuxRxModeStatus enumDpAuxRxModeStatus = GET_DP_AUX_RX1_MODE_EXINT();

    // Avoid Tx & FW conflict
    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        SET_DP_AUX_RX1_MANUAL_MODE_EXINT();
    }
#endif

    // Set Dpcd Addr
    ScalerDpAuxRx1SetDpcdAccessAddr_WDINT(TO_DWORD(0x00, ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL));

#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    // Set Dpcd Access Data
    ScalerDpAuxRx1AccessSelect_WDINT(_DP_AUX_RX_DPCD_ACCESS_DATA);
#endif

    // Set Dpcd Data
    ScalerDpAuxRx1SetDpcdAccessByteData_WDINT(ucDpcdValue);

#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    // Restore to Original Mode
    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        SET_DP_AUX_RX1_AUTO_MODE_EXINT();
    }
#endif
}

//--------------------------------------------------
// Description  : Set DPCD Table Information in WDINT
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
//                ucDpcdValue --> DPCD Value
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx1SetDpcdWriteValue_WDINT(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue)
{
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    ScalerDpAuxRx1SetDpcdValue_WDINT(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);
#else
    EnumDpAuxRxModeStatus enumDpAuxRxModeStatus = GET_DP_AUX_RX1_MODE_EXINT();

    // Set Manual Mode For R/W Dpcd
    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        SET_DP_AUX_RX1_MANUAL_MODE_EXINT();
    }

    // Set Dpcd Addr
    ScalerDpAuxRx1SetDpcdAccessAddr_WDINT(TO_DWORD(0x00, ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL));

    // Set Dpcd Data
    ScalerDpAuxRx1SetDpcdAccessByteData_WDINT(ucDpcdValue);

    // Restore to Original Mode
    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        SET_DP_AUX_RX1_AUTO_MODE_EXINT();
    }
#endif
}

//--------------------------------------------------
// Description  : Set DPCD Table Information in WDINT
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
//                ucDpcdValue --> DPCD Value
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx1SetDpcdWrite1ClearValue_WDINT(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue)
{
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    ScalerDpAuxRx1SetDpcdValue_WDINT(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);
#else
    EnumDpAuxRxModeStatus enumDpAuxRxModeStatus = GET_DP_AUX_RX1_MODE_EXINT();

    // Set Auto Mode For W1C Dpcd
    if(enumDpAuxRxModeStatus == _DP_RX_AUX_MANUAL_MODE)
    {
        SET_DP_AUX_RX1_AUTO_MODE_EXINT();
    }

    // Set Dpcd Addr
    ScalerDpAuxRx1SetDpcdAccessAddr_WDINT(TO_DWORD(0x00, ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL));

    // Set Dpcd Data
    ScalerDpAuxRx1SetDpcdAccessByteData_WDINT(ucDpcdValue);

    // Restore to Original Mode
    if(enumDpAuxRxModeStatus == _DP_RX_AUX_MANUAL_MODE)
    {
        SET_DP_AUX_RX1_MANUAL_MODE_EXINT();
    }
#endif
}

//--------------------------------------------------
// Description  : Set DPCD Table Information in WDINT
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
//                ucDpcdValue --> DPCD Value
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx1SetDpcdBitValue_WDINT(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit)
{
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    EnumDpAuxRxModeStatus enumDpAuxRxModeStatus = GET_DP_AUX_RX1_MODE_EXINT();

    // Avoid Tx & FW conflict
    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        SET_DP_AUX_RX1_MANUAL_MODE_EXINT();
    }
#endif

    // Set Dpcd Addr
    ScalerDpAuxRx1SetDpcdAccessAddr_WDINT(TO_DWORD(0x00, ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL));

#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    // Set Dpcd Access Data
    ScalerDpAuxRx1AccessSelect_WDINT(_DP_AUX_RX_DPCD_ACCESS_DATA);
#endif

    // Set Dpcd Data Value = Original Data and Set _BITX
    ScalerDpAuxRx1SetDpcdAccessBitData_WDINT((WORD)ulNotDpcdBit, ucDpcdBit);

#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    // Restore to Original Mode
    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        SET_DP_AUX_RX1_AUTO_MODE_EXINT();
    }
#endif
}

//--------------------------------------------------
// Description  : Set DPCD Table Information in WDINT
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
//                ucDpcdValue --> DPCD Value
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx1SetDpcdBitWriteValue_WDINT(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit)
{
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    ScalerDpAuxRx1SetDpcdBitValue_WDINT(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);
#else
    EnumDpAuxRxModeStatus enumDpAuxRxModeStatus = GET_DP_AUX_RX1_MODE_EXINT();

    // Set Manual Mode For R/W Dpcd
    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        SET_DP_AUX_RX1_MANUAL_MODE_EXINT();
    }

    // Set Dpcd Addr
    ScalerDpAuxRx1SetDpcdAccessAddr_WDINT(TO_DWORD(0x00, ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL));

    // Set Dpcd Data Value = Original Data and Set _BITX
    ScalerDpAuxRx1SetDpcdAccessBitData_WDINT((WORD)ulNotDpcdBit, ucDpcdBit);

    // Restore to Original Mode
    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        SET_DP_AUX_RX1_AUTO_MODE_EXINT();
    }
#endif
}

//--------------------------------------------------
// Description  : Set DPCD Table Information in WDINT
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
//                ucDpcdValue --> DPCD Value
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx1SetDpcdBitWrite1ClearValue_WDINT(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit)
{
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    ScalerDpAuxRx1SetDpcdBitValue_WDINT(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);
#else
    EnumDpAuxRxModeStatus enumDpAuxRxModeStatus = GET_DP_AUX_RX1_MODE_EXINT();

    // Set Auto Mode For W1C Dpcd
    if(enumDpAuxRxModeStatus == _DP_RX_AUX_MANUAL_MODE)
    {
        SET_DP_AUX_RX1_AUTO_MODE_EXINT();
    }

    // Set Dpcd Addr
    ScalerDpAuxRx1SetDpcdAccessAddr_WDINT(TO_DWORD(0x00, ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL));

    // Set Dpcd Data Value = Original Data and Set _BITX
    ScalerDpAuxRx1SetDpcdAccessBitData_WDINT((WORD)ulNotDpcdBit, ucDpcdBit);

    // Restore to Original Mode
    if(enumDpAuxRxModeStatus == _DP_RX_AUX_MANUAL_MODE)
    {
        SET_DP_AUX_RX1_MANUAL_MODE_EXINT();
    }
#endif
}

//--------------------------------------------------
// Description  : Set DPCD Table Information in WDINT, Use For Dpcd Need Manual Mapping
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
//                ucDpcdValue --> DPCD Value
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx1SetDpcdMirrorValue_WDINT(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue)
{
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    DWORD ulDpcdAddrMirror = ScalerDpAuxRxDpcdGetMirrorAddr_WDINT((ucDpcdAccessPortH & 0x0F), ucDpcdAccessPortM, ucDpcdAccessPortL);
    BYTE ucDpcdAddrMirrorH = (ulDpcdAddrMirror >> 16) & 0x0F;
    BYTE ucDpcdAddrMirrorM = (ulDpcdAddrMirror >> 8) & 0xFF;
    BYTE ucDpcdAddrMirrorL = ulDpcdAddrMirror & 0xFF;
    EnumDpAuxRxModeStatus enumDpAuxRxModeStatus = GET_DP_AUX_RX1_MODE_EXINT();

    // Set Manual Mode to Protect Mirror Addr Mismatch
    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        SET_DP_AUX_RX1_MANUAL_MODE_EXINT();
    }

    // Set Target Dpcd Addr
    ScalerDpAuxRx1SetDpcdValue_WDINT(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);

    if(ulDpcdAddrMirror != 0xFFFFFFFF)
    {
        // Set Mirror Dpcd Addr
        ScalerDpAuxRx1SetDpcdValue_WDINT(ucDpcdAddrMirrorH, ucDpcdAddrMirrorM, ucDpcdAddrMirrorL, ucDpcdValue);
    }

    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        SET_DP_AUX_RX1_AUTO_MODE_EXINT();
    }
#else
    ScalerDpAuxRx1SetDpcdValue_WDINT(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);
#endif
}

//--------------------------------------------------
// Description  : Set DPCD Table Information in WDINT, Use For Dpcd Need Manual Mapping
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
//                ucDpcdValue --> DPCD Value
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx1SetDpcdMirrorWriteValue_WDINT(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue)
{
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    ScalerDpAuxRx1SetDpcdMirrorValue_WDINT(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);
#else
    ScalerDpAuxRx1SetDpcdWriteValue_WDINT(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);
#endif
}

//--------------------------------------------------
// Description  : Set DPCD Table Information in WDINT, Use For Dpcd Need Manual Mapping
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
//                ucDpcdValue --> DPCD Value
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx1SetDpcdMirrorWrite1ClearValue_WDINT(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue)
{
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    ScalerDpAuxRx1SetDpcdMirrorValue_WDINT(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);
#else
    ScalerDpAuxRx1SetDpcdWrite1ClearValue_WDINT(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);
#endif
}

//--------------------------------------------------
// Description  : Set DPCD Table Information in WDINT, Use For Dpcd Need Manual Mapping
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
//                ucDpcdValue --> DPCD Value
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx1SetDpcdMirrorBitValue_WDINT(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit)
{
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    DWORD ulDpcdAddrMirror = ScalerDpAuxRxDpcdGetMirrorAddr_WDINT((ucDpcdAccessPortH & 0x0F), ucDpcdAccessPortM, ucDpcdAccessPortL);
    BYTE ucDpcdAddrMirrorH = (ulDpcdAddrMirror >> 16) & 0x0F;
    BYTE ucDpcdAddrMirrorM = (ulDpcdAddrMirror >> 8) & 0xFF;
    BYTE ucDpcdAddrMirrorL = ulDpcdAddrMirror & 0xFF;
    EnumDpAuxRxModeStatus enumDpAuxRxModeStatus = GET_DP_AUX_RX1_MODE_EXINT();

    // Set Manual Mode to Protect Mirror Addr Mismatch
    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        SET_DP_AUX_RX1_MANUAL_MODE_EXINT();
    }

    // Set Target Dpcd Addr
    ScalerDpAuxRx1SetDpcdBitValue_WDINT(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);

    if(ulDpcdAddrMirror != 0xFFFFFFFF)
    {
        // Set Mirror Dpcd Addr
        ScalerDpAuxRx1SetDpcdBitValue_WDINT(ucDpcdAddrMirrorH, ucDpcdAddrMirrorM, ucDpcdAddrMirrorL, ulNotDpcdBit, ucDpcdBit);
    }

    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        SET_DP_AUX_RX1_AUTO_MODE_EXINT();
    }
#else
    ScalerDpAuxRx1SetDpcdBitValue_WDINT(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);
#endif
}

//--------------------------------------------------
// Description  : Set DPCD Table Information in WDINT, Use For Dpcd Need Manual Mapping
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
//                ucDpcdValue --> DPCD Value
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx1SetDpcdMirrorBitWriteValue_WDINT(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit)
{
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    ScalerDpAuxRx1SetDpcdMirrorBitValue_WDINT(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);
#else
    ScalerDpAuxRx1SetDpcdBitWriteValue_WDINT(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);
#endif
}

//--------------------------------------------------
// Description  : Set DPCD Table Information in WDINT, Use For Dpcd Need Manual Mapping
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
//                ucDpcdValue --> DPCD Value
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx1SetDpcdMirrorBitWrite1ClearValue_WDINT(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit)
{
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    ScalerDpAuxRx1SetDpcdMirrorBitValue_WDINT(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);
#else
    ScalerDpAuxRx1SetDpcdBitWrite1ClearValue_WDINT(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);
#endif
}

//--------------------------------------------------
// Description  : DP Dpcd Port Access Backup
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx1DpcdPortAccessBackup_WDINT(void)
{
#if(_HW_DP_AUX_RX_MAC_DPCD_ACCESS_TYPE == _DP_AUX_RX_MAC_DPCD_ACCESS_WAIT_BUSY)
    WORD usTimeout = 1000;

    while((Scaler32GetBit_WDINT(_REG_DP_AUX_RX1_DPCD_ACCESS_CONTROL, _BIT(2, 0)) != 0x00) && (--usTimeout))
    {
        ScalerMcuDelayDot2usPN();
    }

    if(Scaler32GetBit_WDINT(_REG_DP_AUX_RX1_DPCD_ACCESS_CONTROL, _BIT3) == _BIT3)
    {
        // Backup Addr
        g_ulDpAuxRx1Backup_WDINT = Scaler32GetDWord_WDINT(_REG_DP_AUX_RX1_DPCD_ADDR_OUTPUT_PORT);
    }
    else
#endif
    {
        // Backup Addr, Backup Auto Inc when _HW_DP_AUX_RX_MAC_DPCD_ACCESS_TYPE = _DP_AUX_RX_MAC_DPCD_ACCESS_NORMAL
        g_ulDpAuxRx1Backup_WDINT = Scaler32GetDWord_WDINT(_REG_DP_AUX_RX1_DPCD_ADDR_INPUT_PORT);
    }

#if(_HW_DP_AUX_RX_MAC_DPCD_ACCESS_TYPE == _DP_AUX_RX_MAC_DPCD_ACCESS_WAIT_BUSY)
    // Backup Auto Inc / Config & Data Sel
    g_ucDpAuxRx1AccessBackup_WDINT = Scaler32GetByte_WDINT(_REG_DP_AUX_RX1_DPCD_ACCESS_CONTROL, 0x00) & (_BIT5 | _BIT4 | _BIT3);
#endif

    ScalerDpAuxRx1DpcdAutoIncEnable_WDINT(_DISABLE);
}

//--------------------------------------------------
// Description  : DP Dpcd Port Access Backup Restore
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx1DpcdPortAccessBackupRestore_WDINT(void)
{
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    EnumDpAuxRxModeStatus enumDpAuxRxModeStatus = GET_DP_AUX_RX1_MODE_EXINT();

    // Avoid Tx & FW conflict
    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        SET_DP_AUX_RX1_MANUAL_MODE_EXINT();
    }
#endif

    // Restore Addr, Restore Auto Inc when _HW_DP_AUX_RX_MAC_DPCD_ACCESS_TYPE = _DP_AUX_RX_MAC_DPCD_ACCESS_NORMAL
    ScalerDpAuxRx1SetDpcdAccessAddr_WDINT(g_ulDpAuxRx1Backup_WDINT);

    // If Main Loop is Set Dpcd Bit
    if(GET_DP_AUX_RX1_DPCD_UPDATE_PROTECT() == _TRUE)
    {
        // Set Dpcd Data Value = Original Data and Set _BITX
        g_stDpAuxRx1DpcdUpdateProtect.usDpAuxRxDpcdData = ((ScalerDpAuxRx1GetDpcdAccessData_WDINT() & g_stDpAuxRx1DpcdUpdateProtect.usDpAuxRxNotDpcdBit) | g_stDpAuxRx1DpcdUpdateProtect.usDpAuxRxDpcdBit);

        // Set Dpcd Data
        Scaler32SetDWord_WDINT(_REG_DP_AUX_RX1_DPCD_DATA_INPUT_PORT, g_stDpAuxRx1DpcdUpdateProtect.usDpAuxRxDpcdData);
    }

#if(_HW_DP_AUX_RX_MAC_DPCD_ACCESS_TYPE == _DP_AUX_RX_MAC_DPCD_ACCESS_WAIT_BUSY)
    // Restore Auto Inc / Config & Data Sel
    Scaler32SetDWord_WDINT(_REG_DP_AUX_RX1_DPCD_ACCESS_CONTROL, g_ucDpAuxRx1AccessBackup_WDINT);
#endif

    ScalerMcuDelayDot2usPN();

#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    // Restore to Original Mode
    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        SET_DP_AUX_RX1_AUTO_MODE_EXINT();
    }
#endif
}

//--------------------------------------------------
// Description  : Dp IRQ Assert Proc in WDINT
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx1HpdIrqAssert_WDINT(void)
{
#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && ((_PORT_CTRL_EMBEDDED_SUPPORT == _ON) || (_PORT_CTRL_TCPM_SUPPORT == _ON)))

    EnumInputPort enumInputPort = ScalerDpAuxRxRxDxMapping_EXINT0(_RX1);
    EnumTypeCPcbPort enumTypeCPcbPort = ScalerTypeCDxConvertToPcbPort_EXINT0(enumInputPort);

#if(_PORT_CTRL_EMBEDDED_SUPPORT == _ON)
    if(ScalerTypeCPcbxTypeCxMapping_EXINT0(enumTypeCPcbPort) != _EMB_TYPE_C_NOT_EXIST)
    {
        if(ScalerDpRxGetHotPlugStatus_EXINT0(enumInputPort) == _HIGH)
        {
            ScalerTypeCPdDpCTSForceHpdIrq_EXINT0(enumInputPort);
        }
    }
    else
#elif(_PORT_CTRL_TCPM_SUPPORT == _ON)
    if(ScalerTypeCRxGetPortCtrlType_EXINT0(enumInputPort) == _TYPE_C_PORT_CTRL_TCPM)
    {
        if(ScalerDpRxGetHotPlugStatus_EXINT0(enumInputPort) == _HIGH)
        {
            ScalerTypeCTcpmPdPushHpd_EXINT0(enumTypeCPcbPort, _PD_HPD_IRQ, 2);
        }
    }
    else
#endif
#endif
    {
        if(PCB_D1_HOTPLUG_DETECT() == _D1_HOT_PLUG_HIGH)
        {
#if(_DP_IRQ_HPD_MODE == _DP_IRQ_HPD_T2_MODE)
            SET_DP_AUX_RX1_HPD_IRQ_ASSERT_T2_EVENT();
#else
            EnumDpAuxRxModeStatus enumDpAuxRxModeStatus = GET_DP_AUX_RX1_MODE_EXINT();

#if(_DP_TX_SUPPORT == _ON)
            // Disable IRQs that take too long
            BYTE ucBackUp2 = ScalerGetBit_EXINT(PBB_72_HPD_IRQ_EN, _BIT6);
            ScalerSetBit_EXINT(PBB_72_HPD_IRQ_EN, ~_BIT6, 0x00);
#endif

            if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
            {
                SET_DP_AUX_RX1_MANUAL_MODE_EXINT();
            }

            PCB_D1_HOTPLUG(_D1_HOT_PLUG_LOW);

            // Default = 750us
            switch(GET_DP_IRQ_TIME_10US())
            {
                case 55:
                    DELAY_XUS_EXINT(500);
                    break;

                case 60:
                    DELAY_XUS_EXINT(546);
                    break;

                case 65:
                    DELAY_XUS_EXINT(588);
                    break;

                case 70:
                    DELAY_XUS_EXINT(634);
                    break;

                case 75:
                default:
                    DELAY_XUS_EXINT(682);
                    break;

                case 80:
                    DELAY_XUS_EXINT(728);
                    break;

                case 85:
                    DELAY_XUS_EXINT(768);
                    break;

                case 90:
                    DELAY_XUS_EXINT(816);
                    break;

                case 95:
                    DELAY_XUS_EXINT(862);
                    break;
            }

            PCB_D1_HOTPLUG(_D1_HOT_PLUG_HIGH);

            if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
            {
                SET_DP_AUX_RX1_AUTO_MODE_EXINT();
            }

#if(_DP_TX_SUPPORT == _ON)
            ScalerSetBit_EXINT(PBB_72_HPD_IRQ_EN, ~_BIT6, ucBackUp2);
#endif
#endif
        }
    }
}

//--------------------------------------------------
// Description  : DPCD Link Status Field Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx1DpcdLinkStatusReset_WDINT(EnumDpResetStatus enumDpResetStatus)
{
    EnumInputPort enumInputPort = ScalerDpAuxRxRxDxMapping_EXINT0(_RX1);
    EnumDpAuxRxModeStatus enumDpAuxRxModeStatus = ScalerDpAuxRxGetAuxModeStatus_WDINT(enumInputPort);

    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        SET_DP_AUX_RX1_MANUAL_MODE_EXINT();
    }

    if(enumDpResetStatus == _DP_DPCD_LINK_STATUS_INITIAL)
    {
        // Set DPCD 00600h to 0x01
        ScalerDpAuxRx1SetDpcdBitWriteValue_WDINT(0x00, 0x06, 0x00, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
    }

    ScalerDpAuxRx1SetDpcdMirrorValue_WDINT(0x00, 0x02, 0x02, 0x00);
    ScalerDpAuxRx1SetDpcdMirrorValue_WDINT(0x00, 0x02, 0x03, 0x00);
    ScalerDpAuxRx1SetDpcdMirrorValue_WDINT(0x00, 0x02, 0x04, 0x80);
    ScalerDpAuxRx1SetDpcdWrite1ClearValue_WDINT(0x00, 0x20, 0x05, (ScalerDpAuxRx1GetDpcdInfo_WDINT(0x00, 0x20, 0x05) | _BIT1));
    ScalerDpAuxRx1SetDpcdMirrorValue_WDINT(0x00, 0x02, 0x05, 0x00);
    ScalerDpAuxRx1SetDpcdValue_WDINT(0x00, 0x02, 0x06, 0x00);
    ScalerDpAuxRx1SetDpcdValue_WDINT(0x00, 0x02, 0x07, 0x00);

    SET_DP_AUX_RX1_LINK_TRAINING_STATUS(_DP_LINK_TRAINING_NONE);

    CLR_DP_AUX_RX1_BACKUP_PD_LINK_STATUS_FLG();

#if(_DP_RX_FEC_SUPPORT == _ON)
    ScalerDpMacDphyRxFecDecode_EXINT0(enumInputPort, _DISABLE);

    if((ScalerDpAuxRx1GetDpcdBitInfo_WDINT(0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) == _BIT1) ||
       (ScalerDpAuxRx1GetDpcdBitInfo_WDINT(0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT0)))
    {
        // Reset FEC Ready
        ScalerDpAuxRx1SetDpcdWriteValue_WDINT(0x00, 0x01, 0x20, 0x00);
        ScalerDpMacDphyRxFecInitial_WDINT(enumInputPort);
    }
#endif

#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
    if(ScalerDpAuxRx1GetDpcdBitInfo_WDINT(0x00, 0x01, 0x16, (_BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT1 | _BIT0))
    {
        ScalerDpAuxRx1SetDpcdBitWrite1ClearValue_WDINT(0x00, 0x20, 0x0B, ~_BIT2, _BIT2);
    }

    ScalerDpMacDphyRxAuxlessAlpmEnable_WDINT(enumInputPort, _DISABLE);
#endif

#if(_DP_MST_SUPPORT == _ON)

    if(ScalerDpAuxRx1GetDpcdBitInfo_WDINT(0x00, 0x00, 0x21, _BIT0) == _BIT0)
    {
        ScalerDpAuxRx1SetDpcdWrite1ClearValue_WDINT(0x00, 0x02, 0xC0, (ScalerDpAuxRx1GetDpcdInfo_WDINT(0x00, 0x02, 0xC0) & ~_BIT1));
    }

#endif

    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        ScalerDpAuxRxSetAutoMode_WDINT(enumInputPort);
    }
}

#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP Aux Mac Access Select For New Mac
// Input Value  : enumInputPort, enumDpAuxRxDpcdAccess
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx1AccessSelect_WDINT(EnumDpAuxRxDpcdAccess enumDpAuxRxDpcdAccess)
{
#if(_HW_DP_AUX_RX_MAC_DPCD_ACCESS_TYPE == _DP_AUX_RX_MAC_DPCD_ACCESS_WAIT_BUSY)
    Scaler32SetBit_WDINT(PB19006_68_AUX_DPCD_ACCESS_CONTROL, ~(_BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), enumDpAuxRxDpcdAccess);
#else
    Scaler32SetBit_WDINT(_REG_DP_AUX_RX1_DPCD_ADDR_INPUT_PORT, ~(_BIT(23, 22)), enumDpAuxRxDpcdAccess);
#endif
}
#endif
#endif

