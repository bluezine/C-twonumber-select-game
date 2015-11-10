#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BOXSIZE 10
#define NUMBERRANGE 10

struct Box {
	int data;
};

int main(void) {
	int i, j, score = 0;
	struct Box **box = (struct Box **)malloc(sizeof(struct Box *) * BOXSIZE);
	int **temp = (int **)malloc(sizeof(int *) * 2);
	
	srand((unsigned int)time(NULL));
	
	// puzzle initialize
	for (i = 0;i < BOXSIZE;i++) {
		box[i] = (struct Box *)malloc(sizeof(struct Box) * BOXSIZE);
	}

	// number count initialize
	for (i = 0;i < 2;i++) {
		temp[i] = (int *)malloc(sizeof(int) * NUMBERRANGE);
	}

	for (i = 0;i < NUMBERRANGE;i++) {
		temp[0][i] = i + 1;
		temp[1][i] = 0;
	}
	
	// puzzle list generate
	for (i = 0;i < BOXSIZE;i++) {
		for (j = 0;j < BOXSIZE;j++) {
			int ran = rand() % NUMBERRANGE + 1;
			box[i][j].data = ran;
			temp[1][ran - 1]++;
		}
	}

	// puzzle print
	printf("Puzzle List\n");
	printf("Score : %d\n", score);
	for (i = 0;i < BOXSIZE;i++) {
		for (j = 0;j < BOXSIZE;j++) {
			printf("%2d ", box[i][j].data);
		}
		printf("\n");
	}
	printf("\n");

	/*
	printf("Number Count\n");
	for (i = 0;i < 2;i++) {
		for (j = 0;j < NUMBERRANGE;j++) {
			printf("%2d ", temp[i][j]);
		}
		printf("\n");
	}
	*/
	
	// Game
	while (1) {
		int x1, y1, x2, y2;
		printf("(x1, y1), (x2, y2) : x1 y1 x2 y2 => ");
		fflush(stdin);
		scanf_s("%d %d %d %d)", &x1, &y1, &x2, &y2);
		
		// two ordered compare
		if (box[x1][y1].data == box[x2][y2].data) {
			// same position number select
			if (&box[x1][y1] == &box[x2][y2]) {
				printf("Same position number select impossible.\n");
				continue;
			}
			score += 10;
			
			// new number generate
			int ran;
			for (i = 0;i < 2;i++) {
				while (1) {
					ran = rand() % NUMBERRANGE + 1;
					if (temp[1][ran - 1] % 2 != 0) {
						temp[1][ran - 1]++;
						break;
					}
				}
				if (i==0)
					box[x1][y1].data = ran;
				else if (i==1)
					box[x2][y2].data = ran;
			}
			
			system("cls");

			// redraw puzzle list
			printf("Puzzle List\n");
			printf("Score : %d\n", score);
			for (i = 0;i < BOXSIZE;i++) {
				for (j = 0;j < BOXSIZE;j++) {
					printf("%2d ", box[i][j].data);
				}
				printf("\n");
			}
			printf("\n");
		}
	}

	return 0;
}