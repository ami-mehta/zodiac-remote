/*
  Test HTTP Client
  Context: Arduino, with WINC1500 module or uBlox NINA module
*/
// include required libraries and config files
#include <SPI.h>
//#include <WiFi101.h>        // use this for MKR1000 boards
//#include <ESP8266WiFi.h>  // use this instead of WiFi101 for ESP8266 modules
#include <WiFiNINA.h>       // use this for MKR1010 and Nano 33 IoT boards
#include "arduino_secrets.h"
#include <ArduinoHttpClient.h>

WiFiClient netSocket;               // network socket to server
const char server[] = "198.211.110.218";  // server name
String route1 = "/horoscope";              // API route
String route2 = "/mood";              // API route
String route3 = "/color";              // API route
int button1 = 2;
int button2 = 3;
int button3 = 4;

void setup() {
  Serial.begin(9600);               // initialize serial communication
  while (!Serial);        // wait for serial monitor to open
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);

  // while you're not connected to a WiFi AP,
  while ( WiFi.status() != WL_CONNECTED) {
    Serial.print("Attempting to connect to Network named: ");
    Serial.println(SECRET_SSID);           // print the network name (SSID)
    WiFi.begin(SECRET_SSID, SECRET_PASS);         // try to connect
    delay(2000);
  }

  // When you're connected, print out the device's network status:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
}

void loop() {

  HttpClient http(netSocket, server, 3000);      // make an HTTP client
  if (digitalRead(button1) == LOW) {
    Serial.print("button1");
    makeGetRequest(route1);
  } else if (digitalRead(button2) == LOW) {
    Serial.print("button2");
    makeGetRequest(route2);
  } else if (digitalRead(button3) == LOW) {
    Serial.print("button3");
    makeGetRequest(route3);
  }
}

void makeGetRequest(String route) {
  Serial.println("making request");
  HttpClient http(netSocket, server, 3000);      // make an HTTP client
  http.get(route);  // make a GET request
  while (http.connected()) {       // while connected to the server,
    if (http.available()) {        // if there is a response from the server,
      String result = http.readString();  // read it
      Serial.print(result);               // and print it
    }
  }
  //  // when there's nothing left to the response,
  http.stop();                     // close the request
}
