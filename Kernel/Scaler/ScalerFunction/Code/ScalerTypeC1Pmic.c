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
// ID Code      : ScalerTypeC1Pmic.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"
#include "TypeC1Pmic/ScalerTypeC1Pmic.h"

#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON) && (_EMB_TYPE_C_1_PMIC_TYPE != _PMIC_NONE))

#if(_TYPE_C_1_PMIC_FORCE_OUTPUT == _ON)
#warning "Type-C 1 Pmic would force output, Type-C port don't connect anything."
#endif // End of #if(_TYPE_C_1_PMIC_FORCE_OUTPUT == _ON)

#if((_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD != _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) && (_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD != _TYPE_C_PMIC_FW_OCP_BY_10_BIT_ADC))
#warning "NOTE: Type-C 1 Peak_Current OCP is NOT protect! Please make sure PDO_Peak_Current is set to '_PD_PEAK_CUR_NONE', otherwise User_OCP protection must be support!"
#endif // End of #if((_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD != _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) && (_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD != _TYPE_C_PMIC_FW_OCP_BY_10_BIT_ADC))

#endif // End of #if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON) && (_EMB_TYPE_C_1_PMIC_TYPE != _PMIC_NONE))


#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON) && (_EMB_TYPE_C_1_PMIC_TYPE != _PMIC_NONE))
//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
volatile StructPmicIICStatus g_stTypeC1PmicIICStatus;
volatile StructTypeC1PmicControl g_stTypeC1PmicControl;


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_EMB_TYPE_C_1_PMIC_IIC != _PMIC_NO_IIC_PIN)
//--------------------------------------------------
// Description  : TypeC Hardware IIC Initial Settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PmicHwIICInitial(void)
{
    // Reset IIC module
    ScalerSetBit(P7F_80_I2CM_CR0, ~_BIT7, 0x00);

    // Enable IIC module and disable TOR
    ScalerSetBit(P7F_80_I2CM_CR0, ~(_BIT7 | _BIT0), _BIT7);

    // Set TOR: time-out = TOR x 2 x ((FD10+1)/input clk)
    ScalerSetByte(P7F_81_I2CM_CR1, _TYPE_C_1_HW_IIC_TOR);

    // Disable burst mode
    ScalerSetByte(P7F_82_I2CM_CR2, 0x00);

    // Clear interrupts
    ScalerSetByte(P7F_83_I2CM_CR3, 0x00);

    // Set I2C Master Debounce
    ScalerSetBit(P7F_84_I2CM_STR0, ~(_BIT6 | _BIT5 | _BIT4), 0x00);

    // Set fall time period count (FTPC)
    ScalerSetByte(P7F_8E_I2CM_STR4, _TYPE_C_1_HW_IIC_FTPC);

    // Set STA setup time period count
    ScalerSetByte(P7F_85_I2CM_STR1, _TYPE_C_1_HW_IIC_STA_SUGPIO_C);

    // Set SCL high period count
    ScalerSetByte(P7F_86_I2CM_STR2, _TYPE_C_1_HW_IIC_SHPC_28000K);

    // Set SCL low period count
    ScalerSetByte(P7F_87_I2CM_STR3, _TYPE_C_1_HW_IIC_SLPC_28000K);

    // Set frequency divisor: ref = xtal/(FD10+1)
    ScalerSetByte(P7F_8A_I2CM_CCR, _TYPE_C_1_HW_IIC_FD10_28000K);

    // Set I2C Master Repeated_Start
    ScalerSetByte(P7F_8F_I2CM_STR5, 0x38);

    // Clear Pmic related control flag
    CLR_TYPE_C_1_PMIC_IIC_SET_START();
}

//--------------------------------------------------
// Description  : TypeC Hardware IIC Clock Select
// Input Value  : Clock --> _EXT_XTAL_CLK/_IOSC_CLK
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PmicHwIICSetFreqDiv(EnumClkSel enumClock)
{
    if(enumClock == _EXT_XTAL_CLK)
    {
#if(_EXT_XTAL == _XTAL14318K)

        // Set freq. divisor: ref = XTAL/(FD10+1) = 7.16M(ref should be approx 10MHz)
        ScalerSetByte(P7F_8A_I2CM_CCR, _TYPE_C_1_HW_IIC_FD10_14318K);

        // Set STA setup time period count
        ScalerSetByte(P7F_85_I2CM_STR1, _TYPE_C_1_HW_IIC_STA_SUGPIO_C);

        // Set SCL high period count
        ScalerSetByte(P7F_86_I2CM_STR2, _TYPE_C_1_HW_IIC_SHPC_14318K);

        // Set SCL low period count
        ScalerSetByte(P7F_87_I2CM_STR3, _TYPE_C_1_HW_IIC_SLPC_14318K);

#elif(_EXT_XTAL == _XTAL27000K)

        // Set freq. divisor: ref = XTAL/(FD10+1) = 9M(ref should be approx 10MHz)
        ScalerSetByte(P7F_8A_I2CM_CCR, _TYPE_C_1_HW_IIC_FD10_27000K);

        // Set STA setup time period count
        ScalerSetByte(P7F_85_I2CM_STR1, _TYPE_C_1_HW_IIC_STA_SUGPIO_C);

        // Set SCL high period count
        ScalerSetByte(P7F_86_I2CM_STR2, _TYPE_C_1_HW_IIC_SHPC_27000K);

        // Set SCL low period count
        ScalerSetByte(P7F_87_I2CM_STR3, _TYPE_C_1_HW_IIC_SLPC_27000K);

#endif
    }
    else
    {
        // Set freq. divisor: ref = IOSC/(FD10+1) = 9.3M(ref should be approx 10MHz)
        ScalerSetByte(P7F_8A_I2CM_CCR, _TYPE_C_1_HW_IIC_FD10_28000K);

        // Set STA setup time period count
        ScalerSetByte(P7F_85_I2CM_STR1, _TYPE_C_1_HW_IIC_STA_SUGPIO_C);

        // Set SCL high period count
        ScalerSetByte(P7F_86_I2CM_STR2, _TYPE_C_1_HW_IIC_SHPC_28000K);

        // Set SCL low period count
        ScalerSetByte(P7F_87_I2CM_STR3, _TYPE_C_1_HW_IIC_SLPC_28000K);
    }
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
bit ScalerTypeC1PmicHwIICRead(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, BYTE ucDataLength, BYTE *pucReadArray)
{
    BYTE ucI = 0;

    // Return fail if Data to be received is greater than IIC buffer size
    if(ucDataLength > _TYPE_C_1_HW_IIC_BUFFER_SIZE)
    {
        return _FAIL;
    }

    // Check if set start before
    if(ScalerTypeC1PmicHwIICSetStartCheck() == _FAIL)
    {
        CLR_TYPE_C_1_PMIC_IIC_IN_MAIN_LOOP();

        return _FAIL;
    }

    // Reset(Block) IIC module
    ScalerSetBit(P7F_80_I2CM_CR0, ~_BIT7, 0x00);

    // Enable IIC module
    ScalerSetBit(P7F_80_I2CM_CR0, ~_BIT7, _BIT7);

    // Wait I2C Fifo Clk Switch to Mcu Clk
    if(ScalerTimerPollingFlagProc(2, P7F_88_I2CM_SR, _BIT5, _TRUE) == _FALSE)
    {
        // Reset(Block) IIC module
        ScalerSetBit(P7F_80_I2CM_CR0, ~_BIT7, 0x00);

        // Enable IIC module
        ScalerSetBit(P7F_80_I2CM_CR0, ~_BIT7, _BIT7);

        CLR_TYPE_C_1_PMIC_IIC_IN_MAIN_LOOP();

        return _FAIL;
    }

    // Load Slave Address to IIC Buffer
    switch(ucSubAddrLength)
    {
        case 0:

            // Set 1 byte for FRSIB
            ScalerSetBit(P7F_82_I2CM_CR2, ~(_BIT1 | _BIT0), 0x00);

            // Set no repeat start
            ScalerSetBit(P7F_83_I2CM_CR3, ~(_BIT4 | _BIT3), 0x00);

            // Load Slave Address to receive data
            ScalerSetByte(P7F_89_I2CM_TD, (ucSlaveAddr | _READ));

            break;

        case 1:

            // Set 2 bytes for FRSIB
            ScalerSetBit(P7F_82_I2CM_CR2, ~(_BIT1 | _BIT0), _BIT0);

            // Set one repeat start
            ScalerSetBit(P7F_83_I2CM_CR3, ~(_BIT4 | _BIT3), _BIT3);

            // Load Slave Address to IIC Buffer
            ScalerSetByte(P7F_89_I2CM_TD, (ucSlaveAddr | _WRITE));

            // Load Sub-Address to IIC Buffer
            ScalerSetByte(P7F_89_I2CM_TD, (BYTE)(usSubAddr));

            // Load Slave Address to receive data
            ScalerSetByte(P7F_89_I2CM_TD, (ucSlaveAddr | _READ));

            break;

        case 2:

            // Set 3 bytes for FRSIB
            ScalerSetBit(P7F_82_I2CM_CR2, ~(_BIT1 | _BIT0), _BIT1);

            // Set one repeat start
            ScalerSetBit(P7F_83_I2CM_CR3, ~(_BIT4 | _BIT3), _BIT3);

            // Load Slave Address to IIC Buffer
            ScalerSetByte(P7F_89_I2CM_TD, (ucSlaveAddr | _WRITE));

            // Load First Sub-Address to IIC Buffer
            ScalerSetByte(P7F_89_I2CM_TD, (BYTE)((usSubAddr & 0xFF00) >> 8));

            // Load Second Sub-Address to IIC Buffer
            ScalerSetByte(P7F_89_I2CM_TD, (BYTE)(usSubAddr));

            // Load Slave Address to receive data
            ScalerSetByte(P7F_89_I2CM_TD, (ucSlaveAddr | _READ));

            break;

        default:

            break;
    }

    // Set data length
    ScalerSetBit(P7F_80_I2CM_CR0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), ((ucDataLength - 1) << 1));

    // If int happened while this I2C setting, then return.
    if((GET_TYPE_C_1_PMIC_IIC_EVER_IN_EXINT0_LOOP() == _TRUE) || (GET_TYPE_C_1_PMIC_IIC_EVER_IN_WDINT_LOOP() == _TRUE))
    {
        // Reset(Block) IIC module
        ScalerSetBit(P7F_80_I2CM_CR0, ~_BIT7, 0x00);

        // Enable IIC module
        ScalerSetBit(P7F_80_I2CM_CR0, ~_BIT7, _BIT7);

        CLR_TYPE_C_1_PMIC_IIC_IN_MAIN_LOOP();

        return _FAIL;
    }

    // IIC command Start
    ScalerSetBit(P7F_80_I2CM_CR0, ~_BIT6, _BIT6);

    // Set Pmic I2C set start flag
    SET_TYPE_C_1_PMIC_IIC_SET_START();

    // Wait until Master Receive Complete
    if(ScalerTimerPollingFlagProc(4, P7F_88_I2CM_SR, _BIT1, _TRUE) == _FALSE)
    {
        // Reset(Block) IIC module
        ScalerSetBit(P7F_80_I2CM_CR0, ~_BIT7, 0x00);

        // Enable IIC module
        ScalerSetBit(P7F_80_I2CM_CR0, ~_BIT7, _BIT7);

        CLR_TYPE_C_1_PMIC_IIC_IN_MAIN_LOOP();

        return _FAIL;
    }

    // Wait I2C Fifo Clk Switch to Mcu Clk
    if(ScalerTimerPollingFlagProc(2, P7F_88_I2CM_SR, _BIT5, _TRUE) == _FALSE)
    {
        // Reset(Block) IIC module
        ScalerSetBit(P7F_80_I2CM_CR0, ~_BIT7, 0x00);

        // Enable IIC module
        ScalerSetBit(P7F_80_I2CM_CR0, ~_BIT7, _BIT7);

        CLR_TYPE_C_1_PMIC_IIC_IN_MAIN_LOOP();

        return _FAIL;
    }

    // Save received data
    for(ucI = 0; ucI < ucDataLength; ucI++)
    {
        *pucReadArray = ScalerGetByte(P7F_89_I2CM_TD);
        pucReadArray++;
    }

    // Clear all flags
    ScalerSetByte(P7F_88_I2CM_SR, (_BIT2 | _BIT1 | _BIT0));

    // Clear Pmic I2C set start flag
    CLR_TYPE_C_1_PMIC_IIC_SET_START();

    // If int happened while this I2C setting, then return.
    if((GET_TYPE_C_1_PMIC_IIC_EVER_IN_EXINT0_LOOP() == _TRUE) || (GET_TYPE_C_1_PMIC_IIC_EVER_IN_WDINT_LOOP() == _TRUE))
    {
        // Reset(Block) IIC module
        ScalerSetBit(P7F_80_I2CM_CR0, ~_BIT7, 0x00);

        // Enable IIC module
        ScalerSetBit(P7F_80_I2CM_CR0, ~_BIT7, _BIT7);

        CLR_TYPE_C_1_PMIC_IIC_IN_MAIN_LOOP();

        return _FAIL;
    }

    CLR_TYPE_C_1_PMIC_IIC_IN_MAIN_LOOP();

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : Write data to the selected device by TypeC IIC
// Input Value  : ucSlaveAddr      --> Slave address
//                ucSubAddrLength  --> Start address length of selected device
//                usSubAddr        --> Start address of selected device
//                ucDataLength     --> Numbers of data we want to write
//                pucWriteArray    --> Result array
// Output Value : Write result (Fail/Success)
//--------------------------------------------------
bit ScalerTypeC1PmicHwIICWrite(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, BYTE ucDataLength, BYTE *pucWriteArray)
{
    BYTE ucI = 0;
    BYTE ucTempLength = 0;

    // Return fail if Data to be transmitted is greater than IIC buffer size
    if((ucDataLength + ucSubAddrLength) > _TYPE_C_1_HW_IIC_WRITE_SIZE)
    {
        return _FAIL;
    }

    // Check if set start before
    if(ScalerTypeC1PmicHwIICSetStartCheck() == _FAIL)
    {
        CLR_TYPE_C_1_PMIC_IIC_IN_MAIN_LOOP();

        return _FAIL;
    }

    // Reset(Block) IIC module
    ScalerSetBit(P7F_80_I2CM_CR0, ~_BIT7, 0x00);

    // Enable IIC module
    ScalerSetBit(P7F_80_I2CM_CR0, ~_BIT7, _BIT7);

    // Set 1 byte for FRSIB
    ScalerSetBit(P7F_82_I2CM_CR2, ~(_BIT1 | _BIT0), 0x00);

    // Set no repeat start
    ScalerSetBit(P7F_83_I2CM_CR3, ~(_BIT4 | _BIT3), 0x00);

    // Wait I2C Fifo Clk Switch to Mcu Clk
    if(ScalerTimerPollingFlagProc(2, P7F_88_I2CM_SR, _BIT5, _TRUE) == _FALSE)
    {
        // Reset(Block) IIC module
        ScalerSetBit(P7F_80_I2CM_CR0, ~_BIT7, 0x00);

        // Enable IIC module
        ScalerSetBit(P7F_80_I2CM_CR0, ~_BIT7, _BIT7);

        CLR_TYPE_C_1_PMIC_IIC_IN_MAIN_LOOP();

        return _FAIL;
    }

    // Load Slave Address to IIC Buffer
    ScalerSetByte(P7F_89_I2CM_TD, (ucSlaveAddr | _WRITE));

    ScalerSetBit(P7F_80_I2CM_CR0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), 0x00);

    pData[0] = ucDataLength;

    switch(ucSubAddrLength)
    {
        case 0:

            // Set data length
            ucTempLength = ((pData[0] - 1) << 1);

            break;

        case 1:

            // Load Sub-Address to IIC Buffer
            ScalerSetByte(P7F_89_I2CM_TD, (BYTE)(usSubAddr));

            // Set data length
            ucTempLength = (pData[0] << 1);

            break;

        case 2:

            // Load First Sub-Address to IIC Buffer
            ScalerSetByte(P7F_89_I2CM_TD, (BYTE)((usSubAddr & 0xFF00) >> 8));

            // Load Second Sub-Address to IIC Buffer
            ScalerSetByte(P7F_89_I2CM_TD, (BYTE)(usSubAddr));

            // Set data length
            ucTempLength = ((pData[0] + 1) << 1);

            break;

        default:

            break;
    }

    // Load data to IIC buffer for transmission
    for(ucI = 0; ucI < pData[0]; ucI++)
    {
        ScalerSetByte(P7F_89_I2CM_TD, pucWriteArray[ucI]);
    }

    // If int happened while this I2C setting, then return.
    if((GET_TYPE_C_1_PMIC_IIC_EVER_IN_EXINT0_LOOP() == _TRUE) || (GET_TYPE_C_1_PMIC_IIC_EVER_IN_WDINT_LOOP() == _TRUE))
    {
        // Reset(Block) IIC module
        ScalerSetBit(P7F_80_I2CM_CR0, ~_BIT7, 0x00);

        // Enable IIC module
        ScalerSetBit(P7F_80_I2CM_CR0, ~_BIT7, _BIT7);

        CLR_TYPE_C_1_PMIC_IIC_IN_MAIN_LOOP();

        return _FAIL;
    }

    // Send IIC command Start
    ScalerSetByte(P7F_80_I2CM_CR0, (0xC0 + ucTempLength));

    // Set Pmic I2C set start flag
    SET_TYPE_C_1_PMIC_IIC_SET_START();

    CLR_TYPE_C_1_PMIC_IIC_IN_MAIN_LOOP();

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : Set FRS data to the selected device by TypeC IIC
// Input Value  : ucSlaveAddr      --> Slave address
//                ucSubAddrLength  --> Start address length of selected device
//                usSubAddr        --> Start address of selected device
//                ucDataLength     --> Numbers of data we want to write
//                pucWriteArray    --> Result array
// Output Value : Write result (Fail/Success)
//--------------------------------------------------
bit ScalerTypeC1PmicHwIICSetFrsData(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, BYTE ucDataLength, BYTE *pucWriteArray)
{
    BYTE ucI = 0;
    BYTE ucTempLength = 0;

    // Return fail if Data to be transmitted is greater than IIC buffer size
    if((ucDataLength + ucSubAddrLength) > _TYPE_C_1_HW_IIC_WRITE_SIZE)
    {
        return _FAIL;
    }

    // Disable INT & Clear all flags
    ScalerSetBit(P7F_8B_I2CM_FRS_SR, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1));

    // Reset(Block) IIC module
    ScalerSetBit(P7F_80_I2CM_CR0, ~_BIT7, 0x00);

    // Enable IIC module
    ScalerSetBit(P7F_80_I2CM_CR0, ~_BIT7, _BIT7);

    // Set 1 byte for FRSIB
    ScalerSetBit(P7F_82_I2CM_CR2, ~(_BIT1 | _BIT0), 0x00);

    // Set no repeat start
    ScalerSetBit(P7F_83_I2CM_CR3, ~(_BIT4 | _BIT3), 0x00);

    // Wait I2C Fifo Clk Switch to Mcu Clk
    if(ScalerTimerPollingFlagProc(2, P7F_8B_I2CM_FRS_SR, _BIT5, _TRUE) == _FALSE)
    {
        // Reset(Block) IIC module
        ScalerSetBit(P7F_80_I2CM_CR0, ~_BIT7, 0x00);

        // Enable IIC module
        ScalerSetBit(P7F_80_I2CM_CR0, ~_BIT7, _BIT7);

        return _FAIL;
    }

    // Load Slave Address to IIC Buffer
    ScalerSetByte(P7F_8C_I2CM_FRS_TD, (ucSlaveAddr | _WRITE));

    ScalerSetBit(P7F_8D_I2CM_FRS_WL, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    pData[0] = ucDataLength;

    switch(ucSubAddrLength)
    {
        case 0:

            // Set data length
            ucTempLength = pData[0] - 1;

            break;

        case 1:

            // Load Sub-Address to IIC Buffer
            ScalerSetByte(P7F_8C_I2CM_FRS_TD, (BYTE)(usSubAddr));

            // Set data length
            ucTempLength = pData[0];

            break;

        case 2:

            // Load First Sub-Address to IIC Buffer
            ScalerSetByte(P7F_8C_I2CM_FRS_TD, (BYTE)((usSubAddr & 0xFF00) >> 8));

            // Load Second Sub-Address to IIC Buffer
            ScalerSetByte(P7F_8C_I2CM_FRS_TD, (BYTE)(usSubAddr));

            // Set data length
            ucTempLength = pData[0] + 1;

            break;

        default:

            break;
    }

    // Load data to IIC buffer for transmission
    for(ucI = 0; ucI < pData[0]; ucI++)
    {
        ScalerSetByte(P7F_8C_I2CM_FRS_TD, pucWriteArray[ucI]);
    }

    // Set data length
    ScalerSetByte(P7F_8D_I2CM_FRS_WL, ucTempLength);

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : TypeC Hardware IIC Check if Set Start
// Input Value  : None
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
bit ScalerTypeC1PmicHwIICSetStartCheck(void)
{
    SET_TYPE_C_1_PMIC_IIC_IN_MAIN_LOOP();

    CLR_TYPE_C_1_PMIC_IIC_EVER_IN_EXINT0_LOOP();

    CLR_TYPE_C_1_PMIC_IIC_EVER_IN_WDINT_LOOP();

    if(GET_TYPE_C_1_PMIC_IIC_SET_START() == _TRUE)
    {
        // Wait until Master Transmit Complete
        if(ScalerTimerPollingFlagProc(4, P7F_88_I2CM_SR, _BIT0, _TRUE) == _FALSE)
        {
            // Reset(Block) IIC module
            ScalerSetBit(P7F_80_I2CM_CR0, ~_BIT7, 0x00);

            // Enable IIC module
            ScalerSetBit(P7F_80_I2CM_CR0, ~_BIT7, _BIT7);

            // Clear Pmic I2C set start flag
            CLR_TYPE_C_1_PMIC_IIC_SET_START();

            return _FAIL;
        }

        // Clear all flags
        ScalerSetByte(P7F_88_I2CM_SR, (_BIT2 | _BIT1 | _BIT0));

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
bit ScalerTypeC1PmicIICRead(BYTE ucSlaveAddr, WORD usSubAddr, BYTE ucSubAddrLength, WORD usLength, BYTE *pucReadArray)
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
        if(ScalerTypeC1PmicHwIICRead(ucSlaveAddress, ucSubAddrLength, usSubAddr, ucDataCnt, pucReadArray) == _FAIL)
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
bit ScalerTypeC1PmicIICWrite(BYTE ucSlaveAddr, WORD usSubAddr, BYTE ucSubAddrLength, WORD usLength, BYTE *pucWriteArray)
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
        memcpy(pucTempData, pucWriteArray, ucDataCnt);

        // Increase data location
        pucWriteArray += ucDataCnt;

        // Execute Hardware IIC Write Command
        if(ScalerTypeC1PmicHwIICWrite(ucSlaveAddress, ucSubAddrLength, usSubAddr, ucDataCnt, pucTempData) == _FAIL)
        {
            return _FAIL;
        }

        // Increment Sub-Addr for next Write
        usSubAddr += ucDataCnt;
    }

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : Set FRS data to the selected device by TypeC IIC
// Input Value  : ucSlaveAddr      --> Slave address
//                ucSubAddrLength  --> Start address length of selected device
//                usSubAddr        --> Start address of selected device
//                usLength         --> Numbers of data we want to write
//                pucWriteArray    --> Result array
// Output Value : Write result (Fail/Success)
//--------------------------------------------------
bit ScalerTypeC1PmicIICSetFrsData(BYTE ucSlaveAddr, WORD usSubAddr, BYTE ucSubAddrLength, WORD usLength, BYTE *pucWriteArray)
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
        memcpy(pucTempData, pucWriteArray, ucDataCnt);

        // Increase data location
        pucWriteArray += ucDataCnt;

        // Execute Hardware IIC Write Command
        if(ScalerTypeC1PmicHwIICSetFrsData(ucSlaveAddress, ucSubAddrLength, usSubAddr, ucDataCnt, pucTempData) == _FAIL)
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
void ScalerTypeC1PmicIICReset(void)
{
    CLR_TYPE_C_1_PMIC_IIC_IN_MAIN_LOOP();
    CLR_TYPE_C_1_PMIC_IIC_IN_EXINT0_LOOP();
    CLR_TYPE_C_1_PMIC_IIC_IN_WDINT_LOOP();
    CLR_TYPE_C_1_PMIC_IIC_EVER_IN_EXINT0_LOOP();
    CLR_TYPE_C_1_PMIC_IIC_EVER_IN_WDINT_LOOP();

    if(GET_TYPE_C_1_PMIC_IIC_SET_START() == _TRUE)
    {
        // Wait until Master Transmit Complete
        if(ScalerTimerPollingFlagProc(4, P7F_88_I2CM_SR, _BIT0, _TRUE) == _FALSE)
        {
            // Reset(Block) IIC module
            ScalerSetBit(P7F_80_I2CM_CR0, ~_BIT7, 0x00);

            // Enable IIC module
            ScalerSetBit(P7F_80_I2CM_CR0, ~_BIT7, _BIT7);

            // Clear Pmic I2C set start flag
            CLR_TYPE_C_1_PMIC_IIC_SET_START();

            return;
        }

        // Clear all flags
        ScalerSetByte(P7F_88_I2CM_SR, (_BIT2 | _BIT1 | _BIT0));

        // Clear Pmic I2C set start flag
        CLR_TYPE_C_1_PMIC_IIC_SET_START();
    }
}
#endif // End of #if(_EMB_TYPE_C_1_PMIC_IIC != _PMIC_NO_IIC_PIN)

//--------------------------------------------------
// Description  : Type-C 1 PMIC Initial Settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PmicInitial(void)
{
    EnumTypeCPcbPort enumTypeCPcbPort = ScalerTypeCxPcbxMapping(_EMB_TYPE_C_1);

    // ========================================================
    // Initial HW Setting
    // ========================================================
#if(_EMB_TYPE_C_1_PMIC_IIC != _PMIC_NO_IIC_PIN)
    ScalerTypeC1PmicHwIICInitial();
#endif

    ScalerTypeC1PmicSetting(_OFF, _PD_POWER_SRC, _PD_NONE_SETTING_PDO, 0, 0, _PD_PEAK_CUR_NONE);

    ExternalDeviceInterfaceTypeCPmicACOnInitial(enumTypeCPcbPort);

#if(_PORT_CTRL_EMB_UNATTACH_HW_FORCE_VBUS_OFF == _ON)
    ExternalDeviceInterfaceTypeCPmicForceOffConfig(enumTypeCPcbPort);
#endif

    // ========================================================
    // Initial Flag and Initial Value
    // ========================================================

#if((_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) || (_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_10_BIT_ADC))
    // Set Vbus Short Voltage
    SET_TYPE_C_1_PMIC_SHORT_VOLTAGE((WORD)(((DWORD)_TYPE_C_1_PMIC_SHORT_VOLTAGE * 1024) / _EMB_TYPE_C_1_PMIC_VBUS_MAX_VOLTAGE));
#endif // End of #if((_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) || (_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_10_BIT_ADC))

    // ========================================================
    // Debug Function
    // ========================================================
#if(_TYPE_C_1_PMIC_FORCE_OUTPUT == _ON)
    ScalerTypeC1PmicSetting(_ON, _PD_POWER_SRC, _PD_FIX_SUPPLY_PDO, _TYPE_C_1_PMIC_FORCE_VOLTAGE, _TYPE_C_1_PMIC_FORCE_CURRENT, _PD_PEAK_CUR_NONE);
    ScalerTimerDelayXms(3000);

#if(_EMB_TYPE_C_PMIC_DEBUG == _ON)
    if(ExternalDeviceInterfaceTypeCPmicDebugCheckStatus(enumTypeCPcbPort) == _TYPE_C_PMIC_CONTROL_FAIL)
    {
        DebugMessageTypeC("PMIC Check Fail!", 0x00);
    }
#endif

    ScalerTypeC1PmicSetting(_OFF, _PD_POWER_SRC, _PD_NONE_SETTING_PDO, 0, 0, _PD_PEAK_CUR_NONE);
#endif
}

//--------------------------------------------------
// Description  : Type-C 1 PMIC Reset Settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PmicReset(void)
{
    EnumTypeCPcbPort enumTypeCPcbPort = ScalerTypeCxPcbxMapping(_EMB_TYPE_C_1);

    // ========================================================
    // Reset HW Setting
    // ========================================================
#if(_EMB_TYPE_C_1_PMIC_IIC != _PMIC_NO_IIC_PIN)
    ScalerTypeC1PmicIICReset();
#endif

    ExternalDeviceInterfaceTypeCPmicUnattachReset(enumTypeCPcbPort);

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
// Description  : Type-C 1 PMIC Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PmicHandler(void)
{
#if(_EMB_TYPE_C_1_PMIC_CHECK_SUPPORT == _ON)
    // Check if Start PMIC Protection Tracking Timer
    if(GET_TYPE_C_1_PMIC_PROTECT_TIMER_START() == _TRUE)
    {
        CLR_TYPE_C_1_PMIC_PROTECT_TIMER_START();

        // Active PMIC Protection Tracking Timer
        ScalerTimerReactiveTimerEvent(40, _SCALER_TIMER_EVENT_TYPE_C_1_PMIC_TRACKING);
    }
#endif
}

//--------------------------------------------------
// Description  : Type-C 1 PMIC Timer Event Proc
// Input Value  : enumEventID
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PmicTimerEventProc(EnumScalerTimerEventID enumEventID)
{
    enumEventID = enumEventID;

    switch(enumEventID)
    {
#if(_EMB_TYPE_C_1_PMIC_CHECK_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_TYPE_C_1_PMIC_TRACKING:

            ScalerTypeC1PmicProtectTracking();

            break;

#if(((_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) || (_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_10_BIT_ADC)) &&\
    (_EMB_TYPE_C_1_PMIC_SAFETY_PROTECT_SUPPORT == _ON))
        case _SCALER_TIMER_EVENT_TYPE_C_1_PMIC_SAFETY_PROTECT:

            ScalerTypeC1PmicSafetyProtect();

            break;
#endif // End of #if(((_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) || (_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_10_BIT_ADC)) && (_EMB_TYPE_C_1_PMIC_SAFETY_PROTECT_SUPPORT == _ON))

#if(_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_POLLING_PMIC)
        case _SCALER_TIMER_EVENT_TYPE_C_1_PMIC_POLLING_OCP:

            ScalerTypeC1PmicPollingOcpProtect();

            break;
#endif // End of #if(_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_POLLING_PMIC)
#endif // End of #if(_EMB_TYPE_C_1_PMIC_CHECK_SUPPORT == _ON)

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Control Type-C 1 PMIC to Directed Voltage
// Input Value  : bAction : _ON / _OFF
//                bPowerDirection : _PD_POWER_SNK / _PD_POWER_SRC
//                usVoltage : 0 ~ 2100 (Unit = 10mV) / usCurrent : 0 ~ 500 (Unit = 10mA)
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
bit ScalerTypeC1PmicSetting(bit bAction, bit bPowerDirection, EnumTypeCPDPdoType enumPdoType, WORD usVoltage, WORD usCurrent, EnumTypeCPDPeakCurType enumPeakCurrent)
{
    EnumTypeCPcbPort enumTypeCPcbPort = ScalerTypeCxPcbxMapping(_EMB_TYPE_C_1);
    EnumTypeCPmicControlResult enumResult = _TYPE_C_PMIC_CONTROL_FAIL;
    EnumTypeCPmicDirection enumDirection = _TYPE_C_PMIC_DIRECTION_SNK;

#if(_TYPE_C_POWER_DEBUG == _ON)
    DebugMessageTypeC("    [PMIC] Setting Flow", bAction);
    DebugMessageTypeC("        ----> Request Voltage: ", usVoltage);
    DebugMessageTypeC("        ----> Request Current: ", usCurrent);
    DebugMessageTypeC("        ----> Request Power: ", (WORD)((DWORD)usVoltage * usCurrent / 1000));
#endif

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
        ScalerTypeCAdcInOutCompIntControl(_TYPE_C_CHANNEL_1_VMON, _DISABLE);
        CLR_TYPE_C_1_PMIC_FW_OVP_UVP_CHECK();

        // Set OVP/UVP range
        ScalerTypeCAdcInOutCompIntSetting(_TYPE_C_CHANNEL_1_VMON, usOVPThreshold, usUVPThreshold, _TYPE_C_ADC_WITHOUT_RANGE);
    }
    else
    {
        // Disable INT
        ScalerTypeCAdcInOutCompIntControl(_TYPE_C_CHANNEL_1_VMON, _DISABLE);
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
        ScalerTypeCAdcInOutCompIntControl(_TYPE_C_1_IMON, _DISABLE);

        // Set Range to check if Vbus current will be triggered OCP Current.
        // Do not enable INT immediately for avoiding inrush current.
        ScalerTypeCAdcInOutCompIntSetting(_TYPE_C_1_IMON, 0xFFFF, GET_TYPE_C_1_PMIC_FW_OCP_CURRENT(0), _TYPE_C_ADC_WITHIN_RANGE);

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
        ScalerTypeCAdcInOutCompIntControl(_TYPE_C_1_IMON, _DISABLE);
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
        ScalerTypeC1PmicSwitchControl(_ON, bPowerDirection);

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
            if(ExternalDeviceInterfaceTypeCPmicPpsOutputModeSetting(enumTypeCPcbPort, enumDirection, enumPdoType) == _TYPE_C_PMIC_CONTROL_FAIL)
            {
                return _FAIL;
            }
#endif
            SET_TYPE_C_1_PMIC_OUTPUT_MODE_STATUS(enumPdoType);
        }

        enumResult = ExternalDeviceInterfaceTypeCPmicVoltageCurrentSetting(enumTypeCPcbPort, enumDirection, usVoltage, usCurrent);

#if(_TYPE_C_POWER_DEBUG == _ON)
        DebugMessageTypeC("    [PMIC] Vbus Power On", bAction);
#endif
    }
    else
    {
        // Reset PMIC Output Type
        SET_TYPE_C_1_PMIC_OUTPUT_MODE_STATUS(enumPdoType);

        enumResult = ExternalDeviceInterfaceTypeCPmicTurnOff(enumTypeCPcbPort);

#if(_TYPE_C_POWER_DEBUG == _ON)
        DebugMessageTypeC("    [PMIC] Vbus Power Off", bAction);
#endif
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

#if(_TYPE_C_POWER_DEBUG == _ON)
        DebugMessageTypeC("        ----> Setting Voltage: ", GET_TYPE_C_1_OUTPUT_VOL());
        DebugMessageTypeC("        ----> Setting Current: ", GET_TYPE_C_1_OUTPUT_CUR());
        DebugMessageTypeC("        ----> Setting Power: ", GET_TYPE_C_1_REQ_PWR());
#endif

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
bit ScalerTypeC1PmicVbusDischarge(bit bEn)
{
    EnumTypeCPmicDischarge enumDischarge = _TYPE_C_PMIC_DISCHARGE_DISABLE;

    if(bEn == _ON)
    {
        enumDischarge = _TYPE_C_PMIC_DISCHARGE_ENABLE;
    }
    else
    {
        ScalerTypeC1PmicSwitchControl(_OFF, _PD_POWER_SNK);
        enumDischarge = _TYPE_C_PMIC_DISCHARGE_DISABLE;
    }

    if(ExternalDeviceInterfaceTypeCPmicVbusDischarge(ScalerTypeCxPcbxMapping(_EMB_TYPE_C_1), enumDischarge) == _TYPE_C_PMIC_CONTROL_SUCCESS)
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
bit ScalerTypeC1PmicSwitchControl(bit bEn, bit bPowerDirection)
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


    if(ExternalDeviceInterfaceTypeCPmicSwitchControl(ScalerTypeCxPcbxMapping(_EMB_TYPE_C_1), enumSwitchControl, enumDirection) == _TYPE_C_PMIC_CONTROL_SUCCESS)
    {
        return _SUCCESS;
    }
    else
    {
        return _FAIL;
    }
}

//--------------------------------------------------
// Description  : Type-C 1 PMIC Set Vbus Protect Info
// Input Value  : StructTypeCVbusProtectInfo
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PmicSetVbusProtectInfo(StructTypeCVbusProtectInfo stTypeCVbusProtectInfo)
{
    // Set Vbus Debounce Time for Protection Judgment before protection trigger
    SET_TYPE_C_1_PMIC_OVP_JUDGE_DEBOUNCE(stTypeCVbusProtectInfo.ucOvpDebounce);
    SET_TYPE_C_1_PMIC_UVP_JUDGE_DEBOUNCE(stTypeCVbusProtectInfo.ucUvpDebounce);
    SET_TYPE_C_1_PMIC_OCP_JUDGE_DEBOUNCE(stTypeCVbusProtectInfo.ucOcpDebounce);

#if((_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) || (_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_10_BIT_ADC))
    // Set Vbus OCP Calculation Include Peak Current or not
    SET_TYPE_C_1_PMIC_PEAK_CURRENT_PROTECT(stTypeCVbusProtectInfo.enumPeakCurrentProtect);
#endif
}

#if(_EMB_TYPE_C_1_PMIC_CHECK_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Type-C 1 PMIC Protection Start
// Input Value  : enumPowerRole : _TYPE_C_POWER_SRC / _TYPE_C_POWER_SNK
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PmicProtectStart(EnumTypeCPowerRole enumPowerRole)
{
    if(enumPowerRole == _TYPE_C_POWER_SRC)
    {
        // Enable PMIC Protection Int
#if(_EMB_TYPE_C_1_PMIC_FW_OVP_UVP_SUPPORT == _ON)
        // Enable OVP/UVP Int
        ScalerTypeCAdcInOutCompIntControl(_TYPE_C_CHANNEL_1_VMON, _ENABLE);
        SET_TYPE_C_1_PMIC_FW_OVP_UVP_CHECK();
#endif

#if((_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) || (_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_10_BIT_ADC))
        // Enable OCP Int
        ScalerTypeCAdcInOutCompIntControl(_TYPE_C_1_IMON, _ENABLE);
#endif
    }
    else
    {
        // Enable PMIC Protection Int
#if(_EMB_TYPE_C_1_PMIC_FW_OVP_UVP_SUPPORT == _ON)
        // Enable OVP/UVP Int
        ScalerTypeCAdcInOutCompIntControl(_TYPE_C_CHANNEL_1_VMON, _ENABLE);
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

//--------------------------------------------------
// Description  : Type-C 1 PMIC Protection Tracking
// Input Value  : None
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
bit ScalerTypeC1PmicProtectTracking(void)
{
    EnumTypeCPcbPort enumTypeCPcbPort = ScalerTypeCxPcbxMapping(_EMB_TYPE_C_1);
    BYTE ucTimerEventDelay = 0xFF; // 0xFF: Control_Fail, 0xFE: Cancel_Timer
    BYTE ucSafetyProtectDelay = 0xFF;
    BYTE ucPollingOcpDelay = 0xFF;
    BYTE ucVoltageCompensationDelay = 0xFF;
    BYTE ucIntPinDelay = 0xFF;

    // Avoid warning
    enumTypeCPcbPort = enumTypeCPcbPort;
    ucSafetyProtectDelay = ucSafetyProtectDelay;
    ucPollingOcpDelay = ucPollingOcpDelay;
    ucVoltageCompensationDelay = ucVoltageCompensationDelay;
    ucIntPinDelay = ucIntPinDelay;

    // Check if PMIC Protection Valid
    if(GET_TYPE_C_1_PMIC_PROTECT_VALID() == _TRUE)
    {
#if((_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) || (_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_10_BIT_ADC))
#if(_EMB_TYPE_C_1_PMIC_SAFETY_PROTECT_SUPPORT == _ON)
        ucSafetyProtectDelay = ScalerTypeC1PmicTrackingSafetyProtect();
        ucTimerEventDelay = MINOF(ucTimerEventDelay, ucSafetyProtectDelay);
#endif
#elif(_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_POLLING_PMIC)
        ucPollingOcpDelay = ScalerTypeC1PmicTrackingPollingOcp(enumTypeCPcbPort);
        ucTimerEventDelay = MINOF(ucTimerEventDelay, ucPollingOcpDelay);
#endif

#if(_EMB_TYPE_C_1_PMIC_VOLTAGE_COMPENSATION == _ON)
        ucVoltageCompensationDelay = ScalerTypeC1PmicTrackingVoltageCompensation(enumTypeCPcbPort);
        ucTimerEventDelay = MINOF(ucTimerEventDelay, ucVoltageCompensationDelay);
#endif

#if(_EMB_TYPE_C_1_PMIC_INT_PIN_CHECK_METHOD == _TYPE_C_PMIC_INT_PIN_CHECK_BY_POLLING)
        ucIntPinDelay = ScalerTypeC1PmicTrackingIntPin(enumTypeCPcbPort);
        ucTimerEventDelay = MINOF(ucTimerEventDelay, ucIntPinDelay);
#endif

#if(_EMB_TYPE_C_PMIC_DEBUG == _ON)
        ExternalDeviceInterfaceTypeCPmicDebugCheckStatus(enumTypeCPcbPort);

        ucTimerEventDelay = MINOF(ucTimerEventDelay, 200);
#endif
    }

    // Check if Control Fail
    if(ucTimerEventDelay == 0xFF)
    {
        return _FAIL;
    }

    // Reactive PMIC Protection Tracking Timer Event
    if(ucTimerEventDelay < 0xFE)
    {
        ScalerTimerReactiveTimerEvent(ucTimerEventDelay, _SCALER_TIMER_EVENT_TYPE_C_1_PMIC_TRACKING);
    }

    return _SUCCESS;
}

#if((_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) || (_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_10_BIT_ADC))

#if(_EMB_TYPE_C_1_PMIC_SAFETY_PROTECT_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Type-C 1 PMIC Safety Protect Check
// Input Value  : enumTypeCPcbPort
// Output Value : Delay_Time(Unit: ms): 10 ~ 253
//--------------------------------------------------
BYTE ScalerTypeC1PmicTrackingSafetyProtect(void)
{
    if(GET_TYPE_C_1_PMIC_SAFETY_PROTECT_TRIGGER() == _FALSE)
    {
        WORD usCurrentValue = 0x0000;
        WORD usOcpDelay = 0x0000;

        DebugMessageTypeC("Pmic Safety Protect Tracking", 0x00);

        // Translate Current of 10-Bit_ADC to 10mA/bit
        usCurrentValue = ((WORD)((((DWORD)ScalerTypeCAdcCorrectionToIdealData(_TYPE_C_1_IMON, ScalerTypeCAdcGetAdcOutput(_TYPE_C_1_IMON))) * _EMB_TYPE_C_1_PMIC_IOUT_MAX_CURRENT) / 1024));

        // Debounce when current > OCP threshold
        if(usCurrentValue >= GET_TYPE_C_1_PMIC_SAFETY_CURRENT_VALUE())
        {
            ScalerTimerDelayXms(2);

            // Read again after ADC stable
            usCurrentValue = ((WORD)((((DWORD)ScalerTypeCAdcCorrectionToIdealData(_TYPE_C_1_IMON, ScalerTypeCAdcGetAdcOutput(_TYPE_C_1_IMON))) * _EMB_TYPE_C_1_PMIC_IOUT_MAX_CURRENT) / 1024));
        }

        // OCP judgment
        if(usCurrentValue >= GET_TYPE_C_1_PMIC_SAFETY_CURRENT_VALUE())
        {
            // Start Protection Delay
            usOcpDelay = MAXOF(_EMB_TYPE_C_1_PMIC_SAFETY_DELAY_SHUTDOWN, 10);
            ScalerTimerReactiveTimerEvent(usOcpDelay, _SCALER_TIMER_EVENT_TYPE_C_1_PMIC_SAFETY_PROTECT);

            DebugMessageTypeC("Pmic: Safety Protect Trigger", 0x00);

            SET_TYPE_C_1_PMIC_SAFETY_PROTECT_TRIGGER();

            // Already in Safety Protect State
            return 0xFE;
        }

        // Set 10ms Timer Event for Safety Protect
        return 10;
    }

    // Already in Safety Protect State
    return 0xFE;
}

//--------------------------------------------------
// Description  : Type-C 1 PMIC Safety Protect
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PmicSafetyProtect(void)
{
    WORD usCurrentValue = 0x0000;

    if(GET_TYPE_C_1_PMIC_SAFETY_PROTECT_TRIGGER() == _TRUE)
    {
        // Translate Current of 10-Bit_ADC to 10mA/bit
        usCurrentValue = ((WORD)((((DWORD)ScalerTypeCAdcCorrectionToIdealData(_TYPE_C_1_IMON, ScalerTypeCAdcGetAdcOutput(_TYPE_C_1_IMON))) * _EMB_TYPE_C_1_PMIC_IOUT_MAX_CURRENT) / 1024));

        // Debounce when current > OCP threshold
        if(usCurrentValue >= GET_TYPE_C_1_PMIC_SAFETY_CURRENT_VALUE())
        {
            ScalerTimerDelayXms(2);

            // Read again after ADC stable
            usCurrentValue = ((WORD)((((DWORD)ScalerTypeCAdcCorrectionToIdealData(_TYPE_C_1_IMON, ScalerTypeCAdcGetAdcOutput(_TYPE_C_1_IMON))) * _EMB_TYPE_C_1_PMIC_IOUT_MAX_CURRENT) / 1024));
        }

        // OCP judgment
        if(usCurrentValue >= GET_TYPE_C_1_PMIC_SAFETY_CURRENT_VALUE())
        {
            DebugMessageTypeC("Pmic turn-off for Safety Protect", 0x00);

            ScalerTypeC1PmicSetting(_OFF, _PD_POWER_SNK, _PD_NONE_SETTING_PDO, 0, 0, _PD_PEAK_CUR_NONE);

#if(_TYPE_C_EIZO_CUSTOMIZED_PMIC_SIC437A_SUPPORT == _ON)
            // [Eizo] SIC437A Customized Power Control : OCP
            ScalerTypeC1PmicSic437aPmicOcpProc();
#endif

            // Set OCP Event
            ScalerTypeC1PdSetSystemEvent(_PD_SYS_EVENT_POWER_OCP);
        }
        else
        {
            DebugMessageTypeC("Pmic Safety Protect Cancel!", 0x00);

            CLR_TYPE_C_1_PMIC_SAFETY_PROTECT_TRIGGER();

            ScalerTimerReactiveTimerEvent(10, _SCALER_TIMER_EVENT_TYPE_C_1_PMIC_TRACKING);
        }
    }
}
#endif

#elif(_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_POLLING_PMIC)
//--------------------------------------------------
// Description  : Type-C 1 PMIC Polling Ocp Tracking
// Input Value  : enumTypeCPcbPort
// Output Value : Delay_Time(Unit: ms): 10 ~ 253
//--------------------------------------------------
BYTE ScalerTypeC1PmicTrackingPollingOcp(EnumTypeCPcbPort enumTypeCPcbPort)
{
    if(GET_TYPE_C_1_PMIC_OCP_PROTECT_TRIGGER() == _FALSE)
    {
        WORD usCurrentValue = 0x0000;
        WORD usOcpDelay = 0x0000;

        DebugMessageTypeC("Pmic Polling OCP Tracking", 0x00);

        // Read current value from PMIC's ADC
        usCurrentValue = ExternalDeviceInterfaceTypeCPmicReadPmicAdcCurrentValue(enumTypeCPcbPort);

        // Debounce when current > OCP threshold
        if(usCurrentValue >= GET_TYPE_C_1_PMIC_OCP_CURRENT_VALUE())
        {
            ScalerTimerDelayXms(2);
            usCurrentValue = ExternalDeviceInterfaceTypeCPmicReadPmicAdcCurrentValue(enumTypeCPcbPort);
        }

        // OCP judgment
        if(usCurrentValue >= GET_TYPE_C_1_PMIC_OCP_CURRENT_VALUE())
        {
            usOcpDelay = MAXOF(_EMB_TYPE_C_1_PMIC_FW_OCP_DELAY_SHUTDOWN, 10);
            ScalerTimerReactiveTimerEvent(usOcpDelay, _SCALER_TIMER_EVENT_TYPE_C_1_PMIC_POLLING_OCP);

            DebugMessageTypeC("Pmic:Output Current OCP", 0x00);

            SET_TYPE_C_1_PMIC_OCP_PROTECT_TRIGGER();

            // Already in Safety Protect State
            return 0xFE;
        }

        // Set 10ms Timer Event for FW Polling OCP
        return 10;
    }

    // Already in Safety Protect State
    return 0xFE;
}

//--------------------------------------------------
// Description  : Type-C 1 PMIC FW Polling Ocp Protect
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PmicPollingOcpProtect(void)
{
    if(GET_TYPE_C_1_PMIC_OCP_PROTECT_TRIGGER() == _TRUE)
    {
        DebugMessageTypeC("Pmic turn-off for Polling OCP", 0x00);

        ScalerTypeC1PmicSetting(_OFF, _PD_POWER_SNK, _PD_NONE_SETTING_PDO, 0, 0, _PD_PEAK_CUR_NONE);

#if(_TYPE_C_EIZO_CUSTOMIZED_PMIC_SIC437A_SUPPORT == _ON)
        // [Eizo] SIC437A Customized Power Control : OCP
        ScalerTypeC1PmicSic437aPmicOcpProc();
#endif

        // Set OCP Event
        ScalerTypeC1PdSetSystemEvent(_PD_SYS_EVENT_POWER_OCP);
    }
}
#endif // End of #if((_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) || (_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_10_BIT_ADC))

#if(_EMB_TYPE_C_1_PMIC_VOLTAGE_COMPENSATION == _ON)
//--------------------------------------------------
// Description  : Type-C 1 PMIC Voltage Compensation
// Input Value  : enumTypeCPcbPort
// Output Value : Delay_Time(Unit: ms): 10 ~ 253
//--------------------------------------------------
BYTE ScalerTypeC1PmicTrackingVoltageCompensation(EnumTypeCPcbPort enumTypeCPcbPort)
{
    WORD usCurrentValue = 0x0000;
    WORD usVoltageValue = 0x0000;
    WORD usSchmittVIL = 0x0000;
    WORD usSchmittVIH = 0x0000;

    // Translate Current of 10-Bit_ADC to 10mA/bit
    usCurrentValue = ((WORD)((((DWORD)ScalerTypeCAdcCorrectionToIdealData(_TYPE_C_1_IMON, ScalerTypeCAdcGetAdcOutput(_TYPE_C_1_IMON))) * _EMB_TYPE_C_1_PMIC_IOUT_MAX_CURRENT) / 1024));

    // Calculate VIL of compesation voltage (10mV)
    usSchmittVIL = GET_TYPE_C_1_OUTPUT_VOL() + ((usCurrentValue * 10) / _TYPE_C_1_VOLTAGE_COMPESATION_CURRENT_UNIT);

    // Calculate VIH of compesation voltage (10mV)
    usSchmittVIH = GET_TYPE_C_1_OUTPUT_VOL() + (((usCurrentValue + 5) * 10) / _TYPE_C_1_VOLTAGE_COMPESATION_CURRENT_UNIT);

    // Translate Voltage of 10-Bit_ADC to 10mV/bit
    usVoltageValue = ((WORD)((((DWORD)ScalerTypeCAdcCorrectionToIdealData(_TYPE_C_CHANNEL_1_VMON, ScalerTypeCAdcGetAdcOutput(_TYPE_C_CHANNEL_1_VMON))) * _EMB_TYPE_C_1_PMIC_VBUS_MAX_VOLTAGE) / 1024));

    // Voltage compensation detect
    if(usVoltageValue < usSchmittVIL)
    {
        DebugMessageTypeC("0.Pmic:Currnet Value", usCurrentValue);
        DebugMessageTypeC("0.Pmic:Voltage Change", usSchmittVIL);

        if(ExternalDeviceInterfaceTypeCPmicVoltageCurrentSetting(enumTypeCPcbPort, _TYPE_C_PMIC_DIRECTION_SRC, usSchmittVIL, GET_TYPE_C_1_OUTPUT_CUR()) == _TYPE_C_PMIC_CONTROL_FAIL)
        {
            return 0xFF;
        }
    }
    else if(usVoltageValue > usSchmittVIH)
    {
        DebugMessageTypeC("0.Pmic:Currnet Value", usCurrentValue);
        DebugMessageTypeC("0.Pmic:Voltage Change", usSchmittVIH);

        if(ExternalDeviceInterfaceTypeCPmicVoltageCurrentSetting(enumTypeCPcbPort, _TYPE_C_PMIC_DIRECTION_SRC, usSchmittVIH, GET_TYPE_C_1_OUTPUT_CUR()) == _TYPE_C_PMIC_CONTROL_FAIL)
        {
            return 0xFF;
        }
    }

    return 200;
}
#endif // End of #if(_EMB_TYPE_C_1_PMIC_VOLTAGE_COMPENSATION == _ON)

#if(_EMB_TYPE_C_1_PMIC_INT_PIN_CHECK_METHOD == _TYPE_C_PMIC_INT_PIN_CHECK_BY_POLLING)
//--------------------------------------------------
// Description  : Type-C 1 PMIC INT Pin Check
// Input Value  : enumTypeCPcbPort
// Output Value : Delay_Time(Unit: ms): 10 ~ 253
//--------------------------------------------------
BYTE ScalerTypeC1PmicTrackingIntPin(EnumTypeCPcbPort enumTypeCPcbPort)
{
    // Check GPIO status
    if(ScalerTypeCGetPmicInterruptDetectStatus(enumTypeCPcbPort) == _TRUE)
    {
        ScalerTypeC1PmicSetting(_OFF, _PD_POWER_SNK, _PD_NONE_SETTING_PDO, 0, 0, _PD_PEAK_CUR_NONE);

#if(_TYPE_C_EIZO_CUSTOMIZED_PMIC_SIC437A_SUPPORT == _ON)
        // [Eizo] SIC437A Customized Power Control : OCP
        ScalerTypeC1PmicSic437aPmicOcpProc();
#endif

        DebugMessageTypeC("Pmic INT_Pin trigger!", 0xFF);

        // Set OCP Event
        ScalerTypeC1PdSetSystemEvent(_PD_SYS_EVENT_POWER_OCP);
    }

    return 200;
}
#endif // End of #if(_EMB_TYPE_C_1_PMIC_INT_PIN_CHECK_METHOD == _TYPE_C_PMIC_INT_PIN_CHECK_BY_POLLING)
#endif // End of #if(_EMB_TYPE_C_1_PMIC_CHECK_SUPPORT == _ON)

#if(_PORT_CTRL_EMB_UNATTACH_HW_FORCE_VBUS_OFF == _ON)
//--------------------------------------------------
// Description  : Type-C 1 Set PMIC Vbus Force Off Control Type
// Input Value  : enumForceOffType
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PmicSetForceOffControlType(EnumTypeCPmicForceOffType enumForceOffType)
{
    SET_TYPE_C_1_PMIC_FORCE_OFF_TYPE(enumForceOffType);
}

//--------------------------------------------------
// Description  : Type-C 1 Get PMIC Vbus Force Off Control Type
// Input Value  : None
// Output Value : enumForceOffType
//--------------------------------------------------
EnumTypeCPmicForceOffType ScalerTypeC1PmicGetForceOffControlType(void)
{
    return GET_TYPE_C_1_PMIC_FORCE_OFF_TYPE();
}

//--------------------------------------------------
// Description  : Type-C 1 Set Gpio Control Data
// Input Value  : enumPinConfig
//                ucPinControl : _HIGH/_LOW
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PmicSetForceOffGpio(EnumPinConfigType enumPinConfig, BYTE ucPinControl)
{
    SET_TYPE_C_1_PMIC_FORCE_OFF_PIN_CONFIG(enumPinConfig);
    SET_TYPE_C_1_PMIC_FORCE_OFF_PIN_CONTROL(ucPinControl);
}

//--------------------------------------------------
// Description  : Type-C 1 Get Gpio Pinshare Config
// Input Value  : None
// Output Value : enumPinConfig
//--------------------------------------------------
EnumPinConfigType ScalerTypeC1PmicGetForceOffGpioPinConfig(void)
{
    return GET_TYPE_C_1_PMIC_FORCE_OFF_PIN_CONFIG();
}

//--------------------------------------------------
// Description  : Type-C 1 Get Gpio Control Value
// Input Value  : None
// Output Value : ucPinControl : _HIGH/_LOW
//--------------------------------------------------
BYTE ScalerTypeC1PmicGetForceOffGpioPinControl(void)
{
    return GET_TYPE_C_1_PMIC_FORCE_OFF_PIN_CONTROL();
}
#endif // End of #if(_PORT_CTRL_EMB_UNATTACH_HW_FORCE_VBUS_OFF == _ON)

/////////////////////////////////////
// EIZO PMIC SIC437A CUSTOMIZED FW //
/////////////////////////////////////
#if(_TYPE_C_EIZO_CUSTOMIZED_PMIC_SIC437A_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Type-C 1 Unattached Power Control Flow
// Input Value  : enumPowerRole : _TYPE_C_POWER_SRC / _TYPE_C_POWER_SNK
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PmicSic437aUnattachProc(EnumTypeCPowerRole enumPowerRole)
{
    EnumTypeCVbusCheckType enumVbusCheckType = ExternalDeviceInterfaceTypeCPmicUnattachProc(ScalerTypeCxPcbxMapping(_EMB_TYPE_C_1), enumPowerRole);

    ScalerTypeC1PmicSic437aVbusCheckProc(enumVbusCheckType);
}

//--------------------------------------------------
// Description  : Type-C 1 Send/Receive Hard Reset Control Flow
// Input Value  : enumPowerRole : _TYPE_C_POWER_SRC / _TYPE_C_POWER_SNK
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PmicSic437aHardRstStartProc(EnumTypeCPowerRole enumPowerRole)
{
    EnumTypeCVbusCheckType enumVbusCheckType = ExternalDeviceInterfaceTypeCPmicHardRstStartProc(ScalerTypeCxPcbxMapping(_EMB_TYPE_C_1), enumPowerRole);

    ScalerTypeC1PmicSic437aVbusCheckProc(enumVbusCheckType);
}

//--------------------------------------------------
// Description  : Type-C 1 as SRC and Vbus Has Turned Off During Hard Reset Control Flow
// Input Value  : None
// Output Value : Control Result : _SUCCESS / _FAIL
//--------------------------------------------------
BYTE ScalerTypeC1PmicSic437aHardRstVbusOffProc(void)
{
    if(ExternalDeviceInterfaceTypeCPmicHardRstVbusOffProc(ScalerTypeCxPcbxMapping(_EMB_TYPE_C_1)) == _TYPE_C_PMIC_CONTROL_SUCCESS)
    {
        return _SUCCESS;
    }
    else
    {
        return _FAIL;
    }
}

//--------------------------------------------------
// Description  : Type-C 1 Detect OCP Event Control Flow
// Input Value  : None
// Output Value : Control Result : _SUCCESS / _FAIL
//--------------------------------------------------
BYTE ScalerTypeC1PmicSic437aPmicOcpProc(void)
{
    if(ExternalDeviceInterfaceTypeCPmicOcpProc(ScalerTypeCxPcbxMapping(_EMB_TYPE_C_1)) == _TYPE_C_PMIC_CONTROL_SUCCESS)
    {
        return _SUCCESS;
    }
    else
    {
        return _FAIL;
    }
}

//--------------------------------------------------
// Description  : Type-C 1 Vbus Check Control Flow
// Input Value  : Vbus Check Type : _TYPE_C_VBUS_CHECK_0V / _TYPE_C_VBUS_CHECK_5V
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PmicSic437aVbusCheckProc(EnumTypeCVbusCheckType enumVbusCheckType)
{
    if(enumVbusCheckType == _TYPE_C_VBUS_CHECK_5V)
    {
        // Set ADC In Out Range Comparator = In Range vSafe5V
        ScalerTypeCAdcInOutCompIntSetting(_TYPE_C_CHANNEL_1_VMON, GET_TYPE_C_1_5V_UP_BND(), GET_TYPE_C_1_5V_LOW_BND(), _TYPE_C_ADC_WITHIN_RANGE);

        // Enable INT
        ScalerTypeCAdcInOutCompIntControl(_TYPE_C_CHANNEL_1_VMON, _ENABLE);

        // Set Vbus 5V Check Flag
        SET_TYPE_C_1_PMIC_EIZO_VBUS_5V_CHECK();
    }
    else if(enumVbusCheckType == _TYPE_C_VBUS_CHECK_0V)
    {
        // Set ADC In Out Range Comparator = In Range vSafe0V
        ScalerTypeCAdcInOutCompIntSetting(_TYPE_C_CHANNEL_1_VMON, GET_TYPE_C_1_0V_UP_BND(), 0, _TYPE_C_ADC_WITHIN_RANGE);

        // Enable INT
        ScalerTypeCAdcInOutCompIntControl(_TYPE_C_CHANNEL_1_VMON, _ENABLE);

        // Set Vbus 0V Check Flag
        SET_TYPE_C_1_PMIC_EIZO_VBUS_0V_CHECK();
    }
}
#endif // End of #if(_TYPE_C_EIZO_CUSTOMIZED_PMIC_SIC437A_SUPPORT == _ON)
#endif // End of #if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON) && (_EMB_TYPE_C_1_PMIC_TYPE != _PMIC_NONE))

