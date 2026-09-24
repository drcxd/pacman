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
  dst.x = _pos.X;
  dst.y = _pos.Y;
  dst.w = _texture.GetWidth();
  dst.h = _texture.GetHeight();
  SDL_RenderTexture(renderer, _texture.GetTexture(), NULL, &dst);
}

void Object::Update(double delta) {
  if (auto* maze = gGameInstance->GetMaze()) {
    if (maze->CanMove(_pos, _dir)) {
      constexpr double SPEED = 32;
      double dist_delta = delta * SPEED;
      if (InputHandler::IsKeyDown(SDL_SCANCODE_W)) {
        _pos.Y -= dist_delta;
        // MoveY(-dist_delta);
      }
      if (InputHandler::IsKeyDown(SDL_SCANCODE_S)) {
        _pos.Y += dist_delta;
        // MoveY(+dist_delta);
      }
      if (InputHandler::IsKeyDown(SDL_SCANCODE_A)) {
        _pos.X -= dist_delta;
        // MoveX(-dist_delta);
      }
      if (InputHandler::IsKeyDown(SDL_SCANCODE_D)) {
        _pos.X += dist_delta;
        // MoveX(+dist_delta);
      }
    }
  }
}
