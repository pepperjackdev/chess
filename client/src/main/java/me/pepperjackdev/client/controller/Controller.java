package me.pepperjackdev.client.controller;

import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController("greet")
public class Controller {

    @GetMapping
    public String greet() {
        return "Hello World!";
    }
}
