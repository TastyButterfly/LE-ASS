#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#pragma warning (disable:4996)
int menuSelect,loginSelect,pass1,pass2,pass3,accID,linecheck,SIDline,attempt;
char PIN[8], studentDetails[][3][60] = { {"KPKL1234","idk",},{""} }/*ID, name*/, studSem1Sub[][8][10] = { {"AAA1003","AAA1014","AAA1013","AAA1024","AAA1024","AAA1052","July","October"}}, studSem2Sub[][13][8] = {{"AAA1103","AAA1114","AAA1113","","","","November","January"}}, studSem3Sub[][13][8] = {{"AAA1203","AAA1214","AAA1213","AAA1224","AAA1224","AAA1252","February","June"}};//course codes, sem start, sem end
char* PINcheck[] = {"234567","123456","234565"};
float studSem1GPA[][13]={{4.0,4.0,4.0,4.0,4.0,4.0,3,4,3,4,4,2,20}}, studSem2GPA[][13] = { {4.0,4.0,4.0,0,0,0,3,4,3,0,0,0,10} }, studSem3GPA[][13] = { {4.0,4.0,4.0,4.0,4.0,4.0,3,4,3,4,4,2,20} };//gpa for respective course and total sem credit hours
void menu() {
	for (int i = 0; i < 50; i++) {
		putchar('=');
	}
	printf("\n%27s\n", "MENU");
	for (int i = 0; i < 50; i++) {
		putchar('=');
	}
	printf("\n1.CGPA System\n2.CGPA Target Calculator\n");
	//above prints out menu interface and options
	do { //do loop
		scanf("%d", &menuSelect);
		rewind(stdin);//while this is only required for [^\n] in theory, rewind is useful here if user inputs chars or strings
		if (menuSelect != 2 && menuSelect != 1)
			printf("Enter 1 or 2 only!\n");//only displayed if user gives wrong input
	} while (menuSelect != 2 && menuSelect != 1);//if user does not input given options, they are asked to input again
}
void getAID() {
	char AID[11], IDcheck[10];
	if (attempt == 1) {
		printf("Enter login credentials\nAdmin ID:");
	}
	else { printf("Record not found!\nAdmin ID:"); }
	scanf("%10s", AID);
	rewind(stdin);//needed if input exceeds 10 characters, same applies to all rewinds after %ns after this occurence
	FILE* file1 = fopen("AID.txt", "r");
	rewind(file1);
	while (fgets(IDcheck, sizeof(IDcheck), file1)) {
		if (strcmp(AID, IDcheck) == 0) {
			accID/=2;
			attempt = 1;
			printf("Logged in successfully.\n");
			pass1 = 1;//is a global variable set to 0;allows the loop to exit
			fclose(file1);	
		}
		else {accID++;}
	}
	attempt++;
}
void getSID() {
	char SID[9];
	int IDcheck=0,IDcheckline = 0;
	if (attempt == 1) {
		printf("Enter login credentials(0 to exit)\nStudent ID:");
	}
	else { printf("Record not found!(0 to exit)\nStudent ID:"); }
	scanf("%9s",SID);
	rewind(stdin);
	for (int i = 0;i <(sizeof(studentDetails)/sizeof(studentDetails[0])); i++) {
		if (strcmp(SID,studentDetails[i][0]) == 0) {
			printf("Logged in successfully.\nWelcome, %s",studentDetails[i][1]);
			pass3 = 1;//is a global variable set to 0;allows the loop to exit
			attempt = 1;
			break;
		}
		else if(strcmp(SID, "0") == 0) {
			pass3 = -1;
			break;
		}
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
	scanf("%d", &loginSelect);
	while (loginSelect != 2 && loginSelect != 1) {//while loop
		rewind(stdin);//refer to menu()
		printf("Enter 1 or 2 only!\n");
		scanf("%d", &loginSelect);
	}
}
void getPW() {
	printf("Enter PIN:");
	scanf("%7s", PIN);
	if (strcmp(PIN,PINcheck[accID])==0) {
		rewind(stdin);
		printf("Access granted\n");
		pass2 = 1;
	}
	else {printf("Wrong password\n");}
}
void adminMenu() {
	system("cls");
	for (int i = 0; i < 50; i++) {
		putchar('=');
	}
	printf("\n%30s\n", "ADMIN MENU");
	for (int i = 0; i < 50; i++) {
		putchar('=');
	}
	//above is to print admin menu, clears console
	int select, subSelect, i, loop = 1, loop2 = 1, menu2select, subjectLoop, ID,check, semSelect, gradeLoop = 1,sessionSelect;
	char IDcheck[10], grade[2],stdID[10],IDConfirm[10],stdName[60],nameConfirm[60];
	while (loop == 1) {
		printf("\n1.Add new student.\n2.Enter student course details.\n3.View students' CGPA and GPA score.\n0.Exit\n");//prints menu
		scanf("%d", &select);
		while (select < 1 || select >3) {
			rewind(stdin);
			printf("Enter a value between 1 to 3!");
			scanf("%d", &select);
		}//checks input
		switch (select) {
		case 0:
			loop = 0;
			break;//exit
		case 1://add new student
			system("cls");
			for (ID = 0; ID < sizeof(studentDetails) / sizeof(studentDetails[0]);ID++) {
				if (strcmp(studentDetails[ID][0], "") == 0) { break; }
			}//check id validity
			printf("Enter new student ID:");
			scanf("%9s", studentDetails[ID][0]);
			rewind(stdin);
			printf("Confirm ID (ID cannot be changed!):");
			scanf("%9s", IDConfirm);
			rewind(stdin);
			for (check = 0; check < (sizeof(studentDetails) / sizeof(studentDetails[0])) - 1;check++) {
				if (strcmp(studentDetails[ID][0], studentDetails[check][0]) == 0) {
					printf("ID is already used!\n");
					printf("Enter new student ID:");
					scanf("%8s", studentDetails[ID][0]);
					rewind(stdin);
					printf("Confirm ID (ID cannot be changed!):");
					scanf("%9s", IDConfirm);
					rewind(stdin);
				}
			}//check id duplicate
			while (strcmp(studentDetails[ID][0], IDConfirm) != 0) {
				printf("ID does not match or is invalid!\n");
				printf("Enter new student ID:");
				scanf("%8s", studentDetails[ID][0]);
				rewind(stdin);
				printf("Confirm ID (ID cannot be changed!):");
				scanf("%9s", IDConfirm);
				rewind(stdin);
			}//check confirmation id match
			strcpy(studentDetails[ID + 1][0], "");
			printf("Enter new student name:");
			scanf("%59[^\n]", studentDetails[ID][1]);
			rewind(stdin);
			printf("Confirm name (name cannot be changed!):");
			scanf("%59[^\n]", nameConfirm);
			rewind(stdin);
			for (check = 0; check < (sizeof(studentDetails) / sizeof(studentDetails[0])) - 1;check++) {
				if (strcmp(studentDetails[ID][1], studentDetails[check][1]) == 0) {
					printf("Name is already used!\n");
					printf("Enter new student name:");
					scanf("%59[^\n]", studentDetails[ID][1]);
					rewind(stdin);
					printf("Confirm name (name cannot be changed!):");
					scanf("%59[^\n]", nameConfirm);
					rewind(stdin);
				}
			}//check duplicate name
			while (strcmp(studentDetails[ID][1], nameConfirm) != 0) {
				printf("Name does not match!\n");
				printf("Enter new student name:");
				scanf("%59[^\n]", studentDetails[ID][1]);
				rewind(stdin);
				printf("Confirm name (name cannot be changed!):");
				scanf("%59[^\n]", nameConfirm);
				rewind(stdin);
			}//check name confirmation
			printf("Would you like to continue editing student details? Enter 1 to continue, any other value to stop.");
			scanf("%d", &loop);
			rewind(stdin);
			break;
		case 2://enter course details
			while (loop2 == 1) {
				printf("Enter student ID:");
				scanf("%9s", IDcheck);
				rewind(stdin);
				for (ID = 0; ID < sizeof(studentDetails) / sizeof(studentDetails[0]);ID++) {
					if (strcmp(studentDetails[ID][0], IDcheck) == 0) {
						loop2 = 0;
						break;}
				}
			}//enter ID and check if id is available
			if (ID == sizeof(studentDetails) / sizeof(studentDetails[0])) { printf("Record not found!"); }//runs if id is unavailable
			else {//if id is found in system:
				system("cls");
				for (int i = 0; i < 50; i++) {
					putchar('=');
				}
				printf("\n%33s\n", "DETAILS EDITOR");
				for (int i = 0; i < 50; i++) {
					putchar('=');
				}//print menu
				menuSelect = 0;//reset parameters
				printf("\nYou are now editing %s, %s's details\n1.Enter course code and grade obtained.\n2.Enter current semester session.\n", studentDetails[ID][0], studentDetails[ID][1]);
				scanf("%d", &menu2select);
				while (menu2select != 1 && menu2select != 2) {
					rewind(stdin);
					printf("Enter a value between 1 to 2!\n");
					scanf("%d", &menu2select);
				}//check user input validity
				switch (menu2select) {
				case 1://input course details
					semSelect = 0;
					printf("Enter edited semester (1,2 or 3):");
					scanf("%d", &semSelect);
					while (semSelect < 1 || semSelect>3) {
						rewind(stdin);
						printf("Enter 1,2 or 3 only!\n");
						scanf("%d", &semSelect);
					}//check user input validity
					subjectLoop = 0;
					switch (semSelect) {
					case 1:
						printf("Enter number of courses:");
						scanf("%d", &subjectLoop);
						while (subjectLoop > 6 || subjectLoop < 0) {
							rewind(stdin);
							printf("Enter a number between 1 to 6!");
							scanf("%d", &subjectLoop);
						}//check user input validity
						for (int n = 0;n < subjectLoop;n++) {
							printf("Enter course code for subject %d", n + 1);
							scanf("%7s", studSem1Sub[ID][n]);//reads until 7 chars only
							rewind(stdin);
							studSem1GPA[ID][n + 6] = (float)studSem1Sub[ID][n][6] - 48;//course weightage
							printf("Enter grade obtained:");
							scanf("%2s", grade);
							while (gradeLoop == 1) {
								if (strcmp(grade, "A") == 0) {
									studSem1GPA[ID][n] = 4.0;
									gradeLoop = 0;
								}
								else if (strcmp(grade, "A-") == 0) {
									studSem1GPA[ID][n] = 3.75;
									gradeLoop = 0;
								}
								else if (strcmp(grade, "B+") == 0) {
									studSem1GPA[ID][n] = 3.50;
									gradeLoop = 0;
								}
								else if (strcmp(grade, "B") == 0) {
									studSem1GPA[ID][n] = 3.00;
									gradeLoop = 0;
								}
								else if (strcmp(grade, "B-") == 0) {
									studSem1GPA[ID][n] = 2.75;
									gradeLoop = 0;
								}
								else if (strcmp(grade, "C+") == 0) {
									studSem1GPA[ID][n] = 2.50;
									gradeLoop = 0;
								}
								else if (strcmp(grade, "C") == 0) {
									studSem1GPA[ID][n] = 2.00;
									gradeLoop = 0;
								}
								else if (strcmp(grade, "F") == 0) {
									studSem1GPA[ID][n] = 0.00;
									gradeLoop = 0;
								}
								else {
									rewind(stdin);
									printf("Enter a valid grade!");
									scanf("%2s", grade);
								}
							}
						}
						break;
					case 2:
						printf("Enter number of courses:");
						scanf("%d", &subjectLoop);
						while (subjectLoop > 6 || subjectLoop < 0) {
							rewind(stdin);
							printf("Enter a number between 1 to 6!");
							scanf("%d", &subjectLoop);
						}
						for (int n = 0;n < subjectLoop;n++) {
							printf("Enter course code for subject %d", n + 1);
							scanf("%7s", studSem2Sub[ID][n]);//reads until 7 chars only
							rewind(stdin);
							studSem2GPA[ID][n + 6] = (float)studSem2Sub[ID][n][6] - 48;//calculate course weightage
							printf("Enter grade obtained:");
							scanf("%2s", grade);
							while (gradeLoop == 1) {
								if (strcmp(grade, "A") == 0) {
									studSem2GPA[ID][n] = 4.0;
									gradeLoop = 0;
								}
								else if (strcmp(grade, "A-") == 0) {
									studSem2GPA[ID][n] = 3.75;
									gradeLoop = 0;
								}
								else if (strcmp(grade, "B+") == 0) {
									studSem2GPA[ID][n] = 3.50;
									gradeLoop = 0;
								}
								else if (strcmp(grade, "B") == 0) {
									studSem2GPA[ID][n] = 3.00;
									gradeLoop = 0;
								}
								else if (strcmp(grade, "B-") == 0) {
									studSem2GPA[ID][n] = 2.75;
									gradeLoop = 0;
								}
								else if (strcmp(grade, "C+") == 0) {
									studSem2GPA[ID][n] = 2.50;
									gradeLoop = 0;
								}
								else if (strcmp(grade, "C") == 0) {
									studSem2GPA[ID][n] = 2.00;
									gradeLoop = 0;
								}
								else if (strcmp(grade, "F") == 0) {
									studSem2GPA[ID][n] = 0.00;
									gradeLoop = 0;
								}
								else {
									rewind(stdin);
									printf("Enter a valid grade!");
									scanf("%2s", grade);
								}
							}
						}
						break;
					case 3:
						printf("Enter number of courses:");
						scanf("%d", &subjectLoop);
						while (subjectLoop > 6 || subjectLoop < 0) {
							rewind(stdin);
							printf("Enter a number between 1 to 6!");
							scanf("%d", &subjectLoop);
						}
						for (int n = 0;n < subjectLoop;n++) {
							printf("Enter course code for subject %d", n + 1);
							scanf("%7s", studSem3Sub[ID][n]);//reads until 7 chars only
							rewind(stdin);
							studSem3GPA[ID][n + 6] = (float)studSem3Sub[ID][n][6] - 48;//calculate course weightage
							printf("Enter grade obtained:");
							scanf("%2s", grade);
							while (gradeLoop == 1) {
								if (strcmp(grade, "A") == 0) {
									studSem3GPA[ID][n] = 4.0;
									gradeLoop = 0;
								}
								else if (strcmp(grade, "A-") == 0) {
									studSem3GPA[ID][n] = 3.75;
									gradeLoop = 0;
								}
								else if (strcmp(grade, "B+") == 0) {
									studSem3GPA[ID][n] = 3.50;
									gradeLoop = 0;
								}
								else if (strcmp(grade, "B") == 0) {
									studSem3GPA[ID][n] = 3.00;
									gradeLoop = 0;
								}
								else if (strcmp(grade, "B-") == 0) {
									studSem3GPA[ID][n] = 2.75;
									gradeLoop = 0;
								}
								else if (strcmp(grade, "C+") == 0) {
									studSem3GPA[ID][n] = 2.50;
									gradeLoop = 0;
								}
								else if (strcmp(grade, "C") == 0) {
									studSem3GPA[ID][n] = 2.00;
									gradeLoop = 0;
								}
								else if (strcmp(grade, "F") == 0) {
									studSem3GPA[ID][n] = 0.00;
									gradeLoop = 0;
								}
								else {
									rewind(stdin);
									printf("Enter a valid grade!");
									scanf("%2s", grade);
								}
							}
						}

					}
					break;
				case 2:
					printf("Enter edited semester:");
					scanf("%d", &sessionSelect);
					while (sessionSelect < 1 || sessionSelect>3) {
						rewind(stdin);
						printf("Enter 1,2 or 3 only!\n");
						scanf("%d", &sessionSelect);
					}//check user input validity
					
				}
			}
			break;
		case 3:break;
		}
	}
}
	
void main(){
	char loop = '1';
	while (loop == '1') {
		attempt = 1;
		menu();
		if (menuSelect == 1) {
			login();
			if (loginSelect == 1) {
				pass1 = 0, pass2 = 0;
				while (pass1 == 0) { 
					accID = 1;
					getAID();
				}
				while (pass1 == 1 && pass2 == 0) {
					getPW();
				}
				while (pass1 == 1 && pass2 == 1) { adminMenu();break; }
			}
			if (loginSelect == 2) {
				pass3 = 0;
				while (pass3 == 0) {
					getSID();
				}
				while (pass3 == 1) {}
			}
		}
		else if (menuSelect==2){}
		printf("\nWould you like to continue? Type 1 to continue; any other value to exit.\n");
		scanf("%c", &loop);
		rewind(stdin);
		system("cls");//clears console
	}
}