# Pulse

Pulse is a custom programming language designed for GUI programming. It translates custom syntax into C++, enabling seamless GUI development. The goal is to create a flexible, powerful, and efficient programming language for developers who want a custom solution for GUI programming.

## Features
- Custom syntax designed for GUI programming.
- Modular architecture with clear separation of components.
- Automatic translation into C++ for high performance.

## Folder Structure
```
examples/       # Example Pulse (.pls) files
    helloworld.pls  # Sample Hello World program in Pulse
Interpreter.h    # Header file for the interpreter
Interpreter.py   # Python-based interpreter implementation
main.py          # Main Python script for running the interpreter
modules/         # Additional modules like Bluetooth, Network, and System
    Bluetooth.h      # Header for Bluetooth module
    Network.h        # Header for Network module
    System.h         # Header for System module
__pycache__/     # Cached Python files
    Interpreter.cpython-313.pyc  # Cached Python bytecode
README.md        # Project documentation
```

## Prerequisites
- **Python**: Make sure Python 3.10 or higher is installed on your system.

## Installation
To run the interpreter, simply use the following command:

```bash
python3 main.py
```

## Usage
To execute a Pulse program, run the following command:

```bash
python3 main.py examples/helloworld.pls
```

## Clean Build
To clean up cached Python files, you can manually remove the `__pycache__` directory or its contents.

## License
This project is licensed under the terms specified in the LICENSE file.
