/*
Author: Ninad Kulkarni
Date: 6/7/2020
Description: TODO
*/

#include <stdio.h>

// Forward Declaration Functions
void printMenu();

int main(int argc, char** argv)
{
	printMenu();
	int selectedOption = 0;
	int successCode = 0;
	do
	{
		successCode = scanf("%d", &selectedOption);
		if (successCode == 0 || selectedOption > 2)
		{
			while ((getchar()) != '\n');
			printf("\nSorry, please enter a valid option\n\n");
			printMenu();
		}
	} while(successCode == 0 || selectedOption > 2);
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
