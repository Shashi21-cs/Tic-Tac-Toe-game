#include "tictactoelog.h"


int main() {
    srand((unsigned int)time(NULL));

    int board_size, game_mode, total_players;
    char player_marks[MAX_PARTICIPANT] = {'X', 'O', 'Z'};
    int participant_type[MAX_PARTICIPANT];

    display_welcome();

    // Board size
    while (1) {
        printf("Enter board size (3 - 10): ");
        scanf("%d", &board_size);
        if (board_size >= 3 && board_size <= 10) break;
        printf("Invalid size. Please enter between 3 and 10.\n");
    }

    // Game mode
    while (1) {
        printf("Select mode:\n");
        printf("1. Human vs Human\n");
        printf("2. Human vs Computer\n");
        printf("3. Custom (2-3 players)\n");
        printf("Enter option (1-3): ");
        scanf("%d", &game_mode);
        if (game_mode >= 1 && game_mode <= 3) break;
        printf("Invalid option.\n");
    }

    // Assign player types
    if (game_mode == 1) {
        total_players = 2;
        participant_type[0] = 0;
        participant_type[1] = 0;
    } else if (game_mode == 2) {
        total_players = 2;
        participant_type[0] = 0;
        participant_type[1] = 1;
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

    // Allocate memory for board
    char **game_board = (char **)malloc(board_size * sizeof(char *));
    for (int i = 0; i < board_size; i++)
        game_board[i] = (char *)malloc(board_size * sizeof(char));

    setup_game_board(game_board, board_size);

    int current_turn = 0, game_over = 0;

    FILE *log = fopen("game_log.txt", "w");
    if (log) {
        fprintf(log, "Tic-Tac-Toe Game Started\n");
        fclose(log);
    }

    // Game loop
    while (!game_over) {
        print_board(game_board, board_size);
        printf("Participant %d (%c)'s move\n", current_turn + 1, player_marks[current_turn]);

        if (participant_type[current_turn] == 0)
            human_move(game_board, board_size, player_marks[current_turn]);
        else
            computer_move(game_board, board_size, player_marks[current_turn], player_marks[(current_turn + 1) % total_players]);

        if (check_victory(game_board, board_size, player_marks[current_turn])) {
            print_board(game_board, board_size);
            printf("Participant %d (%c) wins!\n", current_turn + 1, player_marks[current_turn]);
            log_move("Game ended with a WIN\n");
            game_over = 1;
        } else if (board_filled(game_board, board_size)) {
            print_board(game_board, board_size);
            printf("It's a draw!\n");
            log_move("Game ended in a DRAW\n");
            game_over = 1;
        } else {
            current_turn = (current_turn + 1) % total_players;
        }
    }

    for (int i = 0; i < board_size; i++)
        free(game_board[i]);
    free(game_board);

    return 0;
}

