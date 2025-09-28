#ifndef I_GENERIC_CLOCK_H
#define I_GENERIC_CLOCK_H

#include "display_manager.h"
#include "openweather_client.h" 
#include "RTClib.h"

class AppPreferences; // Keep the forward declaration for now if other parts need it

class IGenericClock {
public:
    virtual ~IGenericClock() {}

    virtual const char* getSsid() const = 0;
    virtual const char* getPassword() const = 0;
    virtual const char* getTimezone() const = 0;

    virtual bool isOkToRunScenes() const = 0;

    virtual const char* getTempUnit() const = 0;
    virtual const char* getOwmApiKey() const = 0;
    virtual const char* getOwmCity() const = 0;
    virtual const char* getOwmStateCode() const = 0;
    virtual const char* getOwmCountryCode() const = 0;
    virtual void setWeatherData(const OpenWeatherData& data) = 0;

    virtual void formatTime(char *txt, unsigned txt_size, const char *format, time_t now) = 0;
    
    virtual IDisplayDriver& getDisplay() = 0;
    virtual DisplayManager& getClock() = 0;
    virtual RTC_DS1307& getRtc() = 0;
    virtual bool isRtcActive() const = 0;
    virtual void syncRtcFromNtp() = 0;
    virtual const char* getAppName() const = 0;
    virtual void activateAccessPoint() = 0;
};

#endif // I_GENERIC_CLOCK_H
