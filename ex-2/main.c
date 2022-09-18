#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define LENGTH_OF(x) sizeof(x)/sizeof(x[0])
#define PI 3.141592
#define CIRCLE_PERIMETER(r) 2*PI*r
#define CIRCLE_AREA(r) PI*r*r
#define RECTANGLE_PERIMETER(a,b) 2*a+2*b
#define RECTANGLE_AREA(a,b) a*b
#define TRIANGLE_PERIMETER(a,b,c) a+b+c
#define TRIANGLE_AREA(a,b,c,s) sqrt( s*(s-a)*(s-b)*(s-c) ) //Heron's formula; s-perimeter devided by 2
#define TRAPEZOID_PERIMETER(a,b,c,d) a+b+c+d
//#define TRAPEZOID_AREA(a,b,c,d) 
#define DISTANCE(A,B) sqrt( (B[0]-A[0])*(B[0]-A[0]) + (B[1]-A[1])*(B[1]-A[1]) )

float take_float_from_user(char* name);
char let_user_decide(char* possibilities_keys[], char possibilities_values[], int no_possibilities);
int is_choice_valid(char possibilities[], int no_posssibilities, char users_choice);

int main() 
{
	char users_choice = '0';
	float r, a, b, c, d, h;
	float A[2], B[2], C[2], D[2]; // cartesian coordinates [x,y]
	float perimeter, area;

	do
	{
		switch (users_choice)
		{
		case '0': // state START
			system("cls");
			printf("Welcome to our super duper geometric calculator. What figure do you have in mind?\n\n");
			char* possibilities_keys[] = { "CIRCLE","RECTANGLE","TRIANGLE","TRAPEZOID","Just get me outta here" };
			char possibilities_values[] = { '1','2','3','4','x' };
			int no_possibilities = LENGTH_OF(possibilities_keys);
			users_choice = let_user_decide(possibilities_keys, possibilities_values, no_possibilities);

			break;


		case '1': // state CIRCLE
			system("cls");
			printf("You've chosen a circle. Now choose the way of providing some more details...\n\n");
			
			char* possibilities_keys_circle[] = { "BACK","EXACT VALUES","CARTESIAN COORDINATES","EXIT" };
			char possibilities_values_circle[] = { '1','2','3','x' };
			int no_possibilities_circle = LENGTH_OF(possibilities_keys_circle);
			users_choice = let_user_decide(possibilities_keys_circle, possibilities_values_circle, no_possibilities_circle);

			switch (users_choice)
			{
			case '1': // back to state START
				users_choice = '0'; // outer switch block understands '0' as START state
				break;
			case '2': // exact values
				system("cls");
				printf("Ok, now exter the values...\n\n");
				r = take_float_from_user("r");

				users_choice = '1'; // remain in the current state
				break;
			case '3': // cartesian coordinates
				system("cls");
				printf("Ok, now exter the coordinates...\n\n");
				A[0] = take_float_from_user("X0 (center) [x-coordinate]");
				A[1] = take_float_from_user("X0 (center) [y-coordinate]");
				B[0] = take_float_from_user("X1 (center) [x-coordinate]");
				B[1] = take_float_from_user("X1 (center) [y-coordinate]");

				r = DISTANCE(A,B);

				users_choice = '1'; // remain in the current state
				break;
			case 'x': // back to state START
				users_choice = 'x'; // outer switch block understands '0' as START state
				break;
			}
			
			if (!(users_choice == '0' || users_choice == 'x')) // if user wants to return to the main menu, skip the calculations
			{
				perimeter = CIRCLE_PERIMETER(r);
				area = CIRCLE_AREA(r);

				system("cls");
				printf("r = %f\n", r);
				printf("The perimeter of your figure is: %f\n", perimeter);
				printf("The area of your figure: %f\n\n", area);
				printf("Press Any Key to Continue\n"); // to give the user time to read
				getch();

				users_choice = '0'; //return to the START state
			}	

			break;


		case '2': // state RECTANGLE
			system("cls");
			printf("You've chosen a rectangle. Now choose the way of providing some more details...\n\n");

			char* possibilities_keys_rectangle[] = { "WEST","EAST","NORTH","SOUTH" };
			char possibilities_values_rectangle[] = { '1','2','3','x' };
			int no_possibilities_rectangle = LENGTH_OF(possibilities_keys_rectangle);
			users_choice = let_user_decide(possibilities_keys_rectangle, possibilities_values_rectangle, no_possibilities_rectangle);

			switch (users_choice)
			{
			case '1': // back to state START
				users_choice = '0'; // outer switch block understands '0' as START state
				break;
			case '2': // exact values
				system("cls");
				printf("Ok, now exter the values...\n\n");
				a = take_float_from_user("a");
				b = take_float_from_user("b");

				users_choice = '1'; // remain in the current state
				break;
			case '3': // cartesian coordinates
				system("cls");
				printf("Ok, now exter the coordinates...\n\n");
				A[0] = take_float_from_user("A [x-coordinate]");
				A[1] = take_float_from_user("A [y-coordinate]");
				B[0] = take_float_from_user("B [x-coordinate]");
				B[1] = take_float_from_user("B [y-coordinate]");
				C[0] = take_float_from_user("C [x-coordinate]");
				C[1] = take_float_from_user("C [y-coordinate]");
				D[0] = take_float_from_user("D [x-coordinate]");
				D[1] = take_float_from_user("D [y-coordinate]");

				a = DISTANCE(A, B);
				b = DISTANCE(B, C);

				users_choice = '1'; // remain in the current state
				break;
			case 'x': // back to state START
				users_choice = 'x'; // outer switch block understands '0' as START state
				break;
			}

			if (!(users_choice == '0' || users_choice == 'x')) // if user wants to return to the main menu, skip the calculations
			{
				perimeter = RECTANGLE_PERIMETER(a, b);
				area = RECTANGLE_AREA(a, b);

				system("cls");
				printf("a = %f\tb = %f\n", a, b);
				printf("The perimeter of your figure is: %f\n", perimeter);
				printf("The area of your figure: %f\n\n", area);
				printf("Press Any Key to Continue\n"); // to give the user time to read
				getch();

				users_choice = '0'; //return to the START state
			}

			break;


		case '3': // state TRIANGLE
			system("cls");
			printf("You've chosen a triangle. Now please enter the length of the consecutive sides...\n\n");

			char* possibilities_keys_triangle[] = { "BACK","EXACT VALUES","CARTESIAN COORDINATES","EXIT" };
			char possibilities_values_triangle[] = { '1','2','3','x' };
			int no_possibilities_triangle = LENGTH_OF(possibilities_keys_triangle);
			users_choice = let_user_decide(possibilities_keys_triangle, possibilities_values_triangle, no_possibilities_triangle);

			switch (users_choice)
			{
			case '1': // back to state START
				users_choice = '0'; // outer switch block understands '0' as START state
				break;
			case '2': // exact values
				system("cls");
				printf("Ok, now exter the values...\n\n");
				a = take_float_from_user("a");
				b = take_float_from_user("b");
				c = take_float_from_user("c");

				users_choice = '1'; // remain in the current state
				break;
			case '3': // cartesian coordinates
				system("cls");
				printf("Ok, now exter the coordinates...\n\n");
				A[0] = take_float_from_user("A [x-coordinate]");
				A[1] = take_float_from_user("A [y-coordinate]");
				B[0] = take_float_from_user("B [x-coordinate]");
				B[1] = take_float_from_user("B [y-coordinate]");
				C[0] = take_float_from_user("C [x-coordinate]");
				C[1] = take_float_from_user("C [y-coordinate]");

				a = DISTANCE(A, B);
				b = DISTANCE(B, C);
				c = DISTANCE(C, A);

				users_choice = '1'; // remain in the current state
				break;
			case 'x': // back to state START
				users_choice = 'x'; // outer switch block understands '0' as START state
				break;
			}

			if (!(users_choice == '0' || users_choice == 'x')) // if user wants to return to the main menu, skip the calculations
			{
				perimeter = TRIANGLE_PERIMETER(a, b, c);
				area = TRIANGLE_AREA(a, b, c, perimeter / 2);

				system("cls");
				printf("a = %f\tb = %f\tc = %f\n", a, b, c);
				printf("The perimeter of your figure is: %f\n", perimeter);
				printf("The area of your figure: %f\n\n", area);
				printf("Press Any Key to Continue\n"); // to give the user time to read
				getch();

				users_choice = '0'; //return to the START state
			}
			break;


		case '4': // state TRAPEZOID
			system("cls");
			printf("You've chosen a triangle. Now please enter the length of the consecutive sides...\n\n");

			char* possibilities_keys_trapezoid[] = { "BACK","EXACT VALUES","CARTESIAN COORDINATES","EXIT" };
			char possibilities_values_trapezoid[] = { '1','2','3','x' };
			int no_possibilities_trapezoid = LENGTH_OF(possibilities_keys_trapezoid);
			users_choice = let_user_decide(possibilities_keys_trapezoid, possibilities_values_trapezoid, no_possibilities_trapezoid);

			switch (users_choice)
			{
			case '1': // back to state START
				users_choice = '0'; // outer switch block understands '0' as START state
				break;
			case '2': // exact values
				system("cls");
				printf("Ok, now exter the values...\n\n");
				a = take_float_from_user("a");
				b = take_float_from_user("b");
				c = take_float_from_user("c");
				d = take_float_from_user("d");
				h = take_float_from_user("h");

				users_choice = '1'; // remain in the current state
				break;
			case '3': // cartesian coordinates
				system("cls");
				printf("Ok, now exter the coordinates (starting with points that belong to the first of the parallel sides)...\n\n");
				A[0] = take_float_from_user("A [x-coordinate]");
				A[1] = take_float_from_user("A [y-coordinate]");
				B[0] = take_float_from_user("B [x-coordinate]");
				B[1] = take_float_from_user("B [y-coordinate]");
				C[0] = take_float_from_user("C [x-coordinate]");
				C[1] = take_float_from_user("C [y-coordinate]");
				D[0] = take_float_from_user("C [x-coordinate]");
				D[1] = take_float_from_user("C [y-coordinate]");

				a = DISTANCE(A, B);
				b = DISTANCE(B, C);
				c = DISTANCE(C, D);
				d = DISTANCE(D, A);

				// To calculate h value...
				// ...First, find general line formula parameters...
				float param_A, param_B, param_C; // elements of general line formula param_A*x + param_B*y = param_C
				param_A = A[1] - B[1];
				param_B = B[0] - A[0];
				param_C = B[1] * A[0] - A[0] * A[1];

				// ...Then, use formula for the distance between line (AB) and point (D)...
				h = abs(param_A*D[0] + param_B*D[1] + param_C) / sqrt(param_A * param_A + param_B * param_B);

				users_choice = '1'; // remain in the current state
				break;
			case 'x': // back to state START
				users_choice = 'x'; // outer switch block understands '0' as START state
				break;
			}

			if (!(users_choice == '0' || users_choice == 'x')) // if user wants to return to the main menu, skip the calculations
			{
				perimeter = TRAPEZOID_PERIMETER(a, b, c, d);
				area = ((a + b) / 2) * h;

				system("cls");
				printf("a = %f\tb = %f\tc = %f\td = %f\th = %f\n", a, b, c, d, h);
				printf("The perimeter of your figure is: %f\n", perimeter);
				printf("The perimeter of your figure is: %f\n\n", area);
				printf("Press Any Key to Continue\n"); // to give the user time to read
				getch();

				users_choice = '0'; //return to the START state
				break;
			}

		}
	} while (users_choice != 'x');
	
	return 0;
}

float take_float_from_user(char* name)
{
	char users_input[30];
	char zero[] = "0";
	float number;
	
	do
	{
		printf("%s:\t", name);
		scanf_s("%s", &users_input, 30);

		number = atof(users_input);

		if (number == 0 && strcmp(&users_input, &zero)) // if user entered "0" on purpose, then continue, else - it means input was invalid
		{
			printf("\n\nSomething went wrong. Make sure you enter correct value...\n\n");
		}
	} while (number == 0 && strcmp(&users_input, &zero)); // if user entered "0" on purpose, then continue, else - it means input was invalid
	
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

// TODO: Find formula for the area of trapezoid (given only sides lengths)
// TODO: Test various cases of input, whether the output is correct? (long input, out-of-range input, etc.)
// TODO: Restrict the max value of sides (prevent overflow)
// TODO: Make sure that user enters correct length of sides (is it possible to make, say a rectangle out of them?)
// TODO: Make sure the coordinates are also correct
// TODO: Extract repeating code blocks into separate functions
