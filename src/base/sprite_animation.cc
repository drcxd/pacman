#include "sprite_animation.hh"

#include <optional>

#include "base/configs.hh"
#include "base/settings.hh"
#include "base/math.hh"
#include "base/texture_manager.hh"

auto SpriteAnimation::Init(std::string_view name) -> bool {
  _name = name;
  std::optional<SpriteAnimationConfig> config =
      Settings::Get().GetSpriteAnimationConfig(name);
  if (config) {
    _texture_name = config->TextureName;
    _frame_per_second = config->FramePerSecond;
    _frames = std::move(config->Frames);
    _max_time = _frames.size() / _frame_per_second;
    _current_frame = 0;
    _current_time = 0;
    _texture = TextureManager::Get().GetTexture(_texture_name);
  }

  if (!config || _texture == nullptr) {
    SDL_Log("Failed to initialized sprite animation: %s", name.data());
    return false;
  }

  return true;
}

void SpriteAnimation::Update(double delta) {
  _current_time += delta;
  _current_time = mod<double>(_current_time, _max_time);
  // TODO: use _current_time to compute _current_frame for a more flexible frame
  // duration setting
  _current_frame += delta * _frame_per_second;
  _current_frame = mod<double>(_current_frame, _frames.size());
}

auto SpriteAnimation::GetCurrentFrame() const -> SpriteAnimationFrame {
  SpriteAnimationFrame ret;
  ret.Texture = _texture;
  if (0 <= _current_frame && _current_frame < _frames.size()) {
    ret.Frame = _frames.at(static_cast<int>(_current_frame));
  }
  return ret;
}
