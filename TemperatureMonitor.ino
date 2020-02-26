/*
TODO.... add info about connectors and pins
1.8" TFT display

BLK => 3.3V
CS => D10
DC => D9
RST => D8
SDA => D11
SCL => D12
VDD => 5V
GND => GND
*/

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>
#include <DHT.h> //Library for temperature sensor


/*DEFINE PIN FOR TFT DISPLAY*/
  #define TFT_CS         10
  #define TFT_RST        8
  #define TFT_DC         9


/*DEFINE PINS FOR DHT11*/
  #define DHTTYPE DHT11
  #define DHTPINCPU 7

  
  
 DHT dhtCPU(DHTPINCPU,DHTTYPE);
 Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

float p = 3.1415926;

void setup(void) {
  Serial.begin(9600);
  Serial.print(F("Hello! Arduino Stat meter of PC."));

  // Use this initializer if using a 1.8" TFT screen:
  tft.initR(INITR_BLACKTAB);      // Init ST7735S chip, black tab

  Serial.println(F("Initialized"));

  //Setting time
  uint16_t time = millis();
  tft.fillScreen(ST77XX_BLACK);
  time = millis() - time;

  /*
  Serial.println(time, DEC);
  delay(500);
*/

  /*INIT DHT */
  dhtCPU.begin();
  
  
  tft.setRotation(1); // rotating a display
  InitPrint();
  delay(4500);  
}

void loop() {
  // tft print function!
   tftPrintHWinfo();
   delay(5000);

/*
  tft.invertDisplay(true);
  delay(500);
  tft.invertDisplay(false);
  delay(500);
*/
}

void InitPrint()
{
  tft.setTextWrap(true);
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(0,5);
  
  tft.setTextColor(ST77XX_BLUE);
  tft.setTextSize(2);
  tft.println("HW INFO\nCPU\nGPU\nHDD\n");
  
  delay(4000);
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(0,5);
  tft.println("Created by\nPavel Sestak\n2020");
}
  

void tftPrintHWinfo()
{
  tft.setTextWrap(true); //allow wrap text
  tft.fillScreen(ST77XX_BLACK); //Clear display
  tft.setCursor(0,5);
  tft.setTextSize(1.5);
  tft.println("DEV | TEMP C | HUMI %"); //set head of table
  tft.println("");
  
  tft.setTextSize(2);
  
  tft.print("CPU: ");
  //todo read cpu meter
  int hum = dhtCPU.readHumidity();
  int tem = dhtCPU.readTemperature();
  tft.print(tem);
  tft.print("C ");
  tft.print(hum);
  tft.print("%\n");
  
  
  tft.print("GPU: ");
  //todo read cpu meter
  tft.print("hodnota\n");
  
  
  tft.print("HDD: ");
  //todo read cpu meter
  tft.print("hodnota\n");
  
  
  tft.setTextSize(1.5);
  tft.println("");
  tft.print("UPTIME: ");
  tft.print(millis()/1000);
  tft.print(" s\n");
  tft.println("Created by Pavel Sestak");  
}
