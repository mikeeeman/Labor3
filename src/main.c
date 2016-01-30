/*
 * lab_Struct.c
 *
 *  Created on: 28.01.2016
 *      Author: Michael Meyer
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define IDSIZE 10
#define FNSIZE 30
#define LNSIZE 30
#define EMSIZE 50
#define SEXSIZE 10
#define MAXSTUD 20

struct record
	{
		char id[IDSIZE];
		char sex[SEXSIZE];
		char fName[FNSIZE];
		char lName[LNSIZE];
		char eMail[EMSIZE];
		int quizze1;
		int	quizze2;
		float midScore;
		float averageScore;
		float totalScore;
		char finalGrade;
	} studList[MAXSTUD];

int displayMenu(void);
void addRec(struct record *studRec_t, int *itemCount);
int searchEntry(struct record *studRec_t, int id, int *itemCount);
void delRec(struct record *studRec_t, int *itemCount);
void cleanRec(struct record *studRec_t, int *itemCount);
void updateRec(struct record *studRec_t, int *itemCount);
void viewAll(struct record *studRec_t, int *itemCount);
//----------------------------------------------------
//----------------------------------------------------
int main(void)
{
	int listLength = 0;

	do{
		switch(displayMenu())
		{
		case 1:
		{
			addRec(studList, &listLength);
			break;
		}
		case 2:
		{
			delRec(studList, &listLength);
			break;
		}
		case 3:
		{
			updateRec(studList, &listLength);
			break;
		}
		case 4:
		{
			viewAll(studList, &listLength);
			break;
		}
		case 5:
		{

			break;
		}
		case 6:
		{

			break;
		}
		case 7:
		{

			break;
		}
		case 8:
		{

			break;
		}
		case 9:
		{

			break;
		}
		case 0:
		{
			puts("\nProgram has ended.");
			exit(0);
			break;
		}
		default:
		{
			puts("You entered a wrong Number!");
			break;
		}
		}
	} while(1);

	return 0;
}
//----------------------------------------------------
//----------------------------------------------------
int displayMenu(void)
{
	int choice;
	puts(""
			"**********************************************************\n"
			"**\tControl Menu - Student Management System\t**\n"
			"**********************************************************\n");
	puts(""
			"1 : Add student records\n"
			"2 : Delete student records\n"
			"3 : Update student records\n"
			"4 : View all student records\n"
			"5 : Calculate an average of a selected student's score\n"
			"6 : Show student who gets the max total score\n"
			"7 : Show student who gets the min total score\n"
			"8 : Find student by ID\n"
			"9 : Sort records by total scores\n"
			"0 : Exit Program");
	puts("\nYour choice: ");
	fflush(stdout);
	scanf("%d", &choice);

	return choice;
}
//----------------------------------------------------

void addRec(struct record *studRec_t, int *itemCount)
{
	struct record tempStud;
	struct record *listPos;
	listPos = studRec_t;
	int tmp = 0;
	int cnt = 0;
	int cnt2 = 0;

	do
	{
		printf("\nEnter ID-Number (Max length %d): ", IDSIZE);
		fflush(stdout);
		fgets(tempStud.id, IDSIZE, stdin);
		for(tmp = 0, cnt = 0, listPos = studRec_t ; cnt < *itemCount ; listPos++, cnt++)
		{
			for(cnt2 = 0 ; cnt2 < IDSIZE ; cnt2++)
			{
				if(tempStud.id[cnt2] != listPos->id[cnt2])
				{
					tmp = 0;
					break;
				}
				else
				{
					tmp = 1;
				}
			}
			if(tmp == 1)
			{
				puts("The entered ID already exists.");
				break;
			}
		}
	} while(tmp == 1);
	printf("\nEnter sex (Max length %d): ", SEXSIZE);
	fflush(stdout);
	fgets(tempStud.sex, SEXSIZE, stdin);
	printf("\nEnter first Name (Max length %d): ", FNSIZE);
	fflush(stdout);
	fgets(tempStud.fName, FNSIZE, stdin);
	printf("\nEnter last Name (Max length %d): ", LNSIZE);
	fflush(stdout);
	fgets(tempStud.lName, LNSIZE, stdin);
	printf("\nEnter E-Mail (Max length %d): ", EMSIZE);
	fflush(stdout);
	fgets(tempStud.eMail, EMSIZE, stdin);

	studRec_t[*itemCount] = tempStud;
	*itemCount += 1;

	return;
}

//----------------------------------------------------
int searchEntry(struct record *studRec_t, int id, int *itemCount)
{
	int cnt = 0;
	struct record *listPos;
	listPos = studRec_t;

	for(cnt = 0, listPos = studRec_t ; cnt < *itemCount ; cnt++, listPos++)
	{
		if(id == listPos->id)
		{
			return cnt;
		}
	}
	puts("ID not found!");
	return -1;
}
//----------------------------------------------------

void delRec(struct record *studRec_t, int *itemCount)
{
	struct record tempStud;
	int id;
	int pos = 0;

	do
	{
		puts("Enter ID from Student you want to delete:");
		fflush(stdout);
		scanf("%d", &id);
		pos = searchEntry(studRec_t, id, itemCount);
	} while(pos == -1);


	if(pos == *itemCount - 1)
	{
		cleanRec(studRec_t, itemCount);
	}
	else
	{
		tempStud = studRec_t[*itemCount - 1];
		studRec_t[*itemCount - 1] = studRec_t[pos];
		studRec_t[pos] = tempStud;
		cleanRec(studRec_t, itemCount);
	}

	printf("ID %d deleted!", id);
	*itemCount -= 1;
	return;
}
//----------------------------------------------------
void cleanRec(struct record *studRec_t, int *itemCount)
{
	struct record empty = {0};
	studRec_t[*itemCount - 1] = empty;
	return;
}
//----------------------------------------------------
void updateRec(struct record *studRec_t, int *itemCount)
{
	int id;
	int pos = 0;
	int choice = 0;
	struct record tempStud;

	do
	{
		puts("Enter ID from Student you want to update:");
		fflush(stdout);
		scanf("%d", &id);
		pos = searchEntry(studRec_t, id, itemCount);
	} while(pos == -1);

	do
	{
	puts("What would you like to update?\n"
			"1 : Sex\n"
			"2 : First Name\n"
			"3 : Last Name\n"
			"4 : E-Mail\n"
			"0 : Done");
	fflush(stdout);
	scanf("%d", &choice);

		switch(choice)
		{
		case 1:
		{
			printf("\nEnter sex (Max length %d): ", SEXSIZE);
			fflush(stdout);
			scanf("%s", tempStud.sex);
			strcpy(studRec_t[pos].sex, tempStud.sex);
			break;
		}
		case 2:
		{
			printf("\nEnter first Name (Max length %d): ", FNSIZE);
			fflush(stdout);
			scanf("%s", tempStud.fName);
			strcpy(studRec_t[pos].fName, tempStud.fName);
			break;
		}
		case 3:
		{
			printf("\nEnter last Name (Max length %d): ", LNSIZE);
			fflush(stdout);
			scanf("%s", tempStud.lName);
			strcpy(studRec_t[pos].lName, tempStud.lName);
			break;
		}
		case 4:
		{
			printf("\nEnter E-Mail (Max length %d): ", EMSIZE);
			fflush(stdout);
			scanf("%s", tempStud.eMail);
			strcpy(studRec_t[pos].eMail, tempStud.eMail);
			break;
		}
		case 0:
		{
			printf("ID %d updated!", id);
			return;
		}
		default:
			puts("You entered a wrong Number!");
			break;
		}

	}while(1);

	return;
}
//----------------------------------------------------
void viewAll(struct record *studRec_t, int *itemCount)
{
	int cnt = 0;

	puts("List of all Students.\n"
			"--------------------------------------------------------------------------------------------------------------------------------");
	puts(""
			"--------------------------------------------------------------------------------------------------------------------------------\n"
			"| Index | ID                             | Quizze 1   | Quizze 2    | MidScore   | AverageScore   | TotalScore   | FinalGrade  |\n"
			"|       | Sex                            |            |             |            |                |              |             |\n"
			"|       | First Name                     |            |             |            |                |              |             |\n"
			"|       | Last Name                      |            |             |            |                |              |             |\n"
			"|       | E-Mail                         |            |             |            |                |              |             |\n"
			"--------------------------------------------------------------------------------------------------------------------------------\n"
			"--------------------------------------------------------------------------------------------------------------------------------");
	for(cnt = 0 ; cnt < *itemCount ; cnt++)
	{
		printf(""
				"| %-5d | %-30d | %-10d | %-10d | %-10f | %-14f | %-12f | %-11c |\n"
				"|       | %-30s |            |             |            |                |              |             |\n"
				"|       | %-30s |            |             |            |                |              |             |\n"
				"|       | %-30s |            |             |            |                |              |             |\n"
				"|       | %-30s |            |             |            |                |              |             |\n"
				,cnt, studRec_t[cnt].id, studRec_t[cnt].quizze1, studRec_t[cnt].quizze2, studRec_t[cnt].midScore
				, studRec_t[cnt].averageScore , studRec_t[cnt].totalScore, studRec_t[cnt].finalGrade
				, studRec_t[cnt].sex, studRec_t[cnt].fName, studRec_t[cnt].lName, studRec_t[cnt].eMail);
		puts("--------------------------------------------------------------------------------------------------------------------------------");
	}

	return;
}
//----------------------------------------------------



