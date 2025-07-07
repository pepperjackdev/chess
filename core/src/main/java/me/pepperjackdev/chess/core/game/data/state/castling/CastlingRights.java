package me.pepperjackdev.chess.core.game.data.state.castling;

public interface CastlingRights {
    boolean getWhiteCanCastleKingSide();
    boolean getWhiteCanCastleQueenSide();
    boolean getBlackCanCastleKingSide();
    boolean getBlackCanCastleQueenSide();
}
