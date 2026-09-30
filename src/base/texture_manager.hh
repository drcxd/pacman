#pragma once

#include <string>
#include <unordered_map>

#include "texture.hh"

class TextureManager {
public:
  TextureManager(TextureManager const&) = delete;
  TextureManager(TextureManager&&) = delete;
  auto operator=(TextureManager const&) -> TextureManager& = delete;
  auto operator=(TextureManager&&) -> TextureManager& = delete;
  ~TextureManager() = default;
  static auto Get() -> TextureManager& {
    static TextureManager inst;
    return inst;
  }

  auto Init() -> bool;
  auto GetTexture(std::string const& name) const -> Texture const*;
private:
  TextureManager() = default;
  std::unordered_map<std::string, Texture> _textures;
};
