#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include <conio.h> 

const short int NO_ATTEMPTS = 5;
const short int MAX_NO_LETTERS = 10;

//void read_incognito(char* string, int string_max_size);
void discard_input_buffer();
int contains_only_letters(char* s);

int main() {

// MAKE UP A WORD PHASE
	printf("Please enter a word (max %i letters)\n", MAX_NO_LETTERS);

	// read that word 
	char* the_word = malloc(sizeof(char)*(MAX_NO_LETTERS + 1));
	scanf_s("%s", the_word, MAX_NO_LETTERS + 1);

	//read_incognito(the_word, MAX_NO_LETTERS + 1);

	////validate it(should be invisible)
	//while (!contains_only_letters(the_word) || strlen(the_word) > MAX_NO_LETTERS) {  // if entered word is too long, scanf_s() doesn't return anything
	//	if (strlen(the_word) > MAX_NO_LETTERS) {
	//		printf("Given word is too long. Let's try again...\n");
	//	} else if (!contains_only_letters(the_word)) {
	//		printf("Given word contains forbidden characters. Let's try again...\n");
	//	}
	//	discard_input_buffer();
	//	read_incognito(the_word, MAX_NO_LETTERS + 1);
	//}

	//validate it(should be invisible)
	while (!contains_only_letters(the_word) || strlen(the_word) == 0) {  // if entered word is too long, scanf_s() doesn't return anything
		if (strlen(the_word) == 0) {
			printf("Given word is too long. Let's try again...\n");
		} else if (!contains_only_letters(the_word)) {
			printf("Given word contains forbidden characters. Let's try again...\n");
		}
		discard_input_buffer();
		scanf_s("%s", the_word, MAX_NO_LETTERS + 1);
	}

// GUESS THE WORD PHASE
	// display a number of letters (***)

	// keep asking until he gets that right

	free(the_word);

	return 0;
}

//void read_incognito(char* string, int string_max_size) {
//	char c;
//	int i = 0;
//	while ((c = _getch()) != '\r' && i < string_max_size - 1) {
//		if (c == '\b') { // handle backspace
//			printf("\b \b");
//			i--;
//		} else {
//			string[i] = c;
//			printf("_");
//			i++;
//		}
//	}
//	string[i] = '\0';
//	if (true) {
//
//	}
//}

void discard_input_buffer() {
	char c;
	while ((c = getchar()) != '\n' && c != EOF);
}

int contains_only_letters(char* s) {
	int contains_only_letters = 1;
	while ( *s != '\0') {
		if (!isalpha(*s)) {
			contains_only_letters = 0;
		}
		s++;
	}
	return contains_only_letters;
}
