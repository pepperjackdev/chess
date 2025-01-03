package me.pepperjackdev.chess.core.piece;

import java.util.Objects;

public class Piece {
    private PieceType type;
    private final PieceSide side;

    public Piece(PieceType type, PieceSide side) {
        this.type = type;
        this.side = side;
    }

    public PieceType getType() {
        return type;
    }

    public void setType(PieceType type) {
        this.type = type;
    }

    public PieceSide getSide() {
        return side;
    }

    @Override
    public boolean equals(Object o) {
        if (o == null || getClass() != o.getClass()) return false;
        Piece piece = (Piece) o;
        return type == piece.type && side == piece.side;
    }

    @Override
    public int hashCode() {
        return Objects.hash(type, side);
    }
}
