#ifndef APP_VIEWER_H
#define APP_VIEWER_H

#include <vector>
#include <string>
#include <M5EPD.h> // Include the M5EDP library for screen handling
#include "gesture.h" // Include gesture detection for swipe actions 

using namespace std;

class AppViewer {
private:
    struct App {
        string name;
        function<void()> execute; // Function pointer to the app's execution logic
        bool isRunning;
    };

    vector<App> runningApps; // List of currently running apps
    App *activeApp = nullptr; // Currently active app
    M5EPD_Canvas canvas; // Canvas for rendering UI

public:
    AppViewer() : canvas(&M5.EPD) {}

    /**
     * Register a new app to the viewer
     */
    void register_app(const string &name, function<void()> execute) {
        runningApps.push_back({name, execute, false});
    }

    /**
     * Open an app in full screen
     */
    void open_app(const string &name) {
        for (auto &app : runningApps) {
            if (app.name == name) {
                app.isRunning = true;
                activeApp = &app;
                draw_fullscreen_app(app.name);
                app.execute(); // Execute the app logic
                return;
            }
        }
        draw_message("App not found!");
    }

    /**
     * Minimize the active app (swipe up gesture simulation)
     */
    void minimize_active_app() {
        if (activeApp) {
            activeApp = nullptr; // Minimize by setting activeApp to nullptr
        }
    }

    /**
     * Show all currently running apps (swipe up and hold simulation)
     */
    void show_running_apps() {
        canvas.fillCanvas(15); // Clear canvas
        canvas.setTextSize(2);
        canvas.drawString("Running Apps:", 10, 10);

        int y = 40;
        for (const auto &app : runningApps) {
            if (app.isRunning) {
                canvas.drawString("- " + app.name, 10, y);
                y += 30;
            }
        }
        canvas.pushCanvas(0, 0);
    }

    /**
     * Close an app (swipe up on app in running apps view)
     */
    void close_app(const string &name) {
        for (auto &app : runningApps) {
            if (app.name == name && app.isRunning) {
                app.isRunning = false;
                return;
            }
        }
        draw_message("App not found or not running!");
    }

    /**
     * Render the full-screen UI for the active app
     */
    void draw_fullscreen_app() {
        canvas.fillCanvas(0); // Black background
        canvas.setTextColor(15); // White text
        canvas.setTextSize(3);
        canvas.pushCanvas(0, 0);
    }

    /**
     * Display a message on the screen
     */
    void draw_message(const string &message) {
        canvas.fillCanvas(15); // White background
        canvas.setTextColor(0); // Black text
        canvas.setTextSize(2);
        canvas.drawString(message, 10, 10);
        canvas.pushCanvas(0, 0);
        delay(2000); // Show the message for 2 seconds
    }

    void handle_swipe_actions() {
        Gesture::SwipeDirection gesture = Gesture::detect_swipe();
        if (gesture == Gesture::UP) {
            minimize_active_app(); // Minimize active app
        } else if (gesture == Gesture::DOWN) {
            show_running_apps(); // Show running apps
        } else if (gesture == Gesture::NONE) {
            // No action
        }
    }
};

#endif // APP_VIEWER_H
