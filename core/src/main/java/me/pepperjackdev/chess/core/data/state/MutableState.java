package me.pepperjackdev.chess.core.data.state;

import me.pepperjackdev.chess.core.data.state.castling.MutableCastingRights;
import me.pepperjackdev.chess.core.data.state.placement.MutablePlacement;
import me.pepperjackdev.chess.core.position.Position;
import me.pepperjackdev.chess.core.Side;

public class MutableState
    implements State {

    private final MutablePlacement placement;
    private Side activeColor;
    private final MutableCastingRights castlingRights;
    private Position enPassantTargetSquare;
    private int halfMoveClock;
    private int fullMoveClock;

    public MutableState(MutablePlacement placement,
                        Side activeColor,
                        MutableCastingRights castlingRights,
                        Position enPassantTargetSquare,
                        int halfMoveClock,
                        int fullMoveClock) {
        this.placement = placement;
        this.activeColor = activeColor;
        this.castlingRights = castlingRights;
        this.enPassantTargetSquare = enPassantTargetSquare;
        this.halfMoveClock = halfMoveClock;
        this.fullMoveClock = fullMoveClock;
    }

    @Override
    public MutablePlacement getPlacement() {
        return placement;
    }

    @Override
    public Side getActiveColor() {
        return activeColor;
    }

    public void setActiveColor(Side activeColor) {
        this.activeColor = activeColor;
    }

    @Override
    public MutableCastingRights getCastlingRights() {
        return castlingRights;
    }

    @Override
    public Position getEnPassantTargetSquare() {
        return enPassantTargetSquare;
    }

    public void setEnPassantTargetSquare(Position enPassantTargetSquare) {
        this.enPassantTargetSquare = enPassantTargetSquare;
    }

    @Override
    public int getHalfMoveClock() {
        return halfMoveClock;
    }

    public void setHalfMoveClock(int halfMoveClock) {
        this.halfMoveClock = halfMoveClock;
    }

    @Override
    public int getFullMoveClock() {
        return fullMoveClock;
    }

    public void setFullMoveClock(int fullMoveClock) {
        this.fullMoveClock = fullMoveClock;
    }
}
