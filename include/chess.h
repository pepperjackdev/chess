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

typedef enum : uint8_t {
  PIECE_HAS_BEEN_MOVED = 0b00010000,
} PieceFlags;

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

typedef enum : uint8_t {
  SQUARE_EMPTY          = 0b00000001,
  SQUARE_OCCUPIED_ALLY  = 0b00000010,
  SQUARE_OCCUPIED_ENEMY = 0b00000100,
  SQUARE_EN_PASSANT     = 0b00001000,
  PIECE_NEVER_MOVED     = 0b00010000
} MoveCondition;

typedef struct {
  Array directions;
  int limit;
  MoveCondition condition;
} MovePattern;

#define MOVE_PATTERN(NAME, limit, status, ...) \
  static MoveDirection NAME##_MOVE_DIRECTIONS[] = {__VA_ARGS__}; \
  static MovePattern NAME##_MOVE_PATTERN = (MovePattern){ \
    ARRAY_FROM_C_ARRAY(NAME##_MOVE_DIRECTIONS), \
    limit, \
    status \
  }

#define REGISTER_PIECE_MOVE_PATTERNS(NAME, ...) \
  static MovePattern *NAME##_MOVE_PATTERNS[] = { \
    __VA_ARGS__ \
  }

// KING
MOVE_PATTERN(KING, 1, SQUARE_EMPTY | SQUARE_OCCUPIED_ENEMY,
  NORTH, NORTH_EAST, 
  EAST, SOUTH_EAST, 
  SOUTH, SOUTH_WEST, 
  WEST, NORTH_WEST,
);

REGISTER_PIECE_MOVE_PATTERNS(KING, &KING_MOVE_PATTERN);

// QUEEN
MOVE_PATTERN(QUEEN, -1, SQUARE_EMPTY | SQUARE_OCCUPIED_ENEMY,
  NORTH, NORTH_EAST, 
  EAST, SOUTH_EAST, 
  SOUTH, SOUTH_WEST, 
  WEST, NORTH_WEST,
);

REGISTER_PIECE_MOVE_PATTERNS(QUEEN, &QUEEN_MOVE_PATTERN);

// BISHOP
MOVE_PATTERN(BISHOP, -1, SQUARE_EMPTY | SQUARE_OCCUPIED_ENEMY, 
  NORTH_EAST, SOUTH_EAST, SOUTH_WEST, NORTH_WEST
);

REGISTER_PIECE_MOVE_PATTERNS(BISHOP, &BISHOP_MOVE_PATTERN);

// KNIGHT
MOVE_PATTERN(KNIGHT, 1, SQUARE_EMPTY | SQUARE_OCCUPIED_ENEMY, 
  NORTH_NORTH_EAST, EAST_NORTH_EAST,
  EAST_SOUTH_EAST, SOUTH_SOUTH_EAST,
  SOUTH_SOUTH_WEST, WEST_SOUTH_WEST,
  WEST_NORTH_WEST, NORTH_NORTH_WEST,
);

REGISTER_PIECE_MOVE_PATTERNS(KNIGHT, &KNIGHT_MOVE_PATTERN);

// ROOK
MOVE_PATTERN(ROOK, -1, SQUARE_EMPTY | SQUARE_OCCUPIED_ENEMY, 
  NORTH, EAST, SOUTH, WEST
);
 
REGISTER_PIECE_MOVE_PATTERNS(ROOK, &ROOK_MOVE_PATTERN);

// PAWN
MOVE_PATTERN(PAWN_FORWARD, 1, SQUARE_EMPTY, 
  NORTH
);

MOVE_PATTERN(PAWN_FORWARD_FIRST, 1, SQUARE_EMPTY | PIECE_NEVER_MOVED,
  NORTH * 2 // Move of two square...
);

MOVE_PATTERN(PAWN_CAPTURE, 1, SQUARE_OCCUPIED_ENEMY,
  NORTH_EAST, NORTH_WEST
);

MOVE_PATTERN(PAWN_EN_PASSANT, 1, SQUARE_EN_PASSANT,
  NORTH_WEST, NORTH_EAST
);

REGISTER_PIECE_MOVE_PATTERNS(PAWN, 
  &PAWN_FORWARD_MOVE_PATTERN,
  &PAWN_FORWARD_FIRST_MOVE_PATTERN,
  &PAWN_CAPTURE_MOVE_PATTERN,
  &PAWN_EN_PASSANT_MOVE_PATTERN
);

static Move LEGAL_MOVES_CACHE_C_ARRAY[256];
static Array LEGAL_MOVES_CACHE = (Array){
  LEGAL_MOVES_CACHE_C_ARRAY,
  0,
  CHESS_MAX_NUMBER_OF_MOVES
};

void generate_legal_moves(Array *moves, State *state);
void move(Move move, State *state);