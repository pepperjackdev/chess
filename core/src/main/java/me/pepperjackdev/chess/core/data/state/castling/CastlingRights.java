package me.pepperjackdev.chess.core.data.state.castling;

public interface CastlingRights {
    boolean getWhiteCanCastleKingSide();
    boolean getWhiteCanCastleQueenSide();
    boolean getBlackCanCastleKingSide();
    boolean getBlackCanCastleQueenSide();
}
