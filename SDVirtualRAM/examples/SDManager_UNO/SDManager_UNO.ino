#include <Wire.h>
#include <SPI.h>
#include "SDVirtualRAM_I2CSlave.h"
#include "crc16.h"
#include "SHA1.h"

// Pin config
#define SD_CS_PIN         10
#define SLAVE_I2C_ADDRESS 0x42
#define PAGE_SIZE         256

// Instantiate SDVirtualRAM slave with page cache
SDVirtualRAM_I2CSlave vramSlave(SD_CS_PIN);

// LED feedback
#define LED_STATUS 13
unsigned long blinkTimer = 0;
bool ledState = false;

void setup() {
  pinMode(LED_STATUS, OUTPUT);
  digitalWrite(LED_STATUS, LOW);

  Serial.begin(115200);
  while (!Serial) ; // wait for Serial on Leonardo/Micro

  Serial.println(F("=== SD-Manager UNO Booting ==="));

  // Start I2C and SD-VRAM
  vramSlave.begin();

  // Format if needed
  if (!vramSlave.SDVirtualRAM::begin()) {
    Serial.println(F("ERROR: Could not init SDVirtualRAM. Trying to format..."));
    if (vramSlave.format()) {
      Serial.println(F("Format OK"));
    } else {
      Serial.println(F("FATAL: Format failed."));
      while (true) delay(500);
    }
  }
  Serial.println(F("Ready. Awaiting I2C from Neural Cores..."));
}

void loop() {
  // Blinky status
  if (millis() - blinkTimer > 1000) {
    ledState = !ledState;
    digitalWrite(LED_STATUS, ledState);
    blinkTimer = millis();
  }
}
