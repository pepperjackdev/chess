package me.pepperjackdev.chess.server;

import com.fasterxml.jackson.databind.module.SimpleModule;
import me.pepperjackdev.chess.core.data.state.State;
import me.pepperjackdev.chess.server.state.StateDeserializer;
import me.pepperjackdev.chess.server.state.StateSerializer;
import org.springframework.boot.autoconfigure.jackson.Jackson2ObjectMapperBuilderCustomizer;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;

@Configuration
public class JacksonConfig {
    @Bean
    public Jackson2ObjectMapperBuilderCustomizer customStateClassSerializerDeserializer() {
        return builder -> {
            SimpleModule module = new SimpleModule();
            module.addSerializer(State.class, new StateSerializer());
            module.addDeserializer(State.class, new StateDeserializer());
            builder.modules(module);
        };
    }
}
