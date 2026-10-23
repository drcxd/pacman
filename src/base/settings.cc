#include "settings.hh"

#include <fstream>

#include "SDL3/SDL_log.h"

using nlohmann::json;

auto Settings::Init(std::string_view file) -> bool {
  std::ifstream fs(file.data());
  if (fs.good()) {
    _configs = json::parse(fs, nullptr, false);
    bool succeed = !_configs.is_discarded();
    if (!succeed) {
      SDL_Log("Parsing json file failed: %s", file.data());
    }
    return succeed;
  }
  SDL_Log("Can not open config file: %s", file.data());
  return false;
}

auto Settings::GetSpriteAnimationConfig(std::string_view name) const
    -> std::optional<SpriteAnimationConfig> {
  std::optional<SpriteAnimationConfig> ret;
  if (auto sprite_animations = _configs.find("sprite_animations");
      sprite_animations != _configs.end()) {
    for (auto const& [key, value] : sprite_animations->items()) {
      if (key == name) {
        auto frames = value.find("frames");
        auto texture_name = value.find("texture_name");
        auto frame_per_second = value.find("frame_per_second");
        if (frames != value.end() && texture_name != value.end() &&
            frame_per_second != value.end() && frames->is_array() &&
            texture_name->is_string() && frame_per_second->is_number()) {
          std::vector<SDL_FRect> rects;
          for (auto const& frame : *frames) {
            if (frame.size() >= 4 && frame[0].is_number() &&
                frame[1].is_number() && frame[2].is_number() &&
                frame[3].is_number()) {
              rects.push_back(
                  SDL_FRect{frame[0], frame[1], frame[2], frame[3]});
            }
            else {
              SDL_Log("Frame animation config %s format error: frame "
                      "description.");
            }
          }

          ret = SpriteAnimationConfig{value["texture_name"],
                                      value["frame_per_second"], rects};
        }
        else {
          SDL_Log("Invalid frame animation entry: %s", name.data());
        }
        break;
      }
    }
  }
  return ret;
}
