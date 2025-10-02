#include "scene_manager.h"
#include "enc_debug.h"
#include "i_weather_clock.h"

#include "anim_slot_machine.h"
#include "anim_matrix.h"
#include "anim_scrolling_text.h"

SceneManager::SceneManager(IBaseClock& clock) : _app(clock) {}

void SceneManager::setup(const DisplayScene* playlist, int numScenes) {
    _scenePlaylist = playlist;
    _numScenes = numScenes;
    _currentSceneIndex = -1;
    _sceneStartTime = 0;    
}

void SceneManager::update() {
    // This logic only runs if the app says it's okay (e.g., FSM is in the right state)
    if (_app.isOkToRunScenes() == false) {
        return;
    }

    unsigned long currentTime = millis();
    if (_app.getClock().isAnimationRunning()) {
        return;
    }

    const DisplayScene& currentScene = _scenePlaylist[_currentSceneIndex];
    if (_currentSceneIndex < 0 || (currentTime - _sceneStartTime >= currentScene.duration_ms)) {
        int nextIndex = _currentSceneIndex;
        
        const char* units = "imperial"; // Default
        IWeatherClock* weather_app = _app.asWeatherClock(); // Safely check for weather support
        if (weather_app) {
            units = weather_app->getTempUnit();
        }
        
        while (true) {
            nextIndex = (nextIndex + 1) % _numScenes;
            const DisplayScene& nextScene = _scenePlaylist[nextIndex];
            
            if (strcmp(nextScene.scene_name, "Temperature") == 0) {
                bool isImperialScene = (strstr(nextScene.format_string, "F") != nullptr);
                if ((strcmp(units, OWM_UNIT_IMPERIAL) == 0 && isImperialScene) || (strcmp(units, OWM_UNIT_METRIC) == 0 && !isImperialScene)) {
                    break;
                }
            } else {
                break;
            }
        }
        _currentSceneIndex = nextIndex;
        _sceneStartTime = millis();

        const DisplayScene& newScene = _scenePlaylist[_currentSceneIndex];

        char buffer[12];
        time_t now = _app.isRtcActive() ? _app.getRtc().now().unixtime() : time(0);
        if (strcmp(newScene.scene_name, "Time") == 0 || strcmp(newScene.scene_name, "Date") == 0) {
            _app.formatTime(buffer, sizeof(buffer), newScene.format_string, now);
        } else {
            float value = newScene.getDataValue();
            if (value == UNSET_VALUE) {
                strncpy(buffer, "NO DATA", sizeof(buffer));
            } else {
                snprintf(buffer, sizeof(buffer), newScene.format_string, value);
            }
        }

        ENC_LOG("Scene: %s - %s", newScene.scene_name, buffer);
        if (newScene.animation_type == SLOT_MACHINE) {
            auto anim = std::make_unique<SlotMachineAnimation>(buffer, newScene.anim_param_1, 2000, newScene.anim_param_2, newScene.dots_with_previous);
            _app.getClock().setAnimation(std::move(anim));
        } else if (newScene.animation_type == MATRIX) {
            auto anim = std::make_unique<MatrixAnimation>(buffer, newScene.anim_param_1, 2000, newScene.anim_param_2, newScene.dots_with_previous);
            _app.getClock().setAnimation(std::move(anim));
        } else if (newScene.animation_type == SCROLLING) {
            auto anim = std::make_unique<ScrollingTextAnimation>(buffer, newScene.anim_param_1, newScene.dots_with_previous);
            _app.getClock().setAnimation(std::move(anim));
        }
    } else {
        if (currentScene.animation_type == SCROLLING) {
            return;
        }
        char buffer[12];
        time_t now = _app.isRtcActive() ? _app.getRtc().now().unixtime() : time(0);
        if (strcmp(currentScene.scene_name, "Time") == 0 || strcmp(currentScene.scene_name, "Date") == 0) {
            _app.formatTime(buffer, sizeof(buffer), currentScene.format_string, now);
        } else {
            float value = currentScene.getDataValue();
            if (value == UNSET_VALUE) {
                strncpy(buffer, "NO DATA", sizeof(buffer));
            } else {
                snprintf(buffer, sizeof(buffer), currentScene.format_string, value);
            }
        }
        _app.getDisplay().print(buffer, currentScene.dots_with_previous);
    }
}


