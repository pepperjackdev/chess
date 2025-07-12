package me.pepperjackdev.chess.core.data.state.placement;

import me.pepperjackdev.chess.core.piece.Piece;
import me.pepperjackdev.chess.core.position.Position;

import java.util.Map;
import java.util.Optional;

public class MutablePlacement
    implements Placement {

    private final Size size;
    private final Piece[][] pieces;

    public MutablePlacement(Size size, Map<Position, Piece> pieces) {
        this.size = size;
        this.pieces = new Piece[size.rows()][size.columns()];
        for (var entry: pieces.entrySet()) {
            var _ = setPiece(entry.getKey(), entry.getValue());
        }
    }

    public MutablePlacement(Size size) {
        this(size, Map.of());
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
