//#include<stdio.h>
//#include<stdlib.h>
//#include<ctype.h>
//#include<Windows.h>
//#pragma warning(disable:4996)
//
//typedef struct {
//	int hrs, min;
//}Time;
//
//typedef struct {
//	int day, month, year;
//}Date;
//
//typedef struct {
//	char ptID[6], ptName[40], gender;
//	char nrsName[40], drName[40];
//	Time fromTime, toTime;
//	char week[10];
//	Date date;
//}Appointment;
//
//Date date;
//Time fromTime, toTime;
//Appointment appointment, modTrack[20], delTrack[20], addTrack[20], appmt[20] = { { "P0001","Amy",'F',"Lisa","Isabell",14,00,16,00,"Sunday",30,12,2018 }
//,{ "P0004","Dan",'M',"Ken","Nike",10,30,12,30,"Friday",21,12,2018 },{ "P0006","Fred",'M',"Mike","Jack",13,00,15,00,"Saturday",22,12,2018 } };
//
//
//void main()
//{
//	FILE *DisplayBin;
//	DisplayBin = fopen("appointmentRecord.bin", "rb");
//
//	int appmtRecord = 0, i = 0, j = 0, count = 0;
//
//	SYSTEMTIME t;
//	GetLocalTime(&t);
//	printf(" Appointment Schedule - as at %d-%d-%d %d:%d\n\n", t.wDay, t.wMonth, t.wYear, t.wHour, t.wMinute);
//
//	printf(" Patient Detail                 Nurse On Duty   Doctor Preferred   Time                                     \n");
//	printf(" ID       Name         Gender   Name            Name               From     To       Week         Date      \n");
//	printf(" ======   ==========   ======   =============   ================   ======   ======   ==========   ==========\n");
//
//	while (fread(&appointment, sizeof(appointment), 1, DisplayBin) != 0)
//	{
//		if (appointment.gender != '\0')
//		{
//			appmt[i] = appointment;
//			appmtRecord++;
//			i++;
//		}
//	}
//	
//	for (i = 0; i < appmtRecord; i++)
//	{
//		for (j = 0; j < appmtRecord; j++)
//		{
//			if (appmt[i].date.year == appmt[j].date.year)
//			{
//				if (appmt[i].date.month == appmt[j].date.month)
//				{
//					if (appmt[i].date.day == appmt[j].date.day)
//					{
//						if (appmt[i].fromTime.hrs == appmt[j].fromTime.hrs)
//						{
//							if (appmt[i].fromTime.min < appmt[j].fromTime.min)
//							{
//								appointment = appmt[j];
//								appmt[j] = appmt[i];
//								appmt[i] = appointment;
//							}
//						}
//						else if (appmt[i].fromTime.hrs < appmt[j].fromTime.hrs)
//						{
//							appointment = appmt[j];
//							appmt[j] = appmt[i];
//							appmt[i] = appointment;
//						}
//					}
//					else if (appmt[i].date.day < appmt[j].date.day)
//					{
//						appointment = appmt[j];
//						appmt[j] = appmt[i];
//						appmt[i] = appointment;
//					}
//				}
//				else if (appmt[i].date.month < appmt[j].date.month)
//				{
//					appointment = appmt[j];
//					appmt[j] = appmt[i];
//					appmt[i] = appointment;
//				}
//			}
//			else if (appmt[i].date.year < appmt[j].date.year)
//			{
//				appointment = appmt[j];
//				appmt[j] = appmt[i];
//				appmt[i] = appointment;
//			}
//		}
//	}
//
//	for (i = 0; i < appmtRecord; i++)
//	{
//		printf(" %-6s   %-10s   %-6c   %-13s   %-16s  %3d:%02d   %3d:%02d    %-10s   %d-%d-%d\n", appmt[i].ptID, appmt[i].ptName,
//			appmt[i].gender, appmt[i].nrsName, appmt[i].drName, appmt[i].fromTime, appmt[i].toTime, appmt[i].week, appmt[i].date);
//	}
//
//	printf(" < %d Schedule Listed >\n", appmtRecord);
//	fclose(DisplayBin);
//
//	system("pause");
//}