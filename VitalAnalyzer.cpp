#include "VitalAnalyzer.h"

ConditionType VitalAnalyzer::mapValueToCondition(float value, const VitalLimits& limits) {
    switch (limits.type) {
        case VitalType::TEMPERATURE: return analyzeTemperature(value, limits);
        case VitalType::PULSE_RATE: return analyzePulseRate(value, limits);
        case VitalType::SPO2: return analyzeSpO2(value, limits);
        default: return ConditionType::NORMAL;
    }
}

VitalStatus VitalAnalyzer::checkVitalStatus(float value, const VitalLimits& limits) {
    if (value < limits.min || value > limits.max) return VitalStatus::CRITICAL;
    if ((value >= limits.min && value <= limits.min + limits.warningTolerance) || 
        (value >= limits.max - limits.warningTolerance && value <= limits.max)) 
        return VitalStatus::WARNING;
    return VitalStatus::NORMAL;
}

ConditionType VitalAnalyzer::analyzeTemperature(float value, const VitalLimits& limits) {
    if (value < limits.min) return ConditionType::HYPO_THERMIA;
    if (value > limits.max) return ConditionType::HYPER_THERMIA;
    if (value <= limits.min + limits.warningTolerance) return ConditionType::NEAR_HYPO;
    if (value >= limits.max - limits.warningTolerance) return ConditionType::NEAR_HYPER;
    return ConditionType::NORMAL;
}

ConditionType VitalAnalyzer::analyzePulseRate(float value, const VitalLimits& limits) {
    if (value < limits.min) return ConditionType::BRADYCARDIA;
    if (value > limits.max) return ConditionType::TACHYCARDIA;
    if (value <= limits.min + limits.warningTolerance) return ConditionType::NEAR_BRADY;
    if (value >= limits.max - limits.warningTolerance) return ConditionType::NEAR_TACHY;
    return ConditionType::NORMAL;
}

ConditionType VitalAnalyzer::analyzeSpO2(float value, const VitalLimits& limits) {
    if (value < limits.min) return ConditionType::HYPOXEMIA;
    if (value > limits.max) return ConditionType::HYPEROXEMIA;
    if (value <= limits.min + limits.warningTolerance) return ConditionType::NEAR_HYPOXEMIA;
    return ConditionType::NORMAL;
}
