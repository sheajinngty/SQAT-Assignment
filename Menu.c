#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable:4996)
#include<Windows.h>
SYSTEMTIME t;
void allMenus(int);
void errorMessage();
//4 Modules
void patientInfo();
void patientVisit();
void staffInfo();
void appointmentModule();

int homePage() {
	int choice;

	allMenus(1);

	printf("Please enter your option : ");
	rewind(stdin);
	scanf("%d", &choice);
	printf("\n");
	return choice;
}

void main() {
	int choice, backToMainMenu = 0;
	GetLocalTime(&t);
	do {
		printf("%d/%d/%d                                                             Yang Yang Clinic                                                             %d:%02d\n", t.wDay, t.wMonth, t.wYear, t.wHour, t.wMinute);
		printf("-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-\n");
		choice = homePage();
		while (choice >= 6) {
			errorMessage();
			rewind(stdin);
			scanf("%d", &choice);
			printf("\n");
		}
		switch (choice) {
		case 1:
			patientInfo();
			break;
		case 2:
			patientVisit();
			break;
		case 3:
			staffInfo();
			break;
		case 4:
			appointmentModule();
			break;
		}
	} while (choice != 5);
	system("pause");
}