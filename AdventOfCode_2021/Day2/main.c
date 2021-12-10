#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]) {
	char* fileName = argv[1];
	FILE *in_file = fopen(fileName, "r");
	
	int x = 0, y = 0, aim = 0;
	int n;
	char* str;
	while(fscanf(in_file, "%s %d", str, &n) != EOF) {
		if(strcmp(str, "forward") == 0) {
			x += n;
			y += (aim * n);
		}
		else if(strcmp(str, "down") == 0) {
			aim += n;
		}
		else if(strcmp(str, "up") == 0) {
			aim -= n;
		}
	}
	printf("Coordinates are (%d, %d), and the product is %d\n", x, y, x * y);
	fclose(in_file);
	return 0;
}
