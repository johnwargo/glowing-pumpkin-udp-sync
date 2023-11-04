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

#define MIN_DELAY 3000
#define MAX_DELAY 10000
#define NUM_LEDS 25
#define PIN A3

// store the credentials in the project's constants.h file
const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWORD;
// if you change the UDP Broadcast Prefix in the receiver sketch
// you must change the following value to match.
// https://github.com/espressif/arduino-esp32/blob/master/libraries/WiFi/examples/WiFiUDPClient/WiFiUDPClient.ino
// multicast
String broadcastPrefix = "pmpkn::";
const char* udpAddress = "192.168.86.255";
const uint16_t udpPort = 65001;

bool justFlickered = false;
int numColors = 6;
int lastColorIdx = -1;
uint32_t colors[] = { CRGB::Blue, CRGB::Green, CRGB::Orange, CRGB::Purple, CRGB::Red, CRGB::Yellow };
CRGB leds[NUM_LEDS];  // LED Array (internal memory structure from FastLED)

WiFiUDP udp;

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("\nGlowing Pumpkin UDP Sender");
  Serial.println("By John M. Wargo\n");

  // Initialize the FastLED library
  FastLED.addLeds<NEOPIXEL, PIN>(leds, NUM_LEDS);

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

  Serial.print("\nIP address: ");
  Serial.println(WiFi.localIP());
  Serial.println();

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
    if (!justFlickered) {
      // if it's a 9 or a 10, do that flicker thing
      justFlickered = true;
      cmdStr += "f";
      sendBroadcast(cmdStr);
      flicker();
      delay(1000);
    }
  } else {
    justFlickered = false;
    // Otherwise switch to the new color
    // pick a new color index
    colorIdx = random(1, numColors + 1);
    // if it's the same color as last time, keep looking until you get a new one
    while (colorIdx == lastColorIdx) {
      // pick another color index
      colorIdx = random(1, numColors + 1);
    }
    // whew, we made it here, so we must have a new color index
    // assign it to lastColorIdx to use the next time around
    lastColorIdx = colorIdx;
    // build the command string
    cmdStr += "c:";
    cmdStr += String(colorIdx);
    sendBroadcast(cmdStr);
    fadeColor(colors[colorIdx]);
    // wait a while
    delay((int)random(MIN_DELAY, MAX_DELAY));
  }
  delay(25);
}

void sendBroadcast(String msg) {
  // command (cmd): pmpkn::c:#
  // a little longer than the command string (+1)
  int cmdLen = 11;

  char charArray[cmdLen];
  // unsigned int strLen;

  Serial.print("Outgoing command: ");
  Serial.println(msg);
  // add spaces to the end of the command to make all commands
  // `c:#` or `f` the same length
  msg = padRight(msg, cmdLen - 1);
  // copy the message (String) to the Character array
  msg.toCharArray(charArray, cmdLen);
  udp.beginMulticastPacket();
  udp.beginPacket(udpAddress, udpPort);
  udp.printf(charArray);
  udp.endPacket();
}

String padRight(String str, int len) {
  int delta = len - str.length();
  if (delta > 0) {
    for (int i = 0; i < delta; i++) str += " ";
  }
  return str;
}


// Fill the NeoPixel array with a specific color
void fadeColor(CRGB c) {
  for (int i = 0; i < 25; i++) {
    leds[i] = c;
    FastLED.show();
    delay(10);
  }
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
