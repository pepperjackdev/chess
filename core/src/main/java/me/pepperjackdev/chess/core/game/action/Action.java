package me.pepperjackdev.chess.core.game.action;

public sealed interface Action
    permits MoveAction, DrawAction {}
