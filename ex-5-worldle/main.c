#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

const short int NO_ATTEMPTS = 5;
const short int MAX_NO_LETTERS = 10;

void read_incognito(char* string, int string_max_size);
//void discard_input_buffer();
int contains_only_letters(char* s);
void print_asterisk(int how_many);

int main() {

// MAKE UP A WORD PHASE
	printf("Please enter a word (max %i letters)\n", MAX_NO_LETTERS);

	// read the word 
	char* the_word = malloc(sizeof(char)*(MAX_NO_LETTERS + 1)); // char the_word[WORD_SIZE] would be more effective
	printf("\n");
	read_incognito(the_word, MAX_NO_LETTERS + 1);

	// validate it(should be invisible)
	while (!contains_only_letters(the_word) || strlen(the_word) == 0) {  // if entered word is too long, scanf_s() doesn't return anything
		system("cls");
		if (strlen(the_word) == 0) {
			printf("Given word is too long (max length: %i). Let's try again...\n\n", MAX_NO_LETTERS);
		} else if (!contains_only_letters(the_word)) {
			printf("Given word contains forbidden characters. Let's try again...\n\n");
		}
		//discard_input_buffer();
		read_incognito(the_word, MAX_NO_LETTERS + 1);
	}

// GUESS THE WORD PHASE

	char* the_guess = malloc(sizeof(char) * (MAX_NO_LETTERS + 1));

	int attempt = 1;
	while (strcmp(the_word, the_guess) != 0 && attempt <= NO_ATTEMPTS) {
		// display a number of letters (***)
		system("cls");
		printf("The word: ");
		print_asterisk(strlen(the_word));
		printf("\n\n");

		// keep asking until he gets that right
		if (attempt == 1) {
			printf("Enter your guess (%i attempts left): \n", NO_ATTEMPTS - attempt + 1);
		} else {
			printf("You're wrong, try again (%i attempts left): \n", NO_ATTEMPTS - attempt + 1);
		}
		scanf_s("%s", the_guess, (MAX_NO_LETTERS + 1));

		attempt++;
	}

	if (strcmp(the_word, the_guess) == 0) {
		system("cls");
		printf("Congratulations, you've won!!! It took you %i attempt(s) :)\n\n", attempt - 1);
	} else {
		system("cls");
		printf("Better luck next time ;)\n\n");
	}

	free(the_guess);
	free(the_word);
	
	return 0;
}

void read_incognito(char* string, int string_max_size) {
	// returns empty string if word exceeds string_max_size
	char c;
	int i = 0;
	while ((c = _getch()) != '\r' && i < string_max_size - 1) {
		if (c == '\b') { // handle backspace
			printf("\b \b");
			i--;
		} else {
			string[i] = c;
			printf("_");
			i++;
		}
	}
	if (c !='\r') { // if word has more letters than it should, make string empty
		string[0] = '\0';
	} else { 
		string[i] = '\0';
	}
	printf("\n");
}

//void discard_input_buffer() {
//	char c;
//	while ((c = getchar()) != '\n' && c != EOF && c != '\r');
//}

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

void print_asterisk(int how_many) {
	for (int i = 0; i < how_many; i++) {
		putchar('*');
	}
}