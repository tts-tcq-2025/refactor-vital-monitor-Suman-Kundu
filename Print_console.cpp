#include "./Print_console.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <string>
using std::cout, std::flush, std::this_thread::sleep_for, std::chrono::seconds;

// Separated I/O concern - pure alert function
void displayAlert(const std::string& message) {
    cout << message << "\n";
}

// Separated I/O concern - visual alert animation
void showVisualAlert() {
    for (int i = 0; i < 6; i++) {
        cout << "\r* " << flush;
        sleep_for(seconds(1));
        cout << "\r *" << flush;
        sleep_for(seconds(1));
    }
}

// Aspect-oriented approach: Alert handler that can be reused
void handleCriticalVital(const std::string& vitalName) {
    displayAlert(vitalName + " is critical!");
    showVisualAlert();
}