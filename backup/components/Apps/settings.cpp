#include <iostream>
#include <string>
#include <vector>

// We'll keep a small struct to hold info about each app.
struct AppInfo {
    std::string name;
    // You can add more fields if needed (icon, callback function, etc.)
};

// Number of pages can change but the number of apps per page is const (4 apps per row, 5 apps per column)
static int NUM_PAGES = 1;
static const int APPS_PER_PAGE = 4*5;

// We define a 2D array (or vector of vectors) to store which apps live on which page.
// Here, each "row" is a page, and each "column" is a slot on that page.
static AppInfo g_appsLayout[NUM_PAGES][APPS_PER_PAGE] = {
    for (int page : NUM_PAGES) {
        
    }
};

// Helper function to safely get an app by page and position.
//
// page and slot are 1-based from the user's perspective, but
// we convert them to 0-based for C++ array indexing internally.
//
// Returns a pointer to the app's info if valid; otherwise nullptr.
const AppInfo* getAppInfo(int page, int slot)
{
    // Convert 1-based (user) to 0-based (C++ array).
    int pageIndex = page - 1;
    int slotIndex = slot - 1;

    // Validate indices to avoid out-of-bounds errors.
    if (pageIndex < 0 || pageIndex >= NUM_PAGES) {
        std::cerr << "[ERROR] Page " << page << " is out of range.\n";
        return nullptr;
    }
    if (slotIndex < 0 || slotIndex >= APPS_PER_PAGE) {
        std::cerr << "[ERROR] Slot " << slot << " on page " << page << " is out of range.\n";
        return nullptr;
    }

    // Return pointer to the app info in the layout.
    return &g_appsLayout[pageIndex][slotIndex];
}

// Example function showing usage
void printAppName(int page, int slot)
{
    const AppInfo* app = getAppInfo(page, slot);
    if (app != nullptr) {
        std::cout << "Page " << page
                  << ", Slot " << slot
                  << " -> App: " << app->name << "\n";
    } else {
        std::cout << "Page " << page << ", Slot " << slot << " -> Invalid.\n";
    }
}

// This could be called from somewhere else in your code:
void settings_showAppLayoutExample()
{
    std::cout << "=== App Layout Example ===\n";
    // Iterate over pages (1-based) and slots (1-based)
    for (int page = 1; page <= NUM_PAGES; ++page) {
        for (int slot = 1; slot <= APPS_PER_PAGE; ++slot) {
            printAppName(page, slot);
        }
    }
    std::cout << "==========================\n";
}
