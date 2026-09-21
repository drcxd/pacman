#pragma once

#include "SDL3/SDL_init.h"

class InputHandler
{
public:
  static auto IsKeyDown(SDL_Scancode scancode) -> bool;
};
