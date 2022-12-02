#include <stdio.h>
#include <string.h>
#include <stdlib.h>

unsigned long f[9];

int parseInt(char s[]) {
	int ans = 0;
	int len = strlen(s);
	for(int i = 0; i < len; i++) {
		ans = ans * 10 + s[i] - '0';
	}
	return ans;
}

int main(int argc, char* argv[]) {
	char* fileName = argv[1];
	FILE *in_file = fopen(fileName, "r");
	
	char *token;
	char s[2] = ",";
	s[1] = '\0';
	
	char numstring[1001];
	fscanf(in_file, "%s", numstring);

	//unsigned long f[9];
	token = strtok(numstring, s);
	while(token != NULL) {
		f[parseInt(token)]++;
		token = strtok(NULL, s);
	}

	for(int day = 1; day <= 256; day++) {
		int newFish = 0;
		unsigned long aux = f[0];
		for(int i = 1; i < 9; i++) {
			f[i - 1] = f[i];
		}
		f[6] += aux;
		f[8] = aux;

		printf("Day %d: ", day);
		for(int i = 0; i < 9; i++) {
			printf("%lu ", f[i]);
		}
		printf("\n");
	}
	unsigned long ans = 0;
	for(int i = 0; i < 9; i++) {
		ans += f[i];
	}	
	printf("Number of fish after 256 days: %lu\n", ans);
	fclose(in_file);
	return 0;
}
