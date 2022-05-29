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
	/*float harper_eland[7] = { 56.7, 22, 60, 45, 96, 19.5, 59.7 };
	float celement_hayes[7] = { 40.2, 80, 57, 49.1, 38.5, 89.7, 96.1};
	float belinsa_jacobs[7] = { 90.2, 79.3, 95.9, 95.1, 97.1, 79.4, 80.1};
	float cedric_santos[7] = { 78.2, 50.1, 58.63, 80.2, 18.4, 96.3, 96.1 };
	float fiona_wilcher[7] = { 95.2, 99.2, 82.4, 60.77, 90.24, 97.56, 90.1};
	*/

	//students[0] = "Michal";
	//scores[0][0] = 96.0;
	//scores[0][1] = 96.0;
	//scores[0][2] = 91.0;
	//scores[0][3] = 91.0;
	//scores[0][4] = 91.0;
	//scores[0][5] = 91.0;
	//scores[0][6] = 91.0;
	//grades[0][0] = 'A';
	//grades[0][1] = 'A';
	//grades[0][2] = 'A';
	//grades[0][3] = 'A';
	//grades[0][4] = 'A';
	//grades[0][5] = 'A';
	//grades[0][6] = 'A';

	//Enter students details

	system("cls");
	printf("TEACHER'S ASSISTANT");
	printf("\n\nEnter the name of the student:\t");
	scanf_s("%[^\n]s", &students[no_students], 30);

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
		scores[no_students][i] = scores_buffer / NUMBER_OF_NOTES_IN_SUBJECT; // average score in subject
		grades[no_students][i] = give_grade(scores[no_students][i]); // grade for subject
	}
	no_students++;

	// Print  received grades

	for (int i = 0; i < LENGTH_OF(subjects); i++)
	{
		printf("\n\n%s:\t%c", subjects[i], grades[0][i]);
	}

	if (is_eligible(scores[0],7))
	{
		printf("\n\nStudent is eligible for scholarship\n\n");
	}
	else
	{
		printf("\n\nStudent is not eligible for scholarship\n\n");
	}

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
