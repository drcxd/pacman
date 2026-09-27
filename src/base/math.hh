#pragma once

#include <cmath>

/**
 * Return z = `x` % `y` so that z is non negative.
 */
auto mod(int x, int y) -> int {
  return ((x % y) + y) % y;
}

auto modf(float x, float y) -> float {
  return fmod(fmod(x, y) + y, y);
}
