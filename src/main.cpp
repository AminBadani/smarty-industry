#define BLYNK_TEMPLATE_ID "TMPL6yaLtgbMp"
#define BLYNK_TEMPLATE_NAME "Smart Industry"

#include <Wire.h>
#include <Adafruit_GFX.h>     // Oled Display
#include <Adafruit_SSD1306.h> // Oled Display
#include <PZEM004Tv30.h>      // Library PZEM-004T
#include <BlynkSimpleEsp32.h> // Library blynk

#define DISPLAY_ADDRESS 0x3C
#define DISPLAY_SDA_PIN 21    // Pin SDA pada ESP32
#define DISPLAY_SCL_PIN 22    // Pin SCL pada ESP32
#define SCREEN_WIDTH 128      // OLED display width
#define SCREEN_HEIGHT 64      // OLED display height
#define OLED_DISPLAY_RESET -1 // Reset display OLED

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_DISPLAY_RESET);

// PZEM004Tv30 pzem(Serial2, 21, 22); // Specify the serial port and the pins used for RX and TX
char auth[] = "qaYkcDyL43Zxh0oSMCq83MNS_h4VgLTN"; // Blynk auth token
char ssid[] = "Wokwi-GUEST";                      // WiFi default di Wokwi
char pass[] = "";

float voltage1, current1, energy1, frequency1, power1; 
float maxVoltage = 600, minVoltage = 0;     // Threshold tegangan untuk trigger relay
bool hidup = true;                          // Kontrol on/off relay

void setupDisplay() {
    display.begin(SSD1306_SWITCHCAPVCC, DISPLAY_ADDRESS);

    display.clearDisplay();
    display.setCursor(10, 0);
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.println("Connecting...");
    display.display();
    delay(100);
}

// Baca data dari Blynk (tombol on/off)
BLYNK_WRITE(V1) {
    // any code you place here will execute when the virtual pin value changes
    if (param.asInt() == 1) {
        hidup = true;
    }
    else {
        hidup = false;
    }
}

// Baca data dari Blynk slider Maximum Voltage
BLYNK_WRITE(V8) {
    float pinValue = param.asFloat();
    maxVoltage = pinValue;
}

// Baca data dari Blynk slider Minimum Voltage
BLYNK_WRITE(V9) {
    float pinValue = param.asFloat();
    minVoltage = pinValue;
}

void updateBlynk(float v, float c, float e, float f, float p) {
    Blynk.run();

    Blynk.virtualWrite(V3, v);
    Blynk.virtualWrite(V4, c);
    Blynk.virtualWrite(V5, e);
    Blynk.virtualWrite(V6, f);
    Blynk.virtualWrite(V7, p);
}

void setup() {
    // put your setup code here, to run once:
    Serial.begin(115200);
    setupDisplay();
    pinMode(16, OUTPUT);
    Blynk.begin(auth, ssid, pass);

    Serial.println("Hello, ESP32!");
}

void loop() {
    // put your main code here, to run repeatedly:

    // Baca potentiometer
    voltage1 = analogRead(32) / 4;
    current1 = analogRead(32) / 5;
    energy1 = analogRead(32) / 3;
    frequency1 = analogRead(32) / 4;
    power1 = (voltage1 * current1) / 100;

    updateBlynk(voltage1, current1, energy1, frequency1, power1);

    // Cek tegangan untuk mengatur on/off relay
    if (voltage1 >= maxVoltage || voltage1 <= minVoltage || hidup ==  false) {
        digitalWrite(16, LOW);
    } else {
        digitalWrite(16, HIGH);
    }

    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.printf("Voltage  : %.2f V\n", voltage1);
    display.printf("Current  : %.2f A\n", current1);
    display.printf("Energy   : %.2f kWh\n", energy1);
    display.printf("Frequency: %.2f Hz\n", frequency1);
    display.printf("Power    : %.2f W\n", power1);
    display.display();
    delay(2000);
}
