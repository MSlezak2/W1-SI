//TODO: Finish introducing let_user_decide function into code
//TODO: Finish introducing LENGTH_OF macro into code
//TODO: Extract rest of repeating code into functions
#include<stdio.h>
#include <math.h>
#include <string.h>

#define LENGTH_OF(x) sizeof(x)/sizeof(x[0])

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

char let_user_decide(char* possibilities_keys[], char possibilities_values[], int no_possibilities);
int is_choice_valid(char possibilities[], int no_posssibilities, char users_choice);

int main() {

	char users_choice = '0';

	while (users_choice != 'x') // if user entered 'x' exit the program 
	{
		switch (users_choice)
		{
		case '0': // state START

			// robot introduces itself and asks which parameter to print
			system("cls");
			printf("Hi! I'm %s. Greetings form Mars! How can I help you?\n\n", name); //TODO: show that message only once (static)
			printf("Which parameter do you want me to show you?\n");
			char* possibilities_keys_start[] = {"NAME","BATTERY CHARGE STATUS","TEMPERATURE","VELOCITY","STATUS","EXIT"};
			char possibilities_values_start[] = {'1','2','3','4','5','x'};
			int no_possibilities_start = LENGTH_OF(possibilities_keys_start);
			users_choice = let_user_decide(possibilities_keys_start, possibilities_values_start, no_possibilities_start);
			
			break;

		case '1': // state NAME
			system("cls");
			printf("As I already mentioned, my name is: %s\n\n", name);

			char* possibilities_keys_name[] = { "BACK","VARIABLE SIZE","EXIT" };
			char possibilities_values_name[] = { '1','2','x' };
			int no_possibilities_name = LENGTH_OF(possibilities_keys_name);
			users_choice = let_user_decide(possibilities_keys_name, possibilities_values_name, no_possibilities_name);

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

			char* possibilities_keys_battery[] = { "BACK","VARIABLE SIZE","PARAMETER'S RANGE", "EXIT"};
			char possibilities_values_battery[] = { '1','2','3','x' };
			int no_possibilities_battery = LENGTH_OF(possibilities_keys_battery);
			users_choice = let_user_decide(possibilities_keys_battery, possibilities_values_battery, no_possibilities_battery);
			
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
			
			char* possibilities_keys_temperature[] = { "BACK","VARIABLE SIZE","PARAMETER'S RANGE","CHANGE UNITS","ABSOLUTE VALUE","EXIT" };
			char possibilities_values_temperature[] = { '1','2','3','4','5','x' };
			int no_possibilities_temperature = LENGTH_OF(possibilities_keys_temperature);
			users_choice = let_user_decide(possibilities_keys_temperature, possibilities_values_temperature, no_possibilities_temperature);

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
				int no_unit_types = LENGTH_OF(temperature_units_symbols); // number of unit types

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

			char* possibilities_keys_velocity[] = { "BACK","VARIABLE SIZE","PARAMETER'S RANGE","CHANGE NOTATION","EXIT" };
			char possibilities_values_velocity[] = { '1','2','3','4','x' };
			int no_possibilities_velocity = LENGTH_OF(possibilities_keys_velocity);
			users_choice = let_user_decide(possibilities_keys_velocity, possibilities_values_velocity, no_possibilities_velocity);

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
				int no_notations = LENGTH_OF(notation_specifiers); // number of notation types

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

			char* possibilities_keys_status[] = { "BACK","VARIABLE SIZE","EXIT" };
			char possibilities_values_status[] = { '1','2','x' };
			int no_possibilities_status = LENGTH_OF(possibilities_keys_status);
			users_choice = let_user_decide(possibilities_keys_status, possibilities_values_status, no_possibilities_status);

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