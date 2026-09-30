#define SDL_MAIN_USE_CALLBACKS 1 /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include <base/game_instance.hh>
#include <base/timer.hh>
#include <game/object.hh>
#include <game/input_handler.hh>

/* This function runs once at startup. */
auto SDL_AppInit(void** /*appstate*/, int /*argc*/, char* /*argv*/[])
    -> SDL_AppResult {
  SDL_SetAppMetadata("Pac-Man", "1.0", "pac-man");

  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  if (!GameInstance::Get().Init("config/game.json")) {
    SDL_Log("Failed to initialize game instance.");
    return SDL_APP_FAILURE;
  }
  return SDL_APP_CONTINUE; /* carry on with the program! */
}

/* This function runs when a new event (mouse input, keypresses, etc) occurs. */
auto SDL_AppEvent(void* /*appstate*/, SDL_Event* event) -> SDL_AppResult {
  if (event->type == SDL_EVENT_QUIT) {
    return SDL_APP_SUCCESS; /* end the program, reporting success to the OS. */
  }
  else if (event->type == SDL_EVENT_KEY_DOWN) {
    return GameInstance::Get().OnKeyDown(event->key);
  }
  return SDL_APP_CONTINUE;
}

/* This function runs once per frame, and is the heart of the program. */
auto SDL_AppIterate(void* /*appstate*/) -> SDL_AppResult {
  auto& game_instance = GameInstance::Get();
  double delta = game_instance.GetDelta();

  auto* renderer = game_instance.GetRenderer();
  /* as you can see from this, rendering draws over whatever was drawn before
   * it. */
  SDL_SetRenderDrawColor(renderer, 0, 0, 0,
                         SDL_ALPHA_OPAQUE); /* black, full alpha */
  SDL_RenderClear(renderer);                /* start with a blank canvas. */

  game_instance.Update(delta);

  game_instance.Draw(renderer);

  SDL_RenderPresent(renderer); /* put it all on the screen! */

  game_instance.IncFrame();
  double const frame_time = game_instance.GetMinFrameTime();
  if (delta < frame_time) {
    SDL_Delay(static_cast<unsigned>((frame_time - delta) * 1000 + 0.5));
  }
  return SDL_APP_CONTINUE; /* carry on with the program! */
}

/* This function runs once at shutdown. */
auto SDL_AppQuit(void* /*appstate*/, SDL_AppResult /*result*/) -> void {
  /* SDL will clean up the window/renderer for us. */
}
