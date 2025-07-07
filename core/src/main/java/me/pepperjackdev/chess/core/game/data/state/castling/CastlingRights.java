package me.pepperjackdev.chess.core.game.data.state.castling;

public interface CastlingRights {
    boolean canWhiteCastleKingSide();
    boolean canWhiteCastleQueenSide();
    boolean canBlackCastleKingSide();
    boolean canBlackCastleQueenSide();
}
