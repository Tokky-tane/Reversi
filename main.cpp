#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>

#define N 10
#define T 100

void make_board(int board[N][N]);

void print_board(int board[N][N]);

int check_finish(int t, int board[N][N]);

struct INPUT_DATA input_key(int player_frame, int board[N][N]);

int check_WB(int k, int board[N][N]);

void change_board(int player_frame, int x, int y, int board[N][N]);

int check_change(int player_frame, int x, int y, int board[N][N]);

struct INPUT_DATA {
    int x;
    int y;
};

int main(void) {
    int board[N][N][N] = {0};
    int turn;
    int player_frame[T];
    struct INPUT_DATA input_data;

    make_board(board[0]);
    print_board(board[0]);

    turn = 0;
    player_frame[0] = 1;
    while (/*check_finish(turn,board)*/ 1) {
        //player_frame = check_WB(player_frame, board);
        input_data = input_key(player_frame[turn], board[turn]);

        memcpy(board[turn + 1], board[turn], sizeof(int) * N * N);

        change_board(player_frame[turn], input_data.x, input_data.y, board[turn + 1]);

        print_board(board[turn + 1]);
        player_frame[turn + 1] = player_frame[turn] * -1;
        turn++;
    }
}

void make_board(int board[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == 0 || i == N - 1 || j == 0 || j == N - 1) {
                board[i][j] = 2;
            } else {
                board[i][j] = 0;
            }
        }
    }

    board[N / 2][N / 2] = 1;
    board[N / 2 - 1][N / 2 - 1] = 1;
    board[N / 2 - 1][N / 2] = -1;
    board[N / 2][N / 2 - 1] = -1;
}

void print_board(int board[N][N]) {
    putchar('\n');
    printf("     ");
    for (int i = 0; i < N - 2; i++) {
        printf("%c ", i + 97);
    }
    putchar('\n');

    for (int i = 0; i < N; i++) {
        if (0 < i && i < N - 1) {
            printf("%2d", i);
        } else {
            printf("  ");
        }
        putchar('|');
        for (int j = 0; j < N; j++) {
            switch (board[j][i]) {
                case 0:
                    putchar(' ');
                    break;
                case 1:
                    putchar('O');
                    break;
                case -1:
                    putchar('*');
                    break;
                case 2:
                    putchar('-');
                default:
                    break;
            }

            putchar('|');
        }
        putchar('\n');
    }
}

int check_finish(int t, int board[N][N]) {
    return 0;
}

struct INPUT_DATA input_key(int player_frame, int board[N][N]) {

    struct INPUT_DATA input_key = {0, 0};

    while (1) {
        printf("player[%c]のターン\n", (player_frame == 1) ? 'O' : '*');
        printf("座標を入力(x,y)=");
        scanf("%c,%d", &input_key.x, &input_key.y);
        while (getchar() != '\n');

        input_key.x -= 96;

        if (!((0 < input_key.x && input_key.x < N) &&
              (0 < input_key.y && input_key.y < N))) {
            puts("ボードの範囲外です\n");
        } else if (check_change(player_frame, input_key.x, input_key.y, board) == 0)
            puts("選択したマスにはおけません\n");
        else {
            break;
        }
    }
    return input_key;
}

int check_WB(int k, int board[N][N]) {
    return 0;
}

void change_board(int player_frame, int x, int y, int board[N][N]) {
    int X = x, Y = y;
    int rival_frame = player_frame * -1;

    board[X][Y] = player_frame;

    // 右側の裏返し
    while (board[X + 1][y] == rival_frame) {
        X++;
    }
    if (board[X + 1][y] == player_frame) {
        X = x;
        while (board[X + 1][y] == rival_frame) {
            board[X + 1][y] = player_frame;
            X++;
        }
    }
    X = x;

    //　左側の裏返し
    while (board[X - 1][y] == rival_frame) {
        X--;
    }
    if (board[X - 1][y] == player_frame) {
        X = x;
        while (board[X - 1][y] == rival_frame) {
            board[X - 1][y] = player_frame;
            X--;
        }
    }
    X = x;

    // 上側の裏返し
    while (board[x][Y + 1] == rival_frame) {
        Y++;
    }
    if (board[x][Y + 1] == player_frame) {
        Y = y;
        while (board[x][Y + 1] == rival_frame) {
            board[x][Y + 1] = player_frame;
            Y++;
        }
    }
    Y = y;

    // 下側の裏返し
    while (board[x][Y - 1] == rival_frame) {
        Y--;
    }
    if (board[x][Y - 1] == player_frame) {
        Y = y;
        while (board[x][Y - 1] == rival_frame) {
            board[x][Y - 1] = player_frame;
            Y--;
        }
    }
    Y = y;

    // 右斜め上
    while (board[X + 1][Y - 1] == rival_frame) {
        X++;
        Y--;
    }
    if (board[X + 1][Y - 1] == player_frame) {
        X = x;
        Y = y;
        while (board[X + 1][Y - 1] == rival_frame) {
            board[X + 1][Y - 1] = player_frame;
            X++;
            Y--;
        }
    }
    X = x;
    Y = y;

    // 右斜め下
    while (board[X + 1][Y + 1] == rival_frame) {
        X++;
        Y++;
    }
    if (board[X + 1][Y + 1] == player_frame) {
        X = x;
        Y = y;
        while (board[X + 1][Y + 1] == rival_frame) {
            board[X + 1][Y + 1] = player_frame;
            X++;
            Y++;
        }
    }
    X = x;
    Y = y;

    // 左斜め下
    while (board[X - 1][Y + 1] == rival_frame) {
        X--;
        Y++;
    }
    if (board[X - 1][Y + 1] == player_frame) {
        X = x;
        Y = y;
        while (board[X - 1][Y + 1] == rival_frame) {
            board[X - 1][Y + 1] = player_frame;
            X--;
            Y++;
        }
    }
    X = x;
    Y = y;

    // 左斜め上
    while (board[X - 1][Y - 1] == rival_frame) {
        X--;
        Y--;
    }
    if (board[X - 1][Y - 1] == player_frame) {
        X = x;
        Y = y;
        while (board[X - 1][Y - 1] == rival_frame) {
            board[X - 1][Y - 1] = player_frame;
            X--;
            Y--;
        }
    }
}

int check_change(int player_frame, int x, int y, int board[N][N]) {
    int rival_frame = player_frame * -1;
    int X = x, Y = y;
    int check = 0;

    if (board[x][y] != 0)
        return check;


    // 右側の判定
    while (board[X + 1][y] == rival_frame) {
        check = 1;
        X++;
    }
    if (board[X + 1][y] == player_frame && check == 1) {
        check = 1;
        return check;
    }
    check = 0;
    X = x;

    // 左側の判定
    while (board[X - 1][y] == rival_frame) {
        check = 1;
        X--;
    }
    if (board[X - 1][y] == player_frame && check == 1) {
        check = 1;
        return check;
    }
    check = 0;
    X = x;

    // 上側の判定
    while (board[x][Y + 1] == rival_frame) {
        check = 1;
        Y++;
    }
    if (board[x][Y + 1] == player_frame && check == 1) {
        check = 1;
        return check;
    }
    check = 0;
    Y = y;

    // 下側の判定
    while (board[x][Y - 1] == rival_frame) {
        check = 1;
        Y--;
    }
    if (board[x][Y - 1] == player_frame && check == 1) {
        check = 1;
        return check;
    }
    check = 0;
    Y = y;

    // 右斜め上
    while (board[X + 1][Y - 1] == rival_frame) {
        check = 1;
        X++;
        Y--;
    }
    if (board[X + 1][Y - 1] == player_frame && check == 1) {
        check = 1;
        return check;
    }
    check = 0;
    X = x;
    Y = y;

    // 右斜め下
    while (board[X + 1][Y + 1] == rival_frame) {
        check = 1;
        X++;
        Y++;
    }
    if (board[X + 1][Y + 1] == player_frame && check == 1) {
        check = 1;
        return check;
    }
    check = 0;
    X = x;
    Y = y;

    // 左斜め下
    while (board[X - 1][Y + 1] == rival_frame) {
        check = 1;
        X--;
        Y++;
    }
    if (board[X - 1][Y + 1] == player_frame && check == 1) {
        check = 1;
        return check;
    }
    check = 0;
    X = x;
    Y = y;

    // 左斜め上
    while (board[X - 1][Y - 1] == rival_frame) {
        check = 1;
        X--;
        Y--;
    }
    if (board[X - 1][Y - 1] == player_frame && check == 1) {
        check = 1;
        return check;
    }

    return 0;
}
