#define SDL_MAIN_USE_CALLBACKS 1 /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "global.hh"
#include <base/game_instance.hh>
#include <game/object.hh>
#include <game/input_handler.hh>

constexpr int WINDOW_WIDTH = 640;
constexpr int WINDOW_HEIGHT = 480;

/* This function runs once at startup. */
auto SDL_AppInit(void** /*appstate*/, int /*argc*/, char* /*argv*/[])
    -> SDL_AppResult {
  SDL_SetAppMetadata("Pac-Man", "1.0", "pac-man");

  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  gGameInstance = new GameInstance{"Pac-Man", WINDOW_WIDTH, WINDOW_HEIGHT};

  gGameInstance->InitPlayer("assets/ghosts/pinky.png");

  return SDL_APP_CONTINUE; /* carry on with the program! */
}

/* This function runs when a new event (mouse input, keypresses, etc) occurs. */
auto SDL_AppEvent(void* /*appstate*/, SDL_Event* event) -> SDL_AppResult {
  if (event->type == SDL_EVENT_QUIT) {
    return SDL_APP_SUCCESS; /* end the program, reporting success to the OS. */
  }
  else if (event->type == SDL_EVENT_KEY_DOWN &&
           event->key.scancode == SDL_SCANCODE_ESCAPE) {
    return SDL_APP_SUCCESS;
  }
  return SDL_APP_CONTINUE;
}

/* This function runs once per frame, and is the heart of the program. */
auto SDL_AppIterate(void* /*appstate*/) -> SDL_AppResult {
  SDL_FRect dst_rect;

  auto* renderer = gGameInstance->GetRenderer();
  /* as you can see from this, rendering draws over whatever was drawn before
   * it. */
  SDL_SetRenderDrawColor(renderer, 0, 0, 0,
                         SDL_ALPHA_OPAQUE); /* black, full alpha */
  SDL_RenderClear(renderer);                /* start with a blank canvas. */

  if (auto* player = gGameInstance->GetPlayerObject()) {
    player->Update();
    player->Draw(renderer);
  }

  SDL_RenderPresent(renderer); /* put it all on the screen! */

  ++gFrameNumber;
  return SDL_APP_CONTINUE; /* carry on with the program! */
}

/* This function runs once at shutdown. */
auto SDL_AppQuit(void* /*appstate*/, SDL_AppResult /*result*/) -> void {
  /* SDL will clean up the window/renderer for us. */
}
