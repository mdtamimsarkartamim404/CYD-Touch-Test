#include <Arduino.h>
#include <TFT_eSPI.h>
#include <XPT2046_Touchscreen.h>
#include <SPI.h>

TFT_eSPI tft = TFT_eSPI();

// ================= TOUCH PINS =================
#define TOUCH_SCLK 25
#define TOUCH_MISO 39
#define TOUCH_MOSI 32
#define TOUCH_CS   33
#define TOUCH_IRQ  36

SPIClass touchSPI(VSPI);
XPT2046_Touchscreen touch(TOUCH_CS, TOUCH_IRQ);

// ================= SCREEN =================
#define SCREEN_W 320
#define SCREEN_H 240

// ================= CALIBRATION =================
// Based on your actual readings

#define RAW_X_MIN 396
#define RAW_X_MAX 3634

#define RAW_Y_MIN 461
#define RAW_Y_MAX 3575

// ================= TOUCH =================
bool readTouch(int &x, int &y, int &z) {

  if (!touch.touched()) {
    return false;
  }

  TS_Point p = touch.getPoint();

  int rawX = p.x;
  int rawY = p.y;

  // X: Left -> Right
  x = map(
    rawX,
    RAW_X_MIN,
    RAW_X_MAX,
    0,
    SCREEN_W - 1
  );

  // Y: Top -> Bottom
  y = map(
    rawY,
    RAW_Y_MIN,
    RAW_Y_MAX,
    0,
    SCREEN_H - 1
  );

  // Keep inside screen
  x = constrain(x, 0, SCREEN_W - 1);
  y = constrain(y, 0, SCREEN_H - 1);

  z = p.z;

  return true;
}

// ================= SETUP =================
void setup() {

  Serial.begin(115200);
  delay(500);

  // TFT
  tft.init();
  tft.setRotation(1);

  // Backlight
  pinMode(21, OUTPUT);
  digitalWrite(21, HIGH);

  // Touch SPI
  touchSPI.begin(
    TOUCH_SCLK,
    TOUCH_MISO,
    TOUCH_MOSI,
    TOUCH_CS
  );

  touch.begin(touchSPI);

  // IMPORTANT:
  // Do NOT use touch.setRotation()
  // Manual calibration is being used.

  // Screen
  tft.fillScreen(TFT_BLACK);

  tft.setTextColor(TFT_CYAN, TFT_BLACK);
  tft.setTextSize(2);

  tft.setCursor(45, 20);
  tft.println("TOUCH TEST");

  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextSize(1);

  tft.setCursor(45, 50);
  tft.println("Touch anywhere on screen");

  tft.drawRect(
    0,
    0,
    SCREEN_W,
    SCREEN_H,
    TFT_DARKGREY
  );

  Serial.println();
  Serial.println("==============================");
  Serial.println("CYD TOUCH TEST");
  Serial.println("==============================");
}

// ================= LOOP =================
void loop() {

  static unsigned long lastTouch = 0;

  if (millis() - lastTouch < 80) {
    return;
  }

  int x, y, z;

  if (readTouch(x, y, z)) {

    lastTouch = millis();

    // Draw touch point
    tft.fillCircle(
      x,
      y,
      7,
      TFT_RED
    );

    tft.drawCircle(
      x,
      y,
      11,
      TFT_WHITE
    );

    // Information box
    tft.fillRect(
      5,
      180,
      150,
      50,
      TFT_BLACK
    );

    tft.setTextColor(TFT_GREEN, TFT_BLACK);
    tft.setTextSize(1);

    tft.setCursor(10, 185);
    tft.print("SCREEN X: ");
    tft.print(x);

    tft.setCursor(10, 200);
    tft.print("SCREEN Y: ");
    tft.print(y);

    tft.setCursor(10, 215);
    tft.print("PRESSURE: ");
    tft.print(z);

    // Serial
    TS_Point p = touch.getPoint();

    Serial.print("RAW X=");
    Serial.print(p.x);

    Serial.print(" RAW Y=");
    Serial.print(p.y);

    Serial.print("  ->  SCREEN X=");
    Serial.print(x);

    Serial.print(" Y=");
    Serial.print(y);

    Serial.print(" Z=");
    Serial.println(z);
  }
}