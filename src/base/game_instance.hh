#pragma once

#include <string_view>

class Object;

class GameInstance
{
public:
  GameInstance(std::string_view title, int width, int height);
  auto GetRenderer() -> class SDL_Renderer* { return _renderer; }
  auto GetWindow() -> class SDL_Window* { return _window; }
  auto IsError() -> bool { return _error; }
  auto GetPlayerObject() -> Object*;
  auto InitPlayer(std::string_view texture_path) -> bool;
private:
  SDL_Renderer* _renderer = nullptr;
  SDL_Window* _window = nullptr;
  std::string_view _title;
  int _width = 640;
  int _height = 480;
  bool _error = false;

  Object* _player = nullptr;
};
