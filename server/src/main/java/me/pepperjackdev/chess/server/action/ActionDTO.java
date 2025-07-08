package me.pepperjackdev.chess.server.action;

import com.fasterxml.jackson.annotation.JsonSubTypes;
import com.fasterxml.jackson.annotation.JsonTypeInfo;
import me.pepperjackdev.chess.core.action.Action;

@JsonTypeInfo(
        use = JsonTypeInfo.Id.NAME,
        include = JsonTypeInfo.As.PROPERTY,
        property = "type")
@JsonSubTypes({
        @JsonSubTypes.Type(value = DrawActionDTO.class, name = "draw"),
})
public sealed interface ActionDTO
    permits DrawActionDTO {
    Action toAction();
}
