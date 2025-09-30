#ifndef BOOT_MANAGER_H
#define BOOT_MANAGER_H

// Forward declaration to avoid including the full header
class IGenericClock;

class BootManager {
public:
    // The constructor takes the generic clock interface
    BootManager(IGenericClock& clock);

    // This function will contain all the logic and return true if AP mode should be activated.
    bool checkForForceAPMode();

private:
    IGenericClock& _clock;
    const int _resetWindowSeconds = 5; // 5-second window for double reset
};

#endif // BOOT_MANAGER_H
