// Konfigurasi template id dan template name yang didapat dari Bylnk
#define BLYNK_TEMPLATE_ID "TMPL60Dxjwv1S"
#define BLYNK_TEMPLATE_NAME "Smart Industry"

#include <Wire.h>
#include <Adafruit_GFX.h>     // Oled Display
#include <Adafruit_SSD1306.h> // Oled Display
#include <PZEM004Tv30.h>      // Library PZEM-004T
#include <BlynkSimpleEsp32.h> // Library blynk

#define DISPLAY_ADDRESS 0x3C  // Alamat display untuk LCD
#define DISPLAY_SDA_PIN 21    // Pin SDA pada ESP32
#define DISPLAY_SCL_PIN 22    // Pin SCL pada ESP32
#define SCREEN_WIDTH 128      // OLED display width
#define SCREEN_HEIGHT 64      // OLED display height
#define OLED_DISPLAY_RESET -1 // Reset display OLED

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_DISPLAY_RESET);

// PZEM004Tv30 pzem(Serial2, 21, 22); // Specify the serial port and the pins used for RX and TX
char auth[] = "ekzWMzu6s673XC5z2x8k_DoE8BUpIPmp"; // Blynk auth token
char ssid[] = "Wokwi-GUEST";                      // WiFi default di Wokwi
char pass[] = "";

float voltage1, current1, power1, frequency1, energy1 = 0; 
unsigned long lastMillis = 0;               // Digunakan untuk simulasi energy kWh
float maxVoltage = 600, minVoltage = 0;     // Threshold tegangan untuk trigger relay
bool hidup = true;                          // Kontrol on/off relay

void setupDisplay() {
    // Konfigurasi alamat display
    display.begin(SSD1306_SWITCHCAPVCC, DISPLAY_ADDRESS);

    // Bersihkan display
    display.clearDisplay();
    // Lokasi x = 10 dan y = 0 untuk output tulisan
    display.setCursor(10, 0);
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    // Tampilkan text
    display.println("Connecting...");
    display.display();
    // Tunggu 100 ms untuk lanjut
    delay(100);
}

// Baca data dari Blynk (tombol on/off)
BLYNK_WRITE(V0) {
    // Baca virtual pin 0 (V0) yang digunakan berisi nilai 0 atau 1 dari Blynk
    if (param.asInt() == 1) {
        hidup = true;
    }
    else {
        hidup = false;
    }
}

// Baca data dari Blynk slider Maximum Voltage
BLYNK_WRITE(V1) {
    // Baca virtual pin 1 (V1) berisi nilai maximum voltage dari Blynk
    float pinValue = param.asFloat();
    maxVoltage = pinValue;
}

// Baca data dari Blynk slider Minimum Voltage
BLYNK_WRITE(V2) {
    // Baca virtual pin 2 (V2) berisi nilai maximum voltage dari Blynk
    float pinValue = param.asFloat();
    minVoltage = pinValue;
}

// Update data yang ada di Blynk sesuai dengan data pada ESP32
// Mengirimkan data dari ESP32 ke Blynk
void updateBlynk(float v, float c, float p, float f, float e) {
    Blynk.run();

    // Tulis ke virtual pin yang sesuai
    Blynk.virtualWrite(V3, v);
    Blynk.virtualWrite(V4, c);
    Blynk.virtualWrite(V5, p);
    Blynk.virtualWrite(V6, f);
    Blynk.virtualWrite(V7, e);
}

void setup() {
    // put your setup code here, to run once:
    Serial.begin(115200);
    setupDisplay();
    // Pin 16 digunakan untuk mengirimkan instruksi dari ESP32 ke relay
    pinMode(16, OUTPUT);
    // Jalankan blynk sesuai auth, ssid, dan pass
    Blynk.begin(auth, ssid, pass);
    Serial.println("Hello, ESP32!");
}

void loop() {
    // put your main code here, to run repeatedly:

    float rawPot = analogRead(32); // Baca potentiometer
    // Jika VCC = 0V, maka 0.
    // Jika VCC = 3.3V, maka 4095.
    // Jika VCC = 1.65V, maka 2047
    float voltPot = rawPot * (3.3 / 4095.0); // Data voltage dari pot

    // Simulasikan data volt, curr, en, freq, dan pow dari potentiometer
    // map(value, fromLow, fromHigh, toLow, toHigh)
    // // rawPot = data dari potentiometer
    // // fromLow = data minimum potentiometer
    // // fromHigh = data maksimum potentiometer
    // // toLow = simulasi 0V 
    // // toHigh = simulasi 240V
    voltage1 = map(rawPot, 0, 4095, 0, 240);    // Simulate 0-240V
    current1 = map(rawPot, 0, 4095, 0, 10);     // Simulate 0-10A
    power1 = voltage1 * current1;               // Simulated Watts

    // Frekuensi tidak bisa disimulasikan karena 'digital timing-based signal'             
    frequency1 = 0; 

    // Simulasikan energy kWh
    unsigned long currentMillis = millis();
    float hoursElapsed = (currentMillis - lastMillis) / 3600000.0; // ms to hours 
    energy1 += (power1 / 1000.0) * hoursElapsed; // kWh = W × h

    // Update data pada dashboard bylnk
    updateBlynk(voltage1, current1, power1, frequency1, energy1);

    // Cek tegangan untuk mengatur on/off relay
    if (voltage1 >= maxVoltage || voltage1 <= minVoltage || hidup ==  false) {
        digitalWrite(16, LOW);
    } else {
        digitalWrite(16, HIGH);
    }

    // Tampilkan data listrik ke OLED LCD i2C
    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.printf("Voltage  : %.2f V\n", voltage1);
    display.printf("Current  : %.2f A\n", current1);
    display.printf("Power    : %.2f W\n", power1);
    display.printf("Frequency: %.2f Hz\n", frequency1);
    display.printf("Energy   : %.2f kWh\n", energy1);
    display.display();
    delay(200);
}
