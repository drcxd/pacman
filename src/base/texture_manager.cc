#include "texture_manager.hh"

#include "base/settings.hh"

auto TextureManager::Init() -> bool {
  auto const& settings = Settings::Get();
  std::unordered_map<std::string, std::string> textures;
  if (settings.GetConfigValue("textures", &textures)) {
    for (auto const& pair : textures) {
      Texture t;
      if (t.Init(pair.second)) {
        _textures.insert({pair.first, t});
      }
    }
  }
  return true;
}

auto TextureManager::GetTexture(std::string const& name) const
    -> Texture const* {
  Texture const* ret = nullptr;
  if (auto it = _textures.find(name); it != _textures.cend()) {
    ret = &(it->second);
  }
  return ret;
}
