#include "./monitor.h"
#include <assert.h>
#include <thread>
#include <chrono>
#include <iostream>
#include <algorithm>
using std::cout, std::flush, std::this_thread::sleep_for, std::chrono::seconds;

static const PulseRateRange pulseRateRanges[] = {
    {0, 0, 100, 160},    // newborn
    {1, 5, 80, 140},     // infant/toddler
    {6, 10, 70, 110},    // child
    {11, 14, 60, 105},   // adolescent
    {15, 200, 60, 100}   // adult (assuming max age 200)
};

bool isTemperatureOk(float temperature) {
    return temperature >= 95 && temperature <= 102;
}

bool ageInRange(int age, const PulseRateRange& range) {
    return age >= range.minAge && age <= range.maxAge;
}

const PulseRateRange* findPulseRangeForAge(int age) {
    const auto* end = pulseRateRanges +
                      sizeof(pulseRateRanges) / sizeof(pulseRateRanges[0]);
    const auto* result = std::find_if(pulseRateRanges, end,
                                      [age](const PulseRateRange& range) {
                                          return ageInRange(age, range);
                                      });
    return result != end ? result : nullptr;
}

bool isPulseRateOk(float pulseRate, int age) {
    const PulseRateRange* range = findPulseRangeForAge(age);
    return range && pulseRate >= range->minPulse &&
           pulseRate <= range->maxPulse;
}

bool isSpO2Ok(float spo2) {
    return spo2 >= 90;
}

void printAlert(const char* message) {
    cout << message << "\n";
    for (int i = 0; i < 6; i++) {
        cout << "\r* " << flush;
        sleep_for(seconds(1));
        cout << "\r *" << flush;
        sleep_for(seconds(1));
    }
}

VitalChecks checkAllVitals(float temperature, float pulseRate, float spo2,
                           int age) {
    VitalChecks checks;
    checks.temperature = isTemperatureOk(temperature);
    checks.pulseRate = isPulseRateOk(pulseRate, age);
    checks.spo2 = isSpO2Ok(spo2);
    return checks;
}

int handleVitalAlert(bool isOk, const char* message) {
    if (!isOk) {
        printAlert(message);
        return 0;
    }
    return 1;
}

int vitalsOk(float temperature, float pulseRate, float spo2, int age) {
    VitalChecks checks = checkAllVitals(temperature, pulseRate, spo2, age);

    int result = handleVitalAlert(checks.temperature,
                                  "Temperature is critical!");
    if (result == 0) return 0;

    result = handleVitalAlert(checks.pulseRate, "Pulse Rate is out of range!");
    if (result == 0) return 0;

    return handleVitalAlert(checks.spo2, "Oxygen Saturation out of range!");
}
