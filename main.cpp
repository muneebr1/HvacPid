
#include "Particle.h"
#include <Adafruit_GFX_RK.h>        // https://github.com/rickkas7/Adafruit_GFX_RK
#include "Arduino_ST7735_Fast.h"    // adapted from https://github.com/cbm80amiga/Arduino_ST7789_Fast
#include "RREFont.h"
#include "rre_8x12.h"
#include "rre_chicago_20x24.h"

// SYSTEM_MODE(AUTOMATIC) is default when not specified
SYSTEM_THREAD(ENABLED);

RREFont font;

/*
 ST7735 128x160 LCD pinout (header at the top for better viewwing angles, from left):
 #1 BL    -> 3.3V or unconnected
 #2 SCK   -> SCL
 #3 SDA   -> MOSI
 #4 DC    -> D6
 #5 RES   -> D5
 #6 CS    -> A2
 #7 GND   -> GND
 #8 VCC   -> 3.3V
*/

#define LCD_CS         A2

#define SCR_WD   128
#define SCR_HT   160

/********* ST7735 TFT Display Config *********/
#define TFT_CS  A2  // NOT USED - CS wired LOW on display board
#define TFT_DC  D6
#define TFT_RST D5  // NOTE: D4 is SPI1 MISO so cannot be used here

Arduino_ST7735 tft = Arduino_ST7735(TFT_DC, TFT_RST, TFT_CS);
uint16_t bgCol    = RGBto565(255,255,255);

void customRect(int x, int y, int w, int h, int c) { return tft.fillRect(x, y, w, h, c); }


void setup() 
{
  Serial.begin(115200);
 
  tft.begin();

  // Use this initializer if using a 1.8" TFT screen:
  //tft.initR(INITR_BLACKTAB);      // Init ST7735S chip, black tab

  // OR use this initializer if using a 1.8" TFT screen with offset such as WaveShare:
  tft.initR(INITR_GREENTAB);      // Init ST7735S chip, green tab

  tft.fillScreen(bgCol);

  Serial.begin(9600);

  font.init(customRect, SCR_WD, SCR_HT); // custom fillRect function and screen width and height values
//  font.setFont(&rre_8x12);
  font.setFont(&rre_chicago_20x24);

  font.setColor(255);
  
  font.printStr(ALIGN_LEFT,10,"Hello World!");  // center
  
}


void loop()
{
}

