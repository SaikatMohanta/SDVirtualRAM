// SDVirtualRAM.cpp

#include "SDVirtualRAM.h"
#include <Arduino.h>

SDVirtualRAM::SDVirtualRAM(uint8_t csPin)
  : _csPin(csPin)
{}

bool SDVirtualRAM::begin() {
  // Initialize SPI and mount SD card
  if (!_sd.begin(_csPin, SD_SCK_MHZ(50))) {
    Serial.println(F("SD card init failed!"));
    return false;
  }

  // Try to open existing VRAM file
  if (!_file.open(_filename, FILE_READ | FILE_WRITE)) {
    // Create and zero-fill if it doesn't exist
    if (!_file.open(_filename, O_CREAT | O_RDWR)) {
      Serial.println(F("VRAM create failed!"));
      return false;
    }
    // Expand to full size
    if (!_file.truncate(VRAM_SIZE_BYTES)) {
      Serial.println(F("VRAM resize failed!"));
      _file.close();
      return false;
    }
    // Optionally zero-fill (not strictly needed if truncate gives zeros)
    uint8_t zeroBuf[32] = {0};
    for (uint32_t written = 0; written < VRAM_SIZE_BYTES; written += sizeof(zeroBuf)) {
      size_t chunk = min(sizeof(zeroBuf), VRAM_SIZE_BYTES - written);

      if (_file.write(zeroBuf, chunk) != chunk) {
        Serial.println(F("VRAM zero-fill failed!"));
        _file.close();
        return false;
      }
    }
  }

  // Ensure file stays open
  _file.seekSet(0);
  return true;
}

bool SDVirtualRAM::seekTo(uint32_t addr) {
  if (!validRange(addr)) return false;
  return (_file.seekSet(addr) == addr);
}

bool SDVirtualRAM::validRange(uint32_t addr, size_t len) const {
  // Avoid overflow
  if (addr >= VRAM_SIZE_BYTES) return false;
  if (len > 0 && (addr + len) > VRAM_SIZE_BYTES) return false;
  return true;
}

uint8_t SDVirtualRAM::readByte(uint32_t addr) {
  uint8_t val = 0;
  if (!seekTo(addr) || _file.read(&val, 1) != 1) {
    // read error → return 0
    return 0;
  }
  return val;
}

bool SDVirtualRAM::writeByte(uint32_t addr, uint8_t val) {
  if (!seekTo(addr) || _file.write(&val, 1) != 1) {
    return false;
  }
  return true;
}

bool SDVirtualRAM::read(uint32_t addr, uint8_t* buffer, size_t len) {
  if (!validRange(addr, len)) return false;
  if (!seekTo(addr)) return false;
  return (_file.read(buffer, len) == (int)len);
}

bool SDVirtualRAM::write(uint32_t addr, const uint8_t* buffer, size_t len) {
  if (!validRange(addr, len)) return false;
  if (!seekTo(addr)) return false;
  return (_file.write(buffer, len) == (int)len);
}

bool SDVirtualRAM::format() {
  // Close and delete, then recreate
  _file.close();
  if (!_sd.remove(_filename)) {
    Serial.println(F("VRAM remove failed!"));
    return false;
  }
  return begin();
}
