#include "Print_Console.h"
#include <chrono>
#include <iostream>
#include <string>
#include <thread>
using std::cout, std::flush, std::this_thread::sleep_for, std::chrono::seconds;

void displayAlert(const std::string& message) {
    cout << message << "\n";
}

void showVisualAlert() {
    for (int i = 0; i < 6; i++) {
        cout << "\r* " << flush;
        sleep_for(seconds(1));
        cout << "\r *" << flush;
        sleep_for(seconds(1));
    }
}

void handleCriticalVital(const std::string& message) {
    displayAlert(message);
    showVisualAlert();
}