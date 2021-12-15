#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Rule {
	char initial[3];
	char toAdd[2];
	unsigned long long freq;
	unsigned long long newFreq;
	int inc1, inc2;
};

unsigned long long f[30];

int cmp(const void * a, const void * b) {
	return ( *(int*)a - *(int*)b );	
}

void printResult(unsigned long long f[], struct Rule rules[], char template[], int n, int part) {
	f[template[0] - 'A']++;
	for(int i = 0; i < n; i++) {
		f[rules[i].initial[1] - 'A'] += rules[i].freq;
	}

	unsigned long long min = 3619835880592;
	unsigned long long max = 0;
	for(int i = 0; i < n; i++) {
		if(f[i] > max) {
			max =f[i];
		}
		if(f[i] < min && f[i] != 0) {
			min = f[i];
		}
	}
	printf("Part %d: %lld\n", part, max - min);
	f[template[0] - 'A']--;
}

void doPart(char template[], struct Rule rules[], int n, int part) {
	int size = part == 1 ? 10 : 40;
	int len = strlen(template);
	for(int i = 0; i < n; i++) {
		rules[i].freq = 0;
		rules[i].newFreq = 0;
	}
	for(int i = 0; i < 30; i++) {
		f[i] = 0;
	}
	for(int i = 0; i < len - 1; i++) {
		char sub[3];
		strncpy(sub, template + i, 2);
		sub[2] = '\0';
		for(int j = 0; j  < n; j++) {
			if(strcmp(rules[j].initial, sub) == 0) {
				rules[j].freq++;
			}
		}
	}
	for(int j = 0; j < n; j++) {
		char find1[3];
		char find2[3];
		
		find1[0] = rules[j].initial[0];
		find1[1] = rules[j].toAdd[0];
		find1[2] = '\0';	

		find2[0] = rules[j].toAdd[0];
		find2[1] = rules[j].initial[1];
		find2[2] = '\0';
				
		for(int k = 0; k < n; k++) {
			if(strcmp(find1, rules[k].initial) == 0) {
				rules[j].inc1 = k;
			}
			if(strcmp(find2, rules[k].initial) == 0) {
				rules[j].inc2 = k;
			}
		}
	}
	
	// We have initial frequency of pairs
	for(int step = 0; step < size; step++) {
		for(int i = 0; i < n; i++) {
			rules[i].newFreq = 0;
		}
		for(int i = 0; i < n; i++) {
			if(rules[i].freq > 0) {
				//printf("%s - %lld\n", rules[i].initial, rules[i].freq);
				// AB C -> AC/CB
				rules[rules[i].inc1].newFreq += rules[i].freq;
				rules[rules[i].inc2].newFreq += rules[i].freq;
			}
		}
		for(int i = 0; i < n; i++) {
			rules[i].freq = rules[i].newFreq;
		}
	}
	printResult(f, rules, template, n, part);
}

int main(int argc, char* argv[]) {
	char* fileName = argv[1];
	FILE *in_file = fopen(fileName, "r");
	
	struct Rule rules[10000];
	char template[100000];	
	char from[3], to[2];
	int n = 0;

	fscanf(in_file, "%s", template);
	while(fscanf(in_file, "%s -> %s", from, to) != EOF) {
		//printf("%s -> %s\n", from, to);
		strncpy(rules[n].initial, from, strlen(from));
		strncpy(rules[n].toAdd, to, strlen(to));
		rules[n].initial[strlen(from)] = '\0';
		rules[n].toAdd[strlen(to)] = '\0';
		n++;
	}
	
	doPart(template, rules, n, 1); 
	doPart(template, rules, n, 2);

	fclose(in_file);
	return 0;
}
