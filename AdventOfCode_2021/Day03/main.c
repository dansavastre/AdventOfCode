#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]) {
	char* fileName = argv[1];
	FILE *in_file = fopen(fileName, "r");
	
	int len = 12;
	int n = 1000;
	char str[n][len + 1];
	int index = 0;
	int oxygen[n];
	int oind = 0;
	char lookingFor = '1';
	int ones = 0;
	int zeros = 0;

	while(fscanf(in_file, "%s", str[index]) != EOF) {
		if(str[index][0] == '1') {
			ones++;
		}
		else {
			zeros++;
		}
		
		oxygen[oind++] = index;
		index++;
	}

	char o2rating[len + 1];	
	for(int i = 0; i < len; i++) {
		printf("Number of elements: %d\n", oind);

		if(zeros <= ones) {
			lookingFor = '0';
		}
		else {
			lookingFor = '1';
		}
		o2rating[i] = lookingFor;
		printf("\nLooking for %c at position %d:\n", lookingFor, i);
		int aux = 0;
		zeros = 0;
		ones = 0;
		for(int j = 0; j < oind; j++) {
			//Check all numbers to see if they have lookingFor on position i
				
			if(str[oxygen[j]][i] == lookingFor) {
				oxygen[aux++] = oxygen[j];
				printf("str[%d]: %s has %c at position %d ", oxygen[j], str[oxygen[j]], lookingFor, i);
				printf("correct\n");
				if(str[oxygen[j]][i+1] == '0') {
					zeros++;
				}
				else {
					ones++;
				}
			}
		}
		oind = aux;
		if(oind == 1) {
			//o2rating = str[oxygen[0]];
			for(int i = 0; i < len; i++) {
				o2rating[i] = str[oxygen[0]][i];
			}
			break;
		}
	}
	printf("O2 rating: %s\n", o2rating);
	int ans = 0;
	int pow = 1;
	for(int i = len - 1; i >= 0; i--) {
		ans += pow * (o2rating[i] - '0');
		pow *= 2;	
	}
	printf("Decimal: %d\n", ans);
	fclose(in_file);
	return 0;
}
