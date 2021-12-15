#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]) {
	char* fileName = argv[1];
	FILE *in_file = fopen(fileName, "r");
	
	char line[256];
	char s[2];
	s[0] = '-';
	s[1] = '\0';
	while(fscanf(in_file, "%s", line) != EOF) {
		char *token;
		token = strtok(line, s);
		char from[10];
	       	strcpy(from, token);
		token = strtok(NULL, s);
		char to[10];
		strcpy(to, token);

		printf("From %s to %s\n", from, to);
	}

	fclose(in_file);
	return 0;
}
