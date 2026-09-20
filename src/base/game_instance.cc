#include "game_instance.hh"

#include "SDL3/SDL_log.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_video.h"

GameInstance::GameInstance(std::string_view title, int width, int height)
  : _title (title)
  , _width (width)
  , _height (height)
{
  if (SDL_CreateWindowAndRenderer(_title.data(), _width, _height,
                                  SDL_WINDOW_RESIZABLE, &_window, &_renderer)) {
    SDL_SetRenderLogicalPresentation(_renderer, _width, _height,
                                     SDL_LOGICAL_PRESENTATION_LETTERBOX);

  } else {
    SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
    _error = true;
  }
}
