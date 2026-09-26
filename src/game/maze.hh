#pragma once

#include "base/texture.hh"
#include "base/types.hh"

class Maze {
public:
  auto Init() -> bool;

  void Draw(class SDL_Renderer* renderer);

  /**
   * Return if an object can move `delta` units from `src` along `dir`. If
   * succeed, the corrected destination is passed back through `src`.
   */
  [[nodiscard]] auto CanMove(Position& src, Direction const& dir,
                             float delta) const -> bool;

  /**
   * Set `obj` to the player start location.
   */
  void SetToStart(class Object* obj);

private:
  Texture _sprite_sheet;
};
