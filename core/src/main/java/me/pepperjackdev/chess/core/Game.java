package me.pepperjackdev.chess.core;

import me.pepperjackdev.chess.core.action.Action;
import me.pepperjackdev.chess.core.action.DrawAction;
import me.pepperjackdev.chess.core.data.Data;
import me.pepperjackdev.chess.core.data.MutableData;
import me.pepperjackdev.chess.core.action.MoveAction;
import me.pepperjackdev.chess.core.data.Result;
import me.pepperjackdev.chess.core.data.state.MutableState;
import me.pepperjackdev.chess.core.data.state.castling.MutableCastingRights;
import me.pepperjackdev.chess.core.data.state.placement.MutablePlacement;
import me.pepperjackdev.chess.core.data.state.placement.Size;

public class Game {
    public static Game newStandardGame() {
        return new Game(new MutableData(new MutableState(
                new MutablePlacement(new Size(8, 8)),
                Side.WHITE,
                new MutableCastingRights(true),
                null,
                0,
                1
        )));
    }

    private final MutableData data;

    public Game(MutableData data) {
        this.data = data;
    }

    public Data getData() {
        return data;
    }

    public boolean isOngoing() {
        return data.getResult().isEmpty();
    }

    public boolean isFinished() {
        return !isOngoing();
    }

    public void action(Action action) {
        if (isOngoing()) {
            switch (action) {
                case DrawAction _ -> draw();
                case MoveAction moveAction -> move(moveAction);
            }
        }
    }

    private void move(MoveAction moveAction) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    private void draw() {
        data.setResult(Result.DRAW);
    }
}
