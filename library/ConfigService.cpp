/*! @file */

#include "ConfigService.h"

/**
 * @brief Creates a new configuration service with the default system
 *        configuration.
 */
ConfigService::ConfigService()
{
  setDefaultConfig();
}

/**
 * @brief Sets the default system configuration.
 */
void ConfigService::setDefaultConfig()
{
  m_configData.backButtonExitDelay = 500;
  m_configData.backlightFullBrightness = PWMRANGE;
  m_configData.backlightPowerSaveBrightness = 750;
  m_configData.backlightTimeToPowerSaveMs = 1000;
  m_configData.backlightTimeToOffMs = 0;
}

/**
 * @brief Loads the system configuration from a given storage service.
 * @param storage Storage to load from
 * @return True for a successful load
 */
bool ConfigService::loadFrom(IConfigStorage *storage)
{
  if (storage == nullptr)
    return false;

  return storage->load(&m_configData);
}

/**
 * @brief Saves the system configuration to a given storage service.
 * @param storage Storage to save to
 * @return True for a successful save
 */
bool ConfigService::saveTo(IConfigStorage *storage) const
{
  if (storage == nullptr)
    return false;

  return storage->save(&m_configData);
}
