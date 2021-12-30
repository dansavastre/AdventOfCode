#include <stdio.h>
#include <string.h>

struct Position {
	int x;
	int y;
};

char a[1001][1001];
int n, m;

int step(int stepX, int stepY, char target) {
	struct Position positions[100001]; 
	int ind = 0;
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			//printf("%c", m[i][j]);
			if(a[i][j] == target) {
				if(a[(i + stepX) % n][(j + stepY) % m] == '.') {
					// This sea cucumber can move this step
					positions[ind++] = (struct Position) {i, j};
					//printf("(%d, %d)\n", i, j);
				}
			}
		}
		//printf("\n");
	}
	for(int i = 0; i < ind; i++) {
		//printf("(%d, %d) -> (%d, %d)\n", positions[i].x, positions[i].y);
		int x = positions[i].x, y = positions[i].y;
		//printf("(%d, %d) -> (%d, %d)\n", x, y, (x + stepX) % n, (y + stepY) % m);
		a[(x + stepX) % n][(y + stepY) % m] = target;
		a[x][y] = '.';
	}
	//printf("\n");
	//for(int i = 0; i < n; i++) {
	//	printf("%s\n", a[i]);
	//}
	//printf("\n");
	return ind == 0;
}

void doPartOne() {
	int partOne = 1;
	int step1 = step(0, 1, '>');
	int step2 = step(1, 0, 'v');
	while(!(step1 && step2)) {
		partOne++;
		step1 = step(0, 1, '>');
		step2 = step(1, 0, 'v');
	}
	printf("Part one: %d\n", partOne);
}

int main(int argc, char* argv[]) {
	char* fileName = argv[1];
	FILE *in_file = fopen(fileName, "r");
	
	while(fscanf(in_file, "%s", a[n++]) != EOF) {
		m = strlen(a[n - 1]);
	}
	n--;
	//printf("n = %d, m = %d\n", n, m);
	fclose(in_file);
	doPartOne();
	return 0;
}
