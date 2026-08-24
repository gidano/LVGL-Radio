#include "DisplayDevice.h"

#include "options.h"

DisplayDevice::DisplayDevice() {
  {
    auto config = bus_.config();
    config.spi_host = SPI2_HOST;
    config.spi_mode = 0;
    config.freq_write = 40000000;
    config.freq_read = 16000000;
    config.spi_3wire = true;
    config.use_lock = true;
    config.dma_channel = SPI_DMA_CH_AUTO;
    config.pin_sclk = TFT_SCK;
    config.pin_mosi = TFT_MOSI;
#if TOUCH_ENABLED && TS_MODEL == TS_MODEL_XPT2046
    // GPIO13 fizikailag az XPT2046 MISO-ja. Az ILI9488 olvasása tiltott.
    config.pin_miso = TS_MISO;
#else
    config.pin_miso = -1;
#endif
    config.pin_dc = TFT_DC;
    bus_.config(config);
    panel_.setBus(&bus_);
  }

  {
    auto config = panel_.config();
    config.pin_cs = TFT_CS;
    config.pin_rst = TFT_RST;
    config.pin_busy = -1;
    config.panel_width = 320;
    config.panel_height = 480;
    config.memory_width = 320;
    config.memory_height = 480;
    config.offset_x = 0;
    config.offset_y = 0;
    config.offset_rotation = 0;
    config.readable = false;
    config.invert = false;
    config.rgb_order = false;
    config.dlen_16bit = false;
    config.bus_shared = true;
    panel_.config(config);
  }

#if TOUCH_ENABLED
  {
    auto config = touch_.config();
#if TS_MODEL == TS_MODEL_FT6X36
    config.x_min = 0;
    config.x_max = 319;
    config.y_min = 0;
    config.y_max = 479;
    config.pin_int = TS_INT;
    config.pin_rst = TS_RST;
    config.bus_shared = false;
    config.offset_rotation = 0;
    config.i2c_port = 0;
    config.i2c_addr = 0x38;
    config.pin_sda = TS_SDA;
    config.pin_scl = TS_SCL;
    config.freq = 400000;
#else
    config.x_min = 0;
    config.x_max = 4095;
    config.y_min = 0;
    config.y_max = 4095;
    config.pin_int = -1;
    config.bus_shared = true;
    config.offset_rotation = 0;
    config.spi_host = SPI2_HOST;
    config.freq = 1000000;
    config.pin_sclk = TFT_SCK;
    config.pin_mosi = TFT_MOSI;
    config.pin_miso = TS_MISO;
    config.pin_cs = TS_CS;
#endif
    touch_.config(config);
    panel_.setTouch(&touch_);
  }
#endif

  setPanel(&panel_);
}

void DisplayDevice::prepareTouch() {
#if TOUCH_ENABLED
  // A touch vezerlo konfiguracioja a konstruktorban keszul el;
  // az inicializalast a kesobbi LGFX_Device::init() vegzi.
#else
  // Nem erintos build: nincs touch vezerlo es nincs kalibracio.
#endif
}
