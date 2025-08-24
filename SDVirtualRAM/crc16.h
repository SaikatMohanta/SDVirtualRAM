#ifndef CRC16_H
#define CRC16_H

#include <Arduino.h>  // OR: #include <stddef.h>

#include <stdint.h>
uint16_t crc16(const uint8_t* data, size_t length);

#endif
