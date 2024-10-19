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
// ID Code      : ScalerTypeC1Pmic_EXINT0.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"
#include "TypeC1Pmic/ScalerTypeC1Pmic.h"




#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON) && (_EMB_TYPE_C_1_PMIC_TYPE != _PMIC_NONE))
//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_EMB_TYPE_C_1_PMIC_IIC != _PMIC_NO_IIC_PIN)
//--------------------------------------------------
// Description  : Write data to the selected device by TypeC IIC
// Input Value  : ucSlaveAddr      --> Slave address
//                ucSubAddrLength  --> Start address length of selected device
//                usSubAddr        --> Start address of selected device
//                ucDataLength     --> Numbers of data we want to write
//                pucWriteArray    --> Result array
// Output Value : Write result (Fail/Success)
//--------------------------------------------------
BYTE ScalerTypeC1PmicHwIICWrite_EXINT0(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, BYTE ucDataLength, BYTE *pucWriteArray)
{
    BYTE ucI = 0;
    BYTE ucTempLength = 0;

    // Return fail if Data to be transmitted is greater than IIC buffer size
    if((ucDataLength + ucSubAddrLength) > _TYPE_C_1_HW_IIC_WRITE_SIZE)
    {
        return _FAIL;
    }

    // Check if set start before
    if(ScalerTypeC1PmicHwIICSetStartCheck_EXINT0() == _FAIL)
    {
        CLR_TYPE_C_1_PMIC_IIC_IN_EXINT0_LOOP();

        return _FAIL;
    }

    // Reset(Block) IIC module
    ScalerSetBit_EXINT(P7F_80_I2CM_CR0, ~_BIT7, 0x00);

    // Enable IIC module
    ScalerSetBit_EXINT(P7F_80_I2CM_CR0, ~_BIT7, _BIT7);

    // Set 1 byte for FRSIB
    ScalerSetBit_EXINT(P7F_82_I2CM_CR2, ~(_BIT1 | _BIT0), 0x00);

    // Set no repeat start
    ScalerSetBit_EXINT(P7F_83_I2CM_CR3, ~(_BIT4 | _BIT3), 0x00);

    // Wait I2C Fifo Clk Switch to Mcu Clk
    if(ScalerTimerPollingFlagProc_EXINT0(2, P7F_88_I2CM_SR, _BIT5, _TRUE) == _FALSE)
    {
        // Reset(Block) IIC module
        ScalerSetBit_EXINT(P7F_80_I2CM_CR0, ~_BIT7, 0x00);

        // Enable IIC module
        ScalerSetBit_EXINT(P7F_80_I2CM_CR0, ~_BIT7, _BIT7);

        CLR_TYPE_C_1_PMIC_IIC_IN_EXINT0_LOOP();

        return _FAIL;
    }

    // Load Slave Address to IIC Buffer
    ScalerSetByte_EXINT(P7F_89_I2CM_TD, (ucSlaveAddr | _WRITE));

    ScalerSetBit_EXINT(P7F_80_I2CM_CR0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), 0x00);

    BYTE ucDataLengthBackup = ucDataLength;

    switch(ucSubAddrLength)
    {
        case 0:

            // Set data length
            ucTempLength = ((ucDataLengthBackup - 1) << 1);

            break;

        case 1:

            // Load Sub-Address to IIC Buffer
            ScalerSetByte_EXINT(P7F_89_I2CM_TD, (BYTE)(usSubAddr));

            // Set data length
            ucTempLength = (ucDataLengthBackup << 1);

            break;

        case 2:

            // Load First Sub-Address to IIC Buffer
            ScalerSetByte_EXINT(P7F_89_I2CM_TD, (BYTE)((usSubAddr & 0xFF00) >> 8));

            // Load Second Sub-Address to IIC Buffer
            ScalerSetByte_EXINT(P7F_89_I2CM_TD, (BYTE)(usSubAddr));

            // Set data length
            ucTempLength = ((ucDataLengthBackup + 1) << 1);

            break;

        default:

            break;
    }

    // Load data to IIC buffer for transmission
    for(ucI = 0; ucI < ucDataLengthBackup; ucI++)
    {
        ScalerSetByte_EXINT(P7F_89_I2CM_TD, pucWriteArray[ucI]);
    }

    // If int happened while this I2C setting, then return.
    if(GET_TYPE_C_1_PMIC_IIC_EVER_IN_WDINT_LOOP() == _TRUE)
    {
        // Reset(Block) IIC module
        ScalerSetBit_EXINT(P7F_80_I2CM_CR0, ~_BIT7, 0x00);

        // Enable IIC module
        ScalerSetBit_EXINT(P7F_80_I2CM_CR0, ~_BIT7, _BIT7);

        CLR_TYPE_C_1_PMIC_IIC_IN_EXINT0_LOOP();

        return _FAIL;
    }

    // Send IIC command Start
    ScalerSetByte_EXINT(P7F_80_I2CM_CR0, (0xC0 + ucTempLength));

    // Set Pmic I2C set start flag
    SET_TYPE_C_1_PMIC_IIC_SET_START();

    // If interrupt form other process, then wait until transmit finished.
    if((GET_TYPE_C_1_PMIC_IIC_IN_MAIN_LOOP() == _TRUE) || (GET_TYPE_C_1_PMIC_IIC_IN_WDINT_LOOP() == _TRUE))
    {
        // Wait until Master Transmit Complete
        if(ScalerTimerPollingFlagProc_EXINT0(4, P7F_88_I2CM_SR, _BIT0, _TRUE) == _FALSE)
        {
            // Reset(Block) IIC module
            ScalerSetBit_EXINT(P7F_80_I2CM_CR0, ~_BIT7, 0x00);

            // Enable IIC module
            ScalerSetBit_EXINT(P7F_80_I2CM_CR0, ~_BIT7, _BIT7);

            // Clear Pmic I2C set start flag
            CLR_TYPE_C_1_PMIC_IIC_SET_START();

            CLR_TYPE_C_1_PMIC_IIC_IN_EXINT0_LOOP();

            return _FAIL;
        }

        // Clear all flags
        ScalerSetByte_EXINT(P7F_88_I2CM_SR, (_BIT2 | _BIT1 | _BIT0));

        // Clear Pmic I2C set start flag
        CLR_TYPE_C_1_PMIC_IIC_SET_START();

        CLR_TYPE_C_1_PMIC_IIC_IN_EXINT0_LOOP();

        return _SUCCESS;
    }

    CLR_TYPE_C_1_PMIC_IIC_IN_EXINT0_LOOP();

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : Read data from the selected device by TypeC IIC
// Input Value  : ucSlaveAddr      --> Slave address
//                ucSubAddrLength  --> Start address length of selected device
//                usSubAddr        --> Start address of selected device
//                ucDataLength     --> Numbers of data we want to read
//                pucReadArray     --> Result array
// Output Value : Read result (Fail/Success)
//--------------------------------------------------
BYTE ScalerTypeC1PmicHwIICRead_EXINT0(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, BYTE ucDataLength, BYTE *pucReadArray)
{
    BYTE ucI = 0;

    // Return fail if Data to be received is greater than IIC buffer size
    if(ucDataLength > _TYPE_C_1_HW_IIC_BUFFER_SIZE)
    {
        return _FAIL;
    }

    // Check if set start before
    if(ScalerTypeC1PmicHwIICSetStartCheck_EXINT0() == _FAIL)
    {
        CLR_TYPE_C_1_PMIC_IIC_IN_EXINT0_LOOP();

        return _FAIL;
    }

    // Reset(Block) IIC module
    ScalerSetBit_EXINT(P7F_80_I2CM_CR0, ~_BIT7, 0x00);

    // Enable IIC module
    ScalerSetBit_EXINT(P7F_80_I2CM_CR0, ~_BIT7, _BIT7);

    // Wait I2C Fifo Clk Switch to Mcu Clk
    if(ScalerTimerPollingFlagProc_EXINT0(2, P7F_88_I2CM_SR, _BIT5, _TRUE) == _FALSE)
    {
        // Reset(Block) IIC module
        ScalerSetBit_EXINT(P7F_80_I2CM_CR0, ~_BIT7, 0x00);

        // Enable IIC module
        ScalerSetBit_EXINT(P7F_80_I2CM_CR0, ~_BIT7, _BIT7);

        CLR_TYPE_C_1_PMIC_IIC_IN_EXINT0_LOOP();

        return _FAIL;
    }

    // Load Slave Address to IIC Buffer
    switch(ucSubAddrLength)
    {
        case 0:

            // Set 1 byte for FRSIB
            ScalerSetBit_EXINT(P7F_82_I2CM_CR2, ~(_BIT1 | _BIT0), 0x00);

            // Set no repeat start
            ScalerSetBit_EXINT(P7F_83_I2CM_CR3, ~(_BIT4 | _BIT3), 0x00);

            // Load Slave Address to receive data
            ScalerSetByte_EXINT(P7F_89_I2CM_TD, (ucSlaveAddr | _READ));

            break;

        case 1:

            // Set 2 bytes for FRSIB
            ScalerSetBit_EXINT(P7F_82_I2CM_CR2, ~(_BIT1 | _BIT0), _BIT0);

            // Set one repeat start
            ScalerSetBit_EXINT(P7F_83_I2CM_CR3, ~(_BIT4 | _BIT3), _BIT3);

            // Load Slave Address to IIC Buffer
            ScalerSetByte_EXINT(P7F_89_I2CM_TD, (ucSlaveAddr | _WRITE));

            // Load Sub-Address to IIC Buffer
            ScalerSetByte_EXINT(P7F_89_I2CM_TD, (BYTE)(usSubAddr));

            // Load Slave Address to receive data
            ScalerSetByte_EXINT(P7F_89_I2CM_TD, (ucSlaveAddr | _READ));

            break;

        case 2:

            // Set 3 bytes for FRSIB
            ScalerSetBit_EXINT(P7F_82_I2CM_CR2, ~(_BIT1 | _BIT0), _BIT1);

            // Set one repeat start
            ScalerSetBit_EXINT(P7F_83_I2CM_CR3, ~(_BIT4 | _BIT3), _BIT3);

            // Load Slave Address to IIC Buffer
            ScalerSetByte_EXINT(P7F_89_I2CM_TD, (ucSlaveAddr | _WRITE));

            // Load First Sub-Address to IIC Buffer
            ScalerSetByte_EXINT(P7F_89_I2CM_TD, (BYTE)((usSubAddr & 0xFF00) >> 8));

            // Load Second Sub-Address to IIC Buffer
            ScalerSetByte_EXINT(P7F_89_I2CM_TD, (BYTE)(usSubAddr));

            // Load Slave Address to receive data
            ScalerSetByte_EXINT(P7F_89_I2CM_TD, (ucSlaveAddr | _READ));

            break;

        default:

            break;
    }

    // Set data length
    ScalerSetBit_EXINT(P7F_80_I2CM_CR0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), ((ucDataLength - 1) << 1));

    // If int happened while this I2C setting, then return.
    if(GET_TYPE_C_1_PMIC_IIC_EVER_IN_WDINT_LOOP() == _TRUE)
    {
        // Reset(Block) IIC module
        ScalerSetBit_EXINT(P7F_80_I2CM_CR0, ~_BIT7, 0x00);

        // Enable IIC module
        ScalerSetBit_EXINT(P7F_80_I2CM_CR0, ~_BIT7, _BIT7);

        CLR_TYPE_C_1_PMIC_IIC_IN_EXINT0_LOOP();

        return _FAIL;
    }

    // IIC command Start
    ScalerSetBit_EXINT(P7F_80_I2CM_CR0, ~_BIT6, _BIT6);

    // Set Pmic I2C set start flag
    SET_TYPE_C_1_PMIC_IIC_SET_START();

    // Wait until Master Receive Complete
    if(ScalerTimerPollingFlagProc_EXINT0(4, P7F_88_I2CM_SR, _BIT1, _TRUE) == _FALSE)
    {
        // Reset(Block) IIC module
        ScalerSetBit_EXINT(P7F_80_I2CM_CR0, ~_BIT7, 0x00);

        // Enable IIC module
        ScalerSetBit_EXINT(P7F_80_I2CM_CR0, ~_BIT7, _BIT7);

        CLR_TYPE_C_1_PMIC_IIC_IN_EXINT0_LOOP();

        return _FAIL;
    }

    // Wait I2C Fifo Clk Switch to Mcu Clk
    if(ScalerTimerPollingFlagProc_EXINT0(2, P7F_88_I2CM_SR, _BIT5, _TRUE) == _FALSE)
    {
        // Reset(Block) IIC module
        ScalerSetBit_EXINT(P7F_80_I2CM_CR0, ~_BIT7, 0x00);

        // Enable IIC module
        ScalerSetBit_EXINT(P7F_80_I2CM_CR0, ~_BIT7, _BIT7);

        CLR_TYPE_C_1_PMIC_IIC_IN_EXINT0_LOOP();

        return _FAIL;
    }

    // Save received data
    for(ucI = 0; ucI < ucDataLength; ucI++)
    {
        *pucReadArray = ScalerGetByte_EXINT(P7F_89_I2CM_TD);
        pucReadArray++;
    }

    // Clear all flags
    ScalerSetByte_EXINT(P7F_88_I2CM_SR, (_BIT2 | _BIT1 | _BIT0));

    // Clear Pmic I2C set start flag
    CLR_TYPE_C_1_PMIC_IIC_SET_START();

    // If int happened while this I2C setting, then return.
    if(GET_TYPE_C_1_PMIC_IIC_EVER_IN_WDINT_LOOP() == _TRUE)
    {
        // Reset(Block) IIC module
        ScalerSetBit_EXINT(P7F_80_I2CM_CR0, ~_BIT7, 0x00);

        // Enable IIC module
        ScalerSetBit_EXINT(P7F_80_I2CM_CR0, ~_BIT7, _BIT7);

        CLR_TYPE_C_1_PMIC_IIC_IN_EXINT0_LOOP();

        return _FAIL;
    }

    CLR_TYPE_C_1_PMIC_IIC_IN_EXINT0_LOOP();

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : TypeC Hardware IIC Check if Set Start
// Input Value  : None
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
BYTE ScalerTypeC1PmicHwIICSetStartCheck_EXINT0(void)
{
    SET_TYPE_C_1_PMIC_IIC_IN_EXINT0_LOOP();

    SET_TYPE_C_1_PMIC_IIC_EVER_IN_EXINT0_LOOP();

    CLR_TYPE_C_1_PMIC_IIC_EVER_IN_WDINT_LOOP();

    if(GET_TYPE_C_1_PMIC_IIC_SET_START() == _TRUE)
    {
        // Wait until Master Transmit Complete
        if(ScalerTimerPollingFlagProc_EXINT0(4, P7F_88_I2CM_SR, _BIT0, _TRUE) == _FALSE)
        {
            // Reset(Block) IIC module
            ScalerSetBit_EXINT(P7F_80_I2CM_CR0, ~_BIT7, 0x00);

            // Enable IIC module
            ScalerSetBit_EXINT(P7F_80_I2CM_CR0, ~_BIT7, _BIT7);

            // Clear Pmic I2C set start flag
            CLR_TYPE_C_1_PMIC_IIC_SET_START();

            return _FAIL;
        }

        // Clear all flags
        ScalerSetByte_EXINT(P7F_88_I2CM_SR, (_BIT2 | _BIT1 | _BIT0));

        // Clear Pmic I2C set start flag
        CLR_TYPE_C_1_PMIC_IIC_SET_START();
    }

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : Read data from the selected device by TypeC IIC
// Input Value  : ucSlaveAddr      --> Slave address
//                ucSubAddrLength  --> Start address length of selected device
//                usSubAddr        --> Start address of selected device
//                usLength         --> Numbers of data we want to read
//                pucReadArray     --> Result array
// Output Value : Read result (Fail/Success)
//--------------------------------------------------
BYTE ScalerTypeC1PmicIICRead_EXINT0(BYTE ucSlaveAddr, WORD usSubAddr, BYTE ucSubAddrLength, WORD usLength, BYTE *pucReadArray)
{
    BYTE ucSlaveAddress = ucSlaveAddr;
    BYTE ucDataCnt = 0;

    if(usLength == 0)
    {
        return _FAIL;
    }

    while(usLength > 0)
    {
        if(ucSubAddrLength == 1)
        {
            ucSlaveAddress = ucSlaveAddr + (BYTE)((usSubAddr & 0xFF00) >> 7);
        }

        // Receive 24 bytes each time
        ucDataCnt = _TYPE_C_1_HW_IIC_READ_SIZE;

        // Check if more than 24 bytes are needed to be received
        if(usLength > ucDataCnt)
        {
            usLength -= ucDataCnt;
        }
        else
        {
            ucDataCnt = usLength;
            usLength = 0;
        }

        // Execute Hardware IIC Read Command
        if(ScalerTypeC1PmicHwIICRead_EXINT0(ucSlaveAddress, ucSubAddrLength, usSubAddr, ucDataCnt, pucReadArray) == _FAIL)
        {
            return _FAIL;
        }

        // Increase data location
        pucReadArray += ucDataCnt;

        // Increment Sub-Addr for next Read
        usSubAddr += ucDataCnt;
    }

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : Write data to the selected device by TypeC IIC
// Input Value  : ucSlaveAddr      --> Slave address
//                ucSubAddrLength  --> Start address length of selected device
//                usSubAddr        --> Start address of selected device
//                usLength         --> Numbers of data we want to write
//                pucWriteArray    --> Result array
// Output Value : Write result (Fail/Success)
//--------------------------------------------------
BYTE ScalerTypeC1PmicIICWrite_EXINT0(BYTE ucSlaveAddr, WORD usSubAddr, BYTE ucSubAddrLength, WORD usLength, BYTE *pucWriteArray)
{
    BYTE ucSlaveAddress = ucSlaveAddr;
    BYTE ucDataCnt = 0;
    BYTE pucTempData[_TYPE_C_1_HW_IIC_WRITE_SIZE + 2];

    if(usLength == 0)
    {
        return _FAIL;
    }

    while(usLength > 0)
    {
        if(ucSubAddrLength == 1)
        {
            ucSlaveAddress = ucSlaveAddr + (BYTE)((usSubAddr & 0xFF00) >> 7);
        }

        // Transmit max bytes each time
        ucDataCnt = _TYPE_C_1_HW_IIC_WRITE_SIZE - ucSubAddrLength;

        if(usLength > ucDataCnt)
        {
            usLength -= ucDataCnt;
        }
        else
        {
            ucDataCnt = usLength;
            usLength = 0;
        }

        // Save the data to be transfered to pData to ensure the data is saved in XDATA SPACE
        __real_memcpy(pucTempData, pucWriteArray, ucDataCnt);

        // Increase data location
        pucWriteArray += ucDataCnt;

        // Execute Hardware IIC Write Command
        if(ScalerTypeC1PmicHwIICWrite_EXINT0(ucSlaveAddress, ucSubAddrLength, usSubAddr, ucDataCnt, pucTempData) == _FAIL)
        {
            return _FAIL;
        }

        // Increment Sub-Addr for next Write
        usSubAddr += ucDataCnt;
    }

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : PMIC Reset Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PmicIICReset_EXINT0(void)
{
    CLR_TYPE_C_1_PMIC_IIC_IN_MAIN_LOOP();
    CLR_TYPE_C_1_PMIC_IIC_IN_EXINT0_LOOP();
    CLR_TYPE_C_1_PMIC_IIC_IN_WDINT_LOOP();
    CLR_TYPE_C_1_PMIC_IIC_EVER_IN_EXINT0_LOOP();
    CLR_TYPE_C_1_PMIC_IIC_EVER_IN_WDINT_LOOP();

    if(GET_TYPE_C_1_PMIC_IIC_SET_START() == _TRUE)
    {
        // Wait until Master Transmit Complete
        if(ScalerTimerPollingFlagProc_EXINT0(4, P7F_88_I2CM_SR, _BIT0, _TRUE) == _FALSE)
        {
            // Reset(Block) IIC module
            ScalerSetBit_EXINT(P7F_80_I2CM_CR0, ~_BIT7, 0x00);

            // Enable IIC module
            ScalerSetBit_EXINT(P7F_80_I2CM_CR0, ~_BIT7, _BIT7);

            // Clear Pmic I2C set start flag
            CLR_TYPE_C_1_PMIC_IIC_SET_START();

            return;
        }

        // Clear all flags
        ScalerSetByte_EXINT(P7F_88_I2CM_SR, (_BIT2 | _BIT1 | _BIT0));

        // Clear Pmic I2C set start flag
        CLR_TYPE_C_1_PMIC_IIC_SET_START();
    }
}
#endif // End of #if(_EMB_TYPE_C_1_PMIC_IIC != _PMIC_NO_IIC_PIN)

//--------------------------------------------------
// Description  : Type-C 1 PMIC Reset Settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PmicReset_EXINT0(void)
{
    EnumTypeCPcbPort enumTypeCPcbPort = ScalerTypeCxPcbxMapping_EXINT0(_EMB_TYPE_C_1);

    // ========================================================
    // Reset HW Setting
    // ========================================================
#if(_EMB_TYPE_C_1_PMIC_IIC != _PMIC_NO_IIC_PIN)
    ScalerTypeC1PmicIICReset_EXINT0();
#endif

    ExternalDeviceInterfaceTypeCPmicUnattachReset_EXINT0(enumTypeCPcbPort);

    // ========================================================
    // Clear Flag and Reset Value
    // ========================================================

    // Reset PMIC Output Type
    SET_TYPE_C_1_PMIC_OUTPUT_MODE_STATUS(_PD_NONE_SETTING_PDO);

#if((_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) || (_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_10_BIT_ADC))
    SET_TYPE_C_1_PMIC_PEAK_CURRENT_TYPE(_PD_PEAK_CUR_NONE);

#if(_EMB_TYPE_C_1_PMIC_SAFETY_PROTECT_SUPPORT == _ON)
    CLR_TYPE_C_1_PMIC_SAFETY_PROTECT_TRIGGER();
#endif

#elif(_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_POLLING_PMIC)
    SET_TYPE_C_1_PMIC_OCP_CURRENT_VALUE(0);
    CLR_TYPE_C_1_PMIC_OCP_PROTECT_TRIGGER();
#endif // End of #if((_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) || (_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_10_BIT_ADC))

#if(_EMB_TYPE_C_1_PMIC_FW_OVP_UVP_SUPPORT == _ON)
    // Initial OVP/UVP Threshold
    SET_TYPE_C_1_PMIC_FW_OVP_VOLTAGE(0x3FE);
    SET_TYPE_C_1_PMIC_FW_UVP_VOLTAGE(0);
#endif

#if(_EMB_TYPE_C_1_PMIC_CHECK_SUPPORT == _ON)
    CLR_TYPE_C_1_PMIC_OUTPUT_ENABLE();
    SET_TYPE_C_1_PMIC_BIDIR_MODE(_PD_POWER_SNK);
    CLR_TYPE_C_1_PMIC_PROTECT_VALID();
    CLR_TYPE_C_1_PMIC_PROTECT_TIMER_CHECK();
    CLR_TYPE_C_1_PMIC_PROTECT_TIMER_START();
#endif

#if(_PORT_CTRL_EMB_PD3_PPS_SUPPORT == _ON)
    CLR_TYPE_C_1_PMIC_GET_OMF_INFO_START();
    SET_TYPE_C_1_PMIC_OMF_INFO(_TYPE_C_PMIC_CV_MODE_OPERATION);
#endif
}

//--------------------------------------------------
// Description  : Control Type-C 1 PMIC to Directed Voltage
// Input Value  : bAction : _ON / _OFF
//                bPowerDirection : _PD_POWER_SNK / _PD_POWER_SRC
//                usVoltage : 0 ~ 2100 (Unit = 10mV) / usCurrent : 0 ~ 500 (Unit = 10mA)
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
BYTE ScalerTypeC1PmicSetting_EXINT0(bit bAction, bit bPowerDirection, EnumTypeCPDPdoType enumPdoType, WORD usVoltage, WORD usCurrent, EnumTypeCPDPeakCurType enumPeakCurrent)
{
    EnumTypeCPcbPort enumTypeCPcbPort = ScalerTypeCxPcbxMapping_EXINT0(_EMB_TYPE_C_1);
    EnumTypeCPmicControlResult enumResult = _TYPE_C_PMIC_CONTROL_FAIL;
    EnumTypeCPmicDirection enumDirection = _TYPE_C_PMIC_DIRECTION_SNK;

    // Avoid Warning
    enumPeakCurrent = enumPeakCurrent;

    // ========================================================
    // CTS Parameter Adjustment
    // ========================================================

    // Minimum Current Setting for different PDO type
    if(enumPdoType == _PD_3_PROGRAMMABLE_PDO)
    {
        usCurrent = MAXOF(usCurrent, _TYPE_C_1_PMIC_MIN_PPS_CURRENT);
    }
    else
    {
        usCurrent = MAXOF(usCurrent, _TYPE_C_1_PMIC_MIN_CURRENT);
    }

#if(_EMB_TYPE_C_1_PMIC_FW_OVP_UVP_SUPPORT == _ON)
    // ========================================================
    // OVP/UVP Setting Flow
    // ========================================================

    // Caculate OVP & UVP threshold
    if(bAction == _ON)
    {
        WORD usOVPThreshold = 0x0000;
        WORD usUVPThreshold = 0x0000;

        // Translate Voltage to SARADC Value
        usOVPThreshold = ((WORD)(((DWORD)usVoltage * 1024) / _EMB_TYPE_C_1_PMIC_VBUS_MAX_VOLTAGE));
        usUVPThreshold = usOVPThreshold;

        // Set Threshold for OVP
        usOVPThreshold = ((WORD)((((DWORD)(usOVPThreshold)) * _EMB_TYPE_C_1_PMIC_FW_OVP_THRESHOLD) / 100));

        if(usOVPThreshold >= 0x3FF)
        {
            usOVPThreshold = 0x3FE;
        }

        SET_TYPE_C_1_PMIC_FW_OVP_VOLTAGE(usOVPThreshold);

        // Set Threshold for UVP
        if(enumPdoType == _PD_3_PROGRAMMABLE_PDO)
        {
            usUVPThreshold = ((WORD)(((DWORD)_TYPE_C_1_PMIC_FW_UVP_PPS_THRESHOLD * 1024) / _EMB_TYPE_C_1_PMIC_VBUS_MAX_VOLTAGE));
        }
        else
        {
            usUVPThreshold = ((WORD)((((DWORD)(usUVPThreshold)) * _EMB_TYPE_C_1_PMIC_FW_UVP_THRESHOLD) / 100));
        }

        SET_TYPE_C_1_PMIC_FW_UVP_VOLTAGE(usUVPThreshold);

        // Disable INT
        ScalerTypeCAdcInOutCompIntControl_EXINT0(_TYPE_C_CHANNEL_1_VMON, _DISABLE);
        CLR_TYPE_C_1_PMIC_FW_OVP_UVP_CHECK();

        // Set OVP/UVP range
        ScalerTypeCAdcInOutCompIntSetting_EXINT0(_TYPE_C_CHANNEL_1_VMON, usOVPThreshold, usUVPThreshold, _TYPE_C_ADC_WITHOUT_RANGE);
    }
    else
    {
        // Disable INT
        ScalerTypeCAdcInOutCompIntControl_EXINT0(_TYPE_C_CHANNEL_1_VMON, _DISABLE);
        CLR_TYPE_C_1_PMIC_FW_OVP_UVP_CHECK();
    }
#endif // End of #if(_EMB_TYPE_C_1_PMIC_FW_OVP_UVP_SUPPORT == _ON)

#if((_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) || (_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_10_BIT_ADC))
    // ========================================================
    // OCP by SARADC Setting Flow
    // ========================================================

    // Set Peak Current Mode
    SET_TYPE_C_1_PMIC_PEAK_CURRENT_TYPE(enumPeakCurrent);

#if(_EMB_TYPE_C_1_PMIC_SAFETY_PROTECT_SUPPORT == _ON)
    // Clear PMIC Safety Protect Trigger Flag
    CLR_TYPE_C_1_PMIC_SAFETY_PROTECT_TRIGGER();
#endif

    // Caculate OCP threshold
    if((bAction == _ON) && (bPowerDirection == _PD_POWER_SRC))
    {
        BYTE ucCount = 0;
        BYTE pucOcpThreshold[3] = {0, 0, 0};
        WORD usCurrentTemp = 0;
        WORD usDelayTemp = 0;

        // ====================================================
        // Set OCP Threshold
        // ====================================================

        // Clear OCP Protect Level
        SET_TYPE_C_1_PMIC_FW_OCP_PROTECT_LEVEL(0);

        // Calculate OCP current to 10-bit SARADC Code Value
        SET_TYPE_C_1_PMIC_FW_OCP_CURRENT(0, ((WORD)((((DWORD)usCurrent * _EMB_TYPE_C_1_PMIC_FW_OCP_CURRENT_VALUE / 100) * 1024) / _EMB_TYPE_C_1_PMIC_IOUT_MAX_CURRENT)));
        SET_TYPE_C_1_PMIC_FW_OCP_DELAY(0, _EMB_TYPE_C_1_PMIC_FW_OCP_DELAY_SHUTDOWN);


        // ====================================================
        // Check Peak Current Format
        // ====================================================

        // OCP Threshold Sorting from small to big
        if((GET_TYPE_C_1_PMIC_PEAK_CURRENT_PROTECT() == _TYPE_C_PEAK_CURRENT_PROTECT_ENABLE) && (enumPeakCurrent != _PD_PEAK_CUR_NONE))
        {
            // Peak Current Setting from Spec
            if(enumPeakCurrent == _PD_PEAK_CUR_1)
            {
                // Peak Current Threshold 1: 110%(10ms)
                pucOcpThreshold[0] = 110;

                // Peak Current Threshold 2: 125%(2ms)
                pucOcpThreshold[1] = 125;

                // Peak Current Threshold 3: 150%(1ms)
                pucOcpThreshold[2] = 150;
            }
            else if(enumPeakCurrent == _PD_PEAK_CUR_2)
            {
                // Peak Current Threshold 1: 125%(10ms)
                pucOcpThreshold[0] = 125;

                // Peak Current Threshold 2: 150%(2ms)
                pucOcpThreshold[1] = 150;

                // Peak Current Threshold 3: 200%(1ms)
                pucOcpThreshold[2] = 200;
            }
            else if(enumPeakCurrent == _PD_PEAK_CUR_3)
            {
                // Peak Current Threshold 1: 150%(10ms)
                pucOcpThreshold[0] = 150;

                // Peak Current Threshold 2: 175%(2ms)
                pucOcpThreshold[1] = 175;

                // Peak Current Threshold 3: 200%(1ms)
                pucOcpThreshold[2] = 200;
            }

            // Peak Current Threshold 1 to 10-bit SARADC Code Value
            SET_TYPE_C_1_PMIC_FW_OCP_CURRENT(1, ((WORD)((((DWORD)usCurrent * pucOcpThreshold[0] / 100) * 1024) / _EMB_TYPE_C_1_PMIC_IOUT_MAX_CURRENT)));
            SET_TYPE_C_1_PMIC_FW_OCP_DELAY(1, 10);

            // Peak Current Threshold 2 to 10-bit SARADC Code Value
            SET_TYPE_C_1_PMIC_FW_OCP_CURRENT(2, ((WORD)((((DWORD)usCurrent * pucOcpThreshold[1] / 100) * 1024) / _EMB_TYPE_C_1_PMIC_IOUT_MAX_CURRENT)));
            SET_TYPE_C_1_PMIC_FW_OCP_DELAY(2, 2);

            // Peak Current Threshold 3 to 10-bit SARADC Code Value
            SET_TYPE_C_1_PMIC_FW_OCP_CURRENT(3, ((WORD)((((DWORD)usCurrent * pucOcpThreshold[2] / 100) * 1024) / _EMB_TYPE_C_1_PMIC_IOUT_MAX_CURRENT)));
            SET_TYPE_C_1_PMIC_FW_OCP_DELAY(3, 1);

            // Sorting OCP Level
            for(ucCount = 0; ucCount < 3; ucCount++)
            {
                if(GET_TYPE_C_1_PMIC_FW_OCP_CURRENT(ucCount) > GET_TYPE_C_1_PMIC_FW_OCP_CURRENT(ucCount + 1))
                {
                    usCurrentTemp = GET_TYPE_C_1_PMIC_FW_OCP_CURRENT(ucCount);
                    usDelayTemp = GET_TYPE_C_1_PMIC_FW_OCP_DELAY(ucCount);

                    SET_TYPE_C_1_PMIC_FW_OCP_CURRENT((ucCount), GET_TYPE_C_1_PMIC_FW_OCP_CURRENT(ucCount + 1));
                    SET_TYPE_C_1_PMIC_FW_OCP_DELAY((ucCount), GET_TYPE_C_1_PMIC_FW_OCP_DELAY(ucCount + 1));

                    SET_TYPE_C_1_PMIC_FW_OCP_CURRENT((ucCount + 1), usCurrentTemp);
                    SET_TYPE_C_1_PMIC_FW_OCP_DELAY((ucCount + 1), usDelayTemp);
                }
            }
        }
        else
        {
            SET_TYPE_C_1_PMIC_FW_OCP_CURRENT(1, 0x03FF);
            SET_TYPE_C_1_PMIC_FW_OCP_DELAY(1, 0);
            SET_TYPE_C_1_PMIC_FW_OCP_CURRENT(2, 0x03FF);
            SET_TYPE_C_1_PMIC_FW_OCP_DELAY(2, 0);
            SET_TYPE_C_1_PMIC_FW_OCP_CURRENT(3, 0x03FF);
            SET_TYPE_C_1_PMIC_FW_OCP_DELAY(3, 0);
        }

#if(_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC)
#if(_HW_MCU_SARADC_SUPPORT == _SARADC_5BIT_MSB)
        // Round-up last 5-bit for avoiding low resolution error
        SET_TYPE_C_1_PMIC_FW_OCP_CURRENT(0, (((GET_TYPE_C_1_PMIC_FW_OCP_CURRENT(0) & 0x001F) != 0x00) ? ((GET_TYPE_C_1_PMIC_FW_OCP_CURRENT(0) & 0x03E0) + 0x20) : GET_TYPE_C_1_PMIC_FW_OCP_CURRENT(0)));
        SET_TYPE_C_1_PMIC_FW_OCP_CURRENT(1, (((GET_TYPE_C_1_PMIC_FW_OCP_CURRENT(1) & 0x001F) != 0x00) ? ((GET_TYPE_C_1_PMIC_FW_OCP_CURRENT(1) & 0x03E0) + 0x20) : GET_TYPE_C_1_PMIC_FW_OCP_CURRENT(1)));
        SET_TYPE_C_1_PMIC_FW_OCP_CURRENT(2, (((GET_TYPE_C_1_PMIC_FW_OCP_CURRENT(2) & 0x001F) != 0x00) ? ((GET_TYPE_C_1_PMIC_FW_OCP_CURRENT(2) & 0x03E0) + 0x20) : GET_TYPE_C_1_PMIC_FW_OCP_CURRENT(2)));
        SET_TYPE_C_1_PMIC_FW_OCP_CURRENT(3, (((GET_TYPE_C_1_PMIC_FW_OCP_CURRENT(3) & 0x001F) != 0x00) ? ((GET_TYPE_C_1_PMIC_FW_OCP_CURRENT(3) & 0x03E0) + 0x20) : GET_TYPE_C_1_PMIC_FW_OCP_CURRENT(3)));

#elif(_HW_MCU_SARADC_SUPPORT == _SARADC_8BIT)
        // Round-up last 2-bit for avoiding low resolution error
        SET_TYPE_C_1_PMIC_FW_OCP_CURRENT(0, (((GET_TYPE_C_1_PMIC_FW_OCP_CURRENT(0) & 0x0003) != 0x00) ? ((GET_TYPE_C_1_PMIC_FW_OCP_CURRENT(0) & 0x03FC) + 0x04) : GET_TYPE_C_1_PMIC_FW_OCP_CURRENT(0)));
        SET_TYPE_C_1_PMIC_FW_OCP_CURRENT(1, (((GET_TYPE_C_1_PMIC_FW_OCP_CURRENT(1) & 0x0003) != 0x00) ? ((GET_TYPE_C_1_PMIC_FW_OCP_CURRENT(1) & 0x03FC) + 0x04) : GET_TYPE_C_1_PMIC_FW_OCP_CURRENT(1)));
        SET_TYPE_C_1_PMIC_FW_OCP_CURRENT(2, (((GET_TYPE_C_1_PMIC_FW_OCP_CURRENT(2) & 0x0003) != 0x00) ? ((GET_TYPE_C_1_PMIC_FW_OCP_CURRENT(2) & 0x03FC) + 0x04) : GET_TYPE_C_1_PMIC_FW_OCP_CURRENT(2)));
        SET_TYPE_C_1_PMIC_FW_OCP_CURRENT(3, (((GET_TYPE_C_1_PMIC_FW_OCP_CURRENT(3) & 0x0003) != 0x00) ? ((GET_TYPE_C_1_PMIC_FW_OCP_CURRENT(3) & 0x03FC) + 0x04) : GET_TYPE_C_1_PMIC_FW_OCP_CURRENT(3)));
#endif
#endif // End of #if(_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC)

        // Disable INT & Clear INT Flag
        ScalerTypeCAdcInOutCompIntControl_EXINT0(_TYPE_C_1_IMON, _DISABLE);

        // Set Range to check if Vbus current will be triggered OCP Current.
        // Do not enable INT immediately for avoiding inrush current.
        ScalerTypeCAdcInOutCompIntSetting_EXINT0(_TYPE_C_1_IMON, 0xFFFF, GET_TYPE_C_1_PMIC_FW_OCP_CURRENT(0), _TYPE_C_ADC_WITHIN_RANGE);

#if(_EMB_TYPE_C_1_PMIC_SAFETY_PROTECT_SUPPORT == _ON)
        // ====================================================
        // Safety Protect Setting Flow
        // ====================================================

        // Set Flag to Active PMIC Protection Timer When Vbus Power Stable
        SET_TYPE_C_1_PMIC_PROTECT_TIMER_CHECK();

        // Set Safety Current Value
        SET_TYPE_C_1_PMIC_SAFETY_CURRENT_VALUE((WORD)(((DWORD)_EMB_TYPE_C_1_PMIC_SAFETY_POWER_LIMIT * 10000) / usVoltage));

        // Minimum Output Current Assurance
        SET_TYPE_C_1_PMIC_SAFETY_CURRENT_VALUE(MAXOF(usCurrent, GET_TYPE_C_1_PMIC_SAFETY_CURRENT_VALUE()));
#endif // #if(_EMB_TYPE_C_1_PMIC_SAFETY_PROTECT_SUPPORT == _ON)


        // ====================================================
        // PMIC Current Setting Adjustment
        // ====================================================

        // Add more 66% OCP value in order to avoid triggering the PMIC self OCP
        usCurrent = ((WORD)((((DWORD)usCurrent) * _TYPE_C_1_PMIC_HW_OCP_MAX) / 100));
    }
    else
    {
        // Disable INT & Clear INT Flag
        ScalerTypeCAdcInOutCompIntControl_EXINT0(_TYPE_C_1_IMON, _DISABLE);
    }

#elif(_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_POLLING_PMIC)
    // ========================================================
    // OCP by Polling PMIC's ADC Value Setting Flow
    // ========================================================

    // Clear PMIC OCP Protect Trigger Flag
    CLR_TYPE_C_1_PMIC_OCP_PROTECT_TRIGGER();

    if((bAction == _ON) && (bPowerDirection == _PD_POWER_SRC))
    {
        // Set Flag to Active PMIC Protection Timer When Vbus Power Stable
        SET_TYPE_C_1_PMIC_PROTECT_TIMER_CHECK();

        // Set Safety Current Value
        SET_TYPE_C_1_PMIC_OCP_CURRENT_VALUE((WORD)(((DWORD)usCurrent * _EMB_TYPE_C_1_PMIC_FW_OCP_CURRENT_VALUE) / 100));

        // ====================================================
        // PMIC Current Setting Adjustment
        // ====================================================

        // Add more 66% OCP value in order to avoid triggering the PMIC self OCP
        usCurrent = ((WORD)((((DWORD)usCurrent) * _TYPE_C_1_PMIC_HW_OCP_MAX) / 100));
    }
#endif // End of #if((_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) || (_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_10_BIT_ADC))

#if(_EMB_TYPE_C_1_PMIC_VOLTAGE_COMPENSATION == _ON)
    // ========================================================
    // Vbus Voltage Compensation Setting Flow
    // ========================================================
    if((bAction == _ON) && (bPowerDirection == _PD_POWER_SRC))
    {
        // Set Flag to Active PMIC Protection Timer When Vbus Power Stable
        SET_TYPE_C_1_PMIC_PROTECT_TIMER_CHECK();
    }
#endif

#if(_EMB_TYPE_C_1_PMIC_INT_PIN_CHECK_METHOD == _TYPE_C_PMIC_INT_PIN_CHECK_BY_POLLING)
    // ========================================================
    // PMIC INT_Pin Checking Setting Flow
    // ========================================================
    if((bAction == _ON) && (bPowerDirection == _PD_POWER_SRC))
    {
        // Set Flag to Active PMIC Protection Timer When Vbus Power Stable
        SET_TYPE_C_1_PMIC_PROTECT_TIMER_CHECK();
    }
#endif

#if(_PORT_CTRL_EMB_PD3_PPS_SUPPORT == _ON)
    // ====================================================
    // PD 3.0 PPS Support Flow
    // ====================================================
    if((bAction == _ON) && (bPowerDirection == _PD_POWER_SRC))
    {
        SET_TYPE_C_1_PMIC_GET_OMF_INFO_START();
    }
    else
    {
        CLR_TYPE_C_1_PMIC_GET_OMF_INFO_START();
    }
#endif

#if(_EMB_TYPE_C_1_PMIC_CHECK_SUPPORT == _ON)
#if(_EMB_TYPE_C_PMIC_DEBUG == _ON)
    // ========================================================
    // PMIC Debug Setting Flow
    // ========================================================
    if((bAction == _ON) && (bPowerDirection == _PD_POWER_SRC))
    {
        // Set Flag to Active PMIC Protection Timer When Vbus Power Stable
        SET_TYPE_C_1_PMIC_PROTECT_TIMER_CHECK();
    }
#endif

    // ========================================================
    // PMIC Check Support Setting Flow
    // ========================================================
    if((bAction == _ON) && (bPowerDirection == _PD_POWER_SRC))
    {
        SET_TYPE_C_1_PMIC_OUTPUT_ENABLE();
        SET_TYPE_C_1_PMIC_BIDIR_MODE(_PD_POWER_SRC);
    }
    else
    {
        CLR_TYPE_C_1_PMIC_OUTPUT_ENABLE();
        SET_TYPE_C_1_PMIC_BIDIR_MODE(_PD_POWER_SNK);

        // Clear PMIC Protection Timer Check Flag When Turn off Vbus Power
        CLR_TYPE_C_1_PMIC_PROTECT_TIMER_CHECK();
    }

    CLR_TYPE_C_1_PMIC_PROTECT_VALID();
#endif

    // ====================================================
    // PMIC Setting Flow
    // ====================================================
    if(bAction == _ON)
    {
        ScalerTypeC1PmicSwitchControl_EXINT0(_ON, bPowerDirection);

        if(bPowerDirection == _PD_POWER_SRC)
        {
            enumDirection = _TYPE_C_PMIC_DIRECTION_SRC;
        }
        else
        {
            enumDirection = _TYPE_C_PMIC_DIRECTION_SNK;
        }

        if(GET_TYPE_C_1_PMIC_OUTPUT_MODE_STATUS() != enumPdoType)
        {
#if(_PORT_CTRL_EMB_PD3_PPS_SUPPORT == _ON)
            if(ExternalDeviceInterfaceTypeCPmicPpsOutputModeSetting_EXINT0(enumTypeCPcbPort, enumDirection, enumPdoType) == _TYPE_C_PMIC_CONTROL_FAIL)
            {
                return _FAIL;
            }
#endif
            SET_TYPE_C_1_PMIC_OUTPUT_MODE_STATUS(enumPdoType);
        }

        enumResult = ExternalDeviceInterfaceTypeCPmicVoltageCurrentSetting_EXINT0(enumTypeCPcbPort, enumDirection, usVoltage, usCurrent);
    }
    else
    {
        // Reset PMIC Output Type
        SET_TYPE_C_1_PMIC_OUTPUT_MODE_STATUS(enumPdoType);

        enumResult = ExternalDeviceInterfaceTypeCPmicTurnOff_EXINT0(enumTypeCPcbPort);
    }

    // ====================================================
    // Check PMIC Control Result
    // ====================================================
    if(enumResult == _TYPE_C_PMIC_CONTROL_SUCCESS)
    {
        // ================================================
        // Update Setting Information
        // ================================================
        SET_TYPE_C_1_REQ_PWR((WORD)((DWORD)usVoltage * usCurrent / 1000)); // Calculate Requested Power to Unit = 0.1W
        SET_TYPE_C_1_OUTPUT_VOL(usVoltage);
        SET_TYPE_C_1_OUTPUT_CUR(usCurrent);
        SET_TYPE_C_1_VBUS_STATUS(bAction);

        return _SUCCESS;
    }
    else
    {
        return _FAIL;
    }
}

//--------------------------------------------------
// Description  : Type-C 1 PMIC VBUS Discharge Control
// Input Value  : bEn : _ENABLE / _DISABLE
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
BYTE ScalerTypeC1PmicVbusDischarge_EXINT0(bit bEn)
{
    EnumTypeCPmicDischarge enumDischarge = _TYPE_C_PMIC_DISCHARGE_DISABLE;

    if(bEn == _ON)
    {
        enumDischarge = _TYPE_C_PMIC_DISCHARGE_ENABLE;
    }
    else
    {
        ScalerTypeC1PmicSwitchControl_EXINT0(_OFF, _PD_POWER_SNK);
        enumDischarge = _TYPE_C_PMIC_DISCHARGE_DISABLE;
    }

    if(ExternalDeviceInterfaceTypeCPmicVbusDischarge_EXINT0(ScalerTypeCxPcbxMapping_EXINT0(_EMB_TYPE_C_1), enumDischarge) == _TYPE_C_PMIC_CONTROL_SUCCESS)
    {
        return _SUCCESS;
    }
    else
    {
        return _FAIL;
    }
}

//--------------------------------------------------
// Description  : Type-C 1 PMIC Switch Control
// Input Value  : bEn : _ENABLE / _DISABLE
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
BYTE ScalerTypeC1PmicSwitchControl_EXINT0(bit bEn, bit bPowerDirection)
{
    EnumTypeCPmicSwitchControl enumSwitchControl = _TYPE_C_PMIC_SWITCH_CONTROL_DISABLE;
    EnumTypeCPmicDirection enumDirection = _TYPE_C_PMIC_DIRECTION_SNK;

    if(bEn == _ON)
    {
        enumSwitchControl = _TYPE_C_PMIC_SWITCH_CONTROL_ENABLE;
    }
    else
    {
        enumSwitchControl = _TYPE_C_PMIC_SWITCH_CONTROL_DISABLE;
    }

    if(bPowerDirection == _PD_POWER_SRC)
    {
        enumDirection = _TYPE_C_PMIC_DIRECTION_SRC;
    }
    else
    {
        enumDirection = _TYPE_C_PMIC_DIRECTION_SNK;
    }


    if(ExternalDeviceInterfaceTypeCPmicSwitchControl_EXINT0(ScalerTypeCxPcbxMapping_EXINT0(_EMB_TYPE_C_1), enumSwitchControl, enumDirection) == _TYPE_C_PMIC_CONTROL_SUCCESS)
    {
        return _SUCCESS;
    }
    else
    {
        return _FAIL;
    }
}

#if(_PORT_CTRL_EMB_PD3_PPS_SUPPORT == _ON)
//--------------------------------------------------
// Description  : PMIC Read Output Status
// Input Value  : None
// Output Value : Output Mode (Fixed Voltage/PPS)
//--------------------------------------------------
EnumTypeCPmicOperationMode ScalerTypeC1PmicReadPpsOperationModeStatus_EXINT0(void)
{
    EnumTypeCPcbPort enumTypeCPcbPort = ScalerTypeCxPcbxMapping_EXINT0(_EMB_TYPE_C_1);

    // Check GPIO status
    if(ScalerTypeCGetPmicAlertDetectStatus_EXINT0(enumTypeCPcbPort) == _TRUE)
    {
        if(ExternalDeviceInterfaceTypeCPmicReadPpsOperationModeStatus_EXINT0(enumTypeCPcbPort) == _TYPE_C_PMIC_CC_MODE_OPERATION)
        {
            SET_TYPE_C_1_PMIC_OMF_INFO(_TYPE_C_PMIC_CC_MODE_OPERATION);
        }
        else
        {
            SET_TYPE_C_1_PMIC_OMF_INFO(_TYPE_C_PMIC_CV_MODE_OPERATION);
        }
    }

    return GET_TYPE_C_1_PMIC_OMF_INFO();
}
#endif

#if(_EMB_TYPE_C_1_PMIC_CHECK_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Type-C 1 PMIC Protection Start
// Input Value  : enumPowerRole : _TYPE_C_POWER_SRC / _TYPE_C_POWER_SNK
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PmicProtectStart_EXINT0(EnumTypeCPowerRole enumPowerRole)
{
    if(enumPowerRole == _TYPE_C_POWER_SRC)
    {
        // Enable PMIC Protection Int
#if(_EMB_TYPE_C_1_PMIC_FW_OVP_UVP_SUPPORT == _ON)
        // Enable OVP/UVP Int
        ScalerTypeCAdcInOutCompIntControl_EXINT0(_TYPE_C_CHANNEL_1_VMON, _ENABLE);
        SET_TYPE_C_1_PMIC_FW_OVP_UVP_CHECK();
#endif

#if((_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) || (_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_10_BIT_ADC))
        // Enable OCP Int
        ScalerTypeCAdcInOutCompIntControl_EXINT0(_TYPE_C_1_IMON, _ENABLE);
#endif
    }
    else
    {
        // Enable PMIC Protection Int
#if(_EMB_TYPE_C_1_PMIC_FW_OVP_UVP_SUPPORT == _ON)
        // Enable OVP/UVP Int
        ScalerTypeCAdcInOutCompIntControl_EXINT0(_TYPE_C_CHANNEL_1_VMON, _ENABLE);
        SET_TYPE_C_1_PMIC_FW_OVP_UVP_CHECK();
#endif
    }

    // Check if Any PMIC Protection Timer Needs to be Actived
    if(GET_TYPE_C_1_PMIC_PROTECT_TIMER_CHECK() == _TRUE)
    {
        CLR_TYPE_C_1_PMIC_PROTECT_TIMER_CHECK();

        // Set PMIC Protection Timer Start Flag to Active PMIC Protection Tracking Timer in Main Loop
        SET_TYPE_C_1_PMIC_PROTECT_TIMER_START();
    }

    SET_TYPE_C_1_PMIC_PROTECT_VALID();
}

#if((_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) || (_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_10_BIT_ADC))
//--------------------------------------------------
// Description  : Type-C 1 PMIC OCP interrupt handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PmicOcpIntHandler_EXINT0(void)
{
    WORD usCurrentValue = 0;
    WORD usOcpDelay = GET_TYPE_C_1_PMIC_FW_OCP_DELAY(0);
    BYTE ucCount = 0;

    // ====================================================
    // Check Comparator INT Flag
    // ====================================================
    if(ScalerTypeCAdcInOutCompIntCheck_EXINT0(_TYPE_C_1_IMON) == _FALSE)
    {
        return;
    }


    // ====================================================
    // Vbus Shorting Detect
    // ====================================================

#if(_EMB_TYPE_C_1_PMIC_FW_OVP_UVP_SUPPORT != _ON)
    // Only when not support OVP/UVP for avoiding repeated protection
    for(ucCount = 0; ucCount < 2; ucCount++)
    {
        // Compare value in "ADC Ideal Data" Form
        if(ScalerTypeCAdcCorrectionToIdealData_EXINT0(_TYPE_C_CHANNEL_1_VMON, ScalerTypeCAdcGetAdcOutput_EXINT0(_TYPE_C_CHANNEL_1_VMON)) < GET_TYPE_C_1_PMIC_SHORT_VOLTAGE())
        {
            // Disable Pmic
            ScalerTypeC1PmicSetting_EXINT0(_OFF, _PD_POWER_SNK, _PD_NONE_SETTING_PDO, 0, 0, _PD_PEAK_CUR_NONE);

#if(_TYPE_C_EIZO_CUSTOMIZED_PMIC_SIC437A_SUPPORT == _ON)
            // [Eizo] SIC437A Customized Power Control : OCP
            ScalerTypeC1PmicSic437aPmicOcpProc_EXINT0();
#endif

            // Set OCP Event
            ScalerTypeC1PdSetSystemEvent_EXINT0(_PD_SYS_EVENT_POWER_OCP);

            return;
        }
    }
#endif // End of #if(_EMB_TYPE_C_1_PMIC_FW_OVP_UVP_SUPPORT != _ON)


    // ====================================================
    // Determine OCP Trigger Level
    // ====================================================

    // Get Vbus Current Value & Transfer Raw Data to Ideal Data
    usCurrentValue = ScalerTypeCAdcCorrectionToIdealData_EXINT0(_TYPE_C_1_IMON, ScalerTypeCAdcGetAdcOutput_EXINT0(_TYPE_C_1_IMON));

    // Use Ocp Threshold to Determine Delay Time
    for(ucCount = 0; ucCount < 4; ucCount++)
    {
        // Compare value in "ADC Ideal Data" Form
        if(usCurrentValue > GET_TYPE_C_1_PMIC_FW_OCP_CURRENT(ucCount))
        {
            // Record Trigger Level
            SET_TYPE_C_1_PMIC_FW_OCP_PROTECT_LEVEL(ucCount);

            // Set Delay Time
            usOcpDelay = GET_TYPE_C_1_PMIC_FW_OCP_DELAY(ucCount);
        }
    }


    // ====================================================
    // Set OCP Delay
    // ====================================================

    if(usOcpDelay == 0)
    {
        // OCP Protection Debounce check
        for(ucCount = 0; ucCount < GET_TYPE_C_1_PMIC_OCP_JUDGE_DEBOUNCE(); ucCount++)
        {
            // Get Vbus Current Value & Transfer Raw Data to Ideal Data
            usCurrentValue = ScalerTypeCAdcCorrectionToIdealData_EXINT0(_TYPE_C_1_IMON, ScalerTypeCAdcGetAdcOutput_EXINT0(_TYPE_C_1_IMON));

            // Compare OCP Trigger Level with Vbus current in "ADC Ideal Data" Form
            if(usCurrentValue < GET_TYPE_C_1_PMIC_FW_OCP_CURRENT(GET_TYPE_C_1_PMIC_FW_OCP_PROTECT_LEVEL()))
            {
                // Recover Pmic to Normal State

                // Disable INT & Clear INT Flag
                ScalerTypeCAdcInOutCompIntControl_EXINT0(_TYPE_C_1_IMON, _DISABLE);

                // Set to lowest OCP level
                ScalerTypeCAdcInOutCompIntSetting_EXINT0(_TYPE_C_1_IMON, 0xFFFF, GET_TYPE_C_1_PMIC_FW_OCP_CURRENT(0), _TYPE_C_ADC_WITHIN_RANGE);

                // Clear flag and enable INT
                ScalerTypeCAdcInOutCompIntControl_EXINT0(_TYPE_C_1_IMON, _ENABLE);

                // Clear Trigger Level
                SET_TYPE_C_1_PMIC_FW_OCP_PROTECT_LEVEL(0);

                return;
            }
        }

        // Disable Pmic
        ScalerTypeC1PmicSetting_EXINT0(_OFF, _PD_POWER_SNK, _PD_NONE_SETTING_PDO, 0, 0, _PD_PEAK_CUR_NONE);

#if(_TYPE_C_EIZO_CUSTOMIZED_PMIC_SIC437A_SUPPORT == _ON)
        // [Eizo] SIC437A Customized Power Control : OCP
        ScalerTypeC1PmicSic437aPmicOcpProc_EXINT0();
#endif

        // Set OCP Event
        ScalerTypeC1PdSetSystemEvent_EXINT0(_PD_SYS_EVENT_POWER_OCP);
    }
    else
    {
        // Disable INT & Clear INT Flag
        ScalerTypeCAdcInOutCompIntControl_EXINT0(_TYPE_C_1_IMON, _DISABLE);

        // Check OCP triggers highest level or not
        if(GET_TYPE_C_1_PMIC_FW_OCP_PROTECT_LEVEL() < 3)
        {
            // Set to next OCP level
            ScalerTypeCAdcInOutCompIntSetting_EXINT0(_TYPE_C_1_IMON, 0xFFFF, GET_TYPE_C_1_PMIC_FW_OCP_CURRENT(GET_TYPE_C_1_PMIC_FW_OCP_PROTECT_LEVEL() + 1), _TYPE_C_ADC_WITHIN_RANGE);

            // Enable INT & Clear INT Flag
            ScalerTypeCAdcInOutCompIntControl_EXINT0(_TYPE_C_1_IMON, _ENABLE);
        }

        // Check if OCP Delay is lower than WD Timer limit
        if(usOcpDelay < _TYPE_C_1_WD_EVENT_TIME)
        {
            // Set WD Timer Event Time
            SET_TYPE_C_1_PMIC_WD_TIMER_VALUE(usOcpDelay);

            // Active WD Timer Event For Pmic Shutdown Delay
            ScalerTimerWDActivateTimerEvent_EXINT0(usOcpDelay, _SCALER_WD_TIMER_EVENT_TYPE_C_1_PMIC_FW_OCP_DELAY);
        }
        else
        {
            // Set WD Timer Event Time
            SET_TYPE_C_1_PMIC_WD_TIMER_VALUE(_TYPE_C_1_WD_EVENT_TIME);

            // Active WD Timer Event For Pmic Shutdown Delay
            ScalerTimerWDActivateTimerEvent_EXINT0(_TYPE_C_1_WD_EVENT_TIME, _SCALER_WD_TIMER_EVENT_TYPE_C_1_PMIC_FW_OCP_DELAY);
        }
    }
}
#endif // End of #if((_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) || (_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_10_BIT_ADC))

#if(_EMB_TYPE_C_1_PMIC_FW_OVP_UVP_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Type-C 1 PMIC OVP interrupt handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PmicOvpUvpIntHandler_EXINT0(void)
{
    BYTE ucCount = 0;

    // Check if OVP or UVP protect trigger
    if(ScalerTypeCAdcCorrectionToIdealData_EXINT0(_TYPE_C_CHANNEL_1_VMON, ScalerTypeCAdcGetAdcOutput_EXINT0(_TYPE_C_CHANNEL_1_VMON)) >= GET_TYPE_C_1_PMIC_FW_OVP_VOLTAGE())
    {
        // OVP Protection Debounce check
        for(ucCount = 0; ucCount < GET_TYPE_C_1_PMIC_OVP_JUDGE_DEBOUNCE(); ucCount++)
        {
            // Compare OVP Trigger Level with Vbus voltage in "ADC Ideal Data" Form
            if(ScalerTypeCAdcCorrectionToIdealData_EXINT0(_TYPE_C_CHANNEL_1_VMON, ScalerTypeCAdcGetAdcOutput_EXINT0(_TYPE_C_CHANNEL_1_VMON)) < GET_TYPE_C_1_PMIC_FW_OVP_VOLTAGE())
            {
                // Recover Pmic to Normal State

                // Clear flag and enable INT
                ScalerTypeCAdcInOutCompIntControl_EXINT0(_TYPE_C_CHANNEL_1_VMON, _ENABLE);

                return;
            }
        }

        // Set OVP Event
        ScalerTypeC1PdSetSystemEvent_EXINT0(_PD_SYS_EVENT_POWER_OVP);
    }
    else
    {
        // UVP Protection Debounce check
        for(ucCount = 0; ucCount < GET_TYPE_C_1_PMIC_UVP_JUDGE_DEBOUNCE(); ucCount++)
        {
            // Compare UVP Trigger Level with Vbus voltage in "ADC Ideal Data" Form
            if(ScalerTypeCAdcCorrectionToIdealData_EXINT0(_TYPE_C_CHANNEL_1_VMON, ScalerTypeCAdcGetAdcOutput_EXINT0(_TYPE_C_CHANNEL_1_VMON)) > GET_TYPE_C_1_PMIC_FW_UVP_VOLTAGE())
            {
                // Recover Pmic to Normal State

                // Clear flag and enable INT
                ScalerTypeCAdcInOutCompIntControl_EXINT0(_TYPE_C_CHANNEL_1_VMON, _ENABLE);

                return;
            }
        }

        // Set UVP Event
        ScalerTypeC1PdSetSystemEvent_EXINT0(_PD_SYS_EVENT_POWER_UVP);
    }

    // Disable PMIC
    ScalerTypeC1PmicSetting_EXINT0(_OFF, _PD_POWER_SNK, _PD_NONE_SETTING_PDO, 0, 0, _PD_PEAK_CUR_NONE);

#if(_TYPE_C_EIZO_CUSTOMIZED_PMIC_SIC437A_SUPPORT == _ON)
    // [Eizo] SIC437A Customized Power Control : OVP
    ScalerTypeC1PmicSic437aPmicOvpProc_EXINT0();
#endif
}

//--------------------------------------------------
// Description  : Get Type-C 1 PMIC FW OVP/UVP Check Flag
// Input Value  : None
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerTypeC1PmicGetFwOvpUvpCheckFlag_EXINT0(void)
{
    return GET_TYPE_C_1_PMIC_FW_OVP_UVP_CHECK();
}
#endif // End of #if(_EMB_TYPE_C_1_PMIC_FW_OVP_UVP_SUPPORT == _ON)
#endif // End of #if(_EMB_TYPE_C_1_PMIC_CHECK_SUPPORT == _ON)


/////////////////////////////////////
// EIZO PMIC SIC437A CUSTOMIZED FW //
/////////////////////////////////////
#if(_TYPE_C_EIZO_CUSTOMIZED_PMIC_SIC437A_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Type-C 1 Attached Power Control Flow
// Input Value  : enumPowerRole : _TYPE_C_POWER_SRC / _TYPE_C_POWER_SNK
// Output Value : Control Result : _SUCCESS / _FAIL
//--------------------------------------------------
BYTE ScalerTypeC1PmicSic437aAttachProc_EXINT0(EnumTypeCPowerRole enumPowerRole)
{
    if(ExternalDeviceInterfaceTypeCPmicAttachProc_EXINT0(ScalerTypeCxPcbxMapping_EXINT0(_EMB_TYPE_C_1), enumPowerRole) == _TYPE_C_PMIC_CONTROL_SUCCESS)
    {
        return _SUCCESS;
    }
    else
    {
        return _FAIL;
    }
}

//--------------------------------------------------
// Description  : Type-C 1 Unattached Power Control Flow
// Input Value  : enumPowerRole : _TYPE_C_POWER_SRC / _TYPE_C_POWER_SNK
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PmicSic437aUnattachProc_EXINT0(EnumTypeCPowerRole enumPowerRole)
{
    EnumTypeCVbusCheckType enumVbusCheckType = ExternalDeviceInterfaceTypeCPmicUnattachProc_EXINT0(ScalerTypeCxPcbxMapping_EXINT0(_EMB_TYPE_C_1), enumPowerRole);

    ScalerTypeC1PmicSic437aVbusCheckProc_EXINT0(enumVbusCheckType);
}

//--------------------------------------------------
// Description  : Type-C 1 Power Transition Start Control Flow
// Input Value  : usVoltage : 300 ~ 2100 (Unit = 10mV)
//                usCurrent : 0 ~ 500 (Unit = 10mA)
//                pusSrcAdjustPowerTime : 25 ~ 35 (Unit = ms)
// Output Value : Control Result : _SUCCESS / _FAIL
//--------------------------------------------------
BYTE ScalerTypeC1PmicSic437aTransitionStartProc_EXINT0(WORD usVoltage, WORD usCurrent, WORD *pusSrcAdjustPowerTime)
{
    if(ExternalDeviceInterfaceTypeCPmicTransitionStartProc_EXINT0(ScalerTypeCxPcbxMapping_EXINT0(_EMB_TYPE_C_1), usVoltage, usCurrent, pusSrcAdjustPowerTime) == _TYPE_C_PMIC_CONTROL_SUCCESS)
    {
        return _SUCCESS;
    }
    else
    {
        return _FAIL;
    }
}

//--------------------------------------------------
// Description  : Type-C 1 Power Role Swap Start Control Flow
// Input Value  : enumPowerRole : _TYPE_C_POWER_SRC / _TYPE_C_POWER_SNK
// Output Value : Control Result : _SUCCESS / _FAIL
//--------------------------------------------------
BYTE ScalerTypeC1PmicSic437aPRSwapStartProc_EXINT0(EnumTypeCPowerRole enumPowerRole)
{
    if(ExternalDeviceInterfaceTypeCPmicPRSwapStartProc_EXINT0(ScalerTypeCxPcbxMapping_EXINT0(_EMB_TYPE_C_1), enumPowerRole) == _TYPE_C_PMIC_CONTROL_SUCCESS)
    {
        return _SUCCESS;
    }
    else
    {
        return _FAIL;
    }
}

//--------------------------------------------------
// Description  : Type-C 1 Send/Receive Hard Reset Control Flow
// Input Value  : enumPowerRole : _TYPE_C_POWER_SRC / _TYPE_C_POWER_SNK
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PmicSic437aHardRstStartProc_EXINT0(EnumTypeCPowerRole enumPowerRole)
{
    EnumTypeCVbusCheckType enumVbusCheckType = ExternalDeviceInterfaceTypeCPmicHardRstStartProc_EXINT0(ScalerTypeCxPcbxMapping_EXINT0(_EMB_TYPE_C_1), enumPowerRole);

    ScalerTypeC1PmicSic437aVbusCheckProc_EXINT0(enumVbusCheckType);
}

//--------------------------------------------------
// Description  : Type-C 1 Detect OCP Event Control Flow
// Input Value  : None
// Output Value : Control Result : _SUCCESS / _FAIL
//--------------------------------------------------
BYTE ScalerTypeC1PmicSic437aPmicOcpProc_EXINT0(void)
{
    if(ExternalDeviceInterfaceTypeCPmicOcpProc_EXINT0(ScalerTypeCxPcbxMapping_EXINT0(_EMB_TYPE_C_1)) == _TYPE_C_PMIC_CONTROL_SUCCESS)
    {
        return _SUCCESS;
    }
    else
    {
        return _FAIL;
    }
}

//--------------------------------------------------
// Description  : Type-C 1 Detect OVP Event Control Flow
// Input Value  : None
// Output Value : Control Result : _SUCCESS / _FAIL
//--------------------------------------------------
BYTE ScalerTypeC1PmicSic437aPmicOvpProc_EXINT0(void)
{
    if(ExternalDeviceInterfaceTypeCPmicOvpProc_EXINT0(ScalerTypeCxPcbxMapping_EXINT0(_EMB_TYPE_C_1)) == _TYPE_C_PMIC_CONTROL_SUCCESS)
    {
        return _SUCCESS;
    }
    else
    {
        return _FAIL;
    }
}

//--------------------------------------------------
// Description  : Get Type-C 1 PMIC EIZO Vbus 5V Check Flag
// Input Value  : None
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerTypeC1PmicSic437aGetVbus5VCheckFlag_EXINT0(void)
{
    return GET_TYPE_C_1_PMIC_EIZO_VBUS_5V_CHECK();
}

//--------------------------------------------------
// Description  : Clear Type-C 1 PMIC EIZO Vbus 5V Check Flag
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PmicSic437aClrVbus5VCheckFlag_EXINT0(void)
{
    CLR_TYPE_C_1_PMIC_EIZO_VBUS_5V_CHECK();
}

//--------------------------------------------------
// Description  : Get Type-C 1 PMIC EIZO Vbus 0V Check Flag
// Input Value  : None
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerTypeC1PmicSic437aGetVbus0VCheckFlag_EXINT0(void)
{
    return GET_TYPE_C_1_PMIC_EIZO_VBUS_0V_CHECK();
}

//--------------------------------------------------
// Description  : Clear Type-C 1 PMIC EIZO Vbus 0V Check Flag
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PmicSic437aClrVbus0VCheckFlag_EXINT0(void)
{
    CLR_TYPE_C_1_PMIC_EIZO_VBUS_0V_CHECK();
}

//--------------------------------------------------
// Description  : Type-C 1 Vbus Check Control Flow
// Input Value  : Vbus Check Type : _TYPE_C_VBUS_CHECK_0V / _TYPE_C_VBUS_CHECK_5V
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PmicSic437aVbusCheckProc_EXINT0(EnumTypeCVbusCheckType enumVbusCheckType)
{
    if(enumVbusCheckType == _TYPE_C_VBUS_CHECK_5V)
    {
        // Set ADC In Out Range Comparator = In Range vSafe5V
        ScalerTypeCAdcInOutCompIntSetting_EXINT0(_TYPE_C_CHANNEL_1_VMON, GET_TYPE_C_1_5V_UP_BND(), GET_TYPE_C_1_5V_LOW_BND(), _TYPE_C_ADC_WITHIN_RANGE);

        // Enable INT
        ScalerTypeCAdcInOutCompIntControl_EXINT0(_TYPE_C_CHANNEL_1_VMON, _ENABLE);

        // Set Vbus 5V Check Flag
        SET_TYPE_C_1_PMIC_EIZO_VBUS_5V_CHECK();
    }
    else if(enumVbusCheckType == _TYPE_C_VBUS_CHECK_0V)
    {
        // Set ADC In Out Range Comparator = In Range vSafe0V
        ScalerTypeCAdcInOutCompIntSetting_EXINT0(_TYPE_C_CHANNEL_1_VMON, GET_TYPE_C_1_0V_UP_BND(), 0, _TYPE_C_ADC_WITHIN_RANGE);

        // Enable INT
        ScalerTypeCAdcInOutCompIntControl_EXINT0(_TYPE_C_CHANNEL_1_VMON, _ENABLE);

        // Set Vbus 0V Check Flag
        SET_TYPE_C_1_PMIC_EIZO_VBUS_0V_CHECK();
    }
}

//--------------------------------------------------
// Description  : Type-C 1 Vbus 5V Power Control Flow
// Input Value  : enumPowerRole : _TYPE_C_POWER_SRC / _TYPE_C_POWER_SNK
// Output Value : Vbus Check Type : _TYPE_C_VBUS_CHECK_0V / _TYPE_C_VBUS_CHECK_5V
//--------------------------------------------------
EnumTypeCVbusCheckType ScalerTypeC1PmicSic437aVbus5VReadyProc_EXINT0(EnumTypeCPowerRole enumPowerRole)
{
    return ExternalDeviceInterfaceTypeCPmicVbus5VReadyProc_EXINT0(ScalerTypeCxPcbxMapping_EXINT0(_EMB_TYPE_C_1), enumPowerRole);
}

//--------------------------------------------------
// Description  : Type-C 1 Vbus 0V Power Control Flow
// Input Value  : enumPowerRole : _TYPE_C_POWER_SRC / _TYPE_C_POWER_SNK
// Output Value : Control Result : _SUCCESS / _FAIL
//--------------------------------------------------
BYTE ScalerTypeC1PmicSic437aVbus0VReadyProc_EXINT0(EnumTypeCPowerRole enumPowerRole)
{
    if(ExternalDeviceInterfaceTypeCPmicVbus0VReadyProc_EXINT0(ScalerTypeCxPcbxMapping_EXINT0(_EMB_TYPE_C_1), enumPowerRole) == _TYPE_C_PMIC_CONTROL_SUCCESS)
    {
        return _SUCCESS;
    }
    else
    {
        return _FAIL;
    }
}
#endif // End of #if(_TYPE_C_EIZO_CUSTOMIZED_PMIC_SIC437A_SUPPORT == _ON)
#endif // End of #if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON) && (_EMB_TYPE_C_1_PMIC_TYPE != _PMIC_NONE))

