idf_component_register(
    SRCS 
        "Network/network.cpp" 
        "Storage/storage.cpp"
        "Bluetooth/bluetooth.cpp"          # Ensure this file exists
        "Screen/Display/display.cpp"
        "Screen/Keyboard/keyboard.cpp"
        "Screen/Touch/touch.cpp"
    INCLUDE_DIRS 
        "."
        "Network"
        "Storage"
        "Bluetooth"
        "Screen/Display"
        "Screen/Keyboard"
        "Screen/Touch"
    REQUIRES 
        # Add any ESP-IDF components if used, e.g., driver, esp_wifi
)
