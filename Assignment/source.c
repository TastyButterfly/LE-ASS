#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#pragma warning (disable:4996)
int menuSelect,loginSelect,pass1=0,pass2=0,line,linecheck;
char staffID[10], staffPW[20];
int menu() {
	for (int i = 0; i < 50; i++) {
		putchar('=');
	}
	printf("\n%27s\n","MENU");
	for (int i = 0; i < 50; i++) {
		putchar('=');
	}
	printf("\n1.Administrator Login\n2.Student Login\n");
	scanf("%d", &menuSelect);
	while (scanf("%d", &menuSelect)!=1 && scanf("%d", &menuSelect)!=2) {
		printf("Enter 1 or 2 only!\n");
		scanf("%d", &menuSelect);
		rewind(stdin);
	}
	return menuSelect;
}
int getAID() {
	char loginID[255];
	printf("Enter login credentials\nStaff ID:");
	scanf("%s", loginID);
	rewind(stdin);
	FILE* file1 = fopen("AID.txt", "r");
	char IDcheck[10];
	while (fgets(IDcheck, sizeof(IDcheck), file1)) {
		if (strcmp(loginID, IDcheck) == 0) {
			printf("Logged in successfully.\n");
			pass1 = 1;//is a global variable set to 0;allows the loop to exit
			fclose(file1);
			break;
		}
		else { line++; }
	}
	return pass1,line;
}
int getAPW(line){
	char PINcheck[7];
	char PIN[7];
	printf("PIN:");
	scanf("%s", PIN);
	rewind(stdin);
	FILE* file2 = fopen("APIN.txt", "r");
	while (fgets(PINcheck,sizeof(PINcheck), file2)) {
		if (linecheck==line){
			if (strcmp(PIN, PINcheck) == 0) {
				printf("Welcome.");
				pass2 = 1;//is a global variable set to 0;allows the loop to exit
				fclose(file2);
				break;
			}
		}
		else { linecheck++; }
	}
	return pass2;
}
void main() {
	int loop = 1;
	while (loop == 1) {
		menu();
		if (menuSelect == 1) {
			pass1 = 0, pass2 = 0;
			while (pass1 == 0) { line = 0;getAID(); }
			while (pass1 == 1 && pass2 == 0) { linecheck = 0;getAPW(line); }
			while (pass1 == 1 && pass2 == 1) { AdminMenu(); }
		}
		if (menuSelect == 2) {}
		printf("\nWould you like to continue? Type 1 to continue; any other value to exit.\n");
		scanf("%d", &loop);
	}
}