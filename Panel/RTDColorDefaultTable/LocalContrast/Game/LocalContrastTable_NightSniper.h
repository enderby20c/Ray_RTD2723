////////////////////////////////////////////
//Local Contrast High Performance Setting ///
////////////////////////////////////////////
#if(_HW_LOCAL_CONTRAST_GEN_SEL == _LOCAL_CONTRAST_GEN_3)
4, _AUTOINC, 0x9F, 0x42,

// Tone-mapping grid setting
19, _AUTOINC, 0x20, 0x00, 0x50, 0x00, 0x90, 0x01, 0x10, 0x01, 0x90, 0x11, 0xD0, 0x12, 0x50, 0x12, 0xD0, 0x13, 0x10,

// Tone-mapping table
4, _AUTOINC, 0x31, 0x00,
4, _AUTOINC, 0x33, 0x00,
6, _AUTOINC, 0x35, 0xAB, 0x00, 0x00,
6, _AUTOINC, 0x35, 0x4B, 0x02, 0xAD,
6, _AUTOINC, 0x35, 0x2A, 0x03, 0xDA,
6, _AUTOINC, 0x35, 0x25, 0x04, 0x85,
6, _AUTOINC, 0x35, 0x21, 0x05, 0x1C,
6, _AUTOINC, 0x35, 0x15, 0x05, 0xA0,
6, _AUTOINC, 0x35, 0x13, 0x05, 0xF7,
6, _AUTOINC, 0x35, 0x0D, 0x06, 0x46,
6, _AUTOINC, 0x35, 0x15, 0x06, 0x7B,
6, _AUTOINC, 0x35, 0x13, 0x06, 0xCF,
6, _AUTOINC, 0x35, 0x11, 0x07, 0x1C,
6, _AUTOINC, 0x35, 0x0F, 0x07, 0x61,
6, _AUTOINC, 0x35, 0x0E, 0x07, 0x9F,
6, _AUTOINC, 0x35, 0x0B, 0x07, 0xD7,
6, _AUTOINC, 0x35, 0x0B, 0x08, 0x04,
6, _AUTOINC, 0x35, 0x0C, 0x08, 0x31,
6, _AUTOINC, 0x35, 0x0C, 0x08, 0x63,
6, _AUTOINC, 0x35, 0x0B, 0x08, 0x93,
6, _AUTOINC, 0x35, 0x0A, 0x08, 0xC1,
6, _AUTOINC, 0x35, 0x09, 0x08, 0xEB,
6, _AUTOINC, 0x35, 0x06, 0x09, 0x10,
6, _AUTOINC, 0x35, 0x06, 0x09, 0x2B,
6, _AUTOINC, 0x35, 0x05, 0x09, 0x44,
6, _AUTOINC, 0x35, 0x05, 0x09, 0x5B,
6, _AUTOINC, 0x35, 0x04, 0x09, 0x6F,
6, _AUTOINC, 0x35, 0x04, 0x09, 0x82,
6, _AUTOINC, 0x35, 0x05, 0x09, 0x95,
6, _AUTOINC, 0x35, 0x05, 0x09, 0xAA,
6, _AUTOINC, 0x35, 0x06, 0x09, 0xC0,
6, _AUTOINC, 0x35, 0x06, 0x09, 0xD8,
6, _AUTOINC, 0x35, 0x04, 0x09, 0xF3,
6, _AUTOINC, 0x35, 0x0B, 0x0A, 0x13,
4, _AUTOINC, 0x31, 0x01,
4, _AUTOINC, 0x33, 0x00,
6, _AUTOINC, 0x35, 0x9C, 0x00, 0x00,
6, _AUTOINC, 0x35, 0x2F, 0x02, 0x72,
6, _AUTOINC, 0x35, 0x29, 0x03, 0x30,
6, _AUTOINC, 0x35, 0x2E, 0x03, 0xD6,
6, _AUTOINC, 0x35, 0x21, 0x04, 0x90,
6, _AUTOINC, 0x35, 0x16, 0x05, 0x16,
6, _AUTOINC, 0x35, 0x14, 0x05, 0x71,
6, _AUTOINC, 0x35, 0x10, 0x05, 0xC4,
6, _AUTOINC, 0x35, 0x13, 0x06, 0x06,
6, _AUTOINC, 0x35, 0x14, 0x06, 0x52,
6, _AUTOINC, 0x35, 0x11, 0x06, 0xA2,
6, _AUTOINC, 0x35, 0x11, 0x06, 0xE9,
6, _AUTOINC, 0x35, 0x0F, 0x07, 0x2D,
6, _AUTOINC, 0x35, 0x0C, 0x07, 0x6B,
6, _AUTOINC, 0x35, 0x0B, 0x07, 0x9C,
6, _AUTOINC, 0x35, 0x0B, 0x07, 0xCB,
6, _AUTOINC, 0x35, 0x0B, 0x07, 0xF7,
6, _AUTOINC, 0x35, 0x0B, 0x08, 0x23,
6, _AUTOINC, 0x35, 0x0A, 0x08, 0x51,
6, _AUTOINC, 0x35, 0x0A, 0x08, 0x7C,
6, _AUTOINC, 0x35, 0x09, 0x08, 0xA5,
6, _AUTOINC, 0x35, 0x09, 0x08, 0xCB,
6, _AUTOINC, 0x35, 0x08, 0x08, 0xF0,
6, _AUTOINC, 0x35, 0x08, 0x09, 0x10,
6, _AUTOINC, 0x35, 0x07, 0x09, 0x30,
6, _AUTOINC, 0x35, 0x07, 0x09, 0x4E,
6, _AUTOINC, 0x35, 0x07, 0x09, 0x6B,
6, _AUTOINC, 0x35, 0x06, 0x09, 0x88,
6, _AUTOINC, 0x35, 0x08, 0x09, 0xA3,
6, _AUTOINC, 0x35, 0x08, 0x09, 0xC5,
6, _AUTOINC, 0x35, 0x05, 0x09, 0xE7,
6, _AUTOINC, 0x35, 0x0B, 0x0A, 0x13,
4, _AUTOINC, 0x31, 0x02,
4, _AUTOINC, 0x33, 0x00,
6, _AUTOINC, 0x35, 0x88, 0x00, 0x00,
6, _AUTOINC, 0x35, 0x2F, 0x02, 0x23,
6, _AUTOINC, 0x35, 0x22, 0x02, 0xE0,
6, _AUTOINC, 0x35, 0x22, 0x03, 0x6A,
6, _AUTOINC, 0x35, 0x1D, 0x03, 0xF5,
6, _AUTOINC, 0x35, 0x17, 0x04, 0x6C,
6, _AUTOINC, 0x35, 0x15, 0x04, 0xCA,
6, _AUTOINC, 0x35, 0x14, 0x05, 0x1E,
6, _AUTOINC, 0x35, 0x14, 0x05, 0x6E,
6, _AUTOINC, 0x35, 0x14, 0x05, 0xC0,
6, _AUTOINC, 0x35, 0x12, 0x06, 0x11,
6, _AUTOINC, 0x35, 0x11, 0x06, 0x59,
6, _AUTOINC, 0x35, 0x0F, 0x06, 0x9D,
6, _AUTOINC, 0x35, 0x0E, 0x06, 0xDC,
6, _AUTOINC, 0x35, 0x0D, 0x07, 0x14,
6, _AUTOINC, 0x35, 0x0D, 0x07, 0x4B,
6, _AUTOINC, 0x35, 0x0D, 0x07, 0x7F,
6, _AUTOINC, 0x35, 0x0C, 0x07, 0xB3,
6, _AUTOINC, 0x35, 0x0B, 0x07, 0xE3,
6, _AUTOINC, 0x35, 0x0B, 0x08, 0x11,
6, _AUTOINC, 0x35, 0x0B, 0x08, 0x40,
6, _AUTOINC, 0x35, 0x0A, 0x08, 0x6C,
6, _AUTOINC, 0x35, 0x0A, 0x08, 0x95,
6, _AUTOINC, 0x35, 0x0A, 0x08, 0xBE,
6, _AUTOINC, 0x35, 0x0A, 0x08, 0xE6,
6, _AUTOINC, 0x35, 0x09, 0x09, 0x0E,
6, _AUTOINC, 0x35, 0x0A, 0x09, 0x35,
6, _AUTOINC, 0x35, 0x09, 0x09, 0x5D,
6, _AUTOINC, 0x35, 0x09, 0x09, 0x84,
6, _AUTOINC, 0x35, 0x0B, 0x09, 0xAB,
6, _AUTOINC, 0x35, 0x07, 0x09, 0xDA,
6, _AUTOINC, 0x35, 0x0B, 0x0A, 0x13,
4, _AUTOINC, 0x31, 0x03,
4, _AUTOINC, 0x33, 0x00,
6, _AUTOINC, 0x35, 0x74, 0x00, 0x00,
6, _AUTOINC, 0x35, 0x2F, 0x01, 0xD0,
6, _AUTOINC, 0x35, 0x1B, 0x02, 0x8D,
6, _AUTOINC, 0x35, 0x15, 0x02, 0xF9,
6, _AUTOINC, 0x35, 0x19, 0x03, 0x4D,
6, _AUTOINC, 0x35, 0x19, 0x03, 0xB4,
6, _AUTOINC, 0x35, 0x15, 0x04, 0x19,
6, _AUTOINC, 0x35, 0x18, 0x04, 0x6D,
6, _AUTOINC, 0x35, 0x16, 0x04, 0xCE,
6, _AUTOINC, 0x35, 0x15, 0x05, 0x26,
6, _AUTOINC, 0x35, 0x12, 0x05, 0x7A,
6, _AUTOINC, 0x35, 0x11, 0x05, 0xC3,
6, _AUTOINC, 0x35, 0x10, 0x06, 0x07,
6, _AUTOINC, 0x35, 0x0F, 0x06, 0x49,
6, _AUTOINC, 0x35, 0x0F, 0x06, 0x88,
6, _AUTOINC, 0x35, 0x0F, 0x06, 0xC6,
6, _AUTOINC, 0x35, 0x0E, 0x07, 0x05,
6, _AUTOINC, 0x35, 0x0C, 0x07, 0x3F,
6, _AUTOINC, 0x35, 0x0C, 0x07, 0x72,
6, _AUTOINC, 0x35, 0x0C, 0x07, 0xA4,
6, _AUTOINC, 0x35, 0x0C, 0x07, 0xD7,
6, _AUTOINC, 0x35, 0x0C, 0x08, 0x07,
6, _AUTOINC, 0x35, 0x0B, 0x08, 0x3A,
6, _AUTOINC, 0x35, 0x0B, 0x08, 0x69,
6, _AUTOINC, 0x35, 0x0A, 0x08, 0x98,
6, _AUTOINC, 0x35, 0x0B, 0x08, 0xC2,
6, _AUTOINC, 0x35, 0x0B, 0x08, 0xEF,
6, _AUTOINC, 0x35, 0x0D, 0x09, 0x1E,
6, _AUTOINC, 0x35, 0x0E, 0x09, 0x53,
6, _AUTOINC, 0x35, 0x0F, 0x09, 0x8D,
6, _AUTOINC, 0x35, 0x09, 0x09, 0xCB,
6, _AUTOINC, 0x35, 0x0B, 0x0A, 0x13,
4, _AUTOINC, 0x31, 0x04,
4, _AUTOINC, 0x33, 0x00,
6, _AUTOINC, 0x35, 0x32, 0x00, 0x00,
6, _AUTOINC, 0x35, 0x1D, 0x01, 0x96,
6, _AUTOINC, 0x35, 0x19, 0x02, 0x85,
6, _AUTOINC, 0x35, 0x16, 0x03, 0x4D,
6, _AUTOINC, 0x35, 0x14, 0x04, 0x00,
6, _AUTOINC, 0x35, 0x13, 0x04, 0xA4,
6, _AUTOINC, 0x35, 0x12, 0x05, 0x3E,
6, _AUTOINC, 0x35, 0x11, 0x05, 0xCF,
6, _AUTOINC, 0x35, 0x10, 0x06, 0x59,
6, _AUTOINC, 0x35, 0x10, 0x06, 0xDE,
6, _AUTOINC, 0x35, 0x0F, 0x07, 0x5E,
6, _AUTOINC, 0x35, 0x0E, 0x07, 0xDA,
6, _AUTOINC, 0x35, 0x0E, 0x08, 0x51,
6, _AUTOINC, 0x35, 0x0E, 0x08, 0xC6,
6, _AUTOINC, 0x35, 0x0D, 0x09, 0x38,
6, _AUTOINC, 0x35, 0x0D, 0x09, 0xA7,
6, _AUTOINC, 0x35, 0x0D, 0x0A, 0x13,
6, _AUTOINC, 0x35, 0x0D, 0x0A, 0x7E,
6, _AUTOINC, 0x35, 0x0C, 0x0A, 0xE6,
6, _AUTOINC, 0x35, 0x0C, 0x0B, 0x4D,
6, _AUTOINC, 0x35, 0x0C, 0x0B, 0xB1,
6, _AUTOINC, 0x35, 0x0C, 0x0C, 0x14,
6, _AUTOINC, 0x35, 0x0C, 0x0C, 0x76,
6, _AUTOINC, 0x35, 0x0B, 0x0C, 0xD6,
6, _AUTOINC, 0x35, 0x0B, 0x0D, 0x34,
6, _AUTOINC, 0x35, 0x0B, 0x0D, 0x91,
6, _AUTOINC, 0x35, 0x0B, 0x0D, 0xED,
6, _AUTOINC, 0x35, 0x0B, 0x0E, 0x48,
6, _AUTOINC, 0x35, 0x0B, 0x0E, 0xA2,
6, _AUTOINC, 0x35, 0x0B, 0x0E, 0xFB,
6, _AUTOINC, 0x35, 0x0A, 0x0F, 0x53,
6, _AUTOINC, 0x35, 0x0A, 0x0F, 0xA9,
4, _AUTOINC, 0x31, 0x05,
4, _AUTOINC, 0x33, 0x00,
6, _AUTOINC, 0x35, 0x27, 0x00, 0x00,
6, _AUTOINC, 0x35, 0x19, 0x01, 0x38,
6, _AUTOINC, 0x35, 0x14, 0x02, 0x06,
6, _AUTOINC, 0x35, 0x13, 0x02, 0xAA,
6, _AUTOINC, 0x35, 0x15, 0x03, 0x42,
6, _AUTOINC, 0x35, 0x12, 0x03, 0xEB,
6, _AUTOINC, 0x35, 0x0F, 0x04, 0x81,
6, _AUTOINC, 0x35, 0x14, 0x04, 0xFC,
6, _AUTOINC, 0x35, 0x13, 0x05, 0xA1,
6, _AUTOINC, 0x35, 0x16, 0x06, 0x3A,
6, _AUTOINC, 0x35, 0x12, 0x06, 0xEA,
6, _AUTOINC, 0x35, 0x11, 0x07, 0x7D,
6, _AUTOINC, 0x35, 0x12, 0x08, 0x0C,
6, _AUTOINC, 0x35, 0x0E, 0x08, 0x9C,
6, _AUTOINC, 0x35, 0x0E, 0x09, 0x0F,
6, _AUTOINC, 0x35, 0x12, 0x09, 0x7F,
6, _AUTOINC, 0x35, 0x18, 0x0A, 0x13,
6, _AUTOINC, 0x35, 0x12, 0x0A, 0xD4,
6, _AUTOINC, 0x35, 0x0F, 0x0B, 0x66,
6, _AUTOINC, 0x35, 0x0F, 0x0B, 0xE5,
6, _AUTOINC, 0x35, 0x0C, 0x0C, 0x5D,
6, _AUTOINC, 0x35, 0x09, 0x0C, 0xC1,
6, _AUTOINC, 0x35, 0x05, 0x0D, 0x0E,
6, _AUTOINC, 0x35, 0x07, 0x0D, 0x3A,
6, _AUTOINC, 0x35, 0x0B, 0x0D, 0x76,
6, _AUTOINC, 0x35, 0x08, 0x0D, 0xD4,
6, _AUTOINC, 0x35, 0x0B, 0x0E, 0x15,
6, _AUTOINC, 0x35, 0x0A, 0x0E, 0x6E,
6, _AUTOINC, 0x35, 0x0B, 0x0E, 0xC3,
6, _AUTOINC, 0x35, 0x08, 0x0F, 0x1C,
6, _AUTOINC, 0x35, 0x09, 0x0F, 0x63,
6, _AUTOINC, 0x35, 0x09, 0x0F, 0xAF,
4, _AUTOINC, 0x31, 0x06,
4, _AUTOINC, 0x33, 0x00,
6, _AUTOINC, 0x35, 0x15, 0x00, 0x00,
6, _AUTOINC, 0x35, 0x1E, 0x00, 0xAE,
6, _AUTOINC, 0x35, 0x16, 0x01, 0xA3,
6, _AUTOINC, 0x35, 0x10, 0x02, 0x55,
6, _AUTOINC, 0x35, 0x16, 0x02, 0xD7,
6, _AUTOINC, 0x35, 0x13, 0x03, 0x8A,
6, _AUTOINC, 0x35, 0x0F, 0x04, 0x28,
6, _AUTOINC, 0x35, 0x15, 0x04, 0xA7,
6, _AUTOINC, 0x35, 0x13, 0x05, 0x52,
6, _AUTOINC, 0x35, 0x12, 0x05, 0xEE,
6, _AUTOINC, 0x35, 0x12, 0x06, 0x84,
6, _AUTOINC, 0x35, 0x12, 0x07, 0x1A,
6, _AUTOINC, 0x35, 0x12, 0x07, 0xAE,
6, _AUTOINC, 0x35, 0x12, 0x08, 0x40,
6, _AUTOINC, 0x35, 0x0E, 0x08, 0xD1,
6, _AUTOINC, 0x35, 0x1B, 0x09, 0x42,
6, _AUTOINC, 0x35, 0x1D, 0x0A, 0x1C,
6, _AUTOINC, 0x35, 0x14, 0x0B, 0x05,
6, _AUTOINC, 0x35, 0x0F, 0x0B, 0xA5,
6, _AUTOINC, 0x35, 0x10, 0x0C, 0x23,
6, _AUTOINC, 0x35, 0x0B, 0x0C, 0xA9,
6, _AUTOINC, 0x35, 0x07, 0x0D, 0x04,
6, _AUTOINC, 0x35, 0x08, 0x0D, 0x41,
6, _AUTOINC, 0x35, 0x07, 0x0D, 0x83,
6, _AUTOINC, 0x35, 0x07, 0x0D, 0xBD,
6, _AUTOINC, 0x35, 0x08, 0x0D, 0xF6,
6, _AUTOINC, 0x35, 0x09, 0x0E, 0x3A,
6, _AUTOINC, 0x35, 0x09, 0x0E, 0x83,
6, _AUTOINC, 0x35, 0x0A, 0x0E, 0xD1,
6, _AUTOINC, 0x35, 0x0A, 0x0F, 0x21,
6, _AUTOINC, 0x35, 0x09, 0x0F, 0x73,
6, _AUTOINC, 0x35, 0x08, 0x0F, 0xBC,
4, _AUTOINC, 0x31, 0x07,
4, _AUTOINC, 0x33, 0x00,
6, _AUTOINC, 0x35, 0x15, 0x00, 0x00,
6, _AUTOINC, 0x35, 0x0A, 0x00, 0xAE,
6, _AUTOINC, 0x35, 0x1A, 0x01, 0x00,
6, _AUTOINC, 0x35, 0x11, 0x01, 0xD4,
6, _AUTOINC, 0x35, 0x18, 0x02, 0x63,
6, _AUTOINC, 0x35, 0x14, 0x03, 0x24,
6, _AUTOINC, 0x35, 0x10, 0x03, 0xCA,
6, _AUTOINC, 0x35, 0x16, 0x04, 0x4F,
6, _AUTOINC, 0x35, 0x14, 0x04, 0xFF,
6, _AUTOINC, 0x35, 0x13, 0x05, 0xA0,
6, _AUTOINC, 0x35, 0x13, 0x06, 0x3A,
6, _AUTOINC, 0x35, 0x12, 0x06, 0xD3,
6, _AUTOINC, 0x35, 0x12, 0x07, 0x6A,
6, _AUTOINC, 0x35, 0x14, 0x07, 0xFF,
6, _AUTOINC, 0x35, 0x0E, 0x08, 0xA3,
6, _AUTOINC, 0x35, 0x1E, 0x09, 0x16,
6, _AUTOINC, 0x35, 0x28, 0x0A, 0x0B,
6, _AUTOINC, 0x35, 0x13, 0x0B, 0x4D,
6, _AUTOINC, 0x35, 0x0F, 0x0B, 0xEB,
6, _AUTOINC, 0x35, 0x10, 0x0C, 0x67,
6, _AUTOINC, 0x35, 0x0C, 0x0C, 0xEC,
6, _AUTOINC, 0x35, 0x09, 0x0D, 0x4E,
6, _AUTOINC, 0x35, 0x07, 0x0D, 0x97,
6, _AUTOINC, 0x35, 0x07, 0x0D, 0xD0,
6, _AUTOINC, 0x35, 0x07, 0x0E, 0x09,
6, _AUTOINC, 0x35, 0x07, 0x0E, 0x42,
6, _AUTOINC, 0x35, 0x07, 0x0E, 0x7A,
6, _AUTOINC, 0x35, 0x08, 0x0E, 0xB6,
6, _AUTOINC, 0x35, 0x08, 0x0E, 0xF7,
6, _AUTOINC, 0x35, 0x0A, 0x0F, 0x3D,
6, _AUTOINC, 0x35, 0x07, 0x0F, 0x8E,
6, _AUTOINC, 0x35, 0x06, 0x0F, 0xC9,
4, _AUTOINC, 0x31, 0x00,
4, _AUTOINC, 0x33, 0x00,
4, _AUTOINC, 0x39, 0x00,

// CDM
19, _AUTOINC, 0xD0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
19, _AUTOINC, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
4, _AUTOINC, 0xF0, 0x00,

//TM Blending Factor
4, _AUTOINC, 0x3B, 0x60,

// sharpness
19, _AUTOINC, 0x40, 0x80, 0x7F, 0x7E, 0x7C, 0x7A, 0x78, 0x76, 0x73, 0x70, 0x6D, 0x6A, 0x67, 0x64, 0x60, 0x5C, 0x58,
19, _AUTOINC, 0x50, 0x54, 0x50, 0x4B, 0x46, 0x41, 0x3C, 0x37, 0x30, 0x28, 0x20, 0x18, 0x12, 0x0C, 0x06, 0x00, 0x00,
4, _AUTOINC, 0x60, 0x00,
4, _AUTOINC, 0x63, 0x04,
19, _AUTOINC, 0x70, 0xB2, 0x9A, 0x82, 0x6D, 0x61, 0x59, 0x51, 0x4A, 0x45, 0x3F, 0x3A, 0x35, 0x33, 0x30, 0x2A, 0x26,
19, _AUTOINC, 0x80, 0x24, 0x24, 0x24, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22,
4, _AUTOINC, 0x90, 0x16,
4, _AUTOINC, 0x93, 0x00,

4, _AUTOINC, 0x30, 0xC0,
_END,
#endif
