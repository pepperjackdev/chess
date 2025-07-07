package me.pepperjackdev.chess.core.game.data.state.placement;

import me.pepperjackdev.chess.core.game.piece.Piece;
import me.pepperjackdev.chess.core.game.position.Position;

import java.util.Optional;

public interface Placement {
    Size getSize();
    Optional<Piece> getPiece(Position position);
}
