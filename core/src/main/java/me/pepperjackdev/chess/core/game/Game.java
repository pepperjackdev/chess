package me.pepperjackdev.chess.core.game;

import me.pepperjackdev.chess.core.game.action.Action;
import me.pepperjackdev.chess.core.game.action.DrawAction;
import me.pepperjackdev.chess.core.game.data.Data;
import me.pepperjackdev.chess.core.game.data.MutableData;
import me.pepperjackdev.chess.core.game.action.MoveAction;
import me.pepperjackdev.chess.core.game.data.Result;

public class Game {
    private final MutableData data;

    public Game(MutableData data) {
        this.data = data;
    }

    public Data getData() {
        return data;
    }

    public boolean isOngoing() {
        return data.getResult().isPresent();
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
        System.out.println("Draw!");
    }
}
