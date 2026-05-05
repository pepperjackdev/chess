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
    return piece & 0b00001000;
}

void load_fen_into_board(char *fen, int index, State *state) {    
    // Clearing the Board
    memset(state->piece_placement_data, 0, 64);

    for (int fen_index = 0, rank = 0, file = 0; 
        fen[fen_index] != '\0' && fen[fen_index] != ' '; 
        fen_index++) {

        char symbol = fen[fen_index];

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

        // Determining piece
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
                    "Warning: Invalid FEN character '%c'\n", symbol);
                continue;
        }

        // Loading determined piece into board
        if (type != 0 && file < 8) {
            int square = rank * 8 + file;
            state->piece_placement_data[square] = piece_of(type, side);
            file++;
        }
    }
}

void load_fen_into_active_color(char *fen, int index, State *state) {
    PieceSide active_color;
    switch (fen[index]) {
        case 'w': active_color = SIDE_WHITE; break;
        case 'b': active_color = SIDE_BLACK; break;
        
        default:
            fprintf(stderr,
            "Warning: Invalid FEN character '%c'\n", fen[index]);
    }
    state->active_color=active_color;
}

void load_fen_into_castling_availability(char *fen, int index, State *state) {
    CastlingRights castling = 0x00;
    if (fen[index] != '-') {
        for (int i = index; fen[i] != ' '; i++) {
            switch (fen[i]) {
                case 'K': castling |= CASTLING_WHITE_KING_SIDE; break;
                case 'Q': castling |= CASTLING_WHITE_QUEEN_SIDE; break;
                case 'k': castling |= CASTLING_BLACK_KING_SIDE; break;
                case 'q': castling |= CASTLING_BLACK_QUEEN_SIDE; break;
                default:
                    fprintf(stderr, 
                        "Warning: Invalid FEN character '%c", fen[i]);
            }
        }
    }
    state->castling_availability = castling;
}

void load_fen_into_en_passant_target_square(char *fen, int index, State *state) {
    int target_square = -1; // No target square
    if (fen[index] != '-') {
        int rank, file;

        if (fen[index + 1] >= '1' && fen[index + 1] <= '8') {
            rank = fen[index + 1] - '1';
        }

        if (fen[index] >= 'a' && fen[index] <= 'h') {
            file = fen[index] - 'a';
        }

        target_square = rank * 8 + file;
    }
    state->en_passant_target_square = target_square;
}

void load_fen_into_halfmove_clock(char *fen, int index, State *state) {
    int halfmove_clock = 0;
    for (int i = index; fen[i] != ' '; i++) {
        halfmove_clock = halfmove_clock * 10 + (fen[i] - '0');
    }
    state->halfmove_clock = halfmove_clock;
}

void load_fen_into_fullmove_clock(char *fen, int index, State *state) {
    int fullmove_clock = 0;
    for (int i = index; fen[i] != '\0'; i++) {
        fullmove_clock = fullmove_clock * 10 + (fen[i] - '0');
    }
    state->fullmove_clock = fullmove_clock;
}

void load_fen_into_state(char *fen, State *state) {
    if (fen == NULL || state == NULL) return;

    // Loaders
    void (*loader[])(char*, int, State*) = {
        load_fen_into_board,
        load_fen_into_active_color,
        load_fen_into_castling_availability,
        load_fen_into_en_passant_target_square,
        load_fen_into_halfmove_clock,
        load_fen_into_fullmove_clock
    };

    // Reading FEN string
    for (int fen_index = 0, loader_index = 0;
        fen[fen_index] != '\0';
        fen_index++) {
        if (fen_index == 0 || fen[fen_index] == ' ') {
            loader[loader_index++](fen, ++fen_index, state);
        }
    }
}