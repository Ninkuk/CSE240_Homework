#include <iostream>
#include "termcolor.hpp"

using namespace std;
using namespace termcolor;

int inputHandling();
char **generateLand(int width, int height);
char pickLandType();
char generateNeighbor(char item);
void printLand(char **land, int width, int height);
char newFromRuralLand();
char newFromForest();
char newFromTown();
char newFromWater();
char newFromCity();
char newFromMountain();
char evaluateProbability(struct landProbabilities *p);

// Enums with default values used for better code legibility in pickLandType
enum terrains {
    RURAL_LAND, FOREST, TOWN, WATER, CITY, MOUNTAIN
};

// Structs are used as a blueprint to create unique probability for each landType. Used in evaluateProbability
struct landProbabilities {
    short int R, F, T, W, C, M;
};

int main(int argc, char **argv) {
    cout << "Welcome to Fantasy Land Generator!" << endl;
    cout << "Enter width of land: ";
    int width = inputHandling();
    cout << "Enter height of land: ";
    int height = inputHandling();

    char **land = generateLand(width, height);
    printLand(land, width, height);
}

/*
* Purpose: This functions takes the width and height passed by the user and allocates a dynamic 2D array which is filled by function calls to appropriate functions.
*/
char **generateLand(int width, int height) {
    srand(time(0));

    // dynamically allocate memory for 2D array in heap
    char **land = new char *[height];
    for (int i = 0; i < height; ++i) {
        land[i] = new char[width];
    }

    // generate the top left land
    char topLeftTerrain = pickLandType();

    // Nested for loop to fill the 2D array. Outer loop handles the rows and inner handles the columns.
    for (int h = 0; h < height; h++) {
        for (int w = 0; w < width; w++) {

            // Different states of the grid. Top left is filled by pickLandType.
            //      First row has dependency on the land on index directly to the left of it.
            //      First column has dependency on the land on index directly to the top of it.
            //      Rest of the grid's dependency can either be on the index on left or top of it. Determined by generating a number between 0 and 1
            if (h == 0 && w == 0) { // top left terrain
                land[0][0] = topLeftTerrain;
            } else if (h == 0) { // first row
                land[h][w] = generateNeighbor(land[0][w - 1]);
            } else if (w == 0) { // first col
                land[h][w] = generateNeighbor(land[h - 1][0]);
            } else { // rest of the grid
                int dependency = rand() % 2; // generate a number between 0 and 1

                // 0 = left, 1 = top
                if (dependency) {
                    land[h][w] = generateNeighbor(land[h - 1][w]);
                } else {
                    land[h][w] = generateNeighbor(land[h][w - 1]);
                }
            }
        }
    }

    return land;
}

/*
* Purpose: This functions prints the generated land as a grid of dimension width x height.
*          Implemented termcolor for coloring the output of each land type.
 *
 *         Rural Land = Red, Forest = Green, Town = Yellow, Water = Blue, City = Cyan, Mountains = Magenta
 *
 *         There could be possible legibility issues based on your terminal. (ex. white text on yellow)
*/
void printLand(char **land, int width, int height) {
    char landType;
    for (int h = 0; h < height; h++) {
        for (int w = 0; w < width; w++) {
            landType = land[h][w];
            switch (landType) {
                case 'R':
                    cout << on_red << landType;
                    break;
                case 'F':
                    cout << on_green << landType;
                    break;
                case 'T':
                    cout << on_yellow << landType;
                    break;
                case 'W':
                    cout << on_blue << landType;
                    break;
                case 'C':
                    cout << on_cyan << landType;
                    break;
                case 'M':
                    cout << on_magenta << landType;
                    break;
                default:
                    cout << on_white << landType;
                    break;
            }
        }
        cout << reset << endl;
    }
}

/*
* Purpose: This functions serves the purpose of generating the first land type on the top-left part of the grid
*          This land is generated completely randomly with no dependency on any probabilities.
*/
char pickLandType() {
    int randomNum = rand() % 6;
    switch (randomNum) {
        case RURAL_LAND:
            return 'R';
        case FOREST:
            return 'F';
        case TOWN:
            return 'T';
        case WATER:
            return 'W';
        case CITY:
            return 'C';
        case MOUNTAIN:
            return 'M';
        default:
            return 0;
    }
}

/*
* Purpose: This functions takes the landType from index determined by generateLand and creates its neighbouring land by calling the corresponding functions.
*/
char generateNeighbor(char item) {
    switch (item) {
        case 'R':
            return newFromRuralLand();
        case 'F':
            return newFromForest();
        case 'T':
            return newFromTown();
        case 'W':
            return newFromWater();
        case 'C':
            return newFromCity();
        case 'M':
            return newFromMountain();
        default:
            return 0;
    }
}

/*
* Purpose: The following 6 functions serve as a way to generate land based on the existing land type from the last index.
*          A struct with unique probabilities is created for each land type and returns the char of land that is generated.
*/

char newFromRuralLand() {
    struct landProbabilities ruralProbabilities = {40, 25, 15, 10, 0, 10};
    return evaluateProbability(&ruralProbabilities);
}

char newFromForest() {
    struct landProbabilities waterProbs = {20, 40, 5, 20, 0, 15};
    return evaluateProbability(&waterProbs);
}

char newFromTown() {
    struct landProbabilities townProbs = {20, 40, 5, 20, 0, 15};
    return evaluateProbability(&townProbs);
}

char newFromWater() {
    struct landProbabilities waterProbs = {15, 20, 5, 40, 10, 10};
    return evaluateProbability(&waterProbs);
}

char newFromCity() {
    struct landProbabilities cityProbs = {0, 15, 25, 10, 40, 10};
    return evaluateProbability(&cityProbs);
}

char newFromMountain() {
    struct landProbabilities mountainProbs = {5, 15, 5, 15, 10, 50};
    return evaluateProbability(&mountainProbs);
}

/*
* Purpose: This functions takes the struct with probabilities of each land being generated.
*          Then a random number is taken and based on the calculations, the char of corresponding land is returned.
* Parameters:
*	landProbabilities: This struct contains the percent probability of land to generate
* Return:
*	generatedLand: This returns the char land generated based on the result of the if control
*/
char evaluateProbability(struct landProbabilities *p) {
    int landProbability = rand() % 100;

    if (landProbability < p->R) {
        return 'R';
    } else if (landProbability < p->F + p->R) {
        return 'F';
    } else if (landProbability < p->T + (p->F + p->R)) {
        return 'T';
    } else if (landProbability < p->W + (p->T + p->F + p->R)) {
        return 'W';
    } else if (landProbability <
               p->C + (p->W + p->T + p->F + p->R)) {
        return 'C';
    } else {
        return 'M';
    }
}

/*
* Purpose: This functions takes the user input and does error handling.
*          There is no upper limit on the number entered by the user.
* Return:
*	selectedOption: Returns the user input that passes all the checks
*/
int inputHandling() {
    int selectedOption = 0;
    int successCode = 0; // 0 = invalid input, 1 = valid input
    do {
        successCode = scanf("%d", &selectedOption);
        if (successCode == 0 || selectedOption < 20 || selectedOption > 50) {
            while ((getchar()) != '\n')
                continue;
            cout << "\nPlease enter a valid positive number between 20 and 50: ";
        }
    } while (successCode == 0 || selectedOption < 20 || selectedOption > 50);

    return selectedOption;
}
