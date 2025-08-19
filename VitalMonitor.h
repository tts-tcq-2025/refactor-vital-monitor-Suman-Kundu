#pragma once
#include "VitalTypes.h"
#include "MessageTranslator.h"
#include <array>

class VitalMonitor {
private:
    std::array<VitalLimits, 3> vitalLimits;
    MessageTranslator translator;
    void initializeVitalLimits();
    
public:
    VitalMonitor();
    bool checkAllVitals(float temperature, float pulseRate, float spo2);
    void processVital(float value, const VitalLimits& limits);
};
