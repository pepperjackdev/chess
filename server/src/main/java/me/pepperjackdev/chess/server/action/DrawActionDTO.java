package me.pepperjackdev.chess.server.action;

import me.pepperjackdev.chess.core.action.Action;
import me.pepperjackdev.chess.core.action.DrawAction;

public final class DrawActionDTO
    implements ActionDTO {

    @Override
    public Action toAction() {
        return new DrawAction();
    }
}
