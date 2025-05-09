#include "system.h"
#include "lcd.h"
#include "spi.h"
#include "gpio.h"

#define PC_LCD_WIDTH 320
#define PC_LCD_HEIGHT 320
#define PC_LCD_SPI_BUS 1
#define PC_LCD_BPP 16
#define PC_LCD_SCK 10
#define PC_LCD_MOSI 11
#define PC_LCD_MISO 12
#define PC_LCD_CS 13
#define PC_LCD_DC 14
#define PC_LCD_RST 15
#define PC_LCD_DEFAULT_SPEED 50000000  // Reduced from 50MHz to 10MHz for more reliable communication
#define PC_LCD_SPI_TIMEOUT 1000

#define max(a,b)             \
({                           \
    __typeof__ (a) _a = (a); \
    __typeof__ (b) _b = (b); \
    _a > _b ? _a : _b;       \
})

#define min(a,b)             \
({                           \
    __typeof__ (a) _a = (a); \
    __typeof__ (b) _b = (b); \
    _a < _b ? _a : _b;       \
})

#define PC_LCD_CMD(COMMAND, ...) {                               \
  uint8_t args[] = {__VA_ARGS__};                                \
  pc_lcd_command(COMMAND, args, sizeof(args) / sizeof(uint8_t)); \
}

/**
 * Send a command and arguments to the display
 */
void pc_lcd_command(uint8_t command, uint8_t *args, size_t arg_len) {
  int result;
  
  km_gpio_write(PC_LCD_DC, 0);
  km_gpio_write(PC_LCD_CS, 0);
  
  uint8_t commandBuffer[1] = {command};
  result = km_spi_send(PC_LCD_SPI_BUS, commandBuffer, 1, PC_LCD_SPI_TIMEOUT);
  if (result < 0) {
    // Handle error - in production code you might want to log this
    km_gpio_write(PC_LCD_CS, 1); // Make sure to release CS on error
    return;
  }

  if (arg_len > 0) {
    km_gpio_write(PC_LCD_DC, 1);
    
    result = km_spi_send(PC_LCD_SPI_BUS, args, arg_len, PC_LCD_SPI_TIMEOUT);
    if (result < 0) {
      // Handle error
      km_gpio_write(PC_LCD_CS, 1); // Make sure to release CS on error
      return;
    }
  }

  km_gpio_write(PC_LCD_CS, 1);
}

/**
 * Send just a command with no arguments
 */
void pc_lcd_command_1(uint8_t command) {
  pc_lcd_command(command, NULL, 0);
}

/**
 * Initialize SPI bus and related pins
 */
void pc_lcd_bus_init() {
  // Configure GPIO pins as outputs first
  km_gpio_set_io_mode(PC_LCD_CS, KM_GPIO_IO_MODE_OUTPUT);
  km_gpio_set_io_mode(PC_LCD_RST, KM_GPIO_IO_MODE_OUTPUT);
  km_gpio_set_io_mode(PC_LCD_DC, KM_GPIO_IO_MODE_OUTPUT);
  
  // Set initial pin states
  km_gpio_write(PC_LCD_CS, 1);
  km_gpio_write(PC_LCD_RST, 1);
  km_gpio_write(PC_LCD_DC, 1);

  // Setup SPI bus
  km_spi_setup(
    PC_LCD_SPI_BUS,
    KM_SPI_MODE_0,
    PC_LCD_DEFAULT_SPEED,
    KM_SPI_BITORDER_MSB,
    (km_spi_pins_t) {
      .miso = PC_LCD_MISO,
      .mosi = PC_LCD_MOSI,
      .sck = PC_LCD_SCK
    },
    KM_SPI_DATA_NOPULL
  );
}

/**
 * Reset the LCD hardware
 */
void pc_lcd_hw_reset() {
  km_gpio_write(PC_LCD_RST, 1);
  km_delay(10);
  km_gpio_write(PC_LCD_RST, 0);
  km_delay(10);
  km_gpio_write(PC_LCD_RST, 1);
  km_delay(200);
}

/**
 * Initialize the LCD hardware
 */
void pc_lcd_hw_init() {
  // Positive Gamma Control
  PC_LCD_CMD(
    PC_LCD_PGAMCTRL,
    0x00, 0x03, 0x09, 0x08, 0x16, 0x0A, 0x3F, 0x78,
    0x4C, 0x09, 0x0A, 0x08, 0x16, 0x1A, 0x0F
  );

  // Negative Gamma Control
  PC_LCD_CMD(
    PC_LCD_NGAMCTRL,
    0x00, 0x16, 0x19, 0x03, 0x0F, 0x05, 0x32, 0x45,
    0x46, 0x04, 0x0E, 0x0D, 0x35, 0x37, 0x0F
  );

  // Power Control 1
  PC_LCD_CMD(PC_LCD_PWCTRL1, 0x17, 0x15);

  // Power Control 2
  PC_LCD_CMD(PC_LCD_PWCTRL2, 0x41);

  // VCOM Control
  PC_LCD_CMD(PC_LCD_VMCTRL, 0x00, 0x12, 0x80);

  // Memory Access Control
  // MY, MX, MV, ML, BGR, MH, X, X
  // MY = Row Address Order
  // MX = Column Address Order
  // MV = Row/Column Exchange
  // ML = Vertical Refresh Order
  // BGR = Color Order
  // MH = Horizontal Refresh Order
  PC_LCD_CMD(PC_LCD_MADCTL, 0b01001000);

  // Interface Pixel Format
  // [X] DPI[000] [X] DBI[111]
  // DPI = RGB interface format (unused)
  // DBI = MCU interface format; 3bpp=0b001, 16bpp=0b101, 18bpp=0b110, 24bpp=0b111
  PC_LCD_CMD(PC_LCD_COLMOD, 0b101);

  // Interface Mode Control
  // SDA_EN[0] [000] VSPL[0] HSPL[0] DPL[0] EPL[0]
  // SDA_EN = 0 = DIN/SDO used for 3/4 serial interface
  // VSPL = 0 = vsync polarity: low
  // HSPL = 0 = hsync polarity: low
  // DPL = 0 = DOTCLK polarity: fetched at rising time
  // EPL = 0 = ENABLE polarity: high enable for RGB interface
  PC_LCD_CMD(PC_LCD_IFMODE, 0x00);

  // Frame Rate Control; no-tearing / tearing
  // 0b1110 - framerate = 91.15 / 87.53
  // 0b1010 - framerate = 60.76 / 58.35
  // 0b0 - framerate = 28.78 / 27.64
  PC_LCD_CMD(PC_LCD_FRMCTR1, 0b1110);

  // Display Inversion Off
  pc_lcd_command_1(PC_LCD_INVOFF);

  // Display Function Control
  // 0x02 = AGND -> source/VCOM output in non-display area
  // 0x02 = scan cycle 5 frames -> 84ms
  // 0x3B = 59 -> 8 * (59 + 1) = 8 * 60 = 480 lines to drive
  PC_LCD_CMD(PC_LCD_DISCTRL, 0x02, 0x02, 0x3B);

  // Entry Mode Set
  // 0xC6 = EPF[11] [00] DSTB[0] GON[1] DTE[1] GAS[0]
  // EPF = data format when 16/18bpp is stored in internal gram; do conditional copy
  // DSTB = deep standby mode enable
  // GON/DTE = output level of gate driver G1-G480 = 1/1 = normal display
  // GAS = low voltage detection control = enable
  PC_LCD_CMD(PC_LCD_ETMOD, 0xC6);

  // Set Image Function
  // 0x00 disable 24-bit data bus
  PC_LCD_CMD(PC_LCD_SETIMAGE, 0x00);

  // Exit Sleep
  pc_lcd_command_1(PC_LCD_SLPOUT);
  // km_delay(120);

  // Display On
  pc_lcd_command_1(PC_LCD_DISPON);
  // km_delay(120);
}

/**
 * Define a display region for read or write
 */
void pc_display_define_region(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, int write) {
  uint8_t coords[4];
  uint8_t cmd;
  int result;

  km_gpio_write(PC_LCD_CS, 0);
  
  km_gpio_write(PC_LCD_DC, 0);
  cmd = PC_LCD_CASET;
  result = km_spi_send(PC_LCD_SPI_BUS, &cmd, 1, PC_LCD_SPI_TIMEOUT);
  if (result < 0) {
    km_gpio_write(PC_LCD_CS, 1); // Release CS on error
    return;
  }

  km_gpio_write(PC_LCD_DC, 1);
  coords[0] = (uint8_t)(x1 >> 8) & 0xFF;
  coords[1] = (uint8_t)(x1) & 0xFF;
  coords[2] = (uint8_t)(x2 >> 8) & 0xFF;
  coords[3] = (uint8_t)(x2) & 0xFF;
  result = km_spi_send(PC_LCD_SPI_BUS, coords, 4, PC_LCD_SPI_TIMEOUT);
  if (result < 0) {
    km_gpio_write(PC_LCD_CS, 1); // Release CS on error
    return;
  }

  km_gpio_write(PC_LCD_DC, 0);
  cmd = PC_LCD_PASET;
  result = km_spi_send(PC_LCD_SPI_BUS, &cmd, 1, PC_LCD_SPI_TIMEOUT);
  if (result < 0) {
    km_gpio_write(PC_LCD_CS, 1); // Release CS on error
    return;
  }

  km_gpio_write(PC_LCD_DC, 1);
  coords[0] = (uint8_t)(y1 >> 8) & 0xFF;
  coords[1] = (uint8_t)(y1) & 0xFF;
  coords[2] = (uint8_t)(y2 >> 8) & 0xFF;
  coords[3] = (uint8_t)(y2) & 0xFF;
  result = km_spi_send(PC_LCD_SPI_BUS, coords, 4, PC_LCD_SPI_TIMEOUT);
  if (result < 0) {
    km_gpio_write(PC_LCD_CS, 1); // Release CS on error
    return;
  }

  // Set memory write/read command
  km_gpio_write(PC_LCD_DC, 0);
  if (write == 1) {
    cmd = PC_LCD_RAMWR;
    result = km_spi_send(PC_LCD_SPI_BUS, &cmd, 1, PC_LCD_SPI_TIMEOUT);
  }
  else {
    cmd = PC_LCD_RAMRD;
    result = km_spi_send(PC_LCD_SPI_BUS, &cmd, 1, PC_LCD_SPI_TIMEOUT);
  }
  
  if (result < 0) {
    km_gpio_write(PC_LCD_CS, 1); // Release CS on error
    return;
  }

  // DC and not CS is intentional
  // the fill function using this will write data and end CS.
  km_gpio_write(PC_LCD_DC, 1);
}

/**
 * fill a rect
 */
void pc_display_fill_rect(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color) {
  if (x >= PC_LCD_WIDTH || y >= PC_LCD_HEIGHT) return;

  uint16_t x2 = min(PC_LCD_WIDTH - 1,  x + width - 1);
  uint16_t y2 = min(PC_LCD_HEIGHT - 1, y + height - 1);

  // int16_t x2 = x + width - 1;
  // int16_t y2 = y + height - 1;

  if (x < 0) x = 0;
  if (y < 0) y = 0;

  if (x > x2 || y > y2) return;

  pc_display_define_region(x, y, x2, y2, 1);

  // generate fill pattern and row buffer
  uint8_t fill[2] = {
    (uint8_t)(color >> 8) & 0xFF,
    (uint8_t)(color) & 0xFF
  };
  size_t lineBufferLength = (x2 - x + 1) * 2;
  uint8_t lineBuffer[lineBufferLength];
  for (uint16_t i = 0; i < lineBufferLength; i += 2) {
    lineBuffer[i] =     fill[0];
    lineBuffer[i + 1] = fill[1];
  }

  // fill rows
  for (uint16_t cy = y; cy <= y2; cy++) {
    km_spi_send(PC_LCD_SPI_BUS, lineBuffer, lineBufferLength, 5000);
  }

  km_gpio_write(PC_LCD_CS, 1);
}

void pc_lcd_init() {
  pc_lcd_bus_init();
  pc_lcd_hw_reset();
  pc_lcd_hw_init();

  km_delay(100);
  pc_display_fill_rect(0,   0,  PC_LCD_WIDTH, PC_LCD_HEIGHT, PC_COLOR_CYAN);

  // pc_display_fill_rect(20,  20, 50,  50,  PC_COLOR_RED);
  // pc_display_fill_rect(70,  30, 50,  50,  PC_COLOR_GREEN);
  // pc_display_fill_rect(120, 40, 50,  50,  PC_COLOR_BLUE);
}

void pc_lcd_cleanup() {
  km_spi_close(PC_LCD_SPI_BUS); // bus_deinit
}