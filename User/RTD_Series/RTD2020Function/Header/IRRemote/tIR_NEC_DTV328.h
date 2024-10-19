    // Start modulation length
    0x6D,                           // P23_A0_IR_PSR0

    // "0"/"1" modulation length
    0x13,                           // P23_A1_IR_PSR1, org 0x1A

    // "0" silence length
    0x13,                           // P23_A2_IR_PSR2, org 0x1A

    // "1" silence length
    0x3C,                           // P23_A3_IR_PSR3, org 0x50

    // Reserved------------
    0x00,                           // P23_A4_IR_PER0

    // Debounce
    0x00,                           // P23_A5_IR_PER1, org 0x03

    // Repeat silence
    0x17,                           // P23_A6_IR_PER2

    // Start silence length
    0x36,                           // P23_A7_IR_PER3

    // Idle time
    0xFF,                           // P23_A8_IR_SF0

    // One command time
    0x7D,                           // P23_A9_IR_SF1

    //----------------------------------------------

    // Time between 2 commands
    0x02,                           // P23_AE_IR_DPIR2, org 0x13
    0xB0,                           // P23_AF_IR_DPIR3, org 0x9F

    // _BIT7 IR soft reset
    0x00,                           // P23_B0_IR_CR0

    // _BIT7 Panasonic 48bit enable; _BIT5~_BIT0 48bit Extended data number
    0x00,                           // P23_B1_IR_CR1

    // _BIT3 Modulation Length Adjustable Enable; _BIT1 IR RX Endian Select
    0x00,                           // P23_B2_IR_CR2

    // _BTI7 Length mode; _BIT6 Enable burst; _BIT4~_BIT0 data bits
    (_BIT7 | _BIT6 | 0x1F),         // P23_B3_IR_CR3

    //----------------------------------------------

    // Start modulation up level
    0x77,                           // P23_D0_IR_PSR_UP0

    // "0"/"1" modulation length up level
    0x24,                           // P23_D1_IR_PSR_UP1, org 0x1E

    // "0" silence length up level
    0x24,                           // P23_D2_IR_PSR_UP2, org 0x1E

    // "1" silence length up level
    0x6E,                           // P23_D3_IR_PSR_UP3, org 0x64

    // Reserved------------
    0x00,                           // P23_D4_IR_PER_UP0

    // Reserved------------
    0x00,                           // P23_D5_IR_PER_UP1

    // Repeat length up level
    0x1F,                           // P23_D6_IR_PER_UP2

    // Start silence length up level
    0x3E,                           // P23_D7_IR_PER_UP3

    //----------------------------------------------

    // BIT1 Toshiba_en; BIT0 Philip RC6_en
    0x00,                           // P23_DA_IR_CTRL_RC62

    // RC6 mode Trailer Bit Length
    0x00,                           // P23_DB_IR_CTRL_RC63
