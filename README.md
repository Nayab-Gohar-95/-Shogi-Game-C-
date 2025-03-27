# Shogi Game (C++)

## Table of Contents
- [Introduction](#introduction)
- [Features](#features)
- [Game Mechanics](#game-mechanics)
- [Technologies Used](#technologies-used)
- [Project Structure](#project-structure)
- [Setup and Installation](#setup-and-installation)
- [How to Play](#how-to-play)
- [Future Improvements](#future-improvements)
  
## Introduction
This is a **Shogi (Japanese Chess) game** implemented in **C++**. It allows players to experience the traditional board game with programmatic rules and logic.

## Features
- Full implementation of Shogi rules.
- Command-line interface for gameplay.
- Custom input file support.
- Move validation and game state tracking.

## Game Mechanics
- Players take turns moving pieces on the board.
- Each piece has specific movement rules (similar to chess but with unique Shogi mechanics).
- The game ends when a player checkmates the opponent's king.

## Technologies Used
- **C++** (Game Logic)
- **File Handling** (for reading input moves from `Input.txt`)

## Project Structure
```
.
├── shogi.cpp            # Main game source code
├── Input.txt            # Sample input moves file
├── README.md            # Project documentation
```

## Setup and Installation

### **Compiling the Game**
1. **Using g++ (MinGW on Windows)**:
   ```sh
   g++ shogi.cpp -o shogi_game
   ```
2. **Using Dev-C++ or CodeBlocks**:
   - Open `shogi.cpp` in the IDE.
   - Compile and run the project.

## How to Play
- Run the compiled program in the terminal.
- Enter moves manually or provide an `Input.txt` file with pre-defined moves.
- Follow the game rules to capture the opponent's king.

## Future Improvements
- Implement GUI for better user experience.
- Add AI opponent for single-player mode.
- Save and load game states.

