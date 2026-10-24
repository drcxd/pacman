#pragma once

#include "SDL3/SDL_rect.h"
#include "json.hpp"

#include <string>
#include <vector>

using nlohmann::json;

struct SpriteAnimationConfig {
  std::string TextureName;
  double FramePerSecond = 1;
  std::vector<SDL_FRect> Frames;
};

// NOLINTNEXTLINE(modernize-use-constraints)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(SDL_FRect, x, y, w, h);

// NOLINTNEXTLINE(modernize-use-constraints)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(SpriteAnimationConfig, TextureName,
                                   FramePerSecond, Frames);

enum class EDir : unsigned char {
  LEFT = 0,
  RIGHT,
  UP,
  DOWN,
  MAX,
};

struct ObjectConfig {
  std::vector<std::string> SpriteAnimations;
  float Speed = 0;
  std::pair<int, int> Size;
};
