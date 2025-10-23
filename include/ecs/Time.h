#pragma once

#include "Resource.h"
#include <chrono>

class Time : public Resource
{
public:
  Time(float fixedTimeStep);
  float DeltaTime();
  void SwitchToFixed();
  void SwitchToDynamic();
  void Tick();

private:
  float dynamicDeltaTime;
  float fixedDeltaTime;
  float currentDelta;
  std::chrono::steady_clock::time_point lastCheckpoint;
};