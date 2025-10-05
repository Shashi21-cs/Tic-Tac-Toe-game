#include "tictactoelog.h"

// Display welcome message
void display_welcome() {
    printf("..Welcome to Tic-Tac-Toe..\n");
    printf("Rules:\n");
    printf("- 2 or 3 participants can play.\n");
    printf("- Fill a row, column or diagonal to win.\n");
    printf("- Board size range: 3 to 10\n");
}

// Initialize empty board
void setup_game_board(char **game_board, int board_size) {
    for (int i = 0; i < board_size; i++)
        for (int j = 0; j < board_size; j++)
            game_board[i][j] = '-';
}

// Print board
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

// Validate move
int valid_move(char **game_board, int board_size, int row, int col) {
    if (row < 0 || row >= board_size) return 0;
    if (col < 0 || col >= board_size) return 0;
    if (game_board[row][col] != '-') return 0;
    return 1;
}

// Check victory
int check_victory(char **game_board, int board_size, char current_mark) {
    int count;

    // Rows
    for (int r = 0; r < board_size; r++) {
        count = 0;
        for (int c = 0; c < board_size; c++)
            if (game_board[r][c] == current_mark) count++;
        if (count == board_size) return 1;
    }

    // Columns
    for (int c = 0; c < board_size; c++) {
        count = 0;
        for (int r = 0; r < board_size; r++)
            if (game_board[r][c] == current_mark) count++;
        if (count == board_size) return 1;
    }

    // Main diagonal
    count = 0;
    for (int r = 0; r < board_size; r++)
        if (game_board[r][r] == current_mark) count++;
    if (count == board_size) return 1;

    // Anti-diagonal
    count = 0;
    for (int r = 0; r < board_size; r++)
        if (game_board[r][board_size - 1 - r] == current_mark) count++;
    if (count == board_size) return 1;

    return 0;
}

// Check if board is full
int board_filled(char **game_board, int board_size) {
    for (int r = 0; r < board_size; r++)
        for (int c = 0; c < board_size; c++)
            if (game_board[r][c] == '-') return 0;
    return 1;
}

// Human move
void human_move(char **game_board, int board_size, char current_mark) {
    int r, c;
    while (1) {
        printf("Enter row and column: ");
        scanf("%d %d", &r, &c);
        r--; c--;
        if (valid_move(game_board, board_size, r, c)) {
            game_board[r][c] = current_mark;
            char log_msg[50];
            sprintf(log_msg, "Player %c placed at (%d,%d)\n", current_mark, r + 1, c + 1);
            log_move(log_msg);
            break;
        } else {
            printf("Invalid move, Try Again..\n");
        }
    }
}

// Computer move
void computer_move(char **game_board, int board_size, char current_mark, char opponent) {
    int r, c;

    // Try to win
    for (int i = 0; i < board_size; i++) {
        for (int j = 0; j < board_size; j++) {
            if (valid_move(game_board, board_size, i, j)) {
                game_board[i][j] = current_mark;
                if (check_victory(game_board, board_size, current_mark)) {
                    printf("Computer plays at (%d, %d) to WIN\n", i + 1, j + 1);
                    log_move("Computer made a winning move\n");
                    return;
                }
                game_board[i][j] = '-';
            }
        }
    }

    // Block opponent
    for (int i = 0; i < board_size; i++) {
        for (int j = 0; j < board_size; j++) {
            if (valid_move(game_board, board_size, i, j)) {
                game_board[i][j] = opponent;
                if (check_victory(game_board, board_size, opponent)) {
                    game_board[i][j] = current_mark;
                    printf("Computer blocks at (%d, %d)\n", i + 1, j + 1);
                    log_move("Computer blocked opponent\n");
                    return;
                }
                game_board[i][j] = '-';
            }
        }
    }

    // Random move
    do {
        r = rand() % board_size;
        c = rand() % board_size;
    } while (!valid_move(game_board, board_size, r, c));

    game_board[r][c] = current_mark;
    printf("Computer chooses random (%d, %d)\n", r + 1, c + 1);
    log_move("Computer made a random move\n");
}

// Player type
int get_participant_type(char player_mark) {
    int type;
    while (1) {
        printf("Participant %c - 0 = Human, 1 = Computer: ", player_mark);
        scanf("%d", &type);
        if (type == 0 || type == 1) return type;
        printf("Invalid..! Enter 0 or 1.\n");
    }
}

// Log file writer
void log_move(const char *message) {
    FILE *log = fopen("game_log.txt", "a");
    if (log) {
        fprintf(log, "%s", message);
        fclose(log);
    }
}


