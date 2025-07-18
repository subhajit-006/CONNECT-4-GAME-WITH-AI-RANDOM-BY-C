#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROWS 6
#define COLS 7

char board[ROWS][COLS];

void initBoard() {
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
            board[i][j] = '.';
}

void printBoard() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++)
            printf("%c ", board[i][j]);
        printf("\n");
    }
    for (int j = 0; j < COLS; j++)
        printf("%d ", j);
    printf("\n");
}

int dropDisc(int col, char disc) {
    if (col < 0 || col >= COLS) return -1;
    for (int i = ROWS - 1; i >= 0; i--) {
        if (board[i][col] == '.') {
            board[i][col] = disc;
            return i;
        }
    }
    return -1;
}

int checkWin(int row, int col, char disc) {
    int directions[4][2] = {{0,1},{1,0},{1,1},{1,-1}};
    for (int d = 0; d < 4; d++) {
        int count = 1;
        for (int k = 1; k < 4; k++) {
            int r = row + k * directions[d][0];
            int c = col + k * directions[d][1];
            if (r < 0 || r >= ROWS || c < 0 || c >= COLS || board[r][c] != disc)
                break;
            count++;
        }
        for (int k = 1; k < 4; k++) {
            int r = row - k * directions[d][0];
            int c = col - k * directions[d][1];
            if (r < 0 || r >= ROWS || c < 0 || c >= COLS || board[r][c] != disc)
                break;
            count++;
        }
        if (count >= 4) return 1;
    }
    return 0;
}

int aiMove() {
    int col;
    do {
        col = rand() % COLS;
    } while (dropDisc(col, 'O') == -1);
    return col;
}

int main() {
    srand(time(NULL));
    initBoard();
    printBoard();

    int turn = 0; // 0 = player, 1 = AI
    while (1) {
        int col, row;
        if (turn == 0) {
            printf("Your move (0-6): ");
            scanf("%d", &col);
            row = dropDisc(col, 'X');
            if (row == -1) {
                printf("Invalid move. Try again.\n");
                continue;
            }
        } else {
            col = aiMove();
            row = dropDisc(col, 'O');
            printf("AI plays column %d\n", col);
        }

        printBoard();

        if (checkWin(row, col, (turn == 0) ? 'X' : 'O')) {
            printf("%s wins!\n", (turn == 0) ? "You" : "AI");
            break;
        }

        int full = 1;
        for (int j = 0; j < COLS; j++)
            if (board[0][j] == '.') full = 0;
        if (full) {
            printf("Draw!\n");
            break;
        }

        turn = 1 - turn;
    }

    return 0;
}
