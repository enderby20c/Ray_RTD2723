////////////////////////////////////////////
/////Local Contrast Temporal Setting //////
////////////////////////////////////////////
#if((_HW_LOCAL_CONTRAST_GEN_SEL == _LOCAL_CONTRAST_GEN_3) || (_HW_LOCAL_CONTRAST_GEN_SEL == _LOCAL_CONTRAST_GEN_4))
4, _AUTOINC, 0x9F, 0x32,
// Spatial Filter
9, _AUTOINC, 0x4D, 0xC2, 0x11, 0x10, 0x00, 0x00, 0x04,
// New Temporal filter
24, _AUTOINC, 0x5C, 0x07, 0x40, 0x60, 0x80, 0x00, 0x00, 0x99, 0x07, 0x40, 0x60, 0x80, 0x00, 0x00, 0x00, 0x0E, 0x0D, 0x0B, 0x08, 0x06, 0x08, 0x18,
8, _AUTOINC, 0x72, 0x00, 0x17, 0xE2, 0x02, 0x2B,
_END,
#endif
