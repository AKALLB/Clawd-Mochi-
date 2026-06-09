#include <Adafruit_NeoPixel.h>

constexpr uint8_t RGB_PIN = 16;
constexpr uint8_t RGB_COUNT = 1;

Adafruit_NeoPixel rgb(RGB_COUNT, RGB_PIN, NEO_GRB + NEO_KHZ800);

void showColor(uint8_t red, uint8_t green, uint8_t blue) {
  rgb.setPixelColor(0, rgb.Color(red, green, blue));
  rgb.show();
  delay(500);
}

void setup() {
  Serial.begin(115200);
  rgb.begin();
  rgb.setBrightness(20);
  rgb.clear();
  rgb.show();
}

void loop() {
  Serial.println("RP2040-Zero board test: OK");
  showColor(255, 0, 0);
  showColor(0, 255, 0);
  showColor(0, 0, 255);
  showColor(0, 0, 0);
}
