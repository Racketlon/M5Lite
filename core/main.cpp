#include <M5EPD.h>
#include <SD.h> 
#include "pulse/compiler/Compiler.h"
#include "screen/screen_manager.h"
#include "screen/task_manager.h"
#include "screen/layout/app_layout.h"
#include "screen/layout/app_manager.h"
#include "screen/layout/app_viewer.h"
#include "screen/layout/gesture.h"
#include "screen/ui/notification_manager.h"
#include "screen/ui/status_bar.h"
#include "kernel.h"

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
            if (fileName.endsWith(".pulse")) {
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
