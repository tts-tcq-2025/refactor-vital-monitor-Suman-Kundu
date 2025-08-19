#pragma once
#include <string>

enum class VitalStatus { NORMAL = 0, WARNING = 1, CRITICAL = 2 };
enum class VitalType { TEMPERATURE, PULSE_RATE, SPO2 };
enum class Language { ENGLISH, GERMAN };

enum class ConditionType {
    HYPO_THERMIA, NEAR_HYPO, NORMAL, NEAR_HYPER, HYPER_THERMIA,
    BRADYCARDIA, NEAR_BRADY, NEAR_TACHY, TACHYCARDIA,
    HYPOXEMIA, NEAR_HYPOXEMIA, HYPEROXEMIA
};

struct VitalLimits {
    float min, max, warningTolerance;
    std::string name;
    VitalType type;
};
