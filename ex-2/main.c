#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LENGTH_OF(x) sizeof(x)/sizeof(x[0])
#define PI 3.141592

float take_float_from_user(char* name);
char let_user_decide(char* possibilities_keys[], char possibilities_values[], int no_possibilities);
int is_choice_valid(char possibilities[], int no_posssibilities, char users_choice);

int main() 
{
	char users_choice = '0';
	float radius, a, b, c, d;

	do
	{
		switch (users_choice)
		{
		case '0': // state START
			system("cls");
			printf("Welcome to our super duper geometric calculator. Tell me, what figure do you have in mind?\n\n");
			char* possibilities_keys[] = { "CIRCLE","RECTANGLE","TRIANGLE","TRAPEZE","Just get me outta here" };
			char possibilities_values[] = { '1','2','3','4','x' };
			int no_possibilities = LENGTH_OF(possibilities_keys);
			users_choice = let_user_decide(possibilities_keys, possibilities_values, no_possibilities);

			break;


		case '1': // state CIRCLE
			system("cls");
			printf("You've chosen a circle. Now please enter the value of the radius...\n\n");
			
			radius = take_float_from_user("radius");
			
			system("cls");
			printf("The perimeter of your figure is: %f", 2*PI*radius);
			getch();

			users_choice = '0'; //return to the START state

			break;


		case '2': // state RECTANGLE
			system("cls");
			printf("You've chosen a rectangle. Now please enter the length of the consecutive sides...\n\n");

			a = take_float_from_user("a");
			b = take_float_from_user("b");

			system("cls");
			printf("The perimeter of your figure is: %f", 2*a+2*b);
			getch();

			users_choice = '0'; //return to the START state

			break;


		case '3': // state TRIANGLE
			system("cls");
			printf("You've chosen a triangle. Now please enter the length of the consecutive sides...\n\n");

			a = take_float_from_user("a");
			b = take_float_from_user("b");
			c = take_float_from_user("c");

			system("cls");
			printf("The perimeter of your figure is: %f", a+b+c);
			getch();

			users_choice = '0'; //return to the START state

			break;


		case '4': // state TRAPEZE
			system("cls");
			printf("You've chosen a triangle. Now please enter the length of the consecutive sides...\n\n");

			a = take_float_from_user("a");
			b = take_float_from_user("b");
			c = take_float_from_user("c");
			d = take_float_from_user("d");

			system("cls");
			printf("The perimeter of your figure is: %f", a + b + c + d);
			getch();

			users_choice = '0'; //return to the START state
			break;

		}
	} while (users_choice != 'x');
	
	return 0;
}

float take_float_from_user(char* name)
{
	char users_input[30];
	float number;
	do
	{
		printf("%s:\t", name);
		scanf_s("%s", &users_input, 30);
		number = atof(users_input);
		if (number == 0)
		{
			system("cls");
			printf("Make sure you enter correct value...");
			getch();
		}
	} while (number == 0);
	return number;
}

char let_user_decide(char* possibilities_keys[], char possibilities_values[], int no_possibilities)
{
	// Function takes a map of possibilities for user to choose from. Displays the list of them, and waits for 
	// valid user input, which it returns at last.

	// display what are the possible choices
	char choices_list[200] = "";
	char temp[100] = "";

	for (int i = 0; i < no_possibilities; i++)
	{
		sprintf_s(temp, sizeof(temp), "%c - %s", possibilities_values[i], possibilities_keys[i]);
		strcat_s(choices_list, sizeof(choices_list), temp);
		strcat_s(choices_list, sizeof(choices_list), "    ");
	}
	strcat_s(choices_list, 200, "\n\n");

	printf("%s", choices_list);

	// read user's input (wait until it's valid)
	char users_choice;
	do
	{
		scanf_s("%c", &users_choice);
	} while (!is_choice_valid(possibilities_values, no_possibilities, users_choice));

	return users_choice;
}

int is_choice_valid(char possibilities[], int no_posssibilities, char users_choice)
{
	int is_valid = 0;
	for (int i = 0; i < no_posssibilities; i++)
	{
		if (users_choice == possibilities[i])
		{
			is_valid = 1;
		}
	}

	return is_valid;
}

// TODO: Test various cases of input, whether the output is correct? (long input, out-of-range input, etc.)
// TODO: Restrict the value of sides (prevent overflow)
// TODO: Make sure that user enters correct length of sides (is it possible to make, say a rectangle out of them?)
// TODO: Extract repeating code blocks into separate functions