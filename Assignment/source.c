#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#pragma warning (disable:4996)
#define A 4.00
#define A_MINUS 3.75 
#define B_PLUS 3.5 
#define B 3.0
#define B_MINUS 2.75 
#define C_PLUS 2.5
#define C 2.0 
#define F 0.0

int pass1,pass2,accID,attempt;
char PIN[8], studentDetails[][9][99] = {{"KPKL1234","idk","Y","Y","Y","Y","Y","Y"},{""}}/*ID, name,subject entry (3 semesters), session entry (3 semesters)*/, studSem1Sub[][11][99] = {{"AAA1003","AAA1014","AAA1013","AAA1024","AAA1024","AAA1052","July","2023","October","2023"}}, studSem2Sub[][11][99] = {{"AAA1103","AAA1114","AAA1113","","","","November","2023","January","2024"}}, studSem3Sub[][11][99] = {{"AAA1203","AAA1214","AAA1213","AAA1224","AAA1224","AAA1252","February","2024","June","2024"}};//course codes(0-5), sem start(6/7), sem end(8/9)
char* PINcheck[] = {"234567","123456","234565"};
float studSem1GPA[][16]={{4.0,4.0,4.0,4.0,4.0,4.0,3,4,3,4,4,2,20,4.0,6}}, studSem2GPA[][16] = { {4.0,4.0,4.0,0,0,0,3,4,3,0,0,0,10,4.0,3} }, studSem3GPA[][16] = { {4.0,4.0,4.0,4.0,4.0,4.0,3,4,3,4,4,2,20,4.0,6} }, loginSelect = 0, menuSelect = 0;//gpa for respective course(0-5),sem credit hours(6-11),total credit hours(12),cgpa(13),number of subjects(14)
void menu() {
	int i;//counter (applies for all instances of i and n)
	for (i = 1;i <= 148;i++) {
		putchar('*');
		if (i == 70 || i == 140)printf("\n");
	}//prints out 148 '*' with a newline at 70th and 148th *
	printf("Welcome to Kolej Pasar's Multipurpose CGPA Calculator!");
	for (i = 1;i <= 148;i++) {
		putchar('*');
		if (i==8||i == 78|| i == 148)printf("\n");
	}
	printf("\n\n");
	for (i = 0; i < 50; i++) putchar('=');//prints out 50 '='
	printf("\n%26s\n", "MENU");
	for (i = 0; i < 50; i++) putchar('=');
	printf("\n1.CGPA System\n2.CGPA Target Calculator\n0.Exit\n");
	//above prints out menu interface and options
	do { //do loop
		scanf("%f", &menuSelect);
		rewind(stdin);//while this is only required for [^\n] in theory, rewind is useful here if user inputs chars or strings
		if (menuSelect != 2 && menuSelect != 1 && menuSelect!=0)
			printf("Enter 0, 1 or 2 only!\n");//only displayed if user gives wrong input
	} while (menuSelect != 2 && menuSelect != 1&& menuSelect!=0);//if user does not input given options, they are asked to input again
}
void getAID() {
	char AID[11], IDcheck[10];//AID is input, IDcheck is temp value to check input
	if (attempt == 1) {//prints if first attempt
		printf("Enter login credentials\nAdmin ID:");
	}
	else { printf("Record not found!\nAdmin ID:"); }//prints on second attempt
	scanf("%10s", AID);
	rewind(stdin);//needed if input exceeds 10 characters, same applies to all rewinds after %ns after this occurence
	FILE* file1 = fopen("AID.txt", "r");//opens file
	rewind(file1);
	while (fgets(IDcheck, sizeof(IDcheck), file1)) {//reads file
		if (strcmp(AID, IDcheck) == 0) {//check if it is equal
			accID/=2;
			printf("Logged in successfully.\n");
			pass1 = 1;//is a global variable set to 0;allows the loop to exit
			fclose(file1);	//closes file when a match is found
		}
		else {accID++;}//change accID position
	}
	attempt++;
}
void login() {
	for (int i = 0; i < 50; i++) {
		putchar('=');
	}
	printf("\n%26s\n", "LOGIN");
	for (int i = 0; i < 50; i++) {
		putchar('=');
	}
	printf("\n1.Administrator Login\n2.Student Login\n");
	//above prints out menu interface and options
	scanf("%f", &loginSelect);
	while (loginSelect != 2 && loginSelect != 1) {//while loop
		rewind(stdin);//refer to menu()
		printf("Enter 1 or 2 only!\n");
		scanf("%f", &loginSelect);
	}
	rewind(stdin);
}
void getPW() {
	printf("Enter PIN:");
	scanf("%7s", PIN);
	rewind(stdin);
	if (strcmp(PIN,PINcheck[accID])==0) {//if PIN is a match
		pass2 = 1;
	}
	else {printf("Wrong password!\n");}
}
void studentMenu() {
	int ID, loop, i;//loop is loop for login function, ID is position of student in array(applies for all instances of ID)
	char IDcheck[10];
	float wcgpa = 0, totalcred = 0, totalcgpa = 0,loop2=1;//loop2 for loop of entire function
	while (loop2 == 1) {
		system("cls");
		loop = 1;
	while (loop == 1) {
		printf("Enter student ID:");//enter ID and check if id is available
		scanf("%9s", IDcheck);
		rewind(stdin);
		for (ID = 0; ID < sizeof(studentDetails) / sizeof(studentDetails[0]);ID++) {
			if (strcmp(studentDetails[ID][0], IDcheck) == 0) {
				loop = 0;
				break;
			}
		}//verify ID
		if (ID == sizeof(studentDetails) / sizeof(studentDetails[0])) printf("Record not found!\n");//runs if id is unavailable
	}
		system("cls");
		printf("Student ID:%s\nName:%s\n----------------------------------------------------------------------------------\n", studentDetails[ID][0], studentDetails[ID][1]);//prints name and ID
		if (strcmp(studentDetails[ID][5], "Y") == 0)//semester 1 session
			printf("Semester 1 start: %s %s\nSemester 1 end: %s %s\n-----------------------------------------\n", studSem1Sub[ID][6], studSem1Sub[ID][7], studSem1Sub[ID][8], studSem1Sub[ID][9]);
		else printf("Semester 1 start: No record found!\nSemester 1 end: No record found!\n-----------------------------------------\n");
		printf("Semester 1 subjects taken:");//semester 1 subjects
		if (strcmp(studentDetails[ID][2], "Y") == 0) {//checks whether semester 1 data is entered
			for (i = 0;i < studSem1GPA[ID][14];i++) printf("\n%s GPA:%.2f", studSem1Sub[ID][i], studSem1GPA[ID][i]);
			printf("\n-----------------------------------------\nNumber of subjects: %.0f\nTotal credit hours: %.0f\nCGPA: %.2f\n----------------------------------------------------------------------------------\n", studSem1GPA[ID][14], studSem1GPA[ID][12], studSem1GPA[ID][13]);
			wcgpa += studSem1GPA[ID][13] * studSem1GPA[ID][12];//adds to total weighted cgpa
			totalcred += studSem1GPA[ID][12];//find total credit hours
		}//prints if data found
		else printf("No record found!\n----------------------------------------------------------------------------------\n");//prints if no data; semester 2 and 3 share the same program structure
		if (strcmp(studentDetails[ID][6], "Y") == 0)//semester 2 session
			printf("Semester 2 start: %s %s\nSemester 2 end: %s %s\n-----------------------------------------\n", studSem2Sub[ID][6], studSem2Sub[ID][7], studSem2Sub[ID][8], studSem2Sub[ID][9]);
		else printf("Semester 2 start: No record found!\nSemester 2 end: No record found!\n-----------------------------------------\n");
		printf("Semester 2 subjects taken: ");
		if (strcmp(studentDetails[ID][3], "Y") == 0) {
			for (i = 0;i < studSem2GPA[ID][14];i++) printf("\n%s GPA:%.2f", studSem2Sub[ID][i], studSem2GPA[ID][i]);
			printf("\n-----------------------------------------\nNumber of subjects: %.0f\nTotal credit hours: %.0f\nCGPA: %.2f\n----------------------------------------------------------------------------------\n", studSem2GPA[ID][14], studSem2GPA[ID][12], studSem2GPA[ID][13]);
			wcgpa += studSem2GPA[ID][13] * studSem2GPA[ID][12];
			totalcred += studSem2GPA[ID][12];
		}
		else printf("No record found!\n----------------------------------------------------------------------------------\n");
		if (strcmp(studentDetails[ID][7], "Y") == 0)//semester 3
			printf("Semester 3 start: %s %s\nSemester 3 end: %s %s\n-----------------------------------------\n", studSem3Sub[ID][6], studSem3Sub[ID][7], studSem3Sub[ID][8], studSem3Sub[ID][9]);
		else printf("Semester 3 start: No record found!\nSemester 3 end: No record found!\n-----------------------------------------\n");
		printf("Semester 3 subjects taken: ");
		if (strcmp(studentDetails[ID][4], "Y") == 0) {
			for (i = 0;i < studSem3GPA[ID][14];i++) printf("\n%s GPA:%.2f", studSem3Sub[ID][i], studSem3GPA[ID][i]);
			printf("\n-----------------------------------------\nNumber of subjects: %.0f\nTotal credit hours: %.0f\nCGPA: %.2f\n----------------------------------------------------------------------------------\n", studSem3GPA[ID][14], studSem3GPA[ID][12], studSem3GPA[ID][13]);
			wcgpa += studSem3GPA[ID][13] * studSem3GPA[ID][12];
			totalcred += studSem3GPA[ID][12];
		}
		else printf("No record found!\n----------------------------------------------------------------------------------\n");
		if (totalcred != 0)totalcgpa = wcgpa / totalcred;//if total credit hours is NOT 0
		else totalcgpa = 0;//if total credit hours is 0, not possible if there is weighted cgpa, error in data, prevents division error
		if(strcmp(studentDetails[ID][2], "Y") != 0&&strcmp(studentDetails[ID][3], "Y") != 0&&strcmp(studentDetails[ID][4], "Y") != 0) printf("CGPA across 3 semesters: No record found!\n----------------------------------------------------------------------------------\n");//prints if no data is entered as total cannot hence be found
		else printf("CGPA across 3 semesters:%.2f\n----------------------------------------------------------------------------------\n",totalcgpa);//prints total cgpa between all semesters
		printf("\nDo you want to continue to view student details? Enter 1 to continue, any other value to exit.");
		if (scanf("%f", &loop2) == 0) loop2 = 0;//runs if user inputs non-number value, regards it as exit loop
		rewind(stdin);
	}
}
void adminMenu() {
	//above is to print admin menu, clears console
	int i,n, loop2 = 1, ID,check, gradeLoop = 1,pass1,pass2;//i is for menu counter, n is for function counter
	char IDcheck[10], grade[4],IDConfirm[10],nameConfirm[62];
	float totalcgpa=0,wcgpa=0,totalcred=0,select,menu2select=0,subjectLoop = 0, semSelect = 0,sessionSelect = 0, month = 0, year = 0,loop=1,loop3=1;
	while (loop == 1) {
		system("cls");
		for (i = 0; i < 50; i++) {
			putchar('=');
		}
		printf("\n%30s\n", "ADMIN MENU");
		for (i = 0; i < 50; i++) {
			putchar('=');
		}
		select = -1;
		printf("\n1.Add new student.\n2.Enter student course details.\n3.View students' CGPA and GPA score.\n0.Exit admin menu.\n");//prints menu
		scanf("%f", &select);
		while (select != 0 && select !=1&&select!=2&&select!=3) {
			rewind(stdin);
			printf("Enter a value between 0 to 3!");
			scanf("%f", &select);
		}//checks input
		switch ((int)select) {
		case 0:
			loop = 0;
			break;//exit
		case 1://add new student
			pass1 = 0,pass2 = 0;
			system("cls");
			for (ID = 0; ID < sizeof(studentDetails) / sizeof(studentDetails[0]);ID++) {
				if (strcmp(studentDetails[ID][0], "") == 0) break;//check id validity
			}
			printf("Enter new student ID:");
			scanf("%9s", studentDetails[ID][0]);
			rewind(stdin);
			printf("Confirm ID (ID cannot be changed!):");
			scanf("%9s", IDConfirm);
			rewind(stdin);
			while (pass1 == 0) {
				for (check = 0; check < (sizeof(studentDetails) / sizeof(studentDetails[0])) - 1;check++) {
					if (strcmp(studentDetails[ID][0], studentDetails[check][0]) == 0) {
						printf("ID is already used!\n");
						printf("Enter new student ID:");
						scanf("%9s", studentDetails[ID][0]);
						rewind(stdin);
						printf("Confirm ID (ID cannot be changed!):");
						scanf("%9s", IDConfirm);
						rewind(stdin);
					}
				}//check id duplicate
				while (strcmp(studentDetails[ID][0], IDConfirm) != 0 || strlen(studentDetails[ID][0]) != 8) {
					printf("ID does not match or is invalid!\n");
					printf("Enter new student ID:");
					scanf("%8s", studentDetails[ID][0]);
					rewind(stdin);
					printf("Confirm ID (ID cannot be changed!):");
					scanf("%9s", IDConfirm);
					rewind(stdin);
				}//check confirmation id match
				for (check = 0; check < (sizeof(studentDetails) / sizeof(studentDetails[0])) - 1;check++)
					if (strcmp(studentDetails[ID][0], studentDetails[check][0]) == 0)
						break;
				if (check == (sizeof(studentDetails) / sizeof(studentDetails[0])) - 1 && strcmp(studentDetails[ID][0], IDConfirm) == 0 && strlen(studentDetails[ID][0]) == 8)pass1 = 1;//if fulfill conditions, exit loop
			}
			strcpy(studentDetails[ID + 1][0], "");
			strcpy(studentDetails[ID][2],"N");
			strcpy(studentDetails[ID][3], "N");
			strcpy(studentDetails[ID][4], "N");
			strcpy(studentDetails[ID][5], "N");
			strcpy(studentDetails[ID][6], "N");
			strcpy(studentDetails[ID][7], "N");
			studSem1GPA[ID][13] =0;
			studSem2GPA[ID][13] = 0;
			studSem3GPA[ID][13] = 0;
			studSem1GPA[ID][12] = 0;
			studSem2GPA[ID][12] = 0;
			studSem3GPA[ID][12] = 0;//establish data
			printf("\nEnter new student name (max. 60 characters):");
			scanf("%60[^\n]", studentDetails[ID][1]);
			rewind(stdin);
			printf("Confirm name (name cannot be changed!):");
			scanf("%61[^\n]", nameConfirm);//higher characters read to prevent different length strings from passing checks
			rewind(stdin);
			while (pass2 == 0) {
				for (check = 0; check < (sizeof(studentDetails) / sizeof(studentDetails[0])) - 1;check++) {
					if (strcmp(studentDetails[ID][1], studentDetails[check][1]) == 0) {
						printf("Name is already used!\n");
						printf("Enter new student name (max. 60 characters):");
						scanf("%60[^\n]", studentDetails[ID][1]);
						rewind(stdin);
						printf("Confirm name (name cannot be changed!):");
						scanf("%61[^\n]", nameConfirm);
						rewind(stdin);
					}
				}//check duplicate name
				while (strcmp(studentDetails[ID][1], nameConfirm) != 0 || strlen(studentDetails[ID][1]) != strlen(nameConfirm)) {
					printf("Name does not match!\n");
					printf("Enter new student name:");
					scanf("%60[^\n]", studentDetails[ID][1]);
					rewind(stdin);
					printf("Confirm name (name cannot be changed!):");
					scanf("%61[^\n]", nameConfirm);
					rewind(stdin);
				}//check name confirmation if name does not match or length does not match (strlen is used here as user can input a name 60 characters in length then confirm it with an even longer string that has matching first 60 characters which would be unequal, this prevents that.
				for (check = 0; check < (sizeof(studentDetails) / sizeof(studentDetails[0])) - 1;check++)
					if (strcmp(studentDetails[ID][1], studentDetails[check][1]) == 0)
						break;
				if (check == (sizeof(studentDetails) / sizeof(studentDetails[0])) - 1 && strcmp(studentDetails[ID][1], nameConfirm) == 0 && strlen(studentDetails[ID][1]) == strlen(nameConfirm))pass2 = 1;
			}
			printf("\nNew student added sucessfully!\n\nWould you like to continue using the admin menu? Enter 1 to continue, any other value to stop and return to main menu.\n");
			if(scanf("%f", &loop)==0)loop=0;//if data entered is non-number, regards as exit loop
			rewind(stdin);
			break;
		case 2://enter course details
			loop2 = 1;
			while (loop2 == 1) {
				printf("Enter student ID:");
				scanf("%9s", IDcheck);
				rewind(stdin);
				for (ID = 0; ID < sizeof(studentDetails) / sizeof(studentDetails[0]);ID++) {
					if (strcmp(studentDetails[ID][0], IDcheck) == 0) {
						loop2 = 0;
						loop3 = 1;
						break;
					}
				}//verify ID
				if (ID == sizeof(studentDetails) / sizeof(studentDetails[0])) printf("Record not found!\n");//runs if id is unavailable
			}
				while (loop3 == 1) {//if id is found in system:
					system("cls");
					for (i = 0; i < 50; i++) {
						putchar('=');
					}
					printf("\n%33s\n", "DETAILS EDITOR");
					for (i = 0; i < 50; i++) {
						putchar('=');
					}//print menu
					menu2select = -1;//reset parameters
					printf("\nYou are now editing %s, %s's details\n1.Enter course code and grade obtained.\n2.Enter current semester session.\n0.Exit\n", studentDetails[ID][0], studentDetails[ID][1]);
					scanf("%f", &menu2select);
					while (menu2select != 1 && menu2select != 2 && menu2select!=0) {
						rewind(stdin);
						printf("Enter a value between 0 to 2!\n");
						scanf("%f", &menu2select);
					}//check user input validity
					switch ((int)menu2select) {
					case 0:
						loop3 = 0;
						break;
					case 1://input course code and grade
						semSelect = 0;
						printf("Enter edited semester (1,2 or 3):");
						scanf("%f", &semSelect);
						while (semSelect !=1 && semSelect!=2&&semSelect!=3) {
							rewind(stdin);
							printf("Enter 1,2 or 3 only!\n");
							scanf("%f", &semSelect);
						}//check user input validity
						subjectLoop = 0;
						system("cls");
						printf("List of grades and GPA >>>>>>\nA :4.00\nA-:3.75\nB+:3.50\nB :3.00\nB-:2.75\nC+:2.50\nC :2.00\nF :0.00\n-------------------------------------------\n");
						switch ((int)semSelect) {
						case 1:
							studSem1GPA[ID][12] = 0;//reset credit hours
							subjectLoop = 0;//reset parameters
							printf("You have selected Semester 1.\nEnter number of courses (max. 6 supported):");
							scanf("%f", &subjectLoop);//purpose of float scanf for values that are supposed to be integers are so that system will not accept floating-point inputs(system will convert into into int if scanf is %d)
							while (subjectLoop != 1&& subjectLoop != 2 && subjectLoop != 3 && subjectLoop != 4 && subjectLoop != 5 && subjectLoop != 6) {//if user did not input these accepted values
								rewind(stdin);
								printf("Enter a number between 1 to 6!");
								scanf("%f", &subjectLoop);
							}//check user input validity
							rewind(stdin);
							studSem1GPA[ID][14] = subjectLoop;
							for (n = 0;n < subjectLoop;n++) {
								printf("Enter course code for subject %d:", n + 1);
								scanf("%8s", studSem1Sub[ID][n]);//reads until 8 chars only
								rewind(stdin);
								while ((float)studSem1Sub[ID][n][6]-48<= 0 ||(float)studSem1Sub[ID][n][6]-48>9|| strlen(studSem1Sub[ID][n]) != 7) {//float is used here as the value to be stored is also float
									printf("Invalid course code!\nEnter course code for subject %d:",n+1);
									scanf("%8s", studSem1Sub[ID][n]);//reads until 8 chars only, length is checked to only pass if it is equal to 7
									rewind(stdin);
								}
								studSem1GPA[ID][n + 6] = (float)studSem1Sub[ID][n][6] - 48;//course weightage
								studSem1GPA[ID][12] += studSem1GPA[ID][n + 6];
								printf("Enter grade obtained:");
								scanf("%3s", grade);//reads 3 chars instead of 2 to prevent long strings that starts with a valid grade from passing checks, applies to all instances of this line with equal syntax 
								gradeLoop = 1;
								while (gradeLoop == 1) {//for all instances of this line, this is a while loop to convert grade to GPA
									if (strcmp(grade, "A") == 0) {
										studSem1GPA[ID][n] = A;
										gradeLoop = 0;
									}
									else if (strcmp(grade, "A-") == 0) {
										studSem1GPA[ID][n] = A_MINUS;
										gradeLoop = 0;
									}
									else if (strcmp(grade, "B+") == 0) {
										studSem1GPA[ID][n] = B_PLUS;
										gradeLoop = 0;
									}
									else if (strcmp(grade, "B") == 0) {
										studSem1GPA[ID][n] = B;
										gradeLoop = 0;
									}
									else if (strcmp(grade, "B-") == 0) {
										studSem1GPA[ID][n] = B_MINUS;
										gradeLoop = 0;
									}
									else if (strcmp(grade, "C+") == 0) {
										studSem1GPA[ID][n] = C_PLUS;
										gradeLoop = 0;
									}
									else if (strcmp(grade, "C") == 0) {
										studSem1GPA[ID][n] = C;
										gradeLoop = 0;
									}
									else if (strcmp(grade, "F") == 0) {
										studSem1GPA[ID][n] = F;
										gradeLoop = 0;
									}
									else {
										rewind(stdin);
										printf("Enter a valid grade!");//if input is invalid
										scanf("%3s", grade);
										rewind(stdin);
									}
								}
								printf("-------------------------------------------\n");
							}
							strcpy(studentDetails[ID][2], "Y");
							calcCGPA(1,(int)subjectLoop,ID);//calculate CGPA
							break;
						case 2://2nd semester, structure same as 1st sem
							studSem2GPA[ID][12] = 0;//reset credit hours
							subjectLoop = 0;//reset parameters
							printf("You have selected Semester 2.\nEnter number of courses:");
							scanf("%f", &subjectLoop);
							while (subjectLoop != 1 && subjectLoop != 2 && subjectLoop != 3 && subjectLoop != 4 && subjectLoop != 5 && subjectLoop != 6) {
								rewind(stdin);
								printf("Enter a number between 1 to 6!");
								scanf("%f", &subjectLoop);
							}
							rewind(stdin);
							studSem2GPA[ID][14] = subjectLoop;
							for (n = 0;n < subjectLoop;n++) {
								printf("Enter course code for subject %d: ", n + 1);
								scanf("%8s", studSem2Sub[ID][n]);//reads until 8 chars only
								rewind(stdin);
								while ((float)studSem2Sub[ID][n][6] - 48 < 0 || (float)studSem2Sub[ID][n][6] - 48 > 9||strlen(studSem2Sub[ID][n]) != 7) {//can only pass if ending with char 0~9 and 7 char in length
									printf("Invalid course code!\nEnter course code for subject %d:", n + 1);
									scanf("%8s", studSem2Sub[ID][n]);//reads until 8 chars only
									rewind(stdin);
								}
								studSem2GPA[ID][n + 6] = (float)studSem2Sub[ID][n][6] - 48;//course weightage
								studSem2GPA[ID][12] += studSem2GPA[ID][n + 6];//total credit hours
								printf("Enter grade obtained:");
								scanf("%3s", grade);
								gradeLoop = 1;
								while (gradeLoop == 1) {
									if (strcmp(grade, "A") == 0) {
										studSem2GPA[ID][n] = A;
										gradeLoop = 0;
									}
									else if (strcmp(grade, "A-") == 0) {
										studSem2GPA[ID][n] = A_MINUS;
										gradeLoop = 0;
									}
									else if (strcmp(grade, "B+") == 0) {
										studSem2GPA[ID][n] = B_PLUS;
										gradeLoop = 0;
									}
									else if (strcmp(grade, "B") == 0) {
										studSem2GPA[ID][n] = B;
										gradeLoop = 0;
									}
									else if (strcmp(grade, "B-") == 0) {
										studSem2GPA[ID][n] = B_MINUS;
										gradeLoop = 0;
									}
									else if (strcmp(grade, "C+") == 0) {
										studSem2GPA[ID][n] = C_PLUS;
										gradeLoop = 0;
									}
									else if (strcmp(grade, "C") == 0) {
										studSem2GPA[ID][n] = C;
										gradeLoop = 0;
									}
									else if (strcmp(grade, "F") == 0) {
										studSem2GPA[ID][n] = F;
										gradeLoop = 0;
									}
									else {
										rewind(stdin);
										printf("Enter a valid grade!");
										scanf("%3s", grade);
									}
								}
								printf("-------------------------------------------\n");
							}
							strcpy(studentDetails[ID][3], "Y");
							calcCGPA(2, (int)subjectLoop, ID);
							break;
						case 3://3rd semester, refer to 1st semester comments
							studSem3GPA[ID][12] = 0;//reset credit hours
							subjectLoop = 0;//reset parameters
							printf("You have selected Semester 3.\nEnter the number of courses:");
							scanf("%f", &subjectLoop);
							while (subjectLoop != 1 && subjectLoop != 2 && subjectLoop != 3 && subjectLoop != 4 && subjectLoop != 5 && subjectLoop != 6) {
								rewind(stdin);
								printf("Enter a number between 1 to 6!");
								scanf("%f", &subjectLoop);
							}
							rewind(stdin);
							studSem3GPA[ID][14] = subjectLoop;
							for (int n = 0;n < subjectLoop;n++) {
								printf("Enter course code for subject %d: ", n + 1);
								scanf("%8s", studSem3Sub[ID][n]);//reads until 8 chars only
								rewind(stdin);
								while ((float)studSem3Sub[ID][n][6] - 48 < 0 || (float)studSem3Sub[ID][n][6] - 48 > 9||strlen(studSem3Sub[ID][n])!=7) {//pass if 7th char is 0~9 and is 7 chars in length
									printf("Invalid course code!\nEnter course code for subject %d:", n + 1);
									scanf("%8s", studSem3Sub[ID][n]);//reads until 8 chars only
									rewind(stdin);
								}
								studSem3GPA[ID][n + 6] = (float)studSem3Sub[ID][n][6] - 48;//course weightage
								studSem3GPA[ID][12] += studSem3GPA[ID][n + 6];
								printf("Enter grade obtained:");
								scanf("%3s", grade);
								gradeLoop = 1;
								while (gradeLoop == 1) {
									if (strcmp(grade, "A") == 0) {
										studSem3GPA[ID][n] = A;
										gradeLoop = 0;
									}
									else if (strcmp(grade, "A-") == 0) {
										studSem3GPA[ID][n] = A_MINUS;
										gradeLoop = 0;
									}
									else if (strcmp(grade, "B+") == 0) {
										studSem3GPA[ID][n] = B_PLUS;
										gradeLoop = 0;
									}
									else if (strcmp(grade, "B") == 0) {
										studSem3GPA[ID][n] = B;
										gradeLoop = 0;
									}
									else if (strcmp(grade, "B-") == 0) {
										studSem3GPA[ID][n] = B_MINUS;
										gradeLoop = 0;
									}
									else if (strcmp(grade, "C+") == 0) {
										studSem3GPA[ID][n] = C_PLUS;
										gradeLoop = 0;
									}
									else if (strcmp(grade, "C") == 0) {
										studSem3GPA[ID][n] = C;
										gradeLoop = 0;
									}
									else if (strcmp(grade, "F") == 0) {
										studSem3GPA[ID][n] = F;
										gradeLoop = 0;
									}
									else {
										rewind(stdin);
										printf("Enter a valid grade!");
										scanf("%3s", grade);
									}
								}
								printf("-------------------------------------------\n");
							}
							printf("Course code and grade obtained entered successfully!\n\n");
							strcpy(studentDetails[ID][4], "Y");
							calcCGPA(3, (int)subjectLoop, ID);
						}
						break;
					case 2://enter student session
						month = 0, year = 0;//reset value
						sessionSelect = 0;
						printf("Enter edited semester (1,2 or 3):");
						scanf("%f", &sessionSelect);
						rewind(stdin);
						while (sessionSelect != 1 && sessionSelect!=2 && sessionSelect!=3) {//if it is not an accepted value
							rewind(stdin);
							printf("Enter 1,2 or 3 only!\n");
							scanf("%f", &sessionSelect);
						}//check user input validity
						system("cls");
						if (sessionSelect == 1) {
							printf("Enter starting month of semester:\n1.January\n2.February\n3.March\n4.April\n5.May\n6.June\n7.July\n8.August\n9.September\n10.October\n11.November\n12.December\n");
							scanf("%f",&month);//again, prevent floating point input being accepeted by compiler
							rewind(stdin);
							while (month < 1 || month>12 || ((int)month) - month != 0) {//third condition is if it is not an integer
								printf("Enter a valid month! Starting month:");
								scanf("%f", &month);
								rewind(stdin);
							}
							switch ((int)month) {//converts float to int for switch case
							case 1:
								strcpy(studSem1Sub[ID][6], "January");//copies January into studSem1Sub[ID][6]
								break;
							case 2:
								strcpy(studSem1Sub[ID][6], "February");
								break;
							case 3:
								strcpy(studSem1Sub[ID][6], "March");
								break;
							case 4:
								strcpy(studSem1Sub[ID][6], "April");
								break;
							case 5:
								strcpy(studSem1Sub[ID][6], "May");
								break;
							case 6:
								strcpy(studSem1Sub[ID][6], "June");
								break;
							case 7:
								strcpy(studSem1Sub[ID][6], "July");
								break;
							case 8:
								strcpy(studSem1Sub[ID][6], "August");
								break;
							case 9:
								strcpy(studSem1Sub[ID][6], "September");
								break;
							case 10:
								strcpy(studSem1Sub[ID][6], "October");
								break;
							case 11:
								strcpy(studSem1Sub[ID][6], "November");
								break;
							case 12:
								strcpy(studSem1Sub[ID][6], "December");
								break;
							}
							printf("Enter starting year (e.g 2023):");
							scanf("%f", &year);//used to prevent inputs such as 2022.5 from being accepted
							rewind(stdin);
							while (year < 2000 || year>2100||((int)year)-year!=0) {
								printf("Invalid year! Only integer values of 2000~2100 are supported!\nEnter starting year:");
								scanf("%f", &year);
								rewind(stdin);
							}
							itoa((int)year, studSem1Sub[ID][7],10);//converts integer (year) to a string to be stored in a string array (int) is used here as year is initially a float, itoa means integer to ASCII, 3rd parameter is number base
							month = 0, year = 0;//reset value
							printf("Enter ending month of semester:\n1.January\n2.February\n3.March\n4.April\n5.May\n6.June\n7.July\n8.August\n9.September\n10.October\n11.November\n12.December\n");//ending and starting month and year entry has same structure as starting
							scanf("%f", &month);
							rewind(stdin);
							while (month < 1 || month>12 || ((int)month) - month != 0) {
								printf("Enter a valid month! Ending month:");
								scanf("%f", &month);
								rewind(stdin);
							}
							switch ((int)month) {//converts to int for switch case
							case 1:
								strcpy(studSem1Sub[ID][8], "January");
								break;
							case 2:
								strcpy(studSem1Sub[ID][8], "February");
								break;
							case 3:
								strcpy(studSem1Sub[ID][8], "March");
								break;
							case 4:
								strcpy(studSem1Sub[ID][8], "April");
								break;
							case 5:
								strcpy(studSem1Sub[ID][8], "May");
								break;
							case 6:
								strcpy(studSem1Sub[ID][8], "June");
								break;
							case 7:
								strcpy(studSem1Sub[ID][8], "July");
								break;
							case 8:
								strcpy(studSem1Sub[ID][8], "August");
								break;
							case 9:
								strcpy(studSem1Sub[ID][8], "September");
								break;
							case 10:
								strcpy(studSem1Sub[ID][8], "October");
								break;
							case 11:
								strcpy(studSem1Sub[ID][8], "November");
								break;
							case 12:
								strcpy(studSem1Sub[ID][8], "December");
								break;
							}
							printf("Enter ending year (e.g 2023):");
							scanf("%f", &year);
							rewind(stdin);
							while (year < 2000 || year>2100 || ((int)year) - year != 0) {
								printf("Invalid year! Only values of 2000~2100 are supported!\nEnter ending year:");
								scanf("%f", &year);
								rewind(stdin);
							}
							itoa((int)year, studSem1Sub[ID][9], 10);
							month = 0, year = 0;//reset value
							printf("\n\nSemester 1 session date added successfully!\n\n");
							strcpy(studentDetails[ID][5], "Y");
						}
						else if (sessionSelect == 2) {//2nd semester, same structure as 1st
							printf("Enter starting month of semester:\n1.January\n2.February\n3.March\n4.April\n5.May\n6.June\n7.July\n8.August\n9.September\n10.October\n11.November\n12.December\n");
							scanf("%f", &month);
							rewind(stdin);
							while (month < 1 || month>12 || ((int)month) - month != 0) {
								printf("Enter a valid month! Starting month:");
								scanf("%f", &month);
								rewind(stdin);
							}
							switch ((int)month) {
							case 1:
								strcpy(studSem2Sub[ID][6], "January");
								break;
							case 2:
								strcpy(studSem2Sub[ID][6], "February");
								break;
							case 3:
								strcpy(studSem2Sub[ID][6], "March");
								break;
							case 4:
								strcpy(studSem2Sub[ID][6], "April");
								break;
							case 5:
								strcpy(studSem2Sub[ID][6], "May");
								break;
							case 6:
								strcpy(studSem2Sub[ID][6], "June");
								break;
							case 7:
								strcpy(studSem2Sub[ID][6], "July");
								break;
							case 8:
								strcpy(studSem2Sub[ID][6], "August");
								break;
							case 9:
								strcpy(studSem2Sub[ID][6], "September");
								break;
							case 10:
								strcpy(studSem2Sub[ID][6], "October");
								break;
							case 11:
								strcpy(studSem2Sub[ID][6], "November");
								break;
							case 12:
								strcpy(studSem2Sub[ID][6], "December");
								break;
							}
							month = 0;//reset value
							printf("Enter starting year (e.g 2023):");
							scanf("%f", &year);
							rewind(stdin);
							while (year < 2000 || year>2100 || ((int)year) - year != 0) {
								printf("Invalid year! Only values of 2000~2100 are supported!\nEnter ending year:");
								scanf("%f", &year);
								rewind(stdin);
							}
							itoa((int)year, studSem2Sub[ID][7], 10);
							month = 0, year = 0;//reset value
							printf("Enter ending month of semester:\n1.January\n2.February\n3.March\n4.April\n5.May\n6.June\n7.July\n8.August\n9.September\n10.October\n11.November\n12.December\n");
							scanf("%f", &month);
							rewind(stdin);
							while (month < 1 || month>12||((int)month)-month!=0) {
								printf("Enter a valid month! Ending month:");
								scanf("%f", &month);
								rewind(stdin);
							}
							switch ((int)month) {
							case 1:
								strcpy(studSem2Sub[ID][8], "January");
								break;
							case 2:
								strcpy(studSem2Sub[ID][8], "February");
								break;
							case 3:
								strcpy(studSem2Sub[ID][8], "March");
								break;
							case 4:
								strcpy(studSem2Sub[ID][8], "April");
								break;
							case 5:
								strcpy(studSem2Sub[ID][8], "May");
								break;
							case 6:
								strcpy(studSem2Sub[ID][8], "June");
								break;
							case 7:
								strcpy(studSem2Sub[ID][8], "July");
								break;
							case 8:
								strcpy(studSem2Sub[ID][8], "August");
								break;
							case 9:
								strcpy(studSem2Sub[ID][8], "September");
								break;
							case 10:
								strcpy(studSem2Sub[ID][8], "October");
								break;
							case 11:
								strcpy(studSem2Sub[ID][8], "November");
								break;
							case 12:
								strcpy(studSem2Sub[ID][8], "December");
								break;
							}
							month = 0;//reset value
							printf("Enter ending year (e.g 2023):");
							scanf("%f", &year);
							rewind(stdin);
							while (year < 2000 || year>2100 || ((int)year) - year != 0) {
								printf("Invalid year! Only values of 2000~2100 are supported!\nEnter ending year:");
								scanf("%f", &year);
								rewind(stdin);
							}
							itoa((int)year, studSem2Sub[ID][9], 10);
							month = 0, year = 0;//reset value
							printf("\n\nSemester 2 session date added successfully!\n\n");
							strcpy(studentDetails[ID][6], "Y");
						}
						else if (sessionSelect == 3) {//3rd semester has same stucture as 1st, refer to those comments
							printf("Enter starting month of semester:\n1.January\n2.February\n3.March\n4.April\n5.May\n6.June\n7.July\n8.August\n9.September\n10.October\n11.November\n12.December\n");
							scanf("%f", &month);
							rewind(stdin);
							while (month < 1 || month>12 || ((int)month) - month != 0) {
								printf("Enter a valid month! Starting month:");
								scanf("%f", &month);
								rewind(stdin);
							}
							switch ((int)month) {
							case 1:
								strcpy(studSem3Sub[ID][6], "January");
								break;
							case 2:
								strcpy(studSem3Sub[ID][6], "February");
								break;
							case 3:
								strcpy(studSem3Sub[ID][6], "March");
								break;
							case 4:
								strcpy(studSem3Sub[ID][6], "April");
								break;
							case 5:
								strcpy(studSem3Sub[ID][6], "May");
								break;
							case 6:
								strcpy(studSem3Sub[ID][6], "June");
								break;
							case 7:
								strcpy(studSem3Sub[ID][6], "July");
								break;
							case 8:
								strcpy(studSem3Sub[ID][6], "August");
								break;
							case 9:
								strcpy(studSem3Sub[ID][6], "September");
								break;
							case 10:
								strcpy(studSem3Sub[ID][6], "October");
								break;
							case 11:
								strcpy(studSem3Sub[ID][6], "November");
								break;
							case 12:
								strcpy(studSem3Sub[ID][6], "December");
								break;
							}
							printf("Enter starting year (e.g 2023):");
							scanf("%f", &year);
							rewind(stdin);
							while (year < 2000 || year>2100 || ((int)year) - year != 0) {
								printf("Invalid year! Only values of 2000~2100 are supported!\nEnter ending year:");
								scanf("%f", &year);
								rewind(stdin);
							}
							itoa((int)year, studSem3Sub[ID][7], 10);
							month=0, year = 0;//reset value
							printf("Enter ending month of semester:\n1.January\n2.February\n3.March\n4.April\n5.May\n6.June\n7.July\n8.August\n9.September\n10.October\n11.November\n12.December\n");
							scanf("%f", &month);
							rewind(stdin);
							while (month < 1 || month>12 || ((int)month) - month != 0) {
								printf("Enter a valid month! Ending month:");
								scanf("%f", &month);
								rewind(stdin);
							}
							switch ((int)month) {
							case 1:
								strcpy(studSem3Sub[ID][8], "January");
								break;
							case 2:
								strcpy(studSem3Sub[ID][8], "February");
								break;
							case 3:
								strcpy(studSem3Sub[ID][8], "March");
								break;
							case 4:
								strcpy(studSem3Sub[ID][8], "April");
								break;
							case 5:
								strcpy(studSem3Sub[ID][8], "May");
								break;
							case 6:
								strcpy(studSem3Sub[ID][8], "June");
								break;
							case 7:
								strcpy(studSem3Sub[ID][8], "July");
								break;
							case 8:
								strcpy(studSem3Sub[ID][8], "August");
								break;
							case 9:
								strcpy(studSem3Sub[ID][8], "September");
								break;
							case 10:
								strcpy(studSem3Sub[ID][8], "October");
								break;
							case 11:
								strcpy(studSem3Sub[ID][8], "November");
								break;
							case 12:
								strcpy(studSem3Sub[ID][8], "December");
								break;
							}
							printf("Enter ending year (e.g 2023):");
							scanf("%f", &year);
							rewind(stdin);
							while (year < 2000 || year>2100 || ((int)year) - year != 0) {
								printf("Invalid year! Only values of 2000~2100 are supported!\nEnter ending year:");
								scanf("%f", &year);
								rewind(stdin);
							}
							itoa((int)year, studSem3Sub[ID][9], 10);
							month = 0, year = 0;//reset value
							printf("\n\nSemester 3 session date added successfully!\n\n");
							strcpy(studentDetails[ID][7], "Y");
						}
					}
					if (loop3 == 1) {
						printf("Would you like to continue to edit this student's details? Type 1 to continue, any other value to exit and return to admin menu.");
						if (scanf("%f", &loop3) == 0)loop3 = 0;
						rewind(stdin);
					}
				}
			break;
		case 3://prints student menu
			studentMenu();
			break;
		}
	}
}
int calcCGPA(sem,sub,ID) {//features multiple parameters, 1st is semester, 2nd is number of subject, 3rd is student position within array
	int i;
	float cred=0,wgpa=0;//credit and weighted GPA
	switch (sem) {//semester 
		case 1://1st
			cred = studSem1GPA[ID][12];
			for (i = 0;i <sub;i++)
				wgpa +=studSem1GPA[ID][i] * studSem1GPA[ID][i + 6];//credit hours*GPA
			studSem1GPA[ID][13] =(wgpa / cred);
			break;
		case 2://2nd
			cred = studSem2GPA[ID][12];
			for (i = 0;i <sub;i++) 
				wgpa =wgpa+ (studSem2GPA[ID][i] * studSem2GPA[ID][i + 6]);
			studSem2GPA[ID][13] = wgpa / cred;
			break;
		case 3://3rd
			cred = studSem3GPA[ID][12];
			for (i = 0;i <sub;i++)
				wgpa =wgpa+ (studSem3GPA[ID][i] * studSem3GPA[ID][i + 6]);
			studSem3GPA[ID][13] = wgpa / cred;
			break;
	}
	return 0;
}
void targetCalc() {
	int i,mpuCred=0,nCred=0,loop=1,ID,perk,merit=0,futurePerk;//nCred=normal total credit hours
	char IDcheck[10],meritPercent[5];
	float lastCGPA=0,tMPUGPA=0,tnGPA=0,tCGPA,select=0;//tnGPA=target normal GPA
	system("cls");
	for (i = 0; i < 50; i++) putchar('=');
	printf("\n%41s\n", "WELCOME TO CGPA TARGET CALCULATOR");
	for (i = 0; i < 50; i++) putchar('=');
	printf("\nMaking your college life easier!\n1.Import CGPA from existing student ID\n2.Manually input last semester's CGPA\n");//menu
	while (scanf("%f", &select) == 0 || select != 1 && select != 2) {
		rewind(stdin);
		printf("Invalid input! Enter 1 or 2 only!\n");
	}
	rewind(stdin);
	if (select == 1) {
		while (loop == 1) {
			printf("Enter student ID:");//enter ID and check if id is available
			scanf("%9s", IDcheck);
			rewind(stdin);
			for (ID = 0; ID < sizeof(studentDetails) / sizeof(studentDetails[0]);ID++) {
				if (strcmp(studentDetails[ID][0], IDcheck) == 0) {
					loop = 0;
					break;
				}
			}//verify ID
			if (ID == sizeof(studentDetails) / sizeof(studentDetails[0])) printf("Record not found!\n");//runs if id is unavailable
		}
		if (strcmp(studentDetails[ID][4], "Y") == 0) {
			printf("\nHello, %s. Your last semester's (Semester 3) CGPA is %.2f\n", studentDetails[ID][1], studSem3GPA[ID][13]);
			lastCGPA = studSem3GPA[ID][13];
		}
		else if (strcmp(studentDetails[ID][3], "Y") == 0) {
			printf("\nHello, %s. Your last semester's (Semester 2) CGPA is %.2f\n", studentDetails[ID][1], studSem2GPA[ID][13]);
			lastCGPA = studSem2GPA[ID][13];
		}
		else if (strcmp(studentDetails[ID][2], "Y") == 0) {
			printf("\nHello, %s. Your last semester's (Semester 1) CGPA is %.2f\n", studentDetails[ID][1], studSem1GPA[ID][13]);
			lastCGPA = studSem1GPA[ID][13];
		}//prints out last semester's CGPA (starting from semester 3 to 1)
		else {
			printf("\nHello %s. Unfortunately, you have not entered any subjects into the system yet. Hence, your last semester's CGPA cannot be determined. Please manually enter your last semester's CGPA.\n", studentDetails[ID][1]);
			select = 2;
		}//if no data found, asks user to manually enter
	}
	if (select == 2) {//else if is not used here as the user may be directed here even though they selected 1 (refer to line 968's else clause)
		printf("\nEnter your last semester's CGPA:");
		while (scanf("%5f", &lastCGPA) == 0 || lastCGPA < 0 || lastCGPA>4) {
			rewind(stdin);
			printf("Enter a valid CGPA between 0 and 4!\n\nEnter your last semester's CGPA:");
		}
		lastCGPA = round(lastCGPA * 100) / 100;
		rewind(stdin);
	}
	printf("\n%-72s:","Enter the total credit hours for MPU subjects for your next semester");//enter MPU total credit hours
	while (scanf("%d", &mpuCred) == 0 || mpuCred< 0) {//if negative value/invalid value
		rewind(stdin);
		printf("Enter a valid positive integer!\n\nEnter the total credit hours for MPU subjects for your next semester:");
	}
	rewind(stdin);
	printf("\n%-72s:","Enter the total credit hours for non-MPU subjects for your next semester");//enter normal subject total credit hours
	while (scanf("%d", &nCred) == 0 || nCred < 0) {//invalid value
		rewind(stdin);
		printf("Enter a valid positive integer!\n\nEnter the total credit hours for non-MPU subjects for your next semester:");
	}
	rewind(stdin);
	printf("\nEnter your current merit scholarship status:\n1. 100%%\n2. 50%%\n3. 25%%\n4. 20%%\n5. 15%%\n0. None.\n");
	while (scanf("%d", &merit) == 0 || merit< 0||merit>5) {//invalid value
		rewind(stdin);
		printf("Invalid value entered!\n\nEnter your current merit scholarship status:");
	}
	rewind(stdin);
	system("cls");
	tCGPA =(ceil(lastCGPA * 10) / 10)+0.1;
	if (tCGPA > 4)tCGPA = 4;//ensure target CGPA does not exceed 4.0 as it is not possible
	tnGPA = (float)(tCGPA*(mpuCred+nCred)-(0.5*mpuCred))/(mpuCred+nCred);//simultaneous equations
	tMPUGPA = tnGPA + 0.5;
	if (tnGPA < 2) {//normal target GPA cannot be below 2 (fail)
		tnGPA = 2;
		tMPUGPA = 2.5;
		tCGPA = (float)(nCred*tnGPA+mpuCred*tMPUGPA)/(nCred+mpuCred);//target CGPA recalculation
	}
	else if (tnGPA > 3.5) {//if MPU target GPA exceeds 4 (or normal GPA exceeds 3.5 which causes the former to happen)
		tnGPA = (float)(tCGPA * (mpuCred + nCred)-(4*mpuCred))/nCred;
		if (tnGPA < 2) tnGPA = 2;
		tMPUGPA = 4;
		tCGPA = (float)(nCred * tnGPA + mpuCred * tMPUGPA) / (nCred + mpuCred);//target GPA recalculation
	}
	if (tCGPA < 3) perk = 0;//determine perks and benefits
	else if (tCGPA >= 3.0 && tCGPA < 3.25) {
		if (merit != 0) perk = 1;
		else perk = 0;
	}
	else if (tCGPA >= 3.25 && tCGPA < 3.5) {
		if (merit == 2 || merit == 1)perk = 2;
		else if (merit==0) perk = 0;
		else perk = 1;
	}
	else if (tCGPA >= 3.5) {
		if (merit == 1) perk = 3;
		else if (merit == 2)perk = 2;
		else if (merit != 0) perk = 1;
		else perk = 0;
	}
	if (tCGPA >= 3.85) futurePerk = 3;//determine future perks
	else if (tCGPA >= 3.75&& tCGPA<=3.85)futurePerk = 2;
	else if (tCGPA >= 2.5&&tCGPA<=3.75) futurePerk = 1;
	else futurePerk = 0;
	switch (merit) {//switch case, to find out merit percent
		case 0:
			strcpy(meritPercent, "0%");
			break;
		case 1:
			strcpy(meritPercent, "100%");
			break;
		case 2:
			strcpy(meritPercent, "50%");
			break;
		case 3:
			strcpy(meritPercent, "25%");
			break;
		case 4:
			strcpy(meritPercent, "20%");
			break;
		case 5:
			strcpy(meritPercent, "15%");
	}
	printf("Your last semester's CGPA (rounded to 2 d.p) is %.2f.\nYour targeted CGPA is %.2f.\n\n------------------------------------------------------------------------------------\nYour targeted GPA for non-MPU subjects: %.2f\nYour targeted GPA for MPU subjects: %.2f\n------------------------------------------------------------------------------------\nA targeted CGPA of %.2f with a current merit scholarship of %s unlocks the following perks and benefits if the target is attained:\n", lastCGPA, tCGPA,tnGPA,tMPUGPA,tCGPA,meritPercent);
	switch (perk) {//output current perks
		case 0:
			printf("> Pass in all courses, allows for continuation towards the next semester.\n> No merit scholarship.");
			break;
		case 1:
			if(merit==4) printf("> Pass in all courses, allows for continuation towards the next semester.\n> Allows for the retainment of merit scholarship worth 20%%.");
			else if (merit == 5) printf("> Pass in all courses, allows for continuation towards the next semester.\n> Allows for the retainment of merit scholarship worth 15%%.");
			else printf("> Pass in all courses, allows for continuation towards the next semester.\n> Allows for the retainment of merit scholarship worth 25%%.");
			break;
		case 2:
			printf("> Pass in all courses, allows for continuation towards the next semester.\n> Allows for the retainment of merit scholarship worth 50%%.");
			break;
		case 3:
			printf("> Pass in all courses, allows for continuation towards the next semester.\n> Allows for the retainment of merit scholarship worth 100%%.");
	}
	printf("\n------------------------------------------------------------------------------------\nOther than that, ending your programme with a CGPA of %.2f also brings the following future perks (only applicable for degree programmes):\n",tCGPA);
	switch (futurePerk) {//output future perks
	case 0:
		printf("> Entry into a relevant degree programme upon passing a Qualifying Test.\n> No merit scholarship.");
		break;
	case 1:
		printf("> Entry into a relevant degree programme.\n> No merit scholarship.");
		break;
	case 2:
		printf("> Entry into a relevant degree programme.\n> Entitled to a 50%% merit scholarship upon enrollment subject to academic criteria.");
		break;
	case 3:
		printf("> Entry into a relevant degree programme.\n> Entitled to a 100%% merit scholarship upon enrollment subject to academic criteria.");
	}
	printf("\n------------------------------------------------------------------------------------\n\nThank you for using this target calculator!\n");
}
void main(){
	float loop =1;
	while (loop ==1) {
		attempt = 1;//reset attempt
		menuSelect = -1;
		menu();
		if (menuSelect == 1) {
			loginSelect = 0;
			login();
			if (loginSelect == 1) {//admin menu selected
				pass1 = 0, pass2 = 0;
				while (pass1 == 0) {
					accID = 1;
					getAID();//get admin id
				}
				while (pass1 == 1 && pass2 == 0) {
					getPW();//get admin password
				}
				if (pass1 == 1 && pass2 == 1) { adminMenu(); }//if admin password and id is correct
			}
			if (loginSelect == 2) {//student details selected
				studentMenu();
			}
		}
		else if (menuSelect == 2) targetCalc();
		else if (menuSelect == 0) exit(1);//exit program
		printf("\nWould you like to continue using this program? Type 1 to continue; any other value to exit.\n");
		if (scanf("%f", &loop) == 0)loop = 0;//runs if user inputs non-int value, regards it as exit loop;
		rewind(stdin);
		system("cls");//clears console
	}
	if (loop != 1)exit(0);//also exit program
}
