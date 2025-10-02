#include "base_ntp_clock_app.h"
#include <Wire.h>

BaseNtpClockApp::BaseNtpClockApp(BasePreferences& prefs, BaseAccessPointManager& apManager)
    : _prefs(prefs), _apManager(apManager) {}

void BaseNtpClockApp::setup() {
    Wire.begin();
    _prefs.setup();

    _bootManager = std::make_unique<BootManager>(*this);
    if (_bootManager->checkForForceAPMode()) {
        activateAccessPoint();
        return; // Loop forever in AP mode
    }

    _fsmManager = std::make_unique<ClockFsmManager>(*this);
    _sceneManager = std::make_unique<SceneManager>(*this);
    _fsmManager->setup();
}

void BaseNtpClockApp::loop() {
    if (_fsmManager) _fsmManager->update();
    if (_sceneManager) _sceneManager->update();
    getClock().update();
}
