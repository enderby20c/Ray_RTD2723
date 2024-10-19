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
// ID Code      : ScalerFunctionInterface_User.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_FUNCTION_INTERFACE_USER_H__
#define __SCALER_FUNCTION_INTERFACE_USER_H__

#include <Region/ScalerRegionInterface_User.h>

#include <Hdcp2/ScalerHdcp2Interface_User.h>
#include <DpHdcp2/ScalerDpHdcp2Interface_User.h>
#include <DpHdcp2Rx/ScalerDpHdcp2RxInterface_User.h>
#include <DpHdcp2Rx0/ScalerDpHdcp2Rx0Interface_User.h>
#include <DpHdcp2Rx1/ScalerDpHdcp2Rx1Interface_User.h>
#include <DpHdcp2Rx2/ScalerDpHdcp2Rx2Interface_User.h>
#include <DpHdcpRx/ScalerDpHdcpRxInterface_User.h>
#include <DpHdcp14Rx/ScalerDpHdcp14RxInterface_User.h>
#include <DpHdcp14Rx0/ScalerDpHdcp14Rx0Interface_User.h>
#include <DpHdcp14Rx1/ScalerDpHdcp14Rx1Interface_User.h>
#include <DpHdcp14Rx2/ScalerDpHdcp14Rx2Interface_User.h>

#if(_SCALER_TYPE == _RL6829_SERIES)
#include <RL6829_Series_FunctionInterface_User.h>
#elif(_SCALER_TYPE == _RL6952_SERIES)
#include <RL6952_Series_FunctionInterface_User.h>
#elif(_SCALER_TYPE == _RL6978_SERIES)
#include <RL6978_Series_FunctionInterface_User.h>
#endif

#include <VgaAdc/ScalerVgaAdcInterface_User.h>
#include <Audio/ScalerAudioInterface_User.h>
#include <AudioTts/ScalerAudioTtsInterface_User.h>
#include <DpAudioRx/ScalerDpAudioRxInterface_User.h>
#include <DpAudioRx0/ScalerDpAudioRx0Interface_User.h>
#include <DpAudioRx1/ScalerDpAudioRx1Interface_User.h>
#include <DpAudioRx2/ScalerDpAudioRx2Interface_User.h>
#include <DpAudioRx3/ScalerDpAudioRx3Interface_User.h>
#include <DpAudioRx4/ScalerDpAudioRx4Interface_User.h>
#include <HdmiAudioRx3/ScalerHdmiAudioRx3Interface_User.h>
#include <HdmiAudioRx4/ScalerHdmiAudioRx4Interface_User.h>
#include <HdmiArcTx/ScalerHdmiArcTxInterface_User.h>
#include <HdmiArcTxPhy/ScalerHdmiArcTxPhyInterface_User.h>
#include <Cec/ScalerCecInterface_User.h>
#include <VgaAuto/ScalerVgaAutoInterface_User.h>
#include <3DDI/Scaler3DDIInterface_User.h>
#include <Color/ScalerColorInterface_User.h>
#include <DDomain/ScalerDDomainInterface_User.h>
#include <SDRAM/ScalerSDRAMInterface_User.h>
#include <DDR1/ScalerDDR1Interface_User.h>
#include <DDR2/ScalerDDR2Interface_User.h>
#include <DDR3/ScalerDDR3Interface_User.h>
#include <DM/ScalerDMInterface_User.h>
#include <Debug/ScalerDebugInterface_User.h>
#include <Display/ScalerDisplayInterface_User.h>
#include <DisplayDpTx/ScalerDisplayDpTxInterface_User.h>
#include <DisplayDpTxX/ScalerDisplayDpTxXInterface_User.h>
#include <DisplayVboTx/ScalerDisplayVboTxInterface_User.h>
#include <DisplayVboTxX/ScalerDisplayVboTxXInterface_User.h>
#include <DpRx/ScalerDpRxInterface_User.h>
#include <DpStream/ScalerDpStreamInterface_User.h>
#include <DpMacRx/ScalerDpMacRxInterface_User.h>
#include <DpMacDphyRx/ScalerDpMacDphyRxInterface_User.h>
#include <DpMacDphyRx0/ScalerDpMacDphyRx0Interface_User.h>
#include <DpMacDphyRx1/ScalerDpMacDphyRx1Interface_User.h>
#include <DpMacDphyRx2/ScalerDpMacDphyRx2Interface_User.h>
#include <DpMacStreamRx/ScalerDpMacStreamRxInterface_User.h>
#include <DpMacStreamRx0/ScalerDpMacStreamRx0Interface_User.h>
#include <DpMacStreamRx1/ScalerDpMacStreamRx1Interface_User.h>
#include <DpMacStreamRx2/ScalerDpMacStreamRx2Interface_User.h>
#include <DpMacStreamRx3/ScalerDpMacStreamRx3Interface_User.h>
#include <DpMacStreamRx4/ScalerDpMacStreamRx4Interface_User.h>
#include <DpMacDsc/ScalerDpMacDscInterface_User.h>

#include <DpAuxRx/ScalerDpAuxRxInterface_User.h>
#include <DpAuxRx0/ScalerDpAuxRx0Interface_User.h>
#include <DpAuxRx1/ScalerDpAuxRx1Interface_User.h>
#include <DpAuxRx2/ScalerDpAuxRx2Interface_User.h>
#include <DpHdcp14Tx/ScalerDpHdcp14TxInterface_User.h>
#include <DpHdcp2Tx/ScalerDpHdcp2TxInterface_User.h>
#include <DpMstRx/ScalerDpMstRxInterface_User.h>
#include <DpMacMstToSst/ScalerDpMacMstToSstInterface_User.h>
#include <DpAuxTx/ScalerDpAuxTxInterface_User.h>
#include <DpMacTx/ScalerDpMacTxInterface_User.h>
#include <DpPhyTx/ScalerDpPhyTxInterface_User.h>
#include <DpMstTx/ScalerDpMstTxInterface_User.h>
#include <Drr/ScalerDrrInterface_User.h>
#include <DscDecoder/ScalerDscDecoderInterface_User.h>
#include <FmtCnv/ScalerFmtCnvInterface_User.h>
#include <FRC/ScalerFRCInterface_User.h>
#include <ImgCmp/ScalerImgCmpInterface_User.h>
#include <GDIPhyRx/ScalerGDIPhyRxInterface_User.h>
#include <GDIPhyRx0/ScalerGDIPhyRx0Interface_User.h>
#include <GDIPhyRx1/ScalerGDIPhyRx1Interface_User.h>
#include <GDIPhyRx2/ScalerGDIPhyRx2Interface_User.h>
#include <GDIPhyRx3/ScalerGDIPhyRx3Interface_User.h>
#include <GDIPhyRx4/ScalerGDIPhyRx4Interface_User.h>
#include <GDIPhyRx5/ScalerGDIPhyRx5Interface_User.h>
#include <GDIPhyDpTx/ScalerGDIPhyDpTxInterface_User.h>
#include <Gosd/ScalerGosdInterface_User.h>
#include <Gosd/ScalerGosdDecompressInterface_User.h>
#include <Gosd/ScalerGosdSeInterface_User.h>
#include <Gosd/ScalerGosdDispOsdInterface_User.h>
#include <Global/ScalerGlobalInterface_User.h>
#include <IDomain/ScalerIDomainInterface_User.h>
#include <IOSC/ScalerIOSCInterface_User.h>
#include <LDO/ScalerLDOInterface_User.h>
#include <Mbr/ScalerMbrInterface_User.h>
#include <Mcu/ScalerMcuInterface_User.h>
#include <Measure/ScalerMeasureInterface_User.h>
#include <Sync/ScalerSyncInterface_User.h>
#include <MDomain/ScalerMDomainInterface_User.h>
#include <Memory/ScalerMemoryInterface_User.h>
#include <NVRam/ScalerNVRamInterface_User.h>
#include <OD/ScalerODInterface_User.h>
#include <Osd/ScalerOsdInterface_User.h>
#include <OsdSubBlending/ScalerOsdSubBlendingInterface_User.h>
#include <Pinshare/ScalerPinshareInterface_User.h>
#include <PLL/ScalerPLLInterface_User.h>
#include <Power/ScalerPowerInterface_User.h>
#include <Reg/ScalerRegInterface_User.h>
#include <Rotation/ScalerRotationInterface_User.h>
#include <Scaling/ScalerScalingInterface_User.h>
#include <Spi/ScalerSpiInterface_User.h>
#include <VgaSyncProc/ScalerVgaSyncProcInterface_User.h>
#include <Tcon/ScalerTconInterface_User.h>
#include <ThermalSensor/ScalerThermalSensorInterface_User.h>
#include <TimerFunction/ScalerTimerFunctionInterface_User.h>
#include <TmdsMacRx/ScalerTmdsMacRxInterface_User.h>
#include <TmdsPhyRx/ScalerTmdsPhyRxInterface_User.h>
#include <TmdsMacRx3/ScalerTmdsMacRx3Interface_User.h>
#include <TmdsMacRx4/ScalerTmdsMacRx4Interface_User.h>
#include <HdmiFrlMacRx/ScalerHdmiFrlMacRxInterface_User.h>
#include <HdmiFrlMacRx3/ScalerHdmiFrlMacRx3Interface_User.h>
#include <HdmiFrlMacRx4/ScalerHdmiFrlMacRx4Interface_User.h>
#include <TmdsPhyRx3/ScalerTmdsPhyRx3Interface_User.h>
#include <TmdsPhyRx4/ScalerTmdsPhyRx4Interface_User.h>
#include <TypeC/ScalerTypeCInterface_User.h>
#include <TypeCAdc/ScalerTypeCAdcInterface_User.h>
#include <TypeC0Cc/ScalerTypeC0CcInterface_User.h>
#include <TypeC0Pd/ScalerTypeC0PdInterface_User.h>
#include <TypeC0Pmic/ScalerTypeC0PmicInterface_User.h>
#include <TypeC1Cc/ScalerTypeC1CcInterface_User.h>
#include <TypeC1Pd/ScalerTypeC1PdInterface_User.h>
#include <TypeC1Pmic/ScalerTypeC1PmicInterface_User.h>
#include <TypeCTcpm/ScalerTypeCTcpmInterface_User.h>
#include <Usb2Mux/ScalerUsb2MuxInterface_User.h>
#include <Usb3RepeaterMac/ScalerUsb3RepeaterMacInterface_User.h>
#include <Usb3RedriverMac0/ScalerUsb3RedriverMac0Interface_User.h>
#include <Usb3RedriverMac1/ScalerUsb3RedriverMac1Interface_User.h>
#include <Usb3RetimerMac0/ScalerUsb3RetimerMac0Interface_User.h>
#include <Usb3RetimerMac1/ScalerUsb3RetimerMac1Interface_User.h>
#include <Usb3RepeaterPhy/ScalerUsb3RepeaterPhyInterface_User.h>
#include <Usb3RetimerUfpPhy0/ScalerUsb3RetimerUfpPhy0Interface_User.h>
#include <Usb3RetimerDfpPhy0/ScalerUsb3RetimerDfpPhy0Interface_User.h>
#include <Usb3RetimerUfpPhy1/ScalerUsb3RetimerUfpPhy1Interface_User.h>
#include <Usb3RetimerDfpPhy1/ScalerUsb3RetimerDfpPhy1Interface_User.h>
#include <UsbBillboard/ScalerUsbBillboardInterface_User.h>
#include <UsbU2Host/ScalerUsbU2HostInterface_User.h>
#include <UsbFileSys/ScalerUsbFileSysInterface_User.h>
#include <Vga/ScalerVgaInterface_User.h>
#include <Vgip/ScalerVgipInterface_User.h>
#include <IR/ScalerIRInterface_User.h>
#include <TmdsHdcp2Rx3/ScalerTmdsHdcp2Rx3Interface_User.h>
#include <TmdsHdcp2Rx4/ScalerTmdsHdcp2Rx4Interface_User.h>

#include <CpuSync/ScalerCpuSyncInterface_User.h>
#include <CpuCtrl/ScalerCpuCtrlInterface_User.h>

#include <FlashMode/ScalerFlashModeInterface_User.h>

#include <BW32/ScalerBW32Interface_User.h>
#include <BusSb2/ScalerBusSb2Interface_User.h>
#include <BusScpuWrap/ScalerBusScpuWrapInterface_User.h>
#include <CpuHal/ScalerCpuHalInterface_User.h>
#include <ScpuSync/ScalerScpuSyncInterface_User.h>
#include <GlobalCtrl/ScalerGlobalCtrlInterface_User.h>
#include <MiscCtrl/ScalerMiscCtrlInterface_User.h>
#include <RBusToDdr/ScalerRBusToDdrInterface_User.h>
#include <SysTick/ScalerSysTickInterface_User.h>
#include <Timer/ScalerTimerInterface_User.h>
#include <Util/ScalerUtilInterface_User.h>
#include <Wdt/ScalerWdtInterface_User.h>
#include <OTP/ScalerOTPInterface_User.h>
#include <DualBank/ScalerDualBankInterface_User.h>
#include <FwInfo/ScalerFwInfoInterface_User.h>
#include <FwCheck/ScalerFwCheckInterface_User.h>
#include <FwUpdate/ScalerFwUpdateInterface_User.h>
#include <FwUpdateBackground/ScalerFwUpdateBackgroundInterface_User.h>
#include <FwUpdateForeground/ScalerFwUpdateForegroundInterface_User.h>

#endif // End of #ifndef __SCALER_FUNCTION_INTERFACE_USER_H__

