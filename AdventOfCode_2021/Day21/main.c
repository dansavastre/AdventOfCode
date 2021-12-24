#include <stdio.h>
#include <string.h>

int startPos1 = 0;
int startPos2 = 0;

int min(int a, int b) {
	return a < b ? a : b;
}

void playTo1000(int pos1, int pos2) {
	int score1 = 0;
	int score2 = 0;
	int dice = 1;
	int of = 0;
	while(score1 < 1000 && score2 < 1000) {
		pos1 = (pos1 +  (3 * dice + 3));
		if(pos1 > 10) {
			pos1 = pos1 % 10;
			if(pos1 == 0) {
				pos1 = 10;
			}
		}
		score1 += pos1;
		dice += 3;
		if(dice > 100) {
			dice %= 100;
			of++;
		}
		if(score1 >= 1000) {
			break;
		}

		pos2 = (pos2 + (3 * dice + 3));
		if(pos2 > 10) {
			pos2 = pos2 % 10;
			if(pos2 == 0) {
				pos2 = 10;
			}
		}
		score2 += pos2;
		dice += 3;
		if(dice > 100) {
			dice %= 100;
			of++;
		}

		//printf("%d - %d\n", score1, score2);
	}
	//printf("Game over: %d - %d; Dice: %d\n", score1, score2, 100 * of + dice - 1);
	printf("Part one: %d\n", min(score1, score2) * (100 * of + dice - 1));
}

int main(int argc, char* argv[]) {
	char* fileName = argv[1];
	FILE *in_file = fopen(fileName, "r");
	
	char line[255];
	fscanf(in_file, "%s\n", line); // Player
	fscanf(in_file, "%s\n", line); // player number
	fscanf(in_file, "%s\n", line); // starting
	fscanf(in_file, "%s\n", line); // position:
	fscanf(in_file, "%s\n", line); // The starting position
	//printf("%d\n", line[strlen(line) - 1] - '0');
	startPos1 = line[strlen(line) - 1] - '0';

	fscanf(in_file, "%s\n", line); // Player
	fscanf(in_file, "%s\n", line); // player number
	fscanf(in_file, "%s\n", line); // starting
	fscanf(in_file, "%s\n", line); // position:
	fscanf(in_file, "%s\n", line); // The starting position
	//printf("%d\n", line[strlen(line) - 1] - '0');
	startPos2 = line[strlen(line) - 1] - '0';

	// Part one
	playTo1000(startPos1, startPos2);

	fclose(in_file);
	return 0;
}
