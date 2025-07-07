package me.pepperjackdev.chess.server.game;

import me.pepperjackdev.chess.core.game.Game;
import me.pepperjackdev.chess.core.game.data.Data;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
@RequestMapping("/api/game")
public class GameController {
    private final GameService service;

    public GameController(GameService service) {
        this.service = service;
    }

    @GetMapping
    public Data getData() {
        return service.getData();
    }
}
