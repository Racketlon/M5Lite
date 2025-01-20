#ifndef M5EPD_WRAPPER_H
#define M5EPD_WRAPPER_H

#ifdef __cplusplus
extern "C" {
#endif

void epd_init();
void epd_draw_text(const char* text, int x, int y);

#ifdef __cplusplus
}
#endif

#endif // M5EPD_WRAPPER_H
