#ifndef STATUS_BAR_H
#define STATUS_BAR_H

#include <M5EPD.h>
#include <string>

class StatusBar {
private:
    M5EPD_Canvas* canvas;

public:
    StatusBar() : canvas(nullptr) {}

    void attach_canvas(M5EPD_Canvas* canvas_ptr) {
        canvas = canvas_ptr;
    }

    void draw_status_bar(const std::string& message, int battery_level) {
        if (canvas) {
            canvas->fillCanvas(15); // Clear with white
            canvas->drawString(message.c_str(), 10, 10, 1);
            canvas->drawString(("Battery: " + std::to_string(battery_level) + "%").c_str(), 400, 10, 1);
            canvas->pushCanvas(0, 0, UPDATE_MODE_GC16);
        }
    }
};

#endif
