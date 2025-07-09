package me.pepperjackdev.chess.server;

import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.datatype.jdk8.Jdk8Module;
import com.fasterxml.jackson.module.paramnames.ParameterNamesModule;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

@SpringBootApplication
public class ServerApplication {

    @Autowired
    public void configureObjectMapper(ObjectMapper objectMapper) {
        objectMapper.registerModule(new ParameterNamesModule())
                .registerModule(new Jdk8Module());
    }

    public static void main(String[] args) {
        SpringApplication.run(ServerApplication.class, args);
    }
}
