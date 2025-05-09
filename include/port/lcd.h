#ifndef __PC_LCD_H
#define __PC_LCD_H

#define PC_COLOR_WHITE    (uint16_t)(0xFFFF)
#define PC_COLOR_BLACK    (uint16_t)(0x0)
#define PC_COLOR_RED      (uint16_t)(0b1111100000000000)
#define PC_COLOR_GREEN    (uint16_t)(0b0000011111100000)
#define PC_COLOR_BLUE     (uint16_t)(0b0000000000011111)
#define PC_COLOR_YELLOW   (uint16_t)(0b1111111111100000)
#define PC_COLOR_CYAN     (uint16_t)(0b0000011111111111)
#define PC_COLOR_MAGENTA  (uint16_t)(0b1111100000011111)
#define PC_COLOR_GRAY     (uint16_t)(0b1000010000010000)

/**
 * Initialize LCD when system started
 */
void pc_lcd_init();

/**
 * Clean up LCD stuff
 */
void pc_lcd_cleanup();

/**
 * fill a rect
 */
void pc_display_fill_rect(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color);

//
// STANDARD COMMANDS
//

/** NOOP - Do nothing; can be used to terminate frame memory write or read operations */
#define PC_LCD_NOP ((uint8_t)(0x00))

/** Software Reset */
#define PC_LCD_SWRESET ((uint8_t)(0x01))

/** Read Display Identification Information */
#define PC_LCD_RDID ((uint8_t)(0x04))

/** Read Number of the Errors on DSI */
#define PC_LCD_RDNUMED ((uint8_t)(0x05))

/** Read Display Status */
#define PC_LCD_RDDST ((uint8_t)(0x09))

/** Read Display Power Mode */
#define PC_LCD_RDDPM ((uint8_t)(0x0A))

/** Read Display MADCTL */
#define PC_LCD_RDDMADCTL ((uint8_t)(0x0B))

/** Read Display Pixel Format */
#define PC_LCD_RDDCOLMOD ((uint8_t)(0x0C))

/** Read Display Image Mode */
#define PC_LCD_RDDIM ((uint8_t)(0x0D))

/** Read Display Signal Mode */
#define PC_LCD_RDDSM ((uint8_t)(0x0E))

/** Read Display Self-Diagnostic Result */
#define PC_LCD_RDDSDR ((uint8_t)(0x0F))

/** Sleep IN */
#define PC_LCD_SLPIN ((uint8_t)(0x10))

/** Sleep OUT */
#define PC_LCD_SLPOUT ((uint8_t)(0x11))

/** Partial Mode ON */
#define PC_LCD_PTLON ((uint8_t)(0x12))

/** Normal Display Mode ON */
#define PC_LCD_NORON ((uint8_t)(0x13))

/** Display Inversion ON */
#define PC_LCD_INVON ((uint8_t)(0x20))

/** Display Inversion OFF */
#define PC_LCD_INVOFF ((uint8_t)(0x21))

/** All Pixels OFF */
#define PC_LCD_ALLPOFF ((uint8_t)(0x22))

/** All Pixels ON */
#define PC_LCD_ALLPON ((uint8_t)(0x23))

/** Display OFF */
#define PC_LCD_DISPOFF ((uint8_t)(0x28))

/** Display ON */
#define PC_LCD_DISPON ((uint8_t)(0x29))

/** Column Address Set */
#define PC_LCD_CASET ((uint8_t)(0x2A))

/** Page Address Set */
#define PC_LCD_PASET ((uint8_t)(0x2B))

/** Memory Write */
#define PC_LCD_RAMWR ((uint8_t)(0x2C))

/** Memory Read */
#define PC_LCD_RAMRD ((uint8_t)(0x2E))

/** Partial Area */
#define PC_LCD_PTLAR ((uint8_t)(0x30))

/** Vertical Scrolling Definition */
#define PC_LCD_VSCRDEF ((uint8_t)(0x33))

/** Tearing Effect Line Off */
#define PC_LCD_TEOFF ((uint8_t)(0x34))

/** Tearing Effect Line On (NOTE: listed in datasheet as "TEOFF" again, clearly in error) */
#define PC_LCD_TEON ((uint8_t)(0x35))

/** Memory Access Control */
#define PC_LCD_MADCTL ((uint8_t)(0x36))

/** Vertical Scrolling Start Address */
#define PC_LCD_VSCRSADD ((uint8_t)(0x37))

/** Idle Mode Off */
#define PC_LCD_IDMOFF ((uint8_t)(0x38))

/** Idle Mode On */
#define PC_LCD_IDMON ((uint8_t)(0x39))

/** Interface Pixel Format */
#define PC_LCD_COLMOD ((uint8_t)(0x3A))

/** Write Memory Continue */
#define PC_LCD_RAMWRC ((uint8_t)(0x3C))

/** Read Memory Continue */
#define PC_LCD_RAMRDRC ((uint8_t)(0x3E))

/** Write Tear Scan Line */
#define PC_LCD_TESLWR ((uint8_t)(0x44))

/** Read Scan Line */
#define PC_LCD_TESLRD ((uint8_t)(0x45))

/** Write Display Brightness Value */
#define PC_LCD_WRDISBV ((uint8_t)(0x51))

/** Read Display Brightness Value */
#define PC_LCD_RDDISBV ((uint8_t)(0x52))

/** Write CTRL Display Value */
#define PC_LCD_WRCTRLD ((uint8_t)(0x53))

/** Read CTRL Display Value */
#define PC_LCD_RDCTRLD ((uint8_t)(0x54))

/** Write Content Adaptive Brightness Control Value */
#define PC_LCD_WRCABC ((uint8_t)(0x55))

/** Read Content Adaptive Brightness Control Value */
#define PC_LCD_RDCABC ((uint8_t)(0x56))

/** Write CABC Minimum Brightness */
#define PC_LCD_WRCABCMB ((uint8_t)(0x5E))

/** Read CABC Minimum Brightness */
#define PC_LCD_RDCABCMB ((uint8_t)(0x5F))

/** Read Automatic Brightness Control Self-diagnostic Result */
#define PC_LCD_RDABCSDR ((uint8_t)(0x68))

/** Read ID1 */
#define PC_LCD_RDID1 ((uint8_t)(0xDA))

/** Read ID2 */
#define PC_LCD_RDID2 ((uint8_t)(0xDB))

/** Read ID3 */
#define PC_LCD_RDID3 ((uint8_t)(0xDC))

//
// EXTENDED COMMANDS (EXTC)
//

/** Interface Mode Control */
#define PC_LCD_IFMODE ((uint8_t)(0xB0))

/** Frame Rate Control (in Normal Mode/Full Colors) */
#define PC_LCD_FRMCTR1 ((uint8_t)(0xB1))

/** Frame Rate Control (in Idle Mode/8 Colors) */
#define PC_LCD_FRMCTR2 ((uint8_t)(0xB2))

/** Frame Rate Control (in Partial Mode/Full Colors) */
#define PC_LCD_FRMCTR3 ((uint8_t)(0xB3))

/** Display Inversion Control */
#define PC_LCD_INVTR ((uint8_t)(0xB4))

/** Blanking Porch Control */
#define PC_LCD_PRCTR ((uint8_t)(0xB5))

/** Display Function Control */
#define PC_LCD_DISCTRL ((uint8_t)(0xB6))

/** Entry Mode Set */
#define PC_LCD_ETMOD ((uint8_t)(0xB7))

/** Color Enhancement Control 1 */
#define PC_LCD_CECTRL1 ((uint8_t)(0xB9))

/** Color Enhancement Control 2 */
#define PC_LCD_CECTRL2 ((uint8_t)(0xBA))

/** HS Lanes Control */
#define PC_LCD_HSLCTRL ((uint8_t)(0xBE))

/** Power Control 1 */
#define PC_LCD_PWCTRL1 ((uint8_t)(0xC0))

/** Power Control 2 */
#define PC_LCD_PWCTRL2 ((uint8_t)(0xC1))

/** Power Control 3 (For Normal Mode) */
#define PC_LCD_PWCTRL3 ((uint8_t)(0xC2))

/** Power Control 4 (For Idle Mode) */
#define PC_LCD_PWCTRL4 ((uint8_t)(0xC3))

/** Power Control 5 (For Partial Mode) */
#define PC_LCD_PWCTRL5 ((uint8_t)(0xC4))

/** VCOM Control */
#define PC_LCD_VMCTRL ((uint8_t)(0xC5))

/** CABC Control 1 */
#define PC_LCD_CABCCTRL1 ((uint8_t)(0xC6))

/** CABC Control 2 */
#define PC_LCD_CABCCTRL2 ((uint8_t)(0xC8))

/** CABC Control 3 */
#define PC_LCD_CABCCTRL3 ((uint8_t)(0xC9))

/** CABC Control 4 */
#define PC_LCD_CABCCTRL4 ((uint8_t)(0xCA))

/** CABC Control 5 */
#define PC_LCD_CABCCTRL5 ((uint8_t)(0xCB))

/** CABC Control 6 */
#define PC_LCD_CABCCTRL6 ((uint8_t)(0xCC))

/** CABC Control 7 */
#define PC_LCD_CABCCTRL7 ((uint8_t)(0xCD))

/** CABC Control 8 */
#define PC_LCD_CABCCTRL8 ((uint8_t)(0xCE))

/** CABC Control 9 */
#define PC_LCD_CABCCTRL9 ((uint8_t)(0xCF))

/** NV Memory Write */
#define PC_LCD_NVMWR ((uint8_t)(0xD0))

/** NV Memory Protection Key */
#define PC_LCD_NVMPKEY ((uint8_t)(0xD1))

/** NV Memory Status Read (NOTE: Listed erroneously as DISON in datasheet) */
#define PC_LCD_NVMRD ((uint8_t)(0xD2))

/** Read ID4 (???) */
#define PC_LCD_RDID4 ((uint8_t)(0xD3))

/** Adjust Control 1 (NOTE: No corresponding short name in datasheet) */
#define PC_LCD_ADJCTRL1 ((uint8_t)(0xD7))

/** Read ID Version (NOTE: No corresponding short name in datasheet) */
#define PC_LCD_RDIDVER ((uint8_t)(0xD8))

/** Positive Gamma Control */
#define PC_LCD_PGAMCTRL ((uint8_t)(0xE0))

/** Negative Gamma Control */
#define PC_LCD_NGAMCTRL ((uint8_t)(0xE1))

/** Digital Gamma Control 1 */
#define PC_LCD_DGAMCTRL1 ((uint8_t)(0xE2))

/** Digital Gamma Control 2 */
#define PC_LCD_DGAMCTRL2 ((uint8_t)(0xE3))

/** Set Image Function */
#define PC_LCD_SETIMAGE ((uint8_t)(0xE9))

/**
 * Adjust Control 2 (NOTE: No corresponding short name in datasheet)
 * 
 * op-amp chopper function controls,
 * source eq internal timing adjustments,
 * slope function settings,
 * gate modulation timing control
 */
#define PC_LCD_ADJCTRL2 ((uint8_t)(0xF2))

/**
 * Adjust Control 3 (NOTE: No corresponding short name in datasheet)
 * 
 * DSI 18bit option
 */
#define PC_LCD_ADJCTRL3 ((uint8_t)(0xF7))

/**
 * Adjust Control 4 (NOTE: No corresponding short name in datasheet)
 * 
 * 3-gamma function enable,
 * dither enable
 */
#define PC_LCD_ADJCTRL4 ((uint8_t)(0xF8))

/**
 * Adjust Control 5 (NOTE: No corresponding short name in datasheet)
 * 
 * source op-amp chopper function option
 */
#define PC_LCD_ADJCTRL5 ((uint8_t)(0xF9))

/** SPI Read Command Setting (NOTE: No corresponding short name in datasheet) */
#define PC_LCD_SET_SPI_READCMD ((uint8_t)(0xFB))

/**
 * Adjust Control 6 (NOTE: No corresponding short name in datasheet)
 * 
 * gate driver non-overlap timing control
 */
#define PC_LCD_ADJCTRL6 ((uint8_t)(0xFC))

/**
 * Adjust Control 7 (NOTE: No corresponding short name in datasheet)
 * 
 * 24-axis adjustment enable signal for color enhance
 */
#define PC_LCD_ADJCTRL7 ((uint8_t)(0xFF))

#endif /* __PC_LCD_H */