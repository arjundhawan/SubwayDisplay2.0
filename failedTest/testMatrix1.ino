// REQUIRES the following Arduino libraries:
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
// - RGB matrix Panel Library: https://github.com/2dom/PxMatrix
// - Adafruit_GFX Library: https://github.com/adafruit/Adafruit-GFX-Library
// - esp8266 library (nodemcu) found at https://github.com/esp8266/Arduino
// - package_esp8266com_index.json found at http://arduino.esp8266.com/stable/package_esp8266com_index.json
// Find All "Great Projects" Videos : https://www.youtube.com/channel/UCCC8DuqicBtP3A_aC53HYDQ/videos

#include "Arduino.h"
#include <Adafruit_GFX.h>
#include <Fonts/FreeMonoBold12pt7b.h>
#include <PxMatrix.h>

#define P_LAT 16
#define P_A 5
#define P_B 4
#define P_C 15
#define P_D 12
#define P_OE 2

// Pins for LED MATRIX

#define matrix_width 64
#define matrix_height 32

//PxMATRIX display(matrix_width,matrix_height,P_LAT, P_OE,P_A,P_B,P_C);
PxMATRIX display(64,32,P_LAT, P_OE,P_A,P_B,P_C,P_D);
//PxMATRIX display(64,64,P_LAT, P_OE,P_A,P_B,P_C,P_D,P_E);


void setup() {
  Serial.begin(115200);
  delay(2000);
  // Define your display layout here, e.g. 1/8 step
  display.begin(16);

  // Define your scan pattern here {LINE, ZIGZAG, ZAGGIZ, WZAGZIG, VZAG} (default is LINE)
  //display.setScanPattern(LINE);

  // Define multiplex implemention here {BINARY, STRAIGHT} (default is BINARY)
  //display.setMuxPattern(BINARY);

  display.setFastUpdate(true);
  display.setRotation(0); // we don't wrap text so it scrolls nicely
  display.clearDisplay();
  display.println("Connecting");
}

void loop() {

}
