# M5Lite

This repository is dedicated to the development and deployment of a custom operating system for the M5Paper device, implemented in Rust. It provides all the necessary tools, libraries, and scripts for creating and managing applications using the Pulse programming language, as well as flashing the OS onto the M5Paper hardware.

---

## Folder Structure

```
/
├── apps/                      # Prebuilt Pulse apps for the OS
│   ├── Notes.pulse
│   ├── Settings.pulse
│   ├── Terminal.pulse
│   └── Weather.pulse
├── build/                     # Build artifacts and logs
│   └── logs/
├── config/                    # Configuration files for the OS
├── core/                      # Core OS files
│   ├── FreeRTOS/              # Optional FreeRTOS kernel (if needed)
│   ├── kernel.rs              # Kernel-related headers
│   └── main.rs                # Main OS entry point
├── flash/                     # Scripts for flashing the OS
│   ├── flash_os.py
│   └── install_pulse.py
├── lib/                       # Libraries used in the OS
│   ├── Bluetooth/
│   │   └── bluetooth.rs
│   ├── Network/
│   │   └── Network.rs
│   └── System/
│       ├── file_management.rs
│       └── System.rs
├── LICENSE
├── pulse/                     # Pulse programming language and interpreter
│   ├── compiler/
│   │   ├── Compiler.rs
│   │   └── examples/
│   │       ├── counter.pulse
│   │       └── helloworld.pulse
│   ├── interpreter/
│   │   ├── Interpreter.py
│   │   └── vm.py
│   ├── lib/
│   │   ├── Bluetooth.rs
│   │   ├── System.rs
│   │   └── Wifi.rs
│   ├── main.py                # Entry point for Pulse interpreter
│   └── tests/                 # Test cases for the Pulse interpreter
├── README.md
├── screen/                    # UI and screen-related components
│   ├── layout/
│   │   ├── app_layout.rs
│   │   ├── app_manager.rs
│   │   ├── app_viewer.rs
│   │   └── gesture.rs
│   ├── screen_manager.rs
│   ├── task_manager.rs
│   └── ui/
│       ├── keyboard.rs
│       ├── notification_manager.rs
│       └── status_bar.rs
└── tests/                     # General tests for the OS
```

---

## Features

- **Pulse Language Support:**
  - Develop GUI-based applications using the Pulse programming language.
  - Examples and prebuilt apps demonstrate the versatility of Pulse.

- **Modular Design:**
  - Organized folder structure for clear separation of responsibilities.
  - Allows for easy maintenance and expansion.

- **Custom OS Core:**
  - Designed specifically for the M5Paper hardware.
  - Built on Rust, with optional FreeRTOS kernel support for real-time features.

- **Prebuilt Apps:**
  - Ready-to-use apps like Notes, Settings, Terminal, and Weather.

- **Extensibility:**
  - Easily add new libraries or modify existing components.
  - Pulse language interpreter included for running custom apps.

---

## Prerequisites

### Hardware Requirements:

- **Device:** M5Paper
- **Accessories:** Compatible microSD card (for flashing and storage).

### Software Requirements:

- **Python:** Version 3.7 or later
- **Rust:** Installed and configured
- **Drivers:** Necessary drivers for M5Lite development
- **Dependencies:** Additional libraries specified in the `lib/` directory

---

## Installation Instructions

### 1. Set Up the Pulse Environment
Run the following command to install the Pulse environment:

```
python3 flash/install_pulse.py
```

### 2. Flash the OS
Use the script to flash the OS onto the M5Lite device:

```
python3 flash/flash_os.py
```

### 3. Set Up the ESP-IDF Environment
Clone the ESP-IDF repository and install the required tools:

```
git clone --branch v5.3 --recursive https://github.com/espressif/esp-idf.git esp-idf
cd esp-idf
./install.sh
. ./export.sh
```

---

## Usage

### Running Pulse Applications

1. **Create a Pulse File:** Define your application using the Pulse syntax.
2. **Execute Using the Interpreter:**

```
pulse <path-to-pulse-file.pulse>
```

### Example Pulse Program (`helloworld.pulse`)

```
App "Hello World"
label greeting:
    text: "Welcome to Pulse"
    position: center, center
button okButton:
    text: "OK"
    position: center, 300
```

---

## Contributing

We welcome contributions to enhance the OS, libraries, or applications. To contribute:

1. Create an issue describing your idea or problem.
2. Submit a pull request with your changes.

---

## License

This project is licensed under the terms of the LICENSE file included in the repository.

