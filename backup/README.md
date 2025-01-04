# M5Paper Custom OS

This repository contains a custom OS for the M5Paper. It is built using ESP-IDF and includes various drivers and apps.

## Project Structure

- **main.cpp**: Entry point of the main application.
- **Apps/**: Contains sub-applications or modules like Notes, Settings, Weather, etc.
- **Drivers/**: Contains drivers for Network, Screen, Storage, etc.
- **build.sh**: Script for building the project.
- **menuconfig.sh**: Script for launching `idf.py menuconfig`.
- **sdkconfig**: ESP-IDF configuration file.

## Getting Started

1. Install ESP-IDF v5.x or later.
2. Clone this repository.
3. Run `./build.sh` to build the firmware.
4. Upload to M5Paper using `idf.py flash`.
