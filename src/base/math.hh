#pragma once

#include <cmath>

/**
 * Return z = `x` % `y` so that z is non negative.
 */
template<typename T>
auto mod(T x, T y) -> T {
  if constexpr (std::is_integral_v<T>) {
    return ((x % y) + y) % y;
  }
  else {
    return fmod(fmod(x, y) + y, y);
  }
}
