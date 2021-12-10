#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]) {
	char* fileName = argv[1];
	FILE *in_file = fopen(fileName, "r");

	int part1 = 0;	
	char line[512];
	while(fgets(line, sizeof(line), in_file) != NULL) {
		// line holds a line with the puzzle input
		char s[2] = " ";
		s[1] = '\0';
		char *token = strtok(line, s);
		int startOut = 0;
		int f[7];
		char encodings[10][10];
		int index = 0;
		for(int i = 0; i < 7; i++) {
			f[i] = 0;
		}
		while(token != NULL) {
			// token holds the current signal encoding
			int len = strlen(token);
			if(token[len - 1] == '\n') {
				// Removing the new line from the current word
				token[--len] = '\0';
			}			
			if(token[0] == '|') {
				// Output values starting
				startOut = 1;
				printf("Found |: ~%s~\n", token);
			}
			if(startOut == 0) {
				// Input value
				for(int i = 0; i < len; i++) {
					encodings[index][i] = token[i];
				}
				encodings[index][len] = '\0';
				printf("Input val: ~%s~\n", encodings[index]);
				for(int i = 0; i < len; i++) {
					f[token[i] - 'a']++;
				}
				index++;
			}
			// This is only for part one
			else if(token[0] != '|' && (len == 2 || len == 3 || len == 4 || len == 7)){
				printf("~%s~ %ld\n", token, strlen(token));
				part1++;
			}
			token = strtok(NULL, s);
		}
		for(int i = 0; i < 7; i++) {
			char letter = i + 'a';
			printf("%c - %d\n", letter, f[i]);
		}
	}
	
	printf("Answer for Part one: %d\n", part1);

	fclose(in_file);
	return 0;
}
