#include "crc16.h"
#include <Arduino.h>  // OR: #include <stddef.h>

uint16_t crc16(const uint8_t* data, size_t length) {
  uint16_t crc = 0x0000;
  for (size_t i = 0; i < length; i++) {
    crc ^= (uint16_t)data[i] << 8;
    for (uint8_t j = 0; j < 8; j++)
      crc = (crc & 0x8000) ? (crc << 1) ^ 0x1021 : crc << 1;
  }
  return crc;
}
