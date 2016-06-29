#ifndef _DILBERT_H_
#define _DILBERT_H_

#include <Adafruit_NeoPixel.h>
#include <Adafruit_ILI9341.h>
#include <UniversalInputManager.h>

#include "Adafruit_MCP23017.h"

/**
 * @class Dilbert
 * @author Dan Nixon
 * @brief Main hardware abstraction class.
 */
class Dilbert
{
public:
  static const uint8_t MCP23017_INT_GPIO = 1; // UART0 Tx
  static const uint8_t SD_CS_GPIO = 3;        // UART0 Rx
  static const uint8_t TFT_CS_GPIO = 0;
  static const uint8_t TFT_DC_GPIO = 2;
  static const uint8_t TFT_BACKLIGHT_GPIO = 16;
  static const uint8_t NEOPIXEL_GPIO = 15;

  static const uint8_t BUTTON_UP = 1;
  static const uint8_t BUTTON_DOWN = 2;
  static const uint8_t BUTTON_LEFT = 0;
  static const uint8_t BUTTON_RIGHT = 3;
  static const uint8_t BUTTON_A = 4;
  static const uint8_t BUTTON_B = 5;

public:
  Dilbert(size_t numNeoPixels = 8);
  virtual ~Dilbert();

  /**
   * @brief Gets the TFT display driver.
   * @returns Reference to display driver
   */
  inline Adafruit_ILI9341 &display()
  {
    return *m_tftDisplay;
  }

  /**
   * @brief Gets the backlight intensity.
   * @return Intensity
   *
   * Where 0 is off and 1023 is brightest.
   */
  uint16_t backlight() const
  {
    return m_backlightIntensity;
  }

  void setBacklightOn(bool on);
  void setBacklight(uint16_t intensity);

  /**
   * @brief Gets the NeoPixel LED driver.
   * @return Reference to NeoPixel driver
   */
  inline Adafruit_NeoPixel &neoPixels()
  {
    return *m_neopixels;
  }

  /**
   * @brief Gets the IO expender driver.
   * @return Reference to the IO expander driver
   *
   * Warning: some of the IO pins are used for specific functions that are
   * managed elsewhere, do not set a pin that alreadyhas a function, this will
   * probably break something else.
   */
  inline Adafruit_MCP23017 &io()
  {
    return *m_io;
  }

  inline UniversalInputManager &buttons()
  {
    return *m_buttons;
  }

private:
  Adafruit_MCP23017 *m_io;

  Adafruit_ILI9341 *m_tftDisplay;
  uint16_t m_backlightIntensity;

  UniversalInputManager *m_buttons;

  Adafruit_NeoPixel *m_neopixels;
};

#endif
