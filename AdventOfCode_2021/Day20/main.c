#include <stdio.h>
#include <string.h>

char filter[513];
int a[1001][1001];
int newA[1001][1001];
int minI = 100;
int minJ = 100;
int maxI = 100;
int maxJ = 100;
int newMinI, newMinJ, newMaxI, newMaxJ;

int min(int a, int b) {
	return a < b ? a : b;
}

int max(int a, int b) {
	return a > b ? a : b;
}

void applyFilter(int x, int y, int step) {
	int sum = 0;
	for(int i = x - 1; i <= x + 1; i++) {
		for(int j = y - 1; j <= y + 1; j++) {
			if(x >= minI && x < maxI && y >= minJ && y < maxJ) {
				sum = (sum << 1);
				sum |= a[i][j];
				//printf("%d", a[i][j]);
			}
			else {
				sum = (sum << 1);
				sum |= (1 - step % 2);
			}
		}
		//printf("\n");
	}
	//printf("For (%d, %d) out is %d -> f = %d\n\n", x - minI, y - minJ, sum, filter[sum] == '#' ? 1 : 0);
	newA[x][y] = filter[sum] == '#' ? 1 : 0;
}

void enhance(int step) {
	for(int i = 2; i < 999; i++) {
		for(int j = 2; j < 999; j++) {
			applyFilter(i, j, step);
			//printf("apply for (%d, %d)")
		}
	}
	
	//Enhance borders
	for(int i = minI - 1; i < maxI + 1; i++) {
		// a[i][minJ-1] && a[i][maxJ]
		applyFilter(i, minJ - 1, 1);
		applyFilter(i, maxJ, 1);
	}
	for(int j = minJ - 1; j < maxJ + 1; j++) {
		// a[minI - 1][j] && a[maxI][j]
		applyFilter(minI - 1, j, 1);
		applyFilter(maxI, j, 1);
	}
	printf("	  minI = %d, minJ = %d, maxI = %d, maxJ = %d\n", minI, minJ, maxI, maxJ);
	printf("New vals: minI = %d, minJ = %d, maxI = %d, maxJ = %d\n", newMinI, newMinJ, newMaxI, newMaxJ);


//	minI = newMinI;
//	minJ = newMinJ;
//	maxI = newMaxI;
//	maxJ = newMaxJ;
	minI--;
	minJ--;
	maxI++;
	maxJ++;

	printf("Enhanced image: \n");
	for(int i = minI; i < maxI; i++) {
		for(int j = minJ; j < maxJ; j++) {
			printf("%s", newA[i][j] == 1 ? "#" : ".");
			a[i][j] = newA[i][j];
		}
		printf("\n");
	}
}

void doPartOne() {
	int partOne = 0;
	// Do 2 enhancements
	enhance(1);
	enhance(2);
	for(int i = minI; i < maxI; i++) {
		for(int j = minJ; j < maxJ; j++) {
			partOne += a[i][j];
		}
	}
	printf("\nPart one: %d\n", partOne);
}

int main(int argc, char* argv[]) {
	char* fileName = argv[1];
	FILE *in_file = fopen(fileName, "r");
	
	fscanf(in_file, "%s", filter);
	
	char line[101];	
	//fscanf(in_file, "%s", line);
	while(fscanf(in_file, "%s", line) != EOF) {
		for(int i = 0; i < strlen(line); i++) {
			a[maxI][minJ + i] = line[i] == '#' ? 1 : 0;
		}
		maxI++;
		maxJ = minJ + strlen(line);
		printf("%s\n", line);
	}

	//for(int i = minI; i < maxI; i++) {
	//	for(int j = minJ; j < maxJ; j++) {
	//		printf("%d ", a[i][j]);
	//	}
	//	printf("\n");
	//}
	
	//printf("(%d, %d) -> (%d, %d)\n", minI, minJ, maxI, maxJ);
	doPartOne();

	fclose(in_file);
	return 0;
}
