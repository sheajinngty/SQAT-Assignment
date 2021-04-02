#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable:4996)
#include<Windows.h>
#include<ctype.h>
#include<string.h>
SYSTEMTIME t;
//Structure declarations
struct Date {
	int day, month, year;
};

struct Time {
	int h, m;
};

typedef struct {
	char med1[30], med2[30], med3[30];
}Medicine;

typedef struct {
	int recNo;
	struct Date date;
	struct Time time;
	char patId[6], nurId[4], docId[4], diagnosis[30];
	Medicine medicine;
	double charge;
}VisitRec;
VisitRec vr[999];
//4 compulsary functions and 2 added function
char add();
char search();
char modify();
void display();
char report();
void delete();
//Other functions
void displayRecord(int);
void displayHeader();
//
void patientIdDataInputAndValidate(int);
void patientIdDataValidate(char patientId[]);
//
void nurseIdDataInputAndValidate(int);
void nurseIdDataValidate(char nurseId[]);
//
void doctorIdDataInputAndValidate(int);
void doctorIdDataValidate(char doctorId[]);
//
void patientVisitOtherDataInputAndValidate(int);
char askForRepetition(FILE *);
void allMenus(int);

int subMenu(int a) {
	int choice;
	GetLocalTime(&t);
	if (a == 1) {
		allMenus(3);
	}
	else if (a == 2) {
		printf("    1.Search by Record No.\n");
		printf("    2.Search by Patient ID\n\n");
	}
	printf("Please enter your option : ");
	rewind(stdin);
	scanf("%d", &choice);
	printf("\n");
	return choice;
}

int readPatientVisitFile() {
	int i = 0;
	FILE *fptr;
	fptr = fopen("patient visit records.txt", "r");
	if (fptr == NULL) {
		printf("Unable to open patient visit record.");
		exit(-1);
	}
	while (fscanf(fptr, "[%d]%d/%d/%d|%d:%d|%[^\n]\n%[^\|]|%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%lf\n", &vr[i].recNo, &vr[i].date.day, &vr[i].date.month, &vr[i].date.year, &vr[i].time.h, &vr[i].time.m, vr[i].patId, vr[i].nurId, vr[i].docId, vr[i].diagnosis, vr[i].medicine.med1, vr[i].medicine.med2, vr[i].medicine.med3, &vr[i].charge) != EOF) {
		i++;
	}
	fclose(fptr);
	return i;
}

void patientVisit() {
	//Variable declarations
	int i = 0, choice;
	char backToMenu;
	do {
		choice = subMenu(1);
		while (choice < 1 || choice>7) {
			printf("Invalid input ! \n");
			printf("Please enter again.\n\n");
			printf("Please enter your option : ");
			rewind(stdin);
			scanf("%d", &choice);
			printf("\n");
		}
		switch (choice) {
		case 1:
			backToMenu = add();
			backToMenu = toupper(backToMenu);
			printf("\n");
			break;
		case 2:
			backToMenu = search();
			backToMenu = toupper(backToMenu);
			printf("\n");
			break;
		case 3:
			backToMenu = modify();
			backToMenu = toupper(backToMenu);
			printf("\n");
			break;
		case 4:
			display();
			printf("\n\nPress any key to back to Patient Visit Menu : ");
			scanf(" %c", &backToMenu);
			printf("\n");
			backToMenu = 'N';
			break;
		case 5:
			backToMenu = report();
			backToMenu = toupper(backToMenu);
			printf("\n");
			break;
		case 6:
			delete();
			printf("\n\nPress any key to back to Patient Visit Menu : ");
			scanf(" %c", &backToMenu);
			printf("\n");
			backToMenu = 'N';
			break;
		case 7:
			return;
		}
	} while (backToMenu == 'N');
}

//Add
char add() {
	int i, sizeOfRecord;
	char repeat;
	sizeOfRecord = readPatientVisitFile();
	i = sizeOfRecord;
	FILE *fp;
	fp = fopen("patient visit records.txt", "a");
	if (fp == NULL) {
		printf("Unable to open patient visit record.");
		exit(-1);
	}
	GetLocalTime(&t);
	printf("\n    ADD\n");
	printf("    ===\n");
	do {
		vr[i].recNo = vr[i - 1].recNo + 1;
		GetLocalTime(&t);
		//Prompt and validate user input data
		patientIdDataInputAndValidate(i);
		nurseIdDataInputAndValidate(i);
		doctorIdDataInputAndValidate(i);
		patientVisitOtherDataInputAndValidate(i);
		//Get the date and time
		vr[i].date.day = t.wDay;
		vr[i].date.month = t.wMonth;
		vr[i].date.year = t.wYear;
		vr[i].time.h = t.wHour;
		vr[i].time.m = t.wMinute;
		//Write into file
		displayHeader();
		displayRecord(i);
		fprintf(fp, "[%d]%d/%d/%d|%d:%02d|%.5s\n%.3s|%.3s\n%s\n%s\n%s\n%s\n%.2f\n", vr[i].recNo, vr[i].date.day, vr[i].date.month, vr[i].date.year, vr[i].time.h, vr[i].time.m, vr[i].patId, vr[i].nurId, vr[i].docId, vr[i].diagnosis, vr[i].medicine.med1, vr[i].medicine.med2, vr[i].medicine.med3, vr[i].charge);
		//
		repeat = askForRepetition(fp);
		//
		i++;
	} while (repeat == 'Y');
	return 'n';
}

//Display
void display() {
	int i, sizeOfRecord;
	sizeOfRecord = readPatientVisitFile();
	printf("\n    DISPLAY\n");
	printf("    =======\n");
	displayHeader();
	for (i = 0; i < sizeOfRecord; i++) {
		displayRecord(i);
	}
}

//Search
char search() {
	int i, uRecNo, sizeOfRecord, choice, error;
	char uPatientId[6], repeat;
	sizeOfRecord = readPatientVisitFile();
	printf("\n    SEARCH\n");
	printf("    ======\n");
	do {
		choice = subMenu(2);
		while (choice != 1 && choice != 2) {
			printf("Invalid input ! \n");
			printf("Please enter again.\n\n");
			choice = subMenu(2);
		}
		if (choice == 1) {
			do {
				printf("Please enter Record No. : ");
				rewind(stdin);
				scanf("%d", &uRecNo);
				if (uRecNo < 1 || uRecNo > sizeOfRecord) {
					printf("\nNo record found ! \n");
					printf("Please enter again.\n\n");
				}
				else {
					displayHeader();
					for (i = 0; i < sizeOfRecord; i++) {
						if (vr[i].recNo == uRecNo) {

							displayRecord(i);
							printf("\n");
						}
					}
				}
			} while (uRecNo < 1 || uRecNo > sizeOfRecord);
		}
		else if (choice == 2) {
			do {
				error = 0;
				printf("Please enter Patient ID : ");
				rewind(stdin);
				scanf("%[^\n]", uPatientId);
				for (i = 0; i < sizeOfRecord; i++) {
					if (strcmp(vr[i].patId, uPatientId) == 0)
						break;
					else
						error++;
				}
				if (error == sizeOfRecord) {
					printf("\nNo record found ! \n");
					printf("Please enter again.\n\n");
				}
			} while (error == sizeOfRecord);
			displayHeader();
			for (i = 0; i < sizeOfRecord; i++) {
				if (strcmp(vr[i].patId, uPatientId) == 0)
					displayRecord(i);
			}
		}
		//
		printf("Any more? (Y to continue) : ");
		scanf(" %c", &repeat);
		repeat = toupper(repeat);
		//
	} while (repeat == 'Y');
	return 'n';
}

//Modify
char modify() {
	int i, sizeOfRecord, uRecNo;
	char repeat;
	sizeOfRecord = readPatientVisitFile();
	printf("\n    MODIFY\n");
	printf("    ======\n");
	do {
		do {
			printf("Please enter the record No. you want to modify : ");
			scanf("%d", &uRecNo);
			if (uRecNo <= 0 || uRecNo > sizeOfRecord)
				printf("No record found ! \n");
			else {
				for (i = 0; i <= sizeOfRecord; i++) {
					if (vr[i].recNo == uRecNo) {
						//Data to be modified
						displayHeader();
						displayRecord(i);
						//Prompt and validate user input data
						patientIdDataInputAndValidate(i);
						nurseIdDataInputAndValidate(i);
						doctorIdDataInputAndValidate(i);
						patientVisitOtherDataInputAndValidate(i);
						//Display modified data
						printf("\n");
						displayHeader();
						displayRecord(i);
					}
				}
			}
		} while (uRecNo <= 0 || uRecNo > sizeOfRecord);
		FILE *fp;
		fp = fopen("patient visit records.txt", "w");
		if (fp == NULL) {
			printf("Unable to open patient visit record.");
			exit(-1);
		}
		for (i = 0; i < sizeOfRecord; i++) {
			fprintf(fp, "[%d]%d/%d/%d|%d:%02d|%.5s\n%.3s|%.3s\n%s\n%s\n%s\n%s\n%.2f\n", vr[i].recNo, vr[i].date.day, vr[i].date.month, vr[i].date.year, vr[i].time.h, vr[i].time.m, vr[i].patId, vr[i].nurId, vr[i].docId, vr[i].diagnosis, vr[i].medicine.med1, vr[i].medicine.med2, vr[i].medicine.med3, vr[i].charge);
		}
		fclose(fp);
		//
		repeat = askForRepetition(fp);
		//
	} while (repeat == 'Y');
	return 'n';
}

//Report Summary
char report() {
	int sizeOfRecord, month, year, i, error;
	int totalPatient;
	double totalRevenue;
	char repeat;
	sizeOfRecord = readPatientVisitFile();
	printf("\n    REPORT\n");
	printf("    ======");
	do {
		do {
			error = 0;
			totalPatient = 0;
			totalRevenue = 0;
			printf("\nPlease enter the month : ");
			scanf("%d", &month);
			while (month < 1 || month>12) {
				printf("\nInvalid month ! \n");
				printf("Please enter the month : ");
				scanf("%d", &month);
			}
			printf("Please enter the year : ");
			scanf("%d", &year);

			for (i = 0; i < sizeOfRecord; i++) {
				if (vr[i].date.month == month && vr[i].date.year == year) {
					totalPatient++;
					totalRevenue += vr[i].charge;
				}
				else
					error++;
			}
			if (error == sizeOfRecord) {
				printf("\nNo record found ! \n");
				printf("Please enter again.\n");
			}
			else {
				printf("\nFor the month %d at %d\n", month, year);
				printf("Total patient visit : %d\n", totalPatient);
				printf("Total revenue : RM%.2f\n", totalRevenue);
			}
		} while (error == sizeOfRecord);
		printf("\nAny more? (Y to continue) : ");
		scanf(" %c", &repeat);
		repeat = toupper(repeat);
	} while (repeat == 'Y');
	return 'n';
}

//Delete;
void delete() {
	int sizeOfRecord, uRecNo, i, x, sizeOfRecordR;
	char confirmation;
	sizeOfRecord = readPatientVisitFile();
	sizeOfRecordR = sizeOfRecord;
	printf("\n    DELETE\n");
	printf("    ======\n");
	do {
		printf("Please enter the record No. you want to delete : ");
		scanf("%d", &uRecNo);
		if (uRecNo <= 0 || uRecNo > sizeOfRecord)
			printf("\nNo record found ! \n\n");
		else
			for (i = 0; i < sizeOfRecord; i++) {
				if (vr[i].recNo == uRecNo) {
					displayHeader();
					displayRecord(i);
					printf("Are you sure you want to delete this record ? (Y to confirm):");
					scanf(" %c", &confirmation);
					confirmation = toupper(confirmation);
					if (confirmation != 'Y')
						return;
					else {
						for (i = 0; i < sizeOfRecord; i++) {
							if (vr[i].recNo == uRecNo) {
								for (x = i; x < sizeOfRecord; x++) {
									vr[x] = vr[x + 1];

								}
								i--;
								sizeOfRecord--;
							}
						}
						for (i = 0; i < sizeOfRecordR; i++) {
							if (vr[i].recNo > uRecNo) {
								vr[i].recNo--;
							}
						}
						FILE *fp;
						fp = fopen("patient visit records.txt", "w");
						if (fp == NULL) {
							printf("Unable to open patient visit record.");
							exit(-1);
						}

						for (i = 0; i < sizeOfRecord; i++) {

							fprintf(fp, "[%d]%d/%d/%d|%d:%02d|%.5s\n%.3s|%.3s\n%s\n%s\n%s\n%s\n%.2f\n", vr[i].recNo, vr[i].date.day, vr[i].date.month, vr[i].date.year, vr[i].time.h, vr[i].time.m, vr[i].patId, vr[i].nurId, vr[i].docId, vr[i].diagnosis, vr[i].medicine.med1, vr[i].medicine.med2, vr[i].medicine.med3, vr[i].charge);
						}
						fclose(fp);
						printf("\nDeleted succesfully ! ");
						return;
					}
				}
			}
	} while (uRecNo <= 0 || uRecNo > sizeOfRecord);
}
void displayHeader() {
	printf("No.  Date         Time    Pat ID  Nur ID   Doc ID   Diagnosis                      Medicine                   Fees\n");
	printf("===  ====         ====    ======  ======   ======   =========                      ========                   ====\n");
}
void displayRecord(i) {
	printf("[%02d] %02d/%02d/%d   %02d:%02d   %-5.5s   %.3s      %.3s      %-30.30s %-24s   %-.2f\n", vr[i].recNo, vr[i].date.day, vr[i].date.month, vr[i].date.year, vr[i].time.h, vr[i].time.m, vr[i].patId, vr[i].nurId, vr[i].docId, vr[i].diagnosis, vr[i].medicine.med1, vr[i].charge);
	printf("                                                                                   %-30s             \n", vr[i].medicine.med2);
	printf("                                                                                   %-30s             \n", vr[i].medicine.med3);
	printf("---------------------------------------------------------------------------------------------------------------------\n");
}

void patientIdDataInputAndValidate(i) {
	//Patient
	printf("Patient ID : ");
	scanf(" %[^\n]", vr[i].patId);
	patientIdDataValidate(vr[i].patId);

}


void nurseIdDataInputAndValidate(i) {
	//Nurse
	printf("Nurse ID : ");
	rewind(stdin);
	scanf("%[^\n]", vr[i].nurId);
	nurseIdDataValidate(vr[i].nurId);
}
void nurseIdDataValidate(char nurseId[]){
	int strlength;
	strlength = strlen(nurseId);
	while (nurseId[0] != 'N' || strlength < 3 || strlength>3 || !(isdigit(nurseId[1]) && isdigit(nurseId[2]))) {
		//Data validate
		if (nurseId[0] != 'N') {
			printf("\nNurse ID must start with the letter 'N'.");
		}
		if (strlength < 3 || strlength>3) {
			printf("\nNurse ID must have 3 character only.");
		}
		if (!(isdigit(nurseId[1]) && isdigit(nurseId[2]))) {
			printf("\nLast 2 character must be number.");
		}
		printf("\nPlease try again.\n\n");
		printf("Nurse ID : ");
		rewind(stdin);
		scanf("%[^\n]", nurseId);
		strlength = strlen(nurseId);
	}
}

void doctorIdDataInputAndValidate(i) {
	//Doctor
	printf("Doctor ID : ");
	rewind(stdin);
	scanf("%[^\n]", vr[i].docId);
	doctorIdDataValidate(vr[i].docId);
}
void doctorIdDataValidate(char doctorId[]){
	int strlength;
	strlength = strlen(doctorId);
	while (doctorId[0] != 'D' || strlength < 3 || strlength>3 || !(isdigit(doctorId[1]) && isdigit(doctorId[2]))) {
		//Data validate
		if (doctorId[0] != 'D') {
			printf("\nDoctor ID must start with the letter 'D'.");
		}
		if (strlength < 3 || strlength>3) {
			printf("\nDoctor ID must have 3 character only.");
		}
		if (!(isdigit(doctorId[1]) && isdigit(doctorId[2]))) {
			printf("\nLast 2 character must be number.");
		}
		printf("\nPlease try again.\n\n");
		printf("Doctor ID : ");
		rewind(stdin);
		scanf("%[^\n]", doctorId);
		strlength = strlen(doctorId);
	}
}
void patientVisitOtherDataInputAndValidate(i) {
	printf("Diagnosis : ");
	rewind(stdin);
	scanf("%[^\n]", vr[i].diagnosis);
	printf("Medicine 1 : ");
	rewind(stdin);
	scanf("%[^\n]", vr[i].medicine.med1);
	printf("Medicine 2 : ");
	rewind(stdin);
	scanf("%[^\n]", vr[i].medicine.med2);
	printf("Medicine 3 : ");
	rewind(stdin);
	scanf("%[^\n]", vr[i].medicine.med3);
	printf("Fees : ");
	rewind(stdin);
	scanf("%lf", &vr[i].charge);
}

char askForRepetition(FILE *fp) {
	char repeat;
	printf("\nAlready updated the file\n");
	printf("Any more? (Y to continue) : ");
	scanf(" %c", &repeat);
	printf("\n");
	repeat = toupper(repeat);
	if (repeat != 'Y') {
		fclose(fp);
	}
	return repeat;
}
