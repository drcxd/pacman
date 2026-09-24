#pragma once

#include "base/texture.hh"
#include "base/types.hh"

class Maze {
public:
  auto Init() -> bool;
  void Draw(class SDL_Renderer* renderer);
  [[nodiscard]] auto CanMove(Position const& src, Direction const& dir) const
      -> bool;

private:
  Texture _sprite_sheet;
};
