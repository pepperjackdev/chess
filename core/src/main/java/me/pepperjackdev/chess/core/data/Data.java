package me.pepperjackdev.chess.core.data;

import me.pepperjackdev.chess.core.data.state.State;

import java.util.Optional;

public interface Data {
    State getState();
    Optional<Result> getResult();
}
