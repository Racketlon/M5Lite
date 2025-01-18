#include <M5EPD.h>
#include <SD.h> // Ensure the correct library is included
#include "../pulse/compiler/Compiler.h"
#include "../Screen/screen_manager.h"
#include "../Screen/gesture.h"
#include "../Screen/status_bar.h"
#include "../Screen/app_manager.h"

M5EPD_Canvas canvas(&M5.EPD);
ScreenManager screenManager(&canvas);
StatusBar statusBar;
AppManager appManager(&canvas);

void setup() {
    M5.begin();
    M5.EPD.Clear(true);

    if (!SD.begin()) {
        canvas.drawString("SD Card Initialization Failed!", 10, 10, 1);
        canvas.pushCanvas(0, 0, UPDATE_MODE_GC16);
        while (true);
    }

    screenManager.set_status_bar(&statusBar);

    File appsFolder = SD.open("/Apps");
    if (appsFolder && appsFolder.isDirectory()) {
        File appFile = appsFolder.openNextFile();
        while (appFile) {
            String fileName = appFile.name();
            if (fileName.endsWith(".pls")) {
                appManager.register_app(fileName.substring(0, fileName.lastIndexOf('.')),
                                        "/Apps/" + fileName);
            }
            appFile = appsFolder.openNextFile();
        }
    }

    screenManager.set_initial_screen(&statusBar);
}

void loop() {
    screenManager.update();

    if (screenManager.has_gesture()) {
        Gesture gesture = screenManager.get_gesture();
        appManager.handle_gesture(gesture);
    }

    screenManager.refresh();
}
