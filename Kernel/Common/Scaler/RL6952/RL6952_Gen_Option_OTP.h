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
// ID Code      : RL6952_Gen_Option_OTP.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------


////////
// HW //
////////

//-------------------------------------------------
// OTP Mapping Data
//-------------------------------------------------
#if(_HW_FUSE_TYPE == _OTPFUSE_TYPE)

// OTPfuse Total Bank Number
#define _HW_OTPFUSE_TOTAL_BANK_NUM                     1

// OTPfuse IP Start Address
#define _HW_OTPFUSE_CHECK_EMPTY_STR                    1852

#define _HW_OTPFUSE_HDCP14_RXKEYBKSV_STR               0
#define _HW_OTPFUSE_HDCP14_RXKEY_STR                   5
#define _HW_OTPFUSE_HDCP14_TXKEYBKSV_STR               328
#define _HW_OTPFUSE_HDCP14_TXKEY_STR                   333
#define _HW_OTPFUSE_HDCP22_RXKEY_STR                   656
#define _HW_OTPFUSE_HDCP22_RXKEY_CERTRX_STR            656
#define _HW_OTPFUSE_HDCP22_RXKEY_KPRIV_STR             1178
#define _HW_OTPFUSE_HDCP22_RXKEY_RRMODN_STR            1498
#define _HW_OTPFUSE_HDCP22_RXKEY_NPINV_STR             1626
#define _HW_OTPFUSE_HDCP22_RXKEY_DKEY_STR              1630
#define _HW_OTPFUSE_HDCP22_RXKEY_LCKEY_STR             1758
#define _HW_OTPFUSE_TYPE_C_0_TRIMDATA_STR              1788
#define _HW_OTPFUSE_TYPE_C_0_1M_TRIMDATA_STR           1808
#define _HW_OTPFUSE_TYPE_C_1_TRIMDATA_STR              1820
#define _HW_OTPFUSE_TYPE_C_1_1M_TRIMDATA_STR           1840
#define _HW_OTPFUSE_LVDS_AB_IBHN_TRIMDATA_STR          1876
#define _HW_OTPFUSE_DDC_CONFIG_STR                     1880
#define _HW_OTPFUSE_IOSC_TRIMDATA_STR                  1881
#define _HW_OTPFUSE_HDMI_RETIMER_STR                   1885
#define _HW_OTPFUSE_M2PLL_CONFIG_STR                   1887
#define _HW_OTPFUSE_HDMI_TRIMDATA_STR                  1888
#define _HW_OTPFUSE_CEC1_CONFIG_STR                    1896
#define _HW_OTPFUSE_EMCU_CONFIG_STR                    1897
#define _HW_OTPFUSE_THERMAL_SENSOR_STR                 1898
#define _HW_OTPFUSE_SLP_MODE_STR                       1900
#define _HW_OTPFUSE_HDCP_LOCATION_STR                  1901
#define _HW_OTPFUSE_LVDS_CD_IBHN_TRIMDATA_STR          1919
#define _HW_OTPFUSE_LVDS_VCM_AB_TRIMDATA_STR           1920
#define _HW_OTPFUSE_LVDS_VCM_CD_TRIMDATA_STR           1921
#define _HW_OTPFUSE_AUDIO_CORNER_CONFIG_STR            1923
#define _HW_OTPFUSE_EARC_TRIMDATA_STR                  1924
#define _HW_OTPFUSE_TYPE_C_SARADC_TRIMDATA_STR         1928
#define _HW_OTPFUSE_MST_DPTX_IB_TRIMDATA_STR           1955
#define _HW_OTPFUSE_SINK_ASS_1M_TRIMDATA_STR           1960
#define _HW_OTPFUSE_FEATURE_CTRL_BYTE_STR              1966

// OTPfuse IP Length
#define _HW_OTPFUSE_CHECK_EMPTY_LEN                    1
#define _HW_OTPFUSE_HDCP14_RXKEY_LEN                   320
#define _HW_OTPFUSE_HDCP14_RXKEYBKSV_LEN               5
#define _HW_OTPFUSE_HDCP14_TXKEY_LEN                   320
#define _HW_OTPFUSE_HDCP14_TXKEYBKSV_LEN               5
#define _HW_OTPFUSE_HDCP22_RXKEY_LEN                   1118
#define _HW_OTPFUSE_HDCP22_RXKEY_CERTRX_LEN            0// confirm
#define _HW_OTPFUSE_HDCP22_RXKEY_KPRIV_LEN             0// confirm
#define _HW_OTPFUSE_HDCP22_RXKEY_RRMODN_LEN            0// confirm
#define _HW_OTPFUSE_HDCP22_RXKEY_NPINV_LEN             0// confirm
#define _HW_OTPFUSE_HDCP22_RXKEY_DKEY_LEN              0// confirm
#define _HW_OTPFUSE_HDCP22_RXKEY_LCKEY_LEN             0// confirm
#define _HW_OTPFUSE_TYPE_C_0_TRIMDATA_LEN              20
#define _HW_OTPFUSE_TYPE_C_0_1M_TRIMDATA_LEN           1
#define _HW_OTPFUSE_TYPE_C_1_TRIMDATA_LEN              20
#define _HW_OTPFUSE_TYPE_C_1_1M_TRIMDATA_LEN           1
#define _HW_OTPFUSE_LVDS_AB_IBHN_TRIMDATA_LEN          1
#define _HW_OTPFUSE_DDC_CONFIG_LEN                     1
#define _HW_OTPFUSE_IOSC_TRIMDATA_LEN                  1
#define _HW_OTPFUSE_HDMI_RETIMER_LEN                   2
#define _HW_OTPFUSE_M2PLL_CONFIG_LEN                   1
#define _HW_OTPFUSE_HDMI_TRIMDATA_LEN                  8
#define _HW_OTPFUSE_CEC1_CONFIG_LEN                    1
#define _HW_OTPFUSE_EMCU_CONFIG_LEN                    1
#define _HW_OTPFUSE_THERMAL_SENSOR_LEN                 2
#define _HW_OTPFUSE_SLP_MODE_LEN                       1
#define _HW_OTPFUSE_HDCP_LOCATION_LEN                  1
#define _HW_OTPFUSE_LVDS_CD_IBHN_TRIMDATA_LEN          1
#define _HW_OTPFUSE_LVDS_VCM_AB_TRIMDATA_LEN           1
#define _HW_OTPFUSE_LVDS_VCM_CD_TRIMDATA_LEN           1
#define _HW_OTPFUSE_AUDIO_CORNER_CONFIG_LEN            1
#define _HW_OTPFUSE_EARC_TRIMDATA_LEN                  3
#define _HW_OTPFUSE_TYPE_C_SARADC_TRIMDATA_LEN         8
#define _HW_OTPFUSE_MST_DPTX_IB_TRIMDATA_LEN           5
#define _HW_OTPFUSE_SINK_ASS_1M_TRIMDATA_LEN           4
#define _HW_OTPFUSE_FEATURE_CTRL_BYTE_LEN              2

#endif // End of #if(_HW_FUSE_TYPE == _OTPFUSE_TYPE)


////////
// FW //
////////


