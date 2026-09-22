#pragma once

#include <string_view>

#include <base/timer.hh>

class Object;

class GameInstance
{
public:
  GameInstance(std::string_view title, int width, int height);
  ~GameInstance();
  auto GetRenderer() -> class SDL_Renderer* { return _renderer; }
  auto GetWindow() -> class SDL_Window* { return _window; }
  auto IsError() -> bool { return _error; }
  auto GetPlayerObject() -> Object*;
  auto InitPlayer(std::string_view texture_path) -> bool;
  auto GetTimer() const -> Timer const& { return _timer; }
  /**
   * Return the time since the game instance is created in seconds.
   */
  auto GetCurrentTime() const -> double;
  /**
   * Return the time elapsed in seconds since last time the timer is set.
   */
  auto GetDelta() -> double;
private:
  SDL_Renderer* _renderer = nullptr;
  SDL_Window* _window = nullptr;
  std::string_view _title;
  int _width = 640;
  int _height = 480;
  bool _error = false;

  Object* _player = nullptr;

  Timer _timer;
  Uint64 _last_time = 0;
};
