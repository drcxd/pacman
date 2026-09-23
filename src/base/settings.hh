#pragma once

#include <string_view>

#include <json.hpp>
#include "SDL3/SDL_log.h"

class Settings {
public:
  auto Init(std::string_view file) -> bool;
  /**
   * Returns a
   */
  template <typename T>
  auto GetConfigValue(std::string_view key, T* value) const -> bool {
    if (!_configs.is_discarded()) {
      try {
        *value = _configs.at(key.data());
      }
      catch (nlohmann::json::out_of_range& e) {
        SDL_Log("Invalid key in JSON file: %s", key.data());
        return false;
      }
      return true;
    }
    else {
      return false;
    }
  }

private:
  nlohmann::json _configs;
};
