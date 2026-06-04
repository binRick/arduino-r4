/*
 * jp-is-ironman — on the Arduino UNO R4 WiFi's built-in 12x8 LED matrix,
 * repeatedly holds a static "JP" for 3 seconds, then scrolls
 * "JP IS IRONMAN" across it, looping forever.
 */
#include "ArduinoGraphics.h"
#include "Arduino_LED_Matrix.h"

ArduinoLEDMatrix matrix;

const char message[] = "JP IS IRONMAN    ";  // trailing spaces = gap before loop

// Static "JP" splash, 8 rows x 12 columns. 1 = LED on.
uint8_t jp[8][12] = {
  { 0,0,0,0,0, 0, 0,0,0,0,0,0 },
  { 0,1,1,1,1, 0, 0,1,1,1,0,0 },  // J top bar  | P top
  { 0,0,0,1,0, 0, 0,1,0,0,1,0 },  // J stem     | P sides
  { 0,0,0,1,0, 0, 0,1,0,0,1,0 },  // J stem     | P sides
  { 0,0,0,1,0, 0, 0,1,1,1,0,0 },  // J stem     | P bowl close
  { 0,1,0,1,0, 0, 0,1,0,0,0,0 },  // J hook tip | P stem
  { 0,1,1,1,0, 0, 0,1,0,0,0,0 },  // J hook     | P stem
  { 0,0,0,0,0, 0, 0,0,0,0,0,0 },
};

void setup() {
  matrix.begin();
}

void loop() {
  // 1) Hold the static "JP" for 3 seconds.
  matrix.renderBitmap(jp, 8, 12);
  delay(3000);

  // 2) Scroll "JP IS IRONMAN" once across the matrix.
  matrix.beginDraw();
  matrix.stroke(0xFFFFFFFF);
  matrix.textScrollSpeed(60);   // ms per pixel step (lower = faster)
  matrix.textFont(Font_5x7);
  matrix.beginText(0, 1, 0xFFFFFF);
  matrix.println(message);
  matrix.endText(SCROLL_LEFT);
  matrix.endDraw();
}
