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
const char *ssid = WIFI_SSID;
const char *password = WIFI_PASSWORD;
// if you change the UDP Broadcast Prefix in the sender
// you must change the following value to match.
const String broadcastPrefix = "pmpkn::";

// LED Matrix stuff
uint32_t colors[] = { CRGB::Blue, CRGB::Green, CRGB::Orange, CRGB::Purple, CRGB::Red, CRGB::Yellow };
CRGB leds[NUM_LEDS];  // LED Array (internal memory structure from FastLED)

WiFiUDP udp;
String request, searchStr;
int color, colorPos, count;
unsigned int localPort = 65001;       // local port to listen on
char packetBuffer[255];               // buffer to hold incoming packet
char ReplyBuffer[] = "acknowledged";  // a string to send back

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("\nGlowing Pumpkin UDP Receiver");
  Serial.println("By John M. Wargo\n");

  // Initialize the FastLED library
  FastLED.addLeds<NEOPIXEL, PIN>(leds, NUM_LEDS);

  // Check to make sure we have Wi-Fi credentials
  // before trying to use them
  if (String(ssid).isEmpty() || String(password).isEmpty()) {
    Serial.println("Missing Wi-Fi credentials");
    setColor(CRGB::Red);
    for (;;) {
    }
  }
ß
  // flash to let everyone know we're up
  flashLEDs(CRGB::Green, 2);  // Flash the lights twice to let everyone know we've initiated
  delay(500);

  // connect to the Wi-Fi network
  Serial.print("Connecting to ");
  Serial.println(ssid);
  setColor(CRGB::Blue);  // turn all LEDs blue while we connect to the Wi-Fi network

  // tracks how many times we've looped to connect to Wi-Fi
  // helps the sketch format the output a little cleaner
  int counter = 0;

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    counter += 1;
    if (counter > 25) {
      counter = 0;
      Serial.println();
    }
  }
  Serial.println();
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  // Flash LEDs green to let everyone know we successfully
  // connected to Wi-Fi
  flashLEDs(CRGB::Green, 2);

  // start the UDP listener
  Serial.print("Starting UDP listener (port: ");
  Serial.print(localPort);
  Serial.println(")");
  udp.begin(localPort);
}

void loop() {
  // if there's UDP data available, read a packet
  int packetSize = udp.parsePacket();
  if (packetSize) {
    IPAddress remoteIp = udp.remoteIP();
    Serial.print("Received packet of size ");
    Serial.println(packetSize);
    Serial.print("From ");
    Serial.print(remoteIp);
    Serial.print(", port ");
    Serial.println(udp.remotePort());
    // read the packet into packetBufffer
    int len = udp.read(packetBuffer, 255);
    if (len > 0) {
      packetBuffer[len] = 0;
    }

    // // send a reply, to the IP address and port that sent us the packet we received
    // udp.beginPacket(udp.remoteIP(), udp.remotePort());
    // // https://forum.arduino.cc/t/solved-invalid-conversion-from-char-to-uint8_t/563582/2
    // int i = 0;
    // while (ReplyBuffer[i] != 0)
    //   udp.write((uint8_t)ReplyBuffer[i++]);
    // udp.endPacket();

    request = packetBuffer;
    Serial.print("Request: ");
    Serial.println(request);

    // Color
    searchStr = broadcastPrefix + "c:";
    colorPos = searchStr.length();
    if (request.indexOf(searchStr) >= 0) {
      color = request.charAt(colorPos) - '0';
      Serial.print("Set Color #");
      Serial.println(color);
      fadeColor(colors[color]);
      return;  // skip the rest of this loop
    }

    // Flicker
    searchStr = broadcastPrefix + "f";
    if (request.indexOf(searchStr) >= 0) {
      flicker();
    }
  }
  delay(25);
}

// Fill the NeoPixel array with a specific color
void fadeColor(CRGB c) {
  // Serial.println("Changing color");
  for (int i = 0; i < 25; i++) {
    leds[i] = c;
    FastLED.show();
    delay(10);
  }
  delay((int)random(250, 2000));
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
  Serial.print("Flickering LEDs ");
  Serial.print(flashCount);
  Serial.println(" times");
  // flash the lights in white flashCount times
  // with a random duration and random delay between each flash
  for (int i = 0; i < flashCount; i++) {
    // Set all pixels to white and turn them on
    fill_solid(leds, NUM_LEDS, CRGB::White);
    FastLED.show();
    // Delay for a random period of time (in milliseconds)
    delay((int)random(50, 150));
    // clear the lights (set the color to none)
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
