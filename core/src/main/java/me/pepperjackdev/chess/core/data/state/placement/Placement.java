package me.pepperjackdev.chess.core.data.state.placement;

import me.pepperjackdev.chess.core.piece.Piece;
import me.pepperjackdev.chess.core.position.Position;

import java.util.Optional;

public interface Placement {
    Size getSize();
    Optional<Piece> getPiece(Position position);
}
