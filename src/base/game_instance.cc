#include "game_instance.hh"

#include "SDL3/SDL_log.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_video.h"

#include "game/object.hh"
#include "game/maze.hh"
#include "settings.hh"
#include "texture_manager.hh"

GameInstance::~GameInstance() {
  if (_player != nullptr) {
    delete _player;
    _player = nullptr;
  }
}

auto GameInstance::Init(std::string_view config) -> bool {
  auto& settings = Settings::Get();
  if (settings.Init(config)) {
    if (settings.GetConfigValue("width", &_width) &&
        settings.GetConfigValue("height", &_height) &&
        settings.GetConfigValue("title", &_title)) {
      if (SDL_CreateWindowAndRenderer(_title.data(), _width, _height,
                                      SDL_WINDOW_RESIZABLE, &_window,
                                      &_renderer)) {
        SDL_SetRenderLogicalPresentation(
            _renderer, _width, _height, SDL_LOGICAL_PRESENTATION_INTEGER_SCALE);
        SDL_SetDefaultTextureScaleMode(_renderer, SDL_SCALEMODE_PIXELART);
        std::string player_texture;
        if (TextureManager::Get().Init()) {
          if (settings.GetConfigValue("player_texture", &player_texture)) {
            if (InitPlayer(player_texture) && InitMaze()) {
              _maze->SetToStart(_player);
              return true;
            }
          }
        }
      }
      else {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
      }
    }
  }
  return false;
}

void GameInstance::Update(double delta) {
  _player->Update(delta);
}

void GameInstance::GameInstance::Draw(class SDL_Renderer* renderer)  {
  _maze->Draw(renderer);
  _player->Draw(renderer);
}

auto GameInstance::GetPlayerObject() -> Object* { return _player; }

auto GameInstance::InitPlayer(std::string_view texture_path) -> bool {
  _player = new Object();
  return _player->Init(texture_path);
}

auto GameInstance::InitMaze() -> bool {
  _maze = new Maze();
  return _maze->Init();
}

auto GameInstance::GetDelta() -> double {
  return _timer.GetDelta() / 1000.0;
}

auto GameInstance::GetCurrentTime() const -> double {
  return _timer.GetTimeS();
}

auto GameInstance::GetMinFrameTime() const -> double {
  int max_fps = 60;
  Settings::Get().GetConfigValue("max_fps", &max_fps);
  return 1.0 / max_fps;
}

auto GameInstance::OnKeyDown(SDL_KeyboardEvent const& event) -> SDL_AppResult {
  if (event.scancode == SDL_SCANCODE_ESCAPE) {
    return SDL_APP_SUCCESS;
  }
  if (event.scancode == SDL_SCANCODE_T) {
    _debug_draw = !_debug_draw;
  }
  if (event.scancode == SDL_SCANCODE_R) {
    _truncate_location = !_truncate_location;
  }
  return SDL_APP_CONTINUE;
}
