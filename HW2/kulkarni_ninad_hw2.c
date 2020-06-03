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
void miniGames(int, char **);
void throwDown();
int RandomInRange(int, int);
int evensOrOdds(char[]);
int isEven(int);
int rockPaperScissors(char[]);
int guessTheNumber(char[]);
int diceRollShowdown(char[]);
int RollDie(int);

int main(int argc, char **argv)
{
	if (commandLineArgsCheck(argc))
		return -1;

	printMenu();
	int selectedOption = 0;
	int successCode = 0;
	do
	{
		successCode = scanf("%d", &selectedOption);
		if (successCode == 0 || selectedOption > 2)
		{
			while ((getchar()) != '\n')
				;
			printf("\n**Sorry, please enter a valid option**\n\n");
			printMenu();
		}
	} while (successCode == 0 || selectedOption > 2);

	switch (selectedOption)
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
	default:
		break;
	}
}

void miniGames(int argc, char **argv)
{

	// File I/O to generate random opponent
	FILE *randomNamesFile;
	srand(time(0));
	int randomNum;

	// Control structure to open file and generate random number based on Command Line Argument
	if (argc > 1)
	{
		randomNamesFile = fopen(argv[1], "r");
		printf("%d", (int)argv[2]);
		randomNum = rand() % (int)argv[2];
	}
	else
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

	int rounds = 0;
	int successCode = 0;
	do
	{
		successCode = scanf("%d", &rounds);
		if (successCode == 0 || rounds % 2 == 0 || rounds < 0)
		{
			while ((getchar()) != '\n')
				continue;
			printf("\n**Sorry, please enter an odd number**\n\n");
		}
	} while (successCode == 0 || rounds % 2 == 0 || rounds < 0);
}

int RandomInRange(int min, int max)
{
	int range = max - min + 1;
	return ((rand() % range) + min);
}

int evensOrOdds(char name[])
{
	printf("Even/Odd game!\n");
	printf("Guess even or odd! (0 for even, 1 for odd):	");

	int guess = 0;
	int successCode = 0;
	do
	{
		successCode = scanf("%d", &guess);
		if (successCode == 0 || guess > 1 || guess < 0)
		{
			while ((getchar()) != '\n')
				continue;
			printf("\n**Sorry, please guess even or odd! (0 for even, 1 for odd):	**");
		}
	} while (successCode == 0 || guess > 1 || guess < 0);

	printf("Enter a number (between 0 and 100):	");
	int playerNumber = 0;
	do
	{
		successCode = scanf("%d", &playerNumber);
		if (successCode == 0 || playerNumber > 100 || playerNumber < 0)
		{
			while ((getchar()) != '\n')
				continue;
			printf("\n**Sorry, please enter a number (between 0 and 100):	**");
		}
	} while (successCode == 0 || playerNumber > 100 || playerNumber < 0);

	int computerNumber = RandomInRange(0, 100);
	printf("%s picked %d", name, computerNumber);

	int sumOfNumbers = playerNumber + computerNumber;
	char result[5];
	int pointsEarned;
	if (isEven(sumOfNumbers))
	{
		result = "EVEN";
		pointsEarned = 1;
	}
	else
	{
		result = "ODD";
		pointsEarned = 0;
	}

	printf("%d + %d = %d - %s!", playerNumber, computerNumber, sumOfNumbers, result);

	if (guess != isEven(sumOfNumbers))
	{
		printf("You win the round!\n")
	}
	else
	{
		printf("%s wins the round!\n", name);
	}

	return pointsEarned;
}

int isEven(int number)
{
	return (number % 2 == 0) ? 1 : 0;
}

int rockPaperScissors(char name[])
{
	printf("Rock, Paper, Scissors game!\nChoose a throw!\n1. Rock\n2. Paper\n3. Scissors\n");
	int playerThrow = 0;
	int successCode = 0;
	do
	{
		successCode = scanf("%d", &playerThrow);
		if (successCode == 0 || playerThrow > 3 || playerThrow < 1)
		{
			while ((getchar()) != '\n')
				continue;
			printf("\n**Sorry, please throw a valid sign (1. Rock, 2. Paper, 3. Scissors):	**");
		}
	} while (successCode == 0 || playerThrow > 1 || playerThrow < 0);

	int opponentThrow = RandomInRange(1, 3);

	int result;

	switch (playerThrow)
	{
	case 1:
		// Rock

		break;

	default:
		break;
	}
}

int guessTheNumber(char name[])
{
	printf("Number Guessing game!\n");

	int minValue = RandomInRange(0, 500);
	int range = RandomInRange(30, 100);
	int maxValue = minValue + range;
	int mysteryNumber = RandomInRange(minValue, maxValue);

	printf("I'm thinking of a number between %d and %d!", minValue, maxValue);
	int guessesLeft = 5;
	printf("You have %d guesses", guessesLeft);
	while (guessesLeft > 0)
	{
		printf("What's guess #%d?	");

		int playerGuess = 0;
		int successCode = 0;
		do
		{
			successCode = scanf("%d", &playerGuess);
			if (successCode)
			{
				while ((getchar()) != '\n')
					continue;
				printf("\n**Sorry, please enter a number:	**");
			}
		} while (successCode);

		if (playerGuess > mysteryNumber)
		{
			printf("My number is lower!");
		}
		else if (playerGuess < mysteryNumber)
		{
			printf("My number is higher!");
		}
		else
		{
			printf("You guessed it! The mystery number was: %d", mysteryNumber);
			return 1;
		}
	}

	return 0;
}

int diceRollShowdown(char[] name)
{
	printf("Number Guessing game!\n");

	printf("How many sides do the dice have (input a positive number):	");
	int numberOfSides = 0;
	int successCode = 0;
	do
	{
		successCode = scanf("%d", &numberOfSides);
		if (successCode == 0 || numberOfSides > 0)
		{
			while ((getchar()) != '\n')
				continue;
			printf("\n**Sorry, please enter a positive number:	**");
		}
	} while (successCode == 0 || numberOfSides > 0);

	printf("How many dice will each player roll?	");
	int numberOfDice = 0;
	do
	{
		successCode = scanf("%d", &numberOfDice);
		if (successCode == 0 || numberOfDice > 0)
		{
			while ((getchar()) != '\n')
				continue;
			printf("\n**Sorry, please enter a positive number:	**");
		}
	} while (successCode == 0 || numberOfDice > 0);

	printf("Player Rolled:\n");
	int rollDie = 0;
	int playerDieTotal = 0;
	while (rollDie > numberOfDie)
	{
		int dieValue = RollDie(numberOfSides);
		printf("%d\n", dieValue);

		dieTotal += dieValue;
		rollDie++;
	}

	printf("Total: %d", playerDieTotal);

	printf("%s Rolled:\n", name);
	rollDie = 0;
	int opponentDieTotal = 0;
	while (rollDie > numberOfDie)
	{
		int dieValue = RollDie(numberOfSides);
		printf("%d\n", dieValue);

		opponentDieTotal += dieValue;
		rollDie++;
	}

	printf("Total: %d", opponentDieTotal);

	return ((playerDieTotal > opponentDieTotal) ? 1 : 0);
}

int RollDie(int sides)
{
	return RandomInRange(1, sides);
}

int commandLineArgsCheck(int argc)
{
	if (argc == 2)
	{
		printf("Insufficient amount of arguments provided: %d\n", argc);
		return 1;
	}
	else if (argc > 3)
	{
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
