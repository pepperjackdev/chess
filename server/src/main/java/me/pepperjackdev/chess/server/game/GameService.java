package me.pepperjackdev.chess.server.game;

import me.pepperjackdev.chess.core.game.Game;
import me.pepperjackdev.chess.core.game.Side;
import me.pepperjackdev.chess.core.game.data.Data;
import me.pepperjackdev.chess.core.game.data.MutableData;
import me.pepperjackdev.chess.core.game.data.state.MutableState;
import me.pepperjackdev.chess.core.game.data.state.castling.MutableCastingRights;
import me.pepperjackdev.chess.core.game.data.state.placement.MutablePlacement;
import me.pepperjackdev.chess.core.game.data.state.placement.Size;
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
}
