#ifndef EspUtils_h
#define EspUtils_h

#include <WString.h>

class EspUtils {
  public:
  static String getFlashChipIdentification();
  static String getRealFlashChipSize();
  static uint32_t getChipId();
};

#endif

