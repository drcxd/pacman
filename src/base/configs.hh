#pragma once

#include "SDL3/SDL_rect.h"

#include <string>
#include <vector>

struct SpriteAnimationConfig {
  std::string TextureName;
  double FramePerSecond = 1;
  std::vector<SDL_Rect> Frames;
};
