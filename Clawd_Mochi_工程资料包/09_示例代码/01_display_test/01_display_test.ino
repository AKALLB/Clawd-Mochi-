/*
  Clawd Mochi 最小屏幕测试程序
  作用：验证 ESP32-C3 SuperMini 与 1.54" ST7789 240x240 屏幕接线是否正确。

  接线：
  VCC -> 3V3
  GND -> GND
  SDA -> GPIO10
  SCL -> GPIO8
  RES -> GPIO2
  DC  -> GPIO1
  CS  -> GPIO4
  BL  -> GPIO3
*/

#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>

#define TFT_CS   4
#define TFT_DC   1
#define TFT_RST  2
#define TFT_BLK  3
#define TFT_MOSI 10
#define TFT_SCLK 8

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

void setup() {
  pinMode(TFT_BLK, OUTPUT);
  digitalWrite(TFT_BLK, HIGH);

  SPI.begin(TFT_SCLK, -1, TFT_MOSI, TFT_CS);
  tft.init(240, 240, SPI_MODE3);
  tft.setRotation(0);

  tft.fillScreen(ST77XX_ORANGE);
  delay(500);
  tft.fillScreen(ST77XX_BLACK);

  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(2);
  tft.setCursor(20, 40);
  tft.println("Clawd Mochi");
  tft.setCursor(20, 80);
  tft.println("Display OK");

  // 两只方块眼睛
  tft.fillRect(55, 135, 35, 60, ST77XX_ORANGE);
  tft.fillRect(150, 135, 35, 60, ST77XX_ORANGE);
}

void loop() {
  // 简单眨眼动画
  delay(900);
  tft.fillRect(55, 160, 35, 8, ST77XX_BLACK);
  tft.fillRect(150, 160, 35, 8, ST77XX_BLACK);
  delay(120);
  tft.fillRect(55, 135, 35, 60, ST77XX_ORANGE);
  tft.fillRect(150, 135, 35, 60, ST77XX_ORANGE);
}
