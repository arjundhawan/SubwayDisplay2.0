#include <PxMatrix.h>
#include <ESP8266WiFi.h>        // Include the Wi-Fi library

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

// ISR for display refresh
void display_updater(){display.display(70);}

const char* ssid     = "NETGEAR37";        
const char* password = "sillycheese19";   

void setup() {
  //Serial connection setUp
  Serial.begin(115200);

  //display setUp
  display.begin(16);
  display.setBrightness(100); //100/255
  display_ticker.attach(0.002, display_updater);
  
  delay(1000);

  //wifi Connect SetUp
  WiFi.begin(ssid, password);

  //display time it takes to connect
  display.clearDisplay();
  display.setCursor(2,2); 
  display.print("Connecting");

  //to please the eye refresh as little as possible
  display.setCursor(2,12);
  display.print("attempt");

  byte i = 1;
   while (WiFi.status() != WL_CONNECTED && i < 20) {
      display.setCursor(50,12);
      display.print(i);
      delay(750);
      display.fillRect(45, 11, 64, 32,display.color565(0, 0, 0));
      i++;
   }
}

char* stat;
char* link;

void loop() {
  display.setTextColor(display.color565(0, 0, 0));
  if(WiFi.status() == WL_CONNECTED){
    display.fillScreen(display.color565(50, 180, 50));
    stat = "Connected";
    link = "to";  
  }
  else{
    display.fillScreen(display.color565(180, 50, 50));
    stat = "Failed";
    link = "to reach";
  }
  
  display.setCursor(2,2); 
  display.print(stat);
  display.setCursor(2,12);
  display.print(link);
  display.setCursor(2,22);
  display.print(ssid);
  delay(15000);
}
