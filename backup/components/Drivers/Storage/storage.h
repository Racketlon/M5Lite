#pragma once

bool storage_init();
bool storage_save_file(const char* filename, const char* data);
bool storage_load_file(const char* filename, char* outData, int maxLen);
