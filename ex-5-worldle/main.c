#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

const char* GREEN = "[0;32m";
const char* YELLOW = "[0;33m";
const short int NO_ATTEMPTS = 7; 
const short int MAX_NO_LETTERS = 10;

char* make_up_word();
void print_the_results(char* the_word, char* the_guess, int* attempts_p);
char* ask_for_the_word();
void validate_word(char* the_word);

char* keep_guessing(char* the_word, int* attempts);

void validate_guess(char* the_guess, char* the_word);

void display_guessing_screen(char* the_word, int* attempts, char* the_guess);

void read_word_incognito(char* string, int string_max_size);
int contains_only_letters(char* s);
int is_in_word(char letter, char* word);
void print_asterisks(int how_many);
void print_in_color(char letter, char* color_code);
void print_colored_word(char* the_word, char* the_guess, int word_size);
//void discard_input_buffer();

int main() {

// MAKE UP A WORD PHASE
	char* the_word = make_up_word();

// GUESS THE WORD PHASE
	int attempts = 0;
	int* attempts_p = &attempts;
	char* the_guess = keep_guessing(the_word, attempts_p);

// PRINT THE RESULTS PHASE
	print_the_results(the_word, the_guess, attempts_p);

	free(the_guess);
	free(the_word);

	return 0;
}





char* make_up_word() {
	char* the_word = ask_for_the_word();
	validate_word(the_word);
	
	return the_word;
}

char* ask_for_the_word() {
	printf("Please enter a word (max %i letters)\n", MAX_NO_LETTERS);
	char* the_word = malloc(sizeof(char) * (MAX_NO_LETTERS + 1)); // char the_word[WORD_SIZE] would probably be more effective
	printf("\n");

	read_word_incognito(the_word, MAX_NO_LETTERS + 1);

	return the_word;
}

void validate_word(char* the_word) {
	while (!contains_only_letters(the_word) || strlen(the_word) == 0) {  // if entered word is too long, scanf_s() doesn't return anything
		system("cls");
		if (strlen(the_word) == 0) {
			printf("Given word is too long (max length: %i). Let's try again...\n\n", MAX_NO_LETTERS);
		} else if (!contains_only_letters(the_word)) {
			printf("Given word contains forbidden characters. Let's try again...\n\n");
		}
		//discard_input_buffer();
		read_word_incognito(the_word, MAX_NO_LETTERS + 1);
	}
}

void read_word_incognito(char* string, int string_max_size) {
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

char* keep_guessing(char* the_word, int* attempt) {

	char* the_guess = malloc(sizeof(char) * (MAX_NO_LETTERS + 1));

	// keep guessing until user's right or runs out of attepmts
	while (strcmp(the_word, the_guess) != 0 && *attempt < NO_ATTEMPTS) {
		
		(*attempt)++;
		display_guessing_screen(the_word, attempt, the_guess);

		scanf_s("%s", the_guess, (MAX_NO_LETTERS + 1));
		validate_guess(the_guess, the_word);
	}

	return the_guess;
}

void validate_guess(char* the_guess, char* the_word) {
	while (!contains_only_letters(the_guess) || strlen(the_guess) != strlen(the_word)) {
		system("cls");
		if (strlen(the_guess) != strlen(the_word)) {
			printf("Given word has wrong number of letters (should be %i). \n\n", strlen(the_word));
		} else if (!contains_only_letters(the_guess)) {
			printf("Given word contains forbidden characters. Let's try again ()...\n\n");
		}
		//discard_input_buffer();
		scanf_s("%s", the_guess, (MAX_NO_LETTERS + 1));
	}
}

void display_guessing_screen(char* the_word, int* attempt, char* the_guess) {
	// display a number of letters (***)
	system("cls");
	printf("The word: ");
	print_asterisks(strlen(the_word));
	printf("\n\n");

	// first try?
	if (*attempt == 1) {
		printf("Enter your guess (%i attempts left): \n", NO_ATTEMPTS - *attempt + 1);
	} else {
		printf("The guess: ");
		print_colored_word(the_word, the_guess, strlen(the_guess));
		printf("\n\n");
		printf("You're wrong, try again (%i attempts left): \n", NO_ATTEMPTS - *attempt + 1);
	}
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

int is_in_word(char letter, char* word) {
	char* occurence = strchr(word, letter);

	return occurence != NULL;
}

void print_asterisks(int how_many) {
	for (int i = 0; i < how_many; i++) {
		putchar('*');
	}
}

void print_in_color(char letter, char* color_code) {
	char format[10] = "\033";
	strcat_s(format, sizeof(format), color_code);
	printf(format); //Set the text to the color ...
	printf("%c", letter);
	printf("\033[0m"); //Resets the text to default color
}

void print_colored_word(char* the_word, char* the_guess, int word_size) {
	
	for (int i = 0; i < word_size; i++) {
		if (the_word[i] == the_guess[i]) {
			print_in_color(the_guess[i], GREEN);
		} else if (is_in_word(the_guess[i],the_word)) {
			print_in_color(the_guess[i], YELLOW);
		} else {
			putchar(the_guess[i]);
		}
	}

}

void print_the_results(char* the_word, char* the_guess, int* attempts_p) {
	if (strcmp(the_word, the_guess) == 0) {
		system("cls");
		printf("Congratulations, you've won!!! It took you %i attempt(s) :)\n\n", *attempts_p);
	} else {
		system("cls");
		printf("You've lost. Better luck next time ;)\n\n");
	}
}

//void discard_input_buffer() {
//	char c;
//	while ((c = getchar()) != '\n' && c != EOF && c != '\r');
//}