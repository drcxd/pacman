#pragma once

#include "SDL3/SDL_render.h"
#include <memory>
#include <string_view>

struct TextureDeletor {
  void operator()(SDL_Texture* t) const noexcept {
    if (t != nullptr) {
      SDL_DestroyTexture(t);
    }
  }
};

class Texture {
public:
  Texture() = default;
  ~Texture() = default;
  Texture(Texture const&) = delete;
  Texture(Texture&&) = default;
  auto operator=(Texture const&) -> Texture& = delete;
  auto operator=(Texture&&) -> Texture& = default;

  auto Init(std::string_view path) -> bool;
  auto GetWidth() const -> int { return _width; }
  auto GetHeight() const -> int { return _height; }
  auto GetTexture() -> SDL_Texture* { return _texture.get(); }
  auto IsReady() const -> bool { return _texture != nullptr; }

private:
  std::unique_ptr<SDL_Texture, TextureDeletor> _texture;
  int _width = 0;
  int _height = 0;
};
