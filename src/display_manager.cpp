#include "display_manager.h"
#include "enc_debug.h"
#include "Arduino.h"

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
    bool animationFinished = false;

    if (_currentAnimation) {
        _currentAnimation->update();
        if (_currentAnimation->isDone()) {
            _currentAnimation.reset();
            animationFinished = true; // Set the flag
        }
    }

    // If an animation just finished OR if no animation is running,
    // we still need to tell the driver to push its current buffer state
    // to the physical display hardware.
    // For drivers that need continuous updates (like VFDs handled by a task),
    // this call might do nothing, which is fine.
    _display.writeDisplay();

    // If an animation just finished, clear the display *after* writing the last frame
    // if (animationFinished) {
    //     _display.clear();
    //     _display.writeDisplay(); // Write the cleared state
    // }
}

bool DisplayManager::isAnimationRunning() const {
    // The animation is running if the unique_ptr is not null
    return _currentAnimation != nullptr;
}