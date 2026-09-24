#pragma once

#include <string_view>

#include <base/texture.hh>
#include <base/types.hh>

class Object {
public:
  Object() = default;
  auto Init(std::string_view texture_path) -> bool;
  void Update(double delta);
  void Draw(struct SDL_Renderer* renderer);
private:
  Texture _texture;
  Position _pos;
  Direction _dir;
};
