package me.pepperjackdev.chess.io;

import me.pepperjackdev.chess.core.Side;
import me.pepperjackdev.chess.core.data.state.MutableState;
import me.pepperjackdev.chess.core.data.state.State;
import me.pepperjackdev.chess.core.data.state.castling.MutableCastingRights;
import me.pepperjackdev.chess.core.data.state.placement.MutablePlacement;
import me.pepperjackdev.chess.core.data.state.placement.Size;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class StateConverterTest {

    private static final State standardGameStartState = new MutableState(
            new MutablePlacement(new Size(8, 8)),
            Side.WHITE,
            new MutableCastingRights(true),
            null,
            0,
            1
    );

    private static final String standardGameStartFEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";

    @Test
    void serializeStandardGameStartState() {
        // when
        String result = StateConverter.serialize(standardGameStartState);

        // then
        assertEquals("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR", result);
    }

    @Test
    void deserializeStandardGameStartState() {
        // when
        State result = StateConverter.deserialize(standardGameStartFEN);

        // then
        assertEquals(standardGameStartState, result);
    }
}