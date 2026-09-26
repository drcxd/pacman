#pragma once

#include "base/texture.hh"
#include "base/types.hh"

class Maze {
public:
  auto Init() -> bool;
  void Draw(class SDL_Renderer* renderer);

  /**
   * Return if an object can move from `src` to `dst`. Also fix `dst` if
   * necessary.
   */
  [[nodiscard]] auto CanMove(Position const& src, Position& dst,
                             Direction const& dir) const -> bool;
  void SetToStart(class Object* obj);

private:
  Texture _sprite_sheet;
};
