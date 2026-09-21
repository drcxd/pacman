#include "input_handler.hh"

#include <SDL3/SDL_events.h>

auto InputHandler::IsKeyDown(SDL_Scancode scancode) -> bool {
  bool const* states = SDL_GetKeyboardState(NULL);
  return states[scancode];
}
