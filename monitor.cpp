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

// Pure functions for vital validation (Functional paradigm) - reduced complexity
VitalStatus checkTemperature(float temperature) {
    return checkVitalRange(temperature, 95.0f, 102.0f);
}

VitalStatus checkPulseRate(float pulseRate) {
    return checkVitalRange(pulseRate, 60.0f, 100.0f);
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

// Helper function for single animation step
void animateStep(const std::string& pattern) {
    cout << "\r" << pattern << flush;
    sleep_for(seconds(1));
}

// Separated I/O concern - visual alert animation - reduced complexity
void showVisualAlert() {
    for (int i = 0; i < 6; i++) {
        animateStep("* ");
        animateStep(" *");
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
    
private:
    // Helper function to get limits by type - reduced complexity
    const VitalLimits& getLimitsByType(VitalType type) {
        static const VitalLimits* limitsMap[] = {
            &temperatureLimits,  // TEMPERATURE
            &pulseRateLimits,    // PULSE_RATE
            &spo2Limits          // SPO2
        };
        return *limitsMap[static_cast<int>(type)];
    }

    // Helper function to check a single vital and handle critical state
    bool checkSingleVital(float value, const VitalLimits& limits) {
        if (checkVital(value, limits) == VitalStatus::CRITICAL) {
            handleCriticalVital(limits.name);
            return false;
        }
        return true;
    }

public:
    // Procedural approach for sequence of checks - reduced complexity
    bool checkAllVitals(float temperature, float pulseRate, float spo2) {
        return checkSingleVital(temperature, temperatureLimits) &&
               checkSingleVital(pulseRate, pulseRateLimits) &&
               checkSingleVital(spo2, spo2Limits);
    }
    
    // Future-proof: Easy to add new vitals
    void addVitalCheck(float value, const VitalLimits& limits) {
        if (checkVital(value, limits) == VitalStatus::CRITICAL) {
            handleCriticalVital(limits.name);
        }
    }
    
    // Age-based limits (future enhancement ready) - reduced complexity
    VitalLimits getAgeAdjustedLimits(VitalType type, int age) {
        // Placeholder for age-based adjustments
        return getLimitsByType(type);
    }
};

// Legacy function wrapper for backward compatibility
int vitalsOk(float temperature, float pulseRate, float spo2) {
    VitalMonitor monitor;
    return monitor.checkAllVitals(temperature, pulseRate, spo2) ? 1 : 0;
}
