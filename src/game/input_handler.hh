#pragma once

#include "SDL3/SDL_init.h"

class InputHandler
{
public:
  static auto HandleEvent(SDL_Event const* event) -> SDL_AppResult;
private:
  static auto OnKeyUp(SDL_KeyboardEvent const& event) -> SDL_AppResult;
  static auto OnKeyDown(SDL_KeyboardEvent const& event) -> SDL_AppResult;
};
