package me.pepperjackdev.chess.core.action;

public sealed interface Action
    permits MoveAction, DrawAction {}
