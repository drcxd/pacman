#pragma once

#include <string_view>

#include "base/sprite_animation.hh"
#include <base/types.hh>

class Object {
public:
  Object() = default;
  auto Init(std::string_view texture_path) -> bool;
  void Update(double delta);
  void Draw(struct SDL_Renderer* renderer);
  void SetPosition(Position pos) { _pos = pos; }
private:
  SpriteAnimation _animation;
  Position _pos;
  Direction _dir;
};
