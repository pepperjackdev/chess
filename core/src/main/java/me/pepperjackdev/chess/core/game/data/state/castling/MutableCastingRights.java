package me.pepperjackdev.chess.core.game.data.state.castling;

public class MutableCastingRights
        implements CastlingRights {

    private boolean blackCanCastleKingSide;
    private boolean blackCanCastleQueenSide;
    private boolean whiteCanCastleKingSide;
    private boolean whiteCanCastleQueenSide;

    public MutableCastingRights(boolean blackCanCastleKingSide,
                                boolean blackCanCastleQueenSide,
                                boolean whiteCanCastleKingSide,
                                boolean whiteCanCastleQueenSide) {
        this.blackCanCastleKingSide = blackCanCastleKingSide;
        this.blackCanCastleQueenSide = blackCanCastleQueenSide;
        this.whiteCanCastleKingSide = whiteCanCastleKingSide;
        this.whiteCanCastleQueenSide = whiteCanCastleQueenSide;
    }

    public MutableCastingRights(boolean allCanCastle) {
        this(allCanCastle, allCanCastle, allCanCastle, allCanCastle);
    }

    public boolean canBlackCastleKingSide() {
        return blackCanCastleKingSide;
    }

    public void setBlackCanCastleKingSide(boolean blackCanCastleKingSide) {
        this.blackCanCastleKingSide = blackCanCastleKingSide;
    }

    public boolean canBlackCastleQueenSide() {
        return blackCanCastleQueenSide;
    }

    public void setBlackCanCastleQueenSide(boolean blackCanCastleQueenSide) {
        this.blackCanCastleQueenSide = blackCanCastleQueenSide;
    }

    public boolean canWhiteCastleKingSide() {
        return whiteCanCastleKingSide;
    }

    public void setWhiteCanCastleKingSide(boolean whiteCanCastleKingSide) {
        this.whiteCanCastleKingSide = whiteCanCastleKingSide;
    }

    public boolean canWhiteCastleQueenSide() {
        return whiteCanCastleQueenSide;
    }

    public void setWhiteCanCastleQueenSide(boolean whiteCanCastleQueenSide) {
        this.whiteCanCastleQueenSide = whiteCanCastleQueenSide;
    }
}
