#ifndef APP_MANAGER_H
#define APP_MANAGER_H

#include <M5EPD.h>
#include <vector>

class AppManager {
private:
    M5EPD_Canvas* canvas;
    std::vector<String> registeredApps;

public:
    AppManager(M5EPD_Canvas* canvas) : canvas(canvas) {}

    void register_app(const String& app_name, const String& app_path) {
        // Register app logic
        registeredApps.push_back(app_name);
    }

    void handle_gesture(const Gesture& gesture) {
        // Handle gestures for apps
    }
};

#endif
