#include <stdio.h>
#include <string.h>

int a[1000][1000];
int visited[1000][1000];
int cost[1000][1000];
int n, m;

struct position {
	int i;
	int j;
};
struct position q[10000001];

void rebase(int front, int back) {
	for(int i = front; i < back; i++) {
		q[i - front] = q[i];
	}
}

void lee() {
	int back = 0;
	int front = -1;
	q[back].i = 0;	
	q[back++].j = 0;
	cost[0][0] = a[0][0];
	while(front <= back) {
		front++;
		if(back >= 10000000) {
			// Reset q to index 0
			printf("Rebasing\n");
			rebase(front, back);
			back = back - front;
			front = 0;
		}
		int i = q[front].i;
		int j = q[front].j;
		printf("%d - i = %d | j = %d - %d\n", front, i, j, back);
		//if()
		if(i >= n || j >= m) {
			front++;
			continue;
		}
		visited[i][j] = 1;
		if(!visited[i + 1][j]) {
			if(	cost[i + 1][j] == 0 || 
				cost[i + 1][j] > cost[i][j] + a[i + 1][j]) {
				cost[i + 1][j] = cost[i][j] + a[i + 1][j];
			}
			q[back].i = i + 1;
			q[back++].j = j;
			//visited[i + 1][j] = 1;
		}
		if(!visited[i][j + 1]) {
			if(	cost[i][j + 1] == 0 || 
				cost[i][j + 1] > cost[i][j] + a[i][j + 1]) {
				cost[i][j + 1] = cost[i][j] + a[i][j + 1];
			}
			q[back].i = i;
			q[back++].j = j + 1;
			//visited[i][j + 1] = 1;
		}


	}
}

int main(int argc, char* argv[]) {
	char* fileName = argv[1];
	FILE *in_file = fopen(fileName, "r");
	
	char line[1001];
	while(fscanf(in_file, "%s", line) != EOF) {
		//printf("%s\n", line);
		m = strlen(line);
		for(int j = 0; j < m; j++) {
			a[n][j] = line[j] - '0';
		}
		n++;
	}

	lee();

	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			printf("%d ", cost[i][j]);
		}
		printf("\n");
	}
	fclose(in_file);
	return 0;
}
