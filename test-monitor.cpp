#include <gtest/gtest.h>
#include "./monitor.h"

// Test pure logic functions without I/O
TEST(Monitor, TemperatureChecks) {
  ASSERT_TRUE(isTemperatureOk(98.6f));
  ASSERT_TRUE(isTemperatureOk(95.0f));  // lower bound
  ASSERT_TRUE(isTemperatureOk(102.0f));  // upper bound
  ASSERT_FALSE(isTemperatureOk(94.9f));  // below lower
  ASSERT_FALSE(isTemperatureOk(102.1f));  // above upper
}

TEST(Monitor, SpO2Checks) {
  ASSERT_TRUE(isSpO2Ok(95.0f));
  ASSERT_TRUE(isSpO2Ok(90.0f));  // lower bound
  ASSERT_TRUE(isSpO2Ok(100.0f));  // upper bound
  ASSERT_FALSE(isSpO2Ok(89.9f));  // below lower
}

TEST(Monitor, PulseRateChecks) {
  // Newborn (age 0)
  ASSERT_TRUE(isPulseRateOk(130.0f, 0));
  ASSERT_TRUE(isPulseRateOk(100.0f, 0));  // lower bound
  ASSERT_TRUE(isPulseRateOk(160.0f, 0));  // upper bound
  ASSERT_FALSE(isPulseRateOk(99.0f, 0));  // below
  ASSERT_FALSE(isPulseRateOk(161.0f, 0));  // above
  // Adult (age 30)
  ASSERT_TRUE(isPulseRateOk(75.0f, 30));
  ASSERT_TRUE(isPulseRateOk(60.0f, 30));  // lower bound
  ASSERT_TRUE(isPulseRateOk(100.0f, 30));  // upper bound
  ASSERT_FALSE(isPulseRateOk(59.0f, 30));  // below
  ASSERT_FALSE(isPulseRateOk(101.0f, 30));  // above
}

TEST(Monitor, VitalChecksStruct) {
  VitalChecks checks = checkAllVitals(98.6f, 75.0f, 95.0f, 30);
  ASSERT_TRUE(checks.temperature);
  ASSERT_TRUE(checks.pulseRate);
  ASSERT_TRUE(checks.spo2);
  checks = checkAllVitals(105.0f, 45.0f, 85.0f, 30);  // all out of range
  ASSERT_FALSE(checks.temperature);
  ASSERT_FALSE(checks.pulseRate);
  ASSERT_FALSE(checks.spo2);
}

// Test the main function but only for logic, avoiding I/O delay
TEST(Monitor, VitalsOkLogic) {
  // Test cases that should return 1 (OK) - these won't print alerts
  ASSERT_EQ(1, vitalsOk(98.6f, 75.0f, 95.0f, 30));  // all normal adult
  ASSERT_EQ(1, vitalsOk(98.1f, 130.0f, 98.0f, 0));  // normal newborn
  // Test cases that should return 0 (NOT OK) - these will print alerts
  // but we minimize them
  ASSERT_EQ(0, vitalsOk(105.0f, 75.0f, 95.0f, 30));  // temperature critical
  ASSERT_EQ(0, vitalsOk(98.6f, 45.0f, 95.0f, 30));  // only pulse critical
  ASSERT_EQ(0, vitalsOk(98.6f, 75.0f, 85.0f, 30));  // only SpO2 critical
}
