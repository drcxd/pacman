#pragma once

#include "SDL3/SDL_stdinc.h"

class Timer {
public:
  Timer();
  /**
   * Return the time passed since the timer constructed in milliseconds.
   */
  auto GetTime() const -> Uint64;
  /**
   * Return the time passed since the timer constructed in seconds.
   */
  auto GetTimeS() const -> double;
  /**
   * Return the time elapsed since last set. This also sets the timer once
   * again.
   */
  auto GetDelta() -> Uint64;
  /**
   * Remember and return the current time.
   */
  auto Set() -> Uint64;
private:
  /**
   * The tick the timer gets created.
   */
  Uint64 _base_tick = 0;
  /**
   * The tick the timer is set last time.
   */
  Uint64 _last_tick = 0;
};
