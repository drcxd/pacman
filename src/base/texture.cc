#include "texture.hh"

#include "SDL3/SDL_log.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_surface.h"

#include <global.hh>
#include <base/game_instance.hh>

auto Texture::Init(std::string_view path) -> bool {
  if (SDL_Surface *surface = SDL_LoadPNG(path.data())) {
    _width = surface->w;
    _height = surface->h;
    _texture =
        SDL_CreateTextureFromSurface(gGameInstance->GetRenderer(), surface);
    if (_texture == nullptr) {
      SDL_Log("Can not create texture: %s", SDL_GetError());
    }
    SDL_DestroySurface(surface);
  } else {
    SDL_Log("Couldn't load file: %s. Error: %s", path.data(), SDL_GetError());
  }
  return _texture != nullptr;
}

Texture:: ~Texture() {
  if (_texture != nullptr) {
    SDL_DestroyTexture(_texture);
  }
}
