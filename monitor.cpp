#include "./monitor.h"
#include "./Print_console.h"
#include <assert.h>
#include <thread>
#include <chrono>
#include <iostream>
#include <string>
#include <functional>
#include <array>
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
    
    // Procedural approach for sequence of checks - REDUCED COMPLEXITY (was 4, now 2)
    bool checkAllVitals(float temperature, float pulseRate, float spo2) {
        // Array of vital values and their corresponding limits for loop-based processing
        struct VitalCheck {
            float value;
            const VitalLimits* limits;
        };
        
        std::array<VitalCheck, 3> vitalsToCheck = {{
            {temperature, &temperatureLimits},
            {pulseRate, &pulseRateLimits},
            {spo2, &spo2Limits}
        }};
        
        // Single loop reduces complexity from 4 to 2
        for (const auto& vital : vitalsToCheck) {
            if (checkVital(vital.value, *vital.limits) == VitalStatus::CRITICAL) {
                handleCriticalVital(vital.limits->name);
                return false;
            }
        }
        
        return true;
    }
   
    // Future-proof: Easy to add new vitals
    void addVitalCheck(float value, const VitalLimits& limits) {
        if (checkVital(value, limits) == VitalStatus::CRITICAL) {
            handleCriticalVital(limits.name);
        }
    }
};
// Legacy function wrapper for backward compatibility
int vitalsOk(float temperature, float pulseRate, float spo2) {
    VitalMonitor monitor;
    return monitor.checkAllVitals(temperature, pulseRate, spo2) ? 1 : 0;
}
