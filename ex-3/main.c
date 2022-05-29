#include <stdio.h>
#include <string.h>

#define LENGTH_OF(x) sizeof(x)/sizeof(x[0])

const int NUMBER_OF_NOTES_IN_SUBJECT = 7;

char* subjects[7] = { "Math", "English", "History", "Physics", "Biology", "Information Technology", "Foreign Language" };
char* students[5]; // list of students' names
float scores[5][7]; // [student_id][subject_id] average score [%] in particular subject of the student
char grades[5][7]; // [student_id][subject_id] grade [A-F] for particular subject of the student

int no_students = 0; // how many students are already in the system
float temp_score, scores_buffer = 0; // temp variables used for average score calculation (there's no point in storing that data according to the task)

char give_grade(float score_percentage);

int main()
{
	/*float harper_eland[7] = { 56.7, 22, 60, 45, 96, 19.5, 59.7 };
	float celement_hayes[7] = { 40.2, 80, 57, 49.1, 38.5, 89.7, 96.1};
	float belinsa_jacobs[7] = { 90.2, 79.3, 95.9, 95.1, 97.1, 79.4, 80.1};
	float cedric_santos[7] = { 78.2, 50.1, 58.63, 80.2, 18.4, 96.3, 96.1 };
	float fiona_wilcher[7] = { 95.2, 99.2, 82.4, 60.77, 90.24, 97.56, 90.1};
	*/

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

	printf("\n\nGrades of sudent:\t%s:", &students[0]);
	for (int i = 0; i < LENGTH_OF(subjects); i++)
	{
		printf("\n\n%s:\t%c", subjects[i], grades[0][i]);
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

// TODO: Validate entered percentage (0-100)
// TODO: Problem with space in name