#include "object.hh"

#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"

auto Object::Init(std::string_view texture_path) -> bool {
  _texture.Init(texture_path);
  return _texture.IsReady();
}

void Object::Draw(SDL_Renderer* renderer) {
  SDL_FRect dst;
  dst.x = _x;
  dst.y = _y;
  dst.w = _texture.GetWidth();
  dst.h = _texture.GetHeight();
  SDL_RenderTexture(renderer, _texture.GetTexture(), NULL, &dst);
}
