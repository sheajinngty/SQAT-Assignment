#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable:4996)
#include<Windows.h>
#include<ctype.h>
#include<string.h>
void allMenus(int);
int genderValidate(char);
void patientIdDataValidate(char patientId[]);

void allMenus(i) {
	if (i == 1) {
		printf("1.Patient Information\n");
		printf("2.Patient Visit\n");
		printf("3.Staff Information\n");
		printf("4.Appointment\n");
		printf("5.Exit\n\n");
	}
	else if (i == 2) {
		printf("   ~~ Patient Information Menu ~~\n");
		printf("   ==============================\n");
		printf("    1.Add New Patient Information\n");
		printf("    2.Search Patient Information\n");
		printf("    3.Modify Patient Information\n");
		printf("    4.Display Patient Information\n");
		printf("    5.Calculate and Display Patient Body Mass Index (BMI)\n");
		printf("    6.Exit to Main Menu\n\n");
	}
	else if (i == 3) {
		printf("   ~~ Patient Visit Menu ~~\n");
		printf("   ========================\n");
		printf("    1.Add\n");
		printf("    2.Search\n");
		printf("    3.Modify\n");
		printf("    4.Display\n");
		printf("    5.Report\n");
		printf("    6.Delete\n");
		printf("    7.Exit to Main Menu\n\n");
	}
	else if (i == 4) {
		printf("   ~~ Staff Information Menu ~~\n");
		printf("   ============================\n");
		printf("    1.Search Record\n");
		printf("    2.Modify Record\n");
		printf("    3.Add Record\n");
		printf("    4.Display All\n");
		printf("    5.Delete Employee\n");
		printf("    6.Exit to Main Menu\n\n");
	}
	else if (i == 5) {
		printf("   ~~ Appointment ~~\n");
		printf("   =================\n");
		printf("    1.Display Schedule\n");
		printf("    2.Find Schedule\n");
		printf("    3.Add Schedule\n");
		printf("    4.Modify Schedule\n");
		printf("    5.Delete Schedule\n");
		printf("    6.System Tracking Report\n");
		printf("    7.Exit to Main Menu\n\n");
	}
}

void errorMessage() {
	printf("Invalid Input!\n");
	printf("Please enter again.\n");
	printf("\nPlease enter your option : ");
}

int genderValidate(char sex) {
	if (sex != 'm'&& sex != 'M' && sex != 'f' && sex != 'F') {
		printf("\nInvalid gender!\n");
		printf("Please enter again\n\n");
		return 1;
	}
	else
		return 0;
}

void patientIdDataValidate(char patientId[]) {
	int strlength;
	strlength = strlen(patientId);
	//Data validate
	while (patientId[0] != 'P' || strlength < 5 || strlength>5 || !(isdigit(patientId[1]) && isdigit(patientId[2]) && isdigit(patientId[3]) && isdigit(patientId[4]))) {
		if (patientId[0] != 'P') {
			printf("\nPatient ID must start with the letter 'P'.");
		}
		if (strlength < 5 || strlength>5) {
			printf("\nPatient ID must have 5 character only.");
		}
		if (!(isdigit(patientId[1]) && isdigit(patientId[2]) && isdigit(patientId[3]) && isdigit(patientId[4]))) {
			printf("\nLast 4 character must be number.");
		}
		printf("\nPlease try again.\n\n");
		printf("Patient ID : ");
		scanf(" %[^\n]", patientId);
		strlength = strlen(patientId);
	}
}

