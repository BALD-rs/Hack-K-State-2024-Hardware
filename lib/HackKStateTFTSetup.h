//                            USER DEFINED SETTINGS
//   Set driver type, fonts to be loaded, pins used, and SPI control method, etc.
//
//   This file allows for defining the display and configuration settings for TFT_eSPI.

#define USER_SETUP_INFO "Pi Pico with Adafruit 1.8\" ST7735 TFT"

// ##################################################################################
//
// Section 1. Call up the right driver file and any options for it
//
// ##################################################################################

#define ST7735_DRIVER       // Use the ST7735 driver for the Adafruit 1.8" TFT display

// Set the width and height of the display in pixels
#define TFT_WIDTH  160
#define TFT_HEIGHT 128

// For ST7735 ONLY, define the type of display (use one option)
#define ST7735_BLACKTAB     // Common option for 160x128 displays; try others if colors appear incorrect

// If colors appear inverted (white shows as black), uncomment one of the following lines:
// #define TFT_INVERSION_ON
// #define TFT_INVERSION_OFF

// ##################################################################################
//
// Section 2. Define the pins that are used to interface with the display
//
// ##################################################################################

// Define pins for the SPI communication and control
#define TFT_MOSI 3           // GPIO 3 for SPI MOSI (DIN)
#define TFT_MISO 4           // GPIO 4 for SPI MISO (DOUT)
#define TFT_SCLK 2           // GPIO 2 for SPI Clock (SCK)
#define TFT_CS   5           // GPIO 5 for Chip Select (CS)
#define TFT_DC   6           // GPIO 6 for Data/Command Select (DC)
#define TFT_RST  7           // GPIO 7 for Reset (RST)

// Optional: define the frequency for SPI communication (27 MHz works well for ST7735)
#define SPI_FREQUENCY  27000000

// Reduced SPI frequency for reading TFT
#define SPI_READ_FREQUENCY  20000000

// Optional frequency for touch control if using an XPT2046-compatible touch screen controller
#define SPI_TOUCH_FREQUENCY  2500000

// ##################################################################################
//
// Section 3. Define the fonts that are to be used here
//
// ##################################################################################

// Define fonts to include in the compiled library
#define LOAD_GLCD   // Font 1. Basic font needs ~1820 bytes in FLASH
#define LOAD_FONT2  // Font 2. Small 16 pixel font, ~3534 bytes in FLASH
#define LOAD_FONT4  // Font 4. Medium 26 pixel font, ~5848 bytes in FLASH
#define LOAD_FONT6  // Font 6. Large 48 pixel font, ~2666 bytes in FLASH (0-9, a.m./p.m.)
#define LOAD_FONT7  // Font 7. 7 segment 48 pixel font, ~2438 bytes in FLASH (0-9)
#define LOAD_FONT8  // Font 8. Large 75 pixel font, ~3256 bytes in FLASH (0-9)

// Include FreeFonts library for access to Adafruit GFX free fonts FF1 to FF48 and custom fonts
#define LOAD_GFXFF

// Enable smooth fonts (saves ~20kB when disabled)
#define SMOOTH_FONT

// ##################################################################################
//
// Section 4. Other options
//
// ##################################################################################

// Uncomment to use the RP2040 PIO for SPI (may improve performance on Pi Pico)
// #define RP2040_PIO_SPI

// For RP2040 processors, define the SPI port channel used (default is 0 if undefined)
#define TFT_SPI_PORT 0 // Use SPI0 on Raspberry Pi Pico
