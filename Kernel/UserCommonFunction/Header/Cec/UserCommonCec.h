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
// ID Code      : UserCommonCec.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __USER_COMMON_CEC_H__
#define __USER_COMMON_CEC_H__

#if(_HDMI_CEC_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_HDMI_CEC_KERNEL_HAL_SUPPORT == _ON)
#define _CEC_SINK_AUDIO_DESCRIPTOR_MAX_LENGTH               30 // CTA defined only up to 10 Short Audio Descriptors in Audio Data Block
#define _CEC_WAIT_FOR_AUDIO_DESCRIPTOR_REPLY_DURATION       3000

#define _CEC_OSD_NAME_MAX_LENGTH                            14

#define _CEC_REQUEST_TO_DEVICE_QUEUE_SIZE                   10

#define GET_CEC_REQUEST_TO_DEVICE()                         (g_stCecServiceInfo.pucCecRequestToDevice[0])
#define SET_CEC_REQUEST_TO_DEVICE(x)                        {\
                                                                if(((x) != _CEC_OPCODE_NONE) && (g_stCecServiceInfo.ucCecRequestToDeviceQueueCnt < sizeof(g_stCecServiceInfo.pucCecRequestToDevice)))\
                                                                {\
                                                                    g_stCecServiceInfo.pucCecRequestToDevice[g_stCecServiceInfo.ucCecRequestToDeviceQueueCnt++] = (x);\
                                                                }\
                                                                else\
                                                                {\
                                                                    DebugMessageCEC("[CEC] Tx Message Send Queue is Full!", (x));\
                                                                }\
                                                            }

#define CLR_CEC_REQUEST_TO_DEVICE()                         {\
                                                                g_stCecServiceInfo.ucCecRequestToDeviceQueueCnt = 0;\
                                                                memset(g_stCecServiceInfo.pucCecRequestToDevice, _CEC_OPCODE_NONE, sizeof(g_stCecServiceInfo.pucCecRequestToDevice));\
                                                            }

#define GET_CEC_REQUEST_TO_DEVICE_QUEUE_COUNT()             (g_stCecServiceInfo.ucCecRequestToDeviceQueueCnt)
#define CLR_CEC_REQUEST_TO_DEVICE_QUEUE()                   {\
                                                                if(g_stCecServiceInfo.ucCecRequestToDeviceQueueCnt > 0)\
                                                                {\
                                                                    g_stCecServiceInfo.ucCecRequestToDeviceQueueCnt--;\
                                                                    memmove(&g_stCecServiceInfo.pucCecRequestToDevice[0], &g_stCecServiceInfo.pucCecRequestToDevice[1], g_stCecServiceInfo.ucCecRequestToDeviceQueueCnt);\
                                                                }\
                                                                memset(&g_stCecServiceInfo.pucCecRequestToDevice[g_stCecServiceInfo.ucCecRequestToDeviceQueueCnt], _CEC_OPCODE_NONE, sizeof(g_stCecServiceInfo.pucCecRequestToDevice) - g_stCecServiceInfo.ucCecRequestToDeviceQueueCnt);\
                                                            }

#define GET_CEC_DEVICE_LOGICAL_ADDR_BY_PORT(x)              (g_stCecServiceInfo.pucCecDeviceLogicalAddr[x])
#define SET_CEC_DEVICE_LOGICAL_ADDR_BY_PORT(x, y)           (g_stCecServiceInfo.pucCecDeviceLogicalAddr[x] = (y))
#define CLR_CEC_DEVICE_LOGICAL_ADDR_BY_PORT()               (memset(g_stCecServiceInfo.pucCecDeviceLogicalAddr, 0, sizeof(g_stCecServiceInfo.pucCecDeviceLogicalAddr)))

#define GET_CEC_REQUEST_DEVICE_OSD_NAME_BY_PORT(x)          ((g_stCecServiceInfo.bNoneCecRequestOsdName & (1 << (x))) >> (x))
#define SET_CEC_REQUEST_DEVICE_OSD_NAME_BY_PORT(x, y)       (g_stCecServiceInfo.bNoneCecRequestOsdName = ((g_stCecServiceInfo.bNoneCecRequestOsdName & (~(1 << (x)))) | ((y) << (x))))
#define CLR_CEC_REQUEST_DEVICE_OSD_NAME_BY_PORT()           (g_stCecServiceInfo.bNoneCecRequestOsdName = 0)

#define GET_CEC_DEVICE_OSD_NAME_RECEIVED_BY_PORT(x)         ((g_stCecServiceInfo.bNoneCecOsdNameReceived & (1 << (x))) >> (x))
#define SET_CEC_DEVICE_OSD_NAME_RECEIVED_BY_PORT(x, y)      (g_stCecServiceInfo.bNoneCecOsdNameReceived = ((g_stCecServiceInfo.bNoneCecOsdNameReceived & (~(1 << (x)))) | ((y) << (x))))
#define CLR_CEC_DEVICE_OSD_NAME_RECEIVED_BY_PORT()          (g_stCecServiceInfo.bNoneCecOsdNameReceived = 0)

#define GET_CEC_LOGICAL_ADDR_POLLING_CONTINUE()             (g_stCecServiceInfo.b1CecLAPollingContinue)
#define SET_CEC_LOGICAL_ADDR_POLLING_CONTINUE()             (g_stCecServiceInfo.b1CecLAPollingContinue = _TRUE)
#define CLR_CEC_LOGICAL_ADDR_POLLING_CONTINUE()             (g_stCecServiceInfo.b1CecLAPollingContinue = _FALSE)

#define GET_CEC_PHYSICAL_ADDR_REPORTING()                   (g_stCecServiceInfo.b1CecPAReport)
#define SET_CEC_PHYSICAL_ADDR_REPORTING()                   (g_stCecServiceInfo.b1CecPAReport = _TRUE)
#define CLR_CEC_PHYSICAL_ADDR_REPORTING()                   (g_stCecServiceInfo.b1CecPAReport = _FALSE)

#define GET_CEC_PHYSICAL_ADDR_RETRY_TIMEOUT()               (g_stCecServiceInfo.b1CecPARetryTimeout)
#define SET_CEC_PHYSICAL_ADDR_RETRY_TIMEOUT()               (g_stCecServiceInfo.b1CecPARetryTimeout = _TRUE)
#define CLR_CEC_PHYSICAL_ADDR_RETRY_TIMEOUT()               (g_stCecServiceInfo.b1CecPARetryTimeout = _FALSE)

#define GET_CEC_PHYSICAL_ADDR_REPORTING_RETRY_COUNT()       (g_stCecServiceInfo.b2CecPARetryCount)
#define SET_CEC_PHYSICAL_ADDR_REPORTING_RETRY_COUNT(x)      (g_stCecServiceInfo.b2CecPARetryCount = (x))
#define CLR_CEC_PHYSICAL_ADDR_REPORTING_RETRY_COUNT()       (g_stCecServiceInfo.b2CecPARetryCount = 0)

#define GET_CEC_LA_POLLING_BY_SOURCE_POWER()                (g_stCecServiceInfo.b1CecLAPollingStartBy5V)
#define SET_CEC_LA_POLLING_BY_SOURCE_POWER()                (g_stCecServiceInfo.b1CecLAPollingStartBy5V = _TRUE)
#define CLR_CEC_LA_POLLING_BY_SOURCE_POWER()                (g_stCecServiceInfo.b1CecLAPollingStartBy5V = _FALSE)

#define GET_CEC_LOGICAL_ADDR_POLLING_COUNT()                (g_stCecServiceInfo.b4CecLAPollingCount)
#define SET_CEC_LOGICAL_ADDR_POLLING_COUNT(x)               (g_stCecServiceInfo.b4CecLAPollingCount = (x))
#define CLR_CEC_LOGICAL_ADDR_POLLING_COUNT()                (g_stCecServiceInfo.b4CecLAPollingCount = 0)

#define GET_CEC_LOGICAL_ADDR_POLLING_START()                (g_stCecServiceInfo.b1CecLAPollingStart)
#define SET_CEC_LOGICAL_ADDR_POLLING_START()                (g_stCecServiceInfo.b1CecLAPollingStart = _TRUE)
#define CLR_CEC_LOGICAL_ADDR_POLLING_START()                (g_stCecServiceInfo.b1CecLAPollingStart = _FALSE)

#define GET_CEC_LOGICAL_ADDR_POLLING_STATE()                (g_stCecServiceInfo.b2CecTxLAPollingState)
#define SET_CEC_LOGICAL_ADDR_POLLING_STATE(x)               (g_stCecServiceInfo.b2CecTxLAPollingState = (x))
#define CLR_CEC_LOGICAL_ADDR_POLLING_STATE()                (g_stCecServiceInfo.b2CecTxLAPollingState = _CEC_TX_LA_POLLING_STATE_NONE)

#define GET_CEC_OSD_NAME_BUFFER_BY_EXIST_LA(x)              (g_stCecServiceInfo.ppucCecOsdName[x])
#define SET_CEC_OSD_NAME_BUFFER_BY_EXIST_LA(x, y, z)        (memcpy(g_stCecServiceInfo.ppucCecOsdName[x], (y), (((z) < _CEC_OSD_NAME_MAX_LENGTH) ? (z) : _CEC_OSD_NAME_MAX_LENGTH)))
#define CLR_CEC_OSD_NAME_BUFFER_BY_EXIST_LA(x)              (memset(g_stCecServiceInfo.ppucCecOsdName[x], 0, _CEC_OSD_NAME_MAX_LENGTH))
#define CLR_CEC_OSD_NAME_BUFFER()                           {\
                                                                BYTE ucArrayIndex = 0;\
                                                                for(ucArrayIndex = 0; ucArrayIndex < _HDMI_CEC_PORT_AMOUNT; ucArrayIndex++)\
                                                                {\
                                                                    memset(g_stCecServiceInfo.ppucCecOsdName[ucArrayIndex], 0, _CEC_OSD_NAME_MAX_LENGTH);\
                                                                }\
                                                            }

#define REBUILD_CEC_TOPOLOGY()                              {\
                                                                SET_CEC_LOGICAL_ADDR_POLLING_START();\
                                                                SET_CEC_LOGICAL_ADDR_POLLING_COUNT(0);\
                                                                CLR_CEC_DEVICE_LOGICAL_ADDR_BY_PORT();\
                                                                CLR_CEC_REQUEST_DEVICE_OSD_NAME_BY_PORT();\
                                                                CLR_CEC_DEVICE_OSD_NAME_RECEIVED_BY_PORT();\
                                                                CLR_CEC_OSD_NAME_BUFFER();\
                                                            }

#define DELETE_CEC_UNPLUGGED_DEVICE(x)                      {\
                                                                SET_CEC_DEVICE_LOGICAL_ADDR_BY_PORT((x), 0);\
                                                                SET_CEC_REQUEST_DEVICE_OSD_NAME_BY_PORT((x), _FALSE);\
                                                                SET_CEC_DEVICE_OSD_NAME_RECEIVED_BY_PORT((x), _FALSE);\
                                                                CLR_CEC_OSD_NAME_BUFFER_BY_EXIST_LA(x);\
                                                            }

#define GET_CEC_POLLING_AUDIO_DESCRIPTOR_START()            (g_stCecServiceInfo.b1CecPollingAudioDescriptorStart)
#define SET_CEC_POLLING_AUDIO_DESCRIPTOR_START()            (g_stCecServiceInfo.b1CecPollingAudioDescriptorStart = _TRUE)
#define CLR_CEC_POLLING_AUDIO_DESCRIPTOR_START()            (g_stCecServiceInfo.b1CecPollingAudioDescriptorStart = _FALSE)

#define GET_CEC_SINK_AUDIO_DESCRIPTOR_RECEIVED()            (g_stCecServiceInfo.b1CecSinkAudioDescriptorReceived)
#define SET_CEC_SINK_AUDIO_DESCRIPTOR_RECEIVED()            (g_stCecServiceInfo.b1CecSinkAudioDescriptorReceived = _TRUE)
#define CLR_CEC_SINK_AUDIO_DESCRIPTOR_RECEIVED()            (g_stCecServiceInfo.b1CecSinkAudioDescriptorReceived = _FALSE)

#define GET_CEC_POLLING_AUDIO_DESCRIPTOR_COUNT()            (g_stCecServiceInfo.b3CecPollingAudioDescriptorCnt)
#define SET_CEC_POLLING_AUDIO_DESCRIPTOR_COUNT(x)           (g_stCecServiceInfo.b3CecPollingAudioDescriptorCnt = (x))
#define CLR_CEC_POLLING_AUDIO_DESCRIPTOR_COUNT()            (g_stCecServiceInfo.b3CecPollingAudioDescriptorCnt = 0)

#define GET_CEC_WAIT_FOR_AUDIO_DESCRIPTOR_REPLY()           (g_stCecServiceInfo.b1CecWaitForAudioDescriptor)
#define SET_CEC_WAIT_FOR_AUDIO_DESCRIPTOR_REPLY()           (g_stCecServiceInfo.b1CecWaitForAudioDescriptor = _TRUE)
#define CLR_CEC_WAIT_FOR_AUDIO_DESCRIPTOR_REPLY()           (g_stCecServiceInfo.b1CecWaitForAudioDescriptor = _FALSE)

#define GET_CEC_WAIT_FOR_AUDIO_DESCRIPTOR_REPLY_TIMEOUT()   (g_stCecServiceInfo.b1CecWaitForAudioDescriptorTimeout)
#define SET_CEC_WAIT_FOR_AUDIO_DESCRIPTOR_REPLY_TIMEOUT()   (g_stCecServiceInfo.b1CecWaitForAudioDescriptorTimeout = _TRUE)
#define CLR_CEC_WAIT_FOR_AUDIO_DESCRIPTOR_REPLY_TIMEOUT()   (g_stCecServiceInfo.b1CecWaitForAudioDescriptorTimeout = _FALSE)

#define GET_CEC_SINK_AUDIO_DESCRIPTOR_LENGTH()              (g_stCecServiceInfo.ucCecShortAudioDescriptorLength)
#define GET_CEC_SINK_AUDIO_DESCRIPTOR_BUFFER(x)             (g_stCecServiceInfo.pucCecShortAudioDescriptor[(x)])
#define SET_CEC_SINK_AUDIO_DESCRIPTOR_BUFFER(x)             {\
                                                                if(g_stCecServiceInfo.ucCecShortAudioDescriptorLength < _CEC_SINK_AUDIO_DESCRIPTOR_MAX_LENGTH)\
                                                                {\
                                                                    g_stCecServiceInfo.pucCecShortAudioDescriptor[g_stCecServiceInfo.ucCecShortAudioDescriptorLength++] = (x);\
                                                                }\
                                                                else\
                                                                {\
                                                                    DebugMessageCEC("[CEC] Over Audio Descriptor Buffer Size!!!", (x));\
                                                                }\
                                                            }
#define CLR_CEC_SINK_AUDIO_DESCRIPTOR_BUFFER()              {\
                                                                g_stCecServiceInfo.ucCecShortAudioDescriptorLength = 0;\
                                                                memset(g_stCecServiceInfo.pucCecShortAudioDescriptor, 0, sizeof(g_stCecServiceInfo.pucCecShortAudioDescriptor));\
                                                            }

#if(_HDMI_SUPPORT == _ON)
#define GET_CEC_D0_HDMI_SOURCE_POWER()                      (g_stCecSrcPowerInfo.enumD0SourcePower)
#define SET_CEC_D0_HDMI_SOURCE_POWER(x)                     (g_stCecSrcPowerInfo.enumD0SourcePower = (x))

#define GET_CEC_D1_HDMI_SOURCE_POWER()                      (g_stCecSrcPowerInfo.enumD1SourcePower)
#define SET_CEC_D1_HDMI_SOURCE_POWER(x)                     (g_stCecSrcPowerInfo.enumD1SourcePower = (x))

#define GET_CEC_D2_HDMI_SOURCE_POWER()                      (g_stCecSrcPowerInfo.enumD2SourcePower)
#define SET_CEC_D2_HDMI_SOURCE_POWER(x)                     (g_stCecSrcPowerInfo.enumD2SourcePower = (x))

#define GET_CEC_D3_HDMI_SOURCE_POWER()                      (g_stCecSrcPowerInfo.enumD3SourcePower)
#define SET_CEC_D3_HDMI_SOURCE_POWER(x)                     (g_stCecSrcPowerInfo.enumD3SourcePower = (x))

#define GET_CEC_D4_HDMI_SOURCE_POWER()                      (g_stCecSrcPowerInfo.enumD4SourcePower)
#define SET_CEC_D4_HDMI_SOURCE_POWER(x)                     (g_stCecSrcPowerInfo.enumD4SourcePower = (x))

#define GET_CEC_D5_HDMI_SOURCE_POWER()                      (g_stCecSrcPowerInfo.enumD5SourcePower)
#define SET_CEC_D5_HDMI_SOURCE_POWER(x)                     (g_stCecSrcPowerInfo.enumD5SourcePower = (x))
#endif // End of #if(_HDMI_SUPPORT == _ON)
#endif // End of #if(_HDMI_CEC_KERNEL_HAL_SUPPORT == _ON)


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
#if(_HDMI_CEC_KERNEL_HAL_SUPPORT == _ON)
typedef struct
{
    BYTE b1CecLAPollingContinue                  : 1;
    BYTE b1CecPAReport                           : 1;
    BYTE b1CecLAPollingStart                     : 1;
    BYTE b4CecLAPollingCount                     : 4;
    BYTE b2CecPARetryCount                       : 2;
    BYTE b1CecLAPollingStartBy5V                 : 1;
    BYTE b1CecPARetryTimeout                     : 1;
    BYTE b2CecTxLAPollingState                   : 2;
#if(_AUDIO_ARC_SUPPORT == _ON)
    BYTE b1CecPollingAudioDescriptorStart        : 1;
    BYTE b1CecSinkAudioDescriptorReceived         : 1;
    BYTE b3CecPollingAudioDescriptorCnt          : 3;
    BYTE b1CecWaitForAudioDescriptor             : 1;
    BYTE b1CecWaitForAudioDescriptorTimeout      : 1;
    BYTE ucCecShortAudioDescriptorLength;
    BYTE pucCecShortAudioDescriptor[_CEC_SINK_AUDIO_DESCRIPTOR_MAX_LENGTH];
#endif
    BYTE bNoneCecRequestOsdName                  : _HDMI_CEC_PORT_AMOUNT;
    BYTE bNoneCecOsdNameReceived                 : _HDMI_CEC_PORT_AMOUNT;
    BYTE pucCecRequestToDevice[_CEC_REQUEST_TO_DEVICE_QUEUE_SIZE];
    BYTE ucCecRequestToDeviceQueueCnt;
    BYTE pucCecDeviceLogicalAddr[_HDMI_CEC_PORT_AMOUNT];
    BYTE ppucCecOsdName[_HDMI_CEC_PORT_AMOUNT][_CEC_OSD_NAME_MAX_LENGTH];
}StructCecServicelInfo;

#if(_HDMI_SUPPORT == _ON)
typedef struct
{
    EnumUserHdmi5vStatus enumD0SourcePower;
    EnumUserHdmi5vStatus enumD1SourcePower;
    EnumUserHdmi5vStatus enumD2SourcePower;
    EnumUserHdmi5vStatus enumD3SourcePower;
    EnumUserHdmi5vStatus enumD4SourcePower;
    EnumUserHdmi5vStatus enumD5SourcePower;
}StructCecSrc5VPinInfo;
#endif // End of #if(_HDMI_SUPPORT == _ON)
#endif // End of #if(_HDMI_CEC_KERNEL_HAL_SUPPORT == _ON)


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void UserCommonCecRxPopQueueMsg(void);

#if(_HDMI_CEC_KERNEL_HAL_SUPPORT == _ON)
#if(_HDMI_SUPPORT == _ON)
extern void UserCommonCecHalSetSourcePowerStatus(EnumInputPort enumInputPort, EnumUserHdmi5vStatus enumHdmi5vStatus);
extern EnumUserHdmi5vStatus UserCommonCecHalGetSourcePowerStatus(EnumInputPort enumInputPort);
#endif // End of #if(_HDMI_SUPPORT == _ON)
#endif // End of #if(_HDMI_CEC_KERNEL_HAL_SUPPORT == _ON)
#endif // End of #if(_HDMI_CEC_SUPPORT == _ON)

#endif // End of #ifndef __USER_COMMON_CEC_H__