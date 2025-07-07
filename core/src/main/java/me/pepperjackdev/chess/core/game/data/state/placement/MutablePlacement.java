package me.pepperjackdev.chess.core.game.data.state.placement;

import me.pepperjackdev.chess.core.game.piece.Piece;
import me.pepperjackdev.chess.core.game.position.Position;

import java.util.Optional;

public class MutablePlacement
    implements Placement {

    private final Size size;
    private final Piece[][] pieces;

    public MutablePlacement(Size size) {
        this.size = size;
        this.pieces = new Piece[size.rows()][size.columns()];
    }

    @Override
    public Size getSize() {
        return size;
    }

    @Override
    public Optional<Piece> getPiece(Position position) {
        return Optional.ofNullable(pieces[position.row()][position.column()]);
    }

    public Optional<Piece> setPiece(Position position, Piece piece) {
        Optional<Piece> old = getPiece(position);
        pieces[position.row()][position.column()] = piece;
        return old;
    }
}
