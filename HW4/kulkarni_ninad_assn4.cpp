#include <iostream>
#include "kulkarni_ninad_list.hpp"

int inputHandling();

char getColorChar(int colorInt);

void runRandomAction(LinkedList<Zombie> *, Zombie *);

void engineAction(LinkedList<Zombie> *, Zombie *);

void cabooseAction(LinkedList<Zombie> *, Zombie *);

void jumpInLineAction(LinkedList<Zombie> *, Zombie *);

void everyoneOutAction(LinkedList<Zombie> *, Zombie *);

void youreDoneAction(LinkedList<Zombie> *, Zombie *);

void brainsAction(LinkedList<Zombie> *, Zombie *);

void rainbowBrains(LinkedList<Zombie> *, Zombie *);

enum zombieActions {
    ENGINE, CABOOSE, JUMP_IN, EVERYONE_OUT, YOURE_DONE, BRAINS, RAINBOW
};

int main() {
    std::cout << "Welcome! How many round would you like to run?  ";
    int numberOfRounds = inputHandling();

    // Init empty list
    LinkedList<Zombie> *zombieCongaList = new LinkedList<Zombie>();

    srand(time(0));

    // Setup the list
    // 1. Run a Rainbow Brains! Actions
    // 2. Run a random action between 2 and 5
    Zombie *z = new Zombie(getColorChar(rand() % 6));
    rainbowBrains(zombieCongaList, z);
    int randomAction = (rand() % 4) + 2;
    std::cout << randomAction << std::endl;
    switch (randomAction) {
        case 0:
            std::cout << "bruh0" << std::endl;
            engineAction(zombieCongaList, z);
            break;
        case 1:
            std::cout << "bruh1" << std::endl;
            cabooseAction(zombieCongaList, z);
            break;
        case 2:
            std::cout << "bruh2" << std::endl;
            jumpInLineAction(zombieCongaList, z);
            break;
        case 3:
            std::cout << "bruh3" << std::endl;
            everyoneOutAction(zombieCongaList, z);
            break;
        case 4:
            std::cout << "bruh4" << std::endl;
            youreDoneAction(zombieCongaList, z);
            break;
        case 5:
            std::cout << "bruh5" << std::endl;
            brainsAction(zombieCongaList, z);
            break;
        case 6:
            std::cout << "bruh6" << std::endl;
            rainbowBrains(zombieCongaList, z);
            break;
        default:
            std::cout << "Oops something went wrong in executing a random action" << std::endl;
            break;
    }

    std::cout << "works?" << std::endl;

//    zombieCongaList->printList();

    int roundCounter = 0;
    for (roundCounter = 0; roundCounter < numberOfRounds; roundCounter++) {
        std::cout << "reached loop" << std::endl;
        Zombie *zombie = new Zombie(getColorChar(rand() % 6));
//        runRandomAction(zombieCongaList, zombie);
        engineAction(zombieCongaList, zombie);
        std::cout << "loop" << roundCounter << std::endl;

//        zombieCongaList->printList();
        std::cout << "printedf" << roundCounter << std::endl;
    }

    std::cout << "Would you like to continue the party? (y/n)  " << std::endl;
    return 0;
}

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

void engineAction(LinkedList<Zombie> *zombieCongaList, Zombie *zombie) {
    std::cout << "eng" << std::endl;

    zombieCongaList->addToFront(zombie);
    std::cout << "eng ran" << std::endl;

    std::cout << "size " << zombieCongaList->length();
    zombieCongaList->printList();
}

void cabooseAction(LinkedList<Zombie> *zombieCongaList, Zombie *zombie) {
    std::cout << "cab" << std::endl;

    zombieCongaList->addToEnd(zombie);
}

void jumpInLineAction(LinkedList<Zombie> *zombieCongaList, Zombie *zombie) {
    std::cout << "lin" << std::endl;

    int randomLocation = rand() % zombieCongaList->length();
    zombieCongaList->addAtIndex(zombie, randomLocation);
}

void everyoneOutAction(LinkedList<Zombie> *zombieCongaList, Zombie *zombie) {
    std::cout << "out" << std::endl;

    zombieCongaList->removeAllOf(zombie);
}

void youreDoneAction(LinkedList<Zombie> *zombieCongaList, Zombie *zombie) {
    std::cout << "yo" << std::endl;

    zombieCongaList->removeTheFirst(zombie);
}

void brainsAction(LinkedList<Zombie> *zombieCongaList, Zombie *zombie) {
    std::cout << "brain" << std::endl;

    Zombie *z2 = new Zombie(zombie->getColor());
    Zombie *z3 = new Zombie(zombie->getColor());

    zombieCongaList->addToFront(zombie);
    zombieCongaList->addToEnd(z2);
    zombieCongaList->addAtIndex(z3, zombieCongaList->length() / 2);
}

void rainbowBrains(LinkedList<Zombie> *zombieCongaList, Zombie *zombie) {
    std::cout << "rain" << std::endl;

    zombieCongaList->addToFront(zombie);

    // Add each color zombie to the end
    zombieCongaList->addToEnd(new Zombie('R'));
    zombieCongaList->addToEnd(new Zombie('Y'));
    zombieCongaList->addToEnd(new Zombie('G'));
    zombieCongaList->addToEnd(new Zombie('B'));
    zombieCongaList->addToEnd(new Zombie('M'));
    zombieCongaList->addToEnd(new Zombie('C'));
}

void removeHeadAndTail(LinkedList<Zombie> *zombieCongaList) {
    zombieCongaList->removeFromFront();
    zombieCongaList->removeFromEnd();
}

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
int inputHandling() {
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