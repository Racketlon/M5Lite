#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <vector>
#include <string>

using namespace std;

class Bluetooth{
private:
    vector<string> knownDevices;
    vector<string> foundDevices;

public:
    void add_known_device(string device) { knownDevices.push_back(device); }

    void add_found_device(string device) { foundDevices.push_back(device); }

    void show_known_list() {

    }

    void show_found_list() {
        
    }
};


#endif