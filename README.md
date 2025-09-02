
# Implementation of Othello Game in Qt
 Project Overview

## This project is an Othello (Reversi) game implemented in C++ with Qt Framework.
## It was developed as part of the Object-Oriented Programming course.

The game supports the basic rules of Othello, additional board settings, and UI interaction through Qt’s signal/slot mechanism.

# Features
## 1. Screen Layout

Main Screen: Game title, New Game, Continue, Replay, Exit buttons

Game Settings: Choose board size, obstacle count, and first player

Game Screen:

Display of current turn, turn count, and piece counts (top-right)

Possible moves shown as green circles

Save & return to main screen button (bottom-right)

Replay Screen:

Replay logic implemented but currently unstable (crashes occur)

## 2. Game Rules

Valid Move Check: Possible moves displayed with markers

Stone Flipping: Opponent’s stones flip when captured between player’s stones

Turn Passing: If no valid moves, turn is automatically skipped with a message & sound

Game End & Result: When game ends, result is shown and automatically returns to main screen

## 3. Game Settings

Board Size Selection

Obstacle Placement (number and position)

First Player Selection

## 4. Game State Display

Current player’s turn indicator

Piece counts of both players

Highlighted valid move positions

## 5. Replay (Partially Implemented)

Stores each turn’s game state (GameState objects in a QList)

Navigation via slider / previous / next buttons

Move highlighting not yet implemented

Replay screen currently unstable (crashes)

## 6. Program Stability & Quality

Memory Management: deleteLater() and Qt’s automatic cleanup with setCentralWidget()

Signal/Slot: All UI interactions are managed via Qt’s signal-slot mechanism

Undo Feature: Supports undo by restoring previous state from replay history

Exception Handling:

Warnings when moves are not possible

Alerts when Continue/Undo is unavailable

 Tech Stack

Language: C++

Framework: Qt (Widgets, Signal/Slot)

IDE: Qt Creator

### How to Run

Clone the repository

Open the .pro file with Qt Creator

Build & Run the project

### Known Issues

Replay function crashes despite partial implementation

Minor rendering issues with board coloring (painter function)


# Stopped working on this project!
