#include <Arduino.h>
#include "SDVirtualRAM.h"
#include "crc16.h"
#include "SHA1.h"

SDVirtualRAM vram(10); // CS pin = 10 (adjust as per your requirements)

void setup() {
  Serial.begin(9600);
  if (!vram.begin()) {
    Serial.println("SD-VRAM init failed!");
    while (1);
  }
  Serial.println("SD-VRAM ready!");

  // --- Example 1: Write/Read Virtual RAM ---
  uint8_t data = 42;
  vram.writeByte(0, data);
  Serial.print("Read back: ");
  Serial.println(vram.readByte(0));

  // --- Example 2: CRC16 Check ---
  const char *msg = "Hello VRAM!";
  uint16_t crc = crc16((const uint8_t*)msg, strlen(msg));
  Serial.print("CRC16: 0x");
  Serial.println(crc, HEX);

  // --- Example 3: SHA1 Hash ---
  SHA1_CTX ctx;
  uint8_t digest[20];
  SHA1_Init(&ctx);
  SHA1_Update(&ctx, (const uint8_t*)msg, strlen(msg));
  SHA1_Final(digest, &ctx);

  Serial.print("SHA1: ");
  for (int i = 0; i < 20; i++) {
    Serial.print(digest[i], HEX);
  }
  Serial.println();
}

void loop() {
  // Place your project logic in here
}
