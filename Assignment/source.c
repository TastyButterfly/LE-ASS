#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#pragma warning (disable:4996)
int menuSelect,loginSelect,pass1,pass2,pass3,accID,linecheck,SIDline,attempt;
char PIN[8], studentDetails[][8][61] = { {"KPKL1234","idk","Y","Y","Y","Y","Y","Y"},{""}}/*ID, name,subject entry (3 semesters), session entry (3 semesters)*/, studSem1Sub[][10][15] = {{"AAA1003","AAA1014","AAA1013","AAA1024","AAA1024","AAA1052","July","2023","October","2023"}}, studSem2Sub[][10][15] = {{"AAA1103","AAA1114","AAA1113","","","","November","2023","January","2024"}}, studSem3Sub[][10][15] = {{"AAA1203","AAA1214","AAA1213","AAA1224","AAA1224","AAA1252","February","2024","June","2024"}};//course codes(0-5), sem start(6/7), sem end(8/9)
char* PINcheck[] = {"234567","123456","234565"};
float studSem1GPA[][15]={{4.0,4.0,4.0,4.0,4.0,4.0,3,4,3,4,4,2,20,4.0,6}}, studSem2GPA[][15] = { {4.0,4.0,4.0,0,0,0,3,4,3,0,0,0,10,4.0,3} }, studSem3GPA[][15] = { {4.0,4.0,4.0,4.0,4.0,4.0,3,4,3,4,4,2,20,4.0,6} };//gpa for respective course(0-5),sem credit hours(6-11),total credit hours(12),cgpa(13),number of subjects(14)
void menu() {
	int i;//counter
	for (i = 1;i <= 148;i++) {
		putchar('*');
		if (i == 70 || i == 140)printf("\n");
	}
	printf("Welcome to Kolej Pasar's Multipurpose CGPA Calculator!");
	for (i = 1;i <= 148;i++) {
		putchar('*');
		if (i==8||i == 78|| i == 148)printf("\n");
	}
	printf("\n\n");
	for (i = 0; i < 50; i++) putchar('=');
	printf("\n%27s\n", "MENU");
	for (i = 0; i < 50; i++) putchar('=');
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
	char SID[10];
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
	int select=0, i, loop = 1, loop2 = 1,loop3=1,loop4=1, menu2select=0, subjectLoop=0, ID,check, semSelect=0, gradeLoop = 1,sessionSelect=0,month=0,year=0;
	char IDcheck[10], grade[3],IDConfirm[10],stdName[61],nameConfirm[61];
	float totalcgpa=0,wcgpa=0,totalcred=0;
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
			scanf("%8s", studentDetails[ID][0]);
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
			studSem3GPA[ID][12] = 0;
			printf("Enter new student name (max. 60 characters):");
			scanf("%60[^\n]", studentDetails[ID][1]);
			rewind(stdin);
			printf("Confirm name (name cannot be changed!):");
			scanf("%60[^\n]", nameConfirm);
			rewind(stdin);
			for (check = 0; check < (sizeof(studentDetails) / sizeof(studentDetails[0])) - 1;check++) {
				if (strcmp(studentDetails[ID][1], studentDetails[check][1]) == 0) {
					printf("Name is already used!\n");
					printf("Enter new student name (max. 60 characters):");
					scanf("%60[^\n]", studentDetails[ID][1]);
					rewind(stdin);
					printf("Confirm name (name cannot be changed!):");
					scanf("%60[^\n]", nameConfirm);
					rewind(stdin);
				}
			}//check duplicate name
			while (strcmp(studentDetails[ID][1], nameConfirm) != 0) {
				printf("Name does not match!\n");
				printf("Enter new student name:");
				scanf("%60[^\n]", studentDetails[ID][1]);
				rewind(stdin);
				printf("Confirm name (name cannot be changed!):");
				scanf("%60[^\n]", nameConfirm);
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
				}//verify ID
			}//enter ID and check if id is available
			if (ID == sizeof(studentDetails) / sizeof(studentDetails[0])) { printf("Record not found!"); }//runs if id is unavailable
			else {//if id is found in system:
				while (loop3 == 1) {
					system("cls");
					for (int i = 0; i < 50; i++) {
						putchar('=');
					}
					printf("\n%33s\n", "DETAILS EDITOR");
					for (int i = 0; i < 50; i++) {
						putchar('=');
					}//print menu
					menuSelect = 0;//reset parameters
					printf("\nYou are now editing %s, %s's details\n1.Enter course code and grade obtained.\n2.Enter current semester session.\n0.Exit\n", studentDetails[ID][0], studentDetails[ID][1]);
					scanf("%d", &menu2select);
					while (menu2select != 1 && menu2select != 2 && menu2select!=0) {
						rewind(stdin);
						printf("Enter a value between 0 to 2!\n");
						scanf("%d", &menu2select);
					}//check user input validity
					switch (menu2select) {
					case 0:break;
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
							subjectLoop = 0;//reset parameters
							printf("Enter number of courses:");
							scanf("%d", &subjectLoop);
							while (subjectLoop > 6 || subjectLoop < 1) {
								rewind(stdin);
								printf("Enter a number between 1 to 6!");
								scanf("%d", &subjectLoop);
							}//check user input validity
							studSem1GPA[ID][14] = subjectLoop;
							for (int n = 0;n < subjectLoop;n++) {
								printf("Enter course code for subject %d: ", n + 1);
								scanf("%7s", studSem1Sub[ID][n]);//reads until 7 chars only
								rewind(stdin);
								while ((float)studSem1Sub[ID][n][6]-48< 0 ||(float)studSem1Sub[ID][n][6]-48>9) {
									printf("Invalid course code!");
									scanf("%7s", studSem1Sub[ID][n]);//reads until 7 chars only
									rewind(stdin);
								}
								studSem1GPA[ID][n + 6] = (float)studSem1Sub[ID][n][6] - 48;//course weightage
								studSem1GPA[ID][12] += studSem1GPA[ID][n + 6];
								printf("Enter grade obtained:");
								scanf("%2s", grade);
								gradeLoop = 1;
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
										rewind(stdin);
									}
								}
							}
							strcpy(studentDetails[ID][2], "Y");
							calcCGPA(1,subjectLoop,ID);
							break;
						case 2:
							subjectLoop = 0;//reset parameters
							printf("Enter number of courses:");
							scanf("%d", &subjectLoop);
							while (subjectLoop > 6 || subjectLoop < 0) {
								rewind(stdin);
								printf("Enter a number between 1 to 6!");
								scanf("%d", &subjectLoop);
							}
							studSem2GPA[ID][14] = subjectLoop;
							for (int n = 0;n < subjectLoop;n++) {
								printf("Enter course code for subject %d: ", n + 1);
								scanf("%7s", studSem2Sub[ID][n]);//reads until 7 chars only
								rewind(stdin);
								while ((float)studSem2Sub[ID][n][6] - 48 < 0 || (float)studSem2Sub[ID][n][6] - 48 > 9) {
									printf("Invalid course code!");
									scanf("%7s", studSem2Sub[ID][n]);//reads until 7 chars only
									rewind(stdin);
								}
								studSem2GPA[ID][n + 6] = (float)studSem2Sub[ID][n][6] - 48;//course weightage
								studSem2GPA[ID][12] += studSem2GPA[ID][n + 6];
								printf("Enter grade obtained:");
								scanf("%2s", grade);
								gradeLoop = 1;
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
							strcpy(studentDetails[ID][3], "Y");
							calcCGPA(2, subjectLoop, ID);
							break;
						case 3:
							subjectLoop = 0;//reset parameters
							printf("Enter number of courses:");
							scanf("%d", &subjectLoop);
							while (subjectLoop > 6 || subjectLoop < 0) {
								rewind(stdin);
								printf("Enter a number between 1 to 6!");
								scanf("%d", &subjectLoop);
							}
							studSem3GPA[ID][14] = subjectLoop;
							for (int n = 0;n < subjectLoop;n++) {
								printf("Enter course code for subject %d: ", n + 1);
								scanf("%7s", studSem3Sub[ID][n]);//reads until 7 chars only
								rewind(stdin);
								while ((float)studSem3Sub[ID][n][6] - 48 < 0 || (float)studSem3Sub[ID][n][6] - 48 > 9) {
									printf("Invalid course code!");
									scanf("%7s", studSem3Sub[ID][n]);//reads until 7 chars only
									rewind(stdin);
								}
								studSem3GPA[ID][n + 6] = (float)studSem3Sub[ID][n][6] - 48;//course weightage
								studSem3GPA[ID][12] += studSem3GPA[ID][n + 6];
								printf("Enter grade obtained:");
								scanf("%2s", grade);
								gradeLoop = 1;
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
							strcpy(studentDetails[ID][4], "Y");
							calcCGPA(3, subjectLoop, ID);
						}
						break;
					case 2:
						printf("Enter edited semester (1,2 or 3):");
						scanf("%d", &sessionSelect);
						rewind(stdin);
						while (sessionSelect < 1 || sessionSelect>3) {
							rewind(stdin);
							printf("Enter 1,2 or 3 only!\n");
							scanf("%d", &sessionSelect);
						}//check user input validity
						if (sessionSelect == 1) {
							printf("Enter starting month of semester:\n1.January\n2.February\n3.March\n4.April\n5.May\n6.June\n7.July\n8.August\n9.September\n10.October\n11.November\n12.December\n");
							scanf("%d",&month);
							rewind(stdin);
							while (month < 1 || month>12) {
								printf("Enter a valid month! Starting month:");
								scanf("%d", &month);
								rewind(stdin);
							}
							switch (month) {
							case 1:
								strcpy(studSem1Sub[ID][6], "January");
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
							month = 0;//reset value
							printf("Enter starting year (e.g 2023):");
							scanf("%d", &year);
							rewind(stdin);
							while (year < 2000 || year>2100) {
								printf("Invalid year! Only values of 2000~2100 are supported!\nEnter starting year:");
								scanf("%d", &year);
								rewind(stdin);
							}
							itoa(year, studSem1Sub[ID][7],10);
							year = 0;//reset value
							printf("Enter ending month of semester:\n1.January\n2.February\n3.March\n4.April\n5.May\n6.June\n7.July\n8.August\n9.September\n10.October\n11.November\n12.December\n");
							scanf("%d", &month);
							rewind(stdin);
							while (month < 1 || month>12) {
								printf("Enter a valid month! Ending month:");
								scanf("%d", &month);
								rewind(stdin);
							}
							switch (month) {
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
							month = 0;//reset value
							printf("Enter ending year (e.g 2023):");
							scanf("%d", &year);
							rewind(stdin);
							while (year < 2000 || year>2100) {
								printf("Invalid year! Only values of 2000~2100 are supported!\nEnter ending year:");
								scanf("%d", &year);
								rewind(stdin);
							}
							itoa(year, studSem1Sub[ID][9], 10);
							year = 0;//reset value
							strcpy(studentDetails[ID][5], "Y");
						}
						else if (sessionSelect == 2) {
							printf("Enter starting month of semester:\n1.January\n2.February\n3.March\n4.April\n5.May\n6.June\n7.July\n8.August\n9.September\n10.October\n11.November\n12.December\n");
							scanf("%d", &month);
							rewind(stdin);
							while (month < 1 || month>12) {
								printf("Enter a valid month! Starting month:");
								scanf("%d", &month);
								rewind(stdin);
							}
							switch (month) {
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
							scanf("%d", &year);
							rewind(stdin);
							while (year < 2000 || year>2100) {
								printf("Invalid year! Only values of 2000~2100 are supported!\nEnter starting year:");
								scanf("%d", &year);
								rewind(stdin);
							}
							itoa(year, studSem2Sub[ID][7], 10);
							year = 0;//reset value
							printf("Enter ending month of semester:\n1.January\n2.February\n3.March\n4.April\n5.May\n6.June\n7.July\n8.August\n9.September\n10.October\n11.November\n12.December\n");
							scanf("%d", &month);
							rewind(stdin);
							while (month < 1 || month>12) {
								printf("Enter a valid month! Ending month:");
								scanf("%d", &month);
								rewind(stdin);
							}
							switch (month) {
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
							scanf("%d", &year);
							rewind(stdin);
							while (year < 2000 || year>2100) {
								printf("Invalid year! Only values of 2000~2100 are supported!\nEnter ending year:");
								scanf("%d", &year);
								rewind(stdin);
							}
							itoa(year, studSem2Sub[ID][9], 10);
							year = 0;//reset value
							strcpy(studentDetails[ID][6], "Y");
						}
						else if (sessionSelect == 3) {
							printf("Enter starting month of semester:\n1.January\n2.February\n3.March\n4.April\n5.May\n6.June\n7.July\n8.August\n9.September\n10.October\n11.November\n12.December\n");
							scanf("%d", &month);
							rewind(stdin);
							while (month < 1 || month>12) {
								printf("Enter a valid month! Starting month:");
								scanf("%d", &month);
								rewind(stdin);
							}
							switch (month) {
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
							month = 0;//reset value
							printf("Enter starting year (e.g 2023):");
							scanf("%d", &year);
							rewind(stdin);
							while (year < 2000 || year>2100) {
								printf("Invalid year! Only values of 2000~2100 are supported!\nEnter starting year:");
								scanf("%d", &year);
								rewind(stdin);
							}
							itoa(year, studSem3Sub[ID][7], 10);
							year = 0;//reset value
							printf("Enter ending month of semester:\n1.January\n2.February\n3.March\n4.April\n5.May\n6.June\n7.July\n8.August\n9.September\n10.October\n11.November\n12.December\n");
							scanf("%d", &month);
							rewind(stdin);
							while (month < 1 || month>12) {
								printf("Enter a valid month! Ending month:");
								scanf("%d", &month);
								rewind(stdin);
							}
							switch (month) {
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
							month = 0;//reset value
							printf("Enter ending year (e.g 2023):");
							scanf("%d", &year);
							rewind(stdin);
							while (year < 2000 || year>2100) {
								printf("Invalid year! Only values of 2000~2100 are supported!\nEnter ending year:");
								scanf("%d", &year);
								rewind(stdin);
							}
							itoa(year, studSem3Sub[ID][9], 10);
							year = 0;//reset value
							strcpy(studentDetails[ID][7], "Y");
						}
					}
					printf("Would you like to continue to edit this students' details? Type 1 to continue. Any other value to exit.");
					scanf("%d", &loop3);
					rewind(stdin);
				}
				}
			break;
		case 3:
			while (loop4 == 1) {
				printf("Enter student ID:");
				scanf("%9s", IDcheck);
				rewind(stdin);
				for (ID = 0; ID < sizeof(studentDetails) / sizeof(studentDetails[0]);ID++) {
					if (strcmp(studentDetails[ID][0], IDcheck) == 0) {
						loop4 = 0;
						break;
					}
				}//verify ID
			}//enter ID and check if id is available
			if (ID == sizeof(studentDetails) / sizeof(studentDetails[0])) { printf("Record not found!"); }//runs if id is unavailable
			else {
				system("cls");
				printf("Name:%s\n", studentDetails[ID][1]);
				if (strcmp(studentDetails[ID][5], "Y") == 0)//semester 1
					printf("Semester 1 start: %s %s\nSemester 1 end: %s %s\n", studSem1Sub[ID][6], studSem1Sub[ID][7], studSem1Sub[ID][8], studSem1Sub[ID][9]);
				else printf("Semester 1 start: No record!\nSemester 1 end: No record!\n");
				printf("Semester 1 subjects taken: ");
				if (strcmp(studentDetails[ID][2], "Y") == 0) {
					for (i = 0;i < studSem1GPA[ID][14];i++) printf("\n%s GPA:%.2f", studSem1Sub[ID][i],studSem1GPA[ID][i]);
					printf("\nNumber of subjects: %.0f\nTotal credit hours: %.0f\nCGPA: %.2f\n", studSem1GPA[ID][14], studSem1GPA[ID][12], studSem1GPA[ID][13]);
					wcgpa += studSem1GPA[ID][13]*studSem1GPA[ID][12];
					totalcred += studSem1GPA[ID][12];
					printf("\n");
				}
				else printf("No record found!\n");
				if (strcmp(studentDetails[ID][6], "Y") == 0)//semester 2
					printf("Semester 2 start: %s %s\nSemester 2 end: %s %s\n", studSem2Sub[ID][6], studSem2Sub[ID][7], studSem2Sub[ID][8], studSem2Sub[ID][9]);
				else printf("Semester 2 start: No record!\nSemester 2 end: No record!\n");
				printf("Semester 2 subjects taken: ");
				if (strcmp(studentDetails[ID][3], "Y") == 0) {
					for (i = 0;i <studSem2GPA[ID][14];i++) printf("\n%s GPA:%.2f", studSem2Sub[ID][i], studSem2GPA[ID][i]);
					printf("\nNumber of subjects: %.0f\nTotal credit hours: %.0f\nCGPA: %.2f\n", studSem2GPA[ID][14], studSem2GPA[ID][12], studSem2GPA[ID][13]);
					wcgpa += studSem2GPA[ID][13]* studSem2GPA[ID][12];
					totalcred += studSem2GPA[ID][12];
					printf("\n");
				}
				else printf("No record found!\n");
				if (strcmp(studentDetails[ID][7], "Y") == 0)//semester 3
					printf("Semester 3 start: %s %s\nSemester 3 end: %s %s\n", studSem3Sub[ID][6], studSem3Sub[ID][7], studSem3Sub[ID][8], studSem3Sub[ID][9]);
				else printf("Semester 3 start: No record!\nSemester 3 end: No record!\n");
				printf("Semester 2 subjects taken: ");
				if (strcmp(studentDetails[ID][4], "Y") == 0) {
					for (i = 0;i <studSem3GPA[ID][14];i++) printf("\n%s GPA:%.2f", studSem3Sub[ID][i], studSem3GPA[ID][i]);
					printf("\nNumber of subjects: %.0f\nTotal credit hours: %.0f\nCGPA: %.2f\n", studSem3GPA[ID][14], studSem3GPA[ID][12], studSem3GPA[ID][13]);
					wcgpa += studSem3GPA[ID][13]* studSem3GPA[ID][12];
					totalcred += studSem3GPA[ID][12];
					printf("\n");
				}
				else printf("No record found!\n");
				if(totalcred!=0)totalcgpa = wcgpa / totalcred;
				printf("\nCGPA across 3 semesters:%.2f\n", totalcgpa);
				break;
			}
		}
	}
}
void studentMenu() {
	int ID, loop = 1, i;
	char IDcheck[10];
	float wcgpa = 0, totalcred = 0, totalcgpa = 0;
	system("cls");
	while(loop==1){
	printf("Enter student ID:");//enter ID and check if id is available
	scanf("%9s", IDcheck);
	rewind(stdin);
	for (ID = 0; ID < sizeof(studentDetails) / sizeof(studentDetails[0]);ID++) {
		if (strcmp(studentDetails[ID][0], IDcheck) == 0) {
			loop = 0;
			break;
		}
	}//verify ID
	if (ID == sizeof(studentDetails) / sizeof(studentDetails[0])) { printf("Record not found!"); }//runs if id is unavailable
	else {
		printf("Name:%s\n", studentDetails[ID][1]);
		if (strcmp(studentDetails[ID][5], "Y") == 0)//semester 1
			printf("Semester 1 start: %s %s\nSemester 1 end: %s %s\n", studSem1Sub[ID][6], studSem1Sub[ID][7], studSem1Sub[ID][8], studSem1Sub[ID][9]);
		else printf("Semester 1 start: No record!\nSemester 1 end: No record!\n");
		printf("Semester 1 subjects taken: ");
		if (strcmp(studentDetails[ID][2], "Y") == 0) {
			for (i = 0;i < studSem1GPA[ID][14];i++) printf("\n%s GPA:%.2f", studSem1Sub[ID][i], studSem1GPA[ID][i]);
			printf("\nNumber of subjects: %.0f\nTotal credit hours: %.0f\nCGPA: %.2f\n", studSem1GPA[ID][14], studSem1GPA[ID][12], studSem1GPA[ID][13]);
			wcgpa += studSem1GPA[ID][13] * studSem1GPA[ID][12];
			totalcred += studSem1GPA[ID][12];
			printf("\n");
		}
		else printf("No record found!");
		if (strcmp(studentDetails[ID][6], "Y") == 0)//semester 2
			printf("Semester 2 start: %s %s\nSemester 2 end: %s %s\n", studSem2Sub[ID][6], studSem2Sub[ID][7], studSem2Sub[ID][8], studSem2Sub[ID][9]);
		else printf("Semester 2 start: No record!\nSemester 2 end: No record!\n");
		printf("Semester 2 subjects taken: ");
		if (strcmp(studentDetails[ID][3], "Y") == 0) {
			for (i = 0;i < studSem2GPA[ID][14];i++) printf("\n%s GPA:%.2f", studSem2Sub[ID][i], studSem2GPA[ID][i]);
			printf("\nNumber of subjects: %.0f\nTotal credit hours: %.0f\nCGPA: %.2f\n", studSem2GPA[ID][14], studSem2GPA[ID][12], studSem2GPA[ID][13]);
			wcgpa += studSem2GPA[ID][13] * studSem2GPA[ID][12];
			totalcred += studSem2GPA[ID][12];
			printf("\n");
		}
		else printf("No record found!");
		if (strcmp(studentDetails[ID][7], "Y") == 0)//semester 3
			printf("Semester 3 start: %s %s\nSemester 3 end: %s %s\n", studSem3Sub[ID][6], studSem3Sub[ID][7], studSem3Sub[ID][8], studSem3Sub[ID][9]);
		else printf("Semester 3 start: No record!\nSemester 3 end: No record!\n");
		printf("Semester 2 subjects taken: ");
		if (strcmp(studentDetails[ID][4], "Y") == 0) {
			for (i = 0;i <studSem3GPA[ID][14];i++) printf("\n%s GPA:%.2f", studSem3Sub[ID][i], studSem3GPA[ID][i]);
			printf("\nNumber of subjects: %.0f\nTotal credit hours: %.0f\nCGPA: %.2f\n", studSem3GPA[ID][14], studSem3GPA[ID][12], studSem3GPA[ID][13]);
			wcgpa += studSem3GPA[ID][13] * studSem3GPA[ID][12];
			totalcred += studSem3GPA[ID][12];
			printf("\n");
		}
		else printf("No record found!");
		if (totalcred != 0)totalcgpa = wcgpa / totalcred;
		else totalcgpa = 0;
		printf("\nCGPA across 3 semesters:%.2f\n", totalcgpa);
	}
}
int calcCGPA(sem,sub,ID) {
	int i;
	float cred=0,wgpa=0;
	switch (sem) {
		case 1:
			for (i = 0;i < sub;i++) {
				cred += studSem1GPA[ID][i+6];
				wgpa += studSem1GPA[ID][i] * studSem1GPA[ID][i + 6];
			}
			studSem1GPA[ID][13] = wgpa / cred;
		case 2:
			for (i = 0;i < sub;i++) {
				cred += studSem2GPA[ID][i + 6];
				wgpa += studSem2GPA[ID][i] * studSem2GPA[ID][i + 6];
			}
			studSem2GPA[ID][13] = wgpa / cred;
		case 3:
			for (i = 0;i < sub;i++) {
				cred += studSem3GPA[ID][i + 6];
				wgpa += studSem3GPA[ID][i] * studSem3GPA[ID][i + 6];
			}
			studSem3GPA[ID][13] = wgpa / cred;
	}
}
void targetCalc() {
	printf("\nThis area is off limits!\n");
}
void main(){
	int loop =1,studLoop=1;
	while (loop ==1) {
		attempt = 1;
		menu();
		if (menuSelect == 1) {
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
				if(pass1 == 1 && pass2 == 1) { adminMenu();}//if admin password and id is correct
			}
			if (loginSelect == 2) {//student details selected
				while (studLoop ==1) {
					studentMenu();
					printf("Do you want to continue to view student details? Enter 1 to continue.");
					if (scanf("%d", &studLoop) == 0)studLoop = 0;//runs if user inputs non-int value, regards it as exit loop
					rewind(stdin);
				}
			}
		}
		else if (menuSelect == 2) { targetCalc(); }
		printf("\nWould you like to continue? Type 1 to continue; any other value to exit.\n");
		if (scanf("%d", &loop) == 0)loop = 0;//runs if user inputs non-int value, regards it as exit loop;
		rewind(stdin);
		system("cls");//clears console
	}
}
