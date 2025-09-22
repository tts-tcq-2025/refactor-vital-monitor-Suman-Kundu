#include <gtest/gtest.h>
#include "./monitor.h"

// Test the main function but only for logic, avoiding I/O delay
TEST(Monitor, VitalsOkLogic) {
  // Test cases that should return 1 (OK) - these won't print alerts
  ASSERT_EQ(1, vitalsOk(98.6f, 75.0f, 95.0f));  // all normal adult
  // Test cases that should return 0 (NOT OK) - these will print alerts
  // but we minimize them
  ASSERT_EQ(0, vitalsOk(105.0f, 75.0f, 95.0f));  // temperature critical
  ASSERT_EQ(0, vitalsOk(98.6f, 45.0f, 95.0f));  // only pulse critical
  ASSERT_EQ(0, vitalsOk(98.6f, 75.0f, 85.0f));  // only SpO2 critical
}

