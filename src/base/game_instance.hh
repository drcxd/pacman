#pragma once

#include <string_view>
#include <string>

#include <base/timer.hh>
#include <base/settings.hh>

class Object;

class GameInstance {
public:
  explicit GameInstance(std::string_view config);
  ~GameInstance();

  auto GetRenderer() -> class SDL_Renderer* { return _renderer; }
  auto GetWindow() -> class SDL_Window* { return _window; }
  auto IsError() -> bool { return _error; }

  /**
   * Initialize game logic.
   */
  auto Init() -> bool;

  auto GetPlayerObject() -> Object*;

  [[nodiscard]] auto GetTimer() const -> Timer const& { return _timer; }

  /**
   * Return the time since the game instance is created in seconds.
   */
  [[nodiscard]] auto GetCurrentTime() const -> double;

  /**
   * Return the time elapsed in seconds since last time the timer is set.
   */
  auto GetDelta() -> double;

  /**
   * Return the minimum frame time in seconds.
   */
  [[nodiscard]] auto GetMinFrameTime() const -> double;

private:
  auto InitPlayer(std::string_view texture_path) -> bool;

  Settings _settings;

  std::string _title;
  int _width = 0;
  int _height = 0;

  SDL_Renderer* _renderer = nullptr;
  SDL_Window* _window = nullptr;

  bool _error = false;

  Timer _timer;

  Object* _player = nullptr;
};
