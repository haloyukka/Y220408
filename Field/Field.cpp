#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


// 条件コンパイル
#if 1
#	define GRID_HEIGHT 20
#	define GRID_WIDTH 20
#else
#	define GRID_HEIGHT 5
#	define GRID_WIDTH 5
#endif

// prototype
void disp(const int grid[GRID_HEIGHT][GRID_WIDTH]);

int main() {
	srand((unsigned)time(NULL));

	// 配列初期化
	int grid[GRID_HEIGHT][GRID_WIDTH] = { 0 };
	disp(grid);
}

void disp(const int grid[GRID_HEIGHT][GRID_WIDTH]) {
	for (int row = 0; row < GRID_WIDTH; ++row) {
		for (int col = 0; col < GRID_WIDTH; ++col) {
			switch (grid[row][col]) {
			case 1:break;
			case 2:break;
			default:printf("＋"); break;
			}
		}
		printf("\n");
	}
}