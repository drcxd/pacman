#pragma once

#include <vector>
#include <string>

#include "SDL3/SDL_rect.h"

struct SpriteAnimationFrame {
  class Texture* Texture = nullptr;
  SDL_Rect Frame{};
};

class SpriteAnimation {
public:
  void Init(std::string_view name);
  void Update(double delta);
  [[nodiscard]] auto GetCurrentFrame() const -> SpriteAnimationFrame;
private:
  class Texture* _texture = nullptr;
  double _current_frame = 0;

  std::vector<SDL_Rect> _frames;
  std::string _name;
  double _frame_per_second = 1;
};
