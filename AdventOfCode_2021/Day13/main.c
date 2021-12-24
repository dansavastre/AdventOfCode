#include <stdio.h>
#include <string.h>

int a[10000][10000];

struct Fold {
	char axis;
	int point;
} folds[100];

int nFolds = 0;
int sizeX, sizeY;


void fold(char axis, int point) {
	//printf("size: (%d, %d) -> ", sizeX, sizeY);
	if(axis == 'x') {
		//printf("Fold on x\n");
		for(int i = 0; i < sizeY; i++) {
			for(int j = 0; j < point; j++) {
				if(a[i][j] == 0) {
					a[i][j] = a[i][sizeX - j - 1];
				}
			}
		}
		sizeX = point;
	}
	else {
		//printf("Fold on y\n");
		for(int i = 0; i < point; i++) {
			for(int j = 0; j < sizeX; j++) {
				if(a[i][j] == 0) {
					a[i][j] = a[sizeY - i - 1][j];
				}
			}
		}
		sizeY = point;

	}
	//printf("(%d, %d)\n", sizeX, sizeY);
}

void doPartOne() {
	int part1 = 0;
	//for(int i = 0; i < nFolds; i++) {
	//	fold(folds[i].axis, folds[i].point);
	//}
	fold(folds[0].axis, folds[0].point);
	for(int i = 0; i < sizeY; i++) {
		for(int j = 0; j < sizeX; j++) {
			part1 += a[i][j];
		}
	}
	printf("Part 1: %d\n", part1);
}

void doPartTwo() {
	for(int f = 1; f < nFolds; f++) {
		fold(folds[f].axis, folds[f].point);
		//printf("Fold: %c = %d | SizeX: %d | SizeY: %d\n", folds[f].axis, folds[f].point, sizeX, sizeY);
		for(int i = 0; i < sizeY; i++) {
			for(int j = 0; j < sizeX; j++) {
				//printf("%c", a[i][j] == 1 ? '#' : '.');
			}
			//printf("\n");
		}
	}
	//printf("\n");
	
	for(int i = 0; i < sizeY; i++) {
		for(int j = 0; j < sizeX; j++) {
			printf("%c", a[i][j] == 1 ? '#' : ' ');
		}
	printf("\n");
	}
}

int main(int argc, char* argv[]) {
	char* fileName = argv[1];
	FILE *in_file = fopen(fileName, "r");
	
	char word[256];
	while(fscanf(in_file, "%s", word) != EOF) {
		//printf("%s\n", word);
		if(strcmp(word, "fold") == 0) {
			// Read fold coord
			char axis;
			int point = 0;
			fscanf(in_file, "%s", word);	// Skip "along"
			fscanf(in_file, "%s", word);	// axis=point
			axis = word[0];
			for(int i = 2; i < strlen(word); i++) {
				point = point * 10 + word[i] - '0';
			}
			folds[nFolds].axis = axis;
			folds[nFolds++].point = point;
			//printf("Fold along %c=%d\n", axis, point);
		}
		else {
			int x = 0, y = 0;
			char *token = strtok(word, ",");
			for(int i = 0; i < strlen(token); i++) {
				x = x * 10 + token[i] - '0';
			}
			token = strtok(NULL, " \n,");
			for(int i = 0; i < strlen(token); i++) {
				y = y * 10 + token[i] - '0';
			}
			a[y][x] = 1;
			if(x > sizeX) {
				sizeX = x;
			}
			if(y > sizeY) {
				sizeY = y;
			}
			//printf("%d, %d\n", x, y);
		}
	}
	sizeX++;
	sizeY++;

	doPartOne();
	doPartTwo();

	for(int i = 0; i < sizeY; i++) {
		for(int j = 0; j < sizeX; j++) {
			//printf("%c", a[i][j] != 0 ? '#' : '.');
		}
		//printf("\n");
	}

	fclose(in_file);
	return 0;
}
