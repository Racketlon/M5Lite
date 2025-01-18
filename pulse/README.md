# Pulse

Pulse is a custom programming language designed for GUI programming. It translates custom syntax into C++, enabling seamless GUI development. The goal is to create a flexible, powerful, and efficient programming language for developers who want a custom solution for GUI programming.

## Features
- Custom syntax designed for GUI programming.
- Modular architecture with clear separation of components.
- Automatic translation into C++ for high performance.

## Folder Structure
```
compiler/                 # Compiler folder
    examples/             # Example folder
        counter.pulse     # Example file of a counter app
        helloworld.pulse  # Example file of hello world
    Compiler.h            # Compiler header file
Interpreter/              # Interpreter folder
    Interpreter.py        # Interpreter file for debug
    vm.py                 # VM file for creating a preview
tests/                    # Test folder
main.py                   # Main file
README.md                 # Project documentation
```

## Prerequisites
- **Python**: Make sure Python 3.10 or higher is installed on your system.

## Usage
To execute a Pulse program, run the following command:

```bash
pulse examples/helloworld.pulse
```

## Clean Build
To clean up cached Python files, you can manually remove the `__pycache__` directory or its contents.

## License
This project is licensed under the terms specified in the LICENSE file.
