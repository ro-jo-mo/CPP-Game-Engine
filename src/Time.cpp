#include <chrono>
#include <ecs/Time.h>

Time::Time(float fixedTimeStep)
  : fixedDeltaTime(fixedTimeStep)
  , currentDelta(0.01)
  , dynamicDeltaTime(0.01)
  , lastCheckpoint(std::chrono::steady_clock::now()) {};

float
Time::DeltaTime()
{
  return currentDelta;
}

void
Time::SwitchToFixed()
{
  currentDelta = fixedDeltaTime;
}

void
Time::SwitchToDynamic()
{
  currentDelta = dynamicDeltaTime;
}

void
Time::Tick()
{
  auto currentTime = std::chrono::steady_clock::now();
  std::chrono::duration<float> delta = (currentTime - lastCheckpoint);
  dynamicDeltaTime = delta.count();
  lastCheckpoint = currentTime;
}
