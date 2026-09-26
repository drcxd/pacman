#include "object.hh"

#include <cmath>

#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"

#include "global.hh"
#include "base/game_instance.hh"
#include "game/input_handler.hh"
#include "game/maze.hh"

auto Object::Init(std::string_view texture_path) -> bool {
  _texture.Init(texture_path);
  return _texture.IsReady();
}

void Object::Draw(SDL_Renderer* renderer) {
  SDL_FRect dst;
  // TODO: remove constant
  dst.w = 16;
  dst.h = 16;
  dst.x = _pos.X - dst.w / 2;
  dst.y = _pos.Y - dst.h / 2;
  SDL_RenderTexture(renderer, _texture.GetTexture(), NULL, &dst);
  if (gGameInstance->DebugDraw()) {
    SDL_SetRenderDrawColorFloat(renderer, 1, 0, 0, 1);
    SDL_RenderPoint(renderer, _pos.X, _pos.Y);
  }
}

void Object::Update(double delta) {
  if (InputHandler::IsKeyDown(SDL_SCANCODE_W)) {
    _dir = {0, -1};
  }
  if (InputHandler::IsKeyDown(SDL_SCANCODE_S)) {
    _dir = {0, 1};
  }
  if (InputHandler::IsKeyDown(SDL_SCANCODE_A)) {
    _dir = {-1, 0};
  }
  if (InputHandler::IsKeyDown(SDL_SCANCODE_D)) {
    _dir = {1, 0};
  }
  if (auto* maze = gGameInstance->GetMaze()) {
    constexpr double SPEED = 32;
    double dist_delta = delta * SPEED;
    Position dst = _pos;
    dst.X += _dir.X * dist_delta;
    dst.Y += _dir.Y * dist_delta;
    if (maze->CanMove(_pos, dst, _dir)) {
      _pos = dst;
    }
  }
}
