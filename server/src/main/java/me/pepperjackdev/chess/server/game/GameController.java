package me.pepperjackdev.chess.server.game;

import me.pepperjackdev.chess.core.data.Data;
import me.pepperjackdev.chess.server.action.ActionDTO;
import org.springframework.web.bind.annotation.*;

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

    @PostMapping
    public void action(@RequestBody ActionDTO dto) {
        service.action(dto);
    }
}
