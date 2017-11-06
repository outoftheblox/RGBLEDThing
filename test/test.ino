#include <Arduino.h>
#include <unity.h>

#ifdef UNIT_TEST

using namespace g3rb3n;

#define PIN D1

void switchOn()
{
  bool value = true;
  TEST_ASSERT_EQUALS(true, value);
}

void switchOff()
{
  bool value = false;
  TEST_ASSERT_EQUALS(false, value);
}

void setup() 
{
  // NOTE!!! Wait for >2 secs
  // if board doesn't support software reset via Serial.DTR/RTS
  delay(2000);
  UNITY_BEGIN();
}

void loop() 
{
  uint8_t count = 100;
  while(--count)
  {
    RUN_TEST(switchOn);
    RUN_TEST(switchOff);
  }
  UNITY_END();
}

#endif
