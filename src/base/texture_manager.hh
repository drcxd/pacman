#pragma once

#include <string>
#include <unordered_map>

#include "texture.hh"

class TextureManager {
public:
  auto Init() -> bool;
  auto GetTexture(std::string const& name) const -> Texture const*;
private:
  std::unordered_map<std::string, Texture> _textures;
};
