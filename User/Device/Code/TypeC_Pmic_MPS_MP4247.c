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
// ID Code      : TypeC_Pmic_MPS_MP4247.c
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "UserCommonInclude.h"
#include "../Header/TypeC_Pmic_MPS_MP4247.h"

#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON) && ((_EMB_TYPE_C_0_PMIC_TYPE != _PMIC_NONE) || (_EMB_TYPE_C_1_PMIC_TYPE != _PMIC_NONE)) && (_TYPE_C_PMIC_MP4247_SUPPORT == _ON))

#if(_D0_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
#if(_D0_TYPE_C_PMIC_IIC == _OFF)
#warning "PMIC is set. _D0_TYPE_C_PMIC_IIC should be ON!!!"
#endif

#if(_D0_TYPE_C_PMIC_SLAVE_ADDRESS == 0x00)
#warning "PMIC is set. _D0_TYPE_C_PMIC_SLAVE_ADDRESS should NOT be 0x00!!!"
#endif

#if(_D0_TYPE_C_PMIC_VOLTAGE_COMPENSATION == _ON)
#warning "MP4247 can't support voltage compensation!!!"
#endif

#if(_D0_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
#warning "MP4247 can't support PPS!!!"
#endif
#endif // End of #if(_D0_TYPE_C_PMIC_TYPE == _PMIC_MP4247)

#if(_D1_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
#if(_D1_TYPE_C_PMIC_IIC == _OFF)
#warning "PMIC is set. _D1_TYPE_C_PMIC_IIC should be ON!!!"
#endif

#if(_D1_TYPE_C_PMIC_SLAVE_ADDRESS == 0x00)
#warning "PMIC is set. _D1_TYPE_C_PMIC_SLAVE_ADDRESS should NOT be 0x00!!!"
#endif

#if(_D1_TYPE_C_PMIC_VOLTAGE_COMPENSATION == _ON)
#warning "MP4247 can't support voltage compensation!!!"
#endif

#if(_D1_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
#warning "MP4247 can't support PPS!!!"
#endif
#endif // End of #if(_D1_TYPE_C_PMIC_TYPE == _PMIC_MP4247)

#if(_P0_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
#if(_P0_TYPE_C_PMIC_IIC == _OFF)
#warning "PMIC is set. _P0_TYPE_C_PMIC_IIC should be ON!!!"
#endif

#if(_P0_TYPE_C_PMIC_SLAVE_ADDRESS == 0x00)
#warning "PMIC is set. _P0_TYPE_C_PMIC_SLAVE_ADDRESS should NOT be 0x00!!!"
#endif

#if(_P0_TYPE_C_PMIC_VOLTAGE_COMPENSATION == _ON)
#warning "MP4247 can't support voltage compensation!!!"
#endif

#if(_P0_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
#warning "MP4247 can't support PPS!!!"
#endif
#endif // End of #if(_P0_TYPE_C_PMIC_TYPE == _PMIC_MP4247)

#if(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
#if(_ADAPTOR_TYPE_C_PMIC_IIC == _OFF)
#warning "PMIC is set. _ADAPTOR_TYPE_C_PMIC_IIC should be ON!!!"
#endif

#if(_ADAPTOR_TYPE_C_PMIC_SLAVE_ADDRESS == 0x00)
#warning "PMIC is set. _ADAPTOR_TYPE_C_PMIC_SLAVE_ADDRESS should NOT be 0x00!!!"
#endif

#if(_ADAPTOR_TYPE_C_PMIC_VOLTAGE_COMPENSATION == _ON)
#warning "MP4247 can't support voltage compensation!!!"
#endif

#if(_ADAPTOR_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
#warning "MP4247 can't support PPS!!!"
#endif
#endif // End of #if(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_MP4247)


//****************************************************************************
// CODE TABLES
//****************************************************************************
BYTE code tPMIC_MP4247_ADDRESS_TABLE[][2] =
{
    {_MP4247_OPEARTION,                 _MP4247_DATA_LENGTH_1},
    {_MP4247_VOUT_COMMAND,              _MP4247_DATA_LENGTH_2},
    {_MP4247_MFR_CTRL1,                 _MP4247_DATA_LENGTH_1},
    {_MP4247_MFR_CURRENT_LIMIT,         _MP4247_DATA_LENGTH_1},
    {_MP4247_MFR_CTRL2,                 _MP4247_DATA_LENGTH_1},
    {_MP4247_MFR_CTRL3,                 _MP4247_DATA_LENGTH_1},
    {_MP4247_MFR_CTRL4,                 _MP4247_DATA_LENGTH_1},
    {_MP4247_MFR_STATUS_MASK,           _MP4247_DATA_LENGTH_1},
    {_MP4247_REGISTER_END,              0x00},
};

StructMP4247RegisterMap code tPMIC_MP4247_INITIAL_TABLE[] =
{
    {
        _MP4247_OPEARTION_DEFAULT,
        _MP4247_VOUT_COMMAND_DEFAULT,
        _MP4247_MFR_CTRL1_DEFAULT,
        _MP4247_MFR_CURRENT_LIMIT_DEFAULT,
        _MP4247_MFR_CTRL2_DEFAULT,
        _MP4247_MFR_CTRL3_DEFAULT,
        _MP4247_MFR_CTRL4_DEFAULT,
        _MP4247_MFR_STATUS_MASK_DEFAULT,
    },

    {
        _MP4247_OPEARTION_DEFAULT,
        _MP4247_VOUT_COMMAND_DEFAULT,
        _MP4247_MFR_CTRL1_DEFAULT,
        _MP4247_MFR_CURRENT_LIMIT_DEFAULT,
        _MP4247_MFR_CTRL2_DEFAULT,
        _MP4247_MFR_CTRL3_DEFAULT,
        _MP4247_MFR_CTRL4_DEFAULT,
        _MP4247_MFR_STATUS_MASK_DEFAULT,
    },

    {
        _MP4247_OPEARTION_DEFAULT,
        _MP4247_VOUT_COMMAND_DEFAULT,
        _MP4247_MFR_CTRL1_DEFAULT,
        _MP4247_MFR_CURRENT_LIMIT_DEFAULT,
        _MP4247_MFR_CTRL2_DEFAULT,
        _MP4247_MFR_CTRL3_DEFAULT,
        _MP4247_MFR_CTRL4_DEFAULT,
        _MP4247_MFR_STATUS_MASK_DEFAULT,
    },

    {
        _MP4247_OPEARTION_DEFAULT,
        _MP4247_VOUT_COMMAND_DEFAULT,
        _MP4247_MFR_CTRL1_DEFAULT,
        _MP4247_MFR_CURRENT_LIMIT_DEFAULT,
        _MP4247_MFR_CTRL2_DEFAULT,
        _MP4247_MFR_CTRL3_DEFAULT,
        _MP4247_MFR_CTRL4_DEFAULT,
        _MP4247_MFR_STATUS_MASK_DEFAULT,
    }
};

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
StructMP4247RegisterMap g_pstPmicMp4247Data[4];


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : PMIC Initial Settings
// Input Value  : enumTypeCPcbPort : PCB Port
// Output Value : None
//--------------------------------------------------
void ExternalDeviceInterfaceTypeCPmicMp4247ACOnInitial(EnumTypeCPcbPort enumTypeCPcbPort)
{
    BYTE ucDataIndex = 0;
    BYTE ucSlaveAddr = 0;

    // Enable Pin Control
    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
        ucDataIndex = 0;
        ucSlaveAddr = _D0_TYPE_C_PMIC_SLAVE_ADDRESS;
        PCB_D0_PMIC_POWER(_D0_PMIC_POWER_ON);
    }
    else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
        ucDataIndex = 1;
        ucSlaveAddr = _D1_TYPE_C_PMIC_SLAVE_ADDRESS;
        PCB_D1_PMIC_POWER(_D1_PMIC_POWER_ON);
    }
    else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
    {
        ucDataIndex = 2;
        ucSlaveAddr = _P0_TYPE_C_PMIC_SLAVE_ADDRESS;
        PCB_P0_PMIC_POWER(_P0_PMIC_POWER_ON);
    }
    else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
    {
        ucDataIndex = 3;
        ucSlaveAddr = _ADAPTOR_TYPE_C_PMIC_SLAVE_ADDRESS;
        PCB_ADAPTOR_PMIC_POWER(_ADAPTOR_PMIC_POWER_ON);
    }

    g_pstPmicMp4247Data[ucDataIndex] = tPMIC_MP4247_INITIAL_TABLE[ucDataIndex];

    UserCommonUsbTypeCPmicIICWrite(enumTypeCPcbPort, ucSlaveAddr, _MP4247_OPEARTION, _MP4247_SUBADDR_LENGTH, _MP4247_DATA_LENGTH_1, (BYTE *)(&g_pstPmicMp4247Data[ucDataIndex].ucOperation));
    UserCommonUsbTypeCPmicIICWrite(enumTypeCPcbPort, ucSlaveAddr, _MP4247_VOUT_COMMAND, _MP4247_SUBADDR_LENGTH, _MP4247_DATA_LENGTH_2, (BYTE *)(&g_pstPmicMp4247Data[ucDataIndex].usVoutCommand));
    UserCommonUsbTypeCPmicIICWrite(enumTypeCPcbPort, ucSlaveAddr, _MP4247_MFR_CTRL1, _MP4247_SUBADDR_LENGTH, _MP4247_DATA_LENGTH_1, (BYTE *)(&g_pstPmicMp4247Data[ucDataIndex].ucMfrCtrl1));
    UserCommonUsbTypeCPmicIICWrite(enumTypeCPcbPort, ucSlaveAddr, _MP4247_MFR_CURRENT_LIMIT, _MP4247_SUBADDR_LENGTH, _MP4247_DATA_LENGTH_1, (BYTE *)(&g_pstPmicMp4247Data[ucDataIndex].ucMfrCurrentLimit));
    UserCommonUsbTypeCPmicIICWrite(enumTypeCPcbPort, ucSlaveAddr, _MP4247_MFR_CTRL2, _MP4247_SUBADDR_LENGTH, _MP4247_DATA_LENGTH_1, (BYTE *)(&g_pstPmicMp4247Data[ucDataIndex].ucMfrCtrl2));
    UserCommonUsbTypeCPmicIICWrite(enumTypeCPcbPort, ucSlaveAddr, _MP4247_MFR_CTRL3, _MP4247_SUBADDR_LENGTH, _MP4247_DATA_LENGTH_1, (BYTE *)(&g_pstPmicMp4247Data[ucDataIndex].ucMfrCtrl3));
    UserCommonUsbTypeCPmicIICWrite(enumTypeCPcbPort, ucSlaveAddr, _MP4247_MFR_CTRL4, _MP4247_SUBADDR_LENGTH, _MP4247_DATA_LENGTH_1, (BYTE *)(&g_pstPmicMp4247Data[ucDataIndex].ucMfrCtrl4));
    UserCommonUsbTypeCPmicIICWrite(enumTypeCPcbPort, ucSlaveAddr, _MP4247_MFR_STATUS_MASK, _MP4247_SUBADDR_LENGTH, _MP4247_DATA_LENGTH_1, (BYTE *)(&g_pstPmicMp4247Data[ucDataIndex].ucMfrStatusMask));
}

//--------------------------------------------------
// Description  : PMIC Reset Settings
// Input Value  : enumTypeCPcbPort : PCB Port
// Output Value : None
//--------------------------------------------------
void ExternalDeviceInterfaceTypeCPmicMp4247UnattachReset(EnumTypeCPcbPort enumTypeCPcbPort)
{
    BYTE ucDataIndex = 0;
    BYTE ucSlaveAddr = 0;

    // Set Data Index
    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
        ucDataIndex = 0;
        ucSlaveAddr = _D0_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
        ucDataIndex = 1;
        ucSlaveAddr = _D1_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
    {
        ucDataIndex = 2;
        ucSlaveAddr = _P0_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
    {
        ucDataIndex = 3;
        ucSlaveAddr = _ADAPTOR_TYPE_C_PMIC_SLAVE_ADDRESS;
    }

    // Set PMIC Data initial value
    g_pstPmicMp4247Data[ucDataIndex] = tPMIC_MP4247_INITIAL_TABLE[ucDataIndex];

    // Initial Pmic Value
    UserCommonUsbTypeCPmicIICWrite(enumTypeCPcbPort, ucSlaveAddr, _MP4247_OPEARTION, _MP4247_SUBADDR_LENGTH, _MP4247_DATA_LENGTH_1, (BYTE *)(&g_pstPmicMp4247Data[ucDataIndex].ucOperation));
    UserCommonUsbTypeCPmicIICWrite(enumTypeCPcbPort, ucSlaveAddr, _MP4247_VOUT_COMMAND, _MP4247_SUBADDR_LENGTH, _MP4247_DATA_LENGTH_2, (BYTE *)(&g_pstPmicMp4247Data[ucDataIndex].usVoutCommand));
    UserCommonUsbTypeCPmicIICWrite(enumTypeCPcbPort, ucSlaveAddr, _MP4247_MFR_CTRL1, _MP4247_SUBADDR_LENGTH, _MP4247_DATA_LENGTH_1, (BYTE *)(&g_pstPmicMp4247Data[ucDataIndex].ucMfrCtrl1));
    UserCommonUsbTypeCPmicIICWrite(enumTypeCPcbPort, ucSlaveAddr, _MP4247_MFR_CURRENT_LIMIT, _MP4247_SUBADDR_LENGTH, _MP4247_DATA_LENGTH_1, (BYTE *)(&g_pstPmicMp4247Data[ucDataIndex].ucMfrCurrentLimit));
    UserCommonUsbTypeCPmicIICWrite(enumTypeCPcbPort, ucSlaveAddr, _MP4247_MFR_CTRL2, _MP4247_SUBADDR_LENGTH, _MP4247_DATA_LENGTH_1, (BYTE *)(&g_pstPmicMp4247Data[ucDataIndex].ucMfrCtrl2));
    UserCommonUsbTypeCPmicIICWrite(enumTypeCPcbPort, ucSlaveAddr, _MP4247_MFR_CTRL3, _MP4247_SUBADDR_LENGTH, _MP4247_DATA_LENGTH_1, (BYTE *)(&g_pstPmicMp4247Data[ucDataIndex].ucMfrCtrl3));
    UserCommonUsbTypeCPmicIICWrite(enumTypeCPcbPort, ucSlaveAddr, _MP4247_MFR_CTRL4, _MP4247_SUBADDR_LENGTH, _MP4247_DATA_LENGTH_1, (BYTE *)(&g_pstPmicMp4247Data[ucDataIndex].ucMfrCtrl4));
    UserCommonUsbTypeCPmicIICWrite(enumTypeCPcbPort, ucSlaveAddr, _MP4247_MFR_STATUS_MASK, _MP4247_SUBADDR_LENGTH, _MP4247_DATA_LENGTH_1, (BYTE *)(&g_pstPmicMp4247Data[ucDataIndex].ucMfrStatusMask));

    enumTypeCPcbPort = enumTypeCPcbPort;
}

//--------------------------------------------------
// Description  : PMIC Reset Settings
// Input Value  : enumTypeCPcbPort : PCB Port
// Output Value : None
//--------------------------------------------------
void ExternalDeviceInterfaceTypeCPmicMp4247UnattachReset_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort)
{
    BYTE ucDataIndex = 0;
    BYTE ucSlaveAddr = 0;

    // Set Data Index
    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
        ucDataIndex = 0;
        ucSlaveAddr = _D0_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
        ucDataIndex = 1;
        ucSlaveAddr = _D1_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
    {
        ucDataIndex = 2;
        ucSlaveAddr = _P0_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
    {
        ucDataIndex = 3;
        ucSlaveAddr = _ADAPTOR_TYPE_C_PMIC_SLAVE_ADDRESS;
    }

    // Set PMIC Data initial value
    g_pstPmicMp4247Data[ucDataIndex] = tPMIC_MP4247_INITIAL_TABLE[ucDataIndex];

    // Initial Pmic Value
    UserCommonUsbTypeCPmicIICWrite_EXINT0(enumTypeCPcbPort, ucSlaveAddr, _MP4247_OPEARTION, _MP4247_SUBADDR_LENGTH, _MP4247_DATA_LENGTH_1, (BYTE *)(&g_pstPmicMp4247Data[ucDataIndex].ucOperation));
    UserCommonUsbTypeCPmicIICWrite_EXINT0(enumTypeCPcbPort, ucSlaveAddr, _MP4247_VOUT_COMMAND, _MP4247_SUBADDR_LENGTH, _MP4247_DATA_LENGTH_2, (BYTE *)(&g_pstPmicMp4247Data[ucDataIndex].usVoutCommand));
    UserCommonUsbTypeCPmicIICWrite_EXINT0(enumTypeCPcbPort, ucSlaveAddr, _MP4247_MFR_CTRL1, _MP4247_SUBADDR_LENGTH, _MP4247_DATA_LENGTH_1, (BYTE *)(&g_pstPmicMp4247Data[ucDataIndex].ucMfrCtrl1));
    UserCommonUsbTypeCPmicIICWrite_EXINT0(enumTypeCPcbPort, ucSlaveAddr, _MP4247_MFR_CURRENT_LIMIT, _MP4247_SUBADDR_LENGTH, _MP4247_DATA_LENGTH_1, (BYTE *)(&g_pstPmicMp4247Data[ucDataIndex].ucMfrCurrentLimit));
    UserCommonUsbTypeCPmicIICWrite_EXINT0(enumTypeCPcbPort, ucSlaveAddr, _MP4247_MFR_CTRL2, _MP4247_SUBADDR_LENGTH, _MP4247_DATA_LENGTH_1, (BYTE *)(&g_pstPmicMp4247Data[ucDataIndex].ucMfrCtrl2));
    UserCommonUsbTypeCPmicIICWrite_EXINT0(enumTypeCPcbPort, ucSlaveAddr, _MP4247_MFR_CTRL3, _MP4247_SUBADDR_LENGTH, _MP4247_DATA_LENGTH_1, (BYTE *)(&g_pstPmicMp4247Data[ucDataIndex].ucMfrCtrl3));
    UserCommonUsbTypeCPmicIICWrite_EXINT0(enumTypeCPcbPort, ucSlaveAddr, _MP4247_MFR_CTRL4, _MP4247_SUBADDR_LENGTH, _MP4247_DATA_LENGTH_1, (BYTE *)(&g_pstPmicMp4247Data[ucDataIndex].ucMfrCtrl4));
    UserCommonUsbTypeCPmicIICWrite_EXINT0(enumTypeCPcbPort, ucSlaveAddr, _MP4247_MFR_STATUS_MASK, _MP4247_SUBADDR_LENGTH, _MP4247_DATA_LENGTH_1, (BYTE *)(&g_pstPmicMp4247Data[ucDataIndex].ucMfrStatusMask));

    enumTypeCPcbPort = enumTypeCPcbPort;
}

//--------------------------------------------------
// Description  : Control PMIC to Directed Voltage
// Input Value  : enumTypeCPcbPort : PCB Port
//                bPowerDirection : _PD_POWER_SNK / _PD_POWER_SRC
//                usVoltage : 300 ~ 2100 (Unit = 10mV)
//                usCurrent : 0 ~ 500 (Unit = 10mA)
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicMp4247VoltageCurrentSetting(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, WORD usVoltage, WORD usCurrent)
{
    BYTE ucDataIndex = 0;
    BYTE ucSlaveAddr = 0;

    enumPowerDirection = enumPowerDirection;

    // Set Data Index
    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
        ucDataIndex = 0;
        ucSlaveAddr = _D0_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
        ucDataIndex = 1;
        ucSlaveAddr = _D1_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
    {
        ucDataIndex = 2;
        ucSlaveAddr = _P0_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
    {
        ucDataIndex = 3;
        ucSlaveAddr = _ADAPTOR_TYPE_C_PMIC_SLAVE_ADDRESS;
    }

    if(usVoltage > 2000) // maximum 20V
    {
        usVoltage = 2000;
    }

    // -------------------------
    // Operation Mode Setting
    // -------------------------
    g_pstPmicMp4247Data[ucDataIndex].ucOperation = _MP4247_MODE_ON;

    if(UserCommonUsbTypeCPmicIICWrite(enumTypeCPcbPort, ucSlaveAddr, _MP4247_OPEARTION, _MP4247_SUBADDR_LENGTH, _MP4247_DATA_LENGTH_1, (BYTE *)(&g_pstPmicMp4247Data[ucDataIndex].ucOperation)) == _FAIL)
    {
        return _TYPE_C_PMIC_CONTROL_FAIL;
    }

    if(enumPowerDirection == _TYPE_C_PMIC_DIRECTION_SRC)
    {
        // ---------------------
        // Voltage Setting
        // ---------------------

        if(usVoltage <= (300))
        {
            g_pstPmicMp4247Data[ucDataIndex].usVoutCommand = _MP4247_OUTPUT_VOL_5V;
        }
        else if(usVoltage <= (500))
        {
            g_pstPmicMp4247Data[ucDataIndex].usVoutCommand = _MP4247_OUTPUT_VOL_5V;
        }
        else if(usVoltage <= (900))
        {
            g_pstPmicMp4247Data[ucDataIndex].usVoutCommand = _MP4247_OUTPUT_VOL_9V;
        }
        else if(usVoltage <= (1200))
        {
            g_pstPmicMp4247Data[ucDataIndex].usVoutCommand = _MP4247_OUTPUT_VOL_12V;
        }
        else if(usVoltage <= (1500))
        {
            g_pstPmicMp4247Data[ucDataIndex].usVoutCommand = _MP4247_OUTPUT_VOL_15V;
        }
        else if(usVoltage <= (2000))
        {
            g_pstPmicMp4247Data[ucDataIndex].usVoutCommand = _MP4247_OUTPUT_VOL_20V;
        }

        if(UserCommonUsbTypeCPmicIICWrite(enumTypeCPcbPort, ucSlaveAddr, _MP4247_VOUT_COMMAND, _MP4247_SUBADDR_LENGTH, _MP4247_DATA_LENGTH_2, (BYTE *)(&g_pstPmicMp4247Data[ucDataIndex].usVoutCommand)) == _FAIL)
        {
            return _TYPE_C_PMIC_CONTROL_FAIL;
        }

        // ---------------------
        // Current Setting
        // ---------------------

        if(usCurrent <= 100) // < 1A (unit: 10mA)
        {
            g_pstPmicMp4247Data[ucDataIndex].ucMfrCurrentLimit = ((g_pstPmicMp4247Data[ucDataIndex].ucMfrCurrentLimit & _BIT7) | _MP4247_OUTPUT_CURRENT_LIMIT_1_0A);
        }
        else if(usCurrent <= 150)
        {
            g_pstPmicMp4247Data[ucDataIndex].ucMfrCurrentLimit = ((g_pstPmicMp4247Data[ucDataIndex].ucMfrCurrentLimit & _BIT7) | _MP4247_OUTPUT_CURRENT_LIMIT_1_5A);
        }
        else if(usCurrent <= 200)
        {
            g_pstPmicMp4247Data[ucDataIndex].ucMfrCurrentLimit = ((g_pstPmicMp4247Data[ucDataIndex].ucMfrCurrentLimit & _BIT7) | _MP4247_OUTPUT_CURRENT_LIMIT_2_0A);
        }
        else if(usCurrent <= 250)
        {
            g_pstPmicMp4247Data[ucDataIndex].ucMfrCurrentLimit = ((g_pstPmicMp4247Data[ucDataIndex].ucMfrCurrentLimit & _BIT7) | _MP4247_OUTPUT_CURRENT_LIMIT_2_5A);
        }
        else if(usCurrent <= 300)
        {
            g_pstPmicMp4247Data[ucDataIndex].ucMfrCurrentLimit = ((g_pstPmicMp4247Data[ucDataIndex].ucMfrCurrentLimit & _BIT7) | _MP4247_OUTPUT_CURRENT_LIMIT_3_0A);
        }
        else if(usCurrent <= 325)
        {
            g_pstPmicMp4247Data[ucDataIndex].ucMfrCurrentLimit = ((g_pstPmicMp4247Data[ucDataIndex].ucMfrCurrentLimit & _BIT7) | _MP4247_OUTPUT_CURRENT_LIMIT_3_25A);
        }
        else if(usCurrent <= 350)
        {
            g_pstPmicMp4247Data[ucDataIndex].ucMfrCurrentLimit = ((g_pstPmicMp4247Data[ucDataIndex].ucMfrCurrentLimit & _BIT7) | _MP4247_OUTPUT_CURRENT_LIMIT_3_5A);
        }
        else if(usCurrent <= 400)
        {
            g_pstPmicMp4247Data[ucDataIndex].ucMfrCurrentLimit = ((g_pstPmicMp4247Data[ucDataIndex].ucMfrCurrentLimit & _BIT7) | _MP4247_OUTPUT_CURRENT_LIMIT_4_0A);
        }
        else if(usCurrent <= 450)
        {
            g_pstPmicMp4247Data[ucDataIndex].ucMfrCurrentLimit = ((g_pstPmicMp4247Data[ucDataIndex].ucMfrCurrentLimit & _BIT7) | _MP4247_OUTPUT_CURRENT_LIMIT_4_5A);
        }
        else
        {
            g_pstPmicMp4247Data[ucDataIndex].ucMfrCurrentLimit = ((g_pstPmicMp4247Data[ucDataIndex].ucMfrCurrentLimit & _BIT7) | _MP4247_OUTPUT_CURRENT_LIMIT_5_0A);
        }

        g_pstPmicMp4247Data[ucDataIndex].ucMfrCurrentLimit = ((g_pstPmicMp4247Data[ucDataIndex].ucMfrCurrentLimit & _BIT7) | _MP4247_OUTPUT_CURRENT_LIMIT_5_0A); // fix 50MV

        if(UserCommonUsbTypeCPmicIICWrite(enumTypeCPcbPort, ucSlaveAddr, _MP4247_MFR_CURRENT_LIMIT, _MP4247_SUBADDR_LENGTH, _MP4247_DATA_LENGTH_1, (BYTE *)(&g_pstPmicMp4247Data[ucDataIndex].ucMfrCurrentLimit)) == _FAIL)
        {
            return _TYPE_C_PMIC_CONTROL_FAIL;
        }
    }

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : Control PMIC to Directed Voltage
// Input Value  : enumTypeCPcbPort : PCB Port
//                bPowerDirection : _PD_POWER_SNK / _PD_POWER_SRC
//                usVoltage : 300 ~ 2100 (Unit = 10mV)
//                usCurrent : 0 ~ 500 (Unit = 10mA)
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicMp4247VoltageCurrentSetting_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, WORD usVoltage, WORD usCurrent)
{
    BYTE ucDataIndex = 0;
    BYTE ucSlaveAddr = 0;

    enumPowerDirection = enumPowerDirection;

    // Set Data Index
    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
        ucDataIndex = 0;
        ucSlaveAddr = _D0_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
        ucDataIndex = 1;
        ucSlaveAddr = _D1_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
    {
        ucDataIndex = 2;
        ucSlaveAddr = _P0_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
    {
        ucDataIndex = 3;
        ucSlaveAddr = _ADAPTOR_TYPE_C_PMIC_SLAVE_ADDRESS;
    }

    if(usVoltage > 2000) // maximum 20V
    {
        usVoltage = 2000;
    }

    // -------------------------
    // Operation Mode Setting
    // -------------------------
    g_pstPmicMp4247Data[ucDataIndex].ucOperation = _MP4247_MODE_ON;

    if(UserCommonUsbTypeCPmicIICWrite_EXINT0(enumTypeCPcbPort, ucSlaveAddr, _MP4247_OPEARTION, _MP4247_SUBADDR_LENGTH, _MP4247_DATA_LENGTH_1, (BYTE *)(&g_pstPmicMp4247Data[ucDataIndex].ucOperation)) == _FAIL)
    {
        return _TYPE_C_PMIC_CONTROL_FAIL;
    }

    if(enumPowerDirection == _TYPE_C_PMIC_DIRECTION_SRC)
    {
        // ---------------------
        // Voltage Setting
        // ---------------------

        if(usVoltage <= (300))
        {
            g_pstPmicMp4247Data[ucDataIndex].usVoutCommand = _MP4247_OUTPUT_VOL_3V;
        }
        else if(usVoltage <= (500))
        {
            g_pstPmicMp4247Data[ucDataIndex].usVoutCommand = _MP4247_OUTPUT_VOL_5V;
        }
        else if(usVoltage <= (900))
        {
            g_pstPmicMp4247Data[ucDataIndex].usVoutCommand = _MP4247_OUTPUT_VOL_9V;
        }
        else if(usVoltage <= (1200))
        {
            g_pstPmicMp4247Data[ucDataIndex].usVoutCommand = _MP4247_OUTPUT_VOL_12V;
        }
        else if(usVoltage <= (1500))
        {
            g_pstPmicMp4247Data[ucDataIndex].usVoutCommand = _MP4247_OUTPUT_VOL_15V;
        }
        else if(usVoltage <= (2000))
        {
            g_pstPmicMp4247Data[ucDataIndex].usVoutCommand = _MP4247_OUTPUT_VOL_20V;
        }

        if(UserCommonUsbTypeCPmicIICWrite_EXINT0(enumTypeCPcbPort, ucSlaveAddr, _MP4247_VOUT_COMMAND, _MP4247_SUBADDR_LENGTH, _MP4247_DATA_LENGTH_2, (BYTE *)(&g_pstPmicMp4247Data[ucDataIndex].usVoutCommand)) == _FAIL)
        {
            return _TYPE_C_PMIC_CONTROL_FAIL;
        }

        // ---------------------
        // Current Setting
        // ---------------------

        if(usCurrent <= 100) // < 1A (unit: 10mA)
        {
            g_pstPmicMp4247Data[ucDataIndex].ucMfrCurrentLimit = ((g_pstPmicMp4247Data[ucDataIndex].ucMfrCurrentLimit & _BIT7) | _MP4247_OUTPUT_CURRENT_LIMIT_1_0A);
        }
        else if(usCurrent <= 150)
        {
            g_pstPmicMp4247Data[ucDataIndex].ucMfrCurrentLimit = ((g_pstPmicMp4247Data[ucDataIndex].ucMfrCurrentLimit & _BIT7) | _MP4247_OUTPUT_CURRENT_LIMIT_1_5A);
        }
        else if(usCurrent <= 200)
        {
            g_pstPmicMp4247Data[ucDataIndex].ucMfrCurrentLimit = ((g_pstPmicMp4247Data[ucDataIndex].ucMfrCurrentLimit & _BIT7) | _MP4247_OUTPUT_CURRENT_LIMIT_2_0A);
        }
        else if(usCurrent <= 250)
        {
            g_pstPmicMp4247Data[ucDataIndex].ucMfrCurrentLimit = ((g_pstPmicMp4247Data[ucDataIndex].ucMfrCurrentLimit & _BIT7) | _MP4247_OUTPUT_CURRENT_LIMIT_2_5A);
        }
        else if(usCurrent <= 300)
        {
            g_pstPmicMp4247Data[ucDataIndex].ucMfrCurrentLimit = ((g_pstPmicMp4247Data[ucDataIndex].ucMfrCurrentLimit & _BIT7) | _MP4247_OUTPUT_CURRENT_LIMIT_3_0A);
        }
        else if(usCurrent <= 325)
        {
            g_pstPmicMp4247Data[ucDataIndex].ucMfrCurrentLimit = ((g_pstPmicMp4247Data[ucDataIndex].ucMfrCurrentLimit & _BIT7) | _MP4247_OUTPUT_CURRENT_LIMIT_3_25A);
        }
        else if(usCurrent <= 350)
        {
            g_pstPmicMp4247Data[ucDataIndex].ucMfrCurrentLimit = ((g_pstPmicMp4247Data[ucDataIndex].ucMfrCurrentLimit & _BIT7) | _MP4247_OUTPUT_CURRENT_LIMIT_3_5A);
        }
        else if(usCurrent <= 400)
        {
            g_pstPmicMp4247Data[ucDataIndex].ucMfrCurrentLimit = ((g_pstPmicMp4247Data[ucDataIndex].ucMfrCurrentLimit & _BIT7) | _MP4247_OUTPUT_CURRENT_LIMIT_4_0A);
        }
        else if(usCurrent <= 450)
        {
            g_pstPmicMp4247Data[ucDataIndex].ucMfrCurrentLimit = ((g_pstPmicMp4247Data[ucDataIndex].ucMfrCurrentLimit & _BIT7) | _MP4247_OUTPUT_CURRENT_LIMIT_4_5A);
        }
        else
        {
            g_pstPmicMp4247Data[ucDataIndex].ucMfrCurrentLimit = ((g_pstPmicMp4247Data[ucDataIndex].ucMfrCurrentLimit & _BIT7) | _MP4247_OUTPUT_CURRENT_LIMIT_5_0A);
        }

        g_pstPmicMp4247Data[ucDataIndex].ucMfrCurrentLimit = ((g_pstPmicMp4247Data[ucDataIndex].ucMfrCurrentLimit & _BIT7) | _MP4247_OUTPUT_CURRENT_LIMIT_5_0A); // fix 50MV

        if(UserCommonUsbTypeCPmicIICWrite_EXINT0(enumTypeCPcbPort, ucSlaveAddr, _MP4247_MFR_CURRENT_LIMIT, _MP4247_SUBADDR_LENGTH, _MP4247_DATA_LENGTH_1, (BYTE *)(&g_pstPmicMp4247Data[ucDataIndex].ucMfrCurrentLimit)) == _FAIL)
        {
            return _TYPE_C_PMIC_CONTROL_FAIL;
        }
    }

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : Control PMIC to Directed Voltage
// Input Value  : enumTypeCPcbPort : PCB Port
//                bPowerDirection : _PD_POWER_SNK / _PD_POWER_SRC
//                usVoltage : 300 ~ 2100 (Unit = 10mV)
//                usCurrent : 0 ~ 500 (Unit = 10mA)
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicMp4247VoltageCurrentSetting_WDINT(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, WORD usVoltage, WORD usCurrent)
{
    BYTE ucDataIndex = 0;
    BYTE ucSlaveAddr = 0;

    enumPowerDirection = enumPowerDirection;

    // Set Data Index
    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
        ucDataIndex = 0;
        ucSlaveAddr = _D0_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
        ucDataIndex = 1;
        ucSlaveAddr = _D1_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
    {
        ucDataIndex = 2;
        ucSlaveAddr = _P0_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
    {
        ucDataIndex = 3;
        ucSlaveAddr = _ADAPTOR_TYPE_C_PMIC_SLAVE_ADDRESS;
    }

    if(usVoltage > 2000) // maximum 20V
    {
        usVoltage = 2000;
    }

    // -------------------------
    // Operation Mode Setting
    // -------------------------
    g_pstPmicMp4247Data[ucDataIndex].ucOperation = _MP4247_MODE_ON;

    if(UserCommonUsbTypeCPmicIICWrite_WDINT(enumTypeCPcbPort, ucSlaveAddr, _MP4247_OPEARTION, _MP4247_SUBADDR_LENGTH, _MP4247_DATA_LENGTH_1, (BYTE *)(&g_pstPmicMp4247Data[ucDataIndex].ucOperation)) == _FAIL)
    {
        return _TYPE_C_PMIC_CONTROL_FAIL;
    }

    if(enumPowerDirection == _TYPE_C_PMIC_DIRECTION_SRC)
    {
        // ---------------------
        // Voltage Setting
        // ---------------------

        if(usVoltage <= (300))
        {
            g_pstPmicMp4247Data[ucDataIndex].usVoutCommand = _MP4247_OUTPUT_VOL_3V;
        }
        else if(usVoltage <= (500))
        {
            g_pstPmicMp4247Data[ucDataIndex].usVoutCommand = _MP4247_OUTPUT_VOL_5V;
        }
        else if(usVoltage <= (900))
        {
            g_pstPmicMp4247Data[ucDataIndex].usVoutCommand = _MP4247_OUTPUT_VOL_9V;
        }
        else if(usVoltage <= (1200))
        {
            g_pstPmicMp4247Data[ucDataIndex].usVoutCommand = _MP4247_OUTPUT_VOL_12V;
        }
        else if(usVoltage <= (1500))
        {
            g_pstPmicMp4247Data[ucDataIndex].usVoutCommand = _MP4247_OUTPUT_VOL_15V;
        }
        else if(usVoltage <= (2000))
        {
            g_pstPmicMp4247Data[ucDataIndex].usVoutCommand = _MP4247_OUTPUT_VOL_20V;
        }

        if(UserCommonUsbTypeCPmicIICWrite_WDINT(enumTypeCPcbPort, ucSlaveAddr, _MP4247_VOUT_COMMAND, _MP4247_SUBADDR_LENGTH, _MP4247_DATA_LENGTH_2, (BYTE *)(&g_pstPmicMp4247Data[ucDataIndex].usVoutCommand)) == _FAIL)
        {
            return _TYPE_C_PMIC_CONTROL_FAIL;
        }

        // ---------------------
        // Current Setting
        // ---------------------

        if(usCurrent <= 100) // < 1A (unit: 10mA)
        {
            g_pstPmicMp4247Data[ucDataIndex].ucMfrCurrentLimit = ((g_pstPmicMp4247Data[ucDataIndex].ucMfrCurrentLimit & _BIT7) | _MP4247_OUTPUT_CURRENT_LIMIT_1_0A);
        }
        else if(usCurrent <= 150)
        {
            g_pstPmicMp4247Data[ucDataIndex].ucMfrCurrentLimit = ((g_pstPmicMp4247Data[ucDataIndex].ucMfrCurrentLimit & _BIT7) | _MP4247_OUTPUT_CURRENT_LIMIT_1_5A);
        }
        else if(usCurrent <= 200)
        {
            g_pstPmicMp4247Data[ucDataIndex].ucMfrCurrentLimit = ((g_pstPmicMp4247Data[ucDataIndex].ucMfrCurrentLimit & _BIT7) | _MP4247_OUTPUT_CURRENT_LIMIT_2_0A);
        }
        else if(usCurrent <= 250)
        {
            g_pstPmicMp4247Data[ucDataIndex].ucMfrCurrentLimit = ((g_pstPmicMp4247Data[ucDataIndex].ucMfrCurrentLimit & _BIT7) | _MP4247_OUTPUT_CURRENT_LIMIT_2_5A);
        }
        else if(usCurrent <= 300)
        {
            g_pstPmicMp4247Data[ucDataIndex].ucMfrCurrentLimit = ((g_pstPmicMp4247Data[ucDataIndex].ucMfrCurrentLimit & _BIT7) | _MP4247_OUTPUT_CURRENT_LIMIT_3_0A);
        }
        else if(usCurrent <= 325)
        {
            g_pstPmicMp4247Data[ucDataIndex].ucMfrCurrentLimit = ((g_pstPmicMp4247Data[ucDataIndex].ucMfrCurrentLimit & _BIT7) | _MP4247_OUTPUT_CURRENT_LIMIT_3_25A);
        }
        else if(usCurrent <= 350)
        {
            g_pstPmicMp4247Data[ucDataIndex].ucMfrCurrentLimit = ((g_pstPmicMp4247Data[ucDataIndex].ucMfrCurrentLimit & _BIT7) | _MP4247_OUTPUT_CURRENT_LIMIT_3_5A);
        }
        else if(usCurrent <= 400)
        {
            g_pstPmicMp4247Data[ucDataIndex].ucMfrCurrentLimit = ((g_pstPmicMp4247Data[ucDataIndex].ucMfrCurrentLimit & _BIT7) | _MP4247_OUTPUT_CURRENT_LIMIT_4_0A);
        }
        else if(usCurrent <= 450)
        {
            g_pstPmicMp4247Data[ucDataIndex].ucMfrCurrentLimit = ((g_pstPmicMp4247Data[ucDataIndex].ucMfrCurrentLimit & _BIT7) | _MP4247_OUTPUT_CURRENT_LIMIT_4_5A);
        }
        else
        {
            g_pstPmicMp4247Data[ucDataIndex].ucMfrCurrentLimit = ((g_pstPmicMp4247Data[ucDataIndex].ucMfrCurrentLimit & _BIT7) | _MP4247_OUTPUT_CURRENT_LIMIT_5_0A);
        }

        g_pstPmicMp4247Data[ucDataIndex].ucMfrCurrentLimit = ((g_pstPmicMp4247Data[ucDataIndex].ucMfrCurrentLimit & _BIT7) | _MP4247_OUTPUT_CURRENT_LIMIT_5_0A); // fix 50MV

        if(UserCommonUsbTypeCPmicIICWrite_WDINT(enumTypeCPcbPort, ucSlaveAddr, _MP4247_MFR_CURRENT_LIMIT, _MP4247_SUBADDR_LENGTH, _MP4247_DATA_LENGTH_1, (BYTE *)(&g_pstPmicMp4247Data[ucDataIndex].ucMfrCurrentLimit)) == _FAIL)
        {
            return _TYPE_C_PMIC_CONTROL_FAIL;
        }
    }

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : Turn off PMIC
// Input Value  : enumTypeCPcbPort : PCB Port
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicMp4247TurnOff(EnumTypeCPcbPort enumTypeCPcbPort)
{
    BYTE ucDataIndex = 0;
    BYTE ucSlaveAddr = 0;

    // Set Data Index
    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
        ucDataIndex = 0;
        ucSlaveAddr = _D0_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
        ucDataIndex = 1;
        ucSlaveAddr = _D1_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
    {
        ucDataIndex = 2;
        ucSlaveAddr = _P0_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
    {
        ucDataIndex = 3;
        ucSlaveAddr = _ADAPTOR_TYPE_C_PMIC_SLAVE_ADDRESS;
    }

    // Set operation mode
    g_pstPmicMp4247Data[ucDataIndex].ucOperation = _MP4247_MODE_OFF;

    if(UserCommonUsbTypeCPmicIICWrite(enumTypeCPcbPort, ucSlaveAddr, _MP4247_OPEARTION, _MP4247_SUBADDR_LENGTH, _MP4247_DATA_LENGTH_1, (BYTE *)(&g_pstPmicMp4247Data[ucDataIndex].ucOperation)) == _FAIL)
    {
        return _TYPE_C_PMIC_CONTROL_FAIL;
    }

    // Set PMIC output 5V, avoid Hard Reset Peak Voltage
    g_pstPmicMp4247Data[ucDataIndex].usVoutCommand = _MP4247_OUTPUT_VOL_5V;

    if(UserCommonUsbTypeCPmicIICWrite(enumTypeCPcbPort, ucSlaveAddr, _MP4247_VOUT_COMMAND, _MP4247_SUBADDR_LENGTH, _MP4247_DATA_LENGTH_2, (BYTE *)(&g_pstPmicMp4247Data[ucDataIndex].usVoutCommand)) == _FAIL)
    {
        return _TYPE_C_PMIC_CONTROL_FAIL;
    }

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : Turn off PMIC
// Input Value  : enumTypeCPcbPort : PCB Port
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicMp4247TurnOff_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort)
{
    BYTE ucDataIndex = 0;
    BYTE ucSlaveAddr = 0;

    // Set Data Index
    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
        ucDataIndex = 0;
        ucSlaveAddr = _D0_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
        ucDataIndex = 1;
        ucSlaveAddr = _D1_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
    {
        ucDataIndex = 2;
        ucSlaveAddr = _P0_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
    {
        ucDataIndex = 3;
        ucSlaveAddr = _ADAPTOR_TYPE_C_PMIC_SLAVE_ADDRESS;
    }

    // Set operation mode
    g_pstPmicMp4247Data[ucDataIndex].ucOperation = _MP4247_MODE_OFF;

    if(UserCommonUsbTypeCPmicIICWrite_EXINT0(enumTypeCPcbPort, ucSlaveAddr, _MP4247_OPEARTION, _MP4247_SUBADDR_LENGTH, _MP4247_DATA_LENGTH_1, (BYTE *)(&g_pstPmicMp4247Data[ucDataIndex].ucOperation)) == _FAIL)
    {
        return _TYPE_C_PMIC_CONTROL_FAIL;
    }

    // Set PMIC output 5V, avoid Hard Reset Peak Voltage
    g_pstPmicMp4247Data[ucDataIndex].usVoutCommand = _MP4247_OUTPUT_VOL_5V;

    if(UserCommonUsbTypeCPmicIICWrite_EXINT0(enumTypeCPcbPort, ucSlaveAddr, _MP4247_VOUT_COMMAND, _MP4247_SUBADDR_LENGTH, _MP4247_DATA_LENGTH_2, (BYTE *)(&g_pstPmicMp4247Data[ucDataIndex].usVoutCommand)) == _FAIL)
    {
        return _TYPE_C_PMIC_CONTROL_FAIL;
    }

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : Turn off PMIC
// Input Value  : enumTypeCPcbPort : PCB Port
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicMp4247TurnOff_WDINT(EnumTypeCPcbPort enumTypeCPcbPort)
{
    BYTE ucDataIndex = 0;
    BYTE ucSlaveAddr = 0;

    // Set Data Index
    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
        ucDataIndex = 0;
        ucSlaveAddr = _D0_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
        ucDataIndex = 1;
        ucSlaveAddr = _D1_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
    {
        ucDataIndex = 2;
        ucSlaveAddr = _P0_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
    {
        ucDataIndex = 3;
        ucSlaveAddr = _ADAPTOR_TYPE_C_PMIC_SLAVE_ADDRESS;
    }

    // Set operation mode
    g_pstPmicMp4247Data[ucDataIndex].ucOperation = _MP4247_MODE_OFF;

    if(UserCommonUsbTypeCPmicIICWrite_WDINT(enumTypeCPcbPort, ucSlaveAddr, _MP4247_OPEARTION, _MP4247_SUBADDR_LENGTH, _MP4247_DATA_LENGTH_1, (BYTE *)(&g_pstPmicMp4247Data[ucDataIndex].ucOperation)) == _FAIL)
    {
        return _TYPE_C_PMIC_CONTROL_FAIL;
    }

    // Set PMIC output 5V, avoid Hard Reset Peak Voltage
    g_pstPmicMp4247Data[ucDataIndex].usVoutCommand = _MP4247_OUTPUT_VOL_5V;

    if(UserCommonUsbTypeCPmicIICWrite_WDINT(enumTypeCPcbPort, ucSlaveAddr, _MP4247_VOUT_COMMAND, _MP4247_SUBADDR_LENGTH, _MP4247_DATA_LENGTH_2, (BYTE *)(&g_pstPmicMp4247Data[ucDataIndex].usVoutCommand)) == _FAIL)
    {
        return _TYPE_C_PMIC_CONTROL_FAIL;
    }

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : PMIC VBUS Discharge Control
// Input Value  : enumTypeCPcbPort : PCB Port
//                enumEn : _ENABLE / _DISABLE
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicMp4247VbusDischarge(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDischarge enumEn)
{
    BYTE ucDataIndex = 0;
    BYTE ucSlaveAddr = 0;

    // Set Data Index
    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
        ucDataIndex = 0;
        ucSlaveAddr = _D0_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
        ucDataIndex = 1;
        ucSlaveAddr = _D1_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
    {
        ucDataIndex = 2;
        ucSlaveAddr = _P0_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
    {
        ucDataIndex = 3;
        ucSlaveAddr = _ADAPTOR_TYPE_C_PMIC_SLAVE_ADDRESS;
    }

    // Set PMIC VBUS Discharge status
    if(enumEn == _TYPE_C_PMIC_DISCHARGE_ENABLE)
    {
        g_pstPmicMp4247Data[ucDataIndex].ucMfrCtrl1 = ((g_pstPmicMp4247Data[ucDataIndex].ucMfrCtrl1 & ~(_BIT1)) | (_MP4247_DISCHANGE_ENABLE << 1));
    }
    else
    {
        g_pstPmicMp4247Data[ucDataIndex].ucMfrCtrl1 = ((g_pstPmicMp4247Data[ucDataIndex].ucMfrCtrl1 & ~(_BIT1)) | (_MP4247_DISCHANGE_DISABLE << 1));
    }

    // PCB Control
    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
        if(enumEn == _TYPE_C_PMIC_DISCHARGE_ENABLE)
        {
            PCB_D0_VBUS_DISCHARGE_CONTROL(_D0_PMIC_VBUS_DISCHARGE_ON);
        }
        else
        {
            PCB_D0_VBUS_DISCHARGE_CONTROL(_D0_PMIC_VBUS_DISCHARGE_OFF);
        }
    }
    else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
        if(enumEn == _TYPE_C_PMIC_DISCHARGE_ENABLE)
        {
            PCB_D1_VBUS_DISCHARGE_CONTROL(_D1_PMIC_VBUS_DISCHARGE_ON);
        }
        else
        {
            PCB_D1_VBUS_DISCHARGE_CONTROL(_D1_PMIC_VBUS_DISCHARGE_OFF);
        }
    }
    else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
    {
        if(enumEn == _TYPE_C_PMIC_DISCHARGE_ENABLE)
        {
            PCB_P0_VBUS_DISCHARGE_CONTROL(_P0_PMIC_VBUS_DISCHARGE_ON);
        }
        else
        {
            PCB_P0_VBUS_DISCHARGE_CONTROL(_P0_PMIC_VBUS_DISCHARGE_OFF);
        }
    }
    else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
    {
        if(enumEn == _TYPE_C_PMIC_DISCHARGE_ENABLE)
        {
            PCB_ADAPTOR_VBUS_DISCHARGE_CONTROL(_ADAPTOR_PMIC_VBUS_DISCHARGE_ON);
        }
        else
        {
            PCB_ADAPTOR_VBUS_DISCHARGE_CONTROL(_ADAPTOR_PMIC_VBUS_DISCHARGE_OFF);
        }
    }

    // Disable Pmic VBUS Discharge
    if(UserCommonUsbTypeCPmicIICWrite(enumTypeCPcbPort, ucSlaveAddr, _MP4247_MFR_CTRL1, _MP4247_SUBADDR_LENGTH, _MP4247_DATA_LENGTH_1, (BYTE *)(&g_pstPmicMp4247Data[ucDataIndex].ucMfrCtrl1)) == _FAIL)
    {
        return _TYPE_C_PMIC_CONTROL_FAIL;
    }

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : PMIC VBUS Discharge Control
// Input Value  : enumTypeCPcbPort : PCB Port
//                enumEn : _ENABLE / _DISABLE
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicMp4247VbusDischarge_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDischarge enumEn)
{
    BYTE ucDataIndex = 0;
    BYTE ucSlaveAddr = 0;

    // Set Data Index
    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
        ucDataIndex = 0;
        ucSlaveAddr = _D0_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
        ucDataIndex = 1;
        ucSlaveAddr = _D1_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
    {
        ucDataIndex = 2;
        ucSlaveAddr = _P0_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
    {
        ucDataIndex = 3;
        ucSlaveAddr = _ADAPTOR_TYPE_C_PMIC_SLAVE_ADDRESS;
    }

    // Set PMIC VBUS Discharge status
    if(enumEn == _TYPE_C_PMIC_DISCHARGE_ENABLE)
    {
        g_pstPmicMp4247Data[ucDataIndex].ucMfrCtrl1 = ((g_pstPmicMp4247Data[ucDataIndex].ucMfrCtrl1 & ~(_BIT1)) | (_MP4247_DISCHANGE_ENABLE << 1));
    }
    else
    {
        g_pstPmicMp4247Data[ucDataIndex].ucMfrCtrl1 = ((g_pstPmicMp4247Data[ucDataIndex].ucMfrCtrl1 & ~(_BIT1)) | (_MP4247_DISCHANGE_DISABLE << 1));
    }

    // PCB Control
    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
        if(enumEn == _TYPE_C_PMIC_DISCHARGE_ENABLE)
        {
            PCB_D0_VBUS_DISCHARGE_CONTROL(_D0_PMIC_VBUS_DISCHARGE_ON);
        }
        else
        {
            PCB_D0_VBUS_DISCHARGE_CONTROL(_D0_PMIC_VBUS_DISCHARGE_OFF);
        }
    }
    else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
        if(enumEn == _TYPE_C_PMIC_DISCHARGE_ENABLE)
        {
            PCB_D1_VBUS_DISCHARGE_CONTROL(_D1_PMIC_VBUS_DISCHARGE_ON);
        }
        else
        {
            PCB_D1_VBUS_DISCHARGE_CONTROL(_D1_PMIC_VBUS_DISCHARGE_OFF);
        }
    }
    else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
    {
        if(enumEn == _TYPE_C_PMIC_DISCHARGE_ENABLE)
        {
            PCB_P0_VBUS_DISCHARGE_CONTROL(_P0_PMIC_VBUS_DISCHARGE_ON);
        }
        else
        {
            PCB_P0_VBUS_DISCHARGE_CONTROL(_P0_PMIC_VBUS_DISCHARGE_OFF);
        }
    }
    else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
    {
        if(enumEn == _TYPE_C_PMIC_DISCHARGE_ENABLE)
        {
            PCB_ADAPTOR_VBUS_DISCHARGE_CONTROL(_ADAPTOR_PMIC_VBUS_DISCHARGE_ON);
        }
        else
        {
            PCB_ADAPTOR_VBUS_DISCHARGE_CONTROL(_ADAPTOR_PMIC_VBUS_DISCHARGE_OFF);
        }
    }

    // Disable Pmic VBUS Discharge
    if(UserCommonUsbTypeCPmicIICWrite_EXINT0(enumTypeCPcbPort, ucSlaveAddr, _MP4247_MFR_CTRL1, _MP4247_SUBADDR_LENGTH, _MP4247_DATA_LENGTH_1, (BYTE *)(&g_pstPmicMp4247Data[ucDataIndex].ucMfrCtrl1)) == _FAIL)
    {
        return _TYPE_C_PMIC_CONTROL_FAIL;
    }

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : PMIC VBUS Discharge Control
// Input Value  : enumTypeCPcbPort : PCB Port
//                enumEn : _ENABLE / _DISABLE
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicMp4247VbusDischarge_WDINT(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDischarge enumEn)
{
    BYTE ucDataIndex = 0;
    BYTE ucSlaveAddr = 0;

    // Set Data Index
    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
        ucDataIndex = 0;
        ucSlaveAddr = _D0_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
        ucDataIndex = 1;
        ucSlaveAddr = _D1_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
    {
        ucDataIndex = 2;
        ucSlaveAddr = _P0_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
    {
        ucDataIndex = 3;
        ucSlaveAddr = _ADAPTOR_TYPE_C_PMIC_SLAVE_ADDRESS;
    }

    // Set PMIC VBUS Discharge status
    if(enumEn == _TYPE_C_PMIC_DISCHARGE_ENABLE)
    {
        g_pstPmicMp4247Data[ucDataIndex].ucMfrCtrl1 = ((g_pstPmicMp4247Data[ucDataIndex].ucMfrCtrl1 & ~(_BIT1)) | (_MP4247_DISCHANGE_ENABLE << 1));
    }
    else
    {
        g_pstPmicMp4247Data[ucDataIndex].ucMfrCtrl1 = ((g_pstPmicMp4247Data[ucDataIndex].ucMfrCtrl1 & ~(_BIT1)) | (_MP4247_DISCHANGE_DISABLE << 1));
    }

    // PCB Control
    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
        if(enumEn == _TYPE_C_PMIC_DISCHARGE_ENABLE)
        {
            PCB_D0_VBUS_DISCHARGE_CONTROL(_D0_PMIC_VBUS_DISCHARGE_ON);
        }
        else
        {
            PCB_D0_VBUS_DISCHARGE_CONTROL(_D0_PMIC_VBUS_DISCHARGE_OFF);
        }
    }
    else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
        if(enumEn == _TYPE_C_PMIC_DISCHARGE_ENABLE)
        {
            PCB_D1_VBUS_DISCHARGE_CONTROL(_D1_PMIC_VBUS_DISCHARGE_ON);
        }
        else
        {
            PCB_D1_VBUS_DISCHARGE_CONTROL(_D1_PMIC_VBUS_DISCHARGE_OFF);
        }
    }
    else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
    {
        if(enumEn == _TYPE_C_PMIC_DISCHARGE_ENABLE)
        {
            PCB_P0_VBUS_DISCHARGE_CONTROL(_P0_PMIC_VBUS_DISCHARGE_ON);
        }
        else
        {
            PCB_P0_VBUS_DISCHARGE_CONTROL(_P0_PMIC_VBUS_DISCHARGE_OFF);
        }
    }
    else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
    {
        if(enumEn == _TYPE_C_PMIC_DISCHARGE_ENABLE)
        {
            PCB_ADAPTOR_VBUS_DISCHARGE_CONTROL(_ADAPTOR_PMIC_VBUS_DISCHARGE_ON);
        }
        else
        {
            PCB_ADAPTOR_VBUS_DISCHARGE_CONTROL(_ADAPTOR_PMIC_VBUS_DISCHARGE_OFF);
        }
    }

    // Disable Pmic VBUS Discharge
    if(UserCommonUsbTypeCPmicIICWrite_WDINT(enumTypeCPcbPort, ucSlaveAddr, _MP4247_MFR_CTRL1, _MP4247_SUBADDR_LENGTH, _MP4247_DATA_LENGTH_1, (BYTE *)(&g_pstPmicMp4247Data[ucDataIndex].ucMfrCtrl1)) == _FAIL)
    {
        return _TYPE_C_PMIC_CONTROL_FAIL;
    }

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : PMIC Switch Control
// Input Value  : enumTypeCPcbPort : PCB Port
//                enumSwitchControl : _ENABLE / _DISABLE
//                enumPowerDirection : _SRC / _SNK
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicMp4247SwitchControl(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicSwitchControl enumSwitchControl, EnumTypeCPmicDirection enumPowerDirection)
{
    // PCB Control
    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
        if(enumSwitchControl == _TYPE_C_PMIC_SWITCH_CONTROL_ENABLE)
        {
            if(enumPowerDirection == _TYPE_C_PMIC_DIRECTION_SRC)
            {
                PCB_D0_PMIC_VBUS_SINK_CONTROL(_D0_PMIC_VBUS_SINK_SWITCH_OFF);
                PCB_D0_PMIC_VBUS_SOURCE_CONTROL(_D0_PMIC_VBUS_SOURCE_SWITCH_ON);
            }
            else
            {
                PCB_D0_PMIC_VBUS_SOURCE_CONTROL(_D0_PMIC_VBUS_SOURCE_SWITCH_OFF);
                PCB_D0_PMIC_VBUS_SINK_CONTROL(_D0_PMIC_VBUS_SINK_SWITCH_ON);
            }
        }
        else
        {
            PCB_D0_PMIC_VBUS_SOURCE_CONTROL(_D0_PMIC_VBUS_SOURCE_SWITCH_OFF);
        }
    }
    else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
        if(enumSwitchControl == _TYPE_C_PMIC_SWITCH_CONTROL_ENABLE)
        {
            if(enumPowerDirection == _TYPE_C_PMIC_DIRECTION_SRC)
            {
                PCB_D1_PMIC_VBUS_SINK_CONTROL(_D1_PMIC_VBUS_SINK_SWITCH_OFF);
                PCB_D1_PMIC_VBUS_SOURCE_CONTROL(_D1_PMIC_VBUS_SOURCE_SWITCH_ON);
            }
            else
            {
                PCB_D1_PMIC_VBUS_SOURCE_CONTROL(_D1_PMIC_VBUS_SOURCE_SWITCH_OFF);
                PCB_D1_PMIC_VBUS_SINK_CONTROL(_D1_PMIC_VBUS_SINK_SWITCH_ON);
            }
        }
        else
        {
            PCB_D1_PMIC_VBUS_SOURCE_CONTROL(_D1_PMIC_VBUS_SOURCE_SWITCH_OFF);
        }
    }
    else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
    {
        if(enumSwitchControl == _TYPE_C_PMIC_SWITCH_CONTROL_ENABLE)
        {
            if(enumPowerDirection == _TYPE_C_PMIC_DIRECTION_SRC)
            {
                PCB_P0_PMIC_VBUS_SINK_CONTROL(_P0_PMIC_VBUS_SINK_SWITCH_OFF);
                PCB_P0_PMIC_VBUS_SOURCE_CONTROL(_P0_PMIC_VBUS_SOURCE_SWITCH_ON);
            }
            else
            {
                PCB_P0_PMIC_VBUS_SOURCE_CONTROL(_P0_PMIC_VBUS_SOURCE_SWITCH_OFF);
                PCB_P0_PMIC_VBUS_SINK_CONTROL(_P0_PMIC_VBUS_SINK_SWITCH_ON);
            }
        }
        else
        {
            PCB_P0_PMIC_VBUS_SOURCE_CONTROL(_P0_PMIC_VBUS_SOURCE_SWITCH_OFF);
        }
    }
    else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
    {
        if(enumSwitchControl == _TYPE_C_PMIC_SWITCH_CONTROL_ENABLE)
        {
            if(enumPowerDirection == _TYPE_C_PMIC_DIRECTION_SRC)
            {
                PCB_ADAPTOR_PMIC_VBUS_SINK_CONTROL(_ADAPTOR_PMIC_VBUS_SINK_SWITCH_OFF);
                PCB_ADAPTOR_PMIC_VBUS_SOURCE_CONTROL(_ADAPTOR_PMIC_VBUS_SOURCE_SWITCH_ON);
            }
            else
            {
                PCB_ADAPTOR_PMIC_VBUS_SOURCE_CONTROL(_ADAPTOR_PMIC_VBUS_SOURCE_SWITCH_OFF);
                PCB_ADAPTOR_PMIC_VBUS_SINK_CONTROL(_ADAPTOR_PMIC_VBUS_SINK_SWITCH_ON);
            }
        }
        else
        {
            PCB_ADAPTOR_PMIC_VBUS_SOURCE_CONTROL(_ADAPTOR_PMIC_VBUS_SOURCE_SWITCH_OFF);
        }
    }

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : PMIC Switch Control
// Input Value  : enumTypeCPcbPort : PCB Port
//                enumSwitchControl : _ENABLE / _DISABLE
//                enumPowerDirection : _SRC / _SNK
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicMp4247SwitchControl_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicSwitchControl enumSwitchControl, EnumTypeCPmicDirection enumPowerDirection)
{
    // PCB Control
    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
        if(enumSwitchControl == _TYPE_C_PMIC_SWITCH_CONTROL_ENABLE)
        {
            if(enumPowerDirection == _TYPE_C_PMIC_DIRECTION_SRC)
            {
                PCB_D0_PMIC_VBUS_SINK_CONTROL(_D0_PMIC_VBUS_SINK_SWITCH_OFF);
                PCB_D0_PMIC_VBUS_SOURCE_CONTROL(_D0_PMIC_VBUS_SOURCE_SWITCH_ON);
            }
            else
            {
                PCB_D0_PMIC_VBUS_SOURCE_CONTROL(_D0_PMIC_VBUS_SOURCE_SWITCH_OFF);
                PCB_D0_PMIC_VBUS_SINK_CONTROL(_D0_PMIC_VBUS_SINK_SWITCH_ON);
            }
        }
        else
        {
            PCB_D0_PMIC_VBUS_SOURCE_CONTROL(_D0_PMIC_VBUS_SOURCE_SWITCH_OFF);
        }
    }
    else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
        if(enumSwitchControl == _TYPE_C_PMIC_SWITCH_CONTROL_ENABLE)
        {
            if(enumPowerDirection == _TYPE_C_PMIC_DIRECTION_SRC)
            {
                PCB_D1_PMIC_VBUS_SINK_CONTROL(_D1_PMIC_VBUS_SINK_SWITCH_OFF);
                PCB_D1_PMIC_VBUS_SOURCE_CONTROL(_D1_PMIC_VBUS_SOURCE_SWITCH_ON);
            }
            else
            {
                PCB_D1_PMIC_VBUS_SOURCE_CONTROL(_D1_PMIC_VBUS_SOURCE_SWITCH_OFF);
                PCB_D1_PMIC_VBUS_SINK_CONTROL(_D1_PMIC_VBUS_SINK_SWITCH_ON);
            }
        }
        else
        {
            PCB_D1_PMIC_VBUS_SOURCE_CONTROL(_D1_PMIC_VBUS_SOURCE_SWITCH_OFF);
        }
    }
    else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
    {
        if(enumSwitchControl == _TYPE_C_PMIC_SWITCH_CONTROL_ENABLE)
        {
            if(enumPowerDirection == _TYPE_C_PMIC_DIRECTION_SRC)
            {
                PCB_P0_PMIC_VBUS_SINK_CONTROL(_P0_PMIC_VBUS_SINK_SWITCH_OFF);
                PCB_P0_PMIC_VBUS_SOURCE_CONTROL(_P0_PMIC_VBUS_SOURCE_SWITCH_ON);
            }
            else
            {
                PCB_P0_PMIC_VBUS_SOURCE_CONTROL(_P0_PMIC_VBUS_SOURCE_SWITCH_OFF);
                PCB_P0_PMIC_VBUS_SINK_CONTROL(_P0_PMIC_VBUS_SINK_SWITCH_ON);
            }
        }
        else
        {
            PCB_P0_PMIC_VBUS_SOURCE_CONTROL(_P0_PMIC_VBUS_SOURCE_SWITCH_OFF);
        }
    }
    else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
    {
        if(enumSwitchControl == _TYPE_C_PMIC_SWITCH_CONTROL_ENABLE)
        {
            if(enumPowerDirection == _TYPE_C_PMIC_DIRECTION_SRC)
            {
                PCB_ADAPTOR_PMIC_VBUS_SINK_CONTROL(_ADAPTOR_PMIC_VBUS_SINK_SWITCH_OFF);
                PCB_ADAPTOR_PMIC_VBUS_SOURCE_CONTROL(_ADAPTOR_PMIC_VBUS_SOURCE_SWITCH_ON);
            }
            else
            {
                PCB_ADAPTOR_PMIC_VBUS_SOURCE_CONTROL(_ADAPTOR_PMIC_VBUS_SOURCE_SWITCH_OFF);
                PCB_ADAPTOR_PMIC_VBUS_SINK_CONTROL(_ADAPTOR_PMIC_VBUS_SINK_SWITCH_ON);
            }
        }
        else
        {
            PCB_ADAPTOR_PMIC_VBUS_SOURCE_CONTROL(_ADAPTOR_PMIC_VBUS_SOURCE_SWITCH_OFF);
        }
    }

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : PMIC Switch Control
// Input Value  : enumTypeCPcbPort : PCB Port
//                enumSwitchControl : _ENABLE / _DISABLE
//                enumPowerDirection : _SRC / _SNK
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicMp4247SwitchControl_WDINT(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicSwitchControl enumSwitchControl, EnumTypeCPmicDirection enumPowerDirection)
{
    // PCB Control
    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
        if(enumSwitchControl == _TYPE_C_PMIC_SWITCH_CONTROL_ENABLE)
        {
            if(enumPowerDirection == _TYPE_C_PMIC_DIRECTION_SRC)
            {
                PCB_D0_PMIC_VBUS_SINK_CONTROL(_D0_PMIC_VBUS_SINK_SWITCH_OFF);
                PCB_D0_PMIC_VBUS_SOURCE_CONTROL(_D0_PMIC_VBUS_SOURCE_SWITCH_ON);
            }
            else
            {
                PCB_D0_PMIC_VBUS_SOURCE_CONTROL(_D0_PMIC_VBUS_SOURCE_SWITCH_OFF);
                PCB_D0_PMIC_VBUS_SINK_CONTROL(_D0_PMIC_VBUS_SINK_SWITCH_ON);
            }
        }
        else
        {
            PCB_D0_PMIC_VBUS_SOURCE_CONTROL(_D0_PMIC_VBUS_SOURCE_SWITCH_OFF);
        }
    }
    else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
        if(enumSwitchControl == _TYPE_C_PMIC_SWITCH_CONTROL_ENABLE)
        {
            if(enumPowerDirection == _TYPE_C_PMIC_DIRECTION_SRC)
            {
                PCB_D1_PMIC_VBUS_SINK_CONTROL(_D1_PMIC_VBUS_SINK_SWITCH_OFF);
                PCB_D1_PMIC_VBUS_SOURCE_CONTROL(_D1_PMIC_VBUS_SOURCE_SWITCH_ON);
            }
            else
            {
                PCB_D1_PMIC_VBUS_SOURCE_CONTROL(_D1_PMIC_VBUS_SOURCE_SWITCH_OFF);
                PCB_D1_PMIC_VBUS_SINK_CONTROL(_D1_PMIC_VBUS_SINK_SWITCH_ON);
            }
        }
        else
        {
            PCB_D1_PMIC_VBUS_SOURCE_CONTROL(_D1_PMIC_VBUS_SOURCE_SWITCH_OFF);
        }
    }
    else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
    {
        if(enumSwitchControl == _TYPE_C_PMIC_SWITCH_CONTROL_ENABLE)
        {
            if(enumPowerDirection == _TYPE_C_PMIC_DIRECTION_SRC)
            {
                PCB_P0_PMIC_VBUS_SINK_CONTROL(_P0_PMIC_VBUS_SINK_SWITCH_OFF);
                PCB_P0_PMIC_VBUS_SOURCE_CONTROL(_P0_PMIC_VBUS_SOURCE_SWITCH_ON);
            }
            else
            {
                PCB_P0_PMIC_VBUS_SOURCE_CONTROL(_P0_PMIC_VBUS_SOURCE_SWITCH_OFF);
                PCB_P0_PMIC_VBUS_SINK_CONTROL(_P0_PMIC_VBUS_SINK_SWITCH_ON);
            }
        }
        else
        {
            PCB_P0_PMIC_VBUS_SOURCE_CONTROL(_P0_PMIC_VBUS_SOURCE_SWITCH_OFF);
        }
    }
    else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
    {
        if(enumSwitchControl == _TYPE_C_PMIC_SWITCH_CONTROL_ENABLE)
        {
            if(enumPowerDirection == _TYPE_C_PMIC_DIRECTION_SRC)
            {
                PCB_ADAPTOR_PMIC_VBUS_SINK_CONTROL(_ADAPTOR_PMIC_VBUS_SINK_SWITCH_OFF);
                PCB_ADAPTOR_PMIC_VBUS_SOURCE_CONTROL(_ADAPTOR_PMIC_VBUS_SOURCE_SWITCH_ON);
            }
            else
            {
                PCB_ADAPTOR_PMIC_VBUS_SOURCE_CONTROL(_ADAPTOR_PMIC_VBUS_SOURCE_SWITCH_OFF);
                PCB_ADAPTOR_PMIC_VBUS_SINK_CONTROL(_ADAPTOR_PMIC_VBUS_SINK_SWITCH_ON);
            }
        }
        else
        {
            PCB_ADAPTOR_PMIC_VBUS_SOURCE_CONTROL(_ADAPTOR_PMIC_VBUS_SOURCE_SWITCH_OFF);
        }
    }

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

#if(_PORT_CTRL_EMB_PD3_PPS_SUPPORT == _ON)
//--------------------------------------------------
// Description  : PMIC Output Mode Setting
// Input Value  : enumTypeCPcbPort : PCB Port
//                enumOutputMode : Output Mode (Fixed Voltage/PPS)
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicMp4247PpsOutputModeSetting(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, EnumTypeCPDPdoType enumOutputPdoType)
{
    enumTypeCPcbPort = enumTypeCPcbPort;
    enumPowerDirection = enumPowerDirection;
    enumOutputPdoType = enumOutputPdoType;

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : PMIC Output Mode Setting
// Input Value  : enumTypeCPcbPort : PCB Port
//                enumOutputMode : Output Mode (Fixed Voltage/PPS)
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicMp4247PpsOutputModeSetting_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, EnumTypeCPDPdoType enumOutputPdoType)
{
    enumTypeCPcbPort = enumTypeCPcbPort;
    enumPowerDirection = enumPowerDirection;
    enumOutputPdoType = enumOutputPdoType;

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : PMIC Output Mode Setting
// Input Value  : enumTypeCPcbPort : PCB Port
//                enumOutputMode : Output Mode (Fixed Voltage/PPS)
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicMp4247PpsOutputModeSetting_WDINT(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, EnumTypeCPDPdoType enumOutputPdoType)
{
    enumTypeCPcbPort = enumTypeCPcbPort;
    enumPowerDirection = enumPowerDirection;
    enumOutputPdoType = enumOutputPdoType;

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : PMIC Read Output Status
// Input Value  : enumTypeCPcbPort : PCB Port
// Output Value : Output Mode (Fixed Voltage/PPS)
//--------------------------------------------------
EnumTypeCPmicOperationMode ExternalDeviceInterfaceTypeCPmicMp4247ReadPpsOperationModeStatus_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort)
{
    enumTypeCPcbPort = enumTypeCPcbPort;

    return _TYPE_C_PMIC_NONE_MODE_OPERATION;
}
#endif // End of #if(_PORT_CTRL_EMB_PD3_PPS_SUPPORT == _ON)

#if(_EMB_TYPE_C_PMIC_DEBUG == _ON)
//--------------------------------------------------
// Description  : PMIC Status
// Input Value  : enumTypeCPcbPort : PCB Port
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicMp4247DebugCheckStatus(EnumTypeCPcbPort enumTypeCPcbPort)
{
    enumTypeCPcbPort = enumTypeCPcbPort;

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}
#endif // End of #if(_EMB_TYPE_C_PMIC_DEBUG == _ON)

#if(_TYPE_C_PMIC_FW_POLLING_OCP_SUPPORT == _ON)
//--------------------------------------------------
// Description  : PMIC VBUS Current Reading
// Input Value  : enumTypeCPcbPort : PCB Port
// Output Value : usCurrent : 0 ~ 500 (Unit = 10mA)
//--------------------------------------------------
WORD ExternalDeviceInterfaceTypeCPmicMp4247ReadPmicAdcCurrentValue(EnumTypeCPcbPort enumTypeCPcbPort)
{
    enumTypeCPcbPort = enumTypeCPcbPort;

    return 0;
}
#endif // End of #if(_TYPE_C_PMIC_FW_POLLING_OCP_SUPPORT == _ON)

#if(_PORT_CTRL_EMB_UNATTACH_HW_FORCE_VBUS_OFF == _ON)
//--------------------------------------------------
// Description  : PMIC Vbus Force Off Config
// Input Value  : enumTypeCPcbPort : PCB Port
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicMp4247ForceOffConfig(EnumTypeCPcbPort enumTypeCPcbPort)
{
    BYTE ucDataIndex = 0;
    BYTE ucSlaveAddr = 0;

    // Set Data Index
    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
        ucDataIndex = 0;
        ucSlaveAddr = _D0_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
        ucDataIndex = 1;
        ucSlaveAddr = _D1_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
    {
        ucDataIndex = 2;
        ucSlaveAddr = _P0_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
    {
        ucDataIndex = 3;
        ucSlaveAddr = _ADAPTOR_TYPE_C_PMIC_SLAVE_ADDRESS;
    }

    // Set Vbus Force Off Type
    UserCommonUsbTypeCPmicSetForceOffControlType(enumTypeCPcbPort, _TYPE_C_PMIC_FORCE_OFF_BY_IIC);

    // Set operation mode
    g_pstPmicMp4247Data[ucDataIndex].ucOperation = _MP4247_MODE_OFF;

    if(UserCommonUsbTypeCPmicSetForceOffIIC(enumTypeCPcbPort, ucSlaveAddr, _MP4247_OPEARTION, _MP4247_SUBADDR_LENGTH, _MP4247_DATA_LENGTH_1, (BYTE *)(&g_pstPmicMp4247Data[ucDataIndex].ucOperation)) == _FAIL)
    {
        return _TYPE_C_PMIC_CONTROL_FAIL;
    }

    // Set PMIC output 5V, avoid Hard Reset Peak Voltage
    g_pstPmicMp4247Data[ucDataIndex].usVoutCommand = _MP4247_OUTPUT_VOL_5V;

    if(UserCommonUsbTypeCPmicSetForceOffIIC(enumTypeCPcbPort, ucSlaveAddr, _MP4247_VOUT_COMMAND, _MP4247_SUBADDR_LENGTH, _MP4247_DATA_LENGTH_2, (BYTE *)(&g_pstPmicMp4247Data[ucDataIndex].usVoutCommand)) == _FAIL)
    {
        return _TYPE_C_PMIC_CONTROL_FAIL;
    }

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}
#endif // End of #if(_PORT_CTRL_EMB_UNATTACH_HW_FORCE_VBUS_OFF == _ON)
#endif // End of #if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON) && ((_EMB_TYPE_C_0_PMIC_TYPE != _PMIC_NONE) || (_EMB_TYPE_C_1_PMIC_TYPE != _PMIC_NONE)) && (_TYPE_C_PMIC_MP4247_SUPPORT == _ON))

