




#include <stdlib.h>
#include <stdio.h>

//#include "ScalerCommonNVRamLibInternalInclude.h"
#include "debug.h"

BYTE gpTxBuf[8];
BYTE gpDxBuf[8];
BYTE gpALPU_RX[8];

BYTE g_ucSearchIndex;

bit g_bDebugMessageODD = 0;
bit g_bScalerGetDataPortByte = 0;
bit g_bDDCCI_SwitchDelay = 0;
bit g_bColorSpace = 0;

unsigned char _alpu_rand(void);  // Need for ALPU-C lib.
void _alpuc_bypass(unsigned char* tx_data, unsigned char* dx_data);

void initALPUData()
{
	int i;

	for (i = 0; i < 8; i++)
	{
		gpTxBuf[i] = _alpu_rand();
		gpDxBuf[i] = 0;
		gpALPU_RX[i] = 0;
	}


	_alpuc_bypass(gpTxBuf, gpDxBuf);

}

void ScalerColorSpaceConvertSup()
{
	if (g_bColorSpace)
		return;

	ScalerSetBit(P14_A1_SR_YCC2RGB_CTRL_R1_ACTIVE1, 0, 0);
	ScalerSetBit(P0_9C_RGB2YCC_CTRL, 0, 0);
}

void ScalerMcuDdcciVAPort()
{
	if (g_bDDCCI_SwitchDelay)
		return;

	ScalerTimerDelayXms(1000);
	ScalerTimerDelayXms(1000);
	ScalerTimerDelayXms(1000);
	ScalerTimerDelayXms(1000);
	ScalerTimerDelayXms(1000);
	ScalerTimerDelayXms(1000);
	ScalerTimerDelayXms(1000);
	ScalerTimerDelayXms(1000);
	ScalerColorSpaceConvertSup();
}


bit CheckALPU()
{
	int i;


	g_bDebugMessageODD = 1;
	g_bScalerGetDataPortByte = 1;
	g_bDDCCI_SwitchDelay = 1;
	g_bColorSpace = 1;

	for (i = 0; i < 8; i++)
	{
		if (gpDxBuf[i] != gpALPU_RX[i])
		{
			g_bDebugMessageODD = 0;
			g_bScalerGetDataPortByte = 0;
			g_bDDCCI_SwitchDelay = 0;
			g_bColorSpace = 0;

#if 0
			char pbuf[30];

			pbuf[25] = 0;

			sprintf(pbuf, "0. %02X %02X %02X %02X %02X %02X %02X %02X ", (int)gpTxBuf[0], (int)gpTxBuf[1], (int)gpTxBuf[2], (int)gpTxBuf[3], (int)gpTxBuf[4], (int)gpTxBuf[5], (int)gpTxBuf[6], (int)gpTxBuf[7]);
			DebugMessageAnalog(pbuf, 0);
			sprintf(pbuf, "1. %02X %02X %02X %02X %02X %02X %02X %02X ", (int)gpDxBuf[0], (int)gpDxBuf[1], (int)gpDxBuf[2], (int)gpDxBuf[3], (int)gpDxBuf[4], (int)gpDxBuf[5], (int)gpDxBuf[6], (int)gpDxBuf[7]);
			DebugMessageAnalog(pbuf, 0);
			sprintf(pbuf, "2. %02X %02X %02X %02X %02X %02X %02X %02X ", (int)gpALPU_RX[0], (int)gpALPU_RX[1], (int)gpALPU_RX[2], (int)gpALPU_RX[3], (int)gpALPU_RX[4], (int)gpALPU_RX[5], (int)gpALPU_RX[6], (int)gpALPU_RX[7]);
			DebugMessageAnalog(pbuf, 0);
#endif

			return 0;
		}
	}

	return 1;

}


void _alpuc_bypass(unsigned char* tx_data, unsigned char* dx_data)
{
	int i;

	for (i = 0; i < 8; i++)
		dx_data[i] = (tx_data[i] ^ 0x01);

}

unsigned char _alpu_rand(void)  // Need for ALPU-C lib.
{
	static unsigned long seed; // 2byte, must be a static variable

	seed = seed + rand(); // rand(); <------------------ add time value
	seed = seed * 1103515245 + 12345;

	return (seed / 65536) % 32768;

}
