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
		float quizze1;
		float quizze2;
		float midScore;
		float assigmentScore;
		float averageScore;
		char finalGrade;
	};

int displayMenu(void);
void addRec(struct record *studRec_t, int *itemCount);
int searchEntry(struct record *studRec_t, char *id, int *itemCount);
void delRec(struct record *studRec_t, int *itemCount);
void cleanRec(struct record *studRec_t, int *itemCount);
void updateRec(struct record *studRec_t, int *itemCount);
void viewAll(struct record *studRec_t, int *itemCount);
void avrScore(struct record *studRec_t, int *itemCount);
void showMax(struct record *studRec_t, int *itemCount);
void showMin(struct record *studRec_t, int *itemCount);
void findRec(struct record *studRec_t, int *itemCount);
void bubbleSort(struct record *studRec_t, int *itemCount);
//----------------------------------------------------
//----------------------------------------------------
int main(void)
{
	struct record empty = {"","","","","",-1,-1,-1,-1,-1,'\0'};
	struct record studList[MAXSTUD];
	int listLength = 0;


	int cnt = 0;

	for(cnt = 0 ; cnt < MAXSTUD ; cnt++)
	{
		studList[cnt] = empty;
	}

	do{
		switch(displayMenu()){
		case 1:{
			addRec(studList, &listLength);
			break;}
		case 2:{
			delRec(studList, &listLength);
			break;}
		case 3:{
			updateRec(studList, &listLength);
			break;}
		case 4:{
			viewAll(studList, &listLength);
			break;}
		case 5:{
			avrScore(studList, &listLength);
			break;}
		case 6:{
			showMax(studList, &listLength);
			break;}
		case 7:{
			showMin(studList, &listLength);
			break;}
		case 8:{
			findRec(studList, &listLength);
			break;}
		case 9:{
			bubbleSort(studList, &listLength);
			break;}
		case 0:{
			puts("\nProgram has ended.");
			exit(0);
			break;}
		default:{
			puts("You entered a wrong Number!");
			break;}}
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
			"6 : Show student who gets the max average\n"
			"7 : Show student who gets the min average\n"
			"8 : Find student by ID\n"
			"9 : Sort records by average scores\n"
			"0 : Exit Program");
	puts("\nYour choice: ");
	fflush(stdout);
	scanf("%d", &choice);

	return choice;
}
//----------------------------------------------------

void addRec(struct record *studRec_t, int *itemCount)
{
	struct record tempStud = {"","","","","",-1,-1,-1,-1,-1,'\0'};
	struct record *listPos;
	listPos = studRec_t;
	int tmp = 0;
	int cnt = 0;

	do
	{
		printf("\nEnter ID-Number (Max length %d): ", IDSIZE);
		fflush(stdout);
		scanf("%s", tempStud.id);
		for(tmp = 0, cnt = 0, listPos = studRec_t ; cnt < *itemCount ; listPos++, cnt++)
		{
			if(!strcmp(tempStud.id, listPos->id))
			{
				puts("The entered ID already exists.");
				tmp = 1;
			}
		}
	} while(tmp == 1);
	printf("\nEnter sex (Max length %d): ", SEXSIZE);
	fflush(stdout);
	scanf("%s", tempStud.sex);
	printf("\nEnter first Name (Max length %d): ", FNSIZE);
	fflush(stdout);
	scanf("%s", tempStud.fName);
	printf("\nEnter last Name (Max length %d): ", LNSIZE);
	fflush(stdout);
	scanf("%s", tempStud.lName);
	printf("\nEnter E-Mail (Max length %d): ", EMSIZE);
	fflush(stdout);
	scanf("%s", tempStud.eMail);

	studRec_t[*itemCount] = tempStud;
	*itemCount += 1;

	return;
}

//----------------------------------------------------
int searchEntry(struct record *studRec_t, char *id, int *itemCount)
{
	int cnt = 0;
	struct record *listPos;
	listPos = studRec_t;

	for(cnt = 0, listPos = studRec_t ; cnt < *itemCount ; cnt++, listPos++)
	{
		if(!strcmp(id, listPos->id))
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
	char id[IDSIZE];
	int pos = 0;

	do
	{
		puts("Enter ID from Student you want to delete:");
		fflush(stdout);
		scanf("%s", id);
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

	printf("ID %s deleted!\n", id);
	*itemCount -= 1;
	return;
}
//----------------------------------------------------
void cleanRec(struct record *studRec_t, int *itemCount)
{
	struct record empty = {"","","","","",-1,-1,-1,-1,-1,'\0'};
	studRec_t[*itemCount - 1] = empty;
	return;
}
//----------------------------------------------------
void updateRec(struct record *studRec_t, int *itemCount)
{
	char id[IDSIZE];
	int pos = 0;
	int choice = 0;
	struct record tempStud;

	do
	{
		puts("Enter ID from Student you want to update:");
		fflush(stdout);
		scanf("%s", id);
		pos = searchEntry(studRec_t, id, itemCount);
	} while(pos == -1);

	do
	{
	puts("What would you like to update?\n"
			"1 : Sex\n"
			"2 : First Name\n"
			"3 : Last Name\n"
			"4 : E-Mail\n"
			"5 : Quizze 1\n"
			"6 : Quizze 2\n"
			"7 : MidScore\n"
			"8 : AssigmentScore\n"
			"0 : Done");
	fflush(stdout);
	scanf("%d", &choice);

		switch(choice){
		case 1:{
			printf("\nEnter sex (Max length %d): ", SEXSIZE);
			fflush(stdout);
			scanf("%s", tempStud.sex);
			strcpy(studRec_t[pos].sex, tempStud.sex);
			break;}
		case 2:{
			printf("\nEnter first Name (Max length %d): ", FNSIZE);
			fflush(stdout);
			scanf("%s", tempStud.fName);
			strcpy(studRec_t[pos].fName, tempStud.fName);
			break;}
		case 3:{
			printf("\nEnter last Name (Max length %d): ", LNSIZE);
			fflush(stdout);
			scanf("%s", tempStud.lName);
			strcpy(studRec_t[pos].lName, tempStud.lName);
			break;}
		case 4:{
			printf("\nEnter E-Mail (Max length %d): ", EMSIZE);
			fflush(stdout);
			scanf("%s", tempStud.eMail);
			strcpy(studRec_t[pos].eMail, tempStud.eMail);
			break;}
		case 5:{
			printf("\nEnter Quizze 1 Score: ");
			fflush(stdout);
			scanf("%f", &tempStud.quizze1);
			studRec_t[pos].quizze1 = tempStud.quizze1;
			break;}
		case 6:{
			printf("\nEnter Quizze 2 Score: ");
			fflush(stdout);
			scanf("%f", &tempStud.quizze2);
			studRec_t[pos].quizze2 = tempStud.quizze2;
			break;}
		case 7:{
			printf("\nEnter MidScore Score: ");
			fflush(stdout);
			scanf("%f", &tempStud.midScore);
			studRec_t[pos].midScore = tempStud.midScore;
			break;}
		case 8:{
			printf("\nEnter Assigment Score: ");
			fflush(stdout);
			scanf("%f", &tempStud.assigmentScore);
			studRec_t[pos].assigmentScore = tempStud.assigmentScore;
			break;}
		case 0:{
			printf("ID %s updated!\n", id);
			return;}
		default:{
			puts("You have entered a wrong Number!\n");
			break;}
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
			"| Index | ID                             | Quizze 1   | Quizze 2    | MidScore   | Assigm.Score   | Aver.Score   | FinalGrade  |\n"
			"|       | Sex                            |            |             |            |                |              |             |\n"
			"|       | First Name                     |            |             |            |                |              |             |\n"
			"|       | Last Name                      |            |             |            |                |              |             |\n"
			"|       | E-Mail                         |            |             |            |                |              |             |\n"
			"--------------------------------------------------------------------------------------------------------------------------------\n"
			"--------------------------------------------------------------------------------------------------------------------------------");
	for(cnt = 0 ; cnt < *itemCount ; cnt++)
	{
		printf(""
				"| %-5d | %-30s | %-10f | %-10f  | %-10f | %-14f | %-12f | %-11c |\n"
				"|       | %-30s |            |             |            |                |              |             |\n"
				"|       | %-30s |            |             |            |                |              |             |\n"
				"|       | %-30s |            |             |            |                |              |             |\n"
				"|       | %-30s |            |             |            |                |              |             |\n"
				,cnt, studRec_t[cnt].id, studRec_t[cnt].quizze1, studRec_t[cnt].quizze2, studRec_t[cnt].midScore
				, studRec_t[cnt].assigmentScore , studRec_t[cnt].averageScore, studRec_t[cnt].finalGrade
				, studRec_t[cnt].sex, studRec_t[cnt].fName, studRec_t[cnt].lName, studRec_t[cnt].eMail);
		puts("--------------------------------------------------------------------------------------------------------------------------------");
	}

	return;
}
//----------------------------------------------------
void avrScore(struct record *studRec_t, int *itemCount)
{
	char id[IDSIZE];
	int pos = 0;
	int cnt = 0;
	float entry[4] = {-1,-1,-1,-1};
	float sum = 0;
	int div = 0;

	do
	{
		puts("Enter ID from Student you want to calculate the average:");
		fflush(stdout);
		scanf("%s", id);
		pos = searchEntry(studRec_t, id, itemCount);
	} while(pos == -1);

	if(studRec_t[pos].quizze1 >= 0)
	{
		entry[cnt] = studRec_t[pos].quizze1;
		cnt += 1;
		div += 1;
	}
	if(studRec_t[pos].quizze2 >= 0)
	{
		entry[cnt] = studRec_t[pos].quizze2;
		cnt += 1;
		div += 1;
	}
	if(studRec_t[pos].midScore >= 0)
	{
		entry[cnt] = studRec_t[pos].midScore;
		cnt += 1;
		div += 1;
	}
	if(studRec_t[pos].assigmentScore >= 0)
	{
		entry[cnt] = studRec_t[pos].assigmentScore;
		cnt += 1;
		div += 1;
	}

	for(cnt = 0 ; cnt < div ; cnt++)
	{
		sum += entry[cnt];
	}
	studRec_t[pos].averageScore = sum / div;

	return;
}
//----------------------------------------------------
void showMax(struct record *studRec_t, int *itemCount)
{
	int pos = 0;
	int cnt = 0;

	for(cnt = 0 ; cnt < *itemCount ; cnt++)
	{
		if(studRec_t[cnt].averageScore > studRec_t[pos].averageScore)
		{
			pos = cnt;
		}
	}

	puts("Student with max average score:\n"
				"--------------------------------------------------------------------------------------------------------------------------------");
		puts(""
				"--------------------------------------------------------------------------------------------------------------------------------\n"
				"| Index | ID                             | Quizze 1   | Quizze 2    | MidScore   | Assigm.Score   | Aver.Score   | FinalGrade  |\n"
				"|       | Sex                            |            |             |            |                |              |             |\n"
				"|       | First Name                     |            |             |            |                |              |             |\n"
				"|       | Last Name                      |            |             |            |                |              |             |\n"
				"|       | E-Mail                         |            |             |            |                |              |             |\n"
				"--------------------------------------------------------------------------------------------------------------------------------\n"
				"--------------------------------------------------------------------------------------------------------------------------------");
			printf(""
					"| %-5d | %-30s | %-10f | %-10f  | %-10f | %-14f | %-12f | %-11c |\n"
					"|       | %-30s |            |             |            |                |              |             |\n"
					"|       | %-30s |            |             |            |                |              |             |\n"
					"|       | %-30s |            |             |            |                |              |             |\n"
					"|       | %-30s |            |             |            |                |              |             |\n"
					,pos, studRec_t[pos].id, studRec_t[pos].quizze1, studRec_t[pos].quizze2, studRec_t[pos].midScore
					, studRec_t[pos].assigmentScore , studRec_t[pos].averageScore, studRec_t[pos].finalGrade
					, studRec_t[pos].sex, studRec_t[pos].fName, studRec_t[pos].lName, studRec_t[pos].eMail);
			puts("--------------------------------------------------------------------------------------------------------------------------------");

	return;
}
//----------------------------------------------------
void showMin(struct record *studRec_t, int *itemCount)
{
	int pos = 0;
	int cnt = 0;

	for(cnt = 0 ; cnt < *itemCount ; cnt++)
	{
		if(studRec_t[cnt].averageScore < studRec_t[pos].averageScore)
		{
			pos = cnt;
		}
	}

	puts("Student with min average score:\n"
				"--------------------------------------------------------------------------------------------------------------------------------");
		puts(""
				"--------------------------------------------------------------------------------------------------------------------------------\n"
				"| Index | ID                             | Quizze 1   | Quizze 2    | MidScore   | Assigm.Score   | Aver.Score   | FinalGrade  |\n"
				"|       | Sex                            |            |             |            |                |              |             |\n"
				"|       | First Name                     |            |             |            |                |              |             |\n"
				"|       | Last Name                      |            |             |            |                |              |             |\n"
				"|       | E-Mail                         |            |             |            |                |              |             |\n"
				"--------------------------------------------------------------------------------------------------------------------------------\n"
				"--------------------------------------------------------------------------------------------------------------------------------");
			printf(""
					"| %-5d | %-30s | %-10f | %-10f  | %-10f | %-14f | %-12f | %-11c |\n"
					"|       | %-30s |            |             |            |                |              |             |\n"
					"|       | %-30s |            |             |            |                |              |             |\n"
					"|       | %-30s |            |             |            |                |              |             |\n"
					"|       | %-30s |            |             |            |                |              |             |\n"
					,pos, studRec_t[pos].id, studRec_t[pos].quizze1, studRec_t[pos].quizze2, studRec_t[pos].midScore
					, studRec_t[pos].assigmentScore , studRec_t[pos].averageScore, studRec_t[pos].finalGrade
					, studRec_t[pos].sex, studRec_t[pos].fName, studRec_t[pos].lName, studRec_t[pos].eMail);
			puts("--------------------------------------------------------------------------------------------------------------------------------");

	return;
}
//----------------------------------------------------
void findRec(struct record *studRec_t, int *itemCount)
{
	struct record tempStud;
	char id[IDSIZE];
	int pos = 0;

	do
	{
		puts("Enter ID from Student you want to display:");
		fflush(stdout);
		scanf("%s", id);
		pos = searchEntry(studRec_t, id, itemCount);
	} while(pos == -1);


	puts("Student you are looking for:\n"
		"--------------------------------------------------------------------------------------------------------------------------------");
	puts(""
		"--------------------------------------------------------------------------------------------------------------------------------\n"
		"| Index | ID                             | Quizze 1   | Quizze 2    | MidScore   | Assigm.Score   | Aver.Score   | FinalGrade  |\n"
		"|       | Sex                            |            |             |            |                |              |             |\n"
		"|       | First Name                     |            |             |            |                |              |             |\n"
		"|       | Last Name                      |            |             |            |                |              |             |\n"
		"|       | E-Mail                         |            |             |            |                |              |             |\n"
		"--------------------------------------------------------------------------------------------------------------------------------\n"
		"--------------------------------------------------------------------------------------------------------------------------------");
	printf(""
		"| %-5d | %-30s | %-10f | %-10f  | %-10f | %-14f | %-12f | %-11c |\n"
		"|       | %-30s |            |             |            |                |              |             |\n"
		"|       | %-30s |            |             |            |                |              |             |\n"
		"|       | %-30s |            |             |            |                |              |             |\n"
		"|       | %-30s |            |             |            |                |              |             |\n"
		,pos, studRec_t[pos].id, studRec_t[pos].quizze1, studRec_t[pos].quizze2, studRec_t[pos].midScore
		, studRec_t[pos].assigmentScore , studRec_t[pos].averageScore, studRec_t[pos].finalGrade
		, studRec_t[pos].sex, studRec_t[pos].fName, studRec_t[pos].lName, studRec_t[pos].eMail);
	puts("--------------------------------------------------------------------------------------------------------------------------------");
	return;
}
//----------------------------------------------------
void bubbleSort(struct record *studRec_t, int *itemCount)
{
	struct record temp;
	temp = *studRec_t;
	int cnt;
	int swap = 1;

	while(swap)
	{
		for(cnt = 1, swap = 0 ; cnt < *itemCount ; cnt++)
		{
			if(studRec_t[cnt].averageScore > studRec_t[cnt-1].averageScore)
			{
				temp = studRec_t[cnt-1];
				studRec_t[cnt-1] = studRec_t[cnt];
				studRec_t[cnt] = temp;
				swap = 1;
			}
		}
	}
	return;
}
