#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int basin[1001][1001];
int size[1000001];

int cmp(const void * a, const void * b) {
	return ( *(int*)a - *(int*)b );
}

int isLowPoint(int h[1001][1001], int x, int y) {

	for(int i = -1; i < 2; i++) {
		for(int j = -1; j < 2; j++) {
			if((i == 0 || j == 0) && !(i == 0 && j == 0)) {
				if(h[x][y] >= h[x + i][y + j]) {
					return 0;
				}		
			}
		}
	}
	return 1;
}

void traverse(int h[1001][1001], int n, int m, int x, int y, int curr) {
	basin[x][y] = curr;
	size[curr - 1]++;
	for(int i = -1; i < 2; i++) {
		for(int j = -1; j < 2; j++) {
			if((i == 0 || j == 0) && !(i == 0 && j == 0)) {
				if(h[x + i][y + j] < 9 && basin[x + i][y + j] == 0) {
					traverse(h, n, m, x + i, y + j, curr);
				}	
			}
		}
	}
}

int main(int argc, char* argv[]) {
	char* fileName = argv[1];
	FILE *in_file = fopen(fileName, "r");
	
	int part1 = 0;
	int part2 = 1;

	char line[1001];
	int h[1001][1001];
	int n = 1, m = 1;
	int numBasins = 0;

	for(int i = 0; i < 1001; i++) {
		for(int j = 0; j < 1001; j++) {
			h[i][j] = 10;
		}
	}

	while(fgets(line, sizeof(line), in_file)) {
		int len = strlen(line);
		m = len;
		for(int j = 1; j < len; j++) {
			h[n][j] = line[j - 1] - '0';
		}
		n++;
	}
	
	for(int i = 1; i < n; i++) {
		for(int j = 1; j < m; j++) {
			if(isLowPoint(h, i, j)) {
				// Risk level for i is h[i] + 1
				// Low Point found
				part1 += (h[i][j] + 1);
			}
			if(basin[i][j] == 0 && h[i][j] < 9) {
				traverse(h, n, m, i, j, ++numBasins);
			}
		}
	}

	printf("Part 1 answer: %d\n", part1);
	qsort(size, numBasins, sizeof(int), cmp);
	for(int i = numBasins - 1; i > numBasins - 4; i--) {
		part2 *= size[i];
	}
	printf("Part 2 answer: %d\n", part2);
	fclose(in_file);
	return 0;
}
