#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#pragma warning (disable:4996)
int menuSelect,loginSelect,pass1=0,pass2;
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
	while (menuSelect < 1 || menuSelect>2) {
		printf("Enter 1 or 2 only!\n");
		scanf("%d", &menuSelect);
	}
	return menuSelect;
}
int getID() {
	char loginID[255];
	printf("Enter login credentials\nStaff ID:");
	scanf("%s", loginID);
	FILE* file = fopen("Text.txt", "r");
	char IDcheck[10];
	while (fgets(IDcheck, sizeof(IDcheck), file)) {
		if (strcmp(loginID,IDcheck)==0) {
			printf("Logged in successfully.");
			pass1 = 1;//is a global variable set to 0;allows the loop to exit
			break;
		}
	}
	return pass1;
}
void main() {
	int loop = 1;
	while (loop == 1) {
		menu();
		if (menuSelect == 1) {
			while (pass1==0){ getID(); }
		}
		else if (menuSelect==2){}
		printf("\nWould you like to continue? Type 1 to continue; any other value to exit.\n");
		scanf("%d", &loop);
	}
}