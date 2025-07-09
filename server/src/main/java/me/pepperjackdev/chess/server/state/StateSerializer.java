package me.pepperjackdev.chess.server.state;

import com.fasterxml.jackson.core.JsonGenerator;
import com.fasterxml.jackson.databind.JsonSerializer;
import com.fasterxml.jackson.databind.SerializerProvider;
import me.pepperjackdev.chess.core.data.state.State;
import me.pepperjackdev.chess.io.StateConverter;

import java.io.IOException;

public class StateSerializer
    extends JsonSerializer<State> {
    @Override
    public void serialize(
            State state,
            JsonGenerator jsonGenerator,
            SerializerProvider serializerProvider
    ) throws IOException {
        jsonGenerator.writeString(StateConverter.serialize(state));
    }
}
