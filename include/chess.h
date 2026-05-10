#pragma once

#include <stdint.h>
#include "utils/array.h"

#define CHESS_MAX_NUMBER_OF_MOVES 256

typedef enum : uint8_t {
  TYPE_NULL   = 0b00000000,
  TYPE_KING   = 0b00000001,
  TYPE_QUEEN  = 0b00000010,
  TYPE_BISHOP = 0b00000011,
  TYPE_KNIGHT = 0b00000100,
  TYPE_ROOK   = 0b00000101,
  TYPE_PAWN   = 0b00000110
} PieceType;

typedef enum : uint8_t { 
  SIDE_WHITE = 0b00000000, 
  SIDE_BLACK = 0b00001000 
} PieceSide;

typedef uint8_t Piece;

Piece piece_of(PieceType type, PieceSide side);
PieceType type_of(Piece piece);
PieceSide side_of(Piece piece);

typedef uint8_t Board[64];

typedef enum : uint8_t {
  CASTLING_BLACK_KING_SIDE  = 0b00000001,
  CASTLING_BLACK_QUEEN_SIDE = 0b00000010,
  CASTLING_WHITE_KING_SIDE  = 0b00000100,
  CASTLING_WHITE_QUEEN_SIDE = 0b00001000,
} CastlingRights;

typedef struct {
  Board placement;
  PieceSide active_side;
  CastlingRights castling_rights;
  int en_passant_index;
  int halfmove_clock;
  int fullmove_clock;
} State;

typedef struct {
  int source;
  int target;
} Move;

bool compare(Move m1, Move m2);

typedef enum {
  NORTH            = -8,
  NORTH_NORTH_EAST = -15,
  NORTH_EAST       = -7,
  EAST_NORTH_EAST  = -6,
  EAST             = 1,
  EAST_SOUTH_EAST  = 10,
  SOUTH_EAST       = 9,
  SOUTH_SOUTH_EAST = 17,
  SOUTH            = 8,
  SOUTH_SOUTH_WEST = 15,
  SOUTH_WEST       = 7,
  WEST_SOUTH_WEST  = 6,
  WEST             = -1,
  WEST_NORTH_WEST  = -10,
  NORTH_WEST       = -9,
  NORTH_NORTH_WEST = -17
} MoveDirection;

typedef enum {
  SQUARE_EMPTY,
  SQUARE_OCCUPIED_ALLY,
  SQUARE_OCCUPIED_ENEMY,
  SQUARE_EMPTY_OR_OCCUPIED_BY_ENEMY
} SquareStatus;

typedef struct {
  Array directions;
  int limit;
  SquareStatus status;
} MovePattern;

#define MOVE_PATTERN(NAME, limit, status, ...) \
  static MoveDirection NAME##_MOVE_DIRECTIONS[] = {__VA_ARGS__}; \
  static MovePattern NAME##_MOVE_PATTERN = (MovePattern){ \
    ARRAY_FROM_C_ARRAY(NAME##_MOVE_DIRECTIONS), \
    limit, \
    status \
  }

MOVE_PATTERN(ROOK, -1, SQUARE_EMPTY_OR_OCCUPIED_BY_ENEMY, 
  NORTH, EAST, SOUTH, WEST
);

static MovePattern *ROOK_MOVE_PATTERNS[] = {
  &ROOK_MOVE_PATTERN,
};

static Move LEGAL_MOVES_CACHE_C_ARRAY[256];
static Array LEGAL_MOVES_CACHE = (Array){
  LEGAL_MOVES_CACHE_C_ARRAY,
  0,
  CHESS_MAX_NUMBER_OF_MOVES
};

void generate_legal_moves(Array *moves, State *state);
void move(Move move, State *state);