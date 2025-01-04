// main/main.cpp
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "Notes/notes.h"
#include "Network/network.h"
// Include other necessary headers

extern "C" void app_main(void) {
    // Instantiate components
    Notes notes;
    Network network;
    
    // Initialize components
    notes.init();
    network.init();
    
    // Your application logic here
    
    // Example: Start a FreeRTOS task
    xTaskCreate([](void*){
        // Task code here
        vTaskDelete(NULL);
    }, "example_task", 2048, NULL, 5, NULL);
}
