#include <stdio.h>
#include <string.h>

#define LENGTH_OF(x) sizeof(x)/sizeof(x[0])

const int NUMBER_OF_NOTES_IN_SUBJECT = 7;
const int SCHOLARSHIP_TRESHOLD = 95.0; // student has to have at least 3 grades equal or greater than this treshold

char* subjects[7] = { "Math", "English", "History", "Physics", "Biology", "Information Technology", "Foreign Language" };
char* students[5]; // list of students' names
float scores[5][7]; // [student_id][subject_id] average score [%] in particular subject of the student
char grades[5][7]; // [student_id][subject_id] grade [A-F] for particular subject of the student

int no_students = 0; // how many students are already in the system
float temp_score, scores_buffer = 0; // temp variables used for average score calculation (there's no point in storing that data according to the task)

char give_grade(float score_percentage);
int is_eligible(float grades[], int no_grades);

int main()
{
	// populate database
	students[0] = "Michal";
	scores[0][0] = 96.0;
	scores[0][1] = 96.0;
	scores[0][2] = 96.0;
	scores[0][3] = 91.0;
	scores[0][4] = 91.0;
	scores[0][5] = 91.0;
	scores[0][6] = 91.0;
	grades[0][0] = 'A';
	grades[0][1] = 'A';
	grades[0][2] = 'A';
	grades[0][3] = 'A';
	grades[0][4] = 'A';
	grades[0][5] = 'A';
	grades[0][6] = 'A';
	students[1] = "Maciek";
	scores[1][0] = 50.0;
	scores[1][1] = 50.0;
	scores[1][2] = 96.0;
	scores[1][3] = 91.0;
	scores[1][4] = 91.0;
	scores[1][5] = 91.0;
	scores[1][6] = 91.0;
	grades[1][0] = 'F';
	grades[1][1] = 'F';
	grades[1][2] = 'A';
	grades[1][3] = 'A';
	grades[1][4] = 'A';
	grades[1][5] = 'A';
	grades[1][6] = 'A';
	no_students+=2;

	char users_choice[30] = "";
	do
	{
		// MAIN MENU
		system("cls");

		// Show user what options does he have
		printf("TEACHER'S ASSISTANT");
		printf("\n\nChoose one of the following options:\n\n");
		for (int i = 0; i < no_students; i++)
		{
			printf("%i - %s\n", i+1, students[i]);
		}
		int add_option_number = no_students + 1;
		int stats_option_number = no_students + 2;
		if (no_students < 8) printf("%i - ADD\n", add_option_number);
		printf("%i - STATS\n", stats_option_number);
		printf("x - EXIT\n");

		// Take user's input and go to the appropriate conditional block of instruction
		scanf_s("%s", &users_choice, 30);

		int chosen_number = atoi(users_choice); // id of chosen student (if input was not an int, it equals to 0) 

		// Block for displaying students' details
		if (chosen_number > 0 && chosen_number <= no_students) // if user chose one of the students
		{
			// Print  received grades
			system("cls");
			for (int i = 0; i < LENGTH_OF(subjects); i++)
			{
				printf("\n\n%s:\t%.2f%%\t(%c)", subjects[i], scores[chosen_number-1][i], grades[chosen_number - 1][i]);
			}

			if (is_eligible(scores[chosen_number - 1],7))
			{
				printf("\n\nStudent is eligible for scholarship\n\n");
			}
			else
			{
				printf("\n\nStudent is not eligible for scholarship\n\n");
			}
			printf("Press any key to return...");
			getch();
		}

		// Handle adding new students to data base
		if (chosen_number == add_option_number && no_students < 8) // ADD state
		{
			system("cls");
			char temp[30] = "";
			printf("\n\nEnter the name of the student:\t");
			scanf_s("\n%[^\n]s", &temp, 30);
			students[no_students] = temp;

			printf("\n\nNow enter consecutive scores, that student has obtained throughout the semester in following subjects:\t");

			for (int i = 0; i < LENGTH_OF(subjects); i++)
			{
				scores_buffer = 0;
				printf("\n\n%s:",subjects[i]);
				for (int j = 0; j < NUMBER_OF_NOTES_IN_SUBJECT; j++)
				{
					printf("\n\n\t%i:\t", j+1);
					scanf_s("%f", &temp_score);
					scores_buffer += temp_score;
				}
				// giving grades based on the average score
				scores[no_students][i] = scores_buffer / NUMBER_OF_NOTES_IN_SUBJECT; // average score in subject
				grades[no_students][i] = give_grade(scores[no_students][i]); // grade for subject
			}
			no_students++;
		}

		// Calculating and displaying stats regarding each subject and the sholarship
		if (chosen_number == stats_option_number) // STATS state
		{
			system("cls");
			float average_score, min_score, max_score, current_score;
			int no_eligible_students = 0;

			printf("Statistics for each subject:");
			for (int i = 0; i < LENGTH_OF(subjects); i++) // subjects' loop
			{
				min_score = _CRT_INT_MAX;
				max_score = 0;
				scores_buffer = 0;
				for (int j = 0; j < no_students; j++) //students' loop
				{
					current_score = scores[j][i];
					scores_buffer += current_score;
					// the highest note
					if (current_score > max_score)
					{
						max_score = current_score;
					}
					// the lowest note
					if (current_score < min_score)
					{
						min_score = current_score;
					}
				}
				// average class note in each subject
				average_score = scores_buffer / (float)no_students;

				printf("\n\n%s:\tmin:%.2f%%\tmax:%.2f%%\tavg:%.2f%%", subjects[i], min_score, max_score, average_score);
			}
			
			// number of students with scholarship
			for (int i = 0; i < no_students; i++) //students' loop
			{
				no_eligible_students += is_eligible(scores[i], 7);
			}


			printf("\n\nNumber of students eligible for scholarship:\t%i", no_eligible_students);
			printf("\n\nPress any key to return...");
			getch();
		}


	} while (strcmp(&users_choice, "x"));

	return 0;
}



char give_grade(float score_percentage)
{
	char grade;

	if (score_percentage < 50) {
		grade = 'F';
	}
	else if (score_percentage > 50 && score_percentage <= 60) {
		grade = 'E';
	}
	else if (score_percentage > 60 && score_percentage <= 70) {
		grade = 'D';
	}
	else if (score_percentage > 70 && score_percentage <= 80) {
		grade = 'C';
	}
	else if (score_percentage > 80 && score_percentage <= 90) {
		grade = 'B';
	}
	else if (score_percentage > 90 && score_percentage <= 100) {
		grade = 'A';
	}

	return grade;
}

int is_eligible(float grades[], int no_grades)
{
	int is_eligible = 0;
	int no_grades_good_enough = 0;

	for (int i = 0; i < no_grades; i++)
	{
		if (grades[i] > SCHOLARSHIP_TRESHOLD)
		{
			no_grades_good_enough++;
		}
	}

	if (no_grades_good_enough >= 3)
	{
		is_eligible = 1;
	}

	return is_eligible;
}


// TODO: Validate entered percentage (0-100)
