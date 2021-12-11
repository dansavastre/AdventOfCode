#include <stdio.h>
#include <string.h>

int outInd = 0;
int startOut = 0;
char encodedOut[10][10];
int part2 = 0;

int check_0(char s[]) {
	if(strlen(s) == 6 && strchr(s, 'a') != NULL && strchr(s, 'b') != NULL && strchr(s, 'c') != NULL && 
	strchr(s, 'e') != NULL && strchr(s, 'f') != NULL && strchr(s, 'g')) {
		return 1;
	}
	return 0;
}

int check_1(char s[]) {
	if(strlen(s) == 2 && strchr(s, 'c') != NULL && strchr(s, 'f') != NULL) {
		return 1;
	}
	return 0;
}

int check_2(char s[]) {
	if(strlen(s) == 5 && strchr(s, 'a') != NULL && strchr(s, 'c') != NULL && strchr(s, 'd') != NULL && 
	strchr(s, 'e') != NULL && strchr(s, 'g')) {
		return 1;
	}
	return 0;
}

int check_3(char s[]) {
	if(strlen(s) == 5 && strchr(s, 'a') != NULL && strchr(s, 'c') != NULL && strchr(s, 'd') != NULL && 
	strchr(s, 'f') != NULL && strchr(s, 'g')) {
		return 1;
	}
	return 0;
}

int check_4(char s[]) {
	if(strlen(s) == 4 && strchr(s, 'b') != NULL && strchr(s, 'c') != NULL && strchr(s, 'd') != NULL && 
	strchr(s, 'f') != NULL) {
		return 1;
	}
	return 0;
}

int check_5(char s[]) {
	if(strlen(s) == 5 && strchr(s, 'a') != NULL && strchr(s, 'b') != NULL && strchr(s, 'd') != NULL && 
	strchr(s, 'f') != NULL && strchr(s, 'g')) {
		return 1;
	}
	return 0;
}

int check_6(char s[]) {
	if(strlen(s) == 6 && strchr(s, 'a') != NULL && strchr(s, 'b') != NULL && strchr(s, 'd') != NULL && 
	strchr(s, 'e') != NULL && strchr(s, 'f') != NULL && strchr(s, 'g')) {
		return 1;
	}
	return 0;
}

int check_7(char s[]) {
	if(strlen(s) == 3 && strchr(s, 'a') != NULL && strchr(s, 'c') != NULL && strchr(s, 'f') != NULL) {
		return 1;
	}
	return 0;
}

int check_8(char s[]) {
	if(strlen(s) == 7 && strchr(s, 'a') != NULL && strchr(s, 'b') != NULL && strchr(s, 'c') != NULL && 
	strchr(s, 'd') != NULL && strchr(s, 'e') && strchr(s, 'f') != NULL && strchr(s, 'g') != NULL) {
		return 1;
	}
	return 0;
}

int check_9(char s[]) {
	if(strlen(s) == 6 && strchr(s, 'a') != NULL && strchr(s, 'b') != NULL && strchr(s, 'c') != NULL && 
	strchr(s, 'd') != NULL && strchr(s, 'f') && strchr(s, 'g') != NULL) {
		return 1;
	}
	return 0;
}

int findNumber(char s[]) {
	if(check_0(s)) return 0;
	if(check_1(s)) return 1;
	if(check_2(s)) return 2;
	if(check_3(s)) return 3;
	if(check_4(s)) return 4;
	if(check_5(s)) return 5;
	if(check_6(s)) return 6;
	if(check_7(s)) return 7;
	if(check_8(s)) return 8;
	if(check_9(s)) return 9;
}


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
		startOut = 0;
		int f[7];
		char encodings[10][10];
		//char encodedOut[10][10];
		int index = 0;
		//int outInd = 0;
		outInd = 0;
		int key[7];

		for(int i = 0; i < 7; i++) {
			f[i] = 0;
			key[i] = 0;
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
				//printf("Found |: ~%s~\n", token);
			}
			else if(startOut == 0) {
				// Input value
				strncpy(encodings[index], token, len);
				encodings[index++][len] = '\0';
				//printf("Input val: ~%s~\n", encodings[index - 1]);
				for(int i = 0; i < len; i++) {
					f[token[i] - 'a']++;
				}
			}
			if(startOut == 1 && token[0] != '|') {
				// Value to be decoded
				strncpy(encodedOut[outInd], token, len);
				encodedOut[outInd++][len] = '\0';
				//printf("~%s~\n", encodedOut[outInd - 1]);
			}
			// This is only for part one
			if(startOut == 1 && token[0] != '|' && (len == 2 || len == 3 || len == 4 || len == 7)){
				//printf("~%s~ %ld\n", token, strlen(token));
				part1++;
			}
			token = strtok(NULL, s);
		}
		int foundD = 0;
		int foundC = 0;
		for(int i = 0; i < 7; i++) {
			char letter = i + 'a';
			//printf("%c - %d\n", letter, f[i]);
			switch(f[i]) {
				case(4):
					// e(4) has frequency 4
					key[i] = 4;
					break;
				case(6):
					// b(1) has frequency 6
					key[i] = 1;
					break;
				case(7):
					// d(3) and g(6) both have frequency 7
					for(int j = 0; j < index; j++) {
						if(strlen(encodings[j]) == 4) {
							// Encoding of 4 has 4 letters and
							// should only contain one letter(d) with frequency 7
							for(int k = 0; k < strlen(encodings[j]); k++) {
								//printf("f[%c] = %d - Looking for: %c\n", encodings[j][k], f[encodings[j][k] - 'a'], letter);
								if(f[encodings[j][k] - 'a'] != 7) {
									continue;
								}
								if(f[encodings[j][k] - 'a'] == 7 && encodings[j][k] == letter) {
									key[i] = 3;
									break;
								}
								else {
									key[i] = 6;
									break;
								}
							}
						}
					}
					break;
				case(8):
					// a(0) and c(2) both have frequency 8
					for(int j = 0; j < index; j++) {
						if(strlen(encodings[j]) == 4) {
							// Encoding of 4 has 4 letters and
							// should only contain one letter(c) with frequency 8
							for(int k = 0; k < strlen(encodings[j]); k++) {
								if(f[encodings[j][k] - 'a'] != 8) {
									continue;
								}
								if(f[encodings[j][k] - 'a'] == 8 && encodings[j][k] == letter) {
									key[i] = 2;
									break;
								}
								else {
									key[i] = 0;
									break;
								}
							}
						}
					}
					break;
				case(9):
						// f(5) has frequency 9
					key[i] = 5;
					break;
			}
		}

		//for(int i = 0; i < 7; i++) {
		//	printf("key %c - %d\n", i + 'a', key[i]);
		//}
		// Decoding part 2
		int display = 0;
		for(int i = 0; i < outInd; i++) {
			char decoded[10];
			for(int j = 0; j < strlen(encodedOut[i]); j++) {
				int ind = (int)(encodedOut[i][j] - 'a');
				decoded[j] = key[ind] + 'a';
				//printf("%c\n", key[encodedOut[i][j] - 'a'] + 'a');
			}
			decoded[strlen(encodedOut[i])] = '\0';
			display = display * 10 + findNumber(decoded);
			//printf("%s -> %s -> %d\n", encodedOut[i], decoded, findNumber(decoded));
		}
		part2 += display;
		//printf("\n");
	}
	
	printf("Answer for Part one: %d\n", part1);
	printf("Answer for Part two: %d\n", part2);
	fclose(in_file);
	return 0;
}
