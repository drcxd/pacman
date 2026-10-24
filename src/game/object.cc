#include "object.hh"

// #include <cmath>

#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"

#include "base/game_instance.hh"
#include "game/input_handler.hh"
#include "game/maze.hh"
#include "base/settings.hh"

auto Object::Init(std::string_view name) -> bool {
  bool succeed = true;
  if (auto config = Settings::Get().GetObjectConfig(name)) {
    _speed = config->Speed;
    _size = config->Size;
    for (auto const& anim_name : config->SpriteAnimations) {
      SpriteAnimation anim;
      if (anim.Init(anim_name)) {
        _animations.emplace_back(std::move(anim));
      }
      else {
        succeed = false;
        break;
      }
    }
  }
  else {
    succeed = false;
  }
  if (!succeed) {
    SDL_Log("Failed to initialize object: %s", name.data());
  }
  return succeed;
}

void Object::Draw(SDL_Renderer* renderer) {
  SDL_FRect dst;
  dst.w = _size.first;
  dst.h = _size.second;
  dst.x = _pos.X - dst.w / 2;
  dst.y = _pos.Y - dst.h / 2;

  SpriteAnimation& current_anim = GetCurrentSpriteAnimation();
  auto frame = current_anim.GetCurrentFrame();
  SDL_RenderTexture(renderer, frame.Texture->GetTexture(), &frame.Frame, &dst);

  if (GameInstance::Get().DebugDraw()) {
    SDL_SetRenderDrawColorFloat(renderer, 1, 0, 0, 1);
    SDL_RenderPoint(renderer, _pos.X, _pos.Y);
  }
}

void Object::Update(double delta) {
  Direction new_dir = _dir;
  if (InputHandler::IsKeyDown(SDL_SCANCODE_W)) {
    new_dir = UP ;
  }
  if (InputHandler::IsKeyDown(SDL_SCANCODE_S)) {
    new_dir = DOWN;
  }
  if (InputHandler::IsKeyDown(SDL_SCANCODE_A)) {
    new_dir = LEFT;
  }
  if (InputHandler::IsKeyDown(SDL_SCANCODE_D)) {
    new_dir = RIGHT;
  }
  if (auto const* maze = GameInstance::Get().GetMaze()) {
    constexpr double SPEED = 32;
    double dist_delta = delta * SPEED;
    Position dst = _pos;
    if (maze->CanMove(dst, new_dir, dist_delta)) {
      _pos = dst;
      _dir = new_dir;
    }
    else if (new_dir != _dir) { // try the old dir if they are different
      dst = _pos;
      if (maze->CanMove(dst, _dir, dist_delta)) {
        _pos = dst;
      }
    }
  }
  auto& current_anim = GetCurrentSpriteAnimation();
  current_anim.Update(delta);
  // TODO: how to handle the transition from one direction to another?
}

auto Object::GetCurrentSpriteAnimation() -> SpriteAnimation& {
  if (_dir == LEFT) {
    return _animations[static_cast<int>(EDir::LEFT)];
  }
  if (_dir == RIGHT) {
    return _animations[static_cast<int>(EDir::RIGHT)];
  }
  if (_dir == UP) {
    return _animations[static_cast<int>(EDir::UP)];
  }
  return _animations[static_cast<int>(EDir::DOWN)];
}
