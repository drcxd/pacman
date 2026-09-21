#include "object.hh"

#include <cmath>

#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"

#include "game/input_handler.hh"

auto Object::Init(std::string_view texture_path) -> bool {
  _texture.Init(texture_path);
  return _texture.IsReady();
}

void Object::Draw(SDL_Renderer* renderer) {
  SDL_FRect dst;
  dst.x = std::floor(_x + 0.5);
  dst.y = std::floor(_y + 0.5);
  dst.w = _texture.GetWidth();
  dst.h = _texture.GetHeight();
  SDL_RenderTexture(renderer, _texture.GetTexture(), NULL, &dst);
}

void Object::Update() {
  constexpr double SPEED = 0.1;
  if (InputHandler::IsKeyDown(SDL_SCANCODE_W)) {
    MoveY(-SPEED);
  }
  if (InputHandler::IsKeyDown(SDL_SCANCODE_S)) {
    MoveY(+SPEED);
  }
  if (InputHandler::IsKeyDown(SDL_SCANCODE_A)) {
    MoveX(-SPEED);
  }
  if (InputHandler::IsKeyDown(SDL_SCANCODE_D)) {
    MoveX(+SPEED);
  }
}
