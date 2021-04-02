#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#pragma warning (disable : 4996)
char deleteEmployee();
char displayAll();
char viewRecord();
char modifyRecord();
char addRecord();
int readFile();
//validation
void staffIdValidate(char staffId[]);
int genderValidate(char);
//
void allMenus(int);
void errorMessage();
struct Date {
	int day, month, year;
};

struct HomeAdress {
	int doorPlate;
	char taman[20], country[40];
};

struct staffRecord {
	char id[5], name[12], designation[12], gender, groupBlood[12], nationality[12];
	struct Date dateEmp;
	struct HomeAdress adress;
	int contactNo1, contactNo2;
	char qualitification[10], qualitificationUni[10];

};
struct staffRecord record[20];

void staffInfo()
{
	int choice;
	char answer, backToMenu;

	do {
		allMenus(4);
		printf("Please enter your option : ");
		do {
			rewind(stdin);
			scanf("%d", &choice);
			printf("\n");
			switch (choice)
			{
			case 1:
				backToMenu = viewRecord();
				break;
			case 2:
				backToMenu = modifyRecord();
				break;
			case 3:
				backToMenu = addRecord();
				break;
			case 4:
				backToMenu = displayAll();
				break;
			case 5:
				backToMenu = deleteEmployee();
				break;
			case 6:
				return;
			default:
				errorMessage();
			}
		} while (choice > 6 || choice < 1);
		/*rewind(stdin);
		printf("Do you want to choose another choice???");
		scanf("%c", &answer);*/
	} while (backToMenu == 'n');
}
char displayAll()
{
	int i, sizeOfFile;
	sizeOfFile = readFile();
	printf("\n=========================================================================The All information of staff==================================================\n");
	printf("%-5s%-12s%-12s%-8s%-12s%-12s%-19s%-39s%-17s%s\n", "ID", "NAME", "DESIGNATION", "GENDER", "GROUPBLOOD", "NATIONALITY", "DATEEMPLOYED", "HOME ADDRESS", "CONTACT-NO", "QUALITIFICATION");
	printf("=======================================================================================================================================================\n");

	for (i = 0; i < sizeOfFile; i++)
	{
		printf("%-5s%-12s%-12s%-8c%-12s%-12s%02d/%02d/%04d %10d,%-15s,%-20s%03d-%d\t%s(%s)\n", record[i].id, record[i].name, record[i].designation, record[i].gender, record[i].groupBlood, record[i].nationality, record[i].dateEmp.day, record[i].dateEmp.month, record[i].dateEmp.year, record[i].adress.doorPlate, record[i].adress.taman, record[i].adress.country, record[i].contactNo1, record[i].contactNo2, record[i].qualitification, record[i].qualitificationUni);

	}
	return'n';

}
int readFile() {
	/*struct Date dateEmp;*/
	int i = 0;
	FILE*staff;
	staff = fopen("staff.txt", "r");

	if (staff == NULL)
	{
		printf("Unable to open the staff.txt file.");
		system("pause");
		exit(-1);
	}
	while (fscanf(staff, " %[^|]|%[^|]|%[^|]|%c|%[^|]|%[^|]|%d/%d/%d|%d,%[^,],%[^|]|%d-%d|%[^(](%[^)])|\n", &record[i].id, &record[i].name, &record[i].designation, &record[i].gender, &record[i].groupBlood, &record[i].nationality, &record[i].dateEmp.day, &record[i].dateEmp.month, &record[i].dateEmp.year, &record[i].adress.doorPlate, &record[i].adress.taman, &record[i].adress.country, &record[i].contactNo1, &record[i].contactNo2, &record[i].qualitification, &record[i].qualitificationUni) != EOF)
	{
		i++;
	}
	fclose(staff);
	return i;
}
char viewRecord()
{
	int i = 0, sizeOfFile;
	char staffId[5], answer;
	sizeOfFile = readFile();
	/*struct Date dateEmp;*/
	do {

		printf("Enter the ID of staff : ");
		scanf("%s", &staffId);

		printf("\n%-5s%-12s%-12s%-8s%-12s%-12s%-19s%-39s%-17s%s\n", "ID", "NAME", "DESIGNATION", "GENDER", "GROUPBLOOD", "NATIONALITY", "DATEEMPLOYED", "HOME ADDRESS", "CONTACT-NO", "QUALITIFICATION");
		printf("========================================================================================================================================================\n");
		for (i = 0; i < sizeOfFile; i++) {
			if (strcmp(staffId, record[i].id) == 0) {
				printf("%-5s%-12s%-12s%-8c%-12s%-12s%02d/%02d/%04d %10d,%-15s,%-20s%03d-%d\t%s(%s)\n", record[i].id, record[i].name, record[i].designation, record[i].gender, record[i].groupBlood, record[i].nationality, record[i].dateEmp.day, record[i].dateEmp.month, record[i].dateEmp.year, record[i].adress.doorPlate, record[i].adress.taman, record[i].adress.country, record[i].contactNo1, record[i].contactNo2, record[i].qualitification, record[i].qualitificationUni);
			}

		}
		rewind(stdin);
		printf("\nDo you want to continue search???");
		scanf("%c", &answer);

	} while (answer == 'Y' || answer == 'y');
	return 'n';


}
char addRecord()
{
	int i;
	FILE*staff;
	staff = fopen("staff.txt", "a");
	char answer;
	while (staff == NULL)
	{
		printf("Unable to open staff.txt file!\n");
		system("pause");
		exit(-1);
	}
	struct staffRecord record;
	//struct Date dateEmp;*/
	do {
		rewind(stdin);
		printf("Enter the id : ");
		rewind(stdin);
		scanf("%s", record.id);
		staffIdValidate(record.id);
		printf("Enter the staff name : ");
		rewind(stdin);
		scanf("%[^\n]", record.name);
		printf("Enter the designation : ");
		rewind(stdin);
		scanf("%s", record.designation);


		do {
			printf("Enter the gender of staff(F/M): ");
			rewind(stdin);
			scanf("%c", &record.gender);
			i = genderValidate(record.gender);
		} while (i == 1);

		do {
			printf("Enter the groupBlood(AB/O/A/B) : ");
			rewind(stdin);
			scanf("%s", record.groupBlood);
			if (strcmp(record.groupBlood, "AB") != 0 && strcmp(record.groupBlood, "A") != 0 && strcmp(record.groupBlood, "B") != 0 && strcmp(record.groupBlood, "O") != 0) {
				printf("\nInvalid groupBlood");
				printf("\nPlease enter again\n\n");
			}
		} while (strcmp(record.groupBlood, "AB") != 0 && strcmp(record.groupBlood, "A") != 0 && strcmp(record.groupBlood, "B") != 0 && strcmp(record.groupBlood, "O") != 0);

		printf("Enter the nationality : ");
		rewind(stdin);
		scanf("%s", record.nationality);

		printf("Enter the date employed : ");
		rewind(stdin);
		scanf("%d %d %d", &record.dateEmp.day, &record.dateEmp.month, &record.dateEmp.year);
		do {
			if (record.dateEmp.month < 1 || record.dateEmp.month>12 || record.dateEmp.day < 1 || record.dateEmp.day>31 || record.dateEmp.year < 0)
			{

				printf("The date employed is invalid .\n");
				printf("Enter the date employed : ");
				rewind(stdin);
				scanf("%d %d %d", &record.dateEmp.day, &record.dateEmp.month, &record.dateEmp.year);
			}
		} while (record.dateEmp.month < 1 || record.dateEmp.month>12 || record.dateEmp.day < 1 || record.dateEmp.day>31 || record.dateEmp.year < 0);


		printf("Enter the doorPlate of address : ");
		rewind(stdin);
		scanf("%d", &record.adress.doorPlate);
		printf("Enter the taman of address : ");
		rewind(stdin);
		scanf("%[^\n]", record.adress.taman);
		printf("Enter the country of address : ");
		rewind(stdin);
		scanf("%[^\n]", record.adress.country);
		printf("Enter the contact number : ");
		rewind(stdin);
		scanf("%d %d", &record.contactNo1, &record.contactNo2);
		printf("Enter the qualitification: ");
		rewind(stdin);
		scanf("%[^\n]", record.qualitification);
		printf("Enter the university of qualitification: ");
		rewind(stdin);
		scanf("%s", record.qualitificationUni);

		printf("\n==============================The added staff information=================================\n");
		printf("%-5s%-12s%-12s%-8s%-12s%-12s%-19s%-39s%-17s%s\n", "ID", "NAME", "DESIGNATION", "GENDER", "GROUPBLOOD", "NATIONALITY", "DATEEMPLOYED", "HOME ADDRESS", "CONTACT-NO", "QUALITIFICATION");
		printf("========================================================================================================================================================\n");
		fprintf(staff, "%s|%s|%s|%c|%s|%s|%2d/%2d/%4d|%10d,%s,%s|%3d-%d|\t%s(%s)|\n", record.id, record.name, record.designation, record.gender, record.groupBlood, record.nationality, record.dateEmp.day, record.dateEmp.month, record.dateEmp.year, record.adress.doorPlate, record.adress.taman, record.adress.country, record.contactNo1, record.contactNo2, record.qualitification, record.qualitificationUni);
		printf("%-5s%-12s%-12s%-8c%-12s%-12s%02d/%02d/%04d %10d,%-15s,%-20s%03d-%d\t%s(%s)\n", record.id, record.name, record.designation, record.gender, record.groupBlood, record.nationality, record.dateEmp.day, record.dateEmp.month, record.dateEmp.year, record.adress.doorPlate, record.adress.taman, record.adress.country, record.contactNo1, record.contactNo2, record.qualitification, record.qualitificationUni);

		rewind(stdin);
		printf("Do you want to continue : ");
		scanf("%c", &answer);
	} while (answer == 'Y' || answer == 'y');
	fclose(staff);
	return 'n';
}
void staffIdValidate(char staffId[]) {
	int strlength;
	strlength = strlen(staffId);
	while (staffId[0] != 'D' && staffId[0] != 'N' && staffId[0] != 'C' && staffId[0] != 'P' || strlength > 3 || strlength < 3 || !(isdigit(staffId[1]) && isdigit(staffId[2]))) {
		if (staffId[0] != 'D' && staffId[0] != 'N' && staffId[0] != 'C' && staffId[0] != 'P')
			printf("\nFirst character of staff ID must be 'D','N','C' or 'P'");
		if (!(strlength == 3)) {
			printf("\nStaff ID must have 3 character only");
		}
		if (!(isdigit(staffId[1]) && isdigit(staffId[2]))) {
			printf("\nLast two number must be number");
		}
		printf("\nPlease enter again.\n");
		printf("\nEnter the id : ");
		rewind(stdin);
		scanf("%s", staffId);
		strlength = strlen(staffId);
	}
}
char modifyRecord()
{
	int i = 0, sizeOfFile;
	char staffId[5], answer, newName[20], newNationality[20], newTaman[20], newCountry[20];
	int choice, newDoorPlate, newContactNo1, newContactNo2;
	sizeOfFile = readFile();

	do {
		printf("Enter the ID of staff :");
		scanf("%s", staffId);
		for (i = 0; i < sizeOfFile; i++) {
			if (strcmp(staffId, record[i].id) == 0) {

				printf("=====The menu of choice==========\n");
				printf("1. name\n");
				printf("2. nationality\n");
				printf("3. Home Address\n");
				printf("4. contact-no\n");

				printf("Enter the information that you want to edit : ");
				rewind(stdin);
				scanf("%d", &choice);
				switch (choice)
				{
				case 1:
					printf("Enter the new name : ");
					rewind(stdin);
					scanf("%[^\n]", newName);
					strcpy(record[i].name, newName);
					break;
				case 2:
					printf("Enter the new nationality : ");
					rewind(stdin);
					scanf("%s", newNationality);
					strcpy(record[i].nationality, newNationality);
					break;
				case 3:
					printf("Enter the new Door plate of staff : ");
					rewind(stdin);
					scanf("%d", &newDoorPlate);
					record[i].adress.doorPlate = newDoorPlate;
					printf("Enter the new taman of address:");
					rewind(stdin);
					scanf("%[^\n]", newTaman);
					strcpy(record[i].adress.taman, newTaman);
					printf("Enter the new country of address:");
					rewind(stdin);
					scanf("%[^\n]", newCountry);
					strcpy(record[i].adress.country, newCountry);
					break;

				case 4:
					printf("Enter the new contactNo1 : ");
					rewind(stdin);
					scanf("%d", &newContactNo1);
					record[i].contactNo1 = newContactNo1;
					printf("Enter the new contactNo2:");
					rewind(stdin);
					scanf("%d", &newContactNo2);
					record[i].contactNo2 = newContactNo2;
					break;
				default:
					printf("Did not have this choice.\n");
				}
			}

		}

		rewind(stdin);
		printf("\nDo you want to continue edit???");
		scanf("%c", &answer);

	} while (answer == 'Y' || answer == 'y');
	FILE*staff;
	staff = fopen("staff.txt", "w");
	for (i = 0; i < sizeOfFile; i++) {
		fprintf(staff, "%s|%s|%s|%c|%s|%s|%02d/%02d/%04d|%d,%s,%s|%03d-%d|%s(%s)|\n", record[i].id, record[i].name, record[i].designation, record[i].gender, record[i].groupBlood, record[i].nationality, record[i].dateEmp.day, record[i].dateEmp.month, record[i].dateEmp.year, record[i].adress.doorPlate, record[i].adress.taman, record[i].adress.country, record[i].contactNo1, record[i].contactNo2, record[i].qualitification, record[i].qualitificationUni);
	}
	fclose(staff);
	return 'n';
}
char deleteEmployee()
{
	int i = 0, j, sizeOfFile;
	sizeOfFile = readFile();
	char answer, staffId[5], deleteR;

	do
	{
		printf("Enter the ID of staff that you want to delete : ");
		rewind(stdin);
		scanf("%[^\n]", staffId);


		for (i = 0; i < sizeOfFile; i++) {
			if (strcmp(staffId, record[i].id) == 0) {
				printf("\n%-5s%-12s%-12s%-8s%-12s%-12s%-19s%-39s%-17s%s\n", "ID", "NAME", "DESIGNATION", "GENDER", "GROUPBLOOD", "NATIONALITY", "DATEEMPLOYED", "HOME ADDRESS", "CONTACT-NO", "QUALITIFICATION");
				printf("========================================================================================================================================================\n");
				printf("%-5s%-12s%-12s%-8c%-12s%-12s%02d/%02d/%04d %10d,%-15s,%-20s%03d-%d\t%s(%s)\n", record[i].id, record[i].name, record[i].designation, record[i].gender, record[i].groupBlood, record[i].nationality, record[i].dateEmp.day, record[i].dateEmp.month, record[i].dateEmp.year, record[i].adress.doorPlate, record[i].adress.taman, record[i].adress.country, record[i].contactNo1, record[i].contactNo2, record[i].qualitification, record[i].qualitificationUni);
				printf("Did you want to delete this record ???");
				rewind(stdin);
				scanf("%c", &deleteR);
				if (toupper(deleteR) == 'Y') {
					for (i = 0; i < sizeOfFile; i++)
					{
						if (strcmp(staffId, record[i].id) == 0) {

							for (j = i; j < sizeOfFile; j++)
							{

								record[j] = record[j + 1];

							}
							j--;
							sizeOfFile--;

						}
					}
					FILE*staff;
					staff = fopen("staff.txt", "w");
					while (staff == NULL)
					{
						printf("Unable to open staff.txt file!\n");
						system("pause");
						exit(-1);
					}
					for (i = 0; i < sizeOfFile; i++) {
						fprintf(staff, "%s|%s|%s|%c|%s|%s|%02d/%02d/%04d|%d,%s,%s|%03d-%d|%s(%s)|\n", record[i].id, record[i].name, record[i].designation, record[i].gender, record[i].groupBlood, record[i].nationality, record[i].dateEmp.day, record[i].dateEmp.month, record[i].dateEmp.year, record[i].adress.doorPlate, record[i].adress.taman, record[i].adress.country, record[i].contactNo1, record[i].contactNo2, record[i].qualitification, record[i].qualitificationUni);
					}
					fclose(staff);
				}
				else
				{
					return 'n';
				}
			}
		}
		rewind(stdin);
		printf("\nDo you want to continue delete???");
		scanf("%c", &answer);
	} while (answer == 'Y' || answer == 'y');
	return 'n';
}







