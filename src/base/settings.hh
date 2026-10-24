#pragma once

#include <string_view>
#include <optional>

#include <json.hpp>
#include "SDL3/SDL_log.h"

#include "configs.hh"

class Settings {
public:
  Settings(Settings const&) = delete;
  Settings(Settings&&) = delete;
  auto operator=(Settings const&) -> Settings& = delete;
  auto operator=(Settings&&) -> Settings& = delete;
  ~Settings() = default;

  static auto Get() -> Settings& {
    static Settings inst;
    return inst;
  }

  auto Init(std::string_view file) -> bool;

  template <typename T>
  auto GetConfigValue(std::string_view key, T* value) const -> bool {
    if (!_configs.is_discarded()) {
      try {
        *value = _configs.at(key.data()).get<T>();
      }
      catch (nlohmann::json::out_of_range& e) {
        SDL_Log("Invalid key in JSON file: %s", key.data());
        return false;
      }
      catch (nlohmann::json::type_error& e) {
        SDL_Log("Invalid value type in JSON file for key: %s", key.data());
        return false;
      }
      return true;
    }
    return false;
  }

  [[nodiscard]] auto GetSpriteAnimationConfig(std::string_view name) const
      -> std::optional<SpriteAnimationConfig>;

  [[nodiscard]] auto GetObjectConfig(std::string_view name) const
      -> std::optional<ObjectConfig>;

private:
  Settings() = default;

  nlohmann::json _configs;
};
