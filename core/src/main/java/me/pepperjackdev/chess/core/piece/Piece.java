package me.pepperjackdev.chess.core.piece;

import me.pepperjackdev.chess.core.Side;

public sealed abstract class Piece
    permits Pawn, Knight, Bishop, Rook, Queen, King {

    private final Side side;
    private final char symbol;

    public Piece(Side side, char symbol) {
        this.side = side;
        this.symbol = symbol;
    }

    public Side getSide() {
        return side;
    }

    public char getSymbol() {
        return switch (side) {
            case WHITE -> Character.toUpperCase(symbol);
            case BLACK -> Character.toLowerCase(symbol);
        };
    }

    @Override
    public String toString() {
        return String.valueOf(getSymbol());
    }
}
