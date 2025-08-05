#include "./monitor.h"
#include <assert.h>
#include <algorithm>
#include <array>
#include <chrono>
#include <functional>
#include <iostream>
#include <string>
#include <thread>
#include "./Print_console.h"

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
};

// Generic vital checker using functional approach
VitalStatus checkVitalRange(float value, float min, float max) {
    return (value < min || value > max) ? 
           VitalStatus::CRITICAL : VitalStatus::NORMAL;
}

// Class-based approach for encapsulating vital monitoring (OOP)
class VitalMonitor {
 private:
    VitalLimits temperatureLimits = {95.0f, 102.0f, "Temperature"};
    VitalLimits pulseRateLimits = {60.0f, 100.0f, "Pulse Rate"};
    VitalLimits spo2Limits = {90.0f, 100.0f, "Oxygen Saturation"};

 public:
    // Pure function for checking individual vitals
    VitalStatus checkVital(float value, const VitalLimits& limits) {
        return checkVitalRange(value, limits.min, limits.max);
    }

    // Procedural approach for sequence of checks
    bool checkAllVitals(float temperature, float pulseRate, float spo2) {
        // Array of vital values and their corresponding limits 
        // for loop-based processing
        struct VitalCheck {
            float value;
            const VitalLimits* limits;
        };

        std::array<VitalCheck, 3> vitalsToCheck = {{
            {temperature, &temperatureLimits},
            {pulseRate, &pulseRateLimits},
            {spo2, &spo2Limits}
        }};

        // Use std::all_of algorithm for better style
        return std::all_of(vitalsToCheck.begin(), vitalsToCheck.end(),
                          [this](const VitalCheck& vital) {
                              if (checkVital(vital.value, *vital.limits) == 
                                  VitalStatus::CRITICAL) {
                                  handleCriticalVital(vital.limits->name);
                                  return false;
                              }
                              return true;
                          });
    }
};

// Legacy function wrapper for backward compatibility
int vitalsOk(float temperature, float pulseRate, float spo2) {
    VitalMonitor monitor;
    return monitor.checkAllVitals(temperature, pulseRate, spo2) ? 1 : 0;
}
