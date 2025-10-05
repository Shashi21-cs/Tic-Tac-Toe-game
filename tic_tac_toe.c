#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_PARTICIPANT 3  //Maximum number of players can play
			  
//Renamed Function Prototypes
void display_welcome();
void setup_game_board(char **game_board, int board_size);
void print_board(char **game_board, int board_size);
int valid_move(char **game_board, int board_size, int row, int col);
int check_victory(char **game_board, int board_size, char current_ mark);
int board_filled(char **game_board, int board_size);
void human_move(char **game_board, int board_size, char mark);
void computer_move(char **game_board, int board_size, char opponent, char current mark,const char player_marks[], int total_players);
int get_participant_type(char symbol);

int main() {
	srand((unsigned int)time(NULL)); //send random number generator

	int board_size, game_mode, total_players;
	char player_marks[MAX_PARTICIPANTS} = {'X', 'O', 'Z'};
        int participant_type[MAX_PARTICIPANTS]; // 0 = human, 1 = computer
	display_welcome(); //Display welcome message

	//Prompt used for board size
	while (1) {
	 	printf("Enter board size (3 - 10): ");
		scanf("%d", &board_size);
		if (board_size >= 3 && board_size <= 10) break;
		printf("Invalid size. Please enter between 3 and 10.\n");
	}
	
	//Prompt game mode selection
	while (1) {
		printf("Select mode:\n");
		printf("1. Human vs Human\n");
		printf("2. Human vs Computer\n");
		printf("3. Custom (2-3 player with type)\n");
		Printf("Enter option (1-3): ");
		scanf("%d", &game_mode);
		if (game_mode >= 1 && game_mode <= 3) break;
		printf("Invalid option. Choose 1, 2 or 3.\n");
	}

	//Set number of players and assign player types
	if (game_mode == 1) {
		total_players = 2;
		participant_type[0] = 0; //human
		participant_type[1] = 0; //computer
	} else if (game_mode == 2) {
	        total_players = 2;
		participant_type[0] = 0; //human
		participant_type[1] = 0; //computer
	} else {
	    while (1) {
		    printf("Enter total number of participants (2 or 3): ");
		    scanf("%d", &total_players);
		    if (total_players >= 2 && total_players <= 3) break;
		    printf("Invalid number. Enter 2 or 3.\n");
            }
	    for (int i = 0; i < total_players; i++) {
		    participant_type[i] = get_participant_type(symbol[i]);
	    }
   	}
	
	//Allocate board memory
	char **game_board = (char **)malloc(board_size * sizeof(char *));
	for (int i = 0; i < biard_size; i++) {
		game_board[i] = (char *)malloc(board_size * sizeof(char));
	}

	setup_game_board(game_board, board_size); //Setup empty board
	int current_turn = 0;
	int game_over = 0;

	//Main Game Loop
	while (!game_over) {
		print_board(game_board, board_size);
		printf("Participant %d (%c)'s move\n", current_turn + 1, player_marks[current_turn]);
		//Human or Computer takes a turn
		if (participant_type[current index] == 0) {
			human_move(game_board, board_size, player_marks[current_turn]);
	        } else {
			char opponent = player_marks[(current_turn + 1) % total_players];
			computer_mov(game_board, board_size, player_marks[current_turn], opponent);
		}

		//Check game state after the move
		if (check_victory(game_board, board_size, player_marks[current_turn])) {
			print_board(game_board, board_size);
			printf("Participant %d (%c) wins!\n", current_turn + 1, player_marks[current_turn]);
			game_over = 1;
		} else if (board_filled(game_board, board_size)) {
			print_board(game_board, board_size);
			printf("It's a draw!\n");
                        game_over = 1;
		} else {
			current_turn = (current_turn + 1) % total_players;
		       }
		}
		
	//Clean up allocated memory
	for (int i = 0, i < board_size; i++) {
		free(game_board[i]);
	}
	free(game_board);

	return 0;
}


		 	





























