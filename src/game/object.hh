#pragma once

#include <string_view>
#include <vector>

#include "base/sprite_animation.hh"
#include <base/types.hh>

class Object {
public:
  Object() = default;
  auto Init(std::string_view name) -> bool;
  void Update(double delta);
  void Draw(struct SDL_Renderer* renderer);
  void SetPosition(Position pos) { _pos = pos; }
private:
  std::vector<SpriteAnimation> _animations;
  Position _pos;
  Direction _dir;
  float _speed = 0;
  std::pair<int, int> _size;
  auto GetCurrentSpriteAnimation() -> SpriteAnimation&;

  static constexpr Direction LEFT = {.X = -1, .Y = 0};
  static constexpr Direction RIGHT = {.X = 1, .Y = 0};
  static constexpr Direction UP = {.X = 0, .Y = -1};
  static constexpr Direction DOWN = {.X = 0, .Y = 1};
};
