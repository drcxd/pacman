#include "settings.hh"

#include <fstream>

#include "SDL3/SDL_log.h"

using json = nlohmann::json;

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
  else {
    SDL_Log("Can not open config file: %s", file.data());
    return false;
  }
}
