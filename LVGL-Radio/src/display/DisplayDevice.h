#pragma once

#include <LovyanGFX.hpp>

#include "options.h"

class DisplayDevice : public lgfx::LGFX_Device {
 public:
  DisplayDevice();
  void prepareTouch();

 private:
#if DISPLAY_PROFILE_ST7796
  lgfx::Panel_ST7796 panel_;
#else
  lgfx::Panel_ILI9488 panel_;
#endif
  lgfx::Bus_SPI bus_;
#if TS_MODEL == TS_MODEL_FT6X36
  lgfx::Touch_FT5x06 touch_;
#else
  lgfx::Touch_XPT2046 touch_;
#endif
};
