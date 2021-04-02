#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#pragma warning (disable : 4996)

typedef struct {
	char patientID[15];
	char name[30];
	char gender;
	char contactNo[15];
	char allergies[20];
	double height, weight, bmi;
}PatientInfo;
PatientInfo info[10];

void addInfo();
void displayInfo();
void searchInfo();
void modifyInfo();
void calcBmi();
void anotherMenu();
void displayModifyArea();
void invalidSubmenu();
void choosePatientInfoMenu();
void displaySearchInfo();
int readRecord();

void allMenus(int);
void errorMessage();
int genderValidate(char);
void patientIdDataValidate(char patientId[]);

void patientInfo() {

	allMenus(2);
	choosePatientInfoMenu();
}

void addInfo() {
	PatientInfo info;
	FILE*ptr;
	char addMore[2];
	int i;
	ptr = fopen("patientInfo.bin", "ab");
	if (ptr == NULL) {
		printf("unable to opne file\n");
		exit(-1);
	}
	do {

		printf("\nAdd more patient information? (y = yes, n = no) :");
		rewind(stdin);
		scanf("%s", &addMore);
		if (strcmp(addMore, "n") != 0 && strcmp(addMore, "N") != 0) {

			printf("\nAdd Patient Information\n");
			printf("=======================\n");

			
			printf("Patient ID : ");
			rewind(stdin);
			scanf("%s", &info.patientID);
			patientIdDataValidate(info.patientID);

			printf("Patient Name : ");
			rewind(stdin);
			scanf("%[^\n]", &info.name);

			do {
				printf("Gender : ");
				rewind(stdin);
				scanf("%c", &info.gender);
				info.gender = toupper(info.gender);
				i = genderValidate(info.gender);
			} while (i == 1);

			printf("Contact Number : ");
			rewind(stdin);
			scanf("%s", &info.contactNo);

			printf("Allergies : ");
			rewind(stdin);
			scanf("%s", &info.allergies);

			printf("Height (m) : ");
			rewind(stdin);
			scanf("%lf", &info.height);
			while (info.height >= 2) {
				printf("%.2lf is invalid.\n", info.height);
				printf("Please enter the height in meter(m) : ");
				rewind(stdin);
				scanf("%lf", &info.height);

			}
			printf("Weight (kg) : ");
			rewind(stdin);
			scanf("%lf", &info.weight);

			fwrite(&info, sizeof(PatientInfo), 1, ptr);
		}
	} while (strcmp(addMore, "n") != 0 && strcmp(addMore, "N") != 0);

	printf("Done adding.\n");

	fclose(ptr);

	anotherMenu();
}

void displayInfo() {

	int i = 0, qtyInfo;

	FILE*ptr;
	ptr = fopen("patientInfo.bin", "rb");

	if (ptr == NULL) {
		printf("unable to opne file\n");
		exit(-1);
	}

	qtyInfo = readRecord();

	printf("\nPatient ID             Patient Name                  Gender        Contact Number         Allergies           Height(m)      Weight(kg)\n");
	printf("==========             ============                  ======        ==============         =========           =========      ==========\n");

	while (fread(&info, sizeof(PatientInfo), qtyInfo, ptr) != 0); {

		for (i = 0; i < qtyInfo; i++) {
			printf("%-15s        %-30s  %-2c          %-15s        %-20s  %.2lf           %.2lf\n", info[i].patientID, info[i].name, info[i].gender, info[i].contactNo, info[i].allergies, info[i].height, info[i].weight);
		}
	}
	fclose(ptr);

	anotherMenu();

}

void searchInfo() {
	FILE*ptr;
	ptr = fopen("patientInfo.bin", "rb");

	if (ptr == NULL) {
		printf("unable to opne file\n");
		exit(-1);
	}

	int i = 0, choice, qtyInfo;
	char id[15], name[20], contact[15], anotherArea[2];

	qtyInfo = readRecord();

	displaySearchInfo();

	printf("Please enter your choice : ");
	scanf("%d", &choice);

	switch (choice) {

	case 1: {

		printf("\nEnter patient's ID : ");
		rewind(stdin);
		scanf("%s", &id);
		printf("\nPatient ID             Patient Name                 Gender        Contact Number         Allergies           Height(m)      Weight(kg)\n");
		printf("==========             ============                 ======        ==============         =========           =========      ==========\n");

		while (fread(&info, sizeof(PatientInfo), qtyInfo, ptr) != 0) {
			i++;
		}
		for (i = 0; i < qtyInfo; i++) {
			if (strcmp(id, info[i].patientID) == 0) {

				printf("%-15s        %-30s  %-2c           %-15s      %-20s  %.2lf           %.2lf\n", info[i].patientID, info[i].name, info[i].gender, info[i].contactNo, info[i].allergies, info[i].height, info[i].weight);
			}
		}
	}
			break;

	case 2: {
		printf("\nEnter patient's name : ");
		rewind(stdin);
		scanf("%[^\n]", &name);
		printf("\nPatient ID             Patient Name                 Gender        Contact Number         Allergies           Height(m)      Weight(kg)\n");
		printf("==========             ============                 ======        ==============         =========           =========      ==========\n");

		while (fread(&info, sizeof(PatientInfo), qtyInfo, ptr) != 0) {
			i++;
		}
		for (i = 0; i < qtyInfo; i++) {
			if (strcmp(name, info[i].name) == 0) {
				printf("%-15s        %-30s  %-2c           %-15s      %-20s  %.2lf           %.2lf\n", info[i].patientID, info[i].name, info[i].gender, info[i].contactNo, info[i].allergies, info[i].height, info[i].weight);
			}
		}
	}
			break;

	case 3: {
		printf("\nEnter patient's contact number : ");
		rewind(stdin);
		scanf("%s", &contact);

		printf("\nPatient ID             Patient Name                 Gender        Contact Number         Allergies           Height(m)      Weight(kg)\n");
		printf("==========             ============                 ======        ==============         =========           =========      ==========\n");

		while (fread(&info, sizeof(PatientInfo), qtyInfo, ptr) != 0) {
			i++;
		}

		for (i = 0; i < qtyInfo; i++) {
			if (strcmp(contact, info[i].contactNo) == 0) {

				printf("%-15s        %-30s  %-2c           %-15s      %-20s  %.2lf           %.2lf\n", info[i].patientID, info[i].name, info[i].gender, info[i].contactNo, info[i].allergies, info[i].height, info[i].weight);
			}
		}
	}
			break;

	default:
		printf("Invalid choice!\n");
	}

	do {

		printf("\nSearch another area? (y-yes, n-no) : ");
		rewind(stdin);
		scanf("%s", &anotherArea);

		if (strcmp(anotherArea, "n") != 0 && strcmp(anotherArea, "N") != 0) {

			displaySearchInfo();

			printf("Please enter your choice(1-3) : ");
			scanf("%d", &choice);

			switch (choice) {
			case 1: {

				printf("\nEnter patient's ID : ");
				rewind(stdin);
				scanf("%s", &id);

				printf("\nPatient ID             Patient Name                 Gender        Contact Number         Allergies           Height(m)      Weight(kg)\n");
				printf("==========             ============                 ======        ==============         =========           =========      ==========\n");

				while (fread(&info, sizeof(PatientInfo), qtyInfo, ptr) != 0) {
					i++;
				}
				for (i = 0; i < qtyInfo; i++) {
					if (strcmp(id, info[i].patientID) == 0) {

						printf("%-15s        %-30s  %-2c           %-15s      %-20s  %.2lf           %.2lf\n", info[i].patientID, info[i].name, info[i].gender, info[i].contactNo, info[i].allergies, info[i].height, info[i].weight);
					}
				}
			}
					break;

			case 2: {
				printf("\nEnter patient's name : ");
				rewind(stdin);
				scanf("%[^\n]", &name);

				printf("\nPatient ID             Patient Name                  Gender        Contact Number         Allergies           Height(m)      Weight(kg)\n");
				printf("==========             ============                  ======        ==============         =========           =========      ==========\n");

				while (fread(&info, sizeof(PatientInfo), qtyInfo, ptr) != 0) {
					i++;
				}
				for (i = 0; i < qtyInfo; i++) {
					if (strcmp(name, info[i].name) == 0) {
						printf("%-15s        %-30s  %-2c           %-15s      %-20s  %.2lf           %.2lf\n", info[i].patientID, info[i].name, info[i].gender, info[i].contactNo, info[i].allergies, info[i].height, info[i].weight);
					}
				}
			}
					break;

			case 3: {
				printf("\nEnter patient's contact number : ");
				rewind(stdin);
				scanf("%s", &contact);

				printf("\nPatient ID             Patient Name                 Gender        Contact Number         Allergies           Height(m)      Weight(kg)\n");
				printf("==========             ============                 ======        ==============         =========           =========      ==========\n");

				while (fread(&info, sizeof(PatientInfo), qtyInfo, ptr) != 0) {
					i++;
				}

				for (i = 0; i < qtyInfo; i++) {
					if (strcmp(contact, info[i].contactNo) == 0) {

						printf("%-15s        %-30s  %-2c           %-15s      %-20s  %.2lf           %.2lf\n", info[i].patientID, info[i].name, info[i].gender, info[i].contactNo, info[i].allergies, info[i].height, info[i].weight);
					}
				}
			}
					break;

			default:
				printf("Invalid choice!\n");
			}
		}
	} while (strcmp(anotherArea, "n") != 0 && strcmp(anotherArea, "N") != 0);

	fclose(ptr);

	anotherMenu();

}

void modifyInfo() {
	char id[15], anotherArea[2];
	int i = 0, choice, qtyInfo;
	int y;
	qtyInfo = readRecord();

	FILE*ptr;
	ptr = fopen("patientInfo.bin", "rb");

	if (ptr == NULL) {
		printf("unable to opne file\n");
		exit(-1);
	}
	while (fread(&info, sizeof(PatientInfo), qtyInfo, ptr) != 0) {

		fclose(ptr);

		printf("\nPlease enter the patient ID to be modified : ");
		scanf("%s", &id);

		for (i = 0; i < qtyInfo; i++) {
			if (strcmp(id, info[i].patientID) == 0) {
				printf("\nPatient ID             Patient Name                 Gender        Contact Number          Allergies           Height(m)      Weight(kg)\n");
				printf("==========             ============                 ======        ==============          =========           =========      ==========\n");

				printf("%-15s        %-30s %-2c           %-15s        %-20s  %.2lf           %.2lf\n", info[i].patientID, info[i].name, info[i].gender, info[i].contactNo, info[i].allergies, info[i].height, info[i].weight);

				displayModifyArea();

				printf("\nPlease select an area to modify(1-6) : ");
				scanf("%d", &choice);

				switch (choice) {

				case 1: {
					printf("\nPatient name : ");
					rewind(stdin);
					scanf("%[^\n]", &info[i].name);
					break;
				}

				case 2: {
					do {
						printf("\nPatient gender : ");
						rewind(stdin);
						scanf("%s", &info[i].gender);
						info[i].gender = toupper(info[i].gender);
						y = genderValidate(info[i].gender);
					} while (y == 1);
					break;

				}
				case 3: {
					printf("\nPatient contact number : ");
					rewind(stdin);
					scanf("%s", &info[i].contactNo);
					break;
				}

				case 4: {
					printf("\nPatient allergies : ");
					rewind(stdin);
					scanf("%s", &info[i].allergies);
					break;
				}

				case 5: {
					printf("\nHeight (m) : ");
					rewind(stdin);
					scanf("%lf", &info[i].height);
					while (info[i].height >= 2) {
						printf("%.2lf is invalid.\n", info[i].height);
						printf("Please enter the height in meter(m) : ");
						rewind(stdin);
						scanf("%lf", &info[i].height);
					}
					break;
				}

				case 6: {
					printf("\nWeight (kg) : ");
					rewind(stdin);
					scanf("%lf", &info[i].weight);
					break;
				}

				default:
					printf("\nInvalid area!!\n");
				}

				do {
					printf("\nModify another area? (y-yes, n-no) : ");
					rewind(stdin);
					scanf("%s", &anotherArea);

					if (strcmp(anotherArea, "n") != 0 && strcmp(anotherArea, "N") != 0) {

						displayModifyArea();

						printf("\nPlease select an area to modify(1-6) : ");
						scanf("%d", &choice);

						switch (choice) {

						case 1: {
							printf("\nPatient name : ");
							rewind(stdin);
							scanf("%[^\n]", &info[i].name);
							break;
						}

						case 2: {
							printf("\nPatient gender : ");
							rewind(stdin);
							scanf("%s", &info[i].gender);
							info[i].gender = toupper(info[i].gender);
							while (info[i].gender != 'F' && info[i].gender != 'M') {
								printf("%c is an invalid gender.\n", info[i].gender);
								printf("Please re-enter the gender (F=Female, M=Male) : ");
								rewind(stdin);
								scanf("%c", &info[i].gender);
							}
							break;
						}

						case 3: {
							printf("\nPatient contact number : ");
							rewind(stdin);
							scanf("%s", &info[i].contactNo);
							break;
						}

						case 4: {
							printf("\nPatient allergies : ");
							rewind(stdin);
							scanf("%s", &info[i].allergies);
							break;
						}

						case 5: {
							printf("\nHeight (m) : ");
							rewind(stdin);
							scanf("%lf", &info[i].height);
							while (info[i].height >= 2) {
								printf("%.2lf is invalid.\n", info[i].height);
								printf("Please enter the height in meter(m) : ");
								rewind(stdin);
								scanf("%lf", &info[i].height);
							}
							break;
						}

						case 6: {
							printf("\nWeight (kg) : ");
							rewind(stdin);
							scanf("%lf", &info[i].weight);
							break;
						}

						default:
							printf("\nInvalid area!!\n\n");
						}
					}
				} while (strcmp(anotherArea, "n") != 0 && strcmp(anotherArea, "N") != 0);
			}
		}
	}

	ptr = fopen("patientInfo.bin", "wb");
	fwrite(&info, sizeof(PatientInfo), qtyInfo, ptr);

	fclose(ptr);

	anotherMenu();

}

void calcBmi() {

	int i = 0, qtyInfo;
	char status[30];
	FILE*ptr;

	ptr = fopen("patientInfo.bin", "rb");

	if (ptr == NULL) {
		printf("unable to opne file\n");
		exit(-1);
	}

	qtyInfo = readRecord();

	printf("\nPatient ID             Patient Name                    Body Mass Index(BMI)        Status\n");
	printf("==========             ============                    ====================        =============\n");

	while (fread(&info, sizeof(PatientInfo), qtyInfo, ptr) != 0) {
		i++;
	}

	for (i = 0; i < qtyInfo; i++) {

		info[i].bmi = info[i].weight / (info[i].height*info[i].height);

		if (info[i].bmi < 16.0 && info[i].bmi >= 0) {
			strcpy(status, "Severely Underweight");
		}

		else if (info[i].bmi >= 16.0 && info[i].bmi <= 18.5) {
			strcpy(status, "Underweight");
		}

		else if (info[i].bmi >= 18.6 && info[i].bmi <= 25.0) {
			strcpy(status, "Normal Weight");
		}

		else if (info[i].bmi >= 25.1 && info[i].bmi <= 30.0) {
			strcpy(status, "Overweight");
		}

		else if (info[i].bmi >= 30.1 && info[i].bmi <= 35.0) {
			strcpy(status, "Moderately Obese");
		}

		else if (info[i].bmi >= 35.1) {
			strcpy(status, "Severely Obese");
		}

		printf("%-15s        %-30s  %.2lf                       %-30s\n", info[i].patientID, info[i].name, info[i].bmi, status);

	}
	fclose(ptr);

	anotherMenu();

}

void displayModifyArea() {

	printf("\nModify Area\n");
	printf("===========\n");
	printf("1. Modify Name\n");
	printf("2. Modify Gender\n");
	printf("3. Modify Contact Number\n");
	printf("4. Modify Allergies\n");
	printf("5. Modify Height\n");
	printf("6. Modify Weight\n");

}

void invalidSubmenu() {
	int submenu;

	do {

		errorMessage();
		rewind(stdin);
		scanf("%d", &submenu);
		printf("\n");
		switch (submenu) {
		case 1:
			addInfo();
			break;
		case 2:
			searchInfo();
			break;
		case 3:
			modifyInfo();
			break;
		case 4:
			displayInfo();
			break;
		case 5:
			calcBmi();
			break;
		case 6:
			return;
			break;

		default:
			invalidSubmenu();
		}
	} while (submenu >= 7 && submenu <= 0);

}

void choosePatientInfoMenu() {

	int submenu;

	printf("Please enter your option : ");
	scanf("%d", &submenu);
	printf("\n");

	switch (submenu) {
	case 1:
		addInfo();
		break;
	case 2:
		searchInfo();
		break;
	case 3:
		modifyInfo();
		break;
	case 4:
		displayInfo();
		break;
	case 5:
		calcBmi();
		break;
	case 6:
		return;
		break;
	default:
		invalidSubmenu();
	}

}
void anotherMenu() {

	char anotherMenu[10];

	printf("\n\nPress any key to back to Patient Info Menu : ");
	scanf("%s", &anotherMenu);
	printf("\n");
	allMenus(2);
	choosePatientInfoMenu();
}

void displaySearchInfo() {

	printf("Search Patient Information\n");
	printf("==========================\n");
	printf("1. Search by using patient's ID\n");
	printf("2. Search by using patient's name\n");
	printf("3. Search by using patient's contact number\n\n");

}

int readRecord() {
	PatientInfo info;
	int record = 0;
	FILE*ptr;
	ptr = fopen("patientInfo.bin", "rb");

	if (ptr == NULL) {
		printf("unable to opne file\n");
		exit(-1);
	}
	while (fread(&info, sizeof(info), 1, ptr) != 0) {

		record++;

	}
	return record;
	fclose(ptr);

}