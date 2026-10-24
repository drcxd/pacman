#include "settings.hh"

#include <fstream>
#include <format>

#include "SDL3/SDL_log.h"

using nlohmann::json;

auto Settings::Init(std::string_view file) -> bool {
  std::ifstream fstream(file.data());
  if (fstream.good()) {
    bool succeed = true;
    try {
      _configs = json::parse(fstream);
    }
    catch (std::exception& e) {
      SDL_Log("Parsing json file failed: %s", e.what());
      succeed = false;
    }
    return succeed;
  }
  SDL_Log("Can not open config file: %s", file.data());
  return false;
}

auto Settings::GetSpriteAnimationConfig(std::string_view name) const
    -> std::optional<SpriteAnimationConfig> {
  static std::string const SPRITE_ANIMATION_SECTION = "sprite_animations";
  std::optional<SpriteAnimationConfig> ret;
  auto json_pointer =
      json::json_pointer(std::format("/{}/{}", SPRITE_ANIMATION_SECTION, name));
  if (_configs.contains(json_pointer)) {
    // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-avoid-unchecked-container-access)
    auto entry = _configs[json_pointer];
    try {
      SpriteAnimationConfig config = entry.get<SpriteAnimationConfig>();
      ret.emplace(std::move(config));
    }
    catch (std::exception& e) {
      SDL_Log("Failed to read sprite animation entry %s: %s.", name.data(),
              e.what());
    }
  }
  else {
    SDL_Log("Missing sprite animation entry: %s", name.data());
  }
  return ret;
}

static void from_json(json const& json, ObjectConfig& obj) {
  auto anims = json.at("SpriteAnimations");
  if (!anims.is_array() || anims.size() != 4) {
    throw std::runtime_error{
        "SpriteAnimations is not an array or element number mismatch!"};
  }
  for (auto& anim : anims) {
    std::string name = anim;
    obj.SpriteAnimations.emplace_back(std::move(name));
  }
  obj.Speed = json.at("Speed");
  obj.Size = json.at("Size");
}

auto Settings::GetObjectConfig(std::string_view name) const
    -> std::optional<ObjectConfig> {
  static std::string const OBJECTS_SECTION = "objects";
  std::optional<ObjectConfig> ret;
  auto json_pointer =
      json::json_pointer(std::format("/{}/{}", OBJECTS_SECTION, name));
  if (_configs.contains(json_pointer)) {
    // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-avoid-unchecked-container-access)
    auto entry = _configs[json_pointer];
    try {
      ObjectConfig config = entry.get<ObjectConfig>();
      ret.emplace(std::move(config));
    }
    catch (std::exception& e) {
      SDL_Log("Failed to read object entry %s: %s", name.data(), e.what());
    }
  }
  else {
    SDL_Log("Missing object entry: %s", name.data());
  }
  return ret;
}
