#ifndef COMPILER_H
#define COMPILER_H

#include <string>
#include <map>
#include <functional>
#include <Arduino.h>
#include <M5EPD.h>  // Include the library for M5Paper handling

/**
 * @class Compiler
 * @brief A class to compile UI components into executable code for M5Paper.
 */
class Compiler {
private:
    /**
     * @struct Label
     * @brief Represents a label with text, position, and font size.
     */
    struct Label {
        std::string text; ///< The text of the label.
        int x;            ///< The x-coordinate of the label.
        int y;            ///< The y-coordinate of the label.
        int fontSize;     ///< The font size of the label.
    };

    /**
     * @struct Button
     * @brief Represents a button with text, position, size, and a callback.
     */
    struct Button {
        std::string text; ///< The text displayed on the button.
        int x;            ///< The x-coordinate of the button.
        int y;            ///< The y-coordinate of the button.
        int width;        ///< The width of the button.
        int height;       ///< The height of the button.
        std::function<void()> onClick; ///< The function to execute when the button is clicked.
    };

    std::map<std::string, Label> labels; ///< A collection of labels indexed by name.
    std::map<std::string, Button> buttons; ///< A collection of buttons indexed by name.
    M5EPD_Canvas canvas; ///< The canvas for drawing on the M5Paper display.

public:
    /**
     * @brief Constructs a new Compiler object and initializes the canvas.
     */
    Compiler() : canvas(&M5.EPD) {}

    /**
     * @brief Initializes the display and prepares the canvas.
     */
    void setupDisplay() {
        M5.begin();
        M5.EPD.Clear(true);  // Clear the display
        canvas.createCanvas(540, 960);
        canvas.fillCanvas(15);  // Fill with white
    }

    /**
     * @brief Adds a label to the display.
     * 
     * @param name The unique name of the label.
     * @param text The text of the label.
     * @param x The x-coordinate of the label.
     * @param y The y-coordinate of the label.
     * @param fontSize The font size of the label.
     */
    void addLabel(const std::string &name, const std::string &text, int x, int y, int fontSize) {
        labels[name] = {text, x, y, fontSize};
    }

    /**
     * @brief Adds a button to the display.
     * 
     * @param name The unique name of the button.
     * @param text The text displayed on the button.
     * @param x The x-coordinate of the button.
     * @param y The y-coordinate of the button.
     * @param width The width of the button.
     * @param height The height of the button.
     * @param onClick The function to execute when the button is clicked.
     */
    void addButton(const std::string &name, const std::string &text, int x, int y, int width, int height, std::function<void()> onClick) {
        buttons[name] = {text, x, y, width, height, onClick};
    }

    /**
     * @brief Draws all labels on the canvas.
     */
    void drawLabels() {
        for (const auto &[name, label] : labels) {
            canvas.setTextSize(label.fontSize);
            canvas.drawString(label.text.c_str(), label.x, label.y);
        }
    }

    /**
     * @brief Draws all buttons on the canvas.
     */
    void drawButtons() {
        for (const auto &[name, button] : buttons) {
            canvas.fillRect(button.x, button.y, button.width, button.height, 0);  // Black button
            canvas.setTextSize(2);
            canvas.setTextColor(15, 0);  // White text on black button
            canvas.drawString(button.text.c_str(), button.x + 10, button.y + 10);
        }
    }

    /**
     * @brief Handles touch input and triggers button callbacks if applicable.
     * 
     * @param touchX The x-coordinate of the touch input.
     * @param touchY The y-coordinate of the touch input.
     */
    void handleTouch(int touchX, int touchY) {
        for (const auto &[name, button] : buttons) {
            if (touchX >= button.x && touchX <= button.x + button.width &&
                touchY >= button.y && touchY <= button.y + button.height) {
                button.onClick();
            }
        }
    }

    /**
     * @brief Draws all components and updates the display.
     */
    void run() {
        drawLabels();
        drawButtons();
        canvas.pushCanvas(0, 0, UPDATE_MODE_GC16);  // Push updates to the display
    }
};

#endif
