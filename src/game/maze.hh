#pragma once

#include "base/texture.hh"
#include "base/types.hh"

class Maze {
public:
  auto Init() -> bool;
  void Draw(class SDL_Renderer* renderer);
  [[nodiscard]] auto CanMove(Position const& src, Position const& dst) const
      -> bool;
  void SetToStart(class Object* obj);

private:
  Texture _sprite_sheet;
};
