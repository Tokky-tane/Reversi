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

struct INPUT_DATA {
	int x;
	int y;
};

int main(void) {
	int board[N][N] = { 0 };
	int t;
	int k;
	struct INPUT_DATA input_data;

	make_board(board);
	print_board(board);

	t = 0;
	k = 1;
	while (/*check_finish(t,board)*/ 1) {
		t++;
		k = check_WB(k, board);
		input_data = input_key(k, board);

		change_board(k, input_data.x, input_data.y, board);

		print_board(board);
		k *= -1;
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

struct INPUT_DATA input_key(int k, int board[N][N]) {

	struct INPUT_DATA input_key = { 0, 0 };

	while (1) {
		printf("座標を入力(x,y)=");
		scanf("%c,%d", &input_key.x, &input_key.y);

		input_key.x -= 96;

		if ((0 < input_key.x && input_key.x < N) &&
			(0 < input_key.y && input_key.y < N))
			break;

		while (getchar() != '\n');
		puts("ボードの範囲外です\n");
	}

	printf("x=%d, y=%d\n", input_key.x, input_key.y);

	return input_key;
}

int check_WB(int k, int board[N][N]) {
	return 0;
}

void change_board(int k, int x, int y, int board[N][N]) {
}