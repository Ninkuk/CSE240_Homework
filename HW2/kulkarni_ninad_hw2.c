/*
Author: Ninad Kulkarni
Date: 6/7/2020
Description: TODO
*/

#include <stdio.h>

// Forward Declaration Functions
int commandLineArgsCheck(int);
void printMenu();
void miniGames(int, char**);
void throwDown();

int main(int argc, char** argv)
{	
	if(commandLineArgsCheck(argc)) return -1;
		
	printMenu();
	int selectedOption = 0;
	int successCode = 0;
	do
	{
		successCode = scanf("%d", &selectedOption);
		if (successCode == 0 || selectedOption > 2)
		{
			while ((getchar()) != '\n');
			printf("\n**Sorry, please enter a valid option**\n\n");
			printMenu();
		}
	} while(successCode == 0 || selectedOption > 2);

	switch(selectedOption)
	{
		case 1:
			miniGames(argc, argv);
			break;
		case 2:
			//throwDown();
			break;
		case 0:
			printf("Thank you for playing. Come back again!");
			return 0;
	}
}

void printMenu()
{
	printf("Welcome to the CSE240 Assignment 2!\n");
	printf("Menu:\n");
	printf("1 - CSE240 Mini-Game Collection\n");
	printf("2 - Macros vs Functions Throw-down\n");
	printf("0 - Exit\n");
	printf("Choose an option: ");
}

void miniGames(int argc, char** argv)
{	
	char name[10];
	if (argc > 0) {
		
	}	
	//TODO create opponent
	//generate random num between 0 and number of names in file
	//read name from file IO
}









int commandLineArgsCheck(int argc)
{
	if (argc == 2) {
		printf("Insufficient amount of arguments provided: %d\n", argc);
		return 1;
	} else if(argc > 3) {
		printf("Too many arguments provided: %d\n", argc);
		return 1;
	}

	return 0;
}
