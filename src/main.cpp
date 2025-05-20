#include <Wire.h>
#include <Adafruit_GFX.h>     // Oled Display
#include <Adafruit_SSD1306.h> // Oled Display
#include <PZEM004Tv30.h>      // Library PZEM-004T

#define DISPLAY_ADDRESS 0x3C
#define DISPLAY_SDA_PIN 21        // Pin SDA pada ESP32
#define DISPLAY_SCL_PIN 22        // Pin SCL pada ESP32
#define SCREEN_WIDTH 128          // OLED display width
#define SCREEN_HEIGHT 64          // OLED display height
#define OLED_DISPLAY_RESET -1     // Reset display OLED

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_DISPLAY_RESET);

// PZEM004Tv30 pzem(Serial2, 21, 22); // Specify the serial port and the pins used for RX and TX

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

  Serial.println("Hello, ESP32!");
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(16, HIGH);
  delay(1000); // this speeds up the simulation
  digitalWrite(16, LOW);
  delay(1000); // this speeds up the simulation
}
