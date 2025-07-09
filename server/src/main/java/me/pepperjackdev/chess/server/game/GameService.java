package me.pepperjackdev.chess.server.game;

import me.pepperjackdev.chess.core.Game;
import me.pepperjackdev.chess.core.data.Data;
import me.pepperjackdev.chess.server.action.ActionDTO;
import org.springframework.stereotype.Service;

@Service
public class GameService {
    private final Game game;

    public GameService() {
        game = Game.newStandardGame();
    }

    public Data getData() {
        return game.getData();
    }

    public void action(ActionDTO dto) {
        game.action(dto.toAction());
    }
}
