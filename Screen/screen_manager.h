#ifndef SCREEN_MANAGER_H
#define SCREEN_MANAGER_H

#include <M5EPD.h>
#include "status_bar.h"
#include "gesture.h"

class ScreenManager {
private:
    M5EPD_Canvas* canvas;
    StatusBar* statusBar;

public:
    ScreenManager(M5EPD_Canvas* canvas) : canvas(canvas), statusBar(nullptr) {}

    void set_status_bar(StatusBar* bar) {
        statusBar = bar;
        if (canvas) statusBar->attach_canvas(canvas);
    }

    void set_initial_screen(StatusBar* bar) {
        set_status_bar(bar);
    }

    void update() {
        if (statusBar) {
            statusBar->draw_status_bar("Welcome to M5Lite", 85); // Example data
        }
    }

    bool has_gesture() {
        // Placeholder for detecting a gesture
        return false;
    }

    Gesture get_gesture() {
        // Placeholder for returning a detected gesture
        Gesture gesture;
        gesture.direction = Gesture::NONE; // Default to no gesture
        return gesture;
    }

    void refresh() {
        if (canvas) canvas->pushCanvas(0, 0, UPDATE_MODE_GC16);
    }
};

#endif
