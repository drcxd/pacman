#include "maze.hh"

#include "SDL3/SDL_log.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
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
  // TODO: when implementing the teleport feature, we need to change this.
  if (0 <= column && column < MAZE_COLUMN && 0 <= row && row < MAZE_ROW) {
    int index = row * MAZE_COLUMN + column;
    if (0 <= index && index <= tiles.size()) {
      ret = tiles[index] == -1;
    }
  }
  return ret;
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
    if (tile_index >= 0) {
      SetTileSrcLoc(1, tile_index, &src);
      SetTileDstLoc(i, &dst);
      SDL_RenderTexture(renderer, _sprite_sheet.GetTexture(), &src, &dst);
#if DEBUG_DRAW
      SDL_SetRenderDrawColorFloat(renderer, 0, 1, 0, 1);
      SDL_RenderRect(renderer, &dst);
#endif
    }
  }
}

auto Maze::CanMove(Position const& src, Direction const& dir) const -> bool {
  // determine the current tile:
  int x = std::lround(src.X);
  int y = std::lround(src.Y);
  // find the nearest tile
  int row = 0;
  int column = 0;
  ComputeNearestTile(x, y, &row, &column);
  int next_row = row + dir.Y;
  int next_column = column + dir.X;
  bool succeed = IsTileWalkable(next_row, next_column);
  return succeed;
}

void Maze::SetToStart(Object* obj) {
  obj->SetPosition({4 + 13 * TILE_SIZE, 4 + 23 * TILE_SIZE});
}
