#define SDL_MAIN_USE_CALLBACKS 1 /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include <string>

/* We will use this renderer to draw into this window every frame. */
static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static SDL_Texture *texture = NULL;
static int texture_width = 0;
static int texture_height = 0;

constexpr int WINDOW_WIDTH = 640;
constexpr int WINDOW_HEIGHT = 480;

namespace {
  auto OnKeyUp(SDL_KeyboardEvent const& event) -> SDL_AppResult;
  auto OnKeyDown(SDL_KeyboardEvent const& event) -> SDL_AppResult;
}

/* This function runs once at startup. */
auto SDL_AppInit(void** /*appstate*/, int /*argc*/, char* /*argv*/[]) -> SDL_AppResult {
  SDL_SetAppMetadata("Pac-Man", "1.0", "com.vovo.pac-man");

  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  if (!SDL_CreateWindowAndRenderer("Pac-Man", WINDOW_WIDTH, WINDOW_HEIGHT,
                                   SDL_WINDOW_RESIZABLE, &window, &renderer)) {
    SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }
  SDL_SetRenderLogicalPresentation(renderer, WINDOW_WIDTH, WINDOW_HEIGHT,
                                   SDL_LOGICAL_PRESENTATION_LETTERBOX);

  std::string png_path{"assets/ghosts/pinky.png"};

  SDL_Surface* surface = SDL_LoadPNG(png_path.c_str());
  if (!surface) {
    SDL_Log("Couldn't load png: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  texture_width = surface->w;
  texture_height = surface->h;

  texture = SDL_CreateTextureFromSurface(renderer, surface);
  if (!texture) {
    SDL_Log("Couldn't create static texture: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  SDL_DestroySurface(
      surface); /* done with this, the texture has a copy of the pixels now. */
  // TODO: Create wrapper classes for texture, surface, and log.

  return SDL_APP_CONTINUE; /* carry on with the program! */
}

/* This function runs when a new event (mouse input, keypresses, etc) occurs. */
auto SDL_AppEvent(void* /*appstate*/, SDL_Event *event) -> SDL_AppResult {
  if (event->type == SDL_EVENT_QUIT) {
    return SDL_APP_SUCCESS; /* end the program, reporting success to the OS. */
  } else if (event->type == SDL_EVENT_KEY_UP) {
    return OnKeyUp(event->key);
  } else if (event->type == SDL_EVENT_KEY_DOWN) {
    return OnKeyDown(event->key);
  }
  return SDL_APP_CONTINUE; /* carry on with the program! */
}

/* This function runs once per frame, and is the heart of the program. */
auto SDL_AppIterate(void* /*appstate*/) -> SDL_AppResult {
  SDL_FRect dst_rect;

  /* as you can see from this, rendering draws over whatever was drawn before
   * it. */
  SDL_SetRenderDrawColor(renderer, 0, 0, 0,
                         SDL_ALPHA_OPAQUE); /* black, full alpha */
  SDL_RenderClear(renderer);                /* start with a blank canvas. */

  /* center this one. */
  dst_rect.x = ((float)(WINDOW_WIDTH - texture_width)) / 2.0f;
  dst_rect.y = ((float)(WINDOW_HEIGHT - texture_height)) / 2.0f;
  dst_rect.w = (float)texture_width;
  dst_rect.h = (float)texture_height;
  SDL_RenderTexture(renderer, texture, NULL, &dst_rect);

  SDL_RenderPresent(renderer); /* put it all on the screen! */

  return SDL_APP_CONTINUE; /* carry on with the program! */
}

/* This function runs once at shutdown. */
auto SDL_AppQuit(void* /*appstate*/, SDL_AppResult /*result*/) -> void {
  SDL_DestroyTexture(texture);
  /* SDL will clean up the window/renderer for us. */
}

namespace {
auto OnKeyDown(SDL_KeyboardEvent const &event) -> SDL_AppResult {
  switch (event.key) {
  case SDLK_ESCAPE: {
    return SDL_APP_SUCCESS;
    break;
  }
  case SDLK_W: {
    break;
  }
  case SDLK_A: {
    break;
  }
  case SDLK_S: {
    break;
  }
  case SDLK_D: {
    break;
  }
  }
  return SDL_APP_CONTINUE;
}
auto OnKeyUp(SDL_KeyboardEvent const &event) -> SDL_AppResult {
  switch (event.key) {
  case SDLK_W: {
    break;
  }
  case SDLK_A: {
    break;
  }
  case SDLK_S: {
    break;
  }
  case SDLK_D: {
    break;
  }
  }
  return SDL_APP_CONTINUE;
}
} // namespace
