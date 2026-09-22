#include "timer.hh"

#include "SDL3/SDL_timer.h"

Timer::Timer() {
  _base_tick = SDL_GetTicks();
}

auto Timer::GetTime() const -> Uint64 {
  return SDL_GetTicks() - _base_tick;
}

auto Timer::GetTimeS() const -> double {
  return GetTime() / 1000.0;
}

auto Timer::GetDelta() -> Uint64 {
  Uint64 now = SDL_GetTicks();
  Uint64 diff = now - _last_tick;
  _last_tick = now;
  return diff;
}

auto Timer::Set() -> Uint64 {
  _last_tick = SDL_GetTicks();
  return _last_tick;
}
