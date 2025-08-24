// SDVirtualRAM.h

#ifndef SDVIRTUALRAM_H
#define SDVIRTUALRAM_H

#include <Arduino.h>
#include <SdFat.h>

// Size of the “virtual RAM” in bytes.
// Adjust to suit your application, e.g. 512 KB = 512UL * 1024UL
#define VRAM_SIZE_BYTES  (256UL * 1024UL)

class SDVirtualRAM {
public:
  #ifndef SDVIRTUALRAM_CS_PIN
  	#define SDVIRTUALRAM_CS_PIN 10
  #endif

  SDVirtualRAM(uint8_t csPin = SDVIRTUALRAM_CS_PIN);

  
  // Initializes the SD card, creates or opens the VRAM file.
  // Returns true on success.
  bool begin();

  // Read a single byte from virtual address.
  uint8_t  readByte(uint32_t addr);

  // Write a single byte to virtual address.
  bool     writeByte(uint32_t addr, uint8_t val);

  // Bulk read: read len bytes into buffer from addr.
  // Returns true on success.
  bool     read(uint32_t addr, uint8_t* buffer, size_t len);

  // Bulk write: write len bytes from buffer to addr.
  // Returns true on success.
  bool     write(uint32_t addr, const uint8_t* buffer, size_t len);

  // Erase (zero out) the entire VRAM file.
  bool     format();

  // Get the total size of the virtual RAM.
  uint32_t size() const { return VRAM_SIZE_BYTES; }

private:
  SdFat       _sd;
  SdFile      _file;
  uint8_t     _csPin;
  const char* _filename = "VRAM.BIN";

  // Seek to a given virtual address inside the file.
  // Returns true on success.
  bool     seekTo(uint32_t addr);

  // Internal helper to clamp/validate addresses.
  bool     validRange(uint32_t addr, size_t len = 1) const;
};

#endif // SDVIRTUALRAM_H
