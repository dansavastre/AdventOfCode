#include <stdio.h>

struct coordinates {
	int x1, x2, y1, y2;
} coords[1001];

int mat[1001][1001];

int min(int x, int y) {
	return x <= y ? x : y;
}

int max(int x, int y) {
	return x > y ? x : y;
}

void updateMapX(int x, int a, int b) {
	for(int i = a; i <= b; i++) {
		mat[x][i]++;
	}
}

void updateMapY(int y, int a, int b) {
	for(int i = a; i <= b; i++) {
		mat[i][y]++;
	}
}

void updateMapDiag(int x1, int y1, int x2, int y2) {
	if(x1 < x2) {
		int sign = y1 < y2 ? 1 : -1;
		int j = y1;
		for(int i = x1; i <= x2; i++) {
			printf("%d %d\n", i, j);
			mat[i][j]++;
			j += sign;
		}
	}
	else  {
		int sign = y2 < y1 ? 1 : -1;
		int j = y2;		
		for(int i = x2; i <= x1; i++) {
			printf("%d %d\n", i, j);
			mat[i][j]++;
			j += sign;
		}
	}
}

int main(int argc, char* argv[]) {
	char* fileName = argv[1];
	FILE *in_file = fopen(fileName, "r");
	
	int x1, y1, x2, y2;
	int n = 0, m = 0;
	int nCoords = 0;
	while(fscanf(in_file, "%d,%d -> %d,%d", &x1, &y1, &x2, &y2) != EOF) {
		coords[nCoords].x1 = x1;
		coords[nCoords].x2 = x2;
		coords[nCoords].y1 = y1;
		coords[nCoords++].y2 = y2;		
		n = max(max(n, x1), x2);
		m = max(max(m, y1), y2);
		
	}
	for(int i = 0; i < nCoords; i++) {
		//printf("%d, %d -> %d, %d\n", coords[i].x1, coords[i].y1, coords[i].x2, coords[i].y2);
		if(coords[i].x1 == coords[i].x2) {
			if(coords[i].y1 < coords[i].y2) {
				updateMapX(coords[i].x1, coords[i].y1, coords[i].y2);
			}
			else {
				updateMapX(coords[i].x1, coords[i].y2, coords[i].y1);
			}
		}
		else if(coords[i].y1 == coords[i].y2){
			if(coords[i].x1 < coords[i].x2) {
				updateMapY(coords[i].y1, coords[i].x1, coords[i].x2);
			}
			else {
				updateMapY(coords[i].y1, coords[i].x2, coords[i].x1);
			}
		}
		else {
			printf("%d, %d -> %d, %d\n", coords[i].x1, coords[i].y1, coords[i].x2, coords[i].y2);	
			updateMapDiag(coords[i].x1, coords[i].y1, coords[i].x2, coords[i].y2);
		}
	}

	int ans = 0;

	for(int i = 0; i <= n; i++) {
		for(int j = 0; j <= m; j++) {
			if(mat[j][i] > 1) {
				ans++;
			}
			printf("%d ", mat[j][i]);
		}
		printf("\n");
	}

	printf("Part one answer: %d\n", ans);
	fclose(in_file);
	return 0;
}
