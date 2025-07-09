package me.pepperjackdev.chess.server.state;

import com.fasterxml.jackson.core.JacksonException;
import com.fasterxml.jackson.core.JsonParser;
import com.fasterxml.jackson.databind.DeserializationContext;
import com.fasterxml.jackson.databind.JsonDeserializer;
import me.pepperjackdev.chess.core.data.state.State;
import me.pepperjackdev.chess.io.StateConverter;

import java.io.IOException;

public class StateDeserializer
    extends JsonDeserializer<State> {
    @Override
    public State deserialize(
            JsonParser jsonParser,
            DeserializationContext deserializationContext
    ) throws IOException, JacksonException {
        return StateConverter.deserialize(jsonParser.getText());
    }
}
