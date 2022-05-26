#include<stdio.h>

char name[51] = "WALL-E"; // robot's name (max. 50 characters)
int battery_percentage = 5; // battery charge status [%]
float temperature = 36.61; // current temperature [*C] (for now)
float velocity[3] = {1.2, 1.44444, 0.005}; // components of current velocity (in axes: x,y,z) [m/s]
enum status { EXPLORING, SAMPLING, RETURNING, IDLE };
const char* status_names[] = { "EXPLORING", "SAMPLING", "RETURNING", "IDLE" };
enum status robots_status = IDLE; // current activity

int main() {

	char users_choice = '0';
	//printf("a%*sb", 10, "");
	//printf("%s", status_names[0]);
	//printf("%s", status_names[1]);

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

			printf("Press Any Key to Continue\n"); // to give the user time to read
			getch();

			users_choice = '0'; // for program to return to main state
			break;

		case '2': // state BATTERY CHARGE STATUS
			system("cls");
			printf("My battery level is: %i%%\n\n", battery_percentage);

			printf("Press Any Key to Continue\n"); // to give the user time to read
			getch();

			users_choice = '0'; // for program to return to main state
			break;

		case '3': // state TEMPERATURE 
			system("cls");
			printf("Current temperature is: %.1f*C\n\n", temperature);

			printf("Press Any Key to Continue\n"); // to give the user time to read
			getch();

			users_choice = '0'; // for program to return to main state
			break;

		case '4': // state VELOCITY
			system("cls");
			printf("Here is my current velocity [m/s]: X: %.2f    Y: %.2f    Z: %.2f\n\n", velocity[0], velocity[1], velocity[2]);

			printf("Press Any Key to Continue\n"); // to give the user time to read
			getch();

			users_choice = '0'; // for program to return to main state
			break;

		case '5': // state STATUS
			system("cls");
			printf("What I'm doing right now is: %s\n\n", status_names[robots_status]);

			printf("Press Any Key to Continue\n"); // to give the user time to read
			getch();

			users_choice = '0'; // for program to return to main state
			break;
		}

	}


	return 0;
}