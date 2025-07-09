package me.pepperjackdev.chess.core.data.state;

import me.pepperjackdev.chess.core.Side;
import me.pepperjackdev.chess.core.position.Position;
import me.pepperjackdev.chess.core.data.state.castling.CastlingRights;
import me.pepperjackdev.chess.core.data.state.placement.Placement;

public interface State {
    Placement getPlacement();
    Side getActiveColor();
    CastlingRights getCastlingRights();
    Position getEnPassantTargetSquare();
    int getHalfMoveClock();
    int getFullMoveClock();
}
