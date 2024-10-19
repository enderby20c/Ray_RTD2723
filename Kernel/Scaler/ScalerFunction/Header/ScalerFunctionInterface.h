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
// ID Code      : ScalerFunctionInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_FUNCTION_INTERFACE_H__
#define __SCALER_FUNCTION_INTERFACE_H__

#include <ScalerFunctionInterface_User.h>

#include <Hdcp2/ScalerHdcp2Interface.h>
#include <DpHdcp2/ScalerDpHdcp2Interface.h>
#include <DpHdcp2Rx/ScalerDpHdcp2RxInterface.h>
#include <DpHdcp2Rx0/ScalerDpHdcp2Rx0Interface.h>
#include <DpHdcp2Rx1/ScalerDpHdcp2Rx1Interface.h>
#include <DpHdcp2Rx2/ScalerDpHdcp2Rx2Interface.h>
#include <DpHdcpRx/ScalerDpHdcpRxInterface.h>
#include <DpHdcp14Rx/ScalerDpHdcp14RxInterface.h>
#include <DpHdcp14Rx0/ScalerDpHdcp14Rx0Interface.h>
#include <DpHdcp14Rx1/ScalerDpHdcp14Rx1Interface.h>
#include <DpHdcp14Rx2/ScalerDpHdcp14Rx2Interface.h>

#if(_SCALER_TYPE == _RL6829_SERIES)
#include <RL6829_Series_FunctionInterface.h>
#elif(_SCALER_TYPE == _RL6952_SERIES)
#include <RL6952_Series_FunctionInterface.h>
#elif(_SCALER_TYPE == _RL6978_SERIES)
#include <RL6978_Series_FunctionInterface.h>
#endif

#include <VgaAdc/ScalerVgaAdcInterface.h>
#include <Audio/ScalerAudioInterface.h>
#include <AudioTts/ScalerAudioTtsInterface.h>
#include <DpAudioRx/ScalerDpAudioRxInterface.h>
#include <DpAudioRx0/ScalerDpAudioRx0Interface.h>
#include <DpAudioRx1/ScalerDpAudioRx1Interface.h>
#include <DpAudioRx2/ScalerDpAudioRx2Interface.h>
#include <DpAudioRx3/ScalerDpAudioRx3Interface.h>
#include <DpAudioRx4/ScalerDpAudioRx4Interface.h>
#include <HdmiAudioRx3/ScalerHdmiAudioRx3Interface.h>
#include <HdmiAudioRx4/ScalerHdmiAudioRx4Interface.h>
#include <HdmiArcTx/ScalerHdmiArcTxInterface.h>
#include <HdmiArcTxPhy/ScalerHdmiArcTxPhyInterface.h>
#include <Cec/ScalerCecInterface.h>
#include <VgaAuto/ScalerVgaAutoInterface.h>
#include <3DDI/Scaler3DDIInterface.h>
#include <Color/ScalerColorInterface.h>
#include <DDomain/ScalerDDomainInterface.h>
#include <SDRAM/ScalerSDRAMInterface.h>
#include <DDR1/ScalerDDR1Interface.h>
#include <DDR2/ScalerDDR2Interface.h>
#include <DDR3/ScalerDDR3Interface.h>
#include <DM/ScalerDMInterface.h>
#include <Debug/ScalerDebugInterface.h>
#include <Display/ScalerDisplayInterface.h>
#include <DisplayDpTx/ScalerDisplayDpTxInterface.h>
#include <DisplayDpTxX/ScalerDisplayDpTxXInterface.h>
#include <DisplayVboTx/ScalerDisplayVboTxInterface.h>
#include <DisplayVboTxX/ScalerDisplayVboTxXInterface.h>
#include <DpRx/ScalerDpRxInterface.h>
#include <DpStream/ScalerDpStreamInterface.h>
#include <DpMacRx/ScalerDpMacRxInterface.h>
#include <DpMacDphyRx/ScalerDpMacDphyRxInterface.h>
#include <DpMacDphyRx0/ScalerDpMacDphyRx0Interface.h>
#include <DpMacDphyRx1/ScalerDpMacDphyRx1Interface.h>
#include <DpMacDphyRx2/ScalerDpMacDphyRx2Interface.h>
#include <DpMacStreamRx/ScalerDpMacStreamRxInterface.h>
#include <DpMacStreamRx0/ScalerDpMacStreamRx0Interface.h>
#include <DpMacStreamRx1/ScalerDpMacStreamRx1Interface.h>
#include <DpMacStreamRx2/ScalerDpMacStreamRx2Interface.h>
#include <DpMacStreamRx3/ScalerDpMacStreamRx3Interface.h>
#include <DpMacStreamRx4/ScalerDpMacStreamRx4Interface.h>
#include <DpMacDsc/ScalerDpMacDscInterface.h>
#include <Power/ScalerPowerInterface.h>
#include <DpAuxRx/ScalerDpAuxRxInterface.h>
#include <DpAuxRx0/ScalerDpAuxRx0Interface.h>
#include <DpAuxRx1/ScalerDpAuxRx1Interface.h>
#include <DpAuxRx2/ScalerDpAuxRx2Interface.h>
#include <DpPhyRx/ScalerDpPhyRxInterface.h>
#include <DpPhyRx0/ScalerDpPhyRx0Interface.h>
#include <DpPhyRx1/ScalerDpPhyRx1Interface.h>
#include <DpPhyRx2/ScalerDpPhyRx2Interface.h>
#include <DpHdcp14Tx/ScalerDpHdcp14TxInterface.h>
#include <DpHdcp2Tx/ScalerDpHdcp2TxInterface.h>
#include <DpMstRx/ScalerDpMstRxInterface.h>
#include <DpMacMstToSst/ScalerDpMacMstToSstInterface.h>
#include <DpAuxTx/ScalerDpAuxTxInterface.h>
#include <DpMacTx/ScalerDpMacTxInterface.h>
#include <DpPhyTx/ScalerDpPhyTxInterface.h>
#include <DpMstTx/ScalerDpMstTxInterface.h>
#include <Drr/ScalerDrrInterface.h>
#include <DscDecoder/ScalerDscDecoderInterface.h>
#include <DscDecoder0/ScalerDscDecoder0Interface.h>
#include <DscDecoder1/ScalerDscDecoder1Interface.h>
#include <OTP/ScalerOTPInterface.h>
#include <FmtCnv/ScalerFmtCnvInterface.h>
#include <FRC/ScalerFRCInterface.h>
#include <ImgCmp/ScalerImgCmpInterface.h>
#include <GDIPhyRx/ScalerGDIPhyRxInterface.h>
#include <GDIPhyRx0/ScalerGDIPhyRx0Interface.h>
#include <GDIPhyRx1/ScalerGDIPhyRx1Interface.h>
#include <GDIPhyRx2/ScalerGDIPhyRx2Interface.h>
#include <GDIPhyRx3/ScalerGDIPhyRx3Interface.h>
#include <GDIPhyRx4/ScalerGDIPhyRx4Interface.h>
#include <GDIPhyRx5/ScalerGDIPhyRx5Interface.h>
#include <GDIPhyDpTx/ScalerGDIPhyDpTxInterface.h>
#include <Gosd/ScalerGosdInterface.h>
#include <Gosd/ScalerGosdDecompressInterface.h>
#include <Gosd/ScalerGosdSeInterface.h>
#include <Gosd/ScalerGosdDispOsdInterface.h>
#include <Region/ScalerRegionInterface.h>
#include <Global/ScalerGlobalInterface.h>
#include <IDomain/ScalerIDomainInterface.h>
#include <IOSC/ScalerIOSCInterface.h>
#include <LDO/ScalerLDOInterface.h>
#include <Mbr/ScalerMbrInterface.h>
#include <Mcu/ScalerMcuInterface.h>
#include <Measure/ScalerMeasureInterface.h>
#include <MDomain/ScalerMDomainInterface.h>
#include <Memory/ScalerMemoryInterface.h>
#include <NVRam/ScalerNVRamInterface.h>
#include <OD/ScalerODInterface.h>
#include <Osd/ScalerOsdInterface.h>
#include <OsdSubBlending/ScalerOsdSubBlendingInterface.h>
#include <Pinshare/ScalerPinshareInterface.h>
#include <PLL/ScalerPLLInterface.h>
#include <Reg/ScalerRegInterface.h>
#include <Rotation/ScalerRotationInterface.h>
#include <Scaling/ScalerScalingInterface.h>
#include <Spi/ScalerSpiInterface.h>
#include <Sync/ScalerSyncInterface.h>
#include <VgaSyncProc/ScalerVgaSyncProcInterface.h>
#include <Tcon/ScalerTconInterface.h>
#include <ThermalSensor/ScalerThermalSensorInterface.h>
#include <TimerFunction/ScalerTimerFunctionInterface.h>
#include <TmdsMacRx/ScalerTmdsMacRxInterface.h>
#include <TmdsPhyRx/ScalerTmdsPhyRxInterface.h>
#include <TmdsMacRx3/ScalerTmdsMacRx3Interface.h>
#include <TmdsMacRx4/ScalerTmdsMacRx4Interface.h>
#include <HdmiFrlMacRx/ScalerHdmiFrlMacRxInterface.h>
#include <HdmiFrlMacRx3/ScalerHdmiFrlMacRx3Interface.h>
#include <HdmiFrlMacRx4/ScalerHdmiFrlMacRx4Interface.h>
#include <TmdsPhyRx3/ScalerTmdsPhyRx3Interface.h>
#include <TmdsPhyRx4/ScalerTmdsPhyRx4Interface.h>
#include <TypeC/ScalerTypeCInterface.h>
#include <TypeCAdc/ScalerTypeCAdcInterface.h>
#include <TypeC0Cc/ScalerTypeC0CcInterface.h>
#include <TypeC0Pd/ScalerTypeC0PdInterface.h>
#include <TypeC0Pmic/ScalerTypeC0PmicInterface.h>
#include <TypeC1Cc/ScalerTypeC1CcInterface.h>
#include <TypeC1Pd/ScalerTypeC1PdInterface.h>
#include <TypeC1Pmic/ScalerTypeC1PmicInterface.h>
#include <TypeCTcpm/ScalerTypeCTcpmInterface.h>
#include <Usb2Mux/ScalerUsb2MuxInterface.h>
#include <Usb3RepeaterMac/ScalerUsb3RepeaterMacInterface.h>
#include <Usb3RedriverMac0/ScalerUsb3RedriverMac0Interface.h>
#include <Usb3RedriverMac1/ScalerUsb3RedriverMac1Interface.h>
#include <Usb3RetimerMac0/ScalerUsb3RetimerMac0Interface.h>
#include <Usb3RetimerMac1/ScalerUsb3RetimerMac1Interface.h>
#include <Usb3RepeaterPhy/ScalerUsb3RepeaterPhyInterface.h>
#include <Usb3RetimerPhy/ScalerUsb3RetimerPhyInterface.h>
#include <Usb3RetimerUfpPhy0/ScalerUsb3RetimerUfpPhy0Interface.h>
#include <Usb3RetimerDfpPhy0/ScalerUsb3RetimerDfpPhy0Interface.h>
#include <Usb3RetimerUfpPhy1/ScalerUsb3RetimerUfpPhy1Interface.h>
#include <Usb3RetimerDfpPhy1/ScalerUsb3RetimerDfpPhy1Interface.h>
#include <UsbBillboard/ScalerUsbBillboardInterface.h>
#include <UsbU2Host/ScalerUsbU2HostInterface.h>
#include <UsbFileSys/ScalerUsbFileSysInterface.h>
#include <Vga/ScalerVgaInterface.h>
#include <Vgip/ScalerVgipInterface.h>
#include <IR/ScalerIRInterface.h>
#include <TmdsHdcp2Rx3/ScalerTmdsHdcp2Rx3Interface.h>
#include <TmdsHdcp2Rx4/ScalerTmdsHdcp2Rx4Interface.h>

#include <CpuSync/ScalerCpuSyncInterface.h>
#include <CpuCtrl/ScalerCpuCtrlInterface.h>

#include <FlashMode/ScalerFlashModeInterface.h>
#include <MemoryDevicePLL/ScalerMemoryDevicePLLInterface.h>

#include <BW32/ScalerBW32Interface.h>
#include <BusSb2/ScalerBusSb2Interface.h>
#include <BusScpuWrap/ScalerBusScpuWrapInterface.h>
#include <CpuHal/ScalerCpuHalInterface.h>
#include <ScpuSync/ScalerScpuSyncInterface.h>
#include <GlobalCtrl/ScalerGlobalCtrlInterface.h>
#include <MiscCtrl/ScalerMiscCtrlInterface.h>
#include <RBusToDdr/ScalerRBusToDdrInterface.h>
#include <SysTick/ScalerSysTickInterface.h>
#include <Timer/ScalerTimerInterface.h>
#include <Util/ScalerUtilInterface.h>
#include <Wdt/ScalerWdtInterface.h>

#include <../Lib/Header/ScalerImgCmpGen1Include.h>
#include <../Lib/Header/ScalerMbrAdvanceInclude.h>
#include <../Lib/Header/ScalerTconAdvanceInclude.h>
#include <../Lib/Header/ScalerColorAdvancedHDR10Include.h>
#include <../Lib/Header/ScalerColorHDR10Include.h>
#include <DualBank/ScalerDualBankInterface.h>
#include <FwInfo/ScalerFwInfoInterface.h>
#include <FwCheck/ScalerFwCheckInterface.h>
#include <FwUpdate/ScalerFwUpdateInterface.h>
#include <FwUpdateBackground/ScalerFwUpdateBackgroundInterface.h>
#include <FwUpdateForeground/ScalerFwUpdateForegroundInterface.h>

#endif // End of #ifndef __SCALER_FUNCTION_INTERFACE_H__

