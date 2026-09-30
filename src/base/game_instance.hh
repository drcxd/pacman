#pragma once

#include "SDL3/SDL_init.h"
#include <string_view>
#include <string>

#include <base/timer.hh>

class Object;
class Maze;

class GameInstance {
public:
  static auto Get() -> GameInstance& {
    static GameInstance inst;
    return inst;
  }
  GameInstance(GameInstance const&) = delete;
  GameInstance(GameInstance&&) = delete;
  auto operator=(GameInstance const&) -> GameInstance& = delete;
  auto operator=(GameInstance&&) -> GameInstance& = delete;
  ~GameInstance();

  auto GetRenderer() -> class SDL_Renderer* { return _renderer; }
  auto GetWindow() -> class SDL_Window* { return _window; }

  /**
   * Initialize game logic.
   */
  auto Init(std::string_view config) -> bool;

  void Update(double delta);

  void Draw(class SDL_Renderer* renderer);

  auto GetPlayerObject() -> Object*;

  [[nodiscard]] auto GetMaze() const -> Maze const* { return _maze; }

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

  [[nodiscard]] auto DebugDraw() const -> bool { return _debug_draw; }

  [[nodiscard]] auto TruncateLocation() const -> bool {
    return _truncate_location;
  }

  auto OnKeyDown(SDL_KeyboardEvent const& event) -> SDL_AppResult;

  void IncFrame() { ++_frame_number; }

private:
  GameInstance() = default;
  auto InitPlayer(std::string_view texture_path) -> bool;
  auto InitMaze() -> bool;

  std::string _title;
  int _width = 0;
  int _height = 0;

  SDL_Renderer* _renderer = nullptr;
  SDL_Window* _window = nullptr;

  bool _debug_draw = false;
  bool _truncate_location = false;

  Timer _timer;
  long long _frame_number = 0;

  Object* _player = nullptr;
  Maze* _maze = nullptr;
};
