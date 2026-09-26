#pragma once

#include <cmath>

struct Direction {
  char X = -1;
  char Y = 0;

  auto operator==(Direction const& that) -> bool {
    return this->X == that.X && this->Y == that.Y;
  }

  auto operator!=(Direction const& that) -> bool {
    return !(*this == that);
  }
};

struct Position {
  float X = 0;
  float Y = 0;

  void MoveAlongDirection(Direction const& dir, float dist) {
    X += dir.X * dist;
    Y += dir.Y * dist;
  }

  auto Distance(Position const& other) {
    return std::sqrt((other.X - X) * (other.X - X) +
                     (other.Y - Y) * (other.Y - Y));
  }
};
