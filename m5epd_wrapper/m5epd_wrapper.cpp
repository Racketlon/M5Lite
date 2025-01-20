#include "components/M5EPD/include/M5EPD.h"

extern "C" {
    void epd_init() {
        M5.begin();
        M5.EPD.begin();
    }

    void epd_draw_text(const char* text, int x, int y) {
        M5.EPD.Clear(true);
        M5.EPD.WriteString(text, x, y);
        M5.EPD.Update();
    }
}
