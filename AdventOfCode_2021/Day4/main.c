#include <stdio.h>
#include <string.h>

struct table {
	int completed;
	int mat[5][5];
	int found[5][5];
} tables[101];

int completed = 0;




int parseNumber(char s[]) {
	int n = strlen(s);
	int result = 0;
	for(int i = 0; i < n; i++) {
		result = result * 10 + s[i] - '0';
	}
	return result;
}

int checkTable(int tableIndex) {
	for(int i = 0; i < 5; i++) {
		int sumRow = 0;
		int sumCol = 0;
		for(int j = 0; j < 5; j++) {
			sumRow += tables[tableIndex].found[i][j];
			sumCol += tables[tableIndex].found[j][i];	
		}
		if(sumRow == 5 || sumCol == 5) {
			return 1;
		}
	}
	return 0;
}

int checkWinCondition(int numTables) {
	int ans = 0;
	int result = -1;
	
	for(int i = 0; i <= numTables; i++) {
		if(tables[i].completed == 0) {
			ans = checkTable(i);
			if(ans == 1) {
				result = i;
				tables[i].completed = ++completed;
				printf("%d: completed table %d\n", completed, i);
			}
		}
	}
	return result;
}

void fillTables(int number, int tableNumbers) {
	for(int t = 0; t <= tableNumbers; t++) {
		for(int i = 0; i < 5; i++) {
			for(int j = 0; j < 5; j++) {
				if(tables[t].mat[i][j] == number) {
					tables[t].found[i][j] = 1;
				}
			}
		}
	}
}

int calculateResult(int number, int winner) {
	int result = 0;
	for(int i = 0; i < 5; i++) {
		for(int j = 0; j < 5; j++) {
			if(tables[winner].found[i][j] == 0) {
				result += tables[winner].mat[i][j];
			}	
		}
	}
	return result * number;
}


int main(int argc, char* argv[]) {
	char* fileName = argv[1];
	FILE *in_file = fopen(fileName, "r");
	
	if(in_file == NULL) {
		printf("File not found. Exited program");
		return 0;
	}
	int numbers[512];
	int n = 0;

	char *token;
	char comma[2] = ",";
	comma[1] = '\0';

	char numString[512];
	
	fscanf(in_file, "%s", numString);
	token = strtok(numString, comma);
	
	while(token != NULL) {
		// Token is string that holds a number
		
		int len = strlen(token);
		numbers[n] = parseNumber(token); 
		token = strtok(NULL, comma);
		n++;
	}

	int numTables = 0;
	int index = 0;

	while(fscanf(in_file, "%s", numString) != EOF) {	
		if(index == 25) {
			index = 0;
			numTables++;
		}
		int len = strlen(numString);
		tables[numTables].mat[index / 5][index % 5] = parseNumber(numString);
		index++;
	}	
	index = 0;

	// Play bingo
	int winner = -1;
	int flag = 0;
	
	while(completed <= numTables && index < n) {
		fillTables(numbers[index++], numTables);
		winner = checkWinCondition(numTables);
		
		if(winner != -1 && flag == 0) {
			flag = 1;
			printf("Winner is %d, Part one answer: %d\n", winner, calculateResult(numbers[index - 1], winner));			
		}
	}
	// Completed all tables
	for(int i = 0; i <= numTables; i++) {
		if(tables[i].completed == numTables + 1) {
			printf("Result for table %d is %d\n", i, calculateResult(numbers[index - 1], i));
		}
	}

	fclose(in_file);
	return 0;
}
