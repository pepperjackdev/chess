package me.pepperjackdev.chess.io;

import me.pepperjackdev.chess.core.Side;
import me.pepperjackdev.chess.core.data.state.placement.MutablePlacement;
import me.pepperjackdev.chess.core.data.state.placement.Placement;
import me.pepperjackdev.chess.core.data.state.placement.Size;
import me.pepperjackdev.chess.core.piece.Pawn;
import me.pepperjackdev.chess.core.position.Position;
import org.junit.jupiter.api.Test;

import java.util.Map;

import static org.junit.jupiter.api.Assertions.*;

public class PlacementConverterTest {
    private static final Placement testGamePlacement = new MutablePlacement(new Size(8, 8), Map.of(
            new Position(0, 0), new Pawn(Side.BLACK)
    ));

    private static final String testGamePlacementFen = "8/8/8/8/8/8/8/p7";

    @Test
    void serializeTestGamePlacement() {
        // when
        String result = PlacementConverter.serialize(testGamePlacement);

        // then
        assertEquals(testGamePlacementFen, result);
    }
}
