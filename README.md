# 💾 SDVirtualRAM — Virtual RAM on SD Card for Arduino

[![Arduino](https://img.shields.io/badge/Arduino-Library-blue?logo=arduino)](https://www.arduino.cc/)
[![License: MIT](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE)
[![C++](https://img.shields.io/badge/C%2B%2B-17-orange?logo=c%2B%2B)]()

A lightweight Arduino library that turns your **SD card into virtual RAM**.  
Perfect for memory-constrained microcontrollers like the **Arduino Uno, Nano, Mega**, or **ESP boards**, where SRAM is limited.

-----

## ✨ Features
- 📦 **Virtual Address Space** — Define a custom RAM size (default: `256 KB`)
- 🔄 **Random Access Reads/Writes** — Byte or block level access
- 🧹 **Formatting Support** — Reset the virtual RAM file instantly
- 💡 **Plug & Play** — Minimal setup, just connect your SD module

----
##🛠 Potential Use Cases

- Simulating large memory buffers (images, sensor logs, audio samples).
- Creating temporary data caches on SD card.
- Emulating RAM expansions for retro projects.
- Logging and retrieving structured data.

------
##📐 Requirements
- Arduino IDE 1.8+ 
- SdFat Library
- SD card module with SPI interface

------
## 🚀 Getting Started

### 🔧 Installation
1. Clone this repository or download as ZIP.
2. Place in your Arduino `libraries` folder.
3. Include it in your sketch:

```cpp
#include <SDVirtualRAM.h>

SDVirtualRAM vram;

void setup() {
  Serial.begin(9600);
  if (!vram.begin()) {
    Serial.println("Failed to initialize SD Virtual RAM!");
    while (1);
  }

  vram.writeByte(0, 42); // write value at addr=0
  Serial.println(vram.readByte(0)); // should print 42
}

void loop() {}
```

------

### `IMPLEMENTATION`
```markdown
# 🔍 Implementation Details — SDVirtualRAM

This document explains the inner workings of the `SDVirtualRAM` library.

----

## 📦 Core Concept
Since microcontrollers have **very limited SRAM**, this library uses an **SD card file (`VRAM.BIN`)** to act as an extended memory space.  
All read/write operations are redirected to this file, simulating virtual memory.

-----

## ⚙️ How It Works
1. **Initialization (`begin`)**
   - Initializes the SD card with `SdFat`.
   - Opens or creates a binary file (`VRAM.BIN`).
   - Expands it to the defined size (`VRAM_SIZE_BYTES`).

2. **Read/Write Operations**
   - Byte access:
     ```cpp
     uint8_t readByte(uint32_t addr);
     bool writeByte(uint32_t addr, uint8_t val);
     ```
   - Block access:
     ```cpp
     bool read(uint32_t addr, uint8_t* buffer, size_t len);
     bool write(uint32_t addr, const uint8_t* buffer, size_t len);
     ```

3. **Address Validation**
   - Ensures requested addresses do not exceed the defined VRAM size.

4. **Formatting**
   - Deletes and recreates `VRAM.BIN` for a clean reset.

-----

## 📊 Performance Notes
- **Speed** is limited by SD card SPI throughput (~100–500 KB/s on most Arduinos).
- Best suited for **bulk storage**, not high-speed RAM replacement.
- Use **larger block operations** for better performance.

-----

## 🔮 Future Improvements
- Add support for wear-leveling (extend SD card life).
- Implement a caching layer for faster random reads/writes.
- Option to define **multiple VRAM files**.
----
