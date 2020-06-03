/*
Author: Ninad Kulkarni
Date: 6/7/2020
Description: TODO
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

void miniGames(int argc, char** argv)
{	

	// File I/O to generate random opponent
	FILE* randomNamesFile;
	srand(time(0));
	int randomNum;

	// Control structure to open file and generate random number based on Command Line Argument
	if (argc > 1)
	{
		randomNamesFile = fopen(argv[1], "r");
		printf("%d", (int)argv[2]);
		randomNum = rand() % (int)argv[2];
	} else
	{
		randomNamesFile = fopen("random_names.txt", "r");
		randomNum = rand() % 100;
	}

	// If the custom file doesn't open, the default random_names.txt file is opened
	if (randomNamesFile == NULL)
	{
		printf("Invalid file name provided. Using default text file: 'random_names.txt'");
		randomNamesFile = fopen("random_names.txt", "r");
	}

	// read names from file. skips names till the random number is reached and assigns it to name var.
	char name[30];
	int i;
	for (i = 0; i < randomNum; i++)
	{
		fscanf(randomNamesFile, "%s", name);
	}

	// close file after generating random opponent
	fclose(randomNamesFile);

	printf("Welcome to CSE240 Mini-Game Collection!\nI am your opponent %s\n", name);
	printf("How many rounds should we play? (Choose an odd number)	");
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

void printMenu()
{
	printf("Welcome to the CSE240 Assignment 2!\n");
	printf("Menu:\n");
	printf("1 - CSE240 Mini-Game Collection\n");
	printf("2 - Macros vs Functions Throw-down\n");
	printf("0 - Exit\n");
	printf("Choose an option: ");
}
