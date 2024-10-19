//--------------------------Group 1------------------------
// {SLPC, SHPC, STA_SUGPIO_C, TOR, FTPC, FD10}
//---------------------------------------------------------
#if(_HW_HW_IIC_GEN == _HW_IIC_GEN_1)
    // User _HW_IIC_LOW_SPEED_100K PARAMETERS
    {
        // _EXT_XTAL
#if(_EXT_XTAL == _XTAL14318K)
        {0x26, 0x22, 0x2A, 0x47, 0x02, 0x01},

#elif(_EXT_XTAL == _XTAL27000K)
        {0x30, 0x2C, 0x36, 0x47, 0x03, 0x02},
#endif
        // IOSC_CLK(28000K)
        {0x2F, 0x2F, 0x38, 0x47, 0x03, 0x02},
    },

    // User _HW_IIC_HIGH_SPEED_400K PARAMETERS
    {
        // _EXT_XTAL
#if(_EXT_XTAL == _XTAL14318K)
        {0x0C, 0x04, 0x06, 0x23, 0x02, 0x01},

#elif(_EXT_XTAL == _XTAL27000K)
        {0x0D, 0x05, 0x09, 0x23, 0x03, 0x02},
#endif
        // IOSC_CLK(28000K)
        {0x0E, 0x06, 0x09, 0x23, 0x03, 0x02},
    },

//--------------------------Group 2------------------------
// {SLPC, SHPC, STA_SUGPIO_C, TOR, FTPC, FD10, THD_STA_C}
//---------------------------------------------------------
#elif(_HW_HW_IIC_GEN == _HW_IIC_GEN_2)
    // User _HW_IIC_LOW_SPEED_100K PARAMETERS
    {
        // _EXT_XTAL
#if(_EXT_XTAL == _XTAL14318K)
        {0x26, 0x22, 0x2A, 0x47, 0x02, 0x01, 0x2B},

#elif(_EXT_XTAL == _XTAL27000K)
        {0x30, 0x2C, 0x36, 0x47, 0x03, 0x02, 0x36},
#endif
        // IOSC_CLK(28000K)
        {0x2F, 0x2F, 0x38, 0x47, 0x03, 0x02, 0x38},
    },

    // User _HW_IIC_HIGH_SPEED_400K PARAMETERS
    {
        // _EXT_XTAL
#if(_EXT_XTAL == _XTAL14318K)
        {0x0C, 0x04, 0x06, 0x23, 0x02, 0x01, 0x09},

#elif(_EXT_XTAL == _XTAL27000K)
        {0x0D, 0x05, 0x09, 0x23, 0x03, 0x02, 0x0C},
#endif
        // IOSC_CLK(28000K)
        {0x0E, 0x06, 0x09, 0x23, 0x03, 0x02, 0x0C},
    },
#endif // End of #if(_HW_HW_IIC_GEN == _HW_IIC_GEN_1)

//--------------------------Group 3 And Add More-----------

