#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int part1 = 0;
unsigned long long part2 = 0;
int n = 0;
unsigned long long scores[100001];

int cmp(const void * a, void const * b) {
	return ( *(unsigned long long*)a - *(unsigned long long*)b );
}

int isOpenBracket(char ch) {
	if(ch == '(' || ch == '[' || ch == '{' || ch == '<') {
		return 1;
	}
	return 0;
}

int isClosedBracket(char ch) {
	return 1 - isOpenBracket(ch);
}

int isMatch(char a, char b) {
	if((a == '(' && b == ')') ||
	(a == '[' && b == ']') ||
	(a == '{' && b == '}') ||
	(a == '<' && b == '>')) {
		return 1;
	}
	return 0;
}

char assertBrackets(char line[]) {
	int i = 0;
	char v[256];
	int top = 0;
	while(line[i]) {
		if(isOpenBracket(line[i])) {
			v[top++] = line[i];
		}
		else if(isClosedBracket(line[i])) {
			if(top <= 0) {
				return line[i];
			}
			else if(!isMatch(v[top - 1], line[i])) {
				return line[i];
			}
			top--;
		}
		i++;
	}
	part2 = 0;
	printf("%s - ", line);
	for(int i = top - 1; i >= 0; i--) {
		printf("%c", v[i]);
		switch(v[i]) {
			case('('):
				part2 = part2 * 5 + 1;
				break;
			case('['):
				part2 = part2 * 5 + 2;
				break;
			case('{'):
				part2 = part2 * 5 + 3;
				break;
			case('<'):
				part2 = part2 * 5 + 4;
				break;
		}
	}
	scores[n++] = part2;
	printf(" - Part 2: %lld\n", part2);
	return '$';
}

int main(int argc, char* argv[]) {
	char* fileName = argv[1];
	FILE *in_file = fopen(fileName, "r");

	char line[256];
	while(fscanf(in_file, "%s", line) != EOF) {
		char ch = assertBrackets(line);
		//printf("%s - %c\n", line, ch);
		switch(ch) {
			case(')'):
				part1 += 3;
				break;
			case(']'):
				part1 += 57;
				break;
			case('}'):
				part1 += 1197;
				break;
			case('>'):
				part1 += 25137;
				break;
		}
	}
	qsort(scores, n, sizeof(unsigned long long), cmp);
	for(int i = 0; i < n; i++) {
		printf("%d - %lld\n", i, scores[i]);
	}

	printf("Part 1: %d\nPart 2: %lld\n", part1, scores[n / 2]);

	fclose(in_file);
	return 0;
}
