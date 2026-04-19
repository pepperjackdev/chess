#include "chess.h"

#include <raylib.h>
#include <stdio.h>

Piece piece_of(PieceType type, PieceSide side) { 
  return type | side; 
}

PieceType type_of(Piece piece) { 
  return piece & 0b00000111; 
}

PieceSide side_of(Piece piece) { 
  return piece & 0b00001000; 
}

// FIXME: tmp. implementation
void load_fen_into_board(char *fen, Board *board) {
  // Clearing board
  for (int i = 0; i < 65; i++) {
    (*board)[i] = 0;
  }
  // Loading FEN content into board
  for (int fen_index = 0, board_index = 0; 
      fen[fen_index] != '\0' && board_index < 64; 
      fen_index++) {
    char symbol = fen[fen_index];
    
    if (symbol == '/') continue;
    
    if (symbol >= '1' && symbol <= '8') {
      board_index += symbol - '0';
      continue;
    }
    
    PieceSide side;
    if (symbol >= 'A' && symbol <= 'Z') {
      side = SIDE_WHITE;
    } else if (symbol >= 'a' && symbol <= 'z') {
      side = SIDE_BLACK;
    }

    PieceType type;
    switch (symbol) {
      case 'K':
      case 'k':
        type = TYPE_KING;
        break;
      case 'Q':
      case 'q':
        type = TYPE_QUEEN;
        break;
      case 'B':
      case 'b':
        type = TYPE_BISHOP;
        break;
      case 'N':
      case 'n':
        type = TYPE_KNIGHT;
        break;
      case 'R':
      case 'r':
        type = TYPE_ROOK;
        break;
      case 'P':
      case 'p':
        type = TYPE_PAWN;
        break;
      default:
        fprintf(stderr, "Invalid symbol");
    }

    (*board)[board_index++] = piece_of(type, side);
  }
} 
