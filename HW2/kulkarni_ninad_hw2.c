/*
* Author: Ninad Kulkarni
* Date: 6/7/2020
* Description: TODO
*/

// included libraries
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Forward Declaration Functions
int commandLineArgsCheck(int);
void gameMenu(int, char **);
int inputHandling(int, char[]);
int inputHandlingUpperBound(int, int, char[]);
void miniGames(int, char **);
void throwDown();
int RandomInRange(int, int);
int evensOrOdds(char[]);
int isEven(int);
int rockPaperScissors();
int guessTheNumber();
int diceRollShowdown(char[]);
int RollDie(int);

int main(int argc, char **argv)
{
	// Checks the validity of the command line arguments
	if (!commandLineArgsCheck(argc))
		return 0; // return 0 for unsafe exit

	gameMenu(argc, argv);
}

/*
* Purpose: Exception handling for command line arguments
* Parameter:
*	argc: the number of arguments passes by command line
* Return:
*	0: failure
*	1: success
*/
int commandLineArgsCheck(int argc)
{
	// The number of arguments should either be 0 (default behavior) or 3 (custom name file)
	if (argc == 2)
	{
		printf("Insufficient amount of arguments provided: %d\n", argc);
		printf("Required format: ./source [file-name] [# of lines/names]");
		return 0;
	}
	else if (argc > 3)
	{
		printf("Too many arguments provided: %d\n", argc);
		printf("Required format: ./source [file-name] [# of lines/names]");
		return 0;
	}

	// Returns 1 if neither control structures are triggered
	return 1;
}

/*
* Purpose: This function displays the game menua and proceeds to the appropriate functions.
*          This is a separate function from main because it can be called again by the user after finishing game.
* Parameters: The commandline arguemnts don't serve any purpose other than to pass it over to miniGames()
*/
void gameMenu(int argc, char **argv)
{
	printf("\nWelcome to the CSE240 Assignment 2!\nMenu:\n1 - CSE240 Mini-Game Collection\n2 - Macros vs Functions Throw-down\n0 - Exit\nChoose an option: ");

	int selectedMenuOption = inputHandlingUpperBound(2, 0, "Please enter a valid option: ");

	switch (selectedMenuOption)
	{
	case 1:
		miniGames(argc, argv);
		break;
	case 2:
		throwDown();
		break;
	case 0:
		printf("Thank you for playing. Come back again!");
		break;
	default:
		break;
	}
}

/*
* Purpose: Initialize the mini games components. First, this function does File I/O based on command line arguements and creates an opponent.
* Parameter:
*	argc: the number of arguments passes by command line
*	argv: command line arguments
*/
void miniGames(int argc, char **argv)
{

	// File I/O to generate random opponent
	FILE *randomNamesFile;
	srand(time(0)); // Seed the random number generator
	int randomNum;

	/* 
		Generates a random number based on if the user passed in a custom file in the command line arguments.
		If no custom file is provided then default random_names.txt is used.
	*/
	if (argc > 1)
	{
		randomNamesFile = fopen(argv[1], "r");
		randomNum = RandomInRange(0, atoi(argv[2]));
	}
	else
	{
		randomNamesFile = fopen("random_names.txt", "r");
		randomNum = RandomInRange(0, 99);
	}

	// If the custom file doesn't open, the default random_names.txt file is used
	if (randomNamesFile == NULL)
	{
		printf("Invalid file name provided. Using default text file: 'random_names.txt'");
		randomNamesFile = fopen("random_names.txt", "r");
	}

	// read names from file. skips names till the random number is reached and assigns it to name var.
	char opponentName[30];
	int i;
	for (i = 0; i < randomNum; i++)
	{
		fscanf(randomNamesFile, "%s", opponentName);
	}

	// close file after generating random opponent
	fclose(randomNamesFile);

	printf("\nWelcome to CSE240 Mini-Game Collection!\nI am your opponent %s.\n", opponentName);
	printf("\nHow many rounds should we play? (Choose an odd number)  ");

	int totalRounds = 0;
	int successCode = 0; // 0 = invalid input, 1 = valid input
	do
	{
		successCode = scanf("%d", &totalRounds);
		if (successCode == 0 || isEven(totalRounds))
		{
			while ((getchar()) != '\n')
				continue;
			printf("\nPlease enter an odd number: ");
		}
	} while (successCode == 0 || isEven(totalRounds));

	int currentRound = 0;
	int playerScore = 0;
	int opponentScore = 0;

	int victory = (totalRounds + 1) / 2;

	while (currentRound < totalRounds)
	{
		int turnGame = RandomInRange(0, 3);
		int turnResult;
		turnGame = 0;
		switch (turnGame)
		{
		case 0:
			turnResult = evensOrOdds(opponentName);
			break;
		case 1:
			turnResult = rockPaperScissors();
			break;
		case 2:
			turnResult = guessTheNumber();
			break;
		case 3:
			turnResult = diceRollShowdown(opponentName);
		default:
			break;
		}

		if (turnResult)
		{
			playerScore++;
			printf("\nYou win this round!\n");
		}
		else
		{
			opponentScore++;
			printf("\n%s wins this round!\n", opponentName);
		}

		printf("\nThe score is:\n  Player: %d\n  %s: %d\n", playerScore, opponentName, opponentScore);

		if (playerScore == victory || opponentScore == victory)
			break;

		currentRound++;
	}

	if (playerScore > opponentScore)
	{
		printf("\n\nCongratulations! You win the game in %d rounds with a score of %d-%d", currentRound, playerScore, opponentScore);
	}
	else
	{
		printf("Alas! You lost this round with a score of %d-%d", playerScore, opponentScore);
	}

	printf("\nWould you like to continue playing? (0 for no, 1 for yes)  ");
	(inputHandlingUpperBound(1, 0, "Please enter a valid response (0 for no, 1 for yes):  ")) ? miniGames(argc, argv) : gameMenu(argc, argv);
}

/*
* Purpose: Generate a random number between min and max values **INCLUSIVE**
*/
int RandomInRange(int min, int max)
{
	int range = max - min + 1;		 //This makes the max value inclusive
	return ((rand() % range) + min); // generates a number between 0-range and then is added by min to
}

/*
* Purpose: Play the Evens or Odds game. This function first asks the user to guess the parity and then a number between 0 and 100.
*          Then generates a random number and adds the two numbers. After determining the parity of the sum, declares the winner.
* Return (pointsEarned): Values act as both a result and score.
*	0: Player loses and gets 0 points.
*	1: Player wins and gets 1 point.
*/
int evensOrOdds(char opponentName[])
{
	// Gets the player choice of even or odd
	printf("\n\nEven/Odd game!\nGuess even or odd! (0 for even, 1 for odd):  ");
	int playerGuess = inputHandlingUpperBound(1, 0, "Please guess even or odd (0 for even, 1 for odd):  ");

	// Gets the player's number
	printf("Enter a number (between 0 and 100):  ");
	int playerNumber = inputHandlingUpperBound(100, 0, "Please enter a number (between 0 and 100):  ");

	// Generate opponent's number randomly
	int opponentNumber = RandomInRange(0, 100);
	printf("%s picked %d", opponentName, opponentNumber);

	// Sum of both numbers
	int sumOfNumbers = playerNumber + opponentNumber;

	char *resultParity = isEven(sumOfNumbers) ? "EVEN" : "ODD";

	printf("\n\n%d + %d = %d - %s!", playerNumber, opponentNumber, sumOfNumbers, resultParity);

	int pointsEarned = (playerGuess != isEven(sumOfNumbers)) ? 1 : 0;
	return pointsEarned;
}

/*
* Purpose: To determine the parity(# is even or not) of the number provided.
* Return:
*	0: Odd (not even)
*	1: Even
*/
int isEven(int number)
{
	return (number % 2 == 0) ? 1 : 0;
}

/*
* Purpose: Play the game of Rock, Paper, Scissors. First asks the user to enter their sign and then generates a random sign.
*          Then checks if the player won or not and if there is a draw, the functions calls itself again recursively.
* Return (pointsEarned): Values act as both a result and score.
*	0: Player loses and gets 0 points.
*	1: Player wins and gets 1 point.
*/
int rockPaperScissors()
{
	printf("\n\nRock, Paper, Scissors game!\nChoose a throw!\n1. Rock\n2. Paper\n3. Scissors\n");

	int playerThrow = inputHandlingUpperBound(3, 1, "Please throw a valid sign (1. Rock, 2. Paper, 3. Scissors):  ");
	int opponentThrow = RandomInRange(1, 3);

	int pointsEarned = 0;

	if ((playerThrow + 1) % 3 == opponentThrow)
	{
		pointsEarned = 0;
	}
	else if (playerThrow == opponentThrow)
	{
		printf("Oh no, that was a draw, Let's play again!");
		pointsEarned = rockPaperScissors();
	}
	else
	{
		pointsEarned = 1;
	}

	return pointsEarned;
}

/*
* Purpose: Play the game of I’m thinking of a number between ... First generates a random range and a random mystery number. Then creates a counter of 5 and uses a loop to 
* Return: Values act as both a result and score.
*	0: Player loses and gets 0 points.
*	1: Player wins and gets 1 point.
*/
int guessTheNumber()
{
	printf("\n\nNumber Guessing game!\n");

	// To ensure a unique experience everytime, I made the range and min/max bounds of mystery numbers dynamically random too.
	int minValue = RandomInRange(0, 500);
	int range = RandomInRange(30, 100);
	int maxValue = minValue + range;
	int mysteryNumber = RandomInRange(minValue, maxValue);

	printf("I'm thinking of a number between %d and %d!\n", minValue, maxValue);

	int currentGuess = 1;
	printf("You have 5 guesses\n");

	while (currentGuess < 6)
	{
		printf("\nWhat's guess #%d?", currentGuess);

		int playerGuess = inputHandlingUpperBound(maxValue, minValue, "Sorry, please enter a number in the given range: ");

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

		currentGuess++;
	}

	// If the functions hasn't already been terminated yet then that means player ran out of tries and didn't guess the number
	printf("Sorry you ran out of guesses!");
	return 0;
}

/*
* Purpose: Play the game of Dice Roll Showdown. First asks the user for number of sides that the dice should have and how many die should be thrown.
*          Then it uses a loop and generates random values for the set number of dice. Finally, the score is calculated and player with highest score wins.
* Return: Values act as both a result and score.
*	0: Player loses and gets 0 points.
*	1: Player wins and gets 1 point.
*/
int diceRollShowdown(char opponentName[])
{
	// Displays the name of the game
	printf("\n\nDice Roll Showdown!\n");
	printf("How many sides do the dice have (input a positive number):  ");

	// Hypothetically a dice does not have a limit on number of sides and can even be a sphere.
	int numberOfSides = inputHandling(1, "Please enter a positive number of sides:  ");

	printf("How many dice will each player roll?	");
	int numberOfDice = inputHandling(1, "Please enter a positive number of die to roll:  ");

	printf("Player Rolled:\n");
	int rollDie = 0; // counter that is incremented until set number of die are rolled
	int playerDieTotal = 0;
	while (rollDie < numberOfDice)
	{
		int dieValue = RollDie(numberOfSides);
		printf("%d\n", dieValue);

		playerDieTotal += dieValue; // player total is incremented after each roll
		rollDie++;
	}

	printf("Total: %d", playerDieTotal);

	printf("%s Rolled:\n", opponentName);
	rollDie = 0; // the counter is reset after player's turn
	int opponentDieTotal = 0;
	while (rollDie < numberOfDice)
	{
		int dieValue = RollDie(numberOfSides);
		printf("%d\n", dieValue);

		opponentDieTotal += dieValue;
		rollDie++;
	}

	printf("Total: %d", opponentDieTotal);

	// returns the value 1 if player won and 0 if they lost.
	return ((playerDieTotal > opponentDieTotal) ? 1 : 0);
}

/*
* Purpose: This function returns a random number between 1 and the number of sides provided by the user.
*/
int RollDie(int sides)
{
	return RandomInRange(1, sides);
}

/*
* Purpose: This functions takes the user input and does error handling.
*          There is no upper limit on the number entered by the user.
* Parameters:
*	lowerBound: The minimum number user can enter.
*	errorMessage: The error message to display based on the context of the function it is being called from.
* Return:
*	selectedOption: Returns the user input that passes all the checks.
*/
int inputHandling(int lowerBound, char errorMessage[])
{
	int selectedOption = 0;
	int successCode = 0; // 0 = invalid input, 1 = valid input
	do
	{
		successCode = scanf("%d", &selectedOption);
		if (successCode == 0 || selectedOption < lowerBound)
		{
			while ((getchar()) != '\n')
				continue;
			printf("\n%s", errorMessage);
		}
	} while (successCode == 0 || selectedOption < lowerBound);

	return selectedOption;
}

/*
* Purpose: This functions takes the user input and does error handling.
*          In this function, users have a set range of numbers they can input from.
* Parameters:
*	upperBound: The maximum number user can enter. **INCLUSIVE**
*	lowerBound: The minimum number user can enter.
*	errorMessage: The error message to display based on the context of the function it is being called from.
* Return:
*	selectedOption: Returns the user input that passes all the checks.
*/
int inputHandlingUpperBound(int upperBound, int lowerBound, char errorMessage[])
{
	int selectedOption = 0;
	int successCode = 0; // 0 = invalid input, 1 = valid input
	do
	{
		successCode = scanf("%d", &selectedOption);
		if (successCode == 0 || selectedOption > upperBound || selectedOption < lowerBound)
		{
			while ((getchar()) != '\n')
				continue;
			printf("\n%s", errorMessage);
		}
	} while (successCode == 0 || selectedOption > upperBound || selectedOption < lowerBound);

	return selectedOption;
}

int subf(int a, int b)
{
	return a - b;
}

int cubef(int a)
{
	return a * a * a;
}

int minf(int a, int b)
{
	if (a <= b)
	{
		return a;
	}
	else
	{
		return b;
	}
}

int oddf(int a)
{
	if (a % 2 == 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

#define SUB_MACRO(a, b) (a - b)
#define CUBE_MACRO(a) (a * a * a)
#define MIN_MACRO(a, b) ((a <= b) ? a : b)
#define ODD_MACRO(a) ((a % 2 == 0) ? 0 : 1)

/*
* The results are different in macros than functions for some implementations because macro are direct text replacement and thus execute code as seen without considering the semantics.
* The differences are in the implementations that increment or decrement the values and the differences are due to the value being changed multiple times instead of once and then passing by as value.
* In functions, the values are first calculated and then passed through it whereas in macros the values are calculated on run time as the implementation is being executed.
*/
void throwDown()
{
	printf("\n\nMacro’s vs. Functions Throw-down\n");

	int num1 = 10, num2 = 17;
	printf("Subtract Function (num1 - num2)\n %d\n\n", subf(num1, num2));

	num1 = 10;
	num2 = 17;
	printf("Subtract MACRO (num1 - num2)\n %d\n\n", SUB_MACRO(num1, num2));

	num1 = 10;
	num2 = 17;
	printf("Subtract Function (num1++ - num2--)\n %d\n\n", subf(num1++, num2--));

	num1 = 10;
	num2 = 17;
	printf("Subtract MACRO (num1++ - num2--)\n %d\n\n", SUB_MACRO(num1++, num2--));

	num1 = 10;
	num2 = 17;
	printf("Cube Function (num1)\n %d\n\n", cubef(num1));

	num1 = 10;
	num2 = 17;
	printf("Cube MACRO (num1)\n %d\n\n", CUBE_MACRO(num1));

	num1 = 10;
	num2 = 17;
	printf("Cube Function (--num1)\n %d\n\n", cubef(--num1));

	/*
		The result is different in this macro because because num1 is decremented 4 times and then multiplied by the decreased value.
		Thus the answer is not even a cube of num1 but rather a product of (8*8*7)
	*/
	num1 = 10;
	num2 = 17;
	printf("Cube MACRO (--num1)\n %d\n\n", CUBE_MACRO(--num1));

	num1 = 10;
	num2 = 17;
	printf("Minimum Function (num1, num2)\n %d\n\n", minf(num1, num2));

	num1 = 10;
	num2 = 17;
	printf("Minimum MACRO (num1, num2)\n %d\n\n", MIN_MACRO(num1, num2));

	num1 = 10;
	num2 = 17;
	printf("Minimum Function (--num1, --num2)\n %d\n\n", minf(--num1, --num2));

	num1 = 10;
	num2 = 17;
	printf("Minimum MACRO (--num1, --num2)\n %d\n\n", MIN_MACRO(--num1, --num2));

	num1 = 10;
	num2 = 17;
	printf("Odd Function (num1)\n %d\n\n", oddf(num1));

	num1 = 10;
	num2 = 17;
	printf("Odd MACRO (num1)\n %d\n\n", ODD_MACRO(num1));

	num1 = 10;
	num2 = 17;
	printf("Odd Function (num1++)\n %d\n\n", oddf(num1++));

	num1 = 10;
	num2 = 17;
	printf("Odd MACRO (num1++)\n %d\n\n", ODD_MACRO(num1++));
}