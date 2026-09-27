#include "maze.hh"

#include "SDL3/SDL_log.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "base/game_instance.hh"
#include "base/math.hh"
#include "game/object.hh"
#include "global.hh"

#include <cmath>
#include <vector>

namespace {
constexpr int MAZE_COLUMN = 28;
constexpr int MAZE_ROW = 31;
constexpr int TILE_SIZE = 8;
constexpr int SHEET_COLUMN = 16;
constexpr int TILE_MARGIN = 1;
constexpr int TILE_START_X = 224;
constexpr int MAZE_WIDTH = TILE_SIZE * MAZE_COLUMN;
constexpr int MAZE_HEIGHT = TILE_SIZE * MAZE_ROW;
// clang-format off
const std::vector<int> tiles = {
    01, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 43, 42, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 00,
    03, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 25, 24, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 02,
    03, -1, 23, 14, 14, 22, -1, 23, 14, 14, 14, 22, -1, 25, 24, -1, 23, 15, 15, 15, 22, -1, 23, 15, 15, 22, -1, 02,
    03, -1, 25, -1, -1, 24, -1, 25, -1, -1, -1, 24, -1, 25, 24, -1, 25, -1, -1, -1, 24, -1, 25, -1, -1, 24, -1, 02,
    03, -1, 27, 20, 20, 26, -1, 27, 20, 20, 20, 26, -1, 27, 26, -1, 27, 21, 21, 21, 26, -1, 27, 21, 21, 26, -1, 02,
    03, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 02,
    03, -1, 23, 14, 14, 22, -1, 23, 22, -1, 23, 14, 14, 14, 15, 15, 15, 22, -1, 23, 22, -1, 23, 15, 15, 22, -1, 02,
    03, -1, 27, 20, 20, 26, -1, 25, 24, -1, 27, 20, 20, 35, 34, 21, 21, 26, -1, 25, 24, -1, 27, 21, 21, 26, -1, 02,
    03, -1, -1, -1, -1, -1, -1, 25, 24, -1, -1, -1, -1, 25, 24, -1, -1, -1, -1, 25, 24, -1, -1, -1, -1, -1, -1, 02,
    05, 12, 12, 12, 12, 22, -1, 25, 36, 14, 14, 22, -1, 25, 24, -1, 23, 15, 15, 37, 24, -1, 23, 13, 13, 13, 13, 04,
    -1, -1, -1, -1, -1, 03, -1, 25, 34, 20, 20, 26, -1, 27, 26, -1, 27, 21, 21, 35, 24, -1, 02, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, 03, -1, 25, 24, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 25, 24, -1, 02, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, 03, -1, 25, 24, -1, 29, 12, 33, 38, 39, 32, 13, 28, -1, 25, 24, -1, 02, -1, -1, -1, -1, -1,
    10, 10, 10, 10, 10, 26, -1, 27, 26, -1, 02, -1, -1, -1, -1, -1, -1, 03, -1, 27, 26, -1, 27, 11, 11, 11, 11, 11,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 02, -1, -1, -1, -1, -1, -1, 03, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    12, 12, 12, 12, 12, 22, -1, 23, 22, -1, 02, -1, -1, -1, -1, -1, -1, 03, -1, 23, 22, -1, 23, 13, 13, 13, 13, 13,
    -1, -1, -1, -1, -1, 03, -1, 25, 24, -1, 31, 10, 10, 10, 11, 11, 11, 30, -1, 25, 24, -1, 02, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, 03, -1, 25, 24, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 25, 24, -1, 02, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, 03, -1, 25, 24, -1, 23, 14, 14, 14, 15, 15, 15, 22, -1, 25, 24, -1, 02, -1, -1, -1, -1, -1,
    01, 10, 10, 10, 10, 26, -1, 27, 26, -1, 27, 20, 20, 35, 34, 21, 21, 26, -1, 27, 26, -1, 27, 11, 11, 11, 11, 00,
    03, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 25, 24, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 02,
    03, -1, 23, 14, 14, 22, -1, 23, 14, 14, 14, 22, -1, 25, 24, -1, 23, 15, 15, 15, 22, -1, 23, 15, 15, 22, -1, 02,
    03, -1, 27, 20, 35, 24, -1, 27, 20, 20, 20, 26, -1, 27, 26, -1, 27, 21, 21, 21, 26, -1, 25, 34, 21, 26, -1, 02,
    03, -1, -1, -1, 25, 24, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 25, 24, -1, -1, -1, 02,
    07, 14, 22, -1, 25, 24, -1, 23, 22, -1, 23, 14, 14, 14, 15, 15, 15, 22, -1, 23, 22, -1, 25, 24, -1, 23, 15, 06,
     9, 20, 26, -1, 27, 26, -1, 25, 24, -1, 27, 20, 20, 35, 34, 21, 21, 26, -1, 25, 24, -1, 27, 26, -1, 27, 21,  8,
    03, -1, -1, -1, -1, -1, -1, 25, 24, -1, -1, -1, -1, 25, 24, -1, -1, -1, -1, 25, 24, -1, -1, -1, -1, -1, -1, 02,
    03, -1, 23, 14, 14, 14, 14, 37, 36, 14, 14, 22, -1, 25, 24, -1, 23, 15, 15, 37, 36, 15, 15, 15, 15, 22, -1, 02,
    03, -1, 27, 20, 20, 20, 20, 20, 20, 20, 20, 26, -1, 27, 26, -1, 27, 21, 21, 21, 21, 21, 21, 21, 21, 26, -1, 02,
    03, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 02,
    05, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 04,
};
// clang-format on

void SetTileSrcLoc(int group, int index, SDL_FRect* loc) {
  int row = group * 3 + index / SHEET_COLUMN;
  int column = index % SHEET_COLUMN;
  // tiles start at (224, 0), each tile is 8 * 8 pixels, but has
  // one-pixel margin on its left and bottom.
  int x = TILE_START_X + column * (TILE_SIZE + TILE_MARGIN) + TILE_MARGIN;
  int y = 0 + row * (TILE_SIZE + TILE_MARGIN);
  loc->x = x;
  loc->y = y;
}

void SetTileDstLoc(int index, SDL_FRect* loc) {
  int row = index / MAZE_COLUMN;
  int column = index % MAZE_COLUMN;
  int x = TILE_SIZE * column;
  int y = TILE_SIZE * row;
  loc->x = x;
  loc->y = y;
}

void ComputeNearestTile(int x, int y, int* row, int* column) {
  *row = y / TILE_SIZE;
  *column = x / TILE_SIZE;
}

auto IsTileWalkable(int row, int column) -> bool {
  bool ret = false;
  if (0 <= column && column < MAZE_COLUMN && 0 <= row && row < MAZE_ROW) {
    int index = row * MAZE_COLUMN + column;
    if (0 <= index && index <= tiles.size()) {
      ret = tiles[index] == -1;
    }
  }
  return ret;
}

auto ComputeTileCenter(int row, int column) -> Position {
  return {TILE_SIZE / 2.0F + column * TILE_SIZE,
          TILE_SIZE / 2.0F + row * TILE_SIZE};
}

auto MoveTowards(float src, float dst, float delta) -> float {
  if (src < dst) {
    src += delta;
    if (src > dst) {
      src = dst;
    }
  }
  else {
    src -= delta;
    if (src < dst) {
      src = dst;
    }
  }
  return src;
}
} // namespace

auto Maze::Init() -> bool {
  return _sprite_sheet.Init("assets/sprites/maze_fix.png");
}

void Maze::Draw(SDL_Renderer* renderer) {
  SDL_FRect src;
  src.h = src.w = TILE_SIZE;
  SDL_FRect dst;
  dst.h = dst.w = TILE_SIZE;
  for (int i = 0; i < tiles.size(); ++i) {
    int tile_index = tiles[i];
    SetTileDstLoc(i, &dst);
    if (tile_index >= 0) {
      SetTileSrcLoc(1, tile_index, &src);
      SDL_RenderTexture(renderer, _sprite_sheet.GetTexture(), &src, &dst);
      if (gGameInstance->DebugDraw()) {
        SDL_SetRenderDrawColorFloat(renderer, 1, 0, 0, 1);
        SDL_RenderRect(renderer, &dst);
      }
    }
    else {
      if (gGameInstance->DebugDraw()) {
        SDL_SetRenderDrawColorFloat(renderer, 0, 1, 0, 1);
        SDL_RenderRect(renderer, &dst);
      }
    }
  }
  if (gGameInstance->TruncateLocation()) {
    SDL_SetRenderDrawColorFloat(renderer, 0, 1, 0, 1);
    SDL_RenderPoint(renderer, MAZE_WIDTH / 2, MAZE_HEIGHT / 2);
  }
}

auto Maze::CanMove(Position& src, Direction const& dir, float delta) const
    -> bool {
  Position old_src = src;
  src.MoveAlongDirection(dir, delta);
  // round trip if we are moving across the boundary
  if (old_src.X >= 0 && src.X < 0 ||
      old_src.X < MAZE_WIDTH && src.X >= MAZE_WIDTH) {
    float new_x = modf(src.X, MAZE_WIDTH);
    src.X = new_x;

    // NOTE: If rounding the position to integers, we have to return here after
    // teleporting, because rounding would produce undesired tile result after
    // teleporting.
    if (!gGameInstance->TruncateLocation()) {
      return true;
    }
  }
  // NOTE: Determine the current tile. We may truncating or rounding to
  // integer. Rounding produces undesired result after teleporting. Not sure
  // about how these two solutions affect movement in general, though.
  int x = gGameInstance->TruncateLocation() ? src.X : std::lround(src.X);
  int y = gGameInstance->TruncateLocation() ? src.Y : std::lround(src.Y);
  // find the nearest tile
  int row = 0;
  int column = 0;
  ComputeNearestTile(x, y, &row, &column);
  bool succeed = IsTileWalkable(row, column);
  int next_row = row + dir.Y;
  int next_column = column + dir.X;
  next_column = mod(next_column, MAZE_COLUMN);
  bool IsNextWalkable = IsTileWalkable(next_row, next_column);
  Position this_center = ComputeTileCenter(row, column);
  // pull back if next is not walkable and we are moving past the current center
  if (!IsNextWalkable) {
    if (dir.X != 0 && dir.X * (this_center.X - src.X) <= 0) {
      src.X = this_center.X;
      succeed = false;
    }
    else if (dir.Y != 0 && dir.Y * (this_center.Y - src.Y) <= 0) {
      src.Y = this_center.Y;
      succeed = false;
    }
  }

  if (succeed) {
    // if we are moving on X axis, then pull back on Y. Vice versa.
    if (dir.X != 0) {
      src.Y = MoveTowards(src.Y, this_center.Y, delta);
    }
    else if (dir.Y != 0) {
      src.X = MoveTowards(src.X, this_center.X, delta);
    }
  }
  return succeed;
}

void Maze::SetToStart(Object* obj) {
  obj->SetPosition({14 * TILE_SIZE, 4 + 23 * TILE_SIZE});
}
