#include "chess/io/fen.h"

#include "stdio.h"
#include "string.h"

void parse_fen_into_board(char *fen, int index, State *state) {    
    // Clearing the Board
    memset(state->placement, 0, 64);

    for (int fen_index = 0, rank = 0, file = 0; 
        fen[fen_index] != '\0' && fen[fen_index] != ' '; 
        fen_index++) {

        char symbol = fen[fen_index];

        if (symbol == '/') {
            rank++;
            file = 0;
            continue;
        }
        
        if (symbol >= '1' && symbol <= '8') {
            file += symbol - '0';
            continue;
        }

        PieceType type = 0;
        PieceSide side = PIECE_SIDE_WHITE;

        switch (symbol) {
            case 'P': side = PIECE_SIDE_WHITE; type = PIECE_TYPE_PAWN;   break;
            case 'N': side = PIECE_SIDE_WHITE; type = PIECE_TYPE_KNIGHT; break;
            case 'B': side = PIECE_SIDE_WHITE; type = PIECE_TYPE_BISHOP; break;
            case 'R': side = PIECE_SIDE_WHITE; type = PIECE_TYPE_ROOK;   break;
            case 'Q': side = PIECE_SIDE_WHITE; type = PIECE_TYPE_QUEEN;  break;
            case 'K': side = PIECE_SIDE_WHITE; type = PIECE_TYPE_KING;   break;

            case 'p': side = PIECE_SIDE_BLACK; type = PIECE_TYPE_PAWN;   break;
            case 'n': side = PIECE_SIDE_BLACK; type = PIECE_TYPE_KNIGHT; break;
            case 'b': side = PIECE_SIDE_BLACK; type = PIECE_TYPE_BISHOP; break;
            case 'r': side = PIECE_SIDE_BLACK; type = PIECE_TYPE_ROOK;   break;
            case 'q': side = PIECE_SIDE_BLACK; type = PIECE_TYPE_QUEEN;  break;
            case 'k': side = PIECE_SIDE_BLACK; type = PIECE_TYPE_KING;   break;

            default:
                fprintf(stderr, 
                    "Warning: Invalid FEN character '%c'\n", symbol);
                continue;
        }

        if (type != 0 && file < 8) {
            int square = rank * 8 + file;
            state->placement[square] = piece_new(type, side);
            file++;
        }
    }
}

void parse_fen_into_active_color(char *fen, int index, State *state) {
    PieceSide active_color;
    switch (fen[index]) {
        case 'w': active_color = PIECE_SIDE_WHITE; break;
        case 'b': active_color = PIECE_SIDE_BLACK; break;
        
        default:
            fprintf(stderr,
            "Warning: Invalid FEN character '%c'\n", fen[index]);
    }
    state->active_side=active_color;
}

void parse_fen_into_castling_availability(char *fen, int index, State *state) {
    Castling castling = 0x00;
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
    state->castling = castling;
}

void parse_fen_into_en_passant_target_square(char *fen, int index, State *state) {
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
    state->en_passant_index = target_square;
}

void parse_fen_into_halfmove_clock(char *fen, int index, State *state) {
    int halfmove_clock = 0;
    for (int i = index; fen[i] != ' '; i++) {
        halfmove_clock = halfmove_clock * 10 + (fen[i] - '0');
    }
    state->halfmove_clock = halfmove_clock;
}

void parse_fen_into_fullmove_clock(char *fen, int index, State *state) {
    int fullmove_clock = 0;
    for (int i = index; fen[i] != '\0'; i++) {
        fullmove_clock = fullmove_clock * 10 + (fen[i] - '0');
    }
    state->fullmove_clock = fullmove_clock;
}

void parse_fen_into_state(char *fen, State *state) {
    if (fen == NULL || state == NULL) return;

    // Loaders
    void (*loader[])(char*, int, State*) = {
        parse_fen_into_board,
        parse_fen_into_active_color,
        parse_fen_into_castling_availability,
        parse_fen_into_en_passant_target_square,
        parse_fen_into_halfmove_clock,
        parse_fen_into_fullmove_clock
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
