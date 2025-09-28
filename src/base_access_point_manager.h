#ifndef BASE_ACCESS_POINT_MANAGER_H
#define BASE_ACCESS_POINT_MANAGER_H

#include "enc_types.h"

#include <ESPAsyncWebServer.h>
#include <WiFi.h>
#include <DNSServer.h> 
#include <vector>


#define PASSWORD_MASKED "********" 

class AppPreferences;

class BaseAccessPointManager {
public:
    BaseAccessPointManager(AppPreferences& prefs);
    virtual ~BaseAccessPointManager() = default;

    virtual void setup(const char* hostName);
    void loop();
    bool isClientConnected() const { return _isClientConnected; } // <-- ADD THIS

protected:
    friend void onWifiEvent(WiFiEvent_t event); // Allow callback to access private members
    void setClientConnected(bool connected) { _isClientConnected = connected; } // <-- ADD THIS

    AppPreferences& _prefs;
    std::vector<FormField> _formFields;
    virtual void initializeFormFields();

private:
    DNSServer _dnsServer;
    AsyncWebServer _server;
    bool _isClientConnected = false; // <-- ADD THIS

    String generateForm();
    String generateJavascript();
    String assembleHtml();
    void setupServer();
};

#endif // BASE_ACCESS_POINT_MANAGER_H
