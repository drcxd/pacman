#include "game_instance.hh"

#include "SDL3/SDL_log.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_video.h"

#include "game/object.hh"
#include "game/maze.hh"

GameInstance::GameInstance(std::string_view config) {
  if (_settings.Init(config)) {
    bool succeed = true;
    succeed = succeed && _settings.GetConfigValue("width", &_width);
    succeed = succeed && _settings.GetConfigValue("height", &_height);
    succeed = succeed && _settings.GetConfigValue("title", &_title);
    if (succeed) {
      if (SDL_CreateWindowAndRenderer(_title.data(), _width, _height,
                                      SDL_WINDOW_RESIZABLE, &_window,
                                      &_renderer)) {
        SDL_SetRenderLogicalPresentation(_renderer, _width, _height,
                                         SDL_LOGICAL_PRESENTATION_INTEGER_SCALE);
        SDL_SetDefaultTextureScaleMode(_renderer, SDL_SCALEMODE_PIXELART);
      }
      else {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        _error = true;
      }
    }
    else {
      _error = true;
    }
  }
  else {
    _error = true;
  }
}

GameInstance::~GameInstance() {
  if (_player != nullptr) {
    delete _player;
    _player = nullptr;
  }
}

auto GameInstance::Init() -> bool {
  std::string player_texture;
  if (_settings.GetConfigValue("player_texture", &player_texture)) {
    if (_texture_manager.Init()) {
      if (InitPlayer(player_texture) && InitMaze()) {
        _maze->SetToStart(_player);
        return true;
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
  _settings.GetConfigValue("max_fps", &max_fps);
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
