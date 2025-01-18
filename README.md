# Custom OS for M5Lite

This repository is dedicated to developing and deploying a custom operating system for the M5Lite device. It includes all necessary tools, libraries, and scripts for creating and managing applications using the Pulse programming language, as well as flashing the OS onto the M5Lite hardware.

## Folder Structure

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
│   ├── kernel.h               # Kernel-related headers
│   └── main.ino               # Main OS entry point
├── docs/                      # Documentation
│   ├── LICENSE
│   └── README.md
├── flash/                     # Scripts for flashing the OS
│   ├── flash_os.py
│   └── install_pulse.py
├── lib/                       # Libraries used in the OS
│   ├── Bluetooth/
│   │   └── bluetooth.h
│   ├── Network/
│   │   └── Network.h
│   └── System/
│       ├── file_management.h
│       └── System.h
├── pulse/                     # Pulse programming language and interpreter
│   ├── compiler/
│   │   ├── Compiler.h
│   │   └── examples/
│   │       ├── counter.pls
│   │       └── helloworld.pls
│   ├── interpreter/
│   │   ├── Interpreter.py
│   │   └── vm.py
│   ├── main.py                # Entry point for Pulse interpreter
│   └── tests/                 # Test cases for the Pulse interpreter
├── screen/                    # UI and screen-related components
│   ├── layout/
│   │   ├── app_layout.h
│   │   ├── app_manager.h
│   │   ├── app_viewer.h
│   │   └── gesture.h
│   ├── screen_manager.h
│   ├── task_manager.h
│   └── ui/
│       ├── keyboard.h
│       ├── notification_manager.h
│       └── status_bar.h
└── tests/                     # General tests for the OS

## Features

- Pulse Language Support: Develop GUI-based applications using the Pulse programming language.
- Modular Design: Organized folder structure for clear separation of responsibilities.
- Custom OS Core: Based on the M5Lite hardware with additional extensibility via libraries.
- Prebuilt Apps: Comes with ready-to-use apps like Notes, Settings, Terminal, and Weather.

## Prerequisites

- Hardware: M5Lite device, compatible microSD card (if required for flashing).
- Software:
    - Python 3.7 or later
    - Arduino IDE or PlatformIO
    - Necessary drivers for M5Lite
    - Any additional libraries specified in `lib/`

## Installation Instructions

1. Set Up the Pulse Environment: Run the `install_pulse.py` script to configure the Pulse environment:

bash´´´
python3 flash/install_pulse.py
´´´

2. Flash the OS: Use the `flash_os.py` script to flash the OS onto the M5Lite:

bash´´´
python3 flash/flash_os.py
´´´

3. Deploy Applications: Use the Pulse interpreter to execute your `.pls` files, or customize and upload the `main.ino` file in Arduino IDE/PlatformIO.

## Usage

### Running Pulse Applications

1. Create a `.pls` file describing your application.
2. Use the Pulse interpreter to parse and execute the application:

bash´´´
pulse <path-to-pulse-file.pulse>
´´´

### Example Pulse Program (`helloworld.pls`)

App “Hello World”
label greeting:
text: “Welcome to Pulse”
position: center, center
button okButton:
text: “OK”
position: center, 300

## Contributing

Contributions to improve the OS, libraries, or example applications are welcome! Please create an issue or submit a pull request.

## License

This project is licensed under the terms of the LICENSE file.