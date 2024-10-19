////////////////////////////////////////////
//Local Contrast Performance Setting //////
////////////////////////////////////////////
#if((_HW_LOCAL_CONTRAST_GEN_SEL == _LOCAL_CONTRAST_GEN_3) || (_HW_LOCAL_CONTRAST_GEN_SEL == _LOCAL_CONTRAST_GEN_4))
4, _AUTOINC, 0x9F, 0x42,

// Tone-mapping grid setting
19, _AUTOINC, 0x20, 0x00, 0x8F, 0x00, 0xAF, 0x00, 0xCF, 0x01, 0x0F, 0x11, 0x8F, 0x22, 0x0F, 0x22, 0x4F, 0x22, 0x8F,

// Tone-mapping table
4, _AUTOINC, 0x31, 0x00,
4, _AUTOINC, 0x33, 0x00,
6, _AUTOINC, 0x35, 0x18, 0x00, 0x00,
6, _AUTOINC, 0x35, 0x18, 0x00, 0x61,
6, _AUTOINC, 0x35, 0x18, 0x00, 0xC1,
6, _AUTOINC, 0x35, 0x17, 0x01, 0x22,
6, _AUTOINC, 0x35, 0x18, 0x01, 0x82,
6, _AUTOINC, 0x35, 0x17, 0x01, 0xE2,
6, _AUTOINC, 0x35, 0x16, 0x02, 0x40,
6, _AUTOINC, 0x35, 0x16, 0x02, 0x9A,
6, _AUTOINC, 0x35, 0x15, 0x02, 0xF5,
6, _AUTOINC, 0x35, 0x15, 0x03, 0x4C,
6, _AUTOINC, 0x35, 0x15, 0x03, 0xA0,
6, _AUTOINC, 0x35, 0x13, 0x03, 0xF4,
6, _AUTOINC, 0x35, 0x13, 0x04, 0x43,
6, _AUTOINC, 0x35, 0x16, 0x04, 0x8F,
6, _AUTOINC, 0x35, 0x11, 0x04, 0xE9,
6, _AUTOINC, 0x35, 0x0E, 0x05, 0x2E,
6, _AUTOINC, 0x35, 0x0E, 0x05, 0x69,
6, _AUTOINC, 0x35, 0x0D, 0x05, 0xA2,
6, _AUTOINC, 0x35, 0x0F, 0x05, 0xD7,
6, _AUTOINC, 0x35, 0x0E, 0x06, 0x13,
6, _AUTOINC, 0x35, 0x0D, 0x06, 0x4D,
6, _AUTOINC, 0x35, 0x0C, 0x06, 0x83,
6, _AUTOINC, 0x35, 0x07, 0x06, 0xB4,
6, _AUTOINC, 0x35, 0x06, 0x06, 0xD0,
6, _AUTOINC, 0x35, 0x05, 0x06, 0xE9,
6, _AUTOINC, 0x35, 0x05, 0x07, 0x00,
6, _AUTOINC, 0x35, 0x08, 0x07, 0x17,
6, _AUTOINC, 0x35, 0x05, 0x07, 0x38,
6, _AUTOINC, 0x35, 0x07, 0x07, 0x4E,
6, _AUTOINC, 0x35, 0x07, 0x07, 0x65,
6, _AUTOINC, 0x35, 0x07, 0x07, 0x7C,
6, _AUTOINC, 0x35, 0x10, 0x07, 0x91,
4, _AUTOINC, 0x31, 0x01,
4, _AUTOINC, 0x33, 0x00,
6, _AUTOINC, 0x35, 0x16, 0x00, 0x00,
6, _AUTOINC, 0x35, 0x15, 0x00, 0x5A,
6, _AUTOINC, 0x35, 0x18, 0x00, 0xB0,
6, _AUTOINC, 0x35, 0x15, 0x01, 0x10,
6, _AUTOINC, 0x35, 0x17, 0x01, 0x68,
6, _AUTOINC, 0x35, 0x16, 0x01, 0xC4,
6, _AUTOINC, 0x35, 0x15, 0x02, 0x1C,
6, _AUTOINC, 0x35, 0x14, 0x02, 0x73,
6, _AUTOINC, 0x35, 0x15, 0x02, 0xC6,
6, _AUTOINC, 0x35, 0x14, 0x03, 0x1A,
6, _AUTOINC, 0x35, 0x13, 0x03, 0x6B,
6, _AUTOINC, 0x35, 0x12, 0x03, 0xB9,
6, _AUTOINC, 0x35, 0x12, 0x04, 0x05,
6, _AUTOINC, 0x35, 0x12, 0x04, 0x50,
6, _AUTOINC, 0x35, 0x13, 0x04, 0x98,
6, _AUTOINC, 0x35, 0x10, 0x04, 0xE6,
6, _AUTOINC, 0x35, 0x0E, 0x05, 0x27,
6, _AUTOINC, 0x35, 0x0D, 0x05, 0x60,
6, _AUTOINC, 0x35, 0x0F, 0x05, 0x96,
6, _AUTOINC, 0x35, 0x0E, 0x05, 0xD4,
6, _AUTOINC, 0x35, 0x0C, 0x06, 0x0F,
6, _AUTOINC, 0x35, 0x0B, 0x06, 0x40,
6, _AUTOINC, 0x35, 0x0B, 0x06, 0x6D,
6, _AUTOINC, 0x35, 0x0A, 0x06, 0x9B,
6, _AUTOINC, 0x35, 0x07, 0x06, 0xC5,
6, _AUTOINC, 0x35, 0x07, 0x06, 0xE4,
6, _AUTOINC, 0x35, 0x09, 0x07, 0x00,
6, _AUTOINC, 0x35, 0x06, 0x07, 0x25,
6, _AUTOINC, 0x35, 0x08, 0x07, 0x41,
6, _AUTOINC, 0x35, 0x09, 0x07, 0x5B,
6, _AUTOINC, 0x35, 0x09, 0x07, 0x77,
6, _AUTOINC, 0x35, 0x10, 0x07, 0x91,
4, _AUTOINC, 0x31, 0x02,
4, _AUTOINC, 0x33, 0x00,
6, _AUTOINC, 0x35, 0x15, 0x00, 0x00,
6, _AUTOINC, 0x35, 0x14, 0x00, 0x54,
6, _AUTOINC, 0x35, 0x16, 0x00, 0xA4,
6, _AUTOINC, 0x35, 0x13, 0x00, 0xFE,
6, _AUTOINC, 0x35, 0x15, 0x01, 0x4F,
6, _AUTOINC, 0x35, 0x14, 0x01, 0xA5,
6, _AUTOINC, 0x35, 0x14, 0x01, 0xF7,
6, _AUTOINC, 0x35, 0x14, 0x02, 0x4A,
6, _AUTOINC, 0x35, 0x13, 0x02, 0x9A,
6, _AUTOINC, 0x35, 0x13, 0x02, 0xE9,
6, _AUTOINC, 0x35, 0x13, 0x03, 0x36,
6, _AUTOINC, 0x35, 0x11, 0x03, 0x82,
6, _AUTOINC, 0x35, 0x11, 0x03, 0xCB,
6, _AUTOINC, 0x35, 0x11, 0x04, 0x12,
6, _AUTOINC, 0x35, 0x11, 0x04, 0x59,
6, _AUTOINC, 0x35, 0x10, 0x04, 0x9D,
6, _AUTOINC, 0x35, 0x0F, 0x04, 0xE0,
6, _AUTOINC, 0x35, 0x0D, 0x05, 0x1F,
6, _AUTOINC, 0x35, 0x0F, 0x05, 0x55,
6, _AUTOINC, 0x35, 0x0F, 0x05, 0x94,
6, _AUTOINC, 0x35, 0x0D, 0x05, 0xD2,
6, _AUTOINC, 0x35, 0x0C, 0x06, 0x07,
6, _AUTOINC, 0x35, 0x0B, 0x06, 0x39,
6, _AUTOINC, 0x35, 0x0B, 0x06, 0x67,
6, _AUTOINC, 0x35, 0x0B, 0x06, 0x94,
6, _AUTOINC, 0x35, 0x09, 0x06, 0xC0,
6, _AUTOINC, 0x35, 0x0B, 0x06, 0xE7,
6, _AUTOINC, 0x35, 0x07, 0x07, 0x13,
6, _AUTOINC, 0x35, 0x0A, 0x07, 0x33,
6, _AUTOINC, 0x35, 0x0A, 0x07, 0x52,
6, _AUTOINC, 0x35, 0x0A, 0x07, 0x72,
6, _AUTOINC, 0x35, 0x10, 0x07, 0x91,
4, _AUTOINC, 0x31, 0x03,
4, _AUTOINC, 0x33, 0x00,
6, _AUTOINC, 0x35, 0x13, 0x00, 0x00,
6, _AUTOINC, 0x35, 0x13, 0x00, 0x4D,
6, _AUTOINC, 0x35, 0x14, 0x00, 0x9A,
6, _AUTOINC, 0x35, 0x12, 0x00, 0xEA,
6, _AUTOINC, 0x35, 0x14, 0x01, 0x36,
6, _AUTOINC, 0x35, 0x13, 0x01, 0x86,
6, _AUTOINC, 0x35, 0x13, 0x01, 0xD3,
6, _AUTOINC, 0x35, 0x12, 0x02, 0x1F,
6, _AUTOINC, 0x35, 0x12, 0x02, 0x6A,
6, _AUTOINC, 0x35, 0x12, 0x02, 0xB5,
6, _AUTOINC, 0x35, 0x12, 0x02, 0xFE,
6, _AUTOINC, 0x35, 0x11, 0x03, 0x46,
6, _AUTOINC, 0x35, 0x11, 0x03, 0x8D,
6, _AUTOINC, 0x35, 0x11, 0x03, 0xD2,
6, _AUTOINC, 0x35, 0x11, 0x04, 0x16,
6, _AUTOINC, 0x35, 0x10, 0x04, 0x5A,
6, _AUTOINC, 0x35, 0x10, 0x04, 0x9B,
6, _AUTOINC, 0x35, 0x0D, 0x04, 0xDD,
6, _AUTOINC, 0x35, 0x10, 0x05, 0x13,
6, _AUTOINC, 0x35, 0x0F, 0x05, 0x53,
6, _AUTOINC, 0x35, 0x0E, 0x05, 0x92,
6, _AUTOINC, 0x35, 0x0D, 0x05, 0xCA,
6, _AUTOINC, 0x35, 0x0D, 0x06, 0x00,
6, _AUTOINC, 0x35, 0x0C, 0x06, 0x34,
6, _AUTOINC, 0x35, 0x0C, 0x06, 0x67,
6, _AUTOINC, 0x35, 0x0B, 0x06, 0x98,
6, _AUTOINC, 0x35, 0x0D, 0x06, 0xC6,
6, _AUTOINC, 0x35, 0x09, 0x06, 0xFD,
6, _AUTOINC, 0x35, 0x0C, 0x07, 0x25,
6, _AUTOINC, 0x35, 0x0C, 0x07, 0x49,
6, _AUTOINC, 0x35, 0x0C, 0x07, 0x6E,
6, _AUTOINC, 0x35, 0x10, 0x07, 0x91,
4, _AUTOINC, 0x31, 0x04,
4, _AUTOINC, 0x33, 0x00,
6, _AUTOINC, 0x35, 0x10, 0x00, 0x00,
6, _AUTOINC, 0x35, 0x10, 0x00, 0x80,
6, _AUTOINC, 0x35, 0x10, 0x01, 0x00,
6, _AUTOINC, 0x35, 0x10, 0x01, 0x80,
6, _AUTOINC, 0x35, 0x10, 0x02, 0x00,
6, _AUTOINC, 0x35, 0x10, 0x02, 0x80,
6, _AUTOINC, 0x35, 0x10, 0x03, 0x00,
6, _AUTOINC, 0x35, 0x10, 0x03, 0x80,
6, _AUTOINC, 0x35, 0x10, 0x04, 0x00,
6, _AUTOINC, 0x35, 0x10, 0x04, 0x80,
6, _AUTOINC, 0x35, 0x10, 0x05, 0x00,
6, _AUTOINC, 0x35, 0x10, 0x05, 0x80,
6, _AUTOINC, 0x35, 0x10, 0x06, 0x00,
6, _AUTOINC, 0x35, 0x10, 0x06, 0x80,
6, _AUTOINC, 0x35, 0x10, 0x07, 0x00,
6, _AUTOINC, 0x35, 0x10, 0x07, 0x80,
6, _AUTOINC, 0x35, 0x10, 0x08, 0x00,
6, _AUTOINC, 0x35, 0x10, 0x08, 0x80,
6, _AUTOINC, 0x35, 0x10, 0x09, 0x00,
6, _AUTOINC, 0x35, 0x10, 0x09, 0x80,
6, _AUTOINC, 0x35, 0x10, 0x0A, 0x00,
6, _AUTOINC, 0x35, 0x10, 0x0A, 0x80,
6, _AUTOINC, 0x35, 0x10, 0x0B, 0x00,
6, _AUTOINC, 0x35, 0x10, 0x0B, 0x80,
6, _AUTOINC, 0x35, 0x10, 0x0C, 0x00,
6, _AUTOINC, 0x35, 0x10, 0x0C, 0x80,
6, _AUTOINC, 0x35, 0x10, 0x0D, 0x00,
6, _AUTOINC, 0x35, 0x10, 0x0D, 0x80,
6, _AUTOINC, 0x35, 0x10, 0x0E, 0x00,
6, _AUTOINC, 0x35, 0x10, 0x0E, 0x80,
6, _AUTOINC, 0x35, 0x10, 0x0F, 0x00,
6, _AUTOINC, 0x35, 0x10, 0x0F, 0x80,
4, _AUTOINC, 0x31, 0x05,
4, _AUTOINC, 0x33, 0x00,
6, _AUTOINC, 0x35, 0x0C, 0x00, 0x00,
6, _AUTOINC, 0x35, 0x0D, 0x00, 0x52,
6, _AUTOINC, 0x35, 0x0C, 0x00, 0xA2,
6, _AUTOINC, 0x35, 0x0D, 0x00, 0xF7,
6, _AUTOINC, 0x35, 0x0D, 0x01, 0x4C,
6, _AUTOINC, 0x35, 0x0E, 0x01, 0xA4,
6, _AUTOINC, 0x35, 0x0E, 0x01, 0xFF,
6, _AUTOINC, 0x35, 0x0F, 0x02, 0x5B,
6, _AUTOINC, 0x35, 0x0F, 0x02, 0xBB,
6, _AUTOINC, 0x35, 0x10, 0x03, 0x1E,
6, _AUTOINC, 0x35, 0x10, 0x03, 0x87,
6, _AUTOINC, 0x35, 0x10, 0x03, 0xF0,
6, _AUTOINC, 0x35, 0x13, 0x04, 0x5B,
6, _AUTOINC, 0x35, 0x11, 0x04, 0xD3,
6, _AUTOINC, 0x35, 0x12, 0x05, 0x42,
6, _AUTOINC, 0x35, 0x12, 0x05, 0xB6,
6, _AUTOINC, 0x35, 0x11, 0x06, 0x2C,
6, _AUTOINC, 0x35, 0x12, 0x06, 0x9E,
6, _AUTOINC, 0x35, 0x13, 0x07, 0x0A,
6, _AUTOINC, 0x35, 0x13, 0x07, 0x4D,
6, _AUTOINC, 0x35, 0x10, 0x07, 0x91,
6, _AUTOINC, 0x35, 0x10, 0x08, 0x13,
6, _AUTOINC, 0x35, 0x10, 0x08, 0x5C,
6, _AUTOINC, 0x35, 0x0F, 0x08, 0xA6,
6, _AUTOINC, 0x35, 0x0F, 0x08, 0xF4,
6, _AUTOINC, 0x35, 0x10, 0x09, 0x37,
6, _AUTOINC, 0x35, 0x0F, 0x09, 0x79,
6, _AUTOINC, 0x35, 0x0F, 0x09, 0xC7,
6, _AUTOINC, 0x35, 0x10, 0x0A, 0x13,
6, _AUTOINC, 0x35, 0x0F, 0x0A, 0x5A,
6, _AUTOINC, 0x35, 0x0F, 0x0A, 0xA9,
6, _AUTOINC, 0x35, 0x10, 0x0A, 0xF7,
4, _AUTOINC, 0x31, 0x06,
4, _AUTOINC, 0x33, 0x00,
6, _AUTOINC, 0x35, 0x0A, 0x00, 0x00,
6, _AUTOINC, 0x35, 0x0A, 0x00, 0x45,
6, _AUTOINC, 0x35, 0x0A, 0x00, 0x88,
6, _AUTOINC, 0x35, 0x0B, 0x00, 0xD0,
6, _AUTOINC, 0x35, 0x0C, 0x01, 0x18,
6, _AUTOINC, 0x35, 0x0D, 0x01, 0x69,
6, _AUTOINC, 0x35, 0x0D, 0x01, 0xBC,
6, _AUTOINC, 0x35, 0x0E, 0x02, 0x12,
6, _AUTOINC, 0x35, 0x0F, 0x02, 0x6D,
6, _AUTOINC, 0x35, 0x10, 0x02, 0xD1,
6, _AUTOINC, 0x35, 0x10, 0x03, 0x39,
6, _AUTOINC, 0x35, 0x11, 0x03, 0xA5,
6, _AUTOINC, 0x35, 0x12, 0x04, 0x14,
6, _AUTOINC, 0x35, 0x14, 0x04, 0x86,
6, _AUTOINC, 0x35, 0x0D, 0x05, 0x06,
6, _AUTOINC, 0x35, 0x11, 0x05, 0x5B,
6, _AUTOINC, 0x35, 0x14, 0x05, 0xCC,
6, _AUTOINC, 0x35, 0x16, 0x06, 0x4E,
6, _AUTOINC, 0x35, 0x1D, 0x06, 0xD4,
6, _AUTOINC, 0x35, 0x18, 0x07, 0x38,
6, _AUTOINC, 0x35, 0x12, 0x07, 0x91,
6, _AUTOINC, 0x35, 0x12, 0x08, 0x23,
6, _AUTOINC, 0x35, 0x12, 0x08, 0x77,
6, _AUTOINC, 0x35, 0x0E, 0x08, 0xC9,
6, _AUTOINC, 0x35, 0x0C, 0x09, 0x13,
6, _AUTOINC, 0x35, 0x10, 0x09, 0x4B,
6, _AUTOINC, 0x35, 0x0E, 0x09, 0x8C,
6, _AUTOINC, 0x35, 0x0E, 0x09, 0xD5,
6, _AUTOINC, 0x35, 0x0F, 0x0A, 0x1A,
6, _AUTOINC, 0x35, 0x0F, 0x0A, 0x5E,
6, _AUTOINC, 0x35, 0x0F, 0x0A, 0xAA,
6, _AUTOINC, 0x35, 0x10, 0x0A, 0xF7,
4, _AUTOINC, 0x31, 0x07,
4, _AUTOINC, 0x33, 0x00,
6, _AUTOINC, 0x35, 0x08, 0x00, 0x00,
6, _AUTOINC, 0x35, 0x08, 0x00, 0x33,
6, _AUTOINC, 0x35, 0x08, 0x00, 0x64,
6, _AUTOINC, 0x35, 0x09, 0x00, 0x9C,
6, _AUTOINC, 0x35, 0x0A, 0x00, 0xD6,
6, _AUTOINC, 0x35, 0x0B, 0x01, 0x18,
6, _AUTOINC, 0x35, 0x0C, 0x01, 0x62,
6, _AUTOINC, 0x35, 0x0D, 0x01, 0xB0,
6, _AUTOINC, 0x35, 0x0F, 0x02, 0x06,
6, _AUTOINC, 0x35, 0x10, 0x02, 0x68,
6, _AUTOINC, 0x35, 0x11, 0x02, 0xD2,
6, _AUTOINC, 0x35, 0x12, 0x03, 0x41,
6, _AUTOINC, 0x35, 0x13, 0x03, 0xB4,
6, _AUTOINC, 0x35, 0x15, 0x04, 0x2C,
6, _AUTOINC, 0x35, 0x10, 0x04, 0xB5,
6, _AUTOINC, 0x35, 0x11, 0x05, 0x1F,
6, _AUTOINC, 0x35, 0x16, 0x05, 0x8C,
6, _AUTOINC, 0x35, 0x1A, 0x06, 0x19,
6, _AUTOINC, 0x35, 0x21, 0x06, 0xB7,
6, _AUTOINC, 0x35, 0x1C, 0x07, 0x2A,
6, _AUTOINC, 0x35, 0x15, 0x07, 0x91,
6, _AUTOINC, 0x35, 0x16, 0x08, 0x3A,
6, _AUTOINC, 0x35, 0x15, 0x08, 0xA0,
6, _AUTOINC, 0x35, 0x0B, 0x08, 0xFE,
6, _AUTOINC, 0x35, 0x0C, 0x09, 0x37,
6, _AUTOINC, 0x35, 0x0E, 0x09, 0x6D,
6, _AUTOINC, 0x35, 0x0C, 0x09, 0xA9,
6, _AUTOINC, 0x35, 0x0C, 0x09, 0xE9,
6, _AUTOINC, 0x35, 0x0E, 0x0A, 0x24,
6, _AUTOINC, 0x35, 0x0E, 0x0A, 0x64,
6, _AUTOINC, 0x35, 0x0F, 0x0A, 0xAC,
6, _AUTOINC, 0x35, 0x10, 0x0A, 0xF7,
4, _AUTOINC, 0x31, 0x00,
4, _AUTOINC, 0x33, 0x00,
4, _AUTOINC, 0x39, 0x00,

// CDM
19, _AUTOINC, 0xD0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
19, _AUTOINC, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
4, _AUTOINC, 0xF0, 0x00,

//TM Blending Factor
4, _AUTOINC, 0x3B, 0x80,

// sharpness
19, _AUTOINC, 0x40, 0xEB, 0xA4, 0x74, 0x5A, 0x48, 0x36, 0x28, 0x20, 0x18, 0x12, 0x0C, 0x07, 0x03, 0x02, 0x01, 0x01,
19, _AUTOINC, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
4, _AUTOINC, 0x60, 0x00,
4, _AUTOINC, 0x63, 0x05,
19, _AUTOINC, 0x70, 0x4A, 0x69, 0x84, 0x94, 0x97, 0x94, 0x88, 0x7A, 0x6E, 0x63, 0x59, 0x50, 0x48, 0x41, 0x3A, 0x35,
19, _AUTOINC, 0x80, 0x2F, 0x2B, 0x26, 0x22, 0x1F, 0x1C, 0x19, 0x17, 0x14, 0x12, 0x10, 0x0F, 0x0D, 0x0C, 0x0B, 0x0A,
4, _AUTOINC, 0x90, 0x09,
4, _AUTOINC, 0x93, 0x00,

4, _AUTOINC, 0x30, 0xC0,
_END,
#endif