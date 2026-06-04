/*
 * jp-is-ironman — on the Arduino UNO R4 WiFi's built-in 12x8 LED matrix,
 * repeatedly holds a static "JP" for 3 seconds, then scrolls
 * "JP IS IRONMAN" across it, looping forever.
 */
#include "ArduinoGraphics.h"
#include "Arduino_LED_Matrix.h"

ArduinoLEDMatrix matrix;

const char message[] = "JP IS IRONMAN    ";  // trailing spaces = gap before loop

// Static splash: a compact "JP" flanked by little rose blooms (the red
// LEDs make them red roses). 8 rows x 12 cols, 1 = LED on.
//   cols 0-2 = left rose | 3-5 = J | 6-8 = P | 9-11 = right rose
uint8_t splash[8][12] = {
  { 0,0,0, 0,0,0, 0,0,0, 0,0,0 },
  { 0,0,0, 1,1,1, 1,1,1, 0,0,0 },
  { 0,1,0, 0,0,1, 1,0,1, 0,1,0 },
  { 1,1,1, 0,0,1, 1,0,1, 1,1,1 },
  { 1,1,1, 0,0,1, 1,1,1, 1,1,1 },
  { 0,1,0, 1,0,1, 1,0,0, 0,1,0 },
  { 0,0,0, 1,1,1, 1,0,0, 0,0,0 },
  { 0,0,0, 0,0,0, 0,0,0, 0,0,0 },
};

void setup() {
  matrix.begin();
}

void loop() {
  // 1) Draw the static "JP + roses" splash and hold it for 3 seconds.
  //    Drawn via point() (same graphics path as the scroll) so the two
  //    don't fight over the display.
  matrix.beginDraw();
  matrix.clear();
  matrix.stroke(0xFFFFFFFF);
  for (int y = 0; y < 8; y++) {
    for (int x = 0; x < 12; x++) {
      if (splash[y][x]) matrix.point(x, y);
    }
  }
  matrix.endDraw();
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
