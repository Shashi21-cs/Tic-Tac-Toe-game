#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_PARTICIPANT 3  //Maximum number of players can play
			  
//Renamed Function Prototypes
void displayWelcome();
void setup_game_board(char **game_board, int board_size);
void print_board(char **game_board, int board_size);
int valid_move(char **game_board, int board_size, int row, int col);
int check_victory(char **game_board, int board_size, char current_ mark);
int board_filled(char **game_board, int board_size);
void human_move(char **game_board, int board_size, char mark);
void computer_move(char **game_board, int board_size, char current mark, char opponent);
int get_participant_type(char symbol);



























