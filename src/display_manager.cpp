#include "display_manager.h"
#include "enc_debug.h"
#include "Arduino.h"

// We assume a max display size for the frame.
#define DISPLAY_DIGITS 10
typedef unsigned long DisplayFrame[DISPLAY_DIGITS];

extern QueueHandle_t frameQueue;

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
        // The animation has updated the driver's internal buffer.
        // Now, get a copy of that buffer and send it to the queue.
        DisplayFrame frame;
        _display.getFrameData(frame);
        
        // Overwrite the queue with the latest frame.
        // The displayTask will pick this up on its next loop.
        xQueueOverwrite(frameQueue, &frame);
    }
}

bool DisplayManager::isAnimationRunning() const {
    // The animation is running if the unique_ptr is not null
    return _currentAnimation != nullptr;
}