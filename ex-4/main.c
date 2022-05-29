#include <stdio.h>
#include <string.h>

#define LENGTH_OF(x) sizeof(x)/sizeof(x[0])

int take_int_from_user();
char let_user_decide(char* possibilities_keys[], char possibilities_values[], int no_possibilities);
int is_choice_valid(char possibilities[], int no_posssibilities, char users_choice);

int main()
{

	char users_choice = '0';
	int image_size = 0;

	do
	{
		switch (users_choice)
		{
		case '0': // state START
			system("cls");
			printf("Which pattern do you want to create?\n\n");
			char* possibilities_keys[] = { "RECTANGLE","TRIANGLE","GRID","FRAME","X-CROSS","EXIT" };
			char possibilities_values[] = { '1','2','3','4','5','x' };
			int no_possibilities = LENGTH_OF(possibilities_keys);
			users_choice = let_user_decide(possibilities_keys, possibilities_values, no_possibilities);

			break;

		case '1': // RECTANGLE
		{

			image_size = take_int_from_user();

			printf("\n");
			for (int i = 0; i < image_size; i++)
			{
				for (int j = 0; j < image_size; j++)
				{
					printf("X");
				}
				printf("\n");
			}

			printf("\nPress any key to continue...");
			getch();

			users_choice = '0'; //return to the START state
			break;
		}
		case '2': // TRIANGLE

			image_size = take_int_from_user();

			printf("\n");
			for (int i = 0; i < image_size; i++)
			{
				for (int j = 0; j <= i; j++)
				{
					printf("X");
				}
				printf("\n");
			}

			printf("\nPress any key to continue...");
			getch();

			users_choice = '0'; //return to the START state
			break;

		case '3': // GRID

			image_size = take_int_from_user();

			printf("\n");
			for (int i = 0; i < image_size; i++)
			{
				for (int j = 0; j <= image_size; j++)
				{
					if ((i + j) % 2 == 0) // when sum of coordinates of the element is even, then put "X"
					{
						printf("X");
					}
					else // otherwise put "o"
					{
						printf("o");
					}
				}
				printf("\n");
			}

			printf("\nPress any key to continue...");
			getch();

			users_choice = '0'; //return to the START state
			break;

		case '4': // FRAME

			image_size = take_int_from_user();

			printf("\n");
			for (int i = 0; i < image_size; i++)
			{
				for (int j = 0; j < image_size; j++)
				{
					if (i == 0 || i == image_size - 1 || j == 0 || j == image_size - 1) 
					{
						printf("X");
					}
					else // otherwise put "o"
					{
						printf("o");
					}
				}
				printf("\n");
			}

			printf("\nPress any key to continue...");
			getch();

			users_choice = '0'; //return to the START state
			break;

		case '5': // X-CROSS

			image_size = take_int_from_user();

			printf("\n");
			for (int i = 0; i < image_size; i++)
			{
				for (int j = 0; j < image_size; j++)
				{
					if (i == 0 || i == image_size - 1 || j == 0 || j == image_size - 1 || i==j || i+j == image_size - 1)
					{
						printf("X");
					}
					else // otherwise put "o"
					{
						printf("o");
					}
				}
				printf("\n");
			}

			printf("\nPress any key to continue...");
			getch();

			users_choice = '0'; //return to the START state
			break;
		}
	} while (users_choice != 'x');

	return 0;
}


int take_int_from_user()
{
	// Function prompts user to enter positive, int value, then validates it and returns

	int number;
	char temp[20]; // temporary place to read the user input to

	do
	{
		system("cls");
		printf("Enter the size of the image:\t");
		scanf_s("%s", &temp, sizeof(temp));
		number = atoi(temp);
		if (number <= 0) // if user entered "0" on purpose, then continue, else - it means input was invalid
		{
			system("cls");
			printf("Make sure you enter positive, integer value...\n\n");
			printf("\nPress any key to continue...");
			getch();
		}
	} while (number <= 0);

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