////////////////////////////////////////////
//Local Contrast High Performance Setting ///
////////////////////////////////////////////
#if((_HW_LOCAL_CONTRAST_GEN_SEL == _LOCAL_CONTRAST_GEN_3) || (_HW_LOCAL_CONTRAST_GEN_SEL == _LOCAL_CONTRAST_GEN_4))
4, _AUTOINC, 0x9F, 0x42,

// Tone-mapping grid setting
19, _AUTOINC, 0x20, 0x21, 0x1F, 0x22, 0x1F, 0x23, 0x1F, 0x23, 0x3F, 0x23, 0x5F, 0x23, 0x7F, 0x23, 0x9F, 0x23, 0xBF,

// Tone-mapping table
4, _AUTOINC, 0x31, 0x00,
4, _AUTOINC, 0x33, 0x00,
6, _AUTOINC, 0x35, 0x1B, 0x00, 0x00,
6, _AUTOINC, 0x35, 0x19, 0x00, 0xB0,
6, _AUTOINC, 0x35, 0x1F, 0x01, 0x4B,
6, _AUTOINC, 0x35, 0x22, 0x02, 0x19,
6, _AUTOINC, 0x35, 0x15, 0x02, 0xF5,
6, _AUTOINC, 0x35, 0x15, 0x03, 0x81,
6, _AUTOINC, 0x35, 0x18, 0x04, 0x0C,
6, _AUTOINC, 0x35, 0x13, 0x04, 0xA9,
6, _AUTOINC, 0x35, 0x14, 0x05, 0x22,
6, _AUTOINC, 0x35, 0x10, 0x05, 0xA3,
6, _AUTOINC, 0x35, 0x15, 0x06, 0x0A,
6, _AUTOINC, 0x35, 0x0E, 0x06, 0x94,
6, _AUTOINC, 0x35, 0x11, 0x06, 0xF1,
6, _AUTOINC, 0x35, 0x0A, 0x07, 0x5D,
6, _AUTOINC, 0x35, 0x06, 0x07, 0xA0,
6, _AUTOINC, 0x35, 0x0D, 0x07, 0xC9,
6, _AUTOINC, 0x35, 0x07, 0x08, 0x1C,
6, _AUTOINC, 0x35, 0x04, 0x08, 0x4B,
6, _AUTOINC, 0x35, 0x0B, 0x08, 0x67,
6, _AUTOINC, 0x35, 0x09, 0x08, 0x8E,
6, _AUTOINC, 0x35, 0x05, 0x08, 0xAF,
6, _AUTOINC, 0x35, 0x07, 0x08, 0xDA,
6, _AUTOINC, 0x35, 0x0B, 0x08, 0xFB,
6, _AUTOINC, 0x35, 0x09, 0x09, 0x2D,
6, _AUTOINC, 0x35, 0x0B, 0x09, 0x5B,
6, _AUTOINC, 0x35, 0x0D, 0x09, 0x8F,
6, _AUTOINC, 0x35, 0x0E, 0x09, 0xC4,
6, _AUTOINC, 0x35, 0x09, 0x0A, 0x0C,
6, _AUTOINC, 0x35, 0x12, 0x0A, 0x3A,
6, _AUTOINC, 0x35, 0x10, 0x0A, 0x8A,
6, _AUTOINC, 0x35, 0x05, 0x0A, 0xDD,
6, _AUTOINC, 0x35, 0x10, 0x0A, 0xF7,
4, _AUTOINC, 0x31, 0x01,
4, _AUTOINC, 0x33, 0x00,
6, _AUTOINC, 0x35, 0x19, 0x00, 0x00,
6, _AUTOINC, 0x35, 0x17, 0x00, 0xA4,
6, _AUTOINC, 0x35, 0x1C, 0x01, 0x33,
6, _AUTOINC, 0x35, 0x1F, 0x01, 0xEE,
6, _AUTOINC, 0x35, 0x14, 0x02, 0xB4,
6, _AUTOINC, 0x35, 0x14, 0x03, 0x39,
6, _AUTOINC, 0x35, 0x14, 0x03, 0xBD,
6, _AUTOINC, 0x35, 0x14, 0x04, 0x42,
6, _AUTOINC, 0x35, 0x13, 0x04, 0xC5,
6, _AUTOINC, 0x35, 0x10, 0x05, 0x42,
6, _AUTOINC, 0x35, 0x14, 0x05, 0xA8,
6, _AUTOINC, 0x35, 0x0E, 0x06, 0x2C,
6, _AUTOINC, 0x35, 0x14, 0x06, 0x8A,
6, _AUTOINC, 0x35, 0x0A, 0x07, 0x0E,
6, _AUTOINC, 0x35, 0x09, 0x07, 0x52,
6, _AUTOINC, 0x35, 0x08, 0x07, 0x91,
6, _AUTOINC, 0x35, 0x0A, 0x07, 0xC5,
6, _AUTOINC, 0x35, 0x08, 0x08, 0x09,
6, _AUTOINC, 0x35, 0x08, 0x08, 0x3C,
6, _AUTOINC, 0x35, 0x08, 0x08, 0x5A,
6, _AUTOINC, 0x35, 0x07, 0x08, 0x7A,
6, _AUTOINC, 0x35, 0x0A, 0x08, 0xB6,
6, _AUTOINC, 0x35, 0x0B, 0x08, 0xE7,
6, _AUTOINC, 0x35, 0x08, 0x09, 0x1C,
6, _AUTOINC, 0x35, 0x0B, 0x09, 0x48,
6, _AUTOINC, 0x35, 0x0E, 0x09, 0x7B,
6, _AUTOINC, 0x35, 0x0E, 0x09, 0xB5,
6, _AUTOINC, 0x35, 0x0A, 0x09, 0xFF,
6, _AUTOINC, 0x35, 0x11, 0x0A, 0x31,
6, _AUTOINC, 0x35, 0x10, 0x0A, 0x80,
6, _AUTOINC, 0x35, 0x07, 0x0A, 0xD3,
6, _AUTOINC, 0x35, 0x10, 0x0A, 0xF7,
4, _AUTOINC, 0x31, 0x02,
4, _AUTOINC, 0x33, 0x00,
6, _AUTOINC, 0x35, 0x17, 0x00, 0x00,
6, _AUTOINC, 0x35, 0x15, 0x00, 0x97,
6, _AUTOINC, 0x35, 0x1A, 0x01, 0x18,
6, _AUTOINC, 0x35, 0x1B, 0x01, 0xC3,
6, _AUTOINC, 0x35, 0x13, 0x02, 0x73,
6, _AUTOINC, 0x35, 0x13, 0x02, 0xF2,
6, _AUTOINC, 0x35, 0x13, 0x03, 0x6F,
6, _AUTOINC, 0x35, 0x13, 0x03, 0xED,
6, _AUTOINC, 0x35, 0x12, 0x04, 0x69,
6, _AUTOINC, 0x35, 0x10, 0x04, 0xE1,
6, _AUTOINC, 0x35, 0x13, 0x05, 0x47,
6, _AUTOINC, 0x35, 0x0F, 0x05, 0xC4,
6, _AUTOINC, 0x35, 0x13, 0x06, 0x24,
6, _AUTOINC, 0x35, 0x0F, 0x06, 0xA2,
6, _AUTOINC, 0x35, 0x0A, 0x07, 0x02,
6, _AUTOINC, 0x35, 0x08, 0x07, 0x46,
6, _AUTOINC, 0x35, 0x09, 0x07, 0x7F,
6, _AUTOINC, 0x35, 0x0B, 0x07, 0xBA,
6, _AUTOINC, 0x35, 0x0C, 0x07, 0xFC,
6, _AUTOINC, 0x35, 0x0A, 0x08, 0x26,
6, _AUTOINC, 0x35, 0x08, 0x08, 0x4B,
6, _AUTOINC, 0x35, 0x0C, 0x08, 0x8C,
6, _AUTOINC, 0x35, 0x0D, 0x08, 0xC4,
6, _AUTOINC, 0x35, 0x0A, 0x09, 0x01,
6, _AUTOINC, 0x35, 0x0B, 0x09, 0x35,
6, _AUTOINC, 0x35, 0x0F, 0x09, 0x66,
6, _AUTOINC, 0x35, 0x0F, 0x09, 0xA5,
6, _AUTOINC, 0x35, 0x0B, 0x09, 0xF1,
6, _AUTOINC, 0x35, 0x11, 0x0A, 0x29,
6, _AUTOINC, 0x35, 0x10, 0x0A, 0x77,
6, _AUTOINC, 0x35, 0x09, 0x0A, 0xC9,
6, _AUTOINC, 0x35, 0x10, 0x0A, 0xF7,
4, _AUTOINC, 0x31, 0x03,
4, _AUTOINC, 0x33, 0x00,
6, _AUTOINC, 0x35, 0x16, 0x00, 0x00,
6, _AUTOINC, 0x35, 0x15, 0x00, 0x90,
6, _AUTOINC, 0x35, 0x17, 0x01, 0x11,
6, _AUTOINC, 0x35, 0x19, 0x01, 0xAD,
6, _AUTOINC, 0x35, 0x13, 0x02, 0x52,
6, _AUTOINC, 0x35, 0x13, 0x02, 0xCE,
6, _AUTOINC, 0x35, 0x13, 0x03, 0x48,
6, _AUTOINC, 0x35, 0x13, 0x03, 0xC3,
6, _AUTOINC, 0x35, 0x12, 0x04, 0x3B,
6, _AUTOINC, 0x35, 0x10, 0x04, 0xB1,
6, _AUTOINC, 0x35, 0x12, 0x05, 0x17,
6, _AUTOINC, 0x35, 0x0F, 0x05, 0x90,
6, _AUTOINC, 0x35, 0x13, 0x05, 0xF1,
6, _AUTOINC, 0x35, 0x0F, 0x06, 0x6B,
6, _AUTOINC, 0x35, 0x0D, 0x06, 0xCC,
6, _AUTOINC, 0x35, 0x09, 0x07, 0x1F,
6, _AUTOINC, 0x35, 0x09, 0x07, 0x5B,
6, _AUTOINC, 0x35, 0x0A, 0x07, 0x99,
6, _AUTOINC, 0x35, 0x0E, 0x07, 0xD6,
6, _AUTOINC, 0x35, 0x0B, 0x08, 0x09,
6, _AUTOINC, 0x35, 0x08, 0x08, 0x33,
6, _AUTOINC, 0x35, 0x0C, 0x08, 0x78,
6, _AUTOINC, 0x35, 0x0E, 0x08, 0xB1,
6, _AUTOINC, 0x35, 0x0B, 0x08, 0xF1,
6, _AUTOINC, 0x35, 0x0B, 0x09, 0x2B,
6, _AUTOINC, 0x35, 0x0F, 0x09, 0x5C,
6, _AUTOINC, 0x35, 0x0F, 0x09, 0x9C,
6, _AUTOINC, 0x35, 0x0C, 0x09, 0xE9,
6, _AUTOINC, 0x35, 0x11, 0x0A, 0x25,
6, _AUTOINC, 0x35, 0x10, 0x0A, 0x71,
6, _AUTOINC, 0x35, 0x0A, 0x0A, 0xC3,
6, _AUTOINC, 0x35, 0x10, 0x0A, 0xF7,
4, _AUTOINC, 0x31, 0x04,
4, _AUTOINC, 0x33, 0x00,
6, _AUTOINC, 0x35, 0x14, 0x00, 0x00,
6, _AUTOINC, 0x35, 0x13, 0x00, 0x82,
6, _AUTOINC, 0x35, 0x15, 0x00, 0xFA,
6, _AUTOINC, 0x35, 0x16, 0x01, 0x84,
6, _AUTOINC, 0x35, 0x12, 0x02, 0x14,
6, _AUTOINC, 0x35, 0x12, 0x02, 0x88,
6, _AUTOINC, 0x35, 0x12, 0x02, 0xFC,
6, _AUTOINC, 0x35, 0x11, 0x03, 0x70,
6, _AUTOINC, 0x35, 0x11, 0x03, 0xE1,
6, _AUTOINC, 0x35, 0x10, 0x04, 0x52,
6, _AUTOINC, 0x35, 0x12, 0x04, 0xB8,
6, _AUTOINC, 0x35, 0x0F, 0x05, 0x2B,
6, _AUTOINC, 0x35, 0x12, 0x05, 0x8D,
6, _AUTOINC, 0x35, 0x0F, 0x06, 0x00,
6, _AUTOINC, 0x35, 0x0E, 0x06, 0x63,
6, _AUTOINC, 0x35, 0x0C, 0x06, 0xBE,
6, _AUTOINC, 0x35, 0x0C, 0x07, 0x0C,
6, _AUTOINC, 0x35, 0x0A, 0x07, 0x59,
6, _AUTOINC, 0x35, 0x0E, 0x07, 0x99,
6, _AUTOINC, 0x35, 0x0D, 0x07, 0xCB,
6, _AUTOINC, 0x35, 0x0B, 0x07, 0xFB,
6, _AUTOINC, 0x35, 0x0D, 0x08, 0x55,
6, _AUTOINC, 0x35, 0x0F, 0x08, 0x92,
6, _AUTOINC, 0x35, 0x0D, 0x08, 0xD5,
6, _AUTOINC, 0x35, 0x0C, 0x09, 0x18,
6, _AUTOINC, 0x35, 0x0F, 0x09, 0x4E,
6, _AUTOINC, 0x35, 0x0F, 0x09, 0x8E,
6, _AUTOINC, 0x35, 0x0D, 0x09, 0xDD,
6, _AUTOINC, 0x35, 0x10, 0x0A, 0x1E,
6, _AUTOINC, 0x35, 0x10, 0x0A, 0x69,
6, _AUTOINC, 0x35, 0x0C, 0x0A, 0xBA,
6, _AUTOINC, 0x35, 0x10, 0x0A, 0xF7,
4, _AUTOINC, 0x31, 0x05,
4, _AUTOINC, 0x33, 0x00,
6, _AUTOINC, 0x35, 0x12, 0x00, 0x00,
6, _AUTOINC, 0x35, 0x12, 0x00, 0x74,
6, _AUTOINC, 0x35, 0x12, 0x00, 0xE3,
6, _AUTOINC, 0x35, 0x13, 0x01, 0x5A,
6, _AUTOINC, 0x35, 0x11, 0x01, 0xD5,
6, _AUTOINC, 0x35, 0x11, 0x02, 0x42,
6, _AUTOINC, 0x35, 0x11, 0x02, 0xAF,
6, _AUTOINC, 0x35, 0x10, 0x03, 0x1C,
6, _AUTOINC, 0x35, 0x10, 0x03, 0x87,
6, _AUTOINC, 0x35, 0x10, 0x03, 0xF3,
6, _AUTOINC, 0x35, 0x10, 0x04, 0x59,
6, _AUTOINC, 0x35, 0x0F, 0x04, 0xC5,
6, _AUTOINC, 0x35, 0x11, 0x05, 0x29,
6, _AUTOINC, 0x35, 0x0F, 0x05, 0x95,
6, _AUTOINC, 0x35, 0x0F, 0x05, 0xFA,
6, _AUTOINC, 0x35, 0x0F, 0x06, 0x5C,
6, _AUTOINC, 0x35, 0x0E, 0x06, 0xBC,
6, _AUTOINC, 0x35, 0x0B, 0x07, 0x18,
6, _AUTOINC, 0x35, 0x0E, 0x07, 0x5B,
6, _AUTOINC, 0x35, 0x0E, 0x07, 0x8D,
6, _AUTOINC, 0x35, 0x0E, 0x07, 0xC2,
6, _AUTOINC, 0x35, 0x0E, 0x08, 0x32,
6, _AUTOINC, 0x35, 0x0F, 0x08, 0x72,
6, _AUTOINC, 0x35, 0x0F, 0x08, 0xB8,
6, _AUTOINC, 0x35, 0x0D, 0x09, 0x04,
6, _AUTOINC, 0x35, 0x0F, 0x09, 0x40,
6, _AUTOINC, 0x35, 0x10, 0x09, 0x80,
6, _AUTOINC, 0x35, 0x0E, 0x09, 0xD0,
6, _AUTOINC, 0x35, 0x10, 0x0A, 0x17,
6, _AUTOINC, 0x35, 0x10, 0x0A, 0x60,
6, _AUTOINC, 0x35, 0x0E, 0x0A, 0xB1,
6, _AUTOINC, 0x35, 0x10, 0x0A, 0xF7,
4, _AUTOINC, 0x31, 0x06,
4, _AUTOINC, 0x33, 0x00,
6, _AUTOINC, 0x35, 0x10, 0x00, 0x00,
6, _AUTOINC, 0x35, 0x10, 0x00, 0x66,
6, _AUTOINC, 0x35, 0x10, 0x00, 0xC8,
6, _AUTOINC, 0x35, 0x10, 0x01, 0x31,
6, _AUTOINC, 0x35, 0x10, 0x01, 0x97,
6, _AUTOINC, 0x35, 0x10, 0x01, 0xFD,
6, _AUTOINC, 0x35, 0x10, 0x02, 0x63,
6, _AUTOINC, 0x35, 0x10, 0x02, 0xC9,
6, _AUTOINC, 0x35, 0x10, 0x03, 0x2E,
6, _AUTOINC, 0x35, 0x10, 0x03, 0x94,
6, _AUTOINC, 0x35, 0x10, 0x03, 0xFA,
6, _AUTOINC, 0x35, 0x10, 0x04, 0x60,
6, _AUTOINC, 0x35, 0x10, 0x04, 0xC6,
6, _AUTOINC, 0x35, 0x10, 0x05, 0x2B,
6, _AUTOINC, 0x35, 0x10, 0x05, 0x91,
6, _AUTOINC, 0x35, 0x10, 0x05, 0xF7,
6, _AUTOINC, 0x35, 0x10, 0x06, 0x5D,
6, _AUTOINC, 0x35, 0x10, 0x06, 0xC3,
6, _AUTOINC, 0x35, 0x10, 0x07, 0x21,
6, _AUTOINC, 0x35, 0x10, 0x07, 0x58,
6, _AUTOINC, 0x35, 0x10, 0x07, 0x91,
6, _AUTOINC, 0x35, 0x10, 0x08, 0x0D,
6, _AUTOINC, 0x35, 0x10, 0x08, 0x55,
6, _AUTOINC, 0x35, 0x10, 0x08, 0x9C,
6, _AUTOINC, 0x35, 0x10, 0x08, 0xEC,
6, _AUTOINC, 0x35, 0x10, 0x09, 0x32,
6, _AUTOINC, 0x35, 0x10, 0x09, 0x73,
6, _AUTOINC, 0x35, 0x10, 0x09, 0xC3,
6, _AUTOINC, 0x35, 0x10, 0x0A, 0x11,
6, _AUTOINC, 0x35, 0x10, 0x0A, 0x58,
6, _AUTOINC, 0x35, 0x10, 0x0A, 0xA8,
6, _AUTOINC, 0x35, 0x10, 0x0A, 0xF7,
4, _AUTOINC, 0x31, 0x07,
4, _AUTOINC, 0x33, 0x00,
6, _AUTOINC, 0x35, 0x07, 0x00, 0x00,
6, _AUTOINC, 0x35, 0x0F, 0x00, 0x31,
6, _AUTOINC, 0x35, 0x0E, 0x00, 0x92,
6, _AUTOINC, 0x35, 0x0C, 0x00, 0xF3,
6, _AUTOINC, 0x35, 0x12, 0x01, 0x41,
6, _AUTOINC, 0x35, 0x0D, 0x01, 0xB9,
6, _AUTOINC, 0x35, 0x0E, 0x02, 0x10,
6, _AUTOINC, 0x35, 0x11, 0x02, 0x6E,
6, _AUTOINC, 0x35, 0x0D, 0x02, 0xDE,
6, _AUTOINC, 0x35, 0x10, 0x03, 0x35,
6, _AUTOINC, 0x35, 0x0D, 0x03, 0x9C,
6, _AUTOINC, 0x35, 0x0D, 0x03, 0xF2,
6, _AUTOINC, 0x35, 0x0D, 0x04, 0x49,
6, _AUTOINC, 0x35, 0x10, 0x04, 0x9F,
6, _AUTOINC, 0x35, 0x10, 0x05, 0x06,
6, _AUTOINC, 0x35, 0x10, 0x05, 0x6E,
6, _AUTOINC, 0x35, 0x10, 0x05, 0xD5,
6, _AUTOINC, 0x35, 0x10, 0x06, 0x3D,
6, _AUTOINC, 0x35, 0x1B, 0x06, 0x9C,
6, _AUTOINC, 0x35, 0x16, 0x06, 0xFA,
6, _AUTOINC, 0x35, 0x10, 0x07, 0x4A,
6, _AUTOINC, 0x35, 0x18, 0x07, 0xC8,
6, _AUTOINC, 0x35, 0x0D, 0x08, 0x34,
6, _AUTOINC, 0x35, 0x10, 0x08, 0x6F,
6, _AUTOINC, 0x35, 0x12, 0x08, 0xC2,
6, _AUTOINC, 0x35, 0x11, 0x09, 0x14,
6, _AUTOINC, 0x35, 0x0D, 0x09, 0x5B,
6, _AUTOINC, 0x35, 0x13, 0x09, 0x9D,
6, _AUTOINC, 0x35, 0x12, 0x09, 0xFC,
6, _AUTOINC, 0x35, 0x11, 0x0A, 0x50,
6, _AUTOINC, 0x35, 0x10, 0x0A, 0xA8,
6, _AUTOINC, 0x35, 0x10, 0x0A, 0xF7,
4, _AUTOINC, 0x31, 0x00,
4, _AUTOINC, 0x33, 0x00,
4, _AUTOINC, 0x39, 0x00,

// CDM
19, _AUTOINC, 0xD0, 0x00, 0x03, 0x06, 0x43, 0x06, 0x83, 0x06, 0x03, 0x07, 0x04, 0x07, 0x44, 0x07, 0x84, 0x07, 0x04,
19, _AUTOINC, 0xE0, 0x00, 0x00, 0x00, 0x66, 0x00, 0xCC, 0x01, 0x01, 0x01, 0x97, 0x01, 0xFD, 0x02, 0x63, 0x02, 0x01,
4, _AUTOINC, 0xF0, 0x03,

//TM Blending Factor
4, _AUTOINC, 0x3B, 0x40,

// sharpness
19, _AUTOINC, 0x40, 0x5B, 0x5B, 0x5B, 0x5B, 0x5B, 0x5D, 0x61, 0x6B, 0x72, 0x7B, 0x82, 0x88, 0x88, 0x88, 0x82, 0x7B,
19, _AUTOINC, 0x50, 0x72, 0x58, 0x3E, 0x24, 0x10, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
4, _AUTOINC, 0x60, 0x00,
4, _AUTOINC, 0x63, 0x05,
19, _AUTOINC, 0x70, 0xDC, 0xC8, 0xB4, 0xA3, 0x94, 0x88, 0x7D, 0x73, 0x69, 0x64, 0x5F, 0x5C, 0x59, 0x57, 0x55, 0x53,
19, _AUTOINC, 0x80, 0x51, 0x50, 0x50, 0x50, 0x50, 0x50, 0x50, 0x50, 0x50, 0x50, 0x50, 0x50, 0x50, 0x50, 0x50, 0x50,
4, _AUTOINC, 0x90, 0x50,
4, _AUTOINC, 0x93, 0x03,

4, _AUTOINC, 0x30, 0xC0,
_END,
#endif
