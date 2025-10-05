# Tic-Tac-Toe-game
 
IT25100940
Bandara H.C.S
Group 01
# Tic-Tac-Toe in C

A fully functional **Tic-Tac-Toe** game written in C that supports:
- Human vs Human mode  
- Human vs Computer mode  
- Multi-player (2–3 players, human or computer mix)  
- Game logging (records every move and game result in `game_log.txt`)  

## Project Structure
TicTacToe/
│
├── main.c # Contains the main game flow
├── tictactoe.c # Function definitions (game logic)
├── tictactoe.h # Function prototypes and constants
└── game_log.txt # Automatically created during gameplay

## Compilation Instructions

Make sure all three source files (`main.c`, `tictactoe.c`, and `tictactoe.h`) are in the same directory.

To compile:
```bash
gcc main.c tictactoe.c -o tictactoe

To run:
./tictactoe

Features

✅ Board Size Selection
Choose a board size from 3×3 to 10×10.

✅ Game Modes
Human vs Human — two players take turns.
Human vs Computer — play against a simple AI.
Custom Mode — allows 2 or 3 players, any mix of human and computer.

✅ Computer AI
Tries to win if possible.
Blocks your winning moves.
Otherwise makes a random valid move.

✅ Logging System
Each move is recorded in game_log.txt.
Logs game start, player actions, and the final result.

How to Play

Run the program.
Enter the board size (3–10).
Choose your game mode:
  1 → Human vs Human
  2 → Human vs Computer
  3 → Custom setup (2–3 players)

Enter your moves as row and column numbers (e.g., 1 2).
The game ends when:
   A player wins (row, column, or diagonal filled).
   The board is full → Draw.
