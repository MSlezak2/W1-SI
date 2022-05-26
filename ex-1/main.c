#include<stdio.h>
#include <math.h>

char name[51] = "WALL-E"; // robot's name (max. 50 characters)
int battery_percentage = 65; // battery charge status [%] 
float temperature = 259.75; // current temperature [K] 
float velocity[3] = {1.2, 1.44444, 0.005}; // components of current velocity (in axes: x,y,z) [m/s] 
enum status { EXPLORING, SAMPLING, RETURNING, IDLE };
const char* status_names[] = { "EXPLORING", "SAMPLING", "RETURNING", "IDLE" };
enum status robots_status = IDLE; // current activity

const int MAX_BATTERY_PERCENTAGE = 100;
const int MIN_BATTERY_PERCENTAGE = 0;
const float MAX_TEMPERATURE = 2000.0;
const float MIN_TEMPERATURE = 0.0;
const float MAX_VELOCITY = 100.0;
const float MIN_VELOCITY = -100.0;

enum temperature_units { CELSIUS, KELVIN};
const char* temperature_units_symbols[] = { "*C", "K" };
enum temperature_units temperature_chosen_units = KELVIN; // which units to use when displaying temperature (although it's always stored in KELVINs)

enum notation { DECIMAL, SCIENTIFIC };
const char* notation_specifiers[] = { "f", "e" };
enum notation chosen_notation = DECIMAL;

int main() {

	char users_choice = '0';

	while (users_choice != 'x') // if user entered 'x' exit the program 
	{
		switch (users_choice)
		{
		case '0': // state ASK

			// robot introduces itself and asks which parameter to print
			system("cls");
			printf("Hi! I'm %s. Greetings form Mars! How can I help you?\n\n", name); //TODO: show that message only once (static)
			printf("Which parameter do you want me to show you?\n");
			printf("1 - NAME    2 - BATTERY CHARGE STATUS    3 - TEMPERATURE    4 - VELOCITY    5 - STATUS    x - EXIT\n\n");
			// user's input validation
			do
			{
				scanf_s("%c", &users_choice);
			} while (!(users_choice == 'x' || users_choice == '1' || users_choice == '2' || users_choice == '3' || users_choice == '4'
				|| users_choice == '5' )); //TODO: find better way to do that
			break; //TODO: if wrong character enter new in the same line, not in the new one like it's done now

		case '1': // state NAME
			system("cls");
			printf("As I already mentioned, my name is: %s\n\n", name);

			printf("1 - BACK    2 - VARIABLE SIZE    x - EXIT\n\n");
			// user's input validation
			do
			{
				scanf_s("%c", &users_choice);
			} while (!(users_choice == 'x' || users_choice == '1' || users_choice == '2')); //TODO: find better way to do that

			switch (users_choice)
			{
			case '1': // back to state MAIN
				users_choice = '0'; // outer switch block understands '0' as MAIN (starting) state
				break;
			case '2': // state VARIABLE SIZE
				system("cls");
				printf("Number of bytes necessary to store that parameter: %i\n\n", sizeof(name));
				printf("Press Any Key to Continue\n"); // to give the user time to read
				getch();

				users_choice = '1'; // come back to previous state
				break;
			}

			break;

		case '2': // state BATTERY CHARGE STATUS
			system("cls");
			printf("My battery level is: %i%%\n\n", battery_percentage);

			printf("1 - BACK    2 - VARIABLE SIZE    3 - PARAMETER'S RANGE    x - EXIT\n\n");
			// user's input validation
			do
			{
				scanf_s("%c", &users_choice);
			} while (!(users_choice == 'x' || users_choice == '1' || users_choice == '2' || users_choice == '3')); //TODO: find better way to do that

			switch (users_choice)
			{
			case '1': // back to state MAIN
				users_choice = '0'; // outer switch block understands '0' as MAIN (starting) state
				break;
			case '2': // state VARIABLE SIZE
				system("cls");
				printf("Number of bytes necessary to store that parameter: %i\n\n", sizeof(battery_percentage));
				printf("Press Any Key to Continue\n"); // to give the user time to read
				getch();

				users_choice = '2'; // come back to previous state
				break;
			case '3': // state PARAMETER'S RANGE
				system("cls");
				printf("Possible values of that parameter: %i - %i\n\n", MIN_BATTERY_PERCENTAGE, MAX_BATTERY_PERCENTAGE);
				printf("Press Any Key to Continue\n"); // to give the user time to read
				getch();

				users_choice = '2'; // come back to previous state
				break;
			}

			break;

		case '3': // state TEMPERATURE 
			system("cls");
			
			switch (temperature_chosen_units)
			{
			case CELSIUS:
			{
				float temperature_in_C = temperature - 273.15;
				printf("Current temperature is: %.1f%s\n\n", temperature_in_C, temperature_units_symbols[temperature_chosen_units]);
				break;
			}
			case KELVIN:
				printf("Current temperature is: %.1f%s\n\n", temperature, temperature_units_symbols[temperature_chosen_units]);
				break;
			}
			

			printf("1 - BACK    2 - VARIABLE SIZE    3 - PARAMETER'S RANGE    4 - CHANGE UNITS    5 - ABSOLUTE VALUE    x - EXIT\n\n");
			// user's input validation
			do
			{
				scanf_s("%c", &users_choice);
			} while (!(users_choice == 'x' || users_choice == '1' || users_choice == '2' || users_choice == '3' || users_choice == '4'
				|| users_choice == '5')); //TODO: find better way to do that

			switch (users_choice)
			{
			case '1': // back to state MAIN
				users_choice = '0'; // outer switch block understands '0' as MAIN (starting) state
				break;
			case '2': // state VARIABLE SIZE
				system("cls");
				printf("Number of bytes necessary to store that parameter: %i\n\n", sizeof(temperature));
				printf("Press Any Key to Continue\n"); // to give the user time to read
				getch();

				users_choice = '3'; // come back to previous state
				break;
			case '3': // state PARAMETER'S RANGE
				system("cls");
				printf("Possible values of that parameter: %.1f - %.1f\n\n", MIN_TEMPERATURE, MAX_TEMPERATURE);
				printf("Press Any Key to Continue\n"); // to give the user time to read
				getch();

				users_choice = '3'; // come back to previous state
				break;
			case '4': // state CHANGE UNITS
			{
				// It's job is to switch between available units. It does so, by incrementing the variable that holds
				// chosen unit type (enum). When it reaches last unit, it musn't increment, but instead it should
				// come back to the very begining of the "list".
				int no_unit_types = sizeof(temperature_units_symbols) / sizeof(temperature_units_symbols[0]); // number of unit types

				if (temperature_chosen_units < no_unit_types - 1)
				{
					temperature_chosen_units++; // next unit from the "list" (temperature_units enum)
				}
				else
				{
					temperature_chosen_units = 0; // back to the begining of the list
				}

				users_choice = '3'; // come back to previous state
				break;
			}
			case '5': // state VARIABLE SIZE
			{
				// take into account the unit 
				float abs_temperature;
				switch (temperature_chosen_units)
				{
				case CELSIUS:
					abs_temperature = fabs(temperature - 273.15);
					break;
				case KELVIN:
					abs_temperature = fabs(temperature);
					break;			
				}
				system("cls");
				printf("No idea what do you need that for, but here's an absolute value of the temperature: %.1f\n\n", abs_temperature);
				printf("Press Any Key to Continue\n"); // to give the user time to read
				getch();

				users_choice = '3'; // come back to previous state
				break;
			}
			}

			break;

		case '4': // state VELOCITY
			system("cls");
			char message[200] = "";
			// This command's task is to prepare "_Format" parameter for the following printf() function. It has to insert appropriate
			// specifier (%f or %e) depending on the chosen notation (decimal or scientific).
			sprintf_s(message, sizeof(message), "Here is my current velocity [m/s]: X: %%.2%s    Y: %%.2%s    Z: %%.2%s\n\n",
				notation_specifiers[chosen_notation], notation_specifiers[chosen_notation], notation_specifiers[chosen_notation]);
			printf(message, velocity[0], velocity[1], velocity[2]);

			printf("1 - BACK    2 - VARIABLE SIZE    3 - PARAMETER'S RANGE    4 - CHANGE NOTATION    x - EXIT\n\n");
			// user's input validation
			do
			{
				scanf_s("%c", &users_choice);
			} while (!(users_choice == 'x' || users_choice == '1' || users_choice == '2' || users_choice == '3' || users_choice == '4')); //TODO: find better way to do that

			switch (users_choice)
			{
			case '1': // back to state MAIN
				users_choice = '0'; // outer switch block understands '0' as MAIN (starting) state
				break;
			case '2': // state VARIABLE SIZE
				system("cls");
				printf("Number of bytes necessary to store that parameter: %i\n\n", sizeof(velocity)); //TODO: check corectness
				printf("Press Any Key to Continue\n"); // to give the user time to read
				getch();

				users_choice = '4'; // come back to previous state
				break;
			case '3': // state PARAMETER'S RANGE
				system("cls");
				printf("Possible values of that parameter: %.2f - %.2f\n\n", MIN_VELOCITY, MAX_VELOCITY);
				printf("Press Any Key to Continue\n"); // to give the user time to read
				getch();

				users_choice = '4'; // come back to previous state
				break;
			case '4': // state CHANGE NOTATION
			{
				// It's job is to switch between available notations. It does so, by incrementing the variable that holds
				// chosen notation type (enum). When it reaches last unit, it musn't increment, but instead it should
				// come back to the very begining of the "list".
				int no_notations = sizeof(notation_specifiers) / sizeof(notation_specifiers[0]); // number of notation types

				if (chosen_notation < no_notations - 1)
				{
					chosen_notation++; // next unit from the "list" (temperature_units enum)
				}
				else
				{
					chosen_notation = 0; // back to the begining of the list
				}

				users_choice = '4'; // come back to previous state
				break;
			}
			}

			break;

		case '5': // state STATUS
			system("cls");
			printf("What I'm doing right now is: %s\n\n", status_names[robots_status]);

			printf("1 - BACK    2 - VARIABLE SIZE    x - EXIT\n\n");
			// user's input validation
			do
			{
				scanf_s("%c", &users_choice);
			} while (!(users_choice == 'x' || users_choice == '1' || users_choice == '2')); //TODO: find better way to do that

			switch (users_choice)
			{
			case '1': // back to state MAIN
				users_choice = '0'; // outer switch block understands '0' as MAIN (starting) state
				break;
			case '2': // state VARIABLE SIZE
				system("cls");
				printf("Number of bytes necessary to store that parameter: %i\n\n", sizeof(robots_status));
				printf("Press Any Key to Continue\n"); // to give the user time to read
				getch();

				users_choice = '5'; // come back to previous state
				break;
			}

			break;
		}

	}


	return 0;
}