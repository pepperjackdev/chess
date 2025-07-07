package me.pepperjackdev.chess.core.game.data;

import me.pepperjackdev.chess.core.game.data.state.State;

import java.util.Optional;

public interface Data {
    State getState();
    Optional<Result> getResult();
}
