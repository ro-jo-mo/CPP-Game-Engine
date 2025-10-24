#pragma once

enum Schedule : std::size_t {
  PreStartup,
  Startup,
  PostStartup,
  PreUpdate,
  Update,
  PostUpdate,
  PreFixedUpdate,
  FixedUpdate,
  PostFixedUpdate,
  ScheduleSize
};
