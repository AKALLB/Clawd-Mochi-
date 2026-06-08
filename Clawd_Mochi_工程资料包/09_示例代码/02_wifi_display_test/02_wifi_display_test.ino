/*
  Clawd Mochi WiFi + 屏幕验证程序
  作用：验证屏幕、ESP32-C3 SoftAP、网页控制是否工作。
  连接 WiFi：Clawd-Mochi-Test
  密码：clawd1234
  浏览器打开：http://192.168.4.1
*/

#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
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
WebServer server(80);

const char* AP_SSID = "Clawd-Mochi-Test";
const char* AP_PASS = "clawd1234";

uint16_t bg = ST77XX_ORANGE;

void drawNormalEyes() {
  tft.fillScreen(bg);
  tft.fillRect(55, 85, 35, 75, ST77XX_BLACK);
  tft.fillRect(150, 85, 35, 75, ST77XX_BLACK);
}

void drawSquishEyes() {
  tft.fillScreen(bg);
  tft.setTextColor(ST77XX_BLACK);
  tft.setTextSize(8);
  tft.setCursor(40, 85);
  tft.print("><");
}

void drawCode() {
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_ORANGE);
  tft.setTextSize(3);
  tft.setCursor(36, 70);
  tft.print("Claude");
  tft.setTextColor(ST77XX_WHITE);
  tft.setCursor(58, 120);
  tft.print("Code");
}

void handleRoot() {
  String html = R"HTML(
<!doctype html><html><head><meta name='viewport' content='width=device-width,initial-scale=1'>
<title>Clawd Mochi Test</title>
<style>body{font-family:Arial;background:#111;color:#fff;text-align:center;padding:24px}button{font-size:20px;margin:10px;padding:14px 22px;border-radius:12px;border:0;background:#ff6a00;color:#111;font-weight:bold}</style>
</head><body>
<h1>Clawd Mochi Test</h1>
<p>如果你能看到这个页面，WiFi 和网页服务器正常。</p>
<button onclick="location.href='/normal'">Normal eyes</button><br>
<button onclick="location.href='/squish'">Squish eyes</button><br>
<button onclick="location.href='/code'">Claude Code</button><br>
<button onclick="location.href='/off'">Backlight off</button>
<button onclick="location.href='/on'">Backlight on</button>
</body></html>
)HTML";
  server.send(200, "text/html", html);
}

void setup() {
  pinMode(TFT_BLK, OUTPUT);
  digitalWrite(TFT_BLK, HIGH);

  Serial.begin(115200);
  SPI.begin(TFT_SCLK, -1, TFT_MOSI, TFT_CS);
  tft.init(240, 240, SPI_MODE3);
  tft.setRotation(0);
  drawNormalEyes();

  WiFi.mode(WIFI_AP);
  WiFi.softAP(AP_SSID, AP_PASS);

  server.on("/", handleRoot);
  server.on("/normal", [](){ drawNormalEyes(); server.sendHeader("Location", "/"); server.send(302, "text/plain", ""); });
  server.on("/squish", [](){ drawSquishEyes(); server.sendHeader("Location", "/"); server.send(302, "text/plain", ""); });
  server.on("/code", [](){ drawCode(); server.sendHeader("Location", "/"); server.send(302, "text/plain", ""); });
  server.on("/off", [](){ digitalWrite(TFT_BLK, LOW); server.sendHeader("Location", "/"); server.send(302, "text/plain", ""); });
  server.on("/on", [](){ digitalWrite(TFT_BLK, HIGH); server.sendHeader("Location", "/"); server.send(302, "text/plain", ""); });
  server.begin();

  Serial.println("Connect WiFi: Clawd-Mochi-Test / clawd1234");
  Serial.println("Open: http://192.168.4.1");
}

void loop() {
  server.handleClient();
}
