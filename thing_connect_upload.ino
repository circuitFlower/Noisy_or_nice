#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>
#include <Servo.h>

// FROM SETTING WIFI 
byte mac[6];
char *ssid = "hackathon24";
char *password = "tvcogh4x";
char const *ssid_AP = "esp8266";
char const *password_AP = "capstone";
char AP_mode;
char wifi_info_submitted = 0; //See whether pass and ssid submitted or not. 
char connect_success = 0;

//For uploading data
const char* host= "uiot.comlu.com"; // Your domain  
String url;
const int pin = 5;
int sensorPin = A0;
int sensorID = 1;  //using to identify all different sensor systems.
int sensorVal = 0;

ESP8266WebServer server(80);
/* Go to http://192.168.4.1 in a web browser */

void setup() 
{
	pinMode(pin, OUTPUT); 
  pinMode(pin, HIGH);
	delay(1000);
	Serial.begin(115200);
	AP_mode = 0;
  print_mac();
  setupWIFI(20); //argument is waiting time before connecting
}

void loop() 
{
	if(!wifi_info_submitted && !connect_success){
    if( AP_mode == 0){setup_AP();}
    server.handleClient();
  }
  else if(!connect_success && wifi_info_submitted) {
     WiFi.mode(WIFI_OFF);
     AP_mode=0;
     Serial.println("I already know where to connect!");
     setupWIFI(20); //argument is waiting time before connecting
     if( WiFi.status() != WL_CONNECTED ){wifi_info_submitted = 0;}  //redirect to AP mode if still not connected 
  }
  else{ //WIFI connected. Do whatever now!!
    Serial.println("I AM ALREADY CONNECTED. YAYYY");
    upload_stuff();
  }
}
