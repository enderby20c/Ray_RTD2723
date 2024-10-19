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
// ID Code      : ScalerDpAuxRx_WDINT.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"
#include "DpAuxRx/ScalerDpAuxRx.h"




#if(_DP_SUPPORT == _ON)
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
// Description  : DP Port Dx mapping to Rx
// Input Value  : Input Port
// Output Value : Rx1 or Rx2 or Rx3
//--------------------------------------------------
EnumRx ScalerDpAuxRxDxRxMapping_WDINT(EnumInputPort enumInputPort)
{
    EnumRx enumRx = _RX_MAP_NONE;

#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
    if(enumInputPort == _D9_INPUT_PORT)
    {
        enumInputPort = GET_DP_MST_RX_PXP_INPUT_PORT();
    }
#endif

    switch(enumInputPort)
    {
#if(_D0_DP_SUPPORT == _ON)
        case _D0_INPUT_PORT:
            enumRx = _HW_D0_DP_AUX_RX_MAPPING;
            break;
#endif

#if(_D1_DP_SUPPORT == _ON)
        case _D1_INPUT_PORT:
            enumRx = _HW_D1_DP_AUX_RX_MAPPING;
            break;
#endif

#if(_D2_DP_SUPPORT == _ON)
        case _D2_INPUT_PORT:
            enumRx = _HW_D2_DP_AUX_RX_MAPPING;
            break;
#endif

#if(_D7_DP_SUPPORT == _ON)
        case _D7_INPUT_PORT:
            enumRx = _HW_D7_DP_AUX_RX_MAPPING;
            break;
#endif

#if(_D8_DP_SUPPORT == _ON)
        case _D8_INPUT_PORT:
            enumRx = _HW_D8_DP_AUX_RX_MAPPING;
            break;
#endif
        default:

            break;
    }

    return enumRx;
}

//--------------------------------------------------
// Description  : Get DP Aux Mode
// Input Value  : None
// Output Value : DP Aux Mode
//--------------------------------------------------
EnumDpAuxRxModeStatus ScalerDpAuxRxGetAuxModeStatus_WDINT(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping_WDINT(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            return GET_DP_AUX_RX0_MODE_EXINT();
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            return GET_DP_AUX_RX1_MODE_EXINT();
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            return GET_DP_AUX_RX2_MODE_EXINT();
#endif
        default:

            return _DP_RX_AUX_AUTO_MODE;
    }
}

//--------------------------------------------------
// Description  : Get DPCD Table Information in WDINT
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
// Output Value : DPCD Information
//--------------------------------------------------
BYTE ScalerDpAuxRxGetDpcdInfo_WDINT(EnumInputPort enumInputPort, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL)
{
    switch(ScalerDpAuxRxDxRxMapping_WDINT(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            return ScalerDpAuxRx0GetDpcdInfo_WDINT(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL);
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            return ScalerDpAuxRx1GetDpcdInfo_WDINT(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL);
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            return ScalerDpAuxRx2GetDpcdInfo_WDINT(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL);
#endif
        default:

            return 0x00;
    }
}

//--------------------------------------------------
// Description  : Get DPCD Table Information in WDINT
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
// Output Value : DPCD Information
//--------------------------------------------------
BYTE ScalerDpAuxRxGetDpcdBitInfo_WDINT(EnumInputPort enumInputPort, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdBit)
{
    switch(ScalerDpAuxRxDxRxMapping_WDINT(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            return ScalerDpAuxRx0GetDpcdBitInfo_WDINT(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdBit);
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            return ScalerDpAuxRx1GetDpcdBitInfo_WDINT(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdBit);
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            return ScalerDpAuxRx2GetDpcdBitInfo_WDINT(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdBit);
#endif

        default:

            return 0x00;
    }
}

//--------------------------------------------------
// Description  : Set DPCD Table Information in WDINT
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
//                ucDpcdValue --> DPCD Value
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxSetDpcdValue_WDINT(EnumInputPort enumInputPort, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue)
{
    switch(ScalerDpAuxRxDxRxMapping_WDINT(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpAuxRx0SetDpcdValue_WDINT(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpAuxRx1SetDpcdValue_WDINT(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpAuxRx2SetDpcdValue_WDINT(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);

            break;
#endif

#if((_DP_AUX_RX0_SUPPORT == _ON) && (_DP_AUX_RX1_SUPPORT == _ON))
        case _RX7:

            ScalerDpAuxRx0SetDpcdValue_WDINT(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);
            ScalerDpAuxRx1SetDpcdValue_WDINT(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);

            break;
#endif

#if((_DP_AUX_RX1_SUPPORT == _ON) && (_DP_AUX_RX2_SUPPORT == _ON))
        case _RX8:

            ScalerDpAuxRx1SetDpcdValue_WDINT(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);
            ScalerDpAuxRx2SetDpcdValue_WDINT(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Set DPCD Table Information in WDINT
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
//                ucDpcdValue --> DPCD Value
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxSetDpcdBitValue_WDINT(EnumInputPort enumInputPort, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit)
{
    switch(ScalerDpAuxRxDxRxMapping_WDINT(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpAuxRx0SetDpcdBitValue_WDINT(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpAuxRx1SetDpcdBitValue_WDINT(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpAuxRx2SetDpcdBitValue_WDINT(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Set DPCD Table Information in WDINT, Use For Dpcd Need Manual Mapping
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
//                ucDpcdValue --> DPCD Value
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxSetDpcdMirrorValue_WDINT(EnumInputPort enumInputPort, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue)
{
    switch(ScalerDpAuxRxDxRxMapping_WDINT(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpAuxRx0SetDpcdMirrorValue_WDINT(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpAuxRx1SetDpcdMirrorValue_WDINT(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpAuxRx2SetDpcdMirrorValue_WDINT(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);

            break;
#endif

#if((_DP_AUX_RX0_SUPPORT == _ON) && (_DP_AUX_RX1_SUPPORT == _ON))
        case _RX7:

            ScalerDpAuxRx0SetDpcdMirrorValue_WDINT(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);
            ScalerDpAuxRx1SetDpcdMirrorValue_WDINT(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);

            break;
#endif

#if((_DP_AUX_RX1_SUPPORT == _ON) && (_DP_AUX_RX2_SUPPORT == _ON))
        case _RX8:

            ScalerDpAuxRx1SetDpcdMirrorValue_WDINT(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);
            ScalerDpAuxRx2SetDpcdMirrorValue_WDINT(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Set DPCD Table Information in WDINT, Use For Dpcd Need Manual Mapping
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
//                ucDpcdValue --> DPCD Value
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxSetDpcdMirrorBitValue_WDINT(EnumInputPort enumInputPort, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit)
{
    switch(ScalerDpAuxRxDxRxMapping_WDINT(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpAuxRx0SetDpcdMirrorBitValue_WDINT(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpAuxRx1SetDpcdMirrorBitValue_WDINT(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpAuxRx2SetDpcdMirrorBitValue_WDINT(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);

            break;
#endif

#if((_DP_AUX_RX0_SUPPORT == _ON) && (_DP_AUX_RX1_SUPPORT == _ON))
        case _RX7:

            ScalerDpAuxRx0SetDpcdMirrorBitValue_WDINT(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);
            ScalerDpAuxRx1SetDpcdMirrorBitValue_WDINT(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);

            break;
#endif

#if((_DP_AUX_RX1_SUPPORT == _ON) && (_DP_AUX_RX2_SUPPORT == _ON))
        case _RX8:

            ScalerDpAuxRx1SetDpcdMirrorBitValue_WDINT(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);
            ScalerDpAuxRx2SetDpcdMirrorBitValue_WDINT(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);

            break;
#endif

        default:

            break;
    }
}

#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get Dpcd Mirror Address
// Input Value  : Dpcd Address
// Output Value : Mirror Address
//--------------------------------------------------
DWORD ScalerDpAuxRxDpcdGetMirrorAddr_WDINT(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL)
{
    DWORD ulDpcdAddrInput = TO_DWORD(0x00, ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL);

    // 200-201 = 2002-2003
    if((ulDpcdAddrInput >= 0x00200) && (ulDpcdAddrInput <= 0x00201))
    {
        return (ulDpcdAddrInput + 0x01E02);
    }
    else if((ulDpcdAddrInput >= 0x02002) && (ulDpcdAddrInput <= 0x02003))
    {
        return (ulDpcdAddrInput - 0x01E02);
    }
    // 202-205 = 200C-200F
    else if((ulDpcdAddrInput >= 0x00202) && (ulDpcdAddrInput <= 0x00205))
    {
        return (ulDpcdAddrInput + 0x01E0A);
    }
    else if((ulDpcdAddrInput >= 0x0200C) && (ulDpcdAddrInput <= 0x0200F))
    {
        return (ulDpcdAddrInput - 0x01E0A);
    }
    // 20F-2011
    else if(ulDpcdAddrInput == 0x0020F)
    {
        return 0x02011;
    }
    else if(ulDpcdAddrInput == 0x02011)
    {
        return 0x0020F;
    }
    // 2-F = 2202-220F
    else if((ulDpcdAddrInput >= 0x00002) && (ulDpcdAddrInput <= 0x0000F))
    {
        return (ulDpcdAddrInput + 0x02200);
    }
    else if((ulDpcdAddrInput >= 0x02202) && (ulDpcdAddrInput <= 0x0220F))
    {
        return (ulDpcdAddrInput - 0x02200);
    }
    else
    {
        // Fail Case
        return 0xFFFFFFFF;
    }
}
#endif

//--------------------------------------------------
// Description  : DP Dpcd Port Access Backup
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxDpcdPortAccessBackup_WDINT(void)
{
#if(_DP_AUX_RX0_SUPPORT == _ON)
    ScalerDpAuxRx0DpcdPortAccessBackup_WDINT();
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
    ScalerDpAuxRx1DpcdPortAccessBackup_WDINT();
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
    ScalerDpAuxRx2DpcdPortAccessBackup_WDINT();
#endif
}

//--------------------------------------------------
// Description  : DP Dpcd Port Access Backup Restore
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxDpcdPortAccessBackupRestore_WDINT(void)
{
#if(_DP_AUX_RX0_SUPPORT == _ON)
    ScalerDpAuxRx0DpcdPortAccessBackupRestore_WDINT();
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
    ScalerDpAuxRx1DpcdPortAccessBackupRestore_WDINT();
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
    ScalerDpAuxRx2DpcdPortAccessBackupRestore_WDINT();
#endif
}

//--------------------------------------------------
// Description  : DP Aux Get Link Training Status
// Input Value  : None
// Output Value : Link Training Status
//--------------------------------------------------
BYTE ScalerDpAuxRxGetLTStatus_WDINT(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping_WDINT(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            return GET_DP_AUX_RX0_LINK_TRAINING_STATUS();
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            return GET_DP_AUX_RX1_LINK_TRAINING_STATUS();
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            return GET_DP_AUX_RX2_LINK_TRAINING_STATUS();
#endif
        default:

            return _DP_LINK_TRAINING_NONE;
    }
}


//--------------------------------------------------
// Description  : DP Aux Set Link Training Status
// Input Value  : Link Training Status Set
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxSetLTStatus_WDINT(EnumInputPort enumInputPort, BYTE ucLTStatusSet)
{
    switch(ScalerDpAuxRxDxRxMapping_WDINT(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            SET_DP_AUX_RX0_LINK_TRAINING_STATUS(ucLTStatusSet);

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            SET_DP_AUX_RX1_LINK_TRAINING_STATUS(ucLTStatusSet);

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            SET_DP_AUX_RX2_LINK_TRAINING_STATUS(ucLTStatusSet);

            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : DP Aux Auto Mode
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxSetAutoMode_WDINT(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping_WDINT(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            SET_DP_AUX_RX0_AUTO_MODE_EXINT();

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            SET_DP_AUX_RX1_AUTO_MODE_EXINT();

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            SET_DP_AUX_RX2_AUTO_MODE_EXINT();

            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : DP Aux Manual Mode
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxSetManualMode_WDINT(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping_WDINT(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            SET_DP_AUX_RX0_MANUAL_MODE_EXINT();

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            SET_DP_AUX_RX1_MANUAL_MODE_EXINT();

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            SET_DP_AUX_RX2_MANUAL_MODE_EXINT();

            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Get DP Link Rate (DPCD 00100h)
// Input Value  : DP Input Port
// Output Value : DP Link Rate
//--------------------------------------------------
EnumDpLinkRate ScalerDpAuxRxGetDpcdLinkRate_WDINT(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxGetDpcdInfo_WDINT(enumInputPort, 0x00, 0x01, 0x00))
    {
        case 0x21:
            return _DP_LINK_HBR3_9G;

        case 0x1E:
            return _DP_LINK_HBR3;

        case 0x14:
            return _DP_LINK_HBR2;

        case 0x0A:
            return _DP_LINK_HBR;

        case 0x06:
            return _DP_LINK_RBR;

#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
        case 0x04:
            return _DP_LINK_UHBR13_5;

        case 0x02:
            return _DP_LINK_UHBR20;

        case 0x01:
            return _DP_LINK_UHBR10;
#endif
        default:
            return _DP_LINK_RBR;
    }
}

//--------------------------------------------------
// Description  : Get Link Training Link Rate
// Input Value  : SearchPort
// Output Value : Link Rate
//--------------------------------------------------
EnumDpLinkRate ScalerDpAuxRxGetLinkRate_WDINT(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxGetTrainingPatternSet_WDINT(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            return g_enumDpAuxRx0LinkRate;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            return g_enumDpAuxRx1LinkRate;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            return g_enumDpAuxRx2LinkRate;
#endif
        default:

            return 0x00;
    }
}

//--------------------------------------------------
// Description  : Get Link Training Pattern
// Input Value  : SearchPort
// Output Value : Link Training Pattern
//--------------------------------------------------
BYTE ScalerDpAuxRxGetTrainingPatternSet_WDINT(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping_WDINT(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            return g_ucDpAuxRx0TrainingPatternSet;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            return g_ucDpAuxRx1TrainingPatternSet;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            return g_ucDpAuxRx2TrainingPatternSet;
#endif
        default:

            return 0x00;
    }
}

//--------------------------------------------------
// Description  : Set Phy Finish Flag Setting
// Input Value  : enumInputPort, bSetPhyDone
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxSetLinkTrainingSetPhyFinishFlag_WDINT(EnumInputPort enumInputPort, bit bSetPhyDone)
{
    switch(ScalerDpAuxRxDxRxMapping_WDINT(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            if(bSetPhyDone == _TRUE)
            {
                SET_DP_RX0_NORMAL_LINK_TRAINING_SETPHY_FINISH();
            }
            else
            {
                CLR_DP_RX0_NORMAL_LINK_TRAINING_SETPHY_FINISH();
            }

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            if(bSetPhyDone == _TRUE)
            {
                SET_DP_RX1_NORMAL_LINK_TRAINING_SETPHY_FINISH();
            }
            else
            {
                CLR_DP_RX1_NORMAL_LINK_TRAINING_SETPHY_FINISH();
            }

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            if(bSetPhyDone == _TRUE)
            {
                SET_DP_RX2_NORMAL_LINK_TRAINING_SETPHY_FINISH();
            }
            else
            {
                CLR_DP_RX2_NORMAL_LINK_TRAINING_SETPHY_FINISH();
            }

            break;
#endif

        default:

            break;
    }
}

#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get Link Training Coding Type
// Input Value  : SearchPort
// Output Value : Coding Type
//--------------------------------------------------
EnumDpLinkChannelCodingType ScalerDpAuxRxGetCodingType_WDINT(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping_WDINT(enumInputPort))
    {
#if(_DP_AUX_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
        case _RX0:

            return g_enumDpAuxRx0CodingType;

#endif

#if(_DP_AUX_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
        case _RX1:

            return g_enumDpAuxRx1CodingType;

#endif

#if(_DP_AUX_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
        case _RX2:

            return g_enumDpAuxRx2CodingType;

#endif
        default:

            return _CODING_TYPE_8B10B;
    }
}
#endif
//--------------------------------------------------
// Description  : Set DPCD Table Information
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxLinkStatusIRQ_WDINT(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping_WDINT(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpAuxRx0HpdIrqAssert_WDINT();

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpAuxRx1HpdIrqAssert_WDINT();

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpAuxRx2HpdIrqAssert_WDINT();

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Cancel DP IRQ
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxCancelLinkStatusIRQ_WDINT(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping_WDINT(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerTimerCancelTimerEvent_EXINT0(_SCALER_TIMER_EVENT_DP_RX0_LINK_STATUS_IRQ);

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerTimerCancelTimerEvent_EXINT0(_SCALER_TIMER_EVENT_DP_RX1_LINK_STATUS_IRQ);

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerTimerCancelTimerEvent_EXINT0(_SCALER_TIMER_EVENT_DP_RX2_LINK_STATUS_IRQ);

            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Reset DPCD & Status Info
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxDpcdLinkStatusReset_WDINT(EnumInputPort enumInputPort, EnumDpResetStatus enumDpResetStatus)
{
    switch(ScalerDpAuxRxDxRxMapping_WDINT(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpAuxRx0DpcdLinkStatusReset_WDINT(enumDpResetStatus);

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpAuxRx1DpcdLinkStatusReset_WDINT(enumDpResetStatus);

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpAuxRx2DpcdLinkStatusReset_WDINT(enumDpResetStatus);

            break;
#endif
        default:

            break;
    }
}

#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Handle DP LT Timeout WD Timer Event
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxWDTimerEventLinkTrainingTimeoutProc_WDINT(EnumInputPort enumInputPort)
{
    if(ScalerDpAuxRxGetTrainingPatternSet_WDINT(enumInputPort) != 0)
    {
        ScalerDpAuxRxSetDpcdValue_WDINT(enumInputPort, 0x00, 0x02, 0x06, 0x00);
        ScalerDpAuxRxSetDpcdValue_WDINT(enumInputPort, 0x00, 0x02, 0x07, 0x00);
        ScalerDpAuxRxSetDpcdMirrorBitValue_WDINT(enumInputPort, 0x00, 0x02, 0x04, ~(_BIT7 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT4));
    }
}
#endif

//--------------------------------------------------
// Description  : Handle the DP settings when exiting sysint
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxExitIntSetting_WDINT(void)
{
    // Restore Original Access Address
    ScalerDpAuxRxDpcdPortAccessBackupRestore_WDINT();
}

//--------------------------------------------------
// Description  : Handle the DP settings when exiting sysint
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxEnterIntSetting_WDINT(void)
{
    // Backup Original Access Address
    ScalerDpAuxRxDpcdPortAccessBackup_WDINT();
}
#endif

