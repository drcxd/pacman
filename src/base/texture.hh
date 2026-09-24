#pragma once

#include <string_view>

struct SDL_Texture;

class Texture {
public:
  Texture() = default;
  auto Init(std::string_view path) -> bool;
  ~Texture();
  auto GetWidth() const -> int { return _width; }
  auto GetHeight() const -> int { return _height; }
  auto GetTexture() -> SDL_Texture* { return _texture; }
  auto IsReady() const -> bool { return _texture != nullptr; }

private:
  SDL_Texture* _texture = nullptr;
  int _width = 0;
  int _height = 0;
};
