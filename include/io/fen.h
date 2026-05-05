#pragma once

#include "chess.h"

void parse_fen_into_board(char *fen, int index, State *state);
void parse_fen_into_active_color(char *fen, int index, State *state);
void parse_fen_into_castling_availability(char *fen, int index, State *state);
void parse_fen_into_en_passant_target_square(char *fen, int index, State *state);
void parse_fen_into_halfmove_clock(char *fen, int index, State *state);
void parse_fen_into_fullmove_clock(char *fen, int index, State *state);
void parse_fen_into_state(char *fen, State *state);
