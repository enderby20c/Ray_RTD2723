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
// ID Code      : ScalerDpAuxRx.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_DPAUX__

#include "ScalerFunctionInclude.h"
#include "DpAuxRx/ScalerDpAuxRx.h"

#if(_DP_SUPPORT == _ON)
//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
volatile DWORD g_ulDpAuxRxBase32AddressOffset;
volatile bit g_pbDpAuxRxDpcdMstEnBackup[_DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS];

#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
#if(_DP_MST_SUPPORT == _ON)
volatile StructDpAuxRxMsgFlag g_stDpAuxRxMsgFlag;
#endif
#endif


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : DP Port Rx mapping to Dx
// Input Value  : Rx Port
// Output Value : Dx port
//--------------------------------------------------
EnumInputPort ScalerDpAuxRxRxDxMapping(EnumRx enumRx)
{
    EnumInputPort enumInputPort = _NO_INPUT_PORT;

    switch(enumRx)
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            if(_HW_D0_DP_AUX_RX_MAPPING == _RX0)
            {
                enumInputPort = _D0_INPUT_PORT;
            }
            else if(_HW_D1_DP_AUX_RX_MAPPING == _RX0)
            {
                enumInputPort = _D1_INPUT_PORT;
            }
            else if(_HW_D2_DP_AUX_RX_MAPPING == _RX0)
            {
                enumInputPort = _D2_INPUT_PORT;
            }

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            if(_HW_D0_DP_AUX_RX_MAPPING == _RX1)
            {
                enumInputPort = _D0_INPUT_PORT;
            }
            else if(_HW_D1_DP_AUX_RX_MAPPING == _RX1)
            {
                enumInputPort = _D1_INPUT_PORT;
            }
            else if(_HW_D2_DP_AUX_RX_MAPPING == _RX1)
            {
                enumInputPort = _D2_INPUT_PORT;
            }

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            if(_HW_D0_DP_AUX_RX_MAPPING == _RX2)
            {
                enumInputPort = _D0_INPUT_PORT;
            }
            else if(_HW_D1_DP_AUX_RX_MAPPING == _RX2)
            {
                enumInputPort = _D1_INPUT_PORT;
            }
            else if(_HW_D2_DP_AUX_RX_MAPPING == _RX2)
            {
                enumInputPort = _D2_INPUT_PORT;
            }

            break;
#endif

#if((_DP_AUX_RX0_SUPPORT == _ON) && (_DP_AUX_RX1_SUPPORT == _ON))
        case _RX7:

            enumInputPort = _D7_INPUT_PORT;

            break;
#endif

#if((_DP_AUX_RX1_SUPPORT == _ON) && (_DP_AUX_RX2_SUPPORT == _ON))
        case _RX8:

            enumInputPort = _D8_INPUT_PORT;

            break;
#endif

        default:

            break;
    }

    return enumInputPort;
}

//--------------------------------------------------
// Description  : DP Port Dx mapping to Rx
// Input Value  : Input Port
// Output Value : Rx0 or Rx1 or Rx2
//--------------------------------------------------
EnumRx ScalerDpAuxRxDxRxMapping(EnumInputPort enumInputPort)
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

#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
#if(_DP_MST_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP Port Dx mapping for Msg Flag
// Input Value  : None
// Output Value : Rx0 or Rx1 or Rx2
//--------------------------------------------------
EnumRx ScalerDpAuxRxMsgFlagMapping(EnumInputPort enumInputPort)
{
    EnumRx enumRx = ScalerDpAuxRxDxRxMapping(enumInputPort);

    if(enumRx >= _DP_AUX_RX_MAG_FLAG_LENGTH)
    {
        return _RX0;
    }

    return enumRx;
}
#endif
#endif

//--------------------------------------------------
// Description  : Initial Setting for DP AUX
// Input Value  : enumDpVersion, enumDpLaneCount, enumDpRxMstPort, enumDisplayMode, enumFreeSyncSupport
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxInitial(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpAuxRx0Initial();

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpAuxRx1Initial();

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpAuxRx2Initial();

            break;
#endif

#if((_DP_AUX_RX0_SUPPORT == _ON) && (_DP_AUX_RX1_SUPPORT == _ON))
        case _RX7:

            ScalerDpAuxRx0Initial();
            ScalerDpAuxRx1Initial();

            break;
#endif

#if((_DP_AUX_RX1_SUPPORT == _ON) && (_DP_AUX_RX2_SUPPORT == _ON))
        case _RX8:

            ScalerDpAuxRx1Initial();
            ScalerDpAuxRx2Initial();

            break;
#endif
        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Dp Aux Power On
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxPowerOn(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpAuxRx0PowerOn();

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpAuxRx1PowerOn();

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpAuxRx2PowerOn();

            break;
#endif
        default:
            break;
    }
}

//-------------------------------------------------------
// Description  : Set Aux Diff mode or Single-eneded mode
// Input Value  : None
// Output Value : None
//-------------------------------------------------------
void ScalerDpAuxRxSet(void)
{
#if(_DP_AUX_RX0_SUPPORT == _ON)
    ScalerDpAuxRx0AuxSet();
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
    ScalerDpAuxRx1AuxSet();
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
    ScalerDpAuxRx2AuxSet();
#endif
}

//--------------------------------------------------
// Description  : Set DP Lane Mapping Type
// Input Value  : enumInputPort     --> Input Port
//                enumPinAssignment --> Pin Assignment Type
//                enumOrientation   --> Orientation
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxSetLaneMapping(EnumInputPort enumInputPort, EnumTypeCPinCfgType enumPinAssignment, EnumTypeCOrientation enumOrientation)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpAuxRx0SetLaneMapping(enumPinAssignment, enumOrientation);

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpAuxRx1SetLaneMapping(enumPinAssignment, enumOrientation);

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpAuxRx2SetLaneMapping(enumPinAssignment, enumOrientation);

            break;
#endif

#if((_DP_AUX_RX0_SUPPORT == _ON) && (_DP_AUX_RX1_SUPPORT == _ON))
        case _RX7:

            ScalerDpAuxRx0SetLaneMapping(enumPinAssignment, enumOrientation);
            ScalerDpAuxRx1SetLaneMapping(enumPinAssignment, enumOrientation);

            break;
#endif

#if((_DP_AUX_RX1_SUPPORT == _ON) && (_DP_AUX_RX2_SUPPORT == _ON))
        case _RX8:

            ScalerDpAuxRx1SetLaneMapping(enumPinAssignment, enumOrientation);
            ScalerDpAuxRx2SetLaneMapping(enumPinAssignment, enumOrientation);

            break;
#endif
        default:

            break;
    }
}

//-----------------------------------------------------------------------
// Description  : Set DP Aux Power Off
// Input Value  : None
// Output Value : None
//-----------------------------------------------------------------------
void ScalerDpAuxRxLowPowerProc(void)
{
#if(_DP_AUX_RX0_SUPPORT == _ON)
    CLR_DP_AUX_RX0_TOGGLE();
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
    CLR_DP_AUX_RX1_TOGGLE();
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
    CLR_DP_AUX_RX2_TOGGLE();
#endif
}

//--------------------------------------------------
// Description  : DP Fake LT Protect
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxFakeLTProtect(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpAuxRx0FakeLTProtect();

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpAuxRx1FakeLTProtect();

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpAuxRx2FakeLTProtect();

            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Get DP Fake LT Flag
// Input Value  : Input Port
// Output Value : DP Fake LT Flag
//--------------------------------------------------
bit ScalerDpAuxRxGetFakeLT(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            return GET_DP_AUX_RX0_FAKE_LINK_TRAINING();
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            return GET_DP_AUX_RX1_FAKE_LINK_TRAINING();
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            return GET_DP_AUX_RX2_FAKE_LINK_TRAINING();
#endif

        default:

            return _FALSE;
    }
}

//--------------------------------------------------
// Description  : DP Phy Initial Setting
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxSetFakeLinkTraining(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            SET_DP_AUX_RX0_FAKE_LINK_TRAINING();

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            SET_DP_AUX_RX1_FAKE_LINK_TRAINING();

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            SET_DP_AUX_RX2_FAKE_LINK_TRAINING();

            break;
#endif

#if((_DP_AUX_RX0_SUPPORT == _ON) && (_DP_AUX_RX1_SUPPORT == _ON))
        case _RX7:

            SET_DP_AUX_RX0_FAKE_LINK_TRAINING();
            SET_DP_AUX_RX1_FAKE_LINK_TRAINING();

            break;
#endif

#if((_DP_AUX_RX1_SUPPORT == _ON) && (_DP_AUX_RX2_SUPPORT == _ON))
        case _RX8:

            SET_DP_AUX_RX1_FAKE_LINK_TRAINING();
            SET_DP_AUX_RX2_FAKE_LINK_TRAINING();

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : DP Phy Initial Setting
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxClearFakeLinkTraining(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            CLR_DP_AUX_RX0_FAKE_LINK_TRAINING();

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            CLR_DP_AUX_RX1_FAKE_LINK_TRAINING();

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            CLR_DP_AUX_RX2_FAKE_LINK_TRAINING();

            break;
#endif

#if((_DP_AUX_RX0_SUPPORT == _ON) && (_DP_AUX_RX1_SUPPORT == _ON))
        case _RX7:

            CLR_DP_AUX_RX0_FAKE_LINK_TRAINING();
            CLR_DP_AUX_RX1_FAKE_LINK_TRAINING();

            break;
#endif

#if((_DP_AUX_RX1_SUPPORT == _ON) && (_DP_AUX_RX2_SUPPORT == _ON))
        case _RX8:

            CLR_DP_AUX_RX1_FAKE_LINK_TRAINING();
            CLR_DP_AUX_RX2_FAKE_LINK_TRAINING();

            break;
#endif

        default:

            break;
    }
}

#if(_HP_SOURCE_SCAN_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP All Port Fake LT MARCO Status
// Input Value  : None
// Output Value : DP All Port Fake LT MARCO Status
//--------------------------------------------------
BYTE ScalerDpAuxRxGetAllPortFakeLT(void)
{
    BYTE ucFakeLT = 0;

#if(_DP_AUX_RX0_SUPPORT == _ON)
    ucFakeLT = (ucFakeLT | (((BYTE)GET_DP_AUX_RX0_FAKE_LINK_TRAINING()) & _BIT0));
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
    ucFakeLT = (ucFakeLT | (((BYTE)GET_DP_AUX_RX1_FAKE_LINK_TRAINING() << 1) & _BIT1));
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
    ucFakeLT = (ucFakeLT | (((BYTE)GET_DP_AUX_RX2_FAKE_LINK_TRAINING() << 2) & _BIT2));
#endif

    return ucFakeLT;
}
#endif

//--------------------------------------------------
// Description  : Dp Capability Switch
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpAuxRxVersionChange(EnumInputPort enumInputPort, EnumDpVersionType enumDpVersion)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            return ScalerDpAuxRx0VersionChange(enumDpVersion);
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            return ScalerDpAuxRx1VersionChange(enumDpVersion);
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            return ScalerDpAuxRx2VersionChange(enumDpVersion);
#endif
        default:

            return _FALSE;
    }
}

//--------------------------------------------------
// Description  : Dp Version Switch
// Input Value  : _DP_VERSION_1_1 or _DP_VERSION_1_2
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxChangeDpcdVersion(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpAuxRx0ChangeDpcdVersion();

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpAuxRx1ChangeDpcdVersion();

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpAuxRx2ChangeDpcdVersion();

            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Switch Irq Proc
// Input Value  : EnumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxSwitchDpcdAddrIrqSetting(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpAuxRx0SwitchDpcdAddrIrqSetting();

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpAuxRx1SwitchDpcdAddrIrqSetting();

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpAuxRx2SwitchDpcdAddrIrqSetting();

            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : DP Sink Status Setting
// Input Value  : Receive Port, Sync Status
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxSinkStatusSet(EnumInputPort enumInputPort, EnumDpSinkReceivePort enumReceiverPort, EnumDpSinkStatus enumInSync)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpAuxRx0SinkStatusSet(enumReceiverPort, enumInSync);

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpAuxRx1SinkStatusSet(enumReceiverPort, enumInSync);

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpAuxRx2SinkStatusSet(enumReceiverPort, enumInSync);

            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : DP Aux Set Manual Mode
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxSetManualMode(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            SET_DP_AUX_RX0_MANUAL_MODE();

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            SET_DP_AUX_RX1_MANUAL_MODE();

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            SET_DP_AUX_RX2_MANUAL_MODE();

            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : DP Aux Set Manual Mode
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxSetAutoMode(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            SET_DP_AUX_RX0_AUTO_MODE();

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            SET_DP_AUX_RX1_AUTO_MODE();

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            SET_DP_AUX_RX2_AUTO_MODE();

            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : DP Aux Link Status Reload
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxLinkStatusReload(EnumInputPort enumInputPort)
{
    EnumDpAuxRxModeStatus enumBackUpAuxModeStatus = ScalerDpAuxRxGetAuxModeStatus(enumInputPort);

    if(enumBackUpAuxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        ScalerDpAuxRxSetManualMode(enumInputPort);
    }

    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            if(GET_DP_AUX_RX0_BACKUP_PD_LINK_STATUS_FLG() == _TRUE)
            {
                ScalerDpAuxRx0SetDpcdMirrorValue(0x00, 0x02, 0x02, g_pucDpAuxRx0LinkStatusBackup_INT[0]);
                ScalerDpAuxRx0SetDpcdMirrorValue(0x00, 0x02, 0x03, g_pucDpAuxRx0LinkStatusBackup_INT[1]);
                ScalerDpAuxRx0SetDpcdMirrorBitValue(0x00, 0x02, 0x04, ~(_BIT7 | _BIT0), (_BIT7 | g_pucDpAuxRx0LinkStatusBackup_INT[2]));
            }

            CLR_DP_AUX_RX0_BACKUP_PD_LINK_STATUS_FLG();

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            if(GET_DP_AUX_RX1_BACKUP_PD_LINK_STATUS_FLG() == _TRUE)
            {
                ScalerDpAuxRx1SetDpcdMirrorValue(0x00, 0x02, 0x02, g_pucDpAuxRx1LinkStatusBackup_INT[0]);
                ScalerDpAuxRx1SetDpcdMirrorValue(0x00, 0x02, 0x03, g_pucDpAuxRx1LinkStatusBackup_INT[1]);
                ScalerDpAuxRx1SetDpcdMirrorBitValue(0x00, 0x02, 0x04, ~(_BIT7 | _BIT0), (_BIT7 | g_pucDpAuxRx1LinkStatusBackup_INT[2]));
            }

            CLR_DP_AUX_RX1_BACKUP_PD_LINK_STATUS_FLG();

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            if(GET_DP_AUX_RX2_BACKUP_PD_LINK_STATUS_FLG() == _TRUE)
            {
                ScalerDpAuxRx2SetDpcdMirrorValue(0x00, 0x02, 0x02, g_pucDpAuxRx2LinkStatusBackup_INT[0]);
                ScalerDpAuxRx2SetDpcdMirrorValue(0x00, 0x02, 0x03, g_pucDpAuxRx2LinkStatusBackup_INT[1]);
                ScalerDpAuxRx2SetDpcdMirrorBitValue(0x00, 0x02, 0x04, ~(_BIT7 | _BIT0), (_BIT7 | g_pucDpAuxRx2LinkStatusBackup_INT[2]));
            }

            CLR_DP_AUX_RX2_BACKUP_PD_LINK_STATUS_FLG();

            break;
#endif
        default:

            break;
    }

    if(enumBackUpAuxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        ScalerDpAuxRxSetAutoMode(enumInputPort);
    }
}

//--------------------------------------------------
// Description  : DP Aux Assr Mode Enable
// Input Value  : enumInputPort
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpAuxRxGetAssrModeEnable(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

#if(_DP_AUX_RX0_ASSR_SUPPORT == _ON)
            return _TRUE;
#endif

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

#if(_DP_AUX_RX1_ASSR_SUPPORT == _ON)
            return _TRUE;
#endif

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

#if(_DP_AUX_RX2_ASSR_SUPPORT == _ON)
            return _TRUE;
#endif

            break;
#endif
        default:

            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Aux PHY Swap Setting
// Input Value  : EnumInputPort, TypeC PinAssignment, TypeC Orientation
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxTypeCPinAssert(EnumInputPort enumInputPort, EnumTypeCPinCfgType enumPinAssignment, EnumTypeCOrientation enumTypeCOrientation)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpAuxRx0TypeCPinAssert(enumPinAssignment, enumTypeCOrientation);

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpAuxRx1TypeCPinAssert(enumPinAssignment, enumTypeCOrientation);

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpAuxRx2TypeCPinAssert(enumPinAssignment, enumTypeCOrientation);

            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : DP HPD Toggle AUX Reset Process
// Input Value  : DP Input Port, HPD _HIGH/_LOW
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxHpdTogglePhyResetProc(EnumInputPort enumInputPort, bit bHpdHighLow)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:
            ScalerDpAuxRx0HpdTogglePhyResetProc(bHpdHighLow);
            break;
#endif
#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:
            ScalerDpAuxRx1HpdTogglePhyResetProc(bHpdHighLow);
            break;
#endif
#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:
            ScalerDpAuxRx2HpdTogglePhyResetProc(bHpdHighLow);
            break;
#endif
        default:
            break;
    }
}

#if((_DP_RX_DSC_DECODER_SUPPORT == _ON) || (_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Dp Aux Rx DSC Unplug Reset
// Input Value  : ucRxIndex
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxDscUnplugReset(EnumInputPort enumInputPort)
{
    DebugMessageDSC("DSC Unplug Reset", 0x00);

    enumInputPort = enumInputPort;

#if(_DP_RX_DSC_DECODER_SUPPORT == _ON)

    // Reset DSC Function
    ScalerDscDecoderReset(enumInputPort);

    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
        case _RX0:
#if(_DP_AUX_RX0_DSC_DECODER_SUPPORT == _ON)

            // Reset DSC Decompression Enable
            ScalerDpAuxRx0SetDpcdBitWriteValue(0x00, 0x01, 0x60, ~_BIT0, 0x00);

            // Reset DSC Status
            ScalerDpAuxRx0SetDpcdMirrorBitWrite1ClearValue(0x00, 0x02, 0x0F, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

#endif
            break;

        case _RX1:
#if(_DP_AUX_RX1_DSC_DECODER_SUPPORT == _ON)

            // Reset DSC Decompression Enable
            ScalerDpAuxRx1SetDpcdBitWriteValue(0x00, 0x01, 0x60, ~_BIT0, 0x00);

            // Reset DSC Status
            ScalerDpAuxRx1SetDpcdMirrorBitWrite1ClearValue(0x00, 0x02, 0x0F, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

#endif
            break;

        case _RX2:
#if(_DP_AUX_RX2_DSC_DECODER_SUPPORT == _ON)

            // Reset DSC Decompression Enable
            ScalerDpAuxRx2SetDpcdBitWriteValue(0x00, 0x01, 0x60, ~_BIT0, 0x00);

            // Reset DSC Status
            ScalerDpAuxRx2SetDpcdMirrorBitWrite1ClearValue(0x00, 0x02, 0x0F, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

#endif
            break;

        default:
            break;
    }
#endif

#if(_DP_MAC_TX_SUPPORT == _ON)
    if(GET_DP_RX_MAIN_PORT() == enumInputPort)
    {
#if(_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON)
        CLR_DP_TX_DOWNSTREAM_DSC_PASSTHROUGH();
        CLR_DP_TX_DOWNSTREAM_DSC_DETECT_PASSTHROUGH();
        CLR_DP_TX_DOWNSTREAM_DSC_DETECT_ENABLE();
        SET_DP_TX_DSC_PASSTHROUGH_TYPE(_SOURCE_PASSTHROUGH_DSC_BY_NONE);
#endif
#if(_DP_MST2SST_BRANCH_DSC_DECODER_SUPPORT == _ON)
        CLR_DP_MAC_MST2SST_DETECT_DSC_DECODE_ENABLE();
        CLR_DP_MAC_MST2SST_ENABLE();
#endif
    }
#endif
}
#endif

#if(_DP_MST_SUPPORT == _ON)
//--------------------------------------------------
// Description  : MST Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxMstReset(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpAuxRx0MstReset();

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpAuxRx1MstReset();

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpAuxRx2MstReset();

            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : DP Mst Capability Switch
// Input Value  : _ENABLE / _DISABLE
// Output Value : Change or not
//--------------------------------------------------
bit ScalerDpAuxRxMstCapabilitySwitch(EnumInputPort enumInputPort, bit bEn)
{
    if(bEn == _ENABLE)
    {
        if(ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x00, 0x00, 0x21, _BIT0) == 0x00)
        {
            // Down Sream Port Present
            ScalerDpAuxRxSetDpcdValue(enumInputPort, 0x00, 0x00, 0x05, 0x01);
            ScalerDpAuxRxSetDpcdValue(enumInputPort, 0x00, 0x22, 0x05, 0x01);

            ScalerDpAuxRxSetDpcdValue(enumInputPort, 0x00, 0x00, 0x21, 0x01);

            ScalerDpAuxRxSetBranchDeviceSpecificField(enumInputPort);

            return _TRUE;
        }
    }
    else
    {
        if(ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x00, 0x00, 0x21, _BIT0) == _BIT0)
        {
#if((_DP_DPCD_DFP_PRESENT_REF_TO == _DP_TX_EXISTENCE) && (_DP_TX_SUPPORT == _ON))
            // Down Sream Port Present
            ScalerDpAuxRxSetDpcdValue(enumInputPort, 0x00, 0x00, 0x05, 0x01);
            ScalerDpAuxRxSetDpcdValue(enumInputPort, 0x00, 0x22, 0x05, 0x01);

            ScalerDpAuxRxSetBranchDeviceSpecificField(enumInputPort);
#else
            // Down Sream Port isn't Present
            ScalerDpAuxRxSetDpcdValue(enumInputPort, 0x00, 0x00, 0x05, 0x00);
            ScalerDpAuxRxSetDpcdValue(enumInputPort, 0x00, 0x22, 0x05, 0x00);

            ScalerDpAuxRxClrBranchDeviceSpecificField(enumInputPort);
#endif

            ScalerDpAuxRxSetDpcdValue(enumInputPort, 0x00, 0x00, 0x21, 0x00);

            return _TRUE;
        }
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Set Branch Device Specific Field
// Input Value  : EnumInputPort
// Output Value : void
//--------------------------------------------------
void ScalerDpAuxRxSetBranchDeviceSpecificField(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpAuxRx0SetBranchDeviceSpecificField(GET_DP_RX_D0_PORT_TARGET_VERSION());

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpAuxRx1SetBranchDeviceSpecificField(GET_DP_RX_D1_PORT_TARGET_VERSION());

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpAuxRx2SetBranchDeviceSpecificField(GET_DP_RX_D2_PORT_TARGET_VERSION());

            break;
#endif

#if((_DP_AUX_RX0_SUPPORT == _ON) && (_DP_AUX_RX1_SUPPORT == _ON))
        case _RX7:

            ScalerDpAuxRx0SetBranchDeviceSpecificField(GET_DP_RX_D0_PORT_TARGET_VERSION());
            ScalerDpAuxRx1SetBranchDeviceSpecificField(GET_DP_RX_D1_PORT_TARGET_VERSION());

            break;
#endif

#if((_DP_AUX_RX1_SUPPORT == _ON) && (_DP_AUX_RX2_SUPPORT == _ON))
        case _RX8:

            ScalerDpAuxRx1SetBranchDeviceSpecificField(GET_DP_RX_D1_PORT_TARGET_VERSION());
            ScalerDpAuxRx2SetBranchDeviceSpecificField(GET_DP_RX_D2_PORT_TARGET_VERSION());

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Clear Branch Device Specific Field
// Input Value  : EnumInputPort
// Output Value : void
//--------------------------------------------------
void ScalerDpAuxRxClrBranchDeviceSpecificField(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpAuxRx0ClrBranchDeviceSpecificField();

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpAuxRx1ClrBranchDeviceSpecificField();

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpAuxRx2ClrBranchDeviceSpecificField();

            break;
#endif

#if((_DP_AUX_RX0_SUPPORT == _ON) && (_DP_AUX_RX1_SUPPORT == _ON))
        case _RX7:

            ScalerDpAuxRx0ClrBranchDeviceSpecificField();
            ScalerDpAuxRx1ClrBranchDeviceSpecificField();

            break;
#endif

#if((_DP_AUX_RX1_SUPPORT == _ON) && (_DP_AUX_RX2_SUPPORT == _ON))
        case _RX8:

            ScalerDpAuxRx1ClrBranchDeviceSpecificField();
            ScalerDpAuxRx2ClrBranchDeviceSpecificField();

            break;
#endif

        default:

            break;
    }
}
#endif

//--------------------------------------------------
// Description  : Dp Rx Aux Ch Power Status Check
// Input Value  : bCableStatus
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxChPowerStatusCheck(EnumInputPort enumInputPort, bit bCableStatus)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpAuxRx0AuxChPowerStatusCheck(bCableStatus);

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpAuxRx1AuxChPowerStatusCheck(bCableStatus);

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpAuxRx2AuxChPowerStatusCheck(bCableStatus);

            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Aux Rx Link Rate Switch
// Input Value  : enumInputPort, enumDpLinkRate
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxMaxLinkRateCapabilitySwitch(EnumInputPort enumInputPort, EnumDpLinkRate enumDpLinkRate)
{
    switch(enumInputPort)
    {
#if(_D0_DP_SUPPORT == _ON)
        case _D0_INPUT_PORT:

            SET_DP_RX_D0_PORT_TARGET_MAX_LINK_RATE(enumDpLinkRate);

            SET_DP_RX_D0_PORT_TARGET_MAX_LINK_RATE_SWITCH();

            SET_DP_RX_CAPABILITY_SWITCHED();

            break;
#endif

#if(_D1_DP_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            SET_DP_RX_D1_PORT_TARGET_MAX_LINK_RATE(enumDpLinkRate);

            SET_DP_RX_D1_PORT_TARGET_MAX_LINK_RATE_SWITCH();

            SET_DP_RX_CAPABILITY_SWITCHED();

            break;
#endif

#if(_D2_DP_SUPPORT == _ON)
        case _D2_INPUT_PORT:

            SET_DP_RX_D2_PORT_TARGET_MAX_LINK_RATE(enumDpLinkRate);

            SET_DP_RX_D2_PORT_TARGET_MAX_LINK_RATE_SWITCH();

            SET_DP_RX_CAPABILITY_SWITCHED();

            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Dp Link Rate Support Switch Process
// Input Value  : Input Port
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpAuxRxLinkRateCapabilitySwitchProc(EnumInputPort enumInputPort)
{
    EnumDpLinkRate enumDpLinkRate = _DP_LINK_NONE;

    switch(enumInputPort)
    {
#if(_D0_DP_SUPPORT == _ON)
        case _D0_INPUT_PORT:

            if(GET_DP_RX_D0_PORT_TARGET_MAX_LINK_RATE_SWITCH() == _TRUE)
            {
                CLR_DP_RX_D0_PORT_TARGET_MAX_LINK_RATE_SWITCH();

                enumDpLinkRate = GET_DP_RX_D0_PORT_TARGET_MAX_LINK_RATE();

                if(enumDpLinkRate != ScalerDpAuxRxGetDpcdMaxLinkRateCapability(_D0_INPUT_PORT))
                {
                    ScalerDpAuxRxSetDpcdMaxLinkRateCapability(_D0_INPUT_PORT, GET_DP_RX_D0_PORT_TARGET_VERSION(), enumDpLinkRate);

                    return _TRUE;
                }
            }

            break;
#endif

#if(_D1_DP_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            if(GET_DP_RX_D1_PORT_TARGET_MAX_LINK_RATE_SWITCH() == _TRUE)
            {
                CLR_DP_RX_D1_PORT_TARGET_MAX_LINK_RATE_SWITCH();

                enumDpLinkRate = GET_DP_RX_D1_PORT_TARGET_MAX_LINK_RATE();

                if(enumDpLinkRate != ScalerDpAuxRxGetDpcdMaxLinkRateCapability(_D1_INPUT_PORT))
                {
                    ScalerDpAuxRxSetDpcdMaxLinkRateCapability(_D1_INPUT_PORT, GET_DP_RX_D1_PORT_TARGET_VERSION(), enumDpLinkRate);

                    return _TRUE;
                }
            }

            break;
#endif

#if(_D2_DP_SUPPORT == _ON)
        case _D2_INPUT_PORT:

            if(GET_DP_RX_D2_PORT_TARGET_MAX_LINK_RATE_SWITCH() == _TRUE)
            {
                CLR_DP_RX_D2_PORT_TARGET_MAX_LINK_RATE_SWITCH();

                enumDpLinkRate = GET_DP_RX_D2_PORT_TARGET_MAX_LINK_RATE();

                if(enumDpLinkRate != ScalerDpAuxRxGetDpcdMaxLinkRateCapability(_D2_INPUT_PORT))
                {
                    ScalerDpAuxRxSetDpcdMaxLinkRateCapability(_D2_INPUT_PORT, GET_DP_RX_D2_PORT_TARGET_VERSION(), enumDpLinkRate);

                    return _TRUE;
                }
            }

            break;
#endif

        default:

            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Aux Rx Calculate Link Rate
// Input Value  : enumInputPort, DpVersion, Link Rate
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxSetDpcdMaxLinkRateCapability(EnumInputPort enumInputPort, EnumDpVersionType enumDpVersionType, EnumDpLinkRate enumDpLinkRate)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpAuxRx0SetDpcdMaxLinkRateCapability(enumDpVersionType, enumDpLinkRate);

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpAuxRx1SetDpcdMaxLinkRateCapability(enumDpVersionType, enumDpLinkRate);

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpAuxRx2SetDpcdMaxLinkRateCapability(enumDpVersionType, enumDpLinkRate);

            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : DPCD Link Rate Getting with different dp version
// Input Value  : None
// Output Value : LinkRate
//--------------------------------------------------
EnumDpLinkRate ScalerDpAuxRxGetDpcdMaxLinkRateCapability(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            return ScalerDpAuxRx0GetDpcdMaxLinkRateCapability();
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            return ScalerDpAuxRx1GetDpcdMaxLinkRateCapability();
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            return ScalerDpAuxRx2GetDpcdMaxLinkRateCapability();
#endif
        default:

            return _DP_LINK_NONE;
    }
}

//--------------------------------------------------
// Description  : DPCD Lane Count Getting with different dp version
// Input Value  : DP Input Port
// Output Value : DP Lane Count
//--------------------------------------------------
EnumDpLaneCount ScalerDpAuxRxGetDpcdMaxLaneCountCapability(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            return (EnumDpLaneCount) (ScalerDpAuxRx0GetDpcdBitInfo(0x00, 0x00, 0x02, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)));

#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            return (EnumDpLaneCount) (ScalerDpAuxRx1GetDpcdBitInfo(0x00, 0x00, 0x02, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)));

#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            return (EnumDpLaneCount) (ScalerDpAuxRx2GetDpcdBitInfo(0x00, 0x00, 0x02, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)));

#endif
        default:

            return _DP_LINK_4_LANE;
    }
}

//--------------------------------------------------
// Description  : DPCD Link Status Field Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxDpcdLinkStatusReset(EnumInputPort enumInputPort, EnumDpResetStatus enumDpResetStatus)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpAuxRx0DpcdLinkStatusReset(enumDpResetStatus);

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpAuxRx1DpcdLinkStatusReset(enumDpResetStatus);

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpAuxRx2DpcdLinkStatusReset(enumDpResetStatus);

            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Dp Before Hpd Toggle Process
// Input Value  : EnumDpRxHotPlugAssertType
// Output Value : None
//--------------------------------------------------
EnumDpHotPlugTime ScalerDpAuxRxBeforeHpdToggleProc(EnumInputPort enumInputPort, EnumDpHotPlugAssertType enumHpdType)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            return ScalerDpAuxRx0BeforeHpdToggleProc(enumHpdType);
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            return ScalerDpAuxRx1BeforeHpdToggleProc(enumHpdType);
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            return ScalerDpAuxRx2BeforeHpdToggleProc(enumHpdType);
#endif
        default:

            return _DP_HPD_TIME_NONE;
    }
}

//--------------------------------------------------
// Description  : Disconnect Reset
// Input Value  : EnumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxDisconnectReset(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpAuxRx0DisconnectReset();

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpAuxRx1DisconnectReset();

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpAuxRx2DisconnectReset();

            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Dp After Hpd Toggle Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxAfterHpdToggleProc(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpAuxRx0AfterHpdToggleProc();

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpAuxRx1AfterHpdToggleProc();

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpAuxRx2AfterHpdToggleProc();

            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Dp Interrupt Request
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxLinkStatusIRQ(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpAuxRx0LinkStatusIRQ();

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpAuxRx1LinkStatusIRQ();

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpAuxRx2LinkStatusIRQ();

            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Dp IRQ Assert Proc
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxHpdIrqAssert(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpAuxRx0HpdIrqAssert();

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpAuxRx1HpdIrqAssert();

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpAuxRx2HpdIrqAssert();

            break;
#endif
        default:

            break;
    }
}

#if(_DP_TX_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Dp HDCP Enable Read Irq
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxHdcp14EnableReadIrq(bit bEnable, EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
            if(bEnable == _ENABLE)
            {
                // HDCP 6803A Read INT Enable
                ScalerDpAuxRx0SetDpcdIntEnable(0x06, 0x80, 0x3A, 1, _DP_AUX_RX_DPCD_INT_READ, _ENABLE);
            }
            else
            {
                // HDCP 6803A Read INT Disable
                ScalerDpAuxRx0SetDpcdIntEnable(0x06, 0x80, 0x3A, 1, _DP_AUX_RX_DPCD_INT_READ, _DISABLE);
            }
#else
            if(bEnable == _ENABLE)
            {
                CLR_DP_AUX_RX0_HDCP_KSV_FIFO_INT_FLAG();

                // HDCP 68XXX INT Read/Write Switch
                Scaler32SetBit(PB18001_80_AUX_HDCP_01, ~_BIT9, _BIT9);

                // HDCP 6803A Read INT En
                Scaler32SetBit(PB18001_88_AUX_HDCP_IRQ_EN, ~_BIT10, _BIT10);
            }
            else
            {
                // HDCP 68XXX INT Read/Write Switch
                Scaler32SetBit(PB18001_80_AUX_HDCP_01, ~_BIT9, 0x00);

                // HDCP 6803A Read INT En
                Scaler32SetBit(PB18001_88_AUX_HDCP_IRQ_EN, ~_BIT10, 0x00);
            }
#endif

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
            if(bEnable == _ENABLE)
            {
                // HDCP 6803A Read INT Enable
                ScalerDpAuxRx1SetDpcdIntEnable(0x06, 0x80, 0x3A, 1, _DP_AUX_RX_DPCD_INT_READ, _ENABLE);
            }
            else
            {
                // HDCP 6803A Read INT Disable
                ScalerDpAuxRx1SetDpcdIntEnable(0x06, 0x80, 0x3A, 1, _DP_AUX_RX_DPCD_INT_READ, _DISABLE);
            }
#else
            if(bEnable == _ENABLE)
            {
                CLR_DP_AUX_RX1_HDCP_KSV_FIFO_INT_FLAG();

                // HDCP 68XXX INT Read/Write Switch
                Scaler32SetBit(PB19001_80_AUX_HDCP_01, ~_BIT9, _BIT9);

                // HDCP 6803A Read INT En
                Scaler32SetBit(PB19001_88_AUX_HDCP_IRQ_EN, ~_BIT10, _BIT10);
            }
            else
            {
                // HDCP 68XXX INT Read/Write Switch
                Scaler32SetBit(PB19001_80_AUX_HDCP_01, ~_BIT9, 0x00);

                // HDCP 6803A Read INT En
                Scaler32SetBit(PB19001_88_AUX_HDCP_IRQ_EN, ~_BIT10, 0x00);
            }
#endif

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
            if(bEnable == _ENABLE)
            {
                // HDCP 6803A Read INT Enable
                ScalerDpAuxRx2SetDpcdIntEnable(0x06, 0x80, 0x3A, 1, _DP_AUX_RX_DPCD_INT_READ, _ENABLE);
            }
            else
            {
                // HDCP 6803A Read INT Disable
                ScalerDpAuxRx2SetDpcdIntEnable(0x06, 0x80, 0x3A, 1, _DP_AUX_RX_DPCD_INT_READ, _DISABLE);
            }
#else
            if(bEnable == _ENABLE)
            {
                CLR_DP_AUX_RX2_HDCP_KSV_FIFO_INT_FLAG();

                // HDCP 68XXX INT Read/Write Switch
                Scaler32SetBit(PB1A001_80_AUX_HDCP_01, ~_BIT9, _BIT9);

                // HDCP 6803A Read INT En
                Scaler32SetBit(PB1A001_88_AUX_HDCP_IRQ_EN, ~_BIT10, _BIT10);
            }
            else
            {
                // HDCP 68XXX INT Read/Write Switch
                Scaler32SetBit(PB1A001_80_AUX_HDCP_01, ~_BIT9, 0x00);

                // HDCP 6803A Read INT En
                Scaler32SetBit(PB1A001_88_AUX_HDCP_IRQ_EN, ~_BIT10, 0x00);
            }
#endif

            break;
#endif
        default:

            break;
    }
}
#endif

//--------------------------------------------------
// Description  : Initial Setting for DP AUX
// Input Value  : enumDpVersion, enumDpLaneCount, enumDpRxMstPort, enumDisplayMode, enumFreeSyncSupport
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxSetHdcp14DpcdBksv(void)
{
#if(_D0_DP_SUPPORT == _ON)
    ScalerDpAuxRxSetDpcdValue(_D0_INPUT_PORT, 0x06, 0x80, 0x00, g_pucSyncHdcpBksvBackup[0]);
    ScalerDpAuxRxSetDpcdValue(_D0_INPUT_PORT, 0x06, 0x80, 0x01, g_pucSyncHdcpBksvBackup[1]);
    ScalerDpAuxRxSetDpcdValue(_D0_INPUT_PORT, 0x06, 0x80, 0x02, g_pucSyncHdcpBksvBackup[2]);
    ScalerDpAuxRxSetDpcdValue(_D0_INPUT_PORT, 0x06, 0x80, 0x03, g_pucSyncHdcpBksvBackup[3]);
    ScalerDpAuxRxSetDpcdValue(_D0_INPUT_PORT, 0x06, 0x80, 0x04, g_pucSyncHdcpBksvBackup[4]);
#endif

#if(_D1_DP_SUPPORT == _ON)
    ScalerDpAuxRxSetDpcdValue(_D1_INPUT_PORT, 0x06, 0x80, 0x00, g_pucSyncHdcpBksvBackup[0]);
    ScalerDpAuxRxSetDpcdValue(_D1_INPUT_PORT, 0x06, 0x80, 0x01, g_pucSyncHdcpBksvBackup[1]);
    ScalerDpAuxRxSetDpcdValue(_D1_INPUT_PORT, 0x06, 0x80, 0x02, g_pucSyncHdcpBksvBackup[2]);
    ScalerDpAuxRxSetDpcdValue(_D1_INPUT_PORT, 0x06, 0x80, 0x03, g_pucSyncHdcpBksvBackup[3]);
    ScalerDpAuxRxSetDpcdValue(_D1_INPUT_PORT, 0x06, 0x80, 0x04, g_pucSyncHdcpBksvBackup[4]);
#endif

#if(_D2_DP_SUPPORT == _ON)
    ScalerDpAuxRxSetDpcdValue(_D2_INPUT_PORT, 0x06, 0x80, 0x00, g_pucSyncHdcpBksvBackup[0]);
    ScalerDpAuxRxSetDpcdValue(_D2_INPUT_PORT, 0x06, 0x80, 0x01, g_pucSyncHdcpBksvBackup[1]);
    ScalerDpAuxRxSetDpcdValue(_D2_INPUT_PORT, 0x06, 0x80, 0x02, g_pucSyncHdcpBksvBackup[2]);
    ScalerDpAuxRxSetDpcdValue(_D2_INPUT_PORT, 0x06, 0x80, 0x03, g_pucSyncHdcpBksvBackup[3]);
    ScalerDpAuxRxSetDpcdValue(_D2_INPUT_PORT, 0x06, 0x80, 0x04, g_pucSyncHdcpBksvBackup[4]);
#endif
}

//--------------------------------------------------
// Description  : Get Rx FEC Status
// Input Value  : None
// Output Value : True or False
//--------------------------------------------------
bit ScalerDpAuxRxGetFecStatus(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

#if(_DP_AUX_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(g_enumDpAuxRx0CodingType == _CODING_TYPE_128B132B)
            {
                return _TRUE;
            }
            else
#endif
            {
                if((ScalerDpAuxRx0GetDpcdBitInfo(0x00, 0x00, 0x90, _BIT0) == _BIT0) &&
                   (ScalerDpAuxRx0GetDpcdBitInfo(0x00, 0x01, 0x20, _BIT0) == _BIT0))
                {
                    return _TRUE;
                }
            }

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

#if(_DP_AUX_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(g_enumDpAuxRx1CodingType == _CODING_TYPE_128B132B)
            {
                return _TRUE;
            }
            else
#endif
            {
                if((ScalerDpAuxRx1GetDpcdBitInfo(0x00, 0x00, 0x90, _BIT0) == _BIT0) &&
                   (ScalerDpAuxRx1GetDpcdBitInfo(0x00, 0x01, 0x20, _BIT0) == _BIT0))
                {
                    return _TRUE;
                }
            }

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

#if(_DP_AUX_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(g_enumDpAuxRx2CodingType == _CODING_TYPE_128B132B)
            {
                return _TRUE;
            }
            else
#endif
            {
                if((ScalerDpAuxRx2GetDpcdBitInfo(0x00, 0x00, 0x90, _BIT0) == _BIT0) &&
                   (ScalerDpAuxRx2GetDpcdBitInfo(0x00, 0x01, 0x20, _BIT0) == _BIT0))
                {
                    return _TRUE;
                }
            }

            break;
#endif
        default:

            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Get DPCD Table Information
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
// Output Value : DPCD Information
//--------------------------------------------------
BYTE ScalerDpAuxRxGetDpcdInfo(EnumInputPort enumInputPort, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            return ScalerDpAuxRx0GetDpcdInfo(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL);

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            return ScalerDpAuxRx1GetDpcdInfo(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL);

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            return ScalerDpAuxRx2GetDpcdInfo(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL);

            break;
#endif
        default:

            break;
    }

    return 0x00;
}

//--------------------------------------------------
// Description  : Get DPCD Table Information
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
// Output Value : DPCD Information
//--------------------------------------------------
BYTE ScalerDpAuxRxGetDpcdBitInfo(EnumInputPort enumInputPort, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdBit)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            return ScalerDpAuxRx0GetDpcdBitInfo(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdBit);
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            return ScalerDpAuxRx1GetDpcdBitInfo(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdBit);
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            return ScalerDpAuxRx2GetDpcdBitInfo(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdBit);
#endif
        default:

            return 0x00;
    }
}

//--------------------------------------------------
// Description  : Set DPCD Table Information
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
//                ucDpcdValue --> DPCD Value
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxSetDpcdValue(EnumInputPort enumInputPort, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpAuxRx0SetDpcdValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpAuxRx1SetDpcdValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpAuxRx2SetDpcdValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);

            break;
#endif

#if((_DP_AUX_RX0_SUPPORT == _ON) && (_DP_AUX_RX1_SUPPORT == _ON))
        case _RX7:

            ScalerDpAuxRx0SetDpcdValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);
            ScalerDpAuxRx1SetDpcdValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);

            break;
#endif

#if((_DP_AUX_RX1_SUPPORT == _ON) && (_DP_AUX_RX2_SUPPORT == _ON))
        case _RX8:

            ScalerDpAuxRx1SetDpcdValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);
            ScalerDpAuxRx2SetDpcdValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Set DPCD Table Information
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
//                ucDpcdValue --> DPCD Value
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxSetDpcdWriteValue(EnumInputPort enumInputPort, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpAuxRx0SetDpcdWriteValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpAuxRx1SetDpcdWriteValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpAuxRx2SetDpcdWriteValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);

            break;
#endif

#if((_DP_AUX_RX0_SUPPORT == _ON) && (_DP_AUX_RX1_SUPPORT == _ON))
        case _RX7:

            ScalerDpAuxRx0SetDpcdWriteValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);
            ScalerDpAuxRx1SetDpcdWriteValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);

            break;
#endif

#if((_DP_AUX_RX1_SUPPORT == _ON) && (_DP_AUX_RX2_SUPPORT == _ON))
        case _RX8:

            ScalerDpAuxRx1SetDpcdWriteValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);
            ScalerDpAuxRx2SetDpcdWriteValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Set DPCD Table Information
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
//                ucDpcdValue --> DPCD Value
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxSetDpcdWrite1ClearValue(EnumInputPort enumInputPort, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpAuxRx0SetDpcdWrite1ClearValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpAuxRx1SetDpcdWrite1ClearValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpAuxRx2SetDpcdWrite1ClearValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);

            break;
#endif

#if((_DP_AUX_RX0_SUPPORT == _ON) && (_DP_AUX_RX1_SUPPORT == _ON))
        case _RX7:

            ScalerDpAuxRx0SetDpcdWrite1ClearValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);
            ScalerDpAuxRx1SetDpcdWrite1ClearValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);

            break;
#endif

#if((_DP_AUX_RX1_SUPPORT == _ON) && (_DP_AUX_RX2_SUPPORT == _ON))
        case _RX8:

            ScalerDpAuxRx1SetDpcdWrite1ClearValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);
            ScalerDpAuxRx2SetDpcdWrite1ClearValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Set DPCD Table Information
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
//                ucDpcdValue --> DPCD Value
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxSetDpcdBitValue(EnumInputPort enumInputPort, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpAuxRx0SetDpcdBitValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpAuxRx1SetDpcdBitValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpAuxRx2SetDpcdBitValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);

            break;
#endif

#if((_DP_AUX_RX0_SUPPORT == _ON) && (_DP_AUX_RX1_SUPPORT == _ON))
        case _RX7:

            ScalerDpAuxRx0SetDpcdBitValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);
            ScalerDpAuxRx1SetDpcdBitValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);

            break;
#endif

#if((_DP_AUX_RX1_SUPPORT == _ON) && (_DP_AUX_RX2_SUPPORT == _ON))
        case _RX8:

            ScalerDpAuxRx1SetDpcdBitValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);
            ScalerDpAuxRx2SetDpcdBitValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Set DPCD Table Information
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
//                ucDpcdValue --> DPCD Value
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxSetDpcdBitWriteValue(EnumInputPort enumInputPort, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpAuxRx0SetDpcdBitWriteValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpAuxRx1SetDpcdBitWriteValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpAuxRx2SetDpcdBitWriteValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);

            break;
#endif

#if((_DP_AUX_RX0_SUPPORT == _ON) && (_DP_AUX_RX1_SUPPORT == _ON))
        case _RX7:

            ScalerDpAuxRx0SetDpcdBitWriteValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);
            ScalerDpAuxRx1SetDpcdBitWriteValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);

            break;
#endif

#if((_DP_AUX_RX1_SUPPORT == _ON) && (_DP_AUX_RX2_SUPPORT == _ON))
        case _RX8:

            ScalerDpAuxRx1SetDpcdBitWriteValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);
            ScalerDpAuxRx2SetDpcdBitWriteValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Set DPCD Table Information
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
//                ucDpcdValue --> DPCD Value
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxSetDpcdBitWrite1ClearValue(EnumInputPort enumInputPort, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpAuxRx0SetDpcdBitWrite1ClearValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpAuxRx1SetDpcdBitWrite1ClearValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpAuxRx2SetDpcdBitWrite1ClearValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);

            break;
#endif

#if((_DP_AUX_RX0_SUPPORT == _ON) && (_DP_AUX_RX1_SUPPORT == _ON))
        case _RX7:

            ScalerDpAuxRx0SetDpcdBitWrite1ClearValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);
            ScalerDpAuxRx1SetDpcdBitWrite1ClearValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);

            break;
#endif

#if((_DP_AUX_RX1_SUPPORT == _ON) && (_DP_AUX_RX2_SUPPORT == _ON))
        case _RX8:

            ScalerDpAuxRx1SetDpcdBitWrite1ClearValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);
            ScalerDpAuxRx2SetDpcdBitWrite1ClearValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Set DPCD Table Information, Use For Dpcd Need Manual Mapping
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
//                ucDpcdValue --> DPCD Value
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxSetDpcdMirrorValue(EnumInputPort enumInputPort, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpAuxRx0SetDpcdMirrorValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpAuxRx1SetDpcdMirrorValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpAuxRx2SetDpcdMirrorValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);

            break;
#endif

#if((_DP_AUX_RX0_SUPPORT == _ON) && (_DP_AUX_RX1_SUPPORT == _ON))
        case _RX7:

            ScalerDpAuxRx0SetDpcdMirrorValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);
            ScalerDpAuxRx1SetDpcdMirrorValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);

            break;
#endif

#if((_DP_AUX_RX1_SUPPORT == _ON) && (_DP_AUX_RX2_SUPPORT == _ON))
        case _RX8:

            ScalerDpAuxRx1SetDpcdMirrorValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);
            ScalerDpAuxRx2SetDpcdMirrorValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Set DPCD Table Information, Use For Dpcd Need Manual Mapping
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
//                ucDpcdValue --> DPCD Value
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxSetDpcdMirrorWriteValue(EnumInputPort enumInputPort, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpAuxRx0SetDpcdMirrorWriteValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpAuxRx1SetDpcdMirrorWriteValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpAuxRx2SetDpcdMirrorWriteValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);

            break;
#endif

#if((_DP_AUX_RX0_SUPPORT == _ON) && (_DP_AUX_RX1_SUPPORT == _ON))
        case _RX7:

            ScalerDpAuxRx0SetDpcdMirrorWriteValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);
            ScalerDpAuxRx1SetDpcdMirrorWriteValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);

            break;
#endif

#if((_DP_AUX_RX1_SUPPORT == _ON) && (_DP_AUX_RX2_SUPPORT == _ON))
        case _RX8:

            ScalerDpAuxRx1SetDpcdMirrorWriteValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);
            ScalerDpAuxRx2SetDpcdMirrorWriteValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Set DPCD Table Information, Use For Dpcd Need Manual Mapping
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
//                ucDpcdValue --> DPCD Value
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxSetDpcdMirrorWrite1ClearValue(EnumInputPort enumInputPort, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpAuxRx0SetDpcdMirrorWrite1ClearValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpAuxRx1SetDpcdMirrorWrite1ClearValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpAuxRx2SetDpcdMirrorWrite1ClearValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);

            break;
#endif

#if((_DP_AUX_RX0_SUPPORT == _ON) && (_DP_AUX_RX1_SUPPORT == _ON))
        case _RX7:

            ScalerDpAuxRx0SetDpcdMirrorWrite1ClearValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);
            ScalerDpAuxRx1SetDpcdMirrorWrite1ClearValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);

            break;
#endif

#if((_DP_AUX_RX1_SUPPORT == _ON) && (_DP_AUX_RX2_SUPPORT == _ON))
        case _RX8:

            ScalerDpAuxRx1SetDpcdMirrorWrite1ClearValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);
            ScalerDpAuxRx2SetDpcdMirrorWrite1ClearValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Set DPCD Table Information, Use For Dpcd Need Manual Mapping
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
//                ucDpcdValue --> DPCD Value
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxSetDpcdMirrorBitValue(EnumInputPort enumInputPort, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpAuxRx0SetDpcdMirrorBitValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpAuxRx1SetDpcdMirrorBitValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpAuxRx2SetDpcdMirrorBitValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);

            break;
#endif

#if((_DP_AUX_RX0_SUPPORT == _ON) && (_DP_AUX_RX1_SUPPORT == _ON))
        case _RX7:

            ScalerDpAuxRx0SetDpcdMirrorBitValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);
            ScalerDpAuxRx1SetDpcdMirrorBitValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);

            break;
#endif

#if((_DP_AUX_RX1_SUPPORT == _ON) && (_DP_AUX_RX2_SUPPORT == _ON))
        case _RX8:

            ScalerDpAuxRx1SetDpcdMirrorBitValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);
            ScalerDpAuxRx2SetDpcdMirrorBitValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Set DPCD Table Information, Use For Dpcd Need Manual Mapping
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
//                ucDpcdValue --> DPCD Value
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxSetDpcdMirrorBitWriteValue(EnumInputPort enumInputPort, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpAuxRx0SetDpcdMirrorBitWriteValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpAuxRx1SetDpcdMirrorBitWriteValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpAuxRx2SetDpcdMirrorBitWriteValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);

            break;
#endif

#if((_DP_AUX_RX0_SUPPORT == _ON) && (_DP_AUX_RX1_SUPPORT == _ON))
        case _RX7:

            ScalerDpAuxRx0SetDpcdMirrorBitWriteValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);
            ScalerDpAuxRx1SetDpcdMirrorBitWriteValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);

            break;
#endif

#if((_DP_AUX_RX1_SUPPORT == _ON) && (_DP_AUX_RX2_SUPPORT == _ON))
        case _RX8:

            ScalerDpAuxRx1SetDpcdMirrorBitWriteValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);
            ScalerDpAuxRx2SetDpcdMirrorBitWriteValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Set DPCD Table Information, Use For Dpcd Need Manual Mapping
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
//                ucDpcdValue --> DPCD Value
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxSetDpcdMirrorBitWrite1ClearValue(EnumInputPort enumInputPort, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpAuxRx0SetDpcdMirrorBitWrite1ClearValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpAuxRx1SetDpcdMirrorBitWrite1ClearValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpAuxRx2SetDpcdMirrorBitWrite1ClearValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);

            break;
#endif

#if((_DP_AUX_RX0_SUPPORT == _ON) && (_DP_AUX_RX1_SUPPORT == _ON))
        case _RX7:

            ScalerDpAuxRx0SetDpcdMirrorBitWrite1ClearValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);
            ScalerDpAuxRx1SetDpcdMirrorBitWrite1ClearValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);

            break;
#endif

#if((_DP_AUX_RX1_SUPPORT == _ON) && (_DP_AUX_RX2_SUPPORT == _ON))
        case _RX8:

            ScalerDpAuxRx1SetDpcdMirrorBitWrite1ClearValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);
            ScalerDpAuxRx2SetDpcdMirrorBitWrite1ClearValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Set DPCD Table Information
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
//                ucDpcdValue --> DPCD Value
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxDpcdGroupReset(EnumInputPort enumInputPort, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucLen)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpAuxRx0DpcdGroupReset(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucLen);

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpAuxRx1DpcdGroupReset(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucLen);

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpAuxRx2DpcdGroupReset(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucLen);

            break;
#endif

#if((_DP_AUX_RX0_SUPPORT == _ON) && (_DP_AUX_RX1_SUPPORT == _ON))
        case _RX7:

            ScalerDpAuxRx0DpcdGroupReset(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucLen);
            ScalerDpAuxRx1DpcdGroupReset(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucLen);

            break;
#endif

#if((_DP_AUX_RX1_SUPPORT == _ON) && (_DP_AUX_RX2_SUPPORT == _ON))
        case _RX8:

            ScalerDpAuxRx1DpcdGroupReset(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucLen);
            ScalerDpAuxRx2DpcdGroupReset(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucLen);

            break;
#endif

        default:

            break;
    }
}

#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set DPCD Table Config
// Input Value  : ucDpcdAccessPortH        --> High Byte of DPCD Address
//                ucDpcdAccessPortM        --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL        --> Low Bye of DPCD Adress
//                enumDpAuxRxDpcdConfig --> DPCD W / R / WR INT Enable
//                ucDpcdLen                --> Setting N = Len + 1 Dpcd Addr Int Enable
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxSetDpcdIntEnable(EnumInputPort enumInputPort, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdLen, EnumDpAuxRxDpcdInt enumDpAuxRxDpcdInt, bit bEnable)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpAuxRx0SetDpcdIntEnable(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdLen, enumDpAuxRxDpcdInt, bEnable);

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpAuxRx1SetDpcdIntEnable(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdLen, enumDpAuxRxDpcdInt, bEnable);

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpAuxRx2SetDpcdIntEnable(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdLen, enumDpAuxRxDpcdInt, bEnable);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Get Dpcd Mirror Address
// Input Value  : Dpcd Address
// Output Value : Mirror Address
//--------------------------------------------------
DWORD ScalerDpAuxRxDpcdGetMirrorAddr(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL)
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

#if(_DP_RX_DSC_DECODER_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set DPCD Table Information
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxDscDpcdSetting(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_DSC_DECODER_SUPPORT == _ON)
        case _RX0:
            ScalerDpAuxRx0DscDpcdSetting();
            break;
#endif

#if(_DP_AUX_RX1_DSC_DECODER_SUPPORT == _ON)
        case _RX1:
            ScalerDpAuxRx1DscDpcdSetting();
            break;
#endif

#if(_DP_AUX_RX2_DSC_DECODER_SUPPORT == _ON)
        case _RX2:
            ScalerDpAuxRx2DscDpcdSetting();
            break;
#endif

#if(_DP_AUX_RX7_DSC_DECODER_SUPPORT == _ON)
        case _RX7:
            ScalerDpAuxRx0DscDpcdSetting();
            ScalerDpAuxRx1DscDpcdSetting();
            break;
#endif

#if(_DP_AUX_RX8_DSC_DECODER_SUPPORT == _ON)
        case _RX8:
            ScalerDpAuxRx1DscDpcdSetting();
            ScalerDpAuxRx2DscDpcdSetting();
            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Set DPCD Table Information
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxDscDpcdExtendedCapSetting(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_DSC_DECODER_SUPPORT == _ON)
        case _RX0:
            ScalerDpAuxRx0DscDpcdExtendedCapSetting();
            break;
#endif

#if(_DP_AUX_RX1_DSC_DECODER_SUPPORT == _ON)
        case _RX1:
            ScalerDpAuxRx1DscDpcdExtendedCapSetting();
            break;
#endif

#if(_DP_AUX_RX2_DSC_DECODER_SUPPORT == _ON)
        case _RX2:
            ScalerDpAuxRx2DscDpcdExtendedCapSetting();
            break;
#endif

#if(_DP_AUX_RX7_DSC_DECODER_SUPPORT == _ON)
        case _RX7:
            ScalerDpAuxRx0DscDpcdExtendedCapSetting();
            ScalerDpAuxRx1DscDpcdExtendedCapSetting();
            break;
#endif

#if(_DP_AUX_RX8_DSC_DECODER_SUPPORT == _ON)
        case _RX8:
            ScalerDpAuxRx1DscDpcdExtendedCapSetting();
            ScalerDpAuxRx2DscDpcdExtendedCapSetting();
            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : DP Aux Rx DSC Irq Control
// Input Value  : enumInputPort, bEnable
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxDscIrqCtrl(EnumInputPort enumInputPort, bit bEnable)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:
#if(_DP_AUX_RX0_DSC_DECODER_SUPPORT == _ON)
            ScalerDpAuxRx0DscIrqCtrl(bEnable);
#endif
            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:
#if(_DP_AUX_RX1_DSC_DECODER_SUPPORT == _ON)
            ScalerDpAuxRx1DscIrqCtrl(bEnable);
#endif
            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:
#if(_DP_AUX_RX2_DSC_DECODER_SUPPORT == _ON)
            ScalerDpAuxRx2DscIrqCtrl(bEnable);
#endif
            break;
#endif

#if((_DP_AUX_RX0_SUPPORT == _ON) && (_DP_AUX_RX1_SUPPORT == _ON))
        case _RX7:
#if(_DP_AUX_RX7_DSC_DECODER_SUPPORT == _ON)
            ScalerDpAuxRx0DscIrqCtrl(bEnable);
            ScalerDpAuxRx1DscIrqCtrl(bEnable);
#endif
            break;
#endif

#if((_DP_AUX_RX1_SUPPORT == _ON) && (_DP_AUX_RX2_SUPPORT == _ON))
        case _RX8:
#if(_DP_AUX_RX8_DSC_DECODER_SUPPORT == _ON)
            ScalerDpAuxRx1DscIrqCtrl(bEnable);
            ScalerDpAuxRx2DscIrqCtrl(bEnable);
#endif
            break;
#endif

        default:

            break;
    }
}
#endif // End of #if(_DP_RX_DSC_DECODER_SUPPORT == _ON)

#if(_DP_RX_FEC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set DPCD Table Information
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxFecDpcdSetting(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:
            ScalerDpAuxRx0FecDpcdSetting();
            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:
            ScalerDpAuxRx1FecDpcdSetting();
            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:
            ScalerDpAuxRx2FecDpcdSetting();
            break;
#endif

#if((_DP_AUX_RX0_SUPPORT == _ON) && (_DP_AUX_RX1_SUPPORT == _ON))
        case _RX7:
            ScalerDpAuxRx0FecDpcdSetting();
            ScalerDpAuxRx1FecDpcdSetting();
            break;
#endif

#if((_DP_AUX_RX1_SUPPORT == _ON) && (_DP_AUX_RX2_SUPPORT == _ON))
        case _RX8:
            ScalerDpAuxRx1FecDpcdSetting();
            ScalerDpAuxRx2FecDpcdSetting();
            break;
#endif

        default:
            break;
    }
}
#endif

#if(_AUDIO_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Dp Audio Capability Switch Process
// Input Value  : Input Port
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpAuxRxAudioCapabilitySwitchProc(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _D0_INPUT_PORT:

            if(ScalerAudioDpGetCapabilityChange(_D0_INPUT_PORT) == _TRUE)
            {
                if(ScalerAudioDpGetCapabilityState(_D0_INPUT_PORT) == _AUDIO_DP_DPCD_SUPPORT)
                {
                    ScalerDpAuxRxSetDpcdMirrorValue(_D0_INPUT_PORT, 0x00, 0x00, 0x04, 0x01);

                    ScalerDpAuxRxSetDpcdMirrorValue(_D0_INPUT_PORT, 0x00, 0x00, 0x0A, 0x06);
                }
                else
                {
                    ScalerDpAuxRxSetDpcdMirrorValue(_D0_INPUT_PORT, 0x00, 0x00, 0x04, 0x00);

                    ScalerDpAuxRxSetDpcdMirrorValue(_D0_INPUT_PORT, 0x00, 0x00, 0x0A, 0x00);
                }

                return _TRUE;
            }

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            if(ScalerAudioDpGetCapabilityChange(_D1_INPUT_PORT) == _TRUE)
            {
                if(ScalerAudioDpGetCapabilityState(_D1_INPUT_PORT) == _AUDIO_DP_DPCD_SUPPORT)
                {
                    ScalerDpAuxRxSetDpcdMirrorValue(_D1_INPUT_PORT, 0x00, 0x00, 0x04, 0x01);

                    ScalerDpAuxRxSetDpcdMirrorValue(_D1_INPUT_PORT, 0x00, 0x00, 0x0A, 0x06);
                }
                else
                {
                    ScalerDpAuxRxSetDpcdMirrorValue(_D1_INPUT_PORT, 0x00, 0x00, 0x04, 0x00);

                    ScalerDpAuxRxSetDpcdMirrorValue(_D1_INPUT_PORT, 0x00, 0x00, 0x0A, 0x00);
                }

                return _TRUE;
            }

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _D2_INPUT_PORT:

            if(ScalerAudioDpGetCapabilityChange(_D2_INPUT_PORT) == _TRUE)
            {
                if(ScalerAudioDpGetCapabilityState(_D2_INPUT_PORT) == _AUDIO_DP_DPCD_SUPPORT)
                {
                    ScalerDpAuxRxSetDpcdMirrorValue(_D2_INPUT_PORT, 0x00, 0x00, 0x04, 0x01);

                    ScalerDpAuxRxSetDpcdMirrorValue(_D2_INPUT_PORT, 0x00, 0x00, 0x0A, 0x06);
                }
                else
                {
                    ScalerDpAuxRxSetDpcdMirrorValue(_D2_INPUT_PORT, 0x00, 0x00, 0x04, 0x00);

                    ScalerDpAuxRxSetDpcdMirrorValue(_D2_INPUT_PORT, 0x00, 0x00, 0x0A, 0x00);
                }

                return _TRUE;
            }

            break;
#endif

        default:

            break;
    }

    return _FALSE;
}
#endif // End of #if(_AUDIO_SUPPORT == _ON)

//--------------------------------------------------
// Description  : Get DP Rx Aux Manual Mode Status
// Input Value  : enumInputPort
// Output Value : Byte
//--------------------------------------------------
EnumDpAuxRxModeStatus ScalerDpAuxRxGetAuxModeStatus(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            return GET_DP_AUX_RX0_MODE();
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            return GET_DP_AUX_RX1_MODE();
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            return GET_DP_AUX_RX2_MODE();
#endif
        default:

            return _DP_RX_AUX_AUTO_MODE;
    }
}

//--------------------------------------------------
// Description  : Check DP Link Training Occured or Not
// Input Value  : DP Input Port
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpAuxRxLinkTrainingOccur(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)

        case _RX0:

            return (Scaler32GetBit(_REG_DP_AUX_RX0_TPS_OCCR, (_BIT7 | _BIT6 | _BIT5)) != 0x00);
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)

        case _RX1:

            return (Scaler32GetBit(_REG_DP_AUX_RX1_TPS_OCCR, (_BIT7 | _BIT6 | _BIT5)) != 0x00);
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)

        case _RX2:

            return (Scaler32GetBit(_REG_DP_AUX_RX2_TPS_OCCR, (_BIT7 | _BIT6 | _BIT5)) != 0x00);
#endif
        default:

            return (Scaler32GetBit(_REG_DP_AUX_RX0_TPS_OCCR, (_BIT7 | _BIT6 | _BIT5)) != 0x00);
    }
}

//--------------------------------------------------
// Description  : DP Aux Get Link Training Status
// Input Value  : None
// Output Value : Link Training Status
//--------------------------------------------------
BYTE ScalerDpAuxRxGetLTStatus(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
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
void ScalerDpAuxRxSetLTStatus(EnumInputPort enumInputPort, BYTE ucLTStatusSet)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
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
// Description  : Get DP Lane Count (DPCD 00101h)
// Input Value  : DP Input Port
// Output Value : DP Lane Count
//--------------------------------------------------
EnumDpLaneCount ScalerDpAuxRxGetDpcdLaneCount(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            return (ScalerDpAuxRx0GetDpcdBitInfo(0x00, 0x01, 0x01, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)));
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            return (ScalerDpAuxRx1GetDpcdBitInfo(0x00, 0x01, 0x01, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)));
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            return (ScalerDpAuxRx2GetDpcdBitInfo(0x00, 0x01, 0x01, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)));
#endif
        default:

            return _DP_LINK_4_LANE;
    }
}

//--------------------------------------------------
// Description  : Get DP Link Rate (DPCD 00100h)
// Input Value  : DP Input Port
// Output Value : DP Link Rate
//--------------------------------------------------
EnumDpLinkRate ScalerDpAuxRxGetDpcdLinkRate(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x00, 0x01, 0x00))
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
EnumDpLinkRate ScalerDpAuxRxGetLinkRate(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
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
// Description  : Get Link Training Lane Count
// Input Value  : SearchPort
// Output Value : Lane Count
//--------------------------------------------------
EnumDpLaneCount ScalerDpAuxRxGetLaneCount(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            return g_enumDpAuxRx0LaneCount;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            return g_enumDpAuxRx1LaneCount;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            return g_enumDpAuxRx2LaneCount;
#endif
        default:

            return _DP_LINK_NO_LANE;
    }
}

//--------------------------------------------------
// Description  : Set Link Training Link Rate
// Input Value  : SearchPort
// Output Value : Link Rate
//--------------------------------------------------
void ScalerDpAuxRxSetLinkRate(EnumInputPort enumInputPort, BYTE ucLinkRate)
{
    ucLinkRate = ucLinkRate;

    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            g_enumDpAuxRx0LinkRate = ucLinkRate;

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            g_enumDpAuxRx1LinkRate = ucLinkRate;

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            g_enumDpAuxRx2LinkRate = ucLinkRate;

            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Set Link Training Lane Count
// Input Value  : SearchPort
// Output Value : Link Rate
//--------------------------------------------------
void ScalerDpAuxRxSetLaneCount(EnumInputPort enumInputPort, BYTE ucLaneCount)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            g_enumDpAuxRx0LaneCount = ucLaneCount;

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            g_enumDpAuxRx1LaneCount = ucLaneCount;

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            g_enumDpAuxRx2LaneCount = ucLaneCount;

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
EnumDpLinkChannelCodingType ScalerDpAuxRxGetCodingType(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
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

//--------------------------------------------------
// Description  : Set Link Training Coding Type
// Input Value  : SearchPort, Coding Type
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxSetCodingType(EnumInputPort enumInputPort, EnumDpLinkChannelCodingType enumCodingType)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
        case _RX0:
            ScalerDpAuxRx0SetCodingType(enumCodingType);
            break;
#endif

#if(_DP_AUX_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
        case _RX1:
            ScalerDpAuxRx1SetCodingType(enumCodingType);
            break;
#endif

#if(_DP_AUX_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
        case _RX2:
            ScalerDpAuxRx2SetCodingType(enumCodingType);
            break;
#endif
        default:
            break;
    }
}
#endif

//--------------------------------------------------
// Description  : Set Phy Finish Flag Setting
// Input Value  : enumInputPort, bSetPhyDone
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxSetLinkTrainingSetPhyFinishFlag(EnumInputPort enumInputPort, bit bSetPhyDone)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
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

//--------------------------------------------------
// Description  : Get Phy Finish Flag
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
bit ScalerDpAuxRxGetLinkTrainingSetPhyFinishFlag(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            return GET_DP_RX0_NORMAL_LINK_TRAINING_SETPHY_FINISH();
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            return GET_DP_RX1_NORMAL_LINK_TRAINING_SETPHY_FINISH();
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            return GET_DP_RX2_NORMAL_LINK_TRAINING_SETPHY_FINISH();
#endif

        default:

            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Get DP Voltage Swing Level(DPCD 00103h-00106h [1:0])
// Input Value  : DP Input Port, Lane #
// Output Value : DP Voltage Swing Level of the lane
//--------------------------------------------------
EnumDpVoltageSwingLevel ScalerDpAuxRxGetLaneVoltageSwingLv(EnumInputPort enumInputPort, EnumDpLane enumDpLane)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            return (ScalerDpAuxRx0GetDpcdBitInfo(0x00, 0x01, (0x03 + enumDpLane), (_BIT1 | _BIT0)));
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            return (ScalerDpAuxRx1GetDpcdBitInfo(0x00, 0x01, (0x03 + enumDpLane), (_BIT1 | _BIT0)));
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            return (ScalerDpAuxRx2GetDpcdBitInfo(0x00, 0x01, (0x03 + enumDpLane), (_BIT1 | _BIT0)));
#endif
        default:

            return 0;
    }
}

//--------------------------------------------------
// Description  : Get DP Pre-emphasis Level(DPCD 00103h-00106h [4:3])
// Input Value  : DP Input Port, Lane #
// Output Value : DP Pre-emphasis Level of the lane
//--------------------------------------------------
EnumDpPreEmphasisLevel ScalerDpAuxRxGetLanePreEmpLv(EnumInputPort enumInputPort, EnumDpLane enumDpLane)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            return (ScalerDpAuxRx0GetDpcdBitInfo(0x00, 0x01, (0x03 + enumDpLane), (_BIT4 | _BIT3)) >> 3);
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            return (ScalerDpAuxRx1GetDpcdBitInfo(0x00, 0x01, (0x03 + enumDpLane), (_BIT4 | _BIT3)) >> 3);
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            return (ScalerDpAuxRx2GetDpcdBitInfo(0x00, 0x01, (0x03 + enumDpLane), (_BIT4 | _BIT3)) >> 3);
#endif
        default:

            return 0;
    }
}

//--------------------------------------------------
// Description  : Enable Ignore Rx Error
// Input Value  : EnumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxErrorIgnore(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            Scaler32SetBit(_REG_DP_AUX_RX0_MAC_CTRL, ~_BIT14, _BIT14);

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            Scaler32SetBit(_REG_DP_AUX_RX1_MAC_CTRL, ~_BIT14, _BIT14);

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            Scaler32SetBit(_REG_DP_AUX_RX2_MAC_CTRL, ~_BIT14, _BIT14);

            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Clear DP Payload ID Table
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxClearPayload(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
            ScalerDpAuxRx0SetDpcdBitWrite1ClearValue(0x00, 0x02, 0xC0, ~(_BIT(7, 2)), 0x00);

            ScalerDpAuxRx0DpcdGroupReset(0x00, 0x02, 0xC1, 63);
#else
            Scaler32SetBit(PB18001_C0_AUX_PAYLOAD_CTRL, ~_BIT6, _BIT6);
            Scaler32SetBit(PB18001_C0_AUX_PAYLOAD_CTRL, ~_BIT6, 0x00);
#endif

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
            ScalerDpAuxRx1SetDpcdBitWrite1ClearValue(0x00, 0x02, 0xC0, ~(_BIT(7, 2)), 0x00);

            ScalerDpAuxRx1DpcdGroupReset(0x00, 0x02, 0xC1, 63);
#else
            Scaler32SetBit(PB19001_C0_AUX_PAYLOAD_CTRL, ~_BIT6, _BIT6);
            Scaler32SetBit(PB19001_C0_AUX_PAYLOAD_CTRL, ~_BIT6, 0x00);
#endif

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
            ScalerDpAuxRx2SetDpcdBitWrite1ClearValue(0x00, 0x02, 0xC0, ~(_BIT(7, 2)), 0x00);

            ScalerDpAuxRx2DpcdGroupReset(0x00, 0x02, 0xC1, 63);
#else
            Scaler32SetBit(PB1A001_C0_AUX_PAYLOAD_CTRL, ~_BIT6, _BIT6);
            Scaler32SetBit(PB1A001_C0_AUX_PAYLOAD_CTRL, ~_BIT6, 0x00);
#endif

            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Cancel DP Valid Signal Detection
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxCancelValidSignalDetection(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX0_VALID_SIGNAL_DETECT_CHECK);

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX1_VALID_SIGNAL_DETECT_CHECK);

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX2_VALID_SIGNAL_DETECT_CHECK);

            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Get DP Valid Video Check
// Input Value  : enumInputPort
// Output Value : True or False
//--------------------------------------------------
bit ScalerDpAuxRxGetValidVideoCheck(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            return GET_DP_AUX_RX0_VALID_VIDEO_CHECK();

#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            return GET_DP_AUX_RX1_VALID_VIDEO_CHECK();

#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            return GET_DP_AUX_RX2_VALID_VIDEO_CHECK();

#endif
        default:

            return _FALSE;
    }
}

//--------------------------------------------------
// Description  : Clr DP Valid Video Check
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxClrValidVideoCheck(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            CLR_DP_AUX_RX0_VALID_VIDEO_CHECK();

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            CLR_DP_AUX_RX1_VALID_VIDEO_CHECK();

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            CLR_DP_AUX_RX2_VALID_VIDEO_CHECK();

            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Reactive DP HDCP Long HPD
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxReactiveHdcpLongHotplug(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerTimerReactiveTimerEvent(SEC(1), _SCALER_TIMER_EVENT_DP_RX0_HDCP_LONG_HOTPLUG_EVENT);

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerTimerReactiveTimerEvent(SEC(1), _SCALER_TIMER_EVENT_DP_RX1_HDCP_LONG_HOTPLUG_EVENT);

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerTimerReactiveTimerEvent(SEC(1), _SCALER_TIMER_EVENT_DP_RX2_HDCP_LONG_HOTPLUG_EVENT);

            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Cancel DP HDCP Long HPD
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxCancelHdcpLongHotplug(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX0_HDCP_LONG_HOTPLUG_EVENT);

            ScalerDpHdcpRxClrHdcpCpirqFlag(enumInputPort);

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX1_HDCP_LONG_HOTPLUG_EVENT);

            ScalerDpHdcpRxClrHdcpCpirqFlag(enumInputPort);

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX2_HDCP_LONG_HOTPLUG_EVENT);

            ScalerDpHdcpRxClrHdcpCpirqFlag(enumInputPort);

            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Active DP IRQ
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxActiveLinkStatusIRQ(EnumInputPort enumInputPort)
{
    WORD usTime = 0;

    if(ScalerDpHdcpRxGetHdcpCpirqFlag(enumInputPort) == _TRUE)
    {
        ScalerDpHdcpRxClrHdcpCpirqFlag(enumInputPort);

        usTime = 350;
    }
    else
    {
        usTime = 100;
    }

    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerTimerActiveTimerEvent(usTime, _SCALER_TIMER_EVENT_DP_RX0_LINK_STATUS_IRQ);

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerTimerActiveTimerEvent(usTime, _SCALER_TIMER_EVENT_DP_RX1_LINK_STATUS_IRQ);

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerTimerActiveTimerEvent(usTime, _SCALER_TIMER_EVENT_DP_RX2_LINK_STATUS_IRQ);

            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Active DP WD Timer Event IRQ
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxActiveWDLinkStatusIRQ(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerTimerWDActivateTimerEvent(20, _SCALER_WD_TIMER_EVENT_RX0_DP_HPD_IRQ_ASSERT);

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerTimerWDActivateTimerEvent(20, _SCALER_WD_TIMER_EVENT_RX1_DP_HPD_IRQ_ASSERT);

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerTimerWDActivateTimerEvent(20, _SCALER_WD_TIMER_EVENT_RX2_DP_HPD_IRQ_ASSERT);

            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Cancel DP IRQ
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxCancelLinkStatusIRQ(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX0_LINK_STATUS_IRQ);

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX1_LINK_STATUS_IRQ);

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX2_LINK_STATUS_IRQ);

            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Get DP Aux Command No Reply
// Input Value  : enumInputPort
// Output Value : True or False
//--------------------------------------------------
bit ScalerDpAuxRxGetCommandNoReply(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            return GET_DP_AUX_RX0_COMMAND_NO_REPLY();

#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            return GET_DP_AUX_RX1_COMMAND_NO_REPLY();

#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            return GET_DP_AUX_RX2_COMMAND_NO_REPLY();

#endif
        default:

            return _FALSE;
    }
}

//--------------------------------------------------
// Description  : Clear DP Aux Command No Reply
// Input Value  : enumInputPort
// Output Value : True or False
//--------------------------------------------------
void ScalerDpAuxRxClearCommandNoReply(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            CLR_DP_AUX_RX0_COMMAND_NO_REPLY();

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            CLR_DP_AUX_RX1_COMMAND_NO_REPLY();

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            CLR_DP_AUX_RX2_COMMAND_NO_REPLY();

            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Get Link Training Pass
// Input Value  : enumInputPort
// Output Value : _TRUE: pass, _FALSE: fail
//--------------------------------------------------
bit ScalerDpAuxRxGetLinkTrainingPass(EnumInputPort enumInputPort)
{
    if(ScalerDpAuxRxGetLTStatus(enumInputPort) == _DP_NORMAL_LINK_TRAINING_PASS)
    {
        return _TRUE;
    }

    if(ScalerDpAuxRxGetLTStatus(enumInputPort) == _DP_FAKE_LINK_TRAINING_PASS)
    {
        return _TRUE;
    }

    return _FALSE;
}

#if(_DP_MST_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Check if Event is Valid
// Input Value  : ucEventIndex --> Event to be checked
// Output Value : Validity(_TRUE/_FALSE)
//--------------------------------------------------
void ScalerDpAuxRxSourceWritePowerUpProc(void)
{
#if(_DP_AUX_RX0_SUPPORT == _ON)
    if(GET_DP_AUX_RX0_SOURCE_WRITE_POWER_UP() == _DP_SOURCE_WRITE_POWER_UP_TRIGGERED)
    {
        DebugMessageRx0("Rx0 Source Writes 600h = 0x01", 0);

        ScalerTimerReactiveTimerEvent(SEC(3), _SCALER_TIMER_EVENT_DP_RX0_SOURCE_WRITE_POWER_UP_TIMEOUT);

        SET_DP_AUX_RX0_SOURCE_WRITE_POWER_UP(_DP_SOURCE_WRITE_POWER_UP_TIMER_ACTIVE);
    }
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
    if(GET_DP_AUX_RX1_SOURCE_WRITE_POWER_UP() == _DP_SOURCE_WRITE_POWER_UP_TRIGGERED)
    {
        DebugMessageRx1("Rx1 Source Writes 600h = 0x01", 0);

        ScalerTimerReactiveTimerEvent(SEC(3), _SCALER_TIMER_EVENT_DP_RX1_SOURCE_WRITE_POWER_UP_TIMEOUT);

        SET_DP_AUX_RX1_SOURCE_WRITE_POWER_UP(_DP_SOURCE_WRITE_POWER_UP_TIMER_ACTIVE);
    }
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
    if(GET_DP_AUX_RX2_SOURCE_WRITE_POWER_UP() == _DP_SOURCE_WRITE_POWER_UP_TRIGGERED)
    {
        DebugMessageRx2("Rx2 Source Writes 600h = 0x01", 0);

        ScalerTimerReactiveTimerEvent(SEC(3), _SCALER_TIMER_EVENT_DP_RX2_SOURCE_WRITE_POWER_UP_TIMEOUT);

        SET_DP_AUX_RX2_SOURCE_WRITE_POWER_UP(_DP_SOURCE_WRITE_POWER_UP_TIMER_ACTIVE);
    }
#endif
}

//--------------------------------------------------
// Description  : Get Aux Ch Power Status
// Input Value  : EnumInputPort
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
EnumDpRxAuxPowerStatus ScalerDpAuxRxGetAuxChPowerStatus(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            return GET_DP_AUX_RX0_CHECK_CH_POWER_STATUS();
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            return GET_DP_AUX_RX1_CHECK_CH_POWER_STATUS();
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            return GET_DP_AUX_RX2_CHECK_CH_POWER_STATUS();
#endif
        default:

            break;
    }

    return _DP_RX_AUX_POWER_STATUS_NONE;
}

//--------------------------------------------------
// Description  : Get Aux Ch Power On Wake Up
// Input Value  : EnumInputPort
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerDpAuxRxGetAuxChPowerOnWakeUp(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            return GET_DP_AUX_RX0_CH_POWER_ON_WAKE_UP();
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            return GET_DP_AUX_RX1_CH_POWER_ON_WAKE_UP();
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            return GET_DP_AUX_RX2_CH_POWER_ON_WAKE_UP();
#endif
        default:

            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Get Aux Source First Power On
// Input Value  : EnumInputPort
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerDpAuxRxGetSourceFirstPowerOn(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            return GET_DP_AUX_RX0_SOURCE_FIRST_POWER_ON();
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            return GET_DP_AUX_RX1_SOURCE_FIRST_POWER_ON();
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            return GET_DP_AUX_RX2_SOURCE_FIRST_POWER_ON();
#endif
        default:

            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Clear Aux Ch Power On Wake Up
// Input Value  : EnumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxClrAuxChPowerOnWakeUp(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            CLR_DP_AUX_RX0_CH_POWER_ON_WAKE_UP();

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            CLR_DP_AUX_RX1_CH_POWER_ON_WAKE_UP();

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            CLR_DP_AUX_RX2_CH_POWER_ON_WAKE_UP();

            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Clear Source First Power On
// Input Value  : EnumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxClrSourceFirstPowerOn(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            CLR_DP_AUX_RX0_SOURCE_FIRST_POWER_ON();

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            CLR_DP_AUX_RX1_SOURCE_FIRST_POWER_ON();

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            CLR_DP_AUX_RX2_SOURCE_FIRST_POWER_ON();

            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Get Aux Source Write Power Up
// Input Value  : EnumInputPort
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
EnumDpSourceWritePowerUpState ScalerDpAuxRxGetSourceWritePowerUp(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            return GET_DP_AUX_RX0_SOURCE_WRITE_POWER_UP();
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            return GET_DP_AUX_RX1_SOURCE_WRITE_POWER_UP();
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            return GET_DP_AUX_RX2_SOURCE_WRITE_POWER_UP();
#endif
        default:

            break;
    }

    return _DP_SOURCE_WRITE_POWER_UP_NONE;
}

//--------------------------------------------------
// Description  : Clear Check Aux Channel No Power Debounce
// Input Value  : EnumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxClrCheckChNoPowerDebounce(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            CLR_DP_AUX_RX0_CHECK_CH_NO_POWER_DEBOUNCE();

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            CLR_DP_AUX_RX1_CHECK_CH_NO_POWER_DEBOUNCE();

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            CLR_DP_AUX_RX2_CHECK_CH_NO_POWER_DEBOUNCE();

            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Clear Check Aux Channel Power Status
// Input Value  : EnumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxClrCheckChPowerStatus(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            CLR_DP_AUX_RX0_CHECK_CH_POWER_STATUS();

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            CLR_DP_AUX_RX1_CHECK_CH_POWER_STATUS();

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            CLR_DP_AUX_RX2_CHECK_CH_POWER_STATUS();

            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Clear Source Write Power Up
// Input Value  : EnumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxClrSourceWritePowerUp(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            CLR_DP_AUX_RX0_SOURCE_WRITE_POWER_UP();

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            CLR_DP_AUX_RX1_SOURCE_WRITE_POWER_UP();

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            CLR_DP_AUX_RX2_SOURCE_WRITE_POWER_UP();

            break;
#endif
        default:

            break;
    }
}
#endif

//--------------------------------------------------
// Description  : Get Aux Toggle
// Input Value  : EnumInputPort
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerDpAuxRxGetToggle(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            return GET_DP_AUX_RX0_TOGGLE();
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            return GET_DP_AUX_RX1_TOGGLE();
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            return GET_DP_AUX_RX2_TOGGLE();
#endif
        default:

            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Clear Aux Toggle
// Input Value  : EnumInputPort
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
void ScalerDpAuxRxClearToggle(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            CLR_DP_AUX_RX0_TOGGLE();

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            CLR_DP_AUX_RX1_TOGGLE();

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            CLR_DP_AUX_RX2_TOGGLE();

            break;
#endif
        default:

            break;
    }
}

#if(_DP_TX_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Dp Interrupt Request
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxSinkCountUpdate(EnumInputPort enumInputPort, BYTE ucSinkCount, bit bIrqAssert)
{
    BYTE ucRxPreSinkCount = ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x00, 0x02, 0x00);
    BYTE ucRxCurSinkCount = ((ucRxPreSinkCount & _BIT6) | ucSinkCount);

    ScalerDpAuxRxSetDpcdMirrorValue(enumInputPort, 0x00, 0x02, 0x00, ucRxCurSinkCount);

    if(ucSinkCount > 1)
    {
        ScalerDpRxDfpDeviceDetailConfig(enumInputPort);
    }
    else
    {
        ScalerDpRxDfpDeviceDetailConfigReset(enumInputPort);
    }

    if((bIrqAssert == _TRUE) && (ucRxPreSinkCount != ucRxCurSinkCount) && (ScalerDpRxGetHotPlugStatus(enumInputPort) == _HIGH))
    {
        ScalerDpAuxRxSetDpcdMirrorBitValue(enumInputPort, 0x00, 0x02, 0x04, ~_BIT6, _BIT6);
        ScalerDpAuxRxHpdIrqAssert(enumInputPort);
    }
}

//--------------------------------------------------
// Description  : Get Hdcp Repeater Support
// Input Value  : EnumInputPort
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerDpAuxRxGetHdcpRepeaterSupport(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            return GET_DP_AUX_RX0_HDCP_REPEATER_SUPPORT();
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            return GET_DP_AUX_RX1_HDCP_REPEATER_SUPPORT();
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            return GET_DP_AUX_RX2_HDCP_REPEATER_SUPPORT();
#endif
        default:

            break;
    }

    return _FALSE;
}
#endif

#if(_DP_HDCP2_RX_SUPPORT == _ON)
//--------------------------------------------------
// Description  : HDCP2 Type Value Reset
// Input Value  : EnumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxHdcp2TypeValueReset(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpAuxRx0Hdcp2TypeValueReset();

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpAuxRx1Hdcp2TypeValueReset();

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpAuxRx2Hdcp2TypeValueReset();

            break;
#endif

        default:

            break;
    }
}

#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
//--------------------------------------------------
// Description  : HDCP2 Stream ID Type Value Reset
// Input Value  : EnumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxHdcp2StreamIDTypeReset(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpAuxRx0Hdcp2StreamIDTypeReset();

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpAuxRx1Hdcp2StreamIDTypeReset();

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpAuxRx2Hdcp2StreamIDTypeReset();

            break;
#endif

        default:

            break;
    }
}
#endif

//--------------------------------------------------
// Description  : Read M Prime Force Defer
// Input Value  : bEnable
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxSetMPrimeReadDefer(EnumInputPort enumInputPort, bit bEnable)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpAuxRx0SetMPrimeReadDefer(bEnable);

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpAuxRx1SetMPrimeReadDefer(bEnable);

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpAuxRx2SetMPrimeReadDefer(bEnable);

            break;
#endif
        default:

            break;
    }
}


//--------------------------------------------------
// Description  : HDCP2.2 Handshaked Related IRQ
// Input Value  : EnumSourceSearchPort
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxHdcp2HandshakeIRQ(EnumInputPort enumInputPort, bit bEnable)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpAuxRx0Hdcp2HandshakeIRQ(bEnable);

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpAuxRx1Hdcp2HandshakeIRQ(bEnable);

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpAuxRx2Hdcp2HandshakeIRQ(bEnable);

            break;
#endif

        default:
            break;
    }
}
#endif

//--------------------------------------------------
// Description  : Check DPCD HDCP capability
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpAuxRxCheckHdcpCapability(EnumInputPort enumInputPort)
{
    if(ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x06, 0x80, 0x28, _BIT0) == _BIT0)
    {
#if(_DP_HDCP_2_2_SUPPORT == _ON)
        if(ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x06, 0x92, 0x1F, _BIT1) == _BIT1)
#endif
        {
            return _TRUE;
        }
    }

    return _FALSE;
}

#if(_DP_RX_DSC_DECODER_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DSC PPS Time out Process
// Input Value  : ucDscMac
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxDscPpsTimeOutProc(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
        case _D0_INPUT_PORT:
#if(_DP_AUX_RX0_DSC_DECODER_SUPPORT == _ON)
#if(_DP_MST_SUPPORT == _ON)
            if(ScalerDpRxGetMstCapability(_D0_INPUT_PORT) == _TRUE)
            {
                ScalerDpRxSetHotPlugEvent(_D0_INPUT_PORT, _DP_MST_LONG_HPD_EVENT);
            }
            else
#endif
            {
                ScalerDpRxSetHotPlugEvent(_D0_INPUT_PORT, _DP_LONG_HPD_EVENT);
            }
#endif
            break;

        case _D1_INPUT_PORT:
#if(_DP_AUX_RX1_DSC_DECODER_SUPPORT == _ON)
#if(_DP_MST_SUPPORT == _ON)
            if(ScalerDpRxGetMstCapability(_D1_INPUT_PORT) == _TRUE)
            {
                ScalerDpRxSetHotPlugEvent(_D1_INPUT_PORT, _DP_MST_LONG_HPD_EVENT);
            }
            else
#endif
            {
                ScalerDpRxSetHotPlugEvent(_D1_INPUT_PORT, _DP_LONG_HPD_EVENT);
            }
#endif
            break;

        case _D2_INPUT_PORT:
#if(_DP_AUX_RX2_DSC_DECODER_SUPPORT == _ON)
#if(_DP_MST_SUPPORT == _ON)
            if(ScalerDpRxGetMstCapability(_D2_INPUT_PORT) == _TRUE)
            {
                ScalerDpRxSetHotPlugEvent(_D2_INPUT_PORT, _DP_MST_LONG_HPD_EVENT);
            }
            else
#endif
            {
                ScalerDpRxSetHotPlugEvent(_D2_INPUT_PORT, _DP_LONG_HPD_EVENT);
            }
#endif
            break;

        default:
            break;
    }
}
#endif

//--------------------------------------------------
// Description  : Get Msg RX Base Address of Input Port
// Input Value  : enumOutputPort
// Output Value : WORD
//--------------------------------------------------
void ScalerDpAuxRxSetBase32AddressOffset(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            g_ulDpAuxRxBase32AddressOffset = 0x000000;

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            g_ulDpAuxRxBase32AddressOffset = 0x100000;

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            g_ulDpAuxRxBase32AddressOffset = 0x200000;

            break;
#endif

        default:

            g_ulDpAuxRxBase32AddressOffset = 0x000000;

            break;
    }
}

#if(_DP_IRQ_HPD_MODE == _DP_IRQ_HPD_T2_MODE)
//--------------------------------------------------
// Description  : Timer2 Aux Mode Backup
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxManualModeSetting_T2INT(EnumDpAuxManualModeSetting enumSetting)
{
    if(enumSetting == _DP_AUX_MANUAL_MODE_SET)
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        g_enumDpAuxRx0AutoModeBackup_T2INT = GET_DP_AUX_RX0_MODE_T2INT();

        if(g_enumDpAuxRx0AutoModeBackup_T2INT == _DP_RX_AUX_AUTO_MODE)
        {
            SET_DP_AUX_RX0_MANUAL_MODE_T2INT();
        }
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        g_enumDpAuxRx1AutoModeBackup_T2INT = GET_DP_AUX_RX1_MODE_T2INT();

        if(g_enumDpAuxRx1AutoModeBackup_T2INT == _DP_RX_AUX_AUTO_MODE)
        {
            SET_DP_AUX_RX1_MANUAL_MODE_T2INT();
        }
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        g_enumDpAuxRx2AutoModeBackup_T2INT = GET_DP_AUX_RX2_MODE_T2INT();

        if(g_enumDpAuxRx2AutoModeBackup_T2INT == _DP_RX_AUX_AUTO_MODE)
        {
            SET_DP_AUX_RX2_MANUAL_MODE_T2INT();
        }
#endif
    }
    else if(enumSetting == _DP_AUX_MANUAL_MODE_RECOVER)
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        if(g_enumDpAuxRx0AutoModeBackup_T2INT == _DP_RX_AUX_AUTO_MODE)
        {
            SET_DP_AUX_RX0_AUTO_MODE_T2INT();
        }
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        if(g_enumDpAuxRx1AutoModeBackup_T2INT == _DP_RX_AUX_AUTO_MODE)
        {
            SET_DP_AUX_RX1_AUTO_MODE_T2INT();
        }
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        if(g_enumDpAuxRx2AutoModeBackup_T2INT == _DP_RX_AUX_AUTO_MODE)
        {
            SET_DP_AUX_RX2_AUTO_MODE_T2INT();
        }
#endif
    }
}

#endif

#if(_FW_DP_AUX_RX_DYNAMIC_POWER_CUT == _ON)
//--------------------------------------------------
// Description  : DP Aux Rx Power Cut Control
// Input Value  : ON --> Power On
//                OFF --> Power Off
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxPowerControl(EnumInputPort enumInputPort, EnumPowerTarget enumPowerTarget)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            if(enumPowerTarget == _POWER_ON)
            {
                ScalerPowerDomainEnableControl(_POWER_CUT_GROUP_RX0_DP_AUX, _POWER_CUT_OFF, _POWER_ON_DELAY_5_MS);

                ScalerDpAuxRx0Initial();

#if(_DP_MST_SUPPORT == _ON)
                ScalerDpMstRxCapabilitySwitchProc();
#endif

                // Set Pinshare Config AUXP/N
                ScalerPinshareDpAuxRxConfig(enumInputPort, _POWER_ON);
            }
            else
            {
                // Set Pinshare Config AUXP/N
                ScalerPinshareDpAuxRxConfig(enumInputPort, _POWER_OFF);

                ScalerPowerDomainEnableControl(_POWER_CUT_GROUP_RX0_DP_AUX, _POWER_CUT_ON, _POWER_ON_DELAY_NONE);
            }

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            if(enumPowerTarget == _POWER_ON)
            {
                ScalerPowerDomainEnableControl(_POWER_CUT_GROUP_RX1_DP_AUX, _POWER_CUT_OFF, _POWER_ON_DELAY_5_MS);

                ScalerDpAuxRx1Initial();

#if(_DP_MST_SUPPORT == _ON)
                ScalerDpMstRxCapabilitySwitchProc();
#endif

                // Set Pinshare Config AUXP/N
                ScalerPinshareDpAuxRxConfig(enumInputPort, _POWER_ON);
            }
            else
            {
                // Set Pinshare Config AUXP/N
                ScalerPinshareDpAuxRxConfig(enumInputPort, _POWER_OFF);

                ScalerPowerDomainEnableControl(_POWER_CUT_GROUP_RX1_DP_AUX, _POWER_CUT_ON, _POWER_ON_DELAY_NONE);
            }

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            if(enumPowerTarget == _POWER_ON)
            {
                ScalerPowerDomainEnableControl(_POWER_CUT_GROUP_RX2_DP_AUX, _POWER_CUT_OFF, _POWER_ON_DELAY_5_MS);

                ScalerDpAuxRx2Initial();

#if(_DP_MST_SUPPORT == _ON)
                ScalerDpMstRxCapabilitySwitchProc();
#endif

                // Set Pinshare Config AUXP/N
                ScalerPinshareDpAuxRxConfig(enumInputPort, _POWER_ON);
            }
            else
            {
                // Set Pinshare Config AUXP/N
                ScalerPinshareDpAuxRxConfig(enumInputPort, _POWER_OFF);

                ScalerPowerDomainEnableControl(_POWER_CUT_GROUP_RX2_DP_AUX, _POWER_CUT_ON, _POWER_ON_DELAY_NONE);
            }

            break;
#endif
        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Dp AUX Rx Get Power Status
// Input Value  : EnumInputPort enumInputPort
// Output Value : EnumPowerCut
//--------------------------------------------------
EnumPowerCut ScalerDpAuxRxGetPowerStatus(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            return ScalerPowerGroupGetPowerCutStatus(_POWER_CUT_GROUP_RX0_DP_AUX);
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            return ScalerPowerGroupGetPowerCutStatus(_POWER_CUT_GROUP_RX1_DP_AUX);
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            return ScalerPowerGroupGetPowerCutStatus(_POWER_CUT_GROUP_RX2_DP_AUX);
#endif
        default:
            break;
    }

    return _POWER_CUT_OFF;
}
#endif

//--------------------------------------------------
// Description  : DPCD Wildcard function setting
// Input Value  : WildcardId, DPCD address range, address mask or len
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxDpcdWildCardSetting(EnumInputPort enumInputPort, EnumDpAuxRxDpcdWildCardId enumDpAuxRxDpcdWildCardId, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, EnumDpAuxRxDpcdWildCardBitMask enumDpAuxRxDpcdWildCardBitMask)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpAuxRx0DpcdWildCardSetting(enumDpAuxRxDpcdWildCardId, ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, enumDpAuxRxDpcdWildCardBitMask);

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpAuxRx1DpcdWildCardSetting(enumDpAuxRxDpcdWildCardId, ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, enumDpAuxRxDpcdWildCardBitMask);

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpAuxRx2DpcdWildCardSetting(enumDpAuxRxDpcdWildCardId, ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, enumDpAuxRxDpcdWildCardBitMask);

            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : DPCD Wildcard function Set Force Defer Enable
// Input Value  : WildcardId
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxSetDpcdWildCardForceDeferEnable(EnumInputPort enumInputPort, EnumDpAuxRxDpcdWildCardId enumDpAuxRxDpcdWildCardId, bit bEnable)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpAuxRx0SetDpcdWildCardForceDeferEnable(enumDpAuxRxDpcdWildCardId, bEnable);

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpAuxRx1SetDpcdWildCardForceDeferEnable(enumDpAuxRxDpcdWildCardId, bEnable);

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpAuxRx2SetDpcdWildCardForceDeferEnable(enumDpAuxRxDpcdWildCardId, bEnable);

            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : DPCD Wildcard function Get Force Defer Enable
// Input Value  : wildcardId
// Output Value : Force Defer Enable
//--------------------------------------------------
bit ScalerDpAuxRxGetDpcdWildCardForceDeferEnable(EnumInputPort enumInputPort, EnumDpAuxRxDpcdWildCardId enumDpAuxRxDpcdWildCardId)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            return ScalerDpAuxRx0GetDpcdWildCardForceDeferEnable(enumDpAuxRxDpcdWildCardId);
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            return ScalerDpAuxRx1GetDpcdWildCardForceDeferEnable(enumDpAuxRxDpcdWildCardId);
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            return ScalerDpAuxRx2GetDpcdWildCardForceDeferEnable(enumDpAuxRxDpcdWildCardId);
#endif
        default:

            return 0x00;
    }
}

//--------------------------------------------------
// Description  : DPCD Wildcard int enable
// Input Value  : WildcardId, enable/disable
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxSetDpcdWildCardIntEnable(EnumInputPort enumInputPort, EnumDpAuxRxDpcdWildCardId enumDpAuxRxDpcdWildCardId, bit bEnable)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpAuxRx0SetDpcdWildCardIntEnable(enumDpAuxRxDpcdWildCardId, bEnable);

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpAuxRx1SetDpcdWildCardIntEnable(enumDpAuxRxDpcdWildCardId, bEnable);

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpAuxRx2SetDpcdWildCardIntEnable(enumDpAuxRxDpcdWildCardId, bEnable);

            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : DPCD Wildcard int enable
// Input Value  : WildcardId, enable/disable
// Output Value : WildCard Int Enable
//--------------------------------------------------
bit ScalerDpAuxRxGetDpcdWildCardIntEnable(EnumInputPort enumInputPort, EnumDpAuxRxDpcdWildCardId enumDpAuxRxDpcdWildCardId)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            return ScalerDpAuxRx0GetDpcdWildCardIntEnable(enumDpAuxRxDpcdWildCardId);
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            return ScalerDpAuxRx1GetDpcdWildCardIntEnable(enumDpAuxRxDpcdWildCardId);
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            return ScalerDpAuxRx2GetDpcdWildCardIntEnable(enumDpAuxRxDpcdWildCardId);
#endif
        default:

            return 0x00;
    }
}

//--------------------------------------------------
// Description  : DPCD Wildcard int check
// Input Value  : WildcardId
// Output Value : None
//--------------------------------------------------
bit ScalerDpAuxRxDpcdWildCardIntCheck(EnumInputPort enumInputPort, EnumDpAuxRxDpcdWildCardId enumDpAuxRxDpcdWildCardId)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            return ScalerDpAuxRx0DpcdWildCardIntCheck(enumDpAuxRxDpcdWildCardId);
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            return ScalerDpAuxRx1DpcdWildCardIntCheck(enumDpAuxRxDpcdWildCardId);
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            return ScalerDpAuxRx2DpcdWildCardIntCheck(enumDpAuxRxDpcdWildCardId);
#endif
        default:

            return 0;
    }
}

//--------------------------------------------------
// Description  : DPCD Wildcard int clear
// Input Value  : WildcardId
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxDpcdWildCardIntClr(EnumInputPort enumInputPort, EnumDpAuxRxDpcdWildCardId enumDpAuxRxDpcdWildCardId)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpAuxRx0DpcdWildCardIntClr(enumDpAuxRxDpcdWildCardId);

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpAuxRx1DpcdWildCardIntClr(enumDpAuxRxDpcdWildCardId);

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpAuxRx2DpcdWildCardIntClr(enumDpAuxRxDpcdWildCardId);

            break;
#endif
        default:

            break;
    }
}

#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _OFF)
//--------------------------------------------------
// Description  : DPCD 32B Remapping function for Setting
// Input Value  : RemapId, DPCD address
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxDpcdRemap32BSetting(EnumInputPort enumInputPort, EnumDpAuxRxDpcdRemap32BId enumDpAuxRxDpcdRemap32BId, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, EnumDpAuxRxDpcdAttr enumDpAuxRxDpcdAttr)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpAuxRx0DpcdRemap32BSetting(enumDpAuxRxDpcdRemap32BId, ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, enumDpAuxRxDpcdAttr);

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpAuxRx1DpcdRemap32BSetting(enumDpAuxRxDpcdRemap32BId, ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, enumDpAuxRxDpcdAttr);

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpAuxRx2DpcdRemap32BSetting(enumDpAuxRxDpcdRemap32BId, ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, enumDpAuxRxDpcdAttr);

            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : DPCD 16B Remapping function for Setting
// Input Value  : RemapId, DPCD address
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxDpcdRemap16BSetting(EnumInputPort enumInputPort, EnumDpAuxRxDpcdRemap16BId enumDpAuxRxDpcdRemap16BId, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, EnumDpAuxRxDpcdAttr enumDpAuxRxDpcdAttr)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpAuxRx0DpcdRemap16BSetting(enumDpAuxRxDpcdRemap16BId, ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, enumDpAuxRxDpcdAttr);

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpAuxRx1DpcdRemap16BSetting(enumDpAuxRxDpcdRemap16BId, ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, enumDpAuxRxDpcdAttr);

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpAuxRx2DpcdRemap16BSetting(enumDpAuxRxDpcdRemap16BId, ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, enumDpAuxRxDpcdAttr);

            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : DPCD 8B Remapping function for Setting
// Input Value  : RemapId, DPCD address
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxDpcdRemap8BSetting(EnumInputPort enumInputPort, EnumDpAuxRxDpcdRemap8BId enumDpAuxRxDpcdRemap8BId, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, EnumDpAuxRxDpcdAttr enumDpAuxRxDpcdAttr)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpAuxRx0DpcdRemap8BSetting(enumDpAuxRxDpcdRemap8BId, ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, enumDpAuxRxDpcdAttr);

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpAuxRx1DpcdRemap8BSetting(enumDpAuxRxDpcdRemap8BId, ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, enumDpAuxRxDpcdAttr);

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpAuxRx2DpcdRemap8BSetting(enumDpAuxRxDpcdRemap8BId, ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, enumDpAuxRxDpcdAttr);

            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Get DPCD 32B Remapping function Enable
// Input Value  : RemapId
// Output Value : Enable / Disable
//--------------------------------------------------
bit ScalerDpAuxRxGetDpcdRemap32BEnable(EnumInputPort enumInputPort, EnumDpAuxRxDpcdRemap32BId enumDpAuxRxDpcdRemap32BId)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            return ScalerDpAuxRx0GetDpcdRemap32BEnable(enumDpAuxRxDpcdRemap32BId);
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            return ScalerDpAuxRx1GetDpcdRemap32BEnable(enumDpAuxRxDpcdRemap32BId);
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            return ScalerDpAuxRx2GetDpcdRemap32BEnable(enumDpAuxRxDpcdRemap32BId);
#endif
        default:

            return 0x00;
    }
}

//--------------------------------------------------
// Description  : Get DPCD 16B Remapping function Enable
// Input Value  : RemapId
// Output Value : Enable / Disable
//--------------------------------------------------
bit ScalerDpAuxRxGetDpcdRemap16BEnable(EnumInputPort enumInputPort, EnumDpAuxRxDpcdRemap16BId enumDpAuxRxDpcdRemap16BId)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            return ScalerDpAuxRx0GetDpcdRemap16BEnable(enumDpAuxRxDpcdRemap16BId);
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            return ScalerDpAuxRx1GetDpcdRemap16BEnable(enumDpAuxRxDpcdRemap16BId);
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            return ScalerDpAuxRx2GetDpcdRemap16BEnable(enumDpAuxRxDpcdRemap16BId);
#endif
        default:

            return 0x00;
    }
}

//--------------------------------------------------
// Description  : Get DPCD 8B Remapping function Enable
// Input Value  : RemapId
// Output Value : Enable / Disable
//--------------------------------------------------
bit ScalerDpAuxRxGetDpcdRemap8BEnable(EnumInputPort enumInputPort, EnumDpAuxRxDpcdRemap8BId enumDpAuxRxDpcdRemap8BId)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            return ScalerDpAuxRx0GetDpcdRemap8BEnable(enumDpAuxRxDpcdRemap8BId);
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            return ScalerDpAuxRx1GetDpcdRemap8BEnable(enumDpAuxRxDpcdRemap8BId);
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            return ScalerDpAuxRx2GetDpcdRemap8BEnable(enumDpAuxRxDpcdRemap8BId);
#endif
        default:

            return 0x00;
    }
}

//--------------------------------------------------
// Description  : Clear DPCD 32B Remapping function
// Input Value  : RemapId
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxDpcdRemap32BReset(EnumInputPort enumInputPort, EnumDpAuxRxDpcdRemap32BId enumDpAuxRxDpcdRemap32BId)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpAuxRx0DpcdRemap32BReset(enumDpAuxRxDpcdRemap32BId);

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpAuxRx1DpcdRemap32BReset(enumDpAuxRxDpcdRemap32BId);

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpAuxRx2DpcdRemap32BReset(enumDpAuxRxDpcdRemap32BId);

            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Clear DPCD 16B Remapping function
// Input Value  : RemapId
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxDpcdRemap16BReset(EnumInputPort enumInputPort, EnumDpAuxRxDpcdRemap16BId enumDpAuxRxDpcdRemap16BId)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpAuxRx0DpcdRemap16BReset(enumDpAuxRxDpcdRemap16BId);

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpAuxRx1DpcdRemap16BReset(enumDpAuxRxDpcdRemap16BId);

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpAuxRx2DpcdRemap16BReset(enumDpAuxRxDpcdRemap16BId);

            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Clear DPCD 8B Remapping function
// Input Value  : RemapId
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxDpcdRemap8BReset(EnumInputPort enumInputPort, EnumDpAuxRxDpcdRemap8BId enumDpAuxRxDpcdRemap8BId)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpAuxRx0DpcdRemap8BReset(enumDpAuxRxDpcdRemap8BId);

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpAuxRx1DpcdRemap8BReset(enumDpAuxRxDpcdRemap8BId);

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpAuxRx2DpcdRemap8BReset(enumDpAuxRxDpcdRemap8BId);

            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : DPCD 32B Remapping int enable
// Input Value  : remapId
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxDpcdRemap32BIntEnable(EnumInputPort enumInputPort, EnumDpAuxRxDpcdRemap32BId enumDpAuxRxDpcdRemap32BId, BYTE ucDpcdRemapIrqBitOffset, bit bEnable)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpAuxRx0DpcdRemap32BIntEnable(enumDpAuxRxDpcdRemap32BId, ucDpcdRemapIrqBitOffset, bEnable);

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpAuxRx1DpcdRemap32BIntEnable(enumDpAuxRxDpcdRemap32BId, ucDpcdRemapIrqBitOffset, bEnable);

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpAuxRx2DpcdRemap32BIntEnable(enumDpAuxRxDpcdRemap32BId, ucDpcdRemapIrqBitOffset, bEnable);

            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : DPCD 16B Remapping int enable
// Input Value  : remapId
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxDpcdRemap16BIntEnable(EnumInputPort enumInputPort, EnumDpAuxRxDpcdRemap16BId enumDpAuxRxDpcdRemap16BId, BYTE ucDpcdRemapIrqBitOffset, bit bEnable)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpAuxRx0DpcdRemap16BIntEnable(enumDpAuxRxDpcdRemap16BId, ucDpcdRemapIrqBitOffset, bEnable);

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpAuxRx1DpcdRemap16BIntEnable(enumDpAuxRxDpcdRemap16BId, ucDpcdRemapIrqBitOffset, bEnable);

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpAuxRx2DpcdRemap16BIntEnable(enumDpAuxRxDpcdRemap16BId, ucDpcdRemapIrqBitOffset, bEnable);

            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : DPCD 8B Remapping int enable
// Input Value  : remapId
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxDpcdRemap8BIntEnable(EnumInputPort enumInputPort, EnumDpAuxRxDpcdRemap8BId enumDpAuxRxDpcdRemap8BId, BYTE ucDpcdRemapIrqBitOffset, bit bEnable)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpAuxRx0DpcdRemap8BIntEnable(enumDpAuxRxDpcdRemap8BId, ucDpcdRemapIrqBitOffset, bEnable);

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpAuxRx1DpcdRemap8BIntEnable(enumDpAuxRxDpcdRemap8BId, ucDpcdRemapIrqBitOffset, bEnable);

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpAuxRx2DpcdRemap8BIntEnable(enumDpAuxRxDpcdRemap8BId, ucDpcdRemapIrqBitOffset, bEnable);

            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : DPCD 32B Remapping int check
// Input Value  : remapId
// Output Value : Int flag:1/0
//--------------------------------------------------
bit ScalerDpAuxRxDpcdRemap32BIntCheck(EnumInputPort enumInputPort, EnumDpAuxRxDpcdRemap32BId enumDpAuxRxDpcdRemap32BId)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            return ScalerDpAuxRx0DpcdRemap32BIntCheck(enumDpAuxRxDpcdRemap32BId);
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            return ScalerDpAuxRx1DpcdRemap32BIntCheck(enumDpAuxRxDpcdRemap32BId);
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            return ScalerDpAuxRx2DpcdRemap32BIntCheck(enumDpAuxRxDpcdRemap32BId);
#endif
        default:

            return 0x00;
    }
}

//--------------------------------------------------
// Description  : DPCD 16B Remapping int check
// Input Value  : remapId
// Output Value : Int flag:1/0
//--------------------------------------------------
bit ScalerDpAuxRxDpcdRemap16BIntCheck(EnumInputPort enumInputPort, EnumDpAuxRxDpcdRemap16BId enumDpAuxRxDpcdRemap16BId)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            return ScalerDpAuxRx0DpcdRemap16BIntCheck(enumDpAuxRxDpcdRemap16BId);
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            return ScalerDpAuxRx1DpcdRemap16BIntCheck(enumDpAuxRxDpcdRemap16BId);
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            return ScalerDpAuxRx2DpcdRemap16BIntCheck(enumDpAuxRxDpcdRemap16BId);
#endif
        default:

            return 0x00;
    }
}

//--------------------------------------------------
// Description  : DPCD 8B Remapping int check
// Input Value  : remapId
// Output Value : Int flag:1/0
//--------------------------------------------------
bit ScalerDpAuxRxDpcdRemap8BIntCheck(EnumInputPort enumInputPort, EnumDpAuxRxDpcdRemap8BId enumDpAuxRxDpcdRemap8BId)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            return ScalerDpAuxRx0DpcdRemap8BIntCheck(enumDpAuxRxDpcdRemap8BId);
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            return ScalerDpAuxRx1DpcdRemap8BIntCheck(enumDpAuxRxDpcdRemap8BId);
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            return ScalerDpAuxRx2DpcdRemap8BIntCheck(enumDpAuxRxDpcdRemap8BId);
#endif
        default:

            return 0x00;
    }
}

//--------------------------------------------------
// Description  : DPCD 32B Remapping int clear
// Input Value  : remapId
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxDpcdRemap32BIntClr(EnumInputPort enumInputPort, EnumDpAuxRxDpcdRemap32BId enumDpAuxRxDpcdRemap32BId)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpAuxRx0DpcdRemap32BIntClr(enumDpAuxRxDpcdRemap32BId);

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpAuxRx1DpcdRemap32BIntClr(enumDpAuxRxDpcdRemap32BId);

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpAuxRx2DpcdRemap32BIntClr(enumDpAuxRxDpcdRemap32BId);

            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : DPCD 16B Remapping int clear
// Input Value  : remapId
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxDpcdRemap16BIntClr(EnumInputPort enumInputPort, EnumDpAuxRxDpcdRemap16BId enumDpAuxRxDpcdRemap16BId)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpAuxRx0DpcdRemap16BIntClr(enumDpAuxRxDpcdRemap16BId);

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpAuxRx1DpcdRemap16BIntClr(enumDpAuxRxDpcdRemap16BId);

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpAuxRx2DpcdRemap16BIntClr(enumDpAuxRxDpcdRemap16BId);

            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : DPCD 8B Remapping int clear
// Input Value  : remapId
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxDpcdRemap8BIntClr(EnumInputPort enumInputPort, EnumDpAuxRxDpcdRemap8BId enumDpAuxRxDpcdRemap8BId)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpAuxRx0DpcdRemap8BIntClr(enumDpAuxRxDpcdRemap8BId);

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpAuxRx1DpcdRemap8BIntClr(enumDpAuxRxDpcdRemap8BId);

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpAuxRx2DpcdRemap8BIntClr(enumDpAuxRxDpcdRemap8BId);

            break;
#endif
        default:

            break;
    }
}
#endif

#if(_DP_RX_FEC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set Fec Status W1C Protect
// Input Value  : EnumInputPort, _ENABLE/_DISABLE
// Output Value : none
//--------------------------------------------------
void ScalerDpAuxRxSetFecStatusW1cProtectEnable(EnumInputPort enumInputPort, bit bEnable)
{
    bEnable = bEnable;

    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpAuxRx0SetFecStatusW1cProtectEnable(bEnable);

            break;
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpAuxRx1SetFecStatusW1cProtectEnable(bEnable);

            break;
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpAuxRx2SetFecStatusW1cProtectEnable(bEnable);

            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Get Fec Status W1C Protect
// Input Value  : EnumInputPort
// Output Value : _ENABLE/_DISABLE
//--------------------------------------------------
bit ScalerDpAuxRxGetFecStatusW1cProtectEnable(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            return ScalerDpAuxRx0GetFecStatusW1cProtectEnable();
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            return ScalerDpAuxRx1GetFecStatusW1cProtectEnable();
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            return ScalerDpAuxRx2GetFecStatusW1cProtectEnable();
#endif
        default:

            return _FALSE;
    }
}
#endif

#if(_DP_PR_MODE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP Aux Rx PR Mode DPCD Setting
// Input Value  : None
// Output Value : None
//-----------------------------------------------
void ScalerDpAuxRxPRModeDpcdSetting(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:
            ScalerDpAuxRx0PRModeDpcdSetting();
            break;
#endif
#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:
            ScalerDpAuxRx1PRModeDpcdSetting();
            break;
#endif
#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:
            ScalerDpAuxRx2PRModeDpcdSetting();
            break;
#endif
        default:
            break;
    }
}

//--------------------------------------------------
// Description  : DP Aux Rx PR Mode DPCD Setting
// Input Value  : None
// Output Value : None
//-----------------------------------------------
bit ScalerDpAuxRxPRModeFlagStatus(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:
            return ScalerDpAuxRx0PRModeFlagStatus();
#endif
#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:
            return ScalerDpAuxRx1PRModeFlagStatus();
#endif
#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:
            return ScalerDpAuxRx2PRModeFlagStatus();
#endif
        default:
            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Update PR Mode Error Status DPCD 02020h
// Input Value  : EnumInputPort,EnumPRModeErrorStatus
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxDpcdPRModeErrorStateUpdate(EnumInputPort enumInputPort, EnumPRModeErrorStatus enumPRModeErrorStatus)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:
            ScalerDpAuxRx0DpcdPRModeErrorStateUpdate(enumPRModeErrorStatus);
            break;
#endif
#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:
            ScalerDpAuxRx1DpcdPRModeErrorStateUpdate(enumPRModeErrorStatus);
            break;
#endif
#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:
            ScalerDpAuxRx2DpcdPRModeErrorStateUpdate(enumPRModeErrorStatus);
            break;
#endif
        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Update PR Mode Status DPCD 02022h
// Input Value  : EnumInputPort,EnumPRModeStatus
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxDpcdPRModeStatusUpdate(EnumInputPort enumInputPort, EnumPRModeStatus enumPRModeStatus)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:
            ScalerDpAuxRx0DpcdPRModeStatusUpdate(enumPRModeStatus);
            break;
#endif
#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:
            ScalerDpAuxRx1DpcdPRModeStatusUpdate(enumPRModeStatus);
            break;
#endif
#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:
            ScalerDpAuxRx2DpcdPRModeStatusUpdate(enumPRModeStatus);
            break;
#endif
        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Get Dp PR mode 001B0h value
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE ScalerDpAuxRxPRModeGetDpcd001B0hValue(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:

            return ScalerDpAuxRx0GetDpcdInfo(0x00, 0x01, 0xB0);
#endif

#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:

            return ScalerDpAuxRx1GetDpcdInfo(0x00, 0x01, 0xB0);
#endif

#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:

            return ScalerDpAuxRx2GetDpcdInfo(0x00, 0x01, 0xB0);
#endif
        default:

            return 0x00;
    }
}

//--------------------------------------------------
// Description  : Get PR Mode DPCD 001B0h[1] Crc Enable
// Input Value  : EnumInputPort
// Output Value : None
//--------------------------------------------------
bit ScalerDpAuxRxGetPRModeDpcdCrcEnable(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:
            return GET_DP_AUX_RX0_PR_MODE_DPCD_CRC_ENABLE();
#endif
#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:
            return GET_DP_AUX_RX1_PR_MODE_DPCD_CRC_ENABLE();
#endif
#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:
            return GET_DP_AUX_RX2_PR_MODE_DPCD_CRC_ENABLE();
#endif
        default:
            return _FALSE;
    }
}
#endif

#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP Aux Rx Auxless Alpm DPCD Setting
// Input Value  : None
// Output Value : None
//-----------------------------------------------
void ScalerDpAuxRxAuxlessAlpmDpcdSetting(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:
            ScalerDpAuxRx0AuxlessAlpmDpcdSetting();
            break;
#endif
#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:
            ScalerDpAuxRx1AuxlessAlpmDpcdSetting();
            break;
#endif
#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:
            ScalerDpAuxRx2AuxlessAlpmDpcdSetting();
            break;
#endif
        default:
            break;
    }
}
#endif

#if(_DP_HDR10_SUPPORT == _ON)
#if(_DP_HDR_VENDOR_SUPPORT != _DP_HDR_VENDOR_SUPPORT_NONE)
//--------------------------------------------------
// Description  : DP Aux Rx Hdr DPCD Setting
// Input Value  : None
// Output Value : None
//-----------------------------------------------
void ScalerDpAuxRxHdrDpcdSetting(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:
            ScalerDpAuxRx0HdrDpcdSetting();
            break;
#endif
#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:
            ScalerDpAuxRx1HdrDpcdSetting();
            break;
#endif
#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:
            ScalerDpAuxRx2HdrDpcdSetting();
            break;
#endif
        default:
            break;
    }
}
#endif
#endif

#if(_DP_FREESYNC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP Aux Rx Freesync DPCD Setting
// Input Value  : None
// Output Value : None
//-----------------------------------------------
void ScalerDpAuxRxFreesyncDpcdSetting(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:
            ScalerDpAuxRx0FreesyncDpcdSetting();
            break;
#endif
#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:
            ScalerDpAuxRx1FreesyncDpcdSetting();
            break;
#endif
#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:
            ScalerDpAuxRx2FreesyncDpcdSetting();
            break;
#endif
        default:
            break;
    }
}
#endif

#if(_DP_ADAPTIVESYNC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP Aux Rx AdaptiveSync DPCD Setting
// Input Value  : None
// Output Value : None
//-----------------------------------------------
void ScalerDpAuxRxAdaptiveSyncDpcdSetting(EnumInputPort enumInputPort)
{
    switch(ScalerDpAuxRxDxRxMapping(enumInputPort))
    {
#if(_DP_AUX_RX0_SUPPORT == _ON)
        case _RX0:
            ScalerDpAuxRx0AdaptiveSyncDpcdSetting();
            break;
#endif
#if(_DP_AUX_RX1_SUPPORT == _ON)
        case _RX1:
            ScalerDpAuxRx1AdaptiveSyncDpcdSetting();
            break;
#endif
#if(_DP_AUX_RX2_SUPPORT == _ON)
        case _RX2:
            ScalerDpAuxRx2AdaptiveSyncDpcdSetting();
            break;
#endif
        default:
            break;
    }
}
#endif

//--------------------------------------------------
// Description  : Dpcd Initial For 0x00008
// Input Value  : EnumInputPort
// Output Value : none
//--------------------------------------------------
void ScalerDpAuxRxDpcdSetting_00008h(EnumInputPort enumInputPort)
{
    // _BIT1: Local Edid Present
    pData[0] = _BIT1;

#if(_DP_HBLANKING_MODIFY_SUPPORT == _ON)
    // _BIT5/_BIT4: Set Buffer Size unit
    pData[0] |= (_BIT5 | _BIT4);

#if(_DP_HBE_SUPPORT == _ON)
    // _BIT3: Set HBE Cap
    pData[0] |= _BIT3;
#endif

#if(_DP_HBLANKING_REDUCTION_SUPPORT == _ON)
    // _BIT6: Set HBE Cap
    pData[0] |= _BIT6;
#endif
#endif

    ScalerDpAuxRxSetDpcdMirrorValue(enumInputPort, 0x00, 0x00, 0x08, pData[0]);
}

//--------------------------------------------------
// Description  : Dpcd Initial For 0x00008
// Input Value  : EnumInputPort
// Output Value : none
//--------------------------------------------------
void ScalerDpAuxRxDpcdSetting_00009h(EnumInputPort enumInputPort)
{
#if(_DP_HBLANKING_MODIFY_SUPPORT == _ON)
    // Receiver Port0 Buffer size
    ScalerDpAuxRxSetDpcdMirrorValue(enumInputPort, 0x00, 0x00, 0x09, _FW_DP_RX_HBLANKING_MODIFY_BUFFER_SIZE);
#else

#if(_EIZO_CUSTOMIZED_VALUE_OF_DPCD_SUPPORT == _OFF)
    ScalerDpAuxRxSetDpcdMirrorValue(enumInputPort, 0x00, 0x00, 0x09, 0x00);
#endif
#endif
}

#if(_DP_HBLANKING_MODIFY_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Hblanking Modify Dpcd Initial
// Input Value  : none
// Output Value : none
//--------------------------------------------------
void ScalerDpAuxRxHblankingModifyDpcdTimingInfoReset(EnumInputPort enumInputPort)
{
    // DPCD [0x03054 ~ 0x03059]
    ScalerDpAuxRxDpcdGroupReset(enumInputPort, 0x00, 0x30, 0x54, 6);
}
#endif
#endif
