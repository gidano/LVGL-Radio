#pragma once

#include <array>

#include <lvgl.h>

#include "../../audio/AudioSnapshot.h"

class WaveVu {
 public:
  enum class Mode : uint8_t { Spectrum, Stereo, Off };

  void create(lv_obj_t* parent);
  void setBackgroundSource(const uint16_t* fullPixels, int32_t fullWidth,
                           uint8_t opacity, bool enabled);
  void setModeChangedCallback(void* context,
                              void (*callback)(void*, uint8_t));
  void setMode(Mode mode);
  void update(const AudioLevels& levels);
  lv_obj_t* object() const;
  Mode mode() const;
  bool active() const;

 private:
  static void touchEvent(lv_event_t* event);
  void render();
  void renderSpectrum();
  void renderStereo();
  void renderOff();
  void clear(uint16_t color);
  void fillRect(int32_t x, int32_t y, int32_t width, int32_t height,
                uint16_t color);
  static uint8_t approach(uint8_t value, uint8_t target);

  static constexpr int32_t kWidth = 240;
  static constexpr int32_t kHeight = 62;
  static constexpr int32_t kLeft = 0;
  static constexpr int32_t kTop = 258;

  lv_obj_t* root_{nullptr};
  lv_obj_t* canvas_{nullptr};
  lv_obj_t* leftLabel_{nullptr};
  lv_obj_t* rightLabel_{nullptr};
  void* modeChangedContext_{nullptr};
  void (*modeChangedCallback_)(void*, uint8_t){nullptr};
  uint16_t* pixels_{nullptr};
  uint16_t* backgroundPixels_{nullptr};
  std::array<uint8_t, AudioLevels::kSpectrumBands> levels_{};
  std::array<uint8_t, AudioLevels::kSpectrumBands> peaks_{};
  std::array<uint8_t, AudioLevels::kSpectrumBands> peakHold_{};
  uint8_t left_{0};
  uint8_t right_{0};
  uint8_t leftPeak_{0};
  uint8_t rightPeak_{0};
  uint8_t leftHold_{0};
  uint8_t rightHold_{0};
  Mode mode_{Mode::Spectrum};
  lv_point_t pressedAt_{};
};
