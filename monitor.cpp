#include "monitor.h"
#include "VitalMonitor.h"
#include "LanguageManager.h"
#include <iostream>

int vitalsOk(float temperature, float pulseRate, float spo2) {
    VitalMonitor monitor;
    return monitor.checkAllVitals(temperature, pulseRate, spo2) ? 1 : 0;
}

void setLanguage(Language lang) {
    LanguageManager::setLanguage(lang);
}

int main() {
    std::cout << "=== Modular Vital Monitoring System Test ===" << std::endl;
    
    std::cout << "\nTest 1: Normal vitals" << std::endl;
    std::cout << "Temperature: 98.6°F, Pulse: 75 bpm, SPO2: 95%" << std::endl;
    std::cout << "Result: " << (vitalsOk(98.6f, 75.0f, 95.0f) ? "OK" : "NOT OK") << std::endl;
    
    std::cout << "\nTest 2: Warning conditions (English)" << std::endl;
    std::cout << "Temperature: 96.0°F (near hypothermia), Pulse: 75 bpm, SPO2: 95%" << std::endl;
    std::cout << "Result: " << (vitalsOk(96.0f, 75.0f, 95.0f) ? "OK" : "NOT OK") << std::endl;
    
    std::cout << "\nTest 3: Critical condition (English)" << std::endl;
    std::cout << "Temperature: 103°F (critical), Pulse: 75 bpm, SPO2: 95%" << std::endl;
    std::cout << "Result: " << (vitalsOk(103.0f, 75.0f, 95.0f) ? "OK" : "NOT OK") << std::endl;
    
    std::cout << "\n=== Testing German Language Support ===" << std::endl;
    setLanguage(Language::GERMAN);
    
    std::cout << "\nTest 4: Warning condition (German)" << std::endl;
    std::cout << "Temperature: 96.0°F (near hypothermia), Pulse: 75 bpm, SPO2: 95%" << std::endl;
    std::cout << "Result: " << (vitalsOk(96.0f, 75.0f, 95.0f) ? "OK" : "NOT OK") << std::endl;
    
    std::cout << "\nTest 5: Critical condition (German)" << std::endl;
    std::cout << "Temperature: 103°F (critical), Pulse: 75 bpm, SPO2: 95%" << std::endl;
    std::cout << "Result: " << (vitalsOk(103.0f, 75.0f, 95.0f) ? "OK" : "NOT OK") << std::endl;
    
    std::cout << "\nTest 6: Pulse warning (German)" << std::endl;
    std::cout << "Temperature: 98.6°F, Pulse: 61 bpm (near bradycardia), SPO2: 95%" << std::endl;
    std::cout << "Result: " << (vitalsOk(98.6f, 61.0f, 95.0f) ? "OK" : "NOT OK") << std::endl;
    
    return 0;
}