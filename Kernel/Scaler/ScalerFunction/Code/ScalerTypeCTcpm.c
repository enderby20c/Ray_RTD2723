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
// ID Code      : ScalerTypeCTcpm.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"
#include "TypeCTcpm/ScalerTypeCTcpm.h"


#if(_TYPE_C_PORT_CTRL_SUPPORT == _ON)
#if(_PORT_CTRL_TCPM_SUPPORT == _ON)
//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
volatile StructTypeCTcpmHwShift g_pstTypeCTcpmHwShift[_TCPM_PORT_VALID];
volatile StructTypeCTcpmInfo g_pstTypeCTcpmInfo[_TCPM_PORT_VALID];
volatile StructTypeCTcpmDeviceInfo g_pstTypeCTcpmDeviceInfo[_TCPM_PORT_VALID];
volatile StructTypeCTcpmTopInfo g_pstTypeCTcpmTopInfo[_TCPM_PORT_VALID];
volatile StructTypeCTcpmCcInfo g_pstTypeCTcpmCcInfo[_TCPM_PORT_VALID];
volatile StructTypeCTcpmPdInfo g_pstTypeCTcpmPdInfo[_TCPM_PORT_VALID];
volatile StructTypeCTcpmPdPartnerInfo g_pstTypeCTcpmPdPartnerInfo[_TCPM_PORT_VALID];
volatile StructTypeCTcpmPdVdmInfo g_pstTypeCTcpmPdVdmInfo[_TCPM_PORT_VALID];
volatile StructTypeCTcpmPdRxInfo g_pstTypeCTcpmPdRxInfo[_TCPM_PORT_VALID];
volatile StructTypeCTcpmPdTxInfo g_pstTypeCTcpmPdTxInfo[_TCPM_PORT_VALID];
volatile StructTypeCTcpmPowerInfo g_pstTypeCTcpmPowerInfo[_TCPM_PORT_VALID];

#if(_TYPE_C_PMIC_SUPPORT == _ON)
volatile StructTypeCTcpmPmicControl g_pstTypeCTcpmPmicControl[_TCPM_PORT_VALID];
#endif

volatile StructTypeCCableStatus g_pstTypeCTcpmPdCableInfo[_TCPM_PORT_VALID];
volatile StructTypeCCableInfoForDpcd g_pstTypeCTcpmPdCableInfoForDpcd[_TCPM_PORT_VALID];
volatile StructTypeCStatusEvent g_pstTypeCTcpmPdStatusEvent[_TCPM_PORT_VALID];
volatile StructTypeCAlertEvent g_pstTypeCTcpmPdAlertEvent[_TCPM_PORT_VALID];

volatile BYTE g_pucTypeCTcpmPdDataObj[_MAX_DATA_OBJ_CNT * 4];

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Type C TCPM Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmInitial(void)
{
    // Set TCPM HW Shift Index
    ScalerTypeCTcpmSetHwShiftIndex();

    // TCPM Default Setting (PCB Define / Initial State Setting)
    ScalerTypeCTcpmDefaultSetting();

    // TCPM Pinshare Setting
    ScalerTypeCTcpmPinshareSetting();

    // TCPM Clock Setting
    ScalerTypeCTcpmClockSetting(_IOSC_CLK);

#if(_HW_TCPM_0_SUPPORT == _ON)
    // Enable TCPM0 Related INT
    // [0xFA12] [6] tcpm_irq_en, [2] tcpc_0_irq_en, [0] tcpc_1_irq_en
    ScalerSetBit(PFA_12_TCPM_RELATED_IRQ_1, ~(_BIT6 | _BIT2 | _BIT0), (_BIT6 | _BIT2 | _BIT0));

    // [0xFA13] [6] tcpc_0_auto_rd_irq_en, [4] tcpc_0_auto_wr_irq_en, [2] tcpc_1_auto_rd_irq_en, [0] tcpc_1_auto_wr_irq_en
    ScalerSetBit(PFA_13_TCPM_RELATED_IRQ_2, ~(_BIT6 | _BIT4 | _BIT2 | _BIT0), (_BIT6 | _BIT4 | _BIT2 | _BIT0));
#endif

#if(_HW_TCPM_1_SUPPORT == _ON)
    // Enable TCPM1 Related INT
    // [0xFB12] [6] tcpm_irq_en, [2] tcpc_0_irq_en, [0] tcpc_1_irq_en
    ScalerSetBit(PFB_12_TCPM_RELATED_IRQ, ~(_BIT6 | _BIT2 | _BIT0), (_BIT6 | _BIT2 | _BIT0));

    // [0xFB13] [6] tcpc_0_auto_rd_irq_en, [4] tcpc_0_auto_wr_irq_en, [2] tcpc_1_auto_rd_irq_en, [0] tcpc_1_auto_wr_irq_en
    ScalerSetBit(PFB_13_TCPM_RELATED_IRQ_2, ~(_BIT6 | _BIT4 | _BIT2 | _BIT0), (_BIT6 | _BIT4 | _BIT2 | _BIT0));
#endif

    // [RL6978-3962]
    // Tool Usage : [0xFA0E] [3] Unattach HW Force Vbus Off Enable Control, 0 = Disble, 1 = Enable
    // Tool Not Show Warning UI Initially
    ScalerSetBit(PFA_0E_DUMMY_1, ~(_BIT4 | _BIT3), 0x00);
}

//--------------------------------------------------
// Description  : Type C Initial Proc for CC / PD / PMIC / TCPC
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmInitialProc(EnumTypeCPcbPort enumTypeCPcbPort)
{
    BYTE ucPortIndex = ScalerTypeCTcpmGetPortIndex(enumTypeCPcbPort);

    if((ScalerTypeCTcpmTcpciGetByte(ucPortIndex, _TCPM_TCPCI_REG_PWR_STATUS) & _TCPM_TCPCI_PWR_STAT_INIT_STATUS) == 0x00)
    {
        // CC / PD / PMIC Initial
        ScalerTypeCTcpmCcInitial(ucPortIndex);
        ScalerTypeCTcpmPdInitial(ucPortIndex);
#if(_TYPE_C_PMIC_SUPPORT == _ON)
        if(GET_TCPM_PMIC_SUPPORT(ucPortIndex) == _ON)
        {
            ScalerTypeCTcpmPmicInitial(ucPortIndex);
        }
#endif

        // Set TCPC Initial Setting (Enable WDTimer, Fault Detection...)
        ScalerTypeCTcpmInitializeTcpc(ucPortIndex);

        // Get TCPC Device Info (VID, PID, Spec Ver) and Capability (Device Cap, Std I/O Cap...)
        ScalerTypeCTcpmGetTcpcInfo(ucPortIndex);

#if(_HW_TCPM_SUPPORT == _ON)
        // Enable Alert Auto Ctrl Based On Define Settings
        ScalerTypeCTcpmAlertAutoCtrlSetting(ucPortIndex);
#endif

        // 3. TCPM Has Read TCPC Info, Active TCPM Flow
        SET_TCPM_STATE(ucPortIndex, _TCPM_ACTIVE);
    }
}

//--------------------------------------------------
// Description  : Type C TCPM Handler
// Input Value  : enumTypeCPcbPort
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmHandler(EnumTypeCPcbPort enumTypeCPcbPort)
{
    BYTE ucPortIndex = ScalerTypeCTcpmGetPortIndex(enumTypeCPcbPort);

    switch(GET_TCPM_STATE(ucPortIndex))
    {
        case _TCPM_WAIT_TCPC_ON:

            ScalerTypeCTcpmInitialProc(enumTypeCPcbPort);

            break;

        case _TCPM_ACTIVE:

            // Control TCPC to Execute TypeC Function
            ScalerTypeCTcpmCcHandler(ucPortIndex);

            // Do PD Handler Only When "CC Attach" & "Not During Sink Detect CC Open for tPDDebounce"
            // --------------- [Warning] On-Semi -------------
            // (1) TCPC Will Generate Unexpexted HRST_ALERT in SNK BIST Test Data Mode, Which Makes PD into SNK HRST Wait Vbus Off
            // (2) When BIST Mode Finish, TCPC Will Generate CC_STATUS_ALERT for CC Open, Which Will Active WD for tPDDebounce
            // (3) "HRST Vbus Off" and "tPDDebounce" May Happens at Same Time, And Will Cause FW Deadlock in SNK HRST After Unattach
            // -----------------------------------------------
            if((GET_TCPM_CC_ATTACHED(ucPortIndex) == _TRUE) && (GET_TCPM_CC_SNK_UNATTACH_DBC(ucPortIndex) != _TRUE))
            {
                ScalerTypeCTcpmPdHandler(ucPortIndex);
            }

#if((_TYPE_C_PMIC_SUPPORT == _ON) && (_PORT_CTRL_TCPM_PMIC_CHECK_SUPPORT == _ON))
            if((GET_TCPM_PMIC_SUPPORT(ucPortIndex) == _ON) && (GET_TCPM_PMIC_CHECK_SUPPORT(ucPortIndex) == _ON))
            {
                ScalerTypeCTcpmPmicHandler(ucPortIndex);
            }
#endif

            break;

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Timer Event Proc of TCPM
// Input Value  : enumTypeCPcbPort, enumTcpmEventID
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmTimerEventProc(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCTcpmEventID enumTcpmEventID)
{
    BYTE ucPortIndex = ScalerTypeCTcpmGetPortIndex(enumTypeCPcbPort);

    switch(enumTcpmEventID)
    {
#if(_PORT_CTRL_EMB_PD3_PPS_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_TCPM_PPS_TIMEOUT:

            if(GET_TCPM_PD_FW_STATE(ucPortIndex) == _PD_HARDRESET)
            {
                return;
            }

            // PPS Timeout : Send Hard Reset
            ScalerTypeCTcpmPdSendHardRst(ucPortIndex);

            break;
#endif

        case _SCALER_TIMER_EVENT_TCPM_SNK_HARD_RST_TIMEOUT:

            if((GET_TCPM_POWER_ROLE(ucPortIndex) == _PD_POWER_SNK) && (GET_TCPM_PD_FW_STATE(ucPortIndex) == _PD_HARDRESET))
            {
                if(GET_TCPM_PD_HARD_RST_CNT(ucPortIndex) <= _MAX_HARD_RST_CNT)
                {
                    // Enable PD Rcv Detect ([0x2F] : [5] HRST)
                    ScalerTypeCTcpmTcpciSetByte(ucPortIndex, _TCPM_TCPCI_REG_RCV_DETECT, (_TCPM_TCPCI_RCV_DET_HRST));

                    // Send Hard Reset
                    ScalerTypeCTcpmPdSendHardRst(ucPortIndex);
                }
                else
                {
                    // Transit to PD No-Response, and Disable Rcv Msg. INT
                    SET_TCPM_PD_FW_STATE(ucPortIndex, _PD_NO_RESPONSE);

                    // Enable Vbus Detect
                    ScalerTypeCTcpmTcpciSetByte(ucPortIndex, _TCPM_TCPCI_REG_COMMAND, _TCPM_TCPCI_CMD_EN_VBUS_DET);

                    // Enable Sinking Vbus
                    ScalerTypeCTcpmVbusCtrl(ucPortIndex, _ON, _PD_POWER_SNK, _PD_FIX_SUPPLY_PDO, 500, 0, _PD_PEAK_CUR_NONE);

                    // Start PMIC Protection
                    ScalerTypeCTcpmVbusProtectStart(ucPortIndex, _TYPE_C_POWER_SNK);

                    // Enable Sink Detect Disconnect (Disabled When Sending/Rcving HRST)
                    ScalerTypeCTcpmAlertControl(ucPortIndex, (WORD)(_TCPM_TCPCI_ALERT_SNK_DISC), _ENABLE);
                }
            }

            break;

        case _SCALER_TIMER_EVENT_TCPM_S8_HRST:

            if(GET_TCPM_PD_FW_STATE(ucPortIndex) == _PD_HARDRESET)
            {
                return;
            }

            // If It is Already in DP Config, No Need to Do Hard Reset
            if(GET_TCPM_PD_DPAM_CONFIG(ucPortIndex) != _PD_DP_CONFIG)
            {
                ScalerTypeCTcpmPdSendHardRst(ucPortIndex);
            }

            break;

        case _SCALER_TIMER_EVENT_TCPM_SEND_HARD_RST:

            if(GET_TCPM_PD_FW_STATE(ucPortIndex) == _PD_HARDRESET)
            {
                return;
            }

            // Separate "Normal Flow" & "S8 Interop" TimerEvent Since HRST Event Will be Canceled During Power Contract
            ScalerTypeCTcpmPdSendHardRst(ucPortIndex);

            break;

        case _SCALER_TIMER_EVENT_TCPM_CLR_REQ_WAIT:

            CLR_TCPM_PD_REQ_WAIT_FLAG(ucPortIndex);

            break;

        case _SCALER_TIMER_EVENT_TCPM_CLR_PARTNER_ALT_SUPPORT:

            CLR_TCPM_PD_PARTNER_ALT_SUPPORT(ucPortIndex);

            break;

        case _SCALER_TIMER_EVENT_TCPM_TPC_ERROR_RECOVERY:
        case _SCALER_TIMER_EVENT_TCPM_T480_ERROR_RECOVERY:

            SET_TCPM_CC_ERROR_RECOVERY(ucPortIndex);

            break;

        case _SCALER_TIMER_EVENT_TCPM_SRC_TURN_OFF_POWER:

            if((GET_TCPM_POWER_ROLE(ucPortIndex) == _PD_POWER_SRC) && (GET_TCPM_PD_FW_STATE(ucPortIndex) == _PD_HARDRESET))
            {
                // From : (A)Source Send Hard Reset
                // 1. Turn Off Source Vbus
                ScalerTypeCTcpmVbusCtrl(ucPortIndex, _OFF, _PD_POWER_SRC, _PD_NONE_SETTING_PDO, 0, 0, _PD_PEAK_CUR_NONE);

                // 2. Turn On Vbus Discharge
                ScalerTypeCTcpmVbusDischargeCtrl(ucPortIndex, _ON);
            }

            break;

        case _SCALER_TIMER_EVENT_TCPM_SRC_TURN_ON_POWER:

            if(GET_TCPM_PD_SPEC_VER(ucPortIndex) == _PD_VERSION_3_0)
            {
                // if(PD 3.0) Switch Rp to Default Rp (36K / 12K / 4.7K)
                if(GET_TCPM_CC_RP_DEF_VALUE(ucPortIndex) == _TYPE_C_SRC_DEF_USB)
                {
                    SET_TCPM_ROLE_CONTROL(ucPortIndex, _BIT2 | _BIT0);
                }
                else if(GET_TCPM_CC_RP_DEF_VALUE(ucPortIndex) == _TYPE_C_SRC_DEF_1P5A)
                {
                    SET_TCPM_ROLE_CONTROL(ucPortIndex, _BIT4 | _BIT2 | _BIT0);
                }
                else
                {
                    SET_TCPM_ROLE_CONTROL(ucPortIndex, _BIT5 | _BIT2 | _BIT0);
                }

                ScalerTypeCTcpmTcpciSetByte(ucPortIndex, _TCPM_TCPCI_REG_ROLE_CTRL, GET_TCPM_ROLE_CONTROL(ucPortIndex));
            }

            // Turn On Vconn (POWER_CONTROL [0x1C] [0] Vconn Enable)
            ScalerTypeCTcpmVconnCtrl(ucPortIndex, _ON);

            // Set OCP Threshlod
            SET_TCPM_OCP_CURRENT(ucPortIndex, (WORD)(((DWORD)(GET_TCPM_CC_DEF_CUR(ucPortIndex)) * (DWORD)(GET_TCPM_OCP_RATIO(ucPortIndex, 0))) / 100));

            // Turn On Vbus (Enable Sourceing Vbus)
            ScalerTypeCTcpmVbusCtrl(ucPortIndex, _ON, _PD_POWER_SRC, _PD_FIX_SUPPLY_PDO, 500, GET_TCPM_OCP_CURRENT(ucPortIndex), _PD_PEAK_CUR_NONE);

            break;


        case _SCALER_TIMER_EVENT_TCPM_CLR_PRS_WAIT:

            CLR_TCPM_PD_PRS_WAIT_FLAG(ucPortIndex);

            break;

        case _SCALER_TIMER_EVENT_TCPM_CLR_DRS_WAIT:

            CLR_TCPM_PD_DRS_WAIT_FLAG(ucPortIndex);

            break;

        case _SCALER_TIMER_EVENT_TCPM_CLR_VCS_WAIT:

            CLR_TCPM_PD_VCS_WAIT_FLAG(ucPortIndex);

            break;

        case _SCALER_TIMER_EVENT_TCPM_DFP_START_ALT_MODE:

            SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_SEND_DISCOVER_ID);

            break;

        case _SCALER_TIMER_EVENT_TCPM_VDM_RESP_CONFLICT_TIMEOUT:

            SET_TCPM_CC_ERROR_RECOVERY(ucPortIndex);
            ADD_TCPM_PD_VDM_RESP_CONFLICT_CNT(ucPortIndex);

            break;

        case _SCALER_TIMER_EVENT_TCPM_CLR_ATTENTION_WAIT:

            CLR_TCPM_PD_DPAM_ATTENTION_WAIT(ucPortIndex);

            break;

        case _SCALER_TIMER_EVENT_TCPM_CLR_GET_SNK_CAP_WAIT:

            CLR_TCPM_PD_GET_SNK_CAP_WAIT_FLAG(ucPortIndex);

            break;

        case _SCALER_TIMER_EVENT_TCPM_CLR_VDMMSG_WAIT:

            CLR_TCPM_PD_VDMMSG_WAIT_FLAG(ucPortIndex);

            break;

        case _SCALER_TIMER_EVENT_TCPM_CLR_VDM_BUSY_FLAG:

            CLR_TCPM_PD_VDM_BUSY_FLAG(ucPortIndex);

            break;

#if(_PORT_CTRL_TCPM_OVP_UVP_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_TCPM_OVP_UVP_CHECK:

            if(GET_TCPM_OVP_UVP_CHECK(ucPortIndex) == _TRUE)
            {
                ScalerTypeCTcpmOvpUvpHandler(ucPortIndex);
            }

            break;
#endif

#if((_TYPE_C_PMIC_SUPPORT == _ON) && (_PORT_CTRL_TCPM_PMIC_CHECK_SUPPORT == _ON))
        case _SCALER_TIMER_EVENT_TCPM_PMIC_TRACKING:

            // Check if PMIC Protection Valid
            if(GET_TCPM_PMIC_PROTECT_VALID(ucPortIndex) == _TRUE)
            {
                ScalerTypeCTcpmPmicProtectTracking(ucPortIndex);
            }

            break;

#if(_TYPE_C_PMIC_FW_POLLING_OCP_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_TCPM_PMIC_POLLING_OCP:

            if(GET_TCPM_PMIC_OCP_PROTECT_TRIGGER(ucPortIndex) == _TRUE)
            {
                ScalerTypeCTcpmPmicPollingOcpProtect(ucPortIndex);
            }

            break;
#endif
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Set TCPM Discharge Count
// Input Value  : enumTypeCPcbPort, ucDischargeCount : 0-255
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmSetDischargeCount(EnumTypeCPcbPort enumTypeCPcbPort, BYTE ucDischargeCount)
{
    SET_TCPM_CC_DISCHARGE_COUNT(ScalerTypeCTcpmGetPortIndex(enumTypeCPcbPort), ucDischargeCount);
}

//--------------------------------------------------
// Description  : Set TCPM CC Operation Mode
// Input Value  : enumTypeCPcbPort, enumOperationMode
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmSetOperationMode(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCOperationMode enumOperationMode)
{
    BYTE ucPortIndex = ScalerTypeCTcpmGetPortIndex(enumTypeCPcbPort);

    switch(enumOperationMode)
    {
        case _TYPE_C_SRC_ONLY_MODE:

            SET_TCPM_CC_PORT_ROLE(ucPortIndex, _TYPE_C_PORT_SRC_ONLY);
            SET_TCPM_CC_DRP_PREFER(ucPortIndex, _TYPE_C_DRP_NO_PREFERENCE);

            break;

        case _TYPE_C_SNK_ONLY_MODE:

            SET_TCPM_CC_PORT_ROLE(ucPortIndex, _TYPE_C_PORT_SNK_ONLY);
            SET_TCPM_CC_DRP_PREFER(ucPortIndex, _TYPE_C_DRP_NO_PREFERENCE);

            break;

        case _TYPE_C_DRP_NO_PREFERENCE_MODE:

            SET_TCPM_CC_PORT_ROLE(ucPortIndex, _TYPE_C_PORT_DRP);
            SET_TCPM_CC_DRP_PREFER(ucPortIndex, _TYPE_C_DRP_NO_PREFERENCE);

            break;

        case _TYPE_C_DRP_TRY_SNK_MODE:

            SET_TCPM_CC_PORT_ROLE(ucPortIndex, _TYPE_C_PORT_DRP);
            SET_TCPM_CC_DRP_PREFER(ucPortIndex, _TYPE_C_DRP_TRY_SNK);

            break;

        case _TYPE_C_DRP_TRY_SRC_MODE:

            SET_TCPM_CC_PORT_ROLE(ucPortIndex, _TYPE_C_PORT_DRP);
            SET_TCPM_CC_DRP_PREFER(ucPortIndex, _TYPE_C_DRP_TRY_SRC);

            break;

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Set TCPM Source Max Supply Power
// Input Value  : enumTypeCPcbPort, usMaxPower in 0.1W
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmSetMaxPower(EnumTypeCPcbPort enumTypeCPcbPort, WORD usMaxPower)
{
    BYTE ucPortIndex = ScalerTypeCTcpmGetPortIndex(enumTypeCPcbPort);

#if(_PORT_CTRL_EMB_PD3_1_EPR_SUPPORT)
    if(GET_TCPM_PD_EPR_SRC_CAPABLE(ucPortIndex) == _TRUE)
    {
        if(usMaxPower <= 2400)
        {
            SET_TCPM_MAX_POWER(ucPortIndex, usMaxPower);
        }
        else
        {
            SET_TCPM_MAX_POWER(ucPortIndex, 2400);
            DebugMessageTypeC("8. [TCPM] ==========X Max Power > 240W, Clamp to 240W", usMaxPower);
        }
    }
    else
#endif
    {
        if(usMaxPower <= 1000)
        {
            SET_TCPM_MAX_POWER(ucPortIndex, usMaxPower);
        }
        else
        {
            SET_TCPM_MAX_POWER(ucPortIndex, 1000);
            DebugMessageTypeC("8. [TCPM] ==========X Max Power > 100W, Clamp to 100W", usMaxPower);
        }
    }
}

//--------------------------------------------------
// Description  : Set TCPM Number of SPR/EPR PDO Count
// Input Value  : enumTypeCPcbPort, enumPowerRole(Src/Snk PDO), ucSPRPdoCnt, ucEPRPdoCnt
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmSetPdoCnt(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole, BYTE ucSPRPdoCnt, BYTE ucEPRPdoCnt)
{
    BYTE ucPortIndex = ScalerTypeCTcpmGetPortIndex(enumTypeCPcbPort);
    ucEPRPdoCnt = ucEPRPdoCnt;

    if(enumPowerRole == _TYPE_C_POWER_SRC)
    {
        SET_TCPM_PD_SPR_SRC_PDO_CNT(ucPortIndex, ucSPRPdoCnt);

#if(_PORT_CTRL_EMB_PD3_1_EPR_SUPPORT)
        SET_TCPM_PD_EPR_SRC_PDO_CNT(ucPortIndex, ucEPRPdoCnt);
#endif
    }
    else if(enumPowerRole == _TYPE_C_POWER_SNK)
    {
        SET_TCPM_PD_SPR_SNK_PDO_CNT(ucPortIndex, ucSPRPdoCnt);

#if(_PORT_CTRL_EMB_PD3_1_EPR_SUPPORT)
        SET_TCPM_PD_EPR_SNK_PDO_CNT(ucPortIndex, ucEPRPdoCnt);
#endif
    }
}

//--------------------------------------------------
// Description  : Get TCPM Number of SPR/EPR PDO Count
// Input Value  : enumTypeCPcbPort, enumPowerRole(Src/Snk PDO), *pucSPRPdoCnt, *pucEPRPdoCnt
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmGetPdoCnt(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole, BYTE *pucSPRPdoCnt, BYTE *pucEPRPdoCnt)
{
    BYTE ucPortIndex = ScalerTypeCTcpmGetPortIndex(enumTypeCPcbPort);
    *pucEPRPdoCnt = 0;

    if(enumPowerRole == _TYPE_C_POWER_SRC)
    {
        *pucSPRPdoCnt = GET_TCPM_PD_SPR_SRC_PDO_CNT(ucPortIndex);

#if(_PORT_CTRL_EMB_PD3_1_EPR_SUPPORT)
        *pucEPRPdoCnt = GET_TCPM_PD_EPR_SRC_PDO_CNT(ucPortIndex);
#endif
    }
    else if(enumPowerRole == _TYPE_C_POWER_SNK)
    {
        *pucSPRPdoCnt = GET_TCPM_PD_SPR_SNK_PDO_CNT(ucPortIndex);

#if(_PORT_CTRL_EMB_PD3_1_EPR_SUPPORT)
        *pucEPRPdoCnt = GET_TCPM_PD_EPR_SNK_PDO_CNT(ucPortIndex);
#endif
    }
}

//--------------------------------------------------
// Description  : Set TCPM Src/Snk Cap Fix PDO Info
// Input Value  : enumTypeCPcbPort, enumPowerRole(Src/Snk PDO), ucPdoIndex, usVoltage(100mV), usMaxCur(10mA), enumPeakCur
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmSetFixPdo(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole, BYTE ucPdoIndex, WORD usVoltage, WORD usMaxCur, EnumTypeCPDPeakCurType enumPeakCur)
{
    BYTE ucPortIndex = ScalerTypeCTcpmGetPortIndex(enumTypeCPcbPort);

    // Convert Voltage from User 100mV to Fix PDO 10mV
    usVoltage = usVoltage * 10;

    usMaxCur = usMaxCur;

    enumPeakCur = enumPeakCur;

    if(enumPowerRole == _TYPE_C_POWER_SRC)
    {
        // Check PDO Index is Valid [Max PDO Num = 11 (7 SPR PDO + 4 EPR PDO)] and PDO Power < Max Power
        if(((ucPdoIndex >= 1) && (ucPdoIndex <= 11)) && ((WORD)((DWORD)usVoltage * usMaxCur / 1000) <= GET_TCPM_MAX_POWER(ucPortIndex)))
        {
            SET_TCPM_PD_SRC_PDO_TYPE(ucPortIndex, (ucPdoIndex - 1), _PD_FIX_SUPPLY_PDO);

            // Set Peak Current
            SET_TCPM_PD_SRC_CAP_PEAK(ucPortIndex, (ucPdoIndex - 1), enumPeakCur);

            // -------------------- Voltage Setting --------------------
            if(ucPdoIndex <= 7)
            {
                if(usVoltage <= 2000)
                {
                    // SPR PDOs Voltage Cannot More Than 20V
                    SET_TCPM_PD_SRC_CAP_VOL_MAX(ucPortIndex, (ucPdoIndex - 1), usVoltage);
                    SET_TCPM_PD_SRC_CAP_VOL_MIN(ucPortIndex, (ucPdoIndex - 1), usVoltage);
                }
                else
                {
                    SET_TCPM_PD_SRC_CAP_VOL_MAX(ucPortIndex, (ucPdoIndex - 1), 2000);
                    SET_TCPM_PD_SRC_CAP_VOL_MIN(ucPortIndex, (ucPdoIndex - 1), 2000);
                }
            }
            else
            {
                if(usVoltage <= 4800)
                {
                    // EPR PDOs Voltage Cannot More Than 48V
                    SET_TCPM_PD_SRC_CAP_VOL_MAX(ucPortIndex, (ucPdoIndex - 1), usVoltage);
                    SET_TCPM_PD_SRC_CAP_VOL_MIN(ucPortIndex, (ucPdoIndex - 1), usVoltage);
                }
                else
                {
                    SET_TCPM_PD_SRC_CAP_VOL_MAX(ucPortIndex, (ucPdoIndex - 1), 4800);
                    SET_TCPM_PD_SRC_CAP_VOL_MIN(ucPortIndex, (ucPdoIndex - 1), 4800);
                }
            }

            // -------------------- Current Setting --------------------
            if(usMaxCur <= 500)
            {
                SET_TCPM_PD_SRC_CAP_CUR(ucPortIndex, (ucPdoIndex - 1), usMaxCur);
            }
            else
            {
                // Current Cannot More Than 5A
                SET_TCPM_PD_SRC_CAP_CUR(ucPortIndex, (ucPdoIndex - 1), 500);
            }
        }
        else
        {
            if((usVoltage * usMaxCur / 1000) > GET_TCPM_MAX_POWER(ucPortIndex))
            {
                DebugMessageTypeC("8. [TCPM] ==========X Set Fix PDO Error : PDO > Max Power", ucPdoIndex);
            }
            else
            {
                DebugMessageTypeC("8. [TCPM] ==========X Set Fix PDO Index Error", ucPdoIndex);
            }
        }
    }
    else if(enumPowerRole == _TYPE_C_POWER_SNK)
    {
        // Set Sink Capability
        if((ucPdoIndex >= 1) && (ucPdoIndex <= 7))
        {
            SET_TCPM_PD_SNK_PDO_TYPE(ucPortIndex, (ucPdoIndex - 1), _PD_FIX_SUPPLY_PDO);

            // -------------------- Voltage Setting --------------------
            if(usVoltage <= 2000)
            {
                // Other PDOs Voltage Cannot More Than 20V
                SET_TCPM_PD_SNK_CAP_VOL_MAX(ucPortIndex, (ucPdoIndex - 1), usVoltage);
                SET_TCPM_PD_SNK_CAP_VOL_MIN(ucPortIndex, (ucPdoIndex - 1), usVoltage);
            }
            else
            {
                SET_TCPM_PD_SNK_CAP_VOL_MAX(ucPortIndex, (ucPdoIndex - 1), 2000);
                SET_TCPM_PD_SNK_CAP_VOL_MIN(ucPortIndex, (ucPdoIndex - 1), 2000);
            }

            // -------------------- Current Setting --------------------
            if(usMaxCur <= 500)
            {
                SET_TCPM_PD_SNK_CAP_CUR(ucPortIndex, (ucPdoIndex - 1), usMaxCur);
            }
            else
            {
                // Current Cannot More Than 5A
                SET_TCPM_PD_SNK_CAP_CUR(ucPortIndex, (ucPdoIndex - 1), 500);
            }
        }
    }
}

#if(_PORT_CTRL_EMB_PD3_PPS_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set TCPM Src/Snk Cap Argumented PDO (PPS) Info
// Input Value  : enumTypeCPcbPort, enumPowerRole(Src/Snk PDO), ucPdoIndex, usMinVol(100mV), usMaxVol(100mV), ucMaxCur(50mA)
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmSetPpsPdo(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole, BYTE ucPdoIndex, WORD usMinVol, WORD usMaxVol, BYTE ucMaxCur)
{
    BYTE ucPortIndex = ScalerTypeCTcpmGetPortIndex(enumTypeCPcbPort);

    // Convert Voltage from User 100mV to Fix PDO 10mV
    WORD usMaxVoltage = usMaxVol * 10;
    WORD usMinVoltage = usMinVol * 10;

    if(enumPowerRole == _TYPE_C_POWER_SRC)
    {
        // The 1st PDO Cannot Be Argumented PDO (Must Be Fix PDO with 5V), PDO Power Must < Max Power
        if((ucPdoIndex >= 2) && (ucPdoIndex <= 7))
        {
            SET_TCPM_PD_SRC_PDO_TYPE(ucPortIndex, (ucPdoIndex - 1), _PD_3_PROGRAMMABLE_PDO);

            // Reset Peak Current Setting
            SET_TCPM_PD_SRC_CAP_PEAK(ucPortIndex, (ucPdoIndex - 1), _PD_PEAK_CUR_NONE);

            // ------------------ Max Voltage Setting ------------------
            // NOTE : Max Voltage Cannot > 21V
            if(usMaxVoltage <= 2100)
            {
                SET_TCPM_PD_SRC_CAP_VOL_MAX(ucPortIndex, (ucPdoIndex - 1), usMaxVoltage);
            }
            else
            {
                // Max Voltage Cannot > 21V
                SET_TCPM_PD_SRC_CAP_VOL_MAX(ucPortIndex, (ucPdoIndex - 1), 2100);
            }

            // ------------------ Min Voltage Setting ------------------
            // NOTE : Min Voltage Cannot > Max Voltage
            if(usMinVoltage <= usMaxVoltage)
            {
                // NOTE : Min Voltage Cannot < 3V
                if(usMinVoltage < 300)
                {
                    usMinVoltage = 300;
                }

                SET_TCPM_PD_SRC_CAP_VOL_MIN(ucPortIndex, (ucPdoIndex - 1), usMinVoltage);
            }
            else
            {
                // Min Voltage Cannot More Than Max Voltage
                SET_TCPM_PD_SRC_CAP_VOL_MIN(ucPortIndex, (ucPdoIndex - 1), usMaxVoltage);
            }

            // -------------------- Current Setting --------------------
            if(ucMaxCur <= 100)
            {
                SET_TCPM_PD_SRC_CAP_CUR(ucPortIndex, (ucPdoIndex - 1), (WORD)ucMaxCur);
            }
            else
            {
                // Current Cannot More Than 5A
                SET_TCPM_PD_SRC_CAP_CUR(ucPortIndex, (ucPdoIndex - 1), 100);
            }
        }
        else
        {
            if((WORD)(((DWORD)usMaxVol * ucMaxCur) / 20) > GET_TCPM_MAX_POWER(ucPortIndex))
            {
                DebugMessageTypeC("8. [TCPM] ==========X Set Fix PDO Error : PDO > Max Power", ucPdoIndex);
            }
            else
            {
                DebugMessageTypeC("8. [TCPM] ==========X Set Fix PDO Index Error", ucPdoIndex);
            }
        }
    }
    else if(enumPowerRole == _TYPE_C_POWER_SNK)
    {
        // Sink Capability
        if((ucPdoIndex >= 2) && (ucPdoIndex <= 7))
        {
            SET_TCPM_PD_SNK_PDO_TYPE(ucPortIndex, (ucPdoIndex - 1), _PD_3_PROGRAMMABLE_PDO);

            // ------------------ Max Voltage Setting ------------------
            // NOTE : Max Voltage Cannot > 21V
            if(usMaxVoltage <= 2100)
            {
                SET_TCPM_PD_SNK_CAP_VOL_MAX(ucPortIndex, (ucPdoIndex - 1), usMaxVoltage);
            }
            else
            {
                // Max Voltage Cannot > 21V
                SET_TCPM_PD_SNK_CAP_VOL_MAX(ucPortIndex, (ucPdoIndex - 1), 2100);
            }

            // ------------------ Min Voltage Setting ------------------
            // NOTE : Min Voltage Cannot > Max Voltage
            if(usMinVoltage <= usMaxVoltage)
            {
                // NOTE : Min Voltage Cannot < 3V
                if(usMinVoltage < 300)
                {
                    usMinVoltage = 300;
                }

                SET_TCPM_PD_SNK_CAP_VOL_MIN(ucPortIndex, (ucPdoIndex - 1), usMinVoltage);
            }
            else
            {
                // Min Voltage Cannot More Than Max Voltage
                SET_TCPM_PD_SNK_CAP_VOL_MIN(ucPortIndex, (ucPdoIndex - 1), usMaxVoltage);
            }

            // -------------------- Current Setting --------------------
            if(ucMaxCur <= 100)
            {
                SET_TCPM_PD_SNK_CAP_CUR(ucPortIndex, (ucPdoIndex - 1), (WORD)ucMaxCur);
            }
            else
            {
                // Current Cannot More Than 5A
                SET_TCPM_PD_SNK_CAP_CUR(ucPortIndex, (ucPdoIndex - 1), 100);
            }
        }
    }
}
#endif  // End of #if(_PORT_CTRL_EMB_PD3_PPS_SUPPORT == _ON)

//--------------------------------------------------
// Description  : Set TCPM EPR Src/Snk Cap Argumented PDO (PPS) Info
// Input Value  : enumTypeCPcbPort, enumPowerRole(_TYPE_C_POWER_SRC/SNK) / ucPdoIndex : 9~11 / usMinVol (100mV) / usMaxVol(100mV) / enumPeakCur
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmSetAvsPdo(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole, BYTE ucPdoIndex, WORD usMinVol, WORD usMaxVol, EnumTypeCPDPeakCurType enumPeakCur)
{
    BYTE ucPortIndex = ScalerTypeCTcpmGetPortIndex(enumTypeCPcbPort);

    // Convert Voltage from User 100mV to Fix PDO 10mV
    WORD usMaxVoltage = usMaxVol * 10;
    WORD usMinVoltage = usMinVol * 10;

    enumPeakCur = enumPeakCur;

    if(enumPowerRole == _TYPE_C_POWER_SRC)
    {
        // The 8th PDO Cannot Be AVS PDO (Must Be Fix PDO with 28V), PDO Power Must < Max Power
        if((ucPdoIndex >= 9) && (ucPdoIndex <= 11))
        {
            SET_TCPM_PD_SRC_PDO_TYPE(ucPortIndex, (ucPdoIndex - 1), _PD_3_1_ADJUSTABLE_PDO);

            // Set Peak Current
            SET_TCPM_PD_SRC_CAP_PEAK(ucPortIndex, (ucPdoIndex - 1), enumPeakCur);

            // ------------------ Max Voltage Setting ------------------
            // NOTE : Max Voltage Cannot > 48V
            if(usMaxVoltage <= 4800)
            {
                SET_TCPM_PD_SRC_CAP_VOL_MAX(ucPortIndex, (ucPdoIndex - 1), usMaxVoltage);
            }
            else
            {
                // Max Voltage Cannot > 28V
                SET_TCPM_PD_SRC_CAP_VOL_MAX(ucPortIndex, (ucPdoIndex - 1), 4800);
            }

            // ------------------ Min Voltage Setting ------------------
            // NOTE : Min Voltage Cannot > Max Voltage
            if(usMinVoltage <= usMaxVoltage)
            {
                // NOTE : Min Voltage Cannot < 15V
                if(usMinVoltage < 1500)
                {
                    usMinVoltage = 1500;
                }

                SET_TCPM_PD_SRC_CAP_VOL_MIN(ucPortIndex, (ucPdoIndex - 1), usMinVoltage);
            }
            else
            {
                // Min Voltage Cannot More Than Max Voltage
                SET_TCPM_PD_SRC_CAP_VOL_MIN(ucPortIndex, (ucPdoIndex - 1), usMaxVoltage);
            }
        }
        else
        {
            DebugMessageTypeC("8. [TCPM] ==========X Set AVS PDO Index Error", ucPdoIndex);
        }
    }
    else if(enumPowerRole == _TYPE_C_POWER_SNK)
    {
        // Set EPR Sink AVS PDO
    }
}

//--------------------------------------------------
// Description  : Get TCPM Src/Snk Capability Info want to Provide
// Input Value  : enumTypeCPcbPort, enumPowerRole(Src/Snk PDO), ucPdoIndex : 1~7
// Output Value : StructTypeCUserPDO (Voltage Unit = 100mV / Current = 10mA)
//--------------------------------------------------
StructTypeCUserPDO ScalerTypeCTcpmGetPdo(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole, BYTE ucPdoIndex)
{
    StructTypeCUserPDO stTypeCPdo = {_PD_FIX_SUPPLY_PDO, _PD_PEAK_CUR_NONE, 0x00, 0x00, 0x00};
    BYTE ucPortIndex = ScalerTypeCTcpmGetPortIndex(enumTypeCPcbPort);

    if(enumPowerRole == _TYPE_C_POWER_SRC)
    {
        if((ucPdoIndex >= 1) && (ucPdoIndex <= 11))
        {
            stTypeCPdo.enumPdoType = GET_TCPM_PD_SRC_PDO_TYPE(ucPortIndex, ucPdoIndex - 1);

            if(GET_TCPM_PD_SRC_PDO_TYPE(ucPortIndex, ucPdoIndex - 1) == _PD_FIX_SUPPLY_PDO)
            {
                stTypeCPdo.enumPeakCurrent = (EnumTypeCPDPeakCurType)GET_TCPM_PD_SRC_CAP_PEAK(ucPortIndex, ucPdoIndex - 1);

                // Get Voltage in Macro (Unit = 10mV), and Convert to 100mV
                stTypeCPdo.usMaxVoltage = (GET_TCPM_PD_SRC_CAP_VOL_MAX(ucPortIndex, ucPdoIndex - 1) / 10);
                stTypeCPdo.usMinVoltage = (GET_TCPM_PD_SRC_CAP_VOL_MIN(ucPortIndex, ucPdoIndex - 1) / 10);

                // Get Fix PDO Current in Macro (Unit = 10mA)
                stTypeCPdo.usMaxCurrent = GET_TCPM_PD_SRC_CAP_CUR(ucPortIndex, ucPdoIndex - 1);
            }
#if(_PORT_CTRL_EMB_PD3_PPS_SUPPORT == _ON)
            else if(GET_TCPM_PD_SRC_PDO_TYPE(ucPortIndex, ucPdoIndex - 1) == _PD_3_PROGRAMMABLE_PDO)
            {
                // Get Voltage in Macro (Unit = 10mV), and Convert to 100mV
                stTypeCPdo.usMaxVoltage = (GET_TCPM_PD_SRC_CAP_VOL_MAX(ucPortIndex, ucPdoIndex - 1) / 10);
                stTypeCPdo.usMinVoltage = (GET_TCPM_PD_SRC_CAP_VOL_MIN(ucPortIndex, ucPdoIndex - 1) / 10);

                // Get Programmable PDO Current in Macro (Unit = 50mA), and Convert to 10mA
                stTypeCPdo.usMaxCurrent = (GET_TCPM_PD_SRC_CAP_CUR(ucPortIndex, ucPdoIndex - 1) * 5);
            }
#endif  // End of #if(_PORT_CTRL_EMB_PD3_PPS_SUPPORT == _ON)
            else if(GET_TCPM_PD_SRC_PDO_TYPE(ucPortIndex, ucPdoIndex - 1) == _PD_3_1_ADJUSTABLE_PDO)
            {
                // Get Voltage in Macro (Unit = 10mV), and Convert to 100mV
                stTypeCPdo.usMaxVoltage = (GET_TCPM_PD_SRC_CAP_VOL_MAX(ucPortIndex, ucPdoIndex - 1) / 10);
                stTypeCPdo.usMinVoltage = (GET_TCPM_PD_SRC_CAP_VOL_MIN(ucPortIndex, ucPdoIndex - 1) / 10);
            }
        }
    }
    else if(enumPowerRole == _TYPE_C_POWER_SNK)
    {
        if((ucPdoIndex >= 1) && (ucPdoIndex <= GET_TCPM_PD_SPR_SNK_PDO_CNT(ucPortIndex)))
        {
            stTypeCPdo.enumPdoType = GET_TCPM_PD_SNK_PDO_TYPE(ucPortIndex, ucPdoIndex - 1);

            if(GET_TCPM_PD_SNK_PDO_TYPE(ucPortIndex, ucPdoIndex - 1) == _PD_FIX_SUPPLY_PDO)
            {
                // Get Voltage in Macro (Unit = 10mV), and Convert to 100mV
                stTypeCPdo.usMaxVoltage = (GET_TCPM_PD_SNK_CAP_VOL_MAX(ucPortIndex, ucPdoIndex - 1) / 10);
                stTypeCPdo.usMinVoltage = (GET_TCPM_PD_SNK_CAP_VOL_MIN(ucPortIndex, ucPdoIndex - 1) / 10);

                // Get Fix PDO Current in Macro (Unit = 10mA)
                stTypeCPdo.usMaxCurrent = GET_TCPM_PD_SNK_CAP_CUR(ucPortIndex, ucPdoIndex - 1);
            }
#if(_PORT_CTRL_EMB_PD3_PPS_SUPPORT == _ON)
            else if(GET_TCPM_PD_SNK_PDO_TYPE(ucPortIndex, ucPdoIndex - 1) == _PD_3_PROGRAMMABLE_PDO)
            {
                // Get Voltage in Macro (Unit = 10mV), and Convert to 100mV
                stTypeCPdo.usMaxVoltage = (GET_TCPM_PD_SNK_CAP_VOL_MAX(ucPortIndex, ucPdoIndex - 1) / 10);
                stTypeCPdo.usMinVoltage = (GET_TCPM_PD_SNK_CAP_VOL_MIN(ucPortIndex, ucPdoIndex - 1) / 10);

                // Get Programmable PDO Current in Macro (Unit = 50mA), and Convert to 10mA
                stTypeCPdo.usMaxCurrent = (GET_TCPM_PD_SNK_CAP_CUR(ucPortIndex, ucPdoIndex - 1) * 5);
            }
#endif  // End of #if(_PORT_CTRL_EMB_PD3_PPS_SUPPORT == _ON)
        }
    }

    return stTypeCPdo;
}

//--------------------------------------------------
// Description  : Get TCPM Number of Src/Snk Capability from Port Partner
// Input Value  : enumTypeCPcbPort, enumPowerRole : _TYPE_C_POWER_SRC / _TYPE_C_POWER_SNK
// Output Value : ucPdoCnt : Number of Src/Snk Capability
//--------------------------------------------------
BYTE ScalerTypeCTcpmGetPartnerPdoCnt(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole)
{
    BYTE ucPortIndex = ScalerTypeCTcpmGetPortIndex(enumTypeCPcbPort);
    BYTE ucPartnerPdoCnt = 0x00;

    if((enumPowerRole == _TYPE_C_POWER_SRC) && (GET_TCPM_PD_RCV_SRC_CAP(ucPortIndex) == _TRUE))
    {
        ucPartnerPdoCnt = GET_TCPM_PD_PARTNER_SRC_CAP_CNT(ucPortIndex);
    }
    else if((enumPowerRole == _TYPE_C_POWER_SNK) && (GET_TCPM_PD_RCV_SNK_CAP(ucPortIndex) == _TRUE))
    {
        ucPartnerPdoCnt = GET_TCPM_PD_PARTNER_SNK_CAP_CNT(ucPortIndex);
    }

    return ucPartnerPdoCnt;
}

//--------------------------------------------------
// Description  : Get TCPM Src/Snk Capability Info from Port Partner
// Input Value  : enumTypeCPcbPort, enumPowerRole(_TYPE_C_POWER_SRC/SNK) / ucPdoIndex : 1~7
// Output Value : StructTypeCUserPDO (Voltage Unit = 100mV / Current = 10mA)
//--------------------------------------------------
StructTypeCUserPDO ScalerTypeCTcpmGetPartnerPdo(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole, BYTE ucPdoIndex)
{
    StructTypeCUserPDO stTypeCPartnerPdo = {_PD_FIX_SUPPLY_PDO, _PD_PEAK_CUR_NONE, 0x00, 0x00, 0x00};
    BYTE ucPortIndex = ScalerTypeCTcpmGetPortIndex(enumTypeCPcbPort);

    if((enumPowerRole == _TYPE_C_POWER_SRC) && (GET_TCPM_PD_RCV_SRC_CAP(ucPortIndex) == _TRUE))
    {
        if((ucPdoIndex >= 1) && (ucPdoIndex <= GET_TCPM_PD_PARTNER_SRC_CAP_CNT(ucPortIndex)))
        {
            stTypeCPartnerPdo.enumPdoType = GET_TCPM_PD_PARTNER_SRC_CAP_TYPE(ucPortIndex, ucPdoIndex - 1);

            if(GET_TCPM_PD_PARTNER_SRC_CAP_TYPE(ucPortIndex, ucPdoIndex - 1) == _PD_FIX_SUPPLY_PDO)
            {
                stTypeCPartnerPdo.enumPeakCurrent = (EnumTypeCPDPeakCurType)GET_TCPM_PD_PARTNER_SRC_PEAK_CUR(ucPortIndex, ucPdoIndex - 1);
            }

            // Get Voltage in Macro (Unit = 10mV), and Convert to 100mV
            stTypeCPartnerPdo.usMaxVoltage = (GET_TCPM_PD_PARTNER_SRC_CAP_VOL_MAX(ucPortIndex, ucPdoIndex - 1) / 10);
            stTypeCPartnerPdo.usMinVoltage = (GET_TCPM_PD_PARTNER_SRC_CAP_VOL_MIN(ucPortIndex, ucPdoIndex - 1) / 10);

            // Get Current in Macro (Unit = 10mA)
            stTypeCPartnerPdo.usMaxCurrent = GET_TCPM_PD_PARTNER_SRC_CAP_CUR(ucPortIndex, ucPdoIndex - 1);
        }
    }
    else if((enumPowerRole == _TYPE_C_POWER_SNK) && (GET_TCPM_PD_RCV_SNK_CAP(ucPortIndex) == _TRUE))
    {
        if((ucPdoIndex >= 1) && (ucPdoIndex <= GET_TCPM_PD_PARTNER_SNK_CAP_CNT(ucPortIndex)))
        {
            stTypeCPartnerPdo.enumPdoType = GET_TCPM_PD_PARTNER_SNK_CAP_TYPE(ucPortIndex, ucPdoIndex - 1);

            // Get Voltage in Macro (Unit = 10mV), and Convert to 100mV
            stTypeCPartnerPdo.usMaxVoltage = (GET_TCPM_PD_PARTNER_SNK_CAP_VOL_MAX(ucPortIndex, ucPdoIndex - 1) / 10);
            stTypeCPartnerPdo.usMinVoltage = (GET_TCPM_PD_PARTNER_SNK_CAP_VOL_MIN(ucPortIndex, ucPdoIndex - 1) / 10);

            // Get Current in Macro (Unit = 10mA)
            stTypeCPartnerPdo.usMaxCurrent = GET_TCPM_PD_PARTNER_SNK_CAP_CUR(ucPortIndex, ucPdoIndex - 1);
        }
    }

    return stTypeCPartnerPdo;
}

//--------------------------------------------------
// Description  : Get TCPM Status Info from Port Partner
// Input Value  : enumTypeCPcbPort
// Output Value : StructTypeCStatusEvent
//--------------------------------------------------
StructTypeCStatusEvent ScalerTypeCTcpmGetPartnerStatusInfo(EnumTypeCPcbPort enumTypeCPcbPort)
{
    StructTypeCStatusEvent stTypeCPartnerStatusEvent = {0x00, 0x00};
    BYTE ucPortIndex = ScalerTypeCTcpmGetPortIndex(enumTypeCPcbPort);

    stTypeCPartnerStatusEvent.b3NewPowerState = GET_TCPM_PD_PARTNER_NEW_POWER_STATE(ucPortIndex);
    stTypeCPartnerStatusEvent.b3NewPSIndicator = GET_TCPM_PD_PARTNER_NEW_POWER_INDICATOR(ucPortIndex);

    return stTypeCPartnerStatusEvent;
}

//--------------------------------------------------
// Description  : Get TypeC 0 Alert Info from Port Partner
// Input Value  : enumTypeCPcbPort
// Output Value : StructTypeCAlertEvent
//--------------------------------------------------
StructTypeCAlertEvent ScalerTypeCTcpmGetPartnerAlertInfo(EnumTypeCPcbPort enumTypeCPcbPort)
{
    StructTypeCAlertEvent stTypeCPartnerAlertEvent = {_TYPE_C_TYPE_OF_ALERT_NONE, _TYPE_C_BAT_NONE, _TYPE_C_EXT_ALERT_EVENT_NONE};
    BYTE ucPortIndex = ScalerTypeCTcpmGetPortIndex(enumTypeCPcbPort);

    stTypeCPartnerAlertEvent.enumTypeOfAlert = GET_TCPM_PD_PARTNER_TYPE_OF_ALERT(ucPortIndex);
    stTypeCPartnerAlertEvent.enumBatStatus = GET_TCPM_PD_PARTNER_BAT_STATUS(ucPortIndex);
    stTypeCPartnerAlertEvent.enumExtAlertEvent = GET_TCPM_PD_PARTNER_EXT_ALERT_EVENT(ucPortIndex);

    return stTypeCPartnerAlertEvent;
}

//--------------------------------------------------
// Description  : Get TCPM PDO Info
// Input Value  : enumTypeCPcbPort, *pusVoltage (Unit: 10mV), *pusCurrent (Unit: 10mA)
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmGetPdoStatus(EnumTypeCPcbPort enumTypeCPcbPort, WORD *pusVoltage, WORD *pusCurrent)
{
    BYTE ucPortIndex = ScalerTypeCTcpmGetPortIndex(enumTypeCPcbPort);

    // Check Power Role & Power
    if(ScalerTypeCTcpmGetCcAttach(enumTypeCPcbPort) == _TYPE_C_ATTACH)
    {
        if(GET_TCPM_PD_EXPLICIT_CONTRACT(ucPortIndex) == _TRUE)
        {
            // CC Attached, PD Power Contract Established : Negotiated Voltage & Current
            *pusVoltage = GET_TCPM_PD_PDO_STATUS_VOL(ucPortIndex);

            *pusCurrent = GET_TCPM_PD_PDO_STATUS_CUR(ucPortIndex);
        }
        else
        {
            // CC Attached, No PD Power Contract : 5V / Current According to Rp Value
            // Voltage = 10mV * 500 = 5V
            *pusVoltage = 500;

            if(GET_TCPM_POWER_ROLE(ucPortIndex) == _PD_POWER_SRC)
            {
                *pusCurrent = GET_TCPM_CC_DEF_CUR(ucPortIndex);
            }
            else
            {
                if(ScalerTypeCTcpmCcDetResistor(ucPortIndex) == _TYPE_C_DET_RP_3P0A)
                {
                    // Sink Detect Rp-3.0A, Set Current to 3.0A
                    *pusCurrent = 300;
                }
                else if(ScalerTypeCTcpmCcDetResistor(ucPortIndex) == _TYPE_C_DET_RP_1P5A)
                {
                    // Sink Detect Rp-1.5A, Set Current to 1.5A
                    *pusCurrent = 150;
                }
                else
                {
                    // Sink Detect Rp-Default, Set Current to 500mA
                    *pusCurrent = 50;
                }
            }
        }
    }
    else
    {
        // Set Voltage & Current to 0
        *pusVoltage = 0;
        *pusCurrent = 0;
    }
}

//--------------------------------------------------
// Description  : Get TCPM Current Source PDO that Sink Request
// Input Value  : enumTypeCPcbPort
// Output Value : StructTypeCUserPDO (Voltage Unit = 100mV / Current = 10mA)
//--------------------------------------------------
StructTypeCUserPDO ScalerTypeCTcpmGetRequestedSrcPdo(EnumTypeCPcbPort enumTypeCPcbPort)
{
    StructTypeCUserPDO stTypeCSrcPdo = {_PD_FIX_SUPPLY_PDO, _PD_PEAK_CUR_NONE, 0x00, 0x00, 0x00};
    BYTE ucPortIndex = ScalerTypeCTcpmGetPortIndex(enumTypeCPcbPort);

    // Check if CC Attached and PD Power Contract Established
    if(ScalerTypeCTcpmGetCcAttach(enumTypeCPcbPort) == _TYPE_C_ATTACH)
    {
        if(GET_TCPM_PD_EXPLICIT_CONTRACT(ucPortIndex) == _TRUE)
        {
            if(GET_TCPM_POWER_ROLE(ucPortIndex) == _PD_POWER_SRC)
            {
                if((GET_TCPM_PD_PARTNER_OBJ_POS(ucPortIndex) > 0) && (GET_TCPM_PD_PARTNER_OBJ_POS(ucPortIndex) <= GET_TCPM_PD_SPR_SRC_PDO_CNT(ucPortIndex)))
                {
                    stTypeCSrcPdo.enumPdoType = GET_TCPM_PD_SRC_PDO_TYPE(ucPortIndex, GET_TCPM_PD_PARTNER_OBJ_POS(ucPortIndex) - 1);

                    if(GET_TCPM_PD_SRC_PDO_TYPE(ucPortIndex, GET_TCPM_PD_PARTNER_OBJ_POS(ucPortIndex) - 1) == _PD_FIX_SUPPLY_PDO)
                    {
                        stTypeCSrcPdo.enumPeakCurrent = (EnumTypeCPDPeakCurType)GET_TCPM_PD_SRC_CAP_PEAK(ucPortIndex, GET_TCPM_PD_PARTNER_OBJ_POS(ucPortIndex) - 1);

                        // Get Fix PDO Current in Macro (Unit = 10mA)
                        stTypeCSrcPdo.usMaxCurrent = GET_TCPM_PD_SRC_CAP_CUR(ucPortIndex, GET_TCPM_PD_PARTNER_OBJ_POS(ucPortIndex) - 1);
                    }
                    else if(GET_TCPM_PD_SRC_PDO_TYPE(ucPortIndex, GET_TCPM_PD_PARTNER_OBJ_POS(ucPortIndex) - 1) == _PD_3_PROGRAMMABLE_PDO)
                    {
                        // Get Programmable PDO Current in Macro (Unit = 50mA), and Convert to 10mA
                        stTypeCSrcPdo.usMaxCurrent = (GET_TCPM_PD_SRC_CAP_CUR(ucPortIndex, GET_TCPM_PD_PARTNER_OBJ_POS(ucPortIndex) - 1) * 5);
                    }

                    // Get Voltage in Macro (Unit = 10mV), and Convert to 100mV
                    stTypeCSrcPdo.usMaxVoltage = (GET_TCPM_PD_SRC_CAP_VOL_MAX(ucPortIndex, GET_TCPM_PD_PARTNER_OBJ_POS(ucPortIndex) - 1) / 10);
                    stTypeCSrcPdo.usMinVoltage = (GET_TCPM_PD_SRC_CAP_VOL_MIN(ucPortIndex, GET_TCPM_PD_PARTNER_OBJ_POS(ucPortIndex) - 1) / 10);
                }
            }
            else
            {
                if((GET_TCPM_PD_REQ_OBJ_POS(ucPortIndex) > 0) && (GET_TCPM_PD_REQ_OBJ_POS(ucPortIndex) <= GET_TCPM_PD_PARTNER_SRC_CAP_CNT(ucPortIndex)))
                {
                    stTypeCSrcPdo.enumPdoType = GET_TCPM_PD_PARTNER_SRC_CAP_TYPE(ucPortIndex, GET_TCPM_PD_REQ_OBJ_POS(ucPortIndex) - 1);

                    if(GET_TCPM_PD_PARTNER_SRC_CAP_TYPE(ucPortIndex, GET_TCPM_PD_REQ_OBJ_POS(ucPortIndex) - 1) == _PD_FIX_SUPPLY_PDO)
                    {
                        stTypeCSrcPdo.enumPeakCurrent = (EnumTypeCPDPeakCurType)GET_TCPM_PD_PARTNER_SRC_PEAK_CUR(ucPortIndex, GET_TCPM_PD_REQ_OBJ_POS(ucPortIndex) - 1);
                    }

                    // Get Voltage in Macro (Unit = 10mV), and Convert to 100mV
                    stTypeCSrcPdo.usMaxVoltage = (GET_TCPM_PD_PARTNER_SRC_CAP_VOL_MAX(ucPortIndex, GET_TCPM_PD_REQ_OBJ_POS(ucPortIndex) - 1) / 10);
                    stTypeCSrcPdo.usMinVoltage = (GET_TCPM_PD_PARTNER_SRC_CAP_VOL_MIN(ucPortIndex, GET_TCPM_PD_REQ_OBJ_POS(ucPortIndex) - 1) / 10);

                    // Get Current in Macro (Unit = 10mA)
                    stTypeCSrcPdo.usMaxCurrent = GET_TCPM_PD_PARTNER_SRC_CAP_CUR(ucPortIndex, GET_TCPM_PD_REQ_OBJ_POS(ucPortIndex) - 1);
                }
            }
        }
    }

    return stTypeCSrcPdo;
}

//--------------------------------------------------
// Description  : Set TCPM Default Src/Snk Cap
// Input Value  : enumTypeCPcbPort --> _D0_TYPE_C_PORT / _D1_TYPE_C_PORT...
//                enumPowerRole --> _TYPE_C_POWER_SRC / _TYPE_C_POWER_SNK
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmSetPdoByKernel(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole)
{
    BYTE ucPortIndex = ScalerTypeCTcpmGetPortIndex(enumTypeCPcbPort);

    // ------------------------- NOTE -------------------------
    // * Fix Supply PDO Please Use "ScalerTypeTcpmPdSetFixPdo"
    // * Argumented PDO (PPS) Please Use "ScalerTypeTcpmPdSetArgumentedPdo"
    // * 1st PDO Must Be "FIX SUPPLY" With Voltage 5V
    // * According to PD Spec : Max Voltage = 20V, Max Current = 5A
    // * If Set Current > 3A, and FW Cannot Get Cable 5A Cap, Current Will Be Auto Reduce to 3A
    // * For More Info, Ref to PD Spec 10.2
    // --------------------------------------------------------

    if(enumPowerRole == _TYPE_C_POWER_SRC)
    {
        // Set Type-C PDP (PD Power)[Unit = 0.1 W], PDO Power Cannot > PDP
        SET_TCPM_MAX_POWER(ucPortIndex, 25);

        // Set Total Number of SPR PDO
        SET_TCPM_PD_SPR_SRC_PDO_CNT(ucPortIndex, 1);

        // Set Total Number of EPR PDO
        SET_TCPM_PD_EPR_SRC_PDO_CNT(ucPortIndex, 0);

        // ----------------------- 1st PDO ------------------------
        // Index = 1 (1st PDO Must Be "FIX SUPPLY" With Voltage 5V)
        // PDO Type = Fix Supply PDO
        // Peak Current Only for Source Fix Supply PDO
        // Max/Min Voltage (Unit = 100mV) : 50 * 100mV = 5V
        // Max Current (Unit = 10mA)  : 50 *  10mA = 0.5A
        // --------------------------------------------------------
        ScalerTypeCTcpmSetFixPdo(enumTypeCPcbPort, _TYPE_C_POWER_SRC, 1, 50, 50, _PD_PEAK_CUR_NONE);

#if(_PORT_CTRL_EMB_PD3_PPS_SUPPORT == _ON)
        if(GET_TCPM_PD_PPS_SUPPORT(ucPortIndex) == _ON)
        {
            SET_TCPM_PD_SPR_SRC_PDO_CNT(ucPortIndex, GET_TCPM_PD_SPR_SRC_PDO_CNT(ucPortIndex) + 1);

            // ----------------------- 3rd PDO ------------------------
            // Index = 3
            // PDO Type = Programmable PDO (5V PPS PDO = 3.3V ~ 5.9V / 9V PPS PDO = 3.3V ~ 11V)
            // Max Voltage (Unit = 100mV) : 33 * 100mV = 3.3V
            // Min Voltage (Unit = 100mV) : 59 * 100mV = 5.9V
            // Max Current (Unit = 50mA)  : 60 *  50mA = 3A
            // --------------------------------------------------------
            ScalerTypeCTcpmSetPpsPdo(enumTypeCPcbPort, _TYPE_C_POWER_SRC, 3, 33, 59, 60);
        }
#endif
    }
    else if(enumPowerRole == _TYPE_C_POWER_SNK)
    {
        // Set Type-C Sink PDP [Unit = 0.1 W]
        SET_TCPM_PD_SNK_MIN_PDP(ucPortIndex, 25);
        SET_TCPM_PD_SNK_OPERATIONAL_PDP(ucPortIndex, 25);
        SET_TCPM_PD_SNK_MAX_PDP(ucPortIndex, 25);

        // Kernel Default Use 1 Sink PDO
        SET_TCPM_PD_SPR_SNK_PDO_CNT(ucPortIndex, 1);

        // Set Total Number of EPR PDO
        SET_TCPM_PD_EPR_SNK_PDO_CNT(ucPortIndex, 0);

        // --------------------- 1st Sink PDO ---------------------
        // Index = 1 (1st PDO Must Be "FIX SUPPLY" With Voltage 5V)
        // PDO Type = Fix Supply PDO
        // Peak Current Only for Source Fix Supply PDO
        // Max/Min Voltage (Unit = 100mV) : 50 * 100mV = 5V
        // Max Current (Unit = 10mA)  : 50 *  10mA = 500mA
        // --------------------------------------------------------
        ScalerTypeCTcpmSetFixPdo(enumTypeCPcbPort, _TYPE_C_POWER_SNK, 1, 50, 50, _PD_PEAK_CUR_NONE);

#if(_TYPE_C_POWER_SOURCE == _TYPE_C_VBUS_POWER_ONLY)
        // [MM1AE-3035] For Lecroy TEST.PD.PS.SNK.01 Issue, Vbus Powered Sink Must Set At Least 2 Sink PDOs
        SET_TCPM_PD_SPR_SNK_PDO_CNT(ucPortIndex, GET_TCPM_PD_SPR_SNK_PDO_CNT(ucPortIndex) + 1);

        // --------------------- 2nd Sink PDO ---------------------
        // Index = 2
        // PDO Type = Fix Supply PDO
        // Peak Current Only for Source Fix Supply PDO
        // Max/Min Voltage (Unit = 100mV) : 51 * 100mV = 5.1V
        // Max Current (Unit = 10mA)  : 50 *  10mA = 500mA
        // --------------------------------------------------------
        ScalerTypeCTcpmSetFixPdo(enumTypeCPcbPort, _TYPE_C_POWER_SNK, 2, 51, 50, _PD_PEAK_CUR_NONE);
#endif
    }
}

//--------------------------------------------------
// Description  : Set TCPM Sink Information
// Input Value  : enumTypeCPcbPort, stTypeCSnkInfo
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmSetSnkInfo(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCSnkInfo stTypeCSnkInfo)
{
    BYTE ucPortIndex = ScalerTypeCTcpmGetPortIndex(enumTypeCPcbPort);

    if(stTypeCSnkInfo.usSnkMinPDP <= 1000)
    {
        SET_TCPM_PD_SNK_MIN_PDP(ucPortIndex, stTypeCSnkInfo.usSnkMinPDP);
    }
    else
    {
        SET_TCPM_PD_SNK_MIN_PDP(ucPortIndex, 1000);
        DebugMessageTypeC("8. [TCPM] ==========X Sink Min PDP > 100W, Clamp to 100W", stTypeCSnkInfo.usSnkMinPDP);
    }

    if(stTypeCSnkInfo.usSnkOpePDP <= 1000)
    {
        SET_TCPM_PD_SNK_OPERATIONAL_PDP(ucPortIndex, stTypeCSnkInfo.usSnkOpePDP);
    }
    else
    {
        SET_TCPM_PD_SNK_OPERATIONAL_PDP(ucPortIndex, 1000);
        DebugMessageTypeC("8. [TCPM] ==========X Sink Operational PDP > 100W, Clamp to 100W", stTypeCSnkInfo.usSnkOpePDP);
    }

    if(stTypeCSnkInfo.usSnkMaxPDP <= 1000)
    {
        SET_TCPM_PD_SNK_MAX_PDP(ucPortIndex, stTypeCSnkInfo.usSnkMaxPDP);
    }
    else
    {
        SET_TCPM_PD_SNK_MAX_PDP(ucPortIndex, 1000);
        DebugMessageTypeC("8. [TCPM] ==========X Sink Max PDP > 100W, Clamp to 100W", stTypeCSnkInfo.usSnkMaxPDP);
    }
}

//--------------------------------------------------
// Description  : Set TCPM Initial Request RDO Info
// Input Value  : enumTypeCPcbPort, StructTypeCUserInitRDO(Initial Request Option, Target Voltage)
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmSetInitRdo(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCUserInitRDO stTypeCUserInitRdo)
{
    BYTE ucPortIndex = ScalerTypeCTcpmGetPortIndex(enumTypeCPcbPort);

    SET_TCPM_PD_REQ_TYPE(ucPortIndex, stTypeCUserInitRdo.enumReqType);

    switch(stTypeCUserInitRdo.enumTargetVolRDO)
    {
        case _TYPE_C_RDO_5V:

            SET_TCPM_PD_INIT_REQ_TARGET_VOL(ucPortIndex, 50);

            break;

        case _TYPE_C_RDO_5_1V:

            SET_TCPM_PD_INIT_REQ_TARGET_VOL(ucPortIndex, 51);

            break;

        case _TYPE_C_RDO_9V:

            SET_TCPM_PD_INIT_REQ_TARGET_VOL(ucPortIndex, 90);

            break;

        case _TYPE_C_RDO_12V:

            SET_TCPM_PD_INIT_REQ_TARGET_VOL(ucPortIndex, 120);

            break;

        case _TYPE_C_RDO_15V:

            SET_TCPM_PD_INIT_REQ_TARGET_VOL(ucPortIndex, 150);

            break;

        case _TYPE_C_RDO_20V:

            SET_TCPM_PD_INIT_REQ_TARGET_VOL(ucPortIndex, 200);

            break;

        case _TYPE_C_RDO_NO_TARGET:
        default:

            SET_TCPM_PD_INIT_REQ_TARGET_VOL(ucPortIndex, 0);

            break;
    }

    // Set Operating Current and Maximum Current to 0xFFFF, which Means Kernel will Request the Maximum Current of Partner's Src Cap PDO.
    SET_TCPM_PD_REQ_INFO_1(ucPortIndex, 0xFFFF);
    SET_TCPM_PD_REQ_INFO_2(ucPortIndex, 0xFFFF);
}

//--------------------------------------------------
// Description  : Set TCPM Request RDO Info
// Input Value  : enumTypeCPcbPort, StructTypeCUserRDO(Object Position, ReqInfo1, ReqInfo2, Cap Mismatch)
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmSetRdo(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCUserRDO stTypeCUserRdo)
{
    BYTE ucPortIndex = ScalerTypeCTcpmGetPortIndex(enumTypeCPcbPort);

    SET_TCPM_PD_REQ_OBJ_POS(ucPortIndex, stTypeCUserRdo.enumObjPos);
    SET_TCPM_PD_REQ_CAP_MIS(ucPortIndex, stTypeCUserRdo.b1CapMismatch);

    // Give Back Flag Define By Kernel
    SET_TCPM_PD_REQ_GIVE_BACK(ucPortIndex, _GIVE_BACK);

    if(GET_TCPM_PD_PARTNER_SRC_CAP_TYPE(ucPortIndex, GET_TCPM_PD_REQ_OBJ_POS(ucPortIndex) - 1) == _PD_FIX_SUPPLY_PDO)
    {
        // RDO[19:10] : Fix RDO (Op. Cur in 10mA)
        SET_TCPM_PD_REQ_INFO_1(ucPortIndex, (stTypeCUserRdo.usReqInfo1) & 0x3FF);

        // RDO[9:0] : Fix RDO (Max. Cur in 10mA)
        SET_TCPM_PD_REQ_INFO_2(ucPortIndex, (stTypeCUserRdo.usReqInfo2) & 0x3FF);
    }
    else
    {
        // RDO[19:9] : PPS RDO (Vol in 20mV)
        SET_TCPM_PD_REQ_INFO_1(ucPortIndex, (stTypeCUserRdo.usReqInfo1) & 0x7FF);

        // RDO[6:0] : PPS RDO (Op. Cur in 50mA)
        SET_TCPM_PD_REQ_INFO_2(ucPortIndex, (stTypeCUserRdo.usReqInfo2) & 0x7F);
    }

    // Set Request Type to Customized RDO
    SET_TCPM_PD_REQ_TYPE(ucPortIndex, _TYPE_C_REQ_CUSTOMIZED_RDO);
}

//--------------------------------------------------
// Description  : Set TCPM Unconstrained Power Status
// Input Value  : enumTypeCUnconstrainPowerExist : _TYPE_C_UNCONSTRAIN_POWER_NOT_EXIST/ _TYPE_C_UNCONSTRAIN_POWER_EXIST
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmSetUnconstrainedPow(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCUnconstrainPowerExist enumTypeCUnconstrainPowerExist)
{
    BYTE ucPortIndex = ScalerTypeCTcpmGetPortIndex(enumTypeCPcbPort);

    if(enumTypeCUnconstrainPowerExist == _TYPE_C_UNCONSTRAIN_POWER_EXIST)
    {
        SET_TCPM_PD_UNCONSTRAIN_POWER(ucPortIndex, _TRUE);
    }
    else
    {
        SET_TCPM_PD_UNCONSTRAIN_POWER(ucPortIndex, _FALSE);
    }
}

//--------------------------------------------------
// Description  : Set TCPM System Event
// Input Value  : enumTypeCPcbPort, enumPdSysEvent
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmSetPdSystemEvent(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPDSysEvent enumPdSysEvent)
{
    BYTE ucPortIndex = ScalerTypeCTcpmGetPortIndex(enumTypeCPcbPort);

    if((GET_TCPM_PD_SYS_EVENT(ucPortIndex) & _PD_SYS_EVENT_ERROR_RECOVERY) == _PD_SYS_EVENT_ERROR_RECOVERY)
    {
        SET_TCPM_CC_ERROR_RECOVERY(ucPortIndex);
    }
    else
    {
        SET_TCPM_PD_SYS_EVENT(ucPortIndex, enumPdSysEvent);
    }

    // Update Port Controller Event to inform System / User of Specific Events Occurred
    if((GET_TCPM_PD_SYS_EVENT(ucPortIndex) & _PD_SYS_EVENT_POWER_OCP) == _PD_SYS_EVENT_POWER_OCP)
    {
        SET_TCPM_PD_PORT_CTRL_EVENT(ucPortIndex, _PD_PORT_CTRL_EVENT_POWER_OCP);
    }

    if((GET_TCPM_PD_SYS_EVENT(ucPortIndex) & _PD_SYS_EVENT_POWER_OVP) == _PD_SYS_EVENT_POWER_OVP)
    {
        SET_TCPM_PD_PORT_CTRL_EVENT(ucPortIndex, _PD_PORT_CTRL_EVENT_POWER_OVP);
    }

    if((GET_TCPM_PD_SYS_EVENT(ucPortIndex) & _PD_SYS_EVENT_POWER_UVP) == _PD_SYS_EVENT_POWER_UVP)
    {
        SET_TCPM_PD_PORT_CTRL_EVENT(ucPortIndex, _PD_PORT_CTRL_EVENT_POWER_UVP);
    }

    if((GET_TCPM_PD_SYS_EVENT(ucPortIndex) & _PD_SYS_EVENT_VCONN_OCP) == _PD_SYS_EVENT_VCONN_OCP)
    {
        SET_TCPM_PD_PORT_CTRL_EVENT(ucPortIndex, _PD_PORT_CTRL_EVENT_VCONN_OCP);
    }
}

//--------------------------------------------------
// Description  : Get TCPM Port Controller Event
// Input Value  : enumTypeCPcbPort
// Output Value : EnumTypeCPDPortCtrlEvent
//--------------------------------------------------
EnumTypeCPDPortCtrlEvent ScalerTypeCTcpmGetPortCtrlEvent(EnumTypeCPcbPort enumTypeCPcbPort)
{
    BYTE ucPortIndex = ScalerTypeCTcpmGetPortIndex(enumTypeCPcbPort);

    return GET_TCPM_PD_PORT_CTRL_EVENT(ucPortIndex);
}

//--------------------------------------------------
// Description  : Clear TCPM Port Controller Event
// Input Value  : enumTypeCPcbPort, enumPdPortCtrlEvent
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmClrPortCtrlEvent(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPDPortCtrlEvent enumPdPortCtrlEvent)
{
    BYTE ucPortIndex = ScalerTypeCTcpmGetPortIndex(enumTypeCPcbPort);

    CLR_TCPM_PD_PORT_CTRL_EVENT(ucPortIndex, enumPdPortCtrlEvent);
}

//--------------------------------------------------
// Description  : Type C TCPM Set Vbus Protect Info
// Input Value  : enumTypeCPcbPort, ucPdoIndex, StructTypeCUserProtectInfo
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmSetVbusProtectInfo(EnumTypeCPcbPort enumTypeCPcbPort, BYTE ucPdoIndex, StructTypeCVbusProtectInfo stTypeCVbusProtectInfo)
{
    BYTE ucPortIndex = ScalerTypeCTcpmGetPortIndex(enumTypeCPcbPort);

    // Set OCP Setting
    SET_TCPM_OCP_RATIO(ucPortIndex, (ucPdoIndex - 1), stTypeCVbusProtectInfo.ucOcpCurRatio);

#if(_TYPE_C_PMIC_SUPPORT == _ON)
    if(GET_TCPM_PMIC_SUPPORT(ucPortIndex) == _ON)
    {
        // Set OCP Debounce Time for Protection Judgment before protection trigger
        SET_TCPM_PMIC_OCP_JUDGE_DEBOUNCE(ucPortIndex, stTypeCVbusProtectInfo.ucOcpDebounce);
    }
#endif

#if(_PORT_CTRL_TCPM_OVP_UVP_SUPPORT == _ON)
    // Set Vbus Debounce Time for Protection Judgment before protection trigger
    SET_TCPM_OVP_JUDGE_DEBOUNCE(ucPortIndex, stTypeCVbusProtectInfo.ucOvpDebounce);
    SET_TCPM_UVP_JUDGE_DEBOUNCE(ucPortIndex, stTypeCVbusProtectInfo.ucUvpDebounce);
#endif
}

//--------------------------------------------------
// Description  : Type C TCPM Configuration Update
// Input Value  : enumInputPort, enumMultiFunc, enumPinAssignmentCap
// Output Value : _SUCCESS / _FAIL
//--------------------------------------------------
bit ScalerTypeCTcpmUpdateConfig(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCMultiFuncStatus enumMultiFunc, EnumTypeCPinCfgCapType enumPinAssignmentCap)
{
    BYTE ucPortIndex = ScalerTypeCTcpmGetPortIndex(enumTypeCPcbPort);

    // 1. Set Pin Assignment Capabiliy
    SET_TCPM_PD_DPAM_PIN_ASSIGNMENT_CAP(ucPortIndex, enumPinAssignmentCap);

    // 2. Set Multi Function Bit
    if(enumMultiFunc == _TYPE_C_MULTI_FUNC_PREFER)
    {
        SET_TCPM_PD_DPAM_MULTI_FUNC(ucPortIndex);
    }
    else
    {
        CLR_TCPM_PD_DPAM_MULTI_FUNC(ucPortIndex);
    }

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : Ask TCPM to Wait for DP Config Update
// Input Value  : enumTypeCPcbPort
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmWaitDpConfigUpdate(EnumTypeCPcbPort enumTypeCPcbPort)
{
    BYTE ucPortIndex = ScalerTypeCTcpmGetPortIndex(enumTypeCPcbPort);

    // Set Wait DP Config Flag to trigger Alt Mode Not Ready, Clr when rcv DP Config
    SET_TCPM_PD_DPAM_WAIT_CONFIG(ucPortIndex);
}

//--------------------------------------------------
// Description  : Type C TCPM Power Switch Process
// Input Value  : enumTypeCPcbPort, enumPowerAction
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmPowerSwitch(EnumTypeCPcbPort enumTypeCPcbPort, EnumPowerAction enumPowerAction)
{
    BYTE ucPortIndex = ScalerTypeCTcpmGetPortIndex(enumTypeCPcbPort);

    ScalerTypeCTcpmCcPowerSwitch(ucPortIndex, enumPowerAction);

    ScalerTypeCTcpmPdPowerSwitch(ucPortIndex, enumPowerAction);
}

//--------------------------------------------------
// Description  : Type C TCPM Clock Setting (Always Use IOSC = 28MHz (Scaler) / 108M (Translator))
// Input Value  : ucClockSel
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmClockSetting(BYTE ucClockSel)
{
    if(ucClockSel == _IOSC_CLK)
    {
#if(_HW_TCPM_0_SUPPORT == _ON)
        // Disable [0xFA00] [7] iicm_sw_rstn
        ScalerSetBit(PFA_00_I2CM_CR0, ~_BIT7, 0x00);

        // Disable [0xFA20] [7] tcpc_0_alert_det_en & [0xFA90] [7] tcpc_1_alert_det_en
        ScalerSetBit(PFA_20_TCPC_0_ALERT_DETECT, ~_BIT7, 0x00);
        ScalerSetBit(PFA_90_TCPC_1_ALERT_DETECT, ~_BIT7, 0x00);

        // Switch [0xFA10] [6:5] tcpm_sys_clk_sel to IOSC
        ScalerSetBit(PFA_10_TCPM_MUX, ~(_BIT6 | _BIT5), 0x00);

#if(_TCPM_0_IIC_SPEED == _HW_IIC_HIGH_SPEED_400K)
        // Set [0xFA0A] [5:0] fd10 = 0x01
        ScalerSetBit(PFA_0A_I2CM_CCR, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x01);

        // Set [0xFA07] slpc = 0x12
        ScalerSetByte(PFA_07_I2CM_STR3, 0x12);

        // Set [0xFA06] shpc = 0x0D
        ScalerSetByte(PFA_06_I2CM_STR2, 0x0D);

        // Set [0xFA04] [6:4] i2cmd = 0x00
        ScalerSetBit(PFA_04_I2CM_STR0, ~(_BIT6 | _BIT5 | _BIT4), 0x00);

        // Set [0xFA05] sta_sugpio_c = 0x08
        ScalerSetByte(PFA_05_I2CM_STR1, 0x08);

        // Set [0xFA01] tor = 0x2A
        ScalerSetByte(PFA_01_I2CM_CR1, 0x2A);

        // Set [0xFA0B] ftpc = 0x04
        ScalerSetByte(PFA_0B_I2CM_STR4, 0x04);

        // Set [0xFA0C] thd_sta_c = 0x08
        ScalerSetByte(PFA_0C_I2CM_STR5, 0x08);

        // Set [0xFA14] i2c_gap = 0x12
        ScalerSetByte(PFA_14_I2C_GAP, 0x12);
#elif(_TCPM_0_IIC_SPEED == _HW_IIC_HIGH_SPEED_1M)
        // Set [0xFA0A] [5:0] : fd10 = 0x00
        ScalerSetBit(PFA_0A_I2CM_CCR, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

        // Set [0xFA07] slpc = 0xE
        ScalerSetByte(PFA_07_I2CM_STR3, 0x0E);

        // Set [0xFA06] shpc = 0x0A
        ScalerSetByte(PFA_06_I2CM_STR2, 0x0A);

        // Set [0xFA04] [6:4] : i2cmd = 0x00
        ScalerSetBit(PFA_04_I2CM_STR0, ~(_BIT6 | _BIT5 | _BIT4), 0x00);

        // Set [0xFA05] sta_sugpio_c = 0x07
        ScalerSetByte(PFA_05_I2CM_STR1, 0x07);

        // Set [0xFA01] tor = 0x24
        ScalerSetByte(PFA_01_I2CM_CR1, 0x24);

        // Set [0xFA0B] ftpc = 0x03
        ScalerSetByte(PFA_0B_I2CM_STR4, 0x03);

        // Set [0xFA0C] thd_sta_c = 0x07
        ScalerSetByte(PFA_0C_I2CM_STR5, 0x07);

        // Set [0xFA14] i2c_gap = 0x0E
        ScalerSetByte(PFA_14_I2C_GAP, 0x0E);
#endif

        // Enable [0xFA20] [7] tcpc_0_alert_det_en & [0xFA90] [7] tcpc_1_alert_det_en
        ScalerSetBit(PFA_20_TCPC_0_ALERT_DETECT, ~_BIT7, _BIT7);
        ScalerSetBit(PFA_90_TCPC_1_ALERT_DETECT, ~_BIT7, _BIT7);

        // Enable [0xFA00] [7] iicm_sw_rstn & [0] tore
        ScalerSetBit(PFA_00_I2CM_CR0, ~(_BIT7 | _BIT0), (_BIT7 | _BIT0));
#endif

#if(_HW_TCPM_1_SUPPORT == _ON)
        // Disable [0xFB00] [7] iicm_sw_rstn
        ScalerSetBit(PFB_00_I2CM_CR0, ~_BIT7, 0x00);

        // Disable [0xFB20] [7] tcpc_0_alert_det_en & [0xFB90] [7] tcpc_1_alert_det_en
        ScalerSetBit(PFB_20_TCPC_0_ALERT_DETECT, ~_BIT7, 0x00);
        ScalerSetBit(PFB_90_TCPC_1_ALERT_DETECT, ~_BIT7, 0x00);

        // Switch [0xFB10] [6:5] tcpm_sys_clk_sel to IOSC
        ScalerSetBit(PFB_10_TCPM_MUX, ~(_BIT6 | _BIT5), 0x00);

#if(_TCPM_1_IIC_SPEED == _HW_IIC_HIGH_SPEED_400K)
        // Set [0xFB0A] [5:0] fd10 = 0x01
        ScalerSetBit(PFB_0A_I2CM_CCR, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x01);

        // Set [0xFB07] slpc = 0x12
        ScalerSetByte(PFB_07_I2CM_STR3, 0x12);

        // Set [0xFB06] shpc = 0x0D
        ScalerSetByte(PFB_06_I2CM_STR2, 0x0D);

        // Set [0xFB04] [6:4] i2cmd = 0x00
        ScalerSetBit(PFB_04_I2CM_STR0, ~(_BIT6 | _BIT5 | _BIT4), 0x00);

        // Set [0xFB05] sta_sugpio_c = 0x08
        ScalerSetByte(PFB_05_I2CM_STR1, 0x08);

        // Set [0xFB01] tor = 0x2A
        ScalerSetByte(PFB_01_I2CM_CR1, 0x2A);

        // Set [0xFB0B] ftpc = 0x04
        ScalerSetByte(PFB_0B_I2CM_STR4, 0x04);

        // Set [0xFB0C] thd_sta_c = 0x08
        ScalerSetByte(PFB_0C_I2CM_STR5, 0x08);

        // Set [0xFB14] i2c_gap = 0x12
        ScalerSetByte(PFB_14_I2C_GAP, 0x12);
#elif(_TCPM_1_IIC_SPEED == _HW_IIC_HIGH_SPEED_1M)
        // Set [0xFB0A] [5:0] fd10 = 0x00
        ScalerSetBit(PFB_0A_I2CM_CCR, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

        // Set [0xFB07] slpc = 0xE
        ScalerSetByte(PFB_07_I2CM_STR3, 0x0E);

        // Set [0xFB06] shpc = 0x0A
        ScalerSetByte(PFB_06_I2CM_STR2, 0x0A);

        // Set [0xFB04] [6:4] i2cmd = 0x00
        ScalerSetBit(PFB_04_I2CM_STR0, ~(_BIT6 | _BIT5 | _BIT4), 0x00);

        // Set [0xFB05] sta_sugpio_c = 0x07
        ScalerSetByte(PFB_05_I2CM_STR1, 0x07);

        // Set [0xFB01] tor = 0x24
        ScalerSetByte(PFB_01_I2CM_CR1, 0x24);

        // Set [0xFB0B] ftpc = 0x03
        ScalerSetByte(PFB_0B_I2CM_STR4, 0x03);

        // Set [0xFB0C] thd_sta_c = 0x07
        ScalerSetByte(PFB_0C_I2CM_STR5, 0x07);

        // Set [0xFB14] i2c_gap = 0x0E
        ScalerSetByte(PFB_14_I2C_GAP, 0x0E);
#endif

        // Enable [0xFB20] [7] tcpc_0_alert_det_en & [0xFB90] [7] tcpc_1_alert_det_en
        ScalerSetBit(PFB_20_TCPC_0_ALERT_DETECT, ~_BIT7, _BIT7);
        ScalerSetBit(PFB_90_TCPC_1_ALERT_DETECT, ~_BIT7, _BIT7);

        // Enable [0xFB00 [7] iicm_sw_rstn & [0] tore
        ScalerSetBit(PFB_00_I2CM_CR0, ~(_BIT7 | _BIT0), (_BIT7 | _BIT0));
#endif
    }
}

//--------------------------------------------------
// Description  : Control TCPM Power Off/On
// Input Value  : enumTypeCPcbPort, enumPowerControlStatus
// Output Value : Control Power Result (_SUCCESS / _FAIL)
//--------------------------------------------------
bit ScalerTypeCTcpmPowerControl(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerControlStatus enumPowerControlStatus)
{
    EnumTypeCAttachStatus enumAttachStatus = _TYPE_C_UNATTACH;
    BYTE ucIndex = 0;
    bit bControlResult = _FAIL;
    enumTypeCPcbPort = enumTypeCPcbPort;

    if(enumPowerControlStatus == _TYPE_C_POWER_OFF)
    {
        // Judge All TCPM Ports CC Attach Status
        for(ucIndex = 0; ucIndex < _TCPM_PORT_VALID; ++ucIndex)
        {
            enumAttachStatus |= ScalerTypeCTcpmGetCcAttach(g_penumTypeCTcpmPort[ucIndex]);
        }

        if(enumAttachStatus == _TYPE_C_ATTACH)
        {
            // Set All TCPM Ports Disconnect Before Power Cut
            for(ucIndex = 0; ucIndex < _TCPM_PORT_VALID; ++ucIndex)
            {
                ScalerTypeCTcpmCcFunctionControl(g_penumTypeCTcpmPort[ucIndex], _TYPE_C_CC_FUNCTION_DISABLE);
            }
        }
        else
        {
            // Power Off TCPM
            ScalerPowerDomainClockGatingControl(_CLOCK_GATING_GROUP_TYPE_C_TCPM, _CLOCK_GATING_ON);

            bControlResult = _SUCCESS;
        }
    }
    else if(enumPowerControlStatus == _TYPE_C_POWER_ON)
    {
        // Power On TCPM
        ScalerPowerDomainClockGatingControl(_CLOCK_GATING_GROUP_TYPE_C_TCPM, _CLOCK_GATING_OFF);

        bControlResult = _SUCCESS;
    }

    return bControlResult;
}

//--------------------------------------------------
// Description  : Set Error Recovery Flag to Trigger TCPM Reconnect
// Input Value  : enumTypeCPcbPort
// Output Value : _SUCCESS / _FAIL
//--------------------------------------------------
bit ScalerTypeCTcpmReconnect(EnumTypeCPcbPort enumTypeCPcbPort)
{
    BYTE ucPortIndex = ScalerTypeCTcpmGetPortIndex(enumTypeCPcbPort);

    SET_TCPM_CC_ERROR_RECOVERY(ucPortIndex);

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : Set TCPM Function Support Option
// Input Value  : enumTypeCPcbPort, enumFunctionSupport
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmSetFunctionSupport(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCFunctionSupport enumFunctionSupport)
{
    BYTE ucPortIndex = ScalerTypeCTcpmGetPortIndex(enumTypeCPcbPort);

    ScalerTypeCTcpmCcSetFunctionSupport(ucPortIndex, enumFunctionSupport);
    ScalerTypeCTcpmPdSetFunctionSupport(ucPortIndex, enumFunctionSupport);
}

//--------------------------------------------------
// Description  : Get TCPM PD DP Status Info
// Input Value  : enumTypeCPcbPort
// Output Value : StructTypeCDpStatusInfo (enumPartnerDpConnectStatus / b1PartnerMultiFunctionBit...)
//--------------------------------------------------
StructTypeCDpStatusInfo ScalerTypeCTcpmGetDpStatusInfo(EnumTypeCPcbPort enumTypeCPcbPort)
{
#if(_TYPE_C_DPAM_VERSION < _DPAM_VERSION_2_1)
    StructTypeCDpStatusInfo stDpStatusInfo = {_PD_DP_CONNECT_NONE, 0x00, 0x00, 0x00, 0x00, 0x00, _PD_HPD_NONE};
#else
    StructTypeCDpStatusInfo stDpStatusInfo = {_PD_DP_CONNECT_NONE, 0x00, 0x00, 0x00, 0x00, 0x00, _PD_HPD_NONE, 0x00};
#endif

    BYTE ucPortIndex = ScalerTypeCTcpmGetPortIndex(enumTypeCPcbPort);

    stDpStatusInfo.enumPartnerDpConnectStatus = GET_TCPM_PD_PARTNER_DPAM_CONNECT_STATUS(ucPortIndex);
    stDpStatusInfo.b1PartnerDpPowerLow = GET_TCPM_PD_PARTNER_DPAM_POWER_LOW(ucPortIndex);
    stDpStatusInfo.b1PartnerDpFunctionEnabled = GET_TCPM_PD_PARTNER_DPAM_FUNCTION_ENABLE(ucPortIndex);
    stDpStatusInfo.b1PartnerMultiFunctionBit = GET_TCPM_PD_PARTNER_DPAM_MULTI_FUNCTION(ucPortIndex);
    stDpStatusInfo.b1PartnerUsbConfigRequest = GET_TCPM_PD_PARTNER_DPAM_USB_CONFIG_REQUEST(ucPortIndex);
    stDpStatusInfo.b1PartnerDpAltModeExit = GET_TCPM_PD_PARTNER_DPAM_EXIT_REQ(ucPortIndex);
    stDpStatusInfo.enumPartnerHpdType = GET_TCPM_PD_PARTNER_HPD_TYPE(ucPortIndex);
#if(_TYPE_C_DPAM_VERSION >= _DPAM_VERSION_2_1)
    stDpStatusInfo.b1PartnerNoDpAltSuspend = GET_TCPM_PD_PARTNER_DPAM_NO_SUSPEND(ucPortIndex);
#endif

    return stDpStatusInfo;
}

//--------------------------------------------------
// Description  : Set TCPM Status Event
// Input Value  : enumTypeCPcbPort, stTypeCStatusEvent
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmSetStatusEvent(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCStatusEvent stTypeCStatusEvent)
{
    BYTE ucPortIndex = ScalerTypeCTcpmGetPortIndex(enumTypeCPcbPort);

    SET_TCPM_PD_NEW_POWER_STATE(ucPortIndex, stTypeCStatusEvent.b3NewPowerState);
    SET_TCPM_PD_NEW_POWER_INDICATOR(ucPortIndex, stTypeCStatusEvent.b3NewPSIndicator);
}

//--------------------------------------------------
// Description  : Set TCPM Alert Event
// Input Value  : enumTypeCPcbPort, stTypeCAlertEvent
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmSetAlertEvent(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCAlertEvent stTypeCAlertEvent)
{
    BYTE ucPortIndex = ScalerTypeCTcpmGetPortIndex(enumTypeCPcbPort);

    SET_TCPM_PD_TYPE_OF_ALERT(ucPortIndex, stTypeCAlertEvent.enumTypeOfAlert);
    SET_TCPM_PD_BAT_STATUS(ucPortIndex, stTypeCAlertEvent.enumBatStatus);
    SET_TCPM_PD_EXT_ALERT_EVENT(ucPortIndex, stTypeCAlertEvent.enumExtAlertEvent);
}

//--------------------------------------------------
// Description  : Return Tcpm CC Attached Status
// Input Value  : enumTypeCPcbPort
// Output Value : CC Attach Status(_TYPE_C_ATTACH / _TYPE_C_UNATTACH)
//--------------------------------------------------
EnumTypeCAttachStatus ScalerTypeCTcpmGetCcAttach(EnumTypeCPcbPort enumTypeCPcbPort)
{
    BYTE ucPortIndex = ScalerTypeCTcpmGetPortIndex(enumTypeCPcbPort);
    EnumTypeCAttachStatus enumCcAttach = _TYPE_C_UNATTACH;

    enumCcAttach = (GET_TCPM_CC_ATTACHED(ucPortIndex) == _TRUE ? _TYPE_C_ATTACH : _TYPE_C_UNATTACH);

    return enumCcAttach;
}

//--------------------------------------------------
// Description  : Return TCPM DP Alt Mode Ready Status
// Input Value  : enumTypeCPcbPort
// Output Value : DP Alt Mode Ready Status (_TYPE_C_ALT_MODE_READY / _TYPE_C_ALT_MODE_NOT_READY)
//--------------------------------------------------
EnumTypeCAltModeStatus ScalerTypeCTcpmGetAltModeReady(EnumTypeCPcbPort enumTypeCPcbPort)
{
    BYTE ucPortIndex = ScalerTypeCTcpmGetPortIndex(enumTypeCPcbPort);
    EnumTypeCAltModeStatus enumAltModeReady = _TYPE_C_ALT_MODE_NOT_READY;

#if(_PORT_CTRL_EMB_DP_RX_SUPPORT == _ON)
    if(GET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex) == _TYPE_C_DP_RX)
    {
        if(GET_TCPM_PD_SNK_REQUEST_SWAP_TO_SRC(ucPortIndex) == _TRUE)
        {
            if((GET_TCPM_PD_DPAM_CONFIG(ucPortIndex) == _PD_DP_CONFIG) && (GET_TCPM_PD_DPAM_WAIT_CONFIG(ucPortIndex) == _FALSE) && ((GET_TCPM_CC_PORT_ROLE(ucPortIndex) != _TYPE_C_PORT_DRP) || (GET_TCPM_PD_PARTNER_DRP(ucPortIndex) == _FALSE) || (GET_TCPM_POWER_ROLE(ucPortIndex) == _PD_POWER_SRC) || (GET_TCPM_PD_UNCONSTRAIN_POWER(ucPortIndex) == _FALSE) || (GET_TCPM_PD_PRS_REJECT(ucPortIndex) == _TRUE)))
            {
                enumAltModeReady = _TYPE_C_ALT_MODE_READY;
            }
        }
        else
        {
            if((GET_TCPM_PD_DPAM_CONFIG(ucPortIndex) == _PD_DP_CONFIG) && (GET_TCPM_PD_DPAM_WAIT_CONFIG(ucPortIndex) == _FALSE))
            {
                enumAltModeReady = _TYPE_C_ALT_MODE_READY;
            }
        }
    }
#endif

#if(_PORT_CTRL_EMB_DP_TX_SUPPORT == _ON)
    if(GET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex) == _TYPE_C_DP_TX)
    {
        if(GET_TCPM_POWER_ROLE(ucPortIndex) == _PD_POWER_SRC)
        {
            if(GET_TCPM_PD_SRC_REQUEST_SWAP_TO_SNK(ucPortIndex) == _TRUE)
            {
                if((GET_TCPM_PD_DPAM_CONFIG(ucPortIndex) == _PD_DP_CONFIG) && ((GET_TCPM_CC_PORT_ROLE(ucPortIndex) != _TYPE_C_PORT_DRP) || (GET_TCPM_PD_UNCONSTRAIN_POWER(ucPortIndex) == _TRUE) || ((GET_TCPM_PD_GET_SRC_CAP_SENT(ucPortIndex) == _TRUE) && ((GET_TCPM_PD_PARTNER_DRP(ucPortIndex) == _FALSE) || (GET_TCPM_PD_PARTNER_SRC_CAP_CHECK_RESULT(ucPortIndex) == _PD_SRC_CAP_INVALID) || (GET_TCPM_PD_PRS_REJECT(ucPortIndex) == _TRUE)))))
                {
                    enumAltModeReady = _TYPE_C_ALT_MODE_READY;
                }
            }
            else
            {
                if(GET_TCPM_PD_DPAM_CONFIG(ucPortIndex) == _PD_DP_CONFIG)
                {
                    enumAltModeReady = _TYPE_C_ALT_MODE_READY;
                }
            }
        }
        else
        {
            if(GET_TCPM_PD_SNK_REQUEST_SWAP_TO_SRC(ucPortIndex) == _TRUE)
            {
                if((GET_TCPM_PD_DPAM_CONFIG(ucPortIndex) == _PD_DP_CONFIG) && ((GET_TCPM_CC_PORT_ROLE(ucPortIndex) != _TYPE_C_PORT_DRP) || (GET_TCPM_PD_PARTNER_DRP(ucPortIndex) == _FALSE) || (GET_TCPM_PD_UNCONSTRAIN_POWER(ucPortIndex) == _FALSE) || (GET_TCPM_PD_PRS_REJECT(ucPortIndex) == _TRUE)))
                {
                    enumAltModeReady = _TYPE_C_ALT_MODE_READY;
                }
            }
            else
            {
                if(GET_TCPM_PD_DPAM_CONFIG(ucPortIndex) == _PD_DP_CONFIG)
                {
                    enumAltModeReady = _TYPE_C_ALT_MODE_READY;
                }
            }
        }
    }
#endif

    return enumAltModeReady;
}

//--------------------------------------------------
// Description  : Return Tcpm CC Attach Orientation
// Input Value  : enumTypeCPcbPort
// Output Value : Orientation (_TYPE_C_ORIENTATION_UNFLIP / _TYPE_C_ORIENTATION_FLIP)
//--------------------------------------------------
EnumTypeCOrientation ScalerTypeCTcpmGetOrientation(EnumTypeCPcbPort enumTypeCPcbPort)
{
    BYTE ucPortIndex = ScalerTypeCTcpmGetPortIndex(enumTypeCPcbPort);
    EnumTypeCOrientation enumOrientation = _TYPE_C_ORIENTATION_UNFLIP;

    enumOrientation = GET_TCPM_ORIENTATION(ucPortIndex);

    return enumOrientation;
}

//--------------------------------------------------
// Description  : Get TCPM Data Role
// Input Value  : enumTypeCPcbPort
// Output Value : EnumTypeCDataRole (_TYPE_C_UFP_U / _TYPE_C_DFP_U)
//--------------------------------------------------
EnumTypeCDataRole ScalerTypeCTcpmGetDataRole(EnumTypeCPcbPort enumTypeCPcbPort)
{
    BYTE ucPortIndex = ScalerTypeCTcpmGetPortIndex(enumTypeCPcbPort);

    if(GET_TCPM_DATA_ROLE(ucPortIndex) == _PD_DATA_DFP)
    {
        return _TYPE_C_DFP_U;
    }
    else
    {
        return _TYPE_C_UFP_U;
    }
}

//--------------------------------------------------
// Description  : Get Tcpm PD Power Role
// Input Value  : enumTypeCPcbPort
// Output Value : PD Power Role (_TYPE_C_POWER_SNK / _TYPE_C_POWER_SRC)
//--------------------------------------------------
EnumTypeCPowerRole ScalerTypeCTcpmGetPowerRole(EnumTypeCPcbPort enumTypeCPcbPort)
{
    BYTE ucPortIndex = ScalerTypeCTcpmGetPortIndex(enumTypeCPcbPort);

    if(GET_TCPM_POWER_ROLE(ucPortIndex) == _PD_POWER_SRC)
    {
        return _TYPE_C_POWER_SRC;
    }
    else
    {
        return _TYPE_C_POWER_SNK;
    }
}

//--------------------------------------------------
// Description  : Get TCPM Explicit Contract
// Input Value  : enumTypeCPcbPort
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerTypeCTcpmGetExplicitContract(EnumTypeCPcbPort enumTypeCPcbPort)
{
    BYTE ucPortIndex = ScalerTypeCTcpmGetPortIndex(enumTypeCPcbPort);

    return GET_TCPM_PD_EXPLICIT_CONTRACT(ucPortIndex);
}

//--------------------------------------------------
// Description  : Get TCPM Pin Assignment
// Input Value  : enumTypeCPcbPort, penumPinAssignment
// Output Value : _SUCCESS / _FAIL
//--------------------------------------------------
bit ScalerTypeCTcpmGetPinAssignment(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPinCfgType *penumPinAssignment)
{
    BYTE ucPortIndex = ScalerTypeCTcpmGetPortIndex(enumTypeCPcbPort);

    *penumPinAssignment = GET_TCPM_PD_DPAM_PIN_ASSIGNMENT(ucPortIndex);

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : Get TCPM Multi Function Change Process Done Result(Pin Assignment C <=> Pin Assignment D)
// Input Value  : enumTypeCPcbPort
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerTypeCTcpmGetMultiFunctionChangeDone(EnumTypeCPcbPort enumTypeCPcbPort)
{
    BYTE ucPortIndex = ScalerTypeCTcpmGetPortIndex(enumTypeCPcbPort);

    if(GET_TCPM_PD_DPAM_MULTI_FUNCTION_CHANGE_DONE(ucPortIndex) == _TRUE)
    {
        CLR_TCPM_PD_DPAM_MULTI_FUNCTION_CHANGE_DONE(ucPortIndex);

        return _TRUE;
    }
    else
    {
        return _FALSE;
    }
}

//--------------------------------------------------
// Description  : Get TCPM TypeC Cable PD Capability
// Input Value  : enumTypeCPcbPort
// Output Value : _TYPE_C_CABLE_PD_CAP_UNCONFIRMED / _TYPE_C_CABLE_NON_PD_CAPABLE / _TYPE_C_CABLE_DISCOVER_ID_ACK_RECEIVED
//--------------------------------------------------
EnumTypeCCablePdCapability ScalerTypeCTcpmGetCablePdCapability(EnumTypeCPcbPort enumTypeCPcbPort)
{
    BYTE ucPortIndex = ScalerTypeCTcpmGetPortIndex(enumTypeCPcbPort);

    return GET_TCPM_PD_CBL_PD_CAPABILITY(ucPortIndex);
}

//--------------------------------------------------
// Description  : Get TCPM TypeC Product Type when in UFP Data Role
// Input Value  : enumTypeCPcbPort
// Output Value : _TYPE_C_UFP_PRODUCT_TYPE_UNDEFINED / _TYPE_C_UFP_PRODUCT_TYPE_HUB / _TYPE_C_UFP_PRODUCT_TYPE_PERIPHERAL
//--------------------------------------------------
EnumTypeCUFPProductType ScalerTypeCTcpmGetUFPProductType(EnumTypeCPcbPort enumTypeCPcbPort)
{
    BYTE ucPortIndex = ScalerTypeCTcpmGetPortIndex(enumTypeCPcbPort);

    return GET_TCPM_PD_UFP_PRODUCT_TYPE(ucPortIndex);
}

//--------------------------------------------------
// Description  : Get TCPM TypeC Product Type when in DFP Data Role
// Input Value  : enumTypeCPcbPort
// Output Value : _TYPE_C_DFP_PRODUCT_TYPE_UNDEFINED / _TYPE_C_DFP_PRODUCT_TYPE_HUB / _TYPE_C_DFP_PRODUCT_TYPE_HOST / _TYPE_C_DFP_PRODUCT_TYPE_BRICK
//--------------------------------------------------
EnumTypeCDFPProductType ScalerTypeCTcpmGetDFPProductType(EnumTypeCPcbPort enumTypeCPcbPort)
{
    BYTE ucPortIndex = ScalerTypeCTcpmGetPortIndex(enumTypeCPcbPort);

    return GET_TCPM_PD_DFP_PRODUCT_TYPE(ucPortIndex);
}

//--------------------------------------------------
// Description  : Get TCPM TypeC Cable Max Current
// Input Value  : enumTypeCPcbPort
// Output Value : return Cable Max Current (Unit: 10mA)
//--------------------------------------------------
WORD ScalerTypeCTcpmGetCableMaxCurrent(EnumTypeCPcbPort enumTypeCPcbPort)
{
    BYTE ucPortIndex = ScalerTypeCTcpmGetPortIndex(enumTypeCPcbPort);

    return GET_TCPM_PD_CBL_MAX_CUR(ucPortIndex);
}

//--------------------------------------------------
// Description  : Return TCPM Cable Info For DPCD
// Input Value  : enumTypeCPcbPort
// Output Value : StructTypeCCableInfoForDpcd
//--------------------------------------------------
StructTypeCCableInfoForDpcd ScalerTypeCTcpmGetCableInfoForDpcd(EnumTypeCPcbPort enumTypeCPcbPort)
{
    BYTE ucPortIndex = ScalerTypeCTcpmGetPortIndex(enumTypeCPcbPort);
    StructTypeCCableInfoForDpcd stTypeCCableInfoForDpcd = {_PD_CBL_COMPONENT_PASSIVE, _PD_CBL_MAX_DP_RATE_UNCONFIRMED, _FALSE};

#if(_TYPE_C_DPAM_VERSION >= _DPAM_VERSION_2_1)
    // DPCD Table Bit[5:3]: Cable Type
    stTypeCCableInfoForDpcd.enumTypeCCableActiveComponent = GET_TCPM_PD_CBL_ACTIVE_COMPONENT(ucPortIndex);

    // DPCD Table Bit[2]: Cable UHBR13.5 Support
    stTypeCCableInfoForDpcd.b1CableUhbr13p5Support = GET_TCPM_PD_CBL_UHBR13P5_SUPPORT(ucPortIndex);

    // DPCD Table Bit[1:0]: Cable UHBR10_20 Capability
    stTypeCCableInfoForDpcd.enumTypeCCableMaxDpRate = GET_TCPM_PD_CBL_MAX_DP_RATE(ucPortIndex);
#endif

    return stTypeCCableInfoForDpcd;
}

//--------------------------------------------------
// Description  : Type C TCPM Default Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmDefaultSetting(void)
{
    BYTE ucPortIndex = 0;

#if(_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM)
    ucPortIndex = ScalerTypeCTcpmGetPortIndex(_D0_TYPE_C_PORT);

    // TCPM PCB Related Define Setting
    SET_TCPM_USB_TYPE(ucPortIndex, _D0_USB_HUB_TYPE);
    SET_TCPM_USB_SPEED(ucPortIndex, _D0_USB_SPEED);
    SET_TCPM_USB_ROLE(ucPortIndex, _D0_TYPE_C_EMB_USB_ROLE);
    SET_TCPM_CONNECTOR_TYPE(ucPortIndex, _D0_TYPE_C_EMB_CONNECTOR_TYPE);
    SET_TCPM_TCPC_TYPE(ucPortIndex, _D0_TYPE_C_TCPM_TCPC_TYPE);
    SET_TCPM_TCPC_SLAVE_ADDR(ucPortIndex, _D0_TYPE_C_TCPM_TCPC_I2C_SLAVE_ADDR);
    SET_TCPM_CC_RP_DEF_VALUE(ucPortIndex, _D0_TYPE_C_EMB_SRC_DEF_CUR);
    SET_TCPM_PD_PPS_SUPPORT(ucPortIndex, _D0_TYPE_C_EMB_PD3_PPS_SUPPORT);
    SET_TCPM_PD_EPR_SRC_CAPABLE(ucPortIndex, _D0_TYPE_C_EMB_PD3_1_EPR_SUPPORT);
    SET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex, _D0_TYPE_C_EMB_PD_BEHAVIOR_TYPE);
    SET_TCPM_PD_DPAM_SUPPORT(ucPortIndex, _D0_TYPE_C_EMB_DP_ALT_MODE_SUPPORT);
    SET_TCPM_PD_MODAL_OPERATION_SUPPORT(ucPortIndex, _D0_TYPE_C_MODAL_OPERATION_SUPPORT);

    ScalerTypeCTcpmSetPRSwapOption(ucPortIndex);
    ScalerTypeCTcpmSetDRSwapOption(ucPortIndex);

#if(_HW_TCPM_SUPPORT == _ON)
    // TCPM Slave Addr Setting
    ScalerSetByte(PFA_21_TCPC_0_SLV_ADDR + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), GET_TCPM_TCPC_SLAVE_ADDR(ucPortIndex));
#endif

#if(_TYPE_C_PMIC_SUPPORT == _ON)
    SET_TCPM_PMIC_SUPPORT(ucPortIndex, (_D0_TYPE_C_PMIC_TYPE != _PMIC_NONE));
    SET_TCPM_PMIC_OCP_PROTECT_METHOD(ucPortIndex, _D0_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD);

#if(_TYPE_C_PMIC_FW_POLLING_OCP_SUPPORT == _ON)
    SET_TCPM_PMIC_FW_OCP_CURRENT_VALUE(ucPortIndex, _D0_TYPE_C_PMIC_FW_OCP_CURRENT_VALUE);
    SET_TCPM_PMIC_FW_OCP_DELAY_SHUTDOWN(ucPortIndex, _D0_TYPE_C_PMIC_FW_OCP_DELAY_SHUTDOWN);
#endif
#endif

#if(_PORT_CTRL_TCPM_OCP_PROTECT_BY_TCPC == _ON)
    SET_TCPM_OCP_PROTECT_BY_TCPC(ucPortIndex, _D0_TYPE_C_TCPM_OCP_PROTECT_BY_TCPC);
#endif

#if(_PORT_CTRL_TCPM_OVP_UVP_SUPPORT == _ON)
    SET_TCPM_OVP_UVP_SUPPORT(ucPortIndex, _D0_TYPE_C_TCPM_OVP_UVP_SUPPORT);
    SET_TCPM_OVP_THRESHOLD(ucPortIndex, _D0_TYPE_C_TCPM_OVP_THRESHOLD);
    SET_TCPM_UVP_THRESHOLD(ucPortIndex, _D0_TYPE_C_TCPM_UVP_THRESHOLD);
#endif

    // TCPM Initial State Setting
    SET_TCPM_STATE(ucPortIndex, _TCPM_WAIT_TCPC_ON);

    // Do Initial Proc if TCPC Already Wake Up
    ScalerTypeCTcpmInitialProc(_D0_TYPE_C_PORT);
#endif

#if(_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM)
    ucPortIndex = ScalerTypeCTcpmGetPortIndex(_D1_TYPE_C_PORT);

    // TCPM PCB Related Define Setting
    SET_TCPM_USB_TYPE(ucPortIndex, _D1_USB_HUB_TYPE);
    SET_TCPM_USB_SPEED(ucPortIndex, _D1_USB_SPEED);
    SET_TCPM_USB_ROLE(ucPortIndex, _D1_TYPE_C_EMB_USB_ROLE);
    SET_TCPM_CONNECTOR_TYPE(ucPortIndex, _D1_TYPE_C_EMB_CONNECTOR_TYPE);
    SET_TCPM_TCPC_TYPE(ucPortIndex, _D1_TYPE_C_TCPM_TCPC_TYPE);
    SET_TCPM_TCPC_SLAVE_ADDR(ucPortIndex, _D1_TYPE_C_TCPM_TCPC_I2C_SLAVE_ADDR);
    SET_TCPM_CC_RP_DEF_VALUE(ucPortIndex, _D1_TYPE_C_EMB_SRC_DEF_CUR);
    SET_TCPM_PD_PPS_SUPPORT(ucPortIndex, _D1_TYPE_C_EMB_PD3_PPS_SUPPORT);
    SET_TCPM_PD_EPR_SRC_CAPABLE(ucPortIndex, _D1_TYPE_C_EMB_PD3_1_EPR_SUPPORT);
    SET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex, _D1_TYPE_C_EMB_PD_BEHAVIOR_TYPE);
    SET_TCPM_PD_DPAM_SUPPORT(ucPortIndex, _D1_TYPE_C_EMB_DP_ALT_MODE_SUPPORT);
    SET_TCPM_PD_MODAL_OPERATION_SUPPORT(ucPortIndex, _D1_TYPE_C_MODAL_OPERATION_SUPPORT);

    ScalerTypeCTcpmSetPRSwapOption(ucPortIndex);
    ScalerTypeCTcpmSetDRSwapOption(ucPortIndex);

#if(_HW_TCPM_SUPPORT == _ON)
    // TCPM Slave Addr Setting
    ScalerSetByte(PFA_21_TCPC_0_SLV_ADDR + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), GET_TCPM_TCPC_SLAVE_ADDR(ucPortIndex));
#endif

#if(_TYPE_C_PMIC_SUPPORT == _ON)
    SET_TCPM_PMIC_SUPPORT(ucPortIndex, (_D1_TYPE_C_PMIC_TYPE != _PMIC_NONE));
    SET_TCPM_PMIC_OCP_PROTECT_METHOD(ucPortIndex, _D1_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD);

#if(_TYPE_C_PMIC_FW_POLLING_OCP_SUPPORT == _ON)
    SET_TCPM_PMIC_FW_OCP_CURRENT_VALUE(ucPortIndex, _D1_TYPE_C_PMIC_FW_OCP_CURRENT_VALUE);
    SET_TCPM_PMIC_FW_OCP_DELAY_SHUTDOWN(ucPortIndex, _D1_TYPE_C_PMIC_FW_OCP_DELAY_SHUTDOWN);
#endif
#endif

#if(_PORT_CTRL_TCPM_OCP_PROTECT_BY_TCPC == _ON)
    SET_TCPM_OCP_PROTECT_BY_TCPC(ucPortIndex, _D1_TYPE_C_TCPM_OCP_PROTECT_BY_TCPC);
#endif

#if(_PORT_CTRL_TCPM_OVP_UVP_SUPPORT == _ON)
    SET_TCPM_OVP_UVP_SUPPORT(ucPortIndex, _D1_TYPE_C_TCPM_OVP_UVP_SUPPORT);
    SET_TCPM_OVP_THRESHOLD(ucPortIndex, _D1_TYPE_C_TCPM_OVP_THRESHOLD);
    SET_TCPM_UVP_THRESHOLD(ucPortIndex, _D1_TYPE_C_TCPM_UVP_THRESHOLD);
#endif

    // TCPM Initial State Setting
    SET_TCPM_STATE(ucPortIndex, _TCPM_WAIT_TCPC_ON);

    // Do Initial Proc if TCPC Already Wake Up
    ScalerTypeCTcpmInitialProc(_D1_TYPE_C_PORT);
#endif

#if(_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM)
    ucPortIndex = ScalerTypeCTcpmGetPortIndex(_D2_TYPE_C_PORT);

    // TCPM PCB Related Define Setting
    SET_TCPM_USB_TYPE(ucPortIndex, _D2_USB_HUB_TYPE);
    SET_TCPM_USB_SPEED(ucPortIndex, _D2_USB_SPEED);
    SET_TCPM_USB_ROLE(ucPortIndex, _D2_TYPE_C_EMB_USB_ROLE);
    SET_TCPM_CONNECTOR_TYPE(ucPortIndex, _D2_TYPE_C_EMB_CONNECTOR_TYPE);
    SET_TCPM_TCPC_TYPE(ucPortIndex, _D2_TYPE_C_TCPM_TCPC_TYPE);
    SET_TCPM_TCPC_SLAVE_ADDR(ucPortIndex, _D2_TYPE_C_TCPM_TCPC_I2C_SLAVE_ADDR);
    SET_TCPM_CC_RP_DEF_VALUE(ucPortIndex, _D2_TYPE_C_EMB_SRC_DEF_CUR);
    SET_TCPM_PD_PPS_SUPPORT(ucPortIndex, _D2_TYPE_C_EMB_PD3_PPS_SUPPORT);
    SET_TCPM_PD_EPR_SRC_CAPABLE(ucPortIndex, _D2_TYPE_C_EMB_PD3_1_EPR_SUPPORT);
    SET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex, _D2_TYPE_C_EMB_PD_BEHAVIOR_TYPE);
    SET_TCPM_PD_DPAM_SUPPORT(ucPortIndex, _D2_TYPE_C_EMB_DP_ALT_MODE_SUPPORT);
    SET_TCPM_PD_MODAL_OPERATION_SUPPORT(ucPortIndex, _D2_TYPE_C_MODAL_OPERATION_SUPPORT);

    ScalerTypeCTcpmSetPRSwapOption(ucPortIndex);
    ScalerTypeCTcpmSetDRSwapOption(ucPortIndex);

#if(_HW_TCPM_SUPPORT == _ON)
    // TCPM Slave Addr Setting
    ScalerSetByte(PFA_21_TCPC_0_SLV_ADDR + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), GET_TCPM_TCPC_SLAVE_ADDR(ucPortIndex));
#endif

#if(_TYPE_C_PMIC_SUPPORT == _ON)
    SET_TCPM_PMIC_SUPPORT(ucPortIndex, (_D2_TYPE_C_PMIC_TYPE != _PMIC_NONE));
    SET_TCPM_PMIC_OCP_PROTECT_METHOD(ucPortIndex, _D2_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD);

#if(_TYPE_C_PMIC_FW_POLLING_OCP_SUPPORT == _ON)
    SET_TCPM_PMIC_FW_OCP_CURRENT_VALUE(ucPortIndex, _D2_TYPE_C_PMIC_FW_OCP_CURRENT_VALUE);
    SET_TCPM_PMIC_FW_OCP_DELAY_SHUTDOWN(ucPortIndex, _D2_TYPE_C_PMIC_FW_OCP_DELAY_SHUTDOWN);
#endif
#endif

#if(_PORT_CTRL_TCPM_OCP_PROTECT_BY_TCPC == _ON)
    SET_TCPM_OCP_PROTECT_BY_TCPC(ucPortIndex, _D2_TYPE_C_TCPM_OCP_PROTECT_BY_TCPC);
#endif

#if(_PORT_CTRL_TCPM_OVP_UVP_SUPPORT == _ON)
    SET_TCPM_OVP_UVP_SUPPORT(ucPortIndex, _D2_TYPE_C_TCPM_OVP_UVP_SUPPORT);
    SET_TCPM_OVP_THRESHOLD(ucPortIndex, _D2_TYPE_C_TCPM_OVP_THRESHOLD);
    SET_TCPM_UVP_THRESHOLD(ucPortIndex, _D2_TYPE_C_TCPM_UVP_THRESHOLD);
#endif

    // TCPM Initial State Setting
    SET_TCPM_STATE(ucPortIndex, _TCPM_WAIT_TCPC_ON);

    // Do Initial Proc if TCPC Already Wake Up
    ScalerTypeCTcpmInitialProc(_D2_TYPE_C_PORT);
#endif

#if(_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM)
    ucPortIndex = ScalerTypeCTcpmGetPortIndex(_P0_TYPE_C_PORT);

    // TCPM PCB Related Define Setting
    SET_TCPM_USB_TYPE(ucPortIndex, _P0_USB_HUB_TYPE);
    SET_TCPM_USB_SPEED(ucPortIndex, _P0_USB_SPEED);
    SET_TCPM_USB_ROLE(ucPortIndex, _P0_TYPE_C_EMB_USB_ROLE);
    SET_TCPM_CONNECTOR_TYPE(ucPortIndex, _P0_TYPE_C_EMB_CONNECTOR_TYPE);
    SET_TCPM_TCPC_TYPE(ucPortIndex, _P0_TYPE_C_TCPM_TCPC_TYPE);
    SET_TCPM_TCPC_SLAVE_ADDR(ucPortIndex, _P0_TYPE_C_TCPM_TCPC_I2C_SLAVE_ADDR);
    SET_TCPM_CC_RP_DEF_VALUE(ucPortIndex, _P0_TYPE_C_EMB_SRC_DEF_CUR);
    SET_TCPM_PD_PPS_SUPPORT(ucPortIndex, _P0_TYPE_C_EMB_PD3_PPS_SUPPORT);
    SET_TCPM_PD_EPR_SRC_CAPABLE(ucPortIndex, _P0_TYPE_C_EMB_PD3_1_EPR_SUPPORT);
    SET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex, _P0_TYPE_C_EMB_PD_BEHAVIOR_TYPE);
    SET_TCPM_PD_DPAM_SUPPORT(ucPortIndex, _P0_TYPE_C_EMB_DP_ALT_MODE_SUPPORT);
    SET_TCPM_PD_MODAL_OPERATION_SUPPORT(ucPortIndex, _P0_TYPE_C_MODAL_OPERATION_SUPPORT);

    ScalerTypeCTcpmSetPRSwapOption(ucPortIndex);
    ScalerTypeCTcpmSetDRSwapOption(ucPortIndex);

#if(_HW_TCPM_SUPPORT == _ON)
    // TCPM Slave Addr Setting
    ScalerSetByte(PFA_21_TCPC_0_SLV_ADDR + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), GET_TCPM_TCPC_SLAVE_ADDR(ucPortIndex));
#endif

#if(_TYPE_C_PMIC_SUPPORT == _ON)
    SET_TCPM_PMIC_SUPPORT(ucPortIndex, (_P0_TYPE_C_PMIC_TYPE != _PMIC_NONE));
    SET_TCPM_PMIC_OCP_PROTECT_METHOD(ucPortIndex, _P0_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD);

#if(_TYPE_C_PMIC_FW_POLLING_OCP_SUPPORT == _ON)
    SET_TCPM_PMIC_FW_OCP_CURRENT_VALUE(ucPortIndex, _P0_TYPE_C_PMIC_FW_OCP_CURRENT_VALUE);
    SET_TCPM_PMIC_FW_OCP_DELAY_SHUTDOWN(ucPortIndex, _P0_TYPE_C_PMIC_FW_OCP_DELAY_SHUTDOWN);
#endif
#endif

#if(_PORT_CTRL_TCPM_OCP_PROTECT_BY_TCPC == _ON)
    SET_TCPM_OCP_PROTECT_BY_TCPC(ucPortIndex, _P0_TYPE_C_TCPM_OCP_PROTECT_BY_TCPC);
#endif

#if(_PORT_CTRL_TCPM_OVP_UVP_SUPPORT == _ON)
    SET_TCPM_OVP_UVP_SUPPORT(ucPortIndex, _P0_TYPE_C_TCPM_OVP_UVP_SUPPORT);
    SET_TCPM_OVP_THRESHOLD(ucPortIndex, _P0_TYPE_C_TCPM_OVP_THRESHOLD);
    SET_TCPM_UVP_THRESHOLD(ucPortIndex, _P0_TYPE_C_TCPM_UVP_THRESHOLD);
#endif

    // TCPM Initial State Setting
    SET_TCPM_STATE(ucPortIndex, _TCPM_WAIT_TCPC_ON);

    // Do Initial Proc if TCPC Already Wake Up
    ScalerTypeCTcpmInitialProc(_P0_TYPE_C_PORT);
#endif

#if(_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM)
    ucPortIndex = ScalerTypeCTcpmGetPortIndex(_P1_TYPE_C_PORT);

    // TCPM PCB Related Define Setting
    SET_TCPM_USB_TYPE(ucPortIndex, _P1_USB_HUB_TYPE);
    SET_TCPM_USB_SPEED(ucPortIndex, _P1_USB_SPEED);
    SET_TCPM_USB_ROLE(ucPortIndex, _P1_TYPE_C_EMB_USB_ROLE);
    SET_TCPM_CONNECTOR_TYPE(ucPortIndex, _P1_TYPE_C_EMB_CONNECTOR_TYPE);
    SET_TCPM_TCPC_TYPE(ucPortIndex, _P1_TYPE_C_TCPM_TCPC_TYPE);
    SET_TCPM_TCPC_SLAVE_ADDR(ucPortIndex, _P1_TYPE_C_TCPM_TCPC_I2C_SLAVE_ADDR);
    SET_TCPM_CC_RP_DEF_VALUE(ucPortIndex, _P1_TYPE_C_EMB_SRC_DEF_CUR);
    SET_TCPM_PD_PPS_SUPPORT(ucPortIndex, _P1_TYPE_C_EMB_PD3_PPS_SUPPORT);
    SET_TCPM_PD_EPR_SRC_CAPABLE(ucPortIndex, _P1_TYPE_C_EMB_PD3_1_EPR_SUPPORT);
    SET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex, _P1_TYPE_C_EMB_PD_BEHAVIOR_TYPE);
    SET_TCPM_PD_DPAM_SUPPORT(ucPortIndex, _P1_TYPE_C_EMB_DP_ALT_MODE_SUPPORT);
    SET_TCPM_PD_MODAL_OPERATION_SUPPORT(ucPortIndex, _P1_TYPE_C_MODAL_OPERATION_SUPPORT);

    ScalerTypeCTcpmSetPRSwapOption(ucPortIndex);
    ScalerTypeCTcpmSetDRSwapOption(ucPortIndex);

#if(_HW_TCPM_SUPPORT == _ON)
    // TCPM Slave Addr Setting
    ScalerSetByte(PFA_21_TCPC_0_SLV_ADDR + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), GET_TCPM_TCPC_SLAVE_ADDR(ucPortIndex));
#endif

#if(_TYPE_C_PMIC_SUPPORT == _ON)
    SET_TCPM_PMIC_SUPPORT(ucPortIndex, (_P1_TYPE_C_PMIC_TYPE != _PMIC_NONE));
    SET_TCPM_PMIC_OCP_PROTECT_METHOD(ucPortIndex, _P1_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD);

#if(_TYPE_C_PMIC_FW_POLLING_OCP_SUPPORT == _ON)
    SET_TCPM_PMIC_FW_OCP_CURRENT_VALUE(ucPortIndex, _P1_TYPE_C_PMIC_FW_OCP_CURRENT_VALUE);
    SET_TCPM_PMIC_FW_OCP_DELAY_SHUTDOWN(ucPortIndex, _P1_TYPE_C_PMIC_FW_OCP_DELAY_SHUTDOWN);
#endif
#endif

#if(_PORT_CTRL_TCPM_OCP_PROTECT_BY_TCPC == _ON)
    SET_TCPM_OCP_PROTECT_BY_TCPC(ucPortIndex, _P1_TYPE_C_TCPM_OCP_PROTECT_BY_TCPC);
#endif

#if(_PORT_CTRL_TCPM_OVP_UVP_SUPPORT == _ON)
    SET_TCPM_OVP_UVP_SUPPORT(ucPortIndex, _P1_TYPE_C_TCPM_OVP_UVP_SUPPORT);
    SET_TCPM_OVP_THRESHOLD(ucPortIndex, _P1_TYPE_C_TCPM_OVP_THRESHOLD);
    SET_TCPM_UVP_THRESHOLD(ucPortIndex, _P1_TYPE_C_TCPM_UVP_THRESHOLD);
#endif

    // TCPM Initial State Setting
    SET_TCPM_STATE(ucPortIndex, _TCPM_WAIT_TCPC_ON);

    // Do Initial Proc if TCPC Already Wake Up
    ScalerTypeCTcpmInitialProc(_P1_TYPE_C_PORT);
#endif

#if(_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM)
    ucPortIndex = ScalerTypeCTcpmGetPortIndex(_P2_TYPE_C_PORT);

    // TCPM PCB Related Define Setting
    SET_TCPM_USB_TYPE(ucPortIndex, _P2_USB_HUB_TYPE);
    SET_TCPM_USB_SPEED(ucPortIndex, _P2_USB_SPEED);
    SET_TCPM_USB_ROLE(ucPortIndex, _P2_TYPE_C_EMB_USB_ROLE);
    SET_TCPM_CONNECTOR_TYPE(ucPortIndex, _P2_TYPE_C_EMB_CONNECTOR_TYPE);
    SET_TCPM_TCPC_TYPE(ucPortIndex, _P2_TYPE_C_TCPM_TCPC_TYPE);
    SET_TCPM_TCPC_SLAVE_ADDR(ucPortIndex, _P2_TYPE_C_TCPM_TCPC_I2C_SLAVE_ADDR);
    SET_TCPM_CC_RP_DEF_VALUE(ucPortIndex, _P2_TYPE_C_EMB_SRC_DEF_CUR);
    SET_TCPM_PD_PPS_SUPPORT(ucPortIndex, _P2_TYPE_C_EMB_PD3_PPS_SUPPORT);
    SET_TCPM_PD_EPR_SRC_CAPABLE(ucPortIndex, _P2_TYPE_C_EMB_PD3_1_EPR_SUPPORT);
    SET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex, _P2_TYPE_C_EMB_PD_BEHAVIOR_TYPE);
    SET_TCPM_PD_DPAM_SUPPORT(ucPortIndex, _P2_TYPE_C_EMB_DP_ALT_MODE_SUPPORT);
    SET_TCPM_PD_MODAL_OPERATION_SUPPORT(ucPortIndex, _P2_TYPE_C_MODAL_OPERATION_SUPPORT);

    ScalerTypeCTcpmSetPRSwapOption(ucPortIndex);
    ScalerTypeCTcpmSetDRSwapOption(ucPortIndex);

#if(_HW_TCPM_SUPPORT == _ON)
    // TCPM Slave Addr Setting
    ScalerSetByte(PFA_21_TCPC_0_SLV_ADDR + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), GET_TCPM_TCPC_SLAVE_ADDR(ucPortIndex));
#endif

#if(_TYPE_C_PMIC_SUPPORT == _ON)
    SET_TCPM_PMIC_SUPPORT(ucPortIndex, (_P2_TYPE_C_PMIC_TYPE != _PMIC_NONE));
    SET_TCPM_PMIC_OCP_PROTECT_METHOD(ucPortIndex, _P2_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD);

#if(_TYPE_C_PMIC_FW_POLLING_OCP_SUPPORT == _ON)
    SET_TCPM_PMIC_FW_OCP_CURRENT_VALUE(ucPortIndex, _P2_TYPE_C_PMIC_FW_OCP_CURRENT_VALUE);
    SET_TCPM_PMIC_FW_OCP_DELAY_SHUTDOWN(ucPortIndex, _P2_TYPE_C_PMIC_FW_OCP_DELAY_SHUTDOWN);
#endif
#endif

#if(_PORT_CTRL_TCPM_OCP_PROTECT_BY_TCPC == _ON)
    SET_TCPM_OCP_PROTECT_BY_TCPC(ucPortIndex, _P2_TYPE_C_TCPM_OCP_PROTECT_BY_TCPC);
#endif

#if(_PORT_CTRL_TCPM_OVP_UVP_SUPPORT == _ON)
    SET_TCPM_OVP_UVP_SUPPORT(ucPortIndex, _P2_TYPE_C_TCPM_OVP_UVP_SUPPORT);
    SET_TCPM_OVP_THRESHOLD(ucPortIndex, _P2_TYPE_C_TCPM_OVP_THRESHOLD);
    SET_TCPM_UVP_THRESHOLD(ucPortIndex, _P2_TYPE_C_TCPM_UVP_THRESHOLD);
#endif

    // TCPM Initial State Setting
    SET_TCPM_STATE(ucPortIndex, _TCPM_WAIT_TCPC_ON);

    // Do Initial Proc if TCPC Already Wake Up
    ScalerTypeCTcpmInitialProc(_P2_TYPE_C_PORT);
#endif

#if(_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM)
    ucPortIndex = ScalerTypeCTcpmGetPortIndex(_P3_TYPE_C_PORT);

    // TCPM PCB Related Define Setting
    SET_TCPM_USB_TYPE(ucPortIndex, _P3_USB_HUB_TYPE);
    SET_TCPM_USB_SPEED(ucPortIndex, _P3_USB_SPEED);
    SET_TCPM_USB_ROLE(ucPortIndex, _P3_TYPE_C_EMB_USB_ROLE);
    SET_TCPM_CONNECTOR_TYPE(ucPortIndex, _P3_TYPE_C_EMB_CONNECTOR_TYPE);
    SET_TCPM_TCPC_TYPE(ucPortIndex, _P3_TYPE_C_TCPM_TCPC_TYPE);
    SET_TCPM_TCPC_SLAVE_ADDR(ucPortIndex, _P3_TYPE_C_TCPM_TCPC_I2C_SLAVE_ADDR);
    SET_TCPM_CC_RP_DEF_VALUE(ucPortIndex, _P3_TYPE_C_EMB_SRC_DEF_CUR);
    SET_TCPM_PD_PPS_SUPPORT(ucPortIndex, _P3_TYPE_C_EMB_PD3_PPS_SUPPORT);
    SET_TCPM_PD_EPR_SRC_CAPABLE(ucPortIndex, _P3_TYPE_C_EMB_PD3_1_EPR_SUPPORT);
    SET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex, _P3_TYPE_C_EMB_PD_BEHAVIOR_TYPE);
    SET_TCPM_PD_DPAM_SUPPORT(ucPortIndex, _P3_TYPE_C_EMB_DP_ALT_MODE_SUPPORT);
    SET_TCPM_PD_MODAL_OPERATION_SUPPORT(ucPortIndex, _P3_TYPE_C_MODAL_OPERATION_SUPPORT);

    ScalerTypeCTcpmSetPRSwapOption(ucPortIndex);
    ScalerTypeCTcpmSetDRSwapOption(ucPortIndex);

#if(_HW_TCPM_SUPPORT == _ON)
    // TCPM Slave Addr Setting
    ScalerSetByte(PFA_21_TCPC_0_SLV_ADDR + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), GET_TCPM_TCPC_SLAVE_ADDR(ucPortIndex));
#endif

#if(_TYPE_C_PMIC_SUPPORT == _ON)
    SET_TCPM_PMIC_SUPPORT(ucPortIndex, (_P3_TYPE_C_PMIC_TYPE != _PMIC_NONE));
    SET_TCPM_PMIC_OCP_PROTECT_METHOD(ucPortIndex, _P3_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD);

#if(_TYPE_C_PMIC_FW_POLLING_OCP_SUPPORT == _ON)
    SET_TCPM_PMIC_FW_OCP_CURRENT_VALUE(ucPortIndex, _P3_TYPE_C_PMIC_FW_OCP_CURRENT_VALUE);
    SET_TCPM_PMIC_FW_OCP_DELAY_SHUTDOWN(ucPortIndex, _P3_TYPE_C_PMIC_FW_OCP_DELAY_SHUTDOWN);
#endif
#endif

#if(_PORT_CTRL_TCPM_OCP_PROTECT_BY_TCPC == _ON)
    SET_TCPM_OCP_PROTECT_BY_TCPC(ucPortIndex, _P3_TYPE_C_TCPM_OCP_PROTECT_BY_TCPC);
#endif

#if(_PORT_CTRL_TCPM_OVP_UVP_SUPPORT == _ON)
    SET_TCPM_OVP_UVP_SUPPORT(ucPortIndex, _P3_TYPE_C_TCPM_OVP_UVP_SUPPORT);
    SET_TCPM_OVP_THRESHOLD(ucPortIndex, _P3_TYPE_C_TCPM_OVP_THRESHOLD);
    SET_TCPM_UVP_THRESHOLD(ucPortIndex, _P3_TYPE_C_TCPM_UVP_THRESHOLD);
#endif

    // TCPM Initial State Setting
    SET_TCPM_STATE(ucPortIndex, _TCPM_WAIT_TCPC_ON);

    // Do Initial Proc if TCPC Already Wake Up
    ScalerTypeCTcpmInitialProc(_P3_TYPE_C_PORT);
#endif

#if(_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM)
    ucPortIndex = ScalerTypeCTcpmGetPortIndex(_P4_TYPE_C_PORT);

    // TCPM PCB Related Define Setting
    SET_TCPM_USB_TYPE(ucPortIndex, _P4_USB_HUB_TYPE);
    SET_TCPM_USB_SPEED(ucPortIndex, _P4_USB_SPEED);
    SET_TCPM_USB_ROLE(ucPortIndex, _P4_TYPE_C_EMB_USB_ROLE);
    SET_TCPM_CONNECTOR_TYPE(ucPortIndex, _P4_TYPE_C_EMB_CONNECTOR_TYPE);
    SET_TCPM_TCPC_TYPE(ucPortIndex, _P4_TYPE_C_TCPM_TCPC_TYPE);
    SET_TCPM_TCPC_SLAVE_ADDR(ucPortIndex, _P4_TYPE_C_TCPM_TCPC_I2C_SLAVE_ADDR);
    SET_TCPM_CC_RP_DEF_VALUE(ucPortIndex, _P4_TYPE_C_EMB_SRC_DEF_CUR);
    SET_TCPM_PD_PPS_SUPPORT(ucPortIndex, _P4_TYPE_C_EMB_PD3_PPS_SUPPORT);
    SET_TCPM_PD_EPR_SRC_CAPABLE(ucPortIndex, _P4_TYPE_C_EMB_PD3_1_EPR_SUPPORT);
    SET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex, _P4_TYPE_C_EMB_PD_BEHAVIOR_TYPE);
    SET_TCPM_PD_DPAM_SUPPORT(ucPortIndex, _P4_TYPE_C_EMB_DP_ALT_MODE_SUPPORT);
    SET_TCPM_PD_MODAL_OPERATION_SUPPORT(ucPortIndex, _P4_TYPE_C_MODAL_OPERATION_SUPPORT);

    ScalerTypeCTcpmSetPRSwapOption(ucPortIndex);
    ScalerTypeCTcpmSetDRSwapOption(ucPortIndex);

#if(_HW_TCPM_SUPPORT == _ON)
    // TCPM Slave Addr Setting
    ScalerSetByte(PFA_21_TCPC_0_SLV_ADDR + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), GET_TCPM_TCPC_SLAVE_ADDR(ucPortIndex));
#endif

#if(_TYPE_C_PMIC_SUPPORT == _ON)
    SET_TCPM_PMIC_SUPPORT(ucPortIndex, (_P4_TYPE_C_PMIC_TYPE != _PMIC_NONE));
    SET_TCPM_PMIC_OCP_PROTECT_METHOD(ucPortIndex, _P4_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD);

#if(_TYPE_C_PMIC_FW_POLLING_OCP_SUPPORT == _ON)
    SET_TCPM_PMIC_FW_OCP_CURRENT_VALUE(ucPortIndex, _P4_TYPE_C_PMIC_FW_OCP_CURRENT_VALUE);
    SET_TCPM_PMIC_FW_OCP_DELAY_SHUTDOWN(ucPortIndex, _P4_TYPE_C_PMIC_FW_OCP_DELAY_SHUTDOWN);
#endif
#endif

#if(_PORT_CTRL_TCPM_OCP_PROTECT_BY_TCPC == _ON)
    SET_TCPM_OCP_PROTECT_BY_TCPC(ucPortIndex, _P4_TYPE_C_TCPM_OCP_PROTECT_BY_TCPC);
#endif

#if(_PORT_CTRL_TCPM_OVP_UVP_SUPPORT == _ON)
    SET_TCPM_OVP_UVP_SUPPORT(ucPortIndex, _P4_TYPE_C_TCPM_OVP_UVP_SUPPORT);
    SET_TCPM_OVP_THRESHOLD(ucPortIndex, _P4_TYPE_C_TCPM_OVP_THRESHOLD);
    SET_TCPM_UVP_THRESHOLD(ucPortIndex, _P4_TYPE_C_TCPM_UVP_THRESHOLD);
#endif

    // TCPM Initial State Setting
    SET_TCPM_STATE(ucPortIndex, _TCPM_WAIT_TCPC_ON);

    // Do Initial Proc if TCPC Already Wake Up
    ScalerTypeCTcpmInitialProc(_P4_TYPE_C_PORT);
#endif

#if(_ADAPTOR_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM)
    ucPortIndex = ScalerTypeCTcpmGetPortIndex(_ADAPTOR_TYPE_C_PORT);

    // TCPM PCB Related Define Setting
    SET_TCPM_USB_TYPE(ucPortIndex, _ADAPTOR_TYPE_C_USB_TYPE);
    SET_TCPM_USB_SPEED(ucPortIndex, _USB_BILLBOARD_ONLY);
    SET_TCPM_USB_ROLE(ucPortIndex, _TYPE_C_USB_NOT_SUPPORT);
    SET_TCPM_CONNECTOR_TYPE(ucPortIndex, _ADAPTOR_TYPE_C_EMB_CONNECTOR_TYPE);
    SET_TCPM_TCPC_TYPE(ucPortIndex, _ADAPTOR_TYPE_C_TCPM_TCPC_TYPE);
    SET_TCPM_TCPC_SLAVE_ADDR(ucPortIndex, _ADAPTOR_TYPE_C_TCPM_TCPC_I2C_SLAVE_ADDR);
    SET_TCPM_CC_RP_DEF_VALUE(ucPortIndex, _ADAPTOR_TYPE_C_EMB_SRC_DEF_CUR);
    SET_TCPM_PD_PPS_SUPPORT(ucPortIndex, _ADAPTOR_TYPE_C_EMB_PD3_PPS_SUPPORT);
    SET_TCPM_PD_EPR_SRC_CAPABLE(ucPortIndex, _ADAPTOR_TYPE_C_EMB_PD3_1_EPR_SUPPORT);
    SET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex, _ADAPTOR_TYPE_C_EMB_PD_BEHAVIOR_TYPE);
    SET_TCPM_PD_DPAM_SUPPORT(ucPortIndex, _ADAPTOR_TYPE_C_EMB_DP_ALT_MODE_SUPPORT);
    SET_TCPM_PD_MODAL_OPERATION_SUPPORT(ucPortIndex, _ADAPTOR_TYPE_C_MODAL_OPERATION_SUPPORT);

    ScalerTypeCTcpmSetPRSwapOption(ucPortIndex);
    ScalerTypeCTcpmSetDRSwapOption(ucPortIndex);

#if(_HW_TCPM_SUPPORT == _ON)
    // TCPM Slave Addr Setting
    ScalerSetByte(PFA_21_TCPC_0_SLV_ADDR + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), GET_TCPM_TCPC_SLAVE_ADDR(ucPortIndex));
#endif

#if(_TYPE_C_PMIC_SUPPORT == _ON)
    SET_TCPM_PMIC_SUPPORT(ucPortIndex, (_ADAPTOR_TYPE_C_PMIC_TYPE != _PMIC_NONE));
    SET_TCPM_PMIC_OCP_PROTECT_METHOD(ucPortIndex, _ADAPTOR_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD);

#if(_TYPE_C_PMIC_FW_POLLING_OCP_SUPPORT == _ON)
    SET_TCPM_PMIC_FW_OCP_CURRENT_VALUE(ucPortIndex, _ADAPTOR_TYPE_C_PMIC_FW_OCP_CURRENT_VALUE);
    SET_TCPM_PMIC_FW_OCP_DELAY_SHUTDOWN(ucPortIndex, _ADAPTOR_TYPE_C_PMIC_FW_OCP_DELAY_SHUTDOWN);
#endif
#endif

#if(_PORT_CTRL_TCPM_OCP_PROTECT_BY_TCPC == _ON)
    SET_TCPM_OCP_PROTECT_BY_TCPC(ucPortIndex, _ADAPTOR_TYPE_C_TCPM_OCP_PROTECT_BY_TCPC);
#endif

#if(_PORT_CTRL_TCPM_OVP_UVP_SUPPORT == _ON)
    SET_TCPM_OVP_UVP_SUPPORT(ucPortIndex, _ADAPTOR_TYPE_C_TCPM_OVP_UVP_SUPPORT);
    SET_TCPM_OVP_THRESHOLD(ucPortIndex, _ADAPTOR_TYPE_C_TCPM_OVP_THRESHOLD);
    SET_TCPM_UVP_THRESHOLD(ucPortIndex, _ADAPTOR_TYPE_C_TCPM_UVP_THRESHOLD);
#endif

    // TCPM Initial State Setting
    SET_TCPM_STATE(ucPortIndex, _TCPM_WAIT_TCPC_ON);

    // Do Initial Proc if TCPC Already Wake Up
    ScalerTypeCTcpmInitialProc(_ADAPTOR_TYPE_C_PORT);
#endif
}

//--------------------------------------------------
// Description  : Type C TCPM Pinshare Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmPinshareSetting(void)
{
    // Set Pinshare Mux, Only Need to Set TCPM 0 since TCPM 1 Does Not Have Pinshare Mux
#if(_HW_TCPM_0_SUPPORT == _ON)
    switch(_TCPM_0_IIC_PIN)
    {
        case _TCPM_IIC_PIN_80_81_0_0:

            // Set [0xFA10] [3:2] tcpm_sclsda_sel = b00
            ScalerSetBit(PFA_10_TCPM_MUX, ~(_BIT3 | _BIT2), 0x00);

            break;

        case _TCPM_IIC_PIN_102_103_0_1:

            // Set [0xFA10] [3:2] tcpm_sclsda_sel = b01
            ScalerSetBit(PFA_10_TCPM_MUX, ~(_BIT3 | _BIT2), _BIT2);

            break;

        case _TCPM_IIC_PIN_64_65_0_2:

            // Set [0xFA10] [3:2] tcpm_sclsda_sel = b10
            ScalerSetBit(PFA_10_TCPM_MUX, ~(_BIT3 | _BIT2), _BIT3);

            break;

        default:
            break;
    }

    switch(_TCPM_0_ALERT_PIN)
    {
        case _TCPM_ALERT_PIN_82_83_0_0:

            // Set [0xFA10] [1:0] tcpm_alert_sel = b00
            ScalerSetBit(PFA_10_TCPM_MUX, ~(_BIT1 | _BIT0), 0x00);

            break;

        case _TCPM_ALERT_PIN_148_149_0_1:

            // Set [0xFA10] [1:0] tcpm_alert_sel = b01
            ScalerSetBit(PFA_10_TCPM_MUX, ~(_BIT1 | _BIT0), _BIT0);

            break;

        case _TCPM_ALERT_PIN_66_67_0_2:

            // Set [0xFA10] [1:0] tcpm_alert_sel = b10
            ScalerSetBit(PFA_10_TCPM_MUX, ~(_BIT1 | _BIT0), _BIT1);

            break;

        default:
            break;
    }
#endif
}

//--------------------------------------------------
// Description  : Get TCPM Port Index
// Input Value  : enumTypeCPcbPort
// Output Value : Type C TCPM Port Index
//--------------------------------------------------
BYTE ScalerTypeCTcpmGetPortIndex(EnumTypeCPcbPort enumTypeCPcbPort)
{
    BYTE ucPortIndex = 0;
    BYTE ucIndex = 0;

    for(ucIndex = 0; ucIndex < _TCPM_PORT_VALID; ucIndex++)
    {
        if(g_penumTypeCTcpmPort[ucIndex] == enumTypeCPcbPort)
        {
            ucPortIndex = ucIndex;

            break;
        }
    }

    return ucPortIndex;
}

//--------------------------------------------------
// Description  : Set TCPM HW Shift Index
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmSetHwShiftIndex(void)
{
    BYTE ucPortIndex = 0;
    ucPortIndex = ucPortIndex;

#if(_HW_TCPM_0_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
    ucPortIndex = ScalerTypeCTcpmGetPortIndex(_HW_TCPM_0_0_MAPPING);
    SET_TCPM_IIC_HW_SHIFT(ucPortIndex, _HW_TCPM_IIC_0_SHIFT);
    SET_TCPM_TCPC_HW_SHIFT(ucPortIndex, _HW_TCPM_0_0_SHIFT);
#endif

#if(_HW_TCPM_0_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
    ucPortIndex = ScalerTypeCTcpmGetPortIndex(_HW_TCPM_0_1_MAPPING);
    SET_TCPM_IIC_HW_SHIFT(ucPortIndex, _HW_TCPM_IIC_0_SHIFT);
    SET_TCPM_TCPC_HW_SHIFT(ucPortIndex, _HW_TCPM_0_1_SHIFT);
#endif

#if(_HW_TCPM_1_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
    ucPortIndex = ScalerTypeCTcpmGetPortIndex(_HW_TCPM_1_0_MAPPING);
    SET_TCPM_IIC_HW_SHIFT(ucPortIndex, _HW_TCPM_IIC_1_SHIFT);
    SET_TCPM_TCPC_HW_SHIFT(ucPortIndex, _HW_TCPM_1_0_SHIFT);
#endif

#if(_HW_TCPM_1_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
    ucPortIndex = ScalerTypeCTcpmGetPortIndex(_HW_TCPM_1_1_MAPPING);
    SET_TCPM_IIC_HW_SHIFT(ucPortIndex, _HW_TCPM_IIC_1_SHIFT);
    SET_TCPM_TCPC_HW_SHIFT(ucPortIndex, _HW_TCPM_1_1_SHIFT);
#endif
}

//--------------------------------------------------
// Description  : Set TCPM Power Role Swap Options
// Input Value  : ucPortIndex
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmSetPRSwapOption(BYTE ucPortIndex)
{
#if(_HW_TCPM_SUPPORT == _ON)
    switch(g_penumTypeCTcpmPort[ucPortIndex])
    {
#if(_HW_TCPM_0_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _HW_TCPM_0_0_MAPPING:

            if(GET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex) == _TYPE_C_DP_RX)
            {
                SET_TCPM_PD_SRC_ACCEPT_SWAP_TO_SNK(ucPortIndex, _HW_TCPM_0_0_PD_DPRX_SRC_ACCEPT_SWAP_TO_SNK);
                SET_TCPM_PD_SRC_REQUEST_SWAP_TO_SNK(ucPortIndex, _HW_TCPM_0_0_PD_DPRX_SRC_REQUEST_SWAP_TO_SNK);
                SET_TCPM_PD_SNK_ACCEPT_SWAP_TO_SRC(ucPortIndex, _HW_TCPM_0_0_PD_DPRX_SNK_ACCEPT_SWAP_TO_SRC);
                SET_TCPM_PD_SNK_REQUEST_SWAP_TO_SRC(ucPortIndex, _HW_TCPM_0_0_PD_DPRX_SNK_REQUEST_SWAP_TO_SRC);
            }
            else if(GET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex) == _TYPE_C_DP_TX)
            {
                SET_TCPM_PD_SRC_ACCEPT_SWAP_TO_SNK(ucPortIndex, _HW_TCPM_0_0_PD_DPTX_SRC_ACCEPT_SWAP_TO_SNK);
                SET_TCPM_PD_SRC_REQUEST_SWAP_TO_SNK(ucPortIndex, _HW_TCPM_0_0_PD_DPTX_SRC_REQUEST_SWAP_TO_SNK);
                SET_TCPM_PD_SNK_ACCEPT_SWAP_TO_SRC(ucPortIndex, _HW_TCPM_0_0_PD_DPTX_SNK_ACCEPT_SWAP_TO_SRC);
                SET_TCPM_PD_SNK_REQUEST_SWAP_TO_SRC(ucPortIndex, _HW_TCPM_0_0_PD_DPTX_SNK_REQUEST_SWAP_TO_SRC);
            }
            else
            {
                SET_TCPM_PD_SRC_ACCEPT_SWAP_TO_SNK(ucPortIndex, _FALSE);
                SET_TCPM_PD_SRC_REQUEST_SWAP_TO_SNK(ucPortIndex, _FALSE);
                SET_TCPM_PD_SNK_ACCEPT_SWAP_TO_SRC(ucPortIndex, _FALSE);
                SET_TCPM_PD_SNK_REQUEST_SWAP_TO_SRC(ucPortIndex, _FALSE);
            }

            break;
#endif

#if(_HW_TCPM_0_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _HW_TCPM_0_1_MAPPING:

            if(GET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex) == _TYPE_C_DP_RX)
            {
                SET_TCPM_PD_SRC_ACCEPT_SWAP_TO_SNK(ucPortIndex, _HW_TCPM_0_1_PD_DPRX_SRC_ACCEPT_SWAP_TO_SNK);
                SET_TCPM_PD_SRC_REQUEST_SWAP_TO_SNK(ucPortIndex, _HW_TCPM_0_1_PD_DPRX_SRC_REQUEST_SWAP_TO_SNK);
                SET_TCPM_PD_SNK_ACCEPT_SWAP_TO_SRC(ucPortIndex, _HW_TCPM_0_1_PD_DPRX_SNK_ACCEPT_SWAP_TO_SRC);
                SET_TCPM_PD_SNK_REQUEST_SWAP_TO_SRC(ucPortIndex, _HW_TCPM_0_1_PD_DPRX_SNK_REQUEST_SWAP_TO_SRC);
            }
            else if(GET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex) == _TYPE_C_DP_TX)
            {
                SET_TCPM_PD_SRC_ACCEPT_SWAP_TO_SNK(ucPortIndex, _HW_TCPM_0_1_PD_DPTX_SRC_ACCEPT_SWAP_TO_SNK);
                SET_TCPM_PD_SRC_REQUEST_SWAP_TO_SNK(ucPortIndex, _HW_TCPM_0_1_PD_DPTX_SRC_REQUEST_SWAP_TO_SNK);
                SET_TCPM_PD_SNK_ACCEPT_SWAP_TO_SRC(ucPortIndex, _HW_TCPM_0_1_PD_DPTX_SNK_ACCEPT_SWAP_TO_SRC);
                SET_TCPM_PD_SNK_REQUEST_SWAP_TO_SRC(ucPortIndex, _HW_TCPM_0_1_PD_DPTX_SNK_REQUEST_SWAP_TO_SRC);
            }
            else
            {
                SET_TCPM_PD_SRC_ACCEPT_SWAP_TO_SNK(ucPortIndex, _FALSE);
                SET_TCPM_PD_SRC_REQUEST_SWAP_TO_SNK(ucPortIndex, _FALSE);
                SET_TCPM_PD_SNK_ACCEPT_SWAP_TO_SRC(ucPortIndex, _FALSE);
                SET_TCPM_PD_SNK_REQUEST_SWAP_TO_SRC(ucPortIndex, _FALSE);
            }

            break;
#endif

#if(_HW_TCPM_1_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _HW_TCPM_1_0_MAPPING:

            if(GET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex) == _TYPE_C_DP_RX)
            {
                SET_TCPM_PD_SRC_ACCEPT_SWAP_TO_SNK(ucPortIndex, _HW_TCPM_1_0_PD_DPRX_SRC_ACCEPT_SWAP_TO_SNK);
                SET_TCPM_PD_SRC_REQUEST_SWAP_TO_SNK(ucPortIndex, _HW_TCPM_1_0_PD_DPRX_SRC_REQUEST_SWAP_TO_SNK);
                SET_TCPM_PD_SNK_ACCEPT_SWAP_TO_SRC(ucPortIndex, _HW_TCPM_1_0_PD_DPRX_SNK_ACCEPT_SWAP_TO_SRC);
                SET_TCPM_PD_SNK_REQUEST_SWAP_TO_SRC(ucPortIndex, _HW_TCPM_1_0_PD_DPRX_SNK_REQUEST_SWAP_TO_SRC);
            }
            else if(GET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex) == _TYPE_C_DP_TX)
            {
                SET_TCPM_PD_SRC_ACCEPT_SWAP_TO_SNK(ucPortIndex, _HW_TCPM_1_0_PD_DPTX_SRC_ACCEPT_SWAP_TO_SNK);
                SET_TCPM_PD_SRC_REQUEST_SWAP_TO_SNK(ucPortIndex, _HW_TCPM_1_0_PD_DPTX_SRC_REQUEST_SWAP_TO_SNK);
                SET_TCPM_PD_SNK_ACCEPT_SWAP_TO_SRC(ucPortIndex, _HW_TCPM_1_0_PD_DPTX_SNK_ACCEPT_SWAP_TO_SRC);
                SET_TCPM_PD_SNK_REQUEST_SWAP_TO_SRC(ucPortIndex, _HW_TCPM_1_0_PD_DPTX_SNK_REQUEST_SWAP_TO_SRC);
            }
            else
            {
                SET_TCPM_PD_SRC_ACCEPT_SWAP_TO_SNK(ucPortIndex, _FALSE);
                SET_TCPM_PD_SRC_REQUEST_SWAP_TO_SNK(ucPortIndex, _FALSE);
                SET_TCPM_PD_SNK_ACCEPT_SWAP_TO_SRC(ucPortIndex, _FALSE);
                SET_TCPM_PD_SNK_REQUEST_SWAP_TO_SRC(ucPortIndex, _FALSE);
            }

            break;
#endif

#if(_HW_TCPM_1_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _HW_TCPM_1_1_MAPPING:

            if(GET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex) == _TYPE_C_DP_RX)
            {
                SET_TCPM_PD_SRC_ACCEPT_SWAP_TO_SNK(ucPortIndex, _HW_TCPM_1_1_PD_DPRX_SRC_ACCEPT_SWAP_TO_SNK);
                SET_TCPM_PD_SRC_REQUEST_SWAP_TO_SNK(ucPortIndex, _HW_TCPM_1_1_PD_DPRX_SRC_REQUEST_SWAP_TO_SNK);
                SET_TCPM_PD_SNK_ACCEPT_SWAP_TO_SRC(ucPortIndex, _HW_TCPM_1_1_PD_DPRX_SNK_ACCEPT_SWAP_TO_SRC);
                SET_TCPM_PD_SNK_REQUEST_SWAP_TO_SRC(ucPortIndex, _HW_TCPM_1_1_PD_DPRX_SNK_REQUEST_SWAP_TO_SRC);
            }
            else if(GET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex) == _TYPE_C_DP_TX)
            {
                SET_TCPM_PD_SRC_ACCEPT_SWAP_TO_SNK(ucPortIndex, _HW_TCPM_1_1_PD_DPTX_SRC_ACCEPT_SWAP_TO_SNK);
                SET_TCPM_PD_SRC_REQUEST_SWAP_TO_SNK(ucPortIndex, _HW_TCPM_1_1_PD_DPTX_SRC_REQUEST_SWAP_TO_SNK);
                SET_TCPM_PD_SNK_ACCEPT_SWAP_TO_SRC(ucPortIndex, _HW_TCPM_1_1_PD_DPTX_SNK_ACCEPT_SWAP_TO_SRC);
                SET_TCPM_PD_SNK_REQUEST_SWAP_TO_SRC(ucPortIndex, _HW_TCPM_1_1_PD_DPTX_SNK_REQUEST_SWAP_TO_SRC);
            }
            else
            {
                SET_TCPM_PD_SRC_ACCEPT_SWAP_TO_SNK(ucPortIndex, _FALSE);
                SET_TCPM_PD_SRC_REQUEST_SWAP_TO_SNK(ucPortIndex, _FALSE);
                SET_TCPM_PD_SNK_ACCEPT_SWAP_TO_SRC(ucPortIndex, _FALSE);
                SET_TCPM_PD_SNK_REQUEST_SWAP_TO_SRC(ucPortIndex, _FALSE);
            }

            break;
#endif
        default:

            break;
    }
#else

    // [TO-DO] Dennis : TypeC HW IIC Flow
    ucPortIndex = ucPortIndex;

#endif // End of #if(_HW_TCPM_SUPPORT == _ON)
}

//--------------------------------------------------
// Description  : Set TCPM Data Role Swap Options
// Input Value  : ucPortIndex
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmSetDRSwapOption(BYTE ucPortIndex)
{
#if(_HW_TCPM_SUPPORT == _ON)
    switch(g_penumTypeCTcpmPort[ucPortIndex])
    {
#if(_HW_TCPM_0_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _HW_TCPM_0_0_MAPPING:

            if(GET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex) == _TYPE_C_DP_RX)
            {
                SET_TCPM_PD_DFP_SWAP_TO_UFP(ucPortIndex, _HW_TCPM_0_0_PD_DPRX_DFP_SWAP_TO_UFP);
                SET_TCPM_PD_UFP_SWAP_TO_DFP(ucPortIndex, _HW_TCPM_0_0_PD_DPRX_UFP_SWAP_TO_DFP);
            }
            else if(GET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex) == _TYPE_C_DP_TX)
            {
                SET_TCPM_PD_DFP_SWAP_TO_UFP(ucPortIndex, _HW_TCPM_0_0_PD_DPTX_DFP_SWAP_TO_UFP);
                SET_TCPM_PD_UFP_SWAP_TO_DFP(ucPortIndex, _HW_TCPM_0_0_PD_DPTX_UFP_SWAP_TO_DFP);
            }
            else
            {
                SET_TCPM_PD_DFP_SWAP_TO_UFP(ucPortIndex, _FALSE);
                SET_TCPM_PD_UFP_SWAP_TO_DFP(ucPortIndex, _FALSE);
            }

            break;
#endif

#if(_HW_TCPM_0_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _HW_TCPM_0_1_MAPPING:

            if(GET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex) == _TYPE_C_DP_RX)
            {
                SET_TCPM_PD_DFP_SWAP_TO_UFP(ucPortIndex, _HW_TCPM_0_1_PD_DPRX_DFP_SWAP_TO_UFP);
                SET_TCPM_PD_UFP_SWAP_TO_DFP(ucPortIndex, _HW_TCPM_0_1_PD_DPRX_UFP_SWAP_TO_DFP);
            }
            else if(GET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex) == _TYPE_C_DP_TX)
            {
                SET_TCPM_PD_DFP_SWAP_TO_UFP(ucPortIndex, _HW_TCPM_0_1_PD_DPTX_DFP_SWAP_TO_UFP);
                SET_TCPM_PD_UFP_SWAP_TO_DFP(ucPortIndex, _HW_TCPM_0_1_PD_DPTX_UFP_SWAP_TO_DFP);
            }
            else
            {
                SET_TCPM_PD_DFP_SWAP_TO_UFP(ucPortIndex, _FALSE);
                SET_TCPM_PD_UFP_SWAP_TO_DFP(ucPortIndex, _FALSE);
            }

            break;
#endif

#if(_HW_TCPM_1_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _HW_TCPM_1_0_MAPPING:

            if(GET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex) == _TYPE_C_DP_RX)
            {
                SET_TCPM_PD_DFP_SWAP_TO_UFP(ucPortIndex, _HW_TCPM_1_0_PD_DPRX_DFP_SWAP_TO_UFP);
                SET_TCPM_PD_UFP_SWAP_TO_DFP(ucPortIndex, _HW_TCPM_1_0_PD_DPRX_UFP_SWAP_TO_DFP);
            }
            else if(GET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex) == _TYPE_C_DP_TX)
            {
                SET_TCPM_PD_DFP_SWAP_TO_UFP(ucPortIndex, _HW_TCPM_1_0_PD_DPTX_DFP_SWAP_TO_UFP);
                SET_TCPM_PD_UFP_SWAP_TO_DFP(ucPortIndex, _HW_TCPM_1_0_PD_DPTX_UFP_SWAP_TO_DFP);
            }
            else
            {
                SET_TCPM_PD_DFP_SWAP_TO_UFP(ucPortIndex, _FALSE);
                SET_TCPM_PD_UFP_SWAP_TO_DFP(ucPortIndex, _FALSE);
            }

            break;
#endif

#if(_HW_TCPM_1_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _HW_TCPM_1_1_MAPPING:

            if(GET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex) == _TYPE_C_DP_RX)
            {
                SET_TCPM_PD_DFP_SWAP_TO_UFP(ucPortIndex, _HW_TCPM_1_1_PD_DPRX_DFP_SWAP_TO_UFP);
                SET_TCPM_PD_UFP_SWAP_TO_DFP(ucPortIndex, _HW_TCPM_1_1_PD_DPRX_UFP_SWAP_TO_DFP);
            }
            else if(GET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex) == _TYPE_C_DP_TX)
            {
                SET_TCPM_PD_DFP_SWAP_TO_UFP(ucPortIndex, _HW_TCPM_1_1_PD_DPTX_DFP_SWAP_TO_UFP);
                SET_TCPM_PD_UFP_SWAP_TO_DFP(ucPortIndex, _HW_TCPM_1_1_PD_DPTX_UFP_SWAP_TO_DFP);
            }
            else
            {
                SET_TCPM_PD_DFP_SWAP_TO_UFP(ucPortIndex, _FALSE);
                SET_TCPM_PD_UFP_SWAP_TO_DFP(ucPortIndex, _FALSE);
            }

            break;
#endif
        default:

            break;
    }
#else

    // [TO-DO] Dennis : TypeC HW IIC Flow
    ucPortIndex = ucPortIndex;

#endif // End of #if(_HW_TCPM_SUPPORT == _ON)
}

//--------------------------------------------------
// Description  : Type C TCPM Initialize TCPC Device
// Input Value  : ucPortIndex
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmInitializeTcpc(BYTE ucPortIndex)
{
    // ---------------------
    // TCPC Initial Control
    // ---------------------
    // Disable Src/Snk Vbus, Disable CC
    ScalerTypeCTcpmVbusCtrl(ucPortIndex, _OFF, _PD_POWER_SNK, _PD_FIX_SUPPLY_PDO, 0, 0, _PD_PEAK_CUR_NONE);

    // Set TCPC_CONTROL [0x19] : Disable All TCPC Control
    // [7] SMBus PEC (Rsv.) = 0, [6] L4C Alert En (Rsv.) = 0, [5] WD Timer = 0, [4] Debug Acc. Ctrl = 0, [3:2] I2C Stretch = 0, [1] BIST Test Data = 0, [0] Orientation = 0
    SET_TCPM_TCPC_CONTROL(ucPortIndex, 0x00);
    ScalerTypeCTcpmTcpciSetByte(ucPortIndex, _TCPM_TCPCI_REG_TCPC_CTRL, GET_TCPM_TCPC_CONTROL(ucPortIndex));

    // Set ROLE_CONTROL [0x1A] : Disable DRP, Rp Set to Default, CC1/2 Set to Open
    // [6] DRP = 0, [5:4] Rp Refer Macro = 00 (Rp-Def), [3:2] CC1 = [1:0] CC2 = Open (b'11)
    SET_TCPM_ROLE_CONTROL(ucPortIndex, 0x0F);
    ScalerTypeCTcpmTcpciSetByte(ucPortIndex, _TCPM_TCPCI_REG_ROLE_CTRL, GET_TCPM_ROLE_CONTROL(ucPortIndex));

    // Set FAULT_CONTROL [0x1B] : Enable Fault Detection
    // [4] Force Off Vbus (Rsv.) = 0, [3] Vbus Discharge Fault = 0 (Enable) , [2] OCP Fault = 0 (Enable), [1] OVP Fault = 0 (Enable), [0] Vconn OCP Fault = 0 (Enable)
    SET_TCPM_FAULT_CONTROL(ucPortIndex, 0x00);
    ScalerTypeCTcpmTcpciSetByte(ucPortIndex, _TCPM_TCPCI_REG_FAULT_CTRL, GET_TCPM_FAULT_CONTROL(ucPortIndex));


    // Set POWER_CONTROL [0x1C] : Disable All Power Control, Only Enable Voltage Monitor
    // [7] FRS = 0, [6] DIS_VOL_MNT = 0, [5] DIS_VOL_ALARM = 1, [4] AUTO_DISCH = 0, [3] BLD_DISCH = 0, [2] FRC_DISCH = 0, [1] VCONN_PWR = 0, [0] VCONN_EN = 0
    SET_TCPM_POWER_CONTROL(ucPortIndex, 0x20);
    ScalerTypeCTcpmTcpciSetByte(ucPortIndex, _TCPM_TCPCI_REG_PWR_CTRL, GET_TCPM_POWER_CONTROL(ucPortIndex));
    CLR_TCPM_SRC_VCONN(ucPortIndex);

    // ------------------------------
    // Clear Status and Setting Mask
    // ------------------------------
    // Disable Fault Status Mask (0x15) and Clear Fault Status (0x1F = 0xB3)
    SET_TCPM_FAULT_STATUS_MASK(ucPortIndex, 0x00);
    ScalerTypeCTcpmTcpciSetByte(ucPortIndex, _TCPM_TCPCI_REG_FAULT_STATUS_MASK, GET_TCPM_FAULT_STATUS_MASK(ucPortIndex));

    SET_TCPM_FAULT_STATUS(ucPortIndex, 0xB3);
    ScalerTypeCTcpmTcpciSetByte(ucPortIndex, _TCPM_TCPCI_REG_FAULT_STATUS, GET_TCPM_FAULT_STATUS(ucPortIndex));

    // Disable Power Status Mask (0x14)
    SET_TCPM_POWER_STATUS_MASK(ucPortIndex, 0x00);
    ScalerTypeCTcpmTcpciSetByte(ucPortIndex, _TCPM_TCPCI_REG_PWR_STATUS_MASK, GET_TCPM_POWER_STATUS_MASK(ucPortIndex));

    // Disable Alert Mask and Clear Alert
    SET_TCPM_ALERT_MASK(ucPortIndex, 0x00);
    ScalerTypeCTcpmAlertControl(ucPortIndex, (WORD)_TCPM_TCPCI_ALERT_ALL, _DISABLE);
}

//--------------------------------------------------
// Description  : Type C TCPM Get TCPC Device Info and Capability
// Input Value  : ucPortIndex
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmGetTcpcInfo(BYTE ucPortIndex)
{
    // 1. Get TCPC Device Info (VID, PID, Spec Ver)
    SET_TCPM_VENDOR_ID(ucPortIndex, ScalerTypeCTcpmTcpciGetWord(ucPortIndex, _TCPM_TCPCI_REG_VENDER_ID));

    SET_TCPM_PRODUCT_ID(ucPortIndex, ScalerTypeCTcpmTcpciGetWord(ucPortIndex, _TCPM_TCPCI_REG_PRODUCT_ID));

    SET_TCPM_DEVICE_ID(ucPortIndex, ScalerTypeCTcpmTcpciGetWord(ucPortIndex, _TCPM_TCPCI_REG_DEVICE_ID));

    SET_TCPM_DEVICE_CC_VER(ucPortIndex, ScalerTypeCTcpmTcpciGetWord(ucPortIndex, _TCPM_TCPCI_REG_CC_VER));

    SET_TCPM_DEVICE_PD_VER(ucPortIndex, ScalerTypeCTcpmTcpciGetWord(ucPortIndex, _TCPM_TCPCI_REG_PD_VER));

    SET_TCPM_DEVICE_TCPCI_VER(ucPortIndex, ScalerTypeCTcpmTcpciGetWord(ucPortIndex, _TCPM_TCPCI_REG_TCPCI_VER));

    // 2. Get TCPC Device Capability (Device Cap, Std I/O Cap...)
    SET_TCPM_DEVICE_CAPABILITY_1(ucPortIndex, ScalerTypeCTcpmTcpciGetWord(ucPortIndex, _TCPM_TCPCI_REG_DEVICE_CAP1));

    SET_TCPM_DEVICE_CAPABILITY_2(ucPortIndex, ScalerTypeCTcpmTcpciGetWord(ucPortIndex, _TCPM_TCPCI_REG_DEVICE_CAP2));

    SET_TCPM_DEVICE_STD_INPUT_CAP(ucPortIndex, ScalerTypeCTcpmTcpciGetByte(ucPortIndex, _TCPM_TCPCI_REG_STD_IN_CAP));

    SET_TCPM_DEVICE_STD_OUTPUT_CAP(ucPortIndex, ScalerTypeCTcpmTcpciGetByte(ucPortIndex, _TCPM_TCPCI_REG_STD_OUT_CAP));

    // if TCPC Support Device Capability 3, Get Device Capability 3
    if(GET_TCPM_DEVICE_DEVICE_CAP3_CAP(ucPortIndex) == _TRUE)
    {
        SET_TCPM_DEVICE_CAPABILITY_3(ucPortIndex, ScalerTypeCTcpmTcpciGetWord(ucPortIndex, _TCPM_TCPCI_REG_DEVICE_CAP3));
    }
}

//--------------------------------------------------
// Description  : Convert Tcpm Event ID to Event ID
// Input Value  : ucPortIndex, enumTcpmEventID
// Output Value : enumEventID
//--------------------------------------------------
EnumScalerTimerEventID ScalerTypeCTcpmEventIDMapping(BYTE ucPortIndex, EnumTypeCTcpmEventID enumTcpmEventID)
{
    EnumScalerTimerEventID enumEventID = _SCALER_TIMER_EVENT_INVALID;

#if(_HW_TCPM_SUPPORT == _ON)
    switch(g_penumTypeCTcpmPort[ucPortIndex])
    {
#if(_HW_TCPM_0_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _HW_TCPM_0_0_MAPPING:

            enumEventID = (EnumScalerTimerEventID)(enumTcpmEventID + _SCALER_TIMER_EVENT_TCPM_0_0_SNK_HARD_RST_TIMEOUT);

            break;
#endif

#if(_HW_TCPM_0_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _HW_TCPM_0_1_MAPPING:

            enumEventID = (EnumScalerTimerEventID)(enumTcpmEventID + _SCALER_TIMER_EVENT_TCPM_0_1_SNK_HARD_RST_TIMEOUT);

            break;
#endif

#if(_HW_TCPM_1_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _HW_TCPM_1_0_MAPPING:

            enumEventID = (EnumScalerTimerEventID)(enumTcpmEventID + _SCALER_TIMER_EVENT_TCPM_1_0_SNK_HARD_RST_TIMEOUT);

            break;
#endif

#if(_HW_TCPM_1_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _HW_TCPM_1_1_MAPPING:

            enumEventID = (EnumScalerTimerEventID)(enumTcpmEventID + _SCALER_TIMER_EVENT_TCPM_1_1_SNK_HARD_RST_TIMEOUT);

            break;
#endif
        default:

            break;
    }
#else

    // [TO-DO] Dennis : TypeC HW IIC Flow
    ucPortIndex = ucPortIndex;
    enumTcpmEventID = enumTcpmEventID;

#endif // End of #if(_HW_TCPM_SUPPORT == _ON)

    return enumEventID;
}

//--------------------------------------------------
// Description  : Convert Tcpm WD Event ID to WD Event ID
// Input Value  : ucPortIndex, enumTcpmWDEventID
// Output Value : enumWDEventID
//--------------------------------------------------
EnumScalerWDTimerEventID ScalerTypeCTcpmWDEventIDMapping(BYTE ucPortIndex, EnumTypeCTcpmWDEventID enumTcpmWDEventID)
{
    EnumScalerWDTimerEventID enumWDEventID = _SCALER_WD_TIMER_EVENT_INVALID;

#if(_HW_TCPM_SUPPORT == _ON)
    switch(g_penumTypeCTcpmPort[ucPortIndex])
    {
#if(_HW_TCPM_0_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _HW_TCPM_0_0_MAPPING:

            enumWDEventID = (EnumScalerWDTimerEventID)(enumTcpmWDEventID + _SCALER_WD_TIMER_EVENT_TCPM_0_0_CC_DEBOUNCE);

            break;
#endif

#if(_HW_TCPM_0_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _HW_TCPM_0_1_MAPPING:

            enumWDEventID = (EnumScalerWDTimerEventID)(enumTcpmWDEventID + _SCALER_WD_TIMER_EVENT_TCPM_0_1_CC_DEBOUNCE);

            break;
#endif

#if(_HW_TCPM_1_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _HW_TCPM_1_0_MAPPING:

            enumWDEventID = (EnumScalerWDTimerEventID)(enumTcpmWDEventID + _SCALER_WD_TIMER_EVENT_TCPM_1_0_CC_DEBOUNCE);

            break;
#endif

#if(_HW_TCPM_1_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _HW_TCPM_1_1_MAPPING:

            enumWDEventID = (EnumScalerWDTimerEventID)(enumTcpmWDEventID + _SCALER_WD_TIMER_EVENT_TCPM_1_1_CC_DEBOUNCE);

            break;
#endif
        default:

            break;
    }
#else

    // [TO-DO] Dennis : TypeC HW IIC Flow
    ucPortIndex = ucPortIndex;
    enumTcpmWDEventID = enumTcpmWDEventID;

#endif // End of #if(_HW_TCPM_SUPPORT == _ON)

    return enumWDEventID;
}

//--------------------------------------------------
// Description  : Active Tcpm Timer Event
// Input Value  : ucPortIndex, usTime,  enumTcpmEventID
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmActiveTimerEvent(BYTE ucPortIndex, WORD usTime, EnumTypeCTcpmEventID enumTcpmEventID)
{
    ScalerTimerActiveTimerEvent(usTime, ScalerTypeCTcpmEventIDMapping(ucPortIndex, enumTcpmEventID));
}

//--------------------------------------------------
// Description  : Reactive Tcpm Timer Event
// Input Value  : ucPortIndex, usTime,  enumTcpmEventID
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmReactiveTimerEvent(BYTE ucPortIndex, WORD usTime, EnumTypeCTcpmEventID enumTcpmEventID)
{
    ScalerTimerReactiveTimerEvent(usTime, ScalerTypeCTcpmEventIDMapping(ucPortIndex, enumTcpmEventID));
}

//--------------------------------------------------
// Description  : Cancel Tcpm Timer Event
// Input Value  : ucPortIndex, enumTcpmEventID
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmCancelTimerEvent(BYTE ucPortIndex, EnumTypeCTcpmEventID enumTcpmEventID)
{
    ScalerTimerCancelTimerEvent(ScalerTypeCTcpmEventIDMapping(ucPortIndex, enumTcpmEventID));
}

//--------------------------------------------------
// Description  : Cancel Tcpm WD Timer Event
// Input Value  : ucPortIndex, enumTcpmWDEventID
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmWDCancelTimerEvent(BYTE ucPortIndex, EnumTypeCTcpmWDEventID enumTcpmWDEventID)
{
    ScalerTimerWDCancelTimerEvent(ScalerTypeCTcpmWDEventIDMapping(ucPortIndex, enumTcpmWDEventID));
}

//--------------------------------------------------
// Description  : Type C TCPM Control Vbus
// Input Value  : ucPortIndex, bAction, bPowerDirection, enumPdoType, usVoltage(Unit = 10mV), usCurrent(Unit = 10mA), enumPeakCurrent
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmVbusCtrl(BYTE ucPortIndex, bit bAction, bit bPowerDirection, EnumTypeCPDPdoType enumPdoType, WORD usVoltage, WORD usCurrent, EnumTypeCPDPeakCurType enumPeakCurrent)
{
#if(_TYPE_C_PMIC_SUPPORT == _ON)
    if(GET_TCPM_PMIC_SUPPORT(ucPortIndex) == _ON)
    {
        ScalerTypeCTcpmPmicSetting(ucPortIndex, bAction, bPowerDirection, enumPdoType, usVoltage, usCurrent, enumPeakCurrent);
    }
    else
#endif
    {
        if(bAction == _ON)
        {
            if(bPowerDirection == _PD_POWER_SRC)
            {
                if(usVoltage == 500)
                {
                    // Enable Sourcing Vbus 5V : COMMAND [0x23] : 0x77 (Enable Src 5V)
                    ScalerTypeCTcpmTcpciSetByte(ucPortIndex, _TCPM_TCPCI_REG_COMMAND, _TCPM_TCPCI_CMD_EN_SRC_5V);

                    // ONSEMI_GPIO_1_CFG [0xA4] : [2] GPO_VAL : 0, [0] Output En = 1
                    // ScalerTypeCTcpmTcpciSetByte(ucPortIndex, _TCPM_TCPCI_REG_A4, 0x01);

                    SET_TCPM_SRC_VBUS(ucPortIndex);
                }
                else
                {
                    // [TO-DO] Dennis : Vbus Nondefault Flow
                }
            }
            else if(bPowerDirection == _PD_POWER_SNK)
            {
                // Enable Sinking Vbus : COMMAND [0x23] : 0x55 (Enable Snk Vbus)
                ScalerTypeCTcpmTcpciSetByte(ucPortIndex, _TCPM_TCPCI_REG_COMMAND, _TCPM_TCPCI_CMD_EN_SNK_VBUS);

                // ONSEMI_GPIO_1_CFG [0xA4] : [2] GPO_VAL : 0, [0] Output En = 1
                // ScalerTypeCTcpmTcpciSetByte(ucPortIndex, _TCPM_TCPCI_REG_A4, 0x01);

                SET_TCPM_SNK_VBUS(ucPortIndex);
            }
        }
        else
        {
            // Disable Sourcing Vbus : COMMAND [0x23] : 0x66 (Disable Src 5V)
            ScalerTypeCTcpmTcpciSetByte(ucPortIndex, _TCPM_TCPCI_REG_COMMAND, _TCPM_TCPCI_CMD_DIS_SRC_VBUS);

            // Disable Sinking Vbus : COMMAND [0x23] : 0x44 (Disable Snk Vbus)
            ScalerTypeCTcpmTcpciSetByte(ucPortIndex, _TCPM_TCPCI_REG_COMMAND, _TCPM_TCPCI_CMD_DIS_SNK_VBUS);

            // ONSEMI_GPIO_1_CFG [0xA4] : [2] GPO_VAL : 1, [0] Output En = 1
            // ScalerTypeCTcpmTcpciSetByte(ucPortIndex, _TCPM_TCPCI_REG_A4, 0x05);

            CLR_TCPM_SRC_VBUS(ucPortIndex);
            CLR_TCPM_SNK_VBUS(ucPortIndex);
        }
    }

#if(_PORT_CTRL_TCPM_OCP_PROTECT_BY_TCPC == _ON)
    // ========================================================
    // OCP by TCPC Flow
    // ========================================================
    if(GET_TCPM_OCP_PROTECT_BY_TCPC(ucPortIndex) == _ON)
    {
        // Clear Fault Status (Vbus OCP) (0x1F[3])
        ScalerTypeCTcpmTcpciSetByte(ucPortIndex, _TCPM_TCPCI_REG_FAULT_STATUS, _TCPM_TCPCI_FT_STAT_VBUS_OCP);

        // Disable Fault Status (Vbus OCP) Mask (0x15[3])
        SET_TCPM_FAULT_STATUS_MASK(ucPortIndex, GET_TCPM_FAULT_STATUS_MASK(ucPortIndex) & (~(_TCPM_TCPCI_FT_STAT_VBUS_OCP)));
        ScalerTypeCTcpmTcpciSetByte(ucPortIndex, _TCPM_TCPCI_REG_FAULT_STATUS_MASK, GET_TCPM_FAULT_STATUS_MASK(ucPortIndex));
    }
#endif

#if(_PORT_CTRL_TCPM_OVP_UVP_SUPPORT == _ON)
    // ========================================================
    // OVP/UVP Flow
    // ========================================================
    if(GET_TCPM_OVP_UVP_SUPPORT(ucPortIndex) == _ON)
    {
        // Caculate OVP & UVP threshold
        if(bAction == _ON)
        {
            WORD usOVPThreshold = 0x0000;
            WORD usUVPThreshold = 0x0000;

            // Set Threshold for OVP (Unit = 10mV)
            usOVPThreshold = ((WORD)((((DWORD)usVoltage) * GET_TCPM_OVP_THRESHOLD(ucPortIndex)) / 100));

            SET_TCPM_OVP_VOLTAGE(ucPortIndex, usOVPThreshold);

            // Set Threshold for UVP (Unit = 10mV)
            if(enumPdoType == _PD_3_PROGRAMMABLE_PDO)
            {
                usUVPThreshold = ((WORD)_TCPM_UVP_PPS_THRESHOLD);
            }
            else
            {
                usUVPThreshold = ((WORD)((((DWORD)usVoltage) * GET_TCPM_UVP_THRESHOLD(ucPortIndex)) / 100));
            }

            SET_TCPM_UVP_VOLTAGE(ucPortIndex, usUVPThreshold);

            // Cancel Timer Event & Macro to Stop OVP / UVP Protect
            ScalerTypeCTcpmCancelTimerEvent(ucPortIndex, _SCALER_TIMER_EVENT_TCPM_OVP_UVP_CHECK);
            CLR_TCPM_OVP_UVP_CHECK(ucPortIndex);
        }
        else
        {
            // Cancel Timer Event & Macro to Stop OVP / UVP Protect
            ScalerTypeCTcpmCancelTimerEvent(ucPortIndex, _SCALER_TIMER_EVENT_TCPM_OVP_UVP_CHECK);
            CLR_TCPM_OVP_UVP_CHECK(ucPortIndex);
        }
    }
#endif // End of #if(_PORT_CTRL_TCPM_OVP_UVP_SUPPORT == _ON)

    if((bAction == _ON) && (bPowerDirection == _PD_POWER_SRC) && (usVoltage > 500))
    {
        // Tool Show Warning UI when We Provide Vbus > 5V
        ScalerTypeCTcpmToolWarningUIControl(_ENABLE);
    }
    else
    {
        // Tool Not Show Warning UI when We Provide Vbus <= 5V
        ScalerTypeCTcpmToolWarningUIControl(_DISABLE);
    }
}

//--------------------------------------------------
// Description  : Enable/Disable Detect Vbus On/Off to transit State
// Input Value  : ucPortIndex, bAction : _ENABLE / _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmVbusDetCtrl(BYTE ucPortIndex, bit bAction)
{
    if(bAction == _ENABLE)
    {
        // Enable TCPC Auto Discharge Disconnect (POWER_CONTROL [0x1C] [4] Auto Discharge Disconnect)
        SET_TCPM_POWER_CONTROL(ucPortIndex, GET_TCPM_POWER_CONTROL(ucPortIndex) | (_BIT4));
        ScalerTypeCTcpmTcpciSetByte(ucPortIndex, _TCPM_TCPCI_REG_PWR_CTRL, GET_TCPM_POWER_CONTROL(ucPortIndex));
    }
    else
    {
        // Disable TCPC Auto Discharge Disconnect (POWER_CONTROL [0x1C] [4] Auto Discharge Disconnect)
        SET_TCPM_POWER_CONTROL(ucPortIndex, GET_TCPM_POWER_CONTROL(ucPortIndex) & (~_BIT4));
        ScalerTypeCTcpmTcpciSetByte(ucPortIndex, _TCPM_TCPCI_REG_PWR_CTRL, GET_TCPM_POWER_CONTROL(ucPortIndex));
    }
}

//--------------------------------------------------
// Description  : Type C TCPM Discharge Vbus
// Input Value  : ucPortIndex, bAction : _ON / _OFF
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmVbusDischargeCtrl(BYTE ucPortIndex, bit bAction)
{
#if(_TYPE_C_PMIC_SUPPORT == _ON)
    if(GET_TCPM_PMIC_SUPPORT(ucPortIndex) == _ON)
    {
        ScalerTypeCTcpmPmicVbusDischarge(ucPortIndex, bAction);
    }
    else
#endif
    {
        if(bAction == _ON)
        {
            // Enable TCPC Force Discharge (POWER_CONTROL [0x1C] [2] Force Discharge)
            SET_TCPM_POWER_CONTROL(ucPortIndex, GET_TCPM_POWER_CONTROL(ucPortIndex) | (_BIT2));
            ScalerTypeCTcpmTcpciSetByte(ucPortIndex, _TCPM_TCPCI_REG_PWR_CTRL, GET_TCPM_POWER_CONTROL(ucPortIndex));
        }
        else
        {
            // Disable TCPC Force Discharge (POWER_CONTROL [0x1C] [2] Force Discharge)
            SET_TCPM_POWER_CONTROL(ucPortIndex, GET_TCPM_POWER_CONTROL(ucPortIndex) & (~_BIT2));
            ScalerTypeCTcpmTcpciSetByte(ucPortIndex, _TCPM_TCPCI_REG_PWR_CTRL, GET_TCPM_POWER_CONTROL(ucPortIndex));
        }
    }
}

//--------------------------------------------------
// Description  : Type C TCPM Vbus Protection Start
// Input Value  : ucPortIndex, enumPowerRole : _TYPE_C_POWER_SRC / _TYPE_C_POWER_SNK
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmVbusProtectStart(BYTE ucPortIndex, EnumTypeCPowerRole enumPowerRole)
{
    ucPortIndex = ucPortIndex;
    enumPowerRole = enumPowerRole;

#if(_PORT_CTRL_TCPM_OCP_PROTECT_BY_TCPC == _ON)
    // ========================================================
    // OCP by TCPC Flow
    // ========================================================
    if((enumPowerRole == _TYPE_C_POWER_SRC) && (GET_TCPM_OCP_PROTECT_BY_TCPC(ucPortIndex) == _ON))
    {
        // Clear Fault Status (Vbus OCP) (0x1F[3])
        ScalerTypeCTcpmTcpciSetByte(ucPortIndex, _TCPM_TCPCI_REG_FAULT_STATUS, _TCPM_TCPCI_FT_STAT_VBUS_OCP);

        // Enable Fault Status (Vbus OCP) Mask (0x15[3])
        SET_TCPM_FAULT_STATUS_MASK(ucPortIndex, GET_TCPM_FAULT_STATUS_MASK(ucPortIndex) | (_TCPM_TCPCI_FT_STAT_VBUS_OCP));
        ScalerTypeCTcpmTcpciSetByte(ucPortIndex, _TCPM_TCPCI_REG_FAULT_STATUS_MASK, GET_TCPM_FAULT_STATUS_MASK(ucPortIndex));
    }
#endif

#if(_PORT_CTRL_TCPM_OVP_UVP_SUPPORT == _ON)
    // ========================================================
    // OVP/UVP Flow
    // ========================================================
    if(GET_TCPM_OVP_UVP_SUPPORT(ucPortIndex) == _ON)
    {
        // Active Timer Event to Detect OVP/UVP
        ScalerTypeCTcpmActiveTimerEvent(ucPortIndex, 40, _SCALER_TIMER_EVENT_TCPM_OVP_UVP_CHECK);
        SET_TCPM_OVP_UVP_CHECK(ucPortIndex);
    }
#endif

#if((_TYPE_C_PMIC_SUPPORT == _ON) && (_PORT_CTRL_TCPM_PMIC_CHECK_SUPPORT == _ON))
    // ========================================================
    // 1. OCP by Polling PMIC's ADC Flow   2. PMIC Debug Flow in PPS Mode
    // ========================================================
    if((GET_TCPM_PMIC_SUPPORT(ucPortIndex) == _ON) && (GET_TCPM_PMIC_CHECK_SUPPORT(ucPortIndex) == _ON))
    {
        // Check if Any PMIC Protection Timer Needs to be Actived
        if(GET_TCPM_PMIC_PROTECT_TIMER_CHECK(ucPortIndex) == _TRUE)
        {
            CLR_TCPM_PMIC_PROTECT_TIMER_CHECK(ucPortIndex);

            // Set PMIC Protection Timer Start Flag to Active PMIC Protection Tracking Timer in Main Loop
            SET_TCPM_PMIC_PROTECT_TIMER_START(ucPortIndex);
        }

        SET_TCPM_PMIC_PROTECT_VALID(ucPortIndex);
    }
#endif
}

//--------------------------------------------------
// Description  : Type C TCPM Get Vbus Voltage
// Input Value  : ucPortIndex
// Output Value : Vbus Voltage (Unit = 100mV)
//--------------------------------------------------
WORD ScalerTypeCTcpmGetVbusVoltage(BYTE ucPortIndex)
{
    WORD usVbusVoltage = 0x00;
    WORD usTcpcRegValue = 0x00;
    BYTE ucFactor = 0x00;

    // Read TCPC VBUS_VOLTAGE [0x70~71]
    usTcpcRegValue = ScalerTypeCTcpmTcpciGetWord(ucPortIndex, _TCPM_TCPCI_REG_VBUS_VOL);

    // 0x70[3:2] = Scaler Factor (00 : Not Scaled, 01 : Vbus Measure Divided by 2,  10 : Vbus Measure Divided by 4)
    if((usTcpcRegValue & (_BIT11 | _BIT10)) == (_BIT10))
    {
        ucFactor = 0x01;
    }
    else if((usTcpcRegValue & (_BIT11 | _BIT10)) == (_BIT11))
    {
        ucFactor = 0x02;
    }

    // {0x70[1:0],0x71[7:0]} = Vbus Voltage (Unit = 25mV)
    usVbusVoltage = ((usTcpcRegValue & 0x3FF) << ucFactor);

    // Convert Vbus Voltage (Unit = 25mV) to 100mV
    usVbusVoltage = (usVbusVoltage >> 2);

    return usVbusVoltage;
}

//--------------------------------------------------
// Description  : Type C TCPM Control Vconn
// Input Value  : ucPortIndex, bAction : _ON / _OFF
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmVconnCtrl(BYTE ucPortIndex, bit bAction)
{
    if(bAction == _ON)
    {
        if(GET_TCPM_DEVICE_VCONN_OCP_CAP(ucPortIndex) == _TRUE)
        {
            // Clear Fault Status (Vconn OCP) (0x1F[1])
            ScalerTypeCTcpmTcpciSetByte(ucPortIndex, _TCPM_TCPCI_REG_FAULT_STATUS, _TCPM_TCPCI_FT_STAT_VCONN_OCP);

            // Enable Fault Status (Vconn OCP) Mask (0x15[1])
            SET_TCPM_FAULT_STATUS_MASK(ucPortIndex, GET_TCPM_FAULT_STATUS_MASK(ucPortIndex) | (_TCPM_TCPCI_FT_STAT_VCONN_OCP));
            ScalerTypeCTcpmTcpciSetByte(ucPortIndex, _TCPM_TCPCI_REG_FAULT_STATUS_MASK, GET_TCPM_FAULT_STATUS_MASK(ucPortIndex));
        }

        // Turn On Vconn
        SET_TCPM_POWER_CONTROL(ucPortIndex, GET_TCPM_POWER_CONTROL(ucPortIndex) | (_BIT0));
        SET_TCPM_SRC_VCONN(ucPortIndex);
        ScalerTypeCTcpmTcpciSetByte(ucPortIndex, _TCPM_TCPCI_REG_PWR_CTRL, GET_TCPM_POWER_CONTROL(ucPortIndex));
    }
    else
    {
        if(GET_TCPM_DEVICE_VCONN_OCP_CAP(ucPortIndex) == _TRUE)
        {
            // Clear Fault Status (Vconn OCP) (0x1F[1])
            ScalerTypeCTcpmTcpciSetByte(ucPortIndex, _TCPM_TCPCI_REG_FAULT_STATUS, _TCPM_TCPCI_FT_STAT_VCONN_OCP);

            // Disable Fault Status (Vconn OCP) Mask (0x15[1])
            SET_TCPM_FAULT_STATUS_MASK(ucPortIndex, GET_TCPM_FAULT_STATUS_MASK(ucPortIndex) & (~(_TCPM_TCPCI_FT_STAT_VCONN_OCP)));
            ScalerTypeCTcpmTcpciSetByte(ucPortIndex, _TCPM_TCPCI_REG_FAULT_STATUS_MASK, GET_TCPM_FAULT_STATUS_MASK(ucPortIndex));
        }

        // Turn Off Vconn
        SET_TCPM_POWER_CONTROL(ucPortIndex, GET_TCPM_POWER_CONTROL(ucPortIndex) & (~_BIT0));
        CLR_TCPM_SRC_VCONN(ucPortIndex);
        ScalerTypeCTcpmTcpciSetByte(ucPortIndex, _TCPM_TCPCI_REG_PWR_CTRL, GET_TCPM_POWER_CONTROL(ucPortIndex));
    }
}

//--------------------------------------------------
// Description  : Type C TCPM Control TCPC Alert and Alert Mask
// Input Value  : ucPortIndex, AlertType, Action (_ENABLE / _DISABLE)
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmAlertControl(BYTE ucPortIndex, WORD usAlertType, bit bAction)
{
    WORD usTargetAlertMask = 0x00;

#if(_HW_TCPM_SUPPORT == _ON)
#if(_HW_TCPM_ALERT_UPDATE == _ON)
    // 1. Set Fw Busy Flag to Prevent Interrupting by HW
    if(ScalerTypeCTcpmFwBusyCtrl(ucPortIndex, _ENABLE) == _FAIL)
    {
        DebugMessageTypeC("7. [TCPM] Alert Update Failed, Alert Type = ", usAlertType);

        return;
    }

    // 2. Update Clear Alert Reg
    ScalerSetByte(PFA_28_TCPC_0_CLR_ALERT_L + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), (BYTE)(usAlertType));
    ScalerSetByte(PFA_29_TCPC_0_CLR_ALERT_H + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), (BYTE)(usAlertType >> 8));

    if(bAction == _ENABLE)
    {
        // Un-Mask (Enable) Alert
        usTargetAlertMask = (GET_TCPM_ALERT_MASK(ucPortIndex) | usAlertType);
    }
    else
    {
        // Mask (Disable) Alert
        usTargetAlertMask = (GET_TCPM_ALERT_MASK(ucPortIndex) & (~(usAlertType)));
    }

    // 3. Update Alert Mask Mask  & Reg
    SET_TCPM_ALERT_MASK(ucPortIndex, usTargetAlertMask);
    ScalerSetByte(PFA_24_TCPC_0_ALERT_MASK_L + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), (BYTE)(usTargetAlertMask));
    ScalerSetByte(PFA_25_TCPC_0_ALERT_MASK_H + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), (BYTE)(usTargetAlertMask >> 8));

    // 4. Start Alert Update (Do Not Need to Enable alert_update_irq_en)
    // [0xFA23] [2] tcpc_0_alert_update, [1] tcpc_0_alert_update_irq, [0] tcpc_0_alert_update_irq_en
    ScalerSetBit(PFA_23_TCPC_0_ALERT_AUTO_CTRL + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT5 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));

    // 5. Clear Fw Busy Flag
    ScalerTypeCTcpmFwBusyCtrl(ucPortIndex, _DISABLE);
#else
    // 1. Clear Alert
    ScalerTypeCTcpmTcpciSetWord(ucPortIndex, _TCPM_TCPCI_REG_ALERT, usAlertType);

    if(bAction == _ENABLE)
    {
        // Un-Mask (Enable) Alert
        usTargetAlertMask = (GET_TCPM_ALERT_MASK(ucPortIndex) | usAlertType);
    }
    else
    {
        // Mask (Disable) Alert
        usTargetAlertMask = (GET_TCPM_ALERT_MASK(ucPortIndex) & (~(usAlertType)));
    }

    // 2. Update Alert Mask
    SET_TCPM_ALERT_MASK(ucPortIndex, usTargetAlertMask);
    ScalerTypeCTcpmTcpciSetWord(ucPortIndex, _TCPM_TCPCI_REG_ALERT_MASK, usTargetAlertMask);
#endif // End of #if(_HW_TCPM_ALERT_UPDATE == _ON)

    // Enable / Disable Alert IRQ
    ScalerTypeCTcpmAlertIntControl(ucPortIndex, usAlertType, bAction);

#else

    // [TO-DO] Dennis : TypeC HW IIC Flow
    ucPortIndex = ucPortIndex;
    usAlertType = usAlertType;
    bAction = bAction;
    usTargetAlertMask = usTargetAlertMask;

#endif // End of #if(_HW_TCPM_SUPPORT == _ON)
}

//--------------------------------------------------
// Description  : Enable / Disable Receive Interrupt.
// Input Value  : ucPortIndex, b1Action
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmRxIntControl(BYTE ucPortIndex, bit b1Action)
{
#if(_HW_TCPM_SUPPORT == _ON)

    if(b1Action == _ENABLE)
    {
        // Enable Rx Msg IRQ [0xFA48] [2] alert_rx_msg_irq_en
        ScalerSetBit(PFA_48_TCPC_0_RX_MSG_AUTO_CTRL_1 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT3 | _BIT2 | _BIT1), _BIT2);

        // Enable Rx Overflow IRQ [0xFA44] [2] alert_rx_ov_irq_en
        ScalerSetBit(PFA_44_TCPC_0_ALERT_RELATED_IRQ_2 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT3 | _BIT2 | _BIT1), _BIT2);
    }
    else
    {
        // Disable Rx Msg IRQ [0xFA48] [2] alert_rx_msg_irq_en
        ScalerSetBit(PFA_48_TCPC_0_RX_MSG_AUTO_CTRL_1 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT3 | _BIT2 | _BIT1), 0x00);

        // Disable Rx Overflow IRQ [0xFA44] [2] alert_rx_ov_irq_en
        ScalerSetBit(PFA_44_TCPC_0_ALERT_RELATED_IRQ_2 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT3 | _BIT2 | _BIT1), 0x00);
    }

#else

    // [TO-DO] Dennis : TypeC HW IIC Flow
    ucPortIndex = ucPortIndex;
    b1Action = b1Action;

#endif // End of #if(_HW_TCPM_SUPPORT == _ON)
}

//--------------------------------------------------
// Description  : Enable Tool to Show Warning UI when We Provide Vbus > 5V
// Input Value  : _ENABLE / _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmToolWarningUIControl(bit bAction)
{
    // Tool Usage : [0xFA0E] [4] Used to Decide Whether Tool shall Show Warning UI when Disable Unattach HW Force Vbus Off Function([3]=0), 0 = Not Show UI, 1 = Show UI
    if(bAction == _ENABLE)
    {
        ScalerSetBit(PFA_0E_DUMMY_1, ~_BIT4, _BIT4);
    }
    else
    {
        ScalerSetBit(PFA_0E_DUMMY_1, ~_BIT4, 0x00);
    }
}

//--------------------------------------------------
// Description  : Process For Change Between SRC and SNK w/o Unattach
// Input Value  : ucPortIndex, ucTargetRole
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmSwitchPowerRole(BYTE ucPortIndex, BYTE ucTargetRole)
{
    if(ucTargetRole == _PD_POWER_SRC)
    {
        SET_TCPM_CC_FSM(ucPortIndex, _TCPM_CC_FSM_ATTACH_SRC);

        // Set CC to Rp
        // ROLE_CONTROL [0x1A] ([6] DRP = 1, [5:4] Rp Refer Macro, [3:2] CC1 = [1:0] CC2 = Rp)
        if(GET_TCPM_CC_RP_DEF_VALUE(ucPortIndex) == _TYPE_C_SRC_DEF_USB)
        {
            SET_TCPM_ROLE_CONTROL(ucPortIndex, _BIT6 | _BIT2 | _BIT0);
        }
        else if(GET_TCPM_CC_RP_DEF_VALUE(ucPortIndex) == _TYPE_C_SRC_DEF_1P5A)
        {
            SET_TCPM_ROLE_CONTROL(ucPortIndex, _BIT6 | _BIT4 | _BIT2 | _BIT0);
        }
        else
        {
            SET_TCPM_ROLE_CONTROL(ucPortIndex, _BIT6 | _BIT5 | _BIT2 | _BIT0);
        }

        ScalerTypeCTcpmTcpciSetByte(ucPortIndex, _TCPM_TCPCI_REG_ROLE_CTRL, GET_TCPM_ROLE_CONTROL(ucPortIndex));
    }
    else
    {
        SET_TCPM_CC_FSM(ucPortIndex, _TCPM_CC_FSM_ATTACH_SNK);

        // Set CC to Rd
        // ROLE_CONTROL [0x1A] ([6] DRP = 1, [5:4] Rp default, [3:2] CC1 = [1:0] CC2 = Rd)
        SET_TCPM_ROLE_CONTROL(ucPortIndex, _BIT6 | _BIT3 | _BIT1);

        ScalerTypeCTcpmTcpciSetByte(ucPortIndex, _TCPM_TCPCI_REG_ROLE_CTRL, GET_TCPM_ROLE_CONTROL(ucPortIndex));
    }
}

//--------------------------------------------------
// Description  : TypeC TCPM Cc Function Control
// Input Value  : enumTypeCPcbPort, enumCcFunction
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmCcFunctionControl(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCCcFunction enumCcFunction)
{
    BYTE ucPortIndex = ScalerTypeCTcpmGetPortIndex(enumTypeCPcbPort);

    if(enumCcFunction == _TYPE_C_CC_FUNCTION_DISABLE)
    {
        CLR_TCPM_CC_CONNECT_EN(ucPortIndex);
        SET_TCPM_CC_ERROR_RECOVERY(ucPortIndex);
    }
    else if(enumCcFunction == _TYPE_C_CC_FUNCTION_ENABLE)
    {
        SET_TCPM_CC_CONNECT_EN(ucPortIndex);
    }
}

//--------------------------------------------------
// Description  : Type C TCPM CC Initail
// Input Value  : ucPortIndex
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmCcInitial(BYTE ucPortIndex)
{
    // Initial Flags & Status Setting
    CLR_TCPM_CC_ATTACHED(ucPortIndex);
    CLR_TCPM_RESET_FLAG(ucPortIndex);

    // Enable CC
    SET_TCPM_CC_CONNECT_EN(ucPortIndex);

    // Set TCPM CC FSM & FW State Macro
    SET_TCPM_CC_FSM(ucPortIndex, _TCPM_CC_FSM_NONE);
}

//--------------------------------------------------
// Description  : Type C TCPM CC Handler
// Input Value  : ucPortIndex
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmCcHandler(BYTE ucPortIndex)
{
    switch(GET_TCPM_CC_FW_STATE(ucPortIndex))
    {
        case _TCPM_CC_FW_UNATTACH:

            // Do Unattach Reset Only One Time When CC Function is Disable
            if(GET_TCPM_RESET_FLAG(ucPortIndex) == _FALSE)
            {
                SET_TCPM_RESET_FLAG(ucPortIndex);

#if(_TYPE_C_PMIC_SUPPORT == _ON)
                if(GET_TCPM_PMIC_SUPPORT(ucPortIndex) == _ON)
                {
                    ScalerTypeCTcpmPmicReset(ucPortIndex);
                }
#endif
                ScalerTypeCTcpmPdReset(ucPortIndex);
                // FW Solution : Samsung S8 Clear Flag When CC Unattach (Not Cleared When PD Reset)
                ScalerTypeCTcpmPdClrInteropS8Flag(ucPortIndex);
                ScalerTypeCTcpmCcUnattachReset(ucPortIndex);
            }

            if(GET_TCPM_CC_CONNECT_EN(ucPortIndex) == _TRUE)
            {
                CLR_TCPM_RESET_FLAG(ucPortIndex);

                // Setting for CC FSM Connection
                ScalerTypeCTcpmCcConnectionSet(ucPortIndex);

                SET_TCPM_CC_FW_STATE(ucPortIndex, _TCPM_CC_FW_CONNECTING);

                // Enable Alert Detect and Start CC FSM
                ScalerTypeCTcpmCcConnectionStart(ucPortIndex);
            }

            break;

        case _TCPM_CC_FW_CONNECTING:

            // Check if Error Recovery is SET
            if(GET_TCPM_CC_ERROR_RECOVERY(ucPortIndex) == _TRUE)
            {
                // Take Unattach Flow
                ScalerTypeCTcpmCcUnattachSetting(ucPortIndex);

                // Disconnect Both CC1 / CC2, and Wait 30ms (Should Be More Than tPDDebounce Max)
                ScalerTypeCTcpmCcDisconnect(ucPortIndex);

                // Any Fatal Error Happens, Need to Unattach Type C Function
                CLR_TCPM_CC_ERROR_RECOVERY(ucPortIndex);
            }

            break;

        case _TCPM_CC_FW_ATTACHED:

            // --------------- [Warning] On-Semi -------------
            // TCPC Dose Not Detect Unattach When "Unattach" Happens During PD Rcv/Sending Message
            // Set Flag for Main Loop to Check CC Status
            if((GET_TCPM_TCPC_TYPE(ucPortIndex) == _TCPC_ON_SEMI) && (GET_TCPM_CC_FSM(ucPortIndex) == _TCPM_CC_FSM_ATTACH_SNK) && (GET_TCPM_CC_SNK_DET_UNATTACH(ucPortIndex) == _TRUE) && (GET_TCPM_CC_SNK_UNATTACH_DBC(ucPortIndex) != _TRUE))
            {
                if(ScalerTypeCTcpmCcSnkCheckUnattach(ucPortIndex) == _TRUE)
                {
                    ScalerTypeCTcpmCcUnattachSetting(ucPortIndex);
                }

                CLR_TCPM_CC_SNK_DET_UNATTACH(ucPortIndex);
            }


            // Check if Error Recovery is SET
            if(GET_TCPM_CC_ERROR_RECOVERY(ucPortIndex) == _TRUE)
            {
                // Take Unattach Flow
                ScalerTypeCTcpmCcUnattachSetting(ucPortIndex);

                // Disconnect Both CC1 / CC2, and Wait 30ms (Should Be More Than tPDDebounce Max)
                ScalerTypeCTcpmCcDisconnect(ucPortIndex);

                // Any Fatal Error Happens, Need to Unattach Type C Function
                CLR_TCPM_CC_ERROR_RECOVERY(ucPortIndex);
            }

            break;

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Mainloop Process For Unattach Setting
// Input Value  : ucPortIndex
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmCcUnattachSetting(BYTE ucPortIndex)
{
    // From 1. Error Recovery

#if(_HW_TCPM_SUPPORT == _ON)
    // Clear & Disabel Alert IRQ : [0xFA23] [5] tcpc_0_alert_irq, [4] tcpc_0_alert_irq_en
    ScalerSetBit(PFA_23_TCPC_0_ALERT_AUTO_CTRL + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT5 | _BIT4 | _BIT1), _BIT5);
#endif

    // Reset All Alert
    ScalerTypeCTcpmAlertControl(ucPortIndex, (WORD)_TCPM_TCPCI_ALERT_ALL, _DISABLE);

    if(GET_TCPM_SRC_VCONN(ucPortIndex) == _TRUE)
    {
        // Turn Off Vconn, if they are turned on when attached
        ScalerTypeCTcpmVconnCtrl(ucPortIndex, _OFF);
    }

    // Turn Off Vbus and Turn On Vbus Discharge
    ScalerTypeCTcpmVbusCtrl(ucPortIndex, _OFF, _PD_POWER_SNK, _PD_NONE_SETTING_PDO, 0, 0, _PD_PEAK_CUR_NONE);
    ScalerTypeCTcpmVbusDischargeCtrl(ucPortIndex, _ON);

    CLR_TCPM_CC_ATTACHED(ucPortIndex);
    SET_TCPM_CC_FW_STATE(ucPortIndex, _TCPM_CC_FW_UNATTACH);
}

//--------------------------------------------------
// Description  : Type C TCPM Unattach (Turn Off Power / Disconnect Channel / Clear IRQs)
// Input Value  : ucPortIndex
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmCcUnattachReset(BYTE ucPortIndex)
{
    if(GET_TCPM_SRC_VCONN(ucPortIndex) == _TRUE)
    {
        // Turn Off Vconn, if they are turned on when attached
        ScalerTypeCTcpmVconnCtrl(ucPortIndex, _OFF);
    }

    // Only Initial to Unattach & Error Recovery Will Use Mainloop's Unattach Reset, so It's Allowed Some Delay Times When Vbus Discharge
    ScalerTypeCTcpmVbusDischargeCtrl(ucPortIndex, _ON);

    {
        BYTE ucVbusDischargeCnt = 0;

        // Polling Until Vbus Discharge to 0V For User Define Delay times
        while((ucVbusDischargeCnt < GET_TCPM_CC_DISCHARGE_COUNT(ucPortIndex)) && ((ScalerTypeCTcpmGetVbusVoltage(ucPortIndex) > _TCPM_VSAFE0V_UP_BND)))
        {
            ucVbusDischargeCnt += 1;
            ScalerTimerDelayXms(1);
        }
    }

    // Disable Vbus Discharge
    ScalerTypeCTcpmVbusDischargeCtrl(ucPortIndex, _OFF);

    // CC Flags Reset
    CLR_TCPM_CC_ATTACHED(ucPortIndex);
    CLR_TCPM_CC_RA_EXIST(ucPortIndex);
    CLR_TCPM_CC_ERROR_RECOVERY(ucPortIndex);
    CLR_TCPM_CC_SNK_UNATTACH_DBC(ucPortIndex);
    CLR_TCPM_CC_SNK_DET_UNATTACH(ucPortIndex);
    CLR_TCPM_CC_STATUS_CHG(ucPortIndex);
    CLR_TCPM_CC_SRC_DET(ucPortIndex);
    CLR_TCPM_CC_SNK_DET(ucPortIndex);

    // Set POWER_CONTROL [0x1C] : Disable All Power Control, Only Enable Voltage Monitor
    // [7] FRS = 0, [6] DIS_VOL_MNT = 0, [5] DIS_VOL_ALARM = 1, [4] AUTO_DISCH = 0, [3] BLD_DISCH = 0, [2] FRC_DISCH = 0, [1] VCONN_PWR = 0, [0] VCONN_EN = 0
    SET_TCPM_POWER_CONTROL(ucPortIndex, 0x20);
    ScalerTypeCTcpmTcpciSetByte(ucPortIndex, _TCPM_TCPCI_REG_PWR_CTRL, GET_TCPM_POWER_CONTROL(ucPortIndex));
}

//--------------------------------------------------
// Description  : Type C TCPM CC Connection Setting
// Input Value  : ucPortIndex
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmCcConnectionSet(BYTE ucPortIndex)
{
    // Set ROLE_CONTROL [0x1A] : DRP, Rp Value, CC1, CC2
    switch(GET_TCPM_CC_PORT_ROLE(ucPortIndex))
    {
        case _TYPE_C_PORT_SNK_ONLY:

            // ROLE_CONTROL [0x1A] ([6] DRP = 0, [5:4] Rp default, [3:2] CC1 = [1:0] CC2 = Rd)
            SET_TCPM_ROLE_CONTROL(ucPortIndex, _BIT3 | _BIT1);

            ScalerTypeCTcpmTcpciSetByte(ucPortIndex, _TCPM_TCPCI_REG_ROLE_CTRL, GET_TCPM_ROLE_CONTROL(ucPortIndex));

            SET_TCPM_CC_FSM(ucPortIndex, _TCPM_CC_FSM_UNATTACH_SNK);

            break;

        case _TYPE_C_PORT_SRC_ONLY:

            // ROLE_CONTROL [0x1A] ([6] DRP = 0, [5:4] Rp Refer Macro, [3:2] CC1 = [1:0] CC2 = Rp)
            if(GET_TCPM_CC_RP_DEF_VALUE(ucPortIndex) == _TYPE_C_SRC_DEF_USB)
            {
                SET_TCPM_ROLE_CONTROL(ucPortIndex, _BIT2 | _BIT0);

                SET_TCPM_CC_DEF_CUR(ucPortIndex, 90);  // 90 * 10mA = 900mA
            }
            else if(GET_TCPM_CC_RP_DEF_VALUE(ucPortIndex) == _TYPE_C_SRC_DEF_1P5A)
            {
                SET_TCPM_ROLE_CONTROL(ucPortIndex, _BIT4 | _BIT2 | _BIT0);

                SET_TCPM_CC_DEF_CUR(ucPortIndex, 150);  // 150 * 10mA = 1.5A
            }
            else
            {
                SET_TCPM_ROLE_CONTROL(ucPortIndex, _BIT5 | _BIT2 | _BIT0);

                SET_TCPM_CC_DEF_CUR(ucPortIndex, 300); // 300 * 10mA = 3.0A
            }

            ScalerTypeCTcpmTcpciSetByte(ucPortIndex, _TCPM_TCPCI_REG_ROLE_CTRL, GET_TCPM_ROLE_CONTROL(ucPortIndex));

            SET_TCPM_CC_FSM(ucPortIndex, _TCPM_CC_FSM_UNATTACH_SRC);

            break;

        case _TYPE_C_PORT_DRP:

            // ROLE_CONTROL [0x1A] ([6] DRP = 1, [5:4] Rp Refer Macro, [3:2] CC1 = [1:0] CC2 = Rd)
            if(GET_TCPM_CC_RP_DEF_VALUE(ucPortIndex) == _TYPE_C_SRC_DEF_USB)
            {
                SET_TCPM_ROLE_CONTROL(ucPortIndex, _BIT6 | _BIT3 | _BIT1);

                SET_TCPM_CC_DEF_CUR(ucPortIndex, 90);  // 90 * 10mA = 900mA
            }
            else if(GET_TCPM_CC_RP_DEF_VALUE(ucPortIndex) == _TYPE_C_SRC_DEF_1P5A)
            {
                SET_TCPM_ROLE_CONTROL(ucPortIndex, _BIT6 | _BIT4 | _BIT3 | _BIT1);

                SET_TCPM_CC_DEF_CUR(ucPortIndex, 150);  // 150 * 10mA = 1.5A
            }
            else
            {
                SET_TCPM_ROLE_CONTROL(ucPortIndex, _BIT6 | _BIT5 | _BIT3 | _BIT1);

                SET_TCPM_CC_DEF_CUR(ucPortIndex, 300); // 300 * 10mA = 3.0A
            }

            ScalerTypeCTcpmTcpciSetByte(ucPortIndex, _TCPM_TCPCI_REG_ROLE_CTRL, GET_TCPM_ROLE_CONTROL(ucPortIndex));

            SET_TCPM_CC_FSM(ucPortIndex, _TCPM_CC_FSM_DRP_TOGGLE);

            break;

        default:

            // Other CC Operation Mode Need to be Implemented

            break;
    }
}

//--------------------------------------------------
// Description  : Type C TCPM CC Start FSM
// Input Value  : ucPortIndex
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmCcConnectionStart(BYTE ucPortIndex)
{
    // Enable ALERT.CC_STATUS
    ScalerTypeCTcpmAlertControl(ucPortIndex, (WORD)_TCPM_TCPCI_ALERT_CC_STATUS, _ENABLE);

    // Start Look 4 Connection
    ScalerTypeCTcpmTcpciSetByte(ucPortIndex, _TCPM_TCPCI_REG_COMMAND, _TCPM_TCPCI_CMD_LOOK_4_CONNECTION);
}

//--------------------------------------------------
// Description  : Sink Check Unattach
// Input Value  : ucPortIndex
// Output Value : _TRUE (Unattach) / _FALSE (Not Detect Unattach)
//--------------------------------------------------
BYTE ScalerTypeCTcpmCcSnkCheckUnattach(BYTE ucPortIndex)
{
    BYTE ucUnattachDetect = _FALSE;
    BYTE ucCcStatus = 0x00;

    // Read CC Status [0x1D] Info
    SET_TCPM_CC_STATUS(ucPortIndex, ScalerTypeCTcpmTcpciGetByte(ucPortIndex, _TCPM_TCPCI_REG_CC_STATUS));

    if(GET_TCPM_ORIENTATION(ucPortIndex) == _TYPE_C_ORIENTATION_UNFLIP)
    {
        // Un-Flip : ChecK CC1 Rp Value (CC_STATUS [0x1D] [1:0] CC1_STATE)
        ucCcStatus = (GET_TCPM_CC_STATUS(ucPortIndex) & _TCPM_TCPCI_CC_STAT_CC1_STATE);
    }
    else
    {
        // Flip : Check CC2 Rp Value (CC_STATUS [0x1D] [3:2] CC2_STATE)
        ucCcStatus = ((GET_TCPM_CC_STATUS(ucPortIndex) & _TCPM_TCPCI_CC_STAT_CC2_STATE) >> 2);
    }

    if(ucCcStatus == 0x00)
    {
        // CC Pin = Open (b'00), Wait for tPdDebounce and Re-Check
        ScalerTimerDelayXms(_TCPM_PD_DEBOUNCE_TIME);
        SET_TCPM_CC_STATUS(ucPortIndex, ScalerTypeCTcpmTcpciGetByte(ucPortIndex, _TCPM_TCPCI_REG_CC_STATUS));

        if(GET_TCPM_ORIENTATION(ucPortIndex) == _TYPE_C_ORIENTATION_UNFLIP)
        {
            // Un-Flip : ChecK CC1 Rp Value (CC_STATUS [0x1D] [1:0] CC1_STATE)
            ucCcStatus = (GET_TCPM_CC_STATUS(ucPortIndex) & _TCPM_TCPCI_CC_STAT_CC1_STATE);
        }
        else
        {
            // Flip : Check CC2 Rp Value (CC_STATUS [0x1D] [3:2] CC2_STATE)
            ucCcStatus = ((GET_TCPM_CC_STATUS(ucPortIndex) & _TCPM_TCPCI_CC_STAT_CC2_STATE) >> 2);
        }

        if(ucCcStatus == 0x00)
        {
            // Sink Unattach Proc
            CLR_TCPM_CC_SRC_DET(ucPortIndex);
            ucUnattachDetect = _TRUE;
        }
    }

    return ucUnattachDetect;
}

//--------------------------------------------------
// Description  : Type C TCPM CC Power Switch Process
// Input Value  : ucPortIndex, enumPowerAction
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmCcPowerSwitch(BYTE ucPortIndex, EnumPowerAction enumPowerAction)
{
    switch(enumPowerAction)
    {
        case _POWER_ACTION_AC_ON_TO_NORMAL:
        case _POWER_ACTION_AC_ON_TO_OFF:

            // Tcpm AC On Initial State
            SET_TCPM_CC_FW_STATE(ucPortIndex, _TCPM_CC_FW_UNATTACH);

            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Disconnect Both CC1 / CC2, and Wait 30ms (Should Be More Than tPDDebounce Max)
// Input Value  : ucPortIndex
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmCcDisconnect(BYTE ucPortIndex)
{
    // Set ROLE_CONTROL [0x1A] : Disable DRP, Rp Set to Default, CC1/2 Set to Open
    // [6] DRP = 0, [5:4] Rp Refer Macro = 00 (Rp-Def), [3:2] CC1 = [1:0] CC2 = Open (b'11)
    SET_TCPM_ROLE_CONTROL(ucPortIndex, 0x0F);
    ScalerTypeCTcpmTcpciSetByte(ucPortIndex, _TCPM_TCPCI_REG_ROLE_CTRL, GET_TCPM_ROLE_CONTROL(ucPortIndex));

    ScalerTimerDelayXms(30);
}

//--------------------------------------------------
// Description  : Set TCPM CC Function Support Option
// Input Value  : ucPortIndex, enumFunctionSupport
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmCcSetFunctionSupport(BYTE ucPortIndex, EnumTypeCFunctionSupport enumFunctionSupport)
{
    if(enumFunctionSupport == _TYPE_C_SUPPORT_NO_FUNCTION)
    {
        CLR_TCPM_CC_CONNECT_EN(ucPortIndex);
    }
    else
    {
        SET_TCPM_CC_CONNECT_EN(ucPortIndex);
    }
}

//--------------------------------------------------
// Description  : Update & Return CC Pin Resistor (Only For CC Pin, Not Vconn Pin)
// Input Value  : ucPortIndex
// Output Value : None
//--------------------------------------------------
BYTE ScalerTypeCTcpmCcDetResistor(BYTE ucPortIndex)
{
    BYTE ucCcResult = 0;
    BYTE ucCcStatus = ScalerTypeCTcpmTcpciGetByte(ucPortIndex, _TCPM_TCPCI_REG_CC_STATUS);

    // Only Update Resistor of CC Pin, Not Vconn Pin (Flip : [7:4] CC1, Un-Flip : [3:0] CC2)
    if(GET_TCPM_ORIENTATION(ucPortIndex) == _TYPE_C_ORIENTATION_UNFLIP)
    {
        if((ucCcStatus & _TCPM_TCPCI_CC_STAT_CC1_STATE) == (_BIT1 | _BIT0))
        {
            // Rp = Rp-3.0A (SinkTxOK)
            ucCcResult = _TYPE_C_DET_RP_3P0A;
        }
        else if((ucCcStatus & _TCPM_TCPCI_CC_STAT_CC1_STATE) == (_BIT1))
        {
            // Rp = Rp-1.5A (SinkTxNG)
            ucCcResult = _TYPE_C_DET_RP_1P5A;
        }
        else if((ucCcStatus & _TCPM_TCPCI_CC_STAT_CC1_STATE) == (_BIT0))
        {
            // Rp = Rp-Def
            ucCcResult = _TYPE_C_DET_RP_DEF;
        }
        else
        {
            // Rp = Open
            ucCcResult = _TYPE_C_DET_OPEN;
        }
    }
    else
    {
        if((ucCcStatus & _TCPM_TCPCI_CC_STAT_CC2_STATE) == (_BIT3 | _BIT2))
        {
            // Rp = Rp-3.0A (SinkTxOK)
            ucCcResult = _TYPE_C_DET_RP_3P0A;
        }
        else if((ucCcStatus & _TCPM_TCPCI_CC_STAT_CC2_STATE) == (_BIT3))
        {
            // Rp = Rp-1.5A (SinkTxNG)
            ucCcResult = _TYPE_C_DET_RP_1P5A;
        }
        else if((ucCcStatus & _TCPM_TCPCI_CC_STAT_CC2_STATE) == (_BIT2))
        {
            // Rp = Rp-Def
            ucCcResult = _TYPE_C_DET_RP_DEF;
        }
        else
        {
            // Rp = Open
            ucCcResult = _TYPE_C_DET_OPEN;
        }
    }

    return ucCcResult;
}

//--------------------------------------------------
// Description  : TypeC TCPM PD Initial
// Input Value  : ucPortIndex
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmPdInitial(BYTE ucPortIndex)
{
    // Enable PD Function
    SET_TCPM_PD_FUNCTION_EN(ucPortIndex);

    // Enable Alt. Mode Function (DFP can Start Flow / UFP can Resp. Alt. REQ)
    SET_TCPM_PD_ALT_MODE_FUNCTION(ucPortIndex);

    // Clear All Sys Events
    CLR_TCPM_PD_SYS_EVENT(ucPortIndex, _PD_SYS_EVENT_ALL);

    // Clear VDM Response Conflict Cnt
    CLR_TCPM_PD_VDM_RESP_CONFLICT_CNT(ucPortIndex);

    // Set UFP Product Type
#if(_TYPE_C_EMB_UFP_PRODUCT_TYPE == _VALUE_TYPE_C_UFP_PRODUCT_TYPE_DEFAULT)
    if(GET_TCPM_USB_TYPE(ucPortIndex) != _USB_NONE)
    {
        // With Usb Hub IC, UFP Product Type = PDUSB Hub
        SET_TCPM_PD_UFP_PRODUCT_TYPE(ucPortIndex, _TYPE_C_UFP_PRODUCT_TYPE_HUB);
    }
    else
    {
        // Otherwise, UFP Product Type = PDUSB Peripheral
        SET_TCPM_PD_UFP_PRODUCT_TYPE(ucPortIndex, _TYPE_C_UFP_PRODUCT_TYPE_PERIPHERAL);
    }
#elif(_TYPE_C_EMB_UFP_PRODUCT_TYPE == _VALUE_TYPE_C_UFP_PRODUCT_TYPE_UNDEFINED)
    SET_TCPM_PD_UFP_PRODUCT_TYPE(ucPortIndex, _TYPE_C_UFP_PRODUCT_TYPE_UNDEFINED);
#elif(_TYPE_C_EMB_UFP_PRODUCT_TYPE == _VALUE_TYPE_C_UFP_PRODUCT_TYPE_HUB)
    SET_TCPM_PD_UFP_PRODUCT_TYPE(ucPortIndex, _TYPE_C_UFP_PRODUCT_TYPE_HUB);
#elif(_TYPE_C_EMB_UFP_PRODUCT_TYPE == _VALUE_TYPE_C_UFP_PRODUCT_TYPE_PERIPHERAL)
    SET_TCPM_PD_UFP_PRODUCT_TYPE(ucPortIndex, _TYPE_C_UFP_PRODUCT_TYPE_PERIPHERAL);
#endif // End of #if(_TYPE_C_EMB_UFP_PRODUCT_TYPE == _VALUE_TYPE_C_UFP_PRODUCT_TYPE_DEFAULT)

    // Set DFP Product Type
    SET_TCPM_PD_DFP_PRODUCT_TYPE(ucPortIndex, _TYPE_C_DFP_PRODUCT_TYPE_UNDEFINED);
}

//--------------------------------------------------
// Description  : TypeC TCPM PD Reset
// Input Value  : ucPortIndex
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmPdReset(BYTE ucPortIndex)
{
    // -------------------- HW Clear, Disable or Reset to Default Value --------------------
    // 1. Disable PD Rcv Detect ([0x2F] : [5] HRST, [2] SOP", [1] SOP', [0] SOP)
    ScalerTypeCTcpmTcpciSetByte(ucPortIndex, _TCPM_TCPCI_REG_RCV_DETECT, 0x00);

    // 2. Disable BIST Mode
    if(GET_TCPM_PD_BIST_MODE(ucPortIndex) == _PD_BIST_TEST_DATA_MODE)
    {
        // TCPM Would Set TCPC_CONTROL [0x19], [1] = b'1 (BIST Test Data Mode) When Entering Test Data Mode
        // Disable Test Data Mode by Set TCPC_CONTROL [0x19], [1] = b'0
        SET_TCPM_TCPC_CONTROL(ucPortIndex, GET_TCPM_TCPC_CONTROL(ucPortIndex) & (~_BIT1));
        ScalerTypeCTcpmTcpciSetByte(ucPortIndex, _TCPM_TCPCI_REG_TCPC_CTRL, GET_TCPM_TCPC_CONTROL(ucPortIndex));
    }
    SET_TCPM_PD_BIST_MODE(ucPortIndex, _PD_BIST_MODE_NONE);

    // 3. Disable PD Tx/Rx Alert
    ScalerTypeCTcpmAlertControl(ucPortIndex, (WORD)(_TCPM_TCPCI_ALERT_RX_RCV_SOP | _TCPM_TCPCI_ALERT_RX_HRST | _TCPM_TCPCI_ALERT_TX_FAIL | _TCPM_TCPCI_ALERT_TX_DISCARD | _TCPM_TCPCI_ALERT_TX_SUCCESS | _TCPM_TCPCI_ALERT_RX_OVERFLOW), _DISABLE);

    // ------------------------- FW State & Counter & Flag Reset -------------------------
    // 4. Reset PD Related Macros
    // PD Initial States Setting
    SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_STATE_NONE);
    SET_TCPM_PD_CBL_STATE(ucPortIndex, _PD_CBL_STATE_NONE);
    SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_NONE);

    ScalerTypeCTcpmPdClrHpd(ucPortIndex);

#if(_PORT_CTRL_EMB_DP_TX_SUPPORT == _ON)
    if((GET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex) == _TYPE_C_DP_TX) && (GET_TCPM_PD_DPAM_CONFIG(ucPortIndex) == _PD_DP_CONFIG))
    {
        ScalerTypeCTcpmPdPushHpd(g_penumTypeCTcpmPort[ucPortIndex], _PD_HPD_LOW, 0);
    }
#endif

    CLR_TCPM_PD_DPAM_ATTENTION_WAIT(ucPortIndex);
    CLR_TCPM_PD_DPAM_ENTER(ucPortIndex);
    SET_TCPM_PD_DPAM_CONFIG(ucPortIndex, _PD_USB_CONFIG);
    CLR_TCPM_PD_DPAM_EXIT_REQ(ucPortIndex);
    CLR_TCPM_PD_PARTNER_INIT_ALT_MODE(ucPortIndex);
    CLR_TCPM_PD_PARTNER_ALT_SUPPORT(ucPortIndex);
    SET_TCPM_PD_HPD_STATUS(ucPortIndex, _LOW);
    SET_TCPM_PD_DPAM_PIN_ASSIGNMENT(ucPortIndex, _TYPE_C_PIN_ASSIGNMENT_NONE);
    CLR_TCPM_PD_DPAM_MULTI_FUNCTION_CHANGE(ucPortIndex);
    CLR_TCPM_PD_DPAM_MULTI_FUNCTION_CHANGE_DONE(ucPortIndex);

    // Reset Force Sending HPD IRQ Macros
    CLR_TCPM_PD_FORCE_HPD_IRQ(ucPortIndex);

    // Swith DP Lane Mapping
#if(_PORT_CTRL_EMB_DP_RX_SUPPORT == _ON)
    if(GET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex) == _TYPE_C_DP_RX)
    {
        ScalerDpPhyRxSetAltModeLaneMapping(ScalerTypeCPcbPortConvertToDx(g_penumTypeCTcpmPort[ucPortIndex]), GET_TCPM_PD_DPAM_PIN_ASSIGNMENT(ucPortIndex), GET_TCPM_ORIENTATION(ucPortIndex));
    }
#endif

#if(_PORT_CTRL_EMB_DP_TX_SUPPORT == _ON)
    if(GET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex) == _TYPE_C_DP_TX)
    {
        ScalerDpPhyTxSetAltModeLaneMapping(ScalerTypeCPcbPortConvertToPx(g_penumTypeCTcpmPort[ucPortIndex]), GET_TCPM_PD_DPAM_PIN_ASSIGNMENT(ucPortIndex), GET_TCPM_ORIENTATION(ucPortIndex));
    }
#endif

    // Cancel Timer Event
    ScalerTypeCTcpmPdUnattachCancelTimerEvent(ucPortIndex);

    // Reset Counters
    CLR_TCPM_PD_SRC_CAP_CNT(ucPortIndex);
    CLR_TCPM_PD_HARD_RST_CNT(ucPortIndex);
    CLR_TCPM_PD_CHECK_VBUS_CNT(ucPortIndex);
    CLR_TCPM_PD_CBL_DISC_ID_RETRY_CNT(ucPortIndex);
    CLR_TCPM_PD_PARTNER_VDM_NO_RESP_CNT(ucPortIndex);
    CLR_TCPM_PD_CBL_VDM_NO_RESP_CNT(ucPortIndex);
    CLR_TCPM_PD_VDM_BUSY_CNT(ucPortIndex);

    // Reset Flags
    CLR_TCPM_PD_GET_SNK_CAP_SENT(ucPortIndex);
    CLR_TCPM_PD_GET_SRC_CAP_SENT(ucPortIndex);
    CLR_TCPM_PD_PRS_REJECT(ucPortIndex);
    CLR_TCPM_PD_DRS_REJECT(ucPortIndex);
    CLR_TCPM_PD_VCS_REJECT(ucPortIndex);
    CLR_TCPM_PD_RCV_SRC_CAP(ucPortIndex);
    CLR_TCPM_PD_RCV_SNK_CAP(ucPortIndex);
    CLR_TCPM_PD_PRS_WAIT_FLAG(ucPortIndex);
    CLR_TCPM_PD_DRS_WAIT_FLAG(ucPortIndex);
    CLR_TCPM_PD_VCS_WAIT_FLAG(ucPortIndex);
    CLR_TCPM_PD_EXPLICIT_CONTRACT(ucPortIndex);
    SET_TCPM_PD_GET_SNK_CAP_WAIT_FLAG(ucPortIndex);
    CLR_TCPM_PD_PRS_PROCESSING(ucPortIndex);
    CLR_TCPM_PD_VDMMSG_WAIT_FLAG(ucPortIndex);
    CLR_TCPM_PD_VDM_BUSY_FLAG(ucPortIndex);
    CLR_TCPM_PD_HRST_PWR_OFF(ucPortIndex);
    SET_TCPM_PD_NEW_POWER_STATE(ucPortIndex, 0);
    SET_TCPM_PD_NEW_POWER_INDICATOR(ucPortIndex, 0);
    CLR_TCPM_PD_TYPE_OF_ALERT(ucPortIndex, _TYPE_C_TYPE_OF_ALERT_ALL);
    CLR_TCPM_PD_BAT_STATUS(ucPortIndex, _TYPE_C_BAT_ALL);
    SET_TCPM_PD_EXT_ALERT_EVENT(ucPortIndex, _TYPE_C_EXT_ALERT_EVENT_NONE);
    CLR_TCPM_PD_SYS_EVENT(ucPortIndex, _PD_SYS_EVENT_POWER_OCP | _PD_SYS_EVENT_POWER_OVP | _PD_SYS_EVENT_POWER_UVP | _PD_SYS_EVENT_VCONN_OCP);

#if(_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_0)
    SET_TCPM_PD_SPEC_VER(ucPortIndex, _PD_VERSION_3_0);
    SET_TCPM_PD_CBL_SPEC_VER(ucPortIndex, _PD_VERSION_3_0);
#else
    SET_TCPM_PD_SPEC_VER(ucPortIndex, _PD_VERSION_2_0);
    SET_TCPM_PD_CBL_SPEC_VER(ucPortIndex, _PD_VERSION_2_0);
#endif

    // Reset Cable Related Flags
    SET_TCPM_PD_CBL_MAX_CUR(ucPortIndex, _PD_DEFAULT_MAX_CUR);
    SET_TCPM_PD_CBL_PD_CAPABILITY(ucPortIndex, _TYPE_C_CABLE_PD_CAP_UNCONFIRMED);
    SET_TCPM_PD_CBL_PRODUCT_TYPE(ucPortIndex, _PD_PRODUCT_TYPE_UNDEFINED);
    CLR_TCPM_PD_CBL_MODAL_OPERATION_SUPPORT(ucPortIndex);
    SET_TCPM_PD_CBL_CONNECTOR_TYPE(ucPortIndex, _PD_CABLE_CONNECTOR_TYPE_UNCONFIRMED);
    CLR_TCPM_PD_CBL_EPR_MODE_CAPABLE(ucPortIndex);
    SET_TCPM_PD_CBL_TERMINATION_TYPE(ucPortIndex, _PD_CBL_TERMINATION_TYPE_UNDEFINED);
    SET_TCPM_PD_CBL_VCONN_REQUIRED(ucPortIndex);
    SET_TCPM_PD_CBL_MAX_VOL(ucPortIndex, 200);
    CLR_TCPM_PD_CBL_SBU_SUPPORT(ucPortIndex);
    SET_TCPM_PD_CBL_SBU_TYPE(ucPortIndex, _PD_CBL_SBU_TYPE_UNDEFINED);
    SET_TCPM_PD_CBL_USB_HIGHEST_SPEED(ucPortIndex, _PD_CBL_USB_2_ONLY);
    CLR_TCPM_PD_CBL_VBUS_THROUGH(ucPortIndex);
    CLR_TCPM_PD_CBL_SOP_PP_SUPPORT(ucPortIndex);
    SET_TCPM_PD_CBL_U3_TO_U0_TRANSITION_MODE(ucPortIndex, _PD_CBL_U3_TO_U0_UNDEFINED);
    CLR_TCPM_PD_CBL_USB_4_SUPPORT(ucPortIndex);
    CLR_TCPM_PD_CBL_USB_3_2_SUPPORT(ucPortIndex);
    SET_TCPM_PD_CBL_LANES_SUPPORT(ucPortIndex, _PD_CBL_USB_LANES_SUPPORT_UNDEFINED);
    CLR_TCPM_PD_CBL_CHARGE_THROUGH_SUPPORT(ucPortIndex);
    CLR_TCPM_PD_CBL_SOFT_RESET_REQUIRED(ucPortIndex);

#if(_TYPE_C_SVDM_VERSION >= _SVDM_VERSION_2_1)
    // Default Set to 2.1 and Downgrade to 2.0 if Cable Only Support < 2.1
    SET_TCPM_PD_CBL_SVDM_VERSION(ucPortIndex, _PD_SVDM_VER_2_1);
#else
    SET_TCPM_PD_CBL_SVDM_VERSION(ucPortIndex, _PD_SVDM_VER_2_0_EARLIER);
#endif

#if(_TYPE_C_DPAM_VERSION >= _DPAM_VERSION_2_1)
    SET_TCPM_PD_CBL_DPAM_VERSION(ucPortIndex, _PD_DPAM_VER_2_0_EARLIER);
    SET_TCPM_PD_CBL_ENTER_DP_MODE_SUPPORT(ucPortIndex);
    CLR_TCPM_PD_CBL_DP_SVID_SUPPORT(ucPortIndex);
    CLR_TCPM_PD_CBL_DP_MODE_INFO_RECEIVED(ucPortIndex);
    CLR_TCPM_PD_CBL_TBT3_SVID_SUPPORT(ucPortIndex);
    SET_TCPM_PD_CBL_PIN_ASSIGNMENT(ucPortIndex, _PD_CBL_PIN_ASSIGNMENT_UNCONFIRMED);
    SET_TCPM_PD_CBL_TBT3_PRODUCT_TYPE(ucPortIndex, _PD_CBL_TBT3_PRODUCT_TYPE_UNCONFIRMED);
    SET_TCPM_PD_CBL_TBT3_DIRECTION(ucPortIndex, _PD_CBL_TBT3_DIRECTION_UNCONFIRMED);
    CLR_TCPM_PD_CBL_TBT3_RETIMER(ucPortIndex);
    CLR_TCPM_PD_CBL_TBT3_OPTICAL(ucPortIndex);
    SET_TCPM_PD_CBL_TBT3_ROUNDED_SUPPORT(ucPortIndex, _PD_CBL_TBT3_ROUNDED_SUPPORT_UNCONFIRMED);
    SET_TCPM_PD_CBL_TBT3_SPEED(ucPortIndex, _PD_CBL_TBT3_SPEED_UNCONFIRMED);
    SET_TCPM_PD_CBL_ACTIVE_COMPONENT(ucPortIndex, _PD_CBL_COMPONENT_PASSIVE);
    CLR_TCPM_PD_CBL_UHBR13P5_SUPPORT(ucPortIndex);
    SET_TCPM_PD_CBL_MAX_DP_RATE(ucPortIndex, _PD_CBL_MAX_DP_RATE_UNCONFIRMED);
#endif

    // Reset All EPR Flag
    CLR_TCPM_PD_ENTER_EPR_MODE_FLOW(ucPortIndex);
    CLR_TCPM_PD_EPR_MODE(ucPortIndex);
    SET_TCPM_PD_EPR_MODE_ACTION(ucPortIndex, _PD_EPR_MODE_RESERVED);
    SET_TCPM_PD_ENTER_EPR_FAILED_REASON(ucPortIndex, _PD_EPR_MODE_ENTER_FAILED_UNKNOWN);
    SET_TCPM_PD_PARTNER_EPR_SINK_PDP(ucPortIndex, 0);

    // Clear All Port Partner Info
    SET_TCPM_PD_PARTNER_DRP(ucPortIndex, _FALSE);
    SET_TCPM_PD_PARTNER_DRD(ucPortIndex, _TRUE);
    CLR_TCPM_PD_PARTNER_SUSPEND(ucPortIndex);
    CLR_TCPM_PD_PARTNER_EXT_PWR(ucPortIndex);
    CLR_TCPM_PD_PARTNER_USB_CAP(ucPortIndex);
    CLR_TCPM_PD_PARTNER_UNCHK(ucPortIndex);
    SET_TCPM_PD_PARTNER_EPR_CAP(ucPortIndex, _FALSE);
    CLR_TCPM_PD_PARTNER_HIGH_CAP(ucPortIndex);
    CLR_TCPM_PD_PARTNER_FRS_CUR(ucPortIndex);
    SET_TCPM_PD_PARTNER_SRC_CAP_CNT(ucPortIndex, 0);
    SET_TCPM_PD_PARTNER_SNK_CAP_CNT(ucPortIndex, 0);
    SET_TCPM_PD_PARTNER_NEW_POWER_STATE(ucPortIndex, 0);
    SET_TCPM_PD_PARTNER_NEW_POWER_INDICATOR(ucPortIndex, 0);
    SET_TCPM_PD_PARTNER_TYPE_OF_ALERT(ucPortIndex, _TYPE_C_TYPE_OF_ALERT_NONE);
    SET_TCPM_PD_PARTNER_BAT_STATUS(ucPortIndex, _TYPE_C_BAT_NONE);
    SET_TCPM_PD_PARTNER_EXT_ALERT_EVENT(ucPortIndex, _TYPE_C_EXT_ALERT_EVENT_NONE);

#if(_TYPE_C_SVDM_VERSION >= _SVDM_VERSION_2_1)
    // Default Set to 2.1 and Downgrade to 2.0 if Port Partner Only Support < 2.1
    SET_TCPM_PD_PARTNER_SVDM_VERSION(ucPortIndex, _PD_SVDM_VER_2_1);
#else
    SET_TCPM_PD_PARTNER_SVDM_VERSION(ucPortIndex, _PD_SVDM_VER_2_0_EARLIER);
#endif

#if(_TYPE_C_DPAM_VERSION >= _DPAM_VERSION_2_1)
    // Default Set to 2.1 and Downgrade to 2.0 if Port Partner Only Support < 2.1
    SET_TCPM_PD_PARTNER_DPAM_VERSION(ucPortIndex, _PD_DPAM_VER_2_1_HIGHER);
#else
    SET_TCPM_PD_PARTNER_DPAM_VERSION(ucPortIndex, _PD_DPAM_VER_2_0_EARLIER);
#endif

    // Reset Port Partner DP Status Related Flags
    SET_TCPM_PD_PARTNER_DPAM_CONNECT_STATUS(ucPortIndex, _PD_DP_CONNECT_NONE);
    CLR_TCPM_PD_PARTNER_DPAM_POWER_LOW(ucPortIndex);
    CLR_TCPM_PD_PARTNER_DPAM_FUNCTION_ENABLE(ucPortIndex);
    CLR_TCPM_PD_PARTNER_DPAM_MULTI_FUNCTION(ucPortIndex);
    CLR_TCPM_PD_PARTNER_DPAM_USB_CONFIG_REQUEST(ucPortIndex);
    CLR_TCPM_PD_PARTNER_DPAM_EXIT_REQ(ucPortIndex);
    SET_TCPM_PD_PARTNER_HPD_TYPE(ucPortIndex, _PD_HPD_NONE);
#if(_TYPE_C_DPAM_VERSION >= _DPAM_VERSION_2_1)
    CLR_TCPM_PD_PARTNER_DPAM_NO_SUSPEND(ucPortIndex);
#endif

#if(_PORT_CTRL_EMB_PD3_PPS_SUPPORT == _ON)
    CLR_TCPM_PD_REQ_PPS_VOL_SMALL_STEP(ucPortIndex);
#endif

    CLR_TCPM_PD_REQ_AVS_VOL_SMALL_STEP(ucPortIndex);
}

//--------------------------------------------------
// Description  : Type C TCPM PD Handler
// Input Value  : ucPortIndex
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmPdHandler(BYTE ucPortIndex)
{
    if(GET_TCPM_PD_TIMER_EVENT_VALID(ucPortIndex) == _TRUE)
    {
        // Disable Rx IRQ
        ScalerTypeCTcpmRxIntControl(ucPortIndex, _DISABLE);

        // Active Timer Event and Clear Timer Event Valid
        ScalerTypeCTcpmActiveTimerEvent(ucPortIndex, GET_TCPM_PD_TIMER_EVENT_CNT(ucPortIndex), GET_TCPM_PD_TIMER_EVENT_ID(ucPortIndex));
        CLR_TCPM_PD_TIMER_EVENT_VALID(ucPortIndex);

        // Enable Rx IRQ
        ScalerTypeCTcpmRxIntControl(ucPortIndex, _ENABLE);
    }

    switch(GET_TCPM_PD_FW_STATE(ucPortIndex))
    {
        // ------------------------ Source/Sink Establish Power Contract in Interrupt ---------------
        // ------------------------ Source/Sink Ready to Initaite AMS Flow --------------------------
        case _PD_SRC_READY:
        case _PD_SNK_READY:

            // Process On-Going AMS Flow or Initiate New AMS According to Latest Status
            ScalerTypeCTcpmPdReadyStateProc(ucPortIndex);

            break;

        // ----------------------------- Source / Sink Hard Reset Flow ------------------------------
        case _PD_HARDRESET:

            if(GET_TCPM_POWER_ROLE(ucPortIndex) == _PD_POWER_SRC)
            {
                // If Vbus Turned Off, Wait 0.66~1s and Turn On Power to vSafe5v
                if((GET_TCPM_PD_HRST_PWR_OFF(ucPortIndex) == _FALSE) && (ScalerTypeCTcpmGetVbusVoltage(ucPortIndex) <= _TCPM_VSAFE0V_UP_BND))
                {
                    // Turn Off Vbus Discharge
                    ScalerTypeCTcpmVbusDischargeCtrl(ucPortIndex, _OFF);

                    // Reset PD : WARNING !!! PD Must Reset Before Avtive TURN_ON_POWER Timer , Otherwise, Timer Would Be Canceled
                    ScalerTypeCTcpmPdReset(ucPortIndex);

                    // Set Hard Reset Turn Off Power Flag (Clr When Send/Rcv Hard Reset), and Turn On Power Later
                    SET_TCPM_PD_HRST_PWR_OFF(ucPortIndex);
                    ScalerTypeCTcpmActiveTimerEvent(ucPortIndex, _SRC_RECOVER_TIMER, _SCALER_TIMER_EVENT_TCPM_SRC_TURN_ON_POWER);

                    // Set Vbus_Alarm_H Thr to Check Vsafe5V
                    ScalerTypeCTcpmTcpciSetByte(ucPortIndex, _TCPM_TCPCI_REG_VOL_ALARM_H, GET_TCPCI_VOLTAGE_CODE(475));

                    // Enable ALERT.VBUS_ALRM_H
                    ScalerTypeCTcpmAlertControl(ucPortIndex, (WORD)_TCPM_TCPCI_ALERT_VBUS_ALRM_H, _ENABLE);

                    // Enable Vbus Voltage Alarm Detection (Can be Enable When Initial ?)
                    SET_TCPM_POWER_CONTROL(ucPortIndex, GET_TCPM_POWER_CONTROL(ucPortIndex) & (~_BIT5));
                    ScalerTypeCTcpmTcpciSetByte(ucPortIndex, _TCPM_TCPCI_REG_PWR_CTRL, GET_TCPM_POWER_CONTROL(ucPortIndex));
                }
            }
            else
            {
                if((GET_TCPM_PD_HRST_PWR_OFF(ucPortIndex) == _FALSE) && (ScalerTypeCTcpmGetVbusVoltage(ucPortIndex) < _TCPM_VSAFE5V_LOW_BND))
                {
                    ScalerTypeCTcpmPdReset(ucPortIndex);

                    // Set Hard Reset Turn Off Power Flag
                    SET_TCPM_PD_HRST_PWR_OFF(ucPortIndex);

                    // Set Vbus_Alarm_H Thr to Check Vsafe5V
                    ScalerTypeCTcpmTcpciSetByte(ucPortIndex, _TCPM_TCPCI_REG_VOL_ALARM_H, GET_TCPCI_VOLTAGE_CODE(475));

                    // Enable ALERT.VBUS_ALRM_H
                    ScalerTypeCTcpmAlertControl(ucPortIndex, (WORD)_TCPM_TCPCI_ALERT_VBUS_ALRM_H, _ENABLE);

                    // Enable Vbus Voltage Alarm Detection
                    SET_TCPM_POWER_CONTROL(ucPortIndex, GET_TCPM_POWER_CONTROL(ucPortIndex) & (~_BIT5));
                    ScalerTypeCTcpmTcpciSetByte(ucPortIndex, _TCPM_TCPCI_REG_PWR_CTRL, GET_TCPM_POWER_CONTROL(ucPortIndex));
                }
                else
                {
                    // (On-Semi) : CC Open When Sending Message, TCPC Will Not Generate CC Status Change ALERT
                }
            }

            break;

        // --------------------------- Source / Sink Main Loop Idle State ---------------------------
        case _PD_SRC_WDINT_SEND_CAP:
        case _PD_SRC_INT_SEND_CAP:
        case _PD_SRC_INT_WAIT_REQ:
        case _PD_SRC_INT_SEND_ACCEPT_REQ:
        case _PD_SRC_INT_SEND_REJECT_REQ:
        case _PD_SRC_INT_SEND_WAIT_REQ:
        case _PD_SRC_WDINT_TRANSIT_POWER:
        case _PD_SRC_WDINT_SEND_PSRDY:
        case _PD_SRC_INT_SEND_PSRDY:
        case _PD_SNK_START_UP:
        case _PD_SNK_INT_WAIT_SRC_CAP:
        case _PD_SNK_INT_SEND_REQUEST:
        case _PD_SNK_INT_WAIT_REQ_RESP:
        case _PD_SNK_INT_WAIT_PS_RDY:
        case _PD_INT_SEND_SOFTRESET:
        case _PD_INT_WAIT_SOFTRESET_RESP:
        case _PD_INT_SEND_SOFTRESET_RESP:
        case _PD_NO_RESPONSE:
        default:

            if((GET_TCPM_PD_SYS_EVENT(ucPortIndex) & (_PD_SYS_EVENT_POWER_OCP | _PD_SYS_EVENT_POWER_OVP | _PD_SYS_EVENT_POWER_UVP | _PD_SYS_EVENT_VCONN_OCP)) != _PD_SYS_EVENT_NONE)
            {
                ScalerTypeCTcpmPdOcpOvpProc(ucPortIndex);
            }

            break;
    }
}

//--------------------------------------------------
// Description  : Process For SRC/SNK_READY State
// Input Value  : ucPortIndex
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmPdReadyStateProc(BYTE ucPortIndex)
{
    // Wait For Source to do PS_RDY or Alt. Mode Flow, Otherwise, Initiate Certain Flow
    // 1. If (DFP) : DR_Swap => Vconn Swap => Alt. Mode => Get_Snk_Cap => PR_SWAP
    // 2. If (UFP) : Get_Snk_Cap => PR_Swap

    switch(GET_TCPM_PD_SUB_STATE(ucPortIndex))
    {
        case _PD_SUB_SRC_READY:

            // Disable Rx IRQ
            ScalerTypeCTcpmRxIntControl(ucPortIndex, _DISABLE);

            if(GET_TCPM_PD_AMS_STATUS(ucPortIndex) == _PD_AMS_NONE)
            {   // Src Init Message Only When No AMS is On-Going
                ScalerTypeCTcpmPdSrcReadyProc(ucPortIndex);
            }

            // Enable Rx IRQ
            ScalerTypeCTcpmRxIntControl(ucPortIndex, _ENABLE);

#if(_TYPE_C_MODAL_OPERATION_SUPPORT == _ON)
#if(_PORT_CTRL_EMB_DP_ALT_MODE_SUPPORT == _ON)
            // Send VDM Msg After Enable Alert IRQ
            if((GET_TCPM_PD_SUB_STATE(ucPortIndex) == _PD_SUB_SEND_DP_VDM_REQ) || (GET_TCPM_PD_SUB_STATE(ucPortIndex) == _PD_SUB_SEND_CBL_DP_VDM_REQ))
            {
                if(GET_TCPM_DATA_ROLE(ucPortIndex) == _PD_DATA_DFP)
                {
                    ScalerTypeCTcpmPdDpAltModeDfpSendMsg(ucPortIndex);
                }
                else
                {
                    ScalerTypeCTcpmPdDpAltModeUfpSendMsg(ucPortIndex);
                }
            }
#endif
#endif

            break;

        case _PD_SUB_SNK_READY:

            // Disable Rx IRQ
            ScalerTypeCTcpmRxIntControl(ucPortIndex, _DISABLE);

            if(GET_TCPM_PD_AMS_STATUS(ucPortIndex) == _PD_AMS_NONE)
            {   // Src Init Message Only When No AMS is On-Going
                ScalerTypeCTcpmPdSnkReadyProc(ucPortIndex);
            }

            // To Fix [TD.PD.PHY.E18]
            // If in BIST Mode, Rcv Message Int will not be Enabled
            if(GET_TCPM_PD_SUB_STATE(ucPortIndex) != _PD_SUB_BIST_MODE)
            {
                // Enable Rx IRQ
                ScalerTypeCTcpmRxIntControl(ucPortIndex, _ENABLE);
            }

#if(_TYPE_C_MODAL_OPERATION_SUPPORT == _ON)
#if(_PORT_CTRL_EMB_DP_ALT_MODE_SUPPORT == _ON)
            // Send VDM Msg After Enable Alert IRQ
            if((GET_TCPM_PD_SUB_STATE(ucPortIndex) == _PD_SUB_SEND_DP_VDM_REQ) || (GET_TCPM_PD_SUB_STATE(ucPortIndex) == _PD_SUB_SEND_CBL_DP_VDM_REQ))
            {
                if(GET_TCPM_DATA_ROLE(ucPortIndex) == _PD_DATA_DFP)
                {
                    ScalerTypeCTcpmPdDpAltModeDfpSendMsg(ucPortIndex);
                }
                else
                {
                    ScalerTypeCTcpmPdDpAltModeUfpSendMsg(ucPortIndex);
                }
            }
#endif
#endif

            break;

        case _PD_SUB_SEND_GET_SRC_CAP:

            if(ScalerTypeCTcpmPdTxAvaliable(ucPortIndex) == _TRUE)
            {
                // Send "Get Src Cap" and Set Flag
                SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);
                ScalerTypeCTcpmPdSendMsg(ucPortIndex, _PD_SOP_PKT, _PD_CMD_GET_SRC_CAP, _PD_VDM_CMD_RESERVED);
            }

            break;

        case _PD_SUB_SEND_GET_SNK_CAP:

            if(ScalerTypeCTcpmPdTxAvaliable(ucPortIndex) == _TRUE)
            {
                // Send "Get Snk Cap" and Set Flag
                SET_TCPM_PD_GET_SNK_CAP_SENT(ucPortIndex);
                SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);
                ScalerTypeCTcpmPdSendMsg(ucPortIndex, _PD_SOP_PKT, _PD_CMD_GET_SNK_CAP, _PD_VDM_CMD_RESERVED);
            }

            break;

        case _PD_SUB_SEND_SRC_CAP:

            if(ScalerTypeCTcpmPdTxAvaliable(ucPortIndex) == _TRUE)
            {
                // Send "Src Cap" and Set Flag
                SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);
                ScalerTypeCTcpmPdSendMsg(ucPortIndex, _PD_SOP_PKT, _PD_CMD_SRC_CAP, _PD_VDM_CMD_RESERVED);
            }

            break;

        case _PD_SUB_CABLE_PROC:

            if(ScalerTypeCTcpmPdTxAvaliable(ucPortIndex) == _TRUE)
            {
                switch(GET_TCPM_PD_CBL_STATE(ucPortIndex))
                {
                    case _PD_CBL_SEND_SOFT_RST:

                        // Send Soft Reset(SOP') to Reset Cable
                        SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_BY_STATE);
                        ScalerTypeCTcpmPdSendSoftRst(ucPortIndex, _PD_SOP_P_PKT);

                        break;

                    case _PD_CBL_SEND_DISCOVER_ID:

                        // Send Discover ID (SOP') to Get Cable Info
                        SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_BY_STATE);
                        ScalerTypeCTcpmPdSendMsg(ucPortIndex, _PD_SOP_P_PKT, _PD_CMD_VDM, _PD_VDM_CMD_DISCOVER_ID_REQ);

                        break;

                    default:

                        break;
                }
            }

            break;

        case _PD_SUB_SEND_PR_SWAP:

            if(ScalerTypeCTcpmPdTxAvaliable(ucPortIndex) == _TRUE)
            {
                // Send "PR SWAP" and Set Flag
                SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);
                ScalerTypeCTcpmPdSendMsg(ucPortIndex, _PD_SOP_PKT, _PD_CMD_PR_SWAP, _PD_VDM_CMD_RESERVED);
            }

            break;

        case _PD_SUB_SEND_SRC_OFF_PSRDY:

            // Disable Rx Int
            ScalerTypeCTcpmRxIntControl(ucPortIndex, _DISABLE);

#if(_PORT_CTRL_EMB_PD3_PPS_SUPPORT == _ON)
            if(GET_TCPM_PD_PPS_SUPPORT(ucPortIndex) == _ON)
            {
                // Cancel TimerEvent for PPS PDO
                ScalerTypeCTcpmCancelTimerEvent(ucPortIndex, _SCALER_TIMER_EVENT_TCPM_PPS_TIMEOUT);
            }
#endif

            // When Vubs is Turned Off
            // 1. Swith Rp -> Rd  2. Disable Vbus Discharge  3. Send PS_RDY Message  4. Active Timer to Wait Vbus On
            if(ScalerTypeCTcpmGetVbusVoltage(ucPortIndex) <= _TCPM_VSAFE0V_UP_BND)
            {
                // 1. Disable Vbus Det
                ScalerTypeCTcpmVbusDetCtrl(ucPortIndex, _DISABLE);

                // 2. Disable ALERT.CC_STATUS to Avoid Unattach
                ScalerTypeCTcpmAlertControl(ucPortIndex, (WORD)_TCPM_TCPCI_ALERT_CC_STATUS, _DISABLE);

                // 3. Change Rd -> Rp (Set CC State to Sink)
                ScalerTypeCTcpmSwitchPowerRole(ucPortIndex, _PD_POWER_SNK);

                // 4. Disable Vbus Discharge
                ScalerTypeCTcpmVbusDischargeCtrl(ucPortIndex, _OFF);

                // 5. Change PD Power Role to Sink
                SET_TCPM_POWER_ROLE(ucPortIndex, _PD_POWER_SNK);

                // 6. Set Message Header for GoodCRC Reply
                ScalerTypeCTcpmPdUpdateGoodCRCInfo(ucPortIndex);

                // 7. Send PS_RDY
                SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_HARD_RESET);
                ScalerTypeCTcpmPdSendMsg(ucPortIndex, _PD_SOP_PKT, _PD_CMD_PS_RDY, _PD_VDM_CMD_RESERVED);

#if(_PORT_CTRL_EMB_DP_TX_SUPPORT == _ON)
                if(GET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex) == _TYPE_C_DP_TX)
                {
                    if(GET_TCPM_DATA_ROLE(ucPortIndex) == _PD_DATA_DFP)
                    {
                        CLR_TCPM_PD_PARTNER_VDM_NO_RESP_CNT(ucPortIndex);
                        CLR_TCPM_PD_CBL_VDM_NO_RESP_CNT(ucPortIndex);
                    }
                    else
                    {
                        CLR_TCPM_PD_VCS_REJECT(ucPortIndex);
                        CLR_TCPM_PD_DRS_REJECT(ucPortIndex);
                        CLR_TCPM_PD_PRS_REJECT(ucPortIndex);
                    }
                }
#endif
            }
            else
            {
                // Only Enable Rx Int When No Message Sent (SendMsg Should Enable in Tx Done)
                ScalerTypeCTcpmRxIntControl(ucPortIndex, _ENABLE);
            }

            break;

        case _PD_SUB_SEND_DR_SWAP:

            if(ScalerTypeCTcpmPdTxAvaliable(ucPortIndex) == _TRUE)
            {
                // Send "DR SWAP" and Set Flag
                SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);
                ScalerTypeCTcpmPdSendMsg(ucPortIndex, _PD_SOP_PKT, _PD_CMD_DR_SWAP, _PD_VDM_CMD_RESERVED);
            }

            break;

        case _PD_SUB_SEND_VCONN_SWAP:

            if(ScalerTypeCTcpmPdTxAvaliable(ucPortIndex) == _TRUE)
            {
                // Send "DR SWAP" and Set Flag
                SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);
                ScalerTypeCTcpmPdSendMsg(ucPortIndex, _PD_SOP_PKT, _PD_CMD_VCONN_SWAP, _PD_VDM_CMD_RESERVED);
            }

            break;

        case _PD_SUB_BIST_MODE:

            // Remove CTS TD.PD.PHY.E16 Valid Hard Reset Framing FW Solution

            break;

#if(_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_0)
        // [MQP] : PROT-SNK3-STATUS(Rev3.0), Shall Initiate GET_STATUS Msg. When SnkTXOK
        case _PD_SUB_SEND_GET_STATUS:

            if(ScalerTypeCTcpmPdTxAvaliable(ucPortIndex) == _TRUE)
            {
                // Send "Get_status" and Set Flag
                SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);
                ScalerTypeCTcpmPdSendMsg(ucPortIndex, _PD_SOP_PKT, _PD_CMD_GET_STATUS, _PD_VDM_CMD_RESERVED);
            }

            break;

        case _PD_SUB_SEND_ALERT:

            if(ScalerTypeCTcpmPdTxAvaliable(ucPortIndex) == _TRUE)
            {
#if(_TYPE_C_PMIC_OCP_OVP_PROCESS_OPTION == _TYPE_C_PMIC_PROCESS_OPTION_HARD_RESET)
                if((GET_TCPM_PD_SYS_EVENT(ucPortIndex) & (_PD_SYS_EVENT_POWER_OCP | _PD_SYS_EVENT_POWER_OVP)) != _PD_SYS_EVENT_NONE)
                {
                    // Active Timer Event For Receiving Subsequent AMS, ex: Get_Status Msg., Timeout : Hard Reset
                    ScalerTypeCTcpmActiveTimerEvent(ucPortIndex, _ALERT_WAIT_TIMER, _SCALER_TIMER_EVENT_TCPM_SEND_HARD_RST);
                }
#endif

                // Send "Alert" and Set Flag
                SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);
                ScalerTypeCTcpmPdSendMsg(ucPortIndex, _PD_SOP_PKT, _PD_CMD_ALERT, _PD_VDM_CMD_RESERVED);
            }

            break;

        case _PD_SUB_INT_SEND_NOT_SUPPORT:
#endif  // #if(_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_0)
        case _PD_SUB_INT_SEND_SRC_CAP:
        case _PD_SUB_INT_SEND_SNK_CAP:
        case _PD_SUB_INT_SEND_REJECT:
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Process For SRC_READY State
// Input Value  : ucPortIndex
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmPdSrcReadyProc(BYTE ucPortIndex)
{
    if((GET_TCPM_PD_SYS_EVENT(ucPortIndex) & _PD_SYS_EVENT_SEND_HARD_RESET) == _PD_SYS_EVENT_SEND_HARD_RESET)
    {
        ScalerTypeCTcpmPdSendHardRst(ucPortIndex);
        CLR_TCPM_PD_SYS_EVENT(ucPortIndex, _PD_SYS_EVENT_SEND_HARD_RESET);
    }
    else if((GET_TCPM_PD_SYS_EVENT(ucPortIndex) & (_PD_SYS_EVENT_POWER_OCP | _PD_SYS_EVENT_POWER_OVP | _PD_SYS_EVENT_POWER_UVP | _PD_SYS_EVENT_VCONN_OCP)) != _PD_SYS_EVENT_NONE)
    {
        ScalerTypeCTcpmPdOcpOvpProc(ucPortIndex);
    }
    else
    {
#if(_PORT_CTRL_EMB_DP_RX_SUPPORT == _ON)
        if(GET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex) == _TYPE_C_DP_RX)
        {
            ScalerTypeCTcpmPdSrcReadyDpRxProc(ucPortIndex);
        }
#endif

#if(_PORT_CTRL_EMB_DP_TX_SUPPORT == _ON)
        if(GET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex) == _TYPE_C_DP_TX)
        {
            ScalerTypeCTcpmPdSrcReadyDpTxProc(ucPortIndex);
        }
#endif
    }
}

//--------------------------------------------------
// Description  : Process For SNK_READY State
// Input Value  : EnumTypeCPcbPort --> TypeC Port
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmPdSnkReadyProc(BYTE ucPortIndex)
{
    if((GET_TCPM_PD_SYS_EVENT(ucPortIndex) & _PD_SYS_EVENT_SEND_HARD_RESET) == _PD_SYS_EVENT_SEND_HARD_RESET)
    {
        ScalerTypeCTcpmPdSendHardRst(ucPortIndex);
        CLR_TCPM_PD_SYS_EVENT(ucPortIndex, _PD_SYS_EVENT_SEND_HARD_RESET);
    }
    else if((GET_TCPM_PD_SYS_EVENT(ucPortIndex) & (_PD_SYS_EVENT_POWER_OCP | _PD_SYS_EVENT_POWER_OVP | _PD_SYS_EVENT_POWER_UVP | _PD_SYS_EVENT_VCONN_OCP)) != _PD_SYS_EVENT_NONE)
    {
        ScalerTypeCTcpmPdOcpOvpProc(ucPortIndex);
    }
    else
    {
#if(_PORT_CTRL_EMB_DP_RX_SUPPORT == _ON)
        if(GET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex) == _TYPE_C_DP_RX)
        {
            ScalerTypeCTcpmPdSnkReadyDpRxProc(ucPortIndex);
        }
#endif

#if(_PORT_CTRL_EMB_DP_TX_SUPPORT == _ON)
        if(GET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex) == _TYPE_C_DP_TX)
        {
            ScalerTypeCTcpmPdSnkReadyDpTxProc(ucPortIndex);
        }
#endif
    }
}

#if(_PORT_CTRL_EMB_DP_RX_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Process For SRC_READY DP_RX State
// Input Value  : ucPortIndex
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmPdSrcReadyDpRxProc(BYTE ucPortIndex)
{
    // 1. DFP : Try to Discover Cable First ,then Get Sink Capability, Do DR_SWAP, If Un-Avaliable, Initiate Alt. Mode
    // 2. UFP : Ultimate Goal, Wait For Partner to Initaite Alt. Mode
    if(GET_TCPM_DATA_ROLE(ucPortIndex) == _PD_DATA_DFP)
    {
        if((GET_TCPM_PD_VCS_REJECT(ucPortIndex) == _FALSE) && (GET_TCPM_VCONN_ROLE(ucPortIndex) == _PD_VCONN_NOT_SRC) && (GET_TCPM_PD_CBL_PD_CAPABILITY(ucPortIndex) == _TYPE_C_CABLE_PD_CAP_UNCONFIRMED))
        {
            if(GET_TCPM_PD_VCS_WAIT_FLAG(ucPortIndex) == _FALSE)
            {
                SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_SEND_VCONN_SWAP);
            }
        }
        else if((GET_TCPM_VCONN_ROLE(ucPortIndex) == _PD_VCONN_SRC) && (GET_TCPM_PD_CBL_PD_CAPABILITY(ucPortIndex) == _TYPE_C_CABLE_PD_CAP_UNCONFIRMED))
        {
            if(GET_TCPM_PD_CBL_SOFT_RESET_REQUIRED(ucPortIndex) == _TRUE)
            {
                CLR_TCPM_PD_CBL_SOFT_RESET_REQUIRED(ucPortIndex);

                SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_CABLE_PROC);
                SET_TCPM_PD_CBL_STATE(ucPortIndex, _PD_CBL_SEND_SOFT_RST);
            }
            else
            {
                if(GET_TCPM_PD_VDM_BUSY_FLAG(ucPortIndex) == _FALSE)
                {
                    SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_CABLE_PROC);
                    SET_TCPM_PD_CBL_STATE(ucPortIndex, _PD_CBL_SEND_DISCOVER_ID);
                }
            }
        }
        else if((GET_TCPM_PD_DFP_SWAP_TO_UFP(ucPortIndex) == _TRUE) && (GET_TCPM_PD_DRS_REJECT(ucPortIndex) == _FALSE))
        {
            if(GET_TCPM_PD_GET_SNK_CAP_SENT(ucPortIndex) == _FALSE)
            {
                if(GET_TCPM_PD_GET_SNK_CAP_WAIT_FLAG(ucPortIndex) == _FALSE)
                {
                    SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_SEND_GET_SNK_CAP);
                }
                else
                {
                    // [Allion 20210318] Ellisys TD.PD.VNDI3.E3. TD.PD.VNDI3.E5 .TD.PD.VNDI3.E7 : Solution: Wait > 10ms to Avoid Check Point. Timeout : Clear GET_SNK_CAP_WAIT_FLAG
                    ScalerTypeCTcpmActiveTimerEvent(ucPortIndex, _TYPE_C_SRC_GET_SNK_CAP_WAIT_TIMER, _SCALER_TIMER_EVENT_TCPM_CLR_GET_SNK_CAP_WAIT);
                }
            }
#if(_REFER_TO_PORT_PARTNER_CAP == _TRUE)
            else if((GET_TCPM_PD_PARTNER_DRD(ucPortIndex) == _TRUE) && (GET_TCPM_PD_DP_ALT_STATE(ucPortIndex) == _PD_ALT_MODE_NONE))
#else
            else if(GET_TCPM_PD_DP_ALT_STATE(ucPortIndex) == _PD_ALT_MODE_NONE)
#endif
            {
#if(_TYPE_C_DPAM_VERSION <= _DPAM_VERSION_1_0)
                if((GET_TCPM_PD_VCS_REJECT(ucPortIndex) == _FALSE) && (GET_TCPM_VCONN_ROLE(ucPortIndex) == _PD_VCONN_SRC))
                {
                    if(GET_TCPM_PD_VCS_WAIT_FLAG(ucPortIndex) == _FALSE)
                    {
                        SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_SEND_VCONN_SWAP);
                    }
                }
                else
                {
                    if(GET_TCPM_PD_DRS_WAIT_FLAG(ucPortIndex) == _FALSE)
                    {
                        SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_SEND_DR_SWAP);
                    }
                }
#else
                if(GET_TCPM_PD_DRS_WAIT_FLAG(ucPortIndex) == _FALSE)
                {
                    SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_SEND_DR_SWAP);
                }
#endif  // End of #if(_TYPE_C_DPAM_VERSION <= _DPAM_VERSION_1_0)
            }
        }
        else
        {
            // Check if System Request to Send Src Cap
            if((GET_TCPM_PD_SYS_EVENT(ucPortIndex) & _PD_SYS_EVENT_SEND_SRC_CAP) == _PD_SYS_EVENT_SEND_SRC_CAP)
            {
                SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_SEND_SRC_CAP);
            }
            // Check if System Request to Send Get_Status Cap
            else if((GET_TCPM_PD_SYS_EVENT(ucPortIndex) & _PD_SYS_EVENT_SEND_GET_STATUS_MSG) == _PD_SYS_EVENT_SEND_GET_STATUS_MSG)
            {
                SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_SEND_GET_STATUS);
            }
#if(_TYPE_C_MODAL_OPERATION_SUPPORT == _ON)
            else if((GET_TCPM_PD_MODAL_OPERATION_SUPPORT(ucPortIndex) == _TRUE) && (GET_TCPM_PD_ALT_MODE_FUNCTION(ucPortIndex) == _TRUE) && (GET_TCPM_PD_DP_ALT_STATE(ucPortIndex) != _PD_ALT_MODE_ERROR) && (GET_TCPM_PD_PARTNER_VDM_NO_RESP_CNT(ucPortIndex) < _MAX_VDM_NO_RESP_CNT))
            {
                if((GET_TCPM_PD_VCS_REJECT(ucPortIndex) == _FALSE) && (GET_TCPM_VCONN_ROLE(ucPortIndex) == _PD_VCONN_NOT_SRC))
                {
                    if(GET_TCPM_PD_VCS_WAIT_FLAG(ucPortIndex) == _FALSE)
                    {
                        SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_SEND_VCONN_SWAP);
                    }
                }
                else
                {
                    ScalerTypeCTcpmPdAltModeProc(ucPortIndex);
                }
            }
#endif
        }
    }
    else
    {
        if((GET_TCPM_PD_PARTNER_ALT_SUPPORT(ucPortIndex) == _FALSE) || (GET_TCPM_PD_DPAM_CONFIG(ucPortIndex) == _PD_DP_CONFIG))
        {
            if((GET_TCPM_PD_VCS_REJECT(ucPortIndex) == _FALSE) &&
               (((GET_TCPM_VCONN_ROLE(ucPortIndex) == _PD_VCONN_NOT_SRC) && (GET_TCPM_PD_SPEC_VER(ucPortIndex) == _PD_VERSION_3_0) && (GET_TCPM_PD_CBL_PD_CAPABILITY(ucPortIndex) == _TYPE_C_CABLE_PD_CAP_UNCONFIRMED)) ||
                ((GET_TCPM_VCONN_ROLE(ucPortIndex) == _PD_VCONN_SRC) && ((GET_TCPM_PD_SPEC_VER(ucPortIndex) == _PD_VERSION_2_0) || ((GET_TCPM_PD_CBL_PD_CAPABILITY(ucPortIndex) != _TYPE_C_CABLE_PD_CAP_UNCONFIRMED) && (GET_TCPM_PD_DPAM_CONFIG(ucPortIndex) != _PD_DP_CONFIG))))))
            {
                // There are two Conditions to Do Vconn_Swap:
                // 1. If (Vconn Not Source) && (PD 3.0) && (Cable Cap == Unconfirmed), Do Vconn_Swap for Cable Discovery.
                // Note: Lecroy [COMMON.PROC.PD.7 UUT Sent Discover Identity Request], As a UFP, It can't Send SOP' Msg to Cable in PD 2.0.
                // 2. If (Vconn Source) && {(PD 2.0) || [(Cable Cap != Unconfirmed) && (Not DP Config)]}, Do Vconn_Swap for Microsoft Surface Laptop 3 Interop Issue.
                // Note 1: If the FW don't Send Vconn_Swap here, Surface Laptop 3 will not Take any Action afterwards. (MM1AE-1999)
                // Note 2: If the FW Sends Vconn_Swap After DP Config, VAIO VJFH42H14T will Fail to Light Up. (MM1AE-2757)
                if(GET_TCPM_PD_VCS_WAIT_FLAG(ucPortIndex) == _FALSE)
                {
                    SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_SEND_VCONN_SWAP);
                }
            }
            else if((GET_TCPM_VCONN_ROLE(ucPortIndex) == _PD_VCONN_SRC) && (GET_TCPM_PD_SPEC_VER(ucPortIndex) == _PD_VERSION_3_0) && (GET_TCPM_PD_CBL_PD_CAPABILITY(ucPortIndex) == _TYPE_C_CABLE_PD_CAP_UNCONFIRMED))
            {
                if(GET_TCPM_PD_CBL_SOFT_RESET_REQUIRED(ucPortIndex) == _TRUE)
                {
                    CLR_TCPM_PD_CBL_SOFT_RESET_REQUIRED(ucPortIndex);

                    SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_CABLE_PROC);
                    SET_TCPM_PD_CBL_STATE(ucPortIndex, _PD_CBL_SEND_SOFT_RST);
                }
                else
                {
                    if(GET_TCPM_PD_VDM_BUSY_FLAG(ucPortIndex) == _FALSE)
                    {
                        SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_CABLE_PROC);
                        SET_TCPM_PD_CBL_STATE(ucPortIndex, _PD_CBL_SEND_DISCOVER_ID);
                    }
                }
            }
            else if((GET_TCPM_PD_SRC_REQUEST_SWAP_TO_SNK(ucPortIndex)) && (GET_TCPM_PD_PRS_REJECT(ucPortIndex) == _FALSE))
            {
                if((GET_TCPM_CC_PORT_ROLE(ucPortIndex) == _TYPE_C_PORT_DRP) && (GET_TCPM_PD_UNCONSTRAIN_POWER(ucPortIndex) == _FALSE))
                {
                    if(GET_TCPM_PD_GET_SRC_CAP_SENT(ucPortIndex) == _FALSE)
                    {
                        SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_SEND_GET_SRC_CAP);
                    }
                    else if((GET_TCPM_PD_PARTNER_DRP(ucPortIndex) == _TRUE) && (GET_TCPM_PD_PARTNER_SRC_CAP_CHECK_RESULT(ucPortIndex) == _PD_SRC_CAP_VALID))
                    {
                        // When Rcv. PR_Swap Wait Msg. Response, Immediately Active Timer(100ms) to Clear PRS_WAIT_FLAG
                        if(GET_TCPM_PD_PRS_WAIT_FLAG(ucPortIndex) == _FALSE)
                        {
                            SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_SEND_PR_SWAP);
                        }
                    }
                }
            }
            // Check if System Request to Send Src Cap
            else if((GET_TCPM_PD_SYS_EVENT(ucPortIndex) & _PD_SYS_EVENT_SEND_SRC_CAP) == _PD_SYS_EVENT_SEND_SRC_CAP)
            {
                SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_SEND_SRC_CAP);
            }
#if(_TYPE_C_MODAL_OPERATION_SUPPORT == _ON)
            else if((GET_TCPM_PD_MODAL_OPERATION_SUPPORT(ucPortIndex) == _TRUE) && (GET_TCPM_PD_ALT_MODE_FUNCTION(ucPortIndex) == _TRUE))
            {
                ScalerTypeCTcpmPdAltModeProc(ucPortIndex);
            }
#endif  // End of #if(_TYPE_C_MODAL_OPERATION_SUPPORT == _ON)
        }
    }
}

//--------------------------------------------------
// Description  : Process For SNK_READY DP_RX State
// Input Value  : ucPortIndex
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmPdSnkReadyDpRxProc(BYTE ucPortIndex)
{
    // Wait For Source to do PS_RDY or Alt. Mode Flow, Otherwise, Initiate Certain Flow
    if(GET_TCPM_DATA_ROLE(ucPortIndex) == _PD_DATA_UFP)
    {
        if(GET_TCPM_PD_SNK_REQUEST_SWAP_TO_SRC(ucPortIndex))
        {
            if(GET_TCPM_CC_PORT_ROLE(ucPortIndex) == _TYPE_C_PORT_DRP)
            {
                if((GET_TCPM_PD_PARTNER_ALT_SUPPORT(ucPortIndex) == _FALSE) || (GET_TCPM_PD_DPAM_CONFIG(ucPortIndex) == _PD_DP_CONFIG) || (GET_TCPM_PD_PARTNER_INIT_ALT_MODE(ucPortIndex) == _FALSE) || (GET_TCPM_PD_ALT_MODE_FUNCTION(ucPortIndex) == _FALSE))
                {
                    if(GET_TCPM_PD_GET_SNK_CAP_SENT(ucPortIndex) == _FALSE)
                    {
                        if(GET_TCPM_PD_GET_SNK_CAP_WAIT_FLAG(ucPortIndex) == _FALSE)
                        {
                            SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_SEND_GET_SNK_CAP);
                        }
                        else
                        {
                            // [Workshop #114] MQP BMC-PHY-MSG (Rev 2.0):Confirm that repeated incoming MessageID is ignored. Solution: Wait > 40ms to avoid check point.
                            ScalerTypeCTcpmActiveTimerEvent(ucPortIndex, _TYPE_C_SNK_GET_SNK_CAP_WAIT_TIMER, _SCALER_TIMER_EVENT_TCPM_CLR_GET_SNK_CAP_WAIT);
                        }
                    }
#if(_REFER_TO_PORT_PARTNER_CAP == _TRUE)
                    else if((GET_TCPM_PD_PARTNER_DRP(ucPortIndex) == _TRUE) && (GET_TCPM_PD_UNCONSTRAIN_POWER(ucPortIndex) == _TRUE) && (GET_TCPM_PD_PRS_REJECT(ucPortIndex) == _FALSE))
#else
                    else if((GET_TCPM_PD_UNCONSTRAIN_POWER(ucPortIndex) == _TRUE) && (GET_TCPM_PD_PRS_REJECT(ucPortIndex) == _FALSE))
#endif
                    {
                        if((GET_TCPM_PD_VCS_REJECT(ucPortIndex) == _FALSE) && (GET_TCPM_VCONN_ROLE(ucPortIndex) == _PD_VCONN_NOT_SRC))
                        {
                            if(GET_TCPM_PD_VCS_WAIT_FLAG(ucPortIndex) == _FALSE)
                            {
                                SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_SEND_VCONN_SWAP);
                            }
                        }
                        else
                        {
                            if(GET_TCPM_PD_PRS_WAIT_FLAG(ucPortIndex) == _FALSE)
                            {
                                SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_SEND_PR_SWAP);
                            }
                        }
                    }
                    else if((GET_TCPM_PD_SYS_EVENT(ucPortIndex) & _PD_SYS_EVENT_SEND_REQUEST) == _PD_SYS_EVENT_SEND_REQUEST)
                    {
                        // Send "Get Source Capabilitie to Ask Source to Send Src Cap, and Send New Request to Source"
                        SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_SEND_GET_SRC_CAP);
                    }
                    // Check if System Request to Send Get_Status Cap
                    else if((GET_TCPM_PD_SYS_EVENT(ucPortIndex) & _PD_SYS_EVENT_SEND_GET_STATUS_MSG) == _PD_SYS_EVENT_SEND_GET_STATUS_MSG)
                    {
                        SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_SEND_GET_STATUS);
                    }
#if(_TYPE_C_MODAL_OPERATION_SUPPORT == _ON)
                    // Try to Do Alt. Mode Flow (Get HPD Queue)
                    else if((GET_TCPM_PD_MODAL_OPERATION_SUPPORT(ucPortIndex) == _TRUE) && (GET_TCPM_PD_ALT_MODE_FUNCTION(ucPortIndex) == _TRUE))
                    {
                        ScalerTypeCTcpmPdAltModeProc(ucPortIndex);
                    }
#endif
                }
            }
        }
        else
        {
            // Snk-Only or DRP Do Not Support PR_SWAP, Check Whether Request Event Exist
            if((GET_TCPM_PD_SYS_EVENT(ucPortIndex) & _PD_SYS_EVENT_SEND_REQUEST) == _PD_SYS_EVENT_SEND_REQUEST)
            {
                // Send "Get Source Capabilitie to Ask Source to Send Src Cap, and Send New Request to Source"
                SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_SEND_GET_SRC_CAP);
            }
            // Check if System Request to Send Get_Status Cap
            else if((GET_TCPM_PD_SYS_EVENT(ucPortIndex) & _PD_SYS_EVENT_SEND_GET_STATUS_MSG) == _PD_SYS_EVENT_SEND_GET_STATUS_MSG)
            {
                SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_SEND_GET_STATUS);
            }
#if(_TYPE_C_MODAL_OPERATION_SUPPORT == _ON)
            // Try to Do Alt. Mode Flow (Get HPD Queue)
            else if((GET_TCPM_PD_MODAL_OPERATION_SUPPORT(ucPortIndex) == _TRUE) && (GET_TCPM_PD_ALT_MODE_FUNCTION(ucPortIndex) == _TRUE))
            {
                ScalerTypeCTcpmPdAltModeProc(ucPortIndex);
            }
#endif
        }
    }
}
#endif  // End of #if(_PORT_CTRL_EMB_DP_RX_SUPPORT == _ON)

#if(_PORT_CTRL_EMB_DP_TX_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Process For SRC_READY DP_TX State
// Input Value  : ucPortIndex
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmPdSrcReadyDpTxProc(BYTE ucPortIndex)
{
    if(GET_TCPM_DATA_ROLE(ucPortIndex) == _PD_DATA_DFP)
    {
        // Check if System Request to Send Src Cap
        if((GET_TCPM_PD_SYS_EVENT(ucPortIndex) & _PD_SYS_EVENT_SEND_SRC_CAP) == _PD_SYS_EVENT_SEND_SRC_CAP)
        {
            SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_SEND_SRC_CAP);
        }
        // Check if System Request to Send Get_Status Cap
        else if((GET_TCPM_PD_SYS_EVENT(ucPortIndex) & _PD_SYS_EVENT_SEND_GET_STATUS_MSG) == _PD_SYS_EVENT_SEND_GET_STATUS_MSG)
        {
            SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_SEND_GET_STATUS);
        }
#if(_TYPE_C_MODAL_OPERATION_SUPPORT == _ON)
        else if((GET_TCPM_PD_MODAL_OPERATION_SUPPORT(ucPortIndex) == _TRUE) && (GET_TCPM_PD_ALT_MODE_FUNCTION(ucPortIndex) == _TRUE) && (GET_TCPM_PD_DP_ALT_STATE(ucPortIndex) != _PD_ALT_MODE_ERROR) && (GET_TCPM_PD_DP_ALT_STATE(ucPortIndex) != _PD_ALT_MODE_READY) && (GET_TCPM_PD_DP_ALT_STATE(ucPortIndex) != _PD_ALT_MODE_INT_WAIT_ATTENTION) && (GET_TCPM_PD_PARTNER_VDM_NO_RESP_CNT(ucPortIndex) < _MAX_VDM_NO_RESP_CNT))
        {
            if((GET_TCPM_PD_VCS_REJECT(ucPortIndex) == _FALSE) && (GET_TCPM_VCONN_ROLE(ucPortIndex) == _PD_VCONN_NOT_SRC))
            {
                if(GET_TCPM_PD_VCS_WAIT_FLAG(ucPortIndex) == _FALSE)
                {
                    SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_SEND_VCONN_SWAP);
                }
            }
            else
            {
                ScalerTypeCTcpmPdAltModeProc(ucPortIndex);
            }
        }
#endif  // End of #if(_TYPE_C_MODAL_OPERATION_SUPPORT == _ON)
        else if((GET_TCPM_PD_SRC_REQUEST_SWAP_TO_SNK(ucPortIndex) == _TRUE) && (GET_TCPM_CC_PORT_ROLE(ucPortIndex) == _TYPE_C_PORT_DRP) && (GET_TCPM_PD_UNCONSTRAIN_POWER(ucPortIndex) == _FALSE))
        {
            if(GET_TCPM_PD_GET_SRC_CAP_SENT(ucPortIndex) == _FALSE)
            {
                SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_SEND_GET_SRC_CAP);
            }
            else if((GET_TCPM_PD_PARTNER_DRP(ucPortIndex) == _TRUE) && (GET_TCPM_PD_PARTNER_SRC_CAP_CHECK_RESULT(ucPortIndex) == _PD_SRC_CAP_VALID))
            {
                // When Rcv. PR_Swap Wait Msg. Response, Immediately Active Timer(100ms) to Clear PRS_WAIT_FLAG
                if(GET_TCPM_PD_PRS_WAIT_FLAG(ucPortIndex) == _FALSE)
                {
                    SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_SEND_PR_SWAP);
                }
            }
        }
    }
    else
    {
        if((GET_TCPM_PD_UFP_SWAP_TO_DFP(ucPortIndex) == _TRUE) && (GET_TCPM_PD_DPAM_ENTER(ucPortIndex) == _FALSE) && (GET_TCPM_PD_PARTNER_DRD(ucPortIndex) == _TRUE) && (GET_TCPM_PD_DRS_REJECT(ucPortIndex) == _FALSE))
        {
            if((GET_TCPM_PD_PARTNER_INIT_ALT_MODE(ucPortIndex) == _FALSE) || (GET_TCPM_PD_PARTNER_ALT_SUPPORT(ucPortIndex) == _FALSE))
            {
                if(GET_TCPM_PD_DRS_WAIT_FLAG(ucPortIndex) == _FALSE)
                {
                    SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_SEND_DR_SWAP);
                }
            }
        }
        else
        {
            if((GET_TCPM_PD_SRC_REQUEST_SWAP_TO_SNK(ucPortIndex) == _TRUE) && (GET_TCPM_CC_PORT_ROLE(ucPortIndex) == _TYPE_C_PORT_DRP) && (GET_TCPM_PD_UNCONSTRAIN_POWER(ucPortIndex) == _FALSE))
            {
                if((GET_TCPM_PD_DPAM_CONFIG(ucPortIndex) == _PD_DP_CONFIG) || (GET_TCPM_PD_PARTNER_ALT_SUPPORT(ucPortIndex) == _FALSE) || (GET_TCPM_PD_PARTNER_INIT_ALT_MODE(ucPortIndex) == _FALSE))
                {
                    if(GET_TCPM_PD_GET_SRC_CAP_SENT(ucPortIndex) == _FALSE)
                    {
                        SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_SEND_GET_SRC_CAP);
                    }
                    else if((GET_TCPM_PD_PARTNER_DRP(ucPortIndex) == _TRUE) && (GET_TCPM_PD_PARTNER_SRC_CAP_CHECK_RESULT(ucPortIndex) == _PD_SRC_CAP_VALID))
                    {
                        // When Rcv. PR_Swap Wait Msg. Response, Immediately Active Timer(100ms) to Clear PRS_WAIT_FLAG
                        if(GET_TCPM_PD_PRS_WAIT_FLAG(ucPortIndex) == _FALSE)
                        {
                            SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_SEND_PR_SWAP);
                        }
                    }
                    else if((GET_TCPM_PD_SYS_EVENT(ucPortIndex) & _PD_SYS_EVENT_SEND_SRC_CAP) == _PD_SYS_EVENT_SEND_SRC_CAP)
                    {
                        SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_SEND_SRC_CAP);
                    }
                    // Check if System Request to Send Get_Status Cap
                    else if((GET_TCPM_PD_SYS_EVENT(ucPortIndex) & _PD_SYS_EVENT_SEND_GET_STATUS_MSG) == _PD_SYS_EVENT_SEND_GET_STATUS_MSG)
                    {
                        SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_SEND_GET_STATUS);
                    }
#if(_TYPE_C_MODAL_OPERATION_SUPPORT == _ON)
                    else if((GET_TCPM_PD_MODAL_OPERATION_SUPPORT(ucPortIndex) == _TRUE) && (GET_TCPM_PD_ALT_MODE_FUNCTION(ucPortIndex) == _TRUE))
                    {
                        ScalerTypeCTcpmPdAltModeProc(ucPortIndex);
                    }
#endif  // End of #if(_TYPE_C_MODAL_OPERATION_SUPPORT == _ON)
                }
            }
            else
            {
                // Check if System Request to Send Src Cap
                if((GET_TCPM_PD_SYS_EVENT(ucPortIndex) & _PD_SYS_EVENT_SEND_SRC_CAP) == _PD_SYS_EVENT_SEND_SRC_CAP)
                {
                    SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_SEND_SRC_CAP);
                }
                // Check if System Request to Send Get_Status Cap
                else if((GET_TCPM_PD_SYS_EVENT(ucPortIndex) & _PD_SYS_EVENT_SEND_GET_STATUS_MSG) == _PD_SYS_EVENT_SEND_GET_STATUS_MSG)
                {
                    SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_SEND_GET_STATUS);
                }
#if(_TYPE_C_MODAL_OPERATION_SUPPORT == _ON)
                else if((GET_TCPM_PD_MODAL_OPERATION_SUPPORT(ucPortIndex) == _TRUE) && (GET_TCPM_PD_ALT_MODE_FUNCTION(ucPortIndex) == _TRUE))
                {
                    ScalerTypeCTcpmPdAltModeProc(ucPortIndex);
                }
#endif  // End of #if(_TYPE_C_MODAL_OPERATION_SUPPORT == _ON)
            }
        }
    }
}

//--------------------------------------------------
// Description  : Process For SNK_READY DP_TX State
// Input Value  : ucPortIndex
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmPdSnkReadyDpTxProc(BYTE ucPortIndex)
{
    if(GET_TCPM_DATA_ROLE(ucPortIndex) == _PD_DATA_DFP)
    {
        // Check Whether Request Event Exist
        if((GET_TCPM_PD_SYS_EVENT(ucPortIndex) & _PD_SYS_EVENT_SEND_REQUEST) == _PD_SYS_EVENT_SEND_REQUEST)
        {
            // Send "Get Source Capabilitie to Ask Source to Send Src Cap, and Send New Request to Source"
            SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_SEND_GET_SRC_CAP);
        }
        // Check if System Request to Send Get_Status Cap
        else if((GET_TCPM_PD_SYS_EVENT(ucPortIndex) & _PD_SYS_EVENT_SEND_GET_STATUS_MSG) == _PD_SYS_EVENT_SEND_GET_STATUS_MSG)
        {
            SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_SEND_GET_STATUS);
        }
#if(_TYPE_C_MODAL_OPERATION_SUPPORT == _ON)
        else if((GET_TCPM_PD_MODAL_OPERATION_SUPPORT(ucPortIndex) == _TRUE) && (GET_TCPM_PD_ALT_MODE_FUNCTION(ucPortIndex) == _TRUE) && (GET_TCPM_PD_DP_ALT_STATE(ucPortIndex) != _PD_ALT_MODE_ERROR) && (GET_TCPM_PD_DP_ALT_STATE(ucPortIndex) != _PD_ALT_MODE_READY) && (GET_TCPM_PD_DP_ALT_STATE(ucPortIndex) != _PD_ALT_MODE_INT_WAIT_ATTENTION) && (GET_TCPM_PD_PARTNER_VDM_NO_RESP_CNT(ucPortIndex) < _MAX_VDM_NO_RESP_CNT))
        {
            if((GET_TCPM_PD_VCS_REJECT(ucPortIndex) == _FALSE) && (GET_TCPM_VCONN_ROLE(ucPortIndex) == _PD_VCONN_NOT_SRC))
            {
                if(GET_TCPM_PD_VCS_WAIT_FLAG(ucPortIndex) == _FALSE)
                {
                    SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_SEND_VCONN_SWAP);
                }
            }
            else
            {
                ScalerTypeCTcpmPdAltModeProc(ucPortIndex);
            }
        }
#endif  // End of #if(_TYPE_C_MODAL_OPERATION_SUPPORT == _ON)
        else if((GET_TCPM_PD_SNK_REQUEST_SWAP_TO_SRC(ucPortIndex) == _TRUE) && (GET_TCPM_CC_PORT_ROLE(ucPortIndex) == _TYPE_C_PORT_DRP) && (GET_TCPM_PD_PARTNER_DRP(ucPortIndex) == _TRUE) && (GET_TCPM_PD_UNCONSTRAIN_POWER(ucPortIndex) == _TRUE))
        {
            // When Rcv. PR_Swap Wait Msg. Response, Immediately Active Timer(100ms) to Clear PRS_WAIT_FLAG
            if(GET_TCPM_PD_PRS_WAIT_FLAG(ucPortIndex) == _FALSE)
            {
                SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_SEND_PR_SWAP);
            }
        }
    }
    else
    {
        if((GET_TCPM_PD_UFP_SWAP_TO_DFP(ucPortIndex) == _TRUE) && (GET_TCPM_PD_DPAM_ENTER(ucPortIndex) == _FALSE) && (GET_TCPM_PD_PARTNER_DRD(ucPortIndex) == _TRUE) && (GET_TCPM_PD_DRS_REJECT(ucPortIndex) == _FALSE))
        {
            if((GET_TCPM_PD_PARTNER_INIT_ALT_MODE(ucPortIndex) == _FALSE) || (GET_TCPM_PD_PARTNER_ALT_SUPPORT(ucPortIndex) == _FALSE))
            {
                if(GET_TCPM_PD_DRS_WAIT_FLAG(ucPortIndex) == _FALSE)
                {
                    SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_SEND_DR_SWAP);
                }
            }
        }
        else
        {
            if((GET_TCPM_PD_SNK_REQUEST_SWAP_TO_SRC(ucPortIndex) == _TRUE) && (GET_TCPM_CC_PORT_ROLE(ucPortIndex) == _TYPE_C_PORT_DRP) && (GET_TCPM_PD_PARTNER_DRP(ucPortIndex) == _TRUE) && (GET_TCPM_PD_UNCONSTRAIN_POWER(ucPortIndex) == _TRUE))
            {
                if((GET_TCPM_PD_DPAM_CONFIG(ucPortIndex) == _PD_DP_CONFIG) || (GET_TCPM_PD_PARTNER_ALT_SUPPORT(ucPortIndex) == _FALSE))
                {
                    // When Rcv. PR_Swap Wait Msg. Response, Immediately Active Timer(100ms) to Clear PRS_WAIT_FLAG
                    if(GET_TCPM_PD_PRS_WAIT_FLAG(ucPortIndex) == _FALSE)
                    {
                        SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_SEND_PR_SWAP);
                    }
                }
            }
            else
            {
                // Check Whether Request Event Exist
                if((GET_TCPM_PD_SYS_EVENT(ucPortIndex) & _PD_SYS_EVENT_SEND_REQUEST) == _PD_SYS_EVENT_SEND_REQUEST)
                {
                    // Send "Get Source Capabilitie to Ask Source to Send Src Cap, and Send New Request to Source"
                    SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_SEND_GET_SRC_CAP);
                }
                // Check if System Request to Send Get_Status Cap
                else if((GET_TCPM_PD_SYS_EVENT(ucPortIndex) & _PD_SYS_EVENT_SEND_GET_STATUS_MSG) == _PD_SYS_EVENT_SEND_GET_STATUS_MSG)
                {
                    SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_SEND_GET_STATUS);
                }
#if(_TYPE_C_MODAL_OPERATION_SUPPORT == _ON)
                // Try to Do Alt. Mode Flow (Get HPD Queue)
                else if((GET_TCPM_PD_MODAL_OPERATION_SUPPORT(ucPortIndex) == _TRUE) && (GET_TCPM_PD_ALT_MODE_FUNCTION(ucPortIndex) == _TRUE))
                {
                    ScalerTypeCTcpmPdAltModeProc(ucPortIndex);
                }
#endif
            }
        }
    }
}
#endif  // End of #if(_PORT_CTRL_EMB_DP_TX_SUPPORT == _ON)

#if(_TYPE_C_MODAL_OPERATION_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Process For Alt Mode Flow
// Input Value  : ucPortIndex
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmPdAltModeProc(BYTE ucPortIndex)
{
#if(_PORT_CTRL_EMB_DP_ALT_MODE_SUPPORT == _ON)
    // Send Message Only When Data Role = DFP, and Alt Mode Not in Error State
    if((GET_TCPM_PD_DPAM_SUPPORT(ucPortIndex)) && (GET_TCPM_DATA_ROLE(ucPortIndex) == _PD_DATA_DFP))
    {
        if(GET_TCPM_PD_VDMMSG_WAIT_FLAG(ucPortIndex) == _TRUE)
        {
            ScalerTypeCTcpmActiveTimerEvent(ucPortIndex, 50, _SCALER_TIMER_EVENT_TCPM_CLR_VDMMSG_WAIT);
        }
        else if(GET_TCPM_PD_VDM_BUSY_FLAG(ucPortIndex) == _FALSE)
        {
            ScalerTypeCTcpmPdDpAltModeDfpProc(ucPortIndex);
        }
    }
    else
#endif
    {
        if(GET_TCPM_DATA_ROLE(ucPortIndex) == _PD_DATA_UFP)
        {
#if(_PORT_CTRL_EMB_DP_ALT_MODE_SUPPORT == _ON)
            if((GET_TCPM_PD_DPAM_SUPPORT(ucPortIndex)) && (GET_TCPM_PD_DPAM_CONFIG(ucPortIndex) == _PD_DP_CONFIG))
            {
                ScalerTypeCTcpmPdDpAltModeUfpProc(ucPortIndex);

                if(GET_TCPM_PD_SUB_STATE(ucPortIndex) == _PD_SUB_SEND_DP_VDM_REQ)
                {
                    return;
                }
            }
#endif
        }
    }
}

#if(_PORT_CTRL_EMB_DP_ALT_MODE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Process For DFP Dp Alt Mode Flow
// Input Value  : ucPortIndex
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmPdDpAltModeDfpProc(BYTE ucPortIndex)
{
    switch(GET_TCPM_PD_DP_ALT_STATE(ucPortIndex))
    {
        case _PD_ALT_MODE_NONE:

            // DFP Waits 50ms then Starts Alt Mode
            ScalerTypeCTcpmActiveTimerEvent(ucPortIndex, 50, _SCALER_TIMER_EVENT_TCPM_DFP_START_ALT_MODE);

            break;

        case _PD_ALT_MODE_SEND_DISCOVER_ID:
        case _PD_ALT_MODE_SEND_DISCOVER_SVID:
        case _PD_ALT_MODE_SEND_DISCOVER_MODE:
        case _PD_ALT_MODE_SEND_ENTER_MODE:
        case _PD_ALT_MODE_SEND_DP_STATUS:
        case _PD_ALT_MODE_SEND_DP_CONFIG:
        case _PD_ALT_MODE_SEND_EXIT_MODE:

            SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_SEND_DP_VDM_REQ);

            break;

#if(_TYPE_C_DPAM_VERSION >= _DPAM_VERSION_2_1)
        case _PD_ALT_MODE_SEND_DISCOVER_ID_SOP_P:
        case _PD_ALT_MODE_SEND_DISCOVER_SVID_SOP_P:
        case _PD_ALT_MODE_SEND_DP_DISCOVER_MODE_SOP_P:
        case _PD_ALT_MODE_SEND_TBT3_DISCOVER_MODE_SOP_P:
        case _PD_ALT_MODE_SEND_ENTER_MODE_SOP_P:
        case _PD_ALT_MODE_SEND_ENTER_MODE_SOP_PP:
        case _PD_ALT_MODE_SEND_DP_CONFIG_SOP_P:
        case _PD_ALT_MODE_SEND_DP_CONFIG_SOP_PP:
        case _PD_ALT_MODE_SEND_EXIT_MODE_SOP_P:
        case _PD_ALT_MODE_SEND_EXIT_MODE_SOP_PP:

            SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_SEND_CBL_DP_VDM_REQ);

            break;
#endif  // End of #if(_TYPE_C_DPAM_VERSION >= _DPAM_VERSION_2_1)

        case _PD_ALT_MODE_READY:

#if(_PORT_CTRL_EMB_DP_RX_SUPPORT == _ON)
            if((GET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex) == _TYPE_C_DP_RX) && (GET_TCPM_PD_DPAM_CONFIG(ucPortIndex) == _PD_DP_CONFIG) && (GET_TCPM_PD_HPD_CNT(ucPortIndex) > 0) && (GET_TCPM_PD_DPAM_ATTENTION_WAIT(ucPortIndex) == _FALSE))
            {
                SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_SEND_DP_VDM_REQ);
            }
#endif

            break;

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Process For DFP Dp Alt Mode Send Msg
// Input Value  : ucPortIndex
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmPdDpAltModeDfpSendMsg(BYTE ucPortIndex)
{
    switch(GET_TCPM_PD_DP_ALT_STATE(ucPortIndex))
    {
        case _PD_ALT_MODE_SEND_DISCOVER_ID:

            if(ScalerTypeCTcpmPdTxAvaliable(ucPortIndex) == _TRUE)
            {
                SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);

                // Send "Discover ID REQ"
                ScalerTypeCTcpmPdSendMsg(ucPortIndex, _PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_DISCOVER_ID_REQ);
            }

            break;

        case _PD_ALT_MODE_SEND_DISCOVER_SVID:

            if(ScalerTypeCTcpmPdTxAvaliable(ucPortIndex) == _TRUE)
            {
                SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);

                // Send "Discover SVID REQ"
                ScalerTypeCTcpmPdSendMsg(ucPortIndex, _PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_DISCOVER_SVID_REQ);
            }

            break;

        case _PD_ALT_MODE_SEND_DISCOVER_MODE:

            if(ScalerTypeCTcpmPdTxAvaliable(ucPortIndex) == _TRUE)
            {
                SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);

                // Send "DP Discover Mode REQ"
                ScalerTypeCTcpmPdSendMsg(ucPortIndex, _PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_DISCOVER_MODE_REQ);
            }

            break;

#if(_TYPE_C_DPAM_VERSION >= _DPAM_VERSION_2_1)
        case _PD_ALT_MODE_SEND_DISCOVER_ID_SOP_P:

            if(ScalerTypeCTcpmPdTxAvaliable(ucPortIndex) == _TRUE)
            {
                // Send Discover ID (SOP') to Get Cable Info
                SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_BY_STATE);
                ScalerTypeCTcpmPdSendMsg(ucPortIndex, _PD_SOP_P_PKT, _PD_CMD_VDM, _PD_VDM_CMD_DISCOVER_ID_REQ);
            }

            break;

        case _PD_ALT_MODE_SEND_DISCOVER_SVID_SOP_P:

            if(ScalerTypeCTcpmPdTxAvaliable(ucPortIndex) == _TRUE)
            {
                // Send Discover SVID (SOP') to Get Cable SVID
                SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_BY_STATE);
                ScalerTypeCTcpmPdSendMsg(ucPortIndex, _PD_SOP_P_PKT, _PD_CMD_VDM, _PD_VDM_CMD_DISCOVER_SVID_REQ);
            }

            break;

        case _PD_ALT_MODE_SEND_DP_DISCOVER_MODE_SOP_P:

            if(ScalerTypeCTcpmPdTxAvaliable(ucPortIndex) == _TRUE)
            {
                // Send DP Discover Mode (SOP') to Get Cable DP Capabilities
                SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_BY_STATE);
                ScalerTypeCTcpmPdSendMsg(ucPortIndex, _PD_SOP_P_PKT, _PD_CMD_VDM, _PD_VDM_CMD_DISCOVER_MODE_REQ);
            }

            break;

        case _PD_ALT_MODE_SEND_TBT3_DISCOVER_MODE_SOP_P:

            if(ScalerTypeCTcpmPdTxAvaliable(ucPortIndex) == _TRUE)
            {
                // Send TBT3 Discover Mode (SOP') to Get Cable TBT3 Capabilities
                SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_BY_STATE);
                ScalerTypeCTcpmPdSendMsg(ucPortIndex, _PD_SOP_P_PKT, _PD_CMD_VDM, _PD_VDM_CMD_DISCOVER_MODE_REQ);
            }

            break;

        case _PD_ALT_MODE_SEND_ENTER_MODE_SOP_P:

            if(ScalerTypeCTcpmPdTxAvaliable(ucPortIndex) == _TRUE)
            {
                // Send SOP' Enter DP Mode
                SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_BY_STATE);
                ScalerTypeCTcpmPdSendMsg(ucPortIndex, _PD_SOP_P_PKT, _PD_CMD_VDM, _PD_VDM_CMD_ENTER_MODE_REQ);
            }

            break;

        case _PD_ALT_MODE_SEND_ENTER_MODE_SOP_PP:

            if(ScalerTypeCTcpmPdTxAvaliable(ucPortIndex) == _TRUE)
            {
                // Send SOP" Enter DP Mode
                SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_BY_STATE);
                ScalerTypeCTcpmPdSendMsg(ucPortIndex, _PD_SOP_PP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_ENTER_MODE_REQ);
            }

            break;

        case _PD_ALT_MODE_SEND_DP_CONFIG_SOP_P:

            if(ScalerTypeCTcpmPdTxAvaliable(ucPortIndex) == _TRUE)
            {
                // Send SOP' DP Config
                SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_BY_STATE);
                ScalerTypeCTcpmPdSendMsg(ucPortIndex, _PD_SOP_P_PKT, _PD_CMD_VDM, _PD_VDM_CMD_11);
            }

            break;

        case _PD_ALT_MODE_SEND_DP_CONFIG_SOP_PP:

            if(ScalerTypeCTcpmPdTxAvaliable(ucPortIndex) == _TRUE)
            {
                // Send SOP' DP Config
                SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_BY_STATE);
                ScalerTypeCTcpmPdSendMsg(ucPortIndex, _PD_SOP_PP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_11);
            }

            break;

        case _PD_ALT_MODE_SEND_EXIT_MODE_SOP_P:

            if(ScalerTypeCTcpmPdTxAvaliable(ucPortIndex) == _TRUE)
            {
                // Send SOP' Enter DP Mode
                SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_BY_STATE);
                ScalerTypeCTcpmPdSendMsg(ucPortIndex, _PD_SOP_P_PKT, _PD_CMD_VDM, _PD_VDM_CMD_EXIT_MODE_REQ);
            }

            break;

        case _PD_ALT_MODE_SEND_EXIT_MODE_SOP_PP:

            if(ScalerTypeCTcpmPdTxAvaliable(ucPortIndex) == _TRUE)
            {
                // Send SOP" Enter DP Mode
                SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_BY_STATE);
                ScalerTypeCTcpmPdSendMsg(ucPortIndex, _PD_SOP_PP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_EXIT_MODE_REQ);
            }

            break;
#endif  // End of #if(_TYPE_C_DPAM_VERSION >= _DPAM_VERSION_2_1)

        case _PD_ALT_MODE_SEND_ENTER_MODE:

            if(ScalerTypeCTcpmPdTxAvaliable(ucPortIndex) == _TRUE)
            {
                SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);

                // Send "Enter Mode REQ"
                ScalerTypeCTcpmPdSendMsg(ucPortIndex, _PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_ENTER_MODE_REQ);
            }

            break;

        case _PD_ALT_MODE_SEND_DP_STATUS:

            if(ScalerTypeCTcpmPdTxAvaliable(ucPortIndex) == _TRUE)
            {
                SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);

                // Send "DP Status REQ"
                ScalerTypeCTcpmPdSendMsg(ucPortIndex, _PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_10);
            }

            break;

        case _PD_ALT_MODE_SEND_DP_CONFIG:

            if(ScalerTypeCTcpmPdTxAvaliable(ucPortIndex) == _TRUE)
            {
                SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);

#if(_PORT_CTRL_EMB_DP_TX_SUPPORT == _ON)
                if((GET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex) == _TYPE_C_DP_TX) && (GET_TCPM_PD_DPAM_PIN_ASSIGNMENT(ucPortIndex) == _TYPE_C_PIN_ASSIGNMENT_NONE))
                {
                    // When Re-configuration, DFP(DP_TX) Shall Ensure HPD_Low Maintained for a Minimum of 3ms
                    ScalerTimerDelayXms(3);
                }
#endif

                // Send "DP Config REQ"
                ScalerTypeCTcpmPdSendMsg(ucPortIndex, _PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_11);
            }

            break;

        case _PD_ALT_MODE_READY:

#if(_PORT_CTRL_EMB_DP_RX_SUPPORT == _ON)
            if(ScalerTypeCTcpmPdTxAvaliable(ucPortIndex) == _TRUE)
            {
                SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);

                // Send "DP Status REQ"
                ScalerTypeCTcpmPdSendMsg(ucPortIndex, _PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_10);
            }
#endif

            break;

        case _PD_ALT_MODE_SEND_EXIT_MODE:

            if(ScalerTypeCTcpmPdTxAvaliable(ucPortIndex) == _TRUE)
            {
                SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);

                // Send "Exit Mode REQ"
                ScalerTypeCTcpmPdSendMsg(ucPortIndex, _PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_EXIT_MODE_REQ);
            }

            break;

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Process For UFP Dp Alt Mode Flow
// Input Value  : ucPortIndex
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmPdDpAltModeUfpProc(BYTE ucPortIndex)
{
#if(_PORT_CTRL_EMB_DP_RX_SUPPORT == _ON)
    if((GET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex) == _TYPE_C_DP_RX) && (GET_TCPM_PD_HPD_CNT(ucPortIndex) > 0) && (GET_TCPM_PD_DPAM_ATTENTION_WAIT(ucPortIndex) == _FALSE))
    {
        SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_SEND_ATTENTION);
        SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_SEND_DP_VDM_REQ);
    }
#endif  // End of #if(_PORT_CTRL_EMB_DP_RX_SUPPORT == _ON)
}

//--------------------------------------------------
// Description  : Process For UFP Dp Alt Mode Send Msg
// Input Value  : ucPortIndex
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmPdDpAltModeUfpSendMsg(BYTE ucPortIndex)
{
    switch(GET_TCPM_PD_DP_ALT_STATE(ucPortIndex))
    {
#if(_PORT_CTRL_EMB_DP_RX_SUPPORT == _ON)
        case _PD_ALT_MODE_SEND_ATTENTION:

            if(ScalerTypeCTcpmPdTxAvaliable(ucPortIndex) == _TRUE)
            {
                SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);

                // Send "Attention REQ"
                ScalerTypeCTcpmPdSendMsg(ucPortIndex, _PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_ATTENTION_REQ);
            }

            break;
#endif  // End of #if(_PORT_CTRL_EMB_DP_RX_SUPPORT == _ON)

        default:

            break;
    }
}
#endif  // End of #if(_PORT_CTRL_EMB_DP_ALT_MODE_SUPPORT == _ON)
#endif  // End of #if(_TYPE_C_MODAL_OPERATION_SUPPORT == _ON)

//--------------------------------------------------
// Description  : Type C TCPM Send PD Message
// Input Value  : ucPortIndex, enumPacketType, enumPdCmd, enumVdmCmd
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmPdSendMsg(BYTE ucPortIndex, EnumTypeCPDPacketType enumPacketType, EnumTypeCPDCmd enumPdCmd, EnumTypeCVdmCmd enumVdmCmd)
{
    BYTE ucTransmitInfo = 0x00;

    // 1. Clear Flag
    CLR_TCPM_PD_INT_OVERWRITE(ucPortIndex);

    // 2. Clear and Enable Tx_SUCCESS + Tx_FAIL + Tx_DISCARD
    ScalerTypeCTcpmAlertControl(ucPortIndex, ((WORD)(_TCPM_TCPCI_ALERT_TX_FAIL | _TCPM_TCPCI_ALERT_TX_DISCARD | _TCPM_TCPCI_ALERT_TX_SUCCESS)), _ENABLE);

    // 3. Construct Message and Write Data to Tx Buffer [0x51~]
    ScalerTypeCTcpmPdConstructMsg(ucPortIndex, enumPacketType, enumPdCmd, enumVdmCmd);

    // 4. Send Message
    // TRANSMIT [0x50] [5:4] Retry Counter (PD2.0 = 3, PD3.0 = 2)
    // TRANSMIT [0x50] [2:0] SOP Type : 000b (SOP), 001b (SOP'), 010b (SOP"),
    if(enumPacketType == _PD_SOP_PKT)
    {
        if(GET_TCPM_PD_SPEC_VER(ucPortIndex) == _PD_VERSION_2_0)
        {
            ucTransmitInfo = ucTransmitInfo | (_BIT5 | _BIT4);
        }
        else
        {
            ucTransmitInfo = ucTransmitInfo | (_BIT5);
        }

        ADD_TCPM_PD_TX_MSG_ID_SOP(ucPortIndex);
    }
    else if(enumPacketType == _PD_SOP_P_PKT)
    {
        if(GET_TCPM_PD_CBL_SPEC_VER(ucPortIndex) == _PD_VERSION_2_0)
        {
            ucTransmitInfo = ucTransmitInfo | (_BIT5 | _BIT4 | _BIT0);
        }
        else
        {
            ucTransmitInfo = ucTransmitInfo | (_BIT5 | _BIT0);
        }

        ADD_TCPM_PD_TX_MSG_ID_SOP_P(ucPortIndex);
    }
    else if(enumPacketType == _PD_SOP_PP_PKT)
    {
        if(GET_TCPM_PD_CBL_SPEC_VER(ucPortIndex) == _PD_VERSION_2_0)
        {
            ucTransmitInfo = ucTransmitInfo | (_BIT5 | _BIT4 | _BIT1);
        }
        else
        {
            ucTransmitInfo = ucTransmitInfo | (_BIT5 | _BIT1);
        }

        ADD_TCPM_PD_TX_MSG_ID_SOP_PP(ucPortIndex);
    }

    // Only Send Msg. When Tx FIFO Has Not Been Overwritten by INT during Msg. Construct Flow
    if(GET_TCPM_PD_INT_OVERWRITE(ucPortIndex) == _TRUE)
    {
        // Function Has Been Interrupted Before Sending, Just Not Start Transmit.
        return;
    }
    else
    {
        // Disable Rx Int
        ScalerTypeCTcpmRxIntControl(ucPortIndex, _DISABLE);

        // Set Transmit
        ScalerTypeCTcpmTcpciSetTransmit(ucPortIndex, ucTransmitInfo);
    }
}

//--------------------------------------------------
// Description  : Type C TCPM Construct PD Message to Send
// Input Value  : ucPortIndex, enumPacketType, enumPdCmd, enumVdmCmd
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmPdConstructMsg(BYTE ucPortIndex, EnumTypeCPDPacketType enumPacketType, EnumTypeCPDCmd enumPdCmd, EnumTypeCVdmCmd enumVdmCmd)
{
    BYTE ucExtendedBit = 0;
    BYTE ucDataObjectCnt = 0;
    WORD usMsgHeader = 0;

    // 1. Set Up Number of Data Objects(Data Blocks) if Needed
    switch(enumPdCmd)
    {
        // ------------------------------------
        // Control Message
        // Extended = 0, Data Object = 0
        // ------------------------------------
        case _PD_CMD_RSV:
        case _PD_CMD_GOODCRC:
        case _PD_CMD_GOTOMIN:
        case _PD_CMD_ACCEPT:
        case _PD_CMD_REJECT:
        case _PD_CMD_PING:
        case _PD_CMD_PS_RDY:
        case _PD_CMD_GET_SRC_CAP:
        case _PD_CMD_GET_SNK_CAP:
        case _PD_CMD_DR_SWAP:
        case _PD_CMD_PR_SWAP:
        case _PD_CMD_VCONN_SWAP:
        case _PD_CMD_WAIT:
        case _PD_CMD_SOFT_RESET:
#if(_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_0)
        case _PD_CMD_NOT_SUPPORT:
#endif
            ucExtendedBit = 0;
            ucDataObjectCnt = 0;

            break;

        // ------------------------------------
        // Data Message
        // Extended = 0, Data Object = According to Message Type
        // ------------------------------------
        case _PD_CMD_SRC_CAP:

            ucExtendedBit = 0;
            ucDataObjectCnt = GET_TCPM_PD_SPR_SRC_PDO_CNT(ucPortIndex);

#if(_PORT_CTRL_EMB_PD3_PPS_SUPPORT == _ON)
            // Do not send PPS PDO when the Spec Version is PD2.0 or not support PPS
            if((GET_TCPM_PD_PPS_SUPPORT(ucPortIndex) == _ON) && (GET_TCPM_PD_SPEC_VER(ucPortIndex) == _PD_VERSION_2_0))
#endif
            {
                for(pData[0] = GET_TCPM_PD_SPR_SRC_PDO_CNT(ucPortIndex) - 1; pData[0] > 0; pData[0]--)
                {
                    if(GET_TCPM_PD_SRC_PDO_TYPE(ucPortIndex, pData[0]) == _PD_3_PROGRAMMABLE_PDO)
                    {
                        ucDataObjectCnt --;
                    }
                    else
                    {
                        break;
                    }
                }
            }

            break;

        case _PD_CMD_REQUEST:

            ucDataObjectCnt = 1;

            break;

        case _PD_CMD_SNK_CAP:

            ucDataObjectCnt = GET_TCPM_PD_SPR_SNK_PDO_CNT(ucPortIndex);

            break;

        case _PD_CMD_VDM:

            switch(enumVdmCmd)
            {
                case _PD_VDM_CMD_DISCOVER_ID_REQ:
                case _PD_VDM_CMD_DISCOVER_SVID_REQ:
                case _PD_VDM_CMD_DISCOVER_MODE_REQ:
                case _PD_VDM_CMD_ENTER_MODE_REQ:
                case _PD_VDM_CMD_EXIT_MODE_REQ:
                case _PD_VDM_CMD_15:    // Acer Attention (0x15)

                    ucDataObjectCnt = 1;

                    break;

                case _PD_VDM_CMD_ATTENTION_REQ:

                    // If Sub State = SEND_DP_VDM_REQ, Dp Alt Mode Attention
                    if(GET_TCPM_PD_SUB_STATE(ucPortIndex) == _PD_SUB_SEND_DP_VDM_REQ)
                    {
                        ucDataObjectCnt = 2;
                    }
                    else if(GET_TCPM_PD_SUB_STATE(ucPortIndex) == _PD_SUB_SEND_LENOVO_VDM_REQ)
                    {
                        ucDataObjectCnt = 1;
                    }
                    else if(GET_TCPM_PD_SUB_STATE(ucPortIndex) == _PD_SUB_SEND_HP_VDM_REQ)
                    {
                        ucDataObjectCnt = 2;
                    }

                    break;

                // If SVID = _DP_SID, CMD_10 = DP_Status REQ and CMD_11 = DP_Config REQ
                case _PD_VDM_CMD_10:
                case _PD_VDM_CMD_11:

                    ucDataObjectCnt = 2;

                    break;

                case _PD_VDM_CMD_RESERVED:
                default:

                    ucDataObjectCnt = 0;
                    break;
            }

            break;

#if(_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_0)
        case _PD_CMD_BAT_STATUS:        // Not Implemented
        case _PD_CMD_ALERT:
        case _PD_CMD_GET_COUNTRY_INFO:  // Not Implemented

            ucDataObjectCnt = 1;

            break;
#endif  // #if(_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_0)

        // ------------------------------------
        // Extended Message
        // Extended = 1, Data Object = According to Message Type
        // ------------------------------------
        default:

            ucExtendedBit = 0;
            ucDataObjectCnt = 0;

            break;
    }

    // 2. Construct Data Object into Tx FIFO, if Number of Data Object is not 0
    if(ucDataObjectCnt != 0)
    {
        ScalerTypeCTcpmPdConstructDataObj(ucPortIndex, enumPacketType, enumPdCmd, enumVdmCmd);
    }

    // 3. Construct Message Header
    // [15] Extended, [14:12] Num of Data Obj., [4:0] Command
    usMsgHeader = (((ucExtendedBit & (_BIT0)) << 15) | ((ucDataObjectCnt & (_BIT2 | _BIT1 | _BIT0)) << 12) | (enumPdCmd & (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)));

    if(enumPacketType == _PD_SOP_PKT)
    {
        // [11:9] Message ID, [8] Power Role, [7:6] Spec Ver, [5] Data Role
        usMsgHeader = (usMsgHeader | (GET_TCPM_PD_TX_MSG_ID_SOP(ucPortIndex) << 9) | (GET_TCPM_POWER_ROLE(ucPortIndex) << 8) | (GET_TCPM_PD_SPEC_VER(ucPortIndex) << 6) | (GET_TCPM_DATA_ROLE(ucPortIndex) << 5));
    }
    else if(enumPacketType == _PD_SOP_P_PKT)
    {
        // [11:9] Message ID, [8] Cable Plug : Device(0), [7:6] Spec Ver, [5] Rsv.
        usMsgHeader = (usMsgHeader | (GET_TCPM_PD_TX_MSG_ID_SOP_P(ucPortIndex) << 9) | (GET_TCPM_PD_CBL_SPEC_VER(ucPortIndex) << 6));
    }
    else if(enumPacketType == _PD_SOP_PP_PKT)
    {
        // [11:9] Message ID, [8] Cable Plug : Device(0), [7:6] Spec Ver, [5] Rsv.
        usMsgHeader = (usMsgHeader | (GET_TCPM_PD_TX_MSG_ID_SOP_PP(ucPortIndex) << 9) | (GET_TCPM_PD_CBL_SPEC_VER(ucPortIndex) << 6));
    }

    // 4. Write Message to TCPC Tx Buffer (Port, TxByteCnt, Message Header)
    ScalerTypeCTcpmTcpciSetTxBuffer(ucPortIndex, enumPdCmd, (2 + (ucDataObjectCnt * 4)), usMsgHeader);
}

//--------------------------------------------------
// Description  : Type C TCPM Construct PD Message to Send
// Input Value  : ucPortIndex, enumPacketType, enumPdCmd, enumVdmCmd
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmPdConstructDataObj(BYTE ucPortIndex, EnumTypeCPDPacketType enumPacketType, EnumTypeCPDCmd enumPdCmd, EnumTypeCVdmCmd enumVdmCmd)
{
    // Clear ucDataObj_EXINT
    memset(g_pucTypeCTcpmPdDataObj, 0, sizeof(g_pucTypeCTcpmPdDataObj));

    // Process Data Object Fields For FIFO Fill
    switch(enumPdCmd)
    {
        case _PD_CMD_SRC_CAP:

            // | 31 | 30 | 29 | 28 | 27 | 26 | 25 | 24 |
            // | PDO Type| DRP| Sus| UP | UC | DRD| Unc|
            if((GET_TCPM_PD_SRC_ACCEPT_SWAP_TO_SNK(ucPortIndex) == _TRUE) || (GET_TCPM_PD_SNK_ACCEPT_SWAP_TO_SRC(ucPortIndex) == _TRUE) || (GET_TCPM_PD_SRC_REQUEST_SWAP_TO_SNK(ucPortIndex) == _TRUE) || (GET_TCPM_PD_SNK_REQUEST_SWAP_TO_SRC(ucPortIndex) == _TRUE))
            {
                if(GET_TCPM_CC_PORT_ROLE(ucPortIndex) == _TYPE_C_PORT_DRP)
                {
                    g_pucTypeCTcpmPdDataObj[0] = g_pucTypeCTcpmPdDataObj[0] | (_BIT5);
                }
            }

#if(_USB_SUSPEND == _TRUE)
            g_pucTypeCTcpmPdDataObj[0] = g_pucTypeCTcpmPdDataObj[0] | (_BIT4);
#endif
            if(GET_TCPM_PD_UNCONSTRAIN_POWER(ucPortIndex) == _TRUE)
            {
                g_pucTypeCTcpmPdDataObj[0] = g_pucTypeCTcpmPdDataObj[0] | (_BIT3);
            }

            if(GET_TCPM_USB_ROLE(ucPortIndex) != _TYPE_C_USB_NOT_SUPPORT)
            {
                // TCPM Enable USB Support
                g_pucTypeCTcpmPdDataObj[0] = g_pucTypeCTcpmPdDataObj[0] | (_BIT2);
            }

            if((GET_TCPM_PD_DFP_SWAP_TO_UFP(ucPortIndex) == _TRUE) || (GET_TCPM_PD_UFP_SWAP_TO_DFP(ucPortIndex) == _TRUE))
            {
                g_pucTypeCTcpmPdDataObj[0] = g_pucTypeCTcpmPdDataObj[0] | (_BIT1);
            }

#if(_UNCHUNK_SUPPORT == _TRUE)
            if(GET_TCPM_PD_SPEC_VER(ucPortIndex) == _PD_VERSION_3_0)
            {
                g_pucTypeCTcpmPdDataObj[0] = g_pucTypeCTcpmPdDataObj[0] | (_BIT0);
            }
#endif

            // [23] EPR Mode Capable
            if(GET_TCPM_PD_EPR_SRC_CAPABLE(ucPortIndex) == _TRUE)
            {
                g_pucTypeCTcpmPdDataObj[1] = g_pucTypeCTcpmPdDataObj[1] | (_BIT7);
            }

            for(pData[1] = 0; pData[1] < GET_TCPM_PD_SPR_SRC_PDO_CNT(ucPortIndex); pData[1] ++)
            {
                if(GET_TCPM_PD_SRC_PDO_TYPE(ucPortIndex, pData[1]) == _PD_FIX_SUPPLY_PDO)
                {
                    // [31:30] PDO Type = 2'b00 (Fixed Power Supply)
                    g_pucTypeCTcpmPdDataObj[(pData[1] * 4)] = g_pucTypeCTcpmPdDataObj[(pData[1] * 4)] | (((BYTE)GET_TCPM_PD_SRC_PDO_TYPE(ucPortIndex, pData[1])) << 6);

                    // | 23 | 22 | 21 | 20 | 19 | 18 | 17 | 16 |
                    // |  Rsv(0) | Peak Cur| Voltage(50mV)[9:6]|
                    g_pucTypeCTcpmPdDataObj[(pData[1] * 4) + 1] = g_pucTypeCTcpmPdDataObj[(pData[1] * 4) + 1] | ((BYTE)(GET_TCPM_PD_SRC_CAP_PEAK(ucPortIndex, pData[1]) << 4) & (_BIT5 | _BIT4));
                    g_pucTypeCTcpmPdDataObj[(pData[1] * 4) + 1] = g_pucTypeCTcpmPdDataObj[(pData[1] * 4) + 1] | ((BYTE)((GET_TCPM_PD_SRC_CAP_VOL_MAX(ucPortIndex, pData[1]) / 5) >> 6) & (_BIT3 | _BIT2 | _BIT1 | _BIT0));

                    // | 15 | 14 | 13 | 12 | 11 | 10 | 09 | 08 | 07 | 06 | 05 | 04 | 03 | 02 | 01 | 00 |
                    // |     Voltage(50mV) [5:0]     |                  Max.Cur [7:0]                  |
                    g_pucTypeCTcpmPdDataObj[(pData[1] * 4) + 2] = g_pucTypeCTcpmPdDataObj[(pData[1] * 4) + 2] | ((BYTE)((GET_TCPM_PD_SRC_CAP_VOL_MAX(ucPortIndex, pData[1]) / 5) << 2) & (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2));

                    if((GET_TCPM_POWER_ROLE(ucPortIndex) == _PD_POWER_SRC) && (GET_TCPM_PD_SRC_CAP_CUR(ucPortIndex, pData[1]) > GET_TCPM_PD_CBL_MAX_CUR(ucPortIndex)))
                    {
                        // When Power Role = SRC, Adjust Source Capabilty Current Acording to Cable Info, Make Sure Current Not > Cable Current
                        g_pucTypeCTcpmPdDataObj[(pData[1] * 4) + 2] = g_pucTypeCTcpmPdDataObj[(pData[1] * 4) + 2] | ((BYTE)(GET_TCPM_PD_CBL_MAX_CUR(ucPortIndex) >> 8) & (_BIT1 | _BIT0));
                        g_pucTypeCTcpmPdDataObj[(pData[1] * 4) + 3] = g_pucTypeCTcpmPdDataObj[(pData[1] * 4) + 3] | ((BYTE)GET_TCPM_PD_CBL_MAX_CUR(ucPortIndex));
                    }
                    else
                    {
                        // When Power Role = SRC and Source Capabilty Current < Cable Current, Then No Need to Concern Cable's Info
                        // When Power Role = SNK, It Should Provide Full Source Capabilities (That is, The PDOs Declared By The VIF)
                        g_pucTypeCTcpmPdDataObj[(pData[1] * 4) + 2] = g_pucTypeCTcpmPdDataObj[(pData[1] * 4) + 2] | ((BYTE)(GET_TCPM_PD_SRC_CAP_CUR(ucPortIndex, pData[1]) >> 8) & (_BIT1 | _BIT0));
                        g_pucTypeCTcpmPdDataObj[(pData[1] * 4) + 3] = g_pucTypeCTcpmPdDataObj[(pData[1] * 4) + 3] | ((BYTE)(GET_TCPM_PD_SRC_CAP_CUR(ucPortIndex, pData[1])));
                    }
                }
#if(_PORT_CTRL_EMB_PD3_PPS_SUPPORT == _ON)
                else if((GET_TCPM_PD_SPEC_VER(ucPortIndex) == _PD_VERSION_3_0) && (GET_TCPM_PD_SRC_PDO_TYPE(ucPortIndex, pData[1]) == _PD_3_PROGRAMMABLE_PDO))
                {
                    // [31:30] PDO Type = 2'b11 (Programmabl Power Supply)
                    g_pucTypeCTcpmPdDataObj[(pData[1] * 4)] = g_pucTypeCTcpmPdDataObj[(pData[1] * 4)] | (((BYTE)GET_TCPM_PD_SRC_PDO_TYPE(ucPortIndex, pData[1])) << 6);

                    // [24:17] Max Voltage in 100mV
                    g_pucTypeCTcpmPdDataObj[(pData[1] * 4)] = g_pucTypeCTcpmPdDataObj[(pData[1] * 4)] | ((BYTE)((GET_TCPM_PD_SRC_CAP_VOL_MAX(ucPortIndex, pData[1]) / 10) >> 7) & (_BIT0));
                    g_pucTypeCTcpmPdDataObj[(pData[1] * 4) + 1] = g_pucTypeCTcpmPdDataObj[(pData[1] * 4) + 1] | ((BYTE)((GET_TCPM_PD_SRC_CAP_VOL_MAX(ucPortIndex, pData[1]) / 10) << 1) & (~_BIT0));

                    // [15:8] Min Voltage in 100mV
                    g_pucTypeCTcpmPdDataObj[(pData[1] * 4) + 2] = (BYTE)(GET_TCPM_PD_SRC_CAP_VOL_MIN(ucPortIndex, pData[1]) / 10);

                    // [6:0] Max Current in 50mA
                    if((GET_TCPM_POWER_ROLE(ucPortIndex) == _PD_POWER_SRC) && (((GET_TCPM_PD_SRC_CAP_CUR(ucPortIndex, pData[1])) * 5) > GET_TCPM_PD_CBL_MAX_CUR(ucPortIndex)))
                    {
                        // When Power Role = SRC, Adjust Source Capabilty Current Acording to Cable Info, Make Sure Current Not > Cable Current
                        g_pucTypeCTcpmPdDataObj[(pData[1] * 4) + 3] = (((BYTE)(GET_TCPM_PD_CBL_MAX_CUR(ucPortIndex) / 5)) & (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
                    }
                    else
                    {
                        // When Power Role = SRC and Source Capabilty Current < Cable Current, Then No Need to Concern Cable's Info
                        // When Power Role = SNK, It Should Provide Full Source Capabilities (That is, The PDOs Declared By The VIF)
                        g_pucTypeCTcpmPdDataObj[(pData[1] * 4) + 3] = (((BYTE)GET_TCPM_PD_SRC_CAP_CUR(ucPortIndex, pData[1])) & (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
                    }
                }
#endif  // End of #if(_PORT_CTRL_EMB_PD3_PPS_SUPPORT == _ON)
            }

            break;

        case _PD_CMD_REQUEST:

            // | 31 | 30 | 29 | 28 | 27 | 26 | 25 | 24 |
            // | 0  |   Obj. Pos   | GB | CM | UC | Sus|
            g_pucTypeCTcpmPdDataObj[0] = g_pucTypeCTcpmPdDataObj[0] | (GET_TCPM_PD_REQ_OBJ_POS(ucPortIndex) << 4);
            g_pucTypeCTcpmPdDataObj[0] = g_pucTypeCTcpmPdDataObj[0] | (GET_TCPM_PD_REQ_GIVE_BACK(ucPortIndex) << 3);

            if((GET_TCPM_USB_ROLE(ucPortIndex) != _TYPE_C_USB_NOT_SUPPORT) || (GET_TCPM_USB_SPEED(ucPortIndex) == _USB_BILLBOARD_ONLY))
            {
                g_pucTypeCTcpmPdDataObj[0] = g_pucTypeCTcpmPdDataObj[0] | (_BIT1);
            }

#if(_USB_SUSPEND == _FALSE)
            g_pucTypeCTcpmPdDataObj[0] = g_pucTypeCTcpmPdDataObj[0] | (_BIT0);
#endif

            // | 23 | 22 | 21 | 20 | 19 | ... | 16 | 15 | ... | 10 | 09 | 08 | 07 | ... | 00 |
            // | UC | Reserved(0)  |         Info1 [19:10]         |       Info2 [9:0]       |
#if(_UNCHUNK_SUPPORT == _TRUE)
            g_pucTypeCTcpmPdDataObj[1] = g_pucTypeCTcpmPdDataObj[1] | (_BIT7);
#endif

            if(GET_TCPM_PD_PARTNER_SRC_CAP_TYPE(ucPortIndex, GET_TCPM_PD_REQ_OBJ_POS(ucPortIndex) - 1) == _PD_FIX_SUPPLY_PDO)
            {
                if((WORD)GET_TCPM_PD_PARTNER_SRC_CAP_CUR(ucPortIndex, GET_TCPM_PD_REQ_OBJ_POS(ucPortIndex) - 1) < GET_TCPM_PD_REQ_INFO_2(ucPortIndex))
                {
                    // Set Capability Mismatch Flag
                    g_pucTypeCTcpmPdDataObj[0] = g_pucTypeCTcpmPdDataObj[0] | (_BIT2);

                    // RDO[19:10] : Fix (Op. Cur in 10mA)
                    g_pucTypeCTcpmPdDataObj[1] = g_pucTypeCTcpmPdDataObj[1] | ((BYTE)(GET_TCPM_PD_PARTNER_SRC_CAP_CUR(ucPortIndex, GET_TCPM_PD_REQ_OBJ_POS(ucPortIndex) - 1) >> 6) & (_BIT3 | _BIT2 | _BIT1 | _BIT0));
                    g_pucTypeCTcpmPdDataObj[2] = g_pucTypeCTcpmPdDataObj[2] | ((BYTE)(GET_TCPM_PD_PARTNER_SRC_CAP_CUR(ucPortIndex, GET_TCPM_PD_REQ_OBJ_POS(ucPortIndex) - 1) << 2) & (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2));

                    // RDO[9:0] : Fix (Max. Cur in 10mA)
                    g_pucTypeCTcpmPdDataObj[2] = g_pucTypeCTcpmPdDataObj[2] | ((BYTE)(GET_TCPM_PD_PARTNER_SRC_CAP_CUR(ucPortIndex, GET_TCPM_PD_REQ_OBJ_POS(ucPortIndex) - 1) >> 8) & (_BIT1 | _BIT0));
                    g_pucTypeCTcpmPdDataObj[3] = g_pucTypeCTcpmPdDataObj[3] | (BYTE)(GET_TCPM_PD_PARTNER_SRC_CAP_CUR(ucPortIndex, GET_TCPM_PD_REQ_OBJ_POS(ucPortIndex) - 1));
                }
                else
                {
                    // Set Capability Mismatch Flag
                    g_pucTypeCTcpmPdDataObj[0] = g_pucTypeCTcpmPdDataObj[0] | ((GET_TCPM_PD_REQ_CAP_MIS(ucPortIndex) << 2) & (_BIT2));

                    // RDO[19:10] : Fix (Op. Cur in 10mA)
                    g_pucTypeCTcpmPdDataObj[1] = g_pucTypeCTcpmPdDataObj[1] | ((BYTE)(GET_TCPM_PD_REQ_INFO_1(ucPortIndex) >> 6) & (_BIT3 | _BIT2 | _BIT1 | _BIT0));
                    g_pucTypeCTcpmPdDataObj[2] = g_pucTypeCTcpmPdDataObj[2] | ((BYTE)(GET_TCPM_PD_REQ_INFO_1(ucPortIndex) << 2) & (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2));

                    // RDO[9:0] : Fix (Max. Cur in 10mA)
                    g_pucTypeCTcpmPdDataObj[2] = g_pucTypeCTcpmPdDataObj[2] | ((BYTE)(GET_TCPM_PD_REQ_INFO_2(ucPortIndex) >> 8) & (_BIT1 | _BIT0));
                    g_pucTypeCTcpmPdDataObj[3] = g_pucTypeCTcpmPdDataObj[3] | (BYTE)(GET_TCPM_PD_REQ_INFO_2(ucPortIndex));
                }
            }
            else
            {
                // Set Capability Mismatch Flag
                g_pucTypeCTcpmPdDataObj[0] = g_pucTypeCTcpmPdDataObj[0] | ((GET_TCPM_PD_REQ_CAP_MIS(ucPortIndex) << 2) & (_BIT2));

                // RDO[19:9] : PPS (Vol in 20mV)
                g_pucTypeCTcpmPdDataObj[1] = g_pucTypeCTcpmPdDataObj[1] | ((BYTE)(GET_TCPM_PD_REQ_INFO_1(ucPortIndex) >> 7) & (_BIT3 | _BIT2 | _BIT1 | _BIT0));
                g_pucTypeCTcpmPdDataObj[2] = g_pucTypeCTcpmPdDataObj[2] | ((BYTE)(GET_TCPM_PD_REQ_INFO_1(ucPortIndex) << 1) & (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1));

                // RDO[6:0] : PPS (Op. Cur in 50mA)
                g_pucTypeCTcpmPdDataObj[3] = g_pucTypeCTcpmPdDataObj[3] | ((BYTE)(GET_TCPM_PD_REQ_INFO_2(ucPortIndex)) & (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
            }

            break;

        case _PD_CMD_VDM:

            ScalerTypeCTcpmPdConstructVdmDataObj(ucPortIndex, enumPacketType, enumVdmCmd);

            break;

#if(_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_0)
        case _PD_CMD_ALERT:

            // ---------- Data Message (1 Data Object) ----------
            // Set Type of Alert : [30] OVP Event, [26] OCP Event
#if(_TYPE_C_PMIC_OCP_OVP_PROCESS_OPTION == _TYPE_C_PMIC_PROCESS_OPTION_HARD_RESET)
            if((GET_TCPM_PD_SYS_EVENT(ucPortIndex) & _PD_SYS_EVENT_POWER_OVP) == _PD_SYS_EVENT_POWER_OVP)
            {
                g_pucTypeCTcpmPdDataObj[0] = g_pucTypeCTcpmPdDataObj[0] | (_BIT6);
            }
            if((GET_TCPM_PD_SYS_EVENT(ucPortIndex) & _PD_SYS_EVENT_POWER_OCP) == _PD_SYS_EVENT_POWER_OCP)
            {
                g_pucTypeCTcpmPdDataObj[0] = g_pucTypeCTcpmPdDataObj[0] | (_BIT2);
            }
#endif

            // [31:24] Type of Alert
            g_pucTypeCTcpmPdDataObj[0] = g_pucTypeCTcpmPdDataObj[0] | (BYTE)(GET_TCPM_PD_TYPE_OF_ALERT(ucPortIndex));

            // [23:20] Fixed Batteries, [19:16] Hot Swappable Batteries
            g_pucTypeCTcpmPdDataObj[1] = g_pucTypeCTcpmPdDataObj[1] | (BYTE)(GET_TCPM_PD_BAT_STATUS(ucPortIndex));

            // [15:4] Rsv., [3:0] Extended Alert Event Type
            g_pucTypeCTcpmPdDataObj[3] = g_pucTypeCTcpmPdDataObj[3] | ((BYTE)(GET_TCPM_PD_EXT_ALERT_EVENT(ucPortIndex)) & (_BIT3 | _BIT2 | _BIT1 | _BIT0));

            break;
#endif  // #if(_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_0)

        default:

            break;
    }// End of switch(enumPdCmd)
}

//--------------------------------------------------
// Description  : Fill Data Objects into TX FIFO
// Input Value  : ucPortIndex, enumPacketType, enumVdmCmd
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmPdConstructVdmDataObj(BYTE ucPortIndex, EnumTypeCPDPacketType enumPacketType, EnumTypeCVdmCmd enumVdmCmd)
{
    switch(enumVdmCmd)
    {
        case _PD_VDM_CMD_DISCOVER_ID_REQ:
        case _PD_VDM_CMD_DISCOVER_SVID_REQ:

            // -------- Data Obj 0 : VDM Header --------
            // [31:16] PD SID = 0xFF00
            g_pucTypeCTcpmPdDataObj[0] = 0xFF;
            g_pucTypeCTcpmPdDataObj[1] = 0x00;

            // [15] Struct. VDM = 1, [14:11] SVDM Ver, [10:8] Obj. Pos = b'000
            g_pucTypeCTcpmPdDataObj[2] = (_BIT7);

            // For SOP Packet : If Port Partners Support PD 3.0, [14:13] VDM Spec Version = 2b'01 (Ver 2.0)
            // For SOP' Packet : If Port Partners & Cable Support PD 3.0, [14:13] VDM Spec Version = 2b'01 (Ver 2.0)
            if(((enumPacketType == _PD_SOP_PKT) && (GET_TCPM_PD_SPEC_VER(ucPortIndex) == _PD_VERSION_3_0)) ||
               ((enumPacketType == _PD_SOP_P_PKT) && (GET_TCPM_PD_SPEC_VER(ucPortIndex) == _PD_VERSION_3_0) && (GET_TCPM_PD_CBL_SPEC_VER(ucPortIndex) == _PD_VERSION_3_0)))
            {
                g_pucTypeCTcpmPdDataObj[2] = g_pucTypeCTcpmPdDataObj[2] | (_BIT5);

                // SVDM Version = 2.1 Only when Port Partner or Cable Support 2.1 or Higher
                if(((enumPacketType == _PD_SOP_PKT) && (GET_TCPM_PD_PARTNER_SVDM_VERSION(ucPortIndex) >= _PD_SVDM_VER_2_1)) ||
                   ((enumPacketType == _PD_SOP_P_PKT) && (GET_TCPM_PD_CBL_SVDM_VERSION(ucPortIndex) >= _PD_SVDM_VER_2_1)))
                {
                    // SVDM Header [14:13] Major = b'01 (2.x), [12:11] Minor = b'01 (2.1)
                    g_pucTypeCTcpmPdDataObj[2] = g_pucTypeCTcpmPdDataObj[2] | (_BIT3);
                }
            }

            // [7:0] VDM CMD = Discover ID Request (0x01) / Discover SVID Request (0x02)
            g_pucTypeCTcpmPdDataObj[3] = enumVdmCmd;

            break;

        case _PD_VDM_CMD_DISCOVER_MODE_REQ:

            // -------- Data Obj 0 : VDM Header --------
            if((GET_TCPM_PD_DP_ALT_STATE(ucPortIndex) == _PD_ALT_MODE_SEND_DISCOVER_MODE) || (GET_TCPM_PD_DP_ALT_STATE(ucPortIndex) == _PD_ALT_MODE_SEND_DP_DISCOVER_MODE_SOP_P))
            {
                // [31:16] DP SID = 0xFF01
                g_pucTypeCTcpmPdDataObj[0] = 0xFF;
                g_pucTypeCTcpmPdDataObj[1] = 0x01;
            }
            else if(GET_TCPM_PD_DP_ALT_STATE(ucPortIndex) == _PD_ALT_MODE_SEND_TBT3_DISCOVER_MODE_SOP_P)
            {
                // [31:16] TBT3 SID = 0x8087
                g_pucTypeCTcpmPdDataObj[0] = 0x80;
                g_pucTypeCTcpmPdDataObj[1] = 0x87;
            }

            // [15] Struct. VDM = 1, [14:11] SVDM Ver, [10:8] Obj. Pos = b'000
            g_pucTypeCTcpmPdDataObj[2] = (_BIT7);

            // For SOP Packet : If Port Partners Support PD 3.0, [14:13] VDM Spec Version = 2b'01 (Ver 2.0)
            // For SOP' Packet : If Port Partners & Cable Support PD 3.0, [14:13] VDM Spec Version = 2b'01 (Ver 2.0)
            if(((enumPacketType == _PD_SOP_PKT) && (GET_TCPM_PD_SPEC_VER(ucPortIndex) == _PD_VERSION_3_0)) ||
               ((enumPacketType == _PD_SOP_P_PKT) && (GET_TCPM_PD_SPEC_VER(ucPortIndex) == _PD_VERSION_3_0) && (GET_TCPM_PD_CBL_SPEC_VER(ucPortIndex) == _PD_VERSION_3_0)))
            {
                g_pucTypeCTcpmPdDataObj[2] = g_pucTypeCTcpmPdDataObj[2] | (_BIT5);

                // SVDM Version = 2.1 Only when Port Partner or Cable Support 2.1 or Higher
                if(((enumPacketType == _PD_SOP_PKT) && (GET_TCPM_PD_PARTNER_SVDM_VERSION(ucPortIndex) >= _PD_SVDM_VER_2_1)) ||
                   ((enumPacketType == _PD_SOP_P_PKT) && (GET_TCPM_PD_CBL_SVDM_VERSION(ucPortIndex) >= _PD_SVDM_VER_2_1)))
                {
                    // SVDM Header [14:13] Major = b'01 (2.x), [12:11] Minor = b'01 (2.1)
                    g_pucTypeCTcpmPdDataObj[2] = g_pucTypeCTcpmPdDataObj[2] | (_BIT3);
                }
            }

            // [7:0] VDM CMD = Discover Mode Request (0x03)
            g_pucTypeCTcpmPdDataObj[3] = enumVdmCmd;

            break;

        case _PD_VDM_CMD_ENTER_MODE_REQ:
        case _PD_VDM_CMD_EXIT_MODE_REQ:

            // -------- Data Obj 0 : VDM Header --------
            // [31:16] DP SID = 0xFF01
            g_pucTypeCTcpmPdDataObj[0] = 0xFF;
            g_pucTypeCTcpmPdDataObj[1] = 0x01;

            // [15] Struct. VDM = 1, [14:11] SVDM Ver, [10:8] Obj. Pos = b'001-111
            g_pucTypeCTcpmPdDataObj[2] = (_BIT7) | (GET_TCPM_PD_DPAM_OBJ_POS(ucPortIndex));

            // For SOP Packet : If Port Partners Support PD 3.0, [14:13] VDM Spec Version = 2b'01 (Ver 2.0)
            // For SOP' / SOP" Packet : If Port Partners & Cable Support PD 3.0, [14:13] VDM Spec Version = 2b'01 (Ver 2.0)
            if(((enumPacketType == _PD_SOP_PKT) && (GET_TCPM_PD_SPEC_VER(ucPortIndex) == _PD_VERSION_3_0)) ||
               (((enumPacketType == _PD_SOP_P_PKT) || (enumPacketType == _PD_SOP_PP_PKT)) && (GET_TCPM_PD_SPEC_VER(ucPortIndex) == _PD_VERSION_3_0) && (GET_TCPM_PD_CBL_SPEC_VER(ucPortIndex) == _PD_VERSION_3_0)))
            {
                g_pucTypeCTcpmPdDataObj[2] = g_pucTypeCTcpmPdDataObj[2] | (_BIT5);

                // SVDM Version = 2.1 Only when Port Partner or Cable Support 2.1 or Higher
                if(((enumPacketType == _PD_SOP_PKT) && (GET_TCPM_PD_PARTNER_SVDM_VERSION(ucPortIndex) >= _PD_SVDM_VER_2_1)) ||
                   (((enumPacketType == _PD_SOP_P_PKT) || (enumPacketType == _PD_SOP_PP_PKT)) && (GET_TCPM_PD_CBL_SVDM_VERSION(ucPortIndex) >= _PD_SVDM_VER_2_1)))
                {
                    // SVDM Header [14:13] Major = b'01 (2.x), [12:11] Minor = b'01 (2.1)
                    g_pucTypeCTcpmPdDataObj[2] = g_pucTypeCTcpmPdDataObj[2] | (_BIT3);
                }
            }

            // [7:0] VDM CMD = Enter / Exit Mode Request (0x04 / 0x05)
            g_pucTypeCTcpmPdDataObj[3] = enumVdmCmd;

            break;

        // If SVID = _DP_SID, CMD_10 = DP_Status REQ
        case _PD_VDM_CMD_10:

            // -------- Data Obj 0 : VDM Header --------
            // [31:16] DP SID = 0xFF01
            g_pucTypeCTcpmPdDataObj[0] = 0xFF;
            g_pucTypeCTcpmPdDataObj[1] = 0x01;

            // [15] Struct. VDM = 1, [14:11] SVDM Ver, [10:8] Obj. Pos
            g_pucTypeCTcpmPdDataObj[2] = (_BIT7) | (GET_TCPM_PD_DPAM_OBJ_POS(ucPortIndex));

            // If PD 3.0, [14:13] VDM Spec Version = 2b'01 (Ver 2.0)
            if(GET_TCPM_PD_SPEC_VER(ucPortIndex) == _PD_VERSION_3_0)
            {
                g_pucTypeCTcpmPdDataObj[2] = g_pucTypeCTcpmPdDataObj[2] | (_BIT5);

                // SVDM Version = 2.1 Only when DFP/UFP both Support 2.1 or Higher
                if(GET_TCPM_PD_PARTNER_SVDM_VERSION(ucPortIndex) >= _PD_SVDM_VER_2_1)
                {
                    // SVDM Header [14:13] Major = b'01 (2.x), [12:11] Minor = b'01 (2.1)
                    g_pucTypeCTcpmPdDataObj[2] = g_pucTypeCTcpmPdDataObj[2] | (_BIT3);
                }
            }

            // [7:0] VDM CMD = DP Status Req (0x10)
            g_pucTypeCTcpmPdDataObj[3] = enumVdmCmd;

            // -------- Data Obj 1 : DP Status ---------
            // [31:16] Reserved = 0x00
            g_pucTypeCTcpmPdDataObj[4] = 0x00;
            g_pucTypeCTcpmPdDataObj[5] = 0x00;

#if(_PORT_CTRL_EMB_DP_RX_SUPPORT == _ON)
            if(GET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex) == _TYPE_C_DP_RX)
            {
                // [15:9] Reserved, [8] HPD IRQ, [7] HPD State : HIGH/LOW, [6] Exit DP : No, [5] USB Config = No
                // [4] Multi-Func = No, [3] DP En = No, [2] Low Power = No, [1:0] Connected DP Role : DP_RX(b'10)
                g_pucTypeCTcpmPdDataObj[6] = 0x00;
                g_pucTypeCTcpmPdDataObj[7] = 0x02;

                if(GET_TCPM_PD_FORCE_HPD_IRQ(ucPortIndex) == _TRUE)
                {
                    // HPD = IRQ, HPD_High = 1
                    g_pucTypeCTcpmPdDataObj[7] = (g_pucTypeCTcpmPdDataObj[7]) | (_BIT7);

                    // HPD IRQ = 1
                    g_pucTypeCTcpmPdDataObj[6] = _BIT0;

                    DebugMessageTypeC("8. [PD] Force HPD IRQ : ", 1);
                }
                else
                {
                    if(GET_TCPM_PD_HPD_QUEUE(ucPortIndex, GET_TCPM_PD_HPD_RPTR(ucPortIndex)) == _PD_HPD_LOW)
                    {
                        DebugMessageTypeC("8. [PD] HPD LOW : ", 0);
                    }
                    else
                    {
                        // HPD = HIGH or IRQ, HPD_High = 1
                        g_pucTypeCTcpmPdDataObj[7] = (g_pucTypeCTcpmPdDataObj[7]) | (_BIT7);

                        if(GET_TCPM_PD_HPD_QUEUE(ucPortIndex, GET_TCPM_PD_HPD_RPTR(ucPortIndex)) == _PD_HPD_HIGH)
                        {
                            DebugMessageTypeC("8. [PD] HPD HIGH : ", 1);
                        }
                        else
                        {
                            g_pucTypeCTcpmPdDataObj[6] = _BIT0;

                            DebugMessageTypeC("8. [PD] HPD IRQ : ", 1);
                        }
                    }
                }

                if(GET_TCPM_PD_DPAM_EXIT_REQ(ucPortIndex) == _TRUE)
                {
                    g_pucTypeCTcpmPdDataObj[7] = g_pucTypeCTcpmPdDataObj[7] | (_BIT6);
                }
            }
#endif // End of #if(_PORT_CTRL_EMB_DP_RX_SUPPORT == _ON)

#if(_PORT_CTRL_EMB_DP_TX_SUPPORT == _ON)
            if(GET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex) == _TYPE_C_DP_TX)
            {
                // [15:2] Reserved, [1:0] Connected DP Role : DP_TX(b'01)
                g_pucTypeCTcpmPdDataObj[6] = 0x00;
                g_pucTypeCTcpmPdDataObj[7] = 0x01;
            }
#endif // End of #if(_PORT_CTRL_EMB_DP_TX_SUPPORT == _ON)

            break;

        // If SVID = _DP_SID, CMD_11 = DP_Config REQ
        case _PD_VDM_CMD_11:

            // -------- Data Obj 0 : VDM Header --------
            // [31:16] DP SID = 0xFF01
            g_pucTypeCTcpmPdDataObj[0] = 0xFF;
            g_pucTypeCTcpmPdDataObj[1] = 0x01;

            // [15] Struct. VDM = 1, [14:11] SVDM Ver, [10:8] Obj. Pos
            g_pucTypeCTcpmPdDataObj[2] = (_BIT7) | (GET_TCPM_PD_DPAM_OBJ_POS(ucPortIndex));

            // For SOP Packet : If Port Partners Support PD 3.0, [14:13] VDM Spec Version = 2b'01 (Ver 2.0)
            // For SOP' / SOP" Packet : If Port Partners & Cable Support PD 3.0, [14:13] VDM Spec Version = 2b'01 (Ver 2.0)
            if(((enumPacketType == _PD_SOP_PKT) && (GET_TCPM_PD_SPEC_VER(ucPortIndex) == _PD_VERSION_3_0)) ||
               (((enumPacketType == _PD_SOP_P_PKT) || (enumPacketType == _PD_SOP_PP_PKT)) && (GET_TCPM_PD_SPEC_VER(ucPortIndex) == _PD_VERSION_3_0) && (GET_TCPM_PD_CBL_SPEC_VER(ucPortIndex) == _PD_VERSION_3_0)))
            {
                g_pucTypeCTcpmPdDataObj[2] = g_pucTypeCTcpmPdDataObj[2] | (_BIT5);

                // SVDM Version = 2.1 Only when Port Partner or Cable Support 2.1 or Higher
                if(((enumPacketType == _PD_SOP_PKT) && (GET_TCPM_PD_PARTNER_SVDM_VERSION(ucPortIndex) >= _PD_SVDM_VER_2_1)) ||
                   (((enumPacketType == _PD_SOP_P_PKT) || (enumPacketType == _PD_SOP_PP_PKT)) && (GET_TCPM_PD_CBL_SVDM_VERSION(ucPortIndex) >= _PD_SVDM_VER_2_1)))
                {
                    // SVDM Header [14:13] Major = b'01 (2.x), [12:11] Minor = b'01 (2.1)
                    g_pucTypeCTcpmPdDataObj[2] = g_pucTypeCTcpmPdDataObj[2] | (_BIT3);
                }
            }

            // [7:0] VDM CMD = DP Config Req (0x11)
            g_pucTypeCTcpmPdDataObj[3] = enumVdmCmd;

            // -------- Data Obj 1 : DP Configurations ---------
            if(enumPacketType == _PD_SOP_PKT)
            {
                // DPAM v2.1: [31:30] Get From Discover Mode Ack(SOP), [29:26] Get From Discover Mode Ack(SOP'/SOP'')
                // DPAM v2.1: [31:30] VDO Version , [29:28] Cable Active Component, [27] Rsv, [26] Cable UHBR13.5 Support, [25:24] Rsv; Not DPAM v2.1: [31:24] = 0x00
                if(GET_TCPM_PD_PARTNER_DPAM_VERSION(ucPortIndex) >= _PD_DPAM_VER_2_1_HIGHER)
                {
                    g_pucTypeCTcpmPdDataObj[4] = ((GET_TCPM_PD_PARTNER_DPAM_VERSION(ucPortIndex) << 6) | (GET_TCPM_PD_CBL_ACTIVE_COMPONENT(ucPortIndex) << 4) | (GET_TCPM_PD_CBL_UHBR13P5_SUPPORT(ucPortIndex) << 2));
                }
                else
                {
                    // if Partner VDO Version = 0, Set [31:30] VDO Version = Original Version(00), [29:28] Cable Active Component = Passive(00), [26] Cable UHBR13.5 Support = Not Support(0)
                    g_pucTypeCTcpmPdDataObj[4] = 0x00;
                }

                // [23:16] Rsv
                g_pucTypeCTcpmPdDataObj[5] = 0x00;

                // [15:8] Pin Assignment to be Configured
                g_pucTypeCTcpmPdDataObj[6] = GET_TCPM_PD_DPAM_PIN_ASSIGNMENT(ucPortIndex);

                if(GET_TCPM_PD_DPAM_TARGET_CONFIG(ucPortIndex) == _PD_DP_CONFIG)
                {
                    if(GET_TCPM_PD_PARTNER_DPAM_VERSION(ucPortIndex) >= _PD_DPAM_VER_2_1_HIGHER)
                    {
                        // DPAM v2.1: [7:6] Reserved, [5:2] Signaling for Cable : Get From Discover Mode Ack(SOP'/SOP'')
                        g_pucTypeCTcpmPdDataObj[7] = (GET_TCPM_PD_CBL_MAX_DP_RATE(ucPortIndex) << 2);
                    }
                    else
                    {
                        // if Partner VDO Version = 0, Indicates That Port Partner Don't Support DPAM v2.1 Cable Discovery Flow, Set [5:2] Signaling for Cable = 0001
                        g_pucTypeCTcpmPdDataObj[7] = 0x04;
                    }

#if(_PORT_CTRL_EMB_DP_RX_SUPPORT == _ON)
                    if(GET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex) == _TYPE_C_DP_RX)
                    {
                        // [1:0] Other Side Config = DP_Tx = b'01
                        g_pucTypeCTcpmPdDataObj[7] = (g_pucTypeCTcpmPdDataObj[7] | 0x01);
                    }
#endif

#if(_PORT_CTRL_EMB_DP_TX_SUPPORT == _ON)
                    if(GET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex) == _TYPE_C_DP_TX)
                    {
                        // [1:0] Other Side Config = DP_Rx = b'10
                        g_pucTypeCTcpmPdDataObj[7] = (g_pucTypeCTcpmPdDataObj[7] | 0x02);
                    }
#endif
                }
                else
                {
                    // [7:6] Reserved, [5:2] Signaling : Signaling unspecified = b'0000, [1:0] Other Side Config = Config USB = b'00
                    g_pucTypeCTcpmPdDataObj[7] = 0x00;
                }
            }
            else if((enumPacketType == _PD_SOP_P_PKT) || (enumPacketType == _PD_SOP_PP_PKT))
            {
                // [15:8] Pin Assignment to be Configured
                g_pucTypeCTcpmPdDataObj[6] = GET_TCPM_PD_DPAM_PIN_ASSIGNMENT(ucPortIndex);

                if(GET_TCPM_PD_DPAM_TARGET_CONFIG(ucPortIndex) == _PD_DP_CONFIG)
                {
                    // DPAM v2.1: [7:6] Reserved, [5:2] Signaling for Transport = b'1 (Select DP Bit Rate)
                    g_pucTypeCTcpmPdDataObj[7] = 0x04;

#if(_PORT_CTRL_EMB_DP_RX_SUPPORT == _ON)
                    if(GET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex) == _TYPE_C_DP_RX)
                    {
                        // [1:0] Other Side Config = DP_Tx = b'01
                        g_pucTypeCTcpmPdDataObj[7] = (g_pucTypeCTcpmPdDataObj[7] | 0x01);
                    }
#endif

#if(_PORT_CTRL_EMB_DP_TX_SUPPORT == _ON)
                    if(GET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex) == _TYPE_C_DP_TX)
                    {
                        // [1:0] Other Side Config = DP_Rx = b'10
                        g_pucTypeCTcpmPdDataObj[7] = (g_pucTypeCTcpmPdDataObj[7] | 0x02);
                    }
#endif
                }
                else
                {
                    // [7:6] Reserved, [5:2] Signaling : Signaling unspecified = b'0000, [1:0] Other Side Config = Config USB = b'00
                    g_pucTypeCTcpmPdDataObj[7] = 0x00;
                }
            }

            break;

        case _PD_VDM_CMD_ATTENTION_REQ:

            // If Sub State = SEND_DP_VDM_REQ, Dp Alt Mode Attention
            if(GET_TCPM_PD_SUB_STATE(ucPortIndex) == _PD_SUB_SEND_DP_VDM_REQ)
            {
                // -------- Data Obj 0 : VDM Header --------
                // [31:16] DP SID = 0xFF01
                g_pucTypeCTcpmPdDataObj[0] = 0xFF;
                g_pucTypeCTcpmPdDataObj[1] = 0x01;

                // [15] Struct. VDM = 1, [14:11] SVDM Ver, [10:8] Obj. Pos
                g_pucTypeCTcpmPdDataObj[2] = (_BIT7) | (GET_TCPM_PD_DPAM_OBJ_POS(ucPortIndex));

                // If PD 3.0, [14:13] VDM Spec Version = 2b'01 (Ver 2.0)
                if(GET_TCPM_PD_SPEC_VER(ucPortIndex) == _PD_VERSION_3_0)
                {
                    g_pucTypeCTcpmPdDataObj[2] = g_pucTypeCTcpmPdDataObj[2] | (_BIT5);

                    // UFP Resp. SVDM Version = 2.1 Only when DFP/UFP both Support 2.1 or Higher
                    if(GET_TCPM_PD_PARTNER_SVDM_VERSION(ucPortIndex) >= _PD_SVDM_VER_2_1)
                    {
                        // SVDM Header [14:13] Major = b'01 (2.x), [12:11] Minor = b'01 (2.1)
                        g_pucTypeCTcpmPdDataObj[2] = g_pucTypeCTcpmPdDataObj[2] | (_BIT3);
                    }
                }

                // [7:0] VDM CMD = Attention Req (0x06)
                g_pucTypeCTcpmPdDataObj[3] = enumVdmCmd;

                // -------- Data Obj 1 : DP Status ---------
                // [31:16] Reserved = 0x00
                g_pucTypeCTcpmPdDataObj[4] = 0x00;
                g_pucTypeCTcpmPdDataObj[5] = 0x00;

#if(_PORT_CTRL_EMB_DP_RX_SUPPORT == _ON)
                if(GET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex) == _TYPE_C_DP_RX)
                {
                    // [15:9] Reserved, [8] HPD IRQ, [7] HPD State : HIGH/LOW, [6] Exit DP : No, [5] USB Config = No
                    // [4] Multi-Func = No, [3] DP En = Yes, [2] Low Power = No, [1:0] Connected DP Role : DP_RX(b'10)
                    g_pucTypeCTcpmPdDataObj[6] = 0x00;
                    g_pucTypeCTcpmPdDataObj[7] = (0x0A) | (GET_TCPM_PD_DPAM_MULTI_FUNC(ucPortIndex) << 4);

                    if(GET_TCPM_PD_FORCE_HPD_IRQ(ucPortIndex) == _TRUE)
                    {
                        // HPD = IRQ, HPD_High = 1
                        g_pucTypeCTcpmPdDataObj[7] = (g_pucTypeCTcpmPdDataObj[7]) | (_BIT7);

                        // HPD IRQ = 1
                        g_pucTypeCTcpmPdDataObj[6] = _BIT0;

                        DebugMessageTypeC("8. [PD] Force HPD IRQ : ", 1);
                    }
                    else
                    {
                        if(GET_TCPM_PD_HPD_QUEUE(ucPortIndex, GET_TCPM_PD_HPD_RPTR(ucPortIndex)) == _PD_HPD_LOW)
                        {
                            DebugMessageTypeC("8. [PD] HPD LOW : ", 0);
                        }
                        else
                        {
                            // HPD = HIGH or IRQ, HPD_High = 1
                            g_pucTypeCTcpmPdDataObj[7] = (g_pucTypeCTcpmPdDataObj[7]) | (_BIT7);

                            if(GET_TCPM_PD_HPD_QUEUE(ucPortIndex, GET_TCPM_PD_HPD_RPTR(ucPortIndex)) == _PD_HPD_HIGH)
                            {
                                DebugMessageTypeC("8. [PD] HPD HIGH : ", 1);
                            }
                            else
                            {
                                g_pucTypeCTcpmPdDataObj[6] = _BIT0;

                                DebugMessageTypeC("8. [PD] HPD IRQ : ", 1);
                            }
                        }
                    }

                    if(GET_TCPM_PD_DPAM_EXIT_REQ(ucPortIndex) == _TRUE)
                    {
                        g_pucTypeCTcpmPdDataObj[7] = g_pucTypeCTcpmPdDataObj[7] | (_BIT6);
                    }
                }
#endif // End of #if(_PORT_CTRL_EMB_DP_RX_SUPPORT == _ON)

#if(_PORT_CTRL_EMB_DP_TX_SUPPORT == _ON)
                if(GET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex) == _TYPE_C_DP_TX)
                {
                    // [15:9] Reserved, [8] HPD IRQ : No, [7] HPD State : LOW, [6] Exit DP : No, [5] USB Config = No
                    // [4] Multi-Func, [3] DP En = Yes, [2] Low Power = No, [1:0] Connected DP Role : DP_TX(b'01)
                    g_pucTypeCTcpmPdDataObj[6] = 0x00;
                    g_pucTypeCTcpmPdDataObj[7] = (0x09) | (GET_TCPM_PD_DPAM_MULTI_FUNC(ucPortIndex) << 4);

                    if(GET_TCPM_PD_DPAM_EXIT_REQ(ucPortIndex) == _TRUE)
                    {
                        g_pucTypeCTcpmPdDataObj[7] = g_pucTypeCTcpmPdDataObj[7] | (_BIT6);
                    }
                }
#endif // End of #if(_PORT_CTRL_EMB_DP_TX_SUPPORT == _ON)
            }

            break;

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Type C TCPM Send PD  Soft Reset Message
// Input Value  : ucPortIndex, enumPacketType
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmPdSendSoftRst(BYTE ucPortIndex, EnumTypeCPDPacketType enumPacketType)
{
    BYTE ucTransmitInfo = 0x00;

    // 1. Clear and Enable Tx_SUCCESS + Tx_FAIL + Tx_DISCARD
    ScalerTypeCTcpmAlertControl(ucPortIndex, ((WORD)(_TCPM_TCPCI_ALERT_TX_FAIL | _TCPM_TCPCI_ALERT_TX_DISCARD | _TCPM_TCPCI_ALERT_TX_SUCCESS)), _ENABLE);

    // 2. Construct Message and Write Data to Tx Buffer [0x51~]
    ScalerTypeCTcpmPdConstructSoftRst(ucPortIndex, enumPacketType);

    // 3. Send Message
    // TRANSMIT [0x50] [5:4] Retry Counter (PD2.0 = 3, PD3.0 = 2)
    // TRANSMIT [0x50] [2:0] SOP Type : 000b (SOP), 001b (SOP'), 010b (SOP"),
    if(enumPacketType == _PD_SOP_PKT)
    {
        if(GET_TCPM_PD_SPEC_VER(ucPortIndex) == _PD_VERSION_2_0)
        {
            ucTransmitInfo = ucTransmitInfo | (_BIT5 | _BIT4);
        }
        else
        {
            ucTransmitInfo = ucTransmitInfo | (_BIT5);
        }

        ADD_TCPM_PD_TX_MSG_ID_SOP(ucPortIndex);
    }
    else if(enumPacketType == _PD_SOP_P_PKT)
    {
        if(GET_TCPM_PD_CBL_SPEC_VER(ucPortIndex) == _PD_VERSION_2_0)
        {
            ucTransmitInfo = ucTransmitInfo | (_BIT5 | _BIT4 | _BIT0);
        }
        else
        {
            ucTransmitInfo = ucTransmitInfo | (_BIT5 | _BIT0);
        }

        ADD_TCPM_PD_TX_MSG_ID_SOP_P(ucPortIndex);
    }
    else if(enumPacketType == _PD_SOP_PP_PKT)
    {
        if(GET_TCPM_PD_CBL_SPEC_VER(ucPortIndex) == _PD_VERSION_2_0)
        {
            ucTransmitInfo = ucTransmitInfo | (_BIT5 | _BIT4 | _BIT1);
        }
        else
        {
            ucTransmitInfo = ucTransmitInfo | (_BIT5 | _BIT1);
        }

        ADD_TCPM_PD_TX_MSG_ID_SOP_PP(ucPortIndex);
    }

    ScalerTypeCTcpmTcpciSetTransmit(ucPortIndex, ucTransmitInfo);
}

//--------------------------------------------------
// Description  : Type C TCPM Construct PD Soft Reset Message
// Input Value  : ucPortIndex, enumPacketType
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmPdConstructSoftRst(BYTE ucPortIndex, EnumTypeCPDPacketType enumPacketType)
{
    WORD usMsgHeader_EXINT = 0;

    // 1. Construct Soft Reset Message Header
    // [15] Extended, [14:12] Num of Data Obj., [4:0] Command = _PD_CMD_SOFT_RESET
    usMsgHeader_EXINT = (_PD_CMD_SOFT_RESET & (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

    if(enumPacketType == _PD_SOP_PKT)
    {
        // Reset Message ID
        CLR_TCPM_PD_TX_MSG_ID_SOP(ucPortIndex);
        CLR_TCPM_PD_RX_MSG_ID_SOP(ucPortIndex);

        // [11:9] Message ID, [8] Power Role, [7:6] Spec Ver, [5] Data Role
        usMsgHeader_EXINT = (usMsgHeader_EXINT | (GET_TCPM_PD_TX_MSG_ID_SOP(ucPortIndex) << 9) | (GET_TCPM_POWER_ROLE(ucPortIndex) << 8) | (GET_TCPM_PD_SPEC_VER(ucPortIndex) << 6) | (GET_TCPM_DATA_ROLE(ucPortIndex) << 5));
    }
    else if(enumPacketType == _PD_SOP_P_PKT)
    {
        // Reset Message ID
        CLR_TCPM_PD_TX_MSG_ID_SOP_P(ucPortIndex);
        CLR_TCPM_PD_RX_MSG_ID_SOP_P(ucPortIndex);

        // [11:9] Message ID, [8] Cable Plug : Device(1), [7:6] Spec Ver, [5] Rsv.
        usMsgHeader_EXINT = (usMsgHeader_EXINT | (GET_TCPM_PD_TX_MSG_ID_SOP_P(ucPortIndex) << 9) | (_BIT8) | (GET_TCPM_PD_CBL_SPEC_VER(ucPortIndex) << 6));
    }
    else if(enumPacketType == _PD_SOP_PP_PKT)
    {
        // Reset Message ID
        CLR_TCPM_PD_TX_MSG_ID_SOP_PP(ucPortIndex);
        CLR_TCPM_PD_RX_MSG_ID_SOP_PP(ucPortIndex);

        // [11:9] Message ID, [8] Cable Plug, [7:6] Spec Ver, [5] Rsv.
        usMsgHeader_EXINT = (usMsgHeader_EXINT | (GET_TCPM_PD_TX_MSG_ID_SOP_PP(ucPortIndex) << 9) | (_BIT8) | (GET_TCPM_PD_CBL_SPEC_VER(ucPortIndex) << 6));
    }

    // 4. Write Message to TCPC Tx Buffer (Port, Cmd = Soft Reset, TxByteCnt = 2(Message Header), Message Header)
    ScalerTypeCTcpmTcpciSetTxBuffer(ucPortIndex, _PD_CMD_SOFT_RESET, 2, usMsgHeader_EXINT);
}

//--------------------------------------------------
// Description  : Type C TCPM Send PD  Soft Reset Message
// Input Value  : ucPortIndex
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmPdSendHardRst(BYTE ucPortIndex)
{
    if(GET_TCPM_PD_HARD_RST_CNT(ucPortIndex) <= _MAX_HARD_RST_CNT)
    {
        ADD_TCPM_PD_HARD_RST_CNT(ucPortIndex);

        // Disable Tx Discard, Rx, Sink Disconnect (TCPC Will Set TX_Success + TX_Fail After Sending HRST)
        ScalerTypeCTcpmAlertControl(ucPortIndex, (WORD)(_TCPM_TCPCI_ALERT_RX_RCV_SOP | _TCPM_TCPCI_ALERT_RX_HRST | _TCPM_TCPCI_ALERT_TX_DISCARD | _TCPM_TCPCI_ALERT_RX_OVERFLOW | _TCPM_TCPCI_ALERT_SNK_DISC), _DISABLE);

        // TRANSMIT [0x50] [5:4] Retry Counter (00b), [2:0] SOP Type : 101b (HRST)
        ScalerTypeCTcpmTcpciSetByte(ucPortIndex, _TCPM_TCPCI_REG_TRANSMIT, 0x05);

        // Process Hard Reset
        ScalerTypeCTcpmPdProcHardRst(ucPortIndex);
    }
    else
    {
        SET_TCPM_CC_ERROR_RECOVERY(ucPortIndex);
    }
}

//--------------------------------------------------
// Description  : Type C TCPM Hard Reset Process when Receive, Sent Hard Reset
// Input Value  : ucPortIndex
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmPdProcHardRst(BYTE ucPortIndex)
{
    // Clear Hard Reset Turn Off Power Flag (Set When 1.Power Already Turned Off to vSafe0v for SRC 2.Vbus Already Not vSafe5v)
    CLR_TCPM_PD_HRST_PWR_OFF(ucPortIndex);

    if(GET_TCPM_POWER_ROLE(ucPortIndex) == _PD_POWER_SRC)
    {
        // Source can Start Changing Power After tSrcTransition = 25-35 ms (Vbus + Vconn)
        ScalerTypeCTcpmActiveTimerEvent(ucPortIndex, _SRC_ADJUST_POWER_TIMER, _SCALER_TIMER_EVENT_TCPM_SRC_TURN_OFF_POWER);
    }
    else
    {
        // 1. Turn Off Power Draw, Vbus should be drive to vSafe0V by Source (PD 7.1.5).
        ScalerTypeCTcpmVbusCtrl(ucPortIndex, _OFF, _PD_POWER_SNK, _PD_NONE_SETTING_PDO, 0, 0, _PD_PEAK_CUR_NONE);

        // 2. Turn Off Type-C Unattach Vbus Detection
        // (On-Semi) "DO NOT" Turn Off Vbus Detection, It Will Cause Unattach Immediately
        if(GET_TCPM_TCPC_TYPE(ucPortIndex) != _TCPC_ON_SEMI)
        {
            ScalerTypeCTcpmVbusDetCtrl(ucPortIndex, _DISABLE);
        }

        // 3. Active Wait 3sec for Source to Complete Hard Reset (MM1AE-2705), Canceled when Hard Reset Complete (PD Reset)
        ScalerTypeCTcpmActiveTimerEvent(ucPortIndex, _SNK_HARD_RST_TIMER, _SCALER_TIMER_EVENT_TCPM_SNK_HARD_RST_TIMEOUT);
    }

    // Turn Off Vconn, If Already Turned On
    if(GET_TCPM_VCONN_ROLE(ucPortIndex) == _PD_VCONN_SRC)
    {
        ScalerTypeCTcpmVconnCtrl(ucPortIndex, _OFF);
    }

    // RECEIVE_DETECT Disabled by TCPC
    // Hard Reset Related ALERT Has Been Cleared when Receive Hard Reset

    // State Transition
    SET_TCPM_PD_FW_STATE(ucPortIndex, _PD_HARDRESET);
    SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_STATE_NONE);
    SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NONE);
    SET_TCPM_PD_CBL_STATE(ucPortIndex, _PD_CBL_STATE_NONE);
}

//--------------------------------------------------
// Description  : PD Update Message Info for GoodCRC
// Input Value  : ucPortIndex
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmPdUpdateGoodCRCInfo(BYTE ucPortIndex)
{
    // [4] CABLE_PLUG = 0 (Port), [2:1] SPEC_VER = b'01 (Rev 2.0) for GoodCRC Resp. Always Use Rev 2.0 for Response
    BYTE ucMsgHeaderInfo = 0x02;

    // [3] DATA_ROLE = by Macro (0:UFP, 1:DFP)
    if(GET_TCPM_DATA_ROLE(ucPortIndex) == _PD_DATA_DFP)
    {
        ucMsgHeaderInfo |= (_BIT3);
    }

    // [0] POWER_ROLE = by Macro (0:Sink, 1:Source)
    if(GET_TCPM_POWER_ROLE(ucPortIndex) == _PD_POWER_SRC)
    {
        ucMsgHeaderInfo |= (_BIT0);
    }

    // Set MSG_HEADER_INFO [0x2E] :
    ScalerTypeCTcpmTcpciSetByte(ucPortIndex, _TCPM_TCPCI_REG_MSG_HEADER_INFO, ucMsgHeaderInfo);
}

//--------------------------------------------------
// Description  : Type C TCPM PD Power Switch Process
// Input Value  : ucPortIndex, enumPowerAction
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmPdPowerSwitch(BYTE ucPortIndex, EnumPowerAction enumPowerAction)
{
    ucPortIndex = ucPortIndex;

    switch(enumPowerAction)
    {
        case _POWER_ACTION_AC_ON_TO_NORMAL:
        case _POWER_ACTION_OFF_TO_NORMAL:
        case _POWER_ACTION_FAKE_OFF_TO_NORMAL:
        case _POWER_ACTION_PS_TO_NORMAL:

            // Set DP Alt Mode Lane Mapping
#if(_PORT_CTRL_EMB_DP_RX_SUPPORT == _ON)
            if(GET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex) == _TYPE_C_DP_RX)
            {
                ScalerDpPhyRxSetAltModeLaneMapping(ScalerTypeCPcbPortConvertToDx(g_penumTypeCTcpmPort[ucPortIndex]), GET_TCPM_PD_DPAM_PIN_ASSIGNMENT(ucPortIndex), GET_TCPM_ORIENTATION(ucPortIndex));
            }
#endif

#if(_PORT_CTRL_EMB_DP_TX_SUPPORT == _ON)
            if(GET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex) == _TYPE_C_DP_TX)
            {
                ScalerDpPhyTxSetAltModeLaneMapping(ScalerTypeCPcbPortConvertToPx(g_penumTypeCTcpmPort[ucPortIndex]), GET_TCPM_PD_DPAM_PIN_ASSIGNMENT(ucPortIndex), GET_TCPM_ORIENTATION(ucPortIndex));
            }
#endif

            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Process For OCP / OVP Flow
// Input Value  : ucPortIndex
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmPdOcpOvpProc(BYTE ucPortIndex)
{
#if(_TYPE_C_PMIC_OCP_OVP_PROCESS_OPTION == _TYPE_C_PMIC_PROCESS_OPTION_ERROR_RECOVERY)
    // Set Error Recovery
    SET_TCPM_CC_ERROR_RECOVERY(ucPortIndex);
    CLR_TCPM_PD_SYS_EVENT(ucPortIndex, _PD_SYS_EVENT_POWER_OCP | _PD_SYS_EVENT_POWER_OVP | _PD_SYS_EVENT_POWER_UVP | _PD_SYS_EVENT_VCONN_OCP);
#elif(_TYPE_C_PMIC_OCP_OVP_PROCESS_OPTION == _TYPE_C_PMIC_PROCESS_OPTION_HARD_RESET)
    // PMIC OCP or OVP Triggered : (PD2.0 || Power Contract Not Ready) : Hard Reset, (PD3.0 && Power Contract Ready) : Alert + Hard Reset
    if((GET_TCPM_PD_SPEC_VER(ucPortIndex) == _PD_VERSION_2_0) || (GET_TCPM_PD_EXPLICIT_CONTRACT(ucPortIndex) == _FALSE))
    {
        ScalerTypeCTcpmPdSendHardRst(ucPortIndex);
        CLR_TCPM_PD_SYS_EVENT(ucPortIndex, _PD_SYS_EVENT_POWER_OCP | _PD_SYS_EVENT_POWER_OVP | _PD_SYS_EVENT_POWER_UVP | _PD_SYS_EVENT_VCONN_OCP);
    }
    else if(GET_TCPM_PD_ALERT_SENT(ucPortIndex) == _FALSE)
    {
        // Clear OCP/OVP/UVP/Vconn OCP Event when (Power Contract Established in EXINT0)
        SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_SEND_ALERT);

        if((GET_TCPM_PD_SYS_EVENT(ucPortIndex) & _PD_SYS_EVENT_POWER_OCP) == _PD_SYS_EVENT_POWER_OCP)
        {
            SET_TCPM_PD_TYPE_OF_ALERT(ucPortIndex, _TYPE_C_TYPE_OF_ALERT_OCP);
        }

        if((GET_TCPM_PD_SYS_EVENT(ucPortIndex) & _PD_SYS_EVENT_POWER_OVP) == _PD_SYS_EVENT_POWER_OVP)
        {
            SET_TCPM_PD_TYPE_OF_ALERT(ucPortIndex, _TYPE_C_TYPE_OF_ALERT_OVP);
        }
    }
#elif(_TYPE_C_PMIC_OCP_OVP_PROCESS_OPTION == _TYPE_C_PMIC_PROCESS_OPTION_BY_USER)
    // User directly Design the Processing Flow. Embedded Do Nothing but will refer to the Port Controller Event!
    CLR_TCPM_PD_SYS_EVENT(ucPortIndex, _PD_SYS_EVENT_POWER_OCP | _PD_SYS_EVENT_POWER_OVP | _PD_SYS_EVENT_POWER_UVP | _PD_SYS_EVENT_VCONN_OCP);
#endif
}

//--------------------------------------------------
// Description  : Cancel All Timer Events When CC Unattach
// Input Value  : ucPortIndex
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmPdUnattachCancelTimerEvent(BYTE ucPortIndex)
{
    CLR_TCPM_PD_TIMER_EVENT_VALID(ucPortIndex);

    // Cancel Timer Event
    ScalerTypeCTcpmCancelTimerEvent(ucPortIndex, _SCALER_TIMER_EVENT_TCPM_SNK_HARD_RST_TIMEOUT);
    ScalerTypeCTcpmCancelTimerEvent(ucPortIndex, _SCALER_TIMER_EVENT_TCPM_CLR_REQ_WAIT);
    ScalerTypeCTcpmCancelTimerEvent(ucPortIndex, _SCALER_TIMER_EVENT_TCPM_CLR_PARTNER_ALT_SUPPORT);
    ScalerTypeCTcpmCancelTimerEvent(ucPortIndex, _SCALER_TIMER_EVENT_TCPM_T480_ERROR_RECOVERY);
    ScalerTypeCTcpmCancelTimerEvent(ucPortIndex, _SCALER_TIMER_EVENT_TCPM_SRC_TURN_OFF_POWER);
    ScalerTypeCTcpmCancelTimerEvent(ucPortIndex, _SCALER_TIMER_EVENT_TCPM_SRC_TURN_ON_POWER);
    ScalerTypeCTcpmCancelTimerEvent(ucPortIndex, _SCALER_TIMER_EVENT_TCPM_VDM_RESP_CONFLICT_TIMEOUT);
    ScalerTypeCTcpmCancelTimerEvent(ucPortIndex, _SCALER_TIMER_EVENT_TCPM_CLR_ATTENTION_WAIT);
    ScalerTypeCTcpmCancelTimerEvent(ucPortIndex, _SCALER_TIMER_EVENT_TCPM_CLR_GET_SNK_CAP_WAIT);
    ScalerTypeCTcpmCancelTimerEvent(ucPortIndex, _SCALER_TIMER_EVENT_TCPM_S8_HRST);
    ScalerTypeCTcpmCancelTimerEvent(ucPortIndex, _SCALER_TIMER_EVENT_TCPM_SEND_HARD_RST);
    ScalerTypeCTcpmCancelTimerEvent(ucPortIndex, _SCALER_TIMER_EVENT_TCPM_TPC_ERROR_RECOVERY);
    ScalerTypeCTcpmCancelTimerEvent(ucPortIndex, _SCALER_TIMER_EVENT_TCPM_CLR_PRS_WAIT);
    ScalerTypeCTcpmCancelTimerEvent(ucPortIndex, _SCALER_TIMER_EVENT_TCPM_CLR_DRS_WAIT);
    ScalerTypeCTcpmCancelTimerEvent(ucPortIndex, _SCALER_TIMER_EVENT_TCPM_CLR_VCS_WAIT);
    ScalerTypeCTcpmCancelTimerEvent(ucPortIndex, _SCALER_TIMER_EVENT_TCPM_CLR_VDMMSG_WAIT);
    ScalerTypeCTcpmCancelTimerEvent(ucPortIndex, _SCALER_TIMER_EVENT_TCPM_CLR_VDM_BUSY_FLAG);
    ScalerTypeCTcpmCancelTimerEvent(ucPortIndex, _SCALER_TIMER_EVENT_TCPM_DFP_START_ALT_MODE);
#if(_PORT_CTRL_EMB_PD3_PPS_SUPPORT == _ON)
    ScalerTypeCTcpmCancelTimerEvent(ucPortIndex, _SCALER_TIMER_EVENT_TCPM_PPS_TIMEOUT);
#endif
#if(_PORT_CTRL_TCPM_OVP_UVP_SUPPORT == _ON)
    ScalerTypeCTcpmCancelTimerEvent(ucPortIndex, _SCALER_TIMER_EVENT_TCPM_OVP_UVP_CHECK);
#endif
#if((_TYPE_C_PMIC_SUPPORT == _ON) && (_PORT_CTRL_TCPM_PMIC_CHECK_SUPPORT == _ON))
    ScalerTypeCTcpmCancelTimerEvent(ucPortIndex, _SCALER_TIMER_EVENT_TCPM_PMIC_TRACKING);
    ScalerTypeCTcpmCancelTimerEvent(ucPortIndex, _SCALER_TIMER_EVENT_TCPM_PMIC_POLLING_OCP);
#endif

    SET_TCPM_WD_TIME_LEFT(ucPortIndex, 0);
    CLR_TCPM_WD_EVENT_TRIGGERED(ucPortIndex);

    // Cancel WD Timer Event
    ScalerTypeCTcpmWDCancelTimerEvent(ucPortIndex, _SCALER_WD_TIMER_EVENT_TCPM_CC_DEBOUNCE);
    ScalerTypeCTcpmWDCancelTimerEvent(ucPortIndex, _SCALER_WD_TIMER_EVENT_TCPM_PD_DEBOUNCE);
    ScalerTypeCTcpmWDCancelTimerEvent(ucPortIndex, _SCALER_WD_TIMER_EVENT_TCPM_CBL_TIMEOUT);
    ScalerTypeCTcpmWDCancelTimerEvent(ucPortIndex, _SCALER_WD_TIMER_EVENT_TCPM_SEND_SRC_CAP);
    ScalerTypeCTcpmWDCancelTimerEvent(ucPortIndex, _SCALER_WD_TIMER_EVENT_TCPM_SENDER_RESP_TIMEOUT);
    ScalerTypeCTcpmWDCancelTimerEvent(ucPortIndex, _SCALER_WD_TIMER_EVENT_TCPM_PS_TRANSITION_TIMEOUT);
    ScalerTypeCTcpmWDCancelTimerEvent(ucPortIndex, _SCALER_WD_TIMER_EVENT_TCPM_SRC_TURN_ON_POWER);
    ScalerTypeCTcpmWDCancelTimerEvent(ucPortIndex, _SCALER_WD_TIMER_EVENT_TCPM_SRC_TURN_OFF_POWER);
    ScalerTypeCTcpmWDCancelTimerEvent(ucPortIndex, _SCALER_WD_TIMER_EVENT_TCPM_CHECK_VBUS);
    ScalerTypeCTcpmWDCancelTimerEvent(ucPortIndex, _SCALER_WD_TIMER_EVENT_TCPM_BACK_TO_READY_STATE);
    ScalerTypeCTcpmWDCancelTimerEvent(ucPortIndex, _SCALER_WD_TIMER_EVENT_TCPM_SEND_HARD_RST);
    ScalerTypeCTcpmWDCancelTimerEvent(ucPortIndex, _SCALER_WD_TIMER_EVENT_TCPM_SEND_REQUEST);
    ScalerTypeCTcpmWDCancelTimerEvent(ucPortIndex, _SCALER_WD_TIMER_EVENT_TCPM_VDM_RESP_TIMEOUT);
    ScalerTypeCTcpmWDCancelTimerEvent(ucPortIndex, _SCALER_WD_TIMER_EVENT_TCPM_SNK_SWITCH_TO_SRC);
    ScalerTypeCTcpmWDCancelTimerEvent(ucPortIndex, _SCALER_WD_TIMER_EVENT_TCPM_SEND_VCONN_ON_PSRDY);
}

//--------------------------------------------------
// Description  : Check if Tx HW is Avaliable (PD 3.0 : Check TxSinkOK/NG, PD 2.0 : Check PHY Idle)
// Input Value  : ucPortIndex
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerTypeCTcpmPdTxAvaliable(BYTE ucPortIndex)
{
    bit bCheckResult = _FALSE;

    if(GET_TCPM_PD_SPEC_VER(ucPortIndex) == _PD_VERSION_3_0)
    {
        if(GET_TCPM_POWER_ROLE(ucPortIndex) == _PD_POWER_SRC)
        {
            // Source Can Initiate AMS 16-20ms After Change Rp to SinkTxNG (Rp-1.5A)
            // ROLE_CONTROL [0x1A], [5:4] = b'00(Rp-Def), b'01(Rp-1.5A), b'10(Rp-3A)
            SET_TCPM_ROLE_CONTROL(ucPortIndex, (GET_TCPM_ROLE_CONTROL(ucPortIndex) & (~(_BIT5 | _BIT4))) | (_BIT4));
            ScalerTypeCTcpmTcpciSetByte(ucPortIndex, _TCPM_TCPCI_REG_ROLE_CTRL, GET_TCPM_ROLE_CONTROL(ucPortIndex));

            ScalerTimerDelayXms(_SRC_INIT_AMS_TIMER);

            if((GET_TCPM_ROLE_CONTROL(ucPortIndex) & (_BIT5 | _BIT4)) == (_BIT4))
            {
                // Check if Rp is Still SinkTxNG Before Initiate AMS, Prevent Receive Message During the Delay Time and Reset Rp to SinkTxOK.
                bCheckResult = _TRUE;
            }
        }
        else
        {
            if(ScalerTypeCTcpmCcDetResistor(ucPortIndex) == _TYPE_C_DET_RP_3P0A)
            {
                // Rp = SinkTxOK (Rp 3.0A)
                bCheckResult = _TRUE;
            }
            else
            {
                // Rp = SinkTxNG (Rp 1.5A)
                bCheckResult = _FALSE;
            }
        }
    }
    else
    {
        // Always Return _TRUE, TCPC will trigger TX Discard Alert if PHY Non-Idle
        bCheckResult = _TRUE;
    }

    return bCheckResult;
}

//--------------------------------------------------
// Description  : Clear HPD Queue When PD Reset TO Prevent DP Urgent Event DeadLock
// Input Value  : ucPortIndex
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmPdClrHpd(BYTE ucPortIndex)
{
    BYTE ucIndex = 0;
    EnumTypeCPcbPort enumTypeCPcbPort = g_penumTypeCTcpmPort[ucPortIndex];

    for(ucIndex = 0; ucIndex < _HPD_QUEUE_DEPTH; ucIndex++)
    {
        SET_TCPM_PD_HPD_QUEUE(ucPortIndex, _PD_HPD_NONE);
        SET_TCPM_PD_HPD_SPACE_TIME(ucPortIndex, 0);
        ADD_TCPM_PD_HPD_WPTR(ucPortIndex);
    }

#if(_DP_SUPPORT == _ON)
    ScalerDpAuxRxHpdTogglePhyResetProc(ScalerTypeCPcbPortConvertToDx(enumTypeCPcbPort), _LOW);
#endif

    SET_TCPM_PD_HPD_STATUS(ucPortIndex, _LOW);
    CLR_TCPM_PD_HPD_WPTR(ucPortIndex);
    CLR_TCPM_PD_HPD_RPTR(ucPortIndex);
    CLR_TCPM_PD_HPD_CNT(ucPortIndex);
}

//--------------------------------------------------
// Description  : Push HPD into HPD Queue
// Input Value  : enumTypeCPcbPort, enumHpdType : _PD_HPD_LOW / _PD_HPD_HIGH..., HPD Space Time(ms)
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmPdPushHpd(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPDHpdType enumHpdType, WORD usHpdSpaceTime)
{
    BYTE ucPortIndex = ScalerTypeCTcpmGetPortIndex(enumTypeCPcbPort);
    BYTE ucIndex = 0;

    // Push Queue Only Vlid When Alt Mode is Ready
    if(GET_TCPM_PD_DPAM_ENTER(ucPortIndex) != _TRUE)
    {
        return;
    }

    switch(enumHpdType)
    {
        case _PD_HPD_LOW:

            for(ucIndex = 0; ucIndex < _HPD_QUEUE_DEPTH; ucIndex++)
            {
                SET_TCPM_PD_HPD_QUEUE(ucPortIndex, _PD_HPD_NONE);
                SET_TCPM_PD_HPD_SPACE_TIME(ucPortIndex, 0);
                ADD_TCPM_PD_HPD_WPTR(ucPortIndex);
            }

            CLR_TCPM_PD_HPD_WPTR(ucPortIndex);
            CLR_TCPM_PD_HPD_RPTR(ucPortIndex);
            CLR_TCPM_PD_HPD_CNT(ucPortIndex);

            SET_TCPM_PD_HPD_QUEUE(ucPortIndex, _PD_HPD_LOW);
            SET_TCPM_PD_HPD_SPACE_TIME(ucPortIndex, usHpdSpaceTime);

            ADD_TCPM_PD_HPD_WPTR(ucPortIndex);
            ADD_TCPM_PD_HPD_CNT(ucPortIndex);

            break;

        case _PD_HPD_HIGH:

            if((GET_TCPM_PD_HPD_CNT(ucPortIndex) == 0) || (GET_TCPM_PD_HPD_QUEUE(ucPortIndex, (GET_TCPM_PD_HPD_WPTR(ucPortIndex) + _HPD_QUEUE_DEPTH - 1) % _HPD_QUEUE_DEPTH) != _PD_HPD_HIGH))
            {
                SET_TCPM_PD_HPD_QUEUE(ucPortIndex, _PD_HPD_HIGH);
                SET_TCPM_PD_HPD_SPACE_TIME(ucPortIndex, usHpdSpaceTime);

                ADD_TCPM_PD_HPD_WPTR(ucPortIndex);
                ADD_TCPM_PD_HPD_CNT(ucPortIndex);
            }

            break;

        case _PD_HPD_IRQ:

            // Make sure HPD_IRQ has a minumun spacing time of 10ms (DP Alt Mode 5.2.2)
            usHpdSpaceTime = (usHpdSpaceTime < _ATTENTION_SPACING_TIMER) ? _ATTENTION_SPACING_TIMER : usHpdSpaceTime;

            if(GET_TCPM_PD_HPD_CNT(ucPortIndex) <= 1)
            {
                SET_TCPM_PD_HPD_QUEUE(ucPortIndex, _PD_HPD_IRQ);
                SET_TCPM_PD_HPD_SPACE_TIME(ucPortIndex, usHpdSpaceTime);

                ADD_TCPM_PD_HPD_WPTR(ucPortIndex);
                ADD_TCPM_PD_HPD_CNT(ucPortIndex);
            }
            else
            {
                // If Last 2 HPDs are Not Both HPD_IRQs, Push New HPD_IRQ
                if((GET_TCPM_PD_HPD_QUEUE(ucPortIndex, (GET_TCPM_PD_HPD_WPTR(ucPortIndex) + _HPD_QUEUE_DEPTH - 1) % _HPD_QUEUE_DEPTH) != _PD_HPD_IRQ) ||
                   (GET_TCPM_PD_HPD_QUEUE(ucPortIndex, (GET_TCPM_PD_HPD_WPTR(ucPortIndex) + _HPD_QUEUE_DEPTH - 2) % _HPD_QUEUE_DEPTH) != _PD_HPD_IRQ))
                {
                    SET_TCPM_PD_HPD_QUEUE(ucPortIndex, _PD_HPD_IRQ);
                    SET_TCPM_PD_HPD_SPACE_TIME(ucPortIndex, usHpdSpaceTime);

                    ADD_TCPM_PD_HPD_WPTR(ucPortIndex);
                    ADD_TCPM_PD_HPD_CNT(ucPortIndex);
                }
            }

            break;

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Set TCPM PD Function Support Option
// Input Value  : ucPortIndex, enumFunctionSupport
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmPdSetFunctionSupport(BYTE ucPortIndex, EnumTypeCFunctionSupport enumFunctionSupport)
{
    switch(enumFunctionSupport)
    {
        case _TYPE_C_SUPPORT_NO_FUNCTION:
        case _TYPE_C_SUPPORT_CC_FUNCTION:

            CLR_TCPM_PD_FUNCTION_EN(ucPortIndex);
            CLR_TCPM_PD_ALT_MODE_FUNCTION(ucPortIndex);

            break;

        case _TYPE_C_SUPPORT_CC_AND_PD_FUNCTION:

            SET_TCPM_PD_FUNCTION_EN(ucPortIndex);
            CLR_TCPM_PD_ALT_MODE_FUNCTION(ucPortIndex);

            break;

        case _TYPE_C_SUPPORT_FULL_FUNCTION:

            SET_TCPM_PD_FUNCTION_EN(ucPortIndex);
            SET_TCPM_PD_ALT_MODE_FUNCTION(ucPortIndex);

            break;

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Clear Interop S8 Flag to Enable FW Solution
// Input Value  : ucPortIndex
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmPdClrInteropS8Flag(BYTE ucPortIndex)
{
    CLR_TCPM_PD_INTEROP_S8(ucPortIndex);
}

//--------------------------------------------------
// Description  : Type C TCPM Get TCPCI Byte Register (for 1-Byte Reg)
// Input Value  : ucPortIndex, enumReg
// Output Value : pucTcpciData (1-Byte)
//--------------------------------------------------
BYTE ScalerTypeCTcpmTcpciGetByte(BYTE ucPortIndex, EnumTypeCTcpmTcpciReg enumReg)
{
    BYTE pucTcpciData[1] = {0xFF};

#if(_HW_TCPM_SUPPORT == _ON)
    // 1. Set Fw Busy Flag to Prevent Interrupting by HW
    if(ScalerTypeCTcpmFwBusyCtrl(ucPortIndex, _ENABLE) == _FAIL)
    {
        DebugMessageTypeC("7. [TCPM] Polling hw_i2c_busy Failed, <READ | BYTE> Addr = >", (BYTE)enumReg);

        return pucTcpciData[0];
    }

    // 2. Read TCPC Data by TCPM HW IIC
    if(ScalerTypeCTcpmHwIICRead(ucPortIndex, GET_TCPM_TCPC_SLAVE_ADDR(ucPortIndex), 1, (BYTE)enumReg, 1, pucTcpciData) == _FAIL)
    {
        DebugMessageTypeC("7. [TCPM] Read TCPC Data Failed", 0x00);
    }

    // 3. Clear Fw Busy Flag
    ScalerTypeCTcpmFwBusyCtrl(ucPortIndex, _DISABLE);
#else

    // [TO-DO] Dennis : TypeC HW IIC Flow
    enumReg = enumReg;
    ucPortIndex = ucPortIndex;

#endif // End of #if(_HW_TCPM_SUPPORT == _ON)

    return pucTcpciData[0];
}

//--------------------------------------------------
// Description  : Type C TCPM Set TCPCI Byte Register (for 1-Byte Reg)
// Input Value  : ucPortIndex, enumReg, ucData
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmTcpciSetByte(BYTE ucPortIndex, EnumTypeCTcpmTcpciReg enumReg, BYTE ucData)
{
    BYTE pucTcpciData[1];

    pucTcpciData[0] = ucData;

#if(_HW_TCPM_SUPPORT == _ON)
    // 1. Set Fw Busy Flag to Prevent Interrupting by HW
    if(ScalerTypeCTcpmFwBusyCtrl(ucPortIndex, _ENABLE) == _FAIL)
    {
        DebugMessageTypeC("7. [TCPM] Polling hw_i2c_busy Failed, <WRITE | BYTE> Addr = >", (BYTE)enumReg);

        return;
    }

    // 2. Write TCPC Data by TCPM HW IIC
    if(ScalerTypeCTcpmHwIICWrite(ucPortIndex, GET_TCPM_TCPC_SLAVE_ADDR(ucPortIndex), 1, (BYTE)enumReg, 1, pucTcpciData) == _FAIL)
    {
        DebugMessageTypeC("7. [TCPM] Write TCPC Data Failed", 0x00);
    }

    // 3. Clear Fw Busy Flag
    ScalerTypeCTcpmFwBusyCtrl(ucPortIndex, _DISABLE);
#else

    // [TO-DO] Dennis : TypeC HW IIC Flow
    ucPortIndex = ucPortIndex;
    enumReg = enumReg;

#endif // End of #if(_HW_TCPM_SUPPORT == _ON)
}

//--------------------------------------------------
// Description  : Type C TCPM Get TCPCI Word Register (for 2-Byte Reg)
// Input Value  : ucPortIndex, enumReg
// Output Value : pucTcpciData (2-Byte)
//--------------------------------------------------
WORD ScalerTypeCTcpmTcpciGetWord(BYTE ucPortIndex, EnumTypeCTcpmTcpciReg enumReg)
{
    BYTE pucTcpciData[2] = {0xFF, 0xFF};

#if(_HW_TCPM_SUPPORT == _ON)
    // 1. Set Fw Busy Flag to Prevent Interrupting by HW
    if(ScalerTypeCTcpmFwBusyCtrl(ucPortIndex, _ENABLE) == _FAIL)
    {
        DebugMessageTypeC("7. [TCPM] Polling hw_i2c_busy Failed, <READ | WORD> Addr = >", (BYTE)enumReg);

        return TO_WORD(pucTcpciData[1], pucTcpciData[0]);
    }

    // 2. Read TCPC Data by TCPM HW IIC
    if(ScalerTypeCTcpmHwIICRead(ucPortIndex, GET_TCPM_TCPC_SLAVE_ADDR(ucPortIndex), 1, (BYTE)enumReg, 2, pucTcpciData) == _FAIL)
    {
        DebugMessageTypeC("7. [TCPM] Read TCPC Data Failed", 0x00);
    }

    // 3. Clear Fw Busy Flag
    ScalerTypeCTcpmFwBusyCtrl(ucPortIndex, _DISABLE);
#else

    // [TO-DO] Dennis : TypeC HW IIC Flow
    enumReg = enumReg;
    ucPortIndex = ucPortIndex;

#endif // End of #if(_HW_TCPM_SUPPORT == _ON)

    return TO_WORD(pucTcpciData[1], pucTcpciData[0]);
}

//--------------------------------------------------
// Description  : Type C TCPM Set TCPCI Word Register (for 2-Byte Reg)
// Input Value  : ucPortIndex, enumReg, usData
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmTcpciSetWord(BYTE ucPortIndex, EnumTypeCTcpmTcpciReg enumReg, WORD usData)
{
    BYTE pucTcpciData[2];

    pucTcpciData[0] = (BYTE)(usData);
    pucTcpciData[1] = (BYTE)(usData >> 8);

    // --------------------------------------------------------------
    // NOTE : TCPC will not Write Register if TCPM intends to Write Data to Reserved Field (Bit) in Certain Register
    // --------------------------------------------------------------

#if(_HW_TCPM_SUPPORT == _ON)
    // 1. Set Fw Busy Flag to Prevent Interrupting by HW
    if(ScalerTypeCTcpmFwBusyCtrl(ucPortIndex, _ENABLE) == _FAIL)
    {
        DebugMessageTypeC("7. [TCPM] Polling hw_i2c_busy Failed, <WRITE | WORD> Addr = >", (BYTE)enumReg);

        return;
    }

    // 2. Write TCPC Data by TCPM HW IIC
    if(ScalerTypeCTcpmHwIICWrite(ucPortIndex, GET_TCPM_TCPC_SLAVE_ADDR(ucPortIndex), 1, (BYTE)enumReg, 2, pucTcpciData) == _FAIL)
    {
        DebugMessageTypeC("7. [TCPM] Write TCPC Data Failed", 0x00);
    }

    // 3. Clear Fw Busy Flag
    ScalerTypeCTcpmFwBusyCtrl(ucPortIndex, _DISABLE);
#else

    // [TO-DO] Dennis : TypeC HW IIC Flow
    ucPortIndex = ucPortIndex;
    enumReg = enumReg;

#endif // End of #if(_HW_TCPM_SUPPORT == _ON)
}

//--------------------------------------------------
// Description  : Type C TCPM Set TCPCI Tx Buffer
// Input Value  : ucPortIndex, enumPdCmd, ucTxByteCnt, usMessageHeader
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmTcpciSetTxBuffer(BYTE ucPortIndex, EnumTypeCPDCmd enumPdCmd, BYTE ucTxByteCnt, WORD usMessageHeader)
{
#if(_HW_TCPM_SUPPORT == _ON)
#if(_HW_TCPM_TX_AUTO_CTRL == _ON)

    // 1. Set Write Byte Cnt
    ScalerSetByte(PFA_50_TCPC_0_TX_BUFFER_0 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ucTxByteCnt);

    // 2. Re-arrange Data for TCPCI Tx Buffer
    // 2-1. Set Message Header (L, H)
    ScalerSetByte(PFA_51_TCPC_0_TX_BUFFER_1 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), (BYTE)usMessageHeader);
    ScalerSetByte(PFA_52_TCPC_0_TX_BUFFER_2 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), (BYTE)(usMessageHeader >> 8));

    // 2-2. Set Data Object (Data Obj_0 [7:0], Data Obj_0 [15:8], Data Obj_0 [23:16], Data Obj_0 [31:24])
    if((enumPdCmd & (_BIT7 | _BIT6)) == _PD_CMD_TYPE_DATA)
    {
        // ucTxBuffer[3] = Data Obj_0 [7:0]
        // ucTxBuffer[4] = Data Obj_0 [15:8]
        // ucTxBuffer[5] = Data Obj_0 [23:16]
        // ucTxBuffer[6] = Data Obj_0 [31:24]
        for(pData[0] = 0; pData[0] < ((ucTxByteCnt - 2) / 4); pData[0]++)
        {
            ScalerSetByte(PFA_53_TCPC_0_TX_BUFFER_3 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex) + (pData[0] * 4), g_pucTypeCTcpmPdDataObj[3 + (pData[0] * 4)]);
            ScalerSetByte(PFA_54_TCPC_0_TX_BUFFER_4 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex) + (pData[0] * 4), g_pucTypeCTcpmPdDataObj[2 + (pData[0] * 4)]);
            ScalerSetByte(PFA_55_TCPC_0_TX_BUFFER_5 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex) + (pData[0] * 4), g_pucTypeCTcpmPdDataObj[1 + (pData[0] * 4)]);
            ScalerSetByte(PFA_56_TCPC_0_TX_BUFFER_6 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex) + (pData[0] * 4), g_pucTypeCTcpmPdDataObj[0 + (pData[0] * 4)]);
        }
    }
    else if((enumPdCmd & (_BIT7 | _BIT6)) == _PD_CMD_TYPE_EXT)
    {
        // ucTxBuffer[3] = Ext Message Header [7:0]
        // ucTxBuffer[4] = Ext Message Header [15:8]
        ScalerSetByte(PFA_53_TCPC_0_TX_BUFFER_3 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), g_pucTypeCTcpmPdDataObj[1]);
        ScalerSetByte(PFA_54_TCPC_0_TX_BUFFER_4 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), g_pucTypeCTcpmPdDataObj[0]);

        // ucTxBuffer[5] = Data Block_0
        // ucTxBuffer[6] = Data Block_1
        for(pData[0] = 0; pData[0] < (ucTxByteCnt - 4); pData[0]++)
        {
            ScalerSetByte(PFA_55_TCPC_0_TX_BUFFER_5 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex) + pData[0], g_pucTypeCTcpmPdDataObj[2 + pData[0]]);
        }
    }

    // 3. Set Tx Length [0xFA42] [4:0] tcpc_0_tx_len
    ScalerSetBit(PFA_42_TCPC_0_TRANSMIT_AUTO_CTRL + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT6 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ucTxByteCnt);

#else

    BYTE pucTxBuffer[_MAX_DATA_OBJ_CNT * 4];

    // 1. Set Write Byte Cnt
    pucTxBuffer[0] = ucTxByteCnt;

    // 2. Re-arrange Data for TCPCI Tx Buffer
    // 2-1. Set Message Header (L, H)
    pucTxBuffer[1] = (BYTE)usMessageHeader;
    pucTxBuffer[2] = (BYTE)(usMessageHeader >> 8);

    // 2-2. Set Data Object (Data Obj_0 [7:0], Data Obj_0 [15:8], Data Obj_0 [23:16], Data Obj_0 [31:24])
    if((enumPdCmd & (_BIT7 | _BIT6)) == _PD_CMD_TYPE_DATA)
    {
        // ucTxBuffer[3] = Data Obj_0 [7:0]
        // ucTxBuffer[4] = Data Obj_0 [15:8]
        // ucTxBuffer[5] = Data Obj_0 [23:16]
        // ucTxBuffer[6] = Data Obj_0 [31:24]
        for(pData[0] = 0; pData[0] < ((ucTxByteCnt - 2) / 4); pData[0]++)
        {
            pucTxBuffer[3 + (pData[0] * 4)] = g_pucTypeCTcpmPdDataObj[3 + (pData[0] * 4)];
            pucTxBuffer[4 + (pData[0] * 4)] = g_pucTypeCTcpmPdDataObj[2 + (pData[0] * 4)];
            pucTxBuffer[5 + (pData[0] * 4)] = g_pucTypeCTcpmPdDataObj[1 + (pData[0] * 4)];
            pucTxBuffer[6 + (pData[0] * 4)] = g_pucTypeCTcpmPdDataObj[0 + (pData[0] * 4)];
        }
    }
    else if((enumPdCmd & (_BIT7 | _BIT6)) == _PD_CMD_TYPE_EXT)
    {
        // ucTxBuffer[3] = Ext Message Header [7:0]
        // ucTxBuffer[4] = Ext Message Header [15:8]
        pucTxBuffer[3] = g_pucTypeCTcpmPdDataObj[1];
        pucTxBuffer[4] = g_pucTypeCTcpmPdDataObj[0];

        // ucTxBuffer[5] = Data Block_0
        // ucTxBuffer[6] = Data Block_1
        for(pData[0] = 0; pData[0] < (ucTxByteCnt - 4); pData[0]++)
        {
            pucTxBuffer[5 + pData[0]] = g_pucTypeCTcpmPdDataObj[2 + pData[0]];
        }
    }

    // 3. Set Fw Busy Flag to Prevent Interrupting by HW
    if(ScalerTypeCTcpmFwBusyCtrl(ucPortIndex, _ENABLE) == _FAIL)
    {
        return;
    }

    // 4. Write TCPC Data by TCPM HW IIC
    ScalerTypeCTcpmHwIICWrite(ucPortIndex, GET_TCPM_TCPC_SLAVE_ADDR(ucPortIndex), 1, (BYTE)_TCPM_TCPCI_REG_TX_BUF, ucTxByteCnt + 1, (BYTE *)(&pucTxBuffer[0]));

    // 5. Clear Fw Busy Flag
    ScalerTypeCTcpmFwBusyCtrl(ucPortIndex, _DISABLE);

#endif // End of #if(_HW_TCPM_TX_AUTO_CTRL == _ON)

#else

    // [TO-DO] Dennis : TypeC HW IIC Flow
    ucPortIndex = ucPortIndex;
    enumPdCmd = enumPdCmd;
    ucTxByteCnt = ucTxByteCnt;
    usMessageHeader = usMessageHeader;

#endif // End of #if(_HW_TCPM_SUPPORT == _ON)
}

//--------------------------------------------------
// Description  : Type C TCPM Set TCPCI Transmit
// Input Value  : ucPortIndex, ucTransmitInfo
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmTcpciSetTransmit(BYTE ucPortIndex, BYTE ucTransmitInfo)
{
#if(_HW_TCPM_SUPPORT == _ON)
#if(_HW_TCPM_TX_AUTO_CTRL == _ON)

    // 1. Set Transmit
    ScalerSetByte(PFA_6F_TCPC_0_TRANSMIT + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ucTransmitInfo);

    // 2. Start Transmit Tx Buffer + Transmit (Do Not Need to Enable tcpc_0_auto_tx_irq_en)
    // [0xFA42] [7] tcpc_0_auto_tx_en, [6] tcpc_0_auto_tx_irq, [5] tcpc_0_auto_tx_irq_en
    ScalerSetBit(PFA_42_TCPC_0_TRANSMIT_AUTO_CTRL + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6));

#else

    // 1. Set Transmit
    ScalerTypeCTcpmTcpciSetByte(ucPortIndex, _TCPM_TCPCI_REG_TRANSMIT, ucTransmitInfo);

#endif // End of #if(_HW_TCPM_TX_AUTO_CTRL == _ON)

#else

    // [TO-DO] Dennis : TypeC HW IIC Flow
    ucPortIndex = ucPortIndex;
    ucTransmitInfo = ucTransmitInfo;

#endif // End of #if(_HW_TCPM_SUPPORT == _ON)
}

#if(_HW_TCPM_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Read data from the selected device by TCPM IIC
// Input Value  : ucPortIndex, ucSlaveAddr, ucSubAddrLength, usSubAddr, ucDataLength, pucReadArray
// Output Value : Reading result (Fail/Success)
//--------------------------------------------------
bit ScalerTypeCTcpmHwIICRead(BYTE ucPortIndex, BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, BYTE ucDataLength, BYTE *pucReadArray)
{
    BYTE ucI = 0;

    // Return fail if Data to be received is greater than IIC buffer size
    if(ucDataLength > _HW_TCPM_IIC_BUFFER_SIZE)
    {
        return _FAIL;
    }

    // Reset(Block) IIC module
    ScalerSetBit(PFA_00_I2CM_CR0 + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), ~_BIT7, 0x00);

    // Enable IIC module
    ScalerSetBit(PFA_00_I2CM_CR0 + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), ~_BIT7, _BIT7);

    // Wait I2C Fifo Clk Switch to Mcu Clk
    if(ScalerTimerPollingFlagProc(2, (PFA_08_I2CM_SR + GET_TCPM_IIC_HW_SHIFT(ucPortIndex)), _BIT5, _TRUE) == _FALSE)
    {
        // Reset(Block) IIC module
        ScalerSetBit(PFA_00_I2CM_CR0 + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), ~_BIT7, 0x00);

        // Enable IIC module
        ScalerSetBit(PFA_00_I2CM_CR0 + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), ~_BIT7, _BIT7);

        return _FAIL;
    }

    // Load Slave Address to IIC Buffer
    switch(ucSubAddrLength)
    {
        case 0:

            // Set 1 byte for FRSIB
            ScalerSetBit(PFA_02_I2CM_CR2 + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), ~(_BIT1 | _BIT0), 0x00);

            // Set no repeat start
            ScalerSetBit(PFA_03_I2CM_CR3 + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), ~(_BIT4 | _BIT3), 0x00);

            // Load Slave Address to receive data
            ScalerSetByte(PFA_09_I2CM_TD + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), (ucSlaveAddr | _READ));

            break;

        case 1:

            // Set 2 bytes for FRSIB
            ScalerSetBit(PFA_02_I2CM_CR2 + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), ~(_BIT1 | _BIT0), _BIT0);

            // Set one repeat start
            ScalerSetBit(PFA_03_I2CM_CR3 + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), ~(_BIT4 | _BIT3), _BIT3);

            // Load Slave Address to IIC Buffer
            ScalerSetByte(PFA_09_I2CM_TD + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), (ucSlaveAddr | _WRITE));

            // Load Sub-Address to IIC Buffer
            ScalerSetByte(PFA_09_I2CM_TD + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), (BYTE)(usSubAddr));

            // Load Slave Address to receive data
            ScalerSetByte(PFA_09_I2CM_TD + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), (ucSlaveAddr | _READ));

            break;

        case 2:

            // Set 3 bytes for FRSIB
            ScalerSetBit(PFA_02_I2CM_CR2 + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), ~(_BIT1 | _BIT0), _BIT1);

            // Set one repeat start
            ScalerSetBit(PFA_03_I2CM_CR3 + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), ~(_BIT4 | _BIT3), _BIT3);

            // Load Slave Address to IIC Buffer
            ScalerSetByte(PFA_09_I2CM_TD + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), (ucSlaveAddr | _WRITE));

            // Load First Sub-Address to IIC Buffer
            ScalerSetByte(PFA_09_I2CM_TD + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), (BYTE)((usSubAddr & 0xFF00) >> 8));

            // Load Second Sub-Address to IIC Buffer
            ScalerSetByte(PFA_09_I2CM_TD + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), (BYTE)(usSubAddr));

            // Load Slave Address to receive data
            ScalerSetByte(PFA_09_I2CM_TD + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), (ucSlaveAddr | _READ));

            break;

        default:

            break;
    }

    // Set data length
    ScalerSetBit(PFA_00_I2CM_CR0 + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), ((ucDataLength - 1) << 1));

    // IIC command Start
    ScalerSetBit(PFA_00_I2CM_CR0 + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), ~_BIT6, _BIT6);

    // Wait until Master Receive Complete
    if(ScalerTimerPollingFlagProc(4, (PFA_08_I2CM_SR + GET_TCPM_IIC_HW_SHIFT(ucPortIndex)), _BIT1, _TRUE) == _FALSE)
    {
        // Reset(Block) IIC module
        ScalerSetBit(PFA_00_I2CM_CR0 + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), ~_BIT7, 0x00);

        // Enable IIC module
        ScalerSetBit(PFA_00_I2CM_CR0 + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), ~_BIT7, _BIT7);

        return _FAIL;
    }

    // Wait I2C Fifo Clk Switch to Mcu Clk
    if(ScalerTimerPollingFlagProc(2, (PFA_08_I2CM_SR + GET_TCPM_IIC_HW_SHIFT(ucPortIndex)), _BIT5, _TRUE) == _FALSE)
    {
        // Reset(Block) IIC module
        ScalerSetBit(PFA_00_I2CM_CR0 + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), ~_BIT7, 0x00);

        // Enable IIC module
        ScalerSetBit(PFA_00_I2CM_CR0 + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), ~_BIT7, _BIT7);

        return _FAIL;
    }

    // Save received data
    for(ucI = 0; ucI < ucDataLength; ucI++)
    {
        *pucReadArray = ScalerGetByte(PFA_09_I2CM_TD + GET_TCPM_IIC_HW_SHIFT(ucPortIndex));
        pucReadArray++;
    }

    // Clear all flags
    ScalerSetByte(PFA_08_I2CM_SR + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), (_BIT2 | _BIT1 | _BIT0));

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : Write data to the selected device by TypeC IIC
// Input Value  : ucPortIndex, ucSlaveAddr, ucSubAddrLength, usSubAddr, ucDataLength, pucWriteArray
// Output Value : Write result (Fail/Success)
//--------------------------------------------------
bit ScalerTypeCTcpmHwIICWrite(BYTE ucPortIndex, BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, BYTE ucDataLength, BYTE *pucWriteArray)
{
    BYTE ucI = 0;
    BYTE ucTempLength = 0;

    // Return fail if Data to be transmitted is greater than IIC buffer size
    // Max Data Length = Buffer Size - Slave Addr Length (1 Byte) - Sub Addr Length (ucSubAddrLength)
    if(ucDataLength > (_HW_TCPM_IIC_BUFFER_SIZE - 1 - ucSubAddrLength))
    {
        return _FAIL;
    }

    // Reset(Block) IIC module
    ScalerSetBit(PFA_00_I2CM_CR0 + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), ~_BIT7, 0x00);

    // Enable IIC module
    ScalerSetBit(PFA_00_I2CM_CR0 + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), ~_BIT7, _BIT7);

    // Set 1 byte for FRSIB
    ScalerSetBit(PFA_02_I2CM_CR2 + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), ~(_BIT1 | _BIT0), 0x00);

    // Set no repeat start
    ScalerSetBit(PFA_03_I2CM_CR3 + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), ~(_BIT4 | _BIT3), 0x00);

    // Wait I2C Fifo Clk Switch to Mcu Clk
    if(ScalerTimerPollingFlagProc(2, (PFA_08_I2CM_SR + GET_TCPM_IIC_HW_SHIFT(ucPortIndex)), _BIT5, _TRUE) == _FALSE)
    {
        // Reset(Block) IIC module
        ScalerSetBit(PFA_00_I2CM_CR0 + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), ~_BIT7, 0x00);

        // Enable IIC module
        ScalerSetBit(PFA_00_I2CM_CR0 + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), ~_BIT7, _BIT7);

        return _FAIL;
    }

    // Load Slave Address to IIC Buffer
    ScalerSetByte(PFA_09_I2CM_TD + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), (ucSlaveAddr | _WRITE));

    ScalerSetBit(PFA_00_I2CM_CR0 + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), 0x00);

    switch(ucSubAddrLength)
    {
        case 0:

            // Set data length
            ucTempLength = ((ucDataLength - 1) << 1);

            break;

        case 1:

            // Load Sub-Address to IIC Buffer
            ScalerSetByte(PFA_09_I2CM_TD + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), (BYTE)(usSubAddr));

            // Set data length
            ucTempLength = (ucDataLength << 1);

            break;

        case 2:

            // Load First Sub-Address to IIC Buffer
            ScalerSetByte(PFA_09_I2CM_TD + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), (BYTE)((usSubAddr & 0xFF00) >> 8));

            // Load Second Sub-Address to IIC Buffer
            ScalerSetByte(PFA_09_I2CM_TD + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), (BYTE)(usSubAddr));

            // Set data length
            ucTempLength = ((ucDataLength + 1) << 1);

            break;

        default:

            break;
    }

    // Load data to IIC buffer for transmission
    for(ucI = 0; ucI < ucDataLength; ucI++)
    {
        ScalerSetByte(PFA_09_I2CM_TD + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), pucWriteArray[ucI]);
    }

    // Send IIC command Start
    ScalerSetByte(PFA_00_I2CM_CR0 + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), (0xC0 + ucTempLength));

    // Wait until Master Transmit Complete
    if(ScalerTimerPollingFlagProc(4, (PFA_08_I2CM_SR + GET_TCPM_IIC_HW_SHIFT(ucPortIndex)), _BIT0, _TRUE) == _FALSE)
    {
        // Reset(Block) IIC module
        ScalerSetBit(PFA_00_I2CM_CR0 + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), ~_BIT7, 0x00);

        // Enable IIC module
        ScalerSetBit(PFA_00_I2CM_CR0 + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), ~_BIT7, _BIT7);

        return _FAIL;
    }

    // Clear all flags
    ScalerSetByte(PFA_08_I2CM_SR + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), (_BIT2 | _BIT1 | _BIT0));

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : TCPM Alert Auto Ctrl Setting
// Input Value  : ucPortIndex
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmAlertAutoCtrlSetting(BYTE ucPortIndex)
{
#if(_HW_TCPM_ALERT_AUTO_CTRL == _ON)
    // Enable Alert Auto Ctrl : [0xFA23] [7] auto_alert_en, [6] alert_valid_auto_en
    ScalerSetBit(PFA_23_TCPC_0_ALERT_AUTO_CTRL + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT7 | _BIT6 | _BIT5 | _BIT2 | _BIT1), (_BIT7 | _BIT6));
#endif

#if(_HW_TCPM_CS_AUTO_CTRL == _ON)
    // Enable CC Status Auto Ctrl : [0xFA32] [7] auto_cs_en
    ScalerSetBit(PFA_32_TCPC_0_CS_AUTO_CTRL + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT7 | _BIT1), _BIT7);
#endif

#if(_HW_TCPM_PS_AUTO_CTRL == _ON)
    // Enable Power Status Auto Ctrl : [0xFA34] [7] auto_ps_en
    ScalerSetBit(PFA_34_TCPC_0_PS_AUTO_CTRL + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT7 | _BIT1), _BIT7);
#endif

#if(_HW_TCPM_FS_AUTO_CTRL == _ON)
    // Enable Fault Status Auto Ctrl : [0xFA36] [7] auto_fault_en
    ScalerSetBit(PFA_36_TCPC_0_FS_AUTO_CTRL + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT7 | _BIT1), _BIT7);
#endif

#if(_HW_TCPM_EXT_AUTO_CTRL == _ON)
    // Enable Extended Status Auto Ctrl : [0xFA38] [7] auto_ext_en
    ScalerSetBit(PFA_38_TCPC_0_ES_AUTO_CTRL + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT7 | _BIT1), _BIT7);
#endif

#if(_HW_TCPM_ALERT_EXT_AUTO_CTRL == _ON)
    // Enable Alert Extended Auto Ctrl : [0xFA3A] [7] auto_alert_ext_en
    ScalerSetBit(PFA_3A_TCPC_0_ALERT_EXT_AUTO_CTRL + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT7 | _BIT1), _BIT7);
#endif

#if(_HW_TCPM_VENDOR_DEF_AUTO_CTRL == _ON)
    // Enable Vendor Define Auto Ctrl : [0xFA3C] [7] auto_vendor_def_en
    ScalerSetBit(PFA_3C_TCPC_0_VENDOR_DEF_AUTO_CTRL + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT7 | _BIT1), _BIT7);
#endif

#if(_HW_TCPM_VALM_H_AUTO_CTRL == _ON)
    // Enable High-Voltage Alarm Auto Ctrl : [0xFA3F] [4] auto_valm_h_en
    ScalerSetBit(PFA_3F_TCPC_0_VALM_HL_AUTO_CTRL + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT4 | _BIT3 | _BIT1), _BIT4);
#endif

#if(_HW_TCPM_VALM_L_AUTO_CTRL == _ON)
    // Enable Low-Voltage Alarm Auto Ctrl : [0xFA3F] [5] auto_valm_l_en
    ScalerSetBit(PFA_3F_TCPC_0_VALM_HL_AUTO_CTRL + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT5 | _BIT3 | _BIT1), _BIT5);
#endif

#if(_HW_TCPM_RX_MSG_AUTO_CTRL == _ON)
    // Enable Rx Msg Auto Ctrl : [0xFA48] [7] auto_rx_msg_en, [5] rx_auto_rd_opt
    ScalerSetBit(PFA_48_TCPC_0_RX_MSG_AUTO_CTRL_1 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT7 | _BIT5 | _BIT3 | _BIT1), (_BIT7 | _BIT5));

    // Set [0xFA4A] rx_start_addr = 0x30
    ScalerSetByte(PFA_4A_TCPC_0_RX_START_ADDR + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), 0x30);
#endif

#if(_HW_TCPM_RX_BGN_AUTO_CTRL == _ON)
    // Enable Rx Bgn Auto Ctrl : [0xFA48] [6] auto_rx_bgn_en, [5] rx_auto_rd_opt
    ScalerSetBit(PFA_48_TCPC_0_RX_MSG_AUTO_CTRL_1 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT6 | _BIT5 | _BIT3 | _BIT1), (_BIT6 | _BIT5));

    // Set [0xFA4A] rx_start_addr = 0x30
    ScalerSetByte(PFA_4A_TCPC_0_RX_START_ADDR + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), 0x30);
#endif

    // Enable Alert Detection
    ScalerTypeCTcpmAlertDetCtrl(ucPortIndex, _ENABLE);
}

//--------------------------------------------------
// Description  : Enable/Disable TCPM Alert Detect
// Input Value  : ucPortIndex, bAction
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmAlertDetCtrl(BYTE ucPortIndex, bit bAction)
{
    if(bAction == _ENABLE)
    {
        // 1. If alert_det_en = 0, Polling alert_status = 1 before Enable alert_det_en
        if(ScalerGetBit(PFA_20_TCPC_0_ALERT_DETECT + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), _BIT7) == 0x00)
        {
            // Polling [0xFA20] [4] alert_status = 1 (Alert High)
            if(ScalerTimerPollingFlagProc(1, (PFA_20_TCPC_0_ALERT_DETECT + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex)), _BIT0, _TRUE) == _FALSE)
            {
                return;
            }
        }

        // Set [0xFA20] [7] alert_det_en = 1 & [3:1] alert_det_deb = b000
        ScalerSetBit(PFA_20_TCPC_0_ALERT_DETECT + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT7 | _BIT3 | _BIT2 | _BIT1), _BIT7);
    }
    else
    {
        // 1. Set FW Busy Flag
        if(ScalerTypeCTcpmFwBusyCtrl(ucPortIndex, _ENABLE) == _FAIL)
        {
            return;
        }

        // 2. Disable [0xFA20] [7] alert_det_en
        ScalerSetBit(PFA_20_TCPC_0_ALERT_DETECT + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~_BIT7, 0x00);

        // 3. Clear FW Busy Flag
        ScalerTypeCTcpmFwBusyCtrl(ucPortIndex, _DISABLE);
    }
}

//--------------------------------------------------
// Description  : Type C TCPM FW Busy Flag Control
// Input Value  : ucPortIndex, bAction
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
bit ScalerTypeCTcpmFwBusyCtrl(BYTE ucPortIndex, bit bAction)
{
    if(bAction == _ENABLE)
    {
        BYTE ucPollingCnt = 0;

        // If WD Event Triggered, Delay up to 2ms to Avoid WD Event Unable to Use IIC
        while((ucPollingCnt < 2) && (GET_TCPM_WD_EVENT_TRIGGERED(ucPortIndex) == _TRUE))
        {
            ucPollingCnt += 1;
            ScalerTimerDelayXms(1);
        }

        // Polling [0xFA11] [4] hw_i2c_busy = 0
        if(ScalerTimerPollingFlagProc(2, (PFA_11_TCPM_BUSY + GET_TCPM_IIC_HW_SHIFT(ucPortIndex)), _BIT4, _FALSE) == _FALSE)
        {
            return _FAIL;
        }

        // Set [0xFA11] [5] fw_i2c_busy to Prevent Interruptions from Exint & WDINT
        ScalerSetBit(PFA_11_TCPM_BUSY + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), ~_BIT5, _BIT5);

        return _SUCCESS;
    }
    else
    {
        // Clear [0xFA11] [5] fw_i2c_busy
        ScalerSetBit(PFA_11_TCPM_BUSY + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), ~_BIT5, 0x00);

        return _SUCCESS;
    }
}

//--------------------------------------------------
// Description  : Type C TCPM Clear Alert INT
// Input Value  : ucPortIndex, usAlertType, b1Action
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmAlertIntControl(BYTE ucPortIndex, WORD usAlertType, bit b1Action)
{
    if((usAlertType & _TCPM_TCPCI_ALERT_CC_STATUS) == _TCPM_TCPCI_ALERT_CC_STATUS)
    {
        if(b1Action == _ENABLE)
        {
            // Enable CC Status IRQ : [0xFA32] [1] alert_cs_irq, [0] alert_cs_irq_en
            ScalerSetBit(PFA_32_TCPC_0_CS_AUTO_CTRL + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
        }
        else
        {
            // Disable CC Status IRQ : [0xFA32] [1] alert_cs_irq, [0] alert_cs_irq_en
            ScalerSetBit(PFA_32_TCPC_0_CS_AUTO_CTRL + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT1 | _BIT0), _BIT1);
        }
    }

    if((usAlertType & _TCPM_TCPCI_ALERT_PWR_STATUS) == _TCPM_TCPCI_ALERT_PWR_STATUS)
    {
        if(b1Action == _ENABLE)
        {
            // Enable Power Status IRQ : [0xFA34] [1] alert_ps_irq, [0] alert_ps_irq_en
            ScalerSetBit(PFA_34_TCPC_0_PS_AUTO_CTRL + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
        }
        else
        {
            // Disable Power Status IRQ : [0xFA34] [1] alert_ps_irq, [0] alert_ps_irq_en
            ScalerSetBit(PFA_34_TCPC_0_PS_AUTO_CTRL + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT1 | _BIT0), _BIT1);
        }
    }

    if((usAlertType & _TCPM_TCPCI_ALERT_FAULT) == _TCPM_TCPCI_ALERT_FAULT)
    {
        if(b1Action == _ENABLE)
        {
            // Enable Fault Status IRQ : [0xFA36] [1] alert_fault_irq, [0] alert_fault_irq_en
            ScalerSetBit(PFA_36_TCPC_0_FS_AUTO_CTRL + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
        }
        else
        {
            // Disable Fault Status IRQ : [0xFA36] [1] alert_fault_irq, [0] alert_fault_irq_en
            ScalerSetBit(PFA_36_TCPC_0_FS_AUTO_CTRL + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT1 | _BIT0), _BIT1);
        }
    }

    if((usAlertType & _TCPM_TCPCI_ALERT_EXT_STATUS) == _TCPM_TCPCI_ALERT_EXT_STATUS)
    {
        if(b1Action == _ENABLE)
        {
            // Enable Extended Status IRQ : [0xFA38] [1] alert_ext_stat_irq, [0] alert_ext_stat_irq_en
            ScalerSetBit(PFA_38_TCPC_0_ES_AUTO_CTRL + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
        }
        else
        {
            // Disable Extended Status IRQ : [0xFA38] [1] alert_ext_stat_irq, [0] alert_ext_stat_irq_en
            ScalerSetBit(PFA_38_TCPC_0_ES_AUTO_CTRL + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT1 | _BIT0), _BIT1);
        }
    }

    if((usAlertType & _TCPM_TCPCI_ALERT_ALERT_EXT) == _TCPM_TCPCI_ALERT_ALERT_EXT)
    {
        if(b1Action == _ENABLE)
        {
            // Enable Alert Extended IRQ : [0xFA3A] [1] alert_alert_ext_irq, [0] alert_alert_ext_irq_en
            ScalerSetBit(PFA_3A_TCPC_0_ALERT_EXT_AUTO_CTRL + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
        }
        else
        {
            // Disable Alert Extended IRQ : [0xFA3A] [1] alert_alert_ext_irq, [0] alert_alert_ext_irq_en
            ScalerSetBit(PFA_3A_TCPC_0_ALERT_EXT_AUTO_CTRL + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT1 | _BIT0), _BIT1);
        }
    }

    if((usAlertType & _TCPM_TCPCI_ALERT_VENDOR_DEF) == _TCPM_TCPCI_ALERT_VENDOR_DEF)
    {
        if(b1Action == _ENABLE)
        {
            // Enable Vendor Define IRQ : [0xFA3C] [1] alert_vendor_def_irq, [0] alert_vendor_def_irq_en
            ScalerSetBit(PFA_3C_TCPC_0_VENDOR_DEF_AUTO_CTRL + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
        }
        else
        {
            // Disable Vendor Define IRQ : [0xFA3C] [1] alert_vendor_def_irq, [0] alert_vendor_def_irq_en
            ScalerSetBit(PFA_3C_TCPC_0_VENDOR_DEF_AUTO_CTRL + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT1 | _BIT0), _BIT1);
        }
    }

    if((usAlertType & _TCPM_TCPCI_ALERT_VBUS_ALRM_H) == _TCPM_TCPCI_ALERT_VBUS_ALRM_H)
    {
        if(b1Action == _ENABLE)
        {
            // Enable High-Voltage Alarm IRQ : [0xFA3F] [1] alert_valm_h_irq, [0] alert_valm_h_irq_en
            ScalerSetBit(PFA_3F_TCPC_0_VALM_HL_AUTO_CTRL + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT3 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
        }
        else
        {
            // Disable High-Voltage Alarm IRQ : [0xFA3F] [1] alert_valm_h_irq, [0] alert_valm_h_irq_en
            ScalerSetBit(PFA_3F_TCPC_0_VALM_HL_AUTO_CTRL + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT3 | _BIT1 | _BIT0), _BIT1);
        }
    }

    if((usAlertType & _TCPM_TCPCI_ALERT_VBUS_ALRM_L) == _TCPM_TCPCI_ALERT_VBUS_ALRM_L)
    {
        if(b1Action == _ENABLE)
        {
            // Enable Low-Voltage Alarm IRQ : [0xFA3F] [3] alert_valm_l_irq, [2] alert_valm_l_irq_en
            ScalerSetBit(PFA_3F_TCPC_0_VALM_HL_AUTO_CTRL + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT3 | _BIT2 | _BIT1), (_BIT3 | _BIT2));
        }
        else
        {
            // Disable Low-Voltage Alarm IRQ : [0xFA3F] [3] alert_valm_l_irq, [2] alert_valm_l_irq_en
            ScalerSetBit(PFA_3F_TCPC_0_VALM_HL_AUTO_CTRL + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT3 | _BIT2 | _BIT1), _BIT3);
        }
    }

    if((usAlertType & _TCPM_TCPCI_ALERT_RX_RCV_SOP) == _TCPM_TCPCI_ALERT_RX_RCV_SOP)
    {
        if(b1Action == _ENABLE)
        {
            // Enable Rx Msg IRQ : [0xFA48] [3] alert_rx_msg_irq, [2] alert_rx_msg_irq_en
            ScalerSetBit(PFA_48_TCPC_0_RX_MSG_AUTO_CTRL_1 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT3 | _BIT2 | _BIT1), (_BIT3 | _BIT2));
        }
        else
        {
            // Disable Rx Msg IRQ : [0xFA48] [3] alert_rx_msg_irq, [2] alert_rx_msg_irq_en
            ScalerSetBit(PFA_48_TCPC_0_RX_MSG_AUTO_CTRL_1 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT3 | _BIT2 | _BIT1), _BIT3);
        }
    }

    if((usAlertType & _TCPM_TCPCI_ALERT_RX_SOP_BEGIN) == _TCPM_TCPCI_ALERT_RX_SOP_BEGIN)
    {
        if(b1Action == _ENABLE)
        {
            // Enable Rx Bgn IRQ : [0xFA48] [1] alert_rx_bgn_irq, [0] alert_rx_bgn_irq_en
            ScalerSetBit(PFA_48_TCPC_0_RX_MSG_AUTO_CTRL_1 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT3 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
        }
        else
        {
            // Disable Rx Bgn IRQ : [0xFA48] [1] alert_rx_bgn_irq, [0] alert_rx_bgn_irq_en
            ScalerSetBit(PFA_48_TCPC_0_RX_MSG_AUTO_CTRL_1 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT3 | _BIT1 | _BIT0), _BIT1);
        }
    }

    if((usAlertType & _TCPM_TCPCI_ALERT_RX_HRST) == _TCPM_TCPCI_ALERT_RX_HRST)
    {
        if(b1Action == _ENABLE)
        {
            // Enable Hard Reset IRQ : [0xFA43] [7] alert_hrst_irq, [6] alert_hrst_irq_en
            ScalerSetBit(PFA_43_TCPC_0_ALERT_RELATED_IRQ_1 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT7 | _BIT6 | _BIT5 | _BIT3 | _BIT1), (_BIT7 | _BIT6));
        }
        else
        {
            // Disable Hard Reset IRQ : [0xFA43] [7] alert_hrst_irq, [6] alert_hrst_irq_en
            ScalerSetBit(PFA_43_TCPC_0_ALERT_RELATED_IRQ_1 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT7 | _BIT6 | _BIT5 | _BIT3 | _BIT1), _BIT7);
        }
    }

    if((usAlertType & _TCPM_TCPCI_ALERT_TX_FAIL) == _TCPM_TCPCI_ALERT_TX_FAIL)
    {
        if(b1Action == _ENABLE)
        {
            // Enable Tx Fail IRQ : [0xFA43] [5] alert_tx_fail_irq, [4] alert_tx_fail_irq_en
            ScalerSetBit(PFA_43_TCPC_0_ALERT_RELATED_IRQ_1 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT7 | _BIT5 | _BIT4 | _BIT3 | _BIT1), (_BIT5 | _BIT4));
        }
        else
        {
            // Disable Tx Fail IRQ : [0xFA43] [5] alert_tx_fail_irq, [4] alert_tx_fail_irq_en
            ScalerSetBit(PFA_43_TCPC_0_ALERT_RELATED_IRQ_1 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT7 | _BIT5 | _BIT4 | _BIT3 | _BIT1), _BIT5);
        }
    }

    if((usAlertType & _TCPM_TCPCI_ALERT_TX_DISCARD) == _TCPM_TCPCI_ALERT_TX_DISCARD)
    {
        if(b1Action == _ENABLE)
        {
            // Enable Tx Discard IRQ : [0xFA43] [3] alert_tx_discard_irq, [2] alert_tx_discard_irq_en
            ScalerSetBit(PFA_43_TCPC_0_ALERT_RELATED_IRQ_1 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT7 | _BIT5 | _BIT3 | _BIT2 | _BIT1), (_BIT3 | _BIT2));
        }
        else
        {
            // Disable Tx Discard IRQ : [0xFA43] [3] alert_tx_discard_irq, [2] alert_tx_discard_irq_en
            ScalerSetBit(PFA_43_TCPC_0_ALERT_RELATED_IRQ_1 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT7 | _BIT5 | _BIT3 | _BIT2 | _BIT1), _BIT3);
        }
    }

    if((usAlertType & _TCPM_TCPCI_ALERT_TX_SUCCESS) == _TCPM_TCPCI_ALERT_TX_SUCCESS)
    {
        if(b1Action == _ENABLE)
        {
            // Enable Tx Success IRQ : [0xFA43] [1] alert_tx_discard_irq, [0] alert_tx_discard_irq_en
            ScalerSetBit(PFA_43_TCPC_0_ALERT_RELATED_IRQ_1 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT7 | _BIT5 | _BIT3 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
        }
        else
        {
            // Disable Tx Success IRQ : [0xFA43] [1] alert_tx_discard_irq, [0] alert_tx_discard_irq_en
            ScalerSetBit(PFA_43_TCPC_0_ALERT_RELATED_IRQ_1 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT7 | _BIT5 | _BIT3 | _BIT1 | _BIT0), _BIT1);
        }
    }

    if((usAlertType & _TCPM_TCPCI_ALERT_RX_OVERFLOW) == _TCPM_TCPCI_ALERT_RX_OVERFLOW)
    {
        if(b1Action == _ENABLE)
        {
            // Enable Rx Overflow IRQ : [0xFA44] [3] alert_tx_discard_irq, [2] alert_tx_discard_irq_en
            ScalerSetBit(PFA_44_TCPC_0_ALERT_RELATED_IRQ_2 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT3 | _BIT2 | _BIT1), (_BIT3 | _BIT2));
        }
        else
        {
            // Disable Rx Overflow IRQ : [0xFA44] [3] alert_tx_discard_irq, [2] alert_tx_discard_irq_en
            ScalerSetBit(PFA_44_TCPC_0_ALERT_RELATED_IRQ_2 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT3 | _BIT2 | _BIT1), _BIT3);
        }
    }

    if((usAlertType & _TCPM_TCPCI_ALERT_SNK_DISC) == _TCPM_TCPCI_ALERT_SNK_DISC)
    {
        if(b1Action == _ENABLE)
        {
            // Enable Sink Disconnect IRQ : [0xFA44] [1] alert_snk_disc_irq, [0] alert_snk_disc_irq_en
            ScalerSetBit(PFA_44_TCPC_0_ALERT_RELATED_IRQ_2 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT3 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
        }
        else
        {
            // Disable Sink Disconnect IRQ : [0xFA44] [1] alert_snk_disc_irq, [0] alert_snk_disc_irq_en
            ScalerSetBit(PFA_44_TCPC_0_ALERT_RELATED_IRQ_2 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT3 | _BIT1 | _BIT0), _BIT1);
        }
    }
}
#endif // End of #if(_HW_TCPM_SUPPORT == _ON)

#if(_TYPE_C_PMIC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Read data from the selected device by IIC
// Input Value  : enumTypeCPcbPort, ucSlaveAddr, usSubAddr, ucSubAddrLength, usLength, pucReadArray
// Output Value : Read result (Fail/Success)
//--------------------------------------------------
bit ScalerTypeCTcpmPmicIICRead(EnumTypeCPcbPort enumTypeCPcbPort, BYTE ucSlaveAddr, WORD usSubAddr, BYTE ucSubAddrLength, WORD usLength, BYTE *pucReadArray)
{
    BYTE ucPortIndex = ScalerTypeCTcpmGetPortIndex(enumTypeCPcbPort);
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

#if(_HW_TCPM_SUPPORT == _ON)
        ucDataCnt = _HW_TCPM_IIC_BUFFER_SIZE;

        // Check if more than Max Buffer Size are needed to be received
        if(usLength > ucDataCnt)
        {
            usLength -= ucDataCnt;
        }
        else
        {
            ucDataCnt = usLength;
            usLength = 0;
        }

        // 1. Set Fw Busy Flag to Prevent Interrupting by HW
        if(ScalerTypeCTcpmFwBusyCtrl(ucPortIndex, _ENABLE) == _FAIL)
        {
            DebugMessageTypeC("7. [TCPM][PMIC] Polling hw_i2c_busy Failed, <READ | WORD> Addr = >", (BYTE)usSubAddr);

            return _FAIL;
        }

        // 2. Read PMIC Data by TCPM HW IIC
        if(ScalerTypeCTcpmHwIICRead(ucPortIndex, ucSlaveAddress, ucSubAddrLength, usSubAddr, ucDataCnt, pucReadArray) == _FAIL)
        {
            DebugMessageTypeC("7. [TCPM][PMIC] Read PMIC Data Failed", 0x00);

            // Clear Fw Busy Flag
            ScalerTypeCTcpmFwBusyCtrl(ucPortIndex, _DISABLE);

            return _FAIL;
        }

        // 3. Clear Fw Busy Flag
        ScalerTypeCTcpmFwBusyCtrl(ucPortIndex, _DISABLE);
#else

        // [TO-DO] Dennis : TypeC HW IIC Flow
        ucPortIndex = ucPortIndex;
        pucReadArray = pucReadArray;

#endif // End of #if(_HW_TCPM_SUPPORT == _ON)

        // Increase data location
        pucReadArray += ucDataCnt;

        // Increment Sub-Addr for next Read
        usSubAddr += ucDataCnt;
    }

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : Write data to the selected device by IIC
// Input Value  : enumTypeCPcbPort, ucSlaveAddr, usSubAddr, ucSubAddrLength, usLength, pucReadArray
// Output Value : Write result (Fail/Success)
//--------------------------------------------------
bit ScalerTypeCTcpmPmicIICWrite(EnumTypeCPcbPort enumTypeCPcbPort, BYTE ucSlaveAddr, WORD usSubAddr, BYTE ucSubAddrLength, WORD usLength, BYTE *pucWriteArray)
{
    BYTE ucPortIndex = ScalerTypeCTcpmGetPortIndex(enumTypeCPcbPort);
    BYTE ucSlaveAddress = ucSlaveAddr;
    BYTE ucDataCnt = 0;
#if(_HW_TCPM_SUPPORT == _ON)
    BYTE pucTempData[_HW_TCPM_IIC_BUFFER_SIZE + 1];
#endif

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

#if(_HW_TCPM_SUPPORT == _ON)
        // Transmit max bytes each time (Buffer Size - Slave Addr Length (1 Byte) - Sub Addr Length (ucSubAddrLength))
        ucDataCnt = _HW_TCPM_IIC_BUFFER_SIZE - 1 - ucSubAddrLength;

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

        // 1. Set Fw Busy Flag to Prevent Interrupting by HW
        if(ScalerTypeCTcpmFwBusyCtrl(ucPortIndex, _ENABLE) == _FAIL)
        {
            DebugMessageTypeC("7. [TCPM][PMIC] Polling hw_i2c_busy Failed, <WRITE | WORD> Addr = >", (BYTE)usSubAddr);

            return _FAIL;
        }

        // 2. Write PMIC Data by TCPM HW IIC
        if(ScalerTypeCTcpmHwIICWrite(ucPortIndex, ucSlaveAddress, ucSubAddrLength, usSubAddr, ucDataCnt, pucTempData) == _FAIL)
        {
            DebugMessageTypeC("7. [TCPM][PMIC] Write PMIC Data Failed", 0x00);

            // Clear Fw Busy Flag
            ScalerTypeCTcpmFwBusyCtrl(ucPortIndex, _DISABLE);

            return _FAIL;
        }

        // 3. Clear Fw Busy Flag
        ScalerTypeCTcpmFwBusyCtrl(ucPortIndex, _DISABLE);
#else

        // [TO-DO] Dennis : TypeC HW IIC Flow
        ucPortIndex = ucPortIndex;
        pucWriteArray = pucWriteArray;

#endif // End of #if(_HW_TCPM_SUPPORT == _ON)

        // Increment Sub-Addr for next Write
        usSubAddr += ucDataCnt;
    }

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : Type-C TCPM PMIC Initial Settings
// Input Value  : ucPortIndex
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmPmicInitial(BYTE ucPortIndex)
{
    EnumTypeCPcbPort enumTypeCPcbPort = g_penumTypeCTcpmPort[ucPortIndex];

    // ========================================================
    // Initial HW Setting
    // ========================================================
    ExternalDeviceInterfaceTypeCPmicACOnInitial(enumTypeCPcbPort);

    // ========================================================
    // Debug Function
    // ========================================================
#if(_TCPM_PMIC_FORCE_OUTPUT == _ON)
    ScalerTypeCTcpmPmicSetting(ucPortIndex, _ON, _PD_POWER_SRC, _PD_FIX_SUPPLY_PDO, _TCPM_PMIC_FORCE_VOLTAGE, _TCPM_PMIC_FORCE_CURRENT, _PD_PEAK_CUR_NONE);
    ScalerTimerDelayXms(3000);

#if(_EMB_TYPE_C_PMIC_DEBUG == _ON)
    if(ExternalDeviceInterfaceTypeCPmicDebugCheckStatus(enumTypeCPcbPort) == _TYPE_C_PMIC_CONTROL_FAIL)
    {
        DebugMessageTypeC("[TCPM] PMIC Check Fail!", 0x00);
    }
#endif

    ScalerTypeCTcpmPmicSetting(ucPortIndex, _OFF, _PD_POWER_SRC, _PD_NONE_SETTING_PDO, 0, 0, _PD_PEAK_CUR_NONE);
#endif
}

//--------------------------------------------------
// Description  : Type-C TCPM PMIC Reset Settings
// Input Value  : ucPortIndex
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmPmicReset(BYTE ucPortIndex)
{
    EnumTypeCPcbPort enumTypeCPcbPort = g_penumTypeCTcpmPort[ucPortIndex];

    // ========================================================
    // Reset HW Setting
    // ========================================================
    ExternalDeviceInterfaceTypeCPmicUnattachReset(enumTypeCPcbPort);

    // ========================================================
    // Clear Flag and Reset Value
    // ========================================================

    // Reset PMIC Output Type
    SET_TCPM_PMIC_OUTPUT_MODE_STATUS(ucPortIndex, _PD_NONE_SETTING_PDO);

#if(_TYPE_C_PMIC_FW_POLLING_OCP_SUPPORT == _ON)
    if(GET_TCPM_PMIC_OCP_PROTECT_METHOD(ucPortIndex) == _TYPE_C_PMIC_FW_OCP_BY_POLLING_PMIC)
    {
        SET_TCPM_PMIC_OCP_CURRENT_VALUE(ucPortIndex, 0);
        CLR_TCPM_PMIC_OCP_PROTECT_TRIGGER(ucPortIndex);
    }
#endif // End of #if(_TYPE_C_PMIC_FW_POLLING_OCP_SUPPORT == _ON)

#if(_PORT_CTRL_EMB_PD3_PPS_SUPPORT == _ON)
    if(GET_TCPM_PD_PPS_SUPPORT(ucPortIndex) == _ON)
    {
        CLR_TCPM_PMIC_GET_OMF_INFO_START(ucPortIndex);
        SET_TCPM_PMIC_OMF_INFO(ucPortIndex, _TYPE_C_PMIC_CV_MODE_OPERATION);
    }
#endif
}

//--------------------------------------------------
// Description  : Control TCPM PMIC to Directed Voltage
// Input Value  : ucPortIndex, bAction, bPowerDirection, enumPdoType, usVoltage(Unit = 10mV), usCurrent(Unit = 10mA), enumPeakCurrent
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
bit ScalerTypeCTcpmPmicSetting(BYTE ucPortIndex, bit bAction, bit bPowerDirection, EnumTypeCPDPdoType enumPdoType, WORD usVoltage, WORD usCurrent, EnumTypeCPDPeakCurType enumPeakCurrent)
{
    EnumTypeCPcbPort enumTypeCPcbPort = g_penumTypeCTcpmPort[ucPortIndex];
    EnumTypeCPmicControlResult enumResult = _TYPE_C_PMIC_CONTROL_FAIL;
    EnumTypeCPmicDirection enumDirection = _TYPE_C_PMIC_DIRECTION_SNK;

#if(_TYPE_C_POWER_DEBUG == _ON)
    DebugMessageTypeC("    [TCPM][PMIC] Setting Flow", bAction);
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
        usCurrent = MAXOF(usCurrent, _TCPM_PMIC_MIN_PPS_CURRENT);
    }
    else
    {
        usCurrent = MAXOF(usCurrent, _TCPM_PMIC_MIN_CURRENT);
    }

#if(_TYPE_C_PMIC_FW_POLLING_OCP_SUPPORT == _ON)
    if(GET_TCPM_PMIC_OCP_PROTECT_METHOD(ucPortIndex) == _TYPE_C_PMIC_FW_OCP_BY_POLLING_PMIC)
    {
        // ========================================================
        // OCP by Polling PMIC's ADC Value Setting Flow
        // ========================================================

        // Clear PMIC OCP Protect Trigger Flag
        CLR_TCPM_PMIC_OCP_PROTECT_TRIGGER(ucPortIndex);

        if((bAction == _ON) && (bPowerDirection == _PD_POWER_SRC))
        {
            // Set Flag to Active PMIC Protection Timer When Vbus Power Stable
            SET_TCPM_PMIC_PROTECT_TIMER_CHECK(ucPortIndex);

            // Set Safety Current Value
            SET_TCPM_PMIC_OCP_CURRENT_VALUE(ucPortIndex, (WORD)(((DWORD)usCurrent * GET_TCPM_PMIC_FW_OCP_CURRENT_VALUE(ucPortIndex)) / 100));

            // ====================================================
            // PMIC Current Setting Adjustment
            // ====================================================

            // Add more 66% OCP value in order to avoid triggering the PMIC self OCP
            usCurrent = ((WORD)((((DWORD)usCurrent) * (GET_TCPM_PMIC_FW_OCP_CURRENT_VALUE(ucPortIndex) + 66)) / 100));
        }
    }
#endif // End of #if(_TYPE_C_PMIC_FW_POLLING_OCP_SUPPORT == _ON)

#if(_PORT_CTRL_EMB_PD3_PPS_SUPPORT == _ON)
    if(GET_TCPM_PD_PPS_SUPPORT(ucPortIndex) == _ON)
    {
        // ====================================================
        // PD 3.0 PPS Support Flow
        // ====================================================
        if((bAction == _ON) && (bPowerDirection == _PD_POWER_SRC))
        {
            SET_TCPM_PMIC_GET_OMF_INFO_START(ucPortIndex);
        }
        else
        {
            CLR_TCPM_PMIC_GET_OMF_INFO_START(ucPortIndex);
        }
    }
#endif

#if(_PORT_CTRL_TCPM_PMIC_CHECK_SUPPORT == _ON)
    if(GET_TCPM_PMIC_CHECK_SUPPORT(ucPortIndex) == _ON)
    {
#if(_EMB_TYPE_C_PMIC_DEBUG == _ON)
        // ========================================================
        // PMIC Debug Setting Flow
        // ========================================================
        if((bAction == _ON) && (bPowerDirection == _PD_POWER_SRC))
        {
            // Set Flag to Active PMIC Protection Timer When Vbus Power Stable
            SET_TCPM_PMIC_PROTECT_TIMER_CHECK(ucPortIndex);
        }
#endif

        // ========================================================
        // PMIC Check Support Setting Flow
        // ========================================================
        if((bAction == _ON) && (bPowerDirection == _PD_POWER_SRC))
        {
            SET_TCPM_PMIC_OUTPUT_ENABLE(ucPortIndex);
            SET_TCPM_PMIC_BIDIR_MODE(ucPortIndex, _PD_POWER_SRC);
        }
        else
        {
            CLR_TCPM_PMIC_OUTPUT_ENABLE(ucPortIndex);
            SET_TCPM_PMIC_BIDIR_MODE(ucPortIndex, _PD_POWER_SNK);

            // Clear PMIC Protection Timer Check Flag When Turn off Vbus Power
            CLR_TCPM_PMIC_PROTECT_TIMER_CHECK(ucPortIndex);
        }

        CLR_TCPM_PMIC_PROTECT_VALID(ucPortIndex);
    }
#endif

    // ====================================================
    // PMIC Setting Flow
    // ====================================================
    if(bAction == _ON)
    {
        ScalerTypeCTcpmPmicSwitchControl(ucPortIndex, _ON, bPowerDirection);

        if(bPowerDirection == _PD_POWER_SRC)
        {
            enumDirection = _TYPE_C_PMIC_DIRECTION_SRC;
        }
        else
        {
            enumDirection = _TYPE_C_PMIC_DIRECTION_SNK;
        }

        if(GET_TCPM_PMIC_OUTPUT_MODE_STATUS(ucPortIndex) != enumPdoType)
        {
#if(_PORT_CTRL_EMB_PD3_PPS_SUPPORT == _ON)
            if(GET_TCPM_PD_PPS_SUPPORT(ucPortIndex) == _ON)
            {
                if(ExternalDeviceInterfaceTypeCPmicPpsOutputModeSetting(enumTypeCPcbPort, enumDirection, enumPdoType) == _TYPE_C_PMIC_CONTROL_FAIL)
                {
                    return _FAIL;
                }
            }
#endif
            SET_TCPM_PMIC_OUTPUT_MODE_STATUS(ucPortIndex, enumPdoType);
        }

        enumResult = ExternalDeviceInterfaceTypeCPmicVoltageCurrentSetting(enumTypeCPcbPort, enumDirection, usVoltage, usCurrent);

#if(_TYPE_C_POWER_DEBUG == _ON)
        DebugMessageTypeC("    [TCPM][PMIC] Vbus Power On", bAction);
#endif
    }
    else
    {
        // Reset PMIC Output Type
        SET_TCPM_PMIC_OUTPUT_MODE_STATUS(enumPdoType, enumPdoType);

        enumResult = ExternalDeviceInterfaceTypeCPmicTurnOff(enumTypeCPcbPort);

#if(_TYPE_C_POWER_DEBUG == _ON)
        DebugMessageTypeC("    [TCPM][PMIC] Vbus Power Off", bAction);
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
        SET_TCPM_REQ_PWR(ucPortIndex, (WORD)((DWORD)usVoltage * usCurrent / 1000)); // Calculate Requested Power to Unit = 0.1W
        SET_TCPM_OUTPUT_VOL(ucPortIndex, usVoltage);
        SET_TCPM_OUTPUT_CUR(ucPortIndex, usCurrent);
        SET_TCPM_VBUS_STATUS(ucPortIndex, bAction);

#if(_TYPE_C_POWER_DEBUG == _ON)
        DebugMessageTypeC("        ----> Setting Voltage: ", GET_TCPM_OUTPUT_VOL());
        DebugMessageTypeC("        ----> Setting Current: ", GET_TCPM_OUTPUT_CUR());
        DebugMessageTypeC("        ----> Setting Power: ", GET_TCPM_REQ_PWR());
#endif

        return _SUCCESS;
    }
    else
    {
        return _FAIL;
    }
}

//--------------------------------------------------
// Description  : Type-C TCPM PMIC VBUS Discharge Control
// Input Value  : ucPortIndex, bEn : _ENABLE / _DISABLE
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
bit ScalerTypeCTcpmPmicVbusDischarge(BYTE ucPortIndex, bit bEn)
{
    EnumTypeCPmicDischarge enumDischarge = _TYPE_C_PMIC_DISCHARGE_DISABLE;

    if(bEn == _ON)
    {
        enumDischarge = _TYPE_C_PMIC_DISCHARGE_ENABLE;
    }
    else
    {
        ScalerTypeCTcpmPmicSwitchControl(ucPortIndex, _OFF, _PD_POWER_SNK);
        enumDischarge = _TYPE_C_PMIC_DISCHARGE_DISABLE;
    }

    if(ExternalDeviceInterfaceTypeCPmicVbusDischarge(g_penumTypeCTcpmPort[ucPortIndex], enumDischarge) == _TYPE_C_PMIC_CONTROL_SUCCESS)
    {
        return _SUCCESS;
    }
    else
    {
        return _FAIL;
    }
}

//--------------------------------------------------
// Description  : TCPM PMIC Switch Control
// Input Value  : ucPortIndex, bEn, bPowerDirection
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
bit ScalerTypeCTcpmPmicSwitchControl(BYTE ucPortIndex, bit bEn, bit bPowerDirection)
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


    if(ExternalDeviceInterfaceTypeCPmicSwitchControl(g_penumTypeCTcpmPort[ucPortIndex], enumSwitchControl, enumDirection) == _TYPE_C_PMIC_CONTROL_SUCCESS)
    {
        return _SUCCESS;
    }
    else
    {
        return _FAIL;
    }
}

#if(_PORT_CTRL_TCPM_PMIC_CHECK_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Type-C Tcpm PMIC Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmPmicHandler(BYTE ucPortIndex)
{
    // Check if Start PMIC Protection Tracking Timer
    if(GET_TCPM_PMIC_PROTECT_TIMER_START(ucPortIndex) == _TRUE)
    {
        CLR_TCPM_PMIC_PROTECT_TIMER_START(ucPortIndex);

        // Active PMIC Protection Tracking Timer
        ScalerTypeCTcpmReactiveTimerEvent(ucPortIndex, 40, _SCALER_TIMER_EVENT_TCPM_PMIC_TRACKING);
    }
}

//--------------------------------------------------
// Description  : Type-C TCPM PMIC Protection Tracking
// Input Value  : ucPortIndex
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
bit ScalerTypeCTcpmPmicProtectTracking(BYTE ucPortIndex)
{
    BYTE ucTimerEventDelay = 0xFF; // 0xFF: Control_Fail, 0xFE: Cancel_Timer

#if(_TYPE_C_PMIC_FW_POLLING_OCP_SUPPORT == _ON)
    if(GET_TCPM_PMIC_OCP_PROTECT_METHOD(ucPortIndex) == _TYPE_C_PMIC_FW_OCP_BY_POLLING_PMIC)
    {
        BYTE ucPollingOcpDelay = ScalerTypeCTcpmPmicTrackingPollingOcp(ucPortIndex);
        ucTimerEventDelay = MINOF(ucTimerEventDelay, ucPollingOcpDelay);
    }
#endif

#if(_EMB_TYPE_C_PMIC_DEBUG == _ON)
    ExternalDeviceInterfaceTypeCPmicDebugCheckStatus(g_penumTypeCTcpmPort[ucPortIndex]);

    ucTimerEventDelay = MINOF(ucTimerEventDelay, 200);
#endif

    // Check if Control Fail
    if(ucTimerEventDelay == 0xFF)
    {
        return _FAIL;
    }

    // Reactive PMIC Protection Tracking Timer Event
    if(ucTimerEventDelay < 0xFE)
    {
        ScalerTypeCTcpmReactiveTimerEvent(ucPortIndex, ucTimerEventDelay, _SCALER_TIMER_EVENT_TCPM_PMIC_TRACKING);
    }

    return _SUCCESS;
}

#if(_TYPE_C_PMIC_FW_POLLING_OCP_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Type-C TCPM PMIC Polling Ocp Tracking
// Input Value  : ucPortIndex
// Output Value : Delay_Time(Unit: ms): 10 ~ 253
//--------------------------------------------------
BYTE ScalerTypeCTcpmPmicTrackingPollingOcp(BYTE ucPortIndex)
{
    if(GET_TCPM_PMIC_OCP_PROTECT_TRIGGER(ucPortIndex) == _FALSE)
    {
        EnumTypeCPcbPort enumTypeCPcbPort = g_penumTypeCTcpmPort[ucPortIndex];
        WORD usCurrentValue = 0x0000;
        WORD usOcpDelay = 0x0000;

        DebugMessageTypeC("[TCPM] Pmic Polling OCP Tracking", 0x00);

        // Read current value from PMIC's ADC
        usCurrentValue = ExternalDeviceInterfaceTypeCPmicReadPmicAdcCurrentValue(enumTypeCPcbPort);

        // Debounce when current > OCP threshold
        if(usCurrentValue >= GET_TCPM_PMIC_OCP_CURRENT_VALUE(ucPortIndex))
        {
            ScalerTimerDelayXms(2);
            usCurrentValue = ExternalDeviceInterfaceTypeCPmicReadPmicAdcCurrentValue(enumTypeCPcbPort);
        }

        // OCP judgment
        if(usCurrentValue >= GET_TCPM_PMIC_OCP_CURRENT_VALUE(ucPortIndex))
        {
            usOcpDelay = MAXOF(GET_TCPM_PMIC_FW_OCP_DELAY_SHUTDOWN(ucPortIndex), 10);
            ScalerTypeCTcpmReactiveTimerEvent(ucPortIndex, usOcpDelay, _SCALER_TIMER_EVENT_TCPM_PMIC_POLLING_OCP);

            DebugMessageTypeC("[TCPM] Pmic:Output Current OCP", 0x00);

            SET_TCPM_PMIC_OCP_PROTECT_TRIGGER(ucPortIndex);

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
// Description  : Type-C TCPM PMIC FW Polling Ocp Protect
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmPmicPollingOcpProtect(BYTE ucPortIndex)
{
    DebugMessageTypeC("[TCPM] Pmic turn-off for Polling OCP", 0x00);

    ScalerTypeCTcpmVbusCtrl(ucPortIndex, _OFF, _PD_POWER_SNK, _PD_NONE_SETTING_PDO, 0, 0, _PD_PEAK_CUR_NONE);

    // Set OCP Event
    ScalerTypeCTcpmSetPdSystemEvent(ucPortIndex, _PD_SYS_EVENT_POWER_OCP);
}
#endif // End of #if(_TYPE_C_PMIC_FW_POLLING_OCP_SUPPORT == _ON)
#endif // End of #if(_PORT_CTRL_TCPM_PMIC_CHECK_SUPPORT == _ON)
#endif // End of #if(_TYPE_C_PMIC_SUPPORT == _ON)

#if(_PORT_CTRL_TCPM_OVP_UVP_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Type-C 0 PMIC OVP interrupt handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmOvpUvpHandler(BYTE ucPortIndex)
{
    EnumTypeCPcbPort enumTypeCPcbPort = g_penumTypeCTcpmPort[ucPortIndex];
    BYTE ucCount = 0;
    WORD usVoltage = ScalerTypeCTcpmGetVbusVoltage(ucPortIndex);

    // Convert Vbus Voltage (Unit = 100mV) to 10mV
    usVoltage = usVoltage * 10;

    // Check if OVP or UVP protect trigger
    if(usVoltage >= GET_TCPM_OVP_VOLTAGE(ucPortIndex))
    {
        // OVP Protection Debounce check
        for(ucCount = 0; ucCount < GET_TCPM_OVP_JUDGE_DEBOUNCE(ucPortIndex); ucCount++)
        {
            // Compare OVP Trigger Level with Vbus voltage in "ADC Ideal Data" Form
            if((ScalerTypeCTcpmGetVbusVoltage(ucPortIndex) * 10) < GET_TCPM_OVP_VOLTAGE(ucPortIndex))
            {
                // Active Timer Event to Detect OVP/UVP
                ScalerTypeCTcpmActiveTimerEvent(ucPortIndex, 40, _SCALER_TIMER_EVENT_TCPM_OVP_UVP_CHECK);

                return;
            }
        }

        // Set OVP Event
        ScalerTypeCTcpmSetPdSystemEvent(enumTypeCPcbPort, _PD_SYS_EVENT_POWER_OVP);
    }
    else if(usVoltage <= GET_TCPM_UVP_VOLTAGE(ucPortIndex))
    {
        // UVP Protection Debounce check
        for(ucCount = 0; ucCount < GET_TCPM_UVP_JUDGE_DEBOUNCE(ucPortIndex); ucCount++)
        {
            // Compare UVP Trigger Level with Vbus voltage in "ADC Ideal Data" Form
            if((ScalerTypeCTcpmGetVbusVoltage(ucPortIndex) * 10) > GET_TCPM_UVP_VOLTAGE(ucPortIndex))
            {
                // Active Timer Event to Detect OVP/UVP
                ScalerTypeCTcpmActiveTimerEvent(ucPortIndex, 40, _SCALER_TIMER_EVENT_TCPM_OVP_UVP_CHECK);

                return;
            }
        }

        // Set UVP Event
        ScalerTypeCTcpmSetPdSystemEvent(enumTypeCPcbPort, _PD_SYS_EVENT_POWER_UVP);
    }

    // Disable Vbus
    ScalerTypeCTcpmVbusCtrl(ucPortIndex, _OFF, _PD_POWER_SNK, _PD_NONE_SETTING_PDO, 0, 0, _PD_PEAK_CUR_NONE);
}
#endif // End of #if(_PORT_CTRL_TCPM_OVP_UVP_SUPPORT == _ON)
#endif // End of #if(_PORT_CTRL_TCPM_SUPPORT == _ON)
#endif // End of #if(_TYPE_C_PORT_CTRL_SUPPORT == _ON)
