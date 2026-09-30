#include "sprite_animation.hh"

#include "math.hh"

void SpriteAnimation::Init(std::string_view name) {
  _name = name;
  // TODO: init other fields from setting?
}

void SpriteAnimation::Update(double delta) {
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
