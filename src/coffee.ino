#include <ESP8266WiFi.h>
#include <Servo.h>
#include <ESP8266WebServer.h>
#include <WiFiUdp.h>
#include <functional>
#include <String.h>
#include "switch.h"
#include "UpnpBroadcastResponder.h"
#include "CallbackFunction.h"
#include "LightSwitch.h"
#include "AdafruitIO_WiFi.h"

//servo pins
#define SERVO1_PIN 4


//servo Calubration (ON must me higher then OFF)
#define ON_POSITION 120
#define NUTRAL_POSITION 65
#define OFF_POSITION 65

// prototypes
boolean connectWifi();

//on/off callbacks
void Switch1_On();
void Switch1_Off();


// Change this before you flash
const char* ssid = "Verizon-MiFi6620L-0710";
const char* password = "d88e668b";

#define IO_USERNAME    "joeltebo"
#define IO_KEY         "063234aa76ff429cbc39dda29e34688f"

boolean wifiConnected = false;

UpnpBroadcastResponder upnpBroadcastResponder;

Switch *switch1 = NULL;



LightSwitch *ServoSwitch1 = NULL;

AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, ssid, password);

AdafruitIO_Feed *switchCall1 = io.feed("Coffee_feed");



void setup()
{
  Serial.begin(115200);
  while(! Serial);


  //start AdafruitIO
  Serial.print("Connecting to Adafruit IO");
  io.connect();
  // set up a message handler for the count feed.
  switchCall1->onMessage(handleMessage1);
  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.println(io.statusText());

  // Initialise wifi connection
  wifiConnected = connectWifi();


  if(wifiConnected){


    upnpBroadcastResponder.beginUdpMulticast();

    // Define your switches here. Max 14
    // Format: Alexa invocation name, local port no, on callback, off callback
    switch1 = new Switch("Coffee Maker", 84, Switch1_On, Switch1_Off);


    //livingroom fan
    ServoSwitch1 = new LightSwitch(SERVO1_PIN, ON_POSITION, OFF_POSITION, NUTRAL_POSITION);

    Serial.println("Adding switches upnp broadcast responder");
    upnpBroadcastResponder.addDevice(*switch1);
  }

}

void loop()
{
  if(wifiConnected){
    upnpBroadcastResponder.serverLoop();

    switch1->serverLoop();
  }
  io.run();
}

void Switch1_On() {
  Serial.print("Switch 1 turn on ...");
  ServoSwitch1->moveOn();
}

void Switch1_Off() {
  // Serial.print("Switch 1 turn off ...");
  // ServoSwitch1->moveOff();
}



// connect to wifi – returns true if successful or false if not
boolean connectWifi(){
  boolean state = true;
  int i = 0;


  Serial.println("");
  Serial.println("Connecting to WiFi");

  // Wait for connection
  Serial.print("Connecting ...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (i > 10){
      state = false;
      break;
    }
    i++;
  }

  if (state){
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }
  else {
    Serial.println("");
    Serial.println("Connection failed.");
  }

  return state;
}

//AdafruitIO messageHandel
void handleMessage1(AdafruitIO_Data *data) {

  Serial.println("switch 1 received <- ");
  Serial.println(data->value());

  if (data->toString().equalsIgnoreCase("start")){
   Switch1_On();
 }
  else
    Serial.println("not a valid input");

}
