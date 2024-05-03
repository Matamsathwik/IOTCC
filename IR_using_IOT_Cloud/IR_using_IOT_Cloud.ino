#include <ESP8266WiFi.h>
#include "secrets.h"
#include "ThingSpeak.h" 
char ssid[] = SECRET_SSID;   
char pass[] = SECRET_PASS;   
int keyIndex = 0;            
WiFiClient  client;

unsigned long myChannelNumber = SECRET_CH_ID;
const char * myWriteAPIKey = SECRET_WRITE_APIKEY;

int number = 0;
int irPin=D5;

void setup() {
  Serial.begin(115200); 
  while (!Serial) {
    ;   }
  
  WiFi.mode(WIFI_STA); 
  ThingSpeak.begin(client); 
}
void loop() {

  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(SECRET_SSID);
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, pass);  
      Serial.print(".");
      delay(5000);     
    } 
    Serial.println("\nConnected.");
  }  
  int x = ThingSpeak.writeField(myChannelNumber, 1, number, myWriteAPIKey);
  if(x == 200){
    Serial.println("Channel update successful.");
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }

    number++;
  if(number > 99){
    number = 0;
  }
  
  delay(20000);
}
