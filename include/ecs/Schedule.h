#pragma once

class Schedule
{
public:
  virtual void Run() = 0;
};

class DynamicSchedule
{};

class FixedSchedule
{
private:
  float timestep;
};

class StartupSchedule
{};