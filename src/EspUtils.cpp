#include <Arduino.h>
#include "EspUtils.h"

#include <ESP.h>

String EspUtils::getFlashChipIdentification() {
  /**
   * Chip ID
   * 00 - always 00 (Chip ID use only 3 byte)
   * 17 - ? looks like 2^xx is size in Byte ?     // todo: find docu to this
   * 40 - ? may be Speed ?                        // todo: find docu to this
   * C8 - manufacturer ID
   */
#if defined(ESP32)
  return F("Currently not supported on ESP32");
#elif defined(ESP8266)
  switch (ESP.getFlashChipId()) {
    // GigaDevice
    case 0x1740C8:
      return F("GigaDevice GD25Q64B, 8 MB (64 MBit)");
    case 0x1640C8:
      return F("GigaDevice GD25Q32B, 4 MB (32 MBit)");
    case 0x1540C8:
      return F("GigaDevice GD25Q16N, 2 MB (16 MBit)");
    case 0x1440C8:
      return F("GigaDevice GD25Q80, 1 MB (8 MBit)");
    case 0x1340C8:
      return F("GigaDevice GD25Q40, 512 KB (4 MBit)");
    case 0x1240C8:
      return F("GigaDevice GD25Q20, 256 KB (2 MBit)");
    case 0x1140C8:
      return F("GigaDevice GD25Q10, 128 KB (1 MBit)");
    case 0x1040C8:
      return F("GigaDevice GD25Q12, 64 KB (512 KBit)");

    // Winbond
    case 0x1640EF:
      return F("Winbond W25Q32, 4 MB (32 MBit)");
    case 0x1540EF:
      return F("Winbond W25Q16, 2 MB (16 MBit)");
    case 0x1440EF:
      return F("Winbond W25Q80, 1 MB (8 MBit)");
    case 0x1340EF:
      return F("Winbond W25Q40, 512 KB (4 MBit)");

    // BergMicro
    case 0x1640E0:
      return F("BergMicro BG25Q32, 4 MB (32 MBit)");
    case 0x1540E0:
      return F("BergMicro BG25Q16, 2 MB (16 MBit)");
    case 0x1440E0:
      return F("BergMicro BG25Q80, 1 MB (8 MBit)");
    case 0x1340E0:
      return F("BergMicro BG25Q40, 512 KB (4 MBit)");

    // Fidelix
    case 0x1640A1:
      return F("Fidelix FM25Q32, 4 MB (32 MBit)");
    case 0x1540A1:
      return F("Fidelix FM25Q16, 2 MB (16 MBit)");
    case 0x1440A1:
      return F("Fidelix FM25Q08, 1 MB (8 MBit)");
    case 0x1340A1:
      return F("Fidelix FM25Q04, 512 KB (4 MBit)");

    // XMC
    case 0x164020:
      return F("XMC XM25Q32, 4 MB (32 MBit)");
    case 0x154020:
      return F("XMC XM25Q16, 2 MB (16 MBit)");
    case 0x144020:
      return F("XMC XM25Q08, 1 MB (8 MBit)");
    case 0x134020:
      return F("XMC XM25Q04, 512 KB (4 MBit)");

    // ESP8285 internal flash
    case 0x144051:
      return F("ESP8285 internal, 1 MB (8 MBit)");

    // Default
    default:
      return "Unknown flash chip ID 0x" + String(ESP.getFlashChipId(), HEX);
  }
#else
  #error Only ESP32 and ESP8266 supported
#endif
}

String EspUtils::getRealFlashChipSize() {
#if defined(ESP32)
  uint32_t size = ESP.getFlashChipSize();
  switch (size) {
	case (1ULL * 1024ULL * 1024ULL):
	  return F("1 MB (8 MBit)");
	case (2ULL * 1024ULL * 1024ULL):
	  return F("2 MB (16 MBit)");
	case (4ULL * 1024ULL * 1024ULL):
	  return F("4 MB (32 MBit)");
	case (8ULL * 1024ULL * 1024ULL):
	  return F("8 MB (64 MBit)");
	case (16ULL * 1024ULL * 1024ULL):
	  return F("16 MB (128 MBit)");
	default:
      return F("Unknown");
  }
#elif defined(ESP8266)
  switch ((ESP.getFlashChipId() >> 16) & 0xFF) {
    case 0x20:
      return F("64 MB (512 MBit)");
    case 0x19:
      return F("32 MB (256 MBit)");
    case 0x18:
      return F("16 MB (128 MBit)");
    case 0x17:
      return F("8 MB (64 MBit)");
    case 0x16:
      return F("4 MB (32 MBit)");
    case 0x15:
      return F("2 MB (16 MBit)");
    case 0x14:
      return F("1 MB (8 MBit)");
    case 0x13:
      return F("512 KB (4 MBit)");
    case 0x12:
      return F("256 KB (2 MBit)");
    case 0x11:
      return F("128 KB (1 MBit)");
    case 0x10:
      return F("64 KB (512 KBit)");
    case 0x09:
      return F("32 KB (256 KBit)");
    case 0x08:
      return F("16 KB (128 KBit)");
    case 0x07:
      return F("8 KB (64 KBit)");
    default:
      return F("Unknown");
  }
#else
  #error Only ESP32 and ESP8266 supported
#endif
}

uint32_t EspUtils::getChipId() {
#if defined(ESP32)
  return (uint32_t) ESP.getEfuseMac();
#elif defined(ESP8266)
  return ESP.getChipId();
#else
  #error Only ESP32 and ESP8266 supported
#endif
}
