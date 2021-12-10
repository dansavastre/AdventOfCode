#include <stdio.h>
#include <string.h>

int parseInt(char s[]) {
	int result = 0;
	int len = strlen(s);
	for(int i = 0; i < len; i++) {
		result = result * 10 + s[i] - '0';
	}
	return result;
} 

int absDiff(int a, int b) {
	return a < b ? b - a : a - b;
}

int wtDiff(int a, int b) {
	return a < b ? (b - a) * (b - a + 1) / 2 : (a -b) * (a - b + 1) / 2;
}

int min(int a, int b) {
	return a < b ? a : b;
} 

int max(int a, int b) {
	return a > b ? a : b;
}

int main(int argc, char* argv[]) {
	char* fileName = argv[1];
	FILE *in_file = fopen(fileName, "r");
	
	char numString[100001];
	fscanf(in_file, "%s", numString);

	char *token;
	 char s[2] = ",";
	s[1] = '\0';

	int n = 0;
	unsigned long v[100000];
	unsigned long cost[100000];
	unsigned long minn = 100000, maxx = 0;
	token = strtok(numString, s);
	while(token != NULL) {
		v[n++] = parseInt(token);
		minn = min(minn, v[n - 1]);
		maxx = max(maxx, v[n - 1]);
		token = strtok(NULL, s);
	}

	unsigned long minCost = 1e8;
	int minCostPos = -1;
	for(int i = minn; i < maxx; i++) {
		cost[i] = 0;
		for(int j = 0; j < n; j++) {
			//For part 1:
			//int diff = absDiff(v[j], i);

			int diff = wtDiff(v[j], i);
			cost[i] += diff;
		}
		if(minCost > cost[i]) {
			minCost = cost[i];
			minCostPos = i;
		}
		printf("Cost for %d is %lu\n", i, cost[i]);
	}
	printf("\nMinimal cost is %lu at position %d\n", minCost, minCostPos);

	fclose(in_file);
	return 0;
}
