#include "DilbertMenuApp.h"

#define OFFSET(a, d) (((m_itemSize + 1) * d) * a)
#define OFFSET_X(x) OFFSET(x, 6)
#define OFFSET_Y(y) OFFSET(y, 8)

DilbertMenuApp::DilbertMenuApp(uint8_t itemSize, uint16_t bgColour,
                               uint16_t textColour, uint16_t iconColour)
    : DilbertApp("App Menu")
    , m_itemSize(itemSize)
    , m_backgroundColour(bgColour)
    , m_textColour(textColour)
    , m_iconColour(iconColour)
    , m_selectedAppIndex(0)
{
}

DilbertMenuApp::~DilbertMenuApp()
{
}

void DilbertMenuApp::create()
{
  DilbertApp::create();
  m_selectedAppIndex = 0;
}

void DilbertMenuApp::onEntry()
{
  DilbertApp::onEntry();

  Adafruit_ILI9341 &display = m_badge->display();

  display.fillScreen(m_backgroundColour);
  display.setTextColor(m_textColour);
  display.setTextSize(m_itemSize);

  /* Print application names */
  for (uint8_t i = 0; i < m_manager->numApps(); i++)
  {
    display.setCursor(OFFSET_X(1), 10 + OFFSET_Y(i));
    display.print(m_manager->app(i)->name());
  }

  redrawSelectonIcon();
}

bool DilbertMenuApp::handleButton(IButton *button)
{
  if (DilbertApp::handleButton(button))
    return true;

  if (!button->isActive())
  {
    switch (button->getID())
    {
    case Dilbert::BUTTON_DOWN:
      m_selectedAppIndex++;
      if (m_selectedAppIndex >= m_manager->numApps())
        m_selectedAppIndex = 0;
      redrawSelectonIcon();
      break;

    case Dilbert::BUTTON_UP:
      if (m_selectedAppIndex == 0)
        m_selectedAppIndex = m_manager->numApps();
      m_selectedAppIndex--;
      redrawSelectonIcon();
      break;

    case Dilbert::BUTTON_B:
      m_selectedAppIndex = 0;
      redrawSelectonIcon();
      break;

    case Dilbert::BUTTON_A:
      /* Launch selected app */
      m_manager->activateAppByIdx(m_selectedAppIndex);
      return true;

    default:
      return false;
    }

    return true;
  }

  return false;
}

void DilbertMenuApp::redrawSelectonIcon()
{
  /* Clear display around selection arow position */
  m_badge->display().fillRect(0, 0, OFFSET_X(1) - 1, 319, ILI9341_BLACK);

  /* Draw selection arrow */
  m_badge->display().setTextColor(m_iconColour);
  m_badge->display().setCursor(1, 10 + OFFSET_Y(m_selectedAppIndex));
  m_badge->display().print(">");
}