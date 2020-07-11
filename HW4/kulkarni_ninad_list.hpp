#pragma once
#ifndef HW4_KULKARNI_NINAD_LIST_HPP
#define HW4_KULKARNI_NINAD_LIST_HPP

#include<iostream>

template<class T>
class Node {
private:
    T data;
    Node<T> *nextNode;
public:
    Node(); // Default constructor.
    Node(T *data); //
    ~Node(); //
    void setNext(Node<T> *node); //
    Node<T> *getNext(); //
    T getData();
};

template<class T>
Node<T>::Node() {
    this->data = nullptr;
    this->nextNode = nullptr;
}

template<class T>
Node<T>::Node(T *data) {
    this->data = *data;
    this->nextNode = nullptr;
}

template<class T>
Node<T>::~Node<T>() {
//    delete data;
}

template<class T>
void Node<T>::setNext(Node<T> *node) {
    nextNode = node;
}

template<class T>
Node<T> *Node<T>::getNext() {
    return nextNode;
}

template<class T>
T Node<T>::getData() {
    return data.getColor();
}

template<class T>
class LinkedList {
private:
    Node<T> *head, *tail; // Head and Tail pointer for faster modification
public:
    LinkedList(); // Creates an empty list
    ~LinkedList(); // The destructor deletes all the nodes
    void addToFront(T *data); // Create a new node containing T data and add it to the front of the list
    void addToEnd(T *data); // Create a new node containing T data and add it to the end of the list
    bool addAtIndex(T *data, int index); // Create a new node containing T data and add it to the list at index
    T removeFromFront(); // Remove the node from the front of the list and returns it's data
    T removeFromEnd(); // Remove the node from the end of the list and returns it's data
    void removeTheFirst(T *data); // Search the nodes using the data and remove the first one found from the list
    void removeAllOf(T *data); // Search the nodes using the data and remove all the ones found from the list
    bool elementExists(T data); // Search the nodes using the data and return T/F if such node is found
    Node<T> *find(T data); // Search the nodes using the data and return that node if such node is found
    int indexOf(T data); // Search the nodes using the data and return that node's index
    Node<T> *retrieveFront(); // Returns the data from the first node
    Node<T> *retrieveEnd(); // Returns the data from the last node
    Node<T> *retrieve(int index); // Returns the data from the node at index
    void printList(); // Prints the content of each node. Goes LTR
    void empty(); // Empties the list by deleting all the nodes
    int length(); // Returns the length of the list
};

template<class T>
LinkedList<T>::LinkedList() {
    head = nullptr;
    tail = nullptr;
}

template<class T>
void LinkedList<T>::addToFront(T *data) {
    Node<T> *temp = new Node<T>(data);
    if (this->head == nullptr) {
        this->head = temp;
        this->tail = this->head;
    } else {
        temp->setNext(this->head);
        this->head = temp;
    }
}

template<class T>
void LinkedList<T>::addToEnd(T *data) {
    Node<T> *temp = new Node<T>(data);
    if (this->head == nullptr) {
        this->head = temp;
        this->tail = temp;
    } else {
        this->tail->setNext(new Node<T>(data));
        this->tail = this->tail->getNext();
    }
}

template<class T>
bool LinkedList<T>::addAtIndex(T *data, int index) {
    if (index < 0 || index >= length()) {
        return false;
    } else if (index == 0) {
        this->addToFront(data);
        return true;
    } else if (index == length() - 1) {
        this->addToEnd(data);
        return true;
    }

    Node<T> *temp = this->head;
    index--;
    while (index--) {
        temp = temp->getNext();
    }
    Node<T> *newNode = new Node<T>(data);
    temp->setNext(newNode);
    return true;
}

template<class T>
T LinkedList<T>::removeFromFront() {
    if (this->head == nullptr) { return NULL; }
    Node<T> *temp = this->head;
    this->head = this->head->getNext();
    T data = temp->getData();
    delete temp;
    return data;
}

template<class T>
T LinkedList<T>::removeFromEnd() {
    if (this->head == nullptr) { return NULL; }
    Node<T> *temp = this->head;
    while (temp->getNext() != this->tail) {
        temp = temp->getNext();
    }
    Node<T> *temp2 = this->tail;
    this->tail = temp;
    T data = temp2->getData();
    delete temp2;
    return data;
}

template<class T>
void LinkedList<T>::removeTheFirst(T *data) {
    Node<T> *temp = head;
    int count = 0;
    while (temp->getData().getColor() != data->getColor()) {
        if (temp == tail) { return; }
        temp = temp->getNext();
        count++;
    }
    if (count == 0) {
        this->removeFromFront();
        return;
    }
    if (count == length() - 1) {
        this->removeFromEnd();
        return;
    }
    Node<T> *temp2 = head;
    count--;
    while (count--) {
        temp2 = temp2->getNext();
    }
    temp2->setNext(temp2->getNext()->getNext());
    delete temp;
}

template<class T>
void LinkedList<T>::removeAllOf(T *data) {
    Node<T> *temp = this->head;
    while (true) {
        while (temp->getData().getColor() != data->getColor()) {
            if (temp == this->tail) { return; }
            temp = temp->getNext();
        }
        if (temp == this->head) {
            this->removeFromFront();
            continue;
        }
        if (temp == this->tail) {
            this->removeFromEnd();
            return;
        }
        Node<T> *temp2 = this->head;
        while (temp2->getNext() != temp) {
            temp2 = temp2->getNext();
        }
        temp2->setNext(temp2->getNext()->getNext());
        delete temp;
        return;
    }
}

template<class T>
bool LinkedList<T>::elementExists(T data) {
    Node<T> *temp = this->head;

    while (temp->getData()->getColor() != *data->getColor()) {
        if (temp == this->tail) { return false; }
        temp = temp->getNext();
    }

    return true;
}

template<class T>
Node<T> *LinkedList<T>::find(T data) {
    Node<T> *temp = head;

    if (elementExists(data)) {
        while (temp->getData() != data) {
            temp = temp->getNext();
        }
    }

    return temp;
}

template<class T>
int LinkedList<T>::indexOf(T data) {
    int count = 0;
    Node<T> *temp = this->head;
    while (temp->getData() != data) {
        if (temp == this->tail) { return -1; }
        temp = temp->getNext();
        count++;
    }
    return count;
}

template<class T>
Node<T> *LinkedList<T>::retrieveFront() {
    Node<T> *temp = this->head;
    return temp->getData();
}

template<class T>
Node<T> *LinkedList<T>::retrieveEnd() {
    Node<T> *temp = this->tail;
    return temp->getData();
}

template<class T>
Node<T> *LinkedList<T>::retrieve(int index) {
    int listSize = length();
    if (index < 0 || index > listSize) {
        return nullptr;
    } else if (index == 0) {
        return retrieveFront();
    } else if (index == listSize - 1) {
        return retrieveEnd();
    }

    Node<T> *temp = this->head;
    index--;
    while (index--) {
        temp = temp->getNext();
    }
    return temp->getData();
}

template<class T>
void LinkedList<T>::printList() {
//    Node<T> *temp = this->head;
//    std::cout << "YO";
//    std::cout << temp->getData() << "\t";
//
//    while (temp != this->tail) {
//        temp = temp->getNext();
//        std::cout << temp->getData() << "\t";
//    }
//
//    std::cout << std::endl;
}

template<class T>
void LinkedList<T>::empty() {
    Node<T> *temp = this->head;

    while (temp != this->tail) {
        this->head = temp;
        temp = temp->getNext();
        delete head;
    }
    delete tail;
}

template<class T>
int LinkedList<T>::length() {
    int counter = 0;
    Node<T> *temp = this->head;
    while (temp != nullptr) {
        temp = temp->getNext();
        counter++;
    }

    return counter;
}

template<class T>
LinkedList<T>::~LinkedList() {
    empty();
}

class Zombie {
private:
    char color;
public:
    Zombie(); // Default constructor. Assign a color of transparent to the zombie.
    Zombie(char color); // Creates
    void setColor(char color);

    char getColor();

    Zombie *operator=(Zombie *);
};

Zombie::Zombie(char color) {
    this->color = color;
}

void Zombie::setColor(char color) {
    this->color = color;
}

char Zombie::getColor() {
    return this->color;
}

Zombie *Zombie::operator=(Zombie *zombie) {
    this->setColor(zombie->getColor());
    return zombie;
}

#endif //HW4_KULKARNI_NINAD_LIST_HPP
