# 💾 SDVirtualRAM — Virtual RAM on SD Card for Arduino

[![Arduino](https://img.shields.io/badge/Arduino-Library-blue?logo=arduino)](https://www.arduino.cc/)
[![License: MIT](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE)
[![C++](https://img.shields.io/badge/C%2B%2B-17-orange?logo=c%2B%2B)]()

A lightweight Arduino library that turns your **SD card into virtual RAM**.  
Perfect for memory-constrained microcontrollers like the **Arduino Uno, Nano, Mega**, or **ESP boards**, where SRAM is limited.

-----

## ✨ Features
- 📦 **Virtual Address Space** — Define a custom RAM size (default: `256 KB`).
- 🔄 **Random Access Reads/Writes** — Byte or block level access.
- 🧹 **Formatting Support** — Reset the virtual RAM file instantly.
- 💡 **Plug & Play** — Minimal setup, just connect your SD module.

----

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
