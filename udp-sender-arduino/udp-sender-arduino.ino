/*********************************************************
* Glowing Pumpkin 
* 
* Xaio ESP32 S3 version using the Adafruit 5x5 BFF LED
* Matrix.  This edition adds a UDP sender/receiver to the 
* project. The sender sends commands to multiple receivers
* using UDP broadcasts.
*
* By John M. Wargo
* https://johnwargo.com
**********************************************************/
#include <FastLED.h>
#include <WiFi.h>
#include <WiFiUdp.h>

// local file (contains Wi-Fi credentials)
#include "constants.h"

#define NUM_LEDS 25
#define PIN A3

// store the credentials in the project's constants.h file
const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWORD;
// if you change the UDP Broadcast Prefix in the receiver sketch
// you must change the following value to match.
// https://github.com/espressif/arduino-esp32/blob/master/libraries/WiFi/examples/WiFiUDPClient/WiFiUDPClient.ino
// multicast
const char* udpAddress = "192.168.86.255";
// specific address
// const char* udpAddress = "192.168.86.36";
const uint16_t udpPort = 5005;

// LED Matrix stuff
int numColors = 6;
uint32_t colors[] = { CRGB::Blue, CRGB::Green, CRGB::Orange, CRGB::Purple, CRGB::Red, CRGB::Yellow };
CRGB leds[NUM_LEDS];  // LED Array (internal memory structure from FastLED)

WiFiUDP udp;
String broadcastPrefix = "pmpkn::";

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println();

  // Initialize the FastLED library
  FastLED.addLeds<NEOPIXEL, PIN>(leds, NUM_LEDS);

  Serial.println("\nGlowing Pumpkin UDP Sender");

  // Check to make sure we have Wi-Fi credentials before trying to use them
  if (String(ssid).isEmpty() || String(password).isEmpty()) {
    Serial.println("\nMissing Wi-Fi credentials");
    setColor(CRGB::Red);
    for (;;) {}
  }

  // flash to let everyone know we're up and running
  flashLEDs(CRGB::Green, 2);
  delay(500);

  // connect to the Wi-Fi network
  Serial.print("Connecting to ");
  Serial.println(ssid);
  // turn all LEDs blue while we connect to the Wi-Fi network
  setColor(CRGB::Blue);

  // tracks how many times we've looped to connect to Wi-Fi
  // helps the sketch format the output a little cleaner
  int counter = 0;

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(200);
    Serial.print(".");
    counter += 1;
    if (counter > 25) {
      counter = 0;
      Serial.println();
    }
  }

  Serial.println("");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Flash LEDs green to let everyone know we successfully connected to Wi-Fi
  flashLEDs(CRGB::Green, 2);

  // Start the UDP server
  udp.beginMulticast(IPAddress(192, 168, 86, 255), udpPort);
}

void loop() {
  String cmdStr;
  int colorIdx;

  cmdStr = broadcastPrefix;
  //generate a random integer between 1 and 10
  if ((int)random(11) > 8) {
    // if it's a 9 or a 10, do that flicker thing
    cmdStr += "f";
    sendBroadcast(cmdStr);
    flicker();
  } else {
    // Otherwise switch to the new color
    colorIdx = random(1, numColors + 1);
    cmdStr += "c:";
    cmdStr += String(colorIdx);
    sendBroadcast(cmdStr);
    fadeColor(colors[colorIdx]);
  }
  delay(25);
}

// Fill the NeoPixel array with a specific color
void fadeColor(CRGB c) {
  for (int i = 0; i < 25; i++) {
    leds[i] = c;
    FastLED.show();
    delay(10);
  }
  delay((int)random(250, 5000));
}

void flashLEDs(CRGB color, int count) {
  int duration = 500;
  int offDuration = duration / 2;

  for (int i = 0; i < count; i++) {
    fill_solid(leds, NUM_LEDS, color);
    FastLED.show();
    delay(duration);
    fill_solid(leds, NUM_LEDS, CRGB::Black);
    FastLED.show();
    delay(offDuration);
  }
  delay(500);
}

void flicker() {
  // how many times are we going to flash?
  int flashCount = (int)random(2, 6);
  //flash the lights in white flashCount times
  //with a random duration and random delay between each flash
  for (int i = 0; i < flashCount; i++) {
    // Set all pixels to white and turn them on
    fill_solid(leds, NUM_LEDS, CRGB::White);
    FastLED.show();
    // Delay for a random period of time (in milliseconds)
    delay((int)random(50, 150));
    //clear the lights (set the color to none)
    fill_solid(leds, NUM_LEDS, CRGB::Black);
    FastLED.show();
    // Delay for a random period of time (in milliseconds)
    delay((int)random(100, 500));
  }
}

void setColor(CRGB c) {
  fill_solid(leds, NUM_LEDS, c);
  FastLED.show();
}

void sendBroadcast(String msg) {
  // command (cmd): pmpkn::c:#
  int cmdLen = 11;  // a little longer than the command string (+1)
  unsigned int strLen;
  char charArray[cmdLen];

  Serial.println("0");
  Serial.println(msg);
  Serial.println("1");
  delay(500);
  strLen = msg.length();
  Serial.println("2");
  // fill the char array with zeros (clear out any previous command detritus)
  for (int i = 0; i < cmdLen; i++) charArray[i] = ' ';
  Serial.println("3");
  // copy the message (String) to the Character array
  msg.toCharArray(charArray, strLen);
  Serial.println("4");
  udp.beginMulticastPacket();
  Serial.println("5");
  // udp.beginPacket(udpAddress, udpPort);
  udp.printf(charArray);
  Serial.println("6");
  udp.endPacket();
  Serial.println("7");
}
