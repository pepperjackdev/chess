#include "chess.h"

#include <string.h>
#include <stdio.h>

Piece piece_of(PieceType type, PieceSide side) {
    return type | side;
}

PieceType type_of(Piece piece) {
    return piece & 0b00000111;
}

PieceSide side_of(Piece piece) {
    return piece & SIDE_BLACK;
}

void load_fen_into_board(char *fen, Board *board) {
    if (fen == NULL || board == NULL) return;
    // Clearing the Board
    memset(*board, 0, 64);
    
    // Parsing
    int rank = 0;
    int file = 0;

    for (int i = 0; fen[i] != '\0' && fen[i] != ' '; i++) {
        char symbol = fen[i];
        // End of Rank
        if (symbol == '/') {
            rank++;
            file = 0;
            continue;
        }
        // Empty spaces
        if (symbol >= '1' && symbol <= '8') {
            file += symbol - '0';
            continue;
        }

        // Piece
        PieceType type = 0;
        PieceSide side = SIDE_WHITE;

        switch (symbol) {
            case 'P': side = SIDE_WHITE; type = TYPE_PAWN;   break;
            case 'N': side = SIDE_WHITE; type = TYPE_KNIGHT; break;
            case 'B': side = SIDE_WHITE; type = TYPE_BISHOP; break;
            case 'R': side = SIDE_WHITE; type = TYPE_ROOK;   break;
            case 'Q': side = SIDE_WHITE; type = TYPE_QUEEN;  break;
            case 'K': side = SIDE_WHITE; type = TYPE_KING;   break;

            case 'p': side = SIDE_BLACK; type = TYPE_PAWN;   break;
            case 'n': side = SIDE_BLACK; type = TYPE_KNIGHT; break;
            case 'b': side = SIDE_BLACK; type = TYPE_BISHOP; break;
            case 'r': side = SIDE_BLACK; type = TYPE_ROOK;   break;
            case 'q': side = SIDE_BLACK; type = TYPE_QUEEN;  break;
            case 'k': side = SIDE_BLACK; type = TYPE_KING;   break;

            default:
                fprintf(stderr, 
                    "Warning: Invalid FEN character '%c'\n", 
                    symbol);
                continue;
        }

        // Loading determied piece into board
        if (type != 0 && file < 8) {
            int square = rank * 8 + file;
            (*board)[square] = piece_of(type, side);
            file++;
        }
    }
}