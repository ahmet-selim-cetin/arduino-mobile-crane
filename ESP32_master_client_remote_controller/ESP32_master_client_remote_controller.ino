// ESP32 Dev Module - Bluetooth CLIENT (master)
// Mega Serial1 -> ESP32 Serial2 ; ESP32 USB Serial -> bilgisayar debug
#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

#define RXD2 16
#define TXD2 17

String sunucuAdi = "ESP32_Server";
// Daha güvenilir: server'ın MAC adresi (server'da SerialBT.getBtAddress() ile öğren)
// uint8_t sunucuMac[6] = {0x24, 0x6F, 0x28, 0xAA, 0xBB, 0xCC};

unsigned long sonDeneme = 0;

void baglan() {
  Serial.println("Bluetooth'a baglaniliyor...");
  if (SerialBT.connect(sunucuAdi)) {
  // if (SerialBT.connect(sunucuMac)) {
    Serial.println("Baglanti basarili!");
  } else {
    Serial.println("Baglanti basarisiz, tekrar denenecek...");
  }
}

void setup() {
  Serial.begin(115200);                         // Bilgisayar
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);  // Mega

  SerialBT.begin("ESP32_Client", true);         // master modu
  baglan();
}

void loop() {
  // Bağlantı koptuysa 5 saniyede bir yeniden dene
  if (!SerialBT.connected()) {
    if (millis() - sonDeneme > 5000) {
      sonDeneme = millis();
      baglan();
    }
  }

  // Mega -> Bluetooth + bilgisayara debug
  while (Serial2.available()) {
    char c = Serial2.read();
    Serial.write(c);                 // bilgisayarda gör
    if (SerialBT.connected()) SerialBT.write(c);
  }

  // Bluetooth -> Mega + bilgisayara debug
  while (SerialBT.available()) {
    char c = SerialBT.read();
    Serial.write(c);
    Serial2.write(c);
  }

  // Bilgisayar -> Bluetooth (isteğe bağlı test)
  while (Serial.available()) {
    char c = Serial.read();
    if (SerialBT.connected()) SerialBT.write(c);
  }
}