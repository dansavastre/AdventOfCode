#include <stdio.h>

int main(int argc, char* argv[]) {
	char* fileName = argv[1];
	FILE *in_file = fopen(fileName, "r");
	int a, b, c;
	int num, prev;
	int ans = 0;
	int i = 1;
	fscanf(in_file, "%d\n%d\n%d", &a, &b, &c);
	prev = a + b + c;
	a = b;
	b = c;
	while(fscanf(in_file, "%d", &c) != EOF) {
		printf("i = %d, n = %d\n", i, a + b + c);
		num = a + b + c;
		if(num > prev) {
			ans++;
		}
		prev = num;
		a= b;
		b = c;
		i++;
	}
	fclose(in_file);
	printf("%d\n", ans);
	return 0;
}
