#include <iostream>
#include "kulkarni_ninad_list.hpp"

void driverMethod();

int inputHandlingInt();

char getColorChar(int colorInt);

void runRandomAction(LinkedList<Zombie> *, Zombie *);

void engineAction(LinkedList<Zombie> *, Zombie *);

void cabooseAction(LinkedList<Zombie> *, Zombie *);

void jumpInLineAction(LinkedList<Zombie> *, Zombie *);

void everyoneOutAction(LinkedList<Zombie> *, Zombie *);

void youreDoneAction(LinkedList<Zombie> *, Zombie *);

void brainsAction(LinkedList<Zombie> *, Zombie *);

void rainbowBrains(LinkedList<Zombie> *, Zombie *);

void removeHeadAndTail(LinkedList<Zombie> *);

enum zombieActions {
    ENGINE, CABOOSE, JUMP_IN, EVERYONE_OUT, YOURE_DONE, BRAINS, RAINBOW
};

int main() {
    srand(time(0));
    driverMethod();
}

void driverMethod() {
    std::cout << "Welcome! How many round would you like to run?  ";
    int numberOfRounds = inputHandlingInt();
    std::cout << std::endl;

    // Init empty list
    LinkedList<Zombie> *zombieCongaList = new LinkedList<Zombie>();


    // Setup the list
    // 1. Run a Rainbow Brains! Actions
    // 2. Run a random action between 2 and 5
    Zombie *z = new Zombie(getColorChar(rand() % 6));
    rainbowBrains(zombieCongaList, z);
    int randomAction = (rand() % 4) + 2;
    switch (randomAction) {
        case 0:
            engineAction(zombieCongaList, z);
            break;
        case 1:
            cabooseAction(zombieCongaList, z);
            break;
        case 2:
            jumpInLineAction(zombieCongaList, z);
            break;
        case 3:
            everyoneOutAction(zombieCongaList, z);
            break;
        case 4:
            youreDoneAction(zombieCongaList, z);
            break;
        case 5:
            brainsAction(zombieCongaList, z);
            break;
        case 6:
            rainbowBrains(zombieCongaList, z);
            break;
        default:
            std::cout << "Oops something went wrong in executing a random action" << std::endl;
            break;
    }

    int roundCounter = 0;
    for (roundCounter = 0; roundCounter < numberOfRounds; roundCounter++) {
        std::cout << "************************************************" << std::endl;
        std::cout << "Round: " << roundCounter + 1 << std::endl;
        std::cout << "The zombie party keeps on groaning!" << std::endl;
        std::cout << "Size: " << zombieCongaList->length() << " :: ";
        zombieCongaList->printList();

        Zombie *zombie = new Zombie(getColorChar(rand() % 6));
        runRandomAction(zombieCongaList, zombie);

        std::cout << "The conga line is now:" << std::endl;
        std::cout << "Size: " << zombieCongaList->length() << " :: ";
        zombieCongaList->printList();
        std::cout << "************************************************" << std::endl;

        if (roundCounter % 5 == 0) {
            removeHeadAndTail(zombieCongaList);
            std::cout << "The conga line is now:" << std::endl;
            std::cout << "Size: " << zombieCongaList->length() << " :: ";
            zombieCongaList->printList();
        }
    }

    std::cout << "Would you like to continue the party? (y/n)  ";
    char selectedOption = '0';
    scanf(" %c", &selectedOption);

    if (selectedOption == 'y') {
        std::cout << std::endl;
        driverMethod();
    } else {
        std::cout << "Invalid input. Exiting code";
    }
}

// Generates a random number between 0 and 7 and executes a zombie action corresponding to it.
void runRandomAction(LinkedList<Zombie> *zombieCongaList, Zombie *zombie) {
    int randomAction = rand() % 7;
    switch (randomAction) {
        case ENGINE:
            engineAction(zombieCongaList, zombie);
            break;
        case CABOOSE:
            cabooseAction(zombieCongaList, zombie);
            break;
        case JUMP_IN:
            jumpInLineAction(zombieCongaList, zombie);
            break;
        case EVERYONE_OUT:
            everyoneOutAction(zombieCongaList, zombie);
            break;
        case YOURE_DONE:
            youreDoneAction(zombieCongaList, zombie);
            break;
        case BRAINS:
            brainsAction(zombieCongaList, zombie);
            break;
        case RAINBOW:
            rainbowBrains(zombieCongaList, zombie);
            break;
        default:
            std::cout << "Oops something went wrong in executing a random action" << std::endl;
            break;
    }
}

// This zombie becomes the first Zombie in the conga line
void engineAction(LinkedList<Zombie> *zombieCongaList, Zombie *zombie) {
    zombieCongaList->addToFront(zombie);

    std::cout << zombie->getColor() << " zombie jumps in the front of the line! (ENGINE)" << std::endl;
}

// This zombie becomes the last zombie in the conga line
void cabooseAction(LinkedList<Zombie> *zombieCongaList, Zombie *zombie) {
    zombieCongaList->addToEnd(zombie);

    std::cout << zombie->getColor() << " zombie jumps in the back of the line! (CABOOSE)" << std::endl;
}

// This zombie joins the conga line at position X where X <= length of the linked list
void jumpInLineAction(LinkedList<Zombie> *zombieCongaList, Zombie *zombie) {
    int randomLocation = rand() % zombieCongaList->length();
    zombieCongaList->addAtIndex(zombie, randomLocation);

    std::cout << zombie->getColor() << " zombie jumps in the line at " << randomLocation << " location! (JUMP IN LINE)"
              << std::endl;
}

// Remove all matching zombies from the linked list
void everyoneOutAction(LinkedList<Zombie> *zombieCongaList, Zombie *zombie) {
    zombieCongaList->removeAllOf(zombie);

    std::cout << "All " << zombie->getColor() << " zombies have left the chat! (EVERYONE OUT)" << std::endl;
}

// Remove the first matching zombie from the linked list
void youreDoneAction(LinkedList<Zombie> *zombieCongaList, Zombie *zombie) {
    zombieCongaList->removeTheFirst(zombie);
    std::cout << "The first " << zombie->getColor() << " zombie has left the chat! (YOU'RE DONE BUB)" << std::endl;
}

// Generate two more matching Zombies and add one to the front, one to the end and one to the middle
void brainsAction(LinkedList<Zombie> *zombieCongaList, Zombie *zombie) {
    Zombie *z2 = new Zombie(zombie->getColor());
    Zombie *z3 = new Zombie(zombie->getColor());

    zombieCongaList->addToFront(zombie);
    zombieCongaList->addToEnd(z2);
    zombieCongaList->addAtIndex(z3, zombieCongaList->length() / 2);

    std::cout << zombie->getColor() << " zombie brings its friends! (BRAINS!)" << std::endl;
}

// Add this zombie to the front, then add one of each zombie color to the end of the conga line.
void rainbowBrains(LinkedList<Zombie> *zombieCongaList, Zombie *zombie) {
    zombieCongaList->addToFront(zombie);

    // Add each color zombie to the end
    zombieCongaList->addToEnd(new Zombie('R'));
    zombieCongaList->addToEnd(new Zombie('Y'));
    zombieCongaList->addToEnd(new Zombie('G'));
    zombieCongaList->addToEnd(new Zombie('B'));
    zombieCongaList->addToEnd(new Zombie('M'));
    zombieCongaList->addToEnd(new Zombie('C'));

    std::cout << zombie->getColor() << " zombie brought a whole party! (RAINBOW BRAINS!)" << std::endl;
}

// This function is used when head and tail needs to be removed every 5 rounds
void removeHeadAndTail(LinkedList<Zombie> *zombieCongaList) {
    zombieCongaList->removeFromFront();
    zombieCongaList->removeFromEnd();

    std::cout << "Head and Tail zombies removed after every 5 moves!" << std::endl;
}

// Returns a color char based on the random number passed in
char getColorChar(int colorInt) {
    switch (colorInt) {
        case 0:
            return 'R';
        case 1:
            return 'Y';
        case 2:
            return 'G';
        case 3:
            return 'B';
        case 4:
            return 'M';
        case 5:
            return 'C';
        default:
            return 0;
    }
}

/*
* Purpose: This functions takes the user input and does error handling.
*          There is no upper limit on the number entered by the user.
* Return:
*	selectedOption: Returns the user input that passes all the checks
*/
int inputHandlingInt() {
    int selectedOption = 0;
    int successCode = 0; // 0 = invalid input, 1 = valid input
    do {
        successCode = scanf("%d", &selectedOption);
        if (successCode == 0 || selectedOption < 0) {
            while ((getchar()) != '\n')
                continue;
            std::cout << "\nPlease enter a valid positive number: ";
        }
    } while (successCode == 0 || selectedOption < 0);

    return selectedOption;
}