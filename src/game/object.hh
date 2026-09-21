#pragma once

#include <string_view>

#include <base/texture.hh>

class Object {
public:
  Object() = default;
  auto Init(std::string_view texture_path) -> bool;
  void MoveX(double delta) { _x += delta; }
  void MoveY(double delta) { _y += delta; }
  auto GetPosX() const -> double { return _x; }
  auto GetPosY() const -> double { return _y; }
  void Update();
  void Draw(struct SDL_Renderer* renderer);
private:
  Texture _texture;
  // The location of the object on the window!
  // TODO: make it a location in the game world.
  double _x = 0;
  double _y = 0;
};
