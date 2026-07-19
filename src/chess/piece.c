#include "chess/piece.h"

Piece piece_new(PieceType type, PieceSide side) {
    return type | side;
}

PieceType piece_get_type(Piece piece) {
    return piece & 0b00000111;
}

PieceSide piece_get_side(Piece piece) {
    return piece & 0b00001000;
}
