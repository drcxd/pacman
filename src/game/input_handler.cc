#include "input_handler.hh"

#include <SDL3/SDL_log.h>
#include <SDL3/SDL_events.h>

#include <global.hh>
#include <base/game_instance.hh>
#include <game/object.hh>

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
  // TODO: Need an array to store the pressed/released state of keys.
  switch (event.scancode) {
  case SDL_SCANCODE_ESCAPE: {
    SDL_Log("Player requests shutting down...");
    return SDL_APP_SUCCESS;
  }
  case SDL_SCANCODE_W: {
    if (auto* player = g_game_instance->GetPlayerObject()) {
      player->MoveY(-1);
    }
    break;
  }
  case SDL_SCANCODE_S: {
    if (auto* player = g_game_instance->GetPlayerObject()) {
      player->MoveY(+1);
    }
    break;
  }
  case SDL_SCANCODE_A: {
    if (auto* player = g_game_instance->GetPlayerObject()) {
      player->MoveX(-1);
    }
    break;
  }
  case SDL_SCANCODE_D: {
    if (auto* player = g_game_instance->GetPlayerObject()) {
      player->MoveX(+1);
    }
    break;
  }
  default: break;
  }
  return SDL_APP_CONTINUE;
}
