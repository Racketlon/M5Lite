#ifndef APP_LAYOUT_H
#define APP_LAYOUT_H

#include <vector>
#include <string>
#include <M5EPD.h> // Include the M5EDP library for screen handling

using namespace std;

class Layout {
private:
    int appSize {60}; // Size of a side of the app -> X and Y
    int paddingX {20}; // Space between apps horizontally
    int paddingY {30}; // Space between apps vertically
    const int screenWidth {540};   // Screen width
    const int screenHeight {960};  // Screen height
    M5EPD_Canvas canvas; // Canvas for drawing apps dynamically

    vector<vector<string>> positions; // 2D Array of App positions

public:
    Layout() : canvas(&M5.EPD) { // Default constructor with no parameters
        calculate_positions(); // Initialize positions based on default sizes
    }

    /**
     * Update app size
     */
    void change_app_size(int newSize) {
        appSize = newSize;
        calculate_positions(); // Recalculate positions
    }

    /**
     * Update horizontal padding
     */
    void change_padx_size(int new_padx_size) {
        paddingX = new_padx_size;
        calculate_positions();
    }

    /**
     * Update vertical padding
     */
    void change_pady_size(int new_pady_size) {
        paddingY = new_pady_size;
        calculate_positions();
    }

    /**
     * Calculate app positions based on the screen size, app size, and paddings
     */
    void calculate_positions() {
        positions.clear();
        int cols = (screenWidth + paddingX) / (appSize + paddingX);
        int rows = (screenHeight + paddingY) / (appSize + paddingY);

        for (int row = 0; row < rows; ++row) {
            vector<string> row_positions;
            for (int col = 0; col < cols; ++col) {
                row_positions.push_back(to_string(row) + "," + to_string(col));
            }
            positions.push_back(row_positions);
        }
    }

    /**
     * Draw the layout on the canvas
     */
    void draw_layout() {
        canvas.fillCanvas(15); // Clear canvas with a white background
        canvas.setTextSize(2);

        for (int row = 0; row < positions.size(); ++row) {
            for (int col = 0; col < positions[row].size(); ++col) {
                int x = col * (appSize + paddingX);
                int y = row * (appSize + paddingY);
                canvas.drawRect(x, y, appSize, appSize, 0); // Draw app boundary
                canvas.drawString("App", x + appSize / 4, y + appSize / 4);
            }
        }
        canvas.pushCanvas(0, 0); // Push canvas to screen
    }
};

#endif // APP_LAYOUT_H
