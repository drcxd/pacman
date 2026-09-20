#include "input_handler.hh"
#include "SDL3/SDL_log.h"

#include <SDL3/SDL_events.h>

auto InputHandler::HandleEvent(SDL_Event const* event) -> SDL_AppResult {
  if (event->type == SDL_EVENT_KEY_DOWN) {
    return OnKeyDown(event->key);
  }
  else if (event->type == SDL_EVENT_KEY_UP) {
    return OnKeyUp(event->key);
  }
  return SDL_APP_CONTINUE;
}

auto InputHandler::OnKeyUp(SDL_KeyboardEvent const& event) -> SDL_AppResult {
  return SDL_APP_CONTINUE;
}

auto InputHandler::OnKeyDown(SDL_KeyboardEvent const& event) -> SDL_AppResult {
  switch (event.scancode) {
  case SDL_SCANCODE_ESCAPE: {
    SDL_Log("Player requests shutting down...");
    return SDL_APP_SUCCESS;
  }
  case SDL_SCANCODE_W: {
    break;
  }
  case SDL_SCANCODE_S: {
    break;
  }
  case SDL_SCANCODE_A: {
    break;
  }
  case SDL_SCANCODE_D: {
    break;
  }
  default: break;
  }
  return SDL_APP_CONTINUE;
}
