#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#pragma warning (disable:4996)
int menuSelect,loginSelect,pass1,pass2,pass3,accID,linecheck,SIDline;
char staffID[10], staffPW[20],PIN[255];
char* PINcheck[] = {"234567","123456","234565"};
int menu() {
	for (int i = 0; i < 50; i++) {
		putchar('=');
	}
	printf("\n%27s\n","MENU");
	for (int i = 0; i < 50; i++) {
		putchar('=');
	}
	printf("\n1.CGPA System\n2.CGPA Target Calculator\n");
	while (scanf("%d", &menuSelect)!=1 ||(menuSelect!=2 && menuSelect!=1)) {
		rewind(stdin);
		printf("Enter 1 or 2 only!\n");
	}
	return menuSelect;
}
int getAID() {
	char AID[255], c, IDcheck[10];
	printf("Enter login credentials\nAdmin ID:");
	scanf("%s", AID);
	rewind(stdin);
	FILE* file1 = fopen("AID.txt", "r");
	rewind(file1);
	while (fgets(IDcheck, sizeof(IDcheck), file1)) {
		if (strcmp(AID, IDcheck) == 0) {
			accID/=2;
			printf("Logged in successfully.\n");
			pass1 = 1;//is a global variable set to 0;allows the loop to exit
			fclose(file1);	
		}
		else {accID++;}
	}
	return pass1,accID;
}
int getSID(){
	char SID[255],c,IDcheck[10];
	printf("Enter login credentials\nStudent ID:");
	scanf("%s",SID);
	rewind(stdin);
	FILE *file2 = fopen("SID.txt","r");
	for (c = getc(file2);c != EOF; c = getc(file2)) {
		if (c == '\n') // Increment count if this character is newline
			SIDline++;
	}
	rewind(file2);
	while (fgets(IDcheck, sizeof(IDcheck), file2)) {
		if (strcmp(SID,IDcheck)==0) {
			printf("Logged in successfully.\n");
			pass3 = 1;//is a global variable set to 0;allows the loop to exit
			fclose(file2);
			break;
		}
	}
	return pass3;
}
int login() {
	for (int i = 0; i < 50; i++) {
		putchar('=');
	}
	printf("\n%26s\n", "LOGIN");
	for (int i = 0; i < 50; i++) {
		putchar('=');
	}
	printf("\n1.Administrator Login\n2.Student Login\n");
	while (scanf("%d", &loginSelect) != 1 || (loginSelect != 2 && loginSelect != 1)) {
		rewind(stdin);
		printf("Enter 1 or 2 only!\n");
	}
	return loginSelect;
}
int getPW(accID) {
	printf("Enter PIN:");
	scanf("%s", PIN);
	if (strcmp(PIN,PINcheck[accID])==0) {
		rewind(stdin);
		printf("Access granted\n");
		pass2 = 1;
	}
	else {printf("Wrong password\n");}
	return pass2;
}
void main() {
	int loop = 1;
	while (loop == 1) {
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
					getPW(accID);
				}
				while (pass1 == 1 && pass2 == 1) { printf("test");break; }
			}
			if (loginSelect == 2) {
				pass3 = 0;
				while (pass3 == 0) {
					SIDline = 1;
					getSID();
				}
			}
		}
		else if (menuSelect==2){}
		printf("\nWould you like to continue? Type 1 to continue; any other value to exit.\n");
		scanf("%d", &loop);
		system("cls");//clears console
	}
}