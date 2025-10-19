#include "display_manager.h"
#include "enc_debug.h"
#include "Arduino.h" // Needed for FreeRTOS types

// NEW: Get the queue handle from the main .ino file
extern QueueHandle_t displayTriggerQueue;

DisplayManager::DisplayManager(IDisplayDriver& display) : _display(display) {}

void DisplayManager::begin() {
    _display.begin();
    _display.setBrightness(8);
}

void DisplayManager::setAnimation(std::unique_ptr<IAnimation> animation) {
    _currentAnimation = std::move(animation);
    if (_currentAnimation) {
        _currentAnimation->setup(&_display);
    }
}

void DisplayManager::update() {
    if (_currentAnimation) {
        _currentAnimation->update();
        if (_currentAnimation->isDone()) {
            _currentAnimation.reset();
        }
    }

    bool needsUpdate = _display.needsContinuousUpdate();
    
    if (needsUpdate) {
        // OLD logic:
        // _display.writeDisplay();
        
        // NEW logic:
        // Send a non-blocking trigger to the high-priority displayTask.
        // If the queue is full (which it will be if the displayTask
        // is still busy), this message is simply dropped. This is
        // the correct behavior for a high-frequency trigger.
        int dummy = 1;
        xQueueSend(displayTriggerQueue, &dummy, 0); 
    }
}

bool DisplayManager::isAnimationRunning() const {
    // The animation is running if the unique_ptr is not null
    return _currentAnimation != nullptr;
}