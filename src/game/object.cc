#include "object.hh"

#include <cmath>

#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"

#include "base/game_instance.hh"
#include "game/input_handler.hh"
#include "game/maze.hh"

auto Object::Init(std::string_view texture_path) -> bool {
  return _animation.Init("pacman-right");
}

void Object::Draw(SDL_Renderer* renderer) {
  SDL_FRect dst;
  // TODO: remove constant
  dst.w = 16;
  dst.h = 16;
  dst.x = _pos.X - dst.w / 2;
  dst.y = _pos.Y - dst.h / 2;

  auto frame = _animation.GetCurrentFrame();
  SDL_RenderTexture(renderer, frame.Texture->GetTexture(), &frame.Frame, &dst);

  if (GameInstance::Get().DebugDraw()) {
    SDL_SetRenderDrawColorFloat(renderer, 1, 0, 0, 1);
    SDL_RenderPoint(renderer, _pos.X, _pos.Y);
  }
}

void Object::Update(double delta) {
  _animation.Update(delta);
  Direction new_dir = _dir;
  if (InputHandler::IsKeyDown(SDL_SCANCODE_W)) {
    new_dir = {0, -1};
  }
  if (InputHandler::IsKeyDown(SDL_SCANCODE_S)) {
    new_dir = {0, 1};
  }
  if (InputHandler::IsKeyDown(SDL_SCANCODE_A)) {
    new_dir = {-1, 0};
  }
  if (InputHandler::IsKeyDown(SDL_SCANCODE_D)) {
    new_dir = {1, 0};
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
}
