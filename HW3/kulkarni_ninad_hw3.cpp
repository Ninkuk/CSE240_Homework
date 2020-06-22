#include <iostream>

using namespace std;

int inputHandling();

int main(int argc, char **argv) {
    cout << "Welcome to Fantasy Land Generator!" << endl;
    cout << "Enter width of land: ";
    int width = inputHandling();
    cout << "Enter height of land: ";
    int height = inputHandling();
    return 1;
}

/*
* Purpose: This functions takes the user input and does error handling.
*          There is no upper limit on the number entered by the user.
* Return:
*	selectedOption: Returns the user input that passes all the checks.
*/
int inputHandling() {
    int selectedOption = 0;
    int successCode = 0; // 0 = invalid input, 1 = valid input
    do {
        successCode = scanf("%d", &selectedOption);
        if (successCode == 0 || selectedOption < lowerBound) {
            while ((getchar()) != '\n')
                continue;
            printf("\n%s", errorMessage);
        }
    } while (successCode == 0 || selectedOption < lowerBound);

    return selectedOption;
}