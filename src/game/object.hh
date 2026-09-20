#pragma once

#include <string_view>

#include <base/texture.hh>

class Object
{
public:
  Object() = default;
  auto Init(std::string_view texture_path) -> bool;
  void MoveX(int delta) { _x += delta; }
  void MoveY(int delta) { _y += delta; }
  auto GetPosX() const -> int { return _x; }
  auto GetPosY() const -> int { return _y; }
  void Draw(struct SDL_Renderer* renderer);
private:
  Texture _texture;
  // The location of the object on the window! TODO: make it a location in the
  // game world.
  int _x = 0;
  int _y = 0;
};
