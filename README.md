# 🧰 SDVirtualRAM - An Arduino Virtual RAM Toolkit
--------------------

A lightweight Arduino library that brings **extended page memory**, **data integrity**, and **cryptographic hashing** to your microcontroller projects.  
This toolkit combines:

- 📦 **SDVirtualRAM** — emulate large virtual RAM using an SD card  
- 🔑 **SHA1** — compute cryptographic hashes directly on Arduino  
- ✅ **CRC16** — ensure data integrity with checksum verification  

Designed for **resource-constrained devices** like Arduino UNO, Mega, ESP32, etc.

--------------

## ✨ Features

- Emulate up to **megabytes of RAM** using SD card storage  
- Simple API for **byte-level read/write**  
- Fast **CRC16 checksums** for error detection  
- Built-in **SHA1 hashing** for authentication & security  
- Modular: use only the parts you need  

-----------

## 📂 Structure

- crc16.h,cpp 	        → 	CRC16 checksum functions
- SHA1.h,cpp         	→ 	SHA1 hashing implementation
- SDVirtualRAM.h,cpp 	→ 	Virtual RAM over SD card

- Demo usage 	        →  	examples/SD_Manager_example/SD_Manager_example.ino


--------

## 🚀 Getting Started

### 1. Requirements
- Arduino IDE or PlatformIO  
- [SdFat library](https://github.com/greiman/SdFat) for SD card support  
- MicroSD card module + formatted micro-SD card with FAT32 system

### 2. Installation
Clone this repo into your Arduino `libraries/` folder:

```bash
git clone https://github.com/SaikatMohanta/SDVirtualRAM.git
```

-------------

📌 Potential Applications

- Emulate large RAM for image/audio buffering

- Store temporary sensor data logs

- Add integrity checks for wireless communication

- Implement basic cryptographic authentication

--------------
