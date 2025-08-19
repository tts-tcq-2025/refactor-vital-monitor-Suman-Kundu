#include "VitalMonitor.h"
#include "VitalAnalyzer.h"
#include "LanguageManager.h"
#include "Print_Console.h"

VitalMonitor::VitalMonitor() { initializeVitalLimits(); }

void VitalMonitor::initializeVitalLimits() {
    vitalLimits[0] = VitalLimits{95.0f, 102.0f, 1.53f, "Temperature", VitalType::TEMPERATURE};
    vitalLimits[1] = VitalLimits{60.0f, 100.0f, 1.5f, "Pulse Rate", VitalType::PULSE_RATE};
    vitalLimits[2] = VitalLimits{90.0f, 100.0f, 1.5f, "Oxygen Saturation", VitalType::SPO2};
}

bool VitalMonitor::checkAllVitals(float temperature, float pulseRate, float spo2) {
    float values[] = {temperature, pulseRate, spo2};
    bool allNormal = true;
    
    for (int i = 0; i < 3; i++) {
        VitalStatus status = VitalAnalyzer::checkVitalStatus(values[i], vitalLimits[i]);
        if (status == VitalStatus::CRITICAL) {
            processVital(values[i], vitalLimits[i]);
            allNormal = false;
        } else if (status == VitalStatus::WARNING) {
            processVital(values[i], vitalLimits[i]);
        }
    }
    return allNormal;
}

void VitalMonitor::processVital(float value, const VitalLimits& limits) {
    ConditionType condition = VitalAnalyzer::mapValueToCondition(value, limits);
    if (condition == ConditionType::NORMAL) return;
    
    std::string message = translator.getMessage(condition, LanguageManager::getCurrentLanguage());
    
    if (condition == ConditionType::NEAR_HYPO || condition == ConditionType::NEAR_HYPER || 
        condition == ConditionType::NEAR_BRADY || condition == ConditionType::NEAR_TACHY || 
        condition == ConditionType::NEAR_HYPOXEMIA) {
        displayAlert(message);
    } else {
        handleCriticalVital(message);
    }
}
