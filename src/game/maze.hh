#pragma once

#include "base/texture.hh"

class Maze {
public:
  auto Init() -> bool;
  void Draw(class SDL_Renderer* renderer);
private:
  Texture _sprite_sheet;
};
