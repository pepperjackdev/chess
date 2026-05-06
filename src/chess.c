#include "chess.h"

Piece piece_of(PieceType type, PieceSide side) {
    return type | side;
}

PieceType type_of(Piece piece) {
    return piece & 0b00000111;
}

PieceSide side_of(Piece piece) {
    return piece & 0b00001000;
}

void move(Move move, State *state) {
    if (move.source < 0 || move.source > 64 || move.target < 0 || move.target > 64) return;
    Piece piece = state->placement[move.source];
    state->placement[move.source] = 0;
    state->placement[move.target] = piece;
}
