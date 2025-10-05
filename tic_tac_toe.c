#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_PARTICIPANT 3  //Maximum number of players can play
			  
//Renamed Function Prototypes
void display_welcome();
void setup_game_board(char **game_board, int board_size);
void print_board(char **game_board, int board_size);
int valid_move(char **game_board, int board_size, int row, int col);
int check_victory(char **game_board, int board_size, char current_mark);
int board_filled(char **game_board, int board_size);
void human_move(char **game_board, int board_size, char current_mark);
void computer_move(char **game_board, int board_size, char opponent, char current_mark);
int get_participant_type(char player_marks);

int main() {
	srand((unsigned int)time(NULL)); //send random number generator

	int board_size, game_mode, total_players;
	char player_marks[MAX_PARTICIPANT] = {'X', 'O', 'Z'};
        int participant_type[MAX_PARTICIPANT]; // 0 = human, 1 = computer
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
		printf("Enter option (1-3): ");
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
		    participant_type[i] = get_participant_type(player_marks[i]);
	    }
   	}
	
	//Allocate board memory
	char **game_board = (char **)malloc(board_size * sizeof(char *));
	for (int i = 0; i < board_size; i++) {
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
		if (participant_type[current_turn] == 0) {
			human_move(game_board, board_size, player_marks[current_turn]);
	        } else {
			char opponent = player_marks[(current_turn + 1) % total_players];
			computer_move(game_board, board_size, player_marks[current_turn], opponent);
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
	for (int i = 0; i < board_size; i++) {
		free(game_board[i]);
	}
	free(game_board);

	return 0;
}


//Show welcome message
void display_welcome() {
	printf("..Welcome to Tic-Tac-Toe..\n");
	printf("Rules:\n");
	printf("- 2 or 3 participants can play.\n");
	printf("- Fill a row, column or diagonal to win.\n");
	printf("- Board size range: 3 to 10\n");
}

//Initialize empty board
void setup_game_board(char **game_board, int board_size) {
	for (int i = 0; i < board_size; i++)
		for (int j = 0; j < board_size; j++)
			game_board[i][j] = '-';
}

//Print board with grid lines
void print_board(char **game_board, int board_size) {
	printf("\n  ");
	for (int c = 0; c < board_size; c++) printf(" %2d", c + 1);
	printf("\n");

	for (int r = 0; r < board_size; r++) {
		printf(" %2d ", r + 1);
		for (int c = 0; c < board_size; c++) {
			printf(" %c ", game_board[r][c]);
			if (c < board_size - 1) printf("|");
		}
		printf("\n");
		if (r < board_size - 1) {
			printf("  ");
			for (int c = 0; c < board_size; c++) {
				printf("---");
				if (c < board_size - 1) printf("+");
			}
			printf("\n");
		}
	}
	printf("\n");
}

//Validate move: checks bounds and if cell is empty
int valid_move(char **game_board, int board_size, int row, int col) {
	if (row < 0 || row >= board_size) return 0;
	if (col < 0 || col >= board_size) return 0;
	if (game_board[row][col] != '-') return 0;
	return 1;
}

//Check for Winner
int check_victory(char **game_board, int board_size, char current_mark) {
	int count;
	//Check Rows
	for (int r = 0; r < board_size; r++) {
		count = 0;
		for (int c = 0; c < board_size; c++) {
			if (game_board[r][c] == current_mark) count++;
		}
		if (count == board_size) return 1;
	}
	
	//Check columns
	for (int c = 0; c < board_size; c++) {
		count = 0;
		for (int r = 0; r < board_size; r++) {
			if (game_board[r][c] == current_mark) count++;
		}
		if (count == board_size) return 1;
		
	}

	//Check Main Diagonal
	count = 0;
        for (int r = 0; r < board_size; r++) {
		if (game_board[r][r] == current_mark) count++;
	}
	if (count == board_size) return 1;
	

	//Check Anti-Diagonal
	count = 0;
	for (int r = 0; r < board_size; r++) {
		if (game_board[r] [board_size - 1 - r] == current_mark) count++;
	}
	if (count == board_size) return 1;

	return 0;
}

//Check if board is full (Draw condition)
int board_filled(char **game_board, int board_size) {
	for (int r = 0; r < board_size; r++)
		for (int c = 0; c < board_size; c++)
			if (game_board[r][c] == '-') return 0; //Found empty spot
       	return 1; //Board is full
}
		
		 	
//Human Turn
void human_move(char **game_board, int board_size, char current_mark) {
	int r, c;
	while (1) {
		printf("Enter row and column: ");
		scanf("%d %d", &r, &c);
		r--; c--;
		if (valid_move(game_board, board_size, r, c)) {
			game_board[r][c] = current_mark;
			break;
		} else {
			printf("Invalid move, Try Again..\n");
		}
	}
}

//Computer turn
void computer_move(char **game_board, int board_size, char current_mark, char opponent) {
	int r, c;

	//1. Try to win
	for (int i = 0; i < board_size; i++) {
		for (int j = 0; j < board_size; j++) {
			if (valid_move(game_board, board_size, i, j)) {
				game_board [i] [j] = current_mark;
				if (check_victory(game_board, board_size, current_mark)) {
					printf("Computer plays at (%d. %d) to WIN\n", i + 1, j + 1);
					return;
				}
				game_board [i] [j] = '-';
			}
		}
	}

	//2. Try to bloock opponent
	for (int i = 0; i < board_size; i++) {
		for (int j = 0; j < board_size; j++) {
			if (valid_move(game_board, board_size, i, j)) {
		           	game_board [i] [j] = opponent;
				if (check_victory(game_board, board_size, opponent)) {
					game_board [i] [j] = current_mark;
					printf("Computer blocks at (%d, %d)\n", i + 1, j + 1);
					return;
				}
				game_board [i] [j] = '-';
			}
		}
	}

	//3. Else random valid move
	do {
		r = rand() % board_size;
		c = rand() % board_size;
	} while (!valid_move(game_board, board_size, r, c));

	game_board [r] [c] = current_mark;
	printf("Computer choose random (%d, %d)\n", r + 1, c + 1);
}

//Ask player type
int get_participant_type(char player_mark) {
	int type;
	while (1) {
		printf("Participant %c - 0 = Human, 1 = Computer: ", player_mark);
		scanf("%d", &type);
		if (type == 0 || type == 1) return type;
		printf("Invalid..! Enter 0 or 1.\n");
		}
	}




























