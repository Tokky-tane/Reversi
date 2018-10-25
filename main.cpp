#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define N 10
#define T 100

void make_board(int board[N][N]);
void print_board(int board[N][N]);
int check_finish(int t, int board[N][N]);
struct INPUT_DATA input_key(int k, int board[N][N]);
int check_WB(int k, int board[N][N]);
void change_board(int k, int x, int y, int board[N][N]);
int check_change(int k, int i, int j, int board[N][N]);

struct INPUT_DATA {
	int x;
	int y;
};

int main(void) {
	int board[N][N] = { 0 };
	int t;
	int player_frame;
	struct INPUT_DATA input_data;

	make_board(board);
	print_board(board);

	t = 0;
	player_frame = 1;
	while (/*check_finish(t,board)*/ 1) {
		t++;
		//player_frame = check_WB(player_frame, board);
		input_data = input_key(player_frame, board);

		change_board(player_frame, input_data.x, input_data.y, board);

		print_board(board);
		player_frame *= -1;
	}
}

void make_board(int board[N][N]) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (i == 0 || i == N - 1 || j == 0 || j == N - 1) {
				board[i][j] = 2;
			}
			else {
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
		}
		else {
			printf("  ");
		}
		putchar('|');
		for (int j = 0; j < N; j++) {
			switch (board[i][j]) {
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

	struct INPUT_DATA input_key = { 0, 0 };

	while (1) {
		printf("player[%c]のターン\n", (player_frame == 1) ? 'O' : '*');
		printf("座標を入力(x,y)=");
		scanf("%c,%d", &input_key.x, &input_key.y);
		while (getchar() != '\n');

		input_key.x -= 96;

		if (!((0 < input_key.x && input_key.x < N) &&
			(0 < input_key.y && input_key.y < N))) {
			puts("ボードの範囲外です\n");
		}
		else if (check_change(player_frame, input_key.x, input_key.y, board) == 0)
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

void change_board(int k, int x, int y, int board[N][N]) {
}

int check_change(int player_frame, int input_x, int input_y, int board[N][N]) {
	int rival_frame = player_frame * -1;
	int x = input_x, y = input_y;
	int check = 0;

	if (board[input_x][input_y] != 0)
		return check;

	while (board[x + 1][input_y] == rival_frame) {
		check = 1;
		x++;
	}
	if(board[x + 1][input_y] && check == 1) {
		check = 1;
		return check;
	}

	return 0;
}