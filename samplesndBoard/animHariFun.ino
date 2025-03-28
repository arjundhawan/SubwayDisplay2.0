#include <PxMatrix.h>
#include <Fonts/FreeSansBoldOblique9pt7b.h>
#include <Fonts/FreeSansBoldOblique12pt7b.h>

#ifdef ESP32

#define P_LAT 22
#define P_A 19
#define P_B 23
#define P_C 18
#define P_D 5
#define P_E 15
#define P_OE 2
hw_timer_t * timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

#endif

#ifdef ESP8266

#include <Ticker.h>
Ticker display_ticker;
#define P_LAT 16
#define P_A 5
#define P_B 4
#define P_C 15
#define P_D 12
#define P_E 0
#define P_OE 2

#endif

// Pins for LED MATRIX
PxMATRIX display(64,32,P_LAT, P_OE,P_A,P_B,P_C,P_D,P_E);

#ifdef ESP8266
// ISR for display refresh
void display_updater()
{
  //display.displayTestPattern(70);
  display.display(70);
}
#endif

#ifdef ESP32
void IRAM_ATTR display_updater(){
  // Increment the counter and set the time of ISR
  portENTER_CRITICAL_ISR(&timerMux);
  //isplay.display(70);
  display.displayTestPattern(70);
  portEXIT_CRITICAL_ISR(&timerMux);
}
#endif

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  display.begin(16);
  
  #ifdef ESP8266
    display_ticker.attach(0.002, display_updater);
  #endif

  #ifdef ESP32
    timer = timerBegin(0, 80, true);
    timerAttachInterrupt(timer, &display_updater, true);
    timerAlarmWrite(timer, 2000, true);
    timerAlarmEnable(timer);
  #endif

  delay(1000);
}

void DisplayHariFun()
{
  display.fillScreen(display.color565(0, 0,0));
  
  display.setTextSize(1);
  
  display.setFont(&FreeSansBoldOblique9pt7b);
  display.setTextColor(display.color565(0, 0, 255));
  display.setCursor(14,31-18); display.print("Hari");
  
  display.setFont(&FreeSansBoldOblique12pt7b);
  display.setTextColor(display.color565(255,255,0));
  display.setCursor(31-26,31); display.print("FUN");
}

void Chord(int r, float rot)
{
  int nodes = 6;
  float x[nodes];
  float y[nodes];
  for (int i=0; i<nodes; i++)
  {
    float a = rot + (PI*2*i/nodes);
    x[i] = 31+3 + cos(a)*r;
    y[i] = 16 + sin(a)*r;
  }

  display.fillScreen(display.color565(0, 0,0));
  for (int i=0; i<(nodes-1); i++)
    for (int j=i+1; j<nodes; j++)
      display.drawLine(x[i],y[i], x[j],y[j], display.color565(0, 255,0));
}

void loop() {
  DisplayHariFun();
  delay(1500);
 
  float rot;
  float rotationSpeed = PI/15;
  for (int r=1; r<44; r+=3) {
    Chord(r, rot+=rotationSpeed);
    delay(50);
  }

  for (int r=1; r<44; r+=3) {
    Chord(44-r, rot-=rotationSpeed);
    delay(30);
  }
}
