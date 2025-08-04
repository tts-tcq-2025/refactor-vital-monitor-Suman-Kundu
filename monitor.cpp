#include <assert.h>
#include <thread>
#include <chrono>
#include <iostream>
#include <string>
#include <functional>
using std::cout, std::flush, std::this_thread::sleep_for, std::chrono::seconds;

// Enums for better type safety and readability
enum class VitalStatus {
    NORMAL = 0,
    CRITICAL = 1
};

enum class VitalType {
    TEMPERATURE,
    PULSE_RATE,
    SPO2
};

// Struct to encapsulate vital limits (OOP principle)
struct VitalLimits {
    float min;
    float max;
    std::string name;
    std::string unit;
};

// Pure functions for vital validation (Functional paradigm)
VitalStatus checkTemperature(float temperature) {
    return (temperature > 102 || temperature < 95) ? VitalStatus::CRITICAL : VitalStatus::NORMAL;
}

VitalStatus checkPulseRate(float pulseRate) {
    return (pulseRate < 60 || pulseRate > 100) ? VitalStatus::CRITICAL : VitalStatus::NORMAL;
}

VitalStatus checkSpo2(float spo2) {
    return (spo2 < 90) ? VitalStatus::CRITICAL : VitalStatus::NORMAL;
}

// Generic vital checker using functional approach
VitalStatus checkVitalRange(float value, float min, float max) {
    return (value < min || value > max) ? VitalStatus::CRITICAL : VitalStatus::NORMAL;
}

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

// Class-based approach for encapsulating vital monitoring (OOP)
class VitalMonitor {
private:
    VitalLimits temperatureLimits = {95.0f, 102.0f, "Temperature", "°F"};
    VitalLimits pulseRateLimits = {60.0f, 100.0f, "Pulse Rate", "BPM"};
    VitalLimits spo2Limits = {90.0f, 100.0f, "Oxygen Saturation", "%"};

public:
    // Pure function for checking individual vitals
    VitalStatus checkVital(float value, const VitalLimits& limits) {
        return checkVitalRange(value, limits.min, limits.max);
    }
    
    // Procedural approach for sequence of checks
    bool checkAllVitals(float temperature, float pulseRate, float spo2) {
        // Check temperature
        if (checkVital(temperature, temperatureLimits) == VitalStatus::CRITICAL) {
            handleCriticalVital(temperatureLimits.name);
            return false;
        }
        
        // Check pulse rate
        if (checkVital(pulseRate, pulseRateLimits) == VitalStatus::CRITICAL) {
            handleCriticalVital(pulseRateLimits.name);
            return false;
        }
        
        // Check SpO2
        if (checkVital(spo2, spo2Limits) == VitalStatus::CRITICAL) {
            handleCriticalVital(spo2Limits.name);
            return false;
        }
        
        return true;
    }
    
    // Future-proof: Easy to add new vitals
    void addVitalCheck(float value, const VitalLimits& limits) {
        if (checkVital(value, limits) == VitalStatus::CRITICAL) {
            handleCriticalVital(limits.name);
        }
    }
    
    // Age-based limits (future enhancement ready)
    VitalLimits getAgeAdjustedLimits(VitalType type, int age) {
        // Placeholder for age-based adjustments
        switch(type) {
            case VitalType::TEMPERATURE: return temperatureLimits;
            case VitalType::PULSE_RATE: return pulseRateLimits;
            case VitalType::SPO2: return spo2Limits;
        }
        return temperatureLimits;
    }
};

// Legacy function wrapper for backward compatibility
int vitalsOk(float temperature, float pulseRate, float spo2) {
    VitalMonitor monitor;
    return monitor.checkAllVitals(temperature, pulseRate, spo2) ? 1 : 0;
}
