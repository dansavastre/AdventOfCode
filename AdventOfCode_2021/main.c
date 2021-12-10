#include <stdio.h>

int main(int argc, char* argv[]) {
	char* fileName = argv[1];
	FILE *in_file = fopen(fileName, "r");
	
	int n;
	while(fscanf(in_file, "%d", n) != EOF) {
		printf("%n\n", n);
	}

	fclose(in_file);
	return 0;
}
