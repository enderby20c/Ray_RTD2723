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
// ID Code      : ScalerFunctionInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_FUNCTION_INCLUDE_H__
#define __SCALER_FUNCTION_INCLUDE_H__

#include <Global.h>
#include <Project.h>
#include <ScalerFunctionInterface.h>

#include <Sync/ScalerSyncInclude.h>
#include <TimerFunction/ScalerTimerFunctionInclude.h>
#include <DpHdcp14Tx/ScalerDpHdcp14TxInclude.h>
#include <DpRx/ScalerDpRxInclude.h>
#include <DpStream/ScalerDpStreamInclude.h>
#include <DpMacRx/ScalerDpMacRxInclude.h>
#include <DpMacDphyRx/ScalerDpMacDphyRxInclude.h>
#include <DpMacStreamRx/ScalerDpMacStreamRxInclude.h>
#include <DpMacTx/ScalerDpMacTxInclude.h>
#include <DpPhyTx/ScalerDpPhyTxInclude.h>
#include <GDIPhyDpTx/ScalerGDIPhyDpTxInclude.h>

#include <Hdcp2/ScalerHdcp2Include.h>
#include <Hdcp14/ScalerHdcp14Include.h>
#include <DpHdcp2/ScalerDpHdcp2Include.h>
#include <DpHdcp2Rx/ScalerDpHdcp2RxInclude.h>
#include <DpHdcp2Rx0/ScalerDpHdcp2Rx0Include.h>
#include <DpHdcp2Rx1/ScalerDpHdcp2Rx1Include.h>
#include <DpHdcp2Rx2/ScalerDpHdcp2Rx2Include.h>
#include <DpHdcp2Tx/ScalerDpHdcp2TxInclude.h>
#include <DpHdcpRx/ScalerDpHdcpRxInclude.h>
#include <DpHdcp14Rx/ScalerDpHdcp14RxInclude.h>
#include <DpHdcp14Rx0/ScalerDpHdcp14Rx0Include.h>
#include <DpHdcp14Rx1/ScalerDpHdcp14Rx1Include.h>
#include <DpHdcp14Rx2/ScalerDpHdcp14Rx2Include.h>

#if(_SCALER_TYPE == _RL6829_SERIES)
#include <RL6829_Series_FunctionInclude.h>
#elif(_SCALER_TYPE == _RL6952_SERIES)
#include <RL6952_Series_FunctionInclude.h>
#elif(_SCALER_TYPE == _RL6978_SERIES)
#include <RL6978_Series_FunctionInclude.h>
#endif

#include <VgaAdc/ScalerVgaAdcInclude.h>
#include <Audio/ScalerAudioInclude.h>
#include <AudioTts/ScalerAudioTtsInclude.h>
#include <DpAudioRx/ScalerDpAudioRxInclude.h>
#include <DpAudioRx0/ScalerDpAudioRx0Include.h>
#include <DpAudioRx1/ScalerDpAudioRx1Include.h>
#include <DpAudioRx2/ScalerDpAudioRx2Include.h>
#include <DpAudioRx3/ScalerDpAudioRx3Include.h>
#include <DpAudioRx4/ScalerDpAudioRx4Include.h>
#include <HdmiAudioRx3/ScalerHdmiAudioRx3Include.h>
#include <HdmiAudioRx4/ScalerHdmiAudioRx4Include.h>
#include <HdmiArcTx/ScalerHdmiArcTxInclude.h>
#include <HdmiArcTxPhy/ScalerHdmiArcTxPhyInclude.h>
#include <Cec/ScalerCecInclude.h>
#include <VgaAuto/ScalerVgaAutoInclude.h>
#include <Color/ScalerColorInclude.h>
#include <DDomain/ScalerDDomainInclude.h>
#include <Memory/ScalerMemoryInclude.h>
#include <SDRAM/ScalerSDRAMInclude.h>
#include <DDR1/ScalerDDR1Include.h>
#include <DDR2/ScalerDDR2Include.h>
#include <DDR3/ScalerDDR3Include.h>
#include <DM/ScalerDMInclude.h>
#include <Debug/ScalerDebugInclude.h>
#include <Display/ScalerDisplayInclude.h>
#include <DisplayVboTx/ScalerDisplayVboTxInclude.h>
#include <DisplayVboTxX/ScalerDisplayVboTxXInclude.h>
#include <DpMacDphyRx0/ScalerDpMacDphyRx0Include.h>
#include <DpMacDphyRx1/ScalerDpMacDphyRx1Include.h>
#include <DpMacDphyRx2/ScalerDpMacDphyRx2Include.h>
#include <DpMacStreamRx0/ScalerDpMacStreamRx0Include.h>
#include <DpMacStreamRx1/ScalerDpMacStreamRx1Include.h>
#include <DpMacStreamRx2/ScalerDpMacStreamRx2Include.h>
#include <DpMacStreamRx3/ScalerDpMacStreamRx3Include.h>
#include <DpMacStreamRx4/ScalerDpMacStreamRx4Include.h>
#include <DpMacDsc/ScalerDpMacDscInclude.h>
#include <DpAuxRx/ScalerDpAuxRxInclude.h>
#include <DpAuxRx0/ScalerDpAuxRx0Include.h>
#include <DpAuxRx1/ScalerDpAuxRx1Include.h>
#include <DpAuxRx2/ScalerDpAuxRx2Include.h>
#include <DpPhyRx/ScalerDpPhyRxInclude.h>
#include <DpPhyRx0/ScalerDpPhyRx0Include.h>
#include <DpPhyRx1/ScalerDpPhyRx1Include.h>
#include <DpPhyRx2/ScalerDpPhyRx2Include.h>
#include <DpMstRx/ScalerDpMstRxInclude.h>
#include <DpMacMstToSst/ScalerDpMacMstToSstInclude.h>
#include <DpAuxTx/ScalerDpAuxTxInclude.h>
#include <DpMstTx/ScalerDpMstTxInclude.h>
#include <Drr/ScalerDrrInclude.h>
#include <DscDecoder/ScalerDscDecoderInclude.h>
#include <DscDecoder0/ScalerDscDecoder0Include.h>
#include <DscDecoder1/ScalerDscDecoder1Include.h>
#include <FmtCnv/ScalerFmtCnvInclude.h>
#include <OD/ScalerODInclude.h>
#include <FRC/ScalerFRCInclude.h>
#include <ImgCmp/ScalerImgCmpInclude.h>
#include <GDIPhyRx/ScalerGDIPhyRxInclude.h>
#include <GDIPhyRx0/ScalerGDIPhyRx0Include.h>
#include <GDIPhyRx1/ScalerGDIPhyRx1Include.h>
#include <GDIPhyRx2/ScalerGDIPhyRx2Include.h>
#include <GDIPhyRx3/ScalerGDIPhyRx3Include.h>
#include <GDIPhyRx4/ScalerGDIPhyRx4Include.h>
#include <GDIPhyRx5/ScalerGDIPhyRx5Include.h>
#include <Global/ScalerGlobalInclude.h>
#include <Gosd/ScalerGosdInclude.h>
#include <Gosd/ScalerGosdDecompressInclude.h>
#include <Gosd/ScalerGosdSeInclude.h>
#include <Gosd/ScalerGosdDispOsdInclude.h>
#include <IDomain/ScalerIDomainInclude.h>
#include <IOSC/ScalerIOSCInclude.h>
#include <LDO/ScalerLDOInclude.h>
#include <Mbr/ScalerMbrInclude.h>
#include <Mcu/ScalerMcuInclude.h>
#include <Measure/ScalerMeasureInclude.h>
#include <MDomain/ScalerMDomainInclude.h>
#include <DisplayDpTx/ScalerDisplayDpTxInclude.h>
#include <DisplayDpTxX/ScalerDisplayDpTxXInclude.h>
#include <NVRam/ScalerNVRamInclude.h>
#include <Osd/ScalerOsdInclude.h>
#include <OsdSubBlending/ScalerOsdSubBlendingInclude.h>
#include <Pinshare/ScalerPinshareInclude.h>
#include <PLL/ScalerPLLInclude.h>
#include <Power/ScalerPowerInclude.h>
#include <Reg/ScalerRegInclude.h>
#include <Region/ScalerRegionInclude.h>
#include <Rotation/ScalerRotationInclude.h>
#include <Scaling/ScalerScalingInclude.h>
#include <3DDI/Scaler3DDIInclude.h>
#include <Spi/ScalerSpiInclude.h>
#include <VgaSyncProc/ScalerVgaSyncProcInclude.h>
#include <Tcon/ScalerTconInclude.h>
#include <ThermalSensor/ScalerThermalSensorInclude.h>
#include <TmdsMacRx/ScalerTmdsMacRxInclude.h>
#include <TmdsPhyRx/ScalerTmdsPhyRxInclude.h>
#include <TmdsMacRx3/ScalerTmdsMacRx3Include.h>
#include <TmdsMacRx4/ScalerTmdsMacRx4Include.h>
#include <HdmiFrlMacRx/ScalerHdmiFrlMacRxInclude.h>
#include <HdmiFrlMacRx3/ScalerHdmiFrlMacRx3Include.h>
#include <HdmiFrlMacRx4/ScalerHdmiFrlMacRx4Include.h>
#include <TmdsPhyRx3/ScalerTmdsPhyRx3Include.h>
#include <TmdsPhyRx4/ScalerTmdsPhyRx4Include.h>
#include <TypeC/ScalerTypeCInclude.h>
#include <TypeCAdc/ScalerTypeCAdcInclude.h>
#include <TypeC0Cc/ScalerTypeC0CcInclude.h>
#include <TypeC0Pd/ScalerTypeC0PdInclude.h>
#include <TypeC0Pmic/ScalerTypeC0PmicInclude.h>
#include <TypeC1Cc/ScalerTypeC1CcInclude.h>
#include <TypeC1Pd/ScalerTypeC1PdInclude.h>
#include <TypeC1Pmic/ScalerTypeC1PmicInclude.h>
#include <TypeCTcpm/ScalerTypeCTcpmInclude.h>
#include <Usb2Mux/ScalerUsb2MuxInclude.h>
#include <Usb3RepeaterMac/ScalerUsb3RepeaterMacInclude.h>
#include <Usb3RedriverMac0/ScalerUsb3RedriverMac0Include.h>
#include <Usb3RedriverMac1/ScalerUsb3RedriverMac1Include.h>
#include <Usb3RetimerMac0/ScalerUsb3RetimerMac0Include.h>
#include <Usb3RetimerMac1/ScalerUsb3RetimerMac1Include.h>
#include <Usb3RepeaterPhy/ScalerUsb3RepeaterPhyInclude.h>
#include <Usb3RetimerPhy/ScalerUsb3RetimerPhyInclude.h>
#include <Usb3RetimerUfpPhy0/ScalerUsb3RetimerUfpPhy0Include.h>
#include <Usb3RetimerDfpPhy0/ScalerUsb3RetimerDfpPhy0Include.h>
#include <Usb3RetimerUfpPhy1/ScalerUsb3RetimerUfpPhy1Include.h>
#include <Usb3RetimerDfpPhy1/ScalerUsb3RetimerDfpPhy1Include.h>
#include <UsbBillboard/ScalerUsbBillboardInclude.h>
#include <UsbU2Host/ScalerUsbU2HostInclude.h>
#include <UsbFileSys/ScalerUsbFileSysInclude.h>
#include <Vga/ScalerVgaInclude.h>
#include <Vgip/ScalerVgipInclude.h>
#include <IR/ScalerIRInclude.h>
#include <TmdsHdcp2Rx3/ScalerTmdsHdcp2Rx3Include.h>
#include <TmdsHdcp2Rx4/ScalerTmdsHdcp2Rx4Include.h>
#include <CpuSync/ScalerCpuSyncInclude.h>
#include <CpuCtrl/ScalerCpuCtrlInclude.h>
#include <FlashMode/ScalerFlashModeInclude.h>
#include <MemoryDevicePLL/ScalerMemoryDevicePLLInclude.h>

#include <BW32/ScalerBW32Include.h>
#include <BusSb2/ScalerBusSb2Include.h>
#include <BusScpuWrap/ScalerBusScpuWrapInclude.h>
#include <CpuHal/ScalerCpuHalInclude.h>
#include <ScpuSync/ScalerScpuSyncInclude.h>
#include <GlobalCtrl/ScalerGlobalCtrlInclude.h>
#include <MiscCtrl/ScalerMiscCtrlInclude.h>
#include <RBusToDdr/ScalerRBusToDdrInclude.h>
#include <SysTick/ScalerSysTickInclude.h>
#include <Timer/ScalerTimerInclude.h>
#include <Util/ScalerUtilInclude.h>
#include <Wdt/ScalerWdtInclude.h>
#include <OTP/ScalerOTPInclude.h>
#include <DualBank/ScalerDualBankInclude.h>
#include <FwInfo/ScalerFwInfoInclude.h>
#include <FwCheck/ScalerFwCheckInclude.h>
#include <FwUpdate/ScalerFwUpdateInclude.h>
#include <FwUpdateBackground/ScalerFwUpdateBackgroundInclude.h>
#include <FwUpdateForeground/ScalerFwUpdateForegroundInclude.h>

#endif // End of #ifndef __SCALER_FUNCTION_INCLUDE_H__
