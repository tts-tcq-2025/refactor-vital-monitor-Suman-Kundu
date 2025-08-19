#pragma once
#include "VitalTypes.h"

class VitalAnalyzer {
public:
    static ConditionType mapValueToCondition(float value, const VitalLimits& limits);
    static VitalStatus checkVitalStatus(float value, const VitalLimits& limits);

private:
    static ConditionType analyzeTemperature(float value, const VitalLimits& limits);
    static ConditionType analyzePulseRate(float value, const VitalLimits& limits);
    static ConditionType analyzeSpO2(float value, const VitalLimits& limits);
};
