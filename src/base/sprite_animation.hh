#pragma once

#include <vector>
#include <string>

#include "SDL3/SDL_rect.h"

struct SpriteAnimationFrame {
  class Texture const* Texture = nullptr;
  SDL_FRect Frame{};
};

class SpriteAnimation {
public:
  auto Init(std::string_view name) -> bool;
  void Update(double delta);
  [[nodiscard]] auto GetCurrentFrame() const -> SpriteAnimationFrame;

private:
  class Texture const* _texture = nullptr;
  double _current_frame = 0;
  double _current_time = 0;

  /**
   * The name of the sprite animation itself.
   */
  std::string _name;

  std::vector<SDL_FRect> _frames;

  /**
   * The name of the texture it depends on.
   */
  std::string _texture_name;

  /**
   * How many frames played in a second.
   */
  double _frame_per_second = 1;

  /**
   * The total time of this sprite animation.
   */
  double _max_time = 0;
};
