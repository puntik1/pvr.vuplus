#pragma once

#include "client.h"

#include <string>

#include "xbmc_addon_types.h"

class Vu;

namespace VUPLUS
{

static const std::string DEFAULT_HOST = "127.0.0.1";
static const int DEFAULT_CONNECT_TIMEOUT = 30;
static const int DEFAULT_STREAM_PORT = 8001;
static const int DEFAULT_WEB_PORT = 80;
static const int DEFAULT_UPDATE_INTERVAL = 2;
static const std::string DEFAULT_TSBUFFERPATH = "special://userdata/addon_data/pvr.vuplus";
static const int DEFAULT_NUM_GEN_REPEAT_TIMERS = 1;

enum class Timeshift
  : int // same type as addon settings
{
  OFF = 0,
  ON_PLAYBACK,
  ON_PAUSE
};

enum class PrependOutline
  : int // same type as addon settings
{
  NEVER = 0,
  IN_EPG,
  IN_RECORDINGS,
  ALWAYS
};

class Settings
{

public:
  Settings() = default;

  void ReadFromAddon();
  ADDON_STATUS SetValue(const std::string &settingName, const void *settingValue);

  bool IsTimeshiftBufferPathValid() const;

  //Connection
  std::string m_strHostname = DEFAULT_HOST;
  int m_iPortWeb = DEFAULT_WEB_PORT;
  bool m_bUseSecureHTTP = false;
  std::string m_strUsername = "";
  std::string m_strPassword = "";
  bool m_bAutoConfig = false;
  int m_iPortStream = DEFAULT_STREAM_PORT;

  //General
  bool m_bOnlinePicons = true;
  bool m_bUsePiconsEuFormat = false;
  std::string m_strIconPath = "";
  int m_iUpdateInterval = DEFAULT_UPDATE_INTERVAL;
  
  //Channel & EPG
  bool m_bOnlyOneGroup = false;
  std::string m_strOneGroup = "";
  bool m_bZap = false;
  bool m_bExtractExtraEpgInfo = true;
  bool m_bLogMissingGenreMappings = true;

  //Recordings and Timers
  std::string m_strRecordingPath = "";
  bool m_bOnlyCurrentLocation = false;
  bool m_bKeepFolders = false;
  bool m_bEnableGenRepeatTimers = true;
  int  m_iNumGenRepeatTimers = DEFAULT_NUM_GEN_REPEAT_TIMERS;
  bool m_bEnableAutoTimers = true;
  bool m_bAutomaticTimerlistCleanup = false;

  //Timeshift
  Timeshift m_timeshift = Timeshift::OFF;
  std::string m_strTimeshiftBufferPath = DEFAULT_TSBUFFERPATH;

  //Advanced
  PrependOutline m_prependOutline = PrependOutline::IN_EPG;
  bool m_bSetPowerstate = false;
  int m_iReadTimeout = 0;
  int m_streamReadChunkSize = 0;

  //PVR Props
  std::string m_szUserPath = "";
  std::string m_szClientPath = "";

  private:
  template <typename T>
  ADDON_STATUS SetSetting(const std::string& settingName, const void* settingValue, T& currentValue, ADDON_STATUS returnValueIfChanged)
  {
    T newValue =  *static_cast<const T*>(settingValue);
    if (newValue != currentValue)
    {
      XBMC->Log(ADDON::LOG_NOTICE, "%s - Changed Setting '%s' from %d to %d", __FUNCTION__, settingName.c_str(), currentValue, newValue);
      currentValue = newValue;
      return returnValueIfChanged;
    }
    return ADDON_STATUS_OK;
  };

  ADDON_STATUS SetStringSetting(const std::string &settingName, const void* settingValue, std::string &currentValue, ADDON_STATUS returnValueIfChanged);
};

} //namespace VUPLUS
