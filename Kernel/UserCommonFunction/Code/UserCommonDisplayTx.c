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
// ID Code      : UserCommonDisplayTx.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_COMMON_DISPLAYTX__

#include "UserCommonInclude.h"
#include "DisplayTx/UserCommonDisplayTx.h"

//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_PANEL_STYLE == _PANEL_DPTX)
//--------------------------------------------------
// Description  : User Common Display Tx DP SSC Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonDisplayTxDpSSCSet(bit bSscEn)
{
    ScalerDisplayDpTxSSCSet(bSscEn);
}

//--------------------------------------------------
// Description  : Wait for Dp Tx Htpdn
// Input Value  : WORD usNum
// Output Value : None
//--------------------------------------------------
void UserCommonDisplayTxDpTxPollingHotPlug(WORD usNum)
{
#if(_TWO_CHIP_DATA_EXCHANGE_SUPPORT == _ON)
#if(_TWO_CHIP_BACK_CHIP_POWER_OFF_MODE == _ON)
    usNum = 5000;
#endif
#endif

    ScalerDisplayDpTxPollingHotPlug(usNum);
}

//--------------------------------------------------
// Description  : Settings for Dp Tx Link Sequence
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit UserCommonDisplayTxDpTxLinkSequence(void)
{
    return ScalerDisplayDpTxLinkSequence();
}

#if(_PANEL_DPTX_FORCE_OUTPUT_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP Tx Link TSignal Force Output
// Input Value  :
// Output Value :
//--------------------------------------------------
void UserCommonDisplayTxDpTxLinkSignalForceOutput(void)
{
    ScalerDisplayDpTxLinkSignalForceOutput();
}
#endif

//--------------------------------------------------
// Description  : Reset DPTX PLL Setting, Disable DPTX PLL Spread Spectrum Output
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonDisplayTxDpTxPllReset(void)
{
    ScalerPLLDPTxPLLReset();
}

//--------------------------------------------------
// Description  : DP Tx Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonDisplayTxDpTxInitial(void)
{
    ScalerDisplayDpTxInitial();
}

//--------------------------------------------------
// Description  : DP Tx Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonDisplayTxDpTxPhyInitial(void)
{
    ScalerDisplayDpTxPhyInitial();
}

//--------------------------------------------------
// Description  : DP Tx Power Sequence Process
// Input Value  :
// Output Value :
//--------------------------------------------------
void UserCommonDisplayTxDpTxPowerSequenceProc(bit bLevel)
{
    ScalerDisplayDpTxPowerSequenceProc(bLevel);
}

//--------------------------------------------------
// Description  : Settings for Dp Tx Stream Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonDisplayTxDpTxStreamHanlder(bit bOutput)
{
    ScalerDisplayDpTxStreamHanlder(bOutput);
}

//--------------------------------------------------
// Description  : DP Tx I2CoverAux Write
// Input Value  : ucSlaveAddress --> SlaveAddress of I2CoverAux Write
//                ucLength --> Length of I2CoverAux Write
//                pWriteArray --> Data of I2CoverAux Write
// Output Value : EnumDpAuxStatus --> Native Aux Write Sucessful
//--------------------------------------------------
bit UserCommonDisplayTxDpTxXAuxI2COverWrite(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort, BYTE ucSlaveAddress, BYTE ucLength, BYTE *pucDataArray)
{
    while(ucLength > 16)
    {
        ucLength = ucLength - 16;

        if(ScalerDisplayDpTxAuxI2CoverWrite(enumDisplayDpTxOutputPort, ucSlaveAddress, 16, pucDataArray, 1) == _FALSE)
        {
            return _FALSE;
        }
        else
        {
            pucDataArray = pucDataArray + 16;
        }
    }

    if(ScalerDisplayDpTxAuxI2CoverWrite(enumDisplayDpTxOutputPort, ucSlaveAddress, ucLength, pucDataArray, 0) == _FALSE)
    {
        return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : DP Tx I2CoverAux Read
// Input Value  : ucSlaveAddress --> SlaveAddress of I2CoverAux Read
//                ucLength --> Length of I2CoverAux Read
//                pWriteArray --> Data of I2CoverAux Read
// Output Value : EnumDpAuxStatus --> Native Aux Write Sucessful
//--------------------------------------------------
bit UserCommonDisplayTxDpTxXAuxI2COverRead(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort, BYTE ucSlaveAddress, BYTE ucLength, BYTE *pucDataArray)
{
    while(ucLength > 16)
    {
        ucLength = ucLength - 16;

        if(ScalerDisplayDpTxAuxI2CoverRead(enumDisplayDpTxOutputPort, ucSlaveAddress, 16, pucDataArray, 1) == _FALSE)
        {
            return _FALSE;
        }
        else
        {
            pucDataArray = pucDataArray + 16;
        }
    }

    if(ScalerDisplayDpTxAuxI2CoverRead(enumDisplayDpTxOutputPort, ucSlaveAddress, ucLength, pucDataArray, 0) == _FALSE)
    {
        return _FALSE;
    }

    return _TRUE;
}
#endif

#if(_PANEL_STYLE == _PANEL_VBO)
//--------------------------------------------------
// Description  : Wait for Vbyone Htpdn
// Input Value  : WORD usNum
// Output Value : None
//--------------------------------------------------
void UserCommonDisplayTxVboPollingHotPlug(WORD usNum)
{
    ScalerDisplayVboTxPollingHotPlug(usNum);
}

//--------------------------------------------------
// Description  : Vbyone Lockn Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonDisplayTxVboLocknHandler(void)
{
    ScalerDisplayVboTxLocknHandler();
}

//--------------------------------------------------
// Description  : Vbyone Panel Fast Off Setting
// Input Value  : _ENABLE or _DISABLE
// Output Value : None
//--------------------------------------------------
void UserCommonDisplayTxVboPanelSetFastOff(bit bEnable)
{
    ScalerDisplayVboTxPanelSetFastOff(bEnable);
}
#endif

#if(_PANEL_STYLE == _PANEL_LVDS)
//--------------------------------------------------
// Description  : LVDS PLL(Data) Power Control
// Input Value  : _ON or _OFF
// Output Value : None
//--------------------------------------------------
void UserCommonDisplayTxLvdsPLL(bit bOn)
{
    ScalerDisplayLvdsPLL(bOn);
}

//--------------------------------------------------
// Description  : LVDS Power Control
// Input Value  : _ON or _OFF
// Output Value : None
//--------------------------------------------------
void UserCommonDisplayTxLvdsPower(bit bOn)
{
    ScalerDisplayLvdsPower(bOn);
}
#endif

#if(_PANEL_EXIST_MULTIPANEL == _ON)
//--------------------------------------------------
// Description  : User Common Display Tx DP SSC Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonDisplayTxMultiPanelSettingApply(void)
{
    // Set Display Interface Power Switch
    ScalerDisplayInterfacePowerSwitch();

    // Set DisplayConverion
    ScalerDisplaySetDspc();
}
#endif

