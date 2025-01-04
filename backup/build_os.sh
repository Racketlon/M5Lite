#!/usr/bin/env bash

# Simple script to build the project using ESP-IDF

# (Optional) Source your ESP-IDF export script if not already in the environment
# source $HOME/esp/esp-idf/export.sh

clear
idf.py fullclean
idf.py build
