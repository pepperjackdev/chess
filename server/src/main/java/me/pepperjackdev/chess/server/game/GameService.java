package me.pepperjackdev.chess.server.game;

import me.pepperjackdev.chess.core.Game;
import me.pepperjackdev.chess.core.Side;
import me.pepperjackdev.chess.core.data.Data;
import me.pepperjackdev.chess.core.data.MutableData;
import me.pepperjackdev.chess.core.data.state.MutableState;
import me.pepperjackdev.chess.core.data.state.castling.MutableCastingRights;
import me.pepperjackdev.chess.core.data.state.placement.MutablePlacement;
import me.pepperjackdev.chess.core.data.state.placement.Size;
import me.pepperjackdev.chess.server.action.ActionDTO;
import org.springframework.stereotype.Service;

@Service
public class GameService {
    private final Game game;

    public GameService() {
        game = new Game(new MutableData(new MutableState(
                new MutablePlacement(new Size(8, 8)),
                Side.WHITE,
                new MutableCastingRights(true),
                null,
                0,
                1
        )));
    }

    public Data getData() {
        return game.getData();
    }

    public void action(ActionDTO dto) {
        game.action(dto.toAction());
    }
}
