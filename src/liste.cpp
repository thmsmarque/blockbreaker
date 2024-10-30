#ifndef LISTE_CPP
#define LISTE_CPP

#include <stdlib.h>
#include <iostream>


template <typename T>

class Liste
{
private:

    struct Node {
        T data;
        Node* next;
        Node(const T& value) : data(value), next(nullptr) {}
    };

    Node *head;

public:
    Liste()
    {
        head = nullptr;
    }
    
    ~Liste(){
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }


    void add(const T& value)
    {
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
    }

    bool estVide()
    {
        return head == nullptr;
    }

    int size() {
        int count = 0;
        Node* current = head;
        while (current) {
            ++count;
            current = current->next;
        }
        return count;
    }

    Liste copieListe(Liste t)
    {
        return t;
    }

T* index(int index)
{
    int count = 0;
    Node* current = head;

    while (current && count < index) { 
        count++; 
        current = current->next;
    }
    if (!current) {
        return NULL;
    }
    return &current->data;

}

    T getTete()
    {
        return this.head->data;
    }

    void remove(const T& value) {
    Node* current = head;
    Node* previous = nullptr;
    bool trouve = false;
    
    while (current && current->data != value) {
        previous = current;
        current = current->next;
    }

    if (current) {
        if (previous) {  //element trouve
        
            previous->next = current->next;
            current->next =nullptr;
        } else {
            
            head = current->next;  //element en tete de la liste
        }
        delete current;
    }
}

void remove(int index)
{
    int count = 0;
    Node* current = head;
    Node* previous = nullptr;

    while (current && count < index) { 
        count++;
        previous = current;
        current = current->next;
    }
    if (current) {
        if (previous) {  //element trouve
        
            previous->next = current->next;
            current->next =nullptr;
        } else {
            
            head = current->next;  //element en tete de la liste
        }
        delete current;
}
}

void removeAll(T& value) {
    Node* current = head;
    Node* previous = nullptr;

    while (current) {
        if (current->data == value) {
        
            Node* temp = current;
            if (previous) {
                previous->next = current->next;
                current = current->next;
            } else {
                head = current->next;
                current = head;
            }
            delete temp;
        } else {
            previous = current;
            current = current->next; //on passe à l'element suivant
        }
    }
}


    void print() {
        Node* current = head;
        while (current) {
            std::cout << current->data.getValue() << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }
};

#endif