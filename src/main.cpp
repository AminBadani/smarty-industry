// #define BLYNK_TEMPLATE_ID "TMPL6yaLtgbMp"
// #define BLYNK_TEMPLATE_NAME "Quickstart Template"

#include <Wire.h>
#include <Adafruit_GFX.h>     // Oled Display
#include <Adafruit_SSD1306.h> // Oled Display
// #include <PZEM004Tv30.h>      // Library PZEM-004T
// #include <BlynkSimpleEsp32.h> // Library blynk
#include <WiFi.h>

#define DISPLAY_ADDRESS 0x3C
#define DISPLAY_SDA_PIN 21        // Pin SDA pada ESP32
#define DISPLAY_SCL_PIN 22        // Pin SCL pada ESP32
#define SCREEN_WIDTH 128          // OLED display width
#define SCREEN_HEIGHT 64          // OLED display height
#define OLED_DISPLAY_RESET -1     // Reset display OLED

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_DISPLAY_RESET);

// PZEM004Tv30 pzem(Serial2, 21, 22); // Specify the serial port and the pins used for RX and TX
// char ssid[] = "Wokwi-GUEST"; // WiFi default di Wokwi
// char pass[] = "";
// char auth[] = "g1s1w7T1ULIMvqf0qLD2nl3gTK9O0ix_";  // Blynk auth token

float voltage1, current1, energy1, frequency1, power1;

void setupDisplay() {
  // Wire.begin(DISPLAY_SDA_PIN, DISPLAY_SCL_PIN);
  display.begin(SSD1306_SWITCHCAPVCC, DISPLAY_ADDRESS);

  display.clearDisplay();
  display.setCursor(10, 0);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.println("Hello World");
  display.display();
  delay(100);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  setupDisplay();
  pinMode(16, OUTPUT);
  // Blynk.begin(auth, ssid, pass);

  Serial.println("Hello, ESP32!");
}

void loop() {
  // put your main code here, to run repeatedly:
  voltage1 = analogRead(12);
  current1 = 0;
  energy1 = 0;
  frequency1 = 0;
  power1 = 0;

  // Blynk.run();
  // // Send data to blynk
  // Blynk.virtualWrite(V4, voltage1);

  if (voltage1 >= 500) {
    digitalWrite(16, LOW);
  } else {
    digitalWrite(16, HIGH);
  }

  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.printf("Voltage   : %.2f\ V \n", voltage1);
  display.printf("Current   : %.2f\ A \n", current1);
  display.printf("Energy    : %.2f\ kWh \n", energy1);
  display.printf("Frequency : %.2f\ Hz \n", frequency1);
  display.printf("Power     : %.2f\ W \n", power1);
  display.display();
  delay(2000);
}
