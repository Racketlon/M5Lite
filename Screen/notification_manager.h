#ifndef NOTIFICATION_MANAGER_H
#define NOTIFICATION_MANAGER_H

#include <string>
#include <M5EPD.h>

class NotificationManager {
private:
    M5EPD_Canvas canvas;

public:
    NotificationManager() : canvas(&M5.EPD) {}

    void show_notification(const std::string &message, int duration = 3000) {
        canvas.fillCanvas(15); // White background
        canvas.setTextColor(0); // Black text
        canvas.setTextSize(2);
        canvas.drawString(message.c_str(), 10, 10);
        canvas.pushCanvas(0, 0);

        delay(duration); // Keep the notification visible
        clear_notification();
    }

    void clear_notification() {
        canvas.fillCanvas(15); // Clear the canvas
        canvas.pushCanvas(0, 0);
    }
};

#endif // NOTIFICATION_MANAGER_H
